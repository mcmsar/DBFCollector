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

	$Log$
********************************************************************/

#ifndef __DATA_PROXY_H__
#define __DATA_PROXY_H__

#include "emsthread.h"
#include "dataaccesshelper.h"
#include "emsexcpt.h"
#include "aobjbase.h"

class CEMSCMHelper;
class IEMSMonitorDataSink;
class CWnd;
class IEMSProperties;

//! Base class for retrieving and notifying of data.
class CEMSDataProxy : public CEMSThread, public CApiObjBase
{
	public:
		CEMSDataProxy();
		CEMSDataProxy( const CEMSDataProxy& x );
		virtual ~CEMSDataProxy();

		//! Triggers initialization.  The derived class should call _Init with initialization values.
		virtual void Init( IEMSProperties* pProps )  = 0;

		//! Triggers a refresh of the update period.  The derived class retrieves
		//! the value and calls _SetRefreshPeriod.
		virtual void UpdateRefreshPeriod() = 0;

		//! Start monitoring for data.
		void Start();

		//! Stop monitoring for data.
		void Stop();

		bool IsRunning() { return m_bIsRunning; }

		//! Sets a pointer to an interface that is called to notify when new data is available.
		void SetNewDataCallback( IEMSMonitorDataSink* pSink );

		//! Provides a window and message to use for notification of data.
		void SetNewDataCallback( CWnd* pWnd, const UINT cuiMessage );

		//! Retrieve an exception, if one has been set on the worker thread.
		CEMSException GetException() { return m_oException; }

	protected:
		
		//! Triggers data retrieval in the derived class.  A return value of true means that new data
		//! was found.
		virtual bool _GetData() = 0;

		//! Returns a pointer to the DAL Helper member.  The caller should not release the pointer.
		CEMSDataAccessHelper* _GetDataAccessHelper() { return &m_oDALHelper; }

		//! Returns a pointer to a new instance of the data access helper.  The caller must
		//! release the poniter.
		CEMSDataAccessHelper* _GetNewDataAccessHelper();

		//! Set the new  refresh period.  This is the period on which the processing thread runs.
		void _SetRefreshPeriod( const ULONG culPeriod );

		//! Inititialization values for the helper (DAL/CM) classes.
		void _Init( const ULONG culCallerID, const ULONG culCalleeID, const ULONG culChunkSize );

	private:
		//! Processing thread implementation.
		void run();

		//! Called when new data is available.  Performs tasks such as calling the data notification
		//! sink.
		void _OnNewData();

	private:
		ULONG					m_ulRefreshPeriod;
		CEMSDataAccessHelper	m_oDALHelper;
		IEMSMonitorDataSink*	m_pDataSink;
		bool					m_bIsRunning;
		CEMSException			m_oException;

		CWnd* m_pWnd;
		UINT m_uiMessage;

		ULONG	m_ulCallerID;
		ULONG	m_ulCalleeID;
		ULONG	m_ulChunkSize;

};

#endif