;/*********************************************************************
;*	              Copyright (c) 2008 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/

;/*******************************************************************

 ; Revision Record

;	$Log:
;	$
;********************************************************************/

;#ifndef INC_BEACONSNMP_MSGS
;#define INC_BEACONSNMP_MSGS
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

MessageId=0xE350 SymbolicName=EMS_BEACONSNMP_BASE_CODE Facility=ITF
Language=English
EMS Beacon SNMP Agent error.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_PORTUNINITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Cannot communicate with the beacon.  The port has not been initialized.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_BADRESPONSE Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Cannot interpret the response read from the beacon port.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_ONREQ Severity=Success Facility=ITF
Language=English
EMS Beacon SNMP Agent: Received request to turn beacon on.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_OFFREQ Severity=Success Facility=ITF
Language=English
EMS Beacon SNMP Agent: Received request to turn beacon off.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_ONFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Request to turn on the beacon failed.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_OFFFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Request to turn off the beacon failed.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_UNHANDLEDREFRESHEXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Unhandled exception while refreshing beacon information
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_CURRENTSETTINGS Severity=Success Facility=ITF
Language=English
EMS Beacon SNMP Agent: Beacon = %1, Message = <%2>
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_SUPPORTUNAVAILABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: SNMP Agent support not available.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_SERVICESTARTED Severity=Success Facility=ITF
Language=English
EMS Beacon SNMP Agent: Started
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_SERVICESTOPPED Severity=Success Facility=ITF
Language=English
EMS Beacon SNMP Agent: Stopped
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_UNHANDLEDINITEXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Unhandled exception while initializing
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_MIBCOMPILEERROR Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Failed to compile MIB files.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_PORTOPENFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Failed to open port %1. Confirm there is no conflict.
.
MessageId=+1 SymbolicName=EMS_BEACONSNMP_BEACONINITFAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon SNMP Agent: Failed to initialize reference to beacon component.
.
;
;#endif // INC_BEACONSNMP_MSGS
