/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __USER_CONFIG_CL_H__
#define __USER_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) UserConfig
{
	public:
		UserConfig();
		UserConfig( const string& rszName, const string& rszPassword );
		UserConfig( const UserConfig& x );
		
		virtual ~UserConfig();

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		string GetPassword() { return m_szPassword; }
		void   SetPassword( const string& rszPassword ) { m_szPassword = rszPassword; }

	private:
		string        m_szName;
		string        m_szPassword;
};

#endif

