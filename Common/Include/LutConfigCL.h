/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __LUT_CONFIG_CL_H__
#define __LUT_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  LUTConfig
{
	public:
		LUTConfig();
		LUTConfig( const LUTConfig& x );
		virtual ~LUTConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		string GetType() { return m_szType; }
		void   SetType( const string& rszType ) { m_szType = rszType; }

		string GetVersion() { return m_szVersion; }
		void   SetVersion( const string& rszVersion ) { m_szVersion = rszVersion; }

		string GetDescription() { return m_szDescription; }
		void   SetDescription( const string& rszDescription ) { m_szDescription = rszDescription; }

		double GetLatitude() { return m_dLatitude; }
		void   SetLatitude( const double cdLatitude ) { m_dLatitude = cdLatitude; }

		double GetLongitude() { return m_dLongitude; }
		void   SetLongitude( const double cdLongitude ) { m_dLongitude = cdLongitude; }

		double GetAltitude() { return m_dAltitude; }
		void   SetAltitude( const double cdAltitude ) { m_dAltitude = cdAltitude; }

	private:

	private:
		string        m_szID;

		// lut_info
		string        m_szName;
		string        m_szType;
		string        m_szVersion;
		string        m_szDescription;

		// locaiton
		double        m_dLatitude;
		double        m_dLongitude;
		double        m_dAltitude;
};

#endif

