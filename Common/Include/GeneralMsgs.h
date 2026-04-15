/********************************************************************
*	Module:			GeneralMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for General Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_GENERALMSG
#define INC_GENERALMSG

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
// MessageId: EMS_GENERAL_BASE_CODE
//
// MessageText:
//
//  General messages.
//
#define EMS_GENERAL_BASE_CODE            ((EMS_RESULT)0x0004C900L)

//
// MessageId: EMS_GENERAL_FAILURE
//
// MessageText:
//
//  A failure has occurred.  The error code is %1.
//
#define EMS_GENERAL_FAILURE              ((EMS_RESULT)0x8004C901L)

//
// MessageId: EMS_GENERAL_UNKNOWN
//
// MessageText:
//
//  A failure has occurred.  No error code could be retrieved.
//
#define EMS_GENERAL_UNKNOWN              ((EMS_RESULT)0x8004C902L)

//
// MessageId: EMS_GENERAL_CANNOT_OPEN_SCM
//
// MessageText:
//
//  A failure has occurred:  Cannot open the service control manager.
//
#define EMS_GENERAL_CANNOT_OPEN_SCM      ((EMS_RESULT)0x8004C903L)

//
// MessageId: EMS_GENERAL_CANNOT_OPEN_SERVICE
//
// MessageText:
//
//  A failure has occurred:  Cannot open (%1) service from the control manager.
//
#define EMS_GENERAL_CANNOT_OPEN_SERVICE  ((EMS_RESULT)0x8004C904L)

//
// MessageId: EMS_GENERAL_NO_CALLER_ID
//
// MessageText:
//
//  A failure has occurred:  Cannot connect to Gateway because the caller's identifier has not been specified.
//
#define EMS_GENERAL_NO_CALLER_ID         ((EMS_RESULT)0x8004C905L)

//
// MessageId: EMS_GENERAL_GATEWAY_CALL_FAILURE
//
// MessageText:
//
//  A failure has occurred:  A Gateway call has returned error code (%1) with description (%2).
//
#define EMS_GENERAL_GATEWAY_CALL_FAILURE ((EMS_RESULT)0x8004C906L)

//
// MessageId: EMS_GENERAL_INVALID_LOCALE
//
// MessageText:
//
//  Could not initialize language resources. Invalid locale.
//
#define EMS_GENERAL_INVALID_LOCALE       ((EMS_RESULT)0x8004C907L)

//
// MessageId: EMS_GENERAL_NO_DB_CONNECTION
//
// MessageText:
//
//  There is no database connection available to process this request.
//
#define EMS_GENERAL_NO_DB_CONNECTION     ((EMS_RESULT)0x8004C908L)

//
// MessageId: EMS_GENERAL_XML_FILE_LOAD_FAIL
//
// MessageText:
//
//  An error occurred attempting to load the XML file, (%1):  error code = (%2), reason = (%3), source = (%4).
//
#define EMS_GENERAL_XML_FILE_LOAD_FAIL   ((EMS_RESULT)0x8004C909L)

//
// MessageId: EMS_GENERAL_XML_LOAD_FAIL
//
// MessageText:
//
//  An error occurred attempting to load XML from a string:  error code = (%1), reason = (%2), source = (%3).
//
#define EMS_GENERAL_XML_LOAD_FAIL        ((EMS_RESULT)0x8004C90AL)

//
// MessageId: EMS_TREE_STATUS_UPDATE_FAILED
//
// MessageText:
//
//  Failed to update the LUT status displayed in the tree view.
//
#define EMS_TREE_STATUS_UPDATE_FAILED    ((EMS_RESULT)0x8004C90BL)

//
// MessageId: EMS_TREE_STATUS_INIT_FAILED
//
// MessageText:
//
//  Failed to initialize the tree view LUT status display.
//
#define EMS_TREE_STATUS_INIT_FAILED      ((EMS_RESULT)0x8004C90CL)

//
// MessageId: EMS_LUTMONITOR_LAUNCH_FAILED
//
// MessageText:
//
//  Failed to launch LUT Monitor due to error: "%1"
//
#define EMS_LUTMONITOR_LAUNCH_FAILED     ((EMS_RESULT)0x8004C90DL)

//
// MessageId: EMS_CONFIGURATION_ITEM_NOT_FOUND
//
// MessageText:
//
//  Failed to find a configuration item: "%1".
//
#define EMS_CONFIGURATION_ITEM_NOT_FOUND ((EMS_RESULT)0x8004C90EL)

//
// MessageId: EMS_NSP_ERROR
//
// MessageText:
//
//  An error has occurred in the NSP library.  Status = (%1), Function = (%2), Context = (%3), File = (%4), Line = (%5)
//
#define EMS_NSP_ERROR                    ((EMS_RESULT)0x8004C90FL)

//
// MessageId: EMS_SOAP_CALL_ERROR
//
// MessageText:
//
//  A SOAP call failed.  Fault code = %1.  Fault string = %2.  Detail = %3
//
#define EMS_SOAP_CALL_ERROR              ((EMS_RESULT)0x8004C910L)

//
// MessageId: EMS_SOAP_FRAMEWORK_ERROR
//
// MessageText:
//
//  A SOAP call failed.  The SOAP framework encountered an error with code = %1.
//
#define EMS_SOAP_FRAMEWORK_ERROR         ((EMS_RESULT)0x8004C911L)

//
// MessageId: EMS_INVALID_FILTERHEXVALUE
//
// MessageText:
//
//  Failed to build query.  Invalid hex filter value specified.
//
#define EMS_INVALID_FILTERHEXVALUE       ((EMS_RESULT)0x8004C912L)


#endif
