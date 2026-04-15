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
#include "emsdbftypes.h"
#include "emsDBFDataMgr.h"

#include "wave/waveformatchunk.h"
#include "wave/waveextchunk.h"
#include "wave/waveex.h"


#define INITGUID
#include <initguid.h>
#include "datatransmitter.h"

// {1E47D91E-DE7F-4b86-98BF-B6306E54E403}
DEFINE_GUID(CLSID_DataXmitter, 
			0x1e47d91e, 0xde7f, 0x4b86, 0x98, 0xbf, 0xb6, 0x30, 0x6e, 0x54, 0xe4, 0x3);


using std::string;
using std::wstring;

#define DBF_MAX_CHANNELS    (64)		// maximum number of input channels (based upon ADC board capabilities)
#define DBF_MAX_SATELLITES  (5)			// maximum number of DBF tracked satellites per face
#define DBF_SAMPLE_SIZE		(500000)	// maximum number of samples per channel per collection interval
#define DBF_FFT_REAL_SIZE	(524288)	// 2^19 maximum Real FFT size
#define DBF_FFT_SIZE_LOG2	(19)	    // log base2 maximum FFT size
#define DBF_FFT_COMPLEX_SIZE (262144)	// 2^18 complex FFT size
#define COVARIANCE_SIZE     (DBF_MAX_CHANNELS * (DBF_MAX_CHANNELS+1) / 2)

#define ADC_OFFSET          (262144)
//#define ADC_OFFSET          (32768)
#define PULSE_SHAPE_SIZE    (100)
#define PULSE_LENGTH_MAX	(3000)      // maximum pulse length in samples ( 3 msec approximately )
#define MAX_SATELLITE_ID  (400)			// maximum sat ID.

//snl test
#include "criticalsection.h"

class CDigitalBeamFormer
{
public:

	~CDigitalBeamFormer( void );
	CDigitalBeamFormer();

	CDigitalBeamFormer( const CDigitalBeamFormer& x ) ;

	EMS_RESULT Initialize( const TCHAR *cDir);

	EMS_RESULT SetRawData( const unsigned char* abytes, int iSize );

	EMSVECTORD Convert2UnitVector( const double dAzimuth, const double dElevation );

	EMS_RESULT BufferStatistics( const unsigned long *clpRawTimeSeries );

	EMS_RESULT RemoveTimePulse( float *afRawTimeSeries);


	EMS_RESULT DBFprocessor1( const unsigned long *clpRawTimeSeries );
	EMS_RESULT DBFprocessor22( const unsigned long *clpRawTimeSeries );
	EMS_RESULT DBFprocessor1Ex( EMSTIME tm );

	EMS_RESULT DBFprocessor2( const unsigned long *clpRawTimeSeries, int iSatIndex );
	EMS_RESULT DBFprocessor2Ex( EMSTIME tm );

	EMS_RESULT DBFprocessor3( const unsigned long *clpRawTimeSeries );
	EMS_RESULT DBFprocessor3Ex( EMSTIME tm );

	EMS_RESULT DBFprocessor4( EMSTIME tm );

	EMS_RESULT GetADCBuffer( const char *szFilename1, const char *szFilename2, const char *szFilename3, const char *szFilename4 );
	
	EMS_RESULT GetPhaseBuffer( );

	EMS_RESULT GetPassSchedule( EMSTIME tm );
	EMS_RESULT SetPassSchedule( EMSDBFPASSRECORDS* pPassRecords, EMSTIME tm );

	WORD       GetProcess( ){ return ( m_aPassSchedule.rec[0].wProcessID ); };

	void ProcessAll();

	void Reset( );

	EMS_RESULT TestDBFprocessor( int nProcess );

	static int GetNextObjID() {return ms_iNextObjectID++;}

protected:
	void _InitDT();
	void _OutputWave( EMSTIME tm, const ULONG culIndex );
	void _OutputWaveFile( unsigned char* aData, EMSTIME tm, ULONG culSize );
	EMSTIME _SetActualTime( EMSTIME tm );

	void _OutputCalibData( EMSTIME tm );
	void _OpenCalibFile();

	int _GetMostCommonIndex( ULONG* arr, int iCount);

	void _EMScbPowerSpectr(const EMSCOMPLEX *src, float *spectr,ULONG length);
	void _EMSsbNormalize( const float *src, float *dst, ULONG n, const float valuesub, const float valuediv );
	void _EMScbMpy1( const EMSCOMPLEX val, EMSCOMPLEX *dst, ULONG n );
	void _EMScbAdd2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, ULONG n );
	void _EMSsbMpy1( const float val, float *dst, ULONG n );

	float _EMSsMean(const float *vec, ULONG len);
	double _EMSsMeanStdDev(const float *vec, ULONG len, double* pfMean );
	float _EMSsMaxExt(const float  *vec, int len, ULONG* index);
	float _EMSsMinExt(const float  *vec, int len, ULONG* index);

//private: // methods

private: // data
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
	EMSCOMPLEX*				m_acFFTdata;
	EMSCOMPLEX*				m_acFFTdata1;

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

	float*					m_afCovariance;     // Covariance matrix
	float*					m_afPulseShape;    // 1 PPS pulse shape

	EMSCOMPLEX*				m_acTemp1;
	EMSCOMPLEX*				m_acTemp2;
	float*					m_afTemp1;
	float*					m_afTemp2;

	CEMSTime                m_oLastPPS;

	EMSTIME					m_timeStart;
	EMSTIME					m_timeFinish;
	double					m_dElapsedTime;
	double					m_dAverageTime;
	int						m_nCounter;

	ULONG					m_ulRawBuffSize;

	float m_afMean[DBF_MAX_CHANNELS];
	float m_afStdDev[DBF_MAX_CHANNELS];

	IEMSDataTransmitter*    m_pDataTransmit;

	EMSDBFPASSRECORDS		m_aPassSchedule;

	EMSDBFMAINTENANCE		m_aMaintenance;

	EMSDBFARRAY				m_aDBFplate;

	EMSDBFCALIBRECORD       m_LastCalibRecord;

	bool  m_bOutputOK;

	int						m_iObjectID;
	static int              ms_iNextObjectID;

	CEMSDBFDataMgr			m_oDBFpass;
//snl
#ifdef _LOGPHASECORR_

	static void LogPhaseCorrection ( INT64, std::string, ULONG, double, ULONG, EMSCOMPLEX &param1 );
	private:
		static FILE *m_pLogPhaseCorrection;		
		static CEMSCriticalSection		m_csFileHandler;

#endif		
		
//private: // constants

};


#endif // INC_EMSDBF



