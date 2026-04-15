;/*******************************************************************************
;*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of Honeywell International, Inc.
;*
;********************************************************************************/

;#ifndef INC_INTERNAL_MODEL_MSGS
;#define INC_INTERNAL_MODEL_MSGS
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
	Info=0x1
	Warn=0x2
	Alarm=0x3
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xF550 SymbolicName=INTMODEL_BASE_CODE Facility=ITF
Language=English
Internal Model
.
MessageId=+1 SymbolicName=MEOINTERNALMODEL_PARSING_FAILURE Severity=ErrWarn Facility=ITF
Language=English
MeoLut Internal Model encountered %1 exception.  Details:  %2.
.
MessageId=+1 SymbolicName=MEOINTERNALMODEL_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
MeoLut Internal Model encountered a schema exception while parsing %1.  Details:  %2.
.
MessageId=+1 SymbolicName=MEOINTERNALMODEL_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
MeoLut Internal Model encountered a general exception while parsing %1.  Details:  %2.
.
;
;#endif // INC_INTERNAL_MODEL_MSGS
