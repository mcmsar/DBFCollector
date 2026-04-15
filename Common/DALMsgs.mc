;/********************************************************************
;*	Module:			DALMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for DAL Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
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
;	0.0	2003 Nov 10		jb		start 
;
;********************************************************************/
;#ifndef INC_DALMSGS
;#define INC_DALMSGS
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

MessageId=0xB900 SymbolicName=EMS_DAL_BASE_CODE Facility=ITF
Language=English
EMS Data Access Layer Error
.
MessageId=+1 SymbolicName=EMS_DAL_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Service Started
.
MessageId=+1 SymbolicName=EMS_DAL_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_DAL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Service Stopped
.
MessageId=+1 SymbolicName=EMS_DAL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  %1.
.
MessageId=+1 SymbolicName=EMS_DAL_ADO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An ADO exception has occurred.  %1.
.
MessageId=+1 SymbolicName=EMS_DAL_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An exception of an unknown type has occurred. 
.
MessageId=+1 SymbolicName=EMS_DAL_TYPE_UNEXPECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  The value retrieved for a field had an unexpected type. 
.
MessageId=+1 SymbolicName=EMS_DAL_UNKOWN_DATATYPE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An unknown data type for a database field was encountered.
.
MessageId=+1 SymbolicName=EMS_DAL_NO_META_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  Unable to retrieve meta data for a recordset.
.
MessageId=+1 SymbolicName=EMS_DAL_UNKNOWN_RECORD_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An unknown record type was encountered.
.
MessageId=+1 SymbolicName=EMS_DAL_UNKNOWN_TABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  A corresponding table name could not be found for the specified data type.
.
MessageId=+1 SymbolicName=EMS_DAL_CONNECTION Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Info:  Using connection string %1.
.
MessageId=+1 SymbolicName=EMS_DAL_SQL Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Info:  Using SQL string %1.
.
MessageId=+1 SymbolicName=EMS_DAL_SQL_CONSTRUCTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An error occurred while attempting to construct an SQL string.
.
MessageId=+1 SymbolicName=EMS_DAL_DELETE_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  A delete operation timed out.
.
MessageId=+1 SymbolicName=EMS_DAL_UNKOWN_OBJECTSTATE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An unknown database object state was encountered.
.
MessageId=+1 SymbolicName=EMS_DAL_RECORDTYPE_UNEXPECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An unexpected record type was encountered..
.
MessageId=+1 SymbolicName=EMS_DAL_QUERY_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  A query operation timed out.
.
MessageId=+1 SymbolicName=EMS_DAL_CACHE_RETRIEVAL Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Info:  Caller has requested data from the cache.
.
MessageId=+1 SymbolicName=EMS_DAL_META_RETRIEVAL Severity=Success Facility=ITF
Language=English
EMS Data Access Layer Info:  Caller has requested meta information.
.
MessageId=+1 SymbolicName=EMS_DAL_CACHE_LIMIT_REACHED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  The resultset cache has reached its limit.  Results could not be cached.
.
MessageId=+1 SymbolicName=EMS_DAL_SQL_KEYWORD_VIOLATION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An attempt was made to use an SQL statement that may violate the system database's integrity:  %1.
.
MessageId=+1 SymbolicName=EMS_DAL_EXCEPTION_UNHANDLED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An unhandled exception has occurred.
.
MessageId=+1 SymbolicName=EMS_DAL_QUERY_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Access Layer Error:  An exception occurred while processing a query (SQL: %1) (Error: %2) (Line: %3, %4)
.
;
;#endif // INC_DALMSGS



