/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __LUT_CLIENT_H__
#define __LUT_CLIENT_H__

#include "meoconfigclient.h"
#include "meomodel.h"
#include "lutConfigCL.h"
#include "pointerlist.h"

class __declspec(dllexport)  LUTClient : public MEOConfigClient
{
	public:
		LUTClient();
		LUTClient( const string& hostName, const int ciPortNum );
		LUTClient( const LUTClient& x );
		virtual ~LUTClient();

		LUTConfig* getById( const string& id );
		list<LUTConfig*> getAll();

		static void ClearLUTConfigList( list<LUTConfig*>& lstLUTConfig );

	private:
		static const char* ms_cszBeaUrl;
		static const char* ms_cszBeasUrl;

	private:

};

#endif

