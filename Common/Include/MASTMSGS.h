/********************************************************************
*	Module:			MastMsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Master Errors & Messages
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
#ifndef INC_MASTMSGS
#define INC_MASTMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

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
// MessageId: EMS_MAST_BASE_CODE
//
// MessageText:
//
//  EMS Master Error
//
#define EMS_MAST_BASE_CODE               ((EMS_RESULT)0x0004AB00L)

//
// MessageId: EMS_MAST_SERVICE_START
//
// MessageText:
//
//  EMS Master Service Started
//
#define EMS_MAST_SERVICE_START           ((EMS_RESULT)0x0004AB01L)

//
// MessageId: EMS_MAST_SERVICE_FAILED
//
// MessageText:
//
//  EMS Master Service did not start due to error %1
//
#define EMS_MAST_SERVICE_FAILED          ((EMS_RESULT)0x8004AB02L)

//
// MessageId: EMS_MAST_SERVICE_STOP
//
// MessageText:
//
//  EMS Master Service Stopped
//
#define EMS_MAST_SERVICE_STOP            ((EMS_RESULT)0x0004AB03L)

//
// MessageId: EMS_MAST_PASS_START
//
// MessageText:
//
//  EMS Master Service Starting Pass ( Sat=%1, Lut=%2, Flags=%3 )
//
#define EMS_MAST_PASS_START              ((EMS_RESULT)0x0004AB04L)

//
// MessageId: EMS_MAST_PASS_STOP
//
// MessageText:
//
//  EMS Master Service Stopped Pass for Sat %1
//
#define EMS_MAST_PASS_STOP               ((EMS_RESULT)0x0004AB05L)

//
// MessageId: EMS_MAST_ERROR
//
// MessageText:
//
//  EMS Master reports error %1.
//
#define EMS_MAST_ERROR                   ((EMS_RESULT)0x8004AB06L)

//
// MessageId: EMS_MAST_RECV_COMMAND
//
// MessageText:
//
//  EMS Master received command ( %1 ).
//
#define EMS_MAST_RECV_COMMAND            ((EMS_RESULT)0x0004AB07L)

//
// MessageId: EMS_MAST_GPSCLOCK_DIFF
//
// MessageText:
//
//  EMS Master : System clock differs from the GPS clock by %1 seconds.
//
#define EMS_MAST_GPSCLOCK_DIFF           ((EMS_RESULT)0x8004AB08L)

//
// MessageId: EMS_MAST_SITEINFO_ERR
//
// MessageText:
//
//  EMS Master : Reports error %1 while trying to retrieve site information.
//
#define EMS_MAST_SITEINFO_ERR            ((EMS_RESULT)0x8004AB09L)

//
// MessageId: EMS_MAST_MSG_IGNORED
//
// MessageText:
//
//  EMS Master : Ignoring message in file %1 - Unsupported.
//
#define EMS_MAST_MSG_IGNORED             ((EMS_RESULT)0x8004AB0AL)

//
// MessageId: EMS_MAST_SEND_TRACK_SCHED
//
// MessageText:
//
//  EMS Master sending track schedule to database.
//
#define EMS_MAST_SEND_TRACK_SCHED        ((EMS_RESULT)0x0004AB0BL)

//
// MessageId: EMS_MAST_ERR_TRACK_SCHED
//
// MessageText:
//
//  EMS Master reports error %1 sending track schedule.
//
#define EMS_MAST_ERR_TRACK_SCHED         ((EMS_RESULT)0x8004AB0CL)

//
// MessageId: EMS_MAST_SCHEDINFO_ERR
//
// MessageText:
//
//  EMS Master : Reports error %1 while trying to retrieve schedule information.
//
#define EMS_MAST_SCHEDINFO_ERR           ((EMS_RESULT)0x8004AB0DL)

//
// MessageId: EMS_MAST_PASS_END
//
// MessageText:
//
//  EMS Master reports end of pass
//
#define EMS_MAST_PASS_END                ((EMS_RESULT)0x0004AB0EL)

//
// MessageId: EMS_MASTER_TRACER
//
// MessageText:
//
//  EMS Master tracer (%1).
//
#define EMS_MASTER_TRACER                ((EMS_RESULT)0x0004AB0FL)

//
// MessageId: EMS_MAST_GPSCLOCK_CHANGE
//
// MessageText:
//
//  EMS Master : System clock adjusted by %1 seconds by the GPS clock.
//
#define EMS_MAST_GPSCLOCK_CHANGE         ((EMS_RESULT)0x0004AB10L)

//
// MessageId: EMS_MAST_SIT_UNKNOWN
//
// MessageText:
//
//  EMS Master : Unknown SitMsg (%1) ignored.
//
#define EMS_MAST_SIT_UNKNOWN             ((EMS_RESULT)0x8004AB11L)

//
// MessageId: EMS_MAST_SIT_ERR
//
// MessageText:
//
//  EMS Master : Error while processing SitMsg ( %1 ).
//
#define EMS_MAST_SIT_ERR                 ((EMS_RESULT)0x8004AB12L)

//
// MessageId: EMS_MAST_SIT415
//
// MessageText:
//
//  EMS Master : SitMsg415 processed ( %1 ). 
//
#define EMS_MAST_SIT415                  ((EMS_RESULT)0x0004AB13L)

//
// MessageId: EMS_MAST_SIT510
//
// MessageText:
//
//  EMS Master : SitMsg510 processed ( %1 ). 
//
#define EMS_MAST_SIT510                  ((EMS_RESULT)0x0004AB14L)

//
// MessageId: EMS_MAST_SIT_UNEXPECTED
//
// MessageText:
//
//  EMS Master : SitMsg %1 was unexpected ( File=%2 ). 
//
#define EMS_MAST_SIT_UNEXPECTED          ((EMS_RESULT)0x8004AB15L)

//
// MessageId: EMS_MAST_SIT255
//
// MessageText:
//
//  EMS Master : SitMsg255 processed ( %1 ). 
//
#define EMS_MAST_SIT255                  ((EMS_RESULT)0x0004AB16L)

//
// MessageId: EMS_MAST_SIT215
//
// MessageText:
//
//  EMS Master : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_MAST_SIT215                  ((EMS_RESULT)0x0004AB17L)

//
// MessageId: EMS_MAST_CREATE_INSTANCE_ERR
//
// MessageText:
//
//  EMS Master : Unable to create instance of %1 during startup.
//
#define EMS_MAST_CREATE_INSTANCE_ERR     ((EMS_RESULT)0x8004AB18L)

//
// MessageId: EMS_MAST_SYSTEM_STARTUP
//
// MessageText:
//
//  EMS Master : Reports System Startup
//
#define EMS_MAST_SYSTEM_STARTUP          ((EMS_RESULT)0x0004AB19L)

//
// MessageId: EMS_MAST_STATUS_AOS
//
// MessageText:
//
//  %1
//
#define EMS_MAST_STATUS_AOS              ((EMS_RESULT)0x0004AB1AL)

//
// MessageId: EMS_MAST_STATUS_LOS
//
// MessageText:
//
//  %1,EMS Master Status
//
#define EMS_MAST_STATUS_LOS              ((EMS_RESULT)0x0004AB1BL)

//
// MessageId: EMS_MAST_NO_SYSTEST_TIME
//
// MessageText:
//
//  EMS Master reports insufficient time for system test.
//
#define EMS_MAST_NO_SYSTEST_TIME         ((EMS_RESULT)0x0004AB1CL)

//
// MessageId: EMS_MAST_NEW_ORBIT_VECTOR
//
// MessageText:
//
//  EMS Master installed new orbit vectors for %1.
//
#define EMS_MAST_NEW_ORBIT_VECTOR        ((EMS_RESULT)0x0004AB1DL)

//
// MessageId: EMS_MAST_ERR_ORBIT_VECTOR
//
// MessageText:
//
//  EMS Master reports orbit vectors error for %1.
//
#define EMS_MAST_ERR_ORBIT_VECTOR        ((EMS_RESULT)0x8004AB1EL)

//
// MessageId: EMS_MAST_SIT_MSG_RECV
//
// MessageText:
//
//  EMS Master received SitMsg %1.
//
#define EMS_MAST_SIT_MSG_RECV            ((EMS_RESULT)0x0004AB1FL)

//
// MessageId: EMS_MAST_PASS_IN_PROGRESS
//
// MessageText:
//
//  EMS Master is currently processing a pass.
//
#define EMS_MAST_PASS_IN_PROGRESS        ((EMS_RESULT)0x0004AB20L)

//
// MessageId: EMS_MAST_RESTARTING
//
// MessageText:
//
//  EMS Master was instructed to perform a WARM restart. 
//
#define EMS_MAST_RESTARTING              ((EMS_RESULT)0x0004AB21L)

//
// MessageId: EMS_MAST_REBOOT
//
// MessageText:
//
//  EMS Master was instructed to perform a COLD restart. 
//
#define EMS_MAST_REBOOT                  ((EMS_RESULT)0x0004AB22L)

//
// MessageId: EMS_MAST_ERR_INVALID_ORBIT
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors for %1.
//
#define EMS_MAST_ERR_INVALID_ORBIT       ((EMS_RESULT)0x8004AB23L)

//
// MessageId: EMS_MAST_SIT255_ERR
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors when processing SitMsg255 ( %1 ).
//
#define EMS_MAST_SIT255_ERR              ((EMS_RESULT)0x8004AB24L)

//
// MessageId: EMS_MAST_SET_CONFIG
//
// MessageText:
//
//  EMS Master reports config change (%1).
//
#define EMS_MAST_SET_CONFIG              ((EMS_RESULT)0x0004AB25L)

//
// MessageId: EMS_MAST_SIT750A_ERR
//
// MessageText:
//
//  EMS Master reports syntax error processing SIT 750A ( %1 ).
//
#define EMS_MAST_SIT750A_ERR             ((EMS_RESULT)0x8004AB26L)

//
// MessageId: EMS_MAST_AUDIO_NOT_AVAIL
//
// MessageText:
//
//  EMS Master unable to retrieve requested audio data ( %1 ).
//
#define EMS_MAST_AUDIO_NOT_AVAIL         ((EMS_RESULT)0x8004AB27L)

//
// MessageId: EMS_MAST_SIT750A_INVALID_OPTION
//
// MessageText:
//
//  EMS Master reports invalid option in SIT 750A ( %1 ).
//
#define EMS_MAST_SIT750A_INVALID_OPTION  ((EMS_RESULT)0x8004AB28L)

//
// MessageId: EMS_MAST_GENERATED_PASS_SCHED
//
// MessageText:
//
//  EMS Master generated a new pass schedule.
//
#define EMS_MAST_GENERATED_PASS_SCHED    ((EMS_RESULT)0x0004AB29L)

//
// MessageId: EMS_MAST_GENERATED_PASS_SCHED_ERR
//
// MessageText:
//
//  EMS Master reports error ( %1 ) while generating a new pass schedule.
//
#define EMS_MAST_GENERATED_PASS_SCHED_ERR ((EMS_RESULT)0x8004AB2AL)

//
// MessageId: EMS_MAST_INSTALLED_PASS_SCHED
//
// MessageText:
//
//  EMS Master installed a new pass schedule.
//
#define EMS_MAST_INSTALLED_PASS_SCHED    ((EMS_RESULT)0x0004AB2BL)

//
// MessageId: EMS_MAST_DISK_PASS_SCHED
//
// MessageText:
//
//  EMS Master installed last saved pass schedule.
//
#define EMS_MAST_DISK_PASS_SCHED         ((EMS_RESULT)0x0004AB2CL)

//
// MessageId: EMS_MAST_SITMSG_PASS_SCHED
//
// MessageText:
//
//  EMS Master received a new pass schedule.
//
#define EMS_MAST_SITMSG_PASS_SCHED       ((EMS_RESULT)0x0004AB2DL)

//
// MessageId: EMS_MAST_VALIDATE_PASS_SCHED
//
// MessageText:
//
//  EMS Master received a pass schedule to validate.
//
#define EMS_MAST_VALIDATE_PASS_SCHED     ((EMS_RESULT)0x0004AB2EL)

//
// MessageId: EMS_MAST_SCHED_VALIDATED
//
// MessageText:
//
//  EMS Master validated received pass schedule (VALI).
//
#define EMS_MAST_SCHED_VALIDATED         ((EMS_RESULT)0x0004AB2FL)

//
// MessageId: EMS_MAST_SCHED_INVALID
//
// MessageText:
//
//  EMS Master reports no valid entries in received pass schedule (VALI).
//
#define EMS_MAST_SCHED_INVALID           ((EMS_RESULT)0x0004AB30L)

//
// MessageId: EMS_MAST_SCHED_INFO
//
// MessageText:
//
//  EMS Master received a pass schedule for information only.
//
#define EMS_MAST_SCHED_INFO              ((EMS_RESULT)0x0004AB31L)

//
// MessageId: EMS_MAST_SCHED_BAD_OPTION
//
// MessageText:
//
//  EMS Master received a pass schedule with an unrecognised install option.
//
#define EMS_MAST_SCHED_BAD_OPTION        ((EMS_RESULT)0x0004AB32L)

//
// MessageId: EMS_MAST_BAD_ORBIT_OPTION
//
// MessageText:
//
//  EMS Master encountered invalid MF605 while processing orbit vector.
//
#define EMS_MAST_BAD_ORBIT_OPTION        ((EMS_RESULT)0x0004AB33L)

//
// MessageId: EMS_MAST_SYSTEST_MISSING_SERVICE
//
// MessageText:
//
//  EMS Master timed out waiting for the Antenna or SysTest Service.
//
#define EMS_MAST_SYSTEST_MISSING_SERVICE ((EMS_RESULT)0x8004AB34L)

//
// MessageId: EMS_MAST_PENDING_SCHEDULE
//
// MessageText:
//
//  EMS Master reports pending schedule, waiting for end of pass.
//
#define EMS_MAST_PENDING_SCHEDULE        ((EMS_RESULT)0x0004AB35L)

//
// MessageId: EMS_ORBIT_NUMBER_NOT_MATCH
//
// MessageText:
//
//  EMS Master reports one or more passes in the supplied schedule had different orbit number.
//
#define EMS_ORBIT_NUMBER_NOT_MATCH       ((EMS_RESULT)0x0004AB36L)

//
// MessageId: EMS_MAST_FORCED_ENDOFPASS
//
// MessageText:
//
//  EMS Master reports handling forced end of pass.
//
#define EMS_MAST_FORCED_ENDOFPASS        ((EMS_RESULT)0x8004AB37L)

//
// MessageId: EMS_MAST_INITIAL_PROCESS_TIMEOUT
//
// MessageText:
//
//  EMS Master timed out waiting for the core services to start.
//
#define EMS_MAST_INITIAL_PROCESS_TIMEOUT ((EMS_RESULT)0x8004AB38L)

//
// MessageId: EMS_MAST_SYSTEST_TIME_CONFLICT
//
// MessageText:
//
//  EMS Master skipping system test due to insufficient time or pass conflict.
//
#define EMS_MAST_SYSTEST_TIME_CONFLICT   ((EMS_RESULT)0x0004AB39L)

//
// MessageId: EMS_MAST_COMMAND_NOT_SUPPORTED
//
// MessageText:
//
//  EMS Master reports receiving a command that is not handled.
//
#define EMS_MAST_COMMAND_NOT_SUPPORTED   ((EMS_RESULT)0x8004AB3AL)

//
// MessageId: EMS_MAST_PASS_SCHED_CANT_INSTALL
//
// MessageText:
//
//  EMS Master reports an error installing the pass schedule.  A pass in progress.
//
#define EMS_MAST_PASS_SCHED_CANT_INSTALL ((EMS_RESULT)0x8004AB3BL)

//
// MessageId: EMS_MAST_CREATE_INSTANCE_ERR_HR
//
// MessageText:
//
//  EMS Master : Unable to create instance of %1 during startup (Error=%2).
//
#define EMS_MAST_CREATE_INSTANCE_ERR_HR  ((EMS_RESULT)0x8004AB3CL)

//
// MessageId: EMS_MASTER_TRACE_PASSSCHEDSETTINGS
//
// MessageText:
//
//  EMS Master tracer ( PassSchedSettings: PrePass=%1, Tol=%2, Flags=%3 )
//
#define EMS_MASTER_TRACE_PASSSCHEDSETTINGS ((EMS_RESULT)0x0004AB3DL)

//
// MessageId: EMS_MAST_SITEINFO_ERR_HR
//
// MessageText:
//
//  EMS Master : Reports error %2 while trying to retrieve site information %1.
//
#define EMS_MAST_SITEINFO_ERR_HR         ((EMS_RESULT)0x8004AB3EL)

//
// MessageId: EMS_MAST_ERR_INVALID_SATORBIT
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors for sat=%1.
//
#define EMS_MAST_ERR_INVALID_SATORBIT    ((EMS_RESULT)0x8004AB3FL)

//
// MessageId: EMS_MASTER_TRACE_NOACK
//
// MessageText:
//
//  EMS Master tracer ( No ACK: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NOACK           ((EMS_RESULT)0x0004AB40L)

//
// MessageId: EMS_MASTER_TRACE_NORESPONSE
//
// MessageText:
//
//  EMS Master tracer ( No Response: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NORESPONSE      ((EMS_RESULT)0x0004AB41L)

//
// MessageId: EMS_MASTER_TRACE_NOLOG
//
// MessageText:
//
//  EMS Master tracer ( No Log: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NOLOG           ((EMS_RESULT)0x0004AB42L)

//
// MessageId: EMS_MAST_SIT255_MSG
//
// MessageText:
//
//  EMS Master : SitMsg255 processed ( Message=%1 ). 
//
#define EMS_MAST_SIT255_MSG              ((EMS_RESULT)0x0004AB43L)

//
// MessageId: EMS_MAST_SIT255_ERR_MSG
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1 ).  
//
#define EMS_MAST_SIT255_ERR_MSG          ((EMS_RESULT)0x8004AB44L)

//
// MessageId: EMS_MAST_SIT415_DETAILS
//
// MessageText:
//
//  EMS Master : SitMsg415 processed ( Sat=%1  Freq=%2 Time=%3 ). 
//
#define EMS_MAST_SIT415_DETAILS          ((EMS_RESULT)0x0004AB45L)

//
// MessageId: EMS_MAST_SIT510_DETAILS
//
// MessageText:
//
//  EMS Master : SitMsg510 processed ( Sat=%1 FreqOffset=%2 ). 
//
#define EMS_MAST_SIT510_DETAILS          ((EMS_RESULT)0x0004AB46L)

//
// MessageId: EMS_MAST_TIME_ZONE
//
// MessageText:
//
//  EMS Master reports system clock not set to UTC, daylight savings OFF (%1).
//
#define EMS_MAST_TIME_ZONE               ((EMS_RESULT)0x8004AB47L)

//
// MessageId: EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
//  EMS Master installed new orbit vectors for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x0004AB48L)

//
// MessageId: EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
//  EMS Master reports orbit vectors error for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x8004AB49L)

//
// MessageId: EMS_MAST_ERR_INVALID_ORBIT_SAT
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors for Sat=%1.
//
#define EMS_MAST_ERR_INVALID_ORBIT_SAT   ((EMS_RESULT)0x8004AB4AL)

//
// MessageId: EMS_MAST_PASS_SCHED_FILE_EMPTY
//
// MessageText:
//
//  EMS Master reports finding the Pass Schedule file, but it contains no passes.
//
#define EMS_MAST_PASS_SCHED_FILE_EMPTY   ((EMS_RESULT)0x0004AB4BL)

//
// MessageId: EMS_MAST_STOPPING_DB
//
// MessageText:
//
//  EMS Master is stopping the database.
//
#define EMS_MAST_STOPPING_DB             ((EMS_RESULT)0x0004AB4CL)

//
// MessageId: EMS_MAST_FAILED_TO_START_DB
//
// MessageText:
//
//  EMS Master : Failed to start the database (%1).
//
#define EMS_MAST_FAILED_TO_START_DB      ((EMS_RESULT)0x8004AB4DL)

//
// MessageId: EMS_MAST_FAILED_TO_STOP_DB
//
// MessageText:
//
//  EMS Master : Failed to stop the database (%1).
//
#define EMS_MAST_FAILED_TO_STOP_DB       ((EMS_RESULT)0x8004AB4EL)

//
// MessageId: EMS_MAST_SCHED_REJECTED
//
// MessageText:
//
//  EMS Master: Supplied pass schedule was rejected as invalid.
//
#define EMS_MAST_SCHED_REJECTED          ((EMS_RESULT)0x8004AB4FL)

//
// MessageId: EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT
//
// MessageText:
//
//  EMS Master: The orbit data for satellite %1 may be corrupted. Pass schedule validation found %2 passes for this satellite that do not match the LUT predicted times.
//
#define EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT ((EMS_RESULT)0x8004AB50L)

//
// MessageId: EMS_MAST_PASS_OUTSIDE_TOLERANCE
//
// MessageText:
//
//  EMS Master reports one or more passes in the supplied schedule were suppressed. Given AOS/LOS times did not match LUT predictions.
//
#define EMS_MAST_PASS_OUTSIDE_TOLERANCE  ((EMS_RESULT)0x8004AB51L)

//
// MessageId: EMS_MAST_PASS_TOO_OLD
//
// MessageText:
//
//  EMS Master reports one or more passes in the supplied schedule were suppressed. AOS/LOS times were too old.
//
#define EMS_MAST_PASS_TOO_OLD            ((EMS_RESULT)0x8004AB52L)

//
// MessageId: EMS_MAST_PASS_ERROR_DURING_VALIDATION
//
// MessageText:
//
//  EMS Master reports pass suppressed because of error detected during validation (%1).
//
#define EMS_MAST_PASS_ERROR_DURING_VALIDATION ((EMS_RESULT)0x8004AB53L)

//
// MessageId: EMS_MAST_PASS_SCHED_NO_VALID_PASSES
//
// MessageText:
//
//  EMS Master: Pass schedule rejected. There were no unsupressed passes to be processed by this LUT.
//
#define EMS_MAST_PASS_SCHED_NO_VALID_PASSES ((EMS_RESULT)0x8004AB54L)

//
// MessageId: EMS_MAST_SARP_CALIBRATIONTIME_INVALID
//
// MessageText:
//
//  EMS Master: Invalid sarp calibration data.  Difference between new and old calibration times exceeds configured maximum.
//
#define EMS_MAST_SARP_CALIBRATIONTIME_INVALID ((EMS_RESULT)0x8004AB55L)

//
// MessageId: EMS_MAST_SARP_REFFREQUENCY_INVALID
//
// MessageText:
//
//  EMS Master: Invalid sarp calibration data.  Difference between new and old reference frequencies exceed configured maximum.
//
#define EMS_MAST_SARP_REFFREQUENCY_INVALID ((EMS_RESULT)0x8004AB56L)

//
// MessageId: EMS_MAST_SARP_REFFREQUENCY_CALIBRATIONTIME_INVALID
//
// MessageText:
//
//  EMS Master: Invalid sarp calibration data.  Differences between old and new values for calibration time and reference frequency both exceed configured maximums.
//
#define EMS_MAST_SARP_REFFREQUENCY_CALIBRATIONTIME_INVALID ((EMS_RESULT)0x8004AB57L)

//
// MessageId: EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
//  EMS Master installed post manoeuvre orbit vectors for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x0004AB58L)

//
// MessageId: EMS_MAST_OUTDATED_VECTORS
//
// MessageText:
//
//  EMS Master reports that installed orbit vectors for Sat %1 were installed %2 days ago and may now be out of date.
//
#define EMS_MAST_OUTDATED_VECTORS        ((EMS_RESULT)0x8004AB59L)

//
// MessageId: EMS_MAST_OUTDATED_TCAL
//
// MessageText:
//
//  EMS Master reports that TCAL data for Sat %1 was installed %2 days ago and may now be out of date.
//
#define EMS_MAST_OUTDATED_TCAL           ((EMS_RESULT)0x8004AB5AL)

//
// MessageId: EMS_MAST_ORBIT_PROBLEM
//
// MessageText:
//
//  EMS Master reports Orbit Error %1 for Sat %2.
//
#define EMS_MAST_ORBIT_PROBLEM           ((EMS_RESULT)0x8004AB5BL)

//
// MessageId: EMS_MAST_SIT_SARPCALIB_DETAILS
//
// MessageText:
//
//  EMS Master : Sarp Calibration (SitMsg%1) received ( Sat=%2  Freq=%3 Time=%4 ). 
//
#define EMS_MAST_SIT_SARPCALIB_DETAILS   ((EMS_RESULT)0x0004AB5CL)

//
// MessageId: EMS_MAST_GPSCLOCK_ERROR
//
// MessageText:
//
//  EMS Master : Failed to communicate with GPS clock (%1).
//
#define EMS_MAST_GPSCLOCK_ERROR          ((EMS_RESULT)0x8004AB5DL)

//
// MessageId: EMS_MAST_SIT255_ERR_MSG2
//
// MessageText:
//
//  EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1, Error=%2 ).
//
#define EMS_MAST_SIT255_ERR_MSG2         ((EMS_RESULT)0x8004AB5EL)

//
// MessageId: EMS_MAST_ERR_SAT_NO_ORBIT_DATA
//
// MessageText:
//
//  EMS Master reports no orbit data available for satellite <%1>.
//
#define EMS_MAST_ERR_SAT_NO_ORBIT_DATA   ((EMS_RESULT)0x8004AB5FL)

//
// MessageId: EMS_MAST_RESTARTING_FP
//
// MessageText:
//
//  EMS Master sending a restart command to the FP.
//
#define EMS_MAST_RESTARTING_FP           ((EMS_RESULT)0x0004AB60L)

//
// MessageId: EMS_MAST_REBOOTING_FP
//
// MessageText:
//
//  EMS Master sending a reboot command to the FP.
//
#define EMS_MAST_REBOOTING_FP            ((EMS_RESULT)0x0004AB61L)

//
// MessageId: EMS_MAST_EXCEPTION_SENDING_FP_RESTART
//
// MessageText:
//
//  EMS Master: Exception while sending a restart command to the FP.
//
#define EMS_MAST_EXCEPTION_SENDING_FP_RESTART ((EMS_RESULT)0x8004AB62L)

//
// MessageId: EMS_MAST_EXCEPTION_SENDING_FP_REBOOT
//
// MessageText:
//
//  EMS Master: Exception while sending a reboot command to the FP.
//
#define EMS_MAST_EXCEPTION_SENDING_FP_REBOOT ((EMS_RESULT)0x8004AB63L)


#endif // INC_MASTMSGS
