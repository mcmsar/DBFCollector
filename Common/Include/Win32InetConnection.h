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

#ifndef __WIN32_INET_CONNECTION__
#define __WIN32_INET_CONNECTION__

#include <windows.h>
#include <wininet.h>

//! This class is used to initialize the WinInet subystem prior to an application's use.
class CEMSWin32InetConnection
{
	public:
		~CEMSWin32InetConnection();

		//! Checks whether an Internet connection is available using the given URL.
		static bool CheckConnection( const wchar_t* cwszTestURL );

		//! Initialize the WinInet subsystem.  This must be called prior to executing
		//! any other WinInet function calls.
		static bool Open( const wchar_t* cwszAgent, const DWORD cdwAccessType,
					const wchar_t* cwszProxyName, const wchar_t* cwszProxyBypass,
					const DWORD cdwFlags );

		//! Open an URL.  The caller must close the handle when finished.
		static HINTERNET OpenURL( const wchar_t* cwszURL );

		//! Release the underlying Internet connection handle.  Applications should call this
		//! method prior to shutdown.
		static bool Close();

		//! Retrieve a handle to the Internet connection.  The caller must not Release the
		//! handle.
		static const HINTERNET GetConnection();

	protected:
		// Can't be instantiated.
		CEMSWin32InetConnection();
		CEMSWin32InetConnection( const CEMSWin32InetConnection& x );
		

	private:
		static HINTERNET	ms_hConnection;

};

#endif