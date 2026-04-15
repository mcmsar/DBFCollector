/********************************************************************
*	Module:			EMSMutex.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSMutex class
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

	0.0	2001 Apr 10	rvw	start

********************************************************************/
#include <windows.h>
#include <string.h>
#include <tchar.h>

#include "emstypes.h"
#include "emserror.h"
#include "emsmutex.h"

CEMSMutex::CEMSMutex( LPCTSTR lpcszName )
{
	m_lpszName = 0;

	SetName( lpcszName );

	m_hMutex = INVALID_HANDLE_VALUE;
}

CEMSMutex::~CEMSMutex()
{
	Close();

	if ( m_lpszName )
	{
		delete m_lpszName;
		m_lpszName = 0;
	}
}

BOOL CEMSMutex::SetName( LPCTSTR lpcszName )
{
	if ( m_lpszName && lpcszName && ( _tcscmp( lpcszName, m_lpszName) == 0 ) )
	{
		// name is the same : so nothing to do
	}
	else
	{
		if ( m_lpszName )
		{
			delete [ ] m_lpszName;

			m_lpszName = 0;
		}

		if ( lpcszName && *lpcszName )
		{
			m_lpszName = new TCHAR[ _tcslen( lpcszName ) + 1 ];

			if ( m_lpszName )
				_tcscpy( m_lpszName, lpcszName );
		}
	}

	return ( m_lpszName != 0 );
}

EMS_RESULT CEMSMutex::Close( void )
{
	if ( m_hMutex != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hMutex );
		m_hMutex = INVALID_HANDLE_VALUE;
	}
	return EMS_OK;
}

EMS_RESULT CEMSMutex::Create( LPCTSTR lpcszName )
{
	EMS_RESULT hr = EMS_OK;
	SECURITY_ATTRIBUTES     attr;         // security attributes
	SECURITY_DESCRIPTOR sd;

	if ( lpcszName )
		SetName( lpcszName );

	InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );

	SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );

	memset( (void *)&attr, 0, sizeof( attr ) );

	attr.nLength = sizeof( SECURITY_ATTRIBUTES );

	attr.lpSecurityDescriptor = &sd;

	attr.bInheritHandle = FALSE;

	m_hMutex = CreateMutex( &attr, FALSE, m_lpszName );

	if ( !m_hMutex )
	{
		hr = HRESULT_FROM_WIN32( GetLastError() );

		m_hMutex = INVALID_HANDLE_VALUE;
	}
	else
		hr = EMS_OK;

	return hr;
}

BOOL CEMSMutex::Lock( ULONG ulTimeout /* INFINITE */ )
{
	BOOL bLocked = FALSE;

	if ( m_hMutex != INVALID_HANDLE_VALUE )
	{
		if ( WaitForSingleObject( m_hMutex, ulTimeout ) == WAIT_OBJECT_0 )
		{
			bLocked = TRUE;
		}
	}

	return bLocked;
}
       
void CEMSMutex::Unlock( void )
{
	if ( m_hMutex != INVALID_HANDLE_VALUE )
	{
		ReleaseMutex( m_hMutex );
	}
}
