/********************************************************************
*	Module:			Antenna.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*				This header file contans the definitions for the abstract base
*					class Antenna.
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

	0.0	2001/05/22		Igor Zabarsky	start

********************************************************************/


#if !defined(AFX_ANTENNA_H__128718A2_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_)
#define AFX_ANTENNA_H__128718A2_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include <string>
#include <cassert>
#include <sstream>
using namespace std;

#include <windows.h>
#include  <math.h>
#include <process.h>

#include "MTDeque.h"
#include "RS232.h"
#include "AntError.h"
#include "AntTypes.h"
#include "EMSAntTime.h"

enum {FREE,BUSY};
typedef enum {READY,HOMING,MOVING,TRACKING,TESTING} REQUEST_QUEUE_STATUS;

class CAntenna  
{
protected:
	TRACKDATA					m_TrackData, m_ReqTrackData, m_DispTrackData;
	ANT_CONFIG					m_ConfigD;
	DOUBLE						m_DispAZ,m_DispEL;		//Coordinates for display
	DOUBLE						m_ErrorDispAZ, m_ErrorDispEL;//Coordinates errror for display
	EMS_RESULT					m_hr;
	int							m_debug_line_count;
	MTdeque<ANT_REQUEST_PACKET>	m_RequestQ;             //Request packet queue
	long						m_hRequestExeThread;	//Request exequte thread
	HANDLE						m_hKillExeThreadEvent;
	HANDLE						m_hWakeUpEvent;			//Wake up for new request
	CHAR						m_szStatus[10];
	BOOL						m_bSHUT_DOWN;			//Shut down flag
	enum {MAX_REQUEST_BUFFER_SIZE = 1024};
	REQUEST_QUEUE_STATUS		m_eReqQueStatus;
	int							m_nDummy_Arg;		//Dummy argument used in some slew functions


	TCHAR						m_szLogFilePath[512];

		//Critical sections for m_TrackData & m_ZenithMode data structurs.
		//I need them because two threds using same data independly, one for test/real tracking
		//and ather for displaing/monitoring.
	CRITICAL_SECTION m_TrackDataLock;

	CAntenna();
		//It's thread, seperate from main thread, that executes requests located in
		//request queue m_RequestQ
	static void RequestExeThread(void *arglist);

		//It moves the antenna to desired azimuth and elevation by given diraction
	virtual EMS_RESULT Move(double fAZCoordinate, double fELCoordinate, 
		INT wDiraction = NO_MOTION) = 0;

		//It moves the antenna to track a satellite by using lpszAZELfile vectors, which 	
		//is generated during prepass by the ORBIT program
	virtual EMS_RESULT Track(LPTSTR lpszAZELfile) = 0;

		//It aligns the antenna to its home switches, the aligns the plate with the 
		//true north.
	virtual EMS_RESULT Home() = 0;

	virtual EMS_RESULT Test(TRACKDATA TrackData) = 0;

	virtual void Stop();

		//It clean communication channels
	virtual EMS_RESULT Purge() = 0;

		//It clear any antenna faultes and resume proper antenna operation
	virtual void Reset() = 0;

	virtual EMS_RESULT CheckAnt() = 0;

	virtual void  SendAntMessage(CHAR mgType, LPTSTR szText) = 0;

		//It receive and executes requests from request queue til queue empties
	virtual EMS_RESULT RequestWorker();

		//Protected notifycation virtual functions
		//========================================
	virtual void ReqNotify(BOOL RQStatus){}
		//This function notify the antenna location 
	virtual void LocNotify(DOUBLE &AZ, DOUBLE &EL){}
		//This function notify the antenna location error
	virtual void ErrLocNotify(DOUBLE &AZ, DOUBLE &EL){}
		//This function notify the antenna new message.
	virtual void MsgNotify() {}
	virtual void TrackDlgMsgNotify() {}
	virtual void ReqQueStatusChangeNotify(DOUBLE AZ,DOUBLE EL) {}
	virtual void StepLostNotify(INT NewStepNum) {}

public:
	ostringstream		m_DispMsgStr;			//Messages holder string
	string				m_TrackDlgMsg;
	unsigned int		ErrorCount;
	DOUBLE				ElapsedTime;
	VECTOR				m_LocVector,m_ErrLocVector;

	HANDLE				m_hLogFile;

	virtual ~CAntenna();
	virtual EMS_RESULT RequestHandler(ANT_REQUEST_PACKET Request);
	virtual EMS_RESULT ReadConfig();
		//Optional Functions. Derived class isnot requered to support them
	virtual EMS_RESULT IdleFunction();
	virtual EMS_RESULT FormatDebugOutput(char* buffer = NULL, int LineNumber = -1);
	virtual REQUEST_QUEUE_STATUS GetReqQueStatus() 
				{return m_eReqQueStatus;}
		//Non virtual functions
	EMS_RESULT ErrorStatus() {return m_hr;}
	int DebugLineCount() {return m_debug_line_count;}
};

#endif // !defined(AFX_ANTENNA_H__128718A2_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_)
