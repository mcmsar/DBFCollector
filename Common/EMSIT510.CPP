/********************************************************************
*	Module:			emsit510.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit510 & CEMSSit510A Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
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
#include <stdio.h>

#include "emsit510.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%02d");
const TCHAR c_szSitHdrFmtA[ ] = TEXT("/%03d/%04d/%s/%s/%05d/%02d");
const TCHAR c_szSitLineFmt[ ] = TEXT("/%03d/%+09.3f/%+07.3f/%s");

CEMSSit510::CEMSSit510()
{
	SetSitNumber( 510 );
	SetSitCode( 0 );	// Standard Cospas-Sarsat Message

	m_nSatCount = 0;

	memset( m_data, 0, sizeof( m_data ) );
}

CEMSSit510::~CEMSSit510()
{
}

void CEMSSit510::Reset( void )
{
	m_nSatCount = 0;

	memset( m_data, 0, sizeof( m_data ) );

	CEMSSitMessageBase::Reset();

	SetSitNumber( 510 );
}

EMS_RESULT CEMSSit510::GetSatData( LPEMSSIT510DATA lpData, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nSatCount ) && lpData )
		memcpy( lpData, &m_data[ nIndex ], sizeof( EMSSIT510DATA ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit510::AddSatData( LPEMSSIT510DATA lpData, int nIndex /* = -1 */ )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpData )
	{
		if ( nIndex == -1 ) // ie: append 
		{
			if ( m_nSatCount < EMSSIT510_MAX_SATELLITES )
			{
				memcpy( &m_data[ m_nSatCount++ ] , lpData, sizeof( EMSSIT510DATA ) );
			}
			else
				hr = EMS_ERROR_LIMIT;
		}
		else if (( nIndex >= 0 ) && ( nIndex < m_nSatCount ) )	// ie: set
		{
			memcpy( &m_data[ nIndex ] , lpData, sizeof( EMSSIT510DATA ) );
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;
			
	return hr;
}


EMS_RESULT CEMSSit510::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
//	EMSTIMEFIELDS timeFields;
//	int nYear;
//	CEMSTime timeTemp;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;

		for ( int i = 0; ( i < m_nSatCount ) && ( hr == EMS_OK ); i++ )
		{
//			timeTemp.SetTime( m_data[i].timeCalibration );
//
//			timeTemp.GetTime( &timeFields );
//
//			if ( timeFields.nYear >= 2000 )
//				nYear = timeFields.nYear - 2000;
//			else
//				nYear = timeFields.nYear - 1900;

			if ( m_data[i].dFreqOffset > 9999.999 )	      m_data[i].dFreqOffset =  9999.999;
			else if ( m_data[i].dFreqOffset < -9999.999 ) m_data[i].dFreqOffset = -9999.999;

			if ( m_data[i].dFreqDrift > 99.999 )	   m_data[i].dFreqDrift =  99.999;
			else if ( m_data[i].dFreqDrift < -99.999 ) m_data[i].dFreqDrift = -99.999;

			sprintf( szBuffer, c_szSitLineFmt, m_data[i].ulSatID,
							m_data[i].dFreqOffset, m_data[i].dFreqDrift,
							msgField.TextMF66( m_data[i].timeCalibration ) );								

//							nYear,
//							timeFields.nJulianDay,
//							timeFields.nHour,
//							timeFields.nMinute);

			hr = WriteLine( lpStream, szBuffer );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit510::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
	
		sprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
						GetSitDestination(), m_nSatCount );

		hr = WriteLine( lpStream, szBuffer );
		
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT CEMSSit510::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ) && 
						( i < EMSSIT510_MAX_SATELLITES ); i++ )
		{
			hr = _ParseSitLine( lpTokenizer, i );
		}
	}

	return hr;
}

EMS_RESULT CEMSSit510::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		// should find /MF4/MF5/MF44 eol

		if ( nFldCount == 4 )
		{
			CEMSSitMsgField msgField;
			int nCount = 0, nNumber=0, nSitNumber=0;

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
			}

			if ( !msgField.IsEOL( sitField[3].szText ) )
				hr = EMS_SIT_SYNTAX_EOL;
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

EMS_RESULT CEMSSit510::_ParseSitLine( CEMSSitTokenizer *lpTokenizer, int iIndex, BOOL bPeek  )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nNumber = 0;

		// should find /MF6/MF64/MF65/MF66 eol

		if ( nFldCount == 5 )
		{
			hr = msgField.GetMF6( sitField[0].szText, &nNumber );

			if ( hr == EMS_OK )
			{
				m_data[ iIndex ].ulSatID = (ULONG)nNumber;

				hr = msgField.GetMF64( sitField[1].szText, 
									&m_data[ iIndex ].dFreqOffset );
			}

			if ( hr == EMS_OK )
				hr = msgField.GetMF65( sitField[2].szText, 
					&m_data[ iIndex ].dFreqDrift );

			if ( hr == EMS_OK )
				hr = msgField.GetMF66( sitField[3].szText, 
									&m_data[ iIndex ].timeCalibration );

			if ( !msgField.IsEOL( sitField[4].szText ) )
				hr = EMS_SIT_SYNTAX_EOL;

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


CEMSSit510A::CEMSSit510A()
{
	SetSitCode( 0x510A );

	m_nRequestMsgNumber = 0;

	m_controlCode = EMSSCC_Unknown;
}

CEMSSit510A::~CEMSSit510A()
{
}

void CEMSSit510A::Reset( void )
{
	int nSit = GetSitNumber();

	CEMSSit510::Reset();

	SetSitNumber( nSit );

	SetSitCode( 0x510A );
}


EMS_RESULT CEMSSit510A::GenerateSitHeader( IEMSSeqStream *lpStream)
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


EMS_RESULT CEMSSit510A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

LPCTSTR CEMSSit510A::_GetControlCodeText( EMSSITCONTROLCODE code )
{
	switch ( code )
	{
		case EMSSCC_Info:					return TEXT("INFO");
		case EMSSCC_Validate:			return TEXT("VALD");
		case EMSSCC_Execute:				return TEXT("EXEC");
		case EMSSCC_ValidateInstall:	return TEXT("VALI");
		case EMSSCC_Install:				return TEXT("INST");
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


