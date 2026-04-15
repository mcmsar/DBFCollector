/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#include "sptools.h"
#include "emsexcpt.h"
#include "base2.h"
#include "emstime.h"
#include <math.h>
#include <crtdbg.h>

CEMSSPTools::CEMSSPTools()
{
}

CEMSSPTools::CEMSSPTools( const CEMSSPTools& x )
{
}

CEMSSPTools::~CEMSSPTools()
{
}

double 
CEMSSPTools::GetFrequencyComponents( const EMSCOMPLEX* cacmplxRawBurstFreq, const double cdFrequency0,
							    const ULONG culZoomSize, const ULONG culWindowWidth,
								const ULONG culFFTElements, const float cfBinSize, 
								long& rlDopplerPeakIndex, long& rlDopplerStartIndex, 
								long& rlDopplerEndIndex, 
								long& rlAdjustedDopplerPeakIndex, EMSCOMPLEX* acmplxNodBurstFreq )
{
	double dRet = 0.0;

	double*	adWTemp = 0;
	EMSCOMPLEX*	acmplxTemp = 0;
	float*	afTemp = 0;
	
	try
	{
		if( rlDopplerStartIndex > 0 &&
			rlDopplerEndIndex > 0 )
		{
			if( culWindowWidth < 1 )
			{
				THROW_INVALID_ARG_EXCEPTION();
			}

			adWTemp = new double[ culWindowWidth ];

			if( !adWTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( adWTemp, 0, culWindowWidth*sizeof(double) );

			if( culFFTElements < 1 )
			{
				THROW_INVALID_ARG_EXCEPTION();
			}

			acmplxTemp = new EMSCOMPLEX[ culFFTElements ];

			if( !acmplxTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( acmplxTemp, 0, culFFTElements*sizeof(EMSCOMPLEX) );

			afTemp = new float[ culFFTElements ];

			if( !afTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( afTemp, 0, culFFTElements*sizeof(float) );

			double	dTemp1 = 0.0;
			double dTemp2 = 0.0;
			float	fIdxCorrection = 0.0;
			ULONG	n = 0;
			long lDopplerBand = 0; 
			long lIdxPowerMax = 0;
			long lIdx = 0; 
			long lCorrLength = 0;

			// Convolve frequency domain with the extracted carrier.
			emscbZero( acmplxNodBurstFreq, culZoomSize );
			lDopplerBand = rlDopplerEndIndex - rlDopplerStartIndex + 1;

			lCorrLength = 1;
			if (lDopplerBand < lCorrLength)
			{
				lIdx = rlDopplerStartIndex - (lCorrLength-lDopplerBand)/2;
				rlDopplerStartIndex = lIdx;
			}
			else
			{
				lCorrLength = lDopplerBand;
				lIdx = rlDopplerStartIndex;
			}

			_ASSERTE( lIdx < (long) culZoomSize );
			if( lIdx >= (long) culZoomSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			_ASSERTE( lCorrLength <= (long) (culZoomSize - lIdx) );
			if( lCorrLength > (long) (culZoomSize - lIdx) )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			_ASSERTE( lCorrLength <= (long) culFFTElements );
			if( lCorrLength > (long) culFFTElements )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			emscbConj2( &cacmplxRawBurstFreq[lIdx], acmplxTemp, lCorrLength );

			for( n = 0; n < culFFTElements; n++ )
			{
				_ASSERTE( n < culZoomSize );
				if( n >= culZoomSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( lCorrLength <= (long) culFFTElements );
				if( lCorrLength > (long) culFFTElements )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( lCorrLength <= (long) (culZoomSize - n ) );
				if( lCorrLength > (long) (culZoomSize - n ) )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				
				acmplxNodBurstFreq[n] = emscDotProd( acmplxTemp, &cacmplxRawBurstFreq[n], lCorrLength );
			}

			_ASSERTE( culFFTElements <= culZoomSize );
			if( culFFTElements > culZoomSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			emscbPowerSpectr( acmplxNodBurstFreq, afTemp, culFFTElements );

			emssMaxExt( afTemp, culFFTElements, (int *)&lIdxPowerMax );

			rlAdjustedDopplerPeakIndex = lIdxPowerMax;


			// Apply a window function to the frequency domain data surrounding
			// the carrier frequency only. If minimum frequency drift within burst,
			// use raw uncorrected frequency data in lieu of the corrected data.  
			
			lIdxPowerMax = rlDopplerPeakIndex;
    
			for( n = 0; n < culWindowWidth; n++ )
			{
				_ASSERTE( (lIdxPowerMax - 1 + n) < culZoomSize );
				if( (lIdxPowerMax - 1 + n) >= culZoomSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( (lIdxPowerMax - 2 + n) < culZoomSize );
				if( (lIdxPowerMax - 2 + n) >= culZoomSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				dTemp1      = cacmplxRawBurstFreq[ lIdxPowerMax - 1 + n ].re -
							 (float) 0.5 * ( cacmplxRawBurstFreq[ lIdxPowerMax - 2 + n ].re +
								  cacmplxRawBurstFreq[ lIdxPowerMax + n ].re );
				dTemp2      = cacmplxRawBurstFreq[ lIdxPowerMax - 1 + n ].im -
							 (float) 0.5 * ( cacmplxRawBurstFreq[ lIdxPowerMax - 2 + n ].im +
								  cacmplxRawBurstFreq[ lIdxPowerMax + n ].im );

				_ASSERTE( n < culWindowWidth );
				if( n >= culWindowWidth )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				adWTemp[ n ] = dTemp1 * dTemp1 + dTemp2 * dTemp2;
			}

			// Perform an interpolation on the filtered frequency domain data
			// surrounding the carrier frequency
			
			_ASSERTE( culWindowWidth >= 3 );
			if( culWindowWidth < 3 )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			adWTemp[0] = ( adWTemp[0] > 0.0 ) ? log(adWTemp[0]) : -100.0;
			adWTemp[1] = ( adWTemp[1] > 0.0 ) ? log(adWTemp[1]) : -100.0;
			adWTemp[2] = ( adWTemp[2] > 0.0 ) ? log(adWTemp[2]) : -100.0;

			dTemp1 =  0.5 * ( adWTemp[2] - adWTemp[0] );
			dTemp2 =  2.0 * adWTemp[1] - adWTemp[2] - adWTemp[0];
			if (fabs(dTemp2) < 1e-10)
				fIdxCorrection = 0.0;
			else
				fIdxCorrection =  (float)(dTemp1 / dTemp2);

			// Limit correction to 1 frequency bin
			if ( fIdxCorrection > 2.0 ) fIdxCorrection = 2.0;
			if ( fIdxCorrection < -2.0 ) fIdxCorrection = -2.0;
			

			dRet = ( (((double)lIdxPowerMax + fIdxCorrection) * cfBinSize) + cdFrequency0 );

			if( adWTemp )
			{
				delete[] adWTemp;
				adWTemp = 0;
			}

			if( acmplxTemp )
			{
				delete[] acmplxTemp;
				acmplxTemp = 0;
			}

			if( afTemp )
			{
				delete[] afTemp;
				afTemp = 0;
			}
		}
	}
	catch( ... )
	{
		if( adWTemp )
		{
			delete[] adWTemp;
			adWTemp = 0;
		}

		if( acmplxTemp )
		{
			delete[] acmplxTemp;
			acmplxTemp = 0;
		}

		if( afTemp )
		{
			delete[] afTemp;
			afTemp = 0;
		}

		throw;
	}

	return dRet;
}

void 
CEMSSPTools::DoKaiserBesselWindow( const EMSCOMPLEX* cacmplxFilter, const EMSCOMPLEX* cacmplxData,
										const ULONG culSize, const ULONG culOffset,
										EMSCOMPLEX* acmplxOutput )
{
	_ASSERTE( culOffset < culSize );
	if( culOffset >= culSize )
	{
		THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
	}
	emscbMpy3 ( cacmplxFilter, &cacmplxData[culOffset], acmplxOutput, culSize - culOffset );
    
	emscbMpy3 ( &cacmplxFilter[culSize - culOffset], 
			cacmplxData, &acmplxOutput[culSize - culOffset],  culOffset );
}

void
CEMSSPTools::FrameSynch ( const EMSCOMPLEX* cacmplxData, const EMSCOMPLEX* cacmplxFBS, 
						 const ULONG culSize, float& rfFSMax, 
						 long& rlFSIndex )
{
	EMSCOMPLEX* acmplxTempTime = 0;
	EMSCOMPLEX* acmplxTempFreq = 0;
	float* afTempPower = 0;

	try
	{
		if( culSize < 1 )
		{
			THROW_INVALID_ARG_EXCEPTION();
		}

		acmplxTempTime = new EMSCOMPLEX[ culSize ];

		if( !acmplxTempTime )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( acmplxTempTime, 0, culSize*sizeof(EMSCOMPLEX) );

		acmplxTempFreq = new EMSCOMPLEX[ culSize ];

		if( !acmplxTempFreq )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( acmplxTempFreq, 0, culSize*sizeof(EMSCOMPLEX) );

		afTempPower = new float[ culSize ];

		if( !afTempPower )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( afTempPower, 0, culSize*sizeof(float) );


		rfFSMax = 0.0;
		rlFSIndex = 0;

		emscbMpy3( cacmplxFBS, cacmplxData, acmplxTempFreq, culSize );
		emscFftNip( acmplxTempFreq, acmplxTempTime, CEMSBase2::Log(culSize), EMS_SPL_INV );
		emscbPowerSpectr( acmplxTempTime, afTempPower, culSize );
		rfFSMax   = emssMaxExt( afTempPower, culSize, (int *)&rlFSIndex );

		if( acmplxTempTime )
		{
			delete[] acmplxTempTime;
			acmplxTempTime = 0;
		}

		if( acmplxTempFreq )
		{
			delete[] acmplxTempFreq;
			acmplxTempFreq = 0;
		}

		if( afTempPower )
		{
			delete[] afTempPower;
			afTempPower = 0;
		}
	}
	catch( ... )
	{
		if( acmplxTempTime )
		{
			delete[] acmplxTempTime;
			acmplxTempTime = 0;
		}

		if( acmplxTempFreq )
		{
			delete[] acmplxTempFreq;
			acmplxTempFreq = 0;
		}

		if( afTempPower )
		{
			delete[] afTempPower;
			afTempPower = 0;
		}

		throw;
	}
}

double 
CEMSSPTools::GetTimeOffset( const long clOffsetIndex, const double cdSampleRate )
{
	return ((double) clOffsetIndex ) / cdSampleRate ;
}




void 
CEMSSPTools::GetFrameSynchFilter( const long* calFS, const ULONG culFSSize, 
							const ULONG culSize, const float cfBitSize,
							EMSCOMPLEX* acmplxFBS )
{
	float* afTemp = 0;
	EMSCOMPLEX* acmplxTemp = 0;

	try
	{
		_ASSERTE( culSize > 0 );
		
		afTemp = new float[ culSize ];

		if( !afTemp )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		acmplxTemp = new EMSCOMPLEX[ culSize ];

		if( !acmplxTemp )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

	
		ULONG    j, k, n, len = 0;

		emssbZero( afTemp, culSize );
		emscbZero( acmplxTemp, culSize );
        

		for( j = 0; j < culFSSize; j++ )
		{
			n    = (long) ( (cfBitSize * 10.0) * j + 0.5 );
			len  = (long) ( (cfBitSize * 10.0) * (j + 1) + 0.5 - n );
			for( k = 0; k < len; k++ )
			{
				if( k < len / 2 )
				{
					_ASSERTE( n < culSize );
					if( n >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culFSSize );
					if( j >= culFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp[n++]   = (float) calFS[j];

				}
				else
				{
					_ASSERTE( n < culSize );
					if( n >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culFSSize );
					if( j >= culFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp[n++]   = (float) ( -calFS[j] );
				}
			}
		}

		for( j = 0 ; j < n; j += 10 )
		{
			_ASSERTE( (j/10) < culSize );
			if( (j/10) >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			_ASSERTE( j < culSize );
			if( j >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			acmplxTemp[j / 10].re = afTemp[j];
		}

		_ASSERTE( ( (ULONG) CEMSBase2::Log(culSize)) <= culSize );
		if( (ULONG) CEMSBase2::Log(culSize) >= culSize )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}

		emscFftNip( acmplxTemp, acmplxFBS, CEMSBase2::Log(culSize) , EMS_SPL_FWD );

		emssbMpy1( ((float)1.0)/(float)culSize, (float *)acmplxFBS, 2*culSize );
		emscbConj1( acmplxFBS, culSize );
 
		if( afTemp )
		{
			delete[] afTemp;
			afTemp = 0;
		}

		if( acmplxTemp )
		{
			delete[] acmplxTemp;
			acmplxTemp = 0;
		}
	}

	catch( ... )
	{
		if( afTemp )
		{
			delete[] afTemp;
			afTemp = 0;
		}

		if( acmplxTemp )
		{
			delete[] acmplxTemp;
			acmplxTemp = 0;
		}

		throw;
	}

		
}


void 
CEMSSPTools::GetFrameSynchFilter( const long* calMFS, const ULONG culMFSSize, 
								 const long* calTFS, const ULONG culTFSSize,
							const ULONG culSize, const float cfBitSize,
							EMSCOMPLEX* acmplxBurstFilter, EMSCOMPLEX* acmplxFBSReal,
							EMSCOMPLEX* aFBSTest )
{
	float* afTemp1 = 0;
	float* afTemp2 = 0;
	EMSCOMPLEX* acmplxTemp1 = 0;
	EMSCOMPLEX* acmplxTemp2 = 0;

	try
	{
		_ASSERTE( culSize > 0 );
		
		afTemp1 = new float[ culSize ];

		if( !afTemp1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		afTemp2 = new float[ culSize ];

		if( !afTemp2 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		acmplxTemp1 = new EMSCOMPLEX[ culSize ];

		if( !acmplxTemp1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		acmplxTemp2 = new EMSCOMPLEX[ culSize ];

		if( !acmplxTemp2 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		
		float   fWFact, fDB, fB, fBeslfak = 5.0;
		ULONG    j, k, n, len = 0;
		ULONG	nkwin, nkwin2, nkwin16 = 0;

		emssbZero( afTemp1, culSize );
		emssbZero( afTemp2, culSize );
		emscbZero( acmplxTemp1, culSize );
		emscbZero( acmplxTemp2, culSize );
        
		//nkwin   = culSize/4;
		nkwin   = culSize/4/8;
		nkwin2  = nkwin/2;
		nkwin16 = nkwin/16;


		for( j = 0; j < 24; j++ )
		{
			n    = (long) ( (cfBitSize * 10.0) * j + 0.5 );
			len  = (long) ( (cfBitSize * 10.0) * (j + 1) + 0.5 - n );
			for( k = 0; k < len; k++ )
			{
				if( k < len / 2 )
				{
					_ASSERTE( n < culSize );
					if( n >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culMFSSize );
					if( j >= culMFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp1[n]   = (float) calMFS[j];

					_ASSERTE( (n+1) < culSize );
					if( (n+1) >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culTFSSize );
					if( j >= culTFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp2[n++] = (float) calTFS[j];
				}
				else
				{
					_ASSERTE( n < culSize );
					if( n >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culMFSSize );
					if( j >= culMFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp1[n]   = (float) ( -calMFS[j] );

					_ASSERTE( (n+1) < culSize );
					if( (n+1) >= culSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					_ASSERTE( j < culTFSSize );
					if( j >= culTFSSize )
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
					afTemp2[n++] = (float) ( -calTFS[j] );
				}
			}
		}

		for( j = 0 ; j < n; j += 10 )
		{
			_ASSERTE( (j/10) < culSize );
			if( (j/10) >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			_ASSERTE( j < culSize );
			if( j >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			acmplxTemp1[j / 10].re = afTemp1[j];
			acmplxTemp2[j / 10].re = afTemp2[j];
		}

		_ASSERTE( ( (ULONG) CEMSBase2::Log(culSize)) <= culSize );
		if( (ULONG) CEMSBase2::Log(culSize) >= culSize )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}

		emscFftNip( acmplxTemp1, acmplxFBSReal, CEMSBase2::Log(culSize) , EMS_SPL_FWD );

		emssbMpy1( ((float)1.0)/(float)culSize, (float *)acmplxFBSReal, 2*culSize );
		emscbConj1( acmplxFBSReal, culSize );
    
		emscFftNip( acmplxTemp2, aFBSTest, CEMSBase2::Log(culSize) , EMS_SPL_FWD );
		emssbMpy1( ((float)1.0)/(float)culSize, (float *)aFBSTest, 2*culSize );
		emscbConj1( aFBSTest, culSize );

		//  Setup kaiser window
		_ASSERTE( (nkwin2+1) <= culSize );
		if( (nkwin2+1) >= culSize )
		{
			THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
		}
		emssbZero( afTemp1, nkwin2+1 );
		for( n = 0; n <= nkwin2; n++ )
		{
			fWFact = (nkwin2 - n) / (float) nkwin2;
			fWFact = (float) ( 0.5 * fBeslfak * sqrt( 1.0 - fWFact * fWFact ) );
			for( j = 1, fB = 1.0, fDB = 1.0; fDB/fB > 1e-4; j++ )
			{
				fDB *= (fWFact / j);
				fB  += (fDB * fDB);
			}
			_ASSERTE( n < culSize );
			if( n >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			afTemp1[n] = fB;
		}

		//  Setup zoom window
		for( n = 0; n < culSize; n++ )
		{
			if( n < nkwin16 )
			{
				_ASSERTE( (n*8) < culSize );
				if( (n*8) >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( nkwin2 < culSize );
				if( nkwin2 >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( afTemp1[nkwin2] > 0.0 );
				if( afTemp1[nkwin2] == 0.0 )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				fWFact = afTemp1[n * 8] / afTemp1[nkwin2];
			}
			else if ( n > (culSize - nkwin16))
			{
				_ASSERTE( (8 * (culSize - n)) < culSize );
				if( (8 * (culSize - n)) >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( nkwin2 < culSize );
				if( nkwin2 >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( afTemp1[nkwin2] > 0.0 );
				if( afTemp1[nkwin2] == 0.0 )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				fWFact = afTemp1[8 * (culSize - n)] / afTemp1[nkwin2];
			}
			else if( (n < nkwin2) || (n > culSize - nkwin2) )
				fWFact = 1.0;
			else if( n < nkwin )
			{
				_ASSERTE( (nkwin - n) < culSize );
				if( (nkwin - n) >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( nkwin2 < culSize );
				if( nkwin2 >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( afTemp1[nkwin2] > 0.0 );
				if( afTemp1[nkwin2] == 0.0 )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				fWFact = afTemp1[nkwin - n] / afTemp1[nkwin2];
			}
			else if( n >= culSize - nkwin )
			{
				_ASSERTE( (n - culSize + nkwin) < culSize );
				if( (n - culSize + nkwin) >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( nkwin2 < culSize );
				if( nkwin2 >= culSize )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				_ASSERTE( afTemp1[nkwin2] > 0.0 );
				if( afTemp1[nkwin2] == 0.0 )
				{
					THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
				}
				fWFact = afTemp1[n - culSize + nkwin] / afTemp1[nkwin2];
			}
			else
				fWFact = 0.0;

			_ASSERTE( n < culSize );
			if( n >= culSize )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}
			acmplxBurstFilter[n].re = fWFact;
			acmplxBurstFilter[n].im = 0.0;
		}

		if( afTemp1 )
		{
			delete[] afTemp1;
			afTemp1 = 0;
		}

		if( afTemp2 )
		{
			delete[] afTemp2;
			afTemp2 = 0;
		}

		if( acmplxTemp1 )
		{
			delete[] acmplxTemp1;
			acmplxTemp1 = 0;
		}

		if( acmplxTemp2 )
		{
			delete[] acmplxTemp2;
			acmplxTemp2 = 0;
		}
	}
	catch( ... )
	{
		if( afTemp1 )
		{
			delete[] afTemp1;
			afTemp1 = 0;
		}

		if( afTemp2 )
		{
			delete[] afTemp2;
			afTemp2 = 0;
		}

		if( acmplxTemp1 )
		{
			delete[] acmplxTemp1;
			acmplxTemp1 = 0;
		}

		if( acmplxTemp2 )
		{
			delete[] acmplxTemp2;
			acmplxTemp2 = 0;
		}

		throw;
	}

    
}


void 
CEMSSPTools::GetBitsSynchFilter( const long* calMFS, const ULONG culBitNum, const ULONG culSize,
								 const float cfBitSize, EMSCOMPLEX* acmplxBurstFilter, EMSCOMPLEX* acmplxFBSReal )
{
	float* afTemp1 = 0;
	EMSCOMPLEX* acmplxTemp1 = 0;

	try
	{
		ULONG ulSize = culBitNum * ((ULONG)cfBitSize + 1) * 10;
		afTemp1 = new float[ ulSize ];

		if( !afTemp1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		acmplxTemp1 = new EMSCOMPLEX[ culSize ];

		if( !acmplxTemp1 )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		float   fWFact, fDB, fB, fBeslfak = 5.0;
		ULONG    j, k, n, len = 0;
		ULONG	nkwin, nkwin2, nkwin16 = 0;

		emssbZero( afTemp1, ulSize );
		emscbZero( acmplxTemp1, culSize );
        
		nkwin   = culSize/4/8;
		nkwin2  = nkwin/2;
		nkwin16 = nkwin/16;


		for( j = 0; j < culBitNum; j++ )
		{
			n    = (long) ( (cfBitSize * 10.0) * j + 0.5 );
			len  = (long) ( (cfBitSize * 10.0) * (j + 1) + 0.5 - n );
			for( k = 0; k < len; k++ )
			{
				if( k < len / 2 )
				{
					afTemp1[n++]   = (float) calMFS[j];
				}
				else
				{
					afTemp1[n++]   = (float) ( -calMFS[j] );
				}
			}
		}

		for( j = 0 ; j < n; j += 10 )
		{
			acmplxTemp1[j / 10].re = afTemp1[j];
		}

		emscFftNip( acmplxTemp1, acmplxFBSReal, CEMSBase2::Log(culSize) , EMS_SPL_FWD );
		emssbMpy1( ((float)1.0)/(float)culSize, (float *)acmplxFBSReal, 2*culSize );
		emscbConj1( acmplxFBSReal, culSize );
    
		//  Setup kaiser window
		emssbZero( afTemp1, nkwin2+1 );
		for( n = 0; n <= nkwin2; n++ )
		{
			fWFact = (nkwin2 - n) / (float) nkwin2;
			fWFact = (float) ( 0.5 * fBeslfak * sqrt( 1.0 - fWFact * fWFact ) );
			for( j = 1, fB = 1.0, fDB = 1.0; fDB/fB > 1e-4; j++ )
			{
				fDB *= (fWFact / j);
				fB  += (fDB * fDB);
			}
			afTemp1[n] = fB;
		}

		//  Setup zoom window
		for( n = 0; n < culSize; n++ )
		{
			if( n < nkwin16 )
				fWFact = afTemp1[n * 8] / afTemp1[nkwin2];
			else if ( n > (culSize - nkwin16))
				fWFact = afTemp1[8 * (culSize - n)] / afTemp1[nkwin2];
			else if( (n < nkwin2) || (n > culSize - nkwin2) )
				fWFact = 1.0;
			else if( n < nkwin )
				fWFact = afTemp1[nkwin - n] / afTemp1[nkwin2];
			else if( n >= culSize - nkwin )
				fWFact = afTemp1[n - culSize + nkwin] / afTemp1[nkwin2];
			else
				fWFact = 0.0;
			acmplxBurstFilter[n].re = fWFact;
			acmplxBurstFilter[n].im = 0.0;
		}

		if( afTemp1 )
		{
			delete[] afTemp1;
			afTemp1 = 0;
		}

		if( acmplxTemp1 )
		{
			delete[] acmplxTemp1;
			acmplxTemp1 = 0;
		}

	}
	catch( ... )
	{
		if( afTemp1 )
		{
			delete[] afTemp1;
			afTemp1 = 0;
		}

		if( acmplxTemp1 )
		{
			delete[] acmplxTemp1;
			acmplxTemp1 = 0;
		}

		throw;
	}

    
}


void
CEMSSPTools::GetBitShapeFilter( float* afFilter, const ULONG culFilterLength, const ULONG culInterval )
{
	if( culInterval > culFilterLength )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	emssbZero( afFilter, culFilterLength );
    emssbSet( 1.0, afFilter, culInterval );
	_ASSERTE( culInterval <= culFilterLength );
    emssbSet(-1.0, &afFilter[culFilterLength-culInterval], culInterval );
}

void
CEMSSPTools::FrameSynchEx( const EMSCOMPLEX* cacmplxData, const EMSCOMPLEX* cacmplxFBS, 
						   const ULONG culSize, float& rfFSMax, 
						   long& rlFSIndex, double& rdFSIndex )
{
	EMSCOMPLEX* acmplxTempTime = 0;
	EMSCOMPLEX* acmplxTempFreq = 0;
	float* afTempPower = 0;

	try
	{
		if( culSize < 1 )
		{
			THROW_INVALID_ARG_EXCEPTION();
		}

		acmplxTempTime = new EMSCOMPLEX[ culSize ];

		if( !acmplxTempTime )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( acmplxTempTime, 0, culSize*sizeof(EMSCOMPLEX) );

		acmplxTempFreq = new EMSCOMPLEX[ culSize ];

		if( !acmplxTempFreq )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( acmplxTempFreq, 0, culSize*sizeof(EMSCOMPLEX) );

		afTempPower = new float[ culSize ];

		if( !afTempPower )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( afTempPower, 0, culSize*sizeof(float) );


		rfFSMax = 0.0;
		rlFSIndex = 0;

		emscbMpy3( cacmplxFBS, cacmplxData, acmplxTempFreq, culSize );
		emscFftNip( acmplxTempFreq, acmplxTempTime, CEMSBase2::Log(culSize), EMS_SPL_INV );
		emscbPowerSpectr( acmplxTempTime, afTempPower, culSize );
		rfFSMax   = emssMaxExt( afTempPower, culSize, (int *)&rlFSIndex );

		rdFSIndex = QuadraticInterpolation ( afTempPower, rlFSIndex );

		if( acmplxTempTime )
		{
			delete[] acmplxTempTime;
			acmplxTempTime = 0;
		}

		if( acmplxTempFreq )
		{
			delete[] acmplxTempFreq;
			acmplxTempFreq = 0;
		}

		if( afTempPower )
		{
			delete[] afTempPower;
			afTempPower = 0;
		}
	}
	catch( ... )
	{
		if( acmplxTempTime )
		{
			delete[] acmplxTempTime;
			acmplxTempTime = 0;
		}

		if( acmplxTempFreq )
		{
			delete[] acmplxTempFreq;
			acmplxTempFreq = 0;
		}

		if( afTempPower )
		{
			delete[] afTempPower;
			afTempPower = 0;
		}

		throw;
	}
}

double
CEMSSPTools::QuadraticInterpolation ( const float* cafPower, const ULONG culIndex )
{ 
	double dIndex = 0.0;
	double dA = 0.0;
	double dB = 0.0;
	double dY1 = 0.0;
	double dY2 = 0.0;
	double dY3 = 0.0;
	
	// Perform a quadratic interpolation
	// Assume  y = a.X^2 + b.X + C
	//		   y1 = Power(ipeak-1)
	//		   y2 = Power(ipeak)
	//		   y3 = Power(ipeak+1)
	// Peak occurs at dy/dx = 0
	//	y1 = a.(-1)*(-1) + b.(-1) + c = a - b + c
	//	y2 = a.( 0)*( 0) + b.( 0) + c = c
	//	y3 = a.(+1)*(+1) + b.(+1) + c = a + b + c

	// a + b = y3 - y2
	// a - b = y1 - y2
	// a     = [y3 - y2 + y1 - y2]/2 = [y3 + y1 - 2.y2]/2
	// b     = [y3 - y2 - y1 + y2]/2 = [y3 - y1]/2

	// dy/dx = 2aX + b = 0  => X = -b/(2a)

	// X = -[y3 - y1] / [y3 + y1 - 2.y2 ] / 2

	dY1 = cafPower[culIndex-1];
	dY2 = cafPower[culIndex];
	dY3 = cafPower[culIndex+1];

	dA  = ( dY3 + dY1 - 2.0 * dY2 ) / 2.0;
	dB  = ( dY3 - dY1 ) / 2.0;


	if( 0.0 != dA )
	{
		dIndex = -dB / ( 2.0 * dA );
	}

	if( dIndex > 1.0 )
	{
		dIndex = 0.0;
	}

	dIndex += (double) culIndex; 
	
	return dIndex;
}