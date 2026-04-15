/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __ANT_CONFIG_H__
#define __ANT_CONFIG_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  EMSAntennaConfig
{
	public:
		EMSAntennaConfig();
		EMSAntennaConfig( const EMSAntennaConfig& x );
		virtual ~EMSAntennaConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		int    GetAntID() { return m_iAntID; }
		void   SetAntID( const int ciAntID ) { m_iAntID = ciAntID; }

		int    GetStatusCheckIntvl() { return m_iStatusCheckIntvl; }
		void   SetStatusCheckIntvl( const int ciStatusCheckIntvl ) { m_iStatusCheckIntvl = ciStatusCheckIntvl; }

		string GetType() { return m_szType; }
		void   SetType( const string& rszType ) { m_szType = rszType; }

		string GetDescription() { return m_szDescription; }
		void   SetDescription( const string& rszDescription ) { m_szDescription = rszDescription; }

		double GetLatitude() { return m_dLatitude; }
		void   SetLatitude( const double cdLatitude ) { m_dLatitude = cdLatitude; }

		double GetLongitude() { return m_dLongitude; }
		void   SetLongitude( const double cdLongitude ) { m_dLongitude = cdLongitude; }

		double GetAltitude() { return m_dAltitude; }
		void   SetAltitude( const double cdAltitude ) { m_dAltitude = cdAltitude; }

		double GetMinEl() { return m_dMinEl; }
		void   SetMinEl( const double cdMinEl ) { m_dMinEl = cdMinEl; }

		double GetMaxEl() { return m_dMaxEl; }
		void   SetMaxEl( const double cdMaxEl ) { m_dMaxEl = cdMaxEl; }

		double GetMinAz() { return m_dMinAz; }
		void   SetMinAz( const double cdMinAz ) { m_dMinAz = cdMinAz; }

		double GetMaxAz() { return m_dMaxAz; }
		void   SetMaxAz( const double cdMaxAz ) { m_dMaxAz = cdMaxAz; }

		string GetAntControllerXMLConfig() { return m_szAntControllerXML; }
		void   SetAntControllerXMLConfig( const string& rszAntControllerXML ) { m_szAntControllerXML = rszAntControllerXML; }

		list<unsigned long> GetSatellites() {return m_lstSats;}
		void   SetSatellites( const list<unsigned long> clstSats ){ m_lstSats = clstSats;}

private:

	private:
		string        m_szID;

		int           m_iAntID;
		int           m_iStatusCheckIntvl;
		//info_ant
		string        m_szType;
		string        m_szDescription;

		// location
		double        m_dLatitude;
		double        m_dLongitude;
		double        m_dAltitude;

		//el_min
		double        m_dMinEl;
		//el_max
		double        m_dMaxEl;
		//az_min
		double        m_dMinAz;
		//az_max 
		double        m_dMaxAz;

		// antenna_controller
		string        m_szAntControllerXML;

		// satellites
		list<unsigned long> m_lstSats;
};

#endif

