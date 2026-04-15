;/********************************************************************
;*	Module:			SocketMsg.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Socket Service Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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
;	0.0	2003 Apr 1		RVW	
;
;********************************************************************/
;#ifndef INC_SOCKETMSG
;#define INC_SOCKETMSG
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;

MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
	Info=0x1
	Warn=0x2
	Alarm=0x3
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xE000 SymbolicName=EMS_SOCKET_BASE_CODE Facility=ITF
Language=English
EMSSocketService Error
.
MessageId=+1 SymbolicName=EMS_SOCKET_SERVICE_START Severity=Success Facility=ITF
Language=English
EMSSocketService Started
.
MessageId=+1 SymbolicName=EMS_SOCKET_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMSSocketService did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_SOCKET_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMSSocketService Stopped
.
MessageId=+1 SymbolicName=EMS_SOCKET_ERROR Severity=Alarm Facility=ITF
Language=English
EMSSocketService reports error %1.
.
MessageId=+1 SymbolicName=EMS_SOCKET_LOG_EXCEPTION Severity=Alarm Facility=ITF
Language=English
EMSSocketService reports an exception
.
MessageId=+1 SymbolicName=EMS_SOCKET_TRACER Severity=Success Facility=ITF
Language=English
EMSSocketService tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_NAK Severity=Warn Facility=ITF
Language=English
EMSSocketService reports a NAK.
.
MessageId=+1 SymbolicName=EMS_SOCKET_NONE_READY Severity=Warn Facility=ITF
Language=English
EMSSocketService reports no sockets ready.
.
MessageId=+1 SymbolicName=EMS_SOCKET_NOT_INITIALIZED Severity=Alarm Facility=ITF
Language=English
EMSSocketService reports sockets not initialized.
.
MessageId=+1 SymbolicName=EMS_SOCKET_UNKNOWN_ERROR Severity=Alarm Facility=ITF
Language=English
EMSSocketService reports socket error (%1).
.
MessageId=+1 SymbolicName=EMS_SOCKET_NO_CONNECTION Severity=Alarm Facility=ITF
Language=English
EMSSocketService reports socket connection unavailable.
.
MessageId=+1 SymbolicName=EMS_SOCKET_CONFIG Severity=Success Facility=ITF
Language=English
EMSSocketService { cfg: %1 }
.
MessageId=+1 SymbolicName=EMS_SOCKET_MSG_SENT Severity=Success Facility=ITF
Language=English
EMSSocketService sent msg ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_MSG_ERR Severity=Success Facility=ITF
Language=English
EMSSocketService reports error sending msg ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_MULTISIT_ERR Severity=Alarm Facility=ITF
Language=English
EMSSocketService recv'd an unexpected MultiSIT message ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_BADSIT_ERR Severity=Alarm Facility=ITF
Language=English
EMSSocketService recv'd an unknown SIT message ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_SIT_SUPPRESS Severity=Success Facility=ITF
Language=English
EMSSocketService suppressed SIT message ( %1 ).
.
MessageId=+1 SymbolicName=EMS_SOCKET_EVENT_CREATE_ERR Severity=Warn Facility=ITF
Language=English
EMSSocketService failed to initialize event handles.
.
MessageId=+1 SymbolicName=EMS_SOCKET_WAIT_ERR Severity=Warn Facility=ITF
Language=English
EMSSocketService processing loop wait failed with error ( %1 ).
.
;
;#endif // INC_SOCKETMSG



