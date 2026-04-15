/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*							All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include "assert.h"
#include "process.h"

#pragma warning(disable:4284)

#include "emsclock.h"
#include "Watchdog.h"

static unsigned __stdcall _ProcessThreadRoutine( void *pThis );

CEMSWatchdog::CEMSWatchdog( const ULONG culCheckFrequencySeconds, const ULONG culMaxInactiveSeconds )
:	m_ulCheckFrequencySeconds(culCheckFrequencySeconds), m_ulMaxInactiveSeconds(culMaxInactiveSeconds),
	m_hThread(INVALID_HANDLE_VALUE), m_bRunThread(false), m_unThreadID(0), m_bMonitoring(false)
{
	assert( culCheckFrequencySeconds && culMaxInactiveSeconds );

	m_hEventStop = CreateEvent( NULL, FALSE, FALSE, NULL );
}

CEMSWatchdog::~CEMSWatchdog()
{
	_Cleanup();

	if ( INVALID_HANDLE_VALUE != m_hEventStop )
	{
		CloseHandle( m_hEventStop );
		m_hEventStop = INVALID_HANDLE_VALUE;
	}

	if ( INVALID_HANDLE_VALUE != m_hThread )
	{
		CloseHandle( m_hThread );
		m_hThread = INVALID_HANDLE_VALUE;
	}
}

void
CEMSWatchdog::_Cleanup()
{
	// Make sure that we have stopped
	Stop();
}


void
CEMSWatchdog::Start()
{
	// check if already started
	if ( INVALID_HANDLE_VALUE != m_hThread ) return;

	m_critialSection.Enter();
	try
	{
		if ( INVALID_HANDLE_VALUE == m_hThread ) 
		{
			SetActive();

			// Spin a separate thread that will wake up every 'n' seconds 
			// and do the required checks
			const unsigned cunStackSize = 0;
			m_hThread = (HANDLE)_beginthreadex( NULL, cunStackSize, 
								&_ProcessThreadRoutine, this, 0,	&m_unThreadID );

		}
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}
}

static unsigned __stdcall _ProcessThreadRoutine( void *pThis )
{
	if ( pThis )
		((CEMSWatchdog*)pThis)->ThreadRoutine();

	_endthreadex(0);

	return 0;
}

void 
CEMSWatchdog::ThreadRoutine()
{	
	m_bRunThread = true;
	ULONG	ulTimeoutMillisec = m_ulCheckFrequencySeconds * 1000;

	while ( m_bRunThread )
	{
		DWORD dwResult = WaitForMultipleObjects( 1, &m_hEventStop, FALSE, ulTimeoutMillisec );
		switch (dwResult)
		{	
			case WAIT_OBJECT_0: 	// signalled to quit
				m_bRunThread = false;
				break;
			default: // assume WAIT_TIMEOUT
				_DoChecks();
				break;
		}
	} // while
}

void
CEMSWatchdog::_EndThread()
{
	if ( INVALID_HANDLE_VALUE != m_hThread  )
	{
		DWORD dwExitStatus = STILL_ACTIVE;
		BOOL bOK = TRUE;

		SetEvent( m_hEventStop );

		while (bOK && (dwExitStatus == STILL_ACTIVE))
		{
			Sleep(3);

			bOK = GetExitCodeThread(m_hThread, &dwExitStatus);
		}

		CloseHandle( m_hThread );
		m_hThread = INVALID_HANDLE_VALUE;
	}
}

void 
CEMSWatchdog::Stop()
{
	if ( INVALID_HANDLE_VALUE == m_hThread  ) return;

	m_critialSection.Enter();
	try
	{
		if ( INVALID_HANDLE_VALUE != m_hThread  )
		{
			_EndThread();
		}
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}
}

void
CEMSWatchdog::SetActive()
{
	m_otimeLastActive.SetTime( CEMSSystemClock::GetTime() );
}

void 
CEMSWatchdog::_OnInactive()
{
	// Only do something if we haven't been told to stop in the meantime
	m_critialSection.Enter();
	try
	{
		if ( INVALID_HANDLE_VALUE != m_hThread )
		{
			// Ideally --- we should take a function pointer telling us what to do
			// for now we will simply commit suicide
			_exit(EXIT_FAILURE);
		}
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}
}


void 
CEMSWatchdog::StartMonitoring()
{
	m_critialSection.Enter();
	try
	{
		m_bMonitoring = true;
		SetActive();
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}
}

void 
CEMSWatchdog::StopMonitoring()
{
	m_critialSection.Enter();
	try
	{
		m_bMonitoring = false;
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}
}

void 
CEMSWatchdog::_DoChecks()
{
	bool bInactive = false;

	m_critialSection.Enter();
	try
	{
		if ( m_bMonitoring )
		{
			EMSTIME	tNow = CEMSSystemClock::GetTime();
			ULONG	ulInactive = (ULONG )(m_otimeLastActive.SecondsDifferent( tNow ));
			bInactive = ( ulInactive > m_ulMaxInactiveSeconds );
		}
		m_critialSection.Leave();
	}
	catch( ... )
	{
		m_critialSection.Leave();
		throw;
	}

	// Do the following outside the critical section
	if ( bInactive )
	{
		_OnInactive();
	}
}
