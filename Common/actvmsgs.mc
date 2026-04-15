;/********************************************************************
;*	Module:			ActvMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Geo Active Beacon Service
;*				Errors & Messages
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
;#ifndef INC_ACTVMSGS
;#define INC_ACTVMSGS
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

MessageId=0xAA00 SymbolicName=EMS_ACTVBCN_BASE_CODE Facility=ITF
Language=English
EMS ActiveBeacon 
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Started
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Stopped
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_PROCESSING_START Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service starting to process %1 records
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_PROCESSING_STOP Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service finished processing. %1 location records output.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_TRACER Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon received command( %1 ).
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_PROC_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon returns error %1 from _DetermineLocations.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_DETERMINE_LOCATION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon reports result %1 from _DetermineLocation.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BAD_DATA_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon reports error %1 trying to access data directory.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BAD_BCH Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon reports BCH failure for Beacon %1.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_TRACE_CONFIG Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Tracer ( cfg: %1=%2 )
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_TRACE_CONFIGYES Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Tracer ( cfg: %1=yes )
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_TRACE_CONFIGNO Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service Tracer ( cfg: %1=no )
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_IGNORED_INVERTEDFS Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (inverted frame sync)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_IGNORED_INVALIDFS Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (invalid frame sync)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_IGNORED_SERVICENOTPROCESSING Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not processed.  The Active Beacon Service is in the %2 state and can not accept new data.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_INIT_MAXBEACONS Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: Initialized with MaxBeacons=%1
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_INIT_AGEOUT Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BEACON_AGEOUT Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: Data aged out for Beacon (%1). Age=%2 minutes, #Records=%3
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BEACON_REPLACED_NOALERT Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Beacon %1 (@%2) was replaced prior to Alert. #Active Beacons=%3
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BEACON_REPLACED Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service:  Beacon %1 (@%2) was replaced by Beacon %4. #Active Beacons=%3
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BEACON_ADD_FAILED_BIN Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1 (@%2). #Active Beacons=%3, Error=%4
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BEACON_ADD_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1. #Active Beacons=%2
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_BLIST_AGEOUT Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: Beacon List age out of Beacon %1. Type=%2, Age=%3 minutes, #Active Beacons=%4
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_INIT_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Failed to initialize ABL Object (hr = %1)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_LOAD_CONFIG_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during loading the ABS configurations (hr = %1)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_FAILED_TO_WRITE_TO_PIPELINE Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during writing a location record to the pipeline (beacon id = %1, hr = %2)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_FAILED_TO_SENDNOW_LOCATE Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during sending a location record via gateway (beacon id = %1, hr = %2)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_GETLOCATIONS_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during getting location records from the ABL (hr = %1)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_GETBCNLOCATION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during getting a beacons location record from the ABL (beacon id = %1, hr = %2)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_PUTBCNDATA_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: An error occurred during adding a beacons location record to the ABL (beacon id = %1, hr = %2)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_STOPPED_IGNORING_INPUT_RECS Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Calib406 record for beacon (%1) has not been processed. The Active Beacon Service is in the "Idle" state and cannot accept new data.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_NO_SUPPORT_FOR_CONFIG_ITEM Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Wrong ABS configuration item - "%1" is configured to '%2'. This value is not supported in this release. The supported value will be used.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_FAILED_TOGET_CONFIG_ITEM Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Failed to get configuration item - %1 (of '%2' group, hr = %3). Check the configuration files.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_CONFIG_ITEM_VALUE Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: The ABS configuration item - "%1" is configured to '%2'.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_LA_WARN Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_LA_ALARM Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_LA_OK Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is back to normal (actual=%2, expected <=%3).
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_ABL_MAX_CAP Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Reached the maximum configured number of raw input records. (Max=%1); this might limit the list of active beacons data.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_INIT_AGEOUT_UPDFREQ Severity=Success Facility=ITF
Language=English
EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4), QMS(%5)
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_OUTPUT_DETECTION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Failed outputting beacon detection to MTL.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_ACTVBCN_NO_MTL_CLIENT Severity=ErrWarn Facility=ITF
Language=English
EMS ActiveBeacon Service: Failed outputting beacon detection to MTL.  No reference available to MTL Client.
.
;
;#endif // INC_ACTVMSGS
