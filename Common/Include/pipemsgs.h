/********************************************************************
*	Module:			pipemsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Pipeline Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*						All rights reserved
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
#ifndef INC_PIPEMSGS
#define INC_PIPEMSGS

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
// MessageId: EMS_PIPE_BASE_CODE
//
// MessageText:
//
//  EMS Pipeline Error
//
#define EMS_PIPE_BASE_CODE               ((EMS_RESULT)0x00048800L)

//
// MessageId: EMS_PIPE_LIMIT_EXCEEDED
//
// MessageText:
//
//  EMS Pipeline Limit Exceeded
//
#define EMS_PIPE_LIMIT_EXCEEDED          ((EMS_RESULT)0x80048803L)

//
// MessageId: EMS_PIPE_OVERFLOW
//
// MessageText:
//
//  EMS Pipeline Channel %1 has overflowed
//
#define EMS_PIPE_OVERFLOW                ((EMS_RESULT)0x80048804L)

//
// MessageId: EMS_PIPE_DATA_LOST
//
// MessageText:
//
//  EMS Pipeline Channel data has been lost
//
#define EMS_PIPE_DATA_LOST               ((EMS_RESULT)0x80048805L)

//
// MessageId: EMS_PIPE_DATA_TRUNCATED
//
// MessageText:
//
//  EMS Pipeline Channel data has been truncated
//
#define EMS_PIPE_DATA_TRUNCATED          ((EMS_RESULT)0x80048806L)

//
// MessageId: EMS_PIPE_UNKNOWN_SINK
//
// MessageText:
//
//  EMS Pipeline Channel unknown sink
//
#define EMS_PIPE_UNKNOWN_SINK            ((EMS_RESULT)0x80048807L)

//
// MessageId: EMS_PIPE_UNKNOWN_SOURCE
//
// MessageText:
//
//  EMS Pipeline Channel unknown source
//
#define EMS_PIPE_UNKNOWN_SOURCE          ((EMS_RESULT)0x80048808L)

//
// MessageId: EMS_PIPE_NO_SINKS
//
// MessageText:
//
//  EMS Pipeline Channel %1 has no active sinks
//
#define EMS_PIPE_NO_SINKS                ((EMS_RESULT)0x80048809L)

//
// MessageId: EMS_PIPE_ALREADY_REGISTERED
//
// MessageText:
//
//  EMS Pipeline sink / source is already registered
//
#define EMS_PIPE_ALREADY_REGISTERED      ((EMS_RESULT)0x8004880AL)

//
// MessageId: EMS_PIPE_ALREADY_SET
//
// MessageText:
//
//  EMS Pipeline is already registered set
//
#define EMS_PIPE_ALREADY_SET             ((EMS_RESULT)0x8004880BL)

//
// MessageId: EMS_PIPE_TOO_BIG
//
// MessageText:
//
//  EMS Pipeline is too big
//
#define EMS_PIPE_TOO_BIG                 ((EMS_RESULT)0x8004880CL)

//
// MessageId: EMS_PIPE_SERVICE_START
//
// MessageText:
//
//  EMS Pipeline Service Started
//
#define EMS_PIPE_SERVICE_START           ((EMS_RESULT)0x0004880DL)

//
// MessageId: EMS_PIPE_SERVICE_FAILED
//
// MessageText:
//
//  EMS Pipeline Service did not start due to error %1
//
#define EMS_PIPE_SERVICE_FAILED          ((EMS_RESULT)0x8004880EL)

//
// MessageId: EMS_PIPE_SERVICE_STOP
//
// MessageText:
//
//  EMS Pipeline Service Stopped
//
#define EMS_PIPE_SERVICE_STOP            ((EMS_RESULT)0x0004880FL)

//
// MessageId: EMS_PIPE_LOG_CHANNEL_WRITE
//
// MessageText:
//
//  EMS Pipeline Logging Channel Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
//
#define EMS_PIPE_LOG_CHANNEL_WRITE       ((EMS_RESULT)0x00048810L)

//
// MessageId: EMS_PIPE_START_LOGGING
//
// MessageText:
//
//  EMS Pipeline Logging Enabled
//
#define EMS_PIPE_START_LOGGING           ((EMS_RESULT)0x00048811L)

//
// MessageId: EMS_PIPE_STOP_LOGGING
//
// MessageText:
//
//  EMS Pipeline Logging Disabled
//
#define EMS_PIPE_STOP_LOGGING            ((EMS_RESULT)0x00048812L)

//
// MessageId: EMS_PIPE_LOG_REGISTER_SINK
//
// MessageText:
//
//  EMS Pipeline Logging Register Sink ( Type=%1, Count=%2, Result = %3  )
//
#define EMS_PIPE_LOG_REGISTER_SINK       ((EMS_RESULT)0x00048813L)

//
// MessageId: EMS_PIPE_LOG_REGISTER_SOURCE
//
// MessageText:
//
//  EMS Pipeline Logging Register Source ( Type=%1, Count=%2, Result = %3 )
//
#define EMS_PIPE_LOG_REGISTER_SOURCE     ((EMS_RESULT)0x00048814L)

//
// MessageId: EMS_PIPE_LOG_UNREGISTER_SINK
//
// MessageText:
//
//  EMS Pipeline Logging Unregister Sink ( Type=%1, Count=%2, Result = %3  )
//
#define EMS_PIPE_LOG_UNREGISTER_SINK     ((EMS_RESULT)0x00048815L)

//
// MessageId: EMS_PIPE_LOG_UNREGISTER_SOURCE
//
// MessageText:
//
//  EMS Pipeline Logging Unregister Source ( Type=%1, Count=%2, Result = %3 )
//
#define EMS_PIPE_LOG_UNREGISTER_SOURCE   ((EMS_RESULT)0x00048816L)

//
// MessageId: EMS_PIPE_LOG_WRITE_COMMAND
//
// MessageText:
//
//  EMS Pipeline Logging Command Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
//
#define EMS_PIPE_LOG_WRITE_COMMAND       ((EMS_RESULT)0x00048817L)

//
// MessageId: EMS_PIPE_LOG_CHANNEL_SUMMARY
//
// MessageText:
//
//  EMS Pipeline Logging Channel Summary ( Type=%1, Sinks=%2, Srcs=%3, Max=%4, Min=%5 )
//
#define EMS_PIPE_LOG_CHANNEL_SUMMARY     ((EMS_RESULT)0x00048818L)

//
// MessageId: EMS_PIPE_ERROR
//
// MessageText:
//
//  EMS Pipeline Error ( %1 )
//
#define EMS_PIPE_ERROR                   ((EMS_RESULT)0x80048819L)

//
// MessageId: EMS_PIPE_NO_STREAM
//
// MessageText:
//
//  EMS Pipeline reports invalid stream pointer.
//
#define EMS_PIPE_NO_STREAM               ((EMS_RESULT)0x8004881AL)

//
// MessageId: EMS_PIPE_OVERFLOW_RETRY
//
// MessageText:
//
//  EMS Pipeline Channel %1 has overflowed , retry %2
//
#define EMS_PIPE_OVERFLOW_RETRY          ((EMS_RESULT)0x8004881BL)

//
// MessageId: EMS_PIPE_RECV_COMMAND
//
// MessageText:
//
//  Command Received( %1 )
//
#define EMS_PIPE_RECV_COMMAND            ((EMS_RESULT)0x0004881CL)

//
// MessageId: EMS_STREAM_OVERFLOW
//
// MessageText:
//
//  EMS Pipeline stream has overflowed
//
#define EMS_STREAM_OVERFLOW              ((EMS_RESULT)0x8004881DL)

//
// MessageId: EMS_PIPE_CHANNEL_LOCK_FAILED
//
// MessageText:
//
//  DataChannel %1::_Lock Failed
//
#define EMS_PIPE_CHANNEL_LOCK_FAILED     ((EMS_RESULT)0x8004881EL)

//
// MessageId: EMS_PIPE_PIPELINE_LOCK_FAILED
//
// MessageText:
//
//  DataPipeline::_Lock Failed
//
#define EMS_PIPE_PIPELINE_LOCK_FAILED    ((EMS_RESULT)0x8004881FL)

//
// MessageId: EMS_PIPE_TRACE_WRITE_OVERFLOW
//
// MessageText:
//
//  PacketStream::Write Overflow {Type=%1, Retries=%2}
//
#define EMS_PIPE_TRACE_WRITE_OVERFLOW    ((EMS_RESULT)0x00048820L)

//
// MessageId: EMS_PIPE_PKTSTREAM_LOCKFAILED
//
// MessageText:
//
//  EMS Pipeline Error ( PacketStream::_Lock Failed )
//
#define EMS_PIPE_PKTSTREAM_LOCKFAILED    ((EMS_RESULT)0x80048821L)

//
// MessageId: EMS_PIPE_TRACER
//
// MessageText:
//
//  EMS Pipeline : %1
//
#define EMS_PIPE_TRACER                  ((EMS_RESULT)0x00048822L)

//
// MessageId: EMS_PIPE_CHANNEL_OVERFLOW
//
// MessageText:
//
//  EMS Pipeline : Overflow on channel %1 for process %2
//
#define EMS_PIPE_CHANNEL_OVERFLOW        ((EMS_RESULT)0x80048823L)

//
// MessageId: EMS_PIPE_SINK_REGISTERED_FOR_PROCESS
//
// MessageText:
//
//  Sink registered on channel %1 for process %2
//
#define EMS_PIPE_SINK_REGISTERED_FOR_PROCESS ((EMS_RESULT)0x00048824L)

//
// MessageId: EMS_PIPE_SINK_REGISTERED_UNK_PROCESS
//
// MessageText:
//
//  Sink registered on channel %1 for unidentified process
//
#define EMS_PIPE_SINK_REGISTERED_UNK_PROCESS ((EMS_RESULT)0x00048825L)


#endif // INC_PIPEMSGS
