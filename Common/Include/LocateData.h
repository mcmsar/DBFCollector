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

//! Access data from the LOCATE_DATA table.
class CEMSLocateData : public CEMSDataAccessHelperBase
{
	public:
		CEMSLocateData();
		CEMSLocateData( const CEMSLocateData& x );
		virtual ~CEMSLocateData();

		//! Get a list of unique beacon ids newer than the given time.
		CEMSObjectList<INT64> GetUniqueBeacons( const EMSTIME ctimeOldest );

		//! Get a list of locate records for the given beacon id and newer than the given time.
		CEMSObjectList<EMSLOCATE> GetLocations( const INT64 ci64BeaconID, const EMSTIME ctimeOldest );
};

