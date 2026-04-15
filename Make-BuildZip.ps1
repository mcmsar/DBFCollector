#Requires -Version 5.1
<#
.SYNOPSIS
    Creates a distributable build archive for DBFCollectorMT.

.DESCRIPTION
    Packages all source, headers, and third-party libraries needed to build
    the project from a clean checkout, excluding:
      - Build output directories (Debug, Release, x64, Build)
      - IntelliSense/browse databases (.sdf, .opensdf, .bsc, .sbr)
      - VS user/session files (.suo, .user, .aps)
      - Intermediate compiler output (.obj, .pch, .idb, .exp, .map, .binlog)
      - Existing distribution archives (.zip, .7z)
      - vcpkg_installed (vcpkg build artefacts)

    Output: DBFCollectorMT_VS2026_<mm>_<dd>_<yy>.zip
    written to the project root (same directory as this script).

.PARAMETER OutputDir
    Directory to write the zip file to.  Defaults to the project root.

.EXAMPLE
    .\Make-BuildZip.ps1
    .\Make-BuildZip.ps1 -OutputDir D:\Releases
#>
param(
    [string]$OutputDir = $PSScriptRoot
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem

# ── Output path ──────────────────────────────────────────────────────────────
$date    = Get-Date
$zipName = "DBFCollectorMT_VS2026_{0}_{1}_{2}.zip" -f `
           $date.ToString("MM"), $date.ToString("dd"), $date.ToString("yy")

$OutputDir = (Resolve-Path $OutputDir).Path
$zipPath   = Join-Path $OutputDir $zipName
$rootDir   = (Resolve-Path $PSScriptRoot).Path.TrimEnd('\')

# ── What to include ──────────────────────────────────────────────────────────

# Subdirectories of the project root to recurse into
$includeDirs = @(
    "DBFCollectorMT_Apr2_2025",   # VS project (source, vcxproj, FreqSwitch, etc.)
    "3rdParty",                    # Intel IPP/MKL, Xerces, XSD-3.3, Microsoft
    "Common",                      # Shared source + headers + Library/
    "ADBoards",                    # Hardware-interface source and headers
    "DBFPassScheduler",            # Pass-scheduler source + headers
    "Config",                      # Runtime XML/XSD config files
    "Redist",                      # Runtime DLLs (IPP, Xerces, EMSConfigClient)
    ".github",                     # CI workflow
    "scripts"                      # Helper scripts (Check-DllDependencies, etc.)
)

# Loose files at the project root to include
$includeRootFiles = @(
    "EMSConfigClientCPP.dll",       # Win32 EMS config DLL
    "EMSConfigClientCPPx64.def",    # x64 exports definition
    "EMSConfigClientCPPx64.dll",    # x64 EMS config DLL
    ".gitattributes"
)

# ── What to exclude ──────────────────────────────────────────────────────────

# Folder names that will be skipped entirely wherever they appear in the tree
$excludeDirNames = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
@(
    'Debug',            # MSVC output
    'Release',          # MSVC output
    'x64',              # MSVC x64 output (DBFCollectorMT_Apr2_2025\x64\)
    'Build',            # BSCMake / browse output
    'ipch',             # IntelliSense precompiled headers
    'vcpkg_installed',  # vcpkg build artefacts (in-repo deps are in 3rdParty now)
    '.git'              # git repository internals
) | ForEach-Object { $excludeDirNames.Add($_) | Out-Null }

# File extensions to skip
$excludeExtensions = [System.Collections.Generic.HashSet[string]]::new(
    [System.StringComparer]::OrdinalIgnoreCase)
@(
    # VS IntelliSense / browse databases (can be >100 MB each)
    '.sdf', '.opensdf', '.bsc', '.sbr',
    # Compiler/linker intermediates
    '.obj', '.pch', '.idb', '.exp', '.map', '.binlog',
    # VS session / user-preference files
    '.suo', '.user', '.aps',
    # Distribution archives (zip would otherwise include old copies of itself)
    '.zip', '.7z'
) | ForEach-Object { $excludeExtensions.Add($_) | Out-Null }

# ── File collection ──────────────────────────────────────────────────────────

function Get-IncludedFiles([string]$dir) {
    # Skip this entire subtree if the folder name is on the exclusion list
    if ($excludeDirNames.Contains((Split-Path $dir -Leaf))) { return }

    foreach ($item in Get-ChildItem -LiteralPath $dir) {
        if ($item.PSIsContainer) {
            Get-IncludedFiles -dir $item.FullName
        } elseif (-not $excludeExtensions.Contains($item.Extension)) {
            $item   # yield the FileInfo
        }
    }
}

Write-Host "Collecting files..."
$allFiles = [System.Collections.Generic.List[System.IO.FileInfo]]::new()

foreach ($name in $includeDirs) {
    $path = Join-Path $rootDir $name
    if (Test-Path -LiteralPath $path) {
        Get-IncludedFiles -dir $path | ForEach-Object { $allFiles.Add($_) }
    } else {
        Write-Warning "Directory not found, skipping: $path"
    }
}

foreach ($name in $includeRootFiles) {
    $path = Join-Path $rootDir $name
    if (Test-Path -LiteralPath $path) {
        $allFiles.Add((Get-Item -LiteralPath $path))
    } else {
        Write-Warning "Root file not found, skipping: $path"
    }
}

$totalBytes = ($allFiles | Measure-Object -Property Length -Sum).Sum
Write-Host ("Files to archive : {0:N0}  ({1:F1} MB uncompressed)" -f `
            $allFiles.Count, ($totalBytes / 1MB))
Write-Host "Output           : $zipPath"
Write-Host ""

# ── Create the zip ───────────────────────────────────────────────────────────
if (Test-Path -LiteralPath $zipPath) {
    Write-Host "Removing existing archive: $(Split-Path $zipPath -Leaf)"
    Remove-Item -LiteralPath $zipPath
}

$sw          = [System.Diagnostics.Stopwatch]::StartNew()
$zipStream   = [System.IO.File]::Create($zipPath)
$archive     = [System.IO.Compression.ZipArchive]::new(
                   $zipStream,
                   [System.IO.Compression.ZipArchiveMode]::Create,
                   $false)   # leaveOpen = false

try {
    $i = 0
    foreach ($file in $allFiles) {
        $i++
        # Entry name = path relative to project root, using backslashes (Windows convention)
        $entryName = $file.FullName.Substring($rootDir.Length + 1)

        if ($i % 100 -eq 0 -or $i -eq $allFiles.Count) {
            $pct = [int]($i * 100 / $allFiles.Count)
            Write-Progress -Activity "Creating $zipName" `
                           -Status   "$pct% — $entryName" `
                           -PercentComplete $pct
        }

        [System.IO.Compression.ZipFileExtensions]::CreateEntryFromFile(
            $archive,
            $file.FullName,
            $entryName,
            [System.IO.Compression.CompressionLevel]::Optimal
        ) | Out-Null
    }
} finally {
    $archive.Dispose()   # also flushes and closes $zipStream
    Write-Progress -Activity "Creating $zipName" -Completed
}

$sw.Stop()
$zipInfo = Get-Item -LiteralPath $zipPath

Write-Host ("Done in {0:F0}s" -f $sw.Elapsed.TotalSeconds)
Write-Host ("Archive : {0}  ({1:F1} MB)" -f $zipInfo.Name, ($zipInfo.Length / 1MB))
