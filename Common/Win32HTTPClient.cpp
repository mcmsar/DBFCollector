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

#include "win32httpclient.h"
#include "win32inetconnection.h"
#include "arrayhelper.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "httpresponse.h"

CEMSWin32HTTPClient::CEMSWin32HTTPClient()
{
}

CEMSWin32HTTPClient::CEMSWin32HTTPClient( const CEMSWin32HTTPClient& x )
{
}

CEMSWin32HTTPClient::~CEMSWin32HTTPClient()
{
}

CEMSHTTPResponse*
CEMSWin32HTTPClient::Open( const wchar_t* cwszURL )
					
{
	CEMSHTTPResponse* pRet = 0;

	if( NULL == CEMSWin32InetConnection::GetConnection() )
	{
		bool bRet = CEMSWin32InetConnection::Open( L"CEMSWin32HTTPClient", 
										INTERNET_OPEN_TYPE_PRECONFIG,
										NULL,
										NULL,
										0 );

		if( !bRet )
		{
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}
										
	}

	HINTERNET hURL = CEMSWin32InetConnection::OpenURL( cwszURL );

	if( NULL == hURL )
	{
		DWORD dwWin32Err = GetLastError();
		throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
	}

	// Now grab the results.
	pRet = _GetResponse( hURL );

	if( NULL != hURL )
	{
		InternetCloseHandle( hURL );
		hURL = NULL;
	}

	return pRet;
}

CEMSHTTPResponse*
CEMSWin32HTTPClient::Open( const wchar_t* cwszURL, 
						   const wchar_t* cwszProxyName, 
						   const wchar_t* cwszProxyBypass )
					
{
	CEMSHTTPResponse* pRet = 0;

	if( NULL == CEMSWin32InetConnection::GetConnection() )
	{
		bool bRet = CEMSWin32InetConnection::Open( L"CEMSWin32HTTPClient", 
												   INTERNET_OPEN_TYPE_PROXY,
												   cwszProxyName,
												   cwszProxyBypass,
												   0 );

		if( !bRet )
		{
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}
										
	}

	HINTERNET hURL = CEMSWin32InetConnection::OpenURL( cwszURL );

	if( NULL == hURL )
	{
		DWORD dwWin32Err = GetLastError();
		throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
	}

	// Now grab the results.
	pRet = _GetResponse( hURL );

	if( NULL != hURL )
	{
		InternetCloseHandle( hURL );
		hURL = NULL;
	}

	return pRet;
}

/*HINTERNET 
CEMSWin32HTTPClient::_OpenRequest( const HINTERNET chConn, const wchar_t* cwszVerb, 
							const wchar_t* cwszURL,	const wchar_t* cwszVersion, 
							const wchar_t* cwszReferer,	const wchar_t** cawszAcceptTypes, 
							const DWORD cdwFlags, const DWORD cdwContext )
{
	HINTERNET hRet = NULL;

	hRet = HttpOpenRequestW( chConn, cwszVerb, cwszURL, cwszVersion, cwszReferer,
				cawszAcceptTypes, cdwFlags, cdwContext );

	if( NULL == hRet )
	{
		DWORD dwWin32Err = GetLastError();
		throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
	}

	return hRet;
}

bool 
CEMSWin32HTTPClient::_SendRequest( const HINTERNET chRequest )
{
	bool bRet = false;

	if( NULL != chRequest )
	{
		BOOL bCheck = HttpSendRequest( chRequest, NULL, 0, NULL, 0 );

		if( !bCheck )
		{
			DWORD dwWin32Err = GetLastError();
			throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
		}

		bRet = true;
	}

	return bRet;
}
*/

CEMSHTTPResponse*
CEMSWin32HTTPClient::_GetResponse( const HINTERNET chRequest )
{
	CEMSHTTPResponse* pRet = 0;

	if( NULL != chRequest )
	{
		const DWORD cdwBytesToRead = 8192;
		BYTE abyData[cdwBytesToRead];
		DWORD dwBytesRead = 0;
		BOOL bRet = TRUE;

		DWORD dwResponseSize = 0;
		BYTE* abyResponse = NULL;

		try
		{
			do
			{
				memset( abyData, 0, cdwBytesToRead );

				bRet = InternetReadFile( chRequest, abyData, cdwBytesToRead, &dwBytesRead );

				if( bRet && (dwBytesRead > 0 ) )
				{
					CEMSArrayHelper::Concatenate( abyResponse, dwResponseSize, abyData, dwBytesRead );
				}

			} while( bRet && (dwBytesRead > 0 ) );

			if( !bRet )
			{
				DWORD dwWin32Err = GetLastError();
				throw CEMSException( CEMSConversionUtil::ErrnoToEMSResult( dwWin32Err ) );
			}

			if( dwResponseSize > 0 )
			{
				pRet = new CEMSHTTPResponse;

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pRet->SetResponse( dwResponseSize, abyResponse );
			}

			if( abyResponse )
			{
				delete[] abyResponse;
				abyResponse = 0;
			}
		}
		catch( ... )
		{
			if( abyResponse )
			{
				delete[] abyResponse;
				abyResponse = 0;
			}

			if( pRet )
			{
				pRet->Release();
				pRet = 0;
			}

			throw;
		}

	}

	return pRet;
}