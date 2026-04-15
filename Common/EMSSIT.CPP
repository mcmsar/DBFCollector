/********************************************************************
*	Module:			emssit.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of SIT Message Classes
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include "emscom.h"
#include "emstypes.h"
#include "lineterminator.h"
#include "emssit.h"
#include "sittoken.h"
#include "sitfield.h"

const TCHAR c_szNL[]				= { 13, 13, 10, 0 };
const TCHAR c_szEndMsg[]			= TEXT("/ENDMSG");
const TCHAR c_szLastSit[] 		= TEXT("/LASSIT");
const TCHAR c_szNewSit[] 		  	= TEXT("/NEWSIT");
const TCHAR c_szMsgHeaderFmt[]	= TEXT("/%05d %05d/%04d/%02d %03d %02d%02d");
const TCHAR c_szMsgHeaderHiResFmt[]	= TEXT("/%05d %05d/%04d/%02d %03d %02d%02d%02d");
const int	c_nAllocCount			= 33;
const BOOL	c_bPeekOnly				= TRUE;

CEMSSitMessageBase::CEMSSitMessageBase( )
{
	m_bUseHiResTime = FALSE;

	m_nMaxLineSize = EMS_DEFAULT_SIT_LINE_SIZE;
	m_nHeaderLines = EMS_DEFAULT_SIT_HEADER_LINES;
	m_nTrailerLines = EMS_DEFAULT_SIT_TRAILER_LINES;
	m_nMaxMsgSize = EMS_MAX_SIT_MSG_LENGTH;
	m_nMaxLinesPerRecord = EMS_DEFAULT_SIT_LINES_RECORD;
	m_bAutoSend = FALSE;
	m_nSitNumber = 0;

	_Reset();
}

CEMSSitMessageBase::~CEMSSitMessageBase()
{
	_Reset();
}

void CEMSSitMessageBase::_Reset( void )
{
	m_nCurrMsgNumber = m_nLastMsgNumber = 0;
	m_nReportingMCC = 0;
//	m_nSitNumber = 0;
	m_sitCode = 0x0;
	m_nSitDestination = 0;
	m_timeTransmit.ResetTime();
}

void CEMSSitMessageBase::Reset( void )
{
	_Reset();
}

void CEMSSitMessageBase::SetMsgHeader( CEMSSitMessageBase *lpSitMsg )
{
	if ( lpSitMsg )
	{
		m_nCurrMsgNumber = lpSitMsg->m_nCurrMsgNumber;

		m_nLastMsgNumber = lpSitMsg->m_nLastMsgNumber;

		m_nReportingMCC = lpSitMsg->m_nReportingMCC;

		m_timeTransmit = lpSitMsg->m_timeTransmit;
	}
}

EMS_RESULT CEMSSitMessageBase::GenerateMsgHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		EMSTIMEFIELDS timeFields;
		int nYear;
		time_t timeNow;

		time( &timeNow );
		m_timeTransmit.SetTimeSeconds( timeNow );
		m_timeTransmit.GetTime( &timeFields );

		if ( timeFields.nYear >= 2000 )
			nYear = timeFields.nYear - 2000;
		else
			nYear = timeFields.nYear - 1900;

//		if ( m_bUseHiResTime && m_sitCode )

		if ( m_bUseHiResTime )
		{
			_stprintf( szBuffer, c_szMsgHeaderHiResFmt, m_nCurrMsgNumber, 
							m_nLastMsgNumber,	m_nReportingMCC, nYear,
							timeFields.nJulianDay, timeFields.nHour, 
							timeFields.nMinute, timeFields.nSecond );
		}
		else
		{
			_stprintf( szBuffer,c_szMsgHeaderFmt, m_nCurrMsgNumber, 
							m_nLastMsgNumber,	m_nReportingMCC, nYear,
							timeFields.nJulianDay, timeFields.nHour, timeFields.nMinute );
		}
		
		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::GenerateSitBody( IEMSSeqStream *lpStream )
{
	return  ( lpStream ) ? EMS_OK : EMS_INVALID_STREAM;
}

EMS_RESULT CEMSSitMessageBase::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	return  ( lpStream ) ? EMS_OK : EMS_INVALID_STREAM;
}

EMS_RESULT CEMSSitMessageBase::GenerateNewSit( IEMSSeqStream *lpStream )
{
	return WriteLine( lpStream, c_szNewSit );
}

EMS_RESULT CEMSSitMessageBase::WriteLine( IEMSSeqStream *lpStream, LPCTSTR lpcszLine )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		if ( lpcszLine )
		{
			long lLength = lstrlen( lpcszLine );

			if ( lLength <= _GetMaxSitLineLength() )
			{
				ULONG ulWritten = 0;

				hr = lpStream->Write( (LPBYTE)lpcszLine, lLength, &ulWritten );

				if ( hr == EMS_OK )
					hr = lpStream->Write( (LPBYTE)m_LT.WriteEOL(), lstrlen( m_LT.WriteEOL() ), &ulWritten );
			}
			else
				hr = EMS_LINE_LIMIT_EXCEEDED;
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::GenerateSitTrailer( IEMSSeqStream *lpStream )
{
	return WriteLine( lpStream, c_szLastSit );
}

EMS_RESULT CEMSSitMessageBase::GenerateMsgTrailer( IEMSSeqStream *lpStream )
{
	return WriteLine( lpStream, c_szEndMsg );
}

EMS_RESULT CEMSSitMessageBase::GenerateSit( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	try 
	{
		if ( ( hr =	GenerateSitHeader( lpStream) ) != EMS_OK )
			throw hr;

		if ( ( hr =	GenerateSitBody( lpStream ) ) != EMS_OK )
			throw hr;
	}

	catch ( EMS_RESULT errCode )
	{
		hr = errCode;
	}

	catch ( ... )
	{
		hr = EMS_UNKNOWN_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSitMessageBase::Generate( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		try
		{
			if ( ( hr =	GenerateMsgHeader( lpStream) ) != EMS_OK )
				throw hr;

			if ( ( hr =	GenerateSit( lpStream) ) != EMS_OK )
				throw hr;

			if ( ( hr =	GenerateSitTrailer( lpStream ) ) != EMS_OK )
				throw hr;

			if ( ( hr =	GenerateMsgTrailer( lpStream) ) != EMS_OK )
				throw hr;
		}

		catch ( EMS_RESULT errCode )
		{
			hr = errCode;
		}

		catch ( ... )
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

LPCTSTR CEMSSitMessageBase::GetSitCodeStr( void )
{
	sprintf( m_szSitCodeStr, TEXT("%X"), m_sitCode );

	return (LPCTSTR)m_szSitCodeStr;
}

EMS_RESULT CEMSSitMessageBase::ParseMsgStart( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
//	TCHAR szBuffer[ 256 ];
	BOOL bValidHdr = ( ParseMsgHeader( lpTokenizer, c_bPeekOnly ) == EMS_OK );

	while ( !bValidHdr && ( hr == EMS_OK ) )
	{
		// need to discard the previous line - so reset it

		lpTokenizer->ResetUnReadFields();

		hr = ParseMsgHeader( lpTokenizer, c_bPeekOnly );

		switch ( hr )
		{
			case EMS_OK: 	bValidHdr = TRUE; break;
			case EMS_EOF: 	break;
			default:			bValidHdr = FALSE; hr = EMS_OK; break;
		}

	}

	return ( hr == EMS_OK ) ? hr : EMS_SIT_MISSING_MSGHDR;
}

EMS_RESULT CEMSSitMessageBase::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::ParseMsgHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMsgField msgField;
	int nFldCount = 0;
	EMSSITFIELD sitField[ 16 ];

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		EMSTIME timeTemp;

		// should find /MF1/MF2/MF3 eol

		if ( nFldCount == 4 )
		{
			hr = msgField.GetMF1( sitField[0].szText, &m_nCurrMsgNumber, &m_nLastMsgNumber );

			if ( hr == EMS_OK )
				hr = msgField.GetMF2( sitField[1].szText, &m_nReportingMCC );
		
			if ( hr == EMS_OK )
				hr = msgField.GetMF3( sitField[2].szText, &timeTemp );

			if ( hr == EMS_OK )
				m_timeTransmit.SetTime( timeTemp );
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;


		if ( bPeek )
			UnReadSitLine( lpTokenizer, sitField, nFldCount );
	}


	return hr;
}

EMS_RESULT CEMSSitMessageBase::ParseSitTrailer( CEMSSitTokenizer *lpTokenizer,
												BOOL *lpbLastSit )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMsgField msgField;
	int nFldCount = 0;
	EMSSITFIELD sitField[ 16 ];
	BOOL bLastSit = TRUE;

	if ( lpTokenizer )
	{
		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /LASSIT or /NEWSIT

			if ( lstrcmpi( sitField[0].szText, c_szNewSit ) == 0 )
			{
				bLastSit = FALSE;
			}
			else if ( lstrcmpi( sitField[0].szText, c_szLastSit ) == 0 )
			{
				bLastSit = TRUE;
			}
			else
				hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpbLastSit )
		*lpbLastSit = bLastSit;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::ParseMsgTrailer( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMsgField msgField;
	int nFldCount = 0;
	EMSSITFIELD sitField[ 16 ];

	if ( lpTokenizer )
	{
		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /ENDMSG

			if ( lstrcmpi( sitField[0].szText, c_szEndMsg ) == 0 )
			{
			}
			else
				hr = EMS_SIT_SYNTAX_ERROR;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::UnReadSitLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITFIELD lpFld, int nCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTokenizer && lpFld )
	{
		for ( int i = nCount-1; i >= 0; i-- ) 
		{
			lpTokenizer->UnReadField( lpFld[i].szText, lpFld[i].nLength );
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSSitMessageBase::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5 and possibly /MF4A ????

		hr = msgField.GetMF4( sitField[0].szText, &m_nSitNumber );

		if ( hr == EMS_OK )
			hr = msgField.GetMF5( sitField[1].szText, &m_nSitDestination );

		if ( hr == EMS_OK )
		{
			hr = msgField.GetMF4A( sitField[2].szText, &m_sitCode );

			if ( ( hr == EMS_SIT_SYNTAX_ERROR ) || ( hr == EMS_UNKNOWN_SIT_CODE ) )
			{
				m_sitCode = 0;
				hr = EMS_OK;
			}
		}

		if ( bPeek )
			UnReadSitLine( lpTokenizer, sitField, nFldCount );
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::ReadSitLine( CEMSSitTokenizer *lpTokenizer,  LPTSTR lpszBuffer, int nMax, int *lpnLength )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0;

	if ( lpTokenizer && lpszBuffer && nMax )
	{
		hr = lpTokenizer->ReadLine( lpszBuffer, (ULONG)nMax, &ulCount );

		if ( ( hr == EMS_OK ) && ( ulCount > _GetMaxSitLineLength() ) )
			hr = EMS_SIT_LINE_EXCEEDED;
	}

	if ( lpnLength )
		*lpnLength = (int)ulCount;

	return hr;
}

EMS_RESULT CEMSSitMessageBase::ReadSitLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITFIELD lpFld, int nMax, int *lpnCount )
{
	EMS_RESULT hr = EMS_OK;
	int n=0;
	ULONG ulLength = 0;

	if ( lpTokenizer && lpFld && nMax )
	{	
		hr = lpTokenizer->ReadField( lpFld[n].szText, sizeof( lpFld[0].szText ) /
					sizeof( lpFld[0].szText[0] ), &ulLength );

		while ( ( hr == EMS_OK ) && ( n < nMax ) )
		{
			lpFld[ n++ ].nLength = (int)ulLength;			

			if ( m_LT.IsEOL(lpFld[n-1].szText[0]) )
				hr = EMS_EOL;
			else
				hr = lpTokenizer->ReadField( lpFld[n].szText, sizeof( lpFld[0].szText ) /
						sizeof( lpFld[0].szText[0] ), &ulLength );
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpnCount )
		*lpnCount = n;

	return ( hr == EMS_EOL ) ? EMS_OK : hr ;
}

int CEMSSitMessageBase::GetMaxRecordCount( void )
{
	int nMaxCount = 0;
	
	if( 0 < m_nMaxLineSize && 0 < m_nMaxLinesPerRecord )
	{
		// The maximum number of records permitted in the message is:
		//		(MsgFileSize/LineSize - (HeaderLines + TrailerLines))/LinesPerRecord
		nMaxCount = ( m_nMaxMsgSize/m_nMaxLineSize - (m_nHeaderLines + m_nTrailerLines) ) / m_nMaxLinesPerRecord;
	}

	return nMaxCount;
}

CEMSSitAlertMessageBase::CEMSSitAlertMessageBase()
{
	m_nAlertCount = m_nMaxAlertCount = 0;
	m_nSatID = 0;
	m_nPass = 0;
	m_lpSoln = 0;
	m_nAllocCount = 0;
	
	SetMaxLinesPerRecord( EMS_DEFAULT_MAX_LINES_PER_ALERT );
}

CEMSSitAlertMessageBase::~CEMSSitAlertMessageBase()
{
}

void CEMSSitAlertMessageBase::Reset( void )
{
	m_nAlertCount = 0;
	m_nSatID = 0;
	m_nPass = 0;

	if ( m_lpSoln )
	{
		delete [ ] m_lpSoln;
		m_lpSoln = 0;
	}
	m_nAllocCount = 0;

	CEMSSitMessageBase::Reset();
}


EMS_RESULT CEMSSitAlertMessageBase::AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln )
{
	EMS_RESULT hr = EMS_OK;

	if ( GetAlertCount() < GetMaxAlertCount() )
	{
		if ( ( GetAlertCount() + 1 ) > m_nAllocCount )
		{
			int nNewCount = GetAlertCount() + c_nAllocCount;
			LPEMSSITLOCALERTSOLUTION lpNewData = new EMSSITLOCALERTSOLUTION[ nNewCount ];

			if ( lpNewData )
			{
				if ( m_lpSoln )
				{
					memcpy( lpNewData, m_lpSoln, GetAlertCount() * sizeof( EMSSITLOCALERTSOLUTION ) );

					delete [ ] m_lpSoln;
				}
				m_lpSoln = lpNewData;

				m_nAllocCount = nNewCount;
			}
		}

		if ( m_lpSoln )
		{
			memcpy( &m_lpSoln[ GetAlertCount() ], lpSoln, sizeof( EMSSITLOCALERTSOLUTION ) );

			IncrAlertCount();
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_SIT_ALERT_LIMIT;

	return hr;
}

EMS_RESULT CEMSSitAlertMessageBase::GetSolution( LPEMSSITLOCALERTSOLUTION lpSoln, int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpSoln && _GetSolutionPtr( nIndex ) ) 
		memcpy( lpSoln, _GetSolutionPtr( nIndex ), sizeof( EMSSITLOCALERTSOLUTION ) );
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

LPEMSSITLOCALERTSOLUTION CEMSSitAlertMessageBase::_GetSolutionPtr( int nIndex )
{
	LPEMSSITLOCALERTSOLUTION lpSoln = 0;

	if ( m_lpSoln && ( nIndex >= 0 ) && ( nIndex < GetAlertCount() ) )
		lpSoln = &m_lpSoln[ nIndex ];

	return lpSoln;
}

int CEMSSitAlertMessageBase::_AllocSolutions( int nCount )
{
	if ( nCount > GetMaxAlertCount() )
		nCount = GetMaxAlertCount( );

	m_lpSoln = new EMSSITLOCALERTSOLUTION[ nCount ];

	if ( m_lpSoln )
	{
		memset( m_lpSoln , 0, sizeof( EMSSITLOCALERTSOLUTION ) * nCount );

		m_nAllocCount = nCount;

		SetAlertCount( m_nAllocCount );
	}

	return m_nAllocCount;
}

int CEMSSitAlertMessageBase::GetMaxAlertCount()
{
	return GetMaxRecordCount();
}




