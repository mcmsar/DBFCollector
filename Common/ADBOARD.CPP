/********************************************************************
*	Module:			adboard.cpp
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
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>

#include "emsclock.h"
#include "adboard.h"
#include "41632dll.h"

#define nsp_UsesAll
#include "nsp.h"

#define DEBUG

#ifdef DEBUG
#include "debugWin.h"
static CDebugWin debugWin;
static char szDebug[256];
#endif // DEBUG

typedef struct _tagPIC416DATA
{
	HINSTANCE					hModule;
	WORD							wModel;
	WORD							wResolution;
	WORD							wChannels;
	WORD							wShortCycle;
	REALTYPE						rtSingleMaxRate;
	REALTYPE						rtMultiMaxRate;
	TFP_pci416_init 			lpfn_pci416_init;
	TFP_pci416_close			lpfn_pci416_close;
	TFP_pci416_dma_status	lpfn_pci416_dma_status;
	TFP_pci416_setup_dma		lpfn_pci416_setup_dma;
	TFP_pci416_reload_dma	lpfn_pci416_reload_dma;
	TFP_pci416_map_dmabuf	lpfn_pci416_map_dmabuf;
	TFP_pci416_getcaps		lpfn_pci416_getcaps;
	TFP_pci416_fifo_status	lpfn_pci416_fifo_status;
	TFP_pci416_clear_fifo	lpfn_pci416_clear_fifo;
	TFP_set_modes				lpfn_set_modes;
	TFP_get_adm_inf			lpfn_get_adm_inf;
	TFP_start_daq				lpfn_start_daq;
	TFP_start_daq_irq			lpfn_start_daq_irq;
	TFP_stop_daq				lpfn_stop_daq;
	TFP_pt_fifo_full			lpfn_pt_fifo_full;
	TFP_pci416_set_cmdreg	lpfn_pci416_set_cmdreg;
	TFP_pci416_close_dmabuf_hndl	lpfn_pci416_close_dmabuf_hndl;
} PIC416DATA, FAR *LPPIC416DATA;

const unsigned int cunStackSize = 0;
const clock_t	c_cycleTime = 900;	// milliseconds

const CEMSSystemClock c_sysClock;

CEMSAnalogToDigital::CEMSAnalogToDigital()
{
	m_dwBoard = 0;				// always the first board for now
#ifdef DEBUGWITHGPS
	m_lpGpsClock = 0;
	memset( m_gpstimeBuffer, 0, sizeof( m_gpstimeBuffer ) );
#endif // DEBUGWITHGPS

	memset( m_timeBuffer, 0, sizeof( m_timeBuffer ) );

	m_i64BlockCount = 0;
	m_i64Dropouts = 0;

	m_dwBufferSize = m_dwSampleSize = m_dwSampleRate = 0;
	m_bStarted = m_bPaused = m_bInitialized = FALSE;

	m_dwDMABufferIndex = 0;

	m_lpTransferBuffer = 0;

	m_hMutex = CreateMutex( 0, FALSE , 0);

	for ( int i = 0; i < EMS_DMA_BUFFER_COUNT; i++ )
	{
		m_lpDMABuffer[i] = 0;
	}

	m_hEventReady = CreateEvent( NULL, FALSE, FALSE, NULL );

	m_hThread = INVALID_HANDLE_VALUE;

	m_lpData = (LPVOID) new PIC416DATA;

	if ( m_lpData )
	{
		memset( m_lpData, 0, sizeof( PIC416DATA ) );
	}
}

CEMSAnalogToDigital::~CEMSAnalogToDigital()
{
	int i=0;

	Reset();

	if ( m_hMutex )
	{
		CloseHandle( m_hMutex );
		m_hMutex = INVALID_HANDLE_VALUE;
	}

	if ( m_lpData )
	{
		delete m_lpData;

		m_lpData = 0;
	}

	if ( m_hEventReady != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hEventReady );

		m_hEventReady = INVALID_HANDLE_VALUE;
	}
}

EMS_RESULT CEMSAnalogToDigital::_InitFunctionPointers( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpData )
	{
		LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;

		try
		{	
			lpData->hModule = LoadLibrary( TEXT("pci41632.dll") );

			if ( lpData->hModule != 0 )
			{
				if ( ( lpData->lpfn_pci416_close_dmabuf_hndl = 
					(TFP_pci416_close_dmabuf_hndl)GetProcAddress( lpData->hModule, TEXT("pci416_close_dmabuf_hndl" ) ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_set_cmdreg = (TFP_pci416_set_cmdreg)GetProcAddress( lpData->hModule,
															TEXT("pci416_set_cmdreg") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_init = (TFP_pci416_init)GetProcAddress( lpData->hModule,
															TEXT("pci416_init") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_getcaps = (TFP_pci416_getcaps)GetProcAddress( lpData->hModule,
															TEXT("pci416_getcaps") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_close = (TFP_pci416_close)GetProcAddress( lpData->hModule,
															TEXT("pci416_close") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_dma_status = (TFP_pci416_dma_status)GetProcAddress( lpData->hModule,
															TEXT("pci416_dma_status") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_setup_dma = (TFP_pci416_setup_dma)GetProcAddress( lpData->hModule,
															TEXT("pci416_setup_dma") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_reload_dma = (TFP_pci416_reload_dma)GetProcAddress( lpData->hModule,
															TEXT("pci416_reload_dma") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_clear_fifo = (TFP_pci416_clear_fifo)GetProcAddress( lpData->hModule,
															TEXT("pci416_clear_fifo") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_fifo_status = (TFP_pci416_fifo_status)GetProcAddress( lpData->hModule,
															TEXT("pci416_fifo_status") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pci416_map_dmabuf = (TFP_pci416_map_dmabuf)GetProcAddress( lpData->hModule,
															TEXT("pci416_map_dmabuf") ) ) == 0 ) 
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_set_modes = (TFP_set_modes)GetProcAddress( lpData->hModule,
															TEXT("set_modes") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_start_daq = (TFP_start_daq)GetProcAddress( lpData->hModule,
															TEXT("start_daq") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_start_daq_irq = (TFP_start_daq_irq)GetProcAddress( lpData->hModule,
															TEXT("start_daq_irq") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_stop_daq = (TFP_stop_daq)GetProcAddress( lpData->hModule,
															TEXT("stop_daq") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_pt_fifo_full = (TFP_pt_fifo_full)GetProcAddress( lpData->hModule,
															TEXT("pt_fifo_full") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;

				if ( ( lpData->lpfn_get_adm_inf = (TFP_get_adm_inf)GetProcAddress( lpData->hModule,
															TEXT("get_adm_inf") ) ) == 0 )
					throw EMS_ADERR_FN_POINTER;
			}
			else
				hr = EMS_ADERR_NO_DLL;
		}
		catch ( EMS_RESULT errCode )
		{
			hr = errCode;
		}
	}

	return hr;
}

BOOL CEMSAnalogToDigital::_StartThread( void )
{
	m_bRunThread = TRUE;

	m_hThread = (HANDLE)_beginthreadex( NULL, cunStackSize, 
							&_AnalogToDigitalThreadRoutine, this, 
							CREATE_SUSPENDED, &m_unThreadID );

	if ( m_hThread != INVALID_HANDLE_VALUE )
	{
		SetThreadPriority( m_hThread, THREAD_PRIORITY_ABOVE_NORMAL );

		ResumeThread( m_hThread );
	}

	return ( m_hThread != INVALID_HANDLE_VALUE );
}

BOOL CEMSAnalogToDigital::_EndThread(void)
{
	if ( m_hThread != INVALID_HANDLE_VALUE )
	{
		DWORD dwExitStatus = STILL_ACTIVE;
		BOOL bOK = TRUE;

		m_bRunThread = FALSE;

		while (bOK && (dwExitStatus == STILL_ACTIVE))
		{
			Sleep(3);

			bOK = GetExitCodeThread(m_hThread, &dwExitStatus);
		}

		CloseHandle(m_hThread);

		m_hThread = INVALID_HANDLE_VALUE;
	}

	return 0;
}

static unsigned __stdcall _AnalogToDigitalThreadRoutine( void *pThis )
{
	if ( pThis )
		((CEMSAnalogToDigital *)pThis)->_ThreadRoutine();

	_endthreadex(0);

	return 0;
}

void CEMSAnalogToDigital::_ThreadRoutine( void )
{	
	DWORD dwResult = 0, dwStatus = 0;
	DWORD dwBufSize = 0, dwDMABufHandle = 0;
	LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;
	clock_t tempTime = 0, elapsedTime=0;

#ifdef DEBUG
	debugWin.OutputMsg(" Thread Starting !!!!!");
#endif // DEBUG

	m_dwDMABufferIndex = 0;

#ifdef DEBUG
	wsprintf( szDebug, "+LOCKING-> (%d)", (int)m_dwDMABufferIndex );
	debugWin.OutputMsg( szDebug );
#endif // DEBUG

	_StartCollecting();

	m_i64BlockCount = m_i64Dropouts = 0;

	do 
	{
		dwResult = lpData->lpfn_pci416_dma_status( m_dwBoard, &dwStatus );

		if ( dwStatus == 1 )
		{
#ifdef DEBUG
			debugWin.OutputMsg(" DMA Buffer filled!!");
#endif // DEBUG

			BOOL bOverflow = ( lpData->lpfn_pt_fifo_full( m_dwBoard ) != 0 );

			// TC has been reached

#ifdef DEBUG
	wsprintf( szDebug, "-UNLOCKING-> (%d)", (int)m_dwDMABufferIndex );
	debugWin.OutputMsg( szDebug );
#endif // DEBUG

			m_i64BlockCount++;				// keep track of DMA buffers collected

			m_dwDMABufferIndex = !m_dwDMABufferIndex;

#ifdef DEBUG
	wsprintf( szDebug, "+LOCKING-> (%d)", (int)m_dwDMABufferIndex );
	debugWin.OutputMsg( szDebug );
#endif // DEBUG

			if ( bOverflow )
				lpData->lpfn_pci416_clear_fifo( m_dwBoard );

			dwResult = lpData->lpfn_pci416_reload_dma( m_dwBoard, m_dwDMABufferIndex, 
									&dwBufSize, &dwDMABufHandle );

			_SetBufferTime();

			tempTime = clock();

			m_lpDMABuffer[ m_dwDMABufferIndex ] = ( short * )dwDMABufHandle;

			if ( bOverflow )
			{
				m_i64Dropouts++;

#ifdef DEBUG
				wsprintf(szDebug, " Overflow (%lX) (%lX) %ld", dwResult, dwStatus, (ULONG)m_i64Dropouts );
				debugWin.OutputMsg( szDebug );
#endif // DEBUG

			}
			else
			{
				if ( m_lpTransferBuffer )
				{
					if ( LockBuffer() )
					{
						try
						{
							nspwbCopy( m_lpDMABuffer[ !m_dwDMABufferIndex ], 
												m_lpTransferBuffer, m_dwSampleSize );
						}

						catch ( ... )
						{
							; // do nothing
						}

						UnlockBuffer();

						SetEvent( m_hEventReady );	// signal that the buffer is ready
					}
				}
			}
			elapsedTime  = clock() - tempTime;

			if ( elapsedTime < c_cycleTime )
				Sleep( c_cycleTime - elapsedTime );
		}
	}
	while ( m_bRunThread );

	_StopCollecting();

#ifdef DEBUG
	debugWin.OutputMsg(" Thread Ending !!!!!");
#endif // DEBUG
}

EMS_RESULT CEMSAnalogToDigital::Init( DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate )
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;
	DWORD dwResult = 0;

	if ( !m_bInitialized )
	{
		m_dwBufferSize = dwBufferSize;
		m_dwSampleSize = dwSampleSize;
		m_dwSampleRate = dwSampleRate;

		hr = _InitFunctionPointers();

		if ( hr == EMS_OK )
		{
			LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;
			DWORD dwBoardCount = 0, dwCaps[ CAPS_SIZE ];

			dwResult = lpData->lpfn_pci416_init( &dwBoardCount );

			if ( ( dwResult == NOERROR ) && ( m_dwBoard < dwBoardCount ) )
			{
				DWORD dwCmdReg = 0;

				dwResult = lpData->lpfn_pci416_set_cmdreg( m_dwBoard,
					1, 0, &dwCmdReg );

			//	wsprintf( szDebug, "CmdReg(%lX)", dwCmdReg );
			//	debugWin.OutputMsg( szDebug );

				dwResult = lpData->lpfn_pci416_getcaps( m_dwBoard,
					sizeof( dwCaps ), dwCaps );

				if ( dwCaps[4] != 0 )			// IRQ must be disabled 
					hr = EMS_ADERR_IRQ_INUSE;
				else
				{
					WORD wClockSource = C_INTERNAL;
					WORD wTriggerSource = T_INTERNAL;
					WORD wChannel = 0;
					WORD wPreTrigger = 0;	// disabled
					WORD wScan = 0;			// single channel
					WORD wMarker = 1;		// marker bit set

					dwResult = lpData->lpfn_get_adm_inf( m_dwBoard, &(lpData->wModel),
						&(lpData->wResolution), &(lpData->wChannels), 
						&(lpData->wShortCycle), &(lpData->rtSingleMaxRate),
						&(lpData->rtMultiMaxRate) );

					dwResult = lpData->lpfn_set_modes( m_dwBoard, wClockSource, 
						m_dwSampleRate, m_dwSampleSize,	wTriggerSource, 
						wChannel, wPreTrigger, wScan, wMarker );

					if ( dwResult == NOERROR ) 
						hr = EMS_OK;
					else
						hr = EMS_UNKNOWN_ERROR;
				}

				if ( hr != EMS_OK )
					lpData->lpfn_pci416_close( m_dwBoard );
			}
			else
				hr = EMS_ADERR_NO_BOARD;
		}
		m_bInitialized = ( hr == EMS_OK );
	}
	else
		hr = EMS_ADERR_ALREADY_INIT;

	return hr;
}

EMSTIME CEMSAnalogToDigital::GetBufferTime( int nType )
{
#ifdef DEBUGWITHGPS
	if ( nType == 1 )
		return m_gpstimeBuffer[ !m_dwDMABufferIndex ];
	else
#endif // DEBUGWITHGPS
		return m_timeBuffer[ !m_dwDMABufferIndex ];
}

void CEMSAnalogToDigital::_SetBufferTime( void )
{
	EMS_RESULT hr = EMS_OK;

	m_timeBuffer[ m_dwDMABufferIndex ] = c_sysClock.GetTime();

#ifdef DEBUGWITHGPS
	if ( m_lpGpsClock )
	{	
		hr = m_lpGpsClock->ReadTime( &m_gpstimeBuffer[ m_dwDMABufferIndex ] );
	}
	else
		hr = EMS_FALSE;

	if ( hr != EMS_OK )
		m_gpstimeBuffer[ m_dwDMABufferIndex ] = m_timeBuffer[ m_dwDMABufferIndex ];
#endif // DEBUGWITHGPS
}


EMS_RESULT CEMSAnalogToDigital::Reset( void )
{
	EMS_RESULT hr = EMS_OK;

#ifdef DEBUGWITHGPS
	if ( m_lpGpsClock )
	{
		m_lpGpsClock->Release();
		m_lpGpsClock = 0;
	}
#endif // DEBUGWITHGPS

	Stop();

	if ( m_bInitialized && m_lpData )
	{
		LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;

		lpData->lpfn_pci416_close( m_dwBoard );

		if ( lpData->hModule )
		{
			FreeLibrary( lpData->hModule );

			lpData->hModule = 0;
		}
		m_bInitialized = FALSE;
	}

	return hr;
}

EMS_RESULT CEMSAnalogToDigital::Start( void )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( !m_bStarted && m_lpData )
	{
#ifdef DEBUG
//		debugWin.OutputMsg(" AtoD::Start ");
#endif // DEBUG

		if ( _StartThread() )
		{
			hr = EMS_OK;

			m_bStarted = ( hr == EMS_OK );
		}
	}

#ifdef DEBUG
		wsprintf( szDebug, "AtoD returns hr=%lX", hr );
		debugWin.OutputMsg( szDebug );
#endif // DEBUG

	return hr;
}

EMS_RESULT CEMSAnalogToDigital::_StartCollecting( void )
{
	EMS_RESULT hr = EMS_OK;

	LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;
	REALTYPE	rtTriggerRate = 0;
	WORD wTriggerMode = 2;		// continuous internal trigger
	DWORD dwResult = 0;
	DWORD dwMode = DMA_DOUBLE;
	DWORD dwDMABufHandle = 0;
	DWORD dwBufSize[2] = { m_dwBufferSize, m_dwBufferSize };

#ifdef DEBUGWITHGPS
	hr = CoCreateInstance( CLSID_EMSGpsClock, 0, CLSCTX_ALL, 
							IID_IEMSGpsClock, (LPVOID*)&m_lpGpsClock );

	if ( ( hr == EMS_OK ) && m_lpGpsClock )
		hr = m_lpGpsClock->Open( GPS_CLOCK_DEVICE_0 );
#endif // DEBUGWITHGPS
		
	m_dwDMABufferIndex = 0;

	m_i64BlockCount = 0;

	dwResult = lpData->lpfn_pci416_setup_dma( m_dwBoard, dwMode, dwBufSize, 
						&dwDMABufHandle );

#ifdef DEBUG
		if ( dwResult != 0 )
		{
			wsprintf(szDebug, "setup_dma result = %ld", dwResult );
			debugWin.OutputMsg( szDebug );
		}
#endif // DEBUG

	m_lpDMABuffer[ m_dwDMABufferIndex ] = ( short * )dwDMABufHandle;

#ifdef DEBUG
		debugWin.OutputMsg( "after m_lpDMABuffer assignment" );
#endif // DEBUG

	dwResult = lpData->lpfn_start_daq( m_dwBoard, wTriggerMode, &rtTriggerRate );

#ifdef DEBUG
//		if ( dwResult != 0 )
		{
			wsprintf(szDebug, "start_daq result = %ld", dwResult );
			debugWin.OutputMsg( szDebug );
		}
#endif // DEBUG

	_SetBufferTime();

	m_bStarted = ( dwResult == NOERROR );

	return hr;
}

EMS_RESULT CEMSAnalogToDigital::_StopCollecting( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_bStarted && m_lpData )
	{
		LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;
		DWORD dwResult = lpData->lpfn_stop_daq( m_dwBoard );

#ifdef DEBUGWITHGPS
	if ( m_lpGpsClock )
	{
		hr = m_lpGpsClock->Close();
		m_lpGpsClock->Release();
		m_lpGpsClock = 0;
	}
#endif // DEBUGWITHGPS

		m_bStarted = FALSE;
	}

	return hr;
}


EMS_RESULT CEMSAnalogToDigital::Stop( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_bStarted && m_lpData )
	{
		LPPIC416DATA lpData = ( LPPIC416DATA )m_lpData;
		DWORD dwResult = 0;

		_EndThread();

		dwResult = lpData->lpfn_pci416_close_dmabuf_hndl( m_dwBoard );

		m_bStarted = FALSE;
	}

	return hr;
}

EMS_RESULT CEMSAnalogToDigital::Pause( void )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	if ( !m_bPaused )
	{
		m_bPaused = TRUE;
	}

	return hr;
}

EMS_RESULT CEMSAnalogToDigital::Continue( void )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	if ( m_bPaused )
	{
		m_bPaused = FALSE;
	}

	return hr;
}

BOOL CEMSAnalogToDigital::LockBuffer( BOOL bWait )
{
	return ( WaitForSingleObject(m_hMutex, (bWait) ? INFINITE : 1) == WAIT_OBJECT_0);
}

void CEMSAnalogToDigital::UnlockBuffer( void )
{
	ReleaseMutex( m_hMutex );
}


