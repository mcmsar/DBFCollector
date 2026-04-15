;/********************************************************************
;*	Module:			DatabaseResourceMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Database Resource Errors & Messages
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


;#ifndef INC_DATABASERESOURCEMSG
;#define INC_DATABASERESOURCEMSG
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

MessageId=0xD500 SymbolicName=EMS_DB_RESOURCE_BASE_CODE Facility=ITF
Language=English
EMS Database Resource error.
.
MessageId=+1 SymbolicName=EMS_DBRES_RETRIEVAL_RUNNING Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  Database query parameters cannot be changed while a retrieval is in progress.
.
MessageId=+1 SymbolicName=EMS_DBRES_QI_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to retrieve a stream interface pointer for the in-memory stream.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_MEM_STREAM Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to access the memory stream.
.
MessageId=+1 SymbolicName=EMS_DBRES_UNKNOWN_MODE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting determine the retrieval mode.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_REALTIME_EVENT_HANDLE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to start data retrieval in realtime mode.  An event handle could not be obtained.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_REALTIME_TABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the monitor for realtime data.  The table to monitor could not be determined.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_REALTIME_COLUMN Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the monitor for realtime data.  The column to monitor could not be determined.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_REALTIME_NOTIFY_EVENT Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the monitor for realtime data.  The notification event could not be determined.
.
MessageId=+1 SymbolicName=EMS_DBRES_REALTIME_EVENT_CREATION_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the monitor for realtime data.  The notification event, <%1>, could not be created.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_NOFITY_EVENT Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the data notification event.  No event name was specified.
.
MessageId=+1 SymbolicName=EMS_DBRES_NOFITY_EVENT_CREATION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred setting up the data notification event.  Failed to create the event, <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_NOSQL Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred preparing to execute a query.  No SQL statement has been specified.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_REALTIME_MONITOR Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred preparing to execute a query for realtime data.  The realtime data monitor object is not available.
.
MessageId=+1 SymbolicName=EMS_DBRES_SQL_RETRIEVAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred preparing to execute a query for data.  An SQL statement could not be generated.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_WRITEABLE_STREAM Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred preparing to write query results to the data stream.  A pointer to the stream could not be obtained.
.
MessageId=+1 SymbolicName=EMS_DBRES_STREAM_WRITE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred writing query results to the data stream.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_DATA_AVAIL_EVENT Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to signal the availability of query results in the data stream.  No event handle is available.
.
MessageId=+1 SymbolicName=EMS_DBRES_STREAM_WRITE_UNDER Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred writing query results to the data stream.  Attempted to write <%1> bytes, but <%2> bytes were actually written.
.
MessageId=+1 SymbolicName=EMS_DBRES_NOT_ACTIVE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to activate a resource.  The resource is not configured in active mode.
.
MessageId=+1 SymbolicName=EMS_DBRES_THREAD_RUNTIME_ERROR_CAPTURED Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  A runtime error occurred while attempting to start a database retrieval thread.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_NOT_ACTIVE_DEACTIVATE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to deactivate a resource.  The resource is not configured in active mode.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_URL Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to access a resource.  No URL has been specified.
.
MessageId=+1 SymbolicName=EMS_DBRES_NO_QUERY_PARAM Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error has occurred.  The query parameter, <%1>, could not be extracted from the URL query, <%2>.
.
MessageId=+1 SymbolicName=EMS_DBRES_ACTIVE_PARAM_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error has occurred reading the active settings from the URL.  The settings, <%1>, may not be formatted correctly.
.
MessageId=+1 SymbolicName=EMS_DBRES_ACTIVE_PARAM_NO_COLUMN Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error has occurred reading the active settings from the URL.  The column name could not be found in the settings, <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_ACTIVE_PARAM_NO_PERIOD Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error has occurred reading the active settings from the URL.  The period could not be found in the settings, <%1>.
.
MessageId=+1 SymbolicName=EMS_DBRES_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource captured an unknown exception.
.
MessageId=+1 SymbolicName=EMS_DBRES_DATA_CHANNEL_NO_SIGNAL Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  A request was made to establish a data sink, but no event name for signalling new data was specified.
.
;
;#endif
