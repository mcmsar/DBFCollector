/********************************************************************
*	Module:			emsdoppl.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSDoppler
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
#include <stdio.h>	// DEBUG

#include "emsvectr.h"
#include "emsdoppl.h"
#include "emsconst.h"
#include "emsrange.h"
#include "emsearth.h"

// This presumes that the TIMECOORDs are in ascending time order
//
int CEMSDoppler::_FindClosestEntry( EMSTIMECOORD *lpvCoord, ULONG ulCount,EMSTIME timeAT, int nStartIdx )
{
	int nIndex = -1;

	if ( lpvCoord && ulCount && ( nStartIdx < (int)ulCount ) && ( nStartIdx >= 0 ) )
	{
		INT64 i64FirstDiff = timeAT.intTime - lpvCoord[nStartIdx].vTime.intTime;
		INT64 i64SecondDiff = 0;

		for ( int i = nStartIdx; ( i < (int)ulCount-1 ) && ( nIndex == -1 ); i++ )
		{
			i64SecondDiff = lpvCoord[i+1].vTime.intTime - timeAT.intTime;

			if (( i64FirstDiff >= 0 ) && ( i64SecondDiff >= 0 ) )
			{
				nIndex = ( i64FirstDiff > i64SecondDiff ) ? i+1 : i;
			}
			else
				i64FirstDiff = -i64SecondDiff;
		}
	}

	return nIndex;
}

EMS_RESULT CEMSDoppler::GenerateTemplates( EMSTIMECOORD *lpvCoord, 
			ULONG ulCount, LPEMSDOPPLERTEMPLATES lpTemplates, float fDeltaTime, 
			double dFreqScale )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpvCoord && ulCount && lpTemplates )
	{
		ULONG ulMidPoint = ulCount / 2;
		CEMSTime timeAt;
		EMSVECTOR vSatRadius= CEMSVector::Normalize( lpvCoord[ ulMidPoint].coord.radius );
		EMSVECTOR vSatVelocity = CEMSVector::Normalize( lpvCoord[ ulMidPoint].coord.velocity );
		EMSVECTOR vOrbitNormal = CEMSVector::CrossProduct( vSatRadius, vSatVelocity ); 
		EMSVECTOR vELT;
		float fCosCTA, fSinCTA, fCTA;
		EMSRANGERATE rangeRate;
		int nIdx=0;

		memset( lpTemplates, 0, sizeof( EMSDOPPLERTEMPLATES ) );

		lpTemplates->nCount = c_nMaxTemplates;

		lpTemplates->nLength = c_nTemplateLength;

		lpTemplates->fDeltaTime = fDeltaTime;

		for ( int i = 0; i < c_nMaxTemplates; i++ )
		{
			fCTA = (float)i* ((float)30.0 / (float)c_nMaxTemplates);	// TEMPORARY

			lpTemplates->fCTA[ i ] = fCTA;

			fCosCTA = (float)cos( c_dDegToRad * fCTA );

			fSinCTA = (float)sin( c_dDegToRad * fCTA );

			vELT = CEMSVector::Add( CEMSVector::Mult( vSatRadius, fCosCTA), CEMSVector::Mult( vOrbitNormal, fSinCTA ) );

			float fMag = (float)sqrt( CEMSVector::DotProduct( vELT , vELT ) );

			double dRadius = CEMSEarth::Radius( vELT );

			vELT = CEMSVector::Mult( vELT, (float)dRadius ); // scaled to Earth Fixed

			for ( int j = 0; ( hr == EMS_OK ) && ( j < c_nTemplateLength ); j++ )
			{
				hr = CEMSRangeRate::Calculate( vELT, &lpvCoord[j], 1, &rangeRate );

				if ( hr == EMS_OK )
				{
					lpTemplates->fDoppler[j][i] = (float)(( rangeRate.dRangeRate * dFreqScale );
				}
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSDoppler::XXGenerateTemplates( EMSTIMECOORD *lpvCoord, 
			ULONG ulCount, LPEMSDOPPLERTEMPLATES lpTemplates, float fDeltaTime, 
			double dFreqScale )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpvCoord && ulCount && lpTemplates )
	{
		ULONG ulMidPoint = ulCount / 2;
		EMSTIME timeCenter = lpvCoord[ ulMidPoint ].vTime;
		CEMSTime timeAt;
		EMSVECTOR vSatRadius= CEMSVector::Normalize( lpvCoord[ ulMidPoint].coord.radius );
		EMSVECTOR vSatVelocity = CEMSVector::Normalize( lpvCoord[ ulMidPoint].coord.velocity );
		EMSVECTOR vOrbitNormal = CEMSVector::CrossProduct( vSatRadius, vSatVelocity ); 
		EMSVECTOR vELT;
		float fCosCTA, fSinCTA, fCTA;

		EMSRANGERATE *lpRangeRate = new EMSRANGERATE[ c_nTemplateLength+1 ];

		if ( lpRangeRate ) 
		{
			EMSRANGERATE rangeRate;
			int nIdx=0;

			memset( lpTemplates, 0, sizeof( EMSDOPPLERTEMPLATES ) );

			lpTemplates->nCount = c_nMaxTemplates;

			lpTemplates->nLength = c_nTemplateLength;

			lpTemplates->fDeltaTime = fDeltaTime;

			for ( int i = 0; i < c_nMaxTemplates; i++ )
			{
				fCTA = (float)i* ((float)30.0 / (float)c_nMaxTemplates);	// TEMPORARY

				lpTemplates->fCTA[ i ] = fCTA;

				fCosCTA = (float)cos( c_dDegToRad * fCTA );

				fSinCTA = (float)sin( c_dDegToRad * fCTA );

				vELT = CEMSVector::Add( CEMSVector::Mult( vSatRadius, fCosCTA), CEMSVector::Mult( vOrbitNormal, fSinCTA ) );

				float fMag = (float)sqrt( CEMSVector::DotProduct( vELT , vELT ) );

				double dRadius = CEMSEarth::Radius( vELT );

				vELT = CEMSVector::Mult( vELT, (float)dRadius ); // scaled to Earth Fixed

//				vELT = CEMSVector::Mult( vELT, (float)c_dEarthKmRadius ); // scaled to Earth Fixed

				timeAt = timeCenter;

				timeAt.AddSeconds( -(float)( (float)c_nTemplateLength / 2.0 ) * fDeltaTime );

				nIdx = 0;

				for ( int j = 0; ( hr == EMS_OK ) && ( j < c_nTemplateLength ); j++ )
				{
					nIdx = _FindClosestEntry( lpvCoord, ulCount, timeAt, nIdx );

					if ( nIdx != -1 )
					{
						hr = CEMSRangeRate::Calculate( vELT, &lpvCoord[nIdx], 1, &rangeRate );

						if ( hr == EMS_OK )
						{
							lpRangeRate[j] = rangeRate;

							lpTemplates->fDoppler[j][i] = (float)(( rangeRate.dRangeRate * dFreqScale );
						}
					}
					else
						nIdx = 0;

					timeAt.AddSeconds( fDeltaTime );
				}
			}
			delete lpRangeRate;
			lpRangeRate = 0;
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSDoppler::GenerateTemplates( LPEMSORBIT lpOrbit, ULONG ulSatID,
					EMSTIME timeCenter, LPEMSDOPPLERTEMPLATES lpTemplates, 
					float fDeltaTime, double dFreqScale )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpOrbit && lpTemplates )
	{
		LPEMSTIMECOORD lpTimeCoord = new EMSTIMECOORD[ c_nTemplateLength ];

		if ( lpTimeCoord )
		{
			EMSTIME *lpTimeArray = new EMSTIME [ c_nTemplateLength ];

			if ( lpTimeArray )
			{
				ULONG ulRetrieved = 0;
				CEMSTime timeTemp( timeCenter );

				timeTemp.AddSeconds( -(float)( (float)c_nTemplateLength / 2.0 ) * fDeltaTime );

//				FILE *lpFile = fopen("D:\\richard.txt", "w+");
				FILE *lpFile = 0;

				if ( lpFile )
				{
					fprintf( lpFile, "timeCenter=%I64d\n", timeCenter.intTime );
				}

				for ( int i = 0; i < c_nTemplateLength; i++ )
				{
					lpTimeArray[i] = timeTemp;

					if ( lpFile )
					{
						fprintf( lpFile, "%d,%I64d\n", i, lpTimeArray[i].intTime );
					}

					timeTemp.AddSeconds( fDeltaTime );
				}

				if ( lpFile )
				{
					fclose( lpFile );
					lpFile = 0;
				}
				
				// retrieve the predicted position of the satellite at each of the times
				hr = lpOrbit->EarthFixedOrbit( ulSatID, lpTimeArray, 
								(ULONG)c_nTemplateLength, lpTimeCoord, &ulRetrieved );

				if ( hr == EMS_OK )
				{
					hr = GenerateTemplates( lpTimeCoord, (ULONG)c_nTemplateLength, 
													lpTemplates, fDeltaTime, dFreqScale );
				}

				delete [ ] lpTimeArray;
				lpTimeArray = 0;
			}
			else
				hr = EMS_NO_MEMORY;

			delete [ ] lpTimeCoord;
			lpTimeCoord = 0;
		}
		else
			hr = EMS_NO_MEMORY;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}



