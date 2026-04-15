/********************************************************************
*   Module:         W32Async.cpp
*   Process ID:
*   S/W Platforms:
*   H/W Platforms:
*   Compiler:
*   Description:    Implementation of Win32 CEMSWin32Asynch Object
*                       
*
*   Usage:
*   Entry Point:
*   Input Files:
*   Output Files:
*   Comments:
*
*********************************************************************
*	   Copyright (c) 2000 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

    Rev Date            Auth    Changes
    === ====            ====    =======

    0.0 99/08/4     rvw start

********************************************************************/
//#include "stdafx.h"
#include <stdio.h>	// debugging
#include <process.h>
#include <tchar.h>
#include "w32async.h"

#include "DebugWin.h"
//	Mask for desired events to be handled in the thread routine
//
const DWORD cdwCommEventMask = EV_RXCHAR | EV_CTS | EV_DSR | EV_RLSD | EV_ERR;
const DWORD cdwReadBufSize = 4096L;
const DWORD cdwWriteBufSize = 2048L;

CEMSWin32Asynch::CEMSWin32Asynch()
{
	m_dwCommErrors = 0;
	m_hPort = INVALID_HANDLE_VALUE;
	m_hThread = INVALID_HANDLE_VALUE; 
	m_unThreadID = 0;
	m_bRunThread = FALSE;

	m_dwReadHead = m_dwReadTail = 0;
	m_dwWriteHead = m_dwWriteTail = 0;

	m_dwReadBufSize = cdwReadBufSize;
	m_dwWriteBufSize = cdwWriteBufSize;

	m_lpReadBuf = (LPBYTE) new BYTE[m_dwReadBufSize];
	m_lpWriteBuf = (LPBYTE) new BYTE[m_dwWriteBufSize];

	m_hMutexRead = CreateMutex( 0, FALSE , 0);
	m_hMutexWrite = CreateMutex( 0, FALSE , 0);
	m_hEventDataAvail = CreateEvent( 0, FALSE, FALSE, 0);
}

CEMSWin32Asynch::~CEMSWin32Asynch()
{
	if (IsOpen())
	{
		ClosePort();
	}

	if (m_lpReadBuf)
	{
		delete m_lpReadBuf;
		m_lpReadBuf = 0;
	}

	if (m_hMutexRead != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hMutexRead);
		m_hMutexRead = INVALID_HANDLE_VALUE;
	}

	if (m_lpWriteBuf)
	{
		delete m_lpWriteBuf;
		m_lpWriteBuf = 0;
	}

	if (m_hMutexWrite != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hMutexWrite);
		m_hMutexWrite = INVALID_HANDLE_VALUE;
	}

	if (m_hEventDataAvail != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hEventDataAvail);
		m_hEventDataAvail = INVALID_HANDLE_VALUE;
	}
}

EMS_RESULT CEMSWin32Asynch::_InitPort(DWORD dwBaudRate, UINT unDataBits, ASYNCPARITY parity,  ASYNCSTOPBITS stopBits)
{
	EMS_RESULT hr = EMS_OK;

	if (m_hPort != INVALID_HANDLE_VALUE)
	{
		COMMTIMEOUTS	timeouts;
		DCB				dcb;
		DWORD				dwModemStatus;

		GetCommModemStatus(m_hPort, &dwModemStatus);

		memset(&dcb, 0, sizeof(dcb));

		dcb.DCBlength = sizeof( DCB );

		GetCommState(m_hPort, &dcb);

		dcb.BaudRate = dwBaudRate;
		dcb.ByteSize = unDataBits;
		dcb.fBinary = TRUE;
		dcb.fParity = TRUE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fOutX = 0;
		dcb.fInX = 0;

		switch (parity)
		{
			case ASYNC_EvenParity:	dcb.Parity = EVENPARITY; break;
			case ASYNC_MarkParity:	dcb.Parity = MARKPARITY; break;
			case ASYNC_OddParity:	dcb.Parity = ODDPARITY; break;
			case ASYNC_SpaceParity:	dcb.Parity = SPACEPARITY; break;
			default:
			case ASYNC_NoParity:		dcb.Parity = NOPARITY; break;
		}

		switch (stopBits)
		{
			case ASYNC_One5StopBits: dcb.StopBits = ONE5STOPBITS; break;
			case ASYNC_TwoStopBits: dcb.StopBits = TWOSTOPBITS; break;
			default:
			case ASYNC_OneStopBit: dcb.StopBits = ONESTOPBIT; break;
		}

		SetCommState(m_hPort, &dcb);

		memset(&timeouts, 0, sizeof(timeouts));

		//  Set the timeouts
		timeouts.ReadIntervalTimeout = 1;
		timeouts.ReadTotalTimeoutConstant = 1;
		timeouts.ReadTotalTimeoutMultiplier = 1;
		timeouts.WriteTotalTimeoutConstant = 1000;
		timeouts.WriteTotalTimeoutMultiplier = 100;

		if (!SetCommTimeouts(m_hPort, &timeouts))
		{
							
		}

		SetCommMask( m_hPort, cdwCommEventMask);

		EscapeCommFunction( m_hPort, SETDTR);
	}
	else 
		hr = EMS_NOT_OPEN;

	return hr;
}

EMS_RESULT CEMSWin32Asynch::OpenPort(LPCTSTR lpcszParams)
{
	if (!IsOpen())
	{
		int nDataBits = 8;
		DWORD dwBaudRate = 9600;
		ASYNCPARITY parity = ASYNC_NoParity;
		ASYNCSTOPBITS stopBits = ASYNC_OneStopBit;
		TCHAR szPortName[256];

		if (lpcszParams && *lpcszParams)
		{
			TCHAR szParams[256];
			TCHAR *lpszToken = 0;
			int nToken = 0, nParity = 'N', nStopBits = 1;

			_tcsncpy(szParams, lpcszParams, sizeof(szParams)/sizeof(TCHAR));

			lpszToken = _tcschr( szParams, '?');

			if (lpszToken)
				*lpszToken = 0;

			lpszToken = _tcschr( szParams, '&');

			if (lpszToken)
				*lpszToken = 0;

			lpszToken = _tcstok(szParams, TEXT(":,"));

			while (lpszToken)
			{
				switch (nToken)
				{
					case 0: // PortName
						_tcscpy(szPortName, lpszToken);
						break;

					case 1: // BaudRate
						dwBaudRate = _ttol(lpszToken);
						break;

					case 2: // DataBits
						nDataBits = _ttoi(lpszToken);
						break;

					case 3: // Parity
						nParity = *lpszToken;
						switch (nParity)
						{
							default:
							case 'N':
							case 'n':
								parity = ASYNC_NoParity; 
								break;
							case 'E':
							case 'e':
								parity = ASYNC_EvenParity; 
								break;
							case 'O':
							case 'o':
								parity = ASYNC_OddParity; 
								break;
						}
						break;

					case 4: // StopBits
						nStopBits = atoi(lpszToken);

						switch (nStopBits)
						{
							default:
							case 1: 
								stopBits = ASYNC_OneStopBit;
								break;

							case 2:
								stopBits = ASYNC_TwoStopBits;
								break;
						}

						break;
				}
				nToken++;
	  	
				lpszToken = _tcstok(0, ":,");
			}

		}
		m_hPort = CreateFile( szPortName, (GENERIC_READ | GENERIC_WRITE),
									0, NULL, OPEN_EXISTING, 0, NULL);

		if (m_hPort != INVALID_HANDLE_VALUE)
		{
			_InitPort( dwBaudRate, nDataBits, parity, stopBits );

			CreateThread();
			SetOpen( TRUE );
		}

	}
	return (IsOpen()) ? EMS_OK : EMS_NO_COM_PORT;
}

EMS_RESULT CEMSWin32Asynch::ClosePort(void)
{
	if (IsOpen())
	{
		EndThread();

		CloseHandle(m_hPort);

		m_hPort = INVALID_HANDLE_VALUE;

		SetOpen( FALSE );
	}
	return EMS_OK;
}

EMS_RESULT CEMSWin32Asynch::FlushInput(void)
{
	if (IsOpen())
	{
		if (LockReadData())
		{
			m_dwReadHead = m_dwReadTail = 0;

			UnlockReadData();
		}
	}
	return EMS_OK;
}

EMS_RESULT CEMSWin32Asynch::WriteData(LPVOID lpData, INT nCount)
{
	EMS_RESULT hr = EMS_OK;

	if (IsOpen())
	{
		BOOL bOK = TRUE;
		LPBYTE lpBuffer = (LPBYTE)lpData;
		DWORD dwBytesWritten = 0;

		while ((nCount > 0) && bOK)
		{
			if (_LockWriteData())
			{
				bOK = _PushWriteBuffer( *lpBuffer );

				if (bOK)
					dwBytesWritten++;

				lpBuffer++;
				nCount--;

				_UnlockWriteData();
			}
			else
				bOK = FALSE;
		}

		if (dwBytesWritten)
		{
			SetCommMask( m_hPort, cdwCommEventMask | EV_TXEMPTY );
			_OutputBufferEmpty();
		}
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

EMS_RESULT CEMSWin32Asynch::ReadData(LPVOID lpData, INT nCount, DWORD dwTimeout, LPDWORD lpdwBytesRead)
{
	DWORD dwBytesRead = 0;
	EMS_RESULT hr = EMS_OK;

	if (IsOpen())
	{
		LPBYTE lpByteData = (LPBYTE)lpData;
		DWORD dwResult, dwInterval, dwStartTime = GetTickCount();
		BOOL bDone = FALSE;

//		SetEvent( m_hEventDataAvail );

		while (!bDone && (hr == EMS_OK))
		{
			dwResult = WaitForSingleObject( m_hEventDataAvail, dwTimeout );

			switch (dwResult)
			{	
				default:
					hr = EMS_FALSE;
					break;

				case WAIT_TIMEOUT:	// wait has expired
					hr = EMS_TIMEOUT;
					break;

				case WAIT_OBJECT_0:	// check for characters
					if (LockReadData())
					{
						if (m_dwCommErrors)
						{
							m_dwCommErrors = 0;
							hr = EMS_RECV_ERR;
						}
						else
						{
							DWORD dwCount = _GetReadBufferCount();

							if (dwCount > (DWORD)nCount)
							{
								dwCount = (DWORD)nCount;
								SetEvent(m_hEventDataAvail);  // signal - more
							}

							while (dwCount > 0)
							{
								_PopReadBuffer(lpByteData);

								lpByteData++;

								dwBytesRead++;

								dwCount--;
							}

							if (dwBytesRead < (DWORD)nCount)
							{
//								dwInterval = dwStartTime - GetTickCount();
								dwInterval = GetTickCount() - dwStartTime;
								
								if (dwInterval > dwTimeout)
									hr = EMS_TIMEOUT;
								else
									dwTimeout -= dwInterval; 
							}
							else
								bDone = TRUE;
						}
						UnlockReadData();
					}
					break;
			}
		}
	}
	else
		hr = EMS_NOT_OPEN;

	if (lpdwBytesRead)
		*lpdwBytesRead = dwBytesRead;

	return hr;
}


DWORD CEMSWin32Asynch::GetModemStatus(void)
{
	DWORD dwModemStatus = 0;

	if (IsOpen())
	{
		DWORD dwTempStatus = 0;

		GetCommModemStatus(m_hPort, &dwTempStatus);

		if ((dwTempStatus & MS_CTS_ON) == MS_CTS_ON)
			dwModemStatus |= ASYNC_ModemStatus_CTS;

		if ((dwTempStatus & MS_DSR_ON) == MS_DSR_ON)
			dwModemStatus |= ASYNC_ModemStatus_DSR;

		if ((dwTempStatus & MS_RING_ON) == MS_RING_ON)
			dwModemStatus |= ASYNC_ModemStatus_RING;

		if ((dwTempStatus & MS_RLSD_ON) == MS_RLSD_ON)
			dwModemStatus |= ASYNC_ModemStatus_CD;
	}

	return dwModemStatus;
}								

BOOL CEMSWin32Asynch::LockReadData(BOOL bWait)
{
	return (WaitForSingleObject(m_hMutexRead, (bWait) ? INFINITE : 1) == WAIT_OBJECT_0);
}

void CEMSWin32Asynch::UnlockReadData(void)
{
	ReleaseMutex( m_hMutexRead );
}

BOOL CEMSWin32Asynch::_LockWriteData(BOOL bWait)
{
	return (WaitForSingleObject(m_hMutexWrite, (bWait) ? INFINITE : 1) == WAIT_OBJECT_0);
}

void CEMSWin32Asynch::_UnlockWriteData(void)
{
	ReleaseMutex( m_hMutexWrite );
}

BOOL CEMSWin32Asynch::CreateThread(void)
{
	m_bRunThread = TRUE;

	m_hThread = (HANDLE)_beginthreadex( NULL, 0, &SerialThreadRoutine, this, 0,
		&m_unThreadID);

	return (m_hThread != INVALID_HANDLE_VALUE);
}

BOOL CEMSWin32Asynch::EndThread(void)
{
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		DWORD dwExitStatus = STILL_ACTIVE;
		BOOL bOK = TRUE;

		while (bOK && (dwExitStatus == STILL_ACTIVE))
		{
			// signal event to stop : thread should notice it and quit
			m_bRunThread = FALSE;

			SetCommMask(m_hPort, 0); // disable event notification

			Sleep(1);

			bOK = GetExitCodeThread(m_hThread, &dwExitStatus);
		}

		CloseHandle(m_hThread);

		m_hThread = INVALID_HANDLE_VALUE;
	}
	return 0;
}

static unsigned __stdcall SerialThreadRoutine( void *pThis )
{
	if (pThis)
		((CEMSWin32Asynch *)pThis)->ThreadRoutine();

	_endthreadex(0);

	return 0;
}

BOOL CEMSWin32Asynch::_PushReadBuffer(BYTE uByte)
{
	BOOL bOK = FALSE;
	DWORD dwIndex = m_dwReadTail;

	if (++m_dwReadTail >= m_dwReadBufSize)
		m_dwReadTail = 0;

	if (m_dwReadTail != m_dwReadHead)
	{
		m_lpReadBuf[dwIndex] = uByte;

		bOK = TRUE;
	}
	else
		m_dwReadTail = dwIndex;
	
	return bOK;
}

BOOL CEMSWin32Asynch::_PushWriteBuffer(BYTE uByte)
{
	BOOL bOK = FALSE;
	DWORD dwIndex = m_dwWriteTail;

	if (++m_dwWriteTail >= m_dwWriteBufSize)
		m_dwWriteTail = 0;

	if (m_dwWriteTail != m_dwWriteHead)
	{
		m_lpWriteBuf[dwIndex] = uByte;

		bOK = TRUE;
	}
	else
		m_dwWriteTail = dwIndex;
	
	return bOK;
}


BOOL CEMSWin32Asynch::_PopReadBuffer(LPBYTE lpByte)
{
	BOOL bOK = FALSE;

	if (m_dwReadHead != m_dwReadTail)
	{
		if (lpByte)
			*lpByte = m_lpReadBuf[m_dwReadHead];

		if (++m_dwReadHead >= m_dwReadBufSize)
			m_dwReadHead = 0;

		bOK = TRUE;
	}

	return bOK;
}

BOOL CEMSWin32Asynch::_PopWriteBuffer(LPBYTE lpByte)
{
	BOOL bOK = FALSE;

	if (m_dwWriteHead != m_dwWriteTail)
	{
		if (lpByte)
			*lpByte = m_lpWriteBuf[m_dwWriteHead];

		if (++m_dwWriteHead >= m_dwWriteBufSize)
			m_dwWriteHead = 0;

		bOK = TRUE;
	}

	return bOK;
}

DWORD CEMSWin32Asynch::_GetReadBufferCount(void)
{
	LONG lCount = (LONG)m_dwReadTail - (LONG)m_dwReadHead;

	if (lCount < 0)
		lCount += (LONG)m_dwReadBufSize;

	return (DWORD)lCount;
}

DWORD CEMSWin32Asynch::GetReadDataCount(void)
{
	DWORD dwCount = 0;

	if (LockReadData())
	{
		dwCount = _GetReadBufferCount();

		UnlockReadData();
	}

	return dwCount;
}

BOOL CEMSWin32Asynch::ModemStatusChanged(DWORD dwEvent)
{
	return TRUE;
}

EMS_RESULT CEMSWin32Asynch::SetBaudRate(DWORD dwBaudRate)
{
	EMS_RESULT result = EMS_OK;

	if (m_hPort != INVALID_HANDLE_VALUE)
	{
		DCB				dcb;

		memset(&dcb, 0, sizeof(dcb));

		dcb.DCBlength = sizeof( DCB );

		GetCommState(m_hPort, &dcb);

		dcb.BaudRate = dwBaudRate;

		if (SetCommState(m_hPort, &dcb) == 0)
			result = EMS_UNKNOWN_ERROR;
	}
	else
		result = EMS_NOT_OPEN;

	return result;
}

void CEMSWin32Asynch::_OutputBufferEmpty(void)
{
	if (m_hPort != INVALID_HANDLE_VALUE)
	{
		if (_LockWriteData())
		{
			BYTE cData = 0;

			if (_PopWriteBuffer( &cData ))
			{
				DWORD dwBytesWritten = 0;

				WriteFile( m_hPort, &cData, (DWORD)1, &dwBytesWritten, NULL );
			}
			else	// buffer is empty so reset the Event mask
				SetCommMask( m_hPort, cdwCommEventMask);

			_UnlockWriteData();
		}
	}
}

BOOL CEMSWin32Asynch::_ReadCommPort(void)
{
	COMSTAT comStat;
	DWORD dwErrors = 0;
	BYTE cData = 0;
	DWORD dwBytesRead = 0;

	if (ClearCommError( m_hPort, &dwErrors, &comStat))
	{
		DWORD dwLength = comStat.cbInQue;

		if (dwErrors)
			m_dwCommErrors = dwErrors;

		while (dwLength > 0)
		{
			BOOL bResult = ReadFile(m_hPort, &cData, (DWORD)1, &dwBytesRead, NULL);

			if ( bResult && ( dwBytesRead == 1) )
			{
				if (LockReadData())
				{
					_PushReadBuffer(cData);
					UnlockReadData();
				}
			}
			dwLength--;
		}

		if (comStat.cbInQue)
			SetEvent( m_hEventDataAvail );
	}
	
	return TRUE;
}

void CEMSWin32Asynch::ThreadRoutine(void)
{	
	while (m_bRunThread)
	{
		DWORD dwEventMask = 0;

		if (WaitCommEvent(m_hPort, &dwEventMask, 0))
		{
			if ((dwEventMask & EV_RXCHAR) == EV_RXCHAR)
				_ReadCommPort();

			if ((dwEventMask & EV_CTS) == EV_CTS)
				ModemStatusChanged(dwEventMask);

			if ((dwEventMask & EV_DSR) == EV_DSR)
				ModemStatusChanged(dwEventMask);

			if ((dwEventMask & EV_TXEMPTY) == EV_TXEMPTY)
				_OutputBufferEmpty();

			DoEventCallback( dwEventMask );
		}
		else
		{
			m_bRunThread = FALSE;
		}
	} // while
}
