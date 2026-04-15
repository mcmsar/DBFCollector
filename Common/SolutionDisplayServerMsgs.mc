;/********************************************************************
;*	Module:			SolutionDisplayServerMessages.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for Solution Display Server Errors & Messages
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


;#ifndef INC_SOLNDISPSERVERMSG
;#define INC_SOLNDISPSERVERMSG
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

MessageId=0xCD00 SymbolicName=EMS_SOLN_DISP_SERV_BASE_CODE Facility=ITF
Language=English
EMS Solution Display Server error.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the satellite layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the satellite layer.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_TRACK_COL_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the colour for the satellite track while generating the satellite layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the satellite layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the configuration for satellite <%1> in order to extract data filters for the satellite layer.  
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the Solution Display configuration interface while generating the satellite layer.  A NULL pointer was returned.  
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_INIT_SAT_TRACK_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred initializing the satellite track calculation object while generating the satellite layer.  The returned error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_CALCULATE_SAT_TRACK_FAIL_SAT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred running the satellite track calculation object to generate the satellite layer.  The returned error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the configuration for beacon type <%1> in order to generate data for the beacon layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the beacon layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the beacon layer.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_POINT_ADD_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to add a point to a points collection object while generating the beacon layer.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the beacon layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_BITMAP_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the symbol bitmap configuration for beacon type <%1> while generating the beacon layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_NO_BEACON_TYPE_BEA Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  No beacon type was specified in a request to display solutions.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE_BEA Severity=ErrWarn Facility=ITF
Language=English
An error has occurred.  An unrecognized beacon type was specified, <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the mutual visibility layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the mutual visibility layer.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the mutual visibility layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the configuration for LUT <%1> while generating the mutual visibility layer.  
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_INIT_CALC_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred initializing the mutual visibility calculation object while generating the mutual visibility layer.  The returned error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_CALCULATE_MVIS_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred running the mutual visibility calculation object to generate the mutual visibilty layer.  The returned error code is <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_CONFIG_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the configuration for LUT <%1> in order to extract data filters for the mutual visibility layer.  
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_STATIC_MODE_NO_TIME_CRITERIA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  Static update mode was chosen but no filter criteria were specified.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_UNRECOGNIZED_TIME_CRITERIA_TYPE Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error has occurred.  An unrecognized time criteria type was specified, <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_UNRECOGNIZED_UPDATE_MODE Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error has occurred.  An unrecognized update mode was specified, <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SAT_TRACK_NOT_FOUND Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error has occurred.  A satellite track record could not be found for satellite <%1> with pass identifier <%2>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_TLE_SELECT_NO_SATID Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error has occurred.  Dynamic data calculator attempting to retrieve a TLE, but no satellite identifier was provided.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_BAD_BEACON_CRITERIA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  The dataset selection critiera specified for beacon type <%1> do not include any timestamp or other filter conditions.  A query cannot be run without criteria.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_REGION_COL_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the colour for the mutual visibility region while generating the mutual visibility layer.  A NULL pointer was returned.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the Solution Display configuration interface while generating the mutual visibility layer.  A NULL pointer was returned.  
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_GET_SOLN_PROC_TIME_FAIL_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve the solution processing time for satellite <%1>, pass <%2>, LUT <%3>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_INSUFFICIENT_CRITERIA_BEA Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  An error occurred attempting to retrieve data for the beacon layer in static mode.  Insufficient criteria were specified.  At minimum, either a time range or a pass specified by satellite ID and pass ID must be included in the criteria.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_MVIS Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  While generating the mutual visibility layer, unable to find pass summary data for LUT <%1>.
.
MessageId=+1 SymbolicName=EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_LUT Severity=ErrWarn Facility=ITF
Language=English
Solution Display Server:  While generating the LUT visibility layer, unable to find pass summary data for LUT <%1>.
.
;
;#endif
