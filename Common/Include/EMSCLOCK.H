/********************************************************************
*	Module:			emsclock.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSSystemClock
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
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

	0.0	2001/09/17	rvw	start

********************************************************************/

#ifndef INC_EMSCLOCK
#define INC_EMSCLOCK

#include "emstypes.h"
#include "emserror.h"
#include "emstime.h"

class CEMSSystemClock
{
public:
	CEMSSystemClock() { }
	~CEMSSystemClock() { }

	static EMS_RESULT SetTime( EMSTIME time );
	static EMSTIME GetTime( void );
};

#endif // INC_EMSCLOCK
