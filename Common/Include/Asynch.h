/********************************************************************
*   Module:         Asynch.h
*   Process ID:
*   S/W Platforms:
*   H/W Platforms:
*   Compiler:
*   Description:    Definitions for CEMSAsynch Object
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
*
********************************************************************/

/*******************************************************************

  Revision Record

    Rev Date            Auth    Changes
    === ====            ====    =======

    0.0 99/08/4     rvw start

********************************************************************/
#ifndef INC_ASYNCH
#define INC_ASYNCH

#include "emstypes.h"
#include "emserror.h"

#define ASYNC_ModemStatus_CD		(0x1)
#define ASYNC_ModemStatus_RING	(0x2)
#define ASYNC_ModemStatus_DSR	(0x4)
#define ASYNC_ModemStatus_CTS	(0x8)

typedef enum enumASYNCPARITY
{
	ASYNC_NoParity	= 0,
	ASYNC_OddParity = 1,
	ASYNC_EvenParity = 2,
	ASYNC_MarkParity = 3,
	ASYNC_SpaceParity = 4
} ASYNCPARITY;

typedef enum enumASYNCSTOPBITS
{
	ASYNC_OneStopBit = 0,
	ASYNC_One5StopBits = 1,
	ASYNC_TwoStopBits = 2
} ASYNCSTOPBITS;

typedef BOOL (CALLBACK *LPFNASYNCHEVENT)(DWORD dwEvent, LPVOID lpContext);

class CEMSAsynch
{
public: 
	CEMSAsynch();	
	virtual ~CEMSAsynch();	

	virtual EMS_RESULT OpenPort(LPCTSTR lpcszPortName) = 0;
	virtual EMS_RESULT SetBaudRate(DWORD dwBaudRate) = 0;
	virtual EMS_RESULT ClosePort(void) = 0;
	virtual EMS_RESULT FlushInput(void) = 0;
	virtual EMS_RESULT ReadData(LPVOID lpData, INT nCount, DWORD dwTimeout=0xFFFFFFFF, LPDWORD lpdwBytesRead=0) = 0;
	virtual EMS_RESULT WriteData(LPVOID lpData, INT nCount) = 0;
	virtual DWORD GetModemStatus(void) = 0;
	virtual DWORD GetReadDataCount(void) = 0;

	EMS_RESULT ReadByte(LPBYTE lpcData, DWORD dwTimeout=0xFFFFFFFF);
	EMS_RESULT WriteByte(BYTE cData);

	void SetEventCallback(LPFNASYNCHEVENT lpfnCallback, LPVOID lpContext=0);

	inline BOOL IsOpen(void) { return m_bOpen; }
	inline BOOL IsInitialized(void) { return m_bInitialized; }

protected: // methods
	inline void SetOpen(BOOL bOpen) { m_bOpen = bOpen; }
	inline void SetInitialized(BOOL bInitialized) { m_bInitialized = bInitialized; }

	BOOL DoEventCallback( DWORD dwEvent);

private:	// data
	LPFNASYNCHEVENT m_lpfnCallback;
	LPVOID	m_lpContextCallback;
	BOOL	m_bInitialized;
	BOOL	m_bOpen;
};

#endif // INC_ASYNCH
