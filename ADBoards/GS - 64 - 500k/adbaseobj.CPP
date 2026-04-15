/********************************************************************
*	Module:			ADBaseObj.cpp
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

	0.0	01/03/22		rvw	start

********************************************************************/
#include <windows.h>
#include <conio.h>   // INCLUDE
#include <math.h>
#include <iostream>
#include "emstime.h"
#include "emsclock.h"
#include "adbaseobj.h"

CEMSADBoardBaseObject::CEMSADBoardBaseObject()
{
	m_bStarted = false;

	m_bInitialized = false;
	m_lRefCount = 0;

	m_hEvent = INVALID_HANDLE_VALUE;

	m_lpnTransferBuffer = 0;

	m_dwSampleRate = 2000000;

	m_dwSampleSize = m_dwBufferSize = 0;

	m_mutex.Create( );

	m_i64BlockCount =0;
	m_i64DropoutCount=0;

	printf("Running A/D Constructor - sample rate:", m_dwSampleRate);
	//std::cout << "\n Running A/D Constructor - sample rate: " << m_dwSampleRate << std::endl;
}

CEMSADBoardBaseObject::~CEMSADBoardBaseObject()
{
	Reset( );

	if ( INVALID_HANDLE_VALUE != m_hEvent )
	{
		CloseHandle( m_hEvent );
		m_hEvent = INVALID_HANDLE_VALUE;
	}

	m_mutex.Close( );
}

STDMETHODIMP_(ULONG) CEMSADBoardBaseObject::AddRef()
{
   return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSADBoardBaseObject::Release()
{
   LONG lRefCount = InterlockedDecrement( &m_lRefCount );

   if ( 0 == lRefCount )
   {
      delete this;
   }
   return lRefCount;
}

STDMETHODIMP CEMSADBoardBaseObject::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT hr = EMS_NOINTERFACE;
	LPUNKNOWN lpUnknown = 0;

	if ( IsEqualIID(riid, IID_IEMSADBoard ) )
	{
		lpUnknown = (LPUNKNOWN)(LPEMSADBOARD)this;
	}

	if ( lppObj )
	{
		*lppObj = lpUnknown;

		if ( lpUnknown )
		{
			lpUnknown->AddRef();

			hr = EMS_OK;
		}
	}

	return hr;
}

STDMETHODIMP CEMSADBoardBaseObject::Init(  DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate)
{
	EMS_RESULT hr = EMS_OK;

	printf("Running A/D Init");

	if ( !m_bInitialized )
	{
		m_dwSampleRate = dwSampleRate;
		m_dwBufferSize = dwBufferSize;
		m_dwSampleSize = dwSampleSize;

		/*std::cout << "sample rate: " << dwSampleRate <<std::endl;
		std::cout << "sample size: " << dwSampleSize << std::endl;
		std::cout << "buffer size: " << dwBufferSize << std::endl;*/
		printf("Sample Rate: %d\n", dwSampleRate);
	}
	else
		hr = EMS_ALREADY_INITIALIZED;

	return hr;
}


STDMETHODIMP CEMSADBoardBaseObject::Reset( void)
{
	EMS_RESULT hr = EMS_OK;

	if ( m_bInitialized )
	{
		Stop( );

		m_bInitialized = false;
	}

	return hr;
}

STDMETHODIMP CEMSADBoardBaseObject::Start( void)
{
	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::Stop( void)
{
	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::Pause( void)
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP CEMSADBoardBaseObject::Continue( void)
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP CEMSADBoardBaseObject::SetTransferBuffer( short __RPC_FAR *lpBuffer)
{
	m_lpnTransferBuffer = lpBuffer;

	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::LockBuffer( BOOL bWait)
{
	BOOL bLocked = m_mutex.Lock( bWait );
		
	return ( bLocked ) ? EMS_OK : EMS_FALSE;
}

STDMETHODIMP CEMSADBoardBaseObject::UnlockBuffer( void)
{
	m_mutex.Unlock( );
	return EMS_OK;
}

HANDLE CEMSADBoardBaseObject::_CreateEvent( LPCTSTR lpcszSignalName )
{
	EMS_RESULT hr = EMS_OK;
	HANDLE hEvent = INVALID_HANDLE_VALUE;

	if ( lpcszSignalName && *lpcszSignalName )
	{
		SECURITY_ATTRIBUTES     attr;         // security attributes
		SECURITY_DESCRIPTOR sd;

		InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );

		SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );

		memset( (void *)&attr, 0, sizeof( attr ) );
		attr.nLength              = sizeof( SECURITY_ATTRIBUTES );
		attr.lpSecurityDescriptor = &sd;
		attr.bInheritHandle       = TRUE;

		hEvent = CreateEvent( &attr, false, false, lpcszSignalName );

		if ( !hEvent || ( INVALID_HANDLE_VALUE == hEvent ) )
			hEvent = OpenEvent( EVENT_ALL_ACCESS, false, lpcszSignalName );

		if ( !hEvent )
			hEvent = INVALID_HANDLE_VALUE;
	}
	return hEvent;
}

STDMETHODIMP CEMSADBoardBaseObject::SetEventNameA( unsigned char __RPC_FAR *lpszEventName )
{
	EMS_RESULT hr = EMS_OK;

	m_hEvent = _CreateEvent( (const char *)lpszEventName );

	return ( INVALID_HANDLE_VALUE == m_hEvent ) ? EMS_FALSE : EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::SetEventNameW( WCHAR __RPC_FAR *lpszEventName )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP CEMSADBoardBaseObject::GetBlockCount( INT64 __RPC_FAR *lpi64Count)
{
	if ( lpi64Count )
		*lpi64Count = m_i64BlockCount;

	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::GetDropoutCount( INT64 __RPC_FAR *lpi64Count)
{
	if ( lpi64Count )
		*lpi64Count = m_i64DropoutCount;

	double dSeconds = m_timeStarted.SecondsDifferent( m_timeStopped ) ;

	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::SetDropoutCount( INT64 i64Count)
{
	m_i64DropoutCount = i64Count;

	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::GetBufferTime( EMSTIME __RPC_FAR *lpTime)
{
	if ( lpTime )
		*lpTime = m_timeWorkBuffer;

	return EMS_OK;
}

STDMETHODIMP CEMSADBoardBaseObject::GetVersionInfoW( WORD *lpwVersion, 
										WCHAR *lpszModel, WORD wMax, WORD *lpwLength )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP CEMSADBoardBaseObject::GetVersionInfoA( WORD *lpwVersion, 
										unsigned char *lpszModel, WORD wMax, WORD *lpwLength )
{
	return EMS_NOT_IMPLEMENTED;
}

bool CEMSADBoardBaseObject::_SetEvent( void ) 
{
	return ( INVALID_HANDLE_VALUE != m_hEvent ) ? ( TRUE == SetEvent( m_hEvent ) ) : false;
}
