/********************************************************************
*	Module:			EMSSymGPSEphem.cpp 
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

#include <math.h>
#include <string.h>
#include <io.h>

#define DEBUG_GPS_DATA
#define EMSERROR_NODEFINE_TYPES

#include "EMSGPSEphem.h"
#include "EMSSymGPSEphem.h"
#include "EMSGPSConvert.h"
#include "emstleconv.h"
#include "emsconst.h"
#include "gpsephem.h"		// EMSGPSEPHEMERISDATA
#include "emsclock.h"		// CEMSSystemClock

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CEMSSymGPSEphemeris::CEMSSymGPSEphemeris( )
{
	m_lpGpsEphemeris = 0;
	m_bInitialized = false;
}

CEMSSymGPSEphemeris::~CEMSSymGPSEphemeris( )
{
	Reset( );
}

EMS_RESULT CEMSSymGPSEphemeris::Initialize( IEMSSatelliteInfo *lpSatInfo, IEMSOrbit *lpOrbit, IEMSGpsEphemeris *lpGpsEphemeris )
{
	EMS_RESULT hr = EMS_OK;

	ULONG		  ulLength = 0;
	BYTE		  cDataDir[255];
	IEMSSiteInfo *lpSiteInfo=0;

	hr = CEMSGPSEphemeris::Initialize( lpSatInfo, lpOrbit );

	hr = CoCreateInstance( CLSID_EMSSiteInfo, 0, CLSCTX_ALL,
										IID_IEMSSiteInfo, (LPVOID*)&lpSiteInfo );

	hr = lpSiteInfo->GetDataDirectory( cDataDir, sizeof( cDataDir ), &ulLength );

	if ( lpSiteInfo )
	{
		lpSiteInfo->Release( );
		lpSiteInfo = NULL;
	}

	if ( ( hr == EMS_OK ) && ulLength )
	{
		for ( ULONG i = 0; i <= ulLength; i++ )
			m_szFilePath[i] = (TCHAR)cDataDir[i];

		lstrcat( m_szFilePath, TEXT("\\") );
	}

	if( EMS_OK == hr )
	{
		if ( lpGpsEphemeris )
			lpGpsEphemeris->AddRef( );
		else
		{
			// CoCreate
		}

		if ( m_lpGpsEphemeris )
		{
			m_lpGpsEphemeris->Release( );
			m_lpGpsEphemeris = NULL;
		}

		m_lpGpsEphemeris = lpGpsEphemeris;

		if ( !m_bInitialized )
		{
			m_bInitialized = ( ( 0 != m_lpSatInfo ) && ( 0 != m_lpOrbit ) && 
									( 0 != m_lpGpsEphemeris ) );
		}
	}

	if ( !m_bInitialized )
		hr = EMS_FALSE;

	return hr;
}


void CEMSSymGPSEphemeris::Reset( void )
{
	CEMSGPSEphemeris::Reset();

	if ( m_lpGpsEphemeris )
	{
		m_lpGpsEphemeris->Release( );
		m_lpGpsEphemeris = 0;
	}

	m_bInitialized = false;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
EMS_RESULT CEMSSymGPSEphemeris::GetTLE( ULONG ulSatID, EMSTLERECORD *lpTLERec, EMSEPHEMERISDATA2* lpEphemRec )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			EMSEPHEMERISDATA ephemData;

			hr = m_lpGpsEphemeris->GetGpsEphemerisData( ulSatID - c_nMinGpsSatID, &ephemData );

			if ( EMS_OK == hr )
			{
				// Validate GPS data packet
				hr = ValidateGPSephemerisPacket( &ephemData );
			}
			

			if ( EMS_OK == hr )
			{

				TCHAR szFilespec1[256];
				TCHAR szFilespec2[256];

				lstrcpy( szFilespec1, m_szFilePath );
			
				_stprintf( szFilespec2, TEXT( "EMSSymEphemeris-%ld.DAT" ), ulSatID );
				
				lstrcat( szFilespec1, szFilespec2 ); 
				
				FILE *lpFile1 = fopen( szFilespec1, "wb" );

				if ( lpFile1 )
				{
					fwrite( &ephemData, 1, sizeof( EMSEPHEMERISDATA ), lpFile1 );
					fclose( lpFile1 );
				}

				hr = CEMSTLEConvert::GPStoAccurateTLERecord( lpTLERec, &ephemData, ulSatID );

//----------------------------------------------------------------------------------------------
// Debug data output

#ifdef DEBUG_GPS_DATA
				lstrcpy( szFilespec1, m_szFilePath );
			
				_stprintf( szFilespec2, TEXT( "EMSSymEphemeris-%ld.txt" ), ephemData.nWeekNum );
				
				lstrcat( szFilespec1, szFilespec2 ); 

				bool bExists = ( 0 == _access( szFilespec1, 0 ));

				FILE *lpFile = fopen( szFilespec1, "at" );

				if ( lpFile )
				{
					if ( !bExists )
					{
						fprintf( lpFile, "hr,ulSatPRN,dTimeCollection,nWeekNum,cCodeL2,cL2PData,cSVAccRaw,cSVHealth,nIODC,dTGD,dTOC,dAF2,dAF1,dAF0,dSVAcc,cIODE,cFitInterval,dCRS,dDeltaN,dM0,dUC,dE,dCUS,dSqrtA,dTOE,dCIC,dOmegaO,dCIS,dIO,dCrc,dOmega,dOmegaDot,dIDot,dAxis,dN,dR1ME2,dOmegaN,dODotN\n" );
					}
					fprintf( lpFile, "%ld,%ld,%lf,%d,%d,%d,%d,%d,",
							hr, ephemData.ulSatPRN, ephemData.dTimeCollection,
							ephemData.nWeekNum, ephemData.cCodeL2,
							ephemData.cL2PData, ephemData.cSVAccRaw, ephemData.cSVHealth );

					fprintf( lpFile, "%d,%lf,%lf,%lf,%lf,%lf,%lf,",
						ephemData.nIODC, ephemData.dTGD, ephemData.dTOC, 
						ephemData.dAF2, ephemData.dAF1, ephemData.dAF0, ephemData.dSVAcc ); 

					fprintf( lpFile, "%d,%d,%lf,%lf,%lf,%lf,%lf,",
						ephemData.cIODE, ephemData.cFitInterval, ephemData.dCRS, 
						ephemData.dDeltaN, ephemData.dM0, ephemData.dUC, ephemData.dE ); 

					fprintf( lpFile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,",
						ephemData.dCUS, ephemData.dSqrtA, ephemData.dTOE, 
						ephemData.dCIC, ephemData.dOmegaO, ephemData.dCIS, ephemData.dIO );

					fprintf( lpFile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
						ephemData.dCrc, ephemData.dOmega, ephemData.dOmegaDot, 
						ephemData.dIDot, ephemData.dAxis, ephemData.dN, 
						ephemData.dR1ME2, ephemData.dOmegaN, ephemData.dODotN );

					fprintf( lpFile, "\n" );

					fclose( lpFile );
				}

//				hr = CEMSTLEConvert::GPStoTLERecord( lpTLERec, &ephemData );

				lstrcpy( szFilespec1, m_szFilePath );
			
				_stprintf( szFilespec2, TEXT( "EMSSymTLE_Record-%ld.txt" ), ephemData.nWeekNum );
				
				lstrcat( szFilespec1, szFilespec2 ); 

				bExists = ( 0 == _access( szFilespec1, 0 ));

				lpFile = fopen( szFilespec1, "at" );

				if ( lpFile )
				{
					fprintf( lpFile, "%ld, %I64d, %d,%d,%d, %I64d, %f,%f,%f,%f,%f,%f\n",
									 hr,lpTLERec->time,
									 lpTLERec->ulLutID,
									 lpTLERec->ulSatID,
									 lpTLERec->nOrbitNumber,
									 lpTLERec->timeEpoch,
									 lpTLERec->fInclination,
									 lpTLERec->fRightAscNode,
									 lpTLERec->fEccentricity,
									 lpTLERec->fArgPerigee,
									 lpTLERec->fMeanAnomaly,
									 lpTLERec->fMeanMotion	);
				}

#endif 

//----------------------------------------------------------------------------------------------

//				hr = TLEosc2TLEmean( lpTLERec );


				if ( lpTLERec && ( EMS_OK == hr ) )
				{
					lpTLERec->nOrbitNumber = _GetOrbitNumber( ulSatID, lpTLERec->timeEpoch );
				}

				if( lpEphemRec && (EMS_OK == hr ) )
				{
					lpEphemRec->baseData = ephemData;
					lpEphemRec->ulSatID = ulSatID;
				}
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}

EMS_RESULT CEMSSymGPSEphemeris::GetFirstTLE(LPEMSTLERECORD lpTLERecord, EMSEPHEMERISDATA2* lpEphemRec, bool *lpbMore )
{
	m_ulSatIndex = 0;

	return GetNextTLE( lpTLERecord, lpEphemRec, lpbMore );
}

EMS_RESULT CEMSSymGPSEphemeris::GetNextTLE( LPEMSTLERECORD lpTLERecord, EMSEPHEMERISDATA2* lpEphemRec,bool *lpbMore )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpTLERecord && lpEphemRec && lpbMore )
	{
		if ( m_ulSatIndex < m_ulSatCount )
		{
			hr = GetTLE( m_ulSats[ m_ulSatIndex ], lpTLERecord, lpEphemRec );

			m_ulSatIndex++;
		}
		else
			hr = EMS_FALSE;

		*lpbMore = ( m_ulSatIndex < m_ulSatCount );
	}
	else
		hr = EMS_BAD_PARAM;


	return hr;
}


EMS_RESULT CEMSSymGPSEphemeris::ValidateGPSephemerisPacket(LPEMSEPHEMERISDATA lpEphemData )
{

	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( lpEphemData )
	{
		// Validate GPS data packet
		bool iOK = true;

		int		nThreshold = 10000;		
		double	dThreshold = 10000.0;		
		
		iOK &= ( lpEphemData->ulSatPRN < 33 );
		iOK &= ( lpEphemData->ulSatPRN > 0 );

		iOK &= ( lpEphemData->dTimeCollection > 0.0 );
		iOK &= ( lpEphemData->nWeekNum > 0 );


		EMSTIME tGPS, tNOW;
		tGPS = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTOE, lpEphemData->nWeekNum );
		tNOW = CEMSSystemClock::GetTime();
		double dTimeDiff = double( tGPS.intTime - tNOW.intTime )*1e-9;

		iOK &= ( fabs( dTimeDiff ) < 86400 ); // Time must be within current day
			
		iOK &= ( fabs( lpEphemData->dTOC ) < 1000000 );
		
		iOK &= ( lpEphemData->dE > 0.0 );
		iOK &= ( lpEphemData->dE < 0.5 );  // Eccentricity close to circular orbit

		iOK &= ( lpEphemData->dSqrtA > 3162.3 ); // Semi-major axis greater than 10,000 km
		iOK &= ( lpEphemData->dSqrtA < 7000.0 ); // Semi-major axis greater than 49,000 km

		iOK &= ( fabs(lpEphemData->dOmega) <= c_dTwoPI );
		iOK &= ( fabs(lpEphemData->dOmegaO) <= c_dTwoPI );
		iOK &= ( fabs(lpEphemData->dM0) <= c_dTwoPI );
		iOK &= ( lpEphemData->dIO <= c_dPI );
		iOK &= ( lpEphemData->dIO > 0.0 );

		iOK &= ( fabs(lpEphemData->dN ) < 24.0/86400.0 );    // Period less than 24 hours
		iOK &= ( fabs(lpEphemData->dDeltaN) < 1.0/86400.0 );  // Change in period less than 1 hour

		iOK &= ( lpEphemData->cCodeL2 < nThreshold );

			
		iOK &= ( fabs(lpEphemData->dCRS ) < dThreshold );
		iOK &= ( fabs(lpEphemData->dUC  ) < dThreshold );
		iOK &= ( fabs(lpEphemData->dCUS ) < dThreshold );
		iOK &= ( fabs(lpEphemData->dCIC ) < dThreshold );
		iOK &= ( fabs(lpEphemData->dCIS ) < dThreshold );
		
		
		iOK &= ( lpEphemData->cCodeL2   < nThreshold );
		iOK &= ( lpEphemData->cL2PData  < nThreshold );
		iOK &= ( lpEphemData->cSVAccRaw < nThreshold );

		iOK &= ( fabs( lpEphemData->dTGD ) < dThreshold );
		iOK &= ( fabs( lpEphemData->dAF2 ) < dThreshold );
		iOK &= ( fabs( lpEphemData->dAF1 ) < dThreshold );
		iOK &= ( fabs( lpEphemData->dAF0 ) < dThreshold );
		iOK &= ( fabs( lpEphemData->dSVAcc ) < dThreshold );

		//iOK &= ( lpEphemData->cSVHealth < ??? );
		//iOK &= ( lpEphemData->nIODC < ??? );
		//iOK &= ( lpEphemData->cIODE	 < ??? );
		//iOK &= ( lpEphemData->cFitInterval < ??? );
		//iOK &= (fabs(lpEphemData->.dCrc  ) < ??? );
		//iOK &= (fabs(lpEphemData->dOmegaDot) < ??? );
		//iOK &= (fabs(lpEphemData->.dIDot) < ??? );
		//iOK &= (fabs(lpEphemData->.dAxis) < ??? );
		//iOK &= (fabs(lpEphemData->.dR1ME2 ) < ??? );
		//iOK &= (fabs(lpEphemData->.dOmegaN ) < ??? );
		//iOK &= (fabs(lpEphemData->.dODotN ) < ??? );

		if ( iOK )
			hr = EMS_OK;
	}

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

