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

#ifndef __URL_AUTHORITY_H__
#define __URL_AUTHORITY_H__

#include "aobjbase.h"
#include <string>

//! Represents the Authority portion of an URL.  It does not support the userinfo portion of 
//! the Authority, as described in the W3C standard.
class CEMSURLAuthority : public CApiObjBase
{
	public:
		CEMSURLAuthority();
		CEMSURLAuthority( const CEMSURLAuthority& x );
		virtual ~CEMSURLAuthority();

		//! Set the host name.
		void SetHost( const wchar_t* cwszValue );

		//! Retrieve the host name.
		std::wstring GetHost() const;

		//! Set the port number.  This is an optional component of the authority.
		void SetPort( const wchar_t* cwszValue );

		//! Get the port number.
		std::wstring GetPort() const;

		//! Get the string representation of the Authority.
		std::wstring Get() const;

		//! Parse and store a string representation of the Authority.
		void Set( const wchar_t* cwszValue );

	private:
		std::wstring m_owszHost;
		std::wstring m_owszPort;

	private:
		static const wchar_t* ms_cwszPortDelimiter;
};

#endif