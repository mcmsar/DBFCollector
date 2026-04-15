/********************************************************************
*	Module:			ODetMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Orbit Determination Messages
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
#ifndef INC_ODETMSGS
#define INC_ODETMSGS

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
// MessageId: EMS_ODET_BASE_CODE
//
// MessageText:
//
//  EMS OrbitDet Error
//
#define EMS_ODET_BASE_CODE               ((EMS_RESULT)0x0004A700L)

//
// MessageId: EMS_ODET_SERVICE_START
//
// MessageText:
//
//  EMS OrbitDet Service Started
//
#define EMS_ODET_SERVICE_START           ((EMS_RESULT)0x0004A701L)

//
// MessageId: EMS_ODET_SERVICE_FAILED
//
// MessageText:
//
//  EMS OrbitDet Service did not start due to error %1
//
#define EMS_ODET_SERVICE_FAILED          ((EMS_RESULT)0x0004A702L)

//
// MessageId: EMS_ODET_SERVICE_STOP
//
// MessageText:
//
//  EMS OrbitDet Service Stopped
//
#define EMS_ODET_SERVICE_STOP            ((EMS_RESULT)0x0004A703L)

//
// MessageId: EMS_ODET_PROCESSING_START
//
// MessageText:
//
//  EMS OrbitDet Processing %1 records.
//
#define EMS_ODET_PROCESSING_START        ((EMS_RESULT)0x0004A704L)

//
// MessageId: EMS_ODET_PROCESSING_STOP
//
// MessageText:
//
//  EMS OrbitDet completed proccessing.
//
#define EMS_ODET_PROCESSING_STOP         ((EMS_RESULT)0x0004A705L)

//
// MessageId: EMS_ODET_ERROR
//
// MessageText:
//
//  EMS OrbitDet reports error %1.
//
#define EMS_ODET_ERROR                   ((EMS_RESULT)0x8004A706L)

//
// MessageId: EMS_ODET_FORCED_UNLOCK
//
// MessageText:
//
//  EMS OrbitDet forced an UNLOCK
//
#define EMS_ODET_FORCED_UNLOCK           ((EMS_RESULT)0x8004A707L)

//
// MessageId: EMS_ODET_RECV_COMMAND
//
// MessageText:
//
//  EMS OrbitDet received command ( %1 ).
//
#define EMS_ODET_RECV_COMMAND            ((EMS_RESULT)0x0004A708L)

//
// MessageId: EMS_ODET_TRACER
//
// MessageText:
//
//  EMS OrbitDet tracer ( %1 ).
//
#define EMS_ODET_TRACER                  ((EMS_RESULT)0x0004A709L)

//
// MessageId: EMS_ODET_SUMMARY
//
// MessageText:
//
//  EMS OrbitDet Summary ( %1 ).
//
#define EMS_ODET_SUMMARY                 ((EMS_RESULT)0x0004A70AL)

//
// MessageId: EMS_ODET_BOUNDS_ALARM
//
// MessageText:
//
//  EMS OrbitDet reports out of bounds condition { Sat, Pos, Pts, StDev = %1 }
//
#define EMS_ODET_BOUNDS_ALARM            ((EMS_RESULT)0x0004A70BL)

//
// MessageId: EMS_ODET_TLE_UPDATE
//
// MessageText:
//
//  EMS OrbitDet has updated TLE vector.
//
#define EMS_ODET_TLE_UPDATE              ((EMS_RESULT)0x0004A70CL)

//
// MessageId: EMS_ODET_TLE_REJECTED
//
// MessageText:
//
//  EMS OrbitDet has insufficient data to update TLE vector.
//
#define EMS_ODET_TLE_REJECTED            ((EMS_RESULT)0x0004A70DL)

//
// MessageId: EMS_ODET_TRACER_TRACKRECSREAD
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records read)
//
#define EMS_ODET_TRACER_TRACKRECSREAD    ((EMS_RESULT)0x0004A70EL)

//
// MessageId: EMS_ODET_TRACER_CALIB406RECSREAD
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records read)
//
#define EMS_ODET_TRACER_CALIB406RECSREAD ((EMS_RESULT)0x0004A70FL)

//
// MessageId: EMS_ODET_TRACER_CALIB406RECSACC
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records accepted)
//
#define EMS_ODET_TRACER_CALIB406RECSACC  ((EMS_RESULT)0x0004A710L)

//
// MessageId: EMS_ODET_TRACER_TRACKRECSWRITTEN
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records written)
//
#define EMS_ODET_TRACER_TRACKRECSWRITTEN ((EMS_RESULT)0x0004A711L)

//
// MessageId: EMS_ODET_TRACER_ENDOFPASS
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) EndOfPass)
//
#define EMS_ODET_TRACER_ENDOFPASS        ((EMS_RESULT)0x0004A712L)

//
// MessageId: EMS_ODET_TRACER_LOCKED
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Locked)
//
#define EMS_ODET_TRACER_LOCKED           ((EMS_RESULT)0x0004A713L)

//
// MessageId: EMS_ODET_TRACER_UNLOCKED
//
// MessageText:
//
//  EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Unlocked)
//
#define EMS_ODET_TRACER_UNLOCKED         ((EMS_RESULT)0x0004A714L)

//
// MessageId: EMS_ODET_TRACER_UNEXPECTEDSTATE
//
// MessageText:
//
//  EMS OrbitDet tracer (_DoEndOfPass : Unexpected State(%1))
//
#define EMS_ODET_TRACER_UNEXPECTEDSTATE  ((EMS_RESULT)0x0004A715L)

//
// MessageId: EMS_ODET_TRACER_MISMATCHEDSAT
//
// MessageText:
//
//  EMS OrbitDet tracer (_DoEndOfPass : Sat %1 != Sat %2)
//
#define EMS_ODET_TRACER_MISMATCHEDSAT    ((EMS_RESULT)0x0004A716L)

//
// MessageId: EMS_ODET_TRACER_CONFIGTHRESHOLDS
//
// MessageText:
//
//  EMS OrbitDet tracer (OrbitDet config: SatId  %1, PosThr %2 km, VelThr %3 m/sec, DurMax %4 days, ItrMin %5, ItrMax %6)
//
#define EMS_ODET_TRACER_CONFIGTHRESHOLDS ((EMS_RESULT)0x0004A717L)

//
// MessageId: EMS_ODET_TRACER_CONFIGRESIDUALSTRUE
//
// MessageText:
//
//  EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk TRUE, MinPts %3)
//
#define EMS_ODET_TRACER_CONFIGRESIDUALSTRUE ((EMS_RESULT)0x0004A718L)

//
// MessageId: EMS_ODET_TRACER_CONFIGRESIDUALSFALSE
//
// MessageText:
//
//  EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk FALSE, MinPts %3)
//
#define EMS_ODET_TRACER_CONFIGRESIDUALSFALSE ((EMS_RESULT)0x0004A719L)

//
// MessageId: EMS_ODET_PROCESSING_STARTSATPASS
//
// MessageText:
//
//  EMS OrbitDet Processing Start (SatID=%1,Pass=%2).
//
#define EMS_ODET_PROCESSING_STARTSATPASS ((EMS_RESULT)0x0004A71AL)

//
// MessageId: EMS_ODET_SUMMARYDETAILS
//
// MessageText:
//
//  EMS OrbitDet Summary ( SatID=%1,Pass=%2, pos=%3, vel=%4, std=%5, num=%6 )
//
#define EMS_ODET_SUMMARYDETAILS          ((EMS_RESULT)0x0004A71BL)

//
// MessageId: EMS_ODET_BOUNDS_ALARMDETAILS
//
// MessageText:
//
//  EMS OrbitDet reports out of bounds condition { Sat, Pos, Vel, Pts, StDev = %1, %2, %3, %4, %5 }
//
#define EMS_ODET_BOUNDS_ALARMDETAILS     ((EMS_RESULT)0x8004A71CL)

//
// MessageId: EMS_ODET_POST_MANOEUVRE
//
// MessageText:
//
//  EMS OrbitDet will exclude all data from Sat ID %1 prior to %2.
//
#define EMS_ODET_POST_MANOEUVRE          ((EMS_RESULT)0x0004A71DL)


#endif // INC_ODETMSGS
