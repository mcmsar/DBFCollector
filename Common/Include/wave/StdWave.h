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

#ifndef __STD_WAVE_H__
#define __STD_WAVE_H__

#include "stdriff.h"
#include "waveformatchunk.h"
#include "wavedatachunk.h"

//! A WAVE type RIFF chunk.
class CEMSStdWave : public CEMSStdRIFF
{
	public:
		CEMSStdWave();
		CEMSStdWave( const CEMSStdWave& x );
		virtual ~CEMSStdWave();
		
		//! Write data into the WAVE's data chunk.
		virtual DWORD Write( const BYTE* cabyData, const DWORD cdwBytes );

		//! Read data from the RIFF's data chunk.
		virtual DWORD Read( BYTE* abyData, const DWORD cdwBytes ) const;
		
		//! Serialize the entire WAVE into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData ) const;

		//! Serialize the entire RIFF into a stream.
		virtual DWORD Serialize( IEMSSeqStream* pStrm ) const;

		//! Take a stream of bytes comprising a RIFF and extract it into the object model.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Take a stream of bytes comprising a RIFF and extract it into the object model.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		//! Set the data contained in the format chunk.
		void SetFormat( const EMSWAVEFMTCHUNK& cstrFmtChunk ) { m_oFmt.Set( cstrFmtChunk ); _SetHeader(); }

		CEMSWaveFormatChunk GetFormatChunk() const { return m_oFmt; }

		CEMSWaveFormatChunk& GetFormatChunkRef() { return m_oFmt; }

		//! Get the data chunk.  Note that use of this method may cause a stack overflow when compiled
		//! under default MS VC++ 6.0 settings.  This is dependent upon the size defined for the fixed buffer.
		CEMSWaveDataChunk GetDataChunk() const { return m_oData; }

		CEMSWaveDataChunk& GetDataChunkRef() { return m_oData; }

		//! Get the entire RIFF.  Note that use of this method may cause a stack overflow when compiled
		//! under default MS VC++ 6.0 settings.  Use the Serialize() method instead or increase the
		//! stack size to work around.
		//EMSSTDWAVERIFF Get() const;

		DWORD GetDataSize() const { return m_oData.GetDataSize(); }

	protected:
		//! Set the fields in the RIFF header.
		virtual void _SetHeader();

		virtual DWORD _GetMemberChunksSize();

	protected:
		CEMSWaveFormatChunk		m_oFmt;
		CEMSWaveDataChunk		m_oData;

	private:
		static const char* ms_cszWaveFormat;
};

#endif