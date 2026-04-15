/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$


********************************************************************/

#include "routedescription.h"

CEMSRouteDescription::CEMSRouteDescription() : m_ulSourceID(0), m_ulDestID(0)
{
}

CEMSRouteDescription::CEMSRouteDescription( const CEMSRouteDescription& x) : m_wszRouteID( x.m_wszRouteID ), 
											m_ulSourceID( x.m_ulSourceID ),	m_wszSourceAlias( x.m_wszSourceAlias ), 
											m_ulDestID( x.m_ulDestID ),	m_wszDestAlias( x.m_wszDestAlias )
{
}

CEMSRouteDescription::~CEMSRouteDescription()
{
}

void 
CEMSRouteDescription::SetRouteID( const wchar_t* cwszRouteID )
{
	if( cwszRouteID )
	{
		m_wszRouteID = cwszRouteID;
	}
}

std::wstring 
CEMSRouteDescription::GetRouteID() const
{
	return m_wszRouteID;
}

void 
CEMSRouteDescription::SetSourceID( const ULONG culSourceID )
{
	m_ulSourceID = culSourceID;
}

ULONG 
CEMSRouteDescription::GetSourceID() const
{
	return m_ulSourceID;
}

void 
CEMSRouteDescription::SetSourceAlias( const wchar_t* cwszAlias )
{
	if( cwszAlias )
	{
		m_wszSourceAlias = cwszAlias;
	}
}

std::wstring 
CEMSRouteDescription::GetSourceAlias() const
{
	return m_wszSourceAlias;
}

void 
CEMSRouteDescription::SetDestinationID( const ULONG culDestID )
{
	m_ulDestID = culDestID;
}

ULONG 
CEMSRouteDescription::GetDestinationID() const
{
	return m_ulDestID;
}

void 
CEMSRouteDescription::SetDestinationAlias( const wchar_t* cwszAlias )
{
	if( cwszAlias )
	{
		m_wszDestAlias = cwszAlias;
	}
}

std::wstring 
CEMSRouteDescription::GetDestinationAlias() const
{
	return m_wszDestAlias;
}


