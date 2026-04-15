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

;#ifndef INC_FP_MSGS
;#define INC_FP_MSGS
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

MessageId=0xE600 SymbolicName=EMS_FP_BASE_CODE Facility=ITF
Language=English
EMS FP error.
.
MessageId=+1 SymbolicName=EMS_FP_NO_SCHEDULE_FOLDER Severity=ErrWarn Facility=ITF
Language=English
A directory from which to load FP schedules was not configured.
.
MessageId=+1 SymbolicName=EMS_FP_SET_SCHED_INVALID_PAIR_ID Severity=ErrWarn Facility=ITF
Language=English
An attempt was made to input a pass schedule with a pair identifier not configured on the FP.  The pair identifier used was %1.
.
MessageId=+1 SymbolicName=EMS_FP_NO_DS_PROXY_CLASSID Severity=ErrWarn Facility=ITF
Language=English
The proxy class for a datastream proxy could not be loaded because no class identifier was found in the configuration for pair identifier %1.
.
MessageId=+1 SymbolicName=EMS_FP_NO_ANTENNA_PROXY_CLASSID Severity=ErrWarn Facility=ITF
Language=English
The proxy class for a antenna controller proxy could not be loaded because no class identifier was found in the configuration for antenna identifier %1.
.
MessageId=+1 SymbolicName=EMS_FP_RESTART_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A restart command was received.
.
MessageId=+1 SymbolicName=EMS_FP_REBOOT_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A reboot command was received.
.
MessageId=+1 SymbolicName=EMS_FP_REBOOT_FORCE_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A forced reboot command was received.
.
MessageId=+1 SymbolicName=EMS_FP_START_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A start command was received.
.
MessageId=+1 SymbolicName=EMS_FP_STOP_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A stop command was received.
.
MessageId=+1 SymbolicName=EMS_FP_SETSCHEDULE_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A new pass schedule was received for antenna/datastream pair %1.
.
MessageId=+1 SymbolicName=EMS_FP_GETSCHEDULE_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A pass schedule retrieval command was received.
.
MessageId=+1 SymbolicName=EMS_FP_GETLIST_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
An antenna/datatstream pair listing retrieval command was received.
.
MessageId=+1 SymbolicName=EMS_FP_SETORBITS_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A set of orbit vectors was received.
.
MessageId=+1 SymbolicName=EMS_FP_GETORBITS_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A request for the current set of orbit vectors was received.
.
MessageId=+1 SymbolicName=EMS_FP_SETPROPERTY_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A new configuration setting for %1 was received.  The new value is %2.
.
MessageId=+1 SymbolicName=EMS_FP_GETPROPERTY_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A configuration setting request for %1 was received.
.
MessageId=+1 SymbolicName=EMS_FP_SETCONFIG_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
New configuration settings were received.
.
MessageId=+1 SymbolicName=EMS_FP_GETCONFIG_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
A request for the current configuration settings were received.
.
MessageId=+1 SymbolicName=EMS_FP_ANT_SET_ORBITS_FAILED Severity=ErrWarn Facility=ITF
Language=English
An error (%1) occurred while attempting to send orbit vectors to antenna %2.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_FOLDER_LOAD Severity=Success Facility=ITF
Language=English
Loading pass schedules from files found in directory %1.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_FILE_LOAD Severity=Success Facility=ITF
Language=English
Loading pass schedule from file %1.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_FOLDER_SAVE Severity=Success Facility=ITF
Language=English
Saving pass schedules to files in directory %1.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_FILE_SAVE Severity=Success Facility=ITF
Language=English
Saving pass schedule for antenna/datastream pair %1 to file %2.
.
MessageId=+1 SymbolicName=EMS_FP_NO_LONGER_SCHEDULED Severity=Success Facility=ITF
Language=English
The active pass for satellite %1 is no longer in the schedule.
.
MessageId=+1 SymbolicName=EMS_FP_NO_LONGER_IN_PASS Severity=Success Facility=ITF
Language=English
The active pass for satellite %1 is over.
.
MessageId=+1 SymbolicName=EMS_FP_STOP_COLLECTION Severity=Success Facility=ITF
Language=English
The command to stop data collection on A/D Board ID %1, channel %2 has been issued successfully.
.
MessageId=+1 SymbolicName=EMS_FP_STOP_TRACKING Severity=Success Facility=ITF
Language=English
The command to stop tracking with antenna %1 has been issued successfully.
.
MessageId=+1 SymbolicName=EMS_FP_EXCEPTION_MAIN_THREAD Severity=ErrWarn Facility=ITF
Language=English
An unrecognized exception has occurred in the Front End processor controller's main processing thread.
.
MessageId=+1 SymbolicName=EMS_FP_START_MAIN_THREAD Severity=Success Facility=ITF
Language=English
The Front End processor controller main processing thread has started.
.
MessageId=+1 SymbolicName=EMS_FP_STOP_MAIN_THREAD Severity=Success Facility=ITF
Language=English
The Front End processor controller main processing thread has ended.
.
MessageId=+1 SymbolicName=EMS_FP_CONTROLLER_SCHEDULE Severity=Success Facility=ITF
Language=English
The Front End processor controller has received a pass schedule.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_CHANGE Severity=Success Facility=ITF
Language=English
The currently active pass for pair ID %1 differs from current pass in schedule.  The active pass will be stopped.
.
MessageId=+1 SymbolicName=EMS_FP_SCHEDULE_NEW Severity=Success Facility=ITF
Language=English
A current pass has been found in the schedule for pair ID %1.  The pass will be started.
.
MessageId=+1 SymbolicName=EMS_FP_START_COLLECTION Severity=Success Facility=ITF
Language=English
The command to start data collection for satellite %1 on A/D Board ID %2, channel %3 has been issued successfully.
.
MessageId=+1 SymbolicName=EMS_FP_START_TRACKING Severity=Success Facility=ITF
Language=English
The command to start tracking satellite %1 with antenna %2 has been issued successfully.
.
MessageId=+1 SymbolicName=EMS_FP_TRACK_RECORD_AUDIT Severity=Success Facility=ITF
Language=English
A pass schedule entry for pair %1 (antenna=%2,datastream=%3) has SatID = %4, Start=%5, End=%6.
.
MessageId=+1 SymbolicName=EMS_FP_IDLE_COMMAND_RECEIVED Severity=Success Facility=ITF
Language=English
An idle command was received.
.
MessageId=+1 SymbolicName=EMS_FP_STOW_CMD_SENT Severity=Success Facility=ITF
Language=English
Successfully sent STOW command to Antenna ID %1.
.
MessageId=+1 SymbolicName=EMS_FP_STOW_CMD_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failure sending STOW command to Antenna ID %1.  Return code from antenna controller is %2.
.
;
;#endif // INC_FP_MSGS
