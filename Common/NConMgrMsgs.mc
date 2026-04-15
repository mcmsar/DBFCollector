;/********************************************************************
;*	Module:			NConMgrMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMSNetConnMgrService Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2002-2006 by EMS Technologies, Inc.,
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
;	0.0	2002 Oct 8		rvw	start 
;
;********************************************************************/
;#ifndef INC_NCONMGRMSGS
;#define INC_NCONMGRMSGS
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

MessageId=0xDF00 SymbolicName=EMS_NCM_BASE_CODE Facility=ITF
Language=English
EMS Net Connection Manager Error
.
MessageId=+1 SymbolicName=EMS_NCM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Net Connection Manager Service Started
.
MessageId=+1 SymbolicName=EMS_NCM_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_NCM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Net Connection Manager Service Stopped
.
MessageId=+1 SymbolicName=EMS_NCM_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager reports error %1.
.
MessageId=+1 SymbolicName=EMS_NCM_UNKNOWN_EXCEPT Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager reports an unknown exception
.
MessageId=+1 SymbolicName=EMS_NCM_UNHANDLED_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager reports an unknown exception
.
MessageId=+1 SymbolicName=EMS_NCM_UNHANDLED_EXCEPTION_AT Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager reports an unknown exception on %1.
.
MessageId=+1 SymbolicName=EMS_NCM_NO_CONFIG_FILE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: no network connections are configured, the service will shutdown.
.
MessageId=+1 SymbolicName=EMS_NCM_INITIALIZATIOM_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager reports a failure in the service initialization, the service will shutdown.
.
MessageId=+1 SymbolicName=EMS_NCM_COINIT_SECURITY_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager failed to Co-initialize the security, error code = %1.
.
MessageId=+1 SymbolicName=EMS_NCM_COREGCLASS_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager failed to register EMSNetConnMgr factory class, error code = %1.
.
MessageId=+1 SymbolicName=EMS_NCM_CORESUME_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: CoResumeClassObjects() failed, error code = %1.
.
MessageId=+1 SymbolicName=EMS_NCM_UNKNOWN_STATE Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: %1 is in unknown state.
.
MessageId=+1 SymbolicName=EMS_NCM_UNABLE_TO_CONNECT Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager is unable to connect %1.
.
MessageId=+1 SymbolicName=EMS_NCM_CONNECT_LOG Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: "%1" connection status is "Connected".
.
MessageId=+1 SymbolicName=EMS_NCM_DISCONNECT_LOG Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: "%1" connection status is "Disconnected".
.
MessageId=+1 SymbolicName=EMS_NCM_UNKNOWN_CONN Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager: "%1" is unknown connection.
.
MessageId=+1 SymbolicName=EMS_NCM_CONNECT_CALL Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager received a Connect message "Connect( %1, %2 )"
.
MessageId=+1 SymbolicName=EMS_NCM_CONNECTEX_CALL Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager received a Connect message "ConnectEx( %1, %2 )"
.
MessageId=+1 SymbolicName=EMS_NCM_DISCONNECT_CALL Severity=ErrWarn Facility=ITF
Language=English
EMS Net Connection Manager received a Disconnect message "Disconnect( %1, %2 )"
.
;
;#endif



