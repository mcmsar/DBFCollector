/********************************************************************
*	Module:			emsDBF.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
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

	0.0	2006/07/09		rcr		start

********************************************************************/

#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include <io.h>

#include "sigproc.h"
#include "emsclock.h"
#include "emsconst.h"
#include "emsvectr.h"

#include "emsDBF.h"
#include "TrackDBFSatellites.h"

//snl
//#include "emsDBFDataMgr.h"
#include "emsDBFtypes.h"
#include "convutility.h"


int CDigitalBeamFormer::ms_iNextObjectID = 1;
std::wstring		CDigitalBeamFormer::m_wsSPIP;


const char  c_szCalibFile[] = "C:\\EMSDBF_Calib_";

const double	TIMETO_SEND_COVARIANCE_FILE = (1.0/60.0);	//1 mins

#include <sstream>


CEMSTime CDigitalBeamFormer::m_oDBFBufferPhaseLastWriteTime = 0;
CEMSTime CDigitalBeamFormer::m_oDBFCovarFileLastWriteTime = 0;
BOOL CDigitalBeamFormer::m_bIsCovarFileSendTime = FALSE;
CDigitalBeamFormer::CDigitalBeamFormer(CEMSQueue<DBFTrackingData >&  dbfBeamVect) : m_ulChannels(0), m_ulSamplesPerChannel(0), m_ulSatellites(0), m_lpOutputFile( nullptr ),m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asPhaseVector( NULL ), m_asDBFVector( NULL ), 
	m_afRawInputSamples( NULL ), m_afPowerSpectrum(nullptr), m_acMatrix(nullptr), m_qrefDBFBeamVectors( dbfBeamVect )
//CDigitalBeamFormer::CDigitalBeamFormer(CEMSQueue<DBFTrackingData >&  dbfBeamVect) : m_ulChannels(0), m_ulSamplesPerChannel(0), m_ulSatellites(0), m_lpOutputFile( nullptr ),m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asPhaseVector( NULL ), m_asDBFVector( NULL ), 
//	m_afRawInputSamples( NULL ),m_afPowerSpectrum(nullptr),m_acFFTdata1(nullptr), m_acMatrix(nullptr), m_acMatrixT( nullptr), m_qrefDBFBeamVectors( dbfBeamVect )
	//snl added nullptr
{
	m_lpTraceFile = NULL;
	m_pDataTransmit = NULL;
	m_ulLastStartPPS = 0;
	m_ulRawBuffSize = 0;

	m_timeActual.intTime = 0L;

	memset( &m_LastCalibRecord, 0, sizeof( m_LastCalibRecord ) );

	m_iObjectID = GetNextObjID();

	m_lpCalibFile = NULL;

	m_bOutputOK = true;

	//snl
	m_oDBFBufferPhaseLastWriteTime =  m_oDBFCovarFileLastWriteTime = 0;
	//m_bIsCovarFileSendTime = FALSE;
//	m_oDBFpass.Initialize(1);
}

CDigitalBeamFormer::CDigitalBeamFormer( const CDigitalBeamFormer& x ) : m_ulChannels( x.m_ulChannels ),
							m_ulSamplesPerChannel( x.m_ulSamplesPerChannel ),
							m_ulSatellites(x.m_ulSatellites), m_lpOutputFile( NULL),m_lpTraceFile(NULL), m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asPhaseVector( NULL ), m_asDBFVector( NULL ), m_afRawInputSamples( NULL ),m_qrefDBFBeamVectors(x.m_qrefDBFBeamVectors)
{
	m_iObjectID = GetNextObjID();
}

CDigitalBeamFormer::~CDigitalBeamFormer( void )
{
	m_ulChannels = 0;
	m_ulSatellites = 0;
	m_ulSamplesPerChannel = 0;

		
	if (m_lpTraceFile)
	{
		fclose( m_lpTraceFile );
		m_lpTraceFile = 0;
	}
	if (m_lpOutputFile)
	{
		fclose( m_lpOutputFile );
		m_lpOutputFile = 0;
	}

	if( m_lpCalibFile )
	{
		fclose( m_lpCalibFile );
		m_lpCalibFile = NULL;
	}

	if (m_asRawTimeSeries)
	{
		delete [] m_asRawTimeSeries;
		m_asRawTimeSeries = NULL;
	}

	if (m_asPhaseVector)
	{
		delete [] m_asPhaseVector;
		m_asPhaseVector = NULL;
	}

	if (m_asDBFVector)
	{
		delete [] m_asDBFVector;
		m_asDBFVector = NULL;
	}
	
	if (m_afRawInputSamples)
	{
		delete [] m_afRawInputSamples;
		m_afRawInputSamples = NULL;
	}

	if (m_afPowerSpectrum)
	{
		delete [] m_afPowerSpectrum;
		m_afPowerSpectrum = NULL;
	}

	//for(int i = 0; i < DBF_MAX_SATELLITES; ++i)
	//{
	//	if (m_acFFTdata[i])
	//	{
	//		delete [] m_acFFTdata[i] ;
	//		m_acFFTdata[i] = NULL;
	//	}
	//	if (m_nBeam[i])
	//	{
	//		delete [] m_nBeam[i];
	//		m_nBeam[i] = NULL;
	//	}
	//}

	//if (m_acFFTdata)
	//{
	//	delete [] m_acFFTdata;
	//	m_acFFTdata = NULL;
	//}

	if (m_nBeam)
	{
		delete [] m_nBeam;
		m_nBeam = NULL;
	}
	
	//delete []m_acFFTdata;

	//if (m_acFFTdata1)
	//{
	//	delete [] m_acFFTdata1;
	//	m_acFFTdata1 = NULL;
	//}

	// Remove temporary buffer memory
	if (m_acMatrix)
	{
		delete [] m_acMatrix;
		m_acMatrix = NULL;
	}
	//if (m_acMatrixT)
	//{
	//	delete [] m_acMatrixT;
	//	m_acMatrixT = NULL;
	//}
	if (m_acTemp1)
	{
		delete [] m_acTemp1;
		m_acTemp1 = NULL;
	}
	if (m_acTemp2)
	{
		delete [] m_acTemp2;
		m_acTemp2 = NULL;
	}
	if (m_acTemp3)
	{
		delete [] m_acTemp3;
		m_acTemp3 = NULL;
	}
	if (m_afTemp1)
	{
		delete [] m_afTemp1;
		m_afTemp1 = NULL;
	}
	if (m_afTemp2)
	{
		delete [] m_afTemp2;
		m_afTemp2 = NULL;
	}

	if( m_afChan0 )
	{
		delete [] m_afChan0;
		m_afChan0 = NULL;
	}

	if( m_pDataTransmit )
	{
		m_pDataTransmit->Disconnect();
		m_pDataTransmit->Release();
		m_pDataTransmit = NULL;
	}

	//snl

}

//---------------------------------------------------------------------------

EMS_RESULT
CDigitalBeamFormer::SetRawData( const unsigned char* abytes, int iSize )
{
	EMS_RESULT hr = EMS_BAD_PARAM;


	if( iSize == 128000008 )
	{
		INT64* pTM = (INT64*)&(abytes[iSize - 9]);
		m_timeActual.intTime = (*pTM);
	}

	if( m_asRawTimeSeries && abytes )
	{
		if( (iSize - 8) <=  (DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long)) )
		{
			memcpy(m_asRawTimeSeries, abytes, iSize - 8 );// make it a const.

			hr = EMS_OK;

			m_ulRawBuffSize = iSize - 8;
		}
	}
	else
	{
		m_ulRawBuffSize = 0;
	}

	return hr;
}

//---------------------------------------------------------------------------
EMS_RESULT
CDigitalBeamFormer::Initialize( const TCHAR *cDir )
{
	EMS_RESULT hr = EMS_OK;//EMS_BAD_PARAM;

	lstrcpy( m_cFilePath, cDir );

	m_dElapsedTime = 0.0;
	m_dAverageTime = 0.0;
	m_nCounter = 0;

	
	m_ulSamplesPerChannel = DBF_SAMPLE_SIZE;
	m_ulChannels   = DBF_MAX_CHANNELS;
	m_ulSatellites = DBF_MAX_SATELLITES;

	// One second pulse shape function

	m_afPulseShape = new float[ PULSE_SHAPE_SIZE ];

	for ( int i = 0; i < PULSE_SHAPE_SIZE; i++ )
	{

		float t = (float) i / (float) PULSE_SHAPE_SIZE; 
		m_afPulseShape[i] = t * exp( t ) / exp ( 1.0 );
	}

	
	m_asRawTimeSeries = new unsigned long[ DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS ];
	m_asPhaseVector   = new short[ DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * 2 ];
	m_asDBFVector     = new short[ DBF_SAMPLE_SIZE * DBF_MAX_SATELLITES * 2 ];

	m_acCovariance    = new EMSCOMPLEX[ COVARIANCE_SIZE ];     // Covariance matrix
	m_acDBFBeamVectors = new EMSCOMPLEX[ DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES ];

	memset( m_asRawTimeSeries, 0, DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long) );
	memset( m_asPhaseVector, 1.0, DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * 2 * sizeof(short));
	memset( m_asDBFVector, 0, DBF_SAMPLE_SIZE * DBF_MAX_SATELLITES * 2 * sizeof(short));
	
	memset( m_acCovariance, 0, COVARIANCE_SIZE * sizeof(EMSCOMPLEX));
	memset( m_acDBFBeamVectors, 0, DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * sizeof(EMSCOMPLEX));

	m_afRawInputSamples = new float[DBF_LOG20_SIZE];
	m_afPowerSpectrum	= new float[DBF_LOG19_SIZE + 1];
	//m_acFFTdata			= new EMSCOMPLEX*[DBF_MAX_SATELLITES];
	m_nBeam				= new short*[DBF_MAX_SATELLITES];

	m_iBeamIDs				= new int[DBF_MAX_SATELLITES];
	m_iPredictedSATIDs		= new int[DBF_MAX_SATELLITES];
	m_dProbability			= new DOUBLE[DBF_MAX_SATELLITES];
	m_iPrevPassSchedSATIDs	= new int[DBF_MAX_SATELLITES];

	for(int i = 0; i < DBF_MAX_SATELLITES; ++i)
	{
		//m_acFFTdata[i]		= new EMSCOMPLEX[DBF_LOG19_SIZE];
		m_nBeam[i]			= new short[DBF_OUTPUT_SIZE];
		//memset( m_acFFTdata[i], 0, sizeof(EMSCOMPLEX) * DBF_LOG19_SIZE );
		memset( m_nBeam[i], 0, sizeof(short) * DBF_OUTPUT_SIZE );
	}
	//m_acFFTdata1			= new EMSCOMPLEX[DBF_LOG19_SIZE];
	
	memset( m_afRawInputSamples, 0, DBF_SAMPLE_SIZE*sizeof(float));
	memset( m_afPowerSpectrum, 0, (DBF_LOG19_SIZE + 1)*sizeof(float));
	//memset( m_acFFTdata1, 0, DBF_LOG19_SIZE*sizeof(EMSCOMPLEX));

	m_afTemp1	= new float[DBF_LOG20_SIZE];
	m_afTemp2	= new float[DBF_LOG20_SIZE];
	m_acTemp1	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acTemp2	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acTemp3	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acMatrix	= new EMSCOMPLEX[DBF_NUM_ELEMENTS*DBF_LOG19_SIZE];
	//m_acMatrixT	= new EMSCOMPLEX[DBF_NUM_ELEMENTS*DBF_LOG19_SIZE];

	m_afChan0   = new float[DBF_SAMPLE_SIZE];

	memset( m_afTemp1, 0, DBF_LOG20_SIZE*sizeof(float));
	memset( m_acTemp1, 0, (DBF_LOG19_SIZE+1)*sizeof(EMSCOMPLEX));
	memset( m_afTemp2, 0, DBF_LOG20_SIZE*sizeof(float));
	memset( m_acTemp2, 0, (DBF_LOG19_SIZE+1)*sizeof(EMSCOMPLEX));
	memset( m_acTemp3, 0, (DBF_LOG20_SIZE)*sizeof(EMSCOMPLEX));
	memset( m_acMatrix, 0, (DBF_NUM_ELEMENTS*DBF_LOG19_SIZE)*sizeof(EMSCOMPLEX));
	//memset( m_acMatrixT, 0, (DBF_NUM_ELEMENTS*DBF_LOG19_SIZE)*sizeof(EMSCOMPLEX));
	memset( m_afChan0, 0, DBF_SAMPLE_SIZE*sizeof(float));

	memset( &m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORDS));
	memset( &m_aMaintenance, 0, sizeof(EMSDBFMAINTENANCE));
	//memset( &m_aDBFplate, 0, sizeof(EMSDBFARRAY));

	if ( (m_ulSamplesPerChannel>0) && (m_ulChannels>0) && (m_ulSatellites>0) 
		&& (m_asRawTimeSeries) && (m_asPhaseVector) && (m_asDBFVector)
		//&& (m_afRawInputSamples) && (m_afPowerSpectrum) && (m_acFFTdata) && (m_acFFTdata1) )
		&& (m_afRawInputSamples) && (m_afPowerSpectrum) )
	{
		hr = EMS_OK;
	}

	m_timeStart  = CEMSSystemClock::GetTime();
	m_timeFinish = CEMSSystemClock::GetTime();

	TCHAR cTraceFileName[256];
	TCHAR cTempName[256];

	memset(cTraceFileName, 0, sizeof( cTraceFileName ) );
//	lstrcpy( m_cFilePath, cDir );

//	lstrcpy( cTraceFileName, cDir );
			
	//_stprintf( cTempName, TEXT( "DBFtrace-%I64d.csv" ), m_timeStart );
	_stprintf( cTraceFileName, TEXT( "C:\\DBF-Calibration\\DBFtrace_%02d.csv" ), m_iObjectID );
				
//	lstrcat( cTraceFileName, cTempName ); 
				
	m_lpTraceFile  = fopen( cTraceFileName, "wt");
	m_lpOutputFile = NULL;

	
		
	//memset( afRawInputSamples, 0, DBF_SAMPLE_SIZE*sizeof(float));
	memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
	memset( m_afTemp2, 0, DBF_SAMPLE_SIZE*sizeof(float));
		
	
	return hr;
}

//---------------------------------------------------------------------------

void 
CDigitalBeamFormer::Reset( )
{
	if (m_lpTraceFile)
	{
		fclose( m_lpTraceFile );
		m_lpTraceFile = 0;
	}
	if (m_lpOutputFile)
	{
		fclose( m_lpOutputFile );
		m_lpOutputFile = 0;
	}

	if( m_pDataTransmit )
	{
		m_pDataTransmit->Disconnect();
		m_pDataTransmit->Release();
		m_pDataTransmit = NULL;
	}
}


//---------------------------------------------------------------------------

EMS_RESULT 
CDigitalBeamFormer::BufferStatistics( const unsigned long *m_asRawTimeSeries )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( (m_asRawTimeSeries) && (m_afPowerSpectrum) )
	{
		memset( m_afTemp1, 0, m_ulSamplesPerChannel*sizeof(float));
		memset( m_afRawInputSamples, 0, m_ulSamplesPerChannel*sizeof(float));

		ULONG ichunk = 0;
		ULONG iSample = 0;

		// Outer loop divides data block into chunks

		for ( ichunk = 0, iSample = 0; ichunk < m_ulChannels*m_ulSamplesPerChannel; ichunk += m_ulChannels )
		{

			// Convert unsigned integer to float
			emssbIntToFloat( &m_asRawTimeSeries[ichunk], m_afRawInputSamples, m_ulChannels, 32, 0x0800);
			m_afTemp1[iSample++] = emssMean( m_afRawInputSamples, m_ulChannels );

		}

		m_dStdDevADC = _EMSsMeanStdDev( &m_afTemp1[0], m_ulSamplesPerChannel, &m_dMeanADC);

		_EMSsbNormalize(m_afTemp1, m_afRawInputSamples, m_ulSamplesPerChannel, m_dMeanADC, m_dStdDevADC);

		m_dMaxPower = _EMSsMaxExt( &m_afRawInputSamples[0], m_ulSamplesPerChannel, &m_ulStartPPS );

		m_dMinPower = _EMSsMinExt( &m_afRawInputSamples[0], m_ulSamplesPerChannel, &m_ulStopPPS );



		hr = EMS_OK;

	}
	return hr;
}

float
CDigitalBeamFormer::_EMSsMean(const float *vec, ULONG len)
{
	float fMean = 0.0;
	for( ULONG i = 0; i < len; i++ )
	{
		fMean += vec[i];
	}

	fMean = fMean/(float)len;

	return fMean;
}


double
CDigitalBeamFormer::_EMSsMeanStdDev(const float *vec, ULONG len, double* pfMean )
{
	double fSum = 0.00;
	double fMean = 0.00; 
	double fStdDev = 0.00;

    ULONG i;

    for(i = 0; i < len; ++i)
    {
        fSum += vec[i];
    }

    fMean = fSum/len;
	*pfMean = fMean;

    for(i = 0; i < len; ++i)
        fStdDev += pow(vec[i] - fMean, 2);

    return sqrt(fStdDev / len);
}

float
CDigitalBeamFormer::_EMSsMaxExt(const float  *vec, int len, ULONG* index)
{
	float fMaxVal = -1.0;
	for( ULONG i = 0; i < len; i++ )
	{
		if( fMaxVal < vec[i] )
		{
			fMaxVal = vec[i];
			*index = i;
		}
	}
	return fMaxVal;
}

float
CDigitalBeamFormer::_EMSsMinExt(const float  *vec, int len, ULONG* index)
{
	float fMinVal = vec[0];
	for( ULONG i = 0; i < len; i++ )
	{
		if( fMinVal > vec[i] )
		{
			fMinVal = vec[i];
			*index = i;
		}
	}
	return fMinVal;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDigitalBeamFormer::RemoveTimePulse( float *afRawTimeSeries )
{

	EMS_RESULT hr = EMS_OK;

	if( m_ulStartPPS > 0 && m_ulStopPPS < m_ulSamplesPerChannel - PULSE_SHAPE_SIZE )
	{

		for ( int i = 0; i < PULSE_SHAPE_SIZE; i++ )
		{
			afRawTimeSeries[ i + m_ulStartPPS - 2 ] *= m_afPulseShape[ i ];
			afRawTimeSeries[ i + m_ulStopPPS - 2  ] *= m_afPulseShape[ i ];

		}

	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}
//---------------------------------------------------------------------------

HRESULT 
CDigitalBeamFormer::_InitDT()
{
	EMS_RESULT hr =  E_FAIL;
	if(!m_pDataTransmit)
	{
		hr = CoCreateInstance( CLSID_DataXmitter, NULL, CLSCTX_ALL,
							   IID_IEMSDataTransmitter, (void**) &m_pDataTransmit );
		//std::wstring cwszConnectInfo = std::wstring(L"<Connection><ip_address>")  + m_wsSPIP + ::wstring(L"</ip_address><port_id>9070</port_id></Connection>");

		if( EMS_OK != hr || m_pDataTransmit == NULL)
		{
			//printf("\n Failed to load Data Transmitter");
		}
		else if( EMS_OK != m_pDataTransmit->Connect( m_wsSPIP.c_str() ) )
		{
			m_pDataTransmit->Release();
			m_pDataTransmit = NULL;
			//printf("\n Data Transmitter failed to connect");
		}
		else
		{
			//printf("\n Connected");
		}
	}
	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDigitalBeamFormer::DBFprocessorPP(EMSTIME tm)
{
	// TBD
	
	EMSTIME timeStart, timeFinish;

	timeStart.intTime  = 0;
	timeFinish.intTime = 0;

	INT64   i64ElapsedTime = 0;

	EMS_RESULT hr = EMS_OK;

	timeStart = CEMSSystemClock::GetTime();

	try
	{
		if( m_ulSatellites > 0 )
			//hr = DBFprocessor1(m_asRawTimeSeries);

		_OutputWaveExProcess1(  m_timeActual, 1 );
	}
	catch( ... )
	{
		//printf("Unknown exception occurred (%d).\n", m_nCounter);
	}
  
	timeFinish = CEMSSystemClock::GetTime();

	i64ElapsedTime = timeFinish.intTime - timeStart.intTime;


	m_nCounter++;
	m_dElapsedTime += ((double) i64ElapsedTime) * 1e-9; 
	m_dAverageTime = m_dElapsedTime / (double) m_nCounter;

	m_timeFinish = CEMSSystemClock::GetTime();
	i64ElapsedTime = m_timeFinish.intTime - m_timeStart.intTime;
	double dElapsedTime = ((double) i64ElapsedTime) * 1e-9;


/*	printf( "\n 1, %d, AT(sec) = %f, PT = %f, AveT = %f\n",
		m_nCounter, dElapsedTime, m_dElapsedTime, m_dAverageTime );
*/
	if ( m_lpTraceFile )
	{
		fprintf( m_lpTraceFile, "1, %d, %I64d, %f,%f,%f, %f,%f,%f,%ld,%ld, %ld\n",
			m_nCounter, tm.intTime, dElapsedTime, m_dElapsedTime, m_dAverageTime,
			m_dMeanADC, m_dStdDevADC, m_dMaxPower, m_ulStartPPS, m_ulStopPPS - m_ulStartPPS,
			m_ulMaxPowerIndex);

	}
	return hr;
}

EMSTIME 
CDigitalBeamFormer::_SetActualTime( EMSTIME tm )
{
	return m_timeActual;
	EMSTIMEFIELDS tmFlds;
	CEMSTime oTM(tm);

	oTM.GetTime(&tmFlds);

	CEMSTime oActualTime;
	oActualTime.SetTime(tmFlds.nYear, tmFlds.nMonth, tmFlds.nDay, tmFlds.nHour, tmFlds.nMinute, tmFlds.nSecond, 0 );

	m_ulMarkerBitRate = 500000;  //TBD

	if( m_ulLastStartPPS > 0 && !m_oLastPPS.IsZero() )
	{
		double dSecondDiff = m_oLastPPS.SecondsDifferent(tm);
		if( dSecondDiff < 0.0 )
		{
			dSecondDiff *= -1.0;
		}
		dSecondDiff *= 2;
		dSecondDiff = ((ULONG)dSecondDiff) / 2.0;

	}

	double dTimeFraction = (double) (m_ulStartPPS) / (double) m_ulMarkerBitRate;

	m_oLastPPS = tm;
	m_ulLastStartPPS = m_ulStartPPS;

	// To find start time of buffer subtract time fraction
	oActualTime.AddSeconds(-dTimeFraction);

	double dSecDiff = oTM.SecondsDifferent(oActualTime);

	if( dSecDiff < -1.001 )
	{
		oActualTime.AddSeconds(1.0);
	}
	else if( dSecDiff > 1.001 )
	{
		oActualTime.AddSeconds(-1.0);
	}

	// 0.5 second offset correction
	oActualTime.AddSeconds(-0.5);

	return oActualTime;
}



int
CDigitalBeamFormer::_GetMostCommonIndex( ULONG* arr, int iCount)
{
	int iRet = -1;
	ULONG arrCount[32];
	memset( arrCount, 0, sizeof( arrCount ) );

	for( int i = 0; i < 32; i++ )
	{
		for( int j = i + 1; j < 32; j++)
		{
			if( arr[i] == arr[j] )
				arrCount[i]++;
		}
	}

	ULONG lTest = 0;
	for( int k = 0; k < 32; k++ )
	{
		if( lTest < arrCount[k] )
		{
			lTest = arrCount[k];
			iRet = k;
		}
	}

	return iRet;
}


void
CDigitalBeamFormer::_EMScbPowerSpectr(const EMSCOMPLEX *src, float *spectr,ULONG length)
{
	if( src && spectr )
	{
		for( ULONG i = 0; i < length; i++ )
		{
			spectr[i] = sqrt( src[i].re * src[i].re + src[i].im * src[i].im );
		}
	}
}

void
CDigitalBeamFormer::_EMSsbNormalize( const float *src, float *dst, ULONG n, const float valuesub, const float valuediv )
{
	if( src && dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i] = ( src[i] -  valuesub ) / valuediv;
		}
	}
}


void
CDigitalBeamFormer::_EMScbMpy1( const EMSCOMPLEX val, EMSCOMPLEX *dst, ULONG n )
{
	if( dst )
	{
		EMSCOMPLEX cTemp;
		
		for( ULONG i = 0; i < n; i++ )
		{
			cTemp.re = dst[i].re * val.re - dst[i].im * val.im;
			cTemp.im = dst[i].re * val.im + dst[i].im * val.re;
			dst[i].re = cTemp.re;
			dst[i].im = cTemp.im;
		}
	}
}

void
CDigitalBeamFormer::_EMScbAdd2( const EMSCOMPLEX *src, EMSCOMPLEX *dst, ULONG n )
{
	if( src && dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i].re += src[i].re;
			dst[i].im += src[i].im;
		}
	}
}

void
CDigitalBeamFormer::_EMSsbMpy1( const float val, float *dst, ULONG n )
{
	if( dst )
	{
		for( ULONG i = 0; i < n; i++ )
		{
			dst[i] *= val;
		}
	}
}

//---------------------------------------------------------------------------


void 
CDigitalBeamFormer::_IsTimeToCopyCovarFile( const EMSTIME& oCurrentTime)
{
		//check if covariance file send time is up

		CEMSTime oNext(m_oDBFCovarFileLastWriteTime);
		oNext.AddHours(TIMETO_SEND_COVARIANCE_FILE);
		
		EMSTIME tmNext = oNext;
		EMSTIME tmCurrent = oCurrentTime;

		if( tmCurrent.intTime >= tmNext.intTime )
		{
			m_bIsCovarFileSendTime = TRUE;
			m_oDBFCovarFileLastWriteTime = oCurrentTime;
		}
		else
			m_bIsCovarFileSendTime = FALSE;
	
}


bool 
CDigitalBeamFormer::_IsTimeToCopyBufferPhaseFile( const EMSTIME& oCurrentTime)
{
	bool bRet = false;
	if( 0 == m_oDBFBufferPhaseLastWriteTime.GetTimeNano() )
	{
		m_oDBFBufferPhaseLastWriteTime =  m_oDBFCovarFileLastWriteTime = CEMSSystemClock::GetTime();
		bRet = true;
	}
	else
	{
		// check one hour.
		CEMSTime oNext(m_oDBFBufferPhaseLastWriteTime);
		oNext.AddHours(1.0);
		
		EMSTIME tmNext = oNext;
		EMSTIME tmCurrent = oCurrentTime;

		if( tmCurrent.intTime >= tmNext.intTime )
		{
			bRet = true;
		}
		_IsTimeToCopyCovarFile( oCurrentTime );
	}
	return bRet;
}



//---------------------------------------------------------------------------

EMS_RESULT
CDigitalBeamFormer::DBFprocessorEP(EMSTIME tm)
{
	EMSTIME timeStart, timeFinish;

	timeStart.intTime  = tm.intTime;
	timeFinish.intTime = 0;

	INT64   i64ElapsedTime = 0;

	EMS_RESULT hr = EMS_OK;

	
	try
	{
		hr = DBFprocessorEP1(tm, m_asRawTimeSeries);	
	}
	catch( ... )
	{
		//printf("Unknown exception occurred (%d).\n", m_nCounter);
	}
	if( m_bIsCovarFileSendTime )
	{
		m_bIsCovarFileSendTime = FALSE;

		EMSDBFCOVARIANCE aCOV;
		memset( &aCOV, 0, sizeof( EMSDBFCOVARIANCE ) );
		aCOV.timestamp     = tm;
		aCOV.ulSampleSize  = m_ulSamplesPerChannel;
		aCOV.wChannelCount = m_ulChannels;
		aCOV.wPlateID      = 1;

		for( ULONG i = 0; i < m_ulSatellites; i++ )
		{
			aCOV.fPlateAzimuth[i] = m_aPassSchedule.rec[i].fPlateAzimuth;
			aCOV.fPlateElevation[i] = m_aPassSchedule.rec[i].fPlateElevation;
			aCOV.ulSatelliteID[i] = m_aPassSchedule.rec[i].ulSatID;
		}

		memcpy( aCOV.acCovariance, m_acCovariance, sizeof( EMSCOMPLEX ) * COVARIANCE_SIZE );

		CEMSTime oTime( tm );
		EMSTIMEFIELDS tmFields;
		memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
		oTime.GetTime( &tmFields );
		ULONG ulMinutes = tmFields.nMinute + 60*tmFields.nHour;

		char szFileName[256];
		_stprintf( szFileName, TEXT( "c:\\hgt\\DBFCovarianceFiles\\DBFCovariance-%04d.bin" ), ulMinutes );

		FILE* lpCovFile = fopen(szFileName,"wb");
		if( lpCovFile )
		{
			fwrite( &aCOV, 1, sizeof( EMSDBFCOVARIANCE ), lpCovFile );
			fclose( lpCovFile );
		}

	}
	
	m_nCounter++;
	timeFinish = CEMSSystemClock::GetTime();
	i64ElapsedTime = timeFinish.intTime - timeStart.intTime;

	m_dElapsedTime += ((double) i64ElapsedTime) * 1e-9; 
	m_dAverageTime = m_dElapsedTime / (double) m_nCounter;

	if ( m_lpTraceFile )
	{
		wstring sTime =  CEMSConversionUtil::ConvertToDateTimeString2W( tm );
		fprintf( m_lpTraceFile, "1, %d, %s, %f,%f, %f,%f,%f,%ld,%ld, %ld\n",
			m_nCounter, sTime, m_dElapsedTime, m_dAverageTime,
			m_dMeanADC, m_dStdDevADC, m_dMaxPower, m_ulStartPPS, m_ulStopPPS - m_ulStartPPS,
			m_ulMaxPowerIndex);

		for (int i = 0; i < m_ulChannels; i++)
		{
			fprintf(m_lpTraceFile,", %02d, %f, %f", i, m_aMaintenance.dMean[i], m_aMaintenance.dStdDev[i] );
		}
		fprintf(m_lpTraceFile,"\n");
	}
	return hr;
}

//---------------------------------------------------------------------------

// Computes correlation matrix

EMS_RESULT 
CDigitalBeamFormer::DBFprocessorEP1( EMSTIME tm, const unsigned long *clpRawTimeSeries )
{

	EMS_RESULT hr = EMS_BAD_PARAM;
	static int	nScaleFactor = 16;      // Scale factor for integer dot product

	ULONG ulBand50  = 100000; // 50 kHz bandwidth (0.5 Hz bin size)
	ULONG ulBand100 = ulBand50 *2; // 100 kHz bandwidth

	if ( clpRawTimeSeries )
	{
		ULONG i, icell, jsample, index, ichunk;
		double dPower  = 0.0;
		double dMean = 0.0;
		double dStdDev = 0.0;

		CEMSTime timeStart  =  CEMSSystemClock::GetTime();
		CEMSTime timeStart1 =  CEMSSystemClock::GetTime();
		CEMSTime timeEnd    =  CEMSSystemClock::GetTime();

		try
		{
			hr = BufferStatistics( m_asRawTimeSeries );

			memset( m_afMean, 0, DBF_MAX_CHANNELS*sizeof(float));
			memset( m_afStdDev, 0, DBF_MAX_CHANNELS*sizeof(float));
			
			// FFT size is a power of 2 and larger than the number of input samples
			memset( m_afTemp1, 0, DBF_LOG20_SIZE*sizeof(float));
			memset( m_afTemp2, 0, DBF_LOG20_SIZE*sizeof(float));

			memset( m_afRawInputSamples, 0, m_ulSamplesPerChannel*sizeof(float));
			memset( m_acCovariance, 0, COVARIANCE_SIZE*sizeof(EMSCOMPLEX));
			memset( m_acTemp1, 0, (DBF_LOG19_SIZE+1)*sizeof(EMSCOMPLEX));
			memset( m_acTemp2, 0, (DBF_LOG19_SIZE+1)*sizeof(EMSCOMPLEX));

			memset( m_acMatrix,  0, (DBF_NUM_ELEMENTS*DBF_LOG19_SIZE)*sizeof(EMSCOMPLEX));
			//memset( m_acMatrixT, 0, (DBF_NUM_ELEMENTS*DBF_LOG19_SIZE)*sizeof(EMSCOMPLEX));
			memset( m_acDBFBeamVectors, 0, (DBF_NUM_ELEMENTS*DBF_MAX_SATELLITES)*sizeof(EMSCOMPLEX)); 
		}
		catch( ... )
		{
			return hr;
		}

		hr = ComputeChannelData( );
		timeEnd =  CEMSSystemClock::GetTime();
		printf( "ProcessEP1 RAW -> Time elapsed 0 : %f seconds, id: %i \n" ,timeStart.SecondsDifferent( timeEnd) , GetCurrentThreadId() );

		timeStart1 =  CEMSSystemClock::GetTime();
		hr = ComputeCovariance( ulBand100 );
		timeEnd =  CEMSSystemClock::GetTime();
		printf( "ProcessEP1 COV -> Time elapsed 1 : %f seconds, id: %i \n" ,timeStart1.SecondsDifferent( timeEnd) , GetCurrentThreadId() );

		timeStart1 =  CEMSSystemClock::GetTime();
		hr = ComputeDBFBeamVectors( m_ulSatellites, m_acCovariance);

		hr = ApplyDBFBeamVectors( m_ulSatellites );

		timeEnd =  CEMSSystemClock::GetTime();
		printf( "ProcessEP1 DBF -> Time elapsed 2 : %f seconds, id: %i \n" ,timeStart1.SecondsDifferent( timeEnd) , GetCurrentThreadId() );
		
		_BuildDBFSatsTrackingInfo( m_acDBFBeamVectors );


		_OutputWaveEx( tm, m_ulSatellites );

		//timeEnd =  CEMSSystemClock::GetTime();
		//printf( "ProcessEP1 -> Time elapsed 3:%f seconds, id: %i \n" ,timeStart.SecondsDifferent( timeEnd) , GetCurrentThreadId() );
	}

	return hr;
}


//---------------------------------------------------------------------------



EMS_RESULT
CDigitalBeamFormer::DBFprocessorRAW(EMSTIME tm)
{
	EMS_RESULT hr = EMS_OK;
	try
	{
		int size = m_ulRawBuffSize; 
		_OutpuRawDigitalDataFile( (unsigned char*)&m_asRawTimeSeries[0], m_timeActual, size );	
	}
	catch( ... )
	{
		//printf("Unknown exception occurred (%d).\n", m_nCounter);
	}	
	
	return hr;
}



//---------------------------------------------------------------------------
EMS_RESULT 
CDigitalBeamFormer::SetPassSchedule( EMSDBFPASSRECORDS* pPassRecords, EMSTIME tm )
{

	EMS_RESULT hr = EMS_OK;
	if( pPassRecords )
	{
		// read pass schedule information for time 'tm'

		memcpy(&m_aPassSchedule, pPassRecords, sizeof(EMSDBFPASSRECORDS) );

		m_ulSatellites = 0;
		for( int i = 0; i < DBF_MAX_SATELLITES; i++ )
		{
			if( m_aPassSchedule.rec[i].ulSatID > 0 ) m_ulSatellites++;
		}

		m_aMaintenance.timestamp = tm;
		m_aMaintenance.ulSampleSize = m_ulSamplesPerChannel;
		//m_aMaintenance.wCellID
		m_aMaintenance.wChannelCount = m_ulChannels;
		m_aMaintenance.wPlateID = 1;
	}
	else
	{
		memset(&m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORDS) );
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT 
CDigitalBeamFormer::GetADCBuffer( const char *szFilename1, const char *szFilename2, const char *szFilename3, const char *szFilename4  )
{
	EMS_RESULT hr = EMS_BAD_PARAM;
	{
		FILE *lpFile = 0;
		int nRetcode1 = 0;
		int nRetcode2 = 0;
		int nRetcode3 = 0;
		int nRetcode4 = 0;
		ULONG ulIndex = 0;
		ULONG ulIncrement = m_ulChannels * m_ulSamplesPerChannel / 4;
		

		lpFile = fopen( szFilename1, "rb" );
		if ( lpFile )
		{
			nRetcode1 = fread( &m_asRawTimeSeries[ulIndex], 2, ulIncrement, lpFile );
			fclose( lpFile );
		}
		ulIndex += ulIncrement;

		lpFile = fopen( szFilename2, "rb" );
		if ( lpFile )
		{
			nRetcode2 = fread( &m_asRawTimeSeries[ulIndex], 2, ulIncrement, lpFile );
			fclose( lpFile );
		}
		ulIndex += ulIncrement;

		lpFile = fopen( szFilename3, "rb" );
		if ( lpFile  )
		{
			nRetcode3 = fread( &m_asRawTimeSeries[ulIndex], 2, ulIncrement, lpFile );
			fclose( lpFile );
		}
		ulIndex += ulIncrement;

		lpFile = fopen( szFilename4, "rb" );
		if ( lpFile )
		{
			nRetcode4 = fread( &m_asRawTimeSeries[ulIndex], 2, ulIncrement, lpFile );
			fclose( lpFile );
		}

		if ( (nRetcode1 + nRetcode2 + nRetcode3 + nRetcode4) == 4 * ulIncrement )
			hr = EMS_OK;
	}
	return hr;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void
CDigitalBeamFormer::_OutputWave( EMSTIME tm, const ULONG culIndex  )
{
	EMS_RESULT hr = EMS_OK;
	CEMSWaveEx oWaveOut;

	if( !m_bOutputOK )
		return;

//	char fName[256];
//	FILE *OneSecFile = 0;
	DWORD dwBytes = 0;
	BYTE* abyData = 0;

	ULONG ulLutID = m_aPassSchedule.rec[culIndex].ulLutID;
	ULONG ulSatID = m_aPassSchedule.rec[culIndex].ulSatID;
	WORD  wPlateID = m_aPassSchedule.rec[culIndex].wPlateID;
	double dSatAzimuth = (double) m_aPassSchedule.rec[culIndex].fAzimuth;
	double dSatElevation = (double) m_aPassSchedule.rec[culIndex].fElevation;
	ULONG ulBytes = sizeof(short) * DBF_SAMPLE_SIZE;
//	ULONG ulBytes = sizeof(short) * DBF_SAMPLE_SIZE/2;

	ULONG ulIndex = culIndex * ulBytes / sizeof(short);
//	oWaveOut.Write( (unsigned char*)&m_asDBFVector[ulIndex], ulBytes  );
//	oWaveOut.Write( (unsigned char*)m_acFFTdata, DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )  );
//	oWaveOut.Write( (unsigned char*)m_acFFTdata, DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )/2  ); // RR reduced buffer size to 250kHz
//	oWaveOut.Write( (unsigned char*)&m_acFFTdata[40000], DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )/2  ); // RR reduced buffer size to 250kHz & added 50kHz offset

	oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
	oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
//	oWaveOut.GetFormatChunkRef().SetSampleRate( 1000000 );
	oWaveOut.GetFormatChunkRef().SetSampleRate( DBF_SAMPLE_RATE );
	oWaveOut.GetFormatChunkRef().SetBitsPerSample( 16 );


	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
	oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( wPlateID );

	oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );

	// Set additional properties indicating whether the signal requires
	// phase demod or down-conversion.
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC * 10.00 );

	// Wave has not yet been downconverted:
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );//EMS_DC_YES
	//oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_YES );
	
	// Set flag indicating whether the marker bit was found for this measurement.
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( m_ulStartPPS );

	// RR added azimuth and elevation of satellite
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dSatAzimuth );
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dSatElevation );


	if ( ulSatID < 200 )
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
	else
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );

	dwBytes = oWaveOut.Serialize( abyData );
	//printf("\nData Transmitter to send the buffer\n");
	if( dwBytes > 0 )
	{
		int iSent = 0;

		hr = _InitDT();
		if( m_pDataTransmit )
		{
			hr = m_pDataTransmit->Send( dwBytes, abyData, &iSent);
		}
		if(FAILED(hr) )
		{
			//printf("Data Transmitter failed to send the buffer");
			//pDataTransmit->Disconnect();
		}
		/*else
			printf("Data Transmitter successfully sent the buffer");*/

		/*			unsigned long ulBytesWritten = fwrite(abyData, 1, dwBytes, OneSecFile);
		if( ulBytesWritten < (dwBytes) )
			printf("\n  Error writing a wave file... ");

		flushall();
		fclose(OneSecFile);*/
		delete[] abyData;
		abyData = 0;
	}

	return;
}

void
CDigitalBeamFormer::_OutputWaveExProcess1( EMSTIME tm, ULONG culNumSats  )
{
	CEMSTime timeStart =  CEMSSystemClock::GetTime();
	EMS_RESULT hr = EMS_OK;
	/*if( culNumSats > DBF_MAX_SATELLITES )
		culNumSats = DBF_MAX_SATELLITES;
	if( !m_bOutputOK )
		return;*/

//	char fName[256];
//	FILE *OneSecFile = 0;
	int *beamID = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;

	for( int iSat = 0; iSat < culNumSats; iSat++ )
	{
		CEMSWaveEx oWaveOut;

		DWORD dwBytes = 0;
		BYTE* abyData = 0;

		ULONG ulLutID = m_aPassSchedule.rec[iSat].ulLutID;
		ULONG ulSatID = m_aPassSchedule.rec[iSat].ulSatID;
		WORD  wPlateID = m_aPassSchedule.rec[iSat].wPlateID;
		double dSatAzimuth = (double) m_aPassSchedule.rec[iSat].fAzimuth;
		double dSatElevation = (double) m_aPassSchedule.rec[iSat].fElevation;
		ULONG ulBytes = sizeof(short) * DBF_SAMPLE_SIZE;
	//	ULONG ulBytes = sizeof(short) * DBF_SAMPLE_SIZE/2;

		//ULONG ulIndex = culIndex * ulBytes / sizeof(short);
	//	oWaveOut.Write( (unsigned char*)&m_asDBFVector[ulIndex], ulBytes  );
	//	oWaveOut.Write( (unsigned char*)m_acFFTdata, DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )  );
	//	oWaveOut.Write( (unsigned char*)m_acFFTdata, DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )/2  ); // RR reduced buffer size to 250kHz
	//	oWaveOut.Write( (unsigned char*)&m_acFFTdata[iSat][40000], DBF_LOG19_SIZE * sizeof( EMSCOMPLEX )/2  ); // RR reduced buffer size to 250kHz & added 50kHz offset
		//oWaveOut.Write( (unsigned char*)&m_acFFTdata[iSat][40000], 200000 * sizeof( EMSCOMPLEX )  ); // RR reduced buffer size to 250kHz & added 50kHz offset

		oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
		oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
//		oWaveOut.GetFormatChunkRef().SetSampleRate( 1000000 );
		oWaveOut.GetFormatChunkRef().SetSampleRate( DBF_SAMPLE_RATE );
		oWaveOut.GetFormatChunkRef().SetBitsPerSample( 16 );


		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
		oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
		//oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( wPlateID );
		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( beamID[iSat] );

		//oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( (WORD)iSat ); // RR temporary to test satellite sensitivity to nulling

		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );

		// Set additional properties indicating whether the signal requires
		// phase demod or down-conversion.
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC );

		// Wave has not yet been downconverted:
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );//EMS_DC_YES
		//oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_YES );
	
		// Set flag indicating whether the marker bit was found for this measurement.
	//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( m_ulStartPPS );

		// RR added azimuth and elevation of satellite
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dSatAzimuth );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dSatElevation );


		// RR change for LEO calibration testing
		if ( ulSatID < 200 )
			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
		else
			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );

		dwBytes = oWaveOut.Serialize( abyData );
		//printf("\nData Transmitter to send the buffer\n");
		if( dwBytes > 0 )
		{
			int iSent = 0;

			hr = _InitDT();
			if( m_pDataTransmit )
			{
				hr = m_pDataTransmit->Send( dwBytes, abyData, &iSent);
			}
			if(FAILED(hr) )
			{
				//printf("Data Transmitter failed to send the buffer");
				//pDataTransmit->Disconnect();
			}
			/*else
				printf("Data Transmitter successfully sent the buffer");*/

			/*			unsigned long ulBytesWritten = fwrite(abyData, 1, dwBytes, OneSecFile);
			if( ulBytesWritten < (dwBytes) )
				printf("\n  Error writing a wave file... ");

			flushall();
			fclose(OneSecFile);*/
			delete[] abyData;
			abyData = 0;
		}
	}
	
	CEMSTime timeEnd =  CEMSSystemClock::GetTime();
	//printf( "_OutputWaveEx -> Time elapsed : %f seconds for %i sats, id: %i\n" ,timeStart.SecondsDifferent( timeEnd) , culNumSats, GetCurrentThreadId()  );

	return;
}

void
CDigitalBeamFormer::_OutputWaveEx( EMSTIME tm, ULONG culNumSats  )
{
	EMSTIME timeStart =  CEMSSystemClock::GetTime();
	EMS_RESULT hr = EMS_OK;
	if( culNumSats > DBF_MAX_SATELLITES )
		culNumSats = DBF_MAX_SATELLITES;
	if( !m_bOutputOK )
		return;
	INT testSatID = 460;

//	char fName[256];
//	FILE *OneSecFile = 0;
	int *beamID = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
	int *predSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
	double *probability = m_qrefDBFBeamVectors.ReadFirst( ).probability;

	for( int iSat = 0; iSat < culNumSats; iSat++ )
	{
		CEMSWaveEx oWaveOut;

		DWORD dwBytes = 0;
		BYTE* abyData = 0;

		ULONG ulLutID  = m_aPassSchedule.rec[iSat].ulLutID;
		ULONG ulSatID  = m_aPassSchedule.rec[iSat].ulSatID;
		WORD  wPlateID = m_aPassSchedule.rec[iSat].wPlateID;
		double dSatAzimuth = (double) m_aPassSchedule.rec[iSat].fAzimuth;
		double dSatElevation = (double) m_aPassSchedule.rec[iSat].fElevation;
		//if( ulSatID >= 200 && dSatElevation < MEO_MIN_ELEVATION )	//snl added to check > 20 if pass sched has no elev constraints
		//	continue;
		ULONG ulBytes = sizeof(short) * DBF_OUTPUT_SIZE;

		short* sTemp = new short[DBF_OUTPUT_SIZE];
		memcpy( &sTemp[0], &m_nBeam[iSat][0], DBF_OUTPUT_SIZE* sizeof(short) );

		//oWaveOut.Write( (unsigned char*)&m_nBeam[iSat][0], DBF_OUTPUT_SIZE * sizeof(short) );
		oWaveOut.Write( (unsigned char*)&sTemp, DBF_OUTPUT_SIZE * sizeof(short) );

		oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
		oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
		oWaveOut.GetFormatChunkRef().SetSampleRate( DBF_SAMPLE_RATE );
		oWaveOut.GetFormatChunkRef().SetBitsPerSample( 16 );


		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
		oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
		WORD wAntID = 0;
		wAntID = wPlateID*100 +  (WORD) iSat;
		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( wAntID );

		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );

		// Set additional properties indicating whether the signal requires
		// phase demod or down-conversion.SetMeanADC
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC );

		// Wave has not yet been downconverted:
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );//EMS_DC_YES
	
		// Set flag indicating whether the marker bit was found for this measurement.
	//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );
	//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( m_ulStartPPS );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( 0 );
		
		//if( predSatIDs )
		//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( predSatIDs[ iSat ] );
		if( probability )
			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanCarrierFreq( probability[ iSat ] );

		// RR added azimuth and elevation of satellite
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dSatAzimuth );
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dSatElevation );

		// RR change for LEO calibration testing
		if ( ulSatID < 200 )
			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
		else
			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );

			//EMSWAVEEXSUBBAND subBandStruct;


			//CEMSWaveExtSubBandDetails subBand(subBandStruct);
			//subBand.SetEndFrequency(2000000);
			//subBand.SetStartFrequency(50000);

			//oWaveOut.GetExtendedInfoRef().GetSubBandDetails().AddSubBand();
		//oWaveOut.GetExtendedInfoRef().GetSubBandDetails1().SetStartFrequency(50000);
	//	oWaveOut.GetExtendedInfoRef().GetSubBandDetails1().SetEndFrequency(2000000);



		dwBytes = oWaveOut.Serialize( abyData );
		//printf("\nData Transmitter to send the buffer\n");
		if( dwBytes > 0 )
		{
			int iSent = 0;

			hr = _InitDT();
			if( m_pDataTransmit )
			{
				hr = m_pDataTransmit->Send( dwBytes, abyData, &iSent);
				//for debug
				std::stringstream str;
				str <<" Time:" << CEMSConversionUtil::ConvertToDateTimeHiResString2A(tm) << " satid:" << ulSatID << " lutid:" <<ulLutID
					<<" index: " << iSat << " TotSats: " << culNumSats << std::endl;
				//OutputDebugString( str.str().c_str() );
			}
			if(FAILED(hr) )
			{
				printf("Data Transmitter failed to send the buffer");
				//for debug
				std::stringstream str;
				str <<" Time:" << CEMSConversionUtil::ConvertToDateTimeHiResString2A(CEMSSystemClock::GetTime() ) << " tm : " << 
					CEMSConversionUtil::ConvertToDateTimeHiResString2A(tm) << " Error, failed to send " <<
					" satid:" << ulSatID << " lutid:" <<ulLutID
					<<" index: " << iSat << " TotSats: " << culNumSats << std::endl;
				//OutputDebugString( str.str().c_str() );
				//pDataTransmit->Disconnect();
			}
			else
			{
				//printf("Data Transmitter successfully sent the buffer");
				//for debug
				std::stringstream str;
				str <<" Time:"  << CEMSConversionUtil::ConvertToDateTimeHiResString2A(CEMSSystemClock::GetTime()) << " tm: " << 
					CEMSConversionUtil::ConvertToDateTimeHiResString2A(tm) << " Sent satid:" << ulSatID << " lutid:" <<ulLutID
					<<" index: " << iSat << " TotSats: " << culNumSats << std::endl;
				//OutputDebugString( str.str().c_str() );
			}

			/*			unsigned long ulBytesWritten = fwrite(abyData, 1, dwBytes, OneSecFile);
			if( ulBytesWritten < (dwBytes) )
				printf("\n  Error writing a wave file... ");

			flushall();
			fclose(OneSecFile);*/
			delete[] abyData;
			abyData = 0;
		}
	}
	

	return;
}
//---------------------------------------------------------------------------

void
CDigitalBeamFormer::_OutputWaveFile( unsigned char* aData, EMSTIME tm, ULONG culSize )
{
	EMS_RESULT hr = EMS_OK;
	CEMSWaveEx oWaveOut;


	char szFileName[256];
	FILE *pWaveFile = 0;
	DWORD dwBytes = 0;
	BYTE* abyData = 0;

	ULONG ulLutID = m_aPassSchedule.rec[0].ulLutID;
	ULONG ulSatID = m_aPassSchedule.rec[0].ulSatID;
	ULONG ulBytes = sizeof(long) * DBF_SAMPLE_SIZE/2;

	oWaveOut.Write( (unsigned char*)aData, culSize * sizeof(unsigned char) );

	oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
	oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
//	oWaveOut.GetFormatChunkRef().SetSampleRate( 1000000 );
	oWaveOut.GetFormatChunkRef().SetSampleRate( DBF_SAMPLE_RATE );
	oWaveOut.GetFormatChunkRef().SetBitsPerSample( 32 );


	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
	oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( (WORD) ulLutID );
	oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );

	// Set additional properties indicating whether the signal requires
	// phase demod or down-conversion.
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC );

	// Wave has not yet been downconverted:
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );
	
	// Set flag indicating whether the marker bit was found for this measurement.
	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );

	if ( ulSatID < 200 )
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
	else
		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );

	dwBytes = oWaveOut.Serialize( abyData );
	if( dwBytes > 0 )
	{
		memset(szFileName, 0, sizeof(szFileName) );
//		sprintf(szFileName,"D:\\WaveOutput\\DBF_%I64d.wav", tm.intTime);
		sprintf(szFileName,"C:\\HGT\\DBFPassData\\WaveOutput\\DBF_%03d_%I64d.wav", ulSatID, tm.intTime);
//		sprintf(szFileName,"D:\\WaveOutput\\DBF_%I64d.bin", tm.intTime);
//		sprintf(szFileName,"C:\\HGT\\DBFPassData\\WaveOutput\\DBF_%I64d.wav", tm.intTime);--> right
//		sprintf(szFileName,"D:\\DBFPassData\\WaveOutput\\DBF_%I64d.bin", tm.intTime);

		pWaveFile = fopen(szFileName,"w+b");
		if( pWaveFile != NULL )
		{
			fwrite(abyData, 1, dwBytes, pWaveFile);
//			fwrite(aData, 1, culSize, pWaveFile);
			////snl for offline data
			//if( m_aPassSchedule.rec[0].wProcessID == 5 )
			//{
			//	for( int i = 0; i < 4; i++ )
			//	{
			//		fwrite(&m_aPassSchedule.rec[i], 1, sizeof(EMSDBFPASSRECORD), pWaveFile);
			//	}

			//}
			////end snl
			fclose(pWaveFile);
		}

		delete[] abyData;
		abyData = 0;
	}

	return;
}

//snl for testing..tbr
#include <complex>
unsigned long long  GetFreeDiskSpaceInGBs ()
{
	ULARGE_INTEGER FreeBytesAvailable = { 0 };
    ULARGE_INTEGER TotalNumberOfBytes={ 0 };
    ULARGE_INTEGER TotalNumberOfFreeBytes={ 0 };

    BOOL ok = GetDiskFreeSpaceEx(
        "C:\\",
        &FreeBytesAvailable,
        &TotalNumberOfBytes,
        &TotalNumberOfFreeBytes
        );

    if (ok)
    {
        unsigned long long freeAvail = FreeBytesAvailable.QuadPart;
        unsigned long long total = TotalNumberOfBytes.QuadPart;
        unsigned long long totalfree = TotalNumberOfFreeBytes.QuadPart;

        return (freeAvail /std::pow(1024.0,3));	//, total / 1024 / 1024, totalfree / 1024 / 1024);
	}
}

void
CDigitalBeamFormer::_OutpuRawDigitalDataFile( unsigned char* aData, EMSTIME tm, ULONG culSize )
{
	EMS_RESULT hr = EMS_OK;

	char szFileName[256];
	FILE *pRawDataFile = 0;
	BYTE* abyData = 0;
	ULONGLONG freeGigs = GetFreeDiskSpaceInGBs( );
	if( culSize > 0 && freeGigs > 1.5 )
	{
		CEMSTime oTime(tm);
		EMSTIMEFIELDS tmFields;
		memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
		oTime.GetTime( &tmFields );
		float fSeconds = (float) (tmFields.nSecond)  + (float) (tmFields.lNanosecond)*1e-9;

		memset(szFileName, 0, sizeof(szFileName) );
		sprintf(szFileName,"C:\\HGT\\DBFPassData\\WaveOutput\\DBFRawData_%04.1f_%lu_%lu_%lu_%lu.bin", fSeconds, m_aPassSchedule.rec[0].ulSatID
			,m_aPassSchedule.rec[1].ulSatID,m_aPassSchedule.rec[2].ulSatID, m_aPassSchedule.rec[3].ulSatID);
		pRawDataFile  = fopen(szFileName,"w+b");
		if( pRawDataFile  != NULL )
		{
			ULONG ulLength = culSize;
			fwrite(&ulLength, 1, sizeof(ULONG), pRawDataFile );
			fwrite(aData, 1, culSize, pRawDataFile );
			INT sizeT = DBF_MAX_SATELLITES;
			fwrite(&m_aPassSchedule, 1, sizeof(EMSDBFPASSRECORDS), pRawDataFile );
			fclose(pRawDataFile );
		}

		delete[] abyData;
		abyData = 0;
	}

	return;
}

//---------------------------------------------------------------------------

EMS_RESULT 
CDigitalBeamFormer::GetPassSchedule( EMSTIME tm )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	// read pass schedule information for time 'tm'

//	m_aPassSchedule = m_oDBFpass.SetPassSchedule( tm );

	m_ulSatellites = 0;

	for( int i = 0; i < DBF_MAX_SATELLITES; i++ )
	{
		if( m_aPassSchedule.rec[i].ulSatID > 0 ) m_ulSatellites++;
	}

	m_aMaintenance.timestamp = tm;
	m_aMaintenance.ulSampleSize = m_ulSamplesPerChannel;
	//m_aMaintenance.wCellID
	m_aMaintenance.wChannelCount = m_ulChannels;
	m_aMaintenance.wPlateID = 1;

	return hr;
}

//---------------------------------------------------------------------------


void
CDigitalBeamFormer::_SetActualTimeNew()
{
	m_timeActual;

	m_asRawTimeSeries;
	float fScaleFactor        = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion

	ULONG jsample, index;

	for ( jsample = 0, index = 0; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
	{
		m_afChan0[jsample] = (float) ( (m_asRawTimeSeries[index] & 0x000FFFFF) * fScaleFactorInverse) ;
	}

	float fTimeDiff = 0.0;
	float fMaxTimeDiff = 0.0;
	ULONG ulTimeMarker = 0;

	for ( jsample = 0; jsample < (m_ulSamplesPerChannel - 2);  jsample++ )
	{
		fTimeDiff = m_afChan0[jsample + 2] - m_afChan0[jsample];
		if( fTimeDiff > fMaxTimeDiff )
		{
			fMaxTimeDiff = fTimeDiff;
			ulTimeMarker = jsample + 1;
		}
	}

	//long	lNanosecond = (long)(((float)ulTimeMarker/1000000.00) * 1e9);
	long	lNanosecond = (long)(((float)ulTimeMarker/DBF_SAMPLE_RATE) * 1e9);
	EMSTIMEFIELDS tmFlds;
	EMSTIMEFIELDS tmFlds_New;
	CEMSTime oTM(m_timeActual);
	//oTM.AddSeconds(-0.5);

	oTM.GetTime(&tmFlds);

	CEMSTime oActualTime;
	oActualTime.SetTime(tmFlds.nYear, tmFlds.nMonth, tmFlds.nDay, tmFlds.nHour, tmFlds.nMinute, tmFlds.nSecond, 0 );
	oActualTime.AddNanoseconds( -1 * lNanosecond );
	m_timeActual = oActualTime;

	CEMSTime oTM_New(m_timeActual);
	//oTM.AddSeconds(-0.5);

	oTM_New.GetTime(&tmFlds_New);

	int xyz = sizeof( long );
}

void
CDigitalBeamFormer::ProcessAll()
{
	if( m_ulSatellites == 0 || m_aPassSchedule.rec[0].ulSatID == 0 )
		return;

	//find time taken to process
	CEMSTime timeStart =  CEMSSystemClock::GetTime();

	_SetActualTimeNew();

	m_ProcessFlag = m_aPassSchedule.rec[0].wProcessID;

	// Temporary fix
	m_ProcessFlag = PROCESS_DEFAULT;

	switch( m_ProcessFlag && 0x00FF ) 
	{
		case 0:
			break;
		case 1:
			{
				// Eigenvector Method
				DBFprocessorEP(m_aMaintenance.timestamp);
			}
			break;
		case 2:
			{
				// Predicted Phase Pointing metod
				DBFprocessorPP(m_aMaintenance.timestamp);
			}
			break;
		case 4:
			{
				//DBFprocessorCP(m_aMaintenance.timestamp);
			}
			break;
		case 8:
			{
				// Raw data output
				DBFprocessorRAW( m_aMaintenance.timestamp );
			}
			break;
		default:
				break;
	}
	CEMSTime timeEnd =  CEMSSystemClock::GetTime();

	printf( "ProcessAll -> Time elapsed:%f seconds, id: %i \n" ,timeStart.SecondsDifferent( timeEnd) , GetCurrentThreadId() );
}


//---------------------------------------------------------------------------

void
CDigitalBeamFormer::_OutputCalibData( EMSTIME tm )
{
	if( m_aPassSchedule.rec[0].ulSatID != 0 )
	{
		if( !m_lpCalibFile )
		{
			_OpenCalibFile();
		}

		if( m_lpCalibFile )
		{
			EMSDBFCALIBRECORD emsDBFCalib;

			memset( &emsDBFCalib, 0, sizeof(EMSDBFCALIBRECORD) );

			emsDBFCalib.Pass = m_aPassSchedule.rec[0];

			memcpy( emsDBFCalib.fCalibPhaseReal, m_LastCalibRecord.fCalibPhaseReal, sizeof(m_LastCalibRecord.fCalibPhaseReal) );
			memcpy( emsDBFCalib.fCalibPhaseImag, m_LastCalibRecord.fCalibPhaseImag, sizeof(m_LastCalibRecord.fCalibPhaseImag) );
			// Write binary Calib record
			fwrite( &emsDBFCalib, 1, sizeof( EMSDBFCALIBRECORD ), m_lpCalibFile );
		}
		else
		{
			// error.
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void
CDigitalBeamFormer::_OpenCalibFile()
{
	if( !m_lpCalibFile )
	{
		char szFileName[256];

		memset(szFileName, 0, sizeof(szFileName) );

		sprintf(szFileName, "%s_%d.bin", c_szCalibFile, m_iObjectID ); 
		m_lpCalibFile = fopen( szFileName, "ab" );
	}
}

//snl
#ifdef _LOGPHASECORR_


CEMSCriticalSection		CDigitalBeamFormer::m_csFileHandler;
void CDigitalBeamFormer::LogPhaseCorrection (  INT64 timeNum, std::string timeStr , ULONG channel , double dPower, 
	ULONG ulMaxPowerIndex, EMSCOMPLEX &param1  )
{
	try
	{
		m_csFileHandler.Enter();
		if( !m_pLogPhaseCorrection )
		{
			m_pLogPhaseCorrection = fopen( "c:\\DBFLogs\\phasecorrn.csv" , "at" );
			//fprintf(m_pLogPhaseCorrection,"timestamp, timestring, channel, power, maxpowerindex,phasecorr real,phasecorr imag");
			fprintf(m_pLogPhaseCorrection,"timestamp, channel, power, maxpowerindex,phasecorr real,phasecorr imag");

			fprintf(m_pLogPhaseCorrection,"\n");

		}
		if ( m_pLogPhaseCorrection )
		{
			//fprintf( m_pLogPhaseCorrection, " %I64d,%s,%lu,%f,%lu,",timeNum, timeStr.c_str(), channel,dPower, ulMaxPowerIndex );
			fprintf( m_pLogPhaseCorrection, " %I64d,%lu,%f,%lu,",timeNum, channel,dPower, ulMaxPowerIndex );
			fprintf( m_pLogPhaseCorrection, "%f,%f",param1.re,param1.im  );
			fprintf(m_pLogPhaseCorrection,"\n");
			fflush( m_pLogPhaseCorrection );
		}
		m_csFileHandler.Leave();
	}
	catch( ... )
	{
		m_csFileHandler.Leave();

	}
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////

void CDigitalBeamFormer::_EMSGetPhaseOffsets( const unsigned long *clpRawTimeSeries, ULONG ulSatMaxFreq, double *dPeakPhase )
{

	double dMean = 0;
	double dStdDev = 0;
	float fScaleFactor        = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion


	memset( m_afTemp1, 0, DBF_LOG20_SIZE*sizeof(float));
	memset( m_afTemp2, 0, DBF_LOG20_SIZE*sizeof(float));

	// Skip channel 0 (1 PPS signal)
	for ( int ichan = 1; ichan < (int)m_ulChannels; ichan++ )
	{
		// Convert integer to float

		memset( m_afTemp1, 0, DBF_LOG20_SIZE*sizeof(float));
		memset( m_afTemp2, 0, DBF_LOG20_SIZE*sizeof(float));
			
		for ( int jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
		{
			m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
		}

		dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );

		if( dStdDev == 0.00 )
			continue;

		_EMSsbNormalize(m_afTemp1, m_afTemp2, m_ulSamplesPerChannel, dMean, dStdDev);

		emssRealFftNip( m_afTemp2, m_acTemp1, DBF_LOG20, EMS_SPL_FWD );

		// Store only element data (not 1 PPS channel)
		dPeakPhase[ichan-1] = atan2( (double) m_acTemp1[ ulSatMaxFreq ].im, (double) m_acTemp1[ ulSatMaxFreq ].re );
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::DBFCorrectPhaseBias(  EMSCOMPLEX *FFTdata, ULONG length )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBins = (ULONG) (length*0.4);
	ULONG ulStartFreq =  ulBins;
	EMSCOMPLEX cBias;

	_EMScbPowerSpectr( &FFTdata[ulStartFreq], &m_afTemp1[0], ulBins);

	float fMaxPower = 0.0;
	ULONG index = ulStartFreq;
	for( ULONG i = 0; i < ulBins; i++ )
	{
		if ( m_afTemp1[i] > fMaxPower )
		{
			fMaxPower = m_afTemp1[i];
			index = i;
		}
	}
	 cBias.re =  FFTdata[index + ulStartFreq].re / m_afTemp1[index];
	 cBias.im = -FFTdata[index + ulStartFreq].im / m_afTemp1[index];

	 _EMScbMpy1( cBias,  &FFTdata[0], length );

	 FFTdata[index + ulStartFreq].re = 0.0;
	 FFTdata[index + ulStartFreq].im = 0.0;

	return hr;
}

//////////////////////////////////////////////////////////////////////////

//Main Beamforming Function
EMS_RESULT
CDigitalBeamFormer::ComputeDBFBeamVectors( INT nNumBeams, const EMSCOMPLEX *m_acCovariance )
{
	//EMSCOMPLEXD  acCovarianceMatrix[DBF_NUM_ELEMENTS*DBF_NUM_ELEMENTS];	
	float EigenValues[DBF_NUM_ELEMENTS];
	MKL_Complex8 acEigenVectors[DBF_NUM_ELEMENTS*DBF_NUM_ELEMENTS];
	EMSCOMPLEX acNormalizedEigenVectors[DBF_NUM_ELEMENTS*DBF_NUM_ELEMENTS];	

    //memset(acCovarianceMatrix, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));	
	memset(EigenValues, 0, DBF_NUM_ELEMENTS*sizeof(float));	
	memset(acEigenVectors, 0, DBF_NUM_ELEMENTS*DBF_NUM_ELEMENTS*sizeof(MKL_Complex8));	
	memset(acNormalizedEigenVectors, 0, DBF_NUM_ELEMENTS*DBF_NUM_ELEMENTS*sizeof(EMSCOMPLEX));	
	unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
    EMS_RESULT hr = EMS_BAD_PARAM;	
                            
    if ( m_acCovariance )
	{
		hr = PerformEigenDecomposition(m_acCovariance, EigenValues, acEigenVectors);

	}

	if(EMS_OK == hr)
	{
		   hr = PerformEigenVectorNormalization(acEigenVectors, acNormalizedEigenVectors);
	   
		   // Extracting the nNumBeams largest eigenvectors 
		   if (EMS_OK==hr)
		   {
			   EMSCOMPLEX *acLargestEigenVectors  = new EMSCOMPLEX[nNumBeams*NUM_CHANNELS];
			   memset(acLargestEigenVectors,0,nNumBeams*NUM_CHANNELS*sizeof(EMSCOMPLEX));
			  // Extracting the nNumBeams largest eigenvectors
			  for (int  iBeam = 0; iBeam < nNumBeams; iBeam++)
			  {
				  for(int ichan=0; ichan<NUM_CHANNELS; ichan++)
				  {
					   acLargestEigenVectors[iBeam*NUM_CHANNELS+ichan] = acNormalizedEigenVectors[(30-iBeam)*NUM_CHANNELS+ichan];
				  }
			  }			  
		  
			   hr = ComputeNullingVectors(acLargestEigenVectors, nNumBeams, m_acDBFBeamVectors); 	
			   delete [] acLargestEigenVectors;		   
		   }
	 }

  return hr;
}

//////////////////////////////////////////////////////////////////////////////////////
EMS_RESULT
CDigitalBeamFormer::ComputeNullingVectors(const EMSCOMPLEX *acEigenVectors, 
                                  const int nNumBeams, EMSCOMPLEX *acDBFBeamVectors)
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::ApplyDBFBeamVectors( ULONG m_ulSatellites )
{
	EMS_RESULT hr = EMS_FALSE;
	double dMean = 0;
	double dStdDev = 0;
	double dMean0 = 0;
	double dStdDev0 = 0;
	double dMaxValue = 0;
	ULONG ulMaxIndex = 0;
	float fScalefactor = 0;

	if ( m_acDBFBeamVectors && m_acMatrix )
	{
		if ( m_ulSatellites > MAX_BEAMS )
			m_ulSatellites = MAX_BEAMS;

		hr = EMS_OK;
					

		for ( int isat = 0; isat < m_ulSatellites; isat++ )
		{
			memset( m_acTemp1, 0, sizeof(EMSCOMPLEX) * DBF_LOG19_SIZE );
			memset( m_acTemp3, 0, sizeof(EMSCOMPLEX) * DBF_LOG20_SIZE );

			// Note: The stored matrix is a downverted complex time series with same input sample rate
			for ( int ielem = 0; ielem < DBF_NUM_ELEMENTS; ielem++ )
			{
				// The complex time series must remain unchanged to allow multiple satellite outputs
				memcpy( m_acTemp3, &m_acMatrix[ielem*DBF_LOG19_SIZE], DBF_LOG19_SIZE );
				emscbMpy1(m_acDBFBeamVectors[isat*DBF_NUM_ELEMENTS+ielem], m_acTemp3, DBF_LOG19_SIZE );
				emscbAdd2(m_acTemp3, m_acTemp1, DBF_LOG19_SIZE );
			}
		
			// Convert to time series
			memset( m_acTemp3, 0, sizeof(EMSCOMPLEX) * DBF_LOG20_SIZE );
			emscFftNip( &m_acTemp1[0], m_acTemp3, DBF_LOG19, EMS_SPL_FWD );

			// Store the complex conjugate of the original FFT in resevse order
			m_acTemp3[ 0 ].re = 0.0;
			m_acTemp3[ 0 ].im = 0.0;
			m_acTemp3[ DBF_LOG19_SIZE ].re = 0.0;
			m_acTemp3[ DBF_LOG19_SIZE ].im = 0.0;

			for ( ULONG i = 1; i < DBF_LOG19_SIZE; i++ )
			{
				m_acTemp3[ DBF_LOG19_SIZE + i].re =  m_acTemp3[ DBF_LOG19_SIZE - i].re;
				m_acTemp3[ DBF_LOG19_SIZE + i].im = -m_acTemp3[ DBF_LOG19_SIZE - i].im;
			}
			memset( m_acTemp2, 0, sizeof(EMSCOMPLEX) * DBF_LOG20_SIZE );
			emscFftNip( &m_acTemp3[0], m_acTemp2, DBF_LOG20, EMS_SPL_INV );
			
			// Extract the floating point time series
			// Note: The complex components are zero and the sample rate remains unchanged
			for ( ULONG i = 0; i < DBF_OUTPUT_SIZE; i++ )
			{
				m_afTemp1[i] = m_acTemp2[i].re;
				m_afTemp2[i] = m_acTemp2[i].im;
			}

			// Normalize and convert into signed integer
			dStdDev0  = _EMSsMeanStdDev( m_afTemp2, DBF_OUTPUT_SIZE, &dMean0 );
			dStdDev   = _EMSsMeanStdDev( m_afTemp1, DBF_OUTPUT_SIZE, &dMean );

			_EMSsbNormalize(m_afTemp1, m_afTemp2, DBF_OUTPUT_SIZE, dMean, dStdDev);
			dMaxValue = _EMSsMaxExt(m_afTemp2, DBF_OUTPUT_SIZE, &ulMaxIndex);
			float fScalefactor = 32766 / dMaxValue;
			_EMSsbMpy1( fScalefactor, m_afTemp2, DBF_OUTPUT_SIZE );
			emssbFloatToInt(m_afTemp2, &m_nBeam[isat][0], DBF_OUTPUT_SIZE, 16, 0);
			//for ( ULONG i = 0; i < DBF_OUTPUT_SIZE; i++ )
			//{
			//	m_nBeam[isat][i] = (short) &m_afTemp2[i];
			//}

			for ( ULONG i = DBF_OUTPUT_SIZE-10; i < DBF_OUTPUT_SIZE; i++ )
			{
				printf("\n %d, %d, %f", i, m_nBeam[isat][i], m_afTemp2[i]);
			}

		}
	}

    return hr;       
}                           

//////////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT  
CDigitalBeamFormer::PerformEigenDecomposition(const EMSCOMPLEXD *acCovarianceMatrix, 
                              float *EigenValues, MKL_Complex8 *acEigenVectors)
{
	CHGTEigenVectors eigenVect;
	eigenVect.PerformEigenDecomposition( (MKL_Complex8 *)acCovarianceMatrix, EigenValues, acEigenVectors );
	return S_OK;						 
								 
}


EMS_RESULT  
CDigitalBeamFormer::PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors)
{
	double amp;
	double x,y;
	
	memset(acNormalizedEigenVectors, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));
	
	//for (int i =0; i<NUM_CHANNELS; i++)
	//{
	//	for (int j=0;j<NUM_CHANNELS;j++)
	//	{
	//		x=acEigenVectors[i*NUM_CHANNELS+j].real;
	//		y=acEigenVectors[i*NUM_CHANNELS+j].imag;
	//		amp= sqrt(x*x+y*y);
	//		if (amp>0.0)
	//		{
	//			acNormalizedEigenVectors[i*NUM_CHANNELS+j].re =	acEigenVectors[i*NUM_CHANNELS+j].real/amp;
	//		    acNormalizedEigenVectors[i*NUM_CHANNELS+j].im =	acEigenVectors[i*NUM_CHANNELS+j].imag/amp;
	//		}			
	//	}
	//}
    for (int i =0; i<NUM_CHANNELS*NUM_CHANNELS; i++)
	{
		x=acEigenVectors[i].real;
		y=acEigenVectors[i].imag;
		amp= sqrt(x*x+y*y);

		if ( amp > 0.0 )
		{
			acNormalizedEigenVectors[i].re = acEigenVectors[i].real/amp;
			acNormalizedEigenVectors[i].im = acEigenVectors[i].imag/amp;
		}
	}
    return EMS_OK;
	
}

EMS_RESULT
CDigitalBeamFormer::ComputeCovariance( ULONG ulNumSamples )
{
	// Compute sample covariance over the 100 kHz L-Band downlink
	for( ULONG i = 0; i < DBF_NUM_ELEMENTS; i++ )
	{
		emscbConj2( &m_acMatrix[i*DBF_LOG19_SIZE], &m_acTemp1[0], ulNumSamples ); // 100 kHz

		for( ULONG j = i; j < DBF_NUM_ELEMENTS; j++)
		{
			m_acCovariance[i*DBF_NUM_ELEMENTS+j] = emscDotProd(&m_acTemp1[0], &m_acMatrix[j*DBF_LOG19_SIZE], ulNumSamples);
			m_acCovariance[j*DBF_NUM_ELEMENTS+i].re =  m_acCovariance[i*NUM_CHANNELS+j].re;
			m_acCovariance[j*DBF_NUM_ELEMENTS+i].im = -m_acCovariance[i*NUM_CHANNELS+j].im;
		}
	}

	// Normalize the sample covariance matrix
	EMSCOMPLEX cScaleFactor;
	cScaleFactor.re = 1.0/ ((float)(ulNumSamples*(float)ulNumSamples*(float)ulNumSamples));
	cScaleFactor.im = 0.0;
	emscbMpy1(cScaleFactor, m_acCovariance, NUM_CHANNELS*NUM_CHANNELS );

	//emscbMatrixTranspose( m_acMatrix, m_acMatrixT, DBF_LOG19_SIZE, DBF_MAX_CHANNELS );
	//emscbConj1( m_acMatrixT, DBF_MAX_CHANNELS*DBF_LOG19_SIZE  );

	//emscbMatrixMuliply( m_acMatrixT, DBF_MAX_CHANNELS, DBF_LOG19_SIZE, 
	//	m_acMatrix, DBF_LOG19_SIZE, DBF_MAX_CHANNELS, m_acCovariance );

	//EMSCOMPLEX cScaleFactor;
	//cScaleFactor.re = 1.0/ ((float)(DBF_LOG19_SIZE*(float)DBF_LOG19_SIZE*(float)DBF_LOG19_SIZE));
	//cScaleFactor.im = 0.0;
	//emscbMpy1(cScaleFactor, m_acCovariance, DBF_MAX_CHANNELS*DBF_MAX_CHANNELS );

	return EMS_OK;
}

BOOL 
CDigitalBeamFormer::_BuildDBFSatsTrackingInfo( EMSCOMPLEXD* acDBFBeamVectors)
{
	//call tracking function..
		CTrackDBFSatellites objTrackSats;
		//read existing values
		int CurrentSatIds [ MAX_BEAMS ];
		memset( CurrentSatIds, 0, sizeof(int) * MAX_BEAMS );
		for( int i = 0; i < m_ulSatellites; i++ )
		{
			CurrentSatIds[i] = m_aPassSchedule.rec[i].ulSatID;
		}

		//read from q
		EMSCOMPLEXD *prevDBFBeamVectors = m_qrefDBFBeamVectors.ReadFirst( ).dbfBeamVector;
		int *prevSchedulerSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).schedulerSatIds;
		int *prevPredSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
		int *prevBeamIds = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
		double *prevProbability = m_qrefDBFBeamVectors.ReadFirst( ).probability;
		int	prevNumBeams = m_qrefDBFBeamVectors.ReadFirst( ).numBeams;
		//end
		
		// Check if first time
		if( !prevDBFBeamVectors && !prevBeamIds )
		{
			memset(m_iBeamIDs, 0, MAX_BEAMS*sizeof(int) );
			for( int i = 0; i < m_ulSatellites; i++ )
			{
				//first time so set default beam ids
				m_iBeamIDs[i] = i+1;
			}
			DBFTrackingData obj;
			memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
			obj.dbfBeamVector = m_acDBFBeamVectors;
			obj.predBeamIDs = m_iBeamIDs;
			memcpy( m_iPredictedSATIDs, CurrentSatIds, MAX_BEAMS * sizeof(int) );
			obj.predSatIDs = m_iPredictedSATIDs;
			obj.probability = m_dProbability;
			memcpy( m_iPrevPassSchedSATIDs, CurrentSatIds, sizeof(int) * MAX_BEAMS );
			obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
			obj.numBeams = m_ulSatellites;
			m_qrefDBFBeamVectors.InsertAtFirst( obj );
			return true;
		}
		const double Tup = 0.6;
		const double Tlo = 0.45;
		INT nNumBeams = m_ulSatellites;
		int *newBeamIds = new int[ MAX_BEAMS ];
		memset( newBeamIds, 0, sizeof(int) * MAX_BEAMS );
		int *newPredSatIds = new int [ MAX_BEAMS ];
		memset( newPredSatIds, 0, sizeof(int) * MAX_BEAMS );
		objTrackSats.perform_dbf_beam_and_sat_tracking( prevDBFBeamVectors, prevNumBeams, acDBFBeamVectors, nNumBeams,
														prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs, Tup, Tlo,
														newBeamIds, newPredSatIds, m_dProbability );
		//Log
		/*LogDBFTrackingData( prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs,newBeamIds, newPredSatIds, m_dProbability, m_timeActual, m_aPassSchedule 
		,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS  );*/
		//end
		memcpy( m_iBeamIDs, newBeamIds, sizeof(int) * MAX_BEAMS );														
		memcpy( m_iPredictedSATIDs, newPredSatIds, MAX_BEAMS * sizeof(int) );
		DBFTrackingData obj;
		memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
		obj.dbfBeamVector = m_acDBFBeamVectors;
		obj.predBeamIDs = m_iBeamIDs;
		obj.predSatIDs = m_iPredictedSATIDs;
		obj.probability = m_dProbability;
		memcpy( m_iPrevPassSchedSATIDs, &CurrentSatIds, sizeof(int) * MAX_BEAMS );
		obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
		obj.numBeams = nNumBeams;
		//m_qrefDBFBeamVectors.InsertAtFirst( acDBFBeamVectors );
		m_qrefDBFBeamVectors.InsertAtFirst( obj );
		delete []newBeamIds;
		delete []newPredSatIds;
		return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::ComputeChannelData( )
{
	ULONG  i, icell, jsample, index, ichunk;
	ULONG  ulBand50 = 500000; // 50 kHz offset
	double dPower  = 0.0;
	double dMean = 0.0;
	double dStdDev = 0.0;
	
	float fScaleFactor        = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion

	for ( icell = 0; icell < DBF_NUM_ELEMENTS; icell++ )
	{
		// Convert integer to float
		memset( m_afTemp1, 0, DBF_LOG20_SIZE*sizeof(float));
		memset( m_afTemp2, 0, DBF_LOG20_SIZE*sizeof(float));
			
		//Skip first channel, set index = icell + 1
		for ( jsample = 0, index = icell+1; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
		{
			m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
		}

		dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );


		if( dStdDev == 0.00 )
			continue;

		m_aMaintenance.dMean[icell]   = dMean;
		m_aMaintenance.dStdDev[icell] = dStdDev;

		_EMSsbNormalize(m_afTemp1, m_afTemp2, m_ulSamplesPerChannel, dMean, dStdDev);

		emssRealFftNip( m_afTemp2, m_acTemp1, DBF_LOG20, EMS_SPL_FWD );

		// Remove phase bias
		//DBFCorrectPhaseBias( &m_acTemp1[0], DBF_LOG19_SIZE );

		// Downconvert by 50 kHZ assuming downlink is centred at 150 kHz
		DOUBLE dBandWidth = DBF_SAMPLE_RATE / 2;
		DOUBLE dBinSize   = dBandWidth / DBF_LOG20_SIZE;
		ULONG ulOffset50  = (ULONG) (ulBand50 / dBinSize); // 50 kHz offset
		ULONG ulDownConvertSize = 2 * ulOffset50; // 100 kHz bandwidth of satellite downlink signal
		
		// Assume 3*ulOffset50 < DBF_LOG19_SIZE
		memcpy(&m_acTemp2[0], &m_acTemp1[ulOffset50], (ulDownConvertSize) * sizeof(EMSCOMPLEX)); 
			
		// Convert to time series
		emscFftNip( &m_acTemp2[0], m_acTemp1, DBF_LOG19, EMS_SPL_INV );

		// Store downconverted time series for each channel (Note: The sample rate remains unchanged)
		memcpy(&m_acMatrix[icell*DBF_LOG19_SIZE], m_acTemp1, DBF_LOG19_SIZE * sizeof(EMSCOMPLEX));
	}
	return EMS_OK;
}
