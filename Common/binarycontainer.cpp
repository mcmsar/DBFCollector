/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#include "binarycontainer.h"
#include <memory.h>

BinaryContainer::BinaryContainer() : m_buffer(NULL), m_iSize(0)
{
}

BinaryContainer::BinaryContainer( const BYTE* cBuffer, const int ciSize ) : m_buffer(NULL), m_iSize(0)
{
	Set( cBuffer, ciSize );
}

BinaryContainer::BinaryContainer( const BinaryContainer& x ) : m_buffer(NULL), m_iSize(0)
{
	Set( x.GetBuffer(), x.GetSize() );
}

BinaryContainer::~BinaryContainer()
{
	_Clear();
}

void 
BinaryContainer::Set( const BYTE* cBuffer, const int ciSize )
{
	_Clear();

	if( cBuffer && (ciSize > 0 ) )
	{
		m_buffer = new BYTE[ ciSize ];
		memset( m_buffer, 0, ciSize );

		memcpy( m_buffer, cBuffer, ciSize );

		m_iSize = ciSize;
	}
}

void 
BinaryContainer::_Clear()
{
	if( m_buffer )
	{
		delete[] m_buffer;
		m_buffer = NULL;
	}

	m_iSize = 0;
}