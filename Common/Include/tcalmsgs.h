/********************************************************************
*	Module:			TCalMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS TCAL Messages
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
#ifndef INC_TCALMSGS
#define INC_TCALMSGS

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
// MessageId: EMS_TCAL_BASE_CODE
//
// MessageText:
//
//  EMS TCAL Error
//
#define EMS_TCAL_BASE_CODE               ((EMS_RESULT)0x0004AC00L)

//
// MessageId: EMS_TCAL_SERVICE_START
//
// MessageText:
//
//  EMS TCAL Service Started
//
#define EMS_TCAL_SERVICE_START           ((EMS_RESULT)0x0004AC01L)

//
// MessageId: EMS_TCAL_SERVICE_FAILED
//
// MessageText:
//
//  EMS TCAL Service did not start due to error %1
//
#define EMS_TCAL_SERVICE_FAILED          ((EMS_RESULT)0x0004AC02L)

//
// MessageId: EMS_TCAL_SERVICE_STOP
//
// MessageText:
//
//  EMS TCAL Service Stopped
//
#define EMS_TCAL_SERVICE_STOP            ((EMS_RESULT)0x0004AC03L)

//
// MessageId: EMS_TCAL_PROCESSING_START
//
// MessageText:
//
//  EMS TCAL Processing %1 records.
//
#define EMS_TCAL_PROCESSING_START        ((EMS_RESULT)0x0004AC04L)

//
// MessageId: EMS_TCAL_PROCESSING_STOP
//
// MessageText:
//
//  EMS TCAL completed proccessing.
//
#define EMS_TCAL_PROCESSING_STOP         ((EMS_RESULT)0x0004AC05L)

//
// MessageId: EMS_TCAL_ERROR
//
// MessageText:
//
//  EMS TCAL reports error %1.
//
#define EMS_TCAL_ERROR                   ((EMS_RESULT)0x8004AC06L)

//
// MessageId: EMS_TCAL_FORCED_UNLOCK
//
// MessageText:
//
//  EMS TCAL forced an UNLOCK
//
#define EMS_TCAL_FORCED_UNLOCK           ((EMS_RESULT)0x8004AC07L)

//
// MessageId: EMS_TCAL_RECV_COMMAND
//
// MessageText:
//
//  EMS TCAL received command ( %1 ).
//
#define EMS_TCAL_RECV_COMMAND            ((EMS_RESULT)0x0004AC08L)

//
// MessageId: EMS_TCAL_TRACER
//
// MessageText:
//
//  EMS TCAL tracer ( %1 ).
//
#define EMS_TCAL_TRACER                  ((EMS_RESULT)0x0004AC09L)

//
// MessageId: EMS_TCAL_SUMMARY
//
// MessageText:
//
//  EMS TCAL Summary ( %1 ).
//
#define EMS_TCAL_SUMMARY                 ((EMS_RESULT)0x0004AC0AL)

//
// MessageId: EMS_TCAL_BOUNDS_ALARM
//
// MessageText:
//
//  EMS TCAL reports out of bounds condition ( %1 ).
//
#define EMS_TCAL_BOUNDS_ALARM            ((EMS_RESULT)0x0004AC0BL)

//
// MessageId: EMS_TCAL_UPDATE
//
// MessageText:
//
//  EMS TCAL has been updated ( %1 ).
//
#define EMS_TCAL_UPDATE                  ((EMS_RESULT)0x0004AC0CL)

//
// MessageId: EMS_TCAL_REJECTED
//
// MessageText:
//
//  EMS TCAL has insufficient data to update ( %1 ).
//
#define EMS_TCAL_REJECTED                ((EMS_RESULT)0x0004AC0DL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTREAD
//
// MessageText:
//
//  EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records read )
//
#define EMS_TCAL_SUMMARY_COUNTREAD       ((EMS_RESULT)0x0004AC0EL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTWRITTEN
//
// MessageText:
//
//  EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records written )
//
#define EMS_TCAL_SUMMARY_COUNTWRITTEN    ((EMS_RESULT)0x0004AC0FL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTUSED
//
// MessageText:
//
//  EMS TCAL Summary ( Sat %1, %2 TCalSarp records being used )
//
#define EMS_TCAL_SUMMARY_COUNTUSED       ((EMS_RESULT)0x0004AC10L)

//
// MessageId: EMS_TCAL_TRACE_CONFIG
//
// MessageText:
//
//  EMS TCAL tracer ( TCal config: SatId  %1, minUpdatePeriod %2, maxTimeSpan %3, minMeas %4, maxTSarpThresh %5, maxSarpFCThresh %6 )
//
#define EMS_TCAL_TRACE_CONFIG            ((EMS_RESULT)0x0004AC11L)

//
// MessageId: EMS_TCAL_BOUNDS_ALARMERR
//
// MessageText:
//
//  EMS TCAL reports out of bounds condition ( Sat %1, rollErr %2 (%3) secs, fcErr %4 (%5) Hz, sdRes %6 secs )
//
#define EMS_TCAL_BOUNDS_ALARMERR         ((EMS_RESULT)0x8004AC12L)

//
// MessageId: EMS_TCAL_BOUNDS_ALARMTSPAN
//
// MessageText:
//
//  EMS TCAL reports out of bounds condition ( Sat %1, tSpan %2 (%3) days, nMeas %4 (%5) )
//
#define EMS_TCAL_BOUNDS_ALARMTSPAN       ((EMS_RESULT)0x8004AC13L)

//
// MessageId: EMS_TCAL_UPDATE_PART1
//
// MessageText:
//
//  EMS TCAL has been updated ( Sat %1, orb %2, span %3 days, pts %4, mean/sdev/max %5 msec )
//
#define EMS_TCAL_UPDATE_PART1            ((EMS_RESULT)0x0004AC14L)

//
// MessageId: EMS_TCAL_UPDATE_PART2
//
// MessageText:
//
//  EMS TCAL has been updated ( cycles %1 msec, TSarpOffset %2 msec, corr %3, SarpFC %4 Hz )
//
#define EMS_TCAL_UPDATE_PART2            ((EMS_RESULT)0x0004AC15L)

//
// MessageId: EMS_TCAL_REJECTED_DAYSSINCE
//
// MessageText:
//
//  EMS TCAL has insufficient data to update ( Sat %1, TCAL not performed, only %2 (%3) days since TSarp last updated )
//
#define EMS_TCAL_REJECTED_DAYSSINCE      ((EMS_RESULT)0x8004AC16L)


#endif // INC_TCALMSGS
