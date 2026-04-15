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

#ifndef __MonitorDataSink_H__
#define __MonitorDataSink_H__

//! Interface for signalling availability of new data.
class IEMSMonitorDataSink
{
	public:
		virtual ~IEMSMonitorDataSink() {}

		virtual void OnData() = 0;

	protected:
		IEMSMonitorDataSink() {}
};

#endif