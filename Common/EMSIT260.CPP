/********************************************************************
*	Module:			emsit260.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit260  Class
*						Pass Schedule
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

#include "emsit260.h"
#include "sitfield.h"

#include "LogHelper.h"
#include "logmsgparam.h"
#include "sgenmsgs.h"
#include "convutility.h"


const int c_nAllocCount = 32;
const TCHAR c_szSit260HdrFmt[ ] = TEXT("/%03d/%04d/%s/%s/%03d");

const TCHAR c_szSit260APassLine1Fmt[ ] = TEXT("/%04ld/%03ld/%05ld/%s/%+05d/%+05d");
const TCHAR c_szSit260BPassLine1Fmt[ ] = TEXT("/%04ld/%02ld/%03ld/%05ld/%s/%+05d/%+05d");

const TCHAR c_szSit260PassLine2Fmt[ ] = TEXT("/%s/%+05d/%03d/%03d/%03d/%02d/%c%c%c");

const wchar_t* cwszSIT260A       = L"SIT260A";

const wchar_t* cwszLutID		 = L"MF#05A";
const wchar_t* cwszAntennaID	 = L"MF#71";
const wchar_t* cwszSatID		 = L"MF#06";
const wchar_t* cwszOrbitNo       = L"MF#07";
const wchar_t* cwszSatCount		 = L"MF#606";
const wchar_t* cwszAzimuthAOS    = L"MF#613";
const wchar_t* cwszAzimuthPeak	 = L"MF#614";
const wchar_t* cwszAzimuthLOS	 = L"MF#615";
const wchar_t* cwszMaxElevation  = L"MF#616";
const wchar_t* cwszPrePassOffset = L"MF#623";
const wchar_t* cwszStartOffset	 = L"MF#624";
const wchar_t* cwszStopOffset	 = L"MF#625";

CEMSSit260A::CEMSSit260A()
{
	SetSitNumber( 260 );
	SetSitCode( 0x260A );

	m_nAllocCount = m_nSatCount = 0;
	m_usage = EMSSchedUsageUnknown;
	m_lpData = 0;

	SetMaxLinesPerRecord( EMS_LINES_PER_SATELLITE );
}

CEMSSit260A::CEMSSit260A( CEMSSit260A* pSit )
{
	SetSitNumber( 260 );
	SetSitCode( 0x260A );

	m_nSatCount = m_nAllocCount = 0;
	m_lpData = 0;
	m_usage = EMSSchedUsageUnknown;
	
	try
	{
		ULONG ulAntennaID = 0;
		SetMsgHeader( pSit );

		SetScheduleUsage( pSit->GetScheduleUsage() );

		int nNewCount =  pSit->GetSatelliteCount();
		m_lpData = new EMSSIT260DATA[ nNewCount ];
		if ( m_lpData )
		{
			m_nAllocCount = nNewCount;

			for ( int i=0; i<nNewCount; i++ )
			{
				AddPass( pSit->GetPass( i ) );
			}
		}
	}
	catch(...)
	{
		if ( m_lpData )
		{
			delete[] m_lpData;
			m_lpData = 0;
		}
	}
}

CEMSSit260A::CEMSSit260A( CEMSSit260Base* pSit )
{
	SetSitNumber( 260 );
	SetSitCode( 0x260A );

	m_nSatCount = m_nAllocCount = 0;
	m_lpData = 0;
	m_usage = EMSSchedUsageUnknown;

	try
	{
		ULONG ulAntennaID = 0;
		SetMsgHeader( pSit );

		SetScheduleUsage( pSit->GetScheduleUsage() );

		int nNewCount =  pSit->GetSatelliteCount();
		m_lpData = new EMSSIT260DATA[ nNewCount ];
		if ( m_lpData )
		{
			m_nAllocCount = nNewCount;

			for ( int i=0; i<nNewCount; i++ )
			{
				AddPass( pSit->GetPass( i ) );
			}
		}
	}
	catch(...)
	{
		if ( m_lpData )
		{
			delete[] m_lpData;
			m_lpData = 0;
		}
	}
}

CEMSSit260A::~CEMSSit260A()
{
	if ( m_lpData )
	{
		delete [ ] m_lpData;
		m_lpData = 0;	
	}
}

void CEMSSit260A::Reset( void )
{
	m_nAllocCount = m_nSatCount = 0;

	m_usage = EMSSchedUsageUnknown;

	if ( m_lpData )
	{
		delete [ ] m_lpData;
		m_lpData = 0;	
	}
	CEMSSitMessageBase::Reset();

	SetSitNumber( 260 );
	SetSitCode( 0x260A );
}


EMS_RESULT CEMSSit260A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szAction[32];

		switch ( m_usage )
		{
			case EMSSchedUsageInstall:		lstrcpy( szAction, TEXT("INST") ); break;
			case EMSSchedUsageAppend:		lstrcpy( szAction, TEXT("APND") ); break;
			case EMSSchedUsageValidate:	lstrcpy( szAction, TEXT("VALD") ); break;

			default:
			case EMSSchedUsageUnknown:
			case EMSSchedUsageInfo:			lstrcpy( szAction, TEXT("INFO") ); break;
		}

		// MF01/MF02/MF03
		// MF04/MF05/MF04A/605/606
		
		int iMF606 = _ChkSatCountRange( m_nSatCount, cwszSatCount );

		sprintf( szBuffer, c_szSit260HdrFmt, 
						  GetSitNumber(), 
						  GetSitDestination(), 
						  GetSitCodeStr(), 
						  szAction,	
						  iMF606 );

		hr = WriteLine( lpStream, szBuffer );
		
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit260A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[ 256 ];

	if ( m_nSatCount > 0 )
	{
		CEMSSitMsgField msgField;

		if ( m_lpData && ( m_nSatCount <= m_nAllocCount ) )
		{
			for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
			{
				// MF05A/MF06/MF07/MF602/MF623/MF624

				ULONG ulMF05A = _ChkLutIdRange( m_lpData[i].ulLutID, cwszLutID );
				ULONG ulMF06  = _ChkSatIdRange( m_lpData[i].ulSatID, cwszSatID );
				ULONG ulMF07  = _ChkOrbitNoRange( m_lpData[i].ulOrbitNumber, cwszOrbitNo );
				int iMF623    = _ChkOffsetRange( m_lpData[i].dPrePassOffset, cwszPrePassOffset );
				int iMF624    = _ChkOffsetRange( m_lpData[i].dStartDataCollectionOffset, cwszStartOffset );

				sprintf( szBuffer, c_szSit260APassLine1Fmt, 
								ulMF05A,										// MF# 05A
								ulMF06,											// MF# 06
								ulMF07,											// MF# 07
								msgField.TextMF602( m_lpData[i].timeAOS ),		// MF# 602
								iMF623,											// MF# 623
								iMF624 );										// MF# 624

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
			     	// MF603/MF625/MF613/MF614/MF615/MF616/610

					int iMF625 = _ChkOffsetRange( m_lpData[i].dStopDataCollectionOffset, cwszStopOffset );
					int iMF613 = _ChkAZRange( m_lpData[i].degAzimuthAOS, cwszAzimuthAOS );
					int iMF614 = _ChkAZRange( m_lpData[i].degAzimuthPeak, cwszAzimuthPeak );
					int iMF615 = _ChkAZRange( m_lpData[i].degAzimuthLOS, cwszAzimuthLOS );
					int iMF616 = _ChkELRange( m_lpData[i].degMaxElevation, cwszMaxElevation );

					sprintf( szBuffer, c_szSit260PassLine2Fmt, 
								msgField.TextMF603( m_lpData[i].timeLOS ),		// MF# 603
								iMF625,											// MF# 625
								iMF613,											// MF# 613
								iMF614,											// MF# 614
								iMF615,											// MF# 615
								iMF616,											// MF# 616	
								m_lpData[i].wPassSchedOrigin,					// MF# 610_1
								m_lpData[i].wPassSchedStatus,					// MF# 610_2
								m_lpData[i].wPassProcessStatus );				// MF# 610_3

					hr = WriteLine( lpStream, szBuffer );
				}
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSit260A::AddPass( LPEMSSIT260DATA lpPass )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpPass )
	{
		if ( ( m_nSatCount + 1 ) > m_nAllocCount )
		{
			int nNewCount = m_nSatCount + c_nAllocCount;
			LPEMSSIT260DATA lpNewData = new EMSSIT260DATA[ nNewCount ];

			if ( lpNewData )
			{
				if ( m_lpData )
				{
					memcpy( lpNewData, m_lpData, m_nSatCount * sizeof( EMSSIT260DATA ) );
					delete [ ] m_lpData;
				}
				m_lpData = lpNewData;
				m_nAllocCount = nNewCount;
			}
		}
		if ( m_lpData )
		{
			memcpy( &m_lpData[ m_nSatCount++ ], lpPass, sizeof( EMSSIT260DATA ) );
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

LPEMSSIT260DATA CEMSSit260A::GetPass( int nIndex )
{
	LPEMSSIT260DATA lpData = 0;
	
	if ( ( nIndex < m_nSatCount ) && ( nIndex < m_nAllocCount ) && m_lpData )
	{
		lpData = &m_lpData[ nIndex ];
	}
	
	return lpData;
}

EMS_RESULT CEMSSit260A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		if ( m_nSatCount > 0 )
		{
			m_lpData = new EMSSIT260DATA[ m_nSatCount ];

			if ( m_lpData )
			{
				memset( m_lpData, 0, sizeof( EMSSIT260DATA ) * m_nSatCount );

				m_nAllocCount = m_nSatCount;

				for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
				{
					hr = _ParsePassLine1( lpTokenizer, &m_lpData[i] );

					if ( hr == EMS_OK )
						hr = _ParsePassLine2( lpTokenizer, &m_lpData[i] );
				}
			}

		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSit260A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

		// should find /MF4/MF5/MF4A/MF605/MF606 eol

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
				
				if (lstrcmp(sitField[3].szText, TEXT("/VALI")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/EXEC")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/INST")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/APND")) == 0)
				{
					m_usage = EMSSchedUsageAppend;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/VALD")) == 0)
				{
					m_usage = EMSSchedUsageValidate;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/INFO")) == 0)
				{
					m_usage = EMSSchedUsageInfo;
				}
				else
				{
					m_usage = EMSSchedUsageUnknown;
				}
			}

			if ( hr == EMS_OK )
			{
				// use mf605 parameters

				hr = msgField.GetMF606( sitField[4].szText, &nCount );
				
			}


		


			if ( hr == EMS_OK )
			{
				m_nSatCount = nCount;
					
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

EMS_RESULT CEMSSit260A::_ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATA lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0, nNumber;

		// should find /MF5A/MF6/MF7/MF602/MF623/MF624 eol

		if ( nFldCount == 7 )
		{
			hr = msgField.GetMF5A( sitField[0].szText, &nNumber );

			if ( hr == EMS_OK )
			{
				lpData->ulLutID = (ULONG)nNumber;

				hr = msgField.GetMF6( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulSatID = (ULONG)nNumber;

				hr = msgField.GetMF7( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitNumber = (ULONG)nNumber;

				hr = msgField.GetMF602( sitField[3].szText, &(lpData->timeAOS) );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF623( sitField[4].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dPrePassOffset = (double)nNumber;

				hr = msgField.GetMF624( sitField[5].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dStartDataCollectionOffset = (double)nNumber;

				if ( !msgField.IsEOL( sitField[6].szText ) )
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

EMS_RESULT CEMSSit260A::_ParsePassLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATA lpData )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0, nNumber;

		// should find /MF603/MF625/MF613/MF614/MF615/MF616/MF610 eol

		if ( nFldCount == 8 )
		{
			EMSSITMF610 mf610;

			hr = msgField.GetMF603( sitField[0].szText, &(lpData->timeLOS) );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF625( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dStopDataCollectionOffset = (double)nNumber;

				hr = msgField.GetMF613( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthAOS = (double)nNumber;

				hr = msgField.GetMF614( sitField[3].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthPeak = (double)nNumber;

				hr = msgField.GetMF615( sitField[4].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthLOS = (double)nNumber;

				hr = msgField.GetMF616( sitField[5].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degMaxElevation = (double)nNumber;

				hr = msgField.GetMF610( sitField[6].szText, &mf610 );
			}

			if ( hr == EMS_OK )
			{
				lpData->wPassSchedOrigin = mf610.cValue[0];

				lpData->wPassSchedStatus = mf610.cValue[1];

				lpData->wPassProcessStatus = mf610.cValue[2];

				if ( !msgField.IsEOL( sitField[7].szText ) )
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

int
CEMSSit260A::_ChkOffsetRange( const double dOffset, const wchar_t* cwszText )
{
	double dRet =  dOffset;

	if(( dOffset < -9999.0) || ( dOffset > 9999.0 ))
	{
		if( dOffset < -9999.0 ) dRet = -9999.0;
		else if( dOffset > 9999.0 ) dRet = 9999.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dOffset );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int 
CEMSSit260A::_ChkAZRange( const double dAzimuth, const wchar_t* cwszText )
{
	double dRet =  dAzimuth;

	// negative azimuth angles do exist and are ok
	if( dRet < 0.0 ) dRet += 360.0;

	if(( dRet < 0.0 ) || ( dRet > 360.0 ))
	{
		if( dRet < 0.0 ) dRet = 0.0;
		else if( dRet > 360.0 ) dRet = 360.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dAzimuth );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int
CEMSSit260A::_ChkELRange( const double dElevation, const wchar_t* cwszText )
{
	double dRet = dElevation;

	if(( dElevation < 0.0 ) || ( dElevation > 90.0 ))
	{
		if( dElevation < 0.0 ) dRet = 0.0;
		else if( dElevation > 90.0 ) dRet = 90.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dElevation );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int 
CEMSSit260A::_ChkSatCountRange( const int iCount, const wchar_t* cwszText )
{
    int iRet = iCount;

	if(( iCount < 0 ) || ( iCount > 999 ))
	{
 		iRet = min( iCount, 999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( iCount );
		param.Add( iRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return iRet;
}

ULONG
CEMSSit260A::_ChkLutIdRange( const ULONG ulLutId, const wchar_t* cwszText )
{
	ULONG ulRet = ulLutId;

	if(( ulLutId < 0 ) || ( ulLutId > 9999 ))
	{
		ulRet = min( ulLutId, 9999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( ulLutId );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}

ULONG 
CEMSSit260A::_ChkSatIdRange( const ULONG ulSatId, const wchar_t* cwszText )
{
	ULONG ulRet = ulSatId;

	if(( ulSatId < 0 ) || ( ulSatId > 999 ))
	{
		ulRet = min( ulSatId, 999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( ulSatId );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}


ULONG
CEMSSit260A::_ChkOrbitNoRange( const ULONG ulOrbitNo, const wchar_t* cwszText )
{
	ULONG ulRet = ulOrbitNo;

	if(( ulOrbitNo < 0 ) || ( ulOrbitNo > 99999 ))
	{
		ulRet = min( ulOrbitNo, 99999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A);
		param.AddString( cwszText );
		param.Add( ulOrbitNo );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}

CEMSSit260Base::CEMSSit260Base( ) : m_nSatCount(0), m_nAllocCount(0), 
								m_usage(EMSSchedUsageUnknown), m_lpData(0)
{
}

CEMSSit260Base::~CEMSSit260Base( )
{
	if ( m_lpData )
	{
		delete [ ] m_lpData;
		m_lpData = 0;
	}
}

void CEMSSit260Base::Reset( void )
{
	m_nAllocCount = m_nSatCount = 0;

	m_usage = EMSSchedUsageUnknown;

	if ( m_lpData )
	{
		delete [ ] m_lpData;
		m_lpData = 0;	
	}
	CEMSSitMessageBase::Reset();
}



EMS_RESULT CEMSSit260Base::AddPass( LPEMSSIT260DATA lpPass )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpPass )
	{
		EMSSIT260DATAUNION dataEx;

		memset( &dataEx, 0, sizeof( dataEx ) );

		memcpy( &dataEx.x.data, lpPass, sizeof( dataEx.x.data ) );

		hr = AddPassEx( &dataEx.x.dataEx );

	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit260Base::AddPassEx( LPEMSSIT260DATAEX lpPass )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpPass )
	{
		if ( ( m_nSatCount + 1 ) > m_nAllocCount )
		{
			int nNewCount = m_nSatCount + c_nAllocCount;
			LPEMSSIT260DATAUNION lpNewData = new EMSSIT260DATAUNION[ nNewCount ];

			if ( lpNewData )
			{
				if ( m_lpData )
				{
					memcpy( lpNewData, m_lpData, m_nSatCount * sizeof( EMSSIT260DATAUNION ) );
					delete [ ] m_lpData;
				}
				m_lpData = lpNewData;
				m_nAllocCount = nNewCount;
			}
		}

		if ( m_lpData )
		{
			memcpy( &m_lpData[ m_nSatCount ].x.dataEx, lpPass, sizeof( EMSSIT260DATAEX ) );

			m_nSatCount++;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


LPEMSSIT260DATA CEMSSit260Base::GetPass( int nIndex )
{
	LPEMSSIT260DATA lpData = 0;
	
	if ( ( nIndex < m_nSatCount ) && ( nIndex < m_nAllocCount ) && m_lpData )
	{
		lpData = &m_lpData[ nIndex ].x.data;
	}
	
	return lpData;
}

LPEMSSIT260DATAEX CEMSSit260Base::GetPassEx( int nIndex )
{
	LPEMSSIT260DATAEX lpData = 0;
	
	if ( ( nIndex < m_nSatCount ) && ( nIndex < m_nAllocCount ) && m_lpData )
	{
		lpData = &m_lpData[ nIndex ].x.dataEx;
	}
	
	return lpData;
}

EMS_RESULT CEMSSit260Base::GenerateSitBody( IEMSSeqStream *lpStream )
{
	return EMS_NOT_IMPLEMENTED;
}

EMS_RESULT CEMSSit260Base::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szAction[32];

		switch ( m_usage )
		{
			case EMSSchedUsageInstall:		lstrcpy( szAction, TEXT("INST") ); break;
			case EMSSchedUsageAppend:		lstrcpy( szAction, TEXT("APND") ); break;
			case EMSSchedUsageValidate:	lstrcpy( szAction, TEXT("VALD") ); break;

			default:
			case EMSSchedUsageUnknown:
			case EMSSchedUsageInfo:			lstrcpy( szAction, TEXT("INFO") ); break;
		}

		// MF01/MF02/MF03
		// MF04/MF05/MF04A/605/606
		
		int iMF606 = _ChkSatCountRange( m_nSatCount, cwszSatCount );

		sprintf( szBuffer, c_szSit260HdrFmt, 
						  GetSitNumber(), 
						  GetSitDestination(), 
						  GetSitCodeStr(), 
						  szAction,	
						  iMF606 );

		hr = WriteLine( lpStream, szBuffer );
		
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit260Base::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
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

		// should find /MF4/MF5/MF4A/MF605/MF606 eol

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
				
				if (lstrcmp(sitField[3].szText, TEXT("/VALI")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/EXEC")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/INST")) == 0)
				{
					m_usage = EMSSchedUsageInstall;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/APND")) == 0)
				{
					m_usage = EMSSchedUsageAppend;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/VALD")) == 0)
				{
					m_usage = EMSSchedUsageValidate;
				}
				else if (lstrcmp(sitField[3].szText, TEXT("/INFO")) == 0)
				{
					m_usage = EMSSchedUsageInfo;
				}
				else
				{
					m_usage = EMSSchedUsageUnknown;
				}
			}

			if ( hr == EMS_OK )
			{
				// use mf605 parameters

				hr = msgField.GetMF606( sitField[4].szText, &nCount );
				
			}

			if ( hr == EMS_OK )
			{
				m_nSatCount = nCount;
					
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

EMS_RESULT CEMSSit260Base::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		if ( m_nSatCount > 0 )
		{
			m_lpData = new EMSSIT260DATAUNION[ m_nSatCount ];

			if ( m_lpData )
			{
				memset( m_lpData, 0, sizeof( EMSSIT260DATAUNION ) * m_nSatCount );

				m_nAllocCount = m_nSatCount;

				for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
				{
					hr = _ParsePassLine1( lpTokenizer, &m_lpData[i].x.dataEx );

					if ( hr == EMS_OK )
						hr = _ParsePassLine2( lpTokenizer, &m_lpData[i].x.dataEx );
				}
			}

		}
		else
			hr = EMS_SIT_SYNTAX_ERROR;
	}

	return hr;
}


int CEMSSit260Base::_ChkOffsetRange( const double dOffset, const wchar_t* cwszText )
{
	double dRet =  dOffset;

	if(( dOffset < -9999.0) || ( dOffset > 9999.0 ))
	{
		if( dOffset < -9999.0 ) dRet = -9999.0;
		else if( dOffset > 9999.0 ) dRet = 9999.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dOffset );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int CEMSSit260Base::_ChkAZRange( const double dAzimuth, const wchar_t* cwszText )
{
	double dRet =  dAzimuth;

	// negative azimuth angles do exist and are ok
	if( dRet < 0.0 ) dRet += 360.0;

	if(( dRet < 0.0 ) || ( dRet > 360.0 ))
	{
		if( dRet < 0.0 ) dRet = 0.0;
		else if( dRet > 360.0 ) dRet = 360.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dAzimuth );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int CEMSSit260Base::_ChkELRange( const double dElevation, const wchar_t* cwszText )
{
	double dRet = dElevation;

	if(( dElevation < 0.0 ) || ( dElevation > 90.0 ))
	{
		if( dElevation < 0.0 ) dRet = 0.0;
		else if( dElevation > 90.0 ) dRet = 90.0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.AddDouble( dElevation );
		param.AddDouble( dRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return int(dRet);
}

int CEMSSit260Base::_ChkSatCountRange( const int iCount, const wchar_t* cwszText )
{
    int iRet = iCount;

	if(( iCount < 0 ) || ( iCount > 999 ))
	{
 		iRet = min( iCount, 999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( iCount );
		param.Add( iRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return iRet;
}

ULONG CEMSSit260Base::_ChkAntennaIdRange( const ULONG ulAntennaId, const wchar_t* cwszText )
{
	ULONG ulRet = ulAntennaId;

	if(( ulAntennaId < 0 ) || ( ulAntennaId > 99 ))
	{
		ulRet = min( ulAntennaId, 99 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( ulAntennaId );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}

ULONG CEMSSit260Base::_ChkLutIdRange( const ULONG ulLutId, const wchar_t* cwszText )
{
	ULONG ulRet = ulLutId;

	if(( ulLutId < 0 ) || ( ulLutId > 9999 ))
	{
		ulRet = min( ulLutId, 9999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( ulLutId );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}

ULONG CEMSSit260Base::_ChkSatIdRange( const ULONG ulSatId, const wchar_t* cwszText )
{
	ULONG ulRet = ulSatId;

	if(( ulSatId < 0 ) || ( ulSatId > 999 ))
	{
		ulRet = min( ulSatId, 999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A );
		param.AddString( cwszText );
		param.Add( ulSatId );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}


ULONG CEMSSit260Base::_ChkOrbitNoRange( const ULONG ulOrbitNo, const wchar_t* cwszText )
{
	ULONG ulRet = ulOrbitNo;

	if(( ulOrbitNo < 0 ) || ( ulOrbitNo > 99999 ))
	{
		ulRet = min( ulOrbitNo, 99999 );

		CEMSLogMsgParam param(4);
		param.AddString( cwszSIT260A);
		param.AddString( cwszText );
		param.Add( ulOrbitNo );
		param.Add( ulRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return ulRet;
}

EMS_RESULT CEMSSit260Base::_ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData )
{
	return EMS_NOT_IMPLEMENTED;
}

EMS_RESULT CEMSSit260Base::_ParsePassLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0, nNumber;

		// should find /MF603/MF625/MF613/MF614/MF615/MF616/MF610 eol

		if ( nFldCount == 8 )
		{
			EMSSITMF610 mf610;

			hr = msgField.GetMF603( sitField[0].szText, &(lpData->timeLOS) );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF625( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dStopDataCollectionOffset = (double)nNumber;

				hr = msgField.GetMF613( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthAOS = (double)nNumber;

				hr = msgField.GetMF614( sitField[3].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthPeak = (double)nNumber;

				hr = msgField.GetMF615( sitField[4].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degAzimuthLOS = (double)nNumber;

				hr = msgField.GetMF616( sitField[5].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->degMaxElevation = (double)nNumber;

				hr = msgField.GetMF610( sitField[6].szText, &mf610 );
			}

			if ( hr == EMS_OK )
			{
				lpData->wPassSchedOrigin = mf610.cValue[0];

				lpData->wPassSchedStatus = mf610.cValue[1];

				lpData->wPassProcessStatus = mf610.cValue[2];

				if ( !msgField.IsEOL( sitField[7].szText ) )
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


bool CEMSSit260Base::ForSingleAntenna()
{
	bool	bSingle = true;
	int		nCount =  GetSatelliteCount();
	ULONG	ulAntennaID = 0;

	for ( int i=0; i<nCount; i++ )
	{
		LPEMSSIT260DATAEX	pPass = GetPassEx( i );
		if ( 0 == i )
		{
			ulAntennaID = pPass->ulAntennaID;
		}
		else if ( ulAntennaID != pPass->ulAntennaID )
		{
			bSingle = false;
			break;
		}
	}
	return bSingle;
}

CEMSSit260B::CEMSSit260B()
{
	SetSitNumber( 260 );
	SetSitCode( 0x260B );
}

CEMSSit260B::~CEMSSit260B()
{
	Reset( );
}

void CEMSSit260B::Reset( void )
{
	CEMSSit260Base::Reset();

	SetSitNumber( 260 );
	SetSitCode( 0x260B );
}

EMS_RESULT CEMSSit260B::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[ 256 ];

	if ( m_nSatCount > 0 )
	{
		CEMSSitMsgField msgField;

		if ( m_lpData && ( m_nSatCount <= m_nAllocCount ) )
		{
			for ( int i = 0; ( hr == EMS_OK ) && ( i < m_nSatCount ); i++ )
			{
				// MF05A/MF71/MF06/MF07/MF602/MF623/MF624

				ULONG ulMF05A = _ChkLutIdRange( m_lpData[i].x.dataEx.ulLutID, cwszLutID );
				ULONG ulMF71 = _ChkAntennaIdRange( m_lpData[i].x.dataEx.ulAntennaID, cwszAntennaID );
				ULONG ulMF06  = _ChkSatIdRange( m_lpData[i].x.dataEx.ulSatID, cwszSatID );
				ULONG ulMF07  = _ChkOrbitNoRange( m_lpData[i].x.dataEx.ulOrbitNumber, cwszOrbitNo );
				int iMF623    = _ChkOffsetRange( m_lpData[i].x.dataEx.dPrePassOffset, cwszPrePassOffset );
				int iMF624    = _ChkOffsetRange( m_lpData[i].x.dataEx.dStartDataCollectionOffset, cwszStartOffset );

				sprintf( szBuffer, c_szSit260BPassLine1Fmt, 
								ulMF05A,										// MF# 05A
								ulMF71,										// MF# 71 - Antenna ID
								ulMF06,											// MF# 06
								ulMF07,											// MF# 07
								msgField.TextMF602( m_lpData[i].x.dataEx.timeAOS ),		// MF# 602
								iMF623,											// MF# 623
								iMF624 );										// MF# 624

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
				{
			     	// MF603/MF625/MF613/MF614/MF615/MF616/610

					int iMF625 = _ChkOffsetRange( m_lpData[i].x.dataEx.dStopDataCollectionOffset, cwszStopOffset );
					int iMF613 = _ChkAZRange( m_lpData[i].x.dataEx.degAzimuthAOS, cwszAzimuthAOS );
					int iMF614 = _ChkAZRange( m_lpData[i].x.dataEx.degAzimuthPeak, cwszAzimuthPeak );
					int iMF615 = _ChkAZRange( m_lpData[i].x.dataEx.degAzimuthLOS, cwszAzimuthLOS );
					int iMF616 = _ChkELRange( m_lpData[i].x.dataEx.degMaxElevation, cwszMaxElevation );

					sprintf( szBuffer, c_szSit260PassLine2Fmt, 
								msgField.TextMF603( m_lpData[i].x.dataEx.timeLOS ),		// MF# 603
								iMF625,											// MF# 625
								iMF613,											// MF# 613
								iMF614,											// MF# 614
								iMF615,											// MF# 615
								iMF616,											// MF# 616	
								m_lpData[i].x.dataEx.wPassSchedOrigin,					// MF# 610_1
								m_lpData[i].x.dataEx.wPassSchedStatus,					// MF# 610_2
								m_lpData[i].x.dataEx.wPassProcessStatus );				// MF# 610_3

					hr = WriteLine( lpStream, szBuffer );
				}
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}

	return hr;
}

EMS_RESULT CEMSSit260B::_ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;
		int nCount = 0, nNumber;

		// should find /MF5A/MF71/MF6/MF7/MF602/MF623/MF624 eol

		if ( 8 == nFldCount )
		{
			hr = msgField.GetMF5A( sitField[0].szText, &nNumber );

			if ( hr == EMS_OK )
			{
				lpData->ulLutID = (ULONG)nNumber;

				hr = msgField.GetMF71( sitField[1].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulAntennaID = (ULONG)nNumber;

				hr = msgField.GetMF6( sitField[2].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulSatID = (ULONG)nNumber;

				hr = msgField.GetMF7( sitField[3].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->ulOrbitNumber = (ULONG)nNumber;

				hr = msgField.GetMF602( sitField[4].szText, &(lpData->timeAOS) );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF623( sitField[5].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dPrePassOffset = (double)nNumber;

				hr = msgField.GetMF624( sitField[6].szText, &nNumber );
			}

			if ( hr == EMS_OK )
			{
				lpData->dStartDataCollectionOffset = (double)nNumber;

				if ( !msgField.IsEOL( sitField[7].szText ) )
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
