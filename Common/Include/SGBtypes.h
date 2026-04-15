#ifndef __SGBTYPES_H__
#define __SGBTYPES_H__

// Number of bits in Beacon message fields
#define FRAME_SYNCH_BITS	50
#define INFORMATION_BITS	202
#define ROTATE_FIELD_BITS	48
#define ROTATE_ID_BITS      4
#define BCH_BITS			48
#define CCODE_BITS			10
#define LATITUDE_BITS		23
#define LONGITUDE_BITS		24
#define TAC_BITS			16
#define SERIAL_BITS			14
#define VESSEL_TYPE_BITS	3
#define VESSEL_ID_BITS		44
#define SELF_TEST_BITS		1
#define TEST_PROTOCOL_BITS	1
#define HOMING_BITS			1
#define BEACON_TYPE_BITS    3
#define RLS_BITS            1
#define SPARE_BITS			14

// Start bit in decoded message fields
#define FRAME_SYNCH_START	1
#define INFORMATION_START	51

// Start bit in beacon message information fields
#define TAC_START			1
#define SERIAL_START		17
#define CCODE_START			31
#define HOMING_START		41
#define SELF_TEST_START		-1 // Self test flag moved to bit 0 of full message
#define TEST_PROTOCOL_START	43
#define LATITUDE_START		44
#define LONGITUDE_START		67
#define VESSEL_TYPE_START	91
#define VESSEL_ID_START		94
#define BEACON_TYPE_START   138
#define RLS_START           42
#define SPARE_START			141
#define ROTATE_FIELD_START	155
#define BCH_START			203

// Rotating Fields #0 and #1
#define ALTITUDE_START      165
#define ALTITUDE_BITS       10

#include "emstypes.h"
#include "emserror.h"

typedef 
enum _tagSGBTYPE
{	
	SGBTYPE_NORMAL	= 0x0001,	// Normal = 1, Test = 0
	SGBTYPE_TOA		= 0x0002,	// TOA data used in location estimate
	SGBTYPE_FOA		= 0x0004,	// FOA data used in location estimate
	SGBTYPE_MOTION	= 0x0008,	// Motion > 1 km/hr
	SGBTYPE_DETECT	= 0x0010,	// Detect only solution
	SGBTYPE_REFBCN	= 0x0020,	// Reference beacon
	SGBTYPE_CANCEL	= 0x0040,	// Cancellation
	SGBTYPE_MULTI	= 0x0080,	// Multi-burst location
	SGBTYPE_PROBLEM	= 0x8000	// No convergence or other issue
}	SGBTYPE;

// Notes:
//	Each structure is defined as a multiple of 8 bytes
//  WORD is "unsigned short" (2 bytes)
//  INT64 is "__int64" (8 bytes)

typedef struct _tagSGBMESSAGEDATA
{
	UINT64	 i64BeaconID;
	BYTE	 BeaconID[12];
	BYTE	 BeaconMsg[38];
	BYTE	 FrameSynch[7];
	BYTE     RotateField[6];
	BYTE	 Spare[3];
	BYTE     BCH[6];
	WORD	 wCountryCode;
	WORD	 wSerialNumber;
	WORD     wMID;
	WORD	 wRotateFieldNumber;
	WORD	 wBitErrorFS;
	WORD	 wBeaconType;

	bool	 bTestProtocol;
	bool	 bSelftest;
	bool	 bHoming;
	bool	 bCancellation;
	bool	 bDefaultLocation;
	bool     bEncodedCapable;
	bool	 bRLS;

	ULONG	 ulTAC;

	UINT64	 i64VesselID;

	ULONG	 ulVesselType;

	double   dLatitude;
	double   dLongitude;
	double   dAltitude;

} SGBMESSAGEDATA, *LPSGBMESSAGEDATA;
//	SGBMESSAGEDATA total ?? bytes


typedef struct _tagSGBRAWDATA
{
	INT64	 timestamp;
	INT64	 i64BeaconID;
	BYTE	 BeaconID[12];
	BYTE	 BeaconMsg[38]; //complete message including hrame synch
	WORD	 wLutID;
	WORD	 wAntennaID;
	WORD	 wSatID;
	INT64	 i64RxTime;
	double	 dRxFrequency;
	float	 fCarrierPower;
	float    fPWR;
	WORD	 wStatus;
	WORD	 wBitErrorFS;
	WORD     wBitErrorMsg;
	WORD     wChipRate;
	double	 dGNSSlatitude;
	double	 dGNSSlongitude;
	WORD	 wReserved[6];
} SGBRAWDATA, *LPSGBRAWDATA;
// SGBRAWDATA total 160 bytes

typedef struct _tagSGBCALIBDATA
{
	INT64	timestamp;
	INT64	i64BeaconID;
	BYTE	BeaconID[12];
	BYTE	BeaconMsg[38];
	WORD	wType;
	WORD	wSatID;
	WORD	wLutID;
	WORD	wAntennaID;
	INT64	i64TimeMsg;
	float	fTimeOffsetDNL;
	float	fTimeOffsetSAT;
	float	fTimeOffsetMEO;
	double	dFrequency;
	double	dGNSSlatitude;
	double	dGNSSlongitude;
	float	fFreqOffsetDNL;
	float	fFreqOffsetSAT;
	float	fFreqOffsetMEO;
	float	fCNR;
	WORD	wBitErrorFS;
	WORD	wBitErrorMsg;
	WORD    wBitRate;
	WORD	wStatus;
	double	dSatPositionX;
	double	dSatPositionY;
	double	dSatPositionZ;
	double	dSatVelocityX;
	double	dSatVelocityY;
	double	dSatVelocityZ;
	INT64	SatEpoch;
	// Reference beacon computed data
	INT64	i64TxTimep;
	double  dTxFrequency;
	float	fTOAresidual;
	float	fFOAresidual;
	double	dBcnPositionX;
	double	dBcnPositionY;
	double	dBcnPositionZ;
	float	fAzimuthBCN;
	float	fElevationBCN;
	float	fAzimuthMEO;
	float	fElevationMEO;
	WORD	wReserved[6];

} SGBCALIBDATA, *LPSGBCALIBDATA;
//	SGBCALIBDATA total 264 bytes


typedef struct  _tagSGBSINGLEBURSTDATA
{
	INT64	timestamp;
	INT64	i64BeaconID;
	BYTE	BeaconID[12];
	BYTE	BeaconMsg[38]; // best received completr message
	WORD	wCountryCode;
	WORD	wType;
	WORD	wSatIDs[16];
	WORD	wLutIDs[8];
	WORD	wAntennaIDs[16];
	WORD	wNumSatIDs;
	double	dLatitude;
	double	dLongitude;
	float	fAltitude;
	double	dGNSSlatitude;
	double	dGNSSlongitude;
	float	fGNSSaltitude;
	INT64	TxTime;
	double	dTxFrequency;
	WORD	wBitErrorFS;
	WORD	wBitErrorMsg;
	WORD	wNumMsgs;
	WORD	wNumMsgsUsed;
	WORD	wNumTOAUsed;
	WORD	wNumFOAUsed;
	WORD	wNumIterations;
	INT64	timeDataStart;
	INT64	timeDataEnd;
	float	fCNR;
	float	fConfidence;
	float	fHDOP;
	float	fEHE;
	float	fMajorError;
	float	fMinorError;
	float	fHeading;
	float	fTOAnoise;
	float	fFOAnoise;
	double	dXvelocity;
	double	dYvelocity;
	double	dZvelocity;
	float	fLocationError;
	float	fConvergeDistance;
	WORD	wReserved[6];
} SGBSINGLEBURSTDATA, *LPSGBSINGLEBURSTDATA;
//	SGBSINGLEBURSTDATA total 376 bytes
	
typedef struct  _tagSGBMULTIBURSTDATA
{
	INT64	timestamp;
	INT64	i64BeaconID;
	WORD	wBeaconID[12];
	WORD	wCountryCode;
	BYTE	BeaconMsg[38]; // last received completr message
	WORD	wType;
	WORD	wStatus;
	WORD	wSatIDs[16];
	WORD	wLutIDs[8];
	WORD	wAntennaIDs[16];
	WORD	wNumSatIDs;
	double	dLatitude;
	double	dLongitude;
	float	fAltitude;
	double	dGNSSlatitude;
	double	dGNSSlongitude;
	float	fGNSSaltitude;
	float	fConfidence;
	float	fHDOP;
	float	fEHE;
	float	fMajorError;
	float	fMinorError;
	float	fHeading;
	double	dXvelocity;
	double	dYvelocity;
	double	dZvelocity;
	WORD	wNumMsgs;
	WORD	wNumMsgsUsed;
	WORD	wNumBurstsUsed;
	INT64	timeDataStart;
	INT64	timeDataEnd;
	float	fDuration;
	float	fCNR;
	float	fTOAnoise;
	float	fFOAnoise;
	float	fLocationError;
	WORD	wReserved[6];

} SGBMULTIBURSTDATA, *LPSGBMULTIBURSTDATA;
//	SGBMULTIBURSTDATA total 312 bytes


#pragma pack()

#endif 