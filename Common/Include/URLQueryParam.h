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

#ifndef __EMS_URL_QUERY_PARAM_H__
#define __EMS_URL_QUERY_PARAM_H__

#include "aobjbase.h"
#include <string>

//! @class CEMSURLQueryParam
//! Represents a parameter within the query portion of an URL.
class CEMSURLQueryParam : public CApiObjBase
{
	public:
		CEMSURLQueryParam();
		CEMSURLQueryParam( const CEMSURLQueryParam& x );
		virtual ~CEMSURLQueryParam();

		//! @fn void Set( const wchar_t* cwszParameter )
		//! Set the string specifying a parameter
		void Set( const wchar_t* cwszParameter );

		//! @fn std::wstring Get()
		//! Gets the Query parameter string.
		std::wstring Get();

		//! @fn void Set( const wchar_t* cwszLHS, const wchar_t* cwszRHS )
		//! Set a parameter as a LHS and RHS pair.
		void Set( const wchar_t* cwszLHS, const wchar_t* cwszRHS );

		//! @fn std::wstring GetLHS()
		//! Get LHS of the parameter expression.
		std::wstring GetLHS();

		//! @fn std::wstring GetValue()
		//! Get the value of the parameter (i.e., its RHS).
		std::wstring GetValue();

		//! @fn CEMSURLQueryParam& operator=( const CEMSURLQueryParam& crhs )
		//! Overloaded equals operator.
		CEMSURLQueryParam& operator=( const CEMSURLQueryParam& crhs );

		//! Determine whether the parameter is empty.  This is the case when
		//! the LHS of the expression is empty.
		bool IsEmpty() { return m_owszLHS.empty(); }

	private:
		void _Parse();
		std::wstring _Generate();

	private:
		//! @var std::wstring m_owszQueryParam
		//! The string containing the complete URL Query Parameter.
		std::wstring	m_owszQueryParam;

		std::wstring	m_owszLHS;
		std::wstring	m_owszRHS;

	private:
		static const wchar_t* ms_cwszSeparator;

};

#endif