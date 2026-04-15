/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "mqconsumer.h"

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <activemq/util/Config.h>

MQConsumer::MQConsumer( const std::string& brokerURI,
					   const std::string& destinationName,
					int numMessages,
                    bool useTopic,
                    bool sessionTransacted,
                    int waitMillis ) :
    latch(1),
    doneLatch(numMessages),
    connection(NULL),
    session(NULL),
    destination(NULL),
    consumer(NULL),
    waitMillis(waitMillis),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    brokerURI(brokerURI),
	destinationName(destinationName),
	lastException(false),
	mutexException(NULL) {

	// Create mutex for use in exception handling.
	apr_pool_t *mp = NULL;
	apr_pool_create(&mp, NULL); 
	apr_thread_mutex_create(&mutexException, APR_THREAD_MUTEX_UNNESTED, mp);  
}

MQConsumer::~MQConsumer() throw() {
    cleanup();
}

void 
MQConsumer::close() {
    this->cleanup();
}

void 
MQConsumer::waitUntilReady() {
    latch.await();
}

void 
MQConsumer::run() {

    try {

        // Create a ConnectionFactory
        auto_ptr<ConnectionFactory> connectionFactory(
            ConnectionFactory::createCMSConnectionFactory( brokerURI ) );

        // Create a Connection
        connection = connectionFactory->createConnection();
        connection->start();
        connection->setExceptionListener(this);

        // Create a Session
        if( this->sessionTransacted == true ) {
            session = connection->createSession( Session::SESSION_TRANSACTED );
        } else {
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
        }

        // Create the destination (Topic or Queue)
        if( useTopic ) {
            destination = session->createTopic( destinationName );
        } else {
            destination = session->createQueue( destinationName );
        }

        // Create a MessageConsumer from the Session to the Topic or Queue
        consumer = session->createConsumer( destination );

        consumer->setMessageListener( this );

        std::cout.flush();
        std::cerr.flush();

        // Indicate we are ready for messages.
        latch.countDown();

        // Wait while asynchronous messages come in.
        doneLatch.await( waitMillis );

    } catch( CMSException& e ) {

        // Indicate we are ready for messages.
        latch.countDown();
        e.printStackTrace();
		throw e;
    }
}

// Called from the consumer since this class is a registered MessageListener.
void 
MQConsumer::onMessage( const Message* message ) throw() {

    static int count = 0;

    try
    {
        count++;
        const TextMessage* textMessage =
            dynamic_cast< const TextMessage* >( message );
        string text = "";

        if( textMessage != NULL ) {
            text = textMessage->getText();
        } else {
            text = "NOT A TEXTMESSAGE!";
        }

        printf( "Message #%d Received: %s\n", count, text.c_str() );

    } catch (CMSException& e) {
        e.printStackTrace();
    }

    // Commit all messages.
    if( this->sessionTransacted ) {
        session->commit();
    }

    // No matter what, tag the count down latch until done.
    doneLatch.countDown();
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void 
MQConsumer::onException( const CMSException& ex AMQCPP_UNUSED) {
    printf("CMS Exception occurred.\n");
    ex.printStackTrace();
	
	try {
		apr_thread_mutex_lock( mutexException );

		lastException = true;

		apr_thread_mutex_unlock( mutexException );
	}
	catch( Exception& e ) {
		apr_thread_mutex_unlock( mutexException );
		e.printStackTrace();
		throw e;
	}
}

bool
MQConsumer::isLastException() {

	bool ret = false;

	try {
		apr_thread_mutex_lock( mutexException );
		
		ret = lastException;

		lastException = false;

		apr_thread_mutex_unlock( mutexException );
	}
	catch( ... ) {
		apr_thread_mutex_unlock( mutexException );
		throw;
	}

	return ret;
}

void 
MQConsumer::cleanup(){

    //*************************************************
    // Always close destination, consumers and producers before
    // you destroy their sessions and connection.
    //*************************************************

    // Destroy resources.
    try{
        if( destination != NULL ) delete destination;
    }catch (CMSException& e) { e.printStackTrace(); }
    destination = NULL;

    try{
        if( consumer != NULL ) delete consumer;
    }catch (CMSException& e) { e.printStackTrace(); }
    consumer = NULL;

    // Close open resources.
    try{
        if( session != NULL ) session->close();
        if( connection != NULL ) connection->close();
    }catch (CMSException& e) { e.printStackTrace(); }

    // Now Destroy them
    try{
        if( session != NULL ) delete session;
    }catch (CMSException& e) { e.printStackTrace(); }
    session = NULL;

    try{
        if( connection != NULL ) delete connection;
    }catch (CMSException& e) { e.printStackTrace(); }
    connection = NULL;

	try{
		lastException = false;
	} catch(CMSException& e) { e.printStackTrace(); }


	try{
		if( mutexException != NULL ) apr_thread_mutex_destroy( mutexException );
	} catch( ... ) {  }
	mutexException = NULL;
}