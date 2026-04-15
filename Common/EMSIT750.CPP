/********************************************************************
*	Module:			emsit750.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit750A  Class
*						LUT Command
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

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 June 3 rvw	start

********************************************************************/
#include <stdio.h>

#include "sitfield.h"
#include "emsit750.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s/%03d");
const TCHAR c_szSitBodyFmt[ ] = TEXT("/%s");

CEMSSit750A::CEMSSit750A()
{
	SetSitCode( 0x750A );

	m_nCmdCount = 0;

	memset( m_lpszCmds, 0, sizeof( m_lpszCmds ) );
}

CEMSSit750A::~CEMSSit750A()
{
	Reset();
}

void CEMSSit750A::Reset( void )
{
	CEMSSitMessageBase::Reset();

	SetSitCode( 0x750A );

	for ( int i = 0; i < m_nCmdCount; i++ )
	{
		if ( m_lpszCmds[i] )
		{
			delete [ ] m_lpszCmds[i];

			m_lpszCmds[i] = 0;
		}
	}
	m_nCmdCount = 0;
}

int CEMSSit750A::GetCmdLine( int nIndex, LPTSTR lpszBuffer, int nMaxLength )
{
	int nLength = -1;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nCmdCount ) && lpszBuffer && 
						nMaxLength && m_lpszCmds[ nIndex ] )
	{
		lstrcpyn( lpszBuffer, m_lpszCmds[ nIndex ] , nMaxLength );

		nLength = lstrlen( lpszBuffer );
	}

	return nLength;
}

EMS_RESULT CEMSSit750A::SetCmdLine( int nIndex, LPCTSTR lpcszBuffer )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < EMS_SIT750A_MAX_COMMANDS ) && 
			lpcszBuffer && *lpcszBuffer )
	{
		if ( m_lpszCmds[ nIndex ] )
		{
			delete [ ] m_lpszCmds[ nIndex ];
			m_lpszCmds[ nIndex ] = 0;
		}
		m_lpszCmds[ nIndex ] = new TCHAR [ lstrlen( lpcszBuffer ) + 1 ]; 

		if ( m_lpszCmds[ nIndex ] )
		{
			lstrcpy( m_lpszCmds[ nIndex ] , lpcszBuffer );
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit750A::AddCmdLine( LPCTSTR lpcszBuffer )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcszBuffer && *lpcszBuffer )
	{
		if ( m_nCmdCount < EMS_SIT750A_MAX_COMMANDS )
		{
			hr = SetCmdLine( m_nCmdCount, lpcszBuffer );
			
			if ( hr == EMS_OK )
				m_nCmdCount++;
		}
		else
			hr = EMS_LINE_LIMIT_EXCEEDED;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit750A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nCmdCount ); i++ )
		{
			wsprintf( szBuffer, c_szSitBodyFmt, m_lpszCmds[i] ? m_lpszCmds[i] : TEXT("") );

			hr = WriteLine( lpStream, szBuffer );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit750A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		wsprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr(), m_nCmdCount );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit750A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		if ( m_nCmdCount > 0 )
		{
			for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nCmdCount ); i++ )
			{
				hr = _ParseCmdLine( lpTokenizer, i );
			}
		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSit750A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

				hr = msgField.GetMF606( sitField[3].szText, &m_nCmdCount );
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

EMS_RESULT CEMSSit750A::_ParseCmdLine( CEMSSitTokenizer *lpTokenizer, int nIndex )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[ 256 ];
	int nCount = 0;

	hr = ReadSitLine( lpTokenizer, szBuffer, sizeof(szBuffer)/sizeof(szBuffer[0]), &nCount );

	if ( hr == EMS_OK )
	{
		if ( m_lpszCmds[ nIndex ] )
		{
			delete [ ] m_lpszCmds[ nIndex ];
			m_lpszCmds[ nIndex ] = 0;
		}

		if ( nCount)
		{
			m_lpszCmds[ nIndex ] = new TCHAR[ nCount + 1 ];

			if ( m_lpszCmds[ nIndex ] )
				lstrcpy( m_lpszCmds[ nIndex ], szBuffer );
			else
				hr = EMS_NO_MEMORY;
		}
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}
