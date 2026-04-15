#include "emsdbfex.h"
#include <iomanip>
#include "EMSCLOCK.H"
#include "TimeElapsed.h"
#include "dbf_iq_demod_lowpass_filters.h"
#include "dbf_ddc_filters1.h"

#if LOG_FILE == 1
FILE*	CTimeElapsed::m_pTimingFile = NULL;
#endif

//FILE* CDigitalBeamFormerEx::m_pLogPhaseBias = NULL;
#define DBF_PROCESSOR_VER	4
UINT UP_SAMPLING_FACTOR = 0;
const ULONG M =5;

CDigitalBeamFormerEx:: CDigitalBeamFormerEx( CEMSQueue<DBFTrackingData >& dbfBeamVect):CDigitalBeamFormer( dbfBeamVect ), m_acDBFBeamVectors( nullptr )
{

}
CDigitalBeamFormerEx::~CDigitalBeamFormerEx()
{
	delete []acIQSeq;
		
	delete []afISeq1;
	
	delete []afQSeq1;
	/*for(int i = 0; i < 31; i++)
	{
		delete [] acIQMatrix[i];
	}
	delete [] acIQMatrix;*/
	if( m_asBeamMatrix )
	{
		for(int i = 0; i < MAX_BEAMS; i++)
		{
			delete []m_asBeamMatrix[i];
		}
		delete []m_asBeamMatrix;

	}
	if( m_acBeamMatrix )
	{
		for(int i = 0; i < MAX_BEAMS; i++)
		{
			delete []m_acBeamMatrix[i];
		}
		delete []m_acBeamMatrix;
	}
	
	delete []m_asMatrix;
	delete []m_acIQMatrix;
	if( m_acFFTdataSum )
		delete []m_acFFTdataSum;
}
EMS_RESULT
CDigitalBeamFormerEx::Initialize( const TCHAR *cDir )
{
	m_asBeamMatrix = NULL;
	m_acBeamMatrix = NULL;
	m_acFFTdataSum = NULL;
	m_dElapsedTime = 0.0;
	m_dAverageTime = 0.0;
	m_nCounter = 0;

	
	m_ulSamplesPerChannel = DBF_SAMPLE_SIZE;
	m_ulChannels   = DBF_MAX_CHANNELS;
	m_ulSatellites = DBF_MAX_SATELLITES;

	m_asRawTimeSeries = new unsigned long[ DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS ];
	memset( m_asRawTimeSeries, 0, DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long) );

	/*m_afRawInputSamples = new float[DBF_FFT_REAL_SIZE];
	memset( m_afRawInputSamples, 0, DBF_SAMPLE_SIZE*sizeof(float));*/
	m_acFFTdata			= new EMSCOMPLEX*[DBF_MAX_SATELLITES];
	for(int i = 0; i < DBF_MAX_SATELLITES; ++i)
	{
		m_acFFTdata[i] = new EMSCOMPLEX[DBF_FFT_COMPLEX_SIZE];
		memset( m_acFFTdata[i], 0, sizeof(EMSCOMPLEX) * DBF_FFT_COMPLEX_SIZE );
	}	
	m_afTemp1	= new float[DBF_FFT_REAL_SIZE];
	m_afTemp2	= new float[DBF_FFT_REAL_SIZE];
	m_acTemp1	= new EMSCOMPLEX[DBF_FFT_COMPLEX_SIZE+1];
	m_acTemp2	= new EMSCOMPLEX[DBF_FFT_COMPLEX_SIZE+1];
	m_afChan0   = new float[DBF_SAMPLE_SIZE];
	memset( m_afChan0, 0, DBF_SAMPLE_SIZE*sizeof(float));

	memset( m_afTemp1, 0, DBF_FFT_REAL_SIZE*sizeof(float));
	memset( m_acTemp1, 0, (DBF_FFT_COMPLEX_SIZE+1)*sizeof(EMSCOMPLEX));
	memset( m_afTemp2, 0, DBF_FFT_REAL_SIZE*sizeof(float));
	memset( m_acTemp2, 0, (DBF_FFT_COMPLEX_SIZE+1)*sizeof(EMSCOMPLEX));
	//CDigitalBeamFormer::Initialize( cDir );

	#if DOWN_SAMPLING_OPTION==1
	   #define DOWN_SAMPLING_FACTOR   2
	
    #endif	

	//added for Sichun phase bias calc process 7
	/*afISeq= new float[DBF_SAMPLE_SIZE];
	
	afQSeq= new float[DBF_SAMPLE_SIZE];*/
		
	acIQSeq= new EMSCOMPLEXD[DBF_SAMPLE_SIZE];
		
	afISeq1 = new float[DBF_FFT_REAL_SIZE];
	
	afQSeq1= new float [DBF_FFT_REAL_SIZE];
		
	


	
	memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEXD));
		
	memset( afISeq1,  0, DBF_FFT_REAL_SIZE*sizeof(float));
	memset( afQSeq1,  0, DBF_FFT_REAL_SIZE*sizeof(float));
	
	m_asMatrix = new float[ NUM_CHANNELS*DBF_SAMPLE_SIZE ];
	if( DBF_PROCESSOR_VER == 4 )
	{
		m_acIQMatrix = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
	    memset(m_acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEXD));	

	}
	else if( DBF_PROCESSOR_VER == 5 )
	{
		m_acIQMatrix = new EMSCOMPLEXD[NUM_CHANNELS*(DBF_SAMPLE_SIZE/DOWN_SAMPLING_FACTOR)];
		memset(m_acIQMatrix, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/DOWN_SAMPLING_FACTOR)*sizeof(EMSCOMPLEX));

	}
	else if (DBF_PROCESSOR_VER == 6 )
	{
		m_acIQMatrix = new EMSCOMPLEXD[NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)*UP_SAMPLING_FACTOR];
		memset(m_acIQMatrix, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)*UP_SAMPLING_FACTOR*sizeof(EMSCOMPLEX));

	}
	memset(m_asMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));	
	
	return S_OK;
}


// December 29, 2020, SW


EMS_RESULT  CDigitalBeamFormerEx::PerformFIRFiltering( const double *FirFilter, const ULONG Q, const float *InputArray, const ULONG N, 
                    float *OutputArray)
{
	ULONG index, jsample;
	
	EMS_RESULT hr = EMS_BAD_PARAM;
	
	for (index=0; index< N; index++)
	{
		OutputArray[index]=0.0;
		
		if (index<Q)
		{
			for (jsample=0; jsample <= index; jsample++)
			{
				OutputArray[index] += FirFilter[jsample]*InputArray[index-jsample];		
			}	
		}else
		{
			for (jsample=0; jsample < Q; jsample++)
			{
				OutputArray[index] += FirFilter[jsample]*InputArray[index-jsample];		
			}	
		}	
	}
 
	hr =EMS_OK;
    
	return hr;
}	



EMS_RESULT  CDigitalBeamFormerEx::PerformFIRFiltering( const double *FirFilter, const ULONG Q, const EMSCOMPLEXD *InputArray, const ULONG N, 
                    EMSCOMPLEXD *OutputArray)
{
	ULONG index, jsample;
	
	EMS_RESULT hr = EMS_BAD_PARAM;
	
	for (index=0; index< N; index++)
	{
		OutputArray[index].re = 0.0;
		OutputArray[index].im = 0.0;
		if (index<Q)
		{
			for (jsample=0; jsample <= index; jsample++)
			{
				OutputArray[index].re += FirFilter[jsample]*InputArray[index-jsample].re;	
				OutputArray[index].im += FirFilter[jsample]*InputArray[index-jsample].im;
			}		
		}else
		{
			for (jsample=0; jsample < Q; jsample++)
			{
				OutputArray[index].re += FirFilter[jsample]*InputArray[index-jsample].re;	
				OutputArray[index].im += FirFilter[jsample]*InputArray[index-jsample].im;
			}	
		}	
	}
 
	hr =EMS_OK;
    
	return hr;
}	



EMS_RESULT  CDigitalBeamFormerEx::PerformDownSampling( const double *FirFilter, const ULONG DownSamplingRate, 
           const EMSCOMPLEXD *InputArray, const ULONG N, EMSCOMPLEXD *OutputArray)
{
	const ULONG KArray[5] ={63, 31, 25, 15, 12};
	ULONG M = DownSamplingRate;
	ULONG K0;
	EMS_RESULT hr = EMS_BAD_PARAM;

    if (!( (M==2) || (M==4) || (M==5) || (M==8) || (M==10)  ))
    {
           return hr;
	}else
	{
		if (M==2)
			K0=KArray[0];
		else if (M==4)
			K0=KArray[1];
		else if (M==5)
			K0=KArray[2];
		else if (M==8)
			K0=KArray[3];
		else if (M==10)
			K0=KArray[4];
			
        memset(OutputArray, 0, (N/M)*sizeof(EMSCOMPLEXD));		

        // initial segment
		for(ULONG m=0; m <= K0; m++)
		{
			OutputArray[m].re=0.0;
			OutputArray[m].im=0.0;
			for (ULONG jsample=0; jsample <= m*M; jsample++)
			{
				OutputArray[m].re +=  FirFilter[jsample]*InputArray[m*M-jsample].re;
				OutputArray[m].im +=  FirFilter[jsample]*InputArray[m*M-jsample].im;		
			}	
		}

         for(ULONG m=K0+1; m < N/M; m++)
		{
			OutputArray[m].re=0.0;
			OutputArray[m].im=0.0;
			for (ULONG jsample=0; jsample <= N0-1; jsample++)
			{
				OutputArray[m].re +=  FirFilter[jsample]*InputArray[m*M-jsample].re;
				OutputArray[m].im +=  FirFilter[jsample]*InputArray[m*M-jsample].im;		
			}	
		} 
		hr= EMS_OK;
	} 	
    
    return hr;	
}

//  Resampling by the factor L/5, December 31, 2020
EMS_RESULT  CDigitalBeamFormerEx::PerformReSampling( const double *FirFilter, const ULONG UpSamplingFactor, 
           const EMSCOMPLEXD *InputArray, const ULONG N, EMSCOMPLEXD *OutputArray)
{
	const ULONG M = 5;
	ULONG L = UpSamplingFactor;
	ULONG  Q, k, m, n;
	EMS_RESULT hr = EMS_BAD_PARAM;

    if (!( (L==1) || (L==2) || (L==4)  ))
    {
           return hr;
	}else
	{
		Q=128/L;
			
        memset(OutputArray, 0, (N/M)*L*sizeof(EMSCOMPLEXD));		

        for (k=0; k< N/M; k++)
		{
		    for(m=0; m < L; m++)
		    {
			    OutputArray[k*L+m].re=0.0;
			    OutputArray[k*L+m].im=0.0;
				
				if ( (k*M+m) < (Q-1) )
				{
			        for (n=0; n <= k*M+m; n++)
			        {
				        OutputArray[k*L+m].re +=  FirFilter[n*L+m]*InputArray[k*M+m-n].re;
				        OutputArray[k*L+m].im +=  FirFilter[n*L+m]*InputArray[k*M+m-n].im;		
			        }	
				}else if ( (k*M+m) >= (Q-1) )
				{
					for (n=0; n < Q; n++)
			        {
				        OutputArray[k*L+m].re +=  FirFilter[n*L+m]*InputArray[k*M+m-n].re;
				        OutputArray[k*L+m].im +=  FirFilter[n*L+m]*InputArray[k*M+m-n].im;		
			        }	
				}
			}		
		}
		
		hr= EMS_OK;
	} 	   
    return hr;	
}



// Jan. 12, 2021, SW
// Jan. 27, 2021, SW
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation5(unsigned long *clpRawTimeSeries, const ULONG DownSamplingRate, EMSCOMPLEX *acIQMatrix)
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	const float fc = 0.3;
	const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
  
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
        int M = DownSamplingRate;
        memset(acIQMatrix, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)*sizeof(EMSCOMPLEX));
		memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
            continue;
				 
            //Normalize the raw data sample sequence
            //memset( m_afTemp2, 0, DBF_SAMPLE_SIZE*sizeof(float));
            //_EMSsbNormalize(m_afTemp1, m_afTemp2, m_ulSamplesPerChannel, dMean, dStdDev); 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   			
   
            //Bandpass FIR filtering the normalized data stored in asMatrix 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
			//hr = PerformFIRFiltering( bandpass_filter, N0, m_afTemp2, DBF_SAMPLE_SIZE, m_afTemp1);
																																						
            //Perform frequency shifting by translating 150KHz to 0 KHz
            //memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
            for (index = 0; index < DBF_SAMPLE_SIZE; index++)
            {    
	             //acIQSeq[index].re = cos(index*fc*PI)*m_afTemp1[index];
	             //acIQSeq[index].im = -sin(index*fc*PI)*m_afTemp1[index];  
                 acIQSeq[index].re =  cos(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);
	             acIQSeq[index].im = -sin(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]); 				 
            }
																														 
            //Perform lowpass filtering. Further optimization likely using Intel SP library calls 
            //invoking FIR filtering of complex signals                                                                                 
            hr = PerformDownSampling( lowpass_filter, DownSamplingRate, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*(DBF_SAMPLE_SIZE/M));
        }

        //normalization of the complex-valued baseband  channel data streams

        EMSCOMPLEX *pc;

        EMSCOMPLEX meanc;

        float stdc;

        for (int ichan=1;  ichan < (int)m_ulChannels; ichan++ ) 
        {
	        pc = acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE/M;
	
	        stdc = _EMScMeanStdDev(pc, DBF_SAMPLE_SIZE/M, &meanc );
	       _EMScNormalize( pc, acIQSeq, DBF_SAMPLE_SIZE/M, meanc, stdc );
	        for(int jsample=0; jsample < DBF_SAMPLE_SIZE/M; jsample++)
	        {
		         pc[jsample] = acIQSeq[jsample];
	        }
        }
    }
    return hr;
}


// Jan. 27, 2021, SW
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation6(unsigned long *clpRawTimeSeries, const ULONG UpSamplingFactor
, EMSCOMPLEX *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
    const int M = 5;
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        int L = UpSamplingFactor;
        memset(acIQMatrix, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)*L*sizeof(EMSCOMPLEX));
		memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
             // Convert integer to float 
             //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
             for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
             {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
             }

             dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
             if( dStdDev == 0.00 )
                 continue;
				 
             //Normalize the raw data sample sequence
             //memset( m_afTemp2, 0, DBF_SAMPLE_SIZE*sizeof(float));
             //_EMSsbNormalize(m_afTemp1, m_afTemp2, m_ulSamplesPerChannel, dMean, dStdDev); 
             //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   						 
   
             //Bandpass FIR filtering the normalized data stored in asMatrix 
             //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
			 //hr = PerformFIRFiltering( bandpass_filter, N0, m_afTemp2, DBF_SAMPLE_SIZE, m_afTemp1);
																																						
             //Perform frequency shifting by translating 150KHz to 0 KHz
             //memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
             for (index = 0; index < DBF_SAMPLE_SIZE; index++)
             {    
	             //acIQSeq[index].re = cos(index*fc*PI)*m_afTemp1[index];
	             //acIQSeq[index].im = -sin(index*fc*PI)*m_afTemp1[index]; 
                 acIQSeq[index].re =  cos(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);
	             acIQSeq[index].im = -sin(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);				 
             }
																														 
             //Perform lowpass filtering. Further optimization likely using Intel SP library calls 
             //invoking FIR filtering of complex signals                                                                                 
             hr = PerformReSampling( lowpass_filter, UpSamplingFactor, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*(DBF_SAMPLE_SIZE/M)*L);
        }

        //normalization of the complex-valued baseband  channel data streams

        EMSCOMPLEX *pc;

        EMSCOMPLEX meanc;

        float stdc;

        for (int ichan=1;  ichan < (int)m_ulChannels; ichan++ ) 
        {
	        pc = acIQMatrix+(ichan-1)*(DBF_SAMPLE_SIZE/M)*L;
	
	        stdc = _EMScMeanStdDev(pc, (DBF_SAMPLE_SIZE/M)*L, &meanc );
	        _EMScNormalize( pc, acIQSeq, (DBF_SAMPLE_SIZE/M)*L, meanc, stdc );
	        for(int jsample=0; jsample < (DBF_SAMPLE_SIZE/M)*L; jsample++)
	        {
		         pc[jsample] = acIQSeq[jsample];
	        }
        }
    }
	
    return hr;
}




EMS_RESULT  CDigitalBeamFormerEx::ComputeCovarianceMatrix4(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix)
{

  EMS_RESULT hr = EMS_BAD_PARAM;

  unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
  
  if ( clpRawTimeSeries)
  {
	 //Perform baseband IQ demodulation
	 memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof(float));
	 memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ));
	 {
		 m_timeElapsed.FuncTimerStart("PerformIQDemodulation7" );
		//hr = PerformIQDemodulation4(clpRawTimeSeries, acIQMatrix);
		hr = PerformIQDemodulation7(clpRawTimeSeries, acIQMatrix);
		m_timeElapsed.FuncTimerClose();

	 }
	 m_timeElapsed.FuncTimerStart("ComputeCovaMat4 " );

	 if (EMS_OK == hr)
	 {
		EMSCOMPLEXD *Y = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
		EMSCOMPLEXD *Z = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
		if ((Y) &&(Z))
		{
		   memset(Y, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ) );
		   memset(Z, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ) );
		   emscbConj2d(acIQMatrix, Y, NUM_CHANNELS*DBF_SAMPLE_SIZE);
		   //emscbMatrixTranspose(Y, Z, NUM_CHANNELS, DBF_SAMPLE_SIZE ); bug
		   emscbMatrixTransposed(Y, Z,  DBF_SAMPLE_SIZE , NUM_CHANNELS);// SW, Jan. 10, 2021
		   emscbMatrixMultiplyd(acIQMatrix, NUM_CHANNELS, DBF_SAMPLE_SIZE, Z, DBF_SAMPLE_SIZE, NUM_CHANNELS, acCovarianceMatrix );                                                                                          
		}
		for( int iIndx = 0; iIndx < NUM_CHANNELS*NUM_CHANNELS; iIndx++ )
		{
			acCovarianceMatrix[iIndx].re /= DBF_SAMPLE_SIZE;
			acCovarianceMatrix[iIndx].im /= DBF_SAMPLE_SIZE;
		}
		delete[] Y;
		delete[] Z;
		
		hr = EMS_OK;
	 }                           
  }
   m_timeElapsed.FuncTimerClose();
	  
  return hr;
}


EMS_RESULT  CDigitalBeamFormerEx::ComputeCovarianceMatrix5(const ULONG DownSamplingRate, EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix)
{
  EMS_RESULT hr = EMS_BAD_PARAM;

  ULONG M = DownSamplingRate;
  
  unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
  
  if ( clpRawTimeSeries)
  {
	 //Perform baseband IQ demodulation
	 memset(acIQMatrix, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)* sizeof( EMSCOMPLEXD ));
	 
	 hr = PerformIQDemodulation5(clpRawTimeSeries, DownSamplingRate, acIQMatrix);

	 if (EMS_OK == hr)
	 {
		EMSCOMPLEXD *Y = new EMSCOMPLEXD[NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)];
		EMSCOMPLEXD *Z = new EMSCOMPLEXD[NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)];
		if ((Y) &&(Z))
		{
			memset(Y, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)* sizeof( EMSCOMPLEXD ) );
			memset(Z, 0, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M)* sizeof( EMSCOMPLEXD ) );
			emscbConj2d(acIQMatrix, Y, NUM_CHANNELS*(DBF_SAMPLE_SIZE/M));
			//emscbMatrixTranspose(Y, Z, NUM_CHANNELS, DBF_SAMPLE_SIZE/M ); bug
			emscbMatrixTransposed(Y, Z,  DBF_SAMPLE_SIZE/M, NUM_CHANNELS ); // SW, Jan. 10, 2021
			emscbMatrixMultiplyd(acIQMatrix, NUM_CHANNELS, DBF_SAMPLE_SIZE/M, Z, DBF_SAMPLE_SIZE/M, NUM_CHANNELS, acCovarianceMatrix );                                                                                          
		}
		delete[] Y;
		delete[] Z;
		
		hr = EMS_OK;
	 }                           
  }
  
  return hr;
}






EMS_RESULT  
CDigitalBeamFormerEx::PerformEigenDecomposition(const EMSCOMPLEXD *acCovarianceMatrix, 
                              float *EigenValues, MKL_Complex8 *acEigenVectors)
{
	CHGTEigenVectors eigenVect;
	eigenVect.PerformEigenDecomposition( (MKL_Complex8 *)acCovarianceMatrix, EigenValues, acEigenVectors );
	return S_OK;						 
								 
}


EMS_RESULT  
CDigitalBeamFormerEx::PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors)
{
	double amp;
	double x,y;
	
	memset(acNormalizedEigenVectors, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));
	
	for (int i =0; i<NUM_CHANNELS; i++)
	{
		for (int j=0;j<NUM_CHANNELS;j++)
		{
			x=acEigenVectors[i*NUM_CHANNELS+j].real;
			y=acEigenVectors[i*NUM_CHANNELS+j].imag;
			amp= sqrt(x*x+y*y);
			if (amp>0.0)
			{
				acNormalizedEigenVectors[i*NUM_CHANNELS+j].re =	acEigenVectors[i*NUM_CHANNELS+j].real/amp;
			    acNormalizedEigenVectors[i*NUM_CHANNELS+j].im =	acEigenVectors[i*NUM_CHANNELS+j].imag/amp;
			}			
		}
	}
    
    return EMS_OK;
	
}

EMS_RESULT
CDigitalBeamFormerEx::_ComplexMatrixInverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse, ULONG ulMSize  )
{
	EMS_RESULT hr = EMS_OK;
	int iIndex[9] = { 0,1,2,4,5,6,8,9,10 };
	EMSCOMPLEXD cTest[16];

	switch (ulMSize)
	{
		case 1:
			acMatrixInverse[0] = _CDivide ( acMatrix[0] );
			break;

		case 2:
			_ComplexMatrix2x2Inverse( acMatrix, acMatrixInverse );
			break;

		case 3:
			EMSCOMPLEXD cIN[16], cOUT[16];
			memset( cIN, 0, 16*sizeof( EMSCOMPLEXD ) );
			memset( cOUT, 0, 16*sizeof( EMSCOMPLEXD ) );

			for( int i = 0; i < 9; i++ )
			{
				cIN[iIndex[i]] = acMatrix[i];
			}
			cIN[15].re = 1.0;
			cIN[15].im = 0.0;
		
			hr = _ComplexMatrix4x4Inverse( cIN, cOUT );
		
			for( int i = 0; i < 9; i++ )
			{
				acMatrixInverse[i] = cOUT[iIndex[i]];
			}
			break;

		case 4:
			hr = _ComplexMatrix4x4Inverse( acMatrix, acMatrixInverse );
			return hr;
		
		default:
			hr = _ComplexMatrixNxNInverse( acMatrix, acMatrixInverse, ulMSize );
			break;
	}

	return hr;
}

EMS_RESULT  CDigitalBeamFormerEx::ComputeNullingVectors(const EMSCOMPLEXD *acEigenVectors, 
                                  const int nNumBeams, EMSCOMPLEXD *acDBFBeamVectors)
{   
  EMS_RESULT hr = EMS_FALSE;
  
  int DEBUG;
  
  //row major storage assumed for all matrices and vectors defined below
  EMSCOMPLEXD acVectors[NUM_CHANNELS*(MAX_BEAMS-1)];
  EMSCOMPLEXD acA[NUM_CHANNELS*(MAX_BEAMS-1)]; //A
  EMSCOMPLEXD acAt[(MAX_BEAMS-1)*NUM_CHANNELS]; //A transposed
  EMSCOMPLEXD acAh[(MAX_BEAMS-1)*NUM_CHANNELS]; //A' =conj(A transposed) = hermitian transpose of A
  EMSCOMPLEXD acAhA[(MAX_BEAMS-1)*(MAX_BEAMS-1)]; //A'*A
  EMSCOMPLEXD acinvAhA[(MAX_BEAMS-1)*(MAX_BEAMS-1)]; //inv(A'*A)
  EMSCOMPLEXD acinvAhAAh[(MAX_BEAMS-1)*NUM_CHANNELS]; //inv(A'*A)*A'
  EMSCOMPLEXD acAinvAhAAh[NUM_CHANNELS*NUM_CHANNELS];//A*inv(A'*A)*A'
  EMSCOMPLEXD u[NUM_CHANNELS], v[NUM_CHANNELS], w[NUM_CHANNELS];
  
  memset( acVectors, 0, NUM_CHANNELS*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acA, 0, NUM_CHANNELS*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acAt, 0,(MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAh, 0,(MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAhA, 0, (MAX_BEAMS-1)*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acinvAhA, 0, (MAX_BEAMS-1)*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acinvAhAAh, 0, (MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAinvAhAAh, 0, NUM_CHANNELS*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( u,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( v,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( w,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  
  if (nNumBeams <= MAX_BEAMS)
  {
      if (nNumBeams == 1)
      {
		   for(int ichan=0; ichan<NUM_CHANNELS; ichan++)
		   {
				acDBFBeamVectors[ichan] = acEigenVectors[ichan];
		   }
		   
		   hr= 1;
      } 
      else if (nNumBeams > 1)
      {
           for(int iBeam = 0; iBeam < nNumBeams; iBeam++)
           {
                int l = 0;
                for ( int jBeam = 0; jBeam < nNumBeams; jBeam++ )
                {
				    if ( !( jBeam == iBeam ) )
				    {
						  for ( int ichan = 0; ichan < NUM_CHANNELS; ichan++ )
						  {
							  acVectors[l++] = acEigenVectors[jBeam*NUM_CHANNELS+ichan];
							  // row major storage assumed here !!!
						  }
				    }
				}
		   
				emscbConj2d( acVectors, acAh, (nNumBeams-1)*NUM_CHANNELS);
				emscbMatrixTransposed( acVectors, acA, NUM_CHANNELS, nNumBeams-1); 

				emscbMatrixMultiplyd( acAh, nNumBeams-1, NUM_CHANNELS, acA,  NUM_CHANNELS,nNumBeams-1, acAhA );
	   
                hr = _ComplexMatrixInverse( acAhA, acinvAhA, nNumBeams-1); 
				
			   if (EMS_OK == hr)
			   {
					emscbMatrixMultiplyd( acinvAhA,  nNumBeams-1, nNumBeams-1,acAh,  nNumBeams-1,NUM_CHANNELS, acinvAhAAh );
				
					emscbMatrixMultiplyd( acA,  NUM_CHANNELS, nNumBeams-1,acinvAhAAh,  nNumBeams-1,NUM_CHANNELS, acAinvAhAAh );
					
					for (int ichan=0; ichan< NUM_CHANNELS; ichan++)
					{
						u[ichan]= acEigenVectors[iBeam*NUM_CHANNELS+ichan];
					}             
	  
					emscbMatrixMultiplyd(acAinvAhAAh, NUM_CHANNELS,NUM_CHANNELS, u, NUM_CHANNELS,1, v);
					
					for (int ichan=0; ichan< NUM_CHANNELS; ichan++)
					{
						// no normalization performed here
						acDBFBeamVectors[iBeam*NUM_CHANNELS+ichan].re = u[ichan].re-v[ichan].re;
						acDBFBeamVectors[iBeam*NUM_CHANNELS+ichan].im = u[ichan].im-v[ichan].im;
					} 
	  
					hr = EMS_OK;
				} 
		   }				
        }
    }else
    {
	   return EMS_FALSE;
    }
    return hr;       
}                           


EMS_RESULT  CDigitalBeamFormerEx::ComputeDBFBeamVectors(const EMSCOMPLEXD *acCovarianceMatrix, const int nNumBeams,
    float *EigenValues,  MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors, EMSCOMPLEXD *acDBFBeamVectors )
{
	  EMS_RESULT hr = EMS_BAD_PARAM;
	  memset(EigenValues,0, NUM_CHANNELS*sizeof(float));
	  memset(acEigenVectors,0,NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  memset(acNormalizedEigenVectors,0,NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  memset(acDBFBeamVectors,0,nNumBeams*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  {
		  m_timeElapsed.FuncTimerStart("PerformEigenDec" );	 
		  hr = PerformEigenDecomposition(acCovarianceMatrix,EigenValues, acEigenVectors);
		  m_timeElapsed.FuncTimerClose();
	  }
	  m_timeElapsed.FuncTimerStart("ComputeDBFBmVct" );

	  if(EMS_OK == hr)
	  {
		   hr = PerformEigenVectorNormalization(acEigenVectors, acNormalizedEigenVectors);
	   
		   // Extracting the nNumBeams largest eigenvectors 
		   if (EMS_OK==hr)
		   {
			   EMSCOMPLEXD *acLargestEigenVectors  = new EMSCOMPLEXD[nNumBeams*NUM_CHANNELS];
			   memset(acLargestEigenVectors,0,nNumBeams*NUM_CHANNELS*sizeof(EMSCOMPLEXD));
			  // Extracting the nNumBeams largest eigenvectors
			  for (int  iBeam =0; iBeam<nNumBeams; iBeam++)
			  {
				  for(int ichan=0; ichan<NUM_CHANNELS; ichan++)
				  {
					   acLargestEigenVectors[iBeam*NUM_CHANNELS+ichan] = acNormalizedEigenVectors[(30-iBeam)*NUM_CHANNELS+ichan];
				  }
			  }			  
		  
			  //hr = ComputeNullingVectors(acNormalizedEigenVectors,  nNumBeams, acDBFBeamVectors); 
			   hr = ComputeNullingVectors(acLargestEigenVectors, nNumBeams, acDBFBeamVectors); 	
			   delete [] acLargestEigenVectors;		   
		   }
	 }
	  m_timeElapsed.FuncTimerClose();

  return hr;
}

template <typename T>
void LogDouble( const T* input, UINT size,std::string fileName ) 
{
	//Log input values	
	std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName;
	std::fstream fhLog( logPath,  std::fstream::out );

	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i] << "," ;	
	}
	fhLog.close();
}
template <typename T>
void LogComplexD( const T* input, UINT size,std::string fileName ) 
{
	//Log input values	
	std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName;
	std::fstream fhLog( logPath,  std::fstream::out );

	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i].re;
		if( input[i].im >= 0)
			fhLog << "+" ;
		fhLog << std::fixed << std::setprecision(16) << input[i].im << "i," ;	
	}
	fhLog.close();
}

void LogMKLComplex16( const MKL_Complex8* input, UINT size,std::string fileName ) 
{
	//Log input values	
	std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName;
	std::fstream fhLog( logPath,  std::fstream::out );

	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i].real;
		if( input[i].imag >= 0)
			fhLog << "+" ;
		fhLog << std::fixed << std::setprecision(16) << input[i].imag << "i," ;	
	}
	fhLog.close();
}

void LogBeamCSV( const EMSCOMPLEXD* inputBeams, int nBeamIndx, std::string desc ) 
{
	//Log input values
	std::stringstream strStringReal,strStringImg;
	strStringReal << "C:\\TEMP\\DBFCovarianceFiles\\real_" << desc << nBeamIndx << ".csv";
	strStringImg << "C:\\TEMP\\DBFCovarianceFiles\\img_" << desc << nBeamIndx << ".csv";

	std::string logPath = strStringReal.str();
	std::fstream fhRealLog( logPath,  std::fstream::out );
	std::fstream fhImgLog( strStringImg.str(),  std::fstream::out );

	for (int i = 0; i <  DBF_SAMPLE_SIZE; i++)
	{
		fhRealLog << std::fixed << std::setprecision(16) << inputBeams[i].re << "," ;	
		fhImgLog << std::fixed << std::setprecision(16) << inputBeams[i].im << "," ;		

		if( i && !(( i+1) % 1000) )
		{
			fhRealLog << std::endl;
			fhImgLog << std::endl;
		}
	}
	fhRealLog.close();
	fhImgLog.close();
}

EMS_RESULT
CDigitalBeamFormerEx::DBFprocessor8( const int nNumBeams/*, EMSCOMPLEXD **asBeamMatrix, EMSCOMPLEXD **acBeamMatrix*/)
{
	EMS_RESULT hr;
	hr = DBFprocessor8_v4(nNumBeams  );

	
	return hr;	
}
//Jan.1, 2021
//Main Beamforming Function
EMS_RESULT
CDigitalBeamFormerEx::ComputeDBFBeamVectors( INT nNumBeams)
{
	EMSCOMPLEXD  acCovarianceMatrix[NUM_CHANNELS*NUM_CHANNELS];	
	float EigenValues[NUM_CHANNELS];
	MKL_Complex8 acEigenVectors[NUM_CHANNELS*NUM_CHANNELS];
	EMSCOMPLEXD acNormalizedEigenVectors[NUM_CHANNELS*NUM_CHANNELS];	

    memset(acCovarianceMatrix, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));	
	memset(EigenValues, 0, NUM_CHANNELS*sizeof(float));	
	memset(acEigenVectors, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(MKL_Complex8));	
	memset(acNormalizedEigenVectors, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));	
	unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
    EMS_RESULT hr = EMS_BAD_PARAM;	
                            
    if ( clpRawTimeSeries)
    {
        hr = ComputeCovarianceMatrix10( m_acIQMatrix, acCovarianceMatrix);
		if ( (EMS_OK == hr) && (nNumBeams <= MAX_BEAMS) )
		{	
			if( m_acDBFBeamVectors == nullptr )
			{
				m_acDBFBeamVectors = new EMSCOMPLEXD[MAX_BEAMS*NUM_CHANNELS]; 
			}
			hr = ComputeDBFBeamVectors(acCovarianceMatrix, nNumBeams, EigenValues, acEigenVectors,acNormalizedEigenVectors, m_acDBFBeamVectors );
		}
	}
	return hr;
}

EMS_RESULT
CDigitalBeamFormerEx::DBFprocessor8_v4( const int nNumBeams/*, EMSCOMPLEXD **asBeamMatrix, EMSCOMPLEXD **acBeamMatrix*/)

{
    EMS_RESULT hr = EMS_BAD_PARAM;	
    unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
                            
    if ( clpRawTimeSeries)
    {
		EMSTIME timeStart  = CEMSSystemClock::GetTime();

		if ( m_qrefDBFBeamVectors.IsEmpty() )
		{
			//OutputDebugString(" Q empty, local calc DBFBeams" );

			hr = ComputeDBFBeamVectors( nNumBeams );
		}
		else
		{
			if ( /*(EMS_OK == hr) &&*/ (nNumBeams <= MAX_BEAMS) )
			{	
				m_acDBFBeamVectors = m_qrefDBFBeamVectors.ReadFirst( ).dbfBeamVector;
				/*int* beamIDs = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
				for( int iSat = 0; iSat < m_ulSatellites; iSat++ )			
					m_aPassSchedule.rec[iSat].wPlateID = beamIDs[iSat];*/
				std::stringstream str22;
				str22 << " Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( CEMSSystemClock::GetTime() )
					<< "Reading from q - DBFBeamVect100 " << m_acDBFBeamVectors[99].re << "," << m_acDBFBeamVectors[99].im << std::endl ;
				//OutputDebugString(str22.str().c_str() );
			}
			else
			{
				return EMS_BAD_PARAM;
			}
		}
		EMSTIME timeFinish = CEMSSystemClock::GetTime();
		INT64 i64ElapsedTime = timeFinish.intTime - timeStart.intTime;
		double dElapsedTime = ((double) i64ElapsedTime) * 1e-9;
		std::stringstream str1;
		str1 <<"ComputeDBFBeamVectors  Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( CEMSSystemClock::GetTime() ) << 			
			" time taken:" << dElapsedTime << " secs " << std::endl;
		//OutputDebugString( str1.str().c_str() );

		int iMax = 0;
		if( m_ulSatellites >= DBF_MAX_SATELLITES )
		{
			iMax = DBF_MAX_SATELLITES;
		}
		else
			iMax = m_ulSatellites;
		//iMax = 6;	//hardcoded as per Sichun
		std::stringstream str;
		str << "DBFprocessor9 for" << iMax << "beams " ;
		m_timeElapsed.FuncTimerStart(str.str().c_str() );
		DBFprocessor9( iMax );
		m_timeElapsed.FuncTimerClose();
		
		std::stringstream str11;
		str11 << "_OutputwaveEx for " << m_ulSatellites << " Sats at m_timeActual:" 
			<< CEMSConversionUtil::ConvertToDateTimeHiResString2A(m_timeActual) ;
		printf(str11.str().c_str());
		CTimeElapsed::printMessage( str11.str() );
		m_timeElapsed.FuncTimerStart( str11.str() );
		_OutputWaveExBy2( m_timeActual, iMax );


		m_timeElapsed.FuncTimerClose();

		m_timeElapsed.PrintFinalTimes();
		
    } //if ( clpRawTimeSeries )
    
    return hr;
	
}


EMSCOMPLEXD
CDigitalBeamFormerEx::_EMScMean(const EMSCOMPLEXD *vec, ULONG len)
{
	EMSCOMPLEXD fMean;
	
	fMean.re = 0.0;
	fMean.im = 0.0;
	for( ULONG i = 0; i < len; i++ )
	{
		fMean.re += vec[i].re;
		fMean.im += vec[i].im;
	}
	
	fMean.re = fMean.re/(float)len;
	fMean.im = fMean.im/(float)len;
	return fMean;
}


double
CDigitalBeamFormerEx::_EMScMeanStdDev(const EMSCOMPLEXD *vec, ULONG len, EMSCOMPLEXD* pfMean )
{
	double fStdDev = 0.0;
	EMSCOMPLEXD fSum, fMean;
	
	fSum.re =0.0;
	fSum.im =0.0;
	fMean.re =0.0;
	fMean.im =0.0;
	
    ULONG i;

    for(i = 0; i < len; ++i)
    {
        fSum.re += vec[i].re;
		fSum.im += vec[i].im;
    }

    fMean.re = fSum.re/(float)len;
	fMean.im = fSum.im/(float)len;
	*pfMean = fMean;

    fStdDev = 0.0;
    for(i = 0; i < len; ++i)
        fStdDev += ( pow(vec[i].re - fMean.re, 2) + pow(vec[i].im - fMean.im, 2)    );

    return sqrt(fStdDev / (float)(len-1));
}



void
CDigitalBeamFormerEx::_EMScNormalize( const EMSCOMPLEXD *src, EMSCOMPLEXD *dst, ULONG n, const EMSCOMPLEXD& valuesub, const float valuediv )
{
	if( src && dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i].re = ( src[i].re -  valuesub.re ) / valuediv;
			dst[i].im = ( src[i].im -  valuesub.im ) / valuediv;
		}
	}
}

int 
WavFileCreation( BYTE *data, int size, int nIndx )
{
	std::stringstream filePath;
	filePath << "C:\\temp\\DBFCovarianceFiles\\";
	if( nIndx >= 0 )
		filePath << "beam_fftdata" << nIndx << ".wav" ;
	else
		filePath << "beam_fftdata_sum" << nIndx << ".wav" ;

	std::ofstream fs(filePath.str(), std::ios::out | std::ios::binary | std::ios::app);
    fs.write((char*)&data[0], size);
	fs.close();
    
    return 0;
}

EMS_RESULT
CDigitalBeamFormerEx::DBFprocessor9( /*const unsigned long *clpRawTimeSeries,*/ int iNumSats  )
{
	EMS_RESULT hr = EMS_BAD_PARAM;
	float fScaleFactor        = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion

	m_ulMaxPowerIndex = 0;
	m_bOutputOK = true;
	EMSTIME timeStart  = CEMSSystemClock::GetTime();

	//if ( clpRawTimeSeries )
	{
		ULONG ichan, jsample, index;
		ULONG ulMaxPowerIndex = 0;
		ULONG ulOneSecond = 0;
		double dMean   = 0.0;
		double dStdDev = 0.0;
		EMSCOMPLEX cPhaseCorrection;
		double dPower  = 0.0;

		for(int i = 0; i < DBF_MAX_SATELLITES; ++i)
		{
			memset( m_acFFTdata[i], 0, sizeof(EMSCOMPLEX) * DBF_FFT_COMPLEX_SIZE );
		}
	
		//hr = BufferStatistics( m_asRawTimeSeries );
		
		float fDBFFTRealSize2 = DBF_FFT_REAL_SIZE/2;
		float ulSamplesPerChannel2 = m_ulSamplesPerChannel/2;
		for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
		{
			// Convert integer to float

			memset( m_afTemp1, 0, DBF_FFT_REAL_SIZE*sizeof(float));
			memset( m_afTemp2, 0, DBF_FFT_REAL_SIZE*sizeof(float));
			
			//for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
			for ( jsample = 0, index = ichan; jsample < ulSamplesPerChannel2;  jsample++, index += (m_ulChannels*2) )

			{
				m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
			}
			dStdDev = _EMSsMeanStdDev( m_afTemp1, ulSamplesPerChannel2, &dMean );
			if( dStdDev == 0.00 )
				continue;

			_EMSsbNormalize(m_afTemp1, m_afTemp2, ulSamplesPerChannel2, dMean, dStdDev);

			emssRealFftNip( m_afTemp2, m_acTemp1, DBF_FFT_SIZE_LOG2-1, EMS_SPL_FWD );


			for( int iSat = 0; iSat < iNumSats; iSat++ )			
			{
				double dSatElevation = (double) m_aPassSchedule.rec[iSat].fElevation;
				if( m_aPassSchedule.rec[iSat].ulSatID >= 200 && dSatElevation < MEO_MIN_ELEVATION )	//snl added to check > 30 if pass sched has no elev constraints
					continue;
				memcpy( m_acTemp2 ,m_acTemp1, sizeof(EMSCOMPLEX) * ( (DBF_FFT_COMPLEX_SIZE/2)+1) );

				// RR - correction to match the tracking dish FFT output by reducing the power output by 40 dB
				//      any drop below this will result in the spectrum display showing anomalies due to its handling of negative dB levels
				cPhaseCorrection.re = m_acDBFBeamVectors[iSat*NUM_CHANNELS+ichan-1].re;
				cPhaseCorrection.im = m_acDBFBeamVectors[iSat*NUM_CHANNELS+ichan-1].im;
				cPhaseCorrection.im *= -1.00 ;
				if( abs(cPhaseCorrection.re) + abs(cPhaseCorrection.im) > 0.0 )   
				{
					_EMScbMpy1( cPhaseCorrection, m_acTemp2, DBF_FFT_COMPLEX_SIZE/2);	
					_EMScbAdd2( m_acTemp2, m_acFFTdata[iSat], DBF_FFT_COMPLEX_SIZE/2 );	

				}
			}
			m_aMaintenance.dMean[ichan]   = dMean;
			m_aMaintenance.dStdDev[ichan] = dStdDev;
		}

		hr = EMS_OK;
		EMSTIME timeFinish = CEMSSystemClock::GetTime();
		INT64 i64ElapsedTime = timeFinish.intTime - timeStart.intTime;
		double dElapsedTime = ((double) i64ElapsedTime) * 1e-9;
		std::stringstream str1;
		str1 <<"DBFProcessor9  Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( CEMSSystemClock::GetTime() ) << 
			"BufferTime:" << CEMSConversionUtil::ConvertToDateTimeHiResString2A(m_timeActual) << 
			" time taken:" << dElapsedTime << " secs " << std::endl;
		//OutputDebugString( str1.str().c_str() );
	}
	//printf( "\nDBFProcessor2 -> Time elapsed: %f seconds for %i sats, id: %i \n" ,timeStart.SecondsDifferent( timeEnd), iNumSats,  GetCurrentThreadId() );

	return hr;
}
EMS_RESULT  CDigitalBeamFormerEx::PerformSymFIRFiltering( const double *SymFirFilter, const ULONG Q, const EMSCOMPLEXD *InputArray, const ULONG N, 
                    EMSCOMPLEXD *OutputArray)
{
	//Q=2M must be even in this implementation!!!
	
	ULONG index, jsample;
	
	EMS_RESULT hr = EMS_BAD_PARAM;
	
	int M = Q/2;
	
	for (index=0; index< N; index++)
	{
		OutputArray[index].re = 0.0;
		OutputArray[index].im = 0.0;
		if (index<Q)
		{
			for (jsample=0; jsample <= index; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*InputArray[index-jsample].re;	
				OutputArray[index].im += SymFirFilter[jsample]*InputArray[index-jsample].im;
			}		
		}else
		{
			for (jsample=0; jsample < M; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*(InputArray[index-jsample].re + InputArray[index-(Q-1)+jsample].re );	
				OutputArray[index].im += SymFirFilter[jsample]*(InputArray[index-jsample].im + InputArray[index-(Q-1)+jsample].im );
			}	
		}	
	}
 
	hr =EMS_OK;
    
	return hr;
}	








// Jan. 28, 2021
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation7(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
  
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
        memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
				 
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
                continue;
				 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   
             //Bandpass FIR filtering the normalized data stored in asMatrix 
             //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
							   
             //hr = PerformFIRFiltering( bandpass_filter, N0, asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, DBF_SAMPLE_SIZE, m_afTemp1);
																																						
             //Perform frequency shifting by translating 150KHz to 0 KHz
             //memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
             for (index = 0; index < DBF_SAMPLE_SIZE; index++)
             {    
	              //acIQSeq[index].re = cos(index*fc*PI)*m_afTemp1[index];
	              //acIQSeq[index].im = -sin(index*fc*PI)*m_afTemp1[index]; 

                  acIQSeq[index].re =  cos(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);
	              acIQSeq[index].im = -sin(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]); 				  
             }
																														 
#if DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 1
	
             hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 128, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		 

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 2
	
	         hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 32,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 3
	
             hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 16,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);	

#endif
			 
        }

        //normalization of the complex-valued baseband  channel data streams

        EMSCOMPLEX *pc;

        EMSCOMPLEX meanc;

        float stdc;

        for (int ichan=1;  ichan < (int)m_ulChannels; ichan++ ) 
        {
	        pc = acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE;
	
	        stdc = _EMScMeanStdDev(pc, DBF_SAMPLE_SIZE, &meanc );
	        _EMScNormalize( pc, acIQSeq, DBF_SAMPLE_SIZE, meanc, stdc );
	        for(int jsample=0; jsample < DBF_SAMPLE_SIZE; jsample++)
	        {
		        pc[jsample] = acIQSeq[jsample];
	        }
        }
    }
    return hr;
}
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation8(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
	
	const double c[20]={
	1.000000000000000,   0.587785252292473,  -0.309016994374947,  -0.951056516295153,  -0.809016994374947,  -0.000000000000000,
    0.809016994374947,   0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292473,
    0.309016994374945,   0.951056516295153,   0.809016994374948,   0.000000000000001,  -0.809016994374947,  -0.951056516295154,
   -0.309016994374948,   0.587785252292474  };
	
	const double s[20] = {
	 0,                  -0.809016994374947,  -0.951056516295154,  -0.309016994374948,   0.587785252292473,   1.000000000000000,
     0.587785252292474,  -0.309016994374947,  -0.951056516295154,  -0.809016994374948,  -0.000000000000000,   0.809016994374947,
     0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292474,   0.309016994374945,
     0.951056516295153,   0.809016994374947 };
		
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
        memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
				 
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
                continue;
				 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   
            																																				
             //Perform frequency shifting by translating 150KHz to 0 KHz
             //memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
             //for (index = 0; index < DBF_SAMPLE_SIZE; index++)
             //{    
             //     acIQSeq[index].re =  cos(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);
	         //     acIQSeq[index].im = -sin(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]); 				  
             //}
			 
			 for (int bindex = 0; bindex < DBF_SAMPLE_SIZE/20; bindex++)
             {    
		          for(int j = 0; j < 20; j++)
				  {
                      acIQSeq[index*20+j].re =  c[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]);
	                  acIQSeq[index*20+j].im =  s[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]); 
				  }				  
             }
			 
#if DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 1
	
             hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 128, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		 

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 2
	
	         hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 32,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 3
	
             hr = PerformSymFIRFiltering( dbf_iq_demod_lowpass_filter, 16,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);	

#endif
			 
        }

        //normalization of the complex-valued baseband  channel data streams removed for now

        EMSCOMPLEX *pc;

        EMSCOMPLEX meanc;

        float stdc;

        for (int ichan=1;  ichan < (int)m_ulChannels; ichan++ ) 
        {
	        pc = acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE;
	
	        stdc = _EMScMeanStdDev(pc, DBF_SAMPLE_SIZE, &meanc );
	        _EMScNormalize( pc, acIQSeq, DBF_SAMPLE_SIZE, meanc, stdc );
	        for(int jsample=0; jsample < DBF_SAMPLE_SIZE; jsample++)
	        {
		        pc[jsample] = acIQSeq[jsample];
	        }
        }
	
    }
    return hr;
}



EMS_RESULT  CDigitalBeamFormerEx::ComputeCovarianceMatrix7(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix)
{

  EMS_RESULT hr = EMS_BAD_PARAM;

  unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
  
  if ( clpRawTimeSeries)
  {
	 //Perform baseband IQ demodulation
	 memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof(float));
	 memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ));
	 {
		m_timeElapsed.FuncTimerStart("PerformIQDemodulation7" );
		//hr = PerformIQDemodulation4(clpRawTimeSeries, acIQMatrix);
		hr = PerformIQDemodulation8(clpRawTimeSeries, acIQMatrix);
		m_timeElapsed.FuncTimerClose();

	 }
	m_timeElapsed.FuncTimerStart("ComputeCovarianceMatrix7" );

	 if (EMS_OK == hr)
	 {
		EMSCOMPLEXD *Y = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
		EMSCOMPLEXD *Z = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
		if ((Y) &&(Z))
		{
		   memset(Y, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ) );
		   memset(Z, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ) );
		   emscbConj2d(acIQMatrix, Y, NUM_CHANNELS*DBF_SAMPLE_SIZE);
		   //emscbMatrixTranspose(Y, Z, NUM_CHANNELS, DBF_SAMPLE_SIZE ); bug
		   emscbMatrixTransposed(Y, Z,  DBF_SAMPLE_SIZE , NUM_CHANNELS);// SW, Jan. 10, 2021
		   emscbMatrixMultiplyd(acIQMatrix, NUM_CHANNELS, DBF_SAMPLE_SIZE, Z, DBF_SAMPLE_SIZE, NUM_CHANNELS, acCovarianceMatrix );                                                                                          
		}
		for( int iIndx = 0; iIndx < NUM_CHANNELS*NUM_CHANNELS; iIndx++ )
		{
			acCovarianceMatrix[iIndx].re /= DBF_SAMPLE_SIZE;
			acCovarianceMatrix[iIndx].im /= DBF_SAMPLE_SIZE;
		}
		delete[] Y;
		delete[] Z;
		
		hr = EMS_OK;
	 }                           
		m_timeElapsed.FuncTimerClose();

  }
  
  return hr;
}

//Feb. 8, 2021
EMS_RESULT  CDigitalBeamFormerEx::PerformDDC1( const double *DDCPrototypeFilter,
	const ULONG   DDCPrototypeFilterLen, const double  *DDCSubFilterRE, const double  *DDCSubFilterIM, 
	const float *af, EMSCOMPLEXD *ac)
{
	const double A[4] = { 0.587785252292473,  -0.309016994374947,  -0.951056516295153,  -0.809016994374947};
	
	const double c[20] ={ 
	 1,  A[0],  A[1],  A[2],  A[3],
	 0, -A[3], -A[2], -A[1], -A[0],
	-1, -A[0], -A[1], -A[2], -A[3],
	 0,  A[3],  A[2],  A[1],  A[0] };
	
	const double s[20] ={ 
	 0,  A[3],  A[2],  A[1],  A[0], 
	 1,  A[0],  A[1],  A[2],  A[3],
	 0, -A[3], -A[2], -A[1], -A[0],
	-1, -A[0], -A[1], -A[2], -A[3] }; 
	
	/* 
	const double c[20]={
	1.000000000000000,   0.587785252292473,  -0.309016994374947,  -0.951056516295153,  -0.809016994374947,  -0.000000000000000,
    0.809016994374947,   0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292473,
    0.309016994374945,   0.951056516295153,   0.809016994374948,   0.000000000000001,  -0.809016994374947,  -0.951056516295154,
   -0.309016994374948,   0.587785252292474  };
	
	const double s[20] = {
	 0,                  -0.809016994374947,  -0.951056516295154,  -0.309016994374948,   0.587785252292473,   1.000000000000000,
     0.587785252292474,  -0.309016994374947,  -0.951056516295154,  -0.809016994374948,  -0.000000000000000,   0.809016994374947,
     0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292474,   0.309016994374945,
     0.951056516295153,   0.809016994374947 };  
	 */

	const ULONG N = 1000000;
	ULONG Q = DDCPrototypeFilterLen; // Q must be an integer multiple of 20
	ULONG B = DDCPrototypeFilterLen/20;
	
	ULONG index, bidx1, bidx2, isample, jsample, tmpidx;
	
	EMS_RESULT hr = EMS_BAD_PARAM;
	
	for (index=0; index< Q; index++)
	{
		ac[index].re = 0.0;
		ac[index].im = 0.0;
		for (jsample=0; jsample <= index; jsample++)
		{
			tmpidx = jsample-(jsample/20)*20;
			ac[index].re += DDCPrototypeFilter[index-jsample]*c[tmpidx]*af[jsample];	
			ac[index].im += DDCPrototypeFilter[index-jsample]*s[tmpidx]*af[jsample];
		}
	}			

    for (bidx1=0; bidx1<(N-Q)/20; bidx1++)
	{
		for(isample=0; isample<20; isample++)
		{
			//ac[Q+bidx1*20+isample].re=0.0;
			//ac[Q+bidx1*20+isample].im=0.0;
			/* 
			for(bidex2=0; bidx2 < B; bidx2++)
			{
				 for (jsample=0; jsample < 20; jsample++)
				 {
					  //index= Q+bidx1*20+isample;
					  //ac[Q+bidx1*20+isample].re += DBFDDCPrototypeFilter[bidx2*20+jsample]*
					  //              cos(fc*PI*(index-bidx2*20-jsample))*af[index-bidx2*20-jsample];	
					  //ac[Q+bidx1*20+isample].im += DBFDDCPrototypeFilter[bidx2*20+jsample]*
					  //              (-sin(fc*PI*(index-bidx2*20-jsample)))*af[index-bidx2*20-jsample];
					  //index= Q+bidx1*20+isample;
					  //ac[Q+bidx1*20+isample].re += DBFDDCPrototypeFilter[bidx2*20+jsample]*
					  //                 cos(fc*PI*(isample-jsample))*af[index-bidx2*20-jsample];	
					  //ac[Q+bidx1*20+isample].im += DBFDDCPrototypeFilter[bidx2*20+jsample]*
					  //              (-sin(fc*PI*(isample-jsample)))*af[index-bidx2*20-jsample];
					  //index= Q+bidx1*20+isample;
					  //ac[Q+bidx1*20+isample].re += DBFDDCSubFilterRE[isample][bidx2*20+jsample]*af[index-bidx2*20-jsample];	
					  //ac[Q+bidx1*20+isample].im += DBFDDCSubFilterIM[isample][bidx2*20+jsample]*af[index-bidx2*20-jsample];
				 }
				 
				 //
				   for(isample=0; isample<20; isample++)
				   {
					   for (jsample=0; jsample<Q; jsample++)
					   { 
						   //DBFDDCSubFilterRE[isample][jsample] = 
						   //    DBFDDCPrototypeFilter[jsample]*cos(fc*PI*(isample-(jsample-(jsample/20)*20)));
				           
						   //DBFDDCSubFilterIM[isample][jsample] = 
				           //   -DBFDDCPrototypeFilter[jsample]*sin(fc*PI*(isample-(jsample-(jsample/20)*20)));
							
						   DBFDDCSubFilterRE[isample][jsample] = 
						       DBFDDCPrototypeFilter[jsample]*cos(fc*PI*(isample-jsample));
				           
						   DBFDDCSubFilterIM[isample][jsample] = 
				              -DBFDDCPrototypeFilter[jsample]*sin(fc*PI*(isample-jsample));  		  
					   }
					} 
			*/
			
			index= Q+bidx1*20+isample;
			ac[index].re=0.0;
			ac[index].im=0.0;
			for(jsample=0; jsample < Q; jsample++)
			{	 
			    //index= Q+bidx1*20+isample;
			    //ac[Q+bidx1*20+isample].re += DBFDDCSubFilterRE[isample][jsample]*af[index-jsample];	
			    //ac[Q+bidx1*20+isample].im += DBFDDCSubFilterIM[isample][jsample]*af[index-jsample];	

                //ac[Q+bidx1*20+isample].re += DBFDDCSubFilterRE[isample*Q+jsample]*af[index-jsample];	
			    //ac[Q+bidx1*20+isample].im += DBFDDCSubFilterIM[isample*Q+jsample]*af[index-jsample];
				
                ac[index].re += DDCSubFilterRE[isample*Q+jsample]*af[index-jsample];	
			    ac[index].im += DDCSubFilterIM[isample*Q+jsample]*af[index-jsample];		
			}	
		}		
	}
 
	hr =EMS_OK;
    
	return hr;
}	


// Feb. 8, 2021
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation9(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
		
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
        memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
				 
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {

            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
                continue;
				 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   
            																																				
             //Perform digital downconversion via frequency shifting by translating 150KHz to 0 KHz
			
			 hr = PerformDDC1( dbf_ddc_prototypefilter120, 120, dbf_ddc_subfilters120_real, dbf_ddc_subfilters120_imag, 
	                  m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);			
        }

    }
    return hr;
}







// Feb. 9, 2021
EMS_RESULT  CDigitalBeamFormerEx::PerformSymFIRFiltering1( const double *SymFirFilter, const int Q, 
      const EMSCOMPLEX *InputArray, const int N, 
            EMSCOMPLEX *OutputArray)
{
	//Q=2M must be even in this implementation and must be less than or equal to 128 !
	
	int index, jsample;
	
	EMS_RESULT hr = EMS_FALSE;
	
	int M = Q/2;
	
	const int BUFFER_LEN = 128/2;
	double buffer_re[BUFFER_LEN];
	double buffer_im[BUFFER_LEN];
	
	//memset(OutputArray, 0, sizeof(EMSCOMPLEX));
	memset(OutputArray, 0, sizeof(EMSCOMPLEX)*N);
	//for (index=0; index< N; index++)
	//{
		//OutputArray[index].re = 0.0;
		//OutputArray[index].im = 0.0;
		/* if (index<Q)
		{
			OutputArray[index].re = 0.0;
		    OutputArray[index].im = 0.0;
			for (jsample=0; jsample <= index; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*InputArray[index-jsample].re;	
				OutputArray[index].im += SymFirFilter[jsample]*InputArray[index-jsample].im;
			}		
		}else
		{ */
	    for(index=Q-1; index<N; index++)
		{
			/* 
			for (jsample=0; jsample < M; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*(InputArray[index-jsample].re + InputArray[index-(Q-1)+jsample].re );	
				OutputArray[index].im += SymFirFilter[jsample]*(InputArray[index-jsample].im + InputArray[index-(Q-1)+jsample].im );
			}	 
			*/
			for (jsample=0; jsample < M; jsample++)
			{
				buffer_re[jsample] = InputArray[index-jsample].re + InputArray[index-(Q-1)+jsample].re;
				buffer_im[jsample] = InputArray[index-jsample].im + InputArray[index-(Q-1)+jsample].im;
			}
			OutputArray[index].re = emssDotProd64(SymFirFilter, buffer_re, M);
			OutputArray[index].im = emssDotProd64(SymFirFilter, buffer_im, M);
			
		}	
	//}
 
	hr =EMS_OK;
    
	return hr;
}	


// Feb. 9, 2021
EMS_RESULT  CDigitalBeamFormerEx::PerformIQDemodulation10(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
	
	const double c[20]={
	1.000000000000000,   0.587785252292473,  -0.309016994374947,  -0.951056516295153,  -0.809016994374947,  -0.000000000000000,
    0.809016994374947,   0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292473,
    0.309016994374945,   0.951056516295153,   0.809016994374948,   0.000000000000001,  -0.809016994374947,  -0.951056516295154,
   -0.309016994374948,   0.587785252292474  };
	
	const double s[20] = {
	 0,                  -0.809016994374947,  -0.951056516295154,  -0.309016994374948,   0.587785252292473,   1.000000000000000,
     0.587785252292474,  -0.309016994374947,  -0.951056516295154,  -0.809016994374948,  -0.000000000000000,   0.809016994374947,
     0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292474,   0.309016994374945,
     0.951056516295153,   0.809016994374947 };
		
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
        memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
				 
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
                continue;
				 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   
            																																				
             //Perform frequency shifting by translating 150KHz to 0 KHz
 			 for (index = 0; index < DBF_SAMPLE_SIZE/20; index++)
             {    
		          for(int j = 0; j < 20; j++)
				  {
                      acIQSeq[index*20+j].re =  c[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]);
	                  acIQSeq[index*20+j].im =  s[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]); 
				  }				  
             }
			 
#if DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 1
	
             hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 128, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		 

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 2
	
	         hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 32,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 3
	
             hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 16,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);	

#endif
			 
        } 
    }
    return hr;
}


// Feb. 9, 2021
EMS_RESULT  CDigitalBeamFormerEx::ComputeCovarianceMatrix10(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix)
{

  EMS_RESULT hr = EMS_BAD_PARAM;

  unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
  
  if ( clpRawTimeSeries)
  {
	 //Perform baseband IQ demodulation
	 memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof(float));
	 memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ));
	 {
        m_timeElapsed.FuncTimerStart("PerformIQDemod10" );		
		hr = PerformIQDemodulation10(clpRawTimeSeries, acIQMatrix);
		m_timeElapsed.FuncTimerClose();
	 }
	 m_timeElapsed.FuncTimerStart("ComputeCovaMat10");
	 if (EMS_OK == hr)
	 {  
		hr = CalculateCovarianceMatrix3(acIQMatrix, acCovarianceMatrix);
		m_timeElapsed.FuncTimerClose();
	 }                           
  }
  
  return hr;
}



//Feb. 9, 2021
EMS_RESULT  CDigitalBeamFormerEx::CalculateCovarianceMatrix3( const EMSCOMPLEX *acIQMatrix, EMSCOMPLEX *acCovarianceMatrix)
{
	const int BLEN =32000;
    const int B=(DBF_SAMPLE_SIZE/BLEN); //31;
    const int RLEN=DBF_SAMPLE_SIZE-B*BLEN; //8000;
	int index, i, j, b, k,n, m;
	EMSCOMPLEX buffer[BLEN];
	EMSCOMPLEX temp;
    //upper triangular portion of hermitian matrix
	for(i=0; i<NUM_CHANNELS; i++)
	{
		for(j=i;j<NUM_CHANNELS;j++)
		{
			index=i*NUM_CHANNELS+j;
			acCovarianceMatrix[index].re =0.0;
			acCovarianceMatrix[index].im =0.0;
			for(b=0; b< B; b++)
			{
				n= i*DBF_SAMPLE_SIZE+b*BLEN;
				m= j*DBF_SAMPLE_SIZE+b*BLEN;	
				
				/* 
				for(k=0; k<BLEN; k++)
				{
				    acCovarianceMatrix[index].re +=  
					  ( (acIQMatrix[n+k].re)*(acIQMatrix[m+k].re) 
						+ (acIQMatrix[n+k].im)*(acIQMatrix[m+k].im) );	 
				
				    acCovarianceMatrix[index].im +=   
					  ( (acIQMatrix[m+k].re)*(acIQMatrix[n+k].im) 
						 - (acIQMatrix[n+k].re)*(acIQMatrix[m+k].im) );	
				}	 
				*/
                memset(buffer, 0, sizeof(EMSCOMPLEX)*BLEN);
				emscbConj2(acIQMatrix+m, buffer, BLEN);
				temp = emscDotProd(acIQMatrix+n, buffer,BLEN);
                acCovarianceMatrix[index].re += temp.re;
				acCovarianceMatrix[index].im += temp.im;
			}	
			
			//remainder
			n= i*DBF_SAMPLE_SIZE+B*BLEN;
			m= j*DBF_SAMPLE_SIZE+B*BLEN;	
			/* 
			for(k= 0; k< RLEN; k++)
			{
				acCovarianceMatrix[index].re +=  
					  ( (acIQMatrix[n+k].re)*(acIQMatrix[m+k].re) 
						+ (acIQMatrix[n+k].im)*(acIQMatrix[m+k].im) );	 
				
				acCovarianceMatrix[index].im +=   
					  ( (acIQMatrix[m+k].re)*(acIQMatrix[n+k].im) 
						 - (acIQMatrix[n+k].re)*(acIQMatrix[m+k].im) );	
			}	 
			*/
			memset(buffer, 0, sizeof(EMSCOMPLEX)*RLEN);
			emscbConj2(acIQMatrix+m, buffer, RLEN);
			temp = emscDotProd(acIQMatrix+n, buffer,RLEN);
			acCovarianceMatrix[index].re += temp.re;
			acCovarianceMatrix[index].im += temp.im;
		}
	}
	
	//lower triangular portion 
	for(int i=1; i<NUM_CHANNELS; i++)
	{
		for(int j=i-1;j >= 0;j--)
		{
			acCovarianceMatrix[i*NUM_CHANNELS+j].re = acCovarianceMatrix[j*NUM_CHANNELS+i].re;
			acCovarianceMatrix[i*NUM_CHANNELS+j].im = -acCovarianceMatrix[j*NUM_CHANNELS+i].im;	
		}
	}
	
	
	for( int iIndx = 0; iIndx < NUM_CHANNELS*NUM_CHANNELS; iIndx++ )
	{
		acCovarianceMatrix[iIndx].re /= DBF_SAMPLE_SIZE;
		acCovarianceMatrix[iIndx].im /= DBF_SAMPLE_SIZE;
	}
	
	return EMS_OK;
}




