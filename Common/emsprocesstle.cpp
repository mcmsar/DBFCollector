/********************************************************************
*	Module:			EMSGProcessTLE.cpp 
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
#include <stdio.h>

#define EMSERROR_NODEFINE_TYPES

#include "EMSProcessTLE.h"
#include "emsconst.h"
#include "emsclock.h"		// CEMSSystemClock
#include "LogHelper.h"
#include "logmsgparam.h"
#include "mastmsgs.h"
#include "messages.h"
#include "emssatx.h"
#include "emstleconv.h"
#include "SatConfig.h"
#include "satclient.h"
#include "ccbootstrap.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CEMSProcessTLE::CEMSProcessTLE( )
{
	m_ulLutID = 0;
	m_lpSatInfo = 0;
	m_lpTLEDataSource = 0;
	m_lpOrbit = 0;
	m_bInitialized = false;
}

CEMSProcessTLE::~CEMSProcessTLE( )
{
	Reset( );
}

EMS_RESULT CEMSProcessTLE::Initialize( ULONG ulLutID, CEMSPacketSource *lpTLESource, IEMSSatelliteInfo *lpSatInfo, IEMSOrbit *lpOrbit )
{
	EMS_RESULT hr = EMS_OK;
	IEMSOrbit2 *lpOrbit2 = 0;

	m_ulLutID = ulLutID;

	if ( lpSatInfo )
		lpSatInfo->AddRef( );
	else
	{
		// CoCreate
	}

	if ( m_lpSatInfo )
		m_lpSatInfo->Release( );

	m_lpSatInfo = lpSatInfo;

	if ( lpOrbit )
	{
		hr = lpOrbit->QueryInterface( IID_IEMSOrbit2, (LPVOID*)&lpOrbit2 );
	}
	else
	{
		// CoCreate
	}

	if ( m_lpOrbit )
		m_lpOrbit->Release( );

	m_lpOrbit = lpOrbit2;

	if ( lpTLESource )
		lpTLESource->AddRef( );

	if ( m_lpTLEDataSource )
		m_lpTLEDataSource->Release( );

	m_lpTLEDataSource = lpTLESource;


	if ( !m_bInitialized )
	{
		m_bInitialized = ( ( 0 != m_lpSatInfo ) && ( 0 != m_lpOrbit ) && 
									( 0 != m_lpTLEDataSource ) );
	}

	if ( m_bInitialized )
	{
		hr = _GetSatOrbitTolerance();
		if ( hr != EMS_OK )
			m_bInitialized = false;
	}

	return hr;
}

void CEMSProcessTLE::Reset( void )
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

	m_bInitialized = false;
}


EMS_RESULT CEMSProcessTLE::SetNewTLE( LPEMSTLERECORD lpTLERecord, 
											EMSSITCONTROLCODE ctrlCode, bool bAlways )
{
	EMS_RESULT hr = EMS_OK;
	EMSTLEDATA2 tleData2;
	ULONG ulSatID = 0;

	hr = CEMSTLEConvert::TLERecordToTLEData2( &tleData2, lpTLERecord, &ulSatID );

	if ( EMS_OK == hr )
		hr = SetNewTLE( ulSatID, &tleData2, ctrlCode, bAlways );

	return hr;
}
										
EMS_RESULT CEMSProcessTLE::SetNewTLE( ULONG ulSatID, EMSTLEDATA2 *lpTLEData, 
											EMSSITCONTROLCODE ctrlCode, bool bAlways )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		if ( lpTLEData && m_lpOrbit && m_lpSatInfo )
		{
			EMSTIMECOORD vOld, vNew;
			EMSTIME timeNow = CEMSSystemClock::GetTime();
			ULONG ulCount = 0;
			double dError = 0.0;
			double dMaxVelErr=100.0, dMaxPosErr=100.0;
	//		TCHAR szInfo[ 256 ];

			// if there is no effective time : set to Epoch time
			if ( lpTLEData && !lpTLEData->timeEffective.intTime )
				lpTLEData->timeEffective = lpTLEData->tle.timeEpoch;

			if ( m_bInitialized )
			{
				for ( ULONG i=0; i < m_ulSatCount; i++ )
				{
					if ( m_ulSatellites[i] == ulSatID )
					{
						dMaxPosErr = m_dMaxPosError[i];
						dMaxVelErr = m_dMaxVelError[i];
					}
				}
			}

     		hr = m_lpOrbit->EarthFixedOrbitTLE( &lpTLEData->tle,
						            			&timeNow, 1, &vNew, &ulCount );

			if ( hr == EMS_OK )
	     		hr = m_lpOrbit->EarthFixedOrbit( ulSatID, 
						            			&timeNow, 1, &vOld, &ulCount );

			if ( hr == EMS_OK )
			{
				// check the magnitude of the difference before installing
				double dPosErr, dVelErr;
				CEMSLogMsgParam	paramPosVelErr(3);
				wchar_t	wszBuff[32];

				dPosErr = sqrt( (vOld.coord.radius.fX   - vNew.coord.radius.fX)   *
          						(vOld.coord.radius.fX   - vNew.coord.radius.fX)   +
          						(vOld.coord.radius.fY   - vNew.coord.radius.fY)   *
          						(vOld.coord.radius.fY   - vNew.coord.radius.fY)   +
          						(vOld.coord.radius.fZ   - vNew.coord.radius.fZ)   *
          						(vOld.coord.radius.fZ   - vNew.coord.radius.fZ)   );

				dVelErr = 1000.0*sqrt( (vOld.coord.velocity.fX - vNew.coord.velocity.fX) *
          							   (vOld.coord.velocity.fX - vNew.coord.velocity.fX) +
          							   (vOld.coord.velocity.fY - vNew.coord.velocity.fY) *
          							   (vOld.coord.velocity.fY - vNew.coord.velocity.fY) +
          							   (vOld.coord.velocity.fZ - vNew.coord.velocity.fZ) *
          							   (vOld.coord.velocity.fZ - vNew.coord.velocity.fZ) );

				paramPosVelErr.Add( ulSatID );

				swprintf( wszBuff, L"%.2lf", dPosErr );

				paramPosVelErr.AddString( wszBuff );

				swprintf( wszBuff, L"%.2lf", dVelErr );

				paramPosVelErr.AddString( wszBuff );

	//			_stprintf( szInfo, TEXT("Sat=%ld , PosErr=%.2lf, VelErr=%.2lf"), ulSatID,
	//																dPosErr, dVelErr );

				switch ( ctrlCode )
 				{
					case EMSSCC_Info:
						hr = EMS_OK;
						break;

					case EMSSCC_Validate:
						if ( ( dVelErr < dMaxVelErr ) && ( dPosErr < dMaxPosErr ) ) 
						{
							hr = EMS_OK;
						}
						else
						{
							hr = EMS_MAST_ERR_ORBIT_VECTOR;
						}
						break;

					case EMSSCC_Execute:
					case EMSSCC_ValidateInstall:
					case EMSSCC_Install:
					case EMSSCC_InstallManoeuvre:
						if ( ( ( dVelErr < dMaxVelErr ) && ( dPosErr < dMaxPosErr ) ) || 
												( ( ctrlCode == EMSSCC_Install ) ||
												( ctrlCode == EMSSCC_InstallManoeuvre ) ) )
						{
							bool bPostManoeuvre = ( EMSSCC_InstallManoeuvre == ctrlCode );
							bool bInstallNewTLE = true;

							if ( bPostManoeuvre )
							{
								IEMSSatelliteInfo7 *lpSatInfo7 = 0;

								hr = m_lpSatInfo->QueryInterface( IID_IEMSSatelliteInfo7, 
												(LPVOID*)&lpSatInfo7 );

								if (( EMS_OK == hr ) && lpSatInfo7 )
								{
									EMSSATBEHAVIOUR satBehaviour;
									EMSTESTCONFIGDATA testCfg;
									int const c_wLatestRevision = 0;

									memset( &satBehaviour, 0, sizeof( satBehaviour ) );

									memset( &testCfg, 0, sizeof( testCfg ) );

									hr = lpSatInfo7->GetTestConfigData( ulSatID, &testCfg );

									if ( EMS_OK != hr )
										testCfg.dwFlags = 0;

									satBehaviour.ulSatID = ulSatID;

									// set timeEpoch or timeEffective depending of flags

									if ( EMS_TESTCFG_PostManoeuvreUseEffectiveTime & testCfg.dwFlags )
										satBehaviour.timeBegin = lpTLEData->timeEffective;
									else
										satBehaviour.timeBegin = lpTLEData->tle.timeEpoch;

									satBehaviour.dDurationSeconds = 0;
									satBehaviour.type = EMS_SBT_Unknown;
									satBehaviour.status = EMS_SBS_Unknown;

									hr = lpSatInfo7->SetSatBehaviour( ulSatID, 
														c_wLatestRevision, &satBehaviour );

									lpSatInfo7->Release( );
									lpSatInfo7 = 0;
								}
							}

							lpTLEData->timeModified = CEMSSystemClock::GetTime();

							if ( false == bAlways ) // check for different epoch time
							{
								EMSTLEDATA2 tleOld;

								hr = m_lpOrbit->GetSatelliteTLE2( ulSatID, 
													lpTLEData->tle.timeEpoch, &tleOld );

								if ( EMS_OK == hr )
								{
									bInstallNewTLE = ( lpTLEData->tle.timeEpoch.intTime >= tleOld.tle.timeEpoch.intTime );
								}
							}

							if ( bInstallNewTLE )
							{
								if ( (dPosErr+dVelErr) > 0.0 )
								{
									hr = m_lpOrbit->SetSatelliteTLE2( ulSatID, lpTLEData );

									if ( hr == EMS_OK )
										hr = _UpdateTLERecord( ulSatID, lpTLEData, FALSE, dPosErr, dVelErr );

									if ( bPostManoeuvre )
										CEMSLogHelper::LogInfoMsg( EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR, paramPosVelErr );
									else
										CEMSLogHelper::LogInfoMsg( EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR, paramPosVelErr );
								}
								else
								{
									CEMSLogHelper::LogInfoMsg( EMS_OM_DUPL_ORBIT_VECTOR_POSVELERR, paramPosVelErr );
								}
							}
						}
						else
						{
							CEMSLogHelper::LogInfoMsg( EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR, paramPosVelErr );

							hr = EMS_MAST_ERR_ORBIT_VECTOR;
						}
						break;

					default:
						hr = EMS_MAST_BAD_ORBIT_OPTION;
						break;	
				}
			}
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSProcessTLE::_UpdateTLERecord( EMSTLERECORD *lpTLERec )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTLERec ) 
	{
		lpTLERec->ulLutID = m_ulLutID;

		if ( m_lpTLEDataSource )
		{
			ULONG ulBytesSent = 0;

			hr = m_lpTLEDataSource->Write( (LPBYTE)lpTLERec, 
										sizeof( EMSTLERECORD ), &ulBytesSent );
		}
		else
			hr = EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSProcessTLE::_UpdateTLERecord( ULONG ulSatID, EMSTLEDATA2 *lpTLEData, 
								BOOL bMoreFlag, double dPosErr, double dVelErr )
{
	EMS_RESULT hr = EMS_OK;

	if ( ( hr == EMS_OK ) && lpTLEData )
	{
		EMSTLERECORD tleRecord;

		hr = CEMSTLEConvert::TLEData2toTLERecord( &tleRecord, lpTLEData, ulSatID,
										dPosErr, dVelErr, ( TRUE==bMoreFlag ) );

		hr = _UpdateTLERecord( &tleRecord );

		// log error?

		hr = EMS_OK;
	}
	return hr;
}

EMS_RESULT CEMSProcessTLE::IsTLECurrent( ULONG ulSatId )
{
	EMS_RESULT	hr = EMS_OK;
	EMSTLEDATA2 tleCurrent;
	EMSTIME		timeNow;
	EMSTIME		timeEpoch;
	double		dTimeDiff = 0;

	try
	{
		timeEpoch.intTime = 0;	// to get the most current TLE
		if ( m_lpOrbit )
		{
			hr = m_lpOrbit->GetSatelliteTLE2( ulSatId, timeEpoch, &tleCurrent );

			if ( EMS_OK == hr  )
			{
				timeNow = CEMSSystemClock::GetTime();
				dTimeDiff = double( timeNow.intTime - tleCurrent.tle.timeEpoch.intTime )*1e-9;

				if ( dTimeDiff > 172800 ) // older than 2 days
					hr = EMS_FALSE;
			}
			else
			{
				// No orbit for that satellite, return ok
				hr = EMS_OK;
			}
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSProcessTLE::RewriteOrbit( ULONG ulSatId, ULONG ulNoradId, EMSTIME *epochTime )
{
	EMS_RESULT	hr;
	EMSTLEDATA2 tleCurrent;
	EMSTIME		timeEpoch;
	CEMSLogMsgParam	param(2);

	try
	{
		timeEpoch.intTime = 0;	// to get the most current TLE
		if ( m_lpOrbit )
		{
			hr = m_lpOrbit->GetSatelliteTLE2( ulSatId, timeEpoch, &tleCurrent );

			if ( EMS_OK == hr  )
			{
				tleCurrent.timeModified = CEMSSystemClock::GetTime();
				hr = _UpdateTLERecord( ulSatId, &tleCurrent, false );

				if ( EMS_OK == hr )
				{
					*epochTime = tleCurrent.tle.timeEpoch;
				}
				else
				{
					// raise a warning message
					param.Add( ulSatId );
					param.Add( ulNoradId );
					CEMSLogHelper::LogWarningMsg( EMS_OM_ORBIT_NOT_UPDATED, param );
				}
			}
			else
			{
				// raise a warning message
				param.Add( ulSatId );
				param.Add( ulNoradId );
				CEMSLogHelper::LogWarningMsg( EMS_OM_ORBIT_NOT_AVAILABLE, param );
			}
		}
		else
		{
			hr = EMS_FALSE;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}

EMS_RESULT CEMSProcessTLE::_GetSatOrbitTolerance( void )
{
	EMS_RESULT hr = EMS_OK;

	m_ulSatCount = 0;
	memset( m_ulSatellites, 0, sizeof( m_ulSatellites ) );
	memset( m_dMaxPosError, 0, sizeof( m_dMaxPosError ) );
	memset( m_dMaxVelError, 0, sizeof( m_dMaxVelError ) );
	
	list<SatConfig*> lstSatConfig;
	try
	{
		SatClient oSatClient( CCBootstrap::GetConfigServerHost(), CCBootstrap::GetConfigServerPort() );
	
		lstSatConfig = oSatClient.getAll();

		if ( !lstSatConfig.empty() )
		{
			list<SatConfig*>::iterator Iter;

			for( Iter = lstSatConfig.begin(); (Iter != lstSatConfig.end()); Iter++ )
			{
				m_ulSatellites[ m_ulSatCount ] = (*Iter)->GetSatID();
				m_dMaxPosError[ m_ulSatCount ] = (*Iter)->GetPositionThreshold();
				m_dMaxVelError[ m_ulSatCount ] = (*Iter)->GetVelocityThreshold();
				m_ulSatCount++;
			}

			oSatClient.ClearSatConfigList( lstSatConfig );
		}
	}
	catch( ... )
	{
		hr = EMS_EXCEPTION;
		SatClient::ClearSatConfigList( lstSatConfig );
	}

	return hr;
}

