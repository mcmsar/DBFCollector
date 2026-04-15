/********************************************************************
*	Module:			EMSRgKey.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface description for CEMSRegistryKey class
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
#ifndef INC_EMSRGKEY
#define INC_EMSRGKEY

#include "emstypes.h"

class CEMSRegistryKey 
{
public:
	CEMSRegistryKey( HANDLE hKey=0, LPCTSTR lpcszKeyName=0 );
	virtual ~CEMSRegistryKey();

	BOOL OpenKey( HANDLE hKey=0, LPCTSTR lpcszKeyName=0 );
	BOOL CreateKey( HANDLE hKey=0, LPCTSTR lpcszKeyName=0 );
	void CloseKey( void );
	BOOL QueryValue( LPCTSTR lpcszValueName, LPTSTR lpszValue, int nMaxLength );
	BOOL QueryValue( LPCTSTR lpcszValueName, DWORD *pdwValue );
	int SetValue( LPCTSTR lpcszValueName, LPCTSTR lpcszValue );
	int SetValue( LPCTSTR lpcszValueName, DWORD dwValue );
	int DeleteKey( HANDLE hKey=0, LPCTSTR lpcszKeyName=0 );
	BOOL EnumKey( LPTSTR lpszKeyName, LPDWORD lpdwLen );	//returns the name of the first child key on first call
															//then returns the names of subsequent child keys on
															//every other call

	void Reset( void );

	inline operator HANDLE() { return m_hKey; }

private: // methods
	int _SetKeyName( LPCTSTR lpcszKeyName );

private: // data
	HANDLE 	m_hKey;
	HANDLE 	m_hKeyRoot;
	LPTSTR	m_lpszKeyName;
	BOOL		m_bOpen;
	int		m_iEnumValue;

};

#endif // INC_EMSRGKEY
