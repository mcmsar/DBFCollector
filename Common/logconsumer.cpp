/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "logconsumer.h"

CEMSLogConsumer::CEMSLogConsumer( const std::string& brokerURI,
								  const std::string& destinationName, 
								  int numMessages,
								  bool useTopic,
								  bool sessionTransacted,
								  int waitMillis ) : MQConsumer( brokerURI, destinationName, numMessages, useTopic, sessionTransacted, waitMillis ),
													 mutexCommands(NULL)
{
	apr_pool_t *mp = NULL;
	apr_pool_create(&mp, NULL); 
	apr_thread_mutex_create(&mutexCommands, APR_THREAD_MUTEX_UNNESTED, mp);  
}

CEMSLogConsumer::~CEMSLogConsumer()
{
	if( mutexCommands )
	{
		apr_thread_mutex_destroy( mutexCommands );
		mutexCommands = NULL;
	}
}

void 
CEMSLogConsumer::onMessage( const Message* message )
{
	CEMSjLog* pLog = NULL;

	static int count = 0;

	try
    {
        count++;
        const TextMessage* textMessage =
            dynamic_cast< const TextMessage* >( message );
        string text = "";

        if( textMessage != NULL ) {
            text = textMessage->getText();

			if( !text.empty() )
			{
				try {
					apr_thread_mutex_lock( mutexCommands );

					pLog = new CEMSjLog;
					pLog->Set( text );
					lstjLogs.Add( pLog );
					pLog->Release();
					pLog = NULL;

					apr_thread_mutex_unlock( mutexCommands );
				}
				catch( ... ) {
					apr_thread_mutex_unlock( mutexCommands );
					throw;
				}
			}

        } else {
            text = "NOT A TEXTMESSAGE!";
        }

        printf( "Message #%d Received: %s\n", count, text.c_str() );

    } 
	catch (CMSException& e) 
	{
        e.printStackTrace();
    }

	if( pLog ) 
	{
		pLog->Release();
		pLog = NULL;
	}

    // Commit all messages.
    if( this->sessionTransacted ) 
	{
        session->commit();
    }

    // No matter what, tag the count down latch until done.
    doneLatch.countDown();
}

CEMSPointerList<CEMSjLog> 
CEMSLogConsumer::getLogs() 
{
	CEMSPointerList<CEMSjLog> ret;
	try 
	{
		apr_thread_mutex_lock( mutexCommands );
		ret = lstjLogs;
		lstjLogs.Clear();
		apr_thread_mutex_unlock( mutexCommands );
	}
	catch( ... ) 
	{
		apr_thread_mutex_unlock( mutexCommands );
		throw;
	}

	return ret;
}