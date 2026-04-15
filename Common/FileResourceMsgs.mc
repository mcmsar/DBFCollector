;/********************************************************************
;*	Module:			FileResourceMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for File Resource Errors & Messages
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


;#ifndef INC_FILERESOURCEMSG
;#define INC_FILERESOURCEMSG
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

MessageId=0xD700 SymbolicName=EMS_FILE_RESOURCE_BASE_CODE Facility=ITF
Language=English
EMS File Resource error.
.
MessageId=+1 SymbolicName=EMS_FRES_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource captured an unknown exception.
.
MessageId=+1 SymbolicName=EMS_FRES_NO_URL_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred when attempting to open a stream to the resource.  No URL was specified.
.
MessageId=+1 SymbolicName=EMS_FRES_NO_MODE_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred when attempting to open a stream to the resource.  No access mode was specified.
.
MessageId=+1 SymbolicName=EMS_FRES_NO_PATH_ON_OPEN Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred when attempting to open a stream to the resource.  No path was specified in the URL, <%1>.
.
MessageId=+1 SymbolicName=EMS_FRES_ACTIVATE_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred attempting to activate a file resource.  This type of resource cannot operate in active mode.
.
MessageId=+1 SymbolicName=EMS_FRES_DEACTIVATE_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred attempting to deactivate a file resource.  This type of resource cannot operate in active mode.
.
MessageId=+1 SymbolicName=EMS_FRES_NOURL Severity=ErrWarn Facility=ITF
Language=English
EMS File Resource:  An error occurred attempting to access a resource.  No URL has been specified.
.
;
;#endif
