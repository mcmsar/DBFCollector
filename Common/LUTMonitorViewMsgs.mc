;/********************************************************************
;*	Module:			LUTMonitorViewMsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for LUT Monitor View Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2006 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_LUTMONVIEWMSG
;#define INC_LUTMONVIEWMSG
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

MessageId=0xDD00 SymbolicName=EMS_LUT_MON_VIEW_BASE_CODE Facility=ITF
Language=English
EMS LUT Monitor View error.
.
MessageId=+1 SymbolicName=EMS_LUT_MON_VIEW_UKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS LUT Monitor View reports that an error has occurred.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_LUT_MON_VIEW_TITLE Severity=Info Facility=ITF
Language=English
EMS LUT Monitor View
.
;
;#endif
