/********************************************************************
*	Module:			AntMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Antenna Errors & Messages
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
#ifndef INC_ANTMSGS
#define INC_ANTMSGS

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
// MessageId: EMS_ANT_BASE_CODE
//
// MessageText:
//
//  EMS Antenna Error
//
#define EMS_ANT_BASE_CODE                ((EMS_RESULT)0x0004A600L)

//
// MessageId: EMS_ANT_SERVICE_START
//
// MessageText:
//
//  EMS Antenna Service Started
//
#define EMS_ANT_SERVICE_START            ((EMS_RESULT)0x0004A601L)

//
// MessageId: EMS_ANT_SERVICE_FAILED
//
// MessageText:
//
//  EMS Antenna Service did not start due to error %1
//
#define EMS_ANT_SERVICE_FAILED           ((EMS_RESULT)0x8004A602L)

//
// MessageId: EMS_ANT_SERVICE_STOP
//
// MessageText:
//
//  EMS Antenna Service Stopped
//
#define EMS_ANT_SERVICE_STOP             ((EMS_RESULT)0x0004A603L)

//
// MessageId: EMS_ANT_ERROR
//
// MessageText:
//
//  EMS Antenna reports error %1.
//
#define EMS_ANT_ERROR                    ((EMS_RESULT)0x8004A604L)

//
// MessageId: EMS_ANT_START_PASS
//
// MessageText:
//
//  EMS Antenna starting to track pass 
//
#define EMS_ANT_START_PASS               ((EMS_RESULT)0x0004A605L)

//
// MessageId: EMS_ANT_STOP_PASS
//
// MessageText:
//
//  EMS Antenna stopped tracking pass. 
//
#define EMS_ANT_STOP_PASS                ((EMS_RESULT)0x0004A606L)

//
// MessageId: EMS_ANT_RECV_COMMAND
//
// MessageText:
//
//  EMS Antenna received command ( %1 ).
//
#define EMS_ANT_RECV_COMMAND             ((EMS_RESULT)0x0004A607L)

//
// MessageId: EMS_ANT_INITIAL_HOME
//
// MessageText:
//
//  EMS Antenna successfully initialized.
//
#define EMS_ANT_INITIAL_HOME             ((EMS_RESULT)0x0004A608L)

//
// MessageId: EMS_ANT_FAILED_HOME
//
// MessageText:
//
//  EMS Antenna timed out during initialization.
//
#define EMS_ANT_FAILED_HOME              ((EMS_RESULT)0x8004A609L)

//
// MessageId: EMS_ANT_STATUS
//
// MessageText:
//
//  EMS Antenna Homing Successful. Offset: ( %1 ).
//
#define EMS_ANT_STATUS                   ((EMS_RESULT)0x0004A60AL)

//
// MessageId: EMS_ANT_SKIP_HOME
//
// MessageText:
//
//  EMS Antenna skipped homing sequence.
//
#define EMS_ANT_SKIP_HOME                ((EMS_RESULT)0x0004A60BL)

//
// MessageId: EMS_ANT_DEVICE_PERMISSION
//
// MessageText:
//
//  EMS Antenna reports error accessing antenna device. (see DCOMCnfg - may have insufficient permission ).
//
#define EMS_ANT_DEVICE_PERMISSION        ((EMS_RESULT)0x8004A60CL)

//
// MessageId: EMS_ANT_HOMING_FAULT_RETRY
//
// MessageText:
//
//  EMS Antenna reports homing fault ( Retrying attempt %1 ).
//
#define EMS_ANT_HOMING_FAULT_RETRY       ((EMS_RESULT)0x8004A60DL)

//
// MessageId: EMS_ANT_HOMING_FAULT
//
// MessageText:
//
//  EMS Antenna reports homing fault ( Homing Terminated ).
//
#define EMS_ANT_HOMING_FAULT             ((EMS_RESULT)0x8004A60EL)

//
// MessageId: EMS_ANT_HOMING_TIMEOUT_RETRY
//
// MessageText:
//
//  EMS Antenna reports homing timeout ( Retrying attempt %1 ).
//
#define EMS_ANT_HOMING_TIMEOUT_RETRY     ((EMS_RESULT)0x8004A60FL)

//
// MessageId: EMS_ANT_HOMING_TIMEOUT
//
// MessageText:
//
//  EMS Antenna reports homing timeout ( Homing Terminated ).
//
#define EMS_ANT_HOMING_TIMEOUT           ((EMS_RESULT)0x8004A610L)

//
// MessageId: EMS_ANT_PASS_RETRY
//
// MessageText:
//
//  EMS Antenna reports pass failure ( Retrying attempt %1 ).
//
#define EMS_ANT_PASS_RETRY               ((EMS_RESULT)0x8004A611L)

//
// MessageId: EMS_ANT_PASS_ERROR
//
// MessageText:
//
//  EMS Antenna reports pass failure ( Tracking terminated ).
//
#define EMS_ANT_PASS_ERROR               ((EMS_RESULT)0x8004A612L)

//
// MessageId: EMS_ANT_RESET_WAIT_TIMEOUT
//
// MessageText:
//
//  EMS Antenna reports timeout waiting for Antenna subsystem to shutdown.
//
#define EMS_ANT_RESET_WAIT_TIMEOUT       ((EMS_RESULT)0x8004A613L)

//
// MessageId: EMS_ANT_RESET_WAIT_ABANDONED
//
// MessageText:
//
//  EMS Antenna reports wait abandoned for Antenna subsystem to shutdown.
//
#define EMS_ANT_RESET_WAIT_ABANDONED     ((EMS_RESULT)0x8004A614L)

//
// MessageId: EMS_ANT_DEVICE_INIT_FAILED
//
// MessageText:
//
//  EMS Antenna reports an error during ACU initialization (hr = %1). This may indicate a power outage to the ACU or an ACU hardware fault.  Hardware faults can often be cleared by recycling the ACU power.
//
#define EMS_ANT_DEVICE_INIT_FAILED       ((EMS_RESULT)0x8004A615L)

//
// MessageId: EMS_ANT_INIT_HOME
//
// MessageText:
//
//  EMS Antenna reports initial homing was successful.
//
#define EMS_ANT_INIT_HOME                ((EMS_RESULT)0x0004A616L)

//
// MessageId: EMS_ANT_HARDWARE_ERROR
//
// MessageText:
//
//  EMS Antenna reports a hardware problem. This may indicate a power outage to the ACU or an ACU hardware fault. Hardware faults can often be cleared by recycling the ACU power.
//
#define EMS_ANT_HARDWARE_ERROR           ((EMS_RESULT)0x8004A617L)

//
// MessageId: EMS_ANT_HARDWARE_ERROR_CLEARED
//
// MessageText:
//
//  EMS Antenna reports the ACU hardware error condition has been cleared.
//
#define EMS_ANT_HARDWARE_ERROR_CLEARED   ((EMS_RESULT)0x0004A618L)

//
// MessageId: EMS_ANT_INIT_ERROR_SKIP_PASS
//
// MessageText:
//
//  EMS Antenna reports it is skipping a pass (satellite %1) due to problem in ACU initialization.
//
#define EMS_ANT_INIT_ERROR_SKIP_PASS     ((EMS_RESULT)0x8004A619L)


// *** EMSCAT_ANT = 0x87 ***

//
// MessageId: EMSCAT_ANT_BASE_CODE
//
// MessageText:
//
//  Antenna error messages.
//
#define EMSCAT_ANT_BASE_CODE             ((EMS_RESULT)0x80048700L)

//
// MessageId: ANT_INV_CTR_REQUEST
//
// MessageText:
//
//  EMS Antenna reports invalid control request received.
//
#define ANT_INV_CTR_REQUEST              ((EMS_RESULT)0x80048701L)

//
// MessageId: ANT_INV_DEST_NAME
//
// MessageText:
//
//  EMS Antenna: given logical destination is invalid.
//
#define ANT_INV_DEST_NAME                ((EMS_RESULT)0x80048702L)

//
// MessageId: ANT_INV_BEAMWIDTH
//
// MessageText:
//
//  EMS Antenna: Specified azimuth and elevation are not within the beamwidth.
//
#define ANT_INV_BEAMWIDTH                ((EMS_RESULT)0x80048703L)

//
// MessageId: ANT_NOT_REACHED_AOS
//
// MessageText:
//
//  EMS Antenna: Could not move to AOS.
//
#define ANT_NOT_REACHED_AOS              ((EMS_RESULT)0x80048704L)

//
// MessageId: ANT_CW_LIMIT_HIT
//
// MessageText:
//
//  EMS Antenna: At Clockwise limit zone.
//
#define ANT_CW_LIMIT_HIT                 ((EMS_RESULT)0x80048705L)

//
// MessageId: ANT_CCW_LIMIT_HIT
//
// MessageText:
//
//  EMS Antenna: At Counter Clockwise limit zone
//
#define ANT_CCW_LIMIT_HIT                ((EMS_RESULT)0x80048706L)

//
// MessageId: ANT_HIGH_LIMIT_HIT
//
// MessageText:
//
//  EMS Antenna: At High elevation limit zone
//
#define ANT_HIGH_LIMIT_HIT               ((EMS_RESULT)0x80048707L)

//
// MessageId: ANT_LOW_LIMIT_HIT
//
// MessageText:
//
//  EMS Antenna: At Low elevation limit zone
//
#define ANT_LOW_LIMIT_HIT                ((EMS_RESULT)0x80048708L)

//
// MessageId: ANT_INV_REGISTRY
//
// MessageText:
//
//  EMS Antenna: Can't open registry
//
#define ANT_INV_REGISTRY                 ((EMS_RESULT)0x80048709L)

//
// MessageId: ANT_ILLEGAL_LINE_NUMBER
//
// MessageText:
//
//  EMS Antenna: Illegal line number.
//
#define ANT_ILLEGAL_LINE_NUMBER          ((EMS_RESULT)0x8004870AL)

//
// MessageId: ANT_NON_REQUEST_TO_CANCEL
//
// MessageText:
//
//  EMS Antenna: Invalid cancel request.
//
#define ANT_NON_REQUEST_TO_CANCEL        ((EMS_RESULT)0x8004870BL)

//
// MessageId: ANT_INV_AZIMUTH_COMM
//
// MessageText:
//
//  EMS Antenna: Failed to set azimuth.
//
#define ANT_INV_AZIMUTH_COMM             ((EMS_RESULT)0x8004870CL)

//
// MessageId: ANT_INV_ELEVATION_COMM
//
// MessageText:
//
//  EMS Antenna: Failed to set elevation.
//
#define ANT_INV_ELEVATION_COMM           ((EMS_RESULT)0x8004870DL)

//
// MessageId: ANT_CANT_STOP_ANTENNA
//
// MessageText:
//
//  EMS Antenna: Cannot stop antenna.
//
#define ANT_CANT_STOP_ANTENNA            ((EMS_RESULT)0x8004870EL)

//
// MessageId: ANT_HOME_FAULT
//
// MessageText:
//
//  EMS Antenna: Error processing home command.
//
#define ANT_HOME_FAULT                   ((EMS_RESULT)0x8004870FL)

//
// MessageId: EMS_TOO_LATE_FOR_TRACK
//
// MessageText:
//
//  EMS Antenna: Too late for track.
//
#define EMS_TOO_LATE_FOR_TRACK           ((EMS_RESULT)0x80048710L)

//
// MessageId: EMS_ANT_WORKERBUFFERLOCKERR
//
// MessageText:
//
//  EMS Antenna: Error locking buffer in transfer track data in WorkerThread
//
#define EMS_ANT_WORKERBUFFERLOCKERR      ((EMS_RESULT)0x80048711L)

//
// MessageId: EMS_ANT_MEMORYRAWTRACK
//
// MessageText:
//
//  EMS Antenna: Error Allocating memory for l_AdjRawTrack in WorkerThread
//
#define EMS_ANT_MEMORYRAWTRACK           ((EMS_RESULT)0x80048712L)

//
// MessageId: EMS_ANT_TOOMANYSMOOTHINGITER
//
// MessageText:
//
//  EMS Antenna: Too many smoothing iterations in WorkerThread. Smoothing aborted.
//
#define EMS_ANT_TOOMANYSMOOTHINGITER     ((EMS_RESULT)0x80048713L)

//
// MessageId: EMS_ANT_TIMESINCEAXISPOSNTOOLONG
//
// MessageText:
//
//  EMS Antenna: Track execution aborted. Time since last axis position report is too long.
//
#define EMS_ANT_TIMESINCEAXISPOSNTOOLONG ((EMS_RESULT)0x80048714L)

//
// MessageId: EMS_ANT_TRACKSPEEDMEMORYERR
//
// MessageText:
//
//  EMS Antenna: Could not allocate memory for proposed track speeds.
//
#define EMS_ANT_TRACKSPEEDMEMORYERR      ((EMS_RESULT)0x80048715L)

//
// MessageId: EMS_ANT_TRACKMEMORYERR
//
// MessageText:
//
//  EMS Antenna: Could not allocate memory for proposed track.
//
#define EMS_ANT_TRACKMEMORYERR           ((EMS_RESULT)0x80048716L)

//
// MessageId: EMS_ANT_AZIMUTHRECONCILEERR
//
// MessageText:
//
//  EMS Antenna: Cannot reconcile azimuth values to track within the antenna parameters.
//
#define EMS_ANT_AZIMUTHRECONCILEERR      ((EMS_RESULT)0x80048717L)

//
// MessageId: EMS_ANT_RAWTRACKMEMORYERR
//
// MessageText:
//
//  EMS Antenna: Cannot Allocate Memory for l_AdjRawRawTrack
//
#define EMS_ANT_RAWTRACKMEMORYERR        ((EMS_RESULT)0x80048718L)

//
// MessageId: EMS_ANT_MEMORYERR
//
// MessageText:
//
//  EMS Antenna: Cannot Allocate Memory
//
#define EMS_ANT_MEMORYERR                ((EMS_RESULT)0x80048719L)

//
// MessageId: EMS_ANT_COORDMEMORYERR
//
// MessageText:
//
//  EMS Antenna: Cannot Allocate Memory for coordinates
//
#define EMS_ANT_COORDMEMORYERR           ((EMS_RESULT)0x8004871AL)

//
// MessageId: EMS_ANT_HARDWAREERR
//
// MessageText:
//
//  EMS Antenna: Hardware error.
//
#define EMS_ANT_HARDWAREERR              ((EMS_RESULT)0x8004871BL)

//
// MessageId: EMS_ANT_OUTOFBEAMERR
//
// MessageText:
//
//  EMS Antenna: Out of beam error.
//
#define EMS_ANT_OUTOFBEAMERR             ((EMS_RESULT)0x8004871CL)

//
// MessageId: EMS_ANT_UNKNOWNERR
//
// MessageText:
//
//  EMS Antenna: Unknown error.
//
#define EMS_ANT_UNKNOWNERR               ((EMS_RESULT)0x8004871DL)

//
// MessageId: EMS_ANT_AGC_SWITCH_FAIL
//
// MessageText:
//
//  EMS Antenna: Failed to initialize AGC switch (hr=%1).
//
#define EMS_ANT_AGC_SWITCH_FAIL          ((EMS_RESULT)0x8004871EL)

//
// MessageId: EMS_ANT_POLR_SWITCH_FAIL
//
// MessageText:
//
//  EMS Antenna: Failed to initialize polarization switch (hr=%1).
//
#define EMS_ANT_POLR_SWITCH_FAIL         ((EMS_RESULT)0x8004871FL)

//
// MessageId: EMS_ANT_FREQ1_SWITCH_FAIL
//
// MessageText:
//
//  EMS Antenna: Failed to initialize the first frequency switch (hr=%1).
//
#define EMS_ANT_FREQ1_SWITCH_FAIL        ((EMS_RESULT)0x80048720L)

//
// MessageId: EMS_ANT_FREQ2_SWITCH_FAIL
//
// MessageText:
//
//  EMS Antenna: Failed to initialize the second frequency switch (hr=%1).
//
#define EMS_ANT_FREQ2_SWITCH_FAIL        ((EMS_RESULT)0x80048721L)

//
// MessageId: EMS_ANT_HW_ERR_REINIT
//
// MessageText:
//
//  EMS Antenna: Detected a hardware problem and trying to reinitialize the ACU. (This could be a power outages, ACU hardware error or network problem).
//
#define EMS_ANT_HW_ERR_REINIT            ((EMS_RESULT)0x80048722L)


#endif // INC_ANTMSGS
