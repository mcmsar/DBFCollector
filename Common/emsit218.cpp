/********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "emsit218.h"
#include "sitfield.h"
#include "convutility.h"

const double	c_dSecondsPerMinute 	= (double)60;
const double	c_dMinutesPerHour		= (double)60;
const double	c_dHoursPerDay			= (double)24;
const double	c_dNanoseconds			= (double)1000000000;
const double	c_dNanosecondsPerDay 	= c_dNanoseconds * c_dHoursPerDay 
							* c_dMinutesPerHour * c_dSecondsPerMinute;

CEMSSit218::CEMSSit218() : m_nSatCount(0)
{
	SetSitNumber( 218 );
	memset( m_data, 0, sizeof( m_data ) );
	memset( &m_utcConversion, 0, sizeof(m_utcConversion));
}

CEMSSit218::~CEMSSit218()
{
}


void CEMSSit218::Reset( void )
{
	int nSit = GetSitNumber();
	CEMSSitMessageBase::Reset();
	SetSitNumber( nSit );
	m_nSatCount = 0;
	memset( m_data, 0, sizeof( m_data ) );
	memset( &m_utcConversion, 0, sizeof(m_utcConversion));
}

EMS_RESULT CEMSSit218::_ParseBody( CEMSSitTokenizer *lpTokenizer, EMSSCALEDEPHEMERISDATAEX *lpData )
{
	EMS_RESULT hr = EMS_OK;
	int i, nSatID = 0;

	TCHAR szLine[ 256 ];
	int nLength = 0;

	hr = ReadSitLine( lpTokenizer,  szLine, sizeof( szLine ) / sizeof( szLine[0] ), &nLength );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF6/MFB02 eol

		if ( nLength == 154 )	// As specified in the ICD GAL-IF-CAPG-SARVTB
		{
			TCHAR szMF6[5];
			for ( i=0; i<4; i++ )
				szMF6[i] = szLine[i];
			szMF6[4] = 0;
			hr = msgField.GetMF6( szMF6, &nSatID );

			if ( hr == EMS_OK )
			{
				TCHAR szMFB02[160];
				for ( i=0; i<nLength-4; i++ )
					szMFB02[i] = szLine[i+4];
				szMFB02[nLength-4] = 0;

				hr = msgField.GetMFB02( szMFB02, lpData );
				lpData->ulSatID = nSatID;
				lpData->constellation = EMS_CONSTELLATION_GALILEO;
			}
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;

	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMSTIME CEMSSit218::_ConvertEpochTime( double dEpochTime )
{
	CEMSTime epochTime;
	int nYear = (int) (dEpochTime / 1000.0);	// year is YYddd.ddddd

	dEpochTime -= (double)nYear * 1000.0;	// remove year encoding

	if (( nYear >= 57 ) && ( nYear <= 99 ))
		nYear += 1900;
	else
		nYear += 2000;

	dEpochTime -= 1.0;		// want the number of days NOT the Julian Day

	epochTime.SetTime( nYear, dEpochTime );	// set using year and days

	return epochTime;
}

EMS_RESULT CEMSSit218::GetScaledEphemerisData( LPEMSSCALEDEPHEMERISDATAEX lpData, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nSatCount ) && lpData )
		memcpy( lpData, &m_data[ nIndex ], sizeof( EMSSCALEDEPHEMERISDATAEX ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit218::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
		{
			hr = _ParseBody( lpTokenizer, &m_data[i] );
		}
	}

	return hr;
}

EMS_RESULT CEMSSit218::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	EMSUTCCONVERSION UtcConversion;
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nSats = 0;

		// should find /MF4/MF5/MF44/B01

		if ( nFldCount == 5 )
		{
			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF44( sitField[2].szText, &nSats );
			}

			if ( hr == EMS_OK )
			{
				m_nSatCount = nSats;

				hr = msgField.GetMFB01( sitField[3].szText, &UtcConversion );
			}

			if ( hr == EMS_OK )
			{
				m_utcConversion = UtcConversion;
				if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
			}
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;

		if ( bPeek )
			UnReadSitLine( lpTokenizer, sitField, nFldCount );
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}
