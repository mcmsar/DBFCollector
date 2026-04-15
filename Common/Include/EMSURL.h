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

#ifndef __EMS_URL_H__
#define __EMS_URL_H__

#include "aobjbase.h"
#include "urlquery.h"
#include "urlauthority.h"
#include <string>

//! @class CEMSURL
//! Represents an URL.  An URL is composed of 4 main parts:  a scheme, authority, path and query.
class CEMSURL : public CApiObjBase
{
	public:
		CEMSURL();
		CEMSURL( const CEMSURL& x );
		CEMSURL( const wchar_t* cwszURL );
		virtual ~CEMSURL();

		//! @fn void Set( const wchar_t* cwszURL )
		//! Set the string specifying the URL.
		void Set( const wchar_t* cwszURL );

		//! @fn std::wstring GetURLString()
		//! Gets the URL string.
		std::wstring Get();

		//! @fn std::wstring GetScheme()
		//! Retrieve the scheme portion of the URL.
		std::wstring GetScheme();

		//! @fn void SetScheme( const wchar_t* cwszScheme )
		//! Set the scheme portion of the URL.
		void SetScheme( const wchar_t* cwszScheme );

		//! @fn std::wstring GetAuthority()
		//! Get the authority portion of the URL.
		std::wstring GetAuthority();

		//! @fn void SetAuthority( const wchar_t* cwszAuthority )
		//! Set the authority portion of the URL.
		void SetAuthority( const wchar_t* cwszAuthority );

		//! Get the authority portion of the URL in object format.
		CEMSURLAuthority GetAuthorityEx();

		//! Set authority portion of the URL.
		void SetAuthority( const CEMSURLAuthority& coAuthority );

		//! @fn std::wstring GetPath()
		//! Get the path portion of the URL.
		std::wstring GetPath();

		//! @fn void SetPath( const wchar_t* cwszPath )
		//! Set the path portion of the URL.
		void SetPath( const wchar_t* cwszPath );

		//! @fn CEMSURLQuery GetQuery()
		//! Get the query portion of the URL.
		CEMSURLQuery GetQuery();

		//! @fn void SetQuery( const CEMSURLQuery& coQuery )
		//! Set the query portion of the URL.
		void SetQuery( const CEMSURLQuery& coQuery );

		//! @fn CEMSURL& operator=( const CEMSURL& crhs )
		//! Overloaded equals operator.
		CEMSURL& operator=( const CEMSURL& crhs );

		//! Get the identifier of the source.  The returned value is a LUT
		//! Identifier.
		ULONG GetSourceID();

		//! Get the identifier of the destination.  The returned value is a LUT
		//! Identifier.
		ULONG GetDestID();


	private:
		void _Parse();

		void _ExtractScheme();

		void _ExtractAuthority();

		void _ExtractPath();

		void _ExtractQuery();

		std::wstring _Generate();

	private:
		//! @var std::wstring m_owszURL
		//! The string containing the complete URL.
		std::wstring		m_owszURL;

		std::wstring		m_owszScheme;
		std::wstring		m_owszAuthority;
		std::wstring		m_owszPath;
		CEMSURLQuery		m_oQuery;

	private:
		static const wchar_t* ms_cwszSchemeTerminator;
		static const wchar_t* ms_cwszAuthorityStart;
		static const wchar_t* ms_cwszPathStart;
		static const wchar_t* ms_cwszQueryStart;
		static const wchar_t* ms_cwszFragmentStart;

	public:
		static const wchar_t* ms_cwszRouteEndSep;

};

#endif