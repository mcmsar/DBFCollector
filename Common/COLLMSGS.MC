;/********************************************************************
;*	Module:			CollMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Collector Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2001 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
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
;	0.0	01/05/21		rvw	start
;
;********************************************************************/
;#ifndef INC_COLLMSGS
;#define INC_COLLMSGS
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

MessageId=0xA300 SymbolicName=EMS_COLL_BASE_CODE Facility=ITF
Language=English
EMS Collector Error
.
MessageId=+1 SymbolicName=EMS_COLL_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Collector Service Started
.
MessageId=+1 SymbolicName=EMS_COLL_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Collector Service did not start due to error (%1)
.
MessageId=+1 SymbolicName=EMS_COLL_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Collector Service Stopped
.
MessageId=+1 SymbolicName=EMS_COLL_PASS_START Severity=Success Facility=ITF
Language=English
EMS Collector Service Starting Pass for Sat %1.
.
MessageId=+1 SymbolicName=EMS_COLL_PASS_STOP Severity=Success Facility=ITF
Language=English
EMS Collector Service Stopped Pass for Sat %1.
.
MessageId=+1 SymbolicName=EMS_COLL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Collector reports error (%1).
.
MessageId=+1 SymbolicName=EMS_COLL_AD_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
EMS Collector reports A/D Board overflow
.
MessageId=+1 SymbolicName=EMS_COLL_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Collector recv'd cmd( %1 ).
.
MessageId=+1 SymbolicName=EMS_COLL_WARN_MISSING_BUFFER Severity=Warn Facility=ITF
Language=English
EMS Collector hasn't received a buffer in %1 seconds, resetting.
.
MessageId=+0 SymbolicName=EMS_COLL_ALARM_MISSING_BUFFER Severity=Alarm Facility=ITF
Language=English
EMS Collector hasn't received a buffer in %1 seconds, stopping.
.
MessageId=+1 SymbolicName=EMS_COLL_WARN_ADBOARD_INIT_FAILED Severity=Warn Facility=ITF
Language=English
EMS Collector reports error trying to initialize AD Board, resetting. (%1)
.
MessageId=+0 SymbolicName=EMS_COLL_ALARM_ADBOARD_INIT_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Collector reports error trying to initialize AD Board, stopping. (%1) 
.
MessageId=+1 SymbolicName=EMS_COLL_WARN_ADBOARD_START_FAILED Severity=Warn Facility=ITF
Language=English
EMS Collector reports error trying to start AD Board, resetting. (%1)
.
MessageId=+0 SymbolicName=EMS_COLL_ALARM_ADBOARD_START_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Collector reports error trying to start AD Board, stopping. (%1) 
.
MessageId=+1 SymbolicName=EMS_COLL_ALARM_MEMMARKER Severity=Warn Facility=ITF
Language=English
EMS Collector reports memory marker %1 signal.
.
MessageId=+1 SymbolicName=EMS_COLL_START_RECEIVED Severity=Info Facility=ITF
Language=English
EMS Collector reports that a start command was received.
.
MessageId=+1 SymbolicName=EMS_COLL_STOP_RECEIVED Severity=Info Facility=ITF
Language=English
EMS Collector reports that a stop command was received.
.
MessageId=+1 SymbolicName=EMS_COLL_SAT_RECEIVED Severity=Info Facility=ITF
Language=English
EMS Collector reports that a set satellite command was received.  SatID = %1, Flags = %2, Bandwidth = %3.
.
MessageId=+1 SymbolicName=EMS_COLL_INPUTID_RECEIVED Severity=Info Facility=ITF
Language=English
EMS Collector reports that a set input identifier command was received.  InputID = %1.
.
MessageId=+1 SymbolicName=EMS_COLL_START_UNINIT_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Collector reports attempt to start collection on an uninitialized A/D Board (%1) Channel (%2).
.
MessageId=+1 SymbolicName=EMS_COLL_STATUS_UPDATE_FAILED Severity=Info Facility=ITF
Language=English
EMS Collector reports error attempting to update status. (%1)
.
MessageId=+1 SymbolicName=EMS_COLL_NO_AD_CHANNELS Severity=Alarm Facility=ITF
Language=English
EMS Collector reports that A/D Board has no available channels.
.
MessageId=+1 SymbolicName=EMS_CS_WARN_MISSING_BUFFER Severity=Warn Facility=ITF
Language=English
EMS CollectorStub hasn't received a buffer in %1 seconds, resetting.
.
MessageId=+0 SymbolicName=EMS_CS_ALARM_MISSING_BUFFER Severity=Alarm Facility=ITF
Language=English
EMS CollectorStub hasn't received a buffer in %1 seconds, stopping.
.
MessageId=+1 SymbolicName=EMS_CS_FP_COMMS_FAILED Severity=Alarm Facility=ITF
Language=English
EMS CollectorStub failed to communicate with FP (%1)
.
MessageId=+1 SymbolicName=EMS_CS_FP_COMMS_RESTORED Severity=Info Facility=ITF
Language=English
EMS CollectorStub communications restored to FP.
.
MessageId=+1 SymbolicName=EMS_COLL_1PPS_SIGNAL_OFF_ALARM Severity=Alarm Facility=ITF
Language=English
EMS Collector reports that the one pulse per second signal has not been detected for %1 seconds.
.
MessageId=+1 SymbolicName=EMS_COLL_1PPS_SIGNAL_OFF Severity=Info Facility=ITF
Language=English
EMS Collector reports that the one pulse per second signal was not detected in the last collected data buffer.
.
MessageId=+1 SymbolicName=EMS_COLL_1PPS_SIGNAL_ON Severity=Info Facility=ITF
Language=English
EMS Collector reports that after an outage, the one pulse per second signal is now being detected.
.
MessageId=+1 SymbolicName=EMS_COLL_ERROR_SENDING_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Collector reports an error sending data.  Error code = %1.  Disconnecting.
.
MessageId=+1 SymbolicName=EMS_COLL_TRANSMITTING Severity=Info Facility=ITF
Language=English
EMS Collector reports transmitting Wave with time = %1 (%2).
.
MessageId=+1 SymbolicName=EMS_COLL_ERROR_SENDING_WAVE_RECORD Severity=ErrWarn Facility=ITF
Language=English
EMS Collector reports an error sending wave record.
.
MessageId=+1 SymbolicName=EMS_COLL_COMMON_INFO_MEG Severity=Info Facility=ITF
Language=English
EMS Collector reports %1.
.
MessageId=+1 SymbolicName=EMS_COLL_DATA_DEST_OFFLINE Severity=ErrWarn Facility=ITF
Language=English
EMS Collector reports connection failed.  Data destination is offline.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: %3.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_MARKER_INDEX Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Last  marker index = %3, This marker index = %4.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_MARKER_BIT_INDEX Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Marker bit index calculated as %3.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_DATA_BUF_TIME Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Original Data Buffer Time = %3 (%4).
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_DATA_NAROSEC_OFFSET Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Nanosecond offset %3.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_DATA_SEC_DIFF Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Difference between time of last buffer and this buffer is %3 seconds.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_1 Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers exceeds 1.1 seconds. Last time = %3, this time = %4.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_2 Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers less than 1.0 second. Last time = %3, this time = %4.
.
MessageId=+1 SymbolicName=EMS_COLL_DC_DEBUG_MSG_ADJUSTED_TIME Severity=Info Facility=ITF
Language=English
EMS Collector reports File: %1 Line: %2 with debug message: Adjusted Time = %3 (%4).
.
;
;#endif // INC_COLLMSGS

