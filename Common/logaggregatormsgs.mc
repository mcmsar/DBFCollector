;/*********************************************************************
;*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

;#ifndef INC_LOG_AGGREGATOR_MSGS
;#define INC_LOG_AGGREGATOR_MSGS
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

MessageId=0xF300 SymbolicName=EMS_LA_BASE_CODE Facility=ITF
Language=English
EMS Pass Scheduler error.
.
MessageId=+1 SymbolicName=EMS_LA_STARTED Severity=Success Facility=ITF
Language=English
EMS Log Aggregator has started.
.
MessageId=+1 SymbolicName=EMS_LA_START_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator failed to start with error code %1.
.
MessageId=+1 SymbolicName=EMS_LA_STOPPED Severity=Success Facility=ITF
Language=English
EMS Log Aggregator has stopped.
.
MessageId=+1 SymbolicName=EMS_LA_NO_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator failed to find a configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
.
MessageId=+1 SymbolicName=EMS_LA_NO_TEMP_FOLDER Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator failed to find a value for the temporary folder (%1) in the configuration file (%2).
.
MessageId=+1 SymbolicName=EMS_LA_MAIN_LOOP_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator caught an unknown exception in the main processing loop.
.
MessageId=+1 SymbolicName=EMS_LA_NO_OUTPUT_FOLDER_CONFIG Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator failed to find a configured log output folder.
.
MessageId=+1 SymbolicName=EMS_LA_LOG_CONSUMER_NOT_CONNECTED Severity=Success Facility=ITF
Language=English
EMS Log Aggregator Service reports that it could not connect to the Message Queue for receipt of log messages. Processing will continue, but logs will not be received.
.
MessageId=+1 SymbolicName=EMS_LA_PRODUCER_CREATED Severity=Success Facility=ITF
Language=English
EMS Log Aggregator Service registered an MQ producer with broker %1 on topic %2 with persistent delivery %3.
.
MessageId=+1 SymbolicName=EMS_LA_PRODUCER_INIT_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator Service failed to initialize a message queue producer.
.
MessageId=+1 SymbolicName=EMS_LA_INVALID_LOG_RECORD_SIZE Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator Service unable to convert binary log to XML. Input log record does not match expected size.
.
MessageId=+1 SymbolicName=EMS_LA_NO_MQ_PRODUCER Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator Service failure. Unable to transfer pipeline data to MQ. MQ Producer is not initialized.
.
MessageId=+1 SymbolicName=EMS_LA_PRODUCER_SEND_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Log Aggregator Service failed to send message on Message Queue. Details:  %1.
.
MessageId=+1 SymbolicName=EMS_LA_LOG_EXCEPTION Severity=Success Facility=ITF
Language=English
EMS Aggregator Service reports that an exception report was received from the log message handler.
.
;
;#endif // INC_LOG_AGGREGATOR_MSGS

