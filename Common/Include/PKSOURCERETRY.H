#ifndef __PKSOURCERETRY_H__
#define __PKSOURCERETRY_H__

#include "PKSOURCE.h"
#ifdef TRACE
#include "EMSLOGGR.h"
#endif

class CEMSRetryPacketSource : public IEMSDataSource
{
public:
	CEMSRetryPacketSource( BYTE cType = 0, INT nMaxLength = 0 );
	CEMSRetryPacketSource( BYTE cType, INT nMaxLength, ULONG ulRetryTime );

	/*********************************************************************
	*	IUnknown Methods
	*********************************************************************/
	STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef(void); 
	STDMETHODIMP_(ULONG) Release(void); 

	/*********************************************************************
	*	IEMSDataSource Methods
	*********************************************************************/

	STDMETHODIMP SetType( BYTE cDataType );
	STDMETHODIMP GetType( BYTE __RPC_FAR *lpcDataType );
	STDMETHODIMP GetMaxLength( INT __RPC_FAR *lpnMaxLength );
	STDMETHODIMP SetMaxLength( INT nMaxLength );
	STDMETHODIMP SetStream( LPEMSPACKETSTREAM lpStream );
	STDMETHODIMP GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream );

	/*********************************************************************
	*	
	*********************************************************************/
	STDMETHODIMP Write( const BYTE __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbWritten );

private: // methods
	virtual ~CEMSRetryPacketSource();

private: // data
    CEMSPacketSource    &m_rSource;
    volatile LONG       m_lRefCount;
    ULONG               m_ulRetryTime;      // in milliseconds
#ifdef TRACE
    BYTE                m_byType;
    LPEMSLOGGER         m_pLogger;
#endif

};

#endif
