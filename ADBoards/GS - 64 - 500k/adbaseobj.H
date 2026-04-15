#ifndef INC_ADBASEOBJ 
#define INC_ADBASEOBJ

#include <stdio.h>		// DEBUG

#include "emsadboard.h"
#include "emserror.h"
#include "emstime.h"
#include "emsmutex.h"
#include "emsthread.h"

class CEMSADBoardBaseObject : public IEMSADBoard
{
public:
	CEMSADBoardBaseObject();

/*********************************************************************
*	IEMSADBoard Methods
*********************************************************************/
	HRESULT STDMETHODCALLTYPE Init(  DWORD dwBufferSize, DWORD dwSampleSize, DWORD dwSampleRate);
	HRESULT STDMETHODCALLTYPE Reset( void);
	HRESULT STDMETHODCALLTYPE Start( void);
	HRESULT STDMETHODCALLTYPE Stop( void);
	HRESULT STDMETHODCALLTYPE Pause( void);
	HRESULT STDMETHODCALLTYPE Continue( void);
	HRESULT STDMETHODCALLTYPE SetTransferBuffer( short __RPC_FAR *lpBuffer);
	HRESULT STDMETHODCALLTYPE LockBuffer( BOOL bWait);
	HRESULT STDMETHODCALLTYPE UnlockBuffer( void);
	HRESULT STDMETHODCALLTYPE GetEventHandle( DWORD __RPC_FAR *lphEvent);
	HRESULT STDMETHODCALLTYPE GetBlockCount( INT64 __RPC_FAR *lpi64Count);
	HRESULT STDMETHODCALLTYPE GetDropoutCount( INT64 __RPC_FAR *lpi64Count);
	HRESULT STDMETHODCALLTYPE SetDropoutCount( INT64 i64Count);
	HRESULT STDMETHODCALLTYPE GetBufferTime( EMSTIME __RPC_FAR *lpTime);

	HRESULT STDMETHODCALLTYPE SetEventNameA( unsigned char __RPC_FAR *lpszEventName );
	HRESULT STDMETHODCALLTYPE SetEventNameW( WCHAR __RPC_FAR *lpszEventName);

	HRESULT STDMETHODCALLTYPE GetVersionInfoA( WORD __RPC_FAR *lpwVersion,
            unsigned char __RPC_FAR *lpszModel,
            WORD wMax, WORD __RPC_FAR *lpwLength);
        
	HRESULT STDMETHODCALLTYPE GetVersionInfoW( WORD __RPC_FAR *lpwVersion,
            WCHAR __RPC_FAR *lpszModel,
            WORD wMax, WORD __RPC_FAR *lpwLength);

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);

protected: // methods
	inline INT64 _IncrBlockCount( void ) { return ++m_i64BlockCount; }
	inline INT64 _IncrDropoutCount( void ) { return ++m_i64DropoutCount; }
	inline DWORD _GetBufferSize( void ) { return m_dwBufferSize; }
	inline DWORD _GetSampleRate( void ) { return m_dwSampleRate; }
	inline DWORD _GetSampleSize( void ) { return m_dwSampleSize; }
	inline short *_GetTransferBuffer( void ) { return m_lpnTransferBuffer; }
	bool _SetEvent( void );

	virtual ~CEMSADBoardBaseObject();

private: // methods
	HANDLE _CreateEvent( LPCTSTR lpcszSignalName );

private: // data
	volatile LONG  	m_lRefCount;

	bool				m_bInitialized;
	bool				m_bStarted;
	bool				m_bRun;
	HANDLE				m_hEvent;
	CEMSMutex			m_mutex;
	short				*m_lpnTransferBuffer;
	DWORD				m_dwSampleSize;
	DWORD				m_dwBufferSize;
	DWORD				m_dwSampleRate;
	INT64				m_i64BlockCount;
	INT64				m_i64DropoutCount;
	CEMSTime			m_timeStarted;
	CEMSTime			m_timeStopped;
	CEMSTime			m_timeDataBuffer;
	CEMSTime			m_timeWorkBuffer;
};

#endif // INC_ADBASEOBJ

