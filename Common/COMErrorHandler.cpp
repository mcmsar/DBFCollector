/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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

#include "comerrorhandler.h"
#include <comutil.h>	// For _bstr_t
#include <comdef.h>	// For _bstr_t

#include <crtdbg.h>

CEMSCOMErrorHandler::CEMSCOMErrorHandler()
{
}

CEMSCOMErrorHandler::CEMSCOMErrorHandler( const CEMSCOMErrorHandler& x )
{
}

CEMSCOMErrorHandler::~CEMSCOMErrorHandler()
{
}

void 
CEMSCOMErrorHandler::SetErrorInfo( CEMSException& oException )
{
	ICreateErrorInfo* pErrorInfo = 0;
	IErrorInfo* pError = 0;

	wchar_t* wszMsg = 0;

	try
	{
		// If an error has already been set on the thread then don't overwrite it.
		// Note that reading it clears it from the thread and therfore it must be reset by calling SetErrorInfo again.
		EMS_RESULT hr = GetErrorInfo( 0, &pError );

		if( EMS_FALSE == hr )	// No error info currently set on the thread.
		{
			hr = CreateErrorInfo( &pErrorInfo );

			if( SUCCEEDED(hr) && pErrorInfo )
			{
				std::wstring wszMessage = _GetErrorMessage( oException );
		
				if( !wszMessage.empty() )
				{
					wszMsg = new wchar_t[ wszMessage.length() + 1 ];

					if( wszMsg )
					{
						memset( wszMsg, 0, (wszMessage.length() + 1)*sizeof(wchar_t)  );
						wcsncpy( wszMsg, wszMessage.c_str(), wszMessage.length() );
				
						hr = pErrorInfo->SetDescription( wszMsg );

						delete[] wszMsg;
						wszMsg = 0;

						if( SUCCEEDED(hr) )
						{
							hr = pErrorInfo->QueryInterface( IID_IErrorInfo, (void**) &pError );
						}

					}
				}

				pErrorInfo->Release();
				pErrorInfo = 0;
			}
		}

		if( SUCCEEDED(hr) && pError )
		{
			hr = ::SetErrorInfo( 0, pError );

			pError->Release();
			pError = 0;
		}

	}
	catch( ... )
	{
		// We're already handling an error.  Don't throw this exception, just clean up.
		if( pErrorInfo )
		{
			pErrorInfo->Release();
			pErrorInfo = 0;
		}

		if( pError )
		{
			pError->Release();
			pError = 0;
		}

		if( wszMsg )
		{
			delete[] wszMsg;
			wszMsg = 0;
		}
	}
}

void 
CEMSCOMErrorHandler::SetErrorInfo( const EMS_RESULT chrError )
{
	
}

std::wstring 
CEMSCOMErrorHandler::GetErrorInfoFromThread()
{
	std::wstring wszRet;

	IErrorInfo* pError = 0;
	BSTR bszDescription = 0;

	try
	{
		EMS_RESULT hr = GetErrorInfo( 0, &pError );

		if( EMS_OK == hr )
		{
			hr = pError->GetDescription( &bszDescription );

			if( EMS_OK == hr )
			{
				wszRet = bszDescription;

				SysFreeString( bszDescription );
				bszDescription = 0;
			}
		}
	}
	catch( ... )
	{
		if( pError )
		{
			pError->Release();
			pError = 0;
		}

		if( bszDescription )
		{
			SysFreeString( bszDescription );
			bszDescription = 0;
		}

		// Don't throw another exception since we are already dealing with one.
	}

	return wszRet;
}

void 
CEMSCOMErrorHandler::SetErrorInfo( const wchar_t* cwszErrorInfo )
{
	_ASSERTE( cwszErrorInfo );

	ICreateErrorInfo* pErrorInfo = 0;
	IErrorInfo* pError = 0;

	try
	{
		if( cwszErrorInfo )
		{
			EMS_RESULT hr = CreateErrorInfo( &pErrorInfo );
			
			if( SUCCEEDED(hr) )
			{
				hr = pErrorInfo->SetDescription( _bstr_t( cwszErrorInfo ) );

				if( SUCCEEDED(hr) )
				{
					hr = pErrorInfo->QueryInterface( IID_IErrorInfo, (void**) &pError );
				}

				if( SUCCEEDED(hr) && pError )
				{
					hr = ::SetErrorInfo( 0, pError );

					pError->Release();
					pError = 0;
				}

				pErrorInfo->Release();
				pErrorInfo = 0;
			}
		}
	}
	catch( ... )
	{
		if( pErrorInfo )
		{
			pErrorInfo->Release();
			pErrorInfo = 0;
		}

		if( pError )
		{
			pError->Release();
			pError = 0;
		}

		// Don't throw an exception since we're already dealing with one.
	}
}

std::wstring 
CEMSCOMErrorHandler::_GetErrorMessage( CEMSException& oException )
{
	return m_oMsgTable.GetMessage( oException.GetErrCode(), oException.GetParam() );
}

