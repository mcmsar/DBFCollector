/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include <windows.h>
#include <math.h>
#include <tchar.h>
#include <stdio.h>
#include <io.h>
#include <time.h>

#include "emstime.h"
#include "emsclock.h"
#include "gsobj.h"
#include "emsconfg.h"



#pragma pack( 1 )

typedef struct _tagEMSFOURCHANNELS
{
	unsigned short	usChannel0;
	unsigned short	usChannel1;
} EMSFOURCHANNELS, *LPEMSFOURCHANNELS;

#pragma pack( )

const TCHAR c_szPulseDefn[ ] = TEXT("Pulse");
const TCHAR c_szTimeOffset[ ] = TEXT("Offset");
const TCHAR c_szGPSComponentName[] = TEXT("GPSClock");
const TCHAR c_szExternalClocking[ ] = TEXT("ExternalClocking");

const char  c_szLogFile[] = "C:\\EMSUSBDTLog.txt";

const int c_nDefaultPulseDefn = 2048;
const int c_nNumOfBuffers     = 8;
const int c_nNumOfADChannels  = 2;

#define CHECKERROR(ecode) if( ( m_Board.status = (ecode) ) != OLNOERROR)\
							{ throw ecode;}


IUnknown *EMSCreateADBoardObject( void )
{
	return new CEMSADBoardGSObject;
}

IUnknown *EMSCreateADMultiBoardObject( void )
{
	// Not supported
	return NULL;
}

CEMSADBoardGSObject::CEMSADBoardGSObject( ) : m_lRefCount(0), m_lpLogFile(NULL), m_bInitialized(false),
											  m_bStarted(false), m_bUseExternalClock(false),
											  m_hEvent(INVALID_HANDLE_VALUE), m_nPulseDefn(c_nDefaultPulseDefn),
											  m_i64TimeOffset(0), m_lpnTransferBuffer(NULL),
											  m_lpnWorkBuffer(NULL), m_lpnTimeBuffer(NULL), m_dwWorkBufferCount(0),
											  m_dwSampleSize(0), m_dwBufferSize(0), m_dwSampleRate(500000),
											  m_i64BlockCount(0), m_i64DropoutCount(0), m_lIndex(0),
											  m_nLastMarker(-1), m_nLastValue(0), m_pMainBuff(NULL), 
											  m_pSharedBuff(NULL), m_pBuffMgr(NULL), m_pCollectionMgr(NULL)
{

	m_mutex.Create( );
	m_lpLogFile = fopen( c_szLogFile, "wt" );
}

CEMSADBoardGSObject::~CEMSADBoardGSObject( )
{
	Reset( );

	if( INVALID_HANDLE_VALUE != m_hEvent )
	{
		CloseHandle( m_hEvent );
		m_hEvent = INVALID_HANDLE_VALUE;
	}

	if( m_lpLogFile )
	{
		fclose( m_lpLogFile );
		m_lpLogFile = NULL;
	}

	m_mutex.Close( );

}

STDMETHODIMP_(ULONG) CEMSADBoardGSObject::AddRef( )
{
   return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSADBoardGSObject::Release( )
{
   LONG lRefCount = InterlockedDecrement( &m_lRefCount );

   if( 0 == lRefCount )
   {
      delete this;
   }
   return lRefCount;
}

STDMETHODIMP 
CEMSADBoardGSObject::QueryInterface( REFIID riid, LPVOID *lppObj )
{
	EMS_RESULT hr = EMS_NOINTERFACE;
	LPUNKNOWN lpUnknown = 0;

	if( IsEqualIID(riid, IID_IEMSADBoard ) )
	{
		lpUnknown = (LPUNKNOWN)(LPEMSADBOARD)this;
	}

	if( lppObj )
	{
		*lppObj = lpUnknown;

		if( lpUnknown )
		{
			lpUnknown->AddRef();

			hr = EMS_OK;
		}
	}

	return hr;
}


STDMETHODIMP 
CEMSADBoardGSObject::Init(  DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate )
{
	EMS_RESULT hr = EMS_OK;

	printf("GSobj Init - Sample Rate: %d \n", dwSampleRate);

	if( !m_bInitialized )
	{
		if( !m_lpLogFile )
		{
			m_lpLogFile = fopen( c_szLogFile, "wt" );
		}

		if( m_lpLogFile )
		{
			fprintf( m_lpLogFile, "\n::Init()\n" );
			fflush( m_lpLogFile );
		}

		//m_hSharedEvent =  CreateEvent(NULL, FALSE, FALSE, NULL);
		//_GetRegistrySettings( );
		m_hEvent = _CreateEvent( "EvDataReadyX" );
		m_hSharedEvent = _CreateEvent( "EvSharedDataReady" );

		if( INVALID_HANDLE_VALUE == m_hEvent )
		{
			hr =  EMS_FALSE;
			return hr;
		}

		if( INVALID_HANDLE_VALUE == m_hSharedEvent )
		{
			hr =  EMS_FALSE;
			return hr;
		}

		//m_pMainBuff = new unsigned char[64000000]; // one second worth of data.
		m_pSharedBuff = new unsigned char[64000000]; // half second worth of data.

		if( !m_pSharedBuff /*|| !m_pMainBuff*/ )
		{
			return EMS_FALSE;
		}

		_Init( dwBufferSize, dwSampleSize, dwSampleRate );

	}
	
	return hr;
}

EMS_RESULT 
CEMSADBoardGSObject::_Init( DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate )
{
	EMS_RESULT hr = EMS_OK;


	if( !m_bInitialized )
	{
		if( m_lpLogFile )
		{
			fprintf( m_lpLogFile, "\n::_Init() - Begin\n" );
			fflush( m_lpLogFile );
		}

		m_dwSampleRate = dwSampleRate;

		printf("GSobj _Init - Sample Rate: %d \n", m_dwSampleRate);

		m_pBuffMgr = new CEMSGSDataBufMgr();

		m_pBuffMgr->SetMainBuffEvent(m_hEvent);
		m_pBuffMgr->SetSharedBuffEvent(m_hSharedEvent);

		m_pBuffMgr->SetMainBuff(m_pMainBuff);
		m_pBuffMgr->SetSharedBuff(m_pSharedBuff);

		m_pCollectionMgr = new CEMSGSDataCollection();

		//m_pCollectionMgr->SetMainBuffEvent(m_hEvent);
		m_pCollectionMgr->SetSharedBuffEvent(m_hSharedEvent);

		//m_pCollectionMgr->SetMainBuff(m_pMainBuff);
		m_pCollectionMgr->SetSharedBuff(m_pSharedBuff);


//		m_pBuffMgr->Initialize(32000000, 10); - Smruti commented
		m_pBuffMgr->Initialize(dwBufferSize, 10);
		m_pBuffMgr->Start();
		m_bInitialized = true;
		
		//m_pCollectionMgr->Start();

	}
	
	return hr;
}


STDMETHODIMP 
CEMSADBoardGSObject::Reset( )
{
	EMS_RESULT hr = EMS_OK;

	if( m_bInitialized )
	{
		m_bInitialized = false;
		Stop();

		if( m_lpnTimeBuffer )
		{
			delete [ ] m_lpnTimeBuffer;
			m_lpnTimeBuffer = 0;
		}

		if( m_lpnWorkBuffer )
		{
			delete [ ] m_lpnWorkBuffer;
			m_lpnWorkBuffer = 0;
		}

		if( m_pBuffMgr )
		{
			delete m_pBuffMgr;
			m_pBuffMgr = NULL;
		}

		if( m_pCollectionMgr )
		{
			delete m_pCollectionMgr;
			m_pCollectionMgr = NULL;
		}

		Sleep(1000);

		if( m_pSharedBuff )
		{
			delete[] m_pSharedBuff;
			m_pSharedBuff = NULL;
		}

		m_bInitialized = false;
	}

	return hr;
}


STDMETHODIMP 
CEMSADBoardGSObject::Start( )
{
	if( m_lpLogFile )
	{
		fprintf( m_lpLogFile, "\n::Start() - Begin\n" );
		fflush( m_lpLogFile );
	}

	EMS_RESULT hr = Init( m_dwBufferSize, m_dwSampleSize, m_dwSampleRate );

	try
	{
		if( EMS_OK == hr && m_pCollectionMgr )
		{
			m_pCollectionMgr->Start();


			m_dwWorkBufferCount = 0;
			m_i64BlockCount = 0;

			// Ticket 24400: Also zero the dropout count
			m_i64DropoutCount = 0;

			m_timeDataBuffer.SetTime( CEMSSystemClock::GetTime( ) );

			try
			{
				if( m_lpLogFile )
				{
					fprintf( m_lpLogFile, "\n::Start() - calling -> olDaStart( m_Board.hdass ) \n" );
					fflush( m_lpLogFile );
				}


				if( m_lpLogFile )
				{
					fprintf( m_lpLogFile, "\n::Start() - olDaStart( m_Board.hdass ) --> Done\n" );
					fflush( m_lpLogFile );
				}
			}
			catch( ... )
			{
				// handle ec.
				if( m_lpLogFile )
				{
				}

				throw;
			}

			// assuming no problem
			if( m_lpLogFile )
			{
				char szMsg[256];
				sprintf( szMsg, "\nCEMSADBoardGSObject::Start() - Running" );
				fprintf( m_lpLogFile, "\n%s", szMsg );
				fflush( m_lpLogFile );
				OutputDebugString( szMsg );
			}

			m_bStarted = true;
		}
		else
		{
			if( m_lpLogFile )
			{
				char szMsg[256];
				sprintf( szMsg, "\nCEMSADBoardGSObject::Start() - Failed to inititialize" );
				fprintf( m_lpLogFile, "\n%s", szMsg );
				fflush( m_lpLogFile );
				OutputDebugString( szMsg );
			}
		}
	}
	catch ( ... )
	{
		// handle ec.
		if( m_lpLogFile )
		{
			fprintf( m_lpLogFile, "\nCEMSADBoardGSObject::Start:  Unknown exception !\n" );
			fflush( m_lpLogFile );
		}

		hr = EMS_EXCEPTION;
	}

	if( m_lpLogFile )
	{
		fprintf( m_lpLogFile, "\n::Start() - End\n" );
		fflush( m_lpLogFile );
	}
	return hr;
}

STDMETHODIMP 
CEMSADBoardGSObject::Stop( )
{
	EMS_RESULT hr = EMS_OK;

	if( m_lpLogFile )
	{
		fprintf( m_lpLogFile, "\n::Stop() - Begin\n" );
		fflush( m_lpLogFile );
	}
	try
	{
		// handle ec.
		if( m_lpLogFile )
		{
			fprintf( m_lpLogFile, "\nCEMSADBoardGSObject::Stop(), Stopping" );
			fflush( m_lpLogFile );
		}

		m_pBuffMgr->Stop();

		m_pCollectionMgr->Stop();
	}
	catch ( ... )
	{

		hr = EMS_EXCEPTION;
	}

	if( m_lpLogFile )
	{
		fprintf( m_lpLogFile, "\n::Stop() - End\n" );
		fflush( m_lpLogFile );
	}
	return hr;
}

STDMETHODIMP 
CEMSADBoardGSObject::Pause( )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP 
CEMSADBoardGSObject::Continue( )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP 
CEMSADBoardGSObject::SetTransferBuffer( short __RPC_FAR *lpBuffer )
{
//	m_lpnTransferBuffer = lpBuffer;

	m_pMainBuff = (unsigned char*)lpBuffer;

	if( m_pBuffMgr )
		m_pBuffMgr->SetMainBuff(m_pMainBuff);

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::LockBuffer( BOOL bWait )
{
	BOOL bLocked = m_mutex.Lock( bWait );
		
	return ( bLocked ) ? EMS_OK : EMS_FALSE;
}

STDMETHODIMP 
CEMSADBoardGSObject::UnlockBuffer( )
{
	m_mutex.Unlock( );
	return EMS_OK;
}


HANDLE 
CEMSADBoardGSObject::_CreateEvent( LPCTSTR lpcszSignalName )
{
	EMS_RESULT hr = EMS_OK;
	HANDLE hEvent = INVALID_HANDLE_VALUE;

	if( lpcszSignalName && *lpcszSignalName )
	{
		SECURITY_ATTRIBUTES attr;         // security attributes
		SECURITY_DESCRIPTOR sd;

		InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );

		SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );

		memset( (void *)&attr, 0, sizeof( attr ) );
		attr.nLength              = sizeof( SECURITY_ATTRIBUTES );
		attr.lpSecurityDescriptor = &sd;
		attr.bInheritHandle       = TRUE;

		hEvent = CreateEvent( &attr, false, false, lpcszSignalName );

		if( !hEvent || ( INVALID_HANDLE_VALUE == hEvent ) )
		{
			hEvent = OpenEvent( EVENT_ALL_ACCESS, false, lpcszSignalName );
		}

		if( !hEvent )
		{
			hEvent = INVALID_HANDLE_VALUE;
		}
	}
	return hEvent;
}

STDMETHODIMP 
CEMSADBoardGSObject::SetEventNameA( unsigned char __RPC_FAR *lpszEventName )
{
	EMS_RESULT hr = EMS_OK;

	m_hEvent = _CreateEvent( (const char *)lpszEventName );

	return ( INVALID_HANDLE_VALUE == m_hEvent ) ? EMS_FALSE : EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::SetEventNameW( WCHAR __RPC_FAR *lpszEventName )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetBlockCount( INT64 __RPC_FAR *lpi64Count )
{
	if( lpi64Count )
	{
		*lpi64Count = m_i64BlockCount;
	}

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetDropoutCount( INT64 __RPC_FAR *lpi64Count )
{
	if( lpi64Count )
	{
		*lpi64Count = m_i64DropoutCount;
	}

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::SetDropoutCount( INT64 i64Count )
{
	m_i64DropoutCount = i64Count;

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetBufferTime( EMSTIME __RPC_FAR *lpTime )
{
	if( lpTime )
	{
		*lpTime = m_timeWorkBuffer;
	}

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetMarkerTimeOffset( INT64 __RPC_FAR *lpi64TimeOffset )
{
	if( lpi64TimeOffset )
	{
		*lpi64TimeOffset = m_i64TimeOffset;
	}

	return EMS_OK;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetVersionInfoW( WORD *lpwVersion,
										 WCHAR *lpszModel, 
										 WORD wMax, 
										 WORD *lpwLength )
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP 
CEMSADBoardGSObject::GetVersionInfoA( WORD *lpwVersion, 
										 unsigned char *lpszModel,
										 WORD wMax,
										 WORD *lpwLength )
{
	return EMS_NOT_IMPLEMENTED;
}

bool 
CEMSADBoardGSObject::_SetMarkerBit( INT nPulse, INT nIndex )
{
	bool bSet = false;

	if( ( ( m_nPulseDefn > 0 ) && ( nPulse > m_nPulseDefn ) ) ||
		( ( m_nPulseDefn < 0 ) && ( nPulse < m_nPulseDefn ) ) )
	{
		if( nIndex != ( m_nLastMarker + 1 ) % m_dwSampleSize )
		{
			m_lpnWorkBuffer[ nIndex ] |= 0x8000;

			m_nLastMarker = nIndex;

			bSet = true;
		}
	}

	return bSet;
}



/*
void 
CEMSADBoardGSObject::_OnBlockDataReady( const void *Buffer, long lSize, long Unused )
{
	LPEMSFOURCHANNELS lpData = (LPEMSFOURCHANNELS)Buffer;

	int nCount = lSize/c_nNumOfADChannels;

	int nTimePulse = 0;

	for( int i = 0; i < nCount; i++ )
	{
		if( (unsigned int)m_dwWorkBufferCount < m_dwSampleSize )
		{
			m_lpnWorkBuffer[ m_dwWorkBufferCount ] = ( (lpData->usChannel0 / 4) ) & 0x3FFF;
			m_lpnTimeBuffer[ m_dwWorkBufferCount ] = lpData->usChannel1;
			m_dwWorkBufferCount++;
		}

		if( m_dwWorkBufferCount == m_dwSampleSize )
		{
			int nMaxValue = 0, nMaxIndex = 0, nMaxCount = 0;
			double dTimeCorrection = (double)( nCount - i ) / (double)m_dwSampleRate;

			nTimePulse = m_nLastValue - m_lpnTimeBuffer[ 0 ];

			_SetMarkerBit( nTimePulse, 0 );

			// Establish 1 second marker bit
			for( DWORD j = 0; j < (m_dwWorkBufferCount - 1); j++ )
			{
				nTimePulse = m_lpnTimeBuffer[ j ] - m_lpnTimeBuffer[ j+1 ];

				_SetMarkerBit( nTimePulse, j );
			}

			m_nLastValue = m_lpnTimeBuffer[ m_dwSampleSize - 1 ];
			m_lIndex++;

			int nCopySize = m_dwSampleSize * sizeof( m_lpnTransferBuffer[0] );

			LockBuffer( TRUE );

			memcpy( m_lpnTransferBuffer, m_lpnWorkBuffer, nCopySize );

			m_timeWorkBuffer.SetTime( m_timeDataBuffer );

			UnlockBuffer( );

			m_timeDataBuffer.SetTime( CEMSSystemClock::GetTime( ) );

			m_timeDataBuffer.AddSeconds( -dTimeCorrection );

			m_timeDataBuffer.AddNanoseconds( -m_i64TimeOffset );	// test to "move" marker to 1/2 sec position

			SetEvent( m_hEvent );

			m_i64BlockCount++;
			
			m_dwWorkBufferCount = 0;
		}
		lpData++;
	}

}*/

EMS_RESULT 
CEMSADBoardGSObject::_GetRegistrySettings( )
{
	EMS_RESULT hr = EMS_OK;
	CEMSRegistryConfig reg;
	TCHAR szValue[ 512 ];
	int nMaxLen = sizeof( szValue ) / sizeof( szValue[0] );

	reg.SetComponentName( c_szGPSComponentName );

	if( reg.OpenKey( ) )
	{
		if( reg.QueryValue( c_szPulseDefn, szValue, nMaxLen ) )
		{
			m_nPulseDefn = atoi( szValue );
		}

		if( reg.QueryValue( c_szTimeOffset, szValue, nMaxLen ) )
		{
			m_i64TimeOffset = atof( szValue ) * 1000000000.0;
		}

		if( reg.QueryValue( c_szExternalClocking, szValue, nMaxLen ) )
		{
			int n = atoi( szValue );
			m_bUseExternalClock = (0 != n) ? true : false;
		}

		reg.CloseKey( );
	}
	return hr;
}
