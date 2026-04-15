/********************************************************************
*       Module:                 emsit270.cpp
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Implementation of CEMSSit270A Class
*                              MetOps Manoeuvre schedule notification
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

        0.0     2002 Dec 12             fjp     start

********************************************************************/

#include <stdio.h>
#include <tchar.h>
#include "emsit270.h"
#include "sitfield.h"

// MF# /04/05/04A = "/270/1234/270A"
const TCHAR c_szSitHdrFmt[]               = TEXT("/%03d/%04d/%s");

// MF# /06/660/661/662/663 = "/006/IP/04 365 235959/0123/PL"
const TCHAR c_szSitSatManoeuvreMsgFmt[]   = TEXT("/%03d/%s/%02d %03d %02d%02d%02d/%04d/%s");

CEMSSit270A::CEMSSit270A() :
   m_bInitialized( false )
{
   SetSitNumber( 270 );
   SetSitCode( 0x270A );
   memset( &m_data, 0, sizeof( m_data ) );
}

CEMSSit270A::~CEMSSit270A()
{
}

void
CEMSSit270A::Reset( void )
{
   CEMSSitMessageBase::Reset();

   SetSitNumber( 270 );
   SetSitCode( 0x270A );
   memset( &m_data, 0, sizeof( m_data ) );
   m_bInitialized = false;
}

EMS_RESULT
CEMSSit270A::GenerateSitHeader( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      if ( m_bInitialized )
      {
         TCHAR szBuffer[ 256 ];

         // c_szSitHdrFmt = "/%03d/%04d/%s"
         _sntprintf( szBuffer, 256, c_szSitHdrFmt,
            GetSitNumber(),         // MF# 04   sit number
            GetSitDestination(),    // MF# 05   sit destination
            GetSitCodeStr() );      // MF# 04A  sit code (modified sit number)                              

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
CEMSSit270A::GenerateSitBody( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      if ( m_bInitialized )
      {
         TCHAR          szBuffer[ 256 ];
         EMSTIMEFIELDS  timeFields;
         CEMSTime       timeTemp;
         int            nYear;
         CEMSSitMsgField   msgField;

         timeTemp.SetTime( m_data.startTime );
         timeTemp.GetTime( &timeFields );

         if ( timeFields.nYear >= 2000 )
         {
            nYear = timeFields.nYear - 2000;
         }
         else
         {
            nYear = timeFields.nYear - 1900;
         }
         // c_szSitSatManoeuvreMsgFmt = "/%03d/%s/%02d %03d %02d%02d%02d/%04d/%s"
         _sntprintf( szBuffer, 256, c_szSitSatManoeuvreMsgFmt,
            // "/006/IP/04 365 235959/0123/PL"
            m_data.ulSatID,                                 // MF# 06
				 msgField.TextMF660( m_data.type ),
               nYear,                                       // MF# 661
               timeFields.nJulianDay,
               timeFields.nHour, 
               timeFields.nMinute, 
               timeFields.nSecond,
            m_data.wDuration,                               // MF# 662
				 msgField.TextMF663( m_data.status ) );

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
CEMSSit270A::GetManoeuvreData( EMSMANOEUVREDATA* pData )
{
   EMS_RESULT hr = EMS_OK;

   if ( pData )
   {
      if ( m_bInitialized )
      {
         memcpy( pData, &m_data, sizeof( EMSMANOEUVREDATA ) );
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
CEMSSit270A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = EMS_BAD_PARAM;
   
   if ( lpTokenizer )
   {
      hr = ParseSitHeader( lpTokenizer );

      if ( EMS_OK == hr )
      {
         hr = _ParseManoeuvreDataLine( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         m_bInitialized = true;
      }
   }
   return hr;
}

EMS_RESULT
CEMSSit270A::ParseSitHeader(   CEMSSitTokenizer*    lpTokenizer, 
                              BOOL                 bPeek )
{
   EMS_RESULT  hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int         nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

   if ( EMS_OK == hr )
   {
      // should find /MF#04/MF#05/MF#04A/
      if ( nFldCount == 4 )
      {
         CEMSSitMsgField   msgField;

         int nSitNumber;
         hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );
         SetSitNumber( nSitNumber );

         if ( EMS_OK == hr )
         {
            int nSitDestination;
            hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
            SetSitDestination( nSitDestination );
         }
         if ( EMS_OK == hr )
         {
            EMSSITCODE sitCode;
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
            SetSitCode( sitCode );
         }
         if ( !msgField.IsEOL( sitField[3].szText ) )
         {
            hr = EMS_SIT_SYNTAX_EOL;
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
CEMSSit270A::_ParseManoeuvreDataLine( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT     hr = EMS_OK;
   EMSSITFIELD    sitField[ 16 ];
   int            nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

   if ( EMS_OK == hr )
   {
      // should find /MF#06/MF#660/MF#661/MF#662/MF#663
      if ( nFldCount == 6 )
      {
         CEMSSitMsgField   msgField;
         EMSMANOEUVREDATA  data;

         hr = msgField.GetMF6( sitField[0].szText, (int*)(&(data.ulSatID)) );
         if ( EMS_OK == hr )
         {
            hr = msgField.GetMF660( sitField[1].szText, &(data.type) );
         }
         if ( EMS_OK == hr )
         {
            hr = msgField.GetMF661( sitField[2].szText, &(data.startTime) );
         }
         if ( EMS_OK == hr )
         {
            hr = msgField.GetMF662( sitField[3].szText, (int*)&(data.wDuration) );
         }
         if ( EMS_OK == hr )
         {
            hr = msgField.GetMF663( sitField[4].szText, &(data.status) );
         }
         if ( !msgField.IsEOL( sitField[5].szText ) )
         {
            hr = EMS_SIT_SYNTAX_EOL;
         }
         if ( EMS_OK == hr )
         {
            memcpy( &m_data, &data, sizeof( EMSMANOEUVREDATA ) );
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

