/********************************************************************
*	Module:			emsit950.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit950A  Class
*						Communication Check
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

	0.0	2002 June 3 rvw	start

********************************************************************/
#include <stdio.h>

#include "sitfield.h"
#include "emsit950.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s");

CEMSSit950A::CEMSSit950A()
{
	SetSitCode( 0x950A );
}

CEMSSit950A::~CEMSSit950A()
{
}

void CEMSSit950A::Reset( void )
{
	CEMSSitMessageBase::Reset();

	SetSitCode( 0x950A );
}

EMS_RESULT CEMSSit950A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	return ( lpStream ) ? EMS_OK : EMS_INVALID_STREAM;
}

EMS_RESULT CEMSSit950A::GenerateSitHeader( IEMSSeqStream *lpStream)
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

EMS_RESULT CEMSSit950A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	return ParseSitHeader( lpTokenizer );
}

EMS_RESULT CEMSSit950A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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
