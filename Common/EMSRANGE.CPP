/********************************************************************
*	Module:			emsrange.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSRangeRate
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	2001/11/14	rvw	start

********************************************************************/
#include <math.h>
#include <memory.h>

#include "emsvectr.h"
#include "emsrange.h"
#include "emscoord.h"


EMS_RESULT CEMSRangeRate::Calculate( EMSVECTOR vGLoc, EMSTIMECOORD *lpvCoord, ULONG ulCount, EMSRANGERATE *lpRangeRate )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpvCoord && ulCount && lpRangeRate )
	{
		EMSTIMECOORD vCoord;
		CEMSCoordSystem coordSys;

		for ( ULONG i = 0; ( i < ulCount ) && ( hr == EMS_OK ); i++ )
		{
			switch ( lpvCoord[i].coordSystem )
			{
				case COORDSYS_EarthFixed:
					memset( &vCoord, 0, sizeof( vCoord ) );

					vCoord.vTime = lpvCoord[i].vTime;

					vCoord.coord.radius = vGLoc;

					vCoord.coord.velocity = coordSys.EarthFixedVelocity( vGLoc );
					break;

				case COORDSYS_Inertial:
					vCoord = coordSys.EarthFixedToInertial( vGLoc, lpvCoord[i].vTime );
					break;

				default:
					hr = EMS_BAD_PARAM;
					break;
			}


			if ( hr == EMS_OK )
			{
				EMSVECTOR vDiffRadius, vDiffVelocity;

				vDiffRadius = CEMSVector::Sub( lpvCoord[i].coord.radius , vCoord.coord.radius );

				vDiffVelocity = CEMSVector::Sub( lpvCoord[i].coord.velocity , vCoord.coord.velocity );

				lpRangeRate[i].fRange = (float)sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );

				lpRangeRate[i].fRangeRate = (float)CEMSVector::DotProduct( vDiffRadius, vDiffVelocity ) /
														lpRangeRate[i].fRange;

				lpRangeRate[i].vTime = lpvCoord[i].vTime;
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;
	
	return hr;	
}

EMS_RESULT CEMSRangeRate::Calculate( EMSVECTORD vGLoc, EMSTIMECOORDD *lpvCoord, ULONG ulCount, EMSRANGERATED *lpRangeRate )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpvCoord && ulCount && lpRangeRate )
	{
		EMSTIMECOORDD vCoord;
		CEMSCoordSystem coordSys;

		for ( ULONG i = 0; ( i < ulCount ) && ( hr == EMS_OK ); i++ )
		{
			switch ( lpvCoord[i].coordSystem )
			{
				case COORDSYS_EarthFixed:
					memset( &vCoord, 0, sizeof( vCoord ) );

					vCoord.vTime = lpvCoord[i].vTime;

					vCoord.coord.radius = vGLoc;

					vCoord.coord.velocity = coordSys.EarthFixedVelocity( vGLoc );
					break;

				case COORDSYS_Inertial:
					vCoord = coordSys.EarthFixedToInertial( vGLoc, lpvCoord[i].vTime );
					break;

				default:
					hr = EMS_BAD_PARAM;
					break;
			}


			if ( hr == EMS_OK )
			{
				EMSVECTORD vDiffRadius, vDiffVelocity;

				vDiffRadius = CEMSVector::Sub( lpvCoord[i].coord.radius , vCoord.coord.radius );

				vDiffVelocity = CEMSVector::Sub( lpvCoord[i].coord.velocity , vCoord.coord.velocity );

				lpRangeRate[i].dRange = sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );

				lpRangeRate[i].dRangeRate = CEMSVector::DotProduct( vDiffRadius, vDiffVelocity ) /
														lpRangeRate[i].dRange;

				lpRangeRate[i].vTime = lpvCoord[i].vTime;
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;
	
	return hr;	
}

