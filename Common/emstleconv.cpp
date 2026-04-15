/********************************************************************
*	Module:			EMSTLEConv.cpp 
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
*
*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

	0.0	2006/12/06	rvw 	start

********************************************************************/
#include <math.h>

#define EMSERROR_NODEFINE_TYPES

#include "emstypes.h"
#include "EMSTLEConv.h"
#include "EMSGPSConvert.h"
#include "emsconst.h"
#include "gpsephem.h"		// EMSGPSEPHEMERISDATA
#include "emsclock.h"		// CEMSSystemClock
#include "emscoord.h"
#include "emsvectr.h"
#include "emsorbit.h"
#include "EMSGPSOrbit.h"
#include "emsexcpt.h"

const INT c_nMinGpsSatID = 300;
const INT c_nMinGalSatID = 400;

IEMSOrbit4* CEMSTLEConvert::ms_pOrbit = NULL;
CEMSCriticalSection CEMSTLEConvert::ms_cs;
bool CEMSTLEConvert::m_bGotLeapSeconds = false;
int  CEMSTLEConvert::m_iLeapSeconds = 0;

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::GPStoTLEData( LPEMSTLEDATA lpTLEData, EMSEPHEMERISDATA *lpEphemData ) 
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLEData )
	{
		EMSTLEDATA2 tleData2;

		hr = GPStoTLEData2( &tleData2, lpEphemData );

		if ( ( EMS_OK == hr ) && lpTLEData )
			*lpTLEData = tleData2.tle;
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSTLEConvert::GPStoTLEData2( LPEMSTLEDATA2 lpTLEData2, EMSEPHEMERISDATA *lpEphemData )  
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLEData2 )
	{
		EMSTLERECORD tleRec;
		EMSTLEDATA2 tleData2;

		memset( &tleData2, 0, sizeof(tleData2) );

		hr = GPStoTLERecord( &tleRec, lpEphemData );

		if ( ( EMS_OK == hr ) && lpTLEData2 )
		{
			tleData2.timeModified = tleRec.time;

			tleData2.timeEffective = tleRec.timeEffective;
		 
			tleData2.tle.timeEpoch = tleRec.timeEpoch;
	
			tleData2.tle.elem.var.fEccentricity = tleRec.fEccentricity;
			tleData2.tle.elem.var.fInclination  = tleRec.fInclination;
			tleData2.tle.elem.var.fMeanAnomaly  = tleRec.fMeanAnomaly;
			tleData2.tle.elem.var.fArgPerigee   = tleRec.fArgPerigee;
			tleData2.tle.elem.var.fRightAscNode = tleRec.fRightAscNode;
			tleData2.tle.elem.var.fMeanMotion   = tleRec.fMeanMotion;

			*lpTLEData2 = tleData2;
		}
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

#define EQ     ==
#define AND    &&
#define OR     ||

#define DMOD(a,b)      ((a) - (long int)((a)/(b)) * (b))
#define SIGN(a,b)      ((b) >= 0 ? fabs (a) : -fabs (a))
#define LEAP_YEAR(iyr) ((iyr) % 4 EQ 0 AND ((iyr) % 100 != 0 OR (iyr) % 400 EQ 0))

#define PI     3.14159265
#define PIO2   1.57079633
#define TWOPI  6.2831853
#define X3PIO2 4.71238898
#define DE2RA   .174532925e-1
#define RHO     .15696615

#define TDELTA80  5260320.0    /* 1980 - 1990 period in minutes */
#define OBLIQ        23.442    /* Inclination of Equator over Earth's orbital plane (degs) */
#define RDG 57.295779513  /* Degrees / radian */
#define RE  6378.135      /* Earth's radius (km) */
#define E2  0.00669438002 /* oblateness**2 of Earth */
#define J2  -1082.63e-6   /* 2nd Tesserel harmonic coefficient */
#define SID 86164.09054   /* Sidereal day (secs) */
#define SOL 86636.55536   /* Solar day (secs) */
#define MU  3.986005e5    /* Gravitation constant (km**3/sec**2) */

static long double Dnuc (long double t)
{
    long double t80, td, ldres;
    double      f, d, w;

    t80 = (t + TDELTA80) * 60.0;    /* in seconds from 1980 */
    td  = t80/86400.0 + 29219.0;
    f     = DMOD ( 11.25089 + 13.229350449*td, 360.0)/RDG;
    d     = DMOD (350.73749 + 12.190749191*td, 360.0)/RDG;
    w     = DMOD (259.18328 -  0.052953922*td, 360.0)/RDG;
    ldres = (-17.2327*sin(w) - 1.2729*sin(2.0*(f + w - d)) +
             0.2088*sin(2.0*w) - 0.2037*sin(2.0*(f + w))) / 3600.0;
    w     = OBLIQ / RDG;
    ldres = ldres * cos (w);

    return (ldres);     /* in degrees */
}

static long double Gst (long double t)
{
    long double t80, td, tc, ldres;

    t80   = (t + TDELTA80) * 60.0;    /* in seconds from 1980 */
    td    = t80 / 86400.0;
    tc    = td / 36525.0;
    ldres = DMOD (99.8135 + 360.0*(SOL/86400.0)*td + 0.000387*tc*tc + Dnuc (t), 360.0);

    ldres = ldres * PI / 180.0;

    return (ldres);     /* in radians */
}

//////////////////////////////////////////////////////////////////////////////

int CEMSTLEConvert::_GeneratePositionVectorData( LPEMSEPHEMERISDATA lpEphemerisData,
								int nMaxPts, LPEMSTIMECOORDD lpRawdata )
{

	EMS_RESULT hr = EMS_OK;
	int nPts = 0;

	if ( lpRawdata && lpEphemerisData)
	{

		CEMSGPSOrbit oGPS;
		EMSTIMECOORDD GPSEFVector;

				
		memset( &GPSEFVector, 0, sizeof(GPSEFVector) );
		
		// Check if within time range
		double dTimeRange = 12.0 * 3600; // +/-12 hour period
		double dTimeInterval = 600.0; // 10 minute interval
		double dTimeOffset = - dTimeRange;

		while ( (dTimeOffset < dTimeRange) && (nPts < nMaxPts) )
		{
			hr = oGPS.GPStoEFT( lpEphemerisData, dTimeOffset, &GPSEFVector );
				
			dTimeOffset += dTimeInterval;

			if ( EMS_OK == hr )
			{
				lpRawdata[nPts] = GPSEFVector;
				nPts ++;
			}
		}

	}

	return nPts;
}

////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT CEMSTLEConvert::_TLE2HK( EMSTLEDATA tle, LPEMSHKCOORD hk )
{
	EMS_RESULT      hr = EMS_OK;;
	if ( &hk )
	{
		hk->elem.var.dH1 = tle.elem.var.fEccentricity * cos( tle.elem.var.fArgPerigee * c_dDegToRad );
		hk->elem.var.dH2 = tle.elem.var.fEccentricity * sin( tle.elem.var.fArgPerigee * c_dDegToRad ); 
		hk->elem.var.dK1 = (tle.elem.var.fInclination  * c_dDegToRad ) * cos ( tle.elem.var.fRightAscNode * c_dDegToRad );
		hk->elem.var.dK2 = (tle.elem.var.fInclination  * c_dDegToRad ) * sin ( tle.elem.var.fRightAscNode * c_dDegToRad );
		hk->elem.var.dMP = ( tle.elem.var.fMeanAnomaly + tle.elem.var.fArgPerigee ) * c_dDegToRad;
		if ( hk->elem.var.dMP > c_dTwoPI )
			hk->elem.var.dMP -= c_dTwoPI;
		if ( hk->elem.var.dMP < -c_dTwoPI )
			hk->elem.var.dMP += c_dTwoPI;
		hk->elem.var.dXN = tle.elem.var.fMeanMotion;
	}
	else
		hr = EMS_BAD_PARAM;
	return ( hr );
}

////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT CEMSTLEConvert::_HK2TLE( EMSHKCOORD hk, LPEMSTLEDATA tle )
{
	EMS_RESULT      hr = EMS_OK;;
	if ( &hk )
	{
		tle->elem.var.fMeanMotion   = hk.elem.var.dXN;
		tle->elem.var.fEccentricity = sqrt( hk.elem.var.dH1 * hk.elem.var.dH1 +
									hk.elem.var.dH2 * hk.elem.var.dH2 );
		tle->elem.var.fArgPerigee   = atan2( hk.elem.var.dH2, hk.elem.var.dH1 );
		tle->elem.var.fMeanAnomaly  = hk.elem.var.dMP - tle->elem.var.fArgPerigee;
		tle->elem.var.fRightAscNode = atan2( hk.elem.var.dK2, hk.elem.var.dK1 );
		tle->elem.var.fInclination  = sqrt( hk.elem.var.dK1 * hk.elem.var.dK1 + 
									hk.elem.var.dK2 * hk.elem.var.dK2 );

		tle->elem.var.fRightAscNode *= c_dRadToDeg;
		tle->elem.var.fInclination *= c_dRadToDeg;
		tle->elem.var.fMeanAnomaly *= c_dRadToDeg; 
		tle->elem.var.fArgPerigee  *= c_dRadToDeg;
	}
	else
		hr = EMS_BAD_PARAM;
	return ( hr );
}


EMS_RESULT CEMSTLEConvert::GPStoTLERecord( LPEMSTLERECORD lpTLERecord, 
										   LPEMSEPHEMERISDATA lpEphemData,
										   bool bGalileoSat ) 
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLERecord )
	{
		EMSTLERECORD tleRec;
		CEMSTime timeTemp,time1990(1990, 1, 1, 0,0,0,0);
		double dMinutes = 0;
		long double ldGST;

		memset( &tleRec, 0, sizeof(tleRec) );

		tleRec.time = CEMSSystemClock::GetTime();

		if ( !bGalileoSat )
			tleRec.ulSatID = ULONG (lpEphemData->ulSatPRN + c_nMinGpsSatID );
		else
			tleRec.ulSatID = ULONG (lpEphemData->ulSatPRN + c_nMinGalSatID );

		tleRec.timeEffective = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTimeCollection, lpEphemData->nWeekNum );
		 
		tleRec.timeEpoch = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTOE, lpEphemData->nWeekNum );

		dMinutes = time1990.MinutesDifferent( tleRec.timeEpoch );

		ldGST = Gst( dMinutes );
                                                                                                                                                                                                                                                                                                                                                                             

		tleRec.nOrbitNumber = 0;
	
		tleRec.fEccentricity = lpEphemData->dE;
		tleRec.fInclination  = lpEphemData->dIO * c_dRadToDeg;
		tleRec.fMeanAnomaly  = lpEphemData->dM0 * c_dRadToDeg;
		tleRec.fArgPerigee   = lpEphemData->dOmega * c_dRadToDeg;

		tleRec.fRightAscNode = (lpEphemData->dOmegaO + ldGST);
		tleRec.fRightAscNode -= lpEphemData->dTOE * c_radEarthRotationRate;
		//tleRec.fRightAscNode -= lpEphemData->dTOE * 7.2921151467e-5;

		tleRec.fRightAscNode *= c_dRadToDeg;
		
		tleRec.fMeanMotion   = lpEphemData->dN * c_dSecondsPerDay /  c_dTwoPI;

		// Set range from 0 to 360
		tleRec.fMeanAnomaly = DMOD(tleRec.fMeanAnomaly, 360.0);
		if ( tleRec.fMeanAnomaly < 0.0 ) tleRec.fMeanAnomaly += 360.0;

		tleRec.fArgPerigee = DMOD(tleRec.fArgPerigee, 360.0);
		if ( tleRec.fArgPerigee < 0.0 ) tleRec.fArgPerigee += 360.0;

		tleRec.fRightAscNode = DMOD(tleRec.fRightAscNode, 360.0);
		if ( tleRec.fRightAscNode < 0.0 ) tleRec.fRightAscNode += 360.0;

		*lpTLERecord = tleRec;

	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::TLEData2toTLERecord(	LPEMSTLERECORD lpTLERecord,
							LPEMSTLEDATA2 lpTLEData, ULONG ulSatID, double dPosErr, double dVelErr, bool bMoreFlag )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTLEData && lpTLERecord )
	{
		memset( lpTLERecord, 0, sizeof( *lpTLERecord ));

		lpTLERecord->time = lpTLEData->timeModified;
		lpTLERecord->timeEffective = lpTLEData->timeEffective;
		lpTLERecord->ulSatID = ulSatID;

		if ( bMoreFlag ) 
			lpTLERecord->ulSatID |= EMS_TLE_MORE_SAT_FLAG;

		lpTLERecord->nOrbitNumber = lpTLEData->tle.nOrbitNumber;
		lpTLERecord->timeEpoch = lpTLEData->tle.timeEpoch;
		lpTLERecord->fBStar = lpTLEData->tle.fBStar;
		lpTLERecord->fInclination = lpTLEData->tle.elem.var.fInclination;
		lpTLERecord->fRightAscNode = lpTLEData->tle.elem.var.fRightAscNode;
		lpTLERecord->fArgPerigee = lpTLEData->tle.elem.var.fArgPerigee;
		lpTLERecord->fEccentricity = lpTLEData->tle.elem.var.fEccentricity;
		lpTLERecord->fMeanAnomaly = lpTLEData->tle.elem.var.fMeanAnomaly;
		lpTLERecord->fMeanMotion = lpTLEData->tle.elem.var.fMeanMotion;
		lpTLERecord->fXndt2o = lpTLEData->tle.fXndt2o;
		lpTLERecord->fXndd6o = lpTLEData->tle.fXndd6o;

    	for ( int i = 0; i < 21; i++ )
			lpTLERecord->fCoVarMatrix[i] = lpTLEData->tle.fCoVarMatrix[i];

		lpTLERecord->dVelocityDifference = dVelErr;

		lpTLERecord->dRadiusDifference = dPosErr;

	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::TLERecordToTLEData2(	LPEMSTLEDATA2 lpTLEData, LPEMSTLERECORD lpTLERecord,
							ULONG *lpulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTLEData && lpTLERecord )
	{
		memset( lpTLEData, 0, sizeof( *lpTLEData ));

		lpTLEData->timeModified = lpTLERecord->time; 
		lpTLEData->timeEffective = lpTLERecord->timeEffective;
		lpTLEData->tle.nOrbitNumber = lpTLERecord->nOrbitNumber; 
		lpTLEData->tle.timeEpoch = lpTLERecord->timeEpoch; 
		lpTLEData->tle.fBStar = lpTLERecord->fBStar; 
		lpTLEData->tle.elem.var.fInclination = lpTLERecord->fInclination; 
		lpTLEData->tle.elem.var.fRightAscNode = lpTLERecord->fRightAscNode; 
		lpTLEData->tle.elem.var.fArgPerigee = lpTLERecord->fArgPerigee; 
		lpTLEData->tle.elem.var.fEccentricity = lpTLERecord->fEccentricity; 
		lpTLEData->tle.elem.var.fMeanAnomaly = lpTLERecord->fMeanAnomaly; 
		lpTLEData->tle.elem.var.fMeanMotion = lpTLERecord->fMeanMotion; 
		lpTLEData->tle.fXndt2o = lpTLERecord->fXndt2o; 
		lpTLEData->tle.fXndd6o = lpTLERecord->fXndd6o; 

    	for ( int i = 0; i < 21; i++ )
			lpTLEData->tle.fCoVarMatrix[i] = lpTLERecord->fCoVarMatrix[i]; 

		if ( lpulSatID )
			*lpulSatID = lpTLERecord->ulSatID & 0xFFFF;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


EMS_RESULT CEMSTLEConvert::TLEosc2EF( EMSTLEDATA *lpTLE, EMSTIMECOORDD *lpCoordEF )
{
	EMS_RESULT hr = EMS_OK;
	EMSTIMECOORDD CoordIC;
	CEMSCoordSystem coordSys;

	memset( &CoordIC, 0, sizeof(EMSTIMECOORDD) );

	hr = TLEosc2IC( lpTLE, &CoordIC );

	*lpCoordEF = coordSys.ToEarthFixed( CoordIC );

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::TLEosc2IC( EMSTLEDATA *lpTLE, EMSTIMECOORDD *lpCoord )
{

	EMS_RESULT hr = EMS_OK;

	double A = 0.0, E = 0.0, V = 0.0;

	double sinU, cosU, sinI, cosI, sinRAAN, cosRAAN, sinP, cosP;
	double r, p, v, xop, yop;

	double ecc	= lpTLE->elem.var.fEccentricity;
    double N	= lpTLE->elem.var.fMeanMotion;
	double I	= (lpTLE->elem.var.fInclination) * c_dDegToRad;
	double M	= (lpTLE->elem.var.fMeanAnomaly) * c_dDegToRad;
	double RAAN = (lpTLE->elem.var.fRightAscNode)* c_dDegToRad;
	double P	= (lpTLE->elem.var.fArgPerigee)  * c_dDegToRad;

    N  = N * c_dTwoPI / 86400.0;
    A  = pow (c_dGravitationConstant / ( N * N ), 1.0 / 3.0);

	int iterations = _Kepler( ecc, M, &E, &V );

	sinU = sin(V+P);
	cosU = cos(V+P);

	sinP = sin(P);
	cosP = cos(P);

	sinI = sin(I);
	cosI = cos(I);

	sinRAAN = sin(RAAN);
	cosRAAN = cos(RAAN);

	r = A * ( 1.0 - ecc * cos(E) );
	p = A * ( 1.0 - ecc * ecc );
	v = sqrt( c_dGravitationConstant / p );

	xop = r * cosU;
	yop = r * sinU;

	lpCoord->coord.radius.dX = xop * cosRAAN - yop * cosI * sinRAAN;
	lpCoord->coord.radius.dY = xop * sinRAAN + yop * cosI * cosRAAN;
	lpCoord->coord.radius.dZ = yop * sinI;

	xop = sinU + ecc * sinP;
	yop = cosU + ecc * cosP;

	lpCoord->coord.velocity.dX = - v * ( cosRAAN * xop + sinRAAN * cosI * yop );
	lpCoord->coord.velocity.dY = - v * ( sinRAAN * xop - cosRAAN * cosI * yop );
	lpCoord->coord.velocity.dZ = v * sinI * ( cosU + ecc * cosP );

	
	lpCoord->vTime = lpTLE->timeEpoch;

	lpCoord->coordSystem = COORDSYS_Inertial;

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::ConvertGPSEPHEMERIStoEF( LPEMSEPHEMERISDATA pGPSEphermis, LPEMSTIMECOORDD pGPSEFVector )
{

	EMS_RESULT hr = EMS_OK;

	EMSTIME epochtime;

	EMSEPHEMERISDATA x = *pGPSEphermis;

	int iterations;

	double M = 0.0; // mean anomaly
	double E = 0.0; // eccentric anomaly
	double v = 0.0; // true anomaly

	double theta, s2theta, c2theta;

	// second harmonic perturbations
	double du; // argument of latitude correction
	double dr; // radius correction
	double di; // inclination correction

	double r; // corrected radius
	double u, sinu, cosu; // corrected argument of latitude
	double i, sini, cosi; // corrected inclination
	double ANODE, sinANODE, cosANODE; // corrected longitude of ascending node

	double xop, yop; // position in orbit plane
	double xef[3], yef[3], zef[3]; // earth-fixed coordinates

	double dt[3] ={ -1.0,0.0,1.0}; // time increment for velocity calculations
	double dt1 = dt[2] - dt[0];

	epochtime = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( x.dTimeCollection, x.nWeekNum );

	pGPSEFVector->coordSystem = COORDSYS_StdEarthFixed;
	pGPSEFVector->vTime = epochtime;

	for ( int k = 0; k < 2; k++ )
	{
	
		M = x.dM0 + x.dN * dt[k];
		
		iterations = _Kepler( x.dE, M, &E, &v );

		theta = v + x.dOmega;
		s2theta = sin( 2*theta );
		c2theta = cos( 2*theta );

		du = x.dCUS * s2theta + x.dCrc * c2theta;
		dr = x.dCUS * s2theta + x.dCrc * c2theta;
		di = x.dCIS * s2theta + x.dCIC * c2theta;

		u = theta + du;
		sinu = sin(u);
		cosu = cos(u);

		i = x.dIO + di + x.dIDot * dt[k];
		sini = sin(i);
		cosi = cos(i);

		ANODE = x.dOmegaO + ( x.dOmegaDot - c_radEarthRotationRate ) * dt[k];
		ANODE -= c_radEarthRotationRate * x.dTOE;		
		sinANODE = sin(ANODE);
		cosANODE = cos(ANODE);

		r = x.dAxis * ( 1.0 - x.dE * cos(E) ) + dr;

		xop = r * cosu;
		yop = r * sinu;

		xef[k] = xop * cosANODE - yop * cosi * sinANODE;
		yef[k] = xop * sinANODE + yop * cosi * cosANODE;
		zef[k] = yop * sini;

	}

	pGPSEFVector->coord.radius.dX = xef[1];
	pGPSEFVector->coord.radius.dY = yef[1];
	pGPSEFVector->coord.radius.dY = zef[1];

	pGPSEFVector->coord.velocity.dX = (xef[2]-xef[0]) / dt1 ;
	pGPSEFVector->coord.velocity.dY = (yef[2]-yef[0]) / dt1 ;
	pGPSEFVector->coord.velocity.dZ = (zef[2]-zef[0]) / dt1 ;
	

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::GloEphemToTLERecord( LPEMSTLERECORD lpTLERecord, 
												LPEMSGLOEPHEMERIS lpGloEphemData,
												ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	CEMSTime		T;
	EMSTLEDATA		tleDataOUT;
    EMSTLEDATA2		tleData2;
	EMSTIMECOORDD	timeCoord;
	//EMSTIMECOORDD	timeCoordWGS84;
	CEMSCoordSystem coordSys;

	IEMSOrbit4* s_lpOrbit = _GetOrbit();
	
//	hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, 
//						IID_IEMSOrbit4, (LPVOID*)&s_lpOrbit );


	if ( hr == EMS_OK )
	{
		timeCoord.coordSystem = COORDSYS_StdEarthFixed;

		int				iNbYearsSinceLastLeap;
		int				iLastLeapYear;
		EMSTIME			timeNow = CEMSSystemClock::GetTime();
		CEMSTime		oTime( timeNow );
		EMSTIMEFIELDS	timeFields;

		oTime.GetTime( &timeFields );
		iNbYearsSinceLastLeap = timeFields.nYear % 4;
		iLastLeapYear = timeFields.nYear - iNbYearsSinceLastLeap;


		//if ( m_bGotLeapSeconds == false )
		//{
		//	// Ticket 97522: Leap seconds already included in Glonass time.
		//	// Therefore, commenting out the getting of leap seconds.
		//	// m_iLeapSeconds = CEMSGPSConvert::GetLeapSeconds( true );
		//	m_bGotLeapSeconds = true;
		//}

		//		timeCoord.vTime ???
		T.SetTime( iLastLeapYear, 1, 1, 00, 00, 00, 0 );		// Time at Jan 01, LastLeapYear
		T.AddDays( int(lpGloEphemData->siDne - 1) );
		timeCoord.vTime = T.AddSeconds( lpGloEphemData->iTb - 10800 ); // 10800 = 3 hours

		timeCoord.coord.radius.dX = lpGloEphemData->dR[0];
		timeCoord.coord.radius.dY = lpGloEphemData->dR[1];
		timeCoord.coord.radius.dZ = lpGloEphemData->dR[2];
		timeCoord.coord.velocity.dX = lpGloEphemData->fV[0];
		timeCoord.coord.velocity.dY = lpGloEphemData->fV[1];
		timeCoord.coord.velocity.dZ = lpGloEphemData->fV[2];

		//timeCoordWGS84 = coordSys.PZ90toWGS84( timeCoord );

		//hr = s_lpOrbit->ConvertOrbitVectorToTLEDouble( ulSatID, timeCoordWGS84, &tleDataOUT );
		hr = s_lpOrbit->ConvertOrbitVectorToTLEDouble( ulSatID, timeCoord, &tleDataOUT );
		if ( hr != EMS_BAD_PARAM )
		{
			tleData2.tle = tleDataOUT;

			hr = CEMSTLEConvert::TLEData2toTLERecord( lpTLERecord, &tleData2, ulSatID );
		

			// Setting the Effective time to epoch time
			lpTLERecord->timeEffective = lpTLERecord->timeEpoch;
		
			// Set range from 0 to 360
			lpTLERecord->fMeanAnomaly = DMOD(lpTLERecord->fMeanAnomaly, 360.0);
			if ( lpTLERecord->fMeanAnomaly < 0.0 ) lpTLERecord->fMeanAnomaly += 360.0;

			lpTLERecord->fArgPerigee = DMOD(lpTLERecord->fArgPerigee, 360.0);
			if ( lpTLERecord->fArgPerigee < 0.0 ) lpTLERecord->fArgPerigee += 360.0;

			lpTLERecord->fRightAscNode = DMOD(lpTLERecord->fRightAscNode, 360.0);
			if ( lpTLERecord->fRightAscNode < 0.0 ) lpTLERecord->fRightAscNode += 360.0;
		}
	}

//	if( s_lpOrbit )
//	{
//		s_lpOrbit->Release();
//		s_lpOrbit = NULL;
//	}

	return ( hr );
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSTLEConvert::GPStoAccurateTLERecord( LPEMSTLERECORD lpTLERecord, 
												  LPEMSEPHEMERISDATA lpEphemData,
												  ULONG ulSatID,
												  bool bGalileoSat )
{
	EMS_RESULT hr = EMS_OK;

    EMSTLEDATA2  tleData;
    EMSTLEDATA2  tleData0;
    EMSTLEDATA2  tleDataTemp;
    EMSTLEDATA2  tleDataBestFit;
	EMSHKCOORD  HK;
	EMSTIME		vTime;
	EMSTIMECOORDD EF0, EF;
	EMSVECTORD	vR;
	ULONG		ulResult = 0;

    double      prrHK[6];
    double      HtH[6][6],  HtR[6], dHK[6];
	double		HtHBestFit[6][6];
    double      dr, dRes;
	double      dThreshold  = 0.0;
	double		dMean		= 1.0e10;
	double		dStdDev		= 1.0e10;
	double		dMean0		= 1.0e10;
	double		dStdDev0	= 1.0e10;
	double		dLastMean	= 1.0e10;
	double		dMeanDiff	= 1.0e10;
	double		dMinMean	= 1.0e10;
	double		dMinStdDev	= 1.0e10;

    long        j, k, n, nvar, ndim;
	long		nWlsIter = -1;
//	char		szInfo[256];
	bool		bConverged = false;

	int			nMaxRecords = 256;
	int			nNumRecords = 0;
	int			nWlsIterMax = 500;

	EMSTIMECOORDD rawdata[256];
	double		dResidual[256];

	
	double      prrHKMax[6] = {0,0,0,0,0,0};
	double		dConvergenceTest	= 0.001;        // Convergence criteria for StdDev change
	double      c_dHK[6]   = {0.00001, 0.00001, 0.01, 0.01, 0.01, 0.01};
	double      c_dHKmax[6]= {0.0005,  0.0005,  0.5, 0.5, 0.5, 0.1};
	double		dMinEccentricity		= 1.0e-5;

	FILE*		fpOut = _wfopen( L"D:\OrbitTest.csv", L"a+t" );
	
//	fwprintf( fpOut,L"SatID,Iter,Mean(km),MeanDiff(km),StdDev(km),Res(0),Res(mid),Res(end)\n"); 

	
	IEMSOrbit4* s_lpOrbit = _GetOrbit();
	
//	hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, 
//						IID_IEMSOrbit4, (LPVOID*)&s_lpOrbit );

	nNumRecords = _GeneratePositionVectorData( lpEphemData, nMaxRecords, &rawdata[0] );

	if ( !bGalileoSat )
		hr = GPStoTLERecord( lpTLERecord, lpEphemData );
	else
		hr = GPStoTLERecord( lpTLERecord, lpEphemData, bGalileoSat );

	hr = TLERecordToTLEData2( &tleData0, lpTLERecord, &ulSatID );

	if( nNumRecords && (EMS_OK == hr) )
	{
		vTime.intTime = 0;

	    memcpy( &tleDataBestFit, &tleData0,  sizeof( EMSTLEDATA2 ) );
	    memcpy( &tleData, &tleData0,  sizeof( EMSTLEDATA2 ) );

		while( nWlsIter < nWlsIterMax && !bConverged && (EMS_OK == hr) )
		{

			nWlsIter++;

			// Initialize WLS matrices
			memset( HtH, 0, sizeof(HtH) );
			memset( HtR, 0, sizeof(HtR) );
			
			// Process each datum.
				

			for( n = 0; (n < nNumRecords) && (hr == EMS_OK); n++ )
			{

				// Predict to the datum time and calculate earth-fixed position vector
				vTime = rawdata[n].vTime;
				
				hr = s_lpOrbit->EarthFixedOrbitTLEDouble( &tleData.tle, &vTime, 1, &EF0, &ulResult );
				if ( hr == EMS_OK )
				{
					//  Calculate the residuals
					vR = CEMSVector::Sub( rawdata[n].coord.radius, EF0.coord.radius );

					dr = CEMSVector::DotProduct( vR, vR );

					dr = sqrt( dr );

					dResidual[n] = dr;
				
					for( ndim = 0; (ndim < 3) && (hr == EMS_OK); ndim++ )
					{

						// Calculate partial derivatives
						memcpy( &tleDataTemp, &tleData, sizeof( EMSTLEDATA2 ) );

						memset( &HK, 0, sizeof( EMSHKCOORD ) );
						hr = _TLE2HK( tleDataTemp.tle, &HK );
					
						for( j = 0; (j < 6) && (hr == EMS_OK); j++ )
						{
							HK.elem.vect[j] += c_dHK[j];
							hr = _HK2TLE( HK, &tleDataTemp.tle );

							vTime = rawdata[n].vTime;
							hr = s_lpOrbit->EarthFixedOrbitTLEDouble( &tleDataTemp.tle, &vTime, 1, &EF, &ulResult );
							if ( hr == EMS_OK )
							{
								if ( ndim == 0 )
									dr = EF.coord.radius.dX - EF0.coord.radius.dX;
								else if ( ndim == 1 )
									dr = EF.coord.radius.dY - EF0.coord.radius.dY;
								else
									dr = EF.coord.radius.dZ - EF0.coord.radius.dZ;

								prrHK[j] = dr/c_dHK[j];

								HK.elem.vect[j] -= c_dHK[j];

								if( fabs( prrHK[j] ) > prrHKMax[j] )  prrHKMax[j] = fabs( prrHK[j] );
							}
						}


						if ( hr == EMS_OK )
						{
							if ( ndim == 0 )
								dr = rawdata[n].coord.radius.dX - EF0.coord.radius.dX;
							else if ( ndim == 1 )
								dr = rawdata[n].coord.radius.dY - EF0.coord.radius.dY;
							else
								dr = rawdata[n].coord.radius.dZ - EF0.coord.radius.dZ;


							// Update WLS matrices
							for( j = 0; j < 6; j++ )
							{
								for( k = 0; k < 6; k++ )
								{
									HtH[j][k] += prrHK[j]*prrHK[k];
								}
								HtR[j] += prrHK[j]*dr;
							}
						}

					}

				} // end if hr == EMS_OK
				
			}

			if ( hr == EMS_OK )
			{
				memset( &dHK, 0, sizeof(dHK) );

				nvar = 6;
				_TLESolve( (double *)HtH, HtR, dHK, nvar );

				for( j = 0; j < 6; j++ )
				{
					if( fabs(dHK[j]) > c_dHKmax[j] )
						dHK[j] *= ( c_dHKmax[j] / fabs(dHK[j]) );
					HK.elem.vect[j] += dHK[j];
				}

				// Convert back to TLE elements
				hr = _HK2TLE( HK, &tleData.tle );
				if ( tleData.tle.elem.vect[2] < dMinEccentricity )
					tleData.tle.elem.vect[2] = dMinEccentricity;

				dMean = 0.0;
				dStdDev = 0.0;

				for( n = 0; n < nNumRecords; n++ )
				{
					dRes   = dResidual[n];
					dMean   += dRes;
					dStdDev += dRes*dRes;
				}
				dMean  /= nNumRecords;
				dStdDev = sqrt( fabs( dStdDev/nNumRecords - dMean * dMean ) );

				// Establish input noise data
				if ( nWlsIter == 0 )
				{
					dMean0 = dMean;
					dStdDev0 = dStdDev;
				
					memcpy( &HtHBestFit, &HtH, sizeof( HtH ) );
				}

				dMeanDiff = dLastMean - dMean;

				if ( dMeanDiff < 0.0 )
				{

					for( j = 0; j < 6; j++ )
					{
						HK.elem.vect[j] -= 1.5*dHK[j];
					}

					// Convert back to TLE elements
					hr = _HK2TLE( HK, &tleData.tle );
					if ( tleData.tle.elem.vect[2] < dMinEccentricity )
						tleData.tle.elem.vect[2] = dMinEccentricity;

				}

				if ( dMean < dMinMean )
				{
					dMinMean = dMean;
					dMinStdDev  = dStdDev;
	
					memcpy( &tleDataBestFit, &tleData, sizeof( EMSTLEDATA2 ) );
				
					memcpy( &HtHBestFit, &HtH, sizeof( HtH ) );
				}

				dLastMean  = dMean;

				if ( fpOut && (nWlsIter > 10)) 
					fwprintf( fpOut,L"%I64d, %d, %d, %f, %f, %f, %f, %f, %f\n", 
						tleData.timeModified.intTime, ulSatID, nWlsIter, dMean, dMeanDiff, dStdDev,
						dResidual[0],dResidual[nNumRecords/2],dResidual[nNumRecords-1]); 

				// Check for convergence
				if ( ( (fabs(dMeanDiff) < dConvergenceTest ) && (nWlsIter > 5) ) )
				{
					bConverged = true;
				}

			}	// end if hr == EMS_OK

		}

	}

	if ( hr == EMS_OK )
	{
		memcpy( &tleData, &tleDataBestFit, sizeof( EMSTLEDATA2 ) );

//	for ( int i = 0; i < 21; i++ )
//		lpTLEData->tle.fCoVarMatrix[i] = &HtHBestFit[i];
	
		hr = TLEData2toTLERecord( lpTLERecord, &tleData, ulSatID, dMean, dStdDev );
	}

//	if( s_lpOrbit )
//	{
//		s_lpOrbit->Release();
//		s_lpOrbit = NULL;
//	}
	fflush( fpOut );
	fclose( fpOut );
	fpOut = NULL;

	return ( hr );
}


EMS_RESULT 
CEMSTLEConvert::ScaleEphemerisData( const EMSEPHEMERISDATA& crEphem,
								  EMSSCALEDEPHEMERISDATA& rEphemScaled )
{
	EMS_RESULT hr = EMS_OK;

	const INT64 TWOEXP5 = 32;
	const INT64 TWOEXP19 = 524288;
	const INT64 TWOEXP29 = 536870912;
	const INT64 TWOEXP31 = 2147483648;
	const INT64 TWOEXP33 = 8589934592;
	const INT64 TWOEXP43 = 8796093022208;

	rEphemScaled.nWeekNum = crEphem.nWeekNum;
	rEphemScaled.i64DeltaN = (INT64) (crEphem.dDeltaN*TWOEXP43);
	rEphemScaled.nIODC = crEphem.nIODC;
	rEphemScaled.cIODE = crEphem.cIODE;
	rEphemScaled.i64M0 = (INT64) (crEphem.dM0*TWOEXP31);
	rEphemScaled.i64UC = (INT64) (crEphem.dUC*TWOEXP29);
	rEphemScaled.i64E = (INT64) (crEphem.dE*TWOEXP33);
	rEphemScaled.i64CUS = (INT64) (crEphem.dCUS*TWOEXP29);
	rEphemScaled.i64CRC = (INT64) (crEphem.dCrc*TWOEXP5);
	rEphemScaled.i64CRS = (INT64) (crEphem.dCRS*TWOEXP5);
	rEphemScaled.i64SqrtA = (INT64) (crEphem.dSqrtA*TWOEXP19);
	rEphemScaled.ulTOE = (ULONG) crEphem.dTOE;
	rEphemScaled.i64CIC = (INT64) (crEphem.dCIC*TWOEXP29);
	rEphemScaled.i64OmegaO = (INT64) (crEphem.dOmegaO*TWOEXP31);
	rEphemScaled.i64CIS = (INT64) (crEphem.dCIS*TWOEXP29);
	rEphemScaled.i64IO = (INT64) (crEphem.dIO*TWOEXP31);
	rEphemScaled.i64Omega = (INT64) (crEphem.dOmega*TWOEXP31);
	rEphemScaled.i64OmegaDot = (INT64) (crEphem.dOmegaDot*TWOEXP43);
	rEphemScaled.i64IDot = (INT64) (crEphem.dIDot*TWOEXP43);
	rEphemScaled.i64N = (INT64) (crEphem.dN*TWOEXP43);

	return hr;
}

EMS_RESULT 
CEMSTLEConvert::UnScaleEphemerisData( const EMSSCALEDEPHEMERISDATA& crEphemScaled,
									  EMSEPHEMERISDATA& rEphem )
{
	EMS_RESULT hr = EMS_OK;

	const double dTWOEXP5 = 32.0;
	const double dTWOEXP19 = 524288.0;
	const double dTWOEXP29 = 536870912.0;
	const double dTWOEXP31 = 2147483648.0;
	const double dTWOEXP33 = 8589934592.0;
	const double dTWOEXP43 = 8796093022208.0;

//    INT nIODC;
//    BYTE cFitInterval;

	rEphem.nWeekNum = crEphemScaled.nWeekNum;
	rEphem.dDeltaN = (double) (crEphemScaled.i64DeltaN / dTWOEXP43);
	rEphem.nIODC = crEphemScaled.nIODC;
	rEphem.cIODE = crEphemScaled.cIODE;
	rEphem.dM0 = (double) (crEphemScaled.i64M0 / dTWOEXP31);
	rEphem.dUC = (double) (crEphemScaled.i64UC / dTWOEXP29);
	rEphem.dE = (double) (crEphemScaled.i64E / dTWOEXP33);
	rEphem.dCUS = (double) (crEphemScaled.i64CUS / dTWOEXP29);
	rEphem.dCrc = (double) (crEphemScaled.i64CRC / dTWOEXP5);
	rEphem.dCRS = (double) (crEphemScaled.i64CRS / dTWOEXP5);
	rEphem.dSqrtA = (double) (crEphemScaled.i64SqrtA / dTWOEXP19);
	rEphem.dTOE = (double) crEphemScaled.ulTOE;
	rEphem.dCIC = (double) (crEphemScaled.i64CIC / dTWOEXP29);
	rEphem.dOmegaO = (double) (crEphemScaled.i64OmegaO / dTWOEXP31);
	rEphem.dCIS = (double) (crEphemScaled.i64CIS / dTWOEXP29);
	rEphem.dIO = (double) (crEphemScaled.i64IO / dTWOEXP31);
	rEphem.dOmega = (double) (crEphemScaled.i64Omega / dTWOEXP31);
	rEphem.dOmegaDot = (double) (crEphemScaled.i64OmegaDot / dTWOEXP43);
	rEphem.dIDot = (double) (crEphemScaled.i64IDot / dTWOEXP43);
	rEphem.dN = (double) (crEphemScaled.i64N / dTWOEXP43);

	return hr;
}

//////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int CEMSTLEConvert::_Kepler( double e, double M, double *EA, double *VA )
{

	int iter = 0;
	double dE = 0.0;
	double sinE, cosE;
	double E, v;
	int nMAXIteration = 25;
	
	// Use Newton's method
	E = 0.0;

	for (iter = 0; (iter < nMAXIteration) & (dE > 1e-8); iter++ )
	{
		E += dE;
		sinE = sin(E);
		cosE = cos(E);
		dE = ( M + e * sinE - E ) / ( 1.0 - e * cosE);
	}

	v = atan2( sqrt(1 - e*e) * sinE, cosE - e );

	dE = E - e * sin(E) - M;

	*EA = E;
	*VA = v;

	return iter;
}

//////////////////////////////////////////////////////////////////////////////

// Description:
//
//       this module solves a set of up to 6 simultaneous linear
// equations using the gauss-jordan reduction method with
// pivoting, first by inverting the input coefficient matrix,
// then multiplying it by the right-hand side column matrix.
//
//
// calling sequence:
//
//    TLESolve( a, c, b, nv )
//
//      arguments:
//
//        a  - coefficient matrix, size 6x6
//             (becomes the inverted matrix)
//        c  - right-hand column matrix, size 1*6
//        b  - column matrix of solutions to linear equations
//        nv - size of matrix (max 6)

void CEMSTLEConvert::_TLESolve( double *a, double *c, double *b, long nv )
{
    long      i, j, k, n, icol, irow, ipiv[6], index[6][2];
    double    at[6][6], temp, piv;

//    i,j,k,n - index counters
//    irow    - row index
//    icol    - column index
//    ipiv    - pivot flags
//    index   - sorting matrix to restore rows and columns
//    temp    - tempory variable for matrix element
//    piv     - pivot element

//  zero pivot indices.

    memcpy( at,    a, sizeof( at    ) );
    memset( ipiv,  0, sizeof( ipiv  ) );
    memset( index, 0, sizeof( index ) );

//  invert the square coefficient matrix "a".

    for( i = 0; i < nv; i++ )
    {

//    search for largest element to be the pivot.

      piv = 0.0;
      for( j = 0; j < nv; j++ )
      {
        if( ipiv[j] > 0 )  continue;
        for( k = 0; k < nv; k++ )
        {
          if( ipiv[k] > 0 )  continue;
          if( fabs( at[j][k] ) < fabs( piv ) )  continue;
          irow = j;
          icol = k;
          piv  = at[j][k];
        }
      }
      ipiv[icol] = 1;

//    put pivot element on diagonal if not already on it.

      if( irow != icol )
      {
        for( n = 0; n < nv; n++ )
        {
          temp = at[irow][n];
          at[irow][n] = at[icol][n];
          at[icol][n] = temp;
        }
      }
      index[i][0] = irow;
      index[i][1] = icol;

//    divide pivot row by pivot element.

      at[icol][icol] = 1.0;
      for( n = 0; n < nv; n++ )
      {
        at[icol][n] /= piv;
      }

//    reduce non-pivot rows.

      for( k = 0; k < nv; k++ )
      {
        if( k == icol )  continue;
        temp = at[k][icol];
        at[k][icol] = 0.0;
        for( n = 0; n < nv; n++ )
        {
          at[k][n] -= at[icol][n]*temp;
        }
      }

    }

//  coefficient matrix inverted, but with possible column changes.
//  interchange them as necessary.

    for( i = 0; i < nv; i++ )
    {
      n = nv - 1 - i;
      if( index[n][0] == index[n][1] )  continue;
      irow = index[n][0];
      icol = index[n][1];
      for( k = 0; k < nv; k++ )
      {
        temp = at[k][irow];
        at[k][irow] = at[k][icol];
        at[k][icol] = temp;
      }
    }

//  multiply inverted coefficient matrix "a" by right hand side
//  column matrix "c", and store it in solution column matrix "b"

    for( i = 0; i < nv; i++ )
    {
      b[i] = 0.0;
      for( j = 0; j < nv; j++ )
      {
        b[i] += at[i][j]*c[j];
      }
    }

    memcpy( a, at, sizeof( at ) );

	return;
}

IEMSOrbit4* 
CEMSTLEConvert::_GetOrbit()
{
	IEMSOrbit4* pRet = NULL;
	IEMSOrbitInit* pInit = NULL;

	try
	{
		ms_cs.Enter();

		pRet = ms_pOrbit;

		if( !pRet )
		{
			EMS_RESULT hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, 
						IID_IEMSOrbitInit, (LPVOID*)&pInit );

			if( EMS_OK == hr )
			{
				hr = pInit->Initialize();

				if( EMS_OK != hr )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}
				else
				{
					hr = pInit->QueryInterface( IID_IEMSOrbit4, (void**) &ms_pOrbit );

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION(hr);
					}
				}

				pInit->Release();
				pInit = NULL;

				pRet = ms_pOrbit;

			}
			else
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}

		}

		
		ms_cs.Leave();
	}
	catch( ... )
	{
		if( ms_pOrbit )
		{
			ms_pOrbit->Release();
			ms_pOrbit = NULL;
		}

		if( pInit )
		{
			pInit->Release();
			pInit = NULL;
		}

		ms_cs.Leave();

		throw;

	}
	
	return pRet;
	
}

//////////////////////////////////////////////////////////////////////////////
