#pragma message( "!!!!!!!!!!!!!!!!_AllocSolutions() prevents large SIT122 messages (ie. with many alerts) from being parsed properly!!!!!!!!!!")

/********************************************************************
*	Module:			emsit122.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit122
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include <stdio.h>
#include <array.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit122.h"
#include "sitfield.h"
#include "emslinfo.h"

const TCHAR c_szSit122HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit122SolnHdr1Fmt[] = TEXT("/%04d/%s/%s/%02d");
const TCHAR c_szSit122SolnHdr2Fmt[] = TEXT("/%s");

const TCHAR c_szSit122AHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%03d");
const TCHAR c_szSit122ASolnHdr1Fmt[] = TEXT("/%04d/%13.3lf %+09.3lf/%s %+09.6lf/%01d");
const TCHAR c_szSit122ASolnHdr2Fmt[] = TEXT("/%s/%c/%01d %01d %01d/%+07.2lf");
const TCHAR c_szSit122ASolnHdr3Fmt[] = TEXT("/%s");

const TCHAR c_szSit122BHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%03d");
const TCHAR c_szSit122BSolnHdr1Fmt[] = TEXT("/%04d/%s/%s/%04d");
const TCHAR c_szSit122BSolnHdr2Fmt[] = TEXT("/%c/%01d %01d %01d/%+07.2lf");
const TCHAR c_szSit122BSolnHdr3Fmt[] = TEXT("/%s");

const TCHAR c_szSit122CHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit122CSolnHdr1Fmt[] = TEXT("/%04d/%05d/%s/%s/%04d");
const TCHAR c_szSit122CSolnHdr2Fmt[] = TEXT("/%s/%c/%01d %01d %01d/%+07.2lf");
const TCHAR c_szSit122CSolnHdr3Fmt[] = TEXT("/%s");


const TCHAR c_szSit122ESolnHdr1Fmt[] = TEXT("/%04d/%13.3lf %+09.3lf/%s %+09.6lf");
const TCHAR c_szSit122ESolnHdr2Fmt[] = TEXT("/%c/%c/%01d %01d %01d/%+07.2lf");

CEMSSit122::CEMSSit122()
{
	SetSitNumber(122);
	SetMaxAlertCount( EMS_MAX_SIT122_ALERTS );
}

CEMSSit122::~CEMSSit122()
{
	Reset();
}

void CEMSSit122::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount( 0 );
	SetSitNumber(122);
	SetMaxAlertCount( EMS_MAX_SIT122_ALERTS );
}

EMS_RESULT CEMSSit122::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
			   // Number of Bursts Used
				int nNumPoints = lpSoln->sideA.nNumPoints;	//MF21

				if ( 0 == nNumPoints )	// if non used - report number of bursts
					nNumPoints = lpSoln->hdr.nNumPoints;

				if ( nNumPoints > 99 ) 
					nNumPoints = 99;

   			if ( nNumPoints < 1 )
   				nNumPoints = 1;

				for ( int j = 0; j < 15; j++ )
				{
					sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				sprintf( szBuffer, c_szSit122SolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11

						msgField.TextMF13( lpSoln->sideA.dBias,
								lpSoln->sideA.dBSdev,
								lpSoln->sideA.dDrift ),

						msgField.TextMF14( lpSoln->sideA.timeTCA ),

						nNumPoints // MF21
					 );

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSit122SolnHdr2Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
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

EMS_RESULT CEMSSit122::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
				
		sprintf( szBuffer, c_szSit122HdrFmt, 
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

EMS_RESULT CEMSSit122::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		EMSSITLOCALERTSOLUTION alertData, *lpAlertData=0;
		int nCount = _AllocSolutions( GetAlertCount( ) );

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			memset( &alertData, 0, sizeof( alertData ) );

			hr = _ParseAlertLine1( lpTokenizer, &alertData );

			if ( hr == EMS_OK )
				hr = _Parse406Message( lpTokenizer, &alertData );

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

EMS_RESULT CEMSSit122::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

EMS_RESULT CEMSSit122::_ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF11/MF13/MF14/MF21 EOL 

			if ( nFldCount == 5 )
			{
				CEMSSitMsgField msgField;
				EMSTIME timeTCA;
				int nNumber=0, nLutID = 0, nPoints=0;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0;

				hr = msgField.GetMF11( sitField[0].szText, &nLutID );

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nPrimaryLutID = nLutID;

					hr = msgField.GetMF13( sitField[0].szText, &dBias,
												&dBSDev, &dDrift );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->sideA.dBias = dBias;

					lpAlertData->sideA.dBSdev = dBSDev;

					lpAlertData->sideA.dDrift = dDrift;

					hr = msgField.GetMF14( sitField[ 2 ].szText, &timeTCA );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->sideA.timeTCA = timeTCA;

					hr = msgField.GetMF21( sitField[ 3 ].szText, &nPoints );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nNumPoints = nPoints;

					if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
				}
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

EMS_RESULT CEMSSit122::_Parse406Message( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
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
				if ( sitField[0].nLength > 30 )
				{
					int i = 0;
					INT64 i64BeaconID = 0;
					TCHAR szTemp[32];

					lstrcpy( szTemp, TEXT("0x") );

					for ( i = 0; i < 30; i += 2 )
					{
						lstrcpyn( &szTemp[2], &sitField[0].szText[i+1], 3 );

						lpAlertData->hdr.cBeaconMsg[ 3+ (i/2) ] = (BYTE)strtol( szTemp, 0, 16 );
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

CEMSSit122A::CEMSSit122A()
{
	SetSitCode( 0x122A );
	SetMaxAlertCount( EMS_MAX_SIT122A_ALERTS );
}

CEMSSit122A::~CEMSSit122A()
{
	Reset();
}

void CEMSSit122A::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 122 );
	SetSitCode(0x122A);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT122A_ALERTS );
}

EMS_RESULT CEMSSit122A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR szTime[40],szMF12[3];
	ULONG ulYear;
	char str;


	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				for ( int j = 0; j < 15; j++ )
				{
					sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				tmpTime.SetTime( lpSoln->hdr.timeMsg );
				tmpTime.GetTime( &timeFields );

				ulYear = timeFields.nYear - (timeFields.nYear/100)*100;
				sprintf(szTime,"%2.2d %3.3d %2.2d%2.2d %02d.%06d",
						ulYear,
						timeFields.nJulianDay,
						timeFields.nHour,
						timeFields.nMinute,
						timeFields.nSecond,
						timeFields.lNanosecond/1000);
		
				// ticket# 51915, make sure the freq. offset is not > 9999.999 or < -9999.999 (snnnn.nnn).
				double dLutFreqOffset = lpSoln->hdr.dLutFreqOffset; 

				if( dLutFreqOffset > 9999.999 ) 
					dLutFreqOffset = 9999.999;
				else if( dLutFreqOffset < -9999.999 ) 
					dLutFreqOffset = -9999.999;

				sprintf( szBuffer, c_szSit122ASolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						lpSoln->hdr.dRecvFreq, //MF647
						dLutFreqOffset,
						szTime,					//MF648
						lpSoln->hdr.dLutTimeOffset,
						( lpSoln->hdr.nDupCopyCount > 9 ) ? 9 :
								lpSoln->hdr.nDupCopyCount	//MF627
						);

				hr = WriteLine( lpStream, szBuffer );


				if ( hr == EMS_OK )
				{
					switch ( lpSoln->hdr.msgType )
					{
						default:
						case EMSSMT_Normal:			str = 'N';	break;
						case EMSSMT_Test:			str = 'T';	break;
						case EMSSMT_Combination:	str = 'C';	break;
						case EMSSMT_Invalid:			str = 'X';	break;
					}

					if (lpSoln->hdr.bLocalFlag)
					{
						sprintf(szMF12,"+%d",lpSoln->hdr.nFreqBand);
					}
					else
					{
						sprintf(szMF12,"-%d",lpSoln->hdr.nFreqBand);
					}

	
					sprintf( szBuffer, c_szSit122ASolnHdr2Fmt,
							szMF12,						//MF12
							str	,						//MF619
							lpSoln->hdr.nBitErrorsPreamble,	//MF626
							lpSoln->hdr.nBitErrorsField1,
							lpSoln->hdr.nBitErrorsField2,
							lpSoln->hdr.dPower		//MF628
							);

					hr = WriteLine( lpStream, szBuffer );
				}

				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSit122ASolnHdr3Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
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

EMS_RESULT CEMSSit122A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit122AHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCode(),
						GetSatelliteID(),
						GetAlertCount()
					);

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT CEMSSit122A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );

   if ( EMS_OK == hr )
   {
      if ( GetAlertCount() > 0 )
      {
         _AllocSolutions( GetAlertCount() );

         LPEMSSITLOCALERTSOLUTION lpLocateSolution = 0;

         for ( int ii = 0; (ii < GetAlertCount()) && (EMS_OK == hr); ii++ )
         {
            lpLocateSolution = _GetSolutionPtr( ii );

            if ( lpLocateSolution )
            {
   			   hr = _ParseAlertLine1( lpTokenizer, lpLocateSolution );

               if ( EMS_OK == hr )
               {
      			   hr = _ParseAlertLine2( lpTokenizer, lpLocateSolution );
               }

               if ( EMS_OK == hr )
               {
   				   hr = _Parse406Message( lpTokenizer, lpLocateSolution );
               }
            }
         }
      }
   }
   return hr;
}

EMS_RESULT CEMSSit122A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF4A/MF6/MF10 eol

		if ( nFldCount == 6 )
		{
			int nSatNumber=0, nAlertCount=0, nNumber = 0;
			EMSSITCODE sitCode;

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

				hr = msgField.GetMF6( sitField[3].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatelliteID( nSatNumber );

				hr = msgField.GetMF10A( sitField[4].szText, &nAlertCount );
			}

			if ( hr == EMS_OK )
			{
				SetAlertCount( nAlertCount );

				if ( !msgField.IsEOL( sitField[5].szText ) )
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

EMS_RESULT CEMSSit122A::_ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF11/MF647/MF648/MF627 eol

			if ( nFldCount == 5 )
			{
				CEMSSitMsgField msgField;
				EMSTIME timeMsg;
				int nNumber=0, nLutID = 0, nDuplicates=0 ;
				double dTimeOffset = 0.0;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0, dFreq=0.0, dFreqOffset=0.0;

				hr = msgField.GetMF11( sitField[0].szText, &nLutID );

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nPrimaryLutID = nLutID;

					hr = msgField.GetMF647( sitField[1].szText, &dFreq, &dFreqOffset );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.dRecvFreq = dFreq;

					lpAlertData->hdr.dLutFreqOffset = dFreqOffset;

					hr = msgField.GetMF648( sitField[ 2 ].szText, &timeMsg, &dTimeOffset );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.timeMsg = timeMsg;

					lpAlertData->hdr.dLutTimeOffset = dTimeOffset;

					hr = msgField.GetMF627( sitField[ 3 ].szText, &nDuplicates );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nDupCopyCount = nDuplicates;

					if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
				}
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

EMS_RESULT CEMSSit122A::_ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0, nType = '?', nPreamble=0, nPF1=0, nPF2=0 ;
		double dPower = 0.0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF12/MF619/MF626/MF628 eol

			if ( nFldCount == 5 )
			{
				CEMSSitMsgField msgField;
				int nNumber=0, nLutID = 0, nPoints=0, nFreqBand=0;
				BOOL bLocalFlag = FALSE;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0;

				hr = msgField.GetMF12( sitField[0].szText, &bLocalFlag, &nFreqBand );

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.bLocalFlag = bLocalFlag;

					lpAlertData->hdr.nFreqBand = nFreqBand;

					hr = msgField.GetMF619( sitField[1].szText, reinterpret_cast<int*>(&(lpAlertData->hdr.msgType)) );
				}
				if ( hr == EMS_OK )
				{
					hr = msgField.GetMF626( sitField[ 2 ].szText, &nPreamble, &nPF1, &nPF2 );
				}
				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nBitErrorsPreamble = nPreamble;

					lpAlertData->hdr.nBitErrorsField1 = nPF1;

					lpAlertData->hdr.nBitErrorsField2 = nPF2;

					hr = msgField.GetMF628( sitField[ 3 ].szText, &dPower );
				}

				if ( hr == EMS_OK )
				{
				 	lpAlertData->hdr.dPower	 = dPower;

					if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;
	}

	return hr;
}

CEMSSit122B::CEMSSit122B()
{
	SetSitCode(0x122B);
	SetMaxAlertCount( EMS_MAX_SIT122B_ALERTS );
}

CEMSSit122B::~CEMSSit122B()
{
	Reset();
}

void CEMSSit122B::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 122 );
	SetSitCode(0x122B);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT122B_ALERTS );
}

EMS_RESULT CEMSSit122B::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
	char str;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{

				for ( int j = 0; j < 15; j++ )
				{
					wsprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				sprintf( szBuffer, c_szSit122BSolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11

						msgField.TextMF13( lpSoln->sideA.dBias,
								lpSoln->sideA.dBSdev,
								lpSoln->sideA.dDrift ),

						msgField.TextMF14( lpSoln->sideA.timeTCA ),

						min( lpSoln->sideA.nNumPoints, 9999 ) //MF21A
						);

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					switch ( lpSoln->hdr.msgType )
					{
						default:
						case EMSSMT_Normal:			str = 'N';	break;
						case EMSSMT_Test:			str = 'T';	break;
						case EMSSMT_Combination:	str = 'C';	break;
						case EMSSMT_Invalid:			str = 'X';	break;
					}

					sprintf( szBuffer, c_szSit122BSolnHdr2Fmt,
							str,						//MF619
							lpSoln->hdr.nBitErrorsPreamble,	//MF626
							lpSoln->hdr.nBitErrorsField1,
							lpSoln->hdr.nBitErrorsField2,
							lpSoln->hdr.dPower		//MF628
							);

					hr = WriteLine( lpStream, szBuffer );
				}

				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSit122BSolnHdr3Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
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

EMS_RESULT CEMSSit122B::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		wsprintf( szBuffer, c_szSit122BHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCode(),
						GetSatelliteID(),
						GetAlertCount()
					);

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT
CEMSSit122B::_ParseAlertLine1(   CEMSSitTokenizer*          lpTokenizer,
                                 LPEMSSITLOCALERTSOLUTION   lpAlertData )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && lpAlertData )
   {
      EMSSITFIELD sitField[ 16 ];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF11/MF13/MF14/MF21A + eol

         if ( 5 == nFldCount )
         {
            hr = msgField.GetMF11( sitField[0].szText, &(lpAlertData->hdr.nPrimaryLutID) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF13( sitField[1].szText, &(lpAlertData->sideA.dBias),
                                       &(lpAlertData->sideA.dBSdev), &(lpAlertData->sideA.dDrift) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF14( sitField[2].szText, &(lpAlertData->sideA.timeTCA) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF21A( sitField[3].szText, &(lpAlertData->sideA.nNumPoints) );
            }
            if ( EMS_OK == hr )
            {
				   if ( !msgField.IsEOL( sitField[4].szText ) )
               {
					   hr = EMS_SIT_SYNTAX_EOL;
               }
            }
         }
         else
         {
	         hr = EMS_SIT_FIELD_COUNT_ERROR;
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
CEMSSit122B::_ParseAlertLine2(   CEMSSitTokenizer*          lpTokenizer, 
                                 LPEMSSITLOCALERTSOLUTION   lpAlertData )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && lpAlertData )
   {
      EMSSITFIELD sitField[ 16 ];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF619/MF626/MF628 + eol

         if ( 4 == nFldCount )
         {
            hr = msgField.GetMF619( sitField[0].szText, reinterpret_cast<int*>(&(lpAlertData->hdr.msgType)) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF626( sitField[1].szText, &(lpAlertData->hdr.nBitErrorsPreamble),
                                       &(lpAlertData->hdr.nBitErrorsField1), &(lpAlertData->hdr.nBitErrorsField2) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF628( sitField[2].szText, &(lpAlertData->hdr.dPower) );
            }
            if ( EMS_OK == hr )
            {
				   if ( !msgField.IsEOL( sitField[3].szText ) )
               {
					   hr = EMS_SIT_SYNTAX_EOL;
               }
            }
         }
         else
         {
	         hr = EMS_SIT_FIELD_COUNT_ERROR;
         }
      }
   }
   else
   {
	   hr = EMS_BAD_PARAM;
   }
   return hr;
}


CEMSSit122C::CEMSSit122C()
{
	SetSitCode(0x122C);
	SetMaxAlertCount( EMS_MAX_SIT122C_ALERTS );
}

CEMSSit122C::~CEMSSit122C()
{
	Reset();
}

void CEMSSit122C::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 122 );
	SetSitCode(0x122C);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT122C_ALERTS );
}

EMS_RESULT CEMSSit122C::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
	TCHAR szMF12[3];
	char str;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
                ULONG ulPassID = lpSoln->hdr.ulPass <= 99999 ? lpSoln->hdr.ulPass : 99999;  //MF07

                for ( int j = 0; j < 15; j++ )
				{
					sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				sprintf( szBuffer, c_szSit122CSolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						ulPassID,	//MF07

						msgField.TextMF13( lpSoln->sideA.dBias,
								lpSoln->sideA.dBSdev,
								lpSoln->sideA.dDrift ),

						msgField.TextMF14( lpSoln->sideA.timeTCA ),

						min( lpSoln->sideA.nNumPoints, 9999 ) //MF21A
						);

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					switch ( lpSoln->hdr.msgType )
					{
						default:
						case EMSSMT_Normal:			str = 'N';	break;
						case EMSSMT_Test:			str = 'T';	break;
						case EMSSMT_Combination:	str = 'C';	break;
						case EMSSMT_Invalid:			str = 'X';	break;
					}

					if (lpSoln->hdr.bLocalFlag)
					{
						sprintf(szMF12,"+%d",lpSoln->hdr.nFreqBand);
					}
					else
					{
						sprintf(szMF12,"-%d",lpSoln->hdr.nFreqBand);
					}
					
					sprintf( szBuffer, c_szSit122CSolnHdr2Fmt,
							szMF12,						//MF12
							str,						//MF619
							lpSoln->hdr.nBitErrorsPreamble,	//MF626
							lpSoln->hdr.nBitErrorsField1,
							lpSoln->hdr.nBitErrorsField2,
							lpSoln->hdr.dPower		//MF628
							);

					hr = WriteLine( lpStream, szBuffer );
				}

				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSit122CSolnHdr3Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
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

EMS_RESULT CEMSSit122C::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit122CHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCode(),
						GetSatelliteID(),
						GetPassID(),
						GetAlertCount()
					);

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT
CEMSSit122C::ParseSitHeader(  CEMSSitTokenizer*    lpTokenizer,
                              BOOL                 bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A/MF06/MF07/MF10A + eol

		if ( 7 == nFldCount )
		{
		   EMSSITCODE sitCode;

			int nNumber          = 0;
         int nSitNumber       = 0;
         int nSitDestination  = 0;

			// MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				// MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}
			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

   			// MF04A Internal SIT number (aka SIT code)
				hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
			}

			if ( hr == EMS_OK )
			{
				SetSitCode( sitCode );

            // MF06 Satellite ID
				hr = msgField.GetMF6( sitField[3].szText, &nNumber );
			}
			if ( hr == EMS_OK )
			{
            SetSatelliteID( nNumber );

				// MF07 Pass ID (aka Orbit number)
            hr = msgField.GetMF7( sitField[4].szText, &nNumber );
         }
   		if ( hr == EMS_OK )
   		{
            SetPassID( nNumber );

			   // MF10A 
            hr = msgField.GetMF10A( sitField[5].szText, &nNumber );
         }
   		if ( hr == EMS_OK )
   		{
            SetAlertCount( nNumber );
            
			   if ( !msgField.IsEOL( sitField[6].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
		}
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
      }

		if ( bPeek )
      {
			UnReadSitLine( lpTokenizer, sitField, nFldCount );
      }
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT
CEMSSit122C::_ParseAlertLine1(   CEMSSitTokenizer*          lpTokenizer,
                                 LPEMSSITLOCALERTSOLUTION   lpAlertData )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && lpAlertData )
   {
      EMSSITFIELD sitField[ 16 ];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF11/MF07/MF13/MF14/MF21A + eol

         if ( 6 == nFldCount )
         {
            hr = msgField.GetMF11( sitField[0].szText, &(lpAlertData->hdr.nPrimaryLutID) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF7( sitField[1].szText, reinterpret_cast<int*>(&(lpAlertData->hdr.ulPass)) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF13( sitField[2].szText, &(lpAlertData->sideA.dBias),
                                       &(lpAlertData->sideA.dBSdev), &(lpAlertData->sideA.dDrift) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF14( sitField[3].szText, &(lpAlertData->sideA.timeTCA) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF21A( sitField[4].szText, &(lpAlertData->sideA.nNumPoints) );
            }
            if ( EMS_OK == hr )
            {
				   if ( !msgField.IsEOL( sitField[5].szText ) )
               {
					   hr = EMS_SIT_SYNTAX_EOL;
               }
            }
         }
         else
         {
	         hr = EMS_SIT_FIELD_COUNT_ERROR;
         }
      }
   }
   else
   {
	   hr = EMS_BAD_PARAM;
   }
   return hr;
}

CEMSSit122E::CEMSSit122E()
{
	SetSitCode( 0x122E );
}

CEMSSit122E::~CEMSSit122E()
{
	Reset();
}

void CEMSSit122E::Reset( void )
{
	CEMSSit122A::Reset();
	SetSitCode(0x122E);
	m_wLutType = EMSLutTypeUnknown;
}



EMS_RESULT 
CEMSSit122E::_ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF11/MF647/MF648 eol

			if( nFldCount == 4 )
			{
				CEMSSitMsgField msgField;
				EMSTIME timeMsg;
				int nNumber=0, nLutID = 0, nDuplicates=0 ;
				double dTimeOffset = 0.0;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0, dFreq=0.0, dFreqOffset=0.0;

				hr = msgField.GetMF11( sitField[0].szText, &nLutID );

				if( EMS_OK == hr )
				{
					lpAlertData->hdr.nPrimaryLutID = nLutID;

					hr = msgField.GetMF647( sitField[1].szText, &dFreq, &dFreqOffset );
				}

				if( EMS_OK == hr )
				{
					lpAlertData->hdr.dRecvFreq = dFreq;

					lpAlertData->hdr.dLutFreqOffset = dFreqOffset;

					hr = msgField.GetMF648( sitField[ 2 ].szText, &timeMsg, &dTimeOffset );
				}

				if( EMS_OK == hr )
				{
					lpAlertData->hdr.timeMsg = timeMsg;

					lpAlertData->hdr.dLutTimeOffset = dTimeOffset;

					if( !msgField.IsEOL( sitField[3].szText ) )
					{
						hr = EMS_SIT_SYNTAX_EOL;
					}
				}
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

EMS_RESULT 
CEMSSit122E::_ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0, nType = '?', nPreamble=0, nPF1=0, nPF2=0 ;
		double dPower = 0.0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF12A/MF619/MF626/MF628 eol

			if( nFldCount == 5 )
			{
				CEMSSitMsgField msgField;
				TCHAR           cDataType;
				int nNumber=0, nLutID = 0, nPoints=0, nFreqBand=0;
				BOOL bLocalFlag = FALSE;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0;

				hr = msgField.GetMF12A( sitField[0].szText, &cDataType );

				if( EMS_OK == hr )
				{ 
					if( (_T('G') == cDataType) || (_T('G') == cDataType) )
					{
						m_wLutType = EMSGeoLutType;
					}
					else if( (_T('L') == cDataType) || (_T('l') == cDataType) )
					{
						m_wLutType = EMSLeoLutType;
					}
					else if( (_T('M') == cDataType) || (_T('m') == cDataType) )
					{
						m_wLutType = EMSMeoLutType;
					}
					else
					{
						hr = EMS_SIT_UNKNOWN_TYPE;
						m_wLutType = EMSLutTypeUnknown;
					}

					if( EMS_OK == hr )
					{
						hr = msgField.GetMF619( sitField[1].szText, reinterpret_cast<int*>(&(lpAlertData->hdr.msgType)) );
					}
				}

				if( EMS_OK == hr )
				{
					hr = msgField.GetMF626( sitField[ 2 ].szText, &nPreamble, &nPF1, &nPF2 );
				}

				if( EMS_OK == hr )
				{
					lpAlertData->hdr.nBitErrorsPreamble = nPreamble;

					lpAlertData->hdr.nBitErrorsField1 = nPF1;

					lpAlertData->hdr.nBitErrorsField2 = nPF2;

					hr = msgField.GetMF628( sitField[ 3 ].szText, &dPower );
				}

				if( EMS_OK == hr )
				{
				 	lpAlertData->hdr.dPower	 = dPower;

					if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit122E::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT      hr = EMS_OK;
	TCHAR           szBuffer[256], szBeaconMsg[36];
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR           szTime[40];
	TCHAR           cMF12A = _T(' ');
	ULONG			ulYear;
	char			str;


	if ( lpStream )
	{
		for( int i = 0; ( EMS_OK == hr ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if( lpSoln )
			{
				for( int j = 0; j < 15; j++ )
				{
					sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				tmpTime.SetTime( lpSoln->hdr.timeMsg );
				tmpTime.GetTime( &timeFields );

				ulYear = timeFields.nYear - (timeFields.nYear/100)*100;
				sprintf(szTime,"%2.2d %3.3d %2.2d%2.2d %02d.%06d",
						ulYear,
						timeFields.nJulianDay,
						timeFields.nHour,
						timeFields.nMinute,
						timeFields.nSecond,
						timeFields.lNanosecond/1000);
		
				// ticket# 51915, make sure the freq. offset is not > 9999.999 or < -9999.999 (snnnn.nnn).
				double dLutFreqOffset = lpSoln->hdr.dLutFreqOffset; 

				if( dLutFreqOffset > 9999.999 ) 
					dLutFreqOffset = 9999.999;
				else if( dLutFreqOffset < -9999.999 ) 
					dLutFreqOffset = -9999.999;

				sprintf( szBuffer, c_szSit122ESolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						lpSoln->hdr.dRecvFreq, //MF647
						dLutFreqOffset,
						szTime					//MF648
						);

				hr = WriteLine( lpStream, szBuffer );


				if( EMS_OK == hr )
				{
					switch ( lpSoln->hdr.msgType )
					{
						default:
						case EMSSMT_Normal:			str = 'N';	break;
						case EMSSMT_Test:			str = 'T';	break;
						case EMSSMT_Combination:	str = 'C';	break;
						case EMSSMT_Invalid:		str = 'X';	break;
					}

					switch( m_wLutType )
					{
					case EMSGeoLutType:
						{
							cMF12A = _T('G');
						}
						break;
					case EMSLeoLutType:
						{
							cMF12A = _T('L');
						}
						break;
					case EMSMeoLutType:
						{
							cMF12A = _T('M');
						}
						break;
					default:
						{
							cMF12A = _T(' ');
							hr = EMS_SIT_UNKNOWN_TYPE;
						}
						break;
					}

					if( EMS_OK == hr )
					{
						memset( szBuffer, 0, sizeof(szBuffer) );
						sprintf( szBuffer, c_szSit122ESolnHdr2Fmt,
								cMF12A,						//MF12A
								str	,						//MF619
								lpSoln->hdr.nBitErrorsPreamble,	//MF626
								lpSoln->hdr.nBitErrorsField1,
								lpSoln->hdr.nBitErrorsField2,
								lpSoln->hdr.dPower		//MF628
								);

						hr = WriteLine( lpStream, szBuffer );
					}
				}

				if( EMS_OK == hr )
				{
					sprintf( szBuffer, c_szSit122ASolnHdr3Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
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
