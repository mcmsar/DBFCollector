;#ifndef INC_LMMSGS
;#define INC_LMMSGS
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

MessageId=0xC500 SymbolicName=EMS_LM_BASE_CODE Facility=ITF
Language=English
EMS LUT Monitor Error
.
MessageId=+1 SymbolicName=EMS_LM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS LUT Monitor Service Started
.
MessageId=+1 SymbolicName=EMS_LM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS LUT Monitor Service Stopped.
.
MessageId=+1 SymbolicName=EMS_LM_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS LUT Monitor Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_LM_COMM_CHECK_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS LUT Monitor - Comms check failed, LUT: %1
.
MessageId=+1 SymbolicName=EMS_LM_FAILED_CONFIGLUTGET Severity=ErrWarn Facility=ITF
Language=English
Unable to retrieve configured LUTs list.
.
MessageId=+1 SymbolicName=EMS_LM_NULLGROUPID Severity=ErrWarn Facility=ITF
Language=English
NULL Group ID returned.
.
;
;#endif // INC_DACMSGS
