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

#ifndef __MONITOR_DATA_H__
#define __MONITOR_DATA_H__

#include "emsthread.h"
#include "dataaccesshelper.h"

class CEMSDataAccessHelper;
class CEMSCMHelper;

//! Base class for retrieving and notifying of realtime data.
class CEMSMonitorData : public CEMSThread
{
	public:
		CEMSMonitorData();
		CEMSMonitorData( const CEMSMonitorData& x );
		virtual ~CEMSMonitorData();

		//! Triggers a refresh of the update period.  The derived class retrieves
		//! the value and calls _SetRefreshPeriod.
		virtual void UpdateRefreshPeriod() = 0;

		//! Start monitoring for data.
		void Start();

		//! Stop monitoring for data.
		void Stop();

		//! Sets a pointer to an interface that is called to notify when new data is available.
		void SetNewDataCallback( IEMSMonitorDataSink* pSink );

	protected:
		
		//! Triggers data retrieval in the derived class.  A return value of true means that new data
		//! was found.
		virtual bool _GetData() = 0;

		//! Returns a pointer to the DAL Helper member.  The caller should not release the pointer.
		CEMSDataAccessHelper* _GetDataAccessHelper();

		//! Returns a pointer to the CM Helper member.   The caller should not release the pointer.
		CEMSCMHelper* _GetCMHelper();

		//! Set the new  refresh period.  This is the period on which the processing thread runs.
		void _SetRefreshPeriod( const ULONG culPeriod );

	private:
		//! Processing thread implementation.
		void run();

		//! Called when new data is available.  Performs tasks such as calling the data notification
		//! sink.
		void _OnNewData();

	private:
		ULONG					m_ulRefreshPeriod;
		CEMSDataAccessHelper	m_oDALHelper;

};

#endif