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

#ifndef __WAVE_EXT_SUBBANDS_DETAILS_H__
#define __WAVE_EXT_SUBBANDS_DETAILS_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "wave/waveextsubbanddetails.h"
#include "objectlist.h"

//! Maintains information about a set of sub bands.
class CEMSWaveExtSubBandsDetails : public CApiObjBase
{
	public:
		CEMSWaveExtSubBandsDetails();
		CEMSWaveExtSubBandsDetails( const CEMSWaveExtSubBandsDetails& x );
		virtual ~CEMSWaveExtSubBandsDetails();

		//! Get the number of sub-bands.
		WORD GetNumber() { return (unsigned short) m_olstSubBands.Count(); }

		void SetFlags( const DWORD cdwValue ) {m_dwFlags = cdwValue; }
		DWORD GetFlags() const { return m_dwFlags; }

		void AddSubBand( const CEMSWaveExtSubBandDetails& coSubBand );
		CEMSObjectList<CEMSWaveExtSubBandDetails> GetSubBands() const;

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

		//! Return the size in bytes of all contained data when serialized to a byte array.
		DWORD GetSize();
		
	private:
		DWORD m_dwFlags;
		CEMSObjectList<CEMSWaveExtSubBandDetails>	m_olstSubBands;
};

#endif