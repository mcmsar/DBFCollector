;/********************************************************************
;*	Module:			pipemsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Pipeline Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
;*						All rights reserved
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
;#ifndef INC_PIPEMSGS
;#define INC_PIPEMSGS
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

MessageId=0x8800 SymbolicName=EMS_PIPE_BASE_CODE Facility=ITF
Language=English
EMS Pipeline Error
.
MessageId=+3 SymbolicName=EMS_PIPE_LIMIT_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Limit Exceeded
.
MessageId=+1 SymbolicName=EMS_PIPE_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel %1 has overflowed
.
MessageId=+1 SymbolicName=EMS_PIPE_DATA_LOST Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel data has been lost
.
MessageId=+1 SymbolicName=EMS_PIPE_DATA_TRUNCATED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel data has been truncated
.
MessageId=+1 SymbolicName=EMS_PIPE_UNKNOWN_SINK Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel unknown sink
.
MessageId=+1 SymbolicName=EMS_PIPE_UNKNOWN_SOURCE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel unknown source
.
MessageId=+1 SymbolicName=EMS_PIPE_NO_SINKS Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel %1 has no active sinks
.
MessageId=+1 SymbolicName=EMS_PIPE_ALREADY_REGISTERED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline sink / source is already registered
.
MessageId=+1 SymbolicName=EMS_PIPE_ALREADY_SET Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline is already registered set
.
MessageId=+1 SymbolicName=EMS_PIPE_TOO_BIG Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline is too big
.
MessageId=+1 SymbolicName=EMS_PIPE_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Pipeline Service Started
.
MessageId=+1 SymbolicName=EMS_PIPE_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_PIPE_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Pipeline Service Stopped
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_CHANNEL_WRITE Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Channel Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
.
MessageId=+1 SymbolicName=EMS_PIPE_START_LOGGING Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Enabled
.
MessageId=+1 SymbolicName=EMS_PIPE_STOP_LOGGING Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Disabled
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_REGISTER_SINK Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Register Sink ( Type=%1, Count=%2, Result = %3  )
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_REGISTER_SOURCE Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Register Source ( Type=%1, Count=%2, Result = %3 )
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_UNREGISTER_SINK Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Unregister Sink ( Type=%1, Count=%2, Result = %3  )
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_UNREGISTER_SOURCE Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Unregister Source ( Type=%1, Count=%2, Result = %3 )
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_WRITE_COMMAND Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Command Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
.
MessageId=+1 SymbolicName=EMS_PIPE_LOG_CHANNEL_SUMMARY Severity=Success Facility=ITF
Language=English
EMS Pipeline Logging Channel Summary ( Type=%1, Sinks=%2, Srcs=%3, Max=%4, Min=%5 )
.
MessageId=+1 SymbolicName=EMS_PIPE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Error ( %1 )
.
MessageId=+1 SymbolicName=EMS_PIPE_NO_STREAM Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline reports invalid stream pointer.
.
MessageId=+1 SymbolicName=EMS_PIPE_OVERFLOW_RETRY Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Channel %1 has overflowed , retry %2
.
MessageId=+1 SymbolicName=EMS_PIPE_RECV_COMMAND Severity=Success Facility=ITF
Language=English
Command Received( %1 )
.
MessageId=+1 SymbolicName=EMS_STREAM_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline stream has overflowed
.
MessageId=+1 SymbolicName=EMS_PIPE_CHANNEL_LOCK_FAILED Severity=ErrWarn Facility=ITF
Language=English
DataChannel %1::_Lock Failed
.
MessageId=+1 SymbolicName=EMS_PIPE_PIPELINE_LOCK_FAILED Severity=ErrWarn Facility=ITF
Language=English
DataPipeline::_Lock Failed
.
MessageId=+1 SymbolicName=EMS_PIPE_TRACE_WRITE_OVERFLOW Severity=SUCCESS Facility=ITF
Language=English
PacketStream::Write Overflow {Type=%1, Retries=%2}
.
MessageId=+1 SymbolicName=EMS_PIPE_PKTSTREAM_LOCKFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Error ( PacketStream::_Lock Failed )
.
MessageId=+1 SymbolicName=EMS_PIPE_TRACER Severity=Success Facility=ITF
Language=English
EMS Pipeline : %1
.
MessageId=+1 SymbolicName=EMS_PIPE_CHANNEL_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline : Overflow on channel %1 for process %2
.
MessageId=+1 SymbolicName=EMS_PIPE_SINK_REGISTERED_FOR_PROCESS Severity=Success Facility=ITF
Language=English
Sink registered on channel %1 for process %2
.
MessageId=+1 SymbolicName=EMS_PIPE_SINK_REGISTERED_UNK_PROCESS Severity=Success Facility=ITF
Language=English
Sink registered on channel %1 for unidentified process
.
;
;#endif // INC_PIPEMSGS

