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

#include "wave/waveformatchunk.h"
#include <memory.h>
#include <string.h>
#include "emsexcpt.h"

const char* CEMSWaveFormatChunk::ms_cszDefaultID = "fmt ";
const DWORD CEMSWaveFormatChunk::ms_cdwPCM = 1;
const WORD CEMSWaveFormatChunk::ms_cwMONO = 1;

CEMSWaveFormatChunk::CEMSWaveFormatChunk()
{
	memcpy( &m_strWaveFormat.dwSubChunkID, ms_cszDefaultID,
				(strlen(ms_cszDefaultID) > sizeof(m_strWaveFormat.dwSubChunkID)) ? sizeof(m_strWaveFormat.dwSubChunkID) : strlen(ms_cszDefaultID) );

	m_strWaveFormat.dwSubChunkSize = 16;

	m_strWaveFormat.wAudioFormat = ms_cdwPCM;

	m_strWaveFormat.wNumChannels = ms_cwMONO;

	m_strWaveFormat.dwSampleRate = 0;

	m_strWaveFormat.wBitsPerSample = 8;

	_Recalculate();
}

CEMSWaveFormatChunk::CEMSWaveFormatChunk( const CEMSWaveFormatChunk& x )
{
	Set( x.m_strWaveFormat );
}

CEMSWaveFormatChunk::~CEMSWaveFormatChunk()
{
}

void 
CEMSWaveFormatChunk::SetNumChannels( const WORD cwNumChannels ) 
{ 
	m_strWaveFormat.wNumChannels = cwNumChannels; 

	_Recalculate();
}

void 
CEMSWaveFormatChunk::SetSampleRate( const DWORD cdwRate ) 
{ 
	m_strWaveFormat.dwSampleRate = cdwRate; 

	_Recalculate();
}

void 
CEMSWaveFormatChunk::SetBitsPerSample( const WORD cwBps ) 
{ 
	int iMod = cwBps % 8;

	if( 0 != iMod )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	m_strWaveFormat.wBitsPerSample = cwBps; 

	_Recalculate();
}

void 
CEMSWaveFormatChunk::_Recalculate()
{
	_CalculateByteRate();

	_CalculateBlockAlignment();
}

void 
CEMSWaveFormatChunk::_CalculateByteRate()
{
	m_strWaveFormat.dwByteRate = m_strWaveFormat.dwSampleRate*m_strWaveFormat.wNumChannels*m_strWaveFormat.wBitsPerSample/8;
}

void 
CEMSWaveFormatChunk::_CalculateBlockAlignment()
{
	m_strWaveFormat.wBlockAlign = m_strWaveFormat.wNumChannels*m_strWaveFormat.wBitsPerSample/8;
}