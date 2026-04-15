/********************************************************************
*	Module:			pkstream.cpp
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
#include <windows.h>
#include "pkstream.h"

#include "logevent.h"
//#include "pipemsgs.h"		/// DEBUG
#include "debugwin.h"
CDebugWin debugWin;
static char szDebug[256];

const DWORD c_dwTimeout = 1000 * 10;	// ten seconds
const INT	c_nQueueSize		= 32;
const DWORD c_dwSleepMSecs	= 3;	
const DWORD c_dwRetryTimeout = 60000; // i.e. 60 seconds

CEMSPacketStream::CEMSPacketStream( BYTE cType, int nMaxLength, DWORD dwFlags)
{
	m_dwFlags = dwFlags;
	m_cType = cType;

	m_nMaxRecLen = nMaxLength;

	if ( nMaxLength && _VariableLength( ) )
		m_nMaxRecLen += sizeof( INT );

	m_nQueueSize = 0;
//	m_nQueueDefaultSize = c_nQueueSize;
	m_nQueueHead = m_nQueueTail = 0;
	m_lpQueue = 0 ;
	m_i64Sequence = 0;
	m_bNewData = FALSE;
	m_hEventNewData = 0;
	m_lRefCount = 1;
	m_dwTimeout = c_dwTimeout;
	m_hMutex = CreateMutex( 0, FALSE , 0);
}

CEMSPacketStream::~CEMSPacketStream()
{
	_ResetDataQueue();

	if ( m_hMutex != INVALID_HANDLE_VALUE)
	{
		CloseHandle( m_hMutex );

		m_hMutex = INVALID_HANDLE_VALUE;
	}

	if ( m_hEventNewData != INVALID_HANDLE_VALUE)
	{
		CloseHandle( m_hEventNewData );

		m_hEventNewData = INVALID_HANDLE_VALUE;
	}
}

EMS_RESULT CEMSPacketStream::Initialize( int nQueueSize /* = 32 */ )
{
	m_nQueueSize = nQueueSize;

	return _InitDataQueue();
}

STDMETHODIMP_(ULONG) CEMSPacketStream::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSPacketStream::Release()
{
	LONG lRef = InterlockedDecrement( &m_lRefCount );

	if ( lRef == 0 )
	{
		delete this;
	}

	return (ULONG)lRef;
}

STDMETHODIMP CEMSPacketStream::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT hr = E_NOINTERFACE;

	if ( lppObj )
	{
		LPUNKNOWN lpUnknown = 0;

		*lppObj = 0;

		if ( riid == IID_IUnknown || riid == IID_IEMSSeqStream )
		{
  		lpUnknown = (IUnknown *)(LPEMSSEQSTREAM)this;
		}
		else if ( riid == IID_IEMSPacketStream )
		{
  		lpUnknown = (IUnknown *)(LPEMSPACKETSTREAM)this;
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

STDMETHODIMP CEMSPacketStream::Read( BYTE __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbRead )
{
	EMS_RESULT hr = EMS_OK;

	if ( _Lock( TRUE, m_dwTimeout ) )
	{
		hr = _PopDataQueue( pv, cb, pcbRead );

		_Unlock();
	}
	else
		hr = EMS_TIMEOUT;

	return hr;
}

STDMETHODIMP CEMSPacketStream::Write(	const BYTE __RPC_FAR *pv,	ULONG cb, ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulWritten = 0;
	BOOL bCompleted = FALSE;
	int nRetries = 0;
	int nMaxRetries = (int)( c_dwRetryTimeout / c_dwSleepMSecs );

	while ( !bCompleted )
	{
		if ( _Lock( TRUE, m_dwTimeout ) )
		{
			hr = _PushDataQueue( pv, cb, &ulWritten );

			_Unlock();

			// DONT'T DO THIS HERE
			// Hard-coded strings must be moved to an PipeMSGS.MC if the following is ever uncommented
//			if ( ( hr == EMS_PIPE_OVERFLOW ) && ( m_dwFlags & EMS_PIPE_WAIT_WRITE )
//				&& ( ++nRetries < nMaxRetries ) )
//			{
//				CEMSLogEvent logEvent;
//				TCHAR szMsg[256];
//				LPCTSTR lpcszStrs[1] =  { (LPTSTR)szMsg };
//
//				wsprintf( szMsg, "PacketStream::Write Overflow {Type=%d, Retry=%d}", m_cType, nRetries );
//
//				logEvent.ReportEvent( EMSLogMsgAlarm, EMS_PIPE_ERROR, EMSLOGCAT_Pipeline, 
//											1, lpcszStrs );
//
//				Sleep( c_dwSleepMSecs ); 
//			}
//			else
				bCompleted = TRUE;
		}
		else
			hr = EMS_TIMEOUT;
	}


	if ( pcbWritten )
		*pcbWritten = ulWritten;

	return hr;
}

STDMETHODIMP CEMSPacketStream::SetType( BYTE cDataType )
{
	m_cType = cDataType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketStream::GetType( BYTE __RPC_FAR *lpcDataType )
{
	if ( lpcDataType )
		*lpcDataType = m_cType;

	return EMS_OK;
}

STDMETHODIMP CEMSPacketStream::SetMaxLength( INT nMaxLength )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_lpQueue )	// can't change if already initialized
	{
		m_nMaxRecLen = nMaxLength;

		if ( _VariableLength( ) )
			m_nMaxRecLen += sizeof( INT );
	}
	else
		hr = EMS_ALREADY_INITIALIZED;

	return hr;
}

STDMETHODIMP CEMSPacketStream::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
	if ( lpnMaxLength )
		*lpnMaxLength = _MaxDataLength();

	return EMS_OK;
}

STDMETHODIMP CEMSPacketStream::SetFlags( DWORD dwFlags )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_lpQueue )	// can't change if already initialized
	{
		BOOL bWasVariableLength = _VariableLength();
	
		m_dwFlags = dwFlags;

		// if NOW Variable Length - must fix max record length if already set
		//
		if ( _VariableLength() && !bWasVariableLength && m_nMaxRecLen )
			m_nMaxRecLen += sizeof(INT);
	}
	else
		hr = EMS_ALREADY_INITIALIZED;

	return hr;
}

BOOL CEMSPacketStream::_IsOverflow( void )
{
	BOOL bOverflow = FALSE;

	if ( _Lock( TRUE, m_dwTimeout ) )
	{
		int nCount = GetQueueCount();

		wsprintf(szDebug, "IsOverflow Count=%d, Size = %d", nCount, m_nQueueSize );
		debugWin.OutputMsg( szDebug );

		bOverflow = ( GetQueueCount() >= ( m_nQueueSize - 1) );
		
		_Unlock();
	}

	return bOverflow;
}


STDMETHODIMP CEMSPacketStream::GetFlags( DWORD __RPC_FAR *lpdwFlags )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpdwFlags )
	{
		if ( _IsOverflow() )
			m_dwFlags |= EMS_PIPE_IS_FULL;
		else
			m_dwFlags &= ~EMS_PIPE_IS_FULL;

		*lpdwFlags = m_dwFlags;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSPacketStream::_InitDataQueue( void )
{
	_ResetDataQueue();

//	int nCount = ( m_nQueueDefaultSize * m_nMaxRecLen );

	int nCount = ( m_nQueueSize * m_nMaxRecLen );

	m_lpQueue = new BYTE [ nCount ];

	if ( m_lpQueue )
	{
		memset( m_lpQueue, 0, nCount );

//		m_nQueueSize = m_nQueueDefaultSize;
	}

	return ( m_lpQueue ) ? EMS_OK : EMS_NO_MEMORY;
}

EMS_RESULT CEMSPacketStream::_ResetDataQueue( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpQueue )
	{
		delete m_lpQueue;
		m_lpQueue = 0;
	}
	m_nQueueHead = m_nQueueTail = 0;

//DELETE	m_nQueueSize = 0;

	return hr;
}

EMS_RESULT CEMSPacketStream::_PushDataQueue( BYTE const *lpBuffer, ULONG dwLength, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulWritten = 0;

	if ( lpBuffer && dwLength )
	{
		int nIndex = m_nQueueTail;

		if ( ++m_nQueueTail >= m_nQueueSize )
			m_nQueueTail = 0;

		if ( m_nQueueTail != m_nQueueHead )
		{
			LPBYTE lpDest = _GetDataPointer( nIndex );

			if ( lpDest )
			{
				if ( dwLength > (DWORD)_MaxDataLength() )
				{
					dwLength = (DWORD)_MaxDataLength();

					hr = EMS_PIPE_DATA_TRUNCATED;
				}

				memcpy( lpDest, lpBuffer, dwLength );

				_SetDataLength( nIndex, dwLength );

				ulWritten = dwLength;

				m_i64Sequence++;

				m_bNewData = TRUE;

				SetEvent( m_hEventNewData ); // signal that new data was received
			}
			else
			{
				hr = EMS_UNKNOWN_ERROR;
			}
		}
		else
		{
			m_nQueueTail = nIndex;

			hr = EMS_STREAM_OVERFLOW;
		}
	}

	if ( lpulCount )
		*lpulCount = ulWritten;

	return hr;
}

void CEMSPacketStream::_SetDataLength( int nIndex, int nLength )
{
	LPBYTE lpPointer = _GetDataPointer( nIndex );

	if ( lpPointer )
	{
		if ( _VariableLength( ) )
			*((int*)(lpPointer - sizeof(INT) )) = nLength;
	}
}

int CEMSPacketStream::_GetDataLength( int nIndex )
{
	LPBYTE lpPointer = _GetDataPointer( nIndex );
	int nLength = 0;

	if ( lpPointer )
	{
		if ( _VariableLength( ) )
			nLength = *((int*)(lpPointer - sizeof(INT) ));
		else
			nLength = m_nMaxRecLen;
	}

	return nLength;
}

LPBYTE CEMSPacketStream::_GetDataPointer( int nIndex )
{
	LPBYTE lpPointer = 0;

	if ( ( nIndex >= 0 ) && ( nIndex < m_nQueueSize ) )
	{
		lpPointer = m_lpQueue + ( m_nMaxRecLen * nIndex );

		if ( _VariableLength( ) )
			lpPointer += sizeof( INT );
	}

	return lpPointer;
}

EMS_RESULT CEMSPacketStream::_PopDataQueue( BYTE const *lpBuffer, ULONG dwLength, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_FALSE;
	ULONG ulBytesRead = 0;

	if ( lpBuffer && dwLength )
	{
		if (	m_nQueueHead != m_nQueueTail )
		{
			if ( lpBuffer )
			{
				LPBYTE lpFrom = _GetDataPointer( m_nQueueHead );

				if ( lpFrom )
				{
					if ( dwLength > (DWORD)_GetDataLength( m_nQueueHead ) )
						dwLength = (DWORD)_GetDataLength( m_nQueueHead );

					memcpy( (LPVOID)lpBuffer, lpFrom, dwLength );

					ulBytesRead = dwLength;

					hr = EMS_OK;
				}
			}
			if ( ++m_nQueueHead >= m_nQueueSize )
				m_nQueueHead = 0;
		}
	}

	if ( lpulCount )
		*lpulCount = ulBytesRead;

	return hr;
}

int CEMSPacketStream::GetQueueCount( void )
{
	int nCount = 0;

	nCount = m_nQueueTail - m_nQueueHead;

	if ( nCount < 0 )
		nCount += m_nQueueSize;

	return nCount;
}

BOOL CEMSPacketStream::_Lock( BOOL bWait, DWORD dwTimeout )
{
	BOOL bOK = FALSE;

	DWORD dwResult = WaitForSingleObject( m_hMutex, (bWait) ? 5000 : 1); 

	switch ( dwResult )
	{
		case WAIT_OBJECT_0:
			bOK = TRUE;
			break;

		case WAIT_TIMEOUT:
			{
				// debug !!!!!
				debugWin.OutputMsg(" <*>PacketStream::_Lock failed" ); 

				CEMSLogEvent	logEvent;
				logEvent.ReportEvent(
								EMSLogMsgTrace,
								EMS_PIPE_PKTSTREAM_LOCKFAILED,
								EMSLOGCAT_Pipeline, 
								0,
								NULL );

			}
			break;
	}
	return bOK;
//	return ( WaitForSingleObject( m_hMutex, (bWait) ? dwTimeout : 1) == WAIT_OBJECT_0 );
}

void CEMSPacketStream::_Unlock( void )
{
	ReleaseMutex( m_hMutex );
}

