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

#ifndef __SOCKET_BRIDGE_H__
#define __SOCKET_BRIDGE_H__

#include "aobjbase.h"
#include "emsthread.h"
#include <log4cxx/logger.h>

class CEMSSocketBridge;
class IEMSSocket;

//! Bridges data from one socket to another, unidirectionally.  Use two instances to get
//! bidirectional flow.
class CEMSSocketBridge : public CApiObjBase, public CEMSThread
{
	public:
		CEMSSocketBridge();
		CEMSSocketBridge( const CEMSSocketBridge& x );
		~CEMSSocketBridge();

		void Init( IEMSSocket* pSockFrom, IEMSSocket* pSockTo );

		void Start();
		void Stop();
		bool IsRunning() const { return m_bRunning; }

	private:
		void run();

	private:
		static const char* ms_cszLogger;
		
	private:
		IEMSSocket* m_pSockFrom;
		IEMSSocket* m_pSockTo;
		bool m_bRunning;
		log4cxx::LoggerPtr m_pLogger;
};

#endif