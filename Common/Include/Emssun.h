/********************************************************************
*	Module:			emssun.h
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

	0.0	2001/03/22	rvw	start

********************************************************************/

#ifndef INC_EMSSUN
#define INC_EMSSUN

#include "emstypes.h"
#include "emstime.h"
#include "emsconst.h"
//#include "emsvectr.h"

class CEMSSun
{
protected:	
	CEMSSun() { }
	~CEMSSun() { }

public:
	static EMSAZELVECTOR SunPoint( EMSTIME timeNow, EMSLOCATION location );
	static EMSENUVECTOR  SunESZVector( EMSTIME timeNow, EMSLOCATION location );
	static EMSVECTOR     SunVector( EMSTIME timeNow, EMSLOCATION location );
	static EMSVECTOR     SunVector( EMSTIME emsTime );
	static double        SunRadius( EMSTIME emsTime );

private:
	static double _Modulo2PI( double dRadians );
	static double _CenturyJ2000( EMSTIME emsTime );
	static double _Obliquity( double dCenturyU );
	static double _MeanAnomaly( double dCenturyU );
};

#endif // INC_EMSSUN
