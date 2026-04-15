/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __MEOLUT_CONFIG_CL_H__
#define __MEOLUT_CONFIG_CL_H__

#include "LutConfigCL.h"
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  MEOLUTConfig: public LUTConfig
{
	public:
		MEOLUTConfig();
		MEOLUTConfig( const MEOLUTConfig& x );
		virtual ~MEOLUTConfig();

		string GetPublicKeyFileName() { return m_szPublic_Key_Filename; }
		void   SetPublicKeyFileName( const string& rszPublic_Key_Filename ) { m_szPublic_Key_Filename = rszPublic_Key_Filename; }

		string GetPrivateKeyFileName() { return m_szPrivate_Key_Filename; }
		void   SetPrivateKeyFileName( const string& rszPrivate_Key_Filename ) { m_szPrivate_Key_Filename = rszPrivate_Key_Filename; }

		list<string> GetFPs() { return m_lstFPs; }
		void         SetFPs( const list<string>& rlstFPs ) { m_lstFPs = rlstFPs; }
		
		list<string> GetActiveAnts() { return m_lstActiveAnts; }
		void         SetActiveAnts( const list<string>& rlstActiveFPs ) { m_lstActiveAnts = rlstActiveFPs; }

		list<string> GetAntennas() { return m_lstAntennas; }
		void         SetAntennas( const list<string>& rlstAntennas ) { m_lstAntennas = rlstAntennas; }

		list<string> GetClocks() { return m_lstClocks; }
		void         SetClocks( const list<string>& rlstClocks ) { m_lstClocks = rlstClocks; }

		list<string> GetSPs() { return m_lstSPs; }
		void         SetSPs( const list<string>& rlstSPs ) { m_lstSPs = rlstSPs; }

		list<string> GetLPs() { return m_lstLPs; }
		void         SetLPs( const list<string>& rlstLPs ) { m_lstLPs = rlstLPs; }

		list<string> GetMCCs() { return m_lstMCCs; }
		void         SetMCCs( const list<string>& rlstMCCs ) { m_lstMCCs = rlstMCCs; }

		string GetMQUrl() { return m_szMQUrl; }
		void   SetMQUrl( const string& rszMQUrl ) { m_szMQUrl = rszMQUrl; }

		string GetTrackingMode() { return m_szTrackingMode; }
		void   SetTrackingMode( const string& rszTrackingMode ) { m_szTrackingMode = rszTrackingMode; }

		// Set and Get for Redundancy mode
		string GetRedundancyMode() { return m_szRedundancyMode; }
		void   SetRedundancyMode( const string& rszRedundancyMode ) { m_szRedundancyMode = rszRedundancyMode; }

		bool   IsActiveAntsPresent() { return m_bActiveAntsPresent;}
		void   SetActiveAntsPresnt( bool bPresent ) { m_bActiveAntsPresent = bPresent; }

	private:

	private:
		// security
		string        m_szPublic_Key_Filename;
		string        m_szPrivate_Key_Filename;

		list<string>  m_lstFPs;
		list<string>  m_lstAntennas;
		list<string>  m_lstActiveAnts;
		list<string>  m_lstClocks;
		list<string>  m_lstSPs;
		list<string>  m_lstLPs;
		list<string>  m_lstMCCs;

		bool          m_bActiveAntsPresent;
		
		// mq_url
		string        m_szMQUrl;
		string		  m_szTrackingMode; 
		string		  m_szRedundancyMode;
};

#endif

