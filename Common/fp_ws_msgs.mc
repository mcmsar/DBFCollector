;/*********************************************************************
;*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

;#ifndef INC_FP_WS_MSGS
;#define INC_FP_WS_MSGS
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

MessageId=0xE200 SymbolicName=EMS_FP_WS_BASE_CODE Facility=ITF
Language=English
EMS FP Web Service error.
.
MessageId=+1 SymbolicName=EMS_FP_WS_NO_CONFIGURATION Severity=ErrWarn Facility=ITF
Language=English
EMS FP Web Service had not been initialized with configuration.
.
MessageId=+1 SymbolicName=EMS_FP_WS_NO_CLASSID Severity=ErrWarn Facility=ITF
Language=English
EMS FP Web Service could not find a plugin class ID in the supplied configuration.  The plugin cannot be loaded.
.
;
;#endif // INC_WSMSGS
