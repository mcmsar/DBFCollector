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

#ifndef __DB_STREAM_DATA_CHANNEL_H__
#define __DB_STREAM_DATA_CHANNEL_H__

#include "logclient.h"
#include "streamdatachannel.h"

class CEMSDBRetriever;

//! A data channel housing a stream of data returned from a database query.
class CEMSDBStreamDataChannel : public CEMSStreamDataChannel
{
	public:
		CEMSDBStreamDataChannel();
		CEMSDBStreamDataChannel( const CEMSDBStreamDataChannel& x );
		virtual ~CEMSDBStreamDataChannel();

		//! Connect a sink to the data stream and return a pointer to it.
		//! If this is the first sink connecting then a database retriever
		//! is initialized and started as well.
		//! The caller must disconnect and Release the sink when finished.
		virtual void ConnectSinkStream( IEMSSeqStream*& pSink, const wchar_t* cwszSignalName,
											const ULONG culMaxBufferSize );

		//! Disconnects a sink from the data stream.  If this is the last
		//! connected sink (i.e., no more sinks remain connected) then the
		//! database retriever is shut down too.
		virtual void DisconnectSinkStream( IEMSSeqStream* pSink );

		//! Connect a source to the data stream and return a pointer to it.
		//! The caller must disconnect and Release the source when finished.
		virtual void ConnectSourceStream( IEMSSeqStream*& pSource, const wchar_t* cwszSignalName,
									const ULONG culMaxBufferSize );

		//! Disconnects a source from the data stream.
		virtual void DisconnectSourceStream( IEMSSeqStream* pSink );

		//! Start the data retrieval.  If retrieval was started then restart it because
		//! a new sink may have been added.
		virtual void Activate();

		//! Stop data retrieval.
		virtual void Deactivate();

		void SetRoute( const wchar_t* cwszRoute ) { if( cwszRoute ) m_owszRoute = cwszRoute; }

		void SetSrcID( const ULONG culSrcID ) { m_ulSrcID = culSrcID; }

		void SetDestID( const ULONG culDestID ) { m_ulDestID = culDestID; }

		void SetSQL( const wchar_t* cwszSQL ) { if( cwszSQL ) m_owszSQL = cwszSQL; }

		void SetSrcTable( const wchar_t* cwszSrcTable ) { if( cwszSrcTable ) m_owszSrcTable = cwszSrcTable; }
		
		void SetSrcColumn( const wchar_t* cwszSrcColumn ) { if( cwszSrcColumn ) m_owszSrcColumn = cwszSrcColumn; }

		void SetCriteria( const wchar_t* cwszCriteria ) { if( cwszCriteria ) m_owszCriteria = cwszCriteria; }

		void SetTestPeriod( const ULONG culTestPeriod ) { m_ulTestPeriod = culTestPeriod; }

		void SetDBConn( const wchar_t* cwszConn ) { if( cwszConn ) m_owszDBConn = cwszConn; }

		void SetChunkSize( const ULONG culChunkSize ) { m_ulChunkSize = culChunkSize; }

		//! Retrieve meta data describing the records held in the resource.
		void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields );


	private:
		void _ReleaseRetriever();
		void _ConnectRetriever();

	private:
		CEMSDBRetriever*	m_pDB;
		std::wstring		m_owszRoute;
		ULONG				m_ulSrcID;
		ULONG				m_ulDestID;
		std::wstring		m_owszSQL;
		std::wstring		m_owszSrcTable;
		std::wstring		m_owszSrcColumn;
		std::wstring		m_owszCriteria;
		ULONG				m_ulTestPeriod;
		std::wstring		m_owszDBConn;
		ULONG				m_ulChunkSize;

};

#endif