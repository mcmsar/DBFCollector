/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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
	 2    Common    1.1         09/02/2005 5:17:29 PM  Jason Bass      Added
	      Clear() method.
	 1    Common    1.0         17/12/2004 5:35:17 PM  Jason Bass      
	$
********************************************************************/

#ifndef __POINTER_QUEUE_H__
#define __POINTER_QUEUE_H__

#include "aobjbase.h"
#include <queue>
#include "criticalsection.h"
#include "emsexcpt.h"

//! @class CEMSPointerQueue
//! A thread-safe queue of pointer.
template<class T>
class CEMSPointerQueue : public CApiObjBase
{
	public:
		CEMSPointerQueue();
		CEMSPointerQueue( const CEMSPointerQueue& x );
		virtual ~CEMSPointerQueue();

		//! @fn void Push( T* obj )
		//! Push a pointer onto the queue.
		void Push( T* obj );

		//! @fn T* Pop()
		//! Retrieve the next pointer in the queue and remove it from the queue.
		T* Pop();

		//! @fn void Clear()
		//! Delete any items in the queue.
		void Clear() { _Clear(); }

		//! Set a maximum size the queue can grow to.  Once reached an exception is thrown each time
		//! an Push operation is executed.
		void SetMaxSize( const ULONG culMax );

		ULONG GetMaxSize();

		//! Get the number of elements in the queue.
		ULONG Count();

	private:
		void _Clear();

	private:
		std::queue<T*>		m_queuePointers;
		CEMSCriticalSection	m_csQueue;
		ULONG				m_ulMaxItems;
};

template<class T>
CEMSPointerQueue<T>::CEMSPointerQueue() : m_ulMaxItems( 0 )
{
}

template<class T>
CEMSPointerQueue<T>::CEMSPointerQueue( const CEMSPointerQueue& x ) : m_ulMaxItems( x.m_ulMaxItems )
{
}

template<class T>
CEMSPointerQueue<T>::~CEMSPointerQueue()
{
	_Clear();
}

template<class T>
void
CEMSPointerQueue<T>::Push( T* pObj )
{
	try
	{
		m_csQueue.Enter();

		if( m_ulMaxItems > 0 )
		{
			if( m_queuePointers.size() + 1 > m_ulMaxItems )
			{
				throw CEMSException( EMS_OVERFLOW );
			}
		}
		
		m_queuePointers.push( pObj );

		pObj->AddRef();

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}
}

template<class T>
T*
CEMSPointerQueue<T>::Pop()
{
	T* ret = 0;

	try
	{
		m_csQueue.Enter();

		if( m_queuePointers.size() > 0 )
		{
			ret = m_queuePointers.front();
			m_queuePointers.pop();

			// No AddRef or Release().  They cancel out:  one AddRef() for returned pointer
			// and one Release() for removal from the queue.
		}

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}

	return ret;
}

template<class T>
void
CEMSPointerQueue<T>::SetMaxSize( const ULONG culItems )
{
	try
	{
		m_csQueue.Enter();

		m_ulMaxItems = culItems;

		if( m_ulMaxItems < m_queuePointers.size() )
		{
			throw CEMSException( EMS_OVERFLOW );
		}

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}
}

template<class T>
ULONG
CEMSPointerQueue<T>::GetMaxSize()
{
	ULONG ulRet = 0;

	try
	{
		m_csQueue.Enter();

		ulRet = m_ulMaxItems;

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}

	return ulRet;
}

template<class T>
ULONG
CEMSPointerQueue<T>::Count()
{
	ULONG ulRet = 0;

	try
	{
		m_csQueue.Enter();

		ulRet = m_queuePointers.size();

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}

	return ulRet;
}


template<class T>
void
CEMSPointerQueue<T>::_Clear()
{
	try
	{
		m_csQueue.Enter();

		if( m_queuePointers.size() > 0 )
		{
			T* pCurrent = m_queuePointers.front();

			while( pCurrent )
			{
				// Remove it.			
				m_queuePointers.pop();

				// Release it.
				pCurrent->Release();

				pCurrent = 0;
				
				if( m_queuePointers.size() > 0 )
					pCurrent = m_queuePointers.front();
			}
		}

		m_csQueue.Leave();
	}
	catch( ... )
	{
		m_csQueue.Leave();

		throw;
	}
}

#endif