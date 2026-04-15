/********************************************************************
*	Module:			EMSJavGPSEphem.h
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

#ifndef INC_EMSJAVGPSEPHEM
#define INC_EMSJAVGPSEPHEM

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
#include "JavadIf.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2
#include "emsatinf.h"		// IEMSSatelliteInfo
#include "passched.h"
#include "glosatidlookup.h"

const INT c_nMinGalSatID = 400;
const INT c_nMaxGalSatID = 499;
const INT c_nMinGloSatID = 500;
const INT c_nMaxGloSatID = 599;

class CEMSJavGPSEphemeris : public CEMSGPSEphemeris
{
public:

	CEMSJavGPSEphemeris( );
	virtual ~CEMSJavGPSEphemeris( );

	EMS_RESULT Initialize( IEMSSatelliteInfo *lpSatInfo=0, 
						   IEMSOrbit *lpOrbit=0, IEMSJavadInterface *lpGpsEphemeris = 0 );
	void Reset( void );

	EMS_RESULT GetTLE( ULONG ulSatID, LPEMSTLERECORD lpTLERecord );

	EMS_RESULT InitEphemerisData( );
	EMS_RESULT InitGpsEphemeris( );
	EMS_RESULT InitGalEphemeris( );
	EMS_RESULT InitGloEphemeris( );
	EMS_RESULT GetGpsTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSEPHEMERISDATA2 *lpEphemRec );
	EMS_RESULT GetGalTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSEPHEMERISDATA2 *lpEphemRec );
	EMS_RESULT GetGloTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSGLOEPHEMERIS2 *lpGloEphemRec );
	EMS_RESULT ValidateGPSephemerisPacket(LPEMSEPHEMERISDATA lpEphemData );
	EMS_RESULT ValidateGLOephemerisPacket(LPEMSGLOEPHEMERIS lpEphemData );
	EMS_RESULT Open( );
	EMS_RESULT Close( );
	EMS_RESULT GetTime( EMSTIME *pTimeGPS );
	EMS_RESULT SyncSystemClock( );

	EMS_RESULT SetGalSatellites( void );
	EMS_RESULT SetGloSatellites( void );
	bool IsGalSatConfigured( ULONG ulSatId );
	bool IsGloSatConfigured( LONG  lSlot, LONG lChannel, ULONG *lpulSatId );

	EMS_RESULT GetTimeAccuracy( float *pfAccuracy );

private: // methods
	EMS_RESULT _SaveEphemData( ULONG ulSatID, EMSEPHEMERISDATA ephemData );
	EMS_RESULT _SaveGloEphemData( ULONG ulSatID, EMSGLOEPHEMERIS ephemData );
	EMS_RESULT _SaveEphemTxtData( EMSEPHEMERISDATA ephemData, EMSTLERECORD tleRecord, bool bHasBadParams );
	EMS_RESULT _SaveGalEphemTxtData( EMSEPHEMERISDATA ephemData, ULONG ulSatId );
	EMS_RESULT _SaveScaledEphemData( EMSSCALEDEPHEMERISDATAEX ephemScaled );
	EMS_RESULT _SaveGloEphemTxtData( EMSGLOEPHEMERIS ephemData, EMSTLERECORD tleRecord, ULONG ulSatID, bool bHasBadParams );
	EMS_RESULT _SaveGloEphemTxtData2( EMSGLOEPHEMERIS ephemData );

private: // data
	IEMSJavadInterface		*m_lpGpsEphemeris;
	bool					m_bInitialized;
	TCHAR					m_szFilePath[256];
	ULONG					m_ulGalSats[ EMS_MAX_SATELLITES ];
	ULONG					m_ulGloSats[ EMS_MAX_SATELLITES ];
	LONG					m_lGloSatSlot[ EMS_MAX_SATELLITES ];
	LONG					m_lGloSatChannel[ EMS_MAX_SATELLITES ];
	ULONG					m_ulGalSatCount;
	ULONG					m_ulGloSatCount;
	CEMSGloSatIDLookup		m_gloSatIdLookup;
};

//private: // constants

#endif // INC_EMSJAVGPSEPHEM

