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
#include "MEOlutConfig.h"
#include "LutConfigCL.h"
#include "FPConfigCL.h"
#include "SPConfigCL.h"
#include "LPConfigCL.h"
#include "DataManagerConfig.h"
#include "WinServiceConfig.h"
#include "pointerlist.h"
#include "meotypes.h"
#include "ClocksConfig.h"

class __declspec(dllexport)  MEOSystemClient : public MEOConfigClient
{
	public:
		MEOSystemClient();
		MEOSystemClient( const string& hostName, const int ciPortNum );
		MEOSystemClient( const MEOSystemClient& x );
		virtual ~MEOSystemClient();

		MEOLUTConfig*    getMEOLUTConfig();
		FPConfig*        getFPById( const string& id );
		SPConfig*        getSPById( const string& id );
		SPParamsConfig*  getSPParamsById( const string& id );
		LPConfig*        getLPById( const string& id );
		LPParamsConfig*  getLPParamsById( const string& id );
		LPParamsConfig*  getLPParamsByLPId( const string& id );

		EMSClocksConfig* getClocksConfig();
		list<EMSClocksConfig*> getAllClocksConfig();

		string getDataManagerIDBySubsystemID( const string& id );
		string getServicesIDBySubsystemID( const string& id );

		DataManagerConfig*     getDataManagerById( const string& id );
		WinServicesConfig*     getWinServicesById( const string& id );

		LUTConfig* getLUTById( const string& id );
		list<LUTConfig*> getAllLUTs();

		MEO_SUBSYSTEM_TYPE getSubSystemType( const string& id );

		void getCollectorOutputXMLByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );
		void getDCPluginsXMLByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );
		void getDCWebServicesByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );
		void getFPWebServicesByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );
		void getFPPairsByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );
		void getFPDataStreamsByFpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );

		void getLPUrlRecvWWByLpId( const string& rszFpId, char* szXml, const unsigned long ulMaxSize );

		string getTrackingMode( const string& meoLutCfgStr );
		string getRedundancyMode( const string& meoLutCfgStr );
		
		static void ClearLUTConfigList( list<MEOLUTConfig*>& lstLUTConfig );

	private:

};

#endif

