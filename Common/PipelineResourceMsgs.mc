;/********************************************************************
;*	Module:			PipelineResourceMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Pipeline Resource Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2005 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_PIPELINERESOURCEMSG
;#define INC_PIPELINERESOURCEMSG
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

MessageId=0xD800 SymbolicName=EMS_PIPELINE_RESOURCE_BASE_CODE Facility=ITF
Language=English
EMS Pipeline Resource error.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NO_URL_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No URL was specified.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NO_MODE_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No access mode was specified.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NO_PATH_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No path was specified in the URL, <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NO_EVENT Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No data notification event was specified.  It is required when reading from the pipeline.
.
MessageId=+1 SymbolicName=EMS_PIPERES_PIPE_CREATE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No data notification event was specified.  Pipeline instance creation failed with error code <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_PIPE_CREATE_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  No data notification event was specified.  An instance of the pipeline could not be created.
.
MessageId=+1 SymbolicName=EMS_PIPERES_SRC_REGISTER_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  Registering a source on channel <%1> with the pipeline failed with error code <%2>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_SRC_GETSTREAM_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to open a stream to the resource.  An attempt to retrieve the stream from a source object failed with error code <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_ALREADY_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to configure a data sink event.  The sink was already configured.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_NO_EVENT Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to configure a data sink event.  No event was specified.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_NO_CHANNEL Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to configure a data sink event.  No data channel was specified.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_SINK_REG_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to connect a data sink.  The error code <%1> was returned when attempting to register the sink.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_SINK_STREAM_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to retrieve the stream to a data sink.  The sink does not exist.
.
MessageId=+1 SymbolicName=EMS_PIPERES_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource captured an unknown exception.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NOT_ACTIVE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred attempting to activate a resource.  The resource is not configured in active mode.
.
MessageId=+1 SymbolicName=EMS_PIPERES_SINK_NOT_CONNECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred attempting to activate a resource.  The pipeline sink has not been connected.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NOT_ACTIVE_DEACTIVATE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred attempting to deactivate a resource.  The resource is not configured in active mode.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_RUNTIME_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An unrecognized error occurred while running a sink listener thread.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_RUNTIME_ERROR_CAPTURED Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  A runtime error occurred while attempting to start a sink listener thread.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_PIPE_CREATE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to connect a sink to the pipeline.  No data notification event was specified.  Pipeline instance creation failed with error code <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_NO_PIPE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to connect or disconnect a sink to the pipeline.  A pointer to the pipeline could not be obtained.
.
MessageId=+1 SymbolicName=EMS_PIPERES_NO_STREAM Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to connect a sink to the pipeline.  A pointer to the stream could not be obtained.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_NO_REC_SIZE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred when attempting to configure a data sink.  A record size of 0 was specified.
.
MessageId=+1 SymbolicName=EMS_PIPERES_GET_RECSIZE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pipeline Resource:  An error occurred attempting to retrieve the record size from the URL.  There may be a syntax error in the URL <%1>.
.
MessageId=+1 SymbolicName=EMS_PIPERES_THREAD_ALREADY_RUNNING Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  Pipeline sink parameters cannot be changed while connected to the pipeline.
.
;
;#endif
