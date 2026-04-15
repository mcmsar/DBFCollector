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
#include "emsDBFtypes.h"
#include "emsconst.h"
#include "emsvectr.h"
#include "emscoord.h"

#define INITGUID			
#include <initguid.h>
#include "emsiteif.h"
#include "emsatinf.h"

#include "emslinfo.h"
#include "emstleconv.h"
#include "emsorbit.h"
#include "emssun.h"
#include "configurationaccessor.h"

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

#include "emsclock.h"
#include "convutility.h"



const CEMSCoordSystem c_coordSys;

/********************************************************************/



CDBFPointingAngles::CDBFPointingAngles() : m_ulChannels(0), m_ulSatellites(0),
								m_asPhaseVector(NULL), m_lpOrbit(NULL),
								m_lpSatellite(NULL),m_pafBiasOffset(NULL)
{
	m_bInitialized = FALSE;
	m_bSun = false;
	m_dDlFrequency = 0.0;
}

CDBFPointingAngles::CDBFPointingAngles( const CDBFPointingAngles& x ) : m_ulChannels( x.m_ulChannels ),
							m_ulSatellites(x.m_ulSatellites),
							m_asPhaseVector(NULL), m_lpOrbit(x.m_lpOrbit),
								m_lpSatellite(x.m_lpSatellite)
{
	m_bInitialized = FALSE;

	if( m_lpOrbit )
		m_lpOrbit->AddRef();

	if( m_lpSatellite )
		m_lpSatellite->AddRef();

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

	_Reset();

}

//---------------------------------------------------------------------------

void 
CDBFPointingAngles::_Reset( )
{
	if ( m_lpOrbit )
	{
		m_lpOrbit->Release( );
		m_lpOrbit = 0;
	}

	if ( m_lpSatellite )
	{
		m_lpSatellite->Release( );
		m_lpSatellite = 0;
	}

	if ( m_bInitialized )
	{
		m_bInitialized = FALSE;
	}
	return;
}

//---------------------------------------------------------------------------

void 
CDBFPointingAngles::SetPlate( EMSDBFARRAY *aDBFplate )
{
	memset(&m_aDBFplate, 0, sizeof(EMSDBFARRAY));
	memcpy( &m_aDBFplate, aDBFplate, sizeof(EMSDBFARRAY) );
}
//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::Initialize()
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;

	//m_ulChannels   = 16; //DBF_MAX_CHANNELS;
	//m_ulSatellites = 4;  //DBF_MAX_SATELLITES;
	m_ulChannels   = DBF_MAX_CHANNELS;
	m_ulSatellites = DBF_MAX_SATELLITES;

	//m_dWaveLength  = (c_dVelocityOfLight / 1544.1e6) * 10000000; // in cm  RR big mistake
	m_dWaveLength  = (c_dVelocityOfLight / 1544.1e6) * 10000; // in cm 

	m_lpOrbit = 0;
	m_ulLutID = 0;
	m_ulValidSatID = 0;
	
	m_asPhaseVector   = new short[ DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 ];

	memset( m_asPhaseVector, 0, DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 * sizeof(short));
	memset( &m_atleData, 0, culMaxSats*sizeof( EMSTLEDATA ) );
	memset( m_aulSatID, 0, culMaxSats );

	DWORD dwResult = 0;

	if ( !m_bInitialized )
	{
		hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, IID_IEMSOrbit, (LPVOID*)&m_lpOrbit );
		hr = EMS_FALSE;
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

			if( EMS_OK == hr )
			{
				hr = CoCreateInstance( CLSID_EMSSatelliteInfo, 0, CLSCTX_ALL, IID_IEMSSatelliteInfo12, (LPVOID*)&m_lpSatellite );
			}

			if( EMS_OK == hr )
			{
				// Get valid satellites
				hr = GetValidSatellites();
				//hr = pSatInfo->GetPassSchedulePriority( m_ulLutID, &m_locnAntenna );
			}

		}

		m_bInitialized = ( hr == EMS_OK );
	}
			
	if( EMS_OK == hr )
	{
		if ( (m_ulChannels>0) && (m_ulSatellites>0) && (m_asPhaseVector) && (m_atleData) )
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

EMS_RESULT
CDBFPointingAngles::Initialize( const wchar_t* cwsSatsConfig )
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;

	m_ulChannels   = DBF_MAX_CHANNELS;
	m_ulSatellites = DBF_MAX_SATELLITES;

	//m_dWaveLength  = (c_dVelocityOfLight / 1544.1e6) * 1000; // in metres - 400 satellites 
	m_dWaveLength  = (c_dVelocityOfLight / 1544.1e6) * 100000; // in centimetres 

	m_lpOrbit = 0;
	m_ulLutID = 0;
	m_ulValidSatID = 0;
	
	m_asPhaseVector   = new short[ DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 ];

	memset( m_asPhaseVector, 0, DBF_MAX_CHANNELS * DBF_MAX_SATELLITES * 2 * sizeof(short));
	memset( &m_atleData, 0, culMaxSats*sizeof( EMSTLEDATA ) );
	memset( m_aulSatID, 0, culMaxSats );

	DWORD dwResult = 0;

	if ( !m_bInitialized )
	{
		hr = CoCreateInstance( CLSID_EMSOrbit, 0, CLSCTX_ALL, IID_IEMSOrbit, (LPVOID*)&m_lpOrbit );
		//hr = EMS_FALSE;

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

			if( EMS_OK == hr )
			{
				hr = CoCreateInstance( CLSID_EMSSatelliteInfo, 0, CLSCTX_ALL, IID_IEMSSatelliteInfo12, (LPVOID*)&m_lpSatellite );
			}

			if( EMS_OK == hr )
			{
				//if( cwsSatsConfig )
				std::string str = CEMSConversionUtil::ConvertToString(cwsSatsConfig);
				if(!str.empty())
				{
					hr = _GetValidSatellites( cwsSatsConfig );
				}
				else
				{
					hr = GetValidSatellites();
					//hr = pSatInfo->GetPassSchedulePriority( m_ulLutID, &m_locnAntenna );
				}
			}

		}
		//double dlFreq = m_dDlFrequency;
		//m_dWaveLength  = (c_dVelocityOfLight / 1544.5e6) * 1000; // in metres - leo satellites 
		m_bInitialized = ( hr == EMS_OK );
	}
			
	if( EMS_OK == hr )
	{
		if ( (m_ulChannels>0) && (m_ulSatellites>0) && (m_asPhaseVector) && (m_atleData) )
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

EMS_RESULT
CDBFPointingAngles::GetValidSatellites()
{
	EMS_RESULT hr = EMS_UNKNOWN_ERROR;

	if( m_lpOrbit )
	{
		m_ulValidSatID = 0;

		ULONG ulSatPriority = 0;

		EMSTLEDATA tleData;
		EMSTIME timeNow;
		CEMSSystemClock     oTime;

		timeNow = oTime.GetTime();

		memset( &tleData, 0, sizeof(EMSTLEDATA) );

//		for( ULONG l = 0; (l < 100) & (m_ulValidSatID < culMaxSats) ; l++ )//700 - Smruti commented
//		for( ULONG l = 400; (l < 500) & (m_ulValidSatID < culMaxSats) ; l++ ) - requirement
		for( ULONG l = 0; (l < 500) & (m_ulValidSatID < culMaxSats) ; l++ )
		{
			hr = m_lpSatellite->GetPassSchedulePriority( l, &ulSatPriority );
			
			if( EMS_OK == hr && ulSatPriority > 0 )
			{
				hr = m_lpOrbit->GetSatelliteTLE( l, timeNow, &tleData );

				if( EMS_OK == hr )
				{
					m_aulSatID[ m_ulValidSatID ] = l;
					m_aulSatPriority[ m_ulValidSatID ] = ulSatPriority;
					memcpy( &m_atleData[ m_ulValidSatID ], &tleData, sizeof(EMSTLEDATA) );

					m_ulValidSatID++;
				}
			}
		}
	}

	if( m_ulValidSatID > 0 )
	{
		hr = EMS_OK;
	}

	return hr;
}


EMS_RESULT 
CDBFPointingAngles::_GetValidSatellites( const wchar_t* cwsSatsConfig )
{
	EMS_RESULT hr = EMS_BAD_PARAM;
	
	if( cwsSatsConfig && m_lpOrbit )
	{
		EMSTLEDATA tleData;
		EMSTIME timeNow;
		CEMSSystemClock     oTime;

		timeNow = oTime.GetTime();

		memset( &tleData, 0, sizeof(EMSTLEDATA) );

		m_ulValidSatID = 0;

		CEMSConfigurationAccessor oConfig;

		oConfig.SetSource(cwsSatsConfig);

		m_bSun = oConfig.GetElementValueBoolean(L"sun");
		CEMSObjectList<CEMSConfigurationAccessor> olstSatsConfig = oConfig.GetAccessorList( L"sat" );

		olstSatsConfig.MoveFirst();

		for( ULONG l = 0; (l < olstSatsConfig.Count()) && (m_ulValidSatID < culMaxSats); l++ )
		{
			try
			{
				CEMSConfigurationAccessor oSatConfig = olstSatsConfig.GetNext();
				
				ULONG ulSatID = oSatConfig.GetAttributeValueULong( L"@id" );
				m_dDlFrequency = oSatConfig.GetElementValueDouble(L"signal_sat/dl_frequency");
				//ULONG ulPriority = oSatConfig.GetElementValueULong( L"priority" ); - Smruti commented
				ULONG ulPriority = oSatConfig.GetElementValueULong( L"orbit/priority" );
				
				if( ulSatID < 700 && ulPriority > 0 )
				{
					hr = m_lpOrbit->GetSatelliteTLE( ulSatID, timeNow, &tleData );

					if( EMS_OK == hr )
					{
						m_aulSatID[ m_ulValidSatID ] = ulSatID;
						m_aulSatPriority[ m_ulValidSatID ] = ulPriority;
						memcpy( &m_atleData[ m_ulValidSatID ], &tleData, sizeof(EMSTLEDATA) );

						m_ulValidSatID++;
					}
				}
			}
			catch(...)
			{
				// error.
			}
		}

	}

	return hr;
}

//---------------------------------------------------------------------------

int
CDBFPointingAngles::GetConstellationType( ULONG ulSatID )
{
	int nSatType;

	nSatType = ulSatID / 100;

	return nSatType;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::GetConstellationAZELs( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRecords = 0;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}
	else
	{
		ulRecords = *pulActual;
		*pulActual = 0;
	}

	if( EMS_OK == hr )
	{

		// Determine satellite constellation counts

		int anSatCount[6];
		memset( anSatCount, 0, sizeof(int) * 6 );

		int nSatType  = -1;
		ULONG i;

		for( i = 0; i < ulRecords; i++ )
		{
			nSatType = GetConstellationType( aAzEls[i].ulSatID );

			if ( (nSatType > -1) && (nSatType < 6) )
			//if ( (nSatType > 3) && (nSatType < 6) )
			{
				anSatCount[nSatType] += aAzEls[i].ulSatPriority;
			}
		}

		// Choose constellation with maximum number of visible satellites

		int nSatTypeX = -1;
		int nMaxCount = 0;

		//for ( i = 0; i < 4; i++ )
		for ( i = 0; i < 6; i++ )
		{
			if ( anSatCount[i] > nMaxCount )
			{
				nMaxCount = anSatCount[i];
				nSatTypeX = i;
			}
		}

		for ( i = 0; i < ulRecords; i++ )
		{

			nSatType = GetConstellationType( aAzEls[i].ulSatID );

			if (  nSatType == nSatTypeX || aAzEls[i].ulSatID == 999) //include sun vector
			{
				aAzEls[*pulActual] = aAzEls[i];
				(*pulActual)++;
			}
		}

	}

	return hr;
}

//---------------------------------------------------------------------------

EMSVECTORD
CDBFPointingAngles::_Convert2UnitVector( const double dAzimuth, const double dElevation )
{
	EMSVECTORD vUnitVector;
		
	// Compute unit vector pointing vectors
	vUnitVector.dX = cos( dAzimuth * c_dDegToRad ) * cos( dElevation * c_dDegToRad );
	vUnitVector.dY = sin( dAzimuth * c_dDegToRad ) * cos( dElevation * c_dDegToRad );
	vUnitVector.dZ = sin( dElevation * c_dDegToRad );

	return vUnitVector;
}
//---------------------------------------------------------------------------

void
CDBFPointingAngles::RotationMatrix( )
{
	EMSVECTORD vPlateX, vPlateY, vPlateZ;
	EMSVECTORD X, Y, Z;
	double dCangle1,dCangle2, dCangle3;

	double dPlateAzimuth   = m_aDBFplate.fPlateFaceAzimuth;
	double dPlateElevation = m_aDBFplate.fPlateFaceElevation;

	m_vRotationRow1.dX = -sin(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow1.dY = cos(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow1.dZ = 0.0;

	m_vRotationRow2.dX = -sin(dPlateElevation  * c_dDegToRad) * cos(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow2.dY = -sin(dPlateElevation  * c_dDegToRad) * sin(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow2.dZ = cos(dPlateElevation  * c_dDegToRad);

	m_vRotationRow3.dX = cos(dPlateElevation  * c_dDegToRad) * cos(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow3.dY = cos(dPlateElevation  * c_dDegToRad) * sin(dPlateAzimuth  * c_dDegToRad);
	m_vRotationRow3.dZ = sin(dPlateElevation  * c_dDegToRad);

	// Validiation of matrix

	vPlateX = _Convert2UnitVector( dPlateAzimuth+90.0, 0.0 );
	vPlateY = _Convert2UnitVector( dPlateAzimuth-180, 90.0-dPlateElevation );
	vPlateZ = _Convert2UnitVector( dPlateAzimuth, dPlateElevation );

	dCangle1 = CEMSVector::DotProduct( vPlateX, vPlateY );
	dCangle2 = CEMSVector::DotProduct( vPlateY, vPlateZ );
	dCangle3 = CEMSVector::DotProduct( vPlateZ, vPlateX );

	X.dX =  CEMSVector::DotProduct( m_vRotationRow1, vPlateX );
	X.dY =  CEMSVector::DotProduct( m_vRotationRow2, vPlateX );
	X.dZ =  CEMSVector::DotProduct( m_vRotationRow3, vPlateX );

	Y.dX =  CEMSVector::DotProduct( m_vRotationRow1, vPlateY );
	Y.dY =  CEMSVector::DotProduct( m_vRotationRow2, vPlateY );
	Y.dZ =  CEMSVector::DotProduct( m_vRotationRow3, vPlateY );

	Z.dX =  CEMSVector::DotProduct( m_vRotationRow1, vPlateZ );
	Z.dY =  CEMSVector::DotProduct( m_vRotationRow2, vPlateZ );
	Z.dZ =  CEMSVector::DotProduct( m_vRotationRow3, vPlateZ );

	return;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::_Satellite2PlateRotation( const double dSatAzimuth, double dSatElevation,
											double *dDBFazimuth, double *dDBFelevation )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( dSatElevation > 0 )
	{

		EMSVECTORD vSat, vSatDBF, vPlateX, vPlateY, vPlateZ;
		EMSVECTORD vQ, vR, vS;
		
		double dCangle, dCangle1;
		double dAz, dEl;
		double dAz1, dEl1;

		double dPlateAzimuth   = m_aDBFplate.fPlateFaceAzimuth;
		double dPlateElevation = m_aDBFplate.fPlateFaceElevation;

		// Compute unit vector pointing vectors
		vSat    = _Convert2UnitVector( dSatAzimuth, dSatElevation );

		vSatDBF.dX =  CEMSVector::DotProduct( m_vRotationRow1, vSat );
		vSatDBF.dY =  CEMSVector::DotProduct( m_vRotationRow2, vSat );
		vSatDBF.dZ =  CEMSVector::DotProduct( m_vRotationRow3, vSat );

		dEl = 90.0 - acos( vSatDBF.dZ ) * c_dRadToDeg;
		dAz = atan2 ( vSatDBF.dX, vSatDBF.dY ) * c_dRadToDeg;

		// Validation

		vPlateX = _Convert2UnitVector( dPlateAzimuth+90.0, 0.0 );
		vPlateY = _Convert2UnitVector( dPlateAzimuth-180, 90.0-dPlateElevation );
		vPlateZ = _Convert2UnitVector( dPlateAzimuth, dPlateElevation );

		// Compute satellite elevation in DBF plate coordinates
		dCangle = CEMSVector::DotProduct( vSat, vPlateZ );
		dEl1 = 90.0 - acos( dCangle ) * c_dRadToDeg;
		dAz1 = 0.0;

		// Compute azimuth angle
		if ( dEl1 <= 89.95 )
		{
 			vQ  = CEMSVector::CrossProduct( vSat, vPlateZ );
			vQ  = CEMSVector::Normalize( vQ );
			vR  = CEMSVector::CrossProduct( vPlateZ, vQ );
			vR  = CEMSVector::Normalize( vR );

		//dCangle2 = CEMSVector::DotProduct( vSat, vPlateZ );
		//vS.dX = vSat.dX - dCangle2*vPlateZ.dX; 
		//vS.dY = vSat.dY - dCangle2*vPlateZ.dY; 
		//vS.dZ = vSat.dZ - dCangle2*vPlateZ.dZ; 
		//vS  = CEMSVector::Normalize( vS );

			dCangle1 =  CEMSVector::DotProduct( vR, vPlateX );
			dCangle  =  CEMSVector::DotProduct( vR, vPlateY );
			dAz1  = acos( dCangle )  * c_dRadToDeg;
			if ( dCangle1 < 0.0)
			{
				dAz1 = -dAz1;
			}
		}

		*dDBFazimuth   = fmod( dAz + 360.0, 360.0 );
		*dDBFelevation = dEl;

		hr = EMS_OK;

	}
	return hr;
}

//---------------------------------------------------------------------------
// Zeinab's function
//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::_Satellite2PlateRotation_V2( const double dSatAzimuth, double dSatElevation,
												 double *dDBFazimuth, double *dDBFelevation )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( dSatElevation > 0 )
	{

		EMSVECTORD vSat, vPlateX, vPlateY, vPlateZ;
		EMSVECTORD vS;
		
		double dAz = 0;
		double dEl = 0;
		

		double dPlateAzimuth   = m_aDBFplate.fPlateFaceAzimuth;
		double dPlateElevation = -m_aDBFplate.fPlateFaceElevation;

		// Compute unit vector pointing vectors
		vSat    = _Convert2UnitVector( dSatAzimuth, dSatElevation );


		/*vPlateX.dX = -sin(dPlateAzimuth * c_dDegToRad);
		vPlateX.dY = cos(dPlateAzimuth * c_dDegToRad);
                vPlateX.dZ = 0.0 ;

		vPlateY.dX = -sin(dPlateElevation * c_dDegToRad) * cos(dPlateAzimuth * c_dDegToRad);
		vPlateY.dY = -sin(dPlateElevation * c_dDegToRad) * sin(dPlateAzimuth * c_dDegToRad);
                vPlateY.dZ = cos(dPlateElevation * c_dDegToRad) ;

		vPlateZ.dX = cos(dPlateElevation * c_dDegToRad) * cos(dPlateAzimuth * c_dDegToRad);
		vPlateZ.dY = cos(dPlateElevation * c_dDegToRad) * sin(dPlateAzimuth * c_dDegToRad);
                vPlateZ.dZ = sin(dPlateElevation * c_dDegToRad) ;*/
		
		vPlateX.dX =  cos(dPlateAzimuth * c_dDegToRad);
		vPlateX.dY =  sin(dPlateAzimuth * c_dDegToRad);
		vPlateX.dZ =  0.0 ;

		vPlateY.dX =  -cos(dPlateElevation * c_dDegToRad) * sin(dPlateAzimuth * c_dDegToRad);
		vPlateY.dY =  cos(dPlateElevation * c_dDegToRad) * cos(dPlateAzimuth * c_dDegToRad);
		vPlateY.dZ =  sin(dPlateElevation * c_dDegToRad) ;

		vPlateZ.dX =  sin(dPlateElevation * c_dDegToRad) * sin(dPlateAzimuth * c_dDegToRad);
		vPlateZ.dY =  -sin(dPlateElevation * c_dDegToRad) * cos(dPlateAzimuth * c_dDegToRad);
		vPlateZ.dZ =  cos(dPlateElevation * c_dDegToRad) ;

		vS.dX = CEMSVector::DotProduct( vSat, vPlateX );
		vS.dY = CEMSVector::DotProduct( vSat, vPlateY );
		vS.dZ = CEMSVector::DotProduct( vSat, vPlateZ );	
		
		
		dEl = asin( vS.dZ ) * c_dRadToDeg;

		// Compute azimuth angle
		if ( dEl <= 89.95 )
		{
			dAz = atan2( vS.dY , vS.dX ) * c_dRadToDeg ;

			if ( dAz > 180)
			{
				dAz = dAz - 360;
			}
			else
			{
				dAz = dAz;
			}

		}

		*dDBFazimuth   = fmod( dAz + 360.0, 360.0 );
		*dDBFelevation = dEl;

		hr = EMS_OK;

	}
	return hr;
}

//---------------------------------------------------------------------------

//EMS_RESULT
//CDBFPointingAngles::_DBFcellpositions( double *dCellPositionX,
//												  double *dCellPositionY )
//{
//	EMS_RESULT hr = EMS_BAD_PARAM;
//
//	{
//	
//		// wavelength = c /Freq (in metres)
//		double dWaveLength = 1000.0 * c_dVelocityOfLight / c_dDownlinkCarrierFreq;
//
//		double dCellPositionX[DBF_MAX_CHANNELS];
//		double dCellPositionY[DBF_MAX_CHANNELS];
//
//		double dy = 0.095250 / dWaveLength;
//		double dx = 2 * 0.047625 / dWaveLength;
//
//		double dxcentre = 8.5 * dx / 2;
//		double dycentre = 6 * dy / 2;
//
//		memcpy( &dCellPositionX[0], 0, DBF_MAX_CHANNELS * sizeof(double) );
//		memcpy( &dCellPositionY[0], 0, DBF_MAX_CHANNELS * sizeof(double) );
//
//		for ( int i = 0; i < 64; i++ )
//		{
//			switch ( i )
//			{
//				case 9:
//				dCellPositionX[9] = dCellPositionX[0] + dx/2;
//				dCellPositionY[9] = dCellPositionY[0] + dy;
//				break;
//				case 18:
//				dCellPositionX[18] = dCellPositionX[0];
//				dCellPositionY[18] = dCellPositionY[0] + 2*dy;
//				break;
//				case 27:
//				dCellPositionX[27] = dCellPositionX[0] + dx/2;;
//				dCellPositionY[27] = dCellPositionY[0] + 3*dy;
//				break;
//				case 36:
//				dCellPositionX[36] = dCellPositionX[0];
//				dCellPositionY[36] = dCellPositionY[0] + 4*dy;
//				break;
//				case 45:
//				dCellPositionX[45] = dCellPositionX[0] + dx/2;;
//				dCellPositionY[45] = dCellPositionY[0] + 4*dy;
//				break;
//				case 54:
//				dCellPositionX[54] = dCellPositionX[0];
//				dCellPositionY[54] = dCellPositionY[0] + 5*dy;
//				break;
//				default:
//				dCellPositionX[i+1]  = dCellPositionX[i] + dx;
//				dCellPositionY[i+1]  = dCellPositionX[i];
//				break;
//			}
//			
//
//		}
//		
//
//		for ( int i = 0; i < 64; i++ )
//		{
//			dCellPositionX[i] =  dCellPositionX[i] - dxcentre;
//			dCellPositionY[i] =  dCellPositionY[i] - dycentre;
//		}
//
//		hr = EMS_OK;
//	}
//	return hr;
//}
//

//---------------------------------------------------------------------------

void
CDBFPointingAngles::_NearFieldCorrections( EMSDBFAZEL *aAzEl , int index, bool bAdd )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	for ( int i = 1; i < DBF_MAX_CHANNELS; i++ )
	{
		if ( bAdd )
		{
			m_aDBFplate.emsDBFCells[i].fRHCP += m_aDBFplate.emsFixedPoints[index].fPhaseAdjust[i];
			m_aDBFplate.emsDBFCells[i].fLHCP += m_aDBFplate.emsFixedPoints[index].fPhaseAdjust[i];
		}
		else
		{
			m_aDBFplate.emsDBFCells[i].fRHCP -= m_aDBFplate.emsFixedPoints[index].fPhaseAdjust[i];
			m_aDBFplate.emsDBFCells[i].fLHCP -= m_aDBFplate.emsFixedPoints[index].fPhaseAdjust[i];
		}
	}
	return;
}
//---------------------------------------------------------------------------

void
CDBFPointingAngles::_ComputeNearFieldCorrections( EMSDBFAZEL *aAzEl , int index )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( aAzEl > 0 )
	{

		EMSVECTORD vSat;
		vSat = _Convert2UnitVector( aAzEl[0].degPlateAzimuth, aAzEl[0].degPlateElevation );

		// Note: Azimuth is measured from the Y axis of the plate. Therefore there is a 90 degree switch in the vSat vector.

		double dSatDist = m_aDBFplate.emsFixedPoints[index].fFixedPointDistance;
		double dCosAngle = 0.0;
		double dAngle = 0.0;
		double dCellRadius = 0.0;
		double dActualDistance = 0.0;  // distance from element to transmitter (in cm)
		double dExtraDistance = 0.0;


		// Perform loop for number of cells NOT number of channels
		for( int i = 1; i < DBF_MAX_CHANNELS; i++ )
		{
			
			//dCosAngle = m_aDBFplate.emsDBFCells[i].fXcoord * vSat.dX * dSatDist  + m_aDBFplate.emsDBFCells[i].fYcoord * vSat.dY * dSatDist;
			dCosAngle = m_aDBFplate.emsDBFCells[i].fXcoord * vSat.dY * dSatDist  + m_aDBFplate.emsDBFCells[i].fYcoord * vSat.dX * dSatDist;

			dCellRadius = sqrt( m_aDBFplate.emsDBFCells[i].fXcoord * m_aDBFplate.emsDBFCells[i].fXcoord
							  + m_aDBFplate.emsDBFCells[i].fYcoord * m_aDBFplate.emsDBFCells[i].fYcoord );


			dActualDistance = sqrt( dSatDist*dSatDist + dCellRadius*dCellRadius - 2.0*dCosAngle);

			dAngle = acos( dCosAngle/dCellRadius/dSatDist );

			dExtraDistance = dCellRadius * sin( 180 - dAngle );

			m_aDBFplate.emsFixedPoints[index].fPhaseAdjust[i] = (float) (( dActualDistance - dSatDist - dExtraDistance ) / m_dWaveLength * 360.0 );

		}
	}

	//m_aDBFplate;
}

EMS_RESULT
CDBFPointingAngles::CellPhaseAngles( EMSDBFAZEL *aAzEl )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if( aAzEl > 0 )
	{

		EMSVECTORD vSat;
		
		// Note: Azimuth is measured from the Y axis of the plate. Therefore there is a 90 degree switch in the vSat vector.
		vSat = _Convert2UnitVector( (90.0-aAzEl[0].degPlateAzimuth), aAzEl[0].degPlateElevation );
		
		double dPhase = 0.0;
		double dCellRadius = 0.0;
		double dDelayDistance = 0.0;  // delay distance from centre of array (in metres)

		// Perform loop for number of cells NOT number of channels
		for( int i = 1; i < DBF_MAX_CHANNELS; i++ )
		{
			//dCellRadius = sqrt( m_aDBFplate.fXcoord[i] * m_aDBFplate.fXcoord[i]
			//				  + m_aDBFplate.fYcoord[i] * m_aDBFplate.fYcoord[i] );

			//dDelayDistance = vSat.dX * m_aDBFplate.fXcoord[i] + vSat.dY * m_aDBFplate.fYcoord[i];
			dCellRadius = sqrt( m_aDBFplate.emsDBFCells[i].fXcoord * m_aDBFplate.emsDBFCells[i].fXcoord
							  + m_aDBFplate.emsDBFCells[i].fYcoord * m_aDBFplate.emsDBFCells[i].fYcoord );


			dDelayDistance = vSat.dX * m_aDBFplate.emsDBFCells[i].fXcoord + vSat.dY * m_aDBFplate.emsDBFCells[i].fYcoord;
			//dDelayDistance = vSat.dY * m_aDBFplate.emsDBFCells[i].fXcoord + vSat.dX * m_aDBFplate.emsDBFCells[i].fYcoord;

			dPhase = dDelayDistance / m_dWaveLength;
			
			//Question if it is should be applied now or later 
			//if ( m_aDBFplate.wPlatePolarization )
				//dPhase += (m_aDBFplate.emsDBFCells[i].fRHCP * c_dTwoPI/360.00);
			//else
				//dPhase += (m_aDBFplate.emsDBFCells[i].fLHCP * c_dTwoPI/360.00);

			dPhase = fmod(dPhase * c_dTwoPI, c_dTwoPI );

			// khalid's changes, Zeinab's change
			//aAzEl[0].acmplxPhase[m_aDBFplate.wCellID[i]].re = (float) cos( dPhase );
			//aAzEl[0].acmplxPhase[m_aDBFplate.wCellID[i]].im = (float) sin( dPhase );
		
			aAzEl[0].acmplxPhase[m_aDBFplate.emsDBFCells[i].wChannelID].re = (float) cos( dPhase );
			aAzEl[0].acmplxPhase[m_aDBFplate.emsDBFCells[i].wChannelID].im = (float) sin( dPhase );
			
			aAzEl[0].acmplxPhase[m_aDBFplate.emsDBFCells[i].wChannelID].im *= -1.0;;

		}

		hr = EMS_OK;
	}
	return hr;
}



//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::GetPlateAZELs( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRecords = 0;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}
	else
	{
		ulRecords = *pulActual;
		*pulActual = 0;
	}

	if( EMS_OK == hr )
	{
	
		double dDBFazimuth;
		double dDBFelevation;
		double dPlateMinElevation;

		for ( ULONG l = 0; l < ulRecords; l++ )
		{
//			hr = _Satellite2PlateRotation( aAzEls[l].degSatAzimuth, aAzEls[l].degSatElevation,
	//									&dDBFazimuth, &dDBFelevation );
			// ZA use the new function
			hr = _Satellite2PlateRotation_V2( aAzEls[l].degSatAzimuth, aAzEls[l].degSatElevation,
											&dDBFazimuth, &dDBFelevation );
			if (aAzEls[l].ulSatID > 400) 
			{
					dPlateMinElevation = cdPlateMinElevationMEO;
			}
			else
			{
					dPlateMinElevation = cdPlateMinElevationLEO;
			}
			if ( (EMS_OK == hr) && ( dDBFelevation > dPlateMinElevation ) )
			{
				
				aAzEls[*pulActual] = aAzEls[l];
				aAzEls[*pulActual].degPlateAzimuth   = dDBFazimuth;
				aAzEls[*pulActual].degPlateElevation = dDBFelevation;

				(*pulActual)++;
			}

		}

	}

	return hr;
}
//---------------------------------------------------------------------------


void
CDBFPointingAngles::GetFixedPointSched( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	*pulActual = 1;
	int iCount = 0;

	for ( int i = 0; i < m_aDBFplate.wFixedPointNumber; i++ )
	{
		if ( m_aDBFplate.emsFixedPoints[i].bEnabled )
		{
			aAzEls[iCount].degSatAzimuth = m_aDBFplate.emsFixedPoints[i].fFixPointAzimuth;
			aAzEls[iCount].degSatElevation = m_aDBFplate.emsFixedPoints[i].fFixPointElevation;
			GetPlateAZELs( &aAzEls[iCount], pulActual );
			_ComputeNearFieldCorrections( &aAzEls[iCount], i );
			_NearFieldCorrections( &aAzEls[iCount], i, true );
			CellPhaseAngles( &aAzEls[iCount] );
			_NearFieldCorrections( &aAzEls[iCount], i, false );

			iCount++;
		}
	}
	*pulActual = iCount;
	//GetNullPhase( aAzEls, &ulActual );
	return;
}

EMS_RESULT
CDBFPointingAngles::CheckLEOMEO( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;
	
	ULONG ulCount = 0;
	bool bLEO = false;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}
	for( ULONG i = 0; i < *pulActual; i++ )
	{
		if( aAzEls[i].ulSatID < 200 ) bLEO = true;
	}

	if( bLEO )
	{
		for( ULONG i = 0; i < *pulActual; i++ )
		{
			if( aAzEls[i].ulSatID < 200 )
			{
				memcpy( &aAzEls[ulCount], &aAzEls[i], sizeof(EMSDBFAZEL) );
				ulCount++;
			}
		}
		*pulActual = ulCount;
	}
	return hr;
}

EMS_RESULT
CDBFPointingAngles::GetSatelliteAZELs( EMSTIME timeNow, EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMSAZELVECTOR azelVector;
	EMS_RESULT hr = EMS_OK;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}
	else
		*pulActual = 0;

	ULONG ulActual = 0;

	if( EMS_OK == hr )
	{
		memset( &azelVector, 0, sizeof( azelVector ) );

		if( m_lpOrbit )
		{
			EMSTIMECOORD timeCoord;
			ULONG ulCount = 0;

			EMSTLEDATA tleData;
			memset( &tleData, 0, sizeof(EMSTLEDATA) );

			for( ULONG l = 0; (l < m_ulValidSatID) && ( EMS_OK == hr ); l++ )
			{

				hr = m_lpOrbit->GetSatelliteTLE( m_aulSatID[l], timeNow, &tleData );

				if( EMS_OK == hr  )
				{

					hr = m_lpOrbit->InertialOrbitTLE( &tleData, &timeNow, 1, &timeCoord, &ulCount);

					if ( EMS_OK == hr )
					{
						EMSVECTOR vDiff, vObserver;
						EMSESUVECTOR esuVector;
						
						vObserver = c_coordSys.ToInertialPosition( m_locnAntenna, timeNow );

						vDiff.fX = timeCoord.coord.radius.fX - vObserver.fX;
						vDiff.fY = timeCoord.coord.radius.fY - vObserver.fY;
						vDiff.fZ = timeCoord.coord.radius.fZ - vObserver.fZ;

						esuVector = c_coordSys.ToTopocentricHorizon( vDiff, m_locnAntenna, timeNow );

						azelVector = c_coordSys.ToAzimuthAndElevation( esuVector );

						if ( azelVector.azel.degElevation > cdSiteMinElevation )
						{
							aAzEls[ulActual].ulSatID = m_aulSatID[l];
							aAzEls[ulActual].ulSatPriority = m_aulSatPriority[l];
							aAzEls[ulActual].degSatAzimuth = fmod(azelVector.azel.degAzimuth +360.0, 360.0);
							aAzEls[ulActual].degSatElevation = azelVector.azel.degElevation;
							ulActual++;
						}
					}
				}
				else
				{
					printf("\nError finding satellite %d.",m_aulSatID[l] );
//					hr = EMS_FALSE;
				}

			}
		}
		else
		{
			hr = EMS_NO_ORBIT_OBJ;
		}

		*pulActual = ulActual;
		if(m_bSun)
		{
			// Add sun vector
			EMSAZELVECTOR aSun;
			
			aSun = CEMSSun::SunPoint( timeNow, m_locnAntenna );

			if ( aSun.azel.degElevation > cdSiteMinElevation )
			{
				aAzEls[*pulActual].ulSatID = 999;
				aAzEls[*pulActual].ulSatPriority = 100;
				aAzEls[*pulActual].degSatAzimuth = fmod( aSun.azel.degAzimuth + 360.0, 360.0 );
				aAzEls[*pulActual].degSatElevation = aSun.azel.degElevation;
				(*pulActual)++;
			}

		}
	}

	return hr;
}

//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::ApplyPhaseBias( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !pulActual || !aAzEls )
	{
		hr = EMS_INVALID_PTR;
	}

	if ( EMS_OK == hr )
	{
	
		ULONG i,j;
		double dPhase;
		double dCosPhaseOffset, dSinPhaseOffset;
		double dCosPhase, dSinPhase;


		for( i = 0; i < *pulActual; i++ )
		{ 
			for( j = 0; j < DBF_MAX_CHANNELS; j++ )
			{
				if ( m_aDBFplate.wPlatePolarization )
					dPhase = m_aDBFplate.emsDBFCells[j].fRHCP * c_dTwoPI/360.00;
				else
					dPhase = m_aDBFplate.emsDBFCells[j].fLHCP * c_dTwoPI/360.00;

				dCosPhaseOffset = cos(dPhase);
				dSinPhaseOffset = sin(dPhase);
				//dSinPhaseOffset = -sin(dPhase);

				dCosPhase = aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].re;
				dSinPhase = aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].im;

				aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].re = dCosPhase*dCosPhaseOffset - dSinPhase*dSinPhaseOffset;
				aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].im = dCosPhase*dSinPhaseOffset + dSinPhase*dCosPhaseOffset;
			}
		}
	}

	return hr;
}

EMS_RESULT
CDBFPointingAngles::SetBiasOffset( const float* biasOffset)
{
	EMS_RESULT hr = EMS_OK;
	//memcpy( m_pafBiasOffset, biasOffset, 32 * sizeof(float) );
	m_pafBiasOffset = const_cast< float * > (biasOffset);
	return hr;
}

EMS_RESULT
CDBFPointingAngles::ApplyPhaseBias1( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !pulActual || !aAzEls )
	{
		hr = EMS_INVALID_PTR;
	}

	if ( EMS_OK == hr )
	{
	
		ULONG i,j;
		double dPhase;
		double dCosPhaseOffset, dSinPhaseOffset;
		double dCosPhase, dSinPhase;
		double dMag;


		for( i = 0; i < *pulActual; i++ )
		{ 
			for( j = 0; j < DBF_MAX_CHANNELS; j++ )
			{
				if ( m_aDBFplate.wPlatePolarization )
					dPhase = m_aDBFplate.emsDBFCells[j].fRHCP * c_dTwoPI/360.00;
				else if( m_pafBiasOffset )
					//dPhase = m_pafBiasOffset[j] *-1.0;
					dPhase = m_pafBiasOffset[j];
				else
					dPhase = m_aDBFplate.emsDBFCells[j].fLHCP * c_dTwoPI/360.00;


				dCosPhaseOffset = cos(dPhase);
				dSinPhaseOffset = sin(dPhase);
				//dSinPhaseOffset = -sin(dPhase);

				dCosPhase = aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].re;
				dSinPhase = aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].im;

				dMag = sqrt( dCosPhase*dCosPhase + dSinPhase*dSinPhase );
				if (dMag < 1.0e-6 ) dMag = 1.0e-6;
				dCosPhase /= dMag;
				dSinPhase /= dMag;


				aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].re = dCosPhase*dCosPhaseOffset - dSinPhase*dSinPhaseOffset;
				aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].im = dCosPhase*dSinPhaseOffset + dSinPhase*dCosPhaseOffset;

				//aAzEls[i].acmplxPhase[m_aDBFplate.emsDBFCells[j].wChannelID].im *= -1.0;
			}
		}
	}

	return hr;
}
//---------------------------------------------------------------------------

EMS_RESULT
CDBFPointingAngles::GetDBFPhase( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !pulActual || !aAzEls )
	{
		hr = EMS_INVALID_PTR;
	}

	if ( EMS_OK == hr )
	{
	
		ULONG i;

		for( i = 0; i < *pulActual; i++ )
		{ 
			hr = CellPhaseAngles( &aAzEls[i]);
			//hr = _CellPhaseAngles( (aAzEls+i));
		}
	}

	return hr;
}

EMS_RESULT
CDBFPointingAngles::GetSeparationAngles( EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}

	if( EMS_OK == hr )
	{

		ULONG i, j;
		EMSVECTORD vSat1, vSat2;
		double dMinSA, dSA;

		for( i = 0; i < *pulActual; i++ )
		{ 
			vSat1 = _Convert2UnitVector( aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );

			dMinSA = 90.0;
			for( j = 0; j < *pulActual; j++ )
			{ 
				if ( !(i == j) )
				{
				
					vSat2 = _Convert2UnitVector( aAzEls[j].degPlateAzimuth, aAzEls[j].degPlateElevation );
					dSA = acos( vSat1.dX * vSat2.dX + vSat1.dY * vSat2.dY +vSat1.dZ * vSat2.dZ );
					dSA *= c_dRadToDeg;
					if ( dSA > 0 && dSA < dMinSA )
					{
						dMinSA = dSA;
					}
				}
			}
			aAzEls[i].degMinSeparation = dMinSA;

		}

	}

	return hr;
}

//

EMS_RESULT
CDBFPointingAngles::TestPhaseOutputPower( EMSTIME truetime, EMSDBFAZEL* aAzEls1, EMSDBFAZEL* aAzEls, ULONG* pulActual )
{
	EMS_RESULT hr = EMS_OK;

	if( !pulActual )
	{
		hr = EMS_INVALID_PTR;
	}


	if( EMS_OK == hr )
	{
		if ( *pulActual > 1 )
		{
			CEMSTime  oTime = truetime;
			EMSTIMEFIELDS tmFields;
			oTime.GetTime(&tmFields);

			double dTest;
			EMSCOMPLEX cTest;
			EMSVECTORD vSat1, vSat2;
			double dSA, dSAmin;
			EMSCOMPLEX cValue[DBF_MAX_CHANNELS];
			EMSCOMPLEX cValue1[DBF_MAX_CHANNELS];

			long lGainEL[10] = {0,10,20,30,40,50,60,70,80,90};
			double dGainDB[10] = {-6.0,-3.0,0.0,2.0,3.5,4.5,5.0,5.5,5.95,5.98};
			long lElInt = 0;

			FILE* m_lpNull = fopen("C:\\NullFile.csv","at");
	
			for ( int i = 0; i < *pulActual; i++ )
			{
				vSat1 = _Convert2UnitVector( aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );
				fprintf( m_lpNull,"\n0, %04d/%02d/%02d,%02d:%02d:%02d",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond );
				dSAmin = 1000.0;

				printf( "0, %04d/%02d/%02d,%02d:%02d:%02d",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond );

				fprintf(m_lpNull,", %3d, %3d, %7.2f, %7.2f", *pulActual, aAzEls[i].ulSatID, aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );
				printf(", %3d, %3d, %7.2f, %7.2f **", *pulActual, aAzEls[i].ulSatID,aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );
				
				for ( int j = 0; j < *pulActual; j++ )
				{
					emscbConj2 (aAzEls1[i].acmplxPhase, cValue, DBF_MAX_CHANNELS);
					emscbConj2 (aAzEls[j].acmplxPhase, cValue1, DBF_MAX_CHANNELS);
					cTest = emscDotProd( cValue, aAzEls[j].acmplxPhase, DBF_MAX_CHANNELS);
					cTest = emscDotProd( aAzEls1[i].acmplxPhase, aAzEls[j].acmplxPhase, DBF_MAX_CHANNELS);
					//cTest = emscDotProd( cValue, cValue1, DBF_MAX_CHANNELS);
					dTest = sqrt(cTest.re * cTest.re + cTest.im * cTest.im);

					if ( i == j )
					{
						dSA = 0.0;
					}
					else
					{
						vSat2 = _Convert2UnitVector( aAzEls[j].degPlateAzimuth, aAzEls[j].degPlateElevation );
						dSA = acos( vSat1.dX * vSat2.dX + vSat1.dY * vSat2.dY +vSat1.dZ * vSat2.dZ );
						dSA *= c_dRadToDeg;
						if ( dSA < dSAmin ) dSAmin = dSA;
					}
					//fprintf(m_lpNull,",  %8.4f",dTest );
	
					if (i==j)
					{
						lElInt = long(aAzEls[i].degPlateElevation/10.0);
						printf(",  %8.4f",log10(dTest)*20 + dGainDB[lElInt] );
					}
					else
						printf(",  %8.4f",dTest );

				}
				//fprintf(m_lpNull,", %8.2f", dSAmin );
				printf(",** %8.2f\n", dSAmin );

				fprintf(m_lpNull, "\n1, %04d/%02d/%02d,%02d:%02d:%02d",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond );
				fprintf(m_lpNull,", %3d, %7.2f, %7.2f", aAzEls1[i].ulSatID,aAzEls1[i].degPlateAzimuth, aAzEls1[i].degPlateElevation );
				for ( int j = 0; j < 32; j++ )
				{
					fprintf(m_lpNull,",  %9.5f, %9.5f",aAzEls1[i].acmplxPhase[j].re, aAzEls1[i].acmplxPhase[j].im );
				}
				
				fprintf(m_lpNull, "\n2, %04d/%02d/%02d,%02d:%02d:%02d",
				tmFields.nYear,
				tmFields.nMonth,
				tmFields.nDay,
				tmFields.nHour,
				tmFields.nMinute,
				tmFields.nSecond );
				fprintf(m_lpNull,", %3d, %7.2f, %7.2f", aAzEls[i].ulSatID,aAzEls[i].degPlateAzimuth, aAzEls[i].degPlateElevation );
				for ( int j = 0; j < 32; j++ )
				{
					fprintf(m_lpNull,", %9.5f, %9.5f",aAzEls[i].acmplxPhase[j].re, aAzEls[i].acmplxPhase[j].im );
				}

			}
			fflush( m_lpNull );
			fclose( m_lpNull );
			m_lpNull = NULL;
		}
	}
	return hr;
}

