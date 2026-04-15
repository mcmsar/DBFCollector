;/*******************************************************************************
;*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of Honeywell International, Inc.
;*
;********************************************************************************/

;#ifndef INC_CONFIGCLIENT_MSGS
;#define INC_CONFIGCLIENT_MSGS
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

MessageId=0xF500 SymbolicName=CONFCLI_BASE_CODE Facility=ITF
Language=English
Configuration Client
.
MessageId=+1 SymbolicName=CONFGCLI_HTTPGET_FAIL Severity=ErrWarn Facility=ITF
Language=English
Configuration Client exception performing HTTP GET.  HTTP Status code = %1.  HTTP Reason = %2.
.
MessageId=+1 SymbolicName=CONFGCLI_HTTPGET_FAIL_NO_RESPONSE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client exception performing HTTP GET.  HTTP Server is not responding, URL is http://%1:%2/%3.
.
MessageId=+1 SymbolicName=SATCLIENT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Satellite encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=SATCLIENT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Satellite encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=SATCLIENT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Satellite encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=PIPEMQCLIENT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Pipe to MQ Bridging encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=PIPEMQCLIENT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Pipe to MQ Bridging encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=PIPEMQCLIENT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Pipe to MQ Bridging encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=BEACLIENT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Beacon encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=BEACLIENT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Beacon encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=BEACLIENT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for Beacon encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=CCODECLIENT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for CountryCode encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=CCODECLIENT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for CountryCode encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=CCODECLIENT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for CountryCode encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LUT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LUTConfig encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LUT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LUTConfig encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LUT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LUTConfig encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_MEOLUT_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem MEOLUTConfig encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_MEOLUT_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem MEOLUTConfig encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_MEOLUT_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem MEOLUTConfig encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_CLOCK_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem ClockConfig encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_CLOCK_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem ClockConfig encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_CLOCK_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem ClockConfig encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_FP_CONFIG_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem FPConfig encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_FP_CONFIG_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem FPConfig encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_FP_CONFIG_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem FPConfig encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_CONFIG_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SPConfig encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_CONFIG_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SPConfig encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_CONFIG_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SPConfig encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SP Params Config encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SP Params Config encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem SP Params Config encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_DM_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem DataManager Config encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_DM_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem DataManager Config encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_DM_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem DataManager Config encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SERVICES_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem WinServices Config encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SERVICES_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem WinServices Config encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_SERVICES_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem WinServices Config encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_CONFIG_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LPConfig Config encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_CONFIG_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LPConfig Config encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_CONFIG_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LPConfig Config encountered an exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LP Params Config encountered a configuration parsing exception.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LP Params Config encountered a schema exception while parsing configuration.  Details:  %1.
.
MessageId=+1 SymbolicName=MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Configuration Client for MeoSystem LP Params Config encountered an exception while parsing configuration.  Details:  %1.
.
;
;#endif // INC_CONFIGCLIENT_MSGS
