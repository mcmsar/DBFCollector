#include "PKSOURCERETRY.h"
#include "iconfigmanager.h"
#include "EMSCLOCK.h"
#include "EMSEXCPT.h"
#include <stdio.h>
#include "pipelineretry.h"
#include "ccbootstrap.h"
#include "ConfigManagerProxyClsid.h"

#ifdef TRACE
#include "PKSOURCEMSGS.h"
#endif


CEMSRetryPacketSource::CEMSRetryPacketSource( BYTE cType, INT nMaxLength ) : m_rSource( *new CEMSPacketSource( cType, nMaxLength ) )
{
    EMS_RESULT hr = EMS_OK;
    EMSVARITYPE configItem;
    LPEMSCONFIGURATIONMANAGER lpConfig = NULL;
    ULONG ulLutID;

    m_lRefCount = 1L;
    m_ulRetryTime = 0;

	if( CCBootstrap::IsMEOSystem() )
	{
		hr = CoCreateInstance( CLSID_EMSConfigProxy, 0, CLSCTX_ALL, 
										IID_IEMSConfigurationManager, (void**) &lpConfig);
		THROW_IF_FAILED(hr);
		m_ulRetryTime = 3000; // default value in the CM config.
		THROW_IF_FAILED(lpConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyLutiD, &configItem ));
		ulLutID = configItem.uiVal;
	}
	else
	{
		THROW_IF_FAILED(::CoCreateInstance( CLSID_EMSConfigurationManager, NULL, CLSCTX_ALL, IID_IEMSConfigurationManager, (LPVOID*)&lpConfig ));
		THROW_IF_FAILED(lpConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyTimeOut, &configItem ));
		m_ulRetryTime = configItem.uiVal;
		THROW_IF_FAILED(lpConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyLutiD, &configItem ));
		ulLutID = configItem.uiVal;
	}
#ifdef TRACE
    m_pLogger = NULL;
    m_byType = cType;
    THROW_IF_FAILED(::CoCreateInstance( CLSID_EMSLeo600Logger, NULL, CLSCTX_ALL, IID_IEMSLeo600Logger, (LPVOID*)&m_pLogger ));
    THROW_IF_FAILED(m_pLogger->Initialize( ulLutID, 0 ));
#endif

    lpConfig->Release();
}

CEMSRetryPacketSource::CEMSRetryPacketSource(   BYTE     cType, 
                                                INT      nMaxLength, 
                                                ULONG    ulRetryTime ) :
   m_rSource( *new CEMSPacketSource( cType, nMaxLength ) ),
   m_lRefCount( 1L ),
   m_ulRetryTime( ulRetryTime )
{
}

CEMSRetryPacketSource::~CEMSRetryPacketSource()
{
    m_rSource.Release();
#ifdef TRACE
    m_pLogger->Release();
#endif
}

STDMETHODIMP_(ULONG) CEMSRetryPacketSource::AddRef()
{
	return InterlockedIncrement( &m_lRefCount );
}

STDMETHODIMP_(ULONG) CEMSRetryPacketSource::Release()
{
	LONG lRef = InterlockedDecrement( &m_lRefCount );

	if ( lRef == 0 )
	{
		delete this;
	}

	return (ULONG)lRef;
}

STDMETHODIMP CEMSRetryPacketSource::QueryInterface(REFIID riid, LPVOID *lppObj)
{
    EMS_RESULT hr = E_NOINTERFACE;

    if ( lppObj )
    {
        LPUNKNOWN lpUnknown = 0;

        *lppObj = 0;

        if ( riid == IID_IUnknown || riid == IID_IEMSDataSource )
        {
            lpUnknown = (IUnknown *)(LPEMSDATASOURCE)this;
        }

        if ( lpUnknown )
        {
            lpUnknown->AddRef();

            hr = S_OK;
        }
        *lppObj = lpUnknown;
    }
    else
        hr = E_INVALIDARG;

    return hr;
}

STDMETHODIMP CEMSRetryPacketSource::SetType( BYTE cDataType )
{
    return m_rSource.SetType( cDataType );
}

STDMETHODIMP CEMSRetryPacketSource::GetType( BYTE __RPC_FAR *lpcDataType )
{
    return m_rSource.GetType( lpcDataType );
}

STDMETHODIMP CEMSRetryPacketSource::SetMaxLength( INT nMaxLength )
{
    return m_rSource.SetMaxLength( nMaxLength );
}

STDMETHODIMP CEMSRetryPacketSource::GetMaxLength( INT __RPC_FAR *lpnMaxLength )
{
    return m_rSource.GetMaxLength( lpnMaxLength );
}

STDMETHODIMP CEMSRetryPacketSource::SetStream( LPEMSPACKETSTREAM lpStream )
{
    return m_rSource.SetStream( lpStream );
}

STDMETHODIMP CEMSRetryPacketSource::GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream )
{
    return m_rSource.GetStream( lplpStream );
}

STDMETHODIMP CEMSRetryPacketSource::Write(	const BYTE __RPC_FAR *pv,	ULONG cb, ULONG __RPC_FAR *pcbWritten )
{
    BOOL bRetry = TRUE;
    CEMSTime startTime = CEMSSystemClock::GetTime();
    EMS_RESULT hr = EMS_OK;
    EMSTIME curTime;
#ifdef TRACE
    ULONG ulNumRetry = 0;
#endif

    do
    {
        hr = m_rSource.Write( pv, cb, pcbWritten );
        switch( hr )
        {
        case EMS_STREAM_OVERFLOW:
        case EMS_PIPE_OVERFLOW:
            curTime = CEMSSystemClock::GetTime();
            if( startTime.NanosecondsDifferent( curTime ) / 1000000 > m_ulRetryTime )
            {
                bRetry = FALSE;
            }
            else
            {
                // let another process run
                Sleep(10);
#ifdef TRACE
                ulNumRetry++;
                {
                    char szTemp[128];
                    sprintf( szTemp, "Channel: %d Retry: %d.", m_byType, ulNumRetry );
                    m_pLogger->ReportLogEventA( EMSLogMsgTrace, EMS_PKSRC_RETRY, szTemp, strlen(szTemp) );
                }
#endif
            }
            break;
        default:
            bRetry = FALSE;
            break;
        }
    }
    while( TRUE == bRetry );

    return hr;
}
