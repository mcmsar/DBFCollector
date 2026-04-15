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

MessageId=0xC800 SymbolicName=EMS_SOLN_DISP_BASE_CODE Facility=ITF
Language=English
EMS Solution Display error.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_ADD_CHILD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred adding a <%1> child node to <%2>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_VIEWS_LOAD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred loading views from file <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_GET_SOURCE_NODE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to retrieve a source node.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_CLONE_NODE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to clone a source node.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_CHILD_ADD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
An error occurred while attempting to add the child element <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_ELEMENT_NOT_FOUND_IN_LAYER Severity=ErrWarn Facility=ITF
Language=English
An error occurred because the element <%1> could not be found in a layer configuration.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_FAILED_TO_CREATE_CHILD_NODE Severity=ErrWarn Facility=ITF
Language=English
An error occurred while attempting to add the child node <%1> to <%2>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_ROOT_NODE Severity=ErrWarn Facility=ITF
Language=English
An error occurred while attempting to retrieve a root node.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_INVALID_BEACON_TYPE Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  An attempt was made to create a configuration profile for an unsupported beacon type, <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  An unrecognized beacon type was specified, <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_BEACON_TYPE Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  No beacon type was specified in a request to display solutions.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_UNKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Solution Display reports that an error has occurred.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_TITLE Severity=Info Facility=ITF
Language=English
EMS Solution Display
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_BEACON_TYPE_CONFIG_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  Unable to retrieve configuration for beacon type <%1> from the view configuration.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_RGB_VALUE_OUT_OF_RANGE Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  An out of range RGB value of <%1> was specified.  Values must be in the range <%2> to <%3>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_LUT_CONFIG_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  Unable to retrieve configuration for LUT <%1> from the view configuration.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SAT_CONFIG_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  Unable to retrieve configuration for Satellite <%1> from the view configuration.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_CURRENT_VIEW Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  No View Configuration has been selected.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_SESSION Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  The Solution Display does not have a session identifier.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_PROVIDER_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  An exception was thrown by the map provider.  The error code is <%1> and description is <%2>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_BEACON_DETAILS Severity=ErrWarn Facility=ITF
Language=English
Detailed information for the selected beacon could not be found.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_MUTUAL_CONFIG_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  Unable to retrieve Mutual Visibility configuration for LUT <%1> from the view configuration.
.
;
;#endif
