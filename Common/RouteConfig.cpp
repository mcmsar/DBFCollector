#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length

#include "routeconfig.h"
#include "routeendconfig.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "routeconfigconstants.h"
#include "iconfigmanager.h"
#include <string>
#include "convutility.h"
#include "mtlmsgs.h"

CEMSRouteConfig::CEMSRouteConfig() : m_pEnd1(0), m_pEnd2(0), m_bEnabled(false)
{
}

CEMSRouteConfig::CEMSRouteConfig( const CEMSRouteConfig& x )
{

}

CEMSRouteConfig::~CEMSRouteConfig()
{
	if( m_pEnd1 )
		m_pEnd1->Release();
	m_pEnd1 = 0;

	if( m_pEnd2 )
		m_pEnd2->Release();
	m_pEnd1 = 0;
}

void 
CEMSRouteConfig::SetEnd1( CEMSRouteEndConfig* pEnd1 )
{
	if( m_pEnd1 )
		m_pEnd1->Release();

	m_pEnd1 = pEnd1;
	
	if( m_pEnd1 )
		m_pEnd1->AddRef();

}

CEMSRouteEndConfig* 
CEMSRouteConfig::GetEnd1()
{
	CEMSRouteEndConfig* pRet = m_pEnd1;

	if( pRet )
		pRet->AddRef();

	return pRet;
}

void 
CEMSRouteConfig::SetEnd2( CEMSRouteEndConfig* pEnd2 )
{
	if( m_pEnd2 )
		m_pEnd2->Release();

	m_pEnd2 = pEnd2;
	
	if( m_pEnd2 )
		m_pEnd2->AddRef();

}

CEMSRouteEndConfig* 
CEMSRouteConfig::GetEnd2()
{
	CEMSRouteEndConfig* pRet = m_pEnd2;

	if( pRet )
		pRet->AddRef();

	return pRet;
}

void
CEMSRouteConfig::PopulateRoute( const wchar_t* cwszRoute, IEMSConfigurationManager* pConfig )
{
	if( !cwszRoute || !pConfig )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	int iCount = 0;
	EMSCONFIGURATIONITEM**  apConfigData   = 0;

	CEMSRouteEndConfig*	pEnd1 = 0;
	CEMSRouteEndConfig*	pEnd2 = 0;

	try
	{
		SetRouteName( cwszRoute );

		EMS_RESULT hr = pConfig->GetGroup( cwszRouteGroup, cwszRoute, &iCount, &apConfigData );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		pEnd1 = new CEMSRouteEndConfig;

		if( !pEnd1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pEnd2 = new CEMSRouteEndConfig;

		if( !pEnd2 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		for( int i = 0; i < iCount; i++ )
		{
			if( !apConfigData[i] )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
			
			if( !apConfigData[i]->pwcsKeyName )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			if( !apConfigData[i]->ValueList )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			// First check whether it is an End1 or End2 value.
			std::wstring wszTemp( apConfigData[i]->pwcsKeyName );

			// First check if this is the "enabled" flag (which is not associated with an end).
			if( wszTemp == cwszRouteEnabled )
			{
				SetEnabled( apConfigData[i]->ValueList[0].bVal ? true : false );
			}
			else
			{
				std::wstring::size_type iEnd1 = wszTemp.find( cwszEnd1 );

				CEMSRouteEndConfig* pEnd = pEnd1;

				if( std::wstring::npos == iEnd1 )
				{
					std::wstring::size_type iEnd2 = wszTemp.find( cwszEnd2 );

					if( std::wstring::npos != iEnd2 )
						pEnd = pEnd2;
					else
						THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
				}

				if( std::wstring::npos != wszTemp.find( cwszAlias ) )
				{
					pEnd->SetAlias( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszIdentifier ) )
				{
					pEnd->SetID( apConfigData[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInSITSSID ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetInSitSID( apConfigData[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszInSITSInternal ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetInSitInternal( _ConvertToSITCode( apConfigData[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataAntennaEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ANTENNA, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalib406Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIB406, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalibCBCEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIBCBC, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalibCBCStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIBCBC_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCBCEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CBC, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCollectorEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COLLECTOR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCombine406Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMB406, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCombine406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCommsStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMMS_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataConfigEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CONFIG, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataGEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_GEO_CALIB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataGEOStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_GEO_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LEO_CALIB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLocateEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOCATE, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLocateStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOCATE_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLogEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOG, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataOrbitEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ORBIT, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataOrbitStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ORBIT_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataPassStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_PASS_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataResidualEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_RESIDUAL, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPCalibEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP_CALIB, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPCalibStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP_CALIB_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRCalibEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_CALIB, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRCalibStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_CALIB_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARREnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSatTrackEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SAT_TRACK, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSatSensorEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SENSOR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSpectrumEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SPECTRUM, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataStatusEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_STAT_SUMMARY, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataWidebandEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_WIDEBAND_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataAudioEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_AUDIO, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataManoeuvreEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_MANOEUVRE, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRExtEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_EXT, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalib4062Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIB406_2, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutTranslationTable ) )
				{
					pEnd->SetTranslationTable( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutSITsSID ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetSitSID( apConfigData[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutSITsInternal ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetSitInternal( _ConvertToSITCode( apConfigData[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAutoSITsSID ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetAutoSitSID( apConfigData[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAutoSITsInternal ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetAutoSitInternal( _ConvertToSITCode( apConfigData[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendLocationMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_LOCATION, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendAlarmMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_ALARM, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendWarningMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_WARNING, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendStatusMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_STATUS, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendOrbitVectorMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_ORBV, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendTLEMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_TLE, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendPassScheduleMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_PASS_SCHED, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendMetopScheduleMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_METOP_SCHED, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ));
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendSARPCalibMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_SARP_CALIB, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendSARRCalibMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_SARR_CALIB, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendStartupMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_STARTUP, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendLEOPassSummaryMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_LEO_PASS_SUMMARY, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendGEOPassSummaryMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_GEO_PASS_SUMMARY, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommandAcknowledgementMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_CMD_ACK, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommsCheckMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_COMMS_CHECK, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommandMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_CMD, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRetransmitMsgsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_RETRANSMIT_MSGS, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendMsgsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_MSGS, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGetDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_GET_DATA, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceInitManProcMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_INIT_MAN_PROC, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRemoveDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_REMOVE_DATA, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceProcess406MsgType ) )
				{
					pEnd->SetMsgType( EMSRES_PROCESS_406, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceUploadDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_UPLOAD_DATA, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceCancelSessionMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CANCEL_SESSION, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGenerateAlertsMsgsType ) )
				{
					pEnd->SetMsgType( EMSRES_GEN_ALERTS, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_DATA, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ));
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRecoverDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_RECOVER_DATA, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGetControlFilenamesMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_GET_CONTROL_FILENAMES, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendDataReportMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_DATA_REPORT, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceConfigGetMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CONFIG_GET, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceConfigSetStringMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CONFIG_SET_STRING, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAlertSendSolutionsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_ALERT_SEND_SOLNS, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAlertTransmitMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_ALERT_TRANSMIT, _GetMsgType( apConfigData[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutFormat ) )
				{
					bool bMulti = false;

					if( apConfigData[i]->ValueList[0].pwcsVal )
					{
						if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszSit ) == 0 )
						{
							bMulti = false;
						}
						else if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszMultiSit ) == 0 )
						{
							bMulti = true;
						}
						else
						{
							THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
						}
					}

					pEnd->SetMultiSit( bMulti );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutMaxSatellites ) )
				{
					pEnd->SetMaxSatellites( apConfigData[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataAntennaEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ANTENNA, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalib406Enabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIB406, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalibCBCEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIBCBC, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalibCBCStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIBCBC_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCBCEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CBC, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCollectorEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COLLECTOR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCombine406Enabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMB406, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCombine406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCommsStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMMS_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataConfigEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CONFIG, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataGEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_GEO_CALIB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataGEOStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_GEO_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LEO_CALIB406_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLocateEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOCATE, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLocateStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOCATE_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLogEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOG, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataOrbitEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ORBIT, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataOrbitStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ORBIT_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataPassStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_PASS_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataResidualEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_RESIDUAL, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPCalibEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP_CALIB, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPCalibStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP_CALIB_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRCalibEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR_CALIB, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRCalibStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR_CALIB_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARREnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSatTrackEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SAT_TRACK, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSatSensorEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SENSOR, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSpectrumEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SPECTRUM, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataStatusEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_STAT_SUMMARY, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataWidebandEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_WIDEBAND_STATS, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataAudioEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_AUDIO, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataManoeuvreEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_MANOEUVRE, 
										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
				}
//				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRExtEnabled ) )
//				{
//					pEnd->SetBinarySend( EMSRT_SARR_EXT, 
//										(1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
//				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsDirectDirectory ) )
				{
					pEnd->SetDirectDir( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPHost ) )
				{
					pEnd->SetFTPHost( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPPort ) )
				{
					pEnd->SetFTPPort( apConfigData[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPLogin ) )
				{
					pEnd->SetFTPLogin( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPPassword ) )
				{
					pEnd->SetFTPPwd( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPDirectory ) )
				{
					pEnd->SetFTPDir( apConfigData[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsSOAPEndpoint ) )
				{
					pEnd->SetSOAPEndpoint( apConfigData[i]->ValueList[0].pwcsVal );
				}
				// Started a new "if" ... compiler limit
				if( std::wstring::npos != wszTemp.find( cwszOutUseSecurityToken ) )
				{
					pEnd->SetUseSecurityToken( 1 == apConfigData[i]->ValueList[0].bVal ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutMultiSitMaxAlertsPerMessage ) )
				{
					pEnd->SetMaxAlertsPerMessage( apConfigData[i]->ValueList[0].uiVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAlertChannels ) )
				{
					for( int i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
					{
						pEnd->SetAlertChannel( apConfigData[i]->ValueList[i2].uiVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutReportSourceChannel ) )
				{
					pEnd->SetReportSourceChannel( 1 == apConfigData[i]->ValueList[0].bVal ? true : false );
				}
			}
		}

		SetEnd1( pEnd1 );
		SetEnd2( pEnd2 );

		pEnd1->Release();
		pEnd1 = 0;

		pEnd2->Release();
		pEnd2 = 0;

		if( apConfigData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apConfigData[i] )
				{
					if( apConfigData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apConfigData[i]->ValueList[i2].dataType )
							{
								if( apConfigData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apConfigData[i]->ValueList[i2].pwcsVal );
									apConfigData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apConfigData[i]->ValueList );
						apConfigData[i]->ValueList = 0;
					}

					CoTaskMemFree( apConfigData[i] );
					apConfigData[i] = 0;
				}
			}

			CoTaskMemFree( apConfigData );
			apConfigData = 0;
		}

	}
	catch( ... )
	{
		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( pEnd1 )
		{
			pEnd1->Release();
			pEnd1 = 0;
		}

		if( pEnd2 )
		{
			pEnd2->Release();
			pEnd2 = 0;
		}

		if( apConfigData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apConfigData[i] )
				{
					if( apConfigData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apConfigData[i]->ValueList[i2].dataType )
							{
								if( apConfigData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apConfigData[i]->ValueList[i2].pwcsVal );
									apConfigData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apConfigData[i]->ValueList );
						apConfigData[i]->ValueList = 0;
					}

					CoTaskMemFree( apConfigData[i] );
					apConfigData[i] = 0;
				}
			}

			CoTaskMemFree( apConfigData );
			apConfigData = 0;
		}

		throw;
	}
}

void
CEMSRouteConfig::PopulateRoute( const int ciNumConfigItems, const EMSCONFIGURATIONITEM** capConfigItems )
{
	if( !capConfigItems )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}


	CEMSRouteEndConfig*	pEnd1 = 0;
	CEMSRouteEndConfig*	pEnd2 = 0;

	try
	{
		pEnd1 = new CEMSRouteEndConfig;

		if( !pEnd1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pEnd2 = new CEMSRouteEndConfig;

		if( !pEnd2 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		for( int i = 0; i < ciNumConfigItems; i++ )
		{
			if( !capConfigItems[i] )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
			
			if( !capConfigItems[i]->pwcsKeyName )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			if( !capConfigItems[i]->ValueList )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			// First check whether it is an End1 or End2 value.
			std::wstring wszTemp( capConfigItems[i]->pwcsKeyName );

			// First check if this is the "enabled" flag (which is not associated with an end).
			if( wszTemp == cwszRouteEnabled )
			{
				SetEnabled( capConfigItems[i]->ValueList[0].bVal ? true : false );
			}
			else
			{

				std::wstring::size_type iEnd1 = wszTemp.find( cwszEnd1 );

				CEMSRouteEndConfig* pEnd = pEnd1;

				if( std::wstring::npos == iEnd1 )
				{
					std::wstring::size_type iEnd2 = wszTemp.find( cwszEnd2 );

					if( std::wstring::npos != iEnd2 )
						pEnd = pEnd2;
					else
						THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
				}

				if( std::wstring::npos != wszTemp.find( cwszAlias ) )
				{
					pEnd->SetAlias( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszIdentifier ) )
				{
					pEnd->SetID( capConfigItems[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInSITSSID ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetInSitSID( capConfigItems[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszInSITSInternal ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetInSitInternal( _ConvertToSITCode( capConfigItems[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataAntennaEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ANTENNA, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalib406Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIB406, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalibCBCEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIBCBC, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalibCBCStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIBCBC_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCBCEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CBC, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCollectorEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COLLECTOR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCombine406Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMB406, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCombine406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCommsStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_COMMS_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataConfigEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CONFIG, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataGEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_GEO_CALIB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataGEOStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_GEO_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LEO_CALIB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLocateEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOCATE, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLocateStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOCATE_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataLogEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_LOG, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataOrbitEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ORBIT, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataOrbitStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_ORBIT_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataPassStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_PASS_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataResidualEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_RESIDUAL, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPCalibEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP_CALIB, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPCalibStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP_CALIB_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARPEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARP, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRCalibEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_CALIB, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRCalibStatsEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_CALIB_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARREnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSatTrackEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SAT_TRACK, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSatSensorEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SENSOR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSpectrumEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SPECTRUM, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataStatusEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_STAT_SUMMARY, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataWidebandEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_WIDEBAND_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataAudioEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_AUDIO, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataManoeuvreEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_MANOEUVRE, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataSARRExtEnabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_SARR_EXT, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszInBinaryDataCalib4062Enabled ) )
				{
					pEnd->SetBinaryReceive( EMSRT_CALIB406_2, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutTranslationTable ) )
				{
					pEnd->SetTranslationTable( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutSITsSID ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetSitSID( capConfigItems[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutSITsInternal ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetSitInternal( _ConvertToSITCode( capConfigItems[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAutoSITsSID ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetAutoSitSID( capConfigItems[i]->ValueList[i2].iVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAutoSITsInternal ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetAutoSitInternal( _ConvertToSITCode( capConfigItems[i]->ValueList[i2].pwcsVal ) );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendLocationMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_LOCATION, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendAlarmMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_ALARM, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendWarningMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_WARNING, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendStatusMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_STATUS, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendOrbitVectorMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_ORBV, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendTLEMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_TLE, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendPassScheduleMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_PASS_SCHED, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendMetopScheduleMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_METOP_SCHED, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ));
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendSARPCalibMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_SARP_CALIB, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendSARRCalibMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_SARR_CALIB, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendStartupMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_STARTUP, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendLEOPassSummaryMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_LEO_PASS_SUMMARY, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendGEOPassSummaryMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_GEO_PASS_SUMMARY, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommandAcknowledgementMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_CMD_ACK, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommsCheckMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_COMMS_CHECK, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendCommandMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_CMD, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRetransmitMsgsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_RETRANSMIT_MSGS, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendMsgsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_MSGS, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGetDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_GET_DATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceInitManProcMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_INIT_MAN_PROC, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRemoveDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_REMOVE_DATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceProcess406MsgType ) )
				{
					pEnd->SetMsgType( EMSRES_PROCESS_406, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceUploadDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_UPLOAD_DATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceCancelSessionMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CANCEL_SESSION, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGenerateAlertsMsgsType ) )
				{
					pEnd->SetMsgType( EMSRES_GEN_ALERTS, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_DATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ));
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceRecoverDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_RECOVER_DATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceGetControlFilenamesMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_GET_CONTROL_FILENAMES, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceSendDataReportMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SEND_DATA_REPORT, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceConfigGetMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CONFIG_GET, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceConfigSetStringMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_CONFIG_SET_STRING, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAlertSendSolutionsMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_ALERT_SEND_SOLNS, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAlertTransmitMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_ALERT_TRANSMIT, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceTransmitMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_SIT_TRANSMIT, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutFormat ) )
				{
					bool bMulti = false;

					if( capConfigItems[i]->ValueList[0].pwcsVal )
					{
						if( wcsicmp( capConfigItems[i]->ValueList[0].pwcsVal, cwszSit ) == 0 )
						{
							bMulti = false;
						}
						else if( wcsicmp( capConfigItems[i]->ValueList[0].pwcsVal, cwszMultiSit ) == 0 )
						{
							bMulti = true;
						}
						else
						{
							THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
						}
					}

					pEnd->SetMultiSit( bMulti );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutMaxSatellites ) )
				{
					pEnd->SetMaxSatellites( capConfigItems[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataAntennaEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ANTENNA, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalib406Enabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIB406, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalibCBCEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIBCBC, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCalibCBCStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CALIBCBC_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCBCEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CBC, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCollectorEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COLLECTOR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCombine406Enabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMB406, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCombine406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataCommsStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_COMMS_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataConfigEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_CONFIG, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataGEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_GEO_CALIB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataGEOStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_GEO_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLEOCalib406StatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LEO_CALIB406_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLocateEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOCATE, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLocateStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOCATE_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataLogEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_LOG, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataOrbitEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ORBIT, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataOrbitStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_ORBIT_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataPassStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_PASS_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataResidualEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_RESIDUAL, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPCalibEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP_CALIB, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPCalibStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP_CALIB_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARPEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARP, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRCalibEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR_CALIB, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRCalibStatsEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR_CALIB_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARREnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SARR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSatTrackEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SAT_TRACK, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSatSensorEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SENSOR, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSpectrumEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_SPECTRUM, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataStatusEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_STAT_SUMMARY, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataWidebandEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_WIDEBAND_STATS, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataAudioEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_AUDIO, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataManoeuvreEnabled ) )
				{
					pEnd->SetBinarySend( EMSRT_MANOEUVRE, 
										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
				}
//				else if( std::wstring::npos != wszTemp.find( cwszOutBinaryDataSARRExtEnabled ) )
//				{
//					pEnd->SetBinarySend( EMSRT_SARREXT, 
//										(1 == capConfigItems[i]->ValueList[0].bVal ) ? true : false );
//				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsDirectDirectory ) )
				{
					pEnd->SetDirectDir( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPHost ) )
				{
					pEnd->SetFTPHost( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPPort ) )
				{
					pEnd->SetFTPPort( capConfigItems[i]->ValueList[0].iVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPLogin ) )
				{
					pEnd->SetFTPLogin( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPPassword ) )
				{
					pEnd->SetFTPPwd( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutCommsFTPDirectory ) )
				{
					pEnd->SetFTPDir( capConfigItems[i]->ValueList[0].pwcsVal );
				}

				// --- the compiler doesn't support so many nested blocks ---
				if( std::wstring::npos != wszTemp.find( cwszOutCommsSOAPEndpoint ) )
				{
					pEnd->SetSOAPEndpoint( capConfigItems[i]->ValueList[0].pwcsVal );
				}
				
				if( std::wstring::npos != wszTemp.find( cwszOutUseSecurityToken ) )
				{
					pEnd->SetUseSecurityToken( 1 == capConfigItems[i]->ValueList[0].bVal ? true : false );
				}
				
				
				// --- the compiler doesn't support so many nested blocks ---
				if( std::wstring::npos != wszTemp.find( cwszOutMultiSitMaxAlertsPerMessage ) )
				{
					pEnd->SetMaxAlertsPerMessage( capConfigItems[i]->ValueList[0].uiVal );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioRequestMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_MAKEFREEREQUEST, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioReqGetDataMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_GETFREEREQUESTDATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioReqCancelMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_CANCELFREEREQUEST, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioRealConnectMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_CONNECT, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioRealGetMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_GETDATA, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioRealSetParamMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_SETPARAM, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutResourceAudioRealDisconnectMsgType ) )
				{
					pEnd->SetMsgType( EMSRES_AUDIO_DISCONNECT, _GetMsgType( capConfigItems[i]->ValueList[0].pwcsVal ) );
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutAlertChannels ) )
				{
					for( int i2 = 0; i2 < capConfigItems[i]->uiValues; i2++ )
					{
						pEnd->SetAlertChannel( capConfigItems[i]->ValueList[i2].uiVal );
					}
				}
				else if( std::wstring::npos != wszTemp.find( cwszOutReportSourceChannel ) )
				{
					pEnd->SetReportSourceChannel( 1 == capConfigItems[i]->ValueList[0].bVal ? true : false );
				}


			}
		}

		SetEnd1( pEnd1 );
		SetEnd2( pEnd2 );

		pEnd1->Release();
		pEnd1 = 0;

		pEnd2->Release();
		pEnd2 = 0;

	}
	catch( ... )
	{
		if( pEnd1 )
		{
			pEnd1->Release();
			pEnd1 = 0;
		}

		if( pEnd2 )
		{
			pEnd2->Release();
			pEnd2 = 0;
		}

		throw;
	}
}


EMSMSGTYPE 
CEMSRouteConfig::_GetMsgType( const wchar_t* cwszType )
{
	EMSMSGTYPE eType = MSGTYPE_UNKNOWN;

	if( cwszType )
	{
		if( wcsicmp( cwszType, cwszSOAP ) == 0 )
		{
			eType = MSGTYPE_SOAP;
		}
		else if( wcsicmp( cwszType, cwszSIT ) == 0 )
		{
			eType = MSGTYPE_SIT;
		}
		else if( wcsicmp( cwszType, cwszBinary ) == 0 )
		{
			eType = MSGTYPE_BINARY;
		}
		else if( wcsicmp( cwszType, cwszUDP ) == 0 )
		{
			eType = MSGTYPE_UDP;
		}
		else
		{
			CEMSLogMsgParam logParam;
#if defined(UNICODE) || defined(_UNICODE)
			logParam += cwszType;
#else
			logParam += CEMSConversionUtil::ConvertToString( cwszType ).c_str();
#endif
			throw CEMSException( EMS_MTL_CFG_UNKNOWN_MSG_TYPE, logParam );
		}
	}

	return eType;
}

CEMSRouteEndConfig* 
CEMSRouteConfig::GetEnd( const unsigned long culID )
{
	CEMSRouteEndConfig* pRet = 0;

	if( m_pEnd1 )
	{
		if( culID == m_pEnd1->GetID() )
		{
			pRet = m_pEnd1;
			pRet->AddRef();
		}
	}

	if( !pRet )
	{
		if( m_pEnd2 )
		{
			if( culID == m_pEnd2->GetID() )
			{
				pRet = m_pEnd2;
				pRet->AddRef();
			}
		}
	}

	return pRet;
}

CEMSRouteEndConfig* 
CEMSRouteConfig::GetEnd( const wchar_t* cwszAlias )
{
	if( !cwszAlias )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSRouteEndConfig* pRet = 0;

	wchar_t* wszAlias = 0;

	try
	{
		if( m_pEnd1 )
		{
			if( wcsicmp( wszAlias = m_pEnd1->GetAlias(), cwszAlias ) == 0 )
			{
				pRet = m_pEnd1;
				pRet->AddRef();
			}
		}

		if( wszAlias )
		{
			delete[] wszAlias;
			wszAlias = 0;
		}

		if( !pRet )
		{
			if( m_pEnd2 )
			{
				if( wcsicmp( wszAlias = m_pEnd2->GetAlias(), cwszAlias ) == 0 )
				{
					pRet = m_pEnd2;
					pRet->AddRef();
				}
			}
		}

		if( wszAlias )
		{
			delete[] wszAlias;
			wszAlias = 0;
		}

	}
	catch( ... )
	{
		if( wszAlias )
		{
			delete[] wszAlias;
			wszAlias = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

long 
CEMSRouteConfig::_ConvertToSITCode( const wchar_t* cwszSITCode )
{
//	if( !cwszSITCode )
//	{
//		THROW_NULL_POINTER_EXCEPTION();
//	}

	long lRet = 0;
	if( cwszSITCode && wcslen( cwszSITCode ) > 0 )
	{
		wstring wszTemp( cwszSITCode );

		swscanf( wszTemp.c_str(), L"%x", &lRet );
	}
	

	return lRet;
}