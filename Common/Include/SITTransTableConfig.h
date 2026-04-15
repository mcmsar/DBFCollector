/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_TRANS_TABLE_CONFIG_H__
#define __SIT_TRANS_TABLE_CONFIG_H__

#include "cacheconfig.h"
#include "igateway.h"
#include <map>

typedef enum tagSITTimeFormat
{
	SIT_TIME_FMT_UNKNOWN = 0,
	SIT_TIME_FMT_SID = 1,
	SIT_TIME_FMT_EXTENDED = 2
} SITTIMEFMT;

interface IEMSConfigurationManager;

//! @class CEMSSTTConfig
//! Stores SIT Translation Table configuration information.
class CEMSSTTConfig : public CEMSCacheConfig
{
	public:
		CEMSSTTConfig();
		CEMSSTTConfig( const CEMSSTTConfig& x );
		~CEMSSTTConfig();

		void SetTranslation( const long clSitCode, const long clTranslation );
		long GetTranslation( const long clSitCode );

		inline void SetTimeFormat( const SITTIMEFMT ceTimeFmt ) { m_eTimeFmt = ceTimeFmt; }
		inline SITTIMEFMT GetTimeFormat() const { return m_eTimeFmt; }

		void Populate( const wchar_t* cwszTableName, IEMSConfigurationManager* pConfig );
		
	private:	// methods

	private:	// data
		std::map<long,long>	m_mapTranslationTable;
		SITTIMEFMT m_eTimeFmt;

};

#endif // __SIT_TRANS_TABLE_CONFIG_H__

	