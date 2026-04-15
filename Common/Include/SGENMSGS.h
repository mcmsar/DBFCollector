/********************************************************************
*	Module:			SGenMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Sit Generator Messages
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
#ifndef INC_SGENMSGS
#define INC_SGENMSGS

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
// MessageId: EMS_SITGEN_BASE_CODE
//
// MessageText:
//
// EMS SitGen Error
//
#define EMS_SITGEN_BASE_CODE             ((EMS_RESULT)0x0004B200L)

//
// MessageId: EMS_SITGEN_SERVICE_START
//
// MessageText:
//
// EMS SitGen Service Started
//
#define EMS_SITGEN_SERVICE_START         ((EMS_RESULT)0x0004B201L)

//
// MessageId: EMS_SITGEN_SERVICE_FAILED
//
// MessageText:
//
// EMS SitGen Service did not start due to error %1
//
#define EMS_SITGEN_SERVICE_FAILED        ((EMS_RESULT)0x0004B202L)

//
// MessageId: EMS_SITGEN_SERVICE_STOP
//
// MessageText:
//
// EMS SitGen Service Stopped
//
#define EMS_SITGEN_SERVICE_STOP          ((EMS_RESULT)0x0004B203L)

//
// MessageId: EMS_SITGEN_ERROR
//
// MessageText:
//
// EMS SitGen reports error %1.
//
#define EMS_SITGEN_ERROR                 ((EMS_RESULT)0x8004B204L)

//
// MessageId: EMS_SITGEN_PIPELINE_CONNECT_ERROR
//
// MessageText:
//
// EMS SitGen reports error %1 while trying to connect to the pipeline.
//
#define EMS_SITGEN_PIPELINE_CONNECT_ERROR ((EMS_RESULT)0x8004B205L)

//
// MessageId: EMS_SITGEN_NO_SITEINFO
//
// MessageText:
//
// EMS SitGen reports error trying to access the site info.
//
#define EMS_SITGEN_NO_SITEINFO           ((EMS_RESULT)0x8004B206L)

//
// MessageId: EMS_SITGEN_NO_LOGGER
//
// MessageText:
//
// EMS SitGen reports error trying to connect to the logger.
//
#define EMS_SITGEN_NO_LOGGER             ((EMS_RESULT)0x8004B207L)

//
// MessageId: EMS_SITGEN_INVALID_SEND_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing send directory( %1 ).
//
#define EMS_SITGEN_INVALID_SEND_DIR      ((EMS_RESULT)0x8004B208L)

//
// MessageId: EMS_SITGEN_FILE_CREATE_ERR
//
// MessageText:
//
// EMS SitGen reports error trying to create file (%1).
//
#define EMS_SITGEN_FILE_CREATE_ERR       ((EMS_RESULT)0x8004B209L)

//
// MessageId: EMS_SITGEN_INVALID_SENT_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing sent directory( %1 ).
//
#define EMS_SITGEN_INVALID_SENT_DIR      ((EMS_RESULT)0x8004B20AL)

//
// MessageId: EMS_SITGEN_INVALID_UNDELIVERED_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing undelivered directory( %1 ).
//
#define EMS_SITGEN_INVALID_UNDELIVERED_DIR ((EMS_RESULT)0x8004B20BL)

//
// MessageId: EMS_SITGEN_UNKNOWN_DEST
//
// MessageText:
//
// EMS SitGen reports error trying to identify dest ID %1.
//
#define EMS_SITGEN_UNKNOWN_DEST          ((EMS_RESULT)0x8004B20CL)

//
// MessageId: EMS_SITGEN_RESEND_BUSY
//
// MessageText:
//
// EMS SitGen rejected retransmit request from dest ID %1.
//
#define EMS_SITGEN_RESEND_BUSY           ((EMS_RESULT)0x8004B20DL)

//
// MessageId: EMS_SITGEN_RESEND_REQ
//
// MessageText:
//
// EMS SitGen received request from dest ID %1 msgs to be resent.
//
#define EMS_SITGEN_RESEND_REQ            ((EMS_RESULT)0x0004B20EL)

//
// MessageId: EMS_SITGEN_RESEND_RESULT
//
// MessageText:
//
// EMS SitGen resent dest ID %1 messages.
//
#define EMS_SITGEN_RESEND_RESULT         ((EMS_RESULT)0x0004B20FL)

//
// MessageId: EMS_SITGEN_NO_ORBIT
//
// MessageText:
//
// EMS SitGen cannot create orbit interface (%1).
//
#define EMS_SITGEN_NO_ORBIT              ((EMS_RESULT)0x0004B210L)

//
// MessageId: EMS_SITGEN_SELECTION_EMPTY
//
// MessageText:
//
// EMS SitGen reports no data to reply to the request.
//
#define EMS_SITGEN_SELECTION_EMPTY       ((EMS_RESULT)0x8004B211L)

//
// MessageId: EMS_SITGEN_SELECTION_LIMIT
//
// MessageText:
//
// EMS SitGen reports too much data to reply to the request.
//
#define EMS_SITGEN_SELECTION_LIMIT       ((EMS_RESULT)0x8004B212L)

//
// MessageId: EMS_SITGEN_UNKNOWN_REQUEST
//
// MessageText:
//
// EMS SitGen reports unknown SendData ( %1 ) request.
//
#define EMS_SITGEN_UNKNOWN_REQUEST       ((EMS_RESULT)0x8004B213L)

//
// MessageId: EMS_SITGEN_NO_DEST_SIT
//
// MessageText:
//
// EMS SitGen reports SIT format not defined by destination.
//
#define EMS_SITGEN_NO_DEST_SIT           ((EMS_RESULT)0x8004B214L)

//
// MessageId: EMS_SITGEN_TRACER
//
// MessageText:
//
// EMS SitGen tracer ( %1 ).
//
#define EMS_SITGEN_TRACER                ((EMS_RESULT)0x0004B215L)

//
// MessageId: EMS_SITGEN_SUPPRESSED
//
// MessageText:
//
// EMS SitGen suppressed %1 alerts.
//
#define EMS_SITGEN_SUPPRESSED            ((EMS_RESULT)0x0004B216L)

//
// MessageId: EMS_SITGEN_ALERT_FILTER
//
// MessageText:
//
// EMS SitGen reports finding an Alert Filter module.
//
#define EMS_SITGEN_ALERT_FILTER          ((EMS_RESULT)0x0004B217L)

//
// MessageId: EMS_SITGEN_NO_ALERT_FILTER
//
// MessageText:
//
// EMS SitGen reports no Alert Filter module found.
//
#define EMS_SITGEN_NO_ALERT_FILTER       ((EMS_RESULT)0x0004B218L)

//
// MessageId: EMS_SITGEN_RESEND_REQ_NODATA
//
// MessageText:
//
// EMS SitGen reports failed resend request.  The requested messages %1 cannot be found.
//
#define EMS_SITGEN_RESEND_REQ_NODATA     ((EMS_RESULT)0x8004B219L)

//
// MessageId: EMS_SITGEN_RESEND_REQ_FAILED
//
// MessageText:
//
// EMS SitGen reports failed resend request.  The request for messages %1 could not be processed.
//
#define EMS_SITGEN_RESEND_REQ_FAILED     ((EMS_RESULT)0x8004B21AL)

//
// MessageId: EMS_SITGEN_MSG_SIZE_UNKNOWN
//
// MessageText:
//
// EMS SitGen reports failure retrieving configured value for maximum SIT message size.
//
#define EMS_SITGEN_MSG_SIZE_UNKNOWN      ((EMS_RESULT)0x8004B21BL)

//
// MessageId: EMS_SITGEN_NO_CM
//
// MessageText:
//
// EMS SitGen reports failure initializing the Configuration Manager.  Error code = %1.
//
#define EMS_SITGEN_NO_CM                 ((EMS_RESULT)0x8004B21CL)

//
// MessageId: EMS_SITGEN_NO_SECURITY_TOKEN
//
// MessageText:
//
// EMS SitGen reports failure retrieving a security token.  Error code = %1.
//
#define EMS_SITGEN_NO_SECURITY_TOKEN     ((EMS_RESULT)0x8004B21DL)

//
// MessageId: EMS_SITGEN_TRACE_ENTER
//
// MessageText:
//
// EMS SitGen tracer ( ** Enter: Sit (%1) )
//
#define EMS_SITGEN_TRACE_ENTER           ((EMS_RESULT)0x0004B21EL)

//
// MessageId: EMS_SITGEN_TRACE_EXIT
//
// MessageText:
//
// EMS SitGen tracer ( ** Exit: Sit (%1) )
//
#define EMS_SITGEN_TRACE_EXIT            ((EMS_RESULT)0x0004B21FL)

//
// MessageId: EMS_SITGEN_TRACE_SELN
//
// MessageText:
//
// EMS SitGen tracer ( Selection (%1) - (%2) )
//
#define EMS_SITGEN_TRACE_SELN            ((EMS_RESULT)0x0004B220L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIG
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=%2 )
//
#define EMS_SITGEN_TRACE_CONFIG          ((EMS_RESULT)0x0004B221L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIGYES
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=yes )
//
#define EMS_SITGEN_TRACE_CONFIGYES       ((EMS_RESULT)0x0004B222L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIGNO
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=no )
//
#define EMS_SITGEN_TRACE_CONFIGNO        ((EMS_RESULT)0x0004B223L)

//
// MessageId: EMS_SITGEN_TRACE_SATEPOCH
//
// MessageText:
//
// EMS SitGen tracer ( Sat=%1, Epoch=%2 )
//
#define EMS_SITGEN_TRACE_SATEPOCH        ((EMS_RESULT)0x0004B224L)

//
// MessageId: EMS_SITGEN_TRACE_DEST
//
// MessageText:
//
// EMS SitGen tracer ( Dest %1 - %2 dwFlags(%3) )
//
#define EMS_SITGEN_TRACE_DEST            ((EMS_RESULT)0x0004B225L)

//
// MessageId: EMS_SITGEN_TRACE_CHARMAPINUSE
//
// MessageText:
//
// EMS SitGen: Dest %1 has character mapping specified (%2)
//
#define EMS_SITGEN_TRACE_CHARMAPINUSE    ((EMS_RESULT)0x0004B226L)

//
// MessageId: EMS_SITGEN_LINE_LIMIT_EXCEEDED
//
// MessageText:
//
// EMS SitGen: Maximum allowed line length for a sit message has been exceeded.
//
#define EMS_SITGEN_LINE_LIMIT_EXCEEDED   ((EMS_RESULT)0x8004B227L)

//
// MessageId: EMS_SITGEN_BEACON_SUPPRESSED_FOR_DEST
//
// MessageText:
//
// EMS SitGen: Alert suppressed (Beacon: %1, Dest: %2).
//
#define EMS_SITGEN_BEACON_SUPPRESSED_FOR_DEST ((EMS_RESULT)0x0004B228L)

//
// MessageId: EMS_SITGEN_MF_RANGE_EXCEEDED
//
// MessageText:
//
// EMS SitGen: %1 %2 value was adjusted before being output (%3 changed to %4).
//
#define EMS_SITGEN_MF_RANGE_EXCEEDED     ((EMS_RESULT)0x0004B229L)

//
// MessageId: EMS_SITGEN_SENDDATA_FAILED
//
// MessageText:
//
// EMS SitGen reports error trying to process "SendData" command (SIT Number=%1, dest ID=%2, Error - %3).
//
#define EMS_SITGEN_SENDDATA_FAILED       ((EMS_RESULT)0x8004B22AL)

//
// MessageId: EMS_SIT_ALREADY_INITIALIZED
//
// MessageText:
//
// Programming error: SIT message has already been initialized.
//
#define EMS_SIT_ALREADY_INITIALIZED      ((EMS_RESULT)0x8004B22BL)

//
// MessageId: EMS_SIT_CANT_CONNECT_SEQ_NUM_WEB_SRVC
//
// MessageText:
//
// Can't connect to Sequence Number Generator Web Service(%s:%d): %s
//
#define EMS_SIT_CANT_CONNECT_SEQ_NUM_WEB_SRVC ((EMS_RESULT)0x8004B22CL)


#endif // INC_SGENMSGS
