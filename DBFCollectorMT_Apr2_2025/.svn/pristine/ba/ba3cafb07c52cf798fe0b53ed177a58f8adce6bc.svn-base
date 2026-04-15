/********************************************************************
*	Module:			DBFPointingAngles.cpp 
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

	0.0	2010/15/12		rcr		start

********************************************************************/
#include "DBFPointingAngles.h"
#include "emsconst.h"
#include "emsvectr.h"
#include "emscoord.h"

#define INITGUID			
#include <initguid.h>
#include "emsiteif.h"
#include "emslinfo.h"
#include "emstleconv.h"
#include "emsorbit.h"

//#include <memory.h>
//#include <stdlib.h>
//#include <math.h>
//#include <windows.h>
//#include <tchar.h>
//#include <io.h>


/********************************************************************/
//#include <windows.h>
//#include <process.h>
//#include <stdio.h>
//#include <time.h>
//#include <conio.h>

//#include "emsclock.h"
//#include "convutility.h"



const CEMSCoordSystem c_coordSys;

/********************************************************************/



CDBFPointingAngles::CDBFPointingAngles() : m_ulChannels(0), m_ulSatellites(0)
{
}

CDBFPointingAngles::CDBFPointingAngles( const CDBFPointingAngles& x ) : m_ulChannels( x.m_ulChannels ),
							m_ulSatellites(x.m_ulSatellites)
{
}

CDBFPointingAngles::~CDBFPointingAngles( void )
{
	m_ulChannels = 0;
	m_ulSatellites = 0;
		
	if (m_asPhaseVector)
	{
		delete [] m_asPhaseVector;
		m_asPhaseVector = NULL;
	}

}

//---------------------------------------------------------------------------

EMS_RESULT CDBFPointingAngles::Initialize()
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;

	m_ulChannels   = 16; //DBF_MAX_CHANNELS;
	m_ulSatellites = 1;  //DBF_MAX_SATELLITES;

	m_lpOrbit = 0;
	m_ulSats  = 0;
	m_ulLutID = 0;
	
	m_asPhaseVector   = new short[ DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 ];

	memset( m_asPhaseVector, 0, DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 * sizeof(short));
	memset( &m_atleRecord, 0, culMaxSats*sizeof( EMSTLERECORD ) );

	DWORD dwResult = 0;

	if ( !m_bInitialized )
	{
		hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, IID_IEMSOrbit, (LPVOID*)&m_lpOrbit );

		if( EMS_OK == hr )
		{
			IEMSSiteInfo* pSiteInfo = NULL;

			hr = CoCreateInstance( CLSID_EMSSiteInfo, 0, CLSCTX_ALL, IID_IEMSSiteInfo, (LPVOID*)&pSiteInfo );

			if( EMS_OK == hr )
			{
				hr = pSiteInfo->GetLutID( &m_ulLutID );
			}

			if( pSiteInfo )
			{
				pSiteInfo->Release();
				pSiteInfo = NULL;
			}

			IEMSLutInfo* pLutInfo = NULL;

			if( EMS_OK == hr )
			{
				hr = CoCreateInstance( CLSID_EMSLutInfo, 0, CLSCTX_ALL, IID_IEMSLutInfo, (LPVOID*)&pLutInfo );
			}

			if( EMS_OK == hr )
			{
				hr = pLutInfo->GetSiteLocation( m_ulLutID, &m_locnAntenna );
			}


			if( pLutInfo )
			{
				pLutInfo->Release();
				pLutInfo = NULL;
			}
		}

		m_bInitialized = ( hr == EMS_OK );
	}
			
	if( EMS_OK == hr )
	{
		if ( (m_ulChannels>0) && (m_ulSatellites>0) && (m_asPhaseVector) && (m_atleRecord) )
		{
			hr = EMS_OK;
		}
		else
		{
			hr = EMS_UNKNOWN_ERROR;
		}
	}

	return hr;
}

//---------------------------------------------------------------------------
void CDBFPointingAngles::_Reset( )
{
	if ( m_lpOrbit )
	{
		m_lpOrbit->Release( );
		m_lpOrbit = 0;
	}

	if ( m_bInitialized )
	{
		m_bInitialized = FALSE;
	}
	return;
}

//---------------------------------------------------------------------------
EMSVECTORD CDBFPointingAngles::_Convert2UnitVector( const double dAzimuth, const double dElevation )
{
	EMSVECTORD vUnitVector;
		
	// Compute unit vector pointing vectors
	vUnitVector.dX = cos( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
	vUnitVector.dY = sin( dAzimuth * c_dDegToRad ) * sin( dElevation * c_dDegToRad );
	vUnitVector.dZ = cos( dElevation * c_dDegToRad );

	return vUnitVector;
}

//---------------------------------------------------------------------------
EMS_RESULT CDBFPointingAngles::_Satellite2PlateRotation( const double dSatAzimuth, double dSatElevation,
											const double dPlateAzimuth, const double dPlateElevation,
											const double dPlateRoll, const double dMinElevation,
											double dDBFazimuth, double dDBFelevation )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( dSatElevation > 0 )
	{

		EMSVECTORD vSat, vPlate;

		// Convert to radians
		double dRoll    = dPlateRoll * c_dDegToRad;
		double dMinEl   = dMinElevation * c_dDegToRad;

		// Compute unit vector pointing vectors

		vSat   = _Convert2UnitVector( dSatAzimuth, dSatElevation );
		vPlate = _Convert2UnitVector( dSatAzimuth, dSatElevation );

		// Compute satellite elevation in DBF plate coordinates
		dDBFelevation = c_dTwoPI - acos( CEMSVector::DotProduct( vSat, vPlate ) );
		dDBFelevation *= c_dDegToRad;

		if ( dDBFelevation > dMinElevation )
		{
			// Compute azimuth angle
			EMSVECTORD vQ, vR;

			vQ = _Convert2UnitVector( dSatAzimuth, 90.0 - dSatElevation );
			vR = CEMSVector::CrossProduct( vSat, vPlate );

			dDBFazimuth = acos( CEMSVector::DotProduct( vQ, vR ) ) + c_dTwoPI;
			dDBFazimuth *= c_dDegToRad;

			dDBFazimuth += dPlateRoll; 

			hr = EMS_OK;
		}
	}
	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT CDBFPointingAngles::_DBFcellpositions( double *dCellPositionX,
												  double *dCellPositionY )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	{
	
		// wavelength = c /Freq (in metres)
		double dWaveLength = 1000.0 * c_dVelocityOfLight / c_dDownlinkCarrierFreq;

		double dCellPositionX[DBF_MAX_CHANNELS];
		double dCellPositionY[DBF_MAX_CHANNELS];

		double R = 0.12; // cell separation in metres

		double dx = (sqrt(3)*R) / (2*dWaveLength);
		double dy = R / (2*dWaveLength);

		memcpy( &dCellPositionX[0], 0, DBF_MAX_CHANNELS * sizeof(double) );
		memcpy( &dCellPositionY[0], 0, DBF_MAX_CHANNELS * sizeof(double) );

		dCellPositionX[0]  = -3*dx;
		dCellPositionY[0]  =   0.0;
		dCellPositionX[2]  = -2*dx;
		dCellPositionY[2]  =    dy;
		dCellPositionX[4]  =   -dx;
		dCellPositionY[4]  =  2*dy;
		dCellPositionX[6]  =   0.0;
		dCellPositionY[6]  =  3*dy;
		dCellPositionX[8]  = -2*dx;
		dCellPositionY[8]  =   -dy;
		dCellPositionX[10] =   -dx;
		dCellPositionY[10] =   0.0;
		dCellPositionX[12] =   0.0;
		dCellPositionY[12] =    dy;
		dCellPositionX[14] =    dx;
		dCellPositionY[14] =  2*dy;

		for ( int i = 0; i < DBF_MAX_CHANNELS; i =+2 )
		{
			dCellPositionX[i+1] = -dCellPositionX[i];
			dCellPositionY[i+1] = -dCellPositionY[i];
		}
		

		hr = EMS_OK;
	}
	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT CDBFPointingAngles::_PhaseCorrection( const double dDBFazimuth, const double dDBFelevation,
							const double *dCellPositionX, const double *dCellPositionY,
							short *lpPhaseVector)
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( lpPhaseVector > 0 && dDBFelevation > 0 )
	{

		EMSVECTORD vSat;
		vSat = _Convert2UnitVector( dDBFazimuth, dDBFelevation );

		double dScaleFactor = 32768; // 2^15
		
		double dPhase = 0.0;
		for( int i = 0, j = 0; i < DBF_MAX_CHANNELS; i++ )
		{
			dPhase = cos( vSat.dX * dCellPositionX[i] + vSat.dY * dCellPositionY[i] );
			lpPhaseVector[j++] = (short) ( sin( dPhase * c_dTwoPI ) * dScaleFactor );
			lpPhaseVector[j++] = (short) ( cos( dPhase * c_dTwoPI ) * dScaleFactor );
		}

		hr = EMS_OK;
	}
	return hr;
}


//---------------------------------------------------------------------------

EMS_RESULT CDBFPointingAngles::_GetSatelliteAZELs( EMSTIME timeNow, EMSLOCATION location, 
											   ULONG ulMaxSats, EMSSATAZEL* aAzEls, ULONG* pulActual )
{
	EMSAZELVECTOR azelVector;
	EMS_RESULT hr = EMS_OK;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}
	else
		*pulActual = 0;

	if( EMS_OK == hr )
	{
		memset( &azelVector, 0, sizeof( azelVector ) );

		if( m_lpOrbit )
		{
			for( ULONG l = 0; (l < ulMaxSats) && (l < m_ulSats) && ( EMS_OK == hr ); l++ )
			{
				EMSTIMECOORD timeCoord;
				ULONG ulCount = 0;

				//m_tleRecord must be converted to EMSTLEDATA  !!!!!
				EMSTLEDATA2 strTLEData;
				memset( &strTLEData, 0, sizeof(strTLEData) );
				hr = CEMSTLEConvert::TLERecordToTLEData2( &strTLEData, &(m_atleRecord[l]) );

				if( EMS_OK == hr )
				{
					hr = m_lpOrbit->InertialOrbitTLE( &strTLEData.tle, &timeNow, 1, &timeCoord, &ulCount);

					if ( EMS_OK == hr )
					{
						EMSVECTOR vDiff, vObserver = c_coordSys.ToInertialPosition( location, timeNow );
						EMSESUVECTOR esuVector;

						vDiff.fX = timeCoord.coord.radius.fX - vObserver.fX;
						vDiff.fY = timeCoord.coord.radius.fY - vObserver.fY;
						vDiff.fZ = timeCoord.coord.radius.fZ - vObserver.fZ;

						esuVector = c_coordSys.ToTopocentricHorizon( vDiff, location, timeNow );

						azelVector = c_coordSys.ToAzimuthAndElevation( esuVector );

						aAzEls[l].ulSatID = m_atleRecord[l].ulSatID;
						aAzEls[l].degAzimuth = azelVector.azel.degAzimuth;
						aAzEls[l].degElevation = azelVector.azel.degElevation;
						(*pulActual)++;
					}
				}
				else
				{
					printf("\nError converting from EMSTLERECORD to EMSTLEDATA2 for satellite %d.", m_atleRecord[l].ulSatID );
				}
			}
		}
		else
			hr = EMS_NO_ORBIT_OBJ;
	}

	return hr;
}

//---------------------------------------------------------------------------

