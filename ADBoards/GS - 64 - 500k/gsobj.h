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

#ifndef INC_USBDTOBJ 
#define INC_USBDTOBJ

#include <stdio.h>

#include "emsadboard.h"
#include "emserror.h"
#include "emstime.h"
#include "emsmutex.h"
#include "EMSGSDataCollection.h"
#include "EMSGSDataBufMgr.h"

/* simple structure used with board */

class CEMSADBoardGSObject : public IEMSADBoard
{
public:
	CEMSADBoardGSObject( );

/*********************************************************************
*	IEMSADBoard Methods
*********************************************************************/
	HRESULT STDMETHODCALLTYPE Init(  DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate );
	HRESULT STDMETHODCALLTYPE Reset( );
	HRESULT STDMETHODCALLTYPE Start( );
	HRESULT STDMETHODCALLTYPE Stop( );
	HRESULT STDMETHODCALLTYPE Pause( );
	HRESULT STDMETHODCALLTYPE Continue( );
	HRESULT STDMETHODCALLTYPE SetTransferBuffer( short __RPC_FAR *lpBuffer );
	HRESULT STDMETHODCALLTYPE LockBuffer( BOOL bWait );
	HRESULT STDMETHODCALLTYPE UnlockBuffer( );
	HRESULT STDMETHODCALLTYPE GetEventHandle( DWORD __RPC_FAR *lphEvent );
	HRESULT STDMETHODCALLTYPE GetBlockCount( INT64 __RPC_FAR *lpi64Count );
	HRESULT STDMETHODCALLTYPE GetDropoutCount( INT64 __RPC_FAR *lpi64Count );
	HRESULT STDMETHODCALLTYPE SetDropoutCount( INT64 i64Count );
	HRESULT STDMETHODCALLTYPE GetBufferTime( EMSTIME __RPC_FAR *lpTime );

	HRESULT STDMETHODCALLTYPE GetMarkerTimeOffset( INT64 __RPC_FAR *lp64TimeOffset );

	HRESULT STDMETHODCALLTYPE SetEventNameA( unsigned char __RPC_FAR *lpszEventName );
	HRESULT STDMETHODCALLTYPE SetEventNameW( WCHAR __RPC_FAR *lpszEventName );

	HRESULT STDMETHODCALLTYPE GetVersionInfoA( WORD __RPC_FAR *lpwVersion,
            unsigned char __RPC_FAR *lpszModel,
            WORD wMax, WORD __RPC_FAR *lpwLength );
        
	HRESULT STDMETHODCALLTYPE GetVersionInfoW( WORD __RPC_FAR *lpwVersion,
            WCHAR __RPC_FAR *lpszModel,
            WORD wMax, WORD __RPC_FAR *lpwLength );

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);

protected: // methods


private: // methods
	virtual ~CEMSADBoardGSObject( );

	bool _SetMarkerBit( INT nPulse, INT nIndex );
	EMS_RESULT _GetRegistrySettings( );

	EMS_RESULT _Init(  DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate );

	HANDLE _CreateEvent( LPCTSTR lpcszSignalName );

private: // data
	volatile LONG  	m_lRefCount;
	
	FILE*				m_lpLogFile;
	bool				m_bInitialized;
	bool				m_bStarted;
	bool				m_bUseExternalClock;
	INT					m_nPulseDefn;
	INT64				m_i64TimeOffset;
	short*				m_lpnTransferBuffer;
	unsigned short*		m_lpnWorkBuffer;
	unsigned short*		m_lpnTimeBuffer;
	DWORD				m_dwWorkBufferCount;
	DWORD				m_dwSampleSize;
	DWORD				m_dwBufferSize;
	DWORD				m_dwSampleRate;
	INT64				m_i64BlockCount;
	INT64				m_i64DropoutCount;
	LONG				m_lIndex;
	INT					m_nLastMarker;
	INT					m_nLastValue;

	HANDLE				m_hSharedEvent;
	HANDLE				m_hEvent;

	CEMSTime			m_timeDataBuffer;
	CEMSTime			m_timeWorkBuffer;
	CEMSMutex			m_mutex;

	unsigned char*      m_pMainBuff;
	unsigned char*      m_pSharedBuff;

	CEMSGSDataBufMgr*       m_pBuffMgr;
	CEMSGSDataCollection*   m_pCollectionMgr;
};

#endif // INC_USBDTOBJ

