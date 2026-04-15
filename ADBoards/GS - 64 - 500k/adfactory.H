/********************************************************************
*	Module:			ADFactory.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface to CEMSADBoardFactory 
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
#ifndef INC_ADFACTORY
#define INC_ADFACTORY

#include "emscom.h"


class CEMSADBoardFactory : public IClassFactory 
{
public:
	CEMSADBoardFactory( );

/*********************************************************************
*	IClassFactory Interfaces
*********************************************************************/
	STDMETHOD(CreateInstance)	(IUnknown *pUnkOuter, REFIID riid, void **ppv);
	STDMETHOD(LockServer)	(BOOL bLock);

/*********************************************************************
*	IUnknown Interfaces
*********************************************************************/
	STDMETHOD(QueryInterface)	(REFIID riid, void **ppv);
	STDMETHOD_(ULONG, AddRef)	(void);
	STDMETHOD_(ULONG, Release)	(void);

	static ULONG LockCount(void) { return (ULONG)m_lLockCount; }

	friend IUnknown *EMSCreateADBoardObject( void );
	friend IUnknown *EMSCreateADMultiBoardObject( void );

private: // methods
	virtual ~CEMSADBoardFactory();

private: // data
	static volatile LONG		m_lLockCount;
	volatile LONG				m_lRefCount;
};

#endif // INC_ADFACTORY
