/********************************************************************
*	Module:			EMSCmReg.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of CEMSComRegistry class
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
#include "emstypes.h"
#include "emscmreg.h"
#include "emsrgkey.h"
#include <tchar.h>

const TCHAR cszInProcServer32[]	= TEXT( "InprocServer32" );
const TCHAR cszLocalServer32[]	= TEXT( "LocalServer32" );
const TCHAR cszLocalService[]	= TEXT( "LocalService" );
const TCHAR cszServiceParameters[]	= TEXT( "ServiceParameters" );
const TCHAR cszThreadModel[]		= TEXT( "ThreadingModel" );
const TCHAR cszFree[]				= TEXT( "Free" );
const TCHAR cszApartment[]		= TEXT( "Apartment" );
const TCHAR cszBoth[]				= TEXT( "Both" );
const TCHAR cszProgID[]			= TEXT( "ProgID" );
const TCHAR cszVersionIndependentProgID[] = TEXT( "VersionIndependentProgID" );
const TCHAR cszProgIDFmt[]		= TEXT( "EMS.%s.%d" );
const TCHAR cszProgIDNoVersionFmt[] = TEXT( "EMS.%s" );
const TCHAR cszCurVer[]			= TEXT( "CurVer" );
const TCHAR cszCLSID[]				= TEXT( "CLSID" );
const TCHAR cszAppID[]				= TEXT( "AppID" );
const TCHAR cszDllSurrogate[]		= TEXT( "DllSurrogate" );
const TCHAR cszRunAs[]			= TEXT( "RunAs" );
const TCHAR cszIUSER[]			= TEXT( "Interactive User" );


CEMSClassReg::CEMSClassReg() : m_szName(0), m_iVersion(0), m_szClsid(0), m_szDescription(0)
{
	memset( &m_clsid, 0, sizeof(CLSID) );
}

CEMSClassReg::CEMSClassReg( const CEMSClassReg& x ) : m_szName(0), m_iVersion(0), m_szClsid(0), m_szDescription(0)
{
	memset( &m_clsid, 0, sizeof(CLSID) );

	SetClassID( x.m_clsid );
	SetName( x.m_szName );
	SetVersion( x.m_iVersion );
	SetClassIDString( x.m_szClsid );
	SetDescription( x.m_szDescription );
}

CEMSClassReg::~CEMSClassReg()
{
	if( m_szName )
	{
		delete[] m_szName;
		m_szName = 0;
	}

	if( m_szClsid )
	{
		delete[] m_szClsid;
		m_szClsid = 0;
	}

	if( m_szDescription )
	{
		delete[] m_szDescription;
		m_szDescription = 0;
	}
}

void
CEMSClassReg::SetClassID( const CLSID cclsid )
{
	memcpy( &m_clsid, &cclsid, sizeof(CLSID) );
}

CLSID 
CEMSClassReg::GetClassID()
{
	CLSID clsidRet;

	memcpy( &clsidRet, &m_clsid, sizeof(CLSID) );

	return clsidRet;
}

void 
CEMSClassReg::SetName( LPCTSTR cszName )
{
	if( cszName )
	{
		if( m_szName )
		{
			delete[] m_szName;
			m_szName = 0;
		}

		long lLen = _tcslen( cszName ) + 1;
		
		m_szName = new TCHAR[ lLen ];
		memset( m_szName, 0, lLen*sizeof(TCHAR) );

		_tcscpy( m_szName, cszName );
	}
}

void 
CEMSClassReg::SetClassIDString( LPCTSTR cszClassID )
{
	if( cszClassID )
	{
		if( m_szClsid )
		{
			delete[] m_szClsid;
			m_szClsid = 0;
		}

		long lLen = _tcslen( cszClassID ) + 1;
		
		m_szClsid = new TCHAR[ lLen ];
		memset( m_szClsid, 0, lLen*sizeof(TCHAR) );

		_tcscpy( m_szClsid, cszClassID );
	}
}

void 
CEMSClassReg::SetDescription( LPCTSTR cszDescription )
{
	if( cszDescription )
	{
		if( m_szDescription )
		{
			delete[] m_szDescription;
			m_szDescription = 0;
		}

		long lLen = _tcslen( cszDescription ) + 1;
		
		m_szDescription = new TCHAR[ lLen ];
		memset( m_szDescription, 0, lLen*sizeof(TCHAR) );

		_tcscpy( m_szDescription, cszDescription );
	}
}

CEMSComRegistry::CEMSComRegistry( )
{
	m_clsContext = EMSCLSCTX_UNKNOWN;
	m_nThreadModel = EMSTHREADMODEL_UNKNOWN;
}

CEMSComRegistry::~CEMSComRegistry()
{
	m_vecClasses.clear();
}

EMS_RESULT CEMSComRegistry::_RegisterClassID( void )
{
	EMS_RESULT hr = EMS_OK;

	for( long l = 0; l < m_vecClasses.size(); l++ )
	{
		CEMSRegistryKey keyCLSID;
		CEMSRegistryKey keyProgID;
		CEMSRegistryKey keyNoVersionProgID;
		TCHAR szValue[256];

		if ( keyCLSID.CreateKey( HKEY_CLASSES_ROOT, cszCLSID ) )
		{
			CEMSRegistryKey keyThisClass;

			/******************************************************************************/
			 if ( keyThisClass.OpenKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
			 {
				 keyThisClass.DeleteKey();
			 }
			/******************************************************************************/

			if ( keyThisClass.CreateKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
			{
	//			CEMSRegistryKey keyInProcServer;

				keyThisClass.SetValue( 0, m_vecClasses[l].GetDescription() );	// Default

				if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), TRUE ) )
				{
					CEMSRegistryKey keyTemp;

					if ( keyTemp.CreateKey( keyThisClass, cszProgID ) )
					{
						keyTemp.SetValue( 0, szValue );
						keyTemp.Reset();
					}
				}

				if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), FALSE ) )
				{
					CEMSRegistryKey keyTemp;

					if ( keyTemp.CreateKey( keyThisClass, cszVersionIndependentProgID ) )
					{
						keyTemp.SetValue( 0, szValue );
						keyTemp.Reset();
					}
				}

				keyThisClass.CloseKey();
			}
			keyCLSID.Reset();
		}

		if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), TRUE ) )
		{
			if ( keyProgID.CreateKey( HKEY_CLASSES_ROOT, szValue ) )
			{
				keyProgID.SetValue( 0,  m_vecClasses[l].GetDescription() );	// Default

				if ( keyCLSID.CreateKey( keyProgID, cszCLSID ) )
				{
					keyCLSID.SetValue( 0, m_vecClasses[l].GetClassIDString() );
					keyCLSID.Reset();
				}
				keyProgID.CloseKey();
			}
		}

		if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), FALSE ) )
		{
			if ( keyNoVersionProgID.CreateKey( HKEY_CLASSES_ROOT, szValue ) )
			{
				keyNoVersionProgID.SetValue( 0, m_vecClasses[l].GetDescription() );	// Default

				if ( keyCLSID.CreateKey( keyNoVersionProgID, cszCLSID ) )
				{
					keyCLSID.SetValue( 0, m_vecClasses[l].GetClassIDString() );
					keyCLSID.Reset();
				}

				if ( keyCLSID.CreateKey( keyNoVersionProgID, cszCurVer ) )
				{
					if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), TRUE ) )
					{
						keyCLSID.SetValue( 0, szValue );
					}
					keyCLSID.Reset();
				}

				keyNoVersionProgID.CloseKey();
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSComRegistry::_UnRegisterClassID( void )
{
	EMS_RESULT hr = EMS_OK;

	for( long l = 0; l < m_vecClasses.size(); l++ )
	{
		CEMSRegistryKey keyCLSID;
		CEMSRegistryKey keyProgID;
		CEMSRegistryKey keyNoVersionProgID;
		TCHAR szValue[256];

		if ( keyCLSID.CreateKey( HKEY_CLASSES_ROOT, cszCLSID ) )
		{
			CEMSRegistryKey keyThisClass;

			if ( keyThisClass.OpenKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
			{
				if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), TRUE ) )
				{
					CEMSRegistryKey keyTemp;

					keyTemp.DeleteKey( keyThisClass, cszProgID );
				}

				if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), FALSE ) )
				{
					CEMSRegistryKey keyTemp;

					keyTemp.DeleteKey( keyThisClass, cszVersionIndependentProgID );
				}

				keyThisClass.CloseKey();

				keyThisClass.DeleteKey();
			}
			keyCLSID.Reset();
		}

		if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), TRUE ) )
		{
			if ( keyProgID.OpenKey( HKEY_CLASSES_ROOT, szValue ) )
			{
				keyCLSID.DeleteKey( keyProgID, cszCLSID );

				keyProgID.CloseKey();

				keyProgID.DeleteKey( );
			}
		}

		if ( _GetProgID( m_vecClasses[l].GetName(), m_vecClasses[l].GetVersion(), szValue, sizeof(szValue) / sizeof( TCHAR ), FALSE ) )
		{
			if ( keyNoVersionProgID.OpenKey( HKEY_CLASSES_ROOT, szValue ) )
			{
				keyNoVersionProgID.SetValue( 0, m_vecClasses[l].GetDescription() );	// Default

				keyCLSID.DeleteKey( keyNoVersionProgID, cszCLSID );

				keyCLSID.DeleteKey( keyNoVersionProgID, cszCurVer );

				keyNoVersionProgID.CloseKey();

				keyNoVersionProgID.DeleteKey();
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSComRegistry::SetThreadModel( int nThreadModel )
{
	EMS_RESULT hr = EMS_OK;

	switch ( nThreadModel )
	{
		case EMSTHREADMODEL_FREE:
		case EMSTHREADMODEL_BOTH:
		case EMSTHREADMODEL_APARTMENT:
		case EMSTHREADMODEL_UNKNOWN:
			m_nThreadModel = nThreadModel;
			break;

		default:
			hr = EMS_BAD_PARAM;
			break;
	}
	return hr;
}

EMS_RESULT CEMSComRegistry::_RegisterInprocServer32( HANDLE hModule, BOOL bSurrogate, LPCTSTR lpcszSurrogateApp )
{
	EMS_RESULT hr = EMS_OK;

	for( long l = 0; l < m_vecClasses.size(); l++ )
	{
		CEMSRegistryKey keyCLSID;
		CEMSRegistryKey keyAppID;
		
		if ( keyCLSID.CreateKey( HKEY_CLASSES_ROOT, cszCLSID ) )
		{
			CEMSRegistryKey keyThisClass;

			if ( keyThisClass.OpenKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
			{
				CEMSRegistryKey keyInProcServer;

				if ( keyInProcServer.CreateKey( keyThisClass, cszInProcServer32 ) )
				{
					TCHAR szModulePathName[MAX_PATH];

					if ( GetModuleFileName( (HMODULE)hModule, szModulePathName,
						sizeof( szModulePathName ) / sizeof( TCHAR )) == 0 )
					{
						szModulePathName[0] = 0;
					}

					keyInProcServer.SetValue( 0, szModulePathName );

					switch ( m_nThreadModel )
					{
						case EMSTHREADMODEL_FREE:
							keyInProcServer.SetValue( cszThreadModel, cszFree );
							break;

						case EMSTHREADMODEL_BOTH:
							keyInProcServer.SetValue( cszThreadModel, cszBoth );
							break;

						case EMSTHREADMODEL_APARTMENT:
							keyInProcServer.SetValue( cszThreadModel, cszApartment );
							break;

						default:
							break;
					}


					keyInProcServer.CloseKey();
				}

				if( bSurrogate )
				{
					keyThisClass.SetValue( cszAppID, m_vecClasses[l].GetClassIDString() );
				}

				keyThisClass.CloseKey();
			}
			keyCLSID.Reset();
		}

		if( bSurrogate )
		{
			if ( keyAppID.OpenKey( HKEY_CLASSES_ROOT, cszAppID ) )
			{	
				CEMSRegistryKey keyThisAppID;

				if ( keyThisAppID.OpenKey( keyAppID, m_vecClasses[l].GetClassIDString() ) )
				{
					keyThisAppID.DeleteKey();
				}

				if ( keyThisAppID.CreateKey( keyAppID, m_vecClasses[l].GetClassIDString() ) )
				{
					keyThisAppID.SetValue( 0, m_vecClasses[l].GetName() );

					keyThisAppID.SetValue( cszDllSurrogate, lpcszSurrogateApp );

					keyThisAppID.SetValue( cszRunAs, cszIUSER );

					keyThisAppID.Reset();

				}

				keyAppID.Reset();
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSComRegistry::_RegisterLocalServer32( CLSID *lpAppID, BOOL bService, LPCTSTR lpcszServiceName )
{
	EMS_RESULT hr = EMS_OK;

	for( long l = 0; l < m_vecClasses.size(); l++ )
	{
		CEMSRegistryKey keyCLSID;
		CEMSRegistryKey keyAppID;

		if ( lpAppID )
		{
			WCHAR wszAppID[ 256 ];
			TCHAR szAppID[ 256 ];

			StringFromGUID2( *lpAppID, wszAppID, sizeof(wszAppID) / sizeof(wszAppID[0]) );

			_WideCharToLocal( szAppID, wszAppID, sizeof(szAppID) / sizeof(szAppID[0]) );

			if ( keyCLSID.OpenKey( HKEY_CLASSES_ROOT, cszCLSID ) )
			{
				CEMSRegistryKey keyThisClass;

				if ( keyThisClass.CreateKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
				{
					CEMSRegistryKey keyLocalServer;

					keyThisClass.SetValue( cszAppID, szAppID );

					if ( keyLocalServer.CreateKey( keyThisClass, cszLocalServer32 ) )
					{
						TCHAR szModulePathName[MAX_PATH];

						if ( GetModuleFileName( 0, szModulePathName,
							sizeof( szModulePathName ) / sizeof( TCHAR )) == 0)
						{
							szModulePathName[0] = 0;
						}

						keyLocalServer.SetValue( 0, szModulePathName );

						keyLocalServer.CloseKey();
					}

					keyThisClass.Reset();
				}
				keyCLSID.Reset();
			}

			if ( keyAppID.OpenKey( HKEY_CLASSES_ROOT, cszAppID ) )
			{	
				CEMSRegistryKey keyThisAppID;

				/*******************************************************************/
				if ( keyThisAppID.OpenKey( keyAppID, szAppID ) )
				{
					keyThisAppID.DeleteKey();
				}
				/*******************************************************************/

				if ( keyThisAppID.CreateKey( keyAppID, szAppID ) )
				{
					keyThisAppID.SetValue( 0, m_vecClasses[l].GetName() );

					if ( bService )
					{
						if ( lpcszServiceName && *lpcszServiceName )
							keyThisAppID.SetValue( cszLocalService, lpcszServiceName );
						else
							keyThisAppID.SetValue( cszLocalService, m_vecClasses[l].GetName() );

						keyThisAppID.SetValue( cszServiceParameters, TEXT("-Service") );
					}

					keyThisAppID.Reset();
				}

				keyAppID.Reset();
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSComRegistry::_UnRegisterInprocServer32( void )
{
	CEMSRegistryKey keyCLSID;
	EMS_RESULT hr = EMS_OK;
	
	if ( keyCLSID.OpenKey( HKEY_CLASSES_ROOT, cszCLSID ) )
	{
		for( long l = 0; l < m_vecClasses.size(); l++ )
		{
			CEMSRegistryKey keyThisClass;

			if ( keyThisClass.OpenKey( keyCLSID, m_vecClasses[l].GetClassIDString() ) )
			{
				CEMSRegistryKey keyInProcServer;

				keyInProcServer.DeleteKey( keyThisClass, cszInProcServer32 );

				keyThisClass.CloseKey();
			}
		}

		keyCLSID.Reset();
	}
	return hr;
}

int CEMSComRegistry::_WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
	int nLength = 0;

	if ( pLocal )
	{
		*pLocal = 0;

#ifdef UNICODE
		lstrcpyn( pLocal, pWide, dwChars );
#else
		WideCharToMultiByte( CP_ACP, 0, pWide, -1, pLocal, dwChars, NULL, NULL);
#endif

		nLength = lstrlen( pLocal );
	}
	return nLength;
}

BOOL CEMSComRegistry::SetClassID( const CLSID* lpClsID, LPCTSTR szName, int iVersion, LPCTSTR szDescription)
{
	BOOL bRet = TRUE;

	if( lpClsID )
	{
		CEMSClassReg classReg;
		classReg.SetClassID( *lpClsID );
		classReg.SetName( szName );
		classReg.SetVersion( iVersion );
		classReg.SetDescription( szDescription );

		TCHAR szCLSID[ 256 ];
		memset( szCLSID, 0, 256*sizeof(TCHAR) );
		// Now get the string version of the class id.
		_ConvertClassIDToString( *lpClsID, szCLSID, 256 );

		classReg.SetClassIDString( szCLSID );

		m_vecClasses.push_back( classReg );

		bRet = TRUE;

	}

	return bRet;
}

void CEMSComRegistry::_ConvertClassIDToString( CLSID clsid, TCHAR* szCLSID, long lLen )
{
	WCHAR wszCLSID[ 256 ];

	StringFromGUID2( clsid, wszCLSID, sizeof(wszCLSID) / sizeof(wszCLSID[0]) );

	_WideCharToLocal( szCLSID, wszCLSID, lLen  );
}

LONG CEMSComRegistry::_RegSetStringValue( HANDLE hKey, LPCTSTR lpcszName, LPCTSTR lpcszValue )
{
	DWORD dwLength = ( lpcszValue ) ? lstrlen( lpcszValue ) + 1 : 0;
	LONG lResult = ( hKey ) ? RegSetValueEx( (HKEY)hKey, lpcszName, 0, REG_SZ, 
											(BYTE*)lpcszValue, dwLength ) : 0;
	return lResult;
}

int CEMSComRegistry::_GetProgID( LPCTSTR lpszComponent, int nVersion, LPTSTR lpszProgID, int nMaxLength, BOOL bVersion )
{
	int nLength = 0;

	if ( lpszProgID && nMaxLength && lpszComponent && *lpszComponent )
	{
 		TCHAR szValue[256];

		if ( bVersion )
	 		wsprintf( szValue, cszProgIDFmt, lpszComponent, nVersion );
		else
	 		wsprintf( szValue, cszProgIDNoVersionFmt, lpszComponent );

		lstrcpyn( lpszProgID, szValue, nMaxLength );

		nLength = lstrlen( lpszProgID );
	}

	return nLength;
}

EMS_RESULT CEMSComRegistry::RegisterInprocServer( HANDLE hModule, BOOL bSurrogate, LPCTSTR lpcszSurrogateApp )
{
	EMS_RESULT hr = _RegisterClassID( );

	hr = _RegisterInprocServer32( hModule, bSurrogate, lpcszSurrogateApp );

	return hr;
}

EMS_RESULT CEMSComRegistry::RegisterLocalServer( CLSID *lpAppID )
{
	EMS_RESULT hr = _RegisterClassID( );

	hr = _RegisterLocalServer32( lpAppID, FALSE );

	return hr;
}

EMS_RESULT CEMSComRegistry::RegisterLocalService( CLSID *lpAppID, LPCTSTR lpcszServiceName )
{
	EMS_RESULT hr = _RegisterClassID( );

	hr = _RegisterLocalServer32( lpAppID, TRUE, lpcszServiceName );

	return hr;
}

EMS_RESULT CEMSComRegistry::UnRegisterLocalServer( void )
{
	EMS_RESULT hr = EMS_OK;

	hr = _UnRegisterClassID( );

	return hr;
}

EMS_RESULT CEMSComRegistry::UnRegisterInprocServer( void )
{
	EMS_RESULT hr = _UnRegisterInprocServer32( );

	hr = _UnRegisterClassID( );

	return hr;
}
