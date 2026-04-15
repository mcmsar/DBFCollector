/********************************************************************
*	Module:			EMSGPSOrbit.cpp 
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

	0.0	2006/07/09		rcr		start

********************************************************************/
#include <math.h>

#define EMSERROR_NODEFINE_TYPES

#include "EMSGPSOrbit.h"
#include "EMSGPSConvert.h"
#include "emsconst.h"
#include "gpsephem.h"		// EMSGPSEPHEMERISDATA
#include "emsclock.h"		// CEMSSystemClock

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::GPStoTLE(	EMSEPHEMERISDATA *lpEphemData, LPEMSTLEDATA lpTLEData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLEData )
	{
		EMSTLEDATA2 tleData2;

		hr = GPStoTLE( lpEphemData, &tleData2 );

		if ( ( EMS_OK == hr ) && lpTLEData )
			*lpTLEData = tleData2.tle;
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSGPSOrbit::GPStoTLE(	EMSEPHEMERISDATA *lpEphemData, LPEMSTLEDATA2 lpTLEData2 )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLEData2 )
	{
		EMSTLERECORD tleRec;
		EMSTLEDATA2 tleData2;

		memset( &tleData2, 0, sizeof(tleData2) );

		hr = GPStoTLE( lpEphemData, &tleRec );

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


EMS_RESULT CEMSGPSOrbit::GPStoTLE( LPEMSEPHEMERISDATA lpEphemData, LPEMSTLERECORD lpTLERecord )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpEphemData && lpTLERecord )
	{
		EMSTLERECORD tleRec;

		memset( &tleRec, 0, sizeof(tleRec) );

		tleRec.time = CEMSSystemClock::GetTime();

		tleRec.ulSatID = ULONG (lpEphemData->ulSatPRN + 300);

		tleRec.timeEffective = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTimeCollection, lpEphemData->nWeekNum );
		 
		tleRec.timeEpoch = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTOE, lpEphemData->nWeekNum );
	
		tleRec.fEccentricity = lpEphemData->dE;
		tleRec.fInclination  = lpEphemData->dIO * c_dRadToDeg;
		tleRec.fMeanAnomaly  = lpEphemData->dM0 * c_dRadToDeg;
		tleRec.fArgPerigee   = lpEphemData->dOmega * c_dRadToDeg;
		tleRec.fRightAscNode = lpEphemData->dOmegaO * c_dRadToDeg;
		tleRec.fMeanMotion   = lpEphemData->dN * c_dSecondsPerDay /  c_dTwoPI;

		*lpTLERecord = tleRec;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSGPSOrbit::GPStoTLE( const BYTE *cpGPSrp0x58, LPEMSTLERECORD pGPSTLEVector )
{

	EMS_RESULT hr = EMS_BAD_PARAM;
	
	hr = _DecodeGPSDataPacket( cpGPSrp0x58 );
		
	ULONG ulSatID = _GetSatelliteID();

	if ( (EMS_OK == hr) & _IsRequestOK() )
	{
		if ( _IsEphemeris() )
		{
			GPSRP0X58EPHEMERIS x;
			x = m_Data.Ephemeris;

			EMSTLERECORD y;
			memset( &y, 0, sizeof(EMSTLERECORD) );

			y.ulSatID = ULONG (x.SV_number + 300);

			y.time = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double) x.t_ephem, x.weeknum );
			
			y.timeEpoch = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double) x.t_oe, x.weeknum );
			
			y.fEccentricity = x.e;
			y.fInclination  = x.i_0;
			y.fMeanAnomaly  = x.M_0;
			y.fArgPerigee   = x.Omega;
			y.fRightAscNode = x.OMEGA_0;
			y.fMeanMotion   = x.n;
			
			pGPSTLEVector = &y;
		}

		else if ( _IsAlmanac() )
		{
			GPSRP0X58ALMANAC x;
			x = m_Data.Almanac;

			EMSTLERECORD y;
			memset( &y, 0, sizeof(EMSTLERECORD) );

			y.ulSatID = ulSatID;

			y.time = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double) x.t_oa_raw, x.Weeknum );
			
			y.timeEpoch = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double) x.t_oa, x.Weeknum );
			
			y.fEccentricity = x.e;
			y.fInclination  = x.i_o;
			y.fMeanAnomaly  = x.M_0;
			y.fArgPerigee   = x.omega;
			y.fRightAscNode = x.OMEGA_0;
			y.fMeanMotion   = x.n;
			
			pGPSTLEVector = &y;
		}
	}
	return hr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::GPStoEF( const BYTE *cpGPSrp0x58, 
								 LPEMSTIMECOORDD pGPSEFVector,
								 ULONG ulSatID )
{

	EMS_RESULT hr = EMS_BAD_PARAM;
	
	hr = _DecodeGPSDataPacket( cpGPSrp0x58 );

	ulSatID = _GetSatelliteID();

	if ( (EMS_OK == hr) & _IsRequestOK() )
	{
		if ( _IsEphemeris() )
		{
			GPSRP0X58EPHEMERIS x;
			x = m_Data.Ephemeris;

			ulSatID = ULONG (x.SV_number + 300);

			hr = _ConvertGPSEPHEMERIStoEF( &x, pGPSEFVector );

		}

	}

	return hr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::GPStoEFT( LPEMSEPHEMERISDATA pGPSEphermis,
								 double dTimeIncrement,
								 LPEMSTIMECOORDD pGPSEFVector )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	GPSRP0X58EPHEMERIS x; 
	
	memset( &x, 0, sizeof(x) );
	
	hr = _ConvertToGPSRP0X58EPHEMERIS( pGPSEphermis, &x );
	
	hr = _ConvertGPSEPHEMERIStoEF( &x, pGPSEFVector, dTimeIncrement );

	return hr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::_DecodeGPSDataPacket( const BYTE *cpGPSrp0x58 )
{

	EMS_RESULT hr = EMS_OK;

	m_byOPER	= cpGPSrp0x58[0];
	
	m_byType	= cpGPSrp0x58[1];

	m_bySatPRN	= cpGPSrp0x58[2];

	m_byBytes	= cpGPSrp0x58[3];

	short nBytes = sizeof(m_Data);

	memset( &m_Data, 0, nBytes);
	
	if (m_byBytes < nBytes ) nBytes = m_byBytes;
	
	memcpy( &m_Data, &cpGPSrp0x58[4], nBytes ); 

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::_ConvertGPSALMANACtoEF( LPGPSRP0X58ALMANAC pGPSAlmanac, LPEMSTIMECOORD pGPSEFVector )
{

	EMS_RESULT hr = EMS_OK;




	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::_ConvertToEMSEPHEMERISDATA( LPGPSRP0X58EPHEMERIS pGPSRP0X58,
												   LPEMSEPHEMERISDATA pEMSEPHEMERIS )
{

	EMS_RESULT hr = EMS_OK;

	if ( pGPSRP0X58 && pEMSEPHEMERIS )
	{
		GPSRP0X58EPHEMERIS x = *pGPSRP0X58;
		EMSEPHEMERISDATA   y = *pEMSEPHEMERIS;


		y.ulSatPRN			= (ULONG) x.SV_number;
		y.dTimeCollection	= (double) x.t_ephem;
		y.nWeekNum			= (INT) x.weeknum;
		y.cCodeL2			= x.CodeL2;
		y.cL2PData			= x.L2Pdata;
		y.cSVAccRaw			= x.SVacc_raw;
		y.cSVHealth			= x.SV_health;
		y.nIODC				= (INT) x.IODC;
		y.dTGD				= (double) x.T_GD;
		y.dTOC				= (double) x.t_oc;
		y.dAF2				= (double) x.a_f2;
		y.dAF1				= (double) x.a_f1;
		y.dAF0				= (double) x.a_f0;
		y.dSVAcc			= (double) x.SVacc;
		y.cIODE				= x.IODE;
		y.cFitInterval		= x.fit_interval;
		y.dCRS				= (double) x.C_rs;
		y.dDeltaN			= (double) x.Delta_n;
		y.dM0				= x.M_0;
		y.dUC				= (double) x.C_uc;
		y.dE				= x.e;
		y.dCUS				= (double) x.C_us;
		y.dSqrtA			= x.sqrt_A;
		y.dTOE				= (double) x.t_oe;
		y.dCIC				= (double) x.C_ic;
		y.dOmegaO			= x.OMEGA_0;
		y.dCIS				= (double) x.C_is;
		y.dIO				= x.i_0;
		y.dCrc				= (double) x.C_rc;
		y.dOmega			= x.Omega;
		y.dOmegaDot			= (double) x.OMEGADOT;
		y.dIDot				= (double) x.IDOT;
		y.dAxis				= x.Axis;
		y.dN				= x.n;
		y.dR1ME2			= x.r1me2;
		y.dOmegaN			= x.OMEGA_n;
		y.dODotN			= x.ODOT_n;

		*pEMSEPHEMERIS		= y;
	}

	return hr;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::_ConvertToGPSRP0X58EPHEMERIS( LPEMSEPHEMERISDATA pEMSEPHEMERIS,
													  LPGPSRP0X58EPHEMERIS pGPSRP0X58 )
{

	EMS_RESULT hr = EMS_OK;

	if ( pGPSRP0X58 && pEMSEPHEMERIS )
	{
		GPSRP0X58EPHEMERIS x = *pGPSRP0X58;
		EMSEPHEMERISDATA   y = *pEMSEPHEMERIS;

		x.SV_number		= (UCHAR) y.ulSatPRN;
		x.t_ephem		= (float) y.dTimeCollection;
		x.weeknum		= y.nWeekNum;
		x.CodeL2		= y.cCodeL2;
		x.L2Pdata		= y.cL2PData;
		x.SVacc_raw		= y.cSVAccRaw;
		x.SV_health		= y.cSVHealth;
		x.IODC			= y.nIODC;
		x.T_GD			= (float) y.dTGD;
		x.t_oc			= (float) y.dTOC;
		x.a_f2			= (float) y.dAF2;
		x.a_f1			= (float) y.dAF1;
		x.a_f0			= (float) y.dAF0;
		x.SVacc			= (float) y.dSVAcc;
		x.IODE			= y.cIODE;
		x.fit_interval	= y.cFitInterval;
		x.C_rs			= (float) y.dCRS;
		x.Delta_n		= (float) y.dDeltaN;
		x.M_0			= y.dM0;
		x.C_uc			= (float) y.dUC;
		x.e				= y.dE;
		x.C_us			= (float) y.dCUS;
		x.sqrt_A		= y.dSqrtA;
		x.t_oe			= (float) y.dTOE;
		x.C_ic			= (float) y.dCIC;
		x.OMEGA_0		= y.dOmegaO;
		x.C_is			= (float) y.dCIS;
		x.i_0			= y.dIO;
		x.C_rc			= (float) y.dCrc;
		x.Omega			= y.dOmega;
		x.OMEGADOT		= (float) y.dOmegaDot;
		x.IDOT			= (float) y.dIDot;
		x.Axis			= y.dAxis;
		x.n				= y.dN;
		x.r1me2			= y.dR1ME2;
		x.OMEGA_n		= y.dOmegaN;
		x.ODOT_n		= y.dODotN;

		*pGPSRP0X58		= x;
	}

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

EMS_RESULT CEMSGPSOrbit::_ConvertGPSEPHEMERIStoEF( LPGPSRP0X58EPHEMERIS pGPSEphermis,
												  LPEMSTIMECOORDD pGPSEFVector,
												  double dTimeOffset )
{

	EMS_RESULT hr = EMS_OK;

	EMSTIME epochtime;

	GPSRP0X58EPHEMERIS x = *pGPSEphermis;

	int iterations;

	double M = 0.0; // mean anomaly
	double E = 0.0; // eccentric anomaly
	double v = 0.0; // true anomaly
	double A = 0.0; // semi-major axis in km
	double n = 0.0; // mean motion in rad/sec
	double n0 = 0.0; // computed mean motion in rad/sec

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

	//epochtime = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double)x.t_ephem, x.weeknum );
	epochtime = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( (double)x.t_oe, x.weeknum );

	pGPSEFVector->coordSystem = COORDSYS_StdEarthFixed;

	pGPSEFVector->vTime = epochtime;
	pGPSEFVector->vTime.intTime += (__int64) (dTimeOffset*1e9);
	
	dt[0]+= dTimeOffset;
	dt[1]+= dTimeOffset;
	dt[2]+= dTimeOffset;
	
	A = x.sqrt_A * x.sqrt_A * 0.001;

	n0 = sqrt( c_dGravitationConstant / A / A / A );

	n = n0 + x.Delta_n;

	// Validate input array
	bool bOK = true;
	
	bOK &= (fabs(x.M_0) <= c_dTwoPI);
	bOK &= (fabs(x.Omega) <= c_dTwoPI);
	bOK &= (fabs(x.OMEGA_0) <= c_dTwoPI);
	bOK &= ( A < 30000.0 && A > 20000.0 );
	bOK &= ( n*86400.0 < 24.0  );  //... period less than 24 hours
	
	if ( bOK )
	{
		for ( int k = 0; k < 3; k++ )
		{
		
			M = x.M_0 + n * dt[k];

			//while ( M < 0.0      ) M += c_dTwoPI;
			//while ( M > c_dTwoPI ) M -= c_dTwoPI;
			M = fmod( M, c_dTwoPI);

			iterations = _Kepler( x.e, M, &E, &v );

			theta = v + x.Omega;
			s2theta = sin( 2*theta );
			c2theta = cos( 2*theta );

			du = x.C_us * s2theta + x.C_uc * c2theta;
			dr = x.C_rs * s2theta + x.C_rc * c2theta;
			di = x.C_is * s2theta + x.C_ic * c2theta;

			// convert to km
			dr *= 0.001;

			u = theta + du;
			sinu = sin(u);
			cosu = cos(u);

			i = x.i_0 + di + x.IDOT * dt[k];
			sini = sin(i);
			cosi = cos(i);

			ANODE = x.OMEGA_0 + ( x.OMEGADOT - c_radEarthRotationRate ) * dt[k];
			ANODE -= c_radEarthRotationRate * x.t_oe;		
			sinANODE = sin(ANODE);
			cosANODE = cos(ANODE);

			r = A * ( 1.0 - x.e * cos(E) ) + dr;

			xop = r * cosu;
			yop = r * sinu;

			xef[k] = xop * cosANODE - yop * cosi * sinANODE;
			yef[k] = xop * sinANODE + yop * cosi * cosANODE;
			zef[k] = yop * sini;

		}

		pGPSEFVector->coord.radius.dX = xef[1];
		pGPSEFVector->coord.radius.dY = yef[1];
		pGPSEFVector->coord.radius.dZ = zef[1];

		pGPSEFVector->coord.velocity.dX = (xef[2]-xef[0]) / dt1 ;
		pGPSEFVector->coord.velocity.dY = (yef[2]-yef[0]) / dt1 ;
		pGPSEFVector->coord.velocity.dZ = (zef[2]-zef[0]) / dt1 ;
	}
	else
		hr = EMS_FALSE;

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


int CEMSGPSOrbit::_Kepler( double e, double M, double *pE, double *pV )
{

	int iter = 0;
	double E = 0.0;
	double v = 0.0;
	double dE = 1.0;
	double sinE, cosE;
	int nMAXIteration = 25;

	while ( M < 0.0      ) M += c_dTwoPI;
	while ( M > c_dTwoPI ) M -= c_dTwoPI;
	
	// Use Newton's method

	for (iter = 0; (iter < nMAXIteration) & (fabs(dE) > 1e-8); iter++ )
	{
		sinE = sin(E);
		cosE = cos(E);
		dE = ( M + e * sinE - E ) / ( 1.0 - e * cosE);
		E += dE;
	}

	v = atan2( sqrt(1 - e*e) * sinE, cosE - e );

	while ( v < 0.0      ) v += c_dTwoPI;
	while ( v > c_dTwoPI ) v -= c_dTwoPI;

	*pV = v;
	*pE = E;
	return iter;
}
