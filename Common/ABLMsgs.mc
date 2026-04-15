;/********************************************************************
;*	Module:			ABLMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for ABL Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2002-2007 by EMS Technologies, Inc.,
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
;	0.0	2002 Oct 8		rvw	start 
;
;********************************************************************/
;#ifndef INC_ABLMSGS
;#define INC_ABLMSGS
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

MessageId=0xED00 SymbolicName=EMS_ABL_BASE_CODE Facility=ITF
Language=English
EMS Active Beacon List Object Error
.
MessageId=+1 SymbolicName=EMS_ABL_UNKNOWN_EXCEPT Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object reports an unknown exception
.
MessageId=+1 SymbolicName=EMS_ABL_UNHANDLED_EXCEPTION_AT Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object reports an unknown exception on %1.
.
MessageId=+1 SymbolicName=EMS_ABL_NO_CONFIG_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object: no configuration file.
.
MessageId=+1 SymbolicName=EMS_ABL_MEM_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object reports a memory overflow.
.
MessageId=+1 SymbolicName=EMS_ABL_NO_LOCATION_UPDATE Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object reports no location updates at this time.
.
MessageId=+1 SymbolicName=EMS_ABL_MAX_CAP Severity=ErrWarn Facility=ITF
Language=English
EMS Active Beacon List Object reached the maximum configured number of raw input records.
.
;
;#endif



