/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_154_H__
#define __SIT_154_H__

#include "emsitmeoalertmessagebase.h"

// Unlocated MEO Alerts
class CEMSSit154 : public CEMSSitMEOAlertMessageBase
{
	public:
		CEMSSit154();
		CEMSSit154( const CEMSSit154& x );
		virtual ~CEMSSit154();
};

#endif