/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "dccontrol.h"

CEMSDCControl CEMSDCControl::ms_oThis;

CEMSDCControl::CEMSDCControl() : m_ulSatID(0), m_ulFlags(0), m_ulBandwidth(0), m_ulInputDataID(0),
							m_hStart(INVALID_HANDLE_VALUE), m_hStop(INVALID_HANDLE_VALUE), 
							m_hSetSatellite(INVALID_HANDLE_VALUE), m_hSetInputDataID(INVALID_HANDLE_VALUE)
{
	m_hStart = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hStop = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hSetSatellite = CreateEvent( NULL, FALSE, FALSE, NULL );
	m_hSetInputDataID = CreateEvent( NULL, FALSE, FALSE, NULL );
}

CEMSDCControl::~CEMSDCControl()
{
	if ( INVALID_HANDLE_VALUE != m_hStart )
	{
		CloseHandle( m_hStart );
		m_hStart = INVALID_HANDLE_VALUE;
	}

	if ( INVALID_HANDLE_VALUE != m_hStop )
	{
		CloseHandle( m_hStop );
		m_hStop = INVALID_HANDLE_VALUE;
	}

	if ( INVALID_HANDLE_VALUE != m_hSetSatellite )
	{
		CloseHandle( m_hSetSatellite );
		m_hSetSatellite = INVALID_HANDLE_VALUE;
	}

	if ( INVALID_HANDLE_VALUE != m_hSetInputDataID )
	{
		CloseHandle( m_hSetInputDataID );
		m_hSetInputDataID = INVALID_HANDLE_VALUE;
	}
}

CEMSDCControl* 
CEMSDCControl::GetInstance()
{
	return &ms_oThis;
}

void 
CEMSDCControl::Start( const ULONG culADBoardID, const ULONG culChannelID )
{
	SetEvent( m_hStart );
}

void 
CEMSDCControl::Stop( const ULONG culADBoardID, const ULONG culChannelID )
{
	SetEvent( m_hStop );
}

void 
CEMSDCControl::SetSatelliteID( const ULONG culADBoardID, const ULONG culChannelID,
					const ULONG culSatID, const ULONG culFlags,
					const ULONG culBandwidth )
{
	m_ulSatID = culSatID;
	m_ulFlags = culFlags;
	m_ulBandwidth = culBandwidth;

	SetEvent( m_hSetSatellite );
}

void
CEMSDCControl::SetInputDataID( const ULONG culADBoardID, const ULONG culChannelID,
					const ULONG culInputDataID )
{
	m_ulInputDataID = culInputDataID;

	SetEvent( m_hSetInputDataID );
}