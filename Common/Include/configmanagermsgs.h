/********************************************************************
*	Module:			configmanagermsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for config manager
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2003-2005 by EMS Technologies, Inc.,
* All rights reserved
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

	0.0	2003Oct03		FJP	start 

********************************************************************/
#ifndef INC_CONFIGMANAGERMSGS
#define INC_CONFIGMANAGERMSGS

#include "emserror.h"

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
// MessageId: EMS_CM_BASE_CODE
//
// MessageText:
//
//  EMS CM Error
//
#define EMS_CM_BASE_CODE                 ((EMS_RESULT)0x0004B700L)

//
// MessageId: EMS_CM_SERVICE_START
//
// MessageText:
//
//  EMS CM Service Started
//
#define EMS_CM_SERVICE_START             ((EMS_RESULT)0x0004B701L)

//
// MessageId: EMS_CM_SERVICE_STOP
//
// MessageText:
//
//  EMS CM Service Stopped
//
#define EMS_CM_SERVICE_STOP              ((EMS_RESULT)0x0004B702L)

//
// MessageId: EMS_CM_SERVICE_FAILED
//
// MessageText:
//
//  EMS CM Service did not start due to error %1
//
#define EMS_CM_SERVICE_FAILED            ((EMS_RESULT)0x8004B703L)

//
// MessageId: EMS_CM_ERROR
//
// MessageText:
//
//  EMS CM Error:  %1
//
#define EMS_CM_ERROR                     ((EMS_RESULT)0x8004B704L)

//
// MessageId: EMS_CM_EXCEPTION
//
// MessageText:
//
//  EMS CM exception has occurred:  %1
//
#define EMS_CM_EXCEPTION                 ((EMS_RESULT)0x8004B705L)

//
// MessageId: EMS_CM_TRACE_MSG
//
// MessageText:
//
//  EMS CM trace message:  %1
//
#define EMS_CM_TRACE_MSG                 ((EMS_RESULT)0x0004B706L)

//
// MessageId: EMS_CM_INVALID_SYS_CFG_FILE
//
// MessageText:
//
//  EMS CM Error:  Error reading CM system configuration file.
//
#define EMS_CM_INVALID_SYS_CFG_FILE      ((EMS_RESULT)0x8004B707L)

//
// MessageId: EMS_CM_INVALID_SCHEMA_FILE
//
// MessageText:
//
//  EMS CM Error:  Error reading schema file (%1).
//
#define EMS_CM_INVALID_SCHEMA_FILE       ((EMS_RESULT)0x8004B708L)

//
// MessageId: EMS_CM_INVALID_DATA_FILE
//
// MessageText:
//
//  EMS CM could not read data file (%1).
//
#define EMS_CM_INVALID_DATA_FILE         ((EMS_RESULT)0x0004B709L)

//
// MessageId: EMS_CM_INVALID_GROUP_TYPE
//
// MessageText:
//
//  EMS CM Error:  Invalid group type (%1).
//
#define EMS_CM_INVALID_GROUP_TYPE        ((EMS_RESULT)0x8004B70AL)

//
// MessageId: EMS_CM_INVALID_GROUP_ID
//
// MessageText:
//
//  EMS CM Error:  Invalid group ID (%1).
//
#define EMS_CM_INVALID_GROUP_ID          ((EMS_RESULT)0x8004B70BL)

//
// MessageId: EMS_CM_INVALID_KEY_NAME
//
// MessageText:
//
//  EMS CM Error:  Invalid key name (%1).
//
#define EMS_CM_INVALID_KEY_NAME          ((EMS_RESULT)0x8004B70CL)

//
// MessageId: EMS_CM_INVALID_DATA
//
// MessageText:
//
//  EMS CM Error:  Invalid configuration data (key = %1).
//
#define EMS_CM_INVALID_DATA              ((EMS_RESULT)0x8004B70DL)

//
// MessageId: EMS_CM_INVALID_LEVEL
//
// MessageText:
//
//  EMS CM Error:  Invalid level (%1).
//
#define EMS_CM_INVALID_LEVEL             ((EMS_RESULT)0x8004B70EL)

//
// MessageId: EMS_CM_NO_DATA
//
// MessageText:
//
//  EMS CM Error:  Unable to retrieve configuration data (key = %1).
//
#define EMS_CM_NO_DATA                   ((EMS_RESULT)0x8004B70FL)

//
// MessageId: EMS_CM_PIPELINE_INIT_ERR
//
// MessageText:
//
//  EMS CM Error: Failed to instantiate pipeline (%1).
//
#define EMS_CM_PIPELINE_INIT_ERR         ((EMS_RESULT)0x8004B710L)

//
// MessageId: EMS_CM_CMDSINK_INIT_ERR
//
// MessageText:
//
//  EMS CM Error: Failed to instantiate command sink.
//
#define EMS_CM_CMDSINK_INIT_ERR          ((EMS_RESULT)0x8004B711L)

//
// MessageId: EMS_CM_CMDSINK_REG_ERR
//
// MessageText:
//
//  EMS CM Error: Failed to register command sink (%1).
//
#define EMS_CM_CMDSINK_REG_ERR           ((EMS_RESULT)0x8004B712L)

//
// MessageId: EMS_CM_INIT_UNK_ERR
//
// MessageText:
//
//  EMS CM Error: Service failed to start. Unhandled exception.
//
#define EMS_CM_INIT_UNK_ERR              ((EMS_RESULT)0x8004B713L)

//
// MessageId: EMS_CM_INVALID_VALUE_ASSIGNMENT
//
// MessageText:
//
//  Attempt to assign an invalid value to [%1] %2 (level=%3) data value: %4
//
#define EMS_CM_INVALID_VALUE_ASSIGNMENT  ((EMS_RESULT)0x8004B714L)

//
// MessageId: EMS_CM_NONEXISTANT_DATA_FILE
//
// MessageText:
//
//  EMS CM data file does not exist (%1).
//
#define EMS_CM_NONEXISTANT_DATA_FILE     ((EMS_RESULT)0x8004B715L)

//
// MessageId: EMS_CM_JOURNALIZE_FAILED
//
// MessageText:
//
//  Could not journalize entry [%1:%2] %3 (error: %4)
//
#define EMS_CM_JOURNALIZE_FAILED         ((EMS_RESULT)0x0004B716L)

//
// MessageId: EMS_CM_NOT_INITIALIZED
//
// MessageText:
//
//  EMS CM Error: Could not process request. Configuration manager has not been initialized.
//
#define EMS_CM_NOT_INITIALIZED           ((EMS_RESULT)0x0004B717L)

//
// MessageId: EMS_CM_GETCONFIGGROUP_ERR
//
// MessageText:
//
//  EMS CM: Could not access specified configuration data group.
//
#define EMS_CM_GETCONFIGGROUP_ERR        ((EMS_RESULT)0x8004B718L)

//
// MessageId: EMS_CM_SETDATA_ERR
//
// MessageText:
//
//  EMS CM: Configuration data items not saved.
//
#define EMS_CM_SETDATA_ERR               ((EMS_RESULT)0x8004B719L)

//
// MessageId: EMS_CM_INVALIDSYSTEMCFGFILE
//
// MessageText:
//
//  EMS CM: Invalid system configuration file.
//
#define EMS_CM_INVALIDSYSTEMCFGFILE      ((EMS_RESULT)0x8004B71AL)

//
// MessageId: EMS_CM_CMSYSCONFIGINITFAILED
//
// MessageText:
//
//  EMS CM: Could not load the system configuration file.
//
#define EMS_CM_CMSYSCONFIGINITFAILED     ((EMS_RESULT)0x8004B71BL)

//
// MessageId: EMS_CM_INVALID_SYS_CFG_FILE_DETAILS
//
// MessageText:
//
//  EMS CM Error:  Error reading CM system configuration file (%1) (%2).
//
#define EMS_CM_INVALID_SYS_CFG_FILE_DETAILS ((EMS_RESULT)0x8004B71CL)

//
// MessageId: EMS_CM_INVALID_DATA_ENCOUNTERED
//
// MessageText:
//
//  EMS CM Error:  Invalid data encountered during processing.
//
#define EMS_CM_INVALID_DATA_ENCOUNTERED  ((EMS_RESULT)0x8004B71DL)

//
// MessageId: EMS_CM_INVALID_INI_KEY
//
// MessageText:
//
//  EMS CM Error:  Invalid key name "%1" found in "%2".
//
#define EMS_CM_INVALID_INI_KEY           ((EMS_RESULT)0x8004B71EL)

//
// MessageId: EMS_CM_INI_ERROR
//
// MessageText:
//
//  EMS CM Error:  An error occured while loading "%1".
//
#define EMS_CM_INI_ERROR                 ((EMS_RESULT)0x8004B71FL)

//
// MessageId: EMS_CM_JOURNALIZE_EXCEPTION
//
// MessageText:
//
//  EMS CM Error:  Exception while attempting to journalize initial configuration.
//
#define EMS_CM_JOURNALIZE_EXCEPTION      ((EMS_RESULT)0x8004B720L)


#endif // INC_CONFIGMANAGERMSGS
