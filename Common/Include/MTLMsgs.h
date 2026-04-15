/********************************************************************
*	Module:			MTLMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for MTL
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 Oct 8		jb	start 

********************************************************************/
#ifndef INC_MTLMSGS
#define INC_MTLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values layed out as follows:
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
// MessageId: EMS_MTL_BASE_CODE
//
// MessageText:
//
//  EMS MTL Error
//
#define EMS_MTL_BASE_CODE                ((EMS_RESULT)0x0004B600L)

//
// MessageId: EMS_MTL_EXCEPTION
//
// MessageText:
//
//  EMS MTL exception has occurred:  %1
//
#define EMS_MTL_EXCEPTION                ((EMS_RESULT)0x8004B601L)

//
// MessageId: EMS_MTL_SIT_NOT_ALLOWED
//
// MessageText:
//
//  EMS MTL Error:  SIT message sequence %1 of type %2 from %3 to %4 not permitted.
//
#define EMS_MTL_SIT_NOT_ALLOWED          ((EMS_RESULT)0x8004B602L)

//
// MessageId: EMS_MTL_BIN_NOT_ALLOWED
//
// MessageText:
//
//  EMS MTL Error:  Binary message file %1 of type %2 from %3 to %4 not permitted.
//
#define EMS_MTL_BIN_NOT_ALLOWED          ((EMS_RESULT)0x8004B603L)

//
// MessageId: EMS_MTL_SOAP_CLIENT_EXCEPTION
//
// MessageText:
//
//  EMS MTL Error:  SOAP Client error code %1, Reason: %2, Detail: %3.
//
#define EMS_MTL_SOAP_CLIENT_EXCEPTION    ((EMS_RESULT)0x8004B604L)

//
// MessageId: EMS_MTL_CONFIG_TWO_KEYS
//
// MessageText:
//
//  EMS MTL Error:  Could not retrieve configuration value for Group %1:%2, Key %3 or %4.
//
#define EMS_MTL_CONFIG_TWO_KEYS          ((EMS_RESULT)0x8004B605L)

//
// MessageId: EMS_MTL_NO_ROUTE_FOUND
//
// MessageText:
//
//  EMS MTL Error:  Configuration data for a route between %1 and %2 could not be found.
//
#define EMS_MTL_NO_ROUTE_FOUND           ((EMS_RESULT)0x8004B606L)

//
// MessageId: EMS_MTL_CFG_UNKNOWN_MSG_TYPE
//
// MessageText:
//
//  EMS MTL Error:  An unknown message type was read from configuration:  %1.
//
#define EMS_MTL_CFG_UNKNOWN_MSG_TYPE     ((EMS_RESULT)0x8004B607L)

//
// MessageId: EMS_MTL_CFG_OUT_DIR
//
// MessageText:
//
//  EMS MTL Error:  The Send directory could not be obtained from the configuration.
//
#define EMS_MTL_CFG_OUT_DIR              ((EMS_RESULT)0x8004B608L)

//
// MessageId: EMS_MTL_CFG_SHORT_NAME
//
// MessageText:
//
//  EMS MTL Error:  The Cospas-Sarsat short name associated with identifier %1 could not be found in the configuration.
//
#define EMS_MTL_CFG_SHORT_NAME           ((EMS_RESULT)0x8004B609L)

//
// MessageId: EMS_MTL_INVALID_MAX_SARR_SATELLITES
//
// MessageText:
//
//  EMS MTL Error:  The configured value for maximum satellites in a single SARR calibration message must be at least 1.  The value is %1.
//
#define EMS_MTL_INVALID_MAX_SARR_SATELLITES ((EMS_RESULT)0x8004B60AL)

//
// MessageId: EMS_MTL_SOAP_CLIENT_FAULT
//
// MessageText:
//
//  EMS MTL Error:  A SOAP client fault has occurred.
//
#define EMS_MTL_SOAP_CLIENT_FAULT        ((EMS_RESULT)0x8004B60BL)

//
// MessageId: EMS_MTL_SOAP_SERVER_FAULT
//
// MessageText:
//
//  EMS MTL Error:  A SOAP server fault has occurred.
//
#define EMS_MTL_SOAP_SERVER_FAULT        ((EMS_RESULT)0x8004B60CL)

//
// MessageId: EMS_MTL_SOAP_TAG_MISMATCH
//
// MessageText:
//
//  EMS MTL Error:  A SOAP message XML element didn't correspond to anything expected.
//
#define EMS_MTL_SOAP_TAG_MISMATCH        ((EMS_RESULT)0x8004B60DL)

//
// MessageId: EMS_MTL_SOAP_TYPE_MISMATCH
//
// MessageText:
//
//  EMS MTL Error:  A SOAP message XML schema type mismatch was encountered.
//
#define EMS_MTL_SOAP_TYPE_MISMATCH       ((EMS_RESULT)0x8004B60EL)

//
// MessageId: EMS_MTL_SOAP_SYNTAX_ERROR
//
// MessageText:
//
//  EMS MTL Error:  A SOAP message XML syntax error occurred on the input.
//
#define EMS_MTL_SOAP_SYNTAX_ERROR        ((EMS_RESULT)0x8004B60FL)

//
// MessageId: EMS_MTL_SOAP_NO_TAG
//
// MessageText:
//
//  EMS MTL Error:  A SOAP message beginning of an element expected, but not found.
//
#define EMS_MTL_SOAP_NO_TAG              ((EMS_RESULT)0x8004B610L)

//
// MessageId: EMS_MTL_SOAP_IOB
//
// MessageText:
//
//  EMS MTL Error:  A SOAP processor array index is out of bounds.
//
#define EMS_MTL_SOAP_IOB                 ((EMS_RESULT)0x8004B611L)

//
// MessageId: EMS_MTL_SOAP_MUSTUNDERSTAND
//
// MessageText:
//
//  EMS MTL Error:  A SOAP element configured as "must understand" needs to be ignored.
//
#define EMS_MTL_SOAP_MUSTUNDERSTAND      ((EMS_RESULT)0x8004B612L)

//
// MessageId: EMS_MTL_SOAP_NAMESPACE
//
// MessageText:
//
//  EMS MTL Error:  A SOAP namespace name mismatch has occurred.
//
#define EMS_MTL_SOAP_NAMESPACE           ((EMS_RESULT)0x8004B613L)

//
// MessageId: EMS_MTL_SOAP_OBJ_MISMATCH
//
// MessageText:
//
//  EMS MTL Error:  The SOAP processor has encountered a mismatch in the size and/or shape of an object.
//
#define EMS_MTL_SOAP_OBJ_MISMATCH        ((EMS_RESULT)0x8004B614L)

//
// MessageId: EMS_MTL_SOAP_ERROR
//
// MessageText:
//
//  EMS MTL Trace:  A SOAP error was returned to the client.  Error code = %1.
//
#define EMS_MTL_SOAP_ERROR               ((EMS_RESULT)0x8004B615L)

//
// MessageId: EMS_MTL_SOAP_CLIENT_ERROR
//
// MessageText:
//
//  EMS MTL Trace:  A SOAP error was encountered on the client:  %1.
//
#define EMS_MTL_SOAP_CLIENT_ERROR        ((EMS_RESULT)0x8004B616L)

//
// MessageId: EMS_MTL_SOAP_UNKNOWN_ERROR
//
// MessageText:
//
//  EMS MTL Trace:  An unknown error was returned to the SOAP client.
//
#define EMS_MTL_SOAP_UNKNOWN_ERROR       ((EMS_RESULT)0x8004B617L)

//
// MessageId: EMS_MTL_SIT_OUTPUTFILE
//
// MessageText:
//
//  EMS MTL Trace:  Writing outgoing SIT message to %1.
//
#define EMS_MTL_SIT_OUTPUTFILE           ((EMS_RESULT)0x0004B618L)

//
// MessageId: EMS_MTL_SIT_OUTDIR
//
// MessageText:
//
//  EMS MTL Trace:  Writing outgoing SIT message to directory %1.
//
#define EMS_MTL_SIT_OUTDIR               ((EMS_RESULT)0x0004B619L)

//
// MessageId: EMS_MTL_SIT_SRC_NAME
//
// MessageText:
//
//  EMS MTL Trace:  Outgoing SIT message source name is %1.
//
#define EMS_MTL_SIT_SRC_NAME             ((EMS_RESULT)0x0004B61AL)

//
// MessageId: EMS_MTL_SIT_DEST_NAME
//
// MessageText:
//
//  EMS MTL Trace:  Outgoing SIT message destination name is %1.
//
#define EMS_MTL_SIT_DEST_NAME            ((EMS_RESULT)0x0004B61BL)

//
// MessageId: EMS_MTL_CONFIG_RTE_OUT_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  Unable to retrieve outgoing configuration information for routing from %1 to %2.
//
#define EMS_MTL_CONFIG_RTE_OUT_NOT_FOUND ((EMS_RESULT)0x8004B61CL)

//
// MessageId: EMS_MTL_ALERT_UNKNOWN_TYPE
//
// MessageText:
//
//  EMS MTL Error:  Unable to create alert SIT message type %1.
//
#define EMS_MTL_ALERT_UNKNOWN_TYPE       ((EMS_RESULT)0x8004B61DL)

//
// MessageId: EMS_MTL_ALERT_SIT_NOT_CONFIGURED
//
// MessageText:
//
//  EMS MTL Error:  Requested SIT message type %1 is not configured for destination %2.
//
#define EMS_MTL_ALERT_SIT_NOT_CONFIGURED ((EMS_RESULT)0x8004B61EL)

//
// MessageId: EMS_MTL_ALERT_NO_DESTINATIONS_CONFIGURED
//
// MessageText:
//
//  EMS MTL Trace:  No Alert destinations are configured.
//
#define EMS_MTL_ALERT_NO_DESTINATIONS_CONFIGURED ((EMS_RESULT)0x0004B61FL)

//
// MessageId: EMS_MTL_CONFIG_ROUTE_NAME_SYNTAX
//
// MessageText:
//
//  EMS MTL Error:  An invalid route name syntax was encountered:  %1.
//
#define EMS_MTL_CONFIG_ROUTE_NAME_SYNTAX ((EMS_RESULT)0x8004B620L)

//
// MessageId: EMS_MTL_CONFIG_NULL
//
// MessageText:
//
//  EMS MTL Error:  Unable to access the MTL configuration object.
//
#define EMS_MTL_CONFIG_NULL              ((EMS_RESULT)0x8004B621L)

//
// MessageId: EMS_MTL_SOAP_SERVER_INIT
//
// MessageText:
//
//  EMS MTL Trace:  Socket connection successful.  %1.
//
#define EMS_MTL_SOAP_SERVER_INIT         ((EMS_RESULT)0x0004B622L)

//
// MessageId: EMS_MTL_SOAP_CONNECT_RECVD
//
// MessageText:
//
//  EMS MTL Trace:  Accepted connection from IP: %1.
//
#define EMS_MTL_SOAP_CONNECT_RECVD       ((EMS_RESULT)0x0004B623L)

//
// MessageId: EMS_MTL_SOAP_REQUEST_SERVED
//
// MessageText:
//
//  EMS MTL Trace:  SOAP Request served on handler thread %1.
//
#define EMS_MTL_SOAP_REQUEST_SERVED      ((EMS_RESULT)0x0004B624L)

//
// MessageId: EMS_MTL_SOAP_PORT_BIND_ERROR
//
// MessageText:
//
//  EMS MTL Error:  SOAP Server could not bind to incoming message port %1.
//
#define EMS_MTL_SOAP_PORT_BIND_ERROR     ((EMS_RESULT)0x8004B625L)

//
// MessageId: EMS_MTL_SERVICE_STARTED
//
// MessageText:
//
//  EMS Message Translation Layer (MTL) Service started
//
#define EMS_MTL_SERVICE_STARTED          ((EMS_RESULT)0x0004B626L)

//
// MessageId: EMS_MTL_SERVICE_START_FAILED
//
// MessageText:
//
//  EMS Message Translation Layer (MTL) Service failed to start with error %1.
//
#define EMS_MTL_SERVICE_START_FAILED     ((EMS_RESULT)0x8004B627L)

//
// MessageId: EMS_MTL_SERVICE_STOP
//
// MessageText:
//
//  EMS Message Translation Layer (MTL) Service stopped
//
#define EMS_MTL_SERVICE_STOP             ((EMS_RESULT)0x0004B628L)

//
// MessageId: EMS_SOAP_SERVICE_STARTED
//
// MessageText:
//
//  EMS SOAP Service started
//
#define EMS_SOAP_SERVICE_STARTED         ((EMS_RESULT)0x0004B629L)

//
// MessageId: EMS_SOAP_SERVICE_START_FAILED
//
// MessageText:
//
//  EMS SOAP Service failed to start with error %1.
//
#define EMS_SOAP_SERVICE_START_FAILED    ((EMS_RESULT)0x8004B62AL)

//
// MessageId: EMS_SOAP_SERVICE_STOP
//
// MessageText:
//
//  EMS SOAP Service stopped
//
#define EMS_SOAP_SERVICE_STOP            ((EMS_RESULT)0x0004B62BL)

//
// MessageId: EMS_MTL_SOAP_FATAL_ERROR
//
// MessageText:
//
//  EMS MTL Error:  Internal SOAP error.
//
#define EMS_MTL_SOAP_FATAL_ERROR         ((EMS_RESULT)0x8004B62CL)

//
// MessageId: EMS_MTL_SOAP_NO_METHOD
//
// MessageText:
//
//  EMS MTL Error:  SOAP skeleton error.  The skeleton cannot serve the method.
//
#define EMS_MTL_SOAP_NO_METHOD           ((EMS_RESULT)0x8004B62DL)

//
// MessageId: EMS_MTL_SOAP_GET_METHOD
//
// MessageText:
//
//  EMS MTL Error:  SOAP unsupported HTTP Get error.
//
#define EMS_MTL_SOAP_GET_METHOD          ((EMS_RESULT)0x8004B62EL)

//
// MessageId: EMS_MTL_SOAP_EOM
//
// MessageText:
//
//  EMS MTL Error:  SOAP out of memory error.
//
#define EMS_MTL_SOAP_EOM                 ((EMS_RESULT)0x8004B62FL)

//
// MessageId: EMS_MTL_SOAP_NULL
//
// MessageText:
//
//  EMS MTL Error:  The SOAP processor encountered an unexpected NULL value.
//
#define EMS_MTL_SOAP_NULL                ((EMS_RESULT)0x8004B630L)

//
// MessageId: EMS_MTL_SOAP_MULTI_ID
//
// MessageText:
//
//  EMS MTL Error:  The SOAP processor encountered multiple occurrences of the same element ID on the input.
//
#define EMS_MTL_SOAP_MULTI_ID            ((EMS_RESULT)0x8004B631L)

//
// MessageId: EMS_MTL_SOAP_MISSING_ID
//
// MessageText:
//
//  EMS MTL Error:  The SOAP processor encountered a missing element ID for an HREF on the input.
//
#define EMS_MTL_SOAP_MISSING_ID          ((EMS_RESULT)0x8004B632L)

//
// MessageId: EMS_MTL_SOAP_HREF
//
// MessageText:
//
//  EMS MTL Error:  The SOAP processor encountered an object reference incompatible with the object refered to.
//
#define EMS_MTL_SOAP_HREF                ((EMS_RESULT)0x8004B633L)

//
// MessageId: EMS_MTL_SOAP_TCP_ERROR
//
// MessageText:
//
//  EMS MTL Error:  A TCP connection error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_TCP_ERROR           ((EMS_RESULT)0x8004B634L)

//
// MessageId: EMS_MTL_SOAP_HTTP_ERROR
//
// MessageText:
//
//  EMS MTL Error:  An HTTP error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_HTTP_ERROR          ((EMS_RESULT)0x8004B635L)

//
// MessageId: EMS_MTL_SOAP_SSL_ERROR
//
// MessageText:
//
//  EMS MTL Error:  An SSL error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_SSL_ERROR           ((EMS_RESULT)0x8004B636L)

//
// MessageId: EMS_MTL_SOAP_ZLIB_ERROR
//
// MessageText:
//
//  EMS MTL Error:  A ZLIB error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_ZLIB_ERROR          ((EMS_RESULT)0x8004B637L)

//
// MessageId: EMS_MTL_SOAP_DIME_ERROR
//
// MessageText:
//
//  EMS MTL Error:  A DIME parsing error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_DIME_ERROR          ((EMS_RESULT)0x8004B638L)

//
// MessageId: EMS_MTL_SOAP_EOD
//
// MessageText:
//
//  EMS MTL Error:  An end of DIME error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_EOD                 ((EMS_RESULT)0x8004B639L)

//
// MessageId: EMS_MTL_SOAP_VERSION_MISMATCH
//
// MessageText:
//
//  EMS MTL Error:  A SOAP version mismatch or no SOAP message error has occurred.
//
#define EMS_MTL_SOAP_VERSION_MISMATCH    ((EMS_RESULT)0x8004B63AL)

//
// MessageId: EMS_MTL_SOAP_DIME_MISMATCH
//
// MessageText:
//
//  EMS MTL Error:  A SOAP DIME version mismatch has occurred.
//
#define EMS_MTL_SOAP_DIME_MISMATCH       ((EMS_RESULT)0x8004B63BL)

//
// MessageId: EMS_MTL_SOAP_PLUGIN_ERROR
//
// MessageText:
//
//  EMS MTL Error:  Failure registering SOAP plugin.
//
#define EMS_MTL_SOAP_PLUGIN_ERROR        ((EMS_RESULT)0x8004B63CL)

//
// MessageId: EMS_MTL_SOAP_EOF
//
// MessageText:
//
//  EMS MTL Error:  SOAP error occurred.  Unexpected end of file, no input, or timeout receiving data.
//
#define EMS_MTL_SOAP_EOF                 ((EMS_RESULT)0x8004B63DL)

//
// MessageId: EMS_MTL_CLIENT_RESOURCE_TO_SIT_ERROR
//
// MessageText:
//
//  EMS MTL Error:  The MTL Client has no mapping from the resource identifier %1 to a SIT message type.
//
#define EMS_MTL_CLIENT_RESOURCE_TO_SIT_ERROR ((EMS_RESULT)0x8004B63EL)

//
// MessageId: EMS_MTL_SOAP_SERVER_THREADS
//
// MessageText:
//
//  EMS SOAP Server is initializing %1 handler threads.
//
#define EMS_MTL_SOAP_SERVER_THREADS      ((EMS_RESULT)0x0004B63FL)

//
// MessageId: EMS_MTL_SIT_SERVER_NO_SHORT_NAME
//
// MessageText:
//
//  EMS MTL Error:  Cannot find the short name for lut %1.
//
#define EMS_MTL_SIT_SERVER_NO_SHORT_NAME ((EMS_RESULT)0x8004B640L)

//
// MessageId: EMS_MTL_SOAP_NO_HANDLER_THREAD
//
// MessageText:
//
//  EMS MTL Trace:  Could not obtain an available SOAP handler thread.
//
#define EMS_MTL_SOAP_NO_HANDLER_THREAD   ((EMS_RESULT)0x0004B641L)

//
// MessageId: EMS_MTL_SOAP_INIT_HANDLER_THREAD
//
// MessageText:
//
//  EMS MTL Trace:  Running SOAP handler thread %1.
//
#define EMS_MTL_SOAP_INIT_HANDLER_THREAD ((EMS_RESULT)0x0004B642L)

//
// MessageId: EMS_MTL_BINARY_UNKNOWN
//
// MessageText:
//
//  EMS MTL Error:  Unknown error in the binary server.
//
#define EMS_MTL_BINARY_UNKNOWN           ((EMS_RESULT)0x8004B643L)

//
// MessageId: EMS_MTL_SIT_SERVER_UNKNOWN
//
// MessageText:
//
//  EMS MTL Error:  Unknown error in the SIT server.
//
#define EMS_MTL_SIT_SERVER_UNKNOWN       ((EMS_RESULT)0x8004B644L)

//
// MessageId: EMS_MTL_TRACK_INSTALL_TIME_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  Unable to find associated pass schedule record for pass summary record.  AOS time will be used for install time on summary record.
//
#define EMS_MTL_TRACK_INSTALL_TIME_NOT_FOUND ((EMS_RESULT)0x8004B645L)

//
// MessageId: EMS_MTL_SIT_SENDER
//
// MessageText:
//
//  EMS MTL Info:  Transmission of SIT message file %1 was invoked by user %2.
//
#define EMS_MTL_SIT_SENDER               ((EMS_RESULT)0x8004B646L)

//
// MessageId: EMS_MTL_INVALID_MSG_TYPE
//
// MessageText:
//
//  EMS MTL Error:  A request to send a message via an unrecognized type was encountered.
//
#define EMS_MTL_INVALID_MSG_TYPE         ((EMS_RESULT)0x8004B647L)

//
// MessageId: EMS_MTL_NOT_SUPPORTED_MSG_TYPE
//
// MessageText:
//
//  EMS MTL Error:  An attempt was made to send a message via an unsupported message type.
//
#define EMS_MTL_NOT_SUPPORTED_MSG_TYPE   ((EMS_RESULT)0x8004B648L)

//
// MessageId: EMS_MTL_UNKNOWN_ENDPOINT
//
// MessageText:
//
//  EMS MTL Error:  Unable to retrieve the SOAP endpoint from configuration for a route.
//
#define EMS_MTL_UNKNOWN_ENDPOINT         ((EMS_RESULT)0x8004B649L)

//
// MessageId: EMS_MTL_UNSUPPORTED_INPUT_TYPE
//
// MessageText:
//
//  EMS MTL Error:  Data was received in an unsupported format.
//
#define EMS_MTL_UNSUPPORTED_INPUT_TYPE   ((EMS_RESULT)0x8004B64AL)

//
// MessageId: EMS_MTL_ALERT_SUPPRESSED
//
// MessageText:
//
//  EMS MTL Info:  %1 alerts have been suppressed.
//
#define EMS_MTL_ALERT_SUPPRESSED         ((EMS_RESULT)0x0004B64BL)

//
// MessageId: EMS_MTL_MISSING_ALIAS
//
// MessageText:
//
//  EMS MTL Error:  Route %1 is missing configuration of an alias for one or both endpoints.
//
#define EMS_MTL_MISSING_ALIAS            ((EMS_RESULT)0x8004B64CL)

//
// MessageId: EMS_MTL_RTE_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  The requested route, %1, could not be found in the configuration.
//
#define EMS_MTL_RTE_NOT_FOUND            ((EMS_RESULT)0x8004B64DL)

//
// MessageId: EMS_MTL_SIT_CLIENT_NO_WRAPPER_DEFINITION
//
// MessageText:
//
//  EMS MTL Error:  A definition for the wrapper SIT message type <%1> could not be found.
//
#define EMS_MTL_SIT_CLIENT_NO_WRAPPER_DEFINITION ((EMS_RESULT)0x8004B64EL)

//
// MessageId: EMS_MTL_NO_SECURITY_TOKEN_FIELD_DEFINED
//
// MessageText:
//
//  EMS MTL Error:  Could not retrieve the SIT message security token field name from configuration.  Searching for key <%1>.<%2>.  CM returned error <%3>.
//
#define EMS_MTL_NO_SECURITY_TOKEN_FIELD_DEFINED ((EMS_RESULT)0x8004B64FL)

//
// MessageId: EMS_MTL_CLIENT_ROUTE_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  MTL Client could not find route with identifier <%1> in configuration.
//
#define EMS_MTL_CLIENT_ROUTE_NOT_FOUND   ((EMS_RESULT)0x8004B650L)

//
// MessageId: EMS_MTL_CLIENT_SOURCE_END_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  While determining transmission message type, the MTL client could not find the sender's endpoint in the specified route.  Sender ID = <%1>, Specified Route = <%2>.
//
#define EMS_MTL_CLIENT_SOURCE_END_NOT_FOUND ((EMS_RESULT)0x8004B651L)

//
// MessageId: EMS_MTL_SIT_CLIENT_TRANS_TABLE_NOT_FOUND
//
// MessageText:
//
//  EMS MTL Error:  The translation table <%1> specified in route <%2> could not be found in the configuration.
//
#define EMS_MTL_SIT_CLIENT_TRANS_TABLE_NOT_FOUND ((EMS_RESULT)0x8004B652L)

//
// MessageId: EMS_MTL_SIT_CLIENT_NO_INSTANCE_FOUND
//
// MessageText:
//
//  EMS MTL Error:  A referenced instance of name <%1> could not be found in the SIT Message Definition.  There may be an error in the SIT Message Definition.
//
#define EMS_MTL_SIT_CLIENT_NO_INSTANCE_FOUND ((EMS_RESULT)0x8004B653L)

//
// MessageId: EMS_MTL_CONFIGURATION_NO_TRANS_TABLE
//
// MessageText:
//
//  EMS MTL Error:  Could not find the translation table named <%1> in the configuration.  A route may may be configured incorrectly.
//
#define EMS_MTL_CONFIGURATION_NO_TRANS_TABLE ((EMS_RESULT)0x8004B654L)

//
// MessageId: EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE
//
// MessageText:
//
//  EMS MTL Error:  Could not find the entry <%1> in the translation table named <%2> in the configuration.  A route may may be configured incorrectly or the translation table is incomplete.
//
#define EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE ((EMS_RESULT)0x8004B655L)

//
// MessageId: EMS_MTL_SIT_CLIENT_XMIT_TIME_IDENTIFIER_NAME_RETRIEVE_ERROR
//
// MessageText:
//
//  EMS MTL Error:  The SIT Client was unable to obtain the identifier of the transmit time message field.
//
#define EMS_MTL_SIT_CLIENT_XMIT_TIME_IDENTIFIER_NAME_RETRIEVE_ERROR ((EMS_RESULT)0x8004B656L)

//
// MessageId: EMS_MTL_SIT_CLIENT_XMIT_TIME_FIELD_OBJECT_RETRIEVE_ERROR
//
// MessageText:
//
//  EMS MTL Error:  The SIT Client was unable to obtain the <%1> message field from the object model.
//
#define EMS_MTL_SIT_CLIENT_XMIT_TIME_FIELD_OBJECT_RETRIEVE_ERROR ((EMS_RESULT)0x8004B657L)

//
// MessageId: EMS_MTL_UDP_CONNECT_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client could not connect to the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_CONNECT_ERROR        ((EMS_RESULT)0x8004B658L)

//
// MessageId: EMS_MTL_UDP_INIT_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client could not be initialized.
//
#define EMS_MTL_UDP_INIT_ERROR           ((EMS_RESULT)0x8004B659L)

//
// MessageId: EMS_MTL_UDP_SEND_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client could not send data to the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_SEND_ERROR           ((EMS_RESULT)0x8004B65AL)

//
// MessageId: EMS_MTL_UDP_RECV_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client could not recive data from the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_RECV_ERROR           ((EMS_RESULT)0x8004B65BL)

//
// MessageId: EMS_MTL_UDP_DISCONNECT_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client disconnect error; LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_DISCONNECT_ERROR     ((EMS_RESULT)0x8004B65CL)

//
// MessageId: EMS_MTL_UDP_SETPARAM_ERROR
//
// MessageText:
//
//  EMS MTL Error:  UDP Client could not set the parameters.
//
#define EMS_MTL_UDP_SETPARAM_ERROR       ((EMS_RESULT)0x8004B65DL)

//
// MessageId: EMS_MTL_RTE_NOT_FOUND_B
//
// MessageText:
//
//  EMS MTL Error:  The requested route, between <%1> and <%2>, could not be found in the configuration.
//
#define EMS_MTL_RTE_NOT_FOUND_B          ((EMS_RESULT)0x8004B65EL)

//
// MessageId: EMS_MTL_SOAP_SERVER_INIT_STATS
//
// MessageText:
//
//  EMS MTL Trace:  Socket connection successful.  Listening on port %1.  Master socket:  %2  Max backlog queue size:  %3.
//
#define EMS_MTL_SOAP_SERVER_INIT_STATS   ((EMS_RESULT)0x0004B65FL)

//
// MessageId: EMS_MTL_EXCEPTION_UNHANDLED
//
// MessageText:
//
//  EMS MTL unhandled exception has occurred.
//
#define EMS_MTL_EXCEPTION_UNHANDLED      ((EMS_RESULT)0x8004B660L)

//
// MessageId: EMS_MTL_UDP_SERVER_LISTENING
//
// MessageText:
//
//  EMS MTL Info:  UDP Server listening at IP <%1>, port <%2>.
//
#define EMS_MTL_UDP_SERVER_LISTENING     ((EMS_RESULT)0x0004B661L)

//
// MessageId: EMS_MTL_UDP_SERVER_LISTENING_FAILURE
//
// MessageText:
//
//  EMS MTL Error:  UDP Server failed to bind socket for listening at IP <%1>, port <%2>.  Socket error code is <%3>.
//
#define EMS_MTL_UDP_SERVER_LISTENING_FAILURE ((EMS_RESULT)0x8004B662L)

//
// MessageId: EMS_MTL_UDP_SERVER_RECEIVED
//
// MessageText:
//
//  EMS MTL Trace:  UDP Server received data or connection attempt from IP <%1>, port <%2>.
//
#define EMS_MTL_UDP_SERVER_RECEIVED      ((EMS_RESULT)0x0004B663L)

//
// MessageId: EMS_MTL_UDP_SERVER_NEW_CONNECTION
//
// MessageText:
//
//  EMS MTL Info:  New connection established on UDP Server from IP <%1>, LUT ID <%2>.  Server will respond to client's port <%3>.  <%4> of maximum <%5> connections in use.
//
#define EMS_MTL_UDP_SERVER_NEW_CONNECTION ((EMS_RESULT)0x0004B664L)

//
// MessageId: EMS_MTL_UDP_SERVER_CONNECTION_LIMIT_REACHED
//
// MessageText:
//
//  EMS MTL Info:  UDP Server received a connection attempt from IP <%1>, LUT ID <%2>, but client connection limit of <%3> has been reached.
//
#define EMS_MTL_UDP_SERVER_CONNECTION_LIMIT_REACHED ((EMS_RESULT)0x8004B665L)

//
// MessageId: EMS_MTL_UDP_SERVER_CONNECTION_CLOSED
//
// MessageText:
//
//  EMS MTL Info:  UDP Server closing connection to IP <%1>, port <%2>, LUT ID <%3>.  <%4> of maximum <%5> connections in use.
//
#define EMS_MTL_UDP_SERVER_CONNECTION_CLOSED ((EMS_RESULT)0x0004B666L)

//
// MessageId: EMS_MTL_SOAP_SERVER_AUDIO_NEW_CONNECTION
//
// MessageText:
//
//  EMS MTL Info:  New audio data connection established on SOAP Server from IP <%1>, LUT ID <%2>.
//
#define EMS_MTL_SOAP_SERVER_AUDIO_NEW_CONNECTION ((EMS_RESULT)0x0004B667L)

//
// MessageId: EMS_MTL_SOAP_SERVER_AUDIO_CONNECTION_CLOSED
//
// MessageText:
//
//  EMS MTL Info:  UDP Server closing connection to IP <%1>, LUT ID <%2>.
//
#define EMS_MTL_SOAP_SERVER_AUDIO_CONNECTION_CLOSED ((EMS_RESULT)0x0004B668L)


#endif // INC_MTLMSGS
