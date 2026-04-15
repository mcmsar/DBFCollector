/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __DBF_SCHEDULER_H__
#define __DBF_SCHEDULER_H__

#include "eservice.h"
//#include "logclient.h"
#include "emsclock.h"
#include <string>
#include "DBFPhaseHandling.h"   //Smruti added - 22-april-2020

class CEMSDBFSchedulerService : public CEMSService
{
	public:
		CEMSDBFSchedulerService();
		virtual ~CEMSDBFSchedulerService();

		virtual const wchar_t* GetComponent() { return L"DBFPassScheduler"; }


	protected:
		virtual EMS_RESULT StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv );
		virtual EMS_RESULT StopEMSService( void );
		virtual EMS_RESULT PauseEMSService( void );
		virtual EMS_RESULT ContinueEMSService( void );
		virtual EMS_RESULT InstallEMSService( void );
		virtual EMS_RESULT RemoveEMSService( void );
protected:	
		virtual EMS_RESULT StartService( DWORD dwArgc, LPTSTR *lpszArgv );
		virtual EMS_RESULT StopService( void );
		virtual EMS_RESULT PauseService( void );
		virtual EMS_RESULT ContinueService( void );
		virtual EMS_RESULT InstallService( void );
		virtual EMS_RESULT RemoveService( void );
		virtual BOOL StopIsAccepted( void );

	private: // methods
		EMS_RESULT _ServiceProcessLoop(void);
		void _ReleaseObjects( void );
		BOOL _OkayToStop( void );
		void _Init();

		void _DoIdle();
		bool _TimeToGeneratePassSched();
		void _GenerateNewPassSched( EMSTIME startTime, EMSTIME endTime );

	protected:
		static const wchar_t* ms_cwszPassSchedConfig;
		static const wchar_t* ms_cwszPlatesConfig;
		static const wchar_t* ms_cwszPlateConfig;
		static const wchar_t* ms_cwszPlateConfigFile;
		static const wchar_t* ms_cwszSatsConfig;
		static const wchar_t* ms_cwszSatConfig;

		//Smruti added
		static std::string ms_szDBFPhaseDir;

	private: //data
		HANDLE					m_hEventStop;
		HANDLE					m_hEventSignal;
		BOOL					m_bPaused;
		DWORD					m_dwRegister;
		DWORD					m_dwThreadID;
		ULONG					m_ulMinObjCount;
		BOOL					m_bStopEnabled;

		double                  m_dTimeSpan;

		EMSTIME					m_LastGenTime;
//		EMSTIME					m_TimeEnd;
		CEMSSystemClock         m_oSysTime;

		std::wstring			m_owszPlateConfigFile;
		std::wstring			m_owszSatsConfig;

		CDBFPhaseHandling		m_oDbfPhaseBuff;
};

#endif // __DBF_SCHEDULER_H__

