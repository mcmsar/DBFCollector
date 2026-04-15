/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
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

#ifndef __BEACONSUMMARY_H__
#define __BEACONSUMMARY_H__

#ifdef __VMS
#pragma pack(push,BS,1)
#endif

//! Summary beacon message information.
typedef struct tagBeaconSummary
{
	INT64 i64BeaconID;
	EMSBEACONTYPE eType;
	bool bHasGPSLocation;
	double dLat;
	double dLong;
} EMSBEACONSUMMARY;

#ifdef __VMS
#pragma pack(pop,BS)
#endif

#endif
