;/********************************************************************
;*	Module:			Calib406Msg.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Calib406 Errors & Messages
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
;#ifndef INC_CALIB406MSG
;#define INC_CALIB406MSG
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

MessageId=0xA400 SymbolicName=EMS_CALIB406_BASE_CODE Facility=ITF
Language=English
EMS Calibrate406 Error
.
MessageId=+1 SymbolicName=EMS_CALIB406_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Started
.
MessageId=+1 SymbolicName=EMS_CALIB406_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_CALIB406_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Stopped
.
MessageId=+1 SymbolicName=EMS_CALIB406_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports error %1.
.
MessageId=+1 SymbolicName=EMS_CALIB406_PRIORITY_CLASS Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports error %1 when calling SetPriorityClass
.
MessageId=+1 SymbolicName=EMS_CALIB406_THREAD_PRIORITY Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports error %1 when calling SetThreadPriority
.
MessageId=+1 SymbolicName=EMS_CALIB406_IDEAL_PROCESSOR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports error %1 when calling SetThreadIdealProcessor
.
MessageId=+1 SymbolicName=EMS_CALIB406_START_PASS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reports initialized pass for satellite %1
.
MessageId=+1 SymbolicName=EMS_CALIB406_CALIBRATE_PASS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 starting to calibrate pass for satellite %1
.
MessageId=+1 SymbolicName=EMS_CALIB406_CALIBRATE_PASS_DONE Severity=Success Facility=ITF
Language=English
EMS Calibrate406 finished calibrating pass for satellite %1
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACER Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_HISTORY_RECS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 read %1 history records.
.
MessageId=+1 SymbolicName=EMS_CALIB406_BUFFER_ADD Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports an error adding record %1 to the buffer.
.
MessageId=+1 SymbolicName=EMS_CALIB406_NEW_SARR_OFFSETS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 : New SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
.
MessageId=+1 SymbolicName=EMS_CALIB406_CALC_SARR_OFFSETS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 : Insufficient Points for SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
.
MessageId=+1 SymbolicName=EMS_CALIB406_SARP_OFFSETS Severity=Success Facility=ITF
Language=English
EMS Calibrate406 has calculated new SARP Offsets ( SatID = %1, Freq=%2, Time=%3 ).
.
MessageId=+1 SymbolicName=EMS_CALIB406_ORBIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reported error %1 while trying to access IEMSOrbit.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SAT_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reported error %1 while trying to access IEMSSatInfo.
.
MessageId=+1 SymbolicName=EMS_CALIB406_LUT_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reported error %1 while trying to access IEMSLutInfo.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SITE_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reported error %1 while trying to access IEMSLeo600SiteInfo
.
MessageId=+1 SymbolicName=EMS_CALIB406_REF_BEACON_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reported error %1 while trying to access IEMSRefBeacon.
.
MessageId=+1 SymbolicName=EMS_CALIB406_HISTORY_OUT Severity=Success Facility=ITF
Language=English
EMS Calibrate406 wrote %1 history records.
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_CONFIG Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( cfg: %1=%2 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_CONFIGYES Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( cfg: %1=yes )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_CONFIGNO Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( cfg: %1=no )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_SORTEXCEPTION Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( EX: Left=%1 ,Right=%2, Split=%3, Max=%4, Depth=%5 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_SELNSORTEXCEPTION Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( EX (SelectionSort): Left=%1 ,Right=%2 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_PARTITION Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( Partition: Left=%1, Right=%2, Max=%3, *** )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_PARTITIONLTZERO Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( Partition: Left=%d, Right=%d, Max=%d, Split < ZERO )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_FORWARDINGCOUNT Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( Forwarding %1 records for Beacon %2 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_SARRSARPADDED Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( SarrSarpRecords Added=%1 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_BEFORELOCK Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( before lock )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_AFTERLOCK Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( after lock )
.
MessageId=+1 SymbolicName=EMS_CALIB406_TRACE_HISTORYREAD Severity=Success Facility=ITF
Language=English
EMS Calibrate406 Service Tracer ( SarrSarpHistory records read = %1 )
.
MessageId=+1 SymbolicName=EMS_CALIB406_ROLLOVER_PERIOD_GET_ERROR Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reported error retrieving rollover period from configuration.  The configuration manager returned error %1.
.
MessageId=+1 SymbolicName=EMS_CALIB406_ROLLOVER_PERIOD_ZERO_ERROR Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reported error retrieving rollover period.  The value is 0.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SAT_CAPS_GET_ERROR Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reported error retrieving satellite capabilities for satellite %1 from configuration  The configuration manager returned error %2.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SAT_PROCESSINFO_GET_ERROR Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reported error retrieving satellite processing information for satellite %1 from configuration  The configuration manager returned error %2.
.
MessageId=+1 SymbolicName=EMS_CALIB406_TCAL_BEACON_COUNT Severity=Success Facility=ITF
Language=English
Calibration will use %1 TCAL beacons to check SARR time accuracy.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SARR_TIME_ERROR Severity=ErrWarn Facility=ITF
Language=English
Calibration suggests that LutID(%1) AntennaID(%2) has a %3 second SARR time error.
.
MessageId=+1 SymbolicName=EMS_CALIB406_SARR_TIME_OKAY Severity=Success Facility=ITF
Language=English
Calibration confirms that LutID(%1) AntennaID(%2) has a valid SARR time.
.
MessageId=+1 SymbolicName=EMS_CALIB406_ORBIT_VECTOR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 cannot calculate an orbit vector for Satellite %1.
.
MessageId=+1 SymbolicName=EMS_CALIB406_BUFFER_ADD_EX Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports an error(0x%1) adding record(%2) SatID(%3) BeaconID(%4).
.
MessageId=+1 SymbolicName=EMS_CALIB406_DATA_SOURCE_PROBLEM Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports bad data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)).
.
MessageId=+1 SymbolicName=EMS_CALIB406_DATA_SOURCE_PROBLEM_CLEARED Severity=Success Facility=ITF
Language=English
EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)) is back to normal.
.
MessageId=+1 SymbolicName=EMS_CALIB406_TIME_SOURCE_PROBLEM Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), BeaconID(%4), MessageTime (%5)) error.
.
MessageId=+1 SymbolicName=EMS_CALIB406_STOP_COMBINE_SARR_SARP Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 reports a frequency shift exceeding the allowable tolerance of %1Hz for satellite %2.  Combined SARR/SARP location processing will be disabled for the current pass.
.
MessageId=+1 SymbolicName=EMS_CALIB406_LOW_NUMBER_SARP_RECORDS Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 produced low number of SARP records (%1) for satellite %2 passId %3.
.
MessageId=+1 SymbolicName=EMS_CALIB406_DATA_FILE_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS Calibrate406 cannot find the LSCalibData.xml file as specified in the registry (%1).
.
;
;#endif // INC_CALIB406MSG


