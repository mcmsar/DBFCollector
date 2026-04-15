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

#include "wave/waveextsubbandsdetails.h"
#include "emsexcpt.h"
#include "arrayhelper.h"

CEMSWaveExtSubBandsDetails::CEMSWaveExtSubBandsDetails() : m_dwFlags(0)
{
}

CEMSWaveExtSubBandsDetails::CEMSWaveExtSubBandsDetails( const CEMSWaveExtSubBandsDetails& x ) : 
									m_olstSubBands(x.m_olstSubBands), m_dwFlags(x.m_dwFlags)
{
}

CEMSWaveExtSubBandsDetails::~CEMSWaveExtSubBandsDetails()
{
}

DWORD 
CEMSWaveExtSubBandsDetails::GetSize()
{
	DWORD dwRet = 0;

	// Count each one.  Alternatively, could assume same size for each
	// and just to a calculation.  Calculating each provides flexibility
	// in case the sub band data becomes variable size.
	
	m_olstSubBands.MoveFirst();

	for( ULONG l = 0; l < m_olstSubBands.Count(); l++ )
	{
		CEMSWaveExtSubBandDetails oDetail = m_olstSubBands.GetNext();

		dwRet += oDetail.GetSize();
	}

	dwRet += sizeof(m_dwFlags) + sizeof(WORD);

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandsDetails::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	BYTE* abyTemp = 0;
	DWORD dwTempSize = 0;

	try
	{
		// Serializing as EMSWAVEEXSUBBANDS.

		dwRet = sizeof(m_dwFlags) + sizeof(WORD);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		WORD wNumSubBands = (unsigned short) m_olstSubBands.Count();
		
		memcpy( abyData, &wNumSubBands, sizeof(wNumSubBands) );

		memcpy( abyData + sizeof(wNumSubBands), &m_dwFlags, sizeof(m_dwFlags) );

		m_olstSubBands.MoveFirst();

		for( ULONG l = 0; l < m_olstSubBands.Count(); l++ )
		{
			CEMSWaveExtSubBandDetails oSubBand = m_olstSubBands.GetNext();

			dwTempSize = oSubBand.Serialize( abyTemp );

			CEMSArrayHelper::Concatenate( abyData, dwRet, abyTemp, dwTempSize );

			if( abyTemp )
			{
				delete[] abyTemp;
				abyTemp = 0;
			}

		}

	}
	catch( ... )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		if( abyTemp )
		{
			delete[] abyTemp;
			abyTemp = 0;
		}

		throw;
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandsDetails::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		WORD wNumSubBands = (unsigned short) m_olstSubBands.Count();

		DWORD dwWritten = 0;
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &wNumSubBands, sizeof(wNumSubBands), &dwWritten );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		dwRet += dwWritten;

		dwWritten = 0;
		hr = pStrm->Write( (const BYTE*) &m_dwFlags, sizeof(m_dwFlags), &dwWritten );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		dwRet += dwWritten;

		m_olstSubBands.MoveFirst();

		for( ULONG l = 0; l < m_olstSubBands.Count(); l++ )
		{
			CEMSWaveExtSubBandDetails oSubBand = m_olstSubBands.GetNext();
			dwRet += oSubBand.Serialize( pStrm );
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandsDetails::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		// We don't actually save this value, but it's useful for reading.
		WORD wNumSubBands = 0;

		if( dwBytes >= sizeof(wNumSubBands) )
		{
			dwRet = sizeof(wNumSubBands);

			memcpy( &wNumSubBands, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

		if( dwBytes >= sizeof( m_dwFlags ) )
		{
			dwRet = sizeof(m_dwFlags);

			memcpy( &m_dwFlags, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

		for( WORD w = 0; w < wNumSubBands; w++ )
		{
			CEMSWaveExtSubBandDetails oSubBand;
			dwRet += oSubBand.Deserialize( abyData, dwBytes );
			m_olstSubBands.Add( oSubBand );
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandsDetails::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		DWORD dwRead = 0;
		WORD wNumSubBands = 0;
		EMS_RESULT hr = pStrm->Read( (BYTE*) &wNumSubBands, sizeof(wNumSubBands), &dwRead );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
		
		dwRet += dwRead;

		dwRead = 0;
		hr = pStrm->Read( (BYTE*) &m_dwFlags, sizeof(m_dwFlags), &dwRead );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
		
		dwRet += dwRead;

		for( WORD w = 0; w < wNumSubBands; w++ )
		{
			CEMSWaveExtSubBandDetails oSubBand;
			dwRet += oSubBand.Deserialize( pStrm );
			m_olstSubBands.Add( oSubBand );
		}

	}

	return dwRet;
}