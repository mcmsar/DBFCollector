/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#include "ccbootstrap.h"
#include "RegistrySettings.h"

std::string 
CCBootstrap::GetConfigServerHost()
{
	std::string ret = CEMSRegistrySettings::GetStringValueA( TEXT("ConfigClient"), TEXT("host") );

	return ret;
}

int 
CCBootstrap::GetConfigServerPort()
{
	int ret = 0;

	std::string value = CEMSRegistrySettings::GetStringValueA( TEXT("ConfigClient"), TEXT("port") );

	if( !value.empty() )
	{
		ret = atoi( value.c_str() );
	}

	return ret;
}

std::string 
CCBootstrap::GetThisSubsystemId()
{

	std::string ret = CEMSRegistrySettings::GetStringValueA( TEXT("ConfigClient"), TEXT("subsystem_id") );

	return ret;
}


bool
CCBootstrap::IsMEOSystem()
{
	bool bRet = false;

	std::string value = CEMSRegistrySettings::GetStringValueA( TEXT("ConfigClient"), TEXT("is_meo") );

	if( !value.empty() )
	{
		int iVal = atoi( value.c_str() );
		if( iVal )
		{
			bRet = true;
		}
	}

	return bRet;
}