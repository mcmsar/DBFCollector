;/********************************************************************
;*	Module:			DataIOMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Data IO Errors & Messages
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


;#ifndef INC_DATAIOMSG
;#define INC_DATAIOMSG
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

MessageId=0xD600 SymbolicName=EMS_DATAIO_BASE_CODE Facility=ITF
Language=English
EMS File Resource error.
.
MessageId=+1 SymbolicName=EMS_DATAIO_SCHEME_MAPPING_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  Could not find mapping to a resource accessor class identifier for the URL scheme <%1>.
.
MessageId=+1 SymbolicName=EMS_DATAIO_CREATION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  The error <%1> occurred when attempting to create an instance of the resource class with identifier <%2>.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NO_RESOURCE Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An attempt has been made to access a resource, but no accessor has been created.
.
MessageId=+1 SymbolicName=EMS_DATAIO_RESOURCE_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while accessing a resource.  Error code is <%1> and description is <%2>.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NO_MODE_SET Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while attempting to access a resource.  An invalid access mode was specified.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NO_URL_SET Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while attempting to access a resource.  No URL was specified.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NULL_RESOURCE Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while attempting to access a resource.  The resource object could not be created.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NULL_FORMATTER Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while attempting to access a resource.  The specified formatter object could not be created.
.
MessageId=+1 SymbolicName=EMS_DATAIO_NO_RES_FOR_FORMATTER Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error occurred while attempting to assign a resource to a formatter object.  The resource object has not been initialized.
.
MessageId=+1 SymbolicName=EMS_DATAIO_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO captured an unknown exception.
.
MessageId=+1 SymbolicName=EMS_DATAIO_URL_NO_SCHEME Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred processing an URL.  No scheme could be found in the supplied URL, <%1>.
.
MessageId=+1 SymbolicName=EMS_DATAIO_FORMAT_NO_CLASSID Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred retrieving a formatting object.  No class identifier could be found in the formatting instructions.
.
MessageId=+1 SymbolicName=EMS_DATAIO_FORMAT_NO_CLASSID_STRING Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred retrieving a formatting object.  The class identifier in the formatting instructions is empty.
.
MessageId=+1 SymbolicName=EMS_DATAIO_FORMAT_LOAD_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred retrieving a formatting object.  The class with identifier <%1> could not be created.
.
MessageId=+1 SymbolicName=EMS_DATAIO_FORMAT_NO_METHOD Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred retrieving a formatting object.  No method could be found in the formatting instructions.
.
MessageId=+1 SymbolicName=EMS_DATAIO_FORMAT_NO_METHOD_STRING Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  An error has occurred retrieving a formatting object.  The method in the formatting instructions is empty.
.
MessageId=+1 SymbolicName=EMS_DATAFORMATTER_CREATION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data IO:  The error <%1> occurred when attempting to create an instance of the data formatter class with identifier <%2>.
.
;
;#endif
