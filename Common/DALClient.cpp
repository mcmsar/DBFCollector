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

#include "dalclient.h"
#include "emsexcpt.h"
#include "comerrorhandler.h"
#include "convutility.h"

CEMSDALClient::CEMSDALClient()
{
}

CEMSDALClient::CEMSDALClient( const CEMSDALClient& x )
{
}

CEMSDALClient::~CEMSDALClient()
{
}

void 
CEMSDALClient::GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords,
						const bool cbReturnDescriptor, const wchar_t* cwszConnection,
						const wchar_t* cwszSQL, bool* pbCacheOverflowed, 
						ULONG* pulTotalRecords, ULONG* pulRecordSize,
						ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, 
						ULONG* pulDataSize, unsigned char** pabyData )
{
	IEMSDALVariable* pDAL = 0;

	try
	{
		pDAL = _Connect();

		if( !pDAL )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		boolean bCacheOverFlowed;

		EMS_RESULT hr = pDAL->GetData( pCacheID, culMaxRecords, cbReturnDescriptor,
						0, pulTotalRecords, pulRecordSize, &bCacheOverFlowed, cwszConnection, 
						cwszSQL, pulFields, paFields, pulDataSize, pabyData );


		if( FAILED(hr) )
		{
			CEMSCOMErrorHandler oComError;
			
			CEMSLogMsgParam oLogParam;
			oLogParam.AddString( CEMSConversionUtil::HexULongToStringW( hr ).c_str() );
			oLogParam.AddString( oComError.GetErrorInfoFromThread().c_str() );
#pragma message("Get a proper exception code and message here")
//			throw CEMSException( EMS_GENERAL_GATEWAY_CALL_FAILURE, oLogParam );
			THROW_RUNTIME_EXCEPTION( hr );
		}

		*pbCacheOverflowed = bCacheOverFlowed ? true : false;

		pDAL->Release();
		pDAL = 0;


	}
	catch( ... )
	{
		if( pDAL )
		{
			pDAL->Release();
			pDAL = 0;
		}

		throw;
	}
}

IEMSDALVariable* 
CEMSDALClient::_Connect()
{
	IEMSDALVariable* pRet = 0;

	try
	{
		// No caching.  This may be less efficient, but prevents situation where the DAL service
		// is shutdown while we hold a connection to it.
		EMS_RESULT hr = CoCreateInstance( CLSID_EMSDAL, 0, CLSCTX_ALL, IID_IEMSDALVariable,
											(void**) &pRet );

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
