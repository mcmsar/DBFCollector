/********************************************************************
*	Module:			emsit960.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit960
*						Historical SIT used by Trenton Geo500 for GeoSarr data
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
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

	0.0	2002/10/31	rvw	start

********************************************************************/

#include <stdio.h>
#include <tchar.h>

#include "emscom.h"
#include "emstypes.h"
#include "emsit960.h"
#include "sitfield.h"

const TCHAR c_szSit960HdrFmt[ ] = TEXT("/%03d/%04d");
const TCHAR c_szSit960AlertHdrFmt[ ] = TEXT("/%04d/%03d/%03d");
const TCHAR c_szSit960SolnHdr1Fmt[] = TEXT("/%s");
const TCHAR c_szSit960SolnHdr2Fmt[] = TEXT("/%s %05.1f %05.1f %05.1f");
const TCHAR c_szSit960SolnHdr3Fmt[] = 
			TEXT("/%010.3f %+08.3f %04.1f %04.2f %c %02d %1d %1d %s %s %s %02d");

CEMSSit960::CEMSSit960()
{
	SetSitNumber(960);
	SetMaxAlertCount( EMS_MAX_SIT960_ALERTS );
}

CEMSSit960::~CEMSSit960()
{
	Reset();
}

void CEMSSit960::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount( 0 );
	SetSitNumber(960);
	SetMaxAlertCount( EMS_MAX_SIT960_ALERTS );
}

EMS_RESULT CEMSSit960::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR szTCA[40];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				for ( int j = 0; j < 15; j++ )
				{
					_stprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				_stprintf( szBuffer, c_szSit960SolnHdr1Fmt );

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					tmpTime.SetTime( lpSoln->sideA.timeTCA );

					tmpTime.GetTime( &timeFields );

					_stprintf( szTCA,"%02d%02d%02d %02d%02d%02d.%06d",
							timeFields.nYear % 100,
							timeFields.nMonth,
							timeFields.nDay,
							timeFields.nHour,
							timeFields.nMinute,
							timeFields.nSecond,
							(int)timeFields.lNanosecond/10000000 );

					_stprintf( szBuffer, c_szSit960SolnHdr2Fmt, szTCA,
 						0.0	// FIX THIS!!!
					 	);

					hr = WriteLine( lpStream, szBuffer );

					if ( hr == EMS_OK )
					{
						_stprintf( szBuffer, c_szSit960SolnHdr3Fmt, szBeaconMsg); //MF23

						hr = WriteLine( lpStream, szBuffer );
					}
				}
			}
			else
				hr = EMS_UNKNOWN_ERROR;
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit960::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
				
		_stprintf( szBuffer, c_szSit960HdrFmt, 
						GetSitNumber(), GetSitDestination() );

		hr = WriteLine( lpStream, szBuffer );

		_stprintf( szBuffer, c_szSit960AlertHdrFmt, GetLutID(),
						GetSatelliteID(),	GetAlertCount() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit960::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		hr = _ParseAlertHeader( lpTokenizer );

		if ( hr == EMS_OK )
		{
			EMSSITLOCALERTSOLUTION alertData, *lpAlertData=0;
			int nCount = _AllocSolutions( GetAlertCount( ) );

			for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
			{
				memset( &alertData, 0, sizeof( alertData ) );

				alertData.hdr.nPrimaryLutID = GetLutID();

				alertData.hdr.msgType = EMSSMT_Normal;

				alertData.hdr.nFreqBand = 8; // ie SARR or SARR DETECT

				hr = _ParseAlertLine( lpTokenizer, &alertData );

				if ( ( hr == EMS_OK ) && ( i < nCount ) )
				{
					lpAlertData = _GetSolutionPtr( i );
				
					if ( lpAlertData )
						*lpAlertData = alertData;
				}
			}

			if ( hr == EMS_OK )
				hr = _ParseAlertTrailer( lpTokenizer );
		}
	}

	return hr;
}

EMS_RESULT CEMSSit960::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5

		if ( nFldCount == 3 )
		{
			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[2].szText ) )
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

EMS_RESULT CEMSSit960::_ParseAlertHeader( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF2/MF6/MF10A

		if ( nFldCount == 4 )
		{
			int nSatNumber=0, nAlertCount=0, nLutID=0;

			hr = msgField.GetMF2( sitField[0].szText, &nLutID );

			if ( hr == EMS_OK )
			{
				SetLutID( nLutID );

				hr = msgField.GetMF6( sitField[1].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatelliteID( nSatNumber );

				hr = msgField.GetMF10A( sitField[2].szText, &nAlertCount );
			}

			if ( hr == EMS_OK )
			{
				SetAlertCount( nAlertCount );

				if ( !msgField.IsEOL( sitField[3].szText ) )
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

EMS_RESULT CEMSSit960::_ParseAlertLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{	
		TCHAR szBuffer[ 256 ], *lpszToken=0;
		int nCount = 0, nToken = 0;

		hr = ReadSitLine( lpTokenizer, szBuffer, sizeof(szBuffer)/sizeof(szBuffer[0]), &nCount );

		if ( hr == EMS_OK )
		{
			CEMSTime timeTemp;
			double dFreqBias = 0.0, dFraction = 0.0, dCNR = 0.0;
			EMSTIMEFIELDS timeFields;

			memset( &timeFields, 0, sizeof( timeFields ) );

			try
			{
				lpszToken = _tcstok( szBuffer, TEXT(" ") );
			
				while ( lpszToken )
				{
					switch ( nToken++ )
					{
						case 0:	// BeaconMsg
							hr = _SetBeaconMsgAndID( lpszToken, lpAlertData );
							break;

						case 1: 	// year/month/day
							sscanf( lpszToken, TEXT("%02d%02d%02d"),
									&timeFields.nYear, &timeFields.nMonth,
									&timeFields.nDay );

                     timeFields.nYear += ( timeFields.nYear >= 80 ) ? 1900 : 2000;         // year 2080 bug

							break;
					
						case 2: 	// hours/minutes/seconds
							
							sscanf( lpszToken, TEXT("%02d%02d%02d%lf"),
									&timeFields.nHour, &timeFields.nMinute,
									&timeFields.nSecond, &dFraction );

							timeFields.lNanosecond = (long)( dFraction * 1000000000);

							break;

						case 3:	
							dCNR = atof( lpszToken );
							break;

						case 4:
							dFreqBias = atof( lpszToken );
							break;
					}
					lpszToken = _tcstok( 0, TEXT(" ") );
				}

				timeTemp.SetTime( &timeFields );

				lpAlertData->hdr.timeMsg = timeTemp;

				lpAlertData->sideA.dBias = dFreqBias;

				lpAlertData->hdr.dPower = dCNR;

				lpAlertData->hdr.dRecvFreq = 406e6 + dFreqBias;
			}

			catch ( ... )
			{
				hr = EMS_SIT_SYNTAX_ERROR;
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit960::_ParseAlertTrailer( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[ 256 ];
	int nCount = 0;

	hr = ReadSitLine( lpTokenizer, szBuffer, sizeof(szBuffer)/sizeof(szBuffer[0]), &nCount );

	if ( hr == EMS_OK )
	{
		if ( lstrcmp( szBuffer, TEXT("QQQQ") ) != 0 ) 
			hr = EMS_SIT_SYNTAX_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSit960::_SetBeaconMsgAndID( LPCTSTR lpcszBeaconMsg, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszBeaconMsg && *lpcszBeaconMsg && ( lstrlen( lpcszBeaconMsg ) == 30 ) )
	{
		INT64 i64BeaconID = 0;
		TCHAR szTemp[32];
		int i = 0;

		lstrcpy( szTemp, TEXT("0x") );

		for ( i = 0; i < 30; i += 2 )
		{
			lstrcpyn( &szTemp[2], &lpcszBeaconMsg[i], 3 );

			lpAlertData->hdr.cBeaconMsg[ 3+(i/2) ] = (BYTE)strtol( szTemp, 0, 16 );
		}

		//Extract beacon id from beacon msg 

		i64BeaconID = ( 0x7F & lpAlertData->hdr.cBeaconMsg[3] );

		for ( i = 1; i < 7; i++ )
		{
			i64BeaconID = i64BeaconID << 8;
			i64BeaconID |= lpAlertData->hdr.cBeaconMsg[3+i];
		}

		i64BeaconID = i64BeaconID << 5;

		i64BeaconID |= ( 0x1F & ( lpAlertData->hdr.cBeaconMsg[10] >> 3 ) );

		lpAlertData->hdr.i64BeaconID = i64BeaconID;
	}
	else
		hr = EMS_SIT_SYNTAX_ERROR;

	return hr;
}
