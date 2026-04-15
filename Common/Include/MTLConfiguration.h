//! @file MTLConfiguration.h
//! Header file for the CEMSMTLConfiguration class.

#ifndef __MTL_CONFIGURATION_H__
#define __MTL_CONFIGURATION_H__

#include "aobjbase.h"
#include "emssit.h"
#include "igateway.h"
#include <string>
#include <map>
#include "routeendconfig.h"
#include "routeconfig.h"
#include "criticalsection.h"

typedef enum eServerType
{
	SERVTYPE_UNKNOWN = 0,
	SERVTYPE_LUT_SERVER = 1,
	SERVTYPE_LUT = 2
} EMSSERVERTYPE;

const long MAX_SIT_MSG_LINE_LENGTH = 68;

const unsigned long MAX_LUT_ID_VALUE = 9999;

class CEMSRouteConfig;
interface IEMSConfigurationManager;
class CEMSProcessConfig;
class CEMSLutConfig;
class CEMSSTTConfig;

//! @class CEMSMTLConfiguration
//! This class is used to access configuration data specific to the MTL.
class CEMSMTLConfiguration : public CApiObjBase
{
	public:

		static CEMSMTLConfiguration* GetMTLConfigInstance();

		//! @fn void RefreshCache()
		//! When called, this method deletes all cached data, forcing subsequent requests for config data
		//! to go to the configuration manager for data.
		void RefreshCache();

		//! @fn void GetSITOutgoingDir( wchar_t*& wszOuputDir )
		//! @brief Get the output directory for SIT messages.
		void GetSITOutgoingDir( wchar_t*& wszOuputDir );

		//! @fn void GetSITUndeliveredDir( wchar_t*& wszUndeliveredDir )
		//! @brief Get the "undelivered" directory for SIT messages.
		void GetSITUndeliveredDir( wchar_t*& wszUndeliveredDir );

		//! @fn void GetShortName( unsigned long ulLutID, wchar_t*& wszShortName )
		//! Get the short name for the specified LUT Identifier
		void GetShortName( unsigned long ulLutID, wchar_t*& wszShortName );
		
		//! @fn long GetNextOutSequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName )
		//! Get the message sequence number for the next outgoing SIT message and increment it.
		//! It is assumed that this is a single point of access this configuration value.  Otherwise, 
		//! updates of this value will not be synchronized.
		long GetNextOutSequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName );
		
		//! @fn long GetNextOutBinarySequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName )
		//! Get the message sequence number for the next outgoing binary message and intrement it.
		//! It is assumed that this is a single point of access this configuration value.  Otherwise, 
		//! updates of this value will not be synchronized.
		long GetNextOutBinarySequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName );

		unsigned long GetMaxAlertsPerMessage( const unsigned long culFromID, const unsigned long culDestID );

		//! @fn unsigned long GetMaxCmdLineLen()
		//! Get the configured value for the maximum allowable length of a line in a SIT
		//! "Send Data" command message.
		unsigned long GetMaxCmdLineLen() { return MAX_SIT_MSG_LINE_LENGTH; }

		//! @fn wchar_t* GetSoapEndPoint( unsigned long ulFromID, unsigned long ulToID )
		//! Retrieve the SOAP endpoint for a particular Route.
		wchar_t* GetSoapEndPoint( unsigned long ulFromID, unsigned long ulToID );

		//! @fn wchar_t* GetProcessingDir()
		//! Get the local directory where files ready for processing should be placed.
		wchar_t* GetProcessingDir();

		//! @fn wchar_t* GetProcessedBinaryDir()
		//! Get thre directory where processed binary files should be placed.
		wchar_t* GetProcessedBinaryDir();

		//! @fn bool GetShuntToGateway()
		//! Determine whether the system is configured to have SIT messages pass through the Gateway.
		bool GetShuntToGateway();

		unsigned long GetThisLutID();

		int GetSOAPPort();

		int GetSOAPBackLogSize();

		long GetNumSOAPHandlerThreads();

		EMSLOCATION GetSiteLocation( const unsigned long culSiteID );

		void GetRouteConfigs( const unsigned long culFromID, const unsigned long culToID,
								unsigned long& ulRoutes, CEMSRouteConfig**& apRouteConfig );

		void GetOutRouteEnds( const unsigned long culFromID, unsigned long& ulRouteEnds, 
								CEMSRouteEndConfig**& apOutRouteEnds );

		void GetOutRouteConfigs( const unsigned long culFromID, unsigned long& ulRoutes, 
								CEMSRouteConfig**& apRoutes );

		void GetOutRouteEnd( const unsigned long culFromID, const unsigned long culToID, 
										CEMSRouteEndConfig*& pRouteOut );

		CEMSSTTConfig* GetTranslationTable( const wchar_t* cwszTableName ) { return _GetTranslationTable( cwszTableName ); }

		CEMSRouteConfig* GetRouteConfig( const wchar_t* cwszFromAlias, const wchar_t* cwszToAlias );

		CEMSRouteConfig* GetRouteConfig( const unsigned long culRouteID );

		std::wstring GetTranslation( const wchar_t* cwszTableName, const wchar_t* cwszSITCode );

	protected:
		//! @fn CEMSMTLConfiguration()
		//! @brief Default Constructor.
		CEMSMTLConfiguration();

		//! @fn CEMSMTLConfiguration( const CEMSMTLConfiguration& mtlConfig )
		//! @brief Copy Constructor.
		CEMSMTLConfiguration( const CEMSMTLConfiguration& mtlConfig );		

		//! @fn virtual ~CEMSMTLConfiguration()
		//! @brief Destructor.
		virtual ~CEMSMTLConfiguration();
	
	private:	// methods

		IEMSConfigurationManager* _GetConfigManager();
		
		void _ClearConfig();

		CEMSProcessConfig* _GetProcess();

		CEMSLutConfig* _GetLut( const unsigned long culID );

		CEMSLutConfig* _GetLutFromCM( const unsigned long culID );

		CEMSSTTConfig* _GetTranslationTable( const wchar_t* cwszTable );

		CEMSSTTConfig* _GetTransTableFromCM( const wchar_t* cwszTable );

		void _LoadRoutes();

		bool _IsRouteEnabled( const int iConfigItems, EMSCONFIGURATIONITEM** apConfigItems );

	private:	// data
		IEMSConfigurationManager*					m_pConfigMgr;
		CEMSCriticalSection							m_csMgr;

		CEMSProcessConfig*							m_pProcessCfg;
		CEMSCriticalSection							m_csProcess;

		CEMSCriticalSection							m_csOutSequence;

		std::map<std::wstring,CEMSRouteConfig*>		m_mapRoutes;
		CEMSCriticalSection							m_csRoutes;

		std::map<unsigned long, CEMSLutConfig*>		m_mapLuts;
		CEMSCriticalSection							m_csLuts;

		static CEMSMTLConfiguration*				ms_pMTLConfig;
		static CEMSCriticalSection					ms_csConfigMgr;

		std::map<std::wstring,CEMSSTTConfig*>		m_mapTransTables;
		CEMSCriticalSection							m_csTransTables;

		std::multimap<std::wstring,CEMSRouteConfig*>	m_multimapRoutes;
		CEMSCriticalSection								m_csAllRoutes;
		bool											m_bRoutesInitialized;

		class CEMSInBoundLookupKey
		{
			public:
				CEMSInBoundLookupKey() {}
				~CEMSInBoundLookupKey() {}

				CEMSInBoundLookupKey( const wchar_t* wszFromName, const wchar_t* wszToName ) 
				{ 
					m_wszFromName = wszFromName; 
					m_wszToName = wszToName; 
				}

				CEMSInBoundLookupKey( const CEMSInBoundLookupKey& x )
				{
					m_wszFromName = x.m_wszFromName;
					m_wszToName = x.m_wszToName;

				}

				CEMSInBoundLookupKey& operator=( const CEMSInBoundLookupKey& rhs )
				{
					m_wszFromName = rhs.m_wszFromName;
					m_wszToName = rhs.m_wszToName;

					return *this;
				}

				bool operator<( const CEMSInBoundLookupKey& rhs) const
				{
					bool bRet = false;

					if( wcscmp( m_wszFromName.c_str(), rhs.m_wszFromName.c_str() ) < 0  )
					{
						if( wcscmp( m_wszToName.c_str(), rhs.m_wszToName.c_str() ) < 0 )
						{
							bRet = true;
						}
					}

					return bRet;
				}

			private:
				std::wstring m_wszFromName;
				std::wstring m_wszToName;
		};

		typedef CEMSInBoundLookupKey INBOUNDLOOKUPKEY;
		typedef std::map<INBOUNDLOOKUPKEY, CEMSRouteConfig*, std::less<INBOUNDLOOKUPKEY> > INBOUNDLOOKUPTABLE;

		INBOUNDLOOKUPTABLE		m_mapInboundLookupTable;
		CEMSCriticalSection		m_csInLookup;

		typedef std::map<std::wstring, std::wstring > TRANSLATIONTABLE;
		typedef std::map<std::wstring,TRANSLATIONTABLE > TABLEOFTRANSLATIONTABLES;
		TABLEOFTRANSLATIONTABLES m_mapTranslationTables;
		CEMSCriticalSection		m_csTranslationTables;
};


#endif // __MTL_CONFIGURATION_H__