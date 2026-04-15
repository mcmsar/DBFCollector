#pragma warning(disable:4786)	// disable compiler warning for stl debug symbol size

#include "lutconfig.h"
#include "emserror.h"
#include "emsexcpt.h"
#include <string>
#include "lutconfigconstants.h"

CEMSLutConfig::CEMSLutConfig() : m_ulID(0), m_wszShortName(0), 
								m_eLocality(DEPLOY_UNKNOWN), m_wszTransTable(0)
{
}

CEMSLutConfig::CEMSLutConfig( const CEMSLutConfig& x ) : m_ulID(0), m_wszShortName(0), 
								m_eLocality(DEPLOY_UNKNOWN), m_wszTransTable(0)
{
	m_ulID = x.m_ulID;

	_SetString( m_wszShortName, x.m_wszShortName );
	_SetString( m_wszTransTable, x.m_wszTransTable );
}

CEMSLutConfig::~CEMSLutConfig()
{
	if( m_wszShortName )
	{
		delete[] m_wszShortName;
		m_wszShortName = 0;
	}

	if( m_wszTransTable )
	{
		delete[] m_wszTransTable;
		m_wszTransTable = 0;
	}
}

void 
CEMSLutConfig::SetShortName( const wchar_t* cwszName )
{
	_SetString( m_wszShortName, cwszName );
}

wchar_t* 
CEMSLutConfig::GetShortName()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszShortName );

	return wszRet;
}

void 
CEMSLutConfig::SetResource( const EMSRESOURCEIDENTIFIER ceResource, const bool cbEnabled )
{
	std::map<EMSRESOURCEIDENTIFIER,bool>::iterator itFind = m_mapResources.find( ceResource );

	if( itFind != m_mapResources.end() )
	{
		itFind->second = cbEnabled;
	}
	else
	{
		m_mapResources.insert( std::pair<EMSRESOURCEIDENTIFIER,bool>( ceResource, cbEnabled ) );
	}
}

bool 
CEMSLutConfig::GetResource( const EMSRESOURCEIDENTIFIER ceResource )
{
	bool bRet = false;

	std::map<EMSRESOURCEIDENTIFIER,bool>::iterator itFind = m_mapResources.find( ceResource );

	if( itFind != m_mapResources.end() )
	{
		bRet = itFind->second;
	}

	return bRet;

}

void 
CEMSLutConfig::SetAsCommand( const EMSRESOURCEIDENTIFIER ceResource, const bool cbEnabled )
{
	std::map<EMSRESOURCEIDENTIFIER,bool>::iterator itFind = m_mapCommands.find( ceResource );

	if( itFind != m_mapCommands.end() )
	{
		itFind->second = cbEnabled;
	}
	else
	{
		m_mapCommands.insert( std::pair<EMSRESOURCEIDENTIFIER,bool>( ceResource, cbEnabled ) );
	}
}

bool 
CEMSLutConfig::GetAsCommand( const EMSRESOURCEIDENTIFIER ceResource )
{
	bool bRet = false;

	std::map<EMSRESOURCEIDENTIFIER,bool>::iterator itFind = m_mapCommands.find( ceResource );

	if( itFind != m_mapCommands.end() )
	{
		bRet = itFind->second;
	}

	return bRet;
}

void 
CEMSLutConfig::SetTranslationTable( const wchar_t* cwszName )
{
	_SetString( m_wszTransTable, cwszName );
}

wchar_t* 
CEMSLutConfig::GetTranslationTable()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszTransTable );

	return wszRet;
}

void
CEMSLutConfig::SetLutType( std::wstring& wstrLutType )
{
	if( std::wstring::npos != wstrLutType.find( cwszTypeLEOLUT600 ) )
	{
		m_eLutType = EMSLeoLut600;
	}
	else if( std::wstring::npos != wstrLutType.find( cwszTypeGEOLUT600 ) )
	{
		m_eLutType = EMSGeoLut600;
	}
	else if( std::wstring::npos != wstrLutType.find( cwszTypeMEOLUT600 ) )
	{
		m_eLutType = EMSMeoLut600;
	}
	else if( std::wstring::npos != wstrLutType.find( cwszTypeLUTSERVER ) )
	{
		m_eLutType = EMSLutClopType;
	}
	else if( std::wstring::npos != wstrLutType.find( cwszTypeOpInt600 ) )
	{
		m_eLutType = EMSOpIntType;
	}
	// We don't currently handle these other types:
	//		cwszTypeOCC
	//		cwszTypeATLUT
	else
	{
		m_eLutType = EMSLutTypeUnknown;
	}
}

void 
CEMSLutConfig::Populate( const unsigned long culID, IEMSConfigurationManager* pConfig )
{
	if( !pConfig )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	int iCount = 0;
	EMSCONFIGURATIONITEM**  apConfigData   = 0;

	try
	{
		wchar_t wszLutID[ 8 ];
		memset( wszLutID, 0, 8*sizeof(wchar_t) );
		_ltow( culID, wszLutID, 10 );

		EMS_RESULT hr = pConfig->GetGroup( cwszLutGroup, wszLutID, &iCount, &apConfigData );

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

			if( !apConfigData[i]->uiValues )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			std::wstring wszTemp( apConfigData[i]->pwcsKeyName );

			SetID( culID );

			if( wszTemp == cwszShortName )
			{
				SetShortName( apConfigData[i]->ValueList[0].pwcsVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResTranslationTable ) )
			{
				SetTranslationTable( apConfigData[i]->ValueList[0].pwcsVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendLocationEnabled ) )
			{
				SetResource( EMSRES_SEND_LOCATION, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendAlarmEnabled ) )
			{
				SetResource( EMSRES_SEND_ALARM, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendWarningEnabled ) )
			{
				SetResource( EMSRES_SEND_WARNING, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendStatusEnabled ) )
			{
				SetResource( EMSRES_SEND_STATUS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendOrbitVectorEnabled ) )
			{
				SetResource( EMSRES_SEND_ORBV, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendTLEEnabled ) )
			{
				SetResource( EMSRES_SEND_TLE, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendPassScheduleEnabled ) )
			{
				SetResource( EMSRES_SEND_PASS_SCHED, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendMetopScheduleEnabled ) )
			{
				SetResource( EMSRES_SEND_METOP_SCHED, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendSARPCalibEnabled ) )
			{
				SetResource( EMSRES_SEND_SARP_CALIB, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendSARRCalibEnabled ) )
			{
				SetResource( EMSRES_SEND_SARR_CALIB, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendStartupEnabled ) )
			{
				SetResource( EMSRES_SEND_STARTUP, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendLEOPassSummaryEnabled ) )
			{
				SetResource( EMSRES_SEND_LEO_PASS_SUMMARY, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendGEOPassSummaryEnabled ) )
			{
				SetResource( EMSRES_SEND_GEO_PASS_SUMMARY, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommandAckEnabled ) )
			{
				SetResource( EMSRES_SEND_CMD_ACK, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommsCheckEnabled ) )
			{
				SetResource( EMSRES_SEND_COMMS_CHECK, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommandEnabled ) )
			{
				SetResource( EMSRES_SEND_CMD, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRetransmitMsgsEnabled ) )
			{
				SetResource( EMSRES_RETRANSMIT_MSGS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendMsgsEnabled ) )
			{
				SetResource( EMSRES_SEND_MSGS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGetDataEnabled ) )
			{
				SetResource( EMSRES_GET_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResInitManProcEnabled ) )
			{
				SetResource( EMSRES_INIT_MAN_PROC, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRemoveDataEnabled ) )
			{
				SetResource( EMSRES_REMOVE_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResUploadDataEnabled ) )
			{
				SetResource( EMSRES_UPLOAD_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResProcess406Enabled ) )
			{
				SetResource( EMSRES_PROCESS_406, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResCancelSessionEnabled ) )
			{
				SetResource( EMSRES_CANCEL_SESSION, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGenerateAlertsEnabled ) )
			{
				SetResource( EMSRES_GEN_ALERTS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendDataEnabled ) )
			{
				SetResource( EMSRES_SEND_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRecoverDataEnabled ) )
			{
				SetResource( EMSRES_RECOVER_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGetControlFilenamesEnabled ) )
			{
				SetResource( EMSRES_GET_CONTROL_FILENAMES, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendDataReportEnabled ) )
			{
				SetResource( EMSRES_SEND_DATA_REPORT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResConfigGetEnabled ) )
			{
				SetResource( EMSRES_CONFIG_GET, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResConfigSetStringEnabled ) )
			{
				SetResource( EMSRES_CONFIG_SET_STRING, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAlertSendSolutionsEnabled ) )
			{
				SetResource( EMSRES_ALERT_SEND_SOLNS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAlertTransmitEnabled ) )
			{
				SetResource( EMSRES_ALERT_TRANSMIT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSITTransmitEnabled ) )
			{
				SetResource( EMSRES_SIT_TRANSMIT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioConnectEnabled ) )
			{
				SetResource( EMSRES_AUDIO_CONNECT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioGetDataEnabled ) )
			{
				SetResource( EMSRES_AUDIO_GETDATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioSetParamEnabled ) )
			{
				SetResource( EMSRES_AUDIO_SETPARAM, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioDisconnectEnabled ) )
			{
				SetResource( EMSRES_AUDIO_DISCONNECT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioMakeFreeRequestEnabled ) )
			{
				SetResource( EMSRES_AUDIO_MAKEFREEREQUEST, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioGetFreeRequestDataEnabled ) )
			{
				SetResource( EMSRES_AUDIO_GETFREEREQUESTDATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioCancelFreeRequestEnabled ) )
			{
				SetResource( EMSRES_AUDIO_CANCELFREEREQUEST, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendLocationAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_LOCATION, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendAlarmAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_ALARM, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendWarningAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_WARNING, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendStatusAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_STATUS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendOrbitVectorAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_ORBV, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendTLEAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_TLE, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendPassScheduleAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_PASS_SCHED, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendMetopScheduleAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_METOP_SCHED, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendSARPCalibAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_SARP_CALIB, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendSARRCalibAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_SARR_CALIB, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendStartupAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_STARTUP, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendLEOPassSummaryAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_LEO_PASS_SUMMARY, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendGEOPassSummaryAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_GEO_PASS_SUMMARY, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommandAckAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_CMD_ACK, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommsCheckAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_COMMS_CHECK, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendCommandAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_CMD, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRetransmitMsgsAsCommand ) )
			{
				SetAsCommand( EMSRES_RETRANSMIT_MSGS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendMsgsAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_MSGS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGetDataAsCommand ) )
			{
				SetAsCommand( EMSRES_GET_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResInitManProcAsCommand ) )
			{
				SetAsCommand( EMSRES_INIT_MAN_PROC, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRemoveDataAsCommand ) )
			{
				SetAsCommand( EMSRES_REMOVE_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResUploadDataAsCommand ) )
			{
				SetAsCommand( EMSRES_UPLOAD_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResProcess406AsCommand ) )
			{
				SetAsCommand( EMSRES_PROCESS_406, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResCancelSessionAsCommand ) )
			{
				SetAsCommand( EMSRES_CANCEL_SESSION, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGenerateAlertsAsCommand ) )
			{
				SetAsCommand( EMSRES_GEN_ALERTS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendDataAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResRecoverDataAsCommand ) )
			{
				SetAsCommand( EMSRES_RECOVER_DATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResGetControlFilenamesAsCommand ) )
			{
				SetAsCommand( EMSRES_GET_CONTROL_FILENAMES, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSendDataReportAsCommand ) )
			{
				SetAsCommand( EMSRES_SEND_DATA_REPORT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResConfigGetAsCommand ) )
			{
				SetAsCommand( EMSRES_CONFIG_GET, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResConfigSetStringAsCommand ) )
			{
				SetAsCommand( EMSRES_CONFIG_SET_STRING, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAlertSendSolutionsAsCommand ) )
			{
				SetAsCommand( EMSRES_ALERT_SEND_SOLNS, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAlertTransmitAsCommand ) )
			{
				SetAsCommand( EMSRES_ALERT_TRANSMIT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResSITTransmitAsCommand ) )
			{
				SetAsCommand( EMSRES_SIT_TRANSMIT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioConnectAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_CONNECT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioGetDataAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_GETDATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioSetParamAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_SETPARAM, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioDisconnectAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_DISCONNECT, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioMakeFreeReqAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_MAKEFREEREQUEST, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioGetFreeReqDataAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_GETFREEREQUESTDATA, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszResAudioCancelFreeReqAsCommand ) )
			{
				SetAsCommand( EMSRES_AUDIO_CANCELFREEREQUEST, ( 1 == apConfigData[i]->ValueList[0].bVal ) ? true : false );
			}

			else if( std::wstring::npos != wszTemp.find( cwszLocality ) )
			{
				if( apConfigData[i]->ValueList[0].pwcsVal )
				{
					if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszLocalityLocal ) == 0 )
					{
						SetLocality( DEPLOY_LOCAL );
					}
					else if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszLocalityRemote ) == 0 )
					{
						SetLocality( DEPLOY_REMOTE );
					}
				}
			}
			else if( cwszLatitude == wszTemp )
			{
				SetLatitude( apConfigData[i]->ValueList[0].dVal );
			}
			else if( cwszLongitude == wszTemp )
			{
				SetLongitude( apConfigData[i]->ValueList[0].dVal );
			}
			else if( cwszAltitude == wszTemp )
			{
				SetAltitude( apConfigData[i]->ValueList[0].dVal );
			}
			else if ( wszTemp == cwszType )
			{
				std::wstring	wstrType = apConfigData[i]->ValueList[0].pwcsVal;
				SetLutType( wstrType );
			}
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

	}
	catch( ... )
	{
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