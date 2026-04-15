/********************************************************************
*	Module:			AObjBase.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of CApiObjBase
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

  0.0 01/05/10	    rvw 	start

********************************************************************/
#ifdef WIN32
#include <windows.h>
#endif

#include "AObjBase.h"
#include "emserror.h"
#include <tchar.h>

//#define DEBUGWIN TRUE

#ifdef DEBUGWIN
#include <stdio.h>
#include "debugwin.h"
static CDebugWin debugWin;
static char szDebug[256];
#endif

ULONG volatile CApiObjBase::m_ulObjCount = 0;
ULONG CApiObjBase::m_ulObjSerial = 0;

CApiObjBase::CApiObjBase(LPCTSTR lpcszObjName) : m_lpszName(0)
{
	m_lRefCount = 1;

	if (lpcszObjName && *lpcszObjName)
	{
		m_lpszName = new TCHAR[_tcslen(lpcszObjName) + 1];

		if (m_lpszName)
			_tcscpy(m_lpszName, lpcszObjName);
	}

	m_unID = (UINT)++m_ulObjSerial;

	ObjectCreated();

#ifdef WIN32
#ifdef DEBUGWIN
	sprintf( szDebug, "ObjectCreated( %s ) {%d}", m_lpszName, m_ulObjCount );
	debugWin.OutputMsg( szDebug );
#endif
#endif
}

CApiObjBase::~CApiObjBase()
{
	ObjectDestroyed();

#ifdef WIN32
#ifdef DEBUGWIN
	sprintf( szDebug, "ObjectDestroyed( %s ) {%d}", CApiObjBase::m_lpszName, m_ulObjCount );
	debugWin.OutputMsg( szDebug );
#endif
#endif

	if ( m_lpszName )
	{
		delete [ ] m_lpszName;
		m_lpszName = 0;
	}
}

ULONG CApiObjBase::ObjectCreated()
{
#ifdef WIN32
	return InterlockedIncrement((LONG*)&m_ulObjCount);
#elif defined(__VMS)
	// Note that this method is not thread-safe on VMS.  As a result the accuaracy of m_ulObjCount
	// cannot be guaranteed.
	return ++m_ulObjCount;
#else
#error Platform not supported.
#endif
}

ULONG CApiObjBase::ObjectDestroyed()
{
#ifdef WIN32
	return InterlockedDecrement((LONG*)&m_ulObjCount);
#elif defined(__VMS)
	// Note that this method is not thread-safe on VMS.  As a result the accuaracy of m_ulObjCount
	// cannot be guaranteed.
	return --m_ulObjCount;
#else
#error Platform not supported.
#endif
}

ULONG CApiObjBase::IncrRefCount(void)
{
#ifdef WIN32
	// The LeoLut600DBS links against older versions of the library
	// and will not compile without the following cast
	return InterlockedIncrement((LONG*)&m_lRefCount);
#elif defined(__VMS)
	return ++m_lRefCount;
#else
#error Platform not supported.
#endif
}

ULONG CApiObjBase::DecrRefCount(void)
{
#ifdef WIN32
	// The LeoLut600DBS links against older versions of the library
	// and will not compile without the following cast
	return InterlockedDecrement((LONG*)&m_lRefCount);
#elif defined(__VMS)
	return --m_lRefCount;
#else
#error Platform not supported.
#endif
}

CApiObjBase& 
CApiObjBase::operator=( const CApiObjBase& crhs )
{
	m_lRefCount = crhs.m_lRefCount;
	m_unID = crhs.m_unID;

	if( crhs.m_lpszName )
	{
		if( m_lpszName )
		{
			delete[] m_lpszName;
			m_lpszName = 0;
		}

		long lLen = _tcslen( crhs.m_lpszName );

		if( lLen > 0 )
		{
			m_lpszName = new TCHAR[ lLen + 1 ];

			if( m_lpszName )
			{
				memset( m_lpszName, 0, (lLen+1)*sizeof(TCHAR) );
				_tcsncpy( m_lpszName, crhs.m_lpszName, lLen );
			}
		}
	}

	return *this;
}

ULONG CApiObjBase::AddRef()
{
	return IncrRefCount();
}
	
ULONG CApiObjBase::Release()
{
	ULONG ulRes = DecrRefCount();

	if( 0 == ulRes )
		delete this;

	return ulRes;
}