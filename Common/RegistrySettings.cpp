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

#include "registrysettings.h"
#include "emsconfg.h"
#include "convutility.h"

#include <tchar.h>


const TCHAR* CEMSRegistrySettings::ms_cszComponents = TEXT("Components");
const TCHAR* CEMSRegistrySettings::ms_cszConfig = TEXT("Config");


CEMSRegistrySettings::CEMSRegistrySettings()
{
}

CEMSRegistrySettings::CEMSRegistrySettings( const CEMSRegistrySettings& x )
{
}

CEMSRegistrySettings::~CEMSRegistrySettings()
{
}

std::wstring 
CEMSRegistrySettings::GetConfigPath( const TCHAR* cszComponent )
{
	std::wstring owszRet;

	CEMSRegistryConfig reg;
	TCHAR szValue[ 256 ]="";

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( cszComponent );

	if ( reg.OpenKey( ) )
	{
		reg.QueryValue( ms_cszConfig, szValue, sizeof( szValue ) / sizeof( szValue[0] ) );

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

std::wstring 
CEMSRegistrySettings::GetStringValue( const TCHAR* cszComponent, const TCHAR* cszValueID )
{
	std::wstring owszRet;

	CEMSRegistryConfig reg;
	TCHAR szValue[ 256 ]="";

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( cszComponent );

	if ( reg.OpenKey( ) )
	{
		reg.QueryValue( cszValueID, szValue, sizeof( szValue ) / sizeof( szValue[0] ) );

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

std::string 
CEMSRegistrySettings::GetStringValueA( const TCHAR* cszComponent, const TCHAR* cszValueID )
{
	std::string oszRet;

	CEMSRegistryConfig reg;
	TCHAR szValue[ 256 ]="";

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( cszComponent );

	if ( reg.OpenKey( ) )
	{
		reg.QueryValue( cszValueID, szValue, sizeof( szValue ) / sizeof( szValue[0] ) );

		reg.CloseKey( );
	}

	if( szValue && 
		(_tcslen(szValue) > 0) )
	{
#ifdef UNICODE
		oszRet = CEMSConversionUtil::ConvertToString( szValue );
#else
		oszRet = szValue;
#endif
	}

	return oszRet;
}

void
CEMSRegistrySettings::SetStringValue( const TCHAR* cszComponent, const TCHAR* cszValueID, const TCHAR* cszValue )
{
	CEMSRegistryConfig reg;

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( cszComponent );

	if ( reg.OpenKey( ) )
	{
		reg.SetValue( cszValueID, cszValue );

		reg.CloseKey( );
	}
}

void
CEMSRegistrySettings::SetStringValueIfNotExist( const TCHAR* cszComponent, const TCHAR* cszValueID, const TCHAR* cszValue )
{
	CEMSRegistryConfig reg;

	reg.SetAppName( ms_cszComponents );
	reg.SetComponentName( cszComponent );

	if( !reg.OpenKey( ) )
	{
		reg.CreateKey();
		if ( reg.OpenKey( ) )
		{
			reg.SetValue( cszValueID, cszValue );

			reg.CloseKey( );
		}
	}
}