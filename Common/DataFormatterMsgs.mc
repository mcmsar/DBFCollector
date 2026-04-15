;/********************************************************************
;*	Module:			DataFormatterMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Data Formatter Errors & Messages
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


;#ifndef INC_DATAFORMATTERMSG
;#define INC_DATAFORMATTERMSG
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

MessageId=0xD900 SymbolicName=EMS_DATA_FORMATTER_BASE_CODE Facility=ITF
Language=English
EMS Database Resource error.
.
MessageId=+1 SymbolicName=EMS_FMTER_NO_METHOD Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred attempting to translate a data format.  The format method could not be determined.
.
MessageId=+1 SymbolicName=EMS_FMTER_INVALID_METHOD Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred attempting to translate a data format.  The specified translation method, <%1>, is not supported.
.
MessageId=+1 SymbolicName=EMS_FMTER_RESOURCE_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred attempting to translate a data format.  A pointer to the resource plug-in could not be obtained.
.
MessageId=+1 SymbolicName=EMS_FMTER_RESOURCE_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred while accessing a resource.  Error code is <%1> and description is <%2>.
.
MessageId=+1 SymbolicName=EMS_FMTER_META_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred while attempting to retrieve meta information.
.
MessageId=+1 SymbolicName=EMS_FMTER_RAW_DATA_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred while attempting to retrieve raw data.
.
MessageId=+1 SymbolicName=EMS_FMTER_REC_READER_NULL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred while attempting to retrieve a database record accessor.
.
MessageId=+1 SymbolicName=EMS_FMTER_OUTPUT_BUFFER_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter:  An error occurred while attempting to write converted data to the supplied array.  The array is no large enough.
.
MessageId=+1 SymbolicName=EMS_FMTER_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Formatter captured an unknown exception.
.
;
;#endif
