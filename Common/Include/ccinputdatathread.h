/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
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

#ifndef __CC_INPUTDATA_THREAD_H__
#define __CC_INPUTDATA_THREAD_H__

#include "emsthread.h"
#include "emscc.h"
#include "aobjbase.h"

//! Send data asynchronously to the CC service.
class CEMSCCInputDataThread : public CEMSThread, public CApiObjBase
{
	public:
		CEMSCCInputDataThread();
		virtual ~CEMSCCInputDataThread();

		void Run( const EMSCCSPEC& crstrCMD, const ULONG culDelay = 0 );

		EMS_RESULT GetLastResultCode() const { return m_hrLast; }

	private:
		void run();

	private:
		EMSCCSPEC m_strCMD;
		EMS_RESULT m_hrLast;
		ULONG m_ulDelay;
};

#endif