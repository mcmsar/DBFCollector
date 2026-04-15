;/********************************************************************
;*	Module:			WBandMsg.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Wideband Errors & Messages
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
;#ifndef INC_WBANDMSG
;#define INC_WBANDMSG
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

MessageId=0xA200 SymbolicName=EMS_WIDEBAND_BASE_CODE Facility=ITF
Language=English
EMS Wideband Error
.
MessageId=+1 SymbolicName=EMS_WBAND_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Wideband Service Started
.
MessageId=+1 SymbolicName=EMS_WBAND_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS Wideband Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_WBAND_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Wideband Service Stopped
.
MessageId=+1 SymbolicName=EMS_WBAND_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband reports error %1.
.
MessageId=+1 SymbolicName=EMS_WBAND_PRIORITY_CLASS Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband reports error %1 when calling SetPriorityClass
.
MessageId=+1 SymbolicName=EMS_WBAND_THREAD_PRIORITY Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband reports error %1 when calling SetThreadPriority
.
MessageId=+1 SymbolicName=EMS_WBAND_IDEAL_PROCESSOR Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband reports error %1 when calling SetThreadIdealProcessor
.
MessageId=+1 SymbolicName=EMS_WBAND_NO_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband reports no data in last %1 seconds during a pass
.
MessageId=+1 SymbolicName=EMS_WBAND_START_PASS Severity=Success Facility=ITF
Language=English
EMS Wideband starting pass ( SatID=%1, LutID=%2, Flags=%3 ).
.
MessageId=+1 SymbolicName=EMS_WBAND_STOP_PASS Severity=Success Facility=ITF
Language=English
EMS Wideband stopping pass. 
.
MessageId=+1 SymbolicName=EMS_WBAND_RECV_COMMAND Severity=Success Facility=ITF
Language=English
EMS Wideband recv'd cmd( %1 ).
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER Severity=Success Facility=ITF
Language=English
EMS Wideband ( %1 ).
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_TWIN0TO1 Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband twin signal 0 -> 1)
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_TWIN1TO0 Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband twin signal 1 -> 0)
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_REPEATINGINDEX Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband repeating index (%1))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_OVERFLOW Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband reports overflow (%1))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_HIGHESTCOUNT Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband highest count (%1))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_OTHERBUFFER Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband reporting other buffer signaled (%1))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_OLDERTHANAOS Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband data %1 minutes older than AOS )
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_DUPLICATETIME Severity=Success Facility=ITF
Language=English
EMS Wideband (** Wideband detected duplicate time in buffer)
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_PREVTIME Severity=Success Facility=ITF
Language=English
EMS Wideband (** Wideband detected previous time in buffer)
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_SECTOINITIALIZE Severity=Success Facility=ITF
Language=English
EMS Wideband (*** Wideband took %1 seconds to initialize)
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_CONFIGYES Severity=Success Facility=ITF
Language=English
EMS Wideband (EMS Wideband (cfg: %1=yes))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_CONFIGNO Severity=Success Facility=ITF
Language=English
EMS Wideband (EMS Wideband (cfg: %1=no))
.
MessageId=+1 SymbolicName=EMS_WBAND_TRACER_CONFIG Severity=Success Facility=ITF
Language=English
EMS Wideband (cfg: %1=%2)
.
MessageId=+1 SymbolicName=EMS_WBAND_INVALIDSTOPCMD Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband is not collecting so a request to Stop was ignored.
.
MessageId=+1 SymbolicName=EMS_WBAND_INVALIDSTARTCMD Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband is already collecting so a request to Start was ignored.
.
MessageId=+1 SymbolicName=EMS_WBAND_CMDERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Wideband detected an error while processing a %1 command <%2>
.
;
;#endif // INC_WBANDMSG

