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

//! This file is based on the soaplistenerthread.cpp found in the MTL/SOAP Server project.

#ifndef __SOAP_LISTENER_THREADEX_H__
#define __SOAP_LISTENER_THREADEX_H__

#include "emsthread.h"
#include "soaph.h"

//! Thread class used for listening for incoming SOAP message requests.  It dispatches
//! received requests to available handler objects.
class CEMSSOAPListenerThreadEx : public CEMSThread
{
	public:
		CEMSSOAPListenerThreadEx();
		CEMSSOAPListenerThreadEx( const CEMSSOAPListenerThreadEx& x );
		virtual ~CEMSSOAPListenerThreadEx();

		void Init( struct soap* pSoap );
		void Shutdown();
		void Start();

		void SetNumHandlerThreads( const long clNum ) { m_lNumHandlerThreads; }
		long GetNumHandlerThreads() const { return m_lNumHandlerThreads; }

		bool IsRunning() const { return m_bIsRunning; }

		void RegisterGetHandler( void* pfnGetHandler ) { m_pfnGetHandler = pfnGetHandler; }

		void SetUseSSL( const bool cbValue ) { m_bUseSSL = cbValue; }
		bool GetUseSSL() const { return m_bUseSSL; }

	protected:
		virtual void run();

	private:
		long _GetNumHandlerThreads();

	private:
		struct soap*	m_pSoap;
		bool			m_bShutdownFlag;
		long			m_lNumHandlerThreads;
		bool			m_bIsRunning;
		void*			m_pfnGetHandler;
		bool			m_bUseSSL;

};

#endif	// __SOAP_LISTENER_THREADEX_H__