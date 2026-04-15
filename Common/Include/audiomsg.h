/********************************************************************
*	Module:			AudioMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Audio Service Messages
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
#ifndef INC_AUDIOMSG
#define INC_AUDIOMSG

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
// MessageId: EMS_AUDIO_BASE_CODE
//
// MessageText:
//
//  EMS Audio Error
//
#define EMS_AUDIO_BASE_CODE              ((EMS_RESULT)0x0004BE00L)

//
// MessageId: EMS_AUDIO_SERVICE_START
//
// MessageText:
//
//  EMS Audio Service Started
//
#define EMS_AUDIO_SERVICE_START          ((EMS_RESULT)0x0004BE01L)

//
// MessageId: EMS_AUDIO_SERVICE_FAILED
//
// MessageText:
//
//  EMS Audio Service did not start due to error %1
//
#define EMS_AUDIO_SERVICE_FAILED         ((EMS_RESULT)0x0004BE02L)

//
// MessageId: EMS_AUDIO_SERVICE_STOP
//
// MessageText:
//
//  EMS Audio Service Stopped
//
#define EMS_AUDIO_SERVICE_STOP           ((EMS_RESULT)0x0004BE03L)

//
// MessageId: EMS_AUDIO_ERROR
//
// MessageText:
//
//  EMS Audio reports error %1.
//
#define EMS_AUDIO_ERROR                  ((EMS_RESULT)0x8004BE04L)

//
// MessageId: EMS_AUDIO_LOG_EXCEPTION
//
// MessageText:
//
//  EMS Audio reports an exception
//
#define EMS_AUDIO_LOG_EXCEPTION          ((EMS_RESULT)0x8004BE05L)

//
// MessageId: EMS_AUDIO_LOG_INFO
//
// MessageText:
//
//  EMS Audio reports info
//
#define EMS_AUDIO_LOG_INFO               ((EMS_RESULT)0x0004BE06L)

//
// MessageId: EMS_AUDIO_DIRECTORY_ERROR
//
// MessageText:
//
//  EMS Audio reports error while trying to create directory ( %1 ).
//
#define EMS_AUDIO_DIRECTORY_ERROR        ((EMS_RESULT)0x8004BE07L)

//
// MessageId: EMS_AUDIO_TRACER
//
// MessageText:
//
//  EMS Audio tracer ( %1 ).
//
#define EMS_AUDIO_TRACER                 ((EMS_RESULT)0x0004BE08L)

//
// MessageId: EMS_AUDIO_FILE_READ_FAIL
//
// MessageText:
//
//  EMS Audio reports error %1 while attempting to open file %2.
//
#define EMS_AUDIO_FILE_READ_FAIL         ((EMS_RESULT)0x0004BE09L)

//
// MessageId: EMS_AUDIOMANAGER_MAXSESSIONS
//
// MessageText:
//
//  EMS Audio Manager error : Max sessions reached.
//
#define EMS_AUDIOMANAGER_MAXSESSIONS     ((EMS_RESULT)0x8004BE0AL)

//
// MessageId: EMS_AUDIOMANAGER_CLIENTNOTCONNECTED
//
// MessageText:
//
//  EMS Audio Manager error : Client is not connected.
//
#define EMS_AUDIOMANAGER_CLIENTNOTCONNECTED ((EMS_RESULT)0x8004BE0BL)

//
// MessageId: EMS_AUDIOMANAGER_NODATA
//
// MessageText:
//
//  EMS Audio Manager : No data found.
//
#define EMS_AUDIOMANAGER_NODATA          ((EMS_RESULT)0x0004BE0CL)

//
// MessageId: EMS_AUDIOMANAGER_PROCESSFILE
//
// MessageText:
//
//  EMS Audio Manager is processing the file ( %1 ).
//
#define EMS_AUDIOMANAGER_PROCESSFILE     ((EMS_RESULT)0x0004BE0DL)

//
// MessageId: EMS_AUDIOMANAGER_REQ_COMPLETED
//
// MessageText:
//
//  EMS Audio Manager : Audio Request processing completed.
//
#define EMS_AUDIOMANAGER_REQ_COMPLETED   ((EMS_RESULT)0x0004BE0EL)

//
// MessageId: EMS_AUDIO_TRACER_RECORDSGEN
//
// MessageText:
//
//  EMS Audio tracer ( Request ID: %1, records generated: %2)
//
#define EMS_AUDIO_TRACER_RECORDSGEN      ((EMS_RESULT)0x0004BE0FL)

//
// MessageId: EMS_AUDIO_TRACER_AUDIOREQ
//
// MessageText:
//
//  EMS Audio tracer ( AudioReq %1 )
//
#define EMS_AUDIO_TRACER_AUDIOREQ        ((EMS_RESULT)0x0004BE10L)

//
// MessageId: EMS_AUDIO_TRACER_REQDETAILS
//
// MessageText:
//
//  EMS Audio tracer ( SatID %1, Time %2, Duration %3, CenterFreq %4, Bandwidth %5 )
//
#define EMS_AUDIO_TRACER_REQDETAILS      ((EMS_RESULT)0x0004BE11L)

//
// MessageId: EMS_AUDIO_TRACER_MAKEWAVEFILE
//
// MessageText:
//
//  EMS Audio tracer ( _MakeWaveFile:     result = %1 )
//
#define EMS_AUDIO_TRACER_MAKEWAVEFILE    ((EMS_RESULT)0x0004BE12L)

//
// MessageId: EMS_AUDIO_TRACER_CONFIG
//
// MessageText:
//
//  EMS Audio tracer ( cfg: %1=%2 )
//
#define EMS_AUDIO_TRACER_CONFIG          ((EMS_RESULT)0x0004BE13L)

//
// MessageId: EMS_AUDIO_TRACER_CHANSCOEFFS
//
// MessageText:
//
//  EMS Audio tracer ( Chans %1, coeffs %2 )
//
#define EMS_AUDIO_TRACER_CHANSCOEFFS     ((EMS_RESULT)0x0004BE14L)

//
// MessageId: EMS_AUDIOMANAGER_INITFAILED
//
// MessageText:
//
//  EMS Audio Manager initialization failed (%1)
//
#define EMS_AUDIOMANAGER_INITFAILED      ((EMS_RESULT)0x8004BE15L)


#endif // INC_AUDIOMSG
