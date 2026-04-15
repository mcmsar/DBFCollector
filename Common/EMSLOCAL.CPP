/********************************************************************
*	Module:			emslocal.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSLocale - Localization Support Object
*						
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

	0.0	2001/06/01	rvw	start

********************************************************************/
#include <memory.h>
#include <windows.h>
#include <winnt.h>

#include <stdio.h>	// DEBUG ONLY

#include "emslocal.h"

//#include "D:\devsar\include\debugwin.h"
//static CDebugWin debugWin;
//static char szDebug[256];

CEMSLocale::CEMSLocale( LPCTSTR lpcszFilespec, WORD wLangID )
{
	m_wCurrentLanguageID = m_wDesiredLanguageID = wLangID;

	if ( m_wDesiredLanguageID == 0 )
		m_wDesiredLanguageID = MAKELANGID( LANG_SPANISH, SUBLANG_SPANISH_ARGENTINA );
	
	m_lpszResFilespec = 0;

	SetFilespec( lpcszFilespec );

	m_hResHandle = INVALID_HANDLE_VALUE;

	m_lastError = EMS_OK;

	m_bInitialized = FALSE;
}

CEMSLocale::~CEMSLocale()
{
	if ( m_bInitialized)
		UnInitialize();

	if ( m_lpszResFilespec )
	{
		delete m_lpszResFilespec;
		m_lpszResFilespec = 0;
	}
}

BOOL CEMSLocale::IsValid( void )
{
	return ( m_hResHandle != INVALID_HANDLE_VALUE );
}


EMS_RESULT CEMSLocale::Initialize( LPCTSTR lpcszFilespec, WORD wLangID )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( !m_bInitialized )
	{
		if ( lpcszFilespec && *lpcszFilespec )
			SetFilespec( lpcszFilespec );

		if ( wLangID )
			m_wDesiredLanguageID = wLangID;

		m_wCurrentLanguageID = m_wDesiredLanguageID;

		m_hResHandle = _LoadLibrary( &m_wCurrentLanguageID );

		if ( m_hResHandle )
 		{
				if ( m_wCurrentLanguageID == m_wDesiredLanguageID )
				hr = EMS_OK;
			else
				hr = EMS_NOT_DESIRED_LANGUAGE;
		}
		else
			m_hResHandle = INVALID_HANDLE_VALUE;

		m_bInitialized = ( m_hResHandle != INVALID_HANDLE_VALUE );
	}
	else
		hr = EMS_ALREADY_INITIALIZED;

	m_lastError = hr;

	return hr;
}

void CEMSLocale::UnInitialize( void )
{
	m_lastError = EMS_OK;

	if ( m_bInitialized )
	{
		if ( m_hResHandle != INVALID_HANDLE_VALUE )
		{
			FreeLibrary( (HINSTANCE)m_hResHandle );

			m_hResHandle = INVALID_HANDLE_VALUE;
		}
		m_bInitialized = FALSE;
	}
}

int CEMSLocale::SetFilespec( LPCTSTR lpcszFilespec )
{
	int nLength = 0;

	if ( m_lpszResFilespec )
	{
		delete m_lpszResFilespec;

		m_lpszResFilespec = 0;
	}

	if ( lpcszFilespec && *lpcszFilespec )
	{
		nLength = lstrlen( lpcszFilespec );

		m_lpszResFilespec = new TCHAR [ nLength + 1 ];

		if ( m_lpszResFilespec )
			lstrcpy( m_lpszResFilespec, lpcszFilespec );
	}

	m_lastError = EMS_OK;

	return nLength;
}

static BOOL  CALLBACK _EnumCallback( HINSTANCE hModule, LPCTSTR lpcszType ,
			LPCTSTR lpszName, WORD wLanguage, LONG lParam )
{
	printf("Language %X\n", wLanguage );
	return TRUE;
}


static BOOL CALLBACK _EnumTypesProc(
  HINSTANCE hModule,  // resource-module handle
  LPTSTR lpszType, // pointer to resource type
  LONG lParam      // application-defined parameter
)
{
		
		return TRUE;
}
 
int CEMSLocale::LoadString( UINT unID, LPTSTR lpszBuffer, int nBufferMax, WORD wLangID )
{
	int nLength = 0;

	m_lastError = EMS_OK;

	if ( m_bInitialized )
	{
		if ( wLangID == 0 )
			wLangID = m_wCurrentLanguageID;

		if ( m_hResHandle != INVALID_HANDLE_VALUE )
		{
			LCID lcidSave = GetThreadLocale();

			SetThreadLocale( MAKELCID( wLangID, SORT_DEFAULT ) );

			nLength = ::LoadString( (HINSTANCE)m_hResHandle, unID , lpszBuffer, nBufferMax );

			SetThreadLocale( lcidSave );
		}
	}
	else
		m_lastError = EMS_NOT_INITIALIZED;

	return nLength;
}

HANDLE CEMSLocale::_LoadLibrary( LPWORD lpwLanguageID )
{
	HANDLE hResHandle = 0;
	BOOL bDone = FALSE;
	TCHAR szFilespec[256], szExt[32];
	WORD wLanguageID = ( lpwLanguageID ) ? *lpwLanguageID : 0;

	if ( m_lpszResFilespec && *m_lpszResFilespec )
	{
		while ( !bDone )
		{
			if ( _LanguageSuffix( szExt, sizeof(szExt)/sizeof(TCHAR), wLanguageID ) )
			{
				wsprintf( szFilespec, m_lpszResFilespec, szExt );

				hResHandle = (HANDLE)LoadLibrary( szFilespec );

				if ( hResHandle )
				{
					if ( lpwLanguageID )
						*lpwLanguageID = wLanguageID;

					bDone = TRUE;
				}
				else
				{
					m_lastError = GetLastError();
				}
			}

			if ( !bDone )
			{
				WORD wPrime = PRIMARYLANGID( wLanguageID );
				WORD wSub = SUBLANGID( wLanguageID );

				if ( wPrime == LANG_NEUTRAL )
				{
					if ( wSub == SUBLANG_NEUTRAL )
						bDone = TRUE;
					else
						wLanguageID = MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL );
				}
				else if ( wPrime == LANG_ENGLISH )
				{
					if ( wSub == SUBLANG_NEUTRAL )
						wLanguageID = MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT );
					else
						wLanguageID = MAKELANGID( LANG_ENGLISH, SUBLANG_NEUTRAL );
				}
				else
				{
					if ( ( wSub != SUBLANG_NEUTRAL ) && ( wSub != SUBLANG_DEFAULT ) )
						wLanguageID = MAKELANGID( wPrime, SUBLANG_DEFAULT );
					else if ( wSub == SUBLANG_DEFAULT )
						wLanguageID = MAKELANGID( wPrime, SUBLANG_NEUTRAL );
					else
						wLanguageID = MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT );
				}
			}
		}
	}
	else
		m_lastError = EMS_INVALID_FILESPEC;

	return hResHandle;
}

BOOL CEMSLocale::_LanguageSuffix( LPTSTR lpszExt, int nMaxLength, WORD wLanguageID )
{
	BOOL bOK = FALSE;
	TCHAR *lpszTemp = 0;

	if ( lpszTemp && nMaxLength )
		*lpszTemp = 0;

	switch ( wLanguageID )
	{
		case MAKELANGID( LANG_SPANISH, SUBLANG_NEUTRAL ):
		case MAKELANGID( LANG_SPANISH, SUBLANG_DEFAULT ):
			lpszTemp = TEXT("SPN");
			break;

		case MAKELANGID( LANG_SPANISH, SUBLANG_SPANISH_ARGENTINA ):
			lpszTemp = TEXT("SPA");
			break;

		default:	
			lpszTemp = 0;
			break;
	}						

	if ( lpszTemp )
	{
		int nLength = lstrlen( lpszTemp );

		if ( nLength < nMaxLength )
		{
			lstrcpy( lpszExt, lpszTemp );

			bOK = TRUE;
		}
	}

	return bOK;
}

