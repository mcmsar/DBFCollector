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
#pragma warning(disable:4786)

#include "wave/waveextchunk.h"
#include "emsexcpt.h"
#include "arrayhelper.h"
#include <memory.h>
#include <string.h>

const char* CEMSWaveExtChunk::ms_cszDefaultID = "emsx";

CEMSWaveExtChunk::CEMSWaveExtChunk() : m_dwSubChunkID(0), m_dwSubChunkSize(0)
{
	memcpy( &m_dwSubChunkID, ms_cszDefaultID,
			(strlen(ms_cszDefaultID) > sizeof(m_dwSubChunkID)) ? 
			sizeof(m_dwSubChunkID) : strlen(ms_cszDefaultID) );

	m_dwSubChunkSize = m_oLutDetails.GetSize() + m_oSatDetails.GetSize() + m_oSignalDetails.GetSize() +
						m_oSubBandsDetails.GetSize() + m_oProperties.GetSize();
}

CEMSWaveExtChunk::CEMSWaveExtChunk( const CEMSWaveExtChunk& x ) : m_dwSubChunkID( x.m_dwSubChunkID ),
												m_dwSubChunkSize( x.m_dwSubChunkSize ),
												m_oLutDetails( x.m_oLutDetails ),
												m_oSatDetails( x.m_oSatDetails ),
												m_oSignalDetails( x.m_oSignalDetails ),
												m_oSubBandsDetails( x.m_oSubBandsDetails ),
												m_oProperties( x.m_oProperties )
{
}

CEMSWaveExtChunk::~CEMSWaveExtChunk()
{
}

DWORD 
CEMSWaveExtChunk::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	BYTE* abyDataTemp = 0;

	// Write data into a byte array.  Order is important and is defined by the structure
	// of EMSWAVEEXTCHUNK.

	try
	{
		DWORD dwTempSize = sizeof(m_dwSubChunkID) + sizeof(m_dwSubChunkSize);
		abyDataTemp = new BYTE[ dwTempSize ];

		if( !abyDataTemp )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyDataTemp, 0, dwTempSize );
		memcpy( abyDataTemp, &m_dwSubChunkID, sizeof(m_dwSubChunkID) );
		memcpy( abyDataTemp + sizeof(m_dwSubChunkID), &m_dwSubChunkSize, sizeof(m_dwSubChunkSize) );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;

		dwTempSize = m_oLutDetails.Serialize( abyDataTemp );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;

		dwTempSize = m_oSatDetails.Serialize( abyDataTemp );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;

		dwTempSize = m_oSignalDetails.Serialize( abyDataTemp );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;

		dwTempSize = m_oSubBandsDetails.Serialize( abyDataTemp );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;

		dwTempSize = m_oProperties.Serialize( abyDataTemp );

		CEMSArrayHelper::Concatenate( abyData, dwRet, abyDataTemp, dwTempSize );

		delete[] abyDataTemp;
		abyDataTemp = 0;
		dwTempSize = 0;
	}
	catch( ... )
	{
		throw;
	}

	return dwRet;
}

DWORD 
CEMSWaveExtChunk::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		DWORD dwWritten = 0;

		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_dwSubChunkID, sizeof(m_dwSubChunkID), &dwWritten );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		dwRet += dwWritten;

		dwWritten = 0;
		hr = pStrm->Write( (const BYTE*) &m_dwSubChunkSize, sizeof(m_dwSubChunkSize), &dwWritten );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		dwRet += dwWritten;

		dwRet += m_oLutDetails.Serialize( pStrm );
		dwRet += m_oSatDetails.Serialize( pStrm );
		dwRet += m_oSignalDetails.Serialize( pStrm );
		dwRet += m_oSubBandsDetails.Serialize( pStrm );
		dwRet += m_oProperties.Serialize( pStrm );

	}

	return dwRet;
}

DWORD 
CEMSWaveExtChunk::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData && ( dwBytes > 0 ) )
	{
		if( dwBytes >= sizeof(m_dwSubChunkID) )
		{
			memcpy( &m_dwSubChunkID, abyData, sizeof(m_dwSubChunkID) );
			abyData += sizeof(m_dwSubChunkID);
			dwBytes -= sizeof(m_dwSubChunkID);
			dwRet += sizeof(m_dwSubChunkID);
		}

		if( dwBytes >= sizeof(m_dwSubChunkID) )
		{
			memcpy( &m_dwSubChunkSize, abyData, sizeof(m_dwSubChunkSize) );
			abyData += sizeof(m_dwSubChunkSize);
			dwBytes -= sizeof(m_dwSubChunkSize);
			dwRet += sizeof(m_dwSubChunkSize);
		}

		dwRet += m_oLutDetails.Deserialize( abyData, dwBytes );
		dwRet += m_oSatDetails.Deserialize( abyData, dwBytes );
		dwRet += m_oSignalDetails.Deserialize( abyData, dwBytes );
		dwRet += m_oSubBandsDetails.Deserialize( abyData, dwBytes );
		dwRet += m_oProperties.Deserialize( abyData, dwBytes );

	}

	return dwRet;
}

DWORD 
CEMSWaveExtChunk::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		DWORD dwRead = 0;

		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_dwSubChunkID, sizeof(m_dwSubChunkID), &dwRead );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		dwRet += dwRead;

		hr = pStrm->Read( (BYTE*) &m_dwSubChunkSize, sizeof(m_dwSubChunkSize), &dwRead );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		dwRet += dwRead;

		dwRet += m_oLutDetails.Deserialize( pStrm );
		dwRet += m_oSatDetails.Deserialize( pStrm );
		dwRet += m_oSignalDetails.Deserialize( pStrm );
		dwRet += m_oSubBandsDetails.Deserialize( pStrm );
		dwRet += m_oProperties.Deserialize( pStrm );
		
	}

	return dwRet;
}

DWORD 
CEMSWaveExtChunk::GetSize()
{
	return sizeof(m_dwSubChunkID) + sizeof(m_dwSubChunkSize) + m_oLutDetails.GetSize() +
					m_oSatDetails.GetSize() + m_oSignalDetails.GetSize() + m_oSubBandsDetails.GetSize() +
					m_oProperties.GetSize();


}