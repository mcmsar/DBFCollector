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

#ifndef __SOAP_SERVER_ERROR_HANDLER__
#define __SOAP_SERVER_ERROR_HANDLER__

#include "emsexcpt.h"

//! Handles exceptions on Soap Servers / Web Services by ensuring that error information
//! is made available for return to the caller.
class CEMSSoapServerErrorHdlr
{
	public:
		CEMSSoapServerErrorHdlr();
		CEMSSoapServerErrorHdlr( const CEMSSoapServerErrorHdlr& x );
		~CEMSSoapServerErrorHdlr();

		//! Handle a server-responsible exception.
		static void HandleReceiverException( struct soap* pSoap, CEMSException& rExcept );

		//! Handle a server-responsible exception.
		static void HandleReceiverException( struct soap* pSoap, const DWORD dwErrInfo );
};

#endif
