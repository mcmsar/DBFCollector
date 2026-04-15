/********************************************************************
*	Module:			STestMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS System Test Errors & Messages
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
#ifndef INC_STESTMSG
#define INC_STESTMSG

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
// MessageId: EMS_SYSTEST_BASE_CODE
//
// MessageText:
//
//  EMS System Test Error
//
#define EMS_SYSTEST_BASE_CODE            ((EMS_RESULT)0x0004AE00L)

//
// MessageId: EMS_SYSTEST_SERVICE_START
//
// MessageText:
//
//  EMS System Test Service Started
//
#define EMS_SYSTEST_SERVICE_START        ((EMS_RESULT)0x0004AE01L)

//
// MessageId: EMS_SYSTEST_SERVICE_FAILED
//
// MessageText:
//
//  EMS System Test Service did not start due to error %1
//
#define EMS_SYSTEST_SERVICE_FAILED       ((EMS_RESULT)0x0004AE02L)

//
// MessageId: EMS_SYSTEST_SERVICE_STOP
//
// MessageText:
//
//  EMS System Test Service Stopped
//
#define EMS_SYSTEST_SERVICE_STOP         ((EMS_RESULT)0x0004AE03L)

//
// MessageId: EMS_SYSTEST_ERROR
//
// MessageText:
//
//  EMS System Test reports error %1.
//
#define EMS_SYSTEST_ERROR                ((EMS_RESULT)0x8004AE04L)

//
// MessageId: EMS_SYSTEST_TIMEOUT
//
// MessageText:
//
//  EMS System Test timed out during operation.
//
#define EMS_SYSTEST_TIMEOUT              ((EMS_RESULT)0x8004AE05L)

//
// MessageId: EMS_SYSTEST_START
//
// MessageText:
//
//  EMS System Test Initiated.
//
#define EMS_SYSTEST_START                ((EMS_RESULT)0x0004AE06L)

//
// MessageId: EMS_SYSTEST_FAIL_ANTENNA
//
// MessageText:
//
//  EMS System Test Indicates Possible Antenna Problem %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_FAIL_ANTENNA         ((EMS_RESULT)0x8004AE07L)

//
// MessageId: EMS_SYSTEST_FAIL_POWER
//
// MessageText:
//
//  EMS System Test Indicates Possible Signal Reception Problem %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_FAIL_POWER           ((EMS_RESULT)0x8004AE08L)

//
// MessageId: EMS_SYSTEST_STATUS
//
// MessageText:
//
//  %1,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS               ((EMS_RESULT)0x0004AE09L)

//
// MessageId: EMS_SYSTEST_PASSED
//
// MessageText:
//
//  EMS System Test Passed  %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_PASSED               ((EMS_RESULT)0x0004AE0AL)

//
// MessageId: EMS_SYSTEST_NO_AGC_SWITCH_INFO
//
// MessageText:
//
//  EMS System Test reports AGC switch not available yet.
//
#define EMS_SYSTEST_NO_AGC_SWITCH_INFO   ((EMS_RESULT)0x0004AE0BL)

//
// MessageId: EMS_SYSTEST_NO_AGC_SWITCH_ALARM
//
// MessageText:
//
//  EMS System Test reports AGC switch not available.
//
#define EMS_SYSTEST_NO_AGC_SWITCH_ALARM  ((EMS_RESULT)0x8004AE0BL)

//
// MessageId: EMS_SYSTEST_NO_ANTENNA
//
// MessageText:
//
//  EMS System Test unable to communicate with the Antenna Service.
//
#define EMS_SYSTEST_NO_ANTENNA           ((EMS_RESULT)0x8004AE0CL)

//
// MessageId: EMS_SYSTEST_STATUS_OKAY
//
// MessageText:
//
//  %1,OKAY,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS_OKAY          ((EMS_RESULT)0x0004AE0DL)

//
// MessageId: EMS_SYSTEST_STATUS_FAILED
//
// MessageText:
//
//  %1,FAILED,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS_FAILED        ((EMS_RESULT)0x0004AE0EL)

//
// MessageId: EMS_SYSTEST_NOT_INIT
//
// MessageText:
//
//  EMS System Test has not initialized.
//
#define EMS_SYSTEST_NOT_INIT             ((EMS_RESULT)0x8004AE0FL)

//
// MessageId: EMS_SYSTEST_ALREADY_IN_TEST
//
// MessageText:
//
//  EMS System Test cannot process the request to start a system test as a test is currently underway.
//
#define EMS_SYSTEST_ALREADY_IN_TEST      ((EMS_RESULT)0x8004AE10L)

//
// MessageId: EMS_SYSTEST_NO_TX_SWITCH_ALARM
//
// MessageText:
//
//  EMS System Test reports Transmitter switch not available.
//
#define EMS_SYSTEST_NO_TX_SWITCH_ALARM   ((EMS_RESULT)0x8004AE11L)

//
// MessageId: EMS_SYSTEST_TX_SWITCH_ON_FP
//
// MessageText:
//
//  EMS System Test expecting Transmitter to be switched on the FP.
//
#define EMS_SYSTEST_TX_SWITCH_ON_FP      ((EMS_RESULT)0x0004AE12L)


#endif // INC_STESTMSG
