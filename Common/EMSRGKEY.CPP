/********************************************************************
*	Module:			EMSRgKey.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSRegistryKey class
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
#include "emsrgkey.h"

CEMSRegistryKey::CEMSRegistryKey( HANDLE hKey, LPCTSTR lpcszKeyName )
{
	m_hKey = 0;
	m_hKeyRoot = hKey;

	m_lpszKeyName = 0;

	_SetKeyName( lpcszKeyName );

	m_iEnumValue = 0;

	m_bOpen = FALSE;
}

CEMSRegistryKey::~CEMSRegistryKey()
{
	Reset();
}

void CEMSRegistryKey::Reset( void )
{
	if ( m_hKey != 0 )
	{
		CloseKey();

		m_hKey = 0;

		m_iEnumValue = 0;
	}

	if ( m_lpszKeyName )
	{
		delete [ ] m_lpszKeyName;
		m_lpszKeyName = 0;
	}
}

BOOL CEMSRegistryKey::OpenKey( HANDLE hKey, LPCTSTR lpcszKeyName )
{
	if ( !m_bOpen )
	{
		if ( hKey != 0 )
			m_hKeyRoot = hKey;

		if ( lpcszKeyName )
			_SetKeyName( lpcszKeyName );

		m_bOpen = ( ::RegOpenKeyEx( (HKEY)m_hKeyRoot, m_lpszKeyName, 0, 
									KEY_ALL_ACCESS, (HKEY*)&m_hKey ) == ERROR_SUCCESS );

		m_iEnumValue = 0;
	}

	return m_bOpen;
}

BOOL CEMSRegistryKey::CreateKey( HANDLE hKey, LPCTSTR lpcszKeyName )
{
	if ( !m_bOpen )
	{
		DWORD dwDisposition = 0;

		if ( hKey != 0 )
			m_hKeyRoot = hKey;

		if ( lpcszKeyName )
			_SetKeyName( lpcszKeyName );

		m_bOpen = ( ::RegCreateKeyEx( (HKEY)m_hKeyRoot, lpcszKeyName, 0, 0, 
								REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, 
								(HKEY*)&m_hKey, &dwDisposition ) == ERROR_SUCCESS );

		m_iEnumValue = 0;
	}
	return m_bOpen;
}

void CEMSRegistryKey::CloseKey( void )
{
	if ( m_bOpen && m_hKey )
	{
		::RegCloseKey( (HKEY)m_hKey );
		m_iEnumValue = 0;
		m_bOpen = FALSE;
	}
}

BOOL CEMSRegistryKey::QueryValue( LPCTSTR lpcszValueName, LPTSTR lpszValue, int nMaxLength )
{
	int nResult = -1;

	if ( m_bOpen )
	{
		DWORD dwType = 0;
		DWORD dwByteCount = (DWORD)nMaxLength * sizeof( TCHAR );

		nResult = (int)::RegQueryValueEx( (HKEY)m_hKey, lpcszValueName, 0, &dwType,
								(LPBYTE)lpszValue, &dwByteCount );
	}
	return ( nResult == ERROR_SUCCESS );
}

BOOL CEMSRegistryKey::QueryValue( LPCTSTR lpcszValueName, DWORD *pdwValue )
{
	int nResult = -1;

	if ( m_bOpen )
	{
		DWORD dwType = 0;
		DWORD dwByteCount = (DWORD)sizeof(DWORD);

		nResult = (int)::RegQueryValueEx( (HKEY)m_hKey, lpcszValueName, 0, &dwType,
								(LPBYTE)pdwValue, &dwByteCount );
	}
	return ( nResult == ERROR_SUCCESS );
}
int CEMSRegistryKey::SetValue( LPCTSTR lpcszValueName, LPCTSTR lpcszValue )
{
	int nResult = -1;

	if ( m_bOpen )
	{
		DWORD dwByteCount = ( ::lstrlen( lpcszValue ) + 1 ) * sizeof(TCHAR);

		nResult = (int)::RegSetValueEx( (HKEY)m_hKey, lpcszValueName, 0, REG_SZ,
								(BYTE * const)lpcszValue, dwByteCount );
	}

	return nResult;
}

int CEMSRegistryKey::SetValue( LPCTSTR lpcszValueName, DWORD dwValue )
{
	int nResult = -1;

	if ( m_bOpen )
	{
		nResult = (int)::RegSetValueEx( (HKEY)m_hKey, lpcszValueName, 0, REG_DWORD,
								(BYTE * const)&dwValue, sizeof(dwValue) );
	}

	return nResult;
}

int CEMSRegistryKey::DeleteKey( HANDLE hKey, LPCTSTR lpcszKeyName )
{
	if ( hKey != 0 )
		m_hKeyRoot = hKey;

	if ( lpcszKeyName )
		_SetKeyName( lpcszKeyName );

	if ( m_hKey != 0 )
	{
		CloseKey();

		m_hKey = 0;
	}

	if ( m_hKeyRoot && m_lpszKeyName && *m_lpszKeyName )
		::RegDeleteKey( (HKEY)m_hKeyRoot, m_lpszKeyName );

	return 0;
}

int CEMSRegistryKey::_SetKeyName( LPCTSTR lpcszKeyName )
{
	if ( m_lpszKeyName )
	{
		delete [ ] m_lpszKeyName;
		m_lpszKeyName = 0;
	}

	if ( lpcszKeyName && *lpcszKeyName )
	{
		m_lpszKeyName = new TCHAR[ lstrlen( lpcszKeyName ) + 1 ];

		if ( m_lpszKeyName )
			lstrcpy( m_lpszKeyName, lpcszKeyName );
	}
	return ( m_lpszKeyName ) ? lstrlen( m_lpszKeyName ) : 0;
}

BOOL CEMSRegistryKey::EnumKey( LPTSTR lpszKeyName, LPDWORD lpdwLen )
{
	BOOL ret = FALSE;
	FILETIME fileTime;		//only used because RegEnumKeyEx requires it
	LONG lRetCode;

	if( m_bOpen )
	{
		lRetCode = RegEnumKeyEx( (HKEY)m_hKey, m_iEnumValue++, lpszKeyName, lpdwLen, NULL, NULL, NULL, &fileTime );
		ret = ( lRetCode == ERROR_MORE_DATA ) || ( lRetCode == ERROR_SUCCESS );
	}

	return ret;
}