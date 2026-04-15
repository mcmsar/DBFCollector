;/********************************************************************
;*	Module:			GeoCalibMsg.mc 
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS Calib406 Errors & Messages
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
;*					All rights reserved
;*	This program is unpublished software and contains the trade secrets
;*	and confidential information of EMS Technologies, Inc.  It may not be 
;*	reproduced in whole or in part, in any form or by any means whatsoever 
;*	without the express written permission of EMS Technologies, Inc.
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
;	0.0	01/05/21		rvw	start
;
;********************************************************************/
;#ifndef INC_GEOCALIBMSG
;#define INC_GEOCALIBMSG
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

MessageId=0xA900 SymbolicName=EMS_GEOCALIB_BASE_CODE Facility=ITF
Language=English
EMS GeoCalib406 Error
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Service Started
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SERVICE_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 Service did not start due to error %1
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Service Stopped
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reports error %1.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_END_PASS Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 reports end of pass for satellite %1
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_START_PASS Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 reports initialized pass for satellite %1
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_TRACER Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Tracer ( %1 )
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_HISTORY_RECS Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 read %1 history records.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_BUFFER_ADD Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reports an error adding record %1 to the buffer.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SARR_OFFSETS Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 has calculated new SARR Offsets ( SatID = %1, Freq=%2 ).
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_ORBIT_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reported error %1 while trying to access IEMSOrbit.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SAT_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reported error %1 while trying to access IEMSSatInfo.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_LUT_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reported error %1 while trying to access IEMSLutInfo.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_SITE_INFO_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reported error %1 while trying to access IEMSLeo600SiteInfo
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_REF_BEACON_ERROR Severity=ErrWarn Facility=ITF
Language=English
EMS GeoCalib406 reported error %1 while trying to access IEMSRefBeacon.
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_TRACE_CONFIG Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Tracer ( cfg: %1=%2 )
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_TRACE_CONFIGYES Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Tracer ( cfg: %1=yes )
.
MessageId=+1 SymbolicName=EMS_GEOCALIB_TRACE_CONFIGNO Severity=Success Facility=ITF
Language=English
EMS GeoCalib406 Tracer ( cfg: %1=no )
.
;
;#endif // INC_GEOCALIBMSG

