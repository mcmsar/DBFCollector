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

#ifndef __WAVE_EXT_SIGNAL_DETAILS_H__
#define __WAVE_EXT_SIGNAL_DETAILS_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "emspipe.h"
#include <string>

//! Maintains information about a particular signal.
class CEMSWaveExtSignalDetails : public CApiObjBase
{
	public:
		CEMSWaveExtSignalDetails();
		CEMSWaveExtSignalDetails( const CEMSWaveExtSignalDetails& x );
		virtual ~CEMSWaveExtSignalDetails();

		void SetFlags( const DWORD cdwFlags ) { m_signalDetails.dwFlags = cdwFlags; }
		DWORD GetFlags() const { return m_signalDetails.dwFlags; }

		void SetMaxADC( const double cdValue ) { m_signalDetails.dMaxADC = cdValue; }
		double GetMaxADC() const { return m_signalDetails.dMaxADC; }

		void SetMeanADC( const double cdValue ) { m_signalDetails.dMeanADC = cdValue; }
		double GetMeanADC() const { return m_signalDetails.dMeanADC; }

		void SetStdDevADC( const double cdValue ) { m_signalDetails.dStdDevADC = cdValue; }
		double GetStdDevADC() const { return m_signalDetails.dStdDevADC; }
		
		void SetMeanCarrierFreq( const double cdValue ) { m_signalDetails.dMeanCarrierFreq = cdValue; }
		double GetMeanCarrierFreq() const { return m_signalDetails.dMeanCarrierFreq; }

		void SetStdDevCarrierFreq( const double cdValue ) { m_signalDetails.dStdDevCarrierFreq = cdValue; }
		double GetStdDevCarrierFreq() const { return m_signalDetails.dStdDevCarrierFreq; }

		void SetMaxModIndex( const double cdValue ) { m_signalDetails.dMaxModIndex = cdValue; }
		double GetMaxModIndex() const { return m_signalDetails.dMaxModIndex; }

		void SetMeanModIndex( const double cdValue ) { m_signalDetails.dMeanModIndex = cdValue; }
		double GetMeanModIndex() const { return m_signalDetails.dMeanModIndex; }

		void SetStdDevModIndex( const double cdValue ) { m_signalDetails.dStdDevModIndex = cdValue; }
		double GetStdDevModIndex() const { return m_signalDetails.dStdDevModIndex; }

		void SetPhaseModState( const EMSPHASEMODSTATE ceState ) { m_signalDetails.statePhaseMod = ceState; }
		EMSPHASEMODSTATE GetPhaseModState() const { return m_signalDetails.statePhaseMod; }
		std::wstring GetPhaseModStateString() const;

		void SetDCState( const EMSDCSTATE ceState ) { m_signalDetails.stateDC = ceState; }
		EMSDCSTATE GetDCState() const { return m_signalDetails.stateDC; }
		std::wstring GetDCStateString() const;

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

		DWORD GetSize() const { return sizeof(m_signalDetails); }

	public:	// constants
		static const DWORD EMSWAVEEXSIGNAL_GOOD_MARKER_BIT;
		static const DWORD EMSWAVEEXSIGNAL_BAD_MARKER_BIT;

		
	private:
		EMSWAVEEXSIGNALDETAILS m_signalDetails;
};

#endif