;/********************************************************************
;*	Module:			BeaconAdvisoryMsgs.mc
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

;#ifndef INC_BARMSGS
;#define INC_BARMSGS
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

MessageId=0xEF70 SymbolicName=EMS_BAR_BASE_CODE Facility=ITF
Language=English
EMS Beacon Advisory Service Error
.
MessageId=+1 SymbolicName=EMS_BAR_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Beacon Advisory Service Started
.
MessageId=+1 SymbolicName=EMS_BAR_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_BAR_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Beacon Advisory Service Stopped
.
MessageId=+1 SymbolicName=EMS_BAR_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service reports error %1.
.
MessageId=+1 SymbolicName=EMS_BAR_TRACER Severity=Success Facility=ITF
Language=English
EMS Beacon Advisory Service Trace (%1).
.
MessageId=+1 SymbolicName=EMS_BAR_NOT_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service has not been initialized so cannot process the request.
.
MessageId=+1 SymbolicName=EMS_BAR_UNEXPECTED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected an unexpected exception.
.
MessageId=+1 SymbolicName=EMS_BAR_RECEIVECALIB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected error while receiving calib406 data (%1).
.
MessageId=+1 SymbolicName=EMS_BAR_PROCESSCALIB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected error while processing calib406 data (%1).
.
MessageId=+1 SymbolicName=EMS_BAR_CONFIG_OVERRIDE Severity=Success Facility=ITF
Language=English
EMS Beacon Advisory Service: Configuration value for "%1=%3" is out of range.  A value of %2 will be used instead.
.
MessageId=+1 SymbolicName=EMS_BAR_REPORT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected error while generating an advisory report (%1)
.
MessageId=+1 SymbolicName=EMS_BAR_RESTORE_UNSUPPORTED_VERSION Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service: Failed to restore data from file.  File has an unsupported version.
.
MessageId=+1 SymbolicName=EMS_BAR_RESTORE_READ_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to read the expected number of bytes.
.
MessageId=+1 SymbolicName=EMS_BAR_SAVE_WRITE_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to write the required number of bytes.
.
MessageId=+1 SymbolicName=EMS_BAR_LOADFILE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service: Error detected while attempting to restore data from file (%1)
.
MessageId=+1 SymbolicName=EMS_BAR_SAVEFILE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service: Error detected while attempting to save data to file (%1)
.
MessageId=+1 SymbolicName=EMS_BAR_BAD_DATA_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service: Configuration specified an invalid data directory.  The software will not be able to save across restarts.
.
MessageId=+1 SymbolicName=EMS_BAR_RECEIVELOCATE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected error while receiving locate data (%1).
.
MessageId=+1 SymbolicName=EMS_BAR_PROCESSLOCATE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Advisory Service detected error while processing locate data (%1).
.
;
;#endif // INC_BARMSGS

