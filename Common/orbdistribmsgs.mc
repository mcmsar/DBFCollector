;/*********************************************************************
;*	              Copyright (c) 2007 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/

;/*******************************************************************

 ; Revision Record

;	$Log:
;	$
;********************************************************************/

;#ifndef INC_ORBIT_DIST_MSGS
;#define INC_ORBIT_DIST_MSGS
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

MessageId=0xE700 SymbolicName=EMS_ORBIT_DIST_BASE_CODE Facility=ITF
Language=English
EMS Orbit Distributor error.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_STARTED Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor has started.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor failed to start with error code %1.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_STOPPED Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor has stopped.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_NO_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor failed to to get configuration from ConfigWS for %1 Component.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_NO_SITE_INFO Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor failed to create an instance of the site configuration object.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DEST_NUM_SATS Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor retrieved a list of %1 satellites from configuration.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_NO_ORBIT Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor failed to create an instance of the orbit object.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_ORBIT_RET_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor failed to retrieve orbit data for satellite %1.  Orbit object returned error code %2.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_NO_SAT_MAPPING Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor did not find the satellite ID to NORAD name mappings in the configuration file.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_OUT_FOLDER_AUDIT Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor found an output folder in the configuration.  Path = %1, Data File = %2, Index File = %3.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_OUT_FOLDER_NO_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor could not open a data file for writing.  The data file name was not found.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_OUT_FOLDER_NO_INDEX_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor could not open a index file for writing.  The index file name was not found.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_FILE_OPEN_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor could not open file %1 for writing.  OS error is %2.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_TLE_CONV_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor encountered error %1 while attempting to convert from EMSTLEDATA2 TO EMSTLERECORD formats.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_TLE_SEND_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor encountered error %1 while attempting to send orbit data to a Front End Processor.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_FP_PROXY_CREATE_FAIL Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Distributor encountered error %1 while attempting to create an instance of a Front End Processor proxy class.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_FILES_WRITTEN Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor output orbit data to %1 and index %2.
.
MessageId=+1 SymbolicName=EMS_ORBIT_DIST_FP_OUTPUT Severity=Success Facility=ITF
Language=English
EMS Orbit Distributor output orbit data to FP with URL %1.
.
;
;#endif // INC_ORBIT_DIST_MSGS
