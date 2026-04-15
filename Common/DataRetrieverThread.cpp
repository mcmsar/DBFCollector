/*********************************************************************
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

	$Log$
********************************************************************/

#include "dataretrieverthread.h"
#include "recordmetadata.h"
#include "emsexcpt.h"
#include "sqlbuilder.h"
#include "loghelper.h"

const ULONG CEMSDataRetrieverThread::ms_culCheckPeriod = 1; // 1 millisecond
const ULONG CEMSDataRetrieverThread::ms_culShutdownTimeout = 5000;	// 5 seconds

CEMSDataRetrieverThread::CEMSDataRetrieverThread() : m_ulCallee(0), m_ulCaller(0), m_hWndNoitfy(0),
													m_uiMessageID(0), m_bIsRunning(false), m_ulChunksize(0),
													m_bMeta(false), m_pMeta(0),
													m_ulMaxRecords(0)
{
}


CEMSDataRetrieverThread::CEMSDataRetrieverThread( const CEMSDataRetrieverThread& x ) : m_ulCallee( x.m_ulCallee ),
								m_ulCaller( x.m_ulCaller ), m_hWndNoitfy( x.m_hWndNoitfy ), m_uiMessageID( x.m_uiMessageID ),
								m_bIsRunning(false), m_ulChunksize( x.m_ulChunksize ), m_bMeta( x.m_bMeta ), 
								m_pMeta(x.m_pMeta), m_wszSQL( x.m_wszSQL ),
								m_ulMaxRecords( x.m_ulMaxRecords )
{
	if( m_pMeta )
	{
		m_pMeta->AddRef();
	}
}


CEMSDataRetrieverThread::~CEMSDataRetrieverThread()
{
	_ClearMeta();
}

void 
CEMSDataRetrieverThread::SetSQL( const wchar_t* cwszSQL )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_wszSQL = cwszSQL;
}

void 
CEMSDataRetrieverThread::SetCalleeID( const ULONG culID )
{ 
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCallee = culID; 
}

void CEMSDataRetrieverThread::SetCallerID( const ULONG culID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCaller = culID; 
}

void 
CEMSDataRetrieverThread::SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_hWndNoitfy = chWndNotify;
	m_uiMessageID = cuiMessageID;

}

void 
CEMSDataRetrieverThread::SetChunkSize( const ULONG culSize ) 
{ 
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulChunksize = culSize; 
}

void 
CEMSDataRetrieverThread::SetMetaData( const bool cbMeta )
{ 
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_bMeta = cbMeta; 
}

void 
CEMSDataRetrieverThread::SetMaxRecords( const ULONG culMaxRecords )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulMaxRecords = culMaxRecords; 
}

void 
CEMSDataRetrieverThread::RetrieveData()
{
	start();
}

void 
CEMSDataRetrieverThread::StopRetrieval()
{
	SignalStop();

	bool bShutdownOkay = wait( ms_culShutdownTimeout );

	if( !bShutdownOkay )
		stop();		// Force the thread to stop.

	m_bIsRunning = false;
}

CEMSRawDataRecord* 
CEMSDataRetrieverThread::GetNextRecord()
{
	return m_queueData.Pop();
}

CEMSRecordMetaData*
CEMSDataRetrieverThread::GetMetaData()
{
	CEMSRecordMetaData* pRet = 0;

	try
	{
		m_csMeta.Enter();

		pRet = m_pMeta;

		if( pRet )
			pRet->AddRef();

		m_csMeta.Leave();

	}
	catch( ... )
	{
		m_csMeta.Leave();

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSDataRetrieverThread::run()
{
	try
	{
		CoInitialize(0);

		m_bIsRunning = true;

		_GetData();

	}
	catch( ... )
	{
		// This is an independent thread with no exception handler.
		// Let it shutdown.
	}

	m_bIsRunning = false;

	CoUninitialize();
}

void 
CEMSDataRetrieverThread::_GetData()
{
	m_oGatewayHelper.SetCallerID( m_ulCaller );

	bool bRetrievedOnce = false;

	EMSDALCACHEID cacheID = INITIALDALCACHEID;

	ULONG ulTotalRecordsRetrieved = 0;

	do
	{
		bool bOverflow = false;
		ULONG ulTotalRecords = 0;
		ULONG ulRecordSize = 0;
		ULONG ulFields = 0;
		EMSFIELDDESCRIPTOR* aFieldDesc = 0;
		ULONG ulDataSize = 0;
		unsigned char* abyData = 0;

		try
		{
			m_oGatewayHelper.GetData( m_ulCallee, &cacheID, 
									m_ulMaxRecords < m_ulChunksize ? m_ulMaxRecords : m_ulChunksize, 
									bRetrievedOnce ? false : m_bMeta, 0, 
									m_wszSQL.c_str(), &bOverflow, &ulTotalRecords, &ulRecordSize, 
									&ulFields, &aFieldDesc, &ulDataSize, &abyData );

			bRetrievedOnce = true;

			if( m_bMeta )
			{
				_SaveMetaData( ulFields, aFieldDesc );

				CoTaskMemFree( aFieldDesc );
				aFieldDesc = 0;
			}

			if( (ulDataSize > 0) && abyData && (ulRecordSize > 0) )
			{
				_SaveData( ulDataSize, ulRecordSize, abyData );

				_SignalData();

				ulTotalRecordsRetrieved += ( ulDataSize / ulRecordSize );
			}

			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		}
		catch( ... )
		{
			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

			if( aFieldDesc )
			{
				CoTaskMemFree( aFieldDesc );
				aFieldDesc = 0;
			}

			throw;
		}
		
	} while( !WaitForStop(ms_culCheckPeriod) && 
						(NULLDALCACHEID != cacheID) && 
						( ulTotalRecordsRetrieved < m_ulMaxRecords ) );	// This max is approximate.
}

void 
CEMSDataRetrieverThread::_SaveMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFieldDesc )
{
	try
	{
		m_csMeta.Enter();

		_ClearMeta();

		if( (culFields > 0) && caFieldDesc )
		{
			m_pMeta = new CEMSRecordMetaData;

			if( !m_pMeta )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			m_pMeta->Set( culFields, caFieldDesc );
		}

		m_csMeta.Leave();
	}
	catch( ... )
	{
		m_csMeta.Leave();

		throw;
	}
}

void 
CEMSDataRetrieverThread::_SaveData( const ULONG culDataSize, const ULONG culRecordSize, 
								   const unsigned char* cabyData )
{
	CEMSRawDataRecord* pRec = 0;

	try
	{
		if( (culDataSize > 0) && (culRecordSize > 0) && cabyData )
		{
			ULONG ulRecords = culDataSize / culRecordSize;

			const unsigned char* cabyCurrentRec = cabyData;

			for( ULONG l = 0; l < ulRecords; l++ )
			{
				pRec = new CEMSRawDataRecord( culRecordSize, cabyCurrentRec + l*culRecordSize );

				if( !pRec )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				m_queueData.Push( pRec );

				pRec->Release();
				pRec = 0;
			}
		}
	}
	catch( ... )
	{
		if( pRec )
		{
			pRec->Release();
			pRec = 0;
		}

		throw;
	}
}

void 
CEMSDataRetrieverThread::_ClearMeta()
{
	try
	{
		m_csMeta.Enter();

		if( m_pMeta )
		{
			m_pMeta->Release();
			m_pMeta = 0;
		}

		m_csMeta.Leave();
	}
	catch( ... )
	{
		m_csMeta.Leave();

		throw;
	}
}

void 
CEMSDataRetrieverThread::_SignalData()
{
	if( m_hWndNoitfy && m_uiMessageID )
	{
		PostMessage( m_hWndNoitfy, m_uiMessageID, 0, 0 );
	}
}