/********************************************************************
*	Module:			EMSConfg.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSRegistryConfig class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/06/22	rvw	start

********************************************************************/
#include <windows.h>
#include <io.h>
#include "emsconfg.h"
#include "emsrgkey.h"
#include <tchar.h>
#include <stdlib.h>

const TCHAR c_szEMSSoftwareKeyFmt[] = TEXT("Software\\EMS Technologies\\%s\\%s");
const TCHAR c_szEMSSoftwareComponentKeyFmt[] = TEXT("Software\\EMS Technologies\\Components\\%s");

CEMSRegistryConfig::CEMSRegistryConfig( )
{
	m_lpszApp = 0;
	m_lpszComponent = 0;
}

CEMSRegistryConfig::~CEMSRegistryConfig()
{
	if ( m_lpszApp )
	{
		delete [ ] m_lpszApp;
		m_lpszApp = 0;
	}
	if ( m_lpszComponent )
	{
		delete [ ] m_lpszComponent;
		m_lpszComponent = 0;
	}
}

void CEMSRegistryConfig::SetComponentName( LPCTSTR lpcszComponent )
{
	_SetName( &m_lpszComponent, lpcszComponent );
}

void CEMSRegistryConfig::SetAppName( LPCTSTR lpcszApp )
{
	_SetName( &m_lpszApp, lpcszApp );
}

BOOL CEMSRegistryConfig::_SetName( LPTSTR *lplpszName, LPCTSTR lpcszValue )
{
	if ( lplpszName )
	{
		if ( *lplpszName )
		{
			delete [ ] *lplpszName;

			*lplpszName = 0;
		}

		if ( lpcszValue && *lpcszValue )
		{
			*lplpszName = new TCHAR[ lstrlen( lpcszValue ) + 1 ];

			if ( *lplpszName )
				lstrcpy( *lplpszName, lpcszValue );
		}
	}
	return ( *lplpszName != 0 );
}

BOOL CEMSRegistryConfig::OpenKey( void )
{
	BOOL bOK = FALSE;

	if ( m_lpszComponent )
	{
		TCHAR szTemp[256];

		if ( m_lpszApp )
			wsprintf( szTemp, c_szEMSSoftwareKeyFmt, m_lpszApp, m_lpszComponent );
		else 
			wsprintf( szTemp, c_szEMSSoftwareComponentKeyFmt, m_lpszComponent );

		bOK = m_key.OpenKey( HKEY_LOCAL_MACHINE, szTemp );
	}

	return bOK;
}

BOOL CEMSRegistryConfig::CreateKey( void )
{
	BOOL bOK = FALSE;

	if ( m_lpszComponent )
	{
		TCHAR szTemp[256];

		if ( m_lpszApp )
			wsprintf( szTemp, c_szEMSSoftwareKeyFmt, m_lpszApp, m_lpszComponent );
		else 
			wsprintf( szTemp, c_szEMSSoftwareComponentKeyFmt, m_lpszComponent );

 		bOK = m_key.CreateKey( HKEY_LOCAL_MACHINE, szTemp );
	}

	return bOK;
}

void CEMSRegistryConfig::CloseKey( void )
{
	m_key.CloseKey( );
}


BOOL CEMSRegistryConfig::QueryValue( LPCTSTR lpcszValueName, LPTSTR lpszValue, int nMaxLength )
{
	return m_key.QueryValue( lpcszValueName, lpszValue, nMaxLength );
}

BOOL CEMSRegistryConfig::QueryValue( LPCTSTR lpcszValueName, DWORD *pdwValue )
{
	return m_key.QueryValue( lpcszValueName, pdwValue );
}

int CEMSRegistryConfig::SetValue( LPCTSTR lpcszValueName, LPCTSTR lpcszValue )
{
	return m_key.SetValue( lpcszValueName, lpcszValue );
}

int CEMSRegistryConfig::SetValue( LPCTSTR lpcszValueName, DWORD dwValue )
{
	return m_key.SetValue( lpcszValueName, dwValue );
}

BOOL CEMSRegistryConfig::DeleteKey( void )
{
	BOOL bOK = FALSE;

	if ( m_lpszComponent )
	{
		TCHAR szTemp[256];

		if ( m_lpszApp )
			wsprintf( szTemp, c_szEMSSoftwareKeyFmt, m_lpszApp, m_lpszComponent );
		else 
			wsprintf( szTemp, c_szEMSSoftwareComponentKeyFmt, m_lpszComponent );

 		bOK = m_key.DeleteKey( HKEY_LOCAL_MACHINE, szTemp );
	}
	return bOK;
}

EMS_RESULT CEMSRegistryConfig::FindFile( LPTSTR lpszPath, int nMaxLen, HANDLE hModule, LPCTSTR lpcszFilename )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( lpcszFilename && *lpcszFilename && lpszPath && nMaxLen )
	{
		TCHAR szPath[ _MAX_PATH ], szFilespec[ _MAX_PATH ];

		*lpszPath = szPath[0] = 0;

		if ( hModule )
		{
			TCHAR szModulePathName[ _MAX_PATH ];
			TCHAR szDrive[_MAX_DRIVE];
			TCHAR szDir[_MAX_DIR];
			TCHAR szFname[_MAX_FNAME];
			TCHAR szExt[_MAX_EXT];

			if ( GetModuleFileName( (HMODULE)hModule, szModulePathName,
					sizeof( szModulePathName ) / sizeof( TCHAR )) > 0 )
			{
				// first look in this directory
				_tsplitpath( szModulePathName, szDrive, szDir, szFname, szExt );

				wsprintf( szPath, TEXT("%s%s"), szDrive, szDir );

				wsprintf( szFilespec, TEXT("%s%s"), szPath, lpcszFilename );

				// it that fails look in "..\config" directory
				if ( _taccess( szFilespec, 0 ) != 0 )
				{
					int nStrLen = lstrlen( szPath );

					if ( nStrLen && ( ( szPath[ nStrLen-1 ] == '\\' ) ||
						( szPath[ nStrLen-1 ] == '/' ) ) )
						szPath[ nStrLen-1 ] = 0;

					_tsplitpath( szPath, szDrive, szDir, szFname, szExt );

					wsprintf( szPath, TEXT("%s%sConfig\\"), szDrive, szDir );

					wsprintf( szFilespec, TEXT("%s%s"), szPath, lpcszFilename );

					if ( _taccess( szFilespec, 0 ) != 0 )
						szPath[0] = 0;
				}

				if ( szPath[0] ) 
				{
					lstrcpyn( lpszPath, szPath, nMaxLen );

					hr = EMS_OK;
				}
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

