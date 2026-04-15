/********************************************************************
*	Module:			EMSSecMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Security Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Dec01		RI		start 
		2005Jan05		CH		Ticket 6652: significant changes to 
								support use of actual error code as
								the message identifier for logging
********************************************************************/
#ifndef INC_EMSSECMSGS
#define INC_EMSSECMSGS

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
// MessageId: EMS_SECURITY_BASE_CODE
//
// MessageText:
//
//  EMS SECURITY Error
//
#define EMS_SECURITY_BASE_CODE           ((EMS_RESULT)0x0004BC00L)

//
// MessageId: EMS_SECURITY_ACCESS_DENIED
//
// MessageText:
//
//  EMS Security Access Denied
//
#define EMS_SECURITY_ACCESS_DENIED       ((EMS_RESULT)0x8004BC01L)

//
// MessageId: EMS_SEC_RESOURCE_UNDEFINED
//
// MessageText:
//
//  EMS Security Resource undefined
//
#define EMS_SEC_RESOURCE_UNDEFINED       ((EMS_RESULT)0x8004BC02L)

//
// MessageId: EMS_SEC_KEY_CLOSE_ERROR
//
// MessageText:
//
//  EMS Security Cryptography Key closing error
//
#define EMS_SEC_KEY_CLOSE_ERROR          ((EMS_RESULT)0x8004BC03L)

//
// MessageId: EMS_SEC_KEY_FWRITE_ERR
//
// MessageText:
//
//  EMS Security Writing Cryptography Key to file error
//
#define EMS_SEC_KEY_FWRITE_ERR           ((EMS_RESULT)0x8004BC04L)

//
// MessageId: EMS_SEC_KEY_FREAD_ERR
//
// MessageText:
//
//  EMS Security Reading Cryptography Key file error
//
#define EMS_SEC_KEY_FREAD_ERR            ((EMS_RESULT)0x8004BC05L)

//
// MessageId: EMS_SEC_PUBLICKEY_LOAD_ERR
//
// MessageText:
//
//  EMS Security Loading Public Key error
//
#define EMS_SEC_PUBLICKEY_LOAD_ERR       ((EMS_RESULT)0x8004BC06L)

//
// MessageId: EMS_SEC_PUBLICKEY_GEN_ERR
//
// MessageText:
//
//  EMS Security Generating Public Key error
//
#define EMS_SEC_PUBLICKEY_GEN_ERR        ((EMS_RESULT)0x8004BC07L)

//
// MessageId: EMS_SEC_TOKEN_DECRYPT_ERR
//
// MessageText:
//
//  EMS Security Decrypting token error
//
#define EMS_SEC_TOKEN_DECRYPT_ERR        ((EMS_RESULT)0x8004BC08L)

//
// MessageId: EMS_SEC_TOKEN_ENCRYPT_ERR
//
// MessageText:
//
//  EMS Security Encrypting token error
//
#define EMS_SEC_TOKEN_ENCRYPT_ERR        ((EMS_RESULT)0x8004BC09L)

//
// MessageId: EMS_SEC_WRITE_KEYID_ERR
//
// MessageText:
//
//  EMS Security Writing Key ID error
//
#define EMS_SEC_WRITE_KEYID_ERR          ((EMS_RESULT)0x8004BC0AL)

//
// MessageId: EMS_SEC_READ_KEYID_ERR
//
// MessageText:
//
//  EMS Security Reading Key ID error
//
#define EMS_SEC_READ_KEYID_ERR           ((EMS_RESULT)0x8004BC0BL)

//
// MessageId: EMS_SEC_TOKEN_CREATETXT_ERR
//
// MessageText:
//
//  EMS Security Creating text token error
//
#define EMS_SEC_TOKEN_CREATETXT_ERR      ((EMS_RESULT)0x8004BC0CL)

//
// MessageId: EMS_SEC_TOKEN_PARSE_ERR
//
// MessageText:
//
//  EMS Security Parsing text token error
//
#define EMS_SEC_TOKEN_PARSE_ERR          ((EMS_RESULT)0x8004BC0DL)

//
// MessageId: EMS_SEC_TOKEN_ENCODEDTOBIN_ERR
//
// MessageText:
//
//  EMS Security Error Creating binary token from encoded one
//
#define EMS_SEC_TOKEN_ENCODEDTOBIN_ERR   ((EMS_RESULT)0x8004BC0EL)

//
// MessageId: EMS_SEC_TOKEN_EXPIRED
//
// MessageText:
//
//  EMS Security Error Security token expired
//
#define EMS_SEC_TOKEN_EXPIRED            ((EMS_RESULT)0x8004BC0FL)

//
// MessageId: EMS_SEC_PRIVATEKEY_LOAD_ERR
//
// MessageText:
//
//  EMS Security Loading Private Key error
//
#define EMS_SEC_PRIVATEKEY_LOAD_ERR      ((EMS_RESULT)0x8004BC10L)

//
// MessageId: EMS_SEC_PRIVATEKEY_GEN_ERR
//
// MessageText:
//
//  EMS Security Generating Private Key error
//
#define EMS_SEC_PRIVATEKEY_GEN_ERR       ((EMS_RESULT)0x8004BC11L)

//
// MessageId: EMS_SEC_PRIVATEKEY_FWRITE_ERR
//
// MessageText:
//
//  EMS Security Writing Private Key to file error
//
#define EMS_SEC_PRIVATEKEY_FWRITE_ERR    ((EMS_RESULT)0x8004BC12L)

//
// MessageId: EMS_SEC_PRIVATEKEY_FREAD_ERR
//
// MessageText:
//
//  EMS Security Reading Private Key file error
//
#define EMS_SEC_PRIVATEKEY_FREAD_ERR     ((EMS_RESULT)0x8004BC13L)

//
// MessageId: EMS_SEC_IDENTIFY_USER_ERR
//
// MessageText:
//
//  EMS Security Error identifying user
//
#define EMS_SEC_IDENTIFY_USER_ERR        ((EMS_RESULT)0x8004BC14L)

//
// MessageId: EMS_SEC_EXTRACTING_USERNAME_ERR
//
// MessageText:
//
//  EMS Security Error extracting user name
//
#define EMS_SEC_EXTRACTING_USERNAME_ERR  ((EMS_RESULT)0x8004BC15L)

//
// MessageId: EMS_SEC_EXTRACTING_USERGROUPS_ERR
//
// MessageText:
//
//  EMS Security Error extracting user groups
//
#define EMS_SEC_EXTRACTING_USERGROUPS_ERR ((EMS_RESULT)0x8004BC16L)

//
// MessageId: EMS_SEC_NOROLEID_ERROR
//
// MessageText:
//
//  EMS Security Error cannot find the role id
//
#define EMS_SEC_NOROLEID_ERROR           ((EMS_RESULT)0x8004BC17L)

//
// MessageId: EMS_SEC_GETTING_KEYINFO_ERR
//
// MessageText:
//
//  EMS Security Error cannot find the security key information
//
#define EMS_SEC_GETTING_KEYINFO_ERR      ((EMS_RESULT)0x8004BC18L)

//
// MessageId: EMS_SEC_AUTHORIZATION_DISABLED
//
// MessageText:
//
//  EMS Security, Authorization is disabled, the call succeeded
//
#define EMS_SEC_AUTHORIZATION_DISABLED   ((EMS_RESULT)0x0004BC19L)

//
// MessageId: EMS_SEC_CANNOT_INITIALIZE_EXCEPTION
//
// MessageText:
//
//  EMS Security initialization failed with an unhandled exception
//
#define EMS_SEC_CANNOT_INITIALIZE_EXCEPTION ((EMS_RESULT)0x8004BC1AL)

//
// MessageId: EMS_SEC_CANNOT_AUTHENTICATE_EXCEPTION
//
// MessageText:
//
//  EMS Security authentication failed with an unhandled exception
//
#define EMS_SEC_CANNOT_AUTHENTICATE_EXCEPTION ((EMS_RESULT)0x8004BC1BL)

//
// MessageId: EMS_SEC_INITIALIZED
//
// MessageText:
//
//  Security component initialized
//
#define EMS_SEC_INITIALIZED              ((EMS_RESULT)0x0004BC1CL)

//
// MessageId: EMS_SEC_AUTH_REQUEST_RECVD
//
// MessageText:
//
//  Authorization request received
//
#define EMS_SEC_AUTH_REQUEST_RECVD       ((EMS_RESULT)0x0004BC1DL)

//
// MessageId: EMS_SEC_INTERNAL_OBJ_INVALID
//
// MessageText:
//
//  The Internal objects are not valid
//
#define EMS_SEC_INTERNAL_OBJ_INVALID     ((EMS_RESULT)0x8004BC1EL)

//
// MessageId: EMS_SEC_PUBLIC_KEY_INIT
//
// MessageText:
//
//  Initialization of the Public key succeeded
//
#define EMS_SEC_PUBLIC_KEY_INIT          ((EMS_RESULT)0x0004BC1FL)

//
// MessageId: EMS_SEC_PRIVATE_KEY_INIT
//
// MessageText:
//
//  Initialization of the Private key succeeded
//
#define EMS_SEC_PRIVATE_KEY_INIT         ((EMS_RESULT)0x0004BC20L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_LOADED
//
// MessageText:
//
//  The Public Key loaded successfully
//
#define EMS_SEC_PUBLIC_KEY_LOADED        ((EMS_RESULT)0x0004BC21L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_LOADED
//
// MessageText:
//
//  The Private Key loaded successfully
//
#define EMS_SEC_PRIVATE_KEY_LOADED       ((EMS_RESULT)0x0004BC22L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_LOAD_ERR
//
// MessageText:
//
//  Cannot load Private Key
//
#define EMS_SEC_PRIVATE_KEY_LOAD_ERR     ((EMS_RESULT)0x8004BC23L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_LOAD_ERR
//
// MessageText:
//
//  Cannot load Public Key
//
#define EMS_SEC_PUBLIC_KEY_LOAD_ERR      ((EMS_RESULT)0x8004BC24L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_INIT_ERR
//
// MessageText:
//
//  Cannot Initialize Private Key
//
#define EMS_SEC_PRIVATE_KEY_INIT_ERR     ((EMS_RESULT)0x8004BC25L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_INIT_ERR
//
// MessageText:
//
//  Cannot Initialize Public Key
//
#define EMS_SEC_PUBLIC_KEY_INIT_ERR      ((EMS_RESULT)0x8004BC26L)

//
// MessageId: EMS_SEC_TOKEN_SIZE_OK
//
// MessageText:
//
//  The security token size is OK
//
#define EMS_SEC_TOKEN_SIZE_OK            ((EMS_RESULT)0x0004BC27L)

//
// MessageId: EMS_SEC_TOKEN_SET_OK
//
// MessageText:
//
//  Setting the encoded token is successful
//
#define EMS_SEC_TOKEN_SET_OK             ((EMS_RESULT)0x0004BC28L)

//
// MessageId: EMS_SEC_TOKEN_DECODE_OK
//
// MessageText:
//
//  The Security Token has been decoded successfully
//
#define EMS_SEC_TOKEN_DECODE_OK          ((EMS_RESULT)0x0004BC29L)

//
// MessageId: EMS_SEC_TOKEN_DECRYPT_OK
//
// MessageText:
//
//  The Security Token has been decrypted successfully
//
#define EMS_SEC_TOKEN_DECRYPT_OK         ((EMS_RESULT)0x0004BC2AL)

//
// MessageId: EMS_SEC_TOKEN_PARSE_OK
//
// MessageText:
//
//  The Security Token has been parsed successfully
//
#define EMS_SEC_TOKEN_PARSE_OK           ((EMS_RESULT)0x0004BC2BL)

//
// MessageId: EMS_SEC_TOKEN_DECODE_ERR
//
// MessageText:
//
//  Cannot decode the Security token
//
#define EMS_SEC_TOKEN_DECODE_ERR         ((EMS_RESULT)0x8004BC2CL)

//
// MessageId: EMS_SEC_TOKEN_SET_ERR
//
// MessageText:
//
//  Cannot set the encoded token.
//
#define EMS_SEC_TOKEN_SET_ERR            ((EMS_RESULT)0x8004BC2DL)

//
// MessageId: EMS_SEC_TOKEN_SIZE_ERR
//
// MessageText:
//
//  The token size is not OK
//
#define EMS_SEC_TOKEN_SIZE_ERR           ((EMS_RESULT)0x8004BC2EL)

//
// MessageId: EMS_SEC_USER_IDENTIFY_RETRY
//
// MessageText:
//
//  Retrying to identify the user
//
#define EMS_SEC_USER_IDENTIFY_RETRY      ((EMS_RESULT)0x0004BC2FL)

//
// MessageId: EMS_SEC_AUTHORIZATION_OK
//
// MessageText:
//
//  The request has been authorized for the user: %1, role ID: %2  for resource ID: %3
//
#define EMS_SEC_AUTHORIZATION_OK         ((EMS_RESULT)0x0004BC30L)

//
// MessageId: EMS_SEC_TOKEN_CHECK_FAILED_AT
//
// MessageText:
//
//  EMS Security Access Denied: The token for the user: %1 has expired Year %2 Month %3 Day %4 Hour %5 Minute %6 Second %7
//
#define EMS_SEC_TOKEN_CHECK_FAILED_AT    ((EMS_RESULT)0x8004BC31L)

//
// MessageId: EMS_SEC_ROLE_NOT_AUTHORIZED
//
// MessageText:
//
//  EMS Security Access Denied: The user %1 Role ID %2 is not authorized to use the resource ID %3
//
#define EMS_SEC_ROLE_NOT_AUTHORIZED      ((EMS_RESULT)0x8004BC32L)

//
// MessageId: EMS_SEC_AUTHORIZATION_FAILED
//
// MessageText:
//
//  EMS Security Access Denied: Error %4 while checking privileges: User Name %1, Role ID %2, resource requested %3
//
#define EMS_SEC_AUTHORIZATION_FAILED     ((EMS_RESULT)0x8004BC33L)

//
// MessageId: EMS_SEC_NOT_INITIALIZED
//
// MessageText:
//
//  Request failed. Security subsystem has not been initialized.
//
#define EMS_SEC_NOT_INITIALIZED          ((EMS_RESULT)0x8004BC34L)

//
// MessageId: EMS_SEC_INIT_ERROR
//
// MessageText:
//
//  EMS Security initialization failed.
//
#define EMS_SEC_INIT_ERROR               ((EMS_RESULT)0x8004BC35L)


#endif // INC_EMSSECMSGS
