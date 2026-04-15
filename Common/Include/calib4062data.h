/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

//! Access data from the CALIB4062_DATA table.
class CEMSCalib4062Data : public CEMSDataAccessHelperBase
{
	public:
		CEMSCalib4062Data();
		CEMSCalib4062Data( const CEMSCalib4062Data& x );
		virtual ~CEMSCalib4062Data();

		//! Get a list of unique beacon ids newer than the given time.
		CEMSObjectList<INT64> GetUniqueBeacons( const EMSTIME ctimeOldest );

		//! Get a list of locate records for the given beacon id and newer than the given time.
		CEMSObjectList<EMSCALIB406DATA2> GetBeacons( const INT64 ci64BeaconID, const EMSTIME ctimeOldest );
};

