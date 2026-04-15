/********************************************************************
*	Module:			EMSTLEConv.h
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

	0.0	06/08/09		rcr		start

********************************************************************/
#ifndef INC_EMSTLECONV
#define INC_EMSTLECONV

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
#include "gpsephem.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2
#include "emsatinf.h"		// IEMSSatelliteInfo
#include "passched.h"
#include "emscoord.h"
#include "JavadIf.h"		// EMSJAVADINTERFACE
#include "criticalsection.h"

typedef struct _tagEMSHKCOORD {
    /* [switch_is][switch_type] */ union 
        {
        /* [default] */ struct 
            {
				double		dH1;	// eccentricity * cos (omega)
				double		dH2;	// eccentricity * sin (omega)
				double		dK1;	// cos (inclination) * cos (node)
				double		dK2;	// cos (inclination) * sin (node)
				double		dMP;	// anomoly + omega
				double		dXN;	// mean motion
            }	var;
        /* [case()] */ double vect[ 6 ];
        }	elem;
}	EMSHKCOORD, *LPEMSHKCOORD;

class CEMSTLEConvert
{
public:

static EMS_RESULT GPStoTLEData( LPEMSTLEDATA lpTLEData, EMSEPHEMERISDATA *lpEphemData );

static EMS_RESULT GPStoTLEData2( LPEMSTLEDATA2 lpTLEData2, EMSEPHEMERISDATA *lpEphemData );

static EMS_RESULT GPStoTLERecord( LPEMSTLERECORD lpTLERecord, LPEMSEPHEMERISDATA lpEphemData,
								  bool bGalileoSat = false ); 

static EMS_RESULT GPStoAccurateTLERecord( LPEMSTLERECORD lpTLERecord,
										 LPEMSEPHEMERISDATA lpEphemData,
										 ULONG ulSatID,
										 bool bGalileoSat = false );

static EMS_RESULT GloEphemToTLERecord( LPEMSTLERECORD lpTLERecord, 
									   LPEMSGLOEPHEMERIS lpGloEphemData,
									   ULONG ulSatID );

static	EMS_RESULT TLEData2toTLERecord(	LPEMSTLERECORD lpTLERecord,
							LPEMSTLEDATA2 lpTLE2, ULONG ulSatID=0, 
							double dPosErr=0.0, double dVelErr=0.0,
							bool bMoreFlag = false );

static	EMS_RESULT TLERecordToTLEData2(	LPEMSTLEDATA2 lpTLEData, LPEMSTLERECORD lpTLERecord,
							ULONG *lpulSatID=0 ); 

static EMS_RESULT TLEosc2IC( EMSTLEDATA *lpTLE, EMSTIMECOORDD *lpCoord );

static EMS_RESULT TLEosc2EF( EMSTLEDATA *lpTLE, EMSTIMECOORDD *lpCoord );

static EMS_RESULT ConvertGPSEPHEMERIStoEF( LPEMSEPHEMERISDATA pGPSEphermis,
									LPEMSTIMECOORDD pGPSEFVector );

static EMS_RESULT ScaleEphemerisData( const EMSEPHEMERISDATA& crEphem,
									  EMSSCALEDEPHEMERISDATA& rEphemScaled );

static EMS_RESULT UnScaleEphemerisData( const EMSSCALEDEPHEMERISDATA& crEphemScaled,
										EMSEPHEMERISDATA& rEphem );

private: // methods
	
static int _Kepler( double e, double M, double *E, double *v );

static int _GeneratePositionVectorData( LPEMSEPHEMERISDATA lpEphemerisData,
									int nMaxPts, LPEMSTIMECOORDD lpRawdata );

static EMS_RESULT _TLE2HK( EMSTLEDATA tle, LPEMSHKCOORD hk );

static EMS_RESULT _HK2TLE( EMSHKCOORD hk, LPEMSTLEDATA tle );

static void _TLESolve( double *a, double *c, double *b, long nv );


private:
	static IEMSOrbit4* _GetOrbit();

private:
	static IEMSOrbit4* ms_pOrbit;
	static CEMSCriticalSection ms_cs;
	static bool	m_bGotLeapSeconds;
	static int	m_iLeapSeconds;

};

//private: // constants

#endif // INC_EMSTLECONV

