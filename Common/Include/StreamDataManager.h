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

#ifndef __STREAM_DATA_MANAGER_H__
#define __STREAM_DATA_MANAGER_H__

//#include "logclient.h"

#include "criticalsection.h"
#include "pointermap.h"
#include <string>

class CEMSStreamDataChannel;
class CEMSStreamDataMgrCleaner;

//! Manages access to stream data channels.
class CEMSStreamDataManager //: public CEMSLogClient
{
	public:
		~CEMSStreamDataManager();

		//! Get a pointer to the process-wide instance of the stream data manager.
		static CEMSStreamDataManager* GetInstance();

		//! Retrieve a pointer to the data channel associated with the given URL.
		//! If no channel for this URL currently exists, one will be created.
		//! The caller must Release the data channel when finished with it.
		CEMSStreamDataChannel* GetDataChannel( const wchar_t* cwszURL );

		//! Removes unused data channels from the cache.
		void Cleanup();

	protected:
		CEMSStreamDataManager();

	private:
		CEMSStreamDataChannel* _CreateNewChannel( const wchar_t* cwszURL );

	private:
		
		//! The process-wide instance of the stream data manager.
		static CEMSStreamDataManager m_oMgr;

		//! Critical section used to manage concurrent access to the data manager.
		CEMSCriticalSection m_csMgr;

		//! A map holding pointers to stream data channel objects and keyed by URL.
		CEMSPointerMap<std::wstring,CEMSStreamDataChannel> m_omapDataChannels;

		//! Runs a separate thread that periodically cleans the stream data manager
		//! cache.
		CEMSStreamDataMgrCleaner* m_pCleaner;

};

#endif