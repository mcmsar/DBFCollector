/********************************************************************
*	Module:			LangResources.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Wrappers access to translatable resources
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
	0.0	14Jan2005		CH		Started

********************************************************************/

#ifdef USINGMFC
#include <afxwin.h>         // MFC core and standard components
#endif

#include <assert.h>
#include <mbctype.h>
#include "criticalsection.h"	// CEMSCriticalSection
#include "emsexcpt.h"

#include "LangResources.h"
#include "convutility.h"
#include "logMsgParam.h"
#include "emsrgkey.h"

CEMSLangResources*		CEMSLangResources::ms_pRes = NULL;
CEMSCriticalSection		CEMSLangResources::ms_csCreation;

// Registry keys for current language and path to language-specific dlls
// If these have not been set the software will default to ENGLISH and 
// will look for the dlls in the current directory
const TCHAR c_szLocaleKey[]				= TEXT("SOFTWARE\\EMS Technologies\\Locale");
const TCHAR c_szLanguageFieldOI[]		= TEXT("OILanguage");
const TCHAR c_szPathFieldOI[]			= TEXT("OILanguageFiles");
const TCHAR c_szLanguageFieldService[]	= TEXT("ServicesLanguage");
const TCHAR c_szPathFieldService[]		= TEXT("ServicesLanguageFiles");


CEMSLangResources::CEMSLangResources() :
	CApiObjBase(_T("EMSLangResources")), 
	m_hr( EMS_OK ),
	m_bInit( false ),
	m_bHasErrorMsg( false ),
	m_eLang( EMSLANG_INVALID ),
	m_eApp( EMSAPP_INVALID ),
	m_dwLangID( 0 ),
	m_iStringResCount( 0 ),
	m_hGUIResources( INVALID_HANDLE_VALUE )
{
	for ( int i=0; i<MAX_STRINGRES; i++ )
	{
		m_ahStringResources[i] = INVALID_HANDLE_VALUE;
	}
}

CEMSLangResources::~CEMSLangResources()
{
	if ( m_hGUIResources != INVALID_HANDLE_VALUE )
	{
		FreeLibrary( (HINSTANCE)m_hGUIResources );
		m_hGUIResources = INVALID_HANDLE_VALUE;
	}
	for ( int i = 0; i < m_iStringResCount; i++ )
	{
		if ( m_ahStringResources[i] != INVALID_HANDLE_VALUE )
		{
			FreeLibrary( (HINSTANCE)m_ahStringResources[i] );
			m_ahStringResources[i] = INVALID_HANDLE_VALUE;
		}
	}
	m_iStringResCount	= 0;
	m_eLang				= EMSLANG_INVALID;
	m_eApp				= EMSAPP_INVALID;
	m_bInit				= false;
}
void
CEMSLangResources::Reset()
{
	if ( ms_pRes )
	{
		ms_csCreation.Enter();
		try
		{
			if ( ms_pRes )
			{
				ULONG	ulCount = ms_pRes->Release();
				if ( ulCount == 0 )
				{
					ms_pRes = NULL;
				}
			}
			ms_csCreation.Leave();
		}
		catch( ... )
		{
			ms_csCreation.Leave();
			throw;
		}
	}
	return;
}

EMS_RESULT		
CEMSLangResources::Init( const EMSAPP eApp, wstring* pwstrError )
{
	bool		bAddRef = true;
	EMS_RESULT	hr = EMS_OK;

	// confirm that parameters are valid
	// and that the global array has not been corrupted
	assert( ISVALID_EMSAPP( eApp ) );
	assert( eApp == g_aAppResources[eApp].eTheApp );

	if ( !ms_pRes )
	{
		CEMSLangResources* pRes = NULL;

		ms_csCreation.Enter();

		try
		{
			if( !ms_pRes )
			{
				pRes = new CEMSLangResources();

				if( !pRes )
				{
					hr = EMS_NO_MEMORY;
				}
				else
				{
					hr = pRes->_Init( eApp, pwstrError );
					if ( SUCCEEDED(hr) )
					{
						ms_pRes = pRes;
					}
				}
			}
		}
		catch( ... )
		{
			if ( pwstrError )
			{
				*pwstrError = L"Language resource initialization failed with unexpected exception.";
			}
			hr = EMS_EXCEPTION;
		}
		ms_csCreation.Leave();
		if ( FAILED( hr ) && pRes )
		{
			delete pRes;
		}
	}

	// Didn't create ... so call AddRef()
	if ( SUCCEEDED(hr) && bAddRef )
	{
		ms_pRes->AddRef();
	}

	return hr;
}

// This function may ONLY be called from within the critical section
EMS_RESULT
CEMSLangResources::_Init( const EMSAPP eApp, wstring* pwstrError )
{
	// Have we been called twice in the same exe/dll but with
	// different application specifiers?
	assert( m_eApp == eApp || !m_bInit );

	if ( m_bInit ) return EMS_OK;

	// Assume that the parameter has already been validated
	m_eApp = eApp;

	try
	{
		_InitLocale();

		// Error Strings
		_LoadStringLib( m_eLang );
		// Then GUI resources
		_LoadGUIResources( m_eLang );

		m_bInit = true;
	}
	catch( ... )
	{
		if ( !m_bHasErrorMsg )
		{
			m_bHasErrorMsg = true;
			m_wstrErrorMsg = L"Language resource initialization failed with unexpected exception.";
		}
		if ( pwstrError )
		{
			*pwstrError = m_wstrErrorMsg;
		}
		if ( SUCCEEDED(m_hr) ) m_hr = EMS_EXCEPTION;
	}
#ifdef _DEBUG
	if ( m_bHasErrorMsg )
	{
		m_wstrErrorMsg = m_wstrErrorMsg + L"\n";
		OutputDebugStringW( m_wstrErrorMsg.c_str() );
	}
#endif
	return m_hr;
}

void
CEMSLangResources::_LoadGUIResources( const EMSLANG eLang )
{
	m_hGUIResources = _LoadLib( eLang, g_aAppResources[m_eApp].wszGUIResDLL );
	if ( m_hGUIResources != INVALID_HANDLE_VALUE )
	{
#ifdef USINGMFC
		AfxSetResourceHandle( (HINSTANCE)m_hGUIResources );
#endif
	}
	return;
}

void
CEMSLangResources::_LoadStringLib( const EMSLANG eLang )
{
	assert( m_iStringResCount < MAX_STRINGRES );

	m_ahStringResources[m_iStringResCount] = _LoadLib( eLang, g_aAppResources[m_eApp].wszStringDLL );
	if ( m_ahStringResources[m_iStringResCount] != INVALID_HANDLE_VALUE )
	{
		m_iStringResCount++;
	}
	return;
}

HANDLE
CEMSLangResources::_LoadLib( const EMSLANG eLang, LPCWSTR wszPrefix )
{
	HANDLE	hRet = INVALID_HANDLE_VALUE;
	wstring	wszLib = _BuildLibName( wszPrefix, eLang );
	if ( !wszLib.empty() )
	{
		// NOTE: if use LOAD_LIBRARY_AS_DATAFILE the software will crash when attempting to open a child window
		hRet = LoadLibraryExW(	wszLib.c_str(),
								NULL, 
								DONT_RESOLVE_DLL_REFERENCES );

		if ( !hRet )
		{
			wchar_t	wszError[256];
			swprintf( wszError, L"Unknown error when attempting to load resource file: %s\nSystem error: %ld", wszLib.c_str(), GetLastError() );
			m_wstrErrorMsg = wszError;

			m_bHasErrorMsg = true;
			m_hr = EMS_NO_FILE; // invalid file error
			THROW_RUNTIME_EXCEPTION(m_hr);
		}
	}
	return hRet;
}

wstring
CEMSLangResources::_BuildLibName( LPCWSTR wszDLLPrefix, const EMSLANG eLang )
{
	// There may not be a DLL ... this is ok
	if ( !wszDLLPrefix || wcslen(wszDLLPrefix) == 0 ) return L"";

	// underscore (1) + null term (1) + .dll (4)
	int iLen= 1 + 1 + 4
				+ m_wstrLibPath.length()
				+ wcslen(wszDLLPrefix)
				+ wcslen(g_aLangConstants[eLang].wszAbbrev);

	wstring wszLibName;
	wszLibName.reserve( iLen );

	wszLibName = m_wstrLibPath;
	wszLibName += wszDLLPrefix;
	wszLibName += L"_";
	wszLibName += g_aLangConstants[eLang].wszAbbrev;
	wszLibName += L".DLL"; 

	return wszLibName;
}

void
CEMSLangResources::_InitLocale()
{
	bool bOK = true;

	_LoadConfig();

	// confirm that array has not been corrupted
	assert( m_eLang == g_aLangConstants[m_eLang].eTheLanguage );

	if ( g_aLangConstants[m_eLang].wszLocale 
		&& wcslen(g_aLangConstants[m_eLang].wszLocale) > 0 )
	{
		// Ticket 7351: Previously tried a combo of LC_COLLATE|LC_CTYPE for the specified locale
		// and then english for LC_NUMBERIC|LC_TIME
		// This caused the logger to be unable to retrieve most of its log entries...
		// The following combination seems to work.
		LPCWSTR wszSetLocale = _wsetlocale( LC_ALL, 
											g_aLangConstants[m_eLang].wszLocale );
		bOK = wszSetLocale ? true : false;

		if ( bOK )
		{
			wszSetLocale = _wsetlocale( LC_NUMERIC, L"English_USA.1252" );
			bOK = wszSetLocale ? true : false;
		}

#ifdef _MBCS
		if ( bOK )
		{
			bOK = (0 == _setmbcp( _MB_CP_LOCALE ) );
		}
#endif
		if ( !bOK )
		{
			m_wstrErrorMsg = L"Unable to set the locale to ";
			m_wstrErrorMsg += g_aLangConstants[m_eLang].wszLocale;
			m_bHasErrorMsg = true;
			m_hr = EMS_EXCEPTION;
			THROW_RUNTIME_EXCEPTION(m_hr);
		}
	}
	if ( g_aLangConstants[m_eLang].ulLangID > 0 )
	{
		m_dwLangID = g_aLangConstants[m_eLang].ulLangID;
	}
	else
	{
		// The default language, from the locale
		m_dwLangID = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
	}
	return;
}

wstring	
CEMSLangResources::GetString( const DWORD dwStringID, LPCWSTR wszSingleParam )
{
	LPCWSTR*	awszParams = NULL;
	int			iCount = 0;
	if ( wszSingleParam ) 
	{
		awszParams = &wszSingleParam;
		iCount = 1;
	}

	return GetString( dwStringID, awszParams, iCount );
}

string	
CEMSLangResources::GetStringA( const DWORD dwStringID, LPCSTR szSingleParam )
{
	wstring		wstr;
	if ( szSingleParam )
	{
		wstring		wszParam = CEMSConversionUtil::ConvertToString( szSingleParam );
		LPCWSTR		awszParam[] = { wszParam.c_str() };
		wstr = 	GetString( dwStringID, awszParam, 1 );
	}
	else
	{
		wstr = 	GetString( dwStringID, NULL, 0 );
	}
	return CEMSConversionUtil::ConvertToString( wstr.c_str() );
}
tstring	
CEMSLangResources::GetStringT( const DWORD dwStringID, LPCTSTR szSingleParam )
{
#ifdef UNICODE
	return GetString( dwStringID, szSingleParam ).c_str();
#else
	return GetStringA( dwStringID, szSingleParam ).c_str();
#endif
}

wstring	
CEMSLangResources::GetString( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam )
{
	return GetString( dwStringID, pMsgParam->GetParams(), pMsgParam->GetCount() );
}

string	
CEMSLangResources::GetStringA( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam )
{
	wstring	wstr = GetString( dwStringID, pMsgParam );
	return CEMSConversionUtil::ConvertToString( wstr.c_str() );
}
tstring	
CEMSLangResources::GetStringT( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam )
{
#ifdef UNICODE
	return GetString( dwStringID, pMsgParam ).c_str();
#else
	return GetStringA( dwStringID, pMsgParam ).c_str();
#endif
}

wstring		
CEMSLangResources::GetFormatString( const DWORD dwStringID )
{
	wstring wstr;

	// First try MFC
	if ( ms_pRes )
	{
		wstr = ms_pRes->_GetFormatString( dwStringID );
	}
	else
		// else .. have been called without initialization ... programming error
		assert( false );

	return wstr;
}

string		
CEMSLangResources::GetFormatStringA( const DWORD dwStringID )
{
	wstring	wstr = GetFormatString( dwStringID );
	return CEMSConversionUtil::ConvertToString( wstr.c_str() );
}

tstring		
CEMSLangResources::GetFormatStringT( const DWORD dwStringID )
{
#ifdef UNICODE
	return GetFormatString( dwStringID ).c_str();
#else
	return GetFormatStringA( dwStringID ).c_str();
#endif
}

wstring	
CEMSLangResources::GetString( const DWORD dwStringID, LPCWSTR* awszParams, int iCount )
{
	if ( ms_pRes ) return ms_pRes->_GetString( dwStringID, awszParams, iCount );
	// else .. have been called without initialization ... programming error
	assert( false );
	return L"";
}

wstring	
CEMSLangResources::_GetString( const DWORD dwStringID, LPCWSTR* awszParams, int iCount )
{
	wstring		wstr;

	// To make sure that there are always enough parameters for a message
	// In case a translator adds parameters or a programmer screws up
	// Note that 12 is an arbitrary number .. assuming that we won't have
	// that many parameters
	LPCWSTR		awszPaddedParams[12];
	LPCWSTR		wszBlank = L"";
	LPCWSTR*	awszUseParams = NULL;
	if ( iCount < 12 )
	{
		int ip = 0;
		memset( awszPaddedParams, 0, 12*sizeof(LPCWSTR) );
		for( ip=0; ip<iCount; ip++ )
		{
			awszPaddedParams[ip] = awszParams[ip];
		}
		for ( ip=iCount; ip <12; ip++ )
		{
			awszPaddedParams[ip] = wszBlank;
		}
		awszUseParams = awszPaddedParams;
	}
	else
	{
		awszUseParams = awszParams;
	}

	// First try MFC
	wstr = _GetMFCString( dwStringID, awszUseParams);

	// Then search the separate string table libraries
	for ( int i=0; wstr.empty() && i<m_iStringResCount; i++ )
	{
		assert ( m_ahStringResources[i] != INVALID_HANDLE_VALUE );
		wstr = _GetString( m_ahStringResources[i], dwStringID, awszUseParams );
	}
	_TraceResults( dwStringID, wstr.c_str() );
	return wstr;
}

void
CEMSLangResources::_TraceResults( DWORD dwStringID, LPCWSTR wsz )
{
#ifdef _DEBUG
	wchar_t	wszDbg[512];
	if ( wcslen( wsz ) == 0 )
	{
		swprintf( wszDbg, L"*** ERROR: String not found: 0x%x\n", dwStringID );
		OutputDebugStringW( wszDbg );
	}
	else
	{
		swprintf( wszDbg, L"String 0x%x found. Length %d\n", dwStringID, wcslen(wsz)  );
		OutputDebugStringW( wszDbg );
	}
#endif
}

wstring	
CEMSLangResources::_GetString( HANDLE hLib, const DWORD dwStringID, LPCWSTR* awszParams )
{
	assert ( hLib && hLib != INVALID_HANDLE_VALUE );
	if ( !hLib || INVALID_HANDLE_VALUE == hLib ) return L"";

	wstring		wstrReturn;
	wchar_t		wszBuff[512];
	memset( wszBuff, 0, 512*sizeof(wchar_t) );
	DWORD		dwBuffSize = 512;

	DWORD		dwMsgLen = 0;
	DWORD		dwFlags =	FORMAT_MESSAGE_ARGUMENT_ARRAY |		// params are actually an array
							FORMAT_MESSAGE_FROM_HMODULE |		// use supplied hlib
							FORMAT_MESSAGE_FROM_SYSTEM |		// also try the system error messages
							FORMAT_MESSAGE_MAX_WIDTH_MASK;		// Do not introduce any line breaks aside from
																// explicitly specified in the string (%n)

	dwMsgLen = FormatMessageW(	dwFlags,
								hLib,
								dwStringID,
								0, // use default language 
								wszBuff, dwBuffSize,
								(va_list *)awszParams );

	if ( dwMsgLen > 0 )
	{
		wstrReturn = wszBuff;
	}
	return wstrReturn;
}

// For some reason using CString finds the GUI strings ...
wstring
CEMSLangResources::_GetMFCString( DWORD dwStringID, LPCWSTR* awszParams )
#ifdef USINGMFC
{
	wstring	wstr;

	CString sz;
	sz.LoadString( dwStringID );
	if ( sz.IsEmpty() ) return L""; // no point in going further

#ifdef UNICODE
	wstr = sz;
#else
	wstr = CEMSConversionUtil::ConvertToString( sz );
#endif
	if ( awszParams )
	{
		LPWSTR	wszBuffer = NULL;
			FormatMessageW( FORMAT_MESSAGE_ARGUMENT_ARRAY | 
							FORMAT_MESSAGE_FROM_STRING |
							FORMAT_MESSAGE_ALLOCATE_BUFFER,
							wstr.c_str(), 
							0, // message ID ... not required since we're supplying the format stmt
							0, // language id ... use default
							(LPWSTR)&wszBuffer, // buffer to allocate
							0, // buffer size ... ignored
							(va_list *)awszParams );

		if ( wszBuffer )
		{
			wstr = wszBuffer;
			LocalFree(wszBuffer);
		}
		else
		{
			wstr = L"";
		}
	}
	return wstr;
}
#else
{
	return L"";
}
#endif


wstring				
CEMSLangResources::_GetFormatString( DWORD dwStringID )
{
	wstring wstr;

	wstr = _GetMFCFormatString( dwStringID );
	
	// Then search the separate string table libraries
	for ( int i=0; wstr.empty() && i<m_iStringResCount; i++ )
	{
		assert ( m_ahStringResources[i] != INVALID_HANDLE_VALUE );
		wstr = _GetFormatString( m_ahStringResources[i], dwStringID );
	}

	return wstr;
}

wstring				
CEMSLangResources::_GetFormatString( HANDLE hLib, const DWORD dwStringID )
{
	assert ( hLib && hLib != INVALID_HANDLE_VALUE );
	if ( !hLib || INVALID_HANDLE_VALUE == hLib ) return L"";

	wstring		wstrReturn;
	wchar_t		wszBuff[512];
	memset( wszBuff, 0, 512*sizeof(wchar_t) );
	DWORD		dwBuffSize = 512;

	DWORD		dwMsgLen = 0;
	DWORD		dwFlags =	FORMAT_MESSAGE_IGNORE_INSERTS |		// ignore inserts
							FORMAT_MESSAGE_FROM_HMODULE |		// use supplied hlib
							FORMAT_MESSAGE_FROM_SYSTEM |		// also try the system error messages
							FORMAT_MESSAGE_MAX_WIDTH_MASK;		// Do not introduce any line breaks aside from
																// explicitly specified in the string (%n)

	dwMsgLen = FormatMessageW(	dwFlags,
								hLib,
								dwStringID,
								0, // use default language 
								wszBuff, dwBuffSize,
								0 );

	if ( dwMsgLen > 0 )
	{
		wstrReturn = wszBuff;
	}
	return wstrReturn;
}

wstring				
CEMSLangResources::_GetMFCFormatString( DWORD dwStringID )
#ifdef USINGMFC
{
	wstring	wstr;

	CString sz;
	sz.LoadString( dwStringID );
	if ( sz.IsEmpty() ) return L""; // no point in going further

#ifdef UNICODE
	wstr = sz;
#else
	wstr = CEMSConversionUtil::ConvertToString( sz );
#endif
/*	if ( awszParams )
	{
		LPWSTR	wszBuffer = NULL;
			FormatMessageW( FORMAT_MESSAGE_IGNORE_INSERTS | 
							FORMAT_MESSAGE_FROM_STRING |
							FORMAT_MESSAGE_ALLOCATE_BUFFER,
							wstr.c_str(), 
							0, // message ID ... not required since we're supplying the format stmt
							0, // language id ... use default
							(LPWSTR)&wszBuffer, // buffer to allocate
							0, // buffer size ... ignored
							0 );

		if ( wszBuffer )
		{
			wstr = wszBuffer;
			LocalFree(wszBuffer);
		}
		else
		{
			wstr = L"";
		}
	}
*/
	return wstr;
}
#else
{
	return L"";
}
#endif

// In the absence of the above registry keys the software
// will default to ENGLISH and will look for the language dlls
// in the current directory
void
CEMSLangResources::_LoadConfig()
{
	CEMSRegistryKey 	regKey;
	TCHAR				szLangID[32];
	unsigned long		ulLangID = 0;
	TCHAR				szDLLPath[256];
	wstring				wstrPath;
	LPCTSTR				szField = NULL;
	LPCTSTR				szPathField = NULL;

	switch( g_aAppResources[m_eApp].eAppType )
	{
		case EMSAPPTYPE_OI:
			szField		= c_szLanguageFieldOI;
			szPathField	= c_szPathFieldOI;
			break;
		case EMSAPPTYPE_SERVICE:
		default:
			szField		= c_szLanguageFieldService;
			szPathField	= c_szPathFieldService;
			break;
	}

	// Assume defaults to start
	m_wstrLibPath = L"";
	m_eLang = EMSLANG_DEFAULT;


	if ( regKey.OpenKey( HKEY_LOCAL_MACHINE, c_szLocaleKey ) )
	{
		if ( regKey.QueryValue( szField, szLangID, sizeof( szLangID ) / sizeof( szLangID[0] ) ) )
		{
			ulLangID = CEMSConversionUtil::ConvertToULong( szLangID );
		}
		if ( regKey.QueryValue( szPathField, szDLLPath, sizeof( szDLLPath ) / sizeof( szDLLPath[0] ) ) )
		{
#ifdef UNICODE
			wstrPath = szDLLPath;
#else
			wstrPath = CEMSConversionUtil::ConvertToString( szDLLPath );
#endif
		}
		regKey.CloseKey();
	}
	// Lookup the specified language
	if ( ulLangID > 0 )
	{
		int i=0; 
		while( g_aLangConstants[i].eTheLanguage != EMSLANG_NONE )
		{
			if ( g_aLangConstants[i].ulLangID == ulLangID )
			{
				m_eLang = g_aLangConstants[i].eTheLanguage;
				break;
			}
			i++;
		}
	}
	// Confirm that a valid dll path was specified
	if ( !wstrPath.empty() )
	{
		// ensure that there is a trailing "\"
		if ( wstrPath[wstrPath.length()-1] != L'\\' )
		{
			wstrPath.append( L"\\" );
		}
		// Does the directory exist?
		if ( 0 == _waccess( wstrPath.c_str(), 00 ) )
		{
			m_wstrLibPath = wstrPath;
		}
	}
	// Use the current directory
	if ( m_wstrLibPath.empty() )
	{
		m_wstrLibPath = L".\\";
	}
}

// The following is for use by Win32 dialogs (as opposed to MFC dialogs)
int
CEMSLangResources::DialogBoxParam(	LPCTSTR lpTemplateName,
									HWND hWndParent,
								    DLGPROC lpDialogFunc,
									LPARAM dwInitParam )
{
	if ( ms_pRes ) return ms_pRes->_DialogBoxParam(	lpTemplateName,
													hWndParent,
													lpDialogFunc,
													dwInitParam );
	// else .. have been called without initialization ... programming error
	assert( false );
	return -1;
}

int
CEMSLangResources::_DialogBoxParam(	LPCTSTR lpTemplateName,
									HWND hWndParent,
								    DLGPROC lpDialogFunc,
									LPARAM dwInitParam )
{
	int			iRet = -1; // failure

	HINSTANCE	hLib = (HINSTANCE)m_hGUIResources;
	if ( ( !hLib || hLib == INVALID_HANDLE_VALUE ) && m_iStringResCount > 0 )
	{
		hLib = (HINSTANCE)m_ahStringResources[0];
	}
	if ( hLib && hLib != INVALID_HANDLE_VALUE )
	{
		iRet = ::DialogBoxParam(hLib,
								lpTemplateName, 
								hWndParent, 
								lpDialogFunc,
								dwInitParam );
	}
	return iRet;
}
