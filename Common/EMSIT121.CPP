/********************************************************************
*	Module:			emsit121.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit121
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
#include <stdio.h>

#include <array.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit121.h"
#include "sitfield.h"

const TCHAR c_szSit121HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit121SolnHdr1Fmt[] = TEXT("/%04d/%+02d/%s/%s/%01d");
const TCHAR c_szSit121SolnHdr2Fmt[] = TEXT("/%01d/%s/%04d/%02d/%04d %02d");
const TCHAR c_szSit121SolnLineFmt[] = TEXT("/%+04d/%+07.3lf/%+08.3lf/%s/%02.0lf/%s/%01.0lf/%05.1lf %05.1lf");

const TCHAR c_szSit121AHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit121ASolnHdrFmt[] = TEXT("/%04d/%s/%02d/%04d %02d/%s");
const TCHAR c_szSit121ASolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit121ASolnLineFmt2[] = TEXT("/%s/%s/%02.0lf/%01.0lf");
const TCHAR c_szSit121ASolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf");

const TCHAR c_szSit121BHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit121BSolnHdrFmt[] = TEXT("/%04d/%s/%02d/%04d %02d/%s");
const TCHAR c_szSit121BSolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit121BSolnLineFmt2[] = TEXT("/%s/%s/%02.0lf/%01.0lf");
const TCHAR c_szSit121BSolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf/%s");


CEMSSit121::CEMSSit121()
{
	SetSitNumber(121);
	SetMaxAlertCount ( EMS_MAX_SIT121_ALERTS );
}

CEMSSit121::~CEMSSit121()
{
	Reset();
}

void CEMSSit121::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetSitNumber(121);
	SetAlertCount( 0 );
	SetMaxAlertCount ( EMS_MAX_SIT121_ALERTS );
}

EMS_RESULT CEMSSit121::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField msgField;

			sprintf( szBuffer,	c_szSit121SolnLineFmt,
						lpSide->nServiceArea,		//MF24
						lpSide->dLatitude,			//MF25
						lpSide->dLongitude,			//MF26

						msgField.TextMF27( lpSide->dErrEllipseAngle,	
									lpSide->dErrEllipseMajAxis,
									lpSide->dErrEllipseMinAxis ), 

						lpSide->dProbability * 100,	//MF28
						msgField.TextMF29( lpSide->timeNextVisibility ), //MF29
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

EMS_RESULT CEMSSit121::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				sprintf( szBuffer, c_szSit121SolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						lpSoln->hdr.nFreqBand,	//MF12
						msgField.TextMF13( lpSoln->sideA.dBias,		//MF13
										lpSoln->sideA.dBSdev,
										lpSoln->sideA.dDrift ),
						msgField.TextMF14( lpSoln->sideA.timeTCA ),
						lpSoln->sideA.wWindowFactor//MF15
					 );

				hr = WriteLine( lpStream, szBuffer );

				sprintf( szBuffer, c_szSit121SolnHdr2Fmt, 
						lpSoln->sideA.wIterations,	//MF16
						msgField.TextMF17( lpSoln->sideA.dCTA ),
						lpSoln->hdr.nSecondaryLutID,	//MF18		
						lpSoln->hdr.nSideBands,	//MF19
						lpSoln->hdr.nSweepPeriod,		//MF20
						lpSoln->hdr.nSweepPeriodSdev
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

EMS_RESULT CEMSSit121::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit121HdrFmt, 
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

EMS_RESULT CEMSSit121::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	return EMS_NOT_IMPLEMENTED;
}

EMS_RESULT CEMSSit121::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	return EMS_NOT_IMPLEMENTED;
}


//************** 121A **************

CEMSSit121A::CEMSSit121A()
{
	SetSitCode(0x121A);
	SetMaxAlertCount( EMS_MAX_SIT121A_ALERTS );
}

CEMSSit121A::~CEMSSit121A()
{
	Reset();
}

void CEMSSit121A::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 121 );
	SetSitCode(0x121A);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT121A_ALERTS );
}

EMS_RESULT CEMSSit121A::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];
	CEMSSitMsgField msgField;

	if ( lpStream )
	{
		if ( lpSide )
		{
			sprintf(szBuffer,
						c_szSit121ASolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A

						msgField.TextMF14( lpSide->timeTCA ), //MF14

						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999),		//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA ) //MF17A
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit121ASolnLineFmt2,

						msgField.TextMF622( lpSide->dLatLongCorrCoeff ), 

						msgField.TextMF27( lpSide->dErrEllipseAngle,
								lpSide->dErrEllipseMajAxis,
								lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence			//MF30
					);

				hr = WriteLine( lpStream, szBuffer );
			}

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit121ASolnLineFmt3,
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

EMS_RESULT CEMSSit121A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR str[10];
	TCHAR szMF12[3];
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				switch ( lpSoln->hdr.solnType )
				{
					default:
					case EMSSST_Unknown:	
						lstrcpy( str, TEXT("UN") );
						break;
					case EMSSST_Beacon:		
						lstrcpy( str, TEXT("BE") );	
						break;
					case EMSSST_Interferer:	
						lstrcpy( str, TEXT("IN") );	
						break;
				}

				if (lpSoln->hdr.bLocalFlag)
				{
					sprintf(szMF12,"+%d",lpSoln->hdr.nFreqBand);
				}
				else
				{
					sprintf(szMF12,"-%d",lpSoln->hdr.nFreqBand);
				}

				sprintf( szBuffer, c_szSit121ASolnHdrFmt, 
						 lpSoln->hdr.nPrimaryLutID,	//MF11
						 szMF12,					//MF12
						 lpSoln->hdr.nSideBands,	//MF19
						 lpSoln->hdr.nSweepPeriod,		//MF20
						 lpSoln->hdr.nSweepPeriodSdev ,
						 str						  //MF618
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

EMS_RESULT CEMSSit121A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		sprintf( szBuffer, c_szSit121AHdrFmt, 
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

//************** 121B **************

CEMSSit121B::CEMSSit121B()
{
	SetSitCode(0x121B);
	SetMaxAlertCount( EMS_MAX_SIT121B_ALERTS );
}

CEMSSit121B::~CEMSSit121B()
{
	Reset();
}

void CEMSSit121B::Reset( void )
{
	int nSitNumber = GetSitNumber();

	CEMSSitAlertMessageBase::Reset();

	SetSitNumber( nSitNumber ? nSitNumber : 121 );
	SetSitCode(0x121B);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT121B_ALERTS );
}

EMS_RESULT CEMSSit121B::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];
	CEMSSitMsgField msgField;

	if ( lpStream )
	{
		if ( lpSide )
		{
			sprintf(szBuffer,
						c_szSit121BSolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A

						msgField.TextMF14( lpSide->timeTCA ), //MF14

						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999),		//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA ) //MF17A
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit121BSolnLineFmt2,

						msgField.TextMF622( lpSide->dLatLongCorrCoeff ), 

						msgField.TextMF27( lpSide->dErrEllipseAngle,
								lpSide->dErrEllipseMajAxis,
								lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence			//MF30
					);

				hr = WriteLine( lpStream, szBuffer );
			}

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit121BSolnLineFmt3,
						msgField.TextMF13( lpSide->dBias,				//MF13
										lpSide->dBSdev,
										lpSide->dDrift ),
						lpSide->dDataResSdev,							//MF31
						lpSide->dDataResTrend,
						msgField.TextMF29( lpSide->timeNextVisibility ) //MF29
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
CEMSSit121B::_ParseSolutionSideLine3(  CEMSSitTokenizer*          lpTokenizer, 
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

