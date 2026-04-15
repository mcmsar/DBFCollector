/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "logprocesssettings.h"

CEMSLogProcessSettings CEMSLogProcessSettings::m_oLogProcessSettings;

CEMSLogProcessSettings::CEMSLogProcessSettings() : m_ulLutID(0), m_ulProcessID(0)
{
}

CEMSLogProcessSettings::~CEMSLogProcessSettings()
{
}

CEMSLogProcessSettings* 
CEMSLogProcessSettings::GetInstance()
{
	return &m_oLogProcessSettings;
}

void 
CEMSLogProcessSettings::SetLutID( const ULONG culLutID )
{
	m_csSettings.Enter();

	// Don't reset to zero.
	if( 0 != culLutID )
	{
		m_ulLutID = culLutID;
	}

	m_csSettings.Leave();
}

ULONG 
CEMSLogProcessSettings::GetLutID()
{
	ULONG ulRet = 0;

	m_csSettings.Enter();

	ulRet = m_ulLutID;

	m_csSettings.Leave();

	return ulRet;
}

void 
CEMSLogProcessSettings::SetProcessID( const ULONG culProcessID )
{
	m_csSettings.Enter();

	if( 0 != culProcessID )
		m_ulProcessID = culProcessID;

	m_csSettings.Leave();
}

ULONG 
CEMSLogProcessSettings::GetProcessID()
{
	ULONG ulRet = 0;

	m_csSettings.Enter();

	ulRet = m_ulProcessID;

	m_csSettings.Leave();

	return ulRet;
}

void
CEMSLogProcessSettings::SetProcessName( const wchar_t* cwszProcessName )
{
	try
	{
		m_csSettings.Enter();

		if( cwszProcessName )
			m_oszProcessName = cwszProcessName;

		m_csSettings.Leave();
	}
	catch( ... )
	{
		m_csSettings.Leave();

		throw;
	}
}

EMSLOGString
CEMSLogProcessSettings::GetProcessName( )
{
	EMSLOGString oszRet;

	try
	{
		m_csSettings.Enter();

		oszRet = m_oszProcessName;

		m_csSettings.Leave();
	}
	catch( ... )
	{
		m_csSettings.Leave();

		throw;
	}

	return oszRet;
}

