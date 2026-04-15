/********************************************************************
*	Module:			emsit722.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit722
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	Copyright (c) 2006 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include <stdio.h>
#include <array.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit722.h"
#include "sitfield.h"
#include "emstime.h"
#include "emsbeacon.h"
#include "uniquetimeprovider.h"
#include "configurationaccessor.h"
#include "xmlmfdefns.h"
#include "convutility.h"
#include "sittoken.h"
#include "emsexcpt.h"
#include "csvreader.h"

const TCHAR c_szSit722HdrFmt[ ] = TEXT("/%03d/%04d/%02d");
const TCHAR c_szSit722Body1Fmt[] = TEXT("/%03d/%04d/%02d/%s");
const TCHAR c_szSit722Body2Fmt[] = TEXT("/%02d %03d %02d%02d %02d.%06d/%013.9f");
const wchar_t c_wszSit722Body2Fmt[] = L"%02d %03d %02d%02d %02d.%06d";
const TCHAR c_szSit722Body3Fmt[] = TEXT("/%08.6f/%+010.3f/%04.1f/%07.3f/%04X");

const double c_dMF70Default = 99999.999;		// Default Freq Offset
const double c_dMF70Override = 0.0;			//

const double c_dMF72Default = 0.0;				// Default Power Level
const double c_dMF72Override = 35.0;

const double c_dMF75Default = 0.0;				// Default Bit Rate
const double c_dMF75Override = 400.0;

CEMSSit722::CEMSSit722() : m_iBurstCount(0)
{
	SetSitNumber(722);
	SetMaxBurstCount( EMS_MAX_SIT722_BURSTS );
}

CEMSSit722::~CEMSSit722()
{
	Reset();
}

void CEMSSit722::Reset( void )
{
	CEMSSitMessageBase::Reset();

	m_olst406Data.Clear();
	SetBurstCount( 0 );
	SetSitNumber(722);
	SetMaxBurstCount( EMS_MAX_SIT722_BURSTS );
}

EMS_RESULT CEMSSit722::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];

	if ( lpStream )
	{
		int iReportingID = GetReportingMCC();

		m_olst406Data.MoveFirst();
		ULONG ulCount = m_olst406Data.Count();

		for ( ULONG i = 0; ( EMS_OK == hr ) && ( i < ulCount ); i++ )
		{
			EMSCALIB406DATAEXT str406Data = m_olst406Data.GetNext();

			// Line 1
			for ( int j = 0; j < 15; j++ )
			{
				_stprintf( &szBeaconMsg[j*2], "%02X", str406Data.calib406.cBeaconMsg[3+j] );
			}

			_stprintf( szBuffer, c_szSit722Body1Fmt, 
									str406Data.calib406.hdr.id.ulSatID,
									(0 == iReportingID) ? str406Data.calib406.hdr.id.ulLutID : iReportingID,
									str406Data.calib406.wAntennaID,										// not currently part of the extended record
									szBeaconMsg );

			hr = WriteLine( lpStream, szBuffer );

			// Line 2
			if ( EMS_OK == hr )
			{
				EMSTIMEFIELDS tmfldsMsgTime;
				CEMSTime oTime( str406Data.calib406.timeMsg );

				oTime.GetTime( &tmfldsMsgTime );

				long lMicroSeconds = tmfldsMsgTime.lNanosecond / 1000L;

				_stprintf( szBuffer, c_szSit722Body2Fmt,
									tmfldsMsgTime.nYear - 2000,
									tmfldsMsgTime.nJulianDay,
									tmfldsMsgTime.nHour,
									tmfldsMsgTime.nMinute,
									tmfldsMsgTime.nSecond,
									lMicroSeconds, 
									str406Data.calib406.dFrequency / ((double) 1000000.0) );

				hr = WriteLine( lpStream, szBuffer );
			}

			// Line 3
			if( EMS_OK == hr )
			{
				_stprintf( szBuffer, c_szSit722Body3Fmt,
									(double) str406Data.calib406.i64TimeOffset / (double) 1000000000,
									_GetFrequencyOffset( str406Data.calib406.dFreqOffset ),
									str406Data.calib406.dCarrierPower,
									str406Data.calib406.dBitRate,
									_DataFlagsToMEOFlags( str406Data.calib406.dwDataFlags ) );
//									str406Data.wMEOFlags );

				hr = WriteLine( lpStream, szBuffer );
			}
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit722::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
				
		sprintf( szBuffer, c_szSit722HdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						m_olst406Data.Count() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit722::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	m_olst406Data.Clear();

	for ( int i = 0; ( EMS_OK == hr ) && ( i < GetBurstCount() ); i++ )
	{
		EMSCALIB406DATAEXT str406Data;
		memset( &str406Data, 0, sizeof( str406Data ) );

		// Use the transmit time for the time stamp.
		str406Data.calib406.hdr.id.time = CEMSUniqueTimeProvider::GetInstance()->GetTime();

		hr = _ParseLine1( lpTokenizer, str406Data );

		if (EMS_OK == hr )
			hr = _ParseLine2( lpTokenizer, str406Data );

		if (EMS_OK == hr )
			hr = _ParseLine3( lpTokenizer, str406Data );

		if ( EMS_OK == hr )
		{
			m_olst406Data.Add( str406Data );
		}
	}

	return hr;
}

EMS_RESULT CEMSSit722::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF74 EOL

		if ( nFldCount == 4 )
		{
			int nSitNumber = 0, nSitDestination = 0, nBursts = 0;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF74( sitField[2].szText, &nBursts );
			}

			if ( hr == EMS_OK )
			{
				SetBurstCount( nBursts );

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

EMS_RESULT CEMSSit722::Get( EMSCALIB406DATAEXT& rstr406, const ULONG culIndex )
{
	EMS_RESULT hr = EMS_OK;

	if( !m_olst406Data.Get( culIndex, rstr406 ) )
		hr = EMS_ARRAY_OUT_OF_BOUNDS;

	return hr;
}

EMS_RESULT CEMSSit722::Add( const EMSCALIB406DATAEXT& crstr406 )
{
	EMS_RESULT hr = EMS_OK;

	if ( GetActualBurstCount() < GetMaxBurstCount() )
	{
		m_olst406Data.Add( crstr406 );
	}
	else
		hr = EMS_SIT_ALERT_LIMIT;

	return hr;
}


EMS_RESULT CEMSSit722::_ParseLine1( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF6/MF11/MF71/MF23 EOL 

		// The type is EMSCALIBTYPE_406_SARR
		rstrBurstData.calib406.hdr.wType = EMSCALIBTYPE_406_SARR;

		if ( nFldCount == 5 )
		{
			CEMSSitMsgField msgField;

			hr = msgField.GetMF6( sitField[0].szText, (int*) &rstrBurstData.calib406.hdr.id.ulSatID );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF11( sitField[1].szText, (int*) &rstrBurstData.calib406.hdr.id.ulLutID );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF71( sitField[2].szText, (int*) &rstrBurstData.calib406.wAntennaID );
			}

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF23( sitField[3].szText, rstrBurstData.calib406.cBeaconMsg );
			}

			if( hr == EMS_OK )
			{
				// Extract the beacon ID.
				BYTE abyBuf[18];
				memset( abyBuf, 0, sizeof(abyBuf) );

				memcpy( &abyBuf[3], rstrBurstData.calib406.cBeaconMsg, 15 );

				CBeaconMsg oBcnMsg( abyBuf );
				
				rstrBurstData.calib406.i64BeaconID = oBcnMsg.getBeaconID();
				
				oBcnMsg.Get( rstrBurstData.calib406.cBeaconMsg );
				
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[4].szText ) )
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

EMS_RESULT CEMSSit722::_ParseLine2( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF67/MF68 EOL 

		if ( nFldCount == 3 )
		{
			CEMSSitMsgField msgField;

			hr = msgField.GetMF67( sitField[0].szText, &rstrBurstData.calib406.timeMsg );

			if ( hr == EMS_OK )
			{
				hr = msgField.GetMF68( sitField[1].szText, &rstrBurstData.calib406.dFrequency );

				if( hr == EMS_OK )
				{
					rstrBurstData.calib406.dFrequency *= (double) 1000000;
				}
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

EMS_RESULT CEMSSit722::_ParseLine3( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF69/MF70/MF72/MF75/MF76 EOL 

		if ( nFldCount == 6 )
		{
			CEMSSitMsgField msgField;

			double dTimeOffset = 0.0;

			hr = msgField.GetMF69( sitField[0].szText, &dTimeOffset );

			if ( hr == EMS_OK )
			{
				rstrBurstData.calib406.i64TimeOffset = dTimeOffset * 1000000000;	// convert from seconds to nanoseconds

				hr = msgField.GetMF70( sitField[1].szText, &rstrBurstData.calib406.dFreqOffset );
			}

			if ( hr == EMS_OK )
			{
				if ( c_dMF70Default == rstrBurstData.calib406.dFreqOffset )
				{
					rstrBurstData.calib406.dwResolutionFlags |= EMS_C406RF_FREQRES_LOW;

					rstrBurstData.calib406.dFreqOffset = c_dMF70Override;
				}

				hr = msgField.GetMF72( sitField[2].szText, &rstrBurstData.calib406.dCarrierPower );
			}

			if ( hr == EMS_OK )
			{
				if ( c_dMF72Default == rstrBurstData.calib406.dCarrierPower )
				{
					rstrBurstData.calib406.dwResolutionFlags |= EMS_C406RF_POWERRES_LOW;

					rstrBurstData.calib406.dCarrierPower = c_dMF72Override;
				}

				hr = msgField.GetMF75( sitField[3].szText, &rstrBurstData.calib406.dBitRate );
			}

			if ( hr == EMS_OK )
			{
				WORD wMEOFlags = 0;

				if ( c_dMF75Default == rstrBurstData.calib406.dBitRate )
				{
					rstrBurstData.calib406.dwResolutionFlags |= EMS_C406RF_BPSRES_LOW;

					rstrBurstData.calib406.dBitRate = c_dMF75Override;
				}

				hr = msgField.GetMF76( sitField[4].szText, &wMEOFlags );

				if ( EMS_OK == hr )
					rstrBurstData.calib406.dwDataFlags = _MEOFlagsToDataFlags( wMEOFlags );

//				hr = msgField.GetMF76( sitField[4].szText, &rstrBurstData.wMEOFlags );
			}

			if ( hr == EMS_OK )
			{
				if ( !msgField.IsEOL( sitField[5].szText ) )
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


WORD CEMSSit722::_DataFlagsToMEOFlags( DWORD dwDataFlags )
{
	WORD wMEOFlags = 0;

	if ( dwDataFlags &  EMS_C406DF_FLAG_01) wMEOFlags |= 0x0001;
	if ( dwDataFlags &  EMS_C406DF_FLAG_02) wMEOFlags |= 0x0002;
	if ( dwDataFlags &  EMS_C406DF_FLAG_03) wMEOFlags |= 0x0004;
	if ( dwDataFlags &  EMS_C406DF_FLAG_04) wMEOFlags |= 0x0008;
	if ( dwDataFlags &  EMS_C406DF_FLAG_05) wMEOFlags |= 0x0010;
	if ( dwDataFlags &  EMS_C406DF_FLAG_06) wMEOFlags |= 0x0020;
	if ( dwDataFlags &  EMS_C406DF_FLAG_07) wMEOFlags |= 0x0040;
	if ( dwDataFlags &  EMS_C406DF_FLAG_08) wMEOFlags |= 0x0080;
	if ( dwDataFlags &  EMS_C406DF_FLAG_09) wMEOFlags |= 0x0100;
	if ( dwDataFlags &  EMS_C406DF_FLAG_10) wMEOFlags |= 0x0200;
	if ( dwDataFlags &  EMS_C406DF_FLAG_11) wMEOFlags |= 0x0400;
	if ( dwDataFlags &  EMS_C406DF_FLAG_12) wMEOFlags |= 0x0800;
	if ( dwDataFlags &  EMS_C406DF_FLAG_13) wMEOFlags |= 0x1000;
	if ( dwDataFlags &  EMS_C406DF_FLAG_14) wMEOFlags |= 0x2000;
	if ( dwDataFlags &  EMS_C406DF_FLAG_15) wMEOFlags |= 0x4000;
	if ( dwDataFlags &  EMS_C406DF_FLAG_16) wMEOFlags |= 0x8000;
	return wMEOFlags;
}

DWORD CEMSSit722::_MEOFlagsToDataFlags( WORD wMEOFlags )
{
	DWORD dwDataFlags = 0;

	if ( wMEOFlags & 0x0001 ) dwDataFlags |= EMS_C406DF_FLAG_01;
	if ( wMEOFlags & 0x0002 ) dwDataFlags |= EMS_C406DF_FLAG_02;
	if ( wMEOFlags & 0x0004 ) dwDataFlags |= EMS_C406DF_FLAG_03;
	if ( wMEOFlags & 0x0008 ) dwDataFlags |= EMS_C406DF_FLAG_04;
	if ( wMEOFlags & 0x0010 ) dwDataFlags |= EMS_C406DF_FLAG_05;
	if ( wMEOFlags & 0x0020 ) dwDataFlags |= EMS_C406DF_FLAG_06;
	if ( wMEOFlags & 0x0040 ) dwDataFlags |= EMS_C406DF_FLAG_07;
	if ( wMEOFlags & 0x0080 ) dwDataFlags |= EMS_C406DF_FLAG_08;
	if ( wMEOFlags & 0x0100 ) dwDataFlags |= EMS_C406DF_FLAG_09;
	if ( wMEOFlags & 0x0200 ) dwDataFlags |= EMS_C406DF_FLAG_10;
	if ( wMEOFlags & 0x0400 ) dwDataFlags |= EMS_C406DF_FLAG_11;
	if ( wMEOFlags & 0x0800 ) dwDataFlags |= EMS_C406DF_FLAG_12;
	if ( wMEOFlags & 0x1000 ) dwDataFlags |= EMS_C406DF_FLAG_13;
	if ( wMEOFlags & 0x2000 ) dwDataFlags |= EMS_C406DF_FLAG_14;
	if ( wMEOFlags & 0x4000 ) dwDataFlags |= EMS_C406DF_FLAG_15;
	if ( wMEOFlags & 0x8000 ) dwDataFlags |= EMS_C406DF_FLAG_16;

	return dwDataFlags;
}

double 
CEMSSit722::_GetFrequencyOffset( const double cdRecValue ) const
{
	double dRet = cdRecValue;

	if( dRet > 99999.999 )
	{
		dRet = 99999.999;
	}
	else if(  dRet < -99999.999 )
	{
		dRet = -99999.999;
	}

	return dRet;
}

/*******************************
	722A
*******************************/


CEMSSit722A::CEMSSit722A()
{
	SetSitCode( 0x722A );
}

CEMSSit722A::~CEMSSit722A()
{
	Reset();
}

EMS_RESULT 
CEMSSit722A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	// Do nothing here.
	return EMS_OK;
}

EMS_RESULT 
CEMSSit722A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	CEMSConfigurationAccessor* pRecAccessor = NULL;
	BYTE* abyXML = NULL;

	try
	{

		if( lpStream )
		{
			CEMSSitMsgField sitField;

			int iReportingID = GetReportingMCC();

			// Generate the XML.
			CEMSConfigurationAccessor oConfig;
			oConfig.SetSource( gs_cwsz722RootElem, gs_cwsz722NS );

			m_olst406Data.MoveFirst();
			ULONG ulRecs = m_olst406Data.Count();

			for( int i = 0; i < ulRecs; i++ )
			{
				// New TOA_FOA entry
				pRecAccessor = oConfig.AddChildElement( NULL, gs_cwszTOAFOAElem, gs_cwsz722NSURI );
				
				if( pRecAccessor )
				{

					EMSCALIB406DATAEXT data = m_olst406Data.GetNext();

					// satid, MF6
					pRecAccessor->SetElementValue( gs_cwszMF6[NAME_ONLY], data.calib406.hdr.id.ulSatID, gs_cwsz722NSURI );

					// lutid, MF11
					pRecAccessor->SetElementValue( gs_cwszMF11[NAME_ONLY], (0 == iReportingID) ? data.calib406.hdr.id.ulLutID : iReportingID, gs_cwsz722NSURI  );

					// antenna id, MF 71
					pRecAccessor->SetElementValue( gs_cwszMF71[NAME_ONLY], data.calib406.wAntennaID, gs_cwsz722NSURI );

					// 15 hex beacon id, MF22
					wchar_t wszBeaconID[16];
					memset( wszBeaconID, 0, sizeof(wszBeaconID) );
					_snwprintf( wszBeaconID, 15, L"%015I64X", data.calib406.i64BeaconID );
					pRecAccessor->SetElementValue( gs_cwszMF22[NAME_ONLY], wszBeaconID, gs_cwsz722NSURI );

					// 36 hex beacon msg, MF 77
					wchar_t wszBeaconMsg[37];
					memset( wszBeaconMsg, 0, sizeof(wszBeaconMsg));
					for ( int j = 0; j < 18; j++ )
					{
						swprintf( &wszBeaconMsg[j*2], L"%02X", data.calib406.cBeaconMsg[j] );
					}

					pRecAccessor->SetElementValue( gs_cwszMF77[NAME_ONLY], wszBeaconMsg, gs_cwsz722NSURI );

					// receive time, MF 67
					EMSTIMEFIELDS tmfldsMsgTime;
					CEMSTime oTime( data.calib406.timeMsg );

					oTime.GetTime( &tmfldsMsgTime );

					long lMicroSeconds = tmfldsMsgTime.lNanosecond / 1000L;

					wchar_t wszMsgTime[256];
					memset( wszMsgTime, 0, sizeof(wszMsgTime));
					_snwprintf( wszMsgTime, 255, c_wszSit722Body2Fmt,
										tmfldsMsgTime.nYear - 2000,
										tmfldsMsgTime.nJulianDay,
										tmfldsMsgTime.nHour,
										tmfldsMsgTime.nMinute,
										tmfldsMsgTime.nSecond,
										lMicroSeconds );
					pRecAccessor->SetElementValue( gs_cwszMF67[NAME_ONLY], wszMsgTime, gs_cwsz722NSURI );


					// frequency, MF 68
					wchar_t wszFrequency[32];
					memset( wszFrequency, 0, sizeof(wszFrequency));
					_snwprintf( wszFrequency, 31, L"%13.3f", data.calib406.dFrequency );
					pRecAccessor->SetElementValue( gs_cwszMF68[NAME_ONLY], wszFrequency, gs_cwsz722NSURI );

					// time offset, MF 69
					wchar_t wszTimeOffset[32];
					memset( wszTimeOffset, 0, sizeof(wszTimeOffset));
					_snwprintf( wszTimeOffset, 31, L"%8.6f", (double) data.calib406.i64TimeOffset / (double) 1000000000 );
					pRecAccessor->SetElementValue( gs_cwszMF69[NAME_ONLY], wszTimeOffset, gs_cwsz722NSURI);

					// frequency offset, MF 70
					wchar_t wszFreqOffset[32];
					memset( wszFreqOffset, 0, sizeof(wszFreqOffset));
					_snwprintf( wszFreqOffset, 31, L"%+09.3f", _GetFrequencyOffset( data.calib406.dFreqOffset ) );
					pRecAccessor->SetElementValue( gs_cwszMF70[NAME_ONLY], wszFreqOffset, gs_cwsz722NSURI );

					// carrier power, MF 72
					wchar_t wszPower[32];
					memset( wszPower, 0, sizeof(wszPower));
					_snwprintf( wszPower, 31, L"%4.1f", data.calib406.dCarrierPower );
					pRecAccessor->SetElementValue( gs_cwszMF72[NAME_ONLY], wszPower, gs_cwsz722NSURI );

					// bit rate, MF 73
					wchar_t wszBitRate[32];
					memset( wszBitRate, 0, sizeof(wszBitRate));
					_snwprintf( wszBitRate, 31, L"%7.3f", data.calib406.dBitRate );
					pRecAccessor->SetElementValue( gs_cwszMF73[NAME_ONLY], wszBitRate, gs_cwsz722NSURI );

					// flags, MF 74
					wchar_t wszFlags[5];
					memset( wszFlags, 0, sizeof(wszFlags));
					_snwprintf( wszFlags, 4, L"%04X", _DataFlagsToMEOFlags( data.calib406.dwDataFlags ) );
					pRecAccessor->SetElementValue( gs_cwszMF74[NAME_ONLY], wszFlags, gs_cwsz722NSURI );

					// orbit position vector (x y z in km), MF75
					std::wstring owszMF75;
#ifdef UNICODE
					owszMF75 = sitFields.TextMF75A( data.extras.SatTPVC.coord.radius.dX,
													data.extras.SatTPVC.coord.radius.dY,
													data.extras.SatTPVC.coord.radius.dZ );
#else
					owszMF75 = CEMSConversionUtil::ConvertToString( sitField.TextMF75A( data.extras.SatTPVC.coord.radius.dX,
															data.extras.SatTPVC.coord.radius.dY,
															data.extras.SatTPVC.coord.radius.dZ ) );
#endif
					pRecAccessor->SetElementValue( gs_cwszMF75[NAME_ONLY], owszMF75.c_str() , gs_cwsz722NSURI);


					std::wstring owszMF76;
#ifdef UNICODE
					owszMF76 = sitFields.TextMF76A( data.extras.SatTPVC.coord.velocity.dX,
													data.extras.SatTPVC.coord.velocity.dY,
													data.extras.SatTPVC.coord.velocity.dZ );
#else
					owszMF76 = CEMSConversionUtil::ConvertToString( sitField.TextMF76A( data.extras.SatTPVC.coord.velocity.dX,
													data.extras.SatTPVC.coord.velocity.dY,
													data.extras.SatTPVC.coord.velocity.dZ ) );
#endif
					pRecAccessor->SetElementValue( gs_cwszMF76[NAME_ONLY], owszMF76.c_str(), gs_cwsz722NSURI );


					pRecAccessor->Release();
					pRecAccessor = NULL;
				}
			}

			std::string oszXML = CEMSConversionUtil::ConvertToString(oConfig.Serialize().c_str());

			ULONG ulToWrite = 0;
			CEMSConversionUtil::ConvertToByteArray( (char*) oszXML.c_str(), ulToWrite, abyXML );

			ULONG ulWritten = 0;
			hr = lpStream->Write( abyXML, ulToWrite, &ulWritten );

			delete[] abyXML;
			abyXML = NULL;

		}
	}
	catch( ... )
	{
		if( pRecAccessor )
		{
			pRecAccessor->Release();
			pRecAccessor = NULL;
		}

		if( abyXML )
		{
			delete[] abyXML;
			abyXML = NULL;
		}

		throw;
	}

	return hr;
}

EMS_RESULT 
CEMSSit722A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	if( lpTokenizer )
	{
		std::string oszFullMessage;
		hr = lpTokenizer->ReadAllText( oszFullMessage );

		if( (EMS_OK == hr) && !oszFullMessage.empty() )
		{
			CEMSConfigurationAccessor oMsg;

			try
			{
				oMsg.SetSource( CEMSConversionUtil::ConvertToString(oszFullMessage.c_str()).c_str(), gs_cwsz722ToaFoaNS );
			}
			catch( CEMSException& e )
			{
				// Couldn't load it as XML.
				hr = e.GetErrCode();
			}
			catch( ... )
			{
				// Couldn't load it as XML.
				hr = EMS_DATA_INVALID;
			}

			if( EMS_OK == hr )
			{
				// Get the record list first.
				CEMSObjectList<CEMSConfigurationAccessor> lstRecords = oMsg.GetAccessorList( gs_cwszTOAFOAElemFullyQualified );

				m_iBurstCount = lstRecords.Count();
				lstRecords.MoveFirst();

				m_olst406Data.Clear();

				for( ULONG l = 0; l < m_iBurstCount; l++ )
				{
					CEMSConfigurationAccessor recordAccessor = lstRecords.GetNext();


					EMSCALIB406DATAEXT record;
					memset( &record, 0, sizeof(record));

					record.calib406.hdr.id.time = CEMSUniqueTimeProvider::GetInstance()->GetTime();
					record.calib406.hdr.wType = EMSCALIBTYPE_406_SARR;
					record.calib406.hdr.id.ulSatID = recordAccessor.GetElementValueULong( gs_cwszMF6[FULLY_QUALIFIED] );
					record.calib406.hdr.id.ulLutID = recordAccessor.GetElementValueULong( gs_cwszMF11[FULLY_QUALIFIED] );
					record.calib406.wAntennaID = recordAccessor.GetElementValueShort( gs_cwszMF71[FULLY_QUALIFIED] );
					record.calib406.i64BeaconID = recordAccessor.GetElementValueUI64( gs_cwszMF22[FULLY_QUALIFIED] );
					std::wstring owszBcnMsg = recordAccessor.GetElementValue( gs_cwszMF77[FULLY_QUALIFIED] );

// Below decoding of MF77 as if it were MF82 is residual from a discrepancy in the initial definition
// of the message fields.  Beacon Message was proposed to be MF82 and Altitude (for alert messages) MF77.
// These two field names have since been swapped.					
					CEMSSitMsgField sitField;
#ifdef UNICODE
					hr = sitField.GetMF82( owszBcnMsg.c_str(), record.calib406.cBeaconMsg );
#else
					hr = sitField.GetMF82( CEMSConversionUtil::ConvertToString(owszBcnMsg.c_str()).c_str(), record.calib406.cBeaconMsg );
#endif
					std::wstring owszTimeMsg = recordAccessor.GetElementValue( gs_cwszMF67[FULLY_QUALIFIED] );
#ifdef UNICODE
					hr = sitField.GetMF67Ex( owszTimeMsg.c_str(), &record.calib406.timeMsg );
#else
					hr = sitField.GetMF67Ex( CEMSConversionUtil::ConvertToString(owszTimeMsg.c_str()).c_str(), &record.calib406.timeMsg );
#endif
					record.calib406.dFrequency = recordAccessor.GetElementValueDouble( gs_cwszMF68[FULLY_QUALIFIED]);
					record.calib406.i64TimeOffset = recordAccessor.GetElementValueDouble( gs_cwszMF69[FULLY_QUALIFIED]) * 1000000000L;
					record.calib406.dFreqOffset = recordAccessor.GetElementValueDouble( gs_cwszMF70[FULLY_QUALIFIED]);

					if ( c_dMF70Default == record.calib406.dFreqOffset )
					{
						record.calib406.dwResolutionFlags |= EMS_C406RF_FREQRES_LOW;

						record.calib406.dFreqOffset = c_dMF70Override;
					}

					record.calib406.dCarrierPower = recordAccessor.GetElementValueDouble( gs_cwszMF72[FULLY_QUALIFIED]);
					record.calib406.dBitRate = recordAccessor.GetElementValueDouble( gs_cwszMF73[FULLY_QUALIFIED]);
					
					WORD wFlags = 0;
					std::wstring owszFlags = recordAccessor.GetElementValue( gs_cwszMF74[FULLY_QUALIFIED]);

#ifdef UNICODE
					hr = sitField.GetMF76Ex( owszFlags.c_str(), &wFlags );
#else
					hr = sitField.GetMF76Ex( CEMSConversionUtil::ConvertToString(owszFlags.c_str()).c_str(), &wFlags );
#endif
					record.calib406.dwDataFlags = _MEOFlagsToDataFlags( wFlags );

					std::wstring owszMF75 = recordAccessor.GetElementValue( gs_cwszMF75[FULLY_QUALIFIED] );

					sitField.GetMF75A( 
#ifdef UNICODE
						owszMF75.c_str(), 
#else
						CEMSConversionUtil::ConvertToString( owszMF75.c_str() ).c_str(),
#endif
						record.extras.SatTPVC.coord.radius.dX, 
						record.extras.SatTPVC.coord.radius.dY,
						record.extras.SatTPVC.coord.radius.dZ );
					
					std::wstring owszMF76 = recordAccessor.GetElementValue( gs_cwszMF76[FULLY_QUALIFIED] );

					sitField.GetMF76A( 
#ifdef UNICODE
						owszMF76.c_str(), 
#else
						CEMSConversionUtil::ConvertToString( owszMF76.c_str() ).c_str(),
#endif
						record.extras.SatTPVC.coord.velocity.dX, 
						record.extras.SatTPVC.coord.velocity.dY,
						record.extras.SatTPVC.coord.velocity.dZ );

					record.extras.SatTPVC.coordSystem = COORDSYS_EarthFixed;
					record.extras.SatTPVC.vTime.intTime = record.calib406.timeMsg.intTime;
					
					m_olst406Data.Add( record );

				}
			}


		}
	}



	return hr;
}

EMS_RESULT 
CEMSSit722A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;

	return hr;
}

/*******************************
	722B
*******************************/


CEMSSit722B::CEMSSit722B()
{
	SetSitCode( 0x722B );
}

CEMSSit722B::~CEMSSit722B()
{
	Reset();
}

EMS_RESULT 
CEMSSit722B::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	// Do nothing here.
	return EMS_OK;
}

EMS_RESULT 
CEMSSit722B::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	CEMSConfigurationAccessor* pRecAccessor = NULL;
	BYTE* abyMsg = NULL;

	try
	{

		if( lpStream )
		{
			const wchar_t* cwszLineFmt = L"%s,%8.6f,%03d,%04d,%02d,%s,%s,%013.3f,%+09.3f,%04.1f,%07.3f,%s,%s\r\n";

			int iReportingID = GetReportingMCC();

			m_olst406Data.MoveFirst();
			ULONG ulRecs = m_olst406Data.Count();

			std::wstring owszMsg;
			
			for( int i = 0; i < ulRecs; i++ )
			{

				EMSCALIB406DATAEXT data = m_olst406Data.GetNext();

				// 15 hex beacon id, MF22
				wchar_t wszBeaconID[16];
				memset( wszBeaconID, 0, sizeof(wszBeaconID) );
				_snwprintf( wszBeaconID, 15, L"%015I64X", data.calib406.i64BeaconID );

				// 36 hex beacon msg, MF 82
				wchar_t wszBeaconMsg[37];
				memset( wszBeaconMsg, 0, sizeof(wszBeaconMsg));
				for ( int j = 0; j < 18; j++ )
				{
					swprintf( &wszBeaconMsg[j*2], L"%02X", data.calib406.cBeaconMsg[j] );
				}

				
				// receive time, MF 67
				EMSTIMEFIELDS tmfldsMsgTime;
				CEMSTime oTime( data.calib406.timeMsg );

				oTime.GetTime( &tmfldsMsgTime );

				long lMicroSeconds = tmfldsMsgTime.lNanosecond / 1000L;

				wchar_t wszMsgTime[256];
				memset( wszMsgTime, 0, sizeof(wszMsgTime));
				_snwprintf( wszMsgTime, 255, c_wszSit722Body2Fmt,
									tmfldsMsgTime.nYear - 2000,
									tmfldsMsgTime.nJulianDay,
									tmfldsMsgTime.nHour,
									tmfldsMsgTime.nMinute,
									tmfldsMsgTime.nSecond,
									lMicroSeconds );

				CEMSSitMsgField sitField;


				LPCTSTR szMF75A = sitField.TextMF75A( data.extras.SatTPVC.coord.radius.dX,
														data.extras.SatTPVC.coord.radius.dY,
														data.extras.SatTPVC.coord.radius.dZ);

				LPCTSTR szMF76A = sitField.TextMF76A( data.extras.SatTPVC.coord.velocity.dX,
													data.extras.SatTPVC.coord.velocity.dY,
													data.extras.SatTPVC.coord.velocity.dZ);

				wchar_t wszLine[2048];
				memset( wszLine, 0, sizeof(wszLine));


				_snwprintf( wszLine, 2047, cwszLineFmt, 
								wszMsgTime,
								(double) data.calib406.i64TimeOffset / (double) 1000000000,
								data.calib406.hdr.id.ulSatID,
								(0 == iReportingID) ? data.calib406.hdr.id.ulLutID : iReportingID,
								data.calib406.wAntennaID,
								wszBeaconID,
								wszBeaconMsg,
								data.calib406.dFrequency,
								_GetFrequencyOffset( data.calib406.dFreqOffset ),
								data.calib406.dCarrierPower,
								data.calib406.dBitRate,
#ifdef UNICODE
								szMF75A,
								szMF76A
#else
								CEMSConversionUtil::ConvertToString( szMF75A ).c_str(),
								CEMSConversionUtil::ConvertToString( szMF76A ).c_str()
#endif

								 );

				if( owszMsg.empty() )
					owszMsg = wszLine;
				else
					owszMsg.append( wszLine );
			}

			std::string oszMsg = CEMSConversionUtil::ConvertToString(owszMsg.c_str());

			ULONG ulToWrite = 0;
			CEMSConversionUtil::ConvertToByteArray( (char*) oszMsg.c_str(), ulToWrite, abyMsg );

			ULONG ulWritten = 0;
			hr = lpStream->Write( abyMsg, ulToWrite, &ulWritten );

			delete[] abyMsg;
			abyMsg = NULL;

		}
	}
	catch( ... )
	{
		if( pRecAccessor )
		{
			pRecAccessor->Release();
			pRecAccessor = NULL;
		}

		if( abyMsg )
		{
			delete[] abyMsg;
			abyMsg = NULL;
		}

		throw;
	}

	return hr;
}

EMS_RESULT 
CEMSSit722B::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	if( lpTokenizer )
	{
		std::string oszFullMessage;
		hr = lpTokenizer->ReadAllText( oszFullMessage );

		if( (EMS_OK == hr) && !oszFullMessage.empty() )
		{
			// Read line by line.
			// Skip delims at beginning, find start of first token
			const char* cszDelims = "\r\n";
			std::string::size_type lastPos = oszFullMessage.find_first_not_of(cszDelims, 0);
			// Find next delimiter @ end of token
			std::string::size_type pos = oszFullMessage.find_first_of(cszDelims, lastPos);

			m_olst406Data.Clear();

			while (std::string::npos != pos || std::string::npos != lastPos)
			{
				EMSCALIB406DATAEXT record;
				memset( &record, 0, sizeof(record));

				// Found a line
				std::string szLine = oszFullMessage.substr(lastPos, pos - lastPos);

				// Is this a header line.  Check if the first character is not a digit.
				if( !szLine.empty() && isdigit(szLine.at(0)) )
				{

					CEMSCSVReader lineReader( CEMSConversionUtil::ConvertToString(szLine.c_str()), L',', NULL );

					record.calib406.hdr.id.time = CEMSUniqueTimeProvider::GetInstance()->GetTime();
					record.calib406.hdr.wType = EMSCALIBTYPE_406_SARR;

					std::wstring owszTimeMsg = lineReader.GetFieldAsStringW(0L);
					CEMSSitMsgField sitField;
#ifdef UNICODE
					hr = sitField.GetMF67Ex( owszTimeMsg.c_str(), &record.calib406.timeMsg );
#else
					hr = sitField.GetMF67Ex( CEMSConversionUtil::ConvertToString(owszTimeMsg.c_str()).c_str(), &record.calib406.timeMsg );
#endif
					record.calib406.i64TimeOffset = lineReader.GetFieldAsDouble(1) * 1000000000L;
					record.calib406.hdr.id.ulSatID = lineReader.GetFieldAsULong(2);
					record.calib406.hdr.id.ulLutID = lineReader.GetFieldAsULong(3);
					record.calib406.wAntennaID = lineReader.GetFieldAsUShort(4);
					record.calib406.i64BeaconID = lineReader.GetFieldAsI64(5);

					std::wstring owszBcnMsg = lineReader.GetFieldAsStringW(6);
					
#ifdef UNICODE
					hr = sitField.GetMF82( owszBcnMsg.c_str(), record.calib406.cBeaconMsg );
#else
					hr = sitField.GetMF82( CEMSConversionUtil::ConvertToString(owszBcnMsg.c_str()).c_str(), record.calib406.cBeaconMsg );
#endif
					record.calib406.dFrequency = lineReader.GetFieldAsDouble(7);
					
					record.calib406.dFreqOffset = lineReader.GetFieldAsDouble(8);

					if ( c_dMF70Default == record.calib406.dFreqOffset )
					{
						record.calib406.dwResolutionFlags |= EMS_C406RF_FREQRES_LOW;

						record.calib406.dFreqOffset = c_dMF70Override;
					}

					record.calib406.dCarrierPower = lineReader.GetFieldAsDouble(9);
					record.calib406.dBitRate = lineReader.GetFieldAsDouble(10);
					
					std::wstring owszMF75 = lineReader.GetFieldAsStringW(11);

					sitField.GetMF75A( 
#ifdef UNICODE
						owszMF75.c_str(), 
#else
						CEMSConversionUtil::ConvertToString( owszMF75.c_str() ).c_str(),
#endif
						record.extras.SatTPVC.coord.radius.dX, 
						record.extras.SatTPVC.coord.radius.dY,
						record.extras.SatTPVC.coord.radius.dZ );
					
					std::wstring owszMF76 = lineReader.GetFieldAsStringW(12);

					sitField.GetMF76A( 
#ifdef UNICODE
						owszMF76.c_str(), 
#else
						CEMSConversionUtil::ConvertToString( owszMF76.c_str() ).c_str(),
#endif
						record.extras.SatTPVC.coord.velocity.dX, 
						record.extras.SatTPVC.coord.velocity.dY,
						record.extras.SatTPVC.coord.velocity.dZ );

					record.extras.SatTPVC.coordSystem = COORDSYS_EarthFixed;
					record.extras.SatTPVC.vTime.intTime = record.calib406.timeMsg.intTime;

					m_olst406Data.Add( record );
				}
			  
				// Skip delims.  Note the "not_of". this is beginning of token
				lastPos = oszFullMessage.find_first_not_of(cszDelims, pos);

				// Find next delimiter at end of token.
				pos     = oszFullMessage.find_first_of(cszDelims, lastPos);

			}

		}
	}



	return hr;
}

EMS_RESULT 
CEMSSit722B::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;

	return hr;


}