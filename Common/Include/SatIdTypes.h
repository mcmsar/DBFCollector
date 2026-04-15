#ifndef __EMSSATIDTYPES_H__
#define __EMSSATIDTYPES_H__

#include "spectrum.h"


#define MAX_NUMBER_SATELLITES	30
#define FREQ_BIN_NUMBER			2048		
#define SPECTRUM_SCALE				0.2

typedef struct _tagEMSSATIDCNTRLDATA
{
    ULONG			ulSatId;
    bool			bCalibrationRequired;
	bool			bPhaseMod;
	double          dElevationThreshold;        // to get Visible Satellites List
	float			fDopplerFreqShiftRange;		// Doppler shift freq.range
    double			dDownlinkCarrierFreq;
	double			dLatitude;
	double			dLongitude;
	float			fAltitude;
	ULONG			ulAvailableSatId[ MAX_NUMBER_SATELLITES ];
} EMSSATIDCNTRLDATA, *LPEMSSATIDCNTRLDATA;


typedef enum _tagStatsType
{	
	MEDIAN	= 0,
	MEAN	= 1,
	ST_DEV	= 2,
	MAX_VAL	= 3,
	MIN_VAL = 4
} EMSSTATSTYPE;


typedef struct _tagEMSPATTERNSTATS
{
    float   fMedianPower;
    float   fMeanPower;
    float   fStdDev;
    float   fMaxPower;
    float   fMinPower;
	float   fNormMedianPower;
} EMSPATTERNSTATS, *LPEMSPATTERNSTATS;



typedef struct _tagEMSSATPATTERN
{
	ULONG	uSampleSize;
	ULONG   ulSatID;
	float   fMaxDopplerFreqShift;
    float	fMeanPatternVal;
    BOOL    bPhaseModulated;
	ULONG   ulLutID;
    float	fMaxPower;
    float	fFreqOffset;
    float	fFreqQFactor;
	float   fCarrierFrequency;
	EMSPATTERNSTATS arrStats[FREQ_BIN_NUMBER];
} EMSSATPATTERN, *LPEMSSATPATTERN;



typedef struct _tagEMSSATIDSTATS
{
    ULONG	ulSatID;
    float	fSatIDProb;
} EMSSATIDSTATS, *LPEMSSATIDSTATS;



typedef struct _tagEMSSATIDPROB
{
    EMSTIME time;
	ULONG   ulSatID;
	ULONG   ulLutID;
    float	fMaxPower;
    float	fFreqOffset;
    float	fFreqQFactor;
	float   fCarrierFrequency;
	EMSSATIDSTATS arrSatIdProb[MAX_NUMBER_SATELLITES];
} EMSSATIDPROB, *LPEMSSATIDPROB;


#endif 