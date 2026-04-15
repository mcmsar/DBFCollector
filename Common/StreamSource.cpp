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

#include "streamsource.h"

#include "emsexcpt.h"
#include "emsqueuememstrm.h"

const ULONG CEMSStreamSource::ms_culDefaultMaxBuf = 512000;	// Bytes

CEMSStreamSource::CEMSStreamSource() : CEMSLogClient(L"CEMSStreamSource"), m_pStrm(0), m_hEvent(0),
									m_ulMaxBufferSize( ms_culDefaultMaxBuf ), m_bMayHoldData(false),
									m_bInUse(true)
{
}


CEMSStreamSource::CEMSStreamSource( const CEMSStreamSource& x ) : CEMSLogClient(L"CEMSStreamSource"), 
																m_pStrm( x.m_pStrm ),
																m_owszSignalName( x.m_owszSignalName ),
																m_ulMaxBufferSize( x.m_ulMaxBufferSize ),
																m_bMayHoldData( x.m_bMayHoldData ),
																m_bInUse(x.m_bInUse)
{
	if( m_pStrm )
		m_pStrm->AddRef();
}

CEMSStreamSource::~CEMSStreamSource()
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
CEMSStreamSource::SetSignalName( const wchar_t* cwszSignal )
{
	if( cwszSignal )
		m_owszSignalName = cwszSignal;
}

IEMSSeqStream* 
CEMSStreamSource::GetStream()
{
	IEMSSeqStream* pRet = this;
	pRet->AddRef();
	return pRet;
}

EMS_RESULT
CEMSStreamSource::Read( BYTE *pv, ULONG cb, ULONG *pcbRead)
{
	EMS_RESULT hr = EMS_OK;

	IEMSSeqStream* pStrm = 0;

	try
	{
		m_csReadWrite.Enter();

		pStrm = _GetStream();

		if( !pStrm )
		{
			EMSLOG_DEBUG( this, L"Failure getting pointer to stream for read." );

			THROW_NULL_POINTER_EXCEPTION();
		}

		hr = pStrm->Read( pv, cb, pcbRead );

		if( EMS_OK == hr &&
			*pcbRead > 0 )
			m_bMayHoldData = true;
		else
			m_bMayHoldData = false;

		pStrm->Release();
		pStrm = 0;

		m_csReadWrite.Leave();

	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		m_csReadWrite.Leave();

		throw;
	}

	return hr;
}

EMS_RESULT
CEMSStreamSource::Write( const BYTE *pv, ULONG cb, ULONG *pcbWritten)
{
	EMS_RESULT hr = EMS_OK;

	IEMSSeqStream* pStrm = 0;

	try
	{
		m_csReadWrite.Enter();

		pStrm = _GetStream();

		if( !pStrm )
		{
			EMSLOG_DEBUG( this, L"Failure getting pointer to stream for write." );

			THROW_NULL_POINTER_EXCEPTION();
		}

		hr = pStrm->Write( pv, cb, pcbWritten );

		if( (EMS_OK == hr) && (*pcbWritten > 0) )
		{
			m_bMayHoldData = true;
			_OnNewData();
		}

		pStrm->Release();
		pStrm = 0;

		m_csReadWrite.Leave();

	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		m_csReadWrite.Leave();

		throw;
	}

	return hr;
}

STDMETHODIMP_(ULONG) CEMSStreamSource::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSStreamSource::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSStreamSource::QueryInterface(REFIID riid, LPVOID *lppObj)
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

bool 
CEMSStreamSource::HasData()
{
	bool bRet = false;

	try
	{
		m_csReadWrite.Enter();

		bRet = m_bMayHoldData;

		m_csReadWrite.Leave();
	}
	catch( ... )
	{
		m_csReadWrite.Leave();
		throw;
	}

	return bRet;
}

void 
CEMSStreamSource::SetInUse( const bool cbInUse )
{
	try
	{
		m_csReadWrite.Enter();

		m_bInUse = cbInUse;

		m_csReadWrite.Leave();
	}
	catch( ... )
	{
		m_csReadWrite.Leave();
		throw;
	}
}

bool 
CEMSStreamSource::GetInUse()
{
	bool bRet = false;

	try
	{
		m_csReadWrite.Enter();

		bRet = m_bInUse;

		m_csReadWrite.Leave();
	}
	catch( ... )
	{
		m_csReadWrite.Leave();
		throw;
	}

	return bRet;
}

IEMSSeqStream* 
CEMSStreamSource::_GetStream()
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
CEMSStreamSource::_OnNewData()
{
	if( !m_hEvent )
	{
		_CreateEvent();
	}

	SetEvent( m_hEvent );
}

void			
CEMSStreamSource::_CreateEvent()
{
	if( !m_hEvent )
	{
		m_hEvent = CreateEventW( 0, FALSE, FALSE, m_owszSignalName.c_str() );
	}
}