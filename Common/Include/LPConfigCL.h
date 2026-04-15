/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __LP_CONFIG_CL_H__
#define __LP_CONFIG_CL_H__

#include "UserConfigCL.h"
#include "FolderConfigCL.h"
#include "FPorbConfigCL.h"
#include "WebServiceConfigCL.h"
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  LPParamsConfig
{
	public:
		LPParamsConfig();
		LPParamsConfig( const LPParamsConfig& x );
		virtual ~LPParamsConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetPSConfig() { return m_szPSConfig; }
		void   SetPSConfig( const string& rszPSConfig ) { m_szPSConfig = rszPSConfig; }

		string GetABSConfig() { return m_szABSConfig; }
		void   SetABSConfig( const string& rszABSConfig ) { m_szABSConfig = rszABSConfig; }

		int  GetAlarmCount(){ return m_iAlarmCount; }
		void SetAlarmCount( const int ciAlarmCount ){ m_iAlarmCount = ciAlarmCount; }

		int  GetAlarmThreshold(){ return m_iAlarmThreshold; }
		void SetAlarmThreshold( const int ciAlarmThreshold ){ m_iAlarmThreshold = ciAlarmThreshold; }

		double GetFreqFilterGain(){ return m_dFreqFilterGain; }
		void   SetFreqFilterGain( const double cdFreqFilterGain ) { m_dFreqFilterGain = cdFreqFilterGain; }

		double GetFreqFilterThreshold(){ return m_dFreqFilterThreshold; }
		void   SetFreqFilterThreshold( const double cdFreqFilterThreshold ) { m_dFreqFilterThreshold = cdFreqFilterThreshold; }

		double GetTimeFilterGain(){ return m_dTimeFilterGain; }
		void   SetTimeFilterGain( const double cdTimeFilterGain ) { m_dTimeFilterGain = cdTimeFilterGain; }

		double GetTimeFilterThreshold(){ return m_dTimeFilterThreshold; }
		void   SetTimeFilterThreshold( const double cdTimeFilterThreshold ) { m_dTimeFilterThreshold = cdTimeFilterThreshold; }

		double GetCNRFilterThreshold(){ return m_dCNRFilterThreshold; }
		void   SetCNRFilterThreshold( const double cdCNRFilterThreshold ) { m_dCNRFilterThreshold = cdCNRFilterThreshold; }

		int  GetFrameBitThreshold(){ return m_iFrameBitThreshold; }
		void SetFrameBitThreshold( const int ciFrameBitThreshold ){ m_iFrameBitThreshold = ciFrameBitThreshold; }

	private:

	private:
		string         m_szID;
		// ps
		string         m_szPSConfig;
		// abs
		string         m_szABSConfig;
		// calibration
		int            m_iAlarmCount;
		int            m_iAlarmThreshold;
		double         m_dFreqFilterGain;
		double         m_dFreqFilterThreshold;
		double         m_dTimeFilterGain;
		double         m_dTimeFilterThreshold;
		double         m_dCNRFilterThreshold;
		int            m_iFrameBitThreshold;
};

class __declspec(dllexport)  LPConfig
{
	public:
		LPConfig();
		LPConfig( const LPConfig& x );
		virtual ~LPConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetDescription() { return m_szDescription; }
		void   SetDescription( const string& rszDescription ) { m_szDescription = rszDescription; }

		string GetHW() { return m_szHW; }
		void   SetHW( const string& rszHW ) { m_szHW = rszHW; }

		string GetOS() { return m_szOS; }
		void   SetOS( const string& rszOS ) { m_szOS = rszOS; }

		double GetSW() { return m_dSW; }
		void   SetSW( const double dSW ) { m_dSW = dSW; }

		list<UserConfig> GetUsers() { return m_lstUsers; }
		void             SetUsers( const list<UserConfig>& rlstUsers ) { m_lstUsers = rlstUsers; }

		string GetUsersXML() { return m_szUsers; }
		void   SetUsersXML( const string& rstrXML ) { m_szUsers = rstrXML; }

		long    GetMaxFileSizeMB() { return m_lMax_filesize_mb; }
		void    SetMaxFileSizeMB( const long lMax_filesize_mb ) { m_lMax_filesize_mb = lMax_filesize_mb; }

		long    GetOutputPeriodMinutes() { return m_lOutput_period_minutes; }
		void    SetOutputPeriodMinutes( const long lOutput_period_minutes) { m_lOutput_period_minutes = lOutput_period_minutes; }

		string  GetOutputFolder() { return m_szOutput_folder; }
		void    SetOutputFolder( const string& rszOutput_folder ) { m_szOutput_folder = rszOutput_folder; }

		string  GetGNSSType() { return m_szGNSS_Type; }
		void    SetGNSSType( const string& rszGNSS_Type ) { m_szGNSS_Type = rszGNSS_Type; }

		string  GetIpAddress() { return m_szIp_address; }
		void    SetIpAddress( const string& rszIp_address ) { m_szIp_address = rszIp_address; }

		string  GetPortId() { return m_szPort_id; }
		void    SetPortId( const string& rszPort_id ) { m_szPort_id = rszPort_id; }

		string  GetPassword() { return m_szPassword; }
		void    SetPassword( const string& rszPassword ) { m_szPassword = rszPassword; }

		long    GetAllowedGpsTimeDifference() { return m_lAllowed_gps_time_difference; }
		void    SetAllowedGpsTimeDifference( const long lAllowed_gps_time_difference ) { m_lAllowed_gps_time_difference = lAllowed_gps_time_difference; }

		long    GetSecondsBeforeReportGpsFailure() { return m_lSeconds_before_report_gps_failure; }
		void    SetSecondsBeforeReportGpsFailure( const long lValue ) { m_lSeconds_before_report_gps_failure = lValue; }

		long    GetSecondsUnreasonableGpsTimeDifference() { return m_lSeconds_unreasonable_gps_time_difference; }
		void    SetSecondsUnreasonableGpsTimeDifference( const long lValue ) { m_lSeconds_unreasonable_gps_time_difference = lValue; }

		bool	GetOverrideDateOnSync() { return m_bOverride_date_on_sync; }
		void	SetOverrideDateOnSync( const bool bValue ) { m_bOverride_date_on_sync = bValue; }

		long    GetPeriod() { return m_lPeriod; }
		void    SetPeriod( const long lPeriod ) { m_lPeriod = lPeriod; }

		list<FolderConfig> GetFolders() { return m_lstFolders; }
		void               SetFolders( const list<FolderConfig>& rlstFolders ) { m_lstFolders = rlstFolders; }

		list<FPorbConfig> GetFPsorb() { return m_lstFPsorb; }
		void              SetFPsorb( const list<FPorbConfig>& rlstFPsorb ) { m_lstFPsorb = rlstFPsorb; }

		list<WebServiceConfig> GetWebServiceConfig() {return m_lstWebServices; }
		void                   SetWebServiceConfig( const list<WebServiceConfig>& rlstWebServices ) { m_lstWebServices = rlstWebServices; }

		string GetUrlRecvWS() { return m_szUrlRecvWSXML; }
		void   SetUrlRecvWS( const string& rstrXML ) { m_szUrlRecvWSXML = rstrXML; }

		string GetPassSchedWS() { return m_szPassSchedWSXML; }
		void   SetPassSchedWS( const string& rstrXML ) { m_szPassSchedWSXML = rstrXML; }

		string GetClockComponent() { return m_szClockComponent; }
		void   SetClockComponent( const string& rszClockComponent ) { m_szClockComponent = rszClockComponent; }

		string GetLPParams() { return m_szLPParams; }
		void   SetLPParams( const string& rszLPParams ) { m_szLPParams = rszLPParams; }

		string GetDataManager() { return m_szDataManager; }
		void   SetDataManager( const string& rszDataManager ) { m_szDataManager = rszDataManager; }

		double GetCacheLifeSpan() { return m_dCacheLifeSpan; }
		void   SetCacheLifeSpan( const double dCacheLifeSpan ) { m_dCacheLifeSpan = dCacheLifeSpan; }

		unsigned long GetCacheMaxResults() { return m_ulCacheMaxResults;}
		void  SetCacheMaxResults( const unsigned long culCacheMaxResults ) { m_ulCacheMaxResults = culCacheMaxResults;}

		string GetDefaultConnection() { return m_szDefaultConnection; }
		void   SetDefaultConnection( const string& rszDefaultConnection ) { m_szDefaultConnection = rszDefaultConnection; }

		string GetDBDirectory() { return m_szDBDirectory; }
		void   SetDBDirectory( const string& rszDBDirectory ) { m_szDBDirectory = rszDBDirectory; }

		string GetOutputDirectory() { return m_szOutputDirectory; }
		void   SetOutputDirectory( const string& rszOutputDirectory ) { m_szOutputDirectory = rszOutputDirectory; }

		unsigned long GetMaxReturnRecords() { return m_ulMaxReturnRecords;}
		void  SetMaxReturnRecords( const unsigned long culMaxReturnRecords ) { m_ulMaxReturnRecords = culMaxReturnRecords;}

		unsigned long GetMaxPipelineRetry() { return m_ulMaxPipelineRetry;}
		void  SetMaxPipelineRetry( const unsigned long culMaxPipelineRetry ) { m_ulMaxPipelineRetry = culMaxPipelineRetry;}

		unsigned long GetDeleteTimeout() { return m_ulDeleteTimeout;}
		void  SetDeleteTimeout( const unsigned long culDeleteTimeout ) { m_ulDeleteTimeout = culDeleteTimeout;}

		unsigned long GetQueryTimeout() { return m_ulQueryTimeout;}
		void  SetQueryTimeout( const unsigned long culQueryTimeout ) { m_ulQueryTimeout = culQueryTimeout;}

		string GetServicesID() { return m_szServicesID; }
		void   SetServicesID( const string& rszServicesID ) { m_szServicesID = rszServicesID; }

		string GetLPCControlFileDir() { return m_szLPCControlFileDir; }
		void   SetLPCControlFileDir( const string& rszLPCControlFileDir ) { m_szLPCControlFileDir = rszLPCControlFileDir; }

	private:

	private:
		string        m_szID;

		// lp_info
		string        m_szDescription;
		string        m_szHW;
		string        m_szOS;
		double        m_dSW;

		// users
		list<UserConfig> m_lstUsers;
		string           m_szUsers;

		// log_aggregator_config
		long          m_lMax_filesize_mb;
		long          m_lOutput_period_minutes;
		string        m_szOutput_folder;

		//gnss
		string		m_szGNSS_Type;
		string		m_szIp_address;
		string		m_szPort_id;
		string		m_szPassword;
		long		m_lAllowed_gps_time_difference;
		long		m_lSeconds_before_report_gps_failure;
		long		m_lSeconds_unreasonable_gps_time_difference;
		bool		m_bOverride_date_on_sync;

		// orbit_distributor
		long               m_lPeriod;
		list<FolderConfig> m_lstFolders;
		list<FPorbConfig>  m_lstFPsorb;

		// Webservices
		list<WebServiceConfig> m_lstWebServices;
		string             m_szUrlRecvWSXML;
		string             m_szPassSchedWSXML;

		// clock_component
		string        m_szClockComponent;

		// lp_parameter
		string        m_szLPParams;

		// data_manager
		string        m_szDataManager;

		// services_id
		string        m_szServicesID;

		// lpc_control_file_directory
		string        m_szLPCControlFileDir;

		// dal_config
		double          m_dCacheLifeSpan;
		unsigned long   m_ulCacheMaxResults;
		string			m_szDefaultConnection;
		string			m_szDBDirectory;
		string			m_szOutputDirectory;
		unsigned long   m_ulMaxReturnRecords;
		unsigned long   m_ulMaxPipelineRetry;
		unsigned long   m_ulDeleteTimeout;
		unsigned long   m_ulQueryTimeout;
};

#endif

