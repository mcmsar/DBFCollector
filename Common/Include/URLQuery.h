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

#ifndef __EMS_URL_QUERY_H__
#define __EMS_URL_QUERY_H__

#include "aobjbase.h"
#include "urlqueryparam.h"
#include "objectlist.h"

#include "objectmap.h"

#include <string>

//! @class CEMSURLQuery
//! Represents the query portion of an URL.
class CEMSURLQuery : public CApiObjBase
{
	public:
		CEMSURLQuery();
		CEMSURLQuery( const CEMSURLQuery& x );
		virtual ~CEMSURLQuery();

		//! @fn void Set( const wchar_t* cwszQuery )
		//! Set the string specifying the query portion of the URL.
		void Set( const wchar_t* cwszQuery );

		//! @fn std::wstring Get()
		//! Gets the URL Query string.
		std::wstring Get();

		//! Retrieve the % decoded query string.
		std::wstring GetDecoded();

		//! @fn void AddParam( CEMSURLQueryParam& oQueryParam )
		//! Add a query parameter.
		void AddParam( CEMSURLQueryParam& oQueryParam );

		//! @fn CEMSURLQueryParam GetParam( const wchar_t* cwszLHS )
		//! Retrieve the query parameter with the given LHS.  If not found, an
		//! object is returned with empty LHS and RHS values.
		CEMSURLQueryParam GetParam( const wchar_t* cwszLHS );

		//! @fn CEMSObjectList<CEMSQueryParam> GetParams()
		//! Retrieve the list of all query parameters.
		CEMSObjectList<CEMSURLQueryParam> GetParams();

		//! @fn void Clear()
		//! Clear all parameter data.
		void Clear();

		//! CEMSURLQuery& operator=( const CEMSURLQuery& crhs )
		//! Overloaded equals operator.
		CEMSURLQuery& operator=( const CEMSURLQuery& crhs );

	private:
		void _Parse();
		std::wstring _Generate();

	private:
		//! @var std::wstring m_owszQuery
		//! The string containing the complete URL Query.
		std::wstring		m_owszQuery;

		CEMSObjectMap<std::wstring,CEMSURLQueryParam>	m_mapParams;

	private:
		static const wchar_t* ms_cwszParamSeparator;

};

#endif