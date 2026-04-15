/********************************************************************
*	Module:			emsit216.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit216  
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2005 Oct 27 rvw	start

********************************************************************/

#include <stdio.h>
#include <tchar.h>
#include "emsit216.h"

CEMSSit216::CEMSSit216()
{
	SetSitNumber(216);
}

CEMSSit216::~CEMSSit216()
{
}

void CEMSSit216::Reset( void )
{
	CEMSSit215::Reset();

	SetSitNumber(216);
}

