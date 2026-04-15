/********************************************************************
*	Module:			AntDefns.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Antenna-related Definitions
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

	0.0	01/07/21		rvw	start

********************************************************************/
#ifndef INC_ANTDEFNS
#define INC_ANTDEFNS

#include "emstypes.h"
#include "emstypex.h"

#define EMS_MAX_ANTENNA_VECTORS	64

typedef struct _tagEMSANTENNACMD
{
	ULONG			ulCode;			//	code ( & flags )
	ULONG			ulID;				// usually the Satellite ID
} EMSANTENNACMD, *LPEMSANTENNACMD;

typedef struct _tagEMSANTENNATRACK
{
	EMSANTENNACMD	cmd;
	EMSTIME			timeStart;
	ULONG				ulInterval;		// number of seconds between vectors
	ULONG				ulCount;			// number of vectors
	WORD				wSequence;
	WORD				wTotal;
	EMSESUVECTOR	esuVector[ EMS_MAX_ANTENNA_VECTORS ];
} EMSANTENNATRACK, *LPEMSANTENNATRACK;

#endif	// INC_ANTDEFNS

