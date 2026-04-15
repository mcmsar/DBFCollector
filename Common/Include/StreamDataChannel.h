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

#ifndef __STREAM_DATA_CHANNEL_H__
#define __STREAM_DATA_CHANNEL_H__

#include "logclient.h"
#include "pointermap.h"
#include "emspipe.h"
#include "criticalsection.h"
#include "aobjbase.h"
#include "dal.h"

class CEMSStreamSink;
class CEMSStreamSource;

//! A generic data channel housing a stream of data.
class CEMSStreamDataChannel : public CEMSLogClient, public CApiObjBase
{
	public:
		CEMSStreamDataChannel();
		CEMSStreamDataChannel( const CEMSStreamDataChannel& x );
		virtual ~CEMSStreamDataChannel();

		//! Set the URL that is the source of data.
		void SetURL( const wchar_t* cwszURL ) { if( cwszURL ) m_owszURL = cwszURL; }

		//! Get the URL that is the source of data.
		std::wstring GetURL() { return m_owszURL; }

		//! Connect a sink to the data stream and return a pointer to it.
		//! The caller must disconnect and Release the sink when finished.
		virtual void ConnectSinkStream( IEMSSeqStream*& pSink, const wchar_t* cwszSignalName,
										const ULONG culMaxBufferSize ) = 0;

		//! Disconnects a sink from the data stream.
		virtual void DisconnectSinkStream( IEMSSeqStream* pSink ) = 0;

		//! Connect a source to the data stream and return a pointer to it.
		//! The caller must disconnect and Release the source when finished.
		virtual void ConnectSourceStream( IEMSSeqStream*& pSource, const wchar_t* cwszSignalName,
											const ULONG culMaxBufferSize ) = 0;

		//! Disconnects a source from the data stream.
		virtual void DisconnectSourceStream( IEMSSeqStream* pSink ) = 0;

		//! Start the data retrieval.  If retrieval was started then restart it because
		//! a new sink may have been added.
		virtual void Activate() = 0;

		//! Stop data retrieval or reading from sources.
		virtual void Deactivate() = 0;

		//! Writes the supplied data stream to all registered sinks.
		void WriteData( const BYTE *pv, ULONG cb );

		//! Retrieve meta data describing the records held in the resource.
		virtual void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields ) = 0;

		//! Indicates whether the channel is active.
		virtual bool IsRunning() { return false; }

		//! Cleanup any resources that are no longer in use.
		void Cleanup();


	protected:
		ULONG _AddSink( CEMSStreamSink* pSink );
		ULONG _RemoveSink( IEMSSeqStream* pStrm );
		ULONG _AddSource( CEMSStreamSource* pSource );
		ULONG _RemoveSource( IEMSSeqStream* pStrm );
		ULONG _ReadSources( BYTE*& rabyData );
		std::wstring _GetURL() const { return m_owszURL; }

	private:

		//! The URL specifying the data source for this data channel.
		std::wstring m_owszURL;

		//! A map of sinks.  IEMSSeqStream* is the key type for the map since it is
		//! what's exposed to consumers of the channel.
		CEMSPointerMap<IEMSSeqStream*,CEMSStreamSink> m_omapSinks;

		//! A map of sources.  IEMSSeqStream* is the key type for the map since it is
		//! what's exposed to consumers of the channel.
		CEMSPointerMap<IEMSSeqStream*,CEMSStreamSource> m_omapSources;

		//! A critical section used to synchronize access to the class's data.
		CEMSCriticalSection m_ocsChannel;

	private:
		
		//! The time in milliseconds to wait between writes to an overflowing sink, in milliseconds.
		static const ULONG ms_culRetryWait;

		//! The maximum number of retries when attempting to write to an overflowing sink.
		static const ULONG ms_culMaxRetries;

		//! The maximum number of bytes to read from a source in one call.
		static const ULONG ms_culBytesPerRead;

};

#endif