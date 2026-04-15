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

#include "wave/waveextsubbanddetails.h"
#include "emsexcpt.h"

CEMSWaveExtSubBandDetails::CEMSWaveExtSubBandDetails()
{
	memset( &m_subBand, 0, sizeof(m_subBand) );
}

CEMSWaveExtSubBandDetails::CEMSWaveExtSubBandDetails( const CEMSWaveExtSubBandDetails& x ) : m_subBand( x.m_subBand )
{
}

CEMSWaveExtSubBandDetails::CEMSWaveExtSubBandDetails( const EMSWAVEEXSUBBAND& x ) : m_subBand( x )
{
}

CEMSWaveExtSubBandDetails::~CEMSWaveExtSubBandDetails()
{
}

DWORD 
CEMSWaveExtSubBandDetails::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	try
	{
		dwRet = sizeof(m_subBand);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( abyData, &m_subBand, sizeof(m_subBand) );
	}
	catch( ... )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		throw;
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandDetails::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_subBand, sizeof(m_subBand), &dwRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandDetails::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		if( dwBytes >= sizeof(m_subBand) )
		{
			dwRet = sizeof(m_subBand);

			memcpy( &m_subBand, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtSubBandDetails::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_subBand, sizeof(m_subBand), &dwRet );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}

	return dwRet;
}