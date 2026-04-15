/********************************************************************
*	Module:			EMSGPSEphem.h
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
#ifndef INC_EMSGPSEPHEM
#define INC_EMSGPSEPHEM

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
//#include "gpsephem.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2
#include "emsatinf.h"		// IEMSSatelliteInfo
#include "passched.h"

const INT c_nMinGpsSatID = 300;
const INT c_nMaxGpsSatID = 399;

class CEMSGPSEphemeris
{
public:

	CEMSGPSEphemeris( );
	virtual ~CEMSGPSEphemeris( );

	EMS_RESULT Initialize( IEMSSatelliteInfo *lpSatInfo=0, IEMSOrbit *lpOrbit=0 );
	void Reset( void );

	EMS_RESULT SetSatellites( void );
	EMS_RESULT SetSatellites( ULONG *lpulSats, ULONG lCount );
	void ResetSatellites( void );
	bool IsGpsSatConfigured( ULONG ulSatId );

	EMS_RESULT TLEosc2TLEmean( LPEMSTLERECORD lpTLERecord );

protected: // methods
	ULONG _GetOrbitNumber( ULONG ulSatID, EMSTIME timeOrbitNumber );

protected: //data
	IEMSSatelliteInfo		*m_lpSatInfo;
	IEMSOrbit4				*m_lpOrbit;
	ULONG					m_ulSats[ EMS_MAX_SATELLITES ];
	ULONG					m_ulSatCount;
	ULONG					m_ulSatIndex;

private: // methods
	ULONG _GetNoradID( ULONG ulSatID );
	
private: // data
//	TCHAR						m_szFilePath[256];
};

//private: // constants

#endif // INC_EMSGPSEPHEM

