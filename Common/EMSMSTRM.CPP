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

#include "emsmstrm.h"
#include "emserror.h"

CEMSMemoryStream::CEMSMemoryStream( ) : CApiObjBase("CEMSMemoryStream")
{
	m_lpBuffer = 0;
	m_ulBufferLength = 0;
	m_ulBufferAllocated = 0;
	m_ulBufferPosition = 0;
}

CEMSMemoryStream::~CEMSMemoryStream() 
{
	Free();
}

EMS_RESULT CEMSMemoryStream::Allocate( ULONG ulBytes )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_lpBuffer )
	{
		m_lpBuffer = new BYTE [ ulBytes ];

		if ( m_lpBuffer )
		{
			m_ulBufferAllocated = ulBytes;

			memset( m_lpBuffer, 0, ulBytes );
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_ALREADY_INITIALIZED;

	return hr;
}

EMS_RESULT CEMSMemoryStream::Reset( void )
{
	EMS_RESULT hr = EMS_OK;

	m_ulBufferLength = 0;
	m_ulBufferPosition = 0;

	return hr;
}

EMS_RESULT CEMSMemoryStream::Free( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpBuffer )
	{
		delete [ ] m_lpBuffer;
		m_lpBuffer = 0;
		m_ulBufferAllocated = 0;

		Reset();
	}
	else
		hr = EMS_NOT_INITIALIZED;

	return hr;
}

ULONG CEMSMemoryStream::SetPosition( ULONG ulOffset )
{
	if ( ulOffset > m_ulBufferAllocated )
		ulOffset = m_ulBufferAllocated;

	if ( ulOffset > m_ulBufferLength )
	{
// delete ***		ulOffset = m_ulBufferLength;
		m_ulBufferLength = ulOffset;
	}

	m_ulBufferPosition = ulOffset;

	return m_ulBufferPosition;
}

STDMETHODIMP_(ULONG) CEMSMemoryStream::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSMemoryStream::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSMemoryStream::QueryInterface(REFIID riid, LPVOID *lppObj)
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

STDMETHODIMP CEMSMemoryStream::Read( BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbRead )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesRead = 0;

	if ( pv && cb )
	{
		if ( m_lpBuffer )
		{
			if ( m_ulBufferPosition + cb > m_ulBufferLength )
				cb = m_ulBufferLength - m_ulBufferPosition;

			if ( cb )
			{
				memcpy( pv, &m_lpBuffer[ m_ulBufferPosition ], cb );

				ulBytesRead = cb;

				m_ulBufferPosition += ulBytesRead;
			}
		}
		else
			hr = EMS_NOT_INITIALIZED;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( pcbRead )
		*pcbRead = ulBytesRead;

	return hr;
}
        
STDMETHODIMP CEMSMemoryStream::Write( const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesWritten = 0;

	if ( pv && cb )
	{
		if ( m_lpBuffer )
		{
			if ( m_ulBufferPosition + cb > m_ulBufferAllocated )
				cb = m_ulBufferAllocated - m_ulBufferPosition;

			if ( cb )
			{
				memcpy( &m_lpBuffer[ m_ulBufferPosition ], pv, cb );

				ulBytesWritten = cb;
			
				m_ulBufferPosition += ulBytesWritten;

				if ( m_ulBufferPosition > m_ulBufferLength )
					m_ulBufferLength = m_ulBufferPosition;
			}
		}
		else
			hr = EMS_NOT_INITIALIZED;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( pcbWritten )
		*pcbWritten = ulBytesWritten;

	return hr;
}

