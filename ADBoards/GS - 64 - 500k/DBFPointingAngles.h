/********************************************************************
*	Module:			DBFPointingAngles.h
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

	0.0	2010/12/15		rcr		start

********************************************************************/
#ifndef INC_DBFPOINTINGANGLES
#define INC_DBFPOINTINGANGLES

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>



#include "emstypes.h"
#include "emserror.h"
#include "sigproc.h"

#include "gpsclock.h"
#include "emstime.h"

#include "emstle.h"

interface IEMSOrbit;

#define DBF_MAX_CHANNELS    (32)		// maximum number of input channels (based upon ADC board capabilities)
#define DBF_MAX_SATELLITES  (4)			// maximum number of DBF tracked satellites per face

typedef struct tagEMSSatAzEl
{
	ULONG ulSatID;
	EMSDEGREES	degElevation;
	EMSDEGREES	degAzimuth;
} EMSSATAZEL;

const ULONG culMaxSats = 128;


class CDBFPointingAngles
{
public:

	~CDBFPointingAngles( void );
	CDBFPointingAngles();

	CDBFPointingAngles( const CDBFPointingAngles& x ) ;

	EMS_RESULT Initialize();

	EMSVECTORD _Convert2UnitVector( const double dAzimuth, const double dElevation );

	EMS_RESULT _DBFcellpositions( double *dCellPositionX,
								  double *dCellPositionY );

	EMS_RESULT _Satellite2PlateRotation( const double dSatAzimuth, double dSatElevation,
										const double dPlateAzimuth, const double dPlateElevation,
										const double dPlateRoll, const double dMinElevation,
										double dDBFazimuth, double dDBFelevation );

	EMS_RESULT _PhaseCorrection( const double dDBFazimuth, const double dDBFelevation,
								const double *dCellPositionX, const double *dCellPositionY,
								short *lpPhaseVector);

	void _Reset( );
	
	EMS_RESULT _GetSatelliteAZELs( EMSTIME timeNow, EMSLOCATION location, 
								ULONG ulMaxSats, EMSSATAZEL* aAzEls, ULONG* pulActual );


//protected:

//private: // methods

private: // data

	BOOL					m_bInitialized;
	ULONG					m_ulChannels;
	ULONG					m_ulSatellites;

	short*					m_asPhaseVector;
	
	IEMSOrbit				*m_lpOrbit;
	ULONG					m_ulSats;
	ULONG					m_ulLutID;
	EMSLOCATION				m_locnAntenna;

	EMSTLERECORD			m_atleRecord[ culMaxSats ];

//private: // constants

};


#endif // INC_DBFPOINTINGANGLES



