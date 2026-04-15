/********************************************************************
*	Module:			Calib406Msg.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Calib406 Errors & Messages
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
#ifndef INC_CALIB406MSG
#define INC_CALIB406MSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values laid out as follows:
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
// MessageId: EMS_CALIB406_BASE_CODE
//
// MessageText:
//
// EMS Calibrate406 Error
//
#define EMS_CALIB406_BASE_CODE           ((EMS_RESULT)0x0004A400L)

//
// MessageId: EMS_CALIB406_SERVICE_START
//
// MessageText:
//
// EMS Calibrate406 Service Started
//
#define EMS_CALIB406_SERVICE_START       ((EMS_RESULT)0x0004A401L)

//
// MessageId: EMS_CALIB406_SERVICE_FAILED
//
// MessageText:
//
// EMS Calibrate406 Service did not start due to error %1
//
#define EMS_CALIB406_SERVICE_FAILED      ((EMS_RESULT)0x8004A402L)

//
// MessageId: EMS_CALIB406_SERVICE_STOP
//
// MessageText:
//
// EMS Calibrate406 Service Stopped
//
#define EMS_CALIB406_SERVICE_STOP        ((EMS_RESULT)0x0004A403L)

//
// MessageId: EMS_CALIB406_ERROR
//
// MessageText:
//
// EMS Calibrate406 reports error %1.
//
#define EMS_CALIB406_ERROR               ((EMS_RESULT)0x8004A404L)

//
// MessageId: EMS_CALIB406_PRIORITY_CLASS
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetPriorityClass
//
#define EMS_CALIB406_PRIORITY_CLASS      ((EMS_RESULT)0x8004A405L)

//
// MessageId: EMS_CALIB406_THREAD_PRIORITY
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetThreadPriority
//
#define EMS_CALIB406_THREAD_PRIORITY     ((EMS_RESULT)0x8004A406L)

//
// MessageId: EMS_CALIB406_IDEAL_PROCESSOR
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetThreadIdealProcessor
//
#define EMS_CALIB406_IDEAL_PROCESSOR     ((EMS_RESULT)0x8004A407L)

//
// MessageId: EMS_CALIB406_START_PASS
//
// MessageText:
//
// EMS Calibrate406 reports initialized pass for satellite %1
//
#define EMS_CALIB406_START_PASS          ((EMS_RESULT)0x0004A408L)

//
// MessageId: EMS_CALIB406_CALIBRATE_PASS
//
// MessageText:
//
// EMS Calibrate406 starting to calibrate pass for satellite %1
//
#define EMS_CALIB406_CALIBRATE_PASS      ((EMS_RESULT)0x0004A409L)

//
// MessageId: EMS_CALIB406_CALIBRATE_PASS_DONE
//
// MessageText:
//
// EMS Calibrate406 finished calibrating pass for satellite %1
//
#define EMS_CALIB406_CALIBRATE_PASS_DONE ((EMS_RESULT)0x0004A40AL)

//
// MessageId: EMS_CALIB406_TRACER
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( %1 )
//
#define EMS_CALIB406_TRACER              ((EMS_RESULT)0x0004A40BL)

//
// MessageId: EMS_CALIB406_HISTORY_RECS
//
// MessageText:
//
// EMS Calibrate406 read %1 history records.
//
#define EMS_CALIB406_HISTORY_RECS        ((EMS_RESULT)0x0004A40CL)

//
// MessageId: EMS_CALIB406_BUFFER_ADD
//
// MessageText:
//
// EMS Calibrate406 reports an error adding record %1 to the buffer.
//
#define EMS_CALIB406_BUFFER_ADD          ((EMS_RESULT)0x8004A40DL)

//
// MessageId: EMS_CALIB406_NEW_SARR_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 : New SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
//
#define EMS_CALIB406_NEW_SARR_OFFSETS    ((EMS_RESULT)0x0004A40EL)

//
// MessageId: EMS_CALIB406_CALC_SARR_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 : Insufficient Points for SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
//
#define EMS_CALIB406_CALC_SARR_OFFSETS   ((EMS_RESULT)0x0004A40FL)

//
// MessageId: EMS_CALIB406_SARP_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 has calculated new SARP Offsets ( SatID = %1, Freq=%2, Time=%3 ).
//
#define EMS_CALIB406_SARP_OFFSETS        ((EMS_RESULT)0x0004A410L)

//
// MessageId: EMS_CALIB406_ORBIT_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSOrbit.
//
#define EMS_CALIB406_ORBIT_ERROR         ((EMS_RESULT)0x8004A411L)

//
// MessageId: EMS_CALIB406_SAT_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSSatInfo.
//
#define EMS_CALIB406_SAT_INFO_ERROR      ((EMS_RESULT)0x8004A412L)

//
// MessageId: EMS_CALIB406_LUT_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSLutInfo.
//
#define EMS_CALIB406_LUT_INFO_ERROR      ((EMS_RESULT)0x8004A413L)

//
// MessageId: EMS_CALIB406_SITE_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSLeo600SiteInfo
//
#define EMS_CALIB406_SITE_INFO_ERROR     ((EMS_RESULT)0x8004A414L)

//
// MessageId: EMS_CALIB406_REF_BEACON_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSRefBeacon.
//
#define EMS_CALIB406_REF_BEACON_ERROR    ((EMS_RESULT)0x8004A415L)

//
// MessageId: EMS_CALIB406_HISTORY_OUT
//
// MessageText:
//
// EMS Calibrate406 wrote %1 history records.
//
#define EMS_CALIB406_HISTORY_OUT         ((EMS_RESULT)0x0004A416L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIG
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=%2 )
//
#define EMS_CALIB406_TRACE_CONFIG        ((EMS_RESULT)0x0004A417L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIGYES
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=yes )
//
#define EMS_CALIB406_TRACE_CONFIGYES     ((EMS_RESULT)0x0004A418L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIGNO
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=no )
//
#define EMS_CALIB406_TRACE_CONFIGNO      ((EMS_RESULT)0x0004A419L)

//
// MessageId: EMS_CALIB406_TRACE_SORTEXCEPTION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( EX: Left=%1 ,Right=%2, Split=%3, Max=%4, Depth=%5 )
//
#define EMS_CALIB406_TRACE_SORTEXCEPTION ((EMS_RESULT)0x0004A41AL)

//
// MessageId: EMS_CALIB406_TRACE_SELNSORTEXCEPTION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( EX (SelectionSort): Left=%1 ,Right=%2 )
//
#define EMS_CALIB406_TRACE_SELNSORTEXCEPTION ((EMS_RESULT)0x0004A41BL)

//
// MessageId: EMS_CALIB406_TRACE_PARTITION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Partition: Left=%1, Right=%2, Max=%3, *** )
//
#define EMS_CALIB406_TRACE_PARTITION     ((EMS_RESULT)0x0004A41CL)

//
// MessageId: EMS_CALIB406_TRACE_PARTITIONLTZERO
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Partition: Left=%d, Right=%d, Max=%d, Split < ZERO )
//
#define EMS_CALIB406_TRACE_PARTITIONLTZERO ((EMS_RESULT)0x0004A41DL)

//
// MessageId: EMS_CALIB406_TRACE_FORWARDINGCOUNT
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Forwarding %1 records for Beacon %2 )
//
#define EMS_CALIB406_TRACE_FORWARDINGCOUNT ((EMS_RESULT)0x0004A41EL)

//
// MessageId: EMS_CALIB406_TRACE_SARRSARPADDED
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( SarrSarpRecords Added=%1 )
//
#define EMS_CALIB406_TRACE_SARRSARPADDED ((EMS_RESULT)0x0004A41FL)

//
// MessageId: EMS_CALIB406_TRACE_BEFORELOCK
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( before lock )
//
#define EMS_CALIB406_TRACE_BEFORELOCK    ((EMS_RESULT)0x0004A420L)

//
// MessageId: EMS_CALIB406_TRACE_AFTERLOCK
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( after lock )
//
#define EMS_CALIB406_TRACE_AFTERLOCK     ((EMS_RESULT)0x0004A421L)

//
// MessageId: EMS_CALIB406_TRACE_HISTORYREAD
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( SarrSarpHistory records read = %1 )
//
#define EMS_CALIB406_TRACE_HISTORYREAD   ((EMS_RESULT)0x0004A422L)

//
// MessageId: EMS_CALIB406_ROLLOVER_PERIOD_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving rollover period from configuration.  The configuration manager returned error %1.
//
#define EMS_CALIB406_ROLLOVER_PERIOD_GET_ERROR ((EMS_RESULT)0x0004A423L)

//
// MessageId: EMS_CALIB406_ROLLOVER_PERIOD_ZERO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving rollover period.  The value is 0.
//
#define EMS_CALIB406_ROLLOVER_PERIOD_ZERO_ERROR ((EMS_RESULT)0x0004A424L)

//
// MessageId: EMS_CALIB406_SAT_CAPS_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving satellite capabilities for satellite %1 from configuration  The configuration manager returned error %2.
//
#define EMS_CALIB406_SAT_CAPS_GET_ERROR  ((EMS_RESULT)0x0004A425L)

//
// MessageId: EMS_CALIB406_SAT_PROCESSINFO_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving satellite processing information for satellite %1 from configuration  The configuration manager returned error %2.
//
#define EMS_CALIB406_SAT_PROCESSINFO_GET_ERROR ((EMS_RESULT)0x0004A426L)

//
// MessageId: EMS_CALIB406_TCAL_BEACON_COUNT
//
// MessageText:
//
// Calibration will use %1 TCAL beacons to check SARR time accuracy.
//
#define EMS_CALIB406_TCAL_BEACON_COUNT   ((EMS_RESULT)0x0004A427L)

//
// MessageId: EMS_CALIB406_SARR_TIME_ERROR
//
// MessageText:
//
// Calibration suggests that LutID(%1) AntennaID(%2) has a %3 second SARR time error.
//
#define EMS_CALIB406_SARR_TIME_ERROR     ((EMS_RESULT)0x8004A428L)

//
// MessageId: EMS_CALIB406_SARR_TIME_OKAY
//
// MessageText:
//
// Calibration confirms that LutID(%1) AntennaID(%2) has a valid SARR time.
//
#define EMS_CALIB406_SARR_TIME_OKAY      ((EMS_RESULT)0x0004A429L)

//
// MessageId: EMS_CALIB406_ORBIT_VECTOR
//
// MessageText:
//
// EMS Calibrate406 cannot calculate an orbit vector for Satellite %1.
//
#define EMS_CALIB406_ORBIT_VECTOR        ((EMS_RESULT)0x8004A42AL)

//
// MessageId: EMS_CALIB406_BUFFER_ADD_EX
//
// MessageText:
//
// EMS Calibrate406 reports an error(0x%1) adding record(%2) SatID(%3) BeaconID(%4).
//
#define EMS_CALIB406_BUFFER_ADD_EX       ((EMS_RESULT)0x8004A42BL)

//
// MessageId: EMS_CALIB406_DATA_SOURCE_PROBLEM
//
// MessageText:
//
// EMS Calibrate406 reports bad data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)).
//
#define EMS_CALIB406_DATA_SOURCE_PROBLEM ((EMS_RESULT)0x8004A42CL)

//
// MessageId: EMS_CALIB406_DATA_SOURCE_PROBLEM_CLEARED
//
// MessageText:
//
// EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)) is back to normal.
//
#define EMS_CALIB406_DATA_SOURCE_PROBLEM_CLEARED ((EMS_RESULT)0x0004A42DL)

//
// MessageId: EMS_CALIB406_TIME_SOURCE_PROBLEM
//
// MessageText:
//
// EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), BeaconID(%4), MessageTime (%5)) error.
//
#define EMS_CALIB406_TIME_SOURCE_PROBLEM ((EMS_RESULT)0x8004A42EL)

//
// MessageId: EMS_CALIB406_STOP_COMBINE_SARR_SARP
//
// MessageText:
//
// EMS Calibrate406 reports a frequency shift exceeding the allowable tolerance of %1Hz for satellite %2.  Combined SARR/SARP location processing will be disabled for the current pass.
//
#define EMS_CALIB406_STOP_COMBINE_SARR_SARP ((EMS_RESULT)0x8004A42FL)

//
// MessageId: EMS_CALIB406_LOW_NUMBER_SARP_RECORDS
//
// MessageText:
//
// EMS Calibrate406 produced low number of SARP records (%1) for satellite %2 passId %3.
//
#define EMS_CALIB406_LOW_NUMBER_SARP_RECORDS ((EMS_RESULT)0x8004A430L)


#endif // INC_CALIB406MSG
