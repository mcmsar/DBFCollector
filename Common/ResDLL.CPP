/********************************************************************
*	ResDLL.cpp
*
*		This is a dummy DLL mainline to be used with resource-only
*		DLLs.
*
*		Written to bypass a problem with loading the dll.
*
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
*					All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
//
//	LAST CHANGED: $Date$
//
//	REVISION HISTORY:
//	$Log$
//
/********************************************************************/

#include <windows.h>

static HMODULE s_hDLLModule = 0;

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  dwReason, LPVOID lpReserved )
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			s_hDLLModule = (HMODULE)hModule;

			break;
		default:
			break;
	}
	return TRUE;
}

