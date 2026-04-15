/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __AWCONFG_CLIENT_H__
#define __AWCONFG_CLIENT_H__

#include "meoconfigclient.h"
#include "KeyValueConfig.h"
#include <map>
using std::map;

class __declspec(dllexport)  EMSAlarmsWarningsClient : public MEOConfigClient
{
	public:
		EMSAlarmsWarningsClient();
		EMSAlarmsWarningsClient( const string& hostName, const int ciPortNum );
		EMSAlarmsWarningsClient( const EMSAlarmsWarningsClient& x );
		virtual ~EMSAlarmsWarningsClient();

		double getAlarmValueById( const string& id );
		map<string,KeyValueItem> getAllAlarms();

		double getWarningValueById( const string& id );
		map<string,KeyValueItem> getAllWarnings();

	private:

};

#endif

