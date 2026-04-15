/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __MEO_CONFIG_CLIENT_H__
#define __MEO_CONFIG_CLIENT_H__

#include <string>
#include <map>
#include "ccbootstrap.h"

class __declspec(dllexport) MEOConfigClient
{
	public:
		MEOConfigClient();
		MEOConfigClient( const std::string& hostName, const int ciPortNum );
		MEOConfigClient( const MEOConfigClient& x );
		virtual ~MEOConfigClient();

		void SetHost( const std::string& hostName ) { m_HostName = hostName; }
		std::string GetHost() const { return m_HostName; }

		void SetPort( const int ciPortNum ) { m_iPortNum = ciPortNum; }
		int GetPort() const { return m_iPortNum; }

		std::string DoGetRequest( const std::string& url, std::map<std::string,std::string> paramList );

	private:
		std::string m_HostName;
		int m_iPortNum;
};

#endif