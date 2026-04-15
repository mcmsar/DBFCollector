/********************************************************************
*	Module:			emsit215.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit215  & CEMSSit215A Class
*						Leosar Orbit Vectors ( Earth-Fixed Format )
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
#include <tchar.h>
#include "emsit215.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%02d");
const TCHAR c_szSitHdrFmtA[ ] = TEXT("/%03d/%04d/%s/%s/%05d/%02d");
const TCHAR c_szSitVectorLine1Fmt[ ] = TEXT("/%03ld/%05ld/%02ld");
const TCHAR c_szSitVectorLine2Fmt[ ] = 	TEXT("/%s");
const TCHAR c_szSitVectorLine3Fmt[ ] = 
			TEXT("/%+010.4lf %+010.4lf %+010.4lf/%+010.5lf %+010.5lf %+010.5lf");
const TCHAR c_szSitVectorLine1FmtB[ ] = TEXT("/%03ld/%05ld/%02ld/%s");

const TCHAR c_szSitVectorLine3FmtC[ ] = 
			TEXT("/%+011.4lf %+011.4lf %+011.4lf/%+010.6lf %+010.6lf %+010.6lf");

CEMSSit215::CEMSSit215()
{
	SetSitNumber(215);

	SetSitCode( 0 );		// standard Cospas-Sarsat message

	m_nSatCount = 0;

	memset( m_data, 0, sizeof( m_data ) );
}

CEMSSit215::~CEMSSit215()
{
}

void CEMSSit215::Reset( void )
{
	CEMSSitMessageBase::Reset();

	SetSitNumber(215);

	m_nSatCount = 0;

	memset( m_data, 0, sizeof( m_data ) );
}

EMS_RESULT CEMSSit215::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		for ( int i = 0; ( i < m_nSatCount ) && ( hr == EMS_OK ); i++ )
		{
			hr = _WriteVectorLine1( lpStream, i );

			if ( hr == EMS_OK )
			{
				hr = _WriteVectorLine2( lpStream, i );
			}

			if ( hr == EMS_OK )
			{
				hr = _WriteVectorLine3( lpStream, i );
			}
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT CEMSSit215::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		sprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
								GetSitDestination(),	GetSatCount() );					

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit215::GetOrbitData( LPEMSSIT215DATA lpData, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nSatCount ) && lpData )
		memcpy( lpData, &m_data[ nIndex ], sizeof( EMSSIT215DATA ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit215::AddOrbitData( LPEMSSIT215DATA lpData, int nIndex /* = -1 */ )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpData )
	{
		if ( nIndex == -1 ) // ie: append 
		{
			if ( m_nSatCount < EMSSIT215_MAX_SATELLITES )
			{
				memcpy( &m_data[ m_nSatCount++ ] , lpData, sizeof( EMSSIT215DATA ) );
			}
			else
				hr = EMS_ERROR_LIMIT;
		}
		else if (( nIndex >= 0 ) && ( nIndex < m_nSatCount ) )	// ie: set
		{
			memcpy( &m_data[ nIndex ] , lpData, sizeof( EMSSIT215DATA ) );
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;
			
	return hr;
}


EMS_RESULT CEMSSit215::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
		{
			hr = _ParseOrbitVectorLine1( lpTokenizer, &m_data[i] );

			if ( hr == EMS_OK )
				hr = _ParseOrbitVectorLine2( lpTokenizer, &m_data[i] );

			if ( hr == EMS_OK )
				hr = _ParseOrbitVectorLine3( lpTokenizer, &m_data[i] );

			if ( hr == EMS_OK )
			{
				if ( m_data[i].timeEffective.intTime == 0 )
					m_data[i].timeEffective = m_data[i].timeOrbit;
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSit215::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF44/

		if ( nFldCount == 4 )
		{
			int nNumber = 0;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF44( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				m_nSatCount = nNumber;

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

EMS_RESULT CEMSSit215::_ParseOrbitVectorLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nNumber=0;

		// should find /MF6/MF7/MF32 

		if ( nFldCount == 4 )
		{
			int nNumber = 0;

			hr = msgField.GetMF6( sitField[0].szText, &nNumber );

			if ( hr == EMS_OK )
			{
				lpData->ulSatID = (ULONG)nNumber;

				hr = msgField.GetMF7( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitNumber = (ULONG)nNumber;

				hr = msgField.GetMF32( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitVectors = (ULONG)nNumber;

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

EMS_RESULT CEMSSit215::_ParseOrbitVectorLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF34 eol

		if ( nFldCount == 2 )
		{
			int nNumber = 0;

			hr = msgField.GetMF34( sitField[0].szText, &(lpData->timeOrbit) );

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[1].szText ) )
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

EMS_RESULT CEMSSit215::_ParseOrbitVectorLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF35/MF36 eol

		if ( nFldCount == 3 )
		{
			int nNumber = 0;

			hr = msgField.GetMF35( sitField[0].szText, &(lpData->vOrbitPosition ) );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF36( sitField[1].szText, &(lpData->vOrbitVelocity ) );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[2].szText ) )
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


EMS_RESULT
CEMSSit215::_WriteVectorLine1( IEMSSeqStream* pStrm, int iDataIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( pStrm )
	{
		TCHAR szBuffer[ 256 ];

		memset( szBuffer, 0, 256 * sizeof(TCHAR) );

		_sntprintf( szBuffer, 256, c_szSitVectorLine1Fmt, 
				m_data[iDataIndex].ulSatID,            // MF#6
				m_data[iDataIndex].ulOrbitNumber,      // MF#7
				m_data[iDataIndex].ulOrbitVectors );   // MF#32 

		hr = WriteLine( pStrm, szBuffer );
	}

	return hr;
}

EMS_RESULT
CEMSSit215::_WriteVectorLine2( IEMSSeqStream* pStrm, int iDataIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( pStrm )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;
		
		memset( szBuffer, 0, 256 * sizeof(TCHAR) );

		_sntprintf( szBuffer, 256, c_szSitVectorLine2Fmt, 
			        msgField.TextMF34( m_data[iDataIndex].timeOrbit ) );

		hr = WriteLine( pStrm, szBuffer );
	}

	return hr;
}

EMS_RESULT
CEMSSit215::_WriteVectorLine3( IEMSSeqStream* pStrm, int iDataIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( pStrm )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;
		
		memset( szBuffer, 0, 256 * sizeof(TCHAR) );

		_sntprintf( szBuffer, 256, c_szSitVectorLine3Fmt,
			        m_data[iDataIndex].vOrbitPosition.fX, //Position
					m_data[iDataIndex].vOrbitPosition.fY,
					m_data[iDataIndex].vOrbitPosition.fZ,
					m_data[iDataIndex].vOrbitVelocity.fX, //Velocity
					m_data[iDataIndex].vOrbitVelocity.fY,
					m_data[iDataIndex].vOrbitVelocity.fZ );

		hr = WriteLine( pStrm, szBuffer );
	}

	return hr;
}


CEMSSit215A::CEMSSit215A()
{
	SetSitCode( 0x215A );

	m_nRequestMsgNumber = 0;

	m_controlCode = EMSSCC_Unknown;
}

CEMSSit215A::~CEMSSit215A()
{
}

void CEMSSit215A::Reset( void )
{
	int nSit = GetSitNumber();

	CEMSSit215::Reset();

	SetSitNumber( nSit );

	SetSitCode( 0x215A );
}


EMS_RESULT CEMSSit215A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szCC[32];
		
		lstrcpy( szCC, _GetControlCodeText( m_controlCode ) );
		
		wsprintf( szBuffer, c_szSitHdrFmtA, GetSitNumber(), 
							GetSitDestination(),	GetSitCodeStr(), 
							szCC, m_nRequestMsgNumber , GetSatCount() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT CEMSSit215A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF4A/MF605/MF01A/MF44/

		if ( nFldCount == 7 )
		{
			int nNumber = 0;
			EMSSITCODE sitCode;
	 		EMSSITMF605 mf605;

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

				hr = msgField.GetMF1A( sitField[4].szText, &m_nRequestMsgNumber );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF44( sitField[5].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatCount( nNumber );

				if ( !msgField.IsEOL( sitField[6].szText ) )
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

LPCTSTR CEMSSit215A::_GetControlCodeText( EMSSITCONTROLCODE code )
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


CEMSSit215B::CEMSSit215B()
{
	SetSitCode( 0x215B );
}

CEMSSit215B::~CEMSSit215B()
{
}

void CEMSSit215B::Reset()
{
	CEMSSit215::Reset();

	SetSitCode( 0x215B );
}

EMS_RESULT CEMSSit215B::_ParseOrbitVectorLine1(   CEMSSitTokenizer* lpTokenizer,
                                       LPEMSSIT215DATA lpData )
{
	EMSSITFIELD    sitField[ 16 ];
	EMS_RESULT     hr          = EMS_OK;
	int            nFldCount   = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( EMS_OK == hr )
	{
		CEMSSitMsgField   msgField;
		int               nNumber = 0;

		// should find /MF6/MF7/MF32/MF664
		if ( 5 == nFldCount )
		{
			int nNumber = 0;

			hr = msgField.GetMF6( sitField[0].szText, &nNumber );

			if ( hr == EMS_OK )
			{
				lpData->ulSatID = (ULONG)nNumber;
		
				hr = msgField.GetMF7( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitNumber = (ULONG)nNumber;

				hr = msgField.GetMF32( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitVectors = (ULONG)nNumber;
		
				hr = msgField.GetMF664( sitField[3].szText, &(lpData->timeEffective) );
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
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	return hr;
}

EMS_RESULT CEMSSit215B::_WriteVectorLine1( IEMSSeqStream* lpStream,
                                 int iDataIndex )   // index into m_data[]
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;

		_sntprintf( szBuffer, 256, c_szSitVectorLine1FmtB, 
				m_data[iDataIndex].ulSatID,            // MF#6
				m_data[iDataIndex].ulOrbitNumber,      // MF#7
				m_data[iDataIndex].ulOrbitVectors,     // MF#32
				msgField.TextMF664( m_data[iDataIndex].timeEffective ) );   // MF#664

		hr = WriteLine( lpStream, szBuffer );
	}
	return hr;
}


CEMSSit215C::CEMSSit215C()
{
	SetSitCode( 0x215C );
}

CEMSSit215C::~CEMSSit215C()
{
}

void 
CEMSSit215C::Reset()
{
	CEMSSit215::Reset();

	SetSitCode( 0x215C );
}


EMS_RESULT
CEMSSit215C::_WriteVectorLine3( IEMSSeqStream* pStrm, int iDataIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( pStrm )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;
		
		memset( szBuffer, 0, 256 * sizeof(TCHAR) );

		_sntprintf( szBuffer, 256, c_szSitVectorLine3FmtC,
			        m_data[iDataIndex].vOrbitPosition.fX, //Position
					m_data[iDataIndex].vOrbitPosition.fY,
					m_data[iDataIndex].vOrbitPosition.fZ,
					m_data[iDataIndex].vOrbitVelocity.fX, //Velocity
					m_data[iDataIndex].vOrbitVelocity.fY,
					m_data[iDataIndex].vOrbitVelocity.fZ );

		hr = WriteLine( pStrm, szBuffer );
	}

	return hr;
}


EMS_RESULT 
CEMSSit215C::_ParseOrbitVectorLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF35A/MF36A eol

		if ( nFldCount == 3 )
		{
			int nNumber = 0;

			hr = msgField.GetMF35A( sitField[0].szText, &(lpData->vOrbitPosition ) );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF36A( sitField[1].szText, &(lpData->vOrbitVelocity ) );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[2].szText ) )
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
