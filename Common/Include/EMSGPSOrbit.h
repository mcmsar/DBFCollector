/********************************************************************
*	Module:			EMSGPSOrbit.h
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
#ifndef INC_EMSGPSOrbit
#define INC_EMSGPSOrbit

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
#include "gpsephem.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2


#pragma pack(1)

typedef enum tagOperationTypes
{
	GPS_OPTYPE_FAIL = 0,
	GPS_OPTYPE_AQK	= 1,
	GPS_OPTYPE_DATA = 2,
	GPS_OPTYPE_NA	= 3
} GPS_OPTYPE;	

// Type of satellite information included in this report:
typedef enum tagDataTypes
{
	GPS_DATATYPE_RV			= 1,	// 1 = Reserved value
	GPS_DATATYPE_ALMANAC	= 2,	// 2 = Almanac (see Table 3-36)
	GPS_DATATYPE_HEALTH		= 3,	// 3 = Health page, T_oa, WN_oa (see Table 3-37)
	GPS_DATATYPE_IONO		= 4,	// 4 = Ionosphere (see Table 3-38)
	GPS_DATATYPE_UTC		= 5,	// 5 = UTC (see Table 3-39)
	GPS_DATATYPE_EPHEMERIS	= 6		// 6 = Ephemeris (see Table 3-40)
} GPS_DATATYPE;	


// Report Packet 0x58 Satellite System Data Reports

// Report Packet 0x58 provides GPS data (almanac, ephemeris, etc.). The receiver sends this
// packet on request or in response to Command Packet 0x38 (acknowledging the loading of
// data). Table 3-35 shows the data format. The binary almanac, health page, and UTC data
// streams are similar to Report Packet 0x40, 0x49, and 0x4F respectively, and those reports
// are preferred. To get ionosphere or ephemeris, this report packet must be used. See Table
// 3-36 through Table 3-40.


// GPS Report packet 0x58 Almanac
// Refer to ICD-GPS-200, Section 20.3.3.5.1.2
typedef struct  _tagGPSRP0X58ALMANAC
{
	BYTE t_oa_raw; 
	BYTE SV_HEALTH; 
	float e; 
	float t_oa;
	float i_o;
	float OMEGADOT;
	float sqrt_A;
	float OMEGA_0;
	float omega;
	float M_0;
	float a_f0;
	float a_f1;
	float Axis;
	float n;
	float OMEGA_n;
	float ODOT_n;
	float t_zc;
	short Weeknum;
	short wn_oa;
}	GPSRP0X58ALMANAC;
typedef struct _tagGPSRP0X58ALMANAC __RPC_FAR *LPGPSRP0X58ALMANAC;


// Table 3-37 Almanac Health Report Data Format
// Refer to ICD-GPS-200, Sec 20.3.3.5.1.3
typedef struct  _tagGPSRP0X58HEALTH
{
	BYTE	Week; // Week # for health BYTE 
	BYTE	SV_health[32];
	BYTE	t_oa;
	BYTE	current_t_oa; // Units = seconds/4096
	short	current_week; // current week #
}	GPSRP0X58HEALTH;
typedef struct _tagGPSRP0X58HEALTH __RPC_FAR *LPGPSRP0X58HEALTH;


// Table 3-38 Ionosphere Report Data Format
// Refer to ICD-GPS-200, Sec 20.3.3.5.1.3
typedef struct  _tagGPSRP0X58IONO
{
	BYTE store[8]; // Compact storage of the following information
	float Alpha_0;
	float Alpha_1;
	float Alpha_2;
	float Alpha_3;
	float Beta_0;
	float Beta_1;
	float Beta_2;
	float Beta_3;
}	GPSRP0X58IONO;
typedef struct _tagGPSRP0X58IONO __RPC_FAR *LPGPSRP0X58IONO;

// Table 3-39 UTC Report Data Format
// Refer to ICD-GPS-200, Sec 20.3.3.5.1.8
typedef struct  _tagGPSRP0X58UTC
{
	BYTE store[13]; // Compact storage of the following information
	double A_0;
	float A_1;
	short Delta_t_LS;
	float t_ot;
	short WN_t;
	short WN_LSF;
	short DN;
	short Delta_t_LSF;
}	GPSRP0X58UTC;
typedef struct _tagGPSRP0X58UTC __RPC_FAR *LPGPSRP0X58UTC;


// Table 3-40 Ephemeris Report Data Format
// Refer to ICD-GPS-200, Sec 20.3.3.3, Table 20-I.
// Refer to ICD-GPS-200, Sec 20.3.3.4
typedef struct  _tagGPSRP0X58EPHEMERIS
{
	BYTE SV_number; // SV PRN number
	float t_ephem; // Time of collection
	short weeknum;
	BYTE CodeL2;
	BYTE L2Pdata;
	BYTE SVacc_raw;  
	BYTE SV_health;
	short IODC;
	float T_GD;
	float t_oc;
	float a_f2;
	float a_f1;
	float a_f0;
	float SVacc;
	BYTE IODE;
	BYTE fit_interval;
	float C_rs;
	float Delta_n;
	double M_0;
	float C_uc;
	double e;
	float C_us;
	double sqrt_A;
	float t_oe;
	float C_ic;
	double OMEGA_0;
	float C_is;
	double i_0;
	float C_rc;
	double Omega;
	float OMEGADOT;
	float IDOT;
	double Axis;	// = (sqrt_A)2
	double n;		// Derived from delta_n
	double r1me2;	// = sqrt(1.0-e2)
	double OMEGA_n; // Derived from OMEGA_0, OMEGADOT
	double ODOT_n;	// Derived from OMEGADOT
}	GPSRP0X58EPHEMERIS;
typedef struct _tagGPSRP0X58EPHEMERIS __RPC_FAR *LPGPSRP0X58EPHEMERIS;

typedef union tagGPSRP0X58DATA
{
	GPSRP0X58ALMANAC	Almanac;
	GPSRP0X58HEALTH		Health;
	GPSRP0X58IONO		Iono;
	GPSRP0X58UTC		UTC;
	GPSRP0X58EPHEMERIS	Ephemeris;
} GPSRP0X58DATA;


class CEMSGPSOrbit
{
public:
	EMS_RESULT GPStoTLE(	const BYTE *cpGPSRP0X58, 
							LPEMSTLERECORD pGPSTLEVector );

	EMS_RESULT GPStoTLE(	EMSEPHEMERISDATA *lpEphemData, 
							LPEMSTLERECORD lpTLERecord );

	EMS_RESULT GPStoTLE(	EMSEPHEMERISDATA *lpEphemData, 
							LPEMSTLEDATA2 lpTLE2 );

	EMS_RESULT GPStoTLE(	EMSEPHEMERISDATA *lpEphemData, 
							LPEMSTLEDATA lpTLEData );

	EMS_RESULT GPStoEF(		const BYTE *cpGPSRP0X58, 
							LPEMSTIMECOORDD pGPSEFVector,
							ULONG ulSatID );

	EMS_RESULT GPStoEFT(	EMSEPHEMERISDATA *lpEphemData,
							double dTimeIncrement,
							LPEMSTIMECOORDD pGPSEFVector );

//protected:

private: // methods
	EMS_RESULT _DecodeGPSDataPacket( const BYTE *pByteArray );

	EMS_RESULT _ConvertGPSALMANACtoEF( LPGPSRP0X58ALMANAC pGPSAlmanac,
										LPEMSTIMECOORD pGPSEFVector );

	EMS_RESULT _ConvertGPSEPHEMERIStoEF( LPGPSRP0X58EPHEMERIS pGPSEphermis,
										LPEMSTIMECOORDD pGPSEFVector,
										double dTimeIncrement = 0.0);

	EMS_RESULT _ConvertToEMSEPHEMERISDATA( LPGPSRP0X58EPHEMERIS pGPSRP0X58,
										LPEMSEPHEMERISDATA pEMSEPHEMERIS );

	EMS_RESULT _ConvertToGPSRP0X58EPHEMERIS( LPEMSEPHEMERISDATA pEMSEPHEMERIS,
										LPGPSRP0X58EPHEMERIS pGPSRP0X58 );

	int _Kepler( double e, double M, double *E, double *V );


	bool _IsRequestNOWAY()	{ return  (m_byOPER == 0) ? true : false ; }
	bool _IsRequestAQK()	{ return  (m_byOPER == 1) ? true : false ; }
	bool _IsRequestOK()		{ return  (m_byOPER == 2) ? true : false ; }
	bool _IsRequestNA()		{ return  (m_byOPER == 3) ? true : false ; }

	bool _IsAlmanac()	{ return  (m_byType == 2) ? true : false ; }
	bool _IsHealth()	{ return  (m_byType == 3) ? true : false ; }
	bool _IsIonosphere(){ return  (m_byType == 4) ? true : false ; }
	bool _IsUTC()		{ return  (m_byType == 5) ? true : false ; }
	bool _IsEphemeris()	{ return  (m_byType == 6) ? true : false ; } 


	ULONG _GetSatelliteID(){ return ULONG(m_bySatPRN + 300); }

private: // data

	BYTE			m_byOPER;	// Type of satellite operation
					// 0 = Request acknowledged/Cannot grant request
					// 1 = Request acknowledged
					// 2 = Requested data included in this report packet
					// 3 = Requested data not available for SV

	BYTE			m_byType;	// Type of satellite information included in this report:
					// 1 = Reserved value
					// 2 = Almanac (see Table 3-36)
					// 3 = Health page, T_oa, WN_oa (see Table 3-37)
					// 4 = Ionosphere (see Table 3-38)
					// 5 = UTC (see Table 3-39)
					// 6 = Ephemeris (see Table 3-40)

	BYTE			m_bySatPRN;
					// 0 = Data that is not satellite ID specific
					// 1-32 = Satellite PRN number

	BYTE			m_byBytes; // Number of bytes of data to be loaded
	GPSRP0X58DATA	m_Data;

};

//private: // constants

#endif // INC_EMSGPSOrbit

