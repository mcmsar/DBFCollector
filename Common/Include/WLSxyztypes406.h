/********************************************************************
*	Module:			WLSxyzTypes406.h
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
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth    	Changes
	===	====			====	    =======

  0.0 01/11/2010        R.Renner	start

********************************************************************/

#ifndef INC_WLSXYZTYPES406
#define INC_WLSXYZTYPES406

#define	MAXVARIABLES	(5)

#define SIND(a)		   (sin(a * c_dDegToRad))
#define COSD(a)        (cos(a * c_dDegToRad))
#define TAND(a)        (tan(a * c_dDegToRad))
#define TAN2D(a,b)     (tan2(a,b))
#define ASIND(a)       (c_dRadToDeg * asin(a))
#define ACOSD(a)       (c_dRadToDeg * acos(a))
#define ATAND(a)       (c_dRadToDeg * atan(a))
#define ATAN2D(a,b)    (c_dRadToDeg * atan2(a,b))

#define PROCESS_FBIAS	(0x01)
#define PROCESS_TBIAS	(0x02)
#define PROCESS_ALTITUDE  (0x04)

#define PROCESS_TDOA    (0x0001)
#define PROCESS_FDOA    (0x0002)
#define PROCESS_FREQ    (0x0004)

#include "emstypex.h"

#define MAX_LUTS        32
#define MAX_SATS        16

typedef struct _tagEMSPARTIALDERVATIVE // Partial dervatives
{
	double	x;
	double	y;
	double	z;
	double	Fbias;
	double	Tbias;
} EMSPARTIALDERVATIVE, *LPEMSPARTIALDERVATIVE;


typedef struct _tagEMSWLSCONTROL // COMMON CONTROL
{
	WORD	wProcessDataType;  // Set data types to be processed (1=TDOA,2=FDOA,4=FREQ)
    
	double  dCal406DurInHours; // Maximum duration of measurements to process (Hrs)
    int     iCal406MeasMax;    // Maximum number of measurements to process
    int     iCal406MeasMin;    // Minimum number of measurements to process

	int		iVariableFlag;

	int     iIterationsMax;  // maximum number of iterations allowed
	int     iIterationsMin;  // minimum number of iterations allowed

	int     iMinBiasPoints;  // minimum number of measurements allowed for frequency bias processing

	double  dFbias;	// initial estimate of frequency bias
	double  dTbias;	// initial estimate of time bias

	double	dXYZMax;	// maximum change in XYZ
	double  dFbiasMax;	// maximum change in frequency bias
	double  dTbiasMax;	// maximum change in time bias

	double	dXYZMin;	// minimum change in Alpha
	double  dFbiasMin;	// minimum change in frequency bias
	double  dTbiasMin;	// minimum change in time bias


//	double	dMaxNoise;			// maximum allowed measurement noise ( used for convergence test )
	double	dMaxFreqNoise;		// maximum allowed frequency measurement noise ( used for convergence test )
	double	dMaxTimeNoise;		// maximum allowed time measurement noise ( used for convergence test )
	double	dResidThresholdMin;	// minimum allowed residual threshold(Hz)
	double	dStdDevMax;			// maximum number of standard deviations allowed for residual

//	double	dMaxDriftCorrelation;  // Correlation Threshold for Drift processing

	double	dNomErrorEllipseScaleFactor; // Nominal Multiplier of error ellipse
	double	dNomErrorEllipseOrbitError;  // Nominal Orbit error to be included in error ellipse (km)
	double	dMarErrorEllipseScaleFactor; // Marginal Multiplier of error ellipse
	double	dMarErrorEllipseOrbitError;  // Marginal Orbit error to be included in error ellipse (km)

    int     iType; // index to ellipse errs (     SARP=0,     SARR=1,     SARP/SARR=2)
                   //                       (FDOA-SARP=3,FDOA-SARR=4,FDOA-SARP/SARR=5)
                   //                       (     TDOA=6,FDOA-TDOA=7,           ALL=8)
	double	dNomErrorEllipseOrbitErrors[16];  // Nominal Orbit errors to be included in error ellipse (km)
	double	dMarErrorEllipseOrbitErrors[16];  // Marginal Orbit errors to be included in error ellipse (km)
	double	dNomErrorEllipseScaleFactors[16]; // Nominal Multipliers of error ellipse
	double	dMarErrorEllipseScaleFactors[16]; // Marginal Multipliers of error ellipse

//	BOOL	bDrift;			// Temporary variables used to inhibit processing

	double  dMinCovStdDev;     // Minimum covariance residual noise (Hz)

	ULONG	ulMinPtsVisible;	// Minimum number of points visible in satellite footprint.

	double	dFreqWeight;		// Frequency measurement weight factor
	double	dTimeWeight;		// Time measurement weight factor

	bool	bOutputEncoded;
	bool	bRefBeaconOption;
	bool	bSingleBurstOnly;
	double  dOutputTimeInterval;
	double	dDataDurationMinutes;

	double	dMEOTimeOffset;	// Time offset for MEO data
	double	dGEOTimeOffset;	// Time offset for GEO data

	int		iRemoveLUT[10];   // set of LUT IDs to be excluded
	int		iRemoveSAT[10];   // set of Satellite IDs to be excluded

} EMSWLSCONTROL, *LPEMSWLSCONTROL;


#endif // INC_WLSXYZTYPES406
