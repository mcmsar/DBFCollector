/********************************************************************
*	Module:			EMSMStrm.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:	
*	Description: 		CEMSMemoryStream implementation
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/30 	rvw	start

********************************************************************/
#include <stdio.h>

#include "emsqueuememstrm.h"
#include "emserror.h"

CEMSQueueMemoryStream::CEMSQueueMemoryStream( ) : CApiObjBase("CEMSQueueMemoryStream")
{
}

CEMSQueueMemoryStream::~CEMSQueueMemoryStream() 
{
}

EMS_RESULT CEMSQueueMemoryStream::SetMaxSize( const ULONG culBytes )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		m_csBuffer.Enter();

		m_oQueue.SetMaxSize( culBytes );

		m_csBuffer.Leave();
	}
	catch( ... )
	{
		m_csBuffer.Leave();

		throw;
	}

	return hr;
}


STDMETHODIMP_(ULONG) CEMSQueueMemoryStream::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSQueueMemoryStream::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSQueueMemoryStream::QueryInterface(REFIID riid, LPVOID *lppObj)
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

STDMETHODIMP CEMSQueueMemoryStream::Read( BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbRead )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		m_csBuffer.Enter();

		if ( pv && cb )
		{
			ULONG ulQueueSize = m_oQueue.Count();

			for( ULONG l = 0; (l < cb) && (l < ulQueueSize); l++ )
			{
				BYTE byValue = m_oQueue.Pop();

				memcpy( pv + l, &byValue, sizeof(BYTE) );

				(*pcbRead)++;
			}

			if( ulQueueSize < cb )
			{
				hr = EMS_FALSE;
			}

		}
		else
			hr = EMS_BAD_PARAM;

		m_csBuffer.Leave();
	}
	catch( CEMSException& e )
	{
		m_csBuffer.Leave();

		hr = e.GetErrCode();

	}
	catch( ... )
	{
		m_csBuffer.Leave();

		hr = EMS_IO_ERROR;
	}

	return hr;
}
        
STDMETHODIMP CEMSQueueMemoryStream::Write( const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesWritten = 0;

	try
	{
		m_csBuffer.Enter();

		if ( pv && cb )
		{
			if( cb <=  m_oQueue.GetMaxSize() - m_oQueue.Count() )
			{
				for( ULONG l = 0; l < cb; l++ )
				{
					m_oQueue.Push( *(pv+l) );

					(*pcbWritten)++;
				}
			}
			else
			{
				throw CEMSException( EMS_OVERFLOW );
			}

		}
		else
			hr = EMS_BAD_PARAM;

		m_csBuffer.Leave();
	}
	catch( CEMSException& e )
	{
		m_csBuffer.Leave();

		hr = e.GetErrCode();

	}
	catch( ... )
	{
		m_csBuffer.Leave();

		hr = EMS_IO_ERROR;
	}

	return hr;
}

