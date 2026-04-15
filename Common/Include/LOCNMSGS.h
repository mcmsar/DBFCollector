/********************************************************************
*	Module:			LocnMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Location Processor 
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
#ifndef INC_LOCNMSGS
#define INC_LOCNMSGS

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
// MessageId: EMS_LOCN_BASE_CODE
//
// MessageText:
//
// EMS Location 
//
#define EMS_LOCN_BASE_CODE               ((EMS_RESULT)0x0004A500L)

//
// MessageId: EMS_LOCN_SERVICE_START
//
// MessageText:
//
// EMS Location Service Started
//
#define EMS_LOCN_SERVICE_START           ((EMS_RESULT)0x0004A501L)

//
// MessageId: EMS_LOCN_SERVICE_STOP
//
// MessageText:
//
// EMS Location Service Stopped
//
#define EMS_LOCN_SERVICE_STOP            ((EMS_RESULT)0x0004A502L)

//
// MessageId: EMS_LOCN_SERVICE_FAILED
//
// MessageText:
//
// EMS Location Service did not start due to error %1
//
#define EMS_LOCN_SERVICE_FAILED          ((EMS_RESULT)0x8004A503L)

//
// MessageId: EMS_LOCN_PROCESSING_START
//
// MessageText:
//
// EMS Location Service starting to process %1 records
//
#define EMS_LOCN_PROCESSING_START        ((EMS_RESULT)0x0004A504L)

//
// MessageId: EMS_LOCN_PROCESSING_STOP
//
// MessageText:
//
// EMS Location Service finished processing. %1 location records output.
//
#define EMS_LOCN_PROCESSING_STOP         ((EMS_RESULT)0x0004A505L)

//
// MessageId: EMS_LOCN_TRACER
//
// MessageText:
//
// EMS Location Service Tracer ( %1 )
//
#define EMS_LOCN_TRACER                  ((EMS_RESULT)0x0004A506L)

//
// MessageId: EMS_LOCN_RECV_COMMAND
//
// MessageText:
//
// EMS Location received command( %1 ).
//
#define EMS_LOCN_RECV_COMMAND            ((EMS_RESULT)0x0004A507L)

//
// MessageId: EMS_LOCN_PROC_ERROR
//
// MessageText:
//
// EMS Location returns error %1 from _DetermineLocations.
//
#define EMS_LOCN_PROC_ERROR              ((EMS_RESULT)0x8004A508L)

//
// MessageId: EMS_LOCN_DETERMINE_LOCATION_ERROR
//
// MessageText:
//
// EMS Location reports result %1 from _DetermineLocation.
//
#define EMS_LOCN_DETERMINE_LOCATION_ERROR ((EMS_RESULT)0x8004A509L)

//
// MessageId: EMS_LOCN_BAD_DATA_DIR
//
// MessageText:
//
// EMS Location reports error %1 trying to access data directory.
//
#define EMS_LOCN_BAD_DATA_DIR            ((EMS_RESULT)0x8004A50AL)

//
// MessageId: EMS_LOCN_BAD_BCH
//
// MessageText:
//
// EMS Location reports BCH failure for Beacon %1.
//
#define EMS_LOCN_BAD_BCH                 ((EMS_RESULT)0x8004A50BL)

//
// MessageId: EMS_TLE_SERV_RETRIEVE_FAIL_RETRYING
//
// MessageText:
//
// EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Retrying.
//
#define EMS_TLE_SERV_RETRIEVE_FAIL_RETRYING ((EMS_RESULT)0x0004A50CL)

//
// MessageId: EMS_TLE_SERV_RETRIEVE_FAIL_NORETRY
//
// MessageText:
//
// EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Maximum number of retries has been reached.
//
#define EMS_TLE_SERV_RETRIEVE_FAIL_NORETRY ((EMS_RESULT)0x8004A50DL)

//
// MessageId: EMS_LOCN_INSUFF_POINTS
//
// MessageText:
//
// EMS Location reports insufficient points for processing.
//
#define EMS_LOCN_INSUFF_POINTS           ((EMS_RESULT)0x8004A50EL)

//
// MessageId: EMS_LOCN_TRACER_DOIDLE
//
// MessageText:
//
// EMS Location Service Tracer ( Catch in DoIdle )
//
#define EMS_LOCN_TRACER_DOIDLE           ((EMS_RESULT)0x0004A50FL)

//
// MessageId: EMS_LOCN_TRACER_TCACONSTRAINED
//
// MessageText:
//
// EMS Location Service Tracer ( ** TCA was constrained to %1 seconds )
//
#define EMS_LOCN_TRACER_TCACONSTRAINED   ((EMS_RESULT)0x0004A510L)

//
// MessageId: EMS_LOCN_TRACER_EMPTYFILE
//
// MessageText:
//
// EMS Location Service Tracer ( File %1 has no data )
//
#define EMS_LOCN_TRACER_EMPTYFILE        ((EMS_RESULT)0x0004A511L)

//
// MessageId: EMS_LOCN_TRACER_FILECOUNT
//
// MessageText:
//
// EMS Location Service Tracer ( %1 recs in File %2 )
//
#define EMS_LOCN_TRACER_FILECOUNT        ((EMS_RESULT)0x0004A512L)

//
// MessageId: EMS_LOCN_TRACER_EXECTIME
//
// MessageText:
//
// EMS Location Service Tracer ( Execution time = %1 secs, dbHist %2 - %3 )
//
#define EMS_LOCN_TRACER_EXECTIME         ((EMS_RESULT)0x0004A513L)

//
// MessageId: EMS_LOCN_LEOCALIBREG_ERROR
//
// MessageText:
//
// Unable to register LEO_CALIBRATE_406_DATA sink
//
#define EMS_LOCN_LEOCALIBREG_ERROR       ((EMS_RESULT)0x8004A514L)

//
// MessageId: EMS_LOCN_LEOCOMBREG_ERROR
//
// MessageText:
//
// Unable to register LEO_COMBINE_406_DATA sink
//
#define EMS_LOCN_LEOCOMBREG_ERROR        ((EMS_RESULT)0x8004A515L)

//
// MessageId: EMS_LOCN_TRACER_CBCCONFIGSAT
//
// MessageText:
//
// EMS Location Service Tracer ( LocateCBC config: SatId  %1, DetMin %2, AmpMin %3, AmpMax %4, ItrMax %5, Thresh %6, CorMax %7, Drift %8, MaxNoise %9, MinPtsVisible %10 )
//
#define EMS_LOCN_TRACER_CBCCONFIGSAT     ((EMS_RESULT)0x0004A516L)

//
// MessageId: EMS_LOCN_TRACER_CBCCONFIGEE
//
// MessageText:
//
// EMS Location Service Tracer ( LocateCBC config: EEFact %1, EEAdj  %2, SwpThr %3, SwpPts %4 )
//
#define EMS_LOCN_TRACER_CBCCONFIGEE      ((EMS_RESULT)0x0004A517L)

//
// MessageId: EMS_LOCN_TRACER_406CONFIGSAT
//
// MessageText:
//
// EMS Location Service Tracer ( Locate406 config:  SatId  %1, ItrMax %2, Thresh %3, CorMax %4, Drift  %5, Altit  %6, MaxNoise %7, MinPtsVisible %8 )
//
#define EMS_LOCN_TRACER_406CONFIGSAT     ((EMS_RESULT)0x0004A518L)

//
// MessageId: EMS_LOCN_TRACER_406CONFIGEE
//
// MessageText:
//
// EMS Location Service Tracer ( Locate406 config:  EEFact %1, EEAdj  %2 )
//
#define EMS_LOCN_TRACER_406CONFIGEE      ((EMS_RESULT)0x0004A519L)

//
// MessageId: EMS_LOCN_PROCESSING_START_COUNT
//
// MessageText:
//
// EMS Location Service starting to process %1 (%2 CBC, %3 406, %4 Combine) records
//
#define EMS_LOCN_PROCESSING_START_COUNT  ((EMS_RESULT)0x0004A51AL)

//
// MessageId: EMS_LOCN_ACCURACY_CHECK_FAILURE
//
// MessageText:
//
// EMS Location Service reports that the calculated position for reference beacon %1 is %2 km different from expected (lat:%3 lon: %4).
//
#define EMS_LOCN_ACCURACY_CHECK_FAILURE  ((EMS_RESULT)0x8004A51BL)

//
// MessageId: EMS_TLE_SERV_NUM_CACHED
//
// MessageText:
//
// EMS TLE Server reports %1 orbit vectors currently stored in the cache.
//
#define EMS_TLE_SERV_NUM_CACHED          ((EMS_RESULT)0x0004A51CL)

//
// MessageId: EMS_TLE_SERV_CACHE_LIMIT_REACHED
//
// MessageText:
//
// EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached.  Oldest record in the cache will be overwritten.  
//
#define EMS_TLE_SERV_CACHE_LIMIT_REACHED ((EMS_RESULT)0x8004A51DL)

//
// MessageId: EMS_TLE_SERV_CACHE_INPUT_STOPPED
//
// MessageText:
//
// EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached while loading from the database.  No more database records shall be added.
//
#define EMS_TLE_SERV_CACHE_INPUT_STOPPED ((EMS_RESULT)0x0004A51EL)

//
// MessageId: EMS_LOCN_UNINITIALIZED
//
// MessageText:
//
// EMS Location Service cannot process a request because it has not been initialized.
//
#define EMS_LOCN_UNINITIALIZED           ((EMS_RESULT)0x8004A51FL)

//
// MessageId: EMS_LOCN_NUMBER_INVALID_RECORDS
//
// MessageText:
//
// EMS Location Service reports %1 invalid input records.
//
#define EMS_LOCN_NUMBER_INVALID_RECORDS  ((EMS_RESULT)0x0004A520L)

//
// MessageId: EMS_LOCN_CMD_UNRECOGNIZED
//
// MessageText:
//
// EMS Location Service reports that an unrecognized command (%1) was received.  The command will be ignored.
//
#define EMS_LOCN_CMD_UNRECOGNIZED        ((EMS_RESULT)0x8004A521L)

//
// MessageId: EMS_LOCN_CMD_RESETDB
//
// MessageText:
//
// EMS Location Service reports that a command was received to clear the TOA/FOA measurement cache.
//
#define EMS_LOCN_CMD_RESETDB             ((EMS_RESULT)0x0004A522L)

//
// MessageId: EMS_LOCN_CMD_BURST_STORE_TIME
//
// MessageText:
//
// EMS Location Service reports that a command was received to set the TOA/FOA measurement store time to %1 minutes.
//
#define EMS_LOCN_CMD_BURST_STORE_TIME    ((EMS_RESULT)0x0004A523L)

//
// MessageId: EMS_LOCN_CMD_EXCEPTION
//
// MessageText:
//
// EMS Location Service reports that an exception report was received from the command message handler:  %1.
//
#define EMS_LOCN_CMD_EXCEPTION           ((EMS_RESULT)0x0004A524L)

//
// MessageId: EMS_LOCN_CMD_NOT_CONNECTED
//
// MessageText:
//
// EMS Location Service reports that it could not connect to the Message Queue for receipt of command messages.  Processing will continue, but commands will not be received.
//
#define EMS_LOCN_CMD_NOT_CONNECTED       ((EMS_RESULT)0x0004A525L)


#endif // INC_LOCNMSGS
