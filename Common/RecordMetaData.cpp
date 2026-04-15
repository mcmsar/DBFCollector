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
	 2    Common    1.1         11/02/2005 4:15:04 PM  Jason Bass      Added new
	      constructor.
	 1    Common    1.0         10/02/2005 2:38:25 PM  Jason Bass      
	$
********************************************************************/

#include "recordmetadata.h"
#include "emsexcpt.h"

CEMSRecordMetaData::CEMSRecordMetaData() : m_ulFields(0), m_aDescriptors(0)
{
}

CEMSRecordMetaData::CEMSRecordMetaData( const CEMSRecordMetaData& x )  : m_ulFields(0), m_aDescriptors(0)
{
	_Set( x.m_ulFields, x.m_aDescriptors );
}

CEMSRecordMetaData::CEMSRecordMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors ) : 
																				m_ulFields(0),
																				m_aDescriptors(0)
{
	_Set( culFields, caDescriptors );
}

CEMSRecordMetaData::~CEMSRecordMetaData()
{
	_Clear();
}

void 
CEMSRecordMetaData::Set( const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors )
{
	_Set( culFields, caDescriptors );
}

const EMSFIELDDESCRIPTOR* 
CEMSRecordMetaData::GetDescriptorPtr( const ULONG culIndex )
{
	const EMSFIELDDESCRIPTOR* cpRet = 0;

	if( !(culIndex < m_ulFields) )
	{
		throw CEMSException( EMS_ARRAY_OUT_OF_BOUNDS );
	}

	if( !m_aDescriptors )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	cpRet = &( m_aDescriptors[ culIndex ] );

	return cpRet;

}

long 
CEMSRecordMetaData::GetSize( const ULONG culIndex )
{
	if( !(culIndex < m_ulFields) )
	{
		throw CEMSException( EMS_ARRAY_OUT_OF_BOUNDS );
	}

	if( !m_aDescriptors )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	return m_aDescriptors[culIndex].lSize;
}

std::wstring 
CEMSRecordMetaData::GetName( const ULONG culIndex )
{
	if( !(culIndex < m_ulFields) )
	{
		throw CEMSException( EMS_ARRAY_OUT_OF_BOUNDS );
	}

	if( !m_aDescriptors )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	return std::wstring( m_aDescriptors[culIndex].wszName );
}

long 
CEMSRecordMetaData::GetIndex( const wchar_t* cwszColumn )
{
	long lIndex = -1;

	if( cwszColumn )
	{
		for( ULONG l = 0; l < m_ulFields && (-1 == lIndex); l++ )
		{
			if( 0 == wcsicmp( m_aDescriptors[l].wszName, cwszColumn ) )
			{
				lIndex = l;
			}
		}
	}

	return lIndex;
}

void 
CEMSRecordMetaData::_Set(  const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors )
{
	_Clear();

	_AllocateCopy( culFields, caDescriptors, m_ulFields, m_aDescriptors );
}

void 
CEMSRecordMetaData::_Clear()
{
	if( m_aDescriptors )
	{
		delete[] m_aDescriptors;
		m_aDescriptors = 0;
	}

	m_ulFields = 0;
}

void 
CEMSRecordMetaData::AllocateCopy( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
{
	_AllocateCopy( m_ulFields, m_aDescriptors, ulFields, aFields );
}

void 
CEMSRecordMetaData::_AllocateCopy
(	const ULONG					culOrigFields,
	const EMSFIELDDESCRIPTOR*	caOrigFields,
	ULONG&						ulFields, 
	EMSFIELDDESCRIPTOR*&		aFields )
{
	if ( culOrigFields > 0 && caOrigFields )
	{
		aFields = new EMSFIELDDESCRIPTOR[ culOrigFields ];
		if ( !aFields )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
		memcpy( aFields, caOrigFields, culOrigFields*sizeof(EMSFIELDDESCRIPTOR) );
		ulFields = culOrigFields;
	}
}

