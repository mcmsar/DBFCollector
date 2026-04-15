/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
						unknown

********************************************************************/

#include <assert.h>

#include "dtbinaryfile.h"

#include "emsfstrm.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "binmsgbody.h"
#include "locatebinstrm.h"
#include "calib406binstrm.h"
#include "cbcbinstrm.h"
#include "logbinstrm.h"
#include "spectrumbinstrm.h"
#include "statusbinstrm.h"
#include "tlebinstrm.h"
#include "sarpcalibbinstrm.h"
#include "sarpbinstrm.h"
#include "sarrcalibbinstrm.h"
#include "sarrbinstrm.h"
#include "sattrackbinstrm.h"
#include "calibcbcbinstrm.h"
#include "comb406binstrm.h"
#include "configbinstrm.h"
#include "residualbinstrm.h"
#include "audioriffbinstrm.h"
#include "sarrextbinstrm.h"
#include "calib406exbinstrm.h"
#include "calib4062binstrm.h"
#include "bcnadvisorybinstrm.h"

#include "arrayhelper.h"

CEMSDTBinaryFile::CEMSDTBinaryFile() :	m_pStrm(NULL)
{
}

CEMSDTBinaryFile::CEMSDTBinaryFile( const CEMSDTBinaryFile& x ) 
			:	m_pStrm( x.m_pStrm ), m_owszFilename( x.m_owszFilename )
{
	if( m_pStrm )
		m_pStrm->AddRef();

}

CEMSDTBinaryFile::~CEMSDTBinaryFile()
{
	Close();
}

void
CEMSDTBinaryFile::SetFilename( const wchar_t* cwszFilename )
{
	m_owszFilename = cwszFilename;
}


void
CEMSDTBinaryFile::SetHeader( EMSBINARYSTRMHEADER header )
{
	// Get stream positioned at the very start
	// Note that this will only work if this is the very first use of this stream!!!
	IEMSRandomStream* pStrm = _GetStream();

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->MoveFirst();

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		unsigned long ulWritten = 0;
		hr = pStrm->Write( (const unsigned char*) &header, sizeof(EMSBINARYSTRMHEADER), &ulWritten );

		pStrm->Release();
		pStrm = 0;

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}
}

EMSBINARYSTRMHEADER
CEMSDTBinaryFile::GetHeader()
{
	EMSBINARYSTRMHEADER strRet;
	memset( &strRet, 0, sizeof(EMSBINARYSTRMHEADER) );

	IEMSRandomStream* pStrm = _GetStream();

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->MoveFirst();

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		unsigned long ulRead = 0;
		hr = pStrm->Read( (unsigned char*) &strRet, sizeof(EMSBINARYSTRMHEADER), &ulRead );

		pStrm->Release();
		pStrm = 0;

		if( FAILED(hr) &&
			EMS_EOF != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}

	return strRet;
}

void 
CEMSDTBinaryFile::Close()
{
	if( m_pStrm )
	{
		m_pStrm->CloseFile();
		m_pStrm->Release();
		m_pStrm = 0;
	}
}

void 
CEMSDTBinaryFile::Reset()
{
	Close();
	m_owszFilename.erase();
}

EMSVARIANTRECORD3* 
CEMSDTBinaryFile::ReadNext()
{
	THROW_RUNTIME_EXCEPTION( EMS_NOT_IMPLEMENTED );
}

void 
CEMSDTBinaryFile::WriteRecord( const EMSVARIANTRECORD2& record )
{
	CEMSBinMsgBody* pMsgBody = 0;

	// Get writable stream
	IEMSRandomStream* pStrm = _GetStream( );
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody( record.eType );

		if( pMsgBody )
		{
			// Move stream to the end.
			EMS_RESULT hr = pStrm->MoveLast();

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

			pMsgBody->SetStream( pStrm );

			pMsgBody->WriteRecord2( record );

			_IncrementCount( );

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

	}
	catch( ... )
	{
		delete pMsgBody;
		pMsgBody = NULL;

		if( pStrm )
		{
			pStrm->Release();
			pStrm = NULL;
		}
		throw;
	}
	return;
}



void 
CEMSDTBinaryFile::WriteRecord( const EMSVARIANTRECORD3& record )
{
	CEMSBinMsgBody* pMsgBody = 0;

	// Get writable stream
	IEMSRandomStream* pStrm = _GetStream( );
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody( record.eType );

		if( pMsgBody )
		{
			// Move stream to the end.
			EMS_RESULT hr = pStrm->MoveLast();

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

			pMsgBody->SetStream( pStrm );

			pMsgBody->WriteRecord3( record );

			_IncrementCount( );

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

	}
	catch( ... )
	{
		delete pMsgBody;
		pMsgBody = NULL;

		if( pStrm )
		{
			pStrm->Release();
			pStrm = NULL;
		}
		throw;
	}
	return;
}

void 
CEMSDTBinaryFile::Get( BYTE*& rabyData, ULONG& rulBytes )
{
	THROW_RUNTIME_EXCEPTION( EMS_NOT_IMPLEMENTED );
}

IEMSRandomStream*
CEMSDTBinaryFile::_GetStream(  )
{
	IEMSRandomStream* pStrm = 0;

	if( !m_pStrm )
	{
		if( !m_owszFilename.empty() )
		{

			// Member setting can override the supplied writable flag
			m_pStrm = new CEMSFileStream;

			if( !m_pStrm )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			EMS_RESULT hr = m_pStrm->OpenFile( 
	#ifdef UNICODE
											m_owszFilename.c_str(),
	#else
											CEMSConversionUtil::ConvertToString( m_owszFilename.c_str() ).c_str(),
	#endif
											TRUE, FALSE, TRUE );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}
		}
	}

	if( m_pStrm )
	{
		pStrm = m_pStrm;
		pStrm->AddRef();
	}


	return pStrm;
}

CEMSBinMsgBody*
CEMSDTBinaryFile::_AllocMsgBody( const EMSRECORDTYPE ceType )
{
	CEMSBinMsgBody* pMsgBody = NULL;
	switch( ceType )
	{
		case EMSRT_CALIB406:
			pMsgBody = new CEMSCalib406BinStrm;
			break;
		case EMSRT_LOCATE:
		case EMSRT_LOCATE_124:
			pMsgBody = new CEMSLocateBinStrm;
			break;
        case EMSRT_CBC:
            pMsgBody = new CEMSCBCBinStrm;
            break;
        case EMSRT_LOG:
            pMsgBody = new CEMSLogBinStrm;
            break;
        case EMSRT_SPECTRUM:
            pMsgBody = new CEMSSpectrumBinStrm;
            break;
        case EMSRT_ANTENNA:
        case EMSRT_CALIBCBC_STATS:
        case EMSRT_COLLECTOR:
        case EMSRT_COMB406_STATS:
        case EMSRT_COMMS_STATS:
        case EMSRT_GEO_CALIB406_STATS:
        case EMSRT_GEO_STATS:
        case EMSRT_LEO_CALIB406_STATS:
        case EMSRT_LOCATE_STATS:
        case EMSRT_ORBIT_STATS:
        case EMSRT_PASS_STATS:
        case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS_124:
        case EMSRT_SARR_CALIB_STATS:
        case EMSRT_SENSOR:
        case EMSRT_STAT_SUMMARY:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
            pMsgBody = new CEMSStatusBinStrm;
            break;
        case EMSRT_ORBIT:
            pMsgBody = new CEMSTLEBinStrm;
            break;
        case EMSRT_SARP_CALIB:
		case EMSRT_SARP_CALIB_124:
            pMsgBody = new CEMSSarpCalibBinStrm;
            break;
        case EMSRT_SARP:
            pMsgBody = new CEMSSarpBinStrm;
            break;
        case EMSRT_SARR_CALIB:
            pMsgBody = new CEMSSarrCalibBinStrm;
            break;
        case EMSRT_SARR:
		case EMSRT_SARR_124:
            pMsgBody = new CEMSSarrBinStrm;
            break;
        case EMSRT_SAT_TRACK:
            pMsgBody = new CEMSSatTrackBinStrm;
            break;
        case EMSRT_CALIBCBC:
            pMsgBody = new CEMSCalibCBCBinStrm;
            break;
        case EMSRT_COMB406:
            pMsgBody = new CEMSComb406BinStrm;
            break;
        case EMSRT_CONFIG:
            pMsgBody = new CEMSConfigBinStrm;
            break;
        case EMSRT_RESIDUAL:
            pMsgBody = new CEMSResidualBinStrm;
            break;
		case EMSRT_AUDIO:
			pMsgBody = new CEMSAudioRiffBinStrm;
			break;
		case EMSRT_SARR_EXT:
			pMsgBody = new CEMSSarrExtBinStrm;
			break;
		case EMSRT_CALIB406_EXT:
			pMsgBody = new CEMSCalib406ExBinStrm;
			break;
		case EMSRT_CALIB406_2:
			pMsgBody = new CEMSCalib4062BinStrm;
			break;
		case EMSRT_BEACON_ADVISORY:
			pMsgBody = new CEMSBcnAdvisoryBinStrm();
			break;
		default:
			assert( FALSE );
			THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
			break;
	}
	if ( !pMsgBody )
	{
		THROW_NOMEMORY_EXCEPTION();
	}
	return pMsgBody;
}

void 
CEMSDTBinaryFile::_IncrementCount()
{
	EMSBINARYSTRMHEADER strHeader = GetHeader();

	strHeader.ulRecordCount++;

	SetHeader( strHeader );
}