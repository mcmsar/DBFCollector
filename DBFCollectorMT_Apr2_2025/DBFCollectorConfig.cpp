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
// Defaults match previously hardcoded values throughout the project.
// All generated/written paths now live under Output\ so that source and
// output trees stay cleanly separated.
// ---------------------------------------------------------------------------
void CDBFCollectorConfig::SetDefaults()
{
#define DBF_ROOT   "C:\\Users\\joshua.rehm\\DBFCollectorMT_03_26_26\\"
#define DBF_OUTPUT DBF_ROOT "Output\\"

    // Input / configuration (unchanged location)
    m_sConfigDir         = DBF_ROOT "Config\\";
    m_sConstellationFile = DBF_ROOT "Config\\DBFConstellation.xml";
    m_sDataDrive         = "C:\\";

    // Pass/data output directories  →  Output\
    m_sPassDataDir   = DBF_OUTPUT "DBFPassData\\";
    m_sWavOutputDir  = DBF_OUTPUT "DBFPassData\\WAV\\";
    m_sBiasEigenDir  = DBF_OUTPUT "DBFPassData\\BiasEigen\\";
    m_sBiasSignalDir = DBF_OUTPUT "DBFPassData\\BiasSignal\\";
    m_sBinOutputDir  = DBF_OUTPUT "DBFPassData\\BIN\\";
    m_sSatIDDir      = DBF_OUTPUT "DBFPassData\\SatID\\";
    m_sRawDataDir    = DBF_OUTPUT "RawDataBin\\Galileo_2sec\\";
    m_sRawAltDir     = DBF_OUTPUT "Raw\\";
    m_sADCRawDir     = DBF_OUTPUT "ADCraw\\";

    // Calibration output  →  Output\Calibration\
    m_sCalibFilePrefix = DBF_OUTPUT "Calibration\\EMSDBF_Calib_";
    m_sCalibTraceDir   = DBF_OUTPUT "Calibration\\";

    // Covariance/eigen output  →  Output\DBFCovarianceFiles\
    m_sCovarianceDir   = DBF_OUTPUT "DBFCovarianceFiles\\";
    m_sEigenOutputFile = DBF_OUTPUT "DBFCovarianceFiles\\Output.csv";

    // Log output  →  Output\Logs\
    m_sLogFile         = DBF_OUTPUT "Logs\\logfile";
    m_sLogDir          = DBF_OUTPUT "Logs\\";
    m_sLogRedirectFile = DBF_OUTPUT "Logs\\logfile";
    m_sEMSDBFLogPrefix = DBF_OUTPUT "Logs\\EMSDBFlogger";
    m_sTimingLogFile   = DBF_OUTPUT "Logs\\dbf_timing_log.txt";
    m_sSunAzElFile     = DBF_OUTPUT "Logs\\SunAzEl.csv";
    m_sNullTestFile    = DBF_OUTPUT "Logs\\NullTest.csv";

#undef DBF_OUTPUT
#undef DBF_ROOT
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
