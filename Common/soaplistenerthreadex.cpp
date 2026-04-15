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

#include "soaplistenerthreadex.h"
#include "soaphandlerthreadex.h"
#include "emsexcpt.h"
#include <process.h>

const long EMS_WAIT_FOR_AVAILABLE_THREAD = 500;	// milliseconds
const long EMS_THREAD_STOP_WAIT = 3000;	// milliseconds to wait for threads to stop before forcing shutdown.

CEMSSOAPListenerThreadEx::CEMSSOAPListenerThreadEx() : m_pSoap(0), 
												m_bShutdownFlag(false), m_lNumHandlerThreads(1), m_bIsRunning(false),
												m_pfnGetHandler(NULL), m_bUseSSL(false)
{
}

CEMSSOAPListenerThreadEx::CEMSSOAPListenerThreadEx( const CEMSSOAPListenerThreadEx& x ) : 
													m_pSoap(x.m_pSoap), 
													m_bShutdownFlag(false), m_lNumHandlerThreads(x.m_lNumHandlerThreads), 
													m_bIsRunning(false),
													m_pfnGetHandler(x.m_pfnGetHandler),
													m_bUseSSL( x.m_bUseSSL )

{
}

CEMSSOAPListenerThreadEx::~CEMSSOAPListenerThreadEx()
{
	soap_destroy( m_pSoap );
	soap_end( m_pSoap );

	m_pSoap = 0;	
}

void
CEMSSOAPListenerThreadEx::Init( struct soap* pSoap )
{
	m_pSoap = pSoap;

#ifdef DEBUG
	char szLogFile[ 128 ];
	sprintf( szLogFile, "recv_listener.txt" );
	soap_set_recv_logfile( m_pSoap, szLogFile );

	sprintf( szLogFile, "sent_listener.txt" );
	soap_set_sent_logfile( m_pSoap, szLogFile );

	sprintf( szLogFile, "test_listener.txt" );
	soap_set_test_logfile( m_pSoap, szLogFile );
#endif
}

void
CEMSSOAPListenerThreadEx::Shutdown()
{
	m_bShutdownFlag = true;

	soap_done( m_pSoap );
}

void
CEMSSOAPListenerThreadEx::Start()
{
	if( !m_bIsRunning )
		start();
}

void 
CEMSSOAPListenerThreadEx::run()
{
	m_bIsRunning = true;

	if( m_pSoap )
	{
		CEMSSOAPHandlerThreadEx** apHandlers = 0; 
		long lHandlerThreads = 0;
		struct soap *pRequestSoap = 0;

		try
		{
			// Set up the Handler Threads:
			lHandlerThreads = _GetNumHandlerThreads();

			if( lHandlerThreads < 1 )
			{
				// There must be at least one thread.
				lHandlerThreads = 1;
			}
			wchar_t wszThreads[ 8 ];
			swprintf( wszThreads, L"%d", lHandlerThreads );
//			LogInfoMsg( EMS_MTL_SOAP_SERVER_THREADS, wszThreads );
		
			apHandlers = new CEMSSOAPHandlerThreadEx*[ lHandlerThreads ];

			if( !apHandlers )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( apHandlers, 0, lHandlerThreads*sizeof(CEMSSOAPHandlerThreadEx*) );

			for( long l = 0; l < lHandlerThreads; l++ )
			{
				apHandlers[l] = new CEMSSOAPHandlerThreadEx;

				if( !apHandlers[l] )
				{
					THROW_NOMEMORY_EXCEPTION();
				}
			}

			while( !m_bShutdownFlag )
			{
				int s = soap_accept( m_pSoap );

				if( s < 0 )
					break;

				pRequestSoap = soap_copy(m_pSoap);

				if( m_bUseSSL )
				{
					// should call soap_ssl_accept on a copy of the soap runtime

#ifndef NO_OPEN_SSL
					if (soap_ssl_accept(pRequestSoap))
					{
						soap_print_fault(pRequestSoap, stderr);
						//soap_free(pRequestSoap);
						//pRequestSoap = NULL;
						
						// when soap_ssl_accept fails, we should just go on
					} 
#endif
				}

/* Ticket 6998: Commented out.  Message was flooding the log in trace mode.
				int i1 = (m_pSoap->ip>>24)&0xFF;
				int i2 = (m_pSoap->ip>>16)&0xFF;
				int i3 = (m_pSoap->ip>>8)&0xFF;
				int i4 = (m_pSoap->ip)&0xFF;

				wchar_t wszIP[ 16 ];
				swprintf( wszIP, L"%d.%d.%d.%d", i1, i2, i3, i4 );

				LogTraceMsg( EMS_MTL_SOAP_CONNECT_RECVD, wszIP );
*/
				bool bFoundThread = false;

				while( !bFoundThread )
				{
					for( long l = 0; (l < lHandlerThreads) && !bFoundThread; l++ )
					{
						if( apHandlers[l] )
						{
							if( apHandlers[l]->wait( EMS_WAIT_FOR_AVAILABLE_THREAD ) )
							{
								apHandlers[l]->RegisterGetHandler( m_pfnGetHandler );
								apHandlers[l]->SetSoap( pRequestSoap );
								pRequestSoap = NULL;	// Handler now owns it.
								apHandlers[l]->start();

								bFoundThread = true;
							}
						}
					}

					if( !bFoundThread )
					{
//						LogTraceMsg( EMS_MTL_SOAP_NO_HANDLER_THREAD );
					}
				}
			}

			if( apHandlers )
			{
				for( long l = 0; l < lHandlerThreads; l++ )
				{
					if( apHandlers[l] )
					{
						if ( !apHandlers[l]->wait( EMS_THREAD_STOP_WAIT ) )
						{
							// timeout
							apHandlers[l]->stop();
						}
						delete apHandlers[l];
						apHandlers[l] = 0;
					}
				}

				delete[] apHandlers;
				apHandlers = 0;
			}
		}
		catch( ... )
		{
			if( apHandlers )
			{
				for( long l = 0; l < lHandlerThreads; l++ )
				{
					if( apHandlers[l] )
					{
						if ( !apHandlers[l]->wait( EMS_THREAD_STOP_WAIT ) )
						{
							// timeout
							apHandlers[l]->stop();
						}

						delete apHandlers[l];
						apHandlers[l] = 0;
					}
				}

				delete[] apHandlers;
				apHandlers = 0;
			}

			m_bIsRunning = false;

			throw;

		}

	}

	m_bIsRunning = false;
}

long 
CEMSSOAPListenerThreadEx::_GetNumHandlerThreads()
{
	return m_lNumHandlerThreads;
}