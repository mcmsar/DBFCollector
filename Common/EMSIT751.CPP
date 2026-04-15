/********************************************************************
*	Module:			emsit751.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit751A  Class
*						LUT Command Ack
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
#include <string.h>

#include <array.h>
#include "emsit751.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s");
const TCHAR c_szSitBodyFmt[ ] = TEXT("/%05d/%s");

CEMSSit751A::CEMSSit751A()
{
	SetSitCode( 0x751A );
	m_nAckMsgNumber = 0;
	memset( m_szStatus, 0 ,sizeof( m_szStatus ) );
}

CEMSSit751A::~CEMSSit751A()
{
}

void CEMSSit751A::Reset( void )
{
	CEMSSitMessageBase::Reset();

	SetSitCode( 0x751A );
	m_nAckMsgNumber = 0;
	memset( m_szStatus, 0 ,sizeof( m_szStatus ) );
}

void CEMSSit751A::SetStatus( LPCTSTR lpcszStatus )
{
	if ( lpcszStatus && *lpcszStatus )
		lstrcpyn( m_szStatus, lpcszStatus, EMS_SIT751A_STATUS_LEN + 1 );
	else
		memset( m_szStatus, 0 ,sizeof( m_szStatus ) );
}

EMS_RESULT CEMSSit751A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		wsprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit751A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		wsprintf( szBuffer, c_szSitBodyFmt, m_nAckMsgNumber, m_szStatus );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit751A::ParseSitMessage( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		EMSSITFIELD sitField[3];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

		if ( hr == EMS_OK )
		{
			if( 3 == nFldCount )
			{
				CEMSSitMsgField msgField;

				// Should be /MF01A/MF605 + eol
				hr = msgField.GetMF1A( sitField[0].szText, &m_nAckMsgNumber );

				if( SUCCEEDED(hr) )
				{
					EMSSITMF605 mf605;
					memset( &mf605, 0, sizeof(EMSSITMF605) );

					hr = msgField.GetMF605( sitField[1].szText, &mf605 );

					if( SUCCEEDED(hr) )
					{
						if( EMS_SIT751A_STATUS_LEN >= sizeof(mf605.cValue) )
						{
							_tcsncpy( m_szStatus, mf605.cValue, sizeof(mf605.cValue) );
						}
					}
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}

	return hr;
}
