/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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
#pragma warning(disable:4786)

#include "streamdatamanager.h"
#include "emsurl.h"
#include "supportedurlschemes.h"
#include "dburl.h"
#include "streamdatamanagercleaner.h"
#include "streamdatachannel.h"
#include "dbstreamdatachannel.h"
#include "filestreamdatachannel.h"
#include "emsexcpt.h"
#include "streamsink.h"
#include "streamsource.h"
#include "resourcemsgs.h"

CEMSStreamDataManager CEMSStreamDataManager::m_oMgr;

CEMSStreamDataManager::CEMSStreamDataManager() : m_pCleaner(0)
{
	m_pCleaner = new CEMSStreamDataMgrCleaner;

	if( m_pCleaner )
	{
		m_pCleaner->start();
	}
}

CEMSStreamDataManager::~CEMSStreamDataManager()
{
	if( m_pCleaner )
	{
		m_pCleaner->Stop();

		m_pCleaner->Release();
		m_pCleaner = 0;
	}
}

CEMSStreamDataManager* 
CEMSStreamDataManager::GetInstance()
{
	return &m_oMgr;
}

CEMSStreamDataChannel* 
CEMSStreamDataManager::GetDataChannel( const wchar_t* cwszURL )
{
	CEMSStreamDataChannel* pRet = 0;

	try
	{
		m_csMgr.Enter();

		// Is it in the map already.
		pRet = m_omapDataChannels.Get( std::wstring( cwszURL ));

		if( !pRet )
		{
			pRet = _CreateNewChannel( cwszURL );

			if( pRet )
			{
				// Add it to the cache.
				m_omapDataChannels.Add( std::wstring( cwszURL ), pRet );
			}
		}

		m_csMgr.Leave();
	}
	catch( ... )
	{
		m_csMgr.Leave();

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSStreamDataManager::Cleanup()
{
	CEMSStreamDataChannel* pChannel = 0;

	try
	{
		m_csMgr.Enter();

		// Go through the list of managed channels and release any channels that are not
		// in use.
		m_omapDataChannels.MoveFirst();

		pChannel= m_omapDataChannels.GetNext();

		while( pChannel )
		{
			pChannel->Cleanup();

			ULONG ulRefCount = pChannel->GetRefCount();

			// A Ref count of 2 means:  one reference owned by the map and one owned by the 
			// pChannel temp variable.  Therefore, there are no other users of the channel and
			// it can be removed from the map.
			if( 2 == ulRefCount && !pChannel->IsRunning() )
			{
				std::wstring wszURL = pChannel->GetURL();
				m_omapDataChannels.Remove( wszURL );

//				CEMSLogMsgParam oParam;
//				oParam.AddString( wszURL.c_str() );
//				EMSLOGEX( this, EMSLogMsgDebug, EMS_RESOURCE_CHANNEL_RELEASED, oParam );
			}

			pChannel->Release();
			pChannel = 0;

			pChannel = m_omapDataChannels.GetNext();

		}


		m_csMgr.Leave();
	}
	catch( ... )
	{
		m_csMgr.Leave();

		throw;
	}

}

CEMSStreamDataChannel* 
CEMSStreamDataManager::_CreateNewChannel( const wchar_t* cwszURL )
{
	CEMSStreamDataChannel* pRet = 0;

	CEMSDBStreamDataChannel* pDBChannel = 0;
	CEMSFileStreamDataChannel* pFileChannel = 0;

	try
	{
		CEMSURL oURL( cwszURL );
	
		// Currently, support the "db" URL scheme.
		if( 0 == wcsicmp( oURL.GetScheme().c_str(), CEMSSupportedURLSchemes::DB ) ) 
		{
			pDBChannel = new CEMSDBStreamDataChannel;

			if( !pDBChannel )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			// Setup the channel.

			CEMSDBURL oDBUrl( cwszURL );

			pDBChannel->SetURL( cwszURL );
			pDBChannel->SetSrcID( oDBUrl.GetSourceID() );
			pDBChannel->SetDestID( oDBUrl.GetDestID() );
			pDBChannel->SetSQL( oDBUrl.GetSQL().c_str() );
			pDBChannel->SetSrcTable( oDBUrl.GetActiveTable().c_str() );
			pDBChannel->SetSrcColumn( oDBUrl.GetActiveColumn().c_str() );
			pDBChannel->SetCriteria( oDBUrl.GetActiveCriteria().c_str() );
			pDBChannel->SetTestPeriod( oDBUrl.GetActiveTestPeriod() );
			pDBChannel->SetDBConn( oDBUrl.GetConnection().c_str() );
			pDBChannel->SetChunkSize( oDBUrl.GetChunkSize() );

			pRet = pDBChannel;
		}
		else if( 0 == wcsicmp( oURL.GetScheme().c_str(), CEMSSupportedURLSchemes::FILE ) ) 
		{
			pFileChannel = new CEMSFileStreamDataChannel;

			if( !pFileChannel )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			// Setup the channel.
			CEMSDBURL oDBUrl( cwszURL );

			pFileChannel->SetURL( cwszURL );

			pRet = pFileChannel;

		}

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}