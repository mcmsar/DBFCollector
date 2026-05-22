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
#include "emsDBFtypes2.h"
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

// {6B134451-0FF9-47AB-AFAC-8A2DBCBEA593}
DEFINE_GUID(CLSID_DataXmitter2,
	0x6b134451, 0x0ff9, 0x47ab, 0xaf, 0xac, 0x8a, 0x2d, 0xbc, 0xbe, 0xa5, 0x93);


using std::string;
using std::wstring;

#define DBF_MAX_CHANNELS    (32)		// maximum number of input channels (based upon ADC board capabilities)
#define NUM_CHANNELS		(31)
#define DBF_NUM_ELEMENTS	(31)		// number of antenna elements (assume 1 channel is reserved for 1 pPS signal)
#define DBF_CENTRE_ELEMENT  (23)		// Central element of the array
#define DBF_FREQ_OFFSET		50000.0			// 0 kHz offset of element filter by default
#define DBF_FREQ_BANDWIDTH	100000		// MEO satellite downlink 100kHz bandwidth

#define MAX_BEAMS			(5)
#define DBF_MAX_SATELLITES  (5)			// maximum number of DBF tracked satellites per face

#define DBF_SAMPLE_SIZE		(1000000)	// maximum number of samples per channel per collection interval
#define DBF_OUTPUT_SIZE		(800000)    // output WAV file size (200kHz for 2 seconds)
#define DBF_SAMPLE_RATE		(500000)	// maximum number of samples per channel per second
//#define DBF_SAMPLE_RATE		(1000000)	// maximum number of samples per channel per second
#define DBF_LOG20_SIZE		(1048576)	// 2^20 maximum Real FFT size
#define DBF_LOG19_SIZE      (524288)	// 2^19 complex FFT size
#define DBF_LOG18_SIZE      (262144)	// 2^18 complex FFT size
#define DBF_LOG17_SIZE      (131072)	// 2^17 complex FFT size
#define DBF_LOG16_SIZE      (65536)		// 2^16 complex FFT size
#define MEO_MIN_ELEVATION	20.0        // Minimum plate elevation allowed


#define COVARIANCE_SIZE     (DBF_NUM_ELEMENTS * DBF_NUM_ELEMENTS)
#define DBF_LOG20			(20)
#define DBF_LOG19           (19)
#define DBF_LOG18           (18)
#define DBF_LOG17           (17)
#define DBF_LOG16           (16)
#define ADC_OFFSET          (524288)
//#define ADC_OFFSET          (32768)
#define PULSE_SHAPE_SIZE    (100)
#define PULSE_LENGTH_MAX	(3000)      // maximum pulse length in samples ( 3 msec approximately )

#define MAX_TEST_FILES		(20)		// Maximum number of test raw data files 
#define PI					(3.141592653589793)

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

	EMS_RESULT DBFprocessorPP( EMSTIME tm ); // Predicted Phase
	EMS_RESULT DBFprocessorCP( EMSTIME tm ); // Carrier Phase
	EMS_RESULT DBFprocessorEP( EMSTIME tm ); // Eigenvector Phase
	EMS_RESULT DBFprocessorRAW( EMSTIME tm ); // Raw data

	EMS_RESULT DBFprocessorSUM( EMSTIME tm ); // utput Covariance and trace file update
	EMS_RESULT InitializeMemory();

	EMS_RESULT DBFCarrierTrack( EMSTIME tm, ULONG *m_ulFreqIndex, float *m_fMaxpower );
	EMS_RESULT BiasEstimator( EMSTIME tm );
	EMS_RESULT ComputeNullingVectors(const EMSCOMPLEX *acNormalizedEigenVectors, const int nNumBeams, EMSCOMPLEX *acDBFBeamVectors);
	EMS_RESULT ApplyDBFBeamVectors( ULONG m_ulSatellites, bool bTimeFreqFlag, bool bBandwidthFlag );
	EMS_RESULT ComputeCovariance( ULONG ulNumSamples );
	EMS_RESULT ComputeChannelData( bool bTimeFreqFlag, bool bBandwidthFlag ); 

	EMS_RESULT GetADCBuffer( const char *szFilename1, const char *szFilename2, const char *szFilename3, const char *szFilename4 );
	EMS_RESULT GetPassSchedule( EMSTIME tm );
	EMS_RESULT SetPassSchedule( EMSDBFPASSRECORDS2* pPassRecords, EMSTIME tm );

	EMS_RESULT ConvertComplex2Real( EMSCOMPLEX* cData, float* fData, ULONG ulNpts );
	
	EMS_RESULT SatelliteIdentify(ULONG m_ulSatellites );

	EMS_RESULT	InitializeTOAFOA( EMSTIME timestamp);
	
	EMS_RESULT	SeparationAngle( ULONG m_ulSatellites );

	bool	    SatelliteTOAFOA(  int isat );

	bool		IdentifyTOAFOA( EMSTIME tm, EMSCOMPLEX* acDBFBeamVectors );

	bool		ReferenceBeaconCheck(  int isat, ULONG* ulFreqIndex, float* fCNR );

	bool		CheckBit(  char cHex[36], int iBit );

	WORD        GetProcess( ){ return ( m_aPassSchedule.rec[0].wProcessID ); };

	void ProcessAll();

	void Reset( );

	EMS_RESULT TestDBFprocessor( int nProcess );
	int DirectoryList(string sfolder, string sfiletype);

	static int GetNextObjID() {return ms_iNextObjectID++;}

	static void SetSPIP(std::string SPIP);
	static void SetSPIP2(std::string SPIP2);

	void SetFrequencyOffset( float fHz ) { m_fFrequencyOffset = fHz; }
	float GetFrequencyOffset() const     { return m_fFrequencyOffset; }
	//funcs added on Sichun's behalf
	
protected:
	HRESULT _InitDT();
	HRESULT _InitDT2();
	void _OutputWaveEx( EMSTIME tm, ULONG culNumSats, bool bBandwidthFlag);

	void _OutputWaveFile( unsigned char* aData, EMSTIME tm, int iSat, bool bBandwidthFlag );
	EMSTIME _SetActualTime( EMSTIME tm );
	void _SetActualTimeNew();
	char _GetTimeNano( EMSTIME tm );

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
	int   _Power2( ULONG ulInput );
	int   _Hex2Int( char cHex );

	void _OutputBufferPhases( const CEMSTime& emsCurrTime );

	void _OutpuRawDigitalDataFile( unsigned char* aData, EMSTIME tm, ULONG culSize );

	BOOL  _BuildDBFSatsTrackingInfo( EMSCOMPLEXD*);

	void  _FormatWAVoutput( int isat );

	EMS_RESULT  _CopyData(  float* fTest, float fValue, ULONG nCount );



//private: // methods

private: // data
	EMSCOMPLEX*				m_acCovariance;     // Covariance matrix
	EMSCOMPLEX*				m_acMatrix;
	
protected:
	EMSCOMPLEX*				m_acTemp1;
	EMSCOMPLEX*				m_acTemp2;
	EMSCOMPLEX*				m_acTemp3;
	EMSCOMPLEX*				m_acFFTBeacon;

	short**					m_nBeam;

	FILE 					*m_lpTraceFile;
	FILE 					*m_lpOutputFile;
	FILE*					m_lpCalibFile;

	TCHAR					m_cFilePath[256];


	ULONG					m_ulChannels;
	ULONG					m_ulSatellites;
	ULONG					m_ulSamplesPerChannel;

	ULONG					m_ulFreqIndex;
	float					m_fMaxPower;
	float					m_fFrequencyOffset;  // Hz – set from DBFConstellation.xml <FrequencyOffset>

	unsigned long*			m_asRawTimeSeries;
//	short*					m_asPhaseVector;
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

	float					m_afMean[DBF_MAX_CHANNELS];
	float					m_afStdDev[DBF_MAX_CHANNELS];

	double					m_dSAmin[DBF_MAX_SATELLITES];  //min separation angle
	double					m_dCellPositionX[DBF_MAX_CHANNELS];
	double					m_dCellPositionY[DBF_MAX_CHANNELS];
	EMSCOMPLEX				m_acPhaseVector[DBF_MAX_CHANNELS];

	IEMSDataTransmitter*    m_pDataTransmit;
	IEMSDataTransmitter*    m_pDataTransmit2;

	EMSDBFPASSRECORDS2		m_aPassSchedule;

	EMSDBFMAINTENANCE		m_aMaintenance;

	EMSDBFARRAY				m_aDBFplate;

	EMSDBFCALIBRECORD       m_LastCalibRecord;
		
	EMSDBFTOAFOARECORD		m_aTOAFOA;

	bool	m_bOutputOK;
	bool	m_bEigenFlag;

	EMSDBFBUFFERPHASE      m_emsDBFBufferPhase;

	int						m_iObjectID;
	static int              ms_iNextObjectID;
	//snl testing for dbfphase buffer log
	static CEMSTime				m_oDBFBufferPhaseLastWriteTime;
	//covariance file sent time
	static CEMSTime				m_oDBFCovarFileLastWriteTime;
	static BOOL					m_bIsCovarFileSendTime;
	static	std::wstring		m_wsSPIP;
	static	std::wstring		m_wsSPIP2;
	bool _IsTimeToCopyBufferPhaseFile( const EMSTIME& oCurrentTime );
	void _IsTimeToCopyCovarFile( const EMSTIME& oCurrentTime );
	

	EMSCOMPLEX*		m_acDBFBeamVectors; //[MAX_BEAMS*DBF_NUM_ELEMENTS] 
	EMSCOMPLEX*		m_acDBFCarrierVectors;//[MAX_BEAMS*DBF_NUM_ELEMENTS]
	float*			m_fPrevPhaseBias;
	int*			m_iBeamIDs;
	int*			m_iPredictedSATIDs;
	float*			m_fProbability;
	int*			m_iPrevPassSchedSATIDs;

	//for debug
	//CTimeElapsed	m_timeElapsed;
	//snl commented
	//CEMSDBFDataMgr			m_oDBFpass;

	// Process flag establishes input/output and beamformer process	
	WORD			m_ProcessFlag;
	int*			m_iOutputBuffer;
	ULONG			m_ulOutputLength;


	const char*		m_FileNames[MAX_TEST_FILES];

#ifdef _LOGPHASECORR_

	static void LogPhaseCorrection ( INT64, std::string, ULONG, double, ULONG, EMSCOMPLEX &param1 );
	private:
		static FILE *m_pLogPhaseCorrection;		
		static CEMSCriticalSection		m_csFileHandler;

#endif		
		
//private: // constants

};


#endif // INC_EMSDBF



