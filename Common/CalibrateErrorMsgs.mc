;/********************************************************************
;*	Module:			CalibrateErrorMsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Calibrate Errors
;*
;*					These errors were previously defined in a 
;*					stand-alone CalibrateError.h file
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


;#ifndef INC_CALIBRATEERROR
;#define INC_CALIBRATEERROR
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


;// *** EMSCAT_CALIBRATE ***
;
MessageId=0x9100 SymbolicName=EMSCAT_CALIBRATE_BASE_CODE Facility=ITF
Language=English
Calibrate error messages.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_MEMORYALLOC_ERROR Severity=ErrWarn Facility=ITF
Language=English
An out of memory error has been detected.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_FILE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Problem opening file.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_READ_ERROR Severity=ErrWarn Facility=ITF
Language=English
Problem reading file.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_NO_DATA Severity=ErrWarn Facility=ITF
Language=English
No locate data information has been initialized.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_IE_NON_CONVERGE Severity=ErrWarn Facility=ITF
Language=English
IE fails to converge.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_CN_NON_CONVERGE Severity=ErrWarn Facility=ITF
Language=English
Converge fails to converge.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_TCA_OUTOFBOUNDS Severity=ErrWarn Facility=ITF
Language=English
TCA out of bounds.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_SOLVE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Solve error.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_NO_POINTS Severity=ErrWarn Facility=ITF
Language=English
No points.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_WLS_NON_CONVERGE Severity=ErrWarn Facility=ITF
Language=English
WLS fails to converge.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_WRITING_ERROR Severity=ErrWarn Facility=ITF
Language=English
Problem writing file.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_INDEX_ERROR Severity=ErrWarn Facility=ITF
Language=English
Calibration index error.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_INPUT_DATA_ERROR Severity=ErrWarn Facility=ITF
Language=English
Calibration input data error.
.
MessageID=+1 SymbolicName=EMS_CALIBRATE_BEACON_ID_ERROR Severity=ErrWarn Facility=ITF
Language=English
Beacon id error.
.
;
;#endif
