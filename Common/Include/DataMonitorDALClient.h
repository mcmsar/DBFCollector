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

#ifndef __DATA_MONITOR_DAL_CLIENT_H__
#define __DATA_MONITOR_DAL_CLIENT_H__

#include "dataaccesshelperbase.h"

//! @class CEMSDataMonitorDALClient
//! The data access layer client used by the new data monitor class.
class CEMSDataMonitorDALClient : public CEMSDataAccessHelperBase
{
	public:
		CEMSDataMonitorDALClient();
		CEMSDataMonitorDALClient( const CEMSDataMonitorDALClient& x );
		~CEMSDataMonitorDALClient();

		//! Retrieve the value of the latest timestampe for the given table.
		EMSTIME GetTimestamp( const wchar_t* cwszTimestampField, const wchar_t* cwszTable,
								const wchar_t* cwszAdditionalCriteria = 0 );

	private:
		std::wstring _GetLatestTimestampSQL( const wchar_t* cwszField, const wchar_t* cwszTable,
											const wchar_t* cwszAdditionalCriteria);
};

#endif