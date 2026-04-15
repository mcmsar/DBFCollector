;/********************************************************************
;*	Module:			C406Msgs.mc
;*	Process ID: 
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Combine 406 Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
;*					All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
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
;	0.0	01/05/21		rvw	start
;
;********************************************************************/
;#ifndef INC_C406MSGS
;#define INC_C406MSGS
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

MessageId=0xBD00 SymbolicName=EMS_COMB406_BASE_CODE Facility=ITF
Language=English
EMS Combine406 Error
.
MessageId=+1 SymbolicName=EMS_COMB406_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Combine406 Service Started
.
MessageId=+1 SymbolicName=EMS_COMB406_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS Combine406 Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_COMB406_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Combine406 Service Stopped
.
MessageId=+1 SymbolicName=EMS_COMB406_PROCESSING_START Severity=Success Facility=ITF
Language=English
EMS Combine406 Processing %1 records.
.
MessageId=+1 SymbolicName=EMS_COMB406_PROCESSING_STOP Severity=Success Facility=ITF
Language=English
EMS Combine406 completed proccessing.
.
MessageId=+1 SymbolicName=EMS_COMB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Combine406 reports error %1.
.
MessageId=+1 SymbolicName=EMS_COMB406_FORCED_UNLOCK Severity=ErrWarn Facility=ITF
Language=English
EMS Combine406 forced an UNLOCK
.
MessageId=+1 SymbolicName=EMS_COMB406_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Combine406 received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMB406_TRACER Severity=Success Facility=ITF
Language=English
EMS Combine406 tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMB406_SUMMARY Severity=Success Facility=ITF
Language=English
EMS Combine406 Summary ( %1 ).
.
MessageId=+1 SymbolicName=EMS_COMB406_GEOSARR_BUFFER_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Combine406 GEOSarr buffer overflow has occurred.
.
MessageId=+1 SymbolicName=EMS_COMB406_GEOSARR_DATA_ADD_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Combine406: Failed to add GEOSarr data to buffer (%1:%2)
.
MessageId=+1 SymbolicName=EMS_COMB406_TRACER_CALIB406READ Severity=Success Facility=ITF
Language=English
EMS Combine406 tracer ( %1 Calib406 Records read ).
.
MessageId=+1 SymbolicName=EMS_COMB406_CONFIGREAD_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error reading %1 configuration, using %2.
.
;
;#endif // INC_C406MSGS
