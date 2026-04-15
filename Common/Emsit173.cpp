/********************************************************************
*	Module:			emsit173.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit173
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
#include "emsit173.h"
#include "sitfield.h"


const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%03d/%05d/%02d");
const TCHAR c_szSitSolnLine1Fmt[] = TEXT("/%04d/%05d/%s/%s/%04d");
const TCHAR c_szSitSolnLine2Fmt[] = TEXT("/%02X/%c/%1.1d %1.1d %1.1d/%+07.2lf");
const TCHAR c_szSitSolnLine3Fmt[] = TEXT("/%s");


CEMSSit173::CEMSSit173()
{
//	m_nAlerts = 0;
//	m_nSatID = 0;
//	m_nPass = 0;
//	memset( m_lpSoln, 0, sizeof( m_lpSoln ) );
	SetSitNumber(173);
	SetMaxAlertCount( EMS_MAX_SIT173_ALERTS );
}

CEMSSit173::~CEMSSit173()
{
	Reset();
}

void CEMSSit173::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount( 0 );
	SetSitNumber(173);
	SetMaxAlertCount( EMS_MAX_SIT173_ALERTS );
}

EMS_RESULT CEMSSit173::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	EMSTIMEFIELDS   timeFields;
	CEMSTime		tmpTime;
	TCHAR szTCA[40];
	TCHAR szBuffer[ 256 ], szBeaconMsg[36];
	ULONG ulYear;
//	double dBias= 0.0, dBSdev = 0.0, dDrift= 0.0;	//RVW
	WORD wNumPoints = 0;							// RVW

	char str;


	if ( lpStream )
	{
		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

			if ( lpSoln )
			{
				//Message
				for ( int j = 0; j < 15; j++ )
				{
					wsprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
				}

				
				//Beacon Type Normal or Test
				switch ( lpSoln->hdr.msgType )
				{
					default:
					case EMSSMT_Normal:			str = 'N';	break;
					case EMSSMT_Test:			str = 'T';	break;
					case EMSSMT_Combination:	str = 'C';	break;
					case EMSSMT_Invalid:			str = 'X';	break;
				}


		
				//TCA
				tmpTime.SetTime(lpSoln->sideA.timeTCA);
				tmpTime.GetTime(&timeFields);
				ulYear = timeFields.nYear - (timeFields.nYear/100)*100;
				wsprintf(szTCA,"%2.2d %3.3d %2.2d%2.2d %02d.%02d",
							ulYear,
							timeFields.nJulianDay,
							timeFields.nHour,
							timeFields.nMinute,
							timeFields.nSecond,
							timeFields.lNanosecond/100000000);
			
				CEMSSitMsgField msgField;

				//Line 1
				sprintf(szBuffer,
						c_szSitSolnLine1Fmt,
							lpSoln->hdr.nPrimaryLutID, //MF11
							GetPassID(),				//MF07
							msgField.TextMF13(	lpSoln->sideA.dBias,	//MF13
												lpSoln->sideA.dBSdev,
												lpSoln->sideA.dDrift ),
							szTCA,						//MF14
							lpSoln->sideA.nNumPoints );	//MF105


				hr = WriteLine( lpStream, szBuffer );

				//Line 2
				if ( hr == EMS_OK)
				{
					sprintf( szBuffer,
							c_szSitSolnLine2Fmt,
							lpSoln->hdr.wDataTypes,			//MF117
							str,							//MF119
							lpSoln->hdr.nBitErrorsPreamble,	//MF126
							lpSoln->hdr.nBitErrorsField1,
							lpSoln->hdr.nBitErrorsField2,
							lpSoln->hdr.dPower );
	
					hr = WriteLine( lpStream, szBuffer );
				}
				
				//Line 3
				if ( hr == EMS_OK )
				{
					sprintf( szBuffer, c_szSitSolnLine3Fmt, szBeaconMsg);
					hr = WriteLine( lpStream, szBuffer );

				}
			}
			else
			{
				hr = EMS_BAD_PARAM;
			}
		}									
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit173::GenerateSitHeader( IEMSSeqStream *lpStream)
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


