;/********************************************************************
;*	Module:			SGenMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Sit Generator Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
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
;#ifndef INC_SGENMSGS
;#define INC_SGENMSGS
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

MessageId=0xB200 SymbolicName=EMS_SITGEN_BASE_CODE Facility=ITF
Language=English
EMS SitGen Error
.
MessageId=+1 SymbolicName=EMS_SITGEN_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS SitGen Service Started
.
MessageId=+1 SymbolicName=EMS_SITGEN_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS SitGen Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_SITGEN_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS SitGen Service Stopped
.
MessageId=+1 SymbolicName=EMS_SITGEN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error %1.
.
MessageId=+1 SymbolicName=EMS_SITGEN_PIPELINE_CONNECT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error %1 while trying to connect to the pipeline.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_SITEINFO Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error trying to access the site info.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_LOGGER Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error trying to connect to the logger.
.
MessageId=+1 SymbolicName=EMS_SITGEN_INVALID_SEND_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error accessing send directory( %1 ).
.
MessageId=+1 SymbolicName=EMS_SITGEN_FILE_CREATE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error trying to create file (%1).
.
MessageId=+1 SymbolicName=EMS_SITGEN_INVALID_SENT_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error accessing sent directory( %1 ).
.
MessageId=+1 SymbolicName=EMS_SITGEN_INVALID_UNDELIVERED_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error accessing undelivered directory( %1 ).
.
MessageId=+1 SymbolicName=EMS_SITGEN_UNKNOWN_DEST Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error trying to identify dest ID %1.
.
MessageId=+1 SymbolicName=EMS_SITGEN_RESEND_BUSY Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen rejected retransmit request from dest ID %1.
.
MessageId=+1 SymbolicName=EMS_SITGEN_RESEND_REQ Severity=Success Facility=ITF
Language=English
EMS SitGen received request from dest ID %1 msgs to be resent.
.
MessageId=+1 SymbolicName=EMS_SITGEN_RESEND_RESULT Severity=Success Facility=ITF
Language=English
EMS SitGen resent dest ID %1 messages.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_ORBIT Severity=Success Facility=ITF
Language=English
EMS SitGen cannot create orbit interface (%1).
.
MessageId=+1 SymbolicName=EMS_SITGEN_SELECTION_EMPTY Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports no data to reply to the request.
.
MessageId=+1 SymbolicName=EMS_SITGEN_SELECTION_LIMIT Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports too much data to reply to the request.
.
MessageId=+1 SymbolicName=EMS_SITGEN_UNKNOWN_REQUEST Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports unknown SendData ( %1 ) request.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_DEST_SIT Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports SIT format not defined by destination.
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACER Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SITGEN_SUPPRESSED Severity=Success Facility=ITF
Language=English
EMS SitGen suppressed %1 alerts.
.
MessageId=+1 SymbolicName=EMS_SITGEN_ALERT_FILTER Severity=Success Facility=ITF
Language=English
EMS SitGen reports finding an Alert Filter module.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_ALERT_FILTER Severity=Success Facility=ITF
Language=English
EMS SitGen reports no Alert Filter module found.
.
MessageId=+1 SymbolicName=EMS_SITGEN_RESEND_REQ_NODATA Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failed resend request.  The requested messages %1 cannot be found.
.
MessageId=+1 SymbolicName=EMS_SITGEN_RESEND_REQ_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failed resend request.  The request for messages %1 could not be processed.
.
MessageId=+1 SymbolicName=EMS_SITGEN_MSG_SIZE_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failure retrieving configured value for maximum SIT message size.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_CM Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failure initializing the Configuration Manager.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_SITGEN_NO_SECURITY_TOKEN Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failure retrieving a security token.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_ENTER Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( ** Enter: Sit (%1) )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_EXIT Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( ** Exit: Sit (%1) )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_SELN Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( Selection (%1) - (%2) )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_CONFIG Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( cfg: %1=%2 )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_CONFIGYES Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( cfg: %1=yes )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_CONFIGNO Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( cfg: %1=no )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_SATEPOCH Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( Sat=%1, Epoch=%2 )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_DEST Severity=Success Facility=ITF
Language=English
EMS SitGen tracer ( Dest %1 - %2 dwFlags(%3) )
.
MessageId=+1 SymbolicName=EMS_SITGEN_TRACE_CHARMAPINUSE Severity=Success Facility=ITF
Language=English
EMS SitGen: Dest %1 has character mapping specified (%2)
.
MessageId=+1 SymbolicName=EMS_SITGEN_LINE_LIMIT_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen: Maximum allowed line length for a sit message has been exceeded.
.
MessageId=+1 SymbolicName=EMS_SITGEN_BEACON_SUPPRESSED_FOR_DEST Severity=Success Facility=ITF
Language=English
EMS SitGen: Alert suppressed (Beacon: %1, Dest: %2).
.
MessageId=+1 SymbolicName=EMS_SITGEN_MF_RANGE_EXCEEDED Severity=Success Facility=ITF
Language=English
EMS SitGen: %1 %2 value was adjusted before being output (%3 changed to %4).
.
MessageId=+1 SymbolicName=EMS_SITGEN_SENDDATA_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports error trying to process "SendData" command (SIT Number=%1, dest ID=%2, Error - %3).
.
MessageId=+1 SymbolicName=EMS_SIT_ALREADY_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
Programming error: SIT message has already been initialized.
.
MessageId=+1 SymbolicName=EMS_SIT_CANT_CONNECT_SEQ_NUM_WEB_SRVC Severity=ErrWarn Facility=ITF
Language=English
Can't connect to Sequence Number Generator Web Service(%1:%2): %3
.
MessageId=+1 SymbolicName=EMS_SITGEN_CANT_SAVE_SEQ_NUM Severity=ErrWarn Facility=ITF
Language=English
EMS SitGen reports failure saving sequence number.
.
;
;#endif // INC_SGENMSGS



