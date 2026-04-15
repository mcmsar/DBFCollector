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

#ifdef WIN32
#pragma warning(disable:4786)	// disable compiler warnings for STL debug symbol size
#endif

#include "rawrecordcache.h"
#include "emsclock.h"
#include "emstime.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "cachedrawrecord.h"
#include "rawdatarecord.h"

const CEMSRawRecordCache::EMSDALCACHEID cMaxCacheID = 1000000;
const CEMSRawRecordCache::EMSDALCACHEID cMinCacheID = 1;

CEMSRawRecordCache* CEMSRawRecordCache::ms_pRsCache = 0;
CEMSCriticalSection	CEMSRawRecordCache::ms_csCacheLifetime;
CEMSRawRecordCache::EMSDALCACHEID CEMSRawRecordCache::ms_nextCacheID = cMinCacheID;

CEMSRawRecordCache::CEMSRawRecordCache() : m_ulMaxCacheSize( 128 ), m_dCacheLifespan( 120.0 )
{
}

CEMSRawRecordCache::CEMSRawRecordCache( const CEMSRawRecordCache& x ) : m_ulMaxCacheSize(x.m_ulMaxCacheSize),
																		m_dCacheLifespan(x.m_dCacheLifespan)
{
}

CEMSRawRecordCache::~CEMSRawRecordCache()
{
	_ClearCache();
}

CEMSRawRecordCache*
CEMSRawRecordCache::GetResultsetCache()
{
	CEMSRawRecordCache* pRet = 0;

	try
	{
		ms_csCacheLifetime.Enter();

		if( !ms_pRsCache )
		{
			ms_pRsCache = new CEMSRawRecordCache;

			if( !ms_pRsCache )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}

		pRet = ms_pRsCache;
		pRet->AddRef();

		ms_csCacheLifetime.Leave();

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		ms_csCacheLifetime.Leave();

		throw;
	}

	return pRet;
}

CEMSRawDataRecord*	
CEMSRawRecordCache::Checkout( const EMSDALCACHEID cCacheID )
{
	CEMSRawDataRecord* pRet = 0;

	try
	{
		m_csMap.Enter();

		std::map<EMSDALCACHEID,CEMSCachedRawRecord*>::iterator itFind = m_mapRs.find( cCacheID );
		
		if( itFind != m_mapRs.end() )
		{
			CEMSCachedRawRecord* pCacheRs = itFind->second;

			if( !pCacheRs )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet = pCacheRs->GetRecordset();

			pCacheRs->Release();
			pCacheRs = 0;
			
			// Remove it from the cache now.
			m_mapRs.erase( itFind );
		}

		m_csMap.Leave();
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		m_csMap.Leave();

		throw;
	}

	return pRet;
}

CEMSRawRecordCache::EMSDALCACHEID	
CEMSRawRecordCache::CheckIn( CEMSRawDataRecord* pRs )
{
	EMSDALCACHEID cacheID = 0;

	CEMSCachedRawRecord* pCacheRs = 0;

	if( !pRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		m_csMap.Enter();

		// First, check whether there's room in the cache.
		if( m_mapRs.size() < _GetMaxCacheSize() )
		{
			pCacheRs = new CEMSCachedRawRecord( pRs, _GetCurrentTime() );

			if( !pCacheRs )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			cacheID = _GetNextCacheID();

			// First, remove any cached results using this ID.  In case the number has turned
			// over.
			Delete( cacheID );

			m_mapRs.insert( std::pair<EMSDALCACHEID,CEMSCachedRawRecord*>( cacheID, pCacheRs ) );
		}
		else
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			//LogWarningMsg( EMS_DAL_CACHE_LIMIT_REACHED );
		}

		m_csMap.Leave();
	}
	catch( ... )
	{
		if( pCacheRs )
		{
			pCacheRs->Release();
			pCacheRs = 0;
		}

		m_csMap.Leave();

		throw;
	}

	return cacheID;
}

void
CEMSRawRecordCache::Delete( const EMSDALCACHEID cCacheID )
{
	try
	{
		m_csMap.Enter();

		std::map<EMSDALCACHEID,CEMSCachedRawRecord*>::iterator itFind = m_mapRs.find( cCacheID );
		
		if( itFind != m_mapRs.end() )
		{
			CEMSCachedRawRecord* pCacheRs = itFind->second;

			if( !pCacheRs )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pCacheRs->Release();
			pCacheRs = 0;
			
			// Remove it from the cache now.
			m_mapRs.erase( itFind );
		}

		m_csMap.Leave();
	}
	catch( ... )
	{
		m_csMap.Leave();

		throw;
	}
}

void			
CEMSRawRecordCache::CleanCache()
{
	try
	{
		double dLifeSpan = _GetCacheLifeSpan();

		// Iterate through the cached recordsets and remove those that
		// have aged out.
		m_csMap.Enter();

		std::map<EMSDALCACHEID,CEMSCachedRawRecord*>::iterator it = m_mapRs.begin();

		while( it != m_mapRs.end() )
		{
			CEMSCachedRawRecord* pCacheRs = it->second;

			if( !pCacheRs )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			CEMSTime timeCached( pCacheRs->GetCachedTime() );

			if( timeCached.SecondsDifferent( _GetCurrentTime () ) > dLifeSpan )
			{
				// It's expired.  So, remove from the cache.
				it = m_mapRs.erase( it );

				pCacheRs->Release();
				pCacheRs = 0;
			}
			else
			{
				it++;
			}

		}

		m_csMap.Leave();
	}
	catch( ... )
	{
		m_csMap.Leave();

		throw;
	}
}

unsigned long	
CEMSRawRecordCache::GetCacheSize()
{
	unsigned long ulRet = 0;

	try
	{
		m_csMap.Enter();

		ulRet = m_mapRs.size();

		m_csMap.Leave();
	}
	catch( ... )
	{
		throw;

		m_csMap.Leave();
	}

	return ulRet;
}

void
CEMSRawRecordCache::_ClearCache()
{
	try
	{
		m_csMap.Enter();

		std::map<EMSDALCACHEID,CEMSCachedRawRecord*>::iterator it = m_mapRs.begin();

		while( it != m_mapRs.end() )
		{
			CEMSCachedRawRecord* pCacheRs = it->second;

			if( pCacheRs )
			{
				pCacheRs->Release();
				pCacheRs = 0;
			}

			it++;
		}

		m_mapRs.clear();

		m_csMap.Leave();
	}
	catch( ... )
	{
		m_csMap.Leave();

		throw;
	}
}

CEMSRawRecordCache::EMSDALCACHEID	
CEMSRawRecordCache::_GetNextCacheID()
{
	EMSDALCACHEID cacheID = 0;

	try
	{
		m_csCacheID.Enter();

		ms_nextCacheID++;

		if( ms_nextCacheID >= cMaxCacheID )
		{
			// Reset once the maximum is reached.
			ms_nextCacheID = cMinCacheID;
		}
		
		cacheID = ms_nextCacheID;

		m_csCacheID.Leave();
	}
	catch( ... )
	{
		m_csCacheID.Leave();

		throw;
	}

	return cacheID;
}

unsigned long	
CEMSRawRecordCache::_GetMaxCacheSize()
{
	return m_ulMaxCacheSize;
}

EMSTIME			
CEMSRawRecordCache::_GetCurrentTime()
{
	return CEMSSystemClock::GetTime();
}

double	
CEMSRawRecordCache::_GetCacheLifeSpan()
{
	return m_dCacheLifespan;
}