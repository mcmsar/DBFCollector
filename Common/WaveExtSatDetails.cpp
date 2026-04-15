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

#include "wave/waveextsatdetails.h"
#include "emsexcpt.h"

CEMSWaveExtSatDetails::CEMSWaveExtSatDetails()
{
	memset( &m_satDetails, 0, sizeof(m_satDetails) );
}

CEMSWaveExtSatDetails::CEMSWaveExtSatDetails( const CEMSWaveExtSatDetails& x ) : m_satDetails( x.m_satDetails )
{
}

CEMSWaveExtSatDetails::~CEMSWaveExtSatDetails()
{
}

DWORD 
CEMSWaveExtSatDetails::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	try
	{
		dwRet = sizeof(m_satDetails);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( abyData, &m_satDetails, sizeof(m_satDetails) );
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
CEMSWaveExtSatDetails::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_satDetails, sizeof(m_satDetails), &dwRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSatDetails::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		if( dwBytes >= sizeof(m_satDetails) )
		{
			dwRet = sizeof(m_satDetails);

			memcpy( &m_satDetails, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtSatDetails::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_satDetails, sizeof(m_satDetails), &dwRet );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}

	return dwRet;
}