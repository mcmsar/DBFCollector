/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __CACHE_CONFIG_H__
#define __CACHE_CONFIG_H__

#include "aobjbase.h"
#include <wchar.h>

//! @class CEMSCacheConfig
//! Base class for cached configuration data.
class CEMSCacheConfig : public CApiObjBase
{
	public:
		CEMSCacheConfig();
		CEMSCacheConfig( const CEMSCacheConfig& x );
		~CEMSCacheConfig();

	protected:
		void _SetString( wchar_t*& wszLHS, const wchar_t* cwszRHS ) const;

};

#endif // __CACHE_CONFIG_H__