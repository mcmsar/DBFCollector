#ifndef __EMSBERTYPES_H__
#define __EMSBERTYPES_H__

#define MAX_NUM_SUBGROUP  50
#define DEFAULT_BEACON_REP_RATE  50  
#define FREQUENCY_FACTOR         406000000.0

typedef struct _tagEMSBERCNTRLDATA
{
	bool			bDynamicGrp;
	double      	dTimeRange;
	float           fProbabilityThreshold;
	double			dFreqRange;
	float			fPwrlvl;
	float			fMinPwrlvl;
	float			fMaxPwrlvl;
	int				iBitDiff;
	int             iAgingPeriod;
	ULONG           ulMinNumOfRec;
	TCHAR			szMatchingMask[ 18 ];

} EMSBERCNTRLDATA, *LPEMSBERCNTRLDATA;

typedef struct  _tagEMSBERDATA
    {
	ULONG   ulSatID;
	ULONG   ulLutID;
    INT64   i64BeaconID;
    EMSTIME timeMsg;
    BYTE cBeaconMsg[ 18 ];
    double dFrequency;
    double dCarrierToNoiseRatio;
	double dRepRate;
    }	EMSBERDATA, *LPEMSBERDATA;


typedef struct _tagEMSBERCNROUTPUTDATA
{
	ULONG   ulDetect;
	double  dMinPower;
	double  dMaxPower;
	double  dMeanPower;
	double  dStDevPower;
	double  dBitErrorRate;
    ULONG   ularrBitError[ 144 ];
} EMSBERCNROUTPUTDATA, *LPEMSBERCNROUTPUTDATA;

typedef struct _tagEMSBERGROUPOUTPUTDATA
{
	INT64   i64BeaconID;
	ULONG   ulLutID;
	ULONG   ulSatID;
	ULONG   ulTimeMeasureOutofSeq;
	ULONG   ulRepRateNotConsistent;
	ULONG   ulFreqMeasurement;
	ULONG   ulPowerOutOfRange;
	BYTE    cBeaconMsg[ 36 ];
	double  dTxFreq;
	double  dRepRate; //RepRate
	double  dMinPower;
	double  dMaxPower;
	EMSTIME timeFirstTx; // date and time of first tranmission
	EMSTIME timeLastTx; // date and time of last tranmission
	double  dTestDuration;
	ULONG   ulExpectedTxCount;
	ULONG   ulReceivedTxCount;
	double  dMaxTimeInterval; // maximum interval between transmissions.
	double  dMeanTimeInterval;
	double  dStDevTimeInterval;
	double  dFreqMean;
	double  dStDevFreq;
	double  dTrendFreq;
	double  dFreqDiffMean; 
	double  dStDevFreqDiff;
	double  dTrendFreqDiff;

	EMSBERCNROUTPUTDATA cnrOutputData[MAX_NUM_SUBGROUP];
	EMSBERCNROUTPUTDATA cnrGrpSummary;

} EMSBERGROUPOUTPUTDATA, *LPEMSBERGROUPOUTPUTDATA;

#endif 