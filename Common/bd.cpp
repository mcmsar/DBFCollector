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

	$Log:
	$
********************************************************************/
#pragma warning(disable:4786)

#include "bd.h"
#include "emsbeaconbase.h"
#include "seimacbeacon.h"
#include "cselbeacon.h"
#include "cbcnmsgdecodebase.h"
#include "hexutilis.h"

CEMSBD::CEMSBD() : CApiObjBase(TEXT("CEMSBD"))
{
}

CEMSBD::CEMSBD( const CEMSBD& x ) : CApiObjBase(TEXT("CEMSBD")), m_oMLBKeys(x.m_oMLBKeys), 
								m_oCCAccessor(x.m_oCCAccessor)
{
}

CEMSBD::~CEMSBD()
{
}

void 
CEMSBD::Init( const char* cszMLBKeysFile, const char* cszMLBDecryptPwd,
				const char* cszCountryFile, const char* cszCFDecryptPwd )
{
	m_oMLBKeys.Init( cszMLBKeysFile, cszMLBDecryptPwd );
	m_oCCAccessor.Init( cszCountryFile, cszCFDecryptPwd );
}

INT64 
CEMSBD::GetBeaconID( const char* cszBeaconData )
{
	INT64 i64Ret = 0;

	// Get the beacon type.
	EMSBEACONTYPE eType = _GetBeaconType( cszBeaconData );

	if( _IsThisCountryCode( cszBeaconData ) )
	{
		switch( eType )
		{
			case EMSBEACONTYPE_STANDARD:
				i64Ret = _GetStandardBeaconID( cszBeaconData );
				break;
			case EMSBEACONTYPE_MLB:
				i64Ret = _GetMLBBeaconID( cszBeaconData );
				break;
			case EMSBEACONTYPE_CSEL:
				i64Ret = _GetCSELBeaconID( cszBeaconData );
				break;
		}
	}
	else
	{
		i64Ret = _GetStandardBeaconID( cszBeaconData );
	}	

	return i64Ret;
}

EMSBEACONTYPE 
CEMSBD::GetBeaconType( const char* cszBeaconData )
{
	EMSBEACONTYPE eType = EMSBEACONTYPE_UNKNOWN;

	EMSBEACONTYPE eTypeTemp = _GetBeaconType( cszBeaconData );

	if( _IsThisCountryCode( cszBeaconData ) )
	{
		switch( eTypeTemp )
		{
			case EMSBEACONTYPE_STANDARD:
				eType = eTypeTemp;
				break;
			case EMSBEACONTYPE_MLB:
			case EMSBEACONTYPE_CSEL:
				eType = eTypeTemp;
				break;
		}
	}
	else
	{
		eType = EMSBEACONTYPE_STANDARD;
	}

	return eType;
}

EMSBEACONSUMMARY 
CEMSBD::GetBeaconSummary( const char* cszBeaconData )
{
	EMSBEACONSUMMARY strRet;
	memset( &strRet, 0, sizeof(strRet) );

	EMSBEACONTYPE eType = _GetBeaconType( cszBeaconData );

	if( _IsThisCountryCode( cszBeaconData ) )
	{
		switch( eType )
		{
			case EMSBEACONTYPE_STANDARD:
				strRet = _GetStandardBeaconSummary( cszBeaconData );
				break;
			case EMSBEACONTYPE_MLB:
				strRet = _GetMLBBeaconSummary( cszBeaconData );
				break;
			case EMSBEACONTYPE_CSEL:
				strRet = _GetCSELBeaconSummary( cszBeaconData );
				break;
		}
	}
	else
	{
		strRet = _GetStandardBeaconSummary( cszBeaconData );
	}

	return strRet;
}

EMSBEACONTYPE 
CEMSBD::_GetBeaconType( const char* cszBeaconData )
{
	EMSBEACONTYPE eRet = EMSBEACONTYPE_UNKNOWN;

	// Need to check if it's a CSEL before testing if it's an MLB since CSEL's pass the MLB test too.
	CEMSCSELBeacon oCSEL( cszBeaconData, strlen(cszBeaconData ) );

	if( oCSEL.IsCSELBeacon() )
	{
		eRet = EMSBEACONTYPE_CSEL;
	}
	else
	{
		CEMSSeimacBeacon oSeimac( cszBeaconData, strlen(cszBeaconData ) );

		if( oSeimac.IsSeimacBeacon() )
		{
			eRet = EMSBEACONTYPE_MLB;
		}
		else
		{
			eRet = EMSBEACONTYPE_STANDARD;
		}
	}

	return eRet;
}

bool
CEMSBD::_IsThisCountryCode( const char* cszBeaconData )
{
	bool bRet = false;

	// Convert the text representation into binary.
	BYTE abyBcnMsg[18];
	memset( abyBcnMsg, 0, sizeof(abyBcnMsg));
	_GetBeaconMsg( cszBeaconData, abyBcnMsg );

	CBeaconMsgBase oMsg( abyBcnMsg );
	ULONG ulCC = oMsg.getCountryCode();

	bRet = m_oCCAccessor.IsInSet( ulCC );

	return bRet;
}

INT64 
CEMSBD::_GetStandardBeaconID( const char* cszBeaconData )
{
	INT64 i64Ret = 0;

	// Convert the text representation into binary.
	BYTE abyBcnMsg[18];
	memset( abyBcnMsg, 0, sizeof(abyBcnMsg));
	_GetBeaconMsg( cszBeaconData, abyBcnMsg );

	CBeaconMsgBase oMsg( abyBcnMsg );
	i64Ret = oMsg.getBeaconID();

	return i64Ret;
}

INT64 
CEMSBD::_GetMLBBeaconID( const char* cszBeaconData )
{
	INT64 i64Ret = 0;

	CEMSSeimacBeacon oSeimac( cszBeaconData, strlen(cszBeaconData ) );
	i64Ret = oSeimac.GetBeaconID();

	return i64Ret;
}

INT64 
CEMSBD::_GetCSELBeaconID( const char* cszBeaconData )
{
	INT64 i64Ret = 0;

	CEMSCSELBeacon oCSEL( cszBeaconData, strlen(cszBeaconData ) );
	i64Ret = oCSEL.GetBeaconID();

	return i64Ret;
}

EMSBEACONSUMMARY 
CEMSBD::_GetStandardBeaconSummary( const char* cszBeaconData )
{
	EMSBEACONSUMMARY strRet;
	memset( &strRet, 0, sizeof(strRet) );
	strRet.bHasGPSLocation = false;

	// Convert the text representation into binary.
	BYTE abyBcnMsg[18];
	memset( abyBcnMsg, 0, sizeof(abyBcnMsg));
	_GetBeaconMsg( cszBeaconData, abyBcnMsg );
	CBeaconMessage oMsg( abyBcnMsg );

	strRet.i64BeaconID = oMsg.BeaconID();
	strRet.eType = EMSBEACONTYPE_STANDARD;

	CBcnMsgDecodeBase oDecoder;
	oDecoder.Initialize();
	oDecoder.DecodeEx( oMsg );
	oDecoder.GetEncodedLocation( strRet.bHasGPSLocation, strRet.dLat, strRet.dLong );

	return strRet;
}

EMSBEACONSUMMARY 
CEMSBD::_GetMLBBeaconSummary( const char* cszBeaconData )
{
	EMSBEACONSUMMARY strRet;
	memset( &strRet, 0, sizeof(strRet) );
	strRet.bHasGPSLocation = false;

	CEMSSeimacBeacon oBcn( cszBeaconData, strlen(cszBeaconData) );
	strRet.i64BeaconID = oBcn.GetBeaconID();
	strRet.eType = EMSBEACONTYPE_MLB;

	int iLatKey = 0, iLongKey = 0;
	if( m_oMLBKeys.GetKeys( strRet.i64BeaconID, iLatKey, iLongKey ) )
	{
		if( oBcn.GetSeimacBcnLatLong( cszBeaconData, strlen(cszBeaconData), iLatKey, iLongKey,
										&strRet.dLat, &strRet.dLong ) )
		{
			strRet.bHasGPSLocation = true;
		}
	}
	

	return strRet;
}

EMSBEACONSUMMARY 
CEMSBD::_GetCSELBeaconSummary( const char* cszBeaconData )
{
	EMSBEACONSUMMARY strRet;
	memset( &strRet, 0, sizeof(strRet) );

	strRet.bHasGPSLocation = false;

	CEMSCSELBeacon oBcn( cszBeaconData, strlen(cszBeaconData) );
	strRet.i64BeaconID = oBcn.GetBeaconID();
	strRet.eType = EMSBEACONTYPE_CSEL;

	strRet.bHasGPSLocation = oBcn.GetLatLong( strRet.dLat, strRet.dLong );


	return strRet;
}

void 
CEMSBD::_GetBeaconMsg( const char* cszBeaconData, BYTE abyBcnData[18] )
{
	char* szTemp = NULL;

	try
	{
		if( cszBeaconData )
		{
			int iLen = strlen( cszBeaconData );

			switch( iLen )
			{
				case 36:
					szTemp = strdup( cszBeaconData );
					HexReadEx( szTemp, abyBcnData, 36 );
					delete[] szTemp;
					szTemp = NULL;
					break;
				case 30:
					{
						char cHex36Msg[36];
						memset( cHex36Msg, 0, sizeof(char) * 36 );
						memcpy( &(cHex36Msg[6]), cszBeaconData, 30 );
						HexReadEx( cHex36Msg, abyBcnData, 36 );
					}
					break;
				case 18:
					memcpy( abyBcnData, cszBeaconData, iLen );
					break;
				default:
					memset( abyBcnData, 0, sizeof(abyBcnData) );
			}
		}
	}
	catch( ... )
	{
		if( szTemp )
		{
			delete[] szTemp;
			szTemp = NULL;
		}

		throw;
	}
}
