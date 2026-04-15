;#ifndef INC_OMMSGS
;#define INC_OMMSGS
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
	Alarm=0x3
)

FacilityNames=
( 
	System=0x0
	Runtime=0x2
	Stubs=0x3
	ITF=0x4
)

MessageId=0xF200 SymbolicName=EMS_OM_BASE_CODE Facility=ITF
Language=English
EMS Orbit Manager Error
.
MessageId=+1 SymbolicName=EMS_OM_SERVICE_START Severity=Success Facility=ITF
Language=English
EMS Orbit Manager Service Started
.
MessageId=+1 SymbolicName=EMS_OM_SERVICE_STOP Severity=Success Facility=ITF
Language=English
EMS Orbit Manager Service Stopped
.
MessageId=+1 SymbolicName=EMS_OM_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager Exception thrown: %1
.
MessageId=+1 SymbolicName=EMS_OM_TRACER Severity=Success Facility=ITF
Language=English
EMS Orbit Manager - Trace %1.
.
MessageId=+1 SymbolicName=EMS_OM_EXCEPTION_TRACE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Exception thrown: File: %1 Line: %2 hr = %3
.
MessageId=+1 SymbolicName=EMS_OM_CONFIGITEM_NOTFOUND Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Unable to find config item Group: %1 GroupID: %2 Key: %3.
.
MessageId=+1 SymbolicName=EMS_OM_GETTING_GLO_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager is retrieving ephemeris for Glonass satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GOT_GLO_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager retrieved ephemeris for (%1) Glonass satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GETTING_GAL_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager is retrieving ephemeris for Galileo satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GETTING_BDS_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager is retrieving ephemeris for Beidou satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GOT_GAL_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager retrieved ephemeris for (%1) Galileo satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GOT_BDS_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager retrieved ephemeris for (%1) Beidou satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GETTING_GPS_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager is retrieving ephemeris for GPS satellites.
.
MessageId=+1 SymbolicName=EMS_OM_GOT_GPS_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager retrieved ephemeris for (%1) GPS satellites.
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_NOT_CURRENT Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Orbit vector for satellite %1 is older than 2 days.
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_NOT_AVAILABLE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) is not available.
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_NOT_UPDATED Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) could not be updated.
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_LOADED Severity=Success Facility=ITF
Language=English
EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) has been loaded by the system, Epoch time = %3.
.
MessageId=+1 SymbolicName=EMS_OM_JAVAD_CONNECT_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Orbit Manager - Connection to Javad GNSS failed.
.
MessageId=+1 SymbolicName=EMS_OM_GNSS_INITIALIZATION_FAILED Severity=Alarm Facility=ITF
Language=English
EMS Orbit Manager - Initialization of the GNSS failed.
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_NOT_LOADED Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) was not loaded by the system.
.
MessageId=+1 SymbolicName=EMS_OM_INIT_JAVAD_EPHEM Severity=Success Facility=ITF
Language=English
EMS Orbit Manager is sending a request to Javad GNSS to output all ephemeris.
.
MessageId=+1 SymbolicName=EMS_OM_DUPL_ORBIT_VECTOR_POSVELERR Severity=Success Facility=ITF
Language=English
Duplicate orbit vector received[satID=%1, source=%2, dTimeDiff=%3, b%4Hours=%5, bValid=%6, dPosErr=%7:dVelErr=%8, bPosVelBelowThresholds=%9, bInstallNewTLE=%10] 
.
MessageId=+1 SymbolicName=EMS_OM_EPHEMERIS_SERIALIZATION_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager was unable to serialize the ephemeris. Error:  %1.
.
MessageId=+1 SymbolicName=EMS_OM_ORBITEXT_SERIALIZATION_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager was unable to serialize the orbit text. Error:  %1.
.
MessageId=+1 SymbolicName=EMS_OM_NEW_EPHEMERIS_UPDATE Severity=Success Facility=ITF
Language=English
EMS Orbit Manager received new ephemeris data.
.
MessageId=+1 SymbolicName=EMS_OM_NEW_TLE_UPDATE Severity=Success Facility=ITF
Language=English
EMS Orbit Manager received new TLE data.
.
MessageId=+1 SymbolicName=EMS_OM_EPHEMERIS_UPDATE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager failed to process the received ephemeris data. Error:  %1.
.
MessageId=+1 SymbolicName=EMS_OM_TLE_UPDATE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager failed to process the received TLE data. Error:  %1.
.
MessageId=+1 SymbolicName=EMS_OM_ERR_ORBIT_SOURCE_PRIORITY_SATISFY Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager reports orbit priority value does satisfy %11 [satID=%1, source=%2] 
.
MessageId=+1 SymbolicName=EMS_OM_ERR_ORBIT_SOURCE_PRIORITY_NOT_SATISFY Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager reports orbit priority value does not satisfy %11 [satID=%1, source=%2] 
.
MessageId=+1 SymbolicName=EMS_OM_ORBIT_VECTOR_REJECTED Severity=Success Facility=ITF
Language=English
EMS Orbit Manager rejected orbit vector[satID=%1, source=%2, dTimeDiff=%3, b%4Hours=%5, bValid=%6, dPosErr=%7:dVelErr=%8, bPosVelBelowThresholds=%9, bInstallNewTLE=%10] 
.
MessageId=+1 SymbolicName=EMS_OM_CANT_FIND_SATELLITE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Can't find satellite in config[satID=%1] 
.
MessageId=+1 SymbolicName=EMS_OM_TOO_MANY_SATELLITES Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager - Max number of satellites exceeded(%1).
.
MessageId=+1 SymbolicName=EMS_OM_NEW_MCC_TLE_UPDATE Severity=Success Facility=ITF
Language=English
EMS Orbit Manager received new MCC TLE data.
.
MessageId=+1 SymbolicName=EMS_OM_MCC_TLE_UPDATE_FAILURE Severity=ErrWarn Facility=ITF
Language=English
EMS Orbit Manager failed to process the received MCC TLE data. Error:  %1.
.
;
;#endif // INC_OMMSGS
