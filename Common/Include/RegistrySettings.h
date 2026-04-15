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

#ifndef __REGISTRY_SETTINGS_H__
#define __REGISTRY_SETTINGS_H__

#include <string>
#include "emstypes.h"

//! Used for accessing registry values.
class CEMSRegistrySettings
{
	public:
		CEMSRegistrySettings();
		CEMSRegistrySettings( const CEMSRegistrySettings& x );
		~CEMSRegistrySettings();

		//! Retrieve the fully qualified filename of the configuration file for the given component
		//! configured in the registry.
		static std::wstring GetConfigPath( const TCHAR* cszComponent );

		//! Retrieve the registry string value for the given component.
		static std::wstring GetStringValue( const TCHAR* cszComponent, const TCHAR* cszValueID );

		//! Retrieve the registry string value for the given component.
		static std::string GetStringValueA( const TCHAR* cszComponent, const TCHAR* cszValueID );

		//! Set a registry string value for the given component.
		static void SetStringValue( const TCHAR* cszComponent, const TCHAR* cszValueID, const TCHAR* cszValue );

		//! Set a registry string value for the given component if the registry setting does not exist,
		//! if the registry setting exists it will not change its value.
		static void SetStringValueIfNotExist( const TCHAR* cszComponent, const TCHAR* cszValueID, const TCHAR* cszValue );

	private:
		static const TCHAR* ms_cszComponents;
		static const TCHAR* ms_cszSection;
		static const TCHAR* ms_cszConfig;
};

#endif