/********************************************************************
*       Module:                 emsit662.cpp
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Implementation of CEMSSit662A Class
*                              GeoLUT data collection summary
*       Usage:
*       Entry Point:
*       Input Files:
*       Output Files:
*       Comments:       
*                                       
*
*********************************************************************
*                     Copyright (c) 2002 by EMS Technologies, Inc.,
*                                                                               All rights reserved
*       This program is unpublished software and contains the trade secrets
*       and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

        Rev     Date                    Auth    Changes
        ===     ====                    ====    =======

        0.0     2002 Dec 20             fjp     start

********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include <array.h>
#include <sitfield.h>
#include <emsit662.h>

CEMSSit662A::CEMSSit662A() :
   m_bInitialized( false )
{
   SetSitNumber( 662 );
   SetSitCode( 0x662A );
   memset( &m_data, 0, sizeof( m_data ) );
}

CEMSSit662A::~CEMSSit662A()
{
}

void
CEMSSit662A::Reset( void )
{
   CEMSSitMessageBase::Reset();

   SetSitNumber( 662 );
   SetSitCode( 0x662A );
   memset( &m_data, 0, sizeof( m_data ) );
   m_bInitialized = false;
}

EMS_RESULT
CEMSSit662A::GenerateSitHeader( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      if ( m_bInitialized )
      {
         // MF# /04/05/04A = "/662/1234/662A"
         const TCHAR c_szSitHdrFmt[] = TEXT("/%03d/%04d/%s");

         TCHAR szBuffer[ 256 ];

         _sntprintf( szBuffer, 256, c_szSitHdrFmt,
            GetSitNumber(),         // MF# 04   sit number
            GetSitDestination(),    // MF# 05   sit destination
            GetSitCodeStr() );      // MF# 04A  sit code (modified sit number)                              

         // send the string
         hr = WriteLine( lpStream, szBuffer );
      }
      else
      {
         hr = EMS_NOT_INITIALIZED;
      }
   }
   else
   {
      hr = EMS_INVALID_STREAM;
   }
   return hr;
}

EMS_RESULT
CEMSSit662A::GenerateSitBody( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      if ( m_bInitialized )
      {
         hr = _GenerateSitBodyLine1( lpStream );
         if ( EMS_OK == hr )
         {
            hr = _GenerateSitBodyLine2( lpStream );
         }
      }
      else
      {
         hr = EMS_NOT_INITIALIZED;
      }
   }
   else
   {
      hr = EMS_INVALID_STREAM;
   }
   return hr;
}

EMS_RESULT
CEMSSit662A::_GenerateSitBodyLine1( IEMSSeqStream *lpStream )
{
   EMS_RESULT     hr = EMS_OK;
   TCHAR          szBuffer[ 256 ];
   EMSTIMEFIELDS  startTimeFields;
   EMSTIMEFIELDS  endTimeFields;
   CEMSTime       timeTemp;
   int            nStartYear;
   int            nEndYear;
   double         dStartSeconds;
   double         dEndSeconds;

   // start time
   timeTemp.SetTime( m_data.startTime );
   timeTemp.GetTime( &startTimeFields );

   if ( startTimeFields.nYear >= 2000 )
   {
      nStartYear = startTimeFields.nYear - 2000;
   }
   else
   {
      nStartYear = startTimeFields.nYear - 1900;
   }
   dStartSeconds = (double)startTimeFields.nSecond + (double)startTimeFields.lNanosecond / 1000000000.0;
   if ( 60.00 <= dStartSeconds )
   {
	   // Assume that the original data is fine and that this is just a rounding error in the above calc
	   // In other words, simply pull it back and do not touch the minutes field
	   dStartSeconds = 59.99;
   }

   // end time
   timeTemp.SetTime( m_data.endTime );
   timeTemp.GetTime( &endTimeFields );

   if ( endTimeFields.nYear >= 2000 )
   {
      nEndYear = endTimeFields.nYear - 2000;
   }
   else
   {
      nEndYear = endTimeFields.nYear - 1900;
   }
   dEndSeconds = (double)endTimeFields.nSecond + (double)endTimeFields.lNanosecond / 1000000000.0;
   if ( 60.00 <= dEndSeconds )
   {
	   // Assume that the original data is fine and that this is just a rounding error in the above calc
	   // In other words, simply pull it back and do not touch the minutes field
   	   dEndSeconds = 59.99;
   }

   // create the string
   // MF# /06/602/603 = "/208/01 345 2300 00.00/01 345 2359 59.99"
   const TCHAR c_szSitDataLine1Fmt[] = TEXT("/%03d/%02d %03d %02d%02d %05.2lf/%02d %03d %02d%02d %05.2lf");

   _sntprintf( szBuffer, 256, c_szSitDataLine1Fmt,
      m_data.ulSatID,                  // MF# 06
         nStartYear,                   // MF# 602
         startTimeFields.nJulianDay,
         startTimeFields.nHour, 
         startTimeFields.nMinute, 
         dStartSeconds,
         nEndYear,                     // MF# 602
         endTimeFields.nJulianDay,
         endTimeFields.nHour, 
         endTimeFields.nMinute, 
         dEndSeconds
      );
   // send the string
   hr = WriteLine( lpStream, szBuffer );

   return hr;
}

EMS_RESULT
CEMSSit662A::_GenerateSitBodyLine2( IEMSSeqStream *lpStream )
{
   EMS_RESULT     hr = EMS_OK;
   TCHAR          szBuffer[ 256 ];
   WORD wDurationScheduled = m_data.wDurationScheduled <= 9999 ? m_data.wDurationScheduled : 9999;
   WORD wDurationActual = m_data.wDurationActual <= 9999 ? m_data.wDurationActual : 9999;
   WORD wGoodSignal = m_data.wGoodSignal <= 100 ? m_data.wGoodSignal : 100;
   WORD wBeaconIDs = m_data.wBeaconIDs <= 999 ? m_data.wBeaconIDs : 999;
   WORD wBeaconBursts = m_data.wBeaconBursts <= 9999 ? m_data.wBeaconBursts : 9999;
   WORD wSolutions = m_data.wSolutions <= 9999 ? m_data.wSolutions : 9999;
   WORD wAlarms = m_data.wAlarms <= 99 ? m_data.wAlarms : 99;
   WORD wWarnings = m_data.wWarnings <= 99 ? m_data.wWarnings : 99;

   // create the string
   // MF# /604/629/630/10B/636/601/634/635 = "/0060/0060/100/012/0765/0654/00/01"
   const TCHAR c_szSitDataLine2Fmt[] = TEXT("/%04d/%04d/%03d/%03d/%04d/%04d/%02d/%02d");

   _sntprintf( szBuffer, 256, c_szSitDataLine2Fmt,
      // "/006/IP/04 365 235959/0123/PL"
      wDurationScheduled,
      wDurationActual,
      wGoodSignal,
      wBeaconIDs,
      wBeaconBursts,
      wSolutions,
      wAlarms,
      wWarnings );
   // send the string
   hr = WriteLine( lpStream, szBuffer );

   return hr;
}

EMS_RESULT
CEMSSit662A::SetCollectionSummary( EMSCOLLECTIONSUMMARY* pData )
{
   EMS_RESULT hr = EMS_OK;

   if ( pData )
   {
      m_bInitialized = true;
      memcpy( &m_data, pData, sizeof( EMSCOLLECTIONSUMMARY ) );
   }
   else
   {
      hr = EMS_BAD_PARAM;
   }
   return hr;
}

EMS_RESULT
CEMSSit662A::GetCollectionSummary( EMSCOLLECTIONSUMMARY* pData )
{
	EMS_RESULT hr = EMS_OK;

	if( pData )
	{
		if( m_bInitialized )
		{
			memcpy( pData, &m_data, sizeof( EMSCOLLECTIONSUMMARY ) );
		}
		else
		{
			hr = EMS_NOT_INITIALIZED;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit662A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );

   if ( EMS_OK == hr )
   {
      // /MF06/MF602/MF603
      hr = _ParseCollectionSummaryLine1( lpTokenizer );

      if ( EMS_OK == hr )
      {
         // /MF604/MF629/MF630/MF10B/MF636/MF601/MF634/MF635
         hr = _ParseCollectionSummaryLine2( lpTokenizer );
      }

	  if( EMS_OK == hr )
	  {
		m_bInitialized = true;
	  }
   }
   return hr;
}

EMS_RESULT
CEMSSit662A::ParseSitHeader(  CEMSSitTokenizer*    lpTokenizer, 
                              BOOL                 bPeek )
{
   EMS_RESULT  hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int         nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( EMS_OK == hr )
   {
      CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A + eol

      if ( 4 == nFldCount )
      {
         int nNumber = 0;
         EMSSITCODE sitCode;

         // MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nNumber );

         if ( EMS_OK == hr )
         {
            SetSitNumber( nNumber );

            // MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nNumber );
         }
         if ( EMS_OK == hr )
         {
            SetSitDestination( nNumber );

            // MF04A Internal SIT number (aka SIT code)
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
         }

         if ( EMS_OK == hr )
         {
            SetSitCode( sitCode );

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

      if ( bPeek )
      {
         UnReadSitLine( lpTokenizer, sitField, nFldCount );
      }
   }
   else 
   {
      hr = EMS_BAD_PARAM;
   }
   return hr;
}

EMS_RESULT
CEMSSit662A::_ParseCollectionSummaryLine1( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = EMS_OK;

   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( EMS_OK == hr )
   {
	   // should find /MF06/MF602/MF603 + eol

	   if ( 4 == nFldCount )
	   {
		   CEMSSitMsgField   msgField;

		   hr = msgField.GetMF6( sitField[0].szText, reinterpret_cast<int*>(&m_data.ulSatID) );

      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF602( sitField[1].szText, &m_data.startTime );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF603( sitField[2].szText, &m_data.endTime );
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
   else
   {
      hr = EMS_BAD_PARAM;
   }
   return hr;
}
EMS_RESULT
CEMSSit662A::_ParseCollectionSummaryLine2( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = EMS_OK;

   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( EMS_OK == hr )
   {
	   // should find /MF604/MF629/MF630/MF10B/MF636/MF601/MF634/MF635 + eol

	   if ( 9 == nFldCount )
	   {
		   CEMSSitMsgField   msgField;

		   hr = msgField.GetMF604( sitField[0].szText, reinterpret_cast<int*>(&m_data.wDurationScheduled) );

      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF629( sitField[1].szText, reinterpret_cast<int*>(&m_data.wDurationActual) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF630( sitField[2].szText, reinterpret_cast<int*>(&m_data.wGoodSignal) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF10B( sitField[3].szText, reinterpret_cast<int*>(&m_data.wBeaconIDs) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF636( sitField[4].szText, reinterpret_cast<int*>(&m_data.wBeaconBursts) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF601( sitField[5].szText, reinterpret_cast<int*>(&m_data.wSolutions) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF634( sitField[6].szText, reinterpret_cast<int*>(&m_data.wAlarms) );
         }
      	if ( EMS_OK == hr )
         {
		      hr = msgField.GetMF635( sitField[7].szText, reinterpret_cast<int*>(&m_data.wWarnings) );
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
   else
   {
      hr = EMS_BAD_PARAM;
   }
   return hr;
}

