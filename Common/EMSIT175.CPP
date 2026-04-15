/********************************************************************
*	Module:			emsit175.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit175
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

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5	rvw	start

********************************************************************/
#include <stdio.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit175.h"
#include "sitfield.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%03d/%05d/%02d");
const TCHAR c_szSitSolnHdrFmt[] = TEXT("/%04d/%04d/%05d/%02X/%c/%1d %1d %1d/%s");
const TCHAR c_szSitSolnLine1Fmt[] = TEXT("/%+08.4lf/%+09.4lf/%s/%1d/%04d/%1d/%+07.3lf");
const TCHAR c_szSitSolnLine2Fmt[] = TEXT("/%05.2lf/%05.2lf/%06.4lf/%s/%02.0lf/%1.0lf");
const TCHAR c_szSitSolnLine3Fmt[] = TEXT("/%s/%05.1lf %05.1lf");

CEMSSit175::CEMSSit175()
{
	SetSitNumber(175);
	SetMaxAlertCount( EMS_MAX_SIT175_ALERTS );
}

CEMSSit175::~CEMSSit175()
{
	Reset();
}

void CEMSSit175::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetSitNumber(175);
	SetAlertCount( 0 );
	SetMaxAlertCount( EMS_MAX_SIT175_ALERTS );
}

EMS_RESULT CEMSSit175::_GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide )
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
			wsprintf(szTCA,"%2.2d %3.3d %2.2d%2.2d %02d.%02d",
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
//						lpSide->dLatCorrCoeff,	//MF121
//						lpSide->dLongCorrCoeff,	//MF123
						0.0, 0.0, 
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
						msgField.TextMF13(	lpSide->dBias,	//MF13
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

EMS_RESULT CEMSSit175::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	char str;

	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr( i );

			if ( lpSoln )
			{
				TCHAR szBuffer[ 256 ], szBeaconMsg[36];

				for ( int j = 0; j < 15; j++ )
				{
					wsprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				switch ( lpSoln->hdr.msgType )
				{
					default:
					case EMSSMT_Normal:			str = 'N';	break;
					case EMSSMT_Test:				str = 'T';	break;
					case EMSSMT_Combination:	str = 'C';	break;
					case EMSSMT_Invalid:			str = 'X';	break;
				}

				wsprintf( szBuffer, c_szSitSolnHdrFmt, 
						lpSoln->hdr.nPrimaryLutID,
						lpSoln->hdr.nSecondaryLutID,
						lpSoln->hdr.ulPass,
						lpSoln->hdr.wDataTypes,
						str,
						lpSoln->hdr.nBitErrorsPreamble,
						lpSoln->hdr.nBitErrorsField1,
						lpSoln->hdr.nBitErrorsField2,
						szBeaconMsg );

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

EMS_RESULT CEMSSit175::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
	
		wsprintf( szBuffer, c_szSitHdrFmt, 
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

