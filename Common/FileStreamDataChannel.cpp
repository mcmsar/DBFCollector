/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/
#pragma warning(disable:4786)

#include "filestreamdatachannel.h"
#include "emsexcpt.h"
#include "streamsink.h"
#include "streamsource.h"
#include "emsfstrm.h"
#include "convutility.h"
#include "emsurl.h"

CEMSFileStreamDataChannel::CEMSFileStreamDataChannel()  : m_pFS(0), m_bWriteable(false), m_bRunning(false),
													m_bMaybeMoreSourceData(false)
{
	 SetParent( L"CEMSFileStreamDataChannel" );
}

CEMSFileStreamDataChannel::CEMSFileStreamDataChannel( const CEMSFileStreamDataChannel& x ) :
															CEMSStreamDataChannel( x ),
															m_pFS(x.m_pFS),
															m_bWriteable(x.m_bWriteable),
															m_bRunning(false),
															m_bMaybeMoreSourceData(false)
{
	SetParent( L"CEMSFileStreamDataChannel" );

	if( m_pFS )
		m_pFS->AddRef();
}

CEMSFileStreamDataChannel::~CEMSFileStreamDataChannel()
{
	Deactivate();
}

void 
CEMSFileStreamDataChannel::ConnectSinkStream( IEMSSeqStream*& pSink, const wchar_t* cwszSignalName,
											const ULONG culMaxBufferSize )
{
	if( !cwszSignalName )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	CEMSStreamSink* pNewSink = 0;

	try
	{
		m_oCS.Enter();

		pNewSink = new CEMSStreamSink;

		if( !pNewSink )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pNewSink->SetSignalName( cwszSignalName );
		pNewSink->SetMaxBufferSize( culMaxBufferSize );

		_AddSink( pNewSink );

		pSink = pNewSink->GetStream();

		pNewSink->Release();
		pNewSink = 0;

		m_oCS.Leave();
	
	}
	catch( ... )
	{
		if( pNewSink )
		{
			pNewSink->Release();
			pNewSink = 0;
		}

		if( pSink )
		{
			pSink->Release();
			pSink = 0;
		}

		m_oCS.Leave();

		throw;
	}
}

void 
CEMSFileStreamDataChannel::DisconnectSinkStream( IEMSSeqStream* pSink )
{
	try
	{
		m_oCS.Enter();

		if( 0 == _RemoveSink( pSink ) )
		{
			_ReleaseFile();
		}

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();

		throw;
	}
}

void 
CEMSFileStreamDataChannel::ConnectSourceStream( IEMSSeqStream*& pSource, const wchar_t* cwszSignalName,
									const ULONG culMaxBufferSize )
{
	if( !cwszSignalName )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	CEMSStreamSource* pNewSource = 0;

	try
	{
		m_oCS.Enter();

		pNewSource = new CEMSStreamSource;

		if( !pNewSource )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pNewSource->SetSignalName( cwszSignalName );
		pNewSource->SetMaxBufferSize( culMaxBufferSize );

		_AddSource( pNewSource );

		pSource = pNewSource->GetStream();

		pNewSource->Release();
		pNewSource = 0;

		m_oCS.Leave();
	
	}
	catch( ... )
	{
		if( pNewSource )
		{
			pNewSource->Release();
			pNewSource = 0;
		}

		if( pSource )
		{
			pSource->Release();
			pSource = 0;
		}

		m_oCS.Leave();

		throw;
	}
}

void 
CEMSFileStreamDataChannel::DisconnectSourceStream( IEMSSeqStream* pSource )
{
	try
	{
		m_oCS.Enter();

		_RemoveSource( pSource );

/*		if( 0 == _RemoveSource( pSource ) )
		{
			_ReleaseFile();
		}
*/

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
}

void 
CEMSFileStreamDataChannel::Activate()
{
	try
	{
		m_oCS.Enter();
		
		if( !m_bRunning )
		{
			start();

			// Give the thread a chance to start.
			Sleep( 100 );
		}

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();

		throw;
	}
}

void 
CEMSFileStreamDataChannel::Deactivate()
{
	try
	{
		m_oCS.Enter();

		if( m_bRunning )
		{
			SignalStop();

			if( !wait( 10000 ) )
				stop();
		}

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();

		throw;
	}
}

void 
CEMSFileStreamDataChannel::GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSFileStreamDataChannel::run()
{
	m_bRunning = true;

	try
	{
		_OpenFile();

		// Iterate over sources/sinks to see if any have data to write/read to the file.
		// Even if requested, don't stop if there is still more source data to write.
		do 
		{
			if( m_bWriteable )
				_ProcessSources();
			else
				_ProcessSinks();
		} while( !WaitForStop( 1 ) || 			
			m_bMaybeMoreSourceData );
			

		_ReleaseFile();

	}
	catch( CEMSException& e )
	{
		LogException( e );
	}
	catch( ... )
	{
		LogMsg( EMSLogMsgAlarm, __FILE__, __LINE__, L"Exception running file stream data channel thread.");
	}

	m_bRunning = false;
}

void
CEMSFileStreamDataChannel::_ReleaseFile()
{
	if( m_pFS )
	{
		m_pFS->Release();
		m_pFS = 0;
	}
}

void 
CEMSFileStreamDataChannel::_OpenFile()
{
	if( !m_pFS )
	{
		m_pFS = new CEMSFileStream;

		if( !m_pFS )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}

#if defined(UNICODE) || defined(_UNICODE)
	EMS_RESULT hr = m_pFS->OpenFile( _GetFileName().c_str(), 
#else
	EMS_RESULT hr = m_pFS->OpenFile( CEMSConversionUtil::ConvertToString( _GetFileName().c_str() ).c_str(), 
#endif
									m_bWriteable ? TRUE : FALSE,
									m_bWriteable ? TRUE : FALSE,
									m_bWriteable ? TRUE : FALSE );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION(hr);
	}
}

void
CEMSFileStreamDataChannel::_ProcessSources()
{
	// Transfer data held in sources to the file.

	BYTE* abySourceData = 0;

	try
	{
		if( !m_pFS )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}


		ULONG ulBytes = _ReadSources( abySourceData );

		if( ulBytes > 0 )
		{
			m_bMaybeMoreSourceData = true;

			ULONG ulWritten = 0;
			EMS_RESULT hr = m_pFS->Write( abySourceData, ulBytes, &ulWritten );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

			hr = m_pFS->Flush();

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

		}
		else
			m_bMaybeMoreSourceData = false;

		if( abySourceData )
		{
			delete[] abySourceData;
			abySourceData = 0;
		}
	}
	catch( ... )
	{
		if( abySourceData )
		{
			delete[] abySourceData;
			abySourceData = 0;
		}

		throw;
	}
}

void
CEMSFileStreamDataChannel::_ProcessSinks()
{
	// Transfer data from file into sinks.
	try
	{
		if( !m_pFS )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		const ULONG culBytesPerRead = 4096;
		BYTE abyDataRead[ culBytesPerRead ];
		memset( abyDataRead, 0, culBytesPerRead );

		EMS_RESULT hr = EMS_OK;

		while( EMS_OK == hr )
		{
			ULONG ulRead = 0;
			hr = m_pFS->Read( abyDataRead, culBytesPerRead, &ulRead );

			if( EMS_OK == hr &&
				ulRead > 0 )
			{
				WriteData( abyDataRead, ulRead );
			}
		}
	}
	catch( ... )
	{
		throw;
	}
}

std::wstring
CEMSFileStreamDataChannel::_GetFileName()
{
	std::wstring owszURL = _GetURL();

	if( owszURL.empty() )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	CEMSURL oURL( owszURL.c_str() );

	return oURL.GetPath();
}