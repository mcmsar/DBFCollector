;/*********************************************************************
;*	              Copyright (c) 2007 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/

;/*******************************************************************

 ; Revision Record

;	$Log:
;	$
;********************************************************************/

;#ifndef INC_BUS_WS_MSGS
;#define INC_BUS_WS_MSGS
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

MessageId=0xEB00 SymbolicName=EMS_BUS_BASE_CODE Facility=ITF
Language=English
EMS Backup Server error.
.
MessageId=+1 SymbolicName=EMS_BUS_DBTYPE_UNSUPPORTED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  Specified database type, %1, not supported.
.
MessageId=+1 SymbolicName=EMS_BUS_DBTYPE_UNSPECIFIED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  Database type not specified.
.
MessageId=+1 SymbolicName=EMS_BUS_STORAGE_UNSPECIFIED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  Folder/directory for storage of backup files not specified.
.
MessageId=+1 SymbolicName=EMS_BUS_STORE_BACKUP_TRANS_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  Failed to save some or all data for a received backup in the database.  Transaction rolled back.
.
MessageId=+1 SymbolicName=EMS_BUS_UPDATE_AGEOUT_TRANS_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  During an update, failed to save some or all data defining ageout events for backup %1 in the database.  Transaction rolled back.
.
MessageId=+1 SymbolicName=EMS_BUS_AGEOUT_FOLDER_UNSPECIFIED Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server error.  Folder/directory for storage of aged-out files not specified.
.
MessageId=+1 SymbolicName=EMS_BUS_WS_PUT_NO_FILES Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server Web Service error.  Command to store backup received with an empty list of backup file attachments.
.
MessageId=+1 SymbolicName=EMS_BUS_WS_PUT_NO_FILENAME Severity=ErrWarn Facility=ITF
Language=English
EMS Backup Server Web Service error.  Command to store backup could not extract a backup file attachment name from the received message.
.
;
;#endif // INC_WSMSGS
