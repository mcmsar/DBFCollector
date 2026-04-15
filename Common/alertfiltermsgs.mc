;/********************************************************************
;*	Module:			AlertFilterMsgs.mc
;*	Process ID: 
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Alert Filter Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2005 by EMS Technologies, Inc.,
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
;	0.0	2005/11/15		rvw	start
;
;********************************************************************/
;#ifndef INC_ALERTFILTERMSGS
;#define INC_ALERTFILTERMSGS
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

MessageId=0xCF00 SymbolicName=EMS_ALERTFILTER_BASE_CODE Facility=ITF
Language=English
EMS Alert Filter Base Code
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNKNOWN_REASON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) for an unknown reason.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_INVALID_COUNTRY_CODE Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid country code.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_SINGLE_PDF1_ERROR_LIMIT Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) with a single message and uncorrectable PDF1 errors
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNLOCATED_CBC121 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated CBC 121.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNLOCATED_CBC243 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated CBC 243.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNLOCATED_CBC406 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated interferer.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LOCATED_CBC121 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located CBC 121.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LOCATED_CBC243 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located CBC 243.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LOCATED_CBC406 Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located interferer.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_ORBITOGRAPHY_BEACON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Orbitography beacon.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_REFERENCE_BEACON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Reference Beacon.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_TEST_BEACON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Test encoding.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_INVERTEDFS_BEACON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to inverted frame sync.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LEOGEO_OUTOFSPEC Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to out of spec LEO/GEO
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LEOGEO_UNLOCATED Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated LEO/GEO
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LEOGEO_LOCATED Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located LEO/GEO
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNLOCATED_SARP Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated SARP.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LOCATED_SARP Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located SARP.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_UNLOCATED_SARR Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated SARR.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_LOCATED_SARR Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located SARR.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_INVALID_ENCODING Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid encoding.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_STANDARD_BEACON Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed Beacon: %1, Dest: %2 (as configured).
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_TOO_MANY_BIT_ERRORS Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) because of too many bit errors.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_SUPPRESSNORMAL Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) as normal
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_COUNTRYCODE Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to country code.
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_RESERVED Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed as configured (Beacon: %1, Dest: %2).
.
MessageId=+1 SymbolicName=EMS_ALERTFILTER_INVALID_FIXED_BITS Severity=Warn Facility=ITF
Language=English
EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid location fixed bits.
.
;#endif // INC_ALERTFILTERMSGS
