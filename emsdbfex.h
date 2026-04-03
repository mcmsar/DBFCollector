#pragma once
#include "emsdbf.h"
#include "TimeElapsed.h"

//sichuns functions

// this option ranges from 1 to 5
#define DOWN_SAMPLING_OPTION  1

//this option ranges from 1 to 3
#define UP_SAMPLING_OPTION 2
class CDigitalBeamFormerEx : public CDigitalBeamFormer
{
public:
	CDigitalBeamFormerEx( CEMSQueue<DBFTrackingData >& );
	~CDigitalBeamFormerEx();
private:
	EMS_RESULT  PerformIQDemodulation(unsigned long *clpRawTimeSeries, EMSCOMPLEXD acIQMatrix[31][DBF_SAMPLE_SIZE]);
	EMS_RESULT  PerformIQDemodulation2(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformIQDemodulation3(unsigned long *clpRawTimeSeries, float *asMatrix, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformFIRFiltering( const double *FirFilter, const ULONG Q, const float *InputArray, const ULONG N, 
                    float *OutputArray);
	EMS_RESULT  PerformFIRFiltering( const double *FirFilter, const ULONG Q, const EMSCOMPLEXD *InputArray, const ULONG N, 
                    EMSCOMPLEXD *OutputArray);
	EMS_RESULT  PerformDownSampling( const double *FirFilter, const ULONG DownSamplingRate, 
           const EMSCOMPLEXD *InputArray, const ULONG N, EMSCOMPLEXD *OutputArray);
	EMS_RESULT  PerformReSampling( const double *FirFilter, const ULONG UpSamplingFactor, 
           const EMSCOMPLEXD *InputArray, const ULONG N, EMSCOMPLEXD *OutputArray);
	EMS_RESULT  PerformIQDemodulation4(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformIQDemodulation5(unsigned long *clpRawTimeSeries, const ULONG DownSamplingRate, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformIQDemodulation6(unsigned long *clpRawTimeSeries, const ULONG UpSamplingFactor
	, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformSymFIRFiltering( const double *SymFirFilter, const ULONG Q, const EMSCOMPLEXD *InputArray, const ULONG N, 
                    EMSCOMPLEXD *OutputArray);
	EMS_RESULT  PerformIQDemodulation7(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformIQDemodulation8(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformIQDemodulation9(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  PerformDDC1( const double *DDCPrototypeFilter,const ULONG   DDCPrototypeFilterLen, const double  *DDCSubFilterRE, const double  *DDCSubFilterIM, 
	const float *af, EMSCOMPLEXD *ac);
	EMS_RESULT  ComputeCovarianceMatrix4( EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  ComputeCovarianceMatrix5(const ULONG DownSamplingRate, EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  ComputeCovarianceMatrix6(const ULONG UpSamplingFactor, EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  ComputeCovarianceMatrix7(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  ComputeCovarianceMatrix9(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  PerformEigenDecomposition(const EMSCOMPLEXD *acCovarianceMatrix, 
                              float* EigenValues, MKL_Complex8 *acEigenVectors);;
	EMS_RESULT  PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors);
	EMS_RESULT  ComputeNullingVectors(const EMSCOMPLEXD *acNormalizedEigenVectors, 
       const int nNumBeams, EMSCOMPLEXD *acDBFBeamVectors);
	EMS_RESULT  ComputeDBFBeamVectors(const EMSCOMPLEXD *acCovarianceMatrix, const int nNumBeams,
    float *EigenValues,  MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors, EMSCOMPLEXD *acDBFBeamVectors );
	EMS_RESULT  PerformIQDemodulation(unsigned long *clpRawTimeSeries/*, EMSCOMPLEX acIQMatrix[31][DBF_SAMPLE_SIZE]*/);
	EMS_RESULT  PerformSymFIRFiltering1( const double *SymFirFilter, const int Q, const EMSCOMPLEX *InputArray, const int N, 
            EMSCOMPLEX *OutputArray);
	EMS_RESULT  PerformIQDemodulation10(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
	EMS_RESULT  ComputeCovarianceMatrix10(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  CalculateCovarianceMatrix1( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  CalculateCovarianceMatrix2( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT  CalculateCovarianceMatrix3( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
	EMS_RESULT ComputeDBFBeamVectors( INT nNumBeams );
	//void _OutputWaveEx( EMSTIME tm, ULONG culNumSats/*,EMSCOMPLEXD**  */);
	//void _OutputWaveEx( EMSTIME tm);
	//
public:
	virtual EMS_RESULT Initialize( const TCHAR *cDir);

	//EMS_RESULT DBFprocessor7(/*unsigned long *clpRawTimeSeries, float *phaseBias */);
	EMS_RESULT _ComplexMatrixInverse( EMSCOMPLEXD* acMatrix, EMSCOMPLEXD* acMatrixInverse, ULONG ulMSize );
	virtual EMS_RESULT DBFprocessor8( const int nNumBeams/*, EMSCOMPLEXD **asBeamMatrix, EMSCOMPLEXD **acBeamMatrix*/);

	//EMS_RESULT DBFprocessor8_v4( const int nNumBeams, EMSCOMPLEX asBeamMatrix[MAX_BEAMS][DBF_SAMPLE_SIZE], EMSCOMPLEX acBeamMatrix[MAX_BEAMS][DBF_SAMPLE_SIZE] );
	virtual EMS_RESULT DBFprocessor8_v4( const int nNumBeams/*, EMSCOMPLEXD **asBeamMatrix, EMSCOMPLEXD** acBeamMatrix*/);
	//virtual EMS_RESULT DBFprocessor8_v5(const int nNumBeams/*, EMSCOMPLEXD acBeamMatrix[MAX_BEAMS][DBF_SAMPLE_SIZE]*/ );
	//virtual EMS_RESULT DBFprocessor8_v6(const int nNumBeams/*, EMSCOMPLEXD acBeamMatrix[MAX_BEAMS][DBF_SAMPLE_SIZE]*/ );
private:
	EMSCOMPLEXD _EMScMean(const EMSCOMPLEXD *vec, ULONG len);
	double _EMScMeanStdDev(const EMSCOMPLEXD *vec, ULONG len, EMSCOMPLEXD* pfMean );
	void _EMScNormalize( const EMSCOMPLEXD *src, EMSCOMPLEXD *dst, ULONG n, const EMSCOMPLEXD& valuesub, const float valuediv );
	EMS_RESULT DBFprocessor9( /*const unsigned long *clpRawTimeSeries,*/ int iSatIndex );
	EMS_RESULT DBFprocessor9By2( int iSatIndex );
private:
	//CDigitalBeamFormer m_dbfObj;
	float *m_asMatrix;
	std::ofstream m_phaseBiasFile;
	float *afISeq;
	
	//float *afQSeq;
		float *afISeq1; 
	
	float *afQSeq1;
	
	EMSCOMPLEXD *acIQSeq;
		
		
	//EMSCOMPLEXD *acIQSeq1 ;

	//EMSCOMPLEXD *acISeq2;
	
	//EMSCOMPLEXD *acQSeq2;
		
	//EMSCOMPLEXD *acIQSeq2; 
		
	//EMSCOMPLEXD  *acFFTdata;
	EMSCOMPLEX  *m_acFFTdataSum;

	//EMSCOMPLEXD  **acFFTdataMatrix;
	/*float *afPowerSpectrum;
		
	float *afPowerSpectrumSum ;
*/
	//static FILE *m_pLogPhaseBias;
	//EMSCOMPLEX acIQMatrix[31][DBF_SAMPLE_SIZE];
	EMSCOMPLEXD *m_acIQMatrix;
	//EMSCOMPLEXD **acIQMatrix;

	//EMSCOMPLEXD m_acDBFBeamVectors[MAX_BEAMS*NUM_CHANNELS]; 
	EMSCOMPLEXD *m_acDBFBeamVectors/*[MAX_BEAMS*NUM_CHANNELS]*/; 

	EMSCOMPLEXD** m_asBeamMatrix;
	EMSCOMPLEXD** m_acBeamMatrix;
	//CEMSQueue<DBFTrackingData >&			m_qrefDBFBeamVectors;

	//for debug
	CTimeElapsed	m_timeElapsed;
};