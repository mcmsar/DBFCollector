/********************************************************************
*	Module:			SARAntenna.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*				This cpp file contans the definitions for the 
*					class SARAntenna, that connect Antenna Hardware to LEOLUT600
*					and provid control to antenna. I'am useing 5 threads in this
*					program 4 for hardware connection and one for request queue.
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

//#include "StdAfx.h"

//#include <afxwin.h>         // MFC core and standard components

//#include <afxext.h>         // MFC extensions
//#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
//#ifndef _AFX_NO_AFXCMN_SUPPORT
//#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <sstream>
//#endif // _AFX_NO_AFXCMN_SUPPORT

//#include "MFC Test Antenna.h"
#include "SARAntenna.h"
#include <deque>
#include <string>
using namespace std;

#include <windows.h>

//static CDebugWin debugWin;
//static char szDebug[256];

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
CSARAntenna::CSARAntenna(const string &AZPort_name,
						 const string &ELPort_name,
						long baud_rate,		// = UNCHANGED,
						char parity,		// = UNCHANGED,
						int word_length,	// = UNCHANGED,
						int stop_bits,		// = UNCHANGED,
						int dtr,			// = SET,
						int rts,			// = SET,
						int xon_xoff,		// = DISABLE,
						int rts_cts,		// = DISABLE,
						int dtr_dsr			// = DISABLE 
)
{
	m_pAZPort = new Win32Port(AZPort_name,
								   baud_rate,		// = UNCHANGED,
								   parity,			// = UNCHANGED,
								   word_length,		// = UNCHANGED,
								   stop_bits,		// = UNCHANGED,
								   dtr,				// = SET,
								   rts,				// = SET,
								   xon_xoff,		// = DISABLE,
								   rts_cts,			// = DISABLE,
								   dtr_dsr			// = DISABLE 
								   );
	m_pELPort = new Win32Port(ELPort_name,
								baud_rate,			// = UNCHANGED,
								parity,				// = UNCHANGED,
								word_length,		// = UNCHANGED,
								stop_bits,			// = UNCHANGED,
								dtr,				// = SET,
								rts,				// = SET,
								xon_xoff,			// = DISABLE,
								rts_cts,			// = DISABLE,
								dtr_dsr				// = DISABLE
								);
		//SARAntenna has to share the debug output with m_AZPort, mELPort and parent
		//class. To determine where first lines start, we call the FormatDebugOutput()
		//without parameters of all of them.
	m_FirstDebugOutputLine = CAntenna::FormatDebugOutput();
	m_AZFirstDedugOutputLine = m_pAZPort->FormatDebugOutput();
	m_ELFirstDedugOutputLine = m_pELPort->FormatDebugOutput();

	m_hFile = INVALID_HANDLE_VALUE;
	m_ReqTrackData.m_StartStep = 0;
	m_DispTrackData.m_StartStep = 0;

	m_DispTrackData.m_Mode = DISPLAY;
	
}

EMS_RESULT  CSARAntenna::SetProgSmoothTracking(TRACKDATA& TrackData)
{

	::EnterCriticalSection(&m_TrackDataLock);
	TRACKDATA TempTrackData = m_TrackData;
	m_TrackData = TrackData;

	EMS_RESULT			hr = EMS_OK;
	INT					nDiraction;			//Move diraction of antenna
	CHAR				Buff[256];
	DWORD				nCount;
	DOUBLE				dwMaxDriverVelocity = LookUpTable
		[sizeof(LookUpTable)/sizeof(DWORD) - 1];
	INT					nRecordStart = 0;
	INT					nRecordPers = m_TrackData.m_Records - 1;
	MOVE				AZMove,ELMove;
	DOUBLE				PrevAZNormPos = 0.0;
	DOUBLE				PrevELNormPos = 0.0;
	LONG				CurrAZVelocity;
	LONG				CurrELVelocity;
	DOUBLE				DistInSteps;
	DOUBLE				AzelInterval = m_TrackData.m_AzelInterval/1000;
	DOUBLE				tRampTime;
	BOOL				bSwitchBack = FALSE;
	BOOL				bSwitchAhead = FALSE;

	lpSTEP_DATA			pStepData;
	BOOL				bMoveable = (m_TrackData.m_Records - m_TrackData.m_StartStep) > 1 &&
								   (m_TrackData.m_Mode == TEST || m_TrackData.m_Mode == REAL);
#ifdef LOG_FILE_ACTIVE
	SYSTEMTIME			SysTime;
	CEMSAntTime			EMSCurrTime;
	TCHAR				szLogBuff[1024];
	DWORD				nBWrite;
#endif
	m_TrackData.CleanTrackProfileList();

	TrackDir(nDiraction);

	m_TrackData.m_nDiraction = nDiraction;

	PassAngles(m_TrackData.m_AzelStart,PrevAZNormPos,PrevELNormPos);

	AZMove.Start = 0.0;	AZMove.End = PrevAZNormPos;
	ELMove.Start = 0.0;	ELMove.End = PrevELNormPos;

	CalSARMove(AZMove,ELMove,nDiraction);

		if((PrevAZNormPos < 180) &&(PrevAZNormPos > 90))
			PrevAZNormPos -= 360;

		if((PrevAZNormPos < 270) &&(PrevAZNormPos > 180))
			PrevAZNormPos += 360;

	PrevAZNormPos = AZMove.End;
	PrevELNormPos = ELMove.End;


	if(bMoveable || m_TrackData.m_Mode == TEST)
	{
		if(m_TrackData.m_Mode == TEST)
			m_TrackData.m_StartStep = 0;		//Test start from beginning

		Sleep(10);			//For messages.

		if(nDiraction == CW)
			SendAntMessage(MSG_TRACE,"Clockwise satellite track.");
		else
			SendAntMessage(MSG_TRACE,"Counter clockwise satellite track.");


		Sleep(10);

		nRecordStart = m_TrackData.m_StartStep;

/*		PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelInterval *
			m_TrackData.m_StartStep,PrevAZNormPos,PrevELNormPos);*/

		sprintf(Buff,"Position antenna to the start: AZ%f,EL%f",
			PrevAZNormPos,PrevELNormPos);
		SendAntMessage(MSG_TRACE,Buff);

#ifdef LOG_FILE_ACTIVE
		GetSystemTime(&SysTime);
		EMSCurrTime.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
							SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
		sprintf(szLogBuff,"At %s antenna started travel to start position.\r\n",EMSCurrTime.GetTimeData());
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif

		hr = Move(PrevAZNormPos,PrevELNormPos,nDiraction);

#ifdef LOG_FILE_ACTIVE
		GetSystemTime(&SysTime);
		EMSCurrTime.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
							SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
		sprintf(szLogBuff,"At %s antenna located on start position.\r\n",EMSCurrTime.GetTimeData());
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
		sprintf(szLogBuff,"      Antenna position :-> AZ = %5.2f EL = %5.2f\r\n",
			PrevAZNormPos,PrevELNormPos);
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif

		Output(RMT_STNDBY,0,0);
	
		sprintf(Buff,"%c",ESC);		//ESC = '27'
		Send(AZIMUTH,Buff,nCount = 2);
		sprintf(Buff,"%c",ESC);		//ESC = '27'
		Send(ELEVATION,Buff,nCount = 2);

		SendAntMessage(MSG_TRACE,"Started programming Indexers");
	

			//Enter the program block at address 0
		sprintf(Buff,"E\r");
		hr = Send(AZIMUTH,Buff,nCount = 2);
		sprintf(Buff,"E\r");
		hr = Send(ELEVATION,Buff,nCount = 2);
	}
	else
	{
		if(m_TrackData.m_Mode == REAL)
			return hr = EMS_TOO_LATE_FOR_TRACK;
	}
#ifdef LOG_FILE_ACTIVE
		GetSystemTime(&SysTime);
		EMSCurrTime.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
							SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
		sprintf(szLogBuff,"At %s strted programming indexes.\r\n",EMSCurrTime.GetTimeData());
		strcat(szLogBuff,"\r\n++++++++++++-INDEXES PROGRAMMING REPORT-++++++++++++++\r\n\r\n");
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

		sprintf(szLogBuff,"\r\n|No|%-10s|%-9s|%-9s|%-8s|%-7s|%-8s|%-7s|\r\n",
			"TIME","AZIMUTH","ELEVATIO","AZ VELOC","AZ F","EL VELOC","EL F");
		strcat(szLogBuff,"|--|----------|---------|---------|--------|-------|--------|-------|\r\n");
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

		EMSCurrTime.SetTime(m_TrackData.m_EMSTimeStart);

#endif
//----------------------------- Programming ------------------------------------
	for(nRecordStart;nRecordStart<nRecordPers && hr == EMS_OK && 
		!m_bSHUT_DOWN;nRecordStart++)
	{
		pStepData = new STEP_DATA;

		PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelInterval*nRecordStart,
			AZMove.Start,ELMove.Start);
		PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelInterval*
			(nRecordStart+1),AZMove.End,ELMove.End);

		if((AZMove.Start < 360)&&(AZMove.Start > 270) && 
			(AZMove.End < 270) &&(AZMove.End > 180))
				bSwitchBack = TRUE;

		if((AZMove.Start < 90)&&(AZMove.Start > 0) && 
			(AZMove.End < 180) &&(AZMove.End > 90))
				bSwitchAhead = TRUE;

		CalSARMove(AZMove,ELMove,nDiraction);
		if(bSwitchBack)
			AZMove.End -= 360;
		if(bSwitchAhead)
			AZMove.End += 360;

#ifdef LOG_FILE_ACTIVE		
		sprintf(szLogBuff,"|%2d|%9s | %7.2f | %7.2f |",
			nRecordStart,EMSCurrTime.GetTimeData(),PrevAZNormPos,PrevELNormPos);
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
		EMSCurrTime.AddSeconds((float)(m_TrackData.m_AzelInterval/1000));
#endif

		AZMove.Start = PrevAZNormPos;
		PrevAZNormPos = AZMove.End;

		ELMove.Start = PrevELNormPos;
		PrevELNormPos = ELMove.End;

		DistInSteps = (AZMove.End - AZMove.Start)*m_ConfigD.m_fAZ_Factor;

		CurrAZVelocity = fabs(DistInSteps)*(DOUBLE)m_ConfigD.m_nAZ_Divider/AzelInterval;

		tRampTime = GetRampTime((INT)m_ConfigD.m_nAZ_Divider,(INT)m_ConfigD.m_nACU_RAMP,
			(INT)(m_ConfigD.m_nACU_START * m_ConfigD.m_nAZ_Divider),CurrAZVelocity);

		//tRampTime = (CurrAZVelocity/dwMaxDriverVelocity)*m_ConfigD.m_tAZRampTime;

		//Start 45.0000 factor correction

/*
		//Three point correction

		if(CurrAZVelocity < 6)
			DistInSteps *= 0.212;
		else
			if(CurrAZVelocity < 300)
				DistInSteps *= 0.960;
			else
				DistInSteps *= 0.955;
*/
/*		CurrAZVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nAZ_Divider/
			(AzelInterval - tRampTime/2.0));*/

		CurrAZVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nAZ_Divider/
			(AzelInterval - tRampTime));

		//End 45.0000 factor correction



		if(m_bSHUT_DOWN) break;

		if(bMoveable || m_TrackData.m_Mode == TEST)
		{
/*			sprintf(Buff,"R%d\r",CurrAZVelocity);
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"W%d\r",(INT)(m_TrackData.m_AzelInterval - 810 -
				fabs(CurrAZVelocity)*0.91));

			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);
*/
			sprintf(Buff,"V%d\r",abs(CurrAZVelocity));
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);

			if(m_bSHUT_DOWN) break;
/*
			if(DistInSteps >= 0) 
				sprintf(Buff,"+%d\r",DistInSteps);
			else
				sprintf(Buff,"%d\r",DistInSteps);
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);
*/
			sprintf(Buff,"@%d\r",(INT)AZMove.End*m_ConfigD.m_fAZ_Factor);
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);
		}

		if(m_bSHUT_DOWN) break;

		pStepData->m_AZMoveVector = AZMove;
		pStepData->m_AZSlope = tRampTime;
		pStepData->m_AZConstVelocity = CurrAZVelocity;


#ifdef LOG_FILE_ACTIVE
		sprintf(szLogBuff," %6d | %5d |",
			CurrAZVelocity,(INT)(m_TrackData.m_AzelInterval - 810 - fabs(CurrAZVelocity)*0.91));
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif

//--------------------------- END AZIMUTH PROG --------------------------------------
		DistInSteps = (ELMove.End - ELMove.Start)*m_ConfigD.m_fEL_Factor;

		CurrELVelocity = fabs(DistInSteps)*(DOUBLE)m_ConfigD.m_nEL_Divider/AzelInterval;

		tRampTime = GetRampTime((INT)m_ConfigD.m_nEL_Divider,(INT)m_ConfigD.m_nACU_RAMP,
			(INT)(m_ConfigD.m_nACU_START * m_ConfigD.m_nEL_Divider),CurrELVelocity);

//		tRampTime = (CurrELVelocity/dwMaxDriverVelocity)*m_ConfigD.m_tELRampTime;

/*		CurrELVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nEL_Divider/
			(AzelInterval - tRampTime/2.0+fabs(CurrELVelocity)*0.00025) + 0.49);
*/
/*
		//Start 45.0000 factor correction
		if(CurrELVelocity < 6)
			DistInSteps *= 0.212;
		else
			if(CurrELVelocity < 300)
				DistInSteps *= 0.970;
			else
				DistInSteps *= 0.955;
*/

/*		CurrELVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nEL_Divider/
			(AzelInterval - tRampTime/2.0));*/

		CurrELVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nEL_Divider/
			(AzelInterval - tRampTime));

		//End 45.0000 factor correction

		if(bMoveable || m_TrackData.m_Mode == TEST)
		{
/*			sprintf(Buff,"R%d\r",CurrELVelocity);
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"W%d\r",(INT)(m_TrackData.m_AzelInterval - 810 - 
				fabs(CurrELVelocity)*0.7));

			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);
*/
			sprintf(Buff,"V%d\r",abs(CurrELVelocity));
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);

			if(m_bSHUT_DOWN) break;
/*
			if(DistInSteps >= 0)
				sprintf(Buff,"+%d\r",DistInSteps);
			else
				sprintf(Buff,"%d\r",DistInSteps);
*/
			sprintf(Buff,"@%d\r",(INT)ELMove.End*m_ConfigD.m_fEL_Factor);
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);

			if(m_bSHUT_DOWN) break;

			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);
		}

		pStepData->m_ELMoveVector = ELMove;
		pStepData->m_ELSlope = tRampTime;
		pStepData->m_ELConstVelocity = CurrELVelocity;

#ifdef LOG_FILE_ACTIVE
		sprintf(szLogBuff," %6d | %5d |",
			CurrELVelocity,(INT)(m_TrackData.m_AzelInterval - 810 - fabs(CurrELVelocity)*0.91));
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif


//--------------------------- END ELEVATION PROG -------------------------------------

		if(bMoveable || m_TrackData.m_Mode == TEST)
		{
			if(hr == EMS_OK)
				sprintf(Buff,"Programming Step %d:Velocity AZ%d EL%d is OK",
				nRecordStart+1,CurrAZVelocity,CurrELVelocity);
			else
				sprintf(Buff,"Programming Step %d:Velocity AZ%d EL%d is FAULT",
				nRecordStart+1,CurrAZVelocity,CurrELVelocity);
			SendAntMessage(MSG_TRACE,Buff);
		}

		m_TrackData.m_TrackProfileList.insert(m_TrackData.m_TrackProfileList.end(),
			pStepData);

#ifdef LOG_FILE_ACTIVE
		sprintf(szLogBuff,"\r\n|--|----------|---------|---------|--------|-------|--------|-------|\r\n");
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif
	}

	if(bMoveable || m_TrackData.m_Mode == TEST && !m_bSHUT_DOWN)
		if(hr == EMS_OK)
		{
				//End and store program block 
			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(AZIMUTH,Buff,nCount);

			sprintf(Buff,"Q1\r");
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);

			sprintf(Buff,"R0\r");			//Stop motors
			nCount = strlen(Buff);
			hr = Send(ELEVATION,Buff,nCount);
			sprintf(Buff,"R0\r");			//Stop motors
			nCount = strlen(Buff);
			Sleep(100);
			hr = Send(AZIMUTH,Buff,nCount);

			sprintf(Buff,"E\r");			//Stop program block
			Send(AZIMUTH,Buff,nCount = 2);
			sprintf(Buff,"E\r");			//Stop program block
			Sleep(100);
			Send(ELEVATION,Buff,nCount = 2);

			Output(RMT_STNDBY,0,0);

			SendAntMessage(MSG_TRACE,"Successed to programming Indexers.");
		}
		else
		{
				//End and not store program block 
			sprintf(Buff,"%c\r",ESC);		//ESC = '27'
			Send(AZIMUTH,Buff,nCount = 2);
			sprintf(Buff,"%c\r",ESC);		//ESC = '27'
			Send(ELEVATION,Buff,nCount = 2);
			Output(RMT_STNDBY,0,0);
			SendAntMessage(MSG_TRACE,"Fault to program Indexers.");
		}

#ifdef LOG_FILE_ACTIVE
	strcat(szLogBuff,"\r\n+++++++++++-END INDEXES PROGRAMMING REPORT-+++++++++++\r\n\r\n");
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

	GetSystemTime(&SysTime);
	CEMSAntTime AOSTime(m_TrackData.m_emsAOS);

	EMSCurrTime.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
				SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
	sprintf(szLogBuff,"At %s finished programming indexes.\r\n",EMSCurrTime.GetTimeData());
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

	EMSTIMEFIELDS WaitTime = AOSTime - EMSCurrTime;
	sprintf(szLogBuff,"AOS in %d Min %d Sec\r\n\r\n",WaitTime.nMinute,WaitTime.nSecond);
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif

	TrackData = m_TrackData;
	m_TrackData = TempTrackData;
	::LeaveCriticalSection(&m_TrackDataLock);
	return hr;
}


	//It initionales SARAntenna's m_TrackData, m_ZenithMode. Also programs
	//AZIMUTH and ELEVATION indexers\drivers for complit pass, locates
	//SARAntenna to start position and waits for right time to strat tracking.
LONG CSARAntenna::ProgSmoothTrack(LONG& tExeTime, LONG& tWaitTime,
									 TRACK_MODE mode)
{
	INT					iStepCount;
	EMS_RESULT			hr = EMS_OK;
	INT					nDiraction;			//Move diraction of antenna
	DOUBLE				dAZ,dEL;			//Calculated location
	CHAR				Buff[256];
	LONG				tProgTime = (m_TrackData.m_Records - 1)*3000;
	DWORD				nCount;
	//DOUBLE				AZCalibTrackTime,ELCalibTrackTime;
	LONG				tAzelStart;

	for(iStepCount = 0,tAzelStart = m_TrackData.m_AzelStart + tProgTime;
		tAzelStart < ReadTime() && mode != TEST;iStepCount++,
			tAzelStart += m_TrackData.m_AzelInterval);

	if((m_TrackData.m_Records - iStepCount) < 3)
	{
		SendAntMessage(MSG_TRACE,"Non time laft for tracking this pass.");
		return -1;
	}

	m_TrackData.m_RecStard = iStepCount;

	if(iStepCount)
		SendAntMessage(MSG_TRACE,"Tracking from middle of Azel file.");

		//Determine diraction of tracking.
	TrackDir(nDiraction);

	Sleep(10);			//For messages.

	if(nDiraction == CW)
		SendAntMessage(MSG_TRACE,"Clockwise satellite track.");
	else
		SendAntMessage(MSG_TRACE,"Counter clockwise satellite track.");

	Sleep(10);
	PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelStart *
		iStepCount,dAZ,dEL);
	sprintf(Buff,"Position antenna to the start: AZ%f,EL%f",
		dAZ,dEL);
	SendAntMessage(MSG_TRACE,Buff);
	hr = Move(dAZ,dEL);

	Output(RMT_STNDBY,0,0);
	
/*	sprintf(Buff,"%c",ESC);		//ESC = '27'
	Send(AZIMUTH,Buff,nCount = 2);
	sprintf(Buff,"%c",ESC);		//ESC = '27'
	Send(ELEVATION,Buff,nCount = 2);*/

//----------------------------- Programming ------------------------------------
	INT				nRecordPers = m_TrackData.m_Records - 1;
	MOVE			AZMove,ELMove;
	DOUBLE			PrevAZNormPos = 0.0;
	DOUBLE			PrevELNormPos = 0.0;
	LONG			CurrAZVelocity;
	LONG			CurrELVelocity;
	DOUBLE			DistInSteps;
	DOUBLE			AzelInterval = m_TrackData.m_AzelInterval/1000;
	DOUBLE			tRampTime;
	DOUBLE			tAZCalibTime = 0.670;
	DOUBLE			tELCalibTime = 0.140;
	BOOL			bSwitchBack = FALSE;

	SendAntMessage(MSG_TRACE,"Started programming Indexers");
	

		//Enter the program block at address 0
	sprintf(Buff,"E\r");
	hr = Send(AZIMUTH,Buff,nCount = 2);
	sprintf(Buff,"E\r");
	hr = Send(ELEVATION,Buff,nCount = 2);

	PassAngles(m_TrackData.m_AzelStart,PrevAZNormPos,PrevELNormPos);

	for(iStepCount;iStepCount<nRecordPers && hr == EMS_OK;iStepCount++)
	{
		PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelInterval*iStepCount,
			AZMove.Start,ELMove.Start);
		PassAngles(m_TrackData.m_AzelStart + m_TrackData.m_AzelInterval*
			(iStepCount+1),AZMove.End,ELMove.End);

		if((AZMove.Start < 360)&&(AZMove.Start > 270) && 
			(AZMove.End < 270) &&(AZMove.End > 180))
			bSwitchBack = TRUE;

		CalSARMove(AZMove,ELMove,nDiraction);
		if(bSwitchBack)
			AZMove.End -= 360;
		AZMove.Start = PrevAZNormPos;
		PrevAZNormPos = AZMove.End;

		ELMove.Start = PrevELNormPos;
		PrevELNormPos = ELMove.End;

		DistInSteps = (AZMove.End - AZMove.Start)*m_ConfigD.m_fAZ_Factor;

			//ConfigD.m_tAZRampTime/4 = 0.61823231067429. = Tw-Tr;
		CurrAZVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nAZ_Divider/
			(AzelInterval) + 0.49);
		
		tRampTime = CalcRampTime(AZIMUTH,fabs(CurrAZVelocity));

		CurrAZVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nAZ_Divider/
			(AzelInterval - tRampTime/2 + tAZCalibTime) + 0.49);

		sprintf(Buff,"R%d\r",CurrAZVelocity);
		nCount = strlen(Buff);
		hr = Send(AZIMUTH,Buff,nCount);


		sprintf(Buff,"W%d\r",(INT)(m_TrackData.m_AzelInterval - 896));
			//(tAZCalibTime + tRampTime)*1000));//*-800-m_ConfigD.m_tAZRampTime/2.0*/));
		nCount = strlen(Buff);
		hr = Send(AZIMUTH,Buff,nCount);


		sprintf(Buff,"Q1\r");
		nCount = strlen(Buff);
		hr = Send(AZIMUTH,Buff,nCount);

//----------------------------------------------------------------------------
		DistInSteps = (ELMove.End - ELMove.Start)*m_ConfigD.m_fEL_Factor;

		CurrELVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nEL_Divider/
			(AzelInterval) + 0.49);

		tRampTime = CalcRampTime(ELEVATION,fabs(CurrAZVelocity));

		CurrELVelocity = (LONG)(DistInSteps*(DOUBLE)m_ConfigD.m_nEL_Divider/
			(AzelInterval - tRampTime/2 + tELCalibTime) + 0.49);

		sprintf(Buff,"R%d\r",CurrELVelocity);
		nCount = strlen(Buff);
		hr = Send(ELEVATION,Buff,nCount);

		sprintf(Buff,"W%d\r",(INT)(m_TrackData.m_AzelInterval - 896));
			//(tELCalibTime + tRampTime)*1000)-565);//-800/*-m_ConfigD.m_tELRampTime/2.0*/));
		nCount = strlen(Buff);
		hr = Send(ELEVATION,Buff,nCount);

		sprintf(Buff,"Q1\r");
		nCount = strlen(Buff);
		hr = Send(ELEVATION,Buff,nCount);

//-----------------------------------------------------------------------
		if(hr == EMS_OK)
			sprintf(Buff,"Programming Step %d:Velocity AZ%d EL%d is OK",
			iStepCount+1,CurrAZVelocity,CurrELVelocity);
		else
			sprintf(Buff,"Programming Step %d:Velocity AZ%d EL%d is FAULT",
			iStepCount+1,CurrAZVelocity,CurrELVelocity);
		SendAntMessage(MSG_TRACE,Buff);
	}



	if(hr == EMS_OK)
	{
			//End and store program block 
		sprintf(Buff,"Q1\r");
		nCount = strlen(Buff);
		hr = Send(AZIMUTH,Buff,nCount);

		sprintf(Buff,"Q1\r");
		nCount = strlen(Buff);
		hr = Send(ELEVATION,Buff,nCount);

		sprintf(Buff,"R0\r");			//Stop motors
		nCount = strlen(Buff);
		hr = Send(ELEVATION,Buff,nCount);
		sprintf(Buff,"R0\r");			//Stop motors
		nCount = strlen(Buff);
		Sleep(100);
		hr = Send(AZIMUTH,Buff,nCount);

		sprintf(Buff,"E\r");			//Stop program block
		Send(AZIMUTH,Buff,nCount = 2);
		sprintf(Buff,"E\r");			//Stop program block
		Sleep(100);
		Send(ELEVATION,Buff,nCount = 2);

		Output(RMT_STNDBY,0,0);

		SendAntMessage(MSG_TRACE,"Successed to programming Indexers.");
	}
	else
	{
			//End and not store program block 
		sprintf(Buff,"%c\r",ESC);		//ESC = '27'
		Send(AZIMUTH,Buff,nCount = 2);
		sprintf(Buff,"%c\r",ESC);		//ESC = '27'
		Send(ELEVATION,Buff,nCount = 2);
		SendAntMessage(MSG_TRACE,"Fault to program Indexers.");
	}

//----------------------------- End Programming --------------------------------

	tWaitTime = m_TrackData.m_AzelStart - ReadTime();
	if(tWaitTime > 0)
		Sleep(tWaitTime);
	//if(hr != EMS_OK)
	return hr;
/*	else
	{
		sprintf(Buff,"G\r");					//Start program in indexers
		nCount = strlen(Buff);
		m_pELPort->Write(Buff,nCount);
		sprintf(Buff,"G\r");					//Start program in indexers
		nCount = strlen(Buff);
		hr = Send(AZIMUTH,Buff,nCount);
		
		return hr;//m_TrackData.m_AzelEnd - m_TrackData.m_AzelStart;
	}*/
}
DOUBLE CSARAntenna::CalcRampTime(INT nChannel,DOUBLE DelVelocity)
{
	DOUBLE tRampTime;
	INT		TableSize = sizeof(LookUpTable)/sizeof(DWORD);
	DOUBLE	M = 2.0;
	DOUBLE	V = 16168.0;
	INT		nCount;
	BOOL    bDone;

	if(nChannel == AZIMUTH)
	{
		DOUBLE	AZ_F = m_ConfigD.m_nACU_START*m_ConfigD.m_nAZ_Divider;
		DOUBLE	AZ_D = m_ConfigD.m_nAZ_Divider;

		bDone = DelVelocity*AZ_D <= AZ_F;

		tRampTime = 1/AZ_F;

		for(nCount = 0; nCount < TableSize && !bDone; nCount++)
			if(LookUpTable[nCount] > AZ_F)
				if(LookUpTable[nCount] <= DelVelocity*AZ_D)
					tRampTime += 1/LookUpTable[nCount];
				else
					bDone = TRUE;

		if(DelVelocity*AZ_D > LookUpTable[TableSize])
			tRampTime += 1/V;

		tRampTime *= M*AZ_D;
	}
	else
	{
		DOUBLE	EL_F = m_ConfigD.m_nACU_START*m_ConfigD.m_nEL_Divider;
		DOUBLE	EL_D = m_ConfigD.m_nEL_Divider;

		bDone = DelVelocity*EL_D <= EL_F;

		tRampTime = 1/EL_F;

		for(nCount = 0; nCount < TableSize && !bDone; nCount++)
			if(LookUpTable[nCount] > EL_F)
				if(LookUpTable[nCount] <= DelVelocity*EL_D)
					tRampTime += 1/LookUpTable[nCount];
				else
					bDone = TRUE;

		if(DelVelocity*EL_D > LookUpTable[TableSize])
			tRampTime += 1/V;

		tRampTime *= M*EL_D;
	}

	return tRampTime;
}

VOID CSARAntenna::CalibrateTrackTiming(DOUBLE& AZProp,DOUBLE& ELProp)
{
	DOUBLE				tStartTime;
	DOUBLE				tAZDel,tELDel;
	DWORD				nCount;
	CHAR				Buff[256];
	DOUBLE				RespProp = 0.011667;

	SendAntMessage(MSG_TRACE,"Calibrating Indexers - please wait...");

	sprintf(Buff,"%c",ESC);		//ESC = '27'
	Send(AZIMUTH,Buff,nCount = 2);
	sprintf(Buff,"%c",ESC);		//ESC = '27'
	Send(ELEVATION,Buff,nCount = 2);

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
/*
	sprintf(Buff,"W1000\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
*/
	sprintf(Buff,"R 0\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
/*
	sprintf(Buff,"W1\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	sprintf(Buff,"S\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
*/
	sprintf(Buff,"K\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	tStartTime = ReadTime();

	sprintf(Buff,"G 0 1\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
	/*Sleep(600);
	m_pAZPort->FlushRXBuffer();
	Sleep(600);*/

	//while(m_pAZPort->RXSpaceUsed() == 0);
	for(m_pAZPort->Read(Buff,500);!strstr(Buff,"K");
			m_pAZPort->Read(Buff,500));

	tAZDel = ReadTime() - tStartTime;
	Sleep(1600);
	m_pAZPort->FlushRXBuffer();

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
/*
	sprintf(Buff,"W1000\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	sprintf(Buff,"R0\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

/*
	sprintf(Buff,"S\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
*/
	sprintf(Buff,"K\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);

	tStartTime = ReadTime();

	sprintf(Buff,"G 0 1\r");
	nCount = strlen(Buff);
	Send(AZIMUTH,Buff,nCount);
	/*Sleep(600);
	m_pAZPort->FlushRXBuffer();
	Sleep(600);*/

	//while(m_pAZPort->RXSpaceUsed() == 0);
	for(m_pAZPort->Read(Buff,500);!strstr(Buff,"K");
			m_pAZPort->Read(Buff,500));

	tAZDel -= (ReadTime() - tStartTime);
	//AZProp = tAZDel/600.0+RespProp;
	AZProp = tAZDel;

	Sleep(600);
	m_pAZPort->FlushRXBuffer();

/**************************************************************************************/
	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"W1600\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"R0\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	tStartTime = ReadTime();

	sprintf(Buff,"G 0 1\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);
	Sleep(600);
	m_pELPort->FlushRXBuffer();
	Sleep(600);

	while(m_pELPort->RXSpaceUsed() == 0);

	tELDel = ReadTime() - tStartTime;
	Sleep(60);
	m_pELPort->FlushRXBuffer();

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"W1000\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"R0\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	sprintf(Buff,"E\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);

	tStartTime = ReadTime();

	sprintf(Buff,"G 0 1\r");
	nCount = strlen(Buff);
	Send(ELEVATION,Buff,nCount);
	Sleep(300);
	m_pELPort->FlushRXBuffer();
	Sleep(300);

	while(m_pELPort->RXSpaceUsed() == 0);

	tELDel -= ReadTime() - tStartTime;
	ELProp = tELDel/600.0+RespProp;

	Sleep(60);
	m_pELPort->FlushRXBuffer();

/**************************************************************************************/
	sprintf(Buff,"Calibration complited.");
	SendAntMessage(MSG_TRACE,Buff);
}

VOID CSARAntenna::CalSARMove(MOVE &AZMove,MOVE &ELMove,INT wDiraction)
{
	DOUBLE	fAZ_SLEW;
	DOUBLE	fFinal_AZ;
	DOUBLE fCompAZ_Slew;		//Complement of shortest azimuth slew

		//This caculation provides the shortest slew from current azimuth to distanation
		//azimuth.
	for(fAZ_SLEW = AZMove.End - AZMove.Start + 540.0;
			fAZ_SLEW > 360.0; fAZ_SLEW -= 360);
	fAZ_SLEW -= 180.0;

		//Calculation of the longest slew for current azimuth
	fCompAZ_Slew = 360.0 - fabs(fAZ_SLEW);
	if(fAZ_SLEW > 0.0) fCompAZ_Slew = -fCompAZ_Slew;
	
	fFinal_AZ = AZMove.Start + fAZ_SLEW;	


		//Use the long route if the antenna encounters the cable limit while moving.
	if((fFinal_AZ < m_ConfigD.m_fMin_Azimuth) && (fAZ_SLEW < 0.0) || 
		(fFinal_AZ > m_ConfigD.m_fMax_Azimuth) && (fAZ_SLEW > 0.0))
	{
		fAZ_SLEW = fCompAZ_Slew;
	}
	else if(wDiraction == m_nDummy_Arg)		//If it case of non-tracking move
	{
		if((fabs(AZMove.Start) > 180.0) || (fabs(fAZ_SLEW) > 45.0))
			if(fabs(AZMove.Start + fAZ_SLEW) > fabs(AZMove.Start + fCompAZ_Slew))
					fAZ_SLEW = fCompAZ_Slew;
	}
	else if((fFinal_AZ < -90.0) && (wDiraction == CCW))
	{
		fAZ_SLEW = fCompAZ_Slew;
		if(fAZ_SLEW < 0.0)	
			fAZ_SLEW += 720.0;
	}
	else if((fFinal_AZ > 90.0) && (wDiraction == CW))
	{
		fAZ_SLEW = fCompAZ_Slew;
		if(fAZ_SLEW > 0.0)	
			fAZ_SLEW -= 720.0;
	}

	AZMove.End = AZMove.Start + fAZ_SLEW;
	ELMove.End = ELMove.End;

	if(AZMove.End < m_ConfigD.m_fMin_Azimuth) 
		AZMove.End += 360.0;
	if(AZMove.End > m_ConfigD.m_fMax_Azimuth) 
		AZMove.End -= 360.0;

	if(ELMove.End < m_ConfigD.m_fMin_Elevation) 
		ELMove.End = m_ConfigD.m_fMin_Elevation;
	if(ELMove.End > m_ConfigD.m_fMax_Elevation) 
		ELMove.End = m_ConfigD.m_fMax_Elevation;
	
}

CSARAntenna::~CSARAntenna()
{

	list<lpAZEL_FORMAT>::iterator i; 		//list iterator number

		//delete list of vectors
	for (i = m_ReqTrackData.m_AzelRecordsList.begin(); i != 
		m_ReqTrackData.m_AzelRecordsList.end();)
	{
		delete *i;
		 ++i;
		m_ReqTrackData.m_AzelRecordsList.pop_front();
	}

	list<lpSTEP_DATA>::iterator ii; 		//list iterator number
		//delete m_TrackProfileList 
	for (ii = m_ReqTrackData.m_TrackProfileList.begin(); ii != 
		m_ReqTrackData.m_TrackProfileList.end();)
	{
		delete *ii;
		 ++ii;
		m_ReqTrackData.m_TrackProfileList.pop_front();
	}


	if(m_hFile != INVALID_HANDLE_VALUE)
		CloseHandle(m_hFile);

	if(m_pAZPort)
		delete m_pAZPort;
	if(m_pELPort)
		delete m_pELPort;

}


EMS_RESULT CSARAntenna::Send(INT nChannel,LPVOID lpData, DWORD &nCount)
{
	EMS_RESULT hr = EMS_OK;
	int	 rs232hr;
	CHAR* Buffer = (CHAR*)lpData;
//	CHAR RetChar;
	DWORD Pos = 0;
	INT Tries = 0;

		//Send the buffer to ACU. If error occur, try sending twice befor giving up.
		//or if return char is in lower case.

	for(Tries = 0; Tries < 2; Tries++,hr = EMS_OK)
	{
		if(nChannel == ELEVATION)
		{
			rs232hr = m_pELPort->Write(Buffer,nCount);
			if(rs232hr < RS232_SUCCESS)
			{
				hr = ANT_INV_ELEVATION_COMM;
				continue;
			}

			rs232hr = IdleFunction(m_pELPort);

			if(rs232hr == RS232_TIMEOUT)  //Maybe greeting mode
			{	
					//Greeting
				rs232hr = m_pELPort->Write("  \r",3);			
				Sleep(500);
				m_pELPort->FlushRXBuffer();
				continue;	//try anain
			}

			nCount = m_pELPort->RXSpaceUsed();
						
			rs232hr = m_pELPort->Read(Buffer,nCount);
			if(rs232hr < RS232_SUCCESS)
			{
				hr = ANT_INV_ELEVATION_COMM;
				continue;
			}
			else
				break;
		}
		else if(nChannel == AZIMUTH)
		{
			rs232hr = m_pAZPort->Write(Buffer,nCount);
			if(rs232hr < RS232_SUCCESS)
			{
				hr = ANT_INV_AZIMUTH_COMM;
				continue;	//Try again
			}

			rs232hr = IdleFunction(m_pAZPort);

			if(rs232hr == RS232_TIMEOUT)  //Maybe greeting mode
			{	
					//Greeting
				rs232hr = m_pAZPort->Write("  \r",3);			
				Sleep(500);
				m_pAZPort->FlushRXBuffer();
				continue;	//try anain
			}

			nCount = m_pAZPort->RXSpaceUsed();
						
			rs232hr = m_pAZPort->Read(Buffer,nCount);
			if(rs232hr < RS232_SUCCESS)
			{
				hr = ANT_INV_AZIMUTH_COMM;
				continue;
			}
			else
				break;
		}
		else
		{
			return m_hr = hr = EMS_NO_COM_PORT;
		}
	}

	if(Tries < 2)
	{
		//nCount = RetBufLength - Pos + 1;	//Dont read first char its command
		//strncpy(Buffer,RetString + Pos,RetBufLength - Pos);
		//strcpy(Buffer,RetString + Pos + 1);
		//memcpy(Buffer,RetString + Pos + 1,2);
		hr = EMS_OK;
	}
	else
	{
		CHAR msg[1024];

		if(nChannel == AZIMUTH)
		{
			m_pAZPort->FlushRXBuffer();
			sprintf(msg,"Azimuth ACU Communication packet rejected"
						"Requested: %s",Buffer);
			SendAntMessage(MSG_WARNING, msg); 
		}
		else
		{
			m_pELPort->FlushRXBuffer();
			sprintf(msg,"Elevation ACU Communication packet rejected"
						"Requested: %s",Buffer);
			SendAntMessage(MSG_WARNING, msg); 
		}
	}

	return m_hr = hr;
}

/*
EMS_RESULT CSARAntenna::Send(INT nChannel,LPVOID lpData, DWORD &nCount,
							 BOOL bEcho)
{
	EMS_RESULT hr = EMS_OK;
	int	 rs232hr;
	CHAR* Buffer = (CHAR*)lpData;
	CHAR RetChar;

	for(int count = 0; count < nCount; count++)
	{
		if(nChannel == ELEVATION)
		{
			rs232hr = m_pELPort->Write(Buffer[count]);

			if(rs232hr < RS232_SUCCESS)
				hr = ANT_INV_ELEVATION_COMM;

				//ReadIdlFunc();	//Not return til char echoed
			Sleep(100);

			rs232hr = RetChar = m_pELPort->Read();

			if(rs232hr < RS232_SUCCESS || Buffer[count] != RetChar)
				hr = ANT_INV_ELEVATION_COMM;

			if((hr != EMS_OK))
				m_pELPort->FlushRXBuffer();
			}
		else if(nChannel == AZIMUTH)
		{
			rs232hr = m_pAZPort->Write(Buffer[count]);
			if(rs232hr < RS232_SUCCESS)
				hr = ANT_INV_AZIMUTH_COMM;

				//ReadIdlFunc();
			Sleep(100);

			rs232hr = RetChar = m_pAZPort->Read();

			if(rs232hr < RS232_SUCCESS || Buffer[count] != RetChar)
				hr = ANT_INV_AZIMUTH_COMM;

			if((hr != EMS_OK))
				m_pAZPort->FlushRXBuffer();
		}
		Buffer[count] = RetChar;
	}

	if(nChannel == AZIMUTH)
	{
		m_pAZPort->Write('\n');
		Sleep(100);
		rs232hr = m_pAZPort->Read();
	}
	else
		m_pELPort->Write('\n');

	if(rs232hr < RS232_SUCCESS || hr != EMS_OK)
	{
		CHAR msg[1024];

		if(nChannel == AZIMUTH)
		{
			sprintf(msg,"Azimuth ACU Communication packet rejected"
						"Requested: %s",Buffer);
			SendAntMessage(MSG_WARNING, msg); 
		}
		else
		{
			sprintf(msg,"Elevation ACU Communication packet rejected"
						"Requested: %s",Buffer);
			SendAntMessage(MSG_WARNING, msg); 
		}
	}
	return m_hr = hr;
}
*/
EMS_RESULT CSARAntenna::Output(DWORD wRequest, DOUBLE fAZCoordinate, DOUBLE fELCoordinate)
{
	CHAR szBuffer[400];
	DOUBLE nMaxRate;
	DWORD nCount;

	EMS_RESULT hr = EMS_OK;

	if(wRequest == STNDBY || wRequest == RMT_STNDBY)
	{
/*		sprintf(szBuffer,"%c",ESC);		//ESC = '27'
		Send(AZIMUTH,szBuffer,nCount = 2);
		sprintf(szBuffer,"%c",ESC);		//ESC = '27'
		Send(ELEVATION,szBuffer,nCount = 2);*/

		for(INT Channel = AZIMUTH; Channel <= ELEVATION; Channel++)
		{
				//Halt the motor
			sprintf(szBuffer,"R0\r");
			if(hr == EMS_OK)
				if(Channel == AZIMUTH)
					hr = Send(AZIMUTH,szBuffer, nCount = 3);
				else
					hr = Send(ELEVATION,szBuffer, nCount = 3);
				//Reset slope
			if(hr == EMS_OK)
			{
				sprintf(szBuffer,"M%d\r",(INT)m_ConfigD.m_nACU_RAMP);
				nCount = strlen(szBuffer);
				if(Channel == AZIMUTH)
					hr = Send(AZIMUTH,szBuffer, nCount);
				else
					hr = Send(ELEVATION,szBuffer, nCount);
			}

				//Set start/stop velocity
			if(hr == EMS_OK)
			{
				if(Channel == AZIMUTH)
				{
					nMaxRate = m_ConfigD.m_nACU_START * m_ConfigD.m_nAZ_Divider;
					sprintf(szBuffer,"F%d\r",(INT)nMaxRate);
					nCount = strlen(szBuffer);
					hr = Send(AZIMUTH,szBuffer, nCount);
				}
				else
				{
					nMaxRate = m_ConfigD.m_nACU_START * m_ConfigD.m_nEL_Divider;
					sprintf(szBuffer,"F%d\r",(INT)nMaxRate);
					nCount = strlen(szBuffer);
					hr = Send(ELEVATION,szBuffer, nCount);
				}
				
			}

				//Set maximum velocity
			if(hr == EMS_OK)
			{
				if(Channel == AZIMUTH)
				{
					nMaxRate = m_ConfigD.m_fAZ_Rate*m_ConfigD.m_nAZ_Divider
						*m_ConfigD.m_fAZ_Factor;
					sprintf(szBuffer,"V%d\r",(INT)fabs(nMaxRate));
					nCount = strlen(szBuffer);
					hr = Send(AZIMUTH,szBuffer, nCount);
				}
				else
				{
					nMaxRate = m_ConfigD.m_fEL_Rate*m_ConfigD.m_nEL_Divider
						*m_ConfigD.m_fEL_Factor;
					sprintf(szBuffer,"V%d\r",(INT)fabs(nMaxRate));
					nCount = strlen(szBuffer);
					hr = Send(ELEVATION,szBuffer, nCount);
				}
				
			}
				//Set velocity divider
			if(hr == EMS_OK)
			{
				if(Channel == AZIMUTH)
				{
					nMaxRate = m_ConfigD.m_nAZ_Divider;
					sprintf(szBuffer,"\\%d\r",(INT)fabs(nMaxRate));
					nCount = strlen(szBuffer);
					hr = Send(AZIMUTH,szBuffer, nCount);
				}
				else
				{
					nMaxRate = m_ConfigD.m_nEL_Divider;
					sprintf(szBuffer,"\\%d\r",(INT)fabs(nMaxRate));
					nCount = strlen(szBuffer);
					hr = Send(ELEVATION,szBuffer, nCount);
				}
				
			}
		}
	}
	else if(wRequest == WRITE_AZEL)
	{
			int	 rs232hr;

			//Convert the azimuth and elevation into step count for ACUs
		DOUBLE dAZ_COORD = fAZCoordinate;
		DOUBLE dEL_COORD = fELCoordinate;

		if(dAZ_COORD < m_ConfigD.m_fMin_Azimuth) dAZ_COORD += 360.0;
		if(dAZ_COORD > m_ConfigD.m_fMax_Azimuth) dAZ_COORD -= 360.0;

		dAZ_COORD *= m_ConfigD.m_fAZ_Factor;
		sprintf(szBuffer,"@%d\r",(LONG)dAZ_COORD);
		nCount = strlen(szBuffer);
		//hr = Send(AZIMUTH,szBuffer, nCount);
		rs232hr = m_pAZPort->Write(szBuffer,nCount);

		if(dEL_COORD < m_ConfigD.m_fMin_Elevation) dEL_COORD = m_ConfigD.m_fMin_Elevation;
		if(dEL_COORD > m_ConfigD.m_fMax_Elevation) dEL_COORD = m_ConfigD.m_fMax_Elevation;

		dEL_COORD *= m_ConfigD.m_fEL_Factor;
		sprintf(szBuffer,"@%d\r",(LONG)dEL_COORD);
		nCount = strlen(szBuffer);
		//hr = Send(ELEVATION,szBuffer, nCount);
		rs232hr = m_pELPort->Write(szBuffer,nCount);
		
		Sleep(200);
	}
	else if(wRequest == RATE_AZEL)
	{
			//Convert the azimuth and elevation into rates in steps for ACUs
		DOUBLE dAZ_COORD = fAZCoordinate*m_ConfigD.m_fAZ_Factor*m_ConfigD.m_nAZ_Divider;
		DOUBLE dEL_COORD = fELCoordinate*m_ConfigD.m_fEL_Factor*m_ConfigD.m_nEL_Divider;

			//Format the rate command string to send to the azimuth ACU
		if(fAZCoordinate < m_ConfigD.m_fAZ_Rate)
		{
			sprintf(szBuffer,"R%d\r",dAZ_COORD);
			nCount = strlen(szBuffer);
			hr = Send(AZIMUTH,szBuffer, nCount);
		}
			//Format the rate command string to send to the elevation ACU
		if(fELCoordinate < m_ConfigD.m_fEL_Rate)
		{
			sprintf(szBuffer,"R%d\r",dEL_COORD);
			nCount = strlen(szBuffer);
			hr = Send(ELEVATION,szBuffer, nCount);
		}
	}


	return m_hr;
}

void CSARAntenna::SendAntMessage(CHAR mgType, LPTSTR szText)
{
	switch(mgType)
	{
	case MSG_LOG:			m_DispMsgStr << "Log Message: ";
							break;
	case MSG_TRACE:			m_DispMsgStr << "Trace Message: ";
							break;
	case MSG_ERROR:			m_DispMsgStr << "Error Message: ";
							break;
	case MSG_WARNING:		m_DispMsgStr << "Warning Message: ";
							break;
	case MSG_ALARM:			m_DispMsgStr << "Alarm Message: ";
							break;
	case MSG_DEBUG:			m_DispMsgStr << "Debug Message: ";
							break;
	case MSG_INFORMATION:	m_DispMsgStr << "Information Message: ";
							break;
	}


	m_DispMsgStr << szText << "\n";

	MsgNotify();
}

#define		HOMING_TRIES	3

EMS_RESULT CSARAntenna::Home()
{
	static INT	nHomingCount;		//It counts how many times antenna homed in one request,
	EMS_RESULT	hr = EMS_OK;		//Start with no errors
	DOUBLE		dComSpeed;			//Computed speed in each axis
	DOUBLE		dLowSpeedAZ;		//Low homing speeds for azimuth
	DOUBLE		dHiSpeedAZ;			//High homing speeds for azimuth
	DOUBLE		dLowSpeedEL;		//Low homing speeds for elevation
	DOUBLE		dHiSpeedEL;			//High homming speeds for elevation
	DOUBLE		dPreviousAZ;
	DOUBLE		dPreviousEL;
	DWORD		nCount;

	BOOL		bLoopBack;
	BOOL		bAZHomeStop;		//Azimuth at home flag
	BOOL		bELHomeStop;		//Elevation at home flag
	BOOL		bHomeFault;			//Home fault condition flag
	BOOL		bDone;

	DOUBLE		tStartTime;			//Time counter
	DOUBLE		tTimeOut;			//Time out period for antenna motion
	DOUBLE		tElepsedTime = 0;	//Elepsed time
	CHAR		szBuffer[256];
	string		SPEED_STRING;

	SendAntMessage(MSG_LOG,"Homing antenna");

		//wsprintf( szDebug, "Homing antenna");
		//debugWin.OutputMsg( szDebug );

	bHomeFault = FALSE;

		//Calculate the speed for the fast and slow moves
	dComSpeed = fabs(m_ConfigD.m_fAZ_Rate * m_ConfigD.m_nAZ_Divider * m_ConfigD.m_fAZ_Factor);
	dLowSpeedAZ = dComSpeed * m_ConfigD.m_fSlowRate;
	dHiSpeedAZ = dComSpeed * m_ConfigD.m_fFast_Rate;

	dComSpeed = fabs(m_ConfigD.m_fEL_Rate * m_ConfigD.m_nEL_Divider * m_ConfigD.m_fEL_Factor);
	dLowSpeedEL = dComSpeed * m_ConfigD.m_fSlowRate;
	dHiSpeedEL = dComSpeed * m_ConfigD.m_fFast_Rate;

		//Calculate time out for initial(fast) move to the home position. Allow a max
		//distance of 270 degrees for azimus.
	tTimeOut = ((270.0/m_ConfigD.m_fAZ_Rate + m_ConfigD.m_fRamp_AZ)/m_ConfigD.m_fFast_Rate)
		 + m_ConfigD.m_fFastTime;


	for(INT Channel = AZIMUTH;Channel <= ELEVATION; Channel++)
	{
			//Set the divider
		if(hr == EMS_OK)
			if(Channel == AZIMUTH)
			{
				sprintf(szBuffer,"\\%d\r",(LONG)m_ConfigD.m_nAZ_Divider);
				nCount = strlen(szBuffer);
				hr = Send(AZIMUTH,szBuffer,nCount);
			}
			else
			{
				sprintf(szBuffer,"\\%d\r",(LONG)m_ConfigD.m_nEL_Divider);
				nCount = strlen(szBuffer);
				hr = Send(ELEVATION,szBuffer,nCount);
			}
			//Set the ramp time to spread out the acceleration
		if(hr == EMS_OK)
		{
			sprintf(szBuffer,"M%d\r",(LONG)m_ConfigD.m_nACU_RAMP);
			nCount = strlen(szBuffer);
			if(Channel == AZIMUTH)	
				hr = Send(AZIMUTH,szBuffer,nCount);
			else
				hr = Send(ELEVATION,szBuffer,nCount);
		}
			//Set the initial velocity
		if(hr == EMS_OK)
			if(Channel == AZIMUTH)
			{
				sprintf(szBuffer,"F%d\r",(LONG)(m_ConfigD.m_nACU_START*m_ConfigD.m_nAZ_Divider));
				nCount = strlen(szBuffer);
				hr = Send(AZIMUTH,szBuffer,nCount);
			}
			else
			{
				sprintf(szBuffer,"F%d\r",(LONG)(m_ConfigD.m_nACU_START*m_ConfigD.m_nEL_Divider));
				nCount = strlen(szBuffer);
				hr = Send(ELEVATION,szBuffer,nCount);
			}
				//Set the maximum velocity
		if(hr == EMS_OK)
			if(Channel == AZIMUTH)
			{
				sprintf(szBuffer,"V%d\r",(LONG)dHiSpeedAZ);
				nCount = strlen(szBuffer);
				hr = Send(AZIMUTH,szBuffer,nCount);
			}
			else
			{
				sprintf(szBuffer,"V%d\r",(LONG)dHiSpeedEL);
				nCount = strlen(szBuffer);
				hr = Send(ELEVATION,szBuffer,nCount);
			}
	}

	SendAntMessage(MSG_LOG, "Starting SARAntenna Homing Algorithm.");

		//wsprintf( szDebug, "Starting SARAntenna Homing Algorithm.");
		//debugWin.OutputMsg( szDebug );

		//Move antenna to home position as fast rate and then again at slow rate
		//and try homing as many times as HOMING_TRIES saies.
	for(INT nSpeed = HiSpeed;nSpeed < HOMING_TRIES; nSpeed++)
	{
		//Set up monitor loop control parameters
		bLoopBack = FALSE;
		tStartTime = ReadTime();	
		DWORD		nCount;

		INT		nAZResult,nELResult;
		DWORD	dCurSpeed;
		INT		iAZStartHome,iELStartHome;


		bELHomeStop =	FALSE;	
		bAZHomeStop =	FALSE;	


		wsprintf( szBuffer, "Homing trie No %d",nSpeed);
		SendAntMessage(MSG_LOG, szBuffer );


			//Get the original status of the buffer

		for(INT Channel = AZIMUTH;Channel <= ELEVATION; Channel++)
		{
			 //Final speed zero, in case of rong(default) diraction decisen,
			sprintf(szBuffer,"R0\r");

			if(Channel == AZIMUTH)
			{
					//Decide about Azimuth speed
				switch(nSpeed)
				{
				case HiSpeed:	dCurSpeed = dHiSpeedAZ; break;
				case LowSpeed:	dCurSpeed = dLowSpeedAZ; break;
				default:		dCurSpeed = dLowSpeedAZ / (DOUBLE)nSpeed;
				}

					//Get Azimuth status
				nAZResult = (nAZResult = ReadIoStatus(Channel)) & 0x07;

				iAZStartHome = nAZResult & 0x01;

					//Decide Azimuth diraction
				switch(nAZResult)
				{
				case 1:
				case 5:	sprintf(szBuffer,"R%d\r",dCurSpeed); break;
				case 0:
				case 2: sprintf(szBuffer,"R%d\r",-dCurSpeed); break;
				default: 
					SendAntMessage(MSG_ALARM,"For Azimuth can't decide Home diraction"); 
				}
				nCount = strlen(szBuffer);
				hr = Send(AZIMUTH,szBuffer,nCount);		//Azimuth Move
			}
			else
			{
					//Decide about Elevation speed
				switch(nSpeed)
				{
				case HiSpeed:	dCurSpeed = dHiSpeedEL; break;
				case LowSpeed:	dCurSpeed = dLowSpeedEL; break;
				default:		dCurSpeed = dLowSpeedEL / (DOUBLE)nSpeed;
				}

					//Get Elevation status
				nELResult = (nELResult = ReadIoStatus(Channel)) & 0x07;

				iELStartHome = nELResult & 0x01;

					//Decide Elevation diraction
				switch(nELResult)
				{
				case 0:
				case 2: sprintf(szBuffer,"R%d\r",-dCurSpeed); break;
				case 1:
				case 5: sprintf(szBuffer,"R%d\r",dCurSpeed); break;
				default: 
					SendAntMessage(MSG_ALARM,"For Elevation can't decide Home diraction");
				}
				nCount = strlen(szBuffer);
				hr = Send(ELEVATION,szBuffer,nCount);	//Elevation Move
			}
			Sleep(100);
		}
	

			//Wait til the antenna changes sector or stop it after timed out
		while(!bLoopBack)
		{

			if(m_bSHUT_DOWN)
			{
				SendAntMessage(MSG_INFORMATION,
					"Homing request stopped by Stop request");
				sprintf(szBuffer,"s\r");
				Send(AZIMUTH,szBuffer,nCount = 2);
				Send(ELEVATION,szBuffer,nCount = 2);
				Output(STNDBY,0,0);
				return m_hr = hr;
			}


			for(INT Channel = AZIMUTH;Channel <= ELEVATION; Channel++)
			{
				if(Channel == AZIMUTH)
				{
						//Get Azimuth status
					nAZResult = (nAZResult = ReadIoStatus(Channel)) & 0x07;
					if((nAZResult & 0x01) != iAZStartHome)
					{
						sprintf(szBuffer,"R0\r");	//Stop Azimuth motor
						hr = Send(AZIMUTH,szBuffer,nCount = 3);
						bAZHomeStop = TRUE;
					}
				}
				else
				{
						//Get Elevation status
					nELResult = (nELResult = ReadIoStatus(Channel)) & 0x07;
					if((nELResult & 0x01) != iELStartHome)
					{
						sprintf(szBuffer,"R0\r");	//Stop Azimuth motor
						hr = Send(ELEVATION,szBuffer,nCount = 3);
						bELHomeStop = TRUE;
					}
				}
			}

			tElepsedTime = (tStartTime - ReadTime())/1000.0;

				//Set timer on loop back if required
			if(bAZHomeStop && bELHomeStop)
				bLoopBack = TRUE;
			else
			{
				if(tElepsedTime > tTimeOut)
				{
					bHomeFault = TRUE;
					if(nSpeed == HiSpeed)
						SPEED_STRING = "fast";
					else
						SPEED_STRING = "slow";

					string str;
					if(!bAZHomeStop)
					{
						str = "Time-out" + SPEED_STRING +
														"searching for azimuth home position";
						SendAntMessage(MSG_INFORMATION,(char*)str.c_str());

		//wsprintf( szDebug, "Homing trie No %d",nSpeed);
		//debugWin.OutputMsg( (char*)str.c_str() );

					}
					if(!bELHomeStop)
					{
						str = "Time-out" + SPEED_STRING +
														"searching for elevation home position";
						SendAntMessage(MSG_INFORMATION,(char*)str.c_str());

		//wsprintf( szDebug, "Homing trie No %d",nSpeed);
		//debugWin.OutputMsg( (char*)str.c_str() );

					}
				}
				Sleep(100);		//Sleep 600 mily seconds
			}
		}
			//The time for low speed homing includes the times for:
			//the program to detect that the antenna has passed home the high speed homing
			// to decelerate to a halt and  a base time for safety
		//tTimeOut = m_ConfigD.m_fSlowTime + m_ConfigD.m_fFast_Rate/m_ConfigD.m_fSlowRate *
				//(tElepsedTime + m_ConfigD.m_fRamp_AZ/2.0); 
	}

//=============================================================================================
	SendAntMessage(MSG_LOG, "Wait til the antenna does not move anymore.");

		//wsprintf( szDebug, "Wait til the antenna does not move anymore.");
		//debugWin.OutputMsg( szDebug );

		//Wait til the antenna does not move anymore 
	hr = GetStatus();
	dPreviousAZ = m_AntStatus.m_dwAZinSteps;
	dPreviousEL = m_AntStatus.m_dwELinSteps;
		//Get Current time
	tStartTime = ReadTime();
	bDone = bHomeFault;
	while(!bDone)
	{
		if(m_bSHUT_DOWN)
		{
			SendAntMessage(MSG_INFORMATION,"Homing request stopped by Stop request");
			sprintf(szBuffer,"s\r");
			Send(AZIMUTH,szBuffer,nCount = 2);
			Send(ELEVATION,szBuffer,nCount = 2);
			Output(STNDBY,0,0);
			return m_hr = hr;
		}
		hr = GetStatus();
		if(m_AntStatus.m_dwAZinSteps == dPreviousAZ && 
			m_AntStatus.m_dwELinSteps == dPreviousEL)
				bDone = TRUE;
		else
		{
			dPreviousAZ = m_AntStatus.m_dwAZinSteps;
			dPreviousEL = m_AntStatus.m_dwELinSteps;

			tElepsedTime = (ReadTime() - tStartTime)/1000;

			if(tElepsedTime > 2.0)
			{
				bHomeFault = TRUE;
				SendAntMessage(MSG_INFORMATION,"Trouble stopping antenna after homing.");
				bDone = TRUE;
					//Stop motors
				sprintf(szBuffer,"R0\r");
				hr = Send(AZIMUTH,szBuffer,nCount = 3);
				hr = Send(ELEVATION,szBuffer,nCount = 3);
				//Sleep(2000);		//Sleep 2 seconds

				//Try recurcivit homing twis if til moving diclar ANT_CANT_STOP_ANTENNA
				if(hr == EMS_OK && nHomingCount++ < 2)	//Recurtion stop & progration 
				{										//condition
					sprintf(szBuffer,"Try homing again %dth time.",nHomingCount);
					SendAntMessage(MSG_INFORMATION,szBuffer);

		wsprintf( szBuffer, "Try homing again %dth time.",nHomingCount);
		SendAntMessage(MSG_LOG, szBuffer );

					m_hr = Home();
					nHomingCount = 0;
					return m_hr;
				}
				else
					if(hr == EMS_OK)
						return ANT_CANT_STOP_ANTENNA;
			}
		}
		Sleep(600);
	}
	SendAntMessage(MSG_LOG, "Started Index Driver Home Search Algorithm.");

		//wsprintf( szDebug, "Started Index Driver Home Search Algorithm.");
		//debugWin.OutputMsg( szDebug );


		//Send the home command to ACU if til OK.
	if(hr == EMS_OK)
	{
		sprintf(szBuffer,"H 255 0\r");
		for(INT Channel = AZIMUTH;Channel <= ELEVATION; Channel++)
		{
				hr = Send(Channel,szBuffer,nCount = 8);	
		}
	

		//Wait til the antenna does not move anymore
		bAZHomeStop =	FALSE;
		bELHomeStop =	FALSE;

		hr = GetStatus();
		dPreviousAZ = m_AntStatus.m_dwAZinSteps;
		dPreviousEL = m_AntStatus.m_dwELinSteps;
		//Get Current time
		tStartTime = ReadTime();
		bDone = FALSE;

		while(!bDone)
		{
			if(m_bSHUT_DOWN)
			{
				SendAntMessage(MSG_INFORMATION,"Homing request stopped by Stop request");
				Output(STNDBY,0,0);
				return m_hr = hr;
			}

			GetStatus();
			bAZHomeStop = m_AntStatus.m_dwAZinSteps == dPreviousAZ; 
			bELHomeStop = m_AntStatus.m_dwELinSteps == dPreviousEL;
			if(bAZHomeStop && bELHomeStop)
				bDone = TRUE;
			else
			{
				dPreviousAZ = m_AntStatus.m_dwAZinSteps;
				dPreviousEL = m_AntStatus.m_dwELinSteps;

				tElepsedTime = (ReadTime() - tStartTime)/1000.0;

				if(tElepsedTime > 90.0)
				{
					bHomeFault = TRUE;
					m_hr = hr = ANT_HOME_FAULT;
					if(!bAZHomeStop)
					{
						SendAntMessage(MSG_INFORMATION,"Azemuth ACU home command timed-out");

		//wsprintf( szDebug, "Azemuth ACU home command timed-out");
		//debugWin.OutputMsg( szDebug );

					}
					if(!bELHomeStop)
					{
						SendAntMessage(MSG_INFORMATION,"Elevation ACU home command timed-out");

		//wsprintf( szDebug, "Elevation ACU home command timed-out");
		//debugWin.OutputMsg( szDebug );

					}
					bDone = TRUE;
					sprintf(szBuffer,"R0\r");
					hr = Send(AZIMUTH,szBuffer,nCount = 3);
					hr = Send(ELEVATION,szBuffer,nCount = 3);
					//Sleep(2000);		//Sleep 2 seconds
				}
				//m_pAZPort->IdleFunction();	//Run Azimuth idle function
				//m_pELPort->IdleFunction();	//Run Elevation idle function
				//LocNotify(m_DispAZ, m_DispEL);
				//ErrLocNotify(m_ErrorDispAZ,m_ErrorDispEL);
				Sleep(600);
			}
		}
		//Sleep(1500);
	}
	SendAntMessage(MSG_LOG, "Reset the parameters ACU counters.");
			//Reset the parameters ACU counters if til OK

		//wsprintf( szDebug, "Reset the parameters ACU counters.");
		//debugWin.OutputMsg( szDebug );

		Sleep(1000);

		sprintf(szBuffer,"%c\r",ESC);		//ESC = '27'
		Send(AZIMUTH,szBuffer,nCount = 2);
		sprintf(szBuffer,"%c\r",ESC);		//ESC = '27'
		Send(ELEVATION,szBuffer,nCount = 2);

	if(hr == EMS_OK)
	{
		GetStatus();
		for(Channel = AZIMUTH;Channel <= ELEVATION; Channel++)
		{
			if(!bHomeFault)
			{
				if(Channel == AZIMUTH)
				{
					sprintf(szBuffer,"Z%d",
						(INT)(((m_ConfigD.m_fAZ_Offset*m_ConfigD.m_fAZ_Factor) - 
						m_AntStatus.m_dwAZinSteps)/m_ConfigD.m_fAZ_Factor));
					string str = "Home azimuth offset: ";
					str += szBuffer;
					SendAntMessage(MSG_LOG,(char*)str.c_str());
					//Sleep(100);
					sprintf(szBuffer,"Z%d\r",(INT)(m_ConfigD.m_fAZ_Offset*
						m_ConfigD.m_fAZ_Factor));
					nCount = strlen(szBuffer);
					hr = Send(Channel,szBuffer,nCount);
				}
				else

				{
					sprintf(szBuffer,"Z%d",
						(INT)(((m_ConfigD.m_fEL_Offset*m_ConfigD.m_fEL_Factor) -
						m_AntStatus.m_dwELinSteps)/m_ConfigD.m_fEL_Factor));
					string str = "Home alevation offset: ";
					str += szBuffer;
					SendAntMessage(MSG_LOG,(char*)str.c_str());
					//Sleep(100);
					sprintf(szBuffer,"Z%d\r",(INT)(m_ConfigD.m_fEL_Offset*
						m_ConfigD.m_fEL_Factor));
					nCount = strlen(szBuffer);
					hr = Send(Channel,szBuffer,nCount);
				}
				/*sprintf(szBuffer,"Z0\r");
				nCount = strlen(szBuffer);
				hr = Send(Channel,szBuffer,nCount);*/
			}
		}
	}

	if(/*hr = EMS_OK && */!bHomeFault)
		SendAntMessage(MSG_LOG,"Successed homing antenna.");

		//wsprintf( szDebug, "Successed homing antenna.");
		//debugWin.OutputMsg( szDebug );


	return m_hr = hr;

}


	//It reads the antenna's status from the ACU's and stores the information 
	//in the status structure block m_AntStatus.
EMS_RESULT CSARAntenna::GetStatus()
{
	EMS_RESULT hr = EMS_OK;
	CHAR szBuffer[40];
	CHAR seps[] = " ";
	CHAR* token;
	DWORD nCount;
	LONG Position;
	//DWORD nPos = 0;
//	DOUBLE dwACU_DATA;

	INT		nAZResult, nELResult;

		//Initialize some parameters
	m_AntStatus.m_fAzimuth = 0.0;
	m_AntStatus.m_fElevation = 0.0;
	m_AntStatus.m_dwELinSteps = 0;
	m_AntStatus.m_dwAZinSteps = 0;
		
		//Get status from azimuth ACU
	nAZResult = (nAZResult = ReadIoStatus(AZIMUTH)) & 0x07;

	m_AntStatus.m_bCWSector = (nAZResult & 0x01) == 1;	
	m_AntStatus.m_bCWLimit = (nAZResult & 0x04) == 4;	
	m_AntStatus.m_bCCWLimit = (nAZResult & 0x02) == 2;	

		//Get the status from elevation ACU
	nELResult = (nELResult = ReadIoStatus(ELEVATION)) & 0x07;

	m_AntStatus.m_bLOWLimit = (nELResult & 0x04) == 4;
	m_AntStatus.m_bHIGHLimit = (nELResult & 0x02) == 2;
		
		//Issue a read position command to azimuth ACU
	strcpy(szBuffer,"Q1\r");
	hr = Send(AZIMUTH,szBuffer,nCount = 7);

	token = strtok(szBuffer,seps);
	token = strtok(NULL,seps);
	Position = atol(token);
	m_AntStatus.m_dwAZinSteps = Position;
	m_AntStatus.m_fAzimuth = Position/m_ConfigD.m_fAZ_Factor;

		//Issue a read position command to elevation ACU
	strcpy(szBuffer,"Q1\r");
	hr = Send(ELEVATION,szBuffer,nCount = 7);

	token = strtok(szBuffer,seps);
	token = strtok(NULL,seps);
	Position = atol(token);
	m_AntStatus.m_dwELinSteps = Position;
	m_AntStatus.m_fElevation = Position/m_ConfigD.m_fEL_Factor;
	
	return hr;
}


	//It calculates the azimuth and elevation of the antenna at a given time in 
	//the slew sequence.The acceleration and max velocity is taken into considaration
	//for determining the position of antenna.
void CSARAntenna::MoveProfile(DOUBLE SlewCurTime)
{
	//Profile generation
	//Calculate position at current instant based on the following:
	//		1) Linear acceleration.   ***************
	//		2) Constant velocity     *       2       *  RATE (v)
	//		3) Linear deceleration	* 1             3 *
	//												 RAMP (t)

	DOUBLE dRate;				//Full slew rate
	DOUBLE dDeccelSlew;			//Slew during deceleration.
	DOUBLE dAccel;				//Axis acceleration rate
	DOUBLE dAccelSlew;			//Max distance slewed in acceleration

	DOUBLE tFullSlew;			//Time at which full slew ends
	DOUBLE tSlewTime;			//Total slew time
	DOUBLE tAZ_TIME,tEL_TIME;	//Current slew time 
	DOUBLE tFullSlewTime;		//Elapsed time in full slew
	DOUBLE tBrakeTime;			//Elapsed time in deceleration

		//If the slew is to be counter-clockwise, then use a negative slew rate
	if(m_Prifile.m_fDeltaAZ < 0)
		dRate = -m_ConfigD.m_fAZ_Rate;
	else
		dRate = m_ConfigD.m_fAZ_Rate;

		//Work-out a few constants used for the profile generation.
	dAccel = dRate/m_ConfigD.m_fRamp_AZ;		//Acces acceleration rate

					//Max distance slewed in acceleration. State 1
	dAccelSlew = 0.5*dAccel*pow(m_Prifile.m_ptStartStopTimeAZ,2.0);

					//Time at which full slew ends. State 2
	tFullSlew = m_Prifile.m_ptStartStopTimeAZ+m_Prifile.m_ptAZ_FullSlew;

					//Total slew time. State 3
	tSlewTime = 2*m_Prifile.m_ptStartStopTimeAZ+m_Prifile.m_ptAZ_FullSlew;

		//If the input time is greater than the slew time required for the move,
		//then generate the profile at the end of the slew.
	if(SlewCurTime > tSlewTime)
		tAZ_TIME = tSlewTime;			
	else
		tAZ_TIME = SlewCurTime;

	m_Prifile.m_fAngleAZ = m_Prifile.m_fInitAZ;

		//Check if position on accelaration. In state 1
	if(tAZ_TIME < m_Prifile.m_ptStartStopTimeAZ)
	{		//******************* State 1 **********************************
			//Distance travelled under acceleration
		m_Prifile.m_fAngleAZ += 0.5*dAccel*pow(tAZ_TIME,2.0);
	}
	else
	{
		m_Prifile.m_fAngleAZ += dAccelSlew;
		if(tAZ_TIME < tFullSlew)
		{		//*************** State 2 **********************************
				//Distance travelled at full slew rate
			tFullSlewTime = tAZ_TIME - m_Prifile.m_ptStartStopTimeAZ;
			m_Prifile.m_fAngleAZ += dRate*tFullSlewTime;
		}
		else
		{
			m_Prifile.m_fAngleAZ += dRate*m_Prifile.m_ptAZ_FullSlew;
			if(tAZ_TIME <= tSlewTime)
			{	//*************** State 3 *********************************
					//Distance travelled under deceleration.
				tBrakeTime = tAZ_TIME - tFullSlew;
				dDeccelSlew = dAccelSlew - 0.5*dAccel*
					pow(m_Prifile.m_ptStartStopTimeAZ - tBrakeTime,2.0);
				m_Prifile.m_fAngleAZ += dDeccelSlew;
			}
		}
	}




		//If the slew is to be counter-clockwise, then use a negative slew rate
	if(m_Prifile.m_fDeltaEL < 0)
		dRate = -m_ConfigD.m_fEL_Rate;
	else
		dRate = m_ConfigD.m_fEL_Rate;

		//Work-out a few constants used for the profile generation.
	dAccel = dRate/m_ConfigD.m_fRamp_EL;		//Acces acceleration rate

					//Max distance slewed in acceleration.
	dAccelSlew = 0.5*dAccel*pow(m_Prifile.m_ptStartStopTimeEL,2.0);

					//Time at which full slew ends
	tFullSlew = m_Prifile.m_ptStartStopTimeEL+m_Prifile.m_ptEL_FullSlew;

					//Total slew time
	tSlewTime = 2*m_Prifile.m_ptStartStopTimeEL+m_Prifile.m_ptEL_FullSlew;

		//If the input time is greater than the slew time required for the move,
		//then generate the profile at the end of the slew.
	if(SlewCurTime > tSlewTime)
		tEL_TIME = tSlewTime;			
	else
		tEL_TIME = SlewCurTime;

	m_Prifile.m_fAngleEL = m_Prifile.m_fInitEL;
	if(tEL_TIME < m_Prifile.m_ptStartStopTimeEL)
	{	
			//Distance travelled under acceleration
		m_Prifile.m_fAngleEL += 0.5*dAccel*pow(tEL_TIME,2.0);
	}
	else
	{
			//Full slew
		m_Prifile.m_fAngleEL += dAccelSlew;
		if(tEL_TIME < tFullSlew)
		{
				//Distance travelled at full slew rate
			tFullSlewTime = tEL_TIME - m_Prifile.m_ptStartStopTimeEL;
			m_Prifile.m_fAngleEL += dRate*tFullSlewTime;
		}
		else
		{
			m_Prifile.m_fAngleEL += dRate*m_Prifile.m_ptEL_FullSlew;
			if(tEL_TIME <= tSlewTime)
			{
					//Distance travelled under deceleration.
				tBrakeTime = tEL_TIME - tFullSlew;
				dDeccelSlew = dAccelSlew - 0.5*dAccel*
					pow(m_Prifile.m_ptStartStopTimeEL - tBrakeTime,2.0);
				m_Prifile.m_fAngleEL += dDeccelSlew;
			}
		}
	}

		//Limit the azimuth and elevation to the limits specified in the configuration file.
	if(m_Prifile.m_fAngleAZ < m_ConfigD.m_fMin_Azimuth)
		m_Prifile.m_fAngleAZ = m_ConfigD.m_fMin_Azimuth;
	if(m_Prifile.m_fAngleAZ > m_ConfigD.m_fMax_Azimuth)
		m_Prifile.m_fAngleAZ = m_ConfigD.m_fMax_Azimuth;

	if(m_Prifile.m_fAngleEL < m_ConfigD.m_fMin_Elevation)
		m_Prifile.m_fAngleEL = m_ConfigD.m_fMin_Elevation;
	if(m_Prifile.m_fAngleEL > m_ConfigD.m_fMax_Elevation)
		m_Prifile.m_fAngleEL = m_ConfigD.m_fMax_Elevation;

}

		//It calculats the position of the antenna at the specified time within the
		//setellite pass
void CSARAntenna::PassAngles(DOUBLE tTime,DOUBLE& dAzimuth,DOUBLE& dElevation)
{
	DOUBLE			dEast;					//East coordinate (Km)
	DOUBLE			dNorth;					//North coordinate (Km)
	DOUBLE			dUp;					//Up coordinate (Km)
	INT				dwRecNum;				//Index of record in AZEL list
	INT				dwn;
	LONG			dwIntervals;			//Namber of intervals
	DOUBLE			dFraction;				//Fraction of interval between records
	lpAZEL_FORMAT	lpCurrRec;				//Current record
	lpAZEL_FORMAT	lpNextRec;				//Next record
	list<lpAZEL_FORMAT>::iterator i; 		//list iterator number


		//Determine which record to use be resived time
	if(tTime > m_TrackData.m_AzelEnd)
		dwRecNum = m_TrackData.m_Records;
	else
	{
		dwRecNum = (tTime - m_TrackData.m_AzelStart)/
			(DOUBLE)m_TrackData.m_AzelInterval;// - 1.0;
		if(dwRecNum < 0)
			dwRecNum = 0;//=1
		else
			if(dwRecNum > m_TrackData.m_Records)
				dwRecNum = m_TrackData.m_Records;
	}


	for(dwn = dwRecNum, i =m_TrackData.m_AzelRecordsList.begin(); dwn; dwn--,++i);
	lpCurrRec = *(i);

		//If the time is earlier than the the antenna start time, return the azimuth
		//and elevation for the first record. If the time is later than the time for the
		//last record in the file, return the azimuth and elevation for the last record.
	if(tTime >= m_TrackData.m_AzelStart || 
		(dwRecNum == m_TrackData.m_Records))
	{
		dEast = lpCurrRec->m_East;
		dNorth = lpCurrRec->m_North;
		dUp = lpCurrRec->m_Up;
	}
	else	//OK midel of the AZEL file
	{
			//Calculate interval time and interpolate ENU coordinates
		lpNextRec = *(++i);	//Get next record
		dwIntervals = dwRecNum - 1;
		dFraction = (tTime -(DOUBLE)dwIntervals*m_TrackData.m_AzelInterval - 
			m_TrackData.m_AzelStart)/m_TrackData.m_AzelInterval;
		dEast = lpCurrRec->m_East + dFraction*(lpNextRec->m_East - lpCurrRec->m_East);
		dNorth = lpCurrRec->m_North + dFraction*(lpNextRec->m_North - lpCurrRec->m_North);
		dUp = lpCurrRec->m_Up + dFraction*(lpNextRec->m_Up - lpCurrRec->m_Up);
	}

		//Convert from ENU coordinates to antenna azimuth and elevation
	dAzimuth = atan2(dEast,dNorth)*180.0/Pi;
	dElevation = atan2(dUp,sqrt(pow(dEast,2.0)+pow(dNorth,2.0)))*180/Pi;
/*
	if(dAzimuth < m_ConfigD.m_fMin_Azimuth) 
		dAzimuth += 360.0;
	if(dAzimuth > m_ConfigD.m_fMax_Azimuth) 
		dAzimuth -= 360.0;

	if(dElevation < m_ConfigD.m_fMin_Elevation) 
		dElevation = m_ConfigD.m_fMin_Elevation;
	if(dElevation > m_ConfigD.m_fMax_Elevation) 
		dElevation = m_ConfigD.m_fMax_Elevation;

	if((dEast < 0.0) && (dNorth < 0.0))
		dAzimuth += 360.0;
	if((dEast < 0.0) && (dNorth > 0.0))
		dAzimuth += 360.0;
*/
	if((dEast < 0.0) && (dNorth < 0.0) || (dEast < 0.0) && (dNorth > 0.0))
		dAzimuth += 360.0;
}

	//It checks if the antenna's motion is within the beam width
EMS_RESULT	CSARAntenna::CheckMotion()
{
	EMS_RESULT			hr = EMS_FALSE;		//Antenna OK
	DOUBLE				fHalfBeam;			//Half of the beam width
	DOUBLE				fCurrAZ;			//Current azimuth where antenna should be now
	DOUBLE				fCurrEL;			//Current elevetion where antenna should be now
	DOUBLE				fAZDiff;			//Error position in azimuth
	DOUBLE				fELDiff;			//Error position in elevation
	char				MSGstr[1024];

		//Calculate half sixe of beam width
	fHalfBeam = m_ConfigD.m_fBeam_Width/2;

		//Allow up to three tries before declaring the antenna fault
	for(INT nCount = 0;hr == EMS_FALSE && nCount < 3; nCount++)
	{
		hr = EMS_OK;

			//Find the expected position of the setellite
		PassAngles(ReadTime(),fCurrAZ,fCurrEL);
			//Get the actual antenna position
		hr = GetStatus();

			//Make sure the antenna azimuth is within the beam width
		fAZDiff = DMOD(m_AntStatus.m_fAzimuth - fCurrAZ + 540.0,360.0) - 180.0;
			//Calculate influence on antenna beam the fAZDiff has.
		fAZDiff = fAZDiff*cos(m_AntStatus.m_fElevation);
		if(fabs(fAZDiff) > fHalfBeam)
		{
			sprintf(MSGstr,"Antenna azimuth    %d\n"
						   "Expected position: %d\n",m_AntStatus.m_fAzimuth,fCurrAZ);
			SendAntMessage(MSG_INFORMATION,MSGstr);
			hr = ANT_INV_BEAMWIDTH;
		}

			//Ensure the antenna elevation is within the beam width
		fELDiff = m_AntStatus.m_fElevation - fCurrEL;
		if(fabs(fELDiff) > fHalfBeam)
		{
			sprintf(MSGstr,"Antenna elevation  %d\n"
						   "Expected position: %d\n",m_AntStatus.m_fElevation,fCurrEL);
			SendAntMessage(MSG_INFORMATION,MSGstr);
			hr = ANT_INV_BEAMWIDTH;
		}
	}

	if(hr != EMS_OK)
	{
		if(m_AntStatus.m_bCWLimit)
			SendAntMessage(MSG_WARNING,"Antenna at Clockwise limit zone");
		else
			if(m_AntStatus.m_bCCWLimit)
				SendAntMessage(MSG_WARNING,"Antenna at Counter Clockwise limit zone");
			else
				if(m_AntStatus.m_bHIGHLimit)
					SendAntMessage(MSG_WARNING, "Antenna at High elevation limit zone");
				else
					if(m_AntStatus.m_bLOWLimit)
						SendAntMessage(MSG_WARNING,"Antenna at low elevation limit zone");
	}
	return hr;

}


	//It ensures that the antenna azimuth and elevation are within the beamwidth
EMS_RESULT	CSARAntenna::Locate(DOUBLE& fAZ, DOUBLE& fEL)
{
	EMS_RESULT			hr = EMS_OK;		//Antenna OK
	INT					nMaxRetry = 0;		//Max number of retry
	INT					nRetryCount = 0;	//Number of retries so far
	BOOL				bRetryFlag = TRUE;
	DOUBLE				dHalfBeam;			//Half of beam width in degree
	DOUBLE				dAZ_DIFF;			//Differentce in azimuth
	DOUBLE				dEL_DIFF;			//Diffirance in elevation
//	CHAR				szBuffer[256];

	dHalfBeam = m_ConfigD.m_fBeam_Width/2.0;

	LocNotify(fAZ,fEL);

		//Get status of antenna and ACU being used if the if Antenna still OK.
		//Assume that the antenna is within permitted range
	while(bRetryFlag)
	{
		GetStatus();
		hr = EMS_OK;

			//Make sure the antenna azimuth is within the beam width.
		for(dAZ_DIFF = m_AntStatus.m_fAzimuth - fAZ + 540.0; dAZ_DIFF > 360.0;
			dAZ_DIFF -= 360.0);
			dAZ_DIFF -= 180;

			//Calculate ABS dAZ_DIFF value;
		if(fabs(dAZ_DIFF) > dHalfBeam)
		{
			/*sprintf(szBuffer,
				"Azimuth out of beam width Err = %f %f",
				dAZ_DIFF,dEL_DIFF);
			SendAntMessage(MSG_INFORMATION,szBuffer);*/
			hr = ANT_INV_BEAMWIDTH;
		}

			//Make sure the antenna elevation is within the beam width.
		dEL_DIFF = m_AntStatus.m_fElevation - fEL;


		if(fabs(dEL_DIFF) > dHalfBeam)
		{
			/*sprintf(szBuffer,
				"Elevation out of beam width Err = %f %f",
				dAZ_DIFF,dEL_DIFF);
			SendAntMessage(MSG_INFORMATION,szBuffer);*/
			hr = ANT_INV_BEAMWIDTH;
		}

		ErrLocNotify(dAZ_DIFF,dEL_DIFF);

		if(hr != EMS_OK)
		{
			//hr = Purge();
			nRetryCount++;
			bRetryFlag = nRetryCount <= nMaxRetry;
		}
		else
		{
			bRetryFlag = FALSE;
		}
	}

	return hr;

}

EMS_RESULT CSARAntenna::Purge()
{
	int				    er;
	EMS_RESULT			hr = EMS_OK;		//Antenna OK

	er = m_pAZPort->FlushRXBuffer();
	if(er < RS232_SUCCESS)
		return hr = EMS_AZ_RX_FLUSH_ERROR;

	er = m_pAZPort->FlushTXBuffer();
	if(er < RS232_SUCCESS)
		return hr = EMS_AZ_TX_FLUSH_ERROR;

	er = m_pELPort->FlushRXBuffer();
	if(er < RS232_SUCCESS)
		return hr = EMS_EL_RX_FLUSH_ERROR;

	er = m_pELPort->FlushTXBuffer();
	if(er < RS232_SUCCESS)
		return hr = EMS_EL_TX_FLUSH_ERROR;

		//Empty AZEL list
	list<lpAZEL_FORMAT>::iterator i; 		//list iterator number

		//delete list of vectors
	for (i = m_ReqTrackData.m_AzelRecordsList.begin(); 
			i != m_ReqTrackData.m_AzelRecordsList.end();)
	{
		delete *i;
		 ++i;
		m_ReqTrackData.m_AzelRecordsList.pop_front();
	}

	list<lpSTEP_DATA>::iterator ii; 		//list iterator number
		//delete m_TrackProfileList 
	for (ii = m_ReqTrackData.m_TrackProfileList.begin(); ii != 
		m_ReqTrackData.m_TrackProfileList.end();)
	{
		delete *ii;
		 ++ii;
		m_ReqTrackData.m_TrackProfileList.pop_front();
	}

	return m_hr = hr;
}

	//It determines when to start slewing the antenna around at its point of maximum
	//elevation. This is to ensure that the antenna will not exceed its maximum 
	//azimuth slew rate at this point of the setellite pass.
void CSARAntenna::ZenithCheck()
{
	DOUBLE		dPeakTime = 
		(m_TrackData.m_AzelStart + m_TrackData.m_AzelEnd)/2.0;
	DOUBLE		dAZ1;									//Azimuth befor peak
	DOUBLE		dAZ2;									//Azimuth after peak
	DOUBLE		dEL;									//Elevetion temporery value
	DOUBLE		dAZSlewTest;							//Current test of azimuth slew
	DOUBLE		dAZRateTest;							//Current test of azimuth rate

	DOUBLE		tPeakTime = dPeakTime;					//Time of max elevation
//DOUBLE		tIncrTime = m_ConfigD.m_IntTime*1000;	//Time increment on either side of peak
	DOUBLE		tIncrTime = m_TrackData.m_AzelInterval;	//Time increment on either side of peak
	BOOL		bDone = FALSE;							//End of file indicator

		//Test the pass defined in the Zenith Mode
	while(!bDone && (tPeakTime - tIncrTime) > m_TrackData.m_AzelStart)
	{
		PassAngles(tPeakTime - tIncrTime,dAZ1,dEL);
		PassAngles(tPeakTime + tIncrTime,dAZ2,dEL);

		//dAZSlewTest = DMOD(dAZ2 - dAZ1 + 540.0,360.0) - 180;
		for(dAZSlewTest = dAZ2 - dAZ1 + 540.0;dAZSlewTest>360;dAZSlewTest-=360);
		dAZSlewTest -= 180;

		dAZRateTest = fabs(1000*0.5*dAZSlewTest/tIncrTime);	//Calculate rate

			//Check if rate right for antenna azimuth driver
		if(dAZRateTest < m_ConfigD.m_fAZ_Rate)
			bDone = TRUE;									//Stop, now OK
		else	//vilocity to big try next pair of vectors
			tIncrTime += tIncrTime;
	}

		//Determine if zenith mode required
	if(tIncrTime > m_TrackData.m_AzelInterval)
	{														//Zenith mode
		m_ZenithMode.m_fStar = dPeakTime - tIncrTime;
		m_ZenithMode.m_fEnd = dPeakTime + tIncrTime;
		m_ZenithMode.m_bMode = TRUE;

		m_ZenithMode.m_fInc = fabs(dAZSlewTest/
			(tIncrTime/(m_ConfigD.m_IntTime*2.0)*1000));
	}
	else
	{
		m_ZenithMode.m_bMode = FALSE;
		m_ZenithMode.m_fInc = 0.0;
	}

}

	//It caculates the max time required by the antenna to slew to a specified azimuth 
	//and elevation. The max slew rate and accelaration of the antenna are considerated
	//in the caculations.
void CSARAntenna::CalcTime(DOUBLE& SlewTime)
{
	DOUBLE	dSlew;
	DOUBLE	fazTime,felTime;


		//Compute the time required for the azimuth axis
	dSlew = fabs(m_Prifile.m_fDeltaAZ);

	m_Prifile.m_ptAZ_FullSlew = __max(0.0,dSlew - 
		m_ConfigD.m_fAZ_Rate*m_ConfigD.m_fRamp_AZ);
		//Calculate the time during which the antenna is accelerating
	if(m_Prifile.m_ptAZ_FullSlew > 0)
			//The antenna will attain its maximum slew rate so its start/stop time will be 
			//ramp time.
		m_Prifile.m_ptStartStopTimeAZ = m_ConfigD.m_fRamp_AZ;
	else
			//If the antenna will not be attaining it's max slew rate, then calculate
			//how long the antenna is to accelerate.S = a*t^2.    S1/S2 = k^2
		m_Prifile.m_ptStartStopTimeAZ = 
			sqrt(dSlew*m_ConfigD.m_fRamp_AZ/m_ConfigD.m_fAZ_Rate);

	//t = s/v
	m_Prifile.m_ptAZ_FullSlew /= m_ConfigD.m_fAZ_Rate;	//Calculate the time
	
	fazTime = m_Prifile.m_ptAZ_FullSlew + 2*m_Prifile.m_ptStartStopTimeAZ;

		//Compute the time required for the elevation axis
	dSlew = fabs(m_Prifile.m_fDeltaEL);

	m_Prifile.m_ptEL_FullSlew = __max(dSlew - 
		m_ConfigD.m_fEL_Rate*m_ConfigD.m_fRamp_EL,0.0);

		//Calculate the time during which the antenna is accelerating
	if(m_Prifile.m_ptEL_FullSlew > 0)
		m_Prifile.m_ptStartStopTimeEL = m_ConfigD.m_fRamp_EL;	//time
	else
		m_Prifile.m_ptStartStopTimeEL = sqrt(dSlew*m_ConfigD.m_fRamp_EL/
			m_ConfigD.m_fEL_Rate);

	m_Prifile.m_ptEL_FullSlew /= m_ConfigD.m_fEL_Rate;

	felTime = m_Prifile.m_ptEL_FullSlew + 2*m_Prifile.m_ptStartStopTimeEL;

		//Tack the longest time
	SlewTime = __max(fazTime,felTime);	

}

	//It accumulates the changes in azimuth between each successive vector to determine 
	//the magnitude and diraction of the azimuth sweep.
void CSARAntenna::TrackDir(INT&	nDiraction)
{
	list<lpAZEL_FORMAT>::iterator i; 	//list iterator number
	DOUBLE	dCumDelAZ = 0.0;			//Cummulative delta azimuth value
	DOUBLE	dAZDiff;					//Delta azimuth between 2 vectors
	DOUBLE	dAZCurr;					//Current vector azumuth value
	DOUBLE	dPrevAZ = 0.0;				//Previous vector azimuth value
//----------------------------- ENU coordinates -----------------------------------------
	DOUBLE	dEast;						//East coordinate
	DOUBLE	dNorth;						//North coordinate

		//Accumulate the changes in azimuth between each vector to determine the magnitude
		//and diraction of the azimyth sweep.
	for (i = m_TrackData.m_AzelRecordsList.begin(); i != m_TrackData.m_AzelRecordsList.end(); ++i)
	{
		dEast = (*i)->m_East;
		dNorth = (*i)->m_North;
		dAZCurr = atan2(dEast,dNorth)*180/Pi;	//North is X and East is Y tng = East/North

		if((dEast < 0.0) && (dNorth < 0.0) || (dEast < 0.0) && (dNorth > 0.0))
			dAZCurr += 360.0;

		if(i != m_TrackData.m_AzelRecordsList.begin())
		{
			dAZDiff = dAZCurr - dPrevAZ;
				//Take care of 180(-180) degree discontinuity
			if(dAZDiff > 180.0)		
				dAZDiff -= 360.0;
			else
				if(dAZDiff < -180.0)	
					dAZDiff += 360.0;
				
			dCumDelAZ += dAZDiff;
		}
		dPrevAZ = dAZCurr;
	}

		//Set the diraction to CW if the dCumDelAZ is positive and CCW if negativ
	if(dCumDelAZ > 0.0)
		nDiraction = CW;
	else
		nDiraction = CCW;

}

EMS_RESULT	CSARAntenna::SetMonitorSmoothMove()
{
	EMS_RESULT		hr = EMS_OK;
	INT				rs232hr;
	DWORD			nCount;
	CHAR			Buff[256];
	SYSTEMTIME		SysTime;
	CEMSAntTime		EMSCurrTimeObject;
	CEMSAntTime		EMSStartTimeObject(m_ReqTrackData.m_EMSTimeStart);//UTC

#ifdef LOG_FILE_ACTIVE
	SYSTEMTIME			LogSysTime;
	CEMSAntTime			EMSCurrTime;
	TCHAR				szLogBuff[1024];
	DWORD				nBWrite;
#endif

	if(m_bSHUT_DOWN || hr != EMS_OK)
		goto Stop;

	GetSystemTime(&SysTime);
	EMSCurrTimeObject.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
		SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);

	if(m_ReqTrackData.m_Mode == REAL)
		//Sleep(EMSStartTimeObject.SecondsDifferent(EMSCurrTimeObject)*1000);
		if((m_ReqTrackData.m_Records - m_TrackData.m_StartStep) > 1)
			Sleep(EMSCurrTimeObject.SecondsDifferent(EMSStartTimeObject)*1000);
		else
			return hr = EMS_TOO_LATE_FOR_TRACK;
	else
		Sleep(2000);
			//- m_ConfigD.m_ulProgramDelay/1000)*1000);


	sprintf(Buff,"G\r");					//Start program in indexers
	nCount = strlen(Buff);
	rs232hr = m_pELPort->Write(Buff,nCount);
	sprintf(Buff,"G\r");					//Start program in indexers
	nCount = strlen(Buff);
	if(rs232hr == RS232_SUCCESS)
		rs232hr = m_pAZPort->Write(Buff,nCount);
	else
		hr = ANT_INV_ELEVATION_COMM;

//	Sleep(200);

#ifdef LOG_FILE_ACTIVE
	GetSystemTime(&LogSysTime);
	EMSCurrTime.SetTime(LogSysTime.wYear,LogSysTime.wMonth,LogSysTime.wDay,LogSysTime.wHour,
						LogSysTime.wMinute,LogSysTime.wSecond,LogSysTime.wMilliseconds*1000);
	sprintf(szLogBuff,"At %s antenna started tracking satellite.\r\n",EMSCurrTime.GetTimeData());
	strcat(szLogBuff,"\r\n<<<<<<<<<<<<-INDEXES MONITORING REPORT->>>>>>>>>>>\r\n");
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

	sprintf(szLogBuff,"\r\n|No|%-10s|%-9s|%-9s|%-8s|%-8s|%-7s|%-7s|\r\n",
		"REP TIME","REP AZ","REP EL","ERROR AZ","ERROR EL","AZ TERR","EL TERR");
	strcat(szLogBuff,"|--|----------|---------|---------|--------|--------|-------|-------|\r\n");
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

#endif

	if(m_bSHUT_DOWN || hr != EMS_OK)
		goto Stop;

	Sleep(m_ReqTrackData.m_AzelInterval/2.0-1000);

	m_pAZPort->FlushRXBuffer();
	m_pELPort->FlushRXBuffer();

	if(m_bSHUT_DOWN || hr != EMS_OK)
		goto Stop;

	Sleep(m_ReqTrackData.m_AzelInterval/2.0-1000);

	if(m_bSHUT_DOWN || hr != EMS_OK)
		goto Stop;

	TrackSmoothMove(m_ReqTrackData);

#ifdef LOG_FILE_ACTIVE
	GetSystemTime(&LogSysTime);
	EMSCurrTime.SetTime(LogSysTime.wYear,LogSysTime.wMonth,LogSysTime.wDay,LogSysTime.wHour,
						LogSysTime.wMinute,LogSysTime.wSecond,LogSysTime.wMilliseconds*1000);
	sprintf(szLogBuff,"\r\n<<<<<<<<<<<<-END INDEXES MONITORING REPORT->>>>>>>>>>>\r\n");
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
	sprintf(szLogBuff,"LOST time at %s .\r\n",EMSCurrTime.GetTimeData());
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif


	m_pAZPort->FlushRXBuffer();
	m_pELPort->FlushRXBuffer();

Stop: if(m_bSHUT_DOWN)
	{
		sprintf(Buff,"%c\r",ESC);		//ESC = '27'
		Send(AZIMUTH,Buff,nCount = 2);
		sprintf(Buff,"%c\r",ESC);		//ESC = '27'
		Send(ELEVATION,Buff,nCount = 2);

		Output(RMT_STNDBY,0,0);
	
	}
			

	return hr;
}


EMS_RESULT CSARAntenna::Test(TRACKDATA TrackData)
{

	EMS_RESULT			hr = EMS_OK;
	INT					rs232hr;
	DWORD				nCount;
	CHAR				Buff[256];
	LONG				tExeTime;
	LONG				tWaitTime;
/*
	//BOOL				bZenMove;			//Move antenna done in zenith mode
	//INT					nDiraction;			//Move diraction of antenna
//	DOUBLE				dAZ,dEL;			//Calculated location
	//DOUBLE				dCurrAZ,dCurrEL;
	CHAR				Buff[256];
	BOOL				bLoop = TRUE;
	BOOL				bZenithMoveSwitch = FALSE;//Indicates zenith mode started
	DOUBLE				tInt = m_ConfigD.m_IntTime*1000;
	//DOUBLE				tCurrTime, tLastMove;
	DWORD				StepCount = 0;

	m_TrackData = TrackData;

	m_TrackData.m_AzelStart = ReadTime();
	m_TrackData.m_AzelEnd = m_TrackData.m_AzelStart + 
		m_TrackData.m_AzelInterval*TrackData.m_Records;

	ZenithCheck();
	if(m_ZenithMode.m_bMode)
	{
		SendAntMessage(MSG_LOG,"Test - Zenith pass mode required!");
		//bZenMove = FALSE;
		m_ZenithMode.m_fStar -= 1000.0;	//One secind early
		m_ZenithMode.m_fEnd   += 1000.0;	//One second laiter;
	}
	else
		SendAntMessage(MSG_LOG,"Test - No zenith pass mode required.");

		//Determine diraction of tracking.
	TrackDir(nDiraction);

	Sleep(10);			//For message perper

	if(nDiraction == CW)
		SendAntMessage(MSG_LOG,"Test - Clockwise satellite track.");
	else
		SendAntMessage(MSG_LOG,"Test - Counter clockwise satellite track.");

	Sleep(10);
	PassAngles(m_TrackData.m_AzelStart,dAZ,dEL);
	sprintf(Buff,"Test - Position antenna to the start: AZ%f,EL%f",
		dAZ,dEL);
	SendAntMessage(MSG_LOG,Buff);
	hr = Move(dAZ,dEL,nDiraction);


	hr = InitSARAntenna(ReadTime());	//Immediate move,dont wait

	while(ReadTime() > m_TrackData.m_AzelStart && ReadTime() < m_TrackData.m_AzelEnd )
	{
		if(m_bSHUT_DOWN)
		{
			DWORD nCount;

			SendAntMessage(MSG_INFORMATION,
				"Test - request stopped by EMS Stop command");
			sprintf(Buff,"s\r");
			Send(AZIMUTH,Buff,nCount = 2);
			Send(ELEVATION,Buff,nCount = 2);
			Output(STNDBY,0,0);
			Purge();
			return hr;
		}


		if(m_ZenithMode.m_bMode && ReadTime() > m_ZenithMode.m_fStar 
			&& ReadTime() < m_ZenithMode.m_fEnd)
		{
			if(!bZenithMoveSwitch)
			{
				bZenithMoveSwitch = TRUE;
				SendAntMessage(MSG_LOG,"Antenna started Zenith Move.");
			}
		}
		else
		{
			if(bZenithMoveSwitch)
			{
				bZenithMoveSwitch = FALSE;
				SendAntMessage(MSG_LOG,"Antenna ended Zenith Move.");
			}
			sprintf(Buff,"Antenna started %d interval step.",++StepCount);
			SendAntMessage(MSG_LOG,Buff);
			//SmoothIntMove();	//Linear interval move
		}
	}
*/
	m_TrackData = TrackData;
	//m_TrackData.m_Mode = TEST;

	m_TrackData.m_AzelStart = ReadTime();
	m_TrackData.m_AzelEnd = m_TrackData.m_AzelStart + 
		m_TrackData.m_AzelInterval*m_TrackData.m_Records;

	ZenithCheck();
	if(m_ZenithMode.m_bMode)
		SendAntMessage(MSG_TRACE,"Zenith pass mode required!");
	else
		SendAntMessage(MSG_TRACE,"No zenith pass mode required.");


	if((hr = ProgSmoothTrack(tExeTime,tWaitTime,TEST)) == EMS_OK)	//Immediate move,dont wait
	{
		sprintf(Buff,"G\r");					//Start program in indexers
		nCount = strlen(Buff);
		rs232hr = m_pELPort->Write(Buff,nCount);
		sprintf(Buff,"G\r");					//Start program in indexers
		nCount = strlen(Buff);
		rs232hr = m_pAZPort->Write(Buff,nCount);

		Sleep(m_TrackData.m_AzelInterval/2.0);
		m_pAZPort->FlushRXBuffer();
		m_pELPort->FlushRXBuffer();
		Sleep(m_TrackData.m_AzelInterval/2.0+600);

		m_TrackData.m_StartStep = 0;
		TrackSmoothMove(m_TrackData);

		m_pAZPort->FlushRXBuffer();
		m_pELPort->FlushRXBuffer();
			
	}

	return hr;
}
/*
EMS_RESULT CSARAntenna::CheckProgMotion()
{
	EMS_RESULT			hr = EMS_OK;
	CHAR				Buff[256];
	BOOL				bLoop = TRUE;
	BOOL				bZenithMoveSwitch = FALSE;//Indicates zenith mode started
	DOUBLE				tInt = m_ConfigD.m_IntTime*1000;
	DWORD				StepCount = 0;

	while(ReadTime() > m_TrackData.m_AzelStart && ReadTime() < m_TrackData.m_AzelEnd )
	{
		if(m_bSHUT_DOWN)
		{
			DWORD nCount;

			SendAntMessage(MSG_INFORMATION,
				"Test - request stopped by EMS Stop command");
			sprintf(Buff,"s\r");
			Send(AZIMUTH,Buff,nCount = 2);
			Send(ELEVATION,Buff,nCount = 2);
			Output(STNDBY,0,0);
			Purge();
			return hr;
		}


		if(m_ZenithMode.m_bMode && ReadTime() > m_ZenithMode.m_fStar 
			&& ReadTime() < m_ZenithMode.m_fEnd)
		{
			if(!bZenithMoveSwitch)
			{
				bZenithMoveSwitch = TRUE;
				SendAntMessage(MSG_LOG,"Antenna started Zenith Move.");
			}
		}
		else
		{
			if(bZenithMoveSwitch)
			{
				bZenithMoveSwitch = FALSE;
				SendAntMessage(MSG_LOG,"Antenna ended Zenith Move.");
			}
			sprintf(Buff,"Antenna started %d interval step.",++StepCount);
			SendAntMessage(MSG_LOG,Buff);
			//SmoothIntMove();	//Linear interval move
		}
	}

		return hr;

}
*/
EMS_RESULT CSARAntenna::TrackSmoothMove(TRACKDATA& trackData)
{
	EMS_RESULT			            hr = EMS_OK;
	CHAR*							token;
	LONG							AZPosition,ELPosition;
	list<lpSTEP_DATA>::iterator		z = trackData.m_TrackProfileList.begin();
	MOVE							AZMove,ELMove;
//	INT								nDiraction = 1;
	INT								nDiraction = (trackData.m_nDiraction == CW)?1:-1;
	DOUBLE							AZDif;
	DOUBLE							ELDif;
	CHAR							Buff[256];
	DOUBLE							SpeedDelay;
	BOOL							bAZDone;
	BOOL							bELDone;
	DWORD							dwStepCount = 1;


#ifdef LOG_FILE_ACTIVE
	SYSTEMTIME			SysTime;
	CEMSAntTime			EMSCurrTime;
	TCHAR				szLogBuff[1024];
	DWORD				nBWrite;
	LONG				fAZTimeReport,fELTimeReport;
#endif

/*
	GetModuleFileName( 0, szLogFilePath, sizeof(szLogFilePath) / sizeof(TCHAR) );

	*(szLogFilePath + strlen(szLogFilePath) - strlen("exe")) = 0;

	strcat(szLogFilePath,"LOG");

	hLogFile = CreateFile(szLogFilePath,GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
*/
//	if(trackData.m_nDiraction == CCW)
//		nDiraction = -1;


	while(trackData.m_StartStep < trackData.m_Records - 1 && 
		hr == EMS_OK && !m_bSHUT_DOWN)
	{
		bAZDone = bELDone = FALSE;
		SpeedDelay = ReadTime();
		while(!bAZDone || !bELDone && !m_bSHUT_DOWN)
		{
			if(!bAZDone)
			{
				m_pAZPort->Peek(Buff,500);
				if(strtok(Buff,"0123456789"))
				{
					sprintf(Buff,"Azimuth in Step %d, Time Error %d",
						dwStepCount,(LONG)(ReadTime()-SpeedDelay - 2000));
					SendAntMessage(MSG_INFORMATION,Buff);
#ifdef LOG_FILE_ACTIVE					
					fAZTimeReport = (LONG)(ReadTime()-SpeedDelay - 2000);
#endif
					bAZDone = TRUE;
				}
			}

			if(!bELDone)
			{
				m_pELPort->Peek(Buff,500);
				if(strtok(Buff,"0123456789"))
				{
					sprintf(Buff,"Elevation in Step %d, Time Error %d",
						dwStepCount,(LONG)(ReadTime()-SpeedDelay - 2000));
					SendAntMessage(MSG_INFORMATION,Buff);
#ifdef LOG_FILE_ACTIVE
					fELTimeReport = (LONG)(ReadTime()-SpeedDelay - 2000);
#endif
					bELDone = TRUE;
				}
			}
			Sleep(6);
		}

		if(m_bSHUT_DOWN) 
			break;


		m_pAZPort->Read(Buff,500);
		token = strtok(Buff," ");
		AZPosition = atol(token);
		m_AntStatus.m_dwAZinSteps = AZPosition;
		m_AntStatus.m_fAzimuth = AZPosition/m_ConfigD.m_fAZ_Factor;
	//-------------------------------------------------------------
		m_pELPort->Read(Buff,500);
		token = strtok(Buff," ");
		ELPosition = atol(token);
		m_AntStatus.m_dwELinSteps = ELPosition;
		m_AntStatus.m_fElevation = ELPosition/m_ConfigD.m_fEL_Factor;

	//-------------------------------------------------------------
		LocNotify(m_AntStatus.m_fAzimuth,m_AntStatus.m_fElevation);

		AZMove = (*(z))->m_AZMoveVector;
		ELMove = (*(z))->m_ELMoveVector;

		AZDif = (m_AntStatus.m_fAzimuth - AZMove.End)*nDiraction;
		ELDif = m_AntStatus.m_fElevation - ELMove.End;

		ErrLocNotify(AZDif,ELDif);

#ifdef LOG_FILE_ACTIVE
		//CHAR FileBuff[1024];
		GetSystemTime(&SysTime);
		EMSCurrTime.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
							SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
		sprintf(szLogBuff,"|%2d|%9s | %7.2f | %7.2f | %6.2f | %6.2f | %5d | %5d |\r\n",
			trackData.m_StartStep+1,EMSCurrTime.GetTimeData(),m_AntStatus.m_fAzimuth,
			m_AntStatus.m_fElevation,AZDif,ELDif,fAZTimeReport,fELTimeReport);

		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);

		sprintf(szLogBuff,"|--|----------|---------|---------|--------|--------|-------|-------|\r\n");
		WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif
		//--------------------------------------------------------------
		dwStepCount++;
		trackData.m_StartStep++;
		if(trackData.m_StartStep < trackData.m_Records - 1)
		{
			++z;
			Sleep(trackData.m_AzelInterval - /*2000 + */(ReadTime() - SpeedDelay));
		}
	}
#ifdef LOG_FILE_ACTIVE
	sprintf(szLogBuff,"\r\n\r\n");
	WriteFile(m_hLogFile,szLogBuff,strlen(szLogBuff),&nBWrite,NULL);
#endif
	return hr;
}

EMS_RESULT CSARAntenna::Track(LPTSTR lpszAZELfile)
{
	EMS_RESULT		hr = EMS_FALSE;

	m_ReqTrackData = m_ReqTrackData;

	hr = SetFileToTrackData(m_ReqTrackData);

	if(hr == EMS_OK)
	{
		SetTimingToTrackData(m_ReqTrackData);
		ZenithCheck();

		hr = SetProgSmoothTracking(m_ReqTrackData);
		if(hr == EMS_OK)
			SetMonitorSmoothMove();

	}


	//Sleep(6000);

/*
	EMS_RESULT			hr = EMS_FALSE;
	CHAR*				lpFile = 0;

	INT					nDiraction;				//Diraction to move antenna 
	DWORD				dwRecords = 0;			//Number of vector records in AZEL file
	DWORD				nBRead;					//Number of bytes readed from file
	lpAZEL_FORMAT		lpAzelRec;				//Pointer to AZEL record vector
	list<lpAZEL_FORMAT>::iterator i; 			//list iterator number
	BOOL				bZenMove;				//Move antenna done in zenith mode
	DOUBLE				tCurrTime;				//Current time
	DOUBLE				dAZ;					//Calculeted antenna azimuth
	DOUBLE				dEL;					//Calculeted antenna elevation
	DOUBLE				dCurrAZ;				//Current calculeted antenna azimuth
	DOUBLE				dCurrEL;				//Current calculeted antenna elevation
	DOUBLE				fAzDiff;				//Delta azimuth to be move
	DOUBLE				fElDiff;				//Delta elevation to be move
	BOOL				bZenithMoved = FALSE;	//Move antenna done in zenith mode

		//Move antenna to home position 
	SendAntMessage(MSG_LOG, "Move antenna to the HOME position before tracking.");
	if(Home() != EMS_OK)
	{
		SendAntMessage(MSG_WARNING, "UNable home antenna for tracking");
		Reset();
		if(CheckAnt() != EMS_OK)
		{
			Sleep(1000);

			Purge();

			return EMS_FALSE;
		}
		SendAntMessage(MSG_WARNING, "Reset repair the problem");
	}

	if(lpFile = Trim(lpszAZELfile)) 
	{
		SendAntMessage(MSG_WARNING, "Wrong AZEL file name");
		return EMS_FALSE;
	}
		//Put antenna in to the stendby mode
	Output(RMT_STNDBY,0.0,0.0);

	m_hFile = CreateFile(lpFile,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
			//File opened for reading read azel configuration
		BOOL bResult = ReadFile(m_hFile,&m_TrackData.m_AzelStart,sizeof(DOUBLE),&nBRead,NULL);
		if(bResult && (nBRead == sizeof(DOUBLE)))
		{
			bResult = ReadFile(m_hFile,&m_TrackData.m_AzelInterval,sizeof(DWORD),&nBRead,NULL);
			//bResult = ReadFile(m_hFile,&m_TrackData.m_AzelOdap,sizeof(DWORD),&nBRead,NULL);
			//bResult = ReadFile(m_hFile,&m_TrackData.m_AzelRev,sizeof(DWORD),&nBRead,NULL);
			if(bResult && (nBRead == sizeof(DOUBLE))) 
				hr = EMS_OK;
		}
			//Read AZEL vectors in to the memmory and determine thay number
		do
		{
			lpAzelRec = new AZEL_FORMAT;
			bResult = ReadFile(m_hFile,lpAzelRec,sizeof(AZEL_FORMAT),&nBRead,NULL);
			if(bResult && (nBRead == sizeof(DOUBLE)))
			{
				m_TrackData.m_AzelRecordsList.insert(m_TrackData.m_AzelRecordsList.end(),lpAzelRec);
				dwRecords++;
			}
		}while(nBRead != sizeof(AZEL_FORMAT));

		m_TrackData.m_Records = dwRecords;

			//End of the file
		m_TrackData.m_AzelEnd = m_TrackData.m_AzelStart + (dwRecords - 1)*
			m_TrackData.m_AzelInterval;
			//if the current time already exceeds the end of the AZEL file
		if(ReadTime() > m_TrackData.m_AzelEnd)
		{
			SendAntMessage(MSG_LOG, "No longer current");
			Purge();
				//Put antenna in to the stendby mode
			Output(RMT_STNDBY,0,0);
				
			delete[] lpFile;
			return hr;
		}

			//Now antenna is ready to tracking mode

			//Determine if zenith mode pass mast be implemented. if so, add one
			//sec for acceleration and one sec for deceleration

		ZenithCheck();
		if(m_ZenithMode.m_bMode)
		{
			SendAntMessage(MSG_LOG, "Zenith pass mode required!");
			bZenMove = FALSE;
			m_ZenithMode.m_fStar -= 1.0;
			m_ZenithMode.m_fEnd += 1.0;
		}
		else
			SendAntMessage(MSG_LOG, "No zenith pass mode required.");

			//Determine diraction of tracking
		TrackDir(nDiraction);

		if(nDiraction == CW)
			SendAntMessage(MSG_LOG, "Clockwise satellite track.");
		else
			SendAntMessage(MSG_LOG, "Counter clockwise satellite track.");

			//Move antenna to the position where it should be at AOS time
				
			//Determine witch time is domenanty for calculation.
		tCurrTime = __max(ReadTime(),m_TrackData.m_AzelStart);
		GetStatus();
			//Determine AZ and El in given time.
		PassAngles(tCurrTime,dAZ,dEL);

			//Determine the time neaded for catching the setllite if time over AOS
		tCurrTime = ReadTime() + 1.0 + 
			__max(fabs((DMOD(dAZ - m_AntStatus.m_fAzimuth + 540.0,360.0) - 180.0)/
				(DOUBLE)m_ConfigD.m_fAZ_Rate), 
				fabs(dEL - m_AntStatus.m_fElevation)/(DOUBLE)m_ConfigD.m_fEL_Rate);
				
			//Determine dominance time.
		tCurrTime = __max(tCurrTime,m_TrackData.m_AzelStart);
		if(m_ZenithMode.m_bMode && tCurrTime > m_ZenithMode.m_fStar)
		{
					//We now going to track zanith mode and befor that mode started
			tCurrTime = __max(tCurrTime, m_ZenithMode.m_fEnd);
			bZenithMoved = TRUE;
		}

		PassAngles(tCurrTime,dAZ,dEL);

		SendAntMessage(MSG_LOG, "Position antenna to start satellite pass");

			//OK move antenna to psition befor tracking
		hr = Move(dAZ,dEL,nDiraction);


		BOOL bLoop;				//Tracking loop control

		if(hr == EMS_OK)
		{
				//Initialize for antenna motion checking, and wait until AOS time comes...
			bLoop = TRUE;
			GetStatus();
			dAZ =m_AntStatus.m_fAzimuth;
			dEL = m_AntStatus.m_fElevation;
				//Wait if neaded until AOS time will came.
			while(ReadTime() < m_TrackData.m_AzelStart)
				Sleep(1000);	//One second
			tCurrTime = ReadTime();  
		}
		else
		{
				//Could not move to AOS
			bLoop = FALSE;
			hr = ANT_NOT_REACHED_AOS;
		}

		tCurrTime = ReadTime();

			//Track main loop
		while(tCurrTime > m_TrackData.m_AzelStart && tCurrTime < m_TrackData.m_AzelEnd && bLoop)
		{
			if(m_bSHUT_DOWN)
			{
				SendAntMessage(MSG_WARNING, "Processed request to sut down.");
				bLoop = FALSE;
			}
			GetStatus();
			dCurrAZ = m_AntStatus.m_fAzimuth;
			dCurrEL = m_AntStatus.m_fElevation;

				//Get the current time
			tCurrTime = ReadTime();

				//Check if zenith mode came
			if(m_ZenithMode.m_bMode && !bZenithMoved && tCurrTime > m_ZenithMode.m_fStar && 
				tCurrTime < m_ZenithMode.m_fEnd)
			{
				bZenithMoved = TRUE;

					//Stop through rate command
				Output(RATE_AZEL,0.0,0.0);
				Sleep(1000);

				SendAntMessage(MSG_INFORMATION, "Begin zenith processing.");

					//Get the position of the antenna at the end of the zenith period
					//and use regular move command to drive it there. The error is ignired
					//here because it will be processed when the zenith time is over.
				PassAngles(m_ZenithMode.m_fEnd,dAZ,dEL);

					//Move directly to the end of zenith mode
				hr = IndtMove(dAZ,dEL);
				if(hr != EMS_OK)
					SendAntMessage(MSG_WARNING, "Zenith processing failed.");

					//Just in case..., Loop and wait until the zenith time is up then
					//go back
				while(ReadTime() < m_ZenithMode.m_fEnd);

				GetStatus();
				dCurrAZ = m_AntStatus.m_fAzimuth;
				dCurrEL = m_AntStatus.m_fElevation;

				if(m_bSHUT_DOWN)
				{
					SendAntMessage(MSG_WARNING, "Processed request to sut down.");
					bLoop = FALSE;
				}
			}

				//Compute the vilocities for ACUs
			PassAngles(ReadTime() + m_ConfigD.m_fLatency,dAZ,dEL);

				//Calculate azimuth and elevation moving rate using the retrieval time
				//Retrieval time is the time, in seconds, that we look in the future as
				//target time for a specific location. From those numbers, the target
				//rate is determined.
			fAzDiff = (DMOD(dAZ - dCurrAZ + 540.0,360.0) - 180.0)/m_ConfigD.m_fLatency;
			fElDiff = (dEL - dCurrEL)/m_ConfigD.m_fLatency;

			if(fabs(fElDiff) > fabs(m_ConfigD.m_fEL_Rate))
				fElDiff = SIGN(m_ConfigD.m_fEL_Rate, fElDiff);

				//send the command buffer to the ACU
			Output(RATE_AZEL,fAzDiff,fElDiff);

			hr = CheckMotion();

				//If a fault occured then abort the tracking and raise the antenna 
				//fault condition
			if(hr != EMS_OK)
			{
				bLoop = FALSE;		//Order to end current antenna track.
					//Stop antenna 
				Output(RATE_AZEL,0.0,0.0);
					//Deley 2 seconds
				Sleep(2000);
					//Release RS-232 TR and DR buffers
				Purge();
					//Put antenna in stndby mode
				Output(STNDBY,0.0,0.0);

			}
		}
	}

	if(hr == EMS_OK)
	{
			//Stop antenna 
		Output(RATE_AZEL,0.0,0.0);
		Sleep(2000);
		Purge();
		Output(STNDBY,0.0,0.0);
	}
	delete[] lpFile;

*/	
	return hr;
}

EMS_RESULT CSARAntenna::IndtMove(DOUBLE fAZCoordinate, DOUBLE fELCoordinate)
{
	EMS_RESULT	hr = EMS_OK;
	DOUBLE		HalfBeam = m_ConfigD.m_fBeam_Width/2.0;
	DOUBLE		AZIMUTH;		//Distination AZIMUTH in staps
	DOUBLE		ELEVATION;		//Distination ELEVATION in steps
	DOUBLE		PreviousAZ;		
	DOUBLE		PreviousEL;
	DOUBLE		AZDiff;
	DOUBLE		ELDiff;
	BOOL		Done = FALSE;
	INT			MaxRetry = 30;
	INT			Tries = 0;

	if(fAZCoordinate < m_ConfigD.m_fMin_Azimuth)
		fAZCoordinate += 360.0;
	if(fAZCoordinate > m_ConfigD.m_fMax_Azimuth)
		fAZCoordinate -= 360.0;
	if(fELCoordinate < m_ConfigD.m_fMin_Elevation)
		fELCoordinate = m_ConfigD.m_fMin_Elevation;
	if(fELCoordinate > m_ConfigD.m_fMax_Elevation)
		fELCoordinate = m_ConfigD.m_fMax_Elevation;

	AZIMUTH = fAZCoordinate * m_ConfigD.m_fAZ_Factor;
	ELEVATION = fELCoordinate * m_ConfigD.m_fEL_Factor;

		//Send the move command to the ACU
	Output(WRITE_AZEL, fAZCoordinate, fELCoordinate);

		//Get antenna status
	GetStatus();
	PreviousAZ = m_AntStatus.m_dwAZinSteps;
	PreviousEL = m_AntStatus.m_dwELinSteps;

		//Loop until the antenna reaches th destination or a fault accurs
	while(!Done && hr == EMS_OK)
	{
		GetStatus();
		
			//Handle hitting limit switch conditions
		if(m_AntStatus.m_bCWLimit)
		{
			SendAntMessage(MSG_WARNING, "Antenna at Clockwise limit zone!");
			hr = ANT_CW_LIMIT_HIT;
		}else
			if(m_AntStatus.m_bCCWLimit)
			{
				SendAntMessage(MSG_WARNING, "Antenna at Counter Clockwise limit zone!");
				hr = ANT_CCW_LIMIT_HIT;
			}else
				if(m_AntStatus.m_bHIGHLimit)
				{
					SendAntMessage(MSG_WARNING, "Antenna at High elevation limit zone!");
					hr = ANT_HIGH_LIMIT_HIT;
				}else
					if(m_AntStatus.m_bLOWLimit)
					{
						SendAntMessage(MSG_WARNING, "Antenna at Low elevation limit zone!");
						hr = ANT_LOW_LIMIT_HIT;
					}

			//Handle antenna get stacked in the middle of the way
			//Delay some time before getting out of the loop
		if(m_AntStatus.m_dwAZinSteps == PreviousAZ && m_AntStatus.m_dwELinSteps == PreviousEL &&
			(m_AntStatus.m_dwAZinSteps != AZIMUTH || m_AntStatus.m_dwELinSteps != ELEVATION))
		{
			Sleep(1000);
			Done = ++Tries > MaxRetry;
			if(Done)
				SendAntMessage(MSG_LOG, "Antenna stopped befor reaching destination");
		}
		else
		{
				//No problem so far. Check if antenna reaches the distanation
			PreviousAZ = m_AntStatus.m_dwAZinSteps;
			PreviousEL = m_AntStatus.m_dwELinSteps;

			if(m_AntStatus.m_dwAZinSteps == AZIMUTH && m_AntStatus.m_dwELinSteps == ELEVATION)
				Done = TRUE;
		}
	}

		//Antenna does not move anymore
		//Check if the satellite is within the antenna beam width
	if(hr == EMS_OK)
	{
		AZDiff = DMOD(m_AntStatus.m_fAzimuth - fAZCoordinate + 540.0,360.0) - 180.0;
		ELDiff = fabs(m_AntStatus.m_fElevation - fELCoordinate);

		if(AZDiff > HalfBeam || ELDiff > HalfBeam)
		{
			hr = ANT_INV_BEAMWIDTH;
			SendAntMessage(MSG_INFORMATION, "Losing track of antenna - outside beam width.");
		}
	}

		//handle antenna fault by moving it to the home position
	if(hr != EMS_OK)
		Home();
	else
		SendAntMessage(MSG_LOG, "Antenna tracking complete successfully.");

	return hr;
}

EMS_RESULT CSARAntenna::CheckAnt()
{
	EMS_RESULT hr = EMS_OK;
	CHAR	   Msg[2048];
	CHAR	   Debug[1024];
	INT		   nDebugLines;

		//Check azimuth communication port
	if(m_pAZPort->ErrorStatus() < RS232_SUCCESS)
	{
		nDebugLines = m_pAZPort->FormatDebugOutput(NULL);
		m_pAZPort->FormatDebugOutput(Debug,nDebugLines);
		hr = EMS_FALSE;

		if(m_pAZPort->ErrorStatus() < RS232_ERROR )
		{
			sprintf(Msg,"The AZIMUTH comm. port has error: %s \n"
						"	AZIMUTH FORNAT DEBUG OUTPUT \n"
						"	=========================== \n\n"
						"%s",m_pAZPort->ErrorName(m_pAZPort->ErrorStatus()),Debug);
			SendAntMessage(MSG_ERROR,Msg);	
		}
		else
		{
			sprintf(Msg,"The AZIMUTH comm. port has warning: %s \n"
						"	AZIMUTH FORNAT DEBUG OUTPUT \n"
						"	=========================== \n\n"
						"%s",m_pAZPort->ErrorName(m_pAZPort->ErrorStatus()),Debug);
			SendAntMessage(MSG_WARNING,Msg);
		}

	}

	if(m_pELPort->ErrorStatus() < RS232_SUCCESS)
	{
		nDebugLines = m_pELPort->FormatDebugOutput(NULL);
		m_pELPort->FormatDebugOutput(Debug,nDebugLines);
		hr = EMS_FALSE;

		if(m_pELPort->ErrorStatus() < RS232_ERROR )
		{
			sprintf(Msg,"The ELEVATION comm. port has error: %s \n"
						"	ELEVATION FORNAT DEBUG OUTPUT \n"
						"	=========================== \n\n"
						"%s",m_pELPort->ErrorName(m_pELPort->ErrorStatus()),Debug);
			SendAntMessage(MSG_ERROR,Msg);	
		}
		else
		{
			sprintf(Msg,"The AZIMUTH comm. port has warning: %s \n"
						"	AZIMUTH FORNAT DEBUG OUTPUT \n"
						"	=========================== \n\n"
						"%s",m_pELPort->ErrorName(m_pELPort->ErrorStatus()),Debug);
			SendAntMessage(MSG_WARNING,Msg);
		}

	}

	return hr;
}

void CSARAntenna::Reset()
{
	m_pAZPort->Reset();
	m_pAZPort->ParityError(CLEAR);
	m_pAZPort->FramingError(CLEAR);
	m_pAZPort->HardwareOverrunError(CLEAR);
	m_pAZPort->SoftwareOverrunError(CLEAR);

	m_pELPort->Reset();
	m_pELPort->ParityError(CLEAR);
	m_pELPort->FramingError(CLEAR);
	m_pELPort->HardwareOverrunError(CLEAR);
	m_pELPort->SoftwareOverrunError(CLEAR);

}

CHAR* CSARAntenna::Trim(CHAR* lpInString)
{
	CHAR*	szTempStr = 0;
	CHAR*	lpFirst = 0;
	CHAR*	lpLast = 0;
	DWORD	nStrLen = strlen(lpInString);
	DWORD   nCount;

	if(lpInString)
	{

			//find first non-blank character
		for(lpFirst = lpInString,nCount = 0; nCount < nStrLen && *lpFirst == ' ';
			nCount++,lpFirst++);
		if(nCount == nStrLen)	return NULL;

			//Find last non-blank character
		for(lpLast = szTempStr+nStrLen; *lpLast == ' '; lpLast--);

		szTempStr = new CHAR(lpLast-lpFirst);
		strcpy(szTempStr,lpFirst);
		*(szTempStr + (lpLast-lpFirst) + 1) = NULL;
	}

	return szTempStr;
}

/***************************************************************************************
This function moves the antenna to desired azimuth and elevation. The diraction of 
antenna motion is chosen such that during a pass, the cable wrap will unwrap itsalf.
Once the diraction of motion has been determined, an interpolation is used to determine
the antenna's path. Intermediate coordinates along the path are calculated and the
antenna move from coordinate to coordinate at time intervals specified in the config.
***************************************************************************************/
EMS_RESULT CSARAntenna::Move(double fAZCoordinate, double fELCoordinate, INT wDiraction)
{
	DOUBLE				fAZ_SLEW;			//Azimuth slew
	DOUBLE				fCompAZ_SLEW;		//Complement of shortest azimuth slew
	DOUBLE				fFinal_AZ;			//Azimuth after move using shortest slew
	DOUBLE				dCurrentAZ;			//Current antenna position in azimuth
	DOUBLE				dCurrentEL;			//Current antenna position in elevation
	EMS_RESULT			hr = EMS_FALSE;
	DOUBLE				RefTime;
	BOOL				LOOP = TRUE;
	BOOL				STOPED;
	BOOL				bError;				//Antenna fault
	INT					nErrCount = 0;		//Number of retries befor fault
	INT					nMaxStaps;			//Maxsimum number of retries allowed
	DOUBLE				dPreviousAZ;		//Previous azimuth position in steps
	DOUBLE				dPreviousEL;		//Previous elevation position in steps
	DOUBLE				dStepsFinalAZ;		//Final azimuth position in steps
	DOUBLE				dStepsFinalEL;		//Final elevation position in steps
	DOUBLE				ProfileTime;
	CHAR				szBuffer[256];
	DWORD				nCount;
	DOUBLE tStopElepsedTime;
	DOUBLE tStopTime;

		//Get the current status and position of the antenna 
	hr = GetStatus();

		//This caculation provides the shortest slew from current azimuth to distanation
		//azimuth.
	for(fAZ_SLEW = fAZCoordinate - m_AntStatus.m_fAzimuth + 540.0;
			fAZ_SLEW > 360.0; fAZ_SLEW -= 360);
	fAZ_SLEW -= 180.0;

		//Calculation of the longest slew for current azimuth
	fCompAZ_SLEW = 360.0 - fabs(fAZ_SLEW);
	if(fAZ_SLEW > 0.0) fCompAZ_SLEW = -fCompAZ_SLEW;
	
	fFinal_AZ = m_AntStatus.m_fAzimuth + fAZ_SLEW;	

		//Use the long route if the antenna encounters the cable limit while moving.
	if((fFinal_AZ < m_ConfigD.m_fMin_Azimuth) && (fAZ_SLEW < 0.0) || 
		(fFinal_AZ > m_ConfigD.m_fMax_Azimuth) && (fAZ_SLEW > 0.0))
	{
		fAZ_SLEW = fCompAZ_SLEW;
	}
	else if(wDiraction == m_nDummy_Arg)		//If it case of non-tracking move
	{
		if((fabs(m_AntStatus.m_fAzimuth) > 180.0) || (fabs(fAZ_SLEW) > 45.0))
			if(fabs(m_AntStatus.m_fAzimuth + fAZ_SLEW) > 
				fabs(m_AntStatus.m_fAzimuth + fCompAZ_SLEW))
					fAZ_SLEW = fCompAZ_SLEW;
	}
	else if((fFinal_AZ < -90.0) && (wDiraction == CCW))
	{
		fAZ_SLEW = fCompAZ_SLEW;
		if(fAZ_SLEW < 0.0)	
			fAZ_SLEW += 720.0;
	}
	else if((fFinal_AZ > 90.0) && (wDiraction == CW))
	{
		fAZ_SLEW = fCompAZ_SLEW;
		if(fAZ_SLEW > 0.0)	
			fAZ_SLEW -= 720.0;
	}
		//Determine the maximum slew time required
	m_Prifile.m_fDeltaAZ = fAZ_SLEW;								//Total change in azimuth
	m_Prifile.m_fDeltaEL = fELCoordinate - m_AntStatus.m_fElevation;//Total change in elevation
	m_Prifile.m_fInitAZ = m_AntStatus.m_fAzimuth;					//Start AZ position
	m_Prifile.m_fInitEL = m_AntStatus.m_fElevation;					//Start EL position

	DOUBLE	anttSlewTime;

		//CalcTime calculates the max time required by the antenna to slew to a specified 
		//azimuth and elevation. The max slew rate and accelaration of the antenna are
		//considered in the calculation.
	CalcTime(anttSlewTime);

		//m_emstIntTime - time interval between commands
		//nMaxError - Max number of retries allowed.
	nMaxStaps = (INT)(anttSlewTime / m_ConfigD.m_IntTime + .49);



		//Calculate antenna slew in steps.
	dStepsFinalAZ = (m_AntStatus.m_fAzimuth + fAZ_SLEW)
		*m_ConfigD.m_fAZ_Factor;
	dStepsFinalEL = fELCoordinate*m_ConfigD.m_fEL_Factor;


		//Check if required antenna move
	if(fabs(m_Prifile.m_fDeltaAZ) < 0.06 && 
		fabs(m_Prifile.m_fDeltaEL) < 0.06)
			LOOP = FALSE;
	else
	{
			//Get the antenna status in steps and stow it in 
			//dPreviousAZ/dPreviousEL
		hr = GetStatus();

		dPreviousAZ = m_AntStatus.m_dwAZinSteps;
		dPreviousEL = m_AntStatus.m_dwELinSteps;

		dCurrentAZ = m_AntStatus.m_fAzimuth + fAZ_SLEW;	//Calculated angleAZ by MoveProfile()
		dCurrentEL = fELCoordinate;	//Calculated angleEL by MoveProfile()
			//Move antenna to requested position
		hr = Output(WRITE_AZEL,m_AntStatus.m_fAzimuth + fAZ_SLEW,
			fELCoordinate);
	}

	RefTime = ReadTime();	//Get current system time
	STOPED = FALSE;

		//From now antenna moves independently SARAntenna software
		//only monitoring its moving.
	
		//Monitoring loop. Loop until the antenna stops moving
	while(LOOP)
	{
			//In that point system flags must be chacked to find conditions
			//that requer output from the loop. That will be done later.
		if(m_bSHUT_DOWN)
		{
			SendAntMessage(MSG_INFORMATION,
				"Moving request stopped by EMS Stop command");
			sprintf(szBuffer,"s\r");
			Send(AZIMUTH,szBuffer,nCount = 2);
			Send(ELEVATION,szBuffer,nCount = 2);
			Output(STNDBY,0,0);
			return hr;
		}

			//Get the antenna current status
		GetStatus();

		if(m_AntStatus.m_bCWLimit || m_AntStatus.m_bCCWLimit 
			|| m_AntStatus.m_bHIGHLimit)
		{
			if(m_AntStatus.m_bCWLimit)
			{
				SendAntMessage(MSG_WARNING,
					"Antenna hit CW limit switch");
				hr = ANT_CW_LIMIT_HIT;
			}
			if(m_AntStatus.m_bCCWLimit)
			{
				SendAntMessage(MSG_WARNING,
					"Antenna hit CCW limit switch");
				hr = ANT_CCW_LIMIT_HIT;
			}
			if(m_AntStatus.m_bHIGHLimit)
			{
				SendAntMessage(MSG_WARNING,
					"Antenna hit HIGH limit switch");
				hr = ANT_HIGH_LIMIT_HIT;
			}
			return hr;
		}
			//Check antenna position at the current time.
		ProfileTime = (ReadTime() - RefTime)/1000.0;

			//MoveProfile calculates the azimuth and elevation (Prifile AngleEL/AngleAZ)
			//of the antenna at given time and profile in the slew sequence. The acceleration
			//and max vilocity of the antenna is taken into considaration when
			//determining the position of the antenna.
		MoveProfile(ProfileTime);

		dCurrentAZ = m_Prifile.m_fAngleAZ;	//Calculated angleAZ by MoveProfile()
		dCurrentEL = m_Prifile.m_fAngleEL;	//Calculated angleEL by MoveProfile()

				//Locate ensures that diferance between calculated angle and real antenna
				//angle still within the beamwidth. Locate() cans retry(wait) depending on
				//value of MAX_RETRY befor declering an antenna fault.
		bError = ANT_INV_BEAMWIDTH == Locate(dCurrentAZ,dCurrentEL);

			//If error number greater then nMaxError exit loop
		if(bError)
		{
			nErrCount++;
			if(nErrCount > nMaxStaps)
				SendAntMessage(MSG_INFORMATION,
				"Losing track of antenna - outside beamwidth");
		}


			//We've two stages befor and after profile data signals to stop. 
			//If profile is not accurate antenna may moves after stop and we've
			//wait til stops..
		if(!STOPED)
		{	//befor profile's stop
				//Handle antenna get stuck in the middle of the way
				//Dalay same time before getting out of the loop
			if(m_AntStatus.m_dwAZinSteps == dPreviousAZ && 
				m_AntStatus.m_dwELinSteps == dPreviousEL
					&& m_AntStatus.m_dwAZinSteps != dStepsFinalAZ && 
						m_AntStatus.m_dwELinSteps != dStepsFinalEL)
			{
				static INT iStuckErrCount;
				//Sleep(1000);
				//anttSlewTime += 1;
				iStuckErrCount++;
				LOOP = iStuckErrCount <= nMaxStaps;
				if(!LOOP)
					SendAntMessage(MSG_LOG,"Antenna stopped befor reaching destination");
			}
			else
			{
					//No problem so far. Check if antenna reaches the destination
				STOPED = (m_AntStatus.m_dwAZinSteps == (LONG)dStepsFinalAZ) && 
					(m_AntStatus.m_dwELinSteps == (LONG)dStepsFinalEL);
				if(STOPED)
				{
					tStopTime = ReadTime();
					SendAntMessage(MSG_LOG,"Wait til antenna doesn't move anymore");
				}
			}
		}
		if(STOPED)
		{	//Stage two after profile signaled to stop
			if(m_AntStatus.m_dwAZinSteps == dPreviousAZ && 
				m_AntStatus.m_dwELinSteps == dPreviousEL)
					LOOP = FALSE;	//Stoped, get out of loop
			else
			{						//Not stoped keep monitoring antenna 6Sec more.
				dPreviousAZ = m_AntStatus.m_dwAZinSteps;
				dPreviousEL = m_AntStatus.m_dwELinSteps;

				tStopElepsedTime = (ReadTime() - tStopTime)/1000;

				if(tStopElepsedTime > 6.0)	//Wait 6 seconds befor declaring error
				{
					SendAntMessage(MSG_WARNING,"Trouble stopping antenna after homing.");
					//Stop motors
					sprintf(szBuffer,"R0\r");
					hr = Send(AZIMUTH,szBuffer,nCount = 3);
					hr = Send(ELEVATION,szBuffer,nCount = 3);
					//Purge();
					return ANT_CANT_STOP_ANTENNA;
				}
			}
		}
		dPreviousAZ = m_AntStatus.m_dwAZinSteps;
		dPreviousEL = m_AntStatus.m_dwELinSteps;
	}	//End while loop


	if(hr != EMS_OK)
	{
			//Report error and poot antenna in to the standby mode
		SendAntMessage(MSG_WARNING,"Antenna monitoring loop fault.");
		Output(STNDBY,dCurrentAZ,dCurrentEL);
	}
	else
	{
			//Antenna O.K.
		SendAntMessage(MSG_LOG, "Antenna move completed.");
	}

	//Purge();

	return hr;

}


	//This function waits til specific number of characters resived
	//through specific port or elapsed time lase then 180 msec,
	//meanwhile display notification functions are throwing.
RS232Error CSARAntenna::IdleFunction(Win32Port *port)
{
	DOUBLE sTime = ReadTime();
	DOUBLE ElapsedTime = 0;
	INT stam;

	while((port->RXSpaceUsed() && ElapsedTime < 180) ||
		ElapsedTime < 180)
	{
		//port->IdleFunction();	//Run port idle function
		//LocNotify(m_DispAZ, m_DispEL);
		//ErrLocNotify(m_ErrorDispAZ,m_ErrorDispEL);
		ElapsedTime += ReadTime() - sTime;
		sTime = ReadTime();
		Sleep(10);
	}

	if(!(stam = port->RXSpaceUsed()))
		return RS232_TIMEOUT;
	else
		return RS232_SUCCESS;
}
/*
RS232Error CSARAntenna::IdleFunction(Win32Port *port)
{
	CHAR Buff[20];
	CHAR seps[] = "\r";
	DOUBLE sTime = ReadTime();

	for(port->Peek(Buff,20);!strtok(Buff,seps)&&
		ElapsedTime < 130;port->Peek(Buff,20))
	{
		//port->IdleFunction();	//Run port idle function
		//LocNotify(m_DispAZ, m_DispEL);
		//ErrLocNotify(m_ErrorDispAZ,m_ErrorDispEL);
		ElapsedTime += ReadTime() - sTime;
		sTime = ReadTime();
	}
	if(!port->RXSpaceUsed())
		return RS232_TIMEOUT;
	else
		return RS232_SUCCESS;
}
*/
#define StrToLong StrToInt

LONG CSARAntenna::ReadIoStatus(INT Channel)
{
	EMS_RESULT hr;
	CHAR szBuffer[20];
	char seps[]   = "Kk ,\t\n";
	char *token;
	DWORD nCount;
	INT	  stam;

	sprintf(szBuffer,"k\r");
	nCount = strlen(szBuffer);
	hr = Send(Channel,szBuffer,nCount);

	token = strtok(szBuffer,seps);
	
	if(token)
		return stam = atol(token);
	else
		return m_hr = hr;
}

EMS_RESULT CSARAntenna::SetFileToTrackData(TRACKDATA& TrackData)
{
	::EnterCriticalSection(&m_TrackDataLock);

	TRACKDATA TempTrackData = m_TrackData;
	m_TrackData = TrackData;

	EMS_RESULT						hr = EMS_OK;
	HANDLE							hf;
	CEMSTime						EMSTimeObject;
	list<lpAZEL_FORMAT>::iterator	i; 		//list iterator number
	DWORD							nBRead;	//Number of bytes readed from file
	lpAZEL_FORMAT					pAzelVector;
	EMSESUVECTOR					esuVector;


	hf = CreateFile(m_TrackData.m_szFileName,GENERIC_READ,0,
		(LPSECURITY_ATTRIBUTES)NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	if(hf != INVALID_HANDLE_VALUE)
	{
		ReadFile(hf,&(m_TrackData.m_ulSatelliteID),sizeof(ULONG),&nBRead,NULL);
		ReadFile(hf,&(m_TrackData.m_emsAOS),sizeof(EMSTIME),&nBRead,NULL);
		ReadFile(hf,&(m_TrackData.m_AzelInterval),sizeof(ULONG),&nBRead,NULL);
		ReadFile(hf,&(m_TrackData.m_Records),sizeof(ULONG),&nBRead,NULL);
		
			//delete list of vectors if present
		for (i = m_TrackData.m_AzelRecordsList.begin(); i != 
			m_TrackData.m_AzelRecordsList.end();)
		{
			delete *i;
			++i;
			m_TrackData.m_AzelRecordsList.pop_front();
		}

		for(INT nStepCount = 0;nStepCount < (INT)m_TrackData.m_Records;
			nStepCount++)
		{
			pAzelVector = new AZEL_FORMAT;

			ReadFile(hf,&esuVector,sizeof(EMSESUVECTOR),&nBRead,NULL);

			pAzelVector->m_East = esuVector.fEast;
			pAzelVector->m_North = esuVector.fNorth;
			pAzelVector->m_Up = esuVector.fUp;

			m_TrackData.m_AzelRecordsList.insert(
				m_TrackData.m_AzelRecordsList.end(),pAzelVector);
		}
		m_TrackData.m_AzelInterval *= 1000;

		CloseHandle(hf);

		m_TrackData.m_AzelStart = 0.0;
		m_TrackData.m_AzelEnd = m_TrackData.m_AzelInterval*m_TrackData.m_Records;
		EMSTimeObject.SetTime(m_TrackData.m_emsAOS);
		m_TrackData.m_EMSTimeStart = EMSTimeObject; 
		m_TrackData.m_EMSTimeEnd = EMSTimeObject.
			AddSeconds((float)TrackData.m_AzelInterval/1000*m_TrackData.m_Records);

	}
	else
		hr = EMS_CANT_OPEN_AZELFILE;


	TrackData = m_TrackData;
	m_TrackData = TempTrackData;
	::LeaveCriticalSection(&m_TrackDataLock);
	return hr;
}


void CSARAntenna::SetTimingToTrackData(TRACKDATA& TrackData)
{

	::EnterCriticalSection(&m_TrackDataLock);
	TRACKDATA TempTrackData = m_TrackData;
	m_TrackData = TrackData;

	SYSTEMTIME		SysTime;
	CEMSAntTime		EMSCurrTimeObject;
	CEMSAntTime		EMSStartTimeObject(m_TrackData.m_EMSTimeStart);//UTC
	INT				nRecordPers = m_TrackData.m_Records - 1;
	EMSTIMEFIELDS	timeFields;
	char			szBuff[260];
	string			strBuff;
	static			PrevStep = 1000;

	GetSystemTime(&SysTime);
	EMSCurrTimeObject.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
		SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);

	for(m_TrackData.m_StartStep = 0;m_TrackData.m_StartStep<nRecordPers;
			m_TrackData.m_StartStep++)
	{
		if(((m_TrackData.m_WaitTime = EMSCurrTimeObject.
			SecondsDifferent(EMSStartTimeObject)) - m_ConfigD.m_ulProgramDelay/1000) > 0)
			break;
		EMSStartTimeObject.AddSeconds((float)m_TrackData.m_AzelInterval/1000);
	}

	m_TrackData.m_EMSTimeStart = EMSStartTimeObject;

	if(m_TrackData.m_StartStep < nRecordPers && m_TrackData.m_StartStep > 0 &&
		PrevStep != m_TrackData.m_StartStep)
	{
		StepLostNotify(m_TrackData.m_StartStep);
		PrevStep = m_TrackData.m_StartStep;
	}

	if(m_TrackData.m_WaitTime >= 0)
	{
		if(!m_TrackData.m_StartStep)
		{
			timeFields = EMSStartTimeObject - EMSCurrTimeObject;
			strBuff = "AOS in ";
		}
		else
		{
			timeFields = EMSStartTimeObject - EMSCurrTimeObject;
			timeFields.nSecond -= m_ConfigD.m_ulProgramDelay/1000;
			sprintf(szBuff,"In step %d for ",m_TrackData.m_StartStep);
			strBuff = szBuff;
		}
	}
	else
	{
		timeFields = EMSCurrTimeObject - EMSStartTimeObject;
		strBuff = "You're late for ";
	}

	if(timeFields.nYear)
	{
		sprintf(szBuff,"%d Y ",timeFields.nYear);
		strBuff += szBuff;
	}

	if(timeFields.nMonth)
	{
		sprintf(szBuff,"%d M ",timeFields.nMonth);
		strBuff += szBuff;
	}

	if(timeFields.nDay)
	{
		sprintf(szBuff,"%d D ",timeFields.nDay);
		strBuff += szBuff;
	}

	if(timeFields.nHour)
	{
		sprintf(szBuff,"%d H ",timeFields.nHour);
		strBuff += szBuff;
	}

	if(timeFields.nMinute)
	{
		sprintf(szBuff,"%d Min ",timeFields.nMinute);
		strBuff += szBuff;
	}

	if(timeFields.nSecond)
	{
		sprintf(szBuff,"%d Sec ",timeFields.nSecond);
		strBuff += szBuff;
	}

	strcpy(szBuff,strBuff.c_str());

	//if(m_TrackData.m_Mode != DISPLAY)		//Idle mode
		//SendAntMessage(MSG_LOG,szBuff);
	//else
	//{
		m_TrackDlgMsg = strBuff;
		TrackDlgMsgNotify();
	//}

	TrackData = m_TrackData;
	m_TrackData = TempTrackData;
	::LeaveCriticalSection(&m_TrackDataLock);
}

DOUBLE CSARAntenna::GetRampTime(INT Divider,INT M,DWORD F,DWORD V)
{
	DWORD		StartVelocity = F/Divider;
	const DWORD	*pStartTable = LookUpTable;
	DOUBLE		RampTime = 0;
	INT			TableSize = sizeof(LookUpTable)/sizeof(DWORD);
	INT			nCount;


	if(StartVelocity > *pStartTable)
		for(nCount = 0;nCount < TableSize && 
			StartVelocity >= *pStartTable;nCount++, pStartTable++);

	if(V >= *pStartTable)
	{
		if(StartVelocity > *LookUpTable)
			RampTime = 1.0/(DOUBLE)StartVelocity;
		while(V > *pStartTable)
			RampTime += 1.0/(DOUBLE)*pStartTable++;
		RampTime += 1.0/(DOUBLE)V;
	}

	RampTime *= M;
	RampTime *= Divider;

	return RampTime;
}

EMS_RESULT CSARAntenna::OldFashionTrack(TRACKDATA& TrackData)
{
	::EnterCriticalSection(&m_TrackDataLock);
	TRACKDATA TempTrackData = m_TrackData;
	m_TrackData = TrackData;

	EMS_RESULT			hr = EMS_FALSE;
//	CHAR*				lpFile = 0;

	INT					nDiraction;				//Diraction to move antenna 
	DWORD				dwRecords = 0;			//Number of vector records in AZEL file
//	DWORD				nBRead;					//Number of bytes readed from file
//	lpAZEL_FORMAT		lpAzelRec;				//Pointer to AZEL record vector
	list<lpAZEL_FORMAT>::iterator i; 			//list iterator number
	BOOL				bZenMove;				//Move antenna done in zenith mode
	DOUBLE				tCurrTime;				//Current time
	DOUBLE				dAZ;					//Calculeted antenna azimuth
	DOUBLE				dEL;					//Calculeted antenna elevation
	DOUBLE				dCurrAZ;				//Current calculeted antenna azimuth
	DOUBLE				dCurrEL;				//Current calculeted antenna elevation
	DOUBLE				fAzDiff;				//Delta azimuth to be move
	DOUBLE				fElDiff;				//Delta elevation to be move
	BOOL				bZenithMoved = FALSE;	//Move antenna done in zenith mode

	DOUBLE				PrevAZNormPos = 0.0;
	DOUBLE				PrevELNormPos = 0.0;
	MOVE				AZMove,ELMove;

/*		//Move antenna to home position 
	SendAntMessage(MSG_LOG, "Move antenna to the HOME position before tracking.");
	if(Home() != EMS_OK)
	{
		SendAntMessage(MSG_WARNING, "UNable home antenna for tracking");
		Reset();
		if(CheckAnt() != EMS_OK)
		{
			Sleep(1000);

			Purge();

			return EMS_FALSE;
		}
		SendAntMessage(MSG_WARNING, "Reset repair the problem");
	}

	if(lpFile = Trim(lpszAZELfile)) 
	{
		SendAntMessage(MSG_WARNING, "Wrong AZEL file name");
		return EMS_FALSE;
	}
		//Put antenna in to the stendby mode
	Output(RMT_STNDBY,0.0,0.0);

	m_hFile = CreateFile(lpFile,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
			//File opened for reading read azel configuration
		BOOL bResult = ReadFile(m_hFile,&m_TrackData.m_AzelStart,sizeof(DOUBLE),&nBRead,NULL);
		if(bResult && (nBRead == sizeof(DOUBLE)))
		{
			bResult = ReadFile(m_hFile,&m_TrackData.m_AzelInterval,sizeof(DWORD),&nBRead,NULL);
			//bResult = ReadFile(m_hFile,&m_TrackData.m_AzelOdap,sizeof(DWORD),&nBRead,NULL);
			//bResult = ReadFile(m_hFile,&m_TrackData.m_AzelRev,sizeof(DWORD),&nBRead,NULL);
			if(bResult && (nBRead == sizeof(DOUBLE))) 
				hr = EMS_OK;
		}
			//Read AZEL vectors in to the memmory and determine thay number
		do
		{
			lpAzelRec = new AZEL_FORMAT;
			bResult = ReadFile(m_hFile,lpAzelRec,sizeof(AZEL_FORMAT),&nBRead,NULL);
			if(bResult && (nBRead == sizeof(DOUBLE)))
			{
				m_TrackData.m_AzelRecordsList.insert(m_TrackData.m_AzelRecordsList.end(),lpAzelRec);
				dwRecords++;
			}
		}while(nBRead != sizeof(AZEL_FORMAT));

		m_TrackData.m_Records = dwRecords;

			//End of the file
		m_TrackData.m_AzelEnd = m_TrackData.m_AzelStart + (dwRecords - 1)*
			m_TrackData.m_AzelInterval;
			//if the current time already exceeds the end of the AZEL file
		if(ReadTime() > m_TrackData.m_AzelEnd)
		{
			SendAntMessage(MSG_LOG, "No longer current");
			Purge();
				//Put antenna in to the stendby mode
			Output(RMT_STNDBY,0,0);
				
			delete[] lpFile;
			return hr;
		}
*/
			//Now antenna is ready to tracking mode

			//Determine if zenith mode pass mast be implemented. if so, add one
			//sec for acceleration and one sec for deceleration

	ZenithCheck();
	if(m_ZenithMode.m_bMode)
	{
		SendAntMessage(MSG_LOG, "Zenith pass mode required!");
		bZenMove = FALSE;
		m_ZenithMode.m_fStar -= 1.0;
		m_ZenithMode.m_fEnd += 1.0;
	}
	else
		SendAntMessage(MSG_LOG, "No zenith pass mode required.");

		//Determine diraction of tracking
	TrackDir(nDiraction);

	m_TrackData.m_nDiraction = nDiraction;

	if(nDiraction == CW)
		SendAntMessage(MSG_LOG, "Clockwise satellite track.");
	else
		SendAntMessage(MSG_LOG, "Counter clockwise satellite track.");

		//Move antenna to the position where it should be at AOS time
	PassAngles(m_TrackData.m_AzelStart,PrevAZNormPos,PrevELNormPos);
	AZMove.Start = 0.0; AZMove.End = PrevAZNormPos;
	ELMove.Start = 0.0; ELMove.End = PrevELNormPos;
	CalSARMove(AZMove,ELMove,nDiraction);
				
		//Determine witch time is domenanty for calculation.
		tCurrTime = __max(ReadTime(),m_TrackData.m_AzelStart);
		GetStatus();
			//Determine AZ and El in given time.
		PassAngles(tCurrTime,dAZ,dEL);

			//Determine the time neaded for catching the setllite if time over AOS
		tCurrTime = ReadTime() + 1.0 + 
			__max(fabs((DMOD(dAZ - m_AntStatus.m_fAzimuth + 540.0,360.0) - 180.0)/
				(DOUBLE)m_ConfigD.m_fAZ_Rate), 
				fabs(dEL - m_AntStatus.m_fElevation)/(DOUBLE)m_ConfigD.m_fEL_Rate);
				
			//Determine dominance time.
		tCurrTime = __max(tCurrTime,m_TrackData.m_AzelStart);
		if(m_ZenithMode.m_bMode && tCurrTime > m_ZenithMode.m_fStar)
		{
					//We now going to track zanith mode and befor that mode started
			tCurrTime = __max(tCurrTime, m_ZenithMode.m_fEnd);
			bZenithMoved = TRUE;
		}

		PassAngles(tCurrTime,dAZ,dEL);

		SendAntMessage(MSG_LOG, "Position antenna to start satellite pass");

			//OK move antenna to psition befor tracking
		hr = Move(dAZ,dEL,nDiraction);


		BOOL bLoop;				//Tracking loop control

		if(hr == EMS_OK)
		{
				//Initialize for antenna motion checking, and wait until AOS time comes...
			bLoop = TRUE;
			GetStatus();
			dAZ =m_AntStatus.m_fAzimuth;
			dEL = m_AntStatus.m_fElevation;
				//Wait if neaded until AOS time will came.
			while(ReadTime() < m_TrackData.m_AzelStart)
				Sleep(1000);	//One second
			tCurrTime = ReadTime();  
		}
		else
		{
				//Could not move to AOS
			bLoop = FALSE;
			hr = ANT_NOT_REACHED_AOS;
		}

		tCurrTime = ReadTime();

			//Track main loop
		while(tCurrTime > m_TrackData.m_AzelStart && tCurrTime < m_TrackData.m_AzelEnd && bLoop)
		{
			if(m_bSHUT_DOWN)
			{
				SendAntMessage(MSG_WARNING, "Processed request to sut down.");
				bLoop = FALSE;
			}
			GetStatus();
			dCurrAZ = m_AntStatus.m_fAzimuth;
			dCurrEL = m_AntStatus.m_fElevation;

				//Get the current time
			tCurrTime = ReadTime();

				//Check if zenith mode came
			if(m_ZenithMode.m_bMode && !bZenithMoved && tCurrTime > m_ZenithMode.m_fStar && 
				tCurrTime < m_ZenithMode.m_fEnd)
			{
				bZenithMoved = TRUE;

					//Stop through rate command
				Output(RATE_AZEL,0.0,0.0);
				Sleep(1000);

				SendAntMessage(MSG_INFORMATION, "Begin zenith processing.");

					//Get the position of the antenna at the end of the zenith period
					//and use regular move command to drive it there. The error is ignired
					//here because it will be processed when the zenith time is over.
				PassAngles(m_ZenithMode.m_fEnd,dAZ,dEL);

					//Move directly to the end of zenith mode
				hr = IndtMove(dAZ,dEL);
				if(hr != EMS_OK)
					SendAntMessage(MSG_WARNING, "Zenith processing failed.");

					//Just in case..., Loop and wait until the zenith time is up then
					//go back
				while(ReadTime() < m_ZenithMode.m_fEnd);

				GetStatus();
				dCurrAZ = m_AntStatus.m_fAzimuth;
				dCurrEL = m_AntStatus.m_fElevation;

				if(m_bSHUT_DOWN)
				{
					SendAntMessage(MSG_WARNING, "Processed request to sut down.");
					bLoop = FALSE;
				}
			}

				//Compute the vilocities for ACUs
			PassAngles(ReadTime() + m_ConfigD.m_fLatency,dAZ,dEL);

				//Calculate azimuth and elevation moving rate using the retrieval time
				//Retrieval time is the time, in seconds, that we look in the future as
				//target time for a specific location. From those numbers, the target
				//rate is determined.
			fAzDiff = (DMOD(dAZ - dCurrAZ + 540.0,360.0) - 180.0)/m_ConfigD.m_fLatency;
			fElDiff = (dEL - dCurrEL)/m_ConfigD.m_fLatency;

			if(fabs(fElDiff) > fabs(m_ConfigD.m_fEL_Rate))
				fElDiff = SIGN(m_ConfigD.m_fEL_Rate, fElDiff);

				//send the command buffer to the ACU
			Output(RATE_AZEL,fAzDiff,fElDiff);

			hr = CheckMotion();

				//If a fault occured then abort the tracking and raise the antenna 
				//fault condition
			if(hr != EMS_OK)
			{
				bLoop = FALSE;		//Order to end current antenna track.
					//Stop antenna 
				Output(RATE_AZEL,0.0,0.0);
					//Deley 2 seconds
				Sleep(2000);
					//Release RS-232 TR and DR buffers
				Purge();
					//Put antenna in stndby mode
				Output(STNDBY,0.0,0.0);

			}
		}
//	}

	if(hr == EMS_OK)
	{
			//Stop antenna 
		Output(RATE_AZEL,0.0,0.0);
		Sleep(2000);
		Purge();
		Output(STNDBY,0.0,0.0);
	}
//	delete[] lpFile;

	TrackData = m_TrackData;
	m_TrackData = TempTrackData;
	::LeaveCriticalSection(&m_TrackDataLock);
	return hr;
}

EMS_RESULT CSARAntenna::OldFashionTrack1(TRACKDATA& TrackData)
{
	EMS_RESULT						hr = EMS_FALSE;
	SYSTEMTIME						SysTime;
	CEMSAntTime						EMSCurrTimeObject, EMSStartTrackTimeObject;
	CEMSAntTime						EMSTempTimeObject;
	DWORD							dwTimeFromStart = 0;
	INT								nDiraction;				//Diraction to move antenna 
//	list<lpAZEL_FORMAT>::iterator	i; 						//list iterator number
	BOOL							bZenMove;				//Move antenna done in zenith mode
	DOUBLE							PrevAZNormPos = 0.0;
	DOUBLE							PrevELNormPos = 0.0;
	MOVE							AZMove,ELMove;
	BOOL							bZenithMoved;			//Move antenna done in zenith mode
	BOOL							bLoop = TRUE;
	CHAR							Buff[256];

	GetStatus();
		//If the current time already exceeds the end of the AZEL file,
		//ignor the track request.
	GetSystemTime(&SysTime);
	EMSCurrTimeObject.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
		SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);
	EMSTempTimeObject.SetTime(TrackData.m_EMSTimeStart);
	EMSTempTimeObject.AddSeconds((float)((TrackData.m_Records - 1)*
		TrackData.m_AzelInterval/1000));

	if(EMSCurrTimeObject > EMSTempTimeObject)
		return hr = EMS_TOO_LATE_FOR_TRACK;

		//Determine if zenith mode pass mast be implemented. if so, add one
		//sec for acceleration and one sec for deceleration

	ZenithCheck();
	if(m_ZenithMode.m_bMode)
	{
		SendAntMessage(MSG_LOG, "Zenith pass mode required!");
		bZenMove = FALSE;
		m_ZenithMode.m_fStar -= 1.0;
		m_ZenithMode.m_fEnd += 1.0;
	}
	else
		SendAntMessage(MSG_LOG, "No zenith pass mode required.");

		//Determine diraction of tracking
	TrackDir(nDiraction);

	m_TrackData.m_nDiraction = nDiraction;

	if(nDiraction == CW)
		SendAntMessage(MSG_LOG, "Clockwise satellite track.");
	else
		SendAntMessage(MSG_LOG, "Counter clockwise satellite track.");

		//Move antenna to the position where it should be at the time when
		//the move is completed.
	if(EMSCurrTimeObject > TrackData.m_EMSTimeStart)
	{
		EMSTempTimeObject.SetTime(TrackData.m_EMSTimeStart);
		dwTimeFromStart = (DWORD)EMSTempTimeObject.SecondsDifferent(EMSCurrTimeObject);				
	}

		//Find if that stap is OK 
	PassAngles(TrackData.m_AzelStart+dwTimeFromStart,PrevAZNormPos,PrevELNormPos);

	AZMove.Start = 0.0;	AZMove.End = PrevAZNormPos;
	ELMove.Start = 0.0;	ELMove.End = PrevELNormPos;

	CalSARMove(AZMove,ELMove,nDiraction);

	if((PrevAZNormPos < 180) &&(PrevAZNormPos > 90))
		PrevAZNormPos -= 360;

	if((PrevAZNormPos < 270) &&(PrevAZNormPos > 180))
		PrevAZNormPos += 360;

	PrevAZNormPos = AZMove.End;
	PrevELNormPos = ELMove.End;

	EMSTempTimeObject.SetTime(EMSCurrTimeObject);

	EMSTempTimeObject.AddSeconds((float)(1.0 + 
		__max(fabs((PrevAZNormPos - m_AntStatus.m_fAzimuth)/(DOUBLE)m_ConfigD.m_fAZ_Rate), 
				fabs(PrevELNormPos - m_AntStatus.m_fElevation)/(DOUBLE)m_ConfigD.m_fEL_Rate)));

	if(EMSTempTimeObject > TrackData.m_EMSTimeStart)
	{
		CEMSAntTime		EMSStartTimeObject(TrackData.m_EMSTimeStart);
		EMSStartTrackTimeObject.SetTime(EMSTempTimeObject);		
		dwTimeFromStart = (DWORD)EMSStartTimeObject.SecondsDifferent(EMSStartTrackTimeObject);
	}
	else
		EMSStartTrackTimeObject.SetTime(TrackData.m_EMSTimeStart);

	if(m_ZenithMode.m_bMode && dwTimeFromStart > m_ZenithMode.m_fStar)
	{
			//We now going to track zanith mode and befor that mode started
		EMSTempTimeObject.SetTime(TrackData.m_EMSTimeStart);
		EMSTempTimeObject.AddSeconds((float)m_ZenithMode.m_fEnd);
		if(EMSTempTimeObject > EMSStartTrackTimeObject)
		{
			EMSStartTrackTimeObject.SetTime(EMSTempTimeObject);
			dwTimeFromStart = m_ZenithMode.m_fEnd;
		}
		bZenithMoved = TRUE;
	}

	PassAngles(TrackData.m_AzelStart+dwTimeFromStart,PrevAZNormPos,PrevELNormPos);

	AZMove.Start = 0.0;	AZMove.End = PrevAZNormPos;
	ELMove.Start = 0.0;	ELMove.End = PrevELNormPos;

	CalSARMove(AZMove,ELMove,nDiraction);

	if((PrevAZNormPos < 180) &&(PrevAZNormPos > 90))
		PrevAZNormPos -= 360;

	if((PrevAZNormPos < 270) &&(PrevAZNormPos > 180))
		PrevAZNormPos += 360;

	PrevAZNormPos = AZMove.End;
	PrevELNormPos = ELMove.End;

	sprintf(Buff,"Position antenna to the start: AZ%f,EL%f",
		PrevAZNormPos,PrevELNormPos);
	SendAntMessage(MSG_TRACE,Buff);

	hr = Move(PrevAZNormPos,PrevELNormPos,nDiraction);

	GetSystemTime(&SysTime);
	EMSCurrTimeObject.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
		SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);

	if(hr == EMS_OK)
		Sleep(EMSCurrTimeObject.SecondsDifferent(EMSStartTrackTimeObject)*1000);
	else
		return hr;

	GetSystemTime(&SysTime);
	EMSCurrTimeObject.SetTime(SysTime.wYear,SysTime.wMonth,SysTime.wDay,SysTime.wHour,
		SysTime.wMinute,SysTime.wSecond,SysTime.wMilliseconds*1000);

	while(EMSCurrTimeObject > TrackData.m_EMSTimeStart &&
		CEMSAntTime(TrackData.m_EMSTimeEnd) > EMSCurrTimeObject && bLoop)
	{
		if(m_bSHUT_DOWN)
		{
			SendAntMessage(MSG_WARNING, "Processed request to sut down.");
			break;
		}

		GetStatus();
	}

	
	return hr;
}
