;/********************************************************************
;*	Module:			MemMgr.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Memory Manager Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;* Copyright (c) 2005 by EMS Technologies, Inc.,
;* All rights reserved
;* This program is unpublished software and contains the trade secrets
;* and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef _INC_MEMMGRMSG
;#define _INC_MEMMGRMSG
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

;// *** EMSCAT_MEMMGR = 0xCE00 ***
;
MessageId=0xCE00 SymbolicName=EMSCAT_MEMMGR_BASE_CODE Facility=ITF
Language=English
Memory Manager messages.
.
MessageID=+1 SymbolicName=EMS_MEMMGR_MUTEX_TIMEOUT Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2', MUTEX timeout
.
MessageID=+1 SymbolicName=EMS_MEMMGR_ALREADY_EXISTS Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2' already exists
.
MessageID=+1 SymbolicName=EMS_MEMMGR_TOO_MANY_NAMES Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2', too many names
.
MessageID=+1 SymbolicName=EMS_MEMMGR_TOO_MUCH_MEMORY Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2', too much memory
.
MessageID=+1 SymbolicName=EMS_MEMMGR_DEVIOCONTROL_ERR Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2', DeviceIoControl error %3
.
MessageID=+1 SymbolicName=EMS_MEMMGR_TRACE_ALLOC Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) %2 '%3', nDefs %4, nUsers %5, %6 KB, total user %7 KB
.
MessageID=+1 SymbolicName=EMS_MEMMGR_DOESNT_EXISTS Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) '%2' doesn't exists
.
MessageID=+1 SymbolicName=EMS_MEMMGR_TRACE Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) %2 '%3', nDefs %4
.
MessageID=+1 SymbolicName=EMS_MEMMGR_TRACE_TOTAL Severity=Success Facility=ITF
Language=English
EMS Memory Manager (%1) %2 '%3', nDefs %4, nUsers %5, total user %6 KB
.
MessageID=+1 SymbolicName=EMS_MEMMGR_CREATEFILE_ERR Severity=Success Facility=ITF
Language=English
EMS Memory Manager: DLL_PROCESS_ATTACH %1, CreateFile 'CMMDRV' error %2
.
MessageID=+1 SymbolicName=EMS_MEMMGR_ATTACH_MUTEX_ERR Severity=Success Facility=ITF
Language=English
EMS Memory Manager: Attach Mutex '%1' err(%2)
.
MessageID=+1 SymbolicName=EMS_MEMMGR_DLL_ATTACH Severity=Success Facility=ITF
Language=English
EMS Memory Manager: #@#DLL_PROCESS_ATTACH
.
MessageID=+1 SymbolicName=EMS_MEMMGR_DLL_CLOSEMEM Severity=Success Facility=ITF
Language=English
EMS Memory Manager: DLL_PROCESS_DETACH, CMM_CloseMem '%1'
.
MessageID=+1 SymbolicName=EMS_MEMMGR_DLL_DETACH Severity=Success Facility=ITF
Language=English
EMS Memory Manager: **DLL_PROCESS_DETACH
.
;
;#endif
