/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __WIN_SERVICE_CONFIG_CL_H__
#define __WIN_SERVICE_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) WinServiceConfig
{
	public:
		WinServiceConfig();
		WinServiceConfig( const WinServiceConfig& x );
		virtual ~WinServiceConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		bool   IsRestart();
		string GetRestart() { return m_szRestart; }
		void   SetRestart( const string& rszRestart ) { m_szRestart = rszRestart; }

		int  GetPiriority() { return m_iPiriority; }
		void SetPiriority( int iPiriority ) { m_iPiriority = iPiriority; }

	private:
		string   m_szID;
		string   m_szName;
		string   m_szRestart;

		int      m_iPiriority;
};


class __declspec(dllexport)  WinServicesConfig
{
	public:
		WinServicesConfig();
		WinServicesConfig( const WinServicesConfig& x );
		virtual ~WinServicesConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		float GetCheckPeriod() { return m_fCheckPeriod; }
		void  SetCheckPeriod( float fCheckPeriod ) { m_fCheckPeriod = fCheckPeriod; }

		string GetVersion() { return m_szVersion; }
		void   SetVersion( const string& rszVersion ) { m_szVersion = rszVersion; }

		list<WinServiceConfig> GetWinServices(){ return m_lstWinServices ;}
		void                   SetWinServices( list<WinServiceConfig>& rolstWinServices ){ m_lstWinServices = rolstWinServices;}

		bool GetSericeById( const string& cszServID, WinServiceConfig& roWinSrvConfg );

	private:

	private:
		string         m_szID;
		float          m_fCheckPeriod;
		string         m_szVersion;

		list<WinServiceConfig> m_lstWinServices;
};

#endif

