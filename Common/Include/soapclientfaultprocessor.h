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

#ifndef __SOAP_CLIENT_FAULT_PROCESSOR_H__
#define __SOAP_CLIENT_FAULT_PROCESSOR_H__

#include "stdsoap2.h"

//! Processes faults that occur during SOAP calls.
class CEMSSOAPClientFaultProcessor
{
	public:
		CEMSSOAPClientFaultProcessor();
		~CEMSSOAPClientFaultProcessor();

		//! Converts a service generated SOAP fault into a CEMSException.
		static void HandleSoapError( struct soap* pSoap );

		//! Converts a SOAP framework fault into a CEMSException.
		static void HandleSoapError( const int ciRetCode  );

};

#endif