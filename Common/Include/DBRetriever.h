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

#ifndef __DB_RETRIEVER_H__
#define __DB_RETRIEVER_H__

#include "emspipe.h"
#include "emsthread.h"
#include "dal.h"
#include "criticalsection.h"
#include "dbretrieverdalclient.h"
#include <string>
#include "aobjbase.h"

class CEMSQueueMemoryStream;
class CEMSNewDataMonitorA;
class CEMSStreamDataChannel;

//! @class CEMSDBRetriever
//! This class executes a query, and stores the data in a local memory stream
//! so that a caller can access the data.  It uses an event to signal the 
//! availability of new data.
class CEMSDBRetriever : public CEMSThread, public CApiObjBase
{
	public:
		CEMSDBRetriever();
		CEMSDBRetriever( const CEMSDBRetriever& x );
		~CEMSDBRetriever();

		//! @fn void SetRoute( const wchar_t* cwszRoute )
		//! Set the name of the route to use for remote connections.
		void SetRoute( const wchar_t* cwszRoute );

		//! @fn void SetSrcDestID( const ULONG culSrcID, const ULONG culDestID )
		//! Set the source and destination identifiers to use for remote connections.
		void SetSrcDestID( const ULONG culSrcID, const ULONG culDestID );

		//! @fn void SetSQL( const wchar_t* cwszSQL )
		//! Set the SQL statement to execute.
		void SetSQL( const wchar_t* cwszSQL );

		//! @fn void SetActive( const wchar_t* cwszSourceTable, const wchar_t* cwszSourceColumn, const wchar_t* cwszCriteria, const ULONG culTestPeriod )
		//! Set active retrieveal properties.  
		//!	@param const wchar_t* cwszSourceTable 
		//! Specifies the table to monitor for new data.
		//! @param const wchar_t* cwszSourceColumn
		//! Specifies the time field to monitor for new data.
		//! @param const wchar_t* cwszCriteria
		//! Specifes any additional criteria to apply when checking for new data.  This is a where clause, but does not include the WHERE statement.
		//! @param const ULONG culTestPeriod
		//! Specifies the number of milliseconds between checks for new data.
		void SetActive( const wchar_t* cwszSourceTable, const wchar_t* cwszSourceColumn,
						const wchar_t* cwszCriteria, const ULONG culTestPeriod );

		//! @fn IEMSSeqStream* GetStream()
		//! Retrieve a stream pointer to the query results.
		IEMSSeqStream* GetStream();

		//! @fn bool IsMoreData()
		//! When the caller is calling the Read method on the IEMSSeqStream pointer, 
		//! an EOF may be encountered before all data is actually retrieved.  This may be a
		//! result of latency in the transfer of data from the database into the local cache.
		//! This method should be used to test whether more data is expected.
		bool IsMoreData();

		//! @fn void SetEventName( const wchar_t* cwszEventName )
		//! Specify the name of the event to use when signalling the availability of new
		//! data.
		void SetEventName( const wchar_t* cwszEventName );

		//! @fn void SetDBConnection( const wchar_t* cwszConn )
		//! Set the database connection string to use.
		void SetDBConnection( const wchar_t* cwszConn );

		//! @fn void SetChunkSize( const ULONG culSize )
		//! Set the number of records to retrieve in one call to the DAL.
		void SetChunkSize( const ULONG culSize );

		//! @fn void Stop()
		//! Stop the retriever.
		void Stop();

		//! @fn EMS_RESULT GetRuntimeError()
		//! Test for any errors that occur during runtime.
		EMS_RESULT GetRuntimeError();

		//! @fn bool IsRunning()
		//! Used to determine whether the retrieval thread is running.
		bool IsRunning() { return m_bRunning; }

		//! @fn void SetMaxBufferSize( const ULONG culMaxBufferSize )
		//! Set the maximum allowable size of the local results buffer.
		//! Database results are written to a queue of bytes upon receipt from the
		//! database.  The results are pulled from the queue by the consumer of the resource.
		//! This value restricts the size of the queue in case the consumer does not pull
		//! records fast enough.
		void SetMaxBufferSize( const ULONG culMaxBufferSize ) { if( culMaxBufferSize > 0 ) m_ulMaxBufferSize = culMaxBufferSize; }

		//! @fn void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
		//! Retrieve meta data describing the records held in the resource.
		void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields );

		//! Provide a pointer to a data channel onto which data will be broadcast when it comes
		//! available.
		void SetCallback( CEMSStreamDataChannel* pChannel );

		typedef enum tagMode
		{
			EMS_DB_RET_MODE_UNKNOWN = 0,
			EMS_DB_RET_MODE_STATIC = 1,
			EMS_DB_RET_MODE_REALTIME = 2
		} EMSDBRETRIEVALMODE;

	protected:
		//! @fn void run()
		//! Run the retriever.
		void run();

	private:
		void				_SetRuntimeError( const EMS_RESULT chrError );
		void				_SetupRealtimeMonitor();
		void				_SetupNotificationEvent();
		void				_ExecuteQuery();
		EMSDBRETRIEVALMODE	_GetMode();
		void				_StopRealtimeMonitor();
		std::wstring		_GetTable();
		std::wstring		_GetColumn();
		ULONG				_GetSourceID();
		ULONG				_GetDestID();
		std::wstring		_GetWhereClause();
		std::wstring		_GetEventName();
		ULONG				_GetSourceIDFromRoute();
		ULONG				_GetDestIDFromRoute();
		std::wstring		_GetSQL();
		std::wstring		_GetRealtimeCriteria();
		void				_WriteToStream( CEMSPointerList<CEMSRawDataRecordReader>& olstData );
		void				_SignalDataAvailable();
		void				_UpdateTimestamp( CEMSRawDataRecordReader* pRec );


	private:
		std::wstring		m_owszRoute;
		ULONG				m_ulSrcID;
		ULONG				m_ulDestID;
		ULONG				m_ulChunkSize;
		std::wstring		m_owszSQL;
		std::wstring		m_owszActiveSourceTable;
		std::wstring		m_owszActiveSourceColumn;
		std::wstring		m_owszActiveSourceWhere;
		ULONG				m_ulTestPeiod;
		CEMSQueueMemoryStream*	m_pMemStrm;
		std::wstring		m_owszEventName;
		EMS_RESULT			m_hrRuntime;
		bool				m_bRunning;
		CEMSCriticalSection m_csRetriever;
		EMSDALCACHEID		m_idCache;
		std::wstring		m_owszDBCon;
		ULONG				m_ulMaxBufferSize;

		HANDLE				m_hNotifyEvent;

		HANDLE				m_hRealtimeEvent;
		CEMSNewDataMonitorA*	m_pDataMonitor;

		EMSTIME				m_timeLastRealtimeRecord;

		CEMSDBRetrieverDALClient m_oDALClient;

		ULONG				m_ulFields;
		EMSFIELDDESCRIPTOR* m_aFields;

		CEMSStreamDataChannel*	m_pDataChannel;

	private:
		static const ULONG ms_culMaxBufferSize;
		static const ULONG ms_culWaitForStop;
		static const ULONG ms_culStopWaitTimeout;
		static const ULONG ms_culRealtimeTimeout;
		static const ULONG ms_culMaxStopAttempts;
		static const ULONG ms_culTimeBetweenStopChecks;
		static const wchar_t* ms_cwszRealtimeEventPrefix;
		static const wchar_t* ms_cwszRealtimeCriteria;
		static const ULONG ms_culRetryWait;
};

#endif