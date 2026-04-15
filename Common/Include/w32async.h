/********************************************************************
*   Module:         W32Async.h
*   Process ID:
*   S/W Platforms:
*   H/W Platforms:
*   Compiler:
*   Description:    Definitions for Win32 CEMSWin32Asynch Object
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
#ifndef INC_W32ASYNC
#define INC_W32ASYNC

//#include "stdafx.h"
#include <windows.h>
#include "asynch.h"
#include "emserror.h"

class CEMSWin32Asynch : public CEMSAsynch
{
public: 
	CEMSWin32Asynch();	
	virtual ~CEMSWin32Asynch();	

	virtual EMS_RESULT OpenPort(LPCTSTR lpcszPortName);
	virtual EMS_RESULT SetBaudRate(DWORD dwBaudRate);
	virtual EMS_RESULT ClosePort(void);
	virtual EMS_RESULT FlushInput(void);
	virtual EMS_RESULT ReadData(LPVOID lpData, INT nCount, DWORD dwTimeout=0xFFFFFFFF, LPDWORD lpdwBytesRead=0);
	virtual EMS_RESULT WriteData(LPVOID lpData, INT nCount);
	virtual DWORD GetModemStatus(void);
	virtual DWORD GetReadDataCount(void);

private: // methods
	friend  unsigned __stdcall SerialThreadRoutine( void* pConnection );

	EMS_RESULT _InitPort(DWORD dwBaudRate, UINT unDataBits, ASYNCPARITY parity,  ASYNCSTOPBITS stopBits);
	BOOL LockReadData(BOOL bWait = TRUE);
	void UnlockReadData(void);
	BOOL _LockWriteData(BOOL bWait = TRUE);
	void  _UnlockWriteData(void);
	BOOL CreateThread(void);
	BOOL EndThread(void);
	void ThreadRoutine(void);
	BOOL _PushReadBuffer(BYTE uByte);
	BOOL _PopReadBuffer(LPBYTE lpByte);
	BOOL _PushWriteBuffer(BYTE uByte);
	BOOL _PopWriteBuffer(LPBYTE lpByte);
	DWORD _GetReadBufferCount(void);
	DWORD _GetWriteBufferCount(void);
	void _OutputBufferEmpty(void);

	BOOL _ReadCommPort(void);
	BOOL ModemStatusChanged(DWORD dwEvent);

private:	// data
	LPBYTE	m_lpReadBuf;
	DWORD		m_dwReadBufSize;
	DWORD		m_dwReadHead;
	DWORD		m_dwReadTail;
	LPBYTE	m_lpWriteBuf;
	DWORD		m_dwWriteBufSize;
	DWORD		m_dwWriteHead;
	DWORD		m_dwWriteTail;
	HANDLE	m_hPort;
	HANDLE	m_hMutexRead;
	HANDLE	m_hMutexWrite;
	HANDLE 	m_hThread;
	unsigned m_unThreadID;
	BOOL		m_bRunThread;
	DWORD		m_dwCommErrors;
	HANDLE	m_hEventDataAvail;
};

#endif // INC_W32ASYNC
