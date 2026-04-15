/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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
#ifndef INC_WSMSGS
#define INC_WSMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: EMS_WS_BASE_CODE
//
// MessageText:
//
// EMS Web Service host error.
//
#define EMS_WS_BASE_CODE                 ((EMS_RESULT)0x0004E100L)

//
// MessageId: EMS_WS_HOST_STARTED
//
// MessageText:
//
// EMS Web Service (%1) has started.
//
#define EMS_WS_HOST_STARTED              ((EMS_RESULT)0x0004E101L)

//
// MessageId: EMS_WS_HOST_START_FAILED
//
// MessageText:
//
// EMS Web Service (%1) failed to start with error code %2.
//
#define EMS_WS_HOST_START_FAILED         ((EMS_RESULT)0x8004E102L)

//
// MessageId: EMS_WS_HOST_STOPPED
//
// MessageText:
//
// EMS Web Service (%1) has stopped.
//
#define EMS_WS_HOST_STOPPED              ((EMS_RESULT)0x0004E103L)

//
// MessageId: EMS_WS_HOST_BIND_FAILURE
//
// MessageText:
//
// EMS Web Service host failed to bind.  Host=%1, Port=%2.
//
#define EMS_WS_HOST_BIND_FAILURE         ((EMS_RESULT)0x8004E104L)

//
// MessageId: EMS_WS_HOST_NO_WS_CONFIG
//
// MessageText:
//
// EMS Web Service host failed to find a web service plugin configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
//
#define EMS_WS_HOST_NO_WS_CONFIG         ((EMS_RESULT)0x8004E105L)

//
// MessageId: EMS_WS_PLUGIN_USER_NOT_FOUND
//
// MessageText:
//
// EMS Web Service (%1) could not find user (%2) in the access control list.
//
#define EMS_WS_PLUGIN_USER_NOT_FOUND     ((EMS_RESULT)0x8004E106L)

//
// MessageId: EMS_WS_PLUGIN_NO_USER
//
// MessageText:
//
// EMS Web Service (%1) did not find a username in a received SOAP message.  Authentication is enabled and usernames are required.
//
#define EMS_WS_PLUGIN_NO_USER            ((EMS_RESULT)0x8004E107L)

//
// MessageId: EMS_WS_PLUGIN_PWD_VERIF_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed to verify user (%2) with the supplied password.  The username or password is incorrect.
//
#define EMS_WS_PLUGIN_PWD_VERIF_FAILURE  ((EMS_RESULT)0x8004E108L)

//
// MessageId: EMS_WS_PLUGIN_NO_USERS_FILE
//
// MessageText:
//
// EMS Web Service (%1) could not load user account information while authenticating.  A user accounts file was not configured.
//
#define EMS_WS_PLUGIN_NO_USERS_FILE      ((EMS_RESULT)0x8004E109L)

//
// MessageId: EMS_WS_PLUGIN_NO_USERNAME
//
// MessageText:
//
// EMS Web Service (%1) encountered a missing username while loading the user accounts.
//
#define EMS_WS_PLUGIN_NO_USERNAME        ((EMS_RESULT)0x8004E10AL)

//
// MessageId: EMS_WS_HOST_CRYPTO_INIT_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to setup the cryptography thread for SSL support.
//
#define EMS_WS_HOST_CRYPTO_INIT_FAILURE  ((EMS_RESULT)0x8004E10BL)

//
// MessageId: EMS_WS_HOST_SSL_NO_KEY_FILE
//
// MessageText:
//
// EMS Web Service (%1) does not have a configured SSL key file.
//
#define EMS_WS_HOST_SSL_NO_KEY_FILE      ((EMS_RESULT)0x8004E10CL)

//
// MessageId: EMS_WS_HOST_SSL_NO_KEY_PWD
//
// MessageText:
//
// EMS Web Service (%1) does not have a configured SSL key file password.
//
#define EMS_WS_HOST_SSL_NO_KEY_PWD       ((EMS_RESULT)0x8004E10DL)

//
// MessageId: EMS_WS_HOST_SSL_CTX_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to set the SSL server context.
//
#define EMS_WS_HOST_SSL_CTX_FAILURE      ((EMS_RESULT)0x8004E10EL)

//
// MessageId: EMS_WS_HOST_ATTACH_OPEN_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to open the file %2 for attachment to a respone message.
//
#define EMS_WS_HOST_ATTACH_OPEN_FAILURE  ((EMS_RESULT)0x8004E10FL)


#endif // INC_WSMSGS
