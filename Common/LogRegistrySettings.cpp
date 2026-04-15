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

#include "logregistrysettings.h"
#include "emsconfg.h"
#include "convutility.h"

#include <tchar.h>

const TCHAR* CEMSLogRegistrySettings::ms_cszComponents = TEXT("Components");
const TCHAR* CEMSLogRegistrySettings::ms_cszApacheLoggerSection = TEXT("ApacheLogger");
const TCHAR* CEMSLogRegistrySettings::ms_cszLoggerConfig = TEXT("Config");


CEMSLogRegistrySettings::CEMSLogRegistrySettings()
{
}

CEMSLogRegistrySettings::CEMSLogRegistrySettings( const CEMSLogRegistrySettings& x )
{
}

CEMSLogRegistrySettings::~CEMSLogRegistrySettings()
{
}

std::wstring 
CEMSLogRegistrySettings::GetPropertiesPath()
{
	std::wstring owszRet;

	CEMSRegistryConfig reg;
	TCHAR szValue[ 256 ]="";

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( ms_cszApacheLoggerSection );

	if ( reg.OpenKey( ) )
	{
		reg.QueryValue( ms_cszLoggerConfig, szValue, sizeof( szValue ) / sizeof( szValue[0] ) );

		reg.CloseKey( );
	}

	if( szValue && 
		(_tcslen(szValue) > 0) )
	{
#ifdef UNICODE
		owszRet = szValue;
#else
		owszRet = CEMSConversionUtil::ConvertToString( szValue );
#endif
	}

	return owszRet;
}