/********************************************************************
*	Module:			JrnlMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS DB Journal Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_JRNLMSGS
#define INC_JRNLMSGS

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
// MessageId: EMS_DBJOURNAL_BASE_CODE
//
// MessageText:
//
//  EMS DB Journal Error
//
#define EMS_DBJOURNAL_BASE_CODE          ((EMS_RESULT)0x0004A100L)

//
// MessageId: EMS_JRNL_SERVICE_START
//
// MessageText:
//
//  EMS DB Journal Service Started
//
#define EMS_JRNL_SERVICE_START           ((EMS_RESULT)0x0004A101L)

//
// MessageId: EMS_JRNL_SERVICE_STOP
//
// MessageText:
//
//  EMS DB Journal Service Stopped
//
#define EMS_JRNL_SERVICE_STOP            ((EMS_RESULT)0x0004A102L)

//
// MessageId: EMS_JRNL_ERROR
//
// MessageText:
//
//  EMS DB Journal reports error %1.
//
#define EMS_JRNL_ERROR                   ((EMS_RESULT)0x8004A103L)

//
// MessageId: EMS_JRNL_DB_ERROR
//
// MessageText:
//
//  EMS DB Journal reports error %1 while accessing database record %2.
//
#define EMS_JRNL_DB_ERROR                ((EMS_RESULT)0x8004A104L)

//
// MessageId: EMS_JRNL_TRACER
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( %1 )
//
#define EMS_JRNL_TRACER                  ((EMS_RESULT)0x0004A105L)

//
// MessageId: EMS_JRNL_TLEDUPKEY
//
// MessageText:
//
//  EMS DB Journal Service reports duplicate primary key writing satellite %1 data to ORBIT_DATA table.
//
#define EMS_JRNL_TLEDUPKEY               ((EMS_RESULT)0x0004A106L)

//
// MessageId: EMS_JRNL_START_DBCLEAN
//
// MessageText:
//
//  EMS DB Journal Starting Database Clean.
//
#define EMS_JRNL_START_DBCLEAN           ((EMS_RESULT)0x0004A107L)

//
// MessageId: EMS_JRNL_STOP_DBCLEAN
//
// MessageText:
//
//  EMS DB Journal Finished Database Clean.
//
#define EMS_JRNL_STOP_DBCLEAN            ((EMS_RESULT)0x0004A108L)

//
// MessageId: EMS_JRNL_TRACER_AUDIORIFFDATA
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( BeaconID=%1, time=%2, Sat ID=%3, Lut ID=%4 )
//
#define EMS_JRNL_TRACER_AUDIORIFFDATA    ((EMS_RESULT)0x0004A109L)

//
// MessageId: EMS_JRNL_TRACER_LOCATEDATA
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( time=%1, type=%2, ID=%3 )
//
#define EMS_JRNL_TRACER_LOCATEDATA       ((EMS_RESULT)0x0004A10AL)

//
// MessageId: EMS_JRNL_TRACER_CALIBCBC
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
//
#define EMS_JRNL_TRACER_CALIBCBC         ((EMS_RESULT)0x0004A10BL)

//
// MessageId: EMS_JRNL_TRACER_RESIDUALDATA
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
//
#define EMS_JRNL_TRACER_RESIDUALDATA     ((EMS_RESULT)0x0004A10CL)

//
// MessageId: EMS_JRNL_TRACER_DBCLEAN
//
// MessageText:
//
//  EMS DB Journal Service Tracer ( DBClean returns %1 )
//
#define EMS_JRNL_TRACER_DBCLEAN          ((EMS_RESULT)0x0004A10DL)

//
// MessageId: EMS_JRNL_INIT_EXCEPTION
//
// MessageText:
//
//  EMS DB Journal initialization failed with an unhandled exception.
//
#define EMS_JRNL_INIT_EXCEPTION          ((EMS_RESULT)0x8004A10EL)

//
// MessageId: EMS_JRNL_DB_ERROR_DUPKEY
//
// MessageText:
//
//  EMS DB Journal reports a duplicate primary key error (%1).
//
#define EMS_JRNL_DB_ERROR_DUPKEY         ((EMS_RESULT)0x8004A10FL)


#endif // INC_JRNLMSGS
