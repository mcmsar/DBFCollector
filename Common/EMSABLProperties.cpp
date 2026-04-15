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
#pragma warning(disable : 4786)


#include "emsablproperties.h"
#include "emsencod.h"
#include "emsexcpt.h"
#include "EMSBEACON.h"
#include "emscoord.h"
#include "configurationaccessor.h"
#include "convutility.h"
#include <emsdomnode.h>

#define MAX_ABL_LUTS_PROPERTIES 24
#define MAX_ABL_SATS_PROPERTIES 24
#define MAX_ABL_LOCATIONS_TYPES_PROPERTIES 16
#define MAX_ABL_BEACONS_PROPERTIES 32
#define MAX_ABL_COUNTRYCODE_TYPES_PROPERTIES 24
#define MAX_ABL_PROTOCOL_PROPERTIES 16


const wchar_t* CEMSABLProperties::ms_cwszID = L"@ID";

const wchar_t* CEMSABLProperties::ms_cwszLUTS = L"LUTS";
const wchar_t* CEMSABLProperties::ms_cwszLUT = L"LUT";

const wchar_t* CEMSABLProperties::ms_cwszSATS = L"SATS";
const wchar_t* CEMSABLProperties::ms_cwszSAT = L"SAT";

const wchar_t* CEMSABLProperties::ms_cwszLocationTypes = L"LocationTypes";
const wchar_t* CEMSABLProperties::ms_cwszLocationType = L"LcnType";

const wchar_t* CEMSABLProperties::ms_cwszBeacons = L"Beacons";
const wchar_t* CEMSABLProperties::ms_cwszBeacon = L"Beacon";

const wchar_t* CEMSABLProperties::ms_cwszCountryCodes = L"CountryCodes";
const wchar_t* CEMSABLProperties::ms_cwszCountryCode = L"CC";
const wchar_t* CEMSABLProperties::ms_cwszCode = L"@Code";

const wchar_t* CEMSABLProperties::ms_cwszProtocols = L"Protocols";
const wchar_t* CEMSABLProperties::ms_cwszProtocol = L"Protocol";
const wchar_t* CEMSABLProperties::ms_cwszType = L"@Type";

const wchar_t* CEMSABLProperties::ms_cwszEnabled = L"Enabled";
const wchar_t* CEMSABLProperties::ms_cwszShortMessage = L"ShortMessage";
const wchar_t* CEMSABLProperties::ms_cwszMaxCapacity = L"MaxCapacity";
const wchar_t* CEMSABLProperties::ms_cwszMinRawDataPerAB = L"MinRawDataPerAB";
const wchar_t* CEMSABLProperties::ms_cwszLUTID = L"LUTID";
const wchar_t* CEMSABLProperties::ms_cwszLocationRadius = L"LocationRadius";
const wchar_t* CEMSABLProperties::ms_cwszOrbDetError = L"OrbitDeterminationError";
const wchar_t* CEMSABLProperties::ms_cwszSDEL = L"SDEL";
const wchar_t* CEMSABLProperties::ms_cwszLocationLatitude = L"LocationLatitude";
const wchar_t* CEMSABLProperties::ms_cwszLocationLongitude = L"LocationLongitude";
const wchar_t* CEMSABLProperties::ms_cwszLocationAltitude = L"LocationAltitude";
const wchar_t* CEMSABLProperties::ms_cwszFloatRate = L"FloatRate";


CEMSABLProperties::CEMSABLProperties()
{
   memset( &m_ABLProperiesData, 0, sizeof( EMSABLProperties ) );
   m_ABLProperiesData.dLocationRadius = 100.0; //default value.
}


CEMSABLProperties::CEMSABLProperties( const EMSABLProperties& cConfig )
{
   memcpy( &m_ABLProperiesData, &cConfig, sizeof( EMSABLProperties ) );
}


CEMSABLProperties::CEMSABLProperties( const CEMSABLProperties& x )
{

   memcpy( &m_ABLProperiesData, &x.m_ABLProperiesData, sizeof( EMSABLProperties ) );
}


CEMSABLProperties::~CEMSABLProperties()
{
}

EMS_RESULT 
CEMSABLProperties::InitXml( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;
	CEMSDOMNode* pNode = NULL;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		try
		{
			CEMSConfigurationAccessor oABLProp;
			std::wstring wszValue;

			oABLProp.SetSource( cwszXMLString );
			wszValue = oABLProp.GetElementValue( CEMSABLProperties::ms_cwszID );

			m_ABLProperiesData.ulABLID = CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );

			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszLUTS );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseLUTS( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}
			
			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszSATS );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseSATS( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}

			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszLocationTypes );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseLcnTypes( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}

			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszBeacons );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseBeacons( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}

			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszCountryCodes );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseCC( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}

			pNode = oABLProp.GetNode( CEMSABLProperties::ms_cwszProtocols );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseProtocols( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
			}

			m_ABLProperiesData.bEnabled = oABLProp.GetAttributeValueBoolean( CEMSABLProperties::ms_cwszEnabled );
			m_ABLProperiesData.bIsShortMessage = oABLProp.GetAttributeValueBoolean( CEMSABLProperties::ms_cwszShortMessage );
			m_ABLProperiesData.ulMaxCapacity = oABLProp.GetAttributeValueULong( CEMSABLProperties::ms_cwszMaxCapacity );
			m_ABLProperiesData.ulMinRawDataPerAB = oABLProp.GetAttributeValueULong( CEMSABLProperties::ms_cwszMinRawDataPerAB );
			m_ABLProperiesData.ulLUTID = oABLProp.GetAttributeValueULong( CEMSABLProperties::ms_cwszLUTID );
			m_ABLProperiesData.dLocationRadius = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszLocationRadius );
			m_ABLProperiesData.dOrbDetError = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszOrbDetError );
			m_ABLProperiesData.dSDEL = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszSDEL );

			m_ABLProperiesData.currentLocation.degLatitude = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszLocationLatitude );
			m_ABLProperiesData.currentLocation.degLongitude = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszLocationLongitude );
			m_ABLProperiesData.currentLocation.fAltitude = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszLocationAltitude );
			
			m_ABLProperiesData.dFloatRate = oABLProp.GetElementValueFloat( CEMSABLProperties::ms_cwszFloatRate );
		}
		catch( ... )
		{
			if( pNode )
			{
				pNode->Release();
				pNode = NULL;
			}

			throw;
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseLUTS( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oLUTS;
		
		oLUTS.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oLUTS.GetAccessorList( CEMSABLProperties::ms_cwszLUT );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oLUT = oConfigAccessList.GetNext();

			wszValue = oLUT.GetElementValue( CEMSABLProperties::ms_cwszID );

			m_ABLProperiesData.aulLuts[l] = CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseSATS( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oSATS;
		
		oSATS.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oSATS.GetAccessorList( CEMSABLProperties::ms_cwszSAT );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oSAT = oConfigAccessList.GetNext();

			wszValue = oSAT.GetElementValue( CEMSABLProperties::ms_cwszID );

			m_ABLProperiesData.aulSats[l] = CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseLcnTypes( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oLcnTypes;
		
		oLcnTypes.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oLcnTypes.GetAccessorList( CEMSABLProperties::ms_cwszLocationType );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oLcnType = oConfigAccessList.GetNext();

			wszValue = oLcnType.GetElementValue( CEMSABLProperties::ms_cwszID );

			m_ABLProperiesData.aLocationTypes[l] = (EMSLOCATETYPE)CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseBeacons( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oBeacons;
		
		oBeacons.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oBeacons.GetAccessorList( CEMSABLProperties::ms_cwszBeacon );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oBeacon = oConfigAccessList.GetNext();

			wszValue = oBeacon.GetElementValue( CEMSABLProperties::ms_cwszID );

			m_ABLProperiesData.ai64Beacons[l] = CEMSConversionUtil::ConvertHexStringToInt64( wszValue.c_str() );
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseCC( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oCCs;
		
		oCCs.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oCCs.GetAccessorList( CEMSABLProperties::ms_cwszCountryCode );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oCC = oConfigAccessList.GetNext();

			wszValue = oCC.GetElementValue( CEMSABLProperties::ms_cwszCode );

			m_ABLProperiesData.aiCountryCode[l] = CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );
		}
	}

	return hr;
}

EMS_RESULT 
CEMSABLProperties::_ParseProtocols( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oProtocols;
		
		oProtocols.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oProtocols.GetAccessorList( CEMSABLProperties::ms_cwszProtocol );

		oConfigAccessList.MoveFirst();

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < MAX_ABL_LUTS_PROPERTIES); l++ )
		{
			CEMSConfigurationAccessor oProtocol = oConfigAccessList.GetNext();

			wszValue = oProtocol.GetElementValue( CEMSABLProperties::ms_cwszType );

			m_ABLProperiesData.aiProtocolType[l] = CEMSConversionUtil::ConvertToULong( wszValue.c_str(), 10 );
		}
	}

	return hr;
}

void
CEMSABLProperties::SetProperties( const EMSABLProperties& cABLProperties )
{
	memcpy( &m_ABLProperiesData, &cABLProperties, sizeof( EMSABLProperties ) );
}


bool 
CEMSABLProperties::IsMatchingProperties( EMSLOCATE* pLocate )
{
	bool bRet = false;
	
	if( pLocate )
	{
/*		bRet = _MatchLutID( pLocate->ulLutID ) && _MatchSatID( pLocate->cSatIDs, sizeof( pLocate->cSatIDs ) ) &&
			   _MatchLocationType( pLocate->wType ) && _MatchBeaconID( pLocate->i64BeaconID ) &&
			   _MatchCountryCode( pLocate ) && _MatchProtocolType( pLocate ) && _MatchMsgLength( pLocate ) &&
			   _WithinLcnRadius( pLocate );
*/

		// for now always return true;
		bRet = true;
	}
	
	return bRet;
}


EMSABLProperties 
CEMSABLProperties::GetConfig()
{
	return m_ABLProperiesData;
}

void 
CEMSABLProperties::GetConfigSats( std::list<ULONG>& lstSats )
{ 
	for( int i = 0; i < MAX_ABL_SATS_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.aulSats[i] ) )
		{
			lstSats.push_back( m_ABLProperiesData.aulSats[i] );
		}
	}
}


void 
CEMSABLProperties::GetConfigLuts( std::list<ULONG>& lstLuts ) 
{ 
	for( int i = 0; i < MAX_ABL_LUTS_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.aulLuts[i] ) )
		{		
			lstLuts.push_back( m_ABLProperiesData.aulLuts[i] );
		}
	}
}


void
CEMSABLProperties::GetConfigBeacons( std::list<INT64>& lstBeacons ) 
{ 
	for( int i = 0; i < MAX_ABL_BEACONS_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.ai64Beacons[i] ) )
		{		
			lstBeacons.push_back( m_ABLProperiesData.ai64Beacons[i] );
		}
	}
}


void
CEMSABLProperties::GetConfigCCids( std::list<int>& lstCCids )
{ 
	for( int i = 0; i < MAX_ABL_COUNTRYCODE_TYPES_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.aiCountryCode[i] ) )
		{		
			lstCCids.push_back( m_ABLProperiesData.aiCountryCode[i] );
		}
	}
}

void 
CEMSABLProperties::GetConfigLocTypes( std::list<EMSLOCATETYPE>& lstLocTypes )
{
	for( int i = 0; i < MAX_ABL_LOCATIONS_TYPES_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.aLocationTypes[i] ) )
		{		
			lstLocTypes.push_back( m_ABLProperiesData.aLocationTypes[i] );
		}
	}
}

void 
CEMSABLProperties::GetConfigProtTypes( std::list<int>& lstProtTypes )
{
	for( int i = 0; i < MAX_ABL_PROTOCOL_PROPERTIES; i++ )
	{
		if( !( 0 == m_ABLProperiesData.aiProtocolType[i] ) )
		{		
			lstProtTypes.push_back( m_ABLProperiesData.aiProtocolType[i] );
		}
	}
}

bool
CEMSABLProperties::_MatchLutID( ULONG ulLutID )
{
	bool bRet = false;
	if( ulLutID == m_ABLProperiesData.ulLUTID )
	{
		bRet = true;
	}
	else if( 0 == m_ABLProperiesData.aulLuts[0] )
	{
		bRet = true;
	}
	else
	{
		for( int i = 0; (i < MAX_ABL_LUTS_PROPERTIES) && !bRet; i++ )
		{
			if( ulLutID == m_ABLProperiesData.aulLuts[i] )
			{
				bRet = true;
			}
		}
	}

	return bRet;
}

bool
CEMSABLProperties::_MatchSatID( BYTE* abSatIDs, int iSize )
{
	bool    bRet = false;
	BYTE    abSatIds[16];
	ULONG   ulTemp = 0;
	ULONG*  aulSatId = NULL;

	if( 0 == m_ABLProperiesData.aulSats[0] )
	{
		bRet = true;
	}
	else if( (0 < iSize) && (sizeof( abSatIds ) <= iSize) )
	{
		memcpy( abSatIds, abSatIDs, sizeof( abSatIds ) );
		aulSatId = new ULONG[iSize];

		if( !aulSatId )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		CEMSEncodedSatID::Expand( &abSatIds, aulSatId, iSize, &ulTemp );

		if( ulTemp )
		{
			for( int i = 0; i < ulTemp; i++ )
			{
				for( int j = 0; j < MAX_ABL_SATS_PROPERTIES && !bRet; j++ )
				{
					if( aulSatId[i] == m_ABLProperiesData.aulSats[j] )
					{
						bRet = true;
					}
				}
			}
		}
		else
		{
			bRet = true;
		}

		delete []aulSatId;
	}

	return bRet;
}

bool
CEMSABLProperties::_MatchLocationType( WORD wType )
{
	bool bRet = false;

	if( 0 == m_ABLProperiesData.aLocationTypes[0] )
	{
		bRet = true;
	}
	else
	{
		for( int i = 0; (i < MAX_ABL_LOCATIONS_TYPES_PROPERTIES) && !bRet ; i++ )
		{
			if( wType == m_ABLProperiesData.aLocationTypes[i] )
			{
				bRet = true;
			}
		}
	}

	return bRet;
}

bool 
CEMSABLProperties::_MatchBeaconID( INT64 i64BeaconID )
{
	bool bRet = false;

	if( 0 == m_ABLProperiesData.ai64Beacons[0] )
	{
		bRet = true;
	}
	else
	{
		for( int i = 0; (i < MAX_ABL_BEACONS_PROPERTIES) && !bRet ; i++ )
		{
			if( i64BeaconID == m_ABLProperiesData.ai64Beacons[i] )
			{
				bRet = true;
			}
		}
	}

	return bRet;
}

bool
CEMSABLProperties::_MatchCountryCode( EMSLOCATE* pLocate )
{
	bool bRet = false;

	if( pLocate )
	{
		if( (pLocate->wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) // TBV
		{
			if( 0 == m_ABLProperiesData.aiCountryCode[0] )
			{
				bRet = true;
			}
			else
			{
				CBeaconMsg oBcnMsg( pLocate->info.rec406.cBeaconMsg );
				ULONG      ulCntCode = oBcnMsg.getCountryCode();

				for( int i = 0; (i < MAX_ABL_COUNTRYCODE_TYPES_PROPERTIES) && !bRet; i++ )
				{
					if( ulCntCode == m_ABLProperiesData.aiCountryCode[i] )
					{
						bRet = true;
					}
				}
			}
		}
	}
	
	return bRet;
}

bool 
CEMSABLProperties::_MatchProtocolType( EMSLOCATE* pLocate )
{
	bool bRet = false;

	if( pLocate )
	{
		if( (pLocate->wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) // TBV
		{
			if( 0 == m_ABLProperiesData.aiProtocolType[0] )
			{
				bRet = true;
			}
			else
			{
				CBeaconMsg oBcnMsg( pLocate->info.rec406.cBeaconMsg );
				ULONG      ulCntCode = oBcnMsg.getProtocolCode();

				for( int i = 0; (i < MAX_ABL_PROTOCOL_PROPERTIES) && !bRet; i++ )
				{
					if( ulCntCode == m_ABLProperiesData.aiProtocolType[i] )
					{
						bRet = true;
					}
				}
			}
		}
	}
	
	return bRet;
}


bool
CEMSABLProperties::_MatchMsgLength( EMSLOCATE* pLocate )
{
	bool bRet = true;

	if( pLocate )
	{
		if( (pLocate->wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) // TBV
		{
			CBeaconMsg oBcnMsg( pLocate->info.rec406.cBeaconMsg );

			bRet = (m_ABLProperiesData.bIsShortMessage != oBcnMsg.getFormatFlag());
		}
	}
	
	return bRet;
}


bool
CEMSABLProperties::_WithinLcnRadius( EMSLOCATE* pLocate )
{
	bool bRet = false;

	if( pLocate )
	{
		if( ( (0.0 == m_ABLProperiesData.currentLocation.degLatitude) &&
			  (0.0 == m_ABLProperiesData.currentLocation.degLongitude) &&
			  (0.0 == m_ABLProperiesData.currentLocation.fAltitude) ) ||
			( 0.0 >= m_ABLProperiesData.dLocationRadius) )
		{
			bRet = true;
		}
		else
		{
			double  dDistApart = 0.0;

			CEMSCoordSystem  oCoordSys;

			if( 0.0 > m_ABLProperiesData.dLocationRadius )
			{
				m_ABLProperiesData.dLocationRadius *= -1.0;
			}

			dDistApart = oCoordSys.DistanceApart( pLocate->wlsSolution.location, m_ABLProperiesData.currentLocation );
			if( dDistApart <= m_ABLProperiesData.dLocationRadius )
			{
				bRet = true;
			}
		}
	}
	
	return bRet;
}
