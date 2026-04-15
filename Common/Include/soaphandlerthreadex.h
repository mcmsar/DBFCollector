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

//! This file is based on the soaphandlerthread.h found in the MTL/SOAP Server project.

#ifndef __SOAP_HANDLER_THREADEX_H__
#define	__SOAP_HANDLER_THREADEX_H__

#include "emsthread.h"

#ifdef WIN32
//#include "logclient.h"
#endif

class CEMSSOAPHandlerThreadEx : public CEMSThread
#ifdef WIN32
//							, public CEMSLogClient
#endif

{
	public:
		CEMSSOAPHandlerThreadEx();
		virtual ~CEMSSOAPHandlerThreadEx();

		void SetSocket( int iSocket ) { m_iSocket = iSocket; }
		
		//! Soap listeners should prefer this method rather than SetSocket to process inbound
		//! soap requests.  By using this method, features like SSL will be supported because
		//! the runtime will have been configured by the caller.
		//! Callers should pass in pointers to structures created using soap_copy or soap_new and
		//! assume that this class takes ownership of the structure, including management of its
		//! lifetime.
		void SetSoap( struct soap* pSoap );
		
		bool IsRunning() { return m_bIsRunning; }

		void RegisterGetHandler( void* pfnGetHandler );

	protected:
		virtual void run();

	private:
		void _ReleaseSoap();

	private:
		struct soap*	m_pSoap;
		int				m_iSocket;
		bool			m_bIsRunning;
		void*			m_pfnGetHandler;
};

#endif // __SOAP_HANDLER_THREADEX_H__