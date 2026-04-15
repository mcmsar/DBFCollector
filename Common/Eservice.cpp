/********************************************************************
*	Module:			EService.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSService class
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
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include <eservice.h>

typedef struct tagSERVICE_PRIVATE_DATA
{
	SERVICE_STATUS 	status;
	SERVICE_STATUS_HANDLE	sshStatusHandle;
} SERVICE_PRIVATE_DATA, *LPSERVICE_PRIVATE_DATA;

CEMSService *CEMSService::m_lpThis = 0;

CEMSService::CEMSService()
{
	m_dwCheckPoint = 0;
	m_bService = TRUE;
	m_bPaused = FALSE;
	m_bAllowPause = TRUE;
	m_bInteractiveProcess = TRUE;

	m_lpszServiceName = 0;
	m_lpThis = this;
	m_lpPrivateData = (LPVOID) new SERVICE_PRIVATE_DATA;

	if ( m_lpPrivateData )
	{
	  	LPSERVICE_PRIVATE_DATA lpData = (LPSERVICE_PRIVATE_DATA)m_lpPrivateData;

		memset( m_lpPrivateData, 0, sizeof( SERVICE_PRIVATE_DATA ) );

		lpData->status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	}
}

CEMSService::~CEMSService()
{
	if ( m_lpszServiceName )
	{
		delete m_lpszServiceName;
		m_lpszServiceName = 0;
	}

	if ( m_lpPrivateData )
	{
		delete m_lpPrivateData;
		m_lpPrivateData = 0;
	}
}

EMS_RESULT CEMSService::Run( LPCTSTR lpcszServiceName, DWORD dwArgc, LPTSTR *lpszArgv, BOOL bDebug )
{
	EMS_RESULT hr = EMS_OK;

#ifdef EMS_DEBUG
	DebugStr("::Run");
	DebugStr( lpcszServiceName );
#endif	// EMS_DEBUG

	_SetServiceName( lpcszServiceName );

	if ( (dwArgc > 1) && ((*lpszArgv[1] == '-') || (*lpszArgv[1] == '/')) )
	{
		if ( _tcsicmp( _T("install"), lpszArgv[1]+1 ) == 0 )
		{
#if _MSC_VER >= 1600 
			hr = InstallEMSService();
#else
			hr = InstallService();
#endif
		}
		else if ( ( _tcsicmp( _T("uninstall"), lpszArgv[1]+1 ) == 0 ) ||
						( _tcsicmp( _T("remove"), lpszArgv[1]+1 ) == 0 ) )
		{
#if _MSC_VER >= 1600 
			hr = RemoveEMSService();
#else
			hr = RemoveService();
#endif
		}
		else if ( _tcsicmp( _T("debug"), lpszArgv[1]+1 ) == 0 )
		{
			m_bService = FALSE;

			hr = _DispatchService( dwArgc, lpszArgv );
		}
		else
		{
			hr = _DispatchService( dwArgc, lpszArgv );
		}
	}
	else
	{
		hr = _DispatchService( dwArgc, lpszArgv );
	}

	return hr;
}

EMS_RESULT CEMSService::_DispatchService( DWORD dwArgc, LPTSTR *lpszArgv )
{
	EMS_RESULT hr = EMS_OK;

	if ( _IsWindowsNT() && m_bService ) 	// must be NT and Service==TRUE
	{
		SERVICE_TABLE_ENTRY st[] =
		{
			{ m_lpszServiceName, (LPSERVICE_MAIN_FUNCTION)_ServiceMainEntry },
			{ NULL, NULL }
		};

		if ( !StartServiceCtrlDispatcher( st ) ) 
		{
			m_bService = FALSE;

		//	SetConsoleCtrlHandler( _ConsoleCtrlHandlerEntry, TRUE );

#if _MSC_VER >= 1600 
		hr = StartEMSService( dwArgc, lpszArgv );
#else
		hr = StartService( dwArgc, lpszArgv );
#endif
	//		hr = EMS_UNKNOWN_ERROR;
		}
	}
	else
	{
		m_bService = FALSE;

		// Console Ctrl+C/Break handling is registered by the application
		// (DBFCollector.cpp CtrlHandler).  Registering a second handler here
		// would take LIFO priority and block the application's handler.
		// SetConsoleCtrlHandler( _ConsoleCtrlHandlerEntry, TRUE );

#if _MSC_VER >= 1600
		hr = StartEMSService( dwArgc, lpszArgv );
#else
		hr = StartService( dwArgc, lpszArgv );
#endif
	}
	return hr;
}


EMS_RESULT CEMSService::ReportServiceStatus( EMS_SERVICE_STATE newState, 
									DWORD dwWin32ExitCode, DWORD dwWaitHint )
{
	EMS_RESULT hr = EMS_OK;

//	printf("CEMSService::ReportServiceStatus\n");

	if ( m_bService && m_lpPrivateData )	// only report the status if in ServiceMode
	{
	  	LPSERVICE_PRIVATE_DATA lpData = (LPSERVICE_PRIVATE_DATA)m_lpPrivateData;

		lpData->status.dwWin32ExitCode = dwWin32ExitCode;

		lpData->status.dwWaitHint = dwWaitHint;

		switch ( newState )
		{
			case EMS_SERVICE_RUNNING:
				lpData->status.dwCurrentState = SERVICE_RUNNING;
				break;

			case EMS_SERVICE_STOPPED:
				lpData->status.dwCurrentState = SERVICE_STOPPED;
				break;

			case EMS_SERVICE_START_PENDING:
				lpData->status.dwCurrentState = SERVICE_START_PENDING;
				break;

			case EMS_SERVICE_STOP_PENDING:
				lpData->status.dwCurrentState = SERVICE_STOP_PENDING;

				break;
			case EMS_SERVICE_CONTINUE_PENDING:
				lpData->status.dwCurrentState = SERVICE_CONTINUE_PENDING;
				break;

			case EMS_SERVICE_PAUSE_PENDING:
				lpData->status.dwCurrentState = SERVICE_PAUSE_PENDING;
				break;

			case EMS_SERVICE_PAUSED:
				lpData->status.dwCurrentState = SERVICE_PAUSED;
				break;
		}

		switch ( lpData->status.dwCurrentState )
		{
			case SERVICE_RUNNING:
			case SERVICE_STOPPED:
				lpData->status.dwCheckPoint = 0;
				lpData->status.dwControlsAccepted = 0;

#if _MSC_VER >= 1600 
				if ( StopEMSIsAccepted() )
#else
				if ( StopIsAccepted() )
#endif
					lpData->status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

				if ( m_bAllowPause )
					lpData->status.dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;

				break;

			case SERVICE_START_PENDING:
				lpData->status.dwCheckPoint = m_dwCheckPoint++;
				lpData->status.dwControlsAccepted = 0;
				break;

			default:
				lpData->status.dwCheckPoint = m_dwCheckPoint++;
				lpData->status.dwControlsAccepted = 0;

#if _MSC_VER >= 1600 
				if ( StopEMSIsAccepted() )
#else
				if ( StopIsAccepted() )
#endif
				lpData->status.dwControlsAccepted = SERVICE_ACCEPT_STOP;

				if ( m_bAllowPause )
					lpData->status.dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE;

				break;
		}
		//printf("CEMSService::ReportServiceStatus 2 \n");

		SetServiceStatus( lpData->sshStatusHandle, &(lpData->status) );

		//printf("CEMSService::ReportServiceStatus 3 \n");
	}

	return hr;
}

BOOL CEMSService::_SetServiceName( LPCTSTR lpcszServiceName )
{
	if ( m_lpszServiceName )
	{
		delete m_lpszServiceName;
     		m_lpszServiceName = 0;
	}

	if ( lpcszServiceName && *lpcszServiceName )
	{
		m_lpszServiceName = new TCHAR[ _tcslen( lpcszServiceName ) + 1 ];

		if ( m_lpszServiceName )
		{
			_tcscpy( m_lpszServiceName, lpcszServiceName );
		}
	}
	return ( m_lpszServiceName != 0 );
}

#if _MSC_VER >= 1600 
EMS_RESULT CEMSService::InstallEMSService( void )
#else
EMS_RESULT CEMSService::InstallService( void )
#endif
{
	EMS_RESULT hr = EMS_FALSE;
	TCHAR szPath[512];

	if ( GetModuleFileName( 0, szPath, sizeof(szPath) / sizeof(TCHAR) ) )
 	{
		SC_HANDLE schSCManager = OpenSCManager( 0, 0, SC_MANAGER_ALL_ACCESS );

		if ( schSCManager )
		{
			DWORD dwServiceType = SERVICE_WIN32_OWN_PROCESS;

#ifndef _64BITS
			if ( m_bInteractiveProcess )
				dwServiceType |= SERVICE_INTERACTIVE_PROCESS;
#endif

			SC_HANDLE schService = CreateService( schSCManager, m_lpszServiceName,
				m_lpszServiceName, SERVICE_ALL_ACCESS, dwServiceType,
				SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, szPath, 0, 0, 0, 0, 0 );

			if ( schService )
			{
				hr = EMS_OK;				
				CloseServiceHandle( schService );
			}

			CloseServiceHandle( schSCManager );
		}
	}

	return hr;
}

#if _MSC_VER >= 1600 
EMS_RESULT CEMSService::RemoveEMSService( void )
#else
EMS_RESULT CEMSService::RemoveService( void )
#endif
{
	EMS_RESULT hr = EMS_OK;
	SC_HANDLE schSCManager = OpenSCManager( 0, 0, SC_MANAGER_ALL_ACCESS );

	if ( schSCManager )
	{
		SC_HANDLE schService = OpenService( schSCManager, m_lpszServiceName,
			SERVICE_ALL_ACCESS );

		if ( schService )
		{
			SERVICE_STATUS ssStatus;       // current status of the service

        if ( ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )
        {
           Sleep( 1000 );

           while( QueryServiceStatus( schService, &ssStatus ) )
           {
              if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
              {
                    Sleep( 1000 );
              }
              else
                    break;
           }

				if ( ssStatus.dwCurrentState == SERVICE_STOPPED )
				{
					hr = EMS_OK;
				}
        }

        // now remove the service
			if ( DeleteService( schService  ) )
			{
			}
			CloseServiceHandle( schService );
		}

		CloseServiceHandle( schSCManager );
	}
	return hr;
}

EMS_RESULT CEMSService::_StartService( DWORD dwArgc, LPTSTR *lpszArgv )
{
	EMS_RESULT hr = EMS_OK;

#ifdef EMS_DEBUG
	DebugStr( "_StartService - Entrance");
#endif // EMS_DEBUG

 	ReportServiceStatus( EMS_SERVICE_START_PENDING );

#if _MSC_VER >= 1600
	hr = StartEMSService( dwArgc, lpszArgv );
#else
	hr = StartService( dwArgc, lpszArgv );
#endif

	ReportServiceStatus( EMS_SERVICE_STOPPED );

#ifdef EMS_DEBUG
	DebugStr( "_StartService - Exit");
#endif // EMS_DEBUG

	return hr;
}

EMS_RESULT CEMSService::_StopService( void )
{
	EMS_RESULT hr = EMS_OK;

	ReportServiceStatus( EMS_SERVICE_STOP_PENDING );

#if _MSC_VER >= 1600 
	hr = StopEMSService();
#else
	hr = StopService();
#endif

	return hr;
}

#if  _MSC_VER >= 1600 
EMS_RESULT CEMSService::PauseEMSService( void ) 
#else
EMS_RESULT CEMSService::PauseService( void ) 
#endif
{ 
 	ReportServiceStatus( EMS_SERVICE_PAUSED );

	m_bPaused = TRUE;

	return EMS_OK; 
}

#if  _MSC_VER >= 1600
EMS_RESULT CEMSService::ContinueEMSService( void ) 
#else
EMS_RESULT CEMSService::ContinueService( void ) 
#endif
{ 
 	ReportServiceStatus( EMS_SERVICE_RUNNING );

	m_bPaused = FALSE;

	return EMS_OK; 
}

void CEMSService::_ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv )
{
	LPSERVICE_PRIVATE_DATA lpData = (LPSERVICE_PRIVATE_DATA)m_lpPrivateData;

	if ( lpData )
	{
		lpData->sshStatusHandle	= RegisterServiceCtrlHandler( m_lpszServiceName, 
													_ServiceControlHandlerEntry );
		_StartService( dwArgc, lpszArgv );
	}
}

void WINAPI CEMSService::_ServiceMainEntry( DWORD dwArgc, LPTSTR *lpszArgv )
{
	if ( m_lpThis )
		m_lpThis->_ServiceMain( dwArgc, lpszArgv );
}

EMS_RESULT CEMSService::_ForceAcceptStop( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_bService && m_lpPrivateData )	// only report the status if in ServiceMode
	{
	  	LPSERVICE_PRIVATE_DATA lpData = (LPSERVICE_PRIVATE_DATA)m_lpPrivateData;

		lpData->status.dwControlsAccepted |= SERVICE_ACCEPT_STOP;

		SetServiceStatus( lpData->sshStatusHandle, &(lpData->status) );
	}

	return hr;
}

void CEMSService::_ServiceControlHandler( DWORD dwControl )
{
	LPSERVICE_PRIVATE_DATA lpData = (LPSERVICE_PRIVATE_DATA)m_lpPrivateData;

	switch ( dwControl )
	{
		case SERVICE_CONTROL_PAUSE:
			if ( m_bAllowPause)
#if _MSC_VER >= 1600 
				PauseEMSService();
#else
				PauseService();
#endif
			break;

		case SERVICE_CONTROL_CONTINUE:
#if _MSC_VER >= 1600 
			ContinueEMSService();
#else
			ContinueService();
#endif
			break;

		case SERVICE_CONTROL_STOP:
			_StopService();
			break;

		case EMS_SERVICE_FORCE_ACCEPT_STOP:
			_ForceAcceptStop();
			break;

		default:
			break;
	}

//	ReportServiceStatus( lpData->status.dwCurrentState );
}    

BOOL CEMSService::_ConsoleCtrlHandler( DWORD dwCtrlType )
{
	BOOL bHandled = FALSE;

	switch( dwCtrlType )
	{
		case CTRL_BREAK_EVENT:  // use Ctrl+C or Ctrl+Break to simulate
		case CTRL_C_EVENT:      // SERVICE_CONTROL_STOP in debug mode
		case CTRL_CLOSE_EVENT:	

			_StopService();

			bHandled = TRUE;

			break;
	}
	return bHandled;
}

BOOL WINAPI CEMSService::_ConsoleCtrlHandlerEntry( DWORD dwType )
{
	return ( m_lpThis ) ? m_lpThis->_ConsoleCtrlHandler( dwType ) : FALSE;
}

void WINAPI CEMSService::_ServiceControlHandlerEntry( DWORD dwControl )
{
	if ( m_lpThis )
		m_lpThis->_ServiceControlHandler( dwControl );
}

BOOL CEMSService::_IsWindowsNT( void )
{
	OSVERSIONINFO osvi;

	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	return (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT);
}


#ifdef EMS_DEBUG

void CEMSService::DebugStr( LPCTSTR lpcszMsg, DWORD dwValue )
{
	if ( lpcszMsg && *lpcszMsg )
	{
	 	TCHAR szTemp[256];

		if ( m_lpszServiceName ) 
			wsprintf( szTemp, TEXT("%s_dbg.txt"), m_lpszServiceName );
		else
			_tcscpy( szTemp, TEXT("CEMSService_dbg.txt") );

	}
}

#endif // EMS_DEBUG 


