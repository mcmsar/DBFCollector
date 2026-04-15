;/********************************************************************
;*	Module:			EMSSecMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Data Transfer Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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
;	0.0	2003Dec04		CH		start 
;
;********************************************************************/
;#ifndef INC_EMSDTSGS
;#define INC_EMSDTMSGS
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

MessageId=0xAF00 SymbolicName=EMS_DTX_BASE_CODE Facility=ITF
Language=English
EMS Data Transfer Error
.
MessageId=+1 SymbolicName=EMS_DTX_GENERAL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Access Denied %1
.
MessageId=+1 SymbolicName=EMS_DTX_TRACE Severity=Success Facility=ITF
Language=English
EMS Data Transfer reports trace %1
.
MessageId=+1 SymbolicName=EMS_DTX_INFO Severity=Success Facility=ITF
Language=English
EMS Data Transfer Info %1
.
MessageId=+1 SymbolicName=EMS_DTX_DEBUG Severity=Success Facility=ITF
Language=English
EMS Data Transfer debug message %1
.
MessageId=+1 SymbolicName=EMS_DTX_NO_TYPES Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer the supported types list is empty %1
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Initialization error %1
.
MessageId=+1 SymbolicName=EMS_DTX_ADD_DEST_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error Cannot add the destination information %1
.
MessageId=+1 SymbolicName=EMS_DTX_SECURITY_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error Cannot retrieve the security token %1
.
MessageId=+1 SymbolicName=EMS_DTX_DAL_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error retrieving data from the DAL %1
.
MessageId=+1 SymbolicName=EMS_DTX_DATATOOBIG_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error data requested is too big %1
.
MessageId=+1 SymbolicName=EMS_DTX_CREATEFILE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error creating the file %1
.
MessageId=+1 SymbolicName=EMS_DTX_WRITEHEADER_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error writing the file header %1
.
MessageId=+1 SymbolicName=EMS_DTX_ADDRECORD_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error adding the record to the file %1
.
MessageId=+1 SymbolicName=EMS_DTX_COPYFILE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error copying the file %1
.
MessageId=+1 SymbolicName=EMS_DTX_NOSTATICFILE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error: no file available in the static file list for the automatic data transfer %1
.
MessageId=+1 SymbolicName=EMS_DTX_REGSINK_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error registering pipeline sink%1
.
MessageId=+1 SymbolicName=EMS_DTX_DATATYPEMISSING_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error cannot find data type information %1
.
MessageId=+1 SymbolicName=EMS_DTX_NORECORDS_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer Error: no records found %1
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot initialize the Data Transfer Subsystem
.
MessageId=+1 SymbolicName=EMS_DTX_INIT Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Data Transfer Subsystem initialized
.
MessageId=+1 SymbolicName=EMS_DTX_UPLOADRECEIVED Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Received Upload request - Destination:%1, Record Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_RETRIEVINGDATA_OK Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Retrieving Data from DAL is OK - Destination:%1, Record Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_WRITINGDATA_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot write the data retrieved from DAL - Destination:%1, Record Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_WRITINGDATA_OK Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Writing Data retrieved from DAL is OK - Destination:%1, Record Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_RETREIVINGDATA_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot retrieve Data from DAL - Destination:%1, Record Type: %2, Error: %3
.
MessageId=+1 SymbolicName=EMS_DTX_AUTOWRITINGDATA_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot write the automatically generated data - Data Type: %1, Error: %2
.
MessageId=+1 SymbolicName=EMS_DTX_PIPELINEINIT_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot initialize Pipeline
.
MessageId=+1 SymbolicName=EMS_DTX_REGISTERSINK_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot register pipeline sink
.
MessageId=+1 SymbolicName=EMS_DTX_READFROMSINK_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot read from pipeline's sink - Data Type: %1
.
MessageId=+1 SymbolicName=EMS_DTX_CREATINGNEWFILE_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot create new file - Data Type: %1
.
MessageId=+1 SymbolicName=EMS_DTX_CLOSEALLFILES_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot close all files
.
MessageId=+1 SymbolicName=EMS_DTX_INSERTTOCLOSEDLIST_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot insert file to the closed list - File Name: %1, Data Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_SENDINGFILE_NOTOK Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot send the file - File Name: %1, Data Type: %2
.
MessageId=+1 SymbolicName=EMS_DTX_AUTOWRITINGDATA_NOTOK_TIMESTAMP Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Cannot write generated data to file - Type: %1, Timestamp: %3, Error: %2
.
MessageId=+1 SymbolicName=EMS_DTX_STATICFILENOTINITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Attempting to access data transfer file for data type %1 but support for this data type was not initialized.
.
MessageId=+1 SymbolicName=EMS_DTX_NO_LOCAL_PATH Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: At initialization, no local path was specified.  
.
MessageId=+1 SymbolicName=EMS_DTX_NO_DATA_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: At initialization, no data type was specified.  
.
MessageId=+1 SymbolicName=EMS_DTX_NEW_NO_LOCAL_PATH Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed to create a new temporary file because no local path was specified.
.
MessageId=+1 SymbolicName=EMS_DTX_SEND_NO_PERIOD Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed while processing a send request.  No send period was specified.
.
MessageId=+1 SymbolicName=EMS_DTX_SEND_NO_SEND_PATH Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed while processing a send request.  No send folder was specified.
.
MessageId=+1 SymbolicName=EMS_DTX_CURRENT_FILE_EMPTY Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed while processing a send request.  The current working file name is unspecified.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error %1 occurred while reading configuration data.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_MAXSIZE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error %1 retrieving maximum file size for data type %2.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_SENDFREQ_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error %1 retrieving sending frequency for data type %2.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_LOCALPATH_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving local path.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_SENDPATH_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving send path.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_DESTS_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving destinations with error code %1.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_EMSSTRING_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving copyright string.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_COMMSSEND_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving Comms send folder.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CONFIG_SECTOKEN_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error retrieving security token for route %1.  Error code = %2.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_SITEINFO_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Error creating instance of site info object.  Error code = %1.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_SENDMSGFOLDER_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  Failed to retrieve the Comms send folder from configuration.  CM return code = %1.
.
MessageId=+1 SymbolicName=EMS_DTX_SEND_NOLOCAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during data send operation.  The Data Transfer local path could be retrieved from configuration.
.
MessageId=+1 SymbolicName=EMS_DTX_ROUTE_NOGTWY_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during data send operation.  The Gateway object could not be created.  Error code is %1.
.
MessageId=+1 SymbolicName=EMS_DTX_ROUTE_SENDDATA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during data send operation.  An error occurred sending data via the Gateway object.  Error code is %1.
.
MessageId=+1 SymbolicName=EMS_DTX_STARTED Severity=Success Facility=ITF
Language=English
EMS Data Transfer service has started.
.
MessageId=+1 SymbolicName=EMS_DTX_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer service failed to start.
.
MessageId=+1 SymbolicName=EMS_DTX_STOPPED Severity=Success Facility=ITF
Language=English
EMS Data Transfer service has stoppped.
.
MessageId=+1 SymbolicName=EMS_DTX_NO_SITEINFO Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer:  The site info object could not be created.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_SRC_LUTID_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed during initialization.  The local LUT ID could not be obtained from configuration.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_DATATYPE_CONFIGURED Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Data type (%1) is configured for collection.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_DATATYPE_RT_CONFIGURED Severity=Success Facility=ITF
Language=English
EMS Data Transfer: Data type (%1) is configured for transmission on at least one route.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_NOTYPES_CONFIGURED Severity=Success Facility=ITF
Language=English
EMS Data Transfer: No data types are configured for collection.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CM_READ_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed to read [%1].%2 from configuration.  CM returned error code %3.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CM_READ_RTE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed to read [RTE:%1].%2 from configuration.  CM returned error code %3.
.
MessageId=+1 SymbolicName=EMS_DTX_INIT_CM_NO_ROUTES Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed to read set of routes from configuration.  CM returned error code %3.
.
MessageId=+1 SymbolicName=EMS_DTX_SECINIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Data Transfer: Failed to initialize security.  Error code %1.
.
;
;#endif // INC_EMSDTMSGS


