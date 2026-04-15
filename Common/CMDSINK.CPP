/********************************************************************
*	Module:			cmdsink.cpp
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
#include "cmdsink.h"

CEMSCommandSink::CEMSCommandSink( BYTE cCmdType, INT nMaxLength )
{
	m_lRefCount = 1;
	m_cType = EMS_PIPE_COMMAND_CHANNEL;
	m_cCmdType = cCmdType;
	m_nMaxLength = nMaxLength;
	m_lpStream = 0;
	m_hOnDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CEMSCommandSink::~CEMSCommandSink()
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

STDMETHODIMP_(ULONG) CEMSCommandSink::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSCommandSink::Release()
{
	LONG lRefCount = InterlockedDecrement( &m_lRefCount );

	if ( lRefCount == 0 )
	{
		delete this;
	}

	return (ULONG)lRefCount;
}

STDMETHODIMP CEMSCommandSink::QueryInterface(REFIID riid, LPVOID *lppObj)
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
		else if ( riid == IID_IEMSCommandSink )
		{
  		lpUnknown = (IUnknown *)(LPEMSCOMMANDSINK)this;
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

STDMETHODIMP CEMSCommandSink::SetType( BYTE cDataType )
{
	return EMS_UNSUPPORTED;
}

STDMETHODIMP CEMSCommandSink::GetType( BYTE __RPC_FAR *lpcDataType )
{
	if ( lpcDataType )
		*lpcDataType = m_cType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::SetCmdType( BYTE cCmdType )
{
	m_cCmdType = cCmdType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::GetCmdType( BYTE __RPC_FAR *lpcCmdType )
{
	if ( lpcCmdType )
		*lpcCmdType = m_cCmdType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::SetMaxLength( INT nMaxLength )
{
	m_nMaxLength = nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
	if ( lpnMaxLength )
		*lpnMaxLength = m_nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::SetStream( LPEMSPACKETSTREAM lpStream )
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

STDMETHODIMP CEMSCommandSink::GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream )
{
	if ( lplpStream )
		*lplpStream = m_lpStream;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSink::OnDataAvailable( DWORD dwSize, DWORD dwFlags )
{
	if ( m_hOnDataEvent )
		SetEvent( m_hOnDataEvent );

	return EMS_OK;
}

EMS_RESULT CEMSCommandSink::Read( BYTE *lpBuffer, ULONG ulMaxLength, ULONG *lpulRead )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpStream )
	{
		hr = m_lpStream->Read( lpBuffer, ulMaxLength, lpulRead );
	}

	return hr;
}
