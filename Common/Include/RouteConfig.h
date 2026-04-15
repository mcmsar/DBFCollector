/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __ROUTE_CONFIG_H__
#define __ROUTE_CONFIG_H__

#include "aobjbase.h"
#include <wchar.h>
#include <string>

#include "routeendconfig.h"

class CEMSRouteEndConfig;
struct IEMSConfigurationManager;

//! @class CEMSRouteConfig
//! Stores configuration information for a route.
class CEMSRouteConfig : public CApiObjBase
{
	public:
		CEMSRouteConfig();
		CEMSRouteConfig( const CEMSRouteConfig& x );
		~CEMSRouteConfig();

		void SetEnd1( CEMSRouteEndConfig* pEnd1 );
		CEMSRouteEndConfig* GetEnd1();

		void SetEnd2( CEMSRouteEndConfig* pEnd2 );
		CEMSRouteEndConfig* GetEnd2();

		void PopulateRoute( const wchar_t* cwszRoute, IEMSConfigurationManager* pConfig ); 
		void PopulateRoute( const int ciNumConfigItems, const EMSCONFIGURATIONITEM** capConfigItems );

		CEMSRouteEndConfig* GetEnd( const unsigned long culID );
		CEMSRouteEndConfig* GetEnd( const wchar_t* cwszAlias );

		void SetRouteName( const wchar_t* cwszName ) { m_wszRouteName = cwszName; }
		std::wstring GetRouteName() { return m_wszRouteName; }

		void SetEnabled( const bool cbEnabled ) { m_bEnabled = cbEnabled; }
		bool GetEnabled() { return m_bEnabled; }

	private:	// methods
		EMSMSGTYPE _GetMsgType( const wchar_t* wszType );
		long _ConvertToSITCode( const wchar_t* cwszSITCode );

	private:	// data
		CEMSRouteEndConfig* m_pEnd1;
		CEMSRouteEndConfig* m_pEnd2;

		// This is the name of the route in the configuration file.
		std::wstring		m_wszRouteName;

		bool				m_bEnabled;
		
};

#endif // __ROUTE_CONFIG_H__

	