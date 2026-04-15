/********************************************************************
*	Module:			CalibCBCMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS CalibCBC Errors & Messages
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
#ifndef INC_CALIBCBCMSG
#define INC_CALIBCBCMSG

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
// MessageId: EMS_CALIBCBC_BASE_CODE
//
// MessageText:
//
//  EMS CalibrateCBC Error
//
#define EMS_CALIBCBC_BASE_CODE           ((EMS_RESULT)0x0004A800L)

//
// MessageId: EMS_CALIBCBC_SERVICE_START
//
// MessageText:
//
//  EMS CalibrateCBC Service Started
//
#define EMS_CALIBCBC_SERVICE_START       ((EMS_RESULT)0x0004A801L)

//
// MessageId: EMS_CALIBCBC_SERVICE_FAILED
//
// MessageText:
//
//  EMS CalibrateCBC Service did not start due to error %1
//
#define EMS_CALIBCBC_SERVICE_FAILED      ((EMS_RESULT)0x8004A802L)

//
// MessageId: EMS_CALIBCBC_SERVICE_STOP
//
// MessageText:
//
//  EMS CalibrateCBC Service Stopped
//
#define EMS_CALIBCBC_SERVICE_STOP        ((EMS_RESULT)0x0004A803L)

//
// MessageId: EMS_CALIBCBC_ERROR
//
// MessageText:
//
//  EMS CalibrateCBC reports error %1.
//
#define EMS_CALIBCBC_ERROR               ((EMS_RESULT)0x8004A804L)

//
// MessageId: EMS_CALIBCBC_START_PASS
//
// MessageText:
//
//  EMS CalibrateCBC initialized for satellite %1
//
#define EMS_CALIBCBC_START_PASS          ((EMS_RESULT)0x0004A805L)

//
// MessageId: EMS_CALIBCBC_CALIBRATE_PASS
//
// MessageText:
//
//  EMS CalibrateCBC completed calibration for satellite=%1, band=%2, result=%3
//
#define EMS_CALIBCBC_CALIBRATE_PASS      ((EMS_RESULT)0x0004A806L)

//
// MessageId: EMS_CALIBCBC_ADDREC_ERROR
//
// MessageText:
//
//  EMS CalibrateCBC reports error %1 adding record %2.
//
#define EMS_CALIBCBC_ADDREC_ERROR        ((EMS_RESULT)0x8004A807L)

//
// MessageId: EMS_CALIBCBC_TRACER
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( %1 )
//
#define EMS_CALIBCBC_TRACER              ((EMS_RESULT)0x0004A808L)

//
// MessageId: EMS_CALIBCBC_RECV_COMMAND
//
// MessageText:
//
//  EMS CalibrateCBC Command Received( %1 )
//
#define EMS_CALIBCBC_RECV_COMMAND        ((EMS_RESULT)0x0004A809L)

//
// MessageId: EMS_CALIBCBC_START_CALIBRATE
//
// MessageText:
//
//  EMS CalibrateCBC Starting to calibrate %1 records.
//
#define EMS_CALIBCBC_START_CALIBRATE     ((EMS_RESULT)0x0004A80AL)

//
// MessageId: EMS_CALIBCBC_SUBSYSTEM_ERR
//
// MessageText:
//
//  EMS CalibrateCBC reports error %1 while trying to access %2
//
#define EMS_CALIBCBC_SUBSYSTEM_ERR       ((EMS_RESULT)0x8004A80BL)

//
// MessageId: EMS_CALIBCBC_TRACE_AUDIOSENT
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 sent )
//
#define EMS_CALIBCBC_TRACE_AUDIOSENT     ((EMS_RESULT)0x0004A80CL)

//
// MessageId: EMS_CALIBCBC_TRACE_AUDIONOTSENT
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 not sent )
//
#define EMS_CALIBCBC_TRACE_AUDIONOTSENT  ((EMS_RESULT)0x0004A80DL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS1
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Config Parms-%1: minAmplitude %2, fTimeBinSize %3 sec, fFreqBinSize %4 Hz, fFreqWindow %5 Hz )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS1 ((EMS_RESULT)0x0004A80EL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS2
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS2 ((EMS_RESULT)0x0004A80FL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS3
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Config Parms: minAmplitude %1, fTimeBinSize    %2 sec, fFreqBinSize    %3 Hz, fFreqWindow %4 Hz )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS3 ((EMS_RESULT)0x0004A810L)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS4
//
// MessageText:
//
//  EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS4 ((EMS_RESULT)0x0004A811L)

//
// MessageId: EMS_CALIBCBC_SUBSYSTEM_ERR_CALIBRATE
//
// MessageText:
//
//  EMS CalibrateCBC reports error %1 (trap %2) while trying to access the calibrate subsystem. 
//
#define EMS_CALIBCBC_SUBSYSTEM_ERR_CALIBRATE ((EMS_RESULT)0x8004A812L)

//
// MessageId: EMS_CALIBCBC_CALIBRATE_TIMEOUT
//
// MessageText:
//
//  EMS CalibrateCBC time limit exceeded for satellite=%1, band=%2
//
#define EMS_CALIBCBC_CALIBRATE_TIMEOUT   ((EMS_RESULT)0x8004A813L)


#endif // INC_CALIBCBCMSG
