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

#ifndef __WAVEEX_H__
#define __WAVEEX_H__

#include "stdwave.h"
#include "waveextchunk.h"

//! EMS extension to the WAVE chunk.  The extension includes an additional
//! chunk containing special fields.
class CEMSWaveEx : public CEMSStdWave
{
	public:
		CEMSWaveEx();
		CEMSWaveEx( const CEMSWaveEx& x );
		virtual ~CEMSWaveEx();

		//! Serialize the entire extended WAVE into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData );

		//! Serialize the entire extended WAVE to the stream pointer specified.
		virtual DWORD Serialize( IEMSSeqStream* pStrm );

		//! Build the extended wave object model from the input byte array.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Build the extended wave object model from the input data stream.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		//! Set the contents of the extended data chunk.
//		void SetExtendedInfo( const EMSWAVEEXTCHUNK& cstrInfoEx ) { m_oExt.Set( cstrInfoEx ); }

		//! Set an extended data chunk.
		void SetExtendedInfo( const CEMSWaveExtChunk& coExt ) { m_oExt = coExt; _SetHeader(); }

		//! Retrieve the contents of the extended data chunk.
		CEMSWaveExtChunk GetExtendedInfo() const { return m_oExt; }

		//! Get a reference to the extended information.
		CEMSWaveExtChunk& GetExtendedInfoRef() { _SetHeader(); return m_oExt; }

	protected:
		virtual DWORD _GetMemberChunksSize();

	protected:
		CEMSWaveExtChunk	m_oExt;
	
};

#endif