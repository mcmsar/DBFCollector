;/********************************************************************
;*	Module:			EMSStatusCalibMonitorMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Calibration Monitor Messages
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
;	0.0	2003Dec01		CH		start 
;
;********************************************************************/
;#ifndef INC_EMSSECMSGS
;#define INC_EMSSECMSGS
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

MessageId=0xB400 SymbolicName=EMS_CALIBMONITOR_BASE_CODE Facility=ITF
Language=English
EMS Calibration Monitor Error
.
MessageId=+1 SymbolicName=EMS_MONITOR_PIPE_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Pipeline Monitor object not initialized
.
MessageId=+1 SymbolicName=EMS_MONITOR_CONFIG_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Monitor Configuration not initialized
.
MessageId=+1 SymbolicName=EMS_MONITOR_GATEWAY_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Monitor Gateway not initialized
.
MessageId=+1 SymbolicName=EMS_MONITOR_SEC_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Monitor Security not initialized
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Calibration Monitor initialization error ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_INIT_OK Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor service started %1
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_PROCESSTLE_ERR Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor: an error has occurred while processing TLEs ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_SENDOVECTORS_ERR Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor: an error occurred while sending orbit vectors ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_SENDTLES_ERR Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor: an error occurred while sending TLEs ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_SENDSARR_ERR Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor: an error occurred while sending SARR data ( %1 )
.
MessageId=+1 SymbolicName=EMS_CALIBMONITOR_SENDSARP_ERR Severity=Success Facility=ITF
Language=English
EMS Calibration Monitor: an error occurred while sending SARP data ( %1 )
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Status Monitor initialization error ( %1 )
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_INIT_OK Severity=Success Facility=ITF
Language=English
EMS Status Monitor service started %1
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_SENDSTATUS_ERR Severity=Success Facility=ITF
Language=English
EMS Status Monitor: an error occurred while sending Statuses ( %1 )
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_SENDSTARTUP_ERR Severity=Success Facility=ITF
Language=English
EMS Status Monitor: an error occurred while sending Startup data ( %1 )
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_SENDWARNING_ERR Severity=Success Facility=ITF
Language=English
EMS Status Monitor: an error occurred while sending warning ( %1 )
.
MessageId=+1 SymbolicName=EMS_STATUSMONITOR_SENDALARM_ERR Severity=Success Facility=ITF
Language=English
EMS Status Monitor: an error occurred while sending Alarm ( %1 )
.
;
;#endif // INC_EMSSECMSGS


