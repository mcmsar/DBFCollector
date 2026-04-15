/********************************************************************
*	Module:			DALMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for DAL Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003 Nov 10		jb		start 

********************************************************************/
#ifndef INC_DALMSGS
#define INC_DALMSGS

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
// MessageId: EMS_DAL_BASE_CODE
//
// MessageText:
//
//  EMS Data Access Layer Error
//
#define EMS_DAL_BASE_CODE                ((EMS_RESULT)0x0004B900L)

//
// MessageId: EMS_DAL_SERVICE_START
//
// MessageText:
//
//  EMS Data Access Layer Service Started
//
#define EMS_DAL_SERVICE_START            ((EMS_RESULT)0x0004B901L)

//
// MessageId: EMS_DAL_SERVICE_FAILED
//
// MessageText:
//
//  EMS Data Access Layer Service did not start due to error %1
//
#define EMS_DAL_SERVICE_FAILED           ((EMS_RESULT)0x8004B902L)

//
// MessageId: EMS_DAL_SERVICE_STOP
//
// MessageText:
//
//  EMS Data Access Layer Service Stopped
//
#define EMS_DAL_SERVICE_STOP             ((EMS_RESULT)0x0004B903L)

//
// MessageId: EMS_DAL_ERROR
//
// MessageText:
//
//  EMS Data Access Layer Error:  %1.
//
#define EMS_DAL_ERROR                    ((EMS_RESULT)0x8004B904L)

//
// MessageId: EMS_DAL_ADO_ERROR
//
// MessageText:
//
//  EMS Data Access Layer Error:  An ADO exception has occurred.  %1.
//
#define EMS_DAL_ADO_ERROR                ((EMS_RESULT)0x8004B905L)

//
// MessageId: EMS_DAL_EXCEPTION
//
// MessageText:
//
//  EMS Data Access Layer Error:  An exception of an unknown type has occurred. 
//
#define EMS_DAL_EXCEPTION                ((EMS_RESULT)0x8004B906L)

//
// MessageId: EMS_DAL_TYPE_UNEXPECTED
//
// MessageText:
//
//  EMS Data Access Layer Error:  The value retrieved for a field had an unexpected type. 
//
#define EMS_DAL_TYPE_UNEXPECTED          ((EMS_RESULT)0x8004B907L)

//
// MessageId: EMS_DAL_UNKOWN_DATATYPE
//
// MessageText:
//
//  EMS Data Access Layer Error:  An unknown data type for a database field was encountered.
//
#define EMS_DAL_UNKOWN_DATATYPE          ((EMS_RESULT)0x8004B908L)

//
// MessageId: EMS_DAL_NO_META_DATA
//
// MessageText:
//
//  EMS Data Access Layer Error:  Unable to retrieve meta data for a recordset.
//
#define EMS_DAL_NO_META_DATA             ((EMS_RESULT)0x8004B909L)

//
// MessageId: EMS_DAL_UNKNOWN_RECORD_TYPE
//
// MessageText:
//
//  EMS Data Access Layer Error:  An unknown record type was encountered.
//
#define EMS_DAL_UNKNOWN_RECORD_TYPE      ((EMS_RESULT)0x8004B90AL)

//
// MessageId: EMS_DAL_UNKNOWN_TABLE
//
// MessageText:
//
//  EMS Data Access Layer Error:  A corresponding table name could not be found for the specified data type.
//
#define EMS_DAL_UNKNOWN_TABLE            ((EMS_RESULT)0x8004B90BL)

//
// MessageId: EMS_DAL_CONNECTION
//
// MessageText:
//
//  EMS Data Access Layer Info:  Using connection string %1.
//
#define EMS_DAL_CONNECTION               ((EMS_RESULT)0x0004B90CL)

//
// MessageId: EMS_DAL_SQL
//
// MessageText:
//
//  EMS Data Access Layer Info:  Using SQL string %1.
//
#define EMS_DAL_SQL                      ((EMS_RESULT)0x0004B90DL)

//
// MessageId: EMS_DAL_SQL_CONSTRUCTION
//
// MessageText:
//
//  EMS Data Access Layer Error:  An error occurred while attempting to construct an SQL string.
//
#define EMS_DAL_SQL_CONSTRUCTION         ((EMS_RESULT)0x8004B90EL)

//
// MessageId: EMS_DAL_DELETE_TIMEOUT
//
// MessageText:
//
//  EMS Data Access Layer Error:  A delete operation timed out.
//
#define EMS_DAL_DELETE_TIMEOUT           ((EMS_RESULT)0x8004B90FL)

//
// MessageId: EMS_DAL_UNKOWN_OBJECTSTATE
//
// MessageText:
//
//  EMS Data Access Layer Error:  An unknown database object state was encountered.
//
#define EMS_DAL_UNKOWN_OBJECTSTATE       ((EMS_RESULT)0x8004B910L)

//
// MessageId: EMS_DAL_RECORDTYPE_UNEXPECTED
//
// MessageText:
//
//  EMS Data Access Layer Error:  An unexpected record type was encountered..
//
#define EMS_DAL_RECORDTYPE_UNEXPECTED    ((EMS_RESULT)0x8004B911L)

//
// MessageId: EMS_DAL_QUERY_TIMEOUT
//
// MessageText:
//
//  EMS Data Access Layer Error:  A query operation timed out.
//
#define EMS_DAL_QUERY_TIMEOUT            ((EMS_RESULT)0x8004B912L)

//
// MessageId: EMS_DAL_CACHE_RETRIEVAL
//
// MessageText:
//
//  EMS Data Access Layer Info:  Caller has requested data from the cache.
//
#define EMS_DAL_CACHE_RETRIEVAL          ((EMS_RESULT)0x0004B913L)

//
// MessageId: EMS_DAL_META_RETRIEVAL
//
// MessageText:
//
//  EMS Data Access Layer Info:  Caller has requested meta information.
//
#define EMS_DAL_META_RETRIEVAL           ((EMS_RESULT)0x0004B914L)

//
// MessageId: EMS_DAL_CACHE_LIMIT_REACHED
//
// MessageText:
//
//  EMS Data Access Layer Error:  The resultset cache has reached its limit.  Results could not be cached.
//
#define EMS_DAL_CACHE_LIMIT_REACHED      ((EMS_RESULT)0x8004B915L)

//
// MessageId: EMS_DAL_SQL_KEYWORD_VIOLATION
//
// MessageText:
//
//  EMS Data Access Layer Error:  An attempt was made to use an SQL statement that may violate the system database's integrity:  %1.
//
#define EMS_DAL_SQL_KEYWORD_VIOLATION    ((EMS_RESULT)0x8004B916L)

//
// MessageId: EMS_DAL_EXCEPTION_UNHANDLED
//
// MessageText:
//
//  EMS Data Access Layer Error:  An unhandled exception has occurred.
//
#define EMS_DAL_EXCEPTION_UNHANDLED      ((EMS_RESULT)0x8004B917L)

//
// MessageId: EMS_DAL_QUERY_EXCEPTION
//
// MessageText:
//
//  EMS Data Access Layer Error:  An exception occurred while processing a query (SQL: %1) (Error: %2) (Line: %3, %4)
//
#define EMS_DAL_QUERY_EXCEPTION          ((EMS_RESULT)0x8004B918L)


#endif // INC_DALMSGS
