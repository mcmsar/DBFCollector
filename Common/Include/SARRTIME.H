/********************************************************************
*    Module:            SARRTime.h
*    Process ID:
*    S/W Platforms:
*    H/W Platforms:
*    Compiler:
*    Description:     CEMSSARRTimeCheck class
*
*    Usage:
*    Entry Point:
*    Input Files:
*    Output Files:
*    Comments:			Uses the Toulouse Beacon(s) to confirm whether 
*							the digital acquistion time is correct
*								
*********************************************************************
*                  Copyright (c) 2007 by EMS Technologies, Inc.,
*                                        All rights reserved
*    This program is unpublished software and contains the trade secrets
*    and confidential information of EMS Technologies, Inc.  It may not be
* reproduced in whole or in part, in any form or by any means whatsoever
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

    Rev    Date            Auth    Changes
    ===    ====            ====    =======

    0.0    2007 Mar 3       rvw        start

********************************************************************/

#ifndef INC_SARRTIME
#define INC_SARRTIME

#include <math.h>

#include "emsbeacn.h"
#include "emserror.h"
#include "calib406.h"
#include "sarrdata.h"

const int c_nMaxTCALBeacons = 16;
const int c_nMaxLUTAntennaPairs = 256;

typedef enum _tagEMSTIMECHECKSTATUS
{
//	EMS_TCS_Unreported = 0x1000,
	EMS_TCS_Valid = 1,
	EMS_TCS_Invalid = 2,
//	EMS_TCS_Unreported_Valid = EMS_TCS_Valid + EMS_TCS_Unreported,
//	EMS_TCS_Unreported_Invalid = EMS_TCS_Invalid + EMS_TCS_Unreported,
	EMS_TCS_Unknown = 0
} EMSTIMECHECKSTATUS;

typedef struct _tagEMSLUTANTENNATIMECHECK
{
	ULONG ulLutID;
	ULONG ulAntennaID;
//	bool bReported;
	double dTimeOffset ;			// most recent TCAL burst time offset ( in seconds )
	INT64 i64TCALBursts;	// number of TCAL bursts since startup
} EMSLUTANTENNATIMECHECK, LPEMSLUTANTENNATIMECHECK;

class CEMSSARRTimeCheck
{
public:
	CEMSSARRTimeCheck( );

	virtual ~CEMSSARRTimeCheck( );

	EMS_RESULT Initialize( EMSREFBEACONDATAEX *lpRefBeaconData, INT nRefBeaconCount );
	void Reset( void );

	void EnableLogging( bool bEnable ) { m_bLogEnabled = bEnable; }
	void EnableWarning( bool bEnable ) { m_bWarningEnabled = bEnable; }

	EMS_RESULT CheckData( EMSCALIB406DATA2 *lpCalib406 );
	EMS_RESULT CheckData( EMSCALIB406DATA *lpCalib406 );
	EMS_RESULT CheckData( EMSSARRDATA *lpSarr406 );

	EMSTIMECHECKSTATUS GetLutAntennaTimeStatus( ULONG ulLutID, ULONG ulAntennaID );
//	EMSTIMECHECKSTATUS SetLutAntennaReported( ULONG ulLutID, ULONG ulAntennaID );

private: // methods
	EMS_RESULT _CheckTCALData( ULONG ulLutID, ULONG ulAntennaID, EMSTIME timeMsg, EMSREFBEACONDATAEX *lpRefBeacon );
	bool _IsTCALBeacon( INT64 i64BeaconID ) { return _GetTCALBeaconIdx( i64BeaconID ) >= 0; }
	INT _GetTCALBeaconIdx( INT64 i64BeaconID );
	INT _GetLUTAntennaIdx( ULONG ulLutID, ULONG ulAntennaID );
	EMSTIMECHECKSTATUS _GetTimeStatus( EMSLUTANTENNATIMECHECK *lpChk );
	void _LogTimeStatusChange( EMSLUTANTENNATIMECHECK *lpChk );

private: // data
	EMSREFBEACONDATAEX 	m_TCALBeacon[ c_nMaxTCALBeacons ];
	int						m_nTCALBeacons;
	EMSLUTANTENNATIMECHECK m_chk[ c_nMaxLUTAntennaPairs ];
	int						m_nChkRecords;
	bool						m_bLogEnabled;
	bool						m_bWarningEnabled;
};


#endif // INC_SARRTIME

