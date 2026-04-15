/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __STREAM_DATA_MANAGER_CLEANER_H__
#define __STREAM_DATA_MANAGER_CLEANER_H__

#include "emsthread.h"
#include "aobjbase.h"

//! This class runs a thread that cleans up unused data channels
//! in the stream data manager's cache.
class CEMSStreamDataMgrCleaner : public CEMSThread, public CApiObjBase
{
	public:
		CEMSStreamDataMgrCleaner();
		virtual ~CEMSStreamDataMgrCleaner();

		//! Set the time between cleanups in milliseconds.
		void SetCleanPeriod( const ULONG culMilliSeconds ) 
		{ 
			m_ulCleanPeriod = culMilliSeconds; 
			m_ulShutdownPeriod = m_ulCleanPeriod + ms_culShutdownTime; 
		}

		//! Stop the thread.
		void Stop();

		//! Determine whether the thread is running.
		bool IsRunning() { return m_bRunFlag; }

	protected:
		void run();
		
	private:
		ULONG m_ulCleanPeriod;
		ULONG m_ulShutdownPeriod;
		bool m_bRunFlag;

	private:
		static const ULONG ms_culDefaultCleanPeriod;
		static const ULONG ms_culShutdownTime;
};

#endif