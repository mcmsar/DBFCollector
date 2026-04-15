/*********************************************************************
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

	$Log:
	$
********************************************************************/

#include "streamsink.h"

#include "emsexcpt.h"
#include "emsqueuememstrm.h"

const ULONG CEMSStreamSink::ms_culDefaultMaxBuf = 512000;	// Bytes

CEMSStreamSink::CEMSStreamSink() : CEMSLogClient(L"CEMSStreamSink"), m_pStrm(0), m_hEvent(0),
									m_ulMaxBufferSize( ms_culDefaultMaxBuf )
{
}


CEMSStreamSink::CEMSStreamSink( const CEMSStreamSink& x ) : CEMSLogClient(L"CEMSStreamSink"), 
																m_pStrm( x.m_pStrm ),
																m_owszSignalName( x.m_owszSignalName ),
																m_ulMaxBufferSize( x.m_ulMaxBufferSize )
{
	if( m_pStrm )
		m_pStrm->AddRef();
}

CEMSStreamSink::~CEMSStreamSink()
{
	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = 0;
	}

	if( m_hEvent )
	{
		CloseHandle( m_hEvent );
		m_hEvent = 0;
	}
}

//! Specify the name of an event to signal when new data is available.
void 
CEMSStreamSink::SetSignalName( const wchar_t* cwszSignal )
{
	if( cwszSignal )
		m_owszSignalName = cwszSignal;
}

IEMSSeqStream* 
CEMSStreamSink::GetStream()
{
	IEMSSeqStream* pRet = this;
	pRet->AddRef();
	return pRet;
}

EMS_RESULT
CEMSStreamSink::Read( BYTE *pv, ULONG cb, ULONG *pcbRead)
{
	EMS_RESULT hr = EMS_OK;

	IEMSSeqStream* pStrm = 0;

	try
	{
		pStrm = _GetStream();

		if( !pStrm )
		{
			EMSLOG_DEBUG( this, L"Failure getting pointer to stream for read." );

			THROW_NULL_POINTER_EXCEPTION();
		}

		hr = pStrm->Read( pv, cb, pcbRead );

		pStrm->Release();
		pStrm = 0;

	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return hr;
}

EMS_RESULT
CEMSStreamSink::Write( const BYTE *pv, ULONG cb, ULONG *pcbWritten)
{
	EMS_RESULT hr = EMS_OK;

	IEMSSeqStream* pStrm = 0;

	try
	{
		pStrm = _GetStream();

		if( !pStrm )
		{
			EMSLOG_DEBUG( this, L"Failure getting pointer to stream for write." );

			THROW_NULL_POINTER_EXCEPTION();
		}

		hr = pStrm->Write( pv, cb, pcbWritten );

		if( (EMS_OK == hr) && (*pcbWritten > 0) )
		{
			_OnNewData();
		}

		pStrm->Release();
		pStrm = 0;

	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return hr;
}

STDMETHODIMP_(ULONG) CEMSStreamSink::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSStreamSink::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSStreamSink::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT result = EMS_NOINTERFACE;
	LPUNKNOWN lpUnknown = 0;

	if (lppObj)
		*lppObj = lpUnknown;

	if (IsEqualIID(riid, IID_IEMSSeqStream))
	{
		lpUnknown = (LPUNKNOWN)(LPEMSSEQSTREAM)this;
	}
	else if (IsEqualIID(riid, IID_IUnknown))
	{
		lpUnknown = (LPUNKNOWN)this;
	}

	if (lpUnknown)
	{
		if (lppObj)
		{
			*lppObj = lpUnknown;

			lpUnknown->AddRef();
		}

		result = EMS_OK;
	}

	return result;
}

IEMSSeqStream* 
CEMSStreamSink::_GetStream()
{
	IEMSSeqStream* pRet = m_pStrm;

	if( !pRet )
	{
		CEMSQueueMemoryStream* pStrm = new CEMSQueueMemoryStream;

		if( !pStrm )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pStrm->SetMaxSize( m_ulMaxBufferSize );

		m_pStrm = pStrm;

		if( !m_pStrm )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pRet = m_pStrm;
	}

	pRet->AddRef();

	return pRet;
}

void			
CEMSStreamSink::_OnNewData()
{
	if( !m_hEvent )
	{
		_CreateEvent();
	}

	SetEvent( m_hEvent );
}

void			
CEMSStreamSink::_CreateEvent()
{
	if( !m_hEvent )
	{
		m_hEvent = CreateEventW( 0, FALSE, FALSE, m_owszSignalName.c_str() );
	}
}