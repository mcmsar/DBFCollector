/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/


#ifndef __POINTER_MULTI_MAP_H__
#define __POINTER_MULTI_MAP_H__

#include "aobjbase.h"
#include "pointerlist.h"
#include <map>

//! A multimap of pointers to objects.  The objects are assumed to have an AddRef and Release method.
template<class Key,class T>
class CEMSPointerMultiMap : public CApiObjBase
{
	public:
		CEMSPointerMultiMap();
		CEMSPointerMultiMap( const CEMSPointerMultiMap& x );
		virtual ~CEMSPointerMultiMap();

		//! Overload of the assignment operator.
		CEMSPointerMultiMap<Key,T>& operator=( const CEMSPointerMultiMap<Key,T>& rhs );

		//! Append operator.
		CEMSPointerMultiMap<Key,T>& operator+=( const CEMSPointerMultiMap<Key,T>& rhs );

		//! Add an object pointer to the map.
		bool Add( const Key& ckeyValue, T* pObject );

		//! Return the number of object pointers currently stored in the map.
		ULONG Count() const;

		//! Determine whether a value is currently stored under the given key.
		bool IsInMap( Key& keyValue ) const;

		//! Get a pointer to the object stored at the specifed key.
		CEMSPointerList<T>	Get( Key& keyValue );

		//! Move to the first element in the map.
		void MoveFirst();

		//! Move to the last element in the map.
		void MoveLast();

		//! Get a pointer to the next value in the map.
		T* GetNext();

		//! Remove any value with the given key from the map.
		void Remove( Key& keyValue );

		//! Clear the map's contents.
		void Clear() { _Clear(); }

		//! Remove the last retrieved item from the map.
		void RemoveCurrent();
		
	private:
		void	_Clear();
		void	_Append( const CEMSPointerMultiMap<Key,T>& oList );

	private:
		std::multimap<Key,T*>			m_mapObjects;
		std::multimap<Key,T*>::iterator	m_itNext;
};

template<class Key,class T>
CEMSPointerMultiMap<Key,T>::CEMSPointerMultiMap()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSPointerMultiMap<Key,T>::CEMSPointerMultiMap( const CEMSPointerMultiMap<Key,T>& x )
{
	_Clear();
	_Append( x );
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSPointerMultiMap<Key,T>::~CEMSPointerMultiMap( )
{
	_Clear();
}

template<class Key,class T>
CEMSPointerMultiMap<Key,T>&
CEMSPointerMultiMap<Key,T>::operator=( const CEMSPointerMultiMap<Key,T>& rhs )
{
	// Clear the existing list.
	_Clear();

	// Add the input list.
	_Append( rhs );

	return *this;
}

template<class Key,class T>
CEMSPointerMultiMap<Key,T>&
CEMSPointerMultiMap<Key,T>::operator+=( const CEMSPointerMultiMap<Key,T>& rhs )
{
	_Append( rhs );

	return *this;
}

template<class Key,class T>
bool
CEMSPointerMultiMap<Key,T>::Add( const Key& ckeyValue, T* pObject )
{
	bool bRet = false;

	if( pObject )
	{
		std::multimap<Key,T*>::iterator it = m_mapObjects.insert( std::pair<Key,T*>( ckeyValue, pObject ) );

		bRet = ( m_mapObjects.end() != it ) ? true : false;

		if( bRet )
			pObject->AddRef();
	}

	return bRet;
}

template<class Key,class T>
ULONG	
CEMSPointerMultiMap<Key,T>::Count() const
{
	return m_mapObjects.size();
}

template<class Key,class T>
bool 
CEMSPointerMultiMap<Key,T>::IsInMap( Key& keyValue ) const
{
	bool bRet = false;

	std::multimap<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		bRet = true;
	}
	return bRet;
}

template<class Key,class T>
CEMSPointerList<T>
CEMSPointerMultiMap<Key,T>::Get( Key& keyValue )
{
	CEMSPointerList<T> olstRet;

	std::multimap<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

	while( citFind != m_mapObjects.end() )
	{
		olstRet.Add( citFind->second );

		citFind++;
	}

	return olstRet;
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::MoveFirst()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::MoveLast()
{
	m_itNext = m_mapObjects.end();
	m_itNext--;
}

template<class Key,class T>
T*
CEMSPointerMultiMap<Key,T>::GetNext()
{
	T* pRet = 0;

	if( m_itNext != m_mapObjects.end() )
	{
		pRet = m_itNext->second;

		if( pRet )
		{
			pRet->AddRef();
		}

		m_itNext++;
	}

	return pRet;
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::Remove( Key& keyValue )
{
	T* pDeleted = 0;
	std::multimap<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		pDeleted = citFind->second;

		if( pDeleted )
		{
			m_mapObjects.erase( keyValue );
			pDeleted->Release();
			pDeleted = 0;
		}
	}
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::RemoveCurrent()
{
	if( m_itNext != m_mapObjects.begin() )
	{
		std::multimap<Key,T*>::iterator itCurrent = m_itNext;
		itCurrent--;
		Remove( (Key&) itCurrent->first );
	}
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::_Clear()
{
	std::multimap<Key,T*>::iterator it = m_mapObjects.begin();

	while( it != m_mapObjects.end() )
	{
		if( it->second )
			it->second->Release();

		it->second = 0;

		it++;
	}

	m_mapObjects.clear();
}

template<class Key,class T>
void
CEMSPointerMultiMap<Key,T>::_Append( const CEMSPointerMultiMap<Key,T>& oMap )
{
	std::multimap<Key,T*>::const_iterator it = oMap.m_mapObjects.begin();

	while( it != oMap.m_mapObjects.end() )
	{
		Add( it->first, it->second );

		it++;
	}
}


#endif