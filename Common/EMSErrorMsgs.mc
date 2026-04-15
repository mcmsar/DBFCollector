;/********************************************************************
;*	Module:			EMSErrorMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Errors & Messages
;*
;*					Defined here so that the numbering remains unchanged
;*					Note that this file actually contains multiple "categories".
;*					Specifically:
;*						EMSCAT_GENERAL
;*						EMSCAT_MATH
;*						EMSCAT_COMM
;*						EMSCAT_IRDA
;*						EMSCAT_TFTP
;*						EMSCAT_COMP
;*						EMSCAT_RPC
;*
;*					The file also ensures that there are error codes and messages
;*					for the following standard Microsoft errors
;*						EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
;*						EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
;*						EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111
;*
;*					The following errors were also moved here ...
;*						Satellite errors ... EMSATFINFO.idl
;*						SIT errors ... emssit.h
;*						COMM errors ... AntError.h
;*						ALTIT errors ... emsaltit.idl
;*						BEACON errors ... emsbeacn.idl
;*						REFRACTION errors ... emsfract.idl
;*						SITEINFO errors ... emssiteif.idl
;*						LUT errors ... emslinfo.idl
;*						ORBIT errors ... emsorbit.idl
;*						PASS errors ... emspass.idl
;*						STATUS errors ... emsstatus.idl
;*						TLE Server errors ... emsTLEServer.idl
;*						Logger errors ... emsloggr.idl
;*						GPS errors ... gpsclock.h
;*						LOCATE errors ... LocateError.h
;*
;*					Note that these have been defined here (rather than in
;*					a set of new mc files to minimize the number of files
;*					that need to be changed.
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;* Copyright (c) 2005 by EMS Technologies, Inc.,
;* All rights reserved
;* This program is unpublished software and contains the trade secrets
;* and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;
;
;
;#ifndef INC_EMSERRORMSG
;#define INC_EMSERRORMSG
;
;#ifndef INC_EMSERROR
;#include "emserror.h"
;#endif
;


MessageIdTypedef=EMS_RESULT

SeverityNames=
(
	Success=0x0
	ErrWarn=0x2
	Info=0x1
	Warn=0x2
	Alarm=0x3
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

;// *** EMSCAT_GENERAL = 0x80 ***
;
MessageId=0x8000 SymbolicName=EMSCAT_GENERAL_BASE_CODE Facility=ITF
Language=English
General messages.
.
MessageID=+1 SymbolicName=EMS_NO_MEMORY Severity=ErrWarn Facility=ITF
Language=English
An out of memory error has been detected.
.
MessageID=+1 SymbolicName=EMS_FILE_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
The specified file cannot be found.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
An unexpected error has been detected.
.
MessageID=+1 SymbolicName=EMS_INVALID_HANDLE Severity=ErrWarn Facility=ITF
Language=English
An invalid handle has been detected.
.
MessageID=+1 SymbolicName=EMS_HANDLE_EOF Severity=ErrWarn Facility=ITF
Language=English
Unexpectedly reached end of file.
.
MessageID=+1 SymbolicName=EMS_FILE_EXISTS Severity=ErrWarn Facility=ITF
Language=English
Specified file already exists.
.
MessageID=+1 SymbolicName=EMS_EOF Severity=ErrWarn Facility=ITF
Language=English
Unexpectedly reached end of file.
.
MessageID=+1 SymbolicName=EMS_NO_FILE Severity=ErrWarn Facility=ITF
Language=English
File could not be opened.
.
MessageID=+1 SymbolicName=EMS_UNSUPPORTED Severity=ErrWarn Facility=ITF
Language=English
Unsupported request has been made.
.
MessageID=+1 SymbolicName=EMS_IO_ERROR  Severity=ErrWarn Facility=ITF
Language=English
I/O error detected.
.
MessageID=+1 SymbolicName=EMS_NOT_IMPLEMENTED Severity=ErrWarn Facility=ITF
Language=English
Requested functionality has not been implemented.
.
MessageID=+1 SymbolicName=EMS_ALREADY_INSTALLED Severity=ErrWarn Facility=ITF
Language=English
Requested functionality has already been installed.
.
MessageID=+1 SymbolicName=EMS_CANNOT_UNINSTALL Severity=ErrWarn Facility=ITF
Language=English
Cannot uninstall.
.
MessageID=+1 SymbolicName=EMS_PATH_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
Specified path not found.
.
MessageID=+1 SymbolicName=EMS_ACCESS_DENIED Severity=ErrWarn Facility=ITF
Language=English
Access denied.
.
MessageID=+1 SymbolicName=EMS_BAD_PARAM Severity=ErrWarn Facility=ITF
Language=English
Invalid parameter received.
.
MessageID=+1 SymbolicName=EMS_DISK_FULL Severity=ErrWarn Facility=ITF
Language=English
Disk is full.
.
MessageID=+1 SymbolicName=EMS_NO_DEVICE Severity=ErrWarn Facility=ITF
Language=English
No device.
.
MessageID=+1 SymbolicName=EMS_ALREADY_OPEN Severity=ErrWarn Facility=ITF
Language=English
Specified resource is already open.
.
MessageID=+1 SymbolicName=EMS_INVALID_CMD Severity=ErrWarn Facility=ITF
Language=English
Invalid command received.
.
MessageID=+1 SymbolicName=EMS_UNAVAIL Severity=ErrWarn Facility=ITF
Language=English
Specified resource is unavailable.
.
MessageID=+1 SymbolicName=EMS_INVALID_TIME Severity=ErrWarn Facility=ITF
Language=English
Invalid time specified.
.
MessageID=+1 SymbolicName=EMS_ALREADY_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
Request to initialize device or service that has already been initialized.
.
MessageID=+1 SymbolicName=EMS_NOT_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
Request to access device or service that has not been initialized.
.
MessageID=+1 SymbolicName=EMS_NOT_DESIRED_LANGUAGE Severity=ErrWarn Facility=ITF
Language=English
Failed to load specified language.
.
MessageID=+1 SymbolicName=EMS_INVALID_FILESPEC Severity=ErrWarn Facility=ITF
Language=English
Invalid file specification.
.
MessageID=+1 SymbolicName=EMS_OVERFLOW Severity=ErrWarn Facility=ITF
Language=English
Overflow detected.
.
MessageID=+1 SymbolicName=EMS_EMPTY Severity=ErrWarn Facility=ITF
Language=English
Empty dataset.
.
MessageID=+1 SymbolicName=EMS_INVALID_PTR Severity=ErrWarn Facility=ITF
Language=English
Invalid pointer detected.
.
MessageID=+1 SymbolicName=EMS_GPS_NOT_TRACK Severity=ErrWarn Facility=ITF
Language=English
GPS is not tracking.
.
MessageID=+1 SymbolicName=EMS_TRUNCATED Severity=ErrWarn Facility=ITF
Language=English
Truncated data detected.
.
MessageID=+1 SymbolicName=EMS_INVALID_STREAM Severity=ErrWarn Facility=ITF
Language=English
Invalid stream detected.
.
MessageID=+1 SymbolicName=EMS_LINE_LIMIT_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
Line limit exceeded.
.
MessageID=+1 SymbolicName=EMS_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
Unhandled exception detected.
.
MessageID=+1 SymbolicName=EMS_EXCEPTION_CONTEXT Severity=ErrWarn Facility=ITF
Language=English
Unhandled exception detected (%1 : %2).
.
MessageID=+1 SymbolicName=EMS_MISSING_B_SIDE Severity=ErrWarn Facility=ITF
Language=English
Missing B side.
.
MessageID=+1 SymbolicName=EMS_EOL Severity=ErrWarn Facility=ITF
Language=English
End of line reached.
.
MessageID=+1 SymbolicName=EMS_SYNTAX_ERROR Severity=ErrWarn Facility=ITF
Language=English
Syntax error detected.
.
MessageID=+1 SymbolicName=EMS_ERROR_ORBIT_NUMBER_NOT_MATCH Severity=ErrWarn Facility=ITF
Language=English
One or more passes have different orbit numbers.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_SERVER_TYPE Severity=ErrWarn Facility=ITF
Language=English
Unknown server type specified.
.
MessageID=+1 SymbolicName=EMS_INVALID_URL Severity=ErrWarn Facility=ITF
Language=English
Invalid URL specified.
.
MessageID=+1 SymbolicName=EMS_INVALID_STREAM_POS Severity=ErrWarn Facility=ITF
Language=English
Invalid stream position specified.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_PARAM_TYPE Severity=ErrWarn Facility=ITF
Language=English
Unknown parameter type specified.
.
MessageID=+1 SymbolicName=EMS_DATA_INVALID Severity=ErrWarn Facility=ITF
Language=English
Invalid data detected.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_URL_TYPE Severity=ErrWarn Facility=ITF
Language=English
Unknown URL type specified.
.
MessageID=+1 SymbolicName=EMS_UNSUPPORTED_URL_TYPE Severity=ErrWarn Facility=ITF
Language=English
Unsupported URL type specified.
.
MessageID=+1 SymbolicName=EMS_WAIT_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
A system wait has timed out.
.
MessageID=+1 SymbolicName=EMS_WAIT_ABANDONDED Severity=ErrWarn Facility=ITF
Language=English
A system wait has been abandoned.
.
MessageID=+1 SymbolicName=EMS_ARRAY_OUT_OF_BOUNDS Severity=ErrWarn Facility=ITF
Language=English
Array out of bounds.
.
MessageID=+1 SymbolicName=EMS_OBJECT_CREATE_FAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to create object %1 with error %2.
.
MessageID=+1 SymbolicName=EMS_QUERY_INTERFACE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to retrieve interface %1 with error %2.
.
MessageID=+1 SymbolicName=EMS_NO_MATCHING_RECORD Severity=ErrWarn Facility=ITF
Language=English
No matching record found.
.
MessageID=+1 SymbolicName=EMS_DIRECTORY_NOT_EMPTY Severity=ErrWarn Facility=ITF
Language=English
Failed to delete a directory because it is not empty.
.
MessageId=+1 SymbolicName=EMS_BAD_REGISTRY_ENTRY Severity=ErrWarn Facility=ITF
Language=English
Failed to find an expected entry in the registry %1
.
;
;// *** EMSCAT_MATH = 0x81 ***
;
MessageId=0x8100 SymbolicName=EMSCAT_MATH_BASE_CODE Facility=ITF
Language=English
Math error messages.
.
MessageID=+1 SymbolicName=EMS_CBCOPY_ZERO_LENGTH Severity=ErrWarn Facility=ITF
Language=English
Zero length cbcopy requested.
.
MessageID=+1 SymbolicName=EMS_SBCOPY_ZERO_LENGTH Severity=ErrWarn Facility=ITF
Language=English
Zero length sbcopy requested.
.
MessageID=+1 SymbolicName=EMS_WBCOPY_ZERO_LENGTH Severity=ErrWarn Facility=ITF
Language=English
Zero length wbcopy requested.
.
;
;// *** EMSCAT_COMM = 0x82 ***
;
MessageId=0x8200 SymbolicName=EMSCAT_COMM_BASE_CODE Facility=ITF
Language=English
Communication error messages.
.
MessageID=+1 SymbolicName=EMS_TIMEOUT Severity=ErrWarn Facility=ITF
Language=English
A timeout was detected.
.
MessageID=+1 SymbolicName=EMS_NOT_OPEN Severity=ErrWarn Facility=ITF
Language=English
Could not open specified device or link.
.
MessageID=+1 SymbolicName=EMS_TRANSMIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Transmit error detected.
.
MessageID=+1 SymbolicName=EMS_CHECKSUM_ERR Severity=ErrWarn Facility=ITF
Language=English
Checksum error detected.
.
MessageID=+1 SymbolicName=EMS_SEQNUMBER_ERR Severity=ErrWarn Facility=ITF
Language=English
Sequence number error detected.
.
MessageID=+1 SymbolicName=EMS_OP_CANCELLED Severity=ErrWarn Facility=ITF
Language=English
Operation cancelled.
.
MessageID=+1 SymbolicName=EMS_ERROR_LIMIT Severity=ErrWarn Facility=ITF
Language=English
Error limit reached.
.
MessageID=+1 SymbolicName=EMS_DUPLICATE_SEQ Severity=ErrWarn Facility=ITF
Language=English
Communications duplicate sequence number detected.
.
MessageID=+1 SymbolicName=EMS_PACKET_ERR Severity=ErrWarn Facility=ITF
Language=English
Packet error detected.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_DATA Severity=ErrWarn Facility=ITF
Language=English
Request to process unknown data.
.
MessageID=+1 SymbolicName=EMS_RECV_ERR Severity=ErrWarn Facility=ITF
Language=English
Data receive error.
.
MessageID=+1 SymbolicName=EMS_OVERRUN_ERR Severity=ErrWarn Facility=ITF
Language=English
Overrun error detected.
.
MessageID=+1 SymbolicName=EMS_PARITY_ERR Severity=ErrWarn Facility=ITF
Language=English
Parity error detected.
.
MessageID=+1 SymbolicName=EMS_FRAMING_ERR Severity=ErrWarn Facility=ITF
Language=English
Framing error detected.
.
MessageID=+1 SymbolicName=EMS_BREAKDETECT_ERR Severity=ErrWarn Facility=ITF
Language=English
Break detected.
.
MessageID=+1 SymbolicName=EMS_NO_PACKET_SERVICE Severity=ErrWarn Facility=ITF
Language=English
No packet service available.
.
MessageID=+1 SymbolicName=EMS_OP_ABORTED Severity=ErrWarn Facility=ITF
Language=English
Operation aborted.
.
MessageID=+1 SymbolicName=EMS_NO_COM_PORT Severity=ErrWarn Facility=ITF
Language=English
No COM port available.
.
MessageID=+1 SymbolicName=EMS_AZ_RX_FLUSH_ERROR Severity=ErrWarn Facility=ITF
Language=English
AZ/RX flush error.
.
MessageID=+1 SymbolicName=EMS_AZ_TX_FLUSH_ERROR Severity=ErrWarn Facility=ITF
Language=English
AZ/TX flush error.
.
MessageID=+1 SymbolicName=EMS_EL_RX_FLUSH_ERROR Severity=ErrWarn Facility=ITF
Language=English
EL/RX flush error.
.
MessageID=+1 SymbolicName=EMS_EL_TX_FLUSH_ERROR Severity=ErrWarn Facility=ITF
Language=English
EL/TX flush error.
.
MessageID=+1 SymbolicName=EMS_CANT_OPEN_AZELFILE Severity=ErrWarn Facility=ITF
Language=English
Cannot open AZ/EL file.
.
MessageID=+1 SymbolicName=EMS_SOCKET_CREATE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to create a socket.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_STARTUP_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to start sockets subsystem.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_ACCEPT_DEBUG Severity=Info Facility=ITF
Language=English
Socket connection accepted.
.
MessageID=+1 SymbolicName=EMS_SOCKET_ACCEPT_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to accept a socket connection.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_BIND_DEBUG Severity=Info Facility=ITF
Language=English
Bound socket to IP=%1, port=%2.
.
MessageID=+1 SymbolicName=EMS_SOCKET_BIND_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to bind socket to IP=%1, port=%2.  Winsock error is %3.
.
MessageID=+1 SymbolicName=EMS_SOCKET_CLOSE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error closing socket.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_CONNECT_DEBUG Severity=Info Facility=ITF
Language=English
Connected to socket at IP=%1, port=%2.
.
MessageID=+1 SymbolicName=EMS_SOCKET_CONNECT_ERROR Severity=ErrWarn Facility=ITF
Language=English
Failed to connect socket to IP=%1, port=%2.  Winsock error is %3.
.
MessageID=+1 SymbolicName=EMS_SOCKET_LISTEN_DEBUG Severity=Info Facility=ITF
Language=English
Listening for connections on socket.
.
MessageID=+1 SymbolicName=EMS_SOCKET_LISTEN_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error listening for socket connection.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_RECV_DEBUG Severity=Info Facility=ITF
Language=English
Received %1 bytes on socket.
.
MessageID=+1 SymbolicName=EMS_SOCKET_RECV_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error receiving on socket.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SENDREQ_DEBUG Severity=Info Facility=ITF
Language=English
Requesting send of %1 bytes with WS2 flags = %2.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SEND_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error sending on socket.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SEND_DEBUG Severity=Info Facility=ITF
Language=English
Sent %1 bytes on socket.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SHUTDOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error shutting down socket.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SHUTDOWN_DEBUG Severity=Info Facility=ITF
Language=English
Socket was shutdown.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SELECT_ERROR Severity=ErrWarn Facility=ITF
Language=English
Error selecting socket status.  Winsock error is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SELECT_READ_DEBUG Severity=Info Facility=ITF
Language=English
Socket read status is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_SELECT_WRITE_DEBUG Severity=Info Facility=ITF
Language=English
Socket write status is %1.
.
MessageID=+1 SymbolicName=EMS_SOCKET_FAMILY_ERROR Severity=ErrWarn Facility=ITF
Language=English
Unrecognized socket address family encountered.
.
MessageId=+1 SymbolicName=EMS_SNMP_CREATEFAILED Severity=ErrWarn Facility=ITF
Language=English
Failed to initialize SNMP communications.
.
;
;// *** EMSCAT_IRDA = 0x83 ***
;
MessageId=0x8300 SymbolicName=EMSCAT_IRDA_BASE_CODE Facility=ITF
Language=English
IrDA error messages.
.
MessageID=+1 SymbolicName=EMS_IRDA_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
IrDA: not found.
.
MessageID=+1 SymbolicName=EMS_IRDA_NOT_ACTIVE Severity=ErrWarn Facility=ITF
Language=English
IrDA: not active.
.
MessageID=+1 SymbolicName=EMS_IRDA_NO_CONNECTION Severity=ErrWarn Facility=ITF
Language=English
IrDA: no connection.
.
MessageID=+1 SymbolicName=EMS_IRDA_IN_USE Severity=ErrWarn Facility=ITF
Language=English
IrDA: in use.
.
;
;// *** EMSCAT_TFTP = 0x84 ***
;
MessageId=0x8400 SymbolicName=EMSCAT_TFTP_BASE_CODE Facility=ITF
Language=English
TFTP error messages.
.
MessageID=+1 SymbolicName=EMS_TFTP_ERROR Severity=ErrWarn Facility=ITF
Language=English
TFTP error.
.
MessageID=+1 SymbolicName=EMS_TFTP_INVALID_OP Severity=ErrWarn Facility=ITF	            
Language=English
TFTP error: invalid operation.
.
MessageID=+1 SymbolicName=EMS_TFTP_UNKNOWN_ID Severity=ErrWarn Facility=ITF	            
Language=English
TFTP error: unknown id.
.
;
;// *** EMSCAT_COMP = 0x85 ***
;
MessageId=0x8500 SymbolicName=EMSCAT_COMP_BASE_CODE Facility=ITF
Language=English
Computer error messages.
.
MessageID=+1 SymbolicName=EMS_NO_COMPUTERS Severity=ErrWarn Facility=ITF		            
Language=English
No computers can be detected.
.
;#define EMS_NO_TERMINALS		EMS_NO_COMPUTERS
;
MessageID=+1 SymbolicName=EMS_GUID_NOT_FOUND Severity=ErrWarn Facility=ITF	 	            
Language=English
Specified GUID not found.
.
MessageID=+1 SymbolicName=EMS_INVALID_DRIVE Severity=ErrWarn Facility=ITF		            
Language=English
Invalid drive specified.
.
MessageID=+1 SymbolicName=EMS_MULTIPLEX_ERR Severity=ErrWarn Facility=ITF		            
Language=English
Multiplex error detected.
.
MessageID=+1 SymbolicName=EMS_SERVICE_BUSY_ERR Severity=ErrWarn Facility=ITF	            
Language=English
Requested service is busy.
.
MessageID=+1 SymbolicName=EMS_UNKNOWN_COMPUTER_TYPE Severity=ErrWarn Facility=ITF 	      
Language=English
Unknown computer type specified.
.
;#define EMS_UNKNOWN_TERMTYPE	EMS_UNKNOWN_COMPUTER_TYPE
;
;
;// *** EMSCAT_RPC = 0x86 ***
;
MessageId=0x8600 SymbolicName=EMSCAT_RPC_BASE_CODE Facility=ITF
Language=English
RPC error messages.
.
MessageID=+1 SymbolicName=EMS_RPC_UNKNOWN_PROTOCOL Severity=ErrWarn Facility=ITF          
Language=English
RPC error: Unknown protocol specified.
.
MessageID=+1 SymbolicName=EMS_RPC_LIMIT_EXCEEDED Severity=ErrWarn Facility=ITF	         
Language=English
RPC error: Limit exceeded.
.
MessageID=+1 SymbolicName=EMS_RPC_NO_CLIENT Severity=ErrWarn Facility=ITF			         
Language=English
RPC error: No client.
.
MessageID=+1 SymbolicName=EMS_RPC_ERROR	Severity=ErrWarn Facility=ITF			         
Language=English
RPC error detected.
.
MessageID=+1 SymbolicName=EMS_RPC_NOT_CONNECTED Severity=ErrWarn Facility=ITF	            
Language=English
RPC error: Not connected.
.
MessageID=+1 SymbolicName=EMS_RPC_UNKNOWN_HANDLER Severity=ErrWarn Facility=ITF	         
Language=English
RPC error: Unknown handler.
.
MessageID=+1 SymbolicName=EMS_RPC_UNKNOWN_METHOD Severity=ErrWarn Facility=ITF	         
Language=English
RPC error: Unknown method.
.
;
;// *** EMSCAT_ORBIT = 0x89 ***
;
MessageId=0x8900 SymbolicName=EMSCAT_ORBIT_BASE_CODE Facility=ITF
Language=English
Orbit errors.
.
MessageID=+1 SymbolicName=EMS_NO_ORBIT_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No orbit object.
.
MessageID=+1 SymbolicName=EMS_ORBIT_NO_SATELLITE Severity=ErrWarn Facility=ITF	         
Language=English
Specified satellite not found
.
MessageID=+1 SymbolicName=EMS_ORBIT_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No orbit data information has been initialized
.
MessageID=+1 SymbolicName=EMS_ORBIT_BAD_DATA Severity=ErrWarn Facility=ITF	         
Language=English
Orbital elements have been corrupted
.
MessageID=+1 SymbolicName=EMS_ORBIT_BAD_TLEXNO Severity=ErrWarn Facility=ITF	         
Language=English
Orbit Constructor - Bad TLE.xno value: Must be > 0
.
MessageID=+1 SymbolicName=EMS_ORBIT_UNEXPECTEDDEEPERR1 Severity=ErrWarn Facility=ITF	         
Language=English
Unexpected error at location 1 in Deep.cpp
.
MessageID=+1 SymbolicName=EMS_ORBIT_UNEXPECTEDDEEPERR2 Severity=ErrWarn Facility=ITF	         
Language=English
Unexpected error at location 2 in Deep.cpp
.
MessageID=+1 SymbolicName=EMS_ORBIT_UNEXPECTEDDEEPERR3 Severity=ErrWarn Facility=ITF	         
Language=English
Unexpected error at location 3 in Deep.cpp
.
MessageID=+1 SymbolicName=EMS_ORBIT_USEDEEPSPACE Severity=ErrWarn Facility=ITF	         
Language=English
Orbit Constructor determined - SHOULD USE DEEP SPACE EPHEMERIS
.
MessageID=+1 SymbolicName=EMS_ORBIT_USENEAREARTH Severity=ErrWarn Facility=ITF	         
Language=English
Orbit Constructor determined - SHOULD USE NEAR EARTH EPHEMERIS
.
MessageID=+1 SymbolicName=EMS_ORBIT_INVALID_FILESPEC Severity=ErrWarn Facility=ITF	         
Language=English
EMS Orbit: Could not locate the file SARSAT.TXT
.
MessageID=+1 SymbolicName=EMS_ORBIT_NO_MEMORY Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit:  Out of memory error has been detected
.
;
;// *** EMSCAT_PASS = 0x8A ***
;
MessageId=0x8A00 SymbolicName=EMSCAT_PASS_BASE_CODE Facility=ITF
Language=English
Pass Schedule Errors
.
MessageID=+1 SymbolicName=EMS_PASS_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
Pass scheduler: no data.
.
MessageID=+1 SymbolicName=EMS_PASS_DATA_OVERFLOW Severity=ErrWarn Facility=ITF	         
Language=English
Pass scheduler: data overflow.
.
;
;// *** EMSCAT_SAT = 0x8B ***
;
MessageId=0x8B00 SymbolicName=EMSCAT_SAT_BASE_CODE Facility=ITF
Language=English
Satellite error messages.
.
MessageID=+1 SymbolicName=EMS_NO_SATINFO_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
Satellite error: no information object available.
.
MessageID=+1 SymbolicName=EMS_SAT_NOT_FOUND Severity=ErrWarn Facility=ITF	         
Language=English
Satellite error: satellite not found.
.
MessageID=+1 SymbolicName=EMS_SAT_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
Satellite error: no data.
.
MessageID=+1 SymbolicName=EMS_SAT_INVALID Severity=ErrWarn Facility=ITF	         
Language=English
Satellite error: invalid satellite.
.
;
;// *** EMSCAT_LUT = 0x8D ***
;
MessageId=0x8D00 SymbolicName=EMSCAT_LUT_BASE_CODE Facility=ITF
Language=English
LUT Info Errors
.
MessageID=+1 SymbolicName=EMS_NO_LUTINFO_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No LUT information object.
.
MessageID=+1 SymbolicName=EMS_LUT_NOT_FOUND Severity=ErrWarn Facility=ITF	         
Language=English
LUT not found.
.
MessageID=+1 SymbolicName=EMS_LUT_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
LUT no data.
.
;
;// *** EMSCAT_STATUS = 0x8F ***
;
MessageId=0x8F00 SymbolicName=EMSCAT_STATUS_BASE_CODE Facility=ITF
Language=English
Status Errors
.
MessageID=+1 SymbolicName=EMS_NO_STATUS_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No status object.
.
MessageID=+1 SymbolicName=EMS_STATUS_NOT_INIT Severity=ErrWarn Facility=ITF	         
Language=English
Status not initialized.
.
;
;// *** EMSCAT_LOCATE = 0x90 ***
;
MessageId=0x9000 SymbolicName=EMSCAT_LOCATE_BASE_CODE Facility=ITF
Language=English
Locate Errors
.
MessageID=+1 SymbolicName=EMS_LOCATE_MEMORYALLOC_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
Memory allocation error
.
MessageID=+1 SymbolicName=EMS_LOCATE_FILE_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
Problem opening file
.
MessageID=+1 SymbolicName=EMS_LOCATE_READ_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
Problem reading file
.
MessageID=+1 SymbolicName=EMS_LOCATE_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No locate data information has been initialized
.
MessageID=+1 SymbolicName=EMS_LOCATE_IE_NON_CONVERGE Severity=ErrWarn Facility=ITF	         
Language=English
IE fails to converge
.
MessageID=+1 SymbolicName=EMS_LOCATE_CN_NON_CONVERGE Severity=ErrWarn Facility=ITF	         
Language=English
Converge fails to converge
.
MessageID=+1 SymbolicName=EMS_LOCATE_TCA_OUTOFBOUNDS Severity=ErrWarn Facility=ITF	         
Language=English
TCA out of bounds
.
MessageID=+1 SymbolicName=EMS_LOCATE_SOLVE_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
Solve error
.
MessageID=+1 SymbolicName=EMS_LOCATE_NO_POINTS Severity=ErrWarn Facility=ITF	         
Language=English
No points
.
MessageID=+1 SymbolicName=EMS_LOCATE_WLS_NON_CONVERGE Severity=ErrWarn Facility=ITF	         
Language=English
WLS fails to converge
.
MessageID=+1 SymbolicName=EMS_LOCATE_WRITING_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
Problem writing file
.
;
;// *** EMSCAT_ADBOARD = 0x98 ***
;
MessageId=0x9800 SymbolicName=EMSCAT_ADBOARD_BASE_CODE Facility=ITF
Language=English
A/D error messages.
.
MessageID=+1 SymbolicName=EMS_ADERR_IRQ_INUSE Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: IRQ in use.
.
MessageID=+1 SymbolicName=EMS_ADERR_FN_POINTER Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: invalid function pointer.
.
MessageID=+1 SymbolicName=EMS_ADERR_NO_INIT Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: not intialized.
.
MessageID=+1 SymbolicName=EMS_ADERR_NO_DLL Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: missing DLL.
.
MessageID=+1 SymbolicName=EMS_ADERR_ALREADY_INIT Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: already intialized.
.
MessageID=+1 SymbolicName=EMS_ADERR_NO_BOARD Severity=ErrWarn Facility=ITF	         
Language=English
A/D error: no board.
.
MessageID=+1 SymbolicName=EMS_USBDT_ECODE_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
A/D board error (%1)
.
;
;// *** EMSCAT_BEACON = 0x99 ***
;
MessageId=0x9900 SymbolicName=EMSCAT_BEACON_BASE_CODE Facility=ITF
Language=English
Ref. Beacon Info Errors
.
MessageID=+1 SymbolicName=EMS_NO_BEACONINFO_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
Missing beacon information object.
.
MessageID=+1 SymbolicName=EMS_BEACON_NOT_FOUND Severity=ErrWarn Facility=ITF	         
Language=English
Beacon not found.
.
MessageID=+1 SymbolicName=EMS_BEACON_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No beacon data.
.
;
;// *** EMSCAT_GPS = 0xB0 ***
;
MessageId=0xB000 SymbolicName=EMSCAT_GPS_BASE_CODE Facility=ITF
Language=English
GPS errors
.
MessageID=+1 SymbolicName=EMS_ERR_GPS_NOT_LOCKED Severity=ErrWarn Facility=ITF	         
Language=English
GPS not locked.
.
MessageID=+1 SymbolicName=EMS_ERR_GPS_ANTENNA Severity=ErrWarn Facility=ITF	         
Language=English
GPS antenna error.
.
MessageID=+1 SymbolicName=EMS_ERR_GPS_SYSTEM Severity=ErrWarn Facility=ITF	         
Language=English
GPS system error.
.
MessageID=+1 SymbolicName=EMS_ERR_GPS_INCORRECT_SAT Severity=ErrWarn Facility=ITF	         
Language=English
GPS Satellite ID does not match.
.
MessageID=+1 SymbolicName=EMS_ERR_GPS_INVALID_EPHEMERIS Severity=ErrWarn Facility=ITF	         
Language=English
GPS Satellite Ephemeris is invalid
.
;
;// *** EMSCAT_ALTIT = 0xCO ***
;
MessageId=0xC000 SymbolicName=EMSCAT_ALTIT_BASE_CODE Facility=ITF
Language=English
Altitude errors
.
MessageID=+1 SymbolicName=EMS_NO_ALTIT_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No altitude object.
.
MessageID=+1 SymbolicName=EMS_ALTIT_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No altitude data.
.
;
;// *** EMSCAT_FRACT = 0xC1 ***
;
MessageId=0xC100 SymbolicName=EMSCAT_FRACT_BASE_CODE Facility=ITF
Language=English
Refraction Errors
.
MessageID=+1 SymbolicName=EMS_NO_FRACT_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No refraction object.
.
MessageID=+1 SymbolicName=EMS_FRACT_NO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No refraction data.
.
;
;// *** EMSCAT_TLEServer = 0xC2 ***
;
MessageId=0xC200 SymbolicName=EMSCAT_TLESERVER_BASE_CODE Facility=ITF
Language=English
TLE Server Errors
.
MessageID=+1 SymbolicName=EMS_NO_TLEServer_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No TLE Server object.
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA1 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA2 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA3 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA4 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA5 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA6 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA7 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
MessageID=+1 SymbolicName=EMS_TLEServer_NO_DATA8 Severity=ErrWarn Facility=ITF	         
Language=English
TLE Server: No data
.
;
;// *** EMSCAT_SIT = 0xEE ***
;
MessageId=0xEE00 SymbolicName=EMSCAT_SIT_BASE_CODE Facility=ITF
Language=English
SIT error messages.
.
MessageID=+1 SymbolicName=EMS_SIT_UNKNOWN_CODE Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: unknown code.
.
;
;#define EMS_UNKNOWN_SIT_CODE EMS_SIT_UNKNOWN_CODE
;
MessageID=+1 SymbolicName=EMS_SIT_SYNTAX_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: syntax error.
.
MessageID=+1 SymbolicName=EMS_SIT_SYNTAX_EOL Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: unexpected end of line.
.
MessageID=+1 SymbolicName=EMS_SIT_UNKNOWN_TYPE Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: unknown type.
.
;
;#define EMS_UNKNOWN_SIT_TYPE EMS_SIT_UNKNOWN_TYPE
;
MessageID=+1 SymbolicName=EMS_SIT_FIELD_COUNT_ERROR Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: field count error.
.
MessageID=+1 SymbolicName=EMS_SIT_ALERT_LIMIT Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: alert limit reached.
.
MessageID=+1 SymbolicName=EMS_SIT_MISSING_MSGHDR Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: missing message header.
.
MessageID=+1 SymbolicName=EMS_SIT_LINE_EXCEEDED Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: maximum line length exceeded.
.
MessageID=+1 SymbolicName=EMS_SIT_MSGSIZE_EXCEEDED Severity=ErrWarn Facility=ITF	         
Language=English
SIT error: maximum message length exceeded.
.
;
;// *** EMSCAT_LOGGER = 0xFC ***
;
MessageId=0xFC00 SymbolicName=EMSCAT_LOGGER_BASE_CODE Facility=ITF
Language=English
Logger Errors
.
MessageID=+1 SymbolicName=EMS_NO_LOGGER_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No logger object
.
;
;// *** EMSCAT_SITEINFO = 0xFD ***
;
MessageId=0xFD00 SymbolicName=EMSCAT_SITEINFO_BASE_CODE Facility=ITF
Language=English
Site Info Errors
.
MessageID=+1 SymbolicName=EMS_NO_SITEINFO_OBJ Severity=ErrWarn Facility=ITF	         
Language=English
No site information object
.
MessageID=+1 SymbolicName=EMS_NO_SITEINFO_DATA Severity=ErrWarn Facility=ITF	         
Language=English
No site information data
.
;
;// *** Standard Microsoft Errors (common identifier values) ***
;//			EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
;//			EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
;//			EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111
;
MessageId=0x4002 SymbolicName=EMS_NOINTERFACE Facility=System
Language=English
No such interface supported.
.
MessageId=0x0110 SymbolicName=EMS_NOAGGREGATION Facility=ITF
Language=English
Class does not support aggregation (or class object is remote).
.
MessageId=0x0111 SymbolicName=EMS_CLASSNOTAVAILABLE Facility=ITF
Language=English
ClassFactory cannot supply requested class.
.
;
;#endif
