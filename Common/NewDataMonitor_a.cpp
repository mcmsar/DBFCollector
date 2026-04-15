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

	$Log:
	$
********************************************************************/

//! This file was originally named NewDataMonitor.cpp and was merged from 
//! one code stream (LUT600) to another (LUT 2.1.1).  The version in the
//! target code stream had been revised to change its behaviour.  In order 
//! to preserve compatibility, with code in the target stream a merge was 
//! not performed.  Instead, this class was renamed.

#include "newdatamonitor_a.h"
#include "emsexcpt.h"
#include "sqlbuilder.h"
#include "loghelper.h"

const long CEMSNewDataMonitorA::ms_clDefaultCheckPeriod = 10000; // 10 seconds
const long CEMSNewDataMonitorA::ms_clDefaultNotifyDelay = 60000; // 60 seconds
const ULONG CEMSNewDataMonitorA::ms_culShutdownTimeout = 5000;	// 5 seconds

CEMSNewDataMonitorA::CEMSNewDataMonitorA() : m_eRecType(EMSRT_UNKNOWN), m_ulCallee(0), m_ulCaller(0),
											m_hWndNoitfy(0), m_uiMessageID(0), 
											m_lCheckPeriod( ms_clDefaultCheckPeriod ),
											m_lNotificationDelay( ms_clDefaultNotifyDelay ),
											m_bIsRunning(false),
											m_eVersion( EMSDBVERSION_LEO_20 ),
											m_hNotifyEvent(0)
{
	m_timeLastRecord.intTime = 0;
}


CEMSNewDataMonitorA::CEMSNewDataMonitorA( const CEMSNewDataMonitorA& x ) : m_eRecType(x.m_eRecType), 
											m_ulCallee(x.m_ulCallee), m_ulCaller(x.m_ulCaller),
											m_hWndNoitfy(x.m_hWndNoitfy), m_uiMessageID(x.m_uiMessageID), 
											m_lCheckPeriod( x.m_lCheckPeriod ),
											m_lNotificationDelay( x.m_lNotificationDelay ),
											m_bIsRunning(false),
											m_eVersion( x.m_eVersion ),
											m_wszAdditionalCriteria( x.m_wszAdditionalCriteria ),
											m_hNotifyEvent( 0 ),
											m_wszTableName( x.m_wszTableName ),
											m_wszColumnName( x.m_wszColumnName ),
											m_wszEventName( x.m_wszEventName ),
											m_timeLastRecord( x.m_timeLastRecord ),
											m_oDALClient( x.m_oDALClient ),
											m_wszCon( x.m_wszCon )
											// Don't copy the SQL or event handle, they get created at thread start-up
{
}


CEMSNewDataMonitorA::~CEMSNewDataMonitorA()
{
}

void 
CEMSNewDataMonitorA::SetTable( const EMSRECORDTYPE ceRecType )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_eRecType = ceRecType;
}

void 
CEMSNewDataMonitorA::SetTable( const wchar_t* cwszTableName, const wchar_t* cwszTimeColumn )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_wszTableName = cwszTableName;
	m_wszColumnName = cwszTimeColumn;
}

void 
CEMSNewDataMonitorA::SetCalleeID( const ULONG culID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCallee = culID;
}

void 
CEMSNewDataMonitorA::SetCallerID( const ULONG culID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_ulCaller = culID;
}

void 
CEMSNewDataMonitorA::SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_hWndNoitfy = chWndNotify;
	m_uiMessageID = cuiMessageID;

}

void 
CEMSNewDataMonitorA::SetCallback( const wchar_t* cwszEventName )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	if( cwszEventName )
	{
		m_wszEventName = cwszEventName;

		m_hNotifyEvent = CreateEventW( 0, FALSE, FALSE, m_wszEventName.c_str() );

		if( 0 == m_hNotifyEvent )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}
	}
}

void 
CEMSNewDataMonitorA::SetCheckPeriod( const long clMilliSeconds )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_lCheckPeriod = clMilliSeconds;
}

void 
CEMSNewDataMonitorA::SetNotificationDelay( const long clMilliSeconds )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	m_lNotificationDelay = clMilliSeconds;
}

void 
CEMSNewDataMonitorA::SetDBConnection( const wchar_t* cwszCon )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_INITIALIZED ) 
	}

	if( cwszCon )
	{
		m_wszCon = cwszCon;
	}
}

void 
CEMSNewDataMonitorA::StartMonitor()
{
	m_timeLastRecord.intTime = 0;

	start();
}

void 
CEMSNewDataMonitorA::StopMonitor()
{
	SignalStop();

	bool bShutdownOkay = wait( ms_culShutdownTimeout );

	if( !bShutdownOkay )
		stop();		// Force the thread to stop.

	m_bIsRunning = false;
}

void 
CEMSNewDataMonitorA::run()
{
	try
	{
		CoInitialize(0);

		m_bIsRunning = true;

//		_BuildSQLStatement();

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
CEMSNewDataMonitorA::_Monitor()
{
	if( 0 != m_ulCaller )
		m_oDALClient.Init( m_ulCaller, m_ulCallee, 0 );

	m_oDALClient.SetDBConnection( m_wszCon.c_str() );

	bool bRetrievedOnce = false;

	do
	{
		try
		{
			EMSTIME timeLatest = _GetLatestTimestamp();

			// Is this the first time its been called.  If so, this is our baseline.
			if( !bRetrievedOnce )
			{
				// Update latest time since records may have appeared since.
				m_timeLastRecord = timeLatest;

				m_timeLastRecord.intTime--;

				if( 0 != m_hNotifyEvent )
				{
					SetEvent( m_hNotifyEvent );
				}
				else
				{
					PostMessage( m_hWndNoitfy, m_uiMessageID, 0, 0 );
				}

				bRetrievedOnce = true;

				// Use the delay here to allow the consumer to pick up data for the first
				// record before we overwrite the timestamp value.

				Sleep( m_lNotificationDelay );
			}
			else
			{
				if( timeLatest.intTime > m_timeLastRecord.intTime )
				{
					// There are new records now.
					// Wait delay period and then notify.
					Sleep( m_lNotificationDelay );

					// Update latest time since records may have appeared since.
					m_timeLastRecord = _GetLatestTimestamp();

					if( 0 != m_hNotifyEvent )
					{
						SetEvent( m_hNotifyEvent );
					}
					else
					{
						PostMessage( m_hWndNoitfy, m_uiMessageID, 0, 0 );
					}
				}
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
CEMSNewDataMonitorA::_GetLatestTimestamp()
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	try
	{
		timeRet = m_oDALClient.GetTimestamp( m_wszColumnName.c_str(), m_wszTableName.c_str(), 
									m_wszAdditionalCriteria.c_str()  );
	}
	catch( ... )
	{
		throw;
	}

	return timeRet;
}

void 
CEMSNewDataMonitorA::_BuildSQLStatement()
{
	m_wszSQLStmt.erase();

	CSQLBuilder oSQL;

	const short csColumns = 1;
	const wchar_t* cawszColumns[csColumns];

	if( m_wszColumnName.empty() )
	{
		cawszColumns[0] = cwszTimestamp;
	}
	else
	{
		cawszColumns[0] = m_wszColumnName.c_str();
	}

	oSQL.AddSelectColumns( csColumns, cawszColumns );
	oSQL.AddFrom();

	std::wstring wszTableName;
	if( !m_wszTableName.empty() )
	{
		wszTableName = m_wszTableName;
	}
	else
	{
		wszTableName = _GetTableName();
	}

	oSQL.AddTable( wszTableName.c_str() );

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
CEMSNewDataMonitorA::_GetTableName()
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