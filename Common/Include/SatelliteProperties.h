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

#ifndef __SATELLITE_PROPERTIES_H__
#define __SATELLITE_PROPERTIES_H__

#include "emstypes.h"

class CEMSSatelliteProperties
{
	public:
		CEMSSatelliteProperties();
		CEMSSatelliteProperties( const CEMSSatelliteProperties& x );
		~CEMSSatelliteProperties();

		static bool RequiresBitReversal( const ULONG culSatID );
		static bool RequiresDDCorrection( const ULONG culSatID );
		static bool RequiresSpectrumInversion( const ULONG culSatID );
		static double GetDownlinkFrequency( const ULONG culSatID );

	public:	// constants
		static const ULONG ms_culMHz;
};

#endif