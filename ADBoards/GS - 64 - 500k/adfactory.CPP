/********************************************************************
*	Module:			ADFactory.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Class Factory EMS A/D Board Objects
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
#include "adfactory.h"
#include "emsadboard.h"			// IEMSADBoard

volatile LONG CEMSADBoardFactory::m_lLockCount = 0;

CEMSADBoardFactory::CEMSADBoardFactory() :
   m_lRefCount( 0 )
{
}

CEMSADBoardFactory::~CEMSADBoardFactory()
{
}

STDMETHODIMP CEMSADBoardFactory::CreateInstance( IUnknown *pUnkOuter, REFIID riid, void **ppv )
{
	EMS_RESULT hResult = E_NOINTERFACE;

	if (ppv)
		*ppv = 0;

	if (pUnkOuter && (riid != IID_IUnknown))
		hResult = EMS_NOAGGREGATION;
	else
	{	
		IUnknown *lpObject = 0;

		if (riid == IID_IEMSADBoard )
			lpObject = EMSCreateADBoardObject( );
		else if (riid == IID_IEMSADMultiBoard )
			lpObject = EMSCreateADMultiBoardObject( );

		if (lpObject)
		{
			lpObject->AddRef();

			hResult = lpObject->QueryInterface(riid, ppv);

			lpObject->Release();

			lpObject = 0;
		}
	}

	return hResult;
}

STDMETHODIMP CEMSADBoardFactory::QueryInterface(REFIID riid, void **ppv)
{
	IUnknown *pUnknown = 0;
	EMS_RESULT hResult = EMS_NOINTERFACE;

	if (ppv)
		*ppv = 0;

	if (riid == IID_IUnknown)
	{
		pUnknown = (IUnknown*)this;
	}
	else if (riid == IID_IClassFactory)
	{
		pUnknown = (IClassFactory*)this;
	}

	if (pUnknown)
	{
		if (ppv)
		{
			*ppv = pUnknown;

			pUnknown->AddRef();
		}

		hResult = EMS_OK;
	}

	return hResult;
}

STDMETHODIMP_(ULONG) CEMSADBoardFactory::AddRef(void)
{
	LONG lRefCount = InterlockedIncrement(&m_lRefCount);

	return (ULONG) lRefCount;
}

STDMETHODIMP_(ULONG) CEMSADBoardFactory::Release(void)
{
	LONG lRefCount = InterlockedDecrement(&m_lRefCount);

	if ( lRefCount == 0 )
	{
		delete this;
		return 0;
	}
	return lRefCount;
}

STDMETHODIMP CEMSADBoardFactory::LockServer(BOOL bLock)
{
	if (bLock)
		InterlockedIncrement(&m_lLockCount);
	else
		InterlockedDecrement(&m_lLockCount);

	return EMS_OK;
}

