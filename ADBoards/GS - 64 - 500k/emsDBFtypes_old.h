/********************************************************************
*	Module:			emsDBFtypes.h
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

	0.0	20/01/10		rcr		start

********************************************************************/
#ifndef INC_EMSDBFTYPES
#define INC_EMSDBFTYPES

#include "sigproc.h"

#define DBF_MAX_CHANNELS    (32)		// maximum number of input channels (based upon ADC board capabilities)
//#define DBF_MAX_SATELLITES  (5)			// maximum number of DBF tracked satellites per face
#define DBF_MAX_SATELLITES  (10)			// maximum number of DBF tracked satellites per face

//#define DBF_MAX_SATELLITES  (12)			// maximum number of DBF tracked satellites per face increased to 12..snl


typedef struct tagEMSDBFAZEL
{
	ULONG ulSatID;
	ULONG ulSatPriority;
	EMSDEGREES	degMinSeparation;
	EMSDEGREES	degSatElevation;
	EMSDEGREES	degSatAzimuth;
	EMSDEGREES	degPlateElevation;
	EMSDEGREES	degPlateAzimuth;
	EMSCOMPLEX	acmplxPhase[DBF_MAX_CHANNELS];
} EMSDBFAZEL;

typedef struct tagEMSDBFAZEL __RPC_FAR *LPEMSDBFAZEL;

typedef struct tagEMSDBFCELLCONFG
{
	WORD  wCellID;// RF cell number associated with the physical element in the array.
	WORD  wChannelID;// RF Channel number associated with A/D channel number (in sequential series)
	float fXcoord;// Cell X coordinate relative to plate phase centre (metres)
	float fYcoord;// Cell Y coordinate relative to plate phase centre (metres)
	float fRHCP;// Cell RHCP phase bias (deg)
	float fLHCP;// Cell LHCP phase bias (deg)
} EMSDBFCELLCONFG;

typedef struct tagEMSDBFCELLCONFG __RPC_FAR *LPEMSDBFCELLCONFG;


typedef struct tagEMSDBFFIXPOINTCONFG
{
	WORD  wFixedPointID;			// Fixed Point Identifier
	float fFixPointAzimuth;			// Fixed point azimuth angle (degN)
	float fFixPointElevation;		// Fixed point elevation angle (deg)
	float fFixedPointDistance;		// Distance from the transmitter to the center of the plate (cm).
	WORD  wFixPointPolarization;	// Fixed Point Polarization Flag ( Polarization = 0 for LHCP, Polarization = 1 for RHCP )
	bool  bEnabled;					// Enable flag (true or false)
	float fPhaseAdjust[DBF_MAX_CHANNELS]; // Near field phase adjustments 
} EMSDBFFIXPOINTCONFG;

typedef struct tagEMSDBFFIXPOINTCONFG __RPC_FAR *LPEMSDBFFIXPOINTCONFG;


typedef struct _tagEMSDBFARRAY
{
	WORD  wPlateID;				// Plate Identifier number, defining an array plate and associated combiner board ( up to 8 plates)
	WORD  wPlatePolarization;	// Plate Polarization Flag ( Polarization = 0 for LHCP, Polarization = 1 for RHCP )
	WORD  wCellNumber;			// Number of active cells
	float fPlateFaceAzimuth;	// Antenna Plate Face azimuth angle (degN)
	float fPlateFaceElevation;	// Antenna Plate Face elevation angle (deg)
	float fPlateFaceRotation;	// Antenna Plate Face rotation angle of face major axis relative to face perpendicular and up direction (deg)
	WORD  wFixedPointNumber;    // number of fixed points (zero means don't use fixed points).
	
	EMSDBFCELLCONFG emsDBFCells[DBF_MAX_CHANNELS];
	EMSDBFFIXPOINTCONFG emsFixedPoints[10];

	ULONG ulReserved;			// Reserved for future growth
}	EMSDBFARRAY;

typedef struct _tagEMSDBFARRAY __RPC_FAR *LPEMSDBFARRAY;

typedef struct _tagEMSDBFPASSRECORD
{
	EMSTIME timestamp;		// Time stamp in nanoseconds.
	ULONG ulLutID;			// LUT Identifier number, according to Cospas-Sarsat.
	ULONG ulSatID;			// Satellite Identifier number, according to Cospas-Sarsat.
	ULONG ulPassID;			// Satellite orbit revolution number.
	WORD  wProcessID;		// Process Identifier: 0 to 5  (see process definition). 
	WORD  wPlateID;			// Plate Identifier number, defining an array plate ( up to 8 plates)
	WORD  wAntennaID;		// Antenna Identifier number, defining a beam pattern ( up to 4 beams allowed)
	float fAzimuth;			// Site azimuth pointing angle to satellite (degN)
	float fElevation;		// Site elevation pointing angle to satellite (deg)
	float fPlateAzimuth;	// Azimuth pointing angle to satellite relative to plate face (degN)
	float fPlateElevation;	// Elevation pointing angle to satellite relative to plate face (deg)
	short nPhaseReal[DBF_MAX_CHANNELS];	// Phase correction real components (up to 32 channels)
	short nPhaseImag[DBF_MAX_CHANNELS];	// Phase correction imaginary components (up to 32 channels)
			
	WORD  ulReserved[DBF_MAX_CHANNELS];	// Reserved for future growth
}	EMSDBFPASSRECORD;

typedef struct _tagEMSDBFPASSRECORD __RPC_FAR *LPEMSDBFPASSRECORD;

typedef struct _tagEMSDBFPASSRECORDS
{
	EMSDBFPASSRECORD rec[DBF_MAX_SATELLITES];
}	EMSDBFPASSRECORDS;

typedef struct _tagEMSDBFPASSRECORDS __RPC_FAR *LPEMSDBFPASSRECORDS;

//	PROCESS Definition
//	There are six possible processing algorithms defined as follows:
//	Bit	0.  Do nothing;
//	Bit	1.	Frequency domain algorithm designed for satellites with strong carrier signals;
//	Bit	2.	Time domain algorithm designed for multiple MEOSAR satellites;
//	Bit	3.	Sample covariance algorithm designed for dark sky pointing;
//	Bit	4.	Raw data collection designed for maintenance;
//	Bit	5.	No data collection designed for monitoring array hardware
#define PROCESS0 0x0;
#define PROCESS1 0x1;
#define PROCESS2 0x2;
#define PROCESS3 0x4;
#define PROCESS4 0x8;
#define PROCESS5 0x10;

typedef struct _tagEMSDBFCALIBRECORD
{

	EMSDBFPASSRECORD Pass;		// Replica of DBF Pass Record
	short fCalibPhaseReal[DBF_MAX_CHANNELS];	// Measured Phase correction real components (up to DBF_MAX_CHANNELS channels)
	short fCalibPhaseImag[DBF_MAX_CHANNELS];	// Measured Phase correction imaginary components (up to DBF_MAX_CHANNELS channels)
//	WORD  ulReserved[32];		// Reserved for future growth
}	EMSDBFCALIBRECORD;

typedef struct _tagEMSDBFCALIBRECORD __RPC_FAR *LPEMSDBFCALIBRECORD;

typedef struct _tagEMSDBFCOVARIANCE
{
	EMSTIME timestamp;			// Time stamp in nanoseconds.
	WORD    wPlateID;			// Plate Identifier number, defining an array plate ( up to 8 plates)
	WORD    wChannelCount;		// Number of channels (N)
	ULONG   ulSampleSize;		// Number of sample sets used in the matrix computation
	EMSCOMPLEX acCovariance[DBF_MAX_CHANNELS * DBF_MAX_CHANNELS];	// Sample matrix components 
	ULONG   ulSatelliteID[DBF_MAX_SATELLITES]; // Predicted satellites to track
	float   fPlateAzimuth[DBF_MAX_SATELLITES];     // Predicted satellite azimuth angles respect to plate orientation
	float   fPlateElevation[DBF_MAX_SATELLITES];   // Predicted satellite elevation angles respect to plate orientatio
//	WORD    wReserved[DBF_MAX_CHANNELS];		// Reserved for future growth

}	EMSDBFCOVARIANCE;

typedef struct _tagEMSDBFCOVARIANCE __RPC_FAR *LPEMSDBFCOVARIANCE;

typedef struct _tagEMSDBFMAINTENANCE
{
	EMSTIME timestamp;			// Time stamp in nanoseconds.
	WORD   wPlateID;			// Plate Identifier number, defining an array plate ( up to 8 plates)
	WORD   wChannelCount;		// Number of channels (N)
	ULONG  ulSampleSize;		// Number of sample sets used in the matrix computation
	WORD   wCellID[DBF_MAX_CHANNELS];			// RF cell number associated with the channel
	double dMean[DBF_MAX_CHANNELS];			// A/D mean value for each channel
	double dStdDev[DBF_MAX_CHANNELS];			// A/D standard deviation value for each channel
//	WORD   wReserved[DBF_MAX_CHANNELS];		// Reserved for future growth

}	EMSDBFMAINTENANCE;

typedef struct _tagEMSDBFMAINTENANCE __RPC_FAR *LPEMSDBFMAINTENANCE;


#endif // INC_EMSDBFTYPES

