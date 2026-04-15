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

#ifndef __WAVE_EXT_CHUNK_H__
#define __WAVE_EXT_CHUNK_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "wave/waveextlutdetails.h"
#include "wave/waveextsatdetails.h"
#include "wave/waveextsignaldetails.h"
#include "wave/waveextsubbandsdetails.h"
#include "wave/waveextproperties.h"
#include "emspipe.h"

//! The EMS extension sub-chunk of a WAVE chunk.  It is used to carry
//! EMS specific information.
class CEMSWaveExtChunk : public CApiObjBase
{
	public:
		CEMSWaveExtChunk();
		CEMSWaveExtChunk( const CEMSWaveExtChunk& x );
		virtual ~CEMSWaveExtChunk();
		
		void SetSubChunkID( const DWORD cdwID ) { m_dwSubChunkID = cdwID; }
		DWORD GetSubChunkID() const { return m_dwSubChunkID; }

		void SetSubChunkSize( const DWORD cdwSize ) { m_dwSubChunkSize = cdwSize; }
		DWORD GetSubChunkSize() const { return m_dwSubChunkSize; }

		CEMSWaveExtLutDetails GetLutDetails() const { return m_oLutDetails; }
		//! Returns a reference to the member LUT Details.
		CEMSWaveExtLutDetails& GetLutDetailsRef() { return m_oLutDetails; }
		void SetLutDetails( const CEMSWaveExtLutDetails& oLutDetails );
		

		CEMSWaveExtSatDetails GetSatDetails() const { return m_oSatDetails; }
		//! Returns a reference to the member Sat Details.
		CEMSWaveExtSatDetails& GetSatDetailsRef() { return m_oSatDetails; }
		void SetSatDetails( const CEMSWaveExtSatDetails& oSatDetails );
		
		
		CEMSWaveExtSignalDetails GetSignalDetails() const { return m_oSignalDetails; }
		//! Returns a reference to the member Sat Details.
		CEMSWaveExtSignalDetails& GetSignalDetailsRef() { return m_oSignalDetails; }
		void SetSignalDetails( const CEMSWaveExtSignalDetails& coDetails );

		CEMSWaveExtSubBandsDetails GetSubBandDetails() const { return m_oSubBandsDetails; }
		CEMSWaveExtSubBandsDetails& GetSubBandDetailsRef() { return m_oSubBandsDetails; }
		void SetSubBandsDetails( const CEMSWaveExtSubBandsDetails& coDetails );

		CEMSWaveExtProperties GetProperties() const { return m_oProperties; }
		CEMSWaveExtProperties& GetPropertiesRef() { return m_oProperties; }
		void SetProperties( const CEMSWaveExtProperties& coProps );

//		void Set( const EMSWAVEEXTCHUNK& cstrExtChunk ) { m_strWaveExt = cstrExtChunk; }
//		EMSWAVEEXTCHUNK Get() const { return m_strWaveExt; }

		//! Serialize the entire extended chunk into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData );

		//! Serialize the entire extended chunk to the stream pointer specified.
		virtual DWORD Serialize( IEMSSeqStream* pStrm );

		//! Build the extended chunk object model from the input byte array.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Build the extended chunk object model from the input data stream.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		DWORD GetSize();

	private:
		DWORD m_dwSubChunkID;
		DWORD m_dwSubChunkSize;
		
		CEMSWaveExtLutDetails m_oLutDetails;
		CEMSWaveExtSatDetails m_oSatDetails;
		CEMSWaveExtSignalDetails m_oSignalDetails;
		CEMSWaveExtSubBandsDetails m_oSubBandsDetails;
		CEMSWaveExtProperties m_oProperties;

	private:	// constants
		static const char* ms_cszDefaultID;
};

#endif