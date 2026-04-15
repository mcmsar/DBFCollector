/********************************************************************
*	Module:			emsit770.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit770A  Class
*						Data Report Message
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

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 June 3 rvw	start
	0.1 2003 Mar 6   Lguan	add parse code

********************************************************************/
#include "emsit770.h"
#include "sitfield.h"
#include "sgenMsgs.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s/%03d");
const TCHAR c_szSitBodyFmt[ ] = TEXT("/%s");
const int	c_nSitBodyFmtLen = 2; // space for the slash and a null terminator
const int	c_nAllocCount = 32;

CEMSSit770A::CEMSSit770A( )
{
	SetSitCode( 0x770A );

	m_nMsgCount = m_nAllocCount = 0;

	m_lpMsg = 0;

	SetMaxLinesPerRecord( EMS_LINES_PER_LOG_RECORD );
}

CEMSSit770A::~CEMSSit770A()
{
	Reset();
}

void CEMSSit770A::Reset( void )
{
	CEMSSitMessageBase::Reset();

	SetSitCode( 0x770A );

	if ( m_lpMsg )
	{
		delete [ ] m_lpMsg;
		m_lpMsg = 0;
	}
	m_nMsgCount = m_nAllocCount = 0;
}

EMS_RESULT CEMSSit770A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		if ( hr == EMS_OK )
		{
			for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nMsgCount ); i++ )
			{
				wsprintf( szBuffer, c_szSitBodyFmt, m_lpMsg[i].szText );

				hr = WriteLine( lpStream, szBuffer );
			}
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT CEMSSit770A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		wsprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
					GetSitDestination(),	GetSitCodeStr(), m_nMsgCount );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

LPCTSTR CEMSSit770A::GetMsg( int nIndex )
{
	LPTSTR lpszMsg = 0;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nMsgCount ) && m_lpMsg )
	{
		lpszMsg = (LPTSTR)&m_lpMsg[ nIndex ];
	}

	return (LPCSTR)lpszMsg;
}

int	CEMSSit770A::GetMaxAddMsgLen()
{
	return ( EMS_MAX_SIT_LINE_LENGTH - c_nSitBodyFmtLen );
}

EMS_RESULT CEMSSit770A::AddMsg( LPCTSTR lpcszMsg )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszMsg )
	{
		//
		// Ticket 7239 has been logged regarding this problem
		// Software should be able to split the data across
		// multiple SIT message lines.
		// Return an error in this case
		//
		long lLength = lstrlen( lpcszMsg );
		if ( lLength <= GetMaxAddMsgLen() )
		{
			if ( ( m_nMsgCount + 1 ) > m_nAllocCount )
			{
				int nNewCount = m_nMsgCount + c_nAllocCount;

				LPEMSSIT770AMSG lpNewData = new EMSSIT770AMSG[ nNewCount ];

				if ( lpNewData )
				{
					memset( lpNewData, 0, nNewCount * sizeof( EMSSIT770AMSG ) );

					if ( m_lpMsg )
					{
						memcpy( lpNewData, m_lpMsg, m_nMsgCount * sizeof( EMSSIT770AMSG ) );
						delete [ ] m_lpMsg;
					}
					m_lpMsg = lpNewData;
					m_nAllocCount = nNewCount;
				}
				else
					hr = EMS_NO_MEMORY;
			}

			if ( SUCCEEDED(hr) && m_lpMsg )
			{
				memcpy( &m_lpMsg[ m_nMsgCount++ ], lpcszMsg, sizeof(EMSSIT770AMSG) );
			}
		}
		else
		{
			hr = EMS_SITGEN_LINE_LIMIT_EXCEEDED;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT CEMSSit770A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		if ( m_nMsgCount > 0 )
		{
	 	    if ( m_lpMsg )
				delete m_lpMsg;

			m_lpMsg = new EMSSIT770AMSG[ m_nMsgCount ];

			for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nMsgCount ); i++ )
			{
				hr = _ParseMsgLine( lpTokenizer, i );
			}
		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}

	return hr;
}


EMS_RESULT CEMSSit770A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

		// should find /MF4/MF5/MF4A/MF606 eol

		if ( nFldCount == 5 )
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

				hr = msgField.GetMF606( sitField[3].szText, &m_nMsgCount );
			}

			if ( hr == EMS_OK )
			{
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


EMS_RESULT CEMSSit770A::_ParseMsgLine( CEMSSitTokenizer *lpTokenizer, int nIndex )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[ 256 ];
	int nCount = 0;

	hr = ReadSitLine( lpTokenizer, szBuffer, sizeof(szBuffer)/sizeof(szBuffer[0]), &nCount );

	if ( szBuffer )
	{
		if (szBuffer[0] == '/') 
		{
			lstrcpy( m_lpMsg[ nIndex ].szText, &szBuffer[1] );
		}
		else
		{
			lstrcpy( m_lpMsg[ nIndex ].szText, szBuffer );
		}

		
	}	
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;

}