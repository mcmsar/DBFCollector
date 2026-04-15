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
#pragma warning(disable:4786)

#include "streamdatamanagercleaner.h"
#include "streamdatamanager.h"
#include "streamdatachannel.h"
#include "streamsink.h"
#include "streamsource.h"

const ULONG CEMSStreamDataMgrCleaner::ms_culDefaultCleanPeriod = 5000;
const ULONG CEMSStreamDataMgrCleaner::ms_culShutdownTime = 1000;

CEMSStreamDataMgrCleaner::CEMSStreamDataMgrCleaner() : m_ulCleanPeriod(ms_culDefaultCleanPeriod),
													m_ulShutdownPeriod( m_ulCleanPeriod + ms_culShutdownTime ),
													m_bRunFlag(false)
{
}

CEMSStreamDataMgrCleaner::~CEMSStreamDataMgrCleaner()
{
	Stop();
}

void 
CEMSStreamDataMgrCleaner::Stop()
{
	if( m_bRunFlag )
	{
		SignalStop();

		bool bShutdownOkay = wait( m_ulShutdownPeriod );

		if( !bShutdownOkay )
			stop();		// Force the thread to stop.

		m_bRunFlag = false;
	}
}

void 
CEMSStreamDataMgrCleaner::run()
{
	m_bRunFlag = true;

	while( !WaitForStop( m_ulCleanPeriod ) )
	{
		CEMSStreamDataManager::GetInstance()->Cleanup();
	}

	m_bRunFlag = false;
}