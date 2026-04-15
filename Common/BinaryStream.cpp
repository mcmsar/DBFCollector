/********************************************************************
*	Module:			BinaryStream.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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
	0.0	06Nov2003		ch		Moved random access support to a derived class
								CEMSRandBinaryStream (RandBinaryStream.cpp/h)

********************************************************************/

#include <assert.h>
#include "aobjbase.h"
#include "emstime.h"
#include <wchar.h>
#include "igateway.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "urlhandler.h"
#include "BinaryStream.h"

#include "emsfstrm.h"
#include "emserror.h"
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

#include "arrayhelper.h"

const char* CEMSBinaryStream::ms_cszEMSIdentifier = "Copyright(c) 2003 EMS Technologies Inc. All rights reserved.";

CEMSBinaryStream::CEMSBinaryStream() :	
									m_pStrm(0), 
									m_bHeaderRead(false),
									m_eType( EMSRT_UNKNOWN )
{
	memset( &m_Header, 0, sizeof(EMSBINARYSTRMHEADER) );
}

CEMSBinaryStream::CEMSBinaryStream( const CEMSBinaryStream& binStream ) 
			:	m_pStrm(0), 
				m_bHeaderRead(binStream.m_bHeaderRead),
				m_eType( binStream.m_eType )
{
	m_urlHandler = binStream.m_urlHandler;

	if( binStream.m_pStrm )
	{
		m_pStrm = binStream.m_pStrm;

		m_pStrm->AddRef();
	}

	memcpy( &m_Header, &(binStream.m_Header), sizeof(EMSBINARYSTRMHEADER) );


}

CEMSBinaryStream::~CEMSBinaryStream()
{
	Close();
}

void
CEMSBinaryStream::SetSourceURL( const wchar_t* wszURL )
{
	m_urlHandler.SetURL( wszURL );
}

void
CEMSBinaryStream::SetSourceURL( const unsigned long culBytes, const unsigned char* cabyURL )
{
	m_urlHandler.SetURL( culBytes, cabyURL );
}

wchar_t*
CEMSBinaryStream::GetSourceURL()
{
	return m_urlHandler.GetURL();
}

const wchar_t*
CEMSBinaryStream::GetSpec()
{
	return m_urlHandler.GetSpec();
}

void
CEMSBinaryStream::SetHeader( EMSBINARYSTRMHEADER header )
{
	// Get stream positioned at the very start
	// Note that this will only work if this is the very first use of this stream!!!
	IEMSSeqStream* pStrm = _GetStream( true );

	if( pStrm )
	{
		m_eType = header.eRecType;

		unsigned long ulWritten = 0;
		EMS_RESULT hr = pStrm->Write( (const unsigned char*) &header, sizeof(EMSBINARYSTRMHEADER), &ulWritten );

		pStrm->Release();
		pStrm = 0;

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}
}

EMSBINARYSTRMHEADER
CEMSBinaryStream::GetHeader()
{
	if( !m_bHeaderRead )
	{
		IEMSSeqStream* pStrm = _GetStream();

		if( pStrm )
		{
			unsigned long ulRead = 0;
			EMS_RESULT hr = pStrm->Read( (unsigned char*) &m_Header, sizeof(EMSBINARYSTRMHEADER), &ulRead );

			pStrm->Release();
			pStrm = 0;

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}
	}
	m_eType = m_Header.eRecType;
	m_bHeaderRead = true;

	return m_Header;
}

EMSVARIANTRECORD*
CEMSBinaryStream::ReadNext()
{
	EMSVARIANTRECORD* pRet = 0;

	if( !m_bHeaderRead )
	{
		THROW_RUNTIME_EXCEPTION( EMS_INVALID_STREAM_POS );
	}

	// Get stream at "current" position
	// Must be part of a sequence of ReadHeader, ReadNext, ReadNext, ...
	IEMSSeqStream* pStrm = _GetStream();

	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSBinMsgBody* pMsgBody = 0;

	try
	{
		pMsgBody = _AllocMsgBody();
		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			pRet = pMsgBody->ReadNext();

			delete pMsgBody;
			pMsgBody = 0;
		}

		pStrm->Release();
		pStrm = 0;
	}
	catch( ... )
	{
		delete pMsgBody;
		pMsgBody = 0;

		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return pRet;
}

void
CEMSBinaryStream::WriteRecord( const EMSVARIANTRECORD& record )
{
	CEMSBinMsgBody* pMsgBody = 0;

	// Get writable stream
	IEMSSeqStream* pStrm = _GetStream( true );
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody();

		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			pMsgBody->WriteRecord( record );

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
CEMSBinaryStream::Close()
{
	m_urlHandler.CloseStream();
	
	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = 0;
	}

	m_bHeaderRead = false;
	memset( &m_Header, 0, sizeof(EMSBINARYSTRMHEADER) );
	m_eType = EMSRT_UNKNOWN;
}

EMSVARIANTRECORD2* 
CEMSBinaryStream::ReadNext2()
{
	EMSVARIANTRECORD2* pRet = 0;

	if( !m_bHeaderRead )
	{
		THROW_RUNTIME_EXCEPTION( EMS_INVALID_STREAM_POS );
	}

	// Get stream at "current" position
	// Must be part of a sequence of ReadHeader, ReadNext, ReadNext, ...
	IEMSSeqStream* pStrm = _GetStream();

	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSBinMsgBody* pMsgBody = 0;

	try
	{
		pMsgBody = _AllocMsgBody();
		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			pRet = pMsgBody->ReadNext2();

			delete pMsgBody;
			pMsgBody = 0;
		}

		pStrm->Release();
		pStrm = 0;
	}
	catch( ... )
	{
		delete pMsgBody;
		pMsgBody = 0;

		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSBinaryStream::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	CEMSBinMsgBody* pMsgBody = 0;

	// Get writable stream
	IEMSSeqStream* pStrm = _GetStream( true );
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody();

		if( !pMsgBody )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pMsgBody->SetStream( pStrm );

		pMsgBody->WriteRecord2( record );

		delete pMsgBody;
		pMsgBody = NULL;

		pStrm->Release();
		pStrm = NULL;

	}
	catch( ... )
	{
		if( pMsgBody )
		{
			delete pMsgBody;
			pMsgBody = NULL;
		}

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
CEMSBinaryStream::Get( BYTE*& rabyData, ULONG& rulBytes )
{
	wchar_t* wszURL = 0;
	IEMSSeqStream* pStrm = 0;

	try
	{
		wszURL = m_urlHandler.GetURL();

		CEMSURLHandler oURLHandler;
		oURLHandler.SetURL( wszURL );

		pStrm = oURLHandler.OpenStream();

		if( !pStrm )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = EMS_OK;
		ULONG ulRead = 0;

		do
		{
			const ULONG culBytes = 128;
			BYTE abyBuf[ culBytes ];
			ulRead = 0;

			memset( abyBuf, 0, culBytes );

			hr = pStrm->Read( abyBuf, culBytes, &ulRead );

			if( ulRead > 0 )
			{
				CEMSArrayHelper::Concatenate( rabyData, rulBytes, abyBuf, ulRead );
			}

		} while( EMS_OK == hr && ulRead > 0 );

		pStrm->Release();
		pStrm = NULL;

		if( wszURL )
		{
			delete[] wszURL;
			wszURL = 0;
		}
	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = NULL;
		}

		if( wszURL )
		{
			delete[] wszURL;
			wszURL = 0;
		}

		throw;
	}
}

void 
CEMSBinaryStream::UpdateHeader( const EMSBINARYSTRMHEADER& crstrHeader )
{
	// Get stream positioned at the very start
	// Note that this will only work if this is the very first use of this stream!!!
	IEMSSeqStream* pStrm = _GetStreamStart( true );

	if( pStrm )
	{
		m_eType = crstrHeader.eRecType;

		unsigned long ulWritten = 0;
		EMS_RESULT hr = pStrm->Write( (const unsigned char*) &crstrHeader, sizeof(EMSBINARYSTRMHEADER), &ulWritten );

		pStrm->Release();
		pStrm = 0;

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}
}

IEMSSeqStream* 
CEMSBinaryStream::_GetStreamStart( const bool cbWriteable  )
{
	IEMSSeqStream* pStrm = 0;

	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = NULL;
	}
	
	// Open for editing if writeable.
	m_pStrm = m_urlHandler.OpenStream( cbWriteable, cbWriteable );

	if( m_pStrm )
	{
		pStrm = m_pStrm;
		pStrm->AddRef();
	}
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_INVALID_STREAM );
	}

	
	return pStrm;
}

// Get the stream .. at current position
IEMSSeqStream*
CEMSBinaryStream::_GetStream( const bool cbWriteable  )
{
	IEMSSeqStream* pStrm = 0;

	if( m_pStrm )
	{
		pStrm = m_pStrm;
		pStrm->AddRef();
	}
	else
	{
		// Member setting can override the supplied writable flag
		m_pStrm = m_urlHandler.OpenStream( cbWriteable );

		if( m_pStrm )
		{
			pStrm = m_pStrm;
			pStrm->AddRef();
		}
		else
		{
			THROW_RUNTIME_EXCEPTION( EMS_INVALID_STREAM );
		}

	}

	return pStrm;
}

CEMSBinMsgBody*
CEMSBinaryStream::_AllocMsgBody()
{
	CEMSBinMsgBody* pMsgBody = NULL;
	switch( m_eType )
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
