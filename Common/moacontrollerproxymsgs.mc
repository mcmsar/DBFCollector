;/*********************************************************************
;*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

;#ifndef INC_MOA_CONTROLLER_PROXY_MSGS
;#define INC_MOA_CONTROLLER_PROXY_MSGS
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

MessageId=0xF400 SymbolicName=EMS_MOA_CONTROLLER_PROXY_BASE_CODE Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy error.
.
MessageId=+1 SymbolicName=EMS_MOAPOXY_CREATE_INSTANCE_ERR_HR Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy: Unable to create instance of %1 during initialization (Error=%2).
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_PROXY_AC_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports an error calling the antenna controller.  The error code is %1 and error message is "%2".
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_PROXY_NO_URL Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports that an endpoint URL was not specified.
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_PROXY_NO_LOCATION Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports an error getting the site location (hr=%1).
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_POXY_UPDATE_ANTENNA_INFO_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports an error getting the site location (hr=%1).
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_POXY_UPDATE_ORBIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports an error updating orbit data for satellite %1 (hr=%2).
.
MessageId=+1 SymbolicName=EMS_MOA_CONTROLLER_POXY_TRACKING_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS MEO Optimized Antenna Controller Proxy reports the antenna has failed to track satellite %1 within %2 seconds.
.
;
;#endif // INC_MOA_CONTROLLER_PROXY_MSGS
