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


#ifndef __POINTER_MAP_H__
#define __POINTER_MAP_H__

#include "aobjbase.h"
#include <map>

//! @class CEMSPointerMap
//! A map of pointers to objects.  The objects are assumed to have an AddRef and Release method.
template<class Key,class T>
class CEMSPointerMap : public CApiObjBase
{
	public:
		CEMSPointerMap();
		CEMSPointerMap( const CEMSPointerMap& x );
		virtual ~CEMSPointerMap();

		//! @fn CEMSPointerMap<Key,T>& operator=( const CEMSPointerMap<Key,T>& rhs  )
		//! Overload of the assignment operator.
		CEMSPointerMap<Key,T>& operator=( const CEMSPointerMap<Key,T>& rhs );

		//! @fn CEMSPointerMap<Key,T>& operator+=( const CEMSPointerMap<Key,T>& rhs )
		//! Append operator.
		CEMSPointerMap<Key,T>& operator+=( const CEMSPointerMap<Key,T>& rhs );

		//! @fn bool Add( const Key& ckeyValue, T* pObject );
		//! Add an object pointer to the map.
		bool Add( const Key& ckeyValue, T* pObject );

		//! @fn ULONG Count() const
		//! Return the number of object pointers currently stored in the map.
		ULONG Count() const;

		//! @fn bool IsInMap( Key& keyValue ) const
		//! Determine whether a value is currently stored under the given key.
		bool IsInMap( Key& keyValue ) const;

		//! @fn T*	Get( Key& keyValue )
		//! Get a pointer to the object stored at the specifed key.
		T*	Get( Key& keyValue );

		//! @fn void MoveFirst()
		//! Move to the first element in the map.
		void MoveFirst();

		//! @fn void MoveLast()
		//! Move to the last element in the map.
		void MoveLast();

		//! @fn T* GetNext()
		//! Get a pointer to the next value in the map.
		T* GetNext();

		//! @fn void Remove( Key& keyValue )
		//! Remove any value with the given key from the map.
		void Remove( Key& keyValue );

		//! @fn void Clear()
		//! Clear the map's contents.
		void Clear() { _Clear(); }

		//! Remove the last retrieved item from the map.
		void RemoveCurrent();
		
	private:
		void	_Clear();
		void	_Append( const CEMSPointerMap<Key,T>& oList );

	private:
		std::map<Key,T*>			m_mapObjects;
		typename std::map<Key,T*>::iterator	m_itNext;
};

template<class Key,class T>
CEMSPointerMap<Key,T>::CEMSPointerMap()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSPointerMap<Key,T>::CEMSPointerMap( const CEMSPointerMap<Key,T>& x )
{
	_Clear();
	_Append( x );
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
CEMSPointerMap<Key,T>::~CEMSPointerMap( )
{
	_Clear();
}

template<class Key,class T>
CEMSPointerMap<Key,T>&
CEMSPointerMap<Key,T>::operator=( const CEMSPointerMap<Key,T>& rhs )
{
	// Clear the existing list.
	_Clear();

	// Add the input list.
	_Append( rhs );

	return *this;
}

template<class Key,class T>
CEMSPointerMap<Key,T>&
CEMSPointerMap<Key,T>::operator+=( const CEMSPointerMap<Key,T>& rhs )
{
	_Append( rhs );

	return *this;
}

template<class Key,class T>
bool
CEMSPointerMap<Key,T>::Add( const Key& ckeyValue, T* pObject )
{
	bool bRet = false;

	if( pObject )
	{
		std::pair<std::map<Key,T*>::iterator,bool> prResult = m_mapObjects.insert( std::pair<Key,T*>( ckeyValue, pObject ) );

		bRet = prResult.second;

		if( bRet )
			pObject->AddRef();
	}

	return bRet;
}

template<class Key,class T>
ULONG	
CEMSPointerMap<Key,T>::Count() const
{
	return m_mapObjects.size();
}

template<class Key,class T>
bool 
CEMSPointerMap<Key,T>::IsInMap( Key& keyValue ) const
{
	bool bRet = false;

	std::map<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		bRet = true;
	}
	return bRet;
}

template<class Key,class T>
T*		
CEMSPointerMap<Key,T>::Get( Key& keyValue )
{
	T* pRet = 0;

	std::map<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

	if( citFind != m_mapObjects.end() )
	{
		pRet = citFind->second;

		if( pRet )
			pRet->AddRef();
	}

	return pRet;
}

template<class Key,class T>
void
CEMSPointerMap<Key,T>::MoveFirst()
{
	m_itNext = m_mapObjects.begin();
}

template<class Key,class T>
void
CEMSPointerMap<Key,T>::MoveLast()
{
	m_itNext = m_mapObjects.end();
	m_itNext--;
}

template<class Key,class T>
T*
CEMSPointerMap<Key,T>::GetNext()
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
CEMSPointerMap<Key,T>::Remove( Key& keyValue )
{
	T* pDeleted = 0;
	std::map<Key,T*>::const_iterator citFind = m_mapObjects.find( keyValue );

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
CEMSPointerMap<Key,T>::RemoveCurrent()
{
	if( m_itNext != m_mapObjects.begin() )
	{
		std::map<Key,T*>::iterator itCurrent = m_itNext;
		itCurrent--;
		Remove( (Key&) itCurrent->first );
	}
}

template<class Key,class T>
void
CEMSPointerMap<Key,T>::_Clear()
{
	std::map<Key,T*>::iterator it = m_mapObjects.begin();

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
CEMSPointerMap<Key,T>::_Append( const CEMSPointerMap<Key,T>& oMap )
{
	std::map<Key,T*>::const_iterator it = oMap.m_mapObjects.begin();

	while( it != oMap.m_mapObjects.end() )
	{
		Add( it->first, it->second );

		it++;
	}
}


#endif