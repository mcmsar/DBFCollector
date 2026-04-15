/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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


#include "seimacbeacon.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

CEMSSeimacBeacon::CEMSSeimacBeacon(): m_dLat(0.0), m_dLong(0.0)
{
	memset( m_cBcnMsg, 0, sizeof( unsigned char ) * 18 );
}

CEMSSeimacBeacon::CEMSSeimacBeacon( const char* cBcnMsg, 
								    const int iSize ): m_dLat(0.0), 
									                   m_dLong(0.0)
{
	// iSize either 18, 30 or 36
	switch( iSize )
	{
	case 36:
		{
			_ReadHexString( cBcnMsg, m_cBcnMsg, 36);
		}
		break;
	case 30:
		{
			char cHex36Msg[36];
			memset( cHex36Msg, 0, sizeof(char) * 36 );
			memcpy( &(cHex36Msg[6]), cBcnMsg, 30 );
			_ReadHexString( cHex36Msg, m_cBcnMsg, 36);
		}
		break;
	case 18:
		{
			memcpy( m_cBcnMsg, cBcnMsg, iSize );
		}
		break;
	default:
		{
			memset( m_cBcnMsg, 0, sizeof( unsigned char ) * 18 );
		}
	}
}

CEMSSeimacBeacon::~CEMSSeimacBeacon()
{
}

bool
CEMSSeimacBeacon::Bit( const int iPos )
{
	int iByteIdx = 0;
	int iBitIdx = iPos;

	if( iPos > 144 )
	{
		return false;
	}

	while( iBitIdx > 8 )
	{
		iBitIdx -= 8;
		iByteIdx++;
	}

	iBitIdx = 8 - iBitIdx;

	return ( m_cBcnMsg[iByteIdx] >> iBitIdx ) & 1;
}

int
CEMSSeimacBeacon::Bits( const int iStart, const int iEnd )
{
	int iRet = 0;

	for( int i = iStart; i <= iEnd; i++ )
	{
		iRet <<= 1;
		if( Bit( i ) )
		{
			iRet++;
		}
	}

	return iRet;
}

__int64
CEMSSeimacBeacon::GetBeaconID()
{
	__int64 i64BcnId = 0;

	*( ((long*)&i64BcnId) + 1 ) = Bits( 26, 53 );
	*( (long*)&i64BcnId ) = Bits( 54, 85 );

	if( IsSeimacBeacon() )
	{
		i64BcnId &= 0xFFFFFFFFFFF80000;

		i64BcnId |= 0x7FFFF;
	}

	return i64BcnId;
}


void
CEMSSeimacBeacon::GetHexBeaconId( char* szHexBcnId )
{
	if( szHexBcnId )
	{
		_GetHexBeaconId( szHexBcnId, GetBeaconID() );
	}
}

void
CEMSSeimacBeacon::_GetHexBeaconId( char* szHexBcnId, __int64 i64BcnId )
{
	if( szHexBcnId )
	{
		memset( szHexBcnId, 0, 16*sizeof(char) );

		_ui64toa( i64BcnId, szHexBcnId, 16 );

		for( int i = 0; i < 15; i++ )
		{
			szHexBcnId[i] = toupper( szHexBcnId[i] );
			if( szHexBcnId[i] ==  ' ' )
			{
				szHexBcnId[i] = '0';
			}
		}
	}
}

bool
CEMSSeimacBeacon::IsSeimacBeacon()
{
	return ( Bit(25) && Bit(26) && (Bits(37,39) == 4) );
}

void
CEMSSeimacBeacon::CalculateLatLong( int iLatKey, int iLongKey )
{
	int iLat = 0;
	int iLong = 0;

	m_dLat = 0.0;
	m_dLong = 0.0;

	bool bPositionBits[45];
	int j = 0;

	for( int i = 67; (i <= 85) && (j < 45); i++ )
	{
		if( Bit( i ) )
		{
			bPositionBits[j++] = true;
		}
		else
		{
			bPositionBits[j++] = false;
		}
	}

	for( i = 107; (i <= 132) && (j < 45); i++ )
	{
		if( Bit( i ) )
		{
			bPositionBits[j++] = true;
		}
		else
		{
			bPositionBits[j++] = false;
		}
	}

	for( j = 0; j < 45; j +=2 )
	{
        iLong <<= 1;
        if( bPositionBits[j] )
        {
            iLong++;
        }
	}

	for( j = 1; j < 45; j +=2 )
	{
        iLat <<= 1;
        if( bPositionBits[j] )
        {
            iLat++;
        }
	}

	if( 0 == iLat )
	{
		iLatKey = 0;
		iLongKey = 0;
	}

	m_dLat = ((double)(iLat - iLatKey)) * 180.0 / pow(2,22) - 90.0;

	if( m_dLat < -90.0 )
	{
		m_dLat += 180.0;
	}

	if( m_dLat > 90.0 )
	{
		m_dLat -= 180.0;
	}

	m_dLong = ((double)(iLong - iLongKey)) * 360.0 / pow(2,23) - 180.0;

	if( m_dLong < -180.0) 
	{
		m_dLong += 360.0;
	}

	if( m_dLong > 180.0 )
	{
		m_dLong -= 360.0;
	}

	m_dLong = -m_dLong;
}

void
CEMSSeimacBeacon::CalculateLatLong( const char* szHexLatKey, const char* szHexLongKey )
{
	int iLatKey = 0;
	int iLongKey = 0;

	if( szHexLatKey && szHexLongKey )
	{
		iLatKey = strtoul( szHexLatKey, 0, 16 );
		iLongKey = strtoul( szHexLongKey, 0, 16 );
	}

	CalculateLatLong( iLatKey, iLongKey );
}


bool
CEMSSeimacBeacon::GetSeimacBcnLatLong( const char* cBcnMsg, const int iSize,
									   int iLatKey, int iLongKey,
									   double* pdLat, double* pdLong )
{
	CEMSSeimacBeacon oSeimacBcn( cBcnMsg, iSize );
	bool bRet = ( pdLat && pdLong && oSeimacBcn.IsSeimacBeacon() );

	if( bRet )
	{
		oSeimacBcn.CalculateLatLong( iLatKey, iLongKey );
		*pdLat = oSeimacBcn.GetLat();
		*pdLong = oSeimacBcn.GetLong();
	}

	return bRet;
}

bool
CEMSSeimacBeacon::GetSeimacBcnLatLong( const char* cBcnMsg, const int iSize,
									   const char* szHexLatKey, const char* szHexLongKey,
									   double* pdLat, double* pdLong )
{
	CEMSSeimacBeacon oSeimacBcn( cBcnMsg, iSize );
	bool bRet = ( pdLat && pdLong && oSeimacBcn.IsSeimacBeacon() );

	if( bRet )
	{
		oSeimacBcn.CalculateLatLong( szHexLatKey, szHexLongKey );
		*pdLat = oSeimacBcn.GetLat();
		*pdLong = oSeimacBcn.GetLong();
	}

	return bRet;
}

void
CEMSSeimacBeacon::_ReadHexString( const char* Hex, void* pBuffer, int iLength )
{
    unsigned char* ptr = (unsigned char*)pBuffer;

    for( int i = 0; i < iLength; i += 2 )
    {
        *ptr = (unsigned char)((_GetHexChar( Hex[i] ) << 4) + _GetHexChar( Hex[i+1] ));
        ptr++;
    }
}

int
CEMSSeimacBeacon::_GetHexChar( char cHexChar )
{
    switch( cHexChar )
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return cHexChar - '0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return cHexChar - 'A' + 10;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return cHexChar - 'a' + 10;
        default:
			return -1;
    }
}

