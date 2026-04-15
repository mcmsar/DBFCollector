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

#ifndef __OBJECT_SET_H__
#define __OBJECT_SET_H__

#include "aobjbase.h"
#include <set>
#include "criticalsection.h"

//! @class CEMSObjectSet
//! A list of objects.  This set is thread-safe, though care should be taken when using the MoveFirst and
//! GetNext methods in a multi-threaded scenario.
template<class T>
class CEMSObjectSet : public CApiObjBase
{
	public:
		CEMSObjectSet();
		CEMSObjectSet( const CEMSObjectSet& x );
		virtual ~CEMSObjectSet();

		//! @fn CEMSObjectSet<T>& operator=( const CEMSObjectSet<T>& rhs )
		//! Assignment operator.
		CEMSObjectSet<T>& operator=( const CEMSObjectSet<T>& rhs );

		//! @fn CEMSObjectSet<T>& operator+=( const CEMSObjectSet<T>& rhs )
		//! Append operator.
		CEMSObjectSet<T>& operator+=( const CEMSObjectSet<T>& rhs );

		//! @fn bool Add( const T& oObject )
		//! Add an object to the list.  Returns true if it was added and false if not.
		bool	Add( const T& oObject );

		//! @fn ULONG Count()
		//! Return the number of objects currently stored in the list.
		ULONG	Count();

		//! @fn void MoveFirst()
		//! Navigate to the beginning of the list.
		void	MoveFirst();

		//! @fn T GetNext()
		//! Retrieve the next object in the list.
		T		GetNext();

		//! @fn bool	IsInSet( const T& obj )
		//! Determine whether the object is in the set.
		bool	IsInSet( const T& obj );

		//! @fn void	Clear()
		//! Clear the contents of the set.
		void	Clear() { _Clear(); }

		//! Remove the item from the set.
		void Remove( const T& coObject );

	private:
		void	_Clear();
		void	_Append( const CEMSObjectSet<T>& oSet );

	private:
		std::set<T>				m_setObjects;
		typename std::set<T>::iterator	m_itNext;
		CEMSCriticalSection m_oCS;
};

template<class T>
CEMSObjectSet<T>::CEMSObjectSet()
{
	m_itNext = m_setObjects.begin();
}

template<class T>
CEMSObjectSet<T>::CEMSObjectSet( const CEMSObjectSet<T>& x )
{
	_Append( x );

	m_itNext = m_setObjects.begin();
}

template<class T>
CEMSObjectSet<T>::~CEMSObjectSet( )
{
	_Clear();
}

template<class T>
CEMSObjectSet<T>& 
CEMSObjectSet<T>::operator=( const CEMSObjectSet<T>& rhs )
{
	try
	{
		m_oCS.Enter();

		_Clear();
		_Append( rhs );

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}

	return *this;
}

template<class T>
CEMSObjectSet<T>& 
CEMSObjectSet<T>::operator+=( const CEMSObjectSet<T>& rhs )
{
	try
	{
		m_oCS.Enter();
		_Append( rhs );
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}

	return *this;
}

template<class T>
bool
CEMSObjectSet<T>::Add( const T& coObject )
{
	std::pair<std::set<T>::iterator, bool> prResult;

	try
	{
		m_oCS.Enter();
		prResult = m_setObjects.insert( coObject );
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}

	return prResult.second;
}

template<class T>
ULONG	
CEMSObjectSet<T>::Count()
{
	ULONG ulRet = 0;
	try
	{
		m_oCS.Enter();
		ulRet = m_setObjects.size();
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}

	return ulRet;
}

template<class T>
void
CEMSObjectSet<T>::MoveFirst()
{
	try
	{
		m_oCS.Enter();
		m_itNext = m_setObjects.begin();
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
}

template<class T>
T	
CEMSObjectSet<T>::GetNext()
{
	T oRet;

	try
	{
		m_oCS.Enter();

		if( m_itNext != m_setObjects.end() )
		{
			oRet = *m_itNext;

			m_itNext++;
		}

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}

	return oRet;
}

template<class T>
bool	
CEMSObjectSet<T>::IsInSet( const T& obj )
{
	bool bRet = false;

	try
	{
		m_oCS.Enter();

		std::set<T>::const_iterator cit = m_setObjects.find( obj );

		if( cit != m_setObjects.end() )
		{
			bRet = true;
		}

		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();

		throw;
	}

	return bRet;
}

template<class T>
void
CEMSObjectSet<T>::Remove( const T& coObject )
{
	try
	{
		m_oCS.Enter();
		m_setObjects.erase( coObject );
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
}

template<class T>
void	
CEMSObjectSet<T>::_Clear()
{
	m_setObjects.clear();
	m_itNext = m_setObjects.begin();
}

template<class T>
void
CEMSObjectSet<T>::_Append( const CEMSObjectSet<T>& oSet )
{
	// Can't use member functions of rhs since they are not const.
	std::set<T>::const_iterator it = oSet.m_setObjects.begin();

	while( it != oSet.m_setObjects.end() )
	{
		Add( *it);
		it++;
	}

}

#endif