;/********************************************************************
;*	Module:			MastMsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Master Errors & Messages
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
;#ifndef INC_MASTMSGS
;#define INC_MASTMSGS
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

MessageId=0xAB00 SymbolicName=EMS_MAST_BASE_CODE Facility=ITF
Language=English
EMS Master Error
.
MessageId=+1 SymbolicName=EMS_MAST_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Master Service Started
.
MessageId=+1 SymbolicName=EMS_MAST_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Master Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_MAST_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Master Service Stopped
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_START Severity=Success Facility=ITF
Language=English
EMS Master Service Starting Pass ( Sat=%1, Lut=%2, Flags=%3 )
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_STOP Severity=Success Facility=ITF
Language=English
EMS Master Service Stopped Pass for Sat %1
.
MessageId=+1 SymbolicName=EMS_MAST_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports error %1.
.
MessageId=+1 SymbolicName=EMS_MAST_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Master received command ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_GPSCLOCK_DIFF Severity=ErrWarn Facility=ITF
Language=English
EMS Master : System clock differs from the GPS clock by %1 seconds.
.
MessageId=+1 SymbolicName=EMS_MAST_SITEINFO_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Reports error %1 while trying to retrieve site information.
.
MessageId=+1 SymbolicName=EMS_MAST_MSG_IGNORED Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Ignoring message in file %1 - Unsupported.
.
MessageId=+1 SymbolicName=EMS_MAST_SEND_TRACK_SCHED Severity=Success Facility=ITF
Language=English
EMS Master sending track schedule to database.
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_TRACK_SCHED Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports error %1 sending track schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_SCHEDINFO_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Reports error %1 while trying to retrieve schedule information.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_END Severity=Success Facility=ITF
Language=English
EMS Master reports end of pass
.
MessageId=+1 SymbolicName=EMS_MASTER_TRACER Severity=Success Facility=ITF
Language=English
EMS Master tracer (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_GPSCLOCK_CHANGE Severity=Success Facility=ITF
Language=English
EMS Master : System clock adjusted by %1 seconds by the GPS clock.
.
MessageId=+1 SymbolicName=EMS_MAST_SIT_UNKNOWN Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Unknown SitMsg (%1) ignored.
.
MessageId=+1 SymbolicName=EMS_MAST_SIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Error while processing SitMsg ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_SIT415 Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg415 processed ( %1 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT510 Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg510 processed ( %1 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT_UNEXPECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Master : SitMsg %1 was unexpected ( File=%2 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT255 Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg255 processed ( %1 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT215 Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_CREATE_INSTANCE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Unable to create instance of %1 during startup.
.
MessageId=+1 SymbolicName=EMS_MAST_SYSTEM_STARTUP Severity=Success Facility=ITF
Language=English
EMS Master : Reports System Startup
.
MessageId=+1 SymbolicName=EMS_MAST_STATUS_AOS Severity=Success Facility=ITF
Language=English
%1
.
MessageId=+1 SymbolicName=EMS_MAST_STATUS_LOS Severity=Success Facility=ITF
Language=English
%1,EMS Master Status
.
MessageId=+1 SymbolicName=EMS_MAST_NO_SYSTEST_TIME Severity=Success Facility=ITF
Language=English
EMS Master reports insufficient time for system test.
.
MessageId=+1 SymbolicName=EMS_MAST_NEW_ORBIT_VECTOR Severity=Success Facility=ITF
Language=English
EMS Master installed new orbit vectors for %1.
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_ORBIT_VECTOR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports orbit vectors error for %1.
.
MessageId=+1 SymbolicName=EMS_MAST_SIT_MSG_RECV Severity=Success Facility=ITF
Language=English
EMS Master received SitMsg %1.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_IN_PROGRESS Severity=Success Facility=ITF
Language=English
EMS Master is currently processing a pass.
.
MessageId=+1 SymbolicName=EMS_MAST_RESTARTING Severity=Success Facility=ITF
Language=English
EMS Master was instructed to perform a WARM restart. 
.
MessageId=+1 SymbolicName=EMS_MAST_REBOOT Severity=Success Facility=ITF
Language=English
EMS Master was instructed to perform a COLD restart. 
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_INVALID_ORBIT Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors for %1.
.
MessageId=+1 SymbolicName=EMS_MAST_SIT255_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors when processing SitMsg255 ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_SET_CONFIG Severity=Success Facility=ITF
Language=English
EMS Master reports config change (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_SIT750A_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports syntax error processing SIT 750A ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_AUDIO_NOT_AVAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Master unable to retrieve requested audio data ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_SIT750A_INVALID_OPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid option in SIT 750A ( %1 ).
.
MessageId=+1 SymbolicName=EMS_MAST_GENERATED_PASS_SCHED Severity=Success Facility=ITF
Language=English
EMS Master generated a new pass schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_GENERATED_PASS_SCHED_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports error ( %1 ) while generating a new pass schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_INSTALLED_PASS_SCHED Severity=Success Facility=ITF
Language=English
EMS Master installed a new pass schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_DISK_PASS_SCHED Severity=Success Facility=ITF
Language=English
EMS Master installed last saved pass schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_SITMSG_PASS_SCHED Severity=Success Facility=ITF
Language=English
EMS Master received a new pass schedule.
.
MessageId=+1 SymbolicName=EMS_MAST_VALIDATE_PASS_SCHED Severity=Success Facility=ITF
Language=English
EMS Master received a pass schedule to validate.
.
MessageId=+1 SymbolicName=EMS_MAST_SCHED_VALIDATED Severity=Success Facility=ITF
Language=English
EMS Master validated received pass schedule (VALI).
.
MessageId=+1 SymbolicName=EMS_MAST_SCHED_INVALID Severity=Success Facility=ITF
Language=English
EMS Master reports no valid entries in received pass schedule (VALI).
.
MessageId=+1 SymbolicName=EMS_MAST_SCHED_INFO Severity=Success Facility=ITF
Language=English
EMS Master received a pass schedule for information only.
.
MessageId=+1 SymbolicName=EMS_MAST_SCHED_BAD_OPTION Severity=Success Facility=ITF
Language=English
EMS Master received a pass schedule with an unrecognised install option.
.
MessageId=+1 SymbolicName=EMS_MAST_BAD_ORBIT_OPTION Severity=Success Facility=ITF
Language=English
EMS Master encountered invalid MF605 while processing orbit vector.
.
MessageId=+1 SymbolicName=EMS_MAST_SYSTEST_MISSING_SERVICE Severity=ErrWarn Facility=ITF
Language=English
EMS Master timed out waiting for the Antenna or SysTest Service.
.
MessageId=+1 SymbolicName=EMS_MAST_PENDING_SCHEDULE Severity=Success Facility=ITF
Language=English
EMS Master reports pending schedule, waiting for end of pass.
.
MessageId=+1 SymbolicName=EMS_ORBIT_NUMBER_NOT_MATCH Severity=Success Facility=ITF
Language=English
EMS Master reports one or more passes in the supplied schedule had different orbit number.
.
MessageId=+1 SymbolicName=EMS_MAST_FORCED_ENDOFPASS Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports handling forced end of pass.
.
MessageId=+1 SymbolicName=EMS_MAST_INITIAL_PROCESS_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Master timed out waiting for the core services to start.
.
MessageId=+1 SymbolicName=EMS_MAST_SYSTEST_TIME_CONFLICT Severity=Success Facility=ITF
Language=English
EMS Master skipping system test due to insufficient time or pass conflict.
.
MessageId=+1 SymbolicName=EMS_MAST_COMMAND_NOT_SUPPORTED Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports receiving a command that is not handled.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_SCHED_CANT_INSTALL Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports an error installing the pass schedule.  A pass in progress.
.
MessageId=+1 SymbolicName=EMS_MAST_CREATE_INSTANCE_ERR_HR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Unable to create instance of %1 during startup (Error=%2).
.
MessageId=+1 SymbolicName=EMS_MASTER_TRACE_PASSSCHEDSETTINGS Severity=Success Facility=ITF
Language=English
EMS Master tracer ( PassSchedSettings: PrePass=%1, Tol=%2, Flags=%3 )
.
MessageId=+1 SymbolicName=EMS_MAST_SITEINFO_ERR_HR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Reports error %2 while trying to retrieve site information %1.
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_INVALID_SATORBIT Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors for sat=%1.
.
MessageId=+1 SymbolicName=EMS_MASTER_TRACE_NOACK Severity=Success Facility=ITF
Language=English
EMS Master tracer ( No ACK: Msg(%1) hr(%2) )
.
MessageId=+1 SymbolicName=EMS_MASTER_TRACE_NORESPONSE Severity=Success Facility=ITF
Language=English
EMS Master tracer ( No Response: Msg(%1) hr(%2) )
.
MessageId=+1 SymbolicName=EMS_MASTER_TRACE_NOLOG Severity=Success Facility=ITF
Language=English
EMS Master tracer ( No Log: Msg(%1) hr(%2) )
.
MessageId=+1 SymbolicName=EMS_MAST_SIT255_MSG Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg255 processed ( Message=%1 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT255_ERR_MSG Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1 ).  
.
MessageId=+1 SymbolicName=EMS_MAST_SIT415_DETAILS Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg415 processed ( Sat=%1  Freq=%2 Time=%3 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_SIT510_DETAILS Severity=Success Facility=ITF
Language=English
EMS Master : SitMsg510 processed ( Sat=%1 FreqOffset=%2 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_TIME_ZONE Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports system clock not set to UTC, daylight savings OFF (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR Severity=Success Facility=ITF
Language=English
EMS Master installed new orbit vectors[satID=%1, source=%2, dTimeDiff=%3, b%4Hours=%5, bValid=%6, dPosErr=%7:dVelErr=%8, bPosVelBelowThresholds=%9, bInstallNewTLE=%10] 
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports orbit vectors error[satID=%1, source=%2, dTimeDiff=%3, b%4Hours=%5, bValid=%6, dPosErr=%7:dVelErr=%8, bPosVelBelowThresholds=%9, bInstallNewTLE=%10]  
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_INVALID_ORBIT_SAT Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors for Sat=%1.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_SCHED_FILE_EMPTY Severity=Success Facility=ITF
Language=English
EMS Master reports finding the Pass Schedule file, but it contains no passes.
.
MessageId=+1 SymbolicName=EMS_MAST_STOPPING_DB Severity=Success Facility=ITF
Language=English
EMS Master is stopping the database.
.
MessageId=+1 SymbolicName=EMS_MAST_FAILED_TO_START_DB Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Failed to start the database (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_FAILED_TO_STOP_DB Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Failed to stop the database (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_SCHED_REJECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Supplied pass schedule was rejected as invalid.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT Severity=ErrWarn Facility=ITF
Language=English
EMS Master: The orbit data for satellite %1 may be corrupted. Pass schedule validation found %2 passes for this satellite that do not match the LUT predicted times.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_OUTSIDE_TOLERANCE Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports one or more passes in the supplied schedule were suppressed. Given AOS/LOS times did not match LUT predictions.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_TOO_OLD Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports one or more passes in the supplied schedule were suppressed. AOS/LOS times were too old.
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_ERROR_DURING_VALIDATION Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports pass suppressed because of error detected during validation (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_PASS_SCHED_NO_VALID_PASSES Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Pass schedule rejected. There were no unsupressed passes to be processed by this LUT.
.
MessageId=+1 SymbolicName=EMS_MAST_SARP_CALIBRATIONTIME_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Invalid sarp calibration data.  Difference between new and old calibration times exceeds configured maximum.
.
MessageId=+1 SymbolicName=EMS_MAST_SARP_REFFREQUENCY_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Invalid sarp calibration data.  Difference between new and old reference frequencies exceed configured maximum.
.
MessageId=+1 SymbolicName=EMS_MAST_SARP_REFFREQUENCY_CALIBRATIONTIME_INVALID Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Invalid sarp calibration data.  Differences between old and new values for calibration time and reference frequency both exceed configured maximums.
.
MessageId=+1 SymbolicName=EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR Severity=Success Facility=ITF
Language=English
EMS Master installed post manoeuvre orbit vectors [satID=%1, source=%2, dTimeDiff=%3, b%4Hours=%5, bValid=%6, dPosErr=%7:dVelErr=%8, bPosVelBelowThresholds=%9, bInstallNewTLE=%10] 
.
MessageId=+1 SymbolicName=EMS_MAST_OUTDATED_VECTORS Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports that installed orbit vectors for Sat %1 were installed %2 days ago and may now be out of date.
.
MessageId=+1 SymbolicName=EMS_MAST_OUTDATED_TCAL Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports that TCAL data for Sat %1 was installed %2 days ago and may now be out of date.
.
MessageId=+1 SymbolicName=EMS_MAST_ORBIT_PROBLEM Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports Orbit Error %1 for Sat %2.
.
MessageId=+1 SymbolicName=EMS_MAST_SIT_SARPCALIB_DETAILS Severity=Success Facility=ITF
Language=English
EMS Master : Sarp Calibration (SitMsg%1) received ( Sat=%2  Freq=%3 Time=%4 ). 
.
MessageId=+1 SymbolicName=EMS_MAST_GPSCLOCK_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Master : Failed to communicate with GPS clock (%1).
.
MessageId=+1 SymbolicName=EMS_MAST_SIT255_ERR_MSG2 Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1, Error=%2 ).
.
MessageId=+1 SymbolicName=EMS_MAST_ERR_SAT_NO_ORBIT_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Master reports no orbit data available for satellite <%1>.
.
MessageId=+1 SymbolicName=EMS_MAST_RESTARTING_FP Severity=Success Facility=ITF
Language=English
EMS Master sending a restart command to the FP.
.
MessageId=+1 SymbolicName=EMS_MAST_REBOOTING_FP Severity=Success Facility=ITF
Language=English
EMS Master sending a reboot command to the FP.
.
MessageId=+1 SymbolicName=EMS_MAST_EXCEPTION_SENDING_FP_RESTART Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Exception while sending a restart command to the FP.
.
MessageId=+1 SymbolicName=EMS_MAST_EXCEPTION_SENDING_FP_REBOOT Severity=ErrWarn Facility=ITF
Language=English
EMS Master: Exception while sending a reboot command to the FP.
.
;
;#endif // INC_MASTMSGS

