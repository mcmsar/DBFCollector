/********************************************************************
*	Module:			CollMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Collector Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_COLLMSGS
#define INC_COLLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values laid out as follows:
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
// MessageId: EMS_COLL_BASE_CODE
//
// MessageText:
//
// EMS Collector Error
//
#define EMS_COLL_BASE_CODE               ((EMS_RESULT)0x0004A300L)

//
// MessageId: EMS_COLL_SERVICE_START
//
// MessageText:
//
// EMS Collector Service Started
//
#define EMS_COLL_SERVICE_START           ((EMS_RESULT)0x0004A301L)

//
// MessageId: EMS_COLL_SERVICE_FAILED
//
// MessageText:
//
// EMS Collector Service did not start due to error (%1)
//
#define EMS_COLL_SERVICE_FAILED          ((EMS_RESULT)0x8004A302L)

//
// MessageId: EMS_COLL_SERVICE_STOP
//
// MessageText:
//
// EMS Collector Service Stopped
//
#define EMS_COLL_SERVICE_STOP            ((EMS_RESULT)0x0004A303L)

//
// MessageId: EMS_COLL_PASS_START
//
// MessageText:
//
// EMS Collector Service Starting Pass for Sat %1.
//
#define EMS_COLL_PASS_START              ((EMS_RESULT)0x0004A304L)

//
// MessageId: EMS_COLL_PASS_STOP
//
// MessageText:
//
// EMS Collector Service Stopped Pass for Sat %1.
//
#define EMS_COLL_PASS_STOP               ((EMS_RESULT)0x0004A305L)

//
// MessageId: EMS_COLL_ERROR
//
// MessageText:
//
// EMS Collector reports error (%1).
//
#define EMS_COLL_ERROR                   ((EMS_RESULT)0x8004A306L)

//
// MessageId: EMS_COLL_AD_OVERFLOW
//
// MessageText:
//
// EMS Collector reports A/D Board overflow
//
#define EMS_COLL_AD_OVERFLOW             ((EMS_RESULT)0x8004A307L)

//
// MessageId: EMS_COLL_RECV_COMMAND
//
// MessageText:
//
// EMS Collector recv'd cmd( %1 ).
//
#define EMS_COLL_RECV_COMMAND            ((EMS_RESULT)0x0004A308L)

//
// MessageId: EMS_COLL_WARN_MISSING_BUFFER
//
// MessageText:
//
// EMS Collector hasn't received a buffer in %1 seconds, resetting.
//
#define EMS_COLL_WARN_MISSING_BUFFER     ((EMS_RESULT)0x8004A309L)

//
// MessageId: EMS_COLL_ALARM_MISSING_BUFFER
//
// MessageText:
//
// EMS Collector hasn't received a buffer in %1 seconds, stopping.
//
#define EMS_COLL_ALARM_MISSING_BUFFER    ((EMS_RESULT)0xC004A309L)

//
// MessageId: EMS_COLL_WARN_ADBOARD_INIT_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to initialize AD Board, resetting. (%1)
//
#define EMS_COLL_WARN_ADBOARD_INIT_FAILED ((EMS_RESULT)0x8004A30AL)

//
// MessageId: EMS_COLL_ALARM_ADBOARD_INIT_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to initialize AD Board, stopping. (%1) 
//
#define EMS_COLL_ALARM_ADBOARD_INIT_FAILED ((EMS_RESULT)0xC004A30AL)

//
// MessageId: EMS_COLL_WARN_ADBOARD_START_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to start AD Board, resetting. (%1)
//
#define EMS_COLL_WARN_ADBOARD_START_FAILED ((EMS_RESULT)0x8004A30BL)

//
// MessageId: EMS_COLL_ALARM_ADBOARD_START_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to start AD Board, stopping. (%1) 
//
#define EMS_COLL_ALARM_ADBOARD_START_FAILED ((EMS_RESULT)0xC004A30BL)

//
// MessageId: EMS_COLL_ALARM_MEMMARKER
//
// MessageText:
//
// EMS Collector reports memory marker %1 signal.
//
#define EMS_COLL_ALARM_MEMMARKER         ((EMS_RESULT)0x8004A30CL)

//
// MessageId: EMS_COLL_START_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a start command was received.
//
#define EMS_COLL_START_RECEIVED          ((EMS_RESULT)0x4004A30DL)

//
// MessageId: EMS_COLL_STOP_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a stop command was received.
//
#define EMS_COLL_STOP_RECEIVED           ((EMS_RESULT)0x4004A30EL)

//
// MessageId: EMS_COLL_SAT_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a set satellite command was received.  SatID = %1, Flags = %2, Bandwidth = %3.
//
#define EMS_COLL_SAT_RECEIVED            ((EMS_RESULT)0x4004A30FL)

//
// MessageId: EMS_COLL_INPUTID_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a set input identifier command was received.  InputID = %1.
//
#define EMS_COLL_INPUTID_RECEIVED        ((EMS_RESULT)0x4004A310L)

//
// MessageId: EMS_COLL_START_UNINIT_FAILED
//
// MessageText:
//
// EMS Collector reports attempt to start collection on an uninitialized A/D Board (%1) Channel (%2).
//
#define EMS_COLL_START_UNINIT_FAILED     ((EMS_RESULT)0xC004A311L)

//
// MessageId: EMS_COLL_STATUS_UPDATE_FAILED
//
// MessageText:
//
// EMS Collector reports error attempting to update status. (%1)
//
#define EMS_COLL_STATUS_UPDATE_FAILED    ((EMS_RESULT)0x4004A312L)

//
// MessageId: EMS_COLL_NO_AD_CHANNELS
//
// MessageText:
//
// EMS Collector reports that A/D Board has no available channels.
//
#define EMS_COLL_NO_AD_CHANNELS          ((EMS_RESULT)0xC004A313L)

//
// MessageId: EMS_CS_WARN_MISSING_BUFFER
//
// MessageText:
//
// EMS CollectorStub hasn't received a buffer in %1 seconds, resetting.
//
#define EMS_CS_WARN_MISSING_BUFFER       ((EMS_RESULT)0x8004A314L)

//
// MessageId: EMS_CS_ALARM_MISSING_BUFFER
//
// MessageText:
//
// EMS CollectorStub hasn't received a buffer in %1 seconds, stopping.
//
#define EMS_CS_ALARM_MISSING_BUFFER      ((EMS_RESULT)0xC004A314L)

//
// MessageId: EMS_CS_FP_COMMS_FAILED
//
// MessageText:
//
// EMS CollectorStub failed to communicate with FP (%1)
//
#define EMS_CS_FP_COMMS_FAILED           ((EMS_RESULT)0xC004A315L)

//
// MessageId: EMS_CS_FP_COMMS_RESTORED
//
// MessageText:
//
// EMS CollectorStub communications restored to FP.
//
#define EMS_CS_FP_COMMS_RESTORED         ((EMS_RESULT)0x4004A316L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_OFF_ALARM
//
// MessageText:
//
// EMS Collector reports that the one pulse per second signal has not been detected for %1 seconds.
//
#define EMS_COLL_1PPS_SIGNAL_OFF_ALARM   ((EMS_RESULT)0xC004A317L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_OFF
//
// MessageText:
//
// EMS Collector reports that the one pulse per second signal was not detected in the last collected data buffer.
//
#define EMS_COLL_1PPS_SIGNAL_OFF         ((EMS_RESULT)0x4004A318L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_ON
//
// MessageText:
//
// EMS Collector reports that after an outage, the one pulse per second signal is now being detected.
//
#define EMS_COLL_1PPS_SIGNAL_ON          ((EMS_RESULT)0x4004A319L)

//
// MessageId: EMS_COLL_ERROR_SENDING_DATA
//
// MessageText:
//
// EMS Collector reports an error sending data.  Error code = %1.  Disconnecting.
//
#define EMS_COLL_ERROR_SENDING_DATA      ((EMS_RESULT)0x8004A31AL)

//
// MessageId: EMS_COLL_TRANSMITTING
//
// MessageText:
//
// EMS Collector reports transmitting Wave with time = %1 (%2).
//
#define EMS_COLL_TRANSMITTING            ((EMS_RESULT)0x4004A31BL)

//
// MessageId: EMS_COLL_ERROR_SENDING_WAVE_RECORD
//
// MessageText:
//
// EMS Collector reports an error sending wave record.
//
#define EMS_COLL_ERROR_SENDING_WAVE_RECORD ((EMS_RESULT)0x8004A31CL)

//
// MessageId: EMS_COLL_COMMON_INFO_MEG
//
// MessageText:
//
// EMS Collector reports %1.
//
#define EMS_COLL_COMMON_INFO_MEG         ((EMS_RESULT)0x4004A31DL)

//
// MessageId: EMS_COLL_DATA_DEST_OFFLINE
//
// MessageText:
//
// EMS Collector reports connection failed.  Data destination is offline.  Error code = %1.
//
#define EMS_COLL_DATA_DEST_OFFLINE       ((EMS_RESULT)0x8004A31EL)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: %3.
//
#define EMS_COLL_DC_DEBUG_MSG            ((EMS_RESULT)0x4004A31FL)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_MARKER_INDEX
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Last  marker index = %3, This marker index = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_MARKER_INDEX ((EMS_RESULT)0x4004A320L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_MARKER_BIT_INDEX
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Marker bit index calculated as %3.
//
#define EMS_COLL_DC_DEBUG_MSG_MARKER_BIT_INDEX ((EMS_RESULT)0x4004A321L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_BUF_TIME
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Original Data Buffer Time = %3 (%4).
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_BUF_TIME ((EMS_RESULT)0x4004A322L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_NAROSEC_OFFSET
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Nanosecond offset %3.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_NAROSEC_OFFSET ((EMS_RESULT)0x4004A323L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_SEC_DIFF
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between time of last buffer and this buffer is %3 seconds.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_SEC_DIFF ((EMS_RESULT)0x4004A324L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_1
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers exceeds 1.1 seconds. Last time = %3, this time = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_1 ((EMS_RESULT)0x4004A325L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_2
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers less than 1.0 second. Last time = %3, this time = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_2 ((EMS_RESULT)0x4004A326L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_ADJUSTED_TIME
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Adjusted Time = %3 (%4).
//
#define EMS_COLL_DC_DEBUG_MSG_ADJUSTED_TIME ((EMS_RESULT)0x4004A327L)


#endif // INC_COLLMSGS