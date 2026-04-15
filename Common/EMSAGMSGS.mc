;#ifndef INC_AGMSGS
;#define INC_AGMSGS
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

MessageId=0xC400 SymbolicName=EMS_AG_BASE_CODE Facility=ITF
Language=English
EMS Alert Generation Error
.
MessageId=+1 SymbolicName=EMS_AG_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Alert Generation Service Started
.
MessageId=+1 SymbolicName=EMS_AG_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Alert Generation Service Stopped
.
MessageId=+1 SymbolicName=EMS_AG_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Alert Generation Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_AG_GATEWAY_INITERR Severity=ErrWarn Facility=ITF
Language=English
EMS Alert Generation: Error initializing the Gateway connection (%1)
.
MessageId=+1 SymbolicName=EMS_AG_SERVICE_START_ERR Severity=ErrWarn Facility=ITF
Language=English
Failed to start Alert Generator service (%1).
.
MessageId=+1 SymbolicName=EMS_AG_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
Alert Generator failed due to unhandled exception (File: %1 Line: %2 hr = %3).
.
;
;#endif // INC_AGMSGS
