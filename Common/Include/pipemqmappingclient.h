/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __PIPEMQ_MAPPING_CLIENT_H__
#define __PIPEMQ_MAPPING_CLIENT_H__

#include "meoconfigclient.h"
#include "PipeMQAdaptorConfig.h"
#include "pointerlist.h"

using namespace std;

class __declspec(dllexport)  PipeMQMappingClient : public MEOConfigClient
{
	public:
		PipeMQMappingClient();
		PipeMQMappingClient( const string& hostName, const int ciPortNum );
		PipeMQMappingClient( const PipeMQMappingClient& x );
		virtual ~PipeMQMappingClient();

		//std::auto_ptr<meoconfig::bridge_mappings>  getBySubsystemId( const string& id );
		//auto_ptr<meoconfig::bridge_mappings> getAll();

		list<BridgeConfig*> getAllBridgeMappings();
		BridgeConfig* getByBridgeMappingId( const string& id );

		static void ClearBridgeConfigList( list<BridgeConfig*>& lstBridgeConfig );
		static void ClearPipeMQAdaptorConfigList( list<PipeMQAdaptorConfig*>& lstPipeMQAdaptorCConfig );

	private:

};

#endif

