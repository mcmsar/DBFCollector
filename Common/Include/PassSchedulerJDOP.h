/*******************************************************************************
*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __PassSchedulerJDOP_H__
#define __PassSchedulerJDOP_H__

#include "emstypes.h"
#include "emserror.h"
#include "emstypex.h"
#include "emsconst.h"
#include "math.h"
#include "emsvectr.h"
#include "emsrange.h"
#include "emscoord.h"
#include "emsclock.h"

//#include "ConfigManagerProxyClsid.h"
#include "ccbootstrap.h"
#include "emstime.h"
#include "emsorbit.h"			// IEMSOrbit
#include "emsatinf.h"			// Satellite Information Object
#include "emsiteif.h"			// IEMSSiteInfo
//#include "emsexcpt.h" 			// CEMSException
//#include "LogHelper.h"
#include <string.h>

#define MAXSATLIST (100)		// Maximum number of satellites
#define MAXSAT (27)				// Maximum number of satellites to be evaluated for JDOP
#define MAXANT (16)				// Maximum number of antennas to be evaluated for JDOP
#define MAXCOMBINATIONS (4845)	// Maximum number of combinations to be evaluated for JDOP
#define MAXTESTLOCATIONS (4)	// Maximum number of test locations to be evaluated for JDOP

const CHAR c_DefaultTraceFile[]     = "c:\\temp\\TrackTrace.csv";
const CHAR c_DefaultTrackFile[]     = "c:\\temp\\TrackPlan.csv";
const CHAR c_DefaultSatelliteFile[] = "c:\\temp\\SatelliteVector.csv";

#pragma pack(1)

typedef 
enum _tagPASSSCHEDULEPROCESSFLAGS
    {	
		PASS_MASK_ALL					= 0xfff,
		PASS_MASK_TRACK					= 0x00f,
		PASS_MASK_CONSTRAINT			= 0x0f0,
		PASS_MASK_TYPE    			    = 0xf00,
		PASS_CURRENT_FLAG				= 0x001,  // currently tracked pass
		PASS_START_FLAG					= 0x002,  // start of pass
		PASS_END_FLAG					= 0x004,  // end of pass
		PASS_SCHEDULE_FLAG              = 0x008,  // OK to schedule
		PASS_ANTENNA_ELEVATION_FLAG		= 0x010,  // antenna elevation angle below threshold
		PASS_ANTENNA_BEAMWIDTH_FLAG		= 0x020,  // pass is suppressed due to mainbeam constraint
		PASS_ANTENNA_OUTAGE_FLAG		= 0x040,  // antenna outage
		PASS_SATELLITE_OUTAGE_FLAG		= 0x080,  // satellite outage
		PASS_SUPPRESS_FLAG				= 0x100,  // pass is suppressed
		PASS_REDUNDENT_FLAG             = 0x200,  // redundant pass
	} PASSSCHEDULEPROCESSFLAGS;

typedef struct  _tagPASSDATA
    {
		ULONG ulStatus;
		ULONG ulLastStatus;
		ULONG ulAntennaID;
		ULONG ulSatID;
		ULONG ulOrbitNumber;
		ULONG ulSatPriority;
		double dFrequency;
		EMSTIMECOORDD satvect;
		EMSTIME startPass; 
		EMSTIME endPass; 
		EMSTIME maxElPass; 
		EMSTIME minElPass; 
		EMSAZEL azelStart;
		EMSAZEL azelEnd;
		EMSAZEL azelMaxEl;
		EMSAZEL azelMinEl;
    }	PASSDATA;

typedef struct _tagPASSDATA __RPC_FAR *LPPASSDATA;

typedef struct  _tagSATDATA
    {
		ULONG  ulSatID;
		ULONG  ulNORADID;
		ULONG  ulSatPriority;
		double dDownlinkFreq;
		EMSTIME tOutageTimeStart;
		EMSTIME tOutageTimeEnd;
		ULONG  ulStatus;
    }	SATDATA;

typedef struct _tagSATDATA __RPC_FAR *LPSATDATA;

typedef struct  _tagANTDATA
    {
		ULONG  ulAntennaID;
		EMSLOCATION antennaLocation;
		EMSVECTORD antennaCoord;
		double dMinElevation;
		double dMinSeparation;
		ULONG  ulSatList[MAXSATLIST];   // List of satellites that antenna is able to track
		ULONG  ulSatCount;				// Count of satellites that antenna is able to track
		EMSTIME tOutageTimeStart;
		EMSTIME tOutageTimeEnd;
		ULONG  ulStatus;
    }	ANTDATA;

typedef struct _tagANTDATA __RPC_FAR *LPANTDATA;

class CPassSchedulerJDOP
{
	public:
		CPassSchedulerJDOP();
		CPassSchedulerJDOP( const CPassSchedulerJDOP& x );
		virtual ~CPassSchedulerJDOP();

		EMS_RESULT  Process();
		EMS_RESULT  Init();
		EMS_RESULT  UpdateStatus( EMSTIME ptime );
		EMS_RESULT  GenerateSchedule();
		EMS_RESULT  CreateObjects();
		EMS_RESULT  PredictPass( EMSTIME ptime ); 
		EMS_RESULT  OutputTrace();


	private:

		double	_JDOP( EMSVECTORD v );
		bool	_GetCombination( ULONG icomb );
		bool	_CheckCombination( ULONG icomb, ULONG isat );
		void	_CheckAvailability( EMSTIME PredictTime );
		void	_CheckSeparationAngle();
		void    _CheckElevationAngle();
		void    _FillPassList( ULONG ulFLAG, bool bUpdate = false );
		void    _FillSatPassList( ULONG ulSatID, bool bUpdate = false );
		void    _FillAntPassList( ULONG ulAntennaID, bool bUpdate = false );
		void    _RemovePassList( ULONG ulFLAG, bool bUpdate = false );
		void    _SetFlag( ULONG index, ULONG ulFLAG );
		void    _ResetFlag( ULONG index, ULONG ulFLAG );
		bool    _CheckFlag( ULONG index, ULONG ulFLAG );
		bool    _CheckMask( ULONG index, ULONG ulMASK );
		bool    _CheckLastMask( ULONG index, ULONG ulMASK );

		EMS_RESULT _OutputSchedule( ULONG ipass );
		EMS_RESULT _SetPass( ULONG ipass );
		EMS_RESULT _ResetPass( ULONG ipass );

		ULONG   _NchooseK( ULONG N, ULONG K );
		ULONG	_GetAllCombinations( ULONG N, ULONG K );
		LONG	_FindAntennaIndex ( ULONG ulAntennaID );
		LONG	_FindSatelliteIndex ( ULONG ulSatID );
		LONG    _FindPassIndex ( ULONG ulAntennaID, ULONG ulSatID );
		EMSAZELVECTORD _GetAzimuthElevation(  EMSTIMECOORDD vCoord, EMSLOCATION siteLocation );
		std::string	_ConvertToDateTimeString( EMSTIME t );

		ULONG _AddtoList( ULONG item, LONG *lpList, ULONG nSize );
		ULONG _RemovefromList( ULONG item, LONG *lpList, ULONG nSize );


	private: // data
		EMSLOCATION m_lpAntennaLocation[MAXANT];
		EMSLOCATION m_lpTestLocation[MAXTESTLOCATIONS];
		EMSVECTORD  m_lpTestXYZ[MAXTESTLOCATIONS];
		ULONG       m_ulTestCount;

		double		m_dMaxPassDuration;
		double		m_dMinPassDuration;
		double		m_dMinElevation;
		double		m_dMinSeparationAngle;

		IEMSOrbit4	*m_lpOrbit;
		IEMSSiteInfo *m_lpSiteInfo;
		
		PASSDATA	*m_lpPassArray;
		ULONG		m_ulPassCount;
		
		ULONG		*m_lpPassList;
		ULONG		m_ulPassListCount;

		SATDATA		*m_lpSatArray;
		ULONG		m_ulSatelliteCount;
		
		ANTDATA		*m_lpAntArray;
		ULONG		m_ulAntennaCount;

		LONG m_SatelliteIndex[MAXSAT];
		LONG m_AntennaIndex[MAXANT];
		LONG m_UniqueSatelliteIndex[MAXSAT];
		LONG m_UniqueAntennaIndex[MAXANT];
		LONG m_CombinationIndex[MAXANT];
		LONG m_AllCombinations[MAXCOMBINATIONS][MAXANT];
		LONG m_ulIndexCount;

		ULONG m_ulUniqueAntennas;
		ULONG m_ulUniqueSatellites;
		
		double m_X[MAXSAT][3];
		double m_Y[MAXSAT][3];
		double m_JDOPfactor;

		EMSTIME m_StartTime;
		EMSTIME m_StopTime;
		double  m_dTimeIncrement;

		FILE 	*m_lpSatelliteVectorFile;
		FILE 	*m_lpTrackPlanFile;
		FILE 	*m_lpTraceFile;
		bool    m_bTraceFile;


};

#pragma pack()
#endif

