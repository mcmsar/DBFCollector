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

	$Log:
	$
********************************************************************/
#ifdef WIN32
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include "tcpiproute.h"
#include "pointerlist.h"
#include "socketbridge.h"
#include "emsexcpt.h"
#include <log4cxx/ndc.h>

const char* CEMSTCPIPRoute::ms_cszLogger = "TCPIPRoute";

CEMSTCPIPRoute::CEMSTCPIPRoute() : CApiObjBase(TEXT("CEMSTCPIPRoute")),m_bRunning(false)
{
	m_pLogger = log4cxx::Logger::getLogger( ms_cszLogger );
}

CEMSTCPIPRoute::CEMSTCPIPRoute( const CEMSTCPIPRoute& x ) : CApiObjBase(TEXT("CEMSTCPIPRoute")),
														m_oSrcAddr(x.m_oSrcAddr), m_oDestAddr(x.m_oDestAddr),
														m_oSrcSocket(x.m_oSrcSocket),
														m_bRunning(x.m_bRunning),
														m_pLogger(x.m_pLogger)
{
}

CEMSTCPIPRoute::CEMSTCPIPRoute( const CEMSSocketAddress& croSourceAddr, 
							   const CEMSSocketAddress& croDestAddr ) : CApiObjBase(TEXT("CEMSTCPIPRoute")),
														m_oSrcAddr(croSourceAddr), m_oDestAddr(croDestAddr),
														m_bRunning(false)
{
	m_pLogger = log4cxx::Logger::getLogger( ms_cszLogger );
}

CEMSTCPIPRoute::CEMSTCPIPRoute( const CEMSSocketAddress& croSourceAddr, 
							   const CEMSSocketAddress& croDestAddr,
							   const CEMSSocketAddress& croDestAddr2 ) : CApiObjBase(TEXT("CEMSTCPIPRoute")),
														m_oSrcAddr(croSourceAddr), m_oDestAddr(croDestAddr),
														m_oDestAddr2(croDestAddr2), m_bRunning(false)
{
	m_pLogger = log4cxx::Logger::getLogger( ms_cszLogger );
}

CEMSTCPIPRoute::~CEMSTCPIPRoute()
{
	Stop();
}

void 
CEMSTCPIPRoute::Set( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr )
{
	if( !m_bRunning )
	{
		m_oSrcAddr = croSourceAddr;
		m_oDestAddr = croDestAddr;
	}
}

void 
CEMSTCPIPRoute::Set( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr,
					const CEMSSocketAddress& croDestAddr2 )
{
	if( !m_bRunning )
	{
		m_oSrcAddr = croSourceAddr;
		m_oDestAddr = croDestAddr;
		m_oDestAddr2 = croDestAddr2;
	}
}

void 
CEMSTCPIPRoute::SetSource( const CEMSSocketAddress& croSourceAddr )
{
	if( !m_bRunning )
	{
		m_oSrcAddr = croSourceAddr;
	}
}

void 
CEMSTCPIPRoute::SetDestination( const CEMSSocketAddress& croDestAddr )
{
	if( !m_bRunning )
	{
		m_oDestAddr = croDestAddr;
	}
}

void 
CEMSTCPIPRoute::SetDestination2( const CEMSSocketAddress& croDestAddr )
{
	if( !m_bRunning )
	{
		m_oDestAddr2 = croDestAddr;
	}
}

void 
CEMSTCPIPRoute::Start()
{
	if( !m_bRunning )
	{
		LOG4CXX_INFO( m_pLogger, "Starting TCP/IP routing." );
		start();
	}
}

void 
CEMSTCPIPRoute::Stop()
{
	if( m_bRunning )
	{
		LOG4CXX_INFO( m_pLogger, "Stopping TCP/IP routing." );
		SignalStop();

		if( !wait( 5000 ) )
			stop();
	}
}

void 
CEMSTCPIPRoute::run()
{
	m_bRunning = true;
    
	// First build a logging context string.  It is the sourceip:sourcport_destip:destport.
	// This allows us to distinguish entries related to one route from another in the log.
	std::stringstream ostrmCtx;
	ostrmCtx << m_oSrcAddr.GetIP() << ":" << m_oSrcAddr.GetPort() << "_" << m_oDestAddr.GetIP() << ":" << m_oDestAddr.GetPort();
	log4cxx::NDC oCtxt( ostrmCtx.str().c_str() );

	try
	{
		// Connect to the destination.
		//LOG4CXX_INFO( m_pLogger, "Connecting to destination socket.");
		//m_oDestSocket.Connect( m_oDestAddr );

		// Bind to the source.
		LOG4CXX_INFO( m_pLogger, "Binding source socket.");
		bool bBound = false;
		m_oSrcSocket.Bind( m_oSrcAddr, bBound );

		if( !bBound )
		{
			LOG4CXX_ERROR( m_pLogger, "Failed to bind source socket.");
		}

		LOG4CXX_INFO( m_pLogger, "Listening on source socket.");
		m_oSrcSocket.Listen();

		bool bShutdown = false;

		//CEMSPointerList<CEMSSocketBridge> olstBridges;
		CEMSSocketBridge* pBridge1 = NULL;
		CEMSSocketBridge* pBridge2 = NULL;


		while( !WaitForStop( 1 ) && !bShutdown )
		{
			IEMSSocket* pSrc = NULL; 
			IEMSSocket* pDest = NULL;
			IEMSSocket* pDest2 = NULL;

			try
			{
				// Only one inbound connection allowed.
				if( !pBridge1 && !pBridge2 )
				{
					if( m_oSrcSocket.IsConnection() )
						pSrc = m_oSrcSocket.Accept();

					if( pSrc )
					{
						LOG4CXX_INFO( m_pLogger, "Received a connection.  Creating bi-directional bridge." );
						
						pDest = new CEMSWin32Socket2();

						if( !pDest )
						{
							THROW_NOMEMORY_EXCEPTION();
						}

						pDest->Connect( m_oDestAddr );

						// Check whether a secondary (dummy) destination connection is required.
						// In some applications this is required to maintain both ports open (e.g., ChannelCard).
						if( m_oDestAddr2.GetPort() > 0 )
						{
							pDest2 = new CEMSWin32Socket2();

							if( !pDest2 )
							{
								THROW_NOMEMORY_EXCEPTION();
							}

							pDest2->Connect( m_oDestAddr2 );
						}

						pBridge1 = new CEMSSocketBridge;

						if( !pBridge1 )
						{
							THROW_NOMEMORY_EXCEPTION();
						}

						pBridge1->Init( pSrc, pDest );

						pBridge2 = new CEMSSocketBridge;

						if( !pBridge2 )
						{
							THROW_NOMEMORY_EXCEPTION();
						}

						pBridge2->Init( pDest, pSrc );
						//olstBridges.Add( pBridge2 );

						pSrc->Release();
						pDest->Release();

						pBridge1->Start();
						pBridge2->Start();

					}

					Sleep( 1000 );
				}
				else
				{
					bool bDisconnect = false;

					// If a bridge is not running, one side of the conversation has disconnected.
					// So, release the pair.
					if( !pBridge1->IsRunning() ||
						!pBridge2->IsRunning() )
					{
						bDisconnect = true;
						
					}
					else if( pDest2 )
					{
						int iSelect = pDest2->Select(true);

						if( 0 != iSelect )
						{
							// Read status is set.  This is most likely a disconnect, but check it.

							const int ciLen = 4096;
							BYTE abyBuff[ciLen];
							memset( abyBuff, 0, ciLen*sizeof(BYTE) );

							int iRead = pDest2->Receive( (char*) abyBuff, ciLen, 0 );

							if( iRead < 1 )
							{
								// Disconnect.
								bDisconnect = true;
							}
						}
					}

					if( bDisconnect )
					{
						pBridge1->Stop();
						pBridge1->Release();
						pBridge1 = NULL;

						pBridge2->Stop();
						pBridge2->Release();
						pBridge2 = NULL;

						pDest2->Release();
						pDest2 = NULL;
					}
				}
			}
			catch( ... )
			{
				LOG4CXX_ERROR( m_pLogger, "An exception was encountered in a TCP/IP route.");

				if( pSrc )
				{
					pSrc->Release();
					pSrc = NULL;
				}

				if( pDest )
				{
					pDest->Release();
					pDest = NULL;
				}

				if( pDest2 )
				{
					pDest2->Release();
					pDest2 = NULL;
				}

				if( pBridge1 )
				{
					pBridge1->Release();
					pBridge1 = NULL;
				}

				if( pBridge2 )
				{
					pBridge2->Release();
					pBridge2 = NULL;
				}
			}
		}

		m_oSrcSocket.Close();
	}
	catch( ... )
	{
		LOG4CXX_ERROR( m_pLogger, "Exception encountered.");
	}

	m_bRunning = false;

	LOG4CXX_INFO( m_pLogger, "TCP/IP routing thread exiting." );
}