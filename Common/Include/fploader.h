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

	$Log:
	$
********************************************************************/

#ifndef __FP_LOADER_H__
#define __FP_LOADER_H__

#include "fpconfig.h"
#include "antennacontrol.h"
#include "datacollector.h"

//! Class loader for FP proxies.
class CEMSFPLoader
{
	public:
		CEMSFPLoader() {}
		~CEMSFPLoader() {}

		static IEMSDataCollector* LoadDatastreamProxy( const ULONG culPairID, CEMSFPConfig& roConfig );
		static IEMSAntenna* LoadAntennaProxy( const ULONG culPairID, CEMSFPConfig& roConfig );
		static IEMSAntenna* LoadAntennaProxyByID( const ULONG culAntennaID, CEMSFPConfig& roConfig );
};

#endif