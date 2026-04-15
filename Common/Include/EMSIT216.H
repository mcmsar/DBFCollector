/********************************************************************
*	Module:			emsit215.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit216 
*						Leosar Orbit Vectors ( Earth-Fixed Format )
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

#ifndef INC_EMSIT216
#define INC_EMSIT216

#include "emsit215.h"

class CEMSSit216 : public CEMSSit215
{
public:
	CEMSSit216();
	virtual ~CEMSSit216();

	virtual void Reset( void );
};

#endif // INC_EMSIT216
