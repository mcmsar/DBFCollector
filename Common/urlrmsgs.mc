;/********************************************************************
;*	Module:			ActvMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS URL Retriever/Receiver 
;*				Services Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2009 by EMS Technologies, Inc.,
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
;#ifndef INC_URLRMSGS
;#define INC_URLRMSGS
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

MessageId=0xF100 SymbolicName=EMS_URLR_BASE_CODE Facility=ITF
Language=English
EMS ActiveBeacon 
.
MessageId=+1 SymbolicName=EMS_URLR_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS URL Retriever Service Started
.
MessageId=+1 SymbolicName=EMS_URLR_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS URL Retriever Service Stoped
.
MessageId=+1 SymbolicName=EMS_URLR_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_URLR_LOAD_CONFIG_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service failed to load the configuration file (%1)
.
MessageId=+1 SymbolicName=EMS_URLR_NO_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service's configuration file is not specified, make sure to configure the service with the proper configuration file.
.
MessageId=+1 SymbolicName=EMS_URLR_NO_URLS Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service's configuration file (%1) does not specify any URL configurations, it must have at least one
.
MessageId=+1 SymbolicName=EMS_FAILED_TO_CONNECT Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service's failed to perform the 'URL Source To Destination' update (URL id=%1), check the network connections to the source and the destination.
.
MessageId=+1 SymbolicName=EMS_BACK_ONLINE Severity=ErrWarn Facility=ITF
Language=English
EMS URL Retriever Service's is able to perform successful 'URL Source To Destination' update (URL id=%1).
.
;
;#endif // INC_URLRMSGS
