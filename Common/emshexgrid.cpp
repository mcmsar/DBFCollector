/********************************************************************
*	Module:			emshexgrid.cpp
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

	0.0	2006/09/15		rcr		start

********************************************************************/
#include <math.h>
#include <memory.h>
#include "emsconst.h"
#include "emscoord.h"
#include "emshexgrid.h"
#include "emsvectr.h"
#include "EMSCONST.H"

CEMSHexGrid::CEMSHexGrid()
{

	m_Tcells = 0;
	m_Xcells = 0;
	m_Ycells = 0;
	memset( &m_GridArray, 0, sizeof(m_GridArray) );
	memset( &m_GridVector, 0, sizeof(m_GridVector) );
	memset( &m_GridLocation, 0, sizeof(m_GridLocation) );
	memset( m_RotationMatrix, 0, sizeof(m_RotationMatrix) );

}

CEMSHexGrid::~CEMSHexGrid()
{
}


EMS_RESULT CEMSHexGrid::RotateGrid( double dDegLatitude, double dDegLongitude)
{
	EMS_RESULT hr = EMS_OK;

	if ( m_Tcells )
	{
		CEMSCoordSystem COORD;

		double dRadLatitude  = dDegLatitude  * c_dDegToRad;
		double dRadLongitude = dDegLongitude * c_dDegToRad;

		m_RotationMatrix[0][0] =  cos( -dRadLatitude ) * cos( dRadLongitude );
		m_RotationMatrix[0][1] =  cos( -dRadLatitude ) * sin( dRadLongitude );
		m_RotationMatrix[0][2] = -sin( -dRadLatitude );

		m_RotationMatrix[1][0] = -sin( dRadLongitude );
		m_RotationMatrix[1][1] =  cos( dRadLongitude );
		m_RotationMatrix[1][2] =  0.0;

		m_RotationMatrix[2][0] =  sin( -dRadLatitude ) * cos( dRadLongitude );
		m_RotationMatrix[2][1] =  sin( -dRadLatitude ) * sin( dRadLongitude );
		m_RotationMatrix[2][2] =  cos( -dRadLatitude );

		for ( int i = 0; i < m_Tcells; i++ )
		{
			m_GridVector[i].dX  = m_RotationMatrix[0][0] * m_GridArray[i].dX;
			m_GridVector[i].dX += m_RotationMatrix[1][0] * m_GridArray[i].dY;
			m_GridVector[i].dX += m_RotationMatrix[2][0] * m_GridArray[i].dZ;

			m_GridVector[i].dY  = m_RotationMatrix[0][1] * m_GridArray[i].dX;
			m_GridVector[i].dY += m_RotationMatrix[1][1] * m_GridArray[i].dY;
			m_GridVector[i].dY += m_RotationMatrix[2][1] * m_GridArray[i].dZ;

			m_GridVector[i].dZ  = m_RotationMatrix[0][2] * m_GridArray[i].dX;
			m_GridVector[i].dZ += m_RotationMatrix[1][2] * m_GridArray[i].dY;
			m_GridVector[i].dZ += m_RotationMatrix[2][2] * m_GridArray[i].dZ;

			m_GridVector[i].dX *= c_dEarthKmRadius;
			m_GridVector[i].dY *= c_dEarthKmRadius;
			m_GridVector[i].dZ *= c_dEarthKmRadius;


			m_GridLocation[i] = COORD.ToGeodetic( m_GridVector[i] ); 

			if ( m_GridLocation[i].degLatitude < -90.0 )
			{
				m_GridLocation[i].degLatitude = -180.0 - m_GridLocation[i].degLatitude;
				m_GridLocation[i].degLongitude += 180.0;
			}
			if ( m_GridLocation[i].degLatitude > 90.0 )
			{
				m_GridLocation[i].degLatitude = 180.0 - m_GridLocation[i].degLatitude;
				m_GridLocation[i].degLongitude += 180.0;
			}
			if ( m_GridLocation[i].degLongitude < -360.0 )
				m_GridLocation[i].degLongitude += 360.0;;
			if ( m_GridLocation[i].degLongitude > 360.0 )
				m_GridLocation[i].degLongitude -= 360.0;;


		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSHexGrid::CalculateGrid( double dAngle, int nXcells, int nYcells )
{
	EMS_RESULT hr = EMS_OK;

	double dAngleRad, dMaxAngle, dAlpha, dBeta, dDist;
	int nMaxCells;

	m_Xcells = nXcells;
	m_Ycells = nYcells;

	// Convert angle from degrees to radians
	dAngleRad = dAngle * c_dDegToRad;

	if ( m_Xcells <= 0 )
		m_Xcells = (int) (sqrt( (double) c_nMaxCells) / 4) - 1;

	if ( m_Ycells <= 0 )
		m_Ycells = m_Xcells;
		
	nMaxCells = (2*m_Xcells+1) * (2*m_Ycells+1);

	while ( nMaxCells > c_nMaxCells )
	{
		m_Xcells--;
		m_Ycells--;
		nMaxCells = (2*m_Xcells+1) * (2*m_Ycells+1);
	}


	if ( nMaxCells <= c_nMaxCells )
	{

		dMaxAngle = dAngleRad * m_Xcells * sqrt(3.0)/2.0;

		m_Tcells = 0;

		for ( int i = -m_Xcells; i <= m_Xcells; i++ )
		{

			for ( int j = -m_Ycells; j <= m_Ycells; j++ )
			{

				dAlpha = i*dAngleRad;
				
				if ( j%2 )
					dAlpha += dAngleRad/2.0;
				
				dBeta = j*dAngleRad * sqrt( 3.0 )/2.0;

				dDist = sqrt( dAlpha * dAlpha + dBeta * dBeta );

				if ( (dDist <= dMaxAngle) && (m_Tcells < nMaxCells) )
				{
					m_GridArray[m_Tcells].dX = cos( dAlpha ) * cos ( dBeta );
					m_GridArray[m_Tcells].dY = sin( dAlpha ) * cos ( dBeta );
					m_GridArray[m_Tcells].dZ = sin( dBeta );
					m_Tcells++;
				}

			}
		}
      
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

int CEMSHexGrid::GetNearestNeighbours( int nIndex, int nNumber, double dAngle, int *pIndexArray )
{

	int nCount = 0;

	if ( m_Tcells && nNumber && pIndexArray && dAngle )
	{
		if ( (nIndex < m_Tcells) && (nNumber < m_Tcells-2) )
		{
			double	dAngleRad = dAngle * c_dDegToRad;

			double dX = m_GridArray[nIndex].dX;
			double dY = m_GridArray[nIndex].dY;
			double dZ = m_GridArray[nIndex].dZ;

			double dTest = 0.0;
			
			for ( int i = 0, j = 0; (i < m_Tcells) && (j < nNumber) ; i++ )
			{
				if ( i != nIndex )
				{
					dTest = dX*m_GridArray[i].dX + dY*m_GridArray[i].dY + dZ*m_GridArray[i].dZ;

					if ( dTest < dAngleRad )
					{
						pIndexArray[j++] = i;
						nCount = j;
					}
				}
			}

		}
	}

return nCount;
}

EMS_RESULT CEMSHexGrid::GenerateGrid( double dDegLatitude, double dDegLongitude, double dAngle, int nXCells, int nYCells )
{
	EMS_RESULT hr = EMS_OK;
	
	CEMSCoordSystem COORD;
	EMSLOCATION pGridLocation;
	EMSLOCATION pGridCentre;
	EMSVECTORD v1, v2;

	double dLat, dLong, dLat1, dLong1;
	double dAngularDistance = 0.0;
	double dMaxAngle = nXCells * dAngle;

	if ( dMaxAngle > 90.0 ) dMaxAngle = 90.0;

	pGridCentre.degLatitude  = dDegLatitude;
	pGridCentre.degLongitude = dDegLongitude;
	pGridCentre.fAltitude    = 0.0;
	v1 = COORD.ToEarthFixedDouble( pGridCentre );
	v1 = CEMSVector::Normalize( v1 );

	pGridLocation.degLatitude  = 0.0;
	pGridLocation.degLongitude = 0.0;
	pGridLocation.fAltitude    = 0.0;

	m_Xcells = nXCells;
	m_Ycells = nYCells;

	dLat1  = dAngle;
	dLong1 = dAngle;
	dLat   = 0.0;
	dLong  = 0.0;
	 
	m_Tcells = 0;

	for ( int i = -m_Xcells; i < m_Xcells; i++ )
	{
		dLat = dDegLatitude + i * dLat1;

		if ( abs(dLat) < 89.0 )
		{
			dLong1 = dAngle / cos( dLat* c_dDegToRad );

			for ( int j = -m_Ycells; j < m_Ycells; j++ )
			{
				dLong = j * dLong1;

				if ( fabs(dLong) < 180.0 )
				{
					dLong = dDegLongitude + j * dLong1;
					if (dLong > 180.0) dLong -= 360.0;
					if (dLong < -180.0) dLong += 360.0;

					pGridLocation.degLatitude  = dLat;
					pGridLocation.degLongitude = dLong;

					v2 = COORD.ToEarthFixedDouble( pGridLocation );
					v2 = CEMSVector::Normalize( v2 );

					dAngularDistance = acos(CEMSVector::DotProduct( v1, v2 )) * c_dRadToDeg;


					// Grid position must be less than the maximum angle from grid centre
					if ( ( dAngularDistance < dMaxAngle ) && (m_Tcells < c_nMaxCells) )
					{
						m_GridLocation[m_Tcells].degLatitude  = dLat;
						m_GridLocation[m_Tcells].degLongitude = dLong;
						m_Tcells++;
					}
				}
			}
		}

	}

	return hr;
}