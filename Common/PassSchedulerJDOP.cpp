/********************************************************************
*	              Copyright (c) 2013 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#define INITGUID
#include <initguid.h>
#include <time.h>
#include "emsconst.h"
#include "math.h"
#include "emsvectr.h"
#include "emsrange.h"
#include "emscoord.h"
//#include "ConfigManagerProxyClsid.h"
#include "ccbootstrap.h"
#include "emstime.h"
#include "emsorbit.h"			// IEMSOrbit
#include "emsatinf.h"			// Satellite Information Object
#include "emsiteif.h"			// IEMSSiteInfo
//#include "emsexcpt.h" 			// CEMSException
//#include "LogHelper.h"
#include "PassSchedulerJDOP.h"



CPassSchedulerJDOP::CPassSchedulerJDOP()
{
}

//-------------------------------------------------------------------------------------------------------------

CPassSchedulerJDOP::~CPassSchedulerJDOP()
{
	if ( m_lpPassArray )
	{
		delete [] m_lpPassArray;
		m_lpPassArray = NULL;
	}
	
	if ( m_lpPassList )
	{
		delete [] m_lpPassList;
		m_lpPassList = NULL;
	}

	if ( m_lpSatArray )
	{
		delete [] m_lpSatArray;
		m_lpSatArray = NULL;
	}

	if ( m_lpAntArray )
	{
		delete [] m_lpAntArray;
		m_lpAntArray = NULL;
	}

	if ( m_lpSatelliteVectorFile )
	{
		fclose( m_lpSatelliteVectorFile );
		m_lpSatelliteVectorFile = NULL;
	}

	if ( m_lpTrackPlanFile )
	{
		fclose( m_lpTrackPlanFile );
		m_lpTrackPlanFile = NULL;
	}
	
	if ( m_lpTraceFile )
	{
		fclose( m_lpTraceFile );
		m_lpTraceFile = NULL;
	}



}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::CreateObjects()
{
	EMS_RESULT hr = EMS_OK;

	//try
	{
		LPUNKNOWN lpUnk = 0;

		//if( CCBootstrap::IsMEOSystem() )
		//{
		//	hr = CoCreateInstance( CLSID_EMSConfigProxy, 0, CLSCTX_ALL, 
		//				IID_IEMSSiteInfo, (void**) &m_lpSiteInfo);
		//}
		//else
		//{
		//}

		m_lpOrbit = 0;


		hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, IID_IEMSOrbit4, 
								(LPVOID*)&m_lpOrbit );

		//if ( hr != EMS_OK )
		//	throw CEMSException(( ????, hr );
	}
	
	//catch ( CEMSException ex )
	//{
	//	hr = ex.GetErrCode();

	//	CEMSLogHelper::LogAlarmMsg( hr , ex.GetSubErrCode() );
	//}

	return hr; 

}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::Process()
{

	EMS_RESULT hr = EMS_FALSE;
	CEMSTime CT( m_StartTime );

	// Ensure existing track and trace files are deleted before processing
	remove( c_DefaultTrackFile );
	remove( c_DefaultTraceFile );
	
	m_lpTrackPlanFile       = fopen(c_DefaultTrackFile,"a+t");
	m_lpTraceFile           = fopen(c_DefaultTraceFile,"a+t");
	m_lpSatelliteVectorFile = fopen(c_DefaultSatelliteFile,"rt");

	// Write header records
	fprintf( m_lpTraceFile, "Time,#Satellites,JDOP,Status,AntennaID,SatelliteID,Azimuth,Elevation\n" );
	
	fprintf( m_lpTrackPlanFile, "LastStatus,Status,AntennaID,SatelliteID,OrbitNumber,Priority,Duration,");
	fprintf( m_lpTrackPlanFile, "StartTime,StartAzimuth,StartElevation,");
	fprintf( m_lpTrackPlanFile, "EndTime,EndAzimuth,EndElevation,");
	fprintf( m_lpTrackPlanFile, "MaxElTime,MaxElAzimuth,MaxElevation,");
	fprintf( m_lpTrackPlanFile, "MinElTime,MinElAzimuth,MinElevation,");
	fprintf( m_lpTrackPlanFile, "OrbitTime,Xposition,Yposition,Zposition,Xvelocity,Yvelocity,Zvelocity\n" );

	EMSTIME nTime = m_StartTime;

	EMSTIME time1 = CEMSSystemClock::GetTime();

	if ( m_lpSatelliteVectorFile && m_lpTrackPlanFile &&  m_lpTraceFile ) hr = EMS_OK;


	while( CT<( m_StopTime ) && (EMS_OK == hr) )
	{
		hr = PredictPass( nTime );
		hr = UpdateStatus( nTime );
		hr = GenerateSchedule();
		hr = OutputTrace();
		nTime = CT.AddMinutes ( m_dTimeIncrement );
	}

	EMSTIME time2 = CEMSSystemClock::GetTime();

	double dTimeDiff = ( time2.intTime - time1.intTime ) *1e-9;

	if ( m_lpSatelliteVectorFile )
	{
		fclose( m_lpSatelliteVectorFile );
		m_lpSatelliteVectorFile = NULL;
	}
	
	if ( m_lpTrackPlanFile )
	{
		fclose( m_lpTrackPlanFile );
		m_lpTrackPlanFile = NULL;
	}
	
	if ( m_lpTraceFile )
	{
		fclose( m_lpTraceFile );
		m_lpTraceFile = NULL;
	}
	
	return hr;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::Init()
{
	EMS_RESULT hr = EMS_OK;
	
	// Default configuration data
	// Note: List must include a reference beacon
	double defaultTestLatitude[4] = { 78.2302, 27.7638, 34.8636, 43.55896 };
	double defaultTestLongitude[4] = { 15.3739,-15.6331, 33.3839, 1.48373 };
	float defaultTestAltitude[4] = { 0,0,0,0 };
	ULONG defaultTestCount = 4;

	// Toulouse Reference beacon
	//double defaultRefBeaconLatitude  = 43.55896;
	//double defaultRefBeaconLongitude = 1.48373;
	//double defaultRefBeaconAltitude  = 0.0;
	//EMSLOCATION defaultRefBeaconLocation;

	double defaultAntennaLatitude[4]  = { 78.2302, 27.7638, 34.8636, 43.55896 };
	double defaultAntennaLongitude[4] = { 15.3739,-15.6331, 33.3839, 1.48373 };
	float defaultAntennaAltitude[4]   = { 0,0,0,0 };
	double defaultAntennaMinElevation = 10.0;
	double defaultAntennaBeamwidth    = 6.0;

	ULONG defaultAntennaCount = 16;
	//ULONG defaultAntennaCount = 4;
	EMSLOCATION defaultAntennaLocation;

	//ULONG defaultSatCount = 13;
	//ULONG defaultSatID[13] = { 301,302,315,316,317,318,319,323,324,329,419,420,501 };
	//ULONG defaultSatPriority[13] = { 10,10,10,10,10,10,10,10,10,10,50,50,50 };
	//double defaultSatFrequency[13] = { 2.226,2.226,2.226,2.226,2.226,2.226,2.226,2.226,2.226,2.226,1.5441,1.5441,1.5449 };
	
	// Default Galileo constellation
	ULONG defaultSatCount = 27;
	ULONG defaultSatID[27];
	ULONG defaultSatPriority[27];
	double defaultSatFrequency[27];

	for( int i = 0; i < defaultSatCount; i++ )
	{
		defaultSatID[i]        = i + 401;
		defaultSatPriority[i]  = 10;
		defaultSatFrequency[i] =  1.5441;
	}

	m_lpSatArray = new SATDATA [ defaultSatCount ];
	m_lpAntArray = new ANTDATA [ defaultAntennaCount ];
		
	memset(&m_lpSatArray[0], 0, sizeof(SATDATA) * defaultSatCount);
	memset(&m_lpAntArray[0], 0, sizeof(ANTDATA) * defaultAntennaCount);
	
	// Establish pass times

	m_StartTime = CEMSSystemClock::GetTime();
	CEMSTime CT( m_StartTime );
	m_StopTime  = CT.AddDays( 1.0 );
	m_dTimeIncrement = 1.0;

	m_dMaxPassDuration	= 4.0 * 60.0;  // units in minutes
	m_dMinPassDuration	= 20.0;  // units in minutes
	m_dMinElevation		= defaultAntennaMinElevation;
	m_dMinSeparationAngle = 6.0;
	m_JDOPfactor		= 5000.0;

	m_bTraceFile = true;


	// Compute test location coordinates
	
	CEMSCoordSystem CS;
	m_ulTestCount = defaultTestCount;

	for( ULONG i = 0; i < m_ulTestCount; i++)
	{
		m_lpTestLocation[i].degLatitude  = defaultTestLatitude[ i ];
		m_lpTestLocation[i].degLongitude = defaultTestLongitude[ i ];
		m_lpTestLocation[i].fAltitude    = defaultTestAltitude[ i ];

		m_lpTestXYZ[i] = CS.ToEarthFixedDouble( m_lpTestLocation[i] );
	}	

	// Read satellite information

	m_ulSatelliteCount = 0;

	for( ULONG isat = 0; isat < defaultSatCount; isat++ )
	{
		// Get next satellite ID

		// if satellite ID exists and is available
		{
			m_lpSatArray[isat].ulSatID		 = defaultSatID[isat];
			m_lpSatArray[isat].ulSatPriority = defaultSatPriority[isat];
			m_lpSatArray[isat].dDownlinkFreq = defaultSatFrequency[isat];
			m_lpSatArray[isat].ulStatus		 = 0;

			m_ulSatelliteCount++;
		}
	}

	// Sort satellite array in highest priority order
	SATDATA testSat;

	for( ULONG isat = 0; isat < m_ulSatelliteCount-1; isat++ )
	{
		testSat = m_lpSatArray[isat];

		for( ULONG jsat = isat+1; jsat < m_ulSatelliteCount; jsat++ )
		{
			if( m_lpSatArray[jsat].ulSatPriority > testSat.ulSatPriority )
			{	
				testSat			   = m_lpSatArray[jsat];
				m_lpSatArray[jsat] = m_lpSatArray[isat];
				m_lpSatArray[isat] = testSat;
			}
		}
	}

	
	// Read antenna information
	
	ULONG ulCount = 0;

	m_ulAntennaCount = 0;
	for( ULONG iant = 0; iant < defaultAntennaCount; iant++ )
	{
		// Get next antenna ID

		// if antenna ID exists and is available
		{
			m_lpAntArray[m_ulAntennaCount].ulAntennaID = iant+1;
			m_lpAntArray[m_ulAntennaCount].dMinElevation = defaultAntennaMinElevation;
			m_lpAntArray[m_ulAntennaCount].dMinSeparation = defaultAntennaBeamwidth;
			m_lpAntArray[m_ulAntennaCount].ulStatus = 0;

			// Get list of available satellites for antenna (if empty assume all satellites)
			m_lpAntArray[m_ulAntennaCount].ulSatCount = 0;
			for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++ )
			{
				// if satellite ID available and is on list 
				m_lpAntArray[m_ulAntennaCount].ulSatList[isat] = m_lpSatArray[isat].ulSatID;
				m_lpAntArray[m_ulAntennaCount].ulSatCount++;
			}
			// Count number of available satellites for antenna
			ulCount += m_lpAntArray[m_ulAntennaCount].ulSatCount;

			// Get antenna location and convert to X,Y,Z coordinates
			ULONG isite = iant % 4;
			//ULONG isite = 3;
			defaultAntennaLocation.degLatitude  = defaultAntennaLatitude[ isite ];
			defaultAntennaLocation.degLongitude = defaultAntennaLongitude[ isite ];
			defaultAntennaLocation.fAltitude    = defaultAntennaAltitude[ isite ];
			m_lpAntArray[m_ulAntennaCount].antennaLocation = defaultAntennaLocation;
			m_lpAntArray[m_ulAntennaCount].antennaCoord = CS.ToEarthFixedDouble( m_lpAntArray[m_ulAntennaCount].antennaLocation );

			m_ulAntennaCount++;
		}
	}

	m_ulPassCount = ulCount;
	m_lpPassArray = new PASSDATA [ m_ulPassCount ];
	m_lpPassList  = new ULONG [ m_ulPassCount ];

	memset(m_lpPassArray, 0, sizeof(PASSDATA) * m_ulPassCount);
	memset(m_lpPassList,  0, sizeof(ULONG) * m_ulPassCount);

	// Establish Pass Array Initial Conditions

	ulCount = 0;
	for( ULONG iant = 0; iant < m_ulAntennaCount; iant++)
	{
		for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++)
		{
			// Check if antenna allowed to track satellite

			//if _satOK( iant, isat )
			{
				m_lpPassArray[ ulCount ].ulAntennaID	= m_lpAntArray[iant].ulAntennaID;
				m_lpPassArray[ ulCount ].ulSatID		= m_lpSatArray[isat].ulSatID;
				m_lpPassArray[ ulCount ].ulSatPriority	= m_lpSatArray[isat].ulSatPriority;
				m_lpPassArray[ ulCount ].dFrequency     = m_lpSatArray[isat].dDownlinkFreq;
				m_lpPassArray[ ulCount ].ulLastStatus   = PASS_MASK_CONSTRAINT;
				m_lpPassArray[ ulCount ].ulStatus       = PASS_MASK_CONSTRAINT;

				m_lpPassArray[ ulCount ].startPass = m_StartTime;
				m_lpPassArray[ ulCount ].endPass   = m_StartTime;
				m_lpPassArray[ ulCount ].minElPass = m_StartTime;
				m_lpPassArray[ ulCount ].maxElPass = m_StartTime;
				m_lpPassArray[ ulCount ].azelMinEl.degElevation = 100;


				ulCount++;
			}

		}
	}
	
	

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::PredictPass( EMSTIME PredictTime )
{
	EMS_RESULT hr = EMS_OK;
	for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++ )
	{
		ULONG ulSatID = m_lpSatArray[isat].ulSatID;
		ULONG ulNORADID = m_lpSatArray[isat].ulNORADID;

		CEMSCoordSystem CS;
			
		EMSTIMECOORDD timeCoord;
		ULONG ulCount = 0;
		ULONG ulOrbitNumber = 0;

		// Predict orbit vector to input time

		if ( m_lpOrbit )
		{

			hr = m_lpOrbit->GetOrbitNumber( ulSatID, PredictTime, &ulOrbitNumber );
			

			memset( &timeCoord, 0, sizeof( timeCoord ) );

			if ( EMS_OK == hr) 	
			{
				hr = m_lpOrbit->EarthFixedOrbitDouble( ulSatID, &PredictTime, 1, &timeCoord, &ulCount );
			}
		}
			
		if ( !(EMS_OK == hr) && m_lpSatelliteVectorFile ) 	
		{
			char line[256];
			if( fgets( line, sizeof(line), m_lpSatelliteVectorFile ) != NULL )
			{
				int k;
				PCHAR pLine;
				pLine = line;
				ULONG ulVectorTime = 0;
				sscanf( pLine, "%03d, %n", &ulSatID, &k );
				ulSatID += 400;
				pLine += k;
				sscanf( pLine, "%06d, %n", &ulNORADID, &k );
				pLine += k;
				sscanf( pLine, "%10d, %n", &ulVectorTime, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.radius.dX, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.radius.dY, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.radius.dZ, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.velocity.dX, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.velocity.dY, &k );
				pLine += k;
				sscanf( pLine, "%lf, %n", &timeCoord.coord.velocity.dZ, &k );
						
				timeCoord.vTime = m_StartTime;
				timeCoord.vTime.intTime += (INT64) (ulVectorTime * 1.0e9);

				timeCoord.coordSystem = COORDSYS_EarthFixed;

				m_lpSatArray[isat].ulNORADID = ulNORADID;

				hr = EMS_OK;

			}
		}

		if ( EMS_OK == hr) 	
		{
			EMSAZELVECTORD Azel;
						
			for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
			{
				// pass number
				ULONG ulAntenna = m_lpAntArray[iant].ulAntennaID;
				int   ipass = _FindPassIndex ( ulAntenna, ulSatID );

				if ( ipass >= 0 )
				{
					m_lpPassArray[ipass].satvect = timeCoord;
					m_lpPassArray[ipass].ulOrbitNumber = ulOrbitNumber;
					m_lpPassArray[ipass].ulLastStatus = m_lpPassArray[ipass].ulStatus;

					_ResetFlag( ipass, PASS_MASK_CONSTRAINT );

					// Compute pointing angles
					Azel = _GetAzimuthElevation(  timeCoord, m_lpAntArray[iant].antennaLocation );
					m_lpPassArray[ipass].azelEnd = Azel.azel;
					m_lpPassArray[ipass].endPass = timeCoord.vTime;

					// Update maximum elevation data
					if( m_lpPassArray[ipass].azelMaxEl.degElevation < m_lpPassArray[ipass].azelEnd.degElevation )
					{
						m_lpPassArray[ipass].azelMaxEl = m_lpPassArray[ipass].azelEnd;
						m_lpPassArray[ipass].maxElPass = m_lpPassArray[ipass].endPass;
					}
					// Update minimum elevation data
					if( m_lpPassArray[ipass].azelMinEl.degElevation > m_lpPassArray[ipass].azelEnd.degElevation )
					{
						m_lpPassArray[ipass].azelMinEl = m_lpPassArray[ipass].azelEnd;
						m_lpPassArray[ipass].minElPass = m_lpPassArray[ipass].endPass;
					}
				}

			}
		}
		else
		{
			hr = EMS_BAD_PARAM;

			m_lpSatArray[isat] .ulStatus |= PASS_SATELLITE_OUTAGE_FLAG;
			for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
			{
				// pass number		
				ULONG ulAntenna = m_lpAntArray[iant].ulAntennaID;
				int ipass = _FindPassIndex ( iant, isat );

				if ( ipass >= 0 )
				{
					_SetFlag( ipass, PASS_SATELLITE_OUTAGE_FLAG );
				}
			}
		}
	}

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::UpdateStatus( EMSTIME PredictTime)
{

	EMS_RESULT hr = EMS_OK;
	
	_CheckAvailability( PredictTime );
	_CheckElevationAngle();
	_CheckSeparationAngle();

	// Fill antenna and satellite index arrays
	m_ulUniqueAntennas = 0;
	for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
	{
		m_UniqueAntennaIndex[m_ulUniqueAntennas++] = m_lpAntArray[iant].ulAntennaID;
	}
	m_ulUniqueSatellites = 0;
	for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++ )
	{
		m_UniqueSatelliteIndex[m_ulUniqueSatellites++] = m_lpSatArray[isat].ulSatID;
	}

	// Establish start and end flags based upon constraint changes
	for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
	{
		bool bTest1 = _CheckLastMask(ipass, PASS_MASK_CONSTRAINT );
		bool bTest2 = _CheckMask( ipass, PASS_MASK_CONSTRAINT );

		if( (!bTest1) && (bTest2) )
		{
			_SetFlag( ipass, PASS_END_FLAG );
			_ResetFlag( ipass, PASS_START_FLAG );
		}
		if( (!bTest2) && (bTest1) )
		{
			_ResetFlag( ipass, PASS_MASK_ALL ); 
			_SetFlag( ipass, PASS_START_FLAG );

			m_lpPassArray[ipass].azelStart = m_lpPassArray[ipass].azelEnd;
			m_lpPassArray[ipass].startPass = m_lpPassArray[ipass].endPass;
			m_lpPassArray[ipass].azelMaxEl = m_lpPassArray[ipass].azelEnd;
			m_lpPassArray[ipass].maxElPass = m_lpPassArray[ipass].endPass;
			m_lpPassArray[ipass].azelMinEl = m_lpPassArray[ipass].azelEnd;
			m_lpPassArray[ipass].minElPass = m_lpPassArray[ipass].endPass;

		}
		if( (!bTest2) && (!bTest1) )
		{
			m_lpPassArray[ipass].ulStatus = m_lpPassArray[ipass].ulLastStatus;
		}

		// Check if pass longer than maximum duration
		double dPassDuration = (double)(m_lpPassArray[ipass].endPass.intTime - m_lpPassArray[ipass].startPass.intTime );
		dPassDuration *= 1.0e-9 / 60.0;  // units in minutes

		if (  (dPassDuration > m_dMaxPassDuration) && _CheckMask( ipass, PASS_CURRENT_FLAG ) )
		{
			_SetFlag( ipass, PASS_END_FLAG );
			_ResetFlag( ipass, PASS_START_FLAG );
		}
		
		// Output pass if pass end detected
		if( _CheckFlag( ipass, PASS_END_FLAG ) )
		{
			_OutputSchedule( ipass );
			_ResetFlag( ipass, PASS_MASK_TRACK | PASS_MASK_TYPE ); 
		}

		// Remove antenna from schedule lists if currently tracking or known outage
		if( _CheckMask( ipass, PASS_ANTENNA_OUTAGE_FLAG | PASS_CURRENT_FLAG ) )
			m_ulUniqueAntennas = _RemovefromList( m_lpPassArray[ipass].ulAntennaID, &m_UniqueAntennaIndex[0], m_ulUniqueAntennas );
		
		// Remove satellite from schedule lists if currently tracked or known outage
		if( _CheckMask( ipass, PASS_SATELLITE_OUTAGE_FLAG | PASS_CURRENT_FLAG ) )
			m_ulUniqueSatellites = _RemovefromList( m_lpPassArray[ipass].ulSatID, &m_UniqueSatelliteIndex[0], m_ulUniqueSatellites );

	}

	// Check if satellite not available to all available antennas
	ULONG ulSatID;
	ULONG ulAntennaID;
	int ipass;

	for( int isat = 0; isat < m_ulUniqueSatellites; isat++ )
	{
		bool bOK = true;
		ulSatID = m_UniqueSatelliteIndex[isat];

		for( int iant = 0; iant < m_ulUniqueAntennas; iant++ )
		{
			ulAntennaID = m_UniqueAntennaIndex[iant];
			ipass = _FindPassIndex ( ulAntennaID, ulSatID );

			if ( ipass >= 0 )
			{
				if ( !_CheckMask( ipass, PASS_MASK_CONSTRAINT ) )
				{
					bOK = false;
					break;
				}
			)
		}

		if( bOK )
		{
			m_ulUniqueSatellites = _RemovefromList( ulSatID, &m_UniqueSatelliteIndex[0], m_ulUniqueSatellites );
			isat++;
		}

	}

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::GenerateSchedule()
{

	EMS_RESULT hr = EMS_OK;

	ULONG ulSatID;
	ULONG ulAntennaID;
	int   ipass;

	memset( m_AntennaIndex, 0, sizeof(ULONG) * m_ulUniqueAntennas );
	memset( m_SatelliteIndex, 0, sizeof(ULONG) * m_ulUniqueSatellites );

		
	for( ULONG iant = 0; iant < m_ulUniqueAntennas; iant++ )
	{
		ulAntennaID = m_UniqueAntennaIndex[iant];
			
		for( ULONG isat = 0; isat < m_ulUniqueSatellites; isat++ )
		{
			ulSatID = m_UniqueSatelliteIndex[isat];
			ipass = _FindPassIndex ( ulAntennaID, ulSatID );

			if ( ipass >= 0 )
			{
				if( !_CheckMask( ipass, PASS_MASK_CONSTRAINT ) )
				{
					m_AntennaIndex[iant]++;
					m_SatelliteIndex[isat]++;
				}
			}
		}
	}


	ULONG ulTotalCombinations = _NchooseK( m_ulUniqueSatellites, m_ulUniqueAntennas );
	
	// Special Case if more antennas than satellites
	// Check if more antennas than satellites
	if( ulTotalCombinations == 0 )
	{
				
		for( ULONG iant = 0; iant < m_ulUniqueAntennas; iant++ )
		{
			ulAntennaID = m_UniqueAntennaIndex[iant];
			for( ULONG isat = 0; isat < m_ulUniqueSatellites; isat++ )
			{
				hr = EMS_FALSE;
				ulSatID = m_UniqueSatelliteIndex[isat];
				ipass = _FindPassIndex ( ulAntennaID, ulSatID );

				if ( ipass >= 0 )
				{
					// Check if pass not available because of constraint or already scheduled
					if( !_CheckMask( ipass, PASS_MASK_CONSTRAINT ) && !_CheckFlag( ipass, PASS_CURRENT_FLAG ) )
					{
						// Schedule 'ipass'
						_SetFlag( ipass, PASS_SCHEDULE_FLAG );
						hr = _SetPass( ipass );
						break;
					}
				}
			}
			if ( EMS_OK )
			{
				m_ulUniqueSatellites = _RemovefromList( ulSatID, &m_UniqueSatelliteIndex[0], m_ulUniqueSatellites );
				m_UniqueAntennaIndex[iant] = -1;
			}
		}

		// Track any satellite in view for all remaining antenna
		ULONG ulLastCount = m_ulUniqueAntennas + 1;
		while( m_ulUniqueAntennas < ulLastCount )
		{
			ulLastCount = m_ulUniqueAntennas;
			m_ulUniqueAntennas = _RemovefromList( -1, &m_UniqueAntennaIndex[0], m_ulUniqueAntennas );
		}

		if ( m_ulUniqueAntennas )
		{
			for( ULONG iant = 0; iant < m_ulUniqueAntennas; iant++ )
			{
				ulAntennaID = m_UniqueAntennaIndex[iant];
				for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++ )
				{
					hr = EMS_FALSE;
					ulSatID = m_lpSatArray[isat].ulSatID;
					ipass = _FindPassIndex ( ulAntennaID, ulSatID );

					if ( ipass >= 0 )
					{
						// Check if pass available and not already scheduled
						if( !_CheckMask( ipass, PASS_MASK_CONSTRAINT ) && !_CheckFlag( ipass, PASS_CURRENT_FLAG ))
						{
							// Schedule 'ipass'
							_SetFlag( ipass, PASS_SCHEDULE_FLAG );
							hr = _SetPass( ipass );
							break;
						}
					}
				}
			}
		}
			
	}
	else
	{
		// More satellites than antennas condition
		ULONG N = m_ulUniqueSatellites;
		ULONG K = m_ulUniqueAntennas;
		ulTotalCombinations = _GetAllCombinations( N, K );

		if( m_ulUniqueAntennas < m_ulAntennaCount )
		{
			memset(m_CombinationIndex, 0, sizeof(LONG)*MAXANT );
			ULONG index = m_ulUniqueAntennas;
			// Find all antennas currently tracking
			for( int ipass = 0; ipass < m_ulPassCount; ipass++ )
			{
				if( _CheckFlag( ipass, PASS_CURRENT_FLAG ) )
				{
					m_CombinationIndex[index++] = ipass;
					if( index >= m_ulAntennaCount ) break;
				}
			}
		}

		double dJDOPmin = 1.0e10;
		double dJDOP    = 0;
		int icombmin    = 0;
		bool bCombOK    = false;

		for( ULONG icomb = 0; icomb < ulTotalCombinations; icomb++ )
		{
			bCombOK = _GetCombination( icomb );

			if ( bCombOK )
			{
				dJDOP = 0.0;
				for( ULONG itest = 0; itest < m_ulTestCount; itest++ )
				{
					dJDOP += _JDOP( m_lpTestXYZ[itest] );
				}

				if ( dJDOP < dJDOPmin )
				{
					dJDOPmin = dJDOP;
					icombmin = icomb;
				}
			}
		}

		_GetCombination( icombmin );

		ULONG index;
		for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
		{
			index = m_CombinationIndex[iant];

			if( !_CheckMask( index, PASS_MASK_CONSTRAINT ) && !_CheckFlag( index, PASS_CURRENT_FLAG ) )
			{
				_SetFlag( index, PASS_SCHEDULE_FLAG );
				hr = _SetPass( index );
			}

		}
	}
	return hr;
}

//-------------------------------------------------------------------------------------------------------------

bool 
CPassSchedulerJDOP::_GetCombination( ULONG icomb )
{
	bool bOK = true;
	for( ULONG iant = 0; iant < m_ulUniqueAntennas; iant++ )
	{
		int isat = m_AllCombinations[icomb][iant];
		if ( ( isat >= 0 ) && ( isat < m_ulUniqueSatellites ) )
		{
			ULONG iSatID = m_UniqueSatelliteIndex[isat];
			ULONG iAntID = m_UniqueAntennaIndex[iant];
			int index    = _FindPassIndex ( iAntID, iSatID );

			if ( index < 0 )
			{
				bOK = false;
			}
			else if( !_CheckMask( index, PASS_MASK_CONSTRAINT ) )
			{
				m_CombinationIndex[iant] = index;
			}
			else
			{
				bOK = false;
			}
		}
		else
		{
			bOK = false;
		}
	}


	return bOK;
}
//-------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------

bool
CPassSchedulerJDOP::_CheckCombination( ULONG icomb, ULONG isat )
{
	bool bOK = true;

	for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
	{
		if( isat == m_AllCombinations[icomb][iant] )
		{
			bOK = false;
			break;
		}
	}
	return bOK;
}

//-------------------------------------------------------------------------------------------------------------


EMS_RESULT 
CPassSchedulerJDOP::_OutputSchedule( ULONG ipass )
{
	ULONG ulStatus;
	EMS_RESULT hr = EMS_FALSE;
	std::string szDateTime;

	if ( m_lpTrackPlanFile )
	{
		double dDuration = m_lpPassArray[ ipass ].endPass.intTime - m_lpPassArray[ ipass ].startPass.intTime;
		dDuration *= 1.0e-9 / 60;
				
		// output pass record if duration greater than minimum allowed
			
		if ( dDuration > m_dMinPassDuration )
		{
			fprintf( m_lpTrackPlanFile,"%3X,%3X,%2d,%3d,%5d,%3d,%5.2f,",
				m_lpPassArray[ ipass ].ulLastStatus,
				m_lpPassArray[ ipass ].ulStatus,
				m_lpPassArray[ ipass ].ulAntennaID,
				m_lpPassArray[ ipass ].ulSatID,
				m_lpPassArray[ ipass ].ulOrbitNumber,
				m_lpPassArray[ ipass ].ulSatPriority,
				dDuration );
				
			szDateTime = _ConvertToDateTimeString( m_lpPassArray[ ipass ].startPass );
			fprintf( m_lpTrackPlanFile,"%s,%6.2f,%6.2f,",szDateTime.c_str(),
				m_lpPassArray[ ipass ].azelStart.degAzimuth,
				m_lpPassArray[ ipass ].azelStart.degElevation);

			szDateTime = _ConvertToDateTimeString( m_lpPassArray[ ipass ].endPass );
			fprintf( m_lpTrackPlanFile,"%s,%6.2f,%6.2f,",szDateTime.c_str(),
				m_lpPassArray[ ipass ].azelEnd.degAzimuth,
				m_lpPassArray[ ipass ].azelEnd.degElevation);

			szDateTime = _ConvertToDateTimeString( m_lpPassArray[ ipass ].maxElPass );
			fprintf( m_lpTrackPlanFile,"%s,%6.2f,%6.2f,",szDateTime.c_str(),
				m_lpPassArray[ ipass ].azelMaxEl.degAzimuth,
				m_lpPassArray[ ipass ].azelMaxEl.degElevation);

			szDateTime = _ConvertToDateTimeString( m_lpPassArray[ ipass ].minElPass );
			fprintf( m_lpTrackPlanFile,"%s,%6.2f,%6.2f,",szDateTime.c_str(),
			m_lpPassArray[ ipass ].azelMinEl.degAzimuth,
			m_lpPassArray[ ipass ].azelMinEl.degElevation);

			szDateTime = _ConvertToDateTimeString( m_lpPassArray[ ipass ].satvect.vTime );
			fprintf( m_lpTrackPlanFile,"%s,%10.3f,%10.3f,%10.3f,%10.6f,%10.6f,%10.6f",szDateTime.c_str(),
				m_lpPassArray[ ipass ].satvect.coord.radius.dX,
				m_lpPassArray[ ipass ].satvect.coord.radius.dY,
				m_lpPassArray[ ipass ].satvect.coord.radius.dZ,
				m_lpPassArray[ ipass ].satvect.coord.velocity.dX,
				m_lpPassArray[ ipass ].satvect.coord.velocity.dY,
				m_lpPassArray[ ipass ].satvect.coord.velocity.dZ);

			fprintf( m_lpTrackPlanFile,"\n");

		}
			
		_ResetPass( ipass );

		hr = EMS_OK;
	}

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

void 
CPassSchedulerJDOP::_CheckAvailability( EMSTIME PredictTime )
{
	// Lookup satellite and antenna availability for input time


	LONG isat = 0;
	LONG iant = 0;

	for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
	{
		
		isat = _FindSatelliteIndex ( m_lpPassArray[ipass].ulSatID );

		if( (m_lpSatArray[isat].tOutageTimeStart.intTime < m_lpPassArray[ipass].endPass.intTime)
			&& (m_lpSatArray[isat].tOutageTimeEnd.intTime > m_lpPassArray[ipass].endPass.intTime) )
		{
			_SetFlag( ipass, PASS_SATELLITE_OUTAGE_FLAG );
		}
		else
		{
			_ResetFlag( ipass, PASS_SATELLITE_OUTAGE_FLAG );
		}

		iant = _FindAntennaIndex ( m_lpPassArray[ipass].ulAntennaID );
		if( (m_lpAntArray[iant].tOutageTimeStart.intTime < m_lpPassArray[ipass].endPass.intTime)
			&& (m_lpAntArray[iant].tOutageTimeEnd.intTime > m_lpPassArray[ipass].endPass.intTime) )
		{
			_SetFlag( ipass, PASS_ANTENNA_OUTAGE_FLAG );
		}
		else
		{
			_ResetFlag( ipass, PASS_ANTENNA_OUTAGE_FLAG );
		}

			
	}

	
	return;
}

//-------------------------------------------------------------------------------------------------------------

void 
CPassSchedulerJDOP::_CheckSeparationAngle()
{
	// Compute separation angles

	
	ULONG ulAntID;
	double dSeparationThreshold = cos( m_dMinSeparationAngle * c_dDegToRad );

	for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
	{
		ulAntID = m_lpAntArray[iant].ulAntennaID;
		dSeparationThreshold = cos( m_lpAntArray[iant].dMinSeparation * c_dDegToRad );
		
		// Find indices with same antenna identifier
		_FillAntPassList( ulAntID, false );

		// Reset beamwidth flag for all records prior to computing the separation angles
		for( ULONG index = 0; index < m_ulPassListCount; index++ )
		{
			ULONG ipass = m_lpPassList[ index ];
			_ResetFlag( ipass, PASS_ANTENNA_BEAMWIDTH_FLAG );
		}


		for( ULONG itest1 = 0; itest1 < m_ulPassListCount-1; itest1++)
		{
			double x1,y1,z1;
			double az1, el1;
			double x2,y2,z2;
			double az2, el2;
			double dSeparation;
			ULONG ipass1, ipass2;

			ipass1 = m_lpPassList[ itest1 ];

			if( !_CheckFlag( ipass1, PASS_ANTENNA_ELEVATION_FLAG ) )
			{
				az1 = m_lpPassArray[ipass1].azelEnd.degAzimuth;
				el1 = m_lpPassArray[ipass1].azelEnd.degElevation;
			
				x1 = cos(az1 * c_dDegToRad) * cos(el1 * c_dDegToRad);
				y1 = sin(az1 * c_dDegToRad) * cos(el1 * c_dDegToRad);
				z1 = sin(el1 * c_dDegToRad);

				for( ULONG itest2 = itest1+1; itest2 < m_ulPassListCount; itest2++)
				{
					ipass2 = m_lpPassList[ itest2 ];
					
					// Check if same downlink
					double dFreq1 =  m_lpPassArray[ipass1].dFrequency; // frequency in MHz
					double dFreq2 =  m_lpPassArray[ipass2].dFrequency;
					bool bFreqOK  = ( fabs(dFreq1-dFreq2) < 0.250 );
					
					if( !_CheckFlag( ipass2, PASS_ANTENNA_ELEVATION_FLAG ) && bFreqOK )
					{
						az2 = m_lpPassArray[ipass2].azelEnd.degAzimuth;
						el2 = m_lpPassArray[ipass2].azelEnd.degElevation;
			
						x2 = cos(az2 * c_dDegToRad) * cos(el2 * c_dDegToRad);
						y2 = sin(az2 * c_dDegToRad) * cos(el2 * c_dDegToRad);
						z2 = sin(el2 * c_dDegToRad);

						dSeparation = x1*x2 + y1*y2 + z1*z2;

						if ( dSeparation > dSeparationThreshold )
						{
							_SetFlag( ipass1, PASS_ANTENNA_BEAMWIDTH_FLAG );
							_SetFlag( ipass2, PASS_ANTENNA_BEAMWIDTH_FLAG );
						}
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------------------

void 
CPassSchedulerJDOP::_CheckElevationAngle()
{
	for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
	{
		ULONG iant = _FindAntennaIndex( m_lpPassArray[ipass].ulAntennaID );
		
		// Check minimum elevation angle
		if ( m_lpPassArray[ipass].azelEnd.degElevation < m_lpAntArray[iant].dMinElevation )
		{
			_SetFlag( ipass, PASS_ANTENNA_ELEVATION_FLAG );
		}
	}

}
//-------------------------------------------------------------------------------------------------------------


double
CPassSchedulerJDOP::_JDOP( EMSVECTORD vBeacon )
{

	double dJDOP = 0;
	EMS_RESULT hr = EMS_OK;

	// Estable partial derivatives

	EMSRANGERATED rangeRate;
	EMSRANGERATED rangeRateX;
	EMSRANGERATED rangeRateY;
	EMSRANGERATED rangeRateZ;
	EMSTIMECOORDD vSatellite;
	ULONG         index;

	m_ulIndexCount = m_ulAntennaCount;

	for( ULONG i = 0; i < m_ulIndexCount; i++ )
	{
		index = m_CombinationIndex[i];

		if( index < m_ulPassCount )
		{
			vSatellite = m_lpPassArray[index].satvect;

			hr = CEMSRangeRate::Calculate( vBeacon, &vSatellite, 1, &rangeRate );

			vBeacon.dX += 1.0;
			hr = CEMSRangeRate::Calculate( vBeacon, &vSatellite, 1, &rangeRateX );
			vBeacon.dX -= 1.0;
		
			vBeacon.dY += 1.0;
			hr = CEMSRangeRate::Calculate( vBeacon, &vSatellite, 1, &rangeRateY );
			vBeacon.dY -= 1.0;
		
			vBeacon.dZ += 1.0;
			hr = CEMSRangeRate::Calculate( vBeacon, &vSatellite, 1, &rangeRateZ );
			vBeacon.dZ -= 1.0;

			m_X[i][0] = rangeRateX.dRange - rangeRate.dRange;
			m_X[i][1] = rangeRateY.dRange - rangeRate.dRange;
			m_X[i][2] = rangeRateZ.dRange - rangeRate.dRange;
		
			m_Y[i][0] = m_JDOPfactor * (rangeRateX.dRangeRate - rangeRate.dRangeRate);
			m_Y[i][1] = m_JDOPfactor * (rangeRateY.dRangeRate - rangeRate.dRangeRate);
			m_Y[i][2] = m_JDOPfactor * (rangeRateZ.dRangeRate - rangeRate.dRangeRate);
		}
	}

	double A[3][3];
	double B[3][3];

	for( ULONG i = 0; i < 3; i++ )
	{
		for( ULONG j = 0; j < 3; j++ )
		{
			A[i][j] = 0;
			B[i][j] = 0;

			for( ULONG k = 0; k < m_ulIndexCount; k++ )
			{
				A[i][j] += m_X[k][i] * m_X[k][j]; 
				B[i][j] += m_Y[k][i] * m_Y[k][j];
			}
		}
	}

	for( ULONG i = 0; i < 3; i++ )
	{
		for( ULONG j = 0; j < 3; j++ )
		{
			A[i][j] += B[i][j];
		}
	}

	// Compute 3x3 matrix inverse
	double det = 0;

	det  = A[0][0] * A[1][1] * A[2][2];
	det += A[1][0] * A[2][1] * A[0][2];
	det += A[2][0] * A[0][1] * A[1][2];
	det -= A[0][0] * A[2][1] * A[1][2];
	det -= A[2][0] * A[1][1] * A[0][2];
	det -= A[1][0] * A[0][1] * A[2][2];

	dJDOP  = A[1][1] * A[2][2] - A[1][2] * A[1][2];
	dJDOP += A[0][0] * A[2][2] - A[0][2] * A[2][0];
	dJDOP += A[0][0] * A[1][1] - A[0][1] * A[1][0];

	dJDOP /= det;

	return dJDOP;
}

//-------------------------------------------------------------------------------------------------------------

LONG
CPassSchedulerJDOP::_FindAntennaIndex ( ULONG ulAntennaID )
{
	LONG index = -1;
	for( ULONG iant = 0; iant < m_ulAntennaCount; iant++ )
	{
		if ( ulAntennaID == m_lpAntArray[iant].ulAntennaID )
		{
			index = iant;
			break;
		}
	}
	return index;
}

//-------------------------------------------------------------------------------------------------------------

LONG
CPassSchedulerJDOP::_FindSatelliteIndex ( ULONG ulSatID )
{
	LONG index = -1;
	for( ULONG isat = 0; isat < m_ulSatelliteCount; isat++ )
	{
		if ( ulSatID == m_lpSatArray[isat].ulSatID )
		{
			index = isat;
			break;
		}
	}
	return index;
}

//-------------------------------------------------------------------------------------------------------------
LONG
CPassSchedulerJDOP::_FindPassIndex ( ULONG ulAntennaID, ULONG ulSatID )
{
	LONG index = -1;
	for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
	{
		if ( (ulSatID == m_lpPassArray[ipass].ulSatID) && (ulAntennaID == m_lpPassArray[ipass].ulAntennaID) )
		{
			index = ipass;
			break;
		}
	}
	return index;
}

//-------------------------------------------------------------------------------------------------------------

EMSAZELVECTORD
CPassSchedulerJDOP::_GetAzimuthElevation(  EMSTIMECOORDD vCoord, EMSLOCATION siteLocation )
{

	EMSAZELVECTORD  vAzEl;

	memset( &vAzEl, 0, sizeof(EMSAZELVECTORD) );
	//if ( vCoord > 0 && siteLocation > 0)
	{
		CEMSCoordSystem CS;
		EMSVECTORD      vDiff;
		EMSVECTORD      vObserver;
		EMSENUVECTORD   vENU;

		vObserver = CS.ToEarthFixedDouble( siteLocation );

		vDiff.dX = vCoord.coord.radius.dX - vObserver.dX;
		vDiff.dY = vCoord.coord.radius.dY - vObserver.dY;
		vDiff.dZ = vCoord.coord.radius.dZ - vObserver.dZ;

		double dSinLatitude = sin( siteLocation.degLatitude * c_dDegToRad );
		double dCosLatitude = cos( siteLocation.degLatitude * c_dDegToRad );
		double dSinLongitude = sin( siteLocation.degLongitude * c_dDegToRad );
		double dCosLongitude = cos( siteLocation.degLongitude * c_dDegToRad );

		vENU.dNorth = -(( dSinLatitude * dCosLongitude * vDiff.dX ) +
						( dSinLatitude * dSinLongitude * vDiff.dY ) -
						( dCosLatitude * vDiff.dZ ) );

		vENU.dEast  =  (( -dSinLongitude * vDiff.dX ) +
						( dCosLongitude * vDiff.dY ) );

		vENU.dUp    =  (( dCosLatitude * dCosLongitude * vDiff.dX ) +
						( dCosLatitude * dSinLongitude * vDiff.dY ) +
						( dSinLatitude * vDiff.dZ ) );


		vAzEl = CS.ToAzimuthAndElevation( vENU );

	}

	return vAzEl;
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CPassSchedulerJDOP::_NchooseK( ULONG N, ULONG K )
{
	ULONG nCombinations = 0;
	if( K <= N && K > 0 )
	{
		double dN = 1;
		double dK = 1;
		for( ULONG i = N; i > N-K; i--) dN *= i;
		for( ULONG i = 1; i < K+1; i++) dK *= i;
		nCombinations = ULONG (dN / dK);
	}
	return nCombinations;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT
CPassSchedulerJDOP::_SetPass( ULONG index )
{
	EMS_RESULT hr = EMS_OK;

	if ( _CheckFlag( index, PASS_SCHEDULE_FLAG ) )
	{
		_ResetFlag( index, PASS_SCHEDULE_FLAG );
		_SetFlag( index, PASS_START_FLAG | PASS_CURRENT_FLAG );
		_ResetFlag( index, PASS_REDUNDENT_FLAG | PASS_SUPPRESS_FLAG );

		m_lpPassArray[index].azelStart = m_lpPassArray[index].azelEnd;
		m_lpPassArray[index].startPass = m_lpPassArray[index].endPass;
		m_lpPassArray[index].azelMaxEl = m_lpPassArray[index].azelEnd;
		m_lpPassArray[index].maxElPass = m_lpPassArray[index].endPass;
		m_lpPassArray[index].azelMinEl = m_lpPassArray[index].azelEnd;
		m_lpPassArray[index].minElPass = m_lpPassArray[index].endPass;

		// Find all corresponding antenna and satellite records and set their status to 'unavailable'
		ULONG ulAntennaID = m_lpPassArray[index].ulAntennaID;
		ULONG ulSatID     = m_lpPassArray[index].ulSatID;

		for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
		{
			if ( !( ipass == index ) )
			{
				if ( ulAntennaID == m_lpPassArray[ipass].ulAntennaID )
				{
					_SetFlag( ipass, PASS_SUPPRESS_FLAG );
					_ResetFlag( ipass, PASS_SCHEDULE_FLAG | PASS_CURRENT_FLAG );
				}
				if ( ulSatID == m_lpPassArray[ipass].ulSatID )
				{
					if( !_CheckFlag( ipass, PASS_CURRENT_FLAG ) )
					{
						_SetFlag( ipass, PASS_REDUNDENT_FLAG );
					}
				}
			}
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT
CPassSchedulerJDOP::_ResetPass( ULONG index )
{
	EMS_RESULT hr = EMS_OK;
	//if( index == 0 )
	//{
	//	int x = 1;
	//}


	m_lpPassArray[index].azelStart = m_lpPassArray[index].azelEnd;
	m_lpPassArray[index].startPass = m_lpPassArray[index].endPass;
	m_lpPassArray[index].azelMaxEl = m_lpPassArray[index].azelEnd;
	m_lpPassArray[index].maxElPass = m_lpPassArray[index].endPass;
	m_lpPassArray[index].azelMinEl = m_lpPassArray[index].azelEnd;
	m_lpPassArray[index].minElPass = m_lpPassArray[index].endPass;

	if ( _CheckFlag( index, PASS_CURRENT_FLAG ) )
	{
		// Find all corresponding antenna and satellite records and set their status to 'available' and restart their pass data
		ULONG ulAntennaID = m_lpPassArray[index].ulAntennaID;
		ULONG ulSatID     = m_lpPassArray[index].ulSatID;
		
		for( ULONG ipass = 0; ipass < m_ulPassCount; ipass++ )
		{
			if ( !( ipass == index ) )
			{
				bool bRestart = false;
				if ( ulAntennaID == m_lpPassArray[ipass].ulAntennaID )
				{
					bRestart = true;
				}
				if ( ulSatID == m_lpPassArray[ipass].ulSatID )
				{
					if( !_CheckFlag( ipass, PASS_CURRENT_FLAG ) )
					{
						bRestart = true;
					}
				}
				if ( bRestart )
				{
					_ResetFlag( ipass, PASS_MASK_TYPE );
					m_lpPassArray[ipass].azelStart = m_lpPassArray[ipass].azelEnd;
					m_lpPassArray[ipass].startPass = m_lpPassArray[ipass].endPass;
					m_lpPassArray[ipass].azelMaxEl = m_lpPassArray[ipass].azelEnd;
					m_lpPassArray[ipass].maxElPass = m_lpPassArray[ipass].endPass;
					m_lpPassArray[ipass].azelMinEl = m_lpPassArray[ipass].azelEnd;
					m_lpPassArray[ipass].minElPass = m_lpPassArray[ipass].endPass;
				}
			}
		}
	}

	_ResetFlag( index, PASS_MASK_TRACK );

	return hr;
}

//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_FillPassList( ULONG ulFLAG, bool bUpdate )
{

	ULONG ulCount = 0;
	ULONG ulMaxCount = m_ulPassListCount;
	ULONG ipass = 0;

	if ( !bUpdate )
	{
		memset( m_lpPassList, 0, sizeof(ULONG) * m_ulPassCount );
		ulMaxCount = m_ulPassCount;
	}
	for( ULONG i = 0; i < ulMaxCount; i++ )
	{
		if (bUpdate )
		{
			ipass = m_lpPassList[ i ];
		}
		else
		{
			ipass = i;
		}
		if ( _CheckMask( ipass , ulFLAG ) )
		{
			m_lpPassList[ ulCount ] =  ipass;
			ulCount++;
		}
	}
	m_ulPassListCount = ulCount;

}

//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_RemovePassList( ULONG ulFLAG, bool bUpdate )
{

	ULONG ulCount = 0;
	ULONG ulMaxCount = m_ulPassListCount;
	ULONG ipass = 0;

	if ( !bUpdate )
	{
		memset( m_lpPassList, 0, sizeof(ULONG) * m_ulPassCount );
		ulMaxCount = m_ulPassCount;
	}
	for( ULONG i = 0; i < ulMaxCount; i++ )
	{
		if (bUpdate )
		{
			ipass = m_lpPassList[ i ];
		}
		else
		{
			ipass = i;
		}
		if ( !_CheckMask( ipass , ulFLAG ) )
		{
			m_lpPassList[ ulCount ] =  ipass;
			ulCount++;
		}
	}
	m_ulPassListCount = ulCount;

}

//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_FillSatPassList( ULONG ulSatID, bool bUpdate )
{

	ULONG ulCount = 0;
	ULONG ulMaxCount = m_ulPassListCount;
	ULONG ipass = 0;

	if ( !bUpdate )
	{
		memset( m_lpPassList, 0, sizeof(ULONG) * m_ulPassCount );
		ulMaxCount = m_ulPassCount;
	}
	for( ULONG i = 0; i < ulMaxCount; i++ )
	{
		if (bUpdate )
		{
			ipass = m_lpPassList[ i ];
		}
		else
		{
			ipass = i;
		}
		if ( m_lpPassArray[ ipass ].ulSatID  == ulSatID )
		{
			m_lpPassList[ ulCount ] =  ipass;
			ulCount++;
		}
	}
	m_ulPassListCount = ulCount;

}

//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_FillAntPassList( ULONG ulAntennaID, bool bUpdate )
{

	ULONG ulCount = 0;
	ULONG ulMaxCount = m_ulPassListCount;
	ULONG ipass = 0;

	if ( !bUpdate )
	{
		memset( m_lpPassList, 0, sizeof(ULONG) * m_ulPassCount );
		ulMaxCount = m_ulPassCount;
	}
	for( ULONG i = 0; i < ulMaxCount; i++ )
	{
		if (bUpdate )
		{
			ipass = m_lpPassList[ i ];
		}
		else
		{
			ipass = i;
		}
		if ( m_lpPassArray[ ipass ].ulAntennaID  == ulAntennaID )
		{
			m_lpPassList[ ulCount ] =  ipass;
			ulCount++;
		}
	}
	m_ulPassListCount = ulCount;


}


//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_SetFlag( ULONG index, ULONG ulFLAG )
{
	if ( index < m_ulPassCount )
		m_lpPassArray[ index ].ulStatus |= ulFLAG;
}

//-------------------------------------------------------------------------------------------------------------

void
CPassSchedulerJDOP::_ResetFlag( ULONG index, ULONG ulFLAG )
{
	if ( index < m_ulPassCount )
		m_lpPassArray[ index ].ulStatus &= ~ulFLAG;
}

//-------------------------------------------------------------------------------------------------------------

bool
CPassSchedulerJDOP::_CheckFlag( ULONG index, ULONG ulFLAG )
{
	bool bOK = false;
	if ( index < m_ulPassCount )
	{
		bOK = ( (m_lpPassArray[ index ].ulStatus & ulFLAG) == ulFLAG );
	}
	return bOK;
}

//-------------------------------------------------------------------------------------------------------------

bool
CPassSchedulerJDOP::_CheckMask( ULONG index, ULONG ulMASK )
{
	bool bOK = false;
	if ( index < m_ulPassCount )
	{
		bOK = ( m_lpPassArray[ index ].ulStatus & ulMASK );
	}
	return bOK;
}
//-------------------------------------------------------------------------------------------------------------

bool
CPassSchedulerJDOP::_CheckLastMask( ULONG index, ULONG ulMASK )
{
	bool bOK = false;
	if ( index < m_ulPassCount )
	{
		bOK = ( m_lpPassArray[ index ].ulLastStatus & ulMASK );
	}
	return bOK;
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CPassSchedulerJDOP::_GetAllCombinations( ULONG N, ULONG K )
{
	ULONG ulCombinations = _NchooseK( N, K );

	if( ulCombinations >= MAXCOMBINATIONS )
	{
		ulCombinations = MAXCOMBINATIONS-1; // Allow one less and fill last one with all zeros
	}

	// Initialize
	for( ULONG i = 0; i < K; i++ )
	{
		m_AllCombinations[0][i] = i;
	}

	for( ULONG i = 1; i < ulCombinations; i++ )
	{
		for( ULONG j = 0; j < K; j++ )
		{
			m_AllCombinations[i][j] = m_AllCombinations[i-1][j];
			m_AllCombinations[i+1][j] = 0;
		}
		m_AllCombinations[i][K-1] += 1;

		for( ULONG j = K-1; j > 0; j-- )
		{
			if ( m_AllCombinations[i][j] > N - (K - j) )
			{
				m_AllCombinations[i][j-1] += 1;
				for( ULONG j1 = j; j1 < K; j1++ )
				{
					m_AllCombinations[i][j1] = m_AllCombinations[i][j1-1] + 1;
				}
			}
		}
			
	}
	return ulCombinations;
}

//-------------------------------------------------------------------------------------------------------------

EMS_RESULT 
CPassSchedulerJDOP::OutputTrace()
{
	EMS_RESULT hr = EMS_OK;

	//FILE *lpOUTPUT = fopen("C:\\temp\\TrackingPlanTrace.csv","a+t");


	//if ( lpOUTPUT )
	if ( m_lpTraceFile )
	{
		
		memset( m_CombinationIndex, 0, MAXANT );

		int iant = 0;
 		
		//Note: combination data stored in Antenna ID order
		for( int ipass = 0; ipass < m_ulPassCount; ipass++ )
		{
			if(_CheckFlag( ipass, PASS_CURRENT_FLAG ) )
			{
				m_CombinationIndex[iant++] = ipass;
			}
		}

		// Compute JDOP for current time
		double dJDOP = 0.0;
		for( ULONG itest = 0; itest < m_ulTestCount; itest++ )
		{
			dJDOP += _JDOP( m_lpTestXYZ[itest] );
		}

		dJDOP /= m_ulTestCount;

		std::string szDateTime;
		szDateTime = _ConvertToDateTimeString( m_lpPassArray[ 0 ].satvect.vTime );
		fprintf( m_lpTraceFile, "%s,%d,%f,", szDateTime.c_str(), iant, dJDOP );

		for( int i = 0; i < m_ulAntennaCount; i++ )
		{
			int ipass = m_CombinationIndex[i];

			if ( m_lpPassArray[ ipass ].ulAntennaID == m_lpAntArray[ i ].ulAntennaID )
			{
				fprintf( m_lpTraceFile, "%X, %02d, %03d, %6.2f, %5.2f,",
					m_lpPassArray[ ipass ].ulStatus,
					m_lpPassArray[ ipass ].ulAntennaID,
					m_lpPassArray[ ipass ].ulSatID,
					m_lpPassArray[ ipass ].azelEnd.degAzimuth,
					m_lpPassArray[ ipass ].azelEnd.degElevation);
			}
			else
			{
				fprintf( m_lpTraceFile, ", %02d,,,,",
					m_lpPassArray[ ipass ].ulStatus,
					m_lpAntArray[ i ].ulAntennaID );
			}
		}
		fprintf( m_lpTraceFile, "\n" );
	}

	return hr;

}

//-------------------------------------------------------------------------------------------------------------

std::string
CPassSchedulerJDOP::_ConvertToDateTimeString( EMSTIME t )
{
	
	char cDateTime[18] = "xxxx/xxx xx:xx:xx";	
	EMSTIMEFIELDS timeFields;
	CEMSTime timeNow( t );

	timeNow.GetTime( &timeFields );
	sprintf( cDateTime, "%04d/%03d %02d:%02d:%02d",
	timeFields.nYear, timeFields.nJulianDay,
	timeFields.nHour, timeFields.nMinute, timeFields.nSecond );


	return cDateTime;
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CPassSchedulerJDOP::_AddtoList( ULONG item, LONG *lpList, ULONG nSize )
{
	ULONG nCount = nSize;
	if ( lpList )
	{
		bool bOK = false;
		for( int i = 0; i < nSize; i++ )
		{
			if( item == lpList[ i ] )
			{
				bOK = true;
				break;
			}
		}
		if( !bOK ) lpList[ nCount++ ] = item;
	}
	return nCount;
}

//-------------------------------------------------------------------------------------------------------------

ULONG
CPassSchedulerJDOP::_RemovefromList( ULONG item, LONG *lpList, ULONG nSize )
{
	ULONG nCount = nSize;
	if ( lpList )
	{
		bool bOK = false;
		for( int i = 0; i < nSize; i++ )
		{
			if( item == lpList[ i ] )
			{
				bOK = true;
				for( int j = i; j < nSize-1; j++ )
				{
					lpList[ j ] = lpList[ j+1 ];
				}
				break;
			}
		}
		if( bOK ) nCount--;
	}
	return nCount;
}

