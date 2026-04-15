;/********************************************************************
;*	Module:			LocnMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Location Processor 
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
;#ifndef INC_LOCNMSGS
;#define INC_LOCNMSGS
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

MessageId=0xA500 SymbolicName=EMS_LOCN_BASE_CODE Facility=ITF
Language=English
EMS Location 
.
MessageId=+1 SymbolicName=EMS_LOCN_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Location Service Started
.
MessageId=+1 SymbolicName=EMS_LOCN_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Location Service Stopped
.
MessageId=+1 SymbolicName=EMS_LOCN_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Location Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_LOCN_PROCESSING_START Severity=Success Facility=ITF
Language=English
EMS Location Service starting to process %1 records
.
MessageId=+1 SymbolicName=EMS_LOCN_PROCESSING_STOP Severity=Success Facility=ITF
Language=English
EMS Location Service finished processing. %1 location records output.
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_LOCN_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Location received command( %1 ).
.
MessageId=+1 SymbolicName=EMS_LOCN_PROC_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Location returns error %1 from _DetermineLocations.
.
MessageId=+1 SymbolicName=EMS_LOCN_DETERMINE_LOCATION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Location reports result %1 from _DetermineLocation.
.
MessageId=+1 SymbolicName=EMS_LOCN_BAD_DATA_DIR Severity=ErrWarn Facility=ITF
Language=English
EMS Location reports error %1 trying to access data directory.
.
MessageId=+1 SymbolicName=EMS_LOCN_BAD_BCH Severity=ErrWarn Facility=ITF
Language=English
EMS Location reports BCH failure for Beacon %1.
.
MessageId=+1 SymbolicName=EMS_TLE_SERV_RETRIEVE_FAIL_RETRYING Severity=Success Facility=ITF
Language=English
EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Retrying.
.
MessageId=+1 SymbolicName=EMS_TLE_SERV_RETRIEVE_FAIL_NORETRY Severity=ErrWarn Facility=ITF
Language=English
EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Maximum number of retries has been reached.
.
MessageId=+1 SymbolicName=EMS_LOCN_INSUFF_POINTS Severity=ErrWarn Facility=ITF
Language=English
EMS Location reports insufficient points for processing.
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_DOIDLE Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( Catch in DoIdle )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_TCACONSTRAINED Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( ** TCA was constrained to %1 seconds )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_EMPTYFILE Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( File %1 has no data )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_FILECOUNT Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( %1 recs in File %2 )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_EXECTIME Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( Execution time = %1 secs, dbHist %2 - %3 )
.
MessageId=+1 SymbolicName=EMS_LOCN_LEOCALIBREG_ERROR Severity=ErrWarn Facility=ITF
Language=English
Unable to register LEO_CALIBRATE_406_DATA sink
.
MessageId=+1 SymbolicName=EMS_LOCN_LEOCOMBREG_ERROR Severity=ErrWarn Facility=ITF
Language=English
Unable to register LEO_COMBINE_406_DATA sink
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_CBCCONFIGSAT Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( LocateCBC config: SatId  %1, DetMin %2, AmpMin %3, AmpMax %4, ItrMax %5, Thresh %6, CorMax %7, Drift %8, MaxNoise %9, MinPtsVisible %10 )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_CBCCONFIGEE Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( LocateCBC config: EEFact %1, EEAdj  %2, SwpThr %3, SwpPts %4 )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_406CONFIGSAT Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( Locate406 config:  SatId  %1, ItrMax %2, Thresh %3, CorMax %4, Drift  %5, Altit  %6, MaxNoise %7, MinPtsVisible %8 )
.
MessageId=+1 SymbolicName=EMS_LOCN_TRACER_406CONFIGEE Severity=Success Facility=ITF
Language=English
EMS Location Service Tracer ( Locate406 config:  EEFact %1, EEAdj  %2 )
.
MessageId=+1 SymbolicName=EMS_LOCN_PROCESSING_START_COUNT Severity=Success Facility=ITF
Language=English
EMS Location Service starting to process %1 (%2 CBC, %3 406, %4 Combine) records
.
MessageId=+1 SymbolicName=EMS_LOCN_ACCURACY_CHECK_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Location Service reports that the calculated position for reference beacon %1 is %2 km different from expected (lat:%3 lon: %4).
.
MessageId=+1 SymbolicName=EMS_TLE_SERV_NUM_CACHED Severity=Success Facility=ITF
Language=English
EMS TLE Server reports %1 orbit vectors currently stored in the cache.
.
MessageId=+1 SymbolicName=EMS_TLE_SERV_CACHE_LIMIT_REACHED Severity=ErrWarn Facility=ITF
Language=English
EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached.  Oldest record in the cache will be overwritten.  
.
MessageId=+1 SymbolicName=EMS_TLE_SERV_CACHE_INPUT_STOPPED Severity=Success Facility=ITF
Language=English
EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached while loading from the database.  No more database records shall be added.
.
MessageId=+1 SymbolicName=EMS_LOCN_UNINITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Location Service cannot process a request because it has not been initialized.
.
MessageId=+1 SymbolicName=EMS_LOCN_NUMBER_INVALID_RECORDS Severity=Success Facility=ITF
Language=English
EMS Location Service reports %1 invalid input records.
.
MessageId=+1 SymbolicName=EMS_LOCN_CMD_UNRECOGNIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Location Service reports that an unrecognized command (%1) was received.  The command will be ignored.
.
MessageId=+1 SymbolicName=EMS_LOCN_CMD_RESETDB Severity=Success Facility=ITF
Language=English
EMS Location Service reports that a command was received to clear the TOA/FOA measurement cache.
.
MessageId=+1 SymbolicName=EMS_LOCN_CMD_BURST_STORE_TIME Severity=Success Facility=ITF
Language=English
EMS Location Service reports that a command was received to set the TOA/FOA measurement store time to %1 minutes.
.
MessageId=+1 SymbolicName=EMS_LOCN_CMD_EXCEPTION Severity=Success Facility=ITF
Language=English
EMS Location Service reports that an exception report was received from the command message handler:  %1.
.
MessageId=+1 SymbolicName=EMS_LOCN_CMD_NOT_CONNECTED Severity=Success Facility=ITF
Language=English
EMS Location Service reports that it could not connect to the Message Queue for receipt of command messages.  Processing will continue, but commands will not be received.
.
;
;#endif // INC_LOCNMSGS
