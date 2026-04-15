/********************************************************************
*	Module:			Alarmsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Leo Alarm Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_ALARMSGS
#define INC_ALARMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif


//	****** NOTE ******* Warning and Alarms of the same type MUST
//	****** NOTE ******* share the same error number.

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: EMS_ALARM_BASE_CODE
//
// MessageText:
//
//  EMS Master Error
//
#define EMS_ALARM_BASE_CODE              ((EMS_RESULT)0x0004CC00L)

//
// MessageId: EMS_ALARM_ANTENNA_NOT_MOVING
//
// MessageText:
//
//  Alarm: Antenna has not moved in the last %1 seconds.
//
#define EMS_ALARM_ANTENNA_NOT_MOVING     ((EMS_RESULT)0xC004CC01L)

//
// MessageId: EMS_WARN_ANTENNA_NOT_MOVING
//
// MessageText:
//
//  Warning: Antenna has not moved in the last %1 seconds.
//
#define EMS_WARN_ANTENNA_NOT_MOVING      ((EMS_RESULT)0x8004CC01L)

//
// MessageId: EMS_ALARM_ANTENNA_BEAM_ANGLE
//
// MessageText:
//
//  Alarm: Antenna direction is outside of tolerance (%1 deg ).
//
#define EMS_ALARM_ANTENNA_BEAM_ANGLE     ((EMS_RESULT)0xC004CC02L)

//
// MessageId: EMS_WARN_ANTENNA_BEAM_ANGLE
//
// MessageText:
//
//  Warning: Antenna direction is outside of tolerance (%1 deg ).
//
#define EMS_WARN_ANTENNA_BEAM_ANGLE      ((EMS_RESULT)0x8004CC02L)

//
// MessageId: EMS_ALARM_COMM_RETRY_LIMIT
//
// MessageText:
//
//  Alarm: Communications Retry Count %1 has exceeded limit.
//
#define EMS_ALARM_COMM_RETRY_LIMIT       ((EMS_RESULT)0xC004CC03L)

//
// MessageId: EMS_WARN_COMM_RETRY_LIMIT
//
// MessageText:
//
//  Warning: Communications Retry Count %1 has exceeded limit.
//
#define EMS_WARN_COMM_RETRY_LIMIT        ((EMS_RESULT)0x8004CC03L)

//
// MessageId: EMS_ALARM_COMM_CONTACT_LIMIT
//
// MessageText:
//
//  Alarm: No comms messages have been received in %1 minutes.
//
#define EMS_ALARM_COMM_CONTACT_LIMIT     ((EMS_RESULT)0xC004CC04L)

//
// MessageId: EMS_WARN_COMM_CONTACT_LIMIT
//
// MessageText:
//
//  Warning: No comms messages have been received in %1 minutes.
//
#define EMS_WARN_COMM_CONTACT_LIMIT      ((EMS_RESULT)0x8004CC04L)

//
// MessageId: EMS_ALARM_NO_CBC_121
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_121             ((EMS_RESULT)0xC004CC05L)

//
// MessageId: EMS_WARN_NO_CBC_121
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_121              ((EMS_RESULT)0x8004CC05L)

//
// MessageId: EMS_ALARM_NO_CBC_243
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_243             ((EMS_RESULT)0xC004CC06L)

//
// MessageId: EMS_WARN_NO_CBC_243
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_243              ((EMS_RESULT)0x8004CC06L)

//
// MessageId: EMS_ALARM_NO_CBC_406
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_406             ((EMS_RESULT)0xC004CC07L)

//
// MessageId: EMS_WARN_NO_CBC_406
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_406              ((EMS_RESULT)0x8004CC07L)

//
// MessageId: EMS_ALARM_NO_SARR_406
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
//
#define EMS_ALARM_NO_SARR_406            ((EMS_RESULT)0xC004CC08L)

//
// MessageId: EMS_WARN_NO_SARR_406
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
//
#define EMS_WARN_NO_SARR_406             ((EMS_RESULT)0x8004CC08L)

//
// MessageId: EMS_ALARM_NO_SARP_406
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
//
#define EMS_ALARM_NO_SARP_406            ((EMS_RESULT)0xC004CC09L)

//
// MessageId: EMS_WARN_NO_SARP_406
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
//
#define EMS_WARN_NO_SARP_406             ((EMS_RESULT)0x8004CC09L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS
//
// MessageText:
//
//  Alarm: Expecting more than (%1) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS     ((EMS_RESULT)0xC004CC0AL)

//
// MessageId: EMS_WARN_PASS_TOO_FEW_SOLNS
//
// MessageText:
//
//  Warning: Expecting more than (%1) solutions.
//
#define EMS_WARN_PASS_TOO_FEW_SOLNS      ((EMS_RESULT)0x8004CC0AL)

//
// MessageId: EMS_ALARM_INSIDE_TEMP_RANGE
//
// MessageText:
//
//  Alarm: Inside Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_INSIDE_TEMP_RANGE      ((EMS_RESULT)0xC004CC0BL)

//
// MessageId: EMS_WARN_INSIDE_TEMP_RANGE
//
// MessageText:
//
//  Warning: Inside Temperature of %1 exceeds limits. 
//
#define EMS_WARN_INSIDE_TEMP_RANGE       ((EMS_RESULT)0x8004CC0BL)

//
// MessageId: EMS_ALARM_OUTSIDE_TEMP_RANGE
//
// MessageText:
//
//  Alarm: Outside Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_OUTSIDE_TEMP_RANGE     ((EMS_RESULT)0xC004CC0CL)

//
// MessageId: EMS_WARN_OUTSIDE_TEMP_RANGE
//
// MessageText:
//
//  Warning: Outside Temperature of %1 exceeds limits. 
//
#define EMS_WARN_OUTSIDE_TEMP_RANGE      ((EMS_RESULT)0x8004CC0CL)

//
// MessageId: EMS_ALARM_EQUIP_TEMP_RANGE
//
// MessageText:
//
//  Alarm: Rack Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_EQUIP_TEMP_RANGE       ((EMS_RESULT)0xC004CC0DL)

//
// MessageId: EMS_WARN_EQUIP_TEMP_RANGE
//
// MessageText:
//
//  Warning: Rack Temperature of %1 exceeds limits. 
//
#define EMS_WARN_EQUIP_TEMP_RANGE        ((EMS_RESULT)0x8004CC0DL)

//
// MessageId: EMS_ALARM_COLLECTOR_MODINDEX
//
// MessageText:
//
//  Alarm: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_ALARM_COLLECTOR_MODINDEX     ((EMS_RESULT)0xC004CC0EL)

//
// MessageId: EMS_WARN_COLLECTOR_MODINDEX
//
// MessageText:
//
//  Warning: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_WARN_COLLECTOR_MODINDEX      ((EMS_RESULT)0x8004CC0EL)

//
// MessageId: EMS_ALARM_COLLECTOR_ADC_LEVEL
//
// MessageText:
//
//  Alarm: Collector reporting low ADC level of %1
//
#define EMS_ALARM_COLLECTOR_ADC_LEVEL    ((EMS_RESULT)0xC004CC0FL)

//
// MessageId: EMS_WARN_COLLECTOR_ADC_LEVEL
//
// MessageText:
//
//  Warning: Collector reporting low ADC level of %1
//
#define EMS_WARN_COLLECTOR_ADC_LEVEL     ((EMS_RESULT)0x8004CC0FL)

//
// MessageId: EMS_ALARM_ON_UPS_POWER
//
// MessageText:
//
//  Alarm: The AC power has been lost. There are %1 minutes of UPS Power left.
//
#define EMS_ALARM_ON_UPS_POWER           ((EMS_RESULT)0xC004CC10L)

//
// MessageId: EMS_ALARM_UPS_FAILURE
//
// MessageText:
//
//  Alarm: The UPS device appears to have failed. This error can often be cleared by recycling the power to the UPS.
//
#define EMS_ALARM_UPS_FAILURE            ((EMS_RESULT)0xC004CC11L)

//
// MessageId: EMS_INFO_POWER_STATE
//
// MessageText:
//
//  DV,AC Power,OK
//
#define EMS_INFO_POWER_STATE             ((EMS_RESULT)0x4004CC12L)

//
// MessageId: EMS_WARN_POWER_STATE
//
// MessageText:
//
//  DV,AC Power,WARN
//
#define EMS_WARN_POWER_STATE             ((EMS_RESULT)0x8004CC12L)

//
// MessageId: EMS_ALARM_POWER_STATE
//
// MessageText:
//
//  DV,AC Power,FAIL
//
#define EMS_ALARM_POWER_STATE            ((EMS_RESULT)0xC004CC12L)

//
// MessageId: EMS_INFO_ANTENNA_STATE
//
// MessageText:
//
//  DV,Antenna,OK
//
#define EMS_INFO_ANTENNA_STATE           ((EMS_RESULT)0x4004CC13L)

//
// MessageId: EMS_WARN_ANTENNA_STATE
//
// MessageText:
//
//  DV,Antenna,WARN
//
#define EMS_WARN_ANTENNA_STATE           ((EMS_RESULT)0x8004CC13L)

//
// MessageId: EMS_ALARM_ANTENNA_STATE
//
// MessageText:
//
//  DV,Antenna,FAIL
//
#define EMS_ALARM_ANTENNA_STATE          ((EMS_RESULT)0xC004CC13L)

//
// MessageId: EMS_INFO_COMMS_STATE
//
// MessageText:
//
//  DV,Comms,OK
//
#define EMS_INFO_COMMS_STATE             ((EMS_RESULT)0x4004CC14L)

//
// MessageId: EMS_WARN_COMMS_STATE
//
// MessageText:
//
//  DV,Comms,WARN
//
#define EMS_WARN_COMMS_STATE             ((EMS_RESULT)0x8004CC14L)

//
// MessageId: EMS_ALARM_COMMS_STATE
//
// MessageText:
//
//  DV,Comms,FAIL
//
#define EMS_ALARM_COMMS_STATE            ((EMS_RESULT)0xC004CC14L)

//
// MessageId: EMS_INFO_COLLECTOR_STATE
//
// MessageText:
//
//  PR,Collector,OK
//
#define EMS_INFO_COLLECTOR_STATE         ((EMS_RESULT)0x4004CC15L)

//
// MessageId: EMS_WARN_COLLECTOR_STATE
//
// MessageText:
//
//  PR,Collector,WARN
//
#define EMS_WARN_COLLECTOR_STATE         ((EMS_RESULT)0x8004CC15L)

//
// MessageId: EMS_ALARM_COLLECTOR_STATE
//
// MessageText:
//
//  PR,Collector,FAIL
//
#define EMS_ALARM_COLLECTOR_STATE        ((EMS_RESULT)0xC004CC15L)

//
// MessageId: EMS_INFO_WIDEBAND_STATE
//
// MessageText:
//
//  PR,Wideband,OK
//
#define EMS_INFO_WIDEBAND_STATE          ((EMS_RESULT)0x4004CC16L)

//
// MessageId: EMS_WARN_WIDEBAND_STATE
//
// MessageText:
//
//  PR,Wideband,WARN
//
#define EMS_WARN_WIDEBAND_STATE          ((EMS_RESULT)0x8004CC16L)

//
// MessageId: EMS_ALARM_WIDEBAND_STATE
//
// MessageText:
//
//  PR,Wideband,FAIL
//
#define EMS_ALARM_WIDEBAND_STATE         ((EMS_RESULT)0xC004CC16L)

//
// MessageId: EMS_INFO_ENVIRONMENT_STATE
//
// MessageText:
//
//  NV,Environment,OK
//
#define EMS_INFO_ENVIRONMENT_STATE       ((EMS_RESULT)0x4004CC17L)

//
// MessageId: EMS_WARN_ENVIRONMENT_STATE
//
// MessageText:
//
//  NV,Environment,WARN
//
#define EMS_WARN_ENVIRONMENT_STATE       ((EMS_RESULT)0x8004CC17L)

//
// MessageId: EMS_ALARM_ENVIRONMENT_STATE
//
// MessageText:
//
//  NV,Environment,FAIL
//
#define EMS_ALARM_ENVIRONMENT_STATE      ((EMS_RESULT)0xC004CC17L)

//
// MessageId: EMS_INFO_PASS_STATE
//
// MessageText:
//
//  PR,Pass,OK
//
#define EMS_INFO_PASS_STATE              ((EMS_RESULT)0x4004CC18L)

//
// MessageId: EMS_WARN_PASS_STATE
//
// MessageText:
//
//  PR,Pass,WARN
//
#define EMS_WARN_PASS_STATE              ((EMS_RESULT)0x8004CC18L)

//
// MessageId: EMS_ALARM_PASS_STATE
//
// MessageText:
//
//  PR,Pass,FAIL
//
#define EMS_ALARM_PASS_STATE             ((EMS_RESULT)0xC004CC18L)

//
// MessageId: EMS_ALARM_TRACER
//
// MessageText:
//
//  StatusAlarm (%1).
//
#define EMS_ALARM_TRACER                 ((EMS_RESULT)0x4004CC19L)

//
// MessageId: EMS_ALARM_ALARMRETCODE
//
// MessageText:
//
//  GeoLeoAlarmInfo retcode=%1
//
#define EMS_ALARM_ALARMRETCODE           ((EMS_RESULT)0x4004CC1AL)

//
// MessageId: EMS_ALARM_STATUSCOLLECTOR
//
// MessageText:
//
//  *Status: Collector elapsed = %1, freq=%2
//
#define EMS_ALARM_STATUSCOLLECTOR        ((EMS_RESULT)0x4004CC1BL)

//
// MessageId: EMS_ALARM_SECABOVE5
//
// MessageText:
//
//  Seconds Above 5 = %1
//
#define EMS_ALARM_SECABOVE5              ((EMS_RESULT)0x4004CC1CL)

//
// MessageId: EMS_ALARM_TIMEDELTA
//
// MessageText:
//
//  Time Delta = %1
//
#define EMS_ALARM_TIMEDELTA              ((EMS_RESULT)0x4004CC1DL)

//
// MessageId: EMS_ALARM_ABOVE5DELTA
//
// MessageText:
//
//  Above 5 TDelta = %1
//
#define EMS_ALARM_ABOVE5DELTA            ((EMS_RESULT)0x4004CC1EL)

//
// MessageId: EMS_ALARM_PDSFRAMERATE
//
// MessageText:
//
//  PDSFrameRate =%1
//
#define EMS_ALARM_PDSFRAMERATE           ((EMS_RESULT)0x4004CC1FL)

//
// MessageId: EMS_ALARM_STARTPASS
//
// MessageText:
//
//  StartPass Sat=%1
//
#define EMS_ALARM_STARTPASS              ((EMS_RESULT)0x4004CC20L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC121
//
// MessageText:
//
//  Alarm: Expecting more than (%1 CBC 121Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC121 ((EMS_RESULT)0xC004CC21L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC121
//
// MessageText:
//
//  Warning: Expecting more than (%1 CBC 121Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC121 ((EMS_RESULT)0x8004CC21L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC243
//
// MessageText:
//
//  Alarm: Expecting more than (%1 CBC 243Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC243 ((EMS_RESULT)0xC004CC22L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC243
//
// MessageText:
//
//  Warning: Expecting more than (%1 CBC 243Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC243 ((EMS_RESULT)0x8004CC22L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC406
//
// MessageText:
//
//  Alarm: Expecting more than (%1 CBC 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC406 ((EMS_RESULT)0xC004CC23L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC406
//
// MessageText:
//
//  Warning: Expecting more than (%1 CBC 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC406 ((EMS_RESULT)0x8004CC23L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_SARP406
//
// MessageText:
//
//  Alarm: Expecting more than (%1 SARP 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_SARP406 ((EMS_RESULT)0xC004CC24L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_SARP406
//
// MessageText:
//
//  Warning: Expecting more than (%1 SARP 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_SARP406 ((EMS_RESULT)0x8004CC24L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_SARR406
//
// MessageText:
//
//  Alarm: Expecting more than (%1 SARR 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_SARR406 ((EMS_RESULT)0xC004CC25L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_SARR406
//
// MessageText:
//
//  Warning: Expecting more than (%1 SARR 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_SARR406 ((EMS_RESULT)0x8004CC25L)

//
// MessageId: EMS_STATUS_MUTEX_INIT_ERROR
//
// MessageText:
//
//  Master Status: Failed to obtain handle onto shared mutex.
//
#define EMS_STATUS_MUTEX_INIT_ERROR      ((EMS_RESULT)0x8004CC26L)

//
// MessageId: EMS_ALARM_TOO_FEW_GEO_DETECTIONS
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
//
#define EMS_ALARM_TOO_FEW_GEO_DETECTIONS ((EMS_RESULT)0xC004CC27L)

//
// MessageId: EMS_WARNING_TOO_FEW_GEO_DETECTIONS
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
//
#define EMS_WARNING_TOO_FEW_GEO_DETECTIONS ((EMS_RESULT)0x8004CC27L)

//
// MessageId: EMS_ALARM_TOO_FEW_GEO_INTEGRATIONS
//
// MessageText:
//
//  Alarm: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
//
#define EMS_ALARM_TOO_FEW_GEO_INTEGRATIONS ((EMS_RESULT)0xC004CC28L)

//
// MessageId: EMS_WARNING_TOO_FEW_GEO_INTEGRATIONS
//
// MessageText:
//
//  Warning: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
//
#define EMS_WARNING_TOO_FEW_GEO_INTEGRATIONS ((EMS_RESULT)0x8004CC28L)

//
// MessageId: EMS_INFO_COLLECTOR_MODINDEX
//
// MessageText:
//
//  Info: Collector detected high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_INFO_COLLECTOR_MODINDEX      ((EMS_RESULT)0x4004CC29L)

//
// MessageId: EMS_ALARM_ANTENNA_FAULT
//
// MessageText:
//
//  Alarm: Antenna has reported a fault.
//
#define EMS_ALARM_ANTENNA_FAULT          ((EMS_RESULT)0xC004CC2AL)

//
// MessageId: EMS_ALARM_COMM_RETRY_LIMIT_RTE
//
// MessageText:
//
//  Alarm: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
//
#define EMS_ALARM_COMM_RETRY_LIMIT_RTE   ((EMS_RESULT)0xC004CC2BL)

//
// MessageId: EMS_WARN_COMM_RETRY_LIMIT_RTE
//
// MessageText:
//
//  Warning: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
//
#define EMS_WARN_COMM_RETRY_LIMIT_RTE    ((EMS_RESULT)0x8004CC2BL)


#endif // INC_ALARMSGS
