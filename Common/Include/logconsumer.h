/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __LOG_CONSUMER_H__
#define __LOG_CONSUMER_H__

#include "mqconsumer.h"
#include "jLog.h"
#include "pointerlist.h"

class CEMSLogConsumer : public MQConsumer
{
	public:
		CEMSLogConsumer( const std::string& brokerURI,
						 const std::string& destinationName, 
						 int numMessages,
						 bool useTopic = false,
						 bool sessionTransacted = false,
						 int waitMillis = 10000 );

		virtual ~CEMSLogConsumer();

		virtual void onMessage( const Message* message ) throw();

		CEMSPointerList<CEMSjLog> getLogs();

	private:
		CEMSLogConsumer( const CEMSLogConsumer& );
		CEMSLogConsumer& operator= ( const CEMSLogConsumer& );

	private:
		CEMSPointerList<CEMSjLog> lstjLogs;

		apr_thread_mutex_t* mutexCommands;
};

#endif