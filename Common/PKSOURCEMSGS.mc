;#ifndef INC_PKSRCRETRY_MSGS
;#define INC_PKSRCRETRY_MSGS
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

MessageId=0x5A00 SymbolicName=EMS_PKSRC_BASE_CODE Facility=ITF
Language=English
EMS Retry Packet Source Error.
.
MessageId=+1 SymbolicName=EMS_PKSRC_RETRY Severity=Success Facility=ITF
Language=English
EMS Retry Packet Source - Retrying Write to Pipeline %1.
.
;
;#endif // INC_PKSRCRETRY_MSGS
