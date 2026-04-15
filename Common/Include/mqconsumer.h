/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __MQ_CONSUMER_H__
#define __MQ_CONSUMER_H__

#include <activemq/core/ActiveMQConnectionFactory.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>

#include <apr_thread_mutex.h>

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

class MQConsumer : public ExceptionListener,
                   public MessageListener,
				   public Runnable {

	public:

		MQConsumer( const std::string& brokerURI,
					const std::string& destinationName, 
					int numMessages,
					bool useTopic = false,
					bool sessionTransacted = false,
					int waitMillis = 10000 );

		virtual ~MQConsumer() throw();

		void close();
		void waitUntilReady();
		virtual void run();

		// Called from the consumer since this class is a registered MessageListener.
		// Derived classes should override this method.
		virtual void onMessage( const Message* message ) throw();

		// If something bad happens you see it here as this class is also been
		// registered as an ExceptionListener with the connection.
		// Derived classes should override this method.
		virtual void onException( const CMSException& ex AMQCPP_UNUSED);

		// Determine if an exception notification was received from the broker.
		bool isLastException();

		// Is there an underlying consumer?  This can be used to indicate
		// the connection to the MQ was successful.
		bool isConsumer() { return ( NULL != consumer ) ? true : false; }

	private:

		MQConsumer( const MQConsumer& );
		MQConsumer& operator= ( const MQConsumer& );
		void cleanup();


	protected:

		CountDownLatch latch;
		CountDownLatch doneLatch;
		Connection* connection;
		Session* session;
		Destination* destination;
		MessageConsumer* consumer;
		long waitMillis;
		bool useTopic;
		bool sessionTransacted;
		std::string brokerURI;
		std::string destinationName;

	private:

		bool lastException;
		//CMSException lastException;
		apr_thread_mutex_t *mutexException;
};

#endif