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



#include "DBFPassScheduler.h"
#include "emscmreg.h"
#include "aobjbase.h"

#include <initguid.h>
#include "DBFPointingAngles.h"
#include "DBFNullPointing.h"
#include "logclient.h"
#include "emsconfg.h"
#include "convutility.h"
#include "configurationaccessor.h"
#include "logregistrysettings.h"
#include "emsexcpt.h"
#include "leosite.h"
#include "emsDBFDataMgr.h"
#include "emsconst.h"
#include "registrysettings.h"
#include "LogHelper.h"

#include <iostream>

const TCHAR c_szServiceName[] = TEXT("EMSDBFPassScheduler");
const TCHAR c_szComponent[]		= TEXT("EMS DBF Pass Scheduler Service");
const TCHAR c_szDescription[]	= TEXT("EMSDBFPassScheduler");
const ULONG c_ulTimeoutInterval	= 1000 * 10;// every 1 minute
const ULONG c_ulSleepInterval	= 	250;
const ULONG c_ulShutdownWait		= 500; // wait one half (1/2) second

const double c_dTimeSpan = 20.0; // 10 hours

const wchar_t* CEMSDBFSchedulerService::ms_cwszPassSchedConfig = L"scheduler_config";
const wchar_t* CEMSDBFSchedulerService::ms_cwszPlatesConfig = L"DBFplates";
const wchar_t* CEMSDBFSchedulerService::ms_cwszPlateConfig = L"plate";
const wchar_t* CEMSDBFSchedulerService::ms_cwszPlateConfigFile = L"config_file";
const wchar_t* CEMSDBFSchedulerService::ms_cwszSatsConfig = L"satellites";
const wchar_t* CEMSDBFSchedulerService::ms_cwszSatConfig = L"sat";

//Smruti added
std::string CEMSDBFSchedulerService::ms_szDBFPhaseDir = "\\\\1.1.1.91\\c$\\HGT\\DBFBufferPhase\\";


// {2B55E302-83AF-42d0-A091-25DCF64152FE}
DEFINE_GUID(APPID_EMSDBFPassScheduler,
0x2b55e302, 0x83af, 0x42d0, 0xa0, 0x91, 0x25, 0xdc, 0xf6, 0x41, 0x52, 0xfe);


CEMSDBFSchedulerService::CEMSDBFSchedulerService() : m_dwRegister(0), m_ulMinObjCount(0), m_bStopEnabled(FALSE),
								m_hEventSignal(INVALID_HANDLE_VALUE), m_hEventStop(INVALID_HANDLE_VALUE)		
{
	m_dTimeSpan = c_dTimeSpan;
	m_LastGenTime.intTime = 0L;

	m_hEventSignal = CreateEvent( NULL, FALSE, FALSE, NULL );

	m_hEventStop = CreateEvent( NULL, FALSE, FALSE, NULL );
}

CEMSDBFSchedulerService::~CEMSDBFSchedulerService()
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
CEMSDBFSchedulerService::_ReleaseObjects( void )
{
}

void	
CEMSDBFSchedulerService::_DoIdle()
{
	if( _TimeToGeneratePassSched() )
	{

		// generate starting the next our but set the last time to hh:10.
		CEMSTime oTempTime = m_oSysTime.GetTime();
		EMSTIMEFIELDS tmTimeFields;
		oTempTime.GetTime( &tmTimeFields );

		CEMSTime  oCurrentTime( tmTimeFields.nYear, tmTimeFields.nMonth, tmTimeFields.nDay, tmTimeFields.nHour );
		
		m_LastGenTime = oCurrentTime;
		oTempTime.SetTimeNano(m_LastGenTime.intTime);
		m_LastGenTime = oTempTime.AddMinutes(10.0);

		CEMSTime  oStartTime = oCurrentTime;
		CEMSTime  oEndTime = oCurrentTime;

//		oStartTime.AddHours(1.0);
		//oEndTime.AddHours(m_dTimeSpan + 1.0); 
		oEndTime.AddHours(23.0);

		//oStartTime.AddHours(-36.0);
		//oEndTime.AddHours(-12.0);
	/*	CEMSTime  oTimeNow = CEMSSystemClock::GetTime();
		CEMSTime  oStartTime = oTimeNow.AddHours(int(1));;
		CEMSTime  oEndTime = oTimeNow.AddHours(int(24)); */

		//Smruti added for DBF Buffer phase - 22nd April 2020
		std::string szFileName = "";
		szFileName  = m_oDbfPhaseBuff.FindFileForCurrentHour(ms_szDBFPhaseDir);

		bool bProcessed = false;
		if(szFileName.size() > 0)
		{
			std::string szfullPath = ms_szDBFPhaseDir + szFileName;
			bProcessed = m_oDbfPhaseBuff.ReadDBFBufferPhaseFromCsv(szfullPath);
			//generate phases
			//function in new class to m_oDbfPhaseBuff.generateoffset, it will use vect data and 
			//if generate returns true,
			
			//	std::cout<<"File procesing failed "<<std::endl;
		}
	
		//Get the buffer
		//std::vector<EMSDBFBUFFER> vectDbfBuffer;
		//vectDbfBuffer.clear();
		//m_oDbfPhaseBuff.GetDBFPhaseBuffer(vectDbfBuffer);

		//Process the vector
		//double arrPhase[32];
		//int nRecordCount  = vectDbfBuffer.size();
		//for(int i = 0; i < nRecordCount; i++)
		//{
		//	int iDataSetType = vectDbfBuffer[i].iDataSetType;

		//	EMSTIME timeStamp = vectDbfBuffer[i].timeStamp;

		//	ULONG ulSatID = vectDbfBuffer[i].ulSatID;

		//	float fPlateAzimuth = vectDbfBuffer[i].fPlateAzimuth;

		//	float fPlateElevation = vectDbfBuffer[i].fPlateElevation;

		//	ULONG ulMaxFreqIndex = vectDbfBuffer[i].ulMaxFreqIndex;

		//	double dMaxPowerlevel = vectDbfBuffer[i].dMaxPowerlevel;

		//	memset(&arrPhase, 0, sizeof(arrPhase));
		//	memcpy(&arrPhase, &vectDbfBuffer[i].PhaseArray, sizeof(arrPhase));

		//}


		_GenerateNewPassSched( oStartTime, oEndTime );
	}
}

bool 
CEMSDBFSchedulerService::_TimeToGeneratePassSched()
{
	bool bRet = false;
	if( 0 == m_LastGenTime.intTime )
	{
		bRet = true;
	}
	else
	{
		// check one hour.
		CEMSTime oCurrentTime = m_oSysTime.GetTime();
		CEMSTime oNext(m_LastGenTime);
		oNext.AddHours(1.0);
		EMSTIME tmNext = oNext;
		EMSTIME tmCurrent = oCurrentTime;

		if( tmCurrent.intTime >= tmNext.intTime )
		{
			bRet = true;
		}
	}
	return bRet;
}


void
CEMSDBFSchedulerService::_GenerateNewPassSched( EMSTIME startTime, EMSTIME endTime )
{
	ULONG			  ulActual = 0;
	EMSDBFAZEL	      aAzEls[culMaxSats]={{0}};

	
	CEMSDBFDataMgr    oDMgr;

	EMSDBFARRAY  	  Plate;
	memset(&Plate, 0, sizeof(EMSDBFARRAY));

	EMS_RESULT hr = oDMgr.Initialize( m_owszPlateConfigFile.c_str() ); // plate number is set to one
	Plate = oDMgr.GetPlate();

	if( EMS_OK == hr )
	{
		CDBFPointingAngles oPA;
		CDBFNullPointing oNP;
		EMSDBFPASSRECORD	PassRecord;
//		EMSDBFPASSRECORDS	PassData;

		//double dScaleFactor = 32768; // 2^15
		double dScaleFactor = 4096; // 2^12 temporary test RR

		
		hr = oPA.Initialize(m_owszSatsConfig.c_str());

		hr = oNP.Initialize();

		oPA.SetPlate( &Plate );
		//apply new calculated biases
		//if(bProcessed)
		{
			if( m_oDbfPhaseBuff.GenerateBiasOffset( oPA ) )
				oPA.SetBiasOffset( m_oDbfPhaseBuff.GetBiasOffset() );
		}
		ULONG irec = 0;

		//EMSTIME timeNow = startTime;

		//while( timeNow.intTime < endTime.intTime  )
//		hr = oPA.OpenNULLfile( startTime );

		while( startTime.intTime < endTime.intTime  )
		{
			memset( aAzEls, 0, sizeof(EMSDBFAZEL) * culMaxSats);
			
			if( Plate.wFixedPointNumber  > 0 )
			{
				oPA.GetFixedPointSched( aAzEls, &ulActual );
			}
			else
			{
				//hr = oPA.GetSatelliteAZELs( timeNow, aAzEls, &ulActual );
				hr = oPA.GetSatelliteAZELs( startTime, aAzEls, &ulActual );
				hr = oPA.CheckLEOMEO( aAzEls, &ulActual );
				hr = oPA.GetPlateAZELs( aAzEls, &ulActual );
				hr = oPA.GetConstellationAZELs( aAzEls, &ulActual );
				
				//RR change to force nulling for all pointing directions
				//hr = oPA.GetSeparationAngles( aAzEls, &ulActual );

				hr = oPA.GetDBFPhase( aAzEls, &ulActual );

				//oDMgr.WritePassSchedule_Debug( aAzEls, &ulActual );

				// RR change to apply bias before nulling. This establishes 'consistant channels 
				//hr = oPA.ApplyPhaseBias( aAzEls, &ulActual );
				//hr = oPA.ApplyPhaseBias1( aAzEls, &ulActual );

				EMSDBFAZEL	      aAzEls1[culMaxSats]={{0}};
				memcpy( aAzEls1, aAzEls, sizeof( EMSDBFAZEL ) * ulActual );

				if (ulActual > 5)
				{
					float x = 1.0;
				}
				hr = oNP.GetNullPhase( aAzEls, &ulActual );
				
				//hr = oPA.ApplyPhaseBias1( aAzEls, &ulActual );

				// test output powers
				if ( ulActual > 1 )
				{
					hr = oPA.TestPhaseOutputPower( startTime, aAzEls1 ,aAzEls, &ulActual );
				}
			}

			memset( &PassRecord, 0, sizeof(EMSDBFPASSRECORD) );

			PassRecord.wProcessID = 0; // do nothing

			
			if ( irec%2   == 1 ) PassRecord.wProcessID = 5; // Compute A/D channel statistics
			if ( irec%50  == 0 ) PassRecord.wProcessID = 3; // Compute sample covariance matrix
			if ( irec%50  == 5 ) PassRecord.wProcessID = 4; // Store raw data buffer

			bool bTestSun = true;
			if ( ulActual == 0 && PassRecord.wProcessID > 0 )
			{
				// Write Pass Records
				PassRecord.timestamp  = startTime;
				PassRecord.ulLutID         = 7171;//oPA.GetLutID();;  
				PassRecord.wAntennaID      = 1; //m_aDBFplate.wPlateID; Note: RR requires plate ID from Data Manager

				hr = oDMgr.WritePassSchedule( PassRecord, bTestSun );
			}
			else if ( ulActual > 0 )
			{

				int nSatType = oPA.GetConstellationType( aAzEls[0].ulSatID );

				if ( ( nSatType < 3 ) && ( ulActual == 1 ) )
				{
					PassRecord.wProcessID = 1; // Perform Frequency Domain method
				}
				else
				{
					//PassRecord.wProcessID = 2; // Perform Time Domain method
					PassRecord.wProcessID = 2; // Perform Time Domain method - for testing
				}
				double dMEOelevation = 30.0;
				double dLEOelevation = 5;
				//double dLEOelevation = 40;
				//double dLEOelevation = 30;

				for ( ULONG j = 0; j < ulActual; j++ )
				{
					
					if (   ( aAzEls[j].ulSatID < 200 && aAzEls[j].degPlateElevation > dLEOelevation )
						|| ( aAzEls[j].ulSatID > 400 && aAzEls[j].degPlateElevation > dMEOelevation ) )
					{
						PassRecord.timestamp  = startTime;
						//PassRecord.timestamp.intTime  = timeNow.intTime;
						PassRecord.ulLutID         = 7171;//oPA.GetLutID();;  
						PassRecord.wAntennaID      = 1; //m_aDBFplate.wPlateID; Note: RR requires plate ID from Data Manager
						PassRecord.ulSatID         = aAzEls[j].ulSatID;
						PassRecord.fAzimuth        = (float) aAzEls[j].degSatAzimuth;
						PassRecord.fElevation      = (float) aAzEls[j].degSatElevation;
						PassRecord.fPlateAzimuth   = (float) aAzEls[j].degPlateAzimuth;
						PassRecord.fPlateElevation = (float) aAzEls[j].degPlateElevation;

						// RR the number of channels is one more than the number of cells
						for ( ULONG k = 0; k < Plate.wCellNumber + 1; k++ )
						{
							PassRecord.nPhaseReal[k] = (short) ( aAzEls[j].acmplxPhase[k].re * dScaleFactor );
							PassRecord.nPhaseImag[k] = (short) ( -aAzEls[j].acmplxPhase[k].im * dScaleFactor );
							//PassRecord.nPhaseImag[k] = (short) ( aAzEls[j].acmplxPhase[k].im * dScaleFactor );  // RR test only
						}

						hr = oDMgr.WritePassSchedule( PassRecord, bTestSun );
					}
				}

			}

			irec++;

			//timeNow.intTime += c_iNanoSecsPerSec;
			//startTime.intTime += c_iNanoSecsPerSec * 60 ; //For debugging
			startTime.intTime += c_iNanoSecsPerSec;
		}
	
//		hr = oPA.CloseNULLfile( );

	}
}


EMS_RESULT 
CEMSDBFSchedulerService::_ServiceProcessLoop( void )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		BOOL bStopped = FALSE;

		HANDLE hEvent[2];
		hEvent[ 0 ] = m_hEventStop;
		hEvent[ 1 ] = m_hEventSignal;

		while ( !bStopped )
		{
			DWORD dwResult = WaitForMultipleObjects( 2, hEvent, FALSE, c_ulTimeoutInterval );

			switch ( dwResult )
			{
				case WAIT_OBJECT_0:		// asked to stop 
					{
						bStopped = TRUE;
					}
					break;

				case WAIT_OBJECT_0 + 1:	// signalled!
					break;

				default:
				case WAIT_TIMEOUT:
					{
						if( _OkayToStop() != m_bStopEnabled )
						{
							// this will recheck and reset SERVICE_ACCEPT_STOP
							ReportServiceStatus( EMS_SERVICE_RUNNING );
						}
						_DoIdle();
					}
					break;
			}
		}
	}
	catch( CEMSException& e )
	{
		CEMSLogHelper::LogException( e );
		hr = e.GetErrCode();
	}
	catch( ... )
	{
		hr = EMS_UNKNOWN_ERROR;
	}

	return hr;
}

EMS_RESULT 
CEMSDBFSchedulerService::InstallService( void )
{
	EMS_RESULT hr = EMS_OK;

	CEMSComRegistry comReg;
	
	if ( IsService() )
	{
		hr = comReg.RegisterLocalService( (CLSID*)&APPID_EMSDBFPassScheduler, c_szServiceName);
	}
	else
	{
		hr = comReg.RegisterLocalServer( (CLSID*)&APPID_EMSDBFPassScheduler ); // DEBUG
	}

	if ( ( hr == EMS_OK ) && IsService() )
	{
		hr = CEMSService::InstallEMSService();
	}

	return hr;
}

EMS_RESULT 
CEMSDBFSchedulerService::RemoveService( void )
{
	return CEMSService::RemoveEMSService();
}


EMS_RESULT 
CEMSDBFSchedulerService::StopService( void ) 
{
	ReportServiceStatus( EMS_SERVICE_STOP_PENDING );

	SetEvent( m_hEventStop );

	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFSchedulerService::PauseService( void )
{
	if ( !m_bPaused )
	{
		m_bPaused = TRUE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFSchedulerService::ContinueService( void )
{
	if ( m_bPaused )
	{
		m_bPaused = FALSE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK;
}

BOOL 
CEMSDBFSchedulerService::StopIsAccepted( void )
{
	//m_bStopEnabled = _OkayToStop();
	//return m_bStopEnabled;
	return true;
}

BOOL 
CEMSDBFSchedulerService::_OkayToStop( void )
{
	return ( CApiObjBase::ObjectCount() == 0 );
}

EMS_RESULT 
CEMSDBFSchedulerService::StartService( DWORD dwArgc, LPTSTR *lpszArgv ) 
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

	_Init();


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

EMS_RESULT
CEMSDBFSchedulerService::StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv ) 
{
	EMS_RESULT hr = EMS_OK;
	int nMaxRetries = c_ulShutdownWait / c_ulSleepInterval, nRetries = 0;

	m_dwThreadID = GetCurrentThreadId();


	m_dwThreadID = GetCurrentThreadId();

	CEMSSecurityDescriptor secDesc;
	secDesc.InitializeFromThreadToken();

	hr = CoInitializeSecurity( secDesc, -1, NULL, NULL,
				RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, 
				NULL, EOAC_NONE, NULL);
	
	// Ok if it fails because it's been called earlier.  Using a Pipeline Log Appender
	// would cause init to occur earlier.
//	if( FAILED(hr) )
//	{
//		THROW_RUNTIME_EXCEPTION(hr);
//	}

	_Init();


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
CEMSDBFSchedulerService::_Init()
{
/*	IEMSSiteInfo* pSite = NULL;

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
			SetLutID( ulLutID );
		}

		pSite->Release();
		pSite = NULL;
	}
*/
//	SetProcessID( EMSLOGCAT_DBFPassScheduler );

	std::wstring owszConfigFile;
		// Get this from the registry.
#ifdef UNICODE
	//owszConfigFile = CEMSRegistrySettings::GetConfigPath( GetComponent() );
	m_owszPlateConfigFile =  CEMSRegistrySettings::GetConfigPath( GetComponent() );
#else
	//owszConfigFile = CEMSRegistrySettings::GetConfigPath( CEMSConversionUtil::ConvertToString( GetComponent() ).c_str() );
	m_owszPlateConfigFile = CEMSRegistrySettings::GetConfigPath( CEMSConversionUtil::ConvertToString( GetComponent() ).c_str() );
#endif

	//if( !owszConfigFile.empty() )
	//{
	//	CEMSConfigurationAccessor oConfig;
	//	oConfig.SetSourceFile( owszConfigFile.c_str() );

	//	CEMSConfigurationAccessor oPlatesConfig = oConfig.GetAccessor( ms_cwszPlatesConfig );

	//	// Get the list of defined web services from the config.

	//	CEMSObjectList<CEMSConfigurationAccessor> olstPlates = oPlatesConfig.GetAccessorList( ms_cwszPlateConfig );

	//	olstPlates.MoveFirst();
	//	// for now we support only one...
	//	//for( int i = 0; i < olstWS.Count(); i++ )
	//	{
	//		CEMSConfigurationAccessor oPlateConfig = olstPlates.GetNext();

	//		m_owszPlateConfigFile = oPlateConfig.GetElementValue( ms_cwszPlateConfigFile );
	//	}
	//	CEMSConfigurationAccessor oSatsConfig = oConfig.GetAccessor( ms_cwszSatsConfig );
	//	m_owszSatsConfig = oSatsConfig.Serialize();
	//}
	// Input Data Files
	const wchar_t* cDir = L"C:\\HGT\\config\\";
	//wchar_t* cSatFile = L"Sats_Gal";
	//wchar_t* cSatFile = L"Sats_leo";
	wchar_t* cSatFile = L"Sats_LeoMeo";
    wchar_t  wszFileName[256];
	
	memset(wszFileName, 0, sizeof(wszFileName) );

	wsprintfW( wszFileName, L"%s%s.xml", cDir, cSatFile );

	if( wszFileName && ( 0 < wcslen( wszFileName ) ) )
	{
		try
		{
			CEMSConfigurationAccessor oSatsConfig;
			std::wstring wszValue;

			oSatsConfig.SetSourceFile( wszFileName );
			
			oSatsConfig.GetAccessorList(ms_cwszSatsConfig);
			m_owszSatsConfig = oSatsConfig.Serialize();

		}
		catch( ... )
		{
			throw;
		}
	}
}

int main(int argc, char* argv[])
{
	//CEMSLogClient oLogClientInit;

	bool bCOMInit = false;
		
	try
	{
		EMS_RESULT hr = CoInitializeEx( 0, COINIT_MULTITHREADED );

		// This call should always succeed.
		if( hr != EMS_OK )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
		else
			bCOMInit = true;

		std::wstring owszLogConfig = CEMSLogRegistrySettings::GetPropertiesPath();
		
		//oLogClientInit.InitializeDefault();

		/*if( !owszLogConfig.empty() )
			oLogClientInit.InitializeLogging( owszLogConfig.c_str() );*/

		/*oLogClientInit.InitializeProcess( 
#if defined(UNICODE) || defined(_UNICODE)
			c_szServiceName, 
#else
			CEMSConversionUtil::ConvertToString( c_szServiceName ).c_str(),
#endif
			0, 0 );*/

		{
			CEMSDBFSchedulerService oDBFPassSchedService;

			int size =  sizeof(EMSDBFCALIBRECORD);

			if( argc > 1 &&
				0 == stricmp( argv[1], "-debug" ) )
			{
				oDBFPassSchedService.RunAsService( FALSE );	// for DEBUGGING
			}

			oDBFPassSchedService.AllowPause( FALSE );
			oDBFPassSchedService.Run( c_szServiceName, argc, argv );
		}

	}
	catch( CEMSException& e )
	{
		//oLogClientInit.LogException( e );
		CEMSLogHelper::LogException( e );

	}
	catch( ... )
	{

	}

//	oLogClientInit.Shutdown();

	if( bCOMInit )
		CoUninitialize();


	return 0; 
}


EMS_RESULT 
CEMSDBFSchedulerService::InstallEMSService( void )
{
	EMS_RESULT hr = EMS_OK;

	CEMSComRegistry comReg;
	
	if ( IsService() )
	{
		hr = comReg.RegisterLocalService( (CLSID*)&APPID_EMSDBFPassScheduler , c_szServiceName);
	}
	else
	{
		hr = comReg.RegisterLocalServer( (CLSID*)&APPID_EMSDBFPassScheduler  ); // DEBUG
	}

	if ( ( hr == EMS_OK ) && IsService() )
	{
		hr = CEMSService::InstallEMSService();
	}

	return hr;
}

EMS_RESULT 
CEMSDBFSchedulerService::RemoveEMSService( void )
{
	return CEMSService::RemoveEMSService();
}


EMS_RESULT 
CEMSDBFSchedulerService::StopEMSService( void ) 
{
	ReportServiceStatus( EMS_SERVICE_STOP_PENDING );

	SetEvent( m_hEventStop );

	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFSchedulerService::PauseEMSService( void )
{
	if ( !m_bPaused )
	{
		m_bPaused = TRUE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK; 
}

EMS_RESULT 
CEMSDBFSchedulerService::ContinueEMSService( void )
{
	if ( m_bPaused )
	{
		m_bPaused = FALSE;

		SetEvent( m_hEventSignal );
	}
	return EMS_OK;
}