/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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
	 1    Common    1.0         29/01/2005 11:23:36 AM Jason Bass      
	$
********************************************************************/

//! This file was originally named NewDataMonitor.h and was merged from 
//! one code stream (LUT600) to another (LUT 2.1.1).  The version in the
//! target code stream had been revised to change its behaviour.  In order 
//! to preserve compatibility, with code in the target stream a merge was 
//! not performed.  Instead, this class was renamed.

#ifndef __NEW_DATA_MONITOR_A_H__
#define __NEW_DATA_MONITOR_A_H__

#include "emsthread.h"
#include "emsdbfieldnames.h"
#include "datamonitordalclient.h"
#include <string>

//! @fn CEMSNewDataMonitorA
//! This class can be used to monitor and receive notifications when new records appear
//! in a database table.
class CEMSNewDataMonitorA : public CEMSThread
{
	public:
		CEMSNewDataMonitorA();
		CEMSNewDataMonitorA( const CEMSNewDataMonitorA& x );
		virtual ~CEMSNewDataMonitorA();

		//! @fn void SetTable( const EMSRECORDTYPE ceRecType )
		//! Specify the table to monitor for new records.
		void SetTable( const EMSRECORDTYPE ceRecType );

		//! @fn void SetTable( const wchar_t* cwszTableName, const wchar_t* cwszTimeColumn )
		//! Specify the table and time column name to monitor for new records,
		void SetTable( const wchar_t* cwszTableName, const wchar_t* cwszTimeColumn );

		//! @fn void void SetCalleeID( const ULONG culID )
		//! Used when connecting to datasource, identifies the source.
		void SetCalleeID( const ULONG culID );

		//! @fn void SetCallerID( const ULONG culID )
		//! Used when connecting to datasource, identifies the caller.
		void SetCallerID( const ULONG culID );

		//! @fn void void SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
		//! Used to specify the window and message ID to send notifications back to.
		void SetCallback( const HWND chWndNotify, const UINT cuiMessageID );

		//! @fn void SetCallback( const wchar_t* cwszEventName )
		//! Used to specify an event name to send notifications back to.
		void SetCallback( const wchar_t* cwszEventName );

		//! @fn void SetCheckPeriod( const long clMilliSeconds )
		//! Specifies the period between queries to the database for new data, in milliseconds.
		void SetCheckPeriod( const long clMilliSeconds );

		//! @fn void SetNotificationDelay( const long clMilliSeconds )
		//! Specifies a delay between when the monitor notices new records in the database and
		//! when it notifies the callback object.  If a batch of records are being added to the
		//! database, this delay can allow all records to be added before notification is sent.
		void SetNotificationDelay( const long clMilliSeconds );

		//! @fn void StartMonitor()
		//! Start the monitor.
		void StartMonitor();
		
		//! @fn void StopMonitor()
		//! Stop the monitor.
		void StopMonitor();

		//! @fn bool IsRunning()
		//! Test whether the monitor is running.
		bool IsRunning() { return m_bIsRunning; }

		//! @fn SetAdditionalCriteria( const wchar_t* cwszWhereClause )
		//! Specify any additional criteria in the form of an SQL where clause.
		void SetAdditionalCriteria( const wchar_t* cwszWhereClause ) { m_wszAdditionalCriteria = cwszWhereClause; }

		//! @fn EMSTIME GetLatestTimestamp()
		//! Get the value of the latest timestamp measured by the monitor.
		EMSTIME GetLatestTimestamp() { return m_timeLastRecord; }

		//! @fn void SetDBConnection( const wchar_t* cwszCon )
		//! Set the database connection string to use.
		void SetDBConnection( const wchar_t* cwszCon );


	private:
		void _BuildSQLStatement();
		std::wstring _GetTableName();
		void _Monitor();
		EMSTIME _GetLatestTimestamp();

	protected:
		void run();

	private:
		EMSRECORDTYPE m_eRecType;
		EMSDBVERSION m_eVersion;
		ULONG m_ulCallee;
		ULONG m_ulCaller;
		HWND m_hWndNoitfy;
		UINT m_uiMessageID;
		long m_lCheckPeriod;
		long m_lNotificationDelay;
		EMSTIME m_timeLastRecord;
		bool m_bIsRunning;
		std::wstring m_wszSQLStmt;
		CEMSDataMonitorDALClient	m_oDALClient;
		std::wstring m_wszAdditionalCriteria;
		std::wstring m_wszTableName;
		std::wstring m_wszColumnName;
		std::wstring m_wszEventName;
		HANDLE m_hNotifyEvent;
		std::wstring m_wszCon;

		static const long ms_clDefaultCheckPeriod;
		static const long ms_clDefaultNotifyDelay;
		static const ULONG ms_culShutdownTimeout;

};

#endif