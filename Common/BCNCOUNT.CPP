/********************************************************************
*	Module:			bcncount.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	CEMSBeaconCounter 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003/03/30	rvw	start

********************************************************************/
#include <string.h>

#include "bcncount.h"
#include "emsclock.h"

CEMSBeaconCounter::CEMSBeaconCounter( int nMaxCount /* = 1000 */ )
{
	m_lpi64BeaconID = 0;
	m_nCurrCount = m_nMaxCount = 0;

	if ( nMaxCount )
	{
		m_lpi64BeaconID = new INT64[ nMaxCount ];

		if ( m_lpi64BeaconID )
		{
			m_nMaxCount = nMaxCount;

			memset( m_lpi64BeaconID, 0, sizeof( INT64 ) * nMaxCount );
		}
	}
}

CEMSBeaconCounter::~CEMSBeaconCounter( )
{
	if ( m_lpi64BeaconID )
	{
		delete [ ] m_lpi64BeaconID;
		m_lpi64BeaconID = 0;
	}
}

void CEMSBeaconCounter::Reset( void )
{
	if ( m_lpi64BeaconID && m_nMaxCount )
	{
	 	memset( m_lpi64BeaconID, 0, sizeof( INT64 ) * m_nMaxCount );
	}
	m_nCurrCount = 0;
}

EMS_RESULT CEMSBeaconCounter::_Reset( INT nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpi64BeaconID && ( nIndex >= 0 ) && ( nIndex < m_nMaxCount ) )
	{
		if ( m_lpi64BeaconID[ nIndex ] )
		{
			if ( m_nCurrCount > 0 )
				m_nCurrCount--;

			m_lpi64BeaconID[ nIndex ] = 0;
		}
		else
			hr = EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSBeaconCounter::AddBeacon( INT64 i64BeaconID )
{
	EMS_RESULT hr = EMS_OK;

//	Tickets 6090/25169: Zero can actually be a valid identifier!
//	if ( i64BeaconID )
	{
		bool bAdded = false;

		for ( int i = 0; ( i < m_nMaxCount ) && !bAdded; i++ )
		{
			if ( 0 == m_lpi64BeaconID[i] )
			{
				m_lpi64BeaconID[i] = i64BeaconID;

				m_nCurrCount++;

				bAdded = true;
			}
			else if ( i64BeaconID == m_lpi64BeaconID[i] )
			{
				bAdded = true;
			}
		}
		hr = ( bAdded ) ? EMS_OK : EMS_FALSE;
	}
//	else
//		hr = EMS_BAD_PARAM;

	return hr;
}

INT64 CEMSBeaconCounter::GetBeaconID( INT nIndex )
{
	INT64 i64BeaconID = 0;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nMaxCount ) && m_lpi64BeaconID )
		i64BeaconID = m_lpi64BeaconID[ nIndex ];

	return i64BeaconID;
}

INT CEMSBeaconCounter::_GetBeaconIndex( INT64 i64BeaconID )
{	
	INT nIndex = -1;

	if ( i64BeaconID && m_lpi64BeaconID )
	{
		for ( int i = 0; ( i < m_nMaxCount ) && ( -1 == nIndex ); i++ )
		{
			if ( i64BeaconID == m_lpi64BeaconID[i] )
			{
				nIndex = i;
			}
		}
	}

	return nIndex;
}

INT CEMSBeaconCounter::GetCount( void )
{
	INT nCount = 0;

	for ( int i = 0; i < m_nMaxCount; i++ )
	{
		if ( m_lpi64BeaconID[i] > 0 )
		{
			nCount++;
		}
	}
	return nCount;
}

bool CEMSBeaconCounter::TestBeacon( INT64 i64BeaconID )
{
	return ( _GetBeaconIndex( i64BeaconID ) >= 0 );
}

CEMSBeaconTimeCounter::CEMSBeaconTimeCounter( int nMaxCount /* = 1000 */ )
	: CEMSBeaconCounter( nMaxCount )
{
	m_lpTimeRef = 0;

	m_updateMode = EMSBTC_UpdateDefault;

	if ( nMaxCount )
	{
		m_lpTimeRef = new EMSTIME[ nMaxCount ];

		if ( m_lpTimeRef )
		{
			memset( m_lpTimeRef, 0, sizeof( EMSTIME ) * nMaxCount );
		}
	}
}

CEMSBeaconTimeCounter::~CEMSBeaconTimeCounter( )
{
	if ( m_lpTimeRef )
	{
		delete [ ] m_lpTimeRef;
		m_lpTimeRef = 0;
	}
}

void CEMSBeaconTimeCounter::Reset( void )
{
	if ( m_lpTimeRef && GetMaxCount() )
	{
	 	memset( m_lpTimeRef, 0, sizeof( EMSTIME ) * GetMaxCount() );
	}
	CEMSBeaconCounter::Reset();
}

INT CEMSBeaconTimeCounter::Reset( EMSTIME timeStart )
{
	INT nRemoved = 0;

	if ( m_lpTimeRef && GetMaxCount() )
	{
		for ( int i = 0; i < GetMaxCount( ); i++ )
 		{
			if ( m_lpTimeRef[i].intTime < timeStart.intTime )
			{
				if ( EMS_OK == _Reset( i ) )
					nRemoved++;

				m_lpTimeRef[i].intTime = 0;
			}
		}
	}
	return nRemoved;
}

EMS_RESULT CEMSBeaconTimeCounter::AddBeacon( INT64 i64BeaconID )
{
	return AddBeacon( i64BeaconID, CEMSSystemClock::GetTime( ) );	
}

EMS_RESULT CEMSBeaconTimeCounter::AddBeacon( INT64 i64BeaconID, EMSTIME timeRef )
{
	EMS_RESULT hr = EMS_OK;

	hr = CEMSBeaconCounter::AddBeacon( i64BeaconID );

	if ( EMS_OK == hr )
	{
		INT nIndex = _GetBeaconIndex( i64BeaconID );
		
		if ( ( nIndex >= 0 ) && m_lpTimeRef )
		{
			switch ( m_updateMode )
			{
				case EMSBTC_UpdateNever:	// only if zero
				default:
					if ( !m_lpTimeRef[ nIndex ].intTime )
						m_lpTimeRef[ nIndex ] = timeRef;
					break;

				case EMSBTC_UpdateNewer:	// only if newer
					if ( timeRef.intTime > m_lpTimeRef[ nIndex ].intTime )
						m_lpTimeRef[ nIndex ] = timeRef;
					break;

				case EMSBTC_UpdateOlder:	// only if older
					if ( timeRef.intTime < m_lpTimeRef[ nIndex ].intTime )
						m_lpTimeRef[ nIndex ] = timeRef;
					break;
			}
		}
	}

	return hr;
}

EMSTIME CEMSBeaconTimeCounter::GetBeaconTime( INT64 i64BeaconID )
{
	CEMSTime timeResult;
	int nIndex = _GetBeaconIndex( i64BeaconID );

	if  ( m_lpTimeRef && ( nIndex >= 0 ) )
		timeResult.SetTime( m_lpTimeRef[ nIndex ] );

	return timeResult;
}

EMSTIME CEMSBeaconTimeCounter::GetBeaconTime( INT nIndex )
{
	EMSTIME timeResult;

	timeResult.intTime = 0;

	if  ( m_lpTimeRef && ( nIndex >= 0 ) && ( nIndex < GetMaxCount( ) ) )
		timeResult = m_lpTimeRef[ nIndex ];

	return timeResult;
}

void CEMSBeaconTimeCounter::SetBeaconTime( INT nIndex, EMSTIME timeRef )
{
	if  ( m_lpTimeRef && ( nIndex >= 0 ) && ( nIndex < GetMaxCount( ) ) )
	{
		switch ( m_updateMode )
		{
			case EMSBTC_UpdateNever:	// only if zero
			default:
				if ( !m_lpTimeRef[ nIndex ].intTime )
					m_lpTimeRef[ nIndex ] = timeRef;
				break;

			case EMSBTC_UpdateNewer:	// only if newer
				if ( timeRef.intTime > m_lpTimeRef[ nIndex ].intTime )
					m_lpTimeRef[ nIndex ] = timeRef;
				break;

			case EMSBTC_UpdateOlder:	// only if older
				if ( timeRef.intTime < m_lpTimeRef[ nIndex ].intTime )
					m_lpTimeRef[ nIndex ] = timeRef;
				break;
		}
	}
}
