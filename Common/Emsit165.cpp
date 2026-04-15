/********************************************************************
*	Module:			emsit165.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit165
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
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

#include <stdio.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit165.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%03d/%05d/%02d");
const TCHAR c_szSitSolnHdrFmt[] = TEXT("/%04d/%02X/%02d/%04d %02d/%s");
const TCHAR c_szSitSolnLine1Fmt[] = TEXT("/%+08.4lf/%+09.4lf/%s/%1d/%04d/%1d/%+07.3lf");
const TCHAR c_szSitSolnLine2Fmt[] = TEXT("/%05.2lf/%05.2lf/%06.4lf/%s/%02.0lf/%1.0lf");
const TCHAR c_szSitSolnLine3Fmt[] = TEXT("/%s/%05.1lf %05.1lf");

CEMSSit165::CEMSSit165()
{
	SetSitNumber(165);
	SetMaxAlertCount( EMS_MAX_SIT165_ALERTS );
}

CEMSSit165::~CEMSSit165()
{
	Reset();
}

void CEMSSit165::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount(0);
	SetSitNumber(165);
	SetMaxAlertCount( EMS_MAX_SIT165_ALERTS );
}

EMS_RESULT CEMSSit165::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
{
	EMS_RESULT hr = EMS_OK;
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR szTCA[40];
	TCHAR szBuffer[256];
	ULONG ulYear;

	if ( lpStream )
	{
		if ( lpSide )
		{
			CEMSSitMsgField msgField;

			tmpTime.SetTime(lpSide->timeTCA);
			tmpTime.GetTime(&timeFields);

			ulYear = timeFields.nYear - (timeFields.nYear/100)*100;
			sprintf(szTCA,"%2.2d %3.3d %2.2d%2.2d %02d.%02d",
						ulYear,
						timeFields.nJulianDay,
						timeFields.nHour,
						timeFields.nMinute,
						timeFields.nSecond,
						timeFields.lNanosecond/10000000);

			sprintf(szBuffer,
						c_szSitSolnLine1Fmt,
						lpSide->dLatitude,		//MF120
						lpSide->dLongitude,		//MF122
						szTCA,					//MF14
						lpSide->wWindowFactor,	//MF15
						lpSide->nNumPoints,		//MF105
						lpSide->wIterations,	//MF16
						lpSide->dCTA			//MF125
					);
			hr = WriteLine( lpStream, szBuffer );	

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSitSolnLine2Fmt,
						lpSide->dLatCorrCoeff,	//MF121
						lpSide->dLongCorrCoeff,	//MF123

						lpSide->dLatLongCorrCoeff,		//MF124

						msgField.TextMF27( lpSide->dErrEllipseAngle, //MF27
									lpSide->dErrEllipseMajAxis,	
									lpSide->dErrEllipseMinAxis ),

						lpSide->dProbability * 100,	//MF28
						lpSide->dConfidence		//MF30	  
						);
				hr = WriteLine( lpStream, szBuffer );	
			}

			if ( hr == EMS_OK )
			{
				sprintf(szBuffer,
						c_szSitSolnLine3Fmt,
						msgField.TextMF13(	lpSide->dBias,		//MF13
											lpSide->dBSdev,
											lpSide->dDrift ),
						lpSide->dDataResSdev,		//MF31
						lpSide->dDataResTrend
						);
				hr = WriteLine( lpStream, szBuffer );	
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}
	return hr;
}

EMS_RESULT CEMSSit165::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR str[8];
	TCHAR szBuffer[256];

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
//				switch ( lpSoln->hdr.nSolnType)
//				//{
//					case EMS_SOLUTION_UNKNOW:
//						strcpy(str,"UN");
//						break;
//					case EMS_SOLUTION_BEACON:
//						strcpy(str,"BE");
//						break;
//				case EMS_SOLUTION_INTERFERER:
//						strcpy(str,"IN");
//						break;
//				}

				switch ( lpSoln->hdr.solnType )
				{
					default:
					case EMSSST_Unknown:		lstrcpy( str, TEXT("UN") );	break;
					case EMSSST_Beacon:		lstrcpy( str, TEXT("BE") );	break;
					case EMSSST_Interferer:	lstrcpy( str, TEXT("IN") );	break;
				}

				switch ( lpSoln->hdr.msgType )
				{
					default:
					case EMSSMT_Normal:			break;
					case EMSSMT_Test:				break;
					case EMSSMT_Combination:	break;
					case EMSSMT_Invalid:			break;
				}
			
				sprintf( szBuffer, c_szSitSolnHdrFmt, 
						lpSoln->hdr.nPrimaryLutID,
						lpSoln->hdr.wDataTypes,
						lpSoln->hdr.nSideBands,
						lpSoln->hdr.nSweepPeriod,
						lpSoln->hdr.nSweepPeriodSdev,
						str
						 );

				hr = WriteLine( lpStream, szBuffer );

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideA );

				if ( hr == EMS_OK )
					hr = _GenerateSolnSide( lpStream, &lpSoln->sideB );
			}
			else
				hr = EMS_UNKNOWN_ERROR;
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit165::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		
		sprintf( szBuffer, c_szSitHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSatelliteID(),
						GetPassID(),
						GetAlertCount() );

		hr = WriteLine( lpStream, szBuffer );
		
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

