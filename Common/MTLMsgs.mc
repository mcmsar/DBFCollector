;/********************************************************************
;*	Module:			MTLMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for MTL
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;
;/*******************************************************************
;
;  Revision Record
;
;	Rev	Date			Auth	Changes
;	===	====			====	=======
;
;	0.0	2002 Oct 8		jb	start 
;
;********************************************************************/
;#ifndef INC_MTLMSGS
;#define INC_MTLMSGS
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;

MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
	ErrWarn=0x2
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xB600 SymbolicName=EMS_MTL_BASE_CODE Facility=ITF
Language=English
EMS MTL Error
.
MessageId=+1 SymbolicName=EMS_MTL_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS MTL exception has occurred:  %1
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_NOT_ALLOWED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SIT message sequence %1 of type %2 from %3 to %4 not permitted.
.
MessageId=+1 SymbolicName=EMS_MTL_BIN_NOT_ALLOWED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Binary message file %1 of type %2 from %3 to %4 not permitted.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_CLIENT_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP Client error code %1, Reason: %2, Detail: %3.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIG_TWO_KEYS Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Could not retrieve configuration value for Group %1:%2, Key %3 or %4.
.
MessageId=+1 SymbolicName=EMS_MTL_NO_ROUTE_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Configuration data for a route between %1 and %2 could not be found.
.
MessageId=+1 SymbolicName=EMS_MTL_CFG_UNKNOWN_MSG_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An unknown message type was read from configuration:  %1.
.
MessageId=+1 SymbolicName=EMS_MTL_CFG_OUT_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The Send directory could not be obtained from the configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_CFG_SHORT_NAME Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The Cospas-Sarsat short name associated with identifier %1 could not be found in the configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_INVALID_MAX_SARR_SATELLITES Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The configured value for maximum satellites in a single SARR calibration message must be at least 1.  The value is %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_CLIENT_FAULT Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP client fault has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_FAULT Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP server fault has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_TAG_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP message XML element didn't correspond to anything expected.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_TYPE_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP message XML schema type mismatch was encountered.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SYNTAX_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP message XML syntax error occurred on the input.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_NO_TAG Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP message beginning of an element expected, but not found.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_IOB Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP processor array index is out of bounds.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_MUSTUNDERSTAND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP element configured as "must understand" needs to be ignored.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_NAMESPACE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP namespace name mismatch has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_OBJ_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SOAP processor has encountered a mismatch in the size and/or shape of an object.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Trace:  A SOAP error was returned to the client.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_CLIENT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Trace:  A SOAP error was encountered on the client:  %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_UNKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Trace:  An unknown error was returned to the SOAP client.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_OUTPUTFILE Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Writing outgoing SIT message to %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_OUTDIR Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Writing outgoing SIT message to directory %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_SRC_NAME Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Outgoing SIT message source name is %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_DEST_NAME Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Outgoing SIT message destination name is %1.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIG_RTE_OUT_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unable to retrieve outgoing configuration information for routing from %1 to %2.
.
MessageId=+1 SymbolicName=EMS_MTL_ALERT_UNKNOWN_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unable to create alert SIT message type %1.
.
MessageId=+1 SymbolicName=EMS_MTL_ALERT_SIT_NOT_CONFIGURED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Requested SIT message type %1 is not configured for destination %2.
.
MessageId=+1 SymbolicName=EMS_MTL_ALERT_NO_DESTINATIONS_CONFIGURED Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  No Alert destinations are configured.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIG_ROUTE_NAME_SYNTAX Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An invalid route name syntax was encountered:  %1.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIG_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unable to access the MTL configuration object.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_INIT Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Socket connection successful.  %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_CONNECT_RECVD Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Accepted connection from IP: %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_REQUEST_SERVED Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  SOAP Request served on handler thread %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_PORT_BIND_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP Server could not bind to incoming message port %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SERVICE_STARTED Severity=Success Facility=ITF
Language=English
EMS Message Translation Layer (MTL) Service started
.
MessageId=+1 SymbolicName=EMS_MTL_SERVICE_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Message Translation Layer (MTL) Service failed to start with error %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Message Translation Layer (MTL) Service stopped
.
MessageId=+1 SymbolicName=EMS_SOAP_SERVICE_STARTED Severity=Success Facility=ITF
Language=English
EMS SOAP Service started
.
MessageId=+1 SymbolicName=EMS_SOAP_SERVICE_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS SOAP Service failed to start with error %1.
.
MessageId=+1 SymbolicName=EMS_SOAP_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS SOAP Service stopped
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_FATAL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Internal SOAP error.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_NO_METHOD Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP skeleton error.  The skeleton cannot serve the method.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_GET_METHOD Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP unsupported HTTP Get error.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_EOM Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP out of memory error.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SOAP processor encountered an unexpected NULL value.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_MULTI_ID Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SOAP processor encountered multiple occurrences of the same element ID on the input.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_MISSING_ID Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SOAP processor encountered a missing element ID for an HREF on the input.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_HREF Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SOAP processor encountered an object reference incompatible with the object refered to.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_TCP_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A TCP connection error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_HTTP_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An HTTP error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SSL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An SSL error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_ZLIB_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A ZLIB error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_DIME_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A DIME parsing error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_EOD Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An end of DIME error occurred while attempting to send a SOAP message.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_VERSION_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP version mismatch or no SOAP message error has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_DIME_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A SOAP DIME version mismatch has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_PLUGIN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Failure registering SOAP plugin.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_EOF Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  SOAP error occurred.  Unexpected end of file, no input, or timeout receiving data.
.
MessageId=+1 SymbolicName=EMS_MTL_CLIENT_RESOURCE_TO_SIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The MTL Client has no mapping from the resource identifier %1 to a SIT message type.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_THREADS Severity=Success Facility=ITF
Language=English
EMS SOAP Server is initializing %1 handler threads.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_SERVER_NO_SHORT_NAME Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Cannot find the short name for lut %1.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_NO_HANDLER_THREAD Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Could not obtain an available SOAP handler thread.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_INIT_HANDLER_THREAD Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Running SOAP handler thread %1.
.
MessageId=+1 SymbolicName=EMS_MTL_BINARY_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unknown error in the binary server.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_SERVER_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unknown error in the SIT server.
.
MessageId=+1 SymbolicName=EMS_MTL_TRACK_INSTALL_TIME_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unable to find associated pass schedule record for pass summary record.  AOS time will be used for install time on summary record.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_SENDER Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Info:  Transmission of SIT message file %1 was invoked by user %2.
.
MessageId=+1 SymbolicName=EMS_MTL_INVALID_MSG_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A request to send a message via an unrecognized type was encountered.
.
MessageId=+1 SymbolicName=EMS_MTL_NOT_SUPPORTED_MSG_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  An attempt was made to send a message via an unsupported message type.
.
MessageId=+1 SymbolicName=EMS_MTL_UNKNOWN_ENDPOINT Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Unable to retrieve the SOAP endpoint from configuration for a route.
.
MessageId=+1 SymbolicName=EMS_MTL_UNSUPPORTED_INPUT_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Data was received in an unsupported format.
.
MessageId=+1 SymbolicName=EMS_MTL_ALERT_SUPPRESSED Severity=Success Facility=ITF
Language=English
EMS MTL Info:  %1 alerts have been suppressed.
.
MessageId=+1 SymbolicName=EMS_MTL_MISSING_ALIAS Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Route %1 is missing configuration of an alias for one or both endpoints.
.
MessageId=+1 SymbolicName=EMS_MTL_RTE_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The requested route, %1, could not be found in the configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_CLIENT_NO_WRAPPER_DEFINITION Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A definition for the wrapper SIT message type <%1> could not be found.
.
MessageId=+1 SymbolicName=EMS_MTL_NO_SECURITY_TOKEN_FIELD_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Could not retrieve the SIT message security token field name from configuration.  Searching for key <%1>.<%2>.  CM returned error <%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_CLIENT_ROUTE_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  MTL Client could not find route with identifier <%1> in configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_CLIENT_SOURCE_END_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  While determining transmission message type, the MTL client could not find the sender's endpoint in the specified route.  Sender ID = <%1>, Specified Route = <%2>.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_CLIENT_TRANS_TABLE_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The translation table <%1> specified in route <%2> could not be found in the configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_CLIENT_NO_INSTANCE_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  A referenced instance of name <%1> could not be found in the SIT Message Definition.  There may be an error in the SIT Message Definition.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIGURATION_NO_TRANS_TABLE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Could not find the translation table named <%1> in the configuration.  A route may may be configured incorrectly.
.
MessageId=+1 SymbolicName=EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  Could not find the entry <%1> in the translation table named <%2> in the configuration.  A route may may be configured incorrectly or the translation table is incomplete.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_CLIENT_XMIT_TIME_IDENTIFIER_NAME_RETRIEVE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SIT Client was unable to obtain the identifier of the transmit time message field.
.
MessageId=+1 SymbolicName=EMS_MTL_SIT_CLIENT_XMIT_TIME_FIELD_OBJECT_RETRIEVE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The SIT Client was unable to obtain the <%1> message field from the object model.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_CONNECT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client could not connect to the LUT <%1>, IP=<%2> Port=<%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_INIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client could not be initialized.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SEND_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client could not send data to the LUT <%1>, IP=<%2> Port=<%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_RECV_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client could not recive data from the LUT <%1>, IP=<%2> Port=<%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_DISCONNECT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client disconnect error; LUT <%1>, IP=<%2> Port=<%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SETPARAM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Client could not set the parameters.
.
MessageId=+1 SymbolicName=EMS_MTL_RTE_NOT_FOUND_B Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  The requested route, between <%1> and <%2>, could not be found in the configuration.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_INIT_STATS Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  Socket connection successful.  Listening on port %1.  Master socket:  %2  Max backlog queue size:  %3.
.
MessageId=+1 SymbolicName=EMS_MTL_EXCEPTION_UNHANDLED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL unhandled exception has occurred.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_LISTENING Severity=Success Facility=ITF
Language=English
EMS MTL Info:  UDP Server listening at IP <%1>, port <%2>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_LISTENING_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Error:  UDP Server failed to bind socket for listening at IP <%1>, port <%2>.  Socket error code is <%3>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_RECEIVED Severity=Success Facility=ITF
Language=English
EMS MTL Trace:  UDP Server received data or connection attempt from IP <%1>, port <%2>.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_NEW_CONNECTION Severity=Success Facility=ITF
Language=English
EMS MTL Info:  New connection established on UDP Server from IP <%1>, LUT ID <%2>.  Server will respond to client's port <%3>.  <%4> of maximum <%5> connections in use.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_CONNECTION_LIMIT_REACHED Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Info:  UDP Server received a connection attempt from IP <%1>, LUT ID <%2>, but client connection limit of <%3> has been reached.
.
MessageId=+1 SymbolicName=EMS_MTL_UDP_SERVER_CONNECTION_CLOSED Severity=Success Facility=ITF
Language=English
EMS MTL Info:  UDP Server closing connection to IP <%1>, port <%2>, LUT ID <%3>.  <%4> of maximum <%5> connections in use.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_AUDIO_NEW_CONNECTION Severity=Success Facility=ITF
Language=English
EMS MTL Info:  New audio data connection established on SOAP Server from IP <%1>, LUT ID <%2>.
.
MessageId=+1 SymbolicName=EMS_MTL_SOAP_SERVER_AUDIO_CONNECTION_CLOSED Severity=Success Facility=ITF
Language=English
EMS MTL Info:  SOAP Server closing connection to IP <%1>, LUT ID <%2>.
.
MessageId=+1 SymbolicName=EMS_MTL_INVALID_EPHEMERIS Severity=ErrWarn Facility=ITF
Language=English
EMS MTL Received an invalid ephemeris in SIT218 for satellite <%1>.
.
;
;#endif // INC_MTLMSGS


