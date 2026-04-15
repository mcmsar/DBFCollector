/********************************************************************
*	Module:			EMSErrorMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Errors & Messages
*
*					Defined here so that the numbering remains unchanged
*					Note that this file actually contains multiple "categories".
*					Specifically:
*						EMSCAT_GENERAL
*						EMSCAT_MATH
*						EMSCAT_COMM
*						EMSCAT_IRDA
*						EMSCAT_TFTP
*						EMSCAT_COMP
*						EMSCAT_RPC
*
*					The file also ensures that there are error codes and messages
*					for the following standard Microsoft errors
*						EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
*						EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
*						EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111
*
*					The following errors were also moved here ...
*						Satellite errors ... EMSATFINFO.idl
*						SIT errors ... emssit.h
*						COMM errors ... AntError.h
*						ALTIT errors ... emsaltit.idl
*						BEACON errors ... emsbeacn.idl
*						REFRACTION errors ... emsfract.idl
*						SITEINFO errors ... emssiteif.idl
*						LUT errors ... emslinfo.idl
*						ORBIT errors ... emsorbit.idl
*						PASS errors ... emspass.idl
*						STATUS errors ... emsstatus.idl
*						TLE Server errors ... emsTLEServer.idl
*						Logger errors ... emsloggr.idl
*						GPS errors ... gpsclock.h
*						LOCATE errors ... LocateError.h
*
*					Note that these have been defined here (rather than in
*					a set of new mc files to minimize the number of files
*					that need to be changed.
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/



#ifndef INC_EMSERRORMSG
#define INC_EMSERRORMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

// *** EMSCAT_GENERAL = 0x80 ***

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
// MessageId: EMSCAT_GENERAL_BASE_CODE
//
// MessageText:
//
//  General messages.
//
#define EMSCAT_GENERAL_BASE_CODE         ((EMS_RESULT)0x00048000L)

//
// MessageId: EMS_NO_MEMORY
//
// MessageText:
//
//  An out of memory error has been detected.
//
#define EMS_NO_MEMORY                    ((EMS_RESULT)0x80048001L)

//
// MessageId: EMS_FILE_NOT_FOUND
//
// MessageText:
//
//  The specified file cannot be found.
//
#define EMS_FILE_NOT_FOUND               ((EMS_RESULT)0x80048002L)

//
// MessageId: EMS_UNKNOWN_ERROR
//
// MessageText:
//
//  An unexpected error has been detected.
//
#define EMS_UNKNOWN_ERROR                ((EMS_RESULT)0x80048003L)

//
// MessageId: EMS_INVALID_HANDLE
//
// MessageText:
//
//  An invalid handle has been detected.
//
#define EMS_INVALID_HANDLE               ((EMS_RESULT)0x80048004L)

//
// MessageId: EMS_HANDLE_EOF
//
// MessageText:
//
//  Unexpectedly reached end of file.
//
#define EMS_HANDLE_EOF                   ((EMS_RESULT)0x80048005L)

//
// MessageId: EMS_FILE_EXISTS
//
// MessageText:
//
//  Specified file already exists.
//
#define EMS_FILE_EXISTS                  ((EMS_RESULT)0x80048006L)

//
// MessageId: EMS_EOF
//
// MessageText:
//
//  Unexpectedly reached end of file.
//
#define EMS_EOF                          ((EMS_RESULT)0x80048007L)

//
// MessageId: EMS_NO_FILE
//
// MessageText:
//
//  File could not be opened.
//
#define EMS_NO_FILE                      ((EMS_RESULT)0x80048008L)

//
// MessageId: EMS_UNSUPPORTED
//
// MessageText:
//
//  Unsupported request has been made.
//
#define EMS_UNSUPPORTED                  ((EMS_RESULT)0x80048009L)

//
// MessageId: EMS_IO_ERROR
//
// MessageText:
//
//  I/O error detected.
//
#define EMS_IO_ERROR                     ((EMS_RESULT)0x8004800AL)

//
// MessageId: EMS_NOT_IMPLEMENTED
//
// MessageText:
//
//  Requested functionality has not been implemented.
//
#define EMS_NOT_IMPLEMENTED              ((EMS_RESULT)0x8004800BL)

//
// MessageId: EMS_ALREADY_INSTALLED
//
// MessageText:
//
//  Requested functionality has already been installed.
//
#define EMS_ALREADY_INSTALLED            ((EMS_RESULT)0x8004800CL)

//
// MessageId: EMS_CANNOT_UNINSTALL
//
// MessageText:
//
//  Cannot uninstall.
//
#define EMS_CANNOT_UNINSTALL             ((EMS_RESULT)0x8004800DL)

//
// MessageId: EMS_PATH_NOT_FOUND
//
// MessageText:
//
//  Specified path not found.
//
#define EMS_PATH_NOT_FOUND               ((EMS_RESULT)0x8004800EL)

//
// MessageId: EMS_ACCESS_DENIED
//
// MessageText:
//
//  Access denied.
//
#define EMS_ACCESS_DENIED                ((EMS_RESULT)0x8004800FL)

//
// MessageId: EMS_BAD_PARAM
//
// MessageText:
//
//  Invalid parameter received.
//
#define EMS_BAD_PARAM                    ((EMS_RESULT)0x80048010L)

//
// MessageId: EMS_DISK_FULL
//
// MessageText:
//
//  Disk is full.
//
#define EMS_DISK_FULL                    ((EMS_RESULT)0x80048011L)

//
// MessageId: EMS_NO_DEVICE
//
// MessageText:
//
//  No device.
//
#define EMS_NO_DEVICE                    ((EMS_RESULT)0x80048012L)

//
// MessageId: EMS_ALREADY_OPEN
//
// MessageText:
//
//  Specified resource is already open.
//
#define EMS_ALREADY_OPEN                 ((EMS_RESULT)0x80048013L)

//
// MessageId: EMS_INVALID_CMD
//
// MessageText:
//
//  Invalid command received.
//
#define EMS_INVALID_CMD                  ((EMS_RESULT)0x80048014L)

//
// MessageId: EMS_UNAVAIL
//
// MessageText:
//
//  Specified resource is unavailable.
//
#define EMS_UNAVAIL                      ((EMS_RESULT)0x80048015L)

//
// MessageId: EMS_INVALID_TIME
//
// MessageText:
//
//  Invalid time specified.
//
#define EMS_INVALID_TIME                 ((EMS_RESULT)0x80048016L)

//
// MessageId: EMS_ALREADY_INITIALIZED
//
// MessageText:
//
//  Request to initialize device or service that has already been initialized.
//
#define EMS_ALREADY_INITIALIZED          ((EMS_RESULT)0x80048017L)

//
// MessageId: EMS_NOT_INITIALIZED
//
// MessageText:
//
//  Request to access device or service that has not been initialized.
//
#define EMS_NOT_INITIALIZED              ((EMS_RESULT)0x80048018L)

//
// MessageId: EMS_NOT_DESIRED_LANGUAGE
//
// MessageText:
//
//  Failed to load specified language.
//
#define EMS_NOT_DESIRED_LANGUAGE         ((EMS_RESULT)0x80048019L)

//
// MessageId: EMS_INVALID_FILESPEC
//
// MessageText:
//
//  Invalid file specification.
//
#define EMS_INVALID_FILESPEC             ((EMS_RESULT)0x8004801AL)

//
// MessageId: EMS_OVERFLOW
//
// MessageText:
//
//  Overflow detected.
//
#define EMS_OVERFLOW                     ((EMS_RESULT)0x8004801BL)

//
// MessageId: EMS_EMPTY
//
// MessageText:
//
//  Empty dataset.
//
#define EMS_EMPTY                        ((EMS_RESULT)0x8004801CL)

//
// MessageId: EMS_INVALID_PTR
//
// MessageText:
//
//  Invalid pointer detected.
//
#define EMS_INVALID_PTR                  ((EMS_RESULT)0x8004801DL)

//
// MessageId: EMS_GPS_NOT_TRACK
//
// MessageText:
//
//  GPS is not tracking.
//
#define EMS_GPS_NOT_TRACK                ((EMS_RESULT)0x8004801EL)

//
// MessageId: EMS_TRUNCATED
//
// MessageText:
//
//  Truncated data detected.
//
#define EMS_TRUNCATED                    ((EMS_RESULT)0x8004801FL)

//
// MessageId: EMS_INVALID_STREAM
//
// MessageText:
//
//  Invalid stream detected.
//
#define EMS_INVALID_STREAM               ((EMS_RESULT)0x80048020L)

//
// MessageId: EMS_LINE_LIMIT_EXCEEDED
//
// MessageText:
//
//  Line limit exceeded.
//
#define EMS_LINE_LIMIT_EXCEEDED          ((EMS_RESULT)0x80048021L)

//
// MessageId: EMS_EXCEPTION
//
// MessageText:
//
//  Unhandled exception detected.
//
#define EMS_EXCEPTION                    ((EMS_RESULT)0x80048022L)

//
// MessageId: EMS_EXCEPTION_CONTEXT
//
// MessageText:
//
//  Unhandled exception detected (%1 : %2).
//
#define EMS_EXCEPTION_CONTEXT            ((EMS_RESULT)0x80048023L)

//
// MessageId: EMS_MISSING_B_SIDE
//
// MessageText:
//
//  Missing B side.
//
#define EMS_MISSING_B_SIDE               ((EMS_RESULT)0x80048024L)

//
// MessageId: EMS_EOL
//
// MessageText:
//
//  End of line reached.
//
#define EMS_EOL                          ((EMS_RESULT)0x80048025L)

//
// MessageId: EMS_SYNTAX_ERROR
//
// MessageText:
//
//  Syntax error detected.
//
#define EMS_SYNTAX_ERROR                 ((EMS_RESULT)0x80048026L)

//
// MessageId: EMS_ERROR_ORBIT_NUMBER_NOT_MATCH
//
// MessageText:
//
//  One or more passes have different orbit numbers.
//
#define EMS_ERROR_ORBIT_NUMBER_NOT_MATCH ((EMS_RESULT)0x80048027L)

//
// MessageId: EMS_UNKNOWN_SERVER_TYPE
//
// MessageText:
//
//  Unknown server type specified.
//
#define EMS_UNKNOWN_SERVER_TYPE          ((EMS_RESULT)0x80048028L)

//
// MessageId: EMS_INVALID_URL
//
// MessageText:
//
//  Invalid URL specified.
//
#define EMS_INVALID_URL                  ((EMS_RESULT)0x80048029L)

//
// MessageId: EMS_INVALID_STREAM_POS
//
// MessageText:
//
//  Invalid stream position specified.
//
#define EMS_INVALID_STREAM_POS           ((EMS_RESULT)0x8004802AL)

//
// MessageId: EMS_UNKNOWN_PARAM_TYPE
//
// MessageText:
//
//  Unknown parameter type specified.
//
#define EMS_UNKNOWN_PARAM_TYPE           ((EMS_RESULT)0x8004802BL)

//
// MessageId: EMS_DATA_INVALID
//
// MessageText:
//
//  Invalid data detected.
//
#define EMS_DATA_INVALID                 ((EMS_RESULT)0x8004802CL)

//
// MessageId: EMS_UNKNOWN_URL_TYPE
//
// MessageText:
//
//  Unknown URL type specified.
//
#define EMS_UNKNOWN_URL_TYPE             ((EMS_RESULT)0x8004802DL)

//
// MessageId: EMS_UNSUPPORTED_URL_TYPE
//
// MessageText:
//
//  Unsupported URL type specified.
//
#define EMS_UNSUPPORTED_URL_TYPE         ((EMS_RESULT)0x8004802EL)

//
// MessageId: EMS_WAIT_TIMEOUT
//
// MessageText:
//
//  A system wait has timed out.
//
#define EMS_WAIT_TIMEOUT                 ((EMS_RESULT)0x8004802FL)

//
// MessageId: EMS_WAIT_ABANDONDED
//
// MessageText:
//
//  A system wait has been abandoned.
//
#define EMS_WAIT_ABANDONDED              ((EMS_RESULT)0x80048030L)

//
// MessageId: EMS_ARRAY_OUT_OF_BOUNDS
//
// MessageText:
//
//  Array out of bounds.
//
#define EMS_ARRAY_OUT_OF_BOUNDS          ((EMS_RESULT)0x80048031L)

//
// MessageId: EMS_OBJECT_CREATE_FAILED
//
// MessageText:
//
//  Failed to create object %1 with error %2.
//
#define EMS_OBJECT_CREATE_FAILED         ((EMS_RESULT)0x80048032L)

//
// MessageId: EMS_QUERY_INTERFACE_ERROR
//
// MessageText:
//
//  Failed to retrieve interface %1 with error %2.
//
#define EMS_QUERY_INTERFACE_ERROR        ((EMS_RESULT)0x80048033L)

//
// MessageId: EMS_NO_MATCHING_RECORD
//
// MessageText:
//
//  No matching record found.
//
#define EMS_NO_MATCHING_RECORD           ((EMS_RESULT)0x80048034L)

//
// MessageId: EMS_DIRECTORY_NOT_EMPTY
//
// MessageText:
//
//  Failed to delete a directory because it is not empty.
//
#define EMS_DIRECTORY_NOT_EMPTY          ((EMS_RESULT)0x80048035L)

//
// MessageId: EMS_BAD_REGISTRY_ENTRY
//
// MessageText:
//
//  Failed to find an expected entry in the registry %1
//
#define EMS_BAD_REGISTRY_ENTRY           ((EMS_RESULT)0x80048036L)


// *** EMSCAT_MATH = 0x81 ***

//
// MessageId: EMSCAT_MATH_BASE_CODE
//
// MessageText:
//
//  Math error messages.
//
#define EMSCAT_MATH_BASE_CODE            ((EMS_RESULT)0x80048100L)

//
// MessageId: EMS_CBCOPY_ZERO_LENGTH
//
// MessageText:
//
//  Zero length cbcopy requested.
//
#define EMS_CBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048101L)

//
// MessageId: EMS_SBCOPY_ZERO_LENGTH
//
// MessageText:
//
//  Zero length sbcopy requested.
//
#define EMS_SBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048102L)

//
// MessageId: EMS_WBCOPY_ZERO_LENGTH
//
// MessageText:
//
//  Zero length wbcopy requested.
//
#define EMS_WBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048103L)


// *** EMSCAT_COMM = 0x82 ***

//
// MessageId: EMSCAT_COMM_BASE_CODE
//
// MessageText:
//
//  Communication error messages.
//
#define EMSCAT_COMM_BASE_CODE            ((EMS_RESULT)0x80048200L)

//
// MessageId: EMS_TIMEOUT
//
// MessageText:
//
//  A timeout was detected.
//
#define EMS_TIMEOUT                      ((EMS_RESULT)0x80048201L)

//
// MessageId: EMS_NOT_OPEN
//
// MessageText:
//
//  Could not open specified device or link.
//
#define EMS_NOT_OPEN                     ((EMS_RESULT)0x80048202L)

//
// MessageId: EMS_TRANSMIT_ERR
//
// MessageText:
//
//  Transmit error detected.
//
#define EMS_TRANSMIT_ERR                 ((EMS_RESULT)0x80048203L)

//
// MessageId: EMS_CHECKSUM_ERR
//
// MessageText:
//
//  Checksum error detected.
//
#define EMS_CHECKSUM_ERR                 ((EMS_RESULT)0x80048204L)

//
// MessageId: EMS_SEQNUMBER_ERR
//
// MessageText:
//
//  Sequence number error detected.
//
#define EMS_SEQNUMBER_ERR                ((EMS_RESULT)0x80048205L)

//
// MessageId: EMS_OP_CANCELLED
//
// MessageText:
//
//  Operation cancelled.
//
#define EMS_OP_CANCELLED                 ((EMS_RESULT)0x80048206L)

//
// MessageId: EMS_ERROR_LIMIT
//
// MessageText:
//
//  Error limit reached.
//
#define EMS_ERROR_LIMIT                  ((EMS_RESULT)0x80048207L)

//
// MessageId: EMS_DUPLICATE_SEQ
//
// MessageText:
//
//  Communications duplicate sequence number detected.
//
#define EMS_DUPLICATE_SEQ                ((EMS_RESULT)0x80048208L)

//
// MessageId: EMS_PACKET_ERR
//
// MessageText:
//
//  Packet error detected.
//
#define EMS_PACKET_ERR                   ((EMS_RESULT)0x80048209L)

//
// MessageId: EMS_UNKNOWN_DATA
//
// MessageText:
//
//  Request to process unknown data.
//
#define EMS_UNKNOWN_DATA                 ((EMS_RESULT)0x8004820AL)

//
// MessageId: EMS_RECV_ERR
//
// MessageText:
//
//  Data receive error.
//
#define EMS_RECV_ERR                     ((EMS_RESULT)0x8004820BL)

//
// MessageId: EMS_OVERRUN_ERR
//
// MessageText:
//
//  Overrun error detected.
//
#define EMS_OVERRUN_ERR                  ((EMS_RESULT)0x8004820CL)

//
// MessageId: EMS_PARITY_ERR
//
// MessageText:
//
//  Parity error detected.
//
#define EMS_PARITY_ERR                   ((EMS_RESULT)0x8004820DL)

//
// MessageId: EMS_FRAMING_ERR
//
// MessageText:
//
//  Framing error detected.
//
#define EMS_FRAMING_ERR                  ((EMS_RESULT)0x8004820EL)

//
// MessageId: EMS_BREAKDETECT_ERR
//
// MessageText:
//
//  Break detected.
//
#define EMS_BREAKDETECT_ERR              ((EMS_RESULT)0x8004820FL)

//
// MessageId: EMS_NO_PACKET_SERVICE
//
// MessageText:
//
//  No packet service available.
//
#define EMS_NO_PACKET_SERVICE            ((EMS_RESULT)0x80048210L)

//
// MessageId: EMS_OP_ABORTED
//
// MessageText:
//
//  Operation aborted.
//
#define EMS_OP_ABORTED                   ((EMS_RESULT)0x80048211L)

//
// MessageId: EMS_NO_COM_PORT
//
// MessageText:
//
//  No COM port available.
//
#define EMS_NO_COM_PORT                  ((EMS_RESULT)0x80048212L)

//
// MessageId: EMS_AZ_RX_FLUSH_ERROR
//
// MessageText:
//
//  AZ/RX flush error.
//
#define EMS_AZ_RX_FLUSH_ERROR            ((EMS_RESULT)0x80048213L)

//
// MessageId: EMS_AZ_TX_FLUSH_ERROR
//
// MessageText:
//
//  AZ/TX flush error.
//
#define EMS_AZ_TX_FLUSH_ERROR            ((EMS_RESULT)0x80048214L)

//
// MessageId: EMS_EL_RX_FLUSH_ERROR
//
// MessageText:
//
//  EL/RX flush error.
//
#define EMS_EL_RX_FLUSH_ERROR            ((EMS_RESULT)0x80048215L)

//
// MessageId: EMS_EL_TX_FLUSH_ERROR
//
// MessageText:
//
//  EL/TX flush error.
//
#define EMS_EL_TX_FLUSH_ERROR            ((EMS_RESULT)0x80048216L)

//
// MessageId: EMS_CANT_OPEN_AZELFILE
//
// MessageText:
//
//  Cannot open AZ/EL file.
//
#define EMS_CANT_OPEN_AZELFILE           ((EMS_RESULT)0x80048217L)

//
// MessageId: EMS_SOCKET_CREATE_ERROR
//
// MessageText:
//
//  Failed to create a socket.  Winsock error is %1.
//
#define EMS_SOCKET_CREATE_ERROR          ((EMS_RESULT)0x80048218L)

//
// MessageId: EMS_SOCKET_STARTUP_ERROR
//
// MessageText:
//
//  Failed to start sockets subsystem.  Winsock error is %1.
//
#define EMS_SOCKET_STARTUP_ERROR         ((EMS_RESULT)0x80048219L)

//
// MessageId: EMS_SOCKET_ACCEPT_DEBUG
//
// MessageText:
//
//  Socket connection accepted.
//
#define EMS_SOCKET_ACCEPT_DEBUG          ((EMS_RESULT)0x4004821AL)

//
// MessageId: EMS_SOCKET_ACCEPT_ERROR
//
// MessageText:
//
//  Failed to accept a socket connection.  Winsock error is %1.
//
#define EMS_SOCKET_ACCEPT_ERROR          ((EMS_RESULT)0x8004821BL)

//
// MessageId: EMS_SOCKET_BIND_DEBUG
//
// MessageText:
//
//  Bound socket to IP=%1, port=%2.
//
#define EMS_SOCKET_BIND_DEBUG            ((EMS_RESULT)0x4004821CL)

//
// MessageId: EMS_SOCKET_BIND_ERROR
//
// MessageText:
//
//  Failed to bind socket to IP=%1, port=%2.  Winsock error is %3.
//
#define EMS_SOCKET_BIND_ERROR            ((EMS_RESULT)0x8004821DL)

//
// MessageId: EMS_SOCKET_CLOSE_ERROR
//
// MessageText:
//
//  Error closing socket.  Winsock error is %1.
//
#define EMS_SOCKET_CLOSE_ERROR           ((EMS_RESULT)0x8004821EL)

//
// MessageId: EMS_SOCKET_CONNECT_DEBUG
//
// MessageText:
//
//  Connected to socket at IP=%1, port=%2.
//
#define EMS_SOCKET_CONNECT_DEBUG         ((EMS_RESULT)0x4004821FL)

//
// MessageId: EMS_SOCKET_CONNECT_ERROR
//
// MessageText:
//
//  Failed to connect socket to IP=%1, port=%2.  Winsock error is %3.
//
#define EMS_SOCKET_CONNECT_ERROR         ((EMS_RESULT)0x80048220L)

//
// MessageId: EMS_SOCKET_LISTEN_DEBUG
//
// MessageText:
//
//  Listening for connections on socket.
//
#define EMS_SOCKET_LISTEN_DEBUG          ((EMS_RESULT)0x40048221L)

//
// MessageId: EMS_SOCKET_LISTEN_ERROR
//
// MessageText:
//
//  Error listening for socket connection.  Winsock error is %1.
//
#define EMS_SOCKET_LISTEN_ERROR          ((EMS_RESULT)0x80048222L)

//
// MessageId: EMS_SOCKET_RECV_DEBUG
//
// MessageText:
//
//  Received %1 bytes on socket.
//
#define EMS_SOCKET_RECV_DEBUG            ((EMS_RESULT)0x40048223L)

//
// MessageId: EMS_SOCKET_RECV_ERROR
//
// MessageText:
//
//  Error receiving on socket.  Winsock error is %1.
//
#define EMS_SOCKET_RECV_ERROR            ((EMS_RESULT)0x80048224L)

//
// MessageId: EMS_SOCKET_SENDREQ_DEBUG
//
// MessageText:
//
//  Requesting send of %1 bytes with WS2 flags = %2.
//
#define EMS_SOCKET_SENDREQ_DEBUG         ((EMS_RESULT)0x40048225L)

//
// MessageId: EMS_SOCKET_SEND_ERROR
//
// MessageText:
//
//  Error sending on socket.  Winsock error is %1.
//
#define EMS_SOCKET_SEND_ERROR            ((EMS_RESULT)0x80048226L)

//
// MessageId: EMS_SOCKET_SEND_DEBUG
//
// MessageText:
//
//  Sent %1 bytes on socket.
//
#define EMS_SOCKET_SEND_DEBUG            ((EMS_RESULT)0x40048227L)

//
// MessageId: EMS_SOCKET_SHUTDOWN_ERROR
//
// MessageText:
//
//  Error shutting down socket.  Winsock error is %1.
//
#define EMS_SOCKET_SHUTDOWN_ERROR        ((EMS_RESULT)0x80048228L)

//
// MessageId: EMS_SOCKET_SHUTDOWN_DEBUG
//
// MessageText:
//
//  Socket was shutdown.
//
#define EMS_SOCKET_SHUTDOWN_DEBUG        ((EMS_RESULT)0x40048229L)

//
// MessageId: EMS_SOCKET_SELECT_ERROR
//
// MessageText:
//
//  Error selecting socket status.  Winsock error is %1.
//
#define EMS_SOCKET_SELECT_ERROR          ((EMS_RESULT)0x8004822AL)

//
// MessageId: EMS_SOCKET_SELECT_READ_DEBUG
//
// MessageText:
//
//  Socket read status is %1.
//
#define EMS_SOCKET_SELECT_READ_DEBUG     ((EMS_RESULT)0x4004822BL)

//
// MessageId: EMS_SOCKET_SELECT_WRITE_DEBUG
//
// MessageText:
//
//  Socket write status is %1.
//
#define EMS_SOCKET_SELECT_WRITE_DEBUG    ((EMS_RESULT)0x4004822CL)

//
// MessageId: EMS_SOCKET_FAMILY_ERROR
//
// MessageText:
//
//  Unrecognized socket address family encountered.
//
#define EMS_SOCKET_FAMILY_ERROR          ((EMS_RESULT)0x8004822DL)

//
// MessageId: EMS_SNMP_CREATEFAILED
//
// MessageText:
//
//  Failed to initialize SNMP communications.
//
#define EMS_SNMP_CREATEFAILED            ((EMS_RESULT)0x8004822EL)


// *** EMSCAT_IRDA = 0x83 ***

//
// MessageId: EMSCAT_IRDA_BASE_CODE
//
// MessageText:
//
//  IrDA error messages.
//
#define EMSCAT_IRDA_BASE_CODE            ((EMS_RESULT)0x80048300L)

//
// MessageId: EMS_IRDA_NOT_FOUND
//
// MessageText:
//
//  IrDA: not found.
//
#define EMS_IRDA_NOT_FOUND               ((EMS_RESULT)0x80048301L)

//
// MessageId: EMS_IRDA_NOT_ACTIVE
//
// MessageText:
//
//  IrDA: not active.
//
#define EMS_IRDA_NOT_ACTIVE              ((EMS_RESULT)0x80048302L)

//
// MessageId: EMS_IRDA_NO_CONNECTION
//
// MessageText:
//
//  IrDA: no connection.
//
#define EMS_IRDA_NO_CONNECTION           ((EMS_RESULT)0x80048303L)

//
// MessageId: EMS_IRDA_IN_USE
//
// MessageText:
//
//  IrDA: in use.
//
#define EMS_IRDA_IN_USE                  ((EMS_RESULT)0x80048304L)


// *** EMSCAT_TFTP = 0x84 ***

//
// MessageId: EMSCAT_TFTP_BASE_CODE
//
// MessageText:
//
//  TFTP error messages.
//
#define EMSCAT_TFTP_BASE_CODE            ((EMS_RESULT)0x80048400L)

//
// MessageId: EMS_TFTP_ERROR
//
// MessageText:
//
//  TFTP error.
//
#define EMS_TFTP_ERROR                   ((EMS_RESULT)0x80048401L)

//
// MessageId: EMS_TFTP_INVALID_OP
//
// MessageText:
//
//  TFTP error: invalid operation.
//
#define EMS_TFTP_INVALID_OP              ((EMS_RESULT)0x80048402L)

//
// MessageId: EMS_TFTP_UNKNOWN_ID
//
// MessageText:
//
//  TFTP error: unknown id.
//
#define EMS_TFTP_UNKNOWN_ID              ((EMS_RESULT)0x80048403L)


// *** EMSCAT_COMP = 0x85 ***

//
// MessageId: EMSCAT_COMP_BASE_CODE
//
// MessageText:
//
//  Computer error messages.
//
#define EMSCAT_COMP_BASE_CODE            ((EMS_RESULT)0x80048500L)

//
// MessageId: EMS_NO_COMPUTERS
//
// MessageText:
//
//  No computers can be detected.
//
#define EMS_NO_COMPUTERS                 ((EMS_RESULT)0x80048501L)

#define EMS_NO_TERMINALS		EMS_NO_COMPUTERS

//
// MessageId: EMS_GUID_NOT_FOUND
//
// MessageText:
//
//  Specified GUID not found.
//
#define EMS_GUID_NOT_FOUND               ((EMS_RESULT)0x80048502L)

//
// MessageId: EMS_INVALID_DRIVE
//
// MessageText:
//
//  Invalid drive specified.
//
#define EMS_INVALID_DRIVE                ((EMS_RESULT)0x80048503L)

//
// MessageId: EMS_MULTIPLEX_ERR
//
// MessageText:
//
//  Multiplex error detected.
//
#define EMS_MULTIPLEX_ERR                ((EMS_RESULT)0x80048504L)

//
// MessageId: EMS_SERVICE_BUSY_ERR
//
// MessageText:
//
//  Requested service is busy.
//
#define EMS_SERVICE_BUSY_ERR             ((EMS_RESULT)0x80048505L)

//
// MessageId: EMS_UNKNOWN_COMPUTER_TYPE
//
// MessageText:
//
//  Unknown computer type specified.
//
#define EMS_UNKNOWN_COMPUTER_TYPE        ((EMS_RESULT)0x80048506L)

#define EMS_UNKNOWN_TERMTYPE	EMS_UNKNOWN_COMPUTER_TYPE


// *** EMSCAT_RPC = 0x86 ***

//
// MessageId: EMSCAT_RPC_BASE_CODE
//
// MessageText:
//
//  RPC error messages.
//
#define EMSCAT_RPC_BASE_CODE             ((EMS_RESULT)0x80048600L)

//
// MessageId: EMS_RPC_UNKNOWN_PROTOCOL
//
// MessageText:
//
//  RPC error: Unknown protocol specified.
//
#define EMS_RPC_UNKNOWN_PROTOCOL         ((EMS_RESULT)0x80048601L)

//
// MessageId: EMS_RPC_LIMIT_EXCEEDED
//
// MessageText:
//
//  RPC error: Limit exceeded.
//
#define EMS_RPC_LIMIT_EXCEEDED           ((EMS_RESULT)0x80048602L)

//
// MessageId: EMS_RPC_NO_CLIENT
//
// MessageText:
//
//  RPC error: No client.
//
#define EMS_RPC_NO_CLIENT                ((EMS_RESULT)0x80048603L)

//
// MessageId: EMS_RPC_ERROR
//
// MessageText:
//
//  RPC error detected.
//
#define EMS_RPC_ERROR                    ((EMS_RESULT)0x80048604L)

//
// MessageId: EMS_RPC_NOT_CONNECTED
//
// MessageText:
//
//  RPC error: Not connected.
//
#define EMS_RPC_NOT_CONNECTED            ((EMS_RESULT)0x80048605L)

//
// MessageId: EMS_RPC_UNKNOWN_HANDLER
//
// MessageText:
//
//  RPC error: Unknown handler.
//
#define EMS_RPC_UNKNOWN_HANDLER          ((EMS_RESULT)0x80048606L)

//
// MessageId: EMS_RPC_UNKNOWN_METHOD
//
// MessageText:
//
//  RPC error: Unknown method.
//
#define EMS_RPC_UNKNOWN_METHOD           ((EMS_RESULT)0x80048607L)


// *** EMSCAT_ORBIT = 0x89 ***

//
// MessageId: EMSCAT_ORBIT_BASE_CODE
//
// MessageText:
//
//  Orbit errors.
//
#define EMSCAT_ORBIT_BASE_CODE           ((EMS_RESULT)0x80048900L)

//
// MessageId: EMS_NO_ORBIT_OBJ
//
// MessageText:
//
//  No orbit object.
//
#define EMS_NO_ORBIT_OBJ                 ((EMS_RESULT)0x80048901L)

//
// MessageId: EMS_ORBIT_NO_SATELLITE
//
// MessageText:
//
//  Specified satellite not found
//
#define EMS_ORBIT_NO_SATELLITE           ((EMS_RESULT)0x80048902L)

//
// MessageId: EMS_ORBIT_NO_DATA
//
// MessageText:
//
//  No orbit data information has been initialized
//
#define EMS_ORBIT_NO_DATA                ((EMS_RESULT)0x80048903L)

//
// MessageId: EMS_ORBIT_BAD_DATA
//
// MessageText:
//
//  Orbital elements have been corrupted
//
#define EMS_ORBIT_BAD_DATA               ((EMS_RESULT)0x80048904L)

//
// MessageId: EMS_ORBIT_BAD_TLEXNO
//
// MessageText:
//
//  Orbit Constructor - Bad TLE.xno value: Must be > 0
//
#define EMS_ORBIT_BAD_TLEXNO             ((EMS_RESULT)0x80048905L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR1
//
// MessageText:
//
//  Unexpected error at location 1 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR1     ((EMS_RESULT)0x80048906L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR2
//
// MessageText:
//
//  Unexpected error at location 2 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR2     ((EMS_RESULT)0x80048907L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR3
//
// MessageText:
//
//  Unexpected error at location 3 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR3     ((EMS_RESULT)0x80048908L)

//
// MessageId: EMS_ORBIT_USEDEEPSPACE
//
// MessageText:
//
//  Orbit Constructor determined - SHOULD USE DEEP SPACE EPHEMERIS
//
#define EMS_ORBIT_USEDEEPSPACE           ((EMS_RESULT)0x80048909L)

//
// MessageId: EMS_ORBIT_USENEAREARTH
//
// MessageText:
//
//  Orbit Constructor determined - SHOULD USE NEAR EARTH EPHEMERIS
//
#define EMS_ORBIT_USENEAREARTH           ((EMS_RESULT)0x8004890AL)

//
// MessageId: EMS_ORBIT_INVALID_FILESPEC
//
// MessageText:
//
//  EMS Orbit: Could not locate the file SARSAT.TXT
//
#define EMS_ORBIT_INVALID_FILESPEC       ((EMS_RESULT)0x8004890BL)

//
// MessageId: EMS_ORBIT_NO_MEMORY
//
// MessageText:
//
//  EMS Orbit:  Out of memory error has been detected
//
#define EMS_ORBIT_NO_MEMORY              ((EMS_RESULT)0x8004890CL)


// *** EMSCAT_PASS = 0x8A ***

//
// MessageId: EMSCAT_PASS_BASE_CODE
//
// MessageText:
//
//  Pass Schedule Errors
//
#define EMSCAT_PASS_BASE_CODE            ((EMS_RESULT)0x80048A00L)

//
// MessageId: EMS_PASS_NO_DATA
//
// MessageText:
//
//  Pass scheduler: no data.
//
#define EMS_PASS_NO_DATA                 ((EMS_RESULT)0x80048A01L)

//
// MessageId: EMS_PASS_DATA_OVERFLOW
//
// MessageText:
//
//  Pass scheduler: data overflow.
//
#define EMS_PASS_DATA_OVERFLOW           ((EMS_RESULT)0x80048A02L)


// *** EMSCAT_SAT = 0x8B ***

//
// MessageId: EMSCAT_SAT_BASE_CODE
//
// MessageText:
//
//  Satellite error messages.
//
#define EMSCAT_SAT_BASE_CODE             ((EMS_RESULT)0x80048B00L)

//
// MessageId: EMS_NO_SATINFO_OBJ
//
// MessageText:
//
//  Satellite error: no information object available.
//
#define EMS_NO_SATINFO_OBJ               ((EMS_RESULT)0x80048B01L)

//
// MessageId: EMS_SAT_NOT_FOUND
//
// MessageText:
//
//  Satellite error: satellite not found.
//
#define EMS_SAT_NOT_FOUND                ((EMS_RESULT)0x80048B02L)

//
// MessageId: EMS_SAT_NO_DATA
//
// MessageText:
//
//  Satellite error: no data.
//
#define EMS_SAT_NO_DATA                  ((EMS_RESULT)0x80048B03L)

//
// MessageId: EMS_SAT_INVALID
//
// MessageText:
//
//  Satellite error: invalid satellite.
//
#define EMS_SAT_INVALID                  ((EMS_RESULT)0x80048B04L)


// *** EMSCAT_LUT = 0x8D ***

//
// MessageId: EMSCAT_LUT_BASE_CODE
//
// MessageText:
//
//  LUT Info Errors
//
#define EMSCAT_LUT_BASE_CODE             ((EMS_RESULT)0x80048D00L)

//
// MessageId: EMS_NO_LUTINFO_OBJ
//
// MessageText:
//
//  No LUT information object.
//
#define EMS_NO_LUTINFO_OBJ               ((EMS_RESULT)0x80048D01L)

//
// MessageId: EMS_LUT_NOT_FOUND
//
// MessageText:
//
//  LUT not found.
//
#define EMS_LUT_NOT_FOUND                ((EMS_RESULT)0x80048D02L)

//
// MessageId: EMS_LUT_NO_DATA
//
// MessageText:
//
//  LUT no data.
//
#define EMS_LUT_NO_DATA                  ((EMS_RESULT)0x80048D03L)


// *** EMSCAT_STATUS = 0x8F ***

//
// MessageId: EMSCAT_STATUS_BASE_CODE
//
// MessageText:
//
//  Status Errors
//
#define EMSCAT_STATUS_BASE_CODE          ((EMS_RESULT)0x80048F00L)

//
// MessageId: EMS_NO_STATUS_OBJ
//
// MessageText:
//
//  No status object.
//
#define EMS_NO_STATUS_OBJ                ((EMS_RESULT)0x80048F01L)

//
// MessageId: EMS_STATUS_NOT_INIT
//
// MessageText:
//
//  Status not initialized.
//
#define EMS_STATUS_NOT_INIT              ((EMS_RESULT)0x80048F02L)


// *** EMSCAT_LOCATE = 0x90 ***

//
// MessageId: EMSCAT_LOCATE_BASE_CODE
//
// MessageText:
//
//  Locate Errors
//
#define EMSCAT_LOCATE_BASE_CODE          ((EMS_RESULT)0x80049000L)

//
// MessageId: EMS_LOCATE_MEMORYALLOC_ERROR
//
// MessageText:
//
//  Memory allocation error
//
#define EMS_LOCATE_MEMORYALLOC_ERROR     ((EMS_RESULT)0x80049001L)

//
// MessageId: EMS_LOCATE_FILE_ERROR
//
// MessageText:
//
//  Problem opening file
//
#define EMS_LOCATE_FILE_ERROR            ((EMS_RESULT)0x80049002L)

//
// MessageId: EMS_LOCATE_READ_ERROR
//
// MessageText:
//
//  Problem reading file
//
#define EMS_LOCATE_READ_ERROR            ((EMS_RESULT)0x80049003L)

//
// MessageId: EMS_LOCATE_NO_DATA
//
// MessageText:
//
//  No locate data information has been initialized
//
#define EMS_LOCATE_NO_DATA               ((EMS_RESULT)0x80049004L)

//
// MessageId: EMS_LOCATE_IE_NON_CONVERGE
//
// MessageText:
//
//  IE fails to converge
//
#define EMS_LOCATE_IE_NON_CONVERGE       ((EMS_RESULT)0x80049005L)

//
// MessageId: EMS_LOCATE_CN_NON_CONVERGE
//
// MessageText:
//
//  Converge fails to converge
//
#define EMS_LOCATE_CN_NON_CONVERGE       ((EMS_RESULT)0x80049006L)

//
// MessageId: EMS_LOCATE_TCA_OUTOFBOUNDS
//
// MessageText:
//
//  TCA out of bounds
//
#define EMS_LOCATE_TCA_OUTOFBOUNDS       ((EMS_RESULT)0x80049007L)

//
// MessageId: EMS_LOCATE_SOLVE_ERROR
//
// MessageText:
//
//  Solve error
//
#define EMS_LOCATE_SOLVE_ERROR           ((EMS_RESULT)0x80049008L)

//
// MessageId: EMS_LOCATE_NO_POINTS
//
// MessageText:
//
//  No points
//
#define EMS_LOCATE_NO_POINTS             ((EMS_RESULT)0x80049009L)

//
// MessageId: EMS_LOCATE_WLS_NON_CONVERGE
//
// MessageText:
//
//  WLS fails to converge
//
#define EMS_LOCATE_WLS_NON_CONVERGE      ((EMS_RESULT)0x8004900AL)

//
// MessageId: EMS_LOCATE_WRITING_ERROR
//
// MessageText:
//
//  Problem writing file
//
#define EMS_LOCATE_WRITING_ERROR         ((EMS_RESULT)0x8004900BL)


// *** EMSCAT_ADBOARD = 0x98 ***

//
// MessageId: EMSCAT_ADBOARD_BASE_CODE
//
// MessageText:
//
//  A/D error messages.
//
#define EMSCAT_ADBOARD_BASE_CODE         ((EMS_RESULT)0x80049800L)

//
// MessageId: EMS_ADERR_IRQ_INUSE
//
// MessageText:
//
//  A/D error: IRQ in use.
//
#define EMS_ADERR_IRQ_INUSE              ((EMS_RESULT)0x80049801L)

//
// MessageId: EMS_ADERR_FN_POINTER
//
// MessageText:
//
//  A/D error: invalid function pointer.
//
#define EMS_ADERR_FN_POINTER             ((EMS_RESULT)0x80049802L)

//
// MessageId: EMS_ADERR_NO_INIT
//
// MessageText:
//
//  A/D error: not intialized.
//
#define EMS_ADERR_NO_INIT                ((EMS_RESULT)0x80049803L)

//
// MessageId: EMS_ADERR_NO_DLL
//
// MessageText:
//
//  A/D error: missing DLL.
//
#define EMS_ADERR_NO_DLL                 ((EMS_RESULT)0x80049804L)

//
// MessageId: EMS_ADERR_ALREADY_INIT
//
// MessageText:
//
//  A/D error: already intialized.
//
#define EMS_ADERR_ALREADY_INIT           ((EMS_RESULT)0x80049805L)

//
// MessageId: EMS_ADERR_NO_BOARD
//
// MessageText:
//
//  A/D error: no board.
//
#define EMS_ADERR_NO_BOARD               ((EMS_RESULT)0x80049806L)

//
// MessageId: EMS_USBDT_ECODE_ERROR
//
// MessageText:
//
//  A/D board error (%1)
//
#define EMS_USBDT_ECODE_ERROR            ((EMS_RESULT)0x80049807L)


// *** EMSCAT_BEACON = 0x99 ***

//
// MessageId: EMSCAT_BEACON_BASE_CODE
//
// MessageText:
//
//  Ref. Beacon Info Errors
//
#define EMSCAT_BEACON_BASE_CODE          ((EMS_RESULT)0x80049900L)

//
// MessageId: EMS_NO_BEACONINFO_OBJ
//
// MessageText:
//
//  Missing beacon information object.
//
#define EMS_NO_BEACONINFO_OBJ            ((EMS_RESULT)0x80049901L)

//
// MessageId: EMS_BEACON_NOT_FOUND
//
// MessageText:
//
//  Beacon not found.
//
#define EMS_BEACON_NOT_FOUND             ((EMS_RESULT)0x80049902L)

//
// MessageId: EMS_BEACON_NO_DATA
//
// MessageText:
//
//  No beacon data.
//
#define EMS_BEACON_NO_DATA               ((EMS_RESULT)0x80049903L)


// *** EMSCAT_GPS = 0xB0 ***

//
// MessageId: EMSCAT_GPS_BASE_CODE
//
// MessageText:
//
//  GPS errors
//
#define EMSCAT_GPS_BASE_CODE             ((EMS_RESULT)0x8004B000L)

//
// MessageId: EMS_ERR_GPS_NOT_LOCKED
//
// MessageText:
//
//  GPS not locked.
//
#define EMS_ERR_GPS_NOT_LOCKED           ((EMS_RESULT)0x8004B001L)

//
// MessageId: EMS_ERR_GPS_ANTENNA
//
// MessageText:
//
//  GPS antenna error.
//
#define EMS_ERR_GPS_ANTENNA              ((EMS_RESULT)0x8004B002L)

//
// MessageId: EMS_ERR_GPS_SYSTEM
//
// MessageText:
//
//  GPS system error.
//
#define EMS_ERR_GPS_SYSTEM               ((EMS_RESULT)0x8004B003L)

//
// MessageId: EMS_ERR_GPS_INCORRECT_SAT
//
// MessageText:
//
//  GPS Satellite ID does not match.
//
#define EMS_ERR_GPS_INCORRECT_SAT        ((EMS_RESULT)0x8004B004L)

//
// MessageId: EMS_ERR_GPS_INVALID_EPHEMERIS
//
// MessageText:
//
//  GPS Satellite Ephemeris is invalid
//
#define EMS_ERR_GPS_INVALID_EPHEMERIS    ((EMS_RESULT)0x8004B005L)


// *** EMSCAT_ALTIT = 0xCO ***

//
// MessageId: EMSCAT_ALTIT_BASE_CODE
//
// MessageText:
//
//  Altitude errors
//
#define EMSCAT_ALTIT_BASE_CODE           ((EMS_RESULT)0x8004C000L)

//
// MessageId: EMS_NO_ALTIT_OBJ
//
// MessageText:
//
//  No altitude object.
//
#define EMS_NO_ALTIT_OBJ                 ((EMS_RESULT)0x8004C001L)

//
// MessageId: EMS_ALTIT_NO_DATA
//
// MessageText:
//
//  No altitude data.
//
#define EMS_ALTIT_NO_DATA                ((EMS_RESULT)0x8004C002L)


// *** EMSCAT_FRACT = 0xC1 ***

//
// MessageId: EMSCAT_FRACT_BASE_CODE
//
// MessageText:
//
//  Refraction Errors
//
#define EMSCAT_FRACT_BASE_CODE           ((EMS_RESULT)0x8004C100L)

//
// MessageId: EMS_NO_FRACT_OBJ
//
// MessageText:
//
//  No refraction object.
//
#define EMS_NO_FRACT_OBJ                 ((EMS_RESULT)0x8004C101L)

//
// MessageId: EMS_FRACT_NO_DATA
//
// MessageText:
//
//  No refraction data.
//
#define EMS_FRACT_NO_DATA                ((EMS_RESULT)0x8004C102L)


// *** EMSCAT_TLEServer = 0xC2 ***

//
// MessageId: EMSCAT_TLESERVER_BASE_CODE
//
// MessageText:
//
//  TLE Server Errors
//
#define EMSCAT_TLESERVER_BASE_CODE       ((EMS_RESULT)0x8004C200L)

//
// MessageId: EMS_NO_TLEServer_OBJ
//
// MessageText:
//
//  No TLE Server object.
//
#define EMS_NO_TLEServer_OBJ             ((EMS_RESULT)0x8004C201L)

//
// MessageId: EMS_TLEServer_NO_DATA1
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA1           ((EMS_RESULT)0x8004C202L)

//
// MessageId: EMS_TLEServer_NO_DATA2
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA2           ((EMS_RESULT)0x8004C203L)

//
// MessageId: EMS_TLEServer_NO_DATA3
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA3           ((EMS_RESULT)0x8004C204L)

//
// MessageId: EMS_TLEServer_NO_DATA4
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA4           ((EMS_RESULT)0x8004C205L)

//
// MessageId: EMS_TLEServer_NO_DATA5
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA5           ((EMS_RESULT)0x8004C206L)

//
// MessageId: EMS_TLEServer_NO_DATA6
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA6           ((EMS_RESULT)0x8004C207L)

//
// MessageId: EMS_TLEServer_NO_DATA7
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA7           ((EMS_RESULT)0x8004C208L)

//
// MessageId: EMS_TLEServer_NO_DATA8
//
// MessageText:
//
//  TLE Server: No data
//
#define EMS_TLEServer_NO_DATA8           ((EMS_RESULT)0x8004C209L)


// *** EMSCAT_SIT = 0xEE ***

//
// MessageId: EMSCAT_SIT_BASE_CODE
//
// MessageText:
//
//  SIT error messages.
//
#define EMSCAT_SIT_BASE_CODE             ((EMS_RESULT)0x8004EE00L)

//
// MessageId: EMS_SIT_UNKNOWN_CODE
//
// MessageText:
//
//  SIT error: unknown code.
//
#define EMS_SIT_UNKNOWN_CODE             ((EMS_RESULT)0x8004EE01L)


#define EMS_UNKNOWN_SIT_CODE EMS_SIT_UNKNOWN_CODE

//
// MessageId: EMS_SIT_SYNTAX_ERROR
//
// MessageText:
//
//  SIT error: syntax error.
//
#define EMS_SIT_SYNTAX_ERROR             ((EMS_RESULT)0x8004EE02L)

//
// MessageId: EMS_SIT_SYNTAX_EOL
//
// MessageText:
//
//  SIT error: unexpected end of line.
//
#define EMS_SIT_SYNTAX_EOL               ((EMS_RESULT)0x8004EE03L)

//
// MessageId: EMS_SIT_UNKNOWN_TYPE
//
// MessageText:
//
//  SIT error: unknown type.
//
#define EMS_SIT_UNKNOWN_TYPE             ((EMS_RESULT)0x8004EE04L)


#define EMS_UNKNOWN_SIT_TYPE EMS_SIT_UNKNOWN_TYPE

//
// MessageId: EMS_SIT_FIELD_COUNT_ERROR
//
// MessageText:
//
//  SIT error: field count error.
//
#define EMS_SIT_FIELD_COUNT_ERROR        ((EMS_RESULT)0x8004EE05L)

//
// MessageId: EMS_SIT_ALERT_LIMIT
//
// MessageText:
//
//  SIT error: alert limit reached.
//
#define EMS_SIT_ALERT_LIMIT              ((EMS_RESULT)0x8004EE06L)

//
// MessageId: EMS_SIT_MISSING_MSGHDR
//
// MessageText:
//
//  SIT error: missing message header.
//
#define EMS_SIT_MISSING_MSGHDR           ((EMS_RESULT)0x8004EE07L)

//
// MessageId: EMS_SIT_LINE_EXCEEDED
//
// MessageText:
//
//  SIT error: maximum line length exceeded.
//
#define EMS_SIT_LINE_EXCEEDED            ((EMS_RESULT)0x8004EE08L)

//
// MessageId: EMS_SIT_MSGSIZE_EXCEEDED
//
// MessageText:
//
//  SIT error: maximum message length exceeded.
//
#define EMS_SIT_MSGSIZE_EXCEEDED         ((EMS_RESULT)0x8004EE09L)


// *** EMSCAT_LOGGER = 0xFC ***

//
// MessageId: EMSCAT_LOGGER_BASE_CODE
//
// MessageText:
//
//  Logger Errors
//
#define EMSCAT_LOGGER_BASE_CODE          ((EMS_RESULT)0x8004FC00L)

//
// MessageId: EMS_NO_LOGGER_OBJ
//
// MessageText:
//
//  No logger object
//
#define EMS_NO_LOGGER_OBJ                ((EMS_RESULT)0x8004FC01L)


// *** EMSCAT_SITEINFO = 0xFD ***

//
// MessageId: EMSCAT_SITEINFO_BASE_CODE
//
// MessageText:
//
//  Site Info Errors
//
#define EMSCAT_SITEINFO_BASE_CODE        ((EMS_RESULT)0x8004FD00L)

//
// MessageId: EMS_NO_SITEINFO_OBJ
//
// MessageText:
//
//  No site information object
//
#define EMS_NO_SITEINFO_OBJ              ((EMS_RESULT)0x8004FD01L)

//
// MessageId: EMS_NO_SITEINFO_DATA
//
// MessageText:
//
//  No site information data
//
#define EMS_NO_SITEINFO_DATA             ((EMS_RESULT)0x8004FD02L)


// *** Standard Microsoft Errors (common identifier values) ***
//			EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
//			EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
//			EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111

//
// MessageId: EMS_NOINTERFACE
//
// MessageText:
//
//  No such interface supported.
//
#define EMS_NOINTERFACE                  ((EMS_RESULT)0x80004002L)

//
// MessageId: EMS_NOAGGREGATION
//
// MessageText:
//
//  Class does not support aggregation (or class object is remote).
//
#define EMS_NOAGGREGATION                ((EMS_RESULT)0x80040110L)

//
// MessageId: EMS_CLASSNOTAVAILABLE
//
// MessageText:
//
//  ClassFactory cannot supply requested class.
//
#define EMS_CLASSNOTAVAILABLE            ((EMS_RESULT)0x80040111L)


#endif
