;/*********************************************************************
;*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

;#ifndef INC_PASS_SCHEDULER_MSGS
;#define INC_PASS_SCHEDULER_MSGS
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

MessageId=0xE800 SymbolicName=EMS_PS_BASE_CODE Facility=ITF
Language=English
EMS Pass Scheduler error.
.
MessageId=+1 SymbolicName=EMS_PS_STARTED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has started.
.
MessageId=+1 SymbolicName=EMS_PS_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler failed to start with error code %1.
.
MessageId=+1 SymbolicName=EMS_PS_STOPPED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has stopped.
.
MessageId=+1 SymbolicName=EMS_PS_NO_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler failed to find a configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
.
MessageId=+1 SymbolicName=EMS_PS_RECS_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has received satellite track records.
.
MessageId=+1 SymbolicName=EMS_PS_RECS_SENT Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has sent %1 satellite track records to FP with URL %2.
.
MessageId=+1 SymbolicName=EMS_PS_GET_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler encountered error (%1) while attempting to retrieve the current schedule from FP (%2).
.
MessageId=+1 SymbolicName=EMS_PS_NO_FP_CONFIG Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler did not find a reference to an FP configuration file in the pass scheduler configuration.  As a result, the Pass Scheduler will not manage any FPs.
.
MessageId=+1 SymbolicName=EMS_FP_GETLIST_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler encountered error (%1) on call to FP (URL=%2) for its list of managed antennas.
.
MessageId=+1 SymbolicName=EMS_FP_SETSCHEDULE_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler encountered error (%1) on call to FP (URL=%2) to set a schedule for antenna (%3).
.
MessageId=+1 SymbolicName=EMS_FP_SETSCHEDULE_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler successfully sent a pass schedule to FP (URL=%1) with (%2) passes for antenna (%3).
.
MessageId=+1 SymbolicName=EMS_FP_GETSCHEDULE_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler successfully received (%1) pass schedule records from FP (URL=%2) managing (%3) antennas.
.
MessageId=+1 SymbolicName=EMS_PS_SCHEDINIT_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has initialized a scheduler with lutid = %1, autogenerate=%2, startup=%3, trackandscan=%4, duration=%5 hours, checkperiod=%6 minutes, pre-pass=%7 seconds, post-pass=%8 seconds.
.
MessageId=+1 SymbolicName=EMS_PS_SCHEDINIT2_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has initialized a scheduler with max_leo_duration=%1 minutes, max_geo_duration=%2 minutes, max_meo_duration=%3 minutes for satellites=(%4).
.
MessageId=+1 SymbolicName=EMS_PS_EXTERNAL_INSTALL_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has installed a schedule that was received from an external source.
.
MessageId=+1 SymbolicName=EMS_PS_UPDATE_FROM_FPS_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has initialized its managed schedule from FP(s) under its control.
.
MessageId=+1 SymbolicName=EMS_PS_GENERATE_INSTALL_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has generated a new schedule and installed it on the FP(s) under its control.
.
MessageId=+1 SymbolicName=EMS_PS_INIT_OUTPUT_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler will output schedule listings to file:  (%1).
.
MessageId=+1 SymbolicName=EMS_PS_MAX_RECS_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler has reached the maximum capacity (%1 satellite pass records) while generating a schedule.
.
MessageId=+1 SymbolicName=EMS_FP_MAX_RECS_WARN Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler has retrieved an FP's pass schedule where the number of entries matches the maximum (%1) that the scheduler can handle.  The FP may actually have a schedule with more records than the scheduler can manage.
.
MessageId=+1 SymbolicName=EMS_PS_AUTOMATIC_COMMAND_EXECUTED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has processed a command to enter into automatic scheduling mode.
.
MessageId=+1 SymbolicName=EMS_PS_MANUAL_COMMAND_EXECUTED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has processed a command to enter into manual scheduling mode.
.
MessageId=+1 SymbolicName=EMS_PS_COMMAND_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler failed to process a command.
.
MessageId=+1 SymbolicName=EMS_PS_COMMAND_FAILED2 Severity=ErrWarn Facility=ITF
Language=English
EMS Pass Scheduler failed to process a command with error code %1.
.
MessageId=+1 SymbolicName=EMS_PS_AUTOMATIC_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has received a command to enter into automatic scheduling mode.
.
MessageId=+1 SymbolicName=EMS_PS_MANUAL_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has received a command to enter into manual scheduling mode.
.
MessageId=+1 SymbolicName=EMS_PS_SETDURATION_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has received a command to set the pass schedule duration to %1 days.
.
MessageId=+1 SymbolicName=EMS_PS_SETMINELEVATION_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Pass Scheduler has received a command to set the minimum elevation angle for scheduled passes to %1 degrees.
.
;
;#endif 

