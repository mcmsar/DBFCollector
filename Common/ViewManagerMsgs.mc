;/********************************************************************
;*	Module:			SolutionDisplayMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Solution Display Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2004 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_SOLNDISPMSG
;#define INC_SOLNDISPMSG
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

MessageId=0xCB00 SymbolicName=EMS_VIEW_MANAGER_BASE_CODE Facility=ITF
Language=English
EMS View Manager.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEWS_FORMAT_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS View Manager reports that the Views configuration is invalid.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEWS_LOAD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred loading views from file <%1>.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEWS_LOAD_NO_CHILD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to retrieve the first child node of a loaded Views configuration.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEW_LOAD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to load an XML view string into the DOM.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEW_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to retrieve the view named <%1>.  It could not be found in the list of available views.
.
MessageId=+1 SymbolicName=EMS_VIEWMGR_VIEW_ALREADY_EXISTS Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to create a new view named <%1>.  A view of this name already exists.
.
;
;#endif
