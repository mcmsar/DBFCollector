/********************************************************************
*	Module:			emsit951.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit951A  Class
*						Retransmit Message Request
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

#include "emsit951.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s");
const TCHAR c_szSitBodyFmt[ ] = TEXT("/%04d/%05d/%02d");

CEMSSit951A::CEMSSit951A()
{
	m_nMsgDestID = 0;
	m_nMsgReqNumber = 0;
	m_nMsgReqCount = 0;
}

CEMSSit951A::~CEMSSit951A()
{
}

void CEMSSit951A::Reset( void )
{
	SetSitCode( 0x951A );
	m_nMsgDestID = 0;
	m_nMsgReqNumber = 0;
	m_nMsgReqCount = 0;
}

EMS_RESULT CEMSSit951A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSitBodyFmt, m_nMsgDestID,
									m_nMsgReqNumber, m_nMsgReqCount );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit951A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		sprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit951A::_ParseRequestLine( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0;

		// should find /MF5A/MF1A/MF635 eol

		if ( nFldCount == 4 )
		{
			hr = msgField.GetMF5A( sitField[0].szText, &m_nMsgDestID );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF1A( sitField[1].szText, &m_nMsgReqNumber );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF635( sitField[2].szText, &m_nMsgReqCount );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[3].szText ) )
					hr = EMS_SIT_SYNTAX_EOL;
			}
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSSit951A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		hr = _ParseRequestLine( lpTokenizer );
	}

	return hr;
}

EMS_RESULT CEMSSit951A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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
