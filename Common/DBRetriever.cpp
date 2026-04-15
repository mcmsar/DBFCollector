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
#pragma warning(disable:4786)

#include "dbretriever.h"
#include "emsqueuememstrm.h"
#include "emsexcpt.h"
#include "databaseresourcemsgs.h"
#include "newdatamonitor_a.h"
#include <sstream>
#include "emsclock.h"
#include "convutility.h"
#include "emsdbfieldnames.h"
#include "sqlbuilder.h"
#include "rawdatarecord.h"
#include "rawdatarecordreader.h"
#include "dbstreamdatachannel.h"
#include "streamsink.h"
#include "streamsource.h"

const ULONG CEMSDBRetriever::ms_culMaxBufferSize = 1024 * 1000;	// Bytes
const ULONG CEMSDBRetriever::ms_culStopWaitTimeout = 100;		// Milliseconds
const ULONG CEMSDBRetriever::ms_culRealtimeTimeout = 100;		// Milliseconds
const ULONG CEMSDBRetriever::ms_culWaitForStop = ms_culStopWaitTimeout + ms_culRealtimeTimeout + 500;	// Milliseconds
const ULONG CEMSDBRetriever::ms_culMaxStopAttempts = 5;
const ULONG CEMSDBRetriever::ms_culTimeBetweenStopChecks = 300;	// Milliseconds
const wchar_t* CEMSDBRetriever::ms_cwszRealtimeEventPrefix = L"DBRealtimeData_";
const wchar_t* CEMSDBRetriever::ms_cwszRealtimeCriteria = L" AND ";
const ULONG CEMSDBRetriever::ms_culRetryWait = 1000;	// Milliseconds

CEMSDBRetriever::CEMSDBRetriever() : m_ulSrcID(0), m_ulDestID(0), m_ulTestPeiod(0),
									m_pMemStrm(0), m_hrRuntime( EMS_OK ), m_bRunning(false),
									m_idCache( INITIALDALCACHEID ), m_hRealtimeEvent(0),
									m_pDataMonitor(0), m_hNotifyEvent(0), 
									m_ulMaxBufferSize( ms_culMaxBufferSize ),
									m_ulFields(0),
									m_aFields(0),
									m_pDataChannel(0)
{
	m_timeLastRealtimeRecord.intTime = 0;
}

CEMSDBRetriever::CEMSDBRetriever( const CEMSDBRetriever& x ) : m_owszRoute( x.m_owszRoute ),
														m_ulSrcID( x.m_ulSrcID ), 
														m_ulDestID( x.m_ulDestID ), 
														m_owszSQL( x.m_owszSQL ), 
														m_owszActiveSourceTable( x.m_owszActiveSourceTable ),
														m_owszActiveSourceColumn( x.m_owszActiveSourceColumn ),
														m_owszActiveSourceWhere( x.m_owszActiveSourceWhere ),
														m_ulTestPeiod( x.m_ulTestPeiod ),
														m_pMemStrm( x.m_pMemStrm ), 
														m_owszEventName( x.m_owszEventName ),
														m_hrRuntime( x.m_hrRuntime ),
														m_bRunning(false), 
														m_idCache( INITIALDALCACHEID ),
														m_hRealtimeEvent(0),
														m_pDataMonitor(0),
														m_hNotifyEvent(0),
														m_timeLastRealtimeRecord( x.m_timeLastRealtimeRecord ),
														m_owszDBCon( x.m_owszDBCon ),
														m_ulMaxBufferSize( x.m_ulMaxBufferSize ),
														m_ulFields(0),
														m_aFields(0),
														m_pDataChannel( x.m_pDataChannel )
{
	if( m_pMemStrm )
		m_pMemStrm->AddRef();

	if( m_pDataChannel )
		m_pDataChannel->AddRef();

}

CEMSDBRetriever::~CEMSDBRetriever()
{
	Stop();

	if( m_pMemStrm )
	{
		m_pMemStrm->Release();
		m_pMemStrm = 0;
	}

	if( m_aFields )
	{
		delete[] m_aFields;
		m_aFields = 0;
	}

	if( m_pDataChannel )
	{
		m_pDataChannel->Release();
		m_pDataChannel = 0;
	}

	_StopRealtimeMonitor();
}

void 
CEMSDBRetriever::SetRoute( const wchar_t* cwszRoute )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		if( cwszRoute )
			m_owszRoute = cwszRoute;

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetSrcDestID( const ULONG culSrcID, const ULONG culDestID )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		m_ulSrcID = culSrcID;
		m_ulDestID = culDestID;

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetSQL( const wchar_t* cwszSQL )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		if( cwszSQL )
		{
			m_owszSQL = cwszSQL;
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetActive( const wchar_t* cwszSourceTable, const wchar_t* cwszSourceColumn,
						const wchar_t* cwszCriteria, const ULONG culTestPeriod )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		if( cwszSourceTable && cwszSourceColumn && culTestPeriod > 0 )
		{
			m_owszActiveSourceTable = cwszSourceTable;
			m_owszActiveSourceColumn = cwszSourceColumn;
			m_owszActiveSourceWhere = cwszCriteria;
			m_ulTestPeiod = culTestPeriod;
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

IEMSSeqStream* 
CEMSDBRetriever::GetStream()
{
	IEMSSeqStream* pRet = 0;

	try
	{
		m_csRetriever.Enter();

		if( !m_pMemStrm )
		{
			// Create an instance of the memory stream.
			m_pMemStrm = new CEMSQueueMemoryStream;

			if( !m_pMemStrm )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			m_pMemStrm->SetMaxSize( m_ulMaxBufferSize );
		}

		if( !m_pMemStrm )
		{
			throw CEMSException( EMS_DBRES_NO_MEM_STREAM );
		}

		if( m_pMemStrm )
		{
			EMS_RESULT hr = m_pMemStrm->QueryInterface( IID_IEMSSeqStream, (void**) &pRet );

			if( EMS_OK != hr )
			{
				CEMSLogMsgParam oParam;
				oParam.AddX( hr );

				throw CEMSException( EMS_DBRES_QI_FAIL, oParam );
			}
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}

	return pRet;
}

bool 
CEMSDBRetriever::IsMoreData()
{
	bool bRet = true;

	try
	{
		m_csRetriever.Enter();

		if( INITIALDALCACHEID == m_idCache ||
			NULLDALCACHEID == m_idCache ||
			DONTCACHE == m_idCache )
		{
			bRet = false;
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}

	return bRet;
}

void 
CEMSDBRetriever::SetEventName( const wchar_t* cwszEventName )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		if( cwszEventName )
		{
			m_owszEventName = cwszEventName;
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetDBConnection( const wchar_t* cwszConn )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		if( cwszConn )
		{
			m_owszDBCon = cwszConn;
		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetChunkSize( const ULONG culSize )
{
	try
	{
		m_csRetriever.Enter();

		if( IsRunning() )
		{
			throw CEMSException( EMS_DBRES_RETRIEVAL_RUNNING );
		}

		m_ulChunkSize = culSize;

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::run()
{
	CoInitialize(0);

	try
	{
		m_csRetriever.Enter();

		// Determine the mode.
		EMSDBRETRIEVALMODE eMode = _GetMode();

		if( EMS_DB_RET_MODE_UNKNOWN == eMode )
		{
			_SetRuntimeError( EMS_DBRES_UNKNOWN_MODE );

			throw CEMSException( EMS_DBRES_UNKNOWN_MODE );
		}

		if( EMS_DB_RET_MODE_REALTIME == eMode )
		{
			_SetupRealtimeMonitor();
		}

		_SetupNotificationEvent();

		// Set state to running.
		m_bRunning = true;

		m_csRetriever.Leave();

		// Query for data.
		bool bDone = false;
		while( !WaitForStop( ms_culStopWaitTimeout ) && !bDone )
		{
			if( EMS_DB_RET_MODE_STATIC == eMode )
			{
				_ExecuteQuery();
				bDone = true;
			}
			else
			{
				// Realtime mode.  So wait for data.
				if( 0 == m_hRealtimeEvent )
				{
					throw CEMSException( EMS_DBRES_NO_REALTIME_EVENT_HANDLE );
				}

				switch( WaitForSingleObject( m_hRealtimeEvent, ms_culRealtimeTimeout ) )
				{
					case WAIT_OBJECT_0:
						_ExecuteQuery();
						break;
				}

			}
		}

		_StopRealtimeMonitor();

		m_csRetriever.Enter();
		m_bRunning = false;
		m_csRetriever.Leave();

	}
	catch( CEMSException& e )
	{
		_SetRuntimeError( e.GetErrCode() );

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();
	}

	CoUninitialize();
}

void 
CEMSDBRetriever::Stop()
{
	SignalStop();

	if( !wait( ms_culWaitForStop ) )
	{
		// Force the thread to stop.
		stop();
	}

	m_bRunning = false;
}

EMS_RESULT 
CEMSDBRetriever::GetRuntimeError()
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		m_csRetriever.Enter();

		hr = m_hrRuntime;

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
	return hr;
}

void 
CEMSDBRetriever::GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
{
	try
	{
		m_csRetriever.Enter();

		m_oDALClient.GetMetaData( ulFields, aFields );

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::SetCallback( CEMSStreamDataChannel* pChannel )
{
	try
	{
		m_csRetriever.Enter();

		if( pChannel )
		{
			if( m_pDataChannel )
			{
				m_pDataChannel->Release();
				m_pDataChannel = 0;
			}

			m_pDataChannel = pChannel;

			m_pDataChannel->AddRef();

		}

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();

		throw;
	}
}

void 
CEMSDBRetriever::_SetRuntimeError( const EMS_RESULT chrError )
{
	try
	{
		m_csRetriever.Enter();

		m_hrRuntime = chrError;

		m_csRetriever.Leave();
	}
	catch( ... )
	{
		m_csRetriever.Leave();
	}
}

void 
CEMSDBRetriever::_SetupRealtimeMonitor()
{
	if( !m_pDataMonitor )
	{
		m_pDataMonitor = new CEMSNewDataMonitorA;

		if( !m_pDataMonitor )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}

	std::wstring owszTable = _GetTable();

	if( owszTable.empty() )
	{
		throw CEMSException( EMS_DBRES_NO_REALTIME_TABLE );
	}

	std::wstring owszColumn = _GetColumn();

	if( owszColumn.empty() )
	{
		throw CEMSException( EMS_DBRES_NO_REALTIME_COLUMN );
	}

	ULONG ulSrcID = _GetSourceID();
	ULONG ulDestID = _GetDestID();

	std::wstring owszWhere = _GetWhereClause();	// optional

	std::wstring wszRealtimeEvent = _GetEventName();

	if( wszRealtimeEvent.empty( ) )
	{
		throw CEMSException( EMS_DBRES_NO_REALTIME_NOTIFY_EVENT );
	}

	m_hRealtimeEvent = CreateEventW( 0, FALSE, FALSE, wszRealtimeEvent.c_str() );

	if( 0 == m_hRealtimeEvent )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( m_owszEventName.c_str() );

		throw CEMSException( EMS_DBRES_REALTIME_EVENT_CREATION_FAIL, oParam );
	}

	m_pDataMonitor->SetTable( owszTable.c_str(), owszColumn.c_str() );
	m_pDataMonitor->SetCalleeID( ulDestID );
	m_pDataMonitor->SetCallerID( ulSrcID );
	m_pDataMonitor->SetCallback( wszRealtimeEvent.c_str() );
	m_pDataMonitor->SetCheckPeriod( m_ulTestPeiod );
	m_pDataMonitor->SetNotificationDelay( 0 );
	m_pDataMonitor->SetDBConnection( m_owszDBCon.c_str() );
	
	if( !owszWhere.empty() )
		m_pDataMonitor->SetAdditionalCriteria( owszWhere.c_str() );

	m_pDataMonitor->StartMonitor();

}

void 
CEMSDBRetriever::_SetupNotificationEvent()
{
	// The notification event is optional.  Could be using callback mechanism.
	if( !m_owszEventName.empty() )
	{
		m_hNotifyEvent = CreateEventW( 0, FALSE, FALSE, m_owszEventName.c_str() );

		if( 0 == m_hNotifyEvent )
		{
			CEMSLogMsgParam oParam;
			oParam.AddString( m_owszEventName.c_str() );

			throw CEMSException( EMS_DBRES_NOFITY_EVENT_CREATION_FAILED, oParam );
		}
	}
}

void 
CEMSDBRetriever::_ExecuteQuery()
{
	CEMSRawDataRecordReader* pRec = 0;

	try
	{
		std::wstring owszSQL = _GetSQL();

		if( owszSQL.empty() )
		{
			throw CEMSException( EMS_DBRES_SQL_RETRIEVAL_FAILURE );
		}

		// Execute the query.
		m_oDALClient.Init( m_ulSrcID, m_ulDestID, m_ulChunkSize );
		m_oDALClient.SetDBConnection( m_owszDBCon.c_str() );

		m_idCache = INITIALDALCACHEID;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecs = m_oDALClient.GetData( &m_idCache, m_ulChunkSize, 
																				owszSQL.c_str() );

		// Write the data to the stream.
		_WriteToStream( olstRecs );

		// Check for more.
		while( NULLDALCACHEID != m_idCache )
		{
			olstRecs = m_oDALClient.GetData( &m_idCache, 0, 0 );

			_WriteToStream( olstRecs );
		}

		// Update the latest timestamp retrieved for realtime mode.
		// Assuming that data has been retrieved in ascending timestamp order.
		olstRecs.MoveLast();
		pRec = olstRecs.GetNext();

		if( pRec )
		{
			_UpdateTimestamp( pRec );

			pRec->Release();
			pRec = 0;
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
CEMSDBRetriever::_WriteToStream( CEMSPointerList<CEMSRawDataRecordReader>& olstData )
{
	IEMSSeqStream* pStrm = 0;
	CEMSRawDataRecordReader* pRec = 0;
	CEMSRawDataRecord* pRawRec = 0;

	try
	{
//		pStrm = GetStream();

//		if( !pStrm )
//		{
//			throw CEMSException( EMS_DBRES_NO_WRITEABLE_STREAM );
//		}

		olstData.MoveFirst();

		for( ULONG l = 0; l < olstData.Count(); l++ )
		{
			pRec = olstData.GetNext();
			
			if( !pRec )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRawRec = pRec->GetRawData();

			if( !pRawRec )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			ULONG ulWritten = 0;
			EMS_RESULT hr = EMS_OK;

//			do
//			{
//				if( pStrm )
//				{
//					hr = pStrm->Write( pRawRec->GetPointerToBuffer(), pRawRec->GetBufferSize(), &ulWritten );
//				}
//				
//				if( EMS_OVERFLOW == hr )
//					Sleep( ms_culRetryWait );
//
//			} while( EMS_OVERFLOW == hr );
//
//			if( EMS_OK != hr )
//			{
//				CEMSLogMsgParam oParam;
//				oParam.AddX( hr );
//
//				throw CEMSException( EMS_DBRES_STREAM_WRITE_FAILURE, oParam );
//			}

//			if( ulWritten != pRawRec->GetBufferSize() )
//			{
//				CEMSLogMsgParam oParam;
//				oParam.Add( pRawRec->GetBufferSize() );
//				oParam.Add( ulWritten );
//
//				throw CEMSException( EMS_DBRES_STREAM_WRITE_UNDER, oParam );
//				
//			}

			// Write the data to the registered callback channel.
			if( m_pDataChannel )
			{
				m_pDataChannel->WriteData( pRawRec->GetPointerToBuffer(), pRawRec->GetBufferSize() );
			}


//			if( ulWritten != pRawRec->GetBufferSize() )
//			{
//				CEMSLogMsgParam oParam;
//				oParam.Add( pRawRec->GetBufferSize() );
//				oParam.Add( ulWritten );
//
//				throw CEMSException( EMS_DBRES_STREAM_WRITE_UNDER, oParam );
//				
//			}

			_SignalDataAvailable();

			pRec->Release();
			pRec = 0;

			pRawRec->Release();
			pRawRec = 0;
		}

//		pStrm->Release();
//		pStrm = 0;
	}
	catch( ... )
	{
		if( pRec )
		{
			pRec->Release();
			pRec = 0;
		}

		if( pRawRec )
		{
			pRawRec->Release();
			pRawRec = 0;
		}

		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}
}

CEMSDBRetriever::EMSDBRETRIEVALMODE
CEMSDBRetriever::_GetMode()
{
	EMSDBRETRIEVALMODE eRet = EMS_DB_RET_MODE_UNKNOWN;

	if( m_owszActiveSourceTable.empty() )
	{
		eRet = EMS_DB_RET_MODE_STATIC;
	}
	else
	{
		eRet = EMS_DB_RET_MODE_REALTIME;
	}

	return eRet;
}

void
CEMSDBRetriever::_StopRealtimeMonitor()
{
	if( m_pDataMonitor )
	{
		ULONG ulIterations = 0;

		m_pDataMonitor->StopMonitor();

		while( m_pDataMonitor->IsRunning() && ulIterations < ms_culMaxStopAttempts )
		{
			Sleep( ms_culTimeBetweenStopChecks );

			ulIterations++;
		}

		delete m_pDataMonitor;
		m_pDataMonitor = 0;
	}
}

std::wstring
CEMSDBRetriever::_GetEventName()
{
	std::wstringstream owstrmRet;

	owstrmRet << ms_cwszRealtimeEventPrefix << CEMSConversionUtil::ConvertToString( CEMSSystemClock::GetTime().intTime );

	return owstrmRet.str();

}

ULONG 
CEMSDBRetriever::_GetSourceID()
{
	ULONG ulRet = 0;

	if( 0 != m_ulSrcID )
	{
		ulRet = m_ulSrcID;
	}
	else
	{
		ulRet = _GetSourceIDFromRoute();
	}

	return ulRet;
}

ULONG
CEMSDBRetriever::_GetDestID()
{
	ULONG ulRet = 0;

	if( 0 != m_ulDestID )
	{
		ulRet = m_ulDestID;
	}
	else
	{
		ulRet = _GetDestIDFromRoute();
	}

	return ulRet;
}

ULONG
CEMSDBRetriever::_GetSourceIDFromRoute()
{
	ULONG ulRet = 0;

	if( !m_owszRoute.empty() )
	{
		// Assuming the route is a string of the form <SRCID>_<DESTID>

	}

	return ulRet;
}

ULONG
CEMSDBRetriever::_GetDestIDFromRoute()
{
	ULONG ulRet = 0;

	if( !m_owszRoute.empty() )
	{
		// Assuming the route is a string of the form <SRCID>_<DESTID>
	}

	return ulRet;
}

std::wstring
CEMSDBRetriever::_GetSQL()
{
	if( m_owszSQL.empty() )
	{
		throw CEMSException( EMS_DBRES_NOSQL );
	}

	CSQLBuilder oSQL( m_owszSQL.c_str() );

	switch( _GetMode() )
	{
		case EMS_DB_RET_MODE_REALTIME:
			{
				std::wstring wszCriteria = _GetRealtimeCriteria();

				if( !oSQL.HasWhere() )
				{
					oSQL.AddWhere( wszCriteria.c_str() );
				}
				else
				{
					oSQL.AddAnd();

					oSQL += wszCriteria.c_str();
				}
			}
			break;
	}

	return oSQL;
}

std::wstring		
CEMSDBRetriever::_GetRealtimeCriteria()
{
	if( 0 == m_timeLastRealtimeRecord.intTime )
	{
		if( !m_pDataMonitor )
		{
			throw CEMSException( EMS_DBRES_NO_REALTIME_MONITOR );
		}

		m_timeLastRealtimeRecord = m_pDataMonitor->GetLatestTimestamp();
	}

	CSQLBuilder oSQL;

	oSQL += cwszTimestamp;
	oSQL.AddGT();
	oSQL += CEMSConversionUtil::ConvertToString( m_timeLastRealtimeRecord.intTime ).c_str();

	return oSQL;
}

void
CEMSDBRetriever::_SignalDataAvailable()
{
	if( 0 == m_hNotifyEvent )
	{
		//throw CEMSException( EMS_DBRES_NO_DATA_AVAIL_EVENT );
	}
	else
	{
		SetEvent( m_hNotifyEvent );
	}
}

void				
CEMSDBRetriever::_UpdateTimestamp( CEMSRawDataRecordReader* pRec )
{
	if( pRec )
	{
		// Only applies to realtime mode.
		if( EMS_DB_RET_MODE_REALTIME == _GetMode() )
		{
			m_timeLastRealtimeRecord = pRec->GetFieldAsTime( m_owszActiveSourceColumn.c_str() );
		}
	}
}

std::wstring		
CEMSDBRetriever::_GetTable()
{
	return m_owszActiveSourceTable;
}
std::wstring		
CEMSDBRetriever::_GetColumn()
{
	return m_owszActiveSourceColumn;
}

std::wstring
CEMSDBRetriever::_GetWhereClause()
{
	return m_owszActiveSourceWhere;
}

