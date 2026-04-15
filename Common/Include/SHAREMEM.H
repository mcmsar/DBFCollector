/********************************************************************
*	Module:			ShareMem.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSSharedMemory
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

	0.0	2002/11/20 	rvw	start

********************************************************************/
#ifndef INC_SHAREMEM
#define INC_SHAREMEM

#include "emsmutex.h"

class CEMSSharedMemory
{
public:
	CEMSSharedMemory();
	~CEMSSharedMemory();

	EMS_RESULT Initialize( LPCSTR lpcszName );

	EMS_RESULT Allocate( ULONG ulBytes );
	EMS_RESULT Deallocate( void );

	BOOL Lock( ULONG ulTimeout = 0xFFFFFFFF ) { return m_mutex.Lock( ulTimeout ); }
	void Unlock( void ) { m_mutex.Unlock( ); }

	inline MemExisted( void ) { return m_bExisted; }
	inline LPVOID MemPtr( void ) { return m_lpMem; }
	inline ULONG MemSize( void ) { return m_ulMemSize; }

private:	// methods 
	EMS_RESULT _Allocate( ULONG ulBytes );

private:
	LPTSTR					m_lpszMemName;
	CEMSMutex				m_mutex;
	LPVOID					m_lpMem;
	ULONG						m_ulMemSize;
	BOOL 						m_bInitialized;
	BOOL 						m_bExisted;
};

#endif	// INC_SHAREMEM
