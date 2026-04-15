/********************************************************************
*	Module:			EMSJavGPSEphem.cpp 
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

#include <math.h>
#include <string.h>
#include <io.h>

#define DEBUG_GPS_DATA
#define EMSERROR_NODEFINE_TYPES

#include "EMSGPSEphem.h"
#include "EMSJavGPSEphem.h"
#include "EMSGPSConvert.h"
#include "LogHelper.h"
#include "logmsgparam.h"
#include "emstleconv.h"
#include "mastmsgs.h"
#include "messages.h"
#include "emsconst.h"
#include "JavadIf.h"		// EMSJAVADINTERFACE
#include "emsclock.h"		// CEMSSystemClock
#include "convutility.h"
#include "SatConfig.h"
#include "satclient.h"
#include "ccbootstrap.h"
#include "LPConfigCL.h"
#include "meosysclient.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
CEMSJavGPSEphemeris::CEMSJavGPSEphemeris( )
{
	m_lpGpsEphemeris = 0;
	m_bInitialized = false;
}

CEMSJavGPSEphemeris::~CEMSJavGPSEphemeris( )
{
	Reset( );
}

EMS_RESULT CEMSJavGPSEphemeris::Initialize( IEMSSatelliteInfo *lpSatInfo, 
										    IEMSOrbit *lpOrbit, IEMSJavadInterface *lpGpsEphemeris )
{
	EMS_RESULT hr = EMS_OK;
	ULONG		  ulLength = 0;
	char		  cDataDir[255];
	MEOSystemClient		oMeoSysClient;
	LPConfig*			pLPConf = NULL;

	try
	{
		hr = CEMSGPSEphemeris::Initialize( lpSatInfo, lpOrbit );

		pLPConf = oMeoSysClient.getLPById( CCBootstrap::GetThisSubsystemId() );

		if( pLPConf )
		{
			memset( cDataDir, 0, sizeof(cDataDir) );
			strcpy( cDataDir, pLPConf->GetDBDirectory().c_str() );
		
			delete pLPConf;
			pLPConf = NULL;
		}

		ulLength = sizeof(cDataDir);
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
	}
	catch ( ... )
	{
		if ( pLPConf )
		{
			delete pLPConf;
			pLPConf = NULL;
		}
		throw;
	}

	return hr;
}


void CEMSJavGPSEphemeris::Reset( void )
{
	CEMSGPSEphemeris::Reset();

	if ( m_lpGpsEphemeris )
	{
		m_lpGpsEphemeris->Release( );
		m_lpGpsEphemeris = 0;
	}

	m_bInitialized = false;
}


EMS_RESULT CEMSJavGPSEphemeris::Open()
{
	EMS_RESULT	hr;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->Open( 0 );
			if ( hr == EMS_UNKNOWN_ERROR )
				CEMSLogHelper::LogWarningMsg( EMS_OM_JAVAD_CONNECT_FAILED );
			else
				hr = EMS_OK;
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::Close()
{
	EMS_RESULT	hr;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->Close( );
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::GetTimeAccuracy( float *pfAccuracy )
{
	EMS_RESULT	hr = EMS_FALSE;
	WORD		wRetries = 3;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			while( (hr != EMS_OK) && ( wRetries-- ) )
			{
				hr = m_lpGpsEphemeris->GetRcvTimeAcuracy( pfAccuracy );
			}
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::GetTime( EMSTIME *pTimeGPS )
{
	EMS_RESULT	hr = EMS_FALSE;
	WORD		wRetries = 3;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			while( (hr != EMS_OK) && ( wRetries-- ) )
			{
				hr = m_lpGpsEphemeris->ReadTime( pTimeGPS );
			}
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::SyncSystemClock( )
{
	EMS_RESULT	hr = EMS_OK;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->SyncSystemClock();
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::InitEphemerisData()
{
	EMS_RESULT	hr = EMS_FALSE;
	WORD		wRetries = 3;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			while( (hr != EMS_OK) && ( wRetries-- ) )
			{
				hr = m_lpGpsEphemeris->InitEphemerisData();
			}
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::InitGpsEphemeris()
{
	EMS_RESULT	hr;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->InitGpsEphemeris();
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::InitGalEphemeris()
{
	EMS_RESULT	hr;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->InitGalEphemeris();
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::InitGloEphemeris()
{
	EMS_RESULT	hr;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			hr = m_lpGpsEphemeris->InitGloEphemeris();
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}
	catch ( ... )
	{
		hr = EMS_EXCEPTION;
	}

	return hr;
}


//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveEphemData( ULONG ulSatID, EMSEPHEMERISDATA ephemData )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSJavEphemeris-%ld.DAT" ), ulSatID );
	
	lstrcat( szFilespec1, szFilespec2 ); 
	
	FILE *lpFile1 = fopen( szFilespec1, "wb" );

	if ( lpFile1 )
	{
		fwrite( &ephemData, 1, sizeof( EMSEPHEMERISDATA ), lpFile1 );
		fclose( lpFile1 );
	}

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveGloEphemData( ULONG ulSatID, EMSGLOEPHEMERIS ephemData )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSJavEphemeris-%ld.DAT" ), ulSatID );
	
	lstrcat( szFilespec1, szFilespec2 ); 
	
	FILE *lpFile1 = fopen( szFilespec1, "wb" );

	if ( lpFile1 )
	{
		fwrite( &ephemData, 1, sizeof( EMSEPHEMERISDATA ), lpFile1 );
		fclose( lpFile1 );
	}

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveEphemTxtData( EMSEPHEMERISDATA ephemData, EMSTLERECORD tleRecord, bool bHasBadParams )
{
	EMS_RESULT		hr = EMS_OK;

	if ( bHasBadParams )
		hr = EMS_FALSE;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSJavEphemeris-%ld.txt" ), ephemData.nWeekNum );
	
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

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSJavTLE_Record-%ld.txt" ), ephemData.nWeekNum );
	
	lstrcat( szFilespec1, szFilespec2 ); 

	bExists = ( 0 == _access( szFilespec1, 0 ));

	lpFile = fopen( szFilespec1, "at" );

	if ( lpFile )
	{
		fprintf( lpFile, "%ld, %I64d, %d,%d,%d, %I64d, %f,%f,%f,%f,%f,%f\n",
						 hr,tleRecord.time,
						 tleRecord.ulLutID,
						 tleRecord.ulSatID,
						 tleRecord.nOrbitNumber,
						 tleRecord.timeEpoch,
						 tleRecord.fInclination,
						 tleRecord.fRightAscNode,
						 tleRecord.fEccentricity,
						 tleRecord.fArgPerigee,
						 tleRecord.fMeanAnomaly,
						 tleRecord.fMeanMotion	);
		fclose( lpFile );
	}

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveGalEphemTxtData( EMSEPHEMERISDATA ephemData, ULONG ulSatId )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSGalileoEphemeris-%ld.txt" ), ulSatId );
	
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

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveScaledEphemData( EMSSCALEDEPHEMERISDATAEX ephemScaled )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSScaledEphemeris-%ld.txt" ), ephemScaled.baseData.nWeekNum );
	
	lstrcat( szFilespec1, szFilespec2 ); 

	bool bExists = ( 0 == _access( szFilespec1, 0 ));

	FILE *lpFile = fopen( szFilespec1, "at" );

	if ( lpFile )
	{
		if ( !bExists )
		{
			fprintf( lpFile, "/SatId/M0 DeltaN E SqrtA Omega0 IO Omega OmegaDot IDot CUC CUS CRC CRS CIC CIS TOE nWeekNum IODE\n" );
		}
		fprintf( lpFile, "/%03d/%+010.10I64d %+05.5I64d %010.10I64d %010.10I64d %+010.10I64d ",
				ephemScaled.ulSatID, ephemScaled.baseData.i64M0, ephemScaled.baseData.i64DeltaN,
				ephemScaled.baseData.i64E, ephemScaled.baseData.i64SqrtA, ephemScaled.baseData.i64OmegaO );

		fprintf( lpFile, "%+010.10I64d %+010.10I64d %+07.7I64d %+04.4I64d %+05.5I64d %+05.5I64d ",
			ephemScaled.baseData.i64IO, ephemScaled.baseData.i64Omega, ephemScaled.baseData.i64OmegaDot, 
			ephemScaled.baseData.i64IDot, ephemScaled.baseData.i64UC, ephemScaled.baseData.i64CUS ); 

		fprintf( lpFile, "%+05.5I64d %+05.5I64d %+05.5I64d %+05.5I64d %06.6d %04.4d %03.3d",
			ephemScaled.baseData.i64CRC, ephemScaled.baseData.i64CRS, ephemScaled.baseData.i64CIC, 
			ephemScaled.baseData.i64CIS, ephemScaled.baseData.ulTOE, ephemScaled.baseData.nWeekNum, ephemScaled.baseData.cIODE ); 

		fprintf( lpFile, "\n" );

		fclose( lpFile );
	}

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveGloEphemTxtData( EMSGLOEPHEMERIS ephemData, EMSTLERECORD tleRecord, ULONG ulSatID, bool bHasBadParams )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	if ( bHasBadParams )
		hr = EMS_FALSE;

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSGloEphemeris-%ld.txt" ), ulSatID );
	
	lstrcat( szFilespec1, szFilespec2 ); 

	bool bExists = ( 0 == _access( szFilespec1, 0 ));

	FILE *lpFile = fopen( szFilespec1, "at" );

	if ( lpFile )
	{
		if ( !bExists )
		{
			fprintf( lpFile, "hr,cSv,cFrqNum,siDne,iTk,iTb,cHealth,cAge,cFlags,dR1,dR2,dR3,fV1,fV2,fV3,fW1,fW2,fW3,dTauSys,fTau,fGamma,fDelTauN,cNFt,cNN4,wFlags2\n" );
		}
		fprintf( lpFile, "%ld,%d,%d,%d,%d,%d,%d,%d,%d",
				hr, ephemData.cSv, ephemData.cFrqNum,
				ephemData.siDne, ephemData.iTk, ephemData.iTb,
				ephemData.cHealth, ephemData.cAge, ephemData.cFlags );

		fprintf( lpFile, "%lf,%lf,%lf,%f,%f,%f,%f,%f,%f,",
			ephemData.dR[0], ephemData.dR[1], ephemData.dR[2], 
			ephemData.fV[0], ephemData.fV[1], ephemData.fV[2], 
			ephemData.fW[0], ephemData.fW[1], ephemData.fW[2] ); 

		fprintf( lpFile, "%lf,%f,%f,%f,%d,%d,%d",
			ephemData.dTauSys, ephemData.fTau, ephemData.fGamma, 
			ephemData.fDelTauN, ephemData.cNFt, ephemData.cNN4, ephemData.wFlags2 ); 

		fprintf( lpFile, "\n" );

		fclose( lpFile );
	}

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "EMSGloTLE_Record-%ld.txt" ), 999 );
	
	lstrcat( szFilespec1, szFilespec2 ); 

	bExists = ( 0 == _access( szFilespec1, 0 ));

	lpFile = fopen( szFilespec1, "at" );

	if ( lpFile )
	{
		fprintf( lpFile, "%ld, %I64d, %d,%d,%d, %I64d, %f,%f,%f,%f,%f,%f\n",
						 hr,tleRecord.time,
						 tleRecord.ulLutID,
						 tleRecord.ulSatID,
						 tleRecord.nOrbitNumber,
						 tleRecord.timeEpoch,
						 tleRecord.fInclination,
						 tleRecord.fRightAscNode,
						 tleRecord.fEccentricity,
						 tleRecord.fArgPerigee,
						 tleRecord.fMeanAnomaly,
						 tleRecord.fMeanMotion	);
		fclose( lpFile );
	}

	return hr;
}

	
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::_SaveGloEphemTxtData2( EMSGLOEPHEMERIS ephemData )
{
	EMS_RESULT		hr = EMS_OK;

	TCHAR szFilespec1[256];
	TCHAR szFilespec2[256];

	lstrcpy( szFilespec1, m_szFilePath );

	_stprintf( szFilespec2, TEXT( "GloEphemDbg.txt" ) );
	
	lstrcat( szFilespec1, szFilespec2 ); 

	bool bExists = ( 0 == _access( szFilespec1, 0 ));

	FILE *lpFile = fopen( szFilespec1, "at" );

	if ( lpFile )
	{
		if ( !bExists )
		{
			fprintf( lpFile, "hr,cSv,cFrqNum,siDne,iTk,iTb,cHealth,cAge,cFlags,dR1,dR2,dR3,fV1,fV2,fV3,fW1,fW2,fW3,dTauSys,fTau,fGamma,fDelTauN,cNFt,cNN4,wFlags2\n" );
		}
		fprintf( lpFile, "%ld,%d,%d,%d,%d,%d,%d,%d,%d",
				hr, ephemData.cSv, ephemData.cFrqNum,
				ephemData.siDne, ephemData.iTk, ephemData.iTb,
				ephemData.cHealth, ephemData.cAge, ephemData.cFlags );

		fprintf( lpFile, "%lf,%lf,%lf,%f,%f,%f,%f,%f,%f,",
			ephemData.dR[0], ephemData.dR[1], ephemData.dR[2], 
			ephemData.fV[0], ephemData.fV[1], ephemData.fV[2], 
			ephemData.fW[0], ephemData.fW[1], ephemData.fW[2] ); 

		fprintf( lpFile, "%lf,%f,%f,%f,%d,%d,%d",
			ephemData.dTauSys, ephemData.fTau, ephemData.fGamma, 
			ephemData.fDelTauN, ephemData.cNFt, ephemData.cNN4, ephemData.wFlags2 ); 

		fprintf( lpFile, "\n" );

		fclose( lpFile );
	}

	return hr;
}

//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::GetGloTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSGLOEPHEMERIS2 *lpGloEphemRec )
{
	EMS_RESULT		hr = EMS_OK;
	ULONG			ulCount, i, j;
	EMSTLERECORD	tleRecord;
	ULONG			ulSatID;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			// Get the Galileo Ephemeris records
			EMSGLOEPHEMERIS		ephemGlo[24];
			LPEMSGLOEPHEMERIS	pEphemGlo[24];

			for ( i=0; i<24; i++ )
			{
				memset( &ephemGlo[i], 0, sizeof( ephemGlo[0] ) );
				pEphemGlo[i] = &ephemGlo[i];
			}

			j = 0;
			ulCount = 0;
			CEMSLogHelper::LogInfoMsg( EMS_OM_GETTING_GLO_EPHEM );
			hr = m_lpGpsEphemeris->GetGloEphemerisData( &ulCount, pEphemGlo );

			CEMSLogMsgParam	param;
			if ( hr == EMS_OK )
			{
				param.Add( ulCount );
				CEMSLogHelper::LogInfoMsg( EMS_OM_GOT_GLO_EPHEM, param );
			}
			else
			{
				ulCount = 0;
				param.Add( "GetGloEphemerisData from Javad failed" );
				CEMSLogHelper::LogWarningMsg( EMS_OM_TRACER, param );
			}

			for ( i=0; i<ulCount; i++)
			{
				bool bSatConfigured = false;
				char cFreq = ephemGlo[i].cFrqNum;

				// ulSatID = m_gloSatIdLookup.GetSatID( long(cFreq), long(ephemGlo[i].cSv) );
#ifdef DEBUG_GPS_DATA
					_SaveGloEphemTxtData2( ephemGlo[i] );
#endif 

				if ( IsGloSatConfigured( long(ephemGlo[i].cSv), long(cFreq), &ulSatID ) )
				{
					bSatConfigured = true;
					lpGloEphemRec[j].baseData = ephemGlo[i];
					lpGloEphemRec[j].ulSatID = ulSatID;
					hr = ValidateGLOephemerisPacket( &ephemGlo[i] );
				}

				if ( (EMS_OK == hr) && bSatConfigured )
				{
					_SaveGloEphemData( ulSatID, ephemGlo[i] );
					hr = CEMSTLEConvert::GloEphemToTLERecord( &tleRecord, 
															  &ephemGlo[i], ulSatID );

					bool bHasBadParams = false;
					if ( &tleRecord && ( EMS_OK == hr ) )
					{
						tleRecord.nOrbitNumber = _GetOrbitNumber( ulSatID, tleRecord.timeEpoch );
						lpTLERec[j++] = tleRecord;
					}
					else
					{
						bHasBadParams = true;
						CEMSLogMsgParam oParam;
						oParam.Add( "CEMSTLEConvert::GloEphemToTLERecord returned bad params" );
						CEMSLogHelper::LogWarningMsg( EMS_OM_TRACER, oParam );
					}
#ifdef DEBUG_GPS_DATA
					_SaveGloEphemTxtData( ephemGlo[i], tleRecord, ulSatID, bHasBadParams );
#endif 
				}
			} // end For loop

			*pulNumRec = j;
		}
		else
		{
			*pulNumRec = 0;
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
		CEMSLogMsgParam	param;
		param.Add( hr );
		CEMSLogHelper::LogWarningMsg( EMS_OM_EXCEPTION, param );
		throw;
	}

	return hr;
}


//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::GetGalTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSEPHEMERISDATA2 *lpEphemRec )
{
	EMS_RESULT		hr = EMS_OK;
	ULONG			ulCount, i, j;
	EMSTLERECORD	tleRecord;
	ULONG			ulSatID;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			// Get the Galileo Ephemeris records
			EMSGALEPHEMERIS		ephemGal[30];
			LPEMSGALEPHEMERIS	pEphemGal[30];

			for ( i=0; i<30; i++ )
			{
				memset( &ephemGal[i], 0, sizeof( ephemGal[0] ) );
				pEphemGal[i] = &ephemGal[i];
			}

			j = 0;
			ulCount = 0;
			CEMSLogHelper::LogInfoMsg( EMS_OM_GETTING_GAL_EPHEM );
			hr = m_lpGpsEphemeris->GetGalEphemerisData( &ulCount, pEphemGal );

			CEMSLogMsgParam	param;
			param.Add( ulCount );
			CEMSLogHelper::LogInfoMsg( EMS_OM_GOT_GAL_EPHEM, param );

			for ( i=0; i<ulCount; i++)
			{
				bool bSatConfigured = false;

				ulSatID = ephemGal[i].gps.ulSatPRN + c_nMinGalSatID;
				_SaveGalEphemTxtData( ephemGal[i].gps, ulSatID );
				if ( IsGalSatConfigured( ulSatID ) )
				{
					bSatConfigured = true;
					lpEphemRec[j].baseData = ephemGal[i].gps;
					hr = ValidateGPSephemerisPacket( &(ephemGal[i].gps) );
				}

				if ( (EMS_OK == hr) && bSatConfigured )
				{
					_SaveEphemData( ulSatID, ephemGal[i].gps );
					hr = CEMSTLEConvert::GPStoAccurateTLERecord( &tleRecord, 
																 &(ephemGal[i].gps), 
																 ephemGal[i].gps.ulSatPRN,
																 true );

#ifdef DEBUG_GPS_DATA
					bool  bHasBadParams = (hr != EMS_OK);
					_SaveEphemTxtData( ephemGal[i].gps, tleRecord, bHasBadParams );

					EMSSCALEDEPHEMERISDATAEX ephemScaled;
					memset( &ephemScaled, 0, sizeof(ephemScaled));

					ephemScaled.ulSatID = ulSatID;
					ephemScaled.constellation = EMS_CONSTELLATION_GALILEO;

					hr = CEMSTLEConvert::ScaleEphemerisData( ephemGal[i].gps, ephemScaled.baseData );

					_SaveScaledEphemData( ephemScaled );
#endif 
					if ( &tleRecord && ( EMS_OK == hr ) )
					{
						tleRecord.nOrbitNumber = _GetOrbitNumber( ulSatID, tleRecord.timeEpoch );
					}
					lpEphemRec[j].ulSatID = ulSatID;
					lpEphemRec[j].constellation = EMS_CONSTELLATION_GALILEO;
					lpTLERec[j++] = tleRecord;

					
				}
			} // end For loop

			*pulNumRec = j;
		}
		else
		{
			*pulNumRec = 0;
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
		CEMSLogMsgParam	param;
		param.Add( hr );
		CEMSLogHelper::LogInfoMsg( EMS_OM_EXCEPTION, param );
		throw;
	}

	return hr;
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
EMS_RESULT CEMSJavGPSEphemeris::GetGpsTLERecords( ULONG *pulNumRec, EMSTLERECORD *lpTLERec, EMSEPHEMERISDATA2 *lpEphemRec )
{
	EMS_RESULT		hr = EMS_OK;
	ULONG			ulCount, i, j;
	EMSTLERECORD	tleRecord;
	ULONG			ulSatID;

	try
	{
		if ( m_lpGpsEphemeris )
		{
			// Get the GPS Ephemeris records
			EMSEPHEMERISDATA	ephemGPS[32];
			LPEMSEPHEMERISDATA	pEphemGPS[32];

			for ( i=0; i<32; i++ )
			{
				memset( &ephemGPS[i], 0, sizeof( ephemGPS[0] ) );
				pEphemGPS[i] = &ephemGPS[i];
			}

			j = 0;
			ulCount = 0;
			CEMSLogHelper::LogInfoMsg( EMS_OM_GETTING_GPS_EPHEM );
			hr = m_lpGpsEphemeris->GetGpsEphemerisData( &ulCount, pEphemGPS );

			CEMSLogMsgParam	param;
			if ( hr == EMS_OK )
			{
				param.Add( ulCount );
				CEMSLogHelper::LogInfoMsg( EMS_OM_GOT_GPS_EPHEM, param );
			}
			else
			{
				ulCount = 0;
				param.Add( "GetGPSEphemerisData from Javad failed" );
				CEMSLogHelper::LogWarningMsg( EMS_OM_TRACER, param );
			}

			for ( i=0; i<ulCount; i++)
			{
				bool bSatConfigured = false;

				ulSatID = ephemGPS[i].ulSatPRN + c_nMinGpsSatID;
				if ( IsGpsSatConfigured( ulSatID ) )
				{
					bSatConfigured = true;
					lpEphemRec[j].baseData = ephemGPS[i];
					hr = ValidateGPSephemerisPacket( &ephemGPS[i] );
				}

				if ( (EMS_OK == hr) && bSatConfigured )
				{
					_SaveEphemData( ulSatID, ephemGPS[i] );
					hr = CEMSTLEConvert::GPStoAccurateTLERecord( &tleRecord, 
																 &ephemGPS[i], 
																 ephemGPS[i].ulSatPRN );
					bool  bHasBadParams = false;
					if ( &tleRecord && ( EMS_OK == hr ) )
					{
						tleRecord.nOrbitNumber = _GetOrbitNumber( ulSatID, tleRecord.timeEpoch );
						lpEphemRec[j].ulSatID = ulSatID;
						lpEphemRec[j].constellation = EMS_CONSTELLATION_DASS;
						lpTLERec[j++] = tleRecord;
					}
					else
					{
						bHasBadParams = true;
						CEMSLogMsgParam oParam;
						oParam.Add( "CEMSTLEConvert::GPStoAccurateTLERecord failed" );
						CEMSLogHelper::LogWarningMsg( EMS_OM_TRACER, oParam );
					}
#ifdef DEBUG_GPS_DATA
					_SaveEphemTxtData( ephemGPS[i], tleRecord, bHasBadParams );
#endif 
					
				}
			} // end For loop

			*pulNumRec = j;
		}
		else
		{
			*pulNumRec = 0;
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	catch ( ... )
	{
		hr = EMS_EXCEPTION;
		CEMSLogMsgParam	param;
		param.Add( hr );
		CEMSLogHelper::LogWarningMsg( EMS_OM_EXCEPTION, param );
		throw;
	}

	return hr;
}


EMS_RESULT CEMSJavGPSEphemeris::SetGalSatellites( void )
{
	EMS_RESULT hr = EMS_OK;

	try
	{
		m_ulGalSatCount = 0;

		memset( m_ulGalSats, 0, sizeof( m_ulGalSats ) );
	
		if ( m_lpSatInfo )
		{
			ULONG ulNoradID = 0;

			for ( int i = c_nMinGalSatID; i <= c_nMaxGalSatID; i++ )
			{
				EMS_RESULT hrLocal = m_lpSatInfo->GetNoradID( i, &ulNoradID );
			
				if ( ( EMS_OK == hrLocal ) && ulNoradID && ( m_ulGalSatCount < EMS_MAX_SATELLITES ) )
				{
					m_ulGalSats[ m_ulGalSatCount++ ] = i;
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

EMS_RESULT CEMSJavGPSEphemeris::SetGloSatellites( void )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulSatId;

	m_ulGloSatCount = 0;
	memset( m_ulGloSats, 0, sizeof( m_ulGloSats ) );
	memset( m_lGloSatSlot, 0, sizeof( m_lGloSatSlot ) );
	memset( m_lGloSatChannel, 0, sizeof( m_lGloSatChannel ) );
	
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
				ulSatId = (*Iter)->GetSatID();
				if ( (ulSatId >= c_nMinGloSatID) && (ulSatId <= c_nMaxGloSatID) )
				{
					m_ulGloSats[ m_ulGloSatCount ] = ulSatId;
					m_lGloSatSlot[ m_ulGloSatCount ] = (*Iter)->GetSlot();
					m_lGloSatChannel[ m_ulGloSatCount ] = (*Iter)->GetChannel();
					m_ulGloSatCount++;
				}
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


bool CEMSJavGPSEphemeris::IsGalSatConfigured( ULONG ulSatId )
{
	bool	bFound = false;
	WORD	i;

	for ( i=0; i < m_ulGalSatCount; i++ )
	{
		if ( m_ulGalSats[i] == ulSatId )
			bFound = true;
	}

	return bFound;
}


bool CEMSJavGPSEphemeris::IsGloSatConfigured( LONG  lSlot, LONG lChannel, ULONG *lpulSatId )
{
	bool	bFound = false;
	WORD	i;

	for ( i=0; i < m_ulGloSatCount; i++ )
	{
		if ( (m_lGloSatSlot[i] == lSlot) &&
			 (m_lGloSatChannel[i] == lChannel) )
		{
			*lpulSatId = m_ulGloSats[i];
			bFound = true;
		}
	}

	return bFound;
}


EMS_RESULT CEMSJavGPSEphemeris::ValidateGPSephemerisPacket(LPEMSEPHEMERISDATA lpEphemData )
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

		lpEphemData->nWeekNum = lpEphemData->nWeekNum + 1024;
		iOK &= ( lpEphemData->nWeekNum > 0 );


		EMSTIME tGPS, tNOW;
		tGPS = CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( lpEphemData->dTOE, lpEphemData->nWeekNum, false );
		tNOW = CEMSSystemClock::GetTime();
		double dTimeDiff = double( tGPS.intTime - tNOW.intTime )*1e-9;

		iOK &= ( fabs( dTimeDiff ) < 86400 ); // Time must be within current day
			
		iOK &= ( fabs( lpEphemData->dTOC ) < 1000000 );
		
		iOK &= ( lpEphemData->dE > 0.0 );
		iOK &= ( lpEphemData->dE < 0.5 );  // Eccentricity close to circular orbit

		iOK &= ( lpEphemData->dSqrtA > 3162.3 ); // Semi-major axis greater than 10,000 km
		iOK &= ( lpEphemData->dSqrtA < 7000.0 ); // Semi-major axis greater than 49,000 km

		lpEphemData->dOmega = lpEphemData->dOmega * c_dPI;
		iOK &= ( fabs(lpEphemData->dOmega) <= c_dTwoPI );

		lpEphemData->dOmegaO = lpEphemData->dOmegaO * c_dPI;
		iOK &= ( fabs(lpEphemData->dOmegaO) <= c_dTwoPI );

		lpEphemData->dM0 = lpEphemData->dM0 * c_dPI;
		iOK &= ( fabs(lpEphemData->dM0) <= c_dTwoPI );

		lpEphemData->dIO = lpEphemData->dIO * c_dPI;
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


EMS_RESULT CEMSJavGPSEphemeris::ValidateGLOephemerisPacket(LPEMSGLOEPHEMERIS lpEphemData )
{

	EMS_RESULT	hr = EMS_BAD_PARAM;
	EMSTIME		tGlonass, tNOW;
	CEMSTime	T;
	double		dPositionMinThreshold = 20000;
	double		dPositionMaxThreshold = 40000;
	double		dVelocityMinThreshold = 1.0;
	double		dVelocityMaxThreshold = 7.0;


	if ( lpEphemData )
	{
		// Validate Glonass ephemeris packet time
		bool iOK = true;

		// Get the last leap year
		int				iNbYearsSinceLastLeap;
		int				iLastLeapYear;
		EMSTIME			timeNow = CEMSSystemClock::GetTime();
		CEMSTime		oTime( timeNow );
		EMSTIMEFIELDS	timeFields;

		oTime.GetTime( &timeFields );
		iNbYearsSinceLastLeap = timeFields.nYear % 4;
		iLastLeapYear = timeFields.nYear - iNbYearsSinceLastLeap;


		T.SetTime( iLastLeapYear, 1, 1, 00, 00, 00, 0 );		// Time at Jan 01 of Last Leap Year
		T.AddDays( int(lpEphemData->siDne - 1) );
		tGlonass = T.AddSeconds( lpEphemData->iTb - 10800 ); // 10800 = 3 hours
		tNOW = CEMSSystemClock::GetTime();
		double dTimeDiff = double( tGlonass.intTime - tNOW.intTime )*1e-9;

		iOK &= ( fabs( dTimeDiff ) < 86400 ); // Time must be within current day

		double dSqrtPosition = sqrt( (lpEphemData->dR[0] * lpEphemData->dR[0]) +
									 (lpEphemData->dR[1] * lpEphemData->dR[1]) +
									 (lpEphemData->dR[2] * lpEphemData->dR[2]) );
		iOK &= ( (dSqrtPosition > dPositionMinThreshold) &&
				 (dSqrtPosition < dPositionMaxThreshold) );

		double dSqrtVelocity = sqrt( (lpEphemData->fV[0] * lpEphemData->fV[0]) +
									 (lpEphemData->fV[1] * lpEphemData->fV[1]) +
									 (lpEphemData->fV[2] * lpEphemData->fV[2]) );
		iOK &= ( (dSqrtVelocity > dVelocityMinThreshold) &&
				 (dSqrtVelocity < dVelocityMaxThreshold) );

		if ( iOK )
			hr = EMS_OK;
	}

	return hr;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

