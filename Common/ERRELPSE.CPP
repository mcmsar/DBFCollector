/******************************************************************** 
*	Module:			ErrElpse.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSErrorEllipse
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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

	0.0	2004 Oct 6 rvw	start

********************************************************************/
#include <math.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "errelpse.h"
#include "emsclock.h"
#include "emsencod.h"
#include "emsconst.h"

#define SIND(a)		   (sin(a * c_dDegToRad))
#define COSD(a)        (cos(a * c_dDegToRad))
#define ATAND(a)       (c_dRadToDeg * atan(a))
#define ATAN2D(a,b)    (c_dRadToDeg * atan2(a,b))

#define ALPHA_ALPHA		(0)

#define ALPHA_BETA		(1)
#define BETA_ALPHA		(1)

#define ALPHA_FBIAS		(2)
#define FBIAS_ALPHA		(2)
#define ALPHA_DRIFT		(3)
#define DRIFT_ALPHA		(3)
#define BETA_BETA		(4)
#define BETA_FBIAS		(5)
#define FBIAS_BETA		(5)
#define BETA_DRIFT		(6)
#define DRIFT_BETA		(6)
#define FBIAS_FBIAS		(7)
#define FBIAS_DRIFT		(8)
#define DRIFT_FBIAS		(8)
#define DRIFT_DRIFT		(9)

const CEMSSystemClock c_sysClock;
const	double c_dMaxAgeInHours = 24.0 * 10.0;		// ten days
const double c_dMaxDistance = 20000.0;	// max magnitude allowed
const double c_dPi = atan(1.0) * 4.0;
const int c_nMinSolnCount = 10;	// mininum no# of solutions
const double c_dMinOrbitError = 0.0;
const double c_dMaxOrbitError = 3.0;
const double c_dOrbitErrorStep = 0.1;
const TCHAR c_szSatIDFmt[] = TEXT("%03ld");

CEMSErrorEllipse::CEMSErrorEllipse()
{
}

CEMSErrorEllipse::~CEMSErrorEllipse()
{
}


EMSEETYPE CEMSErrorEllipse::GetBaseType( WORD wLocType )
{
	EMSEETYPE type = EMSLAT_Unknown;

	switch ( wLocType & EMSLOCTYPE_REAL_BASE_MASK )
	{
		case	EMSLOCTYPE_406_SARP:			type = EMSLAT_SARP; break;
		case	EMSLOCTYPE_406_SARR:			type = EMSLAT_SARR; break;
		case	EMSLOCTYPE_406_SARP_SARR:	type = EMSLAT_SARRSARP; break;

		case	EMSLOCTYPE_406_FDOA_SARR:
		case	EMSLOCTYPE_406_FDOA_SARP:
		case	EMSLOCTYPE_406_FDOA_SARP_SARR:
		case	EMSLOCTYPE_406_FDOA: 		type = EMSLAT_FDOA; break;

		case	EMSLOCTYPE_406_TDOA :		break;
		case	EMSLOCTYPE_CBC_121 :			type = EMSLAT_CBC_121; break;
		case	EMSLOCTYPE_CBC_243 :			type = EMSLAT_CBC_243; break;
		case	EMSLOCTYPE_CBC_121_243 :	type = EMSLAT_CBC_121; break;
		case	EMSLOCTYPE_CBC_406 :			type = EMSLAT_CBC_406; break;
		default:									break;
	}
	return type;
}

EMSEETYPE CEMSErrorEllipse::GetType( LPEMSLOCATE lpLocnRecord )
{
	EMSEETYPE type = EMSLAT_Unknown;

	if ( lpLocnRecord )
	{
		type = GetBaseType( lpLocnRecord->wType );

		if ( ( EMSLAT_Unknown != type ) && ( false == IsNominalSoln( lpLocnRecord ) ) )
			type = (EMSEETYPE)(type | EMSLAT_Marginal);
	}

	return type;
}

bool CEMSErrorEllipse::IsNominalSoln( LPEMSLOCATE lpSoln )
{
	bool bNominal = false;

	if ( lpSoln )
	{
		const double c_dNomCtaMin    = 1.0;    // deg
		const double c_dNomCtaMax    = 20.0;   // deg
		const int    c_nNom406PtsMin = 4;
		const int    c_dNomCbcDurMin = 240;    // seconds

		bNominal = (fabs( lpSoln->fCrossTrackAngle ) >= c_dNomCtaMin)    &&
           (fabs( lpSoln->fCrossTrackAngle ) <= c_dNomCtaMax)    &&
           (lpSoln->timeTCA.intTime >= lpSoln->timeFirstData.intTime) &&
           (lpSoln->timeTCA.intTime <= lpSoln->timeLastData.intTime);

		if ( bNominal )
 		{
			if ( EMSLOCTYPE_CBC == ( lpSoln->wType & EMSLOCTYPE_CBC ) )
			{
				bNominal = ( ( lpSoln->timeLastData.intTime -
							lpSoln->timeFirstData.intTime )/1e9 >= c_dNomCbcDurMin );
			}
			else
			{
				bNominal = ( lpSoln->wlsSolution.wNumMsgsUsed >= c_nNom406PtsMin );
			}
		}
	}

	return bNominal;
}

// returns spheroidal distance between two points in kilometers

double CEMSErrorEllipse::_CalcDistance( EMSLOCATIOND locA, EMSLOCATION locB )
{
	double ld_return, ld_radius0, ld_radiusX, ld_x1, ld_x2, ld_y1, ld_y2, ld_z1, ld_z2;
	double ld_earth = 6378.137;       // WGS84 equatorial radius in km
	double ld_oblat = 0.00669438002;  // factor derived from WGS84 flattening ratio
	double ld_lat1, ld_lon1, ld_lat2, ld_lon2;

	// convert degrees to radians
	ld_lat1 = locA.degLatitude * (c_dPi * 2/360);
	ld_lon1 = locA.degLongitude * (c_dPi * 2/360);
	ld_lat2 = locB.degLatitude * (c_dPi * 2/360);
	ld_lon2 = locB.degLongitude * (c_dPi * 2/360);

	// Compute cartesian geocentric coordinates (x, y, z) for both positions. 

	ld_radius0 = ld_earth * (1.0 - ld_oblat * (sin(ld_lat1) * sin(ld_lat1)));
	ld_radiusX = ld_earth * (1.0 - ld_oblat * (sin(ld_lat2) * sin(ld_lat2)));

	ld_x1 = ld_radiusX * cos(ld_lat2) * cos(ld_lon2);
	ld_y1 = ld_radiusX * cos(ld_lat2) * sin(ld_lon2);
	ld_z1 = ld_radiusX * sin(ld_lat2);

	ld_x2 = ld_radius0 * cos(ld_lat1) * cos(ld_lon1);
	ld_y2 = ld_radius0 * cos(ld_lat1) * sin(ld_lon1);
	ld_z2 = ld_radius0 * sin(ld_lat1);

	// solve for the distance between the two points
	ld_return = sqrt( pow(ld_x2 - ld_x1,2) + pow(ld_y2 - ld_y1,2) + pow( ld_z2 - ld_z1 , 2 ) );

	return ld_return;
}

EMS_RESULT CEMSErrorEllipse::CalcErrEllipse( LPEMSWLSLOCATE lpSoln, double dOrbitError, double dScaleFactor )
{
	HRESULT hr = EMS_OK;
	const double c_dMaxEECorrelation		 = 0.99;

	if ( lpSoln )
	{
		double ErrorAlpha = sqrt( fabs( lpSoln->fCoVarianceMatrix[ ALPHA_ALPHA ])  );
		double ErrorBeta = sqrt( fabs(lpSoln->fCoVarianceMatrix[ BETA_BETA ])  );
		double CorrAlphaBeta = lpSoln->fCoVarianceMatrix[ ALPHA_BETA ] / ErrorAlpha / ErrorBeta;

		// Limit correlation coefficient to range less than 1
		if ( CorrAlphaBeta > c_dMaxEECorrelation ) 
			CorrAlphaBeta = c_dMaxEECorrelation;
		if ( CorrAlphaBeta < -c_dMaxEECorrelation ) 
			CorrAlphaBeta = -c_dMaxEECorrelation;

		// rotate error ellipse
		lpSoln->fHeading = (float) (0.5 * ATAN2D(2.0*ErrorAlpha*ErrorBeta*CorrAlphaBeta,
									ErrorAlpha*ErrorAlpha - ErrorBeta*ErrorBeta) );

		double sh  = SIND (lpSoln->fHeading);
		double ch  = COSD (lpSoln->fHeading);
		double vn  = (ErrorAlpha * c_dEarthKmRadius * c_dDegToRad );
		double ve  = (ErrorBeta  * c_dEarthKmRadius * c_dDegToRad );
		double cen = CorrAlphaBeta;

		double orberr = dOrbitError * dOrbitError; // Orbit error to be included in error ellipse (km)

		lpSoln->fMajorError  = (float) sqrt( fabs ((vn*ch)*(vn*ch) + (ve*sh)*(ve*sh) + 2.0*ve*vn*cen*sh*ch));
		lpSoln->fMinorError  = (float) sqrt( fabs ((ve*ch)*(ve*ch) + (vn*sh)*(vn*sh) - 2.0*ve*vn*cen*sh*ch));
		lpSoln->fMajorError *= (float) dScaleFactor;
		lpSoln->fMinorError *= (float) dScaleFactor;

		// add orbit error term
		lpSoln->fMajorError = (float) sqrt(lpSoln->fMajorError * lpSoln->fMajorError + orberr);
		lpSoln->fMinorError = (float) sqrt(lpSoln->fMinorError * lpSoln->fMinorError + orberr);
    
		// swap major and minor axes if necessary
		if (lpSoln->fMajorError < lpSoln->fMinorError)
		{
			float ftemp = lpSoln->fMajorError;
			lpSoln->fMajorError = lpSoln->fMinorError;
			lpSoln->fMinorError = ftemp;
        	lpSoln->fHeading -= 90.0;
		}
    
		// adjust range of heading angle 
		if (lpSoln->fHeading > 90.0) lpSoln->fHeading -= 180.0;

		lpSoln->fRadiusErrEllipse = (float) sqrt (lpSoln->fMajorError*lpSoln->fMajorError
		                             	+ lpSoln->fMinorError*lpSoln->fMinorError);
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMSEEFACTOR CEMSErrorEllipse::GetNominalEESettings( EMSEETYPE type, 
												EMSEECONFIGDATA *lpEESettings )
{
	type = (EMSEETYPE)(( ULONG)type & ~(ULONG)EMSLAT_Marginal );

	return GetEESettings( type, lpEESettings );
}

EMSEEFACTOR CEMSErrorEllipse::GetMarginalEESettings( EMSEETYPE type, 
												EMSEECONFIGDATA *lpEESettings )
{
	type = (EMSEETYPE)(( ULONG)type | (ULONG)EMSLAT_Marginal );

	return GetEESettings( type, lpEESettings );
}

EMSEEFACTOR CEMSErrorEllipse::GetEESettings( EMSEETYPE type, 
												EMSEECONFIGDATA *lpEESettings )
{
	EMSEEFACTOR ee;
	EMSEECOEFFICIENT eeInfo;

	eeInfo.dScaleFactor = 1.0;
	eeInfo.dAdjustment = 0.0;

	if ( lpEESettings )
	{
		switch ( type )
		{
			case EMSLAT_SARR:
				eeInfo = lpEESettings->nominal.type406.cfSarr;
				break;

			case EMSLAT_Marginal_SARR:
				eeInfo = lpEESettings->marginal.type406.cfSarr;
				break;

			case EMSLAT_SARP:
				eeInfo = lpEESettings->nominal.type406.cfSarp;
				break;

			case EMSLAT_Marginal_SARP:
				eeInfo = lpEESettings->marginal.type406.cfSarp;
				break;

			case EMSLAT_SARRSARP:
				eeInfo = lpEESettings->nominal.type406.cfSarrSarp;
				break;

			case EMSLAT_Marginal_SARRSARP:
				eeInfo = lpEESettings->marginal.type406.cfSarrSarp;
				break;

			case EMSLAT_FDOA:
				eeInfo = lpEESettings->nominal.typeFDOA.cfSarr;
				break;

			case EMSLAT_Marginal_FDOA:
				eeInfo = lpEESettings->marginal.typeFDOA.cfSarr;
				break;

			case EMSLAT_CBC_121:
				eeInfo = lpEESettings->nominal.typeCBC.cf121;
				break;

			case EMSLAT_Marginal_CBC_121:
				eeInfo = lpEESettings->marginal.typeCBC.cf121;
				break;

			case EMSLAT_CBC_243:
				eeInfo = lpEESettings->nominal.typeCBC.cf243;
				break;

			case EMSLAT_Marginal_CBC_243:
				eeInfo = lpEESettings->marginal.typeCBC.cf243;
				break;

			case EMSLAT_CBC_406:
				eeInfo = lpEESettings->nominal.typeCBC.cf406;
				break;

			case EMSLAT_Marginal_CBC_406:
				eeInfo = lpEESettings->marginal.typeCBC.cf406;
				break;

			default:
				ee.dScaleFactor = 1.0;
				ee.dOrbitError = 0.0;
				break;
		}
	}

	ee.dScaleFactor = eeInfo.dScaleFactor;
	ee.dOrbitError = eeInfo.dAdjustment;

	return ee;
}

//	1 = inside ellipse, 0 = outside ellipse, -1 = error
//
int CEMSErrorEllipse::IsInEllipse( EMSWLSLOCATE wls, EMSLOCATION locnBeacon )
{
	EMSLOCATIOND locn;

	locn.degLatitude = locnBeacon.degLatitude;
	locn.degLongitude = locnBeacon.degLongitude;
	locn.dAltitude = locnBeacon.fAltitude;

	return IsInEllipse( wls, locn );
}

int CEMSErrorEllipse::IsInEllipse( EMSWLSLOCATE wls, EMSLOCATIOND locnBeacon )
{
	int nResult = -1;

//	if ( lpRecord )
	{
		// calculate distance from center ( calculated beacon location ) to foci

		if ( ( wls.fMajorError < c_dMaxDistance ) &&
			( wls.fMajorError > -c_dMaxDistance ) &&
			( wls.fMinorError < c_dMaxDistance ) &&
			( wls.fMinorError > -c_dMaxDistance ) )
		{
			double dSemiMajor=0.0, dSemiMinor=0.0, dFocalLength=0.0;
			double dRevHeading = 0.0;
			double dDistanceTotal, dDistance1, dDistance2;
			EMSLOCATION locF, locR;

			dSemiMajor = fabs( wls.fMajorError ) * 1000.0;

			dSemiMinor = fabs( wls.fMinorError ) * 1000.0;
			
			dFocalLength = sqrt( ( dSemiMajor * dSemiMajor ) -
 									( dSemiMinor * dSemiMinor ) );

			// calculate location of foci

			dRevHeading = wls.fHeading + 180.0;

			if ( dRevHeading > 360.0 )
				dRevHeading -= 360.0;

			// get distance from reference point (actual beacon location) to each focus

			locF = _ProjectLocation( wls.location, wls.fHeading, dFocalLength );

			locR = _ProjectLocation( wls.location, dRevHeading, dFocalLength );

			// compare sum of two distances to major axis length 
			// if less, point is inside the ellipse

			dDistance1 = 1000.0 * _CalcDistance( locnBeacon, locF );

			dDistance2 = 1000.0 * _CalcDistance( locnBeacon, locR );

			dDistanceTotal = fabs( dDistance1 ) + fabs( dDistance2 );

			if ( dDistanceTotal <= ( 2 * dSemiMajor ) )
				nResult = 1;	// inside
			else
				nResult = 0;	// outside

		}
	}

	return nResult;
}



////////////////////////////////////////////////////////
//  _ProjectLocation
//
//  Given a starting lat/long, distance, and direction,
//  returns the resulting lat/long. Uses the Vincenty
//  formula for calculating geodetic distance 
//  (thanks to Australian Geodetic Survey website)
//
//  Bob Leviton, Sept. 1999
/////////////////////////////////////////////////////////
EMSLOCATION CEMSErrorEllipse::_ProjectLocation( EMSLOCATION locOrig, double dAzim, double dDistance )
{
	EMSLOCATION locNew;
 
	// INPUT & CONVERSION
	double F10 = locOrig.degLatitude; // start lat (dec. degrees)     
	double G10 = locOrig.degLatitude * c_dPi/180;  // start lat (radians)
	double F11 = locOrig.degLongitude; // start long (dec. degrees)   
	double G11 = locOrig.degLongitude * c_dPi/180; // start long (radians)
	double F12 = dAzim; // input azimuth (dec. degrees)                               
	double G12 = dAzim * c_dPi/180; // input azimuth (radians)
	double G4 = dDistance; // input distance (meters)
	
	// ELLIPSOID PARAMETERS
	const double C9 = 6378137.0; // a (WGS84 ellipsoid radius)
	const double C11 = 0.0033528107; // f (WGS84 flattening)

	double C10 = C9 * (1-C11); // b
	double C12 = ((C9*C9) - (C10*C10)) / (C10*C10); // e to the power of i2

	// formula1
	double C16 = (1 - C11) * tan(G10); // tan U1
	double C17 = C16 / cos(G12); // tan sigma1

	// formula2
	double C19 = sin(atan(C16)); // sin U1
	double C20 = cos(atan(C16)); // cos U1
	double C21 = C20 * sin(G12); // sin alpha
	double C14 = cos(asin(C21)) * cos(asin(C21)) * ((C9*C9)-(C10*C10)) / (C10*C10); // u squared

	// formula3
	double C23 = 1 + C14 / 16384 * (4096 + C14 * (-768 + C14 * (320 - 175 * C14))); // A
	
	// formula4
	double C25 = C14 / 1024 * (256 + C14 * (-128 + C14 * (74 - 47 * C14))); // B
	
	// 100 iterations to resolve circular reference from spreadsheet:
	// formula7
	double C38, C27, F27, F28, F29, F30, F32, F33;
	double F36 = 0.0;  // initial value for circular reference (F36 <-> C38)
	for(int i = 0; i < 100; i++)
	{
		C38 = G4 / (C10 * C23) + F36; // sigma
		// formula5
		C27 = 2 * atan(C17) + C38; // 2 sigma m
		F27 = 2 * atan(C17); // 2 sigma1
		F28 = C25 * sin(C38); // B sin sigma
		F29  = cos(C27); // cos 2 sigma m
		F30 = cos(C38) * (-1 + 2 * F29 * F29); // cos sigma etc
		F32 = -3 + 4 * sin(C38) * sin(C38); //bracket1
		F33 = -3 + 4 * F29 * F29; // bracket2
		F36 = F28 * (F29 + C25 / 4 *(F30 - C25 / 6 * F29 * F32 * F33)); // delta sigma
	}
	// end iterations section
		
	// formula6
	double C36 = C25 * sin(C38) * (cos(C27) + (1/4) * C25 * (cos(C38) * (-1 + 2 * cos(C27) * cos(C27)) - (1/6) * C25 * cos(C27) * (-3 + 4 * sin(C38) * sin(C38)) * (-3 + 4 * cos(C27) * cos(C27)))); // delta sigma

	// formula8
	double C40 = sin(atan(C16)) * cos(C38) + cos(atan(C16)) * sin(C38) * cos(G12); // top term
	double C41 = (1-C11) * sqrt(C21 * C21 + (sin(atan(C16)) * sin(C38) - cos(atan(C16)) * cos(C38) * cos(G12)) * (sin(atan(C16)) * sin(C38) - cos(atan(C16)) * cos(C38) * cos(G12))); // bottom term
	double C42 = C40 / C41; // tan f2
	double C43 = atan(C42); // f2 (rad)
	double C44 = C43 * 180/ c_dPi; // f2 (deg)

	// formula9
	double C46 = sin(C38) * sin(G12) / (C20 * cos(C38) - sin(atan(C16)) * sin(C38) * cos(G12)); // tan lambda
	double C47 = atan2(sin(C38) * sin(G12), 
 	                   (C20 * cos(C38) - sin(atan(C16)) * sin(C38)*cos(G12))); // lambda (tan2)

	// formula10
	double C49 = C11 / 16 * cos(asin(C21)) * cos(asin(C21)) * (4 + C11 * (4 - 3 * cos(asin(C21)) * cos(asin(C21)))); // C

	// formula11
	double C51 = C47 - (1 - C49) * C11 * C21 * (C38 + C49 * sin(C38) * (cos(C27) + C49 * cos(C38) * (-1 + 2 * cos(C27) * cos(C27)))); // L
	double C52 = G11 + C51; // lambda2 (rad)
	double C53 = (C52 < 0) ? (C52 * 180 / c_dPi + 180) : (C52 * 180 / c_dPi); // lambda2 (deg)

	// formula12
	double C55 = C21 / (-sin(atan(C16)) * sin(C38) + C20 * cos(C38) * cos(G12)); // tan alpha2
	double C56 = atan(C55); // alpha2 (rad)
	double C57 = C56 * 180/c_dPi + 180; // alpha2 (deg)
	
	double F38 = G4 / (C10 * C23); // s/bA
	double F42 = atan2(C40, C41); // atan2 f2
	double F44 = F42 * 180 / c_dPi;  // final lat. (dec. Degrees)
	double F53 = C52 * 180 / c_dPi;  // final long (dec. Degrees )
	double F56 = atan2(C21, (-C19 * sin(C38) + C20 * cos(C38) * cos(G12))); // alpha2 (rad)
	double F57 = F56 * 180 / c_dPi + 180; // reverse azimuth (decimal degrees)

	locNew = locOrig;

	locNew.degLongitude = F53;

	locNew.degLatitude = F44;

	return locNew;
}

