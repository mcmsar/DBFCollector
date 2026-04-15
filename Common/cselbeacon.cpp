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


#include "cselbeacon.h"
#include "hexutilis.h"
#include "emsbeaconbase.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>

CEMSCSELBeacon::CEMSCSELBeacon(): m_lCC(0)
{
	memset( m_cBcnMsg, 0, sizeof( m_cBcnMsg ) );
}

CEMSCSELBeacon::CEMSCSELBeacon( const CEMSCSELBeacon& x ) : m_lCC(x.m_lCC)
{
	memcpy( m_cBcnMsg, x.m_cBcnMsg, sizeof(m_cBcnMsg) );
}

CEMSCSELBeacon::CEMSCSELBeacon( const char* cBcnMsg, const int iSize ) :  m_lCC(0)
{
	char* szTemp = NULL;

	try
	{
		// iSize either 18, 30 or 36
		switch( iSize )
		{
		case 36:
			{
				szTemp = strdup( cBcnMsg );
				HexReadEx( szTemp, m_cBcnMsg, 36);
				delete[] szTemp;
				szTemp = NULL;
			}
			break;
		case 30:
			{
				char cHex36Msg[36];
				memset( cHex36Msg, 0, sizeof(char) * 36 );
				memcpy( &(cHex36Msg[6]), cBcnMsg, 30 );
				HexReadEx( cHex36Msg, m_cBcnMsg, 36);
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

CEMSCSELBeacon::~CEMSCSELBeacon()
{
}

bool
CEMSCSELBeacon::Bit( const int iPos ) const
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
CEMSCSELBeacon::Bits( const int iStart, const int iEnd ) const
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

bool	
CEMSCSELBeacon::HasValidEncodedLocation() const
{
	double dLat = 0.0, dLong = 0.0;
	return _CalculateLocation( dLat, dLong );
}

double 
CEMSCSELBeacon::GetLat() const
{
	double dRet = 0.0, dLat = 0.0, dLong = 0.0;

	if( _CalculateLocation( dLat, dLong ) )
	{
		dRet = dLat;
	}

	return dRet;
}

double 
CEMSCSELBeacon::GetLong() const
{
	double dRet = 0.0, dLat = 0.0, dLong = 0.0;

	if( _CalculateLocation( dLat, dLong ) )
	{
		dRet = dLong;
	}

	return dRet;
}


INT64
CEMSCSELBeacon::GetBeaconID() const
{
	INT64 i64BcnId = 0;

	CBeaconMsgBase oMsgBase( m_cBcnMsg );
	i64BcnId = oMsgBase.getBeaconID();	

	return i64BcnId;
}


void
CEMSCSELBeacon::GetHexBeaconId( char* szHexBcnId ) const
{
	if( szHexBcnId )
	{
		_GetHexBeaconId( szHexBcnId, GetBeaconID() );
	}
}

bool
CEMSCSELBeacon::IsCSELBeacon() const
{
	bool bRet = false;

	if( IsUserProtocol() )
	{
		// Does country code match?
		//if( GetCountryCode() == m_lCC )
		{
			// Is it national user protocol?
			if( GetUserProt() == 0x4 )
			{
				// Check system ID.
				int iSystemID = GetSystemId();

				if( 0xC0 == iSystemID ||
					0xC1 == iSystemID ||
					0xC2 == iSystemID ||
					0xC3 == iSystemID )
				{
					bRet = true;
				}
			}
		}
	}
	

	return bRet;
}

void
CEMSCSELBeacon::_GetHexBeaconId( char* szHexBcnId, INT64 i64BcnId ) const
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
CEMSCSELBeacon::_CalculateLocation( double& rdLat, double& rdLong ) const
{
	bool bRet = false;

	if( Bits( 72, 84) != 0xFEF )
	{
		if( !( IsLongMsg() && 
			Bits( 107, 132) == 0x3C0F81F ) )
		{
			bool bNorth = !Bit( 72 );
			bool bEast = !Bit( 80 );

			int iDegreesLat = Bits( 73,79 );
			int iDegreesLong = Bits( 81,84 ) * 16;

			if( iDegreesLat <= 90  )
			{
				if( !IsLongMsg() )
				{
					bRet = true;

					rdLat = iDegreesLat * ( bNorth ? 1.0 : -1.0 );
					rdLong = iDegreesLong * ( bEast ? 1.0 : -1.0 );
				}
				else if( iDegreesLong <= 180  )
				{
					iDegreesLong += Bits( 107, 110 );

					if( iDegreesLong <= 180 )
					{
						int iMinutesLat = Bits( 111, 116 );
						int iSecondsLat = Bits( 117, 121 ) * 2;
						int iMinutesLong = Bits( 122, 127 );
						int iSecondsLong = Bits( 128, 132 ) * 2;

						if( !(	iMinutesLat >= 60 ||
								iMinutesLong >= 60 ||
								iSecondsLat >= 60 ||
								iSecondsLong >= 60 ) )
						{
							bRet = true;

							rdLat = (iDegreesLat + (iMinutesLat/60.0) + (iSecondsLat/3600.00)) * (bNorth ? 1.0 : -1.0 );
							rdLong = (iDegreesLong + (iMinutesLong/60.0) + (iSecondsLong/3600.00)) * ( bEast ? 1.0 : -1.0 );
						}
					}
				}
			}
		}
	}

	return bRet;
}