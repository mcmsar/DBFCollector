/********************************************************************
*	Module:			emsvectr.h
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

#ifndef INC_EMSVECTR
#define INC_EMSVECTR

#include "emstypes.h"
#include "emstime.h"

class CEMSVector
{
protected:	
	CEMSVector() { }
	~CEMSVector() { }

public:
	static float DotProduct( EMSVECTOR v1, EMSVECTOR v2 ) ;
	static double DotProduct( EMSVECTORD v1, EMSVECTORD v2 ) ;

	static EMSVECTOR CrossProduct( EMSVECTOR v1, EMSVECTOR v2 ) ;
	static EMSVECTORD CrossProduct( EMSVECTORD v1, EMSVECTORD v2 ) ;

	static EMSVECTOR Divide( EMSVECTOR v1, float fScalar ) ;
	static EMSVECTORD Divide( EMSVECTORD v1, double dScalar ) ;

	static EMSVECTOR Normalize( EMSVECTOR v1 ) ;
	static EMSVECTORD Normalize( EMSVECTORD v1 ) ;

	static EMSVECTOR Mult( EMSVECTOR v1, float fScalar ) ;
	static EMSVECTORD Mult( EMSVECTORD v1, double dScalar ) ;

	static EMSVECTOR Add( EMSVECTOR v1, EMSVECTOR v2 ) ;
	static EMSVECTORD Add( EMSVECTORD v1, EMSVECTORD v2 ) ;

	static EMSVECTOR Sub( EMSVECTOR v1, EMSVECTOR v2 ) ;
	static EMSVECTORD Sub( EMSVECTORD v1, EMSVECTORD v2 ) ;

	static EMSVECTORD ToDouble( EMSVECTOR v );
	static EMSVECTOR ToFloat( EMSVECTORD v );
};

#endif // INC_EMSVECTR
