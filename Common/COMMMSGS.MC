;/********************************************************************
;*	Module:			CommMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Comms Service Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2007 by EMS Technologies, Inc.,
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
;	0.0	01/05/21		rvw	start
;
;********************************************************************/
;#ifndef INC_COMMMSGS
;#define INC_COMMMSGS
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

MessageId=0xB300 SymbolicName=EMS_COMM_BASE_CODE Facility=ITF
Language=English
EMS Comms Error
.
MessageId=+1 SymbolicName=EMS_COMM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Comms Service Started
.
MessageId=+1 SymbolicName=EMS_COMM_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS Comms Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_COMM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Comms Service Stopped
.
MessageId=+1 SymbolicName=EMS_COMM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports error %1.
.
MessageId=+1 SymbolicName=EMS_COMM_FTP_LOGON_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Comms unable to log on remote server ( %1 )
.
MessageId=+1 SymbolicName=EMS_COMM_FTP_STORE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Comms unable to FTP copy file ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMM_FTP_RENAME_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Comms unable to FTP rename file ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMM_NO_MATCHING_DEST Severity=ErrWarn Facility=ITF
Language=English
EMS Comms unable to find matching destination for %1.  
.
MessageId=+1 SymbolicName=EMS_COMM_SEND_RETRY_LIMIT Severity=ErrWarn Facility=ITF
Language=English
EMS Comms exceeded retries attempting to send file %1.
.
MessageId=+1 SymbolicName=EMS_COMM_RECV_BAD_SEQ Severity=ErrWarn Facility=ITF
Language=English
EMS Comms received message %1 out of sequence.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_SEND_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Send' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_SENT_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Sent' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_RECV_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Received' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_PROCESSED_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Processed' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_UNDELIVERED_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Undelivered' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_DATA_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Data' directory.
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER Severity=Success Facility=ITF
Language=English
EMS Comms tracer (%1).
.
MessageId=+1 SymbolicName=EMS_COMM_MOVE_FILE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports an error copying file (%1).
.
MessageId=+1 SymbolicName=EMS_COMM_MSG_RECV Severity=Success Facility=ITF
Language=English
EMS Comms reports message (%1) received.
.
MessageId=+1 SymbolicName=EMS_COMM_MSG_SENT Severity=Success Facility=ITF
Language=English
EMS Comms reports message (%1) sent.
.
MessageId=+1 SymbolicName=EMS_COMM_SERVICE_START_PURGE Severity=Success Facility=ITF
Language=English
EMS Comms starting to purge message files.
.
MessageId=+1 SymbolicName=EMS_COMM_PURGE_MSG Severity=Success Facility=ITF
Language=English
EMS Comms, %1 purged.
.
MessageId=+1 SymbolicName=EMS_COMM_UNABLE_PURGE_MSG Severity=ErrWarn Facility=ITF
Language=English
EMS Comms unable to purge file in (%1).
.
MessageId=+1 SymbolicName=EMS_COMM_ROUTE_OFFLINE Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports one of the routes is currently offline (%1).
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_LOCAL_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access destination directory for at least one of the outgoing Routes.
.
MessageId=+1 SymbolicName=EMS_COMM_ROUTE_ONLINE Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports route %1 is back online.
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_TRANSFER_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access the configured transfer directory.
.
MessageId=+1 SymbolicName=EMS_COMM_MSG_UNDELIVERED Severity=ErrWarn Facility=ITF
Language=English
An error occurred while processing the file ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_CONFIG Severity=Success Facility=ITF
Language=English
EMS Comms tracer (cfg: %1=%2).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_CONFIG_YES Severity=Success Facility=ITF
Language=English
EMS Comms tracer (cfg: %1=yes).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_CONFIG_NO Severity=Success Facility=ITF
Language=English
EMS Comms tracer (cfg: %1=no).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_CONFIG_ROUTE Severity=Success Facility=ITF
Language=English
EMS Comms tracer (cfg: Route #%1: Timeout=%2).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_SHARINGVIOLATION_PROC Severity=Success Facility=ITF
Language=English
EMS Comms tracer (Sharing Violation while moving %1 to processing).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_SHARINGVIOLATION_UNDEL Severity=Success Facility=ITF
Language=English
EMS Comms tracer (Sharing Violation while moving %1 to Undelivered).
.
MessageId=+1 SymbolicName=EMS_COMM_TRACER_MOVEFILE Severity=Success Facility=ITF
Language=English
EMS Comms tracer (MoveFile(%1) hr=%2).
.
MessageId=+1 SymbolicName=EMS_COMM_PURGE_MSGDIR Severity=Success Facility=ITF
Language=English
EMS Comms, %1 messages in <%2> purged.
.
MessageId=+1 SymbolicName=EMS_COMM_MSG_UNDELIVERED_WITHERR Severity=ErrWarn Facility=ITF
Language=English
An error occurred while processing the file ( File name = %1, Err = %2 ).
.
MessageId=+1 SymbolicName=EMS_COMM_ROUTE_OFFLINE_WITHERR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports one of the routes is currently offline (Route = %1, Err = %2).
.
MessageId=+1 SymbolicName=EMS_COMM_MOVE_RETRY_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports a failure moving the file <%1> to <%2>.  The operating system reports error <%3>.
.
MessageId=+1 SymbolicName=EMS_COMM_IP_STATUS Severity=Success Facility=ITF
Language=English
PR,IP,%1
.
MessageId=+1 SymbolicName=EMS_COMM_PATHWAY_PRIMARY_ACTIVE Severity=Success Facility=ITF
Language=English
EMS Comms reports that the primary pathway for route %1 is now active.
.
MessageId=+1 SymbolicName=EMS_COMM_PATHWAY_ALTERNATE_ACTIVE Severity=Success Facility=ITF
Language=English
EMS Comms reports that the alternate pathway for route %1 is now active.
.
MessageId=+1 SymbolicName=EMS_COMM_IP_STATUS_TOO_MANY Severity=ErrWarn Facility=ITF
Language=English
EMS Comms reports that the number of active IP addresses exceeds the size of the notification message.  Maximum number of IPs is %1.  The output message may be missing IP addresses.
.
MessageId=+1 SymbolicName=EMS_COMM_NO_CONNECTION_MANAGER Severity=Success Facility=ITF
Language=English
EMS Comms reports that the Network Connection Manager subsystem is not installed.  As a result, Comms will not be able to report the active local IP addresses.
.
MessageId=+1 SymbolicName=EMS_COMM_ZIP_FILE_FAILED Severity=Success Facility=ITF
Language=English
EMS Comms reports a failure while zipping file "%1".  Error= %2.
.
MessageId=+1 SymbolicName=EMS_COMM_UNZIP_FILE_FAILED Severity=Success Facility=ITF
Language=English
EMS Comms reports a failure while unzipping file "%1".  Error= %2.
.
MessageId=+1 SymbolicName=EMS_COMM_MSG_UNDELIVERED_NO_MATCHING_SOURCE Severity=ErrWarn Facility=ITF
Language=English
EMS Comms failed to process file (%1). Unable to find matching configuration for message originator (%2).
.
MessageId=+1 SymbolicName=EMS_COMM_BAD_OFFLINE_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Comms was unable to access 'Offline' directory.
.
;
;#endif // INC_COMMMSGS
