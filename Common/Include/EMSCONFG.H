/********************************************************************
*	Module:			EMSconfg.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface description for CEMSRegistryConfig class
*
*					assumes settings are read/written to :
*
*						HKEY_LOCAL_MACHINE\EMS Technologies\Components\"Component"
*				 	or HKEY_LOCAL_MACHINE\EMS Technologies\"App"\"Component"
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
#ifndef INC_EMSCONFG
#define INC_EMSCONFG

#include "emstypes.h"
#include "emserror.h"
#include "emsrgkey.h"

class CEMSRegistryConfig 
{
public:
	CEMSRegistryConfig( );
	virtual ~CEMSRegistryConfig();

	void SetComponentName( LPCTSTR lpcszComponent );
	void SetAppName( LPCTSTR lpcszApp );

	BOOL OpenKey( void );
	BOOL CreateKey( void );
	void CloseKey( void );
	int DeleteKey( void );
	int QueryValue( LPCTSTR lpcszValueName, LPTSTR lpszValue, int nMaxLength );
	int QueryValue( LPCTSTR lpcszValueName, DWORD *pdwValue );
	int SetValue( LPCTSTR lpcszValueName, LPCTSTR lpcszValue );
	int SetValue( LPCTSTR lpcszValueName, DWORD dwValue );
	EMS_RESULT FindFile( LPTSTR lpszPath, int nMaxLen, HANDLE hModule, LPCTSTR lpcszFilename );
	
private: // methods
	BOOL _SetName( LPTSTR *lplpszName, LPCTSTR lpcszValue );

private: // data
	CEMSRegistryKey m_key;
	LPTSTR			m_lpszApp;
	LPTSTR			m_lpszComponent;
};

#endif	// INC_EMSCONFG
