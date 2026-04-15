/********************************************************************
*	Module:			HealthMonitorMsgs.mc
*	Description: 	Message File for the Health Monitoring Service
*
*********************************************************************
*	Copyright (c) 2009 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_HMMSGS
#define INC_HMMSGS

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
// MessageId: EMS_HM_BASE_CODE
//
// MessageText:
//
//  EMS Health Monitor Service Error
//
#define EMS_HM_BASE_CODE                 ((EMS_RESULT)0x0004EF50L)

//
// MessageId: EMS_HM_SERVICE_START
//
// MessageText:
//
//  EMS Health Monitor Service Started
//
#define EMS_HM_SERVICE_START             ((EMS_RESULT)0x0004EF51L)

//
// MessageId: EMS_HM_SERVICE_FAILED
//
// MessageText:
//
//  EMS Health Monitor Service did not start due to error %1
//
#define EMS_HM_SERVICE_FAILED            ((EMS_RESULT)0x8004EF52L)

//
// MessageId: EMS_HM_SERVICE_STOP
//
// MessageText:
//
//  EMS Health Monitor Service Stopped
//
#define EMS_HM_SERVICE_STOP              ((EMS_RESULT)0x0004EF53L)

//
// MessageId: EMS_HM_ERROR
//
// MessageText:
//
//  EMS Health Monitor Service reports error %1.
//
#define EMS_HM_ERROR                     ((EMS_RESULT)0x8004EF54L)

//
// MessageId: EMS_HM_TRACER
//
// MessageText:
//
//  EMS Health Monitor Service Trace (%1).
//
#define EMS_HM_TRACER                    ((EMS_RESULT)0x0004EF55L)

//
// MessageId: EMS_HM_UNEXPECTED_EXCEPTION
//
// MessageText:
//
//  EMS Health Monitor Service detected an unexepcted exception.
//
#define EMS_HM_UNEXPECTED_EXCEPTION      ((EMS_RESULT)0x8004EF56L)

//
// MessageId: EMS_HM_RECEIVECALIB406_ERROR
//
// MessageText:
//
//  EMS Health Monitor Service detected an error while receiving calib406 data for processing.
//
#define EMS_HM_RECEIVECALIB406_ERROR     ((EMS_RESULT)0x8004EF57L)

//
// MessageId: EMS_HM_RECEIVELOGDATA_ERROR
//
// MessageText:
//
//  EMS Health Monitor Service detected an error while receiving calib406 data for processing.
//
#define EMS_HM_RECEIVELOGDATA_ERROR      ((EMS_RESULT)0x8004EF58L)


#endif // INC_HMMSGS
