/********************************************************************
*  Module:        emsit605.cpp
*  Process ID:
*  S/W Platforms:
*  H/W Platforms:
*  Compiler:
*  Description:   Description of CEMSSit605Base Class &&
*                 CEMSSit605, CEMSSit605A, CEMSSit605B, 
*                 CEMSSit605C, CEMSSit605D
*                 LUT Messages
*  Usage:
*  Entry Point:
*  Input Files:
*  Output Files:
*  Comments:   
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

/*******************************************************************

  Revision Record

   Rev   Date        Auth  Changes
   ===   ====        ====  =======

   0.0   2002 June 3 rvw   start

********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include <array.h>
#include "emsit605.h"
#include "sitfield.h"
#include "messages.h"

const int   c_nAllocCount  = 32;
const TCHAR c_szSitHdrAFmt[ ] = TEXT("/%03d/%04d/%s/%03d");
const TCHAR c_szSitHdrBCDFmt[ ] = TEXT("/%03d/%04d/%s");
const TCHAR c_szSitBodyLine1Fmt[ ] = TEXT("/%03ld/%05ld");
const TCHAR c_szSitBodyLine2AFmt[ ] = TEXT("/%-2s/%-16s/%-8s");
const TCHAR c_szSitBodyLine2BCFmt[ ] = TEXT("/%-16s");
const TCHAR c_szSitBodyLine3BCFmt[ ] = TEXT("/%s");
const TCHAR c_szSitBodyLine2EFmt[ ] = TEXT("/%-15s/%-1c/%-1c");


CEMSSit605A::CEMSSit605A()
{
   SetSitNumber( 605 );
   SetSitCode( 0x605A );
   m_nLineCount = m_nAllocCount = 0;
   m_lpLine = 0;
}

CEMSSit605A::~CEMSSit605A()
{
   Reset();
}

void CEMSSit605A::Reset( void )
{
   // SitCode & SitNumber should survive a reset
   int			nSitNumber = GetSitNumber();
   EMSSITCODE	sitCode = GetSitCode();

   CEMSSitMessageBase::Reset();

   SetSitNumber( nSitNumber ? nSitNumber : 605 );
   SetSitCode( sitCode ? sitCode : 0x605A );

   if ( m_lpLine )
   {
      delete [ ] m_lpLine;
      m_lpLine = 0;
   }
   m_nLineCount = m_nAllocCount = 0;
}

EMS_RESULT CEMSSit605A::GenerateSitBody( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      TCHAR szBuffer[ 256 ];

      sprintf( szBuffer, c_szSitBodyLine1Fmt, GetSatelliteID(), GetPassID() );

      hr = WriteLine( lpStream, szBuffer );

      if ( hr == EMS_OK )
      {
         for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nLineCount ); i++ )
         {
            sprintf( szBuffer, c_szSitBodyLine2AFmt, m_lpLine[i].szType,
                  m_lpLine[i].szSource, m_lpLine[i].szStatus );

            hr = WriteLine( lpStream, szBuffer );
         }
      }

   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      TCHAR szBuffer[ 256 ];
      
      sprintf( szBuffer, c_szSitHdrAFmt, GetSitNumber(), 
               GetSitDestination(), GetSitCodeStr(), m_nLineCount );

      hr = WriteLine( lpStream, szBuffer );
   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605A::GetStatus( LPEMSSIT605ASTATUS lpStatus, int nIndex )  
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStatus && ( nIndex >= 0 ) && ( nIndex < m_nLineCount ) )
   {
      memcpy( lpStatus, &m_lpLine[ nIndex ], sizeof( EMSSIT605ASTATUS ) );
   }
   else
      hr = EMS_BAD_PARAM;

   return hr;
}
 
EMS_RESULT CEMSSit605A::AddStatus( LPEMSSIT605ASTATUS lpStatus )  
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStatus )
   {
      if ( ( m_nLineCount + 1 ) > m_nAllocCount )
      {
         int nNewCount = m_nLineCount + c_nAllocCount;

         LPEMSSIT605ASTATUS lpNewData = new EMSSIT605ASTATUS[ nNewCount ];

         if ( lpNewData )
         {
            memset( lpNewData, 0, nNewCount * sizeof( EMSSIT605ASTATUS ) );

            if ( m_lpLine )
            {
               memcpy( lpNewData, m_lpLine, m_nLineCount * sizeof( EMSSIT605ASTATUS ) );
               delete [ ] m_lpLine;
            }
            m_lpLine = lpNewData;
            m_nAllocCount = nNewCount;
         }
         else
            hr = EMS_NO_MEMORY;
      }
      if ( m_lpLine )
         memcpy( &m_lpLine[ m_nLineCount++ ], lpStatus, sizeof(EMSSIT605ASTATUS) );
   }
   else
      hr = EMS_BAD_PARAM;

   return hr;
}

EMS_RESULT
CEMSSit605A::ParseSitMessage( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );
   
   if ( EMS_OK == hr )
   {
      hr = _ParseSatInfoLine( lpTokenizer );

      if ( EMS_OK == hr )
      {
         if ( GetLineCount() > 0 )
         {
            _AllocLines( GetLineCount() );

            LPEMSSIT605ASTATUS lpLine = 0;

            for ( int ii = 0; (ii < GetLineCount()) && (EMS_OK == hr); ii++ )
            {
               lpLine = _GetLinePtr( ii );

               if ( lpLine )
               {
                  hr = _ParseStatusInfoLine( lpTokenizer, lpLine );
               }
            }
         }
         else
         {
            hr = EMS_SIT_SYNTAX_ERROR;
         }
      }
   }
   return hr;
}

EMS_RESULT
CEMSSit605A::ParseSitHeader( CEMSSitTokenizer* lpTokenizer, BOOL bPeek )
{
   EMS_RESULT hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( hr == EMS_OK )
   {
      CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A/MF606 + eol

      if ( 5 == nFldCount )
      {
         int nNumber = 0;
         EMSSITCODE sitCode;

         // MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nNumber );

         if ( hr == EMS_OK )
         {
            SetSitNumber( nNumber );

            // MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nNumber );
         }
         if ( hr == EMS_OK )
         {
            SetSitDestination( nNumber );

            // MF04A Internal SIT number (aka SIT code)
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
         }

         if ( hr == EMS_OK )
         {
            SetSitCode( sitCode );

            // MF606 Total number of data entries
            hr = msgField.GetMF606( sitField[3].szText, &m_nLineCount );
         }
         if ( hr == EMS_OK )
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
CEMSSit605A::_ParseSatInfoLine( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer )
   {
      EMSSITFIELD sitField[ 3 ];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF06A/MF07A + eol

         if ( 3 == nFldCount )
         {
            int nNumber = 0;

            // MF06A SatID
            hr = msgField.GetMF6A( sitField[0].szText, &nNumber );

            if ( EMS_OK == hr )
            {
               SetSatelliteID( nNumber );

               hr = msgField.GetMF7A( sitField[1].szText, &nNumber );
            }
            if ( EMS_OK == hr )
            {
               SetPassID( nNumber );

				   if ( !msgField.IsEOL( sitField[2].szText ) )
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
CEMSSit605A::_ParseStatusInfoLine(  CEMSSitTokenizer*    lpTokenizer, 
                                    LPEMSSIT605ASTATUS   lpLine )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && lpLine )
   {
      EMSSITFIELD sitField[4];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF640/MF641/MF612 + eol

         if ( 4 == nFldCount )
         {
            hr = msgField.GetMF640( sitField[0].szText, lpLine->szType, ARRAY_SIZE(lpLine->szType) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF641( sitField[1].szText, lpLine->szSource, ARRAY_SIZE(lpLine->szSource) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF612( sitField[2].szText, lpLine->szStatus, ARRAY_SIZE(lpLine->szStatus) );
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

int
CEMSSit605A::_AllocLines( int nCount )
{
   if ( nCount > EMSSIT605A_MAX_MSGS )
   {
      nCount = EMSSIT605A_MAX_MSGS;
   }

   m_lpLine = new EMSSIT605ASTATUS[nCount];

   if ( m_lpLine )
   {
      memset( m_lpLine, 0, sizeof(EMSSIT605ASTATUS) * nCount );

      m_nAllocCount = nCount;

      SetLineCount( m_nAllocCount );
   }
   return m_nAllocCount;
}

LPEMSSIT605ASTATUS
CEMSSit605A::_GetLinePtr( int nIndex )
{
   LPEMSSIT605ASTATUS lpLine = 0;

   if ( m_lpLine && ( nIndex >= 0 ) && ( nIndex < GetLineCount() ) )
   {
      lpLine = &m_lpLine[nIndex];
   }
   return lpLine;
}


CEMSSit605B::CEMSSit605B()
{
   SetSitCode( 0x605B );

   memset( m_szSource, 0, sizeof( m_szSource ) );
// memset( m_szMsg, 0, sizeof( m_szMsg ) );
   m_lpszMsg = 0;
}

CEMSSit605B::~CEMSSit605B()
{
   if ( m_lpszMsg )
   {
      delete [ ] m_lpszMsg;
      m_lpszMsg = 0;
   }
}

void CEMSSit605B::Reset( void )
{
   // SitCode & SitNumber should survive a reset
   int			nSitNumber = GetSitNumber();
   EMSSITCODE	sitCode = GetSitCode();

   CEMSSitMessageBase::Reset();

   SetSitCode( sitCode ? sitCode : 0x605B );
   SetSitNumber( nSitNumber ? nSitNumber : 605 );

   memset( m_szSource, 0, sizeof( m_szSource ) );
// memset( m_szMsg, 0, sizeof( m_szMsg ) );

   if ( m_lpszMsg )
   {
      delete [ ] m_lpszMsg;
      m_lpszMsg = 0;
   }
}

EMS_RESULT CEMSSit605B::GenerateSitBody( IEMSSeqStream *lpStream )
{
   EMS_RESULT hr = EMS_OK;
   BOOL bEndLine = FALSE;

   if ( lpStream )
   {
      TCHAR szBuffer[ 1024 ], *lpszCpos=0;

      wsprintf( szBuffer, c_szSitBodyLine1Fmt, GetSatelliteID(), GetPassID() );

      hr = WriteLine( lpStream, szBuffer );

      if ( hr == EMS_OK )
      {
         wsprintf( szBuffer, c_szSitBodyLine2BCFmt, m_szSource );

         hr = WriteLine( lpStream, szBuffer );
      }

      wsprintf( szBuffer, c_szSitBodyLine3BCFmt, ( m_lpszMsg ) ? m_lpszMsg : "" );

      lpszCpos = szBuffer;

      while ( lpszCpos && *lpszCpos && !bEndLine)
      {
         TCHAR szLine[70] = "";

         int nLength = lstrlen( lpszCpos );

         // First, see if there is a natural break like a space.
         if ( nLength > 69 )
         {
            while ( ((nLength > 69) || (lpszCpos[ nLength-1 ] != ' ')) && nLength )
            {
               nLength -= 1;
            }

            if( !nLength )    // no natural break found.
               nLength = 69;

            _tcsncpy( szLine, lpszCpos, nLength );

         }
         else
         {
            _tcscpy( szLine, lpszCpos );
            bEndLine = FALSE;
         }


         hr = WriteLine( lpStream, szLine );

         lpszCpos += nLength;
      }
   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605B::GenerateSitHeader( IEMSSeqStream *lpStream)
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      TCHAR szBuffer[ 256 ];
      
      wsprintf( szBuffer, c_szSitHdrBCDFmt, GetSitNumber(), 
                        GetSitDestination(), GetSitCodeStr() );

      hr = WriteLine( lpStream, szBuffer );
   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

void CEMSSit605B::SetSource( LPCSTR lpszSource )
{
   if ( lpszSource )
   {
      lstrcpyn( m_szSource, lpszSource , EMSSIT605_SOURCE_LEN );
   }
   else
      memset( m_szSource, 0, sizeof( m_szSource ) );
}

void CEMSSit605B::SetMsg( LPCSTR lpszMsg )
{
   if ( m_lpszMsg )
   {
      delete [ ] m_lpszMsg;
      m_lpszMsg = 0;
   }

   if ( lpszMsg && *lpszMsg )
   {
      m_lpszMsg = new TCHAR[ lstrlen( lpszMsg ) + 1 ];

      if ( m_lpszMsg )
      {
         TCHAR *lpcSlash = 0;

         lstrcpy( m_lpszMsg, lpszMsg );

         // change any '/' to '\' to prevent SIT parse problems

         lpcSlash = _tcschr( m_lpszMsg, '/' );

         while ( lpcSlash && *lpcSlash )
         {
            *lpcSlash = '\\';

            lpcSlash = _tcschr( lpcSlash, '/' );
         }
      }
   }
}

EMS_RESULT
CEMSSit605B::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );
   
   if ( EMS_OK == hr )
   {
      hr = _ParseSatInfoLine( lpTokenizer );

      if ( EMS_OK == hr )
      {
         hr = _ParseSourceNameLine( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         hr = _ParseMessageTextLine_s( lpTokenizer );
      }
   }
   return hr;
}

EMS_RESULT
CEMSSit605B::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
   EMS_RESULT hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( hr == EMS_OK )
   {
      CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A + eol

      if ( 4 == nFldCount )
      {
         int nNumber = 0;
         EMSSITCODE sitCode;

         // MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nNumber );

         if ( hr == EMS_OK )
         {
            SetSitNumber( nNumber );

            // MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nNumber );
         }
         if ( hr == EMS_OK )
         {
            SetSitDestination( nNumber );

            // MF04A Internal SIT number (aka SIT code)
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
         }

         if ( hr == EMS_OK )
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
      hr = EMS_BAD_PARAM;

   return hr;
}

EMS_RESULT
CEMSSit605B::_ParseSourceNameLine( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer )
   {
      EMSSITFIELD sitField[2];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF641 + eol

         if ( 2 == nFldCount )
         {
            hr = msgField.GetMF641( sitField[0].szText, m_szSource, ARRAY_SIZE(m_szSource) );

            if ( EMS_OK == hr )
            {
			      if ( !msgField.IsEOL( sitField[1].szText ) )
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
CEMSSit605B::_ParseMessageTextLine_s( CEMSSitTokenizer* lpTokenizer )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer )
   {
      EMSSITFIELD sitField[2];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF651 + eol

         if ( 2 == nFldCount )
         {
            if ( m_lpszMsg )
            {
               delete [] m_lpszMsg;
               m_lpszMsg = 0;
            }

            m_lpszMsg = new TCHAR[EMS_MAX_SIT_LINE_LENGTH];   // even steven: take away the '/' but leave room for the '\0'

            memset( m_lpszMsg, 0, EMS_MAX_SIT_LINE_LENGTH * sizeof(TCHAR) );

            if ( 0 != _tcsncpy( m_lpszMsg, &(sitField[0].szText[1]), EMS_MAX_SIT_LINE_LENGTH - 1 ) )
            {
   			   if ( !msgField.IsEOL( sitField[1].szText ) )
               {
   				   hr = EMS_SIT_SYNTAX_EOL;
               }

               if ( EMS_OK == hr )
               {
                  // get the rest of the MF (if it's spread over multiple lines)

                  for ( int ii = 2; ii < 12; ii++ )
                  {
                     hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

                     if ( EMS_OK == hr )
                     {
                        if (  ( '/' == sitField[0].szText[0] ) // next line - next MF, put it back!
                           || ( 2 != nFldCount )               // unexpected, get out and pass it on
                           )
                        {
                           UnReadSitLine( lpTokenizer, sitField, nFldCount );
                           break;
                        }
                        else                                   // continuation of MF651
                        {
                           TCHAR* ptszTemp = new TCHAR[EMS_MAX_SIT_LINE_LENGTH * ii];

                           _tcscpy( ptszTemp, m_lpszMsg );

                           delete [] m_lpszMsg;

                           m_lpszMsg = ptszTemp;

                           _tcsncat( m_lpszMsg, sitField[0].szText, EMS_MAX_SIT_LINE_LENGTH );
                        }
                     }
                  }
               }
            }
            else
            {
               hr = EMS_GENERAL_UNKNOWN;
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


CEMSSit605C::CEMSSit605C()
{
   SetSitCode( 0x605C );
}

CEMSSit605C::~CEMSSit605C()
{
}

void CEMSSit605C::Reset( void )
{
   // SitCode & SitNumber should survive a reset
   EMSSITCODE	sitCode = GetSitCode();
   int			nSitNumber = GetSitNumber();

   CEMSSit605B::Reset();

   SetSitCode( sitCode ? sitCode : 0x605C );
   SetSitNumber( nSitNumber ? nSitNumber : 605 );
}

CEMSSit605D::CEMSSit605D()
{
   SetSitCode( 0x605D );
}

CEMSSit605D::~CEMSSit605D()
{
}

void CEMSSit605D::Reset( void )
{
   // SitCode & SitNumber should survive a reset
   EMSSITCODE	sitCode = GetSitCode();
   int			nSitNumber = GetSitNumber();

   CEMSSitMessageBase::Reset();

   SetSitCode( sitCode ? sitCode : 0x605D );
   SetSitNumber( nSitNumber ? nSitNumber : 605 );
}

EMS_RESULT CEMSSit605D::GenerateSitBody( IEMSSeqStream *lpStream )
{
   return ( lpStream ) ? EMS_OK : EMS_INVALID_STREAM;
}

EMS_RESULT CEMSSit605D::GenerateSitHeader( IEMSSeqStream *lpStream)
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      TCHAR szBuffer[ 256 ];
      
      wsprintf( szBuffer, c_szSitHdrBCDFmt, GetSitNumber(), 
                        GetSitDestination(), GetSitCodeStr() );

      hr = WriteLine( lpStream, szBuffer );
   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605D::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   return ParseSitHeader( lpTokenizer );
}

EMS_RESULT CEMSSit605D::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
   EMS_RESULT hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;
   EMSSITCODE sitCode;

   hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

   if ( hr == EMS_OK )
   {
      CEMSSitMsgField msgField;
      int nCount = 0;

      // should find /MF4/MF5/MF4A eol

      if ( nFldCount == 4 )
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
               
            if ( !msgField.IsEOL( sitField[3].szText ) )
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

CEMSSit605E::CEMSSit605E()
{
   SetSitNumber( 605 );
   SetSitCode( 0x605E );
   m_nLineCount = m_nAllocCount = 0;
   m_pLine = 0;
}

CEMSSit605E::~CEMSSit605E()
{
   Reset();
}

void CEMSSit605E::Reset( void )
{
   // SitCode & SitNumber should survive a reset
   int			nSitNumber = GetSitNumber();
   EMSSITCODE	sitCode = GetSitCode();

   CEMSSitMessageBase::Reset();

   SetSitNumber( nSitNumber ? nSitNumber : 605 );
   SetSitCode( sitCode ? sitCode : 0x605E );

   if ( m_pLine )
   {
      delete [ ] m_pLine;
      m_pLine = 0;
   }
   m_nLineCount = m_nAllocCount = 0;
}

EMS_RESULT CEMSSit605E::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nLineCount ); i++ )
		{
			sprintf( szBuffer, c_szSitBodyLine2EFmt, m_pLine[i].szIPAddress,
				  m_pLine[i].cState, m_pLine[i].cConnType );

			hr = WriteLine( lpStream, szBuffer );
		}

	}
	else
		hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605E::GenerateSitHeader( IEMSSeqStream *lpStream)
{
   EMS_RESULT hr = EMS_OK;

   if ( lpStream )
   {
      TCHAR szBuffer[ 256 ];
      
      sprintf( szBuffer, c_szSitHdrAFmt, GetSitNumber(), 
               GetSitDestination(), GetSitCodeStr(), m_nLineCount );

      hr = WriteLine( lpStream, szBuffer );
   }
   else
      hr = EMS_INVALID_STREAM;

   return hr;
}

EMS_RESULT CEMSSit605E::GetStatus( PEMSIPSTATUS pStatus, int nIndex )  
{
   EMS_RESULT hr = EMS_OK;

   if ( pStatus && ( nIndex >= 0 ) && ( nIndex < m_nLineCount ) )
   {
      memcpy( pStatus, &m_pLine[ nIndex ], sizeof( EMSIPSTATUS ) );
   }
   else
      hr = EMS_BAD_PARAM;

   return hr;
}
 
EMS_RESULT CEMSSit605E::AddStatus( PEMSIPSTATUS pStatus )  
{
   EMS_RESULT hr = EMS_OK;

   if ( pStatus )
   {
      if ( ( m_nLineCount + 1 ) > m_nAllocCount )
      {
         int nNewCount = m_nLineCount + c_nAllocCount;

         PEMSIPSTATUS pNewData = new EMSIPSTATUS[ nNewCount ];

         if ( pNewData )
         {
            memset( pNewData, 0, nNewCount * sizeof( EMSIPSTATUS ) );

            if ( m_pLine )
            {
               memcpy( pNewData, m_pLine, m_nLineCount * sizeof( EMSIPSTATUS ) );
               delete [ ] m_pLine;
            }
            m_pLine = pNewData;
            m_nAllocCount = nNewCount;
         }
         else
            hr = EMS_NO_MEMORY;
      }
      if ( m_pLine )
         memcpy( &m_pLine[ m_nLineCount++ ], pStatus, sizeof(EMSIPSTATUS) );
   }
   else
      hr = EMS_BAD_PARAM;

   return hr;
}

EMS_RESULT
CEMSSit605E::ParseSitMessage( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );
   
	if ( EMS_OK == hr )
	{
		if ( GetLineCount() > 0 )
		{
			_AllocLines( GetLineCount() );

			PEMSIPSTATUS pLine = 0;

			for ( int ii = 0; (ii < GetLineCount()) && (EMS_OK == hr); ii++ )
			{
			   pLine = _GetLinePtr( ii );

			   if ( pLine )
			   {
				  hr = _ParseStatusInfoLine( lpTokenizer, pLine );
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
CEMSSit605E::ParseSitHeader( CEMSSitTokenizer* lpTokenizer, BOOL bPeek )
{
   EMS_RESULT hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( hr == EMS_OK )
   {
      CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A/MF606 + eol

      if ( 5 == nFldCount )
      {
         int nNumber = 0;
         EMSSITCODE sitCode;

         // MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nNumber );

         if ( hr == EMS_OK )
         {
            SetSitNumber( nNumber );

            // MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nNumber );
         }
         if ( hr == EMS_OK )
         {
            SetSitDestination( nNumber );

            // MF04A Internal SIT number (aka SIT code)
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
         }

         if ( hr == EMS_OK )
         {
            SetSitCode( sitCode );

            // MF606 Total number of data entries
            hr = msgField.GetMF606( sitField[3].szText, &m_nLineCount );
         }
         if ( hr == EMS_OK )
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
CEMSSit605E::_ParseStatusInfoLine(  CEMSSitTokenizer*    lpTokenizer, 
                                    PEMSIPSTATUS   pLine )
{
   EMS_RESULT hr = EMS_OK;

   if ( lpTokenizer && pLine )
   {
      EMSSITFIELD sitField[4];
      int         nFldCount = 0;

      hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

      if ( EMS_OK == hr )
      {
         CEMSSitMsgField msgField;

         // /MF677/MF678/MF679 + eol

         if ( 4 == nFldCount )
         {
            hr = msgField.GetMF677( sitField[0].szText, pLine->szIPAddress, ARRAY_SIZE(pLine->szIPAddress) );

            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF678( sitField[1].szText, &(pLine->cState) );
            }
            if ( EMS_OK == hr )
            {
               hr = msgField.GetMF679( sitField[2].szText, &(pLine->cConnType) );
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

int
CEMSSit605E::_AllocLines( int nCount )
{
   if ( nCount > EMSSIT605A_MAX_MSGS )
   {
      nCount = EMSSIT605A_MAX_MSGS;
   }

   m_pLine = new EMSIPSTATUS[nCount];

   if ( m_pLine )
   {
      memset( m_pLine, 0, sizeof(EMSIPSTATUS) * nCount );

      m_nAllocCount = nCount;

      SetLineCount( m_nAllocCount );
   }
   return m_nAllocCount;
}

PEMSIPSTATUS
CEMSSit605E::_GetLinePtr( int nIndex )
{
   PEMSIPSTATUS pLine = 0;

   if ( m_pLine && ( nIndex >= 0 ) && ( nIndex < GetLineCount() ) )
   {
      pLine = &m_pLine[nIndex];
   }
   return pLine;
}