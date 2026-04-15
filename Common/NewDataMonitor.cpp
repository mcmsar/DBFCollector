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

#include "ChangeMonitor.h"
#include "newdatamonitor.h"
#include "emsexcpt.h"
#include "sqlbuilder.h"
#include "loghelper.h"
#include "MTLMsgs.h"

const long CEMSNewDataMonitor::ms_clDefaultCheckPeriod = 10000; // 10 seconds
const long CEMSNewDataMonitor::ms_clDefaultNotifyDelay = 60000; // 60 seconds
const ULONG CEMSNewDataMonitor::ms_culShutdownTimeout = 5000;	// 5 seconds

CEMSNewDataMonitor::CEMSNewDataMonitor() : m_eRecType(EMSRT_UNKNOWN), m_ulCallee(0), m_ulCaller(0),
											m_hWndNoitfy(0), m_uiMessageID(0), 
											m_pSink(NULL), m_eDataChange(EMSDATACHANGE_UNKNOWN),
											m_lCheckPeriod( ms_clDefaultCheckPeriod ),
											m_lNotificationDelay( ms_clDefaultNotifyDelay ),
											m_bIsRunning(false),
											m_eVersion( EMSDBVERSION_LEO_20 ),
											m_eOfflineChange(EMSDATACHANGE_UNKNOWN),
											m_eOnlineChange(EMSDATACHANGE_UNKNOWN),
											m_bOffline(false)
{
	m_timeLastRecord.intTime = 0;
}


CEMSNewDataMonitor::CEMSNewDataMonitor( const CEMSNewDataMonitor& x ) : m_eRecType(x.m_eRecType), 
											m_ulCallee(x.m_ulCallee), m_ulCaller(x.m_ulCaller),
											m_hWndNoitfy(x.m_hWndNoitfy), m_uiMessageID(x.m_uiMessageID), 
											m_pSink(x.m_pSink), m_eDataChange(x.m_eDataChange),
											m_lCheckPeriod( x.m_lCheckPeriod ),
											m_lNotificationDelay( x.m_lNotificationDelay ),
											m_bIsRunning(false),
											m_eVersion( x.m_eVersion ),
											m_eOfflineChange(x.m_eOfflineChange),
											m_eOnlineChange(x.m_eOnlineChange),
											m_bOffline(false),
											m_wszAdditionalCriteria( x.m_wszAdditionalCriteria )
											// Don't copy the SQL, it gets created a thread start-up
{
	m_timeLastRecord.intTime = 0;
	if ( m_pSink )
	{
		m_pSink->AddRef();
	}
}


CEMSNewDataMonitor::~CEMSNewDataMonitor()
{
	if ( m_pSink )
	{
		m_pSink->Release();
	}
}

void 
CEMSNewDataMonitor::SetTable( const EMSRECORDTYPE ceRecType )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_eRecType = ceRecType;
}

void 
CEMSNewDataMonitor::SetCalleeID( const ULONG culID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCallee = culID;
}

void 
CEMSNewDataMonitor::SetCallerID( const ULONG culID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCaller = culID;
}

void 
CEMSNewDataMonitor::SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_hWndNoitfy = chWndNotify;
	m_uiMessageID = cuiMessageID;

}

void 
CEMSNewDataMonitor::SetCallback( IEMSDataChangeSink* pSink, const EMSDATACHANGE ceChange )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_pSink = pSink;
	m_eDataChange = ceChange;
	if ( pSink )
	{
		pSink->AddRef();
	}
}


void 
CEMSNewDataMonitor::SetCheckPeriod( const long clMilliSeconds )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_lCheckPeriod = clMilliSeconds;
}

void 
CEMSNewDataMonitor::SetNotificationDelay( const long clMilliSeconds )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_lNotificationDelay = clMilliSeconds;
}

void 
CEMSNewDataMonitor::SetReportOfflineAsChange( const EMSDATACHANGE ceOfflineChange, const EMSDATACHANGE ceOnlineChange )
{
	m_eOfflineChange = ceOfflineChange;
	m_eOnlineChange = ceOnlineChange;
}

void 
CEMSNewDataMonitor::StartMonitor()
{
	m_timeLastRecord.intTime = 0;

	start();
}

void 
CEMSNewDataMonitor::StopMonitor()
{
	SignalStop();

	bool bShutdownOkay = wait( ms_culShutdownTimeout );

	if( !bShutdownOkay )
		stop();		// Force the thread to stop.

	m_bIsRunning = false;
}

void 
CEMSNewDataMonitor::run()
{
	try
	{
		CoInitialize(0);

		m_bIsRunning = true;

		_BuildSQLStatement();

		_Monitor();
	}
	catch( ... )
	{
		// This is an independent thread with no exception handler.
		// Let it shutdown.
	}

	CoUninitialize();
}

void 
CEMSNewDataMonitor::_Monitor()
{
	m_oGatewayHelper.SetCallerID( m_ulCaller );

	bool bRetrievedOnce = false;

	do
	{
		try
		{
			// Make sure reset to false on each pass through the loop
			bool bChanged = false;
			bool bOffline = false;

			EMSTIME timeLatest = _GetLatestTimestamp( bOffline );
			EMSDATACHANGE eChange = m_eDataChange;
			

			// Is this the first time its been called.  If so, this is our baseline.
			if( !bRetrievedOnce && !bOffline )
			{
				m_timeLastRecord = timeLatest;

				bRetrievedOnce = true;
			}
			else
			{
				if ( bOffline )
				{
					if ( !m_bOffline && m_eOfflineChange != EMSDATACHANGE_UNKNOWN )
					{
						// Only report on initial transition
						// AND only if asked to
						bChanged = true;
						eChange = m_eOfflineChange;
					}
				}
				else if( timeLatest.intTime > m_timeLastRecord.intTime )
				{
					// There are new records now.
					// Wait delay period and then notify.
					Sleep( m_lNotificationDelay );

					// Update latest time since records may have appeared since
					timeLatest = _GetLatestTimestamp( bOffline );
					if ( !bOffline ) 
					{
						bChanged = true;
						m_timeLastRecord = timeLatest;
					}
					else if ( m_eOfflineChange != EMSDATACHANGE_UNKNOWN )
					{
						bChanged = true;
						eChange = m_eOfflineChange;
					}

				}
				else if ( m_bOffline && m_eOnlineChange != EMSDATACHANGE_UNKNOWN )
				{
					// Only report on initial transition
					// AND only if asked to
					bChanged = true;
					eChange = m_eOnlineChange;
				}

				if ( bChanged )
				{
					if ( m_hWndNoitfy )
					{
						PostMessage( m_hWndNoitfy, m_uiMessageID, 0, 0 );
					}
					if ( m_pSink )
					{
						m_pSink->OnChange( m_ulCallee, eChange, 0, NULL );
					}
				}
				// for next time through
				m_bOffline = bOffline;
			}
		}
		catch( CEMSException& e )
		{
			// Log the exception and continue.  Don't want to kick out of this thread
			// if its possible to continue.
			CEMSLogHelper::LogException( e, false );
		}
		
	} while( !WaitForStop(m_lCheckPeriod) );
}

EMSTIME 
CEMSNewDataMonitor::_GetLatestTimestamp( bool& bOffline )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	EMSDALCACHEID cacheID = DONTCACHE;
	const ULONG culMaxRecords = 1;
	bool bOverflow = false;
	ULONG ulTotalRecords = 0;
	ULONG ulRecordSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFieldDesc = 0;
	ULONG ulDataSize = 0;
	unsigned char* abyData = 0;

	try
	{
		bOffline = false;

		m_oGatewayHelper.GetData( m_ulCallee, &cacheID, culMaxRecords, false, 0, m_wszSQLStmt.c_str(),
								&bOverflow, &ulTotalRecords, &ulRecordSize, &ulFields, &aFieldDesc, 
								&ulDataSize, &abyData );

		if( ( sizeof(INT64) == ulDataSize ) && abyData )
		{
			memcpy( &timeRet.intTime, abyData, sizeof(INT64) );
		}

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
	}
	catch( CEMSException& e )
	{
		// There won't be any data to cleanup since the only method that 
		// would allocate memory is the one that would
		// have thrown this exception
		if ( EMS_MTL_SOAP_TCP_ERROR == e.GetErrCode() )
		{
			bOffline = true;
		}
		else
		{
			throw;
		}
	}
	catch( HRESULT hr )
	{
		// There won't be any data to cleanup since the only method that 
		// would allocate memory is the one that would
		// have thrown this exception
		if ( EMS_MTL_SOAP_TCP_ERROR == hr )
		{
			bOffline = true;
		}
		else
		{
			throw;
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
	return timeRet;
}

void 
CEMSNewDataMonitor::_BuildSQLStatement()
{
	m_wszSQLStmt.erase();

	CSQLBuilder oSQL;

	const short csColumns = 1;
	const wchar_t* cawszColumns[] = { cwszTimestamp };

	oSQL.AddSelectColumns( csColumns, cawszColumns );
	oSQL.AddFrom();
	oSQL.AddTable( _GetTableName().c_str() );

	if( !m_wszAdditionalCriteria.empty() )
	{
		oSQL.AddWhere();

		oSQL.OpenParenth();

		oSQL += m_wszAdditionalCriteria.c_str();

		oSQL.CloseParenth();
	}

	oSQL.AddOrderBy();
	oSQL += cwszTimestamp;
	oSQL.AddDescending();

	m_wszSQLStmt = oSQL;

}

std::wstring 
CEMSNewDataMonitor::_GetTableName()
{
	std::wstring wszRet;

	bool bFound = false;

	int i = 0;

	while( !bFound && ( s_caDataTypeTableMapping[i].eRecType != EMSRT_UNKNOWN ) )
	{
		if( (s_caDataTypeTableMapping[i].eRecType == m_eRecType) && 
			( s_caDataTypeTableMapping[i].version == m_eVersion ) )
		{
			bFound = true;
			wszRet = s_caDataTypeTableMapping[i].wszTableName;
		}

		i++;
	}

	return wszRet;
}