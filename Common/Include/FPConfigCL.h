/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __FP_CONFIG_CL_H__
#define __FP_CONFIG_CL_H__

#include "UserConfigCL.h"
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  FPConfig
{
	public:
		FPConfig();
		FPConfig( const FPConfig& x );
		virtual ~FPConfig();

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

		string GetURL() { return m_szURL; }
		void   SetURL( const string& rszURL ) { m_szURL = rszURL; }

		string GetURLUserName() { return m_szURLUserName; }
		void   SetURLUserName( const string& rszURLUserName ) { m_szURLUserName = rszURLUserName; }

		string GetURLPassword() { return m_szURLPassword; }
		void   SetURLPassword( const string& rszURLPassword ) { m_szURLPassword = rszURLPassword; }

		string GetAntennaComponent() { return m_szAntennaComp; }
		void   SetAntennaComponent( const string& rszAntennaComponent ) { m_szAntennaComp = rszAntennaComponent; }

		list<UserConfig> GetUsers() { return m_lstUsers; }
		void             SetUsers( const list<UserConfig>& rlstUsers ) { m_lstUsers = rlstUsers; }

		string GetUsersXML() { return m_szUsers; }
		void   SetUsersXML( const string& rstrXML ) { m_szUsers = rstrXML; }

		//string GetBoardID() { return m_szBoardID; }
		//void   SetBoardID( const string& rszBoardID ) { m_szBoardID = rszBoardID; }

		//int  GetNumOfChannels() { return m_iChannelNum; }
		//void SetNumOfChannels( int iChannelNum ) { m_iChannelNum = iChannelNum ; }

		//string GetExternalClocking() { return m_szExternalClocking; }
		//void   SetExternalClocking( const string& rszExternalClocking ) { m_szExternalClocking = rszExternalClocking; }

		//list<string> GetDataStreams() { return m_lstDataStreams; }
		//void         SetDataStreams( const list<string>& rlstStrings ) { m_lstDataStreams = rlstStrings; }

		string GetDataStreams() { return m_szDataStreams; }
		void   SetDataStreams( const string& rstrXML ) { m_szDataStreams = rstrXML; }

		string GetSchedFolder() { return m_szSchedFolder; }
		void   SetSchedFolder( const string& rszSchedFolder ) { m_szSchedFolder = rszSchedFolder; }

		string GetPairsConfig() { return m_szPairsConfig; }
		void   SetPairsConfig( const string& rszPairsConfig ) { m_szPairsConfig = rszPairsConfig; }

		//list<string> GetPairs() { return m_lstPairs; }
		//void         SetPairs( const list<string>& rlstStrings ) { m_lstPairs = rlstStrings; }

		string GetDCWebServices() { return m_szDCWebServices; }
		void   SetDCWebServices( const string& rstrXML ) { m_szDCWebServices = rstrXML; }
		
		string GetFPWebServices() { return m_szFPWebServices; }
		void   SetFPWebServices( const string& rstrXML ) { m_szFPWebServices = rstrXML; }

		string GetDCPlugins() { return m_szDCPlugins; }
		void   SetDCPlugins( const string& rstrXML ) { m_szDCPlugins = rstrXML; }

		string GetCollectorOutput() { return m_szCollectorOutput; }
		void   SetCollectorOutput( const string& rszCollectorOutput ) { m_szCollectorOutput = rszCollectorOutput; }

		string GetDataManager() { return m_szDataManager; }
		void   SetDataManager( const string& rszDataManager ) { m_szDataManager = rszDataManager; }

		string GetServicesID() { return m_szServicesID; }
		void   SetServicesID( const string& rszServicesID ) { m_szServicesID = rszServicesID; }

		int  GetAlarmMinPPSLostCount() { return m_iAlarmMinPPSLostCount; }
		void SetAlarmMinPPSLostCount( int iAlarmMinPPSLostCount ) { m_iAlarmMinPPSLostCount = iAlarmMinPPSLostCount; }

private:

	private:
		string        m_szID;

		// fp_info
		string        m_szDescription;
		string        m_szHW;
		string        m_szOS;
		double        m_dSW;

		// fp_url
		string        m_szURL;
		string        m_szURLUserName;
		string        m_szURLPassword;

		// Antenna component
		string        m_szAntennaComp;

		// users
		list<UserConfig> m_lstUsers;
		string           m_szUsers;

		// adboard - currently in datastreams
		//string        m_szBoardID;
		//int           m_iChannelNum;
		//string        m_szExternalClocking;

		// datastreams
		//list<string> m_lstDataStreams;
		string        m_szDataStreams;

		// schedule
		string        m_szSchedFolder;

		// pairs
		string        m_szPairsConfig;
		//list<string>  m_lstPairs;

		// dc_ebservices
		//list<string>  m_lstWebServices;
		string        m_szDCWebServices;

		// fp_ebservices
		string        m_szFPWebServices;

		// dc_plugins
		//list<string>  m_lstDCPlugins;
		string        m_szDCPlugins;

		// Collector output
		string        m_szCollectorOutput;

		// data_manager
		string        m_szDataManager;

		// services_id
		string        m_szServicesID;

		// alarm_min_pps_lost_count
		int           m_iAlarmMinPPSLostCount;
		// Clock component
		//string        m_szClockComp;

};

#endif

