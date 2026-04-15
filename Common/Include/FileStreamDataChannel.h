/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __FILE_STREAM_DATA_CHANNEL_H__
#define __FILE_STREAM_DATA_CHANNEL_H__

#include "logclient.h"
#include "streamdatachannel.h"
#include "emsthread.h"
#include "criticalsection.h"

class CEMSFileStream;

//! A data channel managing access to a file URL.
class CEMSFileStreamDataChannel : public CEMSStreamDataChannel, public CEMSThread
{
	public:
		CEMSFileStreamDataChannel();
		CEMSFileStreamDataChannel( const CEMSFileStreamDataChannel& x );
		virtual ~CEMSFileStreamDataChannel();

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

		//! Stop data retrieval and/or reading from sources.
		virtual void Deactivate();

		//! Retrieve meta data describing the records held in the resource.
		void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields );

		//! Set the file access mode.  A value of true means writeable.
		void SetWriteable( const bool cbWriteable = false ) { m_bWriteable = cbWriteable; }

		//! Indicates whether the channel is active.
		virtual bool IsRunning() { return m_bRunning; }

	protected:
		virtual void run();

	private:
		void			_ReleaseFile();
		void			_OpenFile();
		void			_ProcessSources();
		void			_ProcessSinks();
		std::wstring	_GetFileName();

	private:
		CEMSFileStream*	m_pFS;
		bool			m_bWriteable;
		CEMSCriticalSection	m_oCS;
		bool			m_bRunning;
		bool			m_bMaybeMoreSourceData;

};

#endif