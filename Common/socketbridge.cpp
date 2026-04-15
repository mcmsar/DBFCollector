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

#include "socketbridge.h"
#include "socket/socket.h"
#include "emsexcpt.h"
#include <log4cxx/ndc.h>

const char* CEMSSocketBridge::ms_cszLogger = "SocketBridge";


CEMSSocketBridge::CEMSSocketBridge() : CApiObjBase(TEXT("CEMSSocketBridge")),
									m_pSockFrom(NULL), m_pSockTo(NULL), m_bRunning(false)
{
	m_pLogger = log4cxx::Logger::getLogger( ms_cszLogger );
}

CEMSSocketBridge::CEMSSocketBridge( const CEMSSocketBridge& x ) : 
											m_pSockFrom(x.m_pSockFrom), 
											m_pSockTo(x.m_pSockTo), m_bRunning(false),
											m_pLogger(x.m_pLogger)
{
	if( m_pSockFrom )
		m_pSockFrom->AddRef();

	if( m_pSockTo )
		m_pSockTo->AddRef();
}

CEMSSocketBridge::~CEMSSocketBridge()
{
	Stop();

	if( m_pSockFrom )
	{
		m_pSockFrom->Release();
		m_pSockFrom = NULL;
	}

	if( m_pSockTo )
	{
		m_pSockTo->Release();
		m_pSockTo = NULL;
	}
}

void 
CEMSSocketBridge::Init( IEMSSocket* pSockFrom, IEMSSocket* pSockTo )
{
	if( !m_bRunning )
	{
		if( m_pSockFrom )
		{
			m_pSockFrom->Release();
			m_pSockFrom = NULL;
		}

		m_pSockFrom = pSockFrom;

		if( m_pSockFrom )
			m_pSockFrom->AddRef();

		if( m_pSockTo )
		{
			m_pSockTo->Release();
			m_pSockTo = NULL;
		}

		m_pSockTo = pSockTo;

		if( m_pSockTo )
			m_pSockTo->AddRef();
	}
}

void 
CEMSSocketBridge::Start()
{
	if( !m_bRunning )
	{
		LOG4CXX_INFO( m_pLogger, "Starting TCP/IP bridge." );
		start();
	}
}

void 
CEMSSocketBridge::Stop()
{
	if( m_bRunning )
	{
		LOG4CXX_INFO( m_pLogger, "Stopping TCP/IP bridge." );
		SignalStop();

		if( !wait( 5000 ) )
			stop();
	}
}

void
CEMSSocketBridge::run()
{
	m_bRunning = true;
    
	try
	{
		if( !m_pSockFrom )
		{
			LOG4CXX_ERROR( m_pLogger, "A 'from' socket is not available.");
			THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
		}

		if( !m_pSockTo )
		{
			LOG4CXX_ERROR( m_pLogger, "A 'to' socket is not available.");
			THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
		}

		// First build a logging context string.  It is the sourceip:sourcport_destip:destport.
		// This allows us to distinguish entries related to one route from another in the log.
		std::stringstream ostrmCtx;
		ostrmCtx << m_pSockFrom << "_" << m_pSockTo;
		log4cxx::NDC oCtxt( ostrmCtx.str().c_str() );


		bool bShutdown = false;
		while( !WaitForStop( 1 ) && !bShutdown )
		{
			try
			{
				int iSelect = m_pSockFrom->Select(true);

				if( 0 != iSelect )
				{
					LOG4CXX_DEBUG( m_pLogger, "Data ready on source socket.");

					const int ciLen = 4096;
					BYTE abyBuff[ciLen];
					memset( abyBuff, 0, ciLen*sizeof(BYTE) );

					int iRead = m_pSockFrom->Receive( (char*) abyBuff, ciLen, 0 );

					bool bIsData = false;

					if( iRead > 0 )
					{
						bIsData = true;
					}

					if( bIsData )
					{
						while( bIsData )
						{
							int iSent = m_pSockTo->Send( (const char*) abyBuff, iRead, 0 );

							if( iSent != iRead )
							{
								LOG4CXX_ERROR( m_pLogger, "Attempted to forward " << iRead << " bytes, but " << iSent << " actually sent." );
							}
							else
							{
								LOG4CXX_DEBUG( m_pLogger, "Sent " << iSent << " bytes from src to dest." );
							}

							bIsData = ( m_pSockFrom->Select(true) > 0 ) ? true : false;

							if( bIsData )
							{
								memset( abyBuff, 0, ciLen*sizeof(BYTE) );
								iRead = m_pSockFrom->Receive( (char*) abyBuff, ciLen, 0 );
							}
						}
					}
					else
					{
						// Disconnect request.
						LOG4CXX_INFO( m_pLogger, "Disconnect request received from the source.");
						bShutdown = true;
					}
				}
			}
			catch( ... )
			{
				LOG4CXX_ERROR( m_pLogger, "An exception was encountered in a socket bridge.");
			}
		}
	}
	catch( ... )
	{
		LOG4CXX_ERROR( m_pLogger, "Exception encountered.");
	}

	m_bRunning = false;

	LOG4CXX_INFO( m_pLogger, "TCP/IP bridge thread exiting." );
}