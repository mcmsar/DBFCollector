/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef __MQ_PRODUCER_H__
#define __MQ_PRODUCER_H__

#include <activemq/core/ActiveMQConnectionFactory.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>

using namespace activemq::core;
//using namespace decaf::util::concurrent;
//using namespace decaf::util;
//using namespace decaf::lang;
using namespace cms;
using namespace std;


class MQProducer  {
	
	public:

		MQProducer( const std::string& brokerURI,
					const std::string& destinationName, 		
					int numMessages,
					bool useTopic = false,
					bool sessionTransacted = false,
					bool persistentDelivery = false );

		virtual ~MQProducer() {	cleanup();	}

		void sendMessage( const std::string& msg );
		void sendMessage( const BYTE* buffer, const ULONG culSize );
		void sendMessage( Message* message );

		BytesMessage* createBytesMessage();
		TextMessage* createTextMessage();

	private:
		bool init();
		void cleanup();

	private:

		Connection* connection;
		Session* session;
		Destination* destination;
		MessageProducer* producer;
		int numMessages;
		bool useTopic;
		bool sessionTransacted;
		std::string brokerURI;
		std::string destinationName;
		bool persistentDelivery;


};

#endif