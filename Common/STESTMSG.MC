;/********************************************************************
;*	Module:			STestMsg.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS System Test Errors & Messages
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
;#ifndef INC_STESTMSG
;#define INC_STESTMSG
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

MessageId=0xAE00 SymbolicName=EMS_SYSTEST_BASE_CODE Facility=ITF
Language=English
EMS System Test Error
.
MessageId=+1 SymbolicName=EMS_SYSTEST_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS System Test Service Started
.
MessageId=+1 SymbolicName=EMS_SYSTEST_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS System Test Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_SYSTEST_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS System Test Service Stopped
.
MessageId=+1 SymbolicName=EMS_SYSTEST_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS System Test reports error %1.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS System Test timed out during operation.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_START Severity=Success Facility=ITF
Language=English
EMS System Test Initiated.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_FAIL_ANTENNA Severity=ErrWarn Facility=ITF
Language=English
EMS System Test Indicates Possible Antenna Problem %1 ( ADCrms @ az:el ).
.
MessageId=+1 SymbolicName=EMS_SYSTEST_FAIL_POWER Severity=ErrWarn Facility=ITF
Language=English
EMS System Test Indicates Possible Signal Reception Problem %1 ( ADCrms @ az:el ).
.
MessageId=+1 SymbolicName=EMS_SYSTEST_STATUS Severity=Success Facility=ITF
Language=English
%1,EMS System Test Status 
.
MessageId=+1 SymbolicName=EMS_SYSTEST_PASSED Severity=Success Facility=ITF
Language=English
EMS System Test Passed  %1 ( ADCrms @ az:el ).
.
MessageId=+1 SymbolicName=EMS_SYSTEST_NO_AGC_SWITCH_INFO Severity=Success Facility=ITF
Language=English
EMS System Test reports AGC switch not available yet.
.
MessageId=+0 SymbolicName=EMS_SYSTEST_NO_AGC_SWITCH_ALARM Severity=ErrWarn Facility=ITF
Language=English
EMS System Test reports AGC switch not available.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_NO_ANTENNA Severity=ErrWarn Facility=ITF
Language=English
EMS System Test unable to communicate with the Antenna Service.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_STATUS_OKAY Severity=Success Facility=ITF
Language=English
%1,OKAY,EMS System Test Status 
.
MessageId=+1 SymbolicName=EMS_SYSTEST_STATUS_FAILED Severity=Success Facility=ITF
Language=English
%1,FAILED,EMS System Test Status 
.
MessageId=+1 SymbolicName=EMS_SYSTEST_NOT_INIT Severity=ErrWarn Facility=ITF
Language=English
EMS System Test has not initialized.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_ALREADY_IN_TEST Severity=ErrWarn Facility=ITF
Language=English
EMS System Test cannot process the request to start a system test as a test is currently underway.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_NO_TX_SWITCH_ALARM Severity=ErrWarn Facility=ITF
Language=English
EMS System Test reports Transmitter switch not available.
.
MessageId=+1 SymbolicName=EMS_SYSTEST_TX_SWITCH_ON_FP Severity=Success Facility=ITF
Language=English
EMS System Test expecting Transmitter to be switched on the FP.
.
;
;#endif // INC_STESTMSG


