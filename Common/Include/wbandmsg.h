/********************************************************************
*	Module:			WBandMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Wideband Errors & Messages
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
#ifndef INC_WBANDMSG
#define INC_WBANDMSG

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
// MessageId: EMS_WIDEBAND_BASE_CODE
//
// MessageText:
//
//  EMS Wideband Error
//
#define EMS_WIDEBAND_BASE_CODE           ((EMS_RESULT)0x0004A200L)

//
// MessageId: EMS_WBAND_SERVICE_START
//
// MessageText:
//
//  EMS Wideband Service Started
//
#define EMS_WBAND_SERVICE_START          ((EMS_RESULT)0x0004A201L)

//
// MessageId: EMS_WBAND_SERVICE_FAILED
//
// MessageText:
//
//  EMS Wideband Service did not start due to error %1
//
#define EMS_WBAND_SERVICE_FAILED         ((EMS_RESULT)0x0004A202L)

//
// MessageId: EMS_WBAND_SERVICE_STOP
//
// MessageText:
//
//  EMS Wideband Service Stopped
//
#define EMS_WBAND_SERVICE_STOP           ((EMS_RESULT)0x0004A203L)

//
// MessageId: EMS_WBAND_ERROR
//
// MessageText:
//
//  EMS Wideband reports error %1.
//
#define EMS_WBAND_ERROR                  ((EMS_RESULT)0x8004A204L)

//
// MessageId: EMS_WBAND_PRIORITY_CLASS
//
// MessageText:
//
//  EMS Wideband reports error %1 when calling SetPriorityClass
//
#define EMS_WBAND_PRIORITY_CLASS         ((EMS_RESULT)0x8004A205L)

//
// MessageId: EMS_WBAND_THREAD_PRIORITY
//
// MessageText:
//
//  EMS Wideband reports error %1 when calling SetThreadPriority
//
#define EMS_WBAND_THREAD_PRIORITY        ((EMS_RESULT)0x8004A206L)

//
// MessageId: EMS_WBAND_IDEAL_PROCESSOR
//
// MessageText:
//
//  EMS Wideband reports error %1 when calling SetThreadIdealProcessor
//
#define EMS_WBAND_IDEAL_PROCESSOR        ((EMS_RESULT)0x8004A207L)

//
// MessageId: EMS_WBAND_NO_DATA
//
// MessageText:
//
//  EMS Wideband reports no data in last %1 seconds during a pass
//
#define EMS_WBAND_NO_DATA                ((EMS_RESULT)0x8004A208L)

//
// MessageId: EMS_WBAND_START_PASS
//
// MessageText:
//
//  EMS Wideband starting pass ( SatID=%1, LutID=%2, Flags=%3 ).
//
#define EMS_WBAND_START_PASS             ((EMS_RESULT)0x0004A209L)

//
// MessageId: EMS_WBAND_STOP_PASS
//
// MessageText:
//
//  EMS Wideband stopping pass. 
//
#define EMS_WBAND_STOP_PASS              ((EMS_RESULT)0x0004A20AL)

//
// MessageId: EMS_WBAND_RECV_COMMAND
//
// MessageText:
//
//  EMS Wideband recv'd cmd( %1 ).
//
#define EMS_WBAND_RECV_COMMAND           ((EMS_RESULT)0x0004A20BL)

//
// MessageId: EMS_WBAND_TRACER
//
// MessageText:
//
//  EMS Wideband ( %1 ).
//
#define EMS_WBAND_TRACER                 ((EMS_RESULT)0x0004A20CL)

//
// MessageId: EMS_WBAND_TRACER_TWIN0TO1
//
// MessageText:
//
//  EMS Wideband (*** Wideband twin signal 0 -> 1)
//
#define EMS_WBAND_TRACER_TWIN0TO1        ((EMS_RESULT)0x0004A20DL)

//
// MessageId: EMS_WBAND_TRACER_TWIN1TO0
//
// MessageText:
//
//  EMS Wideband (*** Wideband twin signal 1 -> 0)
//
#define EMS_WBAND_TRACER_TWIN1TO0        ((EMS_RESULT)0x0004A20EL)

//
// MessageId: EMS_WBAND_TRACER_REPEATINGINDEX
//
// MessageText:
//
//  EMS Wideband (*** Wideband repeating index (%1))
//
#define EMS_WBAND_TRACER_REPEATINGINDEX  ((EMS_RESULT)0x0004A20FL)

//
// MessageId: EMS_WBAND_TRACER_OVERFLOW
//
// MessageText:
//
//  EMS Wideband (*** Wideband reports overflow (%1))
//
#define EMS_WBAND_TRACER_OVERFLOW        ((EMS_RESULT)0x0004A210L)

//
// MessageId: EMS_WBAND_TRACER_HIGHESTCOUNT
//
// MessageText:
//
//  EMS Wideband (*** Wideband highest count (%1))
//
#define EMS_WBAND_TRACER_HIGHESTCOUNT    ((EMS_RESULT)0x0004A211L)

//
// MessageId: EMS_WBAND_TRACER_OTHERBUFFER
//
// MessageText:
//
//  EMS Wideband (*** Wideband reporting other buffer signaled (%1))
//
#define EMS_WBAND_TRACER_OTHERBUFFER     ((EMS_RESULT)0x0004A212L)

//
// MessageId: EMS_WBAND_TRACER_OLDERTHANAOS
//
// MessageText:
//
//  EMS Wideband (*** Wideband data %1 minutes older than AOS )
//
#define EMS_WBAND_TRACER_OLDERTHANAOS    ((EMS_RESULT)0x0004A213L)

//
// MessageId: EMS_WBAND_TRACER_DUPLICATETIME
//
// MessageText:
//
//  EMS Wideband (** Wideband detected duplicate time in buffer)
//
#define EMS_WBAND_TRACER_DUPLICATETIME   ((EMS_RESULT)0x0004A214L)

//
// MessageId: EMS_WBAND_TRACER_PREVTIME
//
// MessageText:
//
//  EMS Wideband (** Wideband detected previous time in buffer)
//
#define EMS_WBAND_TRACER_PREVTIME        ((EMS_RESULT)0x0004A215L)

//
// MessageId: EMS_WBAND_TRACER_SECTOINITIALIZE
//
// MessageText:
//
//  EMS Wideband (*** Wideband took %1 seconds to initialize)
//
#define EMS_WBAND_TRACER_SECTOINITIALIZE ((EMS_RESULT)0x0004A216L)

//
// MessageId: EMS_WBAND_TRACER_CONFIGYES
//
// MessageText:
//
//  EMS Wideband (EMS Wideband (cfg: %1=yes))
//
#define EMS_WBAND_TRACER_CONFIGYES       ((EMS_RESULT)0x0004A217L)

//
// MessageId: EMS_WBAND_TRACER_CONFIGNO
//
// MessageText:
//
//  EMS Wideband (EMS Wideband (cfg: %1=no))
//
#define EMS_WBAND_TRACER_CONFIGNO        ((EMS_RESULT)0x0004A218L)

//
// MessageId: EMS_WBAND_TRACER_CONFIG
//
// MessageText:
//
//  EMS Wideband (cfg: %1=%2)
//
#define EMS_WBAND_TRACER_CONFIG          ((EMS_RESULT)0x0004A219L)

//
// MessageId: EMS_WBAND_INVALIDSTOPCMD
//
// MessageText:
//
//  EMS Wideband is not collecting so a request to Stop was ignored.
//
#define EMS_WBAND_INVALIDSTOPCMD         ((EMS_RESULT)0x8004A21AL)

//
// MessageId: EMS_WBAND_INVALIDSTARTCMD
//
// MessageText:
//
//  EMS Wideband is already collecting so a request to Start was ignored.
//
#define EMS_WBAND_INVALIDSTARTCMD        ((EMS_RESULT)0x8004A21BL)

//
// MessageId: EMS_WBAND_CMDERROR
//
// MessageText:
//
//  EMS Wideband detected an error while processing a %1 command <%2>
//
#define EMS_WBAND_CMDERROR               ((EMS_RESULT)0x8004A21CL)


#endif // INC_WBANDMSG
