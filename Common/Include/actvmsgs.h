/********************************************************************
*	Module:			ActvMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Geo Active Beacon Service
*				Errors & Messages
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
#ifndef INC_ACTVMSGS
#define INC_ACTVMSGS

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
// MessageId: EMS_ACTVBCN_BASE_CODE
//
// MessageText:
//
//  EMS ActiveBeacon 
//
#define EMS_ACTVBCN_BASE_CODE            ((EMS_RESULT)0x0004AA00L)

//
// MessageId: EMS_ACTVBCN_SERVICE_START
//
// MessageText:
//
//  EMS ActiveBeacon Service Started
//
#define EMS_ACTVBCN_SERVICE_START        ((EMS_RESULT)0x0004AA01L)

//
// MessageId: EMS_ACTVBCN_SERVICE_STOP
//
// MessageText:
//
//  EMS ActiveBeacon Service Stopped
//
#define EMS_ACTVBCN_SERVICE_STOP         ((EMS_RESULT)0x0004AA02L)

//
// MessageId: EMS_ACTVBCN_SERVICE_FAILED
//
// MessageText:
//
//  EMS ActiveBeacon Service did not start due to error %1
//
#define EMS_ACTVBCN_SERVICE_FAILED       ((EMS_RESULT)0x8004AA03L)

//
// MessageId: EMS_ACTVBCN_PROCESSING_START
//
// MessageText:
//
//  EMS ActiveBeacon Service starting to process %1 records
//
#define EMS_ACTVBCN_PROCESSING_START     ((EMS_RESULT)0x0004AA04L)

//
// MessageId: EMS_ACTVBCN_PROCESSING_STOP
//
// MessageText:
//
//  EMS ActiveBeacon Service finished processing. %1 location records output.
//
#define EMS_ACTVBCN_PROCESSING_STOP      ((EMS_RESULT)0x0004AA05L)

//
// MessageId: EMS_ACTVBCN_TRACER
//
// MessageText:
//
//  EMS ActiveBeacon Service Tracer ( %1 )
//
#define EMS_ACTVBCN_TRACER               ((EMS_RESULT)0x0004AA06L)

//
// MessageId: EMS_ACTVBCN_RECV_COMMAND
//
// MessageText:
//
//  EMS ActiveBeacon received command( %1 ).
//
#define EMS_ACTVBCN_RECV_COMMAND         ((EMS_RESULT)0x0004AA07L)

//
// MessageId: EMS_ACTVBCN_PROC_ERROR
//
// MessageText:
//
//  EMS ActiveBeacon returns error %1 from _DetermineLocations.
//
#define EMS_ACTVBCN_PROC_ERROR           ((EMS_RESULT)0x8004AA08L)

//
// MessageId: EMS_ACTVBCN_DETERMINE_LOCATION_ERROR
//
// MessageText:
//
//  EMS ActiveBeacon reports result %1 from _DetermineLocation.
//
#define EMS_ACTVBCN_DETERMINE_LOCATION_ERROR ((EMS_RESULT)0x8004AA09L)

//
// MessageId: EMS_ACTVBCN_BAD_DATA_DIR
//
// MessageText:
//
//  EMS ActiveBeacon reports error %1 trying to access data directory.
//
#define EMS_ACTVBCN_BAD_DATA_DIR         ((EMS_RESULT)0x8004AA0AL)

//
// MessageId: EMS_ACTVBCN_BAD_BCH
//
// MessageText:
//
//  EMS ActiveBeacon reports BCH failure for Beacon %1.
//
#define EMS_ACTVBCN_BAD_BCH              ((EMS_RESULT)0x8004AA0BL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIG
//
// MessageText:
//
//  EMS ActiveBeacon Service Tracer ( cfg: %1=%2 )
//
#define EMS_ACTVBCN_TRACE_CONFIG         ((EMS_RESULT)0x0004AA0CL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIGYES
//
// MessageText:
//
//  EMS ActiveBeacon Service Tracer ( cfg: %1=yes )
//
#define EMS_ACTVBCN_TRACE_CONFIGYES      ((EMS_RESULT)0x0004AA0DL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIGNO
//
// MessageText:
//
//  EMS ActiveBeacon Service Tracer ( cfg: %1=no )
//
#define EMS_ACTVBCN_TRACE_CONFIGNO       ((EMS_RESULT)0x0004AA0EL)

//
// MessageId: EMS_ACTVBCN_IGNORED_INVERTEDFS
//
// MessageText:
//
//  EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (inverted frame sync)
//
#define EMS_ACTVBCN_IGNORED_INVERTEDFS   ((EMS_RESULT)0x0004AA0FL)

//
// MessageId: EMS_ACTVBCN_IGNORED_INVALIDFS
//
// MessageText:
//
//  EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (invalid frame sync)
//
#define EMS_ACTVBCN_IGNORED_INVALIDFS    ((EMS_RESULT)0x0004AA10L)

//
// MessageId: EMS_ACTVBCN_IGNORED_SERVICENOTPROCESSING
//
// MessageText:
//
//  EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not processed.  The Active Beacon Service is in the %2 state and can not accept new data.
//
#define EMS_ACTVBCN_IGNORED_SERVICENOTPROCESSING ((EMS_RESULT)0x0004AA11L)

//
// MessageId: EMS_ACTVBCN_INIT_MAXBEACONS
//
// MessageText:
//
//  EMS ActiveBeacon Service: Initialized with MaxBeacons=%1
//
#define EMS_ACTVBCN_INIT_MAXBEACONS      ((EMS_RESULT)0x0004AA12L)

//
// MessageId: EMS_ACTVBCN_INIT_AGEOUT
//
// MessageText:
//
//  EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4)
//
#define EMS_ACTVBCN_INIT_AGEOUT          ((EMS_RESULT)0x0004AA13L)

//
// MessageId: EMS_ACTVBCN_BEACON_AGEOUT
//
// MessageText:
//
//  EMS ActiveBeacon Service: Data aged out for Beacon (%1). Age=%2 minutes, #Records=%3
//
#define EMS_ACTVBCN_BEACON_AGEOUT        ((EMS_RESULT)0x0004AA14L)

//
// MessageId: EMS_ACTVBCN_BEACON_REPLACED_NOALERT
//
// MessageText:
//
//  EMS ActiveBeacon Service: Beacon %1 (@%2) was replaced prior to Alert. #Active Beacons=%3
//
#define EMS_ACTVBCN_BEACON_REPLACED_NOALERT ((EMS_RESULT)0x8004AA15L)

//
// MessageId: EMS_ACTVBCN_BEACON_REPLACED
//
// MessageText:
//
//  EMS ActiveBeacon Service:  Beacon %1 (@%2) was replaced by Beacon %4. #Active Beacons=%3
//
#define EMS_ACTVBCN_BEACON_REPLACED      ((EMS_RESULT)0x0004AA16L)

//
// MessageId: EMS_ACTVBCN_BEACON_ADD_FAILED_BIN
//
// MessageText:
//
//  EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1 (@%2). #Active Beacons=%3, Error=%4
//
#define EMS_ACTVBCN_BEACON_ADD_FAILED_BIN ((EMS_RESULT)0x8004AA17L)

//
// MessageId: EMS_ACTVBCN_BEACON_ADD_FAILED
//
// MessageText:
//
//  EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1. #Active Beacons=%2
//
#define EMS_ACTVBCN_BEACON_ADD_FAILED    ((EMS_RESULT)0x8004AA18L)

//
// MessageId: EMS_ACTVBCN_BLIST_AGEOUT
//
// MessageText:
//
//  EMS ActiveBeacon Service: Beacon List age out of Beacon %1. Type=%2, Age=%3 minutes, #Active Beacons=%4
//
#define EMS_ACTVBCN_BLIST_AGEOUT         ((EMS_RESULT)0x0004AA19L)

//
// MessageId: EMS_ACTVBCN_ABL_INIT_FAIL
//
// MessageText:
//
//  EMS ActiveBeacon Service: Failed to initialize ABL Object (hr = %1)
//
#define EMS_ACTVBCN_ABL_INIT_FAIL        ((EMS_RESULT)0x8004AA1AL)

//
// MessageId: EMS_ACTVBCN_LOAD_CONFIG_FAIL
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during loading the ABS configurations (hr = %1)
//
#define EMS_ACTVBCN_LOAD_CONFIG_FAIL     ((EMS_RESULT)0x8004AA1BL)

//
// MessageId: EMS_ACTVBCN_FAILED_TO_WRITE_TO_PIPELINE
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during writing a location record to the pipeline (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_FAILED_TO_WRITE_TO_PIPELINE ((EMS_RESULT)0x8004AA1CL)

//
// MessageId: EMS_ACTVBCN_FAILED_TO_SENDNOW_LOCATE
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during sending a location record via gateway (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_FAILED_TO_SENDNOW_LOCATE ((EMS_RESULT)0x8004AA1DL)

//
// MessageId: EMS_ACTVBCN_ABL_GETLOCATIONS_FAILED
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during getting location records from the ABL (hr = %1)
//
#define EMS_ACTVBCN_ABL_GETLOCATIONS_FAILED ((EMS_RESULT)0x8004AA1EL)

//
// MessageId: EMS_ACTVBCN_ABL_GETBCNLOCATION_FAILED
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during getting a beacons location record from the ABL (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_ABL_GETBCNLOCATION_FAILED ((EMS_RESULT)0x8004AA1FL)

//
// MessageId: EMS_ACTVBCN_ABL_PUTBCNDATA_FAILED
//
// MessageText:
//
//  EMS ActiveBeacon Service: An error occurred during adding a beacons location record to the ABL (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_ABL_PUTBCNDATA_FAILED ((EMS_RESULT)0x8004AA20L)

//
// MessageId: EMS_ACTVBCN_STOPPED_IGNORING_INPUT_RECS
//
// MessageText:
//
//  EMS ActiveBeacon Service: Calib406 record for beacon (%1) has not been processed. The Active Beacon Service is in the "Idle" state and cannot accept new data.
//
#define EMS_ACTVBCN_STOPPED_IGNORING_INPUT_RECS ((EMS_RESULT)0x8004AA21L)

//
// MessageId: EMS_ACTVBCN_NO_SUPPORT_FOR_CONFIG_ITEM
//
// MessageText:
//
//  EMS ActiveBeacon Service: Wrong ABS configuration item - "%1" is configured to '%2'. This value is not supported in this release. The supported value will be used.
//
#define EMS_ACTVBCN_NO_SUPPORT_FOR_CONFIG_ITEM ((EMS_RESULT)0x8004AA22L)

//
// MessageId: EMS_ACTVBCN_FAILED_TOGET_CONFIG_ITEM
//
// MessageText:
//
//  EMS ActiveBeacon Service: Failed to get configuration item - %1 (of '%2' group, hr = %3). Check the configuration files.
//
#define EMS_ACTVBCN_FAILED_TOGET_CONFIG_ITEM ((EMS_RESULT)0x8004AA23L)

//
// MessageId: EMS_ACTVBCN_CONFIG_ITEM_VALUE
//
// MessageText:
//
//  EMS ActiveBeacon Service: The ABS configuration item - "%1" is configured to '%2'.
//
#define EMS_ACTVBCN_CONFIG_ITEM_VALUE    ((EMS_RESULT)0x0004AA24L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_WARN
//
// MessageText:
//
//  EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_WARN          ((EMS_RESULT)0x8004AA25L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_ALARM
//
// MessageText:
//
//  EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_ALARM         ((EMS_RESULT)0x8004AA26L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_OK
//
// MessageText:
//
//  EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is back to normal (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_OK            ((EMS_RESULT)0x0004AA27L)

//
// MessageId: EMS_ACTVBCN_ABL_MAX_CAP
//
// MessageText:
//
//  EMS ActiveBeacon Service: Reached the maximum configured number of raw input records. (Max=%1); this might limit the list of active beacons data.
//
#define EMS_ACTVBCN_ABL_MAX_CAP          ((EMS_RESULT)0x8004AA28L)

//
// MessageId: EMS_ACTVBCN_INIT_AGEOUT_UPDFREQ
//
// MessageText:
//
//  EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4), QMS(%5)
//
#define EMS_ACTVBCN_INIT_AGEOUT_UPDFREQ  ((EMS_RESULT)0x0004AA29L)


#endif // INC_ACTVMSGS
