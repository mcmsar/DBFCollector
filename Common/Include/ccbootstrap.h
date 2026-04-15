/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#ifndef __CC_BOOTSTRAP_H__
#define __CC_BOOTSTRAP_H__

#include <string>

//! Configuration Client Bootstrapper.  Provides boot-up config for Configuration Clients.
class CCBootstrap
{

	public:
		~CCBootstrap();

		static std::string GetConfigServerHost();
		static int GetConfigServerPort();
		static std::string GetThisSubsystemId();
		static bool IsMEOSystem();

	protected:
		CCBootstrap() {}

};

#endif