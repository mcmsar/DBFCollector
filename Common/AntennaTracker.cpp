#include "AntennaTracker.h"
#include "EMSTime.h"
#include <math.h>
#include <tchar.h>
#include "EMSClock.h"
#include <stdio.h>
#include "debugwin.h"
#include "antmsgs.h"
#include "EMSDEVICES.h"

const DWORD c_dwMSecWaitReset = 15000; // 15 seconds max to wait on forced shutdown

#ifdef _DEBUG

//#define _DEBUG_IGNORE_ELEVATION 1

//	#define _DEBUG_WRITEPROPOSEDTRACK	1
//
//	#define _DEBUG_WRITEACTUALTRACK 1
//	#define _DEBUG_WRITELOGFILE		1
	FILE	*g_pAntTrkrLogFile;
	FILE	*g_pAntActualTrackFile;
	FILE	*g_pAntThreadLogFile=NULL;
//	#define _DEBUG_USEDEBUGWINDOW 1
	BOOL	g_bAntennaTrackerIsDoneTrack;



	//#define _DEBUG_DEVICENOTWORKING	1		// for when the device is reporting back totally bogus position data
	//#define _DEBUG_RANDOMSTARTPOS	1

	#define _DEBUG_USEDEBUGWINDOW 1

#endif

#ifdef _DEBUG_USEDEBUGWINDOW
	static CDebugWin	g_theDebugWindow;
#endif


#ifdef _DEBUG_WRITELOGFILE
	#define EMS_OUTPUTDEBUGMSG(Source,szMsg)  EMS_OutputDebugMsg(Source,szMsg);
#else
	#define EMS_OUTPUTDEBUGMSG(Source,szMsg)
#endif

void EMS_OutputDebugMsg(long SourceID,char *szMsg)
{
	switch (SourceID)
	{
	case 0:
#ifdef _DEBUG
        if (g_pAntThreadLogFile==NULL)
		{
			char	l_szFileName[2024];
			CEMSTime	l_CurTime;
			EMSTIMEFIELDS	l_CurTimeEx;

			l_CurTime=CEMSSystemClock::GetTime();
			l_CurTime.GetTime(&l_CurTimeEx);
			sprintf(l_szFileName,"c:\\temp\\AntTrackMsgLog_%02d_%02d_%04d__%02d_%02d_%02d___%d.txt",
								 l_CurTimeEx.nDay,
								 l_CurTimeEx.nMonth,
								 l_CurTimeEx.nYear,
								 l_CurTimeEx.nHour,
								 l_CurTimeEx.nMinute,
								 l_CurTimeEx.nSecond,
								 GetTickCount());
			g_pAntThreadLogFile=fopen(l_szFileName,"w+c");
		};
		if (g_pAntThreadLogFile!=NULL)
		{
			char		l_szTimestamp[1024];
			CEMSTime	l_CurTime;
			EMSTIMEFIELDS	l_CurTimeEx;

			
			l_CurTime=CEMSSystemClock::GetTime();
			l_CurTime.GetTime(&l_CurTimeEx);
			sprintf(l_szTimestamp,"%02d_%02d_%04d  %02d:%02d:%02d : ",
					l_CurTimeEx.nDay,
					l_CurTimeEx.nMonth,
					l_CurTimeEx.nYear,
					l_CurTimeEx.nHour,
					l_CurTimeEx.nMinute,
					l_CurTimeEx.nSecond);
			fwrite((void*)l_szTimestamp,strlen(l_szTimestamp),1,g_pAntThreadLogFile);
			fwrite((void*)szMsg,strlen(szMsg),1,g_pAntThreadLogFile);
			fflush(g_pAntThreadLogFile);
		};
#endif
		break;
	};
};

DWORD WINAPI AntennaTracker::WorkerThreadEnterFunc(LPVOID lpParam)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::WorkerThreadEnterFunc
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		lpParam		: pointer to an AntennaTracker object that has called this function

  STATIC FUNCTION
  
Description:	
	calls the worker thread for the given object
	this is just a placeholder for windows since it doesn't seem to like
	accessing regular (non-static) class member functions direcly
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	AntennaTracker *l_pAT;

	l_pAT=(AntennaTracker *)lpParam;
	if (l_pAT!=NULL)
	{
		return l_pAT->WorkerThread();
	} else {
		return 0;
	};
}

AntennaTracker::AntennaTracker()
{
	m_pIAntenna=NULL;
	m_pIAntInfo=NULL;
	m_hWorkerThread=NULL;
	m_hEventNewTrackReceived=NULL;
	m_hEventThreadStopped=NULL;
	m_hEventThreadStopRequest=NULL;
	m_hMutex_Buffer=NULL;
	m_NextTrack.m_IntervalCount=-1;
	m_NextTrack.m_pCoords=NULL;
	m_MaxSpeed.degElevation=18.0;
	m_MaxSpeed.degAzimuth=18.0;
	m_HomeTime=60*1000; // 60 seconds
	m_BeamWidth=7.5;
	m_MaxTravel.degElevation=95.0;
	m_MinTravel.degElevation=0.0;
	m_MaxTravel.degAzimuth=270.0;
	m_MinTravel.degAzimuth=-270.0;
	m_ResponseLatency_ms=50;
	m_DevicePollInterval_ms=1000; 
	m_HomeLocation.degAzimuth=0.0;
	m_HomeLocation.degElevation=0.0;
	m_MaxOutOfBeamDuration_ms= 1000 * 60 * 17;
	m_CruiseSpeedFactor=0.25;
	m_hMutex_Status=NULL;
	m_hEvent_Notification=NULL;

	OutputDebugString("AntennaTracker Object Created\n");

#ifdef _DEBUG_USEDEBUGWINDOW
	g_theDebugWindow.OutputMsg("AntennaTracker Object Created\n");
#endif

#ifdef _DEBUG
	g_pAntActualTrackFile=NULL;
#endif

    m_pLogger=NULL;
}

AntennaTracker::~AntennaTracker()
{
	Reset();


	OutputDebugString("AntennaTracker Object Destroyed\n");

#ifdef _DEBUG_USEDEBUGWINDOW
	g_theDebugWindow.OutputMsg("AntennaTracker Object Destroyed\n");
#endif

#ifdef _DEBUG
	if (g_pAntThreadLogFile!=NULL)
	{
		fclose(g_pAntThreadLogFile);
		g_pAntThreadLogFile=NULL;
	};
#endif
}

BOOL AntennaTracker::Init(IEMSAntennaDevice *pIAntenna, EMSANTENNAINFO *pIAntInfo, IEMSLeo600Logger *pILogger)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::Init
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		pIAntenna	: Pointer to an antennadevice interface
				pIAntInfo	: Status structure - cannot be NULL
				pILogger	: pointer to the logger interface
			
Description:	
	initialise the object
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO		NOTE
	0.0.1	10DEC2001	Morgan	Added mutex for status
	0.0.2	10DEC2001	Morgan	Uncommented code to retrieve parameters from the device
	0.0.3	06FEB2002	Morgan	Added Logger Interface
*/
{
	BOOL	l_bResult;
	DWORD	l_ThreadID;
	HRESULT	l_hResult;
//	LPEMSDEVICE l_lpd;

	l_bResult=FALSE;

	// just in case somebody calls this function twice in a row
	// and stuff is already open
	Reset(); 

	if ((pIAntenna!=NULL) && (pIAntInfo!=NULL))
	{
		#ifdef _DEBUG_WRITELOGFILE
			g_pAntTrkrLogFile=fopen("c:\\temp\\AntTrkrLogfile.txt","w+c");
		#endif

		#ifdef _DEBUG_WRITEACTUALTRACK
			g_pAntActualTrackFile=fopen("c:\\temp\\AntActualTrack.txt","w+c");
		#endif

		#ifdef _DEBUG_WRITEPROPOSEDTRACK
			FILE *l_pProposedFile=fopen("c:\\temp\\ProposedTrack.txt","w+c");
			if (l_pProposedFile!=NULL)
			{
				fclose(l_pProposedFile);
			};
			l_pProposedFile=NULL;
		#endif

		pIAntenna->AddRef();
//		pIAntenna->Initialize(0);
//		pIAntenna->GetParentDevice( &l_lpd );
//		l_lpd->Initialize(0);
//		l_lpd->Release();
		m_pIAntenna=pIAntenna;
		m_pIAntInfo=pIAntInfo;

		m_pLogger=pILogger; /* revision 0.0.3 */

		m_hMutex_Status=CreateMutex(NULL,FALSE,NULL); /* revision 0.0.1 */

		// retrieve some essential parameters for the anntenna operation
		/* revision 0.0.2 */
		l_hResult=m_pIAntenna->GetMaxSpeed(&m_MaxSpeed);
		if (l_hResult!=S_OK)
		{
			// do what???
		};
		m_pIAntenna->GetHomeTime((ULONG *)&m_HomeTime);
		m_pIAntenna->GetBeamWidth(&m_BeamWidth);
		m_pIAntenna->GetMinElevation(&(m_MinTravel.degElevation));
		m_pIAntenna->GetMaxElevation(&(m_MaxTravel.degElevation));
		m_pIAntenna->GetMaxAzimuth(&(m_MaxTravel.degAzimuth));
		m_MinTravel.degAzimuth=-1.0*m_MaxTravel.degAzimuth; // assume travel is symetrical about 0 degrees (North)
		m_pIAntenna->GetHomePosition(&m_HomeLocation);

		// create all the necessary event handles
		m_hEventThreadStopRequest=CreateEvent(NULL,TRUE,FALSE,NULL);
		m_hEventThreadStopped=CreateEvent(NULL,TRUE,FALSE,NULL);
		m_hEventNewTrackReceived=CreateEvent(NULL,TRUE,FALSE,NULL);

		if ((m_hEventThreadStopRequest!=NULL) &&
			(m_hEventThreadStopped!=NULL) &&
			(m_hEventNewTrackReceived!=NULL))
		{

			m_hMutex_Buffer=CreateMutex(NULL,FALSE,NULL);

			if (m_hMutex_Buffer!=NULL)
			{
				m_hWorkerThread=CreateThread(NULL,
											 0,
											 AntennaTracker::WorkerThreadEnterFunc,
											 (void *)this,
											 0,				// default flags
											 &l_ThreadID);

				if (m_hWorkerThread!=NULL)
				{
					l_bResult=TRUE;
				} else {
					Beep(401,250);
				};
			};
		};
	};

	return l_bResult;
}

BOOL AntennaTracker::Reset()
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::Reset
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		
			
Description:	
	shutdown the object
	This function should ALWAYS be safe to call
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO		NOTE
	0.0.1	10DEC2001	Morgan	Added Mutex for status
*/
{

	if (m_hWorkerThread!=NULL)
	{
		// kill the thread here
		// request a stop
		SetEvent(m_hEventThreadStopRequest);

		DWORD dwResult = WaitForSingleObject(m_hEventThreadStopped, c_dwMSecWaitReset );

		switch ( dwResult )
		{
			case WAIT_TIMEOUT:
				_LogInfoMsg( EMS_ANT_RESET_WAIT_TIMEOUT );

				TerminateThread( m_hWorkerThread, 0 );
				break;

			case WAIT_ABANDONED:
				_LogInfoMsg( EMS_ANT_RESET_WAIT_ABANDONED );

				TerminateThread( m_hWorkerThread, 0 );
				break;
		}
		ResetEvent(m_hEventThreadStopped);

		ResetEvent(m_hEventThreadStopRequest);

		CloseHandle(m_hWorkerThread);
		m_hWorkerThread=NULL;
	};

	if (m_pIAntenna!=NULL)
	{
		LPEMSDEVICE l_lpd = 0;

		m_pIAntenna->GetParentDevice(&l_lpd);

		if ( l_lpd )
		{
			l_lpd->Reset();
			l_lpd->Release();
			l_lpd = 0;
		}

		m_pIAntenna->Release();
		m_pIAntenna=NULL;
	};

	m_pIAntInfo=NULL;
	m_pLogger=NULL;

	if (m_hEventNewTrackReceived!=NULL)
	{
		CloseHandle(m_hEventNewTrackReceived);
		m_hEventNewTrackReceived=NULL;	
	};

	if (m_hEventThreadStopped!=NULL)
	{
		CloseHandle(m_hEventThreadStopped);
		m_hEventThreadStopped=NULL;
	};

	if (m_hEventThreadStopRequest!=NULL)
	{
		CloseHandle(m_hEventThreadStopRequest);
		m_hEventThreadStopRequest=NULL;
	};

	if (m_hMutex_Buffer!=NULL)
	{
		CloseHandle(m_hMutex_Buffer);
		m_hMutex_Buffer=NULL;
	};

	if (m_hMutex_Status!=NULL)
	{
		CloseHandle(m_hMutex_Status);
		m_hMutex_Status=NULL;
	};

	// clean up m_NextTrack
	if (m_NextTrack.m_pCoords!=NULL)
	{
		free(m_NextTrack.m_pCoords);
		m_NextTrack.m_pCoords=NULL;
	};
	m_NextTrack.m_IntervalCount=-1;

	#ifdef _DEBUG_WRITELOGFILE
		if (g_pAntTrkrLogFile!=NULL)
		{
			fclose(g_pAntTrkrLogFile);
			g_pAntTrkrLogFile=NULL;
		};
	#endif

	#ifdef _DEBUG_WRITEACTUALTRACK
		if (g_pAntActualTrackFile!=NULL)
		{
			fclose(g_pAntActualTrackFile);
			g_pAntActualTrackFile=NULL;
		};
	#endif

	return FALSE;
}

BOOL AntennaTracker::NewTrack(EMSTIME StartTime, long TimeInterval, long IntervalCount, EMSENUVECTOR *IntervalCoords)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::NewTrack
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		StartTime		: time to start the track
				TimeInterval	: time between coordinates (ms)
				IntervalCount	: number of coordinates in the track
				IntervalCoords	: array of interval coordinates
			
Description:	
	receives a new track for placement into the queue of tracks to be executed
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO		NOTE
	0.0.1	04FEB2002	Morgan	Added code to detect if buffer could not be locked
*/
{
	EMS_OUTPUTDEBUGMSG(0,"New Track Start\r");

	BOOL	l_bResult;
	BOOL	l_bBufferAlreadyFull;
	long	l_Ndx;
	CEMSCoordSystem	l_CoordSys;
	BOOL	l_bTempResult;

	l_bResult=FALSE;

	l_bTempResult=LockBuffer(TRUE); // prevent worked thread from playing with the buffer

	/* revision 0.0.1 */
	if (l_bTempResult==FALSE)
	{
		EMS_OUTPUTDEBUGMSG(0,"New Track - LockBuffer Failed\r");
		return FALSE;
	};

	// check to see if the buffer already has something in it
	if (m_NextTrack.m_IntervalCount>0)
	{
		l_bBufferAlreadyFull=TRUE;
	} else {
		l_bBufferAlreadyFull=FALSE;
	};
	if (l_bBufferAlreadyFull==TRUE)
	{
		// buffer already in use - dump out and ignore the new data provided
		l_bResult=FALSE;
	} else {
		m_NextTrack.m_IntervalCount=IntervalCount;
		m_NextTrack.m_StartTime=StartTime;
		m_NextTrack.m_IntervalSize=TimeInterval;

		// copy entries propery
		m_NextTrack.m_pCoords=(EMSAZELVECTOR*)malloc(sizeof(EMSAZELVECTOR)*(IntervalCount+1));
		if (m_NextTrack.m_pCoords!=NULL)
		{
			for (l_Ndx=0;l_Ndx<IntervalCount;l_Ndx++)
			{
				m_NextTrack.m_pCoords[l_Ndx]=l_CoordSys.ToAzimuthAndElevation(IntervalCoords[l_Ndx]);
			};
			SetEvent(m_hEventNewTrackReceived);
			l_bResult=TRUE;
		} else {
			m_NextTrack.m_IntervalCount=-1;
			ReportError(ANTTRKR_ERR_MEMORYFAILURE,"Error Allocation Memory for coordinates");

		};

	};

	EMS_OUTPUTDEBUGMSG(0,"New Track End\r");
	UnlockBuffer(); // release the lock on the buffer

	return l_bResult;
}


DWORD AntennaTracker::WorkerThread()
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::WorkerThread
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		
			
Description:	
	Worker thread which does all the main calculations for the object
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO		NOTE
	0.0.1	04DEC2001	Morgan	Added proper values for the antenna device status bit fields
	0.0.2	07DEC2001	Morgan	fixed bug which reported an error  when only 1 axis was finished homing
	0.0.3	10DEC2001	Morgan	Added Status Mutex locking to protect the status info
	0.0.4	24JAN2002	Morgan	Added a signal event for when the track is finished
	0.0.5	05FEB2002	Morgan	Added a limit to the number of smoothing pass iterations
	0.0.6	06FEB2002	Morgan	Added a limit to the amount of time between position reports from the axis
	0.0.7	06FEB2002	Morgan	Added status flags filling for the antennastatusinfo structure
	0.0.8	18FEB2002	Morgan	Added a limit to the number of iterations when creating AdjRawTrack
	0.0.9	02JAN2003	Morgan	Corrected Exiting code when a stop is received in an inner wait (not the first outer one)
*/
{
#define ANTDEVSTATUS_ISHOME		EMS_ANTENNA_HOME	// device has completed a home and is at the home location 
#define ANTDEVSTATUS_FAULTED	EMS_ANTENNA_ERROR	// Device is faulted

	const char* HANDLEGUID = "{F65A6F40-64A1-46d8-809D-5F4E8AB1BA5C}";

	HANDLE	l_hEvents[3];
	long	l_SignalledEvent;
	BOOL	l_bExitThread;
	Antenna_Track	l_RawTrack;
	EMSAZEL			*l_AdjRawTrack;		// normalised raw track for wire wrap - coordinates stay the same as Raw but trimmed to possible values
	EMSAZEL			*l_AdjRawRawTrack;	// normalised raw track for wire wrap - coordinates stay the same as Raw 
	EMSAZEL			*l_ProposedTrack;	// track to actually follow
	long			l_ProposedTrack_NumIntervals;	// number of intervals for the proposed track
	EMSAZEL			*l_ProposedSpeeds;	// values are in degrees per second
	//EMSDEGREES		*l_ProposedDegError; // error in degrees
	//EMSAZEL			*l_ActualTrack;
	//EMSDEGREES		*l_ActualDegError;	// error in degrees
	long			l_Ndx;
	double			l_MaxAzimuth;
	double			l_MinAzimuth;
	EMSAZEL			l_MaxSpeeds;
	long			l_MaxAzSpeedNdx;
	long			l_MaxElSpeedNdx;
	EMSAZEL			l_CurrentPosition;	// current position of the antenna
	CEMSTime		l_CurTime;
	CEMSTime		l_StartHomeTime;
	BOOL			l_bExecutingAHome;	// indicates that a home is being executed
	HANDLE			l_hDeviceStateEvent;	// Event for the Antenna Device
	ULONG			l_AntennaDeviceStatus;	// status from the antennaDevice
	BOOL			l_bHardwareErrorDetected;	// TRUE when a hardware error has been detected (i.e. cancel the move)
	long			l_lSmoothingPassCount;		// counts the number of smoothing iterations that have been done
	const long		l_lMaxSmoothingPassCount=25;	// maximum allowable smoothing passes
	const double	l_MaxTimeSinceAxisPositionReport=15; // maximum time between position reports from the axis during tracking
	Antenna_Track	l_BackupRawTrack;
	TCHAR			szMsg[256];

	l_hDeviceStateEvent=CreateEvent(NULL,FALSE,FALSE,HANDLEGUID);
	m_pIAntenna->SetHandle(strlen(HANDLEGUID), (char*)HANDLEGUID);

	l_hEvents[0]=m_hEventThreadStopRequest;
	l_hEvents[1]=m_hEventNewTrackReceived;
	l_hEvents[2]=l_hDeviceStateEvent;

	if (m_pIAntInfo!=NULL)
	{
		if (LockStatus(5000)!=FALSE)
		{
			m_pIAntInfo->uAntennaStatus=0; // clean out the antenna completely
			UnlockStatus();
		};
	};

	//LogError(EMS_ANT_ERROR,"DEBUG MSG: This is the start of the EMS Antena thread");

	EMS_OUTPUTDEBUGMSG(0,"Thread Started\r");
	l_bExitThread=FALSE;
	while (l_bExitThread==FALSE)
	{
		try 
		{
			EMS_OUTPUTDEBUGMSG(0,"Begin thread wait for command\r");
			l_SignalledEvent=WaitForMultipleObjects(3,l_hEvents,FALSE,INFINITE);
			switch (l_SignalledEvent)
			{
			case WAIT_OBJECT_0:
				EMS_OUTPUTDEBUGMSG(0,"Exit thread event detected\r");
				m_exception.SetMark( __LINE__, __FILE__ );

				// m_hEventThreadStopRequest
				// end the thread
				l_bExitThread=TRUE;
				break;

			case WAIT_OBJECT_0+2:
				EMS_OUTPUTDEBUGMSG(0,"Device state event detected\r");
				m_exception.SetMark( __LINE__, __FILE__ );

				// l_hDeviceStateEvent
				// probably a fault event occuring - might need to change the status object
				break;

			case WAIT_OBJECT_0+1:
				m_exception.SetMark( __LINE__, __FILE__ );
				long	l_TrackPassAttempt=0; // attempt number for doing the pass
				BOOL	l_bTrackPassWasSuccessful=FALSE;

				if (m_pIAntInfo!=NULL)
				{
					if (LockStatus(5000)!=FALSE)
					{
						m_pIAntInfo->uAntennaStatus|=EMSANTINFOFLAG_STATUS_CALCTRACK;
						m_pIAntInfo->uAntennaStatus&=(!EMSANTINFOFLAG_STATUS_FAULT); // clear fault flag
						UnlockStatus();
					};
				};
				EMS_OUTPUTDEBUGMSG(0,"New Track event detected\r");
				// open a new actual track logfile
				#ifdef _DEBUG_WRITEACTUALTRACK
				{
					char	l_szFileName[2024];
					CEMSTime	l_CurTime;
					EMSTIMEFIELDS	l_CurTimeEx;

					if (g_pAntActualTrackFile!=NULL)
					{
						fclose(g_pAntActualTrackFile);
					};
					l_CurTime=CEMSSystemClock::GetTime();
					l_CurTime.GetTime(&l_CurTimeEx);
					sprintf(l_szFileName,"c:\\temp\\AntActualTrack_%02d_%02d_%04d__%02d_%02d_%02d___%d.txt",
									 	l_CurTimeEx.nDay,
									 	l_CurTimeEx.nMonth,
									 	l_CurTimeEx.nYear,
									 	l_CurTimeEx.nHour,
									 	l_CurTimeEx.nMinute,
									 	l_CurTimeEx.nSecond,
									 	GetTickCount());
					g_pAntActualTrackFile=fopen(l_szFileName,"w+c");
				};
				#endif
				// m_hEventNewTrackReceived
				// transfer the data 
				EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Begin Transfer Track Data\r");
				if (LockBuffer(TRUE)!=FALSE)
				{
					l_RawTrack=m_NextTrack;
					m_NextTrack.m_IntervalCount=-1;
					m_NextTrack.m_pCoords=NULL;
					UnlockBuffer();
				} else {
					EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Error locking buffer in transfer track data\r");
					LogError(EMS_ANT_ERROR,"WorkerThread - Error locking buffer in transfer track data");
					l_RawTrack.m_IntervalCount=-10;
				};
				EMS_OUTPUTDEBUGMSG(0,"WorkerThread - End Transfer Track Data\r");
				ResetEvent(m_hEventNewTrackReceived);

				do {
					// backup the antenna track
					l_BackupRawTrack=l_RawTrack;
					l_BackupRawTrack.m_pCoords=(EMSAZELVECTOR *)malloc(sizeof(EMSAZELVECTOR)*(l_RawTrack.m_IntervalCount+1));
					if (l_BackupRawTrack.m_pCoords!=NULL)
					{
						memcpy(l_BackupRawTrack.m_pCoords,l_RawTrack.m_pCoords,sizeof(EMSAZELVECTOR)*l_RawTrack.m_IntervalCount);
					};

					// clear antenna status etc....
					if (m_pIAntInfo!=NULL)
					{
						if (LockStatus(5000)!=FALSE)
						{
							m_pIAntInfo->uAntennaStatus|=EMSANTINFOFLAG_STATUS_CALCTRACK;
							m_pIAntInfo->uAntennaStatus&=(!EMSANTINFOFLAG_STATUS_FAULT); // clear fault flag
							UnlockStatus();
						};
					};

					l_bHardwareErrorDetected=FALSE;

					// do a new track
					// step 1. adjust azimuth and elevation values to prevent wire wrapping
					if (l_RawTrack.m_IntervalCount!=-10)
					{
						l_AdjRawTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_RawTrack.m_IntervalCount+1));
					} else {
						l_AdjRawTrack=NULL;
						LogError(EMS_ANT_ERROR,"WorkerThread - Error Allocating memory for l_AdjRawTrack");
					};
					if (l_AdjRawTrack!=NULL)
					{
						m_exception.SetMark( __LINE__, __FILE__ );
						{
							TCHAR	l_szTempBuffer[1024];
							sprintf(l_szTempBuffer,"WorkerThread - l_RawTrack.m_IntervalCount=%d\r",
									l_RawTrack.m_IntervalCount);
							EMS_OUTPUTDEBUGMSG(0,l_szTempBuffer);
							sprintf(l_szTempBuffer,"WorkerThread - l_RawTrack.m_IntervalSize=%d\r",
									l_RawTrack.m_IntervalSize);
							EMS_OUTPUTDEBUGMSG(0,l_szTempBuffer);
						};
						l_AdjRawRawTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_RawTrack.m_IntervalCount+1));
						if (l_AdjRawRawTrack!=NULL)
						{
							m_exception.SetMark( __LINE__, __FILE__ );
							long	l_Counter_LimitIterations;

							for (l_Ndx=0;l_Ndx<l_RawTrack.m_IntervalCount;l_Ndx++)
							{
								l_AdjRawTrack[l_Ndx].degElevation=l_RawTrack.m_pCoords[l_Ndx].azel.degElevation;
								l_AdjRawTrack[l_Ndx].degAzimuth=l_RawTrack.m_pCoords[l_Ndx].azel.degAzimuth;

								// adjust elevation to keep it within the range - flip azimuth if required
								if (l_AdjRawTrack[l_Ndx].degElevation<m_MinTravel.degElevation)
								{
									l_AdjRawTrack[l_Ndx].degElevation=m_MinTravel.degElevation;
								};

								/*
								// Don't need to do a test for 90 since the input should be 0-90
								// mathmatical errors will sometimes generate values marginally above 90 degrees
								// but these should be ignored since no azimuth flip is required for 0.00000002 degrees
								// past 90.0
								if (l_AdjRawTrack[l_Ndx].degElevation>90.0)
								{
									l_AdjRawTrack[l_Ndx].degElevation=180.0-l_AdjRawTrack[l_Ndx].degElevation;
									l_AdjRawTrack[l_Ndx].degAzimuth+=180.0;
								};*/

								l_AdjRawRawTrack[l_Ndx].degElevation=l_AdjRawTrack[l_Ndx].degElevation;

								if (l_AdjRawTrack[l_Ndx].degElevation>m_MaxTravel.degElevation)
								{
									l_AdjRawTrack[l_Ndx].degElevation=m_MaxTravel.degElevation;
								};

								// adjust azimuth to keep it the minimum distance from the last azimuth
								if (l_Ndx>0)
								{
									l_Counter_LimitIterations=0;

									while (fabs(l_AdjRawTrack[l_Ndx].degAzimuth-l_AdjRawTrack[l_Ndx-1].degAzimuth)>
								   		fabs(l_AdjRawTrack[l_Ndx].degAzimuth+360.0-l_AdjRawTrack[l_Ndx-1].degAzimuth))
									{
										l_AdjRawTrack[l_Ndx].degAzimuth+=360.0;

										/* revision 0.0.8 */
										// limit the number of iterations in this routine
										l_Counter_LimitIterations++;
										if (l_Counter_LimitIterations>100)
										{
											EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Iteration error in writing AdjRawTrack (+360)\r");
											l_RawTrack.m_IntervalCount=-1;
											break;
										};
									};
									l_Counter_LimitIterations=0;
									while (fabs(l_AdjRawTrack[l_Ndx].degAzimuth-l_AdjRawTrack[l_Ndx-1].degAzimuth)>
								   		fabs(l_AdjRawTrack[l_Ndx].degAzimuth-360.0-l_AdjRawTrack[l_Ndx-1].degAzimuth))
									{
										l_AdjRawTrack[l_Ndx].degAzimuth-=360.0;

										/* revision 0.0.8 */
										// limit the number of iterations in this routine
										l_Counter_LimitIterations++;
										if (l_Counter_LimitIterations>100)
										{
											EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Iteration error in writing AdjRawTrack (-360)\r");
											l_RawTrack.m_IntervalCount=-1;
											break;
										};
									};
									l_MinAzimuth=min(l_MinAzimuth,l_AdjRawTrack[l_Ndx].degAzimuth);
									l_MaxAzimuth=max(l_MaxAzimuth,l_AdjRawTrack[l_Ndx].degAzimuth);
								} else {
									l_MaxAzimuth=l_MinAzimuth=l_AdjRawTrack[l_Ndx].degAzimuth;
								};

								l_AdjRawRawTrack[l_Ndx].degAzimuth=l_AdjRawTrack[l_Ndx].degAzimuth;
							};

							if (l_RawTrack.m_IntervalCount!=-1)
							{
								EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Adjust azimuth limits begin\r");
								// now need to possibly adjust the track to fit within the azimuth limits
								while (l_MinAzimuth<m_MinTravel.degAzimuth)
								{
									l_MinAzimuth+=360.0;
									l_MaxAzimuth+=360.0;
									for (l_Ndx=0;l_Ndx<l_RawTrack.m_IntervalCount;l_Ndx++)
									{
										l_AdjRawTrack[l_Ndx].degAzimuth+=360.0;
										l_AdjRawRawTrack[l_Ndx].degAzimuth=l_AdjRawTrack[l_Ndx].degAzimuth;
									};
								};
								while (l_MaxAzimuth>m_MaxTravel.degAzimuth)
								{
									l_MinAzimuth-=360.0;
									l_MaxAzimuth-=360.0;
									for (l_Ndx=0;l_Ndx<l_RawTrack.m_IntervalCount;l_Ndx++)
									{
										l_AdjRawTrack[l_Ndx].degAzimuth-=360.0;
										l_AdjRawRawTrack[l_Ndx].degAzimuth=l_AdjRawTrack[l_Ndx].degAzimuth;
									};
								};

								EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Adjust azimuth limits complete\r");
							};
							if ((l_MinAzimuth>=m_MinTravel.degAzimuth) && 
								(l_MaxAzimuth<=m_MaxTravel.degAzimuth) &&
								(l_RawTrack.m_IntervalCount!=-1))
							{
								m_exception.SetMark( __LINE__, __FILE__ );
								// azimuth values are ok
								l_ProposedTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_RawTrack.m_IntervalCount+1));
								if (l_ProposedTrack!=NULL)
								{
									l_ProposedTrack_NumIntervals=l_RawTrack.m_IntervalCount;
									l_ProposedSpeeds=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_RawTrack.m_IntervalCount+1));
									if (l_ProposedSpeeds!=NULL)
									{
										// tell the device to home itself
										// if there is time to do a home before it needs to execute
										// this is asynchronous
										l_CurTime=CEMSSystemClock::GetTime();
										if (l_CurTime.SecondsDifferent(l_RawTrack.m_StartTime)>((double)m_HomeTime)/1000.0+max(fabs(l_AdjRawTrack[0].degElevation-m_HomeLocation.degElevation)/m_MaxSpeed.degElevation,
																					       		fabs(l_AdjRawTrack[0].degAzimuth-m_HomeLocation.degAzimuth)/m_MaxSpeed.degAzimuth))
										{
											#ifdef _DEBUG_DEVICENOTWORKING
												l_bExecutingAHome=FALSE;
											#else
								 				l_bExecutingAHome=TRUE;
												EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Start the Home Execution\r");
												m_pIAntenna->Home( FALSE );
												l_StartHomeTime=CEMSSystemClock::GetTime();
											#endif

                                            // set homing status bit
					                        if( m_pIAntInfo != NULL )
					                        {
                                                EMSAZEL azelzero;
                                                azelzero.degAzimuth = 0.0;
                                                azelzero.degElevation = 0.0;
						                        if( LockStatus( 500 ) != FALSE )
						                        {
							                        m_pIAntInfo->uAntennaStatus |= 0x10;
                                                    m_pIAntInfo->azelDesired = azelzero;
							                        UnlockStatus();
						                        }
					                        }

										}
										else
										{
											l_bExecutingAHome=FALSE;
											_LogInfoMsg( EMS_ANT_SKIP_HOME );

                                      // clear homing status bit
					                  if( m_pIAntInfo != NULL )
					                  {
						                  if( LockStatus( 500 ) != FALSE )
						                  {
							                  m_pIAntInfo->uAntennaStatus &= ~0x10;
							                  UnlockStatus();
						                  }
					                  }
										}

										for (l_Ndx=0;l_Ndx<l_RawTrack.m_IntervalCount;l_Ndx++)
										{
											l_ProposedTrack[l_Ndx]=l_AdjRawTrack[l_Ndx];
										};

										l_lSmoothingPassCount=0; /* revision 0.0.5 */
										do {
											EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Do Proposed Track Smoothing iteration\r");
											l_MaxAzSpeedNdx=0;
											l_MaxElSpeedNdx=0;
											l_MaxSpeeds=l_ProposedSpeeds[0];
											for (l_Ndx=1;l_Ndx<l_RawTrack.m_IntervalCount;l_Ndx++)
											{
												l_ProposedSpeeds[l_Ndx-1].degAzimuth=(l_ProposedTrack[l_Ndx].degAzimuth-l_ProposedTrack[l_Ndx-1].degAzimuth)/
																		   		(((double)l_RawTrack.m_IntervalSize)/1000.0);
												l_ProposedSpeeds[l_Ndx-1].degElevation=(l_ProposedTrack[l_Ndx].degElevation-l_ProposedTrack[l_Ndx-1].degElevation)/
																		   		(((double)l_RawTrack.m_IntervalSize)/1000.0);
												if (l_Ndx==1)
												{
													l_MaxAzSpeedNdx=0;
													l_MaxElSpeedNdx=0;
													l_MaxSpeeds=l_ProposedSpeeds[0];
												} else {
													if (fabs(l_ProposedSpeeds[l_Ndx-1].degAzimuth)>l_MaxSpeeds.degAzimuth)
													{
														l_MaxSpeeds.degAzimuth=fabs(l_ProposedSpeeds[l_Ndx-1].degAzimuth);
														l_MaxAzSpeedNdx=l_Ndx-1;
													};
													if (fabs(l_ProposedSpeeds[l_Ndx-1].degElevation)>l_MaxSpeeds.degElevation)
													{
														l_MaxSpeeds.degElevation=fabs(l_ProposedSpeeds[l_Ndx-1].degElevation);
														l_MaxElSpeedNdx=l_Ndx-1;
													};
												};
											};

											// if the azimuth is moving too fast at one point,
											// blend out that faster section over the surrounding points
											// until it intersects the desired azimuth at both endpoints
											if (l_MaxSpeeds.degAzimuth>m_MaxSpeed.degAzimuth)
											{
												EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Proposed Track Smoothing Max Azimuth speed too fast\r");
												EMSDEGREES	l_NewSpeed; // new maximum speed to use
												EMSDEGREES	l_CentrePosition;	// new position at l_Ndx+0.5 to use in smoothing
												EMSDEGREES	l_NewCalcPosition;	// calculated new position to use
												BOOL		l_bDoneSmoothPass;

												l_Ndx=l_MaxAzSpeedNdx;
												if (l_ProposedSpeeds[l_Ndx].degAzimuth>0.0)
												{
													l_NewSpeed=m_MaxSpeed.degAzimuth;
												} else {
													l_NewSpeed=m_MaxSpeed.degAzimuth*-1.0;
												};

												l_CentrePosition=(l_ProposedTrack[l_Ndx].degAzimuth+l_ProposedTrack[l_Ndx+1].degAzimuth)/2.0;

												l_bDoneSmoothPass=FALSE;
												for (l_Ndx=l_MaxAzSpeedNdx+1;
											 		(l_bDoneSmoothPass==FALSE) && (l_Ndx<l_RawTrack.m_IntervalCount);
											 		l_Ndx++)
												{
													l_NewCalcPosition=l_CentrePosition+((double)l_Ndx-((double)l_MaxAzSpeedNdx+0.5))*
																			   		l_NewSpeed*
																			   		(l_RawTrack.m_IntervalSize/1000.0);
													if (l_NewSpeed>0.0)
													{
														if (l_NewCalcPosition<l_ProposedTrack[l_Ndx].degAzimuth)
														{
															l_ProposedTrack[l_Ndx].degAzimuth=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													} else {
														if (l_NewCalcPosition>l_ProposedTrack[l_Ndx].degAzimuth)
														{
															l_ProposedTrack[l_Ndx].degAzimuth=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													};
												};

												l_bDoneSmoothPass=FALSE;
												for (l_Ndx=l_MaxAzSpeedNdx;
											 		(l_bDoneSmoothPass==FALSE) && (l_Ndx>=0);
											 		l_Ndx--)
												{
													l_NewCalcPosition=l_CentrePosition+((double)l_Ndx-((double)l_MaxAzSpeedNdx+0.5))*
																			   		l_NewSpeed*
																			   		(l_RawTrack.m_IntervalSize/1000.0);
													if (l_NewSpeed>0.0)
													{
														if (l_NewCalcPosition>l_ProposedTrack[l_Ndx].degAzimuth)
														{
															l_ProposedTrack[l_Ndx].degAzimuth=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													} else {
														if (l_NewCalcPosition<l_ProposedTrack[l_Ndx].degAzimuth)
														{
															l_ProposedTrack[l_Ndx].degAzimuth=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													};
												};

											};

											// repeat smoothing algorithm for the elevation axis
											// if the Elevation is moving too fast at one point,
											// blend out that faster section over the surrounding points
											// until it intersects the desired Elevation at both endpoints
											if (l_MaxSpeeds.degElevation>m_MaxSpeed.degElevation)
											{
												EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Proposed Track Smoothing Max Elevation speed too fast\r");
												EMSDEGREES	l_NewSpeed; // new maximum speed to use
												EMSDEGREES	l_CentrePosition;	// new position at l_Ndx+0.5 to use in smoothing
												EMSDEGREES	l_NewCalcPosition;	// calculated new position to use
												BOOL		l_bDoneSmoothPass;

												l_Ndx=l_MaxElSpeedNdx;
												if (l_ProposedSpeeds[l_Ndx].degElevation>0.0)
												{
													l_NewSpeed=m_MaxSpeed.degElevation;
												} else {
													l_NewSpeed=m_MaxSpeed.degElevation*-1.0;
												};

												l_CentrePosition=(l_ProposedTrack[l_Ndx].degElevation+l_ProposedTrack[l_Ndx+1].degElevation)/2.0;

												l_bDoneSmoothPass=FALSE;
												for (l_Ndx=l_MaxElSpeedNdx+1;
											 		(l_bDoneSmoothPass==FALSE) && (l_Ndx<l_RawTrack.m_IntervalCount);
											 		l_Ndx++)
												{
													l_NewCalcPosition=l_CentrePosition+((double)l_Ndx-((double)l_MaxElSpeedNdx+0.5))*
																			   		l_NewSpeed*
																			   		(l_RawTrack.m_IntervalSize/1000.0);
													if (l_NewSpeed>0.0)
													{
														if (l_NewCalcPosition<l_ProposedTrack[l_Ndx].degElevation)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													} else {
														if (l_NewCalcPosition>l_ProposedTrack[l_Ndx].degElevation)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													};
												};

												l_bDoneSmoothPass=FALSE;
												for (l_Ndx=l_MaxElSpeedNdx;
											 		(l_bDoneSmoothPass==FALSE) && (l_Ndx>=0);
											 		l_Ndx--)
												{
													l_NewCalcPosition=l_CentrePosition+((double)l_Ndx-((double)l_MaxElSpeedNdx+0.5))*
																			   		l_NewSpeed*
																			   		(l_RawTrack.m_IntervalSize/1000.0);
													if (l_NewSpeed>0.0)
													{
														if (l_NewCalcPosition>l_ProposedTrack[l_Ndx].degElevation)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													} else {
														if (l_NewCalcPosition<l_ProposedTrack[l_Ndx].degElevation)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_NewCalcPosition;
														} else {
															l_bDoneSmoothPass=TRUE;
														};
													};
												};

											};

											// we now have a smoothed proposed path - next step - fix it in time

											l_lSmoothingPassCount++;

										} while (((l_MaxSpeeds.degAzimuth>m_MaxSpeed.degAzimuth) ||
										  		(l_MaxSpeeds.degElevation>m_MaxSpeed.degElevation)) &&
										  		(l_lSmoothingPassCount<=l_lMaxSmoothingPassCount));
										if (l_lSmoothingPassCount>l_lMaxSmoothingPassCount)
										{
											EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Proposed Track Smoothing  Too Many Smoothing iterations - smoothing abandonded\r");
											LogError(EMS_ANT_ERROR,"WorkerThread - Too Many smoothing iterations - Smoothing aborted");
										};
										EMS_OUTPUTDEBUGMSG(0,"WorkerThread - Proposed Track Smoothing Complete\r");

										// wait until device is homed (if home was requested)
										// or device error occurs
										EMS_OUTPUTDEBUGMSG(0,"Begin Homing Sequence Code\r");
										if( l_bExecutingAHome == TRUE )
										{
                                            long l_CurrentAttemptNumber = 0;    // 0-based attempt number
                                                                                // we are allowed up to 3 attempts
                                                                                // failure on attempt 1 means a message, 2 means a warning, 3 means an error and stop

                                            do
                                            {
                                                EMSAZEL azel;
                                                EMSTIME AZT, ELT;

												EMS_OUTPUTDEBUGMSG(0,"Home - Wait for signal\r");
												l_SignalledEvent = WaitForMultipleObjects( 3, l_hEvents, FALSE, 1000 );
												EMS_OUTPUTDEBUGMSG(0,"Home - signal received\r");
												switch (l_SignalledEvent)
												{
												case WAIT_OBJECT_0:
													// exit command - just dump out ASAP svp
													l_bHardwareErrorDetected=TRUE;
													l_bExitThread=TRUE; /* revision 0.0.9 */
													break;
												case WAIT_OBJECT_0+2: // antenna state
													break;
												case WAIT_TIMEOUT:
													//l_bHardwareErrorDetected=TRUE;
													break;
												}

												m_pIAntenna->GetStatus(&l_AntennaDeviceStatus);
                                                m_pIAntenna->GetPosition( &azel, &AZT, &ELT );

                                                // log antenna position
					                            if( m_pIAntInfo != NULL )
					                            {
						                            if( LockStatus( 500 ) != FALSE )
						                            {
							                            m_pIAntInfo->uAntennaStatus &= 0xFF;
                                                        m_pIAntInfo->uAntennaStatus |= (l_AntennaDeviceStatus & 0xF) << 8;
                                                        m_pIAntInfo->uAntennaStatus |= (l_AntennaDeviceStatus & 0xF00) << 4;
                                                        m_pIAntInfo->azelActual = azel;
							                            UnlockStatus();
						                            }
					                            }

                                                // check status to make sure it isn't faulted and is home
												if ((l_AntennaDeviceStatus&ANTDEVSTATUS_FAULTED)!=0)
												{
													EMS_OUTPUTDEBUGMSG(0,"Homing sequence - error detected\r");

													switch ( l_CurrentAttemptNumber )
													{
														case 0:
                                         case 1:
															_stprintf( szMsg, TEXT("%d"), (int)l_CurrentAttemptNumber );

															_LogInfoMsg( EMS_ANT_HOMING_FAULT_RETRY, szMsg, lstrlen( szMsg ) + 1 );

                                            Sleep(1000);
															m_pIAntenna->Home( FALSE );
															l_StartHomeTime=CEMSSystemClock::GetTime();
                                            Sleep(500);    //
															l_bHardwareErrorDetected=FALSE;
															break;

														default:
														case 2:
															_LogWarningMsg( EMS_ANT_HOMING_FAULT );
															l_bHardwareErrorDetected=TRUE;
															ReportError(ANTTRKR_ERR_HARDWARE,NULL);
															break;
													}

													l_CurrentAttemptNumber++;
												}
                                                else if( (l_AntennaDeviceStatus & ANTDEVSTATUS_ISHOME) == 0 ) 
												{
													// might just be a homeing issue
													// with only 1 axis homed - need to wait for both to be homed
													// check to make sure it hasn't waiting too long though
													l_CurTime=CEMSSystemClock::GetTime();
													if (l_StartHomeTime.SecondsDifferent(l_CurTime)*1000.0>(double)m_HomeTime)
													{
														EMS_OUTPUTDEBUGMSG(0,"Homing Sequence Failed\r");
														#ifdef _DEBUG_USEDEBUGWINDOW
															g_theDebugWindow.OutputMsg("Homing Failed");
														#endif
														switch (l_CurrentAttemptNumber)
														{
														case 0:
														case 1:
															// Log a message recording the failure of the home
															// and retry to home
															_stprintf( szMsg, TEXT("%d"), (int)l_CurrentAttemptNumber );

															_LogInfoMsg(EMS_ANT_HOMING_TIMEOUT_RETRY, szMsg, lstrlen( szMsg ) + 1 );
															l_CurrentAttemptNumber++;
															l_bHardwareErrorDetected=FALSE;
															m_pIAntenna->Home( FALSE );
															l_StartHomeTime=CEMSSystemClock::GetTime();
															break;

														case 2:
															// log an error message recording the failure of home and
															// exit the homing procedure in a failure state
															_LogWarningMsg(EMS_ANT_HOMING_TIMEOUT );
															l_bHardwareErrorDetected=TRUE;
															ReportError(ANTTRKR_ERR_HARDWARE,NULL);
															break;
														}
													}
												}
											} while ( ((l_AntennaDeviceStatus&ANTDEVSTATUS_ISHOME)==0) &&
												  	(l_bHardwareErrorDetected==FALSE));

                                            // clear homing state bit
					                        if( m_pIAntInfo != NULL )
					                        {
						                        if( LockStatus( 500 ) != FALSE )
						                        {
							                        m_pIAntInfo->uAntennaStatus &= ~0x10;
							                        UnlockStatus();
						                        }
					                        }

											#ifdef _DEBUG_USEDEBUGWINDOW
												g_theDebugWindow.OutputMsg("Homing Done");
											#endif
											if( !l_bHardwareErrorDetected )
											{
												char szInfo[256];
												EMSAZEL azel;
												EMSTIME AZT, ELT;
												m_pIAntenna->GetPosition( &azel, &AZT, &ELT );
												sprintf( szInfo, "%.2lf %.2lf", azel.degAzimuth, azel.degElevation );
												_LogInfoMsg( EMS_ANT_STATUS, szInfo, lstrlen( szInfo ) + 1 );
												m_pIAntenna->ResetCounter();
											}

											EMS_OUTPUTDEBUGMSG(0,"Home Completed\r");
										}
										EMS_OUTPUTDEBUGMSG(0,"End Homing Sequence Code\r");



										// at this point we should now have a valid path that can be followed
										// however, now need to draw in motion to the starting point of the
										// track (from home usually)
										// assume HOME is completed, antenna is ok. 
										// Don't assume position of antenna to be any given value
										if (l_bHardwareErrorDetected==FALSE)
										{
											CEMSTime	l_TimeAtInterval;
											long		l_EndInitMoveNdx_Elevation;
											long		l_EndInitMoveNdx_Azimuth;
											CEMSTime	l_ProposedTrackStartTime;
											CEMSTime	l_EarliestMoveStartTime;	// earliest time that the move can start - discretised to be in an integer interval slot
											EMSAZEL		*l_pTempAzElArray;
											long		l_NumExtraIntervals;
											EMSTIME		l_EMSTimeTemp[2];

											m_pIAntenna->GetPosition(&l_CurrentPosition,&l_EMSTimeTemp[0],&(l_EMSTimeTemp[1]));

											l_ProposedTrackStartTime=l_RawTrack.m_StartTime;
											l_CurTime=CEMSSystemClock::GetTime();

											#ifdef _DEBUG_DEVICENOTWORKING
												// assume current position is at the home position
												l_CurrentPosition=m_HomeLocation;
												#ifdef _DEBUG_RANDOMSTARTPOS
													l_CurrentPosition.degAzimuth=m_MinTravel.degAzimuth+((double)rand())*(m_MaxTravel.degAzimuth-m_MinTravel.degAzimuth)/((double)RAND_MAX);
													l_CurrentPosition.degElevation=m_MinTravel.degElevation+((double)rand())*(m_MaxTravel.degElevation-m_MinTravel.degElevation)/((double)RAND_MAX);
												#endif
											#endif

											// check to see if we need to chop off the beginning of the list at all 
											// if it has already passed
											if (l_CurTime.SecondsDifferent(l_ProposedTrackStartTime)<0.0)
											{

												// proposed start is in the past - chop off the beginning of the track
												ReportError(0,NULL); // missing start of the track

												l_NumExtraIntervals=(long)ceil(l_ProposedTrackStartTime.SecondsDifferent(l_CurTime)/((double)l_RawTrack.m_IntervalSize));

												l_ProposedTrack_NumIntervals-=l_NumExtraIntervals;
												if (l_ProposedTrack_NumIntervals>0)
												{
													l_ProposedTrackStartTime.AddSeconds((float) ( ((double)(l_NumExtraIntervals*l_RawTrack.m_IntervalSize))/1000.0 ) );
													l_pTempAzElArray=l_ProposedTrack;
													l_ProposedTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals+1));
													memcpy(l_ProposedTrack,l_pTempAzElArray+l_NumExtraIntervals,sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals));
													free(l_pTempAzElArray);
												};
											};

											m_exception.SetMark( __LINE__, __FILE__ );

											if (l_ProposedTrack_NumIntervals>0)
											{
												long	l_MoveIntervalCount; // number of intervals required to complete the move
												long	l_FastMoveIntervalCount;
												long	l_SlowMoveIntervalCount;
												double	l_MoveIntervalSpeed; // sign and maginitude of the speed to use

												// identify the earliest time that a move can start using
												// integral time intervals from the proposed track start time
												l_EarliestMoveStartTime=l_ProposedTrackStartTime;
												l_EarliestMoveStartTime.AddSeconds((float) (-1.0*floor(l_CurTime.SecondsDifferent(l_ProposedTrackStartTime)*1000.0/((double)l_RawTrack.m_IntervalSize))*((double)l_RawTrack.m_IntervalSize)/1000.0));

												l_EndInitMoveNdx_Elevation=-1;
												for (l_Ndx=0;l_Ndx<l_ProposedTrack_NumIntervals;l_Ndx++)
												{
													l_TimeAtInterval=l_ProposedTrackStartTime;
													l_TimeAtInterval.AddSeconds((float) ((double)(l_RawTrack.m_IntervalSize)/1000.0)*l_Ndx);
												
													if ( fabs(l_ProposedTrack[l_Ndx].degElevation-l_CurrentPosition.degElevation)/
												 		(l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval))<=m_MaxSpeed.degElevation)
													{
														// this is the interval to end the move to the first position
														// create the new path - extending the track if necessary
														l_EndInitMoveNdx_Elevation=l_Ndx;
														l_FastMoveIntervalCount=(long)ceil(fabs(l_ProposedTrack[l_Ndx].degElevation-l_CurrentPosition.degElevation)/
																		 		(m_MaxSpeed.degElevation*(((double)l_RawTrack.m_IntervalSize)/1000.0)) );
														if (l_Ndx>0)
														{
															l_MoveIntervalCount=l_FastMoveIntervalCount;
															l_MoveIntervalSpeed=m_MaxSpeed.degElevation;
														} else {
															l_SlowMoveIntervalCount=(long)ceil(fabs(l_ProposedTrack[l_Ndx].degElevation-l_CurrentPosition.degElevation)/
																			 		(m_MaxSpeed.degElevation*m_CruiseSpeedFactor*(((double)l_RawTrack.m_IntervalSize)/1000.0)) );
															if ( ((double)l_SlowMoveIntervalCount*(double)l_RawTrack.m_IntervalSize)/1000.0>l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval))
															{
																// can't do the minimum speed
																l_MoveIntervalCount=(long)(l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval)/
																				  		(((double)l_RawTrack.m_IntervalSize)/1000.0));
																l_MoveIntervalSpeed=fabs(l_ProposedTrack[l_EndInitMoveNdx_Elevation].degElevation-l_CurrentPosition.degElevation)/
																					((double)l_MoveIntervalCount)/
																					(((double)l_RawTrack.m_IntervalSize)/1000.0);
															} else {
																// can do the minimum speed
																l_MoveIntervalSpeed=m_MaxSpeed.degElevation*m_CruiseSpeedFactor;;
																l_MoveIntervalCount=l_SlowMoveIntervalCount;
															};
														};
														if (l_ProposedTrack[l_EndInitMoveNdx_Elevation].degElevation<l_CurrentPosition.degElevation)
														{
															l_MoveIntervalSpeed*=-1.0;
														};

														if (l_EndInitMoveNdx_Elevation-l_MoveIntervalCount<0)
														{
															// extend track backwards a few intervals to cover the move
															l_NumExtraIntervals=l_MoveIntervalCount-l_EndInitMoveNdx_Elevation;
															l_ProposedTrack_NumIntervals+=l_NumExtraIntervals;
															l_ProposedTrackStartTime.AddSeconds((float) ( -1.0*((double)(l_NumExtraIntervals*l_RawTrack.m_IntervalSize))/1000.0 ) );
															l_pTempAzElArray=l_ProposedTrack;
															l_ProposedTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals+1));
															memcpy(l_ProposedTrack+l_NumExtraIntervals,l_pTempAzElArray,sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals-l_NumExtraIntervals));
															free(l_pTempAzElArray);
															for (l_Ndx=0;l_Ndx<l_NumExtraIntervals;l_Ndx++)
															{
																l_ProposedTrack[l_Ndx]=l_ProposedTrack[l_NumExtraIntervals];
															};
															l_EndInitMoveNdx_Elevation+=l_NumExtraIntervals;
														};
														// insert the coordinates for the actual motion
														for (l_Ndx=l_EndInitMoveNdx_Elevation-l_MoveIntervalCount;l_Ndx>=0;l_Ndx--)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_CurrentPosition.degElevation;
														};
														for (l_Ndx=l_EndInitMoveNdx_Elevation-l_MoveIntervalCount+1;
													 		l_Ndx<l_EndInitMoveNdx_Elevation;
													 		l_Ndx++)
														{
															l_ProposedTrack[l_Ndx].degElevation=l_ProposedTrack[l_Ndx-1].degElevation+
																		   		l_MoveIntervalSpeed*((double)l_RawTrack.m_IntervalSize)/1000.0;
														};
														break;
													};
												};
												if (l_EndInitMoveNdx_Elevation!=-1)
												{
													l_EndInitMoveNdx_Azimuth=-1;
													for (l_Ndx=0;l_Ndx<l_ProposedTrack_NumIntervals;l_Ndx++)
													{
														l_TimeAtInterval=l_ProposedTrackStartTime;
														l_TimeAtInterval.AddSeconds((float) ((double)(l_RawTrack.m_IntervalSize)/1000.0)*l_Ndx);
													
														if ( fabs(l_ProposedTrack[l_Ndx].degAzimuth-l_CurrentPosition.degAzimuth)/
													 		(l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval))<=m_MaxSpeed.degAzimuth)
														{
															// this is the interval to end the move to the first position
															// create the new path - extending the track if necessary
															l_EndInitMoveNdx_Azimuth=l_Ndx;
															l_FastMoveIntervalCount=(long)ceil(fabs(l_ProposedTrack[l_Ndx].degAzimuth-l_CurrentPosition.degAzimuth)/
																			 		(m_MaxSpeed.degAzimuth*(((double)l_RawTrack.m_IntervalSize)/1000.0)) );
															if (l_Ndx>0)
															{
																l_MoveIntervalCount=l_FastMoveIntervalCount;
																l_MoveIntervalSpeed=m_MaxSpeed.degAzimuth;
															} else {
																l_SlowMoveIntervalCount=(long)ceil(fabs(l_ProposedTrack[l_Ndx].degAzimuth-l_CurrentPosition.degAzimuth)/
																				 		(m_MaxSpeed.degAzimuth*m_CruiseSpeedFactor*(((double)l_RawTrack.m_IntervalSize)/1000.0)) );
																if ( ((double)l_SlowMoveIntervalCount*(double)l_RawTrack.m_IntervalSize)/1000.0>l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval))
																{
																	// can't do the minimum speed
																	l_MoveIntervalCount=(long)(l_EarliestMoveStartTime.SecondsDifferent(l_TimeAtInterval)/
																					  		(((double)l_RawTrack.m_IntervalSize)/1000.0));
																	l_MoveIntervalSpeed=fabs(l_ProposedTrack[l_EndInitMoveNdx_Azimuth].degAzimuth-l_CurrentPosition.degAzimuth)/
																						((double)l_MoveIntervalCount)/
																						(((double)l_RawTrack.m_IntervalSize)/1000.0);
																} else {
																	// can do the minimum speed
																	l_MoveIntervalSpeed=m_MaxSpeed.degAzimuth*m_CruiseSpeedFactor;;
																	l_MoveIntervalCount=l_SlowMoveIntervalCount;
																};
															};
															if (l_ProposedTrack[l_EndInitMoveNdx_Azimuth].degAzimuth<l_CurrentPosition.degAzimuth)
															{
																l_MoveIntervalSpeed*=-1.0;
															};
															if (l_EndInitMoveNdx_Azimuth-l_MoveIntervalCount<0)
															{
																// extend track backwards a few intervals to cover the move
																l_NumExtraIntervals=l_MoveIntervalCount-l_EndInitMoveNdx_Azimuth;
																l_ProposedTrack_NumIntervals+=l_NumExtraIntervals;
																l_ProposedTrackStartTime.AddSeconds((float) ( -1.0*((double)(l_NumExtraIntervals*l_RawTrack.m_IntervalSize))/1000.0 ) );
																l_pTempAzElArray=l_ProposedTrack;
																l_ProposedTrack=(EMSAZEL *)malloc(sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals+1));
																memcpy(l_ProposedTrack+l_NumExtraIntervals,l_pTempAzElArray,sizeof(EMSAZEL)*(l_ProposedTrack_NumIntervals-l_NumExtraIntervals));
																free(l_pTempAzElArray);
																for (l_Ndx=0;l_Ndx<l_NumExtraIntervals;l_Ndx++)
																{
																	l_ProposedTrack[l_Ndx]=l_ProposedTrack[l_NumExtraIntervals];
																};
																l_EndInitMoveNdx_Azimuth+=l_NumExtraIntervals;
															};
															// insert the coordinates for the actual motion
															for (l_Ndx=l_EndInitMoveNdx_Azimuth-l_MoveIntervalCount;l_Ndx>=0;l_Ndx--)
															{
																l_ProposedTrack[l_Ndx].degAzimuth=l_CurrentPosition.degAzimuth;
															};
															for (l_Ndx=l_EndInitMoveNdx_Azimuth-l_MoveIntervalCount+1;
														 		l_Ndx<l_EndInitMoveNdx_Azimuth;
														 		l_Ndx++)
															{
																l_ProposedTrack[l_Ndx].degAzimuth=l_ProposedTrack[l_Ndx-1].degAzimuth+
																			   		l_MoveIntervalSpeed*((double)l_RawTrack.m_IntervalSize)/1000.0;
															};
															break;
														};
													};

													m_exception.SetMark( __LINE__, __FILE__ );

													if (l_EndInitMoveNdx_Azimuth!=-1)
													{
														#ifdef _DEBUG_WRITEPROPOSEDTRACK 
														{
															// writeout to a file the proposed track - as it currently exists
															// also show error comparison here if needed
															FILE *l_pProposedFile; //=fopen("c:\\temp\\ProposedTrack.txt","a+c");
															char	l_szFileName[2024];
															CEMSTime	l_CurTime;
															EMSTIMEFIELDS	l_CurTimeEx;

															l_CurTime=CEMSSystemClock::GetTime();
															l_CurTime.GetTime(&l_CurTimeEx);
															sprintf(l_szFileName,"c:\\temp\\ProposedTrack_%02d_%02d_%04d__%02d_%02d_%02d___%d.txt",
																		 		l_CurTimeEx.nDay,
																		 		l_CurTimeEx.nMonth,
																		 		l_CurTimeEx.nYear,
																		 		l_CurTimeEx.nHour,
																		 		l_CurTimeEx.nMinute,
																		 		l_CurTimeEx.nSecond,
																		 		GetTickCount());
															l_pProposedFile=fopen(l_szFileName,"w+c");
															if (l_pProposedFile!=NULL)
															{
																char l_szData[1024];
																EMSAZEL	l_AzElError;
																BOOL	l_bIsOutOfBeam;
																long	l_RawStartNdx;
																EMSAZEL	l_CurSpeed;

																l_RawStartNdx=l_ProposedTrack_NumIntervals-l_RawTrack.m_IntervalCount;
																for (l_Ndx=0;l_Ndx<l_ProposedTrack_NumIntervals;l_Ndx++)
																{
																	if (l_Ndx>=l_RawStartNdx)
																	{
																		l_AzElError.degAzimuth=fabs(l_AdjRawRawTrack[l_Ndx-l_RawStartNdx].degAzimuth-l_ProposedTrack[l_Ndx].degAzimuth);
																		l_AzElError.degElevation=fabs(l_AdjRawRawTrack[l_Ndx-l_RawStartNdx].degElevation-l_ProposedTrack[l_Ndx].degElevation);
																		l_bIsOutOfBeam=(IsInBeam(l_AdjRawRawTrack[l_Ndx-l_RawStartNdx],l_ProposedTrack[l_Ndx])==FALSE)?TRUE:FALSE;
																	} else {
																		l_bIsOutOfBeam=FALSE;
																		l_AzElError.degAzimuth=0.0;
																		l_AzElError.degElevation=0.0;
																	};
																	if (l_Ndx<l_ProposedTrack_NumIntervals-1)
																	{
																		l_CurSpeed.degAzimuth=(l_ProposedTrack[l_Ndx+1].degAzimuth-l_ProposedTrack[l_Ndx].degAzimuth)/(((double)l_RawTrack.m_IntervalSize)/1000.0);
																		l_CurSpeed.degElevation=(l_ProposedTrack[l_Ndx+1].degElevation-l_ProposedTrack[l_Ndx].degElevation)/(((double)l_RawTrack.m_IntervalSize)/1000.0);
																	} else {
																		l_CurSpeed.degAzimuth=0.0;
																		l_CurSpeed.degElevation=0.0;
																	};
																	sprintf(l_szData,
																			"%.2f,%.2f , %.2f,%.2f , %.2f,%.2f, %.5f,%.5f ,%d%s\r",
																			l_ProposedTrack[l_Ndx].degAzimuth,
																			l_ProposedTrack[l_Ndx].degElevation,
																			// speed Az, Speed El
																			l_CurSpeed.degAzimuth,
																			l_CurSpeed.degElevation,
																			// X,Y
																			(90.0-l_ProposedTrack[l_Ndx].degElevation)*cos(l_ProposedTrack[l_Ndx].degAzimuth/180.0*acos(-1.0)),
																			(90.0-l_ProposedTrack[l_Ndx].degElevation)*sin(l_ProposedTrack[l_Ndx].degAzimuth/180.0*acos(-1.0)),
																			l_AzElError.degAzimuth,
																			l_AzElError.degElevation,
																			l_bIsOutOfBeam,
																			(l_Ndx==0)?",NewTrack":""
																			);
																	fwrite((void*)l_szData,strlen(l_szData),1,l_pProposedFile);
																};
																fclose(l_pProposedFile);
																l_pProposedFile=NULL;
															};
														};
														#endif

														// now execute the track it is all stored as propoosed in the l_ProposedTrack array
														// starting at time l_ProposedTrackStartTime
														// and continuing for l_ProposedTrack_NumIntervals;
														EMSAZEL		l_NextPassDesiredPosition;
														long		l_PrecedingIndex;
														EMSAZEL		l_NewSpeed;
														CEMSTime	l_NextPassTime;
														double		l_IntervalFraction;
														double		l_TimeIntoPass_seconds;
														EMSAZEL		l_SatellitePosition;
														BOOL		l_bHasBeenInBeamOnce;
														long		l_OutOfBeamCounter;	// number of times in a row that the satellite is out-of-beam

														#ifdef _DEBUG_DEVICENOTWORKING
															l_bHardwareErrorDetected=TRUE;
														#endif

		#ifdef _DEBUG_USEDEBUGWINDOW
														g_theDebugWindow.OutputMsg("Waiting for Execution start");
		#endif
														EMS_OUTPUTDEBUGMSG(0,"Waiting for track execution start\r");
														m_exception.SetMark( __LINE__, __FILE__ );

														// step 1. wait until l_CurTime is the start of the track
														l_CurTime=CEMSSystemClock::GetTime();
														while ((l_CurTime.SecondsDifferent(l_ProposedTrackStartTime)>0.0) &&
													   		(l_bHardwareErrorDetected==FALSE))
														{

															// check antenna device for fault
															l_SignalledEvent=WaitForMultipleObjects(3,l_hEvents,FALSE,(DWORD)min(l_CurTime.SecondsDifferent(l_ProposedTrackStartTime)*1000.0/2.0,1000.0));
															switch (l_SignalledEvent)
															{
															case WAIT_OBJECT_0:
																// exit command - just dump out ASAP svp
																l_bHardwareErrorDetected=TRUE;
																l_bExitThread=TRUE; /* revision 0.0.9 */
																break;
															case WAIT_OBJECT_0+2: // antenna state
																break;
															case WAIT_TIMEOUT: // just do the next round
																break;
															};

															// check status to make sure it isn't faulted
															m_pIAntenna->GetStatus(&l_AntennaDeviceStatus);
															if ((l_AntennaDeviceStatus&ANTDEVSTATUS_FAULTED)!=0) 
															{
																l_bHardwareErrorDetected=TRUE;
																ReportError(ANTTRKR_ERR_HARDWARE,NULL);
															};
															//Sleep((DWORD)min(l_CurTime.SecondsDifferent(l_ProposedTrackStartTime)*1000.0/2.0,1000.0));
															l_CurTime=CEMSSystemClock::GetTime();
														};
														EMS_OUTPUTDEBUGMSG(0,"Track execution start reached\r");

														if (l_bHardwareErrorDetected==FALSE)
														{
		#ifdef _DEBUG_USEDEBUGWINDOW
															g_theDebugWindow.OutputMsg("Waiting for Execution start");
		#endif												

															EMSAZEL		l_ReportedPosition;
															CEMSTime	l_ReportedPositionAzTime;
															CEMSTime	l_ReportedPositionElTime;
															CEMSTime	l_ReceivedRptPosTime;
															CEMSTime	l_PreSentMoveTime;
															CEMSTime	l_SentMoveTime;
															EMSAZEL		l_SentMoveVel;


															#ifdef _DEBUG_USEDEBUGWINDOW
																											
	//															EMSTIMEFIELDS	l_RepPosAzTimeEx;
	//															EMSTIMEFIELDS	l_RepPosElTimeEx;
																char		l_szDebugString[1024];
																CEMSTime	l_DebugStartTime;
																l_DebugStartTime=CEMSSystemClock::GetTime();
															#endif

															l_NextPassDesiredPosition=l_ProposedTrack[0];

															if (m_pIAntInfo!=NULL)
															{
																if (LockStatus(500)!=FALSE)
																{
																	m_pIAntInfo->uAntennaStatus|=EMSANTINFOFLAG_STATUS_TRACKING;
																	UnlockStatus();
																};
															};

															m_exception.SetMark( __LINE__, __FILE__ );
															// begin continual execution of the track
															l_bHasBeenInBeamOnce=FALSE;
															l_OutOfBeamCounter=0;
															l_SentMoveVel.degElevation=0.0;
															l_SentMoveVel.degAzimuth=0.0;
															do {

																m_exception.SetMark( __LINE__, __FILE__ );
																// retrieve current position
																m_pIAntenna->GetPosition(&l_ReportedPosition,&(l_EMSTimeTemp[0]),&(l_EMSTimeTemp[1]));
																l_CurTime=CEMSSystemClock::GetTime();
																l_ReportedPositionAzTime=l_EMSTimeTemp[0];
																l_ReportedPositionElTime=l_EMSTimeTemp[1];
																{
																	double	l_DeltaTime[2];

																	l_DeltaTime[0]=l_ReportedPositionAzTime.SecondsDifferent(l_CurTime);
																	l_DeltaTime[1]=l_ReportedPositionElTime.SecondsDifferent(l_CurTime);
																	l_CurrentPosition.degAzimuth=l_ReportedPosition.degAzimuth+l_SentMoveVel.degAzimuth*l_DeltaTime[0];
																	l_CurrentPosition.degElevation=l_ReportedPosition.degElevation+l_SentMoveVel.degElevation*l_DeltaTime[1];
																};

																/* revision 0.0.6 */
																// check to see if the last reported time from the indexers was too long
																// ago - in that case it is time to exit the loop
																if ((l_ReportedPositionAzTime.SecondsDifferent(l_CurTime)>l_MaxTimeSinceAxisPositionReport) ||
																	(l_ReportedPositionElTime.SecondsDifferent(l_CurTime)>l_MaxTimeSinceAxisPositionReport))
																{
																	EMS_OUTPUTDEBUGMSG(0,"Track execution - Time since last axis position report is too long\r");
																	LogError(EMS_ANT_ERROR,"Track execution aborted - Time since last axis position report is too long");
																	l_bHardwareErrorDetected=TRUE;
																	break;
																};

																// debugging beeps - don't use when doing time-sensitive stuff
																#ifdef _DEBUG
																	//Beep((long)(l_CurrentPosition.degAzimuth+270.0*2.0)+400,50);
																	//Beep((long)(l_CurrentPosition.degElevation*4.0)+400,50);
																#endif
																#ifdef _DEBUG_IGNORE_ELEVATION
																	l_CurrentPosition.degElevation=l_NextPassDesiredPosition.degElevation;
																#endif

																m_exception.SetMark( __LINE__, __FILE__ );
																// save information in status
																if (m_pIAntInfo!=NULL)
																{
																	if (LockStatus(10)!=FALSE) /* revision 0.0.3 */
																	{
																		m_pIAntInfo->azelDesired=l_NextPassDesiredPosition;
																		m_pIAntInfo->azelActual=l_CurrentPosition;
																	//	m_pIAntInfo->time=l_CurTime;
																		UnlockStatus();
																	};
																};

																m_exception.SetMark( __LINE__, __FILE__ );
																// calculate error in position from the satellite track
																// l_AdjRawRawTrack  contains the satellite track values
																// this array doesn't trim upper elevations at all
																l_TimeIntoPass_seconds=CEMSTime(l_RawTrack.m_StartTime).SecondsDifferent(l_CurTime);
																l_PrecedingIndex=(long)floor(l_TimeIntoPass_seconds*1000.0/((double)(l_RawTrack.m_IntervalSize)));
																if ((l_PrecedingIndex>=0) && 
																	(l_PrecedingIndex<l_RawTrack.m_IntervalCount-1))
																{
																	l_IntervalFraction=fmod(l_TimeIntoPass_seconds*1000.0,(double)(l_RawTrack.m_IntervalSize))/(double)(l_RawTrack.m_IntervalSize);
																	l_SatellitePosition.degElevation=l_AdjRawRawTrack[l_PrecedingIndex].degElevation+
																								l_IntervalFraction*(l_AdjRawRawTrack[l_PrecedingIndex+1].degElevation-
																													l_AdjRawRawTrack[l_PrecedingIndex].degElevation);
																	l_SatellitePosition.degAzimuth=l_AdjRawRawTrack[l_PrecedingIndex].degAzimuth+
																								l_IntervalFraction*(l_AdjRawRawTrack[l_PrecedingIndex+1].degAzimuth-
																													l_AdjRawRawTrack[l_PrecedingIndex].degAzimuth);


																	if( IsInBeam( l_SatellitePosition, l_CurrentPosition ) == FALSE )
																	{
																		l_OutOfBeamCounter++;
																		if( (l_bHasBeenInBeamOnce == TRUE) &&
																			(l_OutOfBeamCounter * m_DevicePollInterval_ms >= m_MaxOutOfBeamDuration_ms) )
																		{
																			ReportError(ANTTRKR_ERR_OUTOFBEAM,NULL); // Out of beam for too many times in a row / too long
																			break; // exit
																		}
																	}
                                                                    else
                                                                    {
																		l_OutOfBeamCounter = 0;
																		l_bHasBeenInBeamOnce = TRUE;
																	}
																	if( m_pIAntInfo != NULL )
																	{
																		if( LockStatus(10) != FALSE )
																		{
																			if( l_OutOfBeamCounter == 0 )
																			{
																				m_pIAntInfo->uAntennaStatus |= EMSANTINFOFLAG_STATUS_INBEAM;
																			}
                                                                            else
                                                                            {
																				m_pIAntInfo->uAntennaStatus &= ~EMSANTINFOFLAG_STATUS_INBEAM;
																			}
																			UnlockStatus();
																		}
																	}
																}
                                                                else
                                                                {
																	l_SatellitePosition = l_AdjRawRawTrack[0];
																}
																m_exception.SetMark( __LINE__, __FILE__ );


																// calculate where I want to be for the next poll round
																l_NextPassTime=l_CurTime;
																l_NextPassTime.AddSeconds((float) (((double)(/*l_RawTrack.m_IntervalSize*/m_DevicePollInterval_ms))/1000.0));
																l_TimeIntoPass_seconds=l_ProposedTrackStartTime.SecondsDifferent(l_NextPassTime);
																l_PrecedingIndex=(long)floor(l_TimeIntoPass_seconds*1000.0/((double)(l_RawTrack.m_IntervalSize)));
																if (l_PrecedingIndex>=(l_ProposedTrack_NumIntervals-1))
																{
																	// last point
																	l_NextPassDesiredPosition=l_ProposedTrack[l_ProposedTrack_NumIntervals-1];
																} else {
																	l_IntervalFraction=fmod(l_TimeIntoPass_seconds*1000.0,(double)(l_RawTrack.m_IntervalSize))/(double)(l_RawTrack.m_IntervalSize);
																	l_NextPassDesiredPosition.degElevation=l_ProposedTrack[l_PrecedingIndex].degElevation+
																								l_IntervalFraction*(l_ProposedTrack[l_PrecedingIndex+1].degElevation-l_ProposedTrack[l_PrecedingIndex].degElevation);
																	l_NextPassDesiredPosition.degAzimuth=l_ProposedTrack[l_PrecedingIndex].degAzimuth+
																								l_IntervalFraction*(l_ProposedTrack[l_PrecedingIndex+1].degAzimuth-l_ProposedTrack[l_PrecedingIndex].degAzimuth);
																};
																m_exception.SetMark( __LINE__, __FILE__ );

																// calculate what speed I need to get there for the next poll round
																// assume infinite acceleration
																l_NewSpeed.degElevation=(l_NextPassDesiredPosition.degElevation-l_CurrentPosition.degElevation)/
																						(((double)m_DevicePollInterval_ms)/1000.0);
																l_NewSpeed.degAzimuth=(l_NextPassDesiredPosition.degAzimuth-l_CurrentPosition.degAzimuth)/
																						(((double)m_DevicePollInterval_ms)/1000.0);

																// limit speeds
																l_NewSpeed.degElevation=max(min(l_NewSpeed.degElevation,m_MaxSpeed.degElevation),-1.0*m_MaxSpeed.degElevation);
																l_NewSpeed.degAzimuth=max(min(l_NewSpeed.degAzimuth,m_MaxSpeed.degAzimuth),-1.0*m_MaxSpeed.degAzimuth);

																m_exception.SetMark( __LINE__, __FILE__ );
																// tell it to go that fast
																l_PreSentMoveTime=CEMSSystemClock::GetTime();
																m_pIAntenna->MoveAtRate(l_NewSpeed);
																m_exception.SetMark( __LINE__, __FILE__ );

																l_SentMoveTime=CEMSSystemClock::GetTime();
																l_SentMoveVel=l_NewSpeed;
																// send all recorded infomration to debug window
																#ifdef _DEBUG_USEDEBUGWINDOW
																	//sprintf(l_szDebugString,"%07.3f@%07.3f,%07.3f@%07.3f[%07.3f] Vel %06.3f%06.3f@%07.3f",
																	sprintf(l_szDebugString,"%07.3f,%07.3f,%07.3f,%07.3f,%07.3f,%06.3f,%06.3f,%07.3f,%07.3f",
																				   		l_ReportedPosition.degAzimuth,
																				   		l_DebugStartTime.SecondsDifferent(l_ReportedPositionAzTime),
																				   		l_ReportedPosition.degElevation,
																				   		l_DebugStartTime.SecondsDifferent(l_ReportedPositionElTime),
																				   		l_DebugStartTime.SecondsDifferent(l_CurTime),
																				   		l_SentMoveVel.degAzimuth,
																				   		l_SentMoveVel.degElevation,
																				   		l_DebugStartTime.SecondsDifferent(l_PreSentMoveTime),
																				   		l_DebugStartTime.SecondsDifferent(l_SentMoveTime)
																				   		);
																	OutputDebugString(l_szDebugString);
																	OutputDebugString("\n");

																	#ifdef _DEBUG_USEDEBUGWINDOW
																	g_theDebugWindow.OutputMsg(l_szDebugString);
																	#endif
																#endif
	//															#ifdef _DEBUG_WRITEACTUALTRACK
	//																l_ReportedPositionAzTime.GetTime(&l_RepPosAzTimeEx);
	//																l_ReportedPositionElTime.GetTime(&l_RepPosElTimeEx);
	//																sprintf(l_szDebugString,"%I64d,%07.3f,%07.3f,%d:%d:%d,%I64d,%07.3f,%07.3f,%d:%d:%d,%07.3f,%06.3f,%06.3f,%07.3f,%07.3f\r",
	//																				   	l_ReportedPositionAzTime,	
	//																				   	l_DebugStartTime.SecondsDifferent(l_ReportedPositionAzTime),
	//																				   	l_ReportedPosition.degAzimuth,
	//																				   	l_RepPosAzTimeEx.nHour,
	//																				   	l_RepPosAzTimeEx.nMinute,
	//																				   	l_RepPosAzTimeEx.nSecond,
	//																				   	l_ReportedPositionElTime,
	//																				   	l_DebugStartTime.SecondsDifferent(l_ReportedPositionElTime),
	//																				   	l_ReportedPosition.degElevation,
	//																				   	l_RepPosElTimeEx.nHour,
	//																				   	l_RepPosElTimeEx.nMinute,
	//																				   	l_RepPosElTimeEx.nSecond,
	//																				   	l_DebugStartTime.SecondsDifferent(l_CurTime),
	//																				   	l_SentMoveVel.degAzimuth,
	//																				   	l_SentMoveVel.degElevation,
	//																				   	l_DebugStartTime.SecondsDifferent(l_PreSentMoveTime),
	//																				   	l_DebugStartTime.SecondsDifferent(l_SentMoveTime)
	//																				   	);
	//																fwrite((void *)l_szDebugString,strlen(l_szDebugString),1,g_pAntActualTrackFile);
	//															#endif

																m_exception.SetMark( __LINE__, __FILE__ );
																// check antenna device for fault
																l_SignalledEvent=WaitForMultipleObjects(3,l_hEvents,FALSE,m_DevicePollInterval_ms);
																switch (l_SignalledEvent)
																{
																case WAIT_OBJECT_0:
																	// exit command - just dump out ASAP svp
																	l_bHardwareErrorDetected=TRUE;
																	l_bExitThread=TRUE; /* revision 0.0.9 */
																	break;
																case WAIT_OBJECT_0+2: // antenna state
																	break;
																case WAIT_TIMEOUT: // just do the next round
																	break;
																};
																m_exception.SetMark( __LINE__, __FILE__ );

                                                                // get the status
																m_pIAntenna->GetStatus(&l_AntennaDeviceStatus);

																// check status to make sure it isn't faulted
																if ((l_AntennaDeviceStatus&ANTDEVSTATUS_FAULTED)!=0) 
																{
																	l_bHardwareErrorDetected = TRUE;
																	ReportError(ANTTRKR_ERR_HARDWARE,NULL);
    															}

                                                                // log the status information
                                                                if( m_pIAntInfo != NULL )
                                                                {
	                                                                if( LockStatus(50) != FALSE )
	                                                                {
		                                                                m_pIAntInfo->uAntennaStatus &= 0xFF;  // clear high 8 bits
                                                                        m_pIAntInfo->uAntennaStatus |= (l_AntennaDeviceStatus & 0xF) << 8;
                                                                        m_pIAntInfo->uAntennaStatus |= (l_AntennaDeviceStatus & 0xF00) << 4;
		                                                                UnlockStatus();
	                                                                }
                                                                }


																m_exception.SetMark( __LINE__, __FILE__ );

																//Sleep(m_DevicePollInterval_ms);
														
															} while ( (l_PrecedingIndex<(l_ProposedTrack_NumIntervals-1)) &&
															  		(l_bHardwareErrorDetected==FALSE));

                                                            if( m_pIAntInfo != NULL )
															{
																if( LockStatus(50) != FALSE )
																{
																	m_pIAntInfo->uAntennaStatus &= ~EMSANTINFOFLAG_STATUS_TRACKING;
																	UnlockStatus();
																}
															}
														};

														EMS_OUTPUTDEBUGMSG(0,"Track execution Finished\r");

														// motion is done - stop the antenna from moving any more
														l_NewSpeed.degAzimuth=0.0;
														l_NewSpeed.degElevation=0.0;
														m_pIAntenna->MoveAtRate(l_NewSpeed);

														EMS_OUTPUTDEBUGMSG(0,"Antenna stopped after track\r");

														if (l_bHardwareErrorDetected==FALSE)
														{
															l_bTrackPassWasSuccessful=TRUE;
														};
													};

												};
											} else {
												ReportError(ANTTRKR_ERR_OTHER,NULL); // nothing to track - been chopped too much due to time constraints
											};
										};

										// cleanup
										free(l_ProposedSpeeds);
										l_ProposedSpeeds=NULL;
									} else {
										// could not allocate memory for proposed track speeds
										ReportError(ANTTRKR_ERR_MEMORYFAILURE,NULL);
										LogError(EMS_ANT_ERROR,"Could not allocate memory for proposed track speeds");
									};

									// cleanup
									free(l_ProposedTrack);
									l_ProposedTrack=NULL;
								} else {
									// could not allocate memory for proposed track
									ReportError(ANTTRKR_ERR_MEMORYFAILURE,NULL);
									LogError(EMS_ANT_ERROR,"Could not allocate memory for proposed track");
								};

							} else {
								// cannot reconcile azimuth values to track within the antenna parameters
								ReportError(ANTTRKR_ERR_OTHER,NULL);
								LogError(EMS_ANT_ERROR,"cannot reconcile azimuth values to track within the antenna parameters");
							};
							free(l_AdjRawRawTrack);
							l_AdjRawRawTrack=NULL;
						} else {
							ReportError(ANTTRKR_ERR_MEMORYFAILURE,NULL); // Cannot Allocate Memory for l_AdjRawRawTrack
							LogError(EMS_ANT_ERROR,"Cannot Allocate Memory for l_AdjRawRawTrack");
						};

						// cleanup
						free(l_AdjRawTrack);
						l_AdjRawTrack=NULL;
					} else {
						ReportError(ANTTRKR_ERR_MEMORYFAILURE,NULL); // Cannot Allocate Memory
						LogError(EMS_ANT_ERROR,"Cannot Allocate Memory");
					};
					free(l_RawTrack.m_pCoords);
					l_RawTrack.m_pCoords=NULL;
					l_RawTrack.m_IntervalCount=-1;

					#ifdef _DEBUG
						g_bAntennaTrackerIsDoneTrack=TRUE;
					#endif

					// signal event if appropriate to say that track has been completed
					/* revision 0.0.4 */
					if (m_hEvent_Notification!=NULL)
					{
						PulseEvent(m_hEvent_Notification);
					};

					if (l_bHardwareErrorDetected==TRUE)
					{
						if (m_pIAntInfo!=NULL)
						{
							if (LockStatus(5000)!=FALSE)
							{
								m_pIAntInfo->uAntennaStatus|=EMSANTINFOFLAG_STATUS_FAULT;
								UnlockStatus();
							};
						};
					};
					if (m_pIAntInfo!=NULL)
					{
						if (LockStatus(5000)!=FALSE)
						{
							m_pIAntInfo->uAntennaStatus&=(!EMSANTINFOFLAG_STATUS_CALCTRACK);
							UnlockStatus();
						};
					};

					if (l_bTrackPassWasSuccessful==FALSE)
					{
						_stprintf( szMsg, TEXT("%d"), (int)l_TrackPassAttempt );

						switch(l_TrackPassAttempt)
						{
						case 0:
							_LogInfoMsg( EMS_ANT_PASS_RETRY, szMsg, lstrlen( szMsg ) + 1 );
                    Sleep(1000);
							break;

						case 1:
							_LogWarningMsg( EMS_ANT_PASS_RETRY, szMsg, lstrlen( szMsg ) + 1 );
                    Sleep(1000);
							break;

						case 2:
							_LogAlarmMsg( EMS_ANT_PASS_ERROR, szMsg, lstrlen( szMsg ) + 1 );
							break;
						};
						if (l_TrackPassAttempt<3)
						{
							l_RawTrack=l_BackupRawTrack;
							l_TrackPassAttempt++;
						};
					};
				} while ((l_bTrackPassWasSuccessful==FALSE) && (l_TrackPassAttempt<3));
				if (l_BackupRawTrack.m_pCoords!=NULL)
				{
					free(l_BackupRawTrack.m_pCoords);
					l_BackupRawTrack.m_pCoords=NULL;
					l_BackupRawTrack.m_IntervalCount=-1;
				};
				break;
			};
		}
		catch ( ... )
		{
			_LogException( &m_exception );
		}
	};		// while 

	EMS_OUTPUTDEBUGMSG(0,"Thread Exiting\r");

	if (l_hDeviceStateEvent!=NULL)
	{
		m_pIAntenna->SetHandle(0, NULL);
		CloseHandle(l_hDeviceStateEvent);
		l_hDeviceStateEvent=NULL;	
	};

	ResetEvent(m_hEventThreadStopRequest);
	SetEvent(m_hEventThreadStopped);

	EMS_OUTPUTDEBUGMSG(0,"Thread done\r");

	return 0;
}

BOOL AntennaTracker::LockBuffer(BOOL bWait)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::LockBuffer
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		bWait		: TRUE if the caller is willing to wait for the buffer to become available	
			
Description:	
	locks the mutex to allow access to the m_NextTrack by the caller
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	BOOL	l_bResult;
	long	l_Result;

	
	l_Result=WaitForSingleObject(m_hMutex_Buffer, (bWait==TRUE) ? /*INFINITE*/ 10000 : 1);
	if ((l_Result==WAIT_TIMEOUT) && (bWait==TRUE))
	{
		EMS_OUTPUTDEBUGMSG(0,"AntennaTracker::Lock Buffer - Potential Infinite Timeout encountered \r");
	};
	l_bResult=( l_Result == WAIT_OBJECT_0);

	return l_bResult;
}

void AntennaTracker::UnlockBuffer()
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::UnlockBuffer
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:		
			
Description:	
	unlocks the mutex to allow others to access the m_NextTrack 
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	ReleaseMutex( m_hMutex_Buffer );
}


void AntennaTracker::ReportError(long ErrorID, void *pData)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::ReportError
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 22, 2001
ARGUMENTS:			ErrorID		: ID Code for the error
					pData		: pointer to error specific data (if required)
			
Description:	
	Reports an error to the system somehow
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	if (m_pIAntInfo!=NULL)
	{
		switch (ErrorID)
		{
		case ANTTRKR_ERR_MEMORYFAILURE:
		case ANTTRKR_ERR_OTHER:
			//m_pIAntInfo->uAntennaStatus|=ErrorID;
			break;
		case ANTTRKR_ERR_OUTOFBEAM:
			//m_pIAntInfo->uAntennaStatus|=ErrorID;
			break;
		case ANTTRKR_ERR_HARDWARE:
			//m_pIAntInfo->uAntennaStatus|=ErrorID;
			break;
		};

		#ifdef _DEBUG_WRITELOGFILE
			char l_szErrMsg[200];
			char *l_szText="";
			if (pData!=NULL)
			{
				l_szText=(char *)pData;
			};

			switch (ErrorID)
			{
			case ANTTRKR_ERR_MEMORYFAILURE:
				sprintf(l_szErrMsg,"Memory Failure:%s\n",l_szText);
				break;
			case ANTTRKR_ERR_OTHER:
				sprintf(l_szErrMsg,"Other error\n");
				break;
			case ANTTRKR_ERR_OUTOFBEAM:
				sprintf(l_szErrMsg,"Out Of Beam error\n");
				break;
			case ANTTRKR_ERR_HARDWARE:
				sprintf(l_szErrMsg,"Hardware error\n");
				break;
			default:
				sprintf(l_szErrMsg,"Unknown error\n");
				break;
			};
			fwrite(l_szErrMsg,strlen(l_szErrMsg),1,g_pAntTrkrLogFile);
		#endif
	};
}

void AntennaTracker::LogError(DWORD dwErrorID, char *szText)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::LogError
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Feb 6th, 2002
ARGUMENTS:			dwErrorID	: Message ID (.MC file ID?)
					szText		: text message to be included
			
Description:	
	Sends the given message to the logger function
	generally assume that it is using the Message Compilier and
	working as if it is going into the windows system event log
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	if ( m_pLogger!=NULL )
	{
		m_pLogger->ReportLogEvent( EMSLogMsgAlarm, dwErrorID, (TCHAR *const)szText, strlen(szText)+1 );
	}
}

BOOL AntennaTracker::IsInBeam(EMSAZEL &Satellite, EMSAZEL &Antenna)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::IsInBeam
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Nov 23, 2001
ARGUMENTS:			Satellite	: Position of the satellite
					Antenna		: Actual position of the antenna
			
Description:	
		Returns if the satellite at the given position is within the beam of 
		the given antenna position
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	BOOL	l_bResult;
	EMSDEGREES	l_DeltaElevation;
	EMSDEGREES	l_DeltaAzimuth;
	EMSDEGREES	l_AvgElevation;
	EMSDEGREES	l_Distance;

	l_bResult=FALSE;

	l_DeltaElevation=fabs(Satellite.degElevation-Antenna.degElevation);
	#ifdef _DEBUG_IGNORE_ELEVATION
		l_DeltaElevation=0.0;
	#endif
	if (l_DeltaElevation<=m_BeamWidth/2.0)
	{
		l_AvgElevation=(Satellite.degElevation+Antenna.degElevation)/2.0;
		l_DeltaAzimuth=fabs(Satellite.degAzimuth-Antenna.degAzimuth);
		l_Distance=sqrt((l_DeltaElevation*l_DeltaElevation)+
					    (l_DeltaAzimuth*l_DeltaAzimuth)*pow(cos(l_AvgElevation/180.0*acos(-1)),2.0));
		if (l_Distance<=m_BeamWidth/2.0)
		{
			l_bResult=TRUE;
		};
	};

	return l_bResult;
}


BOOL AntennaTracker::LockStatus(long Timeout)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::LockStatus
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Dec 10, 2001
ARGUMENTS:			Timeout	: how long to wait - in ms
			
Description:	
		Locks the mutex for the antenna status
		this is so that an outside program can read/alter the status
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	BOOL	l_bResult;

	l_bResult=FALSE;
	if (m_hMutex_Status!=NULL)
	{
		l_bResult=(WaitForSingleObject(m_hMutex_Status, Timeout) == WAIT_OBJECT_0);
		
	};

	return l_bResult;
}

BOOL AntennaTracker::UnlockStatus()
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::UnlockStatus
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Dec 10, 2001
ARGUMENTS:			
			
Description:	
	Unlock function to complement LockStatus
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	BOOL	l_bResult;

	l_bResult=FALSE;
	if (m_hMutex_Status!=NULL)
	{
		ReleaseMutex(m_hMutex_Status);
		l_bResult=TRUE;
	};

	return l_bResult;

}

void AntennaTracker::SetNotifyEvent(HANDLE hNotifyEvent)
//*****************************************************************************
/* Copyright © 2001 EMS Technologies Canada, Ltd.  All Rights Reserved.
APPLICATION NAME:			LeoLut600
OBJECT/FUNCTION NAME:		AntennaTracker::SetNotifyEvent
INHERITS FROM:				
CREATED BY:					Morgan Fraser
CREATION DATE:				Jan 24th, 2002
ARGUMENTS:			
			
Description:	
	Sets the handle for the event object used to notify any listeners
	that a track has been completed
		
REVISION HISTORY:	

	NOTE: 	PLACE COMMENTS IN CODE, INDICATING REVISIONS.  REMOVE BLOCKS
				OF UNUSED CODE AFTER THEY ARE MORE THAN 1 RELEASE OLD.
		
	VERSION	DDMMMYYYY	WHO	NOTE
*/
{
	m_hEvent_Notification=hNotifyEvent;
}

EMS_RESULT AntennaTracker::MoveToPosition( EMSAZEL position, EMSAZEL rate )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_pIAntenna )
		hr = m_pIAntenna->MoveToPosition( position, rate );
	else
		hr = EMS_NOT_INITIALIZED;

	return hr;
}

EMS_RESULT AntennaTracker::ResetAndHome( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_pIAntenna )
		hr = m_pIAntenna->ResetAndHome( );
	else
		hr = EMS_NOT_INITIALIZED;

	return hr;
}
void AntennaTracker::_LogMsg( EMSLOGMSGTYPE msgType, DWORD dwMsg, 
									LPCTSTR lpcszStrings, ULONG ulStrLen )
{
	if ( m_pLogger )
	{
		m_pLogger->ReportLogEvent( msgType, dwMsg, (TCHAR *const)lpcszStrings, ulStrLen );
	}
}

void AntennaTracker::_LogAlarmMsg( DWORD dwMsg, EMS_RESULT errResult )
{
	TCHAR szError[ 32 ];

	sprintf( szError, "0x%X", errResult );

	_LogAlarmMsg( dwMsg, szError, lstrlen( szError ) + 1 );
}

void AntennaTracker::_LogException( CEMSException *lpExcept )
{
	TCHAR szText[ 256 ], szLine[32], szFile[256];
	ULONG ulTextLen = 0;
	
	if ( lpExcept )
	{
		sprintf( szLine, TEXT("%d"), lpExcept->GetLineNumber() );

		if ( lpExcept->GetFileName() )
			sprintf( szText, TEXT("%s"), lpExcept->GetFileName() );	
		else
			_tcscpy( szText, TEXT("?") );
	}
	else
	{
		_tcscpy( szLine, TEXT("?") );
		_tcscpy( szText, TEXT("?") );
	}

	_splitpath( szText, 0, 0, szFile , 0 );
	
	_tcscpy( szText, szLine );

	ulTextLen = _tcslen( szText );	

	_tcscpy( &szText[ ulTextLen ], szFile );

	ulTextLen += _tcslen( &szText[ ulTextLen ] );	

	_LogAlarmMsg( EMS_LOG_EXCEPTION, szText, ulTextLen );
}

