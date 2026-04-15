/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/
#pragma warning(disable:4786)


#include "mlbkeyaccessor.h"
#include "configurationaccessor.h"
#include "convutility.h"

const wchar_t* CEMSMLBKeyAccessor::ms_cwszBeacon = L"beacon";
const wchar_t* CEMSMLBKeyAccessor::ms_cwszID = L"@id";
const wchar_t* CEMSMLBKeyAccessor::ms_cwszLat = L"lat";
const wchar_t* CEMSMLBKeyAccessor::ms_cwszLong = L"long";

CEMSMLBKeyAccessor::CEMSMLBKeyAccessor() : m_bLoadAttempted(false)
{
}

CEMSMLBKeyAccessor::CEMSMLBKeyAccessor( const CEMSMLBKeyAccessor& x ) : m_oszKeyFile(x.m_oszKeyFile),
																		m_oszPwd(x.m_oszPwd),
																		m_omapKeys(x.m_omapKeys),
																		m_bLoadAttempted(x.m_bLoadAttempted)
{
}

CEMSMLBKeyAccessor::~CEMSMLBKeyAccessor()
{
}

void 
CEMSMLBKeyAccessor::Init( const char* cszKeyFile, const char* cszPwd )
{
	if( cszKeyFile )
	{
		m_oszKeyFile = cszKeyFile;
	}

	if( cszPwd )
	{
		m_oszPwd = cszPwd;
	}

	m_omapKeys.Clear();
	m_bLoadAttempted = false;
}

bool 
CEMSMLBKeyAccessor::GetKeys( const INT64 ci64BeaconID, int& riLatKey, int& riLongKey )
{
	bool bRet = false;

	_LoadMap();

	if( m_omapKeys.IsInMap( ci64BeaconID ) )
	{
		LATLONGPAIR strLatLong;
		memset( &strLatLong, 0, sizeof(strLatLong) );
		strLatLong = m_omapKeys.Get( ci64BeaconID );

		riLatKey = strLatLong.iLat;
		riLongKey = strLatLong.iLong;

		bRet = true;
	}

	return bRet;
}

void 
CEMSMLBKeyAccessor::_LoadMap()
{
	// The map is only loaded once.  That is, the file will only be read the first time this method
	// is called.

	try
	{
		m_ocsMapLoad.Enter();

		if( !m_bLoadAttempted )
		{
			m_bLoadAttempted = true;

			if( !m_oszKeyFile.empty() )
			{
				CEMSConfigurationAccessor oConfig;
				oConfig.SetSourceFile( CEMSConversionUtil::ConvertToString( m_oszKeyFile.c_str() ).c_str() );

				CEMSObjectList<CEMSConfigurationAccessor> olstBeacons = oConfig.GetAccessorList( ms_cwszBeacon );
				olstBeacons.MoveFirst();
				ULONG ulBeacons = olstBeacons.Count();

				for( ULONG l = 0; l < ulBeacons; l++ )
				{
					CEMSConfigurationAccessor oBeaconConfig = olstBeacons.GetNext();

					LATLONGPAIR strLatLong;
					memset( &strLatLong, 0, sizeof(strLatLong) );

					INT64 i64BeaconID = oBeaconConfig.GetAttributeValueHexI64( ms_cwszID );
					strLatLong.iLat = oBeaconConfig.GetElementValueInt( ms_cwszLat );
					strLatLong.iLong = oBeaconConfig.GetElementValueInt( ms_cwszLong );

					m_omapKeys.Add( i64BeaconID, strLatLong );

				}
			}

		}

		m_ocsMapLoad.Leave();
	}
	catch( ... )
	{
		m_ocsMapLoad.Leave();
		throw;
	}

}