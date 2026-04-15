;/********************************************************************
;*	Module:			PasschedMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Pass Schedule Service
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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
;	0.0	2007 Feb 1		RVW	
;
;********************************************************************/
;#ifndef INC_PASSCHEDMSGS
;#define INC_PASSCHEDMSGS
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;

MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
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

MessageId=0xE000 SymbolicName=EMS_PASSCHED_BASE_CODE Facility=ITF
Language=English
EMSPassSchedService Error
.
MessageId=+1 SymbolicName=EMS_PASSCHED_SERVICE_START Severity=Success Facility=ITF
Language=English
EMSPassSchedService Started
.
MessageId=+1 SymbolicName=EMS_PASSCHED_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMSPassSchedService did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_PASSCHED_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMSPassSchedService Stopped
.
MessageId=+1 SymbolicName=EMS_PASSCHED_ERROR Severity=Alarm Facility=ITF
Language=English
EMSPassSchedService reports error %1.
.
MessageId=+1 SymbolicName=EMS_PASSCHED_LOG_EXCEPTION Severity=Alarm Facility=ITF
Language=English
EMSPassSchedService reports an exception
.
MessageId=+1 SymbolicName=EMS_PASSCHED_TRACER Severity=Success Facility=ITF
Language=English
EMSPassSchedService tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_PASSCHED_CONFIG Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Tracer ( cfg: %1=%2 )
.
;#endif // INC_PASSCHEDMSGS



