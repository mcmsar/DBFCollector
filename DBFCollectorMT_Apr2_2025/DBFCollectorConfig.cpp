#include "DBFCollectorConfig.h"
#include <windows.h>
#include <stdio.h>

// ---------------------------------------------------------------------------
// Singleton
// ---------------------------------------------------------------------------
CDBFCollectorConfig& CDBFCollectorConfig::GetInstance()
{
    static CDBFCollectorConfig instance;
    return instance;
}

CDBFCollectorConfig::CDBFCollectorConfig()
{
    SetDefaults();
}

// ---------------------------------------------------------------------------
// Compute the project root directory from the running exe's location.
// Exe is expected at <root>\DBFCollectorMT_Apr2_2025\<Config>\DBFCollector.exe
// (where <Config> is e.g. Debug or Release), so root = exe_dir 3 levels up.
// Returns the root with a trailing backslash.
// ---------------------------------------------------------------------------
static std::string ComputeProjectRoot()
{
    char szExe[MAX_PATH] = {0};
    GetModuleFileNameA(NULL, szExe, MAX_PATH);

    std::string s(szExe);
    // Strip exe filename
    std::string::size_type p = s.find_last_of("\\/");
    if (p != std::string::npos)
        s = s.substr(0, p);

    // Resolve <exe_dir>\..\..\..\  →  absolute project root
    char szRoot[MAX_PATH] = {0};
    GetFullPathNameA((s + "\\..\\..\\..").c_str(), MAX_PATH, szRoot, NULL);

    std::string root(szRoot);
    if (!root.empty() && root.back() != '\\')
        root += '\\';
    return root;
}

// ---------------------------------------------------------------------------
// Defaults are now computed relative to the exe location, so the project can
// be moved without editing source or config files.
// All generated/written paths live under Output\ so that source and output
// trees stay cleanly separated.
// ---------------------------------------------------------------------------
void CDBFCollectorConfig::SetDefaults()
{
    const std::string root   = ComputeProjectRoot();
    const std::string output = root + "Output\\";

    // Input / configuration
    m_sConfigDir         = root + "Config\\";
    m_sConstellationFile = root + "Config\\DBFConstellation.xml";
    m_sDataDrive         = "C:\\";

    // Pass/data output directories  →  Output\
    m_sPassDataDir   = output + "DBFPassData\\";
    m_sWavOutputDir  = output + "DBFPassData\\WAV\\";
    m_sBiasEigenDir  = output + "DBFPassData\\BiasEigen\\";
    m_sBiasSignalDir = output + "DBFPassData\\BiasSignal\\";
    m_sBinOutputDir  = output + "DBFPassData\\BIN\\";
    m_sSatIDDir      = output + "DBFPassData\\SatID\\";
    m_sRawDataDir    = output + "RawDataBin\\Galileo_2sec\\";
    m_sRawAltDir     = output + "Raw\\";
    m_sADCRawDir     = output + "ADCraw\\";

    // Calibration output  →  Output\Calibration\
    m_sCalibFilePrefix = output + "Calibration\\EMSDBF_Calib_";
    m_sCalibTraceDir   = output + "Calibration\\";

    // Covariance/eigen output  →  Output\DBFCovarianceFiles\
    m_sCovarianceDir   = output + "DBFCovarianceFiles\\";
    m_sEigenOutputFile = output + "DBFCovarianceFiles\\Output.csv";

    // Log output  →  Output\Logs\
    m_sLogFile         = output + "Logs\\logfile";
    m_sLogDir          = output + "Logs\\";
    m_sLogRedirectFile = output + "Logs\\logfile";
    m_sEMSDBFLogPrefix = output + "Logs\\EMSDBFlogger";
    m_sTimingLogFile   = output + "Logs\\dbf_timing_log.txt";
    m_sSunAzElFile     = output + "Logs\\SunAzEl.csv";
    m_sNullTestFile    = output + "Logs\\NullTest.csv";
}

// ---------------------------------------------------------------------------
// Creates a single directory and all missing parent directories.
// Silently succeeds if the directory already exists.
// ---------------------------------------------------------------------------
static void CreateDirRecursive(const std::string& path)
{
    if (path.empty())
        return;

    // Work on a copy with the trailing separator stripped so CreateDirectoryA
    // sees a plain directory name, not a path ending in '\\'.
    std::string p = path;
    while (!p.empty() && (p.back() == '\\' || p.back() == '/'))
        p.pop_back();

    if (p.empty())
        return;

    if (CreateDirectoryA(p.c_str(), NULL))
        return;   // created successfully

    DWORD err = GetLastError();
    if (err == ERROR_ALREADY_EXISTS)
        return;   // nothing to do

    if (err == ERROR_PATH_NOT_FOUND)
    {
        // Parent does not exist yet – create it recursively, then retry.
        std::string::size_type sep = p.find_last_of("\\/");
        if (sep != std::string::npos && sep > 0)
        {
            CreateDirRecursive(p.substr(0, sep));
            CreateDirectoryA(p.c_str(), NULL);
        }
    }
}

// Returns the directory portion of a file path (everything before the last
// separator).  Used so we can create parent dirs for file-path members.
static std::string DirOf(const std::string& filePath)
{
    std::string::size_type sep = filePath.find_last_of("\\/");
    return (sep != std::string::npos) ? filePath.substr(0, sep) : std::string();
}

// ---------------------------------------------------------------------------
// Creates every output directory that does not yet exist.
// Call once at startup after configuration has been loaded.
// ---------------------------------------------------------------------------
void CDBFCollectorConfig::EnsureOutputDirs() const
{
    // Explicit directory members
    CreateDirRecursive(m_sPassDataDir);
    CreateDirRecursive(m_sWavOutputDir);
    CreateDirRecursive(m_sBiasEigenDir);
    CreateDirRecursive(m_sBiasSignalDir);
    CreateDirRecursive(m_sBinOutputDir);
    CreateDirRecursive(m_sSatIDDir);
    CreateDirRecursive(m_sRawDataDir);
    CreateDirRecursive(m_sRawAltDir);
    CreateDirRecursive(m_sADCRawDir);
    CreateDirRecursive(m_sCalibTraceDir);
    CreateDirRecursive(m_sCovarianceDir);
    CreateDirRecursive(m_sLogDir);

    // File-path members: create their parent directory in case an XML override
    // pointed them at a directory not covered by the explicit dir members above.
    CreateDirRecursive(DirOf(m_sCalibFilePrefix));
    CreateDirRecursive(DirOf(m_sEigenOutputFile));
    CreateDirRecursive(DirOf(m_sLogFile));
    CreateDirRecursive(DirOf(m_sLogRedirectFile));
    CreateDirRecursive(DirOf(m_sEMSDBFLogPrefix));
    CreateDirRecursive(DirOf(m_sTimingLogFile));
    CreateDirRecursive(DirOf(m_sSunAzElFile));
    CreateDirRecursive(DirOf(m_sNullTestFile));
}

// ---------------------------------------------------------------------------
// Simple XML element extractor – sufficient for flat config structure.
// Returns the text content of the first <tag>...</tag> found, or "".
// ---------------------------------------------------------------------------
std::string CDBFCollectorConfig::ExtractTagValue(const std::string& xml,
                                                  const std::string& tag)
{
    std::string openTag  = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";

    std::string::size_type start = xml.find(openTag);
    if (start == std::string::npos)
        return "";
    start += openTag.size();

    std::string::size_type end = xml.find(closeTag, start);
    if (end == std::string::npos)
        return "";

    return xml.substr(start, end - start);
}

// ---------------------------------------------------------------------------
// Load configuration from an XML file.
// Returns true on success; any missing tag leaves its default intact.
// ---------------------------------------------------------------------------
bool CDBFCollectorConfig::LoadFromFile(const std::string& filePath)
{
    FILE* fp = fopen(filePath.c_str(), "r");
    if (!fp)
        return false;

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    if (fileSize <= 0)
    {
        fclose(fp);
        return false;
    }

    std::string xml(static_cast<size_t>(fileSize), '\0');
    size_t bytesRead = fread(&xml[0], 1, static_cast<size_t>(fileSize), fp);
    fclose(fp);
    xml.resize(bytesRead);

    // Derive {ROOT} from the config file path: root is the directory one level
    // above the directory containing this config file (i.e. parent of Config\).
    // Example: filePath = "D:\proj\Config\DBFCollectorConfig.xml"
    //          configDir = "D:\proj\Config"   root = "D:\proj\"
    std::string sRoot;
    {
        std::string fp2(filePath);
        // strip trailing separators from filePath before searching
        while (!fp2.empty() && (fp2.back() == '\\' || fp2.back() == '/'))
            fp2.pop_back();
        std::string::size_type sep1 = fp2.find_last_of("\\/");   // remove filename
        if (sep1 != std::string::npos)
        {
            std::string configDir = fp2.substr(0, sep1);
            std::string::size_type sep2 = configDir.find_last_of("\\/");  // parent of Config\
            if (sep2 != std::string::npos)
            {
                char szAbs[MAX_PATH] = {0};
                GetFullPathNameA(configDir.substr(0, sep2).c_str(), MAX_PATH, szAbs, NULL);
                sRoot = szAbs;
                if (!sRoot.empty() && sRoot.back() != '\\')
                    sRoot += '\\';
            }
        }
    }

    // Expand {ROOT} token in the raw XML text so paths in the file are portable.
    if (!sRoot.empty())
    {
        const std::string token = "{ROOT}\\";
        std::string::size_type pos = 0;
        while ((pos = xml.find(token, pos)) != std::string::npos)
        {
            xml.replace(pos, token.size(), sRoot);
            pos += sRoot.size();
        }
        // Also handle {ROOT} without trailing backslash (e.g. before a forward slash)
        const std::string token2 = "{ROOT}";
        pos = 0;
        while ((pos = xml.find(token2, pos)) != std::string::npos)
        {
            xml.replace(pos, token2.size(), sRoot);
            pos += sRoot.size();
        }
    }

    // Apply each value only when the tag is present in the file
#define LOAD_PATH(tag, member) \
    { \
        std::string _v = ExtractTagValue(xml, tag); \
        if (!_v.empty()) member = _v; \
    }

    LOAD_PATH("ConfigDir",        m_sConfigDir)
    LOAD_PATH("PassDataDir",      m_sPassDataDir)
    LOAD_PATH("WavOutputDir",     m_sWavOutputDir)
    LOAD_PATH("BiasEigenDir",     m_sBiasEigenDir)
    LOAD_PATH("BiasSignalDir",    m_sBiasSignalDir)
    LOAD_PATH("BinOutputDir",     m_sBinOutputDir)
    LOAD_PATH("SatIDDir",         m_sSatIDDir)
    LOAD_PATH("RawDataDir",       m_sRawDataDir)
    LOAD_PATH("RawAltDir",        m_sRawAltDir)
    LOAD_PATH("ADCRawDir",        m_sADCRawDir)
    LOAD_PATH("CalibFilePrefix",  m_sCalibFilePrefix)
    LOAD_PATH("CalibTraceDir",    m_sCalibTraceDir)
    LOAD_PATH("CovarianceDir",    m_sCovarianceDir)
    LOAD_PATH("EigenOutputFile",  m_sEigenOutputFile)
    LOAD_PATH("ConstellationFile",m_sConstellationFile)
    LOAD_PATH("LogFile",          m_sLogFile)
    LOAD_PATH("LogDir",           m_sLogDir)
    LOAD_PATH("LogRedirectFile",  m_sLogRedirectFile)
    LOAD_PATH("EMSDBFLogPrefix",  m_sEMSDBFLogPrefix)
    LOAD_PATH("TimingLogFile",    m_sTimingLogFile)
    LOAD_PATH("SunAzElFile",      m_sSunAzElFile)
    LOAD_PATH("NullTestFile",     m_sNullTestFile)
    LOAD_PATH("DataDrive",        m_sDataDrive)

#undef LOAD_PATH

    return true;
}

// ---------------------------------------------------------------------------
// Wide-string helpers
// ---------------------------------------------------------------------------
std::wstring CDBFCollectorConfig::NarrowToWide(const std::string& s)
{
    if (s.empty())
        return std::wstring();
    int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, 0);
    if (len <= 1)
        return std::wstring();
    std::wstring result(static_cast<size_t>(len - 1), L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, &result[0], len);
    return result;
}

std::wstring CDBFCollectorConfig::GetConfigDirW() const
{
    return NarrowToWide(m_sConfigDir);
}

std::wstring CDBFCollectorConfig::GetPassDataDirW() const
{
    return NarrowToWide(m_sPassDataDir);
}
