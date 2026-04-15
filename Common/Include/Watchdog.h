/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*							All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef _WATCHDOG_H
#define _WATCHDOG_H

#include "criticalSection.h" // CEMSCriticalSection
#include "emstime.h"
 
//! @class CEMSWatchdog
//! This class is responsible for monitoring whether 
//! a process is active.  If not, it will exit
class CEMSWatchdog
{
public:
	CEMSWatchdog( const ULONG culCheckFrequencySeconds, const ULONG culMaxInactiveSeconds );
	virtual ~CEMSWatchdog();

	//! @fn void Start()
	//! Start thread
	void Start();
	//! @fn void Stop()
	//! Stop thread
	void Stop();

	//! @fn void StartMonitoring()
	//! Start monitoring
	void StartMonitoring();

	//! @fn void StopMonitoring()
	//! Stop monitoring - thread stays alive
	void StopMonitoring();

	//! @fn void SetActive()
	//! Called to indicate that process is still alive
	void SetActive();

	//! @fn void ThreadRoutine()
	//! Called when the checking thread is launched
	//! Do not call directly
	void ThreadRoutine();

protected:

private:
	// Check whether active
	void _DoChecks();
	void _OnInactive();
	void _Cleanup();
	void _EndThread();

	// How often should we check ... and what is the maximum amount of time
	// that the software can be inactive!
	ULONG		m_ulCheckFrequencySeconds;
	ULONG		m_ulMaxInactiveSeconds;
	bool		m_bMonitoring;

	// To manage the thread
	bool						m_bRunThread;
	HANDLE						m_hThread;
	unsigned					m_unThreadID;
	HANDLE						m_hEventStop;

	// When were we last poked ...
	CEMSTime					m_otimeLastActive;

	// To ensure that not started more than once
	CEMSCriticalSection			m_critialSection;
};

#endif // _WATCHDOG_H
