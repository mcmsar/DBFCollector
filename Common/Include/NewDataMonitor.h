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

	$Log$
********************************************************************/

#ifndef __NEW_DATA_MONITOR_H__
#define __NEW_DATA_MONITOR_H__

#include "emsthread.h"
#include "emsdbfieldnames.h"
#include "gatewayhelper.h"
#include "ChangeMonitor.h" // EMSDATACHANGE, IEMSDataChangeSink
#include <string>

//! @fn CEMSNewDataMonitor
//! This class can be used to monitor and receive notifications when new records appear
//! in a database table.
class CEMSNewDataMonitor : public CEMSThread
{
	public:
		CEMSNewDataMonitor();
		CEMSNewDataMonitor( const CEMSNewDataMonitor& x );
		virtual ~CEMSNewDataMonitor();

		//! @fn void SetTable( const EMSRECORDTYPE ceRecType )
		//! Specify the table to monitor for new records.
		void SetTable( const EMSRECORDTYPE ceRecType );

		//! @fn void void SetCalleeID( const ULONG culID )
		//! Used when connecting to datasource, identifies the source.
		void SetCalleeID( const ULONG culID );

		//! @fn void SetCallerID( const ULONG culID )
		//! Used when connecting to datasource, identifies the caller.
		void SetCallerID( const ULONG culID );

		//! @fn void SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
		//! Used to specify the window and message ID to send notifications back to.
		void SetCallback( const HWND chWndNotify, const UINT cuiMessageID );

		//! @fn void SetCallback( IEMSDataChangeSink* pSink, const EMSDATACHANGE ceChange )
		//! Used to specify the sink to notify
		void SetCallback( IEMSDataChangeSink* pSink, const EMSDATACHANGE ceChange );

		//! @fn void SetCheckPeriod( const long clMilliSeconds )
		//! Specifies the period between queries to the database for new data, in milliseconds.
		void SetCheckPeriod( const long clMilliSeconds );

		//! @fn void SetNotificationDelay( const long clMilliSeconds )
		//! Specifies a delay between when the monitor notices new records in the database and
		//! when it notifies the callback object.  If a batch of records are being added to the
		//! database, this delay can allow all records to be added before notification is sent.
		void SetNotificationDelay( const long clMilliSeconds );

		//! @fn void SetReportOfflineOnline( const EMSDATACHANGE ceOfflineChange, const EMSDATACHANGE ceOnlineChange )
		//! Used to indicate that offline/online changes are to trigger a callback
		void SetReportOfflineAsChange( const EMSDATACHANGE ceOfflineChange, const EMSDATACHANGE ceOnlineChange );

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

	private:
		void _BuildSQLStatement();
		std::wstring _GetTableName();
		void _Monitor();
		EMSTIME _GetLatestTimestamp( bool& bOffline );

	protected:
		void run();

	private:
		EMSRECORDTYPE m_eRecType;
		EMSDBVERSION m_eVersion;
		ULONG m_ulCallee;
		ULONG m_ulCaller;
		HWND m_hWndNoitfy;
		UINT m_uiMessageID;
		EMSDATACHANGE m_eDataChange;
		IEMSDataChangeSink* m_pSink;
		long m_lCheckPeriod;
		long m_lNotificationDelay;
		EMSTIME m_timeLastRecord;
		bool m_bIsRunning;
		std::wstring m_wszSQLStmt;
		CEMSGatewayHelper m_oGatewayHelper;
		std::wstring m_wszAdditionalCriteria;
		EMSDATACHANGE m_eOfflineChange;
		EMSDATACHANGE m_eOnlineChange;
		bool m_bOffline;

		static const long ms_clDefaultCheckPeriod;
		static const long ms_clDefaultNotifyDelay;
		static const ULONG ms_culShutdownTimeout;

};

#endif