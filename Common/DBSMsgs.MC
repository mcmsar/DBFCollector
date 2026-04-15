;/********************************************************************
;*	Module:			DBSMsgs.mc
;*	Process ID: 
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for LeoLut600DBS Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
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
;	0.0	03/01/24		jb		start
;
;********************************************************************/
;#ifndef INC_DBSMSGS
;#define INC_DBSMSGS
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

;// EMSLEO600DBS_E_DUPLICATE_KEY to retain original numeric value:
;//		MAKE_HRESULT( SEVERITY_ERROR, FACILITY_ITF, 0x7400 ) 
;// Define first, before the base code, so that new 
;// messages can use the +1 syntax
MessageId=0x7400 SymbolicName=EMSLEO600DBS_E_DUPLICATE_KEY Severity=ErrWarn Facility=ITF
Language=English
EMS LeoLut600 Database: Insert failed due to duplicate primary key.
.
MessageId=0xBF00 SymbolicName=EMS_DBS_BASE_CODE Facility=ITF
Language=English
EMS LeoLut600 Database
.
MessageId=+1 SymbolicName=EMS_DBS_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error %1 occurred while accessing %2.
.
MessageId=+1 SymbolicName=EMS_DBS_ADO_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
An ADO exception occurred while accessing %1:  error code = %2, description = %3, source = %4.
.
MessageId=+1 SymbolicName=EMS_DBS_SQL Severity=ErrWarn Facility=ITF
Language=English
The following SQL statement failed during execution:  %1.
.
MessageId=+1 SymbolicName=EMS_DBS_SERVICE_DELETE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS LeoLut600 Database: Service could not be deleted.
.
MessageId=+1 SymbolicName=EMS_DBS_HANDLERNOTINSTALLED Severity=ErrWarn Facility=ITF
Language=English
EMS LeoLut600 Database: Handler not installed
.
MessageId=+1 SymbolicName=EMS_DBS_SERVICESTOPPED Severity=Success Facility=ITF
Language=English
EMS LeoLut600 Database: Service stopped
.
MessageId=+1 SymbolicName=EMS_DBS_SERVICESTARTED Severity=Success Facility=ITF
Language=English
EMS LeoLut600 Database: Service started
.
MessageId=+1 SymbolicName=EMS_DBS_BADSERVICEREQUEST Severity=ErrWarn Facility=ITF
Language=English
EMS LeoLut600 Database: Bad service request received.
.
MessageId=+1 SymbolicName=EMS_DBS_SMOPEN_ERR Severity=ErrWarn Facility=ITF
Language=English
Couldn't open service manager
.
MessageId=+1 SymbolicName=EMS_DBS_CREATESERVICE_ERR Severity=ErrWarn Facility=ITF
Language=English
Couldn't create service
.
MessageId=+1 SymbolicName=EMS_DBS_OPENSERVICE_ERR Severity=ErrWarn Facility=ITF
Language=English
Couldn't open service
.
MessageId=+1 SymbolicName=EMS_DBS_E_NOTABLE Severity=ErrWarn Facility=ITF
Language=English
EMS LeoLut600 Database: Invalid column or table name specified. Please confirm that your database has been upgraded to the latest version.
.
;
;#endif // INC_DBSMSGS
