;#ifndef INC_CCMSGS
;#define INC_CCMSGS
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

MessageId=0xBA00 SymbolicName=EMS_CC_BASE_CODE Facility=ITF
Language=English
EMS Command and Control Error
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Command and Control Service Started
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Command and Control Service Stopped
.
MessageId=+1 SymbolicName=EMS_CC_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_CC_CMD_SHUTDOWN Severity=Success Facility=ITF
Language=English
EMS Command and Control - Received Shutdown Command
.
MessageId=+1 SymbolicName=EMS_CC_CMD_LUT_STARTUP Severity=Success Facility=ITF
Language=English
EMS Command and Control - Received Startup notification from LUT: %1
.
MessageId=+1 SymbolicName=EMS_CC_BADPROCESS Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to Open Process: %1
.
MessageId=+1 SymbolicName=EMS_CC_PROCESS_NO_START Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to Start Process: %1
.
MessageId=+1 SymbolicName=EMS_CC_PROCESS_STOPPED Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Process %1 stopped.  Attempting to restart.
.
MessageId=+1 SymbolicName=EMS_CC_PROCESS_RESTARTED Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Process %1 has been restarted.
.
MessageId=+1 SymbolicName=EMS_CC_SYSTEM_STARTED Severity=Success Facility=ITF
Language=English
EMS Command and Control - Reports System Started.
.
MessageId=+1 SymbolicName=EMS_CC_TRACER Severity=Success Facility=ITF
Language=English
EMS Command and Control - Trace %1.
.
MessageId=+1 SymbolicName=EMS_CC_WARMRESTART Severity=Success Facility=ITF
Language=English
EMS Command and Control - Warm Restart Commanded.
.
MessageId=+1 SymbolicName=EMS_CC_BAD_ORBIT_DATA Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Reports orbit vectors error for %1.
.
MessageId=+1 SymbolicName=EMS_CC_BAD_SATINFOEX_INTERFACE Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to get IEMSSatelliteInfoEx interface %1.
.
MessageId=+1 SymbolicName=EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to get satellite tolerance information %1.
.
MessageId=+1 SymbolicName=EMS_CC_SERVICESTARTERR Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to start service %1 
.
MessageId=+1 SymbolicName=EMS_CC_SERVICENOTINITIALIZED Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Specified service (%1) has not been initialized 
.
MessageId=+1 SymbolicName=EMS_CC_SERVICEWAITTIMEOUT Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Wait timeout on service (%1)
.
MessageId=+1 SymbolicName=EMS_CC_SERVICESTOPPED Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Service stopped (%1)
.
MessageId=+1 SymbolicName=EMS_CC_EXCEPTION_TRACE Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Cntrol - Exception thrown: File: %1 Line: %2 hr = %3
.
MessageId=+1 SymbolicName=EMS_CC_FILEDELETE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Cntrol - Unable to delete file %1 with error %2
.
MessageId=+1 SymbolicName=EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to get satellite tolerance information hr=%1.
.
MessageId=+1 SymbolicName=EMS_CC_BAD_SATINFOEX_INTERFACE_ERR Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to get IEMSSatelliteInfoEx interface hr=%1.
.
MessageId=+1 SymbolicName=EMS_CC_BAD_ORBIT_DATA_DETAILS Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Reports orbit vectors error for Lut =%1, Sat=%2, PosErr=%3, VelErr=%4, MaxPosErr=%5, MaxVelErr=%6.
.
MessageId=+1 SymbolicName=EMS_CC_BAD_INVALIDSITCONTROLCODE Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Invalid SIT Control Code
.
MessageId=+1 SymbolicName=EMS_CC_INVALIDFILESPEC Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Message: %1 to: %2 does not exist.
.
MessageId=+1 SymbolicName=EMS_CC_PASSSCHED_NOTIMPLEMENTED Severity=ErrWarn Facility=ITF
Language=English
Cannot install pass schedule on a LUT Service.
.
MessageId=+1 SymbolicName=EMS_CC_PASSSCHEDBADCMD Severity=ErrWarn Facility=ITF
Language=English
Unrecognized Pass Schedule Command.
.
MessageId=+1 SymbolicName=EMS_CC_CONFIGITEM_NOTFOUND Severity=ErrWarn Facility=ITF
Language=English
Unable to find config item Group: %1 GroupID: %2 Key: %3.
.
MessageId=+1 SymbolicName=EMS_CC_INVALID_SEL_CRITERIA Severity=ErrWarn Facility=ITF
Language=English
Selection criteria parameter invalid.
.
MessageId=+1 SymbolicName=EMS_CC_INVALID_ORBITVECTOR Severity=ErrWarn Facility=ITF
Language=English
Invalid Orbit Vector.
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_EX_START Severity=Success Facility=ITF
Language=English
EMS Command and Control %1 Started
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_EX_STOP Severity=Success Facility=ITF
Language=English
EMS Command and Control %1 Stopped
.
MessageId=+1 SymbolicName=EMS_CC_SYSTEM_EX_STARTED Severity=Success Facility=ITF
Language=English
EMS Command and Control - Reports %1 Started.
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_STATUS_FAILED Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to retrieve service status for %1.  Windows error code %2.
.
MessageId=+1 SymbolicName=EMS_CC_SERVICE_FAILED_TO_GET_CONFG Severity=ErrWarn Facility=ITF
Language=English
EMS Command and Control - Unable to retrieve the list of managed services from configuration.
.
;
;#endif // INC_CCMSGS
