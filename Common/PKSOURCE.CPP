/********************************************************************
*	Module:			pksource.cpp
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
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/03/22		rvw	start

********************************************************************/
#include "pksource.h"
#include "logevent.h"
#include "pipemsgs.h"
#include "LogMsgParam.h"

const DWORD c_dwSleepMSecs	= 10;	
const DWORD c_dwRetryTimeout = 100; // ie. one second MAX

CEMSPacketSource::CEMSPacketSource( BYTE cType, INT nMaxLength )
{
	m_lRefCount = 1;
	m_cType = cType;
	m_nMaxLength = nMaxLength;
	m_lpStream = 0;
}

CEMSPacketSource::~CEMSPacketSource()
{
	if ( m_lpStream )
	{
		m_lpStream->Release();
		m_lpStream = 0;
	}
}

STDMETHODIMP_(ULONG) CEMSPacketSource::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSPacketSource::Release()
{
	LONG lRef = InterlockedDecrement( &m_lRefCount );

	if ( lRef == 0 )
	{
		delete this;
	}
	return (ULONG)lRef;
}

STDMETHODIMP CEMSPacketSource::QueryInterface(REFIID riid, LPVOID *lppObj)
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

STDMETHODIMP CEMSPacketSource::Write(	const BYTE __RPC_FAR *pv,	ULONG cb, ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpStream )
	{
		BOOL bDone = FALSE;
		int nRetries = 0;
		int nMaxRetries = (int)( c_dwRetryTimeout / c_dwSleepMSecs );
		DWORD dwFlags = EMS_PIPE_WAIT_WRITE;	// DEBUG!!!

		while ( !bDone )
		{
			hr = m_lpStream->Write( pv, cb, pcbWritten );

			switch ( hr )
			{
				case EMS_PIPE_OVERFLOW:
					if ( ( dwFlags & EMS_PIPE_WAIT_WRITE ) && ( nRetries++ < nMaxRetries ) )
					{
//						bDone = TRUE;
						Sleep( c_dwSleepMSecs ); 
					}
					else
						bDone = TRUE;
					break;

				default:
					bDone = TRUE;
					break;
			}
		}
		// Report if we needed to do any retries
		if ( nRetries > 0 )
		{
			CEMSLogMsgParam	param(2);
			CEMSLogEvent	logEvent;

			param.Add( m_cType );
			param.Add( nRetries );

			logEvent.ReportEventW(
				EMSLogMsgInfo,
				EMS_PIPE_TRACE_WRITE_OVERFLOW, 
				EMSLOGCAT_Pipeline, 
				param.GetCount(),
				param.GetParams() );
		}
	}
	else
		hr = EMS_PIPE_NO_STREAM;

	return hr;
}

STDMETHODIMP CEMSPacketSource::SetType( BYTE cDataType )
{
	m_cType = cDataType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSource::GetType( BYTE __RPC_FAR *lpcDataType )
{
	if ( lpcDataType )
		*lpcDataType = m_cType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSource::SetMaxLength( INT nMaxLength )
{
	m_nMaxLength = nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSource::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
	if ( lpnMaxLength )
		*lpnMaxLength = m_nMaxLength;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketSource::SetStream( LPEMSPACKETSTREAM lpStream )
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

STDMETHODIMP CEMSPacketSource::GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream )
{
	if ( lplpStream )
		*lplpStream = m_lpStream;

	return EMS_OK;
}

