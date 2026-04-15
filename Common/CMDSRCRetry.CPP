/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "cmdsrcretry.h"
#include "pipelineretry.h"
#include "iconfigmanager.h"
#include "emstime.h"
#include "emsclock.h"
#include "ccbootstrap.h"
#include "ConfigManagerProxyClsid.h"

CEMSCommandSourceRetry::CEMSCommandSourceRetry( BYTE cCmdType, INT nMaxLength ) : 
													CEMSCommandSource( cCmdType, nMaxLength )
{
	EMS_RESULT hr = EMS_OK;
    EMSVARITYPE configItem;
    LPEMSCONFIGURATIONMANAGER pConfig = NULL;
    ULONG ulLutID;

    m_ulRetryTime = 0;

	if( CCBootstrap::IsMEOSystem() )
	{
		hr = CoCreateInstance( CLSID_EMSConfigProxy, 0, CLSCTX_ALL, 
										IID_IEMSConfigurationManager, (void**) &pConfig);
		THROW_IF_FAILED(hr);
		m_ulRetryTime = 3000; // default value in the CM config.
		THROW_IF_FAILED(pConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyLutiD, &configItem ));
		ulLutID = configItem.uiVal;
	}
	else
	{
		THROW_IF_FAILED(::CoCreateInstance( CLSID_EMSConfigurationManager, NULL, CLSCTX_ALL, IID_IEMSConfigurationManager, (LPVOID*)&pConfig ));
		THROW_IF_FAILED(pConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyTimeOut, &configItem ));
		m_ulRetryTime = configItem.uiVal;
		THROW_IF_FAILED(pConfig->Get( L"PRO", c_pwcsNoGroupID, c_wszKeyLutiD, &configItem ));
		ulLutID = configItem.uiVal;
	}
#ifdef TRACE
    m_pLogger = NULL;
    m_byType = cType;
    THROW_IF_FAILED(::CoCreateInstance( CLSID_EMSLeo600Logger, NULL, CLSCTX_ALL, IID_IEMSLeo600Logger, (LPVOID*)&m_pLogger ));
    THROW_IF_FAILED(m_pLogger->Initialize( ulLutID, 0 ));
#endif

    pConfig->Release();
}

CEMSCommandSourceRetry::~CEMSCommandSourceRetry()
{
#ifdef TRACE
	if( m_pLogger )
	{
		m_pLogger->Release();
		m_pLogger = 0;
	}
#endif
}

STDMETHODIMP CEMSCommandSourceRetry::QueryInterface(REFIID riid, LPVOID *lppObj)
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
		else if ( riid == IID_IEMSCommandSource )
		{
  		lpUnknown = (IUnknown *)(LPEMSCOMMANDSOURCE)this;
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

STDMETHODIMP CEMSCommandSourceRetry::Write( BYTE cTo, const BYTE __RPC_FAR *pv,	ULONG cb, ULONG __RPC_FAR *pcbWritten )
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
		hr = CEMSCommandSource::Write( cTo, pv, cb, pcbWritten );
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


