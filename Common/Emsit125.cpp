/********************************************************************
*	Module:			emsit125.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit125
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
#include "emsit125.h"
#include "sitfield.h"

const TCHAR c_szSit125HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit125SolnHdr1Fmt[] = TEXT("/%04d/%+02d/%s/%s/%01d");
const TCHAR c_szSit125SolnHdr2Fmt[] = TEXT("/%01d/%s/%04d/%02d");
const TCHAR c_szSit125SolnHdr3Fmt[] = TEXT("/%s");
const TCHAR c_szSit125SolnLineFmt[] = TEXT("/%+04d/%+07.3lf/%+08.3lf/%s/%02.0lf/%s/%01.0lf/%05.1lf %05.1lf");

const TCHAR c_szSit125AHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit125ASolnHdrFmt[] = TEXT("/%04d/%04d/%05d/%s/%c/%04d/%s/%s");
const TCHAR c_szSit125ASolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit125ASolnLineFmt2[] = TEXT("/%s/%s/%02.lf/%01.lf");
const TCHAR c_szSit125ASolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf");

const TCHAR c_szSit125BHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit125BSolnHdrFmt[] = TEXT("/%04d/%04d/%05d/%s/%c/%04d/%01d %01d %01d/%s");
const TCHAR c_szSit125BSolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit125BSolnLineFmt2[] = TEXT("/%s/%s/%02.lf/%01.lf");
const TCHAR c_szSit125BSolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf/%s");


CEMSSit125::CEMSSit125()
{
	SetSitNumber(125);
	SetMaxAlertCount( EMS_MAX_SIT125_ALERTS );
}

CEMSSit125::~CEMSSit125()
{
	Reset();
}

void CEMSSit125::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetSitNumber(125);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT125_ALERTS );
}

EMS_RESULT CEMSSit125::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
//	TCHAR szNextVisTime[40];
	TCHAR szBuffer[256];
//	ULONG ulYear;
//	EMSTIMEFIELDS timeFields;
//	CEMSTime		tmpTime;

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField msgField;

	//		tmpTime.SetTime(lpSide->timeNextVisibility);
//			tmpTime.GetTime(&timeFields);
//			ulYear = timeFields.nYear - (timeFields.nYear/100)*100;
//			sprintf(szNextVisTime,"%2.2d %3.3d %2.2d%2.2d",
//					ulYear,
//					timeFields.nJulianDay,
//					timeFields.nHour,
//					timeFields.nMinute
//					);
		
			sprintf(szBuffer,
						c_szSit125SolnLineFmt,
						lpSide->nServiceArea,		//MF24
						lpSide->dLatitude,			//MF25
						lpSide->dLongitude,			//MF26

						msgField.TextMF27( lpSide->dErrEllipseAngle,	
									lpSide->dErrEllipseMajAxis,
									lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28

						msgField.TextMF29( lpSide->timeNextVisibility ),

						lpSide->dConfidence,		//MF30
						lpSide->dDataResSdev,
						lpSide->dDataResTrend		//MF31
					);
			hr = WriteLine( lpStream, szBuffer );	
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}
	return hr;
}

EMS_RESULT CEMSSit125::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
//	EMSTIMEFIELDS   timeFields;
//	CEMSTime		tmpTime;
//	TCHAR szTCA[40];
//	ULONG ulYear;

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{	
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				CEMSSitMsgField msgField;

				for ( int j = 0; j < 15; j++ )
				{
					sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				sprintf( szBuffer, c_szSit125SolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						lpSoln->hdr.nFreqBand,	//MF12

						msgField.TextMF13( lpSoln->sideA.dBias,		//MF13
										lpSoln->sideA.dBSdev,
										lpSoln->sideA.dDrift ),

						msgField.TextMF14( lpSoln->sideA.timeTCA ),
						lpSoln->sideA.wWindowFactor//MF15
					 );

				hr = WriteLine( lpStream, szBuffer );

				sprintf( szBuffer, c_szSit125SolnHdr2Fmt, 
						lpSoln->sideA.wIterations,	//MF16
						msgField.TextMF17( lpSoln->sideA.dCTA ),
						lpSoln->hdr.nSecondaryLutID,	//MF18		
						min( lpSoln->sideA.nNumPoints, 99 )		//MF21
						 );

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSit125SolnHdr3Fmt, szBeaconMsg); //MF23

					hr = WriteLine( lpStream, szBuffer );
				}

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideA );

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideB );
			}
			else
				hr = EMS_UNKNOWN_ERROR;
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit125::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit125HdrFmt, 
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

CEMSSit125A::CEMSSit125A()
{
	SetSitCode(0x125A);
	SetMaxAlertCount( EMS_MAX_SIT125A_ALERTS );

	// This class is derived from 115A so the 125 constructor is not
	// going to get called which is where the sit number gets set
	// ... so we had better do it here
	SetSitNumber(125); 
}

CEMSSit125A::~CEMSSit125A()
{
	Reset();
}

void CEMSSit125A::Reset( void )
{
	int	nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 125 );
	SetSitCode(0x125A);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT125A_ALERTS );
}

EMS_RESULT CEMSSit125A::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR 				szBuffer[256];

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField 	msgField;

			sprintf(szBuffer,
						c_szSit125ASolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A
						msgField.TextMF14( lpSide->timeTCA ),
						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999 ),			//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA )
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit125ASolnLineFmt2,

						msgField.TextMF622( lpSide->dLatLongCorrCoeff ),

						msgField.TextMF27( lpSide->dErrEllipseAngle,	
									lpSide->dErrEllipseMajAxis,
									lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence,		//MF30
						lpSide->dDataResSdev
					);

				hr = WriteLine( lpStream, szBuffer );
			}
			

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit125ASolnLineFmt3,
						msgField.TextMF13( lpSide->dBias,				//MF13
										lpSide->dBSdev,
										lpSide->dDrift ),
						lpSide->dDataResSdev,		//MF31
						lpSide->dDataResTrend		
						
						);
					
				hr = WriteLine( lpStream, szBuffer );
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}
	return hr;
}

EMS_RESULT CEMSSit125A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36], szMF12[3];
	TCHAR str;

	CEMSSitMsgField msgField;

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

				sprintf( szBuffer, c_szSit125ASolnHdrFmt, 
						lpSoln->hdr.nPrimaryLutID,		//MF11
						lpSoln->hdr.nSecondaryLutID,	//MF18
						lpSoln->hdr.ulPass,				//MF07
						szMF12,							//MF12
						str,							//MF619
						min( lpSoln->hdr.nNumPoints, 9999 ) ,			//MF21B
						msgField.TextMF626( lpSoln->hdr.nBitErrorsPreamble,		//MF626
								   lpSoln->hdr.nBitErrorsField1,
								   lpSoln->hdr.nBitErrorsField2 ),
						szBeaconMsg						//MF23
						);
	
				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideA );

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideB );
			}
			else
				hr = EMS_UNKNOWN_ERROR;
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit125A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit125AHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCode(),
						GetSatelliteID(),
						GetPassID(),
						GetAlertCount() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT
CEMSSit125A::ParseSitHeader(  CEMSSitTokenizer*    lpTokenizer, 
                              BOOL                 bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

      // should find /MF04/MF05/MF04A/MF06/MF07/MF08E + eol

		if ( 7 == nFldCount )
		{
			int nNumber = 0;
			EMSSITCODE sitCode;

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

			   // MF8E Number of 406 MHz beacons located
            hr = msgField.GetMF8E( sitField[5].szText, &nNumber );
         }
   		if ( hr == EMS_OK )
   		{
            SetAlertCount( nNumber );
         }
      	if ( hr == EMS_OK )
      	{
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
CEMSSit125A::_ParseSolutionHdr(  CEMSSitTokenizer*       lpTokenizer,
                                 EMSSITLOCALERTHEADER*   pSolutionHeader )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && pSolutionHeader )
   {
	   EMSSITFIELD sitField[ 16 ];
	   int         nFldCount = 0;

	   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
   	   CEMSSitMsgField msgField;
         
         // /MF11/MF18/MF07/MF12/MF619/MF21B/MF626/MF23 + eol

		   if ( 9 == nFldCount )
         {
            hr = msgField.GetMF11( sitField[0].szText, &(pSolutionHeader->nPrimaryLutID) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF18( sitField[1].szText, &(pSolutionHeader->nSecondaryLutID) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF7( sitField[2].szText, reinterpret_cast<int*>(&(pSolutionHeader->ulPass)) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF12( sitField[3].szText, &(pSolutionHeader->bLocalFlag), 
                                       &(pSolutionHeader->nFreqBand) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF619( sitField[4].szText, reinterpret_cast<int*>(&(pSolutionHeader->msgType)) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF21B( sitField[5].szText, &(pSolutionHeader->nNumPoints) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF626( sitField[6].szText, &(pSolutionHeader->nBitErrorsPreamble),
                        &(pSolutionHeader->nBitErrorsField1), &(pSolutionHeader->nBitErrorsField2) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF23( sitField[7].szText, pSolutionHeader->cBeaconMsg );
            }
   			if ( EMS_OK == hr )
   			{
   				if ( !msgField.IsEOL( sitField[8].szText ) )
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


CEMSSit125B::CEMSSit125B()
{
	SetSitCode(0x125B);
	SetMaxAlertCount( EMS_MAX_SIT125B_ALERTS );
}

CEMSSit125B::~CEMSSit125B()
{
	Reset();
}

void CEMSSit125B::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 125 );
	SetSitCode(0x125B);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT125B_ALERTS );
}


EMS_RESULT CEMSSit125B::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR 				szBuffer[256];

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField 	msgField;

			sprintf(szBuffer,
						c_szSit125BSolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A
						msgField.TextMF14( lpSide->timeTCA ),
						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999 ),			//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA )
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit125BSolnLineFmt2,

						msgField.TextMF622( lpSide->dLatLongCorrCoeff ),

						msgField.TextMF27( lpSide->dErrEllipseAngle,	
									lpSide->dErrEllipseMajAxis,
									lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence,		//MF30
						lpSide->dDataResSdev
					);

				hr = WriteLine( lpStream, szBuffer );
			}
			

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit125BSolnLineFmt3,
						msgField.TextMF13( lpSide->dBias,				//MF13
										lpSide->dBSdev,
										lpSide->dDrift ),
						lpSide->dDataResSdev,		//MF31
						lpSide->dDataResTrend,
						msgField.TextMF29( lpSide->timeNextVisibility )  //MF29
						
						);
					
				hr = WriteLine( lpStream, szBuffer );
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}
	return hr;
}

EMS_RESULT
CEMSSit125B::_ParseSolutionSideLine3(  CEMSSitTokenizer*          lpTokenizer, 
                                       EMSSITLOCALERTSIDESOLN*    pSolutionSide )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && pSolutionSide )
   {
      EMSSITFIELD sitField[ 16 ];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
	      CEMSSitMsgField msgField;
         
         // /MF13/MF31/29 + eol

	      if ( 4 == nFldCount )
         {
            hr = msgField.GetMF13( sitField[0].szText, &(pSolutionSide->dBias), &(pSolutionSide->dBSdev), &(pSolutionSide->dDrift) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF31( sitField[1].szText, &(pSolutionSide->dDataResSdev), &(pSolutionSide->dDataResTrend) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF29( sitField[2].szText, &(pSolutionSide->timeNextVisibility) );
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

