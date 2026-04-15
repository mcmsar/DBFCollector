/********************************************************************
*    Module:            SARRTime.cpp
*    Process ID:
*    S/W Platforms:
*    H/W Platforms:
*    Compiler:
*    Description:     CEMSSARRTimeCheck class
*
*    Usage:
*    Entry Point:
*    Input Files:
*    Output Files:
*    Comments:			Uses the Toulouse Beacon(s) to confirm whether 
*							the digital acquistion time is correct
*								
*********************************************************************
*                  Copyright (c) 2007 by EMS Technologies, Inc.,
*                                        All rights reserved
*    This program is unpublished software and contains the trade secrets
*    and confidential information of EMS Technologies, Inc.  It may not be
* reproduced in whole or in part, in any form or by any means whatsoever
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

    Rev    Date            Auth    Changes
    ===    ====            ====    =======

    0.0    2007 Mar 3       rvw        start

********************************************************************/
#include <stdio.h>

#include "sarrtime.h"
#include "LogHelper.h"
#include "logmsgparam.h"
#include "emsconst.h"
#include "calib406msg.h"

const double c_dMaxValidTimeOffset = 1.0; // Max allowed time offset to be considered valid (in seconds)

CEMSSARRTimeCheck::CEMSSARRTimeCheck( )
{
	m_bLogEnabled = false;
	m_bWarningEnabled = false;

	Reset( );
}

CEMSSARRTimeCheck::~CEMSSARRTimeCheck( )
{
}


EMS_RESULT CEMSSARRTimeCheck::Initialize( EMSREFBEACONDATAEX *lpRefBeaconData, INT nRefBeaconCount )
{
	EMS_RESULT hr = EMS_OK;

	Reset( );

	if ( lpRefBeaconData && nRefBeaconCount )
	{
		for ( int i = 0; i < nRefBeaconCount; i++ )
		{
		  if ( EMS_BEACON_TCAL == ( lpRefBeaconData[i].data.uFlag & EMS_BEACON_TCAL ) )
		{
	 		if ( m_nTCALBeacons < c_nMaxTCALBeacons )
			{
				m_TCALBeacon[ m_nTCALBeacons++ ] = lpRefBeaconData[ i ];
			}
		 }
		}
	}

	// warn/info msg - telling how many TCAL beacons have been configured

	if ( m_bLogEnabled )
	{
		CEMSLogMsgParam params(2);

		params.Add( m_nTCALBeacons );

		CEMSLogHelper::LogInfoMsg( EMS_CALIB406_TCAL_BEACON_COUNT, params );
	}
	return hr;
}

void CEMSSARRTimeCheck::Reset( void )
{
	memset( &m_TCALBeacon, 0, sizeof( m_TCALBeacon ) );

	m_nTCALBeacons = 0;

	memset( &m_chk, 0, sizeof( m_chk ) );

	m_nChkRecords = 0;
}

EMS_RESULT CEMSSARRTimeCheck::CheckData( EMSCALIB406DATA *lpCalib406 )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpCalib406 )
	{
		int nIndex = -1;

		switch ( lpCalib406->hdr.wType )
		{
		 	case EMSCALIBTYPE_406_SARR:
				nIndex = _GetTCALBeaconIdx( lpCalib406->i64BeaconID );

				if ( nIndex >= 0 )
				{
					hr = _CheckTCALData( lpCalib406->hdr.id.ulLutID, 0,
											lpCalib406->timeMsg, &m_TCALBeacon[ nIndex ] );
				}
				break;

		 	case EMSCALIBTYPE_406_SARP:
			default:		// nothing to check
				break;
		}
	}
	return hr;
}

EMS_RESULT CEMSSARRTimeCheck::CheckData( EMSSARRDATA *lpSarr406 )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpSarr406 )
	{
		int nIndex = _GetTCALBeaconIdx( lpSarr406->i64BeaconID );

		if ( nIndex >= 0 )
		{
			hr = _CheckTCALData( lpSarr406->hdr.id.ulLutID, 0,
									lpSarr406->timeMsg, &m_TCALBeacon[ nIndex ] );
		}
	}
	return hr;
}

EMS_RESULT CEMSSARRTimeCheck::CheckData( EMSCALIB406DATA2 *lpCalib406 )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpCalib406 )
	{
		int nIndex = -1;

		switch ( lpCalib406->hdr.wType )
		{
		 	case EMSCALIBTYPE_406_SARR:
				nIndex = _GetTCALBeaconIdx( lpCalib406->i64BeaconID );

				if ( nIndex >= 0 )
				{
					hr = _CheckTCALData( lpCalib406->hdr.id.ulLutID, 
											lpCalib406->wAntennaID, 
											lpCalib406->timeMsg, &m_TCALBeacon[ nIndex ] );
				}
				break;

		 	case EMSCALIBTYPE_406_SARP:
			default:		// nothing to check
				break;
		}
	}
	return hr;
}


INT CEMSSARRTimeCheck::_GetTCALBeaconIdx( INT64 i64BeaconID )
{
	INT nIndex = -1;

	for (int i = 0; ( i < m_nTCALBeacons ) && ( -1 == nIndex ); i++ )
	{
		if ( i64BeaconID == m_TCALBeacon[i].i64BeaconID )
			nIndex = i;
	}
	return nIndex;
}

EMS_RESULT CEMSSARRTimeCheck::_CheckTCALData( ULONG ulLutID, ULONG ulAntennaID, EMSTIME timeMsg, EMSREFBEACONDATAEX *lpRefBeacon )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpRefBeacon )
	{
		INT nIndex = _GetLUTAntennaIdx( ulLutID, ulAntennaID );

		if ( -1 == nIndex )	// chk record not created yet, do so now
		{
			if ( m_nChkRecords < c_nMaxLUTAntennaPairs )
			{
				nIndex = m_nChkRecords++;

				m_chk[ nIndex ].ulLutID = ulLutID;

				m_chk[ nIndex ].ulAntennaID = ulAntennaID;

				m_chk[ nIndex ].i64TCALBursts = 0;

				m_chk[ nIndex ].dTimeOffset = 0.0;
			}
		}

		if ( nIndex >= 0 )
		{	
			EMSTIMEFIELDS tf;
			CEMSTime timeTemp;
			char szTemp[64];
			EMSTIMECHECKSTATUS newStatus, oldStatus = _GetTimeStatus( &m_chk[ nIndex ] );
//			double dRepRateFactor = (lpRefBeacon->data.dRepRate - int( lpRefBeacon->data.dRepRate + 0.5))/
//                               int( lpRefBeacon->data.dRepRate + 0.5);

			INT64 i64TimeDiff = (INT64)( timeMsg.intTime %
                              (INT64)(c_dNanoSecsPerSec * lpRefBeacon->data.dRepRate ) );

			timeTemp.SetTime( timeMsg );

			timeTemp.GetTime( &tf );

			sprintf( szTemp, "%02d:%02d:%.2lf", tf.nHour, tf.nMinute, 
				(double)tf.nSecond + ((double)tf.lNanosecond / 1000000000.0 ) );

			m_chk[ nIndex ].i64TCALBursts++;

			m_chk[ nIndex ].dTimeOffset = (double)i64TimeDiff / c_dNanoSecsPerSec;

			if ( ( lpRefBeacon->data.dRepRate - m_chk[ nIndex ].dTimeOffset ) <
				m_chk[ nIndex ].dTimeOffset )
			{
				m_chk[ nIndex ].dTimeOffset = lpRefBeacon->data.dRepRate - m_chk[ nIndex ].dTimeOffset;
			}

			newStatus = _GetTimeStatus( &m_chk[ nIndex ] );

			if ( newStatus != oldStatus )
			{
				_LogTimeStatusChange( &m_chk[ nIndex ] );
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


void CEMSSARRTimeCheck::_LogTimeStatusChange( EMSLUTANTENNATIMECHECK *lpChk )
{
	if ( lpChk && m_bLogEnabled )	// only log if enabled
	{
		CEMSLogMsgParam params(4);

		params.Add( lpChk->ulLutID );

		params.Add( lpChk->ulAntennaID );

		// log the new state
		switch ( _GetTimeStatus( lpChk ) )
		{
			case EMS_TCS_Valid:
				CEMSLogHelper::LogInfoMsg( EMS_CALIB406_SARR_TIME_OKAY, params );
				break;

			case EMS_TCS_Invalid:
				params.Add( (int)lpChk->dTimeOffset / 1 );

				if ( m_bWarningEnabled )
					CEMSLogHelper::LogWarningMsg( EMS_CALIB406_SARR_TIME_ERROR, params );
				else
					CEMSLogHelper::LogInfoMsg( EMS_CALIB406_SARR_TIME_ERROR, params );
				break;

			case EMS_TCS_Unknown:
			default:
				break;
		}
	}
}

INT CEMSSARRTimeCheck::_GetLUTAntennaIdx( ULONG ulLutID, ULONG ulAntennaID )
{
	INT nIndex = -1;

	for ( int i = 0; ( i < m_nChkRecords ) && ( -1 == nIndex ); i++ )
	{
		if ( ( m_chk[i].ulLutID == ulLutID ) && ( m_chk[i].ulAntennaID == ulAntennaID ) )
		{
			nIndex = i;
		}
	}

	return nIndex;
}

//EMSTIMECHECKSTATUS CEMSSARRTimeCheck::SetLutAntennaReported( ULONG ulLutID, ULONG ulAntennaID )
//{
//	EMSTIMECHECKSTATUS status = EMS_TCS_Unknown;
//	INT nIndex = _GetLUTAntennaIdx( ulLutID, ulAntennaID );
//
//	if ( nIndex >= 0 )
//	{
//		m_chk[ nIndex ].bReported = true;
//
//		status = _GetTimeStatus( &m_chk[ nIndex ] );
//	}
//
//	return status;
//}


EMSTIMECHECKSTATUS CEMSSARRTimeCheck::GetLutAntennaTimeStatus( ULONG ulLutID, ULONG ulAntennaID )
{
	EMSTIMECHECKSTATUS status = EMS_TCS_Unknown;
	INT nIndex = _GetLUTAntennaIdx( ulLutID, ulAntennaID );

	if ( nIndex >= 0 )
	{
		status = _GetTimeStatus( &m_chk[ nIndex ] );
	}

	return status;
}


EMSTIMECHECKSTATUS CEMSSARRTimeCheck::_GetTimeStatus( EMSLUTANTENNATIMECHECK *lpChk )
{
	EMSTIMECHECKSTATUS status = EMS_TCS_Unknown;

	if ( lpChk )
	{
		if ( 0 == lpChk->i64TCALBursts )
			status = EMS_TCS_Unknown;
		else
		{
			status = ( fabs( lpChk->dTimeOffset ) <= c_dMaxValidTimeOffset ) ? EMS_TCS_Valid : EMS_TCS_Invalid;

//			if ( !lpChk->bReported )
//				status = (EMSTIMECHECKSTATUS)( (int)status + EMS_TCS_Unreported );
		}
	}

	return status;
}
