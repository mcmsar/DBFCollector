/********************************************************************
*	Module:			emscoord.cpp
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
#include <math.h>
#include <memory.h>
#include "emsconst.h"
#include "emscoord.h"
#include "emsearth.h"
#include "emsvectr.h"
#include "emsrange.h"

static const double		c_dOneMinusFSquared = ( 1.0 - c_dEarthFlatteningTerm ) *
																( 1.0 - c_dEarthFlatteningTerm );
static const double		c_dFTimesFMinus2 = c_dEarthFlatteningTerm *
																( c_dEarthFlatteningTerm - 2.0 );

CEMSCoordSystem::CEMSCoordSystem()
{
	memset( &m_timeCoord,  0, sizeof( m_timeCoord  ) );
	memset( &m_timeCoordd, 0, sizeof( m_timeCoordd ) );
}

CEMSCoordSystem::CEMSCoordSystem( EMSTIMECOORD timeCoord )
{
	m_timeCoord = timeCoord;
}

CEMSCoordSystem::CEMSCoordSystem( EMSTIMECOORDD timeCoord )
{
	m_timeCoordd = timeCoord;
}

CEMSCoordSystem::~CEMSCoordSystem()
{
}


EMSTIMECOORD CEMSCoordSystem::ToEarthFixed( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			destCoord = _InertialToEarthFixed( srcCoord );
			break;

		case COORDSYS_EarthFixed:	// nothing to do
			destCoord = srcCoord;
			break;

		case COORDSYS_StdEarthFixed:
			destCoord = _StdEarthFixedToEarthFixed( srcCoord );			
			break;
	}

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::ToEarthFixed( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			destCoord = _InertialToEarthFixed( srcCoord );
			break;

		case COORDSYS_EarthFixed:	// nothing to do
			destCoord = srcCoord;
			break;

		case COORDSYS_StdEarthFixed:
			destCoord = _StdEarthFixedToEarthFixed( srcCoord );			
			break;
	}

	return destCoord;
}

EMSTIMECOORD CEMSCoordSystem::ToStdEarthFixed( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			destCoord = _InertialToEarthFixed( srcCoord );

			destCoord = _EarthFixedToStdEarthFixed( destCoord );
			break;

		case COORDSYS_EarthFixed:	// nothing to do
			destCoord = _EarthFixedToStdEarthFixed( srcCoord );
			break;

		case COORDSYS_StdEarthFixed:
			destCoord = srcCoord;
			break;
	}

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::ToStdEarthFixed( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			destCoord = _InertialToEarthFixed( srcCoord );

			destCoord = _EarthFixedToStdEarthFixed( destCoord );
			break;

		case COORDSYS_EarthFixed:	// nothing to do
			destCoord = _EarthFixedToStdEarthFixed( srcCoord );
			break;

		case COORDSYS_StdEarthFixed:
			destCoord = srcCoord;
			break;
	}

	return destCoord;
}

EMSTIMECOORD CEMSCoordSystem::_StdEarthFixedToEarthFixed( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;

	destCoord = srcCoord;

	destCoord.coordSystem = COORDSYS_EarthFixed;

	destCoord.coord.velocity.fX -= (float)( c_radEarthRotationRate * destCoord.coord.radius.fY );

	destCoord.coord.velocity.fY += (float)( c_radEarthRotationRate * destCoord.coord.radius.fX );

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::_StdEarthFixedToEarthFixed( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;

	destCoord = srcCoord;

	destCoord.coordSystem = COORDSYS_EarthFixed;

	destCoord.coord.velocity.dX -= ( c_radEarthRotationRate * destCoord.coord.radius.dY );

	destCoord.coord.velocity.dY += ( c_radEarthRotationRate * destCoord.coord.radius.dX );

	return destCoord;
}

EMSTIMECOORD CEMSCoordSystem::_EarthFixedToStdEarthFixed( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;

	destCoord = srcCoord;

	destCoord.coordSystem = COORDSYS_StdEarthFixed;

	destCoord.coord.velocity.fX += (float)( c_radEarthRotationRate * destCoord.coord.radius.fY );

	destCoord.coord.velocity.fY -= (float)( c_radEarthRotationRate * destCoord.coord.radius.fX );

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::_EarthFixedToStdEarthFixed( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;

	destCoord = srcCoord;

	destCoord.coordSystem = COORDSYS_StdEarthFixed;

	destCoord.coord.velocity.dX += ( c_radEarthRotationRate * destCoord.coord.radius.dY );

	destCoord.coord.velocity.dY -= ( c_radEarthRotationRate * destCoord.coord.radius.dX );

	return destCoord;
}

EMSTIMECOORD CEMSCoordSystem::_InertialToEarthFixed( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;
	double dGST = CEMSEarth::GreenwichSiderealTime( srcCoord.vTime );
	double dCosA = cos( dGST ), dSinA = sin( dGST );

	destCoord.coordSystem = COORDSYS_EarthFixed;

	destCoord.vTime = srcCoord.vTime;

	destCoord.coord.radius.fX = (float)(( dCosA * srcCoord.coord.radius.fX ) + 
										( dSinA * srcCoord.coord.radius.fY ));

	destCoord.coord.radius.fY = (float)(( -dSinA * srcCoord.coord.radius.fX ) + 
								 		 ( dCosA * srcCoord.coord.radius.fY ));

	destCoord.coord.radius.fZ = (float)srcCoord.coord.radius.fZ;

//	destCoord.coord.velocity.fX =  (float)(( dCosA * srcCoord.coord.velocity.fX ) + 
//							               ( dSinA * srcCoord.coord.velocity.fY ) + 
//							               ( c_radEarthRotationRate * destCoord.coord.radius.fY ));

//	destCoord.coord.velocity.fY = (float)(( -dSinA * srcCoord.coord.velocity.fX ) + 
//										  (  dCosA * srcCoord.coord.velocity.fY ) - 
//										  (  c_radEarthRotationRate * destCoord.coord.radius.fX ));

	destCoord.coord.velocity.fX =  (float)(( dCosA * srcCoord.coord.velocity.fX ) + 
										   ( dSinA * srcCoord.coord.velocity.fY ));

	destCoord.coord.velocity.fY = (float)(( -dSinA * srcCoord.coord.velocity.fX ) + 
										  (  dCosA * srcCoord.coord.velocity.fY )); 

	destCoord.coord.velocity.fZ = (float)srcCoord.coord.velocity.fZ;

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::_InertialToEarthFixed( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;
	double dGST = CEMSEarth::GreenwichSiderealTime( srcCoord.vTime );
	double dCosA = cos( dGST ), dSinA = sin( dGST );

	destCoord.coordSystem = COORDSYS_EarthFixed;

	destCoord.vTime = srcCoord.vTime;

	destCoord.coord.radius.dX =  (( dCosA * srcCoord.coord.radius.dX ) + 
										( dSinA * srcCoord.coord.radius.dY ));

	destCoord.coord.radius.dY = (( -dSinA * srcCoord.coord.radius.dX ) + 
										( dCosA * srcCoord.coord.radius.dY ));

	destCoord.coord.radius.dZ = srcCoord.coord.radius.dZ;

//	destCoord.coord.velocity.dX =  (( dCosA * srcCoord.coord.velocity.dX ) + 
//							( dSinA * srcCoord.coord.velocity.dY ) + 
//							( c_radEarthRotationRate * destCoord.coord.radius.dY ));

//	destCoord.coord.velocity.dY = (( -dSinA * srcCoord.coord.velocity.dX ) + 
//												( dCosA * srcCoord.coord.velocity.dY ) - 
//												( c_radEarthRotationRate * destCoord.coord.radius.dX ));

	destCoord.coord.velocity.dX =  (( dCosA * srcCoord.coord.velocity.dX ) + 
											( dSinA * srcCoord.coord.velocity.dY ));

	destCoord.coord.velocity.dY = (( -dSinA * srcCoord.coord.velocity.dX ) + 
											( dCosA * srcCoord.coord.velocity.dY )); 

	destCoord.coord.velocity.dZ = srcCoord.coord.velocity.dZ;

	return destCoord;
}

EMSAZELVECTOR CEMSCoordSystem::ToAzimuthAndElevation( EMSTIMECOORD srcCoord, EMSLOCATION location ) const
{
	EMSENUVECTOR enuVector = ToTopocentricHorizon( srcCoord, location );

	return ToAzimuthAndElevation( enuVector );
}

EMSAZELVECTORD CEMSCoordSystem::ToAzimuthAndElevation( EMSTIMECOORDD srcCoord, EMSLOCATION location ) const
{
	EMSENUVECTORD enuVector = ToTopocentricHorizon( srcCoord, location );

	return ToAzimuthAndElevation( enuVector );
}

EMSAZELVECTOR CEMSCoordSystem::ToAzimuthAndElevation( EMSENUVECTOR enuVector ) const
{
	EMSAZELVECTOR azelVector;

	azelVector.fRange = (float)sqrt( ( enuVector.fNorth * enuVector.fNorth ) +
							( enuVector.fEast * enuVector.fEast ) +
							( enuVector.fUp * enuVector.fUp ) );

	azelVector.azel.degElevation = asin( enuVector.fUp / azelVector.fRange );

	azelVector.azel.degAzimuth = atan2( enuVector.fEast , enuVector.fNorth );

	azelVector.azel.degAzimuth *= c_dRadToDeg;

	azelVector.azel.degElevation *= c_dRadToDeg;

	return azelVector;
}

EMSAZELVECTORD CEMSCoordSystem::ToAzimuthAndElevation( EMSENUVECTORD enuVector ) const
{
	EMSAZELVECTORD azelVector;

	azelVector.dRange = sqrt( ( enuVector.dNorth * enuVector.dNorth ) +
							( enuVector.dEast * enuVector.dEast ) +
							( enuVector.dUp * enuVector.dUp ) );

	azelVector.azel.degElevation = asin( enuVector.dUp / azelVector.dRange );

	azelVector.azel.degAzimuth = atan2( enuVector.dEast , enuVector.dNorth );

	azelVector.azel.degAzimuth *= c_dRadToDeg;

	azelVector.azel.degElevation *= c_dRadToDeg;

	return azelVector;
}

EMSENUVECTOR CEMSCoordSystem::ToTopocentricHorizon( EMSTIMECOORD srcCoord, EMSLOCATION location ) const
{
	EMSENUVECTOR enuVector;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			enuVector = ToTopocentricHorizon( srcCoord.coord.radius, location, srcCoord.vTime );
			break;

		default:
			memset( &enuVector, 0, sizeof( enuVector ) );
			break;
	}
	return enuVector;
}

EMSENUVECTORD CEMSCoordSystem::ToTopocentricHorizon( EMSTIMECOORDD srcCoord, EMSLOCATION location ) const
{
	EMSENUVECTORD enuVector;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial:
			enuVector = ToTopocentricHorizon( srcCoord.coord.radius, location, srcCoord.vTime );
			break;

		default:
			memset( &enuVector, 0, sizeof( enuVector ) );
			break;
	}
	return enuVector;
}

EMSENUVECTOR CEMSCoordSystem::ToTopocentricHorizon( EMSVECTOR srcInertialVector, EMSLOCATION location, EMSTIME emsTime ) const
{
	EMSENUVECTOR enuVector;
	double dLST = CEMSEarth::LocalSiderealTime( emsTime, location.degLongitude );
	double dSinLST = sin( dLST );
	double dCosLST = cos( dLST );
	double dSinLatitude = sin( location.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( location.degLatitude * c_dDegToRad );

	enuVector.fNorth = -(float)( ( dSinLatitude * dCosLST * srcInertialVector.fX ) +
									  	( dSinLatitude * dSinLST * srcInertialVector.fY ) -
									  	( dCosLatitude * srcInertialVector.fZ ) );

	enuVector.fEast = (float)( ( -dSinLST * srcInertialVector.fX ) +
									  	( dCosLST * srcInertialVector.fY ) );

	enuVector.fUp = (float)( ( dCosLatitude * dCosLST * srcInertialVector.fX ) +
									  	( dCosLatitude * dSinLST * srcInertialVector.fY ) +
									  	( dSinLatitude * srcInertialVector.fZ ) );

	return enuVector;
}

//
//	x = a C cos(Latitude) cos( LST )
//	y = a C cos(Latitude) sin( LST )
//	z = a S sin(Latitude)
// where:																 2
//	C = 1 / sqrt( 1 + ( f * ( f - 2 ) * sin( Latitude ) 	)
//
//					  2
//	S = ( 1 - f )   * C
//
//	f = earth's flattening term	( 1 / 298.26 )
//	a = earth's radius

EMSENUVECTORD CEMSCoordSystem::ToTopocentricHorizon( EMSVECTORD srcInertialVector, EMSLOCATION location, EMSTIME emsTime ) const
{
	EMSENUVECTORD enuVector;
	double dLST = CEMSEarth::LocalSiderealTime( emsTime, location.degLongitude );
	double dSinLST = sin( dLST );
	double dCosLST = cos( dLST );
	double dSinLatitude = sin( location.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( location.degLatitude * c_dDegToRad );

	enuVector.dNorth = -( ( dSinLatitude * dCosLST * srcInertialVector.dX ) +
									  	( dSinLatitude * dSinLST * srcInertialVector.dY ) -
									  	( dCosLatitude * srcInertialVector.dZ ) );

	enuVector.dEast = ( ( -dSinLST * srcInertialVector.dX ) +
									  	( dCosLST * srcInertialVector.dY ) );

	enuVector.dUp = ( ( dCosLatitude * dCosLST * srcInertialVector.dX ) +
									  	( dCosLatitude * dSinLST * srcInertialVector.dY ) +
									  	( dSinLatitude * srcInertialVector.dZ ) );

	return enuVector;
}

//
//	x = a C cos(Latitude) cos( LST )
//	y = a C cos(Latitude) sin( LST )
//	z = a S sin(Latitude)
// where:																 2
//	C = 1 / sqrt( 1 + ( f * ( f - 2 ) * sin( Latitude ) 	)
//
//					  2
//	S = ( 1 - f )   * C
//
//	f = earth's flattening term	( 1 / 298.26 )
//	a = earth's radius

EMSVECTOR CEMSCoordSystem::ToInertialPosition( EMSLOCATION srcLocation, EMSTIME srcTime ) const
{
	EMSVECTOR position;
	double dLST = CEMSEarth::LocalSiderealTime( srcTime, srcLocation.degLongitude );
	double dSinLatitude = sin( srcLocation.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( srcLocation.degLatitude * c_dDegToRad );
	double dSinLST = sin( dLST );
	double dCosLST = cos( dLST );
	double dTermC = 1.0 / sqrt( 1.0 + ( c_dFTimesFMinus2 * dSinLatitude * dSinLatitude ) );
	double dTermS = c_dOneMinusFSquared * dTermC;
	double dRadius = c_dEarthKmRadius + srcLocation.fAltitude;

	position.fX = (float)( dRadius * dTermC * dCosLatitude * dCosLST );

	position.fY = (float)( dRadius * dTermC * dCosLatitude * dSinLST );

	position.fZ = (float)( dRadius * dTermS * dSinLatitude );

	return position;
}

EMSVECTORD CEMSCoordSystem::ToInertialPositionDouble( EMSLOCATION srcLocation, EMSTIME srcTime ) const
{
	EMSVECTORD position;
	double dLST = CEMSEarth::LocalSiderealTime( srcTime, srcLocation.degLongitude );
	double dSinLatitude = sin( srcLocation.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( srcLocation.degLatitude * c_dDegToRad );
	double dSinLST = sin( dLST );
	double dCosLST = cos( dLST );
	double dTermC = 1.0 / sqrt( 1.0 + ( c_dFTimesFMinus2 * dSinLatitude * dSinLatitude ) );
	double dTermS = c_dOneMinusFSquared * dTermC;
	double dRadius = c_dEarthKmRadius + srcLocation.fAltitude;

	position.dX = ( dRadius * dTermC * dCosLatitude * dCosLST );

	position.dY = ( dRadius * dTermC * dCosLatitude * dSinLST );

	position.dZ = ( dRadius * dTermS * dSinLatitude );

	return position;
}

//EMSVECTOR CEMSCoordSystem::ToEarthFixed( EMSCOORD srcCoord ) const
//{
//	EMSVECTOR position = { 0.0, 0.0, 0.0 };
//
//	return position;
//}

EMSVECTOR CEMSCoordSystem::ToEarthFixed( EMSLOCATION srcLocation ) const
{
	EMSVECTOR position = { 0.0, 0.0, 0.0 };
	double dSinLatitude = sin( srcLocation.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( srcLocation.degLatitude * c_dDegToRad );
	double dSinLongitude = sin( srcLocation.degLongitude * c_dDegToRad );
	double dCosLongitude = cos( srcLocation.degLongitude * c_dDegToRad );
	double dRadius = c_dEarthKmRadius + srcLocation.fAltitude;
	double dTermC = 1.0 / sqrt( 1.0 + ( c_dFTimesFMinus2 * dSinLatitude * dSinLatitude ) );
	double dTermS = c_dOneMinusFSquared * dTermC;

	position.fX = (float)( dRadius * dTermC * dCosLatitude * dCosLongitude );

	position.fY = (float)( dRadius * dTermC * dCosLatitude * dSinLongitude );

	position.fZ = (float)( dRadius * dTermS * dSinLatitude );

	return position;
}


EMSVECTORD CEMSCoordSystem::ToEarthFixedDouble( EMSLOCATION srcLocation ) const
{
	EMSVECTORD position = { 0.0, 0.0, 0.0 };
	double dSinLatitude = sin( srcLocation.degLatitude * c_dDegToRad );
	double dCosLatitude = cos( srcLocation.degLatitude * c_dDegToRad );
	double dSinLongitude = sin( srcLocation.degLongitude * c_dDegToRad );
	double dCosLongitude = cos( srcLocation.degLongitude * c_dDegToRad );
	double dRadius = c_dEarthKmRadius + srcLocation.fAltitude;
	double dTermC = 1.0 / sqrt( 1.0 + ( c_dFTimesFMinus2 * dSinLatitude * dSinLatitude ) );
	double dTermS = c_dOneMinusFSquared * dTermC;

	position.dX = ( dRadius * dTermC * dCosLatitude * dCosLongitude );

	position.dY = ( dRadius * dTermC * dCosLatitude * dSinLongitude );

	position.dZ = ( dRadius * dTermS * dSinLatitude );

	return position;
}


EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSVECTOR position ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double dEZR           = position.fZ / (1.0 - c_dEarthEccentricity);
	double dR             = sqrt( position.fX*position.fX + position.fY*position.fY + dEZR*dEZR);
	location.degLatitude  = asin( dEZR / dR ) * c_dRadToDeg;
	double dSinLatitude   = sin( location.degLatitude * c_dDegToRad );
	double dEarthFactor   = sqrt( 1.0 - c_dEarthEccentricity * dSinLatitude * dSinLatitude );
	location.degLongitude = atan2 (position.fY, position.fX ) * c_dRadToDeg;
	location.fAltitude    =  (float)(dR - c_dEarthKmRadius / dEarthFactor);

	return location;
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSVECTORD position ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double dEZR           = position.dZ / (1.0 - c_dEarthEccentricity);
	double dR             = sqrt( position.dX*position.dX + position.dY*position.dY + dEZR*dEZR);
	location.degLatitude  = asin( dEZR / dR ) * c_dRadToDeg;
	double dSinLatitude   = sin( location.degLatitude * c_dDegToRad );
	double dEarthFactor   = sqrt( 1.0 - c_dEarthEccentricity * dSinLatitude * dSinLatitude );
	location.degLongitude = atan2 (position.dY, position.dX ) * c_dRadToDeg;
	location.fAltitude    =  (float)(dR - c_dEarthKmRadius / dEarthFactor);

	return location;
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSCOORD sat ) const
{

	//*****************************************
	// NOTE : Assumes StdEarthFixed Coordinates
	//*****************************************

	
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosCTA, sinCTA;

	EMSVECTOR E0 = { 0.0, 0.0, 0.0 };
	EMSVECTOR T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR V1 = CEMSVector::Normalize( sat.radius );
	EMSVECTOR V2 = CEMSVector::Normalize( sat.velocity );
	EMSVECTOR ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( V1,  (float)cosCTA );
	T2 = CEMSVector::Mult( ON,  (float)sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  (float)c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSCOORDD sat ) const
{

	//*****************************************
	// NOTE : Assumes StdEarthFixed Coordinates
	//*****************************************

	
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosCTA, sinCTA;

	EMSVECTORD E0 = { 0.0, 0.0, 0.0 };
	EMSVECTORD T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD V1 = CEMSVector::Normalize( sat.radius );
	EMSVECTORD V2 = CEMSVector::Normalize( sat.velocity );
	EMSVECTORD ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( V1,  cosCTA );
	T2 = CEMSVector::Mult( ON,  sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSTIMECOORD sat ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosCTA, sinCTA;

	// Use StdEarthFixed Coordinates
	sat = ToStdEarthFixed( sat );

	EMSVECTOR E0 = { 0.0, 0.0, 0.0 };
	EMSVECTOR T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR V1 = CEMSVector::Normalize( sat.coord.radius );
	EMSVECTOR V2 = CEMSVector::Normalize( sat.coord.velocity );
	EMSVECTOR ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( V1,  (float)cosCTA );
	T2 = CEMSVector::Mult( ON,  (float)sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  (float)c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSTIMECOORDD sat ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosCTA, sinCTA;

	// Use StdEarthFixed Coordinates
	sat = ToStdEarthFixed( sat );

	EMSVECTORD E0 = { 0.0, 0.0, 0.0 };
	EMSVECTORD T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD V1 = CEMSVector::Normalize( sat.coord.radius );
	EMSVECTORD V2 = CEMSVector::Normalize( sat.coord.velocity );
	EMSVECTORD ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( V1,  cosCTA );
	T2 = CEMSVector::Mult( ON,  sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSTIMECOORD sat1, EMSTIMECOORD sat2 ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosBeta1, sinBeta1, Beta0, Beta1;
	double cosCTA, sinCTA;
	double dTest;

	__int64 idt0 = sat2.vTime.intTime-sat1.vTime.intTime;
	__int64 idt1 = a.tca.intTime-sat1.vTime.intTime;

	EMSVECTOR E0 = { 0.0, 0.0, 0.0 };
	EMSVECTOR B0 = { 0.0, 0.0, 0.0 };
	EMSVECTOR T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTOR V1 = CEMSVector::Normalize( sat1.coord.radius );
	EMSVECTOR V2 = CEMSVector::Normalize( sat2.coord.radius );
	EMSVECTOR ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	EMSVECTOR V3 = CEMSVector::CrossProduct( ON, V1 );
	V3 = CEMSVector::Normalize( V3 );

	// Test V3 direction
	dTest = CEMSVector::DotProduct( V3, V2 );
	if ( dTest < 0.0 ) V3 = CEMSVector::Mult( V3, -1.0 );

	Beta0 = acos( CEMSVector::DotProduct( V1, V2 ) );
	Beta1 = Beta0 * double ( idt1 ) / double ( idt0 );

	sinBeta1 = sin(Beta1);
	cosBeta1 = cos(Beta1);

	T1 = CEMSVector::Mult( V1, (float)cosBeta1 );
	T2 = CEMSVector::Mult( V3, (float)sinBeta1 ); 
	B0 = CEMSVector::Add( T1, T2 ); 
	B0 = CEMSVector::Normalize( B0 );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( B0,  (float)cosCTA );
	T2 = CEMSVector::Mult( ON,  (float)sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  (float)c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}

EMSLOCATION CEMSCoordSystem::ToGeodetic( EMSTCACTA a, EMSTIMECOORDD sat1, EMSTIMECOORDD sat2 ) const
{
	EMSLOCATION location  = { 0.0, 0.0, 0.0 };
	double cosBeta1, sinBeta1, Beta0, Beta1;
	double cosCTA, sinCTA;
	double dTest;

	__int64 idt0 = sat2.vTime.intTime-sat1.vTime.intTime;
	__int64 idt1 = a.tca.intTime-sat1.vTime.intTime;

	EMSVECTORD E0 = { 0.0, 0.0, 0.0 };
	EMSVECTORD B0 = { 0.0, 0.0, 0.0 };
	EMSVECTORD T1 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD T2 = { 0.0, 0.0, 0.0 };	// temporary vector
	EMSVECTORD V1 = CEMSVector::Normalize( sat1.coord.radius );
	EMSVECTORD V2 = CEMSVector::Normalize( sat2.coord.radius );
	EMSVECTORD ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	EMSVECTORD V3 = CEMSVector::CrossProduct( ON, V1 );
	V3 = CEMSVector::Normalize( V3 );

	// Test V3 direction
	dTest = CEMSVector::DotProduct( V3, V2 );
	if ( dTest < 0.0 ) V3 = CEMSVector::Mult( V3, -1.0 );

	Beta0 = acos( CEMSVector::DotProduct( V1, V2 ) );
	Beta1 = Beta0 * double ( idt1 ) / double ( idt0 );

	sinBeta1 = sin(Beta1);
	cosBeta1 = cos(Beta1);

	T1 = CEMSVector::Mult( V1, cosBeta1 );
	T2 = CEMSVector::Mult( V3, sinBeta1 ); 
	B0 = CEMSVector::Add( T1, T2 ); 
	B0 = CEMSVector::Normalize( B0 );

	sinCTA = sin( a.cta * c_dDegToRad );
	cosCTA = cos( a.cta * c_dDegToRad );
	
	T1 = CEMSVector::Mult( B0,  cosCTA );
	T2 = CEMSVector::Mult( ON,  sinCTA ); 
	E0 = CEMSVector::Add( T1, T2 ); 
	E0 = CEMSVector::Normalize( E0 );
	E0 = CEMSVector::Mult( E0,  c_dEarthKmRadius ); 

	return ToGeodetic( E0 );
}


EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSLOCATION location, EMSTIMECOORD sat1, EMSTIMECOORD sat2 ) const
{
	EMSVECTOR position = ToEarthFixed( location );
	EMSTCACTA a = ToTcaCta( position, sat1, sat2 );

	return a; 
}

EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSLOCATION location, EMSTIMECOORDD sat1, EMSTIMECOORDD sat2 ) const
{
	EMSVECTORD position = ToEarthFixedDouble( location );
	EMSTCACTA a = ToTcaCta( position, sat1, sat2 );

	return a; 
}


EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSLOCATION location, LPEMSTIMECOORD lpSatvec, ULONG ulCount ) const
{

	EMSVECTOR position = ToEarthFixed( location );
	EMSTCACTA a;
	
	// Establish initial values
	a = ToTcaCta( position, lpSatvec[0], lpSatvec[ulCount-1] );

	// Perform extra processing to get accurate TCA

	EMSRANGERATE *lpRangeRate = new EMSRANGERATE[ulCount];

	CEMSRangeRate::Calculate( position, lpSatvec, ulCount, lpRangeRate );


	double dDeltaRRate  = 0.0;
	INT64 i64DeltaTime = 0;
	int   nIndex1      = 0;
	int   nIndex2      = ulCount-1;

	for ( int i = 0; i < (int)ulCount-1; i++ )
	{
		if ( lpRangeRate[i].fRangeRate * lpRangeRate[i+1].fRangeRate < 0.0 )
		{	

			a = ToTcaCta( position, lpSatvec[i], lpSatvec[i+1] );

			i64DeltaTime = lpRangeRate[i+1].vTime.intTime - lpRangeRate[i].vTime.intTime;		
			dDeltaRRate = lpRangeRate[i+1].fRangeRate - lpRangeRate[i].fRangeRate;
			a.tca.intTime = lpRangeRate[i].vTime.intTime 
					- i64DeltaTime * INT64 ( lpRangeRate[i].fRangeRate / dDeltaRRate );
			break;
		}

	}


	if ( lpRangeRate )
	{
		delete [] lpRangeRate;
		lpRangeRate = 0;
	}

	return a; 
}

EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSLOCATION location, LPEMSTIMECOORDD lpSatvec, ULONG ulCount ) const
{

	EMSVECTORD position = ToEarthFixedDouble( location );
	EMSTCACTA a;
	
	// Establish initial values
	a = ToTcaCta( position, lpSatvec[0], lpSatvec[ulCount-1] );

	// Perform extra processing to get accurate TCA

	EMSRANGERATED *lpRangeRate = new EMSRANGERATED[ulCount];

	CEMSRangeRate::Calculate( position, lpSatvec, ulCount, lpRangeRate );


	double dDeltaRRate  = 0.0;
	INT64 i64DeltaTime = 0;
	int   nIndex1      = 0;
	int   nIndex2      = ulCount-1;

	for ( int i = 0; i < (int)ulCount-1; i++ )
	{
		if ( lpRangeRate[i].dRangeRate * lpRangeRate[i+1].dRangeRate < 0.0 )
		{	

			a = ToTcaCta( position, lpSatvec[i], lpSatvec[i+1] );

			i64DeltaTime = lpRangeRate[i+1].vTime.intTime - lpRangeRate[i].vTime.intTime;		
			dDeltaRRate = lpRangeRate[i+1].dRangeRate - lpRangeRate[i].dRangeRate;
			a.tca.intTime = lpRangeRate[i].vTime.intTime 
					- i64DeltaTime * INT64 ( lpRangeRate[i].dRangeRate / dDeltaRRate );
			break;
		}

	}


	if ( lpRangeRate )
	{
		delete [] lpRangeRate;
		lpRangeRate = 0;
	}

	return a; 
}

EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSVECTOR position, EMSTIMECOORD sat1, EMSTIMECOORD sat2 ) const
{
	EMSTCACTA a;
	double dBeta0, dBeta1, dBeta2, dCosCTA, dCosAngle, dDeltaTime;
	INT64 i64DT;

	EMSVECTOR E0 = CEMSVector::Normalize( position );
	EMSVECTOR V1 = CEMSVector::Normalize( sat1.coord.radius );
	EMSVECTOR V2 = CEMSVector::Normalize( sat2.coord.radius );
	EMSVECTOR ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	a.cta = asin( CEMSVector::DotProduct( E0, ON ) );

	dCosCTA = cos(a.cta);

	dBeta0 = acos( CEMSVector::DotProduct( V1, V2 ) );

	if ( fabs( dBeta0 ) < 1e-7 )
		dBeta0 = 1e-7;

	dCosAngle = CEMSVector::DotProduct( E0, V1 ) / dCosCTA;
 
	if ( dCosAngle > 1.0 )
		dCosAngle = 1.0;
	else if ( dCosAngle < -1.0 )
		dCosAngle = -1.0;

	dBeta1 = acos( dCosAngle );

	dCosAngle = CEMSVector::DotProduct( E0, V2 ) / dCosCTA;
 
	if ( dCosAngle > 1.0 )
		dCosAngle = 1.0;
	else if ( dCosAngle < -1.0 )
		dCosAngle = -1.0;

	dBeta2 = acos( dCosAngle );

	if ( dBeta2 > dBeta0 )
		dBeta1 = - dBeta1;

	i64DT = sat2.vTime.intTime - sat1.vTime.intTime;

	dDeltaTime = dBeta1/dBeta0;

	dDeltaTime *= (double)i64DT;
	
	a.tca.intTime = sat1.vTime.intTime + INT64( dDeltaTime );

	a.cta *=  c_dRadToDeg;

	return a;
}

EMSTCACTA CEMSCoordSystem::ToTcaCta( EMSVECTORD position, EMSTIMECOORDD sat1, EMSTIMECOORDD sat2 ) const
{
	EMSTCACTA a;
	double dBeta0, dBeta1, dBeta2, dCosCTA, dCosAngle, dDeltaTime;
	INT64 i64DT;

	EMSVECTORD E0 = CEMSVector::Normalize( position );
	EMSVECTORD V1 = CEMSVector::Normalize( sat1.coord.radius );
	EMSVECTORD V2 = CEMSVector::Normalize( sat2.coord.radius );
	EMSVECTORD ON = CEMSVector::CrossProduct( V1, V2 );
	ON = CEMSVector::Normalize( ON );

	a.cta = asin( CEMSVector::DotProduct( E0, ON ) );

	dCosCTA = cos(a.cta);

	dBeta0 = acos( CEMSVector::DotProduct( V1, V2 ) );

	if ( fabs( dBeta0 ) < 1e-7 )
		dBeta0 = 1e-7;

	dCosAngle = CEMSVector::DotProduct( E0, V1 ) / dCosCTA;
 
	if ( dCosAngle > 1.0 )
		dCosAngle = 1.0;
	else if ( dCosAngle < -1.0 )
		dCosAngle = -1.0;

	dBeta1 = acos( dCosAngle );

	dCosAngle = CEMSVector::DotProduct( E0, V2 ) / dCosCTA;
 
	if ( dCosAngle > 1.0 )
		dCosAngle = 1.0;
	else if ( dCosAngle < -1.0 )
		dCosAngle = -1.0;

	dBeta2 = acos( dCosAngle );

	if ( dBeta2 > dBeta0 )
		dBeta1 = - dBeta1;

	i64DT = sat2.vTime.intTime - sat1.vTime.intTime;

	dDeltaTime = dBeta1/dBeta0;

	dDeltaTime *= (double)i64DT;
	
	a.tca.intTime = sat1.vTime.intTime + INT64( dDeltaTime );

	a.cta *=  c_dRadToDeg;

	return a;
}

EMSTIMECOORD CEMSCoordSystem::ToInertial( EMSTIMECOORD srcCoord ) const
{
	EMSTIMECOORD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial: // nothing to do
			destCoord = srcCoord;
			break;

		case COORDSYS_EarthFixed:
			destCoord = _EarthFixedToInertial( srcCoord );
			break;

		case COORDSYS_StdEarthFixed:
			srcCoord = _StdEarthFixedToEarthFixed( srcCoord );

			destCoord = _EarthFixedToInertial( srcCoord );
			break;
	}

	return destCoord;

}

EMSTIMECOORDD CEMSCoordSystem::ToInertial( EMSTIMECOORDD srcCoord ) const
{
	EMSTIMECOORDD destCoord;

	switch ( srcCoord.coordSystem )
	{
		case COORDSYS_Inertial: // nothing to do
			destCoord = srcCoord;
			break;

		case COORDSYS_EarthFixed:
			destCoord = _EarthFixedToInertial( srcCoord );
			break;

		case COORDSYS_StdEarthFixed:
			srcCoord = _StdEarthFixedToEarthFixed( srcCoord );

			destCoord = _EarthFixedToInertial( srcCoord );
			break;
	}

	return destCoord;

}

EMSVECTOR CEMSCoordSystem::EarthFixedVelocity( EMSLOCATION srcLocation ) const
{
	return EarthFixedVelocity( ToEarthFixed( srcLocation ) );
}

EMSVECTORD CEMSCoordSystem::EarthFixedVelocityDouble( EMSLOCATION srcLocation ) const
{
	return EarthFixedVelocity( ToEarthFixedDouble( srcLocation ) );
}

EMSVECTOR CEMSCoordSystem::EarthFixedVelocity( EMSVECTOR vLoc ) const
{
	EMSVECTOR vVelocity;

	vVelocity.fX =  - (float)( c_radEarthRotationRate * vLoc.fY );

	vVelocity.fY =    (float)( c_radEarthRotationRate * vLoc.fX );

	vVelocity.fZ =  0.0;

	return vVelocity;
}

EMSVECTORD CEMSCoordSystem::EarthFixedVelocity( EMSVECTORD vLoc ) const
{
	EMSVECTORD vVelocity;

	vVelocity.dX =  - ( c_radEarthRotationRate * vLoc.dY );

	vVelocity.dY =    ( c_radEarthRotationRate * vLoc.dX );

	vVelocity.dZ =  0.0;

	return vVelocity;
}

EMSTIMECOORD CEMSCoordSystem::EarthFixedToInertial( EMSVECTOR vLoc, EMSTIME t ) const
{
	EMSTIMECOORD srcCoord;

	memset( &srcCoord, 0, sizeof( srcCoord ) );

	srcCoord.coordSystem = COORDSYS_EarthFixed;

	srcCoord.vTime = t;

	srcCoord.coord.radius = vLoc;

	srcCoord.coord.velocity = EarthFixedVelocity( srcCoord.coord.radius );

	return _EarthFixedToInertial( srcCoord );
}

EMSTIMECOORDD CEMSCoordSystem::EarthFixedToInertial( EMSVECTORD vLoc, EMSTIME t ) const
{
	EMSTIMECOORDD srcCoord;

	memset( &srcCoord, 0, sizeof( srcCoord ) );

	srcCoord.coordSystem = COORDSYS_EarthFixed;

	srcCoord.vTime = t;

	srcCoord.coord.radius = vLoc;

	srcCoord.coord.velocity = EarthFixedVelocity( srcCoord.coord.radius );

	return _EarthFixedToInertial( srcCoord );
}

EMSTIMECOORD CEMSCoordSystem::_EarthFixedToInertial( EMSTIMECOORD srcCoord ) const
{
//----------------------------------------------------------------------//
//                                                                      //
// Description:                                                         //
//                                                                      //
//      Subroutine to transform earth fixed space into inertial space,  //
// at time t in nanosecs from 1970.                                     //
//                                                                      //
//----------------------------------------------------------------------//

	EMSTIMECOORD destCoord;
	double dGST = CEMSEarth::GreenwichSiderealTime( srcCoord.vTime );
	double dCosA = cos( dGST ), dSinA = sin( dGST );

	destCoord.coordSystem = COORDSYS_Inertial;

	destCoord.vTime = srcCoord.vTime;

	destCoord.coord.radius.fX =  (float)(( dCosA * srcCoord.coord.radius.fX ) - 
											( dSinA * srcCoord.coord.radius.fY ));

	destCoord.coord.radius.fY = (float)(( dSinA * srcCoord.coord.radius.fX ) + 
											( dCosA * srcCoord.coord.radius.fY ));

	destCoord.coord.radius.fZ = srcCoord.coord.radius.fZ;

//	destCoord.coord.velocity.fX =  (float)(( dCosA * srcCoord.coord.velocity.fX ) - 
//							( dSinA * srcCoord.coord.velocity.fY ) - 
//							( c_radEarthRotationRate * destCoord.coord.radius.fY ));

//	destCoord.coord.velocity.fY = (float)(( dSinA * srcCoord.coord.velocity.fX ) + 
//												( dCosA * srcCoord.coord.velocity.fY ) + 
//												( c_radEarthRotationRate * destCoord.coord.radius.fX ));

	destCoord.coord.velocity.fX =  (float)(( dCosA * srcCoord.coord.velocity.fX ) - 
											( dSinA * srcCoord.coord.velocity.fY ) ); 

	destCoord.coord.velocity.fY = (float)(( dSinA * srcCoord.coord.velocity.fX ) + 
											( dCosA * srcCoord.coord.velocity.fY ) ); 

	destCoord.coord.velocity.fZ = srcCoord.coord.velocity.fZ;

	return destCoord;
}

EMSTIMECOORDD CEMSCoordSystem::_EarthFixedToInertial( EMSTIMECOORDD srcCoord ) const
{
//----------------------------------------------------------------------//
//                                                                      //
// Description:                                                         //
//                                                                      //
//      Subroutine to transform earth fixed space into inertial space,  //
// at time t in nanosecs from 1970.                                     //
//                                                                      //
//----------------------------------------------------------------------//

	EMSTIMECOORDD destCoord;
	double dGST = CEMSEarth::GreenwichSiderealTime( srcCoord.vTime );
	double dCosA = cos( dGST ), dSinA = sin( dGST );

	destCoord.coordSystem = COORDSYS_Inertial;

	destCoord.vTime = srcCoord.vTime;

	destCoord.coord.radius.dX =  (( dCosA * srcCoord.coord.radius.dX ) - 
											( dSinA * srcCoord.coord.radius.dY ));

	destCoord.coord.radius.dY = (( dSinA * srcCoord.coord.radius.dX ) + 
											( dCosA * srcCoord.coord.radius.dY ));

	destCoord.coord.radius.dZ = srcCoord.coord.radius.dZ;

//	destCoord.coord.velocity.dX =  (( dCosA * srcCoord.coord.velocity.dX ) - 
//							( dSinA * srcCoord.coord.velocity.dY ) - 
//							( c_radEarthRotationRate * destCoord.coord.radius.dY ));

//	destCoord.coord.velocity.dY = (( dSinA * srcCoord.coord.velocity.dX ) + 
//												( dCosA * srcCoord.coord.velocity.dY ) + 
//												( c_radEarthRotationRate * destCoord.coord.radius.dX ));

	destCoord.coord.velocity.dX =  (( dCosA * srcCoord.coord.velocity.dX ) - 
											( dSinA * srcCoord.coord.velocity.dY ) ); 

	destCoord.coord.velocity.dY = (( dSinA * srcCoord.coord.velocity.dX ) + 
											( dCosA * srcCoord.coord.velocity.dY ) ); 

	destCoord.coord.velocity.dZ = srcCoord.coord.velocity.dZ;

	return destCoord;
}

double CEMSCoordSystem::DistanceApart( EMSLOCATION locA, EMSLOCATION locB ) const
{
	double dDistance = 0.0, dXSQ, dYSQ, dZSQ;
	EMSVECTORD v1, v2;

	v1 = ToEarthFixedDouble( locA );

	v2 = ToEarthFixedDouble( locB );

	dXSQ = ( v1.dX - v2.dX ) *	( v1.dX - v2.dX );

	dYSQ = ( v1.dY - v2.dY ) *	( v1.dY - v2.dY );

	dZSQ = ( v1.dZ - v2.dZ ) *	( v1.dZ - v2.dZ );

	dDistance =  sqrt( dXSQ + dYSQ + dZSQ );

	return dDistance;
}

EMSTIMECOORDD CEMSCoordSystem::PZ90toWGS84( EMSTIMECOORDD satPZ90 ) const
{
	EMSTIMECOORDD satWGS84;
	//EMSVECTORD vDelta = { -1.08, -0.27, -0.9 };
	//double scaleFactor = 1.0 - 0.12e-6;
	//double rotationFactor = 0.82e-6;

	// Conversion excludes rotation and scale factor only small offset since 2007
	EMSVECTORD vDelta = { 0, 0, 0 };
	double scaleFactor = 1.0;
	double rotationFactor = 0.0;

	memset( &satWGS84, 0, sizeof( satPZ90 ) );

	satWGS84.vTime = satPZ90.vTime;

	satWGS84.coordSystem = COORDSYS_StdEarthFixed;

	satWGS84.coord.radius.dX = scaleFactor * ( satPZ90.coord.radius.dX
									- rotationFactor * satPZ90.coord.radius.dY )
									+ vDelta.dX;
	satWGS84.coord.radius.dY = scaleFactor * ( satPZ90.coord.radius.dY
									+ rotationFactor * satPZ90.coord.radius.dX )
									+ vDelta.dY;
	satWGS84.coord.radius.dZ = scaleFactor * satPZ90.coord.radius.dZ
									+ vDelta.dZ;
	

	satWGS84.coord.velocity.dX = scaleFactor * ( satPZ90.coord.velocity.dX
									- rotationFactor * satPZ90.coord.velocity.dY );
	satWGS84.coord.velocity.dY = scaleFactor * ( satPZ90.coord.velocity.dY
									+ rotationFactor * satPZ90.coord.velocity.dX );
	satWGS84.coord.velocity.dZ = scaleFactor * satPZ90.coord.velocity.dZ;

	return satWGS84;
}

