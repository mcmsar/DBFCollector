/********************************************************************
*	Module:			adboard.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
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

	0.0	2001/04/05	rvw	start

********************************************************************/
#ifndef INC_ADBOARD
#define INC_ADBOARD

#include "emstypes.h"
#include "emserror.h"
#include "gpsclock.h"

#define EMS_DMA_BUFFER_COUNT	(2)

//#define DEBUGWITHGPS (1)

class CEMSAnalogToDigital
{
public:
	CEMSAnalogToDigital();
	virtual ~CEMSAnalogToDigital();

	EMS_RESULT Init( DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate );
	EMS_RESULT Reset( void );
	EMS_RESULT Start( void );
	EMS_RESULT Stop( void );
	EMS_RESULT Pause( void );
	EMS_RESULT Continue( void );

	inline void SetTransferBuffer( short *lpBuffer ) { m_lpTransferBuffer = lpBuffer; }
	BOOL LockBuffer( BOOL bWait = TRUE );
	void UnlockBuffer( void );

	inline HANDLE GetEventHandle( void ) { return m_hEventReady; }
	inline INT64 GetBlockCount( void ) { return m_i64BlockCount; }
	inline INT64 GetDropoutCount( void ) { return m_i64Dropouts; }
	inline void SetDropoutCount( INT64 i64Count ) { m_i64Dropouts = i64Count; }
	inline void ResetDropoutCount( void ) { SetDropoutCount( 0 ); }

	EMSTIME GetBufferTime( int nType );

private: // methods
	EMS_RESULT _InitFunctionPointers( void );
	EMS_RESULT _StartCollecting( void );
	EMS_RESULT _StopCollecting( void );
	BOOL _StartThread( void );
	BOOL _EndThread( void );
	void _ThreadRoutine( void );
	void _SetBufferTime( void );

	friend  unsigned __stdcall _AnalogToDigitalThreadRoutine( void *pThis );

private:	// data
	BOOL		m_bInitialized;
	BOOL		m_bStarted;
	BOOL		m_bPaused;
	LPVOID 	m_lpData;
	HANDLE	m_hEventReady;
	HANDLE	m_hThread;
	unsigned m_unThreadID;
	BOOL		m_bRunThread;
	DWORD		m_dwBoard;
	DWORD 	m_dwBufferSize; 
	DWORD 	m_dwSampleSize; 
	DWORD 	m_dwSampleRate;
	DWORD		m_dwDMABufferIndex;
	HANDLE	m_hMutex;
	short		*m_lpDMABuffer[ EMS_DMA_BUFFER_COUNT ];
	short		*m_lpTransferBuffer;
	INT64		m_i64BlockCount;
	INT64		m_i64Dropouts;
	EMSTIME	m_timeBuffer[ EMS_DMA_BUFFER_COUNT ];

#ifdef DEBUGWITHGPS
	EMSTIME	m_gpstimeBuffer[ EMS_DMA_BUFFER_COUNT ];
	LPEMSGPSCLOCK 			m_lpGpsClock;	
#endif // DEBUGWITHGPS
};

#endif // INC_ADBOARD

