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

#ifndef __DATA_RETRIEVER_THREAD_H__
#define __DATA_RETRIEVER_THREAD_H__

#include "emsthread.h"
#include "emsdbfieldnames.h"
#include "gatewayhelper.h"
#include <string>
#include "rawdatarecord.h"
#include "pointerqueue.h"

class CEMSRecordMetaData;

//! @class CEMSDataRetrieverThread
//! This class can be used to asynchronously retrieve data from a 
//! local or remote database table.  It uses the Gateway to connect
//! to the data source.
class CEMSDataRetrieverThread : public CEMSThread
{
	public:
		CEMSDataRetrieverThread();
		CEMSDataRetrieverThread( const CEMSDataRetrieverThread& x );
		virtual ~CEMSDataRetrieverThread();

		//! @fn void SetSQL( const wchar_t* cwszSQL )
		//! Specify the SQL statement to execute.
		void SetSQL( const wchar_t* cwszSQL );

		//! @fn void void SetCalleeID( const ULONG culID )
		//! Used when connecting to datasource, identifies the source.
		void SetCalleeID( const ULONG culID );

		//! @fn void SetCallerID( const ULONG culID )
		//! Used when connecting to datasource, identifies the caller.
		void SetCallerID( const ULONG culID );

		//! @fn void void SetCallback( const HWND chWndNotify, const UINT cuiMessageID )
		//! Used to specify the window and message ID to send notifications back to.
		void SetCallback( const HWND chWndNotify, const UINT cuiMessageID );

		//! @fn void SetChunkSize( const ULONG culSize )
		//! Sets the number of records to retrieve in each call to the Gateway.
		void SetChunkSize( const ULONG culSize );

		//! @fn void SetMetaData( const bool cbMeta = true )
		//! Sets a flag indicating whether to retrieve meta data.
		void SetMetaData( const bool cbMeta = true );

		//! @fn void SetMaxRecords( const ULONG culMaxRecords )
		//! Set the maximum number of records to retrieve.
		void SetMaxRecords( const ULONG culMaxRecords );

		//! @fn void RetrieveData()
		//! Start the retrieval of data.
		void RetrieveData();
		
		//! @fn void StopMonitor()
		//! Stop the retrieval of data.
		void StopRetrieval();

		//! @fn bool IsRunning()
		//! Test whether the monitor is running.
		bool IsRunning() { return m_bIsRunning; }

		//! @fn CEMSRawDataRecord* GetNextRecord()
		//! Gets the next record from the queue.  The caller must call
		//! Release() on the returned pointer.
		CEMSRawDataRecord* GetNextRecord();

		//! @fn CEMSRecordMetaData* GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aDescriptors )
		//! Retrieve the array of field descriptors.  The caller must Release() the returned pointer.
		CEMSRecordMetaData* GetMetaData();

	private:
		void _GetData();
		void _SaveMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFieldDesc );
		void _SaveData( const ULONG culDataSize, const ULONG culRecordSize, const unsigned char* cabyData );
		void _ClearMeta();
		void _SignalData();

	protected:
		void run();

	private:
		std::wstring m_wszSQL;
		ULONG m_ulCallee;
		ULONG m_ulCaller;
		HWND m_hWndNoitfy;
		UINT m_uiMessageID;
		bool m_bIsRunning;
		CEMSGatewayHelper m_oGatewayHelper;
		ULONG m_ulChunksize;
		bool m_bMeta;
		ULONG m_ulMaxRecords;

		CEMSCriticalSection m_csMeta;
		CEMSRecordMetaData*	m_pMeta;

		CEMSPointerQueue<CEMSRawDataRecord> m_queueData;	// A thread-safe queue.


		static const ULONG ms_culShutdownTimeout;
		static const ULONG ms_culCheckPeriod;

};

#endif