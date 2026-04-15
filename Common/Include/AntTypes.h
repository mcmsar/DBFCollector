/********************************************************************
*	Module:			AntTypes.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
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

	Rev	Date			Auth			Changes
	===	====			====			=======

	0.0	2001/04/26		Igor Zabarsky	start

********************************************************************/
#ifndef ANTTYPES
#define ANTTYPES

#include "..\Include\EMSTypex.h"
#include "..\Include\Emstime.h"

const char Month[][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep",
					"Oct","Nov","Dec"};


#include <list>
using namespace std ;

		//Antenna function request parameters
#define		ANT_STATUS_REPORT	"STAT"	//[out]ie. get the status of the antenna 
#define		ANT_SET				"SET"	//[in]ie. set/chack antenna & ACU configuration
#define		ANT_TRACK			"TRK"	//[in]ie. track given satellite
#define		ANT_CANCEL			"CANC"	//[in]ie. one of previouse request canceled 
#define		ANT_HOME			"HOME"	//[in]ie. put the antenna in its home position
#define		ANT_MOVE			"MOVE"	//[in]ie. point the antenna to specified azel
#define		ANT_TEST			"TEST"

		//Antenna function command parameters
#define		ANT_STOP			"STOP"	//[in]ie. stop immediatly and release schedule queue

		//Azimuth motion parameters
#define		NO_MOTION			-1		//Antenna is not moving
#define		CW					 0		//Clockwise azimuth motion
#define		CCW					 1		//Counter-clockwise azimuth mosion

//Service instalation macros - future use
/************************ Macros Start *****************************/
#define DMOD(a,b)				((a) - (double)((a)/(b)) * (b))
#define SIGN(a,b)				((b) >= 0 ? fabs(a): -fabs(a))

#define DECLARE_SERVICE(class_name, service_name) \
	public: \
	static class_name##* m_pThis; \
	static void  WINAPI service_name##Main(DWORD argc,LPTSTR* argv); \
	static void  WINAPI service_name##Handler(DWORD dwControl); \
	static DWORD WINAPI service_name##Watcher(LPVOID lpParameter);
	
#define IMPLEMENT_SERVICE(class_name, service_name) \
	class_name##* class_name::m_pThis = NULL; \
	\
	void WINAPI class_name::service_name##Main(DWORD argc,LPTSTR* argv) \
	{ \
		m_pThis->ServiceMainEntry(argc, argv, \
						(LPHANDLER_FUNCTION)service_name##Handler, \
						(LPHANDLER_FUNCTION)service_name##Watcher); \
	} \
	\
	void WINAPI class_name::service_name##Handler(DWORD dwControl) \
	{ \
		m_pThis->ServiceHandlerEntry(DWORD dwControl); \
	} \
	\
	DWORD WINAPI class_name::service_name##Watcher(LPVOID lpParameter) \
	{ \
		return m_pThis->WatcherThreadMemberProc(); \
	}

#define BEGIN_SERVICE_MAP \
	SERVICE_TABLE_ENTRY svcTable[] = { 

#define SERVICE_MAP_ENTRY(class_name, service_name) \
	{_T(#service_name), class_name::service_name##Main},

#define END_SERVICE_MAP \
	{NULL, NULL}}; \
	StartServiceCtrlDispatcher(svcTable);
/************************ Macros End *******************************/

typedef enum {REAL,TEST,DISPLAY,NUL} TRACK_MODE;


typedef struct tagANT_STATUS_BLOCK			
{
	BOOL		m_bCWSector;	//CW sector flag true ie if K1 high
	BOOL		m_bCWLimit;		//CW limit flag true ie if  K3 high
	BOOL		m_bCCWLimit;	//CCW limit flag true ie if K2 high
	BOOL		m_bLOWLimit;	//LOW limit flag true ie if K3 high
	BOOL		m_bHIGHLimit;	//HIGH limit flag true if   K2 high
	DOUBLE		m_TakenTime;	//Amount of time taken for request execution.
	DOUBLE		m_fAzimuth;		//Antenna azimuth
	DOUBLE		m_fElevation;	//Antenna elevation
	DOUBLE		m_fAZHowFarHome;//How far antenna from azimuth home position?
	DOUBLE		m_fELHowFarHome;//How far antenna from elevation home position?
	DOUBLE		m_dwAZinSteps;	//ACU current azimuth in steps
	DOUBLE		m_dwELinSteps;	//ACU current elevation in steps
	DWORD		m_dwAZOffset;	//AZ differ in staps between desirable and actual positions
	DWORD		m_dwELOffset;	//EL differ in staps between desirable and actual positions
}ANT_STATUS_BLOCK,*LPANT_STATUS_BLOCK;

typedef struct tagDIST_VECTOR
{
	DOUBLE Start;
	DOUBLE End;
}MOVE,*lpMOVE;

typedef struct tagAZEL_FORMAT
{
	DOUBLE	m_East;						//East coordinates in (Km)
	DOUBLE	m_North;					//North coordinates in (Km)
	DOUBLE	m_Up;						//Up coordinates in (Km)
}AZEL_FORMAT,*lpAZEL_FORMAT;

typedef struct tagSTEP_DATA
{
	//WORD	m_AZDivide;					// (\ nn) Divide ramping & constant vilocity.
	DOUBLE	m_AZSlope;					// (M nn) Accelaration/decelaration rates.
	//DWORD	m_AZStartStopVelocity;		// (F nn) It sets start/stop initial velocity
	DWORD	m_AZConstVelocity;			// (R nn) Step final vilocity (steps per second).
	//DWORD	m_AZtWaitTime;				// (W nn) Delay of nn miliseconds.
	MOVE	m_AZMoveVector;

	//WORD	m_ELDivide;					// (\ nn) Divide ramping & constant vilocity.
	DOUBLE	m_ELSlope;					// (M nn) Accelaration/decelaration rates.
	//DWORD	m_ELStartStopVelocity;		// (F nn) It sets start/stop initial velocity
	DWORD	m_ELConstVelocity;			// (R nn) Step final vilocity (steps per second).
	//DWORD	m_ELtWaitTime;				// (W nn) Delay of nn miliseconds.
	MOVE	m_ELMoveVector;
	//LONG	m_ELVelocity;				// Current step elevation velocity 
}STEP_DATA,*lpSTEP_DATA;

	//This data block definitions from the AZEL file that are required during a LEOLUT
	//controlled satellite pass.
typedef struct tagTRACKDATA
{
	//DWORD			m_AzelInterval;		//Interval between AZEL vector records
	//DWORD			m_AzelOdap;			//AZEL file orbit determination number
	DWORD			m_RecStard;
	//DWORD			m_AzelRev;			//AZEL file orbit revolution number
	//DWORD			m_Records;			//Number of vectors in AZEL file
//-----------------------------------------------------------------------------------------
	DOUBLE			m_AzelStart;		//Time counter of first AZEL file vector record
	DOUBLE			m_AzelEnd;			//Time counter of last AZEL file vector record
//-----------------------------------------------------------------------------------------
	list<lpAZEL_FORMAT>	m_AzelRecordsList;	//Records list
//-----------------------------------------------------------------------------------------
	list<lpSTEP_DATA>	m_TrackProfileList;
	INT					m_nDiraction;
	ULONG				m_ulSatelliteID;
	EMSTIME				m_emsAOS;
	ULONG				m_AzelInterval;		//Interval between AZEL vector records
	ULONG				m_Records;			//Number of vectors in AZEL file
	ULONG				m_StartStep;
	EMSTIME				m_EMSTimeStart;
	EMSTIME				m_EMSTimeEnd;
	CHAR				m_szFileName[260];
	TRACK_MODE			m_Mode;
	DOUBLE				m_WaitTime;
	void	CleanTrackProfileList()
	{
		list<lpSTEP_DATA>::iterator i; 		//list iterator number

			//delete list of vectors
		for (i = m_TrackProfileList.begin(); i != m_TrackProfileList.end();)
		{
			delete *i;
			++i;
			m_TrackProfileList.pop_front();
		}

	}
}TRACKDATA,*lpTRACKDATA;

/********************************************************************************************
						ANT_REQUEST_PACKET_HEADER
********************************************************************************************/

typedef struct tagANT_REQUEST_PACKET_HEADER
{
	INT		m_nTypeID;				//Packet header type identifier
	LONG	m_lSourceID;			//Packet source identifier
	LONG	m_lOriginatorID;		//Packet originator identifier
	CHAR	m_szReturnMailbox[80];	//Return mailbox name
}ANT_REQUEST_PACKET_HEADER,*LPANT_REQUEST_PACKET_HEADER;

typedef struct tagANT_REQUEST_DATA
{
	INT				m_nNumber;		//Antenna number (option in case if many antennas)
	DOUBLE			m_tSendTime;	//Time of request sending 
	DOUBLE			m_tRegTime;		//Time of request registration by request dchedule queue 
	DOUBLE			m_fAzimuth;
	DOUBLE			m_fElevation;
}ANT_REQUEST_DATA,*LPANT_REQUEST_DATA;


typedef	struct tagPacketData//CPackData
{
	ANT_REQUEST_DATA	m_AntData;			//[in]
	ANT_STATUS_BLOCK	m_Status;			//[out]
	CHAR				m_cAZELFile[180];	//[in] AZEL file name
	TRACK_MODE			m_TrackMode;		//Can be real or test
	TRACKDATA			m_TestTrackData;	//Records list
}PacketData,*LPPacketData;//							


typedef	struct tagANT_REQUEST_PACKET
{
	ANT_REQUEST_PACKET_HEADER	m_Header;		//Packet common header
	LPTSTR						m_szCommand;	//Packet command
	PacketData					m_uData;		//Packet data
	INT							m_nSize;		//Packet size
}ANT_REQUEST_PACKET,*LPANT_REQUEST_PACKET;

/************************END ANT_REQUEST_PACKET_HEADER*************************************/





/********************************************************************************************
								ANT_CONFIG
********************************************************************************************/
typedef struct tagANT_CONFIG
{
	DOUBLE		m_nACU_RAMP;		//M value for Pacific Scientific ACU
	DOUBLE		m_nACU_START;		//F value for Pacific Scientific ACU
	DOUBLE		m_nAZ_Divider;		//AZ rate divider for Pacific Scientific ACU
	DOUBLE		m_nEL_Divider;		//EL rate divider for Pacific Scientific ACU

	DOUBLE		m_IntTime;			//Time interval between commands
//-----------------------------------------------------------------------------------------
	DOUBLE		m_fAZ_Offset;		//Offset between true north and 0deg
	DOUBLE		m_fEL_Offset;		//Offset between true north and 0deg
	DOUBLE		m_fAZ_Factor;		//AZ gear ratio divided by motor step size
	DOUBLE		m_fEL_Factor;		//EL gear ratio divided by motor step size
	DOUBLE		m_fAZ_Rate;			//Max Antenna AZ slew rate
	DOUBLE		m_fEL_Rate;			//Max Antenna EL slew rate
	DOUBLE		m_fMax_Azimuth;		//Max antenna azimuth
	DOUBLE		m_fMax_Elevation;	//Max antenna elevation
	DOUBLE		m_fMin_Azimuth;		//Min antenna azimuth
	DOUBLE		m_fMin_Elevation;	//Min antenna elevation
	DOUBLE		m_fRamp_AZ;			//Ramp time for azimuth
	DOUBLE		m_fRamp_EL;			//Ramp time for elevation
	DOUBLE		m_fFast_Rate;		//Speed factor for fast move
	DOUBLE		m_fFastTime;		//Extra time dalay for fast move
	DOUBLE		m_fSlowRate;		//Speed factor for slow move
	DOUBLE		m_fSlowTime;		//Extra time dalay for slow move
	DOUBLE		m_fBeam_Width;		//Beam width of the antenna
	DOUBLE		m_fLatency;			//Control loop dalay time

	DOUBLE		m_tAZRampTime;
	DOUBLE		m_tELRampTime;
	ULONG		m_ulProgramDelay;
//	DOUBLE		m_AZHomeOffset;
//	DOUBLE		m_ELHomeOffset;
}ANT_CONFIG,*LPANT_CONFIG;
/*******************************END ANT_CONFIG*********************************************/

typedef struct	tagPROFILE_DATA
{
	DOUBLE		m_fInitAZ;				//Initial azimuth
	DOUBLE		m_fInitEL;				//Initial elevation
	DOUBLE		m_fDeltaAZ;				//Total change in azimuth
	DOUBLE		m_fDeltaEL;				//Total change in elevation
	DOUBLE		m_fAngleEL;				//Required elevation angle
	DOUBLE		m_fAngleAZ;				//Required azimuth angle
	DOUBLE		m_ptAZ_FullSlew;		//Time(degre) spent in azimuth full slew
	DOUBLE		m_ptEL_FullSlew;		//Time spent in elevation full slew
	DOUBLE		m_ptStartStopTimeAZ;	//Time spent in azimuth stop/star
	DOUBLE		m_ptStartStopTimeEL;	//Time spent in elevation stop/start
}PROFILE_DATA,*LPPROFILE_DATA;

typedef struct tagZenith_MODE
{
	BOOL	m_bMode;					//Zenith mode required
	DOUBLE	m_fInc;						//Azemuthal increment required
	DOUBLE	m_fStar;					//Start of zenith slewing
	DOUBLE	m_fEnd;						//End of zenith slewing
}ZENITH_MODE, *lpZENITH_MODE;


typedef struct tagVECTOR
{
	DOUBLE Azimuth;
	DOUBLE Elevation;
}VECTOR,*lpVECTOR;

const	DOUBLE	Pi = 3.14159265;

const	CHAR	ESC = 27;


const DWORD LookUpTable[] = {
	75,		721,	1054,	1324,	1562,	1776,	1973,	2158,	
	2333,	2498,	2656,	2810,	2954,	3103,	3245,	3376,	
	3504,	3628,	3762,	3889,	4007,	4114,	4228,	4347,	
	4452,	4562,	4678,	4775,	4876,	4982,	5092,	5207,	
	5297,	5389,	5486,	5585,	5689,	5760,	5870,	5946,	
	6063,	6144,	6227,	6312,	6400,	6490,	6583,	6678,
	6727,	6827,	6929,	6982,	7089,	7144,	7257,	7314,
	7373,	7493,	7554,	7617,	7680,	7745,	7877,	7945,	
	8014,	8084,	8156,	8229,	8303,	8378,	8455,	8533,
	8613,	8613,	8694,	8777,	8862,	8948,	8948,	9035,
	9125,	9216,	9216,	9309,	9404,	9501,	9501,	9600,	
	9600,	9701,	9804,	9804,	9910,	9910,	10017,	10127,	
	10127,	10240,	10240,	10355,	10355,	10473,	10473,	10593,	
	10593,	10716,	10716,	10842,	10842,	10971,	10971,	10971,	
	11104,	11104,	11239,	11239,	11378,	11378,	11378,	11520,	
	11520,	11520,	11666,	11666,	11815,	11815,	11815,	11969,	
	11969,	11969
};
#endif	//ANTTYPES