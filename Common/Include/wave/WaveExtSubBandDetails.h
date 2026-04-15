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

#ifndef __WAVE_EXT_SUBBAND_DETAILS_H__
#define __WAVE_EXT_SUBBAND_DETAILS_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "emspipe.h"

//! Maintains information about a sub band.
class CEMSWaveExtSubBandDetails : public CApiObjBase
{
	public:
		CEMSWaveExtSubBandDetails();
		CEMSWaveExtSubBandDetails( const CEMSWaveExtSubBandDetails& x );
		CEMSWaveExtSubBandDetails( const EMSWAVEEXSUBBAND& x );
		virtual ~CEMSWaveExtSubBandDetails();

		void SetType( const DWORD cdwType ) { m_subBand.dwType = cdwType; }
		DWORD GetType() const { return m_subBand.dwType; }

		void SetStartFrequency( const double cdValue ) { m_subBand.dFreqStart = cdValue; }
		double GetStartFrequency() const { return m_subBand.dFreqStart; }

		void SetEndFrequency( const double cdValue ) { m_subBand.dFreqEnd = cdValue; }
		double GetEndFrequency() const { return m_subBand.dFreqEnd; }

		//! Serialize the entire SAT chunk into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData );

		//! Serialize the entire SAT chunk to the stream pointer specified.
		virtual DWORD Serialize( IEMSSeqStream* pStrm );

		//! Build the SAT chunk object model from the input byte array.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Build the SAT chunk object model from the input data stream.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		//! Return the size in bytes of all contained data when serialized to a byte array.
		DWORD GetSize() const { return sizeof(m_subBand ); }
		
	private:
		EMSWAVEEXSUBBAND m_subBand;
};

#endif