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

	$Log$
********************************************************************/

#include "rawdatarecord.h"
#include "emsexcpt.h"

CEMSRawDataRecord::CEMSRawDataRecord() : m_ulBufferSize(0), m_abyRawData(0)
{
}

CEMSRawDataRecord::CEMSRawDataRecord( const ULONG culBufferSize, const unsigned char* cabyData ) : m_ulBufferSize(0), m_abyRawData(0)
{
	_Copy( culBufferSize, cabyData );
}

CEMSRawDataRecord::CEMSRawDataRecord( const CEMSRawDataRecord& x ) : m_ulBufferSize(0), m_abyRawData(0)
{
	_Copy( x.m_ulBufferSize, x.m_abyRawData );
}

CEMSRawDataRecord::~CEMSRawDataRecord()
{
	_Clear();
}

void 
CEMSRawDataRecord::Set( const ULONG culBufferSize, const unsigned char* cabyData )
{
	_Copy( culBufferSize, cabyData );
}

unsigned char* 
CEMSRawDataRecord::GetData()
{
	unsigned char* abyRet = 0;

	if( m_ulBufferSize > 0 && m_abyRawData )
	{
		abyRet = new unsigned char[ m_ulBufferSize ];

		if( !abyRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyRet, 0, m_ulBufferSize*sizeof(unsigned char) );

		memcpy( abyRet, m_abyRawData, m_ulBufferSize*sizeof(unsigned char) );
	}

	return abyRet;
}

void 
CEMSRawDataRecord::_Copy( const ULONG culBufferSize, const unsigned char* cabyData )
{
	_Clear();

	if( culBufferSize > 0 )
	{
		m_abyRawData = new unsigned char[ culBufferSize ];

		if( !m_abyRawData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_abyRawData, 0, culBufferSize*sizeof(unsigned char) );

		memcpy( m_abyRawData, cabyData, culBufferSize*sizeof(unsigned char) );

		m_ulBufferSize = culBufferSize;
	}
}

void
CEMSRawDataRecord::_Clear()
{
	if( m_abyRawData )
	{
		delete[] m_abyRawData;
		m_abyRawData = 0;
	}

	m_ulBufferSize = 0;
}