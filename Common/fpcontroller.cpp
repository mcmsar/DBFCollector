/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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
#include "fpcontroller.h"
#include "emsclock.h"
#include "emsexcpt.h"
#include "loggrcat.h"
#include "fpmsgs.h"
#include "convutility.h"

#include <initguid.h>
#include "datacollector.h"
#include "antennacontrol.h"
#include "fploader.h"
#include "StatusBroadcaster.h"
#include "LOGGRCAT.h"
#include "LogHelper.h"
#include "HGTEnvnMeasAdaptor.h"
#include "ccbootstrap.h"
#include <xercesc/util/PlatformUtils.hpp>
#include "meosysclient.h"
#include "mqproducer.h"

const ULONG CEMSFPController::ms_culTimeout = 5000;
const int CEMSFPController::ms_ciStatusUpdateInterval = 10; // default seconds
const int CEMSFPController::ms_ciEnvReadingsUpdateInterval = 120; // default seconds
const ULONG CEMSFPController::ms_culACU_TEMP_ID = 10001;
const ULONG CEMSFPController::ms_culRADOME_TEMP_ID = 10002;
const ULONG CEMSFPController::ms_culOUTSIDE_TEMP_ID = 10003;
const ULONG CEMSFPController::ms_culLNC_TEMP_ID = 10004;
const ULONG CEMSFPController::ms_culMOTOR_TEMP_ID = 10005;
const ULONG CEMSFPController::ms_culACU_HUMIDITY_ID = 10006;

const std::string CEMSFPController::ms_szEnvMeasTopicName = "EnvMeasurement.xml";


CEMSFPController::CEMSFPController() : m_pStatusBroadcast(NULL), m_bIsRunning( false ), m_iStatusUpdateInterval(0)
{
	m_tmLastStatusUpdate.intTime = 0;
	m_tmLastEnvReadingsUpdate.intTime = 0;
	m_eState = EMSSTATE_UN_INITIALIZED;
}

CEMSFPController::~CEMSFPController()
{
	if( m_pStatusBroadcast )
	{
		m_pStatusBroadcast->Release();
		m_pStatusBroadcast = NULL;
	}

	if( IsThreadRunning() )
		SignalStop();

	if( !wait( ms_culTimeout ) )
		stop();
}

void 
CEMSFPController::SetConfiguration( CEMSFPConfig& roConfig )
{
	try
	{
		m_ocsConfig.Enter();
		m_oConfig = roConfig;
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}
}

void
CEMSFPController::SetSchedule( CEMSPointerMap<const ULONG,CEMSPairSchedule>& romapSchedules )
{
	try
	{
		m_ocsSchedule.Enter();
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_CONTROLLER_SCHEDULE );
		m_omapSchedules = romapSchedules;
		_LogSchedule();
		m_ocsSchedule.Leave();
	}
	catch( ... )
	{
		m_ocsSchedule.Leave();
		throw;
	}
}

void 
CEMSFPController::Start()
{
	if( !IsThreadRunning() )
		start();

	m_eState = EMSSTATE_TRACKING;
}

void 
CEMSFPController::Stop()
{
/*	if( IsRunning() )
		SignalStop();

	if( !wait( ms_culTimeout ) )
		stop();
*/
	// Neither Orbital nor EMS antenna currently handle the Stow command.
	// The Orbital antenna actually moves to "Park" when told to idle.
	//_MoveToStow();
	m_eState = EMSSTATE_STOPPED;

}

void
CEMSFPController::Idle()
{
/*	if( IsRunning() )
		SignalStop();

	if( !wait( ms_culTimeout ) )
		stop();
*/
	m_eState = EMSSTATE_IDLE;
}

void 
CEMSFPController::run()
{
	m_bIsRunning = true;

	try
	{
		if(!m_pStatusBroadcast)
		{

			EMS_RESULT hr = CoCreateInstance( CLSID_EMSStatusBroadcaster, NULL, CLSCTX_ALL, 
									IID_IEMSStatusBroadcaster, (void**) &m_pStatusBroadcast );

			if( EMS_OK != hr )
			{
				// not a problem.
				m_pStatusBroadcast = NULL;
			}
		}

		m_iStatusUpdateInterval = m_oConfig.GetAntennaStatusCheckInterval(); // this in minutes
		m_iStatusUpdateInterval = m_iStatusUpdateInterval * 60;
		if( 0 == m_iStatusUpdateInterval )
		{
			m_iStatusUpdateInterval = ms_ciStatusUpdateInterval;
		}

		_InitializeAntennaSensors();

		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_START_MAIN_THREAD );

		bool bCheckNew = true;	// Used to give time between stopping active passes and starting new ones.

		while( !WaitForStop( ms_culTimeout ) )
		{
			try
			{
				switch( m_eState )
				{
				case EMSSTATE_TRACKING:
					{
						if( !bCheckNew )
						{
							// Check on the active pass(es).
							_CheckActive();
						}
						else
						{
							// Check for new pass(es).
							_CheckNew();
						}
					}
					break;
				case EMSSTATE_STOPPED:
				case EMSSTATE_IDLE:
					{
						_StopActive();
					}
					break;
				default:
					{
					}
					break;
				}

				_CheckStatusUpdates();

			}
			catch( CEMSException& e )
			{
				CEMSLogHelper::LogException( e );
			}
			catch( ... )
			{
				CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_FP_EXCEPTION_MAIN_THREAD );
			}

			bCheckNew = !bCheckNew;
		}

		_StopActive();

		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_STOP_MAIN_THREAD );
	}
	catch( ... )
	{
		// Just want to make sure that the m_bIsRunning flag gets set to false.
	}

	m_bIsRunning = false;
}

void
CEMSFPController::_UpdateEnvironmentReadings( const ULONG ulAntID )
{
	m_AntSensors.Reset();
	m_AntSensors.Init();
	if( m_AntSensors.IsInitialized() && !m_szMQUrl.empty() )
	{
		bool bUpdate = false;
		if( 0 == m_tmLastEnvReadingsUpdate.intTime )
		{
			bUpdate = true;
			m_tmLastEnvReadingsUpdate = CEMSSystemClock::GetTime();
		}
		else
		{
			EMSTIME timeNow = CEMSSystemClock::GetTime();
			CEMSTime oLast(m_tmLastEnvReadingsUpdate);
			oLast.AddSeconds( CEMSFPController::ms_ciEnvReadingsUpdateInterval );
			EMSTIME timeNextUpdate = oLast;
			if( timeNextUpdate.intTime <= timeNow.intTime )
			{
				bUpdate = true;
				m_tmLastEnvReadingsUpdate = timeNow;
			}
		}

		if( bUpdate )
		{
			double dACUTemp = AntennaSensors::GetUnknownValue();
			double dAOutdoorRadomeTemp = AntennaSensors::GetUnknownValue();
			double dACU2Temp = AntennaSensors::GetUnknownValue();
			double dLNCTemp = AntennaSensors::GetUnknownValue();
			double dMotorTemp = AntennaSensors::GetUnknownValue();
			double dACUHumidity = AntennaSensors::GetUnknownValue();
			CHGTEnvnMeasAdaptor oAdaptor;
			EMSTIMEFIELDS tmflds;
			memset( &tmflds, 0, sizeof(tmflds) );
			CEMSTime oTime( m_tmLastEnvReadingsUpdate );
			oTime.GetTime( &tmflds );
			::environmentMeasurement::EnvironmentMeasurementType tmepType( ::environmentMeasurement::EnvironmentMeasurementType::TEMPERATURE );
		
			dACUTemp = m_AntSensors.GetACUTemp();
			//if( AntennaSensors::GetUnknownValue() != dACUTemp )
			{
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culACU_TEMP_ID, "ACU Temperature",  dACUTemp, tmepType );
			}

			dAOutdoorRadomeTemp = m_AntSensors.GetOutdoorRadomeTemp();
			//if( AntennaSensors::GetUnknownValue() != dAOutdoorRadomeTemp )
			{
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culRADOME_TEMP_ID, "Radome Temperature",  dAOutdoorRadomeTemp, tmepType );
			}

			dACU2Temp = m_AntSensors.GetACU2Temp();
			//if( AntennaSensors::GetUnknownValue() != dACU2Temp )
			{
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culOUTSIDE_TEMP_ID, "Outside Temperature", dACU2Temp, tmepType );
			}

			dLNCTemp = m_AntSensors.GetLNCTemp();
			//if( AntennaSensors::GetUnknownValue() != dLNCTemp )
			{
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culLNC_TEMP_ID, "LNC Temperature",  dLNCTemp, tmepType );
			}

			dMotorTemp = m_AntSensors.GetMotorTemp();
			//if( AntennaSensors::GetUnknownValue() != dMotorTemp )
			{
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culMOTOR_TEMP_ID, "Motor Temperature",  dMotorTemp, tmepType );
			}

			dACUHumidity = m_AntSensors.GetACUHumidity();
			//if( AntennaSensors::GetUnknownValue() != dACUHumidity )
			{
				::environmentMeasurement::EnvironmentMeasurementType humidityType( ::environmentMeasurement::EnvironmentMeasurementType::HUMIDITY );
				oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culACU_HUMIDITY_ID, "ACU Humidity",  dACUHumidity, humidityType );
			}

			MQProducer oMQProd( m_szMQUrl.c_str(), ms_szEnvMeasTopicName.c_str(), 1, true );

			oMQProd.sendMessage( oAdaptor.GetXMLString().c_str() );
		}
	}
	else if( !m_AntSensors.IsInitialized() && !m_szMQUrl.empty() )
	{
		double dACUTemp = AntennaSensors::GetUnknownValue();
		double dAOutdoorRadomeTemp = AntennaSensors::GetUnknownValue();
		double dACU2Temp = AntennaSensors::GetUnknownValue();
		double dLNCTemp = AntennaSensors::GetUnknownValue();
		double dMotorTemp = AntennaSensors::GetUnknownValue();
		double dACUHumidity = AntennaSensors::GetUnknownValue();
		CHGTEnvnMeasAdaptor oAdaptor;

		EMSTIMEFIELDS tmflds;
		memset( &tmflds, 0, sizeof(tmflds) );
		CEMSTime oTime( m_tmLastEnvReadingsUpdate );
		oTime.GetTime( &tmflds );
		::environmentMeasurement::EnvironmentMeasurementType tmepType( ::environmentMeasurement::EnvironmentMeasurementType::TEMPERATURE );
		
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culACU_TEMP_ID, "ACU Temperature",  dACUTemp, tmepType );
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culRADOME_TEMP_ID, "Radome Temperature",  dAOutdoorRadomeTemp, tmepType );
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culOUTSIDE_TEMP_ID, "Outside Temperature", dACU2Temp, tmepType );
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culLNC_TEMP_ID, "LNC Temperature",  dLNCTemp, tmepType );
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culMOTOR_TEMP_ID, "Motor Temperature",  dMotorTemp, tmepType );
		::environmentMeasurement::EnvironmentMeasurementType humidityType( ::environmentMeasurement::EnvironmentMeasurementType::HUMIDITY );
		oAdaptor.AddEnvMeasurement( tmflds, ulAntID, CEMSFPController::ms_culACU_HUMIDITY_ID, "ACU Humidity",  dACUHumidity, humidityType );
		
		MQProducer oMQProd( m_szMQUrl.c_str(), ms_szEnvMeasTopicName.c_str(), 1, true );

		oMQProd.sendMessage( oAdaptor.GetXMLString().c_str() );
	}
}

void 
CEMSFPController::_CheckStatusUpdates()
{
	if( 0 == m_tmLastStatusUpdate.intTime )
	{
		_UpdateStatus();
		_UpdateFPCollectorStatus();
		m_tmLastStatusUpdate = CEMSSystemClock::GetTime();
	}
	else
	{
		EMSTIME timeNow = CEMSSystemClock::GetTime();
		CEMSTime oLast(m_tmLastStatusUpdate);
		oLast.AddSeconds( m_iStatusUpdateInterval );
		EMSTIME timeNextUpdate = oLast;
		if( timeNextUpdate.intTime <= timeNow.intTime )
		{
			_UpdateStatus();
			_UpdateFPCollectorStatus();
			m_tmLastStatusUpdate = timeNow;
		}
	}
}

void
CEMSFPController::_UpdateStatus()
{
	if( m_pStatusBroadcast )
	{
		EMS_RESULT hr = EMS_OK;
		IEMSAntenna2* pAC2 = NULL; 

		CEMSObjectList<ULONG> oACList = m_oConfig.GetAntennaControllers();
		//

		int iCnt = oACList.Count();
		oACList.MoveFirst();

		for( int i = 0; i < iCnt; i++ )
		{
			ULONG ulAC = oACList.GetNext();
			
			CEMSObjectList<ULONG> oAntennaList = m_oConfig.GetAntennaIDs(ulAC);

			int iAntCnt = oAntennaList.Count();
			oAntennaList.MoveFirst();

			bool bFESDone = false;

			for( int j = 0; j < iAntCnt; j++ )
			{
				ULONG ulAntID = oAntennaList.GetNext();

				pAC2 = _GetAntennaControlEx( ulAntID );
				
				// the FES.
				if( !bFESDone )
				{
					ULONG ulServiceID = EMSLOGCAT_OrbitalController;
					EMSTIME tm = CEMSSystemClock::GetTime();
					EMSCOMPONENTSTATUS eStatus = EMS_STATUS_UNKNOWN;
					std::wstring wszDesc = L"FES";
					std::wstring wszFPContrlErrorMsg = L"";
					
					if( pAC2 )
					{
						EMSFESSTATUS eFESStatus;
						hr = pAC2->GetFESStatus( &eFESStatus );
						if( EMS_FES_STATUS_OK == eFESStatus )
						{
							eStatus = EMS_STATUS_OK;
						}
						else
						{
							eStatus = EMS_STATUS_ERROR;
							if( EMS_OK != hr )
							{
								wszFPContrlErrorMsg = L"Failed to get the status";
							}
							else
							{
								wszFPContrlErrorMsg = L"The FES has internal errors";
							}
						}
					}
					else
					{
						wszFPContrlErrorMsg = L"Can't load the proxy to the FES";
					}

					m_pStatusBroadcast->BroadcastStatus( ulAC, ulServiceID, tm, eStatus, 
						                                 wszDesc.c_str(), 
														 wszFPContrlErrorMsg.c_str() );
					bFESDone = true;
				}
			
				// the Antenna.
				ULONG ulServiceID = EMSLOGCAT_OrbitalAntenna;
				EMSTIME tm = CEMSSystemClock::GetTime();
				EMSCOMPONENTSTATUS eStatus = EMS_STATUS_UNKNOWN;
				std::wstring wszDesc = L"Mesh Antenna";
				std::wstring wszFPContrlErrorMsg = L"";
				EMSANTENNA_STATE eState = EMS_ANTENNA_STATE_IDLE;
				float fAzimuth = 0.0;
				float fElevation = 0.0;
				wszFPContrlErrorMsg = L"";
				ULONG ulSatID = 0;

				if( pAC2 )
				{
					EMSANTENNASTATUS eAntStatus;
					hr = pAC2->GetAntennaStatus( ulAntID, &eAntStatus );

					if( EMS_ANTENNA_STATUS_OK == eAntStatus )
					{
						eStatus = EMS_STATUS_OK;
					}
					else
					{
						eStatus = EMS_STATUS_ERROR;
						if( EMS_OK != hr )
						{
							wszFPContrlErrorMsg += L"Failed to get the status";
						}
						else
						{
							wszFPContrlErrorMsg += L"The antenna has internal errors";
						}
					}
				}
				else
				{
					wszFPContrlErrorMsg += L"Can't load the proxy to the FES";
				}

				m_pStatusBroadcast->BroadcastStatus( ulAntID, ulServiceID, tm, eStatus, 
					                                 wszDesc.c_str(), 
													 wszFPContrlErrorMsg.c_str() );

				if( pAC2 )
				{
					hr = pAC2->GetPosition( ulAntID, &fAzimuth, &fElevation );

					if( EMS_OK != hr )
					{
						wszFPContrlErrorMsg += L"Failed to get the antenna position.";
					}
					
					EMSANTENNASTATE eAntState = EMS_ANTENNA_STATE_UNKNOWN;

					hr = pAC2->GetState( ulAntID, &eAntState );

					if( EMS_OK != hr )
					{
						wszFPContrlErrorMsg += L"Failed to get the antenna state.";
					}
					else
					{
						switch(eAntState)
						{
						case EMS_ANTENNA_STATE_TRACKING:
							{
								eState = EMS_ANTENNA_STATE__TRACKING;
							}
							break;
						case EMS_ANTENNA_STATE_NOTTRACKING:
							{
								eState = EMS_ANTENNA_STATE_IDLE;
							}
							break;
						default:
							{
								eState = EMS_ANTENNA_STATE_FAILED;
							}
							break;
						}
					}
				}

				//ulSatID = _GetSatID( ulAntID );
				//m_pStatusBroadcast->BroadcastAntennaDetails( ulAntID, ulSatID, tm,
				//											 eState, fAzimuth, fElevation );
				if( pAC2 ) 
				{
					pAC2->Release();
					pAC2 = NULL;
				}
				_UpdateEnvironmentReadings( ulAntID );
			}
		}
	}
}

void 
CEMSFPController::_UpdateFPCollectorStatus()
{
	if( m_pStatusBroadcast )
	{
		ULONG ulLutID = m_oConfig.GetLutID(); 
		ULONG ulServiceID = EMSLOGCAT_Collector;
		EMSTIME tm = CEMSSystemClock::GetTime();
		EMSCOMPONENTSTATUS eStatus;

		std::wstring wszDesc = L"FPCollector";
		if(	m_wszFPCollectorErrorMsg.empty() )
		{
			// everything is OK
			eStatus = EMS_STATUS_OK;
		}
		else
		{
			// errors...
			eStatus = EMS_STATUS_ERROR;
		}

		m_pStatusBroadcast->BroadcastStatus( ulLutID, ulServiceID, tm, eStatus, 
											 wszDesc.c_str(), 
											 m_wszFPCollectorErrorMsg.c_str() );
	}
}

void 
CEMSFPController::_CheckActive()
{
	m_omapActivePasses.MoveFirst();

	ULONG ulPasses = m_omapActivePasses.Count();

	for( ULONG l = 0; l < ulPasses; l++  )
	{
		EMSSATTRACKRECORD strActivePass = m_omapActivePasses.GetNext();

		// Does this track record match identically to one in the current schedule.  If the
		// schedule has been updated, this pass may have been removed and we want to stop it.
		if( 2 == _IsInSchedule( m_omapActivePasses.GetKey(), strActivePass  ) )
		{
			// Is this pass still active?
			EMSTIME timeNow = CEMSSystemClock::GetTime();

			if( strActivePass.track.PassInfo.timeAOS.intTime > timeNow.intTime ||
				strActivePass.track.PassInfo.timeLOS.intTime < timeNow.intTime )
			{
				CEMSLogMsgParam oParam;
				oParam.Add( strActivePass.track.PassInfo.ulSatelliteID );
				CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_NO_LONGER_IN_PASS, oParam );

				// Not in this pass.  Stop data collection. Antenna tracking to be stopped if its proxy
				// ask to stop between passes.
				_StopPass( m_omapActivePasses.GetKey(), _GetStopCollectorOnly(m_omapActivePasses.GetKey()) );
			}
		}
		else if( 1 == _IsInSchedule( m_omapActivePasses.GetKey(), strActivePass  ) )
		{
			CEMSLogMsgParam oParam;
			oParam.Add( strActivePass.track.PassInfo.ulSatelliteID );
			CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_NO_LONGER_SCHEDULED, oParam );

			// It is the same pass but different aos/los, stop the collector only
			// because it will start again and save the antenna movement.
			//_StopPass( m_omapActivePasses.GetKey(), true );
			m_omapActivePasses.Remove( m_omapActivePasses.GetKey() );
		}
		else
		{
			CEMSLogMsgParam oParam;
			oParam.Add( strActivePass.track.PassInfo.ulSatelliteID );
			CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_NO_LONGER_SCHEDULED, oParam );

			// Not in this pass.  Stop data collection. Antenna tracking to be stopped if its proxy
			// asks to stop between passes.
			_StopPass( m_omapActivePasses.GetKey(), _GetStopCollectorOnly(m_omapActivePasses.GetKey()) );
		}
	}
}

void 
CEMSFPController::_CheckNew()
{
	CEMSPairSchedule* pPair = NULL;
	EMSSATTRACKRECORD* pSatTrack = NULL;

	try
	{
		m_ocsSchedule.Enter();

		m_omapSchedules.MoveFirst();

		ULONG ulSchedules = m_omapSchedules.Count();

		for( ULONG l = 0; l < ulSchedules; l++ )
		{
			pPair = m_omapSchedules.GetNext();
			
			if( !pPair )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pSatTrack = pPair->GetCurrentPass();

			if( pSatTrack )
			{
				bool bTrackIt = true;

				// There is a current, active pass.
				// Is it already being tracked?
				if( m_omapActivePasses.IsInMap( pPair->GetPairID() ) )
				{
					EMSSATTRACKRECORD strActivePass = m_omapActivePasses.Get( pPair->GetPairID() );

					// Is this the same pass?  If not, stop it.  A new
					// pass schedule may have been received.  
					if( 0 != memcmp( &strActivePass, pSatTrack, sizeof(strActivePass) ) )
					{
						CEMSLogMsgParam oParam;
						oParam.Add( pPair->GetPairID() );
						CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_CHANGE, oParam );

						if( strActivePass.track.PassInfo.ulSatelliteID == pSatTrack->track.PassInfo.ulSatelliteID )
						{
							// don't stop the antenna
							_StopPass( pPair->GetPairID(), true );
						}
						else
						{
							// Not in this pass.  Stop data collection. Antenna tracking to be stopped if its proxy
							// asks to stop between passes.
							_StopPass( pPair->GetPairID(), _GetStopCollectorOnly(m_omapActivePasses.GetKey()) );
						}
					}

					bTrackIt = false;
				}

				if( bTrackIt )
				{
					CEMSLogMsgParam oParam;
					oParam.Add( pPair->GetPairID() );
					CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_NEW, oParam );

					_StartPass( pPair, pSatTrack );
				}

				delete pSatTrack;
				pSatTrack = NULL;
			}

			pPair->Release();
			pPair = NULL;
		
		}

		m_ocsSchedule.Leave();
	}
	catch( ... )
	{
		if( pSatTrack )
		{
			delete pSatTrack;
			pSatTrack = NULL;
		}

		if( pPair )
		{
			pPair->Release();
			pPair = NULL;
		}

		m_ocsSchedule.Leave();

		throw;
	}
}

void 
CEMSFPController::_StopPass( const ULONG culPairID, const bool cbCollectorOnly )
{
	// Stop the data collector.
	IEMSDataCollector* pDataCollector = NULL;
	IEMSAntenna*	pAntennaControl = NULL;
	
	m_wszFPCollectorErrorMsg = L"";
	try
	{
		ULONG ulADBoardID = _GetADBoardID( culPairID );
		ULONG ulChannelID = _GetChannelID( culPairID );
		ULONG ulAntennaID = _GetAntennaID( culPairID );
	
		pDataCollector = _GetDataCollector( culPairID );

		if( !pDataCollector )
		{
			m_wszFPCollectorErrorMsg += L"Failed to connect to the board";
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pDataCollector->Stop( ulADBoardID, ulChannelID );

		if( EMS_OK != hr )
		{
			m_wszFPCollectorErrorMsg += L"The collector failed to stop";
			THROW_RUNTIME_EXCEPTION(hr);
		}

		CEMSLogMsgParam oParam;
		oParam.Add( ulADBoardID );
		oParam.Add( ulChannelID );
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_STOP_COLLECTION, oParam );

		pDataCollector->Release();
		pDataCollector = NULL;

		if( !cbCollectorOnly )
		{
			if( 0 != ulAntennaID )
			{

				pAntennaControl = _GetAntennaControl( culPairID );

				if( pAntennaControl )
				{

					hr = pAntennaControl->Stop( ulAntennaID );

					if( EMS_OK != hr )
					{
						m_wszFPCollectorErrorMsg = L"Failed to stop the antenna";
						THROW_RUNTIME_EXCEPTION(hr);
					}

					CEMSLogMsgParam oParam;
					oParam.Add( ulAntennaID );
					CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_STOP_TRACKING, oParam );

					pAntennaControl->Release();
					pAntennaControl = NULL;
				}
			}
		}

		// Remove the pass from the active list.
		m_omapActivePasses.Remove( culPairID );

	}
	catch( ... )
	{
		if( pDataCollector )
		{
			pDataCollector->Release();
			pDataCollector = NULL;
		}

		if( pAntennaControl )
		{
			pAntennaControl->Release();
			pAntennaControl = NULL;
		}

		_UpdateFPCollectorStatus();
		throw;
	}

	_UpdateFPCollectorStatus();
}

ULONG
CEMSFPController::_GetSatID( const ULONG ulAntID )
{
	ULONG ulRet = 0;
	m_omapActivePasses.MoveFirst();

	ULONG ulActive  = m_omapActivePasses.Count();

	for( ULONG l = 0; l < ulActive; l++ )
	{
		EMSSATTRACKRECORD strActivePass = m_omapActivePasses.GetNext();

		if( ulAntID == m_oConfig.GetAntennaID( m_omapActivePasses.GetKey() ) )
		{
			ulRet = strActivePass.track.PassInfo.ulSatelliteID;
			break;
		}
	}

	return ulRet;
}

void 
CEMSFPController::_StartPass( const CEMSPairSchedule* cpPair, const EMSSATTRACKRECORD* cpPass )
{
	// Need to start and stop the data collector and tell the ACU to track the satellite.

	IEMSAntenna* pAntennaControl = NULL;
	IEMSDataCollector* pDataCollector = NULL;

	m_wszFPCollectorErrorMsg = L"";

	try
	{
		EMS_RESULT hr = EMS_OK;

		if( !cpPair )
		{
			m_wszFPCollectorErrorMsg = L"Bad parameter (null CEMSPairSchedule*)";
			THROW_NULL_POINTER_EXCEPTION();
		}

		if( !cpPass )
		{
			m_wszFPCollectorErrorMsg = L"Bad parameter (null EMSSATTRACKRECORD*)";
			THROW_NULL_POINTER_EXCEPTION();
		}
		
		// Get the antenna tracking the appropriate satellite first since we don't set it to idle between
		// passes.  This means that it is still tracking the last satellite in the schedule (if it's available). 
		pAntennaControl = _GetAntennaControl( cpPair->GetPairID() );

		// There may not be an antenna controller.  This could be an EMS GEO antenna.
		if( pAntennaControl )
		{
			hr = pAntennaControl->Track( cpPair->GetAntennaID(), 1, &cpPass->track.PassInfo.ulSatelliteID );

			if( EMS_OK != hr )
			{
				m_wszFPCollectorErrorMsg = L"Antenna failed to track satellite ";
				m_wszFPCollectorErrorMsg += CEMSConversionUtil::ConvertToString( cpPass->track.PassInfo.ulSatelliteID );
				THROW_RUNTIME_EXCEPTION(hr);
			}

			pAntennaControl->Release();
			pAntennaControl = NULL;

			CEMSLogMsgParam oParam;
			oParam.Add( cpPass->track.PassInfo.ulSatelliteID );
			oParam.Add( cpPair->GetAntennaID() );
			CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_START_TRACKING, oParam );
		}

		// Configure and start the collector.

		pDataCollector = _GetDataCollector( cpPair->GetPairID() );

		if( !pDataCollector )
		{
			m_wszFPCollectorErrorMsg += L"Failed to connect to the board";
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulADBoardID = _GetADBoardID( cpPair->GetDataStreamID() );
		ULONG ulChannelID = _GetChannelID( cpPair->GetDataStreamID() );
		hr = pDataCollector->SetSatelliteID( ulADBoardID, ulChannelID, cpPass->track.PassInfo.ulSatelliteID );

		if( EMS_OK != hr )
		{
			m_wszFPCollectorErrorMsg += L"Failed to set the collector with the satellite details";
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pDataCollector->SetInputDataID( ulADBoardID, ulChannelID, cpPair->GetAntennaID() );

		if( EMS_OK != hr )
		{
			m_wszFPCollectorErrorMsg += L"Failed to set the collector with the input data details";
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pDataCollector->Start( ulADBoardID, ulChannelID );

		if( EMS_OK != hr )
		{
			m_wszFPCollectorErrorMsg += L"The collector failed to start";
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pDataCollector->Release();
		pDataCollector = NULL;

		CEMSLogMsgParam oParam;
		oParam.Add( cpPass->track.PassInfo.ulSatelliteID );
		oParam.Add( ulADBoardID );
		oParam.Add( ulChannelID );
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_START_COLLECTION, oParam );

		// Add to active passes.
		m_omapActivePasses.Add( cpPair->GetPairID(), *cpPass );

	}
	catch( ... )
	{
		if( pAntennaControl )
		{
			pAntennaControl->Release();
			pAntennaControl = NULL;
		}

		if( pDataCollector )
		{
			pDataCollector->Release();
			pDataCollector = NULL;
		}

		_UpdateFPCollectorStatus();
		throw;
	}

	_UpdateFPCollectorStatus();
}

ULONG 
CEMSFPController::_GetADBoardID( const ULONG culDSID )
{
	ULONG ulRet = 0;

	try
	{
		m_ocsConfig.Enter();
		ulRet = m_oConfig.GetADBoardID( culDSID );
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}

	return ulRet;
}

ULONG 
CEMSFPController::_GetChannelID( const ULONG culPairID )
{
	ULONG ulRet = 0;

	try
	{
		m_ocsConfig.Enter();
		ulRet =  m_oConfig.GetChannelID( culPairID );
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}

	return ulRet;
}

ULONG 
CEMSFPController::_GetAntennaID( const ULONG culPairID )
{
	ULONG ulRet = 0;

	try
	{
		m_ocsConfig.Enter();
		ulRet =  m_oConfig.GetAntennaID( culPairID );
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}

	return ulRet;
}

IEMSDataCollector* 
CEMSFPController::_GetDataCollector( const ULONG culPair )
{
	IEMSDataCollector* pRet = NULL;

	try
	{
		m_ocsConfig.Enter();
		pRet = CEMSFPLoader::LoadDatastreamProxy( culPair, m_oConfig );	
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}

	return pRet;
}

IEMSAntenna* 
CEMSFPController::_GetAntennaControl( const ULONG culPair )
{
	IEMSAntenna* pRet = NULL;

	try
	{
		m_ocsConfig.Enter();
		pRet = CEMSFPLoader::LoadAntennaProxy( culPair, m_oConfig );
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		m_ocsConfig.Leave();
		throw;
	}

	return pRet;
}

IEMSAntenna2* 
CEMSFPController::_GetAntennaControlEx( const ULONG culAntennaID )
{
	IEMSAntenna* pAC = NULL;
	IEMSAntenna2* pRet = NULL;

	try
	{
		m_ocsConfig.Enter();
		pAC = CEMSFPLoader::LoadAntennaProxyByID( culAntennaID, m_oConfig );
		if( pAC )
		{
			pAC->QueryInterface( IID_IEMSAntenna2, (void**) &pRet );
			pAC->Release();
			pAC = NULL;
		}
		m_ocsConfig.Leave();
	}
	catch( ... )
	{
		if( pAC )
		{
			pAC->Release();
			pAC = NULL;
		}
		m_ocsConfig.Leave();
		throw;
	}

	return pRet;
}

void
CEMSFPController::_StopActive()
{
	m_omapActivePasses.MoveFirst();

	ULONG ulActive  = m_omapActivePasses.Count();

	for( ULONG l = 0; l < ulActive; l++ )
	{
		m_omapActivePasses.GetNext();

		_StopPass( m_omapActivePasses.GetKey(), false );
	}
}

int 
CEMSFPController::_IsInSchedule( const ULONG culPairID, const EMSSATTRACKRECORD& crstrPass )
{
	int iRet = 0;

	CEMSPairSchedule* pSchedule = NULL;

	try
	{
		m_ocsSchedule.Enter();

		pSchedule = m_omapSchedules.Get( culPairID );

		if( pSchedule )
		{
			iRet = pSchedule->IsInSchedule( crstrPass );

			pSchedule->Release();
			pSchedule = NULL;
		}
		
		m_ocsSchedule.Leave();
	}
	catch( ... )
	{
		m_ocsSchedule.Leave();

		if( pSchedule )
		{
			pSchedule->Release();
			pSchedule = NULL;
		}

		throw;
	}

	return iRet;
}


void
CEMSFPController::_LogSchedule()
{
	EMSSATTRACKRECORD* aPasses = NULL;
	CEMSPairSchedule* pPair = NULL;

	try
	{
		ULONG ulSchedules = m_omapSchedules.Count();

		m_omapSchedules.MoveFirst();

		for( ULONG l = 0; l < ulSchedules; l++ )
		{
			pPair = m_omapSchedules.GetNext();
			
			if( !pPair )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			ULONG ulPasses = pPair->GetNumPasses();
			aPasses = pPair->GetPasses();

			for( ULONG l2 = 0; l2 < ulPasses; l2++ )
			{
				if( (EMS_PASSFLAG_PROCESS == ( EMS_PASSFLAG_PROCESS & aPasses[l2].track.PassInfo.ulFlags )) &&
					!(EMS_PASSFLAG_SKIP == ( EMS_PASSFLAG_SKIP & aPasses[l2].track.PassInfo.ulFlags )) )
				{
					CEMSLogMsgParam oParam;
					oParam.Add( pPair->GetPairID() );
					oParam.Add( pPair->GetAntennaID() );
					oParam.Add( pPair->GetDataStreamID() );
					oParam.Add( aPasses[l2].track.PassInfo.ulSatelliteID );
					oParam.AddString( CEMSConversionUtil::ConvertToDateTimeString2W( aPasses[l2].track.PassInfo.timeAOS ).c_str() );
					oParam.AddString( CEMSConversionUtil::ConvertToDateTimeString2W( aPasses[l2].track.PassInfo.timeLOS ).c_str() );

					CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_TRACK_RECORD_AUDIT, oParam );
				}
			}

			delete[] aPasses;
			aPasses = NULL;

			pPair->Release();
			pPair = NULL;

		}
	}
	catch( ... )
	{
		if( pPair )
		{
			pPair->Release();
			pPair = NULL;
		}

		if( aPasses )
		{
			delete[] aPasses;
			aPasses = NULL;
		}

		throw;
	}
}

void 
CEMSFPController::_MoveToStow()
{
	EMS_RESULT hr = EMS_OK;
	IEMSAntenna2* pAC2 = NULL; 

	CEMSObjectList<ULONG> oACList = m_oConfig.GetAntennaControllers();

	int iCnt = oACList.Count();
	oACList.MoveFirst();

	for( int i = 0; i < iCnt; i++ )
	{
		ULONG ulAC = oACList.GetNext();
		
		CEMSObjectList<ULONG> oAntennaList = m_oConfig.GetAntennaIDs(ulAC);

		int iAntCnt = oAntennaList.Count();
		oAntennaList.MoveFirst();

		bool bFESDone = false;

		for( int j = 0; j < iAntCnt; j++ )
		{
			ULONG ulAntID = oAntennaList.GetNext();

			pAC2 = _GetAntennaControlEx( ulAntID );

			if( pAC2 ) 
			{
				hr = pAC2->Stow( ulAntID );

				if( EMS_OK == hr ) 
				{
					CEMSLogMsgParam oParam;
					oParam.Add( ulAntID );

					CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_STOW_CMD_SENT, oParam );
				}
				else
				{
					CEMSLogMsgParam oParam;
					oParam.Add( ulAntID );
					oParam.AddX( hr );

					CEMSLogHelper::LogMsg( EMSLogMsgWarn, EMS_FP_STOW_CMD_FAILED, oParam );
				}
			}

			if( pAC2 ) 
			{
				pAC2->Release();
				pAC2 = NULL;
			}
		}
	}
}

bool
CEMSFPController::_GetStopCollectorOnly( const ULONG culPairID )
{
	bool           bStopCollectorOnly = true;
	IEMSAntenna2*  pAC2 = NULL;

	pAC2 = _GetAntennaControlEx( _GetAntennaID(culPairID) );

	if( pAC2 )
	{
		BOOL bStopBetweenPasses = FALSE;
		EMS_RESULT hr = pAC2->GetStopBetweenPassesFlag( &bStopBetweenPasses );
		if( EMS_OK == hr && bStopBetweenPasses )
		{
			bStopCollectorOnly = false;
		}
		pAC2->Release();
		pAC2 = NULL;
	}

	return bStopCollectorOnly;
}
			

void
CEMSFPController::_InitializeAntennaSensors()
{
	if( CCBootstrap::IsMEOSystem() )
	{
		// it has to be meosystem.
		//m_AntSensors.Init();

		MEOLUTConfig* pConfig = NULL;
		try
		{
			MEOSystemClient oMEOSys;
			pConfig = oMEOSys.getMEOLUTConfig();
			if( pConfig )
			{
				m_szMQUrl = pConfig->GetMQUrl();
				delete pConfig;
				pConfig = NULL;
			}
		}
		catch( ... )
		{
			if( pConfig )
			{
				delete pConfig;
				pConfig = NULL;
			}
			throw;
		}
	}
}

