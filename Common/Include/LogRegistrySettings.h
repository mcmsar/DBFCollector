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

	$Log$
********************************************************************/

#ifndef __LOG_REGISTRY_SETTINGS_H__
#define __LOG_REGISTRY_SETTINGS_H__

#include <string>
#include "emstypes.h"

//! Used for accessing registry values related to the Apache-derived
//! EMS Logger.
class CEMSLogRegistrySettings
{
	public:
		CEMSLogRegistrySettings();
		CEMSLogRegistrySettings( const CEMSLogRegistrySettings& x );
		~CEMSLogRegistrySettings();

		//! Retrieve the fully qualified filename of the log properties file configured in the
		//! registry.
		static std::wstring GetPropertiesPath();

	private:
		static const TCHAR* ms_cszComponents;
		static const TCHAR* ms_cszApacheLoggerSection;
		static const TCHAR* ms_cszLoggerConfig;
};

#endif