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

#include "wave/stdwave.h"
#include "emsexcpt.h"
#include <crtdbg.h>

const char* CEMSStdWave::ms_cszWaveFormat = "WAVE";

CEMSStdWave::CEMSStdWave()
{
	_SetHeader();
}

CEMSStdWave::CEMSStdWave( const CEMSStdWave& x ) : 
									CEMSStdRIFF( x ), m_oFmt( x.m_oFmt ), m_oData( x.m_oData )
{
}

CEMSStdWave::~CEMSStdWave()
{
}

DWORD 
CEMSStdWave::Write( const BYTE* cabyData, const DWORD cdwBytes )
{
	DWORD dwRet = m_oData.Write( cabyData, cdwBytes );

	// Update the header.
	_SetHeader();

	return dwRet;

}

DWORD 
CEMSStdWave::Read( BYTE* abyData, const DWORD cdwBytes ) const
{
	return m_oData.Read( abyData, cdwBytes );
}

DWORD
CEMSStdWave::Serialize( BYTE*& abyData ) const
{

	DWORD dwSize = m_oHdr.GetSize() + m_oFmt.GetSize() + m_oData.GetSize();

	if( dwSize > 0 )
	{
		abyData = new BYTE[dwSize];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyData, 0, dwSize );

		BYTE* pbyData = abyData;

		_ASSERTE( dwSize >= m_oHdr.GetSize() );
		if( dwSize < m_oHdr.GetSize() )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		memcpy( pbyData, &(m_oHdr.Get()), m_oHdr.GetSize() );

		pbyData += m_oHdr.GetSize();
		_ASSERTE( ( dwSize - m_oHdr.GetSize() ) >= m_oFmt.GetSize() );
		if( ( dwSize - m_oHdr.GetSize() ) < m_oFmt.GetSize() )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		memcpy( pbyData, &(m_oFmt.Get()), m_oFmt.GetSize() );

		pbyData += m_oFmt.GetSize();
		DWORD dwDataBytesToRead = m_oData.GetSize();
		if( dwDataBytesToRead > 0 )
		{
			BYTE* abyTemp = 0;

			DWORD dwBytes = m_oData.Serialize( abyTemp );

			if( abyTemp && (dwBytes > 0) )
			{
				// Calculate room left in buffer.
				DWORD dwRemainingBytes = dwSize - (pbyData - abyData);

				_ASSERTE( dwBytes <= dwRemainingBytes );

				if( dwBytes > dwRemainingBytes )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}

				memcpy( pbyData, abyTemp, dwBytes );

				delete[] abyTemp;
				abyTemp = 0;
			}
		}

	}

	return dwSize;
}

DWORD 
CEMSStdWave::Serialize( IEMSSeqStream* pStrm ) const
{
	DWORD dwSize = 0;

	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	ULONG ulWritten = 0;

	EMS_RESULT hr = pStrm->Write( (const BYTE*) &(m_oHdr.Get()), m_oHdr.GetSize(), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	dwSize += ulWritten;

	hr = pStrm->Write( (const BYTE*) &(m_oFmt.Get()), m_oFmt.GetSize(), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}

	dwSize += ulWritten;

	dwSize += m_oData.Serialize( pStrm );

	return dwSize;
}

DWORD 
CEMSStdWave::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData && (dwBytes > 0) )
	{
		// Pull out the header.

		EMSWAVERIFFHEADER hdrRiff;
		memset( &hdrRiff, 0, sizeof(EMSWAVERIFFHEADER) );

		if( dwBytes >= sizeof(EMSWAVERIFFHEADER)  )
		{
			memcpy( &hdrRiff, abyData, sizeof(EMSWAVERIFFHEADER) );
		}

		m_oHdr.Set( hdrRiff );

		abyData += sizeof(EMSWAVERIFFHEADER);
		dwRet += sizeof(EMSWAVERIFFHEADER);
		dwBytes -= sizeof(EMSWAVERIFFHEADER);

		// Pull out the format chunk.
		EMSWAVEFMTCHUNK fmtChunk;
		memset( &fmtChunk, 0, sizeof(EMSWAVEFMTCHUNK) );

		if( dwBytes  >= sizeof(EMSWAVEFMTCHUNK)  )
		{
			memcpy( &fmtChunk, abyData, sizeof(EMSWAVEFMTCHUNK) );
		}

		m_oFmt.Set( fmtChunk );

		abyData += sizeof(EMSWAVEFMTCHUNK);
		dwRet += sizeof(EMSWAVEFMTCHUNK);
		dwBytes -= sizeof(EMSWAVEFMTCHUNK);

		// Pull out the data chunk.
		dwRet += m_oData.Deserialize( abyData, dwBytes );
	}

	_SetHeader();

	return dwRet;
}

DWORD 
CEMSStdWave::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		// Pull out the header.
		EMSWAVERIFFHEADER hdrRiff;
		memset( &hdrRiff, 0, sizeof(EMSWAVERIFFHEADER) );

		ULONG ulRead = 0;
		EMS_RESULT hr = pStrm->Read( (BYTE*) &hdrRiff, sizeof(EMSWAVERIFFHEADER), &ulRead );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		dwRet += ulRead;

		m_oHdr.Set( hdrRiff );

		// Pull out the format chunk.
		EMSWAVEFMTCHUNK fmtChunk;
		memset( &fmtChunk, 0, sizeof(EMSWAVEFMTCHUNK) );

		hr = pStrm->Read( (BYTE*) &fmtChunk, sizeof(EMSWAVEFMTCHUNK), &ulRead );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		dwRet += ulRead;

		m_oFmt.Set( fmtChunk );

		// Pull out the data chunk.
		dwRet += m_oData.Deserialize( pStrm );
	}

	_SetHeader();

	return dwRet;
}

void 
CEMSStdWave::_SetHeader()
{
	DWORD dwFormat = 0;

	memcpy( &dwFormat, ms_cszWaveFormat, 
		(strlen(ms_cszWaveFormat) > sizeof(dwFormat)) ? sizeof(dwFormat) : strlen(ms_cszWaveFormat) );

	m_oHdr.SetFormat( dwFormat );
	m_oHdr.SetMemberChunksSize( _GetMemberChunksSize() );
}

DWORD
CEMSStdWave::_GetMemberChunksSize()
{
	return m_oFmt.GetSize() + m_oData.GetSize();
}