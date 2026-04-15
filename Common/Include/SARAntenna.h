/********************************************************************
*	Module:			SARAntenna.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*				This header file contans the definitions for the abstract base
*					class SARAntenna.
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

	0.0	2001/05/24		Igor Zabarsky	start

********************************************************************/

#if !defined(AFX_SARANTENNA_H__128718A3_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_)
#define AFX_SARANTENNA_H__128718A3_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
using namespace std;
#include "Win32Port.h"
#include "MessType.h"

#include "Antenna.h"
		//ACU output function request parameters
enum {STNDBY,RMT_STNDBY,WRITE_AZEL,RATE_AZEL};

class CSARAntenna : public CAntenna  
{
protected:
	Win32Port			*m_pAZPort,*m_pELPort;
	ANT_STATUS_BLOCK	m_AntStatus;
	PROFILE_DATA		m_Prifile;
	ZENITH_MODE			m_ZenithMode;
	list<lpAZEL_FORMAT> m_AzelRecord;				//list of AZEL record vectors
	HANDLE				m_hFile;
	int					m_AZFirstDedugOutputLine;
	int					m_ELFirstDedugOutputLine;
	int					m_FirstDebugOutputLine;

		//ACU output function request parameters
	//enum {STNDBY,RMT_STNDBY,WRITE_AZEL,RATE_AZEL};
		//ACU port names
	enum {AZIMUTH,ELEVATION};
		//Antenna speed
	enum {HiSpeed,LowSpeed};

		//It calculates the azimuth and elevation of the antenna at a given time in 
		//the slew sequence.The acceleration and max velocity is taken into considaration
		//for determining the position of antenna.
	virtual void MoveProfile(DOUBLE SlewCurTime);

		//It checks if the antenna's motion is within the beam width
	virtual EMS_RESULT	CheckMotion();

		//It ensures that the antenna azimuth and elevation are within the beamwidth
	virtual EMS_RESULT	Locate(DOUBLE& fAZ, DOUBLE& fEL);

		//It determines when to start slewing the antenna around at its point of maximum
		//elevation. This is to ensure that the antenna will not exceed its maximum 
		//azimuth slew rate at this point of the setellite pass.
	virtual void ZenithCheck();

		//It caculates the max time required by the antenna to slew to a specified azimuth 
		//and elevation. The max slew rate and accelaration of the antenna are considerated
		//in the caculations.
	virtual void CalcTime(DOUBLE& SlewTime);

		//It accumulates the changes in azimuth between each successive vector to determine 
		//the magnitude and diraction of the azimuth sweep.
	virtual void TrackDir(INT&	nDiraction);

		//It calculats the position of the antenna at the specified time within the
		//setellite pass
	virtual void PassAngles(DOUBLE tTime,DOUBLE& dAzimuth,DOUBLE& dElevation);

	virtual EMS_RESULT Send(INT nChannel,LPVOID lpData, DWORD &nCount);

		//It provides the communication link between the SARAntenna and ACU
	virtual EMS_RESULT Output(DWORD wRequest, DOUBLE fAZCoordinate, DOUBLE fELCoordinate);

	virtual	EMS_RESULT Home();

		//It test AZEL records from AZEL librery.
	virtual EMS_RESULT Test(TRACKDATA TrackData);

		//It recurtion function that makes move as smooth as smooth
		//lavel says.
	virtual EMS_RESULT TrackSmoothMove(TRACKDATA& trackData);

		//It reads the antenna's status from the ACU's and stores the information 
		//in the status structure block m_AntStatus.
	virtual EMS_RESULT GetStatus();

		//It clean communication channels
	virtual EMS_RESULT Purge();

	virtual EMS_RESULT CheckAnt();
		//It clear any antenna faultes and resume proper antenna operation
	virtual void Reset();

	virtual EMS_RESULT OldFashionTrack(TRACKDATA& TrackData);
	virtual EMS_RESULT OldFashionTrack1(TRACKDATA& TrackData);

		//It moves the antenna to track a satellite by using lpszAZELfile vectors, which 	
		//is generated during prepass by the ORBIT program
	virtual EMS_RESULT Track(LPTSTR lpszAZELfile);

		//It sends move command to the ACU and wait until the antenna reached 
		//it's destanation or fault accure.
	virtual EMS_RESULT IndtMove(DOUBLE fAZCoordinate, DOUBLE fELCoordinate);

		//It moves the antenna to desired azimuth and elevation by given diraction
	virtual EMS_RESULT Move(double fAZCoordinate, double fELCoordinate, 
		INT wDiraction = NO_MOTION);

		//It initionales SARAntenna's m_TrackData, m_ZenithMode. Also programs
		//AZIMUTH and ELEVATION indexers\drivers for complit pass, locates
		//SARAntenna to start position and waits for right time to strat tracking.
	virtual LONG ProgSmoothTrack(LONG& tExeTime, LONG& tWaitTime,
		TRACK_MODE = REAL);

	//virtual EMS_RESULT CheckProgMotion();
	virtual EMS_RESULT	SetFileToTrackData(TRACKDATA& TrackData);
	virtual void		SetTimingToTrackData(TRACKDATA& TrackData);
	virtual EMS_RESULT  SetProgSmoothTracking(TRACKDATA& TrackData);
	virtual EMS_RESULT	SetMonitorSmoothMove();

	virtual VOID CalSARMove(MOVE &AZMove,MOVE &ELMove,
		INT wDiraction = NO_MOTION);

	virtual VOID CalibrateTrackTiming(DOUBLE& AZProp,DOUBLE& ELProp);
	virtual DOUBLE CalcRampTime(INT nChannel,DOUBLE DelVelocity);
	virtual DOUBLE GetRampTime(INT Divider,INT M,DWORD F,DWORD V);

	LONG ReadIoStatus(INT Channel);
public:
	CSARAntenna(const string &AZPort_name,
				const string &ELPort_name,
               long baud_rate	=	UNCHANGED,
               char parity		=	UNCHANGED,
               int word_length	=	UNCHANGED,
               int stop_bits	=	UNCHANGED,
               int dtr			=	SET,
               int rts			=	SET,
               int xon_xoff		=	DISABLE,
               int rts_cts		=	DISABLE,
               int dtr_dsr		=	DISABLE );
	CSARAntenna(){}



	virtual void  SendAntMessage(CHAR mgType, LPTSTR szText);
	CHAR*		Trim(CHAR* lpInString);
		//This function waits til specific number of characters resived
		//through specific port, meanwhile notification functions are
		//throwing.
	virtual RS232Error IdleFunction(Win32Port *port);
	virtual TRACKDATA& GetTrackData() { return m_TrackData;}

	virtual ~CSARAntenna();
};

#endif // !defined(AFX_SARANTENNA_H__128718A3_584C_11D5_9E1F_A0D8B68D7139__INCLUDED_)
