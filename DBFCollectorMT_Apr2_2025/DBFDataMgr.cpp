/********************************************************************
*	Module:			DBFDataMgr.cpp 
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

	0.0	2011/01/21		rcr		start

********************************************************************/
#pragma warning(disable : 4786)

#include "DBFCollectorConfig.h"
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include <io.h>

#include "emsclock.h"
#include "emsconst.h"
//#include "emsDBF.h"
#include "emsDBFtypes2.h"
#include "emsDBFDataMgr.h"
#include "configurationaccessor.h"
#include <emsdomnode.h>
#include "emsencod.h"
#include "emsexcpt.h"
#include "convutility.h"

/********************************************************************/



/********************************************************************/

CEMSDBFDataMgr::CEMSDBFDataMgr(): m_uiPassSchedIndx( 0 ), m_oConstellationType( UNKNOWN )
{
	m_aPassSchedule = new EMSDBFPASSRECORD2[MAX_SCHEDULE_RECORDS];
	if ( m_aPassSchedule )
	{
		memset( m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORD2) * MAX_SCHEDULE_RECORDS );
	}
	else
	{
		// memory exception
	}

	m_aHourPassSchedule = new EMSDBFPASSRECORDS2[MAX_SCHEDULE_RECORDS_HOUR];
	if ( m_aHourPassSchedule )
	{
		memset( m_aHourPassSchedule, 0, sizeof(EMSDBFPASSRECORDS2) * MAX_SCHEDULE_RECORDS_HOUR );
	}
	else
	{
		// memory exception
	}

	m_lpPassFileBIN  = NULL;
	m_lpPassFileCSV  = NULL;
	memset(&m_aDBFplate, 0, sizeof(EMSDBFARRAY));
	m_ulRecordCount     = 0;
	m_ulLastRecord      = 0;
	m_TimeStart.intTime = 0;
	m_TimeEnd.intTime   = 0;
	memset(m_cFilePath,        0, sizeof(m_cFilePath));
	memset(&m_aPassScheduleNow, 0, sizeof(m_aPassScheduleNow));
}


CEMSDBFDataMgr::~CEMSDBFDataMgr()
{
	Reset();
}

/********************************************************************/

void 
CEMSDBFDataMgr::Reset()
{
	try
	{
	
		if ( m_lpPassFileBIN )
		{
			fclose( m_lpPassFileBIN );
			m_lpPassFileBIN = NULL;
		}

		if ( m_lpPassFileCSV )
		{
			fclose( m_lpPassFileCSV );
			m_lpPassFileCSV = NULL;
		}

		if(m_aPassSchedule)
		{
			delete[] m_aPassSchedule;
			m_aPassSchedule = NULL;
		}

		if(m_aHourPassSchedule)
		{
			delete[] m_aHourPassSchedule;
			m_aHourPassSchedule = NULL;
		}
	}
	catch( ... )
	{
		throw;
	}
	
}

/********************************************************************/

EMS_RESULT
CEMSDBFDataMgr::Initialize( int nPlateNumber )
{

	EMS_RESULT hr = EMS_BAD_PARAM;
	// Input Data Files
	std::wstring wsConfigDir = CDBFCollectorConfig::GetInstance().GetConfigDirW();
	const wchar_t* cDir = wsConfigDir.c_str();
	wchar_t* cPlateFile = L"DBFPlate_";
    wchar_t  wszFileName[256];
	
	memset(wszFileName, 0, sizeof(wszFileName) );

	wsprintfW( wszFileName, L"%s%s%02d.xml", cDir, cPlateFile, nPlateNumber );

	//hr = ReadDBFPlateXML( wszFileName );

	// Establish Pass Schedule data files and parameters

//	lstrcpy( m_cFilePath, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\") );
	lstrcpy( m_cFilePath, CDBFCollectorConfig::GetInstance().GetPassDataDir().c_str() );
	//lstrcpy( m_cFilePath, TEXT("\\\\1.1.1.200\\C$\\HGT\\DBFPassData\\") );
	
	//snl
	//lstrcpy( m_cFilePath, TEXT("Z:") );
	//lstrcpy( m_cFilePath, TEXT("c:") );


	CEMSSystemClock     oTime;
	m_TimeStart = oTime.GetTime();
	m_TimeEnd.intTime = 0;

	m_ulRecordCount = 0;
	m_ulLastRecord  = 0;

	hr = EMS_OK;

	//initialize polarization/freq class
	m_oConstellationMgr.Initialize();
	return hr;
}

/********************************************************************/

//EMS_RESULT
//CEMSDBFDataMgr::Initialize( const wchar_t* cwsPlateConfigFile )
//{
//
//	EMS_RESULT hr = EMS_BAD_PARAM;
//	
//	if( cwsPlateConfigFile )
//	{
//		// Input Data Files
//		hr = ReadDBFPlateXML( cwsPlateConfigFile );
//		
//		/// Establish Pass Schedule data files and parameters
//
//	//	lstrcpy( m_cFilePath, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\") );
//		//lstrcpy( m_cFilePath, TEXT("Z:") );
//		lstrcpy( m_cFilePath, TEXT("C:\\HGT\\DBFPassData\\") );
//		//lstrcpy( m_cFilePath, TEXT("\\\\1.1.1.200\\C$\\HGT\\DBFPassData\\") );
//
//
//
//		CEMSSystemClock     oTime;
//		m_TimeStart = oTime.GetTime();
//		m_TimeEnd.intTime = 0;
//
//		m_ulRecordCount = 0;
//		m_ulLastRecord  = 0;
//
//		hr = EMS_OK;
//	}
//	return hr;
//}

/********************************************************************/

EMS_RESULT
CEMSDBFDataMgr::WritePassSchedule( EMSDBFPASSRECORD2 PassRecord, bool bTestSun )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( &PassRecord )
	{
		CEMSTime  oTime = PassRecord.timestamp;
		EMSTIMEFIELDS tmFields;
		oTime.GetTime(&tmFields);
		int nPassHour = tmFields.nHour;

		EMSTIMEFIELDS tmFieldsFile;
		oTime = m_TimeEnd;
		oTime.GetTime(&tmFieldsFile);
		int nFileHour = tmFieldsFile.nHour;

		if ( !( nFileHour == nPassHour ) || !( m_lpPassFileBIN ) )
		{
			TCHAR szFileName[256];
			TCHAR szFileSpec[256];

			if ( m_lpPassFileBIN )
			{
				fclose( m_lpPassFileBIN );
				m_lpPassFileBIN = NULL;
			}

			if ( !m_lpPassFileBIN )
			{
				_stprintf( szFileName, TEXT( "\\BIN\\EMSDBFPass-%ld.bin" ), nPassHour );

				lstrcpy( szFileSpec, m_cFilePath );
				lstrcat( szFileSpec, szFileName ); 

				m_lpPassFileBIN = fopen( szFileSpec, "wb" );

				m_TimeStart.intTime = PassRecord.timestamp.intTime;
				m_TimeEnd.intTime   = PassRecord.timestamp.intTime;

				m_ulRecordCount = 0;
				m_ulLastRecord  = 0;

			}
			
			if ( m_lpPassFileCSV )
			{
				fclose( m_lpPassFileCSV );
				m_lpPassFileCSV = NULL;
			}

			if ( !m_lpPassFileCSV )
			{
				_stprintf( szFileName, TEXT( "\\CSV\\EMSDBFPass-%ld.csv" ), nPassHour );

				lstrcpy( szFileSpec, m_cFilePath );
				lstrcat( szFileSpec, szFileName ); 

				m_lpPassFileCSV = fopen( szFileSpec, "wt" );
			}

		}

		if ( m_lpPassFileBIN )
		{
			// Write binary Pass Record
			fwrite( &PassRecord, sizeof( EMSDBFPASSRECORD2 ), 1, m_lpPassFileBIN );

			hr = EMS_OK;

		}

		if ( m_lpPassFileCSV )
		{

			// Write CSV Pass Record
			fprintf(m_lpPassFileCSV, "%04d/%02d/%02d,%02d:%02d:%02d,",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond );

			fprintf(m_lpPassFileCSV, "%I64d,%d,%d,%d,%d,%d, %f,%f,%f,%f,",
				PassRecord.timestamp.intTime,
				PassRecord.ulLutID,
				PassRecord.wPlateID,
				PassRecord.wProcessID,
				PassRecord.wAntennaID,
				PassRecord.ulSatID,
				PassRecord.fAzimuth,
				PassRecord.fElevation,
				PassRecord.fPlateAzimuth,
				PassRecord.fPlateElevation );
			
			//for ( ULONG l = 0; l < m_aDBFplate.wCellNumber + 1 ; l++ )
			//{
			//	//double dPang = atan2( (double)PassRecord.nPhaseReal[l], (double)PassRecord.nPhaseImag[l] );
			//// Zeinab's change
			//	double dPang = atan2(  (double)PassRecord.nPhaseImag[l] , (double)PassRecord.nPhaseReal[l]);
			//	if ( dPang < 0.0 ) dPang += c_dTwoPI;
			//	fprintf(m_lpPassFileCSV, "%f,", dPang * c_dRadToDeg );
			//}

			fprintf(m_lpPassFileCSV, "\n" );
			//snl
			fflush( m_lpPassFileCSV );

		}

		if ( bTestSun && ( PassRecord.ulSatID == 999 ) )
		{
			FILE* lpSun = fopen( CDBFCollectorConfig::GetInstance().GetSunAzElFile().c_str(), "at" );
			fprintf(lpSun, "%04d/%02d/%02d,%02d:%02d:%02d,%10.3f,%10.3f\n",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond,
				PassRecord.fAzimuth,
				PassRecord.fElevation );
			fclose( lpSun );
			lpSun = NULL;
		}


	}


	return hr;
}


EMS_RESULT
CEMSDBFDataMgr::WritePassSchedule_Debug( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( aAzEls && pulActual && *pulActual )
	{
		if ( m_lpPassFileCSV )
		{
			fclose( m_lpPassFileCSV );
			m_lpPassFileCSV = NULL;
		}

		if ( !m_lpPassFileCSV )
		{
			TCHAR szFileName[256];
			_stprintf( szFileName, TEXT( "%s" ), CDBFCollectorConfig::GetInstance().GetNullTestFile().c_str() );
			m_lpPassFileCSV = fopen( szFileName, "wt" );
		}

		if ( m_lpPassFileCSV )
		{

			for( int i = 0; i < (*pulActual); i++ )
			{
				fprintf(m_lpPassFileCSV, "%d,%f,%f",
					aAzEls[i].ulSatID, aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );
				for( int j = 0; j < 64; j++ )
				{
					fprintf(m_lpPassFileCSV, ",%f,%f",
						aAzEls[i].acmplxPhase[j].re, aAzEls[i].acmplxPhase[j].im );
				}

				fprintf(m_lpPassFileCSV, "\n" );
			}
			//snl
			fflush( m_lpPassFileCSV );

		}

	}


	return hr;
}

/********************************************************************/

/*
EMS_RESULT
CEMSDBFDataMgr::ReadPassSchedule( EMSTIME tm )
{
	EMS_RESULT hr = EMS_BAD_PARAM;


	if ( m_lpPassFileBIN )
	{
		fclose( m_lpPassFileBIN );
		m_lpPassFileBIN = NULL;
	}

	if ( !m_lpPassFileBIN )
	{
		TCHAR szFileName[256];
		TCHAR szFileSpec[256];
		
		CEMSTime  oTime = tm;
		EMSTIMEFIELDS tmFields;
		oTime.GetTime(&tmFields);
		int nPassHour = tmFields.nHour;

		_stprintf( szFileName, TEXT( "\\BIN\\EMSDBFPass-%ld.bin" ), nPassHour );

		lstrcpy( szFileSpec, m_cFilePath );
		lstrcat( szFileSpec, szFileName ); 

		m_lpPassFileBIN = fopen( szFileSpec, "rb" );

		if ( m_lpPassFileBIN )
		{

			m_ulRecordCount = 0;
			m_ulLastRecord  = 0;

			ULONG ulMaxByteCount = fseek(m_lpPassFileBIN, 0, SEEK_END);

			ulMaxByteCount       = ftell(m_lpPassFileBIN);
			ULONG ulByteCount    = fseek(m_lpPassFileBIN, 0, SEEK_SET);

			ULONG ulRecords = ulMaxByteCount / 240;
			
			while ( ( ulByteCount < ulMaxByteCount ) && ( m_ulRecordCount < MAX_SCHEDULE_RECORDS ) ) 
			{
				
				memset( &m_aPassSchedule[m_ulRecordCount], 0, sizeof(EMSDBFPASSRECORD) );
				ULONG ulSize = fread( &m_aPassSchedule[m_ulRecordCount],1,sizeof(EMSDBFPASSRECORD),m_lpPassFileBIN);
				
				ulByteCount = ftell(m_lpPassFileBIN);

				m_ulRecordCount++;

			}

			m_TimeStart = m_aPassSchedule[0].timestamp;
			m_TimeEnd   = m_aPassSchedule[m_ulRecordCount-1].timestamp;

			fclose( m_lpPassFileBIN );
			m_lpPassFileBIN = NULL;

			hr = EMS_OK;
		}

	}

	return hr;

}*/

EMS_RESULT
CEMSDBFDataMgr::ReadPassSchedule( EMSTIME tm )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( m_lpPassFileBIN )
	{
		fclose( m_lpPassFileBIN );
		m_lpPassFileBIN = NULL;
	}

	if ( !m_lpPassFileBIN && m_aHourPassSchedule )
	{
		TCHAR szFileName[256];
		TCHAR szFileSpec[256];
		
		CEMSTime  oTime = tm;
		EMSTIMEFIELDS tmFields;
		oTime.GetTime(&tmFields);
		int nPassHour = tmFields.nHour;

		EMSDBFPASSRECORD2 emsPassRec = {};

		memset( m_aHourPassSchedule, 0, sizeof(EMSDBFPASSRECORDS2) * MAX_SCHEDULE_RECORDS_HOUR );
		m_ulRecordCount = 0;

		//_stprintf( szFileName, TEXT( "\\BIN\\EMSDBFPass-%ld.bin" ), nPassHour );
		_stprintf( szFileName, TEXT( "\\BIN\\TSIDBFPass-%ld.bin" ), nPassHour );

		lstrcpy( szFileSpec, m_cFilePath );
		lstrcat( szFileSpec, szFileName );

		m_lpPassFileBIN = fopen( szFileSpec, "rb" );

		if ( m_lpPassFileBIN )
		{
			m_ulRecordCount = 0;
			m_ulLastRecord  = 0;

			ULONG ulMaxByteCount = fseek(m_lpPassFileBIN, 0, SEEK_END);

			ulMaxByteCount       = ftell(m_lpPassFileBIN);
			ULONG ulByteCount    = fseek(m_lpPassFileBIN, 0, SEEK_SET);

			ULONG ulRecords = ulMaxByteCount / sizeof(EMSDBFPASSRECORD2);

			bool bFirstRecord = true;
			ULONG ulRecCount = 0;
			
			while ( ( ulByteCount < ulMaxByteCount ) && ( ulRecCount < MAX_SCHEDULE_RECORDS ) ) 
			{
				
				memset( &emsPassRec, 0, sizeof(EMSDBFPASSRECORD2) );
				ULONG ulSize = fread( &emsPassRec,1,sizeof(EMSDBFPASSRECORD2),m_lpPassFileBIN);

				if( ulSize == sizeof(EMSDBFPASSRECORD2) )
				{
					if( bFirstRecord )
					{
						bFirstRecord = false;
						m_TimeStart = emsPassRec.timestamp;
					}

					// Compute predicted phase
					//if ( &m_aDBFplate > 0 )
					//	hr = _PhaseCorrection( &emsPassRec );

					_AddPassRecord( emsPassRec );
					ulRecCount++;
				}
				
				ulByteCount = ftell(m_lpPassFileBIN);
			}

			m_TimeEnd   = emsPassRec.timestamp;

			fclose( m_lpPassFileBIN );
			m_lpPassFileBIN = NULL;

			INT64 lDeltaT = (INT64)(( m_TimeEnd.intTime - m_TimeStart.intTime ) * 1e-9);
			
			if( lDeltaT > 0 )
			{
				m_ulRecordCount = lDeltaT;
			}

			hr = EMS_OK;
		}
	}

	return hr;
}

void 
CEMSDBFDataMgr::_AddPassRecord( EMSDBFPASSRECORD2& dbfPassRec )
{
//	m_ulRecordCount++;
	INT64 lDeltaT = (INT64)(( dbfPassRec.timestamp.intTime - m_TimeStart.intTime ) * 1e-9);

	if( lDeltaT >= 0 && lDeltaT < MAX_SCHEDULE_RECORDS_HOUR)
	{
		int i = 0;
		while( (m_aHourPassSchedule[lDeltaT].rec[i].timestamp.intTime != 0) && i < DBF_MAX_SATELLITES )
		{
			i++;
		}

		if( i < DBF_MAX_SATELLITES )
		{
			m_aHourPassSchedule[lDeltaT].rec[i] = dbfPassRec;
		}
		else
		{
			// error ignore it.
		}
	}
	else
	{
		//error
	}
}

EMSCONSTELLATIONTYPE 
CEMSDBFDataMgr::_GetConstellation( UINT satID)
{
	EMSCONSTELLATIONTYPE oConstellationType;
	if (satID <= 199 ) // leo
	{
		oConstellationType = LEO;
	}
	else if( satID > 199 && satID < 300 ) //geo
	{
		oConstellationType = GEO;
	}
	else if( satID > 300 && satID < 400 )	//S Band
	{
		oConstellationType = GPS;
	}
	else if ( satID > 400 && satID < 500 )
	{
		oConstellationType = GAL;
	}
	else if ( satID > 500 && satID < 600 )
	{
		oConstellationType = GLONASS;
	}
	else if ( satID > 600 && satID < 700 )
	{
		oConstellationType = BEIDOU;
	}
	else
	{
		//default
		oConstellationType = LEO;

		//throw;
	}
	return oConstellationType;
}

BOOL	
CEMSDBFDataMgr::_SetPolarization( UINT uiSatID )
{
	BOOL bSuccess = FALSE;
	//std::cout<< "snl test..return false " << std::endl;
	//return bSuccess;
	////snl test..return false

	if( uiSatID )
	{
		EMSCONSTELLATIONTYPE constellationType = _GetConstellation( uiSatID );
		//if( m_oConstellationType >= 0 )
		if( constellationType >= 0 )
		{
			if( m_oConstellationType != constellationType )
			{
				//printf("Setting polarization to %d for satid %d", constellationType, uiSatID );
				std::cout << "Setting polarization to " << constellationType << " for satid: " << uiSatID << std::endl;
				m_oConstellationMgr.SetSatelliteConstellation( constellationType );
				m_oConstellationType = constellationType;
			}
		}
	}
	return bSuccess;

}

/********************************************************************/
EMSDBFPASSRECORDS2
CEMSDBFDataMgr::GetPassSchedule( EMSTIME tm )
{
	memset( &m_aPassScheduleNow, 0, sizeof( EMSDBFPASSRECORDS2 ) );
	INT64 utime =  ( (INT64) ( tm.intTime * 1e-9 ) ) * 1e9 ;

	// Correction to align pass schedule with buffer time
	utime -=1e9;
	if ( ( utime+1e9 > m_TimeStart.intTime ) &&
		 ( utime+1e9 < m_TimeEnd.intTime ) &&
		 ( m_ulRecordCount > 0 ) )

	/*if ( ( tm.intTime > m_TimeStart.intTime ) &&
		 ( tm.intTime < m_TimeEnd.intTime ) &&
		 ( m_ulRecordCount > 0 ) )*/
	{
		//snl test
		ULONG i  = 0;
		if( m_uiPassSchedIndx > 20 )
		{
			i = m_uiPassSchedIndx - 20;
		}
		int iTestCntr = 0;
		BOOL bFound = FALSE;
 		for( /*ULONG i  = 0*/; i < MAX_SCHEDULE_RECORDS_HOUR && !bFound; i++,++iTestCntr )
		{
			if( m_aHourPassSchedule[i].rec[0].timestamp.intTime == utime )
			{
				m_aPassScheduleNow = m_aHourPassSchedule[i];
				bFound = TRUE;
				m_uiPassSchedIndx = i;

			}
		}
		//m_uiPassSchedIndx = i;

		if( bFound == FALSE )
		{
			printf("\nError: Pass Schedule not found..lets try again..");
			for( ULONG j  = 0; j < m_uiPassSchedIndx && !bFound; j++)
			{
				if( m_aHourPassSchedule[j].rec[0].timestamp.intTime == utime )
				{
					m_aPassScheduleNow = m_aHourPassSchedule[j];
					bFound = TRUE;
				}
			}
		}
		//INT64 lDeltaT = (INT64)(( tm.intTime - m_TimeStart.intTime ) * 1e-9);

		//if( (lDeltaT >= 0) && (lDeltaT <= m_ulRecordCount) )
		//{
		//	m_aPassScheduleNow = m_aHourPassSchedule[lDeltaT];
		//}
		//else
		//{
		//	// not supposed to happen.
		//}
	}
	else
	{
		// skip it.
		ReadPassSchedule( tm );
		m_uiPassSchedIndx = 0;
	}
	//check if constellation has changed
	ULONG ulSatID = m_aPassScheduleNow.rec[0].ulSatID;
	_SetPolarization( ulSatID );
	return m_aPassScheduleNow;
}


//EMSDBFPASSRECORDS
//CEMSDBFDataMgr::GetPassSchedule( EMSTIME tm )
//{
//	memset( &m_aPassScheduleNow, 0, sizeof( EMSDBFPASSRECORDS ) );
//	INT64 utime =  ( (INT64) ( tm.intTime * 1e-9 ) ) * 1e9 ;
//
//	if ( ( utime >= m_TimeStart.intTime ) &&
//		 ( utime <= m_TimeEnd.intTime ) &&
//		 ( m_ulRecordCount > 0 ) )
//
//	/*if ( ( tm.intTime > m_TimeStart.intTime ) &&
//		 ( tm.intTime < m_TimeEnd.intTime ) &&
//		 ( m_ulRecordCount > 0 ) )*/
//	{
//
//		for( ULONG i  = 0; i < MAX_SCHEDULE_RECORDS_HOUR; i++ )
//		{
//			if( m_aHourPassSchedule[i].rec[0].timestamp.intTime == utime )
//			{
//				m_aPassScheduleNow = m_aHourPassSchedule[i];
//				break;
//			}
//		}
//		//save i as data member, next time start from that i or go back 15 secs
//		//new data member = i -15sec ( check if < 0 ).
//		//if utime > m_aHourPassSchedule[i].rec[0].timestamp.intTime ), do it
//
//		//INT64 lDeltaT = (INT64)(( tm.intTime - m_TimeStart.intTime ) * 1e-9);
//
//		//if( (lDeltaT >= 0) && (lDeltaT <= m_ulRecordCount) )
//		//{
//		//	m_aPassScheduleNow = m_aHourPassSchedule[lDeltaT];
//		//}
//		//else
//		//{
//		//	// not supposed to happen.
//		//}
//	}
//	else
//	{
//		// skip it.
//		ReadPassSchedule( tm );
//	}
//
//	return m_aPassScheduleNow;
//}

/*
EMSDBFPASSRECORDS
CEMSDBFDataMgr::GetPassSchedule( EMSTIME tm )
{
	memset( &m_aPassScheduleNow, 0, sizeof( EMSDBFPASSRECORDS ) );

	if ( ( tm.intTime > m_TimeStart.intTime ) &&
		 ( tm.intTime < m_TimeEnd.intTime ) &&
		 ( m_ulRecordCount > 0 ) &&
		 ( m_ulLastRecord  >= 0 ) &&
		 ( m_ulLastRecord  < m_ulRecordCount ) )
	{

		INT64 i64LastTime = m_aPassSchedule[m_ulLastRecord].timestamp.intTime;

		double dT = (double)( i64LastTime - tm.intTime ) * 1e-9;

		if( dT >= 0.0 )
		{
			int x = 5;
			while( ( dT > 0.0 ) && ( m_ulLastRecord  < m_ulRecordCount ) && ( m_ulLastRecord  > 0 ) )
			{
				i64LastTime = m_aPassSchedule[--m_ulLastRecord].timestamp.intTime;
				dT = (double)( i64LastTime - tm.intTime ) * 1e-9;
				if( dT < 1.0 )
				{
					break;
				}
			}

			if ( ( dT >= 0.0 ) && ( dT < 1.0 ) )
			{
				for ( ULONG i = 0; i < DBF_MAX_SATELLITES; i++ )
				{
					if ( dT < 1.0 ) 
					{
						m_aPassScheduleNow.rec[i] = m_aPassSchedule[m_ulLastRecord];
						i64LastTime = m_aPassSchedule[m_ulLastRecord++].timestamp.intTime;
						dT = (double)( i64LastTime - tm.intTime ) * 1e-9;
					}
					else
					{
						int x = 5;
					}
				}
			}
			else
			{
				int z = 5;
			}
		}
		else
		{
			while( ( dT < 0.0 ) && ( m_ulLastRecord  < m_ulRecordCount ) )
			{
				i64LastTime = m_aPassSchedule[++m_ulLastRecord].timestamp.intTime;
				dT = (double)( i64LastTime - tm.intTime ) * 1e-9;
			}

			if ( ( dT >= 0.0 ) && ( dT < 1.0 ) )
			{
				for ( ULONG i = 0; i < DBF_MAX_SATELLITES; i++ )
				{
					if ( dT < 1.0 ) 
					{
						m_aPassScheduleNow.rec[i] = m_aPassSchedule[m_ulLastRecord];
						i64LastTime = m_aPassSchedule[m_ulLastRecord++].timestamp.intTime;
						dT = (double)( i64LastTime - tm.intTime ) * 1e-9;
					}
					else
					{
						int x = 5;
					}
				}
			}
			else
			{
				int z = 5;
			}
		}
	}
	else
	{
		ReadPassSchedule( tm );
	}

	return m_aPassScheduleNow;
}
*/

/********************************************************************/

EMS_RESULT 
CEMSDBFDataMgr::ReadDBFPlateXML( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;
	CEMSDOMNode* pNode = NULL;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		try
		{
			CEMSConfigurationAccessor oDBFarray;
			std::wstring wszValue;

			oDBFarray.SetSourceFile( cwszXMLString );
			//snl
			CEMSObjectList<CEMSConfigurationAccessor> olstPlates = oDBFarray.GetAccessorList( L"Plate" );
			olstPlates.MoveFirst();
			ULONG ulPlates = olstPlates.Count();
			//end snl
			// now it is only one plate
			for( ULONG l = 0; l < 1; l++ )
			{
				memset( &m_aDBFplate, 0, sizeof( m_aDBFplate ) );
				CEMSConfigurationAccessor oPlateConfig = olstPlates.GetNext();

				m_aDBFplate.fPlateFaceAzimuth   = oPlateConfig.GetElementValueFloat( L"platefaceazimuth" );
				m_aDBFplate.fPlateFaceElevation = oPlateConfig.GetElementValueFloat( L"platefaceelevation" );
				m_aDBFplate.fPlateFaceRotation  = oPlateConfig.GetElementValueFloat( L"platefacerotation" );
				
				// Polarization = 0 for LHCP, Polarization = 1 for RHCP
				std::wstring wstrPlatePolarization = oPlateConfig.GetAttributeValue( L"platepolarization" ); 
				if( wstrPlatePolarization == L"RHCP" )
				{
					m_aDBFplate.wPlatePolarization = 1;
				}
				else
					m_aDBFplate.wPlatePolarization = 0;
				
				m_aDBFplate.wCellNumber = (WORD) oPlateConfig.GetAttributeValueULong( L"cellnumber" );
							
				pNode = oPlateConfig.GetNode( L"Cells" );
				if( pNode )
				{
					wszValue = pNode->GetXML();
					hr = _ParseCELLS( wszValue.c_str() );
					pNode->Release();
					pNode = NULL;
				}
				
				m_aDBFplate.wFixedPointNumber = (WORD) oPlateConfig.GetAttributeValueULong( L"FixedPointNumber" );

				pNode = oPlateConfig.GetNode( L"FixedPoints" );
				if( pNode )
				{
					wszValue = pNode->GetXML();
					hr = _ParseFIXEDPOINTS( wszValue.c_str() );
					pNode->Release();
					pNode = NULL;
				}

			}
		}
		catch( ... )
		{
			if( pNode )
			{
				pNode->Release();
				pNode = NULL;
			}

			throw;
		}
	}

	return hr;
}

/********************************************************************/

EMS_RESULT 
CEMSDBFDataMgr::_ParseCELLS( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oCELL;
		
		oCELL.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oCELL.GetAccessorList( L"Cell" );

		oConfigAccessList.MoveFirst();

		// cell numbers are 0 - 30  
		if( m_aDBFplate.wCellNumber > 30) m_aDBFplate.wCellNumber = 30;

		for( int i = 0; i < (oConfigAccessList.Count()+1) && (i < 31); i++ )

		{
			CEMSConfigurationAccessor oCELL = oConfigAccessList.GetNext();

			m_aDBFplate.emsDBFCells[i].wCellID = (WORD) oCELL.GetAttributeValueULong( L"@id" );
			m_aDBFplate.emsDBFCells[i].wChannelID = (WORD) oCELL.GetAttributeValueULong( L"ChannelID" );

			m_aDBFplate.emsDBFCells[i].fXcoord = oCELL.GetElementValueFloat( L"Xcoord" );
			m_aDBFplate.emsDBFCells[i].fYcoord = oCELL.GetElementValueFloat( L"Ycoord" );
			
			m_aDBFplate.emsDBFCells[i].fRHCP = oCELL.GetElementValueFloat( L"RHCPbias" );
			m_aDBFplate.emsDBFCells[i].fLHCP = oCELL.GetElementValueFloat( L"LHCPbias" );
		}
	}

	return hr;
}


/********************************************************************/

EMS_RESULT 
CEMSDBFDataMgr::_ParseFIXEDPOINTS( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = EMS_OK;

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		std::wstring wszValue;
		CEMSConfigurationAccessor	oFIXED;
		
		oFIXED.SetSource( cwszXMLString );

		CEMSObjectList<CEMSConfigurationAccessor> oConfigAccessList = oFIXED.GetAccessorList( L"FixedPoint" );

		oConfigAccessList.MoveFirst();

		// Rich: fixed point numbers are less than 10 
		if( m_aDBFplate.wFixedPointNumber > 10) m_aDBFplate.wFixedPointNumber = 10;

		for( int i = 0; i < (oConfigAccessList.Count()+1) && (i < m_aDBFplate.wFixedPointNumber); i++ )

		{
			CEMSConfigurationAccessor oFIXED = oConfigAccessList.GetNext();

			bool  bEnabled;


			m_aDBFplate.emsFixedPoints[i].wFixedPointID = (WORD) oFIXED.GetAttributeValueULong( L"@id" );

			m_aDBFplate.emsFixedPoints[i].fFixPointAzimuth = oFIXED.GetElementValueFloat( L"FixedPointAz" );
			m_aDBFplate.emsFixedPoints[i].fFixPointElevation = oFIXED.GetElementValueFloat( L"FixedPointEl" );
			m_aDBFplate.emsFixedPoints[i].fFixedPointDistance = oFIXED.GetElementValueFloat( L"FixedPointDistance" );
			m_aDBFplate.emsFixedPoints[i].wFixPointPolarization = (WORD) oFIXED.GetAttributeValueULong( L"FixedPointPol" );
			m_aDBFplate.emsFixedPoints[i].bEnabled = oFIXED.GetAttributeValueBoolean( L"FixedPointEnabled" );
			
			if ( m_aDBFplate.emsFixedPoints[i].bEnabled )
			{
				float px, py, pz;
				float saz, caz, sel, cel;
				float elx, phasex, dx, dy, dz, dist;
				
				float lambda = (c_dVelocityOfLight / 1544.5e6) * 100000; // converted to centimetres
				float dangle = 360.0;
				
				saz = sin( m_aDBFplate.emsFixedPoints[i].fFixPointAzimuth * c_dDegToRad);
				caz = cos( m_aDBFplate.emsFixedPoints[i].fFixPointAzimuth * c_dDegToRad);
				elx = m_aDBFplate.emsFixedPoints[i].fFixPointElevation + m_aDBFplate.fPlateFaceElevation;
				sel = sin( elx * c_dDegToRad); 
				cel = cos( elx * c_dDegToRad);
				px = saz * m_aDBFplate.emsFixedPoints[i].fFixedPointDistance; 
				py = caz * cel * m_aDBFplate.emsFixedPoints[i].fFixedPointDistance; 
				pz = caz * sel * m_aDBFplate.emsFixedPoints[i].fFixedPointDistance; 

				for ( int k = 0; k < DBF_NUM_ELEMENTS; k++ )
				{
					// Assume plate is flat and the fixed point is oriented in the plate coordinates
					dx = m_aDBFplate.emsDBFCells[i].fXcoord - px;
					dy = m_aDBFplate.emsDBFCells[i].fYcoord - py;
					dz = - pz;
					dist = sqrt( dx*dx + dy*dy + dz*dz );
					m_aDBFplate.emsDBFCells[i].fNearField = dist/lambda * dangle;;
				}

				dangle = 360.0;
				for ( int k = 0; k < DBF_NUM_ELEMENTS; k++ )
				{
					phasex = m_aDBFplate.emsDBFCells[i].fNearField - m_aDBFplate.emsDBFCells[DBF_CENTRE_ELEMENT].fNearField;
					m_aDBFplate.emsDBFCells[i].fNearField = fmod(phasex, dangle );
				}
			}
		}
	}

	return hr;
}

//---------------------------------------------------------------------------

EMSVECTORD
CEMSDBFDataMgr::_Convert2UnitVector( const double dAzimuth, const double dElevation )
{
	EMSVECTORD vUnitVector;
		
	// Compute unit vector pointing vectors
	vUnitVector.dX = cos( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
	vUnitVector.dY = sin( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
	vUnitVector.dZ = cos( dElevation * c_dDegToRad );

	return vUnitVector;
}

EMS_RESULT
CEMSDBFDataMgr::_PhaseCorrection( EMSDBFPASSRECORD2 *passrecord )
{
	EMS_RESULT hr = EMS_OK;

	if( passrecord->fPlateElevation > 0 )
	{

		EMSVECTORD vSat;
		double dCellPositionX = 0.0;
		double dCellPositionY = 0.0;
		double dDownlinkCarrierFreq = 1544500000.0;

		// wavelength = c /Freq (in centimetres)
		if ( passrecord->ulSatID < 500 )	// Galileo
			dDownlinkCarrierFreq = 1544100000.0;
		if (passrecord->ulSatID > 600 && passrecord->ulSatID < 700) // Beidou
			dDownlinkCarrierFreq = 1544210000.0;
		if (passrecord->ulSatID > 500 && passrecord->ulSatID < 600) // Glonass
			dDownlinkCarrierFreq = 1544800000.0;
		if (passrecord->ulSatID > 700 ) // GPS L-Band
			dDownlinkCarrierFreq = 1544900000.0;

		// Convert from centimetres to wavelengths
		double dWaveLength = 10000.0 * c_dVelocityOfLight / dDownlinkCarrierFreq;

		vSat = _Convert2UnitVector( passrecord->fPlateAzimuth, passrecord->fPlateElevation );

		double dPhase = 0.0;

		float fScaleFactor = 32675.0;

		for( int i = 0, j = 0; i < DBF_NUM_ELEMENTS; i++ )
		{
			dCellPositionX = m_aDBFplate.emsDBFCells[i].fXcoord / dWaveLength;
			dCellPositionY = m_aDBFplate.emsDBFCells[i].fYcoord / dWaveLength;

			dPhase = cos( vSat.dX * dCellPositionX + vSat.dY * dCellPositionY );

			j = m_aDBFplate.emsDBFCells[i].wChannelID - 1;

			//passrecord->nPhaseReal[j] = (short) ( sin( dPhase  ) * fScaleFactor );
			//passrecord->nPhaseImag[j] = (short) ( cos( dPhase  ) * fScaleFactor );
		}

		hr = EMS_OK;
	}
	return hr;
}