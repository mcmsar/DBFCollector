;/********************************************************************
;*	Module:			HealthMonitorMsgs.mc
;*	Description: 	Message File for the Health Monitoring Service
;*
;*********************************************************************
;*	Copyright (c) 2009 by EMS Technologies, Inc.,
;*					All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/

;#ifndef INC_HMMSGS
;#define INC_HMMSGS
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

MessageId=0xEF50 SymbolicName=EMS_HM_BASE_CODE Facility=ITF
Language=English
EMS Health Monitor Service Error
.
MessageId=+1 SymbolicName=EMS_HM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Health Monitor Service Started
.
MessageId=+1 SymbolicName=EMS_HM_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_HM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Health Monitor Service Stopped
.
MessageId=+1 SymbolicName=EMS_HM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service reports error %1.
.
MessageId=+1 SymbolicName=EMS_HM_TRACER Severity=Success Facility=ITF
Language=English
EMS Health Monitor Service Trace (%1).
.
MessageId=+1 SymbolicName=EMS_HM_NOT_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service has not been initialized so cannot process the request.
.
MessageId=+1 SymbolicName=EMS_HM_UNEXPECTED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected an unexpected exception.
.
MessageId=+1 SymbolicName=EMS_HM_RECEIVECALIB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected error while receiving calib406 data (%1).
.
MessageId=+1 SymbolicName=EMS_HM_RECEIVELOGDATA_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected error while receiving log data (%1).
.
MessageId=+1 SymbolicName=EMS_HM_PROCESSCALIB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected error while processing calib406 data (%1).
.
MessageId=+1 SymbolicName=EMS_HM_PROCESSLOGDATA_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected error while processing log data (%1).
.
MessageId=+1 SymbolicName=EMS_HM_STATUSREPORT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Health Monitor Service detected error while generating a status report (%1).
.
;
;#endif // INC_HMMSGS

