/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
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

#include "LPDTools.h"
#include "emsexcpt.h"
#include <math.h>
#include <crtdbg.h>
#include <stdio.h>
#include "convutility.h"

CEMSLPDTools::CEMSLPDTools() : m_bWaveformInit(false)
{
	memset( &m_keyEncrypt, 0, sizeof(m_keyEncrypt) );
}

CEMSLPDTools::CEMSLPDTools( const CEMSLPDTools& x ) : m_bWaveformInit(x.m_bWaveformInit), 
													m_omapWaveforms(x.m_omapWaveforms),
													m_keyEncrypt( x.m_keyEncrypt ),
													m_owszFilename( x.m_owszFilename )
{
}

CEMSLPDTools::~CEMSLPDTools()
{
}

EMS_RESULT
CEMSLPDTools::GetFrameSynch ( const long clId, long* calFS ) 
{

	EMS_RESULT hr = EMS_FALSE;

	_InitWaveforms();

	if ( clId >= 0 )
	{
		INT64 i64FS = m_omapWaveforms[clId];

		int nBits = 4* NHEXLPD;
		int nIndex = nBits;

		for ( int i = 0; i < nBits; i++ )
		{
			nIndex--;
			calFS[nIndex] = i64FS & 1;
			
			if ( calFS[nIndex] == 0 )
				calFS[nIndex] = -1;

			i64FS = i64FS >> 1;

		}

		hr = EMS_OK;
	}

	return hr;
}

void
CEMSLPDTools::Init( const MLB1000WaveformManager::EncryptionKey ckeyEncrypt, 
					const wchar_t* cwszFilename )
{
	m_keyEncrypt = ckeyEncrypt;

	if( cwszFilename )
		m_owszFilename = cwszFilename;

	_InitWaveforms();
}

void 
CEMSLPDTools::_InitWaveforms()
{
	if( !m_bWaveformInit )
	{
		if( !m_owszFilename.empty() )
		{

			HRESULT hr = MLB1000WaveformManager::GetAllWaveforms( m_keyEncrypt, 
#ifdef UNICODE
				m_owszFilename.c_str(), 
#else
				CEMSConversionUtil::ConvertToString( m_owszFilename.c_str() ).c_str(),
#endif
				m_omapWaveforms );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

		m_bWaveformInit = true;
	}
}

