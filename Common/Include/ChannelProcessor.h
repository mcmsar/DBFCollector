/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __CHANNEL_PROCESSOR_H__
#define __CHANNEL_PROCESSOR_H__

#include "aobjbase.h"
#include "logclient.h"
#include "memtypes.h"
#include "emstime.h"
#include "demodulatorimpl.h"

class CEMSWaveEx;
interface IEMSSignalConditioner;

//! Processes raw data from one channel of an A/D board.
class CEMSChannelProcessor : public CApiObjBase
{
	public:
		CEMSChannelProcessor();
		CEMSChannelProcessor( const CEMSChannelProcessor& x );
		~CEMSChannelProcessor();

		void Init( const wchar_t* cwszSourceFile );

		void InitPass( const ULONG culSampleRate, const ULONG culSampleSize, 
						   const ULONG culProcessFlags );

		//! Resets member data.  This should be called before processing data for a new pass.
		void Reset();

		//! Returns true if the marker bit was found and false otherwise.
		bool ComputeADCMeasurements(	USHORT*& rausData, 
										const ULONG culLen,
										const INT64 ci64MarkerTimeOffset,
										EMSTIME& rtimeBuffer, 
										EMSTIME& rtimeStart,
										ULONG& rulMarkerBitRate,
										double& rdAGCMean,
										double& rdAGCRMS );

		void DigitalDownConvert(	USHORT*& rausData,
									const ULONG culRawDDCSize,
									const LONG clDDCSize,
									const LONG clDDCIndex,
									const ULONG culOverlapBlockSize,
									const ULONG culDMAOffset,
									const ULONG culFFTSize,
									TRawInphase& rRawInPhase,
									TRawQuadrature& rRawQuadrature, 
									TRawPhase& rRawPhase );

		CEMSWaveEx* DigitalDownConvert(	const bool cbModulated, const CEMSWaveEx* cpWave );

		void Demodulate( CEMSWaveEx& roWaveIn, CEMSWaveEx& roWaveOut );

		void ComputePowerSpectrum( const TDemodulatedPhase crDemodPhase,
									const ULONG culMarkerBitRate,
									const LONG clFilterSizeFactor,
									WORD& rwFFTCount, 
									double& rdFFTBinSize,
									TCollectorPsd& rIntegratedPS,
									TCollectorFft& rFFT,
									TCollectorPower& rPS);

		void ComputePowerSpectrumNoPLL( short*& rausData,
										const ULONG culMarkerBitRate,
										const LONG clFilterSizeFactor,
										WORD& rwFFTCount, 
										double& rdFFTBinSize,
										TCollectorPsd& rIntegratedPS,
										TCollectorFft& rFFT,
										TCollectorPower& rPS );

		ULONG GetLastMarkerIndex() const { return m_ulLastMarkerIndex; }

		ULONG GetMarkerBitRate() const { return m_ulMarkerBitRate; }

		LONG GetAGCIndex() const { return m_lAGCIndex; }

		EMSTIME GetLastCorrectedTime() const { return m_timeLastCorrected; }

		void ResetLastCorrectedTime() { m_timeLastCorrected.ResetTime(); }

	private:
		EMSTIME _AdjustTime( const EMSTIME ctimeCurrent, const ULONG culMarkerIndex,
						  const ULONG culSampleRate, const INT64 ci64MarkerTimeOffset );

		IEMSSignalConditioner* _GetDownConverter( const bool cbModulated );

	public:	// constants
		static const DWORD ms_cdwDnlkNoPhaseModulation;
		static const DWORD ms_cdwDnlkPhaseModulation;
		
		static const wchar_t* ms_cwszModulatedDCPluginID;
		static const wchar_t* ms_cwszUnModulatedDCPluginID;

	private:
#ifdef APACHE_LOGGER
		CEMSLogClient			m_oLogger;
#endif
		ULONG					m_ulLastMarkerIndex;
		ULONG					m_ulMarkerBitRate;
		LONG					m_lAGCIndex;
		ULONG					m_ulSampleRate;
		ULONG					m_ulSampleSize;
		ULONG					m_ulProcessFlags;
		CEMSTime				m_timeLastCorrected;
		IEMSSignalConditioner*	m_pModulatedDC;
		IEMSSignalConditioner*	m_pUnModulatedDC;
		std::wstring			m_owszModulatedDCPluginID;
		std::wstring			m_owszUnModulatedDCPluginID;
		CEMSDemodulatorImpl		m_oDemod;
};

#endif