/********************************************************************
*	Module:			EMSGPSEphem.cpp 
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

	0.0	2006/12/06	rvw 	start

********************************************************************/
#include <math.h>
#include <string.h>
#include <io.h>

#define DEBUG_GPS_DATA
#define EMSERROR_NODEFINE_TYPES

#include "EMSGPSEphem.h"
#include "EMSGPSConvert.h"
#include "emstleconv.h"
#include "emsconst.h"
#include "gpsephem.h"		// EMSGPSEPHEMERISDATA
#include "emsclock.h"		// CEMSSystemClock

#define DMOD(a,b)      ((a) - (long int)((a)/(b)) * (b))

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CEMSGPSEphemeris::CEMSGPSEphemeris( )
{
	m_lpSatInfo = 0;
	m_lpOrbit = 0;

	memset( m_ulSats, 0, sizeof(m_ulSats));
	m_ulSatCount = 0;
	m_ulSatIndex = 0;;

	ResetSatellites( );
}

CEMSGPSEphemeris::~CEMSGPSEphemeris( )
{
}

EMS_RESULT CEMSGPSEphemeris::Initialize( IEMSSatelliteInfo *lpSatInfo, IEMSOrbit *lpOrbit )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpSatInfo )
		lpSatInfo->AddRef( );
	else
	{
		// CoCreate
	}

	if ( m_lpSatInfo )
	{
		m_lpSatInfo->Release( );
		m_lpSatInfo = NULL;
	}

	m_lpSatInfo = lpSatInfo;

	if ( m_lpOrbit )
	{
		m_lpOrbit->Release( );
		m_lpOrbit = NULL;
	}

	if ( lpOrbit )
		hr = lpOrbit->QueryInterface( IID_IEMSOrbit4, (void**) &m_lpOrbit );
	else
	{
		// CoCreate
	}

	return hr;
}

void CEMSGPSEphemeris::Reset( void )
{
	if ( m_lpSatInfo )
	{
		m_lpSatInfo->Release( );
		m_lpSatInfo = 0;
	}

	if ( m_lpOrbit )
	{
		m_lpOrbit->Release( );
		m_lpOrbit = 0;
	}
}

void CEMSGPSEphemeris::ResetSatellites( void )
{
	m_ulSatCount = m_ulSatIndex = 0;

	memset( m_ulSats, 0, sizeof( m_ulSats ) );
}

EMS_RESULT CEMSGPSEphemeris::SetSatellites( ULONG *lpulSats, ULONG ulCount )
{
	EMS_RESULT hr = EMS_OK;

	ResetSatellites( );

	if ( lpulSats && ulCount )
	{
		for ( int i = 0; ( i < (int)ulCount ) && ( i < EMS_MAX_SATELLITES ); i++ )
		{
			m_ulSats[ i ] = lpulSats[ i ];

			m_ulSatCount++;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSGPSEphemeris::SetSatellites( void )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		ResetSatellites( );
	
		if ( m_lpSatInfo )
		{
			ULONG ulNoradID = 0;

			for ( int i = c_nMinGpsSatID; i <= c_nMaxGpsSatID; i++ )
			{
				EMS_RESULT hrLocal = m_lpSatInfo->GetNoradID( i, &ulNoradID );
			
				if ( ( EMS_OK == hrLocal ) && ulNoradID && ( m_ulSatCount < EMS_MAX_SATELLITES ) )
				{
					m_ulSats[ m_ulSatCount++ ] = i;
				}
			}
		}
		else
			hr = EMS_NO_SATINFO_OBJ;
	}

	catch (...)
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


bool CEMSGPSEphemeris::IsGpsSatConfigured( ULONG ulSatId )
{
	bool	bFound = false;
	WORD	i;

	for ( i=0; i < m_ulSatCount; i++ )
	{
		if ( m_ulSats[i] == ulSatId )
			bFound = true;
	}

	return bFound;
}


ULONG CEMSGPSEphemeris::_GetOrbitNumber( ULONG ulSatID, EMSTIME timeOrbitNumber )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulOrbitNumber = 0;

	if ( m_lpOrbit )
	{
		hr = m_lpOrbit->GetOrbitNumber( ulSatID, timeOrbitNumber, &ulOrbitNumber );

		if ( EMS_OK != hr )
			ulOrbitNumber = 0;
	}

	return ulOrbitNumber;
}


EMS_RESULT CEMSGPSEphemeris::TLEosc2TLEmean(LPEMSTLERECORD lpTLERecord )
{

	EMS_RESULT hr = EMS_OK;

	if ( lpTLERecord && m_lpOrbit )
	{

		EMSTIMECOORDD timeCoord;

		EMSTLEDATA2 tleData2;
		EMSTLEDATA  tleDataIN;
		EMSTLEDATA  tleDataOUT;

		ULONG ulSatID = lpTLERecord->ulSatID;

		hr = CEMSTLEConvert::TLERecordToTLEData2( &tleData2, lpTLERecord ); 

		tleDataIN = tleData2.tle;

		hr = CEMSTLEConvert::TLEosc2EF( &tleDataIN, &timeCoord );

		hr = m_lpOrbit->ConvertOrbitVectorToTLEDouble( ulSatID, timeCoord, &tleDataOUT );

		tleData2.tle = tleDataOUT;

		hr = CEMSTLEConvert::TLEData2toTLERecord( lpTLERecord, &tleData2, ulSatID );
		
		// Set range from 0 to 360
		lpTLERecord->fMeanAnomaly = DMOD(lpTLERecord->fMeanAnomaly, 360.0);
		if ( lpTLERecord->fMeanAnomaly < 0.0 ) lpTLERecord->fMeanAnomaly += 360.0;

		lpTLERecord->fArgPerigee = DMOD(lpTLERecord->fArgPerigee, 360.0);
		if ( lpTLERecord->fArgPerigee < 0.0 ) lpTLERecord->fArgPerigee += 360.0;

		lpTLERecord->fRightAscNode = DMOD(lpTLERecord->fRightAscNode, 360.0);
		if ( lpTLERecord->fRightAscNode < 0.0 ) lpTLERecord->fRightAscNode += 360.0;
	}

	else
		hr = EMS_BAD_PARAM;


	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

