/********************************************************************
*	Module:			emsit970.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit970
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

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5	rvw	start

********************************************************************/
#include <stdio.h>
#include <tchar.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit970.h"

const TCHAR c_szSitHdr1Fmt[ ] = TEXT("/%03d/%04d");
const TCHAR c_szSitHdr2Fmt[ ] = TEXT("/%03d/%05d");
const TCHAR c_szSitBody1Fmt[ ] = TEXT("/%s/%c");
const TCHAR c_szSitBody2Fmt[ ] = TEXT("/%s");

CEMSSit970::CEMSSit970()
{
	m_cMsgType = 'I';
	m_nSatID = 0;
	m_nPass = 1;
	m_lpszMsgSource = 0;
	m_lpszMsgText = 0;

	SetSitNumber(970);
}

CEMSSit970::~CEMSSit970()
{
	Reset();
}

void CEMSSit970::Reset( void )
{
	SetSitNumber(970);
	_ResetStrings();
}

void CEMSSit970::_ResetStrings( void )
{
	if ( m_lpszMsgSource )
	{
		delete [ ] m_lpszMsgSource;
		m_lpszMsgSource = 0;
	}

	if ( m_lpszMsgText )
	{
		delete [ ] m_lpszMsgText;
		m_lpszMsgText = 0;
	}
}

EMS_RESULT CEMSSit970::SetMsgSource( LPCTSTR lpcszSource )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpszMsgSource )
	{
		delete [ ] m_lpszMsgSource;
		m_lpszMsgSource = 0;
	}

	if ( lpcszSource && *lpcszSource )
	{
		m_lpszMsgSource = new TCHAR[ lstrlen( lpcszSource ) + 1 ];

		if ( m_lpszMsgSource )
			lstrcpy( m_lpszMsgSource, lpcszSource );
	}
	return hr;
}


EMS_RESULT CEMSSit970::SetMsgText( LPCTSTR lpcszText )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpszMsgText )
	{
		delete [ ] m_lpszMsgText;
		m_lpszMsgText = 0;
	}

	if ( lpcszText && *lpcszText )
	{
		m_lpszMsgText = new TCHAR[ lstrlen( lpcszText ) + 1 ];

		if ( m_lpszMsgText )
			lstrcpy( m_lpszMsgText, lpcszText );
	}
	return hr;
}


EMS_RESULT CEMSSit970::SetAdvisoryMessage( LPCTSTR lpcszSource, 
												TCHAR cMsgType, LPCTSTR lpcszMsgText )
{
	EMS_RESULT hr = EMS_OK;

	_ResetStrings();

	m_cMsgType = cMsgType;

	if ( lpcszSource && *lpcszSource )
	{
		m_lpszMsgSource = new TCHAR[ lstrlen( lpcszSource ) + 1 ];

		if ( m_lpszMsgSource )
			lstrcpy( m_lpszMsgSource, lpcszSource );
	}

	if ( lpcszMsgText && *lpcszMsgText )
	{
		m_lpszMsgText = new TCHAR[ lstrlen( lpcszMsgText ) + 1 ];

		if ( m_lpszMsgText )
			lstrcpy( m_lpszMsgText, lpcszMsgText );
	}

	return hr;
}

EMS_RESULT CEMSSit970::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szLine[ 256 ], *lpBlank;
		int nCPos = 0;
		
		wsprintf( szBuffer, c_szSitBody1Fmt, m_lpszMsgSource, m_cMsgType );

		hr = WriteLine( lpStream, szBuffer );

		if ( m_lpszMsgText )
		{
			int nMaxLength = lstrlen( m_lpszMsgText );
			TCHAR cSaveChar;

		 	while ( nCPos < nMaxLength )
			{
				lstrcpy( szLine, &m_lpszMsgText[ nCPos ] );

				if ( lstrlen( szLine ) > EMS_MAX_SIT_LINE_LENGTH ) 
				{
					cSaveChar = szLine[ EMS_MAX_SIT_LINE_LENGTH ];

					szLine[ EMS_MAX_SIT_LINE_LENGTH ] = 0;

					lpBlank = _tcsrchr( szLine, ' ' );

					szLine[ EMS_MAX_SIT_LINE_LENGTH ] = cSaveChar;

					if ( lpBlank )
						*lpBlank = 0;
				}	
				wsprintf( szBuffer, c_szSitBody2Fmt, szLine );
			
				hr = WriteLine( lpStream, szBuffer );

				nCPos += lstrlen( szLine ) + 1;
			}
		 }
		 else
		 {
			wsprintf( szBuffer, c_szSitBody2Fmt, "" );

			hr = WriteLine( lpStream, szBuffer );
		 }
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit970::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
	
		wsprintf( szBuffer, c_szSitHdr1Fmt, GetSitNumber(), GetSitDestination() );

		hr = WriteLine( lpStream, szBuffer );

		wsprintf( szBuffer, c_szSitHdr2Fmt, GetSatelliteID(), GetPassID() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

