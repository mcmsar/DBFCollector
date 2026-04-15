/********************************************************************
*	Module:			DBFCalibration.cpp 
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
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

	0.0	2011/13/02		rcr		start

********************************************************************/
#include "sigproc.h"
#include "DBFCalibration.h"
#include "emsDBFtypes.h"
#include "emsconst.h"

/********************************************************************/


CDBFCalibration::CDBFCalibration()
{
	m_bInitialized = FALSE;

	m_aCalibData = new EMSDBFCALIBRECORD[MAX_CALIB_RECORDS];
	if ( m_aCalibData )
	{
		memset(m_aCalibData, 0, sizeof(EMSDBFCALIBRECORD) * MAX_CALIB_RECORDS );
	}
	m_ulCalibCount = 0;


}


CDBFCalibration::~CDBFCalibration( void )
{

	_Reset();

}

//---------------------------------------------------------------------------

void 
CDBFCalibration::_Reset( )
{
	try
	{
	
		if(m_aCalibData)
		{
			delete[] m_aCalibData;
			m_aCalibData = NULL;
		}

	}
	catch( ... )
	{
		throw;
	}
	

	if ( m_bInitialized )
	{
		m_bInitialized = FALSE;
	}
	return;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDBFCalibration::Initialize( ULONG ulChannels, ULONG ulCount )
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;

	m_ulChannels   = ulChannels; //DBF_MAX_CHANNELS;

	m_bInitialized = true;
			
	m_ulCalibCount = 0;

	hr = _GetCalibrationRecords( ulCount );

	return hr;
}

//---------------------------------------------------------------------------


EMS_RESULT
CDBFCalibration::_GetCalibrationRecords( ULONG ulCount )
{
	EMS_RESULT hr = EMS_OK;
	
	if ( ulCount > MAX_CALIB_RECORDS )
	{
		ulCount = MAX_CALIB_RECORDS;
	}
	
	TCHAR szFileName[256];
		
	lstrcpy( szFileName, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\CALIB\\EMSDBFCalib.bin") );

	FILE* lpCalibFileBIN = fopen( szFileName, "rb" );

	m_ulCalibCount = 0;

	ULONG ulByteCount = 0;
	ULONG ulMaxByteCount = 0;
	ULONG ulRecords = 0;

	ulByteCount    = fseek(lpCalibFileBIN, 0, SEEK_END);
	ulMaxByteCount = ftell(lpCalibFileBIN);
	ulByteCount    = fseek(lpCalibFileBIN, 0, SEEK_SET);

	ulRecords = ulMaxByteCount / sizeof( EMSDBFCALIBRECORD );

	// Read the most recent 'ulCount' records
	if ( ulCount < ulRecords )
	{
		ulByteCount = fseek(lpCalibFileBIN, ( ulRecords - ulCount ) * sizeof( EMSDBFCALIBRECORD ), SEEK_SET);
	}
	

	while ( ( ulByteCount < ulMaxByteCount ) && ( m_ulCalibCount < ulCount ) ) 
	{
			
		memset( &m_aCalibData[m_ulCalibCount], 0, sizeof(EMSDBFCALIBRECORD) );
		ULONG ulSize = fread( &m_aCalibData[m_ulCalibCount],1,sizeof(EMSDBFCALIBRECORD),lpCalibFileBIN);
		
		ulByteCount = ftell(lpCalibFileBIN);

		m_ulCalibCount++;

	}

	fclose( lpCalibFileBIN );
	lpCalibFileBIN = NULL;

	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDBFCalibration::_GetCalibrationCoefficients( void )
{
	EMS_RESULT hr = EMS_OK;

	TCHAR szFileName[256];
		
	lstrcpy( szFileName, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\CALIB\\EMSDBFCalib.csv") );

	FILE* lpCalibFileCSV = fopen( szFileName, "at" );

	memset( m_acCalibCoeff, 0, sizeof( EMSCOMPLEX ) * DBF_MAX_CHANNELS );

	double dAngleTheoretical = 0.0;
	double dAngleMeasurement = 0.0;

	float fAngleMean   = 0.0;
	float fAngleStdDev = 0.0;
	float fMagMean     = 0.0;
	float fMagStdDev   = 0.0;
	float fCalibAngle  = 0.0;

	float *fDiffAngle = new float [ m_ulCalibCount ];
	float *fMag       = new float [ m_ulCalibCount ];

	for ( ULONG ichan = 0; ichan < m_ulChannels; ichan++ )
	{
		fCalibAngle  = 0.0;
		fAngleMean   = 0.0;
		fAngleStdDev = 0.0;

		for ( ULONG irec = 0; irec < m_ulCalibCount; irec++ )
		{
			
			dAngleTheoretical = atan2( (double) m_aCalibData[irec].Pass.nPhaseReal[ichan],
									   (double) m_aCalibData[irec].Pass.nPhaseImag[ichan] );
			dAngleMeasurement = atan2( (double) m_aCalibData[irec].nCalibPhaseReal[ichan], 
									   (double) m_aCalibData[irec].nCalibPhaseImag[ichan] );
			fDiffAngle[irec]  = (float)fmod( (dAngleMeasurement - dAngleTheoretical)* c_dRadToDeg + 360.0, 360.0 );

			if ( fDiffAngle[irec] > 180.0 ) fDiffAngle[irec] -= 180.0;

			fMag[irec]  = (float) m_aCalibData[irec].nCalibPhaseReal[ichan] * (float) m_aCalibData[irec].nCalibPhaseReal[ichan];
			fMag[irec] += (float) m_aCalibData[irec].Pass.nPhaseImag[ichan] * (float) m_aCalibData[irec].Pass.nPhaseImag[ichan];
			fMag[irec]  = (float) sqrt( fMag[irec] );

		}

		fAngleMean   = emssMean( fDiffAngle, m_ulCalibCount );
		fAngleStdDev = emssStdDev( fDiffAngle, m_ulCalibCount );
		
		fMagMean   = emssMean( fMag, m_ulCalibCount );
		fMagStdDev = emssStdDev( fMag, m_ulCalibCount );

		fprintf(lpCalibFileCSV, "%02d, %05d, %10.5f, %10.5f, %10.5f, %10.5f\n",
			ichan, m_ulCalibCount, fAngleMean, fAngleStdDev, fMagMean, fMagStdDev );


	}

	if ( lpCalibFileCSV )
	{
		fclose( lpCalibFileCSV );
		lpCalibFileCSV = NULL;
	}

	if ( fDiffAngle )
	{
		delete [] fDiffAngle;
		fDiffAngle = NULL;
	}

	if ( fMag )
	{
		delete [] fMag;
		fMag = NULL;
	}

	return hr;
}

