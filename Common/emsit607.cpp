/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "emsit607.h"
#include "sitfield.h"

CEMSSit607::CEMSSit607() : m_iSatCount(0)
{
	SetSitNumber( 607 );
}

void
CEMSSit607::Reset()
{
	m_iSatCount = 0;
}

EMS_RESULT CEMSSit607::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF44 EOL

		if ( nFldCount == 4 )
		{
			int nSitNumber = 0, nSitDestination = 0, nSats = 0;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF74( sitField[2].szText, &nSats );
			}

			if ( hr == EMS_OK )
			{
				SetSatCount( nSats );

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

EMS_RESULT CEMSSit607::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	for( int i = 0; i < m_iSatCount; i++ )
	{
		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		// This is just a read of each line right now.  The data is not
		// used by the system.  So, real parsing implementation is not provided
		// at this time.
	}

	return hr;
}