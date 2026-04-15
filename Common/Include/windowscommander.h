/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __WINDOWS_COMMANDER_H__
#define __WINDOWS_COMMANDER_H__

#include "emstypes.h"

class CEMSWindowsCommander
{
	public:
		CEMSWindowsCommander() {}
		~CEMSWindowsCommander() {}

		//! Graceful reboot, allowing s/w to shutdown.
		static void Reboot();

		//! Forced reboot.  Does not wait for s/w to shutdown.
		static void RebootForce();

		//! Shutdown the system to the point where it can be powered off safely.
		static void Shutdown();

	private:
		static void _ExitWindows( const DWORD cdwFlags );
};


#endif