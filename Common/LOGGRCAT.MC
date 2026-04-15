;/********************************************************************
;*	Module:			loggrcat.mc
;*	Process ID:
;*	S/W Platforms:
;*	H/W Platforms:
;*	Compiler:
;*	Description: 	Message File for EMS LeoLut600 Logger Categories
;*
;*
;* WARNING!!!  The identifiers in this file are hard-coded.  They are NOT to be changed
;*
;*
;*	Usage:
;*	Entry Point:
;*	Input Files:
;*	Output Files:
;*	Comments:
;*
;*********************************************************************
;*	              Copyright (c) 2001-2005 by EMS Technologies, Inc.,
;*								All rights reserved
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
;	0.0	01/05/21		rvw		start
;		
;********************************************************************/
;#ifndef INC_LOGGRCAT
;#define INC_LOGGRCAT
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

MessageId=0x1 SymbolicName=EMSLOGCAT_Pipeline
Language=English
Pipeline
.
;#define EMSLOGCAT_MIN		EMSLOGCAT_Pipeline
;
MessageId=0x2 SymbolicName=EMSLOGCAT_Logger
Language=English
Logger
.
MessageId=0x3 SymbolicName=EMSLOGCAT_Journal
Language=English
DBJournal
.
MessageId=0x4 SymbolicName=EMSLOGCAT_Collector
Language=English
Collector
.
MessageId=0x5 SymbolicName=EMSLOGCAT_Calib406
Language=English
Calibrate406
.
MessageId=0x6 SymbolicName=EMSLOGCAT_CalibCBC
Language=English
CalibrateCBC
.
MessageId=0x7 SymbolicName=EMSLOGCAT_Wideband
Language=English
Wideband
.
MessageId=0x8 SymbolicName=EMSLOGCAT_Locate
Language=English
Locate
.
MessageId=0x9 SymbolicName=EMSLOGCAT_Antenna
Language=English
Antenna
.
MessageId=0xA SymbolicName=EMSLOGCAT_OrbitDet
Language=English
OrbitDet
.
MessageId=0xB SymbolicName=EMSLOGCAT_SitGen
Language=English
SitGen
.
MessageId=0xC SymbolicName=EMSLOGCAT_Comms
Language=English
Comms
.
MessageId=0xD SymbolicName=EMSLOGCAT_Master
Language=English
Master
.
MessageId=0xE SymbolicName=EMSLOGCAT_Monitor
Language=English
Monitor
.
MessageId=0xF SymbolicName=EMSLOGCAT_SysTest
Language=English
SysTest
.
MessageId=0x10 SymbolicName=EMSLOGCAT_Status
Language=English
Status
.
MessageId=0x11 SymbolicName=EMSLOGCAT_Audio
Language=English
Status
.
MessageId=0x12 SymbolicName=EMSLOGCAT_Combine406
Language=English
Status
.
MessageId=0x13 SymbolicName=EMSLOGCAT_TCal
Language=English
Status
.
MessageId=0x14 SymbolicName=EMSLOGCAT_Database
Language=English
Database
.
MessageId=0x15 SymbolicName=EMSLOGCAT_Gateway
Language=English
Gateway
.
MessageId=0x16 SymbolicName=EMSLOGCAT_DataAcquisition
Language=English
DataAcquisition
.
MessageId=0x17 SymbolicName=EMSLOGCAT_Security
Language=English
Security
.
MessageId=0x18 SymbolicName=EMSLOGCAT_LPC
Language=English
LocationProcessorController
.
MessageId=0x19 SymbolicName=EMSLOGCAT_DataTransfer
Language=English
DataTransfer
.
MessageId=0x1a SymbolicName=EMSLOGCAT_CommandControl
Language=English
CommandAndControl
.
MessageId=0x1b SymbolicName=EMSLOGCAT_LUTMonitor
Language=English
LUTMonitor
.
MessageId=0x1c SymbolicName=EMSLOGCAT_MTL
Language=English
Message Translation Layer
.
MessageId=0x1d SymbolicName=EMSLOGCAT_DAL
Language=English
Data Access Layer
.
MessageId=0x1e SymbolicName=EMSLOGCAT_AlertGen
Language=English
AlertGeneration
.
MessageId=0x1f SymbolicName=EMSLOGCAT_DataManager
Language=English
DataManager
.
MessageId=0x20 SymbolicName=EMSLOGCAT_CM
Language=English
Configuration Manager
.
MessageId=0x21 SymbolicName=EMSLOGCAT_Sockets
Language=English
Sockets
.
MessageId=0x22 SymbolicName=EMSLOGCAT_TLEServer
Language=English
TLEServer
.
MessageId=0x23 SymbolicName=EMSLOGCAT_CalibrationMonitor
Language=English
CalibrationMonitor
.
MessageId=0x25 SymbolicName=EMSLOGCAT_Unknown
Language=English
Unknown
.
MessageId=0x26 SymbolicName=EMSLOGCAT_LocnAnalysis
Language=English
Location Analysis
.
MessageId=0x27 SymbolicName=EMSLOGCAT_StormMgr
Language=English
StormManager
.
MessageId=0x28 SymbolicName=EMSLOGCAT_NetConnMgr
Language=English
NetConnectionManager
.
MessageId=0x29 SymbolicName=EMSLOGCAT_WSHost
Language=English
WebServiceHost
.
MessageId=0x2A SymbolicName=EMSLOGCAT_FPWSHost
Language=English
Front End Processor WebServiceHost
.
MessageId=0x2B SymbolicName=EMSLOGCAT_DCWSHost
Language=English
Data Collector WebServiceHost
.
MessageId=0x2C SymbolicName=EMSLOGCAT_PassScheduler
Language=English
Pass Scheduler
.
MessageId=0x2D SymbolicName=EMSLOGCAT_PassSchedulerService
Language=English
Pass Scheduler Service
.
MessageId=0x2E SymbolicName=EMSLOGCAT_OrbitDistributor
Language=English
Orbit Distributor
.
MessageId=0x2F SymbolicName=EMSLOGCAT_SignalConditioner
Language=English
Signal Conditioner
.
MessageId=0x30 SymbolicName=EMSLOGCAT_MIServer
Language=English
Message Integration
.
MessageId=0x31 SymbolicName=EMSLOGCAT_SocketServer
Language=English
Socket Server
.
MessageId=0x32 SymbolicName=EMSLOGCAT_Demodulator
Language=English
Demodulator
.
MessageId=0x33 SymbolicName=EMSLOGCAT_Downconverter
Language=English
Downconverter
.
MessageId=0x34 SymbolicName=EMSLOGCAT_FFT
Language=English
FFT
.
MessageId=0x35 SymbolicName=EMSLOGCAT_UnmodDownconverter
Language=English
Unmodulated Downconverter
.
MessageId=0x36 SymbolicName=EMSLOGCAT_BeaconDecoder
Language=English
Beacon Decoder
.
MessageId=0x37 SymbolicName=EMSLOGCAT_BeaconDetector
Language=English
Beacon Detector
.
MessageId=0x38 SymbolicName=EMSLOGCAT_SARRProcessor
Language=English
SARR Processor
.
MessageId=0x39 SymbolicName=EMSLOGCAT_SpectrumProcessor
Language=English
Spectrum Processor
.
MessageId=0x3A SymbolicName=EMSLOGCAT_SPServer
Language=English
Signal Processor Server
.
MessageId=0x3B SymbolicName=EMSLOGCAT_MsgConversion
Language=English
Message Conversion
.
MessageId=0x3C SymbolicName=EMSLOGCAT_MsgCorrelation
Language=English
Message Correlation
.
MessageId=0x3D SymbolicName=EMSLOGCAT_MsgIntegration
Language=English
Message Integration
.
MessageId=0x3E SymbolicName=EMSLOGCAT_SARRConversion
Language=English
SARR Conversion
.
MessageId=0x3F SymbolicName=EMSLOGCAT_DataXmitter
Language=English
Data Transmitter
.
MessageId=0x40 SymbolicName=EMSLOGCAT_FPOrbital
Language=English
FP Orbital
.
MessageId=0x41 SymbolicName=EMSLOGCAT_FPWS
Language=English
FP Web Service
.
MessageId=0x42 SymbolicName=EMSLOGCAT_DCWS
Language=English
Data Collector Web Service
.
MessageId=0x43 SymbolicName=EMSLOGCAT_WaveReceiver
Language=English
Wave Receiver
.
MessageId=0x44 SymbolicName=EMSLOGCAT_DBResource
Language=English
Database Resource
.
MessageId=0x45 SymbolicName=EMSLOGCAT_BREngine
Language=English
Beacon Registry Engine
.
MessageId=0x46 SymbolicName=EMSLOGCAT_BRWS
Language=English
Beacon Registry Web Service
.
MessageId=0x47 SymbolicName=EMSLOGCAT_BRWSHost
Language=English
Beacon Registry Web Service Host
.
MessageId=0x48 SymbolicName=EMSLOGCAT_BRProxy
Language=English
Beacon Registry Proxy
.
MessageId=0x49 SymbolicName=EMSLOGCAT_BUSWS
Language=English
Backup Server Web Service
.
MessageId=0x4A SymbolicName=EMSLOGCAT_BUSWSHost
Language=English
Backup Server Web Service Host
.
MessageId=0x4B SymbolicName=EMSLOGCAT_BDWS
Language=English
Beacon Decoder Web Service
.
MessageId=0x4C SymbolicName=EMSLOGCAT_BDWSHost
Language=English
Beacon Decoder Web Service Host
.
MessageId=0x4D SymbolicName=EMSLOGCAT_BDC
Language=English
Beacon Decoder Client
.
MessageId=0x4E SymbolicName=EMSLOGCAT_DSSEngine
Language=English
Data Synch Engine
.
MessageId=0x4F SymbolicName=EMSLOGCAT_DSSWS
Language=English
Data Store Synch Web Service
.
;#define EMSLOGCAT_MAX		EMSLOGCAT_DSSWS
;//
;// At this point we run into the hard-coded range allocated for the message types
;// These cannot change without re-compiling alot of code.
;//
MessageId=0x60 SymbolicName=EMSLOGCAT_DSSWSHost
Language=English
Data Store Synch Web Service Host
.
;#define EMSLOGCAT_MIN2		EMSLOGCAT_DSSWSHost
;
MessageId=0x61 SymbolicName=EMSLOGCAT_DSSProxy
Language=English
Data Store Synch Proxy
.
MessageId=0x62 SymbolicName=EMSLOGCAT_BRDAccessor
Language=English
Beacon Registry Data Accessor
.
MessageId=0x63 SymbolicName=EMSLOGCAT_SQLDBAccessor
Language=English
SQL Database Accessor
.
MessageId=0x64 SymbolicName=EMSLOGCAT_ActiveBeaconService
Language=English
Active Beacon Service
.
MessageId=0x65 SymbolicName=EMSLOGCAT_ABLObject
Language=English
Active Beacon Object
.
MessageId=0x66 SymbolicName=EMSLOGCAT_BeaconSNMPAgent
Language=English
Beacon SNMP Agent
.
MessageId=0x67 SymbolicName=EMSLOGCAT_OCCAlertsDBAccessor
Language=English
OCC Alerts DB Accessor
.
MessageId=0x68 SymbolicName=EMSLOGCAT_BeaconDecoderEx
Language=English
Beacon Decoder Extended
.
MessageId=0x69 SymbolicName=EMSLOGCAT_HealthMonitor
Language=English
Health Monitor
.
MessageId=0x70 SymbolicName=EMSLOGCAT_URLRetriever
Language=English
URL Retriever
.
MessageId=0x71 SymbolicName=EMSLOGCAT_URcvProxy
Language=English
URL Receiver Proxy
.
MessageId=0x72 SymbolicName=EMSLOGCAT_URcvWSHost
Language=English
URL Receiver
.
MessageId=0x73 SymbolicName=EMSLOGCAT_URcvWS
Language=English
URL Receiver Web Service
.
MessageId=0x74 SymbolicName=EMSLOGCAT_URSarsatPlugin
Language=English
URL Receiver Sarsat Plugin
.
MessageId=0x75 SymbolicName=EMSLOGCAT_BeaconAdvisory
Language=English
Beacon Advisory Service
.
MessageId=0x76 SymbolicName=EMSLOGCAT_JavadInterface
Language=English
Javad Interface
.
MessageId=0x77 SymbolicName=EMSLOGCAT_OrbitManager
Language=English
Orbit Manager Service
.
MessageId=0x78 SymbolicName=EMSLOGCAT_LogAggregator
Language=English
Log Aggregator Service
.
MessageId=0x79 SymbolicName=EMSLOGCAT_OrbitalController
Language=English
Orbital Controller Service
.
MessageId=0x7A SymbolicName=EMSLOGCAT_PSWS
Language=English
Pass Scheduler Web Service
.
MessageId=0x80 SymbolicName=EMSLOGCAT_OrbitalAntenna
Language=English
Orbital Antenna Service
.
MessageId=0x81 SymbolicName=EMSLOGCAT_MTLWS
Language=English
MTL Web Service
.
MessageId=0x82 SymbolicName=EMSLOGCAT_MCCIn
Language=English
MCC In Service
.
MessageId=0x83 SymbolicName=EMSLOGCAT_MCCOut
Language=English
MCC Out Service
.
MessageId=0x84 SymbolicName=EMSLOGCAT_TOAFOA
Language=English
TOA FOA Service
.
MessageId=0x85 SymbolicName=EMSLOGCAT_MEOMonitorControl
Language=English
MEO Monitor Web Service
.
MessageId=0x86 SymbolicName=EMSLOGCAT_MEOTaskScheduler
Language=English
MEO Control Web Service
.
MessageId=0x87 SymbolicName=EMSLOGCAT_MEOTrackModeCtrl
Language=English
MEO Track Mode Control Service
.
MessageId=0x88 SymbolicName=EMSLOGCAT_MCPFTPOut
Language=English
MCPFTP Output Service
.
MessageId=0x89 SymbolicName=EMSLOGCAT_StatusMonitor
Language=English
Status Monitor Service
.
MessageId=0x8A SymbolicName=EMSLOGCAT_PwdManagerWeb
Language=English
Password Manager Web
.
MessageId=0x8B SymbolicName=EMSLOGCAT_PipeMQBridge
Language=English
Pipeline Message Queue Bridge
.
MessageId=0x8C SymbolicName=EMSLOGCAT_TrackingScheduler
Language=English
Tracking Scheduler Service
.
;#define EMSLOGCAT_MAX2		EMSLOGCAT_TrackingScheduler
;#define EMSLOGCAT_VALID(cat)	((cat>= EMSLOGCAT_MIN && cat<=EMSLOGCAT_MAX) || (cat>= EMSLOGCAT_MIN2 && cat<=EMSLOGCAT_MAX2))
;
;
;// MessageId 0x50 is the start of the message type values
;// These CANNOT be changed so new identifiers have to skip over them
;
;
MessageId=0x50 SymbolicName=EMSLOGMSGTYPESTR_INFO
Language=English
Info
.
;#define EMSLOGMSGTYPESTR_MIN		EMSLOGMSGTYPESTR_INFO
;
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_STATUS
Language=English
Status
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_MORESTATUS
Language=English
Status
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_STARTUP
Language=English
Startup
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_ALARM
Language=English
Alarm
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_FATAL
Language=English
Fatal
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_WARNING
Language=English
Warning
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_UNKNOWN
Language=English
Unknown
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_TRACE
Language=English
Trace
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_DEBUG
Language=English
Debug
.
;#define EMSLOGMSGTYPESTR_MAX		EMSLOGMSGTYPESTR_DEBUG
;
;#define EMSLOGMSGTYPESTR_VALID(typ)	(typ>= EMSLOGMSGTYPESTR_MIN && typ<=EMSLOGMSGTYPESTR_MAX)
;
MessageId=0xFF00 SymbolicName=EMS_LOG_EXCEPTION Severity=ErrWarn Facility=ITF
Language=English
Exception thrown in file %1
.
MessageId=+1 SymbolicName=EMS_LOG_HR Severity=ErrWarn Facility=ITF
Language=English
Status code: %1
.
MessageId=+1 SymbolicName=EMS_EXCEPTION_TRACE Severity=Success Facility=ITF
Language=English
Exception %1 %2 (%5) in %3 at line: %4
.
MessageId=+1 SymbolicName=EMS_LOG_UNKNOWNMESSAGE  Severity=Success Facility=ITF
Language=English
Message ID: %1
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_DEBUG_1  Severity=Success Facility=ITF
Language=English
%1
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_INFO_1  Severity=Success Facility=ITF
Language=English
%1
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_WARNING_1  Severity=ErrWarn Facility=ITF
Language=English
%1
.
MessageId=+1 SymbolicName=EMSLOGMSGTYPESTR_ALARM_1  Severity=ErrWarn Facility=ITF
Language=English
%1
.
;#endif // INC_LOGGRCAT
;
