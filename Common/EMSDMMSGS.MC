;#ifndef INC_DMMSGS
;#define INC_DMMSGS
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

MessageId=0xC300 SymbolicName=EMS_DM_BASE_CODE Facility=ITF
Language=English
EMS Data Manager Error
.
MessageId=+1 SymbolicName=EMS_DM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Data Manager Service Started
.
MessageId=+1 SymbolicName=EMS_DM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Data Manager Service Stopped
.
MessageId=+1 SymbolicName=EMS_DM_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_DM_FREESPACE_10 Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Free space available is within 10%% of configured minimum.
.
MessageId=+1 SymbolicName=EMS_DM_FREESPACE_5 Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Free space available is within 5%% of configured minimum.
.
MessageId=+1 SymbolicName=EMS_DM_FREESPACE_1 Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Free space available is within 1%% of configured minimum.
.
MessageId=+1 SymbolicName=EMS_DM_FREESPACE_0 Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Free space available is below configured minimum.
.
MessageId=+1 SymbolicName=EMS_DM_ARCHIVING Severity=Success Facility=ITF
Language=English
EMS Data Manager - Archiving Data Sources.
.
MessageId=+1 SymbolicName=EMS_DM_ARCHIVE_SOURCE Severity=Success Facility=ITF
Language=English
EMS Data Manager - Archiving Data Source: %1.
.
MessageId=+1 SymbolicName=EMS_DM_ARCHIVE_SOURCE_FINISH Severity=Success Facility=ITF
Language=English
EMS Data Manager - Finished Archiving Data Source: %1.
.
MessageId=+1 SymbolicName=EMS_DM_FILEOPEN_SYSERROR Severity=Success Facility=ITF
Language=English
EMS Data Manager - Failed to open file %1 with system error %2.
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_UNKNOWN Severity=Success Facility=ITF
Language=English
Unknown Database Table
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_ANTENNA Severity=Success Facility=ITF
Language=English
Antenna Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_CALIB406 Severity=Success Facility=ITF
Language=English
Calib 406 Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_CALIBCBC Severity=Success Facility=ITF
Language=English
Calib CBC Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_CALIBCBC_STATS Severity=Success Facility=ITF
Language=English
Calib CBC Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_CBC Severity=Success Facility=ITF
Language=English
CBC Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_COLLECTOR Severity=Success Facility=ITF
Language=English
Collector Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_COMB406 Severity=Success Facility=ITF
Language=English
Combine 406 Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_COMB406_STATS Severity=Success Facility=ITF
Language=English
Combine 406 Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_COMMS_STATS Severity=Success Facility=ITF
Language=English
Comms Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_CONFIG Severity=Success Facility=ITF
Language=English
Config Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_GEO_CALIB406_STATS Severity=Success Facility=ITF
Language=English
GEO Calib 406 Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_GEO_STATS Severity=Success Facility=ITF
Language=English
GEO Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_LEO_CALIB406_STATS Severity=Success Facility=ITF
Language=English
LEO Calib 406 Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_LOCATE Severity=Success Facility=ITF
Language=English
Locate Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_LOCATE_STATS Severity=Success Facility=ITF
Language=English
Locate Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_LOG Severity=Success Facility=ITF
Language=English
Log Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_ORBIT Severity=Success Facility=ITF
Language=English
Orbit Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_ORBIT_STATS Severity=Success Facility=ITF
Language=English
Orbit Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_PASS_STATS Severity=Success Facility=ITF
Language=English
Pass Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_RESIDUAL Severity=Success Facility=ITF
Language=English
Residual Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARP_CALIB Severity=Success Facility=ITF
Language=English
SARP Calib Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARP_CALIB_STATS Severity=Success Facility=ITF
Language=English
SARP Calib Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARP Severity=Success Facility=ITF
Language=English
SARP Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARR_CALIB Severity=Success Facility=ITF
Language=English
SARR Calib Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARR_CALIB_STATS Severity=Success Facility=ITF
Language=English
SARR Calib Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SARR Severity=Success Facility=ITF
Language=English
SARR Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SAT_TRACK Severity=Success Facility=ITF
Language=English
Pass Schedule Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SENSOR Severity=Success Facility=ITF
Language=English
Sensor Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_SPECTRUM Severity=Success Facility=ITF
Language=English
Spectrum Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_STAT_SUMMARY Severity=Success Facility=ITF
Language=English
Pass Summary Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_WIDEBAND_STATS Severity=Success Facility=ITF
Language=English
Wideband Stats
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_AUDIO Severity=Success Facility=ITF
Language=English
Audio Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_MANOEUVRE Severity=Success Facility=ITF
Language=English
Manoeuvre Data
.
MessageId=+1 SymbolicName=EMS_DM_EXCEPTION_TRACE Severity=ErrWarn Facility=ITF
Language=English
EMS Data Manager - Exception thrown: File: %1 Line: %2 hr = %3
.
MessageId=+1 SymbolicName=EMS_DM_DISKSPACECHECKERR Severity=ErrWarn Facility=ITF
Language=English
Unable to check available disk space. Error code=%1.
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_ABL_DATA Severity=Success Facility=ITF
Language=English
ABL Data
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_HEALTH_DETECTIONS Severity=Success Facility=ITF
Language=English
Health Detections
.
MessageId=+1 SymbolicName=EMS_DM_RECTYPE_HEALTH_STATUS Severity=Success Facility=ITF
Language=English
Health Status
.
;
;#endif // INC_DMMSGS
