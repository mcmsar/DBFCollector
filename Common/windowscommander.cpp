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

	$Log:
	$
********************************************************************/

#include "windowscommander.h"
#include <windows.h>

void 
CEMSWindowsCommander::Reboot()
{
	_ExitWindows( EWX_REBOOT );
}

void 
CEMSWindowsCommander::RebootForce()
{
	_ExitWindows( EWX_REBOOT | EWX_FORCE );
}

void
CEMSWindowsCommander::Shutdown()
{
	HANDLE hToken = 0;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // token structure 
 
	BOOL bRet = TRUE;
 
	// Get the current process token handle so we can get shutdown 
	// privilege. 
 	if (OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		// Get the LUID for shutdown privilege. 
 		bRet = LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
				&tkp.Privileges[0].Luid); 
	}
 
	if( bRet )
	{
		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
		// Get shutdown privilege for this process. 
 		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
			(PTOKEN_PRIVILEGES) NULL, 0); 
 
		// Cannot reliably test the return value of AdjustTokenPrivileges (according to MSDN documentation).
 		if (GetLastError() != ERROR_SUCCESS) 
			bRet = FALSE;

		if( bRet )
		{
			bRet = InitiateSystemShutdownEx( NULL, NULL, 3, TRUE, FALSE, 
										SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED );
		}
	
		// No guarantee what happens beyond here.  The shutdown occurs asynchronously.

		// Disable shutdown privilege.
		tkp.Privileges[0].Attributes = 0; 
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
				(PTOKEN_PRIVILEGES) NULL, 0); 

		if (GetLastError() != ERROR_SUCCESS) 
			bRet = FALSE;
	}

	if( hToken )
		CloseHandle( hToken );
}

void
CEMSWindowsCommander::_ExitWindows( const DWORD cdwFlags )
{
	HANDLE hToken = 0;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // token structure 
 
	BOOL bRet = TRUE;
 
	// Get the current process token handle so we can get shutdown 
	// privilege. 
 	if (OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		// Get the LUID for shutdown privilege. 
 		bRet = LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
				&tkp.Privileges[0].Luid); 
	}
 
	if( bRet )
	{
		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
		// Get shutdown privilege for this process. 
 		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
			(PTOKEN_PRIVILEGES) NULL, 0); 
 
		// Cannot reliably test the return value of AdjustTokenPrivileges (according to MSDN documentation).
 		if (GetLastError() != ERROR_SUCCESS) 
			bRet = FALSE;

		if( bRet )
		{
			bRet = ExitWindowsEx( cdwFlags, SHTDN_REASON_MAJOR_OTHER | SHTDN_REASON_MINOR_OTHER | SHTDN_REASON_FLAG_PLANNED );
		}
	
		// No guarantee what happens beyond here.  The shutdown occurs asynchronously.

		// Disable shutdown privilege.
		tkp.Privileges[0].Attributes = 0; 
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
				(PTOKEN_PRIVILEGES) NULL, 0); 

		if (GetLastError() != ERROR_SUCCESS) 
			bRet = FALSE;
	}

	if( hToken )
		CloseHandle( hToken );
}