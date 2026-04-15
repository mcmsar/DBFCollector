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

#include "wave/waveextlutdetails.h"

CEMSWaveExtLutDetails::CEMSWaveExtLutDetails()
{
	memset( &m_lutDetails, 0, sizeof(m_lutDetails) );
}

CEMSWaveExtLutDetails::CEMSWaveExtLutDetails( const CEMSWaveExtLutDetails& x ) : m_lutDetails( x.m_lutDetails )
{
}

CEMSWaveExtLutDetails::~CEMSWaveExtLutDetails()
{
}

DWORD 
CEMSWaveExtLutDetails::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	try
	{
		dwRet = sizeof(m_lutDetails);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( abyData, &m_lutDetails, sizeof(m_lutDetails) );
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
CEMSWaveExtLutDetails::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_lutDetails, sizeof(m_lutDetails), &dwRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtLutDetails::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		if( dwBytes >= sizeof(m_lutDetails) )
		{
			dwRet = sizeof(m_lutDetails);

			memcpy( &m_lutDetails, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtLutDetails::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_lutDetails, sizeof(m_lutDetails), &dwRet );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}

	return dwRet;
}