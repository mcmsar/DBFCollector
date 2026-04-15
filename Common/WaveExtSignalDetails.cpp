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

#include "wave/waveextsignaldetails.h"
#include "emsexcpt.h"

const DWORD CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT = 0x0;
const DWORD CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_GOOD_MARKER_BIT = 0x1;

CEMSWaveExtSignalDetails::CEMSWaveExtSignalDetails()
{
	memset( &m_signalDetails, 0, sizeof(m_signalDetails) );
}

CEMSWaveExtSignalDetails::CEMSWaveExtSignalDetails( const CEMSWaveExtSignalDetails& x ) : 
								m_signalDetails( x.m_signalDetails )
{
}

CEMSWaveExtSignalDetails::~CEMSWaveExtSignalDetails()
{
}

std::wstring 
CEMSWaveExtSignalDetails::GetPhaseModStateString() const
{
	std::wstring owszRet;

	switch( m_signalDetails.statePhaseMod )
	{
		case EMS_PHASE_MOD_YES:
			owszRet = gs_cwszPhaseModYes;
			break;
		case EMS_PHASE_MOD_NO:
			owszRet = gs_cwszPhaseModNo;
			break;
		default:
			owszRet = gs_cwszPhaseModUnknown;
			break;
	}

	return owszRet;
}

std::wstring 
CEMSWaveExtSignalDetails::GetDCStateString() const
{
	std::wstring owszRet;

	switch( m_signalDetails.stateDC )
	{
		case EMS_DC_YES:
			owszRet = gs_cwszDCYes;
			break;
		case EMS_DC_NO:
			owszRet = gs_cwszDCNo;
			break;
		default:
			owszRet = gs_cwszPhaseModUnknown;
			break;
	}

	return owszRet;
}

DWORD 
CEMSWaveExtSignalDetails::Serialize( BYTE*& abyData )
{
	DWORD dwRet = 0;

	try
	{
		dwRet = sizeof(m_signalDetails);

		abyData = new BYTE[ dwRet ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( abyData, &m_signalDetails, sizeof(m_signalDetails) );
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
CEMSWaveExtSignalDetails::Serialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Write( (const BYTE*) &m_signalDetails, sizeof(m_signalDetails), &dwRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	return dwRet;
}

DWORD 
CEMSWaveExtSignalDetails::Deserialize( BYTE*& abyData, DWORD& dwBytes )
{
	DWORD dwRet = 0;

	if( abyData )
	{
		if( dwBytes >= sizeof(m_signalDetails) )
		{
			dwRet = sizeof(m_signalDetails);

			memcpy( &m_signalDetails, abyData, dwRet );

			dwBytes -= dwRet;
			abyData += dwRet;
		}

	}

	return dwRet;
}

DWORD 
CEMSWaveExtSignalDetails::Deserialize( IEMSSeqStream* pStrm )
{
	DWORD dwRet = 0;

	if( pStrm )
	{
		EMS_RESULT hr = pStrm->Read( (BYTE*) &m_signalDetails, sizeof(m_signalDetails), &dwRet );
		
		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}

	return dwRet;
}