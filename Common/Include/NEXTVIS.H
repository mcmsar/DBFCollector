/*******************************************************************
*	Module:			NextVis.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSNextVisibility class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:		
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003 Feb 7	rvw	start

********************************************************************/

#ifndef INC_NEXTVIS
#define INC_NEXTVIS

#include "emstypes.h"
#include "emsit260.h"
#include "emspass.h"
#include "emsatinf.h"
#include "emsorbit.h"

const int c_nNextVisMaxSatellites = 32;

class CEMSNextVisibility
{
public:
	CEMSNextVisibility();
	virtual ~CEMSNextVisibility();

	EMS_RESULT Initialize( IEMSPassSchedule *lpPassSchedObj = 0,
										IEMSSatelliteInfo	*lpSatInfo = 0 ,
										IEMSOrbit *lpOrbit = 0 );
	EMS_RESULT Reset( void );

	EMS_RESULT SetCurrentPassSchedule(  CEMSSit260A *lpPassSched );
	EMS_RESULT SetCurrentPassSchedule(  EMSSATELLITEPASS *lpPassInfo, int nPassCount );
	EMS_RESULT SetPassScheduleObject( IEMSPassSchedule *lpPassSchedObj );
	EMS_RESULT AddPass( EMSSATELLITEPASS& passData );

	EMS_RESULT CalculateNextVisibility( EMSLOCATION* pLocation, EMSTIME* pTime );

	EMS_RESULT CalculateNextVisibility( EMSLOCATION* pLocation, EMSTIME* pTime, EMSTIME timeLast, bool bRealTimeOnly = false );

	void SetLutLocation( EMSLOCATION lutLocation ) { m_lutLocation = lutLocation; }

private: // methods
	void _ResetSatList( void );
	void _UpdateSatList( void );
	void _ResetPassSchedule( void );
	EMS_RESULT _AllocPassSchedule( ULONG ulCount );
	EMS_RESULT _AllocRecord( ULONG& ulNextSlot );
	EMS_RESULT _SetLocationInPassSched( EMSLOCATION *lpLocation );
	
	EMSTIME _GetMostCurrentTimeCheckedForSat( ULONG ulSatID, EMSSATELLITEPASS *lpPass, int nIndex, EMSTIME timeLast );
	EMS_RESULT _GetLocationVisibilitySchedule(	EMSLOCATION* pLocation, 
												ULONG ulMaxScheduleSize,
												EMSSATELLITEPASS* aLocationPassTable,
												ULONG& ulEntries );
	EMS_RESULT _FindVisibility( ULONG ulSatID,
								EMSSATELLITEPASS* aLocationPassTable,
								ULONG ulEntries,
								EMSTIME& timeLocationAOS,
								EMSTIME& timeLocationLOS );

	BOOL _HasSARP( ULONG ulSatID );

	EMS_RESULT _CheckPassX( EMSTIME *lpTimeFound, EMSSATELLITEPASS *lpPass, EMSTIME timeLast, bool bRealTimeOnly );
	EMS_RESULT _CheckPass( EMSLOCATION eltLocation, EMSTIME *lpTimeFound, EMSSATELLITEPASS *lpPass, 
										EMSTIME timeLast, bool bRealTimeOnly );

	EMS_RESULT _InitSatInfo();
	EMS_RESULT _InitPassSchedObj();
	EMS_RESULT _GenerateSchedule( ULONG ulMazSize, EMSSATELLITEPASS* aPassSched, ULONG& ulActual );
	EMS_RESULT _GenerateSchedule( ULONG ulMazSize, EMSSATELLITEPASS* aPassSched, ULONG& ulActual, 
								ULONG ulSatID, EMSTIME timeStart, EMSTIME timeEnd );

	EMS_RESULT _Predict( EMSLOCATION eltLocation, EMSLOCATION lutLocation,
			EMSSATELLITEPASS *lpPass, double dMinElevationAngle, double dMinDuration,
			EMSTIME *lpTCA, double *lpdCTA, double *lpdMaxElevation );

	EMS_RESULT _GetSMA( ULONG ulSatID, EMSTIME timeAOS, double *lpdSMA ); 

private: // data
	IEMSPassSchedule	*m_lpPassSchedObj;	// Pointer to the pass schedule object.  Used for generating pass schedules.
	EMSSATELLITEPASS	*m_lpPassInfo;		// The LUT's pass schedule.
	ULONG				m_ulPassCount;		// The number of entries in the LUT's pass schedule.
	IEMSSatelliteInfo	*m_lpSatInfo;		// Pointer to a Satellite Info object.
	ULONG					m_ulSatCount;
	ULONG					m_ulSatList[ c_nNextVisMaxSatellites ];
	IEMSOrbit			*m_lpOrbit;
	EMSLOCATION			m_lutLocation;
	double				m_dMinElevation;
	double				m_dMinDurationMinutes;
};

#endif // INC_NEXTVIS
