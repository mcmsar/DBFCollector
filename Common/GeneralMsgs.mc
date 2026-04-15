;/********************************************************************
;*	Module:			GeneralMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for General Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
;*	All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_GENERALMSG
;#define INC_GENERALMSG
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

MessageId=0xC900 SymbolicName=EMS_GENERAL_BASE_CODE Facility=ITF
Language=English
General messages.
.
MessageId=+1 SymbolicName=EMS_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred.  The error code is %1.
.
MessageId=+1 SymbolicName=EMS_GENERAL_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred.  No error code could be retrieved.
.
MessageId=+1 SymbolicName=EMS_GENERAL_CANNOT_OPEN_SCM Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred:  Cannot open the service control manager.
.
MessageId=+1 SymbolicName=EMS_GENERAL_CANNOT_OPEN_SERVICE Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred:  Cannot open (%1) service from the control manager.
.
MessageId=+1 SymbolicName=EMS_GENERAL_NO_CALLER_ID Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred:  Cannot connect to Gateway because the caller's identifier has not been specified.
.
MessageId=+1 SymbolicName=EMS_GENERAL_GATEWAY_CALL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
A failure has occurred:  A Gateway call has returned error code (%1) with description (%2).
.
MessageId=+1 SymbolicName=EMS_GENERAL_INVALID_LOCALE Severity=ErrWarn Facility=ITF
Language=English
Could not initialize language resources. Invalid locale.
.
MessageId=+1 SymbolicName=EMS_GENERAL_NO_DB_CONNECTION Severity=ErrWarn Facility=ITF
Language=English
There is no database connection available to process this request.
.
MessageId=+1 SymbolicName=EMS_GENERAL_XML_FILE_LOAD_FAIL Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to load the XML file, (%1):  error code = (%2), reason = (%3), source = (%4).
.
MessageId=+1 SymbolicName=EMS_GENERAL_XML_LOAD_FAIL Severity=ErrWarn Facility=ITF
Language=English
An error occurred attempting to load XML from a string:  error code = (%1), reason = (%2), source = (%3).
.
MessageId=+1 SymbolicName=EMS_TREE_STATUS_UPDATE_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to update the LUT status displayed in the tree view.
.
MessageId=+1 SymbolicName=EMS_TREE_STATUS_INIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to initialize the tree view LUT status display.
.
MessageId=+1 SymbolicName=EMS_LUTMONITOR_LAUNCH_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to launch LUT Monitor due to error: "%1"
.
MessageId=+1 SymbolicName=EMS_CONFIGURATION_ITEM_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
Failed to find a configuration item: "%1".
.
MessageId=+1 SymbolicName=EMS_NSP_ERROR Severity=ErrWarn Facility=ITF
Language=English
An error has occurred in the NSP library.  Status = (%1), Function = (%2), Context = (%3), File = (%4), Line = (%5)
.
MessageId=+1 SymbolicName=EMS_SOAP_CALL_ERROR Severity=ErrWarn Facility=ITF
Language=English
A SOAP call failed.  Fault code = %1.  Fault string = %2.  Detail = %3
.
MessageId=+1 SymbolicName=EMS_SOAP_FRAMEWORK_ERROR Severity=ErrWarn Facility=ITF
Language=English
A SOAP call failed.  The SOAP framework encountered an error with code = %1.
.
MessageId=+1 SymbolicName=EMS_INVALID_FILTERHEXVALUE Severity=ErrWarn Facility=ITF
Language=English
Failed to build query.  Invalid hex filter value specified.
.
;
;#endif
