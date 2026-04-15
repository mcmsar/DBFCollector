/********************************************************************
*	Module:			timefreq.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	generic data structure used to describe the raw data 
*						measurements of a particular satellite at a particular
*						time
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

	0.0	2001/11/22 	rvw	start

********************************************************************/

#ifndef INC_TIMEFREQ
#define INC_TIMEFREQ

typedef struct _tagEMSTIMEFREQ
{
	EMSTIME 	time;
	float		fFreq;
	ULONG 	ulSatID;
	EMSVECTOR vSatPosition;	// Satellite Position (EF)
	EMSVECTOR vSatVelocity;	// Satellite Velocity (EF)
} EMSTIMEFREQ , *LPEMSTIMEFREQ;

#endif // INC_TIMEFREQ
