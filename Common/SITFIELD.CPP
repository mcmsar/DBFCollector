/********************************************************************
*	Module:			sitfield.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of SIT Message Field Class
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string>

#include "sitfield.h"
#include "emsconst.h"

const int		c_iMinTimeStringLen		= 12;	// "nn nnn nnnn\0"         including the null terminating char 
const int		c_iMinTime1StringLen	= 18;	// "nn nnn nnnn nn.nn\0"   including the null terminating char 
const int		c_iMinTime2StringLen	= 19;	// "nn nnn nnnn nn.nnn\0"  including the null terminating char 
const int		c_iMinTime3StringLen	= 22;	// "nn nnn nnnn nn.nnnnnn\0"  including the null terminating char 
const int		c_iMinTime4StringLen	= 16;	// "nn nnn nn nn nn\0"  including the null terminating char 

CEMSSitMsgField::CEMSSitMsgField( )
{
}

CEMSSitMsgField::~CEMSSitMsgField()
{
}

BOOL CEMSSitMsgField::IsEOL( LPCTSTR lpcszField )
{
	BOOL bEOL = FALSE;

	if( lpcszField )
	{
		bEOL = m_LT.IsEOL( *lpcszField );
	}
	
	return bEOL;
}

int CEMSSitMsgField::_GetMinLength( LPCTSTR lpcszSyntax )
{
	int nLength = lstrlen( lpcszSyntax );

	for ( int i = nLength-1; i >= 0; i-- )
	{
		if ( lpcszSyntax[i] == '?' )
			nLength--;
	}

	return nLength;
}

EMS_RESULT CEMSSitMsgField::_CheckSyntax( LPCTSTR lpcszField, LPCTSTR lpcszSyntax )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax )
	{
		int nLength = lstrlen( lpcszField );
		TCHAR cChar;

			for ( int i = 0; i < nLength; i++ )
			{
				cChar = lpcszField[i];

				switch ( lpcszSyntax[i] )
				{
					case ' ':
						if ( cChar != ' ' )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case '/':
						if ( cChar != '/' )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case '.':	// decimal
						if ( cChar != '.' )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case 'H':	// HEX letter's A->F
						if ( ( toupper( cChar ) < 'A' ) || ( toupper( cChar ) > 'F' ) )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case 'h':	// Hex digit
						if ( ( toupper( cChar ) < 'A' ) || ( toupper( cChar ) > 'F' ) )
						{
							if ( !isdigit( cChar ) )
								hr = EMS_SIT_SYNTAX_ERROR;
						}
						break;

					case 'a':	// alphanumeric
						break;

					case 'n':	// numeric
						if ( !isdigit( cChar ) )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case 's':	// sign
						if ( ( cChar != '+' ) && ( cChar != '-' ) )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;

					case '?':	// optional ( extended ) representation
						if ( !isdigit( cChar ) )
							hr = EMS_SIT_SYNTAX_ERROR;
						break;
				}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF1( LPCTSTR lpcszField, int *lpMsgId, int *lpLastMsgId )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnn nnnnn");

	if ( lpcszField && lpMsgId && lpLastMsgId )
	{
		int nMinLen = _GetMinLength( c_szSyntax ), nMaxLen = lstrlen( c_szSyntax );
		int nFldLen = lstrlen( lpcszField );

		*lpMsgId = *lpLastMsgId = 0;

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			TCHAR szTemp[32], *lpSpace = 0;

			hr = _CheckSyntax( lpcszField, c_szSyntax );

			if ( hr == EMS_OK )
			{
				lstrcpy( szTemp, lpcszField );

				lpSpace = _tcschr( szTemp, ' ' );

				if ( lpSpace )
			 		*lpSpace = 0;

				*lpMsgId = atoi( &szTemp[1] );

				*lpLastMsgId = atoi( lpSpace+1 );
			}
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF1A( LPCTSTR lpcszField, int *lpnMsgID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnMsgID );
}

EMS_RESULT CEMSSitMsgField::GetMF2( LPCTSTR lpcszField, int *lpMCCID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpMCCID );
}

EMS_RESULT CEMSSitMsgField::GetMF3( LPCTSTR lpcszField, EMSTIME *lpTimeMsg )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn??");

	if ( lpcszField && lpTimeMsg )
	{
		int nMinLen = _GetMinLength( c_szSyntax ), nMaxLen = lstrlen( c_szSyntax );
		int nFldLen = lstrlen( lpcszField );

		lpTimeMsg->intTime = 0;

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			TCHAR szTemp[32], *lpSpace = 0, *lpNextSpace = 0, szNumber[16];
			CEMSTime timeTemp;
			int nYear = 0, nHours=0, nMinutes=0, nSeconds = 0;
			double dDays = 0.0;

			hr = _CheckSyntax( lpcszField , c_szSyntax );

			if ( hr == EMS_OK )
			{
				lstrcpy( szTemp, lpcszField );

				lpSpace = _tcschr( szTemp, ' ' );

				if ( lpSpace )
			 		*lpSpace = 0;

				nYear = atoi( &szTemp[1] );
            nYear += ( nYear >= 80 ) ? 1900 : 2000;         // year 2080 bug

				lpNextSpace = _tcschr( lpSpace+1, ' ' );

				if ( lpNextSpace )
					*lpNextSpace = 0;

//				dDays = atof( lpSpace+1 );

				dDays = atof( lpSpace+1 ) - 1; //Do not count current day

				timeTemp.SetTime( nYear, dDays );

				_tcsncpy( szNumber, ++lpNextSpace, 2 );

				szNumber[2] = 0;

				nHours = atoi( szNumber );

				timeTemp.AddHours( nHours );

				_tcsncpy( szNumber, lpNextSpace+2, 2 );

				szNumber[2] = 0;

				nMinutes = atoi( szNumber );

				timeTemp.AddMinutes( nMinutes );

				lpNextSpace += 4;

				if ( ( lstrlen( lpNextSpace ) == 2 ) )
					nSeconds = atoi( lpNextSpace );

				timeTemp.AddSeconds( nSeconds );

				*lpTimeMsg = (EMSTIME)timeTemp;
			}
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

LPCTSTR CEMSSitMsgField::TextMF3( EMSTIME timeMsgTransmit )
{
	static TCHAR szText[ c_iMinTimeStringLen ];

	_TextTime( timeMsgTransmit, szText, c_iMinTimeStringLen );

	return szText;
}

BOOL CEMSSitMsgField::_ValidSitCode( EMSSITCODE sitCode )
{
	switch ( sitCode )
	{
		case 0x115A:	
		case 0x115B:
		case 0x115C:
		case 0x121A:
		case 0x121B:
		case 0x122A:
		case 0x122B:
		case 0x122C:
		case 0x122E:
		case 0x125A:
		case 0x125B:
		case 0x215A:
		case 0x215B:
		case 0x215C:
		case 0x255A:
		case 0x260A:
		case 0x260B:
		case 0x270A:
		case 0x415A:
		case 0x417A:
		case 0x417B:
		case 0x510A:
		case 0x605A:
		case 0x605B:
		case 0x605C:
		case 0x605D:
		case 0x661A:
		case 0x661B:
		case 0x662A:
		case 0x750A:
		case 0x751A:
		case 0x760A:
		case 0x770A:
		case 0x950A:
		case 0x951A:
			return TRUE;
			break;

		default:
			return FALSE;
			break;
	}
}

EMS_RESULT CEMSSitMsgField::GetMF4( LPCTSTR lpcszField,  int *lpSitNumber )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpSitNumber );
}

EMS_RESULT CEMSSitMsgField::GetMF4A( LPCTSTR lpcszField, EMSSITCODE *lpSitCode )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[ ] = TEXT("/nnnH");

	if ( lpcszField && lpSitCode )
	{
		hr = _CheckSyntax( lpcszField, c_szSyntax );

		if ( hr == EMS_OK )
		{
//			TCHAR szTemp[32]="0x";
//
//			lstrcat( szTemp, &lpcszField[1] );
//
			*lpSitCode = strtol( &lpcszField[1], 0, 16 );

			if ( !_ValidSitCode( *lpSitCode ) )
				hr = EMS_UNKNOWN_SIT_CODE;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF5( LPCTSTR lpcszField,  int *lpnDestID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnDestID );
}

EMS_RESULT CEMSSitMsgField::GetMF5A( LPCTSTR lpcszField, int *lpnDestID )
{
	return GetMF5( lpcszField, lpnDestID );
}

EMS_RESULT CEMSSitMsgField::GetMF6( LPCTSTR lpcszField, int *lpnSatID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSatID );
}

EMS_RESULT
CEMSSitMsgField::GetMF6A( LPCTSTR lpcszField, int *lpnSatID )
{
   return GetMF6( lpcszField, lpnSatID );
}

EMS_RESULT CEMSSitMsgField::GetMF7( LPCTSTR lpcszField, int *lpnOrbitNumber )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnOrbitNumber );
}

EMS_RESULT CEMSSitMsgField::GetMF7A( LPCTSTR lpcszField, int *lpnOrbitNumber )
{
   return GetMF7( lpcszField, lpnOrbitNumber );
}

EMS_RESULT CEMSSitMsgField::GetMF7B( LPCTSTR lpcszField, int *lpnOrbitNumber )
{
   return GetMF7( lpcszField, lpnOrbitNumber );
}

EMS_RESULT
CEMSSitMsgField::GetMF8( LPCTSTR lpcszField, int *lpnAlertCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAlertCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8A( LPCTSTR lpcszField, int *lpnAlertCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAlertCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8B( LPCTSTR lpcszField, int *lpn121LocCount )
{
   return GetMF8A( lpcszField, lpn121LocCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8C( LPCTSTR lpcszField, int *lpn243LocCount )
{
   return GetMF8A( lpcszField, lpn243LocCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8D( LPCTSTR lpcszField, int *lpn406IntLocCount )
{
   return GetMF8A( lpcszField, lpn406IntLocCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8E( LPCTSTR lpcszField, int *lpn406LocCount )
{
   return GetMF8A( lpcszField, lpn406LocCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF8F( LPCTSTR lpcszField, int *lpnMedianLocAccSampleSize )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnMedianLocAccSampleSize );
}

EMS_RESULT CEMSSitMsgField::GetMF10( LPCTSTR lpcszField, int *lpnAlertCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAlertCount );
}

EMS_RESULT CEMSSitMsgField::GetMF10A( LPCTSTR lpcszField, int *lpnAlertCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAlertCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF10B( LPCTSTR lpcszField, int *lpnAlertCount )
{
	return GetMF10A( lpcszField, lpnAlertCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF10C( LPCTSTR lpcszField, int *lpnAlertCount )
{
	return GetMF10A( lpcszField, lpnAlertCount );
}


EMS_RESULT CEMSSitMsgField::GetMF11( LPCTSTR lpcszField,  int *lpLutID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpLutID );
}

EMS_RESULT CEMSSitMsgField::GetMF12( LPCTSTR lpcszField, BOOL *lpbLocalFlag, int *lpnFreqBand )
{
	const TCHAR c_szSyntax[ ] = TEXT("/sn");
	int nNumber = 0;

	EMS_RESULT hr = _GetIntegerField( lpcszField, c_szSyntax, &nNumber );

	if ( lpbLocalFlag )
		*lpbLocalFlag = ( nNumber > 0 );

	if ( lpnFreqBand )
		*lpnFreqBand = ( nNumber > 0 ) ? nNumber : nNumber * -1;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF12A( LPCTSTR lpcszField, TCHAR* lpcDataType )
{
	const TCHAR c_szSyntax[ ] = TEXT("/a");
	
	const long clStrLen = 2;
	TCHAR szString[clStrLen];

	EMS_RESULT hr = _GetAlphaField( lpcszField, c_szSyntax, szString, clStrLen );

	if( EMS_OK == hr && lpcDataType )
	{
		*lpcDataType = szString[0];
	}

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF13(   LPCTSTR     lpcszField, 
					                        double*     lpdBias, 
                                       double*     lpdBSDev,
                                       double*     lpdDrift )
{
   const TCHAR c_szSyntax[] = TEXT("/snnnnn.n nnn.n snn.nn");

   EMS_RESULT hr = _CheckSyntax( lpcszField, c_szSyntax );

   if ( EMS_OK == hr )
   {
      *lpdBias    = atof( &(lpcszField[1]) );
      *lpdBSDev   = atof( &(lpcszField[10]) );
      *lpdDrift   = atof( &(lpcszField[16]) );
   }
	return hr;
}

LPCTSTR CEMSSitMsgField::TextMF13( double dBias, double dBSDev, double dDrift )
{
	static TCHAR szText[ 32 ];

	if ( ( dBias > 75000.0 ) || ( dBias < -25000.0 ) )
		dBias = 99999.9;

	if ( ( dDrift > 99.0 ) || ( dDrift < -99.0 ) )
		dDrift = 99.99;

	if ( ( dBSDev > 900.0 ) || ( dBSDev < 0.0 ) )
		dBSDev = 999.9;

	_stprintf( szText, TEXT("%+08.1lf %05.1lf %+06.2lf"), 
									dBias, dBSDev, dDrift );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF14( LPCTSTR lpcszField, EMSTIME *lpTimeTCA )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lpTimeTCA );
}

LPCTSTR CEMSSitMsgField::TextMF14( EMSTIME timeTCA )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeTCA, szText, c_iMinTime1StringLen );

	return szText;
}

// TextMF14A and TextMF14B are identical to TextMF14 
// but need their own static memory
LPCTSTR CEMSSitMsgField::TextMF14A( EMSTIME timeTCA )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeTCA, szText, c_iMinTime1StringLen );

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF14B( EMSTIME timeTCA )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeTCA, szText, c_iMinTime1StringLen );

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF664( EMSTIME timeOrbitEffective )
{ 
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeOrbitEffective, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF15( LPCTSTR lpcszField, int* lpnWindowFactor )
{
	const TCHAR c_szSyntax[ ] = TEXT("/n");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnWindowFactor );
}

EMS_RESULT
CEMSSitMsgField::GetMF16(  LPCTSTR     lpcszField, 
                           int*        lpnIterations )
{
   const TCHAR c_szSyntax[ ] = TEXT("/n");

   return _GetIntegerField( lpcszField, c_szSyntax, lpnIterations );
}

LPCTSTR CEMSSitMsgField::TextMF17( double dCTA )
{
	static TCHAR szText[ 16 ];

	dCTA = fabs( dCTA );

	if ( dCTA > 33.0 )
		dCTA = 33.0;

	_stprintf( szText, TEXT("%06.3lf"), dCTA );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF17A( LPCTSTR  lpcszField, 
                           double*  lpdCTA )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snn.nnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdCTA );
}

LPCTSTR CEMSSitMsgField::TextMF17A( double dCTA )
{
	static TCHAR szText[ 16 ];

	if ( dCTA > 33.0 )
		dCTA = 33.0;
	else if ( dCTA < -33.0 )
		dCTA = -33.0;

	_stprintf( szText, TEXT("%+07.3lf"), dCTA );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF18( LPCTSTR lpcszField, int *lpnSecondaryLutID )
{
   return GetMF11( lpcszField, lpnSecondaryLutID );
}

EMS_RESULT
CEMSSitMsgField::GetMF19( LPCTSTR lpcszField, int *lpnSideBands )
{
   const TCHAR c_szSyntax[ ] = TEXT("/nn");

   return _GetIntegerField( lpcszField, c_szSyntax, lpnSideBands );
}

EMS_RESULT
CEMSSitMsgField::GetMF20(  LPCTSTR  lpcszField, 
                           int*     lpnSweepPeriod,
                           int*     lpnSweepPeriodSdev )
{
   EMS_RESULT hr = EMS_OK;

   const TCHAR c_szSyntax[] = TEXT("/nnnn nn");

	hr = _CheckSyntax( lpcszField, c_szSyntax );

   if ( EMS_OK == hr )
   {
	   *lpnSweepPeriod      = atoi( &(lpcszField[1]) );
	   *lpnSweepPeriodSdev  = atoi( &(lpcszField[6]) );
   }
   return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF21( LPCTSTR lpcszField, int *lpnNumPoints )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnNumPoints );
}

EMS_RESULT
CEMSSitMsgField::GetMF21A( LPCTSTR lpcszField, int *lpnNumPoints )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnNumPoints );
}

EMS_RESULT
CEMSSitMsgField::GetMF21B( LPCTSTR lpcszField, int *lpnNumPoints )
{
   return GetMF21A( lpcszField, lpnNumPoints );
}

LPCTSTR CEMSSitMsgField::TextMF22( const INT64 ci64BeaconID )
{

#if defined(UNICODE) || defined(_UNICODE)
	// This code assumes that it will not need to support UNICODE
	assert(false);
#endif

	//Max return size from _i64toa() is 33.
	static char szText[33];
	memset( szText, 0, 33 );

	_i64toa( ci64BeaconID, szText, 16 );
	_strupr( szText );

	size_t uLen = strlen( szText );
	if ( uLen < 15 )
	{
		char szZeroPad[15];
		memset( szZeroPad, 0, 15 );
		memset( szZeroPad, '0', 15-uLen );
		strcat( szZeroPad, szText );
		strcpy( szText, szZeroPad );
	}
	
	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF23( const BYTE* cabyBeaconMsg )
{
	assert( cabyBeaconMsg );

#if defined(UNICODE) || defined(_UNICODE)
	// This code assumes that it will not need to support UNICODE
	assert(false);
#endif

	// Allow for too much space
	static char szText[ 32 ];
	memset( szText, 0, 32 );

	// Skip over the first 3 bytes (frame synch)
	// and process the next 15 for the 30Hex message
	for ( int j = 0; j < 15; j++ )
	{
		sprintf( &szText[j*2], "%02X", cabyBeaconMsg[3+j] );
	}

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF23( LPCTSTR lpcszField, BYTE* pacBeaconMsg )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpcszField && pacBeaconMsg )
   {
      const TCHAR c_szSyntax[ ] = TEXT("/hhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"); // 30 hex characters

	   hr = _CheckSyntax( lpcszField , c_szSyntax );

      if ( EMS_OK == hr )
      {
         BYTE     byteTemp;
         TCHAR*   pszBeaconMsg = const_cast<TCHAR*>(&(lpcszField[1]));

         for ( int jj = 0, kk = 0; (jj <= 30 ); jj++ )
         {
            if ( isdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = pszBeaconMsg[jj] - L'0';
            }
            else if ( isxdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = toupper( pszBeaconMsg[jj] ) - L'A' + 0x0A;
            }
            if ( jj % 2 )
            {
               pacBeaconMsg[kk++] |= byteTemp;
            }
            else
            {
               byteTemp <<= 4;
               pacBeaconMsg[kk] = byteTemp;
            }
         }
      }
   }
   else
   {
   	hr = EMS_BAD_PARAM;
   }
   return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF25( LPCTSTR lpcszField, double* lpdLatitude )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snn.nnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdLatitude );
}

LPCTSTR
CEMSSitMsgField::TextMF25( const double cdLatitude )
{
	static TCHAR szText[ 32 ];
	double dLat = cdLatitude;

	if ( dLat > 99.999 ) dLat = 99.999;
	else if ( dLat < -99.999 ) dLat = -99.999;

	// snn.nnn
	sprintf( szText, "%+07.3lf", dLat );
	return szText;
}


EMS_RESULT
CEMSSitMsgField::GetMF25A( LPCTSTR lpcszField, double* lpdLatitude )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snn.nnnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdLatitude );
}

LPCTSTR
CEMSSitMsgField::TextMF25A( const double cdLatitude )
{
	static TCHAR szText[ 32 ];
	double dLat = cdLatitude;

	if ( dLat > 99.9999 ) dLat = 99.9999;
	else if ( dLat < -99.9999 ) dLat = -99.9999;

	// snn.nnnn
	sprintf( szText, "%+08.4lf", dLat );
	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF26( LPCTSTR lpcszField, double* lpdLongitude )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snnn.nnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdLongitude );
}

LPCTSTR
CEMSSitMsgField::TextMF26( const double cdLongitude )
{
	static TCHAR szText[ 32 ];
	double dLon = cdLongitude;

	if ( dLon > 999.999 ) dLon = 999.999;
	else if ( dLon < -999.999 ) dLon = -999.999;

	// snnn.nnn
	sprintf( szText, "%+08.3lf", dLon );
	return szText;
}

LPCTSTR
CEMSSitMsgField::TextMF26A( const double cdLongitude )
{
	static TCHAR szText[ 32 ];
	double dLon = cdLongitude;

	if ( dLon > 999.9999 ) dLon = 999.9999;
	else if ( dLon < -999.9999 ) dLon = -999.9999;

	// snnn.nnnn
	sprintf( szText, "%+09.4lf", dLon );
	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF26A( LPCTSTR lpcszField, double* lpdLongitude )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snnn.nnnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdLongitude );
}

EMS_RESULT CEMSSitMsgField::_GetDecimalField( LPCTSTR lpcszField, LPCSTR lpcszSyntax, double *lpdNumber )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpdNumber )
	{
		int nMinLen = _GetMinLength( lpcszSyntax ), nMaxLen = lstrlen( lpcszSyntax );
		int nFldLen = lstrlen( lpcszField );

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			hr = _CheckSyntax( lpcszField , lpcszSyntax );

			if ( hr == EMS_OK )
			{
				// SITs will have a leading "/".  Other types (i.e., CSV and XML will not).  Skip the
				// "/" only for SITs.
				if( '/' == lpcszField[0] ) 
				{
					*lpdNumber = atof( &lpcszField[1] );
				}
				else
				{
					*lpdNumber = atof( lpcszField );
				}
			}
		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::_GetDecimalField( LPCTSTR lpcszField, LPCSTR lpcszSyntax, float *lpfNumber )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpfNumber )
	{
		int nMinLen = _GetMinLength( lpcszSyntax ), nMaxLen = lstrlen( lpcszSyntax );
		int nFldLen = lstrlen( lpcszField );

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			hr = _CheckSyntax( lpcszField , lpcszSyntax );

			if ( hr == EMS_OK )
				*lpfNumber = (float) atof( &lpcszField[1] );
		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::_GetIntegerField( LPCTSTR lpcszField, LPCSTR lpcszSyntax, int *lpnNumber )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpnNumber )
	{
		int nMinLen = _GetMinLength( lpcszSyntax ), nMaxLen = lstrlen( lpcszSyntax );
		int nFldLen = lstrlen( lpcszField );

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			hr = _CheckSyntax( lpcszField , lpcszSyntax );

			if ( hr == EMS_OK )
				*lpnNumber = atoi( &lpcszField[1] );			
		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::_GetAlphaField( LPCTSTR     lpcszField, 
                                 LPCSTR      lpcszSyntax, 
                                 TCHAR*      pszString,
                                 int         iStringLen )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && pszString )
	{
		int nMinLen = _GetMinLength( lpcszSyntax );
		int nMaxLen = lstrlen( lpcszSyntax );
		int nFldLen = lstrlen( lpcszField );

		if (  ( nFldLen >= nMinLen ) 
			&& ( nFldLen <= nMaxLen ) 
			&& ( iStringLen > (nFldLen - 1) )   // is the in-buffer big enough
			)                                   // (nFldLen - 1): field content minus the starting '/' char
		{
			hr = _CheckSyntax( lpcszField , lpcszSyntax );

			if ( EMS_OK == hr )
			{
				strncpy( pszString, (lpcszField + 1), iStringLen );   // (lpcszField + 1): skip the starting '/' char
			}
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	return hr;
}


 
EMS_RESULT CEMSSitMsgField::_GetUTCConversionField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax,
													EMSUTCCONVERSION *lpUtcConversion )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpUtcConversion )
	{
		int nLen = lstrlen( lpcszField );

		memset( lpUtcConversion, 0, sizeof( EMSUTCCONVERSION ) );

		hr = _CheckSyntax( lpcszField, lpcszSyntax );

		if ( hr == EMS_OK )
		{
			TCHAR szTemp[256], *lpszToken = 0;
			int nCount = 0;

			lstrcpy( szTemp, lpcszField );

			lpszToken = _tcstok( szTemp, "/ " );

			while ( lpszToken )
			{
				switch ( nCount++ )
				{
					case 0:	lpUtcConversion->nA0 = (int)atoi( lpszToken ); break;
					case 1:	lpUtcConversion->nA1 = (int)atoi( lpszToken ); break;
					case 2:	lpUtcConversion->cDelTime = (BYTE)atoi( lpszToken ); break;
					case 3:	lpUtcConversion->cRefTime = (BYTE)atoi( lpszToken ); break;
					case 4:	lpUtcConversion->cUTCRef = (BYTE)atoi( lpszToken ); break;
					case 5:	lpUtcConversion->cWeekNb = (BYTE)atoi( lpszToken ); break;
					case 6:	lpUtcConversion->cDayNb = (BYTE)atoi( lpszToken ); break;
					case 7:	lpUtcConversion->cLeapSec = (BYTE)atoi( lpszToken ); break;
				}
				lpszToken = _tcstok( 0, " " );
			}
		}

	}
	else
		hr = EMS_BAD_PARAM;

 return hr;
}


EMS_RESULT CEMSSitMsgField::_GetScaledEphemField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, 
								 EMSSCALEDEPHEMERISDATAEX *lpScaledEphem )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpScaledEphem )
	{
		int nLen = lstrlen( lpcszField );

		memset( lpScaledEphem, 0, sizeof( EMSSCALEDEPHEMERISDATAEX ) );

		hr = _CheckSyntax( lpcszField, lpcszSyntax );

		if ( hr == EMS_OK )
		{
			TCHAR szTemp[256], *lpszToken = 0;
			int nCount = 0;

			lstrcpy( szTemp, lpcszField );

			lpszToken = _tcstok( szTemp, "/ " );

			while ( lpszToken )
			{
				switch ( nCount++ )
				{
					case  0: lpScaledEphem->baseData.i64M0 = _atoi64( lpszToken ); break;
					case  1: lpScaledEphem->baseData.i64DeltaN = _atoi64( lpszToken ); break;
					case  2: lpScaledEphem->baseData.i64E = _atoi64( lpszToken ); break;
					case  3: lpScaledEphem->baseData.i64SqrtA = _atoi64( lpszToken ); break;
					case  4: lpScaledEphem->baseData.i64OmegaO = _atoi64( lpszToken ); break;
					case  5: lpScaledEphem->baseData.i64IO = _atoi64( lpszToken ); break;
					case  6: lpScaledEphem->baseData.i64Omega = _atoi64( lpszToken ); break;
					case  7: lpScaledEphem->baseData.i64OmegaDot = _atoi64( lpszToken ); break;
					case  8: lpScaledEphem->baseData.i64IDot = _atoi64( lpszToken ); break;
					case  9: lpScaledEphem->baseData.i64UC = _atoi64( lpszToken ); break;
					case 10: lpScaledEphem->baseData.i64CUS = _atoi64( lpszToken) ; break;
					case 11: lpScaledEphem->baseData.i64CRC = _atoi64( lpszToken ); break;
					case 12: lpScaledEphem->baseData.i64CRS = _atoi64( lpszToken ); break;
					case 13: lpScaledEphem->baseData.i64CIC = _atoi64( lpszToken ); break;
					case 14: lpScaledEphem->baseData.i64CIS = _atoi64( lpszToken ); break;
					case 15: lpScaledEphem->baseData.ulTOE = (ULONG)atoi( lpszToken ); break;
					case 16: lpScaledEphem->baseData.nWeekNum = (int)atoi( lpszToken ); break;
					case 17: lpScaledEphem->baseData.cIODE = *lpszToken; break;
				}
				lpszToken = _tcstok( 0, " " );
			}
		}

	}
	else
		hr = EMS_BAD_PARAM;

 return hr;
}


EMS_RESULT CEMSSitMsgField::_GetVectorField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSVECTOR *lpVector )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpcszSyntax && lpVector )
	{
		int nLen = lstrlen( lpcszField );

		memset( lpVector, 0, sizeof( EMSVECTOR ) );

		hr = _CheckSyntax( lpcszField, lpcszSyntax );

		if ( hr == EMS_OK )
		{
			TCHAR szTemp[256], *lpszToken = 0;
			int nCount = 0;

			lstrcpy( szTemp, lpcszField );

			lpszToken = _tcstok( szTemp, "/ " );

			while ( lpszToken )
			{
				switch ( nCount++ )
				{
					case 0:	lpVector->fX = (float)atof( lpszToken ); break;
					case 1:	lpVector->fY = (float)atof( lpszToken ); break;
					case 2:	lpVector->fZ = (float)atof( lpszToken ); break;
				}
				lpszToken = _tcstok( 0, " " );
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

 return hr;
}

EMS_RESULT CEMSSitMsgField::_GetTime( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSTIME *lpTime )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszField && lpTime && lpcszSyntax )
	{
		int nMinLen = _GetMinLength( lpcszSyntax ), nMaxLen = lstrlen( lpcszSyntax );
		int nFldLen = lstrlen( lpcszField );

		lpTime->intTime = 0;

		if ( ( nFldLen >= nMinLen ) && ( nFldLen <= nMaxLen ) )
		{
			TCHAR szTemp[32], *lpSpace = 0, *lpNextSpace = 0, szNumber[16];
			CEMSTime timeTemp;
			int nYear = 0, nHours=0, nMinutes=0;
			double dSeconds=0.0;
			double dJulianDay = 0.0;

			hr = _CheckSyntax( lpcszField , lpcszSyntax );

			if ( hr == EMS_OK )
			{
				lstrcpy( szTemp, lpcszField );

				lpSpace = _tcschr( szTemp, ' ' );

				if ( lpSpace )
			 		*lpSpace = 0;

				nYear = atoi( &szTemp[1] );
            nYear += ( nYear >= 80 ) ? 1900 : 2000;         // year 2080 bug

				lpNextSpace = _tcschr( lpSpace+1, ' ' );

				if ( lpNextSpace )
					*lpNextSpace = 0;

				dJulianDay = atof( lpSpace+1 );

				timeTemp.SetTime( nYear, dJulianDay - 1 );

				_tcsncpy( szNumber, ++lpNextSpace, 2 );

				szNumber[2] = 0;

				nHours = atoi( szNumber );

				timeTemp.AddHours( nHours );

				_tcsncpy( szNumber, lpNextSpace+2, 2 );

				szNumber[2] = 0;

				nMinutes = atoi( szNumber );

				timeTemp.AddMinutes( nMinutes );

				lpNextSpace += 4;

				dSeconds = atof( lpNextSpace+1 );

				timeTemp.AddSeconds( (float)dSeconds );

				if ( lpTime )
					*lpTime = timeTemp;
			}
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF27(  LPCTSTR     lpcszField,
                           double*     lpdErrorElAngle,
                           double*     lpdErrorElMajor,
                           double*     lpdErrorElMinor )
{
   EMS_RESULT hr = EMS_OK;

   const TCHAR c_szSyntax[] = TEXT("/nnn nnn.n nnn.n");

	hr = _CheckSyntax( lpcszField, c_szSyntax );

   if ( EMS_OK == hr )
   {
      *lpdErrorElAngle  = atof( &(lpcszField[1]) );
      *lpdErrorElMajor  = atof( &(lpcszField[5]) );
      *lpdErrorElMinor  = atof( &(lpcszField[11]) );
   }
   return hr;
}

LPCTSTR CEMSSitMsgField::TextMF27( double dErrorElAngle, double dErrorElMajor, double dErrorElMinor )
{
	static TCHAR szText[ 32 ];

	if ( !_finite( dErrorElAngle ) )
		dErrorElAngle = 0.0;

	while (dErrorElAngle > 360.0 )
		dErrorElAngle -= 360.0;

	while (dErrorElAngle < 0.0 )
		dErrorElAngle += 360.0;

	if ( dErrorElAngle >= 359.5 ) 
		dErrorElAngle = 0.0;

	if ( !_finite( dErrorElMajor ) )
		dErrorElMajor = 999.9;

	if ( dErrorElMajor > 999.9 )
		dErrorElMajor = 999.9;

	if ( dErrorElMajor < 0.1 )
		dErrorElMajor = 0.1;

	if ( !_finite( dErrorElMinor ) )
		dErrorElMinor = 999.9;

	if ( dErrorElMinor > 999.9 )
		dErrorElMinor = 999.9;

	if ( dErrorElMinor < 0.1 )
		dErrorElMinor = 0.1;

	_stprintf( szText, TEXT("%03d %05.1lf %05.1lf"), (int)dErrorElAngle,
									dErrorElMajor, dErrorElMinor );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF28( LPCTSTR lpcszField, double *lpdProbability )
{
   const TCHAR c_szSyntax[ ] = TEXT("/nn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdProbability );
}

EMS_RESULT
CEMSSitMsgField::GetMF29( LPCTSTR lpcszField, EMSTIME *lptimeNextVis )
{
   return GetMF3( lpcszField, lptimeNextVis );
}

LPCTSTR
CEMSSitMsgField::TextMF29( EMSTIME timeNextVis )
{
	static TCHAR szText[ c_iMinTimeStringLen ];

	_TextTime( timeNextVis, szText, c_iMinTimeStringLen );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF30( LPCTSTR lpcszField, double *lpdConfidence )
{
   const TCHAR c_szSyntax[ ] = TEXT("/n");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdConfidence );
}

EMS_RESULT
CEMSSitMsgField::GetMF31(  LPCTSTR     lpcszField, 
                           double*     lpdDataResSdev, 
                           double*     lpdDataResTrend )
{
   const TCHAR c_szSyntax[] = TEXT("/nnn.n nnn.n");

   EMS_RESULT hr = _CheckSyntax( lpcszField, c_szSyntax );

   if ( EMS_OK == hr )
   {
      *lpdDataResSdev   = atof( &(lpcszField[1]) );
      *lpdDataResTrend  = atof( &(lpcszField[7]) );
   }
   return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF32( LPCTSTR lpcszField, int *lpnVectorCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnVectorCount );
}

EMS_RESULT CEMSSitMsgField::GetMF34( LPCTSTR lpcszField, EMSTIME *lptimeOrbit )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nnn");

	return _GetTime( lpcszField, c_szSyntax, lptimeOrbit );
}


LPCTSTR CEMSSitMsgField::TextMF34( EMSTIME timeOrbit )
{
	static TCHAR szText[ c_iMinTime2StringLen ];

	_TextTime2( timeOrbit, szText, c_iMinTime2StringLen );

	return szText;
}


EMS_RESULT CEMSSitMsgField::GetMF35( LPCTSTR lpcszField, EMSVECTOR *lpvPosition )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnn.nnnn snnnn.nnnn snnnn.nnnn");

	return _GetVectorField( lpcszField, c_szSyntax, lpvPosition );
}

EMS_RESULT CEMSSitMsgField::GetMF35A( LPCTSTR lpcszField, EMSVECTOR *lpvPosition )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnnn.nnnn snnnnn.nnnn snnnnn.nnnn");

	return _GetVectorField( lpcszField, c_szSyntax, lpvPosition );
}

EMS_RESULT CEMSSitMsgField::GetMF36( LPCTSTR lpcszField, EMSVECTOR *lpvVelocity )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnn.nnnnn snnn.nnnnn snnn.nnnnn");

	return _GetVectorField( lpcszField, c_szSyntax, lpvVelocity );
}


EMS_RESULT CEMSSitMsgField::GetMFB01( LPCTSTR lpcszField, EMSUTCCONVERSION *lpUtcConversion )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnnnnnnnn snnnnnnn snnn nnnnnn nnn nnn n snnn");

	return _GetUTCConversionField( lpcszField, c_szSyntax, lpUtcConversion );
}


EMS_RESULT CEMSSitMsgField::GetMFB02( LPCTSTR lpcszField, EMSSCALEDEPHEMERISDATAEX *lpScaledEphem )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnnnnnnnn snnnnn nnnnnnnnnn nnnnnnnnnn snnnnnnnnnn snnnnnnnnnn snnnnnnnnnn snnnnnnn snnnn snnnnn snnnnn snnnnn snnnnn snnnnn snnnnn nnnnnn nnnn nnn");

	return _GetScaledEphemField( lpcszField, c_szSyntax, lpScaledEphem );
}


EMS_RESULT CEMSSitMsgField::GetMF36A( LPCTSTR lpcszField, EMSVECTOR *lpvVelocity )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snn.nnnnnn snn.nnnnnn snn.nnnnnn");

	return _GetVectorField( lpcszField, c_szSyntax, lpvVelocity );
}

EMS_RESULT CEMSSitMsgField::GetMF37( LPCTSTR lpcszField, EMSTIME *lptimeCalib )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nnn");

	return _GetTime( lpcszField, c_szSyntax, lptimeCalib );
}

LPCTSTR
CEMSSitMsgField::TextMF37( EMSTIME timeCalib )
{
	static TCHAR szText[ c_iMinTime2StringLen ];

	_TextTime2( timeCalib, szText, c_iMinTime2StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF38( LPCTSTR lpcszField, double *lpdCalibFreq )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnnnn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdCalibFreq );
}

// Note that the %011 width specification in the format statement 
// simply ensures a minumum number of characters ... it will allow more than 11
// Therefore ... ensure that the numeric value is within range
LPCTSTR CEMSSitMsgField::TextMF38( const double cdCalibFreq )
{
	static TCHAR szText[ 32 ];
	double dFreq = cdCalibFreq;

	if ( dFreq > 9999999.999 )
	{
		dFreq = 9999999.999;
	}
	else if ( dFreq < 0 )
	{
		dFreq = 0;
	}

	_stprintf( szText, TEXT("%011.3lf"), dFreq );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF38A( LPCTSTR lpcszField, double *lpdCalibFreq )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnnnnn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdCalibFreq );
}

LPCTSTR CEMSSitMsgField::TextMF38A( const double cdCalibFreq )
{
	static TCHAR szText[ 32 ];
	double dFreq = cdCalibFreq;

	if ( dFreq > 99999999.999 )
	{
		dFreq = 99999999.999;
	}
	else if ( dFreq < 0 )
	{
		dFreq = 0.0;
	}

	_stprintf( szText, TEXT("%012.3lf"), dFreq );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF44( LPCTSTR lpcszField,  int *lpnNumberSpacecraft )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnNumberSpacecraft );
}

EMS_RESULT CEMSSitMsgField::GetMF64( LPCTSTR lpcszField, double *lpdFreqOffset )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdFreqOffset );
}

EMS_RESULT CEMSSitMsgField::GetMF65( LPCTSTR lpcszField, double *lpdFreqDrift )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdFreqDrift );
}

EMS_RESULT CEMSSitMsgField::GetMF66( LPCTSTR lpcszField, EMSTIME *lpTimeCalib )
{
	return GetMF3( lpcszField, lpTimeCalib );
}

LPCTSTR
CEMSSitMsgField::TextMF66( EMSTIME tm )
{
	static TCHAR szText[ c_iMinTimeStringLen ];

	_TextTime( tm, szText, c_iMinTimeStringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF601( LPCTSTR lpcszField, int* lpnSolutions )
{
   const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

   return _GetIntegerField( lpcszField, c_szSyntax, lpnSolutions );
}

EMS_RESULT CEMSSitMsgField::GetMF602( LPCTSTR lpcszField, EMSTIME *lptimeAOS )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeAOS );
}

LPCTSTR 
CEMSSitMsgField::TextMF602( EMSTIME timeAOS )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeAOS, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF602A( LPCTSTR lpcszField, EMSTIME *lptimeAOS )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeAOS );
}

LPCTSTR
CEMSSitMsgField::TextMF602A( EMSTIME timeAOS )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeAOS, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF603( LPCTSTR lpcszField, EMSTIME *lptimeLOS )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeLOS );
}

LPCTSTR
CEMSSitMsgField::TextMF603( EMSTIME timeLOS )
{ 
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeLOS, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF603A( LPCTSTR lpcszField, EMSTIME *lptimeLOS )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeLOS );
}

LPCTSTR
CEMSSitMsgField::TextMF603A( EMSTIME timeLOS )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeLOS, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT
CEMSSitMsgField::GetMF604( LPCTSTR lpcszField, int *lpnSecsDuration )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSecsDuration );
}


EMS_RESULT CEMSSitMsgField::GetMF605( LPCTSTR lpcszField, LPEMSSITMF605 lpMF )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[ ] = TEXT("/aaaa");

	if ( lpcszField && lpMF )
	{
		int nLen = lstrlen( lpcszField );

		hr = _CheckSyntax( lpcszField, c_szSyntax );

		if ( hr == EMS_OK )
		{
			for ( int i = 1; ( i < nLen ) && ( i < 5 ); i++ )
				lpMF->cValue[i-1] = lpcszField[i];
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF606( LPCTSTR lpcszField, int *lpnCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnCount );
}

EMS_RESULT CEMSSitMsgField::GetMF607( LPCTSTR lpcszField, double *lpdOrbitPositionOffset )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnn.nnnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdOrbitPositionOffset );
}

EMS_RESULT CEMSSitMsgField::GetMF608( LPCTSTR lpcszField, double *lpdOrbitVelocityOffset )
{
   const TCHAR c_szSyntax[ ] = TEXT("/snnnn.nnnn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdOrbitVelocityOffset );
}

EMS_RESULT
CEMSSitMsgField::GetMF609( LPCTSTR lpcszField, EMSTIME *lpTimeSolnProcessing )
{
   const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

   return _GetTime( lpcszField, c_szSyntax, lpTimeSolnProcessing );
}

LPCTSTR
CEMSSitMsgField::TextMF609( EMSTIME timeProcessCompleted )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeProcessCompleted, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF610( LPCTSTR lpcszField, LPEMSSITMF610 lpData )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[ ] = TEXT("/aaa");

	if ( lpcszField && lpData )
	{
		int nLen = lstrlen( lpcszField );

		hr = _CheckSyntax( lpcszField, c_szSyntax );

		if ( hr == EMS_OK )
		{
			for ( int i = 1; ( i < nLen ) && ( i < 4 ); i++ )
				lpData->cValue[i-1] = lpcszField[i];
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF611( LPCTSTR lpcszField, int* lpnOrbitUpdateStatus )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpcszField && lpnOrbitUpdateStatus )
   {
	   const TCHAR c_szSyntax[ ] = TEXT("/aa");

		hr = _CheckSyntax( lpcszField, c_szSyntax );

		if ( hr == EMS_OK )
		{
         if ( 0 == _tcsnicmp( _T("IN"), &(lpcszField[1]), 2 ) )
         {
            *lpnOrbitUpdateStatus = 1;
         }
         else if ( 0 == _tcsnicmp( _T("OU"), &(lpcszField[1]), 2 ) )
         {
            *lpnOrbitUpdateStatus = 2;
         }
         else if ( 0 == _tcsnicmp( _T("PR"), &(lpcszField[1]), 2 ) )
         {
            *lpnOrbitUpdateStatus = 3;
         }
         else
         {
            *lpnOrbitUpdateStatus = 0;
         }
      }
   }
   return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF612( LPCSTR   lpcszField, 
                           TCHAR*   pszString, 
                           int      iStringLen )
{
   const TCHAR c_szSyntax[ ] = TEXT("/aaaaaaaa");

	return _GetAlphaField( lpcszField, c_szSyntax, pszString, iStringLen );
}

EMS_RESULT CEMSSitMsgField::GetMF613( LPCTSTR lpcszField, int *lpnAzAOL )
{	
	const TCHAR c_szSyntax[] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAzAOL );
}

EMS_RESULT CEMSSitMsgField::GetMF614( LPCTSTR lpcszField, int *lpnAzPeak )
{
	const TCHAR c_szSyntax[] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAzPeak );
}

EMS_RESULT CEMSSitMsgField::GetMF615( LPCTSTR lpcszField, int *lpnAzLOS )
{
	const TCHAR c_szSyntax[] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAzLOS );
}

EMS_RESULT CEMSSitMsgField::GetMF616( LPCTSTR lpcszField, int *lpnMaxElevation )
{
	const TCHAR c_szSyntax[] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnMaxElevation );
}

EMS_RESULT CEMSSitMsgField::GetMF618( LPCTSTR lpcszField, EMSSITSOLNTYPE *lpSolnType )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITSOLNTYPE solnType = EMSSST_Unknown;

	if ( lpcszField && *lpcszField )
	{
		if ( lstrlen( lpcszField )== 3 ) 
		{
			if ( lstrcmp( lpcszField , TEXT("/BE") ) == 0 )
				solnType = EMSSST_Beacon;
			else if ( lstrcmp( lpcszField , TEXT("/IN") ) == 0 )
				solnType = EMSSST_Interferer;
			else if ( lstrcmp( lpcszField , TEXT("/UN") ) == 0 )
				solnType = EMSSST_Unknown;
			else 
				hr = EMS_SIT_SYNTAX_ERROR;
		}
		else
	 		hr = EMS_SIT_SYNTAX_ERROR;
	}
	else
		hr = EMS_SIT_SYNTAX_ERROR;


	if ( lpSolnType )
		*lpSolnType = solnType;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF619( LPCTSTR lpcszField, int *lpnTransmissionType )
{
	const TCHAR c_szSyntax[] = TEXT("/a");
	int nType = '?';
	EMS_RESULT hr = EMS_OK;

	hr = _CheckSyntax( lpcszField, c_szSyntax );

	if ( hr == EMS_OK )
	{
		switch ( lpcszField[ 1 ] )
		{
			case 'X': *lpnTransmissionType = EMSSMT_Invalid;  break;
			case 'C': *lpnTransmissionType = EMSSMT_Combination;  break;
			case 'N': *lpnTransmissionType = EMSSMT_Normal;       break;
			case 'T': *lpnTransmissionType = EMSSMT_Test;         break;
			default:
				hr = EMS_SIT_SYNTAX_ERROR;
				break;
		}
	}
	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF620( LPCTSTR lpcszField, EMSTIME *lptimeStart )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn");

	return _GetTime( lpcszField, c_szSyntax, lptimeStart );
}

EMS_RESULT CEMSSitMsgField::GetMF620Ex( LPCTSTR lpcszField, EMSTIME *lptimeStart )
{
	const TCHAR c_szSyntax[ ] = TEXT("nn nnn nnnn");

	return _GetTime( lpcszField, c_szSyntax, lptimeStart );
}

EMS_RESULT CEMSSitMsgField::GetMF621( LPCTSTR lpcszField, EMSTIME *lptimeEnd )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn");

	return _GetTime( lpcszField, c_szSyntax, lptimeEnd );
}


EMS_RESULT
CEMSSitMsgField::GetMF622( LPCTSTR lpcszField, double* lpdLatLongCorrCoeff )
{
   const TCHAR c_szSyntax[ ] = TEXT("/n.nnnn");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdLatLongCorrCoeff );
}


LPCTSTR CEMSSitMsgField::TextMF622( double dCorrCoeff )
{
	static TCHAR szText[ 16 ];
	
	_stprintf( szText, TEXT("%06.4lf"), fabs( dCorrCoeff ) );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF623( LPCTSTR lpcszField, int *lpnSeconds )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSeconds );
}

EMS_RESULT CEMSSitMsgField::GetMF624( LPCTSTR lpcszField, int *lpnSeconds )
{
	return GetMF623( lpcszField, lpnSeconds );
}

EMS_RESULT CEMSSitMsgField::GetMF625( LPCSTR lpcszField, int *lpnSeconds )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSeconds );
}

EMS_RESULT CEMSSitMsgField::GetMF626( LPCSTR lpcszField, int *lpnPreamble, int *lpnPF1, int *lpnPF2 )
{
	const TCHAR c_szSyntax[ ] = TEXT("/n n n");
	EMS_RESULT hr = _CheckSyntax( lpcszField, c_szSyntax );

	if ( hr == EMS_OK )
	{
		if ( lpnPreamble )
			*lpnPreamble = lpcszField[ 1 ] - '0'; 			

		if ( lpnPF1 )
			*lpnPF1 = lpcszField[ 3 ] - '0'; 			

		if ( lpnPF2 )
			*lpnPF2 = lpcszField[ 5 ] - '0'; 			
	}
	return hr;
}

LPCTSTR	   
CEMSSitMsgField::TextMF626( const int ciErrCountPreamble, const int ciErrCountPDF1, const int ciErrCountPDF2 )
{
	static TCHAR szText[ 32 ];

	_stprintf( szText, TEXT("%01d %01d %01d"),
		(ciErrCountPreamble >=0 && ciErrCountPreamble <=9) ? ciErrCountPreamble : 9,
		(ciErrCountPDF1 >=0 && ciErrCountPDF1 <=9) ? ciErrCountPDF1 : 9,
		(ciErrCountPDF2 >=0 && ciErrCountPDF2 <=9) ? ciErrCountPDF2 : 9 );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF627( LPCSTR lpcszField, int *lpnDuplicates )
{
	const TCHAR c_szSyntax[ ] = TEXT("/n");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnDuplicates );
}

EMS_RESULT CEMSSitMsgField::GetMF628( LPCSTR lpcszField, double *lpdCarrierPower )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnn.nn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdCarrierPower );
}

EMS_RESULT
CEMSSitMsgField::GetMF629( LPCSTR lpcszField, int *lpnSecsCollecting )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSecsCollecting );
}

EMS_RESULT
CEMSSitMsgField::GetMF630( LPCSTR lpcszField, int *lpnPercentageCollecting )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnPercentageCollecting );
}

EMS_RESULT
CEMSSitMsgField::GetMF633( LPCSTR lpcszField, int *lpnAlarmMessages )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnAlarmMessages );
}

EMS_RESULT
CEMSSitMsgField::GetMF634( LPCSTR lpcszField, int *lpnWarningMessages )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnWarningMessages );
}

EMS_RESULT CEMSSitMsgField::GetMF635( LPCSTR lpcszField, int *lpnMsgCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnMsgCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF636( LPCSTR lpcszField, int *lpnSarrMessages )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnSarrMessages );
}

EMS_RESULT
CEMSSitMsgField::GetMF637( LPCTSTR  lpcszField, 
                           int*     lpnPDSRecoveryRate,
                           int*     lpnFramesMissed )
{
   EMS_RESULT hr = EMS_OK;

   const TCHAR c_szSyntax[] = TEXT("/nnn nnnn");

	hr = _CheckSyntax( lpcszField, c_szSyntax );

   if ( EMS_OK == hr )
   {
	   *lpnPDSRecoveryRate  = atoi( &(lpcszField[1]) );
	   *lpnFramesMissed     = atoi( &(lpcszField[5]) );
   }
   return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF638( LPCSTR lpcszField, int *lpnTotalPDSCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnTotalPDSCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF639( LPCSTR lpcszField, int *lpnDistinctPDSCount )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnDistinctPDSCount );
}

EMS_RESULT
CEMSSitMsgField::GetMF640( LPCSTR   lpcszField, 
                           TCHAR*   pszString, 
                           int      iStringLen )
{
   const TCHAR c_szSyntax[ ] = TEXT("/aa");

	return _GetAlphaField( lpcszField, c_szSyntax, pszString, iStringLen );
}

EMS_RESULT
CEMSSitMsgField::GetMF641( LPCSTR   lpcszField, 
                           TCHAR*   pszString, 
                           int      iStringLen )
{
   const TCHAR c_szSyntax[ ] = TEXT("/aaaaaaaaaaaaaaaa");

	return _GetAlphaField( lpcszField, c_szSyntax, pszString, iStringLen );
}

EMS_RESULT CEMSSitMsgField::GetMF645( LPCSTR lpcszField, EMSSITFIELD* pSitField )
{
	EMS_RESULT hr = EMS_OK;

	if( !pSitField )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		const TCHAR c_szSyntax[] = TEXT("/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
		hr = _CheckSyntax( lpcszField, c_szSyntax );
	}

	if( SUCCEEDED(hr) )
	{
		int iLength = strlen( lpcszField);

		// Cannot exceed 64 characters plus the preceeding "/"
		if( 65 >= iLength )
		{
			// Copy all but the preceeding "/"
			if( 2 <= iLength )
			{
				LPCSTR lpszSecToken = lpcszField + 1;

				if( lpszSecToken )
				{
					strncpy( pSitField->szText, lpszSecToken, EMS_MAX_SIT_LINE_LENGTH );

					pSitField->nLength = strlen( lpszSecToken );
				}
			}
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF647( LPCSTR lpcszField, double *lpdFreq, double *lpdFreqOffset )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnnnnnn.nnn snnnn.nnn");
	EMS_RESULT hr = _CheckSyntax( lpcszField, c_szSyntax );
	TCHAR szTemp[ 256 ], *lpszToken=0;
	int nToken = 0;

	if ( hr == EMS_OK )
	{
		lstrcpy( szTemp, lpcszField );

		lpszToken = _tcstok( szTemp, TEXT("/ ") );

		while ( lpszToken )
		{
			switch ( nToken++ )
			{
				case 0: 
					if ( lpdFreq )
						*lpdFreq = atof( lpszToken );
					break;

				case 1: 
					if ( lpdFreqOffset )
						*lpdFreqOffset = atof( lpszToken );
					break;
			}
			lpszToken = _tcstok( 0, TEXT(" ") );
		}
	}
	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF648( LPCSTR lpcszField, EMSTIME *lpTimeMsg, double *lpdTimeOffset )
{
	const TCHAR c_szTimeSyntax[ ] = TEXT("/nn nnn nnnn nn.nnnnnn");
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nnnnnn sn.nnnnnn");
	EMS_RESULT hr = _CheckSyntax( lpcszField, c_szSyntax );
	TCHAR szTemp[ 256 ];

	if ( hr == EMS_OK )
	{
		lstrcpy( szTemp, lpcszField );

		szTemp[ 22 ] = 0;

		hr = _GetTime( szTemp, c_szTimeSyntax, lpTimeMsg );

		if ( lpdTimeOffset )
			*lpdTimeOffset = atof( &szTemp[23] );
	}
	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF650( LPCTSTR lpcszField, int *lpnCheckCode, int *lpnCheckSum )
{
	// field syntax is "/annnnnn" but going to cheat to reuse code
	const TCHAR c_szCheckSumSyntax[ ] = TEXT("annnnnn");

	// JB-National C-S Interface Spec., Version F says check code length is 5 digits.  We'll go with the spec.
	//const TCHAR c_szCheckSumSyntax[ ] = TEXT("annnnn");
	const TCHAR c_szCheckCodeSyntax[ ] = TEXT("/a");
	EMS_RESULT hr = EMS_OK;

	if ( !lpcszField || ( lpcszField[0] != '/' ) )
		hr = EMS_SIT_SYNTAX_ERROR;
	else
	{
		hr = _GetIntegerField( &lpcszField[1], c_szCheckSumSyntax, lpnCheckSum );

		if ( ( hr == EMS_OK ) && lpnCheckCode )
			*lpnCheckCode = (int)lpcszField[1];
	}
	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF652( LPCTSTR lpcszField, EMSTIME *lptimeStart )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeStart );
}

EMS_RESULT CEMSSitMsgField::GetMF652Ex( LPCTSTR lpcszField, EMSTIME *lptimeStart )
{
	const TCHAR c_szSyntax[ ] = TEXT("nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeStart );
}

EMS_RESULT CEMSSitMsgField::GetMF653( LPCTSTR lpcszField, double *lpdDuration )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn.nn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdDuration );
}

EMS_RESULT CEMSSitMsgField::GetMF654( LPCTSTR lpcszField, double *lpdFreqBandwidth )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnnn.n");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdFreqBandwidth );
}

EMS_RESULT CEMSSitMsgField::GetMF655( LPCTSTR lpcszField, int nMax, 
										double **lplpdFreqCoeff,	int *lpnCount )
{
	EMS_RESULT hr = EMS_OK;
	int nCount = 0;

	if ( lpcszField && *lpcszField && lplpdFreqCoeff )
	{
		TCHAR szTemp[ 256 ], *lpszToken = 0;

		lstrcpy( szTemp, lpcszField );

		lpszToken = _tcstok( szTemp, TEXT("/ ") );

		while ( lpszToken )
		{
			if ( nCount < nMax )
 				*lplpdFreqCoeff[ nCount++ ] = atof( lpszToken );

			lpszToken = _tcstok( 0, TEXT(" ") );
		}

	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpnCount )
		*lpnCount = nCount;

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF656( LPCTSTR lpcszField, int *lpnOrderPolynomial)
{
	const TCHAR c_szSyntax[ ] = TEXT("/n");

	return _GetIntegerField( lpcszField, c_szSyntax, lpnOrderPolynomial );
}

// manoeuvre type
EMS_RESULT CEMSSitMsgField::GetMF660( LPCTSTR              lpcszField, 
                           EMSMANOEUVRETYPE*    pManoeuvreType )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[] = TEXT("/aa");
	TCHAR szBuf[3];   // "aa" + null

	hr = _GetAlphaField( lpcszField, c_szSyntax, szBuf, sizeof(szBuf) );

	if ( EMS_OK == hr )
	{
		if ( 0 == strncmp( "IP", szBuf, 2 ) )
		{
			*pManoeuvreType = MANOEUVRETYPE_IP;
		}
		else if ( 0 == strncmp( "OP", szBuf, 2 ) )
		{
			*pManoeuvreType = MANOEUVRETYPE_OP;
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	return hr;
}

LPCTSTR CEMSSitMsgField::TextMF660( EMSMANOEUVRETYPE manType )
{
	static TCHAR szText[ 16 ];

	switch ( manType )
	{
		default:
		case MANOEUVRETYPE_IP:      // "in-plane" manoeuvre
			lstrcpy( szText, TEXT("IP") );
			break;

		case MANOEUVRETYPE_OP:      // "out-plane" manoeuvre
			lstrcpy( szText, TEXT("OP") );
			break;
	}

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF67( LPCTSTR lpcszField, EMSTIME* pstrTime )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nnnnnn");

	return _GetTime( lpcszField, c_szSyntax, pstrTime );
}

LPCTSTR CEMSSitMsgField::TextMF67( EMSTIME tm )
{
	static TCHAR szText[ c_iMinTime3StringLen ];

	_TextTime3( tm, szText, c_iMinTime3StringLen );

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF67( INT64 tm )
{
	EMSTIME time;
	time.intTime = tm;

	return TextMF67( time );
}

EMS_RESULT CEMSSitMsgField::GetMF67Ex( LPCTSTR lpcszField, EMSTIME* pstrTime )
{
	// Assumes no leading "/"
#ifdef UNICODE
	std::wstring oszField = L"/";
#else
	std::string oszField = "/";
#endif

	oszField.append(lpcszField);


	return GetMF67( oszField.c_str(), pstrTime );
}

EMS_RESULT CEMSSitMsgField::GetMF68( LPCTSTR lpcszField, double* pdFreq )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn.nnnnnnnnn");

	return _GetDecimalField( lpcszField, c_szSyntax, pdFreq );
}

EMS_RESULT CEMSSitMsgField::GetMF69( LPCTSTR lpcszField, double* pdOffset )
{
	const TCHAR c_szSyntax[ ] = TEXT("/n.nnnnnn");

	return _GetDecimalField( lpcszField, c_szSyntax, pdOffset );
}

EMS_RESULT CEMSSitMsgField::GetMF70( LPCTSTR lpcszField, double* pdOffset )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snnnnn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, pdOffset );
}

EMS_RESULT CEMSSitMsgField::GetMF71( LPCTSTR lpcszField, int* piAntennaData )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, piAntennaData );
}

EMS_RESULT CEMSSitMsgField::GetMF72( LPCTSTR lpcszField, double* pdCN0 )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn.n");

	return _GetDecimalField( lpcszField, c_szSyntax, pdCN0 );
}

EMS_RESULT CEMSSitMsgField::GetMF74( LPCTSTR lpcszField, int* piNumDataBlocks )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn");

	return _GetIntegerField( lpcszField, c_szSyntax, piNumDataBlocks );
}

EMS_RESULT CEMSSitMsgField::GetMF75( LPCTSTR lpcszField, double* pdBitRate )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn.nnn");

	return _GetDecimalField( lpcszField, c_szSyntax, pdBitRate );
}

EMS_RESULT CEMSSitMsgField::GetMF76( LPCTSTR lpcszField, WORD* pwSpare )
{
	const TCHAR c_szSyntax[ ] = TEXT("/hhhh");

	EMS_RESULT hr = _CheckSyntax( lpcszField , c_szSyntax );

	if ( EMS_OK == hr )
	{
		ULONG ulValue = _tcstoul( lpcszField + 1, NULL, 16 );

		*pwSpare = (WORD) ulValue;
	}

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF76Ex( LPCTSTR lpcszField, WORD* pwSpare )
{
	const TCHAR c_szSyntax[ ] = TEXT("hhhh");

	EMS_RESULT hr = _CheckSyntax( lpcszField , c_szSyntax );

	if ( EMS_OK == hr )
	{
		ULONG ulValue = _tcstoul( lpcszField + 1, NULL, 16 );

		*pwSpare = (WORD) ulValue;
	}

	return hr;
}

// time of manoeuvre start
EMS_RESULT CEMSSitMsgField::GetMF661( LPCTSTR     lpcszField, 
                           EMSTIME*    pManoeuvreStartTime )
{
	return GetMF3( lpcszField, pManoeuvreStartTime );
}

// manoeuvre duration
EMS_RESULT	CEMSSitMsgField::GetMF662( LPCTSTR     lpcszField, 
                           int*        piManoeuvreDuration )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, piManoeuvreDuration );
}

// manoeuvre type
EMS_RESULT CEMSSitMsgField::GetMF663( LPCTSTR                 lpcszField, 
                           EMSMANOEUVRESTATUS*     pManoeuvreStatus )
{
	EMS_RESULT hr = EMS_OK;
	const TCHAR c_szSyntax[] = TEXT("/aa");
	TCHAR szBuf[3];   // "aa" + null

	hr = _GetAlphaField( lpcszField, c_szSyntax, szBuf, sizeof(szBuf) );

	if ( EMS_OK == hr )
	{
		if ( 0 == strncmp( "PL", szBuf, 2 ) )
		{
			*pManoeuvreStatus = MANOEUVRESTATUS_PL;
		}
		else if ( 0 == strncmp( "AC", szBuf, 2 ) )
		{
			*pManoeuvreStatus = MANOEUVRESTATUS_AC;
		}
		else if ( 0 == strncmp( "XX", szBuf, 2 ) )
		{
			*pManoeuvreStatus = MANOEUVRESTATUS_XX;
		}
		else
		{
			hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	return hr;
}

LPCTSTR CEMSSitMsgField::TextMF663( EMSMANOEUVRESTATUS manStatus )
{
	static TCHAR szText[ 16 ];

	switch ( manStatus )
	{
		case MANOEUVRESTATUS_PL:
			lstrcpy( szText, TEXT("PL") );
			break;

		case MANOEUVRESTATUS_AC:
			lstrcpy( szText, TEXT("AC") );
			break;
		
		default:
		case MANOEUVRESTATUS_XX:
			lstrcpy( szText, TEXT("XX") );
			break;
	}

	return szText;
}

// orbit effective time

EMS_RESULT CEMSSitMsgField::GetMF664( LPCTSTR     lpcszField, 
                           EMSTIME*    lptimeOrbitEffective )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeOrbitEffective );
}

EMS_RESULT CEMSSitMsgField::GetMF665( LPCTSTR lpcszField, WORD* pwStatus )
{
	const TCHAR c_szSyntax[ ] = TEXT("/hhhh");

	EMS_RESULT hr = _CheckSyntax( lpcszField , c_szSyntax );

	if ( EMS_OK == hr )
	{
		ULONG ulValue = _tcstoul( lpcszField + 1, NULL, 16 );

		*pwStatus = (WORD) ulValue;
	}

	return hr;
}

EMS_RESULT CEMSSitMsgField::GetMF666( LPCTSTR lpcszField, EMSTIME *lptmLastClockSync )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptmLastClockSync );
}

LPCTSTR CEMSSitMsgField::TextMF666( EMSTIME timeClkSync )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeClkSync, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF667( LPCTSTR lpcszField, EMSTIME *lptmEarliestSARP )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptmEarliestSARP );
}

LPCTSTR CEMSSitMsgField::TextMF667( EMSTIME tmEarliestSARP )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( tmEarliestSARP, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF668( LPCTSTR lpcszField, EMSTIME *lptmLastSARP )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptmLastSARP );
}

LPCTSTR CEMSSitMsgField::TextMF668( EMSTIME timeLastSARP )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime1( timeLastSARP, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF669( LPCTSTR lpcszField, double* pdMedianLocAcc )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnn.nn");

	return _GetDecimalField( lpcszField, c_szSyntax, pdMedianLocAcc );
}

EMS_RESULT
CEMSSitMsgField::GetMF677( LPCSTR   lpcszField, 
                           TCHAR*   pszString, 
                           int      iStringLen )
{
	const TCHAR c_szSyntax[ ] = TEXT("/aaaaaaaaaaaaaaa");

	return _GetAlphaField( lpcszField, c_szSyntax, pszString, iStringLen );
}

EMS_RESULT
CEMSSitMsgField::GetMF678( LPCSTR   lpcszField, 
                           TCHAR*   pcConStatus )
{
	const TCHAR c_szSyntax[ ] = TEXT("/a");
	
	const long clStrLen = 2;
	TCHAR szString[clStrLen];

	EMS_RESULT hr = _GetAlphaField( lpcszField, c_szSyntax, szString, clStrLen );

	if( EMS_OK == hr )
		*pcConStatus = szString[0];

	return hr;
}

EMS_RESULT
CEMSSitMsgField::GetMF679( LPCSTR   lpcszField, 
                           TCHAR*   pcConType )
{
	const TCHAR c_szSyntax[ ] = TEXT("/a");
	
	const long clStrLen = 2;
	TCHAR szString[clStrLen];

	EMS_RESULT hr = _GetAlphaField( lpcszField, c_szSyntax, szString, clStrLen );

	if( EMS_OK == hr )
		*pcConType = szString[0];

	return hr;
}


EMS_RESULT 
CEMSSitMsgField::GetMFN1( LPCTSTR lpcszField, int* lpiWaveID )
{
	const TCHAR c_szSyntax[ ] = TEXT("/snn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpiWaveID );
}


EMS_RESULT 
CEMSSitMsgField::GetMFN4( LPCTSTR lpcszField, EMSTIME *lptimeFirst )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeFirst );
}

LPCTSTR
CEMSSitMsgField::TextMFN4( EMSTIME timeFirst )
{
	static TCHAR szText[ c_iMinTime2StringLen ];

	_TextTime1( timeFirst, szText, c_iMinTime1StringLen );

	return szText;
}

EMS_RESULT 
CEMSSitMsgField::GetMFN5( LPCTSTR lpcszField, EMSTIME *lptimeLast )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nn nnn nnnn nn.nn");

	return _GetTime( lpcszField, c_szSyntax, lptimeLast );
}

LPCTSTR
CEMSSitMsgField::TextMFN5( EMSTIME timeLast )
{
	static TCHAR szText[ c_iMinTime2StringLen ];

	_TextTime1( timeLast, szText, c_iMinTime1StringLen );

	return szText;
}


EMS_RESULT
CEMSSitMsgField::GetMFN6( LPCTSTR lpcszField, int *lpiNumBursts )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpiNumBursts );
}

EMS_RESULT
CEMSSitMsgField::GetMFN7( LPCTSTR lpcszField, int *lpiNumMsgs )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnn");

	return _GetIntegerField( lpcszField, c_szSyntax, lpiNumMsgs );
}

EMS_RESULT 
CEMSSitMsgField::GetMFN8( LPCTSTR lpcszField, double *lpdFreq )
{
	const TCHAR c_szSyntax[ ] = TEXT("/nnnnnnnnn.nn");

	return _GetDecimalField( lpcszField, c_szSyntax, lpdFreq );
}

EMS_RESULT 
CEMSSitMsgField::GetMFN9( LPCTSTR lpcszField, double *lpdQF )
{
   const TCHAR c_szSyntax[ ] = TEXT("/n");

   return _GetDecimalField( lpcszField, c_szSyntax, lpdQF );
}

EMS_RESULT
CEMSSitMsgField::GetMFN22( LPCTSTR lpcszField, __int64* lpi64BcnId )
{
	EMS_RESULT hr = EMS_OK;

	if( lpcszField && lpi64BcnId )
	{
		const TCHAR c_szSyntax[ ] = TEXT("/hhhhhhhhhhhhhhh"); // 15 hex characters

		hr = _CheckSyntax( lpcszField , c_szSyntax );

		if( EMS_OK == hr )
		{
			TCHAR*   pszHexBcnId = const_cast<TCHAR*>(&(lpcszField[1]));
			sscanf( pszHexBcnId, "%I64x", lpi64BcnId );
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	
	return hr;
}


void
CEMSSitMsgField::_TextTime( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen )
{
	memset( pszText, 0, iMaxLen * sizeof(TCHAR) );

	// minimum of 12 character ("nn nnn nnnn")
	if( pszText && (iMaxLen >= c_iMinTimeStringLen) )
	{
		if ( cTime.intTime )
		{
			EMSTIMEFIELDS timeFields;
			CEMSTime timeTemp( cTime );

			timeTemp.GetTime( &timeFields );

			_stprintf( pszText, TEXT("%02d %03d %02d%02d"),
					timeFields.nYear - (timeFields.nYear/100)*100,
					timeFields.nJulianDay,
					timeFields.nHour,
					timeFields.nMinute );
		}
		else
		{
			lstrcpy( pszText, TEXT("00 000 0000") );
		}
	}
}

void
CEMSSitMsgField::_TextTime1( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen )
{
	memset( pszText, 0, iMaxLen * sizeof(TCHAR) );

	// minimum of 18 character ("nn nnn nnnn nn.nn")
	if( pszText && (iMaxLen >= c_iMinTime1StringLen) )
	{
		if( cTime.intTime )
		{
			EMSTIMEFIELDS timeFields;
			CEMSTime timeTemp( cTime );

			timeTemp.GetTime( &timeFields );

			double	dSeconds = timeFields.nSecond + (double )timeFields.lNanosecond/(double )c_iNanoSecsPerSec;
			// Did rounding push this over the max value we can display (59.99)?
			// Adjust this ... otherwise it will display as 60.000
			if ( dSeconds >= 59.99 )
			{
				dSeconds = 59.99;
			}

			_stprintf( pszText,"%02d %03d %02d%02d %05.2f",
					timeFields.nYear - (timeFields.nYear/100)*100,
					timeFields.nJulianDay,
					timeFields.nHour,
					timeFields.nMinute,
					dSeconds );
		}
		else
		{
			lstrcpy( pszText, TEXT("00 000 0000 00.00") );
		}
	}
}

void
CEMSSitMsgField::_TextTime2( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen )
{
	memset( pszText, 0, iMaxLen * sizeof(TCHAR) );

	// minimum of 19 character ("nn nnn nnnn nn.nnn")
	if( pszText && (iMaxLen >= c_iMinTime2StringLen) )
	{
		if( cTime.intTime )
		{
			EMSTIMEFIELDS timeFields;
			CEMSTime timeTemp( cTime );

			timeTemp.GetTime( &timeFields );

			double	dSeconds = timeFields.nSecond + (double )timeFields.lNanosecond/(double )c_iNanoSecsPerSec;
			// Did rounding push this over the max value we can display (59.999)?
			// Adjust this ... otherwise it will display as 60.000
			if ( dSeconds >= 59.999 )
			{
				dSeconds = 59.999;
			}

			_stprintf( pszText,"%02d %03d %02d%02d %06.3f",
					timeFields.nYear - (timeFields.nYear/100)*100,
					timeFields.nJulianDay,
					timeFields.nHour,
					timeFields.nMinute,
					dSeconds );
		}
		else
		{
			lstrcpy( pszText, TEXT("00 000 0000 00.000") );
		}
	}
}

void
CEMSSitMsgField::_TextTime3( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen )
{
	memset( pszText, 0, iMaxLen * sizeof(TCHAR) );

	// minimum of 22 character ("nn nnn nnnn nn.nnnnnn")
	if( pszText && (iMaxLen >= c_iMinTime3StringLen) )
	{
		if( cTime.intTime )
		{
			EMSTIMEFIELDS timeFields;
			CEMSTime timeTemp( cTime );

			timeTemp.GetTime( &timeFields );

			double	dSeconds = timeFields.nSecond + (double )timeFields.lNanosecond/(double )c_iNanoSecsPerSec;
			// Did rounding push this over the max value we can display (59.999999)?
			// Adjust this ... otherwise it will display as 60.000000
			if ( dSeconds >= 59.999999 )
			{
				dSeconds = 59.999999;
			}

			_stprintf( pszText,"%02d %03d %02d%02d %09.6f",
					timeFields.nYear - (timeFields.nYear/100)*100,
					timeFields.nJulianDay,
					timeFields.nHour,
					timeFields.nMinute,
					dSeconds );
		}
		else
		{
			lstrcpy( pszText, TEXT("00 000 0000 00.000000") );
		}
	}
}

void
CEMSSitMsgField::_TextTime4( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen )
{
	memset( pszText, 0, iMaxLen * sizeof(TCHAR) );

	// minimum of 16 character ("nn nnn nn nn nn")
	if( pszText && (iMaxLen >= c_iMinTime4StringLen) )
	{
		if( cTime.intTime )
		{
			EMSTIMEFIELDS timeFields;
			CEMSTime timeTemp( cTime );

			timeTemp.GetTime( &timeFields );

			_stprintf( pszText,"%02d %03d %02d %02d %02d",
					timeFields.nYear - (timeFields.nYear/100)*100,
					timeFields.nJulianDay,
					timeFields.nHour,
					timeFields.nMinute,
					timeFields.nSecond );
		}
		else
		{
			lstrcpy( pszText, TEXT("00 000 00 00 00") );
		}
	}
}

EMS_RESULT
CEMSSitMsgField::GetMF82( LPCTSTR lpcszField, BYTE* pacBeaconMsg )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpcszField && pacBeaconMsg )
   {
      const TCHAR c_szSyntax[ ] = TEXT("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"); // 36 hex characters

	   hr = _CheckSyntax( lpcszField , c_szSyntax );

      if ( EMS_OK == hr )
      {
         BYTE     byteTemp;
         TCHAR*   pszBeaconMsg = const_cast<TCHAR*>(&(lpcszField[0]));

         for ( int jj = 0, kk = 0; (jj < 36 ); jj++ )
         {
            if ( isdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = pszBeaconMsg[jj] - L'0';
            }
            else if ( isxdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = toupper( pszBeaconMsg[jj] ) - L'A' + 0x0A;
            }
            if ( jj % 2 )
            {
               pacBeaconMsg[kk++] |= byteTemp;
            }
            else
            {
               byteTemp <<= 4;
               pacBeaconMsg[kk] = byteTemp;
            }
         }
      }
   }
   else
   {
   	hr = EMS_BAD_PARAM;
   }
   return hr;
}

LPCTSTR CEMSSitMsgField::TextMF82( const BYTE* cabyBeaconMsg )
{
	assert( cabyBeaconMsg );

#if defined(UNICODE) || defined(_UNICODE)
	// This code assumes that it will not need to support UNICODE
	assert(false);
#endif

	// Allow for too much space
	static char szText[ 37 ];
	memset( szText, 0, 37 );

	for ( int j = 0; j < 18; j++ )
	{
		sprintf( &szText[j*2], "%02X", cabyBeaconMsg[j] );
	}

	return szText;
}
EMS_RESULT
CEMSSitMsgField::GetMF99( LPCTSTR lpcszField, BYTE* pacBeaconMsg )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpcszField && pacBeaconMsg )
   {
      const TCHAR c_szSyntax[ ] = TEXT("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"); // 51 hex characters

	   hr = _CheckSyntax( lpcszField , c_szSyntax );

      if ( EMS_OK == hr )
      {
         BYTE     byteTemp;
         TCHAR*   pszBeaconMsg = const_cast<TCHAR*>(&(lpcszField[0]));

         for ( int jj = 0, kk = 0; (jj < 51 ); jj++ )
         {
            if ( isdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = pszBeaconMsg[jj] - L'0';
            }
            else if ( isxdigit( pszBeaconMsg[jj] ) )
            {
               byteTemp = toupper( pszBeaconMsg[jj] ) - L'A' + 0x0A;
            }
            if ( jj % 2 )
            {
               pacBeaconMsg[kk++] |= byteTemp;
            }
            else
            {
               byteTemp <<= 4;
               pacBeaconMsg[kk] = byteTemp;
            }
         }
      }
   }
   else
   {
   	hr = EMS_BAD_PARAM;
   }
   return hr;
}

LPCTSTR CEMSSitMsgField::TextMF99( const BYTE* cabyBeaconMsg )
{
	assert( cabyBeaconMsg );

#if defined(UNICODE) || defined(_UNICODE)
	// This code assumes that it will not need to support UNICODE
	assert(false);
#endif

	// Allow for too much space
	static char szText[ 52 ];
	memset( szText, 0, 52 );
	int j;
	for ( j = 0; j < 25; j++ )
	{
		sprintf( &szText[j*2], "%02X", cabyBeaconMsg[j] );
	}
	sprintf( &szText[j*2], "%1X", cabyBeaconMsg[j] & 0xf );
	return szText;
}

LPCTSTR CEMSSitMsgField::TextMFA01( EMSTIME time )
{
	static TCHAR szText[ c_iMinTime1StringLen ];

	_TextTime4( time, szText, c_iMinTime1StringLen );

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMFE07( const BYTE* cabyBeaconMsg )
{
	assert( cabyBeaconMsg );

#if defined(UNICODE) || defined(_UNICODE)
	// This code assumes that it will not need to support UNICODE
	assert(false);
#endif

	// Allow for too much space
	static char szText[ 40 ];
	memset( szText, 0, 40 );

	// Process all 18 bytes, including frame synch for a 36 Hex message.
	for ( int j = 0; j < 18; j++ )
	{
		sprintf( &szText[j*2], "%02X", cabyBeaconMsg[j] );
	}

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF75A( double dX, double dY, double dZ )
{
	static TCHAR szText[ 48 ];

	_stprintf( szText, TEXT("%+011.4f %+011.4f %+011.4f"), dX, dY, dZ );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF75A( LPCTSTR lpcszField, double& rdX, double& rdY, double& rdZ )
{
	EMS_RESULT hr = EMS_OK;

	TCHAR* szCopy = NULL;

	try
	{
		int iLen = strlen(lpcszField);

		szCopy = new TCHAR[iLen + 1 ];
		memset( szCopy, 0, (iLen+1)*sizeof(TCHAR));

		_tcscpy( szCopy, lpcszField );

		int iToks = 0;
		TCHAR* szTok = _tcstok( szCopy, TEXT(" ") );
		const TCHAR c_szSyntax[ ] = TEXT("snnnnn.nnnn");

		while( szTok && (iToks < 3) )
		{
			switch( iToks )
			{
				case 0:
					_GetDecimalField( szTok, c_szSyntax, &rdX );
					break;
				case 1:
					_GetDecimalField( szTok, c_szSyntax, &rdY );
					break;
				case 2:
					_GetDecimalField( szTok, c_szSyntax, &rdZ );
					break;
			}

			szTok = _tcstok( NULL, TEXT(" ") );
			iToks++;
		}
		
	}
	catch( ... )
	{
		hr = EMS_SIT_SYNTAX_ERROR;
	}


	return hr;
}


LPCTSTR CEMSSitMsgField::TextMF76A( double dX, double dY, double dZ )
{
	static TCHAR szText[ 48 ];

	_stprintf( szText, TEXT("%+011.6f %+011.6f %+011.6f"), dX, dY, dZ );

	return szText;
}

EMS_RESULT CEMSSitMsgField::GetMF76A( LPCTSTR lpcszField, double& rdX, double& rdY, double& rdZ )
{
	EMS_RESULT hr = EMS_OK;

	TCHAR* szCopy = NULL;

	try
	{
		int iLen = strlen(lpcszField);

		szCopy = new TCHAR[iLen + 1 ];
		memset( szCopy, 0, (iLen+1)*sizeof(TCHAR));

		_tcscpy( szCopy, lpcszField );

		int iToks = 0;
		TCHAR* szTok = _tcstok( szCopy, TEXT(" ") );
		const TCHAR c_szSyntax[ ] = TEXT("snnn.nnnnnn");

		while( szTok && (iToks < 3) )
		{
			switch( iToks )
			{
				case 0:
					_GetDecimalField( szTok, c_szSyntax, &rdX );
					break;
				case 1:
					_GetDecimalField( szTok, c_szSyntax, &rdY );
					break;
				case 2:
					_GetDecimalField( szTok, c_szSyntax, &rdZ );
					break;
			}

			szTok = _tcstok( NULL, TEXT(" ") );
			iToks++;
		}
		
	}
	catch( ... )
	{
		hr = EMS_SIT_SYNTAX_ERROR;
	}


	return hr;
}

LPCTSTR CEMSSitMsgField::TextMF77( const double cdAltitude )
{
	static TCHAR szText[ 32 ];
	double dAltitude = cdAltitude;

	if ( dAltitude > 99999.999 )
	{
		dAltitude = 99999.999;
	}
	else if ( dAltitude < 0 )
	{
		dAltitude = 0;
	}

	_stprintf( szText, TEXT("%09.3lf"), dAltitude );

	return szText;
}

LPCTSTR CEMSSitMsgField::TextMF79( const double cdMeanCN )
{
	static TCHAR szText[ 32 ];
	double dMeanCN = cdMeanCN;

	if ( dMeanCN > 99.99 )
	{
		dMeanCN = 99.99;
	}
	else if ( dMeanCN < 0 )
	{
		dMeanCN = 0;
	}

	_stprintf( szText, TEXT("%05.2lf"), dMeanCN );

	return szText;
}

