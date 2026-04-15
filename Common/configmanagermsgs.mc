;/********************************************************************
;*	Module:			configmanagermsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for config manager
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;* Copyright (c) 2003-2005 by EMS Technologies, Inc.,
;* All rights reserved
;* This program is unpublished software and contains the trade secrets
;* and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;
;/*******************************************************************
;
;  Revision Record
;
;	Rev	Date			Auth	Changes
;	===	====			====	=======
;
;	0.0	2003Oct03		FJP	start 
;
;********************************************************************/
;#ifndef INC_CONFIGMANAGERMSGS
;#define INC_CONFIGMANAGERMSGS
;
;#include "emserror.h"
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

MessageId=0xB700 SymbolicName=EMS_CM_BASE_CODE Facility=ITF
Language=English
EMS CM Error
.
MessageId=+1 SymbolicName=EMS_CM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS CM Service Started
.
MessageId=+1 SymbolicName=EMS_CM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS CM Service Stopped
.
MessageId=+1 SymbolicName=EMS_CM_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS CM Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_CM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  %1
.
MessageId=+1 SymbolicName=EMS_CM_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS CM exception has occurred:  %1
.
MessageId=+1 SymbolicName=EMS_CM_TRACE_MSG Severity=Success Facility=ITF
Language=English
EMS CM trace message:  %1
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_SYS_CFG_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Error reading CM system configuration file.
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_SCHEMA_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Error reading schema file (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_DATA_FILE Severity=Success Facility=ITF
Language=English
EMS CM could not read data file (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_GROUP_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid group type (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_GROUP_ID Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid group ID (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_KEY_NAME Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid key name (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid configuration data (key = %1).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_LEVEL Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid level (%1).
.
MessageId=+1 SymbolicName=EMS_CM_NO_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Unable to retrieve configuration data (key = %1).
.
MessageId=+1 SymbolicName=EMS_CM_PIPELINE_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error: Failed to instantiate pipeline (%1).
.
MessageId=+1 SymbolicName=EMS_CM_CMDSINK_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error: Failed to instantiate command sink.
.
MessageId=+1 SymbolicName=EMS_CM_CMDSINK_REG_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error: Failed to register command sink (%1).
.
MessageId=+1 SymbolicName=EMS_CM_INIT_UNK_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error: Service failed to start. Unhandled exception.
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_VALUE_ASSIGNMENT Severity=ErrWarn Facility=ITF
Language=English
Attempt to assign an invalid value to [%1] %2 (level=%3) data value: %4
.
MessageId=+1 SymbolicName=EMS_CM_NONEXISTANT_DATA_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS CM data file does not exist (%1).
.
MessageId=+1 SymbolicName=EMS_CM_JOURNALIZE_FAILED Severity=Success Facility=ITF
Language=English
Could not journalize entry [%1:%2] %3 (error: %4)
.
MessageId=+1 SymbolicName=EMS_CM_NOT_INITIALIZED Severity=Success Facility=ITF
Language=English
EMS CM Error: Could not process request. Configuration manager has not been initialized.
.
MessageId=+1 SymbolicName=EMS_CM_GETCONFIGGROUP_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM: Could not access specified configuration data group.
.
MessageId=+1 SymbolicName=EMS_CM_SETDATA_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CM: Configuration data items not saved.
.
MessageId=+1 SymbolicName=EMS_CM_INVALIDSYSTEMCFGFILE Severity=ErrWarn Facility=ITF
Language=English
EMS CM: Invalid system configuration file.
.
MessageId=+1 SymbolicName=EMS_CM_CMSYSCONFIGINITFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS CM: Could not load the system configuration file.
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_SYS_CFG_FILE_DETAILS Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Error reading CM system configuration file (%1) (%2).
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_DATA_ENCOUNTERED Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid data encountered during processing.
.
MessageId=+1 SymbolicName=EMS_CM_INVALID_INI_KEY Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Invalid key name "%1" found in "%2".
.
MessageId=+1 SymbolicName=EMS_CM_INI_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  An error occured while loading "%1".
.
MessageId=+1 SymbolicName=EMS_CM_JOURNALIZE_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS CM Error:  Exception while attempting to journalize initial configuration.
.
;
;#endif // INC_CONFIGMANAGERMSGS



