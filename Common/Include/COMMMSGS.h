/********************************************************************
*	Module:			CommMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Comms Service Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2007 by EMS Technologies, Inc.,
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_COMMMSGS
#define INC_COMMMSGS

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
// MessageId: EMS_COMM_BASE_CODE
//
// MessageText:
//
//  EMS Comms Error
//
#define EMS_COMM_BASE_CODE               ((EMS_RESULT)0x0004B300L)

//
// MessageId: EMS_COMM_SERVICE_START
//
// MessageText:
//
//  EMS Comms Service Started
//
#define EMS_COMM_SERVICE_START           ((EMS_RESULT)0x0004B301L)

//
// MessageId: EMS_COMM_SERVICE_FAILED
//
// MessageText:
//
//  EMS Comms Service did not start due to error %1
//
#define EMS_COMM_SERVICE_FAILED          ((EMS_RESULT)0x0004B302L)

//
// MessageId: EMS_COMM_SERVICE_STOP
//
// MessageText:
//
//  EMS Comms Service Stopped
//
#define EMS_COMM_SERVICE_STOP            ((EMS_RESULT)0x0004B303L)

//
// MessageId: EMS_COMM_ERROR
//
// MessageText:
//
//  EMS Comms reports error %1.
//
#define EMS_COMM_ERROR                   ((EMS_RESULT)0x8004B304L)

//
// MessageId: EMS_COMM_FTP_LOGON_FAILED
//
// MessageText:
//
//  EMS Comms unable to log on remote server ( %1 )
//
#define EMS_COMM_FTP_LOGON_FAILED        ((EMS_RESULT)0x8004B305L)

//
// MessageId: EMS_COMM_FTP_STORE_FAILED
//
// MessageText:
//
//  EMS Comms unable to FTP copy file ( %1 ).
//
#define EMS_COMM_FTP_STORE_FAILED        ((EMS_RESULT)0x8004B306L)

//
// MessageId: EMS_COMM_FTP_RENAME_FAILED
//
// MessageText:
//
//  EMS Comms unable to FTP rename file ( %1 ).
//
#define EMS_COMM_FTP_RENAME_FAILED       ((EMS_RESULT)0x8004B307L)

//
// MessageId: EMS_COMM_NO_MATCHING_DEST
//
// MessageText:
//
//  EMS Comms unable to find matching destination for %1.  
//
#define EMS_COMM_NO_MATCHING_DEST        ((EMS_RESULT)0x8004B308L)

//
// MessageId: EMS_COMM_SEND_RETRY_LIMIT
//
// MessageText:
//
//  EMS Comms exceeded retries attempting to send file %1.
//
#define EMS_COMM_SEND_RETRY_LIMIT        ((EMS_RESULT)0x8004B309L)

//
// MessageId: EMS_COMM_RECV_BAD_SEQ
//
// MessageText:
//
//  EMS Comms received message %1 out of sequence.
//
#define EMS_COMM_RECV_BAD_SEQ            ((EMS_RESULT)0x8004B30AL)

//
// MessageId: EMS_COMM_BAD_SEND_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Send' directory.
//
#define EMS_COMM_BAD_SEND_DIR            ((EMS_RESULT)0x8004B30BL)

//
// MessageId: EMS_COMM_BAD_SENT_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Sent' directory.
//
#define EMS_COMM_BAD_SENT_DIR            ((EMS_RESULT)0x8004B30CL)

//
// MessageId: EMS_COMM_BAD_RECV_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Received' directory.
//
#define EMS_COMM_BAD_RECV_DIR            ((EMS_RESULT)0x8004B30DL)

//
// MessageId: EMS_COMM_BAD_PROCESSED_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Processed' directory.
//
#define EMS_COMM_BAD_PROCESSED_DIR       ((EMS_RESULT)0x8004B30EL)

//
// MessageId: EMS_COMM_BAD_UNDELIVERED_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Undelivered' directory.
//
#define EMS_COMM_BAD_UNDELIVERED_DIR     ((EMS_RESULT)0x8004B30FL)

//
// MessageId: EMS_COMM_BAD_DATA_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Data' directory.
//
#define EMS_COMM_BAD_DATA_DIR            ((EMS_RESULT)0x8004B310L)

//
// MessageId: EMS_COMM_TRACER
//
// MessageText:
//
//  EMS Comms tracer (%1).
//
#define EMS_COMM_TRACER                  ((EMS_RESULT)0x0004B311L)

//
// MessageId: EMS_COMM_MOVE_FILE_ERROR
//
// MessageText:
//
//  EMS Comms reports an error copying file (%1).
//
#define EMS_COMM_MOVE_FILE_ERROR         ((EMS_RESULT)0x8004B312L)

//
// MessageId: EMS_COMM_MSG_RECV
//
// MessageText:
//
//  EMS Comms reports message (%1) received.
//
#define EMS_COMM_MSG_RECV                ((EMS_RESULT)0x0004B313L)

//
// MessageId: EMS_COMM_MSG_SENT
//
// MessageText:
//
//  EMS Comms reports message (%1) sent.
//
#define EMS_COMM_MSG_SENT                ((EMS_RESULT)0x0004B314L)

//
// MessageId: EMS_COMM_SERVICE_START_PURGE
//
// MessageText:
//
//  EMS Comms starting to purge message files.
//
#define EMS_COMM_SERVICE_START_PURGE     ((EMS_RESULT)0x0004B315L)

//
// MessageId: EMS_COMM_PURGE_MSG
//
// MessageText:
//
//  EMS Comms, %1 purged.
//
#define EMS_COMM_PURGE_MSG               ((EMS_RESULT)0x0004B316L)

//
// MessageId: EMS_COMM_UNABLE_PURGE_MSG
//
// MessageText:
//
//  EMS Comms unable to purge file in (%1).
//
#define EMS_COMM_UNABLE_PURGE_MSG        ((EMS_RESULT)0x8004B317L)

//
// MessageId: EMS_COMM_ROUTE_OFFLINE
//
// MessageText:
//
//  EMS Comms reports one of the routes is currently offline (%1).
//
#define EMS_COMM_ROUTE_OFFLINE           ((EMS_RESULT)0x8004B318L)

//
// MessageId: EMS_COMM_BAD_LOCAL_DIR
//
// MessageText:
//
//  EMS Comms was unable to access destination directory for at least one of the outgoing Routes.
//
#define EMS_COMM_BAD_LOCAL_DIR           ((EMS_RESULT)0x8004B319L)

//
// MessageId: EMS_COMM_ROUTE_ONLINE
//
// MessageText:
//
//  EMS Comms reports route %1 is back online.
//
#define EMS_COMM_ROUTE_ONLINE            ((EMS_RESULT)0x8004B31AL)

//
// MessageId: EMS_COMM_BAD_TRANSFER_DIR
//
// MessageText:
//
//  EMS Comms was unable to access the configured transfer directory.
//
#define EMS_COMM_BAD_TRANSFER_DIR        ((EMS_RESULT)0x8004B31BL)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED
//
// MessageText:
//
//  An error occurred while processing the file ( %1 ).
//
#define EMS_COMM_MSG_UNDELIVERED         ((EMS_RESULT)0x8004B31CL)

//
// MessageId: EMS_COMM_TRACER_CONFIG
//
// MessageText:
//
//  EMS Comms tracer (cfg: %1=%2).
//
#define EMS_COMM_TRACER_CONFIG           ((EMS_RESULT)0x0004B31DL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_YES
//
// MessageText:
//
//  EMS Comms tracer (cfg: %1=yes).
//
#define EMS_COMM_TRACER_CONFIG_YES       ((EMS_RESULT)0x0004B31EL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_NO
//
// MessageText:
//
//  EMS Comms tracer (cfg: %1=no).
//
#define EMS_COMM_TRACER_CONFIG_NO        ((EMS_RESULT)0x0004B31FL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_ROUTE
//
// MessageText:
//
//  EMS Comms tracer (cfg: Route #%1: Timeout=%2).
//
#define EMS_COMM_TRACER_CONFIG_ROUTE     ((EMS_RESULT)0x0004B320L)

//
// MessageId: EMS_COMM_TRACER_SHARINGVIOLATION_PROC
//
// MessageText:
//
//  EMS Comms tracer (Sharing Violation while moving %1 to processing).
//
#define EMS_COMM_TRACER_SHARINGVIOLATION_PROC ((EMS_RESULT)0x0004B321L)

//
// MessageId: EMS_COMM_TRACER_SHARINGVIOLATION_UNDEL
//
// MessageText:
//
//  EMS Comms tracer (Sharing Violation while moving %1 to Undelivered).
//
#define EMS_COMM_TRACER_SHARINGVIOLATION_UNDEL ((EMS_RESULT)0x0004B322L)

//
// MessageId: EMS_COMM_TRACER_MOVEFILE
//
// MessageText:
//
//  EMS Comms tracer (MoveFile(%1) hr=%2).
//
#define EMS_COMM_TRACER_MOVEFILE         ((EMS_RESULT)0x0004B323L)

//
// MessageId: EMS_COMM_PURGE_MSGDIR
//
// MessageText:
//
//  EMS Comms, %1 messages in <%2> purged.
//
#define EMS_COMM_PURGE_MSGDIR            ((EMS_RESULT)0x0004B324L)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED_WITHERR
//
// MessageText:
//
//  An error occurred while processing the file ( File name = %1, Err = %2 ).
//
#define EMS_COMM_MSG_UNDELIVERED_WITHERR ((EMS_RESULT)0x8004B325L)

//
// MessageId: EMS_COMM_ROUTE_OFFLINE_WITHERR
//
// MessageText:
//
//  EMS Comms reports one of the routes is currently offline (Route = %1, Err = %2).
//
#define EMS_COMM_ROUTE_OFFLINE_WITHERR   ((EMS_RESULT)0x8004B326L)

//
// MessageId: EMS_COMM_MOVE_RETRY_FAILURE
//
// MessageText:
//
//  EMS Comms reports a failure moving the file <%1> to <%2>.  The operating system reports error <%3>.
//
#define EMS_COMM_MOVE_RETRY_FAILURE      ((EMS_RESULT)0x8004B327L)

//
// MessageId: EMS_COMM_IP_STATUS
//
// MessageText:
//
//  PR,IP,%1
//
#define EMS_COMM_IP_STATUS               ((EMS_RESULT)0x0004B328L)

//
// MessageId: EMS_COMM_PATHWAY_PRIMARY_ACTIVE
//
// MessageText:
//
//  EMS Comms reports that the primary pathway for route %1 is now active.
//
#define EMS_COMM_PATHWAY_PRIMARY_ACTIVE  ((EMS_RESULT)0x0004B329L)

//
// MessageId: EMS_COMM_PATHWAY_ALTERNATE_ACTIVE
//
// MessageText:
//
//  EMS Comms reports that the alternate pathway for route %1 is now active.
//
#define EMS_COMM_PATHWAY_ALTERNATE_ACTIVE ((EMS_RESULT)0x0004B32AL)

//
// MessageId: EMS_COMM_IP_STATUS_TOO_MANY
//
// MessageText:
//
//  EMS Comms reports that the number of active IP addresses exceeds the size of the notification message.  Maximum number of IPs is %1.  The output message may be missing IP addresses.
//
#define EMS_COMM_IP_STATUS_TOO_MANY      ((EMS_RESULT)0x8004B32BL)

//
// MessageId: EMS_COMM_NO_CONNECTION_MANAGER
//
// MessageText:
//
//  EMS Comms reports that the Network Connection Manager subsystem is not installed.  As a result, Comms will not be able to report the active local IP addresses.
//
#define EMS_COMM_NO_CONNECTION_MANAGER   ((EMS_RESULT)0x0004B32CL)

//
// MessageId: EMS_COMM_ZIP_FILE_FAILED
//
// MessageText:
//
//  EMS Comms reports a failure while zipping file "%1".  Error= %2.
//
#define EMS_COMM_ZIP_FILE_FAILED         ((EMS_RESULT)0x0004B32DL)

//
// MessageId: EMS_COMM_UNZIP_FILE_FAILED
//
// MessageText:
//
//  EMS Comms reports a failure while unzipping file "%1".  Error= %2.
//
#define EMS_COMM_UNZIP_FILE_FAILED       ((EMS_RESULT)0x0004B32EL)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED_NO_MATCHING_SOURCE
//
// MessageText:
//
//  EMS Comms failed to process file (%1). Unable to find matching configuration for message originator (%2).
//
#define EMS_COMM_MSG_UNDELIVERED_NO_MATCHING_SOURCE ((EMS_RESULT)0x8004B32FL)

//
// MessageId: EMS_COMM_BAD_OFFLINE_DIR
//
// MessageText:
//
//  EMS Comms was unable to access 'Offline' directory.
//
#define EMS_COMM_BAD_OFFLINE_DIR         ((EMS_RESULT)0x8004B330L)


#endif // INC_COMMMSGS
