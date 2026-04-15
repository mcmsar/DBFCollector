;/********************************************************************
;*	Module:			SATIDMsgs.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Satellite Identification's Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2005 by EMS Technologies, Inc.,
;*										All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;* reproduced in whole or in part, in any form or by any means whatsoever 
;* without the express written permission of EMS Technologies, Inc.
;*
;********************************************************************/
;


;#ifndef INC_SATIDMSGS
;#define INC_SATIDMSGS
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

MessageId=0xDE00 SymbolicName=EMS_SATID_BASE_CODE Facility=ITF
Language=English
EMS Database Resource error.
.
MessageId=+1 SymbolicName=EMS_SATID_UNHANDLED_EXCEPTION_AT Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification captured an unknown exception on <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_SET_TEST_CONFIG Severity=info Facility=ITF
Language=English
EMS Satelite Identification:  The test control file has been set to: "%1".  
.
MessageId=+1 SymbolicName=EMS_SATID_NULL_INPUT Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  No input.
.
MessageId=+1 SymbolicName=EMS_SATID_NULL_OUTPUT Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  No output. 
.
MessageId=+1 SymbolicName=EMS_SATID_NULL_CONTROL_PARAM Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  No test control.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_LOADING_CONTROL_PARAM Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  An error occured during loading control parameters. 
.
MessageId=+1 SymbolicName=EMS_SATID_LOADED_XML_CONTROL_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  Control Data has been loaded from "%1". 
.
MessageId=+1 SymbolicName=EMS_SATID_CONTROL_LOADED_INTO_XML_STRING Severity=ErrWarn Facility=ITF
Language=English
EMS Beacon Simulator: The control object has been loaded into XML = "%1".
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_RUN_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:   An error occured while the test is running. 
.
MessageId=+1 SymbolicName=EMS_SATID_UNHANDLED_RUN_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification:  An error occured while the test is running. 
.
MessageId=+1 SymbolicName=EMS_SATID_COINIT_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification: Coinitialize failed, hr = <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ENGINE_STARTED Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification: The Engine has started.
.
MessageId=+1 SymbolicName=EMS_SATID_ENGINE_PAUSED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The engine has been paused. 
.
MessageId=+1 SymbolicName=EMS_SATID_ENGINE_RESUMED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The engine has been resumed. 
.
MessageId=+1 SymbolicName=EMS_SATID_ENGINE_STOPPED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The engine has been stopped. 
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_SET_URL_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to SetURL, URL String <%1>, hr = <%2>. 
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_CREATE_DI_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to create instance of DataIO, hr = <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_SET_MODE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to set open mode to read, hr = <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_SET_TRANS_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to set translation parameter, translation string is <%1>, hr <%2>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_SET_EVENT_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to set event name, event name is <%1>, hr <%2>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_IS_ACTIVE_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn isActive() failed, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_ACTIVATE_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to activate DataIO, hr <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_GET_STREAM_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to get data input stream, hr <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_CREATE_EVENT_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn failed to create input event, hr <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_GET_DATA Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn error while retrieving data, hr <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAIN_NO_INPUT_STREAM Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataIn no input stream.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_SET_URL_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to Set URL, URL string <1%>, hr <%2>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_CREATE_DATAO_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to create instance of DataIO, hr = <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_SET_MODE_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to set open mode to write, hr = <%1>.
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_SET_TRANS_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to set translation parameter, translation string is <%1>, hr <%2>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_GET_STREAM_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to get data output stream, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_PATTERN_WRITE_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to get data Pattern Data output stream, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_DATAOUT_PROB_WRITE_FAILED Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: DataOut failed to get data Prob Data output stream, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ENGINE_OUTPUT_PATTERN_DATA Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The engine outputs Pattern Data to output stream. 
.
MessageId=+1 SymbolicName=EMS_SATID_GET_FROM_ORBIT_INTERFACE_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Visible Sat. List Configurator failed to get satellite's orbital vectors , hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_ORBIT_INTERFACE_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Unable to CoCreateInstance IEMSOrbit , hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_LUT_INFO_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Unable to CoCreateInstance instance LUTInfo , hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_CALCULATE_RANGE_RATE Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error in CEMSRangeRate::Calculate(), hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_DISPLAY_LUT_COORD Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Debug: Displays LUT Coordinates, hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_FROM_LUT_INFO_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error in lpLutInfo->GetSiteLocation, hr <%1> 
.
MessageId=+1 SymbolicName=EMS_SATID_CALCULATED_DOPPLER_SHIFT_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Calculated Doppler Shift Out of Frequency Range 
.
MessageId=+1 SymbolicName=EMS_SATID_DOPPLER_FREQ_RANGE_IS_ZERO Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error in the control parameter:Doppler Frequency Range is 0
.
MessageId=+1 SymbolicName=EMS_SATID_SIGNAL_PROBABILITIES Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Debug: displays first, second and joint probability
.
MessageId=+1 SymbolicName=EMS_SATID_CORRELATED_AND_CALCULATED_DOPPLER_SHIFT Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Debug: displays correlated and calculated Doppler shift
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_IN_READING_SAT_PATTERN_NO Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error ir reading pattern from the Pattern File <%1>, hr <%2>
.
MessageId=+1 SymbolicName=EMS_SATID_DATAIN_INIT_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error to initialize DataIn Object,  hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_DATAOUT_INIT_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error to initialize DataOut Object, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_CONTROL_OBJ_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Control Obj does not exist, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_IN_READING_ALL_SAT_PATTERNS Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error ir reading ALL patterns from the Pattern Files, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_ADD_NEW_SIGNAL Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The Sat Signal Calibator Obj does not exist, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_VALIDATE_SIGNAL Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: The Sat Validator Obj does not exist, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_PATTERN_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: There is NO PATTERN generated, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_ERROR_IN_VALIDATION_SETUP Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error is setup: no patterns and Control setup error
.
MessageId=+1 SymbolicName=EMS_SATID_LOAD_PARTTERNS_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: It has be loadded less patterns than the visible satellites
.
MessageId=+1 SymbolicName=EMS_SATID_OUTPUT_PATTERN_ERROR Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Error in Output Pattern to the File, hr <%1>
.
MessageId=+1 SymbolicName=EMS_SATID_BESTMATCHPROB_AND_DOPPSHIFTPROB Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Debug: probabilities: bestmatch nad doppshift, prob1 <%1>, prob2 <%2>
.
MessageId=+1 SymbolicName=EMS_SATID_ANGLE_AND_COS_ANGLE Severity=Info Facility=ITF
Language=English
EMS Satelite Identification: Debug: angle and Cos(angle), angle <%1>, cos(angle) <%2>
.
;
;#endif



