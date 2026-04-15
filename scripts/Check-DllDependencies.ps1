<#
.SYNOPSIS
    Checks that all DLL dependencies of a given executable are resolvable.

.PARAMETER ExePath
    Path to the .exe to analyze.

.PARAMETER SearchDirs
    Additional directories to search for DLLs (beyond the exe's own directory).

.OUTPUTS
    Exits 0 if all dependencies are found, 1 if any are missing.
#>
param(
    [Parameter(Mandatory)]
    [string]$ExePath,

    [string[]]$SearchDirs = @()
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

# Locate dumpbin.exe via vswhere
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
if (-not (Test-Path $vswhere)) {
    Write-Error "vswhere.exe not found. Is Visual Studio installed?"
    exit 1
}

$vsPath = & $vswhere -latest -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (-not $vsPath) {
    Write-Error "No Visual Studio installation with VC tools found."
    exit 1
}

$vcToolsVersion = (Get-Content "$vsPath\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt").Trim()
$dumpbin = "$vsPath\VC\Tools\MSVC\$vcToolsVersion\bin\Hostx86\x86\dumpbin.exe"

if (-not (Test-Path $dumpbin)) {
    Write-Error "dumpbin.exe not found at: $dumpbin"
    exit 1
}

Write-Host "Using dumpbin: $dumpbin"

# Known Windows system DLLs that are always present (case-insensitive)
$systemDlls = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
@(
    'kernel32.dll','user32.dll','gdi32.dll','advapi32.dll','shell32.dll',
    'ole32.dll','oleaut32.dll','rpcrt4.dll','ntdll.dll','msvcrt.dll',
    'ws2_32.dll','wsnmp32.dll','mpr.dll','winmm.dll','wsock32.dll',
    'odbc32.dll','odbccp32.dll','comdlg32.dll','comctl32.dll',
    'secur32.dll','crypt32.dll','wldap32.dll','bcrypt.dll','wininet.dll',
    'mswsock.dll','winspool.drv','version.dll','setupapi.dll',
    'psapi.dll','shlwapi.dll','imagehlp.dll','dbghelp.dll'
) | ForEach-Object { $systemDlls.Add($_) | Out-Null }

# Build search path: exe directory + extra dirs
$exeDir = Split-Path (Resolve-Path $ExePath) -Parent
$searchPath = @($exeDir) + $SearchDirs

function Find-Dll([string]$name) {
    if ($systemDlls.Contains($name)) { return 'SYSTEM' }
    foreach ($dir in $searchPath) {
        $candidate = Join-Path $dir $name
        if (Test-Path $candidate) { return $candidate }
    }
    # Fall back to PATH
    $cmd = Get-Command $name -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    return $null
}

# Recursive dependency check (BFS, avoid revisiting)
$visited  = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::OrdinalIgnoreCase)
$queue    = [System.Collections.Generic.Queue[string]]::new()
$missing  = [System.Collections.Generic.List[string]]::new()

$queue.Enqueue((Resolve-Path $ExePath).Path)

while ($queue.Count -gt 0) {
    $current = $queue.Dequeue()
    if (-not $visited.Add($current)) { continue }

    $output = & $dumpbin /dependents $current 2>&1
    $deps = $output | Where-Object { $_ -match '^\s{4}\S+\.dll\s*$' } |
                      ForEach-Object { $_.Trim() }

    foreach ($dll in $deps) {
        if ($systemDlls.Contains($dll)) {
            Write-Host "[SYSTEM  ] $dll"
            continue
        }

        $found = Find-Dll $dll
        if ($found) {
            Write-Host "[OK      ] $dll  ->  $found"
            if ($found -ne 'SYSTEM') { $queue.Enqueue($found) }
        } else {
            Write-Warning "[MISSING ] $dll  (required by $(Split-Path $current -Leaf))"
            $missing.Add("$dll (required by $(Split-Path $current -Leaf))")
        }
    }
}

Write-Host ""
if ($missing.Count -gt 0) {
    Write-Host "FAILED: $($missing.Count) missing DLL(s):" -ForegroundColor Red
    $missing | ForEach-Object { Write-Host "  - $_" -ForegroundColor Red }
    exit 1
} else {
    Write-Host "PASSED: All DLL dependencies resolved." -ForegroundColor Green
    exit 0
}
