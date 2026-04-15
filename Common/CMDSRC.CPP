/********************************************************************
*	Module:			cmdsrc.cpp
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
#include "cmdsrc.h"

CEMSCommandSource::CEMSCommandSource( BYTE cCmdType, INT nMaxLength )
{
	m_lRefCount = 1;
	m_cType = EMS_PIPE_COMMAND_CHANNEL;
	m_cCmdType = cCmdType;
	m_nMaxLength = nMaxLength;
	m_lpStream = 0;
}

CEMSCommandSource::~CEMSCommandSource()
{
	if ( m_lpStream )
	{
		m_lpStream->Release();
		m_lpStream = 0;
	}
}

STDMETHODIMP_(ULONG) CEMSCommandSource::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSCommandSource::Release()
{
	LONG lRef = InterlockedDecrement( &m_lRefCount );

	if ( lRef == 0 )
	{
		delete this;
	}
	return (ULONG)lRef;
}

STDMETHODIMP CEMSCommandSource::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT hr = E_NOINTERFACE;

	if ( lppObj )
	{
		LPUNKNOWN lpUnknown = 0;

		*lppObj = 0;

		if ( riid == IID_IUnknown || riid == IID_IEMSDataSource )
		{
  		lpUnknown = (IUnknown *)(LPEMSDATASOURCE)this;
		}
		else if ( riid == IID_IEMSCommandSource )
		{
  		lpUnknown = (IUnknown *)(LPEMSCOMMANDSOURCE)this;
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

STDMETHODIMP CEMSCommandSource::Write( BYTE cTo, const BYTE __RPC_FAR *pv,	ULONG cb, ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpStream )
	{
		BYTE *lpTemp = new BYTE[ cb + 1];
		
		if ( lpTemp )
		{
			lpTemp[0] = cTo;

			memcpy( lpTemp + 1, pv, cb );

			hr = m_lpStream->Write( lpTemp, cb+1, pcbWritten );

			delete lpTemp;

			lpTemp = 0;
		}
	}

	return hr;
}

STDMETHODIMP CEMSCommandSource::SetType( BYTE cDataType )
{
	return EMS_UNSUPPORTED;
}

STDMETHODIMP CEMSCommandSource::GetType( BYTE __RPC_FAR *lpcDataType )
{
	if ( lpcDataType )
		*lpcDataType = m_cType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSource::SetCmdType( BYTE cCmdType )
{
	m_cCmdType = cCmdType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSource::GetCmdType( BYTE __RPC_FAR *lpcCmdType )
{
	if ( lpcCmdType )
		*lpcCmdType = m_cCmdType;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSource::SetMaxLength( INT nMaxLength )
{
	m_nMaxLength = nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSource::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
	if ( lpnMaxLength )
		*lpnMaxLength = m_nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSCommandSource::SetStream( LPEMSPACKETSTREAM lpStream )
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

STDMETHODIMP CEMSCommandSource::GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream )
{
	if ( lplpStream )
		*lplpStream = m_lpStream;

	return EMS_OK;
}

