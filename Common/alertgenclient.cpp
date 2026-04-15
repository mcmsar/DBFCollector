/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#include "alertgenclient.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "comerrorhandler.h"
#include "generalmsgs.h"

CEMSAlertGenClient::CEMSAlertGenClient()
{
}

CEMSAlertGenClient::CEMSAlertGenClient( const CEMSAlertGenClient& x )
{
}

CEMSAlertGenClient::~CEMSAlertGenClient()
{
}

void 
CEMSAlertGenClient::GenerateAlerts(	const unsigned long culDestID,
								const unsigned long culDestinations,
								const unsigned long* caulDestinationIDs,
								const unsigned long culLocations,
								const EMSLOCATIONKEY* caLocations)
{
	IEMSGatewayConnection* pGtwyCon = 0;
	IEMSAlertGenGtwy* pGtwyAG = 0;

	try
	{
		pGtwyCon = _Connect();

		if( !pGtwyCon )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pGtwyCon->QueryInterface( IID_IEMSAlertGenGtwy, (void**) &pGtwyAG );

		if( FAILED(hr) )
		{

			THROW_RUNTIME_EXCEPTION_WITH_MSG( hr );
		}

		pGtwyCon->Release();
		pGtwyCon = 0;

		EMSGATEWAYTOKEN	secToken;
		memset( &secToken, 0, sizeof(EMSGATEWAYTOKEN) );

		_GetSecurityToken( _GetCallerID(), culDestID, secToken );

		hr = pGtwyAG->GenerateAlerts( culDestID, &secToken, culDestinations, const_cast<ULONG*>(caulDestinationIDs),
							culLocations, const_cast<EMSLOCATIONKEY*>(caLocations) );


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

		pGtwyAG->Release();
		pGtwyAG = 0;


	}
	catch( ... )
	{
		if( pGtwyCon )
		{
			pGtwyCon->Release();
			pGtwyCon = 0;
		}

		if( pGtwyAG )
		{
			pGtwyAG->Release();
			pGtwyAG = 0;
		}

		throw;
	}
}