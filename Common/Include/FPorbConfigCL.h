/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __FP_ORB_CONFIG_CL_H__
#define __FP_ORB_CONFIG_CL_H__

#include "UserConfigCL.h"
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) FPorbConfig
{
	public:
		FPorbConfig();
		FPorbConfig( const string& rszFPorbURL, const UserConfig rszFPorbUser );
		FPorbConfig( const FPorbConfig& x );
		
		virtual ~FPorbConfig();

		string GetFPorbURL() { return m_szFPorbURL; }
		void   SetFPorbURL( const string& rszFPorbURL ) { m_szFPorbURL = rszFPorbURL; }

		UserConfig GetFPorbUser() { return m_szFPorbUser; }
		void       SetFPorbUser( const UserConfig rszFPorbUser ) { m_szFPorbUser = rszFPorbUser; }

	private:
		string        m_szFPorbURL;
		UserConfig    m_szFPorbUser;
};

#endif

