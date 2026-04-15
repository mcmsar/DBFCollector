/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#include <afxwin.h>
#include "dataproxy.h"
#include "monitordatasink.h"

CEMSDataProxy::CEMSDataProxy() : m_ulRefreshPeriod( 1000 ), m_pDataSink(NULL), m_bIsRunning(false),
							m_pWnd(0), m_uiMessage(0), m_ulCallerID(0), m_ulCalleeID(0),
							m_ulChunkSize(0)
{
}

CEMSDataProxy::CEMSDataProxy( const CEMSDataProxy& x ) : m_ulRefreshPeriod( x.m_ulRefreshPeriod ),
										m_oDALHelper( x.m_oDALHelper ),
										m_pDataSink( x.m_pDataSink ),
										m_bIsRunning( false ),
										m_oException( x.m_oException ),
										m_pWnd( x.m_pWnd ),
										m_uiMessage( x.m_uiMessage ),
										m_ulCallerID( x.m_ulCallerID ), 
										m_ulCalleeID( x.m_ulCalleeID ),
										m_ulChunkSize( x.m_ulChunkSize )
{
}

CEMSDataProxy::~CEMSDataProxy()
{
	Stop();
}

void 
CEMSDataProxy::Start()
{
	if( !m_bIsRunning )
	{
		start();
	}
}

void 
CEMSDataProxy::Stop()
{
	if( m_bIsRunning )
	{
		SignalStop();

		if( !wait( 10000 ) )
			stop();
	}
}

void 
CEMSDataProxy::SetNewDataCallback( IEMSMonitorDataSink* pSink )
{
	m_pDataSink = pSink;
}

void 
CEMSDataProxy::SetNewDataCallback( CWnd* pWnd, const UINT cuiMessage )
{
	m_pWnd = pWnd;
	m_uiMessage = cuiMessage;
}

CEMSDataAccessHelper* 
CEMSDataProxy::_GetNewDataAccessHelper()
{
	CEMSDataAccessHelper* pRet = new CEMSDataAccessHelper;

	if( !pRet )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	pRet->Init( m_ulCallerID, m_ulCalleeID, m_ulChunkSize );

	return pRet;
}

void 
CEMSDataProxy::_SetRefreshPeriod( const ULONG culPeriod )
{
	// Don't allow a zero refresh period.  That means an infinite wait.
	if( culPeriod > 0 )
		m_ulRefreshPeriod = culPeriod;
}

void 
CEMSDataProxy::_Init( const ULONG culCallerID, const ULONG culCalleeID, const ULONG culChunkSize )
{
	m_ulCallerID = culCallerID;
	m_ulCalleeID = culCalleeID;
	m_ulChunkSize = culChunkSize;

	m_oDALHelper.Init( culCallerID, culCalleeID, culChunkSize );
}

void 
CEMSDataProxy::run()
{
	m_bIsRunning = true;

	bool bComInit = false;

	EMS_RESULT hr = CoInitialize(0);

	if( EMS_OK == hr )
	{
		bComInit = true;

		do 
		{
			try
			{
				if( _GetData() )
					_OnNewData();

				// Clear any cached exception.
				m_oException.Clear();
			}
			catch( CEMSException& e )
			{
				m_oException = e;
			}
			catch( ... )
			{
				m_oException.SetErrCode( EMS_UNKNOWN_ERROR );
			}
			
		} while( !WaitForStop( m_ulRefreshPeriod ) );
	}

	if( bComInit )
		CoUninitialize();

	m_bIsRunning = false;
}

void 
CEMSDataProxy::_OnNewData()
{
	if( m_pDataSink )
		m_pDataSink->OnData();

	if( m_pWnd )
		m_pWnd->PostMessage( m_uiMessage );
}