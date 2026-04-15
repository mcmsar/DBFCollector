/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __WIN32_HTTP_CLIENT_H__
#define __WIN32_HTTP_CLIENT_H__

#include <windows.h>
#include <wininet.h>

class CEMSHTTPResponse;

//! A client for issuing HTTP requests and returning responses.
class CEMSWin32HTTPClient
{
	public:
		CEMSWin32HTTPClient();
		CEMSWin32HTTPClient( const CEMSWin32HTTPClient& x );
		~CEMSWin32HTTPClient();

		//! Execute the request synchronously and return results.
		CEMSHTTPResponse* Open( const wchar_t* cwszVerb );
		CEMSHTTPResponse* Open( const wchar_t* cwszVerb, 
								const wchar_t* cwszProxyName, 
								const wchar_t* cwszProxyBypass );

	public:
		const wchar_t* ms_cwszVerbGet;
		const wchar_t* ms_cwszVerbPost;
		const wchar_t* ms_cwszVerbPut;

	private:
//		HINTERNET _OpenRequest( const HINTERNET chConn, const wchar_t* cwszVerb, 
//							const wchar_t* cwszURL,	const wchar_t* cwszVersion, 
//							const wchar_t* cwszReferer,	const wchar_t** cawszAcceptTypes, 
//							const DWORD cdwFlags, const DWORD cdwContext );

//		bool _SendRequest( const HINTERNET chRequest );

		CEMSHTTPResponse* _GetResponse( const HINTERNET chRequest );
};

#endif