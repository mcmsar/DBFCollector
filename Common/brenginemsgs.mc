;/*********************************************************************
;*	              Copyright (c) 2007 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/

;/*******************************************************************

 ; Revision Record

;	$Log:
;	$
;********************************************************************/

;#ifndef INC_BRENGINE_MSGS
;#define INC_BRENGINE_MSGS
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

MessageId=0xEA00 SymbolicName=EMS_BRENGINE_BASE_CODE Facility=ITF
Language=English
EMS Beacon Registry Engine error.
.
MessageId=+1 SymbolicName=EMS_BR_ENGINE_DBINSERT Severity=Success Facility=ITF
Language=English
EMS Beacon Registry:  Successfully inserted new record for beacon %1.
.
MessageId=+1 SymbolicName=EMS_BR_ENGINE_DBINSERT_ERRORS Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Registry: Errors encountered while performing inserts. Check server log for details.
.
MessageId=+1 SymbolicName=EMS_BR_ENGINE_DBINSERT_FAIL Severity=Success Facility=ITF
Language=English
EMS Beacon Registry:  Successfully deleted record for beacon %1.
.
MessageId=+1 SymbolicName=EMS_BR_ENGINE_DBUPDATE Severity=Success Facility=ITF
Language=English
EMS Beacon Registry:  Successfully updated record for beacon %1.
.
MessageId=+1 SymbolicName=EMS_BR_ENGINE_DBDELETE Severity=Success Facility=ITF
Language=English
EMS Beacon Registry:  Successfully deleted record for beacon %1.
.
;
;#endif // INC_WSMSGS
