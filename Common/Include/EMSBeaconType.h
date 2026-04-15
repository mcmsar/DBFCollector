/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMSBEACONTYPE_H__
#define __EMSBEACONTYPE_H__

typedef enum tagBeaconType
{
	EMSBEACONTYPE_UNKNOWN = 0,
	EMSBEACONTYPE_STANDARD = 1,
	EMSBEACONTYPE_MLB = 2,
	EMSBEACONTYPE_CSEL = 3,
	EMSBEACONTYPE_LAST = EMSBEACONTYPE_CSEL
} EMSBEACONTYPE;

#endif
