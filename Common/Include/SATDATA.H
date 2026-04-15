/********************************************************************
*	Module:			SatData.h
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	99/07/30		rvw	start

********************************************************************/
#ifndef INC_SATDATA
#define INC_SATDATA

#include "emsatinf.h"

#define EMS_MAX_SATELLITES ( 32 )

typedef enum _tagEMSSATCHANNELS
{
   EMSSatChannel_Baseband  = 0,
   EMSSatChannel_121       = 1,
   EMSSatChannel_243       = 2,
   EMSSatChannel_406       = 3,
   EMSSatChannel_PDS       = 4

#define MAX_SAT_CHANNELS     5

} EMSSATCHANNELS;

typedef struct _tagEMSSATCHANNELDATA
{
   double   dCentreFreq;
   double   dFreqBandwidth;

} EMSSATCHANNELDATA, *LPEMSSATCHANNELDATA;

typedef struct _tagEMSGENSATDATA
{
   BOOL     bCollect;

   struct
   {
      BOOL     bEnable;
      BOOL     bMultipass;
      BOOL     bMultisat;

   } Process;
   
   struct
   {
      BOOL     bCalibrated;
      BOOL     bSolution;

   } Transmit;

   struct
   {
      BOOL     bLocated;
      BOOL     bUnlocated;
      BOOL     bUnlocated1;
      BOOL     bUnlocated2;

   } MCCSuppress;

   struct
   {
      WORD     wNumPoints;
      WORD     wWindowFactor;
      float    fCTAMin;
      float    fCTAMax;

   } MCCFilterCriteria;

   struct
   {
      double   dMin;
      double   dMax;

   } BasebandFrequency;

   struct
   {
      double   dPassband;
      double   dStopband;
      float    fThreshold;

   } Noise;

   struct
   {
      double   dPassband;
      double   dStopband;
      float    fThreshold;

   } Signal;

   float    fCombineThreshold;
   float    fTimeThreshold;

} EMSGENSATDATA, *LPEMSGENSATDATA;

typedef struct _tagEMSSATSPECTRUMDATA
{
   EMSGENSATDATA     data;

} EMSSATSPECTRUMDATA, *LPEMSSATSPECTRUMDATA;

#define  MAX_AUDIO_BANDS   5

typedef struct _tagEMSSATAUDIODATA
{
   EMSGENSATDATA  data;
   double         dFileDuration;
   double         dArchiveDuration;
   ULONG          ulFileSize;
   ULONG          ulArchiveSize;
   int            nBands;

   struct 
   {
      double   dMinFreq;
      double   dMaxFreq;
   } band[MAX_AUDIO_BANDS];

} EMSSATAUDIODATA, *LPEMSSATAUDIODATA;

#define SARP_DATA_RECORDS_MAX 20

typedef struct _tagEMSSATSARPDATA
{
   EMSGENSATDATA  data;
   WORD           wType;
   WORD           wTimeFieldBits;
   float          fBitrate;

   WORD           wDataRecordsMax;
   struct
   {
      EMSTIME     calibrationTime;
      EMSTIME     rolloverTime;
      EMSTIME     effective;
      double      dUSOFrequency;

   } dataRecord[SARP_DATA_RECORDS_MAX];

} EMSSATSARPDATA, *LPEMSSATSARPDATA;

#define SARR_DATA_RECORDS_MAX 20

typedef struct _tagEMSSATSARRDATA
{
   EMSGENSATDATA  data;
   DWORD          dwDetectsMax;
   WORD           wFSerrosMax;
   float          fDecayThreshold;
   float          fMinCNR;
   double         dPowerConversion;
	double 			dFreqBandAdj;
   struct
   {
      double   dLeadingEdge;
      double   dTrailingEdge;

   } Detect406PulseThreshold;

   WORD           wDataRecordsMax;
   struct
   {
      EMSTIME     calibTime;
      EMSTIME     effective;
      float       fFreqOffset;
      INT64       i64TimeOffset;

   } dataRecord[SARR_DATA_RECORDS_MAX];

} EMSSATSARRDATA, *LPEMSSATSARRDATA;

typedef struct _tagEMSSATCBC121DATA
{
   EMSGENSATDATA  data;

} EMSSATCBC121DATA, *LPEMSSATCBC121DATA;

typedef struct _tagEMSSATCBC243DATA
{
   EMSGENSATDATA  data;

} EMSSATCBC243DATA, *LPEMSSATCBC243DATA;

typedef struct _tagEMSSATCBC406DATA
{
   EMSGENSATDATA  data;

} EMSSATCBC406DATA, *LPEMSSATCBC406DATA;

typedef struct _tagEMSSATMI406DATA
{
   EMSGENSATDATA  data;
   BOOL           bRestart;
   float          fWindowFreq;
   float          fWindowTime;
   DWORD          dwWindowBits;
	 int				nOutOfSpecWindowBits;
//	 double			dMsgTimeoutMinutes;
	 BOOL				bMsgForceUpdate;
   WORD          wIntegrateFSErrMax;
   WORD          wIntegratePDF1ErrMax;
   WORD          wIntegratePDF2ErrMax;
   WORD          wValidFSErrMax;
   WORD          wValidPDF1ErrMax;
   WORD          wValidPDF2ErrMax;
   WORD          wConfirmFSErrMax;
   WORD          wConfirmPDF1ErrMax;
   WORD          wConfirmPDF2ErrMax;
	 double			dMinMsgInterval;
	 double			dMaxMsgInterval;
	 double			dValidMsgInterval;
	 double			dIntegrateMsgInterval;
	 double			dBeaconAgeout;
	 double			dIntegrateAgeout;
   float          fCNR1Threshold;
   float          fCNR2Threshold;
	double			dSarrFreqOffsetThreshold;
	double			dSummaryInterval;
} EMSSATMI406DATA, *LPEMSSATMI406DATA;

typedef struct _tagEMSSATLEOGEODATA
{
   EMSGENSATDATA  data;

} EMSSATLEOGEODATA, *LPEMSSATLEOGEODATA;

typedef struct _tagEMSSATCALIBCBCDATA
{
   struct
   {
      float       fMin;
      float       fMax;
      float       fIncrement;

   } CTA;
   float       fAmplitudeMin;

} EMSSATCALIBCBCDATA, *LPEMSSATCALIBCBCDATA;

typedef struct _tagEMSSATLOCATECBCDATA
{
   WORD        wDetectsMin;
   struct
   {
      float fMin;
      float fMax;
   } Amplitude;

   WORD        wWLSIterationsMax;
   float       fDataThreshold;
   float       fCorrelationMax;
   BOOL        bDrift;
   float       fEEFactor;
   float       fEEAdjustment;
   float       fSweepThreshold;
   WORD        wSweepMinPoints;

} EMSSATLOCATECBCDATA, *LPEMSSATLOCATECBCDATA;

typedef struct _tagEMSSATCALIB406DATA
{
//   DWORD    dwRTDelay;
//   EMSTIME  Tlast;

		EMSTIME		timeLastMsg;			// Time of last message processed
		double		dRealTimeDelaySecs;	// Real-time satellite relay delay
		double		dSarrSarpHistoryAgeoutDays;	// Days to keep SarrSarp history
		double		dSarrSarpFreqDiffHz; // Acceptable Freq Diff between Sarr-Sarp
		double		dSarrSarpTimeDiffSecs; // Acceptable Time Diff
		INT			nSarrSarpMinCount;		//
		BOOL			bSarrSarpCombine;			// Merge same Sarr Sarp pairs
} EMSSATCALIB406DATA, *LPEMSSATCALIB406DATA;


typedef struct _tagEMSSATLOCATE406DATA
{
   DWORD       dwIterationsMax;
   float       fDataThreshold;
   float       fCorrelationMax;
   BOOL        bDrift;
   BOOL        bAltitude;
   float       fEEFactor;
   float       fEEAdjustment;

} EMSSATLOCATE406DATA, *LPEMSSATLOCATE406DATA;

typedef struct _tagEMSSATTCALDATA
{
   DWORD    dwMinPts;
   float    fTimeThreshold;
   float    fFreqThreshold;

} EMSSATTCALDATA, *LPEMSSATTCALDATA;

#define ORBIT_DATA_RECORDS_MAX 20

typedef struct _tagEMSSATORBITDATA
{
   float       fDurationMax;
   BOOL        bDownlink;
   DWORD       dwDownlinkMinPts;
   float       fPositionThreshold;
   float       fVelocityThreshold;
   DWORD       dwBeaconMinPts;

   WORD        wDataRecordsMax;
   struct
   {
      EMSTIME     installation;
      EMSTIME     epoch;
      EMSTIME     effective;

      struct
      {
         double      dInclination;
         double      dRAAN;

      } plane;

      struct
      {
         double      dEccentricity;
         double      dArgOfPerigree;

      } shape;

      struct
      {
         double      dMeanAnomaly;
         double      dMeanMotion;
         double      d1stDerMeanMotion;
         double      d2ndDerMeanMotion;

      } location;

   } dataRecord[ORBIT_DATA_RECORDS_MAX];

} EMSSATORBITDATA, *LPEMSSATORBITDATA;

#define MANOEUVRE_DATA_RECORDS_MAX 20

typedef struct _tagEMSSATMANOEUVREDATA
{
   WORD        wManoeuvresMax;      // element 0 is reserved for "planned manoeuvre"

   struct
   {   
      EMSTIME                    timeBegin;
      float                      fDuration;
      EMSSATBEHAVIOURTYPE        type;
      EMSSATBEHAVIOURSTATUS      status;

   } manoeuvre[MANOEUVRE_DATA_RECORDS_MAX];

} EMSSATMANOEUVREDATA, *LPEMSSATMANOEUVREDATA;

typedef struct _tagEMSSATDATA
{
   BOOL 			         bInUse;

	 struct 
	 {
	 	DWORD dwFlags;
	 } TestConfig;

   ULONG                ulID;
   ULONG                ulNoradID;
   EMSSATELLITETYPE     uSatelliteType;
	TCHAR			         szName[16];
	TCHAR                szDescription[128];
   BOOL                 bPhaseModDownlink;
   WORD                 wPassSchedulePriority;
   
   EMSSATCHANNELDATA		channel[MAX_SAT_CHANNELS];
   EMSSATSPECTRUMDATA		spectrum;
   EMSSATAUDIODATA			audio;
   EMSSATSARPDATA			sarp;
   EMSSATSARRDATA			sarr;
   EMSSATCBC121DATA			cbc121;
   EMSSATCBC243DATA			cbc243;
   EMSSATCBC406DATA			cbc406;
   EMSSATMI406DATA			mi406;
   EMSSATLEOGEODATA			leogeo;
   EMSCALIBCBCCONFIGDATA	calibcbc;
   EMSLOCATECBCCONFIGDATA	locatecbc;
   EMSSATCALIB406DATA		calib406;
   EMSLOCATE406CONFIGDATA	locate406;
   EMSTCALCONFIGDATA		tcal;
   EMSORBITDETCONFIGDATA	orbit;
   EMSSATORBITDATA			orbitdata;
   EMSSATMANOEUVREDATA		manoeuvre;

} EMSSATDATA, *LPEMSSATDATA;

#endif // INC_SATDATA
