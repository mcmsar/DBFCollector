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

#ifndef __WAVE_EXT_PROPERTIES_H__
#define __WAVE_EXT_PROPERTIES_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "emspipe.h"

//! Maintains extended properties.
class CEMSWaveExtProperties : public CApiObjBase
{
	public:
		CEMSWaveExtProperties();
		CEMSWaveExtProperties( const CEMSWaveExtProperties& x );
		virtual ~CEMSWaveExtProperties();

		void SetChannelNumber( const DWORD cdwChannelNo ) { m_Props.dwChannelNumber = cdwChannelNo; }
		DWORD GetChannelNumber() const { return m_Props.dwChannelNumber; }

		void SetHardwareVersion( const DWORD cdwHWVersion ) { m_Props.dwHardwareVersion = cdwHWVersion; }
		DWORD GetHardwareVersion() const { return m_Props.dwHardwareVersion; }

		void SetSoftwareVersion( const DWORD cdwSWVersion ) { m_Props.dwSoftwareVersion = cdwSWVersion; }
		DWORD GetSoftwareVersion() const { return m_Props.dwSoftwareVersion; }

		void SetTimeStart( const EMSTIME ctimeStart ) { m_Props.timeStart = ctimeStart; }
		EMSTIME GetTimeStart() const { return m_Props.timeStart; }

		void SetBinSize( const double cdSize ) { m_Props.dBinSize = cdSize; }
		double GetBinSize() const { return m_Props.dBinSize; }

		void SetStartIndex( const DWORD cdwStartIdx ) { m_Props.dwStartIdx = cdwStartIdx; }
		DWORD GetStartIndex() const { return m_Props.dwStartIdx; }

		void SetEndIndex( const DWORD cdwEndIdx ) { m_Props.dwEndIdx = cdwEndIdx; }
		DWORD GetEndIndex() const { return m_Props.dwEndIdx; }

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
		DWORD GetSize() const { return sizeof(m_Props); }
		
	private:
		EMSWAVEEXTPROPERTIES m_Props;
};

#endif