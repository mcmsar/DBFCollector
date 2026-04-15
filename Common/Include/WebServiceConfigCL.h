/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __WEB_SERVICE_CONFIG_CL_H__
#define __WEB_SERVICE_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) WebServiceConfig
{
	public:
		WebServiceConfig();
		WebServiceConfig( const string& rszWSHost, const string& rszWSPortID, const long rlWSBacklog, const bool rbWSAuthenticate, const string& rszWSUsersFile,
			              const string& rszWS_ssl_keyfile, const string& rszWS_ssl_cafile, const string& rszWS_ssl_password, const bool rbWS_use_ssl,
						  const string& rszWS_classid, const string& rszWSname );
		WebServiceConfig( const WebServiceConfig& x );
		
		virtual ~WebServiceConfig();

		string GetWSHost() { return m_szWSHost; }
		void   SetWSHost( const string& rszWSHost ) { m_szWSHost = rszWSHost; }

		string GetWSPortID() { return m_szWSPortID; }
		void   SetWSPortID( const string& rszWSPortID ) { m_szWSPortID = rszWSPortID; }

		long   GetWSBacklog() { return m_lWSBacklog; }
		void   SetWSBacklog( const long lWSBacklog ) { m_lWSBacklog = lWSBacklog; }

		bool   GetWSAuthenticate() { return m_bWSAuthenticate; }
		void   SetWSAuthenticate( const bool rbWSAuthenticate ) { m_bWSAuthenticate = rbWSAuthenticate; }

		string GetWSUsersFile() { return m_szWSUsersFile; }
		void   SetWSUsersFile( const string& rszWSUsersFile ) { m_szWSUsersFile = rszWSUsersFile; } 

		string GetWS_ssl_keyfile() { return m_szWS_ssl_keyfile; }
		void   SetWS_ssl_keyfile( const string& rszWS_ssl_keyfile ) { m_szWS_ssl_keyfile = rszWS_ssl_keyfile; }

		string GetWS_ssl_cafile() { return m_szWS_ssl_cafile; }
		void   SetWS_ssl_cafile( const string& rszWS_ssl_cafile ) { m_szWS_ssl_cafile = rszWS_ssl_cafile; } 

		string GetWS_ssl_password() { return m_szWS_ssl_password; }
		void   SetWS_ssl_password( const string& rszWS_ssl_password ) { m_szWS_ssl_password = rszWS_ssl_password; } 

		bool   GetWS_use_ssl() { return m_bWS_use_ssl; }
		void   SetWS_use_ssl( const bool rbWS_use_ssl ) { m_bWS_use_ssl = rbWS_use_ssl; }

		string GetWS_classid() { return m_szWS_classid; }
		void   SetWS_classid( const string& rszWS_classid ) { m_szWS_classid = rszWS_classid; }

		string GetWSname() { return m_szWSname; }
		void   SetWSname( const string& rzWSname ) { m_szWSname = rzWSname; }

	private:
		string        m_szWSHost;
		string        m_szWSPortID;
		long          m_lWSBacklog;
		bool          m_bWSAuthenticate;
		string        m_szWSUsersFile;
		//need define extras
		string        m_szWS_ssl_keyfile;
		string        m_szWS_ssl_cafile;
		string        m_szWS_ssl_password;
		bool          m_bWS_use_ssl;
		string        m_szWS_classid;
		string        m_szWSname;
};

#endif

