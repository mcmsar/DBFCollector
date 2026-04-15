/********************************************************************
*	Module:			EMSSecMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Data Transfer Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Dec04		CH		start 

********************************************************************/
#ifndef INC_EMSDTSGS
#define INC_EMSDTMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: EMS_DTX_BASE_CODE
//
// MessageText:
//
//  EMS Data Transfer Error
//
#define EMS_DTX_BASE_CODE                ((EMS_RESULT)0x0004AF00L)

//
// MessageId: EMS_DTX_GENERAL_ERROR
//
// MessageText:
//
//  EMS Data Transfer Access Denied %1
//
#define EMS_DTX_GENERAL_ERROR            ((EMS_RESULT)0x8004AF01L)

//
// MessageId: EMS_DTX_TRACE
//
// MessageText:
//
//  EMS Data Transfer reports trace %1
//
#define EMS_DTX_TRACE                    ((EMS_RESULT)0x0004AF02L)

//
// MessageId: EMS_DTX_INFO
//
// MessageText:
//
//  EMS Data Transfer Info %1
//
#define EMS_DTX_INFO                     ((EMS_RESULT)0x0004AF03L)

//
// MessageId: EMS_DTX_DEBUG
//
// MessageText:
//
//  EMS Data Transfer debug message %1
//
#define EMS_DTX_DEBUG                    ((EMS_RESULT)0x0004AF04L)

//
// MessageId: EMS_DTX_NO_TYPES
//
// MessageText:
//
//  EMS Data Transfer the supported types list is empty %1
//
#define EMS_DTX_NO_TYPES                 ((EMS_RESULT)0x8004AF05L)

//
// MessageId: EMS_DTX_INIT_ERROR
//
// MessageText:
//
//  EMS Data Transfer Initialization error %1
//
#define EMS_DTX_INIT_ERROR               ((EMS_RESULT)0x8004AF06L)

//
// MessageId: EMS_DTX_ADD_DEST_ERROR
//
// MessageText:
//
//  EMS Data Transfer Error Cannot add the destination information %1
//
#define EMS_DTX_ADD_DEST_ERROR           ((EMS_RESULT)0x8004AF07L)

//
// MessageId: EMS_DTX_SECURITY_ERROR
//
// MessageText:
//
//  EMS Data Transfer Error Cannot retrieve the security token %1
//
#define EMS_DTX_SECURITY_ERROR           ((EMS_RESULT)0x8004AF08L)

//
// MessageId: EMS_DTX_DAL_ERROR
//
// MessageText:
//
//  EMS Data Transfer Error retrieving data from the DAL %1
//
#define EMS_DTX_DAL_ERROR                ((EMS_RESULT)0x8004AF09L)

//
// MessageId: EMS_DTX_DATATOOBIG_ERROR
//
// MessageText:
//
//  EMS Data Transfer Error data requested is too big %1
//
#define EMS_DTX_DATATOOBIG_ERROR         ((EMS_RESULT)0x8004AF0AL)

//
// MessageId: EMS_DTX_CREATEFILE_ERR
//
// MessageText:
//
//  EMS Data Transfer Error creating the file %1
//
#define EMS_DTX_CREATEFILE_ERR           ((EMS_RESULT)0x8004AF0BL)

//
// MessageId: EMS_DTX_WRITEHEADER_ERR
//
// MessageText:
//
//  EMS Data Transfer Error writing the file header %1
//
#define EMS_DTX_WRITEHEADER_ERR          ((EMS_RESULT)0x8004AF0CL)

//
// MessageId: EMS_DTX_ADDRECORD_ERR
//
// MessageText:
//
//  EMS Data Transfer Error adding the record to the file %1
//
#define EMS_DTX_ADDRECORD_ERR            ((EMS_RESULT)0x8004AF0DL)

//
// MessageId: EMS_DTX_COPYFILE_ERR
//
// MessageText:
//
//  EMS Data Transfer Error copying the file %1
//
#define EMS_DTX_COPYFILE_ERR             ((EMS_RESULT)0x8004AF0EL)

//
// MessageId: EMS_DTX_NOSTATICFILE_ERR
//
// MessageText:
//
//  EMS Data Transfer Error: no file available in the static file list for the automatic data transfer %1
//
#define EMS_DTX_NOSTATICFILE_ERR         ((EMS_RESULT)0x8004AF0FL)

//
// MessageId: EMS_DTX_REGSINK_ERR
//
// MessageText:
//
//  EMS Data Transfer Error registering pipeline sink%1
//
#define EMS_DTX_REGSINK_ERR              ((EMS_RESULT)0x8004AF10L)

//
// MessageId: EMS_DTX_DATATYPEMISSING_ERR
//
// MessageText:
//
//  EMS Data Transfer Error cannot find data type information %1
//
#define EMS_DTX_DATATYPEMISSING_ERR      ((EMS_RESULT)0x8004AF11L)

//
// MessageId: EMS_DTX_NORECORDS_ERR
//
// MessageText:
//
//  EMS Data Transfer Error: no records found %1
//
#define EMS_DTX_NORECORDS_ERR            ((EMS_RESULT)0x8004AF12L)

//
// MessageId: EMS_DTX_INIT_ERR
//
// MessageText:
//
//  EMS Data Transfer: Cannot initialize the Data Transfer Subsystem
//
#define EMS_DTX_INIT_ERR                 ((EMS_RESULT)0x8004AF13L)

//
// MessageId: EMS_DTX_INIT
//
// MessageText:
//
//  EMS Data Transfer: Data Transfer Subsystem initialized
//
#define EMS_DTX_INIT                     ((EMS_RESULT)0x0004AF14L)

//
// MessageId: EMS_DTX_UPLOADRECEIVED
//
// MessageText:
//
//  EMS Data Transfer: Received Upload request - Destination:%1, Record Type: %2
//
#define EMS_DTX_UPLOADRECEIVED           ((EMS_RESULT)0x0004AF15L)

//
// MessageId: EMS_DTX_RETRIEVINGDATA_OK
//
// MessageText:
//
//  EMS Data Transfer: Retrieving Data from DAL is OK - Destination:%1, Record Type: %2
//
#define EMS_DTX_RETRIEVINGDATA_OK        ((EMS_RESULT)0x0004AF16L)

//
// MessageId: EMS_DTX_WRITINGDATA_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot write the data retrieved from DAL - Destination:%1, Record Type: %2
//
#define EMS_DTX_WRITINGDATA_NOTOK        ((EMS_RESULT)0x8004AF17L)

//
// MessageId: EMS_DTX_WRITINGDATA_OK
//
// MessageText:
//
//  EMS Data Transfer: Writing Data retrieved from DAL is OK - Destination:%1, Record Type: %2
//
#define EMS_DTX_WRITINGDATA_OK           ((EMS_RESULT)0x0004AF18L)

//
// MessageId: EMS_DTX_RETREIVINGDATA_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot retrieve Data from DAL - Destination:%1, Record Type: %2, Error: %3
//
#define EMS_DTX_RETREIVINGDATA_NOTOK     ((EMS_RESULT)0x8004AF19L)

//
// MessageId: EMS_DTX_AUTOWRITINGDATA_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot write the automatically generated data - Data Type: %1, Error: %2
//
#define EMS_DTX_AUTOWRITINGDATA_NOTOK    ((EMS_RESULT)0x8004AF1AL)

//
// MessageId: EMS_DTX_PIPELINEINIT_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot initialize Pipeline
//
#define EMS_DTX_PIPELINEINIT_NOTOK       ((EMS_RESULT)0x8004AF1BL)

//
// MessageId: EMS_DTX_REGISTERSINK_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot register pipeline sink
//
#define EMS_DTX_REGISTERSINK_NOTOK       ((EMS_RESULT)0x8004AF1CL)

//
// MessageId: EMS_DTX_READFROMSINK_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot read from pipeline's sink - Data Type: %1
//
#define EMS_DTX_READFROMSINK_NOTOK       ((EMS_RESULT)0x8004AF1DL)

//
// MessageId: EMS_DTX_CREATINGNEWFILE_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot create new file - Data Type: %1
//
#define EMS_DTX_CREATINGNEWFILE_NOTOK    ((EMS_RESULT)0x8004AF1EL)

//
// MessageId: EMS_DTX_CLOSEALLFILES_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot close all files
//
#define EMS_DTX_CLOSEALLFILES_NOTOK      ((EMS_RESULT)0x8004AF1FL)

//
// MessageId: EMS_DTX_INSERTTOCLOSEDLIST_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot insert file to the closed list - File Name: %1, Data Type: %2
//
#define EMS_DTX_INSERTTOCLOSEDLIST_NOTOK ((EMS_RESULT)0x8004AF20L)

//
// MessageId: EMS_DTX_SENDINGFILE_NOTOK
//
// MessageText:
//
//  EMS Data Transfer: Cannot send the file - File Name: %1, Data Type: %2
//
#define EMS_DTX_SENDINGFILE_NOTOK        ((EMS_RESULT)0x8004AF21L)

//
// MessageId: EMS_DTX_AUTOWRITINGDATA_NOTOK_TIMESTAMP
//
// MessageText:
//
//  EMS Data Transfer: Cannot write generated data to file - Type: %1, Timestamp: %3, Error: %2
//
#define EMS_DTX_AUTOWRITINGDATA_NOTOK_TIMESTAMP ((EMS_RESULT)0x8004AF22L)

//
// MessageId: EMS_DTX_STATICFILENOTINITIALIZED
//
// MessageText:
//
//  EMS Data Transfer: Attempting to access data transfer file for data type %1 but support for this data type was not initialized.
//
#define EMS_DTX_STATICFILENOTINITIALIZED ((EMS_RESULT)0x8004AF23L)

//
// MessageId: EMS_DTX_NO_LOCAL_PATH
//
// MessageText:
//
//  EMS Data Transfer: At initialization, no local path was specified.  
//
#define EMS_DTX_NO_LOCAL_PATH            ((EMS_RESULT)0x8004AF24L)

//
// MessageId: EMS_DTX_NO_DATA_TYPE
//
// MessageText:
//
//  EMS Data Transfer: At initialization, no data type was specified.  
//
#define EMS_DTX_NO_DATA_TYPE             ((EMS_RESULT)0x8004AF25L)

//
// MessageId: EMS_DTX_NEW_NO_LOCAL_PATH
//
// MessageText:
//
//  EMS Data Transfer: Failed to create a new temporary file because no local path was specified.
//
#define EMS_DTX_NEW_NO_LOCAL_PATH        ((EMS_RESULT)0x8004AF26L)

//
// MessageId: EMS_DTX_SEND_NO_PERIOD
//
// MessageText:
//
//  EMS Data Transfer: Failed while processing a send request.  No send period was specified.
//
#define EMS_DTX_SEND_NO_PERIOD           ((EMS_RESULT)0x8004AF27L)

//
// MessageId: EMS_DTX_SEND_NO_SEND_PATH
//
// MessageText:
//
//  EMS Data Transfer: Failed while processing a send request.  No send folder was specified.
//
#define EMS_DTX_SEND_NO_SEND_PATH        ((EMS_RESULT)0x8004AF28L)

//
// MessageId: EMS_DTX_CURRENT_FILE_EMPTY
//
// MessageText:
//
//  EMS Data Transfer: Failed while processing a send request.  The current working file name is unspecified.
//
#define EMS_DTX_CURRENT_FILE_EMPTY       ((EMS_RESULT)0x8004AF29L)

//
// MessageId: EMS_DTX_INIT_CONFIG_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error %1 occurred while reading configuration data.
//
#define EMS_DTX_INIT_CONFIG_FAILURE      ((EMS_RESULT)0x8004AF2AL)

//
// MessageId: EMS_DTX_INIT_CONFIG_MAXSIZE_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error %1 retrieving maximum file size for data type %2.
//
#define EMS_DTX_INIT_CONFIG_MAXSIZE_FAILURE ((EMS_RESULT)0x8004AF2BL)

//
// MessageId: EMS_DTX_INIT_CONFIG_SENDFREQ_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error %1 retrieving sending frequency for data type %2.
//
#define EMS_DTX_INIT_CONFIG_SENDFREQ_FAILURE ((EMS_RESULT)0x8004AF2CL)

//
// MessageId: EMS_DTX_INIT_CONFIG_LOCALPATH_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving local path.
//
#define EMS_DTX_INIT_CONFIG_LOCALPATH_FAILURE ((EMS_RESULT)0x8004AF2DL)

//
// MessageId: EMS_DTX_INIT_CONFIG_SENDPATH_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving send path.
//
#define EMS_DTX_INIT_CONFIG_SENDPATH_FAILURE ((EMS_RESULT)0x8004AF2EL)

//
// MessageId: EMS_DTX_INIT_CONFIG_DESTS_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving destinations with error code %1.
//
#define EMS_DTX_INIT_CONFIG_DESTS_FAILURE ((EMS_RESULT)0x8004AF2FL)

//
// MessageId: EMS_DTX_INIT_CONFIG_EMSSTRING_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving copyright string.
//
#define EMS_DTX_INIT_CONFIG_EMSSTRING_FAILURE ((EMS_RESULT)0x8004AF30L)

//
// MessageId: EMS_DTX_INIT_CONFIG_COMMSSEND_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving Comms send folder.
//
#define EMS_DTX_INIT_CONFIG_COMMSSEND_FAILURE ((EMS_RESULT)0x8004AF31L)

//
// MessageId: EMS_DTX_INIT_CONFIG_SECTOKEN_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error retrieving security token for route %1.  Error code = %2.
//
#define EMS_DTX_INIT_CONFIG_SECTOKEN_FAILURE ((EMS_RESULT)0x8004AF32L)

//
// MessageId: EMS_DTX_INIT_SITEINFO_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Error creating instance of site info object.  Error code = %1.
//
#define EMS_DTX_INIT_SITEINFO_FAILURE    ((EMS_RESULT)0x8004AF33L)

//
// MessageId: EMS_DTX_INIT_SENDMSGFOLDER_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  Failed to retrieve the Comms send folder from configuration.  CM return code = %1.
//
#define EMS_DTX_INIT_SENDMSGFOLDER_FAILURE ((EMS_RESULT)0x8004AF34L)

//
// MessageId: EMS_DTX_SEND_NOLOCAL_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during data send operation.  The Data Transfer local path could be retrieved from configuration.
//
#define EMS_DTX_SEND_NOLOCAL_FAILURE     ((EMS_RESULT)0x8004AF35L)

//
// MessageId: EMS_DTX_ROUTE_NOGTWY_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during data send operation.  The Gateway object could not be created.  Error code is %1.
//
#define EMS_DTX_ROUTE_NOGTWY_FAILURE     ((EMS_RESULT)0x8004AF36L)

//
// MessageId: EMS_DTX_ROUTE_SENDDATA_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during data send operation.  An error occurred sending data via the Gateway object.  Error code is %1.
//
#define EMS_DTX_ROUTE_SENDDATA_FAILURE   ((EMS_RESULT)0x8004AF37L)

//
// MessageId: EMS_DTX_STARTED
//
// MessageText:
//
//  EMS Data Transfer service has started.
//
#define EMS_DTX_STARTED                  ((EMS_RESULT)0x0004AF38L)

//
// MessageId: EMS_DTX_START_FAILED
//
// MessageText:
//
//  EMS Data Transfer service failed to start.
//
#define EMS_DTX_START_FAILED             ((EMS_RESULT)0x8004AF39L)

//
// MessageId: EMS_DTX_STOPPED
//
// MessageText:
//
//  EMS Data Transfer service has stoppped.
//
#define EMS_DTX_STOPPED                  ((EMS_RESULT)0x0004AF3AL)

//
// MessageId: EMS_DTX_NO_SITEINFO
//
// MessageText:
//
//  EMS Data Transfer:  The site info object could not be created.
//
#define EMS_DTX_NO_SITEINFO              ((EMS_RESULT)0x8004AF3BL)

//
// MessageId: EMS_DTX_INIT_SRC_LUTID_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed during initialization.  The local LUT ID could not be obtained from configuration.
//
#define EMS_DTX_INIT_SRC_LUTID_FAILURE   ((EMS_RESULT)0x8004AF3CL)

//
// MessageId: EMS_DTX_INIT_DATATYPE_CONFIGURED
//
// MessageText:
//
//  EMS Data Transfer: Data type (%1) is configured for collection.
//
#define EMS_DTX_INIT_DATATYPE_CONFIGURED ((EMS_RESULT)0x0004AF3DL)

//
// MessageId: EMS_DTX_INIT_DATATYPE_RT_CONFIGURED
//
// MessageText:
//
//  EMS Data Transfer: Data type (%1) is configured for transmission on at least one route.
//
#define EMS_DTX_INIT_DATATYPE_RT_CONFIGURED ((EMS_RESULT)0x0004AF3EL)

//
// MessageId: EMS_DTX_INIT_NOTYPES_CONFIGURED
//
// MessageText:
//
//  EMS Data Transfer: No data types are configured for collection.
//
#define EMS_DTX_INIT_NOTYPES_CONFIGURED  ((EMS_RESULT)0x0004AF3FL)

//
// MessageId: EMS_DTX_INIT_CM_READ_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed to read [%1].%2 from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_READ_FAILURE     ((EMS_RESULT)0x8004AF40L)

//
// MessageId: EMS_DTX_INIT_CM_READ_RTE_FAILURE
//
// MessageText:
//
//  EMS Data Transfer: Failed to read [RTE:%1].%2 from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_READ_RTE_FAILURE ((EMS_RESULT)0x8004AF41L)

//
// MessageId: EMS_DTX_INIT_CM_NO_ROUTES
//
// MessageText:
//
//  EMS Data Transfer: Failed to read set of routes from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_NO_ROUTES        ((EMS_RESULT)0x8004AF42L)

//
// MessageId: EMS_DTX_SECINIT_FAILED
//
// MessageText:
//
//  EMS Data Transfer: Failed to initialize security.  Error code %1.
//
#define EMS_DTX_SECINIT_FAILED           ((EMS_RESULT)0x8004AF43L)


#endif // INC_EMSDTMSGS
