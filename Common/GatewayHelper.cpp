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

	$Log$
********************************************************************/

#include "gatewayhelper.h"
#include "emsexcpt.h"
#include "messages.h"
#include "comerrorhandler.h"
#include "convutility.h"
#include "emstokenmgr.h"

CEMSGatewayHelper::CEMSGatewayHelper() : m_ulCallerID(0)
{
}

CEMSGatewayHelper::CEMSGatewayHelper( const CEMSGatewayHelper& x ) : m_ulCallerID( x.m_ulCallerID )
{
}

CEMSGatewayHelper::~CEMSGatewayHelper()
{
}

void 
CEMSGatewayHelper::GetData( ULONG ulDestID, EMSDALCACHEID* pCacheID, const ULONG culMaxRecords,
						const bool cbReturnDescriptor, const wchar_t* cwszConnection,
						const wchar_t* cwszSQL, bool* pbCacheOverflowed, 
						ULONG* pulTotalRecords, ULONG* pulRecordSize,
						ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, 
						ULONG* pulDataSize, unsigned char** pabyData )
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSDALGtwy* pGtwyDAL = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSDALGtwy, (void**) &pGtwyDAL );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( m_ulCallerID, ulDestID, secToken );

		boolean bCacheOverFlowed;

		hr = pGtwyDAL->GetData( ulDestID, &secToken, pCacheID, culMaxRecords, cbReturnDescriptor,
						0, pulTotalRecords, pulRecordSize, &bCacheOverFlowed, cwszConnection, 
						cwszSQL, pulFields, paFields, pulDataSize, pabyData );


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

		*pbCacheOverflowed = bCacheOverFlowed ? true : false;

		pGtwyDAL->Release();
		pGtwyDAL = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyDAL )
		{
			pGtwyDAL->Release();
			pGtwyDAL = 0;
		}

		throw;
	}
}

IEMSGatewayConnection* 
CEMSGatewayHelper::_Connect()
{
	IEMSGatewayConnection* pRet = 0;

	try
	{
		// No caching.  This may be less efficient, but prevents situation where the Gateway service
		// is shutdown while we hold a connection to it.
		EMS_RESULT hr = CoCreateInstance( CLSID_EMSGateway2, 0, CLSCTX_ALL, IID_IEMSGatewayConnection,
											(void**) &pRet );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		if( 0 == m_ulCallerID )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_GENERAL_NO_CALLER_ID );
		}

		EMSGATEWAYADDRESS addrFrom;
		memset( &addrFrom, 0, sizeof(EMSGATEWAYADDRESS) );
		addrFrom.type = EMSGatewayCSAddress;
		sprintf( (char*)addrFrom.cAddress, "%u", m_ulCallerID );
		
		hr = pRet->Connect( &addrFrom, 0 );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSGatewayHelper::_GetSecurityToken( const ULONG culSrcID, const ULONG culDestID, EMSGATEWAYTOKEN& secToken )
{
	CEMSTokenMgr oTokenManager;

	EMS_RESULT hr = oTokenManager.GetToken( culDestID, culSrcID, &secToken );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
	}
}