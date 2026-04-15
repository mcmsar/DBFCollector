;/********************************************************************
;*	Module:			AudioMsg.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Audio Service Messages
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
;#ifndef INC_AUDIOMSG
;#define INC_AUDIOMSG
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

MessageId=0xBE00 SymbolicName=EMS_AUDIO_BASE_CODE Facility=ITF
Language=English
EMS Audio Error
.
MessageId=+1 SymbolicName=EMS_AUDIO_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Audio Service Started
.
MessageId=+1 SymbolicName=EMS_AUDIO_SERVICE_FAILED Severity=Success Facility=ITF
Language=English
EMS Audio Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_AUDIO_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Audio Service Stopped
.
MessageId=+1 SymbolicName=EMS_AUDIO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio reports error %1.
.
MessageId=+1 SymbolicName=EMS_AUDIO_LOG_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Audio reports an exception
.
MessageId=+1 SymbolicName=EMS_AUDIO_LOG_INFO Severity=Success Facility=ITF
Language=English
EMS Audio reports info
.
MessageId=+1 SymbolicName=EMS_AUDIO_DIRECTORY_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio reports error while trying to create directory ( %1 ).
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( %1 ).
.
MessageId=+1 SymbolicName=EMS_AUDIO_FILE_READ_FAIL Severity=Success Facility=ITF
Language=English
EMS Audio reports error %1 while attempting to open file %2.
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_MAXSESSIONS Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Manager error : Max sessions reached.
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_CLIENTNOTCONNECTED Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Manager error : Client is not connected.
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_NODATA Severity=Success Facility=ITF
Language=English
EMS Audio Manager : No data found.
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_PROCESSFILE Severity=Success Facility=ITF
Language=English
EMS Audio Manager is processing the file ( %1 ).
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_REQ_COMPLETED Severity=Success Facility=ITF
Language=English
EMS Audio Manager : Audio Request processing completed.
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_RECORDSGEN Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( Request ID: %1, records generated: %2)
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_AUDIOREQ Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( AudioReq %1 )
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_REQDETAILS Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( SatID %1, Time %2, Duration %3, CenterFreq %4, Bandwidth %5 )
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_MAKEWAVEFILE Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( _MakeWaveFile:     result = %1 )
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_CONFIG Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( cfg: %1=%2 )
.
MessageId=+1 SymbolicName=EMS_AUDIO_TRACER_CHANSCOEFFS Severity=Success Facility=ITF
Language=English
EMS Audio tracer ( Chans %1, coeffs %2 )
.
MessageId=+1 SymbolicName=EMS_AUDIOMANAGER_INITFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Manager initialization failed (%1)
.
;
;#endif // INC_AUDIOMSG



