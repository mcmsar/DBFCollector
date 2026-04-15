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

#include "lpcclient.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "comerrorhandler.h"
#include "generalmsgs.h"

CEMSLPCClient::CEMSLPCClient()
{
}

CEMSLPCClient::CEMSLPCClient( const CEMSLPCClient& x )
{
}

CEMSLPCClient::~CEMSLPCClient()
{
}

void 
CEMSLPCClient::InitManualProcessing(const unsigned long culDestID,
									wchar_t* wszWhereClause,
									unsigned long& rulSessionID,
									unsigned long& rulRecords,
									EMSCALIB406DATA*& raBeaconData)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->InitManualProcessing( culDestID, &secToken, wszWhereClause, 
							&rulSessionID, &rulRecords, &raBeaconData );


		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}

void 
CEMSLPCClient::RemoveDataFromSet(	const unsigned long culDestID,
									const unsigned long culSessionID,
									const unsigned long culKeys,
									unsigned long* aulKeys)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->RemoveDataFromSet( culDestID, &secToken, 
											culSessionID, culKeys, aulKeys );


		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}
        
void 
CEMSLPCClient::Process406(	const unsigned long culDestID,
					const unsigned long culSessionID,
					wchar_t* wszControlFilename,
					unsigned long& rulResults,
					EMSLOCATE*& raLocations)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->Process406( culDestID, &secToken, 
									culSessionID, wszControlFilename, &rulResults, &raLocations );


		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}

void 
CEMSLPCClient::CancelSession(	const unsigned long culDestID,
				    const unsigned long culSessionID)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->CancelSession( culDestID, &secToken, culSessionID );

		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}

void 
CEMSLPCClient::GetControlFilenames(	const unsigned long culDestID,
							unsigned long& rulCount,
							wchar_t**& rawszControlFilenames)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->GetControlFilenames( culDestID, &secToken, &rulCount, &rawszControlFilenames );

		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}

void 
CEMSLPCClient::InitManual(	const unsigned long culDestID,
					const wchar_t* cwszWhereClause,
					const EMSMANUALPROCESSINGMODE ceProcessingMode,
					unsigned long& rulSessionID,
					unsigned long& rulRecords,
					EMSVARIANTRECORD*& raData)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSLocationGtwy* pGtwyLPC = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSLocationGtwy, (void**) &pGtwyLPC );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyLPC->InitManual( culDestID, &secToken, cwszWhereClause, ceProcessingMode,
								&rulSessionID, &rulRecords, &raData );

		if( FAILED(hr) )
		{
			// Is it a COM error?
			CEMSCOMErrorHandler oComError;
			std::wstring	wstrError = oComError.GetErrorInfoFromThread();
			if ( !wstrError.empty() )
			{			
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
				oLogParam.AddString( wstrError.c_str() );

				throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			}
			else
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
			}
		}

		pGtwyLPC->Release();
		pGtwyLPC = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyLPC )
		{
			pGtwyLPC->Release();
			pGtwyLPC = 0;
		}

		throw;
	}
}