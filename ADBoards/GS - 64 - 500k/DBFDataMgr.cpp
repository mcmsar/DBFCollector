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

#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#include <io.h>

#include "emsclock.h"
#include "emsconst.h"
//#include "emsDBF.h"
#include "emsDBFtypes.h"
#include "emsDBFDataMgr.h"
#include "configurationaccessor.h"
#include <emsdomnode.h>
#include "emsencod.h"
#include "emsexcpt.h"
#include "convutility.h"

/********************************************************************/



/********************************************************************/

CEMSDBFDataMgr::CEMSDBFDataMgr()
{
	m_aPassSchedule = new EMSDBFPASSRECORD[MAX_SCHEDULE_RECORDS];
	if ( m_aPassSchedule )
	{
		memset( m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORD) * MAX_SCHEDULE_RECORDS );
	}
	else
	{
		// memory exception
	}

	m_aHourPassSchedule = new EMSDBFPASSRECORDS[MAX_SCHEDULE_RECORDS_HOUR];
	if ( m_aHourPassSchedule )
	{
		memset( m_aHourPassSchedule, 0, sizeof(EMSDBFPASSRECORDS) * MAX_SCHEDULE_RECORDS_HOUR );
	}
	else
	{
		// memory exception
	}

	m_lpPassFileBIN  = NULL;
	m_lpPassFileCSV  = NULL;
	memset(&m_aDBFplate, 0, sizeof(EMSDBFARRAY) );
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
	const wchar_t* cDir = L"C:\\HGT\\config\\";
	wchar_t* cPlateFile = L"DBFPlate_";
    wchar_t  wszFileName[256];
	
	memset(wszFileName, 0, sizeof(wszFileName) );

	wsprintfW( wszFileName, L"%s%s%02d.xml", cDir, cPlateFile, nPlateNumber );

	hr = ReadDBFPlateXML( wszFileName );


	// Establish Pass Schedule data files and parameters

//	lstrcpy( m_cFilePath, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\") );
	lstrcpy( m_cFilePath, TEXT("C:\\HGT\\DBFPassData\\") ); 
//	lstrcpy( m_cFilePath, TEXT("Z:") );

	CEMSSystemClock     oTime;
	m_TimeStart = oTime.GetTime();
	m_TimeEnd.intTime = 0;

	m_ulRecordCount = 0;
	m_ulLastRecord  = 0;

	hr = EMS_OK;

	return hr;
}

/********************************************************************/

EMS_RESULT
CEMSDBFDataMgr::Initialize( const wchar_t* cwsPlateConfigFile )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	if( cwsPlateConfigFile )
	{
		// Input Data Files
		hr = ReadDBFPlateXML( cwsPlateConfigFile );
		
		/// Establish Pass Schedule data files and parameters

	//	lstrcpy( m_cFilePath, TEXT("C:\\Program Files\\EMS Technologies\\DBF Data Collector\\DATA\\") );
	//	lstrcpy( m_cFilePath, TEXT("Z:\\DBFPassData") );
	//	lstrcpy( m_cFilePath, TEXT("Z:") );
		lstrcpy( m_cFilePath, TEXT("C:\\HGT\\DBFPassData\\") );


		CEMSSystemClock     oTime;
		m_TimeStart = oTime.GetTime();
		m_TimeEnd.intTime = 0;

		m_ulRecordCount = 0;
		m_ulLastRecord  = 0;

		hr = EMS_OK;
	}

	return hr;
}

/********************************************************************/

EMS_RESULT
CEMSDBFDataMgr::WritePassSchedule( EMSDBFPASSRECORD PassRecord, bool bTestSun )
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
			fwrite( &PassRecord, 1, sizeof( EMSDBFPASSRECORD ), m_lpPassFileBIN );

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
				PassRecord.timestamp,
				PassRecord.ulLutID,
				PassRecord.wPlateID,
				PassRecord.wProcessID,
				PassRecord.wAntennaID,
				PassRecord.ulSatID,
				PassRecord.fAzimuth,
				PassRecord.fElevation,
				PassRecord.fPlateAzimuth,
				PassRecord.fPlateElevation );
			
			for ( ULONG l = 0; l < m_aDBFplate.wCellNumber ; l++ )
			{
				double dPang = atan2( (double)PassRecord.nPhaseReal[l], (double)PassRecord.nPhaseImag[l] );
				if ( dPang < 0.0 ) dPang += c_dTwoPI;
				fprintf(m_lpPassFileCSV, "%f,", dPang * c_dRadToDeg );
			}

			fprintf(m_lpPassFileCSV, "\n" );

		}

		if ( bTestSun && ( PassRecord.ulSatID == 999 ) )
		{
			FILE* lpSun = fopen( "C:\\SunAzEl.csv","at" );
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

		EMSDBFPASSRECORD emsPassRec;

		memset( m_aHourPassSchedule, 0, sizeof(EMSDBFPASSRECORDS) * MAX_SCHEDULE_RECORDS_HOUR );
		m_ulRecordCount = 0;

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

			bool bFirstRecord = true;
			ULONG ulRecCount = 0;
			//snl
			//while ( ( ulByteCount < ulMaxByteCount ) && ( ulRecCount < MAX_SCHEDULE_RECORDS ) ) 
			while ( ( ulByteCount < ulMaxByteCount ) /*&& ( ulRecCount < MAX_SCHEDULE_RECORDS )*/ ) 
			{
				
				memset( &emsPassRec, 0, sizeof(EMSDBFPASSRECORD) );
				ULONG ulSize = fread( &emsPassRec,1,sizeof(EMSDBFPASSRECORD),m_lpPassFileBIN);

				if( ulSize == sizeof(EMSDBFPASSRECORD) )
				{
					if( bFirstRecord )
					{
						bFirstRecord = false;
						m_TimeStart = emsPassRec.timestamp;
					}
					_AddPassRecord( emsPassRec );
					ulRecCount++;
				}
				
				ulByteCount = ftell(m_lpPassFileBIN);
			}

			m_TimeEnd   = emsPassRec.timestamp;

			fclose( m_lpPassFileBIN );
			m_lpPassFileBIN = NULL;

			INT64 lDeltaT2 = (INT64)(( m_TimeEnd.intTime - m_TimeStart.intTime ) * 1e-9);
			INT64 lDeltaT = (INT64)(( m_TimeEnd.intTime - m_TimeStart.intTime )/1000000000);

			int x = sizeof(INT64);
			
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
CEMSDBFDataMgr::_AddPassRecord( EMSDBFPASSRECORD& dbfPassRec )
{
//	m_ulRecordCount++;
	INT64 lDeltaT = (INT64)(( dbfPassRec.timestamp.intTime - m_TimeStart.intTime ) * 1e-9);

	if( lDeltaT >= 0 && lDeltaT < 3600 )
	{
		int i = 0;
		while( (m_aHourPassSchedule[lDeltaT].rec[i].timestamp.intTime != 0) && i < 4 )
		{
			i++;
		}

		if( i < 4 )
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


/********************************************************************/

EMSDBFPASSRECORDS
CEMSDBFDataMgr::GetPassSchedule( EMSTIME tm )
{
	memset( &m_aPassScheduleNow, 0, sizeof( EMSDBFPASSRECORDS ) );

	if ( ( tm.intTime > m_TimeStart.intTime ) &&
		 ( tm.intTime < m_TimeEnd.intTime ) &&
		 ( m_ulRecordCount > 0 ) )
	{

		INT64 lDeltaT = (INT64)(( tm.intTime - m_TimeStart.intTime ) * 1e-9);

		if( (lDeltaT >= 0) && (lDeltaT <= m_ulRecordCount) )
		{
			m_aPassScheduleNow = m_aHourPassSchedule[lDeltaT];
		}
		else
		{
			// not supposed to happen.
		}
	}
	else
	{
		// skip it.
		ReadPassSchedule( tm );
	}

	return m_aPassScheduleNow;
}

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
			
			m_aDBFplate.wCellNumber = (WORD) oDBFarray.GetAttributeValueULong( L"CellNumber" );

			m_aDBFplate.fPlateFaceAzimuth   = oDBFarray.GetElementValueFloat( L"PlateFaceAzimuth" );
			m_aDBFplate.fPlateFaceElevation = oDBFarray.GetElementValueFloat( L"PlateFaceElevation" );
			m_aDBFplate.fPlateFaceRotation  = oDBFarray.GetElementValueFloat( L"PlateFaceRotation" );


			
			pNode = oDBFarray.GetNode( L"Cells" );
			if( pNode )
			{
				wszValue = pNode->GetXML();
				hr = _ParseCELLS( wszValue.c_str() );
				pNode->Release();
				pNode = NULL;
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

		for( ULONG l = 0; (l < oConfigAccessList.Count()) && (l < 32); l++ )
		{
			CEMSConfigurationAccessor oCELL = oConfigAccessList.GetNext();

			m_aDBFplate.wCellID[l] = (WORD) oCELL.GetAttributeValueULong( L"ChannelID" );

			m_aDBFplate.fXcoord[l] = oCELL.GetElementValueFloat( L"Xcoord" );
			m_aDBFplate.fYcoord[l] = oCELL.GetElementValueFloat( L"Ycoord" );
		}
	}

	return hr;
}

