;/*******************************************************************************
;*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of Honeywell International, Inc.
;*
;********************************************************************************/

;#ifndef INC_PMQ_MSGS
;#define INC_PMQ_MSGS
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

MessageId=0xF450 SymbolicName=PMQ_BRIDGE_BASE_CODE Facility=ITF
Language=English
Pipeline-MQ Bridge
.
MessageId=+1 SymbolicName=PMQ_SERVICE_START Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Service Started
.
MessageId=+1 SymbolicName=PMQ_SERVICE_STOP Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Service Stopped
.
MessageId=+1 SymbolicName=PMQ_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Service did not start due to error (%1)
.
MessageId=+1 SymbolicName=PMQ_LOOP_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Service exception trapped in main processing loop.  No details available.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_SINK_CONNECTED Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue adapter registered a pipeline sink on channel %1 of record size %2 bytes.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_THREAD_EXIT Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue failure with code %1.  Processing thread is exiting.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_PRODUCER_CREATED Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue adapter registered an MQ producer with broker %1 on topic %2 with persistent delivery %3.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_PRODUCER_SEND_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue adapter failed to send message on Message Queue.  Details:  %1.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_THREAD_CONTNUE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue failure in main processing thread with code %1.  Reconnecting pipeline and message queue.  Processing thread will continue.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_EXCEPTION_THREAD_CONTNUE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue exception in main processing thread.  Processing thread will continue.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_REC_SIZE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue failure.  The pipeline data record buffer size is incorrectly configured.  A value of 0 or less has been configured.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_NO_PRODUCER Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue failure.  Unable to transfer pipeline data to MQ.  An MQ Producer is not initialized.
.
MessageId=+1 SymbolicName=PMQ_NUM_MAPPINGS Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge loaded %1 mappings.
.
MessageId=+1 SymbolicName=PMQ_UNSUPPORTED_DIRECTION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge does not support the direction specified in the mapping for %1.  Mapping will be ignored.
.
MessageId=+1 SymbolicName=PMQ_MAPPING_PARSE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to parse the mapping configuration.  This is most likely due to a format error in the configuration.  Error:  %1.
.
MessageId=+1 SymbolicName=PMQ_MAPPING_PARSE_SCHEMA_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to parse the mapping configuration.  This may be due to a format error in the configuration or an error in the schema definition.  Error:  %1.
.
MessageId=+1 SymbolicName=PMQ_MAPPING_GENERAL_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to parse the mapping configuration.  Error details:  %1.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_START_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to start a Pipeline to Message Queue adapter.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_STARTED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge has started %1 Pipeline to Message Queue adapters.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_STOP_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to stop a Pipeline to Message Queue adapter.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_STOPPED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge has stopped %1 Pipeline to Message Queue adapters.
.
MessageId=+1 SymbolicName=PMQ_PTOMQ_PRODUCER_INIT_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipeline to Message Queue adapter failed to initialize a message queue producer.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_SRC_CONNECTED Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter registered a pipeline source on channel %1 of record size %2 bytes.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_CONSUMER_CREATED Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter registered an MQ consumer with broker %1 on topic %2.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_PENDING_MSGS_WARNING Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter has %1 buffered messages awaiting transfer to Pipeline.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_PENDING_MSGS_ALARM Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter has %1 buffered messages awaiting transfer to Pipeline.  The oldest message has been removed to prevent further resource consumption.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_MQ_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter has received an exception notification from the message queue broker:  %1.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_TYPE_NOT_SUPPORTED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter has been configured to process %1 type source messages.  This message type is not currently supported.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_TYPE_NOT_EXPECTED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe adapter has received a message from the Message Queue of an unexpected type.  It will be ignored.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_NO_PSOURCE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe failure.  Unable to transfer MQ data to pipeline.  A pipeline source is not initialized.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_START_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to start a Message Queue to Pipeline adapter.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_STARTED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge has started %1 Message Queue to Pipeline adapters.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_STOP_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge was unable to stop a Message Queue to Pipeline adapter.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_STOPPED Severity=Success Facility=ITF
Language=English
Pipeline-MQ Bridge has stopped %1 Message Queue to Pipeline adapters.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_RECSIZE_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge notes a difference between the configured record size (%1) and the size of records received from the Message Queue (%2).  Data will still be written to Pipeline.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_RECSIZE_MISMATCH_TOO_BIG Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge notes that the configured record size (%1) is smaller than the size of records received from the Message Queue (%2).  Data will not be written to Pipeline.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_CONSUMER_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe exception has been captured by the Message Queue consumer.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_CONSUMER_INIT_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipeline to Message Queue adapter failed to initialize a message queue consumer.
.
MessageId=+1 SymbolicName=PMQ_MQTOPIPE_THREAD_CONTNUE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe failure in main processing thread with code %1.  Reconnecting pipeline and message queue.  Processing thread will continue.
.
MessageId=+1 SymbolicName=PMQ_UNHANDLED_TYPE_CONVERSION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper unable to perform conversion.  Specified conversion is not handled:  %1.  PipeMQBridge configuration has an error.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_TYPE_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper unable to perform conversion.  Input data record size does not match expected for conversion %1.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_CALIB_XML Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed to convert legacy calib type to XML version.  %1 code returned during conversion.
.
MessageId=+1 SymbolicName=PMQ_PIPETOMQ_DEST_TYPE_CONVERT_UNHANDLED Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Pipe to Message Queue does not support conversion to the destination type configured for mapping %1.  Error in configuration.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_FROM_STRING_STREAM Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed to create a stream from an input string with error code %1.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_FROM_STRING_SIZE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed to create a stream from an input string.  The expected number of bytes written did not match expected value.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_FROM_STRING_PARSE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed while parsing an input string for conversion with error code %1.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_FROM_STRING_NULL Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed while parsing an input string for conversion.  Parsing results are NULL.
.
MessageId=+1 SymbolicName=PMQ_CONVERSION_SIT722A_READ_FAILURE Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Type Mapper failed while reading data from a TOA/FOA string message parser class with code %1.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_NO_TEXT_CONVERSION Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe is configured to receive text type messages, but no conversion/map to type is specified in the mapping configuration for mapping %1.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_PIPELINE_WRITE_ERROR Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge Message Queue to Pipe reports an error with code %1 writing data to the pipeline for mapping %2.
.
MessageId=+1 SymbolicName=PMQ_MQTOP_INTRECSIZE_MISMATCH Severity=ErrWarn Facility=ITF
Language=English
Pipeline-MQ Bridge found difference between the expected record size (%1) and the size of records in the internal container (%2). Data will not be written to MQ.
.
;
;#endif // INC_PMQ_MSGS
