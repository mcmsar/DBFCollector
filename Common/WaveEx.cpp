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

#include "wave/waveex.h"
#include "emsexcpt.h"
#include <crtdbg.h>

CEMSWaveEx::CEMSWaveEx()
{
	_SetHeader();
}

CEMSWaveEx::CEMSWaveEx( const CEMSWaveEx& x ) : CEMSStdWave( x ), m_oExt( x.m_oExt )
{
}

CEMSWaveEx::~CEMSWaveEx()
{
}

DWORD 
CEMSWaveEx::Serialize( BYTE*& abyData )
{
	BYTE* abyExt = 0;
	BYTE* abyDataTemp = 0;
	DWORD dwRet = 0;

	try
	{
		_SetHeader();

		dwRet = CEMSStdWave::Serialize( abyData );

		DWORD dwExtSize = m_oExt.GetSize();

		if( dwExtSize > 0 )
		{
			DWORD dwCombinedSize = dwRet + dwExtSize;

			abyDataTemp = new BYTE[ dwCombinedSize ];

			if( !abyDataTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( abyDataTemp, 0, dwCombinedSize );
			memcpy( abyDataTemp, abyData, dwRet );

			DWORD dwExtSerSize = m_oExt.Serialize( abyExt );

			if( dwExtSize != dwExtSerSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
			}

			_ASSERTE( (dwCombinedSize - dwRet) <= dwExtSerSize );
			if( (dwCombinedSize - dwRet) > dwExtSerSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			memcpy( abyDataTemp + dwRet, abyExt, dwExtSerSize );

			if( abyData )
			{
				delete[] abyData;
				abyData = 0;
			}

			if( abyExt )
			{
				delete[] abyExt;
				abyExt = 0;
			}

			abyData = abyDataTemp;
			dwRet = dwCombinedSize;

		}
	}
	catch( ... )
	{
		if( abyDataTemp )
		{
			delete[] abyDataTemp;
			abyDataTemp = 0;
		}

		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		if( abyExt )
		{
			delete[] abyExt;
			abyExt = 0;
		}

		throw;
	}

	return dwRet;
}

DWORD 
CEMSWaveEx::Serialize( IEMSSeqStream* pStrm )
{
	_SetHeader();

	DWORD dwRet = CEMSStdWave::Serialize( pStrm );
	dwRet += m_oExt.Serialize( pStrm );

	return dwRet;
}

DWORD 
CEMSWaveEx::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = CEMSStdWave::Deserialize( abyData, dwBytes );
	dwRet += m_oExt.Deserialize( abyData, dwBytes );

	_SetHeader();

	return dwRet;

}

DWORD
CEMSWaveEx::Deserialize( IEMSSeqStream* pStrm )
{
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	DWORD dwRet = CEMSStdWave::Deserialize( pStrm );
	dwRet += m_oExt.Deserialize( pStrm );

	_SetHeader();

	return dwRet;
}

DWORD 
CEMSWaveEx::_GetMemberChunksSize()
{
	return m_oExt.GetSize() + CEMSStdWave::_GetMemberChunksSize();
}