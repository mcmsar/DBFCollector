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

	$Log:
	$
********************************************************************/

#include "soaph.h"
#include "soapservererrorhandler.h"
#include "messagetableaccessor.h"
#include "convutility.h"


CEMSSoapServerErrorHdlr::CEMSSoapServerErrorHdlr()
{
}

CEMSSoapServerErrorHdlr::CEMSSoapServerErrorHdlr( const CEMSSoapServerErrorHdlr& x )
{
}

CEMSSoapServerErrorHdlr::~CEMSSoapServerErrorHdlr()
{
}

void 
CEMSSoapServerErrorHdlr::HandleReceiverException( struct soap* pSoap, CEMSException& rExcept )
{
	if( pSoap )
	{
		CEMSMessageTableAccessor oMsgTable;

		std::wstring owszDetail = oMsgTable.GetMessage( rExcept.GetErrCode(), rExcept.GetParam() );

		soap_receiver_fault(	pSoap, 
								CEMSConversionUtil::ConvertToHexStringA( rExcept.GetErrCode() ).c_str(), 
								CEMSConversionUtil::ConvertToString( owszDetail.c_str() ).c_str() );

		soap_send_fault( pSoap );

/*
		if (soap->version == 2) // SOAP 1.2 is used
		{
			soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail);
			soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE_ns1__myStackDataType; // stack type
			soap->fault->SOAP_ENV__Detail->fault = sp; // point to stack
			soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
		}
		else 
		{
			soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail);
			soap->fault->detail->__type = SOAP_TYPE_ns1__myStackDataType; // stack type
			soap->fault->detail->fault = sp; // point to stack
			soap->fault->detail->__any = NULL; // no other XML data
		}
*/
	}
}

void 
CEMSSoapServerErrorHdlr::HandleReceiverException( struct soap* pSoap, const DWORD dwErrInfo )
{
	if( pSoap )
	{
		soap_receiver_fault(	
				pSoap, 
				CEMSConversionUtil::HexULongToStringA( CEMSConversionUtil::ErrnoToEMSResult( dwErrInfo ) ).c_str(),
				NULL );

		soap_send_fault( pSoap );

/*
		if (soap->version == 2) // SOAP 1.2 is used
		{
			soap->fault->SOAP_ENV__Detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail);
			soap->fault->SOAP_ENV__Detail->__type = SOAP_TYPE_ns1__myStackDataType; // stack type
			soap->fault->SOAP_ENV__Detail->fault = sp; // point to stack
			soap->fault->SOAP_ENV__Detail->__any = NULL; // no other XML data
		}
		else 
		{
			soap->fault->detail = (struct SOAP_ENV__Detail*)soap_malloc(soap, sizeof(struct SOAP_ENV__Detail);
			soap->fault->detail->__type = SOAP_TYPE_ns1__myStackDataType; // stack type
			soap->fault->detail->fault = sp; // point to stack
			soap->fault->detail->__any = NULL; // no other XML data
		}
*/
	}
}