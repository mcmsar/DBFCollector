;/********************************************************************
;*	Module:			JrnlMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS DB Journal Errors & Messages
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
;#ifndef INC_JRNLMSGS
;#define INC_JRNLMSGS
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

MessageId=0xA100 SymbolicName=EMS_DBJOURNAL_BASE_CODE Facility=ITF
Language=English
EMS DB Journal Error
.
MessageId=+1 SymbolicName=EMS_JRNL_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Started
.

MessageId=+1 SymbolicName=EMS_JRNL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Stopped
.
MessageId=+1 SymbolicName=EMS_JRNL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS DB Journal reports error %1.
.
MessageId=+1 SymbolicName=EMS_JRNL_DB_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS DB Journal reports error %1 while accessing database record %2.
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_JRNL_TLEDUPKEY Severity=Success Facility=ITF
Language=English
EMS DB Journal Service reports duplicate primary key writing satellite %1 data to ORBIT_DATA table.
.
MessageId=+1 SymbolicName=EMS_JRNL_START_DBCLEAN Severity=Success Facility=ITF
Language=English
EMS DB Journal Starting Database Clean.
.
MessageId=+1 SymbolicName=EMS_JRNL_STOP_DBCLEAN Severity=Success Facility=ITF
Language=English
EMS DB Journal Finished Database Clean.
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER_AUDIORIFFDATA Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( BeaconID=%1, time=%2, Sat ID=%3, Lut ID=%4 )
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER_LOCATEDATA Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( time=%1, type=%2, ID=%3 )
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER_CALIBCBC Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER_RESIDUALDATA Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
.
MessageId=+1 SymbolicName=EMS_JRNL_TRACER_DBCLEAN Severity=Success Facility=ITF
Language=English
EMS DB Journal Service Tracer ( DBClean returns %1 )
.
MessageId=+1 SymbolicName=EMS_JRNL_INIT_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS DB Journal initialization failed with an unhandled exception.
.
MessageId=+1 SymbolicName=EMS_JRNL_DB_ERROR_DUPKEY Severity=ErrWarn Facility=ITF
Language=English
EMS DB Journal reports a duplicate primary key error (%1).
.
;
;#endif // INC_JRNLMSGS
