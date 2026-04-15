/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "mqproducer.h"

MQProducer::MQProducer( const std::string& brokerURI,
						const std::string& destinationName,
						int numMessages,
						bool useTopic,
						bool sessionTransacted,
						bool persistentDelivery)
{
	this->connection = NULL;
	this->session = NULL;
	this->destination = NULL;
	this->producer = NULL;
	this->numMessages = numMessages;
	this->useTopic = useTopic;
	this->sessionTransacted = sessionTransacted;
	this->brokerURI = brokerURI;
	this->destinationName = destinationName;
	this->persistentDelivery = persistentDelivery;
}

bool 
MQProducer::init()
{
	bool ret = false;

	try {

		if( !producer )
		{
			cleanup();

			// Create a ConnectionFactory
			auto_ptr<ConnectionFactory> connectionFactory(
				ConnectionFactory::createCMSConnectionFactory( brokerURI ) );

			// Create a Connection
			connection = connectionFactory->createConnection();
			connection->start();

			// Create a Session
			if( this->sessionTransacted ) {
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

			// Create a MessageProducer from the Session to the Topic or Queue
			producer = session->createProducer( destination );

			if( persistentDelivery ) {
				producer->setDeliveryMode( DeliveryMode::PERSISTENT );
			}
			else {
				producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
			}

			ret = true;
		}
		else {
			ret = true;
		}
	}catch ( CMSException& e ) {
		e.printStackTrace();
		ret = false;
	}

	return ret;
}

void 
MQProducer::sendMessage( const std::string& msg )
{
	if( !msg.empty() ) {

		if( init() ) {

			TextMessage* message = NULL;

			try {
				message = session->createTextMessage( msg );

				// Tell the producer to send the message
				printf( "Sent message %s\n", msg.c_str() );
				producer->send( message );

				delete message;
				message = NULL;
			}
			catch( ... ) {

				if( message ) {
					delete message;
					message = NULL;
				}

				throw;
			}

		}
		else {
			throw std::exception("Failed to send message.  Producer could not be initialized.");
		}
	}
}

void MQProducer::sendMessage( const BYTE* buffer, const ULONG culSize )
{
	if( buffer ) {

		if( init() ) {

			BytesMessage* message = NULL;

			try {
				
				message = session->createBytesMessage( buffer, culSize);

				// Tell the producer to send the message
				printf( "Sent bytes message\n" );
				producer->send( message );

				delete message;
				message = NULL;
			}
			catch( ... ) {

				if( message ) {
					delete message;
					message = NULL;
				}

				throw;
			}

		}
		else {
			throw std::exception("Failed to send message.  Producer could not be initialized.");
		}
	}
}

void MQProducer::sendMessage( Message* message )
{
	if( message )
	{
		if( init() ) {

			try {
				producer->send( message );
			}
			catch( ... ) {

				throw;
			}

		}
		else {
			throw std::exception("Failed to send message.  Producer could not be initialized.");
		}
	}
}

BytesMessage* MQProducer::createBytesMessage()
{
	BytesMessage* message = NULL;

	if( init() ) {

		try {
			message = session->createBytesMessage();
		}
		catch( ... ) {

			if( message ) {
				delete message;
				message = NULL;
			}

			throw;
		}

	}
	else {
		throw std::exception("Failed to create message.  Producer could not be initialized.");
	}

	return message;
}

TextMessage* MQProducer::createTextMessage()
{
	TextMessage* message = NULL;

	if( init() ) {

		try {
			message = session->createTextMessage();
		}
		catch( ... ) {

			if( message ) {
				delete message;
				message = NULL;
			}

			throw;
		}

	}
	else {
		throw std::exception("Failed to create message.  Producer could not be initialized.");
	}

	return message;
}

void 
MQProducer::cleanup()
{
	// Destroy resources.
	try{
		if( destination != NULL ) delete destination;
	}catch ( CMSException& e ) { e.printStackTrace(); }
	destination = NULL;

	try{
		if( producer != NULL ) delete producer;
	}catch ( CMSException& e ) { e.printStackTrace(); }
	producer = NULL;

	// Close open resources.
	try{
		if( session != NULL ) session->close();
		if( connection != NULL ) connection->close();
	}catch ( CMSException& e ) { e.printStackTrace(); }

	try{
		if( session != NULL ) delete session;
	}catch ( CMSException& e ) { e.printStackTrace(); }
	session = NULL;

	try{
		if( connection != NULL ) delete connection;
	}catch ( CMSException& e ) { e.printStackTrace(); }
	connection = NULL;
}