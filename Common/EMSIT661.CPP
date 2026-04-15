/********************************************************************
*	Module:			emsit661.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit661  Class
*						Pass Processing Summary
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

	0.0	2002 June 3 rvw	start

********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include <array.h>
#include "emspass.h"
#include "sitfield.h"
#include "emsit661.h"

#include "LogHelper.h"
#include "logmsgparam.h"
#include "sgenmsgs.h"
#include "convutility.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s");

const TCHAR c_szSitBodyLine1Fmt[ ] = TEXT("/%03lu/%05lu/%s/%s");

const TCHAR c_szSitBodyActualAosLosFmt[ ] = TEXT("/%s/%s");

const TCHAR c_szSitBodyLine2Fmt[ ] = 
					TEXT("/%04d/%04d/%03d/%s/%03d %04d/%05d/%04d/%04d");

const TCHAR c_szSitBodyLine3Fmt[ ] = TEXT("/%s");
const TCHAR c_szSitBodyLine3FmtB[ ] = TEXT("/%05lu/%s");

const TCHAR c_szSitBodyLine4Fmt[ ] = 
					TEXT("/%+010.4f %+010.4f %+010.4f/%+010.5f %+010.5f %+010.5f");

const TCHAR c_szSitBodyLine4FmtB[ ] = 
 			       TEXT("/%+011.4lf %+011.4lf %+011.4lf/%+010.6lf %+010.6lf %+010.6lf");


const TCHAR c_szSitBodyLine5Fmt[ ] = TEXT("/%s/%+010.4lf/%+010.4lf");

const TCHAR c_szSitBodyLine6Fmt[ ] = TEXT("/%s/%s/%+09.3f");
const TCHAR c_szSitBodyLine6FmtB[ ] = TEXT("/%s/%s/%+09.3f");

const TCHAR c_szSitBodyLine7Fmt[ ] = 
					TEXT("/%s/%03d/%03d/%03d/%03d/%03d/%03d/%02d/%02d");

const TCHAR c_szSitBodyLine7FmtB[ ] = 
					TEXT("/%s/%03d/%03d/%03d/%03d/%03d/%03d/%02d/%02d/%03d/%06.2lf");

const TCHAR c_szSitBodyStatsLineFmtB[ ] = TEXT("/%04X/%s/%s/%s");

const TCHAR c_szSitBodyLine8Fmt[ ] = TEXT("/%03lu/%05lu/%s/%s/%s");

const wchar_t* cwszSITMessage      = L"SIT661";
const wchar_t* cwszAlarmMessages   = L"MF#633";
const wchar_t* cwszWarningMessages = L"MF#634";


CEMSSit661A::CEMSSit661A()
{
	_Reset();
}

CEMSSit661A::~CEMSSit661A()
{
}

void CEMSSit661A::_Reset( void )
{
	SetSitNumber( 661 );
	SetSitCode( 0x661A );

	m_ulSatID = 0;
	m_ulOrbitNumber = 0;
	m_timeAOS.intTime = 0;
	m_timeLOS.intTime = 0;
	m_nSecsDuration = 0;
	m_nSecsCollecting = 0;
	m_nPercentageCollecting = 0;
	m_ulPassStatus = 0;
	m_nPDSRecoveryRate = 0;
	m_nFramesMissed = 0;
	m_nDistinctPDSCount = 0;
	m_nTotalPDSCount = 0;
	m_nSarrMessages = 0;
	m_timeOrbitEpoch.intTime = 0;

	memset( &m_vOrbitPosition, 0, sizeof( m_vOrbitPosition ) );

	memset( &m_vOrbitVelocity, 0, sizeof( m_vOrbitVelocity ) );

	m_orbitUpdateStatus = EMSSIT661OrbitUpdateUnknown;
	m_dOrbitPositionOffset = 0.0;
	m_dOrbitVelocityOffset = 0.0;
	m_timeRollover.intTime = 0;
	m_fUSOFreq = 0.0;
	m_fSARR406FreqOff = 0.0;
	m_timeSolnProcessing.intTime = 0;
	m_n121Transmitters = 0;
	m_n243Transmitters = 0;
	m_n406Interferers = 0;
	m_n406LocatedBeacons = 0;
	m_n406UnlocatedBeacons = 0;
	m_nUnlocatedAlerts = 0;
	m_nAlarmMessages = 0;
	m_nWarningMessages = 0;
	m_ulNextSatID = 0;
	m_ulNextOrbitNumber = 0;
	m_timeNextAOS.intTime = 0;
	m_timeNextLOS.intTime = 0;
	m_ulNextPassStatus = 0;
}

void CEMSSit661A::Reset( void )
{
	CEMSSitMessageBase::Reset();

	_Reset();
}

EMS_RESULT CEMSSit661A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR	szNextStatus[10];
	TCHAR	 str[10],  szProcStatus[10];

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ], szMF602[64], szMF603[64];
		CEMSSitMsgField msgField;

		lstrcpy( szMF602, msgField.TextMF602( m_timeAOS ) );

		lstrcpy( szMF603, msgField.TextMF603( m_timeLOS ) );

						//TEXT("/%03d/%05d/%s/%s");
		_stprintf( szBuffer, c_szSitBodyLine1Fmt,
							m_ulSatID,
							m_ulOrbitNumber,
							szMF602, szMF603
				);

		switch ( m_ulPassStatus & EMS_PASSFLAG_ORIGIN_MASK )	// origin
		{
			default:						lstrcpy(szProcStatus,TEXT(".")); break;
			case EMS_PASSFLAG_LUT:			lstrcpy(szProcStatus,TEXT("L")); break;
			case EMS_PASSFLAG_MCC:			lstrcpy(szProcStatus,TEXT("M")); break;
			case EMS_PASSFLAG_RCC:			lstrcpy(szProcStatus,TEXT("R")); break;
			case EMS_PASSFLAG_OPERATOR:		lstrcpy(szProcStatus,TEXT("O")); break;
		}

		switch ( m_ulPassStatus & EMS_PASSFLAG_STATUS_MASK )
		{
			default:						lstrcat(szProcStatus,TEXT("P")); break;
			case EMS_PASSFLAG_SUPPRESS: 	lstrcat(szProcStatus,TEXT("X")); break;
			case EMS_PASSFLAG_PROCESS:		lstrcat(szProcStatus,TEXT("F")); break;
			case EMS_PASSFLAG_REDUNDANT:	lstrcat(szProcStatus,TEXT("R")); break;
		}

		// Ensure that m_ulPassStatus has the correct result bits set.  The result is not stored in the database.
		// So, on retrieval of historical pass summary, we must determine whether it succeeded based on the 
		// number of warnings or alarms.
		if( m_nAlarmMessages > 0 || m_nWarningMessages > 0 )
		{
			// Set to error; unless already set to something else.
			if( EMS_PASSFLAG_ABORT != (m_ulPassStatus & EMS_PASSFLAG_RESULT_MASK) &&
				EMS_PASSFLAG_SUCCESS != (m_ulPassStatus & EMS_PASSFLAG_RESULT_MASK) )
			{
				m_ulPassStatus |= EMS_PASSFLAG_ERROR;
			}
		}
		else
		{
			// Set to success; unless already set to something else.
			if( EMS_PASSFLAG_ABORT != (m_ulPassStatus & EMS_PASSFLAG_RESULT_MASK) &&
				EMS_PASSFLAG_ERROR != (m_ulPassStatus & EMS_PASSFLAG_RESULT_MASK) )
			{
				m_ulPassStatus |= EMS_PASSFLAG_SUCCESS;
			}
		}

		switch ( m_ulPassStatus & EMS_PASSFLAG_RESULT_MASK )	
		{
			default:						lstrcat(szProcStatus,TEXT(".")); break;
			case EMS_PASSFLAG_SUCCESS:		lstrcat(szProcStatus,TEXT("S")); break;
			case EMS_PASSFLAG_ABORT:		lstrcat(szProcStatus,TEXT("A")); break;
			case EMS_PASSFLAG_ERROR:		lstrcat(szProcStatus,TEXT("X")); break;
		}					
		hr = WriteLine( lpStream, szBuffer );

		if ( hr == EMS_OK )	
		{
			int nPredictedDuration = m_nSecsDuration;
			int nActualDuration = m_nSecsCollecting;
			int nPDSRecoveryRate = m_nPDSRecoveryRate;

			if ( nPredictedDuration < 0 )
				nPredictedDuration = 0;

			if ( nPredictedDuration > 9999 )
				nPredictedDuration = 9999;

			if ( nActualDuration < 0 )
				nActualDuration = 0;

			if ( nActualDuration > 9999 )
				nActualDuration = 9999;

			if ( nPDSRecoveryRate > 999 )
				nPDSRecoveryRate = 999;
			else if ( nPDSRecoveryRate < 0 )
				nPDSRecoveryRate = 0;

			_stprintf( szBuffer, c_szSitBodyLine2Fmt,
								nPredictedDuration,
								nActualDuration,
								m_nPercentageCollecting,
								szProcStatus,
								//m_nPDSRecoveryRate,
								nPDSRecoveryRate,	// 0 <= rate <= 999
								m_nFramesMissed,
								m_nTotalPDSCount,
								m_nDistinctPDSCount,
								m_nSarrMessages
					);
			hr = WriteLine( lpStream, szBuffer );

		}

		if ( hr == EMS_OK )	
		{
			_stprintf( szBuffer, c_szSitBodyLine3Fmt, 
								msgField.TextMF34( m_timeOrbitEpoch ) );

			hr = WriteLine( lpStream, szBuffer );
		}

		if ( hr == EMS_OK )	
		{
			_stprintf( szBuffer, c_szSitBodyLine4Fmt,
								m_vOrbitPosition.fX,
								m_vOrbitPosition.fY,
								m_vOrbitPosition.fZ,
								m_vOrbitVelocity.fX,
								m_vOrbitVelocity.fY,
								m_vOrbitVelocity.fZ
							
					);
			hr = WriteLine( lpStream, szBuffer );

		}

		if ( hr == EMS_OK )	
		{
			switch ( m_orbitUpdateStatus )
			{
				case EMSSIT661OrbitUpdateInSpec: 
					lstrcpy(str, TEXT("IN"));
					break;

				default:
				case EMSSIT661OrbitUpdateOutSpec: 
					lstrcpy(str, TEXT("OU"));
					break;

				case EMSSIT661OrbitUpdatePredict:
					lstrcpy(str, TEXT("PR"));
					break;
			}

			_stprintf( szBuffer, c_szSitBodyLine5Fmt,
								str,
								m_dOrbitPositionOffset,
								m_dOrbitVelocityOffset
					);
			hr = WriteLine( lpStream, szBuffer );

		}
		
		if ( hr == EMS_OK )	
		{
			_stprintf( szBuffer, c_szSitBodyLine6Fmt,
								msgField.TextMF37( m_timeRollover ),
//								m_fUSOFreq,
								msgField.TextMF38( m_fUSOFreq ),
								m_fSARR406FreqOff
					);
			hr = WriteLine( lpStream, szBuffer );

		}
		
		if ( hr == EMS_OK )	
		{
	
            // /MF609/MF08B/MF08C/MF08D/MF08E/MF10B/MF10C/MF633/MF634

			int iMF633 = _ChkMessageCountRange( m_nAlarmMessages, cwszAlarmMessages );
			int iMF634 = _ChkMessageCountRange( m_nWarningMessages, cwszWarningMessages );

			_stprintf( szBuffer, c_szSitBodyLine7Fmt,
								msgField.TextMF609( m_timeSolnProcessing ),
								m_n121Transmitters,
								m_n243Transmitters,
								m_n406Interferers,
								m_n406LocatedBeacons,
								m_n406UnlocatedBeacons,
								m_nUnlocatedAlerts,
								iMF633,							//MF #633 
								iMF634							//MF #634 
					);

			hr = WriteLine( lpStream, szBuffer );

		}

		if ( hr == EMS_OK )	
		{
			switch ( m_ulNextPassStatus & EMS_PASSFLAG_ORIGIN_MASK )	// origin
			{
				default:						lstrcpy(szNextStatus,TEXT(".")); break;
				case EMS_PASSFLAG_LUT:			lstrcpy(szNextStatus,TEXT("L")); break;
				case EMS_PASSFLAG_MCC:			lstrcpy(szNextStatus,TEXT("M")); break;
				case EMS_PASSFLAG_RCC:			lstrcpy(szNextStatus,TEXT("R")); break;
				case EMS_PASSFLAG_OPERATOR:		lstrcpy(szNextStatus,TEXT("O")); break;
			}

			switch ( m_ulNextPassStatus & EMS_PASSFLAG_STATUS_MASK )
			{
				default:						lstrcat(szNextStatus,TEXT("P")); break;
				case EMS_PASSFLAG_SUPPRESS: 	lstrcat(szNextStatus,TEXT("X")); break;
				case EMS_PASSFLAG_PROCESS:		lstrcat(szNextStatus,TEXT("F")); break;
				case EMS_PASSFLAG_REDUNDANT:	lstrcat(szNextStatus,TEXT("R")); break;
			}

			switch ( m_ulNextPassStatus & EMS_PASSFLAG_RESULT_MASK )	
			{
				default:						lstrcat(szNextStatus,TEXT(".")); break;
				case EMS_PASSFLAG_SUCCESS:		lstrcat(szNextStatus,TEXT("S")); break;
				case EMS_PASSFLAG_ABORT:		lstrcat(szNextStatus,TEXT("A")); break;
				case EMS_PASSFLAG_ERROR:		lstrcat(szNextStatus,TEXT("X")); break;
			}

			lstrcpy( szMF602, msgField.TextMF602( m_timeNextAOS ) );

			lstrcpy( szMF603, msgField.TextMF603( m_timeNextLOS ) );

			_stprintf( szBuffer, c_szSitBodyLine8Fmt,
								m_ulNextSatID,
								m_ulNextOrbitNumber,
								szMF602, szMF603,
								szNextStatus
					);

			hr = WriteLine( lpStream, szBuffer );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit661A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;
	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		
		_stprintf( szBuffer, c_szSitHdrFmt, 
							GetSitNumber(), 
							GetSitDestination(),
							GetSitCodeStr()
				);

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT
CEMSSit661A::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
   EMS_RESULT hr = ParseSitHeader( lpTokenizer );

   if ( EMS_OK == hr )
   {
      // /MF06/MF07/MF602/MF603
      hr = _ParsePassIDLine( lpTokenizer );

      if ( EMS_OK == hr )
      {
         // /MF602A/MF603A
         hr = _ParseActualAOSLOSLine( lpTokenizer );
      }

      if ( EMS_OK == hr )
      {
         // /MF604/MF629/MF630/MF610/MF637/MF 638/MF 639/MF636
         hr = _ParsePassSummaryLine1( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // [/07B]/MF34
         hr = _ParsePassSummaryLine2( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF35/MF36
         hr = _ParsePassSummaryLine3( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF611/MF607/MF608
         hr = _ParsePassSummaryLine4( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF37/MF38/MF64
         hr = _ParsePassSummaryLine5( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF609/MF08B/MF08C/MF08D/MF08E/MF10B/MF10C/MF633/MF634[/MF08F/MF669]
         hr = _ParsePassSummaryLine6( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF665/MF666/MF667/MF668
         hr = _ParsePassSummaryStatsLine( lpTokenizer );
      }
      if ( EMS_OK == hr )
      {
         // /MF06A/MF07A/MF602/MF603/MF610
         hr = _ParsePassSummaryLine7( lpTokenizer );
      }
   }
   return hr;
}

EMS_RESULT
CEMSSit661A::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
   EMS_RESULT  hr = EMS_OK;
   EMSSITFIELD sitField[ 16 ];
   int         nFldCount = 0;

   hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

   if ( hr == EMS_OK )
   {
      CEMSSitMsgField msgField;

      // /MF04/MF05/MF04A + eol

      if ( 4 == nFldCount )
      {
         int nNumber = 0;
         EMSSITCODE sitCode;

         // MF04 SIT number
         hr = msgField.GetMF4( sitField[0].szText, &nNumber );

         if ( hr == EMS_OK )
         {
            SetSitNumber( nNumber );

            // MF05 Destination
            hr = msgField.GetMF5( sitField[1].szText, &nNumber );
         }
         if ( hr == EMS_OK )
         {
            SetSitDestination( nNumber );

            // MF04A Internal SIT number (aka SIT code)
            hr = msgField.GetMF4A( sitField[2].szText, &sitCode );
         }

         if ( hr == EMS_OK )
         {
            SetSitCode( sitCode );

            if ( !msgField.IsEOL( sitField[3].szText ) )
            {
               hr = EMS_SIT_SYNTAX_EOL;
            }
         }
      }
      else
      {
         hr = EMS_SIT_FIELD_COUNT_ERROR;
      }

      if ( bPeek )
      {
         UnReadSitLine( lpTokenizer, sitField, nFldCount );
      }
   }
   else 
      hr = EMS_BAD_PARAM;

   return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassIDLine( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF06/MF07/MF602/MF603 + eol

		if ( 5 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF6( sitField[0].szText, reinterpret_cast<int*>(&m_ulSatID) );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF7( sitField[1].szText, reinterpret_cast<int*>(&m_ulOrbitNumber) );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF602( sitField[2].szText, &m_timeAOS );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF603( sitField[3].szText, &m_timeLOS );
         }
      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[4].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine1( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF604/MF629/MF630/MF610/MF637/MF638/MF639/MF636 + eol

		if ( 9 == nFldCount )
		{
			CEMSSitMsgField   msgField;
			EMSSITMF610       mf610;

			hr = msgField.GetMF604( sitField[0].szText, &m_nSecsDuration );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF629( sitField[1].szText, &m_nSecsCollecting );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF630( sitField[2].szText, &m_nPercentageCollecting );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF610( sitField[3].szText, &mf610 );
         }
      	if ( EMS_OK == hr )
         {
            m_ulPassStatus = 0;

            // Origin
            switch ( toupper( mf610.cValue[0] ) )
            {
            case _T('L'):  m_ulPassStatus = EMS_PASSFLAG_LUT;        break;
            case _T('M'):  m_ulPassStatus = EMS_PASSFLAG_MCC;        break;
            case _T('R'):  m_ulPassStatus = EMS_PASSFLAG_RCC;        break;
            case _T('O'):  m_ulPassStatus = EMS_PASSFLAG_OPERATOR;   break;
            case _T('V'):
            default:       break;
            }

            // Schedule status
            switch ( toupper( mf610.cValue[1] ) )
            {
            case _T('P'):
            case _T('F'):  m_ulPassStatus |= EMS_PASSFLAG_PROCESS;   break;

            case _T('R'):  m_ulPassStatus |= EMS_PASSFLAG_REDUNDANT; break;

            case _T('S'):
            case _T('X'):
            case _T('N'):
            case _T('O'):
            case _T('A'):  m_ulPassStatus |= EMS_PASSFLAG_SUPPRESS;  break;
            default:       m_ulPassStatus |= EMS_PASSFLAG_PROCESS;   break;
            }

            // Processing status
            switch ( toupper( mf610.cValue[2] ) )
            {
            case _T('.'):  break;
            case _T('S'):  m_ulPassStatus |= EMS_PASSFLAG_SUCCESS;   break;
            case _T('A'):  m_ulPassStatus |= EMS_PASSFLAG_ABORT;     break;
            case _T('X'):  m_ulPassStatus |= EMS_PASSFLAG_ERROR;     break;
            default:       break;
            }

			   hr = msgField.GetMF637( sitField[4].szText, &m_nPDSRecoveryRate, &m_nFramesMissed );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF638( sitField[5].szText, &m_nTotalPDSCount );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF639( sitField[6].szText, &m_nDistinctPDSCount );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF636( sitField[7].szText, &m_nSarrMessages );
         }
      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[8].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine2( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF34 + eol

		if ( 2 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF34( sitField[0].szText, &m_timeOrbitEpoch );

      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[1].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine3( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF35/MF36 + eol

		if ( 3 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF35( sitField[0].szText, &m_vOrbitPosition );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF36( sitField[1].szText, &m_vOrbitVelocity );
         }
      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[2].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine4( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF611/MF607/MF608 + eol

		if ( 4 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF611( sitField[0].szText, reinterpret_cast<int*>(&m_orbitUpdateStatus) );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF607( sitField[1].szText, &m_dOrbitPositionOffset );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF608( sitField[2].szText, &m_dOrbitVelocityOffset );
         }
      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[3].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine5( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF37/MF38/MF64 + eol

		if ( 4 == nFldCount )
		{
			CEMSSitMsgField   msgField;
         double            dNumber = 0;

			hr = msgField.GetMF37( sitField[0].szText, &m_timeRollover );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF38( sitField[1].szText, &dNumber );
         }
      	if ( EMS_OK == hr )
         {
            m_fUSOFreq = static_cast<float>(dNumber);

			   hr = msgField.GetMF64( sitField[2].szText, &dNumber );
         }
      	if ( EMS_OK == hr )
         {
            m_fSARR406FreqOff = static_cast<float>(dNumber);

			   if ( !msgField.IsEOL( sitField[3].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine6( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF609/MF08B/MF08C/MF08D/MF08E/MF10B/MF10C/MF633/MF634 + eol

		if ( 10 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF609( sitField[0].szText, &m_timeSolnProcessing );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF8B( sitField[1].szText, &m_n121Transmitters );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF8C( sitField[2].szText, &m_n243Transmitters );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF8D( sitField[3].szText, &m_n406Interferers );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF8E( sitField[4].szText, &m_n406LocatedBeacons );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF10B( sitField[5].szText, &m_n406UnlocatedBeacons );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF10C( sitField[6].szText, &m_nUnlocatedAlerts );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF633( sitField[7].szText, &m_nAlarmMessages );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF634( sitField[8].szText, &m_nWarningMessages );
         }
      	if ( EMS_OK == hr )
         {
			   if ( !msgField.IsEOL( sitField[9].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

EMS_RESULT
CEMSSit661A::_ParsePassSummaryLine7( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF06A/MF07A/MF602/MF603/MF610 + eol

		if ( 6 == nFldCount )
		{
			CEMSSitMsgField   msgField;
			EMSSITMF610       mf610;

			hr = msgField.GetMF6A( sitField[0].szText, reinterpret_cast<int*>(&m_ulNextSatID) );

      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF7A( sitField[1].szText, reinterpret_cast<int*>(&m_ulNextOrbitNumber) );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF602( sitField[2].szText, &m_timeNextAOS );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF603( sitField[3].szText, &m_timeNextLOS );
         }
      	if ( EMS_OK == hr )
         {
			   hr = msgField.GetMF610( sitField[4].szText, &mf610 );
         }
      	if ( EMS_OK == hr )
         {
            m_ulNextPassStatus = 0;

            // Origin
            switch ( toupper( mf610.cValue[0] ) )
            {
            case _T('L'):  m_ulNextPassStatus = EMS_PASSFLAG_LUT;       break;
            case _T('M'):  m_ulNextPassStatus = EMS_PASSFLAG_MCC;       break;
            case _T('R'):  m_ulNextPassStatus = EMS_PASSFLAG_RCC;       break;
            case _T('O'):  m_ulNextPassStatus = EMS_PASSFLAG_OPERATOR;  break;
            case _T('V'):
            default:       break;
            }

            // Schedule status
            switch ( toupper( mf610.cValue[1] ) )
            {
            case _T('P'):
            case _T('F'):  m_ulNextPassStatus |= EMS_PASSFLAG_PROCESS;     break;

            case _T('R'):  m_ulNextPassStatus |= EMS_PASSFLAG_REDUNDANT;   break;

            case _T('S'):
            case _T('X'):
            case _T('N'):
            case _T('O'):
            case _T('A'):  m_ulNextPassStatus |= EMS_PASSFLAG_SUPPRESS;    break;
            default:       m_ulNextPassStatus |= EMS_PASSFLAG_PROCESS;     break;
            }

            // Processing status
            switch ( toupper( mf610.cValue[2] ) )
            {
            case _T('.'):  break;
            case _T('S'):  m_ulNextPassStatus |= EMS_PASSFLAG_SUCCESS;  break;
            case _T('A'):  m_ulNextPassStatus |= EMS_PASSFLAG_ABORT;    break;
            case _T('X'):  m_ulNextPassStatus |= EMS_PASSFLAG_ERROR;    break;
            default:       break;
            }

			   if ( !msgField.IsEOL( sitField[5].szText ) )
            {
				   hr = EMS_SIT_SYNTAX_EOL;
            }
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
   {
		hr = EMS_BAD_PARAM;
   }
	return hr;
}

int 
CEMSSit661A::_ChkMessageCountRange( const int iCount, const wchar_t* cwszText )
{
	int iRet = iCount;

	if(( iCount < 0 ) || ( iCount > 99 ))
	{
		if( iCount > 99 ) iRet = 99;
		else if ( iCount < 0 )	iRet = 0;

		CEMSLogMsgParam param(4);
		param.AddString( cwszSITMessage );
		param.AddString( cwszText );
		param.Add( iCount );
		param.Add( iRet );
		CEMSLogHelper::LogInfoMsg( EMS_SITGEN_MF_RANGE_EXCEEDED, param );
	}
	return iRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

CEMSSit661B::CEMSSit661B()
{
	_Reset();
}

CEMSSit661B::~CEMSSit661B()
{
}

void 
CEMSSit661B::Reset( void )
{
	CEMSSit661A::Reset();

	_Reset();
}

void 
CEMSSit661B::_Reset( void )
{
	SetSitNumber( 661 );
	SetSitCode( 0x661B );

	m_ulEpochOrbNum = 0;
	m_dUSOFreq = 0.0;
	m_dMedianLocAccuracy = 0.0;
	m_iMedianLocAccSampleSize = 0;
	m_wGeneralStatus = 0;
	m_tmActualAOS.intTime = 0;
	m_tmActualLOS.intTime = 0;
	m_tmLastClockSync.intTime = 0;
	m_tmEarliestSARP.intTime = 0;
	m_tmLastSARP.intTime = 0;
}

EMS_RESULT
CEMSSit661B::_ParseActualAOSLOSLine( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF602A/MF603A + eol

		if( 3 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF602A( sitField[0].szText, &m_tmActualAOS );

			if( EMS_OK == hr )
			{
				hr = msgField.GetMF603A( sitField[1].szText, &m_tmActualLOS );
			}

			if( EMS_OK == hr )
			{
				if( !msgField.IsEOL( sitField[2].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit661B::_ParsePassSummaryLine2( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		EMSTIME		tmEpochTime;

		tmEpochTime.intTime = 0;

		// should find /07B/MF34 + eol
		if( 3 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF7B( sitField[0].szText, reinterpret_cast<int*>(&m_ulEpochOrbNum) );
			
			if( EMS_OK == hr )
			{
				hr = msgField.GetMF34( sitField[1].szText, &tmEpochTime );
			}

			if( EMS_OK == hr )
			{
				SetOrbitEpoch( tmEpochTime );

				if( !msgField.IsEOL( sitField[2].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit661B::_ParsePassSummaryLine3( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if( EMS_OK == hr )
	{
		// should find /MF35A/MF36A + eol

		if( 3 == nFldCount )
		{
			CEMSSitMsgField   msgField;
			EMSVECTOR		  vOrbPos;
			EMSVECTOR		  vOrbVel;

			hr = msgField.GetMF35A( sitField[0].szText, &vOrbPos );

			if( EMS_OK == hr )
			{
				SetOrbitPosition( vOrbPos );
				hr = msgField.GetMF36A( sitField[1].szText, &vOrbVel );
			}
			
			if( EMS_OK == hr )
			{
				SetOrbitVelocity( vOrbVel );
				if( !msgField.IsEOL( sitField[2].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit661B::_ParsePassSummaryLine5( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if( EMS_OK == hr )
	{
		// should find /MF37/MF38A/MF64 + eol

		if( 4 == nFldCount )
		{
			CEMSSitMsgField   msgField;
			double            dNumber = 0;
			EMSTIME			  tmRollover;

			hr = msgField.GetMF37( sitField[0].szText, &tmRollover );

			if( EMS_OK == hr )
			{
				SetRolloverTime( tmRollover );
				hr = msgField.GetMF38A( sitField[1].szText, &m_dUSOFreq );
			}

			if( EMS_OK == hr )
			{
				SetUSOFreq( static_cast<float>(m_dUSOFreq) );

				hr = msgField.GetMF64( sitField[2].szText, &dNumber );
			}

			if( EMS_OK == hr )
			{
				SetSarr406FreqOffset( static_cast<float>(dNumber) );

				if( !msgField.IsEOL( sitField[3].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT
CEMSSit661B::_ParsePassSummaryLine6( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if ( EMS_OK == hr )
	{
		// should find /MF609/MF08B/MF08C/MF08D/MF08E/MF10B/MF10C/MF633/MF634/MF08F/MF669 + eol

		if( 12 == nFldCount )
		{
			CEMSSitMsgField   msgField;
			EMSTIME           tmSonProc;
			int               iNumber = 0;

			tmSonProc.intTime = 0;

			hr = msgField.GetMF609( sitField[0].szText, &tmSonProc );

			if( EMS_OK == hr )
			{
				SetSolnProcessingTime( tmSonProc );
				hr = msgField.GetMF8B( sitField[1].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				Set121Transmitters( iNumber );
				hr = msgField.GetMF8C( sitField[2].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				Set243Transmitters( iNumber );
				hr = msgField.GetMF8D( sitField[3].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				Set406Interferers( iNumber );
				hr = msgField.GetMF8E( sitField[4].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				Set406LocatedBeacons( iNumber );
				hr = msgField.GetMF10B( sitField[5].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				Set406UnlocatedBeacons( iNumber );
				hr = msgField.GetMF10C( sitField[6].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				SetUnlocatedAlerts( iNumber );
				hr = msgField.GetMF633( sitField[7].szText, &iNumber );
			}

			if( EMS_OK == hr )
			{
				SetAlarmMessages( iNumber );
				hr = msgField.GetMF634( sitField[8].szText, &iNumber );
			}
			
			if( EMS_OK == hr )
			{
				SetWarningMessages( iNumber );
				hr = msgField.GetMF8F( sitField[9].szText, &m_iMedianLocAccSampleSize );
			}
			
			if( EMS_OK == hr )
			{
				hr = msgField.GetMF669( sitField[10].szText, &m_dMedianLocAccuracy );
			}
			
			if ( EMS_OK == hr )
			{
				if( !msgField.IsEOL( sitField[11].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
      }
		else
      {
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_ParsePassSummaryStatsLine( CEMSSitTokenizer* lpTokenizer )
{
	EMS_RESULT hr = EMS_OK;

	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0;

	hr = ReadSitLine( lpTokenizer, sitField, ARRAY_SIZE(sitField), &nFldCount );

	if( EMS_OK == hr )
	{
		// should find /MF665/MF666/MF667/MF668 + eol

		if( 5 == nFldCount )
		{
			CEMSSitMsgField   msgField;

			hr = msgField.GetMF665( sitField[0].szText, &m_wGeneralStatus );

			if( EMS_OK == hr )
			{
				hr = msgField.GetMF666( sitField[1].szText, &m_tmLastClockSync );
			}

			if( EMS_OK == hr )
			{
				hr = msgField.GetMF667( sitField[2].szText, &m_tmEarliestSARP );
			}

			if( EMS_OK == hr )
			{
				hr = msgField.GetMF668( sitField[3].szText, &m_tmLastSARP );
			}

			if( EMS_OK == hr )
			{
				if( !msgField.IsEOL( sitField[4].szText ) )
				{
					hr = EMS_SIT_SYNTAX_EOL;
				}
			}
		}
		else
		{
			hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

EMS_RESULT CEMSSit661B::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		hr = _WritePassIDLine( lpStream );

		if( EMS_OK == hr )
		{
			hr = _WriteActualAOSLOSLine( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine1( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine2( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine3( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine4( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine5( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr =  _WritePassSummaryLine6( lpStream );
		}

		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryStatsLine( lpStream );
		}
		
		if( EMS_OK == hr )
		{
			hr = _WritePassSummaryLine7( lpStream );
		}
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}

EMS_RESULT 
CEMSSit661B::_WritePassIDLine( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		TCHAR           szBuffer[ 256 ];
		TCHAR           szMF602[64];
		TCHAR           szMF603[64];

		lstrcpy( szMF602, msgField.TextMF602( GetAOSTime() ) );

		lstrcpy( szMF603, msgField.TextMF603( GetLOSTime() ) );

		//TEXT("/%03d/%05d/%s/%s");
		_stprintf( szBuffer, c_szSitBodyLine1Fmt, GetSatelliteID(),
			                  GetOrbitNumber(), szMF602, szMF603 );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WriteActualAOSLOSLine( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		TCHAR           szBuffer[ 256 ];
		TCHAR           szMF602A[64];
		TCHAR           szMF603A[64];

		lstrcpy( szMF602A, msgField.TextMF602A( m_tmActualAOS ) );

		lstrcpy( szMF603A, msgField.TextMF603A( m_tmActualLOS ) );

		//TEXT("/%s/%s");
		_stprintf( szBuffer, c_szSitBodyActualAosLosFmt, szMF602A, szMF603A );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine1( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];
		TCHAR           szProcStatus[10];
		ULONG           ulPassStatus = GetPassStatus();

		switch ( ulPassStatus & EMS_PASSFLAG_ORIGIN_MASK )	// origin
		{
			default:						lstrcpy(szProcStatus,TEXT(".")); break;
			case EMS_PASSFLAG_LUT:			lstrcpy(szProcStatus,TEXT("L")); break;
			case EMS_PASSFLAG_MCC:			lstrcpy(szProcStatus,TEXT("M")); break;
			case EMS_PASSFLAG_RCC:			lstrcpy(szProcStatus,TEXT("R")); break;
			case EMS_PASSFLAG_OPERATOR:		lstrcpy(szProcStatus,TEXT("O")); break;
		}

		switch ( ulPassStatus & EMS_PASSFLAG_STATUS_MASK )
		{
			default:						lstrcat(szProcStatus,TEXT("P")); break;
			case EMS_PASSFLAG_SUPPRESS: 	lstrcat(szProcStatus,TEXT("X")); break;
			case EMS_PASSFLAG_PROCESS:		lstrcat(szProcStatus,TEXT("F")); break;
			case EMS_PASSFLAG_REDUNDANT:	lstrcat(szProcStatus,TEXT("R")); break;
		}

		// Ensure that ulPassStatus has the correct result bits set.  The result is not stored in the database.
		// So, on retrieval of historical pass summary, we must determine whether it succeeded based on the 
		// number of warnings or alarms.
		if( GetAlarmMessages() > 0 || GetWarningMessages() > 0 )
		{
			// Set to error; unless already set to something else.
			if( EMS_PASSFLAG_ABORT != (ulPassStatus & EMS_PASSFLAG_RESULT_MASK) &&
				EMS_PASSFLAG_SUCCESS != (ulPassStatus & EMS_PASSFLAG_RESULT_MASK) )
			{
				ulPassStatus |= EMS_PASSFLAG_ERROR;
			}
		}
		else
		{
			// Set to success; unless already set to something else.
			if( EMS_PASSFLAG_ABORT != (ulPassStatus & EMS_PASSFLAG_RESULT_MASK) &&
				EMS_PASSFLAG_ERROR != (ulPassStatus & EMS_PASSFLAG_RESULT_MASK) )
			{
				ulPassStatus |= EMS_PASSFLAG_SUCCESS;
			}
		}

		switch ( ulPassStatus & EMS_PASSFLAG_RESULT_MASK )	
		{
			default:						lstrcat(szProcStatus,TEXT(".")); break;
			case EMS_PASSFLAG_SUCCESS:		lstrcat(szProcStatus,TEXT("S")); break;
			case EMS_PASSFLAG_ABORT:		lstrcat(szProcStatus,TEXT("A")); break;
			case EMS_PASSFLAG_ERROR:		lstrcat(szProcStatus,TEXT("X")); break;
		}
		
		SetPassStatus( ulPassStatus );

		if( hr == EMS_OK )	
		{
			int nPredictedDuration = GetSecondsDuration();
			int nActualDuration = GetSecondsCollecting();
			int nPDSRecoveryRate = GetPDSRecoveryRate();

			if( nPredictedDuration < 0 )
				nPredictedDuration = 0;

			if( nPredictedDuration > 9999 )
				nPredictedDuration = 9999;

			if( nActualDuration < 0 )
				nActualDuration = 0;

			if( nActualDuration > 9999 )
				nActualDuration = 9999;

			if( nPDSRecoveryRate > 999 )
			{
				nPDSRecoveryRate = 999;
			}
			else if( nPDSRecoveryRate < 0 )
			{
				nPDSRecoveryRate = 0;
			}

			_stprintf( szBuffer, c_szSitBodyLine2Fmt,
								nPredictedDuration,
								nActualDuration,
								GetPercentageCollecting(),
								szProcStatus,
								nPDSRecoveryRate,
								GetFramesMissed(),
								GetTotalPDSCount(),
								GetDistinctPDSCount(),
								GetSarrMessages() );

			hr = WriteLine( lpStream, szBuffer );
		}

	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine2( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];

		_stprintf( szBuffer, c_szSitBodyLine3FmtB, m_ulEpochOrbNum,
			                   msgField.TextMF34( GetOrbitEpoch() ) );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine3( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];

		_stprintf( szBuffer, c_szSitBodyLine4FmtB,
								GetOrbitPosition().fX,
								GetOrbitPosition().fY,
								GetOrbitPosition().fZ,
								GetOrbitVelocity().fX,
								GetOrbitVelocity().fY,
								GetOrbitVelocity().fZ );

		hr = WriteLine( lpStream, szBuffer );

	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine4( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];
		TCHAR	        str[10];

		switch ( GetOrbitUpdateStatus() )
		{
		case EMSSIT661OrbitUpdateInSpec: 
			{
				lstrcpy(str, TEXT("IN"));
			}
			break;
		
		default:
		case EMSSIT661OrbitUpdateOutSpec: 
			{
				lstrcpy(str, TEXT("OU"));
			}
			break;

		case EMSSIT661OrbitUpdatePredict:
			{
				lstrcpy(str, TEXT("PR"));
			}
			break;
		}

		_stprintf( szBuffer, c_szSitBodyLine5Fmt, str,
								GetOrbitPositionOffset(),
								GetOrbitVelocityOffset() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine5( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];

		_stprintf( szBuffer, c_szSitBodyLine6FmtB, 
			                     msgField.TextMF37( GetRolloverTime() ),
								 msgField.TextMF38A( m_dUSOFreq ),
								 GetSarr406FreqOffset() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine6( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];

		// /MF609/MF08B/MF08C/MF08D/MF08E/MF10B/MF10C/MF633/MF634/08F/669

		int iMF633 = _ChkMessageCountRange( GetAlarmMessages(), cwszAlarmMessages );
		int iMF634 = _ChkMessageCountRange( GetWarningMessages(), cwszWarningMessages );

		_stprintf( szBuffer, c_szSitBodyLine7FmtB,
								msgField.TextMF609( GetSolutionProcessingTime() ),
								Get121Transmitters(),
								Get243Transmitters(),
								Get406Interferers(),
								Get406LocatedBeacons(),
								Get406UnlocatedBeacons(),
								GetUnlocatedAlerts(),
								iMF633,							//MF #633 
								iMF634,							//MF #634 
								m_iMedianLocAccSampleSize,
								m_dMedianLocAccuracy );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryStatsLine( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];

		// /665/666/667/668
		_stprintf( szBuffer, c_szSitBodyStatsLineFmtB,
			                    m_wGeneralStatus,
								msgField.TextMF666( m_tmLastClockSync ),
								msgField.TextMF667( m_tmEarliestSARP ),
								msgField.TextMF668( m_tmLastSARP ) );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


EMS_RESULT
CEMSSit661B::_WritePassSummaryLine7( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lpStream )
	{
		CEMSSitMsgField msgField;
		TCHAR           szBuffer[ 256 ];
		TCHAR	        szNextStatus[10];
		TCHAR           szMF602[64];
		TCHAR           szMF603[64];

		switch ( GetNextPassStatus() & EMS_PASSFLAG_ORIGIN_MASK )	// origin
		{
		default:						lstrcpy(szNextStatus,TEXT(".")); break;
		case EMS_PASSFLAG_LUT:			lstrcpy(szNextStatus,TEXT("L")); break;
		case EMS_PASSFLAG_MCC:			lstrcpy(szNextStatus,TEXT("M")); break;
		case EMS_PASSFLAG_RCC:			lstrcpy(szNextStatus,TEXT("R")); break;
		case EMS_PASSFLAG_OPERATOR:		lstrcpy(szNextStatus,TEXT("O")); break;
		}

		switch ( GetNextPassStatus() & EMS_PASSFLAG_STATUS_MASK )
		{
		default:						lstrcat(szNextStatus,TEXT("P")); break;
		case EMS_PASSFLAG_SUPPRESS: 	lstrcat(szNextStatus,TEXT("X")); break;
		case EMS_PASSFLAG_PROCESS:		lstrcat(szNextStatus,TEXT("F")); break;
		case EMS_PASSFLAG_REDUNDANT:	lstrcat(szNextStatus,TEXT("R")); break;
		}

		switch ( GetNextPassStatus() & EMS_PASSFLAG_RESULT_MASK )	
		{
		default:						lstrcat(szNextStatus,TEXT(".")); break;
		case EMS_PASSFLAG_SUCCESS:		lstrcat(szNextStatus,TEXT("S")); break;
		case EMS_PASSFLAG_ABORT:		lstrcat(szNextStatus,TEXT("A")); break;
		case EMS_PASSFLAG_ERROR:		lstrcat(szNextStatus,TEXT("X")); break;
		}

		lstrcpy( szMF602, msgField.TextMF602( GetNextAOSTime() ) );

		lstrcpy( szMF603, msgField.TextMF603( GetNextLOSTime() ) );

		_stprintf( szBuffer, c_szSitBodyLine8Fmt, GetNextSatID(),
			                    GetNextOrbitNumber(), szMF602, szMF603,
								szNextStatus );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}


