#include "msgnotificationmgr.h"

unsigned long CEMSMsgNotificationMgr::ms_ulCurrentCookie = 1;

CEMSMsgNotificationMgr::CEMSMsgNotificationMgr()
{
}

CEMSMsgNotificationMgr::~CEMSMsgNotificationMgr()
{
	_ReleaseCallbacks();
}

unsigned long
CEMSMsgNotificationMgr::Register( IUnknown* pCallback )
{
	unsigned long ulCookie = 0;

	if( pCallback )
	{
		ulCookie = _Cookie();

		if( ulCookie )
		{
			m_csMap.Enter();

			pCallback->AddRef();

			try
			{
				m_mapCallBacks.insert( MAPCALLBACKS::value_type( ulCookie, pCallback ) );
			}
			catch( ... )
			{
				ulCookie = 0;
			}

			m_csMap.Leave();
		}
	}

	return ulCookie;
}

void
CEMSMsgNotificationMgr::Unregister( const unsigned long culCookie )
{
	if( culCookie )
	{
		// Find it in the map.
		MAPCALLBACKS::iterator itFind = m_mapCallBacks.find( culCookie );

		if( m_mapCallBacks.end() != itFind )
		{
			// Lock the map
			m_csMap.Enter();

			// Make sure that it's still there.
			itFind = m_mapCallBacks.find( culCookie );
			if( m_mapCallBacks.end() != itFind )
			{
				// Call release on the pointer.
				// There is a risk that the pointer is to an out-of-proc object that no longer 
				// exists.  So, protect agains access violation.
				//__try
				//{
				//	IUnknown* pUnk = itFind->second;

				//	if( pUnk )
				//	{
				//		pUnk->Release();
				//		pUnk = 0;
				//	}
				//}
				//__except( GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : 
				//															 EXCEPTION_CONTINUE_SEARCH  )
				//{
				//	// Do nothing.  The pointer is no good.
				//}

				try
				{
					IUnknown* pUnk = itFind->second;

					if( pUnk )
					{
						pUnk->Release();
						pUnk = 0;
					}
				}
				catch( ... )
				{
					// Do nothing.  The pointer is no good.
				}

				m_mapCallBacks.erase( itFind );
			}

			m_csMap.Leave();
		}
	}
}

unsigned long
CEMSMsgNotificationMgr::GetCount()
{
	return m_mapCallBacks.size();
}

IUnknown*
CEMSMsgNotificationMgr::GetAt( const unsigned long culIndex )
{
	IUnknown* pRet = 0;

	if( culIndex >= 0 && culIndex < GetCount() )
	{
		MAPCALLBACKS::iterator itAt = m_mapCallBacks.begin();
		for( long l = 0; l < culIndex; l++ )
		{
			itAt++;
		}

		if( m_mapCallBacks.end() != itAt )
		{
			// Call AddRef on the pointer.
			// There is a risk that the pointer is to an out-of-proc object that no longer 
			// exists.  So, protect agains access violation.
			//__try
			//{
			//	pRet = itAt->second;

			//	if( pRet )
			//	{
			//		pRet->AddRef();
			//	}
			//}
			//__except( GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : 
			//															 EXCEPTION_CONTINUE_SEARCH  )
			//{
			//	// The pointer is no good.  So, remove it from the map.
			//	Unregister( itAt->first );
			//	pRet = 0;
			//}
			try
			{
				pRet = itAt->second;

				if( pRet )
				{
					pRet->AddRef();
				}
			}
			catch( ... )
			{
				// The pointer is no good.  So, remove it from the map.
				Unregister( itAt->first );
				pRet = 0;
			}
		}
	}

	return pRet;
}

void
CEMSMsgNotificationMgr::RemoveAt( const unsigned long culIndex )
{
	m_csMap.Enter();

	if( culIndex >= 0 && culIndex < GetCount() )
	{
		MAPCALLBACKS::iterator itAt = m_mapCallBacks.begin();
		for( long l = 0; l < culIndex; l++ )
		{
			itAt++;
		}

		if( m_mapCallBacks.end() != itAt )
		{
			try
			{
				itAt->second->Release();
				itAt->second = 0;
			}
			catch( ... )
			{
				// do nothing.
			}
			//__try
			//{
			//	itAt->second->Release();
			//	itAt->second = 0;
			//}
			//__except( GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : 
			//															 EXCEPTION_CONTINUE_SEARCH )
			//{
			//	// do nothing.
			//}

			m_mapCallBacks.erase( itAt );
		}
	}

	m_csMap.Leave();
}

void
CEMSMsgNotificationMgr::_ReleaseCallbacks()
{
	m_csMap.Enter();

	MAPCALLBACKS::iterator itCurrent = m_mapCallBacks.begin();

	while( m_mapCallBacks.end() != itCurrent )
	{
		//__try
		//{
		//	IUnknown* pUnk = itCurrent->second;

		//	if( pUnk )
		//	{
		//		pUnk->Release();
		//		pUnk = 0;
		//	}
		//}
		//__except( GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : 
		//																 EXCEPTION_CONTINUE_SEARCH  )
		//{
		//	// Do nothing.
		//}
		
		try
		{
			IUnknown* pUnk = itCurrent->second;

			if( pUnk )
			{
				pUnk->Release();
				pUnk = 0;
			}
		}
		catch( ... )
		{
			// Do nothing.
		}

		MAPCALLBACKS::iterator itNext = itCurrent;
		itNext++;

		m_mapCallBacks.erase( itCurrent );
		
		itCurrent = itNext;
	}
	

	m_csMap.Leave();
}

unsigned long
CEMSMsgNotificationMgr::_Cookie()
{
	unsigned long ulRet = 0;

	m_csCookie.Enter();

	ulRet = ms_ulCurrentCookie++;

	m_csCookie.Leave();

	return ulRet;
}