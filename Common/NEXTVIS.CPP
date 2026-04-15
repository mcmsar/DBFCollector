/*******************************************************************
*	Module:			NextVis.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSNextVisibility class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:		
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003 Feb 7	rvw	start

********************************************************************/
#include <windows.h>
#include <math.h>

#include "nextvis.h"
#include "emsclock.h"
#include "emsconst.h"
#include "emsvectr.h"

#define sind( a ) sin( a * c_dDegToRad )
#define cosd( a ) cos( a * c_dDegToRad )
#define tand( a ) tan( a * c_dDegToRad )
#define acosd( a ) ( acos( a ) * c_dRadToDeg )
#define asind( a ) ( asin( a ) * c_dRadToDeg )
#define atand( a ) ( atan( a ) * c_dRadToDeg )
#define atan2d( a, b ) ( atan2( a, b ) * c_dRadToDeg )


const double c_dMinMinutesInView = ( 50.0 * 3 ) / 60.0; // min 3 bursts??

const int cnScheduleDuration = 2;	// days
//const ULONG culMaxScheduleSize = 200;
const ULONG culMaxScheduleSize = 32;
const INT64 ctimeOverlapTolerance = 2*60* (INT64) 1000000000;	// 2 minutes in nanoseconds

CEMSNextVisibility::CEMSNextVisibility()
{
	m_lpPassSchedObj = 0;
	m_lpPassInfo = 0;
	m_ulPassCount = 0;
	m_lpSatInfo = 0;
	m_lpOrbit = 0;

	memset( &m_lutLocation, 0, sizeof( m_lutLocation ) );

	m_dMinElevation = 5.0;

	m_dMinDurationMinutes = 2.0;

	_ResetSatList();
}

CEMSNextVisibility::~CEMSNextVisibility()
{
	Reset();
}

EMS_RESULT CEMSNextVisibility::Initialize( IEMSPassSchedule *lpPassSchedObj,
								IEMSSatelliteInfo	*lpSatInfo, IEMSOrbit *lpOrbit )

{
	EMS_RESULT hr = EMS_OK;

	if (lpPassSchedObj )
		SetPassScheduleObject( lpPassSchedObj );

	if ( lpOrbit )
		lpOrbit->AddRef();

	if ( m_lpOrbit )
		m_lpOrbit->Release();

	m_lpOrbit = lpOrbit;

	if ( lpSatInfo )
		lpSatInfo->AddRef();

	if ( m_lpSatInfo )
		m_lpSatInfo->Release();

	m_lpSatInfo = lpSatInfo;


	return hr;
}

void CEMSNextVisibility::_ResetPassSchedule( void )
{
	if ( m_lpPassInfo )
	{
		delete [] m_lpPassInfo;
		m_lpPassInfo = 0;
	}

	m_ulPassCount = 0;
}

void CEMSNextVisibility::_ResetSatList( void )
{
	m_ulSatCount = 0;
	memset( m_ulSatList, 0, sizeof( m_ulSatList ) );
}

void CEMSNextVisibility::_UpdateSatList( void )
{
	_ResetSatList();

	if ( m_lpPassInfo )
	{
		for ( ULONG i = 0; i < m_ulPassCount; i++ )
		{	
			bool bFound = false;

			for ( int j = 0; ( j < (int)m_ulSatCount) && !bFound; j++ )
			{
				if ( m_ulSatList[ j ] == m_lpPassInfo[ i ].ulSatelliteID )
					bFound = true;
			}

			if ( !bFound && ( m_ulSatCount < c_nNextVisMaxSatellites ) )
				m_ulSatList[ m_ulSatCount++ ] = m_lpPassInfo[ i ].ulSatelliteID;
		}
	}
}

EMS_RESULT CEMSNextVisibility::_AllocPassSchedule( ULONG ulCount )
{
	EMS_RESULT hr = EMS_OK;

	_ResetPassSchedule( );

	if ( ulCount )
	{
		m_lpPassInfo = new EMSSATELLITEPASS [ ulCount ];
		
		if ( m_lpPassInfo )
		{
			memset( m_lpPassInfo, 0, sizeof( EMSSATELLITEPASS ) * ulCount );

			m_ulPassCount = ulCount;
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_AllocRecord( ULONG& ulNextSlot )
{
	EMS_RESULT hr = EMS_OK;

	if( 0 == m_ulPassCount || !m_lpPassInfo )
	{
		hr = _AllocPassSchedule( 1 );	

		ulNextSlot = 0;
	}
	else
	{
		ULONG ulNewSize = m_ulPassCount + 1;
		EMSSATELLITEPASS* aPassTemp = new EMSSATELLITEPASS[ ulNewSize ];
		if( aPassTemp )
		{
			memset( aPassTemp, 0, sizeof( EMSSATELLITEPASS )*ulNewSize );

			memcpy( aPassTemp, m_lpPassInfo, sizeof( EMSSATELLITEPASS )*m_ulPassCount );
			
			delete[] m_lpPassInfo;
			m_lpPassInfo = aPassTemp;
			
			ulNextSlot = m_ulPassCount;
			m_ulPassCount = ulNewSize;
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}
	}

	return hr;
}

EMS_RESULT CEMSNextVisibility::Reset( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpPassSchedObj )
	{
		m_lpPassSchedObj->Release();
		m_lpPassSchedObj = 0;
	}

	_ResetPassSchedule( );

	if( m_lpSatInfo )
	{
		m_lpSatInfo->Release();
		m_lpSatInfo = 0;
	}

	if ( m_lpOrbit )
	{
		m_lpOrbit->Release();
		m_lpOrbit = 0;
	}

	return hr;
}

EMS_RESULT	CEMSNextVisibility::SetCurrentPassSchedule(  CEMSSit260A *lpPassSched )
{
	EMS_RESULT hr = EMS_OK;

	_ResetPassSchedule();

	if ( lpPassSched && lpPassSched->GetSatelliteCount() )
	{
		// First, omit suppressed passes.
		ULONG ulTotalPasses = 0;
		for( int i = 0; i < lpPassSched->GetSatelliteCount( ); i++ )
		{
			EMSSIT260DATA* lpData = lpPassSched->GetPass( i );

			if( lpData )
			{
				if( EMS_PASSFLAG_PROCESS == (lpData->wPassSchedStatus & EMS_PASSFLAG_PROCESS) )
				{
					ulTotalPasses++;
				}
			}
		}

		hr = _AllocPassSchedule( ulTotalPasses );

		if ( ( hr == EMS_OK ) && m_lpPassInfo )
		{
			EMSSIT260DATA *lpData = 0;

			long lCurrent = 0;
			for ( int i = 0; i < lpPassSched->GetSatelliteCount( ); i++ )
			{
				lpData = lpPassSched->GetPass( i );		
				
				if ( lpData )
				{
					if( EMS_PASSFLAG_PROCESS == (lpData->wPassSchedStatus & EMS_PASSFLAG_PROCESS) )
					{
						m_lpPassInfo[lCurrent].ulSatelliteID = lpData->ulSatID;
						m_lpPassInfo[lCurrent].ulFlags = 0;
						m_lpPassInfo[lCurrent].ulOrbitNumber = lpData->ulOrbitNumber;
						m_lpPassInfo[lCurrent].timeAOS = lpData->timeAOS;
						m_lpPassInfo[lCurrent].timeLOS = lpData->timeLOS;
						m_lpPassInfo[lCurrent].timePeak.intTime = 0;			// not available in SIT
						m_lpPassInfo[lCurrent].degMaxElevation = lpData->degMaxElevation;
						m_lpPassInfo[lCurrent].degMinElevation = 0;			// not available in SIT
						m_lpPassInfo[lCurrent].degAzimuthAOS = lpData->degAzimuthAOS;
						m_lpPassInfo[lCurrent].degAzimuthLOS = lpData->degAzimuthLOS;
						lCurrent++;
					}
				}
			}
		}
	}
	else
		_ResetPassSchedule();

	_UpdateSatList();

	return hr;
}

EMS_RESULT	CEMSNextVisibility::SetCurrentPassSchedule(  EMSSATELLITEPASS *lpPassInfo, int nPassCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpPassInfo && nPassCount )
	{
		hr = _AllocPassSchedule( nPassCount );

		if ( ( hr == EMS_OK ) && m_lpPassInfo )
		{
			for ( int i = 0; i < nPassCount; i++ )
				memcpy( &(m_lpPassInfo[i]), &(lpPassInfo[i]), sizeof(EMSSATELLITEPASS) );
		}
	}
	else
		_ResetPassSchedule( );

	_UpdateSatList();

	return hr;
}

EMS_RESULT CEMSNextVisibility::SetPassScheduleObject( IEMSPassSchedule *lpPassSchedObj )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpPassSchedObj )
	{
		lpPassSchedObj->AddRef();

		if ( m_lpPassSchedObj )
			m_lpPassSchedObj->Release();

		m_lpPassSchedObj = lpPassSchedObj;
	}
	else
	{
		hr = _InitPassSchedObj();
	}

	return hr;
}

EMS_RESULT CEMSNextVisibility::AddPass( EMSSATELLITEPASS& passData )
{
	EMS_RESULT hr = EMS_OK;

	ULONG ulIndex = 0;
	hr = _AllocRecord( ulIndex );

	if( SUCCEEDED(hr) )
	{
		if( m_lpPassInfo )
		{
			m_lpPassInfo[ulIndex] = passData;
		}
		else
		{
			hr = EMS_NOT_INITIALIZED;
		}
	}

	return hr;
}

EMS_RESULT CEMSNextVisibility::CalculateNextVisibility( EMSLOCATION* pLocation, EMSTIME* pTime )
{
	EMS_RESULT hr = EMS_OK;
	BOOL bFound = FALSE;

	if( !pTime )
	{
		hr = EMS_INVALID_PTR;
	}
	else
	{
		pTime->intTime = 0;
	}

	if( m_lpPassInfo )	// The LUT's pass schedule must have been passed in to do the calculation.
	{
		EMSSATELLITEPASS aLocationPassTable[ culMaxScheduleSize ];

		memset( aLocationPassTable, 0, culMaxScheduleSize*sizeof(EMSSATELLITEPASS) );

		ULONG ulEntries = 0;

		hr = _GetLocationVisibilitySchedule( pLocation, culMaxScheduleSize, aLocationPassTable, ulEntries );

		if( SUCCEEDED(hr) )
		{
			for ( ULONG i = 0; !bFound && ( i < m_ulPassCount ); i++ )
			{
				ULONG ulSatID = m_lpPassInfo[i].ulSatelliteID;

				// Find this satellite in the Location pass table.
				EMSTIME timeLocationAOS;
				EMSTIME timeLocationLOS;
				timeLocationAOS.intTime = 0;
				timeLocationLOS.intTime = 0;

				hr = _FindVisibility( ulSatID, aLocationPassTable, ulEntries, timeLocationAOS, timeLocationLOS );

				if( SUCCEEDED(hr) )
				{
					if( timeLocationAOS.intTime > 0 && timeLocationLOS.intTime > 0 )
					{
						// This satellite does see the location.
						BOOL bHasSARP = _HasSARP( ulSatID );

						if( bHasSARP )
						{
							// SARP capability.

							// Is the location visible before or during the time the LUT is visible.
							if( m_lpPassInfo[i].timeLOS.intTime - timeLocationAOS.intTime >= ctimeOverlapTolerance )
							{
								if( m_lpPassInfo[i].timeAOS.intTime > timeLocationAOS.intTime )
								{
									pTime->intTime = m_lpPassInfo[i].timeAOS.intTime;
								}
								else
								{
									pTime->intTime = timeLocationAOS.intTime;
								}

								bFound = TRUE;
							}
						}
						else
						{
							// SARR only.

							// Is the location visible at the same time as the LUT?
							if( timeLocationAOS.intTime >= m_lpPassInfo[i].timeAOS.intTime &&
								timeLocationAOS.intTime <= m_lpPassInfo[i].timeLOS.intTime )
							{
								// Does the overlapping visibility fit our tolerance.
								if( m_lpPassInfo[i].timeLOS.intTime - timeLocationAOS.intTime >= ctimeOverlapTolerance )
								{
									// Set the next visibility time.
									pTime->intTime = timeLocationAOS.intTime;
									bFound = TRUE;
								}
							}
						}
					}
				}
			}
		}
	}

	return hr;
}


EMS_RESULT CEMSNextVisibility::_CheckPassX( EMSTIME *lpTimeFound, EMSSATELLITEPASS *lpPass, 
													EMSTIME timeLast, bool bRealTimeOnly )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTimeFound && lpPass )
	{
		ULONG ulSatID = lpPass->ulSatelliteID;
		EMSTIME timeBegin, timeEnd;

		if ( _HasSARP( ulSatID ) && !bRealTimeOnly )
			timeBegin = timeLast;
		else
			timeBegin = lpPass->timeAOS;

		timeEnd = lpPass->timeLOS;

		if ( timeEnd.intTime > timeBegin.intTime )
		{
			EMSSATELLITEPASS aLocationPassTable[ culMaxScheduleSize ];
			ULONG ulEntries = 0;

			memset( aLocationPassTable, 0, culMaxScheduleSize*sizeof(EMSSATELLITEPASS) );

			hr = _GenerateSchedule( culMaxScheduleSize, aLocationPassTable, ulEntries,
							ulSatID, timeBegin, timeEnd );

			if ( hr == EMS_OK )
			{
				CEMSTime timeSpan;
				double dMinutes;
				boolean bFound = false;

				for ( int i = 0; !bFound && ( i < (int)ulEntries ); i++ )
				{
					timeSpan.SetTime( aLocationPassTable[i].timeAOS );

					dMinutes = timeSpan.MinutesDifferent( aLocationPassTable[i].timeLOS );

					if ( dMinutes >= c_dMinMinutesInView )
					{
						bFound = true;

						*lpTimeFound = lpPass->timeAOS;
					}
				}
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_CheckPass( EMSLOCATION eltLocation, EMSTIME *lpTimeFound, EMSSATELLITEPASS *lpPass, 
													EMSTIME timeLast, bool bRealTimeOnly )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTimeFound && lpPass )
	{
		double dCTA = 0.0, dMaxElevation = 0.0;
		EMSTIME timeTCA;
		lpTimeFound->intTime = 0;

		hr = _Predict( eltLocation, m_lutLocation,
								lpPass, m_dMinElevation, m_dMinDurationMinutes,
								&timeTCA, &dCTA, &dMaxElevation );

		if ( hr == EMS_OK )
		{
			*lpTimeFound = lpPass->timeLOS;
		}
		else if ( hr == EMS_FALSE )
		{
			lpTimeFound->intTime = 0;
			hr = EMS_OK;
		}

	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMSTIME CEMSNextVisibility::_GetMostCurrentTimeCheckedForSat( ULONG ulSatID, EMSSATELLITEPASS *lpPass, int nIndex, EMSTIME timeLast )
{
	if ( lpPass )
	{
		for ( int i = 0; i < nIndex; i++ )
		{
			if ( lpPass[i].ulSatelliteID == ulSatID )
			{
				if ( lpPass[i].timeLOS.intTime > timeLast.intTime )
					timeLast = lpPass[i].timeLOS;
			}
		}
	}
	return timeLast;
}

EMS_RESULT CEMSNextVisibility::CalculateNextVisibility( EMSLOCATION* pLocation, EMSTIME* pTime, EMSTIME timeLast, bool bRealTimeOnly )
{
	EMS_RESULT hr = EMS_OK;
	BOOL bFound = FALSE;
	EMSTIME timeNext, timeNow = CEMSSystemClock::GetTime();

	memset( &timeNext, 0, sizeof( timeNext ) );

	if ( pTime && pLocation && m_lpPassInfo )
	{
		if ( timeLast.intTime == 0 )
			timeLast = CEMSSystemClock::GetTime();

		if ( hr == EMS_OK )
		{
			boolean bFound = false;

			for ( int i = 0; ( i < (int)m_ulPassCount ) && !bFound && ( hr == EMS_OK ); i++ )
			{
				// Make sure that pass is in the future
				if ( m_lpPassInfo[i].timeLOS.intTime > timeNow.intTime )
				{
					hr = _CheckPass( *pLocation, &timeNext, &m_lpPassInfo[i], timeLast, bRealTimeOnly );

					if ( hr == EMS_OK )
						bFound = ( timeNext.intTime > 0 );
				}
			}
		}

		*pTime = timeNext;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_SetLocationInPassSched( EMSLOCATION *lpLocation )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpLocation && m_lpPassSchedObj )
	{
		IEMSPassSchedule2* pSched = 0;

		hr = m_lpPassSchedObj->QueryInterface( IID_IEMSPassSchedule2, (void**) &pSched );

		if ( SUCCEEDED(hr) && pSched )
		{
			hr = pSched->SetLocation( *lpLocation );

			pSched->Release();
			pSched = 0;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_GetLocationVisibilitySchedule( EMSLOCATION* pLocation,
													ULONG ulMaxScheduleSize,
													EMSSATELLITEPASS* aLocationPassTable,
													ULONG& ulEntries )
{
	EMS_RESULT hr = EMS_OK;

	if( !pLocation )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		hr = _InitPassSchedObj();
	}

	if( SUCCEEDED(hr) )
	{
		IEMSPassSchedule2* pSched = 0;
		hr = m_lpPassSchedObj->QueryInterface( IID_IEMSPassSchedule2, (void**) &pSched );

		if( SUCCEEDED(hr) )
		{
			// Assuming that the pass schedule object was initialized with the satellites configured for this LUT.

			// Use default site profile (all zeros).

			hr = m_lpPassSchedObj->SetSatellites( m_ulSatCount, m_ulSatList );

			hr = pSched->SetLocation( *pLocation );
		}

		if( SUCCEEDED(hr) )
		{
			hr = _GenerateSchedule( ulMaxScheduleSize, aLocationPassTable, ulEntries );
		}

		if( pSched )
		{
			pSched->Release();
			pSched = 0;
		}
	}

	return hr;
}

EMS_RESULT
CEMSNextVisibility::_FindVisibility(	ULONG ulSatID,
										EMSSATELLITEPASS* aLocationPassTable,
										ULONG ulEntries,
										EMSTIME& timeLocationAOS,
										EMSTIME& timeLocationLOS )
{
	EMS_RESULT hr = EMS_OK;

	timeLocationAOS.intTime = 0;
	timeLocationLOS.intTime = 0;

	if( !aLocationPassTable )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		// Find the first occurrence of the satellite id in the location pass schedule table.
		BOOL bFound = FALSE;

		for( ULONG ul = 0; ul < ulEntries && !bFound ; ul++ )
		{
			if( aLocationPassTable[ul].ulSatelliteID == ulSatID )
			{
				timeLocationAOS.intTime = aLocationPassTable[ul].timeAOS.intTime;
				timeLocationLOS.intTime = aLocationPassTable[ul].timeLOS.intTime;

				bFound = TRUE;
			}
		}
	}

	return hr;
}

BOOL
CEMSNextVisibility::_HasSARP( ULONG ulSatID )
{
	// Determine whether the satellite has SARP capability.
	BOOL bHasSarp = FALSE;

	EMS_RESULT hr = _InitSatInfo();

	if( SUCCEEDED(hr) )
	{
		ULONG ulCaps = 0;
		hr = m_lpSatInfo->GetCaps( ulSatID, &ulCaps );

		if( SUCCEEDED(hr) )
		{
			if( (ulCaps & EMS_SATCAP_406_SARP) == EMS_SATCAP_406_SARP )
			{
				bHasSarp = TRUE;
			}
		}
	}

	return bHasSarp;

}

EMS_RESULT
CEMSNextVisibility::_InitSatInfo()
{
	EMS_RESULT hr = EMS_OK;

	if( !m_lpSatInfo )
	{
		hr = CoCreateInstance(	CLSID_EMSSatelliteInfo, 
								NULL, 
								CLSCTX_ALL, 
								IID_IEMSSatelliteInfo,
								(void**) &m_lpSatInfo );
	}

	return hr;
}


EMS_RESULT
CEMSNextVisibility::_InitPassSchedObj( )
{
	EMS_RESULT hr = EMS_OK;

	if( !m_lpPassSchedObj )
	{
		hr = CoCreateInstance(	CLSID_EMSPassSchedule, 
								NULL, 
								CLSCTX_ALL, 
								IID_IEMSPassSchedule, 
								(void**) &m_lpPassSchedObj );
	}

	return hr;
}

EMS_RESULT CEMSNextVisibility::_GenerateSchedule( ULONG ulMaxSize, EMSSATELLITEPASS* aPassSched, ULONG& ulActual, ULONG ulSatID, EMSTIME timeStart, EMSTIME timeEnd )
{
	EMS_RESULT hr = EMS_OK;

	if ( aPassSched )
	{
		if ( m_lpPassSchedObj )
		{
			hr = m_lpPassSchedObj->SetSatellites( 1, &ulSatID );

			hr = m_lpPassSchedObj->GenerateSchedule( timeStart, timeEnd );

			if ( hr == EMS_OK )
			{
					hr = m_lpPassSchedObj->GetSchedule( ulMaxSize, 
											aPassSched, 
											&ulActual, 
											&timeStart, 
											&timeEnd );

					if ( hr == EMS_PASS_NO_DATA )
					{
						hr = EMS_OK;
						ulActual = 0;
					}
			 }
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_INVALID_PTR;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_GenerateSchedule( ULONG ulMaxSize, EMSSATELLITEPASS* aPassSched, ULONG& ulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !aPassSched )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		hr = _InitPassSchedObj();
	}

	if( SUCCEEDED(hr) )
	{
		// Generate a schedule from now to some constant time in the future.
		EMSTIME timeStart = CEMSSystemClock::GetTime();

		CEMSTime timeTemp( timeStart );
		timeTemp.AddDays( cnScheduleDuration );
		EMSTIME timeEnd = timeTemp;

		hr = m_lpPassSchedObj->GenerateSchedule( timeStart, timeEnd );
	}

	if( SUCCEEDED(hr) )
	{
		EMSTIME timeStart;
		EMSTIME timeEnd;

		hr = m_lpPassSchedObj->GetSchedule( ulMaxSize, 
											aPassSched, 
											&ulActual, 
											&timeStart, 
											&timeEnd );
	}

	return hr;
}

EMS_RESULT CEMSNextVisibility::_Predict( EMSLOCATION eltLocation, EMSLOCATION lutLocation,
			EMSSATELLITEPASS *lpPass, double dMinElevationAngle, double dMinOutage,
			EMSTIME *lpTCA, double *lpdCTA, double *lpdMaxElevation )
{
	EMS_RESULT hr = EMS_FALSE;
	EMSTIME timeTCA;
	double dCTA = 0.0, dMaxElevation = 0.0;

	timeTCA.intTime = 0;

	if ( lpPass )
	{
		int i;
		EMSLOCATION intersect[3];
		EMSVECTOR V[3], xProduct;
		double dSin = 0.0, dEltRadius, dLutRadius, dTheta, dAzimuth, dABSCTA;
		double dSMA = 0.0;

		_GetSMA( lpPass->ulSatelliteID, lpPass->timeAOS, &dSMA );

		if ( dSMA > c_dEarthKmRadius )
		{

			// Calculate both ELT and LUT radius from centre of earth
			dSin = sind( eltLocation.degLatitude );

			dEltRadius = c_dEarthKmRadius * 
						( 1.0 - ( c_dEarthFlatteningTerm * dSin * dSin ) );

			dSin = sind( lutLocation.degLatitude );

			dLutRadius = c_dEarthKmRadius * 
						( 1.0 - ( c_dEarthFlatteningTerm * dSin * dSin ) );

			// Calculate THETA,the LUT coverage radius (deg) 
			// based upon maximum CTA for a given minimum elevation angle 
			dTheta = dLutRadius * cosd( lpPass->degMinElevation ) / dSMA;

			dTheta = acosd( dTheta ) - lpPass->degMinElevation;

			// Calculate the latitudes and longitudes of the two intersection locations
			// of the current satellite pass with the circle of coverage

			memset( intersect, 0, sizeof( intersect ) );

			for ( i = 0; i < 2; i++ )
 			{
				dAzimuth = ( i == 0 ) ? lpPass->degAzimuthAOS : lpPass->degAzimuthLOS;

				intersect[i].degLatitude = asind(  cosd( dTheta ) * sind( lutLocation.degLatitude ) +
							sind( dTheta ) * cosd( lutLocation.degLatitude ) * cosd( dAzimuth ) );

				intersect[i].degLongitude = atan2d(  sind( dTheta ) * cosd( lutLocation.degLatitude ) 
						* sind( dAzimuth ) , cosd( dTheta ) - sind( lutLocation.degLatitude ) * 
							sind( intersect[i].degLatitude ) ) + lutLocation.degLongitude;

			}

			intersect[2] = eltLocation;


			// Calculate the unit vectors at both intersections and the ELT
			for  ( i = 0; i < 3; i++ )
			{
				V[i].fX = (float)( cosd( intersect[i].degLatitude ) * cosd( intersect[i].degLongitude ));
				V[i].fY = (float)( cosd( intersect[i].degLatitude ) * sind( intersect[i].degLongitude ));
				V[i].fZ = (float)( sind( intersect[i].degLatitude ) );
			}

			// Compute the cross-track angle of the ELT
			// 1. The orbit normal vector is obtained from the cross-product of the 2 intersection vectors
			// 2. The CTA is the arcsine of the dot product of the ELT and the orbit normal unit vector
			xProduct = CEMSVector::CrossProduct( V[0] , V[1] );

			float fDotProduct = CEMSVector::DotProduct( xProduct , xProduct );

			if ( fDotProduct > 0.000001 )
			{
				dCTA = CEMSVector::DotProduct( V[2], xProduct );

				dCTA /= sqrt( fDotProduct );

				dCTA = asind( dCTA );

				dABSCTA = fabs( dCTA );

				if ( dABSCTA < 0.00001 ) 
					dABSCTA = 0.00001;

				// Compute the maximum elevation angle from the ELT to the satellite
				dMaxElevation = atan2d( cosd( dABSCTA ) - ( dEltRadius / dSMA ) ,
											sind( dABSCTA ) );

				// Check ELT elevation angle for visibility to satellite
				if ( dMaxElevation >= dMinElevationAngle )
				{
					float fDP1, fDP2, fDP3, fA1, fA2, fA;
					CEMSTime timeTemp;
					double dTimefromAOS, dTimefromLOS;

					// Project the ELT position on the orbit plane and determine
					// the angles from the projected ELT to the intersection locations
					fDP1 = CEMSVector::DotProduct( V[ 0 ], V[ 2 ]  );
					fDP2 = CEMSVector::DotProduct( V[ 1 ], V[ 2 ]  );
					fDP3 = CEMSVector::DotProduct( V[ 0 ], V[ 1 ]  );

					fA1 = (float)( fDP1 / cosd( dCTA ) );
					fA2 = (float)( fDP2 / cosd( dCTA ) );

					if ( fabs( fA1 ) > 1.0 ) 
						fA1 = (float)( fA1 / fabs( fA1 ) );

					if ( fabs( fA2 ) > 1.0 ) 
						fA2 = (float)( fA2 / fabs( fA2 ) );

					fA1 = (float)acosd( fA1 );

					fA2 = (float)acosd( fA2 );

					fA = (float)acosd( fDP3 );

					// Determine the time of closest approach from a ratio of angles and
					// the known time span for the pass.

					// Determine sign of angle relative to direction of motion
					if ( fA2 > fA && fA2 > fA1 ) fA1 = - fA1;

					timeTCA = lpPass->timeAOS;

					timeTCA.intTime += (INT64)( ( lpPass->timeLOS.intTime - lpPass->timeAOS.intTime )
									* (double)( fA1 / fA ) );

					timeTemp.SetTime( timeTCA );

					dTimefromAOS = timeTemp.MinutesDifferent( lpPass->timeAOS );
					dTimefromLOS = timeTemp.MinutesDifferent( lpPass->timeLOS );

					// Check if TCA within predicted pass window +/- outage window 
					if (( dTimefromAOS < dMinOutage ) && ( dTimefromLOS > -dMinOutage ))
					{
						hr = EMS_OK;
					}

				}
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpTCA )
		*lpTCA = timeTCA;

	if ( lpdCTA )
		*lpdCTA = dCTA;

	if ( lpdMaxElevation )
		*lpdMaxElevation = dMaxElevation;

	return hr;
}

EMS_RESULT CEMSNextVisibility::_GetSMA( ULONG ulSatID, EMSTIME timeAOS, double *lpdSMA )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpdSMA )
	{
		double dSMA = 0.0;

		if ( m_lpOrbit )
		{
			EMSTLEDATA tle;
			double dRadiansPerSec = 0.0;

			memset( &tle, 0, sizeof( tle ) );

			hr = m_lpOrbit->GetSatelliteTLE( ulSatID, timeAOS, &tle );

			dRadiansPerSec = tle.elem.var.fMeanMotion * c_dTwoPI / 86400.0; 

			dSMA = sqrt( c_dGravitationConstant ) / dRadiansPerSec;

			dSMA = pow( dSMA , ( 2.0 / 3.0 ) );
		}

		*lpdSMA = dSMA;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
} 
			
