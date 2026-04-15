/********************************************************************
*	Module:			emsearth.cpp
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
#include "emsearth.h"
#include "emsconst.h"
#include "emsvectr.h"

static const CEMSTime	c_time2000Jan1_12UT1( 2000, 1, 1, 12 ); 
//static const double 	c_dTwoPI = 2.0 * 3.14159265;
//static const double 	c_dDegToRad = c_dTwoPI / 360.0;
//																	 2				 -6  3
//	GST = 24110.54841 + 8640184.812866Tu + 0.093104Tu  - 6.2 x 10	Tu
//				+  ( We * delta T )
//						
//	where Tu = Du / 36525 
//			Du = days since JD 2451545.0 ( 2000 Jan 1, 12h UT1 )
//

#define DMOD(a,b)      ((a) - (long int)((a)/(b)) * (b))

double CEMSEarth::LocalSiderealTime( EMSTIME emsTime, EMSDEGREES degLongitude )
{
	double dLST = _GreenwichSiderealTime( emsTime ) + ( degLongitude * c_dDegToRad ); 

	return _Modulo2PI( dLST );
}

double CEMSEarth::GreenwichSiderealTime( EMSTIME emsTime )
{
	return _Modulo2PI( _GreenwichSiderealTime( emsTime ) );
}

double CEMSEarth::_GreenwichSiderealTime( EMSTIME emsTime )
{
	CEMSTime atTime( emsTime );
	double dDeltaSeconds = atTime.SecondsFromMidnight();
	double dDaysU = c_time2000Jan1_12UT1.DaysDifferent( atTime.AtZeroHour() );
	double dTimeU = dDaysU / 36525.0;
	double dTimeUx2 = dTimeU * dTimeU;
	double dTimeUx3 = dTimeUx2 * dTimeU;

	double dGST = 24110.54841 + ( 8640184.812866 * dTimeU ) +
				( 0.093104 * dTimeUx2 ) - ( 6.2e-6 * dTimeUx3 );

	dGST *= c_dTwoPI / c_dSecondsPerDay;	// convert to radians 

	// add (We * deltaT) term
	dGST += c_radEarthRotationRate * atTime.SecondsFromMidnight(); 

	return dGST; 
}

double CEMSEarth::_Modulo2PI( double dRadians )
{
	while ( dRadians < 0.0 )				// if negative add 2PI
		dRadians += c_dTwoPI;

	while ( dRadians > c_dTwoPI )
		dRadians -= c_dTwoPI;

	return dRadians;
}

// radius of the earth at the point where the vector intersects the surface
//
double CEMSEarth::Radius( EMSVECTOR vIntersect )
{
	EMSVECTOR vNormal = CEMSVector::Normalize( vIntersect );
	double dTermA = c_dEarthFlatteningTerm * (double)vNormal.fZ 
											* (double)vNormal.fZ;
	double dRadius = ( 1.0 - ( dTermA / ( 1.0 - c_dEarthFlatteningTerm ) ) *
								( 1.0 - dTermA ) );

	return c_dEarthKmRadius * sqrt( dRadius );
}
