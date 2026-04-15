/********************************************************************
*	Module:			satcount.cpp
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2007/03/10	rvw	start

********************************************************************/
#include <string.h>

#include "satcount.h"
#include "emsclock.h"

CEMSSatCounter::CEMSSatCounter( int nMaxCount /* = 128 */ )
{
	m_lpulSatID = 0;
	m_lpulCount = 0;
	m_nCurrCount = m_nMaxCount = 0;

	if ( nMaxCount )
	{
		m_lpulSatID = new ULONG[ nMaxCount ];

		if ( m_lpulSatID )
		{
			m_lpulCount = new ULONG[ nMaxCount ];

			if ( m_lpulCount )
			{
				m_nMaxCount = nMaxCount;

				memset( m_lpulCount, 0, sizeof( ULONG ) * nMaxCount );
			}

			memset( m_lpulSatID, 0, sizeof( ULONG ) * nMaxCount );
		}
	}
}

CEMSSatCounter::~CEMSSatCounter( )
{
	if ( m_lpulSatID )
	{
		delete [ ] m_lpulSatID;
		m_lpulSatID = 0;
	}

	if ( m_lpulCount )
	{
		delete [ ] m_lpulCount;
		m_lpulCount = 0;
	}
}

void CEMSSatCounter::Reset( void )
{
	if ( m_nMaxCount )
	{
		if ( m_lpulSatID )
		{
		 	memset( m_lpulSatID, 0, sizeof( ULONG ) * m_nMaxCount );
		}

		if ( m_lpulCount )
		{
		 	memset( m_lpulCount, 0, sizeof( ULONG ) * m_nMaxCount );
		}
	}
	m_nCurrCount = 0;
}

EMS_RESULT CEMSSatCounter::_Reset( INT nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpulSatID && ( nIndex >= 0 ) && ( nIndex < m_nMaxCount ) )
	{
		if ( m_lpulSatID[ nIndex ] )
		{
			if ( m_nCurrCount > 0 )
				m_nCurrCount--;

			m_lpulSatID[ nIndex ] = 0;
			m_lpulCount[ nIndex ] = 0;
		}
		else
			hr = EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSatCounter::AddSat( ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( ulSatID )
	{
		bool bAdded = false;

		for ( int i = 0; ( i < m_nMaxCount ) && !bAdded; i++ )
		{
			if ( 0 == m_lpulSatID[i] )
			{
				m_lpulSatID[i] = ulSatID;

				m_nCurrCount++;

				bAdded = true;
			}
			else if ( ulSatID == m_lpulSatID[i] )
			{
				bAdded = true;
			}
			if ( bAdded )
				m_lpulCount[i]++;
		}
		hr = ( bAdded ) ? EMS_OK : EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


INT CEMSSatCounter::_GetSatIndex( ULONG ulSatID )
{	
	INT nIndex = -1;

	if ( ulSatID && m_lpulSatID )
	{
		for ( int i = 0; ( i < m_nMaxCount ) && ( -1 == nIndex ); i++ )
		{
			if ( ulSatID == m_lpulSatID[i] )
			{
				nIndex = i;
			}
		}
	}

	return nIndex;
}

INT CEMSSatCounter::GetSatCount( void )
{
	INT nCount = 0;

	for ( int i = 0; i < m_nMaxCount; i++ )
	{
		if ( m_lpulSatID[i] > 0 )
		{
			nCount++;
		}
	}
	return nCount;
}

INT CEMSSatCounter::GetSatCount( ULONG ulSatID )
{
	INT nCount = 0;
	INT nIndex = _GetSatIndex( ulSatID );

	if ( ( nIndex >= 0 ) && m_lpulCount )
		nCount = m_lpulCount[ nIndex ];

	return nCount;
}

void CEMSSatCounter::_SortDescOrder( void )
{
	if ( m_nMaxCount && m_lpulSatID && m_lpulCount )
	{
		bool bChanged = true;

		while ( bChanged )
		{
			ULONG ulTempSat, ulTempCount;

			bChanged = false;

			for ( int i = 0; i < m_nMaxCount-1; i++ )
			{
				if ( m_lpulCount[ i ] < m_lpulCount[ i+1 ] )
				{
					ulTempSat = m_lpulSatID[ i ];
					ulTempCount = m_lpulCount[ i ];

					m_lpulSatID[ i ] = m_lpulSatID[ i+1 ];
					m_lpulCount[ i ] = m_lpulCount[ i+1 ];
					m_lpulSatID[ i+1 ] = ulTempSat;
					m_lpulCount[ i+1 ] = ulTempCount;
					bChanged = true;
				}
			}
		}
	}
}

int CEMSSatCounter::GetSatsInDescOrder( ULONG *lpulSats )
{
	int nCount = 0;

	if ( lpulSats && m_nMaxCount && m_lpulSatID )
	{
		_SortDescOrder( );

		for ( int i = 0; i < m_nMaxCount; i++ )
		{
			if ( m_lpulSatID[ i ] && m_lpulCount[ i ] )
			{
				lpulSats[ nCount++ ] = m_lpulSatID[ i ];
			}
		}
	}

	return nCount;
}

CEMSSatSorter::CEMSSatSorter( int nMaxCount /* = 128 */ )
{
	m_lpulSatID = 0;
	m_lpulCount = 0;
	m_nCurrCount = m_nMaxCount = 0;
	m_lptimeLastDetection = 0;

	if ( nMaxCount )
	{
		m_lpulSatID = new ULONG[ nMaxCount ];

		if ( m_lpulSatID )
		{
			m_lpulCount = new ULONG[ nMaxCount ];

			if ( m_lpulCount )
			{
				m_lptimeLastDetection = new EMSTIME[ nMaxCount ];

				if ( m_lptimeLastDetection )
				{
					memset( m_lptimeLastDetection, 0, sizeof( EMSTIME ) * nMaxCount );

					m_nMaxCount = nMaxCount;
				}

				memset( m_lpulCount, 0, sizeof( ULONG ) * nMaxCount );
			}

			memset( m_lpulSatID, 0, sizeof( ULONG ) * nMaxCount );
		}
	}
}

CEMSSatSorter::~CEMSSatSorter( )
{
	if ( m_lpulSatID )
	{
		delete [ ] m_lpulSatID;
		m_lpulSatID = 0;
	}

	if ( m_lpulCount )
	{
		delete [ ] m_lpulCount;
		m_lpulCount = 0;
	}

	if ( m_lptimeLastDetection )
	{
		delete [ ] m_lptimeLastDetection;
		m_lptimeLastDetection = 0;
	}
}

void CEMSSatSorter::Reset( void )
{
	if ( m_nMaxCount )
	{
		if ( m_lpulSatID )
		{
		 	memset( m_lpulSatID, 0, sizeof( ULONG ) * m_nMaxCount );
		}

		if ( m_lpulCount )
		{
		 	memset( m_lpulCount, 0, sizeof( ULONG ) * m_nMaxCount );
		}

		if ( m_lptimeLastDetection )
		{
			memset( m_lptimeLastDetection, 0, sizeof( EMSTIME ) * m_nMaxCount );
		}
	}
	m_nCurrCount = 0;
}

EMS_RESULT CEMSSatSorter::_Reset( INT nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpulSatID && ( nIndex >= 0 ) && ( nIndex < m_nMaxCount ) )
	{
		if ( m_lpulSatID[ nIndex ] )
		{
			if ( m_nCurrCount > 0 )
				m_nCurrCount--;

			m_lpulSatID[ nIndex ] = 0;
			m_lpulCount[ nIndex ] = 0;
			m_lptimeLastDetection[ nIndex ].intTime = 0;
		}
		else
			hr = EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSatSorter::AddSat( ULONG ulSatID, EMSTIME timeDetection )
{
	EMS_RESULT hr = EMS_OK;

	if ( ulSatID )
	{
		bool bAdded = false;

		for ( int i = 0; ( i < m_nMaxCount ) && !bAdded; i++ )
		{
			if ( 0 == m_lpulSatID[i] )
			{
				m_lpulSatID[i] = ulSatID;

				m_nCurrCount++;

				bAdded = true;
			}
			else if ( ulSatID == m_lpulSatID[i] )
			{
				bAdded = true;
			}

			if ( bAdded )
			{
				if ( timeDetection.intTime > m_lptimeLastDetection[i].intTime )
					m_lptimeLastDetection[i] = timeDetection;
					
				m_lpulCount[i]++;
			}
		}
		hr = ( bAdded ) ? EMS_OK : EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

INT CEMSSatSorter::_GetSatIndex( ULONG ulSatID )
{	
	INT nIndex = -1;

	if ( ulSatID && m_lpulSatID )
	{
		for ( int i = 0; ( i < m_nMaxCount ) && ( -1 == nIndex ); i++ )
		{
			if ( ulSatID == m_lpulSatID[i] )
			{
				nIndex = i;
			}
		}
	}

	return nIndex;
}

INT CEMSSatSorter::GetSatCount( void )
{
	INT nCount = 0;

	for ( int i = 0; i < m_nMaxCount; i++ )
	{
		if ( m_lpulSatID[i] > 0 )
		{
			nCount++;
		}
	}
	return nCount;
}

INT CEMSSatSorter::GetSatCount( ULONG ulSatID )
{
	INT nCount = 0;
	INT nIndex = _GetSatIndex( ulSatID );

	if ( ( nIndex >= 0 ) && m_lpulCount )
		nCount = m_lpulCount[ nIndex ];

	return nCount;
}

void CEMSSatSorter::_SortDescOrder( void )
{
	if ( m_nMaxCount && m_lpulSatID && m_lpulCount )
	{
		bool bChanged = true;

		while ( bChanged )
		{
			ULONG ulTempSat, ulTempCount;
			EMSTIME timeTemp;

			bChanged = false;

			for ( int i = 0; i < m_nMaxCount-1; i++ )
			{
				if ( m_lptimeLastDetection[ i ].intTime < m_lptimeLastDetection[ i+1 ].intTime )
				{
					ulTempSat = m_lpulSatID[ i ];
					ulTempCount = m_lpulCount[ i ];
					timeTemp = m_lptimeLastDetection[ i ];

					m_lpulSatID[ i ] = m_lpulSatID[ i+1 ];
					m_lpulCount[ i ] = m_lpulCount[ i+1 ];
					m_lptimeLastDetection[ i ] = m_lptimeLastDetection[ i+1 ];
					m_lpulSatID[ i+1 ] = ulTempSat;
					m_lpulCount[ i+1 ] = ulTempCount;
					m_lptimeLastDetection[ i+1 ] = timeTemp;
					bChanged = true;
				}
			}
		}
	}
}

int CEMSSatSorter::GetSatsInDescOrder( ULONG *lpulSats )
{
	int nCount = 0;

	if ( lpulSats && m_nMaxCount && m_lpulSatID )
	{
		_SortDescOrder( );

		for ( int i = 0; i < m_nMaxCount; i++ )
		{
			if ( m_lpulSatID[ i ] && m_lpulCount[ i ] )
			{
				lpulSats[ nCount++ ] = m_lpulSatID[ i ];
			}
		}
	}

	return nCount;
}
