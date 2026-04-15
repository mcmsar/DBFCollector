/*********************************************************************
* Stub implementations for EMSConfigClientCPP classes.
* These satisfy linker requirements for symbols missing from the
* pre-built EMSConfigClientCPP.lib (2021 version).
*
* MEOSystemClient stubs return NULL/empty so callers fall back to
* their own defaults (e.g. hardcoded leap-second value in emsgpsconvert).
********************************************************************/

#include "UserConfigCL.h"
#include "FolderConfigCL.h"
#include "FPorbConfigCL.h"
#include "WebServiceConfigCL.h"
#include "WinServiceConfig.h"
#include "ClocksConfig.h"
#include "DataManagerConfig.h"
#include "meoconfigclient.h"
#include "meosysclient.h"

// ----------------------------------------------------------------------------
// UserConfig
// ----------------------------------------------------------------------------

UserConfig::UserConfig()
{
}

UserConfig::UserConfig( const string& rszName, const string& rszPassword )
    : m_szName(rszName), m_szPassword(rszPassword)
{
}

UserConfig::UserConfig( const UserConfig& x )
    : m_szName(x.m_szName), m_szPassword(x.m_szPassword)
{
}

UserConfig::~UserConfig()
{
}

// ----------------------------------------------------------------------------
// FolderConfig
// ----------------------------------------------------------------------------

FolderConfig::FolderConfig()
{
}

FolderConfig::FolderConfig( const string& rszFolderData, const string& rszFolderIndex,
                             const string& rszFolderPath )
    : m_szFolderData(rszFolderData), m_szFolderIndex(rszFolderIndex),
      m_szFolderPath(rszFolderPath)
{
}

FolderConfig::FolderConfig( const FolderConfig& x )
    : m_szFolderData(x.m_szFolderData), m_szFolderIndex(x.m_szFolderIndex),
      m_szFolderPath(x.m_szFolderPath)
{
}

FolderConfig::~FolderConfig()
{
}

// ----------------------------------------------------------------------------
// FPorbConfig
// ----------------------------------------------------------------------------

FPorbConfig::FPorbConfig()
{
}

FPorbConfig::FPorbConfig( const string& rszFPorbURL, const UserConfig rszFPorbUser )
    : m_szFPorbURL(rszFPorbURL), m_szFPorbUser(rszFPorbUser)
{
}

FPorbConfig::FPorbConfig( const FPorbConfig& x )
    : m_szFPorbURL(x.m_szFPorbURL), m_szFPorbUser(x.m_szFPorbUser)
{
}

FPorbConfig::~FPorbConfig()
{
}

// ----------------------------------------------------------------------------
// WebServiceConfig
// ----------------------------------------------------------------------------

WebServiceConfig::WebServiceConfig()
    : m_lWSBacklog(0), m_bWSAuthenticate(false), m_bWS_use_ssl(false)
{
}

WebServiceConfig::WebServiceConfig( const string& rszWSHost, const string& rszWSPortID,
    const long rlWSBacklog, const bool rbWSAuthenticate, const string& rszWSUsersFile,
    const string& rszWS_ssl_keyfile, const string& rszWS_ssl_cafile,
    const string& rszWS_ssl_password, const bool rbWS_use_ssl,
    const string& rszWS_classid, const string& rszWSname )
    : m_szWSHost(rszWSHost), m_szWSPortID(rszWSPortID), m_lWSBacklog(rlWSBacklog),
      m_bWSAuthenticate(rbWSAuthenticate), m_szWSUsersFile(rszWSUsersFile),
      m_szWS_ssl_keyfile(rszWS_ssl_keyfile), m_szWS_ssl_cafile(rszWS_ssl_cafile),
      m_szWS_ssl_password(rszWS_ssl_password), m_bWS_use_ssl(rbWS_use_ssl),
      m_szWS_classid(rszWS_classid), m_szWSname(rszWSname)
{
}

WebServiceConfig::WebServiceConfig( const WebServiceConfig& x )
    : m_szWSHost(x.m_szWSHost), m_szWSPortID(x.m_szWSPortID),
      m_lWSBacklog(x.m_lWSBacklog), m_bWSAuthenticate(x.m_bWSAuthenticate),
      m_szWSUsersFile(x.m_szWSUsersFile), m_szWS_ssl_keyfile(x.m_szWS_ssl_keyfile),
      m_szWS_ssl_cafile(x.m_szWS_ssl_cafile), m_szWS_ssl_password(x.m_szWS_ssl_password),
      m_bWS_use_ssl(x.m_bWS_use_ssl), m_szWS_classid(x.m_szWS_classid),
      m_szWSname(x.m_szWSname)
{
}

WebServiceConfig::~WebServiceConfig()
{
}

// ----------------------------------------------------------------------------
// WinServiceConfig
// ----------------------------------------------------------------------------

WinServiceConfig::WinServiceConfig()
    : m_iPiriority(0)
{
}

WinServiceConfig::WinServiceConfig( const WinServiceConfig& x )
    : m_szID(x.m_szID), m_szName(x.m_szName),
      m_szRestart(x.m_szRestart), m_iPiriority(x.m_iPiriority)
{
}

WinServiceConfig::~WinServiceConfig()
{
}

bool WinServiceConfig::IsRestart()
{
    return (m_szRestart == "true");
}

// ----------------------------------------------------------------------------
// WinServicesConfig
// ----------------------------------------------------------------------------

WinServicesConfig::WinServicesConfig()
    : m_fCheckPeriod(0.0f)
{
}

WinServicesConfig::WinServicesConfig( const WinServicesConfig& x )
    : m_szID(x.m_szID), m_fCheckPeriod(x.m_fCheckPeriod),
      m_szVersion(x.m_szVersion), m_lstWinServices(x.m_lstWinServices)
{
}

WinServicesConfig::~WinServicesConfig()
{
}

bool WinServicesConfig::GetSericeById( const string& cszServID, WinServiceConfig& roWinSrvConfg )
{
    return false;
}

// ----------------------------------------------------------------------------
// EMSClocksConfig
// ----------------------------------------------------------------------------

EMSClocksConfig::EMSClocksConfig()
    : m_dTimeZoneBias(0.0), m_dCheckTime(0.0),
      m_dCheckEphemeris(0.0), m_iLeapSeconds(0)
{
}

EMSClocksConfig::EMSClocksConfig( const EMSClocksConfig& x )
    : m_szID(x.m_szID), m_dTimeZoneBias(x.m_dTimeZoneBias),
      m_dCheckTime(x.m_dCheckTime), m_dCheckEphemeris(x.m_dCheckEphemeris),
      m_iLeapSeconds(x.m_iLeapSeconds)
{
}

EMSClocksConfig::~EMSClocksConfig()
{
}

// ----------------------------------------------------------------------------
// DataManagerConfig
// ----------------------------------------------------------------------------

DataManagerConfig::DataManagerConfig()
    : m_ulCheckPeriod(0), m_ulMinFreeDeskSpace(0)
{
}

DataManagerConfig::DataManagerConfig( const DataManagerConfig& x )
    : m_szID(x.m_szID), m_ulCheckPeriod(x.m_ulCheckPeriod),
      m_szDBDrive(x.m_szDBDrive), m_szDBName(x.m_szDBName),
      m_szDirPath(x.m_szDirPath), m_ulMinFreeDeskSpace(x.m_ulMinFreeDeskSpace),
      m_lstDataSource(x.m_lstDataSource)
{
}

DataManagerConfig::~DataManagerConfig()
{
}

// ----------------------------------------------------------------------------
// MEOConfigClient
// ----------------------------------------------------------------------------

MEOConfigClient::MEOConfigClient()
    : m_iPortNum(0)
{
}

MEOConfigClient::MEOConfigClient( const std::string& hostName, const int ciPortNum )
    : m_HostName(hostName), m_iPortNum(ciPortNum)
{
}

MEOConfigClient::MEOConfigClient( const MEOConfigClient& x )
    : m_HostName(x.m_HostName), m_iPortNum(x.m_iPortNum)
{
}

MEOConfigClient::~MEOConfigClient()
{
}

std::string MEOConfigClient::DoGetRequest( const std::string& url,
                                           std::map<std::string,std::string> paramList )
{
    return "";
}

// ----------------------------------------------------------------------------
// MEOSystemClient
// All query methods return NULL; callers already guard against NULL returns.
// ----------------------------------------------------------------------------

MEOSystemClient::MEOSystemClient()
{
}

MEOSystemClient::MEOSystemClient( const string& hostName, const int ciPortNum )
    : MEOConfigClient(hostName, ciPortNum)
{
}

MEOSystemClient::MEOSystemClient( const MEOSystemClient& x )
    : MEOConfigClient(x)
{
}

MEOSystemClient::~MEOSystemClient()
{
}

EMSClocksConfig* MEOSystemClient::getClocksConfig()
{
    return NULL;
}

LPConfig* MEOSystemClient::getLPById( const string& id )
{
    return NULL;
}

MEOLUTConfig* MEOSystemClient::getMEOLUTConfig()
{
    return NULL;
}

FPConfig* MEOSystemClient::getFPById( const string& id )
{
    return NULL;
}

SPConfig* MEOSystemClient::getSPById( const string& id )
{
    return NULL;
}

SPParamsConfig* MEOSystemClient::getSPParamsById( const string& id )
{
    return NULL;
}

LPParamsConfig* MEOSystemClient::getLPParamsById( const string& id )
{
    return NULL;
}

LPParamsConfig* MEOSystemClient::getLPParamsByLPId( const string& id )
{
    return NULL;
}

list<EMSClocksConfig*> MEOSystemClient::getAllClocksConfig()
{
    return list<EMSClocksConfig*>();
}

string MEOSystemClient::getDataManagerIDBySubsystemID( const string& id )
{
    return "";
}

string MEOSystemClient::getServicesIDBySubsystemID( const string& id )
{
    return "";
}

DataManagerConfig* MEOSystemClient::getDataManagerById( const string& id )
{
    return NULL;
}

WinServicesConfig* MEOSystemClient::getWinServicesById( const string& id )
{
    return NULL;
}

LUTConfig* MEOSystemClient::getLUTById( const string& id )
{
    return NULL;
}

list<LUTConfig*> MEOSystemClient::getAllLUTs()
{
    return list<LUTConfig*>();
}

MEO_SUBSYSTEM_TYPE MEOSystemClient::getSubSystemType( const string& id )
{
    return MEO_SUBSYSTEM_TYPE_UNKNOWN;
}

void MEOSystemClient::getCollectorOutputXMLByFpId( const string& rszFpId,
                                                    char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getDCPluginsXMLByFpId( const string& rszFpId,
                                              char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getDCWebServicesByFpId( const string& rszFpId,
                                               char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getFPWebServicesByFpId( const string& rszFpId,
                                               char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getFPPairsByFpId( const string& rszFpId,
                                         char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getFPDataStreamsByFpId( const string& rszFpId,
                                               char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

void MEOSystemClient::getLPUrlRecvWWByLpId( const string& rszFpId,
                                             char* szXml, const unsigned long ulMaxSize )
{
    if( szXml && ulMaxSize > 0 ) szXml[0] = '\0';
}

string MEOSystemClient::getTrackingMode( const string& meoLutCfgStr )
{
    return "";
}

string MEOSystemClient::getRedundancyMode( const string& meoLutCfgStr )
{
    return "";
}

void MEOSystemClient::ClearLUTConfigList( list<MEOLUTConfig*>& lstLUTConfig )
{
    lstLUTConfig.clear();
}
