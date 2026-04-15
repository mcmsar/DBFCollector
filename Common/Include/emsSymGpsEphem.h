/********************************************************************
*	Module:			EMSSymGPSEphem.h
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
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_EMSSYMGPSEPHEM
#define INC_EMSSYMGPSEPHEM

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
#include "gpsephem.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2
#include "emsatinf.h"		// IEMSSatelliteInfo
#include "passched.h"

class CEMSSymGPSEphemeris : public CEMSGPSEphemeris
{
public:

	CEMSSymGPSEphemeris( );
	virtual ~CEMSSymGPSEphemeris( );

	EMS_RESULT Initialize( IEMSSatelliteInfo *lpSatInfo=0, IEMSOrbit *lpOrbit=0, IEMSGpsEphemeris *lpGpsEphemeris = 0 );

	EMS_RESULT GetTLE( ULONG ulSatID, LPEMSTLERECORD lpTLERecord, EMSEPHEMERISDATA2* lpEphemRec );

	EMS_RESULT GetFirstTLE(LPEMSTLERECORD lpTLERecord, EMSEPHEMERISDATA2* lpEphemRec, bool *lpbMore );
	EMS_RESULT GetNextTLE( LPEMSTLERECORD lpTLERecord, EMSEPHEMERISDATA2* lpEphemRec, bool *lpbMore );
	EMS_RESULT ValidateGPSephemerisPacket(LPEMSEPHEMERISDATA lpEphemData );

	void Reset( void );

private: // data
	IEMSGpsEphemeris		*m_lpGpsEphemeris;
	bool						m_bInitialized;
	TCHAR						m_szFilePath[256];
};

//private: // constants

#endif // INC_EMSSYMGPSEPHEM

