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

#include "emsurl.h"
#include "dataiomsgs.h"
#include "resourcemsgs.h"
#include "convutility.h"
#include "emsexcpt.h"
#include <sstream>

const wchar_t* CEMSURL::ms_cwszSchemeTerminator = L":";
const wchar_t* CEMSURL::ms_cwszAuthorityStart = L"//";
const wchar_t* CEMSURL::ms_cwszPathStart = L"/";
const wchar_t* CEMSURL::ms_cwszQueryStart= L"?";
const wchar_t* CEMSURL::ms_cwszFragmentStart= L"#";
const wchar_t* CEMSURL::ms_cwszRouteEndSep = L"_";


CEMSURL::CEMSURL()
{
}

CEMSURL::CEMSURL( const CEMSURL& x ) : m_owszURL( x. m_owszURL ),
										m_owszScheme( x.m_owszScheme ),
										m_owszAuthority( x.m_owszAuthority ),
										m_owszPath( x.m_owszPath ),
										m_oQuery( x.m_oQuery )
{
}

CEMSURL::CEMSURL( const wchar_t* cwszURL ) : m_owszURL( cwszURL )
{
	_Parse();
}

CEMSURL::~CEMSURL()
{
}

void 
CEMSURL::Set( const wchar_t* cwszURL )
{
	if( cwszURL )
	{
		m_owszURL = cwszURL;

		_Parse();
	}
}

std::wstring 
CEMSURL::Get()
{
	return _Generate();
}

std::wstring 
CEMSURL::GetScheme()
{
	return m_owszScheme;
}

void 
CEMSURL::SetScheme( const wchar_t* cwszScheme )
{
	if( cwszScheme )
	{
		m_owszScheme = cwszScheme;

		_Generate();
	}
}

std::wstring 
CEMSURL::GetAuthority()
{
	return m_owszAuthority;
}

void 
CEMSURL::SetAuthority( const wchar_t* cwszAuthority )
{
	if( cwszAuthority )
	{
		m_owszAuthority = cwszAuthority;

		_Generate();
	}
}

//! Get the authority portion of the URL in object format.
CEMSURLAuthority 
CEMSURL::GetAuthorityEx()
{
	CEMSURLAuthority oRet;

	oRet.Set( m_owszAuthority.c_str() );

	return oRet;
}

//! Set authority portion of the URL.
void 
CEMSURL::SetAuthority( const CEMSURLAuthority& coAuthority )
{
	std::wstring owszValue = coAuthority.Get();

	if( !owszValue.empty() )
	{
		m_owszAuthority = owszValue;

		_Generate();
	}
}

std::wstring 
CEMSURL::GetPath()
{
	return m_owszPath;
}

void 
CEMSURL::SetPath( const wchar_t* cwszPath )
{
	if( cwszPath )
	{
		m_owszPath = cwszPath;

		_Generate();
	}
}

CEMSURLQuery 
CEMSURL::GetQuery()
{
	return m_oQuery;
}

void 
CEMSURL::SetQuery( const CEMSURLQuery& coQuery )
{
	m_oQuery = coQuery;
}

CEMSURL& 
CEMSURL::operator=( const CEMSURL& crhs )
{
	m_owszURL = crhs.m_owszURL;
	m_owszScheme = crhs.m_owszScheme;
	m_owszAuthority = crhs.m_owszAuthority;
	m_owszPath = crhs.m_owszPath;
	m_oQuery = crhs.m_oQuery;

	return *this;
}

ULONG 
CEMSURL::GetSourceID()
{
	ULONG ulRet = 0;

	std::wstring wszAuthority = GetAuthority();

	if( !wszAuthority.empty() )
	{
		// Assuming it is a string of the form SourceID_DestID
		std::wstring::size_type iSepPos = wszAuthority.find( ms_cwszRouteEndSep );

		if( wszAuthority.npos == iSepPos )
		{
			CEMSLogMsgParam oParam;
			oParam.AddString( wszAuthority.c_str() );

			throw CEMSException( EMS_RESOURCE_AUTHORITY_FMT_ERROR, oParam );
		}

		std::wstring wszSrc = wszAuthority.substr( 0, iSepPos );

		ulRet = CEMSConversionUtil::ConvertToULong( wszSrc.c_str() );
	}

	return ulRet;
}

ULONG 
CEMSURL::GetDestID()
{
	ULONG ulRet = 0;

	std::wstring wszAuthority = GetAuthority();

	if( !wszAuthority.empty() )
	{
		// Assuming it is a string of the form SourceID_DestID
		std::wstring::size_type iSepPos = wszAuthority.find( ms_cwszRouteEndSep );

		if( wszAuthority.npos == iSepPos )
		{
			CEMSLogMsgParam oParam;
			oParam.AddString( wszAuthority.c_str() );

			throw CEMSException( EMS_RESOURCE_AUTHORITY_FMT_ERROR, oParam );
		}

		std::wstring wszDest = wszAuthority.substr( iSepPos + 1, wszAuthority.length() - iSepPos - 1);

		ulRet = CEMSConversionUtil::ConvertToULong( wszDest.c_str() );
	}

	return ulRet;
}

void 
CEMSURL::_Parse()
{
	m_owszScheme.erase();
	m_owszAuthority.erase();
	m_owszPath.erase();
	m_oQuery.Clear();

	if( !m_owszURL.empty() )
	{
		// First get the scheme.  It is a compulsory element.
		_ExtractScheme();

		_ExtractAuthority();
		
		_ExtractPath();

		_ExtractQuery();

		// We don't currently support the fragment.
	}
}

std::wstring 
CEMSURL::_Generate()
{
	std::wstringstream wstrmBuf;

	wstrmBuf << m_owszScheme.c_str() << ms_cwszSchemeTerminator ;
		
	wstrmBuf << ms_cwszAuthorityStart;

	if( !m_owszAuthority.empty() )
	{
		 wstrmBuf << m_owszAuthority.c_str();
	}

	if( !m_owszPath.empty() )
	{
		wstrmBuf << ms_cwszPathStart << m_owszPath.c_str();
	}

	// Add path terminator only if there is a query.
	std::wstring owszQuery = m_oQuery.Get();

	if( !owszQuery.empty() )
	{
		wstrmBuf << ms_cwszQueryStart << owszQuery.c_str();
	}

	m_owszURL = wstrmBuf.str();

	return m_owszURL;
}

void
CEMSURL::_ExtractScheme()
{
	std::wstring::size_type iPosSchemeTerm = m_owszURL.find( ms_cwszSchemeTerminator );

	if( m_owszURL.npos == iPosSchemeTerm )
	{
		throw CEMSException(EMS_DATAIO_URL_NO_SCHEME );
	}
	
	m_owszScheme = m_owszURL.substr( 0, iPosSchemeTerm );

}

void
CEMSURL::_ExtractAuthority()
{
	std::wstring::size_type iPosAuthorityStart = m_owszURL.find( ms_cwszAuthorityStart );

	std::wstring::size_type iPosAuthorityEnd = 0;

	if( m_owszURL.npos != iPosAuthorityStart )
	{
		iPosAuthorityStart += wcslen( ms_cwszAuthorityStart );

		// The authority ends with the start of the Path ("/"), Query ("?"), Fragement ("#") or end of line.
		iPosAuthorityEnd = m_owszURL.find( ms_cwszPathStart, iPosAuthorityStart  );

		if( m_owszURL.npos == iPosAuthorityEnd )
		{
			iPosAuthorityEnd = m_owszURL.find( ms_cwszQueryStart, iPosAuthorityStart  );
		}

		if( m_owszURL.npos == iPosAuthorityEnd )
		{
			iPosAuthorityEnd = m_owszURL.find( ms_cwszFragmentStart, iPosAuthorityStart );
		}

		if( m_owszURL.npos == iPosAuthorityEnd )
		{
			iPosAuthorityEnd = m_owszURL.length() - 1;
		}
	}

	if( iPosAuthorityEnd > 0 &&
		iPosAuthorityEnd > iPosAuthorityStart )
		m_owszAuthority = m_owszURL.substr( iPosAuthorityStart, iPosAuthorityEnd - iPosAuthorityStart);
}

void
CEMSURL::_ExtractPath()
{
	// First, advance past any authority start characters.
	std::wstring::size_type iPosAuthorityStart = m_owszURL.find( ms_cwszAuthorityStart );

	std::wstring::size_type iPosPathStart = 0;

	if( m_owszURL.npos != iPosAuthorityStart )
	{
		iPosPathStart = iPosAuthorityStart + wcslen( ms_cwszAuthorityStart );
	}

	std::wstring::size_type iPosPathEnd = 0;

	iPosPathStart = m_owszURL.find( ms_cwszPathStart, iPosPathStart );

	if( m_owszURL.npos != iPosPathStart )
	{
		iPosPathStart += wcslen( ms_cwszPathStart );

		// The path ends with the start of the Query ("?"), Fragement ("#") or end of line.
		iPosPathEnd = m_owszURL.find( ms_cwszQueryStart, iPosPathStart );

		if( m_owszURL.npos == iPosPathEnd )
		{
			iPosPathEnd = m_owszURL.find( ms_cwszQueryStart, iPosPathStart );
		}

		if( m_owszURL.npos == iPosPathEnd )
		{
			iPosPathEnd = m_owszURL.find( ms_cwszFragmentStart, iPosPathStart );
		}

		if( m_owszURL.npos == iPosPathEnd )
		{
			iPosPathEnd = m_owszURL.length();
		}
	}

	if( iPosPathEnd > 0 &&
		iPosPathEnd > iPosPathStart )
		m_owszPath = m_owszURL.substr( iPosPathStart, iPosPathEnd - iPosPathStart );
}

void
CEMSURL::_ExtractQuery()
{
	std::wstring::size_type iPosQueryEnd = 0;

	std::wstring::size_type iPosQueryStart = m_owszURL.find( ms_cwszQueryStart );

	if( m_owszURL.npos != iPosQueryStart )
	{
		iPosQueryStart += wcslen( ms_cwszQueryStart );

		// The path ends with a Fragement ("#") or end of line.
		iPosQueryEnd = m_owszURL.find( ms_cwszFragmentStart, iPosQueryStart );

		if( m_owszURL.npos == iPosQueryEnd )
		{
			iPosQueryEnd = m_owszURL.length();
		}
	}

	if( iPosQueryEnd > 0 &&
		iPosQueryEnd > iPosQueryStart )
		m_oQuery.Set( m_owszURL.substr( iPosQueryStart, iPosQueryEnd - iPosQueryStart ).c_str() );
}