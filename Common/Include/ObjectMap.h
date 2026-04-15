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


#ifndef __OBJECT_MAP_H__
#define __OBJECT_MAP_H__

#include "aobjbase.h"
#include <map>

//! @class CEMSObjectMap
//! A map of objects.
template<class Key,class T>
class CEMSObjectMap : public CApiObjBase
{
	public:
		CEMSObjectMap();
		CEMSObjectMap( const CEMSObjectMap& x );
		virtual ~CEMSObjectMap();

		//! @fn CEMSObjectMap<Key,T>& operator=( const CEMSObjectMap<Key,T>& rhs  )
		//! Overload of the assignment operator.
		CEMSObjectMap<Key,T>& operator=( const CEMSObjectMap<Key,T>& rhs );

		//! @fn CEMSObjectMap<Key,T>& operator+=( const CEMSObjectMap<Key,T>& rhs )
		//! Append operator.
		CEMSObjectMap<Key,T>& operator+=( const CEMSObjectMap<Key,T>& rhs );

		//! @fn bool Add( const Key& ckeyValue, const T& oObject );
		//! Add an object to the map.
		bool Add( const Key& ckeyValue, const T& oObject );

		//! @fn ULONG Count() const
		//! Return the number of objects currently stored in the map.
		ULONG Count() const;

		//! @fn bool IsInMap( Key& keyValue ) const
		//! Determine whether a value is currently stored under the given key.
		bool IsInMap( const Key& keyValue ) const;

		//! @fn T	Get( Key& keyValue )
		//! Get an object stored at the specifed key.
		T	Get( const Key& keyValue );

		//! @fn void MoveFirst()
		//! Move to the first element in the map.
		void MoveFirst();

		//! @fn void MoveLast()
		//! Move to the last element in the map.
		void MoveLast();

		//! @fn T GetNext()
		//! Get the next value in the map.
		T GetNext();

		//! @fn void Remove( Key& keyValue )
		//! Remove any value with the given key from the map.
		void Remove( Key& keyValue );

		//! @fn void Clear()
		//! Clear the map's contents.
		void Clear() { _Clear(); }

		//! Useful for iterating over all items.
		void GetNext( Key& rKey, T& rValue );

		//! Get the key of the current element.
		Key GetKey();

		//! Remove the current element;
		void RemoveCurrent();
		
	private:
		void	_Clear();
		void	_Append( const CEMSObjectMap<Key,T>& oList );

	private:
		std::map<Key,T>				m_mapObjects;
		typename std::map<Key,T>::iterator	m_itNext;
};

template<class Key,class T>
CEMSObjectMap<Key,T>::CEMSObjectMap()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSObjectMap<Key,T>::CEMSObjectMap( const CEMSObjectMap<Key,T>& x )
{
	_Clear();
	_Append( x );
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSObjectMap<Key,T>::~CEMSObjectMap( )
{
	_Clear();
}

template<class Key,class T>
CEMSObjectMap<Key,T>&
CEMSObjectMap<Key,T>::operator=( const CEMSObjectMap<Key,T>& rhs )
{
	// Clear the existing list.
	_Clear();

	// Add the input list.
	_Append( rhs );

	return *this;
}

template<class Key,class T>
CEMSObjectMap<Key,T>&
CEMSObjectMap<Key,T>::operator+=( const CEMSObjectMap<Key,T>& rhs )
{
	_Append( rhs );

	return *this;
}

template<class Key,class T>
bool
CEMSObjectMap<Key,T>::Add( const Key& ckeyValue, const T& coObject )
{
	bool bRet = false;

	std::pair<std::map<Key,T>::iterator,bool> prResult = m_mapObjects.insert( std::pair<Key,T>( ckeyValue, coObject ) );

	bRet = prResult.second;

	return bRet;
}

template<class Key,class T>
ULONG	
CEMSObjectMap<Key,T>::Count() const
{
	return m_mapObjects.size();
}

template<class Key,class T>
bool 
CEMSObjectMap<Key,T>::IsInMap( const Key& keyValue ) const
{
	bool bRet = false;

	std::map<Key,T>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		bRet = true;
	}
	return bRet;
}

template<class Key,class T>
T		
CEMSObjectMap<Key,T>::Get( const Key& keyValue )
{
	T oRet;

	std::map<Key,T>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		oRet = citFind->second;

	}

	return oRet;
}

template<class Key,class T>
void
CEMSObjectMap<Key,T>::MoveFirst()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
void
CEMSObjectMap<Key,T>::MoveLast()
{
	m_itNext = m_mapObjects.end();
	m_itNext--;
}

template<class Key,class T>
T
CEMSObjectMap<Key,T>::GetNext()
{
	T oRet;

	if( m_itNext != m_mapObjects.end() )
	{
		oRet = m_itNext->second;

		m_itNext++;
	}

	return oRet;
}

template<class Key,class T>
void
CEMSObjectMap<Key,T>::Remove( Key& keyValue )
{
	m_mapObjects.erase( keyValue );
}


template<class Key,class T>
void 
CEMSObjectMap<Key,T>::GetNext( Key& rKey, T& rValue )
{
	if( m_itNext != m_mapObjects.end() )
	{
		rKey = m_itNext->first;
		rValue = m_itNext->second;

		m_itNext++;
	}
}

template<class Key,class T>
Key
CEMSObjectMap<Key,T>::GetKey()
{
	std::map<Key,T>::iterator it = m_itNext;
	it--;

	return it->first;
}

template<class Key,class T>
void 
CEMSObjectMap<Key,T>::RemoveCurrent()
{
	std::map<Key,T>::iterator it = m_itNext;
	it--;

	m_mapObjects.erase( it );
}

template<class Key,class T>
void
CEMSObjectMap<Key,T>::_Clear()
{
	m_mapObjects.clear();
}

template<class Key,class T>
void
CEMSObjectMap<Key,T>::_Append( const CEMSObjectMap<Key,T>& oMap )
{
	std::map<Key,T>::const_iterator it = oMap.m_mapObjects.begin();

	while( it != oMap.m_mapObjects.end() )
	{
		Add( it->first, it->second );

		it++;
	}
}


#endif