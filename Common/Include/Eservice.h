/********************************************************************
*	Module:			EService.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface to CEMSService class
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

	0.0	2001 Apr 10	rvw	start

********************************************************************/
#ifndef INC_ESERVICE
#define INC_ESERVICE

#include "emstypes.h"
#include "emserror.h"

typedef enum _EMS_SERVICE_STATE {
	EMS_SERVICE_STOPPED                = 0,
	EMS_SERVICE_START_PENDING          = 1,
	EMS_SERVICE_STOP_PENDING           = 2,
	EMS_SERVICE_RUNNING                = 3, 
	EMS_SERVICE_CONTINUE_PENDING       = 4, 
	EMS_SERVICE_PAUSE_PENDING          = 5,
	EMS_SERVICE_PAUSED                 = 6
} EMS_SERVICE_STATE;

#define EMS_SERVICE_FORCE_ACCEPT_STOP	( 132 )	// user-defined control

class CEMSService
{
public:
	CEMSService();
	virtual ~CEMSService();

	EMS_RESULT Run( LPCTSTR lpcszServiceName, DWORD dwArgc, LPTSTR *lpszArgv, BOOL bDebug=FALSE );

	inline void RunAsService( BOOL bService = TRUE ) { m_bService = bService; }
	inline void AllowPause( BOOL bAllow = TRUE ) { m_bAllowPause = bAllow; }
	inline void InteractiveProcess( BOOL bInteractive = TRUE ) { m_bInteractiveProcess = bInteractive; } 
	inline BOOL IsService( void ) { return m_bService; }

protected:
#if _MSC_VER >= 1600 
	virtual EMS_RESULT StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv ) { return EMS_OK; }
	virtual EMS_RESULT StopEMSService( void ) { return EMS_OK; }
	virtual EMS_RESULT PauseEMSService( void );
	virtual EMS_RESULT ContinueEMSService( void );
	virtual EMS_RESULT InstallEMSService( void );
	virtual EMS_RESULT RemoveEMSService( void );
	virtual BOOL StopEMSIsAccepted( void ) { return TRUE; }
#else
	virtual EMS_RESULT StartService( DWORD dwArgc, LPTSTR *lpszArgv ) { return EMS_OK; }
	virtual EMS_RESULT StopService( void ) { return EMS_OK; }
	virtual EMS_RESULT PauseService( void );
	virtual EMS_RESULT ContinueService( void );
	virtual EMS_RESULT InstallService( void );
	virtual EMS_RESULT RemoveService( void );
	virtual BOOL StopIsAccepted( void ) { return TRUE; }
#endif

	EMS_RESULT ReportServiceStatus( EMS_SERVICE_STATE newState, DWORD dwWin32ExitCode=0,
                         DWORD dwWaitHint=0 );

	inline BOOL IsPaused( void ) { return m_bPaused; }
	inline BOOL IsInteractiveProcess( void ) { return m_bInteractiveProcess; }
	inline BOOL IsPauseAllowed( void ) { return m_bAllowPause; }

#ifdef EMS_DEBUG
	void DebugStr( LPCTSTR lpcszMsg, DWORD dwValue = 0 );
#endif // EMS_DEBUG

private: // methods
	EMS_RESULT _StartService( DWORD dwArgc, LPTSTR *lpszArgv );
	EMS_RESULT _StopService( void );
	EMS_RESULT _DispatchService( DWORD dwArgc, LPTSTR *lpszArgv );
	EMS_RESULT _ForceAcceptStop( void );
	BOOL _SetServiceName( LPCTSTR lpcszServiceName );
	void _ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv );
	void _ServiceControlHandler( DWORD dwControl );
	BOOL _ConsoleCtrlHandler( DWORD dwType );
	BOOL _IsWindowsNT( void );

	static void WINAPI _ServiceControlHandlerEntry( DWORD dwControl );
	static void WINAPI _ServiceMainEntry( DWORD dwArgc, LPTSTR *lpszArgv );
	static BOOL WINAPI _ConsoleCtrlHandlerEntry( DWORD dwType );

private: // data
	BOOL	m_bService;
	BOOL	m_bPaused;
	BOOL	m_bAllowPause;
	BOOL	m_bInteractiveProcess;
	LPTSTR m_lpszServiceName;
	LPVOID m_lpPrivateData;
	DWORD m_dwCheckPoint;

	static CEMSService *m_lpThis;		// only doing this because of ServiceMain

};

#endif // INC_ESERVICE

