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

#include "wave/waveextproperties.h"
#include "emsexcpt.h"

CEMSWaveExtProperties::CEMSWaveExtProperties()
{
	memset( &m_Props, 0, sizeof(m_Props) );
}

CEMSWaveExtProperties::CEMSWaveExtProperties( const CEMSWaveExtProperties& x ) : m_Props( x.m_Props )
{
}

CEMSWaveExtProperties::~CEMSWaveExtProperties()
{
}

DWORD 
CEMSWaveExtProperties::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	try
	{
		dwRet = sizeof(m_Props);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( abyData, &m_Props, sizeof(m_Props) );
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
CEMSWaveExtProperties::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_Props, sizeof(m_Props), &dwRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtProperties::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		if( dwBytes >= sizeof(m_Props) )
		{
			dwRet = sizeof(m_Props);

			memcpy( &m_Props, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtProperties::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_Props, sizeof(m_Props), &dwRet );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}

	return dwRet;
}