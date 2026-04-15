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
#pragma warning(disable:4786)

#include "win32inetconnection.h"
#include "emsexcpt.h"
#include "convutility.h"
//#include "emsurl.h"

HINTERNET CEMSWin32InetConnection::ms_hConnection = NULL;

CEMSWin32InetConnection::CEMSWin32InetConnection()
{
}

CEMSWin32InetConnection::CEMSWin32InetConnection( const CEMSWin32InetConnection& x )
{
	// No copying.  The member data is static.
}

CEMSWin32InetConnection::~CEMSWin32InetConnection()
{
	// No releasing.  The member data is static.
}

bool 
CEMSWin32InetConnection::CheckConnection( const wchar_t* cwszTestURL )
{
	bool bRet = false;

	BOOL bCheck = InternetCheckConnectionW( cwszTestURL, FLAG_ICC_FORCE_CONNECTION , 0 );

	if( TRUE == bCheck )
		bRet = true;
	else
		bRet = false;

	return bRet;
}

bool 
CEMSWin32InetConnection::Open( const wchar_t* cwszAgent, const DWORD cdwAccessType,
			const wchar_t* cwszProxyName, const wchar_t* cwszProxyBypass,
			const DWORD cdwFlags )
{
	bool bRet = false;

	if( NULL == ms_hConnection )
	{
		ms_hConnection = InternetOpenW( cwszAgent, cdwAccessType, cwszProxyName,
							cwszProxyBypass, cdwFlags );

		if( NULL == ms_hConnection )
		{
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}
	}

	if( NULL != ms_hConnection )
		bRet = true;

	return bRet;
}

HINTERNET 
CEMSWin32InetConnection::OpenURL( const wchar_t* cwszURL )
{
	HINTERNET hRet = NULL;

	if( cwszURL )
	{
//		CEMSURL oUrl( cwszURL );
//		std::wstring owszServer = oUrl.GetAuthority();

		hRet = InternetOpenUrlW( GetConnection(), cwszURL, NULL, 0, INTERNET_FLAG_RELOAD, 0 );

		if( NULL == hRet )
		{
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}

	}

	return hRet;
}

bool 
CEMSWin32InetConnection::Close()
{
	bool bRet = true;

	if( NULL != ms_hConnection )
	{
		BOOL bCheck = InternetCloseHandle( ms_hConnection );

		if( !bCheck )
		{
			bRet = false;
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}
		
		ms_hConnection = NULL;

	}

	return bRet;
}

const HINTERNET 
CEMSWin32InetConnection::GetConnection()
{
	return ms_hConnection;
}