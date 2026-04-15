;/********************************************************************
;*	Module:			SITMessageCore.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS SIT Message Core Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2004 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_SITMESSAGECOREMSG
;#define INC_SITMESSAGECOREMSG
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

MessageId=0xC600 SymbolicName=EMS_SITMSGCORE_BASE_CODE Facility=ITF
Language=English
EMS SIT Message Core Error
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NOATTRIBUTE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that the attribute named <%1> could not be found in a SIT or MF definition.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_LINE_NOMFID Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that an MF defined as part of a SIT Message Line has no <%1> attribute defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_MFDEF_NOTFOUND Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a definition for MF <%1> could not be found.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_CONFIG_MANAGER Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports error <%1> attempting to connect to the CM subsystem.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_MFDEFS_URL Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports error <%1> attempting to retrieve the MF Definitions URL from the CM subsystem.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_SITDEFS_URL_STRING Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to retrieve the SIT Definitions URL from the CM subsystem.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_LOAD_SITDEFS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to load and parse the SIT Definitions from URL <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_SITS_NODE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to obtain the SITs tree from the SIT Definitions.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_SITIDS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to retrieve any SIT Identifiers from the SIT Definitions.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_SIT_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to find the specification for SIT Type <%1> in the SIT Definitions.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_MFS_NODE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to obtain the MFs tree from the Message Field Definitions.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_MFDEFS_URL_STRING Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to retrieve the Message Field Definitions URL from the CM subsystem.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_LOAD_MFDEFS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it was unable to load and parse the Message Field Definitions from URL <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_SUB_FLD_DEFINITION Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a SIT Message sub-field does not have an associated definition.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_LENGTH Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field max length is <%1>, but actual length is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MIN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field minimum allowable is <%1>, but actual value is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MAX Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field maximum allowable is <%1>, but actual value is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MIN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field minimum allowable is <%1>, but actual value is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MAX Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field maximum allowable is <%1>, but actual value is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_MULTILINE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field illegally contains multiple lines.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SUBMF_INVALID_VALUE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports a SIT Message validation error:  sub-field value <%1> does not match an entry in valid list.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_SERIALIZATION_MF_NO_SEPS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it could not retrieve the default Message Field Separator character/string.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_SERIALIZATION_MF_NO_SUBMFS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that, while serializing, it encountered a Message Field that does not have any sub-fields.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message Field object was not initialized with a definition prior to deserializing.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SUBFIELDS_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message Field object was encountered during deserialization for which no sub-fields are defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SEPS_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it could not retrieve any Message Field separators while attempting to deserialize an MF.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_PARSE_NOSEP Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing Message Field <%1> because no MF separator was found.  MF contents:  <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_LENGTH_DEFINED_ZERO Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing Message Field <%1> because sub-field <%2> has a defined length of 0 or less and no terminating sequence defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TERM_SEQUENCE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing Message Field <%1> because sub-field <%2> does not contain the expected terminating sequence of <%3>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TYPE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing Message Field <%1> because a sub-field type <%2> is unsupported.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_EOLS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it could not retrieve any Message line terminators while attempting to deserialize a Line.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_LENGTH Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a Message line.  The line length is zero.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFS_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Line object was encountered during deserialization for which no Message Fields are defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message Line object was not initialized with a definition prior to deserializing.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_LINE_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message Line object was not initialized with a definition prior to validation.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFSEPS_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a Message Line.  No Message Field separators are defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_LINE_MF_START_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a Message Line.  The start of a Message Field could not be found.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINES_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a SIT object was encountered during deserialization for which no Lines are defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_SUBFIELD_TERMINATORS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a SIT message.  The termination string for a multi-line MF could not be found in line <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINETERMS_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a SIT Message.  No message line terminators are defined.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_EOL_FOUND Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an error parsing a SIT Message.  The end of line <%1> could not be found.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message object was not initialized with a definition prior to deserializing.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SIT_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message object was not initialized with a definition prior to validation.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_TYPE_CHECK_NO_TYPE_POSITIONS Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a SIT cannot be deserialized because its type cannot be determined.  Its type cannot be determined because no SIT type positions are configured.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_TYPE_NOT_DETERMINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a SIT cannot be deserialized because its type cannot be determined.  It may not contain a SIT type specifier or it may not be at the expected offset into the message.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_MF_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it could not find a definition for Message Field <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_LINE_MAX_LEN_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message Line fails validation because it exceeds the maximum allowable length.  Length is <%1> and maximum is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_VALIDATION_SIT_MAX_CHARACTERS_EXCEEDED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a SIT Message fails validation because it exceeds the maximum allowable number of characters.  Number of characters is <%1> and maximum is <%2>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_INITIALIZE_SIT_NO_DEFN Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that a Message object was not set with a definition prior to initializing.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_SIT_ADDCHILD_NO_EMBEDDED_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports an attempt to encapsulate a SIT message within another SIT that is not defined as a container.
.
MessageId=+1 SymbolicName=EMS_SITMSGFILESCAN_NO_LOG_FILE_SPECD Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message File Scanner reports that a request to write a processed file log to disk cannot be performed because a destination file path and name has not been specified.
.
MessageId=+1 SymbolicName=EMS_SITMSGFILESCAN_INVALID_LOG_ENTRY_FORMAT Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message File Scanner reports that an entry of an invalid format was found in a log file.  Line contents:  <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGFILESCAN_NO_TRANS_DIR_SPECIFIED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message File Scanner reports that no transfer directory has been specified.
.
MessageId=+1 SymbolicName=EMS_SITMSGFILESCAN_NO_LOG_DIR_SPECIFIED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message File Scanner reports that no directory for outputting receive log files has been specified.
.
MessageId=+1 SymbolicName=EMS_SITMSGFILESCAN_LOG_FILE_NAME_CREATION Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message File Scanner reports that a log file name could not be constructed.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_SET_SUBMF_UNHANDLEDTYPE Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that an attempt was made to set a sub-field's value using an unexpected data type.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_SET_SUBMF_NOFORMAT Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that an attempt was made to set a sub-field's value using it's native type, but no format string could be found in the sub-field's definition.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_NO_VALIDATION_ERRORS Severity=Success Facility=ITF
Language=English
EMS SIT Editor reports no validation errors found.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_NO_ROUTES Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports that it could not retrieve a list of routes from the configuration manager due to error <%1>.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_CONFIGURATION_READ_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports configuration manager error <%1> while attempting to read [%2:%3].%4.
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_CONFIGURATION_WRITE_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Message Core reports configuration manager error <%1> while attempting to set [%2:%3].%4 to value <%5>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_SENDING_INFO Severity=Info Facility=ITF
Language=English
EMS SIT Editor sending SIT Message on <%1> routes.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_SENDING_TO_ROUTE_INFO Severity=Info Facility=ITF
Language=English
EMS SIT Editor sending SIT Message via route <%1>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_MSG_QUEUED_SUCCESS Severity=Success Facility=ITF
Language=English
EMS SIT Editor successfully queued message for transmission.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_UNKNOWN_TRANSMISSION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that an unknown error has occurred when attempting to queue a message for transmission.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_UNKNOWN_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that an error has occurred.  The error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_LINE_INSERTION_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports an error attempting to insert a new line into a SIT message.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_NO_SIT_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that it was unable to find the specification for SIT Type <%1> in the SIT Definitions.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_NO_EOLS_DEFINED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that no End-Of-Line sequences are defined in the configuration.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_NO_DEFAULT_SRC_SELECTED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that no source has been selected for default.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_SIT_NOT_SUPPORTED Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that SIT <%1> is not supported.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_TITLE Severity=Info Facility=ITF
Language=English
EMS SIT Editor
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_SAVE_AS_PROMPT Severity=Info Facility=ITF
Language=English
Save currently open message to file before proceeding?
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_VALIDATION_ERRORS_PROMPT Severity=Info Facility=ITF
Language=English
Validation errors have been found.  Do you wish to continue anyway?
.
MessageId=+1 SymbolicName=EMS_SITMSGCORE_INVALID_MF_LENGTH Severity=Info Facility=ITF
Language=English
EMS SIT Message Core reports an error extracting a sub-field from MF <%1> with value <%2>.  The MF length is <%3>, but attempting to extract sub-field from offset <%4> with length <%5>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_NO_TRANSFER_DIRECTORY Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that no transfer directory has been specified.  A value is required.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_CANNOT_ACCESS_DIRECTORY Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that it cannot access the directory <%1>.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_CHECKING_COMMS_STATUS Severity=Info Facility=ITF
Language=English
EMS SIT Editor checking EMS Communications subsystem status.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_COMMS_SERVICE_RUNNING Severity=Info Facility=ITF
Language=English
EMS SIT Editor reports that the EMS Communications subsystem is running.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_COMMS_SERVICE_NOT_RUNNING Severity=ErrWarn Facility=ITF
Language=English
EMS SIT Editor reports that the EMS Communications subsystem could not be started.
.
MessageId=+1 SymbolicName=EMS_SITEDITOR_INITIALIZING_SCANNER_INFO Severity=Info Facility=ITF
Language=English
EMS SIT Editor is initializing the directory scanner...
.
;
;#endif
