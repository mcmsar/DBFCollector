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

#include "urlqueryparam.h"
#include <sstream>
#include "emsexcpt.h"
#include "urlencoder.h"

const wchar_t* CEMSURLQueryParam::ms_cwszSeparator = L"=";

CEMSURLQueryParam::CEMSURLQueryParam()
{
}

CEMSURLQueryParam::CEMSURLQueryParam( const CEMSURLQueryParam& x ) : 
																m_owszQueryParam( x.m_owszQueryParam ),
																m_owszLHS( x.m_owszLHS ),
																m_owszRHS( x.m_owszRHS )
{
}

CEMSURLQueryParam::~CEMSURLQueryParam()
{
}

void 
CEMSURLQueryParam::Set( const wchar_t* cwszParameter )
{
	if( cwszParameter )
	{
		m_owszQueryParam = cwszParameter;

		_Parse();
	}
}

std::wstring 
CEMSURLQueryParam::Get()
{
	return _Generate();
}

void 
CEMSURLQueryParam::Set( const wchar_t* cwszLHS, const wchar_t* cwszRHS )
{
	if( cwszLHS && cwszRHS )
	{
		m_owszLHS = cwszLHS;

		CEMSURLEncoder oEncoder;

		m_owszRHS = oEncoder.Encode( cwszRHS );

		_Generate();
	}
}

std::wstring 
CEMSURLQueryParam::GetValue()
{
	_Parse();

	CEMSURLEncoder oEncoder;

	return oEncoder.Decode( m_owszRHS.c_str() );
}

std::wstring 
CEMSURLQueryParam::GetLHS()
{
	_Parse();

	return m_owszLHS;
}

CEMSURLQueryParam& 
CEMSURLQueryParam::operator=( const CEMSURLQueryParam& crhs )
{
	m_owszQueryParam = crhs.m_owszQueryParam;
	m_owszLHS = crhs.m_owszLHS;
	m_owszRHS = crhs.m_owszRHS;

	return *this;
}

void 
CEMSURLQueryParam::_Parse()
{
	if( !m_owszQueryParam.empty() )
	{
		std::wstring::size_type iPosEquals = m_owszQueryParam.find( ms_cwszSeparator );

		if( std::wstring::npos == iPosEquals )
		{
			// The LHS and RHS must be separated by an equals.
			throw CEMSException( EMS_SYNTAX_ERROR );
		}

		m_owszLHS = m_owszQueryParam.substr( 0, iPosEquals );

		m_owszRHS = m_owszQueryParam.substr( iPosEquals + wcslen( ms_cwszSeparator), 
						m_owszQueryParam.length() - ( iPosEquals + wcslen( ms_cwszSeparator) ) );
	}
}

std::wstring 
CEMSURLQueryParam::_Generate()
{
	if( !m_owszLHS.empty() && !m_owszRHS.empty() )
	{
		std::wstringstream owstrmBuf;

		owstrmBuf << m_owszLHS.c_str() << ms_cwszSeparator << m_owszRHS.c_str();

		m_owszQueryParam = owstrmBuf.str();
	}

	return m_owszQueryParam;
}
