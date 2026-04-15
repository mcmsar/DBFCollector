/********************************************************************
*	Module:			emsrange.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/11/14	rvw	start

********************************************************************/
#ifndef INC_EMSRANGE
#define INC_EMSRANGE

#include "emstypes.h"
#include "emstime.h"
#include "emserror.h"

class CEMSRangeRate
{
protected:	
	CEMSRangeRate() { }
	~CEMSRangeRate() { }

public:
	static EMS_RESULT Calculate( EMSVECTOR vGLoc, EMSTIMECOORD *lpvCoord, ULONG ulCount, EMSRANGERATE *lpRangeRate );
	static EMS_RESULT Calculate( EMSVECTORD vGLoc, EMSTIMECOORDD *lpvCoord, ULONG ulCount, EMSRANGERATED *lpRangeRate );
};

#endif // INC_EMSRANGE


