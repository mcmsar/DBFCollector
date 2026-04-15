;/********************************************************************
;*	Module:			Alarmsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Leo Alarm Messages
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
;#ifndef INC_ALARMSGS
;#define INC_ALARMSGS
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;

MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
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

;
;//	****** NOTE ******* Warning and Alarms of the same type MUST
;//	****** NOTE ******* share the same error number.
;

MessageId=0xCC00 SymbolicName=EMS_ALARM_BASE_CODE Facility=ITF
Language=English
EMS Master Error
.
MessageId=+1 SymbolicName=EMS_ALARM_ANTENNA_NOT_MOVING Severity=Alarm Facility=ITF
Language=English
Alarm: Antenna has not moved in the last %1 seconds.
.
MessageId=+0 SymbolicName=EMS_WARN_ANTENNA_NOT_MOVING Severity=Warn Facility=ITF
Language=English
Warning: Antenna has not moved in the last %1 seconds.
.
MessageId=+1 SymbolicName=EMS_ALARM_ANTENNA_BEAM_ANGLE Severity=Alarm Facility=ITF
Language=English
Alarm: Antenna direction is outside of tolerance (%1 deg ).
.
MessageId=+0 SymbolicName=EMS_WARN_ANTENNA_BEAM_ANGLE Severity=Warn Facility=ITF
Language=English
Warning: Antenna direction is outside of tolerance (%1 deg ).
.
MessageId=+1 SymbolicName=EMS_ALARM_COMM_RETRY_LIMIT Severity=Alarm Facility=ITF
Language=English
Alarm: Communications Retry Count %1 has exceeded limit.
.
MessageId=+0 SymbolicName=EMS_WARN_COMM_RETRY_LIMIT Severity=Warn Facility=ITF
Language=English
Warning: Communications Retry Count %1 has exceeded limit.
.
MessageId=+1 SymbolicName=EMS_ALARM_COMM_CONTACT_LIMIT Severity=Alarm Facility=ITF
Language=English
Alarm: No comms messages have been received in %1 minutes.
.
MessageId=+0 SymbolicName=EMS_WARN_COMM_CONTACT_LIMIT Severity=Warn Facility=ITF
Language=English
Warning: No comms messages have been received in %1 minutes.
.
MessageId=+1 SymbolicName=EMS_ALARM_NO_CBC_121 Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
.
MessageId=+0 SymbolicName=EMS_WARN_NO_CBC_121 Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_NO_CBC_243 Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
.
MessageId=+0 SymbolicName=EMS_WARN_NO_CBC_243 Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_NO_CBC_406 Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
.
MessageId=+0 SymbolicName=EMS_WARN_NO_CBC_406 Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_NO_SARR_406 Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
.
MessageId=+0 SymbolicName=EMS_WARN_NO_SARR_406 Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_NO_SARP_406 Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
.
MessageId=+0 SymbolicName=EMS_WARN_NO_SARP_406 Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1) solutions.
.
MessageId=+0 SymbolicName=EMS_WARN_PASS_TOO_FEW_SOLNS Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1) solutions.
.
MessageId=+1 SymbolicName=EMS_ALARM_INSIDE_TEMP_RANGE Severity=Alarm Facility=ITF
Language=English
Alarm: Inside Temperature of %1 exceeds limits. 
.
MessageId=+0 SymbolicName=EMS_WARN_INSIDE_TEMP_RANGE Severity=Warn Facility=ITF
Language=English
Warning: Inside Temperature of %1 exceeds limits. 
.
MessageId=+1 SymbolicName=EMS_ALARM_OUTSIDE_TEMP_RANGE Severity=Alarm Facility=ITF
Language=English
Alarm: Outside Temperature of %1 exceeds limits. 
.
MessageId=+0 SymbolicName=EMS_WARN_OUTSIDE_TEMP_RANGE Severity=Warn Facility=ITF
Language=English
Warning: Outside Temperature of %1 exceeds limits. 
.
MessageId=+1 SymbolicName=EMS_ALARM_EQUIP_TEMP_RANGE Severity=Alarm Facility=ITF
Language=English
Alarm: Rack Temperature of %1 exceeds limits. 
.
MessageId=+0 SymbolicName=EMS_WARN_EQUIP_TEMP_RANGE Severity=Warn Facility=ITF
Language=English
Warning: Rack Temperature of %1 exceeds limits. 
.
MessageId=+1 SymbolicName=EMS_ALARM_COLLECTOR_MODINDEX Severity=Alarm Facility=ITF
Language=English
Alarm: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
.
MessageId=+0 SymbolicName=EMS_WARN_COLLECTOR_MODINDEX Severity=Warn Facility=ITF
Language=English
Warning: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
.
MessageId=+1 SymbolicName=EMS_ALARM_COLLECTOR_ADC_LEVEL Severity=Alarm Facility=ITF
Language=English
Alarm: Collector reporting low ADC level of %1
.
MessageId=+0 SymbolicName=EMS_WARN_COLLECTOR_ADC_LEVEL Severity=Warn Facility=ITF
Language=English
Warning: Collector reporting low ADC level of %1
.
MessageId=+1 SymbolicName=EMS_ALARM_ON_UPS_POWER Severity=Alarm Facility=ITF
Language=English
Alarm: The AC power has been lost. There are %1 minutes of UPS Power left.
.
MessageId=+1 SymbolicName=EMS_ALARM_UPS_FAILURE Severity=Alarm Facility=ITF
Language=English
Alarm: The UPS device appears to have failed. This error can often be cleared by recycling the power to the UPS.
.
MessageId=+1 SymbolicName=EMS_INFO_POWER_STATE Severity=Info Facility=ITF
Language=English
DV,AC Power,OK
.
MessageId=+0 SymbolicName=EMS_WARN_POWER_STATE Severity=Warn Facility=ITF
Language=English
DV,AC Power,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_POWER_STATE Severity=Alarm Facility=ITF
Language=English
DV,AC Power,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_ANTENNA_STATE Severity=Info Facility=ITF
Language=English
DV,Antenna,OK
.
MessageId=+0 SymbolicName=EMS_WARN_ANTENNA_STATE Severity=Warn Facility=ITF
Language=English
DV,Antenna,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_ANTENNA_STATE Severity=Alarm Facility=ITF
Language=English
DV,Antenna,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_COMMS_STATE Severity=Info Facility=ITF
Language=English
DV,Comms,OK
.
MessageId=+0 SymbolicName=EMS_WARN_COMMS_STATE Severity=Warn Facility=ITF
Language=English
DV,Comms,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_COMMS_STATE Severity=Alarm Facility=ITF
Language=English
DV,Comms,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_COLLECTOR_STATE Severity=Info Facility=ITF
Language=English
PR,Collector,OK
.
MessageId=+0 SymbolicName=EMS_WARN_COLLECTOR_STATE Severity=Warn Facility=ITF
Language=English
PR,Collector,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_COLLECTOR_STATE Severity=Alarm Facility=ITF
Language=English
PR,Collector,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_WIDEBAND_STATE Severity=Info Facility=ITF
Language=English
PR,Wideband,OK
.
MessageId=+0 SymbolicName=EMS_WARN_WIDEBAND_STATE Severity=Warn Facility=ITF
Language=English
PR,Wideband,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_WIDEBAND_STATE Severity=Alarm Facility=ITF
Language=English
PR,Wideband,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_ENVIRONMENT_STATE Severity=Info Facility=ITF
Language=English
NV,Environment,OK
.
MessageId=+0 SymbolicName=EMS_WARN_ENVIRONMENT_STATE Severity=Warn Facility=ITF
Language=English
NV,Environment,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_ENVIRONMENT_STATE Severity=Alarm Facility=ITF
Language=English
NV,Environment,FAIL
.
MessageId=+1 SymbolicName=EMS_INFO_PASS_STATE Severity=Info Facility=ITF
Language=English
PR,Pass,OK
.
MessageId=+0 SymbolicName=EMS_WARN_PASS_STATE Severity=Warn Facility=ITF
Language=English
PR,Pass,WARN
.
MessageId=+0 SymbolicName=EMS_ALARM_PASS_STATE Severity=Alarm Facility=ITF
Language=English
PR,Pass,FAIL
.
MessageId=+1 SymbolicName=EMS_ALARM_TRACER Severity=Info Facility=ITF
Language=English
StatusAlarm (%1).
.
MessageId=+1 SymbolicName=EMS_ALARM_ALARMRETCODE Severity=Info Facility=ITF
Language=English
GeoLeoAlarmInfo retcode=%1
.
MessageId=+1 SymbolicName=EMS_ALARM_STATUSCOLLECTOR Severity=Info Facility=ITF
Language=English
*Status: Collector elapsed = %1, freq=%2
.
MessageId=+1 SymbolicName=EMS_ALARM_SECABOVE5 Severity=Info Facility=ITF
Language=English
Seconds Above 5 = %1
.
MessageId=+1 SymbolicName=EMS_ALARM_TIMEDELTA Severity=Info Facility=ITF
Language=English
Time Delta = %1
.
MessageId=+1 SymbolicName=EMS_ALARM_ABOVE5DELTA Severity=Info Facility=ITF
Language=English
Above 5 TDelta = %1
.
MessageId=+1 SymbolicName=EMS_ALARM_PDSFRAMERATE Severity=Info Facility=ITF
Language=English
PDSFrameRate =%1
.
MessageId=+1 SymbolicName=EMS_ALARM_STARTPASS Severity=Info Facility=ITF
Language=English
StartPass Sat=%1
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC121 Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1 CBC 121Mhz) solutions.
.
MessageId=+0 SymbolicName=EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC121 Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1 CBC 121Mhz) solutions.
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC243 Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1 CBC 243Mhz) solutions.
.
MessageId=+0 SymbolicName=EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC243 Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1 CBC 243Mhz) solutions.
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC406 Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1 CBC 406Mhz) solutions.
.
MessageId=+0 SymbolicName=EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC406 Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1 CBC 406Mhz) solutions.
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS_SARP406 Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1 SARP 406Mhz) solutions.
.
MessageId=+0 SymbolicName=EMS_WARNING_PASS_TOO_FEW_SOLNS_SARP406 Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1 SARP 406Mhz) solutions.
.
MessageId=+1 SymbolicName=EMS_ALARM_PASS_TOO_FEW_SOLNS_SARR406 Severity=Alarm Facility=ITF
Language=English
Alarm: Expecting more than (%1 SARR 406Mhz) solutions.
.
MessageId=+0 SymbolicName=EMS_WARNING_PASS_TOO_FEW_SOLNS_SARR406 Severity=Warn Facility=ITF
Language=English
Warning: Expecting more than (%1 SARR 406Mhz) solutions.
.
MessageId=+1 SymbolicName=EMS_STATUS_MUTEX_INIT_ERROR Severity=Warn Facility=ITF
Language=English
Master Status: Failed to obtain handle onto shared mutex.
.
MessageId=+1 SymbolicName=EMS_ALARM_TOO_FEW_GEO_DETECTIONS Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
.
MessageId=+0 SymbolicName=EMS_WARNING_TOO_FEW_GEO_DETECTIONS Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
.
MessageId=+1 SymbolicName=EMS_ALARM_TOO_FEW_GEO_INTEGRATIONS Severity=Alarm Facility=ITF
Language=English
Alarm: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
.
MessageId=+0 SymbolicName=EMS_WARNING_TOO_FEW_GEO_INTEGRATIONS Severity=Warn Facility=ITF
Language=English
Warning: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
.
MessageId=+1 SymbolicName=EMS_INFO_COLLECTOR_MODINDEX Severity=Info Facility=ITF
Language=English
Info: Collector detected high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
.
MessageId=+1 SymbolicName=EMS_ALARM_ANTENNA_FAULT Severity=Alarm Facility=ITF
Language=English
Alarm: Antenna has reported a fault.
.
MessageId=+1 SymbolicName=EMS_ALARM_COMM_RETRY_LIMIT_RTE Severity=Alarm Facility=ITF
Language=English
Alarm: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
.
MessageId=+0 SymbolicName=EMS_WARN_COMM_RETRY_LIMIT_RTE Severity=Warn Facility=ITF
Language=English
Warning: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
.
;
;#endif // INC_ALARMSGS
