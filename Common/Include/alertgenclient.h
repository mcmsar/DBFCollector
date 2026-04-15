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

#ifndef __ALERT_GEN_CLIENT_H__
#define __ALERT_GEN_CLIENT_H__

#include "gatewayhelper.h"

//! Client class for accessing the Alert Generator.  Calls are made via the Gateway,
//! providing both security and remote access.
class CEMSAlertGenClient : public CEMSGatewayHelper
{
	public:
		CEMSAlertGenClient();
		CEMSAlertGenClient( const CEMSAlertGenClient& x );
		virtual ~CEMSAlertGenClient();

		//! Generate alerts for the given location records.
 		void GenerateAlerts(	const unsigned long culDestID,
								const unsigned long culDestinations,
								const unsigned long* caulDestinationIDs,
								const unsigned long culLocations,
								const EMSLOCATIONKEY* caLocations);
};

#endif