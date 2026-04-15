/********************************************************************
*	Module:			emsit115.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit115
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
#include "emsit115.h"
#include "sitfield.h"

const TCHAR c_szSit115HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit115SolnHdr1Fmt[] = TEXT("/%04d/%+02d/%s/%s/%01d");
const TCHAR c_szSit115SolnHdr2Fmt[] = TEXT("/%01d/%s/%04d/%02d/%04d %02d");
const TCHAR c_szSit115SolnLineFmt[] = TEXT("/%+04d/%+07.3lf/%+08.3lf/%s/%02.0lf/%s/%01.0lf/%05.1lf %05.1lf");

const TCHAR c_szSit115AHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d/%03d/%03d");
const TCHAR c_szSit115ASolnHdrFmt[] = TEXT("/%04d/%s/%02d/%04d %02d/%s");
const TCHAR c_szSit115ASolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit115ASolnLineFmt2[] = TEXT("/%s/%s/%02.0lf/%01.0lf");
const TCHAR c_szSit115ASolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf");

const TCHAR c_szSit115BHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d");
const TCHAR c_szSit115BSolnHdrFmt[] = TEXT("/%04d/%s/%02d/%04d %02d/%s");
const TCHAR c_szSit115BSolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit115BSolnLineFmt2[] = TEXT("/%s/%s/%02.0lf/%01.0lf");
const TCHAR c_szSit115BSolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf");


const TCHAR c_szSit115CHdrFmt[ ] = TEXT("/%03d/%04d/%04X/%03d/%05d/%03d/%03d/%03d");
const TCHAR c_szSit115CSolnHdrFmt[] = TEXT("/%04d/%s/%02d/%04d %02d/%s");
const TCHAR c_szSit115CSolnLineFmt1[] = TEXT("/%+08.4lf/%+09.4lf/%s/%01d/%04d/%01d/%s");
const TCHAR c_szSit115CSolnLineFmt2[] = TEXT("/%s/%s/%02.0lf/%01.0lf");
const TCHAR c_szSit115CSolnLineFmt3[] = TEXT("/%s/%05.1lf %05.1lf/%s");


CEMSSit115::CEMSSit115()
{
	SetSitNumber(115);
	SetMaxAlertCount ( EMS_MAX_SIT115_ALERTS );
}

CEMSSit115::~CEMSSit115()
{
	Reset();
}

void CEMSSit115::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetSitNumber(115);
	SetAlertCount( 0 );
	SetMaxAlertCount ( EMS_MAX_SIT115_ALERTS );
}

EMS_RESULT CEMSSit115::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField msgField;

			sprintf(szBuffer,
						c_szSit115SolnLineFmt,
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

EMS_RESULT CEMSSit115::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				CEMSSitMsgField msgField;

				sprintf( szBuffer, c_szSit115SolnHdr1Fmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						lpSoln->hdr.nFreqBand,	//MF12
						msgField.TextMF13( lpSoln->sideA.dBias,		//MF13
										lpSoln->sideA.dBSdev,
										lpSoln->sideA.dDrift ),
						msgField.TextMF14( lpSoln->sideA.timeTCA ), 
						lpSoln->sideA.wWindowFactor//MF15
					 );

				hr = WriteLine( lpStream, szBuffer );

				sprintf( szBuffer, c_szSit115SolnHdr2Fmt, 
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

EMS_RESULT CEMSSit115::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit115HdrFmt, 
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

CEMSSit115A::CEMSSit115A()
{
	m_nAlerts121 = 0;
	m_nAlerts243 = 0;

	SetSitCode(0x115A);

	SetMaxAlertCount( EMS_MAX_SIT115A_ALERTS );
}

CEMSSit115A::~CEMSSit115A()
{
	Reset();
}

void CEMSSit115A::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	m_nAlerts121 = 0;
	m_nAlerts243 = 0;
	SetSitCode(0x115A);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT115A_ALERTS );
}

EMS_RESULT
CEMSSit115A::ParseSitHeader(  CEMSSitTokenizer*    lpTokenizer, 
                              BOOL                 bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

      // should find /MF04/MF05/MF04A/MF06/MF07/MF08A/MF08B/MF08C + eol

		if ( 9 == nFldCount )
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

			   // MF8A Number of located incident solutions in this message
            hr = msgField.GetMF8A( sitField[5].szText, &nNumber );
         }
   		if ( hr == EMS_OK )
   		{
            SetAlertCount( nNumber );

		      // MF8B Number of 121.5 MHz beacons located
            hr = msgField.GetMF8B( sitField[6].szText, &m_nAlerts121 );
         }
      	if ( hr == EMS_OK )
      	{
	         // MF8C Number of 243.0 MHz beacons located
            hr = msgField.GetMF8C( sitField[7].szText, &m_nAlerts243 );
         }
      	if ( hr == EMS_OK )
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
CEMSSit115A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );
   
   if ( hr == EMS_OK )
   {
      if ( GetAlertCount() > 0 )
      {
         _AllocSolutions( GetAlertCount() );

         LPEMSSITLOCALERTSOLUTION lpLocateSolution = 0;

         for ( int ii = 0; ii < GetAlertCount(); ii++ )
         {
            lpLocateSolution = _GetSolutionPtr( ii );

            if ( lpLocateSolution )
            {
               // /MF11/MF12/MF19/MF20/MF618
					hr = _ParseSolutionHdr( lpTokenizer, &(lpLocateSolution->hdr) );

               // /MF25A/MF26A/MF14/MF15/MF21A/MF16/MF17A
               // /MF622/MF27/MF28/MF 30
               // /MF13/MF31
               if ( EMS_OK == hr )
               {
					   hr = _ParseSolutionSide( lpTokenizer, &(lpLocateSolution->sideA) );
               }
               // /MF25A/MF26A/MF14/MF15/MF21A/MF16/MF17A
               // /MF622/MF27/MF28/MF 30
               // /MF13/MF31
               if ( EMS_OK == hr )
               {
					   hr = _ParseSolutionSide( lpTokenizer, &(lpLocateSolution->sideB) );
               }
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

EMS_RESULT
CEMSSit115A::_ParseSolutionHdr(  CEMSSitTokenizer*       lpTokenizer,
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
         
         // /MF11/MF12/MF19/MF20/MF618 + eol

		   if ( 6 == nFldCount )
         {
            hr = msgField.GetMF11( sitField[0].szText, &(pSolutionHeader->nPrimaryLutID) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF12( sitField[1].szText, &(pSolutionHeader->bLocalFlag), &(pSolutionHeader->nFreqBand) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF19( sitField[2].szText, &(pSolutionHeader->nSideBands) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF20( sitField[3].szText, &(pSolutionHeader->nSweepPeriod), &(pSolutionHeader->nSweepPeriodSdev) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF618( sitField[4].szText, &(pSolutionHeader->solnType) );
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
CEMSSit115A::_ParseSolutionSide( CEMSSitTokenizer*          lpTokenizer, 
                                 EMSSITLOCALERTSIDESOLN*    pSolutionSide )
{
   EMS_RESULT hr = EMS_OK;

   // /MF25A/MF26A/MF14/MF15/MF21A/MF16/MF17A
   hr = _ParseSolutionSideLine1( lpTokenizer, pSolutionSide );

   if ( EMS_OK == hr )
   {
      // /MF622/MF27/MF28/MF30
      hr = _ParseSolutionSideLine2( lpTokenizer, pSolutionSide );
   }
   if ( EMS_OK == hr )
   {
      // /MF13/MF31
      hr = _ParseSolutionSideLine3( lpTokenizer, pSolutionSide );
   }
   return hr;
}

EMS_RESULT
CEMSSit115A::_ParseSolutionSideLine1(  CEMSSitTokenizer*          lpTokenizer, 
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
         
         // /MF25A/MF26A/MF14/MF15/MF21A/MF16/MF17A + eol

	      if ( 8 == nFldCount )
         {
            hr = msgField.GetMF25A( sitField[0].szText, &(pSolutionSide->dLatitude) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF26A( sitField[1].szText, &(pSolutionSide->dLongitude) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF14(  sitField[2].szText, &(pSolutionSide->timeTCA) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF15(  sitField[3].szText, reinterpret_cast<int*>(&(pSolutionSide->wWindowFactor)) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF21A( sitField[4].szText, &(pSolutionSide->nNumPoints) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF16(  sitField[5].szText, reinterpret_cast<int*>(&(pSolutionSide->wIterations)) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF17A( sitField[6].szText, &(pSolutionSide->dCTA) );
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
CEMSSit115A::_ParseSolutionSideLine2(  CEMSSitTokenizer*          lpTokenizer, 
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
         
         // /MF622/MF27/MF28/MF30 + eol

	      if ( 5 == nFldCount )
         {
            hr = msgField.GetMF622( sitField[0].szText, &(pSolutionSide->dLatLongCorrCoeff) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF27(  sitField[1].szText, &(pSolutionSide->dErrEllipseAngle), &(pSolutionSide->dErrEllipseMajAxis), &(pSolutionSide->dErrEllipseMinAxis) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF28(  sitField[2].szText, &(pSolutionSide->dProbability) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF30(  sitField[3].szText, &(pSolutionSide->dConfidence) );
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
CEMSSit115A::_ParseSolutionSideLine3(  CEMSSitTokenizer*          lpTokenizer, 
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
         
         // /MF13/MF31 + eol

	      if ( 3 == nFldCount )
         {
            hr = msgField.GetMF13( sitField[0].szText, &(pSolutionSide->dBias), &(pSolutionSide->dBSdev), &(pSolutionSide->dDrift) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF31( sitField[1].szText, &(pSolutionSide->dDataResSdev), &(pSolutionSide->dDataResTrend) );
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


EMS_RESULT CEMSSit115A::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];
	CEMSSitMsgField msgField;

	if ( lpStream )
	{
		if ( lpSide )
		{
			sprintf(szBuffer,
						c_szSit115ASolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A

						msgField.TextMF14( lpSide->timeTCA ), 

						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999 ),		//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA )
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit115ASolnLineFmt2,

						msgField.TextMF622( lpSide->dLatLongCorrCoeff ), 

						msgField.TextMF27( lpSide->dErrEllipseAngle,
								lpSide->dErrEllipseMajAxis,
								lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence		//MF30
						
					);

				hr = WriteLine( lpStream, szBuffer );
			}

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit115ASolnLineFmt3,
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

EMS_RESULT CEMSSit115A::GenerateSitBody( IEMSSeqStream *lpStream )
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

				sprintf( szBuffer, c_szSit115ASolnHdrFmt, 
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

EMS_RESULT CEMSSit115A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		sprintf( szBuffer, c_szSit115AHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCode(),
						GetSatelliteID(),
						GetPassID(),
						GetAlertCount(),
						m_nAlerts121,
						m_nAlerts243
				 );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}



EMS_RESULT CEMSSit115A::AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln )
{
	CEMSSitAlertMessageBase::AddSolution(lpSoln);
	switch (lpSoln->hdr.nFreqBand)
	{
		case 1:
			m_nAlerts121++;
			break;
		case 2:
			m_nAlerts243++;
			break;
		default:
			break;
	}
	return EMS_OK;

}


CEMSSit115B::CEMSSit115B()
{
	SetSitCode(0x115B);
	SetMaxAlertCount( EMS_MAX_SIT115B_ALERTS );
}

CEMSSit115B::~CEMSSit115B()
{
	Reset();
}

void CEMSSit115B::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetSitCode(0x115B);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT115B_ALERTS );
}

EMS_RESULT CEMSSit115B::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];
	CEMSSitMsgField	msgField;

	if ( lpStream )
	{
		if ( lpSide )
		{
			sprintf(szBuffer,
						c_szSit115BSolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A
						msgField.TextMF14( lpSide->timeTCA ),
						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999),		//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA	)			//MF17A
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit115BSolnLineFmt2,

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
						c_szSit115BSolnLineFmt3,
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

EMS_RESULT CEMSSit115B::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szMF12[3];
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);
			
			if ( lpSoln )
			{
				if (lpSoln->hdr.bLocalFlag)
				{
					sprintf(szMF12,"+%d",lpSoln->hdr.nFreqBand);
				}
				else
				{
					sprintf(szMF12,"-%d",lpSoln->hdr.nFreqBand);
				}


				sprintf( szBuffer, c_szSit115BSolnHdrFmt, 
						lpSoln->hdr.nPrimaryLutID,	//MF11
						szMF12,					//MF12
						lpSoln->hdr.nSideBands,	//MF19
						lpSoln->hdr.nSweepPeriod,		//MF20
						lpSoln->hdr.nSweepPeriodSdev,
						TEXT("IN")						  //MF618
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

EMS_RESULT CEMSSit115B::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSit115BHdrFmt, 
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
CEMSSit115B::ParseSitHeader(  CEMSSitTokenizer*    lpTokenizer, 
                              BOOL                 bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

      // should find /MF04/MF05/MF04A/MF06/MF07/MF08D + eol

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

			   // MF8D Number of 406.0 MHz interferers located.
            hr = msgField.GetMF8D( sitField[5].szText, &nNumber );
         }
         if ( EMS_OK == hr )
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


CEMSSit115C::CEMSSit115C()
{
	m_nAlerts121 = 0;
	m_nAlerts243 = 0;
	SetSitCode(0x115C);
	SetMaxAlertCount( EMS_MAX_SIT115C_ALERTS );
}

CEMSSit115C::~CEMSSit115C()
{
	Reset();
}

void CEMSSit115C::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	m_nAlerts121 = 0;
	m_nAlerts243 = 0;
	SetSitCode(0x115C);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT115C_ALERTS );
}



EMS_RESULT CEMSSit115C::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256];
	CEMSSitMsgField msgField;

	if ( lpStream )
	{
		if ( lpSide )
		{
			sprintf(szBuffer,
						c_szSit115CSolnLineFmt1,
						lpSide->dLatitude,			//MF25A
						lpSide->dLongitude,			//MF26A

						msgField.TextMF14( lpSide->timeTCA ), 

						lpSide->wWindowFactor,		//MF15
						min( lpSide->nNumPoints, 9999),		//MF21A
						lpSide->wIterations,		//MF16
						msgField.TextMF17A( lpSide->dCTA )
					);
					
			hr = WriteLine( lpStream, szBuffer );

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSit115CSolnLineFmt2,

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
						c_szSit115CSolnLineFmt3,
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
CEMSSit115C::_ParseSolutionSideLine3(  CEMSSitTokenizer*          lpTokenizer, 
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

