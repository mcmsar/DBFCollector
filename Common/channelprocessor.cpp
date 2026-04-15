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

#include "channelprocessor.h"
#include "convutility.h"
#include "emsconst.h"
#include "sigproc.h"
#include "emspluginloader.h"
#include "configurationaccessor.h"
#include "emsexcpt.h"
#include "wave/waveex.h"
#include "base2.h"

#include <math.h>
#include <assert.h>

#include <initguid.h>
#include "signalconditioner.h"


const wchar_t* CEMSChannelProcessor::ms_cwszModulatedDCPluginID = L"Modulated/ClassID";
const wchar_t* CEMSChannelProcessor::ms_cwszUnModulatedDCPluginID = L"Unmodulated/ClassID";

const DWORD CEMSChannelProcessor::ms_cdwDnlkNoPhaseModulation = 0x01;
const DWORD CEMSChannelProcessor::ms_cdwDnlkPhaseModulation = 0x00;

CEMSChannelProcessor::CEMSChannelProcessor() : m_ulLastMarkerIndex(0), m_ulMarkerBitRate(0),
												m_lAGCIndex(0), m_ulSampleRate(0),
												m_ulSampleSize(0), m_ulProcessFlags(0),
												m_pModulatedDC(NULL), m_pUnModulatedDC(NULL)
{
	m_timeLastCorrected.ResetTime();

#ifdef APACHE_LOGGER
	m_oLogger.SetParent( L"CEMSChannelProcessor" );
#endif
	CEMSSignalProcLib::Initialize();
}

CEMSChannelProcessor::CEMSChannelProcessor( const CEMSChannelProcessor& x ) : 
							m_ulLastMarkerIndex( x.m_ulLastMarkerIndex ), 
							m_ulMarkerBitRate( x.m_ulMarkerBitRate ),
							m_lAGCIndex( x.m_lAGCIndex ),
							m_ulSampleRate( x.m_ulSampleRate ),
							m_ulSampleSize( x.m_ulSampleSize ), 
							m_ulProcessFlags( x.m_ulProcessFlags ),
							m_timeLastCorrected( x.m_timeLastCorrected ),
							m_pModulatedDC(x.m_pModulatedDC),
							m_pUnModulatedDC(x.m_pUnModulatedDC),
							m_owszModulatedDCPluginID( x.m_owszModulatedDCPluginID ),
							m_owszUnModulatedDCPluginID( x.m_owszUnModulatedDCPluginID ),
							m_oDemod( x.m_oDemod )
{
#ifdef APACHE_LOGGER
	m_oLogger.SetParent( L"CEMSChannelProcessor" );
#endif

	if( m_pModulatedDC )
		m_pModulatedDC->AddRef();

	if( m_pUnModulatedDC )
		m_pUnModulatedDC->AddRef();

	CEMSSignalProcLib::Initialize();
}

CEMSChannelProcessor::~CEMSChannelProcessor()
{
	if( m_pModulatedDC )
	{
		m_pModulatedDC->Release();
		m_pModulatedDC = NULL;
	}

	if( m_pUnModulatedDC )
	{
		m_pUnModulatedDC->Release();
		m_pUnModulatedDC = NULL;
	}
}

void 
CEMSChannelProcessor::Init( const wchar_t* cwszSourceFile )
{
	CEMSConfigurationAccessor oConfig;
	oConfig.SetSourceFile( cwszSourceFile );

	m_owszModulatedDCPluginID = oConfig.GetElementValue( ms_cwszModulatedDCPluginID );
	m_owszUnModulatedDCPluginID = oConfig.GetElementValue( ms_cwszUnModulatedDCPluginID );
}

void 
CEMSChannelProcessor::InitPass( const ULONG culSampleRate, const ULONG culSampleSize, 
						   const ULONG culProcessFlags )
{
	m_ulSampleRate = culSampleRate;
	m_ulSampleSize = culSampleSize;
	m_ulProcessFlags = culProcessFlags;
	m_ulLastMarkerIndex = 0;
	m_ulMarkerBitRate = m_ulSampleRate;
	m_lAGCIndex = 0;
	m_timeLastCorrected.ResetTime();
}

bool 
CEMSChannelProcessor::ComputeADCMeasurements(	USHORT*& rausData, 
												const ULONG culLen,
												const INT64 ci64MarkerTimeOffset,
												EMSTIME& rtimeBuffer, 
												EMSTIME& rtimeStart,
												ULONG& rulMarkerBitRate,
												double& rdAGCMean,
												double& rdAGCRMS )
{
	bool bRet = false;

	// Scale factor of FIR filter
	const int	ciFIR_Scale = 16;      

	// Scale factor for phase data
	const int	ciPhase_Scale = 16;    

	// Offset to current dma buffer segment
	ULONG			ulStartOffset=0, ulEndOffset=0, ulOffset=0;
	
	// Marker bit A/D value
	short			sMin_Value=0;                  
	
	// Correction to stddev operations
	float			fTempdata=0.0;
	
	long			lIdx=0;
	
	CEMSTime		timeBuffer;
	
	long			lTimeFraction=0;
	
	ULONG			ulMarkerIndex = 0;

	// Locate first GPS-provided marker bit. Clear sample bit 15 when found.
	// Remove data anomalies (with bit 14 set) if found before a valid marker bit.

	ulStartOffset = ( m_ulProcessFlags == ms_cdwDnlkPhaseModulation ) ? FIR_OVERLAP : EMS_RAW_OVERLAP;

	ulEndOffset = ulStartOffset + m_ulSampleSize;

	lTimeFraction = 0;

	ulOffset = ulStartOffset;	// start at the beginning of the data read into DMA buffer

	do
	{
		sMin_Value = emswMinExt( (const short *)&rausData[ulOffset], 
						m_ulSampleSize/2, (int *) &ulMarkerIndex );
		
		// This check should be removed once we confirm that bit 14 is never getting set, and that
		// all data ariving with bit 15 set represent real marker bits!


		if ( sMin_Value & 0x4000 )
		{
			ulMarkerIndex += ulOffset;
			rausData[ ulMarkerIndex ] &= 0x3FFF;
			sMin_Value = rausData[ ulMarkerIndex ];

		}
		else if ( sMin_Value & 0x8000 )
		{
			ulMarkerIndex += ulOffset;
			rausData[ ulMarkerIndex ] &= 0x3FFF;

			if ( m_ulLastMarkerIndex != 0 )
			{
				LONG lTempBitRate = (LONG)ulMarkerIndex - (LONG)m_ulLastMarkerIndex;

				if ( lTempBitRate < ( m_ulSampleRate / 2 )  )
				{
#ifdef APACHE_LOGGER
					m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
											L"Increasing marker bit rate by the sample size.");
#endif
					m_ulMarkerBitRate = (ULONG)( lTempBitRate + m_ulSampleSize );
				}
				else
				{
					m_ulMarkerBitRate = (ULONG)lTempBitRate;
				}
			}
#ifdef APACHE_LOGGER
			m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
								L"Last marker index = %d, This marker index = %d.", 
								m_ulLastMarkerIndex, ulMarkerIndex  );
#endif

			m_ulLastMarkerIndex = ulMarkerIndex;

			if ( !bRet )
			{
				bRet = true;

				rtimeBuffer = _AdjustTime( rtimeBuffer, ulMarkerIndex, m_ulSampleRate, ci64MarkerTimeOffset );
				
			}
			else
			{
#ifdef APACHE_LOGGER
				m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, L"Found subsequent marker bit.");
#endif
			}
		}
		else
		{
			ulOffset += m_ulSampleSize / 2;
		}
	}
	while( ulOffset <  ulEndOffset );

	if ( !bRet )
	{
#ifdef APACHE_LOGGER
		m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, L"Marker bit not found.");
#endif

		ulMarkerIndex = 0;

		if( m_ulLastMarkerIndex && m_ulMarkerBitRate )
		{
			ulMarkerIndex = m_ulLastMarkerIndex + m_ulMarkerBitRate;

			if( ulMarkerIndex >= ulEndOffset )
			{
#ifdef APACHE_LOGGER
				m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, L"Marker index beyond current buffer, rewinding one sample.");
#endif
				
				ulMarkerIndex -= m_ulSampleSize;
			}
#ifdef APACHE_LOGGER
			m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
								L"Marker bit index calculated as %d.", ulMarkerIndex );
#endif

			rtimeBuffer = _AdjustTime( rtimeBuffer, ulMarkerIndex, m_ulSampleRate, ci64MarkerTimeOffset );

			m_ulLastMarkerIndex = ulMarkerIndex;
		}

	}

	rulMarkerBitRate = m_ulMarkerBitRate;

	// Subtract DC offset from data (including current overlap and excluding future overlap)
	emswbSub1( ADC_OFFSET, (short *)&rausData[ ulStartOffset ], m_ulSampleSize, NSP_NO_SCALE, NULL );

	// Compute sample mean and RMS of input A/D data
	m_lAGCIndex += AGC_SAMPLE_SIZE;

	if ( m_lAGCIndex > m_ulSampleSize - AGC_SAMPLE_SIZE)
		m_lAGCIndex = 0;

	rdAGCMean = (float)emswMean( (short *)&rausData[ m_lAGCIndex ], AGC_SAMPLE_SIZE );

	rdAGCRMS = 0.0;

	for ( lIdx = 0; lIdx < AGC_SAMPLE_SIZE; lIdx++)
	{
		fTempdata = (float)((short)rausData[lIdx + m_lAGCIndex]);
		rdAGCRMS += fTempdata*fTempdata;
	}

	rdAGCRMS /= AGC_SAMPLE_SIZE;
	rdAGCRMS = (float)sqrt( fabs( rdAGCRMS - rdAGCMean * rdAGCMean ) );

	return bRet;
}

CEMSWaveEx* 
CEMSChannelProcessor::DigitalDownConvert(	const bool cbModulated, const CEMSWaveEx* cpWave )
{
	CEMSWaveEx* pRet = 0;

	// This could be based on satellite identifier.
	IEMSSignalConditioner* pSC = 0;


	BYTE* abyWaveIn = 0;
	BYTE* abyWaveOut = 0;

	try
	{
		pSC = _GetDownConverter( cbModulated );

		if( !pSC )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		CEMSWaveEx oWave( *cpWave );

		DWORD dwBytesIn = oWave.Serialize( abyWaveIn );

		ULONG ulBytesOut = 0;
		EMS_RESULT hr = pSC->Process( dwBytesIn, abyWaveIn, &ulBytesOut, &abyWaveOut );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pSC->Release();
		pSC = 0;

		pRet = new CEMSWaveEx;

		if( !pRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		BYTE* abyWaveSerialize = abyWaveOut;

		pRet->Deserialize( abyWaveSerialize, ulBytesOut );

		delete[] abyWaveIn;
		abyWaveIn = 0;

		CoTaskMemFree( abyWaveOut );
		abyWaveOut = 0;
	
	}
	catch( ... )
	{
		if( pSC )
		{
			pSC->Release();
			pSC = 0;
		}

		if( abyWaveIn )
		{
			delete[] abyWaveIn;
			abyWaveIn = 0;
		}

		if( abyWaveOut )
		{
			CoTaskMemFree( abyWaveOut );
			abyWaveOut = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSChannelProcessor::Demodulate( CEMSWaveEx& roWaveIn, CEMSWaveEx& roWaveOut )
{
	m_oDemod.Process( roWaveIn, roWaveOut );
}

void 
CEMSChannelProcessor::ComputePowerSpectrum( const TDemodulatedPhase crDemodPhase,
											const ULONG culMarkerBitRate,
											const LONG clFilterSizeFactor,
											WORD& rwFFTCount, 
											double& rdFFTBinSize,
											TCollectorPsd& rIntegratedPS,
											TCollectorFft& rFFT,
											TCollectorPower& rPS)
{
	static const EMSCOMPLEX s_cacmlpxFreqWindow[3] = {{-0.5,-0.5},{1.0,1.0},{-0.5,-0.5}};
    NSPFirState	EMSFreqWindowState;

    float	fScaleFactor = (float)FFT_SCALE;	// FFT scale factor
    long	i=0;
    long	lCountLog2=0;							// FFT size log base 2
	int		nRawIndex = 0, nOverlapBlockSize=0, nNonOverlapBlockSize=0;

	rwFFTCount = (WORD)(FFT_SIZE / clFilterSizeFactor);

	nOverlapBlockSize = (int)( rwFFTCount * OVERLAP_PERCENT );

	nNonOverlapBlockSize = rwFFTCount - nOverlapBlockSize;

	// Determine FFT bin size from estimate of sample rate (only if reasonable ??)
	if ( culMarkerBitRate > (ULONG)((float)m_ulSampleRate * 0.9) )
		rdFFTBinSize = (double)( ( (double)culMarkerBitRate ) / (double)FFT_SIZE ) ; 
	else
		rdFFTBinSize = ( (double)m_ulSampleRate ) / (double)FFT_SIZE ; 

	lCountLog2 = CEMSBase2::Log( rwFFTCount );               // FFT size logarithm base 2

	emscFirInit( s_cacmlpxFreqWindow, 3, NULL, &EMSFreqWindowState );

	// Zero out the integrated power vector
	emssbSet( 0.0, &rIntegratedPS[0], PSD_SIZE );

	nRawIndex = 0;

	{
		float afTempRaw[ FFT_SIZE ];
		short asTemp[ FFT_SIZE ];

		const short* cpbyDemodPhase = &(crDemodPhase[0][0]);

		for ( i = 0; i < MAX_FFTS; i++ )
		{
			memcpy( asTemp, cpbyDemodPhase, rwFFTCount*sizeof(short) );
			cpbyDemodPhase += nNonOverlapBlockSize;

			// Convert integer phase data to floating point
			emssbIntToFloat( asTemp, afTempRaw, rwFFTCount, 16, NSP_Noflags );

			// Normalize phase data by maximum value
			emssbMpy1( fScaleFactor, afTempRaw, rwFFTCount );

			// Perform not-in-place FFT
			emssRealFftNip( afTempRaw, &rFFT[i][0], lCountLog2, NSP_Forw );

			// Filter in frequency domain (required for CBC processing)
			EMSCOMPLEX	acmplxTempFreq[ FFT_SIZE ];
			emscbFir( &EMSFreqWindowState, &rFFT[i][0], acmplxTempFreq, rwFFTCount/2 );

			// Compute magnitudes of complex FFT vector
			emscbPowerSpectr( acmplxTempFreq, &rPS[i][0], rwFFTCount/2 );

			// Integrate power vectors (not first FFT vector)
			if (i>0)
				emssbAdd2( &rPS[i][0], &rIntegratedPS[0], rwFFTCount/2 );
		}

	}

	emsFirFree( &EMSFreqWindowState );
}

void 
CEMSChannelProcessor::ComputePowerSpectrumNoPLL( short*& rausData,
											const ULONG culMarkerBitRate,
											const LONG clFilterSizeFactor,
											WORD& rwFFTCount, 
											double& rdFFTBinSize,
											TCollectorPsd& rIntegratedPS,
											TCollectorFft& rFFT,
											TCollectorPower& rPS )
{
	// Temporary storage buffer of frequency domain data
	EMSCOMPLEX	acmplxTempFreq[ FFT_SIZE * 4 ];	

	static const EMSCOMPLEX s_cacmplxFreqWindow[3] = {{-0.5,-0.5},{1.0,1.0},{-0.5,-0.5}};
    NSPFirState	EMSFreqWindowState;

	// FFT scale factor
    float	fScaleFactor = (float)FFT_SCALE;	
    long	i = 0;
	
	// FFT size log base 2
    long	nCountLog2 = 0;	
	
	int		nRawIndex = 0, nOverlapBlockSize, nNonOverlapBlockSize;
	int		nIndex = 0, nStartFFTindex = 0;

	rwFFTCount = (WORD)(FFT_SIZE / clFilterSizeFactor);

	nOverlapBlockSize = (int)( rwFFTCount * OVERLAP_PERCENT );

	nNonOverlapBlockSize = rwFFTCount - nOverlapBlockSize;

	// Determine FFT bin size from estimate of sample rate (only if reasonable ??)
	if ( culMarkerBitRate > (ULONG)((float)m_ulSampleRate * 0.9) )
		rdFFTBinSize = (double)( ( (double)culMarkerBitRate ) / (double)FFT_SIZE ) ; 
	else
		rdFFTBinSize = ( (double)SAMPLE_RATE ) / (double)FFT_SIZE ; 

	nCountLog2 = CEMSBase2::Log( rwFFTCount ); // FFT size logarithm base 2
 
	emscFirInit( s_cacmplxFreqWindow, 3, NULL, &EMSFreqWindowState );

	// Zero out the integrated power vector
	emssbSet( 0.0, &rIntegratedPS[0], PSD_SIZE );

	nRawIndex = 0;

	nStartFFTindex = 0;
	nIndex = 0;

	int jj = 0;
	int ii = 0;


	// Wideband expects 500000 for the phase demod system
	float fInterpolationFactor = ((float)culMarkerBitRate/500000.0);

	// Establish Bin Size based upon upconverted sample rate
	rdFFTBinSize /= (double)fInterpolationFactor;

	{
		float afTempRaw[ FFT_SIZE ];

		for (	i = 0; 
				i < MAX_FFTS;
				i++ )
		{
			// Convert integer phase data to floating point
			float fFactor = 0;
			for ( int kk = 0; kk<rwFFTCount; kk++ )
			{
				jj = (int)((float)ii * fInterpolationFactor);
				fFactor = ((float)ii * fInterpolationFactor) - jj;

				afTempRaw[kk] = (float)rausData[jj]*(1.0-fFactor) + (float)rausData[jj+1] * fFactor;
				ii++;
			}

			// Normalize phase data by maximum value
			emssbMpy1( fScaleFactor, afTempRaw, rwFFTCount );

			// Perform not-in-place FFT
			emssRealFftNip( afTempRaw, acmplxTempFreq, nCountLog2, NSP_Forw );

			emscbCopy( &acmplxTempFreq[nStartFFTindex], &rFFT[i][0], rwFFTCount/2 );

			// Filter in frequency domain (required for CBC processing)
			emscbFir( &EMSFreqWindowState, &rFFT[i][0], acmplxTempFreq, rwFFTCount/2 );

			// Compute magnitudes of complex FFT vector
			emscbPowerSpectr( acmplxTempFreq, &rPS[i][0], rwFFTCount/2 );

			// Integrate power vectors (not first FFT vector)
			emssbAdd2( &rPS[i][0], &rIntegratedPS[0], rwFFTCount/2 );

			// go back 12.5 percent
			ii -= nOverlapBlockSize;

		}
	}

	// Fix Spectrum Plot by adding a filter to the frequencies beyond 200kHz
	double dFiltFactor = 1.0;
	for ( ii = (int)(rwFFTCount*2/5); ii < (int)(rwFFTCount/2); ii++ )
	{
		rIntegratedPS[ii] *= dFiltFactor;
		dFiltFactor *= 0.9925;
		if ( rIntegratedPS[ii] < 1.1 ) rIntegratedPS[ii] = (float)1.1;
	}

	// Setup for next one second data buffer
	if ( ( nIndex > 0 ) )
		emswbCopy( (const short *)&rausData[ nIndex ], (short*)&rausData[ 0 ], FFT_SIZE*2/5 );

	emsFirFree( &EMSFreqWindowState );
}

IEMSSignalConditioner* 
CEMSChannelProcessor::_GetDownConverter( const bool cbModulated )
{
	IEMSSignalConditioner* pRet = 0;
	IUnknown* pUnk = 0;

	try
	{
		if( cbModulated )
		{
			if( !m_pModulatedDC )
			{
				EMS_RESULT hr = CEMSPlugInLoader::LoadPlugIn( m_owszModulatedDCPluginID.c_str(), pUnk );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				if( !pUnk )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				hr = pUnk->QueryInterface( IID_IEMSSignalConditioner, (void**) &m_pModulatedDC );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				pUnk->Release();
				pUnk = 0;

			}

			if( !m_pModulatedDC )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet = m_pModulatedDC;
			pRet->AddRef();
		}
		else
		{
			if( !m_pUnModulatedDC )
			{
				EMS_RESULT hr = CEMSPlugInLoader::LoadPlugIn( m_owszUnModulatedDCPluginID.c_str(), pUnk );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				if( !pUnk )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				hr = pUnk->QueryInterface( IID_IEMSSignalConditioner, (void**) &m_pUnModulatedDC );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				pUnk->Release();
				pUnk = 0;
			}

			if( !m_pUnModulatedDC )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet = m_pUnModulatedDC;
			pRet->AddRef();
		}
	}
	catch( ... )
	{
		if( pUnk )
		{
			pUnk->Release();
			pUnk = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

EMSTIME
CEMSChannelProcessor::_AdjustTime( const EMSTIME ctimeCurrent, const ULONG culMarkerIndex,
								  const ULONG culSampleRate, const INT64 ci64MarkerTimeOffset )
{	
	EMSTIMEFIELDS	timeFields;

	const ULONG culMarkerBitPeriod = 1;

	CEMSTime timeBuffer( ctimeCurrent );

#ifdef APACHE_LOGGER
	m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
						 L"Original Data Buffer Time = %s (%I64d).", 
						 CEMSConversionUtil::ConvertToDateTimeHiResStringW( ctimeCurrent ).c_str(),
						 ctimeCurrent.intTime );
#endif

	double dFactor = ( (double) culMarkerIndex / ((double) culSampleRate) );
	
	LONG lNanoseconds =  (LONG)( c_dNanoSecsPerSec * dFactor );

#ifdef APACHE_LOGGER
	m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__,
						L"Nanosecond offset = %d.", lNanoseconds );
#endif

	timeBuffer.AddNanoseconds( lNanoseconds );

	timeBuffer.GetTime( &timeFields );

	// we know that marker is exactly at the 1/2 second mark on the TrueTime Board

	timeFields.lNanosecond = (long)( 1e9 * (double) culMarkerBitPeriod / 2 );

	timeBuffer.SetTime( &timeFields );

	// note: for the TrueTime board - Pulse is 1/2 sec wide - trailing trigger
	//timeBuffer.AddSeconds( +(float)EMS_MARKER_BIT_PERIOD / 2.0f );

	timeBuffer.AddNanoseconds( -lNanoseconds );

	timeBuffer.AddNanoseconds( (long) ci64MarkerTimeOffset );

	float fSecond = fabs( timeBuffer.SecondsDifferent( m_timeLastCorrected ) );
	
#ifdef APACHE_LOGGER
	m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__,
					L"Difference between time of last buffer and this buffer is %f seconds.", fSecond );
#endif

	if( fSecond > 1.1 )
	{
#ifdef APACHE_LOGGER
		m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
			L"Difference between consecutive buffers exceeds 1.1 seconds. Last time = %s, this time = %s.",
			CEMSConversionUtil::ConvertToDateTimeHiResStringW( m_timeLastCorrected ).c_str(),
			CEMSConversionUtil::ConvertToDateTimeHiResStringW( timeBuffer ).c_str() );
#endif

	}
	else if( fSecond < 1.0 )
	{
#ifdef APACHE_LOGGER
		m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
			L"Difference between consecutive buffers less than 1.0 second. Last time = %s, this time = %s.",
			CEMSConversionUtil::ConvertToDateTimeHiResStringW( m_timeLastCorrected ).c_str(),
			CEMSConversionUtil::ConvertToDateTimeHiResStringW( timeBuffer ).c_str() );
#endif

	}

	m_timeLastCorrected.SetTime( timeBuffer );		// keep track of last corrected time

#ifdef APACHE_LOGGER
	m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
			 L"Adjusted Time = %s (%I64d).", 
			 CEMSConversionUtil::ConvertToDateTimeHiResStringW( timeBuffer ).c_str(),
			 ((EMSTIME) timeBuffer).intTime );
#endif

	
	return timeBuffer;
}
