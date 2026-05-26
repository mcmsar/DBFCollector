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

#include "wave/wavedatachunk.h"
#include <memory.h>
#include <string.h>
#include "emsexcpt.h"
#include <crtdbg.h>

const char* CEMSWaveDataChunk::ms_cszDefaultID = "data";

CEMSWaveDataChunk::CEMSWaveDataChunk()
{
	memcpy( &m_strWaveData.dwSubChunkID, ms_cszDefaultID,
			(strlen(ms_cszDefaultID) > sizeof(m_strWaveData.dwSubChunkID)) ? sizeof(m_strWaveData.dwSubChunkID) : strlen(ms_cszDefaultID) );

	m_strWaveData.dwSubChunkSize = 0;

	m_strWaveData.abyData = 0;
}

CEMSWaveDataChunk::CEMSWaveDataChunk( const CEMSWaveDataChunk& x )
{
	memcpy( &m_strWaveData.dwSubChunkID, ms_cszDefaultID,
			(strlen(ms_cszDefaultID) > sizeof(m_strWaveData.dwSubChunkID)) ? sizeof(m_strWaveData.dwSubChunkID) : strlen(ms_cszDefaultID) );

	m_strWaveData.dwSubChunkSize = 0;

	m_strWaveData.abyData = 0;

	Write( x.m_strWaveData.abyData, x.m_strWaveData.dwSubChunkSize );
}

CEMSWaveDataChunk::~CEMSWaveDataChunk()
{
	if( m_strWaveData.abyData )
	{
		delete[] m_strWaveData.abyData;
		m_strWaveData.abyData = 0;
	}
}

DWORD 
CEMSWaveDataChunk::Write( const BYTE* cabyData, const DWORD cdwBytesInput )
{
	DWORD dwRet = 0;

	BYTE* abyTemp = 0;

	try
	{
		DWORD dwNewSize = cdwBytesInput + m_strWaveData.dwSubChunkSize;

		if( dwNewSize > 0 )
		{
			abyTemp = new BYTE[dwNewSize];

			if( !abyTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( abyTemp, 0, dwNewSize );

			//for( DWORD i = 0; i < m_strWaveData.dwSubChunkSize; i++ )
			//{
			//	abyTemp[i] = m_strWaveData.abyData[i];
			//}
			memcpy( abyTemp, m_strWaveData.abyData, m_strWaveData.dwSubChunkSize );

			//for( DWORD i2 = 0; i2 < cdwBytesInput; i2++ )
			//{
			//	abyTemp[i2 + m_strWaveData.dwSubChunkSize ] = cabyData[ i2 ];
			//}
			memcpy( &(abyTemp[m_strWaveData.dwSubChunkSize ]), 
					cabyData,
					cdwBytesInput );

			dwRet = dwNewSize;

			if( m_strWaveData.abyData )
			{
				delete[] m_strWaveData.abyData;
				m_strWaveData.abyData = 0;
			}

			m_strWaveData.abyData = abyTemp;
			m_strWaveData.dwSubChunkSize = dwNewSize;

		}
	}
	catch( ... )
	{
	}

	return dwRet;
}

DWORD 
CEMSWaveDataChunk::Read( BYTE* abyData, const DWORD cdwMaxToRead ) const
{
	DWORD dwRet = 0;

	dwRet = (cdwMaxToRead < m_strWaveData.dwSubChunkSize) ? cdwMaxToRead : m_strWaveData.dwSubChunkSize;

	//for( DWORD i = 0; i < dwRet; i++ )
	//{
	//	abyData[i] = m_strWaveData.abyData[i];
	//}

	memcpy( abyData, m_strWaveData.abyData, dwRet );

	return dwRet;
}

DWORD 
CEMSWaveDataChunk::Serialize( BYTE*& abyData ) const
{
	DWORD dwRet = 0;

	DWORD dwBytes = GetSize();

	if( dwBytes > 0 )
	{
		abyData = new BYTE[ dwBytes ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyData, 0, dwBytes*sizeof(BYTE) );

		_ASSERTE( dwBytes >= sizeof(m_strWaveData.dwSubChunkID) );
		if( dwBytes < sizeof(m_strWaveData.dwSubChunkID) )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		memcpy( abyData, &m_strWaveData.dwSubChunkID, sizeof(m_strWaveData.dwSubChunkID) );

		DWORD dwBytesRemaining = dwBytes -  sizeof(m_strWaveData.dwSubChunkID);
		_ASSERTE( dwBytesRemaining >= sizeof(m_strWaveData.dwSubChunkSize) );
		if( dwBytesRemaining < sizeof(m_strWaveData.dwSubChunkSize) )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		memcpy( abyData + sizeof(m_strWaveData.dwSubChunkID), 
					&m_strWaveData.dwSubChunkSize, sizeof(m_strWaveData.dwSubChunkSize) );

		dwBytesRemaining -= sizeof(m_strWaveData.dwSubChunkSize);
		_ASSERTE( dwBytesRemaining >= m_strWaveData.dwSubChunkSize );
		if( dwBytesRemaining < m_strWaveData.dwSubChunkSize )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		memcpy( abyData + sizeof(m_strWaveData.dwSubChunkID) + sizeof(m_strWaveData.dwSubChunkSize), 
					m_strWaveData.abyData, m_strWaveData.dwSubChunkSize );

		dwRet = dwBytes;
	}

	return dwRet;
}

DWORD 
CEMSWaveDataChunk::Serialize( IEMSSeqStream* pStrm ) const
{
	DWORD dwRet = 0;

	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	ULONG ulWritten = 0;

	EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_strWaveData.dwSubChunkID, 
								sizeof(m_strWaveData.dwSubChunkID), 
								&ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	dwRet += ulWritten;

	hr = pStrm->Write( (const BYTE*) &m_strWaveData.dwSubChunkSize, 
						sizeof(m_strWaveData.dwSubChunkSize),
						&ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	dwRet += ulWritten;

	hr = pStrm->Write( m_strWaveData.abyData, m_strWaveData.dwSubChunkSize,	&ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	dwRet += ulWritten;

	return dwRet;
}

DWORD
CEMSWaveDataChunk::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData && (dwBytes > 0 ) )
	{
		_Clear();

		if( dwBytes >= sizeof(m_strWaveData.dwSubChunkID) )
		{
			memcpy( &m_strWaveData.dwSubChunkID, abyData, sizeof(m_strWaveData.dwSubChunkID) );
		}

		abyData += sizeof(m_strWaveData.dwSubChunkID);
		dwRet += sizeof(m_strWaveData.dwSubChunkID);
		dwBytes -= sizeof(m_strWaveData.dwSubChunkID);

		if( dwBytes >= sizeof(m_strWaveData.dwSubChunkSize) )
		{
			memcpy( &m_strWaveData.dwSubChunkSize, abyData, sizeof(m_strWaveData.dwSubChunkSize) );
		}

		abyData += sizeof(m_strWaveData.dwSubChunkSize);
		dwRet += sizeof(m_strWaveData.dwSubChunkID);
		dwBytes -= sizeof(m_strWaveData.dwSubChunkID);

		if( m_strWaveData.dwSubChunkSize > 0 )
		{
			m_strWaveData.abyData = new BYTE[m_strWaveData.dwSubChunkSize];

			if( !m_strWaveData.abyData )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( m_strWaveData.abyData, 0, m_strWaveData.dwSubChunkSize );

			if( (dwBytes >= m_strWaveData.dwSubChunkSize) )
			{
				memcpy( m_strWaveData.abyData, abyData, m_strWaveData.dwSubChunkSize );

				dwRet += m_strWaveData.dwSubChunkSize ;
				dwBytes -= m_strWaveData.dwSubChunkSize;
				abyData += m_strWaveData.dwSubChunkSize;
			}
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveDataChunk::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		_Clear();

		ULONG ulRead = 0;

		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_strWaveData.dwSubChunkID, 
								sizeof(m_strWaveData.dwSubChunkID),
								&ulRead );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		dwRet += ulRead;

		hr = pStrm->Read( (BYTE*) &m_strWaveData.dwSubChunkSize, 
							sizeof(m_strWaveData.dwSubChunkSize),
							&ulRead );

		dwRet += ulRead;

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
		
		if( m_strWaveData.dwSubChunkSize > 0 )
		{
			m_strWaveData.abyData = new BYTE[m_strWaveData.dwSubChunkSize];

			if( !m_strWaveData.abyData )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( m_strWaveData.abyData, 0, m_strWaveData.dwSubChunkSize );

			hr = pStrm->Read( m_strWaveData.abyData, m_strWaveData.dwSubChunkSize, &ulRead );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			dwRet += ulRead;
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveDataChunk::GetData( BYTE*& abyData ) const
{
	DWORD dwRet = 0;

	DWORD dwBytes = GetDataSize();

	if( dwBytes > 0 )
	{
		abyData = new BYTE[ dwBytes ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyData, 0, dwBytes );

		memcpy( abyData, m_strWaveData.abyData, dwBytes );

		dwRet = dwBytes;
	}

	return dwRet;
}

CEMSWaveDataChunk&
CEMSWaveDataChunk::operator=( const CEMSWaveDataChunk& coRHS )
{
	if( this != &coRHS )
	{
		if( m_strWaveData.abyData )
		{
			delete[] m_strWaveData.abyData;
			m_strWaveData.abyData = 0;
		}

		memcpy( &m_strWaveData.dwSubChunkID, ms_cszDefaultID,
				(strlen(ms_cszDefaultID) > sizeof(m_strWaveData.dwSubChunkID)) ? sizeof(m_strWaveData.dwSubChunkID) : strlen(ms_cszDefaultID) );

		m_strWaveData.dwSubChunkSize = 0;

		Write( coRHS.m_strWaveData.abyData, coRHS.m_strWaveData.dwSubChunkSize );
	}

	return *this;
}

void 
CEMSWaveDataChunk::_Clear()
{
	if( m_strWaveData.abyData )
	{
		delete[] m_strWaveData.abyData;
	}

	memset( &m_strWaveData, 0, sizeof( EMSWAVEDATACHUNK ) );
}
