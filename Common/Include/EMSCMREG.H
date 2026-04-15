/********************************************************************
*	Module:			EMSCmReg.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface description for CEMSComRegistry class
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
#ifndef INC_EMSCMREG
#define INC_EMSCMREG

#include <tchar.h>

#include "emscom.h"
#include "emserror.h"
#include <vector>

class CEMSClassReg
{
	public:
		CEMSClassReg();
		CEMSClassReg( const CEMSClassReg& x );
		~CEMSClassReg();

		void SetClassID( const CLSID cclsid );
		CLSID GetClassID();

		void SetName( LPCTSTR cszName );
		inline LPCTSTR GetName() { return m_szName; }

		inline void SetVersion( int iVersion = 1 ) { m_iVersion = iVersion; }
		inline int GetVersion() { return m_iVersion; }

		void SetClassIDString( LPCTSTR cszClassID );
		inline LPCTSTR GetClassIDString() { return m_szClsid; }

		void SetDescription( LPCTSTR cszDescription );
		inline LPCTSTR GetDescription() { return m_szDescription; }
	
	private:
		CLSID m_clsid;
		LPTSTR m_szName;
		int m_iVersion;
		LPTSTR m_szClsid;
		LPTSTR m_szDescription;
};

class CEMSComRegistry
{
public:
	CEMSComRegistry();
	virtual ~CEMSComRegistry();

	BOOL SetClassID( const CLSID *lpClsID, LPCTSTR szName, int iVersion, LPCTSTR szDescription);

	EMS_RESULT RegisterInprocServer( HANDLE hModule = 0, BOOL bSurrogate=FALSE, LPCTSTR lpcszSurrogateApp= _T("\0") );
	EMS_RESULT RegisterLocalServer( CLSID *lpAppID );
	EMS_RESULT RegisterLocalService( CLSID *lpAppID, LPCTSTR lpcszServiceName=0 );
	EMS_RESULT UnRegisterInprocServer( void );
	EMS_RESULT UnRegisterLocalServer( void );
	EMS_RESULT SetThreadModel( int nThreadModel );


private: // methods
	EMS_RESULT _RegisterClassID( void );
	EMS_RESULT _UnRegisterClassID( void );
	EMS_RESULT _RegisterInprocServer32( HANDLE hModule, BOOL bSurrogate=FALSE, LPCTSTR lpcszSurrogateApp= _T("\0") );
	EMS_RESULT _UnRegisterInprocServer32( void );
	EMS_RESULT _RegisterLocalServer32( CLSID *lpAppID, BOOL bService=FALSE, LPCTSTR lpcszServiceName=0 );
	int _WideCharToLocal( LPTSTR pLocal, LPWSTR pWide, DWORD dwChars );
	LONG _RegSetStringValue( HANDLE hKey, LPCTSTR lpcszName, LPCTSTR lpcszValue );
	void _ConvertClassIDToString( CLSID clsid, TCHAR* szCLSID, long lLen );
	int _GetProgID( LPCTSTR lpszComponent, int nVersion, LPTSTR lpszProgID, int nMaxLength, BOOL bVersion );

private: // data

	std::vector<CEMSClassReg>	m_vecClasses;
	EMSCLSCTX					m_clsContext;
	int							m_nThreadModel;
};

#endif // INC_EMSCMREG
