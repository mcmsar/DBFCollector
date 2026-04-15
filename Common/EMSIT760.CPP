/********************************************************************
*	Module:			emsit760.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit760A  Class
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
#include "emsit760.h"
#include "sitparse.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s/%s/%c%06d");
const TCHAR c_szFieldFmt[] = TEXT("/%s");

CEMSSit760A::CEMSSit760A()
{
	SetSitCode( 0x760A );
	SetSitNumber( 760 );
	m_nCheckCode = 0;
	m_nCheckSum = 0;
	m_controlCode = EMSSCC_Unknown;
	m_lpSitMsg = 0;
	m_nFldCount = 0;
	memset( &m_sitField, 0, 16*sizeof(EMSSITFIELD) );
}

CEMSSit760A::~CEMSSit760A()
{
}

void CEMSSit760A::Reset( void )
{
	CEMSSitMessageBase::Reset( );

	SetSitCode( 0x760A );
	m_nCheckCode = 0;
	m_nCheckSum = 0;
	m_controlCode = EMSSCC_Unknown;

	m_nFldCount = 0;
	memset( &m_sitField, 0, 16*sizeof(EMSSITFIELD) );
}

void CEMSSit760A::SetMsgHeader( CEMSSitMessageBase *lpSitMsg )
{
	CEMSSitMessageBase::SetMsgHeader( lpSitMsg );

	if ( m_lpSitMsg )
		m_lpSitMsg->SetMsgHeader( lpSitMsg );
}

EMS_RESULT CEMSSit760A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{	
		// First, add the special fields.
		hr = _GenerateSpecialFields( lpStream );

		if( SUCCEEDED(hr) )
		{
			if ( m_lpSitMsg )
				hr = m_lpSitMsg->GenerateSit( lpStream );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit760A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szCC[32];

		lstrcpy( szCC, _GetControlCodeText( m_controlCode ) );
		
		wsprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr(), 
							szCC, m_nCheckCode, m_nCheckSum );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit760A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		CEMSSitParser parser;

		if ( m_lpSitMsg )
		{
			delete m_lpSitMsg;
			m_lpSitMsg = 0;
		}

		EMSSITFIELD sitField[1];
		int nFldCount = 0;
		hr = ReadSitLine( lpTokenizer, sitField, 1, &nFldCount );

		if( SUCCEEDED(hr) )
		{
			// Should be an MF645 on this line.
			CEMSSitMsgField msgField;

			hr = msgField.GetMF645( sitField[0].szText, &(m_sitField[0]) );

			if( SUCCEEDED(hr) )
			{
				m_nFldCount = 1;
			}
		}


		hr = parser.ParseSit( lpTokenizer, &m_lpSitMsg );

		if ( ( hr == EMS_OK ) && m_lpSitMsg )
			m_lpSitMsg->SetMsgHeader( this );
	}

	return hr;
}

EMS_RESULT CEMSSit760A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;
	EMSSITCODE sitCode;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
 		EMSSITMF605 mf605;
		int nCount = 0;

		// should find /MF4/MF5/MF4A/MF605/MF650 eol

		if ( nFldCount == 6 )
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

				hr = msgField.GetMF605( sitField[3].szText, &mf605 );
			}

			if ( hr == EMS_OK )
			{
				TCHAR szTemp[ 32 ];

				memset( szTemp, 0, sizeof( szTemp ));

				memcpy( szTemp, &mf605, sizeof( mf605 ) );

				for ( int i = EMSSCC_First; i < EMSSCC_Last; i++ )
				{
					if ( lstrcmpi( _GetControlCodeText( (EMSSITCONTROLCODE)i ), szTemp ) == 0 )
					{
						m_controlCode = (EMSSITCONTROLCODE)i;
						i = EMSSCC_Last;
					}
				}

				hr = msgField.GetMF650( sitField[4].szText, &m_nCheckCode, &m_nCheckSum );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[5].szText ) )
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

void
CEMSSit760A::SetSecurityToken( EMSSITFIELD sitField )
{
	// Clear any existing settings.
	memset( m_sitField, 0, 16*sizeof(EMSSITFIELD) );
	m_nFldCount = 0;

	memcpy( &(m_sitField[0]), &sitField, sizeof(EMSSITFIELD) );
	m_nFldCount = 1;
}

EMSSITFIELD
CEMSSit760A::GetSecurityToken()
{
	EMSSITFIELD ret;
	memset( &ret, 0, sizeof(EMSSITFIELD) );

	if( m_nFldCount > 0 )
	{
		memcpy( &ret, &(m_sitField[0]), sizeof(EMSSITFIELD) );
	}

	return ret;
}

LPCTSTR CEMSSit760A::_GetControlCodeText( EMSSITCONTROLCODE code )
{
	switch ( code )
	{
		case EMSSCC_Info:					return TEXT("INFO");
		case EMSSCC_Validate:			return TEXT("VALD");
		case EMSSCC_Execute:				return TEXT("EXEC");
		case EMSSCC_ValidateInstall:	return TEXT("VALI");
		case EMSSCC_Install:				return TEXT("INST");
		case EMSSCC_InstallManoeuvre:	return TEXT("INSM");
		case EMSSCC_Append:				return TEXT("APND");
		case EMSSCC_ValidData:			return TEXT("DVAL");
		case EMSSCC_InvalidData:		return TEXT("DINV");
		case EMSSCC_CommandAccepted:	return TEXT("CACC");
		case EMSSCC_CommandRejected:	return TEXT("CRJT");
		case EMSSCC_UnknownCommand:	return TEXT("COMX");
		case EMSSCC_ProcessOkay:		return TEXT("CPRS");
		case EMSSCC_ProcessFailed:		return TEXT("CPNS");
		case EMSSCC_Unknown:
		default:								return TEXT("????");
	}
}

EMS_RESULT CEMSSit760A::_GenerateSpecialFields( IEMSSeqStream* lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		for( int i = 0; i < m_nFldCount; i++ )
		{
			if( m_sitField[i].nLength > 0 )
			{
				TCHAR* szField = new TCHAR[m_sitField[i].nLength + 1];
				memset( szField, 0, (m_sitField[i].nLength + 1)*sizeof(TCHAR) );

				_stprintf( szField, c_szFieldFmt, m_sitField[i].szText );

				hr = WriteLine( lpStream, szField );
			}

		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}
