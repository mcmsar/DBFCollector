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


;#ifndef INC_RESOURCEMSG
;#define INC_RESOURCEMSG
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

MessageId=0xD400 SymbolicName=EMS_RESOURCE_BASE_CODE Facility=ITF
Language=English
EMS Data Resource error.
.
MessageId=+1 SymbolicName=EMS_RESOURCE_CHANNEL_RELEASED Severity=Info Facility=ITF
Language=English
EMS Data Resource:  The Stream Data Manager released the cached channel for URL %1.  It no longer has any consumers.
.
MessageId=+1 SymbolicName=EMS_RESOURCE_AUTHORITY_FMT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Database Resource:  An error occurred attempting to decode the authority portion of the specified URL.  The format of the authority, <%1>, may be incorrect.
.
;
;#endif
