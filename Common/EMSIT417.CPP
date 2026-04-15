/********************************************************************
*	Module:			emsit417.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit417  Class
*						Time and Frequency Calibration for a SARP 
*						Introduced to support new Toulouse Beacon & SARP III
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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
#include "emsit417.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%03ld/%05ld/%s/%012.3f"); 
const TCHAR c_szSitHdrFmtA[ ] = TEXT("/%03d/%04d/%s/%s/%05d/%03ld/%05ld/%s/%012.3f"); 
const TCHAR c_szSitHdrFmtB[ ] = TEXT("/%s"); 

CEMSSit417::CEMSSit417()
{
	SetSitNumber( 417 );
	SetSitCode( 0 );	// Standard Cospas-Sarsat Message

	m_ulSatID = 0;
	m_ulOrbitNumber = 0;
	m_timeCalibration.intTime = 0;
	m_dFrequency = 0.0;
}

CEMSSit417::~CEMSSit417()
{
}

void CEMSSit417::Reset( void )
{
	m_ulSatID = 0;
	m_ulOrbitNumber = 0;
	m_timeCalibration.intTime = 0;
	m_dFrequency = 0.0;

	CEMSSitMessageBase::Reset();

	SetSitNumber( 417 );
}

EMS_RESULT CEMSSit417::GenerateSitBody( IEMSSeqStream *lpStream )
{
	return EMS_OK; // nothing to do
}

EMS_RESULT CEMSSit417::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
	
		CEMSSitMsgField msgField;

		// /MF4/MF5/MF6/MF7/MF37/MF38A

		sprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), 
							GetSitDestination(), m_ulSatID, m_ulOrbitNumber,
							msgField.TextMF37( m_timeCalibration ),
							m_dFrequency );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit417::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
	}

	return hr;
}

EMS_RESULT CEMSSit417::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		// should find /MF4/MF5/MF6/MF7/MF37/MF38A

		if ( nFldCount == 7 )
		{
			CEMSSitMsgField msgField;
			EMSTIME timeCalib;
			double dCalibFreq=0.0;
			int nCount = 0, nSatNumber=0, nOrbitNumber;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF6( sitField[2].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				m_ulSatID = (ULONG)nSatNumber;

				hr = msgField.GetMF7( sitField[3].szText, &nOrbitNumber );
			}

			if ( hr == EMS_OK )
			{
				m_ulOrbitNumber = (ULONG)nOrbitNumber;			

				hr = msgField.GetMF37( sitField[4].szText, &timeCalib );
			}

			if ( hr == EMS_OK )
			{
				m_timeCalibration = timeCalib;

				hr = msgField.GetMF38A( sitField[5].szText, &dCalibFreq );
			}

			if ( hr == EMS_OK )
				m_dFrequency = dCalibFreq;

			if ( !msgField.IsEOL( sitField[6].szText ) )
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


CEMSSit417A::CEMSSit417A()
{
	SetSitCode( 0x417A );

	m_nRequestMsgNumber = 0;

	m_controlCode = EMSSCC_Unknown;
}

CEMSSit417A::~CEMSSit417A()
{
}

void CEMSSit417A::Reset( void )
{
	int nSit = GetSitNumber();

	CEMSSit417::Reset();

	SetSitNumber( nSit );

	SetSitCode( 0x417A );
}


EMS_RESULT CEMSSit417A::GenerateSitHeader( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szCC[32];
		CEMSSitMsgField msgField;
	
		lstrcpy( szCC, _GetControlCodeText( m_controlCode ) );

		// /MF4/MF5/MF4A/MF605/MF1A/MF6/MF7/MF37/MF38A

		sprintf( szBuffer, c_szSitHdrFmtA, GetSitNumber(), 
							GetSitDestination(), 
							GetSitCodeStr(), szCC, m_nRequestMsgNumber,
							GetSatelliteID(), GetOrbitNumber(),
							msgField.TextMF37( GetCalibrationTime() ),
							GetFrequency() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT CEMSSit417A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		// should find /MF4/MF5/MF4A/MF605/MF1A/MF6/MF7/MF37/MF38A

		if ( nFldCount == 10 )
		{
			CEMSSitMsgField msgField;
			EMSSITCODE sitCode;
	 		EMSSITMF605 mf605;
			EMSTIME timeCalib;
			double dCalibFreq=0.0;
			int nCount = 0, nSatNumber=0, nOrbitNumber;

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
				hr = msgField.GetMF6( sitField[5].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatelliteID( (ULONG)nSatNumber );

				hr = msgField.GetMF7( sitField[6].szText, &nOrbitNumber );
			}

			if ( hr == EMS_OK )
			{
				SetOrbitNumber( (ULONG)nOrbitNumber );			

				hr = msgField.GetMF37( sitField[7].szText, &timeCalib );
			}

			if ( hr == EMS_OK )
			{
				SetCalibrationTime( timeCalib );

				hr = msgField.GetMF38A( sitField[8].szText, &dCalibFreq );
			}

			if ( hr == EMS_OK )
				SetFrequency( dCalibFreq );

			if ( !msgField.IsEOL( sitField[9].szText ) )
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


LPCTSTR CEMSSit417A::_GetControlCodeText( EMSSITCONTROLCODE code )
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


CEMSSit417B::CEMSSit417B()
{
	SetSitCode( 0x417B );
	m_tmEffectiveTime.intTime = 0;
}

CEMSSit417B::~CEMSSit417B()
{
}

void CEMSSit417B::Reset( void )
{
	CEMSSit417A::Reset();

	SetSitCode( 0x417B );

	m_tmEffectiveTime.intTime = 0;
}


EMS_RESULT CEMSSit417B::GenerateSitHeader( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = CEMSSit417A::GenerateSitHeader( lpStream );

	if ( EMS_OK == hr )
	{
		TCHAR szBuffer[ 256 ];
		CEMSSitMsgField msgField;
	
		//  /MF664
		sprintf( szBuffer, c_szSitHdrFmtB, msgField.TextMF664( m_tmEffectiveTime ) );

		hr = WriteLine( lpStream, szBuffer );
	}

	return hr;
}


EMS_RESULT CEMSSit417B::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = CEMSSit417A::ParseSitHeader( lpTokenizer, bPeek );
	
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		// should find /MF664

		if ( nFldCount == 2 )
		{
			CEMSSitMsgField msgField;
			EMSTIME         timeEffective;

			hr = msgField.GetMF664( sitField[0].szText, &timeEffective );
			
			if( hr == EMS_OK )
			{
				SetEffectiveTime( timeEffective );

				if( !msgField.IsEOL( sitField[1].szText ) )
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

