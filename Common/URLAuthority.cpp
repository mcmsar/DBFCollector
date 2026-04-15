/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#include "urlauthority.h"
#include <sstream>

const wchar_t* CEMSURLAuthority::ms_cwszPortDelimiter = L":";

CEMSURLAuthority::CEMSURLAuthority()
{
}

CEMSURLAuthority::CEMSURLAuthority( const CEMSURLAuthority& x ) : m_owszHost( x.m_owszHost ),
																	m_owszPort( x.m_owszPort )
{
}

CEMSURLAuthority::~CEMSURLAuthority()
{
}

void 
CEMSURLAuthority::SetHost( const wchar_t* cwszValue )
{
	if( cwszValue )
		m_owszHost = cwszValue;
}

std::wstring 
CEMSURLAuthority::GetHost() const
{
	return m_owszHost;
}

void 
CEMSURLAuthority::SetPort( const wchar_t* cwszValue )
{
	if( cwszValue )
		m_owszPort = cwszValue;
}

std::wstring 
CEMSURLAuthority::GetPort() const
{
	return m_owszPort;
}

std::wstring 
CEMSURLAuthority::Get() const
{
	std::wstringstream wstrmRet;

	if( !m_owszHost.empty() )
	{
		wstrmRet << m_owszHost;

		if( !m_owszPort.empty() )
		{
			wstrmRet << ms_cwszPortDelimiter << m_owszPort;
		}
	}

	return wstrmRet.str();
}

void 
CEMSURLAuthority::Set( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		// Parse it.
		std::wstring owszTemp( cwszValue );

		std::wstring::size_type iPos = owszTemp.find( ms_cwszPortDelimiter );

		if( std::wstring::npos == iPos )
		{
			m_owszHost = cwszValue;
		}
		else
		{
			m_owszHost = owszTemp.substr( 0, iPos );
			m_owszPort = owszTemp.substr( iPos + wcslen( ms_cwszPortDelimiter), 
									owszTemp.length() - ( iPos + wcslen( ms_cwszPortDelimiter) ) );
		}
	}
}