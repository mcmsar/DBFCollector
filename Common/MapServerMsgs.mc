;/********************************************************************
;*	Module:			MapServerMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Map Server Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2005 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_MAPSERVERMSG
;#define INC_MAPSERVERMSG
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

MessageId=0xCA00 SymbolicName=EMS_MAP_SERVER_BASE_CODE Facility=ITF
Language=English
EMS Map Server error.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_SESSION_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  Session with identifier <%1> could not be retrieved from the Session Manager.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_MAPX_NO_PARENT_WINDOW Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  Could not create a MapX object because no parent window was specified.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_MAPX_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  An exception was thrown by the MapX component.  The error code is <%1> and description is <%2>.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_MAPX_UNSUPPORTED_CONTAINED_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  A request was made to return a map object as an unsupported type.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_MAPX_UNSUPPORTED_FEATURE_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  An attempt to use an unsupported feature type has occurred.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_NO_MAPX_LICENSE Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  Could not retrieve the license key for the MapX component.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_MAPX_CREATE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  Failed to create an instance of the MapX component.
.
MessageId=+1 SymbolicName=EMS_MAP_SERVER_INVALID_PARTS Severity=ErrWarn Facility=ITF
Language=English
EMS Map Server:  A part within a feature does not have enough points for the feature type.  It has %1 point(s), but requires a minimum of %2 point(s).
.
;
;#endif
