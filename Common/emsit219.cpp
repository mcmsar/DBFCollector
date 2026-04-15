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


#include "emsit219.h"
#include "sitfield.h"
#include "convutility.h"

const double	c_dSecondsPerMinute 	= (double)60;
const double	c_dMinutesPerHour		= (double)60;
const double	c_dHoursPerDay			= (double)24;
const double	c_dNanoseconds			= (double)1000000000;
const double	c_dNanosecondsPerDay 	= c_dNanoseconds * c_dHoursPerDay 
							* c_dMinutesPerHour * c_dSecondsPerMinute;

CEMSSit219::CEMSSit219() : m_nSatCount(0)
{
	SetSitNumber( 219 );
	memset( m_data, 0, sizeof( m_data ) );
}

CEMSSit219::~CEMSSit219()
{
}


void CEMSSit219::Reset( void )
{
	int nSit = GetSitNumber();
	CEMSSitMessageBase::Reset();
	SetSitNumber( nSit );
	m_nSatCount = 0;
	memset( m_data, 0, sizeof( m_data ) );
}

EMS_RESULT CEMSSit219::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	

	if ( lpStream )
	{
		for (int i = 0; i < m_nSatCount && (EMS_OK == hr ); i++)
		{

			if( EMS_OK == hr )
			{
				std::string line = _GenerateLine( m_data[i] );

#ifdef UNICODE
				hr = WriteLine( lpStream, CEMSConversionUtil::ConvertToString(line.c_str()).c_str() );
#else
				hr = WriteLine( lpStream, line.c_str() );
#endif
			}

		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

std::string
CEMSSit219::_GenerateLine( const EMSSCALEDEPHEMERISDATAEX& crData )
{
	std::string ret;

	// TODO:  Some scaling factors may need to be applied here....
	ret = "/";

	TCHAR szSat[5];
	memset( szSat, 0, sizeof(szSat) );
	_sntprintf( szSat, sizeof(szSat)-1, TEXT("%03d"), crData.ulSatID );

	ret.append(szSat);

	ret.append("/");

	char szM0[12];
	memset( szM0, 0, sizeof(szM0) );
	_snprintf( szM0, sizeof(szM0 ) - 1, "%+010.10I64d",crData.baseData.i64M0 );
	ret.append( szM0 );
	ret.append( " " );

	char szDeltaN[7];
	memset( szDeltaN, 0, sizeof(szDeltaN));
	_snprintf( szDeltaN, sizeof(szDeltaN) - 1, "%+05.5I64d", crData.baseData.i64DeltaN );
	ret.append( szDeltaN );
	ret.append( " " );

	char szEcc[11];
	memset( szEcc, 0, sizeof(szEcc));
	_snprintf( szEcc, sizeof(szEcc) - 1, "%010.10I64d", crData.baseData.i64E );
	ret.append( szEcc );
	ret.append( " " );

	char szSqrtA[11];
	memset( szSqrtA, 0, sizeof(szSqrtA));
	_snprintf( szSqrtA, sizeof(szSqrtA) - 1, "%010.10I64d", crData.baseData.i64SqrtA );
	ret.append( szSqrtA );
	ret.append( " " );

	char szOmega0[12];
	memset( szOmega0, 0, sizeof(szOmega0));
	_snprintf( szOmega0, sizeof(szOmega0) - 1, "%+010.10I64d", crData.baseData.i64OmegaO );
	ret.append( szOmega0 );
	ret.append( " " );

	char szI0[12];
	memset( szI0, 0, sizeof(szI0));
	_snprintf( szI0, sizeof(szI0) - 1, "%+010.10I64d", crData.baseData.i64IO );
	ret.append( szI0 );
	ret.append( " " );
	
	char szOmega[12];
	memset( szOmega, 0, sizeof(szOmega));
	_snprintf( szOmega, sizeof(szOmega) - 1, "%+010.10I64d", crData.baseData.i64Omega );
	ret.append( szOmega );
	ret.append( " " );

	char szOmegaDot[9];
	memset( szOmegaDot, 0, sizeof(szOmegaDot));
	_snprintf( szOmegaDot, sizeof(szOmegaDot) - 1, "%+07.7I64d", crData.baseData.i64OmegaDot );
	ret.append( szOmegaDot );
	ret.append( " " );

	char szIDOT[6];
	memset( szIDOT, 0, sizeof(szIDOT));
	_snprintf( szIDOT, sizeof(szIDOT) - 1, "%+04.4I64d", crData.baseData.i64IDot );
	ret.append( szIDOT );
	ret.append( " " );

	char szCUC[7];
	memset( szCUC, 0, sizeof(szCUC));
	_snprintf( szCUC, sizeof(szCUC) - 1, "%+05.5I64d", crData.baseData.i64UC );
	ret.append( szCUC );
	ret.append( " " );

	char szCUS[7];
	memset( szCUS, 0, sizeof(szCUS));
	_snprintf( szCUS, sizeof(szCUS) - 1, "%+05.5I64d", crData.baseData.i64CUS );
	ret.append( szCUS );
	ret.append( " " );

	char szCRC[7];
	memset( szCRC, 0, sizeof(szCRC));
	_snprintf( szCRC, sizeof(szCRC) - 1, "%+05.5I64d", crData.baseData.i64CRC );
	ret.append( szCRC );
	ret.append( " " );

	char szCRS[7];
	memset( szCRS, 0, sizeof(szCRS));
	_snprintf( szCRS, sizeof(szCRS) - 1, "%+05.5I64d", crData.baseData.i64CRS );
	ret.append( szCRS );
	ret.append( " " );

	char szCIC[7];
	memset( szCIC, 0, sizeof(szCIC));
	_snprintf( szCIC, sizeof(szCIC) - 1, "%+05.5I64d", crData.baseData.i64CIC );
	ret.append( szCIC );
	ret.append( " " );

	char szCIS[7];
	memset( szCIS, 0, sizeof(szCIS));
	_snprintf( szCIS, sizeof(szCIS) - 1, "%+05.5I64d", crData.baseData.i64CIS );
	ret.append( szCIS );
	ret.append( " " );

	char szTOE[7];
	memset( szTOE, 0, sizeof(szTOE));
	_snprintf( szTOE, sizeof(szTOE) - 1, "%06.6d", crData.baseData.ulTOE );
	ret.append( szTOE );
	ret.append( " " );

	char szWN[5];
	memset( szWN, 0, sizeof(szWN));
	_snprintf( szWN, sizeof(szWN) - 1, "%04.4d", crData.baseData.nWeekNum );
	ret.append( szWN );
	ret.append( " " );

	char szIODC_OIDE[4];
	memset( szIODC_OIDE, 0, sizeof(szIODC_OIDE));
	switch( crData.constellation ) 
	{
		case EMS_CONSTELLATION_DASS:
			_snprintf( szIODC_OIDE, sizeof(szIODC_OIDE) - 1, "%03.3d", crData.baseData.nIODC );
			break;

		case EMS_CONSTELLATION_GALILEO:
			_snprintf( szIODC_OIDE, sizeof(szIODC_OIDE) - 1, "%03.3d", crData.baseData.cIODE );
			break;
	}
	
	ret.append( szIODC_OIDE );

	return ret;
}

EMS_RESULT CEMSSit219::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		memset( szBuffer, 0, sizeof(szBuffer) );
		
		_sntprintf( szBuffer, sizeof(szBuffer) - 1, TEXT("/%03d/%03d"), GetSitNumber(), m_nSatCount );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

/*
EMS_RESULT CEMSSit219::_ParseLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT255ADATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSatID = 0, nOrbitNumber = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF6/MF7 eol

		if ( nFldCount == 3 )
		{
			int nNumber = 0;

			hr = msgField.GetMF6( sitField[0].szText, &nSatID );

			if ( hr == EMS_OK )
			{
				lpData->ulSatID = nSatID;

				hr = msgField.GetMF7( sitField[1].szText, &nOrbitNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitNumber = nOrbitNumber;

				if ( !msgField.IsEOL( sitField[2].szText ) )
					hr = EMS_SIT_SYNTAX_EOL;
			}
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;

	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit219::_DecodeLine2( EMSSIT255ADATA *lpData, LPTSTR lpszLine )
{
	EMS_RESULT hr = EMS_OK;
	int i, nExp = 0;
	double dEpoch = 0.0;
	double dTemp;
	ULONG  ulTemp;
	

	for (i = 18; i < 32; i++)
	{
		if (lpszLine[i] == ' ')
			lpszLine[i] = '0';	// No blank between year and days 
	}

	sscanf (&lpszLine[18], "%14lf", &dEpoch);

	lpData->timeEpoch = _ConvertEpochTime( dEpoch );

	sscanf (&lpszLine[33], "%10lf", &dTemp);
		
	lpData->fXndt2o = dTemp;

	sscanf (&lpszLine[44], "%6lf",  &dTemp);
	
	lpData->fXndd6o = dTemp;  

	lpData->fXndd6o /= 100000.0;

	sscanf (&lpszLine[50], "%2d",   &nExp  );

	if ( nExp != 0 )
		lpData->fXndd6o *= pow( 10.0 , nExp );

	sscanf (&lpszLine[53], "%6lf",   &dTemp);
	lpData->fBStar = dTemp; 

	lpData->fBStar  /= 100000.0;

	sscanf (&lpszLine[59], "%2d",   &nExp );

	if ( nExp != 0 )
		lpData->fBStar *= pow( 10.0 , nExp );

	for ( i = 64; i < 68; i++ )
	{
		if ( lpszLine[i] == ' ')
  		lpszLine[i] = '0';  // No blank at the beginning of orbit number 
	}
	sscanf( &lpszLine[64], "%4ld", &ulTemp);
	lpData->ulElementNumber = ulTemp;

	return hr;
}

EMS_RESULT CEMSSit219::_DecodeLine3( EMSSIT255ADATA *lpData, LPTSTR lpszLine )
{
	EMS_RESULT hr = EMS_OK;
	int i;
	ULONG ulTemp;
	double dTemp;

	lpszLine[25] = '.';	// Decimal point for eccentricity 

	for ( i = 63; i < 68; i++ )
	{
		if (lpszLine[i] == ' ')
  		lpszLine[i] = '0';  // No blank at the beginning of orbit number 
	}
	sscanf (&lpszLine[ 2], "%5ld",   &ulTemp);
	lpData->ulNoradNumber = ulTemp;

	sscanf (&lpszLine[ 8], "%8lf",   &dTemp);
	lpData->fInclination = dTemp;
	
	sscanf (&lpszLine[17], "%8lf",   &dTemp);
	lpData->fRightAscNode = dTemp;

	sscanf (&lpszLine[25], "%8lf",   &dTemp);
	lpData->fEccentricity = dTemp;

	sscanf (&lpszLine[34], "%8lf",   &dTemp);
	lpData->fArgPerigee = dTemp;

	sscanf (&lpszLine[43], "%8lf",   &dTemp);
	lpData->fMeanAnomaly = dTemp;

	sscanf (&lpszLine[52], "%11lf",  &dTemp);
	lpData->fMeanMotion = dTemp;

	sscanf (&lpszLine[63], "%5ld",   &ulTemp);
	lpData->ulOrbitNumber = ulTemp;

	return hr;
}
*/

EMSTIME CEMSSit219::_ConvertEpochTime( double dEpochTime )
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

EMS_RESULT CEMSSit219::GetEphemeris( EMSSCALEDEPHEMERISDATAEX* pData, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nSatCount ) && pData )
		memcpy( pData, &m_data[ nIndex ], sizeof( EMSSCALEDEPHEMERISDATAEX ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit219::AddEphemeris( const EMSSCALEDEPHEMERISDATAEX& crData, int nIndex /* = -1 */ )
{
	EMS_RESULT hr = EMS_OK;

	if ( nIndex == -1 ) // ie: append 
	{
		if ( m_nSatCount < EMSSIT219_MAX_SATELLITES )
		{
			memcpy( &m_data[ m_nSatCount++ ] , &crData, sizeof( EMSSCALEDEPHEMERISDATAEX ) );
		}
		else
			hr = EMS_ERROR_LIMIT;
	}
	else if (( nIndex >= 0 ) && ( nIndex < m_nSatCount ) )	// ie: set
	{
		memcpy( &m_data[ nIndex ] , &crData, sizeof( EMSSCALEDEPHEMERISDATAEX ) );
	}
	else
		hr = EMS_BAD_PARAM;
			
	return hr;
}

EMS_RESULT CEMSSit219::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		TCHAR szLine[ 256 ];
		int nLength = 0;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
		{
			// TODO Implement parsing code here.

			/*
			hr = _ParseLine1( lpTokenizer, &m_data[i] );

			if ( hr == EMS_OK )
				hr = ReadSitLine( lpTokenizer,  szLine, 
						sizeof( szLine ) / sizeof( szLine[0] ), &nLength );

			if ( hr == EMS_OK )
				hr = _DecodeLine2( &m_data[i], szLine );

			if ( hr == EMS_OK )
				hr = ReadSitLine( lpTokenizer,  szLine, 
						sizeof( szLine ) / sizeof( szLine[0] ), &nLength );

			if ( hr == EMS_OK )
				hr = _DecodeLine3( &m_data[i], szLine );
			*/
		}
	}

	return hr;
}

EMS_RESULT CEMSSit219::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nSats = 0;

		// should find /MF4/MF8 eol

		if ( nFldCount == 3 )
		{
			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF8( sitField[1].szText, &nSats );
			}

			if ( hr == EMS_OK )
			{
				m_nSatCount = nSats;

				if ( !msgField.IsEOL( sitField[3].szText ) )
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
