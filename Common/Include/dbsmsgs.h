/********************************************************************
*	Module:			DBSMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for LeoLut600DBS Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	03/01/24		jb		start

********************************************************************/
#ifndef INC_DBSMSGS
#define INC_DBSMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

// EMSLEO600DBS_E_DUPLICATE_KEY to retain original numeric value:
//		MAKE_HRESULT( SEVERITY_ERROR, FACILITY_ITF, 0x7400 ) 
// Define first, before the base code, so that new 
// messages can use the +1 syntax
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
// MessageId: EMSLEO600DBS_E_DUPLICATE_KEY
//
// MessageText:
//
//  EMS LeoLut600 Database: Insert failed due to duplicate primary key.
//
#define EMSLEO600DBS_E_DUPLICATE_KEY     ((EMS_RESULT)0x80047400L)

//
// MessageId: EMS_DBS_BASE_CODE
//
// MessageText:
//
//  EMS LeoLut600 Database
//
#define EMS_DBS_BASE_CODE                ((EMS_RESULT)0x8004BF00L)

//
// MessageId: EMS_DBS_ERROR
//
// MessageText:
//
//  Error %1 occurred while accessing %2.
//
#define EMS_DBS_ERROR                    ((EMS_RESULT)0x8004BF01L)

//
// MessageId: EMS_DBS_ADO_EXCEPTION
//
// MessageText:
//
//  An ADO exception occurred while accessing %1:  error code = %2, description = %3, source = %4.
//
#define EMS_DBS_ADO_EXCEPTION            ((EMS_RESULT)0x8004BF02L)

//
// MessageId: EMS_DBS_SQL
//
// MessageText:
//
//  The following SQL statement failed during execution:  %1.
//
#define EMS_DBS_SQL                      ((EMS_RESULT)0x8004BF03L)

//
// MessageId: EMS_DBS_SERVICE_DELETE_ERR
//
// MessageText:
//
//  EMS LeoLut600 Database: Service could not be deleted.
//
#define EMS_DBS_SERVICE_DELETE_ERR       ((EMS_RESULT)0x8004BF04L)

//
// MessageId: EMS_DBS_HANDLERNOTINSTALLED
//
// MessageText:
//
//  EMS LeoLut600 Database: Handler not installed
//
#define EMS_DBS_HANDLERNOTINSTALLED      ((EMS_RESULT)0x8004BF05L)

//
// MessageId: EMS_DBS_SERVICESTOPPED
//
// MessageText:
//
//  EMS LeoLut600 Database: Service stopped
//
#define EMS_DBS_SERVICESTOPPED           ((EMS_RESULT)0x0004BF06L)

//
// MessageId: EMS_DBS_SERVICESTARTED
//
// MessageText:
//
//  EMS LeoLut600 Database: Service started
//
#define EMS_DBS_SERVICESTARTED           ((EMS_RESULT)0x0004BF07L)

//
// MessageId: EMS_DBS_BADSERVICEREQUEST
//
// MessageText:
//
//  EMS LeoLut600 Database: Bad service request received.
//
#define EMS_DBS_BADSERVICEREQUEST        ((EMS_RESULT)0x8004BF08L)

//
// MessageId: EMS_DBS_SMOPEN_ERR
//
// MessageText:
//
//  Couldn't open service manager
//
#define EMS_DBS_SMOPEN_ERR               ((EMS_RESULT)0x8004BF09L)

//
// MessageId: EMS_DBS_CREATESERVICE_ERR
//
// MessageText:
//
//  Couldn't create service
//
#define EMS_DBS_CREATESERVICE_ERR        ((EMS_RESULT)0x8004BF0AL)

//
// MessageId: EMS_DBS_OPENSERVICE_ERR
//
// MessageText:
//
//  Couldn't open service
//
#define EMS_DBS_OPENSERVICE_ERR          ((EMS_RESULT)0x8004BF0BL)

//
// MessageId: EMS_DBS_E_NOTABLE
//
// MessageText:
//
//  EMS LeoLut600 Database: Invalid column or table name specified. Please confirm that your database has been upgraded to the latest version.
//
#define EMS_DBS_E_NOTABLE                ((EMS_RESULT)0x8004BF0CL)


#endif // INC_DBSMSGS
