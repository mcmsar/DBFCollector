;#ifndef INC_DACMSGS
;#define INC_DACMSGS
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

MessageId=0xBB00 SymbolicName=EMS_DAC_BASE_CODE Facility=ITF
Language=English
EMS Data Acquisition Error
.
MessageId=+1 SymbolicName=EMS_DAC_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Data Acquisition Service Started
.
MessageId=+1 SymbolicName=EMS_DAC_LUTTYPE_REJECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition not accepting data type: %1
.
MessageId=+1 SymbolicName=EMS_DAC_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Data Acquisition received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_DAC_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Data Acquisition Service Stopped.
.
MessageId=+1 SymbolicName=EMS_DAC_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_DAC_BAD_RETR_INTERVAL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition - Time interval specified for data retrieval is too large.
.
MessageId=+1 SymbolicName=EMS_DAC_BAD_ARRAYINDEX Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition - Array index out of bounds.
.
MessageId=+1 SymbolicName=EMS_DAC_SENDDATAREQ_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition - Error sending data request: DataType: %1
.
MessageId=+1 SymbolicName=EMS_DAC_LUTTYPE_REJECTED_DETAILS Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition not accepting data type: %1 from LUT: %2. %3
.
MessageId=+1 SymbolicName=EMS_DAC_LUTTYPE_LOG_REJECTED_DETAILS Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition not accepting data type: %1 from LUT: %2. %3 %4 %5 %6
.
MessageId=+1 SymbolicName=EMS_DAC_DATAWRITEFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Acquisition data write failed. Channel Type: %1.
.
;
;#endif // INC_DACMSGS
