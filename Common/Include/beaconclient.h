/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __BEACON_CLIENT_H__
#define __BEACON_CLIENT_H__

#include "meoconfigclient.h"
#include "BeaconConfig.h"
#include "pointerlist.h"

class __declspec(dllexport)  BeaconClient : public MEOConfigClient
{
	public:
		BeaconClient();
		BeaconClient( const string& hostName, const int ciPortNum );
		BeaconClient( const BeaconClient& x );
		virtual ~BeaconClient();

		BeaconConfig* getById( const string& id );
		list<BeaconConfig*> getAll();

		static void ClearBeaconConfigList( list<BeaconConfig*>& lstBeaconConfig );

	private:

};

#endif

