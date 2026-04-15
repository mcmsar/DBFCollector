/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __SAT_CONFIG_H__
#define __SAT_CONFIG_H__

#include <string>
using namespace std;

class __declspec(dllexport)  SatConfig
{
	public:
		SatConfig();
		SatConfig( const SatConfig& x );
		virtual ~SatConfig();

		long GetSatID() { return m_lSatID; }
		void SetSatID( const long clSatID ) { m_lSatID = clSatID; }
		
		long GetNoradID() { return m_lNoradID; }
		void SetNoradID( const long clNoradID ) { m_lNoradID = clNoradID; }

		string GetConstellation() { return m_szConstellation; }
		void   SetConstellation( const string& rszConstellation ) { m_szConstellation = rszConstellation; }

		long GetVersion() { return m_lVersion; }
		void SetVersion( const long clVersion ) { m_lVersion = clVersion; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		long GetSlot() { return m_lSlot; }
		void SetSlot( const long clSlot ) { m_lSlot = clSlot; }

		long GetChannel() { return m_lChannel; }
		void SetChannel( const long clChannel ) { m_lChannel = clChannel; }

		long GetLaunch() { return m_lLaunch; }
		void SetLaunch( const long clLaunch ) { m_lLaunch = clLaunch; }

		bool GetPhaseMod() { return m_bPhaseMod; }
		void SetPhaseMod( const bool cbPhaseMod ) { m_bPhaseMod = cbPhaseMod; }

		bool GetInversion() { return m_bInversion; }
		void SetInversion( const bool cbInversion ) { m_bInversion = cbInversion; }

		string GetPolarization() { return m_szPolarization; }
		void   SetPolarization( const string& rszPolarization ) { m_szPolarization = rszPolarization; }

		long GetBandwidth() { return m_lBandwidth; }
		void SetBandwidth( const long clBandwidth ) { m_lBandwidth = clBandwidth; }

		double GetDLFrequency() { return m_dDLFrequency; }
		void   SetDLFrequency( const double cdDLFrequency ) { m_dDLFrequency = cdDLFrequency; }

		double GetDLFrequencyVar() { return m_dDLFrequencyVar; }
		void   SetDLFrequencyVar( const double cdDLFrequencyVar ) { m_dDLFrequencyVar = cdDLFrequencyVar; }

		double GetGroupDelay() { return m_dGroupDelay; }
		void   SetGroupDelay( const double cdGroupDelay ) { m_dGroupDelay = cdGroupDelay; }

		double GetGroupDelayVar() { return m_dGroupDelayVar; }
		void   SetGroupDelayVar( const double cdGroupDelayVar ) { m_dGroupDelayVar = cdGroupDelayVar; }

		long GetBBFrequency() { return m_lBBFrequency; }
		void SetBBFrequency( const long clBBFrequency ) { m_lBBFrequency = clBBFrequency; }

		long GetStartFrequency() { return m_lStartFrequency; }
		void SetStartFrequency( const long clStartFrequency ) { m_lStartFrequency = clStartFrequency; }

		long GetStopFrequency() { return m_lStopFrequency; }
		void SetStopFrequency( const long clStopFrequency ) { m_lStopFrequency = clStopFrequency; }

		long GetPriority() { return m_lPriority; }
		void SetPriority( const long clPriority ) { m_lPriority = clPriority; }

		double GetPositionThreshold() { return m_dPositionThreshold; }
		void   SetPositionThreshold( const double cdPositionThreshold ) { m_dPositionThreshold = cdPositionThreshold; }

		double GetVelocityThreshold() { return m_dVelocityThreshold; }
		void   SetVelocityThreshold( const double cdVelocityThreshold ) { m_dVelocityThreshold = cdVelocityThreshold; } 

		double GetCentreFreq406() { return m_dCentreFreq406; }
		void   SetCentreFreq406( const double cdCentreFreq406 ) { m_dCentreFreq406 = cdCentreFreq406; } 

		double GetPriorityDelayTLE()  { return m_dPriorityDelayTLE; }
		void   SetPriorityDelayTLE( double dPriorityDelayTLE ) { m_dPriorityDelayTLE = dPriorityDelayTLE; }

		double GetPriorityDelayGSC()  { return m_dPriorityDelayGSC; }
		void   SetPriorityDelayGSC( double dPriorityDelayGSC ) { m_dPriorityDelayGSC = dPriorityDelayGSC; }

		double GetPriorityDelaySIS()  { return m_dPriorityDelaySIS; }
		void   SetPriorityDelaySIS( double dPriorityDelaySIS ) { m_dPriorityDelaySIS = dPriorityDelaySIS; }

		double GetPriorityDelayGSCPredict()  { return m_dPriorityDelayGSCPredict; }
		void   SetPriorityDelayGSCPredict( double dPriorityDelayGSCPredict ) { m_dPriorityDelayGSCPredict = dPriorityDelayGSCPredict; }


	private:

	private:
		long          m_lSatID;
		
		// info_sat
		long          m_lNoradID;
		string        m_szConstellation;
		long          m_lVersion;
		string        m_szName;
		long          m_lSlot;
		long          m_lChannel;
		long          m_lLaunch;
		
		// signal_sat
		bool          m_bPhaseMod;
		bool          m_bInversion;
		string        m_szPolarization;
		long          m_lBandwidth;
		double        m_dDLFrequency;
		double        m_dDLFrequencyVar;
		double        m_dGroupDelay;
		double        m_dGroupDelayVar;

		// process
		long          m_lBBFrequency;
		long          m_lStartFrequency;
		long          m_lStopFrequency;
		double		  m_dCentreFreq406;

		//priority delay
		double		m_dPriorityDelayTLE;
		double		m_dPriorityDelaySIS;
		double		m_dPriorityDelayGSC;
		double		m_dPriorityDelayGSCPredict;


		// orbit
		long          m_lPriority;
		double        m_dPositionThreshold;
		double        m_dVelocityThreshold;
};

#endif

