/********************************************************************
*	Module:			PasSched.h
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
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	02/08/12		rvw	start

********************************************************************/
#ifndef INC_PASSCHED
#define INC_PASSCHED

#include <time.h>
#include <stdio.h>
#include <process.h>

#include "emspass.h"			// Pass Schedule Object
#include "emstrack.h"			// IEMSTrackSchedule
#include "leosite.h" 			// EMSSCHEDULEINFO
#include "emsit260.h"			// CEMSSit260
#include "emsorbit.h"			// IEMSOrbit

#define EMS_MAX_SATELLITES			(128)
#define EMS_MAX_LUTS				(64)

#define EMS_PS_FLAG_PREPASS			(0x1)
#define EMS_PS_FLAG_START			(0x2)
#define EMS_PS_FLAG_STOP			(0x4)
#define EMS_PS_FLAG_POSTPASS		(0x8)
#define EMS_PS_FLAG_IGNORE			(0x10)
#define EMS_PS_FLAG_ANTENNA			(0x20)

// want to make sure there are no "gaps" in the data structure
#pragma pack(1)

typedef struct _tagEMSPASSSCHEDDATA
{
	ULONG					ulCount;
	ULONG					ulIndex;
	EMSTIME					timeCreated;
	EMSTIME					timeInstalled;
	EMSTIME					timeRenew;
	EMSTIME					timeOldest;
	WORD					wState[ EMS_MAX_NUM_OPT_SAT_PASSES ];
	EMSTIME					timePrePass[ EMS_MAX_NUM_OPT_SAT_PASSES ];
	EMSSATELLITETRACK		track[ EMS_MAX_NUM_OPT_SAT_PASSES ];
} EMSPASSSCHEDDATA, *LPEMSPASSSCHEDDATA;

#pragma pack()

typedef const enum
{
	PASS_VALID					= 0, 
	PASS_INVALIDPAST			= 1, 
	PASS_INVALIDFUTURE			= 2, 
	PASS_INVALIDTIMETOLERANCE	= 3, 
} EMSPASSVALIDATION;

class CEMSPassSchedule 
{
public:
	CEMSPassSchedule();
	virtual ~CEMSPassSchedule();

	EMS_RESULT Initialize( EMSSCHEDULEINFO settings, ULONG *lpulSatellites, ULONG ulSatCount, 
		ULONG ulLutID, EMSLOCATION locationLut, ULONG *lpulSecondaryLUTs=0,
		ULONG ulSecondaryLUTCount=0, 	IEMSTrackSchedule *lpTrackSchedObj = 0 ,
		IEMSOrbit *lpOrbit = 0 );

	EMS_RESULT Reset( void );

	EMS_RESULT SetDataDirectory( LPCTSTR lpcszDataDirectory );

	EMS_RESULT MarkPassToBeProcessed( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber );
	EMS_RESULT MarkPassToBeSuppressed( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber );

	EMS_RESULT GenerateNewPassScheduleInBackground( void );
	
	EMS_RESULT InstallGeneratedSchedule( void );
	EMS_RESULT InstallScheduleFromFile( void );
	EMS_RESULT InstallScheduleFromSitMsg( CEMSSit260A *lpSitMsg );
	EMS_RESULT InstallSchedule( ULONG ulLutID, EMSSCHEDUSAGE eUsage, 
								LONG lSatelliteCount, EMSSATELLITETRACK **apPasses );
	
	EMS_RESULT ValidateSchedule(	CEMSSit260A*		lpSitMsg );
    EMS_RESULT ValidateSchedule(	ULONG				ulLutID, 
									LONG				lSatelliteCount, 
									EMSSATELLITETRACK**	apPasses );

	EMS_RESULT GeneratePassSchedule( EMSTIME timeStart=CEMSTime(0) );
	void SetSettings( EMSSCHEDULEINFO settings ) { m_schedSettings = settings; }

	INT GetValidPassCount( void );

	BOOL LockSchedule( BOOL bWait=TRUE );
	void UnlockSchedule( void );

	inline ULONG GetCount( void ) { return m_sched.ulCount; }
	inline ULONG GetIndex( void ) { return m_sched.ulIndex; }
	inline void SetIndex( ULONG ulIndex ) { m_sched.ulIndex = ulIndex; }

	inline EMSTIME GetTimeRenew( void ) { return m_sched.timeRenew; }
	inline EMSTIME GetTimeInstalled( void ) { return m_sched.timeInstalled; }

	WORD GetState( ULONG ulIndex );
	void SetState( ULONG ulIndex, WORD wState );
	void AddState( ULONG ulIndex, WORD wState );

	ULONG GetOrbitNumber( ULONG ulIndex );
	EMSTIME GetPrePassTime( ULONG ulIndex );
	ULONG GetSatID( ULONG ulIndex );
	EMSTIME GetLOSTime( ULONG ulIndex );
	EMSTIME GetActualLOSTime( ULONG ulIndex );
	EMSTIME GetAOSTime( ULONG ulIndex );
	EMSTIME GetActualAOSTime( ULONG ulIndex );
	EMSSATELLITETRACK *GetTrackPtr( ULONG ulIndex );

	bool IsPassConflict( EMSTIME timeStart, double dDuration, bool bIncludeSuppress=FALSE );
	bool IsPassTruncated( ULONG ulIndex );

	inline BOOL NewScheduleWasGenerated( void ) { return m_bNewScheduleGenerated; }
	inline void ResetNewScheduleWasGenerated( void ) { m_bNewScheduleGenerated = FALSE; }

	inline BOOL NewScheduleWasInstalled( void ) { return m_bNewScheduleInstalled; }
	inline void ResetNewScheduleWasInstalled( void ) { m_bNewScheduleInstalled = FALSE; }
	inline void SetPrePassDuration( double dSeconds ) { m_dPrePassDuration = dSeconds; }

	inline EMS_RESULT	GetLastErrorCode (void) { return m_hrLastError; }
	inline void			SetLastErrorCode (EMS_RESULT hr) {  m_hrLastError = hr; }

private: // methods
	EMSDEGREES _GetAzimuth( ULONG ulSatID, CEMSTime timeT );
	EMS_RESULT _RemoveExpiredEntries( void );
	EMS_RESULT _DeleteEntry( int nIndex );
	EMS_RESULT _AddTrackToSchedule( EMSSATELLITETRACK *lpTrackInfo );
	void _SetTrackInfo( EMSSATELLITETRACK *lpTrackInfo, LPEMSSIT260DATA lpSitData ); 
	EMS_RESULT _ValidatePass(	BOOL&				bValid,
								ULONG				ulSatID, 
								ULONG*				ulPassID, 
								CEMSTime			timeAOS, 
								CEMSTime			timeLOS, 
								EMSSATELLITEPASS*	lpPassInfo, 
								ULONG				ulCount );
	EMS_RESULT _ValidatePass(	BOOL&	bValid,
								ULONG	ulSatID, 
								ULONG*	ulPassID, 
								EMSTIME	timeAOS, 
								EMSTIME	timeLOS,
								ULONG	ulLutID = 0 );
	EMS_RESULT _ValidatePass(	EMSPASSVALIDATION&	eValid,
								ULONG				ulSatID,
								ULONG*				lpPassID, 
								CEMSTime			timeAOS, 
								CEMSTime			timeLOS,
								ULONG				ulLutID = 0 );

	EMS_RESULT _LoadScheduleFromFile( void );
	EMS_RESULT _SaveScheduleToFile( void );
	EMS_RESULT _WriteScheduleToTextFile( void );
	EMS_RESULT _OpenFileWhenNotBusy( FILE **lplpFilePtr, LPCTSTR lpcszFile, LPCTSTR lpcszOptions );
	void _ReadFile(  void *lpBuffer, size_t size, size_t count, FILE *lpFile );
	void _WriteFile( const void *lpBuffer, size_t size, size_t count, FILE *lpFile );
	int _FindPassIndex( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber=0 );

	EMS_RESULT _InstallPassSchedule( BOOL bSaveToDisk=TRUE );
	EMS_RESULT _BackgroundGenerateSchedule( void );
	EMS_RESULT _SortPassSchedule( void );
	EMS_RESULT _InitPassSchedule( void );
	EMS_RESULT _CalcPrePassTimes( void );
	EMS_RESULT _DetermineOldestScheduleTime( EMSTIME *lpTimeOldest );
	EMS_RESULT _DetermineRenewScheduleTime( EMSTIME *lpTimeOldest );
	EMS_RESULT _SendTrackSchedule( void );
	EMS_RESULT _WaitForThreadsToComplete( void );
	void _ResetThreadHandle( void ) { m_hThread = INVALID_HANDLE_VALUE; }
		
	bool _IsTruncatedAllowed( void ) { return ( ( m_schedSettings.flags & EMSSchedFlag_AcceptTruncated )
																	== EMSSchedFlag_AcceptTruncated ); }

	EMS_RESULT _GetSatelliteAZEL( ULONG ulSatID, EMSTIME timeNow, EMSLOCATION location, LPEMSAZELVECTOR lpAzElVector );
	ULONG _GetOrbitNumber( ULONG ulSatID, EMSTIME t );
	EMSTIME _DeterminePeakTime( ULONG ulSatID, CEMSTime timeAOS, CEMSTime timeLOS );
	EMSDEGREES _GetMinElevation( ULONG ulSatID, CEMSTime timeAOS, CEMSTime timeLOS );

	friend  unsigned __stdcall _GetScheduleThreadRoutine( void *pThis );

private: // data
	HANDLE					m_hThread;
	unsigned 				m_unThreadID;
	HANDLE					m_hMutexSchedule;
	EMSPASSSCHEDDATA		m_sched;
	EMSSCHEDULEINFO		m_schedSettings;

	ULONG						m_ulLutID;
	ULONG						m_ulSatCount;
	ULONG						m_ulSatellites[ EMS_MAX_SATELLITES ];
	LPTSTR					m_lpszDataDirectory;
	LPEMSTRACKSCHEDULE 	m_lpTrackSched;
	IEMSOrbit				*m_lpOrbit;
	BOOL						m_bFirstTimeAfterStartup;

	ULONG						m_ulSecondaryLutCount;
	ULONG						m_ulSecondaryLuts[ EMS_MAX_LUTS ];

	BOOL 						m_bNewScheduleGenerated;
	BOOL 						m_bNewScheduleInstalled;
	double					m_dPrePassDuration;
	EMS_RESULT					m_hrLastError;
	EMSLOCATION				m_locationLUT;
};

#endif // INC_PASSCHED
