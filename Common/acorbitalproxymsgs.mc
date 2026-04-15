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

;#ifndef INC_AC_ORBITAL_PROXY_MSGS
;#define INC_AC_ORBITAL_PROXY_MSGS
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

MessageId=0xE300 SymbolicName=EMS_AC_ORBITAL_PROXY_BASE_CODE Facility=ITF
Language=English
EMS Orbital Antenna Controller Proxy error.
.
MessageId=+1 SymbolicName=EMS_AC_ORBITAL_PROXY_AC_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbital Antenna Controller Proxy reports an error calling the antenna controller.  The error code is %1 and error message is "%2".
.
MessageId=+1 SymbolicName=EMS_AC_ORBITAL_PROXY_NO_URL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbital Antenna Controller Proxy reports that an endpoint URL was not specified.
.
MessageId=+1 SymbolicName=EMS_AC_ORBITAL_POXY_CREATE_INSTANCE_ERR_HR Severity=ErrWarn Facility=ITF
Language=English
EMS Orbital Antenna Controller Proxy: Unable to create instance of %1 during initialization (Error=%2).
.
MessageId=+1 SymbolicName=EMS_AC_ORBITAL_POXY_UPDATE_ANTENNA_INFO_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Orbital Antenna Controller Proxy: Unable to update antenna status info (Error=%1).
.
;
;#endif // INC_AC_ORBITAL_PROXY_MSGS
