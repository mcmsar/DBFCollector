/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __SAT_CLIENT_H__
#define __SAT_CLIENT_H__

#include "meoconfigclient.h"
#include "SatConfig.h"
#include "pointerlist.h"

class __declspec(dllexport)  SatClient : public MEOConfigClient
{
	public:
		SatClient();
		SatClient( const string& hostName, const int ciPortNum );
		SatClient( const SatClient& x );
		virtual ~SatClient();

		//auto_ptr<meoconfig::sat> getById( const string& id );
		//auto_ptr<meoconfig::sats> getAll();

		SatConfig* getById( const string& id );
		list<SatConfig*> getAll();

		static void ClearSatConfigList( list<SatConfig*>& lstSatConfig );

	private:

};

#endif

