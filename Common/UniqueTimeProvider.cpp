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

#include "uniquetimeprovider.h"
#include "emsclock.h"

#include <stdio.h>

// The one and only instance.
CEMSUniqueTimeProvider CEMSUniqueTimeProvider::ms_oTP;

CEMSUniqueTimeProvider::~CEMSUniqueTimeProvider()
{
}

CEMSUniqueTimeProvider::CEMSUniqueTimeProvider()
{
	m_timeLast.intTime = 0;
}

CEMSUniqueTimeProvider* 
CEMSUniqueTimeProvider::GetInstance()
{
	return &ms_oTP;
}

EMSTIME 
CEMSUniqueTimeProvider::GetTime()
{
	EMSTIME timeRet;

	try
	{
		m_ocsTP.Enter();

		EMSTIME timeCurrentClock = CEMSSystemClock::GetTime();

		if( 0 == m_timeLast.intTime )
		{
			timeRet = m_timeLast = timeCurrentClock;
		}
		else
		{
			if( timeCurrentClock.intTime <= m_timeLast.intTime )
			{
				m_timeLast.intTime++;
			}
			else
				m_timeLast = timeCurrentClock;

			timeRet = m_timeLast;

		}

		m_ocsTP.Leave();
	}
	catch( ... )
	{
		m_ocsTP.Leave();

		throw;
	}

	return timeRet;
}

