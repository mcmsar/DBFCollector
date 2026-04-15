/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
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

#include "dataaccesshelperbase.h"
#include "locate.h"
#include "objectlist.h"

//! Access data from the CALIB406EX_DATA table.
class CEMSCalib406ExData : public CEMSDataAccessHelperBase
{
	public:
		CEMSCalib406ExData();
		CEMSCalib406ExData( const CEMSCalib406ExData& x );
		virtual ~CEMSCalib406ExData();

		//! Get a list of unique beacon ids newer than the given time.
		CEMSObjectList<INT64> GetUniqueBeacons( const EMSTIME ctimeOldest );

		//! Get a list of locate records for the given beacon id and newer than the given time.
		//! Self-test beacons can be excluded.
		CEMSObjectList<EMSCALIB406DATAEXT> GetBeacons( const INT64 ci64BeaconID, 
														const EMSTIME ctimeOldest,
														const bool cbExcludeSelfTest );
};

