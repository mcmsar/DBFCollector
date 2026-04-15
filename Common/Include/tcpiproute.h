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

#ifndef __TCPIP_ROUTE_H__
#define __TCPIP_ROUTE_H__

#include "aobjbase.h"
#include "emsthread.h"
#include "socket/win32socket2.h"
#include <log4cxx/logger.h>

//! Routes TCP/IP traffic from one socket to another.
class CEMSTCPIPRoute : public CApiObjBase, public CEMSThread
{
	public:
		CEMSTCPIPRoute();
		CEMSTCPIPRoute( const CEMSTCPIPRoute& x );
		CEMSTCPIPRoute( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr );
		CEMSTCPIPRoute( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr, const CEMSSocketAddress& croDestAddr2 );
		~CEMSTCPIPRoute();

		void Set( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr );
		void Set( const CEMSSocketAddress& croSourceAddr, const CEMSSocketAddress& croDestAddr, const CEMSSocketAddress& croDestAddr2 );

		void SetSource( const CEMSSocketAddress& croSourceAddr );
		CEMSSocketAddress GetSource() const { return m_oSrcAddr; }

		void SetDestination( const CEMSSocketAddress& croDestAddr );
		CEMSSocketAddress GetDestination() const { return m_oDestAddr; }

		void SetDestination2( const CEMSSocketAddress& croDestAddr );
		CEMSSocketAddress GetDestination2() const { return m_oDestAddr; }


		void Start();

		void Stop();

		bool IsRunning() const { return m_bRunning; }

	private:
		void run();

	private:
		static const char* ms_cszLogger;

	private:
		CEMSSocketAddress m_oSrcAddr;
		CEMSSocketAddress m_oDestAddr;
		CEMSSocketAddress m_oDestAddr2;

		CEMSWin32Socket2 m_oSrcSocket;
		//CEMSWin32Socket2 m_oDestSocket;
		//CEMSWin32Socket2 m_oDestSocket2;

		bool m_bRunning;

		log4cxx::LoggerPtr m_pLogger;

};

#endif