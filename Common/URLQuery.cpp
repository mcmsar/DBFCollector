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
#pragma warning(disable:4786)

#include "urlquery.h"
#include <sstream>
#include "urlencoder.h"

const wchar_t* CEMSURLQuery::ms_cwszParamSeparator = L"&";

CEMSURLQuery::CEMSURLQuery()
{
}

CEMSURLQuery::CEMSURLQuery( const CEMSURLQuery& x ) : m_owszQuery( x.m_owszQuery ),
														m_mapParams( x.m_mapParams )
{
}

CEMSURLQuery::~CEMSURLQuery()
{
}

void 
CEMSURLQuery::Set( const wchar_t* cwszQuery )
{
	if( cwszQuery )
	{
		m_owszQuery = cwszQuery;

		_Parse();
	}
}

std::wstring 
CEMSURLQuery::Get()
{
	return _Generate();
}

std::wstring 
CEMSURLQuery::GetDecoded()
{
	CEMSURLEncoder oEncoder;

	return oEncoder.Decode(_Generate().c_str() );
}

void 
CEMSURLQuery::AddParam( CEMSURLQueryParam& oQueryParam )
{
	// Delete it if it already exists in the map.  Effectively replace it.
	m_mapParams.Remove( oQueryParam.GetLHS() );

	m_mapParams.Add( oQueryParam.GetLHS(), oQueryParam );
}

CEMSURLQueryParam 
CEMSURLQuery::GetParam( const wchar_t* cwszLHS )
{
	return m_mapParams.Get( std::wstring( cwszLHS ) );
}

CEMSObjectList<CEMSURLQueryParam> 
CEMSURLQuery::GetParams()
{
	// Convert the map into a list
	CEMSObjectList<CEMSURLQueryParam> oRet;

	m_mapParams.MoveFirst();

	for( ULONG l = 0; l <  m_mapParams.Count(); l++ )
	{
		oRet.Add( m_mapParams.GetNext() );
	}

	return oRet;
}

void 
CEMSURLQuery::Clear()
{
	m_owszQuery.erase();
	m_mapParams.Clear();
}

CEMSURLQuery& 
CEMSURLQuery::operator=( const CEMSURLQuery& crhs )
{
	m_owszQuery = crhs.m_owszQuery;
	m_mapParams = crhs.m_mapParams;

	return *this;
}

void 
CEMSURLQuery::_Parse()
{
	if( !m_owszQuery.empty() )
	{
		m_mapParams.Clear();

		std::wstring::size_type iPosSeparator = 0;
		std::wstring::size_type iStartPos = 0;

		while( iStartPos < m_owszQuery.length() )
		{
			iPosSeparator = m_owszQuery.find( ms_cwszParamSeparator, iStartPos );

			std::wstring owszParam;

			if( std::wstring::npos != iPosSeparator )
			{
				owszParam = m_owszQuery.substr( iStartPos, iPosSeparator - iStartPos );
			}
			else
			{
				owszParam = m_owszQuery.substr( iStartPos, m_owszQuery.length() - iStartPos );

				iPosSeparator = m_owszQuery.length();
			}

			if( !owszParam.empty() )
			{

				CEMSURLQueryParam oParam;
				oParam.Set( owszParam.c_str() );

				m_mapParams.Add( oParam.GetLHS(), oParam );

				iStartPos = iPosSeparator + wcslen( ms_cwszParamSeparator );
			}

		}
	}
}

std::wstring 
CEMSURLQuery::_Generate()
{
	std::wstringstream wstrmBuf;

	m_mapParams.MoveFirst();

	for( ULONG l = 0; l < m_mapParams.Count(); l++ )
	{
		CEMSURLQueryParam oParam = m_mapParams.GetNext();

		if( l > 0 )
		{
			wstrmBuf << ms_cwszParamSeparator;
		}

		wstrmBuf << oParam.Get();
	}

	m_owszQuery = wstrmBuf.str();

	return m_owszQuery;
}