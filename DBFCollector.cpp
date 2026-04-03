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


#pragma warning(disable:4786)

#include <windows.h>

#include <stdio.h> // debug
#include "ESecDesc.h"



#include "DBFCollector.h"
#include "emscmreg.h"
#include "aobjbase.h"

#include <initguid.h>
//#include "logclient.h"
#include "emsconfg.h"
#include "convutility.h"
#include "configurationaccessor.h"
#include "logregistrysettings.h"
#include "emsexcpt.h"
#include "leosite.h"
#include "CollectionObject.h"

const TCHAR c_szServiceName[] = TEXT("EMSDBFCollector");
const TCHAR c_szComponent[]		= TEXT("EMS DBF Collector Service");
const TCHAR c_szDescription[]	= TEXT("EMSDBFCollector");
const ULONG c_ulTimeoutInterval	= 1000 * 5;	// every 5 seconds
const ULONG c_ulSleepInterval	= 	250;
const ULONG c_ulShutdownWait		= 500; // wait one half (1/2) second


// {578AC019-B669-4afc-A038-60CF3D643B08}
DEFINE_GUID(APPID_EMSDBFCollector, 
0x578ac019, 0xb669, 0x4afc, 0xa0, 0x38, 0x60, 0xcf, 0x3d, 0x64, 0x3b, 0x8);


CEMSDBFCollectorService::CEMSDBFCollectorService() : m_dwRegister(0), m_ulMinObjCount(0), 
													 m_bStopEnabled(FALSE),	m_hEventSignal(INVALID_HANDLE_VALUE), 
													 m_hEventStop(INVALID_HANDLE_VALUE)		
{
	

	m_hEventSignal = CreateEvent( NULL, FALSE, FALSE, NULL );

	m_hEventStop = CreateEvent( NULL, FALSE, FALSE, NULL );
}

CEMSDBFCollectorService::~CEMSDBFCollectorService()
{
	if ( m_hEventStop != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hEventStop );
		m_hEventStop = INVALID_HANDLE_VALUE;
	}

	if ( m_hEventSignal != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hEventSignal );
		m_hEventSignal = INVALID_HANDLE_VALUE;
	}

	_ReleaseObjects();
}

void	
CEMSDBFCollectorService::_ReleaseObjects( void )
{
}


EMS_RESULT 
CEMSDBFCollectorService::_ServiceProcessLoop( void )
{
	EMS_RESULT hr = EMS_OK;
	CEMSCollectionObject* poCS = NULL;

	try
	{
		BOOL bStopped = FALSE;

		poCS = new CEMSCollectionObject();

		if(poCS->Initialize(4,0) )
		{
			HANDLE hEvent[2];
			hEvent[ 0 ] = m_hEventStop;
			hEvent[ 1 ] = m_hEventSignal;

			poCS->Start();

			Sleep(2000);

			int iCounter = 0;

			while ( !bStopped )
			{
				DWORD dwResult = WaitForMultipleObjects( 2, hEvent, FALSE, c_ulTimeoutInterval );
				iCounter++;
				
				if( iCounter > 5 )
				{
					//dwResult = WAIT_OBJECT_0; //snl commented for testing
				}

				switch ( dwResult )
				{
					case WAIT_OBJECT_0:		// asked to stop 
						bStopped = TRUE;
						poCS->Stop();
						Sleep(10000);
						break;

					case WAIT_OBJECT_0 + 1:	// signalled!
						break;

					default:
					case WAIT_TIMEOUT:
						if ( _OkayToStop() != m_bStopEnabled )
						{
							// this will recheck and reset SERVICE_ACCEPT_STOP
							ReportServiceStatus( EMS_SERVICE_RUNNING );
						}
						break;
				}
			}
		}
	}
	catch( CEMSException& e )
	{
//		LogException( e );
		hr = e.GetErrCode();
	}
	catch( ... )
	{
		hr = EMS_UNKNOWN_ERROR;
	}

	if( poCS )
	{
		delete poCS;
		poCS = NULL;
	}

	return hr;
}

EMS_RESULT 
CEMSDBFCollectorService::InstallEMSService( void )
{
	EMS_RESULT hr = EMS_OK;

	CEMSComRegistry comReg;
	
	if ( IsService() )
	{
		hr = comReg.RegisterLocalService( (CLSID*)&APPID_EMSDBFCollector, c_szServiceName);
	}
	else
	{
		hr = comReg.RegisterLocalServer( (CLSID*)&APPID_EMSDBFCollector ); // DEBUG
	}

	if ( ( hr == EMS_OK ) && IsService() )
	{
		hr = CEMSService::InstallEMSService();
	}

	return hr;
}

EMS_RESULT 
CEMSDBFCollectorService::RemoveEMSService( void )
{
	return CEMSService::RemoveEMSService();
}


EMS_RESULT 
CEMSDBFCollectorService::StopEMSService( void ) 
{

	ReportServiceStatus( EMS_SERVICE_STOP_PENDING );

	SetEvent( m_hEventStop );

	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFCollectorService::PauseEMSService( void )
{
	if ( !m_bPaused )
	{
		m_bPaused = TRUE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFCollectorService::ContinueEMSService( void )
{
	if ( m_bPaused )
	{
		m_bPaused = FALSE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK;
}

BOOL 
CEMSDBFCollectorService::StopIsAccepted( void )
{
	//m_bStopEnabled = _OkayToStop();
	//return m_bStopEnabled;
	return true;
}

BOOL 
CEMSDBFCollectorService::_OkayToStop( void )
{
	return ( CApiObjBase::ObjectCount() == 0 );
}

EMS_RESULT 
CEMSDBFCollectorService::StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv ) 
{
	EMS_RESULT hr = EMS_OK;
	int nMaxRetries = c_ulShutdownWait / c_ulSleepInterval, nRetries = 0;

	m_dwThreadID = GetCurrentThreadId();

	CEMSSecurityDescriptor secDesc;
	secDesc.InitializeFromThreadToken();

	hr = CoInitializeSecurity( secDesc, -1, NULL, NULL,
				RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, 
				NULL, EOAC_NONE, NULL);

	// Don't throw an exception.  CoInit may have been called earlier and will then
	// fail (harmlessly) here.
//	if( FAILED(hr) )
//	{
//		THROW_RUNTIME_EXCEPTION(hr);
//	}

//	_Init();


	ReportServiceStatus( EMS_SERVICE_RUNNING );

	m_ulMinObjCount = CApiObjBase::ObjectCount();


	hr = _ServiceProcessLoop();

	if( FAILED(hr) )
	{
		// Log a warning.
	}

	_ReleaseObjects();

	while ( CApiObjBase::ObjectCount() && ( nRetries++ < nMaxRetries ) )
	{
		Sleep( c_ulSleepInterval );
	}

	return hr;
}

void 
CEMSDBFCollectorService::_Init()
{
	IEMSSiteInfo* pSite = NULL;

	// If the CM is available then get the LUT ID and inform the logger of it.
	EMS_RESULT hr = CoCreateInstance( CLSID_EMSSiteInfo, NULL, CLSCTX_ALL, 
								IID_IEMSSiteInfo, (void**) &pSite );

	if( EMS_OK == hr &&
		pSite )
	{
		ULONG ulLutID = 0;

		hr = pSite->GetLutID( &ulLutID );

		if( EMS_OK == hr )
		{
//			SetLutID( ulLutID );
		}

		pSite->Release();
		pSite = NULL;
	}

//	SetProcessID( EMSLOGCAT_DBFCollector );
}
#include "TimeElapsed.h"
std::ofstream out( "c:\\temp\\logfile");

std::streambuf* RedirectToFile()
{
// open output file
	if(!out.is_open())
		throw std::runtime_error("failed to open logfile");
	// redirect, save former target
	std::streambuf* orig_cout = std::cout.rdbuf( out.rdbuf());
	return orig_cout;
}
void UndoRedirect( std::streambuf* orig_cout)
{
	// undo redirection
	std::cout.flush();
	std::cout.rdbuf(orig_cout);
	out.close();
}

int main(int argc, char* argv[])
{
	//CEMSLogClient oLogClientInit;
	
	bool bCOMInit = false;
		
	try
	{
			//std::streambuf* orig_cout = RedirectToFile();

	EMS_RESULT hr = CoInitializeEx( 0, COINIT_MULTITHREADED );

		// This call should always succeed.
		if( hr != EMS_OK )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
		else
			bCOMInit = true;
		CTimeElapsed::fileOpen( );
		std::wstring owszLogConfig = CEMSLogRegistrySettings::GetPropertiesPath();
		
		//oLogClientInit.InitializeDefault();

		//if( !owszLogConfig.empty() )
		//	oLogClientInit.InitializeLogging( owszLogConfig.c_str() );

//		oLogClientInit.InitializeProcess( 
//#if defined(UNICODE) || defined(_UNICODE)
//			c_szServiceName, 
//#else
//			CEMSConversionUtil::ConvertToString( c_szServiceName ).c_str(),
//#endif
//			0, 0 );
//
		{
			CEMSDBFCollectorService oDBFCollectorService;
			std::cout << "Testing svc " << std::endl;
			//snl test
			//::Sleep( 13000 );
			//end test
			if( argc > 1 &&
				0 == stricmp( argv[1], "-debug" ) )
			{
				oDBFCollectorService.RunAsService( FALSE );	// for DEBUGGING
			}

			oDBFCollectorService.AllowPause( FALSE );
			oDBFCollectorService.Run( c_szServiceName, argc, argv );
		}
			std::cout << "Line 2 " << std::endl;

	//UndoRedirect(orig_cout);

		CTimeElapsed::fileClose( );


	}
	catch( CEMSException& e )
	{
//		oLogClientInit.LogException( e );
	}
	catch( ... )
	{

	}

//	oLogClientInit.Shutdown();

	if( bCOMInit )
		CoUninitialize();


	return 0; 
}
