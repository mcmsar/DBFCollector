;/*********************************************************************
;*	              Copyright (c) 2008 by EMS Technologies, Inc.,
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

;#ifndef INC_BD_MSGS
;#define INC_BD_MSGS
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

MessageId=0xEC00 SymbolicName=EMS_BD_BASE_CODE Facility=ITF
Language=English
EMS Beacon Registry Web Service error.
.
MessageId=+1 SymbolicName=EMS_BDC_MISSING_REGISTRY Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: Connection information for web service was not found in the registry.
.
MessageId=+1 SymbolicName=EMS_BDC_GETIDERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to retrieve beacon ID from web service. (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_GETLOCERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to retrieve encoded location from web service. (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_GETTYPEERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to retrieve beacon type from web service. (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_SETCONNERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to set the web service connection config. (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_SETURLERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to set the web service connection URL.  (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_SETUSERERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Decoder Client: failed to set the web service connection user. (%1)
.
MessageId=+1 SymbolicName=EMS_BDC_SETPWDERROR Severity=ErrWarn Facility=ITF
Language=English
BeaconDecoder failed to set the web service connection password. (%1)
.
;
;#endif // INC_WSMSGS
