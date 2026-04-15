;/********************************************************************
;*	Module:			CalibCBCMsg.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS CalibCBC Errors & Messages
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
;#ifndef INC_CALIBCBCMSG
;#define INC_CALIBCBCMSG
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

MessageId=0xA800 SymbolicName=EMS_CALIBCBC_BASE_CODE Facility=ITF
Language=English
EMS CalibrateCBC Error
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Started
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Stopped
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC reports error %1.
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_START_PASS Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC initialized for satellite %1
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_CALIBRATE_PASS Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC completed calibration for satellite=%1, band=%2, result=%3
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_ADDREC_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC reports error %1 adding record %2.
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACER Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Command Received( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_START_CALIBRATE Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Starting to calibrate %1 records.
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_SUBSYSTEM_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC reports error %1 while trying to access %2
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_AUDIOSENT Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 sent )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_AUDIONOTSENT Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 not sent )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_CONFIGPARAMS1 Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Config Parms-%1: minAmplitude %2, fTimeBinSize %3 sec, fFreqBinSize %4 Hz, fFreqWindow %5 Hz )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_CONFIGPARAMS2 Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_CONFIGPARAMS3 Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Config Parms: minAmplitude %1, fTimeBinSize    %2 sec, fFreqBinSize    %3 Hz, fFreqWindow %4 Hz )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_TRACE_CONFIGPARAMS4 Severity=Success Facility=ITF
Language=English
EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_SUBSYSTEM_ERR_CALIBRATE Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC reports error %1 (trap %2) while trying to access the calibrate subsystem. 
.
MessageId=+1 SymbolicName=EMS_CALIBCBC_CALIBRATE_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS CalibrateCBC time limit exceeded for satellite=%1, band=%2
.
;
;#endif // INC_CALIBCBCMSG

