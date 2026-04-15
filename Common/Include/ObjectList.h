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

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include "aobjbase.h"
#include <list>

//! @class CEMSObjectList
//! A list of objects.
template<class T>
class CEMSObjectList : public CApiObjBase
{
	public:
		CEMSObjectList();
		CEMSObjectList( const CEMSObjectList& x );
		virtual ~CEMSObjectList();

		//! @fn CEMSObjectList<T>& operator=( const CEMSObjectList<T>& rhs )
		//! Assignment operator.
		CEMSObjectList<T>& operator=( const CEMSObjectList<T>& rhs );

		//! @fn CEMSObjectList<T>& operator+=( const CEMSObjectList<T>& rhs )
		//! Append operator.
		CEMSObjectList<T>& operator+=( const CEMSObjectList<T>& rhs );

		//! @fn void Add( const T& oObject )
		//! Add an object to the list.
		void	Add( const T& oObject );

		//! @fn ULONG Count()
		//! Return the number of objects currently stored in the list.
		ULONG	Count();

		//! @fn void MoveFirst()
		//! Navigate to the beginning of the list.
		void	MoveFirst();

		//! @fn T GetNext()
		//! Retrieve the next object in the list.
		T		GetNext();

		//! @fn void Clear()
		//! Clear all objects from the list.
		void Clear() { _Clear(); }

		//! Get value at the specified index.
		bool Get( const ULONG culIndex, T& roValue );

		//! Sort the list, ascending.
		void Sort();

	private:
		void	_Clear();
		void	_Append( const CEMSObjectList<T>& oList );

	private:
		std::list<T>			m_lstObjects;
		typename std::list<T>::iterator	m_itNext;
};

template<class T>
CEMSObjectList<T>::CEMSObjectList()
{
	m_itNext = m_lstObjects.begin();
}

template<class T>
CEMSObjectList<T>::CEMSObjectList( const CEMSObjectList<T>& x )
{
	_Append( x );

	m_itNext = m_lstObjects.begin();
}

template<class T>
CEMSObjectList<T>::~CEMSObjectList( )
{
	_Clear();
}

template<class T>
CEMSObjectList<T>& 
CEMSObjectList<T>::operator=( const CEMSObjectList<T>& rhs )
{
	_Clear();
	_Append( rhs );

	return *this;
}

template<class T>
CEMSObjectList<T>& 
CEMSObjectList<T>::operator+=( const CEMSObjectList<T>& rhs )
{
	_Append( rhs );

	return *this;
}

template<class T>
void
CEMSObjectList<T>::Add( const T& coObject )
{
	m_lstObjects.push_back( coObject );
}

template<class T>
ULONG	
CEMSObjectList<T>::Count()
{
	return m_lstObjects.size();
}

template<class T>
void
CEMSObjectList<T>::MoveFirst()
{
	m_itNext = m_lstObjects.begin();
}

template<class T>
T	
CEMSObjectList<T>::GetNext()
{
	T oRet;

	if( m_itNext != m_lstObjects.end() )
	{
		oRet = *m_itNext;

		m_itNext++;
	}

	return oRet;
}

template<class T>
bool 
CEMSObjectList<T>::Get( const ULONG culIndex, T& roValue )
{
	bool bRet = false;

	if( culIndex >= 0 &&
		culIndex < m_lstObjects.size() )
	{
		std::list<T>::iterator it = m_lstObjects.begin();

		for( ULONG l = 0; l < culIndex; l++ )
		{
			it++;
		}

		roValue = *it;

		bRet = true;
	}

	return bRet;
}

template<class T>
void 
CEMSObjectList<T>::Sort()
{
	m_lstObjects.sort();
}

template<class T>
void	
CEMSObjectList<T>::_Clear()
{
	m_lstObjects.clear();
	m_itNext = m_lstObjects.begin();
}

template<class T>
void
CEMSObjectList<T>::_Append( const CEMSObjectList<T>& oList )
{
	// Can't use member functions of rhs since they are not const.
	std::list<T>::const_iterator it = oList.m_lstObjects.begin();

	while( it != oList.m_lstObjects.end() )
	{
		Add( *it);
		it++;
	}

}

#endif