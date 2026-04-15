/********************************************************************
*	Module:			pksink.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
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

	0.0	01/03/22		rvw	start

********************************************************************/
#include "pksink.h"

CEMSPacketSink::CEMSPacketSink( BYTE cType, INT nMaxLength )
{
	m_lRefCount = 1;
	m_cType = cType;
	m_nMaxLength = nMaxLength;
	m_lpStream = 0;
	m_dwReceivingProcessID = 0L;
	m_hOnDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CEMSPacketSink::~CEMSPacketSink()
{
	if ( m_hOnDataEvent != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hOnDataEvent );
		m_hOnDataEvent = INVALID_HANDLE_VALUE;
	}

	if ( m_lpStream )
	{
		m_lpStream->Release();
		m_lpStream = 0;
	}
}

STDMETHODIMP_(ULONG) CEMSPacketSink::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSPacketSink::Release()
{
	LONG lRef = InterlockedDecrement( &m_lRefCount );

	if ( lRef == 0 )
	{
		delete this;
	}
	
	return (ULONG)lRef;
}

STDMETHODIMP CEMSPacketSink::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT hr = E_NOINTERFACE;

	if ( lppObj )
	{
		LPUNKNOWN lpUnknown = 0;

		*lppObj = 0;

		if ( riid == IID_IUnknown || riid == IID_IEMSDataSink )
		{
  			lpUnknown = (IUnknown *)(LPEMSDATASINK)this;
		}
		else if ( riid == IID_IEMSDataSink2 )
		{
  			lpUnknown = (IUnknown *)(LPEMSDATASINK2)this;
		}

		if ( lpUnknown )
		{
			lpUnknown->AddRef();
  			hr = S_OK;
 		}
		*lppObj = lpUnknown;
	}
	else
	  	hr = E_INVALIDARG;

	return hr;
}

STDMETHODIMP CEMSPacketSink::SetType( BYTE cDataType )
{
	m_cType = cDataType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::GetType( BYTE __RPC_FAR *lpcDataType )
{
	if ( lpcDataType )
		*lpcDataType = m_cType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::SetMaxLength( INT nMaxLength )
{
	m_nMaxLength = nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpnMaxLength )
	{
		if ( ( m_nMaxLength == 0 ) && m_lpStream )
		{
			int nMaxLen = 0;

			hr = m_lpStream->GetMaxLength( &nMaxLen );

			*lpnMaxLength = nMaxLen;
		}
		else
			*lpnMaxLength = m_nMaxLength;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

STDMETHODIMP CEMSPacketSink::SetStream( LPEMSPACKETSTREAM lpStream )
{
	if ( m_lpStream )
	{
		m_lpStream->Release();
		m_lpStream = 0;
	}

	if ( lpStream )
	{
		m_lpStream = lpStream;
		m_lpStream->AddRef();
	}
	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream )
{
	if ( lplpStream )
		*lplpStream = m_lpStream;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::OnDataAvailable( DWORD dwSize, DWORD dwFlags )
{
	if ( m_hOnDataEvent )
		SetEvent( m_hOnDataEvent );

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSink::SetReceivingProcessID( const DWORD cdwProcessID )
{
	m_dwReceivingProcessID = cdwProcessID;
	return EMS_OK;
}
STDMETHODIMP CEMSPacketSink::GetReceivingProcessID( DWORD* pdwProcessID )
{
	EMS_RESULT hr = EMS_BAD_PARAM;
	if ( pdwProcessID )
	{
		*pdwProcessID = m_dwReceivingProcessID;
		hr = EMS_OK;
	}
	return hr;
}

EMS_RESULT CEMSPacketSink::Read( BYTE *lpBuffer, ULONG ulMaxLength, ULONG *lpulRead )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpStream )
	{
		hr = m_lpStream->Read( lpBuffer, ulMaxLength, lpulRead );
	}

	return hr;
}
