;/********************************************************************
;*	Module:			ODetMsgs.mc
;*	Process ID: 
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Orbit Determination Messages
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
;#ifndef INC_ODETMSGS
;#define INC_ODETMSGS
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

MessageId=0xA700 SymbolicName=EMS_ODET_BASE_CODE Facility=ITF
Language=English
EMS OrbitDet Error
.
MessageId=+1 SymbolicName=EMS_ODET_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS OrbitDet Service Started
.
MessageId=+1 SymbolicName=EMS_ODET_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS OrbitDet Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_ODET_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS OrbitDet Service Stopped
.
MessageId=+1 SymbolicName=EMS_ODET_PROCESSING_START Severity=Success Facility=ITF
Language=English
EMS OrbitDet Processing %1 records.
.
MessageId=+1 SymbolicName=EMS_ODET_PROCESSING_STOP Severity=Success Facility=ITF
Language=English
EMS OrbitDet completed proccessing.
.
MessageId=+1 SymbolicName=EMS_ODET_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS OrbitDet reports error %1.
.
MessageId=+1 SymbolicName=EMS_ODET_FORCED_UNLOCK Severity=ErrWarn Facility=ITF
Language=English
EMS OrbitDet forced an UNLOCK
.
MessageId=+1 SymbolicName=EMS_ODET_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS OrbitDet received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_ODET_SUMMARY Severity=Success Facility=ITF
Language=English
EMS OrbitDet Summary ( %1 ).
.
MessageId=+1 SymbolicName=EMS_ODET_BOUNDS_ALARM Severity=Success Facility=ITF
Language=English
EMS OrbitDet reports out of bounds condition { Sat, Pos, Pts, StDev = %1 }
.
MessageId=+1 SymbolicName=EMS_ODET_TLE_UPDATE Severity=Success Facility=ITF
Language=English
EMS OrbitDet has updated TLE vector.
.
MessageId=+1 SymbolicName=EMS_ODET_TLE_REJECTED Severity=Success Facility=ITF
Language=English
EMS OrbitDet has insufficient data to update TLE vector.
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_TRACKRECSREAD Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records read)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_CALIB406RECSREAD Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records read)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_CALIB406RECSACC Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records accepted)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_TRACKRECSWRITTEN Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records written)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_ENDOFPASS Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) EndOfPass)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_LOCKED Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Locked)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_UNLOCKED Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Unlocked)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_UNEXPECTEDSTATE Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer (_DoEndOfPass : Unexpected State(%1))
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_MISMATCHEDSAT Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer (_DoEndOfPass : Sat %1 != Sat %2)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_CONFIGTHRESHOLDS Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer (OrbitDet config: SatId  %1, PosThr %2 km, VelThr %3 m/sec, DurMax %4 days, ItrMin %5, ItrMax %6)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_CONFIGRESIDUALSTRUE Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk TRUE, MinPts %3)
.
MessageId=+1 SymbolicName=EMS_ODET_TRACER_CONFIGRESIDUALSFALSE Severity=Success Facility=ITF
Language=English
EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk FALSE, MinPts %3)
.
MessageId=+1 SymbolicName=EMS_ODET_PROCESSING_STARTSATPASS Severity=Success Facility=ITF
Language=English
EMS OrbitDet Processing Start (SatID=%1,Pass=%2).
.
MessageId=+1 SymbolicName=EMS_ODET_SUMMARYDETAILS Severity=Success Facility=ITF
Language=English
EMS OrbitDet Summary ( SatID=%1,Pass=%2, pos=%3, vel=%4, std=%5, num=%6 )
.
MessageId=+1 SymbolicName=EMS_ODET_BOUNDS_ALARMDETAILS Severity=ErrWarn Facility=ITF
Language=English
EMS OrbitDet reports out of bounds condition { Sat, Pos, Vel, Pts, StDev = %1, %2, %3, %4, %5 }
.
MessageId=+1 SymbolicName=EMS_ODET_POST_MANOEUVRE Severity=Success Facility=ITF
Language=English
EMS OrbitDet will exclude all data from Sat ID %1 prior to %2.
.
;
;#endif // INC_ODETMSGS
