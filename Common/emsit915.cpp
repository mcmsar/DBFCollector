/********************************************************************
*	Module:			emsit915.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit915  Class
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

	0.0	2003 Jan 31		LGuan	start

********************************************************************/
#include <stdio.h>

#include "sitfield.h"
#include "emsit915.h"

CEMSSit915::CEMSSit915()
{

}

CEMSSit915::~CEMSSit915()
{
	Reset();
}

void CEMSSit915::Reset( void )
{
	CEMSSitMessageBase::Reset();
	SetSitNumber(915);
}


EMS_RESULT CEMSSit915::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		hr = _ParseText( lpTokenizer );
	}
	return hr;
}


EMS_RESULT CEMSSit915::_ParseText( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[16];
	int nFldCount = 0;
	int nCount = 0;
	BOOL bEnd = FALSE;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	bEnd = ( ( lstrcmpi( sitField[0].szText, TEXT("QQQQ") ) == 0 ) || ( hr != EMS_OK ) );

	while ( hr == EMS_OK && !bEnd)
	{
		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );
		bEnd = ( ( lstrcmpi( sitField[0].szText, TEXT("QQQQ") ) == 0 ) || ( hr != EMS_OK ) );
	}
	return hr;
}



EMS_RESULT CEMSSit915::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0;

		// should find /MF4/MF5 eol

		if ( nFldCount == 3 )
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
				
				if ( !msgField.IsEOL( sitField[2].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
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

