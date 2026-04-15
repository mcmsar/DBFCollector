;/********************************************************************
;*	Module:			StormManagerMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Storm Manager Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2006 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;

;#ifndef INC_STORMMANAGERMSGS
;#define INC_STORMMANAGERMSGS
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

MessageId=0xDE00 SymbolicName=EMS_STORM_MANAGER_BASE_CODE Facility=ITF
Language=English
EMS Storm Manager
.
MessageId=+1 SymbolicName=EMS_STORM_MANAGER_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Storm Manager Service Started
.
MessageId=+1 SymbolicName=EMS_STORM_MANAGER_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Storm Manager Service Stopped
.
MessageId=+1 SymbolicName=EMS_STORM_MGR_EXCEPTION_UNHANDLED Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager encountered an unknown exception.
.
MessageId=+1 SymbolicName=EMS_STORM_MGR_SERVICE_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager encountered an unknown exception in its main processing method.
.
MessageId=+1 SymbolicName=EMS_STORM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager encountered error %1 in its main processing method.
.
MessageId=+1 SymbolicName=EMS_STORM_REGISTRY_NO_CONFIG_PATH Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager did not find a registry entry (at HKEY_LOCAL_MACHINE\SOFTWARE\EMS Technologies\%1\%2\%3) specifying the location of the configuration file.
.
MessageId=+1 SymbolicName=EMS_STORM_REGISTRY_CONFIG_FILE Severity=Success Facility=ITF
Language=English
EMS Storm Manager is initializing using configuration file %1.
.
MessageId=+1 SymbolicName=EMS_STORM_INIT_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager failure initializing from configuration.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_STORM_AUTOON_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager failed to activate Storm terminal on port %1.  It is configured to auto-activate.
.
MessageId=+1 SymbolicName=EMS_STORM_MANUALON_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager failed to activate Storm terminal on port %1.  The activation attempt was requested by an external client.
.
MessageId=+1 SymbolicName=EMS_STORM_MANUALOFF_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm Manager failed to deactivate Storm terminal on port %1.  The deactivation attempt was requested by an external client.
.
MessageId=+1 SymbolicName=EMS_STORM_ACTIVATION_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller on port %1 encountered an unrecognized exception while attempting to activate.
.
MessageId=+1 SymbolicName=EMS_STORM_STATUSCHECK_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller on port %1 encountered an unrecognized exception while attempting to check status.
.
MessageId=+1 SymbolicName=EMS_STORM_CMD_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller failed sending command <%1> on port %2.
.
MessageId=+1 SymbolicName=EMS_STORM_PORT_OPEN_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller failed opening port %1.
.
MessageId=+1 SymbolicName=EMS_STORM_ACTIVATION_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller failed to activate the Storm on port %1 within the configured activation timeout.
.
MessageId=+1 SymbolicName=EMS_STORM_CONFIG_DATAPORT_MISSING Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller could not retrieve the data port number from configuration.  Check the configuration file.
.
MessageId=+1 SymbolicName=EMS_STORM_CONFIG_EXPPORT_MISSING Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller could not retrieve the expansion port number from configuration.  Check the configuration file.
.
MessageId=+1 SymbolicName=EMS_STORM_ISACTIVE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller reports that Storm on port %1 is active.
.
MessageId=+1 SymbolicName=EMS_STORM_ISNOLONGERACTIVE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller reports that Storm on port %1 is no longer active.
.
MessageId=+1 SymbolicName=EMS_STORM_BCLTRANS_INIT_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller reports a failure attempting to initialize the BCL translator.
.
MessageId=+1 SymbolicName=EMS_STORM_CMD_BINARY_CONVERT_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller reports a failure attempting to convert a BCL message from text to binary.
.
MessageId=+1 SymbolicName=EMS_STORM_CHECK_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Storm controller reports an exception while attempting to check the status of the Storm(s).
.
;
;#endif // INC_STORMMANAGERMSGS



