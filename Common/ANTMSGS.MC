;/********************************************************************
;*	Module:			AntMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Antenna Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
;*					All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
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
;	0.0	01/05/21		rvw	start
;
;********************************************************************/
;#ifndef INC_ANTMSGS
;#define INC_ANTMSGS
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

MessageId=0xA600 SymbolicName=EMS_ANT_BASE_CODE Facility=ITF
Language=English
EMS Antenna Error
.
MessageId=+1 SymbolicName=EMS_ANT_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Antenna Service Started
.
MessageId=+1 SymbolicName=EMS_ANT_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_ANT_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Antenna Service Stopped
.
MessageId=+1 SymbolicName=EMS_ANT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports error %1.
.
MessageId=+1 SymbolicName=EMS_ANT_START_PASS Severity=Success Facility=ITF
Language=English
EMS Antenna starting to track pass 
.
MessageId=+1 SymbolicName=EMS_ANT_STOP_PASS Severity=Success Facility=ITF
Language=English
EMS Antenna stopped tracking pass. 
.
MessageId=+1 SymbolicName=EMS_ANT_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Antenna received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_ANT_INITIAL_HOME Severity=Success Facility=ITF
Language=English
EMS Antenna successfully initialized.
.
MessageId=+1 SymbolicName=EMS_ANT_FAILED_HOME Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna timed out during initialization.
.
MessageId=+1 SymbolicName=EMS_ANT_STATUS Severity=Success Facility=ITF
Language=English
EMS Antenna Homing Successful. Offset: ( %1 ).
.
MessageId=+1 SymbolicName=EMS_ANT_SKIP_HOME Severity=Success Facility=ITF
Language=English
EMS Antenna skipped homing sequence.
.
MessageId=+1 SymbolicName=EMS_ANT_DEVICE_PERMISSION Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports error accessing antenna device. (see DCOMCnfg - may have insufficient permission ).
.
MessageId=+1 SymbolicName=EMS_ANT_HOMING_FAULT_RETRY Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports homing fault ( Retrying attempt %1 ).
.
MessageId=+1 SymbolicName=EMS_ANT_HOMING_FAULT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports homing fault ( Homing Terminated ).
.
MessageId=+1 SymbolicName=EMS_ANT_HOMING_TIMEOUT_RETRY Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports homing timeout ( Retrying attempt %1 ).
.
MessageId=+1 SymbolicName=EMS_ANT_HOMING_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports homing timeout ( Homing Terminated ).
.
MessageId=+1 SymbolicName=EMS_ANT_PASS_RETRY Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports pass failure ( Retrying attempt %1 ).
.
MessageId=+1 SymbolicName=EMS_ANT_PASS_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports pass failure ( Tracking terminated ).
.
MessageId=+1 SymbolicName=EMS_ANT_RESET_WAIT_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports timeout waiting for Antenna subsystem to shutdown.
.
MessageId=+1 SymbolicName=EMS_ANT_RESET_WAIT_ABANDONED Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports wait abandoned for Antenna subsystem to shutdown.
.
MessageId=+1 SymbolicName=EMS_ANT_DEVICE_INIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports an error during ACU initialization (hr = %1). This may indicate a power outage to the ACU or an ACU hardware fault.  Hardware faults can often be cleared by recycling the ACU power.
.
MessageId=+1 SymbolicName=EMS_ANT_INIT_HOME Severity=Success Facility=ITF
Language=English
EMS Antenna reports initial homing was successful.
.
MessageId=+1 SymbolicName=EMS_ANT_HARDWARE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports a hardware problem. This may indicate a power outage to the ACU or an ACU hardware fault. Hardware faults can often be cleared by recycling the ACU power.
.
MessageId=+1 SymbolicName=EMS_ANT_HARDWARE_ERROR_CLEARED Severity=Success Facility=ITF
Language=English
EMS Antenna reports the ACU hardware error condition has been cleared.
.
MessageId=+1 SymbolicName=EMS_ANT_INIT_ERROR_SKIP_PASS Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports it is skipping a pass (satellite %1) due to problem in ACU initialization.
.
;
;// *** EMSCAT_ANT = 0x87 ***
;
MessageId=0x8700 SymbolicName=EMSCAT_ANT_BASE_CODE Facility=ITF
Language=English
Antenna error messages.
.
MessageID=+1 SymbolicName=ANT_INV_CTR_REQUEST Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna reports invalid control request received.
.
MessageID=+1 SymbolicName=ANT_INV_DEST_NAME Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: given logical destination is invalid.
.
MessageID=+1 SymbolicName=ANT_INV_BEAMWIDTH Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Specified azimuth and elevation are not within the beamwidth.
.
MessageID=+1 SymbolicName=ANT_NOT_REACHED_AOS Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Could not move to AOS.
.
MessageID=+1 SymbolicName=ANT_CW_LIMIT_HIT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: At Clockwise limit zone.
.
MessageID=+1 SymbolicName=ANT_CCW_LIMIT_HIT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: At Counter Clockwise limit zone
.
MessageID=+1 SymbolicName=ANT_HIGH_LIMIT_HIT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: At High elevation limit zone
.
MessageID=+1 SymbolicName=ANT_LOW_LIMIT_HIT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: At Low elevation limit zone
.
MessageID=+1 SymbolicName=ANT_INV_REGISTRY Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Can't open registry
.
MessageID=+1 SymbolicName=ANT_ILLEGAL_LINE_NUMBER Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Illegal line number.
.
MessageID=+1 SymbolicName=ANT_NON_REQUEST_TO_CANCEL Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Invalid cancel request.
.
MessageID=+1 SymbolicName=ANT_INV_AZIMUTH_COMM Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to set azimuth.
.
MessageID=+1 SymbolicName=ANT_INV_ELEVATION_COMM Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to set elevation.
.
MessageID=+1 SymbolicName=ANT_CANT_STOP_ANTENNA Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Cannot stop antenna.
.
MessageID=+1 SymbolicName=ANT_HOME_FAULT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Error processing home command.
.
MessageID=+1 SymbolicName=EMS_TOO_LATE_FOR_TRACK Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Too late for track.
.
MessageID=+1 SymbolicName=EMS_ANT_WORKERBUFFERLOCKERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Error locking buffer in transfer track data in WorkerThread
.
MessageID=+1 SymbolicName=EMS_ANT_MEMORYRAWTRACK Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Error Allocating memory for l_AdjRawTrack in WorkerThread
.
MessageID=+1 SymbolicName=EMS_ANT_TOOMANYSMOOTHINGITER Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Too many smoothing iterations in WorkerThread. Smoothing aborted.
.
MessageID=+1 SymbolicName=EMS_ANT_TIMESINCEAXISPOSNTOOLONG Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Track execution aborted. Time since last axis position report is too long.
.
MessageID=+1 SymbolicName=EMS_ANT_TRACKSPEEDMEMORYERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Could not allocate memory for proposed track speeds.
.
MessageID=+1 SymbolicName=EMS_ANT_TRACKMEMORYERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Could not allocate memory for proposed track.
.
MessageID=+1 SymbolicName=EMS_ANT_AZIMUTHRECONCILEERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Cannot reconcile azimuth values to track within the antenna parameters.
.
MessageID=+1 SymbolicName=EMS_ANT_RAWTRACKMEMORYERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Cannot Allocate Memory for l_AdjRawRawTrack
.
MessageID=+1 SymbolicName=EMS_ANT_MEMORYERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Cannot Allocate Memory
.
MessageID=+1 SymbolicName=EMS_ANT_COORDMEMORYERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Cannot Allocate Memory for coordinates
.
MessageID=+1 SymbolicName=EMS_ANT_HARDWAREERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Hardware error.
.
MessageID=+1 SymbolicName=EMS_ANT_OUTOFBEAMERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Out of beam error.
.
MessageID=+1 SymbolicName=EMS_ANT_UNKNOWNERR Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Unknown error.
.
MessageID=+1 SymbolicName=EMS_ANT_AGC_SWITCH_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to initialize AGC switch (hr=%1).
.
MessageID=+1 SymbolicName=EMS_ANT_POLR_SWITCH_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to initialize polarization switch (hr=%1).
.
MessageID=+1 SymbolicName=EMS_ANT_FREQ1_SWITCH_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to initialize the first frequency switch (hr=%1).
.
MessageID=+1 SymbolicName=EMS_ANT_FREQ2_SWITCH_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Failed to initialize the second frequency switch (hr=%1).
.
MessageID=+1 SymbolicName=EMS_ANT_HW_ERR_REINIT Severity=ErrWarn Facility=ITF
Language=English
EMS Antenna: Detected a hardware problem and trying to reinitialize the ACU. (This could be a power outages, ACU hardware error or network problem).
.
;
;#endif // INC_ANTMSGS

