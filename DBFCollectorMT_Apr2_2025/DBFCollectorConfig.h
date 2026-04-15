#ifndef __DBF_COLLECTOR_CONFIG_H__
#define __DBF_COLLECTOR_CONFIG_H__

#include <string>

// Singleton that holds all runtime-configurable file paths.
// Loaded from Config\DBFCollectorConfig.xml at startup.
// If the file is absent or a tag is missing, built-in defaults apply.
//
// Usage:
//   CDBFCollectorConfig::GetInstance().LoadFromFile(path); // once at startup
//   CDBFCollectorConfig::GetInstance().GetPassDataDir();   // anywhere
class CDBFCollectorConfig
{
public:
    static CDBFCollectorConfig& GetInstance();

    // Load settings from an XML file. Returns true on success.
    // Any tag that is absent leaves the corresponding default unchanged.
    bool LoadFromFile(const std::string& filePath);

    // --- Pass/data directories ---
    const std::string& GetConfigDir()     const { return m_sConfigDir; }
    const std::string& GetPassDataDir()   const { return m_sPassDataDir; }
    const std::string& GetWavOutputDir()  const { return m_sWavOutputDir; }
    const std::string& GetBiasEigenDir()  const { return m_sBiasEigenDir; }
    const std::string& GetBiasSignalDir() const { return m_sBiasSignalDir; }
    const std::string& GetBinOutputDir()  const { return m_sBinOutputDir; }
    const std::string& GetSatIDDir()      const { return m_sSatIDDir; }
    const std::string& GetRawDataDir()    const { return m_sRawDataDir; }
    const std::string& GetRawAltDir()     const { return m_sRawAltDir; }
    const std::string& GetADCRawDir()     const { return m_sADCRawDir; }

    // --- Calibration ---
    const std::string& GetCalibFilePrefix() const { return m_sCalibFilePrefix; }
    const std::string& GetCalibTraceDir()   const { return m_sCalibTraceDir; }

    // --- Covariance/eigen ---
    const std::string& GetCovarianceDir()   const { return m_sCovarianceDir; }
    const std::string& GetEigenOutputFile() const { return m_sEigenOutputFile; }

    // --- Constellation ---
    const std::string& GetConstellationFile() const { return m_sConstellationFile; }

    // --- Logging ---
    const std::string& GetLogFile()          const { return m_sLogFile; }
    const std::string& GetLogDir()           const { return m_sLogDir; }
    const std::string& GetLogRedirectFile()  const { return m_sLogRedirectFile; }
    const std::string& GetEMSDBFLogPrefix()  const { return m_sEMSDBFLogPrefix; }
    const std::string& GetTimingLogFile()    const { return m_sTimingLogFile; }

    // --- Miscellaneous ---
    const std::string& GetSunAzElFile()  const { return m_sSunAzElFile; }
    const std::string& GetNullTestFile() const { return m_sNullTestFile; }
    const std::string& GetDataDrive()    const { return m_sDataDrive; }

    // Wide-string accessors for APIs that require wchar_t*
    std::wstring GetConfigDirW()   const;
    std::wstring GetPassDataDirW() const;

    // Creates all output directories that do not yet exist.
    // Call once after LoadFromFile() (or at startup when using defaults).
    void EnsureOutputDirs() const;

private:
    CDBFCollectorConfig();
    ~CDBFCollectorConfig() {}
    CDBFCollectorConfig(const CDBFCollectorConfig&);
    CDBFCollectorConfig& operator=(const CDBFCollectorConfig&);

    void SetDefaults();
    static std::string  ExtractTagValue(const std::string& xml, const std::string& tag);
    static std::wstring NarrowToWide(const std::string& s);

    std::string m_sConfigDir;
    std::string m_sPassDataDir;
    std::string m_sWavOutputDir;
    std::string m_sBiasEigenDir;
    std::string m_sBiasSignalDir;
    std::string m_sBinOutputDir;
    std::string m_sSatIDDir;
    std::string m_sRawDataDir;
    std::string m_sRawAltDir;
    std::string m_sADCRawDir;
    std::string m_sCalibFilePrefix;
    std::string m_sCalibTraceDir;
    std::string m_sCovarianceDir;
    std::string m_sEigenOutputFile;
    std::string m_sConstellationFile;
    std::string m_sLogFile;
    std::string m_sLogDir;
    std::string m_sLogRedirectFile;
    std::string m_sEMSDBFLogPrefix;
    std::string m_sTimingLogFile;
    std::string m_sSunAzElFile;
    std::string m_sNullTestFile;
    std::string m_sDataDrive;
};

#endif // __DBF_COLLECTOR_CONFIG_H__
