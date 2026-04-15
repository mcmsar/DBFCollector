/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __RAWRECORD_CACHE_H__
#define __RAWRECORD_CACHE_H__

#include "criticalsection.h"
#include <map>
#include "aobjbase.h"

class CEMSRawDataRecord;
class CEMSRawRecordCache;
class CEMSCachedRawRecord;

class CEMSRawRecordCache : public CApiObjBase
{
	public:

		static CEMSRawRecordCache* GetResultsetCache();

		typedef long EMSDALCACHEID;

		CEMSRawDataRecord*	Checkout( const EMSDALCACHEID cCacheID );
		EMSDALCACHEID	CheckIn( CEMSRawDataRecord* pRs );
		void			Delete( const EMSDALCACHEID cCacheID );
		void			CleanCache();
		unsigned long	GetCacheSize();
		void			SetMaxCacheSize( const unsigned long culMax ) { m_ulMaxCacheSize = culMax; }
		void			SetLifespan( const double cdSeconds ) { m_dCacheLifespan = cdSeconds; }

	protected:
		CEMSRawRecordCache();
		CEMSRawRecordCache( const CEMSRawRecordCache& x );
		~CEMSRawRecordCache();

	private:	// methods
		void			_ClearCache();
		EMSDALCACHEID	_GetNextCacheID();
		unsigned long	_GetMaxCacheSize();
		EMSTIME			_GetCurrentTime();
		double			_GetCacheLifeSpan();

	private:	// data
		static CEMSRawRecordCache*	ms_pRsCache;
		static CEMSCriticalSection	ms_csCacheLifetime;

		static EMSDALCACHEID		ms_nextCacheID;
		CEMSCriticalSection			m_csCacheID;

		std::map<EMSDALCACHEID,CEMSCachedRawRecord*>	m_mapRs;
		CEMSCriticalSection								m_csMap;

		unsigned long	m_ulMaxCacheSize;
		double			m_dCacheLifespan;
};

#endif // __RESULTSET_CACHE_H__