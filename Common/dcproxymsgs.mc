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

;#ifndef INC_DC_PROXY_MSGS
;#define INC_DC_PROXY_MSGS
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

MessageId=0xE400 SymbolicName=EMS_DC_PROXY_BASE_CODE Facility=ITF
Language=English
EMS Data Collector Proxy error.
.
MessageId=+1 SymbolicName=EMS_DC_PROXY_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Collector Proxy reports an error calling the data collector.  The error code is %1 and error message is "%2".
.
MessageId=+1 SymbolicName=EMS_DC_PROXY_NO_URL Severity=ErrWarn Facility=ITF
Language=English
EMS Data Collector Proxy reports that an endpoint URL was not specified.
.
;
;#endif // INC_DC_PROXY_MSGS
