/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#include "servicecontroller.h"
#include "emsexcpt.h"
#include "messages.h"
#include "convutility.h"
#include <crtdbg.h>


const ULONG CEMSServiceController::ms_ulDefaultWaitTime = 10000;	// 10 seconds to wait for the service to start
const ULONG CEMSServiceController::ms_culWaitBetweenChecks = 100;

CEMSServiceController::CEMSServiceController() : m_ulWaitTime( ms_ulDefaultWaitTime )
{
}

CEMSServiceController::CEMSServiceController( const wchar_t* cwszName, const ULONG culWaitTime ) : 
																		m_wszServiceName( cwszName ),
																		m_ulWaitTime( culWaitTime )
{
}

CEMSServiceController::CEMSServiceController( const CEMSServiceController& x ) :
																		m_wszServiceName( x.m_wszServiceName ),
																		m_ulWaitTime( x.m_ulWaitTime )
{
}

CEMSServiceController::~CEMSServiceController()
{
}

bool 
CEMSServiceController::Start()
{
	SERVICE_STATUS ssInitialStatus;
	return Start( ssInitialStatus );
}

bool 
CEMSServiceController::Start( SERVICE_STATUS& ssInitialStatus )
{
	bool bRet = false;
	memset( &ssInitialStatus, 0, sizeof(SERVICE_STATUS) );

	_ASSERTE( !m_wszServiceName.empty() );

	if( m_wszServiceName.empty() )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

#ifdef WIN32

	SC_HANDLE schSCManager = 0;
	SC_HANDLE schService = 0;

	try
	{
		if ( _Open( schSCManager, schService ) == true )
		{
			SERVICE_STATUS ssStatus;
			memset( &ssStatus, 0, sizeof(SERVICE_STATUS) );

			if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) )
			{
				if( DWORD dwLastError = GetLastError() != ERROR_SERVICE_NOT_ACTIVE )
				{
					throw CEMSException( HRESULT_FROM_WIN32( dwLastError ) );
				}
				else
				{
					ssStatus.dwCurrentState = SERVICE_STOPPED;
				}
			}

			switch( ssStatus.dwCurrentState )
			{
				case SERVICE_STOPPED:
					if( !StartService( schService, 0, 0 ) )
					{
						throw CEMSException( HRESULT_FROM_WIN32( GetLastError() ) );
					}
					break;
			}

			// Save the initial status
			ssInitialStatus = ssStatus;

			DWORD dwStartWaiting = GetTickCount();

			while( SERVICE_RUNNING != ssStatus.dwCurrentState && ( GetTickCount() < ( dwStartWaiting + m_ulWaitTime ) ) )
			{
				if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) )
				{
					// This test for error doesn't seem dependable.

					//if( DWORD dwLastError = GetLastError() != ERROR_SERVICE_NOT_ACTIVE )
					//{
					//	throw CEMSException( HRESULT_FROM_WIN32( dwLastError ) );
					//}
					
				}

				if( SERVICE_RUNNING != ssStatus.dwCurrentState )
				{
					Sleep( ms_culWaitBetweenChecks );
				}
			}

			if( SERVICE_RUNNING == ssStatus.dwCurrentState )
				bRet = true;

			_Close( schSCManager, schService );
		}

	}
	catch( ... )
	{
		_Close( schSCManager, schService );
		throw;
	}

#endif

	return bRet;

}

void 
CEMSServiceController::SetServiceName( const wchar_t* cwszName )
{
	if( cwszName )
	{
		m_wszServiceName = cwszName;
	}
}

void 
CEMSServiceController::SetWaitTime( const ULONG culWaitTime )
{
	if( culWaitTime > 0 )
	{
		m_ulWaitTime = culWaitTime;
	}
}

bool 
CEMSServiceController::IsRunning()
{
	bool bRet = false;

	_ASSERTE( !m_wszServiceName.empty() );

	if( m_wszServiceName.empty() )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

#ifdef WIN32

	SC_HANDLE schSCManager = 0;
	SC_HANDLE schService = 0;

	try
	{
		if ( _Open( schSCManager, schService ) == true )
		{
			SERVICE_STATUS ssStatus;
			memset( &ssStatus, 0, sizeof(SERVICE_STATUS) );

			if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) )
			{
				if( DWORD dwLastError = GetLastError() != ERROR_SERVICE_NOT_ACTIVE )
				{
					throw CEMSException( HRESULT_FROM_WIN32( dwLastError ) );
				}
				else
				{
					ssStatus.dwCurrentState = SERVICE_STOPPED;
				}
			}

			switch( ssStatus.dwCurrentState )
			{
				case SERVICE_RUNNING:
					bRet = true;
					break;
			}

			_Close( schSCManager, schService );
		}
	}
	catch( ... )
	{
		_Close( schSCManager, schService );
		throw;
	}

#endif

	return bRet;
}

bool 
CEMSServiceController::IsRegistered()
{
	bool bRet = false;

	_ASSERTE( !m_wszServiceName.empty() );

	if( !m_wszServiceName.empty() )
	{

#ifdef WIN32

		SC_HANDLE schSCManager = 0;
		SC_HANDLE schService = 0;

		try
		{
			if ( _Open( schSCManager, schService ) == true )
			{
				bRet = true;
				_Close( schSCManager, schService );
			}
		}
		catch( CEMSException& e )
		{
			if( EMS_GENERAL_CANNOT_OPEN_SERVICE == e.GetErrCode() )
				bRet = false;
			else
				throw;
		}
		catch( ... )
		{
			throw;	
		}
	}

#endif

	return bRet;
}

// ControlService() returns an error code if called in a separate function?
/*
SERVICE_STATUS
CEMSServiceController::_GetStatus( SC_HANDLE& schService )
{
	SERVICE_STATUS ssStatus;
	memset( &ssStatus, 0, sizeof(SERVICE_STATUS) );

	if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) )
	{
		if( DWORD dwLastError = GetLastError() != ERROR_SERVICE_NOT_ACTIVE )
		{
			throw CEMSException( HRESULT_FROM_WIN32( dwLastError ) );
		}
	}
	return ssStatus;
}
*/

bool
CEMSServiceController::_Open( SC_HANDLE& schSCManager, SC_HANDLE& schService )
{
	bool bRet = false;

	_ASSERTE( !m_wszServiceName.empty() );

	schSCManager = OpenSCManager( 0, 0, SC_MANAGER_ALL_ACCESS );

	if( !schSCManager )
	{
		throw CEMSException( EMS_GENERAL_CANNOT_OPEN_SCM );
	}

#if defined(UNICODE) || defined(_UNICODE)
	schService = OpenService( schSCManager, m_wszServiceName.c_str(), SERVICE_ALL_ACCESS );
#else
	schService = OpenService( schSCManager, CEMSConversionUtil::ConvertToString( m_wszServiceName.c_str() ).c_str(), SERVICE_ALL_ACCESS );
#endif

	if( !schService )
	{
		// Ticket 97832: If can't find the service name, do not fail.
		// Systems running Sybase 11 do not require ASANYs_LEOLUT600. 
		if ( ( GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST ) &&
#if defined(UNICODE) || defined(_UNICODE)
			 ( strcmp( m_wszServiceName.c_str(), "ASANYs_LEOLUT600" ) == 0 ) )
#else
			 ( strcmp( CEMSConversionUtil::ConvertToString(m_wszServiceName.c_str()).c_str(), "ASANYs_LEOLUT600" ) == 0 ) )
#endif
		{
			// Don't raise an alarm and don't fail.
		}
		else
		{
			CEMSLogMsgParam oLogParam;
			oLogParam.AddString( m_wszServiceName.c_str() );

			throw CEMSException( EMS_GENERAL_CANNOT_OPEN_SERVICE, oLogParam );
		}
	}
	else
	{
		bRet = true;
	}

	return bRet;
}

void
CEMSServiceController::_Close( SC_HANDLE& schSCManager, SC_HANDLE& schService )
{
	if ( schService )	
	{
		CloseServiceHandle( schService );
		schService = 0;
	}
	if ( schSCManager )	
	{
		CloseServiceHandle( schSCManager );
		schSCManager = 0;
	}
}

bool 
CEMSServiceController::Stop()
{
	bool bRet = false;

	_ASSERTE( !m_wszServiceName.empty() );

	if( m_wszServiceName.empty() )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

#ifdef WIN32

	SC_HANDLE schSCManager = 0;
	SC_HANDLE schService = 0;

	try
	{
		if ( _Open( schSCManager, schService ) == true )
		{
			SERVICE_STATUS ssStatus;
			memset( &ssStatus, 0, sizeof(SERVICE_STATUS) );

			if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) )
			{
				if( DWORD dwLastError = GetLastError() != ERROR_SERVICE_NOT_ACTIVE )
				{
					throw CEMSException( HRESULT_FROM_WIN32( dwLastError ) );
				}
				else
				{
					ssStatus.dwCurrentState = SERVICE_STOPPED;
				}
			}

			switch( ssStatus.dwCurrentState )
			{
				case SERVICE_RUNNING:
					if ( !ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )
					{
						throw CEMSException( HRESULT_FROM_WIN32( GetLastError() ) );
					}
					break;
			}

			// Wait until actually stopped ...
			DWORD dwStartWaiting = GetTickCount();

			while( SERVICE_STOPPED != ssStatus.dwCurrentState 
				&& ( GetTickCount() < ( dwStartWaiting + m_ulWaitTime ) ) )
			{
				if( !ControlService( schService, SERVICE_INTERROGATE, &ssStatus ) ) 
				{
					if ( GetLastError() == ERROR_SERVICE_NOT_ACTIVE )
					{
						ssStatus.dwCurrentState = SERVICE_STOPPED;
					}
					// otherwise ignore... apparently not dependable
				}

				if( SERVICE_STOPPED != ssStatus.dwCurrentState )
				{
					Sleep( ms_culWaitBetweenChecks );
				}
			}

			if( SERVICE_STOPPED == ssStatus.dwCurrentState )
				bRet = true;

			_Close( schSCManager, schService );
		}
	}
	catch( ... )
	{
		_Close( schSCManager, schService );
		throw;
	}

#endif

	return bRet;

}
