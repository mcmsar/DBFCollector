/********************************************************************
*	Module:			LangResources.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Wrappers access to translatable resources
*
*					Note that the mainline for the executable or DLL
*					must instantiate an instance of this class and
*					call init() on it before the static functions
*					can be used.
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

#ifndef _EMSLANGRESOURCES_HDR
#define _EMSLANGRESOURCES_HDR

#pragma warning( disable : 4018)
#include <string>
using std::string;
using std::wstring;

#include "StdString.h" // tstring
#include "AObjBase.h"

#include "emserror.h"
#include "LangConstants.h"

class CEMSLogMsgParam;
class CEMSCriticalSection;

class CEMSLangResources : public CApiObjBase
{

public:
	// Note that static members are only cleared by an explicit call to Reset()
	CEMSLangResources();
	~CEMSLangResources();

	static EMS_RESULT	Init( const EMSAPP eApp, wstring* pwstrErrorMsg = NULL );

	static void			Reset();

	static wstring		GetString( const DWORD dwStringID, LPCWSTR* awszParams, int iCount );

	static wstring		GetString( const DWORD dwStringID, LPCWSTR wszSingleParam = NULL );
	static string		GetStringA( const DWORD dwStringID, LPCSTR szSingleParam = NULL );
	static tstring		GetStringT( const DWORD dwStringID, LPCTSTR szSingleParam = NULL );

	static wstring		GetString( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam );
	static string		GetStringA( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam );
	static tstring		GetStringT( const DWORD dwStringID, CEMSLogMsgParam* pMsgParam );

	static wstring		GetFormatString( const DWORD dwStringID );
	static string		GetFormatStringA( const DWORD dwStringID );
	static tstring		GetFormatStringT( const DWORD dwStringID );

	static int			DialogBoxParam(	LPCTSTR lpTemplateName,
									HWND hWndParent,
								    DLGPROC lpDialogFunc,
									LPARAM dwInitParam );

private: // methods
	EMS_RESULT			_Init( const EMSAPP eApp, wstring* pwstrErrorMsg );
	void				_InitLocale();
	void				_LoadConfig();
	void				_LoadGUIResources( const EMSLANG eLang );
	void				_LoadStringLib( const EMSLANG eLang );
	HANDLE				_LoadLib( const EMSLANG eLang, LPCWSTR wszPrefix );
	wstring				_BuildLibName( LPCWSTR wszDLLPrefix, const EMSLANG eLang );

	wstring				_GetString( const DWORD dwStringID, LPCWSTR* awszParams, int iCount );
	wstring				_GetString( HANDLE hLib, const DWORD dwStringID, LPCWSTR* awszParams );
	wstring				_GetMFCString( DWORD dwStringID, LPCWSTR* awszParams );
	wstring				_GetFormatString( DWORD dwStringID );
	wstring				_GetFormatString( HANDLE hLib, const DWORD dwStringID );
	wstring				_GetMFCFormatString( DWORD dwStringID );

	void				_TraceResults( DWORD dwStringID, LPCWSTR wsz );

	int					_DialogBoxParam(	LPCTSTR lpTemplateName,
											HWND hWndParent,
										    DLGPROC lpDialogFunc,
											LPARAM dwInitParam );

private: // data
	// For initialization errors only!
	wstring						m_wstrErrorMsg;
	bool						m_bHasErrorMsg;
	EMS_RESULT					m_hr;
	
	bool						m_bInit;

	EMSLANG						m_eLang;
	EMSAPP						m_eApp;
	DWORD						m_dwLangID;
	wstring						m_wstrLibPath;

	#define MAX_STRINGRES 2
	HANDLE						m_hGUIResources;
	HANDLE						m_ahStringResources[MAX_STRINGRES];
	int							m_iStringResCount;

	static CEMSLangResources*	ms_pRes;
	static CEMSCriticalSection	ms_csCreation;

};

#endif // _EMSLANGRESOURCES_HDR

