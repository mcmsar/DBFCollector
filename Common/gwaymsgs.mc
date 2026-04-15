;/********************************************************************
;*	Module:			GWayMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS600GatewayService Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2002-2005 by EMS Technologies, Inc.,
;*					All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
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
;	0.0	2002 Oct 8		rvw	start 
;
;********************************************************************/
;#ifndef INC_GWAYMSGS
;#define INC_GWAYMSGS
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

MessageId=0xB500 SymbolicName=EMS_GWAY_BASE_CODE Facility=ITF
Language=English
EMS Gateway Error
.
MessageId=+1 SymbolicName=EMS_GWAY_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Gateway Service Started
.
MessageId=+1 SymbolicName=EMS_GWAY_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_GWAY_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Gateway Service Stopped
.
MessageId=+1 SymbolicName=EMS_GWAY_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports error %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_LOG_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports an exception
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway : Unknown SitMsg %1 ignored ( File=%2 ).
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway : Error while processing SitMsg %1 ( File=%2, Error=%3 ).
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT415 Severity=Success Facility=ITF
Language=English
EMS Gateway : SitMsg415 processed ( Sat=%1, Freq=%2, Time=%3 ). 
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT510 Severity=Success Facility=ITF
Language=English
EMS Gateway : SitMsg510 processed ( Sat=%1, FreqOffset=%2 ). 
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_UNEXPECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway : SitMsg %1 was unexpected ( File=%2 ). 
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT255 Severity=Success Facility=ITF
Language=English
EMS Gateway : SitMsg255 processed ( Sat=%1, Freq=%2, Time=%3 ). 
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT215 Severity=Success Facility=ITF
Language=English
EMS Gateway : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
.
MessageId=+1 SymbolicName=EMS_GWAY_NEW_ORBIT_VECTOR Severity=Success Facility=ITF
Language=English
EMS Gateway installed new orbit vectors for Sat ID %1 ( , posErr, velErr ).
.
MessageId=+1 SymbolicName=EMS_GWAY_ERR_ORBIT_VECTOR Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports orbit vectors error for Sat ID %1 ( , posErr, velErr ).
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_MSG_RECV Severity=Success Facility=ITF
Language=English
EMS Gateway received SitMsg %1 from %2.
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_MSG_RECV_UNKNOWNFILE Severity=Success Facility=ITF
Language=English
EMS Gateway received SitMsg with unknown filename from %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_SIT_MSG_RECV_BYTESTREAM Severity=Success Facility=ITF
Language=English
EMS Gateway received SitMsg as a byte stream from %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_NO_SYSTEST_TIME Severity=Success Facility=ITF
Language=English
EMS Gateway reports insufficient time for system test.
.
MessageId=+1 SymbolicName=EMS_GWAY_PASS_IN_PROGRESS Severity=Success Facility=ITF
Language=English
EMS Gateway is currently processing a pass.
.
MessageId=+1 SymbolicName=EMS_GWAY_CONNECTION_RECVD Severity=Success Facility=ITF
Language=English
EMS Gateway received a connection from %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_DISCONNECTION_RECVD Severity=Success Facility=ITF
Language=English
EMS Gateway:  Client disconnected.
.
MessageId=+1 SymbolicName=EMS_GWAY_SEND_COMMAND Severity=Success Facility=ITF
Language=English
EMS Gateway received command to send to destination %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_SUBSCRIPTION_RECVD Severity=Success Facility=ITF
Language=English
EMS Gateway successfully added a client identified by (%1) to the list of incoming message subscribers.
.
MessageId=+1 SymbolicName=EMS_GWAY_SUBSCRIPTION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports an error adding a client to its list of incoming message subscribers.
.
MessageId=+1 SymbolicName=EMS_GWAY_SUBSCRIPTION_CANCELLED Severity=Success Facility=ITF
Language=English
EMS Gateway reports incoming message subscription cancelled by client (%1).
.
MessageId=+1 SymbolicName=EMS_GWAY_CMD_SENT Severity=Success Facility=ITF
Language=English
EMS Gateway reports successfully sending command:  %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_CMD_SEND_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports failure sending command:  %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_NOTIFY_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that a notification call to a subscriber timed out after %1 seconds.  The thread was terminated.
.
MessageId=+1 SymbolicName=EMS_GWAY_NO_CMD_CHANNEL Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that it cannot establish a command channel to Master.
.
MessageId=+1 SymbolicName=EMS_GWAY_CMD_RECV_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports failure receiving message:  %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_TRACE_MSG Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_BROADCAST_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports an exception while notifying a subscriber.
.
MessageId=+1 SymbolicName=EMS_GWAY_RESOURCE_DISABLED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports attempt to locally access unavailable resource %1.
.
MessageId=+1 SymbolicName=EMS_GWAY_ACCESS_DENIED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports denial of access to resource %1 due to authorization failure.
.
MessageId=+1 SymbolicName=EMS_GWAY_SERIAL_ACCESS_REQUIRED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports attempt to use command or data channel to invoke resource %1 while not in serialized mode.
.
MessageId=+1 SymbolicName=EMS_GWAY_CONFIG_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports failed attempt to find configuration data for key = %1 and value = %2.
.
MessageId=+1 SymbolicName=EMS_GWAY_UNKNOWN_RESPONSE Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports an unknown response command received.
.
MessageId=+1 SymbolicName=EMS_GWAY_PIPE_COMMAND_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports a timeout waiting for a command response on the EMSPipeline.
.
MessageId=+1 SymbolicName=EMS_GWAY_CONFIG_NO_RES_TRANS_TABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that the resource translation table for lut %1 could not be found in the configuration.
.
MessageId=+1 SymbolicName=EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that while constructing a pipeline command string the maximum length was reached.
.
MessageId=+1 SymbolicName=EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that the maximum number of LUTs (%1) from which data can be simultaneously manually recovered has been exceeded.
.
MessageId=+1 SymbolicName=EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that the maximum number of Datatypes (%1) for which data can be simultaneously manually recovered has been exceeded.
.
MessageId=+1 SymbolicName=EMS_GWAY_DAL_QUERY_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports that a query executed on the DAL has timed out.  The query has been cancelled.
.
MessageId=+1 SymbolicName=EMS_GWAY_UNKNOWN_TARGET_LOCATION Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports a problem determining whether a target location is local or remote.
.
MessageId=+1 SymbolicName=EMS_GWAY_BAD_IMPL_POINTER Severity=ErrWarn Facility=ITF
Language=English
EMS Gateway reports an invalid pointer to the Gateway %1 implementation.
.
MessageId=+1 SymbolicName=EMS_GWAY_CSSHORTNAME Severity=Success Facility=ITF
Language=English
C-S Short Name
.
MessageId=+1 SymbolicName=EMS_GWAY_LOCALCALL Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Local call
.
MessageId=+1 SymbolicName=EMS_GWAY_REMOTECALL Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Remote call
.
MessageId=+1 SymbolicName=EMS_GWAY_KERNELMSG Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Message is from kernel
.
MessageId=+1 SymbolicName=EMS_GWAY_NONKERNELMSG Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Message is not from kernel
.
MessageId=+1 SymbolicName=EMS_GWAY_PROCESSEDDIR Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Processed dir=%1
.
MessageId=+1 SymbolicName=EMS_GWAY_FILEPATH Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  File path =%1
.
MessageId=+1 SymbolicName=EMS_GWAY_SENDINGPROCESSFILECMD Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Sending command to process file to Master
.
MessageId=+1 SymbolicName=EMS_GWAY_BROADCASTING Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Broadcasting message to subscribers
.
MessageId=+1 SymbolicName=EMS_GWAY_BROADCASTINGCOUNT Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Broadcasting to %1 subscribers
.
MessageId=+1 SymbolicName=EMS_GWAY_CONVERTSITFAILED Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Failed to convert SIT into a file.
.
MessageId=+1 SymbolicName=EMS_GWAY_BROADCASTOK Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Broadcast thread completed succesfully.
.
MessageId=+1 SymbolicName=EMS_GWAY_SUBSCRIBERREMOVED Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Subscriber at index %1 being removed due to a failure during notification.
.
MessageId=+1 SymbolicName=EMS_GWAY_LUTIDENT Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  This LUT ID is %1
.
MessageId=+1 SymbolicName=EMS_GWAY_BROADCASTTIMEOUT Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Broadcast timeout = %1 seconds
.
MessageId=+1 SymbolicName=EMS_GWAY_MASTERSENDON Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Send to Master enabled
.
MessageId=+1 SymbolicName=EMS_GWAY_MASTERSENDOFF Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Send to Master disabled
.
MessageId=+1 SymbolicName=EMS_GWAY_BYPASSINGMASTER Severity=Success Facility=ITF
Language=English
EMS Gateway trace message:  Bypassing transmission of msg file to Master
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_UNKNOWN Severity=Success Facility=ITF
Language=English
Unknown
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_ALERTGEN Severity=Success Facility=ITF
Language=English
Alert Generator
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_CONFIG Severity=Success Facility=ITF
Language=English
Config Manager
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_DAC Severity=Success Facility=ITF
Language=English
Data Acquisition
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_DAL Severity=Success Facility=ITF
Language=English
Data Access Layer
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_LOCATION Severity=Success Facility=ITF
Language=English
Location Processor Controller
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_DATAXFER Severity=Success Facility=ITF
Language=English
Data Transfer
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_MCC Severity=Success Facility=ITF
Language=English
MCC
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_ALERTMANAGER Severity=Success Facility=ITF
Language=English
Alert Manager
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_SIT Severity=Success Facility=ITF
Language=English
SIT
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_AUDIO Severity=Success Facility=ITF
Language=English
AUDIO
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_HEALTHSTATUS Severity=Success Facility=ITF
Language=English
Health Status
.
MessageId=+1 SymbolicName=GWAY_LABEL_IF_LAST Severity=Success Facility=ITF
Language=English
 
.
;
;#endif // INC_GWAYMSGS



