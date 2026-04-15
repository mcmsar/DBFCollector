;/********************************************************************
;*	Module:			LocnAnalMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Location Analysis Processor 
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
;	0.0	2005/11/21		rvw	start
;
;********************************************************************/
;#ifndef INC_LOCNANALMSGS
;#define INC_LOCNANALMSGS
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;

MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
	Info=0x1
	Warn=0x2
	Alarm=0x3
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xEF00 SymbolicName=EMS_LOCN_ANAL_BASE_CODE Facility=ITF
Language=English
EMS Locn Analysis
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Locn Analysis Service Started
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Locn Analysis Service Stopped
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_SERVICE_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Locn Analysis Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_ACCURACY_CHECK_FAILURE Severity=Warn Facility=ITF
Language=English
EMS Locn Analysis Service reports reference beacon %1 location (lat:%3 lon: %4) is %2 km different from expected.
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_NOM_UPDATE Severity=Success Facility=ITF
Language=English
EMS Locn Analysis Service updated Sat %1 nominal %2 (%3).
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_MARG_UPDATE Severity=Success Facility=ITF
Language=English
EMS Locn Analysis Service updated Sat %1 marginal %2 (%3).
.
MessageId=+1 SymbolicName=EMS_LOCN_ANAL_NEW_SARR_OFFSETS Severity=Success Facility=ITF
Language=English
EMS Locn Analysis Service updated SARR Offsets ( SatID=%1, Freq=%2, Drift=%3, Time=%4 ).
.
;
;#endif // INC_LOCNANALMSGS
