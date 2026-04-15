/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __BEACON_CONFIG_H__
#define __BEACON_CONFIG_H__

#include <string>
using namespace std;

class __declspec(dllexport)  BeaconConfig
{
	public:
		BeaconConfig();
		BeaconConfig( const BeaconConfig& x );
		virtual ~BeaconConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetType() { return m_szType; }
		void   SetType( const string& rszType ) { m_szType = rszType; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		string GetBeaconMsg() { return m_szMsg; }
		void   SetBeaconMsg( const string& rszMsg ) { m_szMsg = rszMsg; }

		double GetLatitude() { return m_dLatitude; }
		void   SetLatitude( const double cdLatitude ) { m_dLatitude = cdLatitude; }

		double GetLongitude() { return m_dLongitude; }
		void   SetLongitude( const double cdLongitude ) { m_dLongitude = cdLongitude; }

		double GetAltitude() { return m_dAltitude; }
		void   SetAltitude( const double cdAltitude ) { m_dAltitude = cdAltitude; }

		double GetModeIndex() { return m_dModeIndex; }
		void   SetModeIndex( const double cdModeIndex ) { m_dModeIndex = cdModeIndex; }

		double GetPower() { return m_dPower; }
		void   SetPower( const double cdPower ) { m_dPower = cdPower; }

		double GetFrequency() { return m_dFrequency; }
		void   SetFrequency( const double cdFrequency ) { m_dFrequency = cdFrequency; }

		double GetRepRate() { return m_dRepRate; }
		void   SetRepRate( const double cdRepRate ) { m_dRepRate = cdRepRate; }

		long GetBitRate() { return m_lBitRate; }
		void SetBitRate( const long clBitRate ) { m_lBitRate = clBitRate; }

		double GetExpectedTime() { return m_dExpectedTime; }
		void   SetExpectedTime( const double cdExpectedTime ) { m_dExpectedTime = cdExpectedTime; }
		
		bool GetActiveFlag() { return m_bActive_Flag; }
		void SetActiveFlag( const bool cbActiveFlag ) { m_bActive_Flag = cbActiveFlag; }

		bool GetOrbitFlag() { return m_bOrbit_Flag; }
		void SetOrbitFlag( const bool cbOrbit_Flag ) { m_bOrbit_Flag = cbOrbit_Flag; }

		bool GetTOAFlag() { return m_bTOA_Flag; }
		void SetTOAFlag( const bool cbTOA_Flag ) { m_bTOA_Flag = cbTOA_Flag; }

		bool GetFOAFlag() { return m_bFOA_Flag; }
		void SetFOAFlag( const bool cbFOA_Flag ) { m_bFOA_Flag = cbFOA_Flag; }

		bool GetMCCSuppressFlag() { return m_bMCC_Suppress_Flag; }
		void SetMCCSuppressFlag( const bool cbMCC_Suppress_Flag ) { m_bMCC_Suppress_Flag = cbMCC_Suppress_Flag; }

		bool GetMCCSuppressBcnAdvisoryFlag() { return m_bMCC_Suppress_Bcn_Advisory_Flag; }
		void SetMCCSuppressBcnAdvisoryFlag( const bool cbMCC_Suppress_Bcn_Advisory_Flag ) { m_bMCC_Suppress_Bcn_Advisory_Flag = cbMCC_Suppress_Bcn_Advisory_Flag; }

		bool GetQMSFlag() { return m_bQMS_Flag; }
		void SetQMSFlag( const bool cbQMS_Flag ) { m_bQMS_Flag = cbQMS_Flag; }

	private:

	private:
		string        m_szID;

		// bea_info
		string        m_szType;
		string        m_szName;
		string        m_szMsg;

		// location
		double        m_dLatitude;
		double        m_dLongitude;
		double        m_dAltitude;

		// signal_bea
		double        m_dModeIndex;
		double        m_dPower;
		double        m_dFrequency;
		double        m_dRepRate;
		long          m_lBitRate;
		double        m_dExpectedTime;

		// flags
		bool          m_bActive_Flag;
		bool          m_bOrbit_Flag;
		bool          m_bTOA_Flag;
		bool          m_bFOA_Flag;
		bool          m_bMCC_Suppress_Flag;
		bool          m_bMCC_Suppress_Bcn_Advisory_Flag;
		bool          m_bQMS_Flag;
};

#endif

