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
	 1    Common    1.0         27/10/2004 1:37:18 PM  Jason Bass      
	$
********************************************************************/

#ifndef __OBJECT_QUEUE_H__
#define __OBJECT_QUEUE_H__

#include "aobjbase.h"
#include <queue>
#include "criticalsection.h"
#include "emsexcpt.h"

//! @class CEMSObjectQueue
//! A thread-safe queue of objects.
template<class T>
class CEMSObjectQueue : public CApiObjBase
{
	public:
		CEMSObjectQueue();
		CEMSObjectQueue( const CEMSObjectQueue& x );
		virtual ~CEMSObjectQueue();

		//! @fn void Push( T& obj )
		//! Push an object onto the queue.
		void Push( T& obj );

		//! @fn void Push( const T& cobj )
		//! Push an object onto the queue.
		void Push( const T& cobj );

		//! @fn T Pop()
		//! Retrieve the next object in the queue and remove it from the queue.
		T Pop();

		//! @fn void SetMaxSize( const ULONG culItems )
		//! Set the maximum allowable size of the queue.
		void SetMaxSize( const ULONG culItems );

		ULONG GetMaxSize();

		//! @fn ULONG Count()
		//! Return the number of elements in the queue.
		ULONG Count();

		//! Clear contents of the class.
		void Clear();

	private:
		std::queue<T>		m_queueObjects;
		CEMSCriticalSection	m_csObjQueue;
		ULONG				m_ulMaxItems;
};

template<class T>
CEMSObjectQueue<T>::CEMSObjectQueue() : m_ulMaxItems(0)
{
}

template<class T>
CEMSObjectQueue<T>::CEMSObjectQueue( const CEMSObjectQueue& x ) : m_ulMaxItems( x.m_ulMaxItems )
{
}

template<class T>
CEMSObjectQueue<T>::~CEMSObjectQueue()
{
}

template<class T>
void
CEMSObjectQueue<T>::Push( T& obj )
{
	try
	{
		m_csObjQueue.Enter();

		if( m_ulMaxItems > 0 )
		{
			if( m_queueObjects.size() + 1 > m_ulMaxItems )
			{
				throw CEMSException( EMS_OVERFLOW );
			}
		}
		
		m_queueObjects.push( obj );

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}
}

template<class T>
void
CEMSObjectQueue<T>::Push( const T& cobj )
{
	try
	{
		m_csObjQueue.Enter();

		if( m_ulMaxItems > 0 )
		{
			if( m_queueObjects.size() + 1 > m_ulMaxItems )
			{
				throw CEMSException( EMS_OVERFLOW );
			}
		}
		
		m_queueObjects.push( cobj );

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}
}

template<class T>
T
CEMSObjectQueue<T>::Pop()
{
	T ret;

	try
	{
		m_csObjQueue.Enter();

		if( m_queueObjects.size() > 0 )
		{
			ret = m_queueObjects.front();
			m_queueObjects.pop();
		}

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}

	return ret;
}

template<class T>
void
CEMSObjectQueue<T>::SetMaxSize( const ULONG culItems )
{
	try
	{
		m_csObjQueue.Enter();

		m_ulMaxItems = culItems;

		if( m_ulMaxItems < m_queueObjects.size() )
		{
			throw CEMSException( EMS_OVERFLOW );
		}

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}
}

template<class T>
ULONG
CEMSObjectQueue<T>::Count()
{
	ULONG ulRet = 0;

	try
	{
		m_csObjQueue.Enter();

		ulRet = m_queueObjects.size();

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}

	return ulRet;
}

template<class T>
ULONG
CEMSObjectQueue<T>::GetMaxSize()
{
	ULONG ulRet = 0;

	try
	{
		m_csObjQueue.Enter();

		ulRet = m_ulMaxItems;

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}

	return ulRet;
}

template<class T>
void
CEMSObjectQueue<T>::Clear()
{
	try
	{
		m_csObjQueue.Enter();

		while( m_queueObjects.size() > 0 )
		{
			m_queueObjects.pop();
		}

		m_csObjQueue.Leave();
	}
	catch( ... )
	{
		m_csObjQueue.Leave();

		throw;
	}

}

#endif