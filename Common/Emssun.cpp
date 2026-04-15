/********************************************************************
*	Module:			emssun.cpp
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

	0.0	2002/05/05	rrr	start

********************************************************************/
#include <memory.h>
#include <math.h>
#include "emsconst.h"
#include "emscoord.h"
#include "emsvectr.h"
#include "emssun.h"

static const CEMSTime	c_time2000Jan1_12UT1( 2000, 1, 1, 12 ); 
const CEMSCoordSystem	c_coordSys;

#define DMOD(a,b)      ((a) - (long int)((a)/(b)) * (b))

EMSAZELVECTOR CEMSSun::SunPoint( EMSTIME timeNow, EMSLOCATION location )
{
	EMSENUVECTOR vSUN;
	EMSAZELVECTOR sunPoint;

	vSUN = CEMSSun::SunESZVector( timeNow, location );
	sunPoint = c_coordSys.ToAzimuthAndElevation( vSUN );

	return sunPoint;
}



EMSENUVECTOR CEMSSun::SunESZVector( EMSTIME timeNow, EMSLOCATION location )
{
	EMSENUVECTOR esuVector;

	EMSVECTOR vDiff = CEMSSun::SunVector( timeNow, location );
	esuVector = c_coordSys.ToTopocentricHorizon( vDiff, location, timeNow );

	return esuVector;
}

EMSVECTOR CEMSSun::SunVector( EMSTIME timeNow, EMSLOCATION location )
{
	EMSVECTOR vDiff;
	EMSVECTOR vObserver = c_coordSys.ToInertialPosition( location, timeNow );
	EMSVECTOR vSun = CEMSSun::SunVector ( timeNow );
	double    dRadius = CEMSSun::SunRadius ( timeNow );

	vDiff.fX = (float)dRadius * vSun.fX - vObserver.fX;
	vDiff.fY = (float)dRadius * vSun.fY - vObserver.fY;
	vDiff.fZ = (float)dRadius * vSun.fZ - vObserver.fZ;

	return vDiff;
}

EMSVECTOR CEMSSun::SunVector( EMSTIME emsTime )

{
	CEMSTime atTime( emsTime );
	EMSVECTOR sun;
	double dMA, dObliq, dCentU;

	dCentU  = _CenturyJ2000( emsTime );
	dMA     = _MeanAnomaly( dCentU );
	dObliq  = _Obliquity( dCentU );
	
	sun.fX = (float)cos(dMA);
	sun.fY = (float)( cos(dObliq)*sin(dMA) );
	sun.fZ = (float)( sin(dObliq)*sin(dMA) );

	return sun; 
}

double CEMSSun::_CenturyJ2000( EMSTIME emsTime )
{
	CEMSTime atTime( emsTime );
	double dCentU = c_time2000Jan1_12UT1.DaysDifferent( emsTime );
	return ( dCentU / 36525.0 );
}
double CEMSSun::_Obliquity( double dCentU )
{
	// Compute the Obliquity of Ecliptic
	double dObliq = _Modulo2PI( 0.408982 - 0.0002269*dCentU );
	return dObliq;
}

double CEMSSun::_MeanAnomaly( double dCentU )
{
	double dG, dDMA, dMA;
	// Compute the Mean anomaly
	dG = 0.993133 + 99.997361*dCentU;
	dG = DMOD(dG,1);

	dDMA  = 6893*sin( c_dTwoPI*dG ) + 72*sin( c_dTwoPI*2*dG );
	dMA   = 0.7859453 + dG;
	dMA  += (6191.2*dCentU + dDMA)/1296000.0;
	dMA   = DMOD(dMA,1);
	dMA  *= c_dTwoPI;

	return dMA;
}


double CEMSSun::SunRadius( EMSTIME emsTime )
{
	double dMA, dCentU, dRadius;

	dCentU  = _CenturyJ2000( emsTime );
	dMA     = _MeanAnomaly( dCentU );

  	dRadius = (1.0014 - 0.01671*cos(dMA) - 0.00014*cos(2*dMA))*149600000.0;

	return dRadius;

}
double CEMSSun::_Modulo2PI( double dRadians )
{
	while ( dRadians < 0.0 )		// if negative add 2PI
		dRadians += c_dTwoPI;

	while ( dRadians > c_dTwoPI )
		dRadians -= c_dTwoPI;

	return dRadians;
}

