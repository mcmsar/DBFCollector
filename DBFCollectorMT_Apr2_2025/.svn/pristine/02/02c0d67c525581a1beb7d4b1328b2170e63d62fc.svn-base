#ifndef __DBF_BEAMVECTORCALC_H__
#define __DBF_BEAMVECTORCALC_H__

#pragma once
#include "mkl_types.h"
//#include "emserror.h"
#include "SIGPROC.H"
#include "emsDBF.h"
#include "TimeElapsed.h"
#include "emsthread.h"
#include "HGTQueueTS.h"
class CDBFBeamVectorCalculator : public CEMSThread, public CApiObjBase
{
  public:
	 CDBFBeamVectorCalculator( CEMSQueue<DBFTrackingData>& );
	~CDBFBeamVectorCalculator();
	EMS_RESULT Initialize();

	void Start();
	void Stop();
	bool IsRunning() {return m_bRunning; }
	EMS_RESULT SetRawData( const unsigned char* abytes, int iSize, const EMSDBFPASSRECORDS& );

  protected:
		virtual void run();

  private: 
		EMS_RESULT _DBFProcessor8Impl( );
		EMS_RESULT PerformSymFIRFiltering( const double *SymFirFilter, const ULONG Q, const EMSCOMPLEXD *InputArray, const ULONG N, EMSCOMPLEXD *OutputArray);
		EMS_RESULT  PerformSymFIRFiltering1( const double *SymFirFilter, const int Q, const EMSCOMPLEX *InputArray, const int N, 
            EMSCOMPLEX *OutputArray);
		EMS_RESULT  PerformIQDemodulation7(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
		EMS_RESULT  ComputeCovarianceMatrix4( EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
		EMS_RESULT  PerformEigenDecomposition(const EMSCOMPLEXD *acCovarianceMatrix, 
                              float* EigenValues, MKL_Complex8 *acEigenVectors);;
		EMS_RESULT  PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors);
		EMS_RESULT  ComputeNullingVectors(const EMSCOMPLEXD *acNormalizedEigenVectors, 
		const int nNumBeams, EMSCOMPLEXD *acDBFBeamVectors);
		EMS_RESULT  ComputeDBFBeamVectors(const EMSCOMPLEXD *acCovarianceMatrix, const int nNumBeams,
		float *EigenValues,  MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors, EMSCOMPLEXD *acDBFBeamVectors );
		EMS_RESULT  PerformIQDemodulation10(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix);
		EMS_RESULT  ComputeCovarianceMatrix10(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
		EMS_RESULT  CalculateCovarianceMatrix1( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
		EMS_RESULT  CalculateCovarianceMatrix2( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
		EMS_RESULT  CalculateCovarianceMatrix3( const EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix);
		EMS_RESULT  CalculateCovarianceMatrix4( const EMSCOMPLEX *acIQMatrix, EMSCOMPLEX *acCovarianceMatrix);

		BOOL		_IsTimeToCalculateBeamVector();
		BOOL		_BuildDBFSatsTrackingInfo( EMSCOMPLEXD*);
  public:
  
  private:
		EMSCOMPLEXD *m_acDBFBeamVectors;
		float *m_asMatrix;
		ULONG m_ulSamplesPerChannel;
		ULONG m_ulChannels;
		unsigned long*			m_asRawTimeSeries;
		float*					m_afTemp1;
		CTimeElapsed	m_timeElapsed;
		bool        m_bRunning;
		bool        m_bInitialized;
		bool		m_bIsCalculating;
		CEMSCriticalSection		m_oCS;
		//EMSTIME					m_timeLast;
		EMSCOMPLEXD *m_acIQMatrix;
		CEMSQueue<DBFTrackingData>&			m_qrefDBFBeamVectors;
		EMSDBFPASSRECORDS		m_aPassSchedule;
		ULONG					m_ulSatellites;
		EMSTIME					m_timeActual;
		HANDLE					m_hProcessSignal ;
		//DBF tracking info
		int*						m_iBeamIDs;
		int*						m_iPredictedSATIDs;
		DOUBLE*						m_dProbability;
		int*						m_iPrevPassSchedSATIDs;
};

#endif
