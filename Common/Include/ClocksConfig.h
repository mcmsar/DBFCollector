/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __CLOCKS_CONFIG_H__
#define __CLOCKS_CONFIG_H__

#include <string>
using namespace std;

class __declspec(dllexport)  EMSClocksConfig
{
	public:
		EMSClocksConfig();
		EMSClocksConfig( const EMSClocksConfig& x );
		virtual ~EMSClocksConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& cszID ) { m_szID = cszID; }

		double GetTimeZoneBias() { return m_dTimeZoneBias; }
		void   SetTimeZoneBias( const double cdTimeZoneBias ) { m_dTimeZoneBias = cdTimeZoneBias; }

		double GetCheckTime() { return m_dCheckTime; }
		void   SetCheckTime( const double cdCheckTime ) { m_dCheckTime = cdCheckTime; }

		double GetCheckEphemeris() { return m_dCheckEphemeris; }
		void   SetCheckEphemeris( const double cdCheckEphemeris ) { m_dCheckEphemeris = cdCheckEphemeris; }

		int    GetLeapSeconds() { return m_iLeapSeconds; }
		void   SetLeapSeconds( const int ciLeapSeconds ) { m_iLeapSeconds = ciLeapSeconds; }

private:

	private:
		string        m_szID;
		// time_zone_bias
		double        m_dTimeZoneBias;
		// check_time
		double        m_dCheckTime;
		// check_ephemeris
		double        m_dCheckEphemeris;
		// leap_seconds
		int           m_iLeapSeconds;
};

#endif

