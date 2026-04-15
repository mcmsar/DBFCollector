/********************************************************************
*	Module:			GWayMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS600GatewayService Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2002-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 Oct 8		rvw	start 

********************************************************************/
#ifndef INC_GWAYMSGS
#define INC_GWAYMSGS

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
// MessageId: EMS_GWAY_BASE_CODE
//
// MessageText:
//
//  EMS Gateway Error
//
#define EMS_GWAY_BASE_CODE               ((EMS_RESULT)0x0004B500L)

//
// MessageId: EMS_GWAY_SERVICE_START
//
// MessageText:
//
//  EMS Gateway Service Started
//
#define EMS_GWAY_SERVICE_START           ((EMS_RESULT)0x0004B501L)

//
// MessageId: EMS_GWAY_SERVICE_FAILED
//
// MessageText:
//
//  EMS Gateway Service did not start due to error %1
//
#define EMS_GWAY_SERVICE_FAILED          ((EMS_RESULT)0x8004B502L)

//
// MessageId: EMS_GWAY_SERVICE_STOP
//
// MessageText:
//
//  EMS Gateway Service Stopped
//
#define EMS_GWAY_SERVICE_STOP            ((EMS_RESULT)0x0004B503L)

//
// MessageId: EMS_GWAY_ERROR
//
// MessageText:
//
//  EMS Gateway reports error %1.
//
#define EMS_GWAY_ERROR                   ((EMS_RESULT)0x8004B504L)

//
// MessageId: EMS_GWAY_LOG_EXCEPTION
//
// MessageText:
//
//  EMS Gateway reports an exception
//
#define EMS_GWAY_LOG_EXCEPTION           ((EMS_RESULT)0x8004B505L)

//
// MessageId: EMS_GWAY_SIT_UNKNOWN
//
// MessageText:
//
//  EMS Gateway : Unknown SitMsg %1 ignored ( File=%2 ).
//
#define EMS_GWAY_SIT_UNKNOWN             ((EMS_RESULT)0x8004B506L)

//
// MessageId: EMS_GWAY_SIT_ERR
//
// MessageText:
//
//  EMS Gateway : Error while processing SitMsg %1 ( File=%2, Error=%3 ).
//
#define EMS_GWAY_SIT_ERR                 ((EMS_RESULT)0x8004B507L)

//
// MessageId: EMS_GWAY_SIT415
//
// MessageText:
//
//  EMS Gateway : SitMsg415 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT415                  ((EMS_RESULT)0x0004B508L)

//
// MessageId: EMS_GWAY_SIT510
//
// MessageText:
//
//  EMS Gateway : SitMsg510 processed ( Sat=%1, FreqOffset=%2 ). 
//
#define EMS_GWAY_SIT510                  ((EMS_RESULT)0x0004B509L)

//
// MessageId: EMS_GWAY_SIT_UNEXPECTED
//
// MessageText:
//
//  EMS Gateway : SitMsg %1 was unexpected ( File=%2 ). 
//
#define EMS_GWAY_SIT_UNEXPECTED          ((EMS_RESULT)0x8004B50AL)

//
// MessageId: EMS_GWAY_SIT255
//
// MessageText:
//
//  EMS Gateway : SitMsg255 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT255                  ((EMS_RESULT)0x0004B50BL)

//
// MessageId: EMS_GWAY_SIT215
//
// MessageText:
//
//  EMS Gateway : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT215                  ((EMS_RESULT)0x0004B50CL)

//
// MessageId: EMS_GWAY_NEW_ORBIT_VECTOR
//
// MessageText:
//
//  EMS Gateway installed new orbit vectors for Sat ID %1 ( , posErr, velErr ).
//
#define EMS_GWAY_NEW_ORBIT_VECTOR        ((EMS_RESULT)0x0004B50DL)

//
// MessageId: EMS_GWAY_ERR_ORBIT_VECTOR
//
// MessageText:
//
//  EMS Gateway reports orbit vectors error for Sat ID %1 ( , posErr, velErr ).
//
#define EMS_GWAY_ERR_ORBIT_VECTOR        ((EMS_RESULT)0x8004B50EL)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV
//
// MessageText:
//
//  EMS Gateway received SitMsg %1 from %2.
//
#define EMS_GWAY_SIT_MSG_RECV            ((EMS_RESULT)0x0004B50FL)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV_UNKNOWNFILE
//
// MessageText:
//
//  EMS Gateway received SitMsg with unknown filename from %1.
//
#define EMS_GWAY_SIT_MSG_RECV_UNKNOWNFILE ((EMS_RESULT)0x0004B510L)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV_BYTESTREAM
//
// MessageText:
//
//  EMS Gateway received SitMsg as a byte stream from %1.
//
#define EMS_GWAY_SIT_MSG_RECV_BYTESTREAM ((EMS_RESULT)0x0004B511L)

//
// MessageId: EMS_GWAY_NO_SYSTEST_TIME
//
// MessageText:
//
//  EMS Gateway reports insufficient time for system test.
//
#define EMS_GWAY_NO_SYSTEST_TIME         ((EMS_RESULT)0x0004B512L)

//
// MessageId: EMS_GWAY_PASS_IN_PROGRESS
//
// MessageText:
//
//  EMS Gateway is currently processing a pass.
//
#define EMS_GWAY_PASS_IN_PROGRESS        ((EMS_RESULT)0x0004B513L)

//
// MessageId: EMS_GWAY_CONNECTION_RECVD
//
// MessageText:
//
//  EMS Gateway received a connection from %1.
//
#define EMS_GWAY_CONNECTION_RECVD        ((EMS_RESULT)0x0004B514L)

//
// MessageId: EMS_GWAY_DISCONNECTION_RECVD
//
// MessageText:
//
//  EMS Gateway:  Client disconnected.
//
#define EMS_GWAY_DISCONNECTION_RECVD     ((EMS_RESULT)0x0004B515L)

//
// MessageId: EMS_GWAY_SEND_COMMAND
//
// MessageText:
//
//  EMS Gateway received command to send to destination %1.
//
#define EMS_GWAY_SEND_COMMAND            ((EMS_RESULT)0x0004B516L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_RECVD
//
// MessageText:
//
//  EMS Gateway successfully added a client identified by (%1) to the list of incoming message subscribers.
//
#define EMS_GWAY_SUBSCRIPTION_RECVD      ((EMS_RESULT)0x0004B517L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_FAILED
//
// MessageText:
//
//  EMS Gateway reports an error adding a client to its list of incoming message subscribers.
//
#define EMS_GWAY_SUBSCRIPTION_FAILED     ((EMS_RESULT)0x8004B518L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_CANCELLED
//
// MessageText:
//
//  EMS Gateway reports incoming message subscription cancelled by client (%1).
//
#define EMS_GWAY_SUBSCRIPTION_CANCELLED  ((EMS_RESULT)0x0004B519L)

//
// MessageId: EMS_GWAY_CMD_SENT
//
// MessageText:
//
//  EMS Gateway reports successfully sending command:  %1.
//
#define EMS_GWAY_CMD_SENT                ((EMS_RESULT)0x0004B51AL)

//
// MessageId: EMS_GWAY_CMD_SEND_FAIL
//
// MessageText:
//
//  EMS Gateway reports failure sending command:  %1.
//
#define EMS_GWAY_CMD_SEND_FAIL           ((EMS_RESULT)0x8004B51BL)

//
// MessageId: EMS_GWAY_NOTIFY_TIMEOUT
//
// MessageText:
//
//  EMS Gateway reports that a notification call to a subscriber timed out after %1 seconds.  The thread was terminated.
//
#define EMS_GWAY_NOTIFY_TIMEOUT          ((EMS_RESULT)0x8004B51CL)

//
// MessageId: EMS_GWAY_NO_CMD_CHANNEL
//
// MessageText:
//
//  EMS Gateway reports that it cannot establish a command channel to Master.
//
#define EMS_GWAY_NO_CMD_CHANNEL          ((EMS_RESULT)0x8004B51DL)

//
// MessageId: EMS_GWAY_CMD_RECV_FAIL
//
// MessageText:
//
//  EMS Gateway reports failure receiving message:  %1.
//
#define EMS_GWAY_CMD_RECV_FAIL           ((EMS_RESULT)0x8004B51EL)

//
// MessageId: EMS_GWAY_TRACE_MSG
//
// MessageText:
//
//  EMS Gateway trace message:  %1.
//
#define EMS_GWAY_TRACE_MSG               ((EMS_RESULT)0x0004B51FL)

//
// MessageId: EMS_GWAY_BROADCAST_EXCEPTION
//
// MessageText:
//
//  EMS Gateway reports an exception while notifying a subscriber.
//
#define EMS_GWAY_BROADCAST_EXCEPTION     ((EMS_RESULT)0x8004B520L)

//
// MessageId: EMS_GWAY_RESOURCE_DISABLED
//
// MessageText:
//
//  EMS Gateway reports attempt to locally access unavailable resource %1.
//
#define EMS_GWAY_RESOURCE_DISABLED       ((EMS_RESULT)0x8004B521L)

//
// MessageId: EMS_GWAY_ACCESS_DENIED
//
// MessageText:
//
//  EMS Gateway reports denial of access to resource %1 due to authorization failure.
//
#define EMS_GWAY_ACCESS_DENIED           ((EMS_RESULT)0x8004B522L)

//
// MessageId: EMS_GWAY_SERIAL_ACCESS_REQUIRED
//
// MessageText:
//
//  EMS Gateway reports attempt to use command or data channel to invoke resource %1 while not in serialized mode.
//
#define EMS_GWAY_SERIAL_ACCESS_REQUIRED  ((EMS_RESULT)0x8004B523L)

//
// MessageId: EMS_GWAY_CONFIG_NOT_FOUND
//
// MessageText:
//
//  EMS Gateway reports failed attempt to find configuration data for key = %1 and value = %2.
//
#define EMS_GWAY_CONFIG_NOT_FOUND        ((EMS_RESULT)0x8004B524L)

//
// MessageId: EMS_GWAY_UNKNOWN_RESPONSE
//
// MessageText:
//
//  EMS Gateway reports an unknown response command received.
//
#define EMS_GWAY_UNKNOWN_RESPONSE        ((EMS_RESULT)0x8004B525L)

//
// MessageId: EMS_GWAY_PIPE_COMMAND_TIMEOUT
//
// MessageText:
//
//  EMS Gateway reports a timeout waiting for a command response on the EMSPipeline.
//
#define EMS_GWAY_PIPE_COMMAND_TIMEOUT    ((EMS_RESULT)0x8004B526L)

//
// MessageId: EMS_GWAY_CONFIG_NO_RES_TRANS_TABLE
//
// MessageText:
//
//  EMS Gateway reports that the resource translation table for lut %1 could not be found in the configuration.
//
#define EMS_GWAY_CONFIG_NO_RES_TRANS_TABLE ((EMS_RESULT)0x8004B527L)

//
// MessageId: EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED
//
// MessageText:
//
//  EMS Gateway reports that while constructing a pipeline command string the maximum length was reached.
//
#define EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED ((EMS_RESULT)0x8004B528L)

//
// MessageId: EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS
//
// MessageText:
//
//  EMS Gateway reports that the maximum number of LUTs (%1) from which data can be simultaneously manually recovered has been exceeded.
//
#define EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS ((EMS_RESULT)0x8004B529L)

//
// MessageId: EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES
//
// MessageText:
//
//  EMS Gateway reports that the maximum number of Datatypes (%1) for which data can be simultaneously manually recovered has been exceeded.
//
#define EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES ((EMS_RESULT)0x8004B52AL)

//
// MessageId: EMS_GWAY_DAL_QUERY_TIMEOUT
//
// MessageText:
//
//  EMS Gateway reports that a query executed on the DAL has timed out.  The query has been cancelled.
//
#define EMS_GWAY_DAL_QUERY_TIMEOUT       ((EMS_RESULT)0x8004B52BL)

//
// MessageId: EMS_GWAY_UNKNOWN_TARGET_LOCATION
//
// MessageText:
//
//  EMS Gateway reports a problem determining whether a target location is local or remote.
//
#define EMS_GWAY_UNKNOWN_TARGET_LOCATION ((EMS_RESULT)0x8004B52CL)

//
// MessageId: EMS_GWAY_BAD_IMPL_POINTER
//
// MessageText:
//
//  EMS Gateway reports an invalid pointer to the Gateway %1 implementation.
//
#define EMS_GWAY_BAD_IMPL_POINTER        ((EMS_RESULT)0x8004B52DL)

//
// MessageId: EMS_GWAY_CSSHORTNAME
//
// MessageText:
//
//  C-S Short Name
//
#define EMS_GWAY_CSSHORTNAME             ((EMS_RESULT)0x0004B52EL)

//
// MessageId: EMS_GWAY_LOCALCALL
//
// MessageText:
//
//  EMS Gateway trace message:  Local call
//
#define EMS_GWAY_LOCALCALL               ((EMS_RESULT)0x0004B52FL)

//
// MessageId: EMS_GWAY_REMOTECALL
//
// MessageText:
//
//  EMS Gateway trace message:  Remote call
//
#define EMS_GWAY_REMOTECALL              ((EMS_RESULT)0x0004B530L)

//
// MessageId: EMS_GWAY_KERNELMSG
//
// MessageText:
//
//  EMS Gateway trace message:  Message is from kernel
//
#define EMS_GWAY_KERNELMSG               ((EMS_RESULT)0x0004B531L)

//
// MessageId: EMS_GWAY_NONKERNELMSG
//
// MessageText:
//
//  EMS Gateway trace message:  Message is not from kernel
//
#define EMS_GWAY_NONKERNELMSG            ((EMS_RESULT)0x0004B532L)

//
// MessageId: EMS_GWAY_PROCESSEDDIR
//
// MessageText:
//
//  EMS Gateway trace message:  Processed dir=%1
//
#define EMS_GWAY_PROCESSEDDIR            ((EMS_RESULT)0x0004B533L)

//
// MessageId: EMS_GWAY_FILEPATH
//
// MessageText:
//
//  EMS Gateway trace message:  File path =%1
//
#define EMS_GWAY_FILEPATH                ((EMS_RESULT)0x0004B534L)

//
// MessageId: EMS_GWAY_SENDINGPROCESSFILECMD
//
// MessageText:
//
//  EMS Gateway trace message:  Sending command to process file to Master
//
#define EMS_GWAY_SENDINGPROCESSFILECMD   ((EMS_RESULT)0x0004B535L)

//
// MessageId: EMS_GWAY_BROADCASTING
//
// MessageText:
//
//  EMS Gateway trace message:  Broadcasting message to subscribers
//
#define EMS_GWAY_BROADCASTING            ((EMS_RESULT)0x0004B536L)

//
// MessageId: EMS_GWAY_BROADCASTINGCOUNT
//
// MessageText:
//
//  EMS Gateway trace message:  Broadcasting to %1 subscribers
//
#define EMS_GWAY_BROADCASTINGCOUNT       ((EMS_RESULT)0x0004B537L)

//
// MessageId: EMS_GWAY_CONVERTSITFAILED
//
// MessageText:
//
//  EMS Gateway trace message:  Failed to convert SIT into a file.
//
#define EMS_GWAY_CONVERTSITFAILED        ((EMS_RESULT)0x0004B538L)

//
// MessageId: EMS_GWAY_BROADCASTOK
//
// MessageText:
//
//  EMS Gateway trace message:  Broadcast thread completed succesfully.
//
#define EMS_GWAY_BROADCASTOK             ((EMS_RESULT)0x0004B539L)

//
// MessageId: EMS_GWAY_SUBSCRIBERREMOVED
//
// MessageText:
//
//  EMS Gateway trace message:  Subscriber at index %1 being removed due to a failure during notification.
//
#define EMS_GWAY_SUBSCRIBERREMOVED       ((EMS_RESULT)0x0004B53AL)

//
// MessageId: EMS_GWAY_LUTIDENT
//
// MessageText:
//
//  EMS Gateway trace message:  This LUT ID is %1
//
#define EMS_GWAY_LUTIDENT                ((EMS_RESULT)0x0004B53BL)

//
// MessageId: EMS_GWAY_BROADCASTTIMEOUT
//
// MessageText:
//
//  EMS Gateway trace message:  Broadcast timeout = %1 seconds
//
#define EMS_GWAY_BROADCASTTIMEOUT        ((EMS_RESULT)0x0004B53CL)

//
// MessageId: EMS_GWAY_MASTERSENDON
//
// MessageText:
//
//  EMS Gateway trace message:  Send to Master enabled
//
#define EMS_GWAY_MASTERSENDON            ((EMS_RESULT)0x0004B53DL)

//
// MessageId: EMS_GWAY_MASTERSENDOFF
//
// MessageText:
//
//  EMS Gateway trace message:  Send to Master disabled
//
#define EMS_GWAY_MASTERSENDOFF           ((EMS_RESULT)0x0004B53EL)

//
// MessageId: EMS_GWAY_BYPASSINGMASTER
//
// MessageText:
//
//  EMS Gateway trace message:  Bypassing transmission of msg file to Master
//
#define EMS_GWAY_BYPASSINGMASTER         ((EMS_RESULT)0x0004B53FL)

//
// MessageId: GWAY_LABEL_IF_UNKNOWN
//
// MessageText:
//
//  Unknown
//
#define GWAY_LABEL_IF_UNKNOWN            ((EMS_RESULT)0x0004B540L)

//
// MessageId: GWAY_LABEL_IF_ALERTGEN
//
// MessageText:
//
//  Alert Generator
//
#define GWAY_LABEL_IF_ALERTGEN           ((EMS_RESULT)0x0004B541L)

//
// MessageId: GWAY_LABEL_IF_CONFIG
//
// MessageText:
//
//  Config Manager
//
#define GWAY_LABEL_IF_CONFIG             ((EMS_RESULT)0x0004B542L)

//
// MessageId: GWAY_LABEL_IF_DAC
//
// MessageText:
//
//  Data Acquisition
//
#define GWAY_LABEL_IF_DAC                ((EMS_RESULT)0x0004B543L)

//
// MessageId: GWAY_LABEL_IF_DAL
//
// MessageText:
//
//  Data Access Layer
//
#define GWAY_LABEL_IF_DAL                ((EMS_RESULT)0x0004B544L)

//
// MessageId: GWAY_LABEL_IF_LOCATION
//
// MessageText:
//
//  Location Processor Controller
//
#define GWAY_LABEL_IF_LOCATION           ((EMS_RESULT)0x0004B545L)

//
// MessageId: GWAY_LABEL_IF_DATAXFER
//
// MessageText:
//
//  Data Transfer
//
#define GWAY_LABEL_IF_DATAXFER           ((EMS_RESULT)0x0004B546L)

//
// MessageId: GWAY_LABEL_IF_MCC
//
// MessageText:
//
//  MCC
//
#define GWAY_LABEL_IF_MCC                ((EMS_RESULT)0x0004B547L)

//
// MessageId: GWAY_LABEL_IF_ALERTMANAGER
//
// MessageText:
//
//  Alert Manager
//
#define GWAY_LABEL_IF_ALERTMANAGER       ((EMS_RESULT)0x0004B548L)

//
// MessageId: GWAY_LABEL_IF_SIT
//
// MessageText:
//
//  SIT
//
#define GWAY_LABEL_IF_SIT                ((EMS_RESULT)0x0004B549L)

//
// MessageId: GWAY_LABEL_IF_AUDIO
//
// MessageText:
//
//  AUDIO
//
#define GWAY_LABEL_IF_AUDIO              ((EMS_RESULT)0x0004B54AL)

//
// MessageId: GWAY_LABEL_IF_HEALTHSTATUS
//
// MessageText:
//
//  Health Status
//
#define GWAY_LABEL_IF_HEALTHSTATUS       ((EMS_RESULT)0x0004B54BL)

//
// MessageId: GWAY_LABEL_IF_LAST
//
// MessageText:
//
//   
//
#define GWAY_LABEL_IF_LAST               ((EMS_RESULT)0x0004B54CL)


#endif // INC_GWAYMSGS
