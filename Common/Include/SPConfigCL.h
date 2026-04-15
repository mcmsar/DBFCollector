/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __SP_CONFIG_CL_H__
#define __SP_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  SPParamsConfig
{
	public:
		SPParamsConfig();
		SPParamsConfig( const SPParamsConfig& x );
		virtual ~SPParamsConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		unsigned long GetPeakWidth(){ return m_ulPeakWidth; }
		void          SetPeakWidth( const unsigned long culPeakWidth ) { m_ulPeakWidth = culPeakWidth; }

		double GetPSThresholdMult(){ return m_dPSThresholdMult; }
		void   SetPSThresholdMult( const double cdPSThresholdMult ) { m_dPSThresholdMult = cdPSThresholdMult; }

		double GetCorrCoefThreshold(){ return m_dCorrCoefThreshold; }
		void   SetCorrCoefThreshold( const double cdCorrCoefThreshold ) { m_dCorrCoefThreshold = cdCorrCoefThreshold; }

		unsigned long GetShiftIndexThreshold(){ return m_ulShiftIndexThreshold; }
		void          SetShiftIndexThreshold( const unsigned long culShiftIndexThreshold ) { m_ulShiftIndexThreshold = culShiftIndexThreshold; }

		unsigned long GetMaxDetections(){ return m_ulMaxDetections; }
		void          SetMaxDetections( const unsigned long culMaxDetections ) { m_ulMaxDetections = culMaxDetections; }

		unsigned long GetMaxGroupCount(){ return m_ulMaxGroupCount; }
		void          SetMaxGroupCount( const unsigned long culMaxGroupCount ) { m_ulMaxGroupCount = culMaxGroupCount; }

		unsigned long GetMaxSubGroupCount(){ return m_ulMaxSubGroupCount; }
		void          SetMaxSubGroupCount( const unsigned long culMaxSubGroupCount ) { m_ulMaxSubGroupCount = culMaxSubGroupCount; }

		double GetMinPowerLevel(){ return m_dMinPowerLevel; }
		void   SetMinPowerLevel( const double cdMinPowerLevel ) { m_dMinPowerLevel = cdMinPowerLevel; }

		double GetFreqRangeHz(){ return m_dFreqRangeHz; }
		void   SetFreqRangeHz( const double cdFreqRangeHz ) { m_dFreqRangeHz = cdFreqRangeHz; }

		double GetTimeRangeSeconds(){ return m_dTimeRangeSeconds; }
		void   SetTimeRangeSeconds( const double cdTimeRangeSeconds ) { m_dTimeRangeSeconds = cdTimeRangeSeconds; }

		double GetAgeoutSeconds(){ return m_dAgeoutSeconds; }
		void   SetAgeoutSeconds( const double cdAgeoutSeconds ) { m_dAgeoutSeconds = cdAgeoutSeconds; }

		int  GetMaxOutOfSpecWindowBitErrors(){ return m_iMaxOutOfSpecWindowBitErrors; }
		void SetMaxOutOfSpecWindowBitErrors( const int ciMaxOutOfSpecWindowBitErrors ){ m_iMaxOutOfSpecWindowBitErrors = ciMaxOutOfSpecWindowBitErrors; }

		int  GetMaxWindowBitErrors(){ return m_iMaxWindowBitErrors; }
		void SetMaxWindowBitErrors( const int ciMaxWindowBitErrors ){ m_iMaxWindowBitErrors = ciMaxWindowBitErrors; }

		int  GetMaxFSErrors(){ return m_iMaxFSErrors; }
		void SetMaxFSErrors( const int ciMaxFSErrors ){ m_iMaxFSErrors = ciMaxFSErrors; }

		int  GetMaxPDF1Errors(){ return m_iMaxPDF1Errors; }
		void SetMaxPDF1Errors( const int ciMaxPDF1Errors ){ m_iMaxPDF1Errors = ciMaxPDF1Errors; }

		int  GetMaxPDF2Errors(){ return m_iMaxPDF2Errors; }
		void SetMaxPDF2Errors( const int ciMaxPDF2Errors ){ m_iMaxPDF2Errors = ciMaxPDF2Errors; }

		double GetFreqOffset(){ return m_dFreqOffset; }
		void   SetFreqOffset( const double cdFreqOffset ) { m_dFreqOffset = cdFreqOffset; }

		double GetTimeOffset(){ return m_dTimeOffset; }
		void   SetTimeOffset( const double cdTimeOffset ) { m_dTimeOffset = cdTimeOffset; }

		int  GetSyncBitsCount(){ return m_iSyncBitsCount; }
		void SetSyncBitsCount( const int ciSyncBitsCount ){ m_iSyncBitsCount = ciSyncBitsCount; }

	private:

	private:
		string         m_szID;
		unsigned long  m_ulPeakWidth;
		double         m_dPSThresholdMult;
		double         m_dCorrCoefThreshold;
		unsigned long  m_ulShiftIndexThreshold;
		unsigned long  m_ulMaxDetections;
		unsigned long  m_ulMaxGroupCount;
		unsigned long  m_ulMaxSubGroupCount;
		double         m_dMinPowerLevel;
		double         m_dFreqRangeHz;
		double         m_dTimeRangeSeconds;
		double         m_dAgeoutSeconds;
		int            m_iMaxOutOfSpecWindowBitErrors;
		int            m_iMaxWindowBitErrors;
		int            m_iMaxFSErrors;
		int            m_iMaxPDF1Errors;
		int            m_iMaxPDF2Errors;
		double         m_dFreqOffset;
		double         m_dTimeOffset;
		int            m_iSyncBitsCount;
};

class __declspec(dllexport)  SPConfig
{
	public:
		SPConfig();
		SPConfig( const SPConfig& x );
		virtual ~SPConfig();

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

		//list<string> GetSPPlugins() { return m_lstSPPlugins; }
		//void         SetSPPlugins( const list<string>& rlstStrings ) { m_lstSPPlugins = rlstStrings; }

		string GetSignalProcessorConfig() { return m_szXMLSignalProcessorConfig; }
		void   SetSignalProcessorConfig( const string& rszSPConfg ) { m_szXMLSignalProcessorConfig = rszSPConfg; }

		string GetSignalConditionerConfig() { return m_szXMLSignalConditionerConfig; }
		void   SetSignalConditionerConfig( const string& rszSCConfg ) { m_szXMLSignalConditionerConfig = rszSCConfg; }

		string GetMIServerConfig() { return m_szXMLMIServerConfig; }
		void   SetMIServerConfig( const string& rszMIServerConfig ) { m_szXMLMIServerConfig = rszMIServerConfig; }

		string GetSocketServerConfig() { return m_szXMLSocketServerConfig; }
		void   SetSocketServerConfig( const string& rszSocketServerConfig ) { m_szXMLSocketServerConfig = rszSocketServerConfig; }

		string GetSPParams() { return m_szSPParams; }
		void   SetSPParams( const string& rszSPParams ) { m_szSPParams = rszSPParams; }

		string GetDataManager() { return m_szDataManager; }
		void   SetDataManager( const string& rszDataManager ) { m_szDataManager = rszDataManager; }

		string GetServicesID() { return m_szServicesID; }
		void   SetServicesID( const string& rszServicesID ) { m_szServicesID = rszServicesID; }

	private:

	private:
		string        m_szID;

		// sp_info
		string        m_szDescription;
		string        m_szHW;
		string        m_szOS;
		double        m_dSW;

		// signal_processor_config
		//list<string> m_lstSPPlugins;
		string        m_szXMLSignalProcessorConfig;

		// signal_conditioner_config
		string        m_szXMLSignalConditionerConfig;


		// miserver_config
		string        m_szXMLMIServerConfig;

		// socket_server_config
		string        m_szXMLSocketServerConfig;

		// sp_parameter
		string        m_szSPParams;

		// data_manager
		string        m_szDataManager;

		// services_id
		string        m_szServicesID;

};

#endif

