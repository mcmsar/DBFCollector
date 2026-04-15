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
#pragma warning(disable:4786)

#include "demodulatorimpl.h"
#include "wave/waveex.h"
#include "emsexcpt.h"
#include "sigproc.h"
#include <math.h>
#include <crtdbg.h>
#include "base2.h"
#include "splerrorhandler.h"

const ULONG CEMSDemodulatorImpl::ms_culMaxFFTs = 70;
const ULONG CEMSDemodulatorImpl::ms_culFFTSize = 8192;
const ULONG CEMSDemodulatorImpl::ms_culMaxSampleSize = 2097152L;  // 2^21;
const double CEMSDemodulatorImpl::ms_cdOverlapPercent = 0.125;
const double CEMSDemodulatorImpl::ms_cdModIndexThreshold = 1.75;
const float CEMSDemodulatorImpl::ms_cfADCRange = 65536.0;
const ULONG CEMSDemodulatorImpl::ms_culSampleRate = 2000000L;
const ULONG CEMSDemodulatorImpl::ms_culPhaseSampleRate = ms_culSampleRate/4;
const float CEMSDemodulatorImpl::ms_cfPhaseConversion = ms_cfADCRange / ((float) ms_culPhaseSampleRate);
const ULONG CEMSDemodulatorImpl::ms_culMaxFreqCorrectionIterations = 3;
const ULONG CEMSDemodulatorImpl::ms_culInitialPhaseEstimateLength = 417;
const ULONG CEMSDemodulatorImpl::ms_culMaxRefAngleEstIterations = 5;
const ULONG CEMSDemodulatorImpl::ms_culDecimationFactor = 8;
const ULONG CEMSDemodulatorImpl::ms_culMaxUnwrapLoopIndex = 8;
const ULONG CEMSDemodulatorImpl::ms_culPSDSize = 4097;
const float CEMSDemodulatorImpl::ms_cfAcquisitionFreqOffset = (float)ms_culPhaseSampleRate/4.0;
const float CEMSDemodulatorImpl::ms_cfAcquisitionPhaseOffset = (ms_cfADCRange*(float)ms_cfAcquisitionFreqOffset/(float)ms_culPhaseSampleRate);
const ULONG CEMSDemodulatorImpl::ms_culPeakFFTSize = 8192;

CEMSDemodulatorImpl::CEMSDemodulatorImpl()
{
}

CEMSDemodulatorImpl::CEMSDemodulatorImpl( const CEMSDemodulatorImpl& x )
{
}

CEMSDemodulatorImpl::~CEMSDemodulatorImpl()
{
}

void 
CEMSDemodulatorImpl::Init( const wchar_t* cwszConfig )
{
}

void 
CEMSDemodulatorImpl::Process( CEMSWaveEx& roWaveIn, CEMSWaveEx& roWaveOut )
{
	_Process( roWaveIn, roWaveOut );
}

void 
CEMSDemodulatorImpl::Process( const ULONG culBytes, const BYTE* cabyRawData, 
							   ULONG& ulBytesOut, BYTE*& abyDataOut )
{

	BYTE* abyData = const_cast<BYTE*>( cabyRawData );
	ULONG ulBytes = culBytes;

	// Reconstitute a Wave and then extract the data for down conversion.
	CEMSWaveEx oWaveInput;
	oWaveInput.Deserialize( abyData, ulBytes );

	CEMSWaveEx oWaveOutput;
	_Process( oWaveInput, oWaveOutput );

	// Serialize wave for output.
	ulBytesOut = oWaveOutput.Serialize( abyDataOut );
	
}

void
CEMSDemodulatorImpl::_Process( CEMSWaveEx& roWaveInput, CEMSWaveEx& roWaveOut )
{
	BYTE* abyDataChunk = NULL;
	short* asDemodulatedData = NULL;

	try
	{
		CEMSSPLErrorHandler::GetInstance()->Activate();

		// Only demodulate if required.
		if( EMS_PHASE_MOD_YES == roWaveInput.GetExtendedInfoRef().GetSignalDetailsRef().GetPhaseModState() )
		{
			// Get the data chunk.
			DWORD dwDataChunkSize = roWaveInput.GetDataChunkRef().GetData( abyDataChunk );
		
			long lSamples = roWaveInput.GetDataChunkRef().GetDataSize() / (roWaveInput.GetFormatChunk().GetBitsPerSample()/8);

			if( lSamples > 0 )
			{
				long lSamplesOut = 0;
				TDataPLL dataPLL;
				memset( &dataPLL, 0, sizeof(dataPLL) );

				_PLL( (short*) abyDataChunk, lSamples, asDemodulatedData, lSamplesOut, &dataPLL );

				// Now build a new output wave with the down converted data.
				// Copy format block from input.
				roWaveOut.SetFormat( roWaveInput.GetFormatChunk().Get() );

				DWORD dwBytesWritten = roWaveOut.Write( (const BYTE*) asDemodulatedData, lSamplesOut*sizeof(asDemodulatedData[0]) );

				// Copy the extended information.
				roWaveOut.SetExtendedInfo( roWaveInput.GetExtendedInfo() );

				// Set calculated extended information.
				roWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanCarrierFreq( dataPLL.Carrier_Frequency );
				roWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dataPLL.Mod_Index );
				roWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dataPLL.Mod_Index_Mean );
				roWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevModIndex( dataPLL.Mod_Index_RMS );
				roWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );

				if( asDemodulatedData )
				{
					delete[] asDemodulatedData;
					asDemodulatedData = 0;
				}
			}

			if( abyDataChunk )
			{
				delete[] abyDataChunk;
				abyDataChunk = 0;
			}
		}
		else
		{
			roWaveOut = roWaveInput;
		}
	}
	catch( ... )
	{
		if( abyDataChunk )
		{
			delete[] abyDataChunk;
			abyDataChunk = NULL;
		}

		if( asDemodulatedData )
		{
			delete[] asDemodulatedData;
			asDemodulatedData = NULL;
		}

		throw;
	}
}

void
CEMSDemodulatorImpl::_PLL( const short* asPhaseIN, const long clSamplesIn, 
							short*& asPhaseOUT, long& lSamplesOut, TDataPLL *lpData )
{
	try
	{
		long lSamples = clSamplesIn;

		float   delta_freq = 0.0;
		float   phase_std_deviation = 2.0;
		float   old_doppler_freq = 0.0;
		float   last_good_dop = 0.0;
		short   valid_old_freq = false;
		long    overlap_save_index = 0;
		short   block_size = 0;
		unsigned long Overlap_Block_Size = 0;  // Start sample index after overlap
		unsigned long Non_Overlap_Block_Size = 0;

		float m_phase_RMS[ms_culMaxFFTs];
		float   doppler_freq=0.0;
		float   doppler_freq_avg=0.0;
		float   doppler_freq_sum=0.0;
		float   phase_ref=0.0;
		float   phase_std_deviation_max=0.0;
		float   mean_phase_RMS=0.0;
		float   stddev_phase_RMS=0.0;

		long    block_index=0;
		long    nblocks=0;
		long    phase_index=0;
		long    blocks_locked=0;
		long    repeat_count=0;
		long    unlocked_count=0;
		long    index_std_deviation_max=0;

		const short   *raw_buffer=0;
		short   valid_freq=0;

		short   phase_shift=0;
		long    i=0;

		TDataPLL& Data = *lpData;

		// Extract I and Q first
		// Raw Inphase Buffer
		//static short nDdcI[ms_culMaxSampleSize/2];

		// Raw Quadrature Buffer
		//static short nDdcQ[ms_culMaxSampleSize/2];

		lSamplesOut = clSamplesIn;

		// Split input AD data into I and Q channels
   		//emsvbReal( (WCplx *) &asPhaseData[0], &nDdcI[0], lSamplesOut );
   		//emsvbImag( (WCplx *) &asPhaseData[0], &nDdcQ[0], lSamplesOut );
		
		//asPhaseIN = new short[lSamplesOut];

		//if( !asPhaseIN )
		//{
		//	THROW_NOMEMORY_EXCEPTION();
		//}

		//memset( asPhaseIN, 0, lSamplesOut*sizeof(short) );

		asPhaseOUT = new short[ lSamplesOut ];

		if( !asPhaseOUT )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( asPhaseOUT, 0, lSamplesOut*sizeof(short) );

		int Phase_Scale = 0;

		// Perform phase detection.  nPhase becomes input.
		//emswbrPhase( &nDdcI[0], &nDdcQ[0], &asPhaseIN[0], lSamplesOut );
		//emswbMpy1( 2, &asPhaseIN[0], lSamplesOut, NSP_NO_SCALE, &Phase_Scale );


		block_size = (unsigned short)( ms_culFFTSize );
		nblocks = lSamples / block_size;

		delta_freq             = 0.0;
		phase_std_deviation    = 2.0;
		old_doppler_freq       = 0.0;
		last_good_dop          = 0.0;
		valid_old_freq         = false;

		phase_index             = 0;
		doppler_freq_sum        = 0.0;
		phase_std_deviation_max = 0.0;
		blocks_locked           = 0;
		repeat_count            = 4;
		unlocked_count          = 10;
		doppler_freq            = last_good_dop;

		Overlap_Block_Size     = (unsigned long)( block_size * ms_cdOverlapPercent );
		Non_Overlap_Block_Size = block_size - Overlap_Block_Size;

		emssbZero( m_phase_RMS, ms_culMaxFFTs );

		long lActualDataBlocks = 0;

		// Start of phase lock loop
		for ( block_index = 0; (block_index < ms_culMaxFFTs) &&
			(phase_index <= (clSamplesIn - block_size)); block_index++ )
		{
		   
			lActualDataBlocks++;

			// Pointer to raw buffer to be processed
		   raw_buffer = &asPhaseIN[phase_index];

		   // Acquire if lock lost, up to three times per second
		   if ( ( phase_std_deviation > ms_cdModIndexThreshold ) &&
				( repeat_count > 0 ) )
		   {
				doppler_freq = -200000.0;
				_AcquirePeak( raw_buffer, block_size, &doppler_freq, &phase_ref );
				repeat_count--;
		   }

		   _PhaseUnwrap( raw_buffer, block_size, &asPhaseOUT[phase_index],
			  &doppler_freq,  &phase_ref, &phase_std_deviation );

		   // Try again on same block, up to three times per second
		   if ( ( phase_std_deviation > ms_cdModIndexThreshold ) &&
				( repeat_count > 0 ) )
		   {
				doppler_freq = last_good_dop;

				_AcquirePeak( raw_buffer, block_size, &doppler_freq, &phase_ref );

				_PhaseUnwrap( raw_buffer, block_size, &asPhaseOUT[phase_index],
          		   &doppler_freq,  &phase_ref, &phase_std_deviation );

			  repeat_count--;
		   }

		   phase_index += Non_Overlap_Block_Size;

		   _ASSERTE( block_index < ms_culMaxFFTs );
		   if( block_index >= ms_culMaxFFTs )
			   THROW_INVALID_ARG_EXCEPTION();

		   m_phase_RMS[block_index] = phase_std_deviation;

		   if ( phase_std_deviation <= ms_cdModIndexThreshold )
		   {
			  blocks_locked++;
			  doppler_freq_sum += doppler_freq;
			  last_good_dop = doppler_freq;
		   }
		   else
		   {
			  unlocked_count--;
			  phase_ref = -200000.0;
		   }

		   doppler_freq = last_good_dop + delta_freq;
		   if ( phase_std_deviation > phase_std_deviation_max )
		   {
			 phase_std_deviation_max = phase_std_deviation;
			 index_std_deviation_max = block_index;
		   }
		}

		// End of block processing
		if ( blocks_locked > 0 )
		{
		   valid_freq       = true;
		   doppler_freq_avg = doppler_freq_sum / blocks_locked;
		}
		else
		{
		   valid_freq       = false;
		   doppler_freq     = 0.0;
		   doppler_freq_avg = 0.0;
		}

		if ( valid_freq )
		{
		   if ( valid_old_freq )
		   {
			  delta_freq = ( doppler_freq_avg - old_doppler_freq ) / ms_culMaxFFTs;
		   }
		   old_doppler_freq = doppler_freq_avg;
		   valid_old_freq   = true;
		}
		else
		{
		   valid_old_freq = false;
		}

		// Compute mean and RMS of modulation index
		mean_phase_RMS   = emssMean( &m_phase_RMS[0], lActualDataBlocks );
		stddev_phase_RMS = emssStdDev( &m_phase_RMS[0], lActualDataBlocks );

		// Establish output PLL data values
		Data.Carrier_Frequency = doppler_freq_avg;
		Data.Mod_Index         = phase_std_deviation_max;
		Data.Mod_Index_Mean    = mean_phase_RMS;
		Data.Mod_Index_RMS     = stddev_phase_RMS;
		Data.Mod_Index_Block   = (short)index_std_deviation_max;

		// Change direction of frequency downconversion
		Data.Carrier_Frequency *= -1.0;

		//if( asPhaseIN )
		//{
		//	delete[] asPhaseIN;
		//	asPhaseIN = 0;
		//}
	}
	catch( ... )
	{
		//if( asPhaseIN )
		//{
		//	delete[] asPhaseIN;
		//	asPhaseIN = 0;
		//}

		if( asPhaseOUT )
		{
			delete[] asPhaseOUT;
			asPhaseOUT = 0;
		}

		throw;
	}

}

void
CEMSDemodulatorImpl::_PhaseUnwrap( const short *phase_input,
                                           short block_size,
                                           short *phase_output,
                                           float *doppler_freq_P,
                                           float *phase_ref_P,
                                           float *phase_std_deviation_P )
{
    double  temp1=0.0, temp2=0.0, temp3=0.0;

    float	avg_ref_angle=0.0;
    float	doppler_freq_inc=0.0;
    float	phase_error_sum=0.0;
    float	phase_error_rms=0.0;
    float	phase_conversion=0.0;

    long	cur_estimation_set_size=0;
    long	i=0;
    long	j=0;
    long	k=0;
    long	number_of_inputs=0;
    long	num_frq_correction_samples=0;

    short	discrete_avg_ref_angle=0;
    short	loop_limit_1=0;
    short	loop_limit_2=0;
    short	phase_error=0;
    short	reference_phase=0;
    short	phase_correction=0;
    short	phase_increment=0;
    short	phase_increment_1=0;
    short	phase_increment_2=0;
    short	previous_phase_increment=0;

    number_of_inputs         = block_size;
    cur_estimation_set_size  = 0;
    previous_phase_increment = 32767;		// Must be an impossible value to start

    if ( block_size == 4096 )
    {
	    phase_conversion = ( ms_cfPhaseConversion*2 );
    }
    else
    {
	    phase_conversion = ms_cfPhaseConversion;
    }

    for ( i = 0; i < ms_culMaxFreqCorrectionIterations; i++ )
    {
	   // Iterate to find mean reference angle
	   phase_increment = ( __int16 ) ( phase_conversion * (*doppler_freq_P) );

	   if ( ( phase_increment != previous_phase_increment ) || ( i == 0 ) )
	   {
	      previous_phase_increment = phase_increment;
          if ( *phase_ref_P > -100000.0 )
          {
                 discrete_avg_ref_angle = (short)*phase_ref_P;
          }
          else
          {
	         discrete_avg_ref_angle = phase_input[0];
          }
	      avg_ref_angle = discrete_avg_ref_angle;

          j = 0;
	      do
	      {
	         phase_correction = discrete_avg_ref_angle;
             phase_error_sum  = 0.0;
	         for ( k = 0; k < ms_culInitialPhaseEstimateLength; k++ )
		     {
                // Logic relies on modulo arithmetic
		        phase_error       = phase_input[k] - phase_correction;
		        phase_error_sum  += (float)phase_error;
		        phase_correction += phase_increment;
	         }
 	         number_of_inputs = ms_culInitialPhaseEstimateLength;
	         avg_ref_angle   += phase_error_sum / ( float ) number_of_inputs;
             discrete_avg_ref_angle = ( __int16 ) avg_ref_angle;
	         j++;
	      }
          while ( j <= ms_culMaxRefAngleEstIterations );
	   }

       // Iterate to find doppler frequency correction
       cur_estimation_set_size += block_size / ms_culMaxFreqCorrectionIterations;
       reference_phase = discrete_avg_ref_angle;
   	   num_frq_correction_samples = 0;

       // Logic relies on modulo arithmetic
       phase_increment_1 = phase_increment * ms_culDecimationFactor;

       if ( *doppler_freq_P >= 0 )
	   {
          // Logic relies on modulo arithmetic
	      phase_increment_2 = phase_increment_1 + 1;
	   }
	   else
	   {
          // Logic relies on modulo arithmetic
	      phase_increment_2 = phase_increment_1 - 1;
	   }

       // Compute phase increment loop counters
       temp1 = (double) (phase_conversion * (double) *doppler_freq_P * ms_culDecimationFactor );
       temp3 = fabs( modf( temp1 , &temp2 ) );
       loop_limit_2 = (__int16) (cur_estimation_set_size *temp3);
       loop_limit_1 = cur_estimation_set_size - loop_limit_2;

       // Compute average and RMS phase error
       phase_error_sum = 0.0;
       phase_error_rms = 0.0;
	   for ( j = 0; j < loop_limit_1; j += ms_culDecimationFactor )
	   {
          phase_error      = phase_input[j] - reference_phase;
          phase_error_sum += (float)phase_error;
          phase_error_rms += ((float)phase_error * (float)phase_error);
	      reference_phase += phase_increment_1;
	      num_frq_correction_samples++;
	   }
	   for ( ; j < cur_estimation_set_size; j += ms_culDecimationFactor )
	   {
          phase_error      = phase_input[j] - reference_phase;
          phase_error_sum += (float)phase_error;
          phase_error_rms += ((float)phase_error * (float)phase_error);
	      reference_phase += phase_increment_2;
	      num_frq_correction_samples++;
	   }
       phase_error_sum /= (float)num_frq_correction_samples;
       phase_error_rms /= (float)num_frq_correction_samples;
       phase_error_rms -= (phase_error_sum * phase_error_sum);
       phase_error_rms  = (float)sqrt(phase_error_rms);

       // Calculate lock parameters
       *phase_std_deviation_P = (float)(2.0 * M_PI / ms_cfADCRange * phase_error_rms);
       doppler_freq_inc = (float)( 2.0 * phase_error_sum
                              / (float)num_frq_correction_samples
	                          / (float)ms_culDecimationFactor / phase_conversion );
	   *doppler_freq_P += doppler_freq_inc;
    }

    // Perform final phase adjustments
    //discrete_avg_ref_angle -= (__int16) phase_error_sum;
    phase_correction  = discrete_avg_ref_angle;
    phase_increment_1 = (short)( phase_conversion * (*doppler_freq_P) );

    if ( *doppler_freq_P >= 0 )
    {
       phase_increment_2 = phase_increment_1 + 1;
    }
    else
    {
       phase_increment_2 = phase_increment_1 - 1;
    }

    // Compute phase increment loop counters
    temp1 = (double) (phase_conversion * (double) *doppler_freq_P );
    temp3 = fabs( modf( temp1 , &temp2 ) );
    loop_limit_2 = (__int16) ( ms_culMaxUnwrapLoopIndex * temp3 );
    loop_limit_1 = ms_culMaxUnwrapLoopIndex - loop_limit_2;
    i = 0;
    do
    {
        for ( j = 0; j < loop_limit_1; j++ )
        {
	       phase_output[i] = phase_correction - phase_input[i];
	       i++;
	       phase_correction += phase_increment_1;
        }

        for ( j = 0; j < loop_limit_2; j++ )
        {
	       phase_output[i] = phase_correction - phase_input[i];
	       i++;
	       phase_correction += phase_increment_2;
        }
    }
    while (i < block_size);

    // Additional correction to doppler frequency
	phase_error_sum  = (float)emswMean( (short *)&phase_output[0], block_size );
	doppler_freq_inc = (float)( -2.0 * phase_error_sum / (float)block_size / phase_conversion );
	*doppler_freq_P += doppler_freq_inc;

    // Compute estimate of next phase reference angle
    avg_ref_angle = (float)((1.0-ms_cdOverlapPercent)* number_of_inputs * phase_conversion * (*doppler_freq_P ));
    avg_ref_angle += discrete_avg_ref_angle;
    discrete_avg_ref_angle = (short)fmod( avg_ref_angle, ms_cfADCRange );

    if ( discrete_avg_ref_angle >  32767.0 ) 
		discrete_avg_ref_angle -= (short)32767.0;

    if ( discrete_avg_ref_angle < -32767.0 )
		discrete_avg_ref_angle += (short)32767.0;

    *phase_ref_P = discrete_avg_ref_angle;
    // *phase_ref_P = -200000.0;

}



//---------------------------------------------------------------------------
void
CEMSDemodulatorImpl::_AcquirePeak( const short *phase_input, short input_block_size, 
								  float *doppler_freq_P, float *phase_ref_P )
{
    float m_adjusted_phase_input[ ms_culPeakFFTSize ];
    float m_cumulative_power_spect[ ms_culPeakFFTSize ];
    float m_power_spect[ ms_culPeakFFTSize  ];
	EMSCOMPLEX m_complex_spectrum[ ms_culPeakFFTSize ];
    short adjusted_phase_increment = (short)(ms_cfAcquisitionPhaseOffset + 0.5);
    short m_discrete_adjusted_phase_input[ ms_culPeakFFTSize ];


    float cumulative_power=0.0f;
    float peak_power_dif=0.0;
    float power_dif=0.0;
    float acq_freq_offset=0.0;
    float acq_phase_offset=0.0;

    long number_of_inputs=0;
    long number_of_outputs=0;
    long i=0;
    long j=0;
    long bs2=0;
    long numj=0;
    long peak_bin=0;
    long start=0,end=0,deltaj=0;
    short phase_increment=0;

	long j1 = 0, j2 = 0;

    bs2              =  CEMSBase2::Log( ms_culPeakFFTSize );
    acq_freq_offset  =  ms_cfAcquisitionFreqOffset;
    acq_phase_offset =  ms_cfAcquisitionPhaseOffset;

	// Override block_size.
	ULONG block_size = ms_culPeakFFTSize;

//    if (block_size == 4096)
//    {
//    	acq_freq_offset  =  ms_cfAcquisitionFreqOffset/2;
//    }

    phase_increment          = 0;
    adjusted_phase_increment = (short)( acq_phase_offset + 0.5 );

    for ( i = 0; i < block_size; i++)
    {
        // Logic relies on modulo arithmetic
	    m_discrete_adjusted_phase_input[i] = phase_input[i] + phase_increment;
	    phase_increment += adjusted_phase_increment;
    }

    number_of_inputs  = block_size;
    number_of_outputs = block_size / 2;

    //-----------------------------------------------------------------------------

    emssbIntToFloat(m_discrete_adjusted_phase_input,m_adjusted_phase_input,
                        number_of_inputs,16,NSP_Noflags);

//    emssbMpy1((float)( 1.0/32767.0 ), m_adjusted_phase_input, number_of_outputs);

    emssbMpy1((float)( 1.0/32767.0 ), m_adjusted_phase_input, number_of_inputs);

    emssRealFftNip(m_adjusted_phase_input,m_complex_spectrum,bs2,EMS_SPL_FWD);

    emscbPowerSpectr(m_complex_spectrum,m_power_spect,number_of_outputs);

    //-----------------------------------------------------------------------------

    cumulative_power = 0.0;
    for ( i = 0; i < number_of_outputs; i++)
    {
	    cumulative_power += m_power_spect[i];
	    m_cumulative_power_spect[i] = cumulative_power;
    }

    peak_power_dif = -1e10;	// modified to have a lower floor

    if(*doppler_freq_P > -100000.0)
    {
        peak_bin = (long)(((*doppler_freq_P+acq_freq_offset)*ms_culPeakFFTSize)/ms_culPhaseSampleRate);
        start    = peak_bin-10;
        end      = peak_bin+10;
        numj     = 100;
    }
    else
    {
        peak_bin = number_of_outputs/4;
        start    = number_of_outputs/4;
        end      = number_of_outputs*3/4;
        numj     = 10;
    }
    deltaj = number_of_outputs/4/numj;

    for ( i = start; i < end; i++ )
    {
        power_dif=m_power_spect[i];
        for(j=0;j<numj;j++)
        {
			j1 = j*deltaj + 3;
			j2 = (j+1)*deltaj + 3;

			if ( i > j2 && i < number_of_outputs - j2 )
			{
				power_dif -= (float)fabs((double)
					( ( m_cumulative_power_spect[i + j2]
		            - m_cumulative_power_spect[i + j1] )
		    		- ( m_cumulative_power_spect[i - j1]
		     	    - m_cumulative_power_spect[i - j2] ) ) );
			}
        }
	    if (power_dif > peak_power_dif)
	    {
	        peak_bin = i;
	        peak_power_dif = power_dif;
	    }
    }

    if ((m_power_spect[peak_bin]
	- 0.5 * (m_power_spect[peak_bin - 1] + m_power_spect[peak_bin + 1])) > 0)
    {
        *doppler_freq_P  = (float)((float)ms_culPhaseSampleRate / (float)ms_culPeakFFTSize * ( peak_bin
		+ 0.25 * (m_power_spect[peak_bin - 1] - m_power_spect[peak_bin + 1])
			/ (m_power_spect[peak_bin]
				- 0.5 * (m_power_spect[peak_bin - 1]
						+ m_power_spect[peak_bin + 1]) )));
    }
    else
    {
        *doppler_freq_P  =
	    ( float ) ms_culPhaseSampleRate / ( float ) ms_culPeakFFTSize * ( float ) peak_bin;
    }

    *doppler_freq_P  -= acq_freq_offset;
//    *phase_ref_P  = atan2 ( m_complex_spectrum[peak_bin].im,m_complex_spectrum[peak_bin].re  );
//    *phase_ref_P *= (ADC_RANGE/NSP_PI);

    *phase_ref_P  = -2000000.0;     // ?????????????

}

