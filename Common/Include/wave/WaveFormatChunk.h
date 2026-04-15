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

#ifndef __WAVE_FORMAT_CHUNK_H__
#define __WAVE_FORMAT_CHUNK_H__

#include "emswavechunk.h"
#include "aobjbase.h"

//! The format sub-chunk of a RIFF chunk.
class CEMSWaveFormatChunk : public CApiObjBase
{
	public:
		CEMSWaveFormatChunk();
		CEMSWaveFormatChunk( const CEMSWaveFormatChunk& x );
		virtual ~CEMSWaveFormatChunk();
		
		void SetSubChunkID( const DWORD cdwID ) { m_strWaveFormat.dwSubChunkID = cdwID; }

		DWORD GetSubChunkID() const { return m_strWaveFormat.dwSubChunkID; }

		void SetSubChunkSize( const DWORD cdwSize ) { m_strWaveFormat.dwSubChunkSize = cdwSize; }

		DWORD GetSubChunkSize() const { return m_strWaveFormat.dwSubChunkSize; }

		void SetAudioFormat( const WORD cwFmt ) { m_strWaveFormat.wAudioFormat = cwFmt; }

		WORD GetAudioFormat() const { return m_strWaveFormat.wAudioFormat; }

		void SetNumChannels( const WORD cwNumChannels );

		WORD GetNumChannels() const { return m_strWaveFormat.wNumChannels; }

		void SetSampleRate( const DWORD cdwRate );

		DWORD GetSampleRate() const { return m_strWaveFormat.dwSampleRate; }

		void SetByteRate( const DWORD cdwByteRate ) { m_strWaveFormat.dwByteRate = cdwByteRate; }

		DWORD GetByteRate() const { return m_strWaveFormat.dwByteRate; }

		void SetBlockAlign( const WORD cwBlockAlign ) { m_strWaveFormat.wBlockAlign = cwBlockAlign; }

		DWORD GetBlockAlign() const { return m_strWaveFormat.wBlockAlign; }

		void SetBitsPerSample( const WORD cwBps );

		WORD GetBitsPerSample() const { return m_strWaveFormat.wBitsPerSample; }

		void Set( const EMSWAVEFMTCHUNK& cstrFmtChunk ) { m_strWaveFormat = cstrFmtChunk; }

		EMSWAVEFMTCHUNK Get() const { return m_strWaveFormat; }

		DWORD GetSize() const { return sizeof(m_strWaveFormat); }

	private:
		void _Recalculate();
		void _CalculateByteRate();
		void _CalculateBlockAlignment();

	private:
		EMSWAVEFMTCHUNK	m_strWaveFormat;

	private:	// constants
		static const char* ms_cszDefaultID;
		static const DWORD ms_cdwPCM;
		static const WORD ms_cwMONO;
};

#endif