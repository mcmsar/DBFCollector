/********************************************************************
*	Module:			AObjBase.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Definitions for platform independent data types
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

  0.0 01/05/10	    rvw 	start

********************************************************************/
#ifndef INC_AOBJBASE
#define INC_AOBJBASE

#include "emstypes.h"

class CApiObjBase  
{
public:
	CApiObjBase(LPCTSTR lpcszObjName=TEXT("?"));
	virtual ~CApiObjBase();

	inline static ULONG ObjectCount(void) { return m_ulObjCount; }

	ULONG IncrRefCount(void);
	ULONG DecrRefCount(void);
	inline ULONG GetRefCount(void) { return (ULONG)m_lRefCount; }

	CApiObjBase& operator=( const CApiObjBase& crhs );

	ULONG AddRef();
	ULONG Release();
	
protected: // methods
	static ULONG ObjectCreated(void);
	static ULONG ObjectDestroyed(void);

private: // data	
	static volatile ULONG m_ulObjCount;
	static ULONG m_ulObjSerial;

	volatile  LONG	m_lRefCount;
	LPTSTR m_lpszName;
	UINT	m_unID;

};

#endif // INC_AOBJBASE
