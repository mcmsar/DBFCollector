/********************************************************************
*	Module:			EMSSIT157.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit157
*	
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include <stdio.h>
#include <tchar.h>
#include "emsit157.h"
#include "sitfield.h"

const TCHAR c_szSitAlertLine7Fmt[ ] = TEXT("/%+07.3lf/%+08.3lf/%s/%02.0lf/%01.0lf/%05.1lf %05.1lf");


CEMSSit157::CEMSSit157()
{
	SetMaxLinesPerRecord( EMS_MAX_LINES_PER_ABL_ALERT_SIT157 );

	SetSitNumber(157);
}

CEMSSit157::~CEMSSit157()
{
	Reset();
}

void 
CEMSSit157::Reset()
{
	CEMSSit152::Reset();

	SetSitNumber(157);
	SetMaxLinesPerRecord( EMS_MAX_LINES_PER_ABL_ALERT_SIT157 );
}


EMS_RESULT
CEMSSit157::_WriteABAlertData( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			hr = CEMSSit152::_WriteABAlertData( lpStream, lpSitABLData );

			if( EMS_OK == hr )
			{
				hr = _WriteABAlertDataLine7( lpStream, lpSitABLData );
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


EMS_RESULT
CEMSSit157::_WriteABAlertDataLine7( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		if( lpSitABLData )
		{
			TCHAR szBuffer[256];
			CEMSSitMsgField oMsgField;

			double dProb = lpSitABLData->dProbability * 100;

			if( dProb > 99.0 )
			{
				dProb = 99;
			}

			sprintf( szBuffer,	c_szSitAlertLine7Fmt,
						lpSitABLData->dLatitude,	//MF25
						lpSitABLData->dLongitude,   //MF26

						oMsgField.TextMF27( lpSitABLData->dHeading,	
									        lpSitABLData->dMajorError,
									        lpSitABLData->dMinorError ), 

						dProb,	//MF28
						lpSitABLData->dLQF,		//MF30
						lpSitABLData->dFOANoise,
						(lpSitABLData->dTOANoise * 1000)	//MF31
					);
			hr = WriteLine( lpStream, szBuffer );	
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


EMS_RESULT
CEMSSit157::_ParseABAlertData( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		hr = CEMSSit152::_ParseABAlertData( lpTokenizer, lpSitABLData );

		if( EMS_OK == hr )
		{
			hr = _ParseABAlertLine7( lpTokenizer, lpSitABLData );
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}



EMS_RESULT 
CEMSSit157::_ParseABAlertLine7( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData )
{
	EMS_RESULT   hr = EMS_OK;

	if( lpTokenizer && lpSitABLData )
	{
		EMSSITFIELD  sitField[ 16 ];
		int          iFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &iFldCount );

		if( EMS_OK == hr )
		{
			// should find /MF25/MF26/MF27/MF28/MF30/MF31 EOL

			CEMSSitMsgField oMsgField;

			if( iFldCount == 7 )
			{
				hr = oMsgField.GetMF25( sitField[0].szText, &(lpSitABLData->dLatitude) );

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMF26( sitField[1].szText, &(lpSitABLData->dLongitude) );
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMF27( sitField[2].szText, 
						                    &(lpSitABLData->dHeading),
											&(lpSitABLData->dMajorError),
											&(lpSitABLData->dMinorError) );
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMF28( sitField[3].szText, &(lpSitABLData->dProbability) );
					if( EMS_OK == hr )
					{
						lpSitABLData->dProbability /= 100.00;
					}
				}

				if( EMS_OK == hr )
				{
					hr = oMsgField.GetMF30( sitField[4].szText, &(lpSitABLData->dLQF) );
				}

				if( EMS_OK == hr )
				{
					double dTOANoise = 0.0;
					hr = oMsgField.GetMF31( sitField[5].szText, 
						                    &(lpSitABLData->dFOANoise),
											&dTOANoise );

					if( EMS_OK == hr )
					{
						lpSitABLData->dTOANoise = (dTOANoise / 1000.0);

						if( (EMS_OK == hr) && !oMsgField.IsEOL( sitField[6].szText ) )
						{
							hr = EMS_SIT_SYNTAX_EOL;
						}
					}
				}
			}
			else
			{
				hr = EMS_SIT_FIELD_COUNT_ERROR;
			}
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}
