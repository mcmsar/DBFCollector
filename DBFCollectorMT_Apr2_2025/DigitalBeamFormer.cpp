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

#include "DBFCollectorConfig.h"
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
#include "ToaFoaProcessor.h"

//snl
#include "emsDBFDataMgr.h"
#include "emsDBFtypes2.h"
#include "convutility.h"
#include <vector>

#include "CBeaconMessage.h"
#include "CBeaconID.h"
#include "HexUtilis.h"

int CDigitalBeamFormer::ms_iNextObjectID = 1;
std::wstring		CDigitalBeamFormer::m_wsSPIP;
std::wstring		CDigitalBeamFormer::m_wsSPIP2;



const double	TIMETO_SEND_COVARIANCE_FILE = (1.0/60.0);	//1 mins

#include <sstream>


CEMSTime CDigitalBeamFormer::m_oDBFBufferPhaseLastWriteTime = 0;
CEMSTime CDigitalBeamFormer::m_oDBFCovarFileLastWriteTime = 0;
BOOL CDigitalBeamFormer::m_bIsCovarFileSendTime = FALSE;
CDigitalBeamFormer::CDigitalBeamFormer(CEMSQueue<DBFTrackingData >&  dbfBeamVect) : m_ulChannels(0), m_ulSamplesPerChannel(0), m_ulSatellites(0),
	m_lpOutputFile( nullptr ),m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asDBFVector( NULL ), 
	m_afRawInputSamples( NULL ), m_afPowerSpectrum(nullptr), m_acMatrix(nullptr), m_qrefDBFBeamVectors( dbfBeamVect )
//CDigitalBeamFormer::CDigitalBeamFormer(CEMSQueue<DBFTrackingData >&  dbfBeamVect) : m_ulChannels(0), m_ulSamplesPerChannel(0), m_ulSatellites(0),
//	m_lpOutputFile( nullptr ),m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asPhaseVector( NULL ), m_asDBFVector( NULL ), 
//	m_afRawInputSamples( NULL ), m_afPowerSpectrum(nullptr), m_acMatrix(nullptr), m_qrefDBFBeamVectors( dbfBeamVect )
//CDigitalBeamFormer::CDigitalBeamFormer(CEMSQueue<DBFTrackingData >&  dbfBeamVect) : m_ulChannels(0), m_ulSamplesPerChannel(0), m_ulSatellites(0), m_lpOutputFile( nullptr ),m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ), m_asPhaseVector( NULL ), m_asDBFVector( NULL ), 
//	m_afRawInputSamples( NULL ),m_afPowerSpectrum(nullptr),m_acFFTdata1(nullptr), m_acMatrix(nullptr), m_acMatrixT( nullptr), m_qrefDBFBeamVectors( dbfBeamVect )
	//snl added nullptr
{
	m_lpTraceFile    = NULL;
	m_pDataTransmit  = NULL;
	m_pDataTransmit2 = NULL;
	m_ulLastStartPPS = 0;
	m_ulRawBuffSize  = 0;
	m_fFrequencyOffset = static_cast<float>(DBF_FREQ_OFFSET);

	m_timeActual.intTime = 0L;

	memset( &m_LastCalibRecord, 0, sizeof( m_LastCalibRecord ) );

	m_iObjectID  = GetNextObjID();
	m_lpCalibFile = NULL;
	m_bOutputOK  = true;

	// Pointer members not covered by the initializer list.
	// All are freed in the destructor, so they must be NULL until allocated.
	m_nBeam                = NULL;
	m_acTemp1              = NULL;
	m_acTemp2              = NULL;
	m_acTemp3              = NULL;
	m_acFFTBeacon          = NULL;
	m_afTemp1              = NULL;
	m_afTemp2              = NULL;
	m_afChan0              = NULL;
	m_iBeamIDs             = NULL;
	m_fPrevPhaseBias       = NULL;
	m_iPredictedSATIDs     = NULL;
	m_fProbability         = NULL;
	m_iPrevPassSchedSATIDs = NULL;
	m_acDBFBeamVectors     = NULL;
	m_acDBFCarrierVectors  = NULL;
	m_afPowerSpectrum1     = NULL;
	m_iOutputBuffer        = NULL;

	//snl
	m_oDBFBufferPhaseLastWriteTime =  m_oDBFCovarFileLastWriteTime = 0;
	//m_bIsCovarFileSendTime = FALSE;
//	m_oDBFpass.Initialize(1);
}

CDigitalBeamFormer::CDigitalBeamFormer( const CDigitalBeamFormer& x ) : m_ulChannels( x.m_ulChannels ),
							m_ulSamplesPerChannel( x.m_ulSamplesPerChannel ),m_ulSatellites(x.m_ulSatellites), 
							m_lpOutputFile( NULL), m_lpTraceFile(NULL), m_lpCalibFile(NULL), m_asRawTimeSeries( NULL ),
							//m_asPhaseVector( NULL ),
							m_asDBFVector( NULL ), m_afRawInputSamples( NULL ),m_qrefDBFBeamVectors(x.m_qrefDBFBeamVectors)
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

	//if (m_asPhaseVector)
	//{
	//	delete [] m_asPhaseVector;
	//	m_asPhaseVector = NULL;
	//}

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

	if (m_nBeam)
	{
		delete [] m_nBeam;
		m_nBeam = NULL;
	}
	
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
	if (m_acFFTBeacon)
	{
		delete [] m_acFFTBeacon;
		m_acFFTBeacon = NULL;
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

	if( m_pDataTransmit2 )
	{
		m_pDataTransmit2->Disconnect();
		m_pDataTransmit2->Release();
		m_pDataTransmit2 = NULL;
	}

	if( m_iBeamIDs )
	{
		delete [] m_iBeamIDs;
		m_iBeamIDs = NULL;
	}
	
	if( m_fPrevPhaseBias )
	{
		delete [] m_fPrevPhaseBias;
		m_fPrevPhaseBias = NULL;
	}

	if( m_iPredictedSATIDs	)
	{
		delete [] m_iPredictedSATIDs;
		m_iPredictedSATIDs = NULL;
	}

	if( m_fProbability )
	{
		delete [] m_fProbability;
		m_fProbability = NULL;
	}

	if( m_iPrevPassSchedSATIDs )
	{
		delete [] m_iPrevPassSchedSATIDs;
		m_iPrevPassSchedSATIDs = NULL;
	}

	if (m_acCovariance) 
	{ 
		delete[] m_acCovariance;
		m_acCovariance = NULL; 
	}
	if (m_acDBFBeamVectors)
	{ 
		delete[] m_acDBFBeamVectors;
		m_acDBFBeamVectors = NULL;
	}
	if (m_acDBFCarrierVectors)
	{ 
		delete[] m_acDBFCarrierVectors;
		m_acDBFCarrierVectors = NULL;
	}
	if (m_afPulseShape)
	{ 
		delete[] m_afPulseShape;
		m_afPulseShape = NULL;
	}

	if (m_nBeam)
	{
		for (int i = 0; i < DBF_MAX_SATELLITES; ++i)
		{
			delete[] m_nBeam[i];
			m_nBeam[i] = nullptr;
		}
		delete[] m_nBeam;
		m_nBeam = NULL;
	}
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

	m_aDBFplate.emsDBFCells[0].fNearField = 35.592494;
	m_aDBFplate.emsDBFCells[1].fNearField = 5.572746;
	m_aDBFplate.emsDBFCells[2].fNearField = 355.490853;
	m_aDBFplate.emsDBFCells[3].fNearField = 5.572746;

	m_aDBFplate.emsDBFCells[4].fNearField = 199.019379;
	m_aDBFplate.emsDBFCells[5].fNearField = 180.19177;
	m_aDBFplate.emsDBFCells[6].fNearField = 199.019379;
	m_aDBFplate.emsDBFCells[7].fNearField = 11.630403;

	m_aDBFplate.emsDBFCells[8].fNearField = 46.176249;
	m_aDBFplate.emsDBFCells[9].fNearField = 102.650786;
	m_aDBFplate.emsDBFCells[10].fNearField = 200.2468;
	m_aDBFplate.emsDBFCells[11].fNearField = 178.699527;
	
	m_aDBFplate.emsDBFCells[12].fNearField = 178.699527;
	m_aDBFplate.emsDBFCells[13].fNearField = 200.2468;
	m_aDBFplate.emsDBFCells[14].fNearField = 242.794422;
	m_aDBFplate.emsDBFCells[15].fNearField = 216.540413;

	m_aDBFplate.emsDBFCells[16].fNearField = 191.527404;
	m_aDBFplate.emsDBFCells[17].fNearField = 191.527404;
	m_aDBFplate.emsDBFCells[18].fNearField = 216.540413;
	m_aDBFplate.emsDBFCells[19].fNearField = 102.650786;

	m_aDBFplate.emsDBFCells[20].fNearField = 46.176249;
	m_aDBFplate.emsDBFCells[21].fNearField = 11.630403;
	m_aDBFplate.emsDBFCells[22].fNearField = 0;
	m_aDBFplate.emsDBFCells[23].fNearField = 256.362618;

	m_aDBFplate.emsDBFCells[24].fNearField = 226.931752;
	m_aDBFplate.emsDBFCells[25].fNearField = 256.362618;
	m_aDBFplate.emsDBFCells[26].fNearField = 35.894619;
	m_aDBFplate.emsDBFCells[27].fNearField = 22.279002;

	m_aDBFplate.emsDBFCells[28].fNearField = 35.894619;
	m_aDBFplate.emsDBFCells[29].fNearField = 76.19085;
	m_aDBFplate.emsDBFCells[30].fNearField = 265.717048;


	// One second pulse shape function

	m_afPulseShape = new float[ PULSE_SHAPE_SIZE ];

	for ( int i = 0; i < PULSE_SHAPE_SIZE; i++ )
	{

		float t = (float) i / (float) PULSE_SHAPE_SIZE; 
		m_afPulseShape[i] = t * exp( t ) / exp ( 1.0 );
	}

	
	m_asRawTimeSeries = new unsigned long[ DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS ];
	//m_asPhaseVector   = new short[ DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * 2 ];
	m_asDBFVector     = new short[ DBF_SAMPLE_SIZE * DBF_MAX_SATELLITES * 2 ];

	m_acCovariance    = new EMSCOMPLEX[ COVARIANCE_SIZE ];     // Covariance matrix
	m_acDBFBeamVectors = new EMSCOMPLEX[ DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES ];
	m_acDBFCarrierVectors = new EMSCOMPLEX[ DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES ];

	memset( m_asRawTimeSeries, 0, DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long) );
	//memset( m_asPhaseVector, 1.0, DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * 2 * sizeof(short));
	memset( m_asDBFVector, 0, DBF_SAMPLE_SIZE * DBF_MAX_SATELLITES * 2 * sizeof(short));
	
	memset( m_acCovariance, 0, COVARIANCE_SIZE * sizeof(EMSCOMPLEX));
	memset( m_acDBFBeamVectors, 0, DBF_NUM_ELEMENTS * DBF_MAX_SATELLITES * sizeof(EMSCOMPLEX));

	m_afRawInputSamples = new float[DBF_LOG20_SIZE];
	m_afPowerSpectrum	= new float[DBF_LOG19_SIZE + 1];
	//m_acFFTdata			= new EMSCOMPLEX*[DBF_MAX_SATELLITES];
	m_nBeam				= new short*[DBF_MAX_SATELLITES];
	m_fPrevPhaseBias		= new float[DBF_NUM_ELEMENTS];
	m_iBeamIDs				= new int[DBF_MAX_SATELLITES];
	m_iPredictedSATIDs		= new int[DBF_MAX_SATELLITES];
	m_fProbability			= new float[DBF_MAX_SATELLITES];
	m_iPrevPassSchedSATIDs	= new int[DBF_MAX_SATELLITES];

	for(int i = 0; i < DBF_MAX_SATELLITES; ++i)
	{
		m_nBeam[i]			= new short[DBF_OUTPUT_SIZE];
		memset( m_nBeam[i], 0, sizeof(short) * DBF_OUTPUT_SIZE );
	}
	
	memset( m_afRawInputSamples, 0, DBF_SAMPLE_SIZE*sizeof(float));
	memset( m_afPowerSpectrum, 0, (DBF_LOG19_SIZE + 1)*sizeof(float));

	m_afTemp1	= new float[DBF_LOG20_SIZE];
	m_afTemp2	= new float[DBF_LOG20_SIZE];
	m_acTemp1	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acTemp2	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acTemp3	= new EMSCOMPLEX[DBF_LOG20_SIZE];
	m_acFFTBeacon = new EMSCOMPLEX[DBF_LOG16_SIZE];
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

	memset( &m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORDS2));
	memset( &m_aMaintenance, 0, sizeof(EMSDBFMAINTENANCE));
	memset( &m_aDBFplate, 0, sizeof(EMSDBFARRAY));

	if ( (m_ulSamplesPerChannel>0) && (m_ulChannels>0) && (m_ulSatellites>0) 
		//&& (m_asRawTimeSeries) && (m_asPhaseVector) && (m_asDBFVector)
		&& (m_asRawTimeSeries) && (m_asDBFVector)
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
	_stprintf( cTraceFileName, TEXT( "%sDBFtrace_%02d.csv" ), CDBFCollectorConfig::GetInstance().GetCalibTraceDir().c_str(), m_iObjectID );
				
//	lstrcat( cTraceFileName, cTempName ); 
				
	if (m_lpTraceFile)
	{
		fclose(m_lpTraceFile);
		m_lpTraceFile = nullptr;
	}
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

	if( m_pDataTransmit2 )
	{
		m_pDataTransmit2->Disconnect();
		m_pDataTransmit2->Release();
		m_pDataTransmit2 = NULL;
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

void
CDigitalBeamFormer::SetSPIP(string SPIP)
{
	m_wsSPIP = std::wstring(SPIP.begin(), SPIP.end());
}

void
CDigitalBeamFormer::SetSPIP2(string SPIP2)
{
	m_wsSPIP2 = std::wstring(SPIP2.begin(), SPIP2.end());
}

HRESULT
CDigitalBeamFormer::_InitDT()
{
	EMS_RESULT hr =  E_FAIL;
	if(!m_pDataTransmit)
	{
		hr = CoCreateInstance( CLSID_DataXmitter, NULL, CLSCTX_ALL,
							   IID_IEMSDataTransmitter, (void**) &m_pDataTransmit );

		if( EMS_OK != hr || m_pDataTransmit == NULL)
		{
			//printf("\n Failed to load Data Transmitter");
		}
		else if (EMS_OK != m_pDataTransmit->Connect(m_wsSPIP.c_str()))
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

HRESULT
CDigitalBeamFormer::_InitDT2()
{
	EMS_RESULT hr = E_FAIL;
	if( m_wsSPIP2.empty() )
		return hr;
	if( !m_pDataTransmit2 )
	{
		hr = CoCreateInstance( CLSID_DataXmitter2, NULL, CLSCTX_ALL,
							   IID_IEMSDataTransmitter, (void**) &m_pDataTransmit2 );

		if( EMS_OK != hr || m_pDataTransmit2 == NULL )
		{
		}
		else if( EMS_OK != m_pDataTransmit2->Connect(m_wsSPIP2.c_str()) )
		{
			m_pDataTransmit2->Release();
			m_pDataTransmit2 = NULL;
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
		hr = DBFprocessorCP(tm);

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
		fflush( m_lpTraceFile );
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
	//oActualTime.AddSeconds(-0.5);
	
	// RR .. 2.5 second offset correction
	oActualTime.AddSeconds(-2.5);

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
CDigitalBeamFormer::DBFprocessorSUM(EMSTIME tm)
{
	EMSTIME timeStart, timeFinish;

	timeStart.intTime  = tm.intTime;
	timeFinish.intTime = 0;

	INT64   i64ElapsedTime = 0;

	EMS_RESULT hr = EMS_OK;

	_IsTimeToCopyBufferPhaseFile( tm );

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
		_stprintf( szFileName, TEXT( "%sDBFCovariance-%04d.bin" ), CDBFCollectorConfig::GetInstance().GetCovarianceDir().c_str(), ulMinutes );

		FILE* lpCovFile = fopen(szFileName,"wb");
		if( lpCovFile )
		{
			fwrite( &aCOV, sizeof( EMSDBFCOVARIANCE ), 1, lpCovFile );
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
		//char  cTime[256];
		//*cTime = _GetTimeNano( tm );

		CEMSTime oTime(tm);
		char cTime[256];
		EMSTIMEFIELDS tmFields;
		memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
		
		oTime.GetTime( &tmFields );
		float fSecond = (float) tmFields.nSecond + ((float)tmFields.lNanosecond) * 1e-9;
		sprintf(cTime,"%04d\\%03d %02d:%02d:%09.6f",
			tmFields.nYear, tmFields.nJulianDay, tmFields.nHour, tmFields.nMinute, fSecond );


		fprintf( m_lpTraceFile, "1, %d, %s, %f,%f, %f,%f,%f, %ld, %ld, %ld",
			m_nCounter, cTime, m_dElapsedTime, m_dAverageTime,
			m_dMeanADC, m_dStdDevADC, m_dMaxPower, m_ulStartPPS, m_ulStopPPS - m_ulStartPPS,
			m_ulMaxPowerIndex);

		for (int i = 0; i < m_ulChannels-1; i++)
		{
			fprintf(m_lpTraceFile,", %02d, %f, %f", i+1, m_aMaintenance.dMean[i], m_aMaintenance.dStdDev[i] );
		}
		fprintf(m_lpTraceFile,"\n");
		fflush( m_lpTraceFile );

	}
	return hr;
}

//---------------------------------------------------------------------------

// Frequency Domain Processing: Performs carrier tracking

EMS_RESULT
CDigitalBeamFormer::DBFprocessorCP(EMSTIME tm )
{

	EMS_RESULT hr = EMS_BAD_PARAM;
	ULONG ulBand50  = 50000; // 50 kHz bandwidth offset 
	ULONG ulBand100 = ulBand50 *2; // 100 kHz downlink bandwidth

	CEMSTime oTime( tm );
	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
	oTime.GetTime( &tmFields );
	
	//CToaFoaProcessor toaFoaProc(m_qrefDBFBeamVectors, m_ulSatellites); 
	
	bool bTimeFreqFlag = false;  // flag set false for frequency domain storage
	bool bBandwidthFlag = false;
	if ( m_ProcessFlag & PROCESS_OUTPUT_SAMPLERATE ) bBandwidthFlag = true;
		
	m_bEigenFlag = false;

	if (m_asRawTimeSeries )
	{
		ULONG i, icell, jsample, index, ichunk;
		double dPower  = 0.0;
		double dMean = 0.0;
		double dStdDev = 0.0;

		CEMSTime timeStart  =  CEMSSystemClock::GetTime();
		CEMSTime timeEnd    =  CEMSSystemClock::GetTime();

		hr = InitializeMemory();
		
		//hr = BufferStatistics( m_asRawTimeSeries );

		hr = ComputeChannelData(  bTimeFreqFlag, bBandwidthFlag );
		
		m_ulFreqIndex = 0;
		m_fMaxPower   = 0.0;
		hr = DBFCarrierTrack( tm, &m_ulFreqIndex, &m_fMaxPower );
		
		hr = BiasEstimator( tm );
		
		hr = ApplyDBFBeamVectors( m_ulSatellites, bTimeFreqFlag, bBandwidthFlag );
		
		_OutputWaveEx( tm, m_ulSatellites, bBandwidthFlag );

		timeEnd =  CEMSSystemClock::GetTime();
		i = 0;
		float fTOAdiff = m_aTOAFOA.fBeaTOA[i]-m_aTOAFOA.fTOA[i];
		float fFOAdiff = m_aTOAFOA.fBeaFOA[i]-m_aTOAFOA.fFOA[i];

		printf("%04d/%02d/%02d %02d:%02d:%02d.%06d, dTOA %6.3f, dFOA %6.1f, Sat %d (%d), Az %6.2f (%6.1f), El %5.2f (%5.2f), Time %f\n",
			tmFields.nYear, tmFields.nMonth, tmFields.nDay, tmFields.nHour,
			tmFields.nMinute, tmFields.nSecond, (UINT)(tmFields.lNanosecond/1000),
			fTOAdiff, fFOAdiff, m_aPassSchedule.rec[i].ulSatID, m_ulSatellites,
				m_aPassSchedule.rec[i].fAzimuth,m_aPassSchedule.rec[i].fPlateAzimuth,
				m_aPassSchedule.rec[i].fElevation,m_aPassSchedule.rec[i].fPlateElevation,
				timeStart.SecondsDifferent( timeEnd) );

	}

	return hr;
}

//---------------------------------------------------------------------------

// Time Domain Processing : Computes correlation matrix

EMS_RESULT 
CDigitalBeamFormer::DBFprocessorEP( EMSTIME tm )
{
	EMS_RESULT hr = EMS_BAD_PARAM;
	bool bTimeFreqFlag = true;  // flag set true for time domain storage

	//CToaFoaProcessor toaFoaProc = CToaFoaProcessor(m_qrefDBFBeamVectors, m_ulSatellites);

	ULONG ulBand50  = 100000; // 50 kHz bandwidth (0.5 Hz bin size)
	ULONG ulBand100 = ulBand50 *2; // 100 kHz bandwidth
	
	bool bBandwidthFlag = false;
	if ( m_ProcessFlag & PROCESS_OUTPUT_SAMPLERATE ) bBandwidthFlag = true;

	CEMSTime oTime( tm );
	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
	oTime.GetTime( &tmFields );

	if ( m_asRawTimeSeries )
	{
		ULONG i, icell, jsample, index, ichunk;
		double dPower  = 0.0;
		double dMean = 0.0;
		double dStdDev = 0.0;

		CEMSTime timeStart  =  CEMSSystemClock::GetTime();
		CEMSTime timeStart1 =  CEMSSystemClock::GetTime();
		CEMSTime timeEnd    =  CEMSSystemClock::GetTime();

		hr = InitializeMemory();
		
		hr = InitializeTOAFOA( tm );

		hr = SeparationAngle( m_ulSatellites );

		//hr = BufferStatistics( m_asRawTimeSeries );

		hr = ComputeChannelData(  bTimeFreqFlag, bBandwidthFlag );
		//timeEnd =  CEMSSystemClock::GetTime();
		//printf( "ProcessEP1 RAW -> Time elapsed 0 : %f seconds, id: %i \n" ,timeStart.SecondsDifferent( timeEnd) , GetCurrentThreadId() );

		timeStart1 =  CEMSSystemClock::GetTime();
		hr = ComputeCovariance( ulBand100 );
		//timeEnd =  CEMSSystemClock::GetTime();
		//printf( "ProcessEP1 COV -> Time elapsed 1 : %f seconds, id: %i \n" ,timeStart1.SecondsDifferent( timeEnd) , GetCurrentThreadId() );

		timeStart1 =  CEMSSystemClock::GetTime();

		hr = ComputeDBFBeamVectors( m_ulSatellites, m_acCovariance);

		m_bEigenFlag = true;
		m_ulFreqIndex = 0;
		m_fMaxPower   = 0.0;
		hr = DBFCarrierTrack( tm, &m_ulFreqIndex, &m_fMaxPower );

		hr = BiasEstimator( tm  );

		hr = ApplyDBFBeamVectors( m_ulSatellites, bTimeFreqFlag, bBandwidthFlag );

		IdentifyTOAFOA( tm, m_acDBFBeamVectors);

		_OutputWaveEx( tm, m_ulSatellites, bBandwidthFlag );

		timeEnd =  CEMSSystemClock::GetTime();
		if (tmFields.nSecond % 10 == 0 )
		{
			printf(" %02d:%02d:%02d.%3d : Time %6.3f: Id %i : Sats %d ( ",
				tmFields.nHour, tmFields.nMinute, tmFields.nSecond,tmFields.lNanosecond/1000,
				timeStart.SecondsDifferent( timeEnd), GetCurrentThreadId(), m_ulSatellites);
			for (int k = 0; k < m_ulSatellites; k++)
			{
				printf(" %03d",m_aPassSchedule.rec[k].ulSatID);
			}
			printf(")\n");
		}

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
CDigitalBeamFormer::SetPassSchedule( EMSDBFPASSRECORDS2* pPassRecords, EMSTIME tm )
{

	EMS_RESULT hr = EMS_OK;
	if( pPassRecords )
	{
		// read pass schedule information for time 'tm'

		memcpy(&m_aPassSchedule, pPassRecords, sizeof(EMSDBFPASSRECORDS2) );

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
		memset(&m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORDS2) );
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

static CEMSWaveEx _BuildWaveEx(EMSTIME tm,
		const short* pSamples, ULONG ulSampleCount,
		ULONG ulSampleRate, WORD wSoftwareVersion,
		ULONG ulLutID, ULONG ulSatID, WORD wAntID,
		double dMeanADC, double dStdDevADC,
		float fProbability,
		double dAz, double dEl, double dPlateAz, double dPlateEl,
		bool bBeaconPresent, DWORD dwBeaconFlag)
{
	CEMSWaveEx w;
	w.Write((unsigned char*)pSamples, ulSampleCount * sizeof(short));
	w.GetFormatChunkRef().SetAudioFormat(1);
	w.GetFormatChunkRef().SetNumChannels(1);
	w.GetFormatChunkRef().SetSampleRate(ulSampleRate);
	w.GetFormatChunkRef().SetBitsPerSample(16);
	w.GetExtendedInfoRef().GetLutDetailsRef().SetLutID(ulLutID);
	w.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID(wAntID);
	w.GetExtendedInfoRef().GetSatDetailsRef().SetSatID(ulSatID);
	w.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart(tm);
	w.GetExtendedInfoRef().GetPropertiesRef().SetHardwareVersion(32);
	w.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion(wSoftwareVersion);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC(dMeanADC);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC(dStdDevADC);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState(EMS_DC_NO);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags(0);
	if (fProbability)
		w.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanCarrierFreq(fProbability);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex(dAz);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex(dEl);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevCarrierFreq(dPlateAz);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevModIndex(dPlateEl);
	w.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState(
		ulSatID < 200 ? EMS_PHASE_MOD_YES : EMS_PHASE_MOD_NO);
	if (bBeaconPresent)
		w.GetExtendedInfoRef().GetSatDetailsRef().SetSatFlags(dwBeaconFlag);
	return w;
}

//---------------------------------------------------------------------------

//void
//CDigitalBeamFormer::_OutputWaveEx( EMSTIME tm, ULONG culNumSats, bool bBandwidthFlag  )
//{
//	EMSTIME timeStart =  CEMSSystemClock::GetTime();
//	EMS_RESULT hr = EMS_OK;
//	if( culNumSats > DBF_MAX_SATELLITES )
//		culNumSats = DBF_MAX_SATELLITES;
//	if( !m_bOutputOK )
//		return;
//
//	//int *beamID = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
//	//int *predSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
//	//double *probability = m_qrefDBFBeamVectors.ReadFirst( ).probability;
//	//double dProbThreshold = 0.9;
//
//	
//
//	for( int iSat = 0; iSat < culNumSats; iSat++ )
//	{
//		int iPredictedSatIndex = 0;
//		for (int jSat = 0; jSat < culNumSats; jSat++) {
//			if (m_aPassSchedule.rec[jSat].ulSatID == m_aTOAFOA.ulSatID[iSat]) {
//				iPredictedSatIndex = jSat;
//				break;
//			}
//		}
//		
//		//if ( probability[iSat] < dProbThreshold ) continue;
//
//		CEMSWaveEx oWaveOut;
//
//		DWORD dwBytes = 0;
//		BYTE* abyData = 0;
//
//		ULONG ulLutID  = m_aPassSchedule.rec[iPredictedSatIndex].ulLutID;
//		ULONG ulSatID  = m_aPassSchedule.rec[iPredictedSatIndex].ulSatID;
//		WORD  wPlateID = m_aPassSchedule.rec[iPredictedSatIndex].wPlateID;
//		WORD  wAntennaID = m_aPassSchedule.rec[iPredictedSatIndex].wAntennaID;
//		double dSatAzimuth = (double) m_aPassSchedule.rec[iPredictedSatIndex].fAzimuth;
//		double dSatElevation = (double) m_aPassSchedule.rec[iPredictedSatIndex].fElevation;
//		double dPlateAzimuth = (double) m_aPassSchedule.rec[iPredictedSatIndex].fPlateAzimuth;
//		double dPlateElevation = (double) m_aPassSchedule.rec[iPredictedSatIndex].fPlateElevation;
//		//if( ulSatID >= 200 && dSatElevation < MEO_MIN_ELEVATION )	//snl added to check > 20 if pass sched has no elev constraints
//		//	continue;
//
//		WORD dHardWareVersion = 32; // 32 channel ADC
//		WORD dSoftWareVersion = 2001;  // 200 kHz, 1 second buffer
//		if ( bBandwidthFlag ) dSoftWareVersion = 1001; // 100 kHz, 1 second buffer
//		if ( m_ulSamplesPerChannel > 500001 ) dSoftWareVersion += 1; // 2 second buffer
//
//
//		//ULONG ulBytes = sizeof(short) * DBF_OUTPUT_SIZE;
//		//if ( bBandwidthFlag ) ulBytes /= 2;
//
//		// Select satellite id that matches pass schedule ID
//		//for ( int iPredictedSatIndex = 0; iPredictedSatIndex < culNumSats; iPredictedSatIndex++)
//		{
//			//if (( ulSatID == m_iPredictedSATIDs[iPredictedSatIndex]) || culNumSats==1 )
//			{
//				//oWaveOut.Write( (unsigned char*)&m_nBeam[iPredictedSatIndex][0], ulBytes );
//				
//				//oWaveOut.Write( (unsigned char*)&m_nBeam[iPredictedSatIndex][0], ulBytes/2 );
//				
//				//oWaveOut.Write( (unsigned char*)&m_nBeam[iPredictedSatIndex][0], ulBytes/2 ); // 1 second buffers
//				//break;
//			}
//		}
//		oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
//		oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
//
//		ULONG ulSampleRate = (ULONG) (0.8 * (float)(m_ulStopPPS - m_ulStartPPS));
//		
//		//RR .. Protect against missing PPS signal
//		if (ulSampleRate < 390000 || ulSampleRate > 410000) ulSampleRate = 400000;
//		
//		//if ( bBandwidthFlag )
//		//{
//		//	oWaveOut.GetFormatChunkRef().SetSampleRate( ulSampleRate/2 );
//		//}
//		//else
//		//{
//		//	oWaveOut.GetFormatChunkRef().SetSampleRate( ulSampleRate );
//		//}
//		oWaveOut.GetFormatChunkRef().SetBitsPerSample( 16 );
//
//
//		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
//		oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
//		WORD wAntID = 0;
//		//wAntID = wPlateID*100 +  (WORD) iPredictedSatIndex;
//		wAntID = wAntennaID*100 +  (WORD) iPredictedSatIndex;
//		oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( wAntID );
//
//		//EMSTIME tempTime = CEMSSystemClock::GetTime();
//		//oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart(tempTime);
//		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );
//
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC );
//
//		// Set additional properties indicating whether the signal requires downconversion
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );//EMS_DC_YES
//	
//		// Set flag indicating whether the marker bit was found for this measurement.
//	//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );
//	//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( m_ulStartPPS );
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( 0 );
//		
//		//if( predSatIDs )
//		//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( predSatIDs[ iPredictedSatIndex ] );
//		if( m_fProbability[iPredictedSatIndex] )
//			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanCarrierFreq( m_fProbability[ iPredictedSatIndex ] );
//
//		// RR added azimuth and elevation of satellite
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dSatAzimuth );
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dSatElevation );
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevCarrierFreq( dPlateAzimuth );
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevModIndex( dPlateElevation );
//
//		// Set additional properties indicating whether the signal requires phase demod
//		if ( ulSatID < 200 ) // LEO satellites
//			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
//		else
//			oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );
//
//		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetHardwareVersion( dHardWareVersion );
//		//oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion( dSoftWareVersion );
//
//		// Add reference beacon indicator
//		if ( m_aPassSchedule.rec[iPredictedSatIndex].fBeaconElevation > 0.0 )
//		{
//			DWORD dFlag = (DWORD) m_aPassSchedule.rec[iPredictedSatIndex].fFOA;
//			oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatFlags( dFlag );
//		}
//
//		CEMSWaveEx oWaveOut2 = oWaveOut;
//
//		hr = _InitDT();
//		if( m_pDataTransmit )
//		{
//			int iSent = 0;
//			ULONG ulBytes = sizeof(short) * DBF_OUTPUT_SIZE;
//			short* newBuffer = new short[400000];
//			int j = 0;
//
//			for (int i = 0, j = 0; i < 400000; i++, j += 2) {
//				newBuffer[i] = m_nBeam[iPredictedSatIndex][j];
//				if (i % 2) {
//					newBuffer[i] *= -1;
//				}
//			}
//			oWaveOut.Write((unsigned char*)&newBuffer[0], ulBytes / 2);
//
//			// 100 kHz, 2s buffer
//			oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion(1002);
//			oWaveOut.GetFormatChunkRef().SetSampleRate(ulSampleRate / 2);
//			dwBytes = oWaveOut.Serialize(abyData);
//
//			if (dwBytes > 0)
//			{
//				hr = m_pDataTransmit->Send(dwBytes, abyData, &iSent);
//			}
//		}
//		if(FAILED(hr) )
//		{
//
//			// WAV file output to disk
//			FILE*	lpWaveFile = NULL;
//			char	szFileName[256];
//			ULONG	ulFileNumber = ((ULONG)m_nCounter) % 100;
//			sprintf(szFileName,"%sDBFRAW_%07d_%03d_%04d.wav", CDBFCollectorConfig::GetInstance().GetWavOutputDir().c_str(), ulFileNumber, ulSatID, ulLutID);
//
//			lpWaveFile = fopen(szFileName,"w+b");
//			if( lpWaveFile != NULL )
//			{
//				fwrite(abyData, dwBytes, 1, lpWaveFile);
//				flushall();
//				fclose(lpWaveFile);
//				lpWaveFile = NULL;
//			}
//		}
//
//		// Forward to secondary destination if configured
//		_InitDT2();
//		if( m_pDataTransmit2 )
//		{
//			int iSent2 = 0;
//			ULONG ulBytes = (sizeof(short) * DBF_OUTPUT_SIZE) / 2;
//				
//			oWaveOut2.Write((unsigned char*)&m_nBeam[iPredictedSatIndex][0], ulBytes );
//
//			oWaveOut2.GetFormatChunkRef().SetSampleRate(ulSampleRate);
//				
//			// 200 kHz, 1s buffer
//			oWaveOut2.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion(2001);
//			dwBytes = oWaveOut2.Serialize(abyData);
//
//			if (dwBytes > 0)
//			{
//				hr = m_pDataTransmit2->Send(dwBytes, abyData, &iSent2);
//			}
//		}
//
//
//		delete[] abyData;
//		abyData = 0;
//	}
//	
//
//	return;
//}

//---------------------------------------------------------------------------

void
CDigitalBeamFormer::_OutputWaveEx(EMSTIME tm, ULONG culNumSats, bool bBandwidthFlag)
{
	EMS_RESULT hr = EMS_OK;
	if (culNumSats > DBF_MAX_SATELLITES)
		culNumSats = DBF_MAX_SATELLITES;
	if (!m_bOutputOK)
		return;

	ULONG ulSampleRate = (ULONG)(0.8f * (float)(m_ulStopPPS - m_ulStartPPS));
	if (ulSampleRate < 390000 || ulSampleRate > 410000) ulSampleRate = 400000;

	// Samples per output: half the available buffer → 1-second payload at Nyquist rate
	//ULONG ulSampleCount = bBandwidthFlag ? (DBF_OUTPUT_SIZE / 4) : (DBF_OUTPUT_SIZE / 2);
	//ULONG ulRate = bBandwidthFlag ? (ulSampleRate / 2) : ulSampleRate;
	ULONG ulSampleRate2 = (ulSampleRate / 2);
	WORD  wVersion = bBandwidthFlag ? 1001 : 2001;
	if (m_ulSamplesPerChannel > 500001) wVersion++;  // 2 second buffer

	for (int iSat = 0; iSat < (int)culNumSats; iSat++)
	{
		int iPredSat = 0;
		for (int jSat = 0; jSat < (int)culNumSats; jSat++)
		{
			if (m_aPassSchedule.rec[jSat].ulSatID == m_aTOAFOA.ulSatID[iSat])
			{
				iPredSat = jSat;
				break;
			}
		}

		ULONG  ulLutID = m_aPassSchedule.rec[iPredSat].ulLutID;
		ULONG  ulSatID = m_aPassSchedule.rec[iPredSat].ulSatID;
		WORD   wPlateID = m_aPassSchedule.rec[iPredSat].wPlateID;
		WORD   wAntennaID = m_aPassSchedule.rec[iPredSat].wAntennaID;
		double dAz = (double)m_aPassSchedule.rec[iPredSat].fAzimuth;
		double dEl = (double)m_aPassSchedule.rec[iPredSat].fElevation;
		double dPlateAz = (double)m_aPassSchedule.rec[iPredSat].fPlateAzimuth;
		double dPlateEl = (double)m_aPassSchedule.rec[iPredSat].fPlateElevation;
		bool   bBeacon = m_aPassSchedule.rec[iPredSat].fBeaconElevation > 0.0f;
		DWORD  dwBeaconFlag = bBeacon ? (DWORD)m_aPassSchedule.rec[iPredSat].fFOA : 0;
		WORD   wAntID = wAntennaID * 100 + (WORD)iPredSat;

		// Primary output → m_pDataTransmit (200kHz 1s buffer -> SP) (file fallback on failure)
		{
			CEMSWaveEx wPrimary = _BuildWaveEx(tm,
				&m_nBeam[iPredSat][0], (DBF_OUTPUT_SIZE / 2),
				ulSampleRate, wVersion,
				ulLutID, ulSatID, wAntID,
				m_dMeanADC, m_dStdDevADC,
				m_fProbability[iPredSat],
				dAz, dEl, dPlateAz, dPlateEl,
				bBeacon, dwBeaconFlag);

			DWORD dwBytes = 0;
			BYTE* abyData = 0;
			dwBytes = wPrimary.Serialize(abyData);
			if (dwBytes > 0)
			{
				int iSent = 0;
				hr = _InitDT();
				if (m_pDataTransmit)
					hr = m_pDataTransmit->Send(dwBytes, abyData, &iSent);

				if (FAILED(hr))
				{
					if (m_pDataTransmit)
					{
						m_pDataTransmit->Release();
						m_pDataTransmit = NULL;
					}

					FILE* lpWaveFile = NULL;
					char  szFileName[256];
					ULONG ulFileNumber = ((ULONG)m_nCounter) % 100;
					sprintf(szFileName, "%sDBFRAW_%07d_%03d_%04d.wav",
						CDBFCollectorConfig::GetInstance().GetWavOutputDir().c_str(),
						ulFileNumber, ulSatID, ulLutID);
					lpWaveFile = fopen(szFileName, "w+b");
					if (lpWaveFile != NULL)
					{
						fwrite(abyData, dwBytes, 1, lpWaveFile);
						flushall();
						fclose(lpWaveFile);
					}

					lpWaveFile = NULL;
				}
			}
			delete[] abyData;
		}

		// Secondary output → m_pDataTransmit2 (100 kHz, 2s buffer -> Gen 10)
		_InitDT2();
		if (m_pDataTransmit2)
		{
			short* newBuffer = new short[400000];
			//short* newBuffer = new short[200000];
			memset(&m_afTemp1[0], 0, DBF_LOG20_SIZE * sizeof(float));
			memset(&m_acTemp1[0], 0, DBF_LOG20_SIZE * sizeof(EMSCOMPLEX));
			memset(&m_acTemp2[0], 0, DBF_LOG20_SIZE * sizeof(EMSCOMPLEX));

			for (ULONG i = 0; i < 800000; i++) {
				m_afTemp1[i] = (float)m_nBeam[iPredSat][i];
			}
			emssRealFftNip(&m_afTemp1[0], &m_acTemp1[0], DBF_LOG20, EMS_SPL_FWD);

			//memcpy(&m_acTemp2[0], &m_acTemp1[100000], 200000 * sizeof(EMSCOMPLEX));
			memcpy(&m_acTemp2[0], &m_acTemp1[100000], (DBF_LOG18_SIZE + 1) * sizeof(EMSCOMPLEX));
			
			ULONG ulMptsHalf = DBF_LOG18_SIZE;
			//ULONG ulMptsHalf = DBF_LOG17_SIZE;
			for (ULONG i = 1; i < ulMptsHalf; i++)
			{
				m_acTemp2[ulMptsHalf + i].re = m_acTemp2[ulMptsHalf - i].re;
				m_acTemp2[ulMptsHalf + i].im = -m_acTemp2[ulMptsHalf - i].im;
			}

			emscFft(&m_acTemp2[0], DBF_LOG19, EMS_SPL_INV);
			//emscFft(&m_acTemp2[0], DBF_LOG18, EMS_SPL_INV);

			/*for (ULONG i = 0; i < DBF_LOG19_SIZE; i++)
			{
				m_afTemp1[i] = m_acTemp2[i].re / DBF_LOG19_SIZE;
				m_afTemp2[i] = m_acTemp2[i].im / DBF_LOG19_SIZE;
			}*/
			for (ULONG i = 0; i < DBF_LOG19_SIZE; i++)
			{
				m_afTemp1[i] = m_acTemp2[i].re / DBF_LOG19_SIZE;
				m_afTemp2[i] = m_acTemp2[i].im / DBF_LOG19_SIZE;
			}
			double dRealAVE = 0.0;
			double dRealSTD = _EMSsMeanStdDev(&m_afTemp1[0], DBF_LOG19_SIZE, &dRealAVE);
			double dImagAVE = 0.0;
			double dImagSTD = _EMSsMeanStdDev(&m_afTemp2[0], DBF_LOG19_SIZE, &dImagAVE);
			
			/*for (ULONG i = 1; i < 400000; i++)
			{
				newBuffer[i] = (short)(m_acTemp1[i].re);
			}*/
			for (ULONG i = 0; i < 400000; i++)
			{
				newBuffer[i] = (short)(m_afTemp1[i]);
			}
			

			//oWaveOut.Write((unsigned char*)&newBuffer[0], 400000);

			//ULONG ulSampleCount2 = (sizeof(short) * DBF_OUTPUT_SIZE) / 2 / sizeof(short);  // 400,000 shorts
			ULONG ulSampleRate2 = (ulSampleRate / 2);
			ULONG ulSampleCount2 = 400000;
			//ULONG ulSampleRate2 = (ulSampleRate / 4);

			CEMSWaveEx wSecondary = _BuildWaveEx(tm,
				&newBuffer[0], ulSampleCount2,
				ulSampleRate2, 1002,
				ulLutID, ulSatID, wAntID,
				m_dMeanADC, m_dStdDevADC,
				m_fProbability[iPredSat],
				dAz, dEl, dPlateAz, dPlateEl,
				bBeacon, dwBeaconFlag);

			DWORD dwBytes2 = 0;
			BYTE* abyData2 = 0;
			try
			{
				dwBytes2 = wSecondary.Serialize(abyData2);
			}
			catch (...)
			{
				delete[] newBuffer;
				throw;
			}
			if (dwBytes2 > 0)
			{
				int iSent2 = 0;
				m_pDataTransmit2->Send(dwBytes2, abyData2, &iSent2);
			}
			delete[] abyData2;
			delete[] newBuffer;
		}
	}

	return;
}

//---------------------------------------------------------------------------

//void
//CDigitalBeamFormer::_OutputWaveFile( unsigned char* aData, EMSTIME tm, int iSat, bool bBandwidthFlag )
//{
//	EMS_RESULT hr = EMS_OK;
//	CEMSWaveEx oWaveOut;
//
//
//	char szFileName[256];
//	FILE *pWaveFile = 0;
//	DWORD dwBytes = 0;
//	BYTE* abyData = 0;
//			
//	WORD dHardWareVersion = 32; // 32 channel ADC
//	WORD dSoftWareVersion = 2;  // 2 second buffer
//
//
//
//	int *beamID = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
//	int *predSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
//	float *probability = m_qrefDBFBeamVectors.ReadFirst().probability;
//
//	ULONG ulLutID = m_aPassSchedule.rec[iSat].ulLutID;
//	ULONG ulSatID = m_aPassSchedule.rec[iSat].ulSatID;
//	WORD  wPlateID = m_aPassSchedule.rec[iSat].wPlateID;
//	WORD  wAntID   = wPlateID*1000 +  (WORD) beamID[iSat];
//
//	double dSatAzimuth = (double) m_aPassSchedule.rec[iSat].fAzimuth;
//	double dSatElevation = (double) m_aPassSchedule.rec[iSat].fElevation;
//	double dPlateAzimuth = (double) m_aPassSchedule.rec[iSat].fPlateAzimuth;
//	double dPlateElevation = (double) m_aPassSchedule.rec[iSat].fPlateElevation;
//
//
//	oWaveOut.GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
//	oWaveOut.GetFormatChunkRef().SetNumChannels( 1 );	// Mono
//	//oWaveOut.GetFormatChunkRef().SetSampleRate( DBF_SAMPLE_RATE );
//	
//	ULONG ulSampleRate = (ULONG) (0.8 * (float)(m_ulStopPPS - m_ulStartPPS));
//	if (ulSampleRate < 350000 ) ulSampleRate = 400000;
//	ULONG ulBytes = DBF_SAMPLE_SIZE * sizeof(short);
//
//	if (bBandwidthFlag )
//	{
//		oWaveOut.GetFormatChunkRef().SetSampleRate( ulSampleRate/2 );
//		oWaveOut.Write( (unsigned char*)aData, (ulBytes/2) * sizeof(unsigned char) );
//	}
//	else
//	{
//		oWaveOut.GetFormatChunkRef().SetSampleRate( ulSampleRate );
//		oWaveOut.Write( (unsigned char*)aData, ulBytes * sizeof(unsigned char) );
//	}
//	oWaveOut.GetFormatChunkRef().SetBitsPerSample( 16 );
//
//
//	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetLutID( ulLutID );
//	oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatID( ulSatID );
//	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( (WORD) ulLutID );
//	oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( tm );
//	oWaveOut.GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( wAntID );
//
//	// Set additional properties indicating whether the signal requires
//	// phase demod or down-conversion.
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( m_dMeanADC );
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( m_dStdDevADC );
//	if( probability )
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanCarrierFreq( probability[ iSat ] );
//
//	// RR added azimuth and elevation of satellite
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMaxModIndex( dSatAzimuth );
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetMeanModIndex( dSatElevation );
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevCarrierFreq( dPlateAzimuth );
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevModIndex( dPlateElevation );
//		
//	// Add HW/SW version information
//	oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetHardwareVersion( dHardWareVersion );
//	oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion( dSoftWareVersion );
//
//	// Wave has not yet been downconverted:
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );
//	
//	// Set flag indicating whether the marker bit was found for this measurement.
//	oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );
//
//	if ( ulSatID < 200 )
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES);
//	else
//		oWaveOut.GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO); 
//
//
//		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetHardwareVersion( dHardWareVersion );
//		oWaveOut.GetExtendedInfoRef().GetPropertiesRef().SetSoftwareVersion( dSoftWareVersion );
//
//		// Add reference beacon indicator
//		if ( m_aPassSchedule.rec[iSat].fBeaconElevation > 0.0 )
//		{
//			DWORD dFlag = (DWORD) m_aPassSchedule.rec[iSat].fFOA;
//			oWaveOut.GetExtendedInfoRef().GetSatDetailsRef().SetSatFlags( dFlag );
//		}
//
//
//		dwBytes = oWaveOut.Serialize( abyData );
//
//		if( dwBytes > 0  )
//		{
//			int iSent = 0;
//
//			hr = _InitDT();
//			if( m_pDataTransmit )
//			{
//				hr = m_pDataTransmit->Send( dwBytes, abyData, &iSent);
//			}
//			if(FAILED(hr) )
//			{
//		
//				// WAV file output to disk
//				FILE*	lpWaveFile = NULL;
//				char	szFileName[256];
//				ULONG	ulFileNumber = ((ULONG)m_nCounter) % 100;
//				sprintf(szFileName,"%sDBFRAW_%07d_%03d_%04d.wav", CDBFCollectorConfig::GetInstance().GetWavOutputDir().c_str(), ulFileNumber, ulSatID, ulLutID);
//
//				lpWaveFile = fopen(szFileName,"w+b");
//				if( lpWaveFile != NULL )
//				{
//					fwrite(abyData, dwBytes, 1, lpWaveFile);
//					flushall();
//					fclose(lpWaveFile);
//					lpWaveFile = NULL;
//				}
//			}
//		}
//
//
//		delete[] abyData;
//		abyData = 0;
//	
//
//	return;
//}


//snl for testing..tbr
#include <complex>
unsigned long long  GetFreeDiskSpaceInGBs ()
{
	ULARGE_INTEGER FreeBytesAvailable = { 0 };
    ULARGE_INTEGER TotalNumberOfBytes={ 0 };
    ULARGE_INTEGER TotalNumberOfFreeBytes={ 0 };

    BOOL ok = GetDiskFreeSpaceEx(
        CDBFCollectorConfig::GetInstance().GetDataDrive().c_str(),
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
//---------------------------------------------------------------------------

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
		float fSeconds = (float)(tmFields.nMinute)*60 + (float) (tmFields.nSecond)  + (float) (tmFields.lNanosecond)*1e-9;

		memset(szFileName, 0, sizeof(szFileName) );
		sprintf(szFileName,"%sDBFRawData_%09.6f_%03d_%03d_%03d_%03d.bin", CDBFCollectorConfig::GetInstance().GetADCRawDir().c_str(),
			fSeconds, m_aPassSchedule.rec[0].ulSatID,
			m_aPassSchedule.rec[1].ulSatID,
			m_aPassSchedule.rec[2].ulSatID,
			m_aPassSchedule.rec[3].ulSatID);
		pRawDataFile  = fopen(szFileName,"w+b");
		if( pRawDataFile  != NULL )
		{
			printf(" %s\n",szFileName);
			
			ULONG ulLength = culSize;
			fwrite(&ulLength, sizeof(ULONG), 1, pRawDataFile );
			fwrite(aData, culSize, 1, pRawDataFile );

			for ( int i = 0; i < m_ulSatellites; i++ )
			{
				fwrite( &m_aPassSchedule.rec[i],sizeof(EMSDBFPASSRECORD2), 1, pRawDataFile);
			}
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
	//m_timeActual;

	//m_asRawTimeSeries;
	float fScaleFactor        = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
	float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion

	ULONG jsample, index;

	for ( jsample = 0, index = 0; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )

	{
		unsigned long mTempTimeSeries = m_asRawTimeSeries[index] & 0x000FFFFF;
		m_afChan0[jsample] = (float) ( mTempTimeSeries * fScaleFactorInverse) ;
	}

	float fTimeDiff = 0.0;
	float fMaxTimeDiff1 = 0.0;
	float fMaxTimeDiff2 = 0.0;
	ULONG ulTimeMarker1 = 0;
	ULONG ulTimeMarker2 = 0;

	for ( jsample = 0; jsample < (m_ulSamplesPerChannel - 2);  jsample++ )
	{
		fTimeDiff = m_afChan0[jsample + 2] - m_afChan0[jsample];
		if (jsample < m_ulSamplesPerChannel/2)
		{
			if( fTimeDiff > fMaxTimeDiff1 )
			{
				fMaxTimeDiff1 = fTimeDiff;
				ulTimeMarker1 = jsample + 1;
			}
		}
		else
		{
			if( fTimeDiff > fMaxTimeDiff2 )
			{
				fMaxTimeDiff2 = fTimeDiff;
				ulTimeMarker2 = jsample + 1;
			}
		}
	}

	// Establish true sample rate.
	m_ulStartPPS = ulTimeMarker1;
	m_ulStopPPS  = ulTimeMarker2;


	long	lNanosecond = (long)(((float)ulTimeMarker1/DBF_SAMPLE_RATE) * 1e9);
	EMSTIMEFIELDS tmFlds;
	EMSTIMEFIELDS tmFlds_New;
	CEMSTime oTM(m_timeActual);

	// RR : adjust by -1 second for data collection delayed by 1 second due to 2 second buffer collection
	oTM.AddSeconds(-1.0);

	oTM.GetTime(&tmFlds);

	CEMSTime oActualTime;
	oActualTime.SetTime(tmFlds.nYear, tmFlds.nMonth, tmFlds.nDay, tmFlds.nHour, tmFlds.nMinute, tmFlds.nSecond, 0 );
	oActualTime.AddNanoseconds( -1 * lNanosecond );
	m_timeActual = oActualTime;

	CEMSTime oTM_New(m_timeActual);

	oTM_New.GetTime(&tmFlds_New);

}

void
CDigitalBeamFormer::ProcessAll()
{
	if( m_ulSatellites == 0 || m_aPassSchedule.rec[0].ulSatID == 0 )
		return;

	//find time taken to process
	CEMSTime timeStart =  CEMSSystemClock::GetTime();

	_SetActualTimeNew();

	m_aMaintenance.timestamp.intTime = m_timeActual.intTime;

	m_ProcessFlag = m_aPassSchedule.rec[0].wProcessID;

	m_ProcessFlag = PROCESS_DEFAULT; //200khz
	
	// Special test
	//m_ProcessFlag = 8; // RAW

	// Temporary fix
	//m_ProcessFlag = PROCESS_DEFAULT + PROCESS_OUTPUT_SAMPLERATE; // 100khz
	

	switch( m_ProcessFlag & 0x00FF ) 
	{
		case 0:
			break;
		case 1:
			{
				if ( m_ulSatellites > 0 )
				//if ( m_ulSatellites > 1 )
				{
					// Time Domain Processing ( Eigenvector Method )
					DBFprocessorEP(m_aMaintenance.timestamp);
					// Summary Output
					DBFprocessorSUM( m_aMaintenance.timestamp );
				}
				else
				{
					// Frequency Domain Processing ( carrier tracking)
					//m_ulSatellites = 1;
					DBFprocessorCP(m_aMaintenance.timestamp);
				}
			}
			break;
		case 2:
			{
				// Predicted Phase Processing ( Bias estimates )
				DBFprocessorPP(m_aMaintenance.timestamp);  // TBD
			}
			break;
		case 4:
			{
				// Frequency Domain Processing ( carrier tracking)
				DBFprocessorCP(m_aMaintenance.timestamp);
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
	
	//CEMSTime timeEnd =  CEMSSystemClock::GetTime();
	//printf( "ProcessAll -> Time elapsed:%f seconds, id: %i \n" ,timeStart.SecondsDifferent( timeEnd) , GetCurrentThreadId() );
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

			emsDBFCalib.Pass.fAzimuth = m_aPassSchedule.rec[0].fAzimuth;
			emsDBFCalib.Pass.fElevation = m_aPassSchedule.rec[0].fElevation;
			emsDBFCalib.Pass.fPlateAzimuth= m_aPassSchedule.rec[0].fPlateAzimuth;
			emsDBFCalib.Pass.fPlateElevation = m_aPassSchedule.rec[0].fPlateElevation;
			emsDBFCalib.Pass.timestamp.intTime = m_aPassSchedule.rec[0].timestamp.intTime;
			emsDBFCalib.Pass.ulSatID = m_aPassSchedule.rec[0].ulSatID;
			emsDBFCalib.Pass.wPlateID = m_aPassSchedule.rec[0].wPlateID;
			emsDBFCalib.Pass.ulLutID = m_aPassSchedule.rec[0].ulLutID;

			memcpy( emsDBFCalib.fCalibPhaseReal, m_LastCalibRecord.fCalibPhaseReal, sizeof(m_LastCalibRecord.fCalibPhaseReal) );
			memcpy( emsDBFCalib.fCalibPhaseImag, m_LastCalibRecord.fCalibPhaseImag, sizeof(m_LastCalibRecord.fCalibPhaseImag) );
			// Write binary Calib record
			fwrite( &emsDBFCalib, sizeof( EMSDBFCALIBRECORD ), 1, m_lpCalibFile );
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

		sprintf(szFileName, "%s_%d.bin", CDBFCollectorConfig::GetInstance().GetCalibFilePrefix().c_str(), m_iObjectID ); 
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
			m_pLogPhaseCorrection = fopen( (CDBFCollectorConfig::GetInstance().GetLogDir() + "phasecorrn.csv").c_str(), "at" );
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
CDigitalBeamFormer::DBFCarrierTrack( EMSTIME tm, ULONG *m_ulFreqIndex, float *m_fMaxpower )
{
	EMS_RESULT hr = EMS_OK;

	// Assume downconvertion by 50 kHZ and downlink is centred at 150 kHz
	//DOUBLE dBinSize   = (float) DBF_SAMPLE_RATE / (float) DBF_LOG20_SIZE;
	DOUBLE dBinSize = 0.5;
	ULONG ulOffset50  = (ULONG) (DBF_FREQ_OFFSET / dBinSize); // 50 kHz offset
	ULONG ulBandWidth = (ULONG) (DBF_FREQ_BANDWIDTH / dBinSize);

	WORD wOutSampleRate = PROCESS_OUTPUT_SAMPLERATE;
	if ( m_ProcessFlag & wOutSampleRate ) ulOffset50 *= 2;

	// Compute Incoherence average power spectrum
	memset( m_afTemp2, 0, ulBandWidth);
	for (int i = 0; i < DBF_NUM_ELEMENTS; i++ )
	{
		_EMScbPowerSpectr( &m_acMatrix[i*DBF_LOG19_SIZE], &m_afTemp1[0], ulBandWidth);
		emssbAdd2(m_afTemp1, m_afTemp2, (int)ulBandWidth );
	}

	// Find maximum carrier power over downlink bandwidth
	float fMaxPower = 0.0;
	ULONG index = 0;
	ULONG ulOffset = 10000;

	fMaxPower = _EMSsMaxExt( &m_afTemp2[ulOffset], ulBandWidth, &index);
	//ULONG ulOffset = 15000;
	//for( ULONG i = ulOffset; i < ulBandWidth-ulOffset; i++ )
	//for( ULONG i = ulOffset; i < ulOffset+100000; i++ )
	//{
	//	if ( m_afTemp2[i] > fMaxPower )
	//	{
	//		fMaxPower = m_afTemp2[i];
	//		index = i;
	//	}
	//}

	if ( !m_bEigenFlag )
	{
		// Assign phase coefficients from complex conjugate of strongest carrier signal
		for( ULONG i = 0; i < DBF_NUM_ELEMENTS; i++ )
		{
			m_acDBFBeamVectors[i].re =  m_acMatrix[i*DBF_LOG19_SIZE + index ].re;
			m_acDBFBeamVectors[i].im = -m_acMatrix[i*DBF_LOG19_SIZE + index ].im;
		}
	}
	*m_ulFreqIndex = index;
	fMaxPower   = 10*log10(fMaxPower);
	m_fMaxPower = fMaxPower;

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
		memcpy(&m_aTOAFOA.fEigenvalue[0], &EigenValues[0], DBF_NUM_ELEMENTS * sizeof(float) );
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

			   // Compute phases of eigenvectors and store
			   float fBeamReal;
			   float fBeamImag;
			   double dPhase;

			   for ( int ibeam = 0; ibeam < nNumBeams; ibeam++ )
			   {
				   for ( int ielement = 0; ielement < DBF_NUM_ELEMENTS; ielement++ )
				   {
					   fBeamReal	 = m_acDBFBeamVectors[ibeam*DBF_NUM_ELEMENTS + ielement].re;
					   fBeamImag	 = m_acDBFBeamVectors[ibeam*DBF_NUM_ELEMENTS + ielement].im;

					   dPhase = atan2( (double)fBeamReal , (double)fBeamImag ) * (360.0/c_dTwoPI);

					   m_aTOAFOA.fEigenvector[ibeam*DBF_NUM_ELEMENTS + ielement ] = (float) dPhase;
				   }
			   }

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
CDigitalBeamFormer::ApplyDBFBeamVectors( ULONG m_ulSatellites, bool bTimeFreqFlag, bool bBandwidthFlag)
{
	EMS_RESULT hr = EMS_FALSE;

	bool bBeaconCheck = false; // Check for Reference Beacon
	double dMean = 0;
	double dStdDev = 0;
	double dMean0 = 0;
	double dStdDev0 = 0;
	double dMaxValue = 0;
	ULONG ulMaxIndex = 0;
	float fScalefactor = 0;
	EMSCOMPLEX cScaleFactor;

	// Assuming downlink is centred at 150 kHz with bandwidth 100 kHz
	//DOUBLE dBinSize   = (float) DBF_LOG20_SIZE  / (float) DBF_SAMPLE_RATE;
	DOUBLE dBinSize = 0.5;
	ULONG ulBandWidth = (ULONG) (DBF_FREQ_BANDWIDTH * dBinSize);

	if ( m_acDBFBeamVectors && m_acMatrix )
	{
		if ( m_ulSatellites > MAX_BEAMS )
			m_ulSatellites = MAX_BEAMS;

		hr = EMS_OK;

		for ( int isat = 0; isat < m_ulSatellites; isat++ )
		{
			// Find 1st pass record with possible reference beacon
			if ( m_aPassSchedule.rec[isat].fBeaconElevation > 0 )
			{
				bBeaconCheck  = true;
				break;
			}
		}	

		for ( int isat = 0; isat < m_ulSatellites; isat++ )
		{
			memset( m_acTemp1, 0, sizeof(EMSCOMPLEX) * DBF_LOG19_SIZE );
			memset( m_acTemp3, 0, sizeof(EMSCOMPLEX) * DBF_LOG20_SIZE );

			// Note: The stored matrix is a downverted complex time series with same input sample rate
			for ( int ielem = 0; ielem < DBF_NUM_ELEMENTS; ielem++ )
			{
				// The complex time or frequency series must remain unchanged to allow multiple satellite outputs
				// Note: Phase correction applies the same to either time or frequency domain data
				memcpy( m_acTemp3, &m_acMatrix[ielem*DBF_LOG19_SIZE], DBF_LOG19_SIZE * sizeof(EMSCOMPLEX));
				emscbMpy1(m_acDBFBeamVectors[isat*DBF_NUM_ELEMENTS+ielem], m_acTemp3, DBF_LOG19_SIZE );
				emscbAdd2(m_acTemp3, m_acTemp1, DBF_LOG19_SIZE );
			}
			
			// Apply normalizing constant
			cScaleFactor.re = 1.0/31000000.0;
			cScaleFactor.im = 0.0;

			emscbMpy1(cScaleFactor,m_acTemp1,DBF_LOG19_SIZE);
			memset( m_acTemp3, 0, sizeof(EMSCOMPLEX) * DBF_LOG20_SIZE );
		
			if ( bTimeFreqFlag )
			{
				// Convert from time series to frequency domain
				emscFftNip( &m_acTemp1[0], m_acTemp3, DBF_LOG19, EMS_SPL_FWD );
			}
			else
			{
				// Keep frequency array
				memcpy( m_acTemp3, &m_acTemp1[0], DBF_LOG19_SIZE * sizeof(EMSCOMPLEX) );
			}

			// Compute maximum power and its frequency bin
			_EMScbPowerSpectr( &m_acTemp3[0], &m_afTemp1[0], DBF_LOG19_SIZE);
			m_dMaxPower = _EMSsMaxExt(&m_afTemp1[0], ulBandWidth, &m_ulMaxPowerIndex );
			
			// Determine TOA and FOA estimates for Eigenvector power spectrum
			//if ( bBeaconCheck )	SatelliteTOAFOA( isat );
			SatelliteTOAFOA( isat );

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
			for ( ULONG i = 0; i < DBF_LOG20_SIZE; i++ )
			{
				m_afTemp1[i] = m_acTemp2[i].re;
				m_afTemp2[i] = m_acTemp2[i].im;
			}

			ULONG ulCount = ULONG( (float)DBF_OUTPUT_SIZE * 1.25);

			// Normalize and convert into signed integer
			dStdDev0  = _EMSsMeanStdDev( m_afTemp2, ulCount, &dMean0 );
			dStdDev   = _EMSsMeanStdDev( m_afTemp1, ulCount, &dMean );

			_EMSsbNormalize(m_afTemp1, m_afTemp2, DBF_LOG20_SIZE, dMean, dStdDev);
			fScalefactor = 32766 / 6.0;
			_EMSsbMpy1( fScalefactor, m_afTemp2, DBF_LOG20_SIZE );


			ULONG j = 0;
			ULONG ulOutputSize = DBF_OUTPUT_SIZE;
			if ( bBandwidthFlag )
			{
				// Downsample to sample rate 200kHz
				ulOutputSize /= 2;
				for ( ULONG i = 0; i < DBF_LOG20_SIZE; i += 5 )
				{
					m_afTemp1[j++] = m_afTemp2[i];
 					m_afTemp1[j++] = m_afTemp2[i+2] * 0.5 + m_afTemp2[i+3] * 0.5;;
				}
			}
			else
			{
				// Downsample to sample rate 400kHz
				for ( ULONG i = 0; i < DBF_LOG20_SIZE; i += 5 )
				{
					m_afTemp1[j++] = m_afTemp2[i];
 					m_afTemp1[j++] = m_afTemp2[i+1] * 0.75 + m_afTemp2[i+2] * 0.25;
 					m_afTemp1[j++] = m_afTemp2[i+2] * 0.5 + m_afTemp2[i+3] * 0.5;;
  					m_afTemp1[j++] = m_afTemp2[i+3] * 0.25 + m_afTemp2[i+4] * 0.75;;
 				}
			}

			memset(&m_nBeam[isat][0], 0, ulOutputSize * sizeof(short));
			emssbFloatToInt(m_afTemp1, &m_nBeam[isat][0], ulOutputSize, 16, 0);

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
	// Note: Remove 1st 50 kHz given elements are centred at 150 kHz.
	// ulStart is the 50 kHz offset given the sample rate 500000.
	ULONG ulStart = DBF_LOG19_SIZE / 5;
	ULONG ulLength = DBF_LOG19_SIZE - ulStart;

	// Compute sample covariance over the 100 kHz L-Band downlink
	for( ULONG i = 0; i < DBF_NUM_ELEMENTS; i++ )
	{
		emscbConj2( &m_acMatrix[i*DBF_LOG19_SIZE+ulStart], &m_acTemp1[0], ulLength ); // 100 kHz

		for( ULONG j = i; j < DBF_NUM_ELEMENTS; j++)
		{
			m_acCovariance[i*DBF_NUM_ELEMENTS+j] = emscDotProd(&m_acTemp1[0], &m_acMatrix[j*DBF_LOG19_SIZE+ulStart], ulLength);
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


//BOOL 
//CDigitalBeamFormer::_BuildDBFSatsTrackingInfo( EMSCOMPLEX* acDBFBeamVectors)
//{
//	//call tracking function..
//		//read existing values
//
//		int i, j, k;
//
//		int CurrentSatIds [ MAX_BEAMS ];
//		memset( CurrentSatIds, 0, sizeof(int) * MAX_BEAMS );
//		for( int i = 0; i < m_ulSatellites; i++ )
//		{
//			CurrentSatIds[i] = m_aPassSchedule.rec[i].ulSatID;
//		}
//
//		//read from q
//		EMSCOMPLEX *prevDBFBeamVectors = m_qrefDBFBeamVectors.ReadFirst( ).dbfBeamVector;
//		int *prevSchedulerSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).schedulerSatIds;
//		int *prevPredSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
//		int *prevBeamIds = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
//		float *prevProbability = m_qrefDBFBeamVectors.ReadFirst( ).probability;
//		int	prevNumBeams = m_qrefDBFBeamVectors.ReadFirst( ).numBeams;
//		//end
//		
//		// Check if first time
//		if( !prevDBFBeamVectors && !prevBeamIds )
//		{
//			memset(m_iBeamIDs, 0, MAX_BEAMS*sizeof(int) );
//			for( i = 0; i < m_ulSatellites; i++ )
//			{
//				//first time so set default beam ids
//				m_iBeamIDs[i] = i+1;
//			}
//			DBFTrackingData obj;
//			memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEX) );
//			obj.dbfBeamVector = m_acDBFBeamVectors;
//			obj.predBeamIDs = m_iBeamIDs;
//			memcpy( m_iPredictedSATIDs, CurrentSatIds, MAX_BEAMS * sizeof(int) );
//			obj.predSatIDs = m_iPredictedSATIDs;
//			obj.probability = m_fProbability;
//			memcpy( m_iPrevPassSchedSATIDs, CurrentSatIds, sizeof(int) * MAX_BEAMS );
//			obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
//			obj.numBeams = m_ulSatellites;
//			m_qrefDBFBeamVectors.InsertAtFirst( obj );
//			return true;
//		}
//		
//		int newBeamIds[ MAX_BEAMS ];
//		memset( newBeamIds, 0, sizeof(int) * MAX_BEAMS );
//		int newPredSatIds[ MAX_BEAMS ];
//		memset( newPredSatIds, 0, sizeof(int) * MAX_BEAMS );
//
//		// Compute probabilities
//		EMSCOMPLEX cTemp1[NUM_CHANNELS];
//		EMSCOMPLEX cTemp;
//
//		// Find new or missing satellites
//		int iCount[MAX_BEAMS];
//		memset( iCount, 0, sizeof(int) * MAX_BEAMS );
//
//		int iMaxBeam = 0;
//		for ( i = 0; i  < m_ulSatellites; i++ )
//		{
//			for ( j = 0; j  < prevNumBeams; j++ )
//			{
//				if ( CurrentSatIds[i] == prevPredSatIDs[j] )
//				{
//					iCount[i] = j+1;
//					if ( iMaxBeam < prevBeamIds[j] ) iMaxBeam = prevBeamIds[j]+1;
//				}
//			}
//		}
//
//		// Best match to previous eigenvector
//		k = 0;
//		for ( i = 0; i  < m_ulSatellites; i++ )
//		{
//			// Check orthogonality
//			float fProb1[25];
//			for ( j = 0; j  < m_ulSatellites; j++ )
//			{
//				memset(&cTemp1[0], 0.0, NUM_CHANNELS * sizeof( EMSCOMPLEX ) );
//				emscbConj2( &m_acDBFBeamVectors[j * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS );
//				cTemp = emscDotProd( &m_acDBFBeamVectors[i * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS );
//				fProb1[k++] = sqrt(cTemp.re*cTemp.re + cTemp.im*cTemp.im ) / NUM_CHANNELS;
//			}
//
//			m_fProbability[i] = 0.0;
//			float fProb       = 0.0;
//
//
//			if ( iCount[i] > 0  ) // Matching satellite condition
//			{
//				for ( j = 0; j  < prevNumBeams; j++ )
//				{
//					memset(&cTemp1[0], 0.0, NUM_CHANNELS * sizeof( EMSCOMPLEX ) );
//					emscbConj2( &prevDBFBeamVectors[j * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS );
//					cTemp = emscDotProd( &m_acDBFBeamVectors[i * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS );
//					fProb = sqrt(cTemp.re*cTemp.re + cTemp.im*cTemp.im ) / NUM_CHANNELS;
//					if ( fProb > m_fProbability[i] )
//					{
//						m_fProbability[i] = fProb;
//						newBeamIds[i]    = prevBeamIds[j];
//						newPredSatIds[i] = prevPredSatIDs[j];
//					}
//				}
//			}
//			else
//			{
//				newPredSatIds[i] = CurrentSatIds[i];
//				newBeamIds[i]    = iMaxBeam;
//				iMaxBeam++;
//			}
//
//		}
//
//		//const double Tup = 0.6;
//		//const double Tlo = 0.45;
//		//INT nNumBeams = m_ulSatellites;
//		//int *newBeamIds = new int[ MAX_BEAMS ];
//		//memset( newBeamIds, 0, sizeof(int) * MAX_BEAMS );
//		//int *newPredSatIds = new int [ MAX_BEAMS ];
//		//memset( newPredSatIds, 0, sizeof(int) * MAX_BEAMS );
//
//
//		//objTrackSats.perform_dbf_beam_and_sat_tracking( prevDBFBeamVectors, prevNumBeams, acDBFBeamVectors, nNumBeams,
//		//												prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs, Tup, Tlo,
//		//												newBeamIds, newPredSatIds, m_fProbability );
//		memcpy( m_iBeamIDs, newBeamIds, sizeof(int) * MAX_BEAMS );														
//		memcpy( m_iPredictedSATIDs, newPredSatIds, MAX_BEAMS * sizeof(int) );
//		DBFTrackingData obj;
//		memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
//		obj.dbfBeamVector = m_acDBFBeamVectors;
//		obj.predBeamIDs = m_iBeamIDs;
//		obj.predSatIDs = m_iPredictedSATIDs;
//		obj.probability = m_fProbability;
//		memcpy( m_iPrevPassSchedSATIDs, &CurrentSatIds, sizeof(int) * MAX_BEAMS );
//		obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
//		obj.numBeams = m_ulSatellites;
//		//m_qrefDBFBeamVectors.InsertAtFirst( acDBFBeamVectors );
//		m_qrefDBFBeamVectors.InsertAtFirst( obj );
//		delete []newBeamIds;
//		delete []newPredSatIds;
//		return TRUE;
//}

///////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::ComputeChannelData( bool bTimeFreqFlag, bool bBandwidthFlag )
{
	ULONG  i, icell, jsample, index, ichunk;

	// Downconvert by 50 kHZ assuming downlink is centred at 150 kHz
	//DOUBLE dBinSize   = (float) DBF_LOG20_SIZE  / (float) DBF_SAMPLE_RATE;
	DOUBLE dBinSize = 0.5;
	ULONG ulOffset50  = (ULONG) (DBF_FREQ_OFFSET / dBinSize); // 50 kHz offset
	ULONG ulBandWidth = (ULONG) (DBF_FREQ_BANDWIDTH / dBinSize);
	
	if ( bBandwidthFlag ) ulOffset50 *= 2;
	ulOffset50 -= 144;

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

		
		// Assume 3*ulOffset50 < DBF_LOG19_SIZE
		memcpy(&m_acTemp2[0], &m_acTemp1[ulOffset50], (DBF_LOG19_SIZE-ulOffset50) * sizeof(EMSCOMPLEX)); 
			

		if ( bTimeFreqFlag )
		{
			// Convert to complex time series
			emscFftNip( &m_acTemp2[0], m_acTemp1, DBF_LOG19, EMS_SPL_INV );
			// Store downconverted time series for each channel (Note: The sample rate remains unchanged)
			memcpy(&m_acMatrix[icell*DBF_LOG19_SIZE], m_acTemp1, DBF_LOG19_SIZE * sizeof(EMSCOMPLEX));
		}
		else
		{
			// Store frequency domain data for each channel (Note: The sample rate remains unchanged)
			memcpy(&m_acMatrix[icell*DBF_LOG19_SIZE], m_acTemp2, DBF_LOG19_SIZE * sizeof(EMSCOMPLEX));
		}

	}

	// Compute the total mean and standard deviation

	m_dMeanADC   = 0.0;
	m_dStdDevADC = 0.0;
	for ( int i = 0; i < DBF_NUM_ELEMENTS; i++ )
	{
		m_dMeanADC +=  m_aMaintenance.dMean[i];
		m_dStdDevADC += m_aMaintenance.dStdDev[i];
	}
	m_dMeanADC   /= DBF_NUM_ELEMENTS;
	m_dStdDevADC /= DBF_NUM_ELEMENTS;

	return EMS_OK;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

int
CDigitalBeamFormer::_Power2( ULONG ulInput )
{
	// Assumes ulInput is positive
	int iPower2 = 0;
	while ( pow(2.0,iPower2) <=  ulInput ) iPower2 += 1;
	return iPower2;
}

///////////////////////////////////////////////////////////////////////////////////

char
CDigitalBeamFormer::_GetTimeNano( EMSTIME tm )
{
	
	CEMSTime oTime(tm);
	char cTime[256];
	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
		
	oTime.GetTime( &tmFields );
	float fSecond = (float) tmFields.nSecond + ((float)tmFields.lNanosecond) * 1e-9;
	sprintf(cTime,"%04d\%03d %02d:%02d:%09.6f",
		tmFields.nYear, tmFields.nJulianDay, tmFields.nHour, tmFields.nMinute, fSecond );

	return *cTime;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::ConvertComplex2Real( EMSCOMPLEX* cData, float* fData, ULONG ulNpts )
{
	// Assumes output array size is a power of 2 and greater or equal to twice the input array size
	
	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( cData  && fData && ulNpts )
	{
		int iPower2      = 0;
		ULONG ulMpts     = 1;
		ULONG ulMptsHalf = 0;

		double dMean1	= 0.0;
		double dMean2	= 0.0;
		double dStdDev1 = 0.0;
		double dStdDev2 = 0.0;

		while ( ulMpts <=  ulNpts )
		{
			ulMpts  *= 2;
			iPower2 += 1;
		}
		ulMptsHalf = (ULONG) (ulMpts/2);

		EMSCOMPLEX* cTemp;
		cTemp = new EMSCOMPLEX[ulMpts];

		float* fTemp1;
		fTemp1 = new float[ulMpts];
		float* fTemp2;
		fTemp2 = new float[ulMpts];

		memset( fTemp1, 0, sizeof(float) * ulMpts );
		memset( fTemp2, 0, sizeof(float) * ulMpts );
		memset( cTemp, 0, sizeof(EMSCOMPLEX) * ulMpts );


		memcpy( cTemp, &cData[0], ulNpts * sizeof(EMSCOMPLEX) );
		emscFft( &cTemp[0], iPower2-1, EMS_SPL_FWD );

		// Store the complex conjugate of the original FFT in resevse order
		cTemp[ 0 ].re = 0.0;
		cTemp[ 0 ].im = 0.0;
		cTemp[ ulMptsHalf ].re = 0.0;
		cTemp[ ulMptsHalf ].im = 0.0;

			for ( ULONG i = 1; i < DBF_LOG19_SIZE; i++ )
			{
				cTemp[ ulMptsHalf + i].re =  cTemp[ ulMptsHalf - i].re;
				cTemp[ ulMptsHalf + i].im = -cTemp[ ulMptsHalf - i].im;
			}
			emscFft( &cTemp[0], ulMpts, EMS_SPL_INV );
			
			// Extract the floating point time series
			// Note: The complex components are zero and the sample rate remains unchanged
			for ( ULONG i = 0; i < ulMpts; i++ )
			{
				fTemp1[i] = cTemp[i].re;
				fTemp2[i] = cTemp[i].im;
			}

			// Normalize and convert into signed integer
			dStdDev1  = _EMSsMeanStdDev( fTemp1, DBF_OUTPUT_SIZE, &dMean1 );
			dStdDev2  = _EMSsMeanStdDev( fTemp2, DBF_OUTPUT_SIZE, &dMean2 );

			_EMSsbNormalize(fTemp1, fData, DBF_OUTPUT_SIZE, dMean1, dStdDev1);

			delete [] cTemp;  cTemp = NULL;
			delete [] fTemp1; fTemp1 = NULL;
			delete [] fTemp2; fTemp2 = NULL;


			hr = EMS_OK;
			
		}
	
	return hr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::InitializeMemory( )
{
	EMS_RESULT hr = EMS_OK;

	try
	{

		//debug only
		//ULONG lSize0 =  DBF_MAX_CHANNELS*sizeof(float);
		//ULONG lSize1 =  DBF_LOG20_SIZE*sizeof(float);
		//ULONG lSize2 =  (DBF_LOG19_SIZE+1)*sizeof(EMSCOMPLEX);
		//ULONG lSize3 =  DBF_NUM_ELEMENTS*DBF_LOG19_SIZE*sizeof(EMSCOMPLEX);
		//ULONG lSize4 =  m_ulSamplesPerChannel*sizeof(float);
		//ULONG lSize5 =  COVARIANCE_SIZE*sizeof(EMSCOMPLEX);
		//

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
		memset( m_acDBFBeamVectors, 0, (DBF_NUM_ELEMENTS*DBF_MAX_SATELLITES)*sizeof(EMSCOMPLEX));

		memset( &m_aTOAFOA, 0, sizeof(EMSDBFTOAFOARECORD) );
	}
	catch( ... )
	{
		hr = EMS_NO_MEMORY;
	}
	return hr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::BiasEstimator( EMSTIME tm  )
{
	EMS_RESULT hr = EMS_OK;

	FILE*	lpBiasFile = NULL;
	char	szFileName[256];
	float	fPhase0[DBF_NUM_ELEMENTS];
	float	fPhase1[DBF_NUM_ELEMENTS];
	float	fPhase2[DBF_NUM_ELEMENTS];
	float	fPhase3[DBF_NUM_ELEMENTS];
	float	fPhase4[DBF_NUM_ELEMENTS];


	EMSCOMPLEX cTemp[DBF_NUM_ELEMENTS];
	
	EMSTIMEFIELDS tmFlds;
	CEMSTime oTM(tm);
	ULONG ulIndex;

	// Output results to temporary bias data files
	oTM.GetTime(&tmFlds);
	ULONG ulDaySec = tmFlds.nHour*3600 + tmFlds.nMinute*60 + tmFlds.nSecond;
	if ( m_bEigenFlag )
	{
		sprintf(szFileName,"%sDBF_Bias_%05d.bin", CDBFCollectorConfig::GetInstance().GetBiasEigenDir().c_str(), ulDaySec);
	}
	else
	{
		sprintf(szFileName,"%sDBF_Bias_%05d.bin", CDBFCollectorConfig::GetInstance().GetBiasSignalDir().c_str(), ulDaySec);
	}

	lpBiasFile = fopen(szFileName,"w+b");

	// Assume first beamvector is harmonic or probe
	memcpy(&cTemp[0], &m_acDBFBeamVectors[0], sizeof(cTemp) );
	float fAmplitude = 0.0;

	for ( int i = 0; i < DBF_NUM_ELEMENTS; i++ )
	{
		// Normalize Beam Vector and compute bias phase angles
		fAmplitude = sqrt( cTemp[i].re*cTemp[i].re + cTemp[i].im*cTemp[i].im );
		cTemp[i].re /= fAmplitude;
		cTemp[i].im /= fAmplitude;
		fPhase0[i] = atan2( (double) cTemp[i].im, (double) cTemp[i].re ) * c_dRadToDeg;
		fPhase3[i] = fAmplitude;
	}

	// Adjust predicted satellite phase angles by subtracting bias phase angles
	for (int isat = 0; isat < m_ulSatellites; isat++ )
	{
		ULONG ulIndex = isat*DBF_NUM_ELEMENTS;
		float f360Angle = 360.0;
		for ( int i = 0; i < DBF_NUM_ELEMENTS; i++ )
		{
			fPhase1[i] = fPhase0[i] - fPhase0[DBF_CENTRE_ELEMENT-1];
			fPhase2[i] = m_aPassSchedule.rec[isat].fPhase[i+1] - fPhase1[i];
			//fPhase2[i] = m_aPassSchedule.rec[isat].fPhase[i+1] + fPhase1[i];
			fPhase2[i] = fmod(fPhase2[i], f360Angle );

			if ( !m_bEigenFlag )
			{
				fPhase2[i] -= m_aDBFplate.emsDBFCells[i].fNearField;
				fPhase2[i] = fmod(fPhase2[i], f360Angle );
				m_acDBFBeamVectors[ulIndex+i].re = cos(fPhase2[i]*c_dDegToRad);
				m_acDBFBeamVectors[ulIndex+i].im = -sin(fPhase2[i]*c_dDegToRad);
			}
		}
		if( lpBiasFile != NULL && isat==0)
		{

			fwrite( &m_aPassSchedule.rec[isat], sizeof(EMSDBFPASSRECORD2), 1, lpBiasFile );
			ulIndex = ftell(lpBiasFile);

			fwrite( &fPhase1[0],  sizeof(float), 31, lpBiasFile );
			fwrite( &fPhase2[0],  sizeof(float), 31, lpBiasFile );
			fwrite( &fPhase3[0],  sizeof(float), 31, lpBiasFile );

			ulIndex = ftell(lpBiasFile);
			fwrite( &m_ulFreqIndex, sizeof(ULONG), 1, lpBiasFile );
			ulIndex = ftell(lpBiasFile);
			fwrite( &m_fMaxPower, sizeof(float), 1, lpBiasFile );
			ulIndex = ftell(lpBiasFile);
		}
	}
	flushall();
	fclose(lpBiasFile);
	lpBiasFile = NULL;

	return hr;
}


EMS_RESULT
CDigitalBeamFormer::TestDBFprocessor( int nProcess )
{

	EMS_RESULT hr = EMS_OK;

	FILE*	lpADCFile  = NULL;
	FILE*	lpPassFile = NULL;

	char	szFileDirectory[256];
	char	szFileName[256];
	int		nFiles, mFiles, iPass;
	ULONG	RawOffset[10];
	ULONG	lSize, lSize0, lSizeMax;

	EMSDBFPASSRECORD2 pPassRecord; 

	lSize = sizeof(ULONG);

	CEMSTime oTime;


	EMSTIMEFIELDS tmFields;

	//sprintf(szFileDirectory,"D:\\HGT\\TSi_DBF\\DBF_raw\\Galileo\\ADCraw\\");
	sprintf(szFileDirectory,"%s", CDBFCollectorConfig::GetInstance().GetRawDataDir().c_str());
	nFiles = DirectoryList(szFileDirectory,"*.bin");
	if ( nFiles == 0 )
	{
		hr = EMS_BAD_PARAM;
		printf("File Directory Error: %s\n",szFileDirectory);
		return hr;
	}

	//for ( int ifile = 0; ifile < nFiles; ifile++ )
	for ( int ifile = 0; ifile < 9; ifile++ )
	{

		lSizeMax = DBF_MAX_CHANNELS*DBF_SAMPLE_SIZE * sizeof(ULONG);
		
		//mFiles = DirectoryList(szFileDirectory,"*.bin");
		sprintf(szFileName,"%s%s",szFileDirectory,m_FileNames[ifile]);

		sprintf(szFileName,"%sAI32SSData000%1d.bin",szFileDirectory,ifile+1);
		lpADCFile = fopen(szFileName,"r+b");

		// obtain file size:
		fseek (lpADCFile , 0 , SEEK_END);
		lSize = ftell (lpADCFile);
		rewind (lpADCFile);

		fread(&RawOffset, 1, 40, lpADCFile );

		memset(m_asRawTimeSeries,0, lSizeMax );

		if ( lSize > lSizeMax + 40) lSize = lSizeMax;

		size_t st_freadCount = fread(m_asRawTimeSeries, 1, lSize, lpADCFile );

		fclose(lpADCFile);
		lpADCFile = NULL;

		m_timeActual = CEMSSystemClock::GetTime();
		oTime.SetTime( m_timeActual );
		oTime.GetTime( &tmFields );


		// Read Pass Schedule

		sprintf(szFileName, "%sEMSDBFPass-%d.bin", CDBFCollectorConfig::GetInstance().GetBinOutputDir().c_str(), tmFields.nHour );

		lpPassFile = fopen( szFileName, "rb" );

		if ( !lpPassFile )
		{
			hr = EMS_BAD_PARAM;
			printf("File Error: %s\n",szFileName);
			return hr;
		}
		else
		{
			// obtain file size:
			fseek (lpPassFile , 0 , SEEK_END);
			lSizeMax = ftell (lpPassFile);
			rewind (lpPassFile);

			iPass = 0;
			lSize = 0;
			m_ulSatellites = 0;
			int icount = 0;
			while ( lSize < lSizeMax )
			{
				lSize0 = fread( &pPassRecord,1,sizeof(EMSDBFPASSRECORD2),lpPassFile);

				if ( icount == 0 )
				{
					// Set date/hour to pass schedule data
					m_timeActual.intTime = pPassRecord.timestamp.intTime; 
					oTime.SetTime( m_timeActual );
					m_timeActual = oTime.AddSeconds( 10.0 );
					oTime.SetTime( m_timeActual );
				}
				icount++;
				lSize += lSize0;
				float fdTime = oTime.NanosecondsDifferent(pPassRecord.timestamp);
				fdTime       /= (float)1000000000;

				if (fabs(fdTime) < 1 &&  pPassRecord.ulSatID > 0)
				{
					m_ulSatellites++;
					memcpy(&m_aPassSchedule.rec[iPass++], &pPassRecord, sizeof(pPassRecord));
					printf("Rec %d, SatID %d (%d), Time Difference %8.5f sec\n", icount++, pPassRecord.ulSatID, m_ulSatellites, fdTime);
				}
			}
		}

		fclose(lpPassFile);
		lpPassFile = NULL;
		
		// Set arbitray time
		m_timeActual = oTime.AddSeconds(ifile*10);
		m_aMaintenance.timestamp.intTime = m_timeActual.intTime;
		
		printf("Input file - %s, Sats %d\n", szFileName, m_ulSatellites); 

		ProcessAll();
	}


	return hr;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int 
CDigitalBeamFormer::DirectoryList(string folder, string filetype)
{
	int i = 0;
	char cFileName[256];
    //string search_path = folder + "/*.*";
    string search_path = folder + filetype;
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if( (hFind != INVALID_HANDLE_VALUE) & (i < MAX_TEST_FILES)) { 
        do { 
            // read all (real) files in current folder
             if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
			 {
                int filenamelength = strlen(fd.cFileName);
				memcpy(cFileName, fd.cFileName,filenamelength) ;
				m_FileNames[i++] = cFileName;
			 }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    } 
    return i;  // return i equals number of files
}

//////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CDigitalBeamFormer::SatelliteIdentify( ULONG m_ulSatellites  )
{
	// Note: Pass schedule phase predictions include the 1st channel with the  1 PPS. 
	//       Therefore all 'real' phases are from 2 to 32 channels.
	
	EMS_RESULT hr = EMS_OK;
	
	EMSCOMPLEX PhaseBias[MAX_BEAMS][MAX_BEAMS][NUM_CHANNELS];
	float fBiasDotProd[MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*MAX_BEAMS];
	ULONG ulBiasIndex[MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*MAX_BEAMS];
	ULONG ulSatEig[MAX_BEAMS*MAX_BEAMS][2];

	EMSCOMPLEX cVect1[NUM_CHANNELS];
	EMSCOMPLEX cVect2[NUM_CHANNELS];
	float fVect1[NUM_CHANNELS];
	float fVect2[NUM_CHANNELS];
	EMSCOMPLEX cTemp1;
	EMSCOMPLEX cTemp2;
	float fMaxBias;
	float fAmplitude1;
	float fAmplitude2;
	
	int   nIndex;

	memset( &PhaseBias,    0, MAX_BEAMS*MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEX) );
	memset( &fBiasDotProd, 0, MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*sizeof(float) );
	memset( &ulBiasIndex,  0, MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*sizeof(ULONG) );
	memset( &ulSatEig,	   0, 2*MAX_BEAMS*MAX_BEAMS*sizeof(ULONG) );

	memset( m_iPredictedSATIDs, 0, MAX_BEAMS*sizeof(ULONG) );
	memset( m_fProbability,     0, MAX_BEAMS*sizeof(float) );
	memset( cVect1,				0, NUM_CHANNELS*sizeof(EMSCOMPLEX) );

	bool bAssigned[MAX_BEAMS] = {};

	int sat1, sat2, eig1, eig2, kindex;
	int i, j, k, m, n, nmax;
	m = 0;
	n = 0;

	nmax = MAX_BEAMS*MAX_BEAMS*MAX_BEAMS*MAX_BEAMS;


	// Generate all possible phase bias vectors
	for ( sat1 = 0; sat1 < m_ulSatellites; sat1++ ) // predicted satellite
	{
		
		for ( eig1 = 0; eig1 < m_ulSatellites; eig1++ ) // eigenvector
		{
			memset(&PhaseBias[sat1][eig1][0], 0, NUM_CHANNELS*sizeof(EMSCOMPLEX));
		    memcpy(&cVect1, &m_acDBFBeamVectors[eig1], NUM_CHANNELS*sizeof(EMSCOMPLEX));

			for ( k = 0; k < NUM_CHANNELS; k++ )
			{
				// Note: centre element is 23 starting at number 1 not zero
				cVect1[k].re -= cVect1[DBF_CENTRE_ELEMENT-1].re;
				cVect1[k].im -= cVect1[DBF_CENTRE_ELEMENT-1].im;
				cTemp1 = cVect1[k];
				//cTemp2.re = (float) m_aPassSchedule.rec[sat1].nPhaseReal[k+1];
				//cTemp2.im = (float) m_aPassSchedule.rec[sat1].nPhaseImag[k+1];
				cTemp2.re = cos(m_aPassSchedule.rec[sat1].fPhase[k+1]);
				cTemp2.im = sin(m_aPassSchedule.rec[sat1].fPhase[k+1]);

				fAmplitude1 = sqrt( cTemp1.re*cTemp1.re + cTemp1.im*cTemp1.im );
				fAmplitude2 = sqrt( cTemp2.re*cTemp2.re + cTemp2.im*cTemp2.im );

				if ( fAmplitude1 < 1e-6 ) fAmplitude1 = 1e-6;
				if ( fAmplitude2 < 1e-6 ) fAmplitude2 = 1e-6;

				PhaseBias[sat1][eig1][k].re = cTemp1.re/fAmplitude1 - cTemp2.re/fAmplitude2 ;
				PhaseBias[sat1][eig1][k].im = cTemp1.im/fAmplitude1 - cTemp2.im/fAmplitude2;
				
			}
		}
	}

	// Compute dot products of phase bias estimates
	 for ( sat1 = 0; sat1 < m_ulSatellites; sat1++ )
	 {
		 for ( eig1 = 0; eig1 < m_ulSatellites; eig1++ )
		 {
			 memcpy(&cVect1, &PhaseBias[sat1][eig1][0], NUM_CHANNELS*sizeof(EMSCOMPLEX));
			 
			for ( sat2 = 0; sat2 < m_ulSatellites; sat2++ )
			{
				if ( sat1 != sat2 )
				{
					for ( eig2 = 0; eig2 < m_ulSatellites; eig2++ )
					{
						if ( eig1 != eig2 )
						{
							memcpy(&cVect2, &PhaseBias[sat2][eig2][0], NUM_CHANNELS*sizeof(EMSCOMPLEX));
							emscbConj1(cVect2, NUM_CHANNELS);
							cTemp1 = emscDotProd( cVect1, cVect2, NUM_CHANNELS);
				 
							 // cosine of angle between two complex vectors
							 emscbMag(cVect1, fVect1, NUM_CHANNELS );
							 emscbMag(cVect2, fVect2, NUM_CHANNELS );
							 fAmplitude1 = 0.0;
							 fAmplitude2 = 0.0;
							 for ( m = 0; m < NUM_CHANNELS; m++ )
							 {
								 fAmplitude1 += fVect1[m];
								 fAmplitude2 += fVect2[m];
							 }
					
							 float fDotMag = sqrt( cTemp1.re * cTemp1.re + cTemp1.im * cTemp1.im );
							 fAmplitude1 = fDotMag / (fAmplitude1 * fAmplitude2 );
							 //if ( fAmplitude1 > 0.0 )
							 {
								fBiasDotProd[n] = fAmplitude1;
								ulBiasIndex[n] = sat1*1000 + eig1*100 + sat2*10 + eig2;
								n++;
								if ( n > nmax ) n = nmax;
							 }
						}	// ieg1, ieg2 if test
					}		// eig2 loop
				}			// sat1, sat2 if test
			 }				// sat2 loop
		 }					// eig1 loop
	 }						// sat1 loop

	 
	 for ( k = 0; k < m_ulSatellites; k++ )
	 {
		 fMaxBias = emssMaxExt( &fBiasDotProd[0], n, &nIndex);
		 sat1 = ulBiasIndex[nIndex]/1000;
		 eig1 = (ulBiasIndex[nIndex] - sat1*1000)/100;
		 sat2 = (ulBiasIndex[nIndex] - sat1*1000 - eig1*100)/10; 
		 eig2 = (ulBiasIndex[nIndex] - sat1*1000 - eig1*100 - sat2*10); 

		 if ( !bAssigned[eig1] )
		 {
			m_iPredictedSATIDs[eig1] = m_aPassSchedule.rec[sat1].ulSatID;
			m_fProbability[eig1]     = fMaxBias;
			bAssigned[eig1]          = true;
		 }
		 if ( !bAssigned[eig2] )
		 {
			m_iPredictedSATIDs[eig2] = m_aPassSchedule.rec[sat2].ulSatID;
			m_fProbability[eig2]     = fMaxBias;
			bAssigned[eig2]          = true;
		 }

		 printf("index %d, sat1 %d, eig1 %d, sat2 %d, eig2 %d, sateig1 %d, sateig2 %d, prob %f\n",
			 ulBiasIndex[nIndex], sat1, eig1, sat2, eig2, m_iPredictedSATIDs[eig1], m_iPredictedSATIDs[eig2], fMaxBias);
		 fBiasDotProd[nIndex]  = -1000.0;
	}

	// reorder eigenvectors to match predicted satellite IDs from Pass Schedule

	for ( sat1 = 0; sat1 < m_ulSatellites; sat1++ )
	{
		for ( sat2 = 0; sat2 < m_ulSatellites; sat2++ )
		{
			if ( m_iPredictedSATIDs[sat1] == m_aPassSchedule.rec[sat2].ulSatID )
			{
				memcpy ( cVect1, &m_acDBFBeamVectors[sat2], NUM_CHANNELS*sizeof(EMSCOMPLEX) );
				memcpy ( &m_acDBFBeamVectors[sat2], &m_acDBFBeamVectors[sat1], NUM_CHANNELS*sizeof(EMSCOMPLEX) );
				memcpy (  &m_acDBFBeamVectors[sat1], cVect1, NUM_CHANNELS*sizeof(EMSCOMPLEX) );

				fAmplitude1 = m_fProbability[sat2];
				m_fProbability[sat2] = m_fProbability[sat1];
				m_fProbability[sat1] = fAmplitude1;
			}
		}
	}



	FILE*	lpSatIdentityFile = NULL;
	char	szFileName[256];

	EMSTIME tx = CEMSSystemClock::GetTime();
	EMSTIMEFIELDS tmFlds;
	CEMSTime oTM(tx);

	oTM.GetTime(&tmFlds);
	ULONG ulHourSec = tmFlds.nHour*60*60 + tmFlds.nMinute*60 + tmFlds.nSecond;
				
	sprintf(szFileName,"%sDBF_SatID_%06d.bin", CDBFCollectorConfig::GetInstance().GetSatIDDir().c_str(), ulHourSec);

	lpSatIdentityFile = fopen(szFileName,"w+b");

	fwrite( &m_ulSatellites, sizeof(ULONG), 1, lpSatIdentityFile);
	kindex = ftell(lpSatIdentityFile);
	for (sat1 = 0; sat1 < m_ulSatellites; sat1++ )
	{
		fwrite( &m_aPassSchedule.rec[sat1].ulSatID, sizeof(ULONG), 1, lpSatIdentityFile);
		fwrite( &m_iPredictedSATIDs[sat1], sizeof(ULONG), 1, lpSatIdentityFile);
		fwrite( &m_fProbability[sat1], sizeof(float), 1, lpSatIdentityFile);
	}
	kindex = ftell(lpSatIdentityFile);

	for (sat1 = 0; sat1 < m_ulSatellites; sat1++ )
	{
		
		kindex = ftell(lpSatIdentityFile);

		for (eig1 = 0; eig1 < m_ulSatellites; eig1++ )
		{
			fwrite( &m_acDBFBeamVectors[eig1], sizeof(EMSCOMPLEX)*NUM_CHANNELS, 1, lpSatIdentityFile);
			fwrite( &PhaseBias[sat1][eig1][0], sizeof(EMSCOMPLEX)*NUM_CHANNELS, 1, lpSatIdentityFile);
		}
	}
	kindex = ftell(lpSatIdentityFile);
	fwrite( &n, sizeof(ULONG), 1, lpSatIdentityFile);

	if ( n> nmax ) n= nmax;
	for ( i = 0; i < n; i++ )
	{
		fwrite( &ulBiasIndex[i], sizeof(ULONG), 1, lpSatIdentityFile);
		fwrite( &fBiasDotProd[i], sizeof(float), 1, lpSatIdentityFile);
	}
	kindex = ftell(lpSatIdentityFile);

	flushall();
	fclose(lpSatIdentityFile);
	lpSatIdentityFile = NULL;
	
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
EMS_RESULT
CDigitalBeamFormer::InitializeTOAFOA( EMSTIME timestamp)
{
	return CToaFoaProcessor::InitializeTOAFOA(
		timestamp,
		m_ulSatellites,
		&m_aPassSchedule,
		m_afTemp1,
		m_acTemp1,
		m_acFFTBeacon,
		&m_aTOAFOA );
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool
CDigitalBeamFormer::ReferenceBeaconCheck(  int isat, ULONG* pulFreqIndex, float* pfCNR )
{
	bool bOK = false;
	float fMaxPower = 0.0;
	float fAvePower = 0.0;
	float fSigmaPower = 0.0;
	float fCNRthreshold  = 35.0; // temporary
	ULONG ulBeaconBandWidth = 5000;
	ULONG ulFreqOffset = 100000;
	ULONG ulFreqIndex = 0;
	ULONG ulFreqBandWidth = DBF_LOG19_SIZE - ulFreqOffset;

	// Find Beacon Power and check above CNR threshold
		
	// assumes filter with 200 kHz bandwidth
	fMaxPower = _EMSsMaxExt(&m_afTemp1[ulFreqOffset], ulFreqBandWidth, &ulFreqIndex);
	ulFreqIndex += ulFreqOffset;
	fAvePower = _EMSsMean(&m_afTemp1[ulFreqIndex + ulBeaconBandWidth], ulBeaconBandWidth/2 );
	*pfCNR = 10.0*log10(fMaxPower / fAvePower ) + 24.0;
	*pulFreqIndex = ulFreqIndex;
	if ( *pfCNR > fCNRthreshold ) bOK = true;

	return bOK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool
CDigitalBeamFormer::SatelliteTOAFOA(  int isat )
{
	return CToaFoaProcessor::SatelliteTOAFOA(
		isat,
		&m_aPassSchedule,
		m_afTemp1,
		m_acTemp1,
		m_acTemp2,
		m_acTemp3,
		m_acFFTBeacon,
		&m_aTOAFOA );
}


bool
CDigitalBeamFormer::IdentifyTOAFOA( EMSTIME tm, EMSCOMPLEX* acDBFBeamVectors )
{
	return CToaFoaProcessor::IdentifyTOAFOA(
		tm,
		m_ulSatellites,
		&m_aPassSchedule,
		m_qrefDBFBeamVectors,
		acDBFBeamVectors,
		m_iBeamIDs,
		m_iPredictedSATIDs,
		m_fProbability,
		m_iPrevPassSchedSATIDs,
		m_acDBFBeamVectors,
		&m_aTOAFOA );
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool
CDigitalBeamFormer::CheckBit(  char cHex[36], int iBit )
{
	bool bOK = false;
	int i1, i2, i3, iHex;

	i1 = iBit/4;
	i2 = ( iBit - i1*4 );
	i3 = 1 << i2;
	iHex = _Hex2Int( cHex[i1] );

	bOK = ( i3 & iHex );

	return bOK;
}

int
CDigitalBeamFormer::_Hex2Int(  char cHex )
{
	if ( cHex == 'A'  ) return 10;
	if ( cHex == 'B'  ) return 11;
	if ( cHex == 'C'  ) return 12;
	if ( cHex == 'D'  ) return 13;
	if ( cHex == 'E'  ) return 14;
	if ( cHex == 'F'  ) return 15;
	return ( (int)cHex - 48 );
}

EMS_RESULT
CDigitalBeamFormer::_CopyData(  float* fTest, float fValue, ULONG nCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( nCount > 0 )
	{
		for ( ULONG i = 0; i < nCount; i++ )
		{
			fTest[i] = fValue;
		}
	}
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
EMS_RESULT
CDigitalBeamFormer::SeparationAngle( ULONG m_ulSatellites )
{
	
	EMS_RESULT hr = EMS_OK;
	double dX1, dY1, dZ1 = 0.0;
	double dX2, dY2, dZ2 = 0.0;
	double dAzimuth, dElevation = 0.0;
	double dSAmin = 0.0;

	m_dSAmin[0] = 180.0;

	if ( m_ulSatellites > 1 )
	{
		for ( int i = 0; i < m_ulSatellites; i++ )
		{
			m_dSAmin[i] = 180.0;
			dAzimuth = m_aPassSchedule.rec[i].fPlateAzimuth;
			dElevation = m_aPassSchedule.rec[i].fPlateElevation;;
			// Compute unit vector pointing vectors
			dX1 = cos( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
			dY1 = sin( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
			dZ1 = cos( dElevation * c_dDegToRad );

			for ( int j = i+1; j < m_ulSatellites; j++ )
			{
				dAzimuth = m_aPassSchedule.rec[j].fPlateAzimuth;
				dElevation = m_aPassSchedule.rec[j].fPlateElevation;;
				// Compute unit vector pointing vectors
				dX2 = cos( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
				dY2 = sin( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
				dZ2 = cos( dElevation * c_dDegToRad );

				dSAmin = acos( dX1*dX2 + dY1*dY2 + dZ1*dZ2 ) * c_dRadToDeg;
				if ( m_dSAmin[i] > dSAmin ) m_dSAmin[i] = dSAmin;
			}
		}
	}
	return hr;
}