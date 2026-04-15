/********************************************************************
*	Module:			emsit161.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit161
*						Historical SIT used by orig Geo600 for GeoSarr data
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
#include "emsit161.h"
#include "sitfield.h"

//			BeaconMsg
// 	1) /h...(36)..h					
//			timeMsg				 Bitrate CNR	SNR
//	2) /yymmdd hhmmss.ssssss nnnn.n nnnn.n nnnn.n 
//			Freq      FreqOff FreqBW Mod Tp  PF1  Grp   Active
//													 FS  PF2	 Cnts		 RepRate
//	3) /nnnnnn.nnn snnnn.nnn nn.n n.nn a nn n n a.. a.. a.. nn
//
//

const TCHAR c_cBase10to36[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const TCHAR c_szSit161HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit161SolnHdr1Fmt[] = TEXT("/%s");
const TCHAR c_szSit161SolnHdr2Fmt[] = TEXT("/%s %05.1f %05.1f %05.1f");
const TCHAR c_szSit161SolnHdr3Fmt[] = 
			TEXT("/%010.3f %+08.3f %04.1f %04.2f %c %02d %1d %1d %s %s %s %s");

CEMSSit161::CEMSSit161()
{
	SetSitNumber(161);
	SetMaxAlertCount( EMS_MAX_SIT161_ALERTS );
}

CEMSSit161::~CEMSSit161()
{
	Reset();
}

void CEMSSit161::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount( 0 );
	SetSitNumber(161);
	SetMaxAlertCount( EMS_MAX_SIT161_ALERTS );
}

EMS_RESULT CEMSSit161::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36+1];
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR szTime[40];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				for ( int j = 0; j < 18; j++ )
				{
					BYTE cByte = lpSoln->hdr.cBeaconMsg[j];

					switch ( j )
					{
						case 0: if ( 0 == cByte ) cByte = 0xFF; break;
						case 1: if ( 0 == cByte ) cByte = 0xFE; break;
						case 2: if ( 0 == cByte ) cByte = 0x2F; break;
						default:	break;
					}

					sprintf( &szBeaconMsg[j*2], "%02X", cByte );
				}

				sprintf( szBuffer, c_szSit161SolnHdr1Fmt, szBeaconMsg );

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					double dSeconds = 0.0;

					tmpTime.SetTime( lpSoln->hdr.timeMsg );

					tmpTime.GetTime( &timeFields );

					dSeconds = (double)timeFields.nSecond;

					dSeconds += (double)timeFields.lNanosecond / 1000000000.0;

					sprintf( szTime,"%02d%02d%02d %02d%02d%09.6lf",
							timeFields.nYear % 100,
							timeFields.nMonth,
							timeFields.nDay,
							timeFields.nHour,
							timeFields.nMinute,
							dSeconds );

					sprintf( szBuffer, c_szSit161SolnHdr2Fmt, szTime,
				 						0.0, 		// FIX THIS !!!!!!
										lpSoln->hdr.dPower, lpSoln->hdr.dPower );

					hr = WriteLine( lpStream, szBuffer );

					if ( hr == EMS_OK )
					{
						TCHAR szGroupIndex[32], szIntegrations[32], szGroupCount[32];

						lstrcpy( szGroupIndex,	_Convert10to36( 0 ,5 ) );

						lstrcpy( szIntegrations, _Convert10to36( lpSoln->hdr.nDupCopyCount, 3 ) );

						lstrcpy( szGroupCount, _Convert10to36( 1 ,2 ) );

						sprintf( szBuffer, c_szSit161SolnHdr3Fmt, 
							lpSoln->hdr.dRecvFreq - 406e6 - lpSoln->sideA.dBias, 
							lpSoln->hdr.dLutFreqOffset, 
							0.0, // FreqBW
							1.0, // Mod
							( lpSoln->hdr.msgType == EMSSMT_Test ) ? 'T' : 'M',
							lpSoln->hdr.nBitErrorsPreamble,
							lpSoln->hdr.nBitErrorsField1,
							lpSoln->hdr.nBitErrorsField2,
							szGroupIndex, szIntegrations, szGroupCount,
							"-1" );

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

EMS_RESULT CEMSSit161::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
				
		sprintf( szBuffer, c_szSit161HdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSatelliteID(),
						GetAlertCount() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit161::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		EMSSITLOCALERTSOLUTION alertData, *lpAlertData=0;
		int nCount = _AllocSolutions( GetAlertCount( ) );

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			memset( &alertData, 0, sizeof( alertData ) );

			alertData.hdr.nPrimaryLutID = GetReportingMCC();

			hr = _ParseAlertLine1( lpTokenizer, &alertData );

			if ( hr == EMS_OK )
				hr = _ParseAlertLine2( lpTokenizer, &alertData );

			if ( hr == EMS_OK )
				hr = _ParseAlertLine3( lpTokenizer, &alertData );

			if ( ( hr == EMS_OK ) && ( i < nCount ) )
			{
				lpAlertData = _GetSolutionPtr( i );
				
				if ( lpAlertData )
					*lpAlertData = alertData;
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSit161::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF6/MF10

		if ( nFldCount == 5 )
		{
			int nSatNumber=0, nAlertCount=0, nNumber = 0;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF6( sitField[2].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatelliteID( nSatNumber );

				hr = msgField.GetMF10( sitField[3].szText, &nAlertCount );
			}

			if ( hr == EMS_OK )
			{
				SetAlertCount( nAlertCount );

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

EMS_RESULT CEMSSit161::_ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF EOL

			if ( nFldCount == 2 )
			{
				if ( sitField[0].nLength > 32 )
				{
					INT64 i64BeaconID = 0;
					TCHAR szTemp[32];
					int i = 0;

					lstrcpy( szTemp, TEXT("0x") );

					for ( i = 0; i < 36; i += 2 )
					{
						lstrcpyn( &szTemp[2], &sitField[0].szText[i+1], 3 );

						lpAlertData->hdr.cBeaconMsg[ i/2 ] = (BYTE)strtol( szTemp, 0, 16 );
					}

					//Extract beacon id from beacon msg [18] (26-85 bits from 144bits)
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
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit161::_ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;
		double dBitRate = 0.0, dCNR = 0.0, dSNR = 0.0;
		EMSTIMEFIELDS timeFields;
		CEMSTime timeTemp;

		memset( &timeFields, 0, sizeof( timeFields ) );

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			TCHAR *lpszToken = 0;
			int nToken = 0;
			// should find /MF EOL

			if ( nFldCount == 2 )
			{
				TCHAR szTemp[32];

				nToken = 0;

				lpszToken = _tcstok( sitField[0].szText, TEXT(" ") );

				while ( lpszToken )
				{
					switch ( nToken++ )
					{
						case 0: 	//yymmdd
							lstrcpyn( szTemp, &lpszToken[1], 3 );

							timeFields.nYear = atoi( szTemp );

							if ( timeFields.nYear < 80 )
								timeFields.nYear += 2000;
							else
								timeFields.nYear += 1900;
 
							lstrcpyn( szTemp, &lpszToken[3], 3 );

							timeFields.nMonth = atoi( szTemp );

							lstrcpyn( szTemp, &lpszToken[5], 3 );

							timeFields.nDay = atoi( szTemp );

							break;

						case 1: 	//hhmmss.ssssss

							lstrcpyn( szTemp, &lpszToken[0], 3 );

							timeFields.nHour = atoi( szTemp );

							lstrcpyn( szTemp, &lpszToken[2], 3 );

							timeFields.nMinute = atoi( szTemp );

							lstrcpyn( szTemp, &lpszToken[4], 3 );

							timeFields.nSecond = atoi( szTemp );

							lstrcpyn( szTemp, &lpszToken[7], 7 );

							timeFields.lNanosecond = atol( szTemp );

							timeFields.lNanosecond *= 1000L; // from microseconds

							break;

						case 2: 	// Bitrate 
							dBitRate = atof( lpszToken );
							break;

						case 3:	// CNR
							dCNR = atof( lpszToken );
							break;

						case 4:	// SNR
							dSNR = atof( lpszToken );
							break;
					}

					lpszToken = _tcstok( 0, TEXT(" ") );
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;

		lpAlertData->hdr.dPower = dCNR;

		timeTemp.SetTime( &timeFields );

		lpAlertData->hdr.timeMsg = timeTemp;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit161::_ParseAlertLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0, nRepRate=0, nPreamble = 0, nPF1 = 0, nPF2 = 0;
		int nMsgCount = 0;
		double dFreqBias=0.0, dFreqOffset=0.0, dFreqBandwidth=0.0;
		double dModIndex = 0.0;
		char cType = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			TCHAR *lpszToken = 0;
			int nToken = 0;

			// should find /MF EOL

			if ( nFldCount == 2 )
			{
				nToken = 0;

				lpszToken = _tcstok( sitField[0].szText, TEXT(" ") );

				while ( lpszToken )
				{
					switch ( nToken++ )
					{
						case 0: 	// Freq
							dFreqBias = atof( &lpszToken[1] );
							break;

						case 1: 	// FreqOffset
							dFreqOffset = atof( lpszToken );
							break;

						case 2: 	// FreqBandwidth
							dFreqBandwidth = atof( lpszToken );
							break;

						case 3:	// ModIndex
							dModIndex = atof( lpszToken );
							break;

						case 4:	// Type
							cType = *lpszToken;
							break;

						case 5: // 
							nPreamble = atoi( lpszToken );
							break;

						case 6:	// PF1
							nPF1 = atoi( lpszToken );
							break;

						case 7:	// PF2
							nPF2 = atoi( lpszToken );
							break;

						case 8:	// ignore
							break;

						case 9:
							nMsgCount = atoi( lpszToken ); // ????
							break;

						case 10: // ignore
							break;

						case 11:
							nRepRate = atoi( lpszToken );
							break;
					}

					lpszToken = _tcstok( 0, TEXT(" ") );
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}

		switch ( cType )
		{
			case 'T':
				lpAlertData->hdr.msgType = EMSSMT_Test;
				break;

			case 'M':
			default:
				lpAlertData->hdr.msgType = EMSSMT_Normal;
				break;
		}

		lpAlertData->hdr.nBitErrorsPreamble = nPreamble;

		lpAlertData->hdr.nBitErrorsField1 = nPF1;

		lpAlertData->hdr.nBitErrorsField2 = nPF2;

		lpAlertData->hdr.dLutFreqOffset = dFreqOffset;

		lpAlertData->sideA.dBias = dFreqBias;

		lpAlertData->hdr.dRecvFreq = 406e6 + dFreqBias;

		lpAlertData->hdr.nFreqBand = 8; // ie SARR or SARR DETECT

		lpAlertData->hdr.nDupCopyCount = nMsgCount;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

LPCSTR CEMSSit161::_Convert10to36(unsigned long ulv10, int nDigits )
{
	static TCHAR s_szv36[6];
	int nOffset = 0;

	if ( nDigits <= 5 ) 
		nOffset = 5 - nDigits;

	ulv10 %= 60466176;

	s_szv36[5] = 0;

	for( int i = 4; i >= 0; --i )
	{
		s_szv36[ i ] = c_cBase10to36[ ulv10 % 36 ];

		ulv10 /= 36;
	}
	return (LPCSTR)&s_szv36[ nOffset ];
}
