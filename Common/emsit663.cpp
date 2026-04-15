/********************************************************************
*       Module:         emsit663.h
*       Description:    Implementation of the CEMSSit663A Class
*						Beacon Advisory Report SIT Message
*
*********************************************************************
*	Copyright (c) 2009 by EMS Technologies, Inc.,
*	All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include <assert.h>
#include <array.h>
#include <sitfield.h>
#include <emsit663.h>
#include <emsexcpt.h>
#include "sgenMsgs.h"

CEMSSit663A::CEMSSit663A() :
   m_bInitialized( false ), m_iBeaconCount(0), m_aBeaconData(0), m_iBeaconAlloc(0)
{
   SetSitNumber( 663 );
   SetSitCode( 0x663A );
}

CEMSSit663A::~CEMSSit663A()
{
	Reset();
}

void
CEMSSit663A::Reset( void )
{
   CEMSSitMessageBase::Reset();

	SetSitNumber( 663 );
	SetSitCode( 0x663A );

	if ( m_aBeaconData )
	{
		delete[] m_aBeaconData;
		m_aBeaconData = 0;
	}
	m_iBeaconAlloc = 0;
	m_iBeaconCount = 0;
	m_bInitialized = false;
}

EMS_RESULT 
CEMSSit663A::SetCount( const int ciCount )
{
	EMS_RESULT hr = EMS_OK;
	if ( m_iBeaconAlloc > 0 )
	{
		// This is a programming error
		assert( false );
		hr = EMS_SIT_ALREADY_INITIALIZED;
	}
	else
	{
		m_aBeaconData = new EMS_BEACON_ADVISORY[ciCount];
		if ( !m_aBeaconData )
		{
			hr = EMS_NO_MEMORY;
		}
		else
		{
			m_iBeaconAlloc = ciCount;
			m_iBeaconCount = 0;
			m_bInitialized = true;
		}
	}
	return hr;
}

EMS_RESULT 
CEMSSit663A::AddBeaconAdvisory( const EMS_BEACON_ADVISORY& advisory )
{
	EMS_RESULT hr = EMS_OK;
	if ( m_iBeaconCount == m_iBeaconAlloc )
	{
		// We are being asked to add more advisories than we have space for
		hr = EMS_BAD_PARAM;
	}
	else
	{
		m_aBeaconData[m_iBeaconCount++] = advisory;
	}
	return hr;

}

void 
CEMSSit663A::GetBeacon( const int ciIndex, EMS_BEACON_ADVISORY& beacon ) 
{
	if ( ciIndex < m_iBeaconCount )
	{
		beacon = m_aBeaconData[ciIndex]; 
	}
	else
	{
		THROW_RUNTIME_EXCEPTION(EMS_BAD_PARAM); 
	}
}

EMS_RESULT
CEMSSit663A::GenerateSitHeader( IEMSSeqStream *lpStream )
{
	if ( !lpStream ) return EMS_INVALID_STREAM;
	if ( !m_bInitialized ) return EMS_NOT_INITIALIZED;

	EMS_RESULT hr = EMS_OK;

	// MF# /04/05/04A/606 = "/663/1234/663A/003"
	const TCHAR c_szSitHdrFmt[] = TEXT("/%03d/%04d/%s/%03d");

	TCHAR szBuffer[ 256 ];

	_sntprintf( szBuffer, 256, c_szSitHdrFmt,
		GetSitNumber(),         // MF# 04   sit number
		GetSitDestination(),    // MF# 05   sit destination
		GetSitCodeStr(),		// MF# 04A  sit code (modified sit number)                              
		GetBeaconCount());      // MF #606	number of beacon records to follow

	// send the string
	hr = WriteLine( lpStream, szBuffer );

	return hr;
}

EMS_RESULT
CEMSSit663A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	if ( !lpStream ) return EMS_INVALID_STREAM;
	if ( !m_bInitialized ) return EMS_NOT_INITIALIZED;

	EMS_RESULT hr = EMS_OK;
	for ( int i=0; i<GetBeaconCount() && SUCCEEDED(hr); i++ )
	{
		hr = _GenerateSitBodyBeaconLines( i, lpStream );
	}
	return hr;
}



EMS_RESULT
CEMSSit663A::_GenerateSitBodyBeaconLines( const int ciIndex, IEMSSeqStream *lpStream )
{
	if ( !lpStream ) return EMS_INVALID_STREAM;
	if ( !m_bInitialized ) return EMS_NOT_INITIALIZED;
	assert( ciIndex < m_iBeaconCount );

	EMS_RESULT hr = EMS_OK;
	try
	{
	
		EMS_BEACON_ADVISORY	beacon;
		GetBeacon( ciIndex, beacon );

		TCHAR			szBuffer[ 256 ];
		CEMSSitMsgField	textField;

		// Four lines per beacon
		// MF#	/22/21C/619 = 15 hex beacon ID/# test bursts/# burst total
		const	TCHAR	c_tszBeaconLine1[] = TEXT("/%s/%04d/%04d");
		_sntprintf( szBuffer, 256, c_tszBeaconLine1,
			textField.TextMF22( beacon.i64BeaconID ),
			min( beacon.ulTestBurstCount, 9999 ),
			min( beacon.ulTotalBurstCount, 9999 ) );
		hr = WriteLine( lpStream, szBuffer );

		// MF#	/23 = full beacon message
		if ( SUCCEEDED(hr) )
		{
			_sntprintf( szBuffer, 256, TEXT("/%s"),
				textField.TextMF23( beacon.cBeaconMsg ) );
			hr = WriteLine( lpStream, szBuffer );
		}

		// MF#	/06/07/14A/14B = lastSatID/lastPassID/timefirstdetect/timelastdetect
		if ( SUCCEEDED(hr) )
		{
			const	TCHAR	c_tszBeaconLine3[] = TEXT("/%03d/%05d/%s/%s");
			_sntprintf( szBuffer, 256, c_tszBeaconLine3,
				beacon.ulSatID,
				beacon.ulPassID,
				textField.TextMF14A(beacon.timeFirstDetect),
				textField.TextMF14B(beacon.timeLastDetect) );
			hr = WriteLine( lpStream, szBuffer );
		}

		// MF#	/25/26 = calculated latitude & longitude
		if ( SUCCEEDED(hr) )
		{
			const	TCHAR	c_tszBeaconLine4[] = TEXT("/%s/%s");
			_sntprintf( szBuffer, 256, c_tszBeaconLine4,
				textField.TextMF25A(beacon.dDegLatitude),
				textField.TextMF26A(beacon.dDegLongitude) );
			hr = WriteLine( lpStream, szBuffer );
		}
	}
	catch( CEMSException& excpt )
	{
		hr = excpt.GetErrCode();
	}
	catch(...)
	{
		hr = EMS_EXCEPTION;
	}
	return hr;
}