/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_RES_TRANS_TABLE_CONFIG_H__
#define __SIT_RES_TRANS_TABLE_CONFIG_H__

#include "cacheconfig.h"
#include "igateway.h"
#include <map>


interface IEMSConfigurationManager;

//! @class CEMSRTTConfig
//! Stores SIT to Resource Translation Table configuration information.
class CEMSRTTConfig : public CEMSCacheConfig
{
	public:
		CEMSRTTConfig();
		CEMSRTTConfig( const CEMSRTTConfig& x );
		~CEMSRTTConfig();

		void SetResource( const long clSit, const EMSRESOURCEIDENTIFIER );
		EMSRESOURCEIDENTIFIER GetResource( const long clSit );
		
		void Populate( const wchar_t* cwszTableName, IEMSConfigurationManager* pConfig );
		
	private:	// methods
		EMSRESOURCEIDENTIFIER _GetResourceCode( const wchar_t* cwszResource );

	private:	// data
		std::map<long,EMSRESOURCEIDENTIFIER>	m_mapResources;
};

#endif // __SIT_TRANS_TABLE_CONFIG_H__

	