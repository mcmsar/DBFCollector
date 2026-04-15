/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of Honeywell International, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __ANT_CLIENT_H__
#define __ANT_CLIENT_H__

#include "meoconfigclient.h"
#include "AntennaConfig.h"
#include "pointerlist.h"

class __declspec(dllexport)  EMSAntennaClient : public MEOConfigClient
{
	public:
		EMSAntennaClient();
		EMSAntennaClient( const string& hostName, const int ciPortNum );
		EMSAntennaClient( const EMSAntennaClient& x );
		virtual ~EMSAntennaClient();

		EMSAntennaConfig* getById( const string& id );
		list<EMSAntennaConfig*> getAll();

		void getAntContXMLConfigByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );

		static void ClearAntennaConfigList( list<EMSAntennaConfig*>& lstAntennaConfig );

	private:

};

#endif

