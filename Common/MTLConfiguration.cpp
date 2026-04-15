#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length
#pragma warning(disable:4503)

// Note that the C4503 warnings cannot be disabled due to a bug in
// Visual C++ (fixed in .NET version).  See KB article on MSDN: Q167355.

#include "mtlconfiguration.h"
#include "routeconfig.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "logmsgparam.h"
#include "convutility.h"
#include "iconfigmanager.h"
#include "mtlmsgs.h"
#include "routeconfigconstants.h"
#include "processconfig.h"
#include "lutconfig.h"
#include "sittranstableconfig.h"
#include <list>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "sittranstableconstants.h"

CEMSMTLConfiguration* CEMSMTLConfiguration::ms_pMTLConfig = 0;
CEMSCriticalSection CEMSMTLConfiguration::ms_csConfigMgr;

CEMSMTLConfiguration::CEMSMTLConfiguration() :m_pConfigMgr(0),  m_pProcessCfg(0), m_bRoutesInitialized(false)
{
}

CEMSMTLConfiguration::CEMSMTLConfiguration( const CEMSMTLConfiguration& x )
{
	m_bRoutesInitialized = x.m_bRoutesInitialized;
}

CEMSMTLConfiguration::~CEMSMTLConfiguration()
{
	if( m_pConfigMgr )
		m_pConfigMgr->Release();
	m_pConfigMgr = 0;

	_ClearConfig();
}

CEMSMTLConfiguration*
CEMSMTLConfiguration::GetMTLConfigInstance()
{
	CEMSMTLConfiguration* pRet = 0;

	try
	{
		ms_csConfigMgr.Enter();

		if( !ms_pMTLConfig )
		{
			ms_pMTLConfig = new CEMSMTLConfiguration;

			if( !ms_pMTLConfig )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		}

		pRet = ms_pMTLConfig;
		pRet->AddRef();

		ms_csConfigMgr.Leave();
	}
	catch( ... )
	{
		ms_csConfigMgr.Leave();

		throw;
	}

	return pRet;
}

void 
CEMSMTLConfiguration::RefreshCache()
{
	_ClearConfig();
}

void 
CEMSMTLConfiguration::GetSITOutgoingDir( wchar_t*& wszOuputDir )
{
	CEMSProcessConfig* pProcConfig = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wszOuputDir = pProcConfig->GetSITOutDirectory();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}
}

void 
CEMSMTLConfiguration::GetSITUndeliveredDir( wchar_t*& wszUndeliveredDir )
{
	CEMSProcessConfig* pProcConfig = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wszUndeliveredDir = pProcConfig->GetSITUndeliveredDirectory();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}
}

void 
CEMSMTLConfiguration::GetShortName( unsigned long ulLutID, wchar_t*& wszShortName )
{
	CEMSLutConfig* pLutConfig = 0;

	try
	{
		pLutConfig = _GetLut( ulLutID );

		if( !pLutConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wszShortName = pLutConfig->GetShortName();

		pLutConfig->Release();
		pLutConfig = 0;

	}
	catch( ... )
	{
		if( pLutConfig )
		{
			pLutConfig->Release();
			pLutConfig = 0;
		}

		throw;
	}
}

long
CEMSMTLConfiguration::GetNextOutSequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName )
{
	long lRet = 0;

	// This is not cached data since it is updated.
	m_csOutSequence.Enter();

	IEMSConfigurationManager* pConfig = 0;

	try
	{
		pConfig = _GetConfigManager();

		if( !pConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wstring wszGroupID = cwszRouteName;

		EMSVARITYPE varEndID;
		memset( &varEndID, 0, sizeof(EMSVARITYPE) );

		EMS_RESULT hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1Identifier, &varEndID );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		EMSVARITYPE varMsgNumber;
		memset( &varMsgNumber, 0, sizeof(EMSVARITYPE) );

		bool bEnd1 = true;
		// Is it the from ID?
		if( varEndID.iVal == culFromID )
		{
			// Get the End1 sequence number.
			hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1OutMsgNumber, &varMsgNumber );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}
		}
		else
		{
			// Check if it's end 2.
			memset( &varEndID, 0, sizeof(EMSVARITYPE) );
			hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2Identifier, &varEndID );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

			if( varEndID.iVal == culFromID )
			{
				// Get the End2 sequence number.
				hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2OutMsgNumber, &varMsgNumber );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				bEnd1 = false;
			}
			else
			{
				CEMSLogMsgParam logMsgParam;
#if defined(UNICODE) || defined(_UNICODE)
				logMsgParam += cwszRouteGroup;
				logMsgParam += cwszRouteGroup;
				logMsgParam += cwszEnd1OutMsgNumber;
				logMsgParam += cwszEnd2OutMsgNumber;
#else
				logMsgParam += CEMSConversionUtil::ConvertToString( cwszRouteGroup ).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszRouteGroup).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszEnd1OutMsgNumber).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszEnd2OutMsgNumber).c_str();
#endif
				
				throw CEMSException( EMS_MTL_CONFIG_TWO_KEYS, logMsgParam );
			}
		}

		lRet = varMsgNumber.iVal;

		if( varMsgNumber.iVal >= clMaxMsgSequenceNumber )
			varMsgNumber.iVal = clMinMsgSequenceNumber;
		else
			varMsgNumber.iVal++;

		if( bEnd1 )
		{
			hr = pConfig->Set( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1OutMsgNumber, varMsgNumber );
		}
		else
		{
			hr = pConfig->Set( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2OutMsgNumber, varMsgNumber );
		}

		pConfig->Release();
		pConfig = 0;

	}
	catch( ... )
	{
		if( pConfig )
			pConfig->Release();
		pConfig = 0;

		m_csOutSequence.Leave();

		throw;
	}

	m_csOutSequence.Leave();

	return lRet;
}

long
CEMSMTLConfiguration::GetNextOutBinarySequenceNumber( const unsigned long culFromID, const wchar_t* cwszRouteName )
{
	long lRet = 0;

	// This is not cached data since it is updated.
	m_csOutSequence.Enter();

	IEMSConfigurationManager* pConfig = 0;

	try
	{
		pConfig = _GetConfigManager();

		if( !pConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wstring wszGroupID = cwszRouteName;

		EMSVARITYPE varEndID;
		memset( &varEndID, 0, sizeof(EMSVARITYPE) );

		EMS_RESULT hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1Identifier, &varEndID );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		EMSVARITYPE varMsgNumber;
		memset( &varMsgNumber, 0, sizeof(EMSVARITYPE) );

		bool bEnd1 = true;
		// Is it the from ID?
		if( varEndID.iVal == culFromID )
		{
			// Get the End1 sequence number.
			hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1OutBinMsgNumber, &varMsgNumber );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}
		}
		else
		{
			// Check if it's end 2.
			memset( &varEndID, 0, sizeof(EMSVARITYPE) );
			hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2Identifier, &varEndID );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

			if( varEndID.iVal == culFromID )
			{
				// Get the End2 sequence number.
				hr = pConfig->Get( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2OutBinMsgNumber, &varMsgNumber );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				bEnd1 = false;
			}
			else
			{
				CEMSLogMsgParam logMsgParam;
#if defined(UNICODE) || defined(_UNICODE)
				logMsgParam += cwszRouteGroup;
				logMsgParam += cwszRouteGroup;
				logMsgParam += cwszEnd1OutMsgNumber;
				logMsgParam += cwszEnd2OutMsgNumber;
#else
				logMsgParam += CEMSConversionUtil::ConvertToString( cwszRouteGroup ).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszRouteGroup).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszEnd1OutBinMsgNumber).c_str();
				logMsgParam += CEMSConversionUtil::ConvertToString(cwszEnd2OutBinMsgNumber).c_str();
#endif
				
				throw CEMSException( EMS_MTL_CONFIG_TWO_KEYS, logMsgParam );
			}
		}

		lRet = varMsgNumber.iVal;

		if( varMsgNumber.iVal >= clMaxBinMsgSequenceNumber )
			varMsgNumber.iVal = clMinBinMsgSequenceNumber;
		else
			varMsgNumber.iVal++;

		if( bEnd1 )
		{
			hr = pConfig->Set( cwszRouteGroup, wszGroupID.c_str(), cwszEnd1OutBinMsgNumber, varMsgNumber );
		}
		else
		{
			hr = pConfig->Set( cwszRouteGroup, wszGroupID.c_str(), cwszEnd2OutBinMsgNumber, varMsgNumber );
		}

		pConfig->Release();
		pConfig = 0;

	}
	catch( ... )
	{
		if( pConfig )
			pConfig->Release();
		pConfig = 0;

		m_csOutSequence.Leave();

		throw;
	}

	m_csOutSequence.Leave();

	return lRet;
}

unsigned long 
CEMSMTLConfiguration::GetMaxAlertsPerMessage( const unsigned long culFromID, const unsigned long culToID )
{
	unsigned long ulRet = 0;

	CEMSRouteEndConfig* pEnd1 = 0;
	CEMSRouteEndConfig* pEnd2 = 0;
	CEMSRouteEndConfig* pOutEnd = 0;
	CEMSRouteConfig** apRoutes = 0;
	unsigned long ulRoutes = 0;

	try
	{
		_LoadRoutes();

		GetRouteConfigs( culFromID, culToID, ulRoutes, apRoutes );

		if( ulRoutes > 0 && apRoutes )
		{
			// Use the first route in the list.
			if( apRoutes[0] )
			{
				pEnd1 = apRoutes[0]->GetEnd1();
				pEnd2 = apRoutes[0]->GetEnd2();

				if( pEnd1->GetID() == culFromID )
				{
					pOutEnd = pEnd1;
					pOutEnd->AddRef();
				}
				else if( pEnd2->GetID() == culFromID )
				{
					pOutEnd = pEnd2;
					pOutEnd->AddRef();
				}

				ulRet = pOutEnd->GetMaxAlertsPerMessage();

				pEnd1->Release();
				pEnd1 = 0;

				pEnd2->Release();
				pEnd2 = 0;

				pOutEnd->Release();
				pOutEnd = 0;
			}
		}

		if( apRoutes )
		{
			for( unsigned long l = 0; l < ulRoutes; l++ )
			{
				if( apRoutes[l] )
				{
					apRoutes[l]->Release();
					apRoutes[l] = 0;
				}
			}

			delete[] apRoutes;
			apRoutes = 0;
		}

	}
	catch( ... )
	{
		if( pEnd1 )
			pEnd1->Release();
		pEnd1 = 0;

		if( pEnd2 )
			pEnd2->Release();
		pEnd2 = 0;

		if( pOutEnd )
			pOutEnd->Release();
		pOutEnd = 0;

		if( apRoutes )
		{
			for( unsigned long l = 0; l < ulRoutes; l++ )
			{
				if( apRoutes[l] )
				{
					apRoutes[l]->Release();
					apRoutes[l] = 0;
				}
			}

			delete[] apRoutes;
			apRoutes = 0;
		}

		throw;
	}

	return ulRet;
}

wchar_t* 
CEMSMTLConfiguration::GetSoapEndPoint( unsigned long ulFromID, unsigned long ulToID )
{
	wchar_t* wszRet = 0;

	CEMSRouteEndConfig* pOutEnd = 0;

	try
	{
		GetOutRouteEnd( ulFromID, ulToID, pOutEnd );

		EMSSOAPSPEC soapSpec = pOutEnd->GetSOAP();

		wszRet = soapSpec.wszEndpoint;

		pOutEnd->Release();
		pOutEnd = 0;

	}
	catch( ... )
	{
		if( pOutEnd )
			pOutEnd->Release();
		pOutEnd = 0;

		throw;
	}

	return wszRet;
}

wchar_t* 
CEMSMTLConfiguration::GetProcessingDir()
{
	CEMSProcessConfig* pProcConfig = 0;
	wchar_t* wszRet = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wszRet = pProcConfig->GetProcessingDirectory();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( wszRet )
		{
			delete[] wszRet;
			wszRet = 0;
		}

		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return wszRet;
}

wchar_t* 
CEMSMTLConfiguration::GetProcessedBinaryDir()
{
	CEMSProcessConfig* pProcConfig = 0;
	wchar_t* wszRet = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		wszRet = pProcConfig->GetProcessedBinaryDirectory();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( wszRet )
		{
			delete[] wszRet;
			wszRet = 0;
		}

		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return wszRet;
}

bool 
CEMSMTLConfiguration::GetShuntToGateway()
{
	CEMSProcessConfig* pProcConfig = 0;
	bool bRet = false;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		bRet = pProcConfig->GetSitGtwyPassThrough();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return bRet;
}

unsigned long
CEMSMTLConfiguration::GetThisLutID()
{
	CEMSProcessConfig* pProcConfig = 0;
	unsigned long ulRet = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ulRet = pProcConfig->GetThisLutID();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return ulRet;
}

int
CEMSMTLConfiguration::GetSOAPPort()
{
	int iRet = 0;
	CEMSProcessConfig* pProcConfig = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		iRet = pProcConfig->GetSOAPPort();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return iRet;
}

int 
CEMSMTLConfiguration::GetSOAPBackLogSize()
{
	int iRet = 0;
	CEMSProcessConfig* pProcConfig = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		iRet = pProcConfig->GetSOAPBackLogSize();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return iRet;
}

long 
CEMSMTLConfiguration::GetNumSOAPHandlerThreads()
{
	long lRet = 0;
	CEMSProcessConfig* pProcConfig = 0;

	try
	{
		pProcConfig = _GetProcess();

		if( !pProcConfig )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		lRet = pProcConfig->GetNumSOAPHandlerThreads();

		pProcConfig->Release();
		pProcConfig = 0;

	}
	catch( ... )
	{
		if( pProcConfig )
		{
			pProcConfig->Release();
			pProcConfig = 0;
		}

		throw;
	}

	return lRet;
}

EMSLOCATION 
CEMSMTLConfiguration::GetSiteLocation( const unsigned long culSiteID )
{
	EMSLOCATION ret;
	memset( &ret, 0, sizeof( EMSLOCATION ) );

	CEMSLutConfig* pLut = 0;
	
	try
	{

		pLut = _GetLut( culSiteID );

		if( !pLut )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ret = pLut->GetLocation();

		pLut->Release();
		pLut = 0;
	}
	catch( ... )
	{
		if( pLut )
		{
			pLut->Release();
			pLut = 0;
		}

		throw;
	}

	return ret;
	
}

void 
CEMSMTLConfiguration::GetRouteConfigs( const unsigned long culFromID, const unsigned long culToID,
								unsigned long& ulRoutes, CEMSRouteConfig**& apRouteConfig )
{
	ulRoutes = 0;
	apRouteConfig = 0;

	_LoadRoutes();

	long lNumRoutes = 0;

	CEMSRouteConfig** apRouteConfigTemp = 0;
    CEMSRouteEndConfig* pEnd1 = 0;
    CEMSRouteEndConfig* pEnd2 = 0;

	try
	{

        std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

		// Shouldn't be a large number here, so reallocating our array is no big deal.
		while( it != m_multimapRoutes.end() )
		{
            CEMSRouteConfig* pRouteConfig = it->second;

            if( !pRouteConfig )
            {
                THROW_NULL_POINTER_EXCEPTION();
            }

            pEnd1 = pRouteConfig->GetEnd1();

            if( !pEnd1 )
            {
                THROW_NULL_POINTER_EXCEPTION();
            }

            pEnd2 = pRouteConfig->GetEnd2();

            if( !pEnd2 )
            {
                THROW_NULL_POINTER_EXCEPTION();
            }

            bool bMatches = false;

            if( pEnd1->GetID() == culFromID )
            {
                if( pEnd2->GetID() == culToID )
                    bMatches = true;
            }

            if( !bMatches )
            {
                if( pEnd1->GetID() == culToID )
                {
                    if( pEnd2->GetID() == culFromID )
                        bMatches = true;
                }
            }

            pEnd1->Release();
            pEnd1 = 0;

            pEnd2->Release();
            pEnd2 = 0;

            if( bMatches )
            {

			    lNumRoutes++;

			    apRouteConfigTemp = new CEMSRouteConfig*[lNumRoutes];

			    if( !apRouteConfigTemp )
			    {
				    THROW_NOMEMORY_EXCEPTION();
			    }

			    memset( apRouteConfigTemp, 0, lNumRoutes*sizeof(CEMSRouteConfig*) );

			    for( long l = 0; l < lNumRoutes - 1; l++ )
			    {
				    // No AddRef here.  So, no Release when the apRouteConfig is deleted below.
				    apRouteConfigTemp[l] = apRouteConfig[l];
			    }

			    apRouteConfigTemp[lNumRoutes-1] = pRouteConfig;

			    if( apRouteConfigTemp[lNumRoutes-1] )
				    apRouteConfigTemp[lNumRoutes-1]->AddRef();

			    if( apRouteConfig )
			    {
				    delete[] apRouteConfig;
				    apRouteConfig = 0;
			    }

			    apRouteConfig = apRouteConfigTemp;
            }

            it++;
		}

		ulRoutes = lNumRoutes;

	}
	catch( ... )
	{
        if( pEnd1 )
        {
            pEnd1->Release();
            pEnd1 = 0;
        }

        if( pEnd2 )
        {
            pEnd2->Release();
            pEnd2 = 0;
        }

		if( apRouteConfig )
		{
			for( long l = 0; l < lNumRoutes; l++ )
			{
				if( apRouteConfig[l] )
				{
					 apRouteConfig[l]->Release();
					  apRouteConfig[l] = 0;
				}
			}

			delete[] apRouteConfig;
			apRouteConfig = 0;
		}

		throw;
	}
}

void 
CEMSMTLConfiguration::GetOutRouteEnds( const unsigned long culFromID, unsigned long& ulRouteEnds, 
								CEMSRouteEndConfig**& apOutRouteEnds )
{
	ulRouteEnds = 0;
	apOutRouteEnds = 0;

	_LoadRoutes();

	std::list<CEMSRouteEndConfig*> lstRouteEnds;

	try
	{
		// Go through the routes and find ends that are outputs of the LUT/LUT Server identified.
		std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

		while( it != m_multimapRoutes.end() )
		{
			CEMSRouteConfig* pRoute = it->second;

			if( !pRoute )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			CEMSRouteEndConfig* pRouteEnd = pRoute->GetEnd( culFromID );

			if( pRouteEnd )
			{
				lstRouteEnds.push_back( pRouteEnd );
			}

			it++;
		}

		long lRouteEnds = lstRouteEnds.size();

		if( lRouteEnds > 0 )
		{
			apOutRouteEnds = new CEMSRouteEndConfig*[ lRouteEnds ];

			if( !apOutRouteEnds )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( apOutRouteEnds, 0, lRouteEnds*sizeof(CEMSRouteEndConfig*) );

			for( long l = 0; l < lRouteEnds; l++ )
			{
				apOutRouteEnds[l] = lstRouteEnds.front();
				lstRouteEnds.pop_front();

				if( apOutRouteEnds[l] )
					apOutRouteEnds[l]->AddRef();

				ulRouteEnds++;
			}
		}

	}
	catch( ... )
	{
		if( apOutRouteEnds )
		{
			for( unsigned long l = 0; l < ulRouteEnds; l++ )
			{
				if( apOutRouteEnds[l] )
				{
					apOutRouteEnds[l]->Release();
					apOutRouteEnds[l] = 0;
				}
			}

			delete[] apOutRouteEnds;
			apOutRouteEnds = 0;
		}
		
		throw;
	}
}

CEMSRouteConfig* 
CEMSMTLConfiguration::GetRouteConfig( const wchar_t* cwszFromAlias, const wchar_t* cwszToAlias )
{
	CEMSRouteConfig* pRet = 0;

	if( !cwszFromAlias || !cwszToAlias )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	m_csInLookup.Enter();
	
	CEMSRouteEndConfig* pEnd1 = 0;
	CEMSRouteEndConfig* pEnd2 = 0;

	wchar_t* wszAlias1 = 0;
	wchar_t* wszAlias2 = 0;
			
	try
	{
		//**************JB-Find is not working.  Disable use of table for now.
		//INBOUNDLOOKUPTABLE::iterator itFind = m_mapInboundLookupTable.find( INBOUNDLOOKUPKEY( cwszFromAlias , cwszToAlias ) );

		//if( itFind != m_mapInboundLookupTable.end() )
		//{
		//	pRet = itFind->second;

		//	if( !pRet )
		//	{
		//		THROW_NULL_POINTER_EXCEPTION();
		//	}

		//	pRet->AddRef();
		//}
		//else
		{
			// Find it and add it.
			_LoadRoutes();

			std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

			bool bFound = false;
			while( it != m_multimapRoutes.end() && !bFound )
			{
				CEMSRouteConfig* pRoute = it->second;

				if( !pRoute )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				pEnd1 = pRoute->GetEnd1();

				if( !pEnd1 )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				pEnd2 = pRoute->GetEnd2();

				if( !pEnd2 )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				wszAlias1 = pEnd1->GetAlias();

				if( !wszAlias1 )
				{
					CEMSLogMsgParam param;
#if defined(UNICODE) || defined(_UNICODE)
					param += pRoute->GetRouteName().c_str();
#else
					param += CEMSConversionUtil::ConvertToString( pRoute->GetRouteName().c_str() ).c_str();
#endif
					throw CEMSException( EMS_MTL_MISSING_ALIAS, param );
				}

				wszAlias2 = pEnd2->GetAlias();

				if( !wszAlias2 )
				{
					CEMSLogMsgParam param;
#if defined(UNICODE) || defined(_UNICODE)
					param += pRoute->GetRouteName().c_str();
#else
					param += CEMSConversionUtil::ConvertToString( pRoute->GetRouteName().c_str() ).c_str();
#endif
					throw CEMSException( EMS_MTL_MISSING_ALIAS, param );
				}

				if( wcsicmp( wszAlias1, cwszFromAlias ) == 0 )
				{
					if( wcsicmp( wszAlias2, cwszToAlias ) == 0 )
					{
						bFound = true;

						pRet = pRoute;
						pRet->AddRef();
					}
				}

				if( !bFound )
				{
					if( wcsicmp( wszAlias1, cwszToAlias ) == 0 )
					{
						if( wcsicmp( wszAlias2, cwszFromAlias ) == 0 )
						{
							bFound = true;

							pRet = pRoute;
							pRet->AddRef();
						}
					}
				}

				// Add it to the lookup table.
				if( bFound )
				{
				//	CEMSInBoundLookupKey keyNew( cwszFromAlias, cwszToAlias );
				//	m_mapInboundLookupTable.insert( INBOUNDLOOKUPTABLE::value_type( keyNew, pRet ) );
				}

				
				delete[] wszAlias1;
				wszAlias1 = 0;

				delete[] wszAlias2;
				wszAlias2 = 0;

				pEnd1->Release();
				pEnd1 = 0;

				pEnd2->Release();
				pEnd2 = 0;

				it++;

			}

		}

		m_csInLookup.Leave();
		
	}
	catch( ... )
	{
		if( pEnd1 )
		{
			pEnd1->Release();
			pEnd1 = 0;
		}

		if( pEnd2 )
		{
			pEnd2->Release();
			pEnd2 = 0;
		}

		if( wszAlias1 )
		{
			delete[] wszAlias1;
			wszAlias1 = 0;
		}

		if( wszAlias2 )
		{
			delete[] wszAlias2;
			wszAlias2 = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		m_csInLookup.Leave();

		throw;
	}

	return pRet;
}

CEMSRouteConfig* 
CEMSMTLConfiguration::GetRouteConfig( const unsigned long culRouteID )
{
	CEMSRouteConfig* pRet = 0;

	try
	{
		_LoadRoutes();

		// Convert the culRouteID to a string.
		std::wstringstream wszRouteStream;
		wszRouteStream << culRouteID;

		std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.find( wszRouteStream.str().c_str() );

		if( it != m_multimapRoutes.end() )
		{
			pRet = it->second;

			if( !pRet )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet->AddRef();
		}
		else
		{
			// Could be disabled.  Therefore, no error.
		}		
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSMTLConfiguration::GetOutRouteConfigs( const unsigned long culFromID, unsigned long& ulRoutes, 
								CEMSRouteConfig**& apRoutes )
{
	ulRoutes = 0;
	apRoutes = 0;

	_LoadRoutes();

	std::list<CEMSRouteConfig*> lstRoutes;

	try
	{
		// Go through the routes and find ends that are outputs of the LUT/LUT Server identified.
		std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

		while( it != m_multimapRoutes.end() )
		{
			CEMSRouteConfig* pRoute = it->second;

			if( !pRoute )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			CEMSRouteEndConfig* pRouteEnd = pRoute->GetEnd( culFromID );

			if( pRouteEnd )
			{
				lstRoutes.push_back( pRoute );
			}

			it++;
		}

		long lRoutes = lstRoutes.size();

		if( lRoutes > 0 )
		{
			apRoutes = new CEMSRouteConfig*[ lRoutes ];

			if( !apRoutes )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( apRoutes, 0, lRoutes*sizeof(CEMSRouteConfig*) );

			for( long l = 0; l < lRoutes; l++ )
			{
				apRoutes[l] = lstRoutes.front();
				lstRoutes.pop_front();

				if( apRoutes[l] )
					apRoutes[l]->AddRef();

				ulRoutes++;
			}
		}

	}
	catch( ... )
	{
		if( apRoutes )
		{
			for( unsigned long l = 0; l < ulRoutes; l++ )
			{
				if( apRoutes[l] )
				{
					apRoutes[l]->Release();
					apRoutes[l] = 0;
				}
			}

			delete[] apRoutes;
			apRoutes = 0;
		}
		
		throw;
	}
}

void
CEMSMTLConfiguration::GetOutRouteEnd( const unsigned long culFromID, const unsigned long culToID, 
										CEMSRouteEndConfig*& pRouteOut )
{
	pRouteOut = 0;

	_LoadRoutes();

	CEMSRouteEndConfig* pRouteEnd1 = 0;
	CEMSRouteEndConfig* pRouteEnd2 = 0;

	try
	{
		// Go through the routes and find ends that are outputs of the LUT/LUT Server identified.
		std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

		bool bFound = false;
		while( it != m_multimapRoutes.end() && !bFound )
		{
			CEMSRouteConfig* pRoute = it->second;

			if( !pRoute )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRouteEnd1 = pRoute->GetEnd1();
			pRouteEnd2 = pRoute->GetEnd2();

			if( pRouteEnd1 )
			{
				if( culFromID == pRouteEnd1->GetID() )
				{
					if( pRouteEnd2 )
					{
						if( culToID == pRouteEnd2->GetID() )
						{
							pRouteOut = pRouteEnd1;
							pRouteOut->AddRef();
							bFound = true;
						}
					}
				}
			}

			if( !bFound )
			{
				if( pRouteEnd2 )
				{
					if( culFromID == pRouteEnd2->GetID() )
					{
						if( pRouteEnd1 )
						{
							if( culToID == pRouteEnd1->GetID() )
							{
								pRouteOut = pRouteEnd2;
								pRouteOut->AddRef();
								bFound = true;

							}
						}
					}
				}
			}

			if( pRouteEnd1 )
			{
				pRouteEnd1->Release();
				pRouteEnd1 = 0;
			}

			if( pRouteEnd2 )
			{
				pRouteEnd2->Release();
				pRouteEnd2 = 0;
			}

			it++;
		}

	}
	catch( ... )
	{
		if( pRouteOut )
		{
			pRouteOut->Release();
			pRouteOut = 0;
		}

		if( pRouteEnd1 )
		{
			pRouteEnd1->Release();
			pRouteEnd1 = 0;
		}

		if( pRouteEnd2 )
		{
			pRouteEnd2->Release();
			pRouteEnd2 = 0;
		}

		throw;
	}
}

std::wstring 
CEMSMTLConfiguration::GetTranslation( const wchar_t* cwszTableName, const wchar_t* cwszSITCode )
{
	std::wstring wszRet;

	int iConfigItems = 0;
	EMSCONFIGURATIONITEM** apConfigItems = 0;

	IEMSConfigurationManager* pConfig = 0;
	
	try
	{
		m_csTranslationTables.Enter();

		TABLEOFTRANSLATIONTABLES::const_iterator citFindTable = m_mapTranslationTables.find( std::wstring( cwszTableName ) );

		TRANSLATIONTABLE mapTransTable;

		if( citFindTable == m_mapTranslationTables.end() )
		{
			// Table not found.  Load it.
			pConfig = _GetConfigManager();

			if( !pConfig )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			EMS_RESULT hr = pConfig->GetGroup( cwszSTTGroup, cwszTableName, &iConfigItems, &apConfigItems );

			if( FAILED(hr) )
			{
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( cwszTableName );
				
				throw CEMSException( EMS_MTL_CONFIGURATION_NO_TRANS_TABLE, oLogParam );
			}

			for( int i = 0; i < iConfigItems; i++ )
			{
				std::wstring wszKey;
				std::wstring wszValue;

				if( !apConfigItems[i] )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				if( !apConfigItems[i]->pwcsKeyName )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				wszKey = apConfigItems[i]->pwcsKeyName;

				if( !apConfigItems[i]->uiValues || !apConfigItems[i]->ValueList )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				wszValue = CEMSConversionUtil::ConvertToString( (long) apConfigItems[i]->ValueList[0].iVal );

				mapTransTable.insert( std::pair<std::wstring,std::wstring>( wszKey, wszValue ) );
			}
			
			m_mapTranslationTables.insert( std::pair<std::wstring,TRANSLATIONTABLE>( std::wstring( cwszTableName ), mapTransTable ) );

			pConfig->Release();
			pConfig = 0;

			if( apConfigItems )
			{
				for( int i = 0; i < iConfigItems; i++ )
				{
					if( apConfigItems[i] )
					{
						if( apConfigItems[i]->ValueList )
						{
							CoTaskMemFree( apConfigItems[i]->ValueList );
							apConfigItems[i]->ValueList = 0;
						}

						if( apConfigItems[i]->pwcsKeyName )
						{
							CoTaskMemFree( apConfigItems[i]->pwcsKeyName );
							apConfigItems[i]->pwcsKeyName = 0;
						}

						CoTaskMemFree( apConfigItems[i] );
						apConfigItems[i] = 0;
					}
				}

				CoTaskMemFree( apConfigItems );
				apConfigItems = 0;
			}
		}
		else
		{
			mapTransTable = citFindTable->second;

		}

		std::wstringstream wszKeyBuf;
		wszKeyBuf << cwszSTTInternal << L"." << cwszSITCode;

		TRANSLATIONTABLE::const_iterator citFind = mapTransTable.find( wszKeyBuf.str() );

		if( citFind == mapTransTable.end() )
		{
			CEMSLogMsgParam oLogParam;
			oLogParam.AddString( wszKeyBuf.str().c_str() );
			oLogParam.AddString( cwszTableName );

			throw CEMSException( EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE, oLogParam );
		}
		else
		{
			wszRet = citFind->second;
		}


		m_csTranslationTables.Leave();

	}
	catch( ... )
	{
		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( apConfigItems )
		{
			for( int i = 0; i < iConfigItems; i++ )
			{
				if( apConfigItems[i] )
				{
					if( apConfigItems[i]->ValueList )
					{
						CoTaskMemFree( apConfigItems[i]->ValueList );
						apConfigItems[i]->ValueList = 0;
					}

					if( apConfigItems[i]->pwcsKeyName )
					{
						CoTaskMemFree( apConfigItems[i]->pwcsKeyName );
						apConfigItems[i]->pwcsKeyName = 0;
					}

					CoTaskMemFree( apConfigItems[i] );
					apConfigItems[i] = 0;
				}
			}

			CoTaskMemFree( apConfigItems );
			apConfigItems = 0;
		}

		m_csTranslationTables.Leave();

		throw;
	}

	return wszRet;
}

void
CEMSMTLConfiguration::_LoadRoutes()
{
	if( !m_bRoutesInitialized )
	{
		int iRoutes = 0;
		wchar_t** awszGroupIDs = 0;

		int iConfigItems = 0;
		EMSCONFIGURATIONITEM** apConfigItems = 0;

		try
		{
			m_csAllRoutes.Enter();

			if( !m_bRoutesInitialized )
			{
				IEMSConfigurationManager* pConfig = _GetConfigManager();

				if( !pConfig )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

			
				EMS_RESULT hr = pConfig->GetGroupIDs( cwszRouteGroup, &iRoutes, &awszGroupIDs );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION( hr );
				}

				for( int i = 0; i < iRoutes; i++ )
				{
					hr = pConfig->GetGroup( cwszRouteGroup, awszGroupIDs[i], &iConfigItems, &apConfigItems );

					if( _IsRouteEnabled( iConfigItems, apConfigItems ) )
					{
						if( FAILED(hr) )
						{
							THROW_RUNTIME_EXCEPTION(hr);
						}

						CEMSRouteConfig* pRouteConfig = new CEMSRouteConfig;

						if( !pRouteConfig )
						{
							THROW_NOMEMORY_EXCEPTION();
						}

						pRouteConfig->SetRouteName( awszGroupIDs[i] );
						pRouteConfig->PopulateRoute( (const int) iConfigItems, (const EMSCONFIGURATIONITEM**) apConfigItems );

						std::wstring wszKey( awszGroupIDs[i] );

						m_multimapRoutes.insert( std::pair<std::wstring,CEMSRouteConfig*>( wszKey,
													pRouteConfig ) );
					}
				}

				m_bRoutesInitialized = true;

				if( awszGroupIDs )
				{
					for( int i = 0; i < iRoutes; i++ )
					{
						if( awszGroupIDs[i] )
						{
							CoTaskMemFree( awszGroupIDs[i] );
							awszGroupIDs[i] = 0;
						}
					}

					CoTaskMemFree( awszGroupIDs );
					awszGroupIDs = 0;
				}

				if( apConfigItems )
				{
					for( int i = 0; i < iConfigItems; i++ )
					{
						if( apConfigItems[i] )
						{
							CoTaskMemFree( apConfigItems[i] );
							apConfigItems[i] = 0;
						}
					}

					CoTaskMemFree( apConfigItems );
					apConfigItems = 0;

				}

			}

			m_csAllRoutes.Leave();
		}
		catch( ... )
		{
			if( awszGroupIDs )
			{
				for( int i = 0; i < iRoutes; i++ )
				{
					if( awszGroupIDs[i] )
					{
						CoTaskMemFree( awszGroupIDs[i] );
						awszGroupIDs[i] = 0;
					}
				}

				CoTaskMemFree( awszGroupIDs );
				awszGroupIDs = 0;
			}

			if( apConfigItems )
			{
				for( int i = 0; i < iConfigItems; i++ )
				{
					if( apConfigItems[i] )
					{
						CoTaskMemFree( apConfigItems[i] );
						apConfigItems[i] = 0;
					}
				}

				CoTaskMemFree( apConfigItems );
				apConfigItems = 0;

			}

			std::multimap<std::wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();
			while( it != m_multimapRoutes.end() )
			{
				if( it->second )
				{
					it->second->Release();
				}

				it++;
			}

			m_multimapRoutes.clear();

			m_csAllRoutes.Leave();

			throw;
		}
	}
}

IEMSConfigurationManager* 
CEMSMTLConfiguration::_GetConfigManager()
{
	IEMSConfigurationManager* pConfig = 0;

#ifdef CACHE_CM
	if( !m_pConfigMgr )
	{
		try
		{
			m_csMgr.Enter();

			if( !m_pConfigMgr )
			{
				EMS_RESULT hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL, 
												IID_IEMSConfigurationManager, (void**) &m_pConfigMgr);

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION( hr );
				}
			}

			m_csMgr.Leave();
		}
		catch( ... )
		{
			m_csMgr.Leave();

			throw;
		}
	}

	pConfig = m_pConfigMgr;

	try
	{
		m_csMgr.Enter();

		pConfig->AddRef();

		m_csMgr.Leave();
	}
	catch( ... )
	{
		m_csMgr.Leave();

		throw
	}

#else
	
	EMS_RESULT hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL, 
												IID_IEMSConfigurationManager, (void**) &pConfig);

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

#endif

	return pConfig;
}

void
CEMSMTLConfiguration::_ClearConfig()
{
	try
	{
		m_csProcess.Enter();

		if( m_pProcessCfg )
		{
			m_pProcessCfg->Release();
			m_pProcessCfg = 0;
		}

		m_csProcess.Leave();
	}
	catch( ... )
	{
		m_csProcess.Leave();
		throw;
	}

	try
	{
		m_csRoutes.Enter();

		std::map<std::wstring,CEMSRouteConfig*>::iterator it = m_mapRoutes.begin();

		while( it != m_mapRoutes.end() )
		{
			if( it->second )
			{
				it->second->Release();
				it->second = 0;
			}
			it++;
		}

		m_mapRoutes.clear();

		m_csRoutes.Leave();
	}
	catch( ... )
	{
		m_csRoutes.Leave();

		throw;
	}

	try
	{
		m_csLuts.Enter();

		std::map<unsigned long,CEMSLutConfig*>::iterator it = m_mapLuts.begin();

		while( it != m_mapLuts.end() )
		{
			if( it->second )
			{
				it->second->Release();
				it->second = 0;
			}
			it++;
		}

		m_mapLuts.clear();

		m_csLuts.Leave();
	}
	catch( ... )
	{
		m_csLuts.Leave();

		throw;
	}

	try
	{
		m_csTransTables.Enter();

		std::map<wstring,CEMSSTTConfig*>::iterator it = m_mapTransTables.begin();

		while( it != m_mapTransTables.end() )
		{
			if( it->second )
			{
				it->second->Release();
				it->second = 0;
			}
			it++;
		}

		m_mapTransTables.clear();

		m_csTransTables.Leave();
	}
	catch( ... )
	{
		m_csTransTables.Leave();
	}

	try
	{
		m_csAllRoutes.Enter();

		std::multimap<wstring,CEMSRouteConfig*>::iterator it = m_multimapRoutes.begin();

		while( it != m_multimapRoutes.end() )
		{
			if( it->second )
			{
				it->second->Release();
				it->second = 0;
			}
			it++;
		}

		m_multimapRoutes.clear();

		m_csAllRoutes.Leave();
	}
	catch( ... )
	{
		m_csAllRoutes.Leave();

		throw;
	}

	try
	{
		m_csInLookup.Enter();

		INBOUNDLOOKUPTABLE::iterator it = m_mapInboundLookupTable.begin();

		while( it != m_mapInboundLookupTable.end() )
		{
			if( it->second )
			{
				it->second->Release();
				it->second = 0;
			}
		}

		m_mapInboundLookupTable.clear();

		m_csInLookup.Leave();
	}
	catch( ... )
	{

		m_csInLookup.Leave();

		throw;

	}
}

CEMSProcessConfig* 
CEMSMTLConfiguration::_GetProcess()
{
	CEMSProcessConfig* pRet = 0;
	IEMSConfigurationManager* pConfig = 0;

	try
	{
		m_csProcess.Enter();

		if( !m_pProcessCfg )
		{
			m_pProcessCfg = new CEMSProcessConfig;

			if( !m_pProcessCfg )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pConfig = _GetConfigManager();

			if( !pConfig )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			m_pProcessCfg->Populate( pConfig );

			pConfig->Release();
			pConfig = 0;
		}

		pRet = m_pProcessCfg;
		pRet->AddRef();

		m_csProcess.Leave();
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		m_csProcess.Leave();

		throw;
	}

	return pRet;
}

CEMSLutConfig*
CEMSMTLConfiguration::_GetLut( const unsigned long culID )
{
	CEMSLutConfig* pLut = 0;

	try
	{
		m_csLuts.Enter();

		// Search for the route.
		std::map<unsigned long,CEMSLutConfig*>::iterator itFind = m_mapLuts.find( culID );

		if( itFind == m_mapLuts.end() )
		{
			// Get it from the CM.
			pLut = _GetLutFromCM( culID );

			if( pLut )
			{
				m_mapLuts.insert( std::pair<unsigned long, CEMSLutConfig*>( culID, pLut ) );
			}
		}
		else
		{
			pLut = itFind->second;
		}

		if( pLut )
			pLut->AddRef();

		m_csLuts.Leave();
	}
	catch( ... )
	{
		if( pLut )
		{
			pLut->Release();
			pLut = 0;
		}

		m_csLuts.Leave();

		throw;
	}


	return pLut;
}

CEMSLutConfig*
CEMSMTLConfiguration::_GetLutFromCM( const unsigned long culID )
{
	CEMSLutConfig* pLut = 0;
	
	IEMSConfigurationManager* pConfig = _GetConfigManager();

	try
	{
		pLut = new CEMSLutConfig;

		if( !pLut )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pLut->Populate( culID, pConfig );

	}
	catch( ... )
	{
		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( pLut )
		{
			pLut->Release();
			pLut = 0;
		}

		throw;
	}
	

	return pLut;
}

CEMSSTTConfig* 
CEMSMTLConfiguration::_GetTranslationTable( const wchar_t* cwszTable )
{
	CEMSSTTConfig* pRet = 0;

	try
	{
		m_csTransTables.Enter();

		// Search for the route.
		wstring wszTemp( cwszTable );
		std::map<wstring,CEMSSTTConfig*>::iterator itFind = m_mapTransTables.find( wszTemp );

		if( itFind == m_mapTransTables.end() )
		{
			// Get it from the CM.
			pRet = _GetTransTableFromCM( cwszTable );

			if( pRet )
			{
				m_mapTransTables.insert( std::pair<wstring, CEMSSTTConfig*>( wszTemp, pRet ) );
			}
		}
		else
		{
			pRet = itFind->second;
		}

		if( pRet )
			pRet->AddRef();

		m_csTransTables.Leave();
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		m_csTransTables.Leave();

		throw;
	}


	return pRet;
}

CEMSSTTConfig*
CEMSMTLConfiguration::_GetTransTableFromCM( const wchar_t* cwszTable )
{
	CEMSSTTConfig* pRet = 0;
	
	IEMSConfigurationManager* pConfig = _GetConfigManager();

	try
	{
		pRet = new CEMSSTTConfig;

		if( !pRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pRet->Populate( cwszTable, pConfig );

	}
	catch( ... )
	{
		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}
	

	return pRet;
}

bool 
CEMSMTLConfiguration::_IsRouteEnabled( const int ciConfigItems, EMSCONFIGURATIONITEM** apConfigItems )
{
	bool bRet = false;

	if( apConfigItems )
	{
		bool bFound = false;

		for( int i = 0; i < ciConfigItems && !bFound; i++ )
		{
			if( wcsicmp( apConfigItems[i]->pwcsKeyName, cwszRouteEnabled ) == 0 )
			{
				bFound = true;

				bRet = apConfigItems[i]->ValueList[0].bVal ? true : false;
			}
		}
	}

	return bRet;
}