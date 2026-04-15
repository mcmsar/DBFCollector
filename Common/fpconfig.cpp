/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/
#pragma warning(disable:4786)

#include "fpconfig.h"
#include "emsexcpt.h"
#include "ccbootstrap.h"
#include "meosysclient.h"
#include "antennaclient.h"
#include "convutility.h"
#include "fploader.h"

const wchar_t* CEMSFPConfig::ms_cwszPairIDs = L"pairs/pair";
const wchar_t* CEMSFPConfig::ms_cwszPair = L"pairs/pair[@id='%d']";
const wchar_t* CEMSFPConfig::ms_cwszID = L"@id";
const wchar_t* CEMSFPConfig::ms_cwszPairAntenna = L"antenna_no";
const wchar_t* CEMSFPConfig::ms_cwszPairDS = L"datastream_no";
const wchar_t* CEMSFPConfig::ms_cwszDataStreamID = L"pairs/pair[@id=%d]/datastream";
const wchar_t* CEMSFPConfig::ms_cwszAntennaID = L"pairs/pair[@id=%d]/antenna";
const wchar_t* CEMSFPConfig::ms_cwszADBoardID = L"datastreams/datastream[@id='%d']/adboard/id";
const wchar_t* CEMSFPConfig::ms_cwszChannelID = L"datastreams/datastream[@id='%d']/adboard/channel_no";
const wchar_t* CEMSFPConfig::ms_cwszDSProxyClassID = L"datastreams/datastream[@id='%d']/proxy/@classid";
const wchar_t* CEMSFPConfig::ms_cwszDSProxyWSURL = L"datastreams/datastream[@id='%d']/proxy/ws/url";
const wchar_t* CEMSFPConfig::ms_cwszDSProxyWSUser = L"datastreams/datastream[@id='%d']/proxy/ws/user";
const wchar_t* CEMSFPConfig::ms_cwszDSProxyWSPwd = L"datastreams/datastream[@id='%d']/proxy/ws/pwd";
const wchar_t* CEMSFPConfig::ms_cwszAntennaProxyClassID = L"antennacontrollers/ac[antennas/antenna/@id='%d']/proxy/@classid";
const wchar_t* CEMSFPConfig::ms_cwszAntennaProxyWSURL = L"antennacontrollers/ac[antennas/antenna/@id='%d']/proxy/ws/url";
const wchar_t* CEMSFPConfig::ms_cwszAntennaProxyWSUser = L"antennacontrollers/ac[antennas/antenna/@id='%d']/proxy/ws/user";
const wchar_t* CEMSFPConfig::ms_cwszAntennaProxyWSPwd = L"antennacontrollers/ac[antennas/antenna/@id='%d']/proxy/ws/pwd";
const wchar_t* CEMSFPConfig::ms_cwszAntenna = L"antennacontrollers/ac";
const wchar_t* CEMSFPConfig::ms_cwszAntennaConfig = L"antennacontrollers/ac[antennas/antenna/@id='%d']";
const wchar_t* CEMSFPConfig::ms_cwszDSConfig = L"datastreams/datastream[@id='%d']";
const wchar_t* CEMSFPConfig::ms_cwszSatellites = L"satellites";
const wchar_t* CEMSFPConfig::ms_cwszScheduleFolder = L"schedulefolder";
const wchar_t* CEMSFPConfig::ms_cwszLutID = L"lut_id";
const wchar_t* CEMSFPConfig::ms_cwszAntennaStatusCheckInterval = L"antennastatuscheckinterval"; //seconds

const wchar_t* CEMSFPConfig::ms_cwszAntennas = L"antennas/antenna";

CEMSFPConfig::CEMSFPConfig()
{
	if( CCBootstrap::IsMEOSystem() )
	{
		m_bUseConfigWS = true;
	}
	else
		m_bUseConfigWS = false;
}

CEMSFPConfig::CEMSFPConfig( const CEMSFPConfig& x ) : m_oConfig( x.m_oConfig ), m_bUseConfigWS( x.m_bUseConfigWS )
{
}

CEMSFPConfig::~CEMSFPConfig()
{
}

void 
CEMSFPConfig::SetConfiguration( const wchar_t* cwszConfigString )
{
	m_oConfig.SetSource( cwszConfigString );
}

std::wstring 
CEMSFPConfig::GetConfiguration()
{
	return m_oConfig.Serialize();
}

void 
CEMSFPConfig::GetList( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs )
{
	if( m_bUseConfigWS )
	{
		_GetListEx( rulPairs, raAntPairs );
	}
	else
	{
		_GetPairsList( m_oConfig, rulPairs, raAntPairs );
	}
}

void
CEMSFPConfig::_GetListEx( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs )
{
	std::wstring				wszPairsConfig;
	CEMSConfigurationAccessor	oConfig;
	wszPairsConfig = _GetPairsXMLConfig();

	oConfig.SetSource( wszPairsConfig.c_str() );
	_GetPairsList( oConfig, rulPairs, raAntPairs );
}

std::wstring 
CEMSFPConfig::_GetPairsXMLConfig()
{
	std::wstring wszPairsConfig;
	MEOSystemClient oSysClient;
	char szXMLConfig[2048];
	memset( szXMLConfig, 0, sizeof( szXMLConfig ) );

	string szSubsystemID = CCBootstrap::GetThisSubsystemId();
	oSysClient.getFPPairsByFpId(szSubsystemID, szXMLConfig, 2047 );
	wszPairsConfig = CEMSConversionUtil::ConvertToString( szXMLConfig );

	return wszPairsConfig;
}

void 
CEMSFPConfig::_GetPairsList( CEMSConfigurationAccessor& roConfig, ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs )
{
	std::wstring wszKey;
	if( m_bUseConfigWS )
	{
		wszKey = L"pair";
	}
	else
	{
		wszKey = ms_cwszPairIDs;
	}

	CEMSObjectList<CEMSConfigurationAccessor> olstPairs = roConfig.GetAccessorList( wszKey.c_str() );

	if( (rulPairs = olstPairs.Count()) > 0 )
	{
		raAntPairs = new EMSANTDATAPAIR[ rulPairs ];

		if( !raAntPairs )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( raAntPairs, 0, rulPairs*sizeof(EMSANTDATAPAIR) );

		olstPairs.MoveFirst();

		for( ULONG l = 0; l < rulPairs; l++ )
		{
			CEMSConfigurationAccessor oPair = olstPairs.GetNext();

			raAntPairs[l].ulPairID = oPair.GetAttributeValueULong( ms_cwszID );
			raAntPairs[l].ulAntennaID = oPair.GetElementValueULong( ms_cwszPairAntenna );
			raAntPairs[l].ulDataStreamID = oPair.GetElementValueULong( ms_cwszPairDS );
		}
	}
}

ULONG	
CEMSFPConfig::GetAntennaID( const ULONG culPair )
{
	ULONG ulRet = 0;
	
	if( m_bUseConfigWS )
	{
		ulRet = _GetAntennaIDEx( culPair );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszAntennaID, culPair );

		ulRet = m_oConfig.GetElementValueULong( wszKey );
	}

	return ulRet;
}


ULONG
CEMSFPConfig::_GetAntennaIDEx( const ULONG culPair )
{
	ULONG ulRet = 0;
	wchar_t wszKey[ 128 ];
	std::wstring				wszPairsConfig;
	CEMSConfigurationAccessor	oConfig;
	wszPairsConfig = _GetPairsXMLConfig();
	oConfig.SetSource( wszPairsConfig.c_str() );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"pair[@id=%d]/antenna_no", culPair );
	ulRet = oConfig.GetElementValueULong( wszKey );

	return ulRet;
}


ULONG	
CEMSFPConfig::GetDSID( const ULONG culPair )
{
	ULONG ulRet = 0;
	
	if( m_bUseConfigWS )
	{
		ulRet = _GetDSIDEx( culPair );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszDataStreamID, culPair );

		ulRet = m_oConfig.GetElementValueULong( wszKey );
	}

	return ulRet;
}

ULONG
CEMSFPConfig::_GetDSIDEx( const ULONG culPair )
{
	ULONG ulRet = 0;
	wchar_t wszKey[ 128 ];
	std::wstring				wszPairsConfig;
	CEMSConfigurationAccessor	oConfig;
	wszPairsConfig = _GetPairsXMLConfig();
	oConfig.SetSource( wszPairsConfig.c_str() );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"pair[@id=%d]/datastream_no", culPair );
	ulRet = oConfig.GetElementValueULong( wszKey );

	return ulRet;
}

void 
CEMSFPConfig::SetProperty( const wchar_t* cwszKey, const wchar_t* cwszValue )
{
	if( !m_bUseConfigWS )
	{
		m_oConfig.SetElementValue( cwszKey, cwszValue );
	}
}

std::wstring 
CEMSFPConfig::GetProperty( const wchar_t* cwszKey )
{
	if( !m_bUseConfigWS )
	{
		return m_oConfig.GetElementValue( cwszKey );
	}
	
	return L"";
}

std::wstring 
CEMSFPConfig::_GetDataStreamXMLConfig()
{
	std::wstring wszPairsConfig;
	MEOSystemClient oSysClient;
	char szXMLConfig[2048];
	memset( szXMLConfig, 0, sizeof( szXMLConfig ) );

	string szSubsystemID = CCBootstrap::GetThisSubsystemId();
	oSysClient.getFPDataStreamsByFpId(szSubsystemID, szXMLConfig, 2047 );
	wszPairsConfig = CEMSConversionUtil::ConvertToString( szXMLConfig );

	return wszPairsConfig;
}


ULONG 
CEMSFPConfig::GetADBoardID( const ULONG culDSID )
{
	ULONG ulRet = 0;
	
	if( m_bUseConfigWS )
	{
		ulRet = _GetADBoardIDEx( culDSID );
	}
	else
	{		
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszADBoardID, culDSID );

		ulRet = m_oConfig.GetElementValueULong( wszKey );
	}

	return ulRet;
}

ULONG 
CEMSFPConfig::_GetADBoardIDEx( const ULONG culDSID )
{
	ULONG ulRet = 0;
	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"datastream[@id='%d']/adboard/id", culDSID );
	ulRet = oConfig.GetElementValueULong( wszKey );

	return ulRet;
}

ULONG 
CEMSFPConfig::GetChannelID( const ULONG culDSID )
{
	ULONG ulRet = 0;
	
	if( m_bUseConfigWS )
	{
		ulRet = _GetChannelIDEx( culDSID );
	}
	else
	{		
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszChannelID, culDSID );

		ulRet = m_oConfig.GetElementValueULong( wszKey );
	}

	return ulRet;
}

ULONG 
CEMSFPConfig::_GetChannelIDEx( const ULONG culDSID )
{
	ULONG ulRet = 0;
	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"datastream[@id='%d']/adboard/channel_no", culDSID );
	ulRet = oConfig.GetElementValueULong( wszKey );

	return ulRet;
}

ULONG
CEMSFPConfig::GetLutID()
{
	ULONG ulRet = 0;
	
	if( m_bUseConfigWS )
	{
		ulRet = _GetLutIDEx();
	}
	else
	{
		ulRet = m_oConfig.GetElementValueULong( ms_cwszLutID );
	}

	return ulRet;
}

ULONG
CEMSFPConfig::_GetLutIDEx()
{
	ULONG ulRet = 0;
	string szSubsystemID = CCBootstrap::GetThisSubsystemId();
	
	ulRet = atol( szSubsystemID.c_str() );
	
	return ulRet;
}

int
CEMSFPConfig::GetAntennaStatusCheckInterval()
{
	int iRet = 0;
	
	if( m_bUseConfigWS )
	{
		iRet = _GetAntennaStatusCheckIntervalEx();
	}
	else
	{
		iRet = m_oConfig.GetElementValueInt( ms_cwszAntennaStatusCheckInterval );
	}

	return iRet;
}


std::string 
CEMSFPConfig::_GetAntennaComponent()
{
	std::string szAntID;
	MEOSystemClient oSysClient;
	
	string szSubsystemID = CCBootstrap::GetThisSubsystemId();

	FPConfig* pFP = oSysClient.getFPById(szSubsystemID);
	if( pFP )
	{
		szAntID = pFP->GetAntennaComponent();
		delete pFP;
		pFP = NULL;
	}

	return szAntID;
}


int
CEMSFPConfig::_GetAntennaStatusCheckIntervalEx()
{
	int iRet = 0;

	EMSAntennaClient oAntCL;

	std::string szAntComp = _GetAntennaComponent();
	EMSAntennaConfig* pAnt = oAntCL.getById(szAntComp);

	if( pAnt )
	{
		iRet = pAnt->GetStatusCheckIntvl();
		delete pAnt;
		pAnt = NULL;
	}

	return iRet;
}

std::wstring 
CEMSFPConfig::GetDSProxyClassID( const ULONG culPair )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetDSProxyClassIDEx( culPair );
	}
	else
	{
		// First, Get the DataStreamID.
		ULONG ulDSID = GetDSID( culPair );

		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszDSProxyClassID, ulDSID );

		wszRet = m_oConfig.GetAttributeValue( wszKey );
	}

	return wszRet;
}

std::wstring 
CEMSFPConfig::_GetDSProxyClassIDEx( const ULONG culPair )
{
	std::wstring wszRet;

	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	// First, Get the DataStreamID.
	ULONG ulDSID = GetDSID( culPair );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"datastream[@id='%d']/proxy/@classid", ulDSID );
	wszRet = oConfig.GetAttributeValue( wszKey );

	return wszRet;
}

std::wstring 
CEMSFPConfig::GetDSWSURL( const ULONG culPair )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetDSWSURLEx( culPair );
	}
	else
	{
		// First, Get the DataStreamID.
		ULONG ulDSID = GetDSID( culPair );

		wchar_t wszKey[ 1024 ];
		memset( wszKey, 0, 1024*sizeof(wchar_t) );

		_snwprintf( wszKey, 1023, ms_cwszDSProxyWSURL, ulDSID );

		wszRet = m_oConfig.GetElementValue( wszKey );
	}

	return wszRet;

}

std::wstring
CEMSFPConfig::_GetDSWSURLEx( const ULONG culPair )
{
	std::wstring wszRet;

	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	// First, Get the DataStreamID.
	ULONG ulDSID = GetDSID( culPair );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 1023, L"datastream[@id='%d']/proxy/ws/url", ulDSID );
	wszRet = oConfig.GetAttributeValue( wszKey );

	return wszRet;
}

std::wstring 
CEMSFPConfig::GetDSWSUser( const ULONG culPair )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetDSWSUserEx( culPair );
	}
	else
	{
		// First, Get the DataStreamID.
		ULONG ulDSID = GetDSID( culPair );

		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszDSProxyWSUser, ulDSID );

		wszRet = m_oConfig.GetElementValue( wszKey );
	}

	return wszRet;
}


std::wstring
CEMSFPConfig::_GetDSWSUserEx( const ULONG culPair )
{
	std::wstring wszRet;

	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	// First, Get the DataStreamID.
	ULONG ulDSID = GetDSID( culPair );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"datastream[@id='%d']/proxy/ws/user/username", ulDSID );
	wszRet = oConfig.GetAttributeValue( wszKey );

	return wszRet;
}


std::wstring 
CEMSFPConfig::GetDSWSPassword( const ULONG culPair )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetDSWSPasswordEx( culPair );
	}
	else
	{
		// First, Get the DataStreamID.
		ULONG ulDSID = GetDSID( culPair );

		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszDSProxyWSPwd, ulDSID );

		return m_oConfig.GetElementValue( wszKey );
	}

	return wszRet;
}

std::wstring
CEMSFPConfig::_GetDSWSPasswordEx( const ULONG culPair )
{
	std::wstring wszRet;

	wchar_t wszKey[ 128 ];
	std::wstring				wszDataStrmsConfig;
	CEMSConfigurationAccessor	oConfig;
	
	wszDataStrmsConfig = _GetDataStreamXMLConfig();
	oConfig.SetSource( wszDataStrmsConfig.c_str() );

	// First, Get the DataStreamID.
	ULONG ulDSID = GetDSID( culPair );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"datastream[@id='%d']/proxy/ws/user/password", ulDSID );
	wszRet = oConfig.GetAttributeValue( wszKey );

	return wszRet;
}

std::wstring 
CEMSFPConfig::GetAntennaProxyClassID( const ULONG culAntennaID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetAntennaProxyClassIDEx( culAntennaID );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszAntennaProxyClassID, culAntennaID );

		wszRet = m_oConfig.GetAttributeValue( wszKey );
	}

	return wszRet;
}

std::wstring
CEMSFPConfig::_GetAntControllerXMLConfig()
{
	std::wstring wszRet;
	EMSAntennaClient oAntCL;

	char szXMLConfig[2048];
	memset( szXMLConfig, 0, sizeof( szXMLConfig ) );

	string szSubsystemID = CCBootstrap::GetThisSubsystemId();
	oAntCL.getAntContXMLConfigByFpId(szSubsystemID, szXMLConfig, 2047 );

	wszRet =  CEMSConversionUtil::ConvertToString( szXMLConfig );

	return wszRet;
}


std::wstring 
CEMSFPConfig::_GetAntennaProxyClassIDEx( const ULONG culAntennaID )
{
	std::wstring wszRet;
	std::wstring wszAntControlConfig = _GetAntControllerXMLConfig();

	if( !wszAntControlConfig.empty() )
	{
		CEMSConfigurationAccessor oConfig;
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, L"proxy/@classid" );

		oConfig.SetSource( wszAntControlConfig.c_str() );
		wszRet = oConfig.GetAttributeValue( wszKey );
	}
	return wszRet;
}

std::wstring 
CEMSFPConfig::GetAntennaWSURL( const ULONG culAntennaID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetAntennaWSURLEx( culAntennaID );
	}
	else
	{
		wchar_t wszKey[ 1024 ];
		memset( wszKey, 0, 1024*sizeof(wchar_t) );

		_snwprintf( wszKey, 1023, ms_cwszAntennaProxyWSURL, culAntennaID );

		wszRet = m_oConfig.GetElementValue( wszKey );
	}

	return wszRet;
}

std::wstring 
CEMSFPConfig::_GetAntennaWSURLEx( const ULONG culAntennaID )
{
	std::wstring wszRet;
	std::wstring wszAntControlConfig = _GetAntControllerXMLConfig();

	if( !wszAntControlConfig.empty() )
	{
		CEMSConfigurationAccessor oConfig;
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, L"proxy/ws/url" );

		oConfig.SetSource( wszAntControlConfig.c_str() );
		wszRet = oConfig.GetAttributeValue( wszKey );
	}
	return wszRet;
}

std::wstring 
CEMSFPConfig::GetAntennaWSUser( const ULONG culAntennaID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetAntennaWSUserEx( culAntennaID );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszAntennaProxyWSUser, culAntennaID );

		return m_oConfig.GetElementValue( wszKey );
	}

	return wszRet;
}

std::wstring 
CEMSFPConfig::_GetAntennaWSUserEx( const ULONG culAntennaID )
{
	std::wstring wszRet;
	std::wstring wszAntControlConfig = _GetAntControllerXMLConfig();

	if( !wszAntControlConfig.empty() )
	{
		CEMSConfigurationAccessor oConfig;
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, L"proxy/ws/user/username" );

		oConfig.SetSource( wszAntControlConfig.c_str() );
		wszRet = oConfig.GetAttributeValue( wszKey );
	}
	return wszRet;
}

std::wstring 
CEMSFPConfig::GetAntennaWSPassword( const ULONG culAntennaID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetAntennaWSPasswordEx( culAntennaID );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, ms_cwszAntennaProxyWSPwd, culAntennaID );

		wszRet = m_oConfig.GetElementValue( wszKey );
	}
	
	return wszRet;
}

std::wstring 
CEMSFPConfig::_GetAntennaWSPasswordEx( const ULONG culAntennaID )
{
	std::wstring wszRet;
	std::wstring wszAntControlConfig = _GetAntControllerXMLConfig();

	if( !wszAntControlConfig.empty() )
	{
		CEMSConfigurationAccessor oConfig;
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );

		_snwprintf( wszKey, 127, L"proxy/ws/user/password" );

		oConfig.SetSource( wszAntControlConfig.c_str() );
		wszRet = oConfig.GetAttributeValue( wszKey );
	}
	return wszRet;
}

CEMSObjectList<ULONG>
CEMSFPConfig::GetAntennaIDs()
{
	CEMSObjectList<ULONG> olstRet;

	if( m_bUseConfigWS )
	{
		olstRet = _GetAntennaIDsEx();
	}
	else
	{
		CEMSObjectList<ULONG> oACList = GetAntennaControllers();
		int iCnt = oACList.Count();
		oACList.MoveFirst();

		for( int i = 0; i < iCnt; i++ )
		{
			ULONG ulAC = oACList.GetNext();
		
			CEMSObjectList<ULONG> oAntennaList = GetAntennaIDs(ulAC);

			int iAntCnt = oAntennaList.Count();
			oAntennaList.MoveFirst();

			bool bFESDone = false;

			for( int j = 0; j < iAntCnt; j++ )
			{
				olstRet.Add( oAntennaList.GetNext() );
			}
		}
	}

	return olstRet;
}

CEMSObjectList<ULONG>
CEMSFPConfig::_GetAntennaIDsEx()
{
	CEMSObjectList<ULONG> olstRet;
	EMSAntennaClient oAntCL;

	std::string szAntComp = _GetAntennaComponent();
	EMSAntennaConfig* pAnt = oAntCL.getById(szAntComp);

	if( pAnt )
	{
		olstRet.Add( pAnt->GetAntID() );
		delete pAnt;
		pAnt = NULL;
	}

	return olstRet;
}

CEMSObjectList<ULONG>
CEMSFPConfig::GetAntennaControllers()
{
	CEMSObjectList<ULONG> olstAntennaIDs;

	if( m_bUseConfigWS )
	{
		olstAntennaIDs = _GetAntennaControllersEx();
	}
	else
	{
		CEMSObjectList<CEMSConfigurationAccessor> olstAntennas = m_oConfig.GetAccessorList( ms_cwszAntenna );

		olstAntennas.MoveFirst();

		ULONG ulAntennas = olstAntennas.Count();

		for( ULONG l = 0; l < ulAntennas; l++ )
		{
			olstAntennaIDs.Add( olstAntennas.GetNext().GetAttributeValueULong( ms_cwszID ) );
		}
	}

	return olstAntennaIDs;
}


CEMSObjectList<ULONG>
CEMSFPConfig::_GetAntennaControllersEx()
{
	CEMSObjectList<ULONG> olstRet;
	EMSAntennaClient oAntCL;
	ULONG ulAC = 1;

	std::string szAntComp = _GetAntennaComponent();
	EMSAntennaConfig* pAnt = oAntCL.getById(szAntComp);

	if( pAnt )
	{
		string szAntType = pAnt->GetType();
		if( !szAntType.empty() )
		{
			ulAC = CEMSConversionUtil::ConvertToULong( pAnt->GetType().c_str() );
		}
		
		delete pAnt;
		pAnt = NULL;
	}

	olstRet.Add( ulAC );
	return olstRet;
}

CEMSObjectList<ULONG>
CEMSFPConfig::GetAntennaIDs( const ULONG culAntController )
{
	CEMSObjectList<ULONG> olstAntennaIDs;

	if( m_bUseConfigWS )
	{
		olstAntennaIDs = _GetAntennaIDsEx( culAntController );
	}
	else
	{
		CEMSObjectList<CEMSConfigurationAccessor> olstControllers = m_oConfig.GetAccessorList( ms_cwszAntenna );

		olstControllers.MoveFirst();

		ULONG ulAntennaControllers = olstControllers.Count();
		bool bFound = false;

		for( ULONG l = 0; (l < ulAntennaControllers) && !bFound; l++ )
		{
			CEMSConfigurationAccessor oAntController = olstControllers.GetNext();
			if( oAntController.GetAttributeValueULong( ms_cwszID ) ==  culAntController )
			{
				CEMSObjectList<CEMSConfigurationAccessor> olstAntennas = oAntController.GetAccessorList( ms_cwszAntennas );

				olstAntennas.MoveFirst();

				ULONG ulAntennas = olstAntennas.Count();

				for( ULONG l = 0; l < ulAntennas; l++ )
				{
					olstAntennaIDs.Add( olstAntennas.GetNext().GetAttributeValueULong( ms_cwszID ) );
				}

				bFound = true;
			}
		}
	}

	return olstAntennaIDs;
}

CEMSObjectList<ULONG>
CEMSFPConfig::_GetAntennaIDsEx( const ULONG culAntController )
{
	CEMSObjectList<ULONG> olstRet;

	olstRet = _GetAntennaIDsEx();

	return olstRet;
}

std::wstring 
CEMSFPConfig::GetAntennaConfig( const ULONG culAntennaID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetAntennaConfigEx( culAntennaID );
	}
	else
	{
		// The basic structure of the configuration is this:
		// fpconfig
		//		-->pairs
		//		-->datastreams
		//			-->datastream ...
		//		-->antennacontrollers
		//			-->ac ...
		//		-->satellites
		//			-->satellite ...
		//
		// We need to provide the specific "ac" portion of the tree plus add the "satellites"
		// portion as a child of "ac".  The antenna controller needs the satellite data too.
		// So, we want to return:
		// 
		// ac
		//		-->satellites

		wchar_t wszKey[ 128 ];
	
		memset( wszKey, 0, 128*sizeof(wchar_t) );
		_snwprintf( wszKey, 127, ms_cwszSatellites );

		CEMSConfigurationAccessor oSatsConfig = m_oConfig.GetAccessor( wszKey );
	
		memset( wszKey, 0, 128*sizeof(wchar_t) );
		_snwprintf( wszKey, 127, ms_cwszAntennaConfig, culAntennaID );
		CEMSConfigurationAccessor oACConfig = m_oConfig.GetAccessor( wszKey );

		oACConfig.Attach( &oSatsConfig );

		wszRet = oACConfig.Serialize();
	}
	
	return wszRet;
}

std::wstring  
CEMSFPConfig::_GetAntennaConfigEx( const ULONG culAntennaID )
{
	std::wstring wszRet;
	return wszRet;
}

std::wstring 
CEMSFPConfig::GetDSConfig( const ULONG culDSID )
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetDSConfigEx( culDSID );
	}
	else
	{
		// The basic structure of the configuration is this:
		// fpconfig
		//		-->pairs
		//		-->datastreams
		//			-->datastream ...
		//		-->antennacontrollers
		//			-->ac ...
		//		-->satellites
		//			-->satellite ...
		//
		// We need to provide the specific "datastream" portion of the tree plus add the "satellites"
		// portion as a child of "datastream".  The data collector needs the satellite data too.
		// So, we want to return:
		// 
		// datastream
		//		-->satellites

		wchar_t wszKey[ 128 ];

		memset( wszKey, 0, 128*sizeof(wchar_t) );
		_snwprintf( wszKey, 127, ms_cwszSatellites );
		CEMSConfigurationAccessor oSatsConfig = m_oConfig.GetAccessor( wszKey );

		memset( wszKey, 0, 128*sizeof(wchar_t) );
		_snwprintf( wszKey, 127, ms_cwszDSConfig, culDSID );
		CEMSConfigurationAccessor oDSConfig = m_oConfig.GetAccessor( wszKey );

		oDSConfig.Attach( &oSatsConfig );

		return oDSConfig.Serialize();
	}

	return wszRet;
}

std::wstring  
CEMSFPConfig::_GetDSConfigEx( const ULONG culDSID )
{
	std::wstring wszRet;

	wszRet = _GetDataStreamXMLConfig();

	return wszRet;
}

std::wstring 
CEMSFPConfig::GetScheduleFolder()
{
	std::wstring wszRet;

	if( m_bUseConfigWS )
	{
		wszRet = _GetScheduleFolderEx();
	}
	else
	{
		wszRet = m_oConfig.GetElementValue( ms_cwszScheduleFolder );
	}

	return wszRet;
}

std::wstring  
CEMSFPConfig::_GetScheduleFolderEx()
{
	std::wstring wszRet;

	FPConfig* pFPConfig = NULL;
	MEOSystemClient oSysClient;
	char szXMLConfig[2048];
	memset( szXMLConfig, 0, sizeof( szXMLConfig ) );

	try
	{
		string szSubsystemID = CCBootstrap::GetThisSubsystemId();
		pFPConfig = oSysClient.getFPById( szSubsystemID );
		if( pFPConfig )
		{
			std::string szSchedFolder = pFPConfig->GetSchedFolder();
			wszRet = CEMSConversionUtil::ConvertToString( szSchedFolder.c_str() );
			delete pFPConfig;
			pFPConfig = NULL;
		}
	}
	catch( ... )
	{
		if( pFPConfig )
		{
			delete pFPConfig;
			pFPConfig = NULL;
		}
		throw;
	}

	return wszRet;
}

bool 
CEMSFPConfig::DoesPairExist( const ULONG culPairID  )
{
	bool bRet = false;

	if( m_bUseConfigWS )
	{
		bRet = _DoesPairExistEx( culPairID );
	}
	else
	{
		wchar_t wszKey[ 128 ];
		memset( wszKey, 0, 128*sizeof(wchar_t) );
		_snwprintf( wszKey, 127, ms_cwszPair, culPairID );

		bRet = m_oConfig.DoesNodeExist( wszKey );
	}

	return bRet;
}

bool
CEMSFPConfig::_DoesPairExistEx( const ULONG culPairID )
{
	bool bRet = false;
	wchar_t wszKey[ 128 ];
	std::wstring				wszPairsConfig;
	CEMSConfigurationAccessor	oConfig;
	wszPairsConfig = _GetPairsXMLConfig();
	oConfig.SetSource( wszPairsConfig.c_str() );

	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, L"pair[@id='%d']", culPairID );
	bRet = oConfig.DoesNodeExist( wszKey );

	return bRet;
}


void
CEMSFPConfig::VerifyConfig()
{
	ULONG ulPairID = 1;
	CEMSFPLoader::LoadDatastreamProxy( ulPairID, (*this) );

	//EMSANTDATAPAIR* pAntPair = NULL;
	//ULONG ulPairs = 0;
	//GetList( ulPairs, pAntPair );

	//ULONG ulPairID = 1;
	//GetAntennaID( ulPairID );
	//GetDSID( ulPairID );

	//ULONG ulDSId = 1;
	//GetADBoardID( ulDSId );
	//GetChannelID( ulDSId );

	//GetLutID();

	GetAntennaStatusCheckInterval();
	//GetDSProxyClassID( ulPairID );
	//GetDSWSURL( ulPairID );
	//GetDSWSUser( ulPairID );
	//GetDSWSPassword( ulPairID );
	ULONG culAntennaID = 0;

	//GetAntennaProxyClassID( culAntennaID );
	//GetAntennaWSURL( culAntennaID );
	//GetAntennaWSUser( culAntennaID );
	//GetAntennaWSPassword( culAntennaID );
	GetAntennaIDs();
	GetAntennaControllers();
	GetAntennaIDs( 0 );
	GetAntennaConfig( 0 );

//	GetDSConfig( ulDSId );
//	GetScheduleFolder();
//	DoesPairExist( ulPairID );
}
