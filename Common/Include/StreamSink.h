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

#ifndef __STREAM_SINK_H__
#define __STREAM_SINK_H__

#include "logclient.h"
#include "emspipe.h"
#include "aobjbase.h"

//! A data stream sink.  Data will flow into this class and it will
//! signal its availability to consumers via the specified event name.
class CEMSStreamSink : public IEMSSeqStream, public CEMSLogClient, public CApiObjBase
{
	public:
		CEMSStreamSink();
		CEMSStreamSink( const CEMSStreamSink& x );
		virtual ~CEMSStreamSink();

		//! Specify the name of an event to signal when new data is available.
		void SetSignalName( const wchar_t* cwszSignal );

		//! Sets the maximum size, in bytes, of the data buffer.  This is used
		//! to prevent excessive memory use in the case where the consumer of the sink
		//! does not pull data from it fast enough.  Once the maximum size has been
		//! reached, any further data written to the sink's buffer is dropped.
		void SetMaxBufferSize( const ULONG culBytes ) { m_ulMaxBufferSize = culBytes; }

		//! Get an IEMSSeqStream pointer to this object.
		//! The caller must call Release when finished.
		IEMSSeqStream* GetStream();

		//! IEMSSeqStream method.  Read from the stream.
		EMS_RESULT STDMETHODCALLTYPE Read( BYTE *pv, ULONG cb, ULONG *pcbRead);
        
		//! IEMSSeqStream method.  Fill the sink.
        EMS_RESULT STDMETHODCALLTYPE Write( const BYTE *pv, ULONG cb, ULONG *pcbWritten);

		//! Member of IUnknown interface.
		STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);

		//! Member of IUnknown interface.
		STDMETHOD_(ULONG, AddRef)		(THIS);

		//! Member of IUnknown interface.
		STDMETHOD_(ULONG, Release)		(THIS);

	private:
		IEMSSeqStream*	_GetStream();
		void			_OnNewData();
		void			_CreateEvent();

	private:
		IEMSSeqStream*	m_pStrm;
		std::wstring	m_owszSignalName;
		HANDLE			m_hEvent;
		ULONG			m_ulMaxBufferSize;

	private:	// constants
		
		//! Default maximum data buffer size.
		static const ULONG ms_culDefaultMaxBuf;
};

#endif