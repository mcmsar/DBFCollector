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

//! This file is based on the soaphandlerthread.cpp found in the MTL/SOAP Server project.

#include "soaphandlerthreadex.h"
#include "soaph.h"
#include "emsexcpt.h"
#include "soapservererrorhandler.h"
#include "httpget.h"

CEMSSOAPHandlerThreadEx::CEMSSOAPHandlerThreadEx() : 
#ifdef WIN32
//	CEMSLogClient( L"CEMSSOAPHandlerThreadEx" ), 
#endif
		m_pSoap(NULL), m_iSocket(0), m_bIsRunning(false), m_pfnGetHandler(NULL)
{
	m_pSoap = soap_new();

#ifdef DEBUG
	char szLogFile[ 128 ];
	sprintf( szLogFile, "recv_%d.txt", m_pSoap );
	soap_set_recv_logfile( m_pSoap, szLogFile );

	sprintf( szLogFile, "sent_%d.txt", m_pSoap );
	soap_set_sent_logfile( m_pSoap, szLogFile );

	sprintf( szLogFile, "test_%d.txt", m_pSoap );
	soap_set_test_logfile( m_pSoap, szLogFile );
#endif

}

CEMSSOAPHandlerThreadEx::~CEMSSOAPHandlerThreadEx()
{
	_ReleaseSoap();

	m_pfnGetHandler = NULL;
}

void 
CEMSSOAPHandlerThreadEx::SetSoap( struct soap* pSoap )
{
	if( m_bIsRunning )
	{
		THROW_RUNTIME_EXCEPTION( EMS_ALREADY_OPEN );
	}

	_ReleaseSoap();

	m_pSoap = pSoap;
}

void 
CEMSSOAPHandlerThreadEx::RegisterGetHandler( void* pfnGetHandler )
{
	if( !m_pSoap )
	{
		m_pSoap = soap_new();
	}

	if( m_pSoap )
	{
		if( pfnGetHandler )
		{
			m_pfnGetHandler = pfnGetHandler;

			if(soap_register_plugin_arg( m_pSoap, http_get, m_pfnGetHandler))
				soap_print_fault(m_pSoap, stderr);
		}
	}
}

void 
CEMSSOAPHandlerThreadEx::run()
{
	if( !m_pSoap )
	{
		m_pSoap = soap_new();
	}

	if( m_pSoap )
	{
		m_bIsRunning = true;

		if(  m_iSocket > 0 ) 
			m_pSoap->socket = m_iSocket;

		if( m_pfnGetHandler )
		{
			if(soap_register_plugin_arg( m_pSoap, http_get, m_pfnGetHandler))
				soap_print_fault(m_pSoap, stderr);
		}

		try
		{
			soap_serve( m_pSoap );	// process RPC skeletons
		}
		catch( CEMSException& e )
		{
			CEMSSoapServerErrorHdlr::HandleReceiverException( m_pSoap, e );
		}
		catch( ... )
		{
			CEMSSoapServerErrorHdlr::HandleReceiverException( m_pSoap, GetLastError() );
		}

		// Paranoia: Listener thread deletes the handler threads
		// if they don't respond on shutdown.  It now calls stop() first
		// so do not expect that to happen any longer but the following
		// check won't hurt.
		if ( m_pSoap )	
		{
			_ReleaseSoap();

			soap_destroy( m_pSoap );
			soap_end( m_pSoap );
			soap_done(m_pSoap);
		}

		m_bIsRunning = false;
	}
}

void
CEMSSOAPHandlerThreadEx::_ReleaseSoap()
{
	if( m_pSoap )
	{
		soap_destroy( m_pSoap );
		soap_end( m_pSoap );
		soap_done( m_pSoap );

		// The runtime must have been allocate by eithe soap_new() or soap_copy().
		soap_free( m_pSoap );
		m_pSoap = NULL;
	}
}

