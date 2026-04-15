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

#ifndef __DEMODULATOR_IMPL_H__
#define __DEMODULATOR_IMPL_H__

#include "aobjbase.h"
#include <wchar.h>

class CEMSWaveEx;

//! Performs demodulation of a signal.
class CEMSDemodulatorImpl : public CApiObjBase
{
	public:
		CEMSDemodulatorImpl();
		CEMSDemodulatorImpl( const CEMSDemodulatorImpl& x );
		virtual ~CEMSDemodulatorImpl();

		//! Initialize with a configuration string.  The string is in XML format, as follows:
		void Init( const wchar_t* cwszConfig );

		//! Process the wave and output the results as another wave.
		//! Both inputs and outputs are serialized forms of an EMS extended Wave chunk.
		void Process( const ULONG culBytes, const BYTE* cabyRawData, ULONG& ulBytesOut, BYTE*& abyDataOut );

		//! Process the wave and output the reesults as another wave.
		void Process( CEMSWaveEx& roWaveIn, CEMSWaveEx& roWaveOut );

	private:
		// PLL Data Structure
		typedef struct tagEMSPLLData
		{
			//! // RMS of A/D samples
			float           AGC_RMS;                   

			//! Mean value of A/D samples
			float           AGC_Mean;                  

			//! Carrier frequency (Hz)
			float           Carrier_Frequency;         

			//! Maximum modulation index (radians)
			float           Mod_Index;                 

			//! Mean value of modulation index (radians)
			float           Mod_Index_Mean;            

			//! RMS of modulation index (radians)
			float           Mod_Index_RMS;             

			//! Block number with maximum mod index
			unsigned short  Mod_Index_Block;           
		} TDataPLL, *LPTDataPLL;

	private:
		void _Process( CEMSWaveEx& roWaveInput, CEMSWaveEx& roWaveOut );

		void _PLL( const short* asWaveData, const long clSamples, 
				   short*& asDemodulated, long& lSamplesOut, TDataPLL* pData  );

		void _PhaseUnwrap( const short *phase_input, short block_size, short *phase_output,
                          float *doppler_freq_P,float *phase_ref_P, float *phase_std_deviation_P );

		void _AcquirePeak( const short *phase_input, short block_size, 
							float *doppler_freq_P, float *phase_ref_P );

	
	

	private:
		static const ULONG ms_culMaxFFTs;
		static const ULONG ms_culFFTSize;
		static const ULONG ms_culMaxSampleSize;
		static const double ms_cdOverlapPercent;
		static const double ms_cdModIndexThreshold;
		static const float ms_cfADCRange;
		static const ULONG ms_culSampleRate;
		static const ULONG ms_culPhaseSampleRate;
		static const float ms_cfPhaseConversion;

		//! The maximum number of iterations to do when determining the
		//! doppler frequency correction
		static const ULONG ms_culMaxFreqCorrectionIterations;

		//! Number of samples used in estimating the initial reference
		//! phase angle.
		static const ULONG ms_culInitialPhaseEstimateLength;

		//! The maximum number of iterations to do when estimating the
		//! reference phase angle
		static const ULONG ms_culMaxRefAngleEstIterations;

		//! Length of interval between samples for estimating an initial
		//! reference angle, the doppler frequency correction needed and phase
		//! standard deviation
		static const ULONG ms_culDecimationFactor;

		//! The maximum loop index for the actual phase unwrap.  Used in
		//! making more accurate phase unwrap.  THIS MUST DIVIDE EVENLY INTO
		//! PHASE_UNWRAP_BLOCK_SIZE!
		static const ULONG ms_culMaxUnwrapLoopIndex;
		static const ULONG ms_culPSDSize;
		static const float ms_cfAcquisitionFreqOffset;
		static const float ms_cfAcquisitionPhaseOffset;

		static const ULONG ms_culPeakFFTSize;
};

#endif