/********************************************************************
*	Module:			emsit255.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit255A  Class
*						Leosar Orbit ( Norad 2-line Element TLE )
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	2002 June 3 rvw	start

********************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


#include "emsit255.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s/%s/%05d/%02d");
const TCHAR c_szSitBodyFmt[ ] = TEXT("/%04d/%05d/%02d");
const TCHAR c_szSitBodyLine1Fmt[ ] = TEXT("/%03d/%05d");
const TCHAR c_szSitBodyLine2Fmt[ ] = TEXT("1 %05dU %05d%C   %02.2d%03.3d.%08.8d %C.%08d %C%05d-%01d %C%05d-%01d 0 %4d");
const TCHAR c_szSitBodyLine3Fmt[ ] = TEXT("2 %05d %8.4f %8.4f %07d %8.4f %8.4f %11.8f%5d");

const double	c_dSecondsPerMinute 	= (double)60;
const double	c_dMinutesPerHour		= (double)60;
const double	c_dHoursPerDay			= (double)24;
const double	c_dNanoseconds			= (double)1000000000;
const double	c_dNanosecondsPerDay 	= c_dNanoseconds * c_dHoursPerDay 
							* c_dMinutesPerHour * c_dSecondsPerMinute;

CEMSSit255A::CEMSSit255A()
{
	m_nSatCount = 0;
	SetSitNumber( 255 );
	SetSitCode( 0x255A );
	m_nRequestMsgNumber = 0;
	m_controlCode = EMSSCC_Unknown;
	memset( m_data, 0, sizeof( m_data ) );
}

CEMSSit255A::~CEMSSit255A()
{
}


void CEMSSit255A::Reset( void )
{
	int nSit = GetSitNumber();
	CEMSSitMessageBase::Reset();
	SetSitNumber( nSit );
	SetSitCode( 0x255A );
	m_nSatCount = 0;
	memset( m_data, 0, sizeof( m_data ) );
}

EMS_RESULT CEMSSit255A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	CEMSTime tmpTime;
	EMSTIMEFIELDS timeFields;
	ULONG ulYear;
	double dDay;
	ULONG ulFractDay;
    LONG lDMM1;
    LONG lDMM2;
	ULONG ulDMM2Exp;
	char szDMM2[20];
	char *lpszDMM2Exp = 0;
    LONG lBStar;
	ULONG ulBStarExp;
	char szBStar[20];
	char *lpszBStarExp = 0;
	ULONG ulEccentricity;
	int nCheckSum;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szBufferWithCheckSum[256];

		for (int i = 0; i < m_nSatCount; i++)
		{
			tmpTime.SetTime(m_data[i].timeEpoch);
			tmpTime.GetTime(&timeFields);
			ulYear = timeFields.nYear - (timeFields.nYear/100)*100;

			sprintf( szBuffer, c_szSitBodyLine1Fmt,
								m_data[i].ulSatID,
								m_data[i].ulOrbitNumber);
			hr = WriteLine( lpStream, szBuffer );

			//Get fraction of the day
			dDay = (((timeFields.nHour * c_dMinutesPerHour * c_dSecondsPerMinute) +  (timeFields.nMinute * c_dSecondsPerMinute) + 
			   (timeFields.nSecond)) * c_dNanoseconds ) + timeFields.lNanosecond;
	
			ulFractDay = (ULONG) ((dDay/c_dNanosecondsPerDay) * 100000000);

			lDMM1 = (LONG) m_data[i].fXndt2o * 100000000;

			//Format DMM2
			sprintf(szDMM2, "%09.5E",m_data[i].fXndd6o);

//			lpszDMM2Exp = &szDMM2[9];
            if( m_data[i].fXndd6o < 1.0 && 0.0 != m_data[i].fXndd6o )
                lpszDMM2Exp = strrchr( szDMM2, '-' );
            else
                lpszDMM2Exp = strrchr( szDMM2, '+' );
            lpszDMM2Exp++;
			int iDMM2Exp = atoi(lpszDMM2Exp);
			lDMM2 = (LONG) ((m_data[i].fXndd6o * pow(10.0, iDMM2Exp)) * 10000);
			ulDMM2Exp = iDMM2Exp;
			if (ulDMM2Exp >= 1)
			{
				ulDMM2Exp = ulDMM2Exp - 1;
			}
			else
			{
				ulDMM2Exp = 0;
			}
			
			//Format Bstar
			sprintf(szBStar, "%09.5E", m_data[i].fBStar);

//			lpszBStarExp = &szBStar[9];
            if( m_data[i].fBStar < 1.0 && 0.0 != m_data[i].fBStar )
                lpszBStarExp = strrchr( szBStar, '-' );
            else
                lpszBStarExp = strrchr( szBStar, '+' );

            lpszBStarExp++;
			int iBStarExp = atoi(lpszBStarExp);
			lBStar = (LONG) ((m_data[i].fBStar * pow(10.0, iBStarExp)) * 10000);
			ulBStarExp = iBStarExp;
			if (ulBStarExp >= 1)
			{
				ulBStarExp = ulBStarExp - 1;
			}
			else
			{
				ulBStarExp = 0;
			}
				
			sprintf( szBuffer, c_szSitBodyLine2Fmt,
								(int)m_data[i].ulNoradNumber,
								0,
								'A',
								ulYear,
								timeFields.nJulianDay,
								ulFractDay,
                                lDMM1 < 0 ? '-' : ' ',
                                lDMM1 < 0 ? -lDMM1 : lDMM1,
                                lDMM2 < 0 ? '-' : ' ',
                                lDMM2 < 0 ? -lDMM2 : lDMM2,
								ulDMM2Exp,
                                lBStar < 0 ? '-' : ' ',
								lBStar < 0 ? -lBStar : lBStar,
								ulBStarExp,
								m_data[i].ulElementNumber );

			nCheckSum = _GetCheckSum(szBuffer);

			sprintf( szBufferWithCheckSum, "%s%01d", szBuffer, nCheckSum );

			hr = WriteLine( lpStream, szBufferWithCheckSum );

			ulEccentricity = (ULONG) ( (double)m_data[i].fEccentricity * 10000000.0 );
			
			_CorrectRange(&m_data[i].fArgPerigee);
			_CorrectRange(&m_data[i].fMeanAnomaly);
			_CorrectRange(&m_data[i].fRightAscNode);

			sprintf( szBuffer, c_szSitBodyLine3Fmt,
								(int)m_data[i].ulNoradNumber,
								m_data[i].fInclination,
								m_data[i].fRightAscNode,
								ulEccentricity,
								m_data[i].fArgPerigee,
								m_data[i].fMeanAnomaly,
								m_data[i].fMeanMotion,
								m_data[i].ulOrbitNumber );

			nCheckSum = _GetCheckSum(szBuffer);

			sprintf( szBufferWithCheckSum, "%s%01d", szBuffer, nCheckSum );

			hr = WriteLine( lpStream, szBufferWithCheckSum );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

int CEMSSit255A::_GetCheckSum(char* lpszBuffer)
{
	char str[2];
	int index = 0;
	int iCheckSum = 0;

	while (lpszBuffer[index] != '\0')
	{
		strncpy(str, &lpszBuffer[index], 1);

		switch (lpszBuffer[index])
		{
			case '-':
			   iCheckSum++;
			   break;
			case '+':
			case '.':
			case ' ':
			   break;
			default:
				iCheckSum = iCheckSum + atoi(str);
				break;
		}
		index++;

	}
	return (int) fmod(iCheckSum, 10.0);

}


void CEMSSit255A::_CorrectRange( double* lpdValue )
{
	while (*lpdValue < 0)
	{
		*lpdValue = *lpdValue + (double) 360;
	}


	while (*lpdValue > 360 )
	{
		*lpdValue = *lpdValue - (double) 360;
	}

	return;
}


EMS_RESULT CEMSSit255A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szCC[32];
		
		lstrcpy( szCC, _GetControlCodeText( m_controlCode ) );
		
		wsprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr(), 
							szCC, m_nRequestMsgNumber , m_nSatCount );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit255A::_ParseLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT255ADATA lpData )
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

EMS_RESULT CEMSSit255A::_DecodeLine2( EMSSIT255ADATA *lpData, LPTSTR lpszLine )
{
	EMS_RESULT hr = EMS_OK;
	int i, nExp = 0;
	double dEpoch = 0.0;
	double dTemp;
	ULONG  ulTemp;
	

	for (i = 18; i < 32; i++)
	{
		if (lpszLine[i] == ' ')
			lpszLine[i] = '0';	/* No blank between year and days */
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
  		lpszLine[i] = '0';  /* No blank at the beginning of orbit number */
	}
	sscanf( &lpszLine[64], "%4ld", &ulTemp);
	lpData->ulElementNumber = ulTemp;

	return hr;
}

EMS_RESULT CEMSSit255A::_DecodeLine3( EMSSIT255ADATA *lpData, LPTSTR lpszLine )
{
	EMS_RESULT hr = EMS_OK;
	int i;
	ULONG ulTemp;
	double dTemp;

	lpszLine[25] = '.';	/* Decimal point for eccentricity */

	for ( i = 63; i < 68; i++ )
	{
		if (lpszLine[i] == ' ')
  		lpszLine[i] = '0';  /* No blank at the beginning of orbit number */
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

EMSTIME CEMSSit255A::_ConvertEpochTime( double dEpochTime )
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

EMS_RESULT CEMSSit255A::GetOrbitData( LPEMSSIT255ADATA lpData, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nSatCount ) && lpData )
		memcpy( lpData, &m_data[ nIndex ], sizeof( EMSSIT255ADATA ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit255A::AddOrbitData( LPEMSSIT255ADATA lpData, int nIndex /* = -1 */ )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpData )
	{
		if ( nIndex == -1 ) // ie: append 
		{
			if ( m_nSatCount < EMSSIT255A_MAX_SATELLITES )
			{
				memcpy( &m_data[ m_nSatCount++ ] , lpData, sizeof( EMSSIT255ADATA ) );
			}
			else
				hr = EMS_ERROR_LIMIT;
		}
		else if (( nIndex >= 0 ) && ( nIndex < m_nSatCount ) )	// ie: set
		{
			memcpy( &m_data[ nIndex ] , lpData, sizeof( EMSSIT255ADATA ) );
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;
			
	return hr;
}

EMS_RESULT CEMSSit255A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		TCHAR szLine[ 256 ];
		int nLength = 0;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
		{
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
		}
	}

	return hr;
}

EMS_RESULT CEMSSit255A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;
	EMSSITCODE sitCode;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nNumber = 0, nReqNumber=0;
 		EMSSITMF605 mf605;

		// should find /MF4/MF5/MF4A/MF605/MF01A/MF44 eol

		if ( nFldCount == 7 )
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

				hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
			}

			if ( hr == EMS_OK )
			{
				SetSitCode( sitCode );

				hr = msgField.GetMF605( sitField[3].szText, &mf605 );

			}

			if ( hr == EMS_OK )
			{
				TCHAR szTemp[ 32 ];

				memset( szTemp, 0, sizeof( szTemp ));

				memcpy( szTemp, &mf605, sizeof( mf605 ) );

				for ( int i = EMSSCC_First; i < EMSSCC_Last; i++ )
				{
					if ( lstrcmpi( _GetControlCodeText( (EMSSITCONTROLCODE)i ), szTemp ) == 0 )
					{
						SetControlCode( (EMSSITCONTROLCODE)i );
						i = EMSSCC_Last;
					}
				}

				hr = msgField.GetMF1A( sitField[ 4 ].szText, &nReqNumber );
			}

			if ( hr == EMS_OK )
			{
				SetRequestMsgNumber( nReqNumber );
				
				hr = msgField.GetMF44( sitField[ 5 ].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				m_nSatCount = nNumber;

				if ( !msgField.IsEOL( sitField[6].szText ) )
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

LPCTSTR CEMSSit255A::_GetControlCodeText( EMSSITCONTROLCODE code )
{
	switch ( code )
	{
		case EMSSCC_Info:					return TEXT("INFO");
		case EMSSCC_Validate:			return TEXT("VALD");
		case EMSSCC_Execute:				return TEXT("EXEC");
		case EMSSCC_ValidateInstall:	return TEXT("VALI");
		case EMSSCC_Install:				return TEXT("INST");
		case EMSSCC_InstallManoeuvre:	return TEXT("INSM");
		case EMSSCC_Append:				return TEXT("APND");
		case EMSSCC_ValidData:			return TEXT("DVAL");
		case EMSSCC_InvalidData:		return TEXT("DINV");
		case EMSSCC_CommandAccepted:	return TEXT("CACC");
		case EMSSCC_CommandRejected:	return TEXT("CRJT");
		case EMSSCC_UnknownCommand:	return TEXT("COMX");
		case EMSSCC_ProcessOkay:		return TEXT("CPRS");
		case EMSSCC_ProcessFailed:		return TEXT("CPNS");
		case EMSSCC_Unknown:
		default:								return TEXT("????");
	}
}
