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
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include "emstypes.h"
#include "sharemem.h"
#include "cmmlib.h"

CEMSSharedMemory::CEMSSharedMemory()
{
	m_lpszMemName = 0;

	m_lpMem =0;

	m_ulMemSize = 0;

	m_bInitialized = m_bExisted = FALSE;
}

CEMSSharedMemory::~CEMSSharedMemory()
{
	Deallocate();

	if ( m_lpszMemName )
	{
		delete [ ] m_lpszMemName;
		m_lpszMemName = 0;
	}

	m_mutex.Close();
}

EMS_RESULT CEMSSharedMemory::Initialize( LPCSTR lpcszName )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szTemp[ 256 ];

	if ( !m_bInitialized )
	{
		if ( lpcszName && *lpcszName )
		{
			_stprintf( szTemp, TEXT("EMS_%s_MUX") , lpcszName );

			m_mutex.Create( szTemp );

			_stprintf( szTemp, TEXT("EMS_%s_MEM") , lpcszName );

			m_lpszMemName = new TCHAR [ lstrlen( szTemp ) + 1 ];

			if ( m_lpszMemName )
			{
				lstrcpy( m_lpszMemName, szTemp );

				m_bInitialized = TRUE;
			}
			else
				hr = EMS_NO_MEMORY;
		}
		else
			hr = EMS_BAD_PARAM;

		m_bExisted = FALSE;
	}

	return hr;
}

EMS_RESULT CEMSSharedMemory::Allocate( ULONG ulBytes )
{
	EMS_RESULT hr = EMS_OK;
//	TCHAR szTemp[ 256 ];

	if ( ulBytes && m_bInitialized )
	{
		hr = _Allocate( ulBytes );

		if ( hr == EMS_OK )
		{
			m_ulMemSize = ulBytes;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSharedMemory::Deallocate( void )
{
	if ( m_lpMem && m_lpszMemName )
	{
		CMM_CloseMem( (char *)m_lpszMemName );

		m_lpMem = 0;

		m_ulMemSize = 0;
	}
	return EMS_OK;
}

EMS_RESULT CEMSSharedMemory::_Allocate( ULONG ulBytes )
{
	EMS_RESULT hr = EMS_OK;
	LONG lMemSizeKB = ( ulBytes + 1023 ) / 1024;

	m_lpMem = CMM_CreateMem( (char *)m_lpszMemName, &lMemSizeKB );

	if ( m_lpMem )	// this instance has "created" the memory
	{
		m_bExisted = FALSE;
	}
	else
	{
		m_lpMem = CMM_OpenMem( (char *)m_lpszMemName, &lMemSizeKB );

		m_bExisted = TRUE;
	}

	if ( m_lpMem )
	{
		if ( ( lMemSizeKB * 1024 ) < (long)ulBytes )	// not enough!
		{
			Deallocate();

			hr = EMS_NO_MEMORY;
		}
	}
	else
		hr = EMS_NO_MEMORY;

	return hr;
}

