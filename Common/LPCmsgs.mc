;/********************************************************************
;*	Module:			LPCMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for LocationProcessorController Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2004 by EMS Technologies, Inc.,
;*										All rights reserved
;* This program is unpublished software and contains the trade secrets
;* and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
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
;	0.0	2003Oct02		CH		start 
;
;********************************************************************/
;#ifndef INC_LPCMSGS
;#define INC_LPCMSGS
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

MessageId=0xB800 SymbolicName=EMS_LPC_BASE_CODE Facility=ITF
Language=English
EMS LPC Error
.
MessageId=+1 SymbolicName=EMS_LPC_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS LPC Service Started
.
MessageId=+1 SymbolicName=EMS_LPC_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Service did not start due to error.
.
MessageId=+1 SymbolicName=EMS_LPC_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS LPC Service Stopped
.
MessageId=+1 SymbolicName=EMS_LPC_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS LPC reports error %1.
.
MessageId=+1 SymbolicName=EMS_LPC_TRACE_MSG Severity=Success Facility=ITF
Language=English
EMS LPC trace message:  %1.
.
MessageId=+1 SymbolicName=EMS_LPC_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_LPC_MAX_SESSIONS_REACHED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC maximum number of manual sessions reached (%1). Cannot initialize a new session.
.
MessageId=+1 SymbolicName=EMS_LPC_INVALID_SESSION_ID Severity=ErrWarn Facility=ITF
Language=English
EMS LPC invalid session id specified: %1
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_STARTED Severity=Success Facility=ITF
Language=English
EMS LPC manual session initialized with parameters %1
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_CANCELLED Severity=Success Facility=ITF
Language=English
EMS LPC manual session (%1) ended.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_DATACOUNT Severity=Success Facility=ITF
Language=English
EMS LPC manual session retrieved %1 records.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_REMOVERECORDS Severity=Success Facility=ITF
Language=English
EMS LPC manual session (%1) records removed.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_PROCESS406 Severity=Success Facility=ITF
Language=English
EMS LPC manual session (%1) location processing requested.
.
MessageId=+1 SymbolicName=EMS_LPC_CONTROLFILELIST Severity=Success Facility=ITF
Language=English
EMS LPC request received for control file list.
.
MessageId=+1 SymbolicName=EMS_LPC_CONTROLFILELIST_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC failed to retrieve control file list.
.
MessageId=+1 SymbolicName=EMS_LPC_FAILEDTOPURGEFILE Severity=Success Facility=ITF
Language=English
EMS LPC failed to purge beacon data file %1
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_INIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC manual session initialization failed WHERE %1
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_PROCESS406_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC manual session (%1) location processing failed.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_REMOVERECORDS_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC manual session (%1) remove records failed.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_CANCEL_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC manual session (%1) cancellation failed.
.
MessageId=+1 SymbolicName=EMS_LPC_MANUAL_TOMANYRECORDS Severity=ErrWarn Facility=ITF
Language=English
EMS LPC manual session initialization attempted to retrieve more than the maximum allowed number of records.
.
MessageId=+1 SymbolicName=EMS_LPC_PURGING_FILES Severity=Success Facility=ITF
Language=English
EMS LPC purging expired files.
.
MessageId=+1 SymbolicName=EMS_LPC_AUTO_REQUESTED_CALIB406 Severity=Success Facility=ITF
Language=English
EMS LPC requesting location processing of %1 calib406 beacons.
.
MessageId=+1 SymbolicName=EMS_LPC_AUTO_REQUESTED_COMB406 Severity=Success Facility=ITF
Language=English
EMS LPC requesting location processing of %1 combine406 beacons.
.
MessageId=+1 SymbolicName=EMS_LPC_INVALID_DATA_DIRECTORY Severity=ErrWarn Facility=ITF
Language=English
EMS LPC failed to access data directory specified by configuration (%1).
.
MessageId=+1 SymbolicName=EMS_LPC_INITIALIZATION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC initialization failed.
.
MessageId=+1 SymbolicName=EMS_LPC_RECEIVECALIB406_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Failed while receiving calib406 data for processing.
.
MessageId=+1 SymbolicName=EMS_LPC_RECEIVECOMB406_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Failed while receiving combine406 data for processing.
.
MessageId=+1 SymbolicName=EMS_LPC_GATEWAYRESPONSE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Failed to write a response to the gateway.
.
MessageId=+1 SymbolicName=EMS_LPC_FILEPURGED Severity=Success Facility=ITF
Language=English
EMS LPC Beacon data file (%1) purged.
.
MessageId=+1 SymbolicName=EMS_LPC_RECEIVECALIB406_SUMMARY Severity=Success Facility=ITF
Language=English
EMS LPC Successfully saved %1 of %2 calib406 records for location processing.
.
MessageId=+1 SymbolicName=EMS_LPC_RECEIVECOMB406_SUMMARY Severity=Success Facility=ITF
Language=English
EMS LPC Successfully saved %1 of %2 combine406 records for location processing.
.
MessageId=+1 SymbolicName=EMS_LPC_NOBEACONSTOPROCESS Severity=Success Facility=ITF
Language=English
EMS LPC Automatic location processing detected no beacons ready for processing.
.
MessageId=+1 SymbolicName=EMS_LPC_AUTOMATIC_PROCESSING_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Automatic location processing failed.
.
MessageId=+1 SymbolicName=EMS_LPC_PURGE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS LPC Periodic file purge failed.
.
MessageId=+1 SymbolicName=EMS_LPC_SOLVE_CMD Severity=Success Facility=ITF
Language=English
EMS LPC Sending solve command to location processor: %1
.
MessageId=+1 SymbolicName=EMS_LPC_LP_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS LPC timed out while waiting for location results.  Location processor may be busy.  Please resubmit request.
.
MessageId=+1 SymbolicName=EMS_LPC_LP_BUSY Severity=ErrWarn Facility=ITF
Language=English
EMS LPC cannot process location requests.  Location Processor is busy.  Please resubmit request.
.
;
;#endif // INC_LPCMSGS



