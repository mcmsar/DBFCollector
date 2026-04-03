/********************************************************************
*	Module:			emsDBF.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	06/07/09		rcr		start

********************************************************************/
#ifndef INC_EMSDBF
#define INC_EMSDBF

#include <string>
#include "emstypes.h"
#include "emserror.h"
#include <stdio.h>
#include "sigproc.h"
#include "emsDBFtypes.h"
//#include "emsDBFDataMgr.h"
#include "HGTQueueTS.h"

#include "wave/waveformatchunk.h"
#include "wave/waveextchunk.h"
#include "wave/waveex.h"
#include "HGTEigenVectors.h"
#include "TimeElapsed.h"


#define INITGUID
#include <initguid.h>
#include "datatransmitter.h"
#include <fstream>

// {1E47D91E-DE7F-4b86-98BF-B6306E54E403}
DEFINE_GUID(CLSID_DataXmitter, 
			0x1e47d91e, 0xde7f, 0x4b86, 0x98, 0xbf, 0xb6, 0x30, 0x6e, 0x54, 0xe4, 0x3);


using std::string;
using std::wstring;

#define DBF_MAX_CHANNELS    (32)		// maximum number of input channels (based upon ADC board capabilities)
#define NUM_CHANNELS		(31)
#define DBF_NUM_ELEMENTS	(31)		// number of antenna elements (assume 1 channel is reserved for 1 pPS signal)
#define MAX_BEAMS  (10)

#define DBF_MAX_SATELLITES  (10)			// maximum number of DBF tracked satellites per face

#define DBF_SAMPLE_SIZE		(1000000)	// maximum number of samples per channel per collection interval
#define DBF_OUTPUT_SIZE		(800000)    // output WAV file size (200kHz for 2 seconds)
#define DBF_SAMPLE_RATE		(500000)	// maximum number of samples per channel per second
#define DBF_LOG20_SIZE		(1048576)	// 2^20 maximum Real FFT size
#define DBF_LOG19_SIZE      (524288)	// 2^19 complex FFT size
#define DBF_LOG18_SIZE      (262144)	// 2^18 complex FFT size
#define MEO_MIN_ELEVATION	20.0

#define COVARIANCE_SIZE     (DBF_NUM_ELEMENTS * DBF_NUM_ELEMENTS)
#define DBF_LOG20			(20)
#define DBF_LOG19           (19)
#define ADC_OFFSET          (524288)
//#define ADC_OFFSET          (32768)
#define PULSE_SHAPE_SIZE    (100)
#define PULSE_LENGTH_MAX	(3000)      // maximum pulse length in samples ( 3 msec approximately )
//#define MAX_SATELLITE_ID  (400)			// maximum sat ID.
// length of pre-designed FIR bandpass and lowpass filters


#define MAX_TEST_FILES		(20)		// Maximum number of test raw data files 
#define PI     (3.141592653589793)

#define  EIGEN_VECTOR_IS_ROW_MAJOR  1  // ???

//snl test
#include "criticalsection.h"

class CDigitalBeamFormer
{
public:

	~CDigitalBeamFormer( void );
	CDigitalBeamFormer( CEMSQueue<DBFTrackingData >& );
	CEMSQueue<DBFTrackingData >&	m_qrefDBFBeamVectors;
	
	CDigitalBeamFormer( const CDigitalBeamFormer& x ) ;

	virtual EMS_RESULT Initialize( const TCHAR *cDir);

	EMS_RESULT SetRawData( const unsigned char* abytes, int iSize );

	EMSVECTORD Convert2UnitVector( const double dAzimuth, const double dElevation );

	EMS_RESULT BufferStatistics( const unsigned long *clpRawTimeSeries );

	EMS_RESULT RemoveTimePulse( float *afRawTimeSeries);

	EMS_RESULT ComputeDBFBeamVectors( INT nNumBeams, const EMSCOMPLEX *m_acCovariance);
	EMS_RESULT PerformEigenDecomposition(const EMSCOMPLEX *m_acCovariance, float* EigenValues, MKL_Complex8 *acEigenVectors);
	EMS_RESULT PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors);

	EMS_RESULT DBFprocessorPP( EMSTIME tm ); // PRedicted Phase
	EMS_RESULT DBFprocessorCP( EMSTIME tm ); // Carrier Phase
	EMS_RESULT DBFprocessorEP( EMSTIME tm ); // Eigenvector Phase
	EMS_RESULT DBFprocessorRAW( EMSTIME tm ); // Raw data

	EMS_RESULT DBFprocessorEP1( EMSTIME tm, const unsigned long *clpRawTimeSeries );

	EMS_RESULT DBFCorrectPhaseBias( EMSCOMPLEX *FFTdata, ULONG length );
	EMS_RESULT ComputeNullingVectors(const EMSCOMPLEX *acNormalizedEigenVectors, const int nNumBeams, EMSCOMPLEX *acDBFBeamVectors);
	EMS_RESULT ApplyDBFBeamVectors( ULONG m_ulSatellites );
	EMS_RESULT ComputeCovariance( ULONG ulNumSamples );
	EMS_RESULT ComputeChannelData(); 

	//virtual EMS_RESULT DBFprocessor8( const int nNumBeams/*, EMSCOMPLEXD **asBeamMatrix, EMSCOMPLEXD **acBeamMatrix*/){ return S_OK; }
	EMS_RESULT GetADCBuffer( const char *szFilename1, const char *szFilename2, const char *szFilename3, const char *szFilename4 );
	EMS_RESULT GetPassSchedule( EMSTIME tm );
	EMS_RESULT SetPassSchedule( EMSDBFPASSRECORDS* pPassRecords, EMSTIME tm );

	WORD       GetProcess( ){ return ( m_aPassSchedule.rec[0].wProcessID ); };

	void ProcessAll();

	void Reset( );

	EMS_RESULT TestDBFprocessor( int nProcess );
	
	int DirectoryList(string folder, string filetype);

	static int GetNextObjID() {return ms_iNextObjectID++;}

	static void SetSPIP( std::string SPIP ) 
	{ 
		m_wsSPIP = std::wstring( SPIP.begin(), SPIP.end() );
	}
	//funcs added on Sichun's behalf
	
protected:
	HRESULT _InitDT();
	void _OutputWave( EMSTIME tm, const ULONG culIndex );
	void _OutputWaveEx( EMSTIME tm, ULONG culNumSats);
	void _OutputWaveExProcess1( EMSTIME tm, ULONG culNumSats  );

	void _OutputWaveFile( unsigned char* aData, EMSTIME tm, ULONG culSize );
	EMSTIME _SetActualTime( EMSTIME tm );
	void _SetActualTimeNew();

	void _OutputCalibData( EMSTIME tm );
	void _OpenCalibFile();

	int _GetMostCommonIndex( ULONG* arr, int iCount);

	void _EMScbPowerSpectr(const EMSCOMPLEX *src, float *spectr,ULONG length);
	void _EMSsbNormalize( const float *src, float *dst, ULONG n, const float valuesub, const float valuediv );
	void _EMScbMpy1( const EMSCOMPLEX val, EMSCOMPLEX *dst, ULONG n );
	void _EMScbAdd2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, ULONG n );
	void _EMSsbMpy1( const float val, float *dst, ULONG n );

	void _EMSGetPhaseOffsets( const unsigned long *clpRawTimeSeries, ULONG ulSatMaxFreq, double *dPeakPhase );


	float _EMSsMean(const float *vec, ULONG len);
	double _EMSsMeanStdDev(const float *vec, ULONG len, double* pfMean );
	float _EMSsMaxExt(const float  *vec, int len, ULONG* index);
	float _EMSsMinExt(const float  *vec, int len, ULONG* index);

	void _OutputBufferPhases( const CEMSTime& emsCurrTime );

	void _OutpuRawDigitalDataFile( unsigned char* aData, EMSTIME tm, ULONG culSize );

	BOOL  _BuildDBFSatsTrackingInfo( EMSCOMPLEXD*);

	void  _FormatWAVoutput( int isat );

//private: // methods

private: // data
	//EMSCOMPLEX*				m_acFFTdata1;
	EMSCOMPLEX*				m_acCovariance;     // Covariance matrix
	EMSCOMPLEX*				m_acMatrix;
	//EMSCOMPLEX*				m_acMatrixT;
	
protected:
	//EMSCOMPLEX**			m_acFFTdata;
	EMSCOMPLEX*				m_acTemp1;
	EMSCOMPLEX*				m_acTemp2;
	EMSCOMPLEX*				m_acTemp3;

	//ULONG**					m_nBeam;
	short**					m_nBeam;

	FILE 					*m_lpTraceFile;
	FILE 					*m_lpOutputFile;
	FILE*					m_lpCalibFile;

	TCHAR					m_cFilePath[256];


	ULONG					m_ulChannels;
	ULONG					m_ulSatellites;
	ULONG					m_ulSamplesPerChannel;

	unsigned long*			m_asRawTimeSeries;
	short*					m_asPhaseVector;
	short*					m_asDBFVector;

	float*					m_afRawInputSamples;
	float*					m_afPowerSpectrum;
	float*					m_afPowerSpectrum1;
	
	ULONG					m_ulPhaseBiasFrequency;

	ULONG					m_ulStartPPS;		// One second pulse start sample index
	ULONG					m_ulLastStartPPS;	// The last one second pulse start sample index
	ULONG					m_ulStopPPS;		// One second pulse stop sample index
	ULONG					m_ulMarkerBitRate;	// Number of samples between one second pulses
	double					m_dMeanADC;			// Mean of ADC values
	double					m_dStdDevADC;		// Standard Deviation of ADC values
	double					m_dMaxPower;		// Maximum power
	double					m_dMinPower;		// Minimum power
	ULONG					m_ulMaxPowerIndex;  // frequency index of maximum power
	ULONG					m_ulMaxPowerIndex1;  // frequency index of maximum power

	float*					m_afPulseShape;    // 1 PPS pulse shape

	float*					m_afTemp1;
	float*					m_afTemp2;
	float*					m_afChan0;

	CEMSTime                m_oLastPPS;

	EMSTIME					m_timeActual;
	EMSTIME					m_timeStart;
	EMSTIME					m_timeFinish;
	double					m_dElapsedTime;
	double					m_dAverageTime;
	int						m_nCounter;
	ULONG					m_ulRawBuffSize;

	float	m_afMean[DBF_MAX_CHANNELS];
	float m_afStdDev[DBF_MAX_CHANNELS];

	IEMSDataTransmitter*    m_pDataTransmit;

	EMSDBFPASSRECORDS		m_aPassSchedule;

	EMSDBFMAINTENANCE		m_aMaintenance;

	//EMSDBFARRAY				m_aDBFplate;

	EMSDBFCALIBRECORD       m_LastCalibRecord;

	bool  m_bOutputOK;

	EMSDBFBUFFERPHASE      m_emsDBFBufferPhase;

	int						m_iObjectID;
	static int              ms_iNextObjectID;
	//snl testing for dbfphase buffer log
	static CEMSTime				m_oDBFBufferPhaseLastWriteTime;
	//covariance file sent time
	static CEMSTime				m_oDBFCovarFileLastWriteTime;
	static BOOL					m_bIsCovarFileSendTime;
	static	std::wstring		m_wsSPIP;
	bool _IsTimeToCopyBufferPhaseFile( const EMSTIME& oCurrentTime );
	void _IsTimeToCopyCovarFile( const EMSTIME& oCurrentTime );
	

	EMSCOMPLEX*		m_acDBFBeamVectors/*[MAX_BEAMS*NUM_CHANNELS]*/; 

	int*			m_iBeamIDs;
	int*			m_iPredictedSATIDs;
	DOUBLE*			m_dProbability;
	int*			m_iPrevPassSchedSATIDs;

	char*			m_FileNames;

	//for debug
	//CTimeElapsed	m_timeElapsed;
	//snl commented
	//CEMSDBFDataMgr			m_oDBFpass;

	// Process flag establishes input/output and beamformer process	
	WORD			m_ProcessFlag;
	int*			m_iOutputBuffer;
	ULONG			m_ulOutputLength;

#ifdef _LOGPHASECORR_

	static void LogPhaseCorrection ( INT64, std::string, ULONG, double, ULONG, EMSCOMPLEX &param1 );
	private:
		static FILE *m_pLogPhaseCorrection;		
		static CEMSCriticalSection		m_csFileHandler;

#endif		
		
//private: // constants

};


#endif // INC_EMSDBF



