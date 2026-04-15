/********************************************************************
*	Module:			EMSSIT152.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit152
*	
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include <stdio.h>
#include <tchar.h>
#include "emsit152.h"
#include "sitfield.h"

const int c_iAllocCount = 32;

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d"); 

const TCHAR c_szSitAlertLine1Fmt[ ] = TEXT("/%04d/%04d/%04d/%012.2lf");
const TCHAR c_szSitAlertLine2Fmt[ ] = TEXT("/%s/%s");
const TCHAR c_szSitAlertLine3Fmt[ ] = TEXT("/%s/%+03d/%01.0lf");
const TCHAR c_szSitAlertLine4Fmt[ ] = TEXT("/%s");
const TCHAR c_szSitAlertLine5Fmt[ ] = TEXT("%s");
const TCHAR c_szSitAlertLine6Fmt[ ] = TEXT("%s");

CEMSSit152::CEMSSit152() : m_iAlertCount(0),
                           m_iAllocCount(0),
                           m_iSatID(0),
						   m_iAlertsToParse(0),
						   m_lpABAlerts(NULL)
{
	SetMaxLinesPerRecord( EMS_MAX_LINES_PER_ABL_ALERT_SIT152 );

	SetSitNumber(152);
}

CEMSSit152::~CEMSSit152()
{
	Reset();
}

void 
CEMSSit152::Reset()
{
	CEMSSitMessageBase::Reset();

	m_iAlertCount = 0;
	m_iAllocCount = 0;
	m_iSatID = 0;
	m_iAlertsToParse = 0;
	
	SetSitNumber(152);
	SetMaxLinesPerRecord( EMS_MAX_LINES_PER_ABL_ALERT_SIT152 );

	if( m_lpABAlerts )
	{
		delete []m_lpABAlerts;
		m_lpABAlerts = NULL;
	}
}

EMS_RESULT 
CEMSSit152::AddABLAlert( const EMSSITABLDATA& crABLSITData )
{
	EMS_RESULT hr = EMS_OK;

	if( GetAlertCount() < GetMaxAlertCount() )
	{
		if( ( GetAlertCount() + 1 ) > m_iAllocCount )
		{
			int iNewCount = GetAlertCount() + c_iAllocCount;
			LPEMSSITABLDATA lpNewData = new EMSSITABLDATA[ iNewCount ];

			if( lpNewData )
			{
				if( m_lpABAlerts )
				{
					memcpy( lpNewData, m_lpABAlerts, GetAlertCount() * sizeof( EMSSITABLDATA ) );

					delete []m_lpABAlerts;
					m_lpABAlerts = NULL;
				}

				m_lpABAlerts = lpNewData;

				m_iAllocCount = iNewCount;
			}
			else
			{
				hr = EMS_NO_MEMORY;
			}
		}

		if( m_lpABAlerts )
		{
			memcpy( &m_lpABAlerts[ GetAlertCount() ], &crABLSITData, sizeof( EMSSITABLDATA ) );

			_IncrAlertCount();
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}
	}
	else
	{
		hr = EMS_SIT_ALERT_LIMIT;
	}

	return hr;
}

int CEMSSit152::GetMaxAlertCount()
{
	int iMaxCount = 0;
	
	if( 0 < m_nMaxLineSize && 0 < m_nMaxLinesPerRecord )
	{
		// The maximum number of records permitted in the message is:
		//		(MsgFileSize/LineSize - (HeaderLines + TrailerLines))/LinesPerRecord
		iMaxCount = ( m_nMaxMsgSize/m_nMaxLineSize - (m_nHeaderLines + m_nTrailerLines) ) / m_nMaxLinesPerRecord;
	}

	return iMaxCount;
}


EMS_RESULT
CEMSSit152::GetABLAlert( LPEMSSITABLDATA lpABLSITData, int iIndex )
{
	EMS_RESULT hr = EMS_OK;

	if( lpABLSITData && m_lpABAlerts && (iIndex >= 0) && (iIndex < GetAlertCount()) )
	{
		memcpy( lpABLSITData, &m_lpABAlerts[iIndex], sizeof( EMSSITABLDATA ) );
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT 
CEMSSit152::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		// /MF4/MF5/MF6/MF8

		sprintf( szBuffer, c_szSitHdrFmt, GetSitNumber(), GetSitDestination(), 
			                   GetSatelliteID(), GetAlertCount() );					

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}


EMS_RESULT 
CEMSSit152::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		for ( int i = 0; ( i < m_iAlertCount ) && ( EMS_OK == hr ); i++ )
		{
			hr = _WriteABAlertData( lpStream, &m_lpABAlerts[i] );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertData( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			hr = _WriteABAlertDataLine1( lpStream, lpSitABLData );

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine2( lpStream, lpSitABLData );
			}

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine3( lpStream, lpSitABLData );
			}

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine4( lpStream, lpSitABLData );
			}

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine5( lpStream, lpSitABLData );
			}

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine6( lpStream, lpSitABLData );
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine1( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			memset( szBuffer, 0, sizeof( szBuffer ) );

			sprintf( szBuffer, c_szSitAlertLine1Fmt, 
						lpSitABLData->iLUTID,
						lpSitABLData->iNumBursts,
						lpSitABLData->iNumMsgs,
						lpSitABLData->dFrequency );

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine2( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			CEMSSitMsgField  oMsgField;
			TCHAR            szBuffer[256];

			memset( szBuffer, 0, sizeof( szBuffer ) );

			sprintf( szBuffer, c_szSitAlertLine2Fmt, 
						oMsgField.TextMFN4(lpSitABLData->timeFirst),
						oMsgField.TextMFN5(lpSitABLData->timeLast) );

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine3( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			TCHAR szHexBeaconID[34];

			memset( szBuffer, 0, sizeof( szBuffer ) );
			memset( szHexBeaconID, 0, sizeof( szHexBeaconID ) );

			_i64toa( lpSitABLData->i64BeaconID, szHexBeaconID, 16 );
			_strupr( szHexBeaconID );

			sprintf( szBuffer, c_szSitAlertLine3Fmt, 
				                       szHexBeaconID,
									   lpSitABLData->iWaveForm, 
									   lpSitABLData->dMQF );

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine4( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			TCHAR szBeaconMsg[36];

			memset( szBuffer, 0, sizeof( szBuffer ) );
			memset( szBeaconMsg, 0, sizeof( szBeaconMsg ) );

			for ( int j = 0; j < 15; j++ )
			{
				wsprintf( &szBeaconMsg[j*2], "%02X", lpSitABLData->acBeaconMsg[3+j] );
			}

			sprintf( szBuffer, c_szSitAlertLine4Fmt, szBeaconMsg ); //MF23

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine5( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			TCHAR szSatIds[65];

			memset( szBuffer, 0, sizeof( szBuffer ) );
			memset( szSatIds, 0, sizeof( szSatIds ) );

			for ( int i = 0; i < EMS_MAX_SATS_PER_ABL_ALERT; i++ )
			{
				wsprintf( &szSatIds[i*4], "/%03d", lpSitABLData->aiSatIDs[i] );
			}

			sprintf( szBuffer, c_szSitAlertLine5Fmt, szSatIds ); 

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_WriteABAlertDataLine6( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			TCHAR szLUTIds[66];

			memset( szBuffer, 0, sizeof( szBuffer ) );
			memset( szLUTIds, 0, sizeof( szLUTIds ) );

			for ( int i = 0; i < EMS_MAX_LUTS_PER_ABL_ALERT; i++ )
			{
				wsprintf( &szLUTIds[i*5], "/%04d", lpSitABLData->aiLutIDs[i] );
			}

			sprintf( szBuffer, c_szSitAlertLine6Fmt, szLUTIds ); 

			hr = WriteLine( lpStream, szBuffer );
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if( EMS_OK == hr )
	{
		for( int i = 0; (EMS_OK == hr) && (i < m_iAlertsToParse); i++ )
		{
			EMSSITABLDATA sitABLData;
			memset( &sitABLData, 0, sizeof(EMSSITABLDATA) );

			hr = _ParseABAlertData( lpTokenizer, &sitABLData );

			if( EMS_OK == hr )
			{
				AddABLAlert( sitABLData );
			}
		}
	}

	return hr;
}

EMS_RESULT 
CEMSSit152::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT   hr = EMS_OK;
	EMSSITFIELD  sitField[ 16 ];
	int          iFldCount = 0;
	int          iSitNumber = 0;
	int          iSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

	if( EMS_OK == hr )
	{
		CEMSSitMsgField oMsgField;

		// should find /MF4/MF5/MF6/MF10

		if( iFldCount == 5 )
		{
			int iNumber = 0;

			hr = oMsgField.GetMF4( sitField[0].szText, &iSitNumber );

			if( EMS_OK == hr )
			{
				SetSitNumber( iSitNumber );

				hr = oMsgField.GetMF5( sitField[1].szText, &iSitDestination );
			}

			if( EMS_OK == hr )
			{
				SetSitDestination( iSitDestination );

				hr = oMsgField.GetMF6( sitField[2].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				m_iSatID = iNumber;

				iNumber = 0;

				hr = oMsgField.GetMF10( sitField[3].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				_SetNumAlertsToParse( iNumber );

				if( !oMsgField.IsEOL( sitField[4].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}

		if( bPeek )
			UnReadSitLine( lpTokenizer, sitField, iFldCount );
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit152::_ParseABAlertData( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		hr = _ParseABAlertLine1( lpTokenizer, lpSitABLData );
		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine2( lpTokenizer, lpSitABLData );
		}

		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine3( lpTokenizer, lpSitABLData );
		}

		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine4( lpTokenizer, lpSitABLData );
		}

		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine5( lpTokenizer, lpSitABLData );
		}

		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine6( lpTokenizer, lpSitABLData );
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit152::_ParseABAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ 16 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF11/N6/N7/N8 EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == 5 )
			{
				hr = oMsgField.GetMF11( sitField[0].szText, &(lpSitABLData->iLUTID) );

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN6( sitField[1].szText, &(lpSitABLData->iNumBursts) );
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN7( sitField[2].szText, &(lpSitABLData->iNumMsgs) );
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN8( sitField[3].szText, &(lpSitABLData->dFrequency) );

					if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[4].szText ) )
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
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit152::_ParseABAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ 16 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /N4/N5 EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == 3 )
			{
				hr = oMsgField.GetMFN4( sitField[0].szText, &(lpSitABLData->timeFirst) );

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN5( sitField[1].szText, &(lpSitABLData->timeLast) );

					if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[2].szText ) )
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
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit152::_ParseABAlertLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ 16 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /22/N1/N9 EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == 4 )
			{
				hr = oMsgField.GetMFN22( sitField[0].szText, &(lpSitABLData->i64BeaconID) );

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN1( sitField[1].szText, &(lpSitABLData->iWaveForm) );
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMFN9( sitField[2].szText, &(lpSitABLData->dMQF) );

					if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[3].szText ) )
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
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSSit152::_ParseABAlertLine4( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ 16 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /23 EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == 2 )
			{
				hr = oMsgField.GetMF23( sitField[0].szText, &(lpSitABLData->acBeaconMsg[3]) );

				if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[1].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
			{
				hr = EMS_SIT_FIELD_COUNT_ERROR;
			}
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSSit152::_ParseABAlertLine5( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ EMS_MAX_SATS_PER_ABL_ALERT + 1 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, (EMS_MAX_SATS_PER_ABL_ALERT + 1), &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF6/MF6... EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == (EMS_MAX_SATS_PER_ABL_ALERT + 1) )
			{
				int i = 0;
				for( i = 0; (EMS_OK == hr) && (i < EMS_MAX_SATS_PER_ABL_ALERT); i++ )
				{
					hr = oMsgField.GetMF6( sitField[i].szText, &(lpSitABLData->aiSatIDs[i]) );
				}

				if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[ i ].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
			{
				hr = EMS_SIT_FIELD_COUNT_ERROR;
			}
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSSit152::_ParseABAlertLine6( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ EMS_MAX_LUTS_PER_ABL_ALERT + 1 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, (EMS_MAX_LUTS_PER_ABL_ALERT + 1), &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF11/MF11... EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == (EMS_MAX_LUTS_PER_ABL_ALERT + 1) )
			{
				int i = 0;
				for( ; (EMS_OK == hr) && (i < EMS_MAX_LUTS_PER_ABL_ALERT); i++ )
				{
					hr = oMsgField.GetMF11( sitField[i].szText, &(lpSitABLData->aiLutIDs[i]) );
				}

				if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[ i ].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
			{
				hr = EMS_SIT_FIELD_COUNT_ERROR;
			}
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}
