;/********************************************************************
;*	Module:			TCalMsgs.mc
;*	Process ID: 
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS TCAL Messages
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
;#ifndef INC_TCALMSGS
;#define INC_TCALMSGS
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

MessageId=0xAC00 SymbolicName=EMS_TCAL_BASE_CODE Facility=ITF
Language=English
EMS TCAL Error
.
MessageId=+1 SymbolicName=EMS_TCAL_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS TCAL Service Started
.
MessageId=+1 SymbolicName=EMS_TCAL_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS TCAL Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_TCAL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS TCAL Service Stopped
.
MessageId=+1 SymbolicName=EMS_TCAL_PROCESSING_START Severity=Success Facility=ITF
Language=English
EMS TCAL Processing %1 records.
.
MessageId=+1 SymbolicName=EMS_TCAL_PROCESSING_STOP Severity=Success Facility=ITF
Language=English
EMS TCAL completed proccessing.
.
MessageId=+1 SymbolicName=EMS_TCAL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS TCAL reports error %1.
.
MessageId=+1 SymbolicName=EMS_TCAL_FORCED_UNLOCK Severity=ErrWarn Facility=ITF
Language=English
EMS TCAL forced an UNLOCK
.
MessageId=+1 SymbolicName=EMS_TCAL_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS TCAL received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_TRACER Severity=Success Facility=ITF
Language=English
EMS TCAL tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_SUMMARY Severity=Success Facility=ITF
Language=English
EMS TCAL Summary ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_BOUNDS_ALARM Severity=Success Facility=ITF
Language=English
EMS TCAL reports out of bounds condition ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_UPDATE Severity=Success Facility=ITF
Language=English
EMS TCAL has been updated ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_REJECTED Severity=Success Facility=ITF
Language=English
EMS TCAL has insufficient data to update ( %1 ).
.
MessageId=+1 SymbolicName=EMS_TCAL_SUMMARY_COUNTREAD Severity=Success Facility=ITF
Language=English
EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records read )
.
MessageId=+1 SymbolicName=EMS_TCAL_SUMMARY_COUNTWRITTEN Severity=Success Facility=ITF
Language=English
EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records written )
.
MessageId=+1 SymbolicName=EMS_TCAL_SUMMARY_COUNTUSED Severity=Success Facility=ITF
Language=English
EMS TCAL Summary ( Sat %1, %2 TCalSarp records being used )
.
MessageId=+1 SymbolicName=EMS_TCAL_TRACE_CONFIG Severity=Success Facility=ITF
Language=English
EMS TCAL tracer ( TCal config: SatId  %1, minUpdatePeriod %2, maxTimeSpan %3, minMeas %4, maxTSarpThresh %5, maxSarpFCThresh %6 )
.
MessageId=+1 SymbolicName=EMS_TCAL_BOUNDS_ALARMERR Severity=ErrWarn Facility=ITF
Language=English
EMS TCAL reports out of bounds condition ( Sat %1, rollErr %2 (%3) secs, fcErr %4 (%5) Hz, sdRes %6 secs )
.
MessageId=+1 SymbolicName=EMS_TCAL_BOUNDS_ALARMTSPAN Severity=ErrWarn Facility=ITF
Language=English
EMS TCAL reports out of bounds condition ( Sat %1, tSpan %2 (%3) days, nMeas %4 (%5) )
.
MessageId=+1 SymbolicName=EMS_TCAL_UPDATE_PART1 Severity=Success Facility=ITF
Language=English
EMS TCAL has been updated ( Sat %1, orb %2, span %3 days, pts %4, mean/sdev/max %5 msec )
.
MessageId=+1 SymbolicName=EMS_TCAL_UPDATE_PART2 Severity=Success Facility=ITF
Language=English
EMS TCAL has been updated ( cycles %1 msec, TSarpOffset %2 msec, corr %3, SarpFC %4 Hz )
.
MessageId=+1 SymbolicName=EMS_TCAL_REJECTED_DAYSSINCE Severity=ErrWarn Facility=ITF
Language=English
EMS TCAL has insufficient data to update ( Sat %1, TCAL not performed, only %2 (%3) days since TSarp last updated )
.
;
;#endif // INC_TCALMSGS
