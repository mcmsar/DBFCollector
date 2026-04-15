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

	$Log$





********************************************************************/

#ifndef __POINTER_LIST_H__
#define __POINTER_LIST_H__

#include "aobjbase.h"
#include "criticalsection.h"
#include <list>

//! @class CEMSPointerList
//! A list of pointers to objects.  This class is thread-safe.
template<class T>
class CEMSPointerList : public CApiObjBase
{
	public:
		CEMSPointerList();
		CEMSPointerList( const CEMSPointerList& x );
		virtual ~CEMSPointerList();

		//! @fn CEMSPointerList& operator=( const CEMSPointerList<T>& rhs  )
		//! Overload of the assignment operator.
		CEMSPointerList<T>& operator=( const CEMSPointerList<T>& rhs );

		//! @fn CEMSPointerList<T>& operator+=( const CEMSPointerList<T>& rhs )
		//! Append operator.
		CEMSPointerList<T>& operator+=( const CEMSPointerList<T>& rhs );

		//! @fn void Add( T* pObject )
		//! Add an object pointer to the list.
		void	Add( T* pObject );

		//! @fn ULONG Count()
		//! Return the number of object pointers currently stored in the list.
		ULONG	Count();

		//! @fn void MoveFirst()
		//! Navigate to the beginning of the list.
		void	MoveFirst();

		//! @fn void MoveLast()
		//! Navigate to the end of the list.
		void		MoveLast();

		//! @fn T*	GetNext()
		//! Retrieve a pointer to the next object in the list.
		T*		GetNext();

		//! @fn void	Clear()
		//! Clear all entries from the list.
		void	Clear() { _Clear(); }

		//! @fn bool	IsInList()
		//! To find out if given object is already in the list.
		bool	IsInList( T* pObject );

		void    RemoveCurrent();

		//! Set the maximum number of pointers that can be held in the list.  Once the 
		//! maximum is reached, further attempts to add/append will result in requests being ignored.
		void SetMaxSize( const ULONG culMaxSize ) { m_ulMaxSize = culMaxSize; }

		
	private:
		void	_Clear();
		void	_Append( const CEMSPointerList<T>& oList );

	private:
		std::list<T*>			m_lstObjects;
		typename std::list<T*>::iterator	m_itNext;
		CEMSCriticalSection		m_csList;
		ULONG					m_ulMaxSize;
};

template<class T>
CEMSPointerList<T>::CEMSPointerList() : m_ulMaxSize(0)
{
	try
	{
		m_csList.Enter();

		m_itNext = m_lstObjects.begin();

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();
		throw;
	}
}

template<class T>
CEMSPointerList<T>::CEMSPointerList( const CEMSPointerList& x ) : m_ulMaxSize(x.m_ulMaxSize)
{
	try
	{
		m_csList.Enter();

		_Clear();
		_Append( x );
		m_itNext = m_lstObjects.begin();

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}
}

template<class T>
CEMSPointerList<T>::~CEMSPointerList( )
{
	try
	{
		m_csList.Enter();
		
		_Clear();

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();
		throw;
	}
}

template<class T>
CEMSPointerList<T>&
CEMSPointerList<T>::operator=( const CEMSPointerList<T>& rhs )
{
	try
	{
		m_csList.Enter();

		// Clear the existing list.
		_Clear();

		// Add the input list.
		_Append( rhs );

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();
		throw;
	}

	return *this;
}

template<class T>
CEMSPointerList<T>&
CEMSPointerList<T>::operator+=( const CEMSPointerList<T>& rhs )
{
	try
	{
		m_csList.Enter();

		_Append( rhs );

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}

	return *this;
}

template<class T>
void
CEMSPointerList<T>::Add( T* pObject )
{
	try
	{
		m_csList.Enter();

		// 0 Max size means don't limit the size.
		if( 0 == m_ulMaxSize ||
			m_lstObjects.size() < m_ulMaxSize )
		{
			m_lstObjects.push_back( pObject );
			pObject->AddRef();
		}

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();
		throw;
	}
}

template<class T>
ULONG	
CEMSPointerList<T>::Count()
{
	ULONG ulRet = 0;

	try
	{
		m_csList.Enter();

		ulRet = m_lstObjects.size();

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}

	return ulRet;
}

template<class T>
bool
CEMSPointerList<T>::IsInList( T* pObject )
{
	bool bInList = false;
	try
	{
		m_csList.Enter();
		std::list<T*>::iterator it = m_lstObjects.begin();

		while( it != m_lstObjects.end() )
		{
			if ( *it == pObject )
			{
				bInList = true;
				break;
			}
			it++;
		}
	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}
	return bInList;
}


template<class T>
void
CEMSPointerList<T>::MoveFirst()
{
	try
	{
		m_csList.Enter();
		
		m_itNext = m_lstObjects.begin();

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}
}

template<class T>
void
CEMSPointerList<T>::MoveLast()
{
	try
	{
		m_csList.Enter();

		m_itNext = m_lstObjects.end();
		m_itNext--;

		m_csList.Leave();

	}
	catch( ... )
	{
		m_csList.Leave();

		throw;
	}
}


template<class T>
T*		
CEMSPointerList<T>::GetNext()
{
	T* pRet = 0;

	try
	{
		m_csList.Enter();

		if( m_itNext != m_lstObjects.end() )
		{
			pRet = *m_itNext;

			if( pRet )
			{
				pRet->AddRef();
			}

			m_itNext++;
		}

		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}


template<class T>
void
CEMSPointerList<T>::RemoveCurrent( )
{
	try
	{
		m_csList.Enter();

		if( --m_itNext != m_lstObjects.end() )
		{
			T* pRef = (*m_itNext);
			if( pRef )
			{
				pRef->Release();
			}
			m_itNext = m_lstObjects.erase( m_itNext );
		}
		m_csList.Leave();
	}
	catch( ... )
	{
		m_csList.Leave();
		throw;
	}
}


template<class T>
void
CEMSPointerList<T>::_Clear()
{
	std::list<T*>::iterator it = m_lstObjects.begin();

	while( it != m_lstObjects.end() )
	{
		if( *it )
			(*it)->Release();

		*it = 0;

		it++;
	}

	m_lstObjects.clear();
}

template<class T>
void
CEMSPointerList<T>::_Append( const CEMSPointerList<T>& oList )
{
	std::list<T*>::const_iterator it = oList.m_lstObjects.begin();

	while( it != oList.m_lstObjects.end() )
	{
		Add( *it );

		it++;
	}
}


#endif

