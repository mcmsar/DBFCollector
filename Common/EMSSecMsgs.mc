;/********************************************************************
;*	Module:			EMSSecMsgs.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Security Messages
;*
;*	Usage: 
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
;*										All rights reserved
;* This program is unpublished software and contains the trade secrets
;* and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;
;/*******************************************************************
;
;  Revision Record
;
;	Rev	Date			Auth	Changes
;	===	====			====	=======
;
;	0.0	2003Dec01		RI		start 
;		2005Jan05		CH		Ticket 6652: significant changes to 
;								support use of actual error code as
;								the message identifier for logging
;********************************************************************/
;#ifndef INC_EMSSECMSGS
;#define INC_EMSSECMSGS
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
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xBC00 SymbolicName=EMS_SECURITY_BASE_CODE Facility=ITF
Language=English
EMS SECURITY Error
.
MessageId=+1 SymbolicName=EMS_SECURITY_ACCESS_DENIED Severity=ErrWarn Facility=ITF
Language=English
EMS Security Access Denied
.
MessageId=+1 SymbolicName=EMS_SEC_RESOURCE_UNDEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS Security Resource undefined
.
MessageId=+1 SymbolicName=EMS_SEC_KEY_CLOSE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Cryptography Key closing error
.
MessageId=+1 SymbolicName=EMS_SEC_KEY_FWRITE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Writing Cryptography Key to file error
.
MessageId=+1 SymbolicName=EMS_SEC_KEY_FREAD_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Reading Cryptography Key file error
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLICKEY_LOAD_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Loading Public Key error
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLICKEY_GEN_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Generating Public Key error
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_DECRYPT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Decrypting token error
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_ENCRYPT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Encrypting token error
.
MessageId=+1 SymbolicName=EMS_SEC_WRITE_KEYID_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Writing Key ID error
.
MessageId=+1 SymbolicName=EMS_SEC_READ_KEYID_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Reading Key ID error
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_CREATETXT_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Creating text token error
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_PARSE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Parsing text token error
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_ENCODEDTOBIN_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error Creating binary token from encoded one
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_EXPIRED Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error Security token expired
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATEKEY_LOAD_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Loading Private Key error
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATEKEY_GEN_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Generating Private Key error
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATEKEY_FWRITE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Writing Private Key to file error
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATEKEY_FREAD_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Reading Private Key file error
.
MessageId=+1 SymbolicName=EMS_SEC_IDENTIFY_USER_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error identifying user
.
MessageId=+1 SymbolicName=EMS_SEC_EXTRACTING_USERNAME_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error extracting user name
.
MessageId=+1 SymbolicName=EMS_SEC_EXTRACTING_USERGROUPS_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error extracting user groups
.
MessageId=+1 SymbolicName=EMS_SEC_NOROLEID_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error cannot find the role id
.
MessageId=+1 SymbolicName=EMS_SEC_GETTING_KEYINFO_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Security Error cannot find the security key information
.
MessageId=+1 SymbolicName=EMS_SEC_AUTHORIZATION_DISABLED Severity=Success Facility=ITF
Language=English
EMS Security, Authorization is disabled, the call succeeded
.
MessageId=+1 SymbolicName=EMS_SEC_CANNOT_INITIALIZE_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Security initialization failed with an unhandled exception
.
MessageId=+1 SymbolicName=EMS_SEC_CANNOT_AUTHENTICATE_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Security authentication failed with an unhandled exception
.
MessageId=+1 SymbolicName=EMS_SEC_INITIALIZED Severity=Success Facility=ITF
Language=English
Security component initialized
.
MessageId=+1 SymbolicName=EMS_SEC_AUTH_REQUEST_RECVD Severity=Success Facility=ITF
Language=English
Authorization request received
.
MessageId=+1 SymbolicName=EMS_SEC_INTERNAL_OBJ_INVALID Severity=ErrWarn Facility=ITF
Language=English
The Internal objects are not valid
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLIC_KEY_INIT Severity=Success Facility=ITF
Language=English
Initialization of the Public key succeeded
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATE_KEY_INIT Severity=Success Facility=ITF
Language=English
Initialization of the Private key succeeded
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLIC_KEY_LOADED Severity=Success Facility=ITF
Language=English
The Public Key loaded successfully
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATE_KEY_LOADED Severity=Success Facility=ITF
Language=English
The Private Key loaded successfully
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATE_KEY_LOAD_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot load Private Key
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLIC_KEY_LOAD_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot load Public Key
.
MessageId=+1 SymbolicName=EMS_SEC_PRIVATE_KEY_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot Initialize Private Key
.
MessageId=+1 SymbolicName=EMS_SEC_PUBLIC_KEY_INIT_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot Initialize Public Key
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_SIZE_OK Severity=Success Facility=ITF
Language=English
The security token size is OK
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_SET_OK Severity=Success Facility=ITF
Language=English
Setting the encoded token is successful
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_DECODE_OK Severity=Success Facility=ITF
Language=English
The Security Token has been decoded successfully
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_DECRYPT_OK Severity=Success Facility=ITF
Language=English
The Security Token has been decrypted successfully
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_PARSE_OK Severity=Success Facility=ITF
Language=English
The Security Token has been parsed successfully
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_DECODE_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot decode the Security token
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_SET_ERR Severity=ErrWarn Facility=ITF
Language=English
Cannot set the encoded token.
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_SIZE_ERR Severity=ErrWarn Facility=ITF
Language=English
The token size is not OK
.
MessageId=+1 SymbolicName=EMS_SEC_USER_IDENTIFY_RETRY Severity=Success Facility=ITF
Language=English
Retrying to identify the user
.
MessageId=+1 SymbolicName=EMS_SEC_AUTHORIZATION_OK Severity=Success Facility=ITF
Language=English
The request has been authorized for the user: %1, role ID: %2  for resource ID: %3
.
MessageId=+1 SymbolicName=EMS_SEC_TOKEN_CHECK_FAILED_AT Severity=ErrWarn Facility=ITF
Language=English
EMS Security Access Denied: The token for the user: %1 has expired Year %2 Month %3 Day %4 Hour %5 Minute %6 Second %7
.
MessageId=+1 SymbolicName=EMS_SEC_ROLE_NOT_AUTHORIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Security Access Denied: The user %1 Role ID %2 is not authorized to use the resource ID %3
.
MessageId=+1 SymbolicName=EMS_SEC_AUTHORIZATION_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Security Access Denied: Error %4 while checking privileges: User Name %1, Role ID %2, resource requested %3
.
MessageId=+1 SymbolicName=EMS_SEC_NOT_INITIALIZED Severity=ErrWarn Facility=ITF
Language=English
Request failed. Security subsystem has not been initialized.
.
MessageId=+1 SymbolicName=EMS_SEC_INIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Security initialization failed.
.
;
;#endif // INC_EMSSECMSGS


