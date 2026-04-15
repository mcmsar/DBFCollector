/********************************************************************
*	Module:			emsvectr.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
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
#include <memory.h>
#include <math.h>

#include "emsvectr.h"

float CEMSVector::DotProduct( EMSVECTOR v1, EMSVECTOR v2 ) 
{
	return ( v1.fX * v2.fX ) + ( v1.fY * v2.fY ) + ( v1.fZ * v2.fZ );
}

double CEMSVector::DotProduct( EMSVECTORD v1, EMSVECTORD v2 ) 
{
	return ( v1.dX * v2.dX ) + ( v1.dY * v2.dY ) + ( v1.dZ * v2.dZ );
}

EMSVECTOR CEMSVector::CrossProduct( EMSVECTOR v1, EMSVECTOR v2 ) 
{
	EMSVECTOR v;

	v.fX = ( v1.fY * v2.fZ ) - ( v1.fZ * v2.fY );
	v.fY = ( v1.fZ * v2.fX ) - ( v1.fX * v2.fZ );
	v.fZ = ( v1.fX * v2.fY ) - ( v1.fY * v2.fX );

	return v;
}

EMSVECTORD CEMSVector::CrossProduct( EMSVECTORD v1, EMSVECTORD v2 ) 
{
	EMSVECTORD v;

	v.dX = ( v1.dY * v2.dZ ) - ( v1.dZ * v2.dY );
	v.dY = ( v1.dZ * v2.dX ) - ( v1.dX * v2.dZ );
	v.dZ = ( v1.dX * v2.dY ) - ( v1.dY * v2.dX );

	return v;
}

EMSVECTOR CEMSVector::Divide( EMSVECTOR v1, float fScalar ) 
{
	EMSVECTOR v = { v1.fX / fScalar , v1.fY / fScalar , v1.fZ / fScalar };

	return v;
}

EMSVECTORD CEMSVector::Divide( EMSVECTORD v1, double dScalar ) 
{
	EMSVECTORD v = { v1.dX / dScalar , v1.dY / dScalar , v1.dZ / dScalar };

	return v;
}

EMSVECTOR CEMSVector::Normalize( EMSVECTOR v1 ) 
{
	float fMagnitude = (float)sqrt( DotProduct( v1 , v1 ) );

	return Divide( v1, fMagnitude );
}

EMSVECTORD CEMSVector::Normalize( EMSVECTORD v1 ) 
{
	double dMagnitude = (double)sqrt( DotProduct( v1 , v1 ) );

	return Divide( v1, dMagnitude );
}


EMSVECTOR CEMSVector::Mult( EMSVECTOR v1, float fScalar ) 
{
	EMSVECTOR v = { v1.fX * fScalar , v1.fY * fScalar , v1.fZ * fScalar };

	return v;
}

EMSVECTORD CEMSVector::Mult( EMSVECTORD v1, double dScalar ) 
{
	EMSVECTORD v = { v1.dX * dScalar , v1.dY * dScalar , v1.dZ * dScalar };

	return v;
}

EMSVECTOR CEMSVector::Add( EMSVECTOR v1, EMSVECTOR v2 ) 
{
	EMSVECTOR v = { v1.fX + v2.fX , v1.fY + v2.fY ,	v1.fZ + v2.fZ };

	return v;
}

EMSVECTORD CEMSVector::Add( EMSVECTORD v1, EMSVECTORD v2 ) 
{
	EMSVECTORD v = { v1.dX + v2.dX , v1.dY + v2.dY ,	v1.dZ + v2.dZ };

	return v;
}

EMSVECTOR CEMSVector::Sub( EMSVECTOR v1, EMSVECTOR v2 ) 
{
	EMSVECTOR v = { v1.fX - v2.fX , v1.fY - v2.fY ,	v1.fZ - v2.fZ };

	return v;
}

EMSVECTORD CEMSVector::Sub( EMSVECTORD v1, EMSVECTORD v2 ) 
{
	EMSVECTORD v = { v1.dX - v2.dX , v1.dY - v2.dY ,	v1.dZ - v2.dZ };

	return v;
}

EMSVECTORD CEMSVector::ToDouble( EMSVECTOR v )
{
	EMSVECTORD vD;

	vD.dX = (double)v.fX;

	vD.dY = (double)v.fY;

	vD.dZ = (double)v.fZ;
 
	return vD;
}

EMSVECTOR CEMSVector::ToFloat( EMSVECTORD v )
{
	EMSVECTOR vF;

	vF.fX = (float)v.dX;

	vF.fY = (float)v.dY;

	vF.fZ = (float)v.dZ;
 
	return vF;
}


