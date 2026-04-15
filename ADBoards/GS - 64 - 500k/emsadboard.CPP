/********************************************************************
*	Module:			EMSADBoard.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

	0.0	2005/04/12 	rvw	start

********************************************************************/
#include <windows.h>
#include "emscmreg.h"

#define INITGUID			
#include <initguid.h>
#include "emsadboard.h"
#include "adfactory.h"

const TCHAR cszComponentName[]	= TEXT("ADBoard");
const TCHAR cszComponentDesc[]	= TEXT("EMSAnalogToDigitalBoard");
const int ciVersion = 1;

/* global */ HMODULE 	g_hDLLModule = 0;

extern "C" BOOL WINAPI DllMain( HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			g_hDLLModule = (HMODULE)hModule;

			break;

		case DLL_PROCESS_DETACH:
			break;

		default:
			break;
	}
    return TRUE;
}

STDAPI DllRegisterServer(VOID)
{
	CEMSComRegistry comReg;
	comReg.SetClassID( &CLSID_EMSADBoard, cszComponentName, ciVersion, cszComponentDesc );

	comReg.SetThreadModel( EMSTHREADMODEL_BOTH );

	return comReg.RegisterInprocServer( g_hDLLModule );
}

STDAPI DllUnregisterServer(VOID)
{
	CEMSComRegistry comReg;
	comReg.SetClassID( &CLSID_EMSADBoard, cszComponentName, ciVersion, cszComponentDesc );

	return comReg.UnRegisterInprocServer();
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID FAR *ppv)
{
	EMS_RESULT hResult = EMS_OK;
	LPUNKNOWN lpUnk = 0;

	if (ppv)
		*ppv = 0;

	if ( CLSID_EMSADBoard == rclsid )
	{
		CEMSADBoardFactory *lpFactory = new CEMSADBoardFactory();

		if (lpFactory)
		{
			lpFactory->AddRef();

			hResult = lpFactory->QueryInterface(riid, ppv);

			lpFactory->Release();	// if QueryInterface failed : instance deleted

			lpFactory = 0;
		}
	}
	else 
		hResult = EMS_CLASSNOTAVAILABLE;

	return hResult;
}

STDAPI DllCanUnloadNow(void)
{
	HRESULT hr = S_FALSE;
	UINT unLockCount = CEMSADBoardFactory::LockCount();

	if (unLockCount==0) 
		hr = S_OK;

	return hr;
}
