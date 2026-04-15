;/***************************************************************************
;*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of Honeywell International, Inc.
;*
;****************************************************************************/

;#ifndef INC_TRACKING_SCHEDULER_MSGS
;#define INC_TRACKING_SCHEDULER_MSGS
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

MessageId=0xF600 SymbolicName=EMS_TS_BASE_CODE Facility=ITF
Language=English
EMS Tracking Scheduler error.
.
MessageId=+1 SymbolicName=EMS_TS_STARTED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has started.
.
MessageId=+1 SymbolicName=EMS_TS_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler failed to start with error code %1.
.
MessageId=+1 SymbolicName=EMS_TS_STOPPED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has stopped.
.
MessageId=+1 SymbolicName=EMS_TS_CONFIG_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler failed to get a configuration from configWS.
.
MessageId=+1 SymbolicName=EMS_TS_NO_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler retrieved an empty configuration change notification from configWS.
.
MessageId=+1 SymbolicName=EMS_TS_RECS_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has received satellite track records.
.
MessageId=+1 SymbolicName=EMS_TS_RECS_SENT Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has sent %1 satellite track records to FP with URL %2.
.
MessageId=+1 SymbolicName=EMS_TS_GET_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler encountered error (%1) while attempting to retrieve the current schedule from FP (%2).
.
MessageId=+1 SymbolicName=EMS_TS_NO_FP_CONFIG Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler did not find a reference to an FP configuration file in the Tracking scheduler configuration.  As a result, the Tracking Scheduler will not manage any FPs.
.
MessageId=+1 SymbolicName=EMS_FP_GETLIST_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler encountered error (%1) on call to FP (URL=%2) for its list of managed antennas.
.
MessageId=+1 SymbolicName=EMS_FP_SETSCHEDULE_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler encountered error (%1) on call to FP (URL=%2) to set a schedule for antenna (%3).
.
MessageId=+1 SymbolicName=EMS_FP_SETSCHEDULE_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler successfully sent a Tracking schedule to FP (URL=%1) with (%2) passes for antenna (%3).
.
MessageId=+1 SymbolicName=EMS_FP_GETSCHEDULE_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler successfully received (%1) pass schedule records from FP (URL=%2) managing (%3) antennas.
.
MessageId=+1 SymbolicName=EMS_TS_SCHEDINIT_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has initialized a scheduler with lutid = %1, runningmode=%2, startup=%3, trackandscan=%4, duration=%5 hours, checkperiod=%6 minutes, pre-pass=%7 seconds, post-pass=%8 seconds.
.
MessageId=+1 SymbolicName=EMS_TS_SCHEDINIT2_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has initialized a scheduler with max_leo_duration=%1 minutes, max_geo_duration=%2 minutes, max_meo_duration=%3 minutes for satellites=(%4).
.
MessageId=+1 SymbolicName=EMS_TS_EXTERNAL_INSTALL_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has installed a schedule that was received from an external source.
.
MessageId=+1 SymbolicName=EMS_TS_UPDATE_FROM_FPS_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has initialized its managed schedule from FP(s) under its control.
.
MessageId=+1 SymbolicName=EMS_TS_GENERATE_INSTALL_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has generated a new schedule and installed it on the FP(s) under its control.
.
MessageId=+1 SymbolicName=EMS_TS_INIT_OUTPUT_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler will output schedule listings to file:  (%1).
.
MessageId=+1 SymbolicName=EMS_TS_MAX_RECS_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler has reached the maximum capacity (%1 satellite pass records) while generating a schedule.
.
MessageId=+1 SymbolicName=EMS_FP_MAX_RECS_WARN Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler has retrieved an FP's pass schedule where the number of entries matches the maximum (%1) that the scheduler can handle.  The FP may actually have a schedule with more records than the scheduler can manage.
.
MessageId=+1 SymbolicName=EMS_TS_LOCAL_COMMAND_EXECUTED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has processed a command to enter into local scheduling mode.
.
MessageId=+1 SymbolicName=EMS_TS_NOMINAL_COMMAND_EXECUTED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has processed a command to enter into nominal scheduling mode.
.
MessageId=+1 SymbolicName=EMS_TS_BACKUP_COMMAND_EXECUTED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has processed a command to enter into backup scheduling mode.
.
MessageId=+1 SymbolicName=EMS_TS_COMMAND_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler failed to process a command.
.
MessageId=+1 SymbolicName=EMS_TS_COMMAND_FAILED2 Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler failed to process a command with error code %1.
.
MessageId=+1 SymbolicName=EMS_TS_LOCAL_MODE_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has received a configuration to run in local mode.
.
MessageId=+1 SymbolicName=EMS_TS_NOMINAL_MODE_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has received a configuration to run in nominal mode.
.
MessageId=+1 SymbolicName=EMS_TS_BACKUP_MODE_RECEIVED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has received a configuration to run in backup mode.
.
MessageId=+1 SymbolicName=EMS_TS_UNSOPPORTED_CONF_CHANGE_RECEIVED Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler received an unsupported mode: %1.
.
MessageId=+1 SymbolicName=EMS_TS_RECEIVED_EMPTY_CONF_CHANGE Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler received an empty configuration change notification.
.
MessageId=+1 SymbolicName=EMS_TS_PARSING_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Tracking Scheduler failed to parse configuration change notification: %1.
.
MessageId=+1 SymbolicName=EMS_TS_PROCESSING_NEW_MODE Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler is processing the received mode: %1 (1=Nominal 2=Backup 3=Local).
.
MessageId=+1 SymbolicName=EMS_TS_LOG_EXCEPTION Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler reports that an exception report was received from: %1.
.
MessageId=+1 SymbolicName=EMS_TS_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Tracking Scheduler was unable to parse %1. This is most likely due to a format error in %2. Error:  %3.
.
MessageId=+1 SymbolicName=EMS_TS_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Tracking Scheduler was unable to parse %1. This may be due to a format error in %2 or an error in the schema definition. Error:  %3.
.
MessageId=+1 SymbolicName=EMS_TS_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Tracking Scheduler was unable to parse %1. Error details:  %2.
.
MessageId=+1 SymbolicName=EMS_TS_SENT_TP_TOAMQ Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler sent Tracking Plan to ActiveMQ topic: %1.
.
MessageId=+1 SymbolicName=EMS_TS_CONSUMER_NOT_CONNECTED Severity=Success Facility=ITF
Language=English
Tracking Scheduler Service reports that it could not connect to the Message Queue for receipt of %1 messages. Processing will continue, but messages will not be received.
.
MessageId=+1 SymbolicName=EMS_TS_RECEIVED_INACTIVE_TP Severity=Success Facility=ITF
Language=English
Tracking Scheduler - %1 Tracking Plan that has Active field set to %2.
.
MessageId=+1 SymbolicName=EMS_TS_INSTALL_LOCAL_SUCCEED Severity=Success Facility=ITF
Language=English
EMS Tracking Scheduler has loaded local schedule and installed it on the FP(s) under its control.
.
;
;#endif 

