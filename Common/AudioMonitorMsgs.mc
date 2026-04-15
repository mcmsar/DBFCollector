;/********************************************************************
;*	Module:			AudioMonitorMsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Audio Monitor Errors & Messages
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
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_AUDIOMONITORMSG
;#define INC_AUDIOMONITORMSG
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

MessageId=0xC700 SymbolicName=EMS_AUDIOMONITOR_BASE_CODE Facility=ITF
Language=English
EMS Audio Monitor Error
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_UNKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor reports that an error has occurred.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_TITLE Severity=Info Facility=ITF
Language=English
EMS Audio Monitor
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_TOOLBAR_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor failed to create toolbar.
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_CONFIG_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor Configuration error. The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_AUDSTREAM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor Creating Audio Stream error. The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AM_AUDIOPLAYER_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor Can't create NCTAudioPlayer2 control. The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AM_AUDIOVISUALISATION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor Can't create NCTAudioVisualisation control. The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AM_AUDIOFILE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor Can't create NCTAudioFile control. The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_AM_BANDWIDTHOUT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor error The bandwith range is 1 to 4 KHz.
.
MessageId=+1 SymbolicName=EMS_AM_FREQUENCYOUT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Audio Monitor error The center frequency is out of range.
.
MessageId=+1 SymbolicName=EMS_AUDIOMONITOR_NODATA Severity=ErrWarn Facility=ITF
Language=English
No data found
.
;
;#endif
