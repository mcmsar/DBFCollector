/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __COMMAND_CONSUMER_H__
#define __COMMAND_CONSUMER_H__

#include "mqconsumer.h"
#include "command.h"
#include "pointerlist.h"

class CEMSCommandConsumer : public MQConsumer
{
	public:
		CEMSCommandConsumer( const std::string& brokerURI,
					const std::string& destinationName, 
					int numMessages,
					bool useTopic = false,
					bool sessionTransacted = false,
					int waitMillis = 10000 );

		virtual ~CEMSCommandConsumer();

		virtual void onMessage( const Message* message ) throw();

		CEMSPointerList<CEMSCommand> getCommands();

	private:
		CEMSCommandConsumer( const CEMSCommandConsumer& );
		CEMSCommandConsumer& operator= ( const CEMSCommandConsumer& );

	private:
		CEMSPointerList<CEMSCommand> lstCommands;

		apr_thread_mutex_t* mutexCommands;

};

#endif