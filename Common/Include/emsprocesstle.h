/********************************************************************
*	Module:			EMSProcessTLE.h
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
#ifndef INC_EMSPROCESSTLE
#define INC_EMSPROCESSTLE

#include "emstypes.h"
#include "emserror.h"
#include "emstle.h"
#include "gpsephem.h"
#include "emsorbit.h"		// EMSTLEDATA and EMSTLEDATA2
#include "emsatinf.h"		// IEMSSatelliteInfo
#include "passched.h"
#include "pksource.h"

class CEMSProcessTLE
{
public:

	CEMSProcessTLE( );
	virtual ~CEMSProcessTLE( );

	EMS_RESULT Initialize( ULONG ulLutID, CEMSPacketSource *lpTLESource, IEMSSatelliteInfo *lpSatInfo=0, IEMSOrbit *lpOrbit=0 );
	void Reset( void );

	EMS_RESULT SetNewTLE( LPEMSTLERECORD lpTLERecord, EMSSITCONTROLCODE ctrlCode=EMSSCC_ValidateInstall, bool bAlways=false );
	EMS_RESULT SetNewTLE( ULONG ulSatID, EMSTLEDATA2 *lpTLEData, EMSSITCONTROLCODE ctrlCode=EMSSCC_ValidateInstall, bool bAlways=false );
	EMS_RESULT IsTLECurrent( ULONG ulSatId );
	EMS_RESULT RewriteOrbit( ULONG ulSatId, ULONG ulNoradId, EMSTIME *epochTime );

private: // methods
	EMS_RESULT _UpdateTLERecord( EMSTLERECORD *lpTLERec );
	EMS_RESULT _UpdateTLERecord( ULONG ulSatID, EMSTLEDATA2 *lpTLEData, BOOL bMoreFlag,
						double dPosErr = 0.0 , double dVelErr = 0.0 );
	EMS_RESULT _GetSatOrbitTolerance( void );

private: // data
	IEMSSatelliteInfo		*m_lpSatInfo;
	IEMSOrbit2				*m_lpOrbit;
	CEMSPacketSource	  	*m_lpTLEDataSource;
	bool						m_bInitialized;
	ULONG						m_ulLutID;
	ULONG					m_ulSatellites[ EMS_MAX_SATELLITES ];
	double					m_dMaxPosError[ EMS_MAX_SATELLITES ];
	double					m_dMaxVelError[ EMS_MAX_SATELLITES ];
	ULONG					m_ulSatCount;
};


#endif // INC_EMSPROCESSTLE

