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

#include "satelliteproperties.h"

const ULONG CEMSSatelliteProperties::ms_culMHz = 1000000;

bool 
CEMSSatelliteProperties::RequiresBitReversal( const ULONG culSatID )
{
	bool bRet = false;

	if( culSatID >= 300 && 
		culSatID < 400 )
	{
		bRet = true;
	}

	return bRet;
}

bool 
CEMSSatelliteProperties::RequiresDDCorrection( const ULONG culSatID )
{
	bool bRet = false;

	if( culSatID >= 200 )
	{
		bRet = true;
	}

	return bRet;
}

bool 
CEMSSatelliteProperties::RequiresSpectrumInversion( const ULONG culSatID )
{
	bool bRet = false;

	if( culSatID >= 300 && 
		culSatID < 400 )
	{
		bRet = true;
	}

	return bRet;
}

double 
CEMSSatelliteProperties::GetDownlinkFrequency( const ULONG culSatID )
{
	double dRet = 1544.5*ms_culMHz; // GEO and LEO satellites
	
	if( culSatID >= 300 )
	{
		dRet = 2226.452*ms_culMHz; // DASS S-Band satellites
	}
	if ( culSatID >= 400 )
	{
		dRet = 1544.1*ms_culMHz; // Galileo L-Band satellites
	}
	if ( culSatID >= 500 )
	{
		dRet = 1544.9*ms_culMHz; // Glonass L-Band satellites
	}
	if ( culSatID >= 600 )
	{
		dRet = 1544.21*ms_culMHz; // Beidou L-Band satellites
	}
	if ( culSatID >= 700 )
	{
		dRet = 1544.8*ms_culMHz; // GPS L-Band satellites
	}

	return dRet;
}