/********************************************************************
*	Module:			RandBinaryStream.cpp 
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
	0.0	06Nov2003		ch		start
		26Nov2003		ch		WriteRecords() to return the number
								of records in the file.  

********************************************************************/

#pragma warning(disable:4786)	// Disable warning messages for stl debug symbol size.
#include <vector>
using std::vector;

#include <assert.h>
#include "igateway.h"
#include "emspipe.h"
#include "randbinarystream.h"
#include "emsexcpt.h"
#include "binmsgbody.h"

typedef vector<EMSVARIANTRECORD*>	EMSVARIANTVECTOR;
typedef vector<EMSVARIANTRECORD2*>	EMSVARIANT2VECTOR;

CEMSRandBinaryStream::CEMSRandBinaryStream()
									:	m_ulMaxRecords( 0 ),
										m_ulWriteOffset( 0 ),
										m_ulRecordCount( 0 )
{
}

// To create a circular stream
CEMSRandBinaryStream::CEMSRandBinaryStream( const unsigned long culMaxRecords ) 
									:	m_ulMaxRecords( culMaxRecords ),
										m_ulWriteOffset( 0 ),
										m_ulRecordCount( 0 )
{
	m_Header.ulMaxRecords = culMaxRecords;
}

CEMSRandBinaryStream::CEMSRandBinaryStream( const CEMSRandBinaryStream& binStream ) 
								:	CEMSBinaryStream(binStream),
									m_ulWriteOffset( binStream.m_ulWriteOffset ),
									m_ulMaxRecords( binStream.m_ulMaxRecords ),
									m_ulRecordCount( binStream.m_ulRecordCount )
{
}

CEMSRandBinaryStream::~CEMSRandBinaryStream()
{
}

EMSBINARYSTRMHEADER
CEMSRandBinaryStream::GetHeader()
{
	// Ensure that m_pStrm is populated
	_InitStream();

	if( !m_bHeaderRead )
	{
		CEMSBinaryStream::GetHeader();

		m_ulMaxRecords = m_Header.ulMaxRecords;
		m_ulWriteOffset = m_Header.ulWriteOffset;
		m_ulRecordCount = m_Header.ulRecordCount;
	}

	return m_Header;
}


void
CEMSRandBinaryStream::ResetHeader( EMSBINARYSTRMHEADER& header )
{
	// Get stream positioned at the very start
	IEMSSeqStream* pStrm = _GetStreamStart();

	if( pStrm )
	{
		// Allow initialization but not changes
		assert( m_eType == EMSRT_UNKNOWN || m_eType == header.eRecType );
		m_eType = header.eRecType;

		// We control these fields if this is a circular stream
		if ( m_ulMaxRecords > 0 )
		{
			header.ulMaxRecords = m_ulMaxRecords;
			header.ulWriteOffset = m_ulWriteOffset;
			header.ulRecordCount = m_ulRecordCount;
		}

		// Pick up supplied changes
		m_Header = header;

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

// Reads all records from the stream
// Allocated memory must be released by the caller.
// The caller should check the returned count and make any corrections 
// to the header if necessary
void
CEMSRandBinaryStream::ReadRecords(	unsigned long&		ulRead, 
									EMSVARIANTRECORD*&	aRecord )
{
	IEMSSeqStream*		pStrm = NULL;
	CEMSBinMsgBody*		pMsgBody = 0;
	EMSVARIANTRECORD*	pRet = 0;
	EMSVARIANTVECTOR	varvector;

	ulRead = 0L;
	aRecord = NULL;

	// Position the stream at the start of data
	pStrm = _GetRecordStreamStart();

	try
	{
		pMsgBody = _AllocMsgBody();
		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			BOOL bDone = FALSE;
			while ( !bDone )
			{
				pRet = pMsgBody->ReadNext();
				if ( pRet )
				{
					varvector.push_back( pRet );
					pRet = NULL;
				}
				else
				{
					bDone = TRUE;
				}
			}

			// Allocate the output buffer
			aRecord = new EMSVARIANTRECORD[varvector.size()];
			if ( !aRecord )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			ulRead = varvector.size();
			for ( int i=0; i<varvector.size(); i++ )
			{
				memcpy( &(aRecord[i]), varvector[i], sizeof(EMSVARIANTRECORD) );
				delete varvector[i];
			}
			varvector.clear();

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

	}
	catch( ... )
	{
		delete[] aRecord;
		delete pRet;
		delete pMsgBody;

		for ( int i=0; i<varvector.size(); i++ )
		{
			delete varvector[i];
		}
		varvector.clear();

		if( pStrm )
		{
			pStrm->Release();
		}
		throw;
	}

	return;
}

// Reads all records from the stream
// Allocated memory must be released by the caller.
// The caller should check the returned count and make any corrections 
// to the header if necessary
void
CEMSRandBinaryStream::ReadRecords(	unsigned long&		ulRead, 
									EMSVARIANTRECORD2*&	aRecord )
{
	IEMSSeqStream*		pStrm = NULL;
	CEMSBinMsgBody*		pMsgBody = 0;
	EMSVARIANTRECORD2*	pRet = 0;
	EMSVARIANT2VECTOR	varvector;

	ulRead = 0L;
	aRecord = NULL;

	// Position the stream at the start of data
	pStrm = _GetRecordStreamStart();

	try
	{
		pMsgBody = _AllocMsgBody();
		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			BOOL bDone = FALSE;
			while ( !bDone )
			{
				pRet = pMsgBody->ReadNext2();
				if ( pRet )
				{
					varvector.push_back( pRet );
					pRet = NULL;
				}
				else
				{
					bDone = TRUE;
				}
			}

			// Allocate the output buffer
			aRecord = new EMSVARIANTRECORD2[varvector.size()];
			if ( !aRecord )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			ulRead = varvector.size();
			for ( int i=0; i<varvector.size(); i++ )
			{
				memcpy( &(aRecord[i]), varvector[i], sizeof(EMSVARIANTRECORD2) );
				delete varvector[i];
			}
			varvector.clear();

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

	}
	catch( ... )
	{
		delete[] aRecord;
		delete pRet;
		delete pMsgBody;

		for ( int i=0; i<varvector.size(); i++ )
		{
			delete varvector[i];
		}
		varvector.clear();

		if( pStrm )
		{
			pStrm->Release();
		}
		throw;
	}

	return;
}

unsigned long
CEMSRandBinaryStream::WriteRecords( const unsigned long		culCount, 
								    const EMSVARIANTRECORD*	aRecord )
{
	return _WriteRecords( culCount, aRecord );
}

unsigned long
CEMSRandBinaryStream::WriteRecords( const unsigned long		culCount, 
								    const EMSVARIANTRECORD2*	aRecord )
{
	return _WriteRecords( culCount, aRecord );
}

void
CEMSRandBinaryStream::WriteRecord( const EMSVARIANTRECORD& record )
{
	_WriteRecords( 1, &record );
}

void
CEMSRandBinaryStream::WriteRecord( const EMSVARIANTRECORD2& record )
{
	_WriteRecords( 1, &record );
}


unsigned long
CEMSRandBinaryStream::_WriteRecords(const unsigned long		culCount, 
									const EMSVARIANTRECORD*	aRecord )
{
	assert (culCount > 0 && aRecord );

	CEMSBinMsgBody* pMsgBody = 0;

	IEMSSeqStream*	pStrm = _GetRecordStream();
	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody();

		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			for ( int i=0; i<culCount; i++ )
			{
				pMsgBody->WriteRecord( aRecord[i] );
				iWritten++;

				if ( m_ulMaxRecords != 0 )
				{
					m_ulWriteOffset++;
					if ( m_ulWriteOffset == m_ulMaxRecords )
					{
						// have hit max
						break;
					}
				}
			}

			// Increment the record count
			m_ulRecordCount += iWritten;
			// If this is a circular stream then could be recycling 
			if ( m_ulMaxRecords != 0 && m_ulRecordCount > m_ulMaxRecords )
			{
				// in that case hold at the max
				m_ulRecordCount = m_ulMaxRecords;
			}

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

		// Did we manage to write everything?
		// If not, assume that we hit the maximum number of records
		// Therefore need to write a 2nd block at the start of the 
		// data section in this stream
		if ( iWritten != culCount )
		{
			_WriteRecords( culCount-iWritten, &(aRecord[iWritten]) );
		}
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
	return m_ulRecordCount;
}

unsigned long
CEMSRandBinaryStream::_WriteRecords(const unsigned long		culCount, 
									const EMSVARIANTRECORD2*	aRecord )
{
	assert (culCount > 0 && aRecord );

	CEMSBinMsgBody* pMsgBody = 0;

	IEMSSeqStream*	pStrm = _GetRecordStream();
	try
	{
		int iWritten = 0;

		pMsgBody = _AllocMsgBody();

		if( pMsgBody )
		{
			pMsgBody->SetStream( pStrm );

			for ( int i=0; i<culCount; i++ )
			{
				pMsgBody->WriteRecord2( aRecord[i] );
				iWritten++;

				if ( m_ulMaxRecords != 0 )
				{
					m_ulWriteOffset++;
					if ( m_ulWriteOffset == m_ulMaxRecords )
					{
						// have hit max
						break;
					}
				}
			}

			// Increment the record count
			m_ulRecordCount += iWritten;
			// If this is a circular stream then could be recycling 
			if ( m_ulMaxRecords != 0 && m_ulRecordCount > m_ulMaxRecords )
			{
				// in that case hold at the max
				m_ulRecordCount = m_ulMaxRecords;
			}

			delete pMsgBody;
			pMsgBody = NULL;
		}

		pStrm->Release();
		pStrm = NULL;

		// Did we manage to write everything?
		// If not, assume that we hit the maximum number of records
		// Therefore need to write a 2nd block at the start of the 
		// data section in this stream
		if ( iWritten != culCount )
		{
			_WriteRecords( culCount-iWritten, &(aRecord[iWritten]) );
		}
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
	return m_ulRecordCount;
}

// Get the stream .. at current position
void
CEMSRandBinaryStream::_InitStream()
{
	if( !m_pStrm )
	{
		// Member setting can override the supplied writable flag
		m_pStrm = m_urlHandler.OpenStream( true, true );

		if( !m_pStrm )
		{
			THROW_RUNTIME_EXCEPTION( EMS_INVALID_STREAM );
		}
	}
}

// Get the stream ... positioned at the very start
IEMSSeqStream* 
CEMSRandBinaryStream::_GetStreamStart()
{
	IEMSSeqStream* pStrm = 0;

	// Ensure that m_pStrm is populated
	_InitStream();

	IEMSRandomStream* pRandStrm = 0;
	EMS_RESULT hr = m_pStrm->QueryInterface( IID_IEMSRandomStream, (void**) &pRandStrm );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	try
	{
		hr = pRandStrm->MoveFirst();

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pRandStrm->QueryInterface( IID_IEMSSeqStream, (void**) &pStrm );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pRandStrm->Release();
		pRandStrm = 0;
	}
	catch( ... )
	{
		if( pRandStrm )
			pRandStrm->Release();
		pRandStrm = 0;

		if( pStrm )
			pStrm->Release();
		pStrm = 0;
	}

	return pStrm;
}

// Return a read stream positioned at the start of data
// Positioned at the start of data
// If you want a writable stream use _GetRecordStream()
IEMSSeqStream* 
CEMSRandBinaryStream::_GetRecordStreamStart()
{
	IEMSSeqStream* pStrm = 0;

	// Ensure that m_pStrm is populated
	_InitStream();

	IEMSRandomStream* pRandStrm = 0;
	EMS_RESULT hr = m_pStrm->QueryInterface( IID_IEMSRandomStream, (void**) &pRandStrm );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	try
	{
		// Position after the heder
		hr = pRandStrm->Move( sizeof( EMSBINARYSTRMHEADER ) );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pRandStrm->QueryInterface( IID_IEMSSeqStream, (void**) &pStrm );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pRandStrm->Release();
		pRandStrm = 0;
	}
	catch( ... )
	{
		if( pRandStrm )
			pRandStrm->Release();
		pRandStrm = 0;

		if( pStrm )
			pStrm->Release();
		pStrm = 0;
	}

	return pStrm;
}

// Positioned at the next write position
// This will be either the end of the stream 
// OR at an offset position if this is a circular stream
IEMSSeqStream* 
CEMSRandBinaryStream::_GetRecordStream()
{
	IEMSSeqStream* pStrm = 0;

	// Ensure that m_pStrm is populated
	_InitStream();

	IEMSRandomStream* pRandStrm = 0;
	EMS_RESULT hr = m_pStrm->QueryInterface( IID_IEMSRandomStream, (void**) &pRandStrm );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	try
	{
		if ( m_ulMaxRecords == 0 )
		{
			// not circular so just position at end
			hr = pRandStrm->MoveLast();
		}
		else if ( m_ulWriteOffset == m_ulMaxRecords )
		{
			// Have hit the end so next write is to the beginning
			hr = pRandStrm->Move( sizeof( EMSBINARYSTRMHEADER ) );
			if ( SUCCEEDED(hr) )
			{
				m_ulWriteOffset = 0;
			}
		}
		else
		{
			// Use current offset
			int iOffset = sizeof( EMSBINARYSTRMHEADER ) + m_ulWriteOffset * _GetRecordSize();
			hr = pRandStrm->Move( iOffset );
		}

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pRandStrm->QueryInterface( IID_IEMSSeqStream, (void**) &pStrm );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pRandStrm->Release();
		pRandStrm = 0;
	}
	catch( ... )
	{
		if( pRandStrm )
			pRandStrm->Release();
		pRandStrm = 0;

		if( pStrm )
			pStrm->Release();
		pStrm = 0;
	}

	return pStrm;
}


int
CEMSRandBinaryStream::_GetRecordSize()
{
	int iSize = 0;
	switch( m_eType )
	{
		case EMSRT_CALIB406:
			iSize = sizeof( EMSCALIB406DATA );
			break;
		case EMSRT_LOCATE:
			iSize = sizeof( EMSLOCATE );
			break;
        case EMSRT_CBC:
			iSize = sizeof( EMSCBCDATA );
            break;
        case EMSRT_LOG:
			iSize = sizeof( EMSLOGDATA );
            break;
        case EMSRT_SPECTRUM:
			iSize = sizeof( EMSSPECTRUM );
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
        case EMSRT_SARR_CALIB_STATS:
        case EMSRT_SENSOR:
        case EMSRT_STAT_SUMMARY:
			iSize = sizeof( EMSLEOSTATUSUPDATE );
            break;
        case EMSRT_ORBIT:
			iSize = sizeof( EMSTLERECORD );
            break;
        case EMSRT_SARP_CALIB:
			iSize = sizeof( EMSSARPCALIBDATA );
            break;
        case EMSRT_SARP:
			iSize = sizeof( EMSSARPDATA );
            break;
        case EMSRT_SARR_CALIB:
			iSize = sizeof( EMSSARRCALIBDATA );
            break;
        case EMSRT_SARR:
			iSize = sizeof( EMSSARRDATA );
            break;
        case EMSRT_SAT_TRACK:
			iSize = sizeof( EMSSATTRACKRECORD );
            break;
        case EMSRT_CALIBCBC:
			iSize = sizeof( EMSCBCOUTPUTDATA );
            break;
        case EMSRT_COMB406:
			iSize = sizeof( EMSCOMBINE406DATA );
            break;
        case EMSRT_CONFIG:
			iSize = sizeof( EMSCONFIGDATA );
            break;
        case EMSRT_RESIDUAL:
			iSize = sizeof( EMSRESIDUALDATA );
            break;
		case EMSRT_SARR_EXT:
			iSize = sizeof( EMSSARRDATAEX );
			break;
		case EMSRT_CALIB406_EXT:
			iSize = sizeof( EMSCALIB406DATAEXT );
			break;
		default:
			assert( FALSE );
			THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
			break;
	}
	return iSize;
}
