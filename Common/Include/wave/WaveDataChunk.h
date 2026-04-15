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

#ifndef __WAVE_DATA_CHUNK_H__
#define __WAVE_DATA_CHUNK_H__

#include "emswavechunk.h"
#include "aobjbase.h"
#include "emspipe.h"

//! The data sub-chunk of a RIFF chunk.
class CEMSWaveDataChunk : public CApiObjBase
{
	public:
		CEMSWaveDataChunk();
		CEMSWaveDataChunk( const CEMSWaveDataChunk& x );
		virtual ~CEMSWaveDataChunk();

		//! Write data to the chunk.  The chunk is fixed size and the number of
		//! bytes actually written is returned.
		DWORD Write( const BYTE* cabyData, const DWORD cdwBytesInput );

		//! Read data from the chunk.  The actual number of bytes read is returned.
		DWORD Read( BYTE* abyData, const DWORD cdwMaxToRead ) const;

		//! Get the size of the data portion of the chunk.
		DWORD GetDataSize() const { return m_strWaveData.dwSubChunkSize; }

		//! Get the size of the entire chunk.
		DWORD GetSize() const { return (sizeof(m_strWaveData.dwSubChunkID) + sizeof(m_strWaveData.dwSubChunkSize) + m_strWaveData.dwSubChunkSize); }

		//! Get the contents of the data chunk.
		//EMSWAVEDATACHUNK Get() const { return m_strWaveData; }

		//! Serialize the entire chunk.  The caller must release the returned array.
		DWORD Serialize( BYTE*& abyData ) const;

		//! Serialize the entire chunk to the given stream.
		DWORD Serialize( IEMSSeqStream* pStrm ) const;

		//! Use the provided chunk of data to fill the Wave Data Chunk object model.
		//! Returns the number of bytes read from the stream.
		DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Use the provided chunk of data to fill the Wave Data Chunk object model.
		//! Returns the number of bytes read from the stream.
		DWORD Deserialize( IEMSSeqStream* pStrm );

		//! Get the data chunk's identitifer.
		DWORD GetSubChunkID() const { return m_strWaveData.dwSubChunkID; }

		//! Return an array of bytes containing the data portion of the chunk.  The retur value is
		//! the size of the array.  The caller must delete the returned array.
		DWORD GetData( BYTE*& abyData ) const;

		//! Overloaded assignment operator.  This is necessary because the wave data chunk contains
		//! dynamically allocated memory.
		CEMSWaveDataChunk& operator=( const CEMSWaveDataChunk& coRHS );

	private:
		void _Clear();

	private:
		EMSWAVEDATACHUNK	m_strWaveData;

	private:	// constants
		static const char* ms_cszDefaultID;
};

#endif