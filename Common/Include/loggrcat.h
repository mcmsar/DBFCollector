/********************************************************************
*	Module:			loggrcat.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS LeoLut600 Logger Categories
*
*
* WARNING!!!  The identifiers in this file are hard-coded.  They are NOT to be changed
*
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*								All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/05/21		rvw		start
		
********************************************************************/
#ifndef INC_LOGGRCAT
#define INC_LOGGRCAT

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: EMSLOGCAT_Pipeline
//
// MessageText:
//
// Pipeline
//
#define EMSLOGCAT_Pipeline               ((EMS_RESULT)0x00000001L)

#define EMSLOGCAT_MIN		EMSLOGCAT_Pipeline

//
// MessageId: EMSLOGCAT_Logger
//
// MessageText:
//
// Logger
//
#define EMSLOGCAT_Logger                 ((EMS_RESULT)0x00000002L)

//
// MessageId: EMSLOGCAT_Journal
//
// MessageText:
//
// DBJournal
//
#define EMSLOGCAT_Journal                ((EMS_RESULT)0x00000003L)

//
// MessageId: EMSLOGCAT_Collector
//
// MessageText:
//
// Collector
//
#define EMSLOGCAT_Collector              ((EMS_RESULT)0x00000004L)

//
// MessageId: EMSLOGCAT_Calib406
//
// MessageText:
//
// Calibrate406
//
#define EMSLOGCAT_Calib406               ((EMS_RESULT)0x00000005L)

//
// MessageId: EMSLOGCAT_CalibCBC
//
// MessageText:
//
// CalibrateCBC
//
#define EMSLOGCAT_CalibCBC               ((EMS_RESULT)0x00000006L)

//
// MessageId: EMSLOGCAT_Wideband
//
// MessageText:
//
// Wideband
//
#define EMSLOGCAT_Wideband               ((EMS_RESULT)0x00000007L)

//
// MessageId: EMSLOGCAT_Locate
//
// MessageText:
//
// Locate
//
#define EMSLOGCAT_Locate                 ((EMS_RESULT)0x00000008L)

//
// MessageId: EMSLOGCAT_Antenna
//
// MessageText:
//
// Antenna
//
#define EMSLOGCAT_Antenna                ((EMS_RESULT)0x00000009L)

//
// MessageId: EMSLOGCAT_OrbitDet
//
// MessageText:
//
// OrbitDet
//
#define EMSLOGCAT_OrbitDet               ((EMS_RESULT)0x0000000AL)

//
// MessageId: EMSLOGCAT_SitGen
//
// MessageText:
//
// SitGen
//
#define EMSLOGCAT_SitGen                 ((EMS_RESULT)0x0000000BL)

//
// MessageId: EMSLOGCAT_Comms
//
// MessageText:
//
// Comms
//
#define EMSLOGCAT_Comms                  ((EMS_RESULT)0x0000000CL)

//
// MessageId: EMSLOGCAT_Master
//
// MessageText:
//
// Master
//
#define EMSLOGCAT_Master                 ((EMS_RESULT)0x0000000DL)

//
// MessageId: EMSLOGCAT_Monitor
//
// MessageText:
//
// Monitor
//
#define EMSLOGCAT_Monitor                ((EMS_RESULT)0x0000000EL)

//
// MessageId: EMSLOGCAT_SysTest
//
// MessageText:
//
// SysTest
//
#define EMSLOGCAT_SysTest                ((EMS_RESULT)0x0000000FL)

//
// MessageId: EMSLOGCAT_Status
//
// MessageText:
//
// Status
//
#define EMSLOGCAT_Status                 ((EMS_RESULT)0x00000010L)

//
// MessageId: EMSLOGCAT_Audio
//
// MessageText:
//
// Status
//
#define EMSLOGCAT_Audio                  ((EMS_RESULT)0x00000011L)

//
// MessageId: EMSLOGCAT_Combine406
//
// MessageText:
//
// Status
//
#define EMSLOGCAT_Combine406             ((EMS_RESULT)0x00000012L)

//
// MessageId: EMSLOGCAT_TCal
//
// MessageText:
//
// Status
//
#define EMSLOGCAT_TCal                   ((EMS_RESULT)0x00000013L)

//
// MessageId: EMSLOGCAT_Database
//
// MessageText:
//
// Database
//
#define EMSLOGCAT_Database               ((EMS_RESULT)0x00000014L)

//
// MessageId: EMSLOGCAT_Gateway
//
// MessageText:
//
// Gateway
//
#define EMSLOGCAT_Gateway                ((EMS_RESULT)0x00000015L)

//
// MessageId: EMSLOGCAT_DataAcquisition
//
// MessageText:
//
// DataAcquisition
//
#define EMSLOGCAT_DataAcquisition        ((EMS_RESULT)0x00000016L)

//
// MessageId: EMSLOGCAT_Security
//
// MessageText:
//
// Security
//
#define EMSLOGCAT_Security               ((EMS_RESULT)0x00000017L)

//
// MessageId: EMSLOGCAT_LPC
//
// MessageText:
//
// LocationProcessorController
//
#define EMSLOGCAT_LPC                    ((EMS_RESULT)0x00000018L)

//
// MessageId: EMSLOGCAT_DataTransfer
//
// MessageText:
//
// DataTransfer
//
#define EMSLOGCAT_DataTransfer           ((EMS_RESULT)0x00000019L)

//
// MessageId: EMSLOGCAT_CommandControl
//
// MessageText:
//
// CommandAndControl
//
#define EMSLOGCAT_CommandControl         ((EMS_RESULT)0x0000001AL)

//
// MessageId: EMSLOGCAT_LUTMonitor
//
// MessageText:
//
// LUTMonitor
//
#define EMSLOGCAT_LUTMonitor             ((EMS_RESULT)0x0000001BL)

//
// MessageId: EMSLOGCAT_MTL
//
// MessageText:
//
// Message Translation Layer
//
#define EMSLOGCAT_MTL                    ((EMS_RESULT)0x0000001CL)

//
// MessageId: EMSLOGCAT_DAL
//
// MessageText:
//
// Data Access Layer
//
#define EMSLOGCAT_DAL                    ((EMS_RESULT)0x0000001DL)

//
// MessageId: EMSLOGCAT_AlertGen
//
// MessageText:
//
// AlertGeneration
//
#define EMSLOGCAT_AlertGen               ((EMS_RESULT)0x0000001EL)

//
// MessageId: EMSLOGCAT_DataManager
//
// MessageText:
//
// DataManager
//
#define EMSLOGCAT_DataManager            ((EMS_RESULT)0x0000001FL)

//
// MessageId: EMSLOGCAT_CM
//
// MessageText:
//
// Configuration Manager
//
#define EMSLOGCAT_CM                     ((EMS_RESULT)0x00000020L)

//
// MessageId: EMSLOGCAT_Sockets
//
// MessageText:
//
// Sockets
//
#define EMSLOGCAT_Sockets                ((EMS_RESULT)0x00000021L)

//
// MessageId: EMSLOGCAT_TLEServer
//
// MessageText:
//
// TLEServer
//
#define EMSLOGCAT_TLEServer              ((EMS_RESULT)0x00000022L)

//
// MessageId: EMSLOGCAT_CalibrationMonitor
//
// MessageText:
//
// CalibrationMonitor
//
#define EMSLOGCAT_CalibrationMonitor     ((EMS_RESULT)0x00000023L)

//
// MessageId: EMSLOGCAT_Unknown
//
// MessageText:
//
// Unknown
//
#define EMSLOGCAT_Unknown                ((EMS_RESULT)0x00000025L)

//
// MessageId: EMSLOGCAT_LocnAnalysis
//
// MessageText:
//
// Location Analysis
//
#define EMSLOGCAT_LocnAnalysis           ((EMS_RESULT)0x00000026L)

//
// MessageId: EMSLOGCAT_StormMgr
//
// MessageText:
//
// StormManager
//
#define EMSLOGCAT_StormMgr               ((EMS_RESULT)0x00000027L)

//
// MessageId: EMSLOGCAT_NetConnMgr
//
// MessageText:
//
// NetConnectionManager
//
#define EMSLOGCAT_NetConnMgr             ((EMS_RESULT)0x00000028L)

//
// MessageId: EMSLOGCAT_WSHost
//
// MessageText:
//
// WebServiceHost
//
#define EMSLOGCAT_WSHost                 ((EMS_RESULT)0x00000029L)

//
// MessageId: EMSLOGCAT_FPWSHost
//
// MessageText:
//
// Front End Processor WebServiceHost
//
#define EMSLOGCAT_FPWSHost               ((EMS_RESULT)0x0000002AL)

//
// MessageId: EMSLOGCAT_DCWSHost
//
// MessageText:
//
// Data Collector WebServiceHost
//
#define EMSLOGCAT_DCWSHost               ((EMS_RESULT)0x0000002BL)

//
// MessageId: EMSLOGCAT_PassScheduler
//
// MessageText:
//
// Pass Scheduler
//
#define EMSLOGCAT_PassScheduler          ((EMS_RESULT)0x0000002CL)

//
// MessageId: EMSLOGCAT_PassSchedulerService
//
// MessageText:
//
// Pass Scheduler Service
//
#define EMSLOGCAT_PassSchedulerService   ((EMS_RESULT)0x0000002DL)

//
// MessageId: EMSLOGCAT_OrbitDistributor
//
// MessageText:
//
// Orbit Distributor
//
#define EMSLOGCAT_OrbitDistributor       ((EMS_RESULT)0x0000002EL)

//
// MessageId: EMSLOGCAT_SignalConditioner
//
// MessageText:
//
// Signal Conditioner
//
#define EMSLOGCAT_SignalConditioner      ((EMS_RESULT)0x0000002FL)

//
// MessageId: EMSLOGCAT_MIServer
//
// MessageText:
//
// Message Integration
//
#define EMSLOGCAT_MIServer               ((EMS_RESULT)0x00000030L)

//
// MessageId: EMSLOGCAT_SocketServer
//
// MessageText:
//
// Socket Server
//
#define EMSLOGCAT_SocketServer           ((EMS_RESULT)0x00000031L)

//
// MessageId: EMSLOGCAT_Demodulator
//
// MessageText:
//
// Demodulator
//
#define EMSLOGCAT_Demodulator            ((EMS_RESULT)0x00000032L)

//
// MessageId: EMSLOGCAT_Downconverter
//
// MessageText:
//
// Downconverter
//
#define EMSLOGCAT_Downconverter          ((EMS_RESULT)0x00000033L)

//
// MessageId: EMSLOGCAT_FFT
//
// MessageText:
//
// FFT
//
#define EMSLOGCAT_FFT                    ((EMS_RESULT)0x00000034L)

//
// MessageId: EMSLOGCAT_UnmodDownconverter
//
// MessageText:
//
// Unmodulated Downconverter
//
#define EMSLOGCAT_UnmodDownconverter     ((EMS_RESULT)0x00000035L)

//
// MessageId: EMSLOGCAT_BeaconDecoder
//
// MessageText:
//
// Beacon Decoder
//
#define EMSLOGCAT_BeaconDecoder          ((EMS_RESULT)0x00000036L)

//
// MessageId: EMSLOGCAT_BeaconDetector
//
// MessageText:
//
// Beacon Detector
//
#define EMSLOGCAT_BeaconDetector         ((EMS_RESULT)0x00000037L)

//
// MessageId: EMSLOGCAT_SARRProcessor
//
// MessageText:
//
// SARR Processor
//
#define EMSLOGCAT_SARRProcessor          ((EMS_RESULT)0x00000038L)

//
// MessageId: EMSLOGCAT_SpectrumProcessor
//
// MessageText:
//
// Spectrum Processor
//
#define EMSLOGCAT_SpectrumProcessor      ((EMS_RESULT)0x00000039L)

//
// MessageId: EMSLOGCAT_SPServer
//
// MessageText:
//
// Signal Processor Server
//
#define EMSLOGCAT_SPServer               ((EMS_RESULT)0x0000003AL)

//
// MessageId: EMSLOGCAT_MsgConversion
//
// MessageText:
//
// Message Conversion
//
#define EMSLOGCAT_MsgConversion          ((EMS_RESULT)0x0000003BL)

//
// MessageId: EMSLOGCAT_MsgCorrelation
//
// MessageText:
//
// Message Correlation
//
#define EMSLOGCAT_MsgCorrelation         ((EMS_RESULT)0x0000003CL)

//
// MessageId: EMSLOGCAT_MsgIntegration
//
// MessageText:
//
// Message Integration
//
#define EMSLOGCAT_MsgIntegration         ((EMS_RESULT)0x0000003DL)

//
// MessageId: EMSLOGCAT_SARRConversion
//
// MessageText:
//
// SARR Conversion
//
#define EMSLOGCAT_SARRConversion         ((EMS_RESULT)0x0000003EL)

//
// MessageId: EMSLOGCAT_DataXmitter
//
// MessageText:
//
// Data Transmitter
//
#define EMSLOGCAT_DataXmitter            ((EMS_RESULT)0x0000003FL)

//
// MessageId: EMSLOGCAT_FPOrbital
//
// MessageText:
//
// FP Orbital
//
#define EMSLOGCAT_FPOrbital              ((EMS_RESULT)0x00000040L)

//
// MessageId: EMSLOGCAT_FPWS
//
// MessageText:
//
// FP Web Service
//
#define EMSLOGCAT_FPWS                   ((EMS_RESULT)0x00000041L)

//
// MessageId: EMSLOGCAT_DCWS
//
// MessageText:
//
// Data Collector Web Service
//
#define EMSLOGCAT_DCWS                   ((EMS_RESULT)0x00000042L)

//
// MessageId: EMSLOGCAT_WaveReceiver
//
// MessageText:
//
// Wave Receiver
//
#define EMSLOGCAT_WaveReceiver           ((EMS_RESULT)0x00000043L)

//
// MessageId: EMSLOGCAT_DBResource
//
// MessageText:
//
// Database Resource
//
#define EMSLOGCAT_DBResource             ((EMS_RESULT)0x00000044L)

//
// MessageId: EMSLOGCAT_BREngine
//
// MessageText:
//
// Beacon Registry Engine
//
#define EMSLOGCAT_BREngine               ((EMS_RESULT)0x00000045L)

//
// MessageId: EMSLOGCAT_BRWS
//
// MessageText:
//
// Beacon Registry Web Service
//
#define EMSLOGCAT_BRWS                   ((EMS_RESULT)0x00000046L)

//
// MessageId: EMSLOGCAT_BRWSHost
//
// MessageText:
//
// Beacon Registry Web Service Host
//
#define EMSLOGCAT_BRWSHost               ((EMS_RESULT)0x00000047L)

//
// MessageId: EMSLOGCAT_BRProxy
//
// MessageText:
//
// Beacon Registry Proxy
//
#define EMSLOGCAT_BRProxy                ((EMS_RESULT)0x00000048L)

//
// MessageId: EMSLOGCAT_BUSWS
//
// MessageText:
//
// Backup Server Web Service
//
#define EMSLOGCAT_BUSWS                  ((EMS_RESULT)0x00000049L)

//
// MessageId: EMSLOGCAT_BUSWSHost
//
// MessageText:
//
// Backup Server Web Service Host
//
#define EMSLOGCAT_BUSWSHost              ((EMS_RESULT)0x0000004AL)

//
// MessageId: EMSLOGCAT_BDWS
//
// MessageText:
//
// Beacon Decoder Web Service
//
#define EMSLOGCAT_BDWS                   ((EMS_RESULT)0x0000004BL)

//
// MessageId: EMSLOGCAT_BDWSHost
//
// MessageText:
//
// Beacon Decoder Web Service Host
//
#define EMSLOGCAT_BDWSHost               ((EMS_RESULT)0x0000004CL)

//
// MessageId: EMSLOGCAT_BDC
//
// MessageText:
//
// Beacon Decoder Client
//
#define EMSLOGCAT_BDC                    ((EMS_RESULT)0x0000004DL)

//
// MessageId: EMSLOGCAT_DSSEngine
//
// MessageText:
//
// Data Synch Engine
//
#define EMSLOGCAT_DSSEngine              ((EMS_RESULT)0x0000004EL)

//
// MessageId: EMSLOGCAT_DSSWS
//
// MessageText:
//
// Data Store Synch Web Service
//
#define EMSLOGCAT_DSSWS                  ((EMS_RESULT)0x0000004FL)

#define EMSLOGCAT_MAX		EMSLOGCAT_DSSWS
//
// At this point we run into the hard-coded range allocated for the message types
// These cannot change without re-compiling alot of code.
//
//
// MessageId: EMSLOGCAT_DSSWSHost
//
// MessageText:
//
// Data Store Synch Web Service Host
//
#define EMSLOGCAT_DSSWSHost              ((EMS_RESULT)0x00000060L)

#define EMSLOGCAT_MIN2		EMSLOGCAT_DSSWSHost

//
// MessageId: EMSLOGCAT_DSSProxy
//
// MessageText:
//
// Data Store Synch Proxy
//
#define EMSLOGCAT_DSSProxy               ((EMS_RESULT)0x00000061L)

//
// MessageId: EMSLOGCAT_BRDAccessor
//
// MessageText:
//
// Beacon Registry Data Accessor
//
#define EMSLOGCAT_BRDAccessor            ((EMS_RESULT)0x00000062L)

//
// MessageId: EMSLOGCAT_SQLDBAccessor
//
// MessageText:
//
// SQL Database Accessor
//
#define EMSLOGCAT_SQLDBAccessor          ((EMS_RESULT)0x00000063L)

//
// MessageId: EMSLOGCAT_ActiveBeaconService
//
// MessageText:
//
// Active Beacon Service
//
#define EMSLOGCAT_ActiveBeaconService    ((EMS_RESULT)0x00000064L)

//
// MessageId: EMSLOGCAT_ABLObject
//
// MessageText:
//
// Active Beacon Object
//
#define EMSLOGCAT_ABLObject              ((EMS_RESULT)0x00000065L)

//
// MessageId: EMSLOGCAT_BeaconSNMPAgent
//
// MessageText:
//
// Beacon SNMP Agent
//
#define EMSLOGCAT_BeaconSNMPAgent        ((EMS_RESULT)0x00000066L)

//
// MessageId: EMSLOGCAT_OCCAlertsDBAccessor
//
// MessageText:
//
// OCC Alerts DB Accessor
//
#define EMSLOGCAT_OCCAlertsDBAccessor    ((EMS_RESULT)0x00000067L)

//
// MessageId: EMSLOGCAT_BeaconDecoderEx
//
// MessageText:
//
// Beacon Decoder Extended
//
#define EMSLOGCAT_BeaconDecoderEx        ((EMS_RESULT)0x00000068L)

//
// MessageId: EMSLOGCAT_HealthMonitor
//
// MessageText:
//
// Health Monitor
//
#define EMSLOGCAT_HealthMonitor          ((EMS_RESULT)0x00000069L)

//
// MessageId: EMSLOGCAT_URLRetriever
//
// MessageText:
//
// URL Retriever
//
#define EMSLOGCAT_URLRetriever           ((EMS_RESULT)0x00000070L)

//
// MessageId: EMSLOGCAT_URcvProxy
//
// MessageText:
//
// URL Receiver Proxy
//
#define EMSLOGCAT_URcvProxy              ((EMS_RESULT)0x00000071L)

//
// MessageId: EMSLOGCAT_URcvWSHost
//
// MessageText:
//
// URL Receiver
//
#define EMSLOGCAT_URcvWSHost             ((EMS_RESULT)0x00000072L)

//
// MessageId: EMSLOGCAT_URcvWS
//
// MessageText:
//
// URL Receiver Web Service
//
#define EMSLOGCAT_URcvWS                 ((EMS_RESULT)0x00000073L)

//
// MessageId: EMSLOGCAT_URSarsatPlugin
//
// MessageText:
//
// URL Receiver Sarsat Plugin
//
#define EMSLOGCAT_URSarsatPlugin         ((EMS_RESULT)0x00000074L)

//
// MessageId: EMSLOGCAT_BeaconAdvisory
//
// MessageText:
//
// Beacon Advisory Service
//
#define EMSLOGCAT_BeaconAdvisory         ((EMS_RESULT)0x00000075L)

//
// MessageId: EMSLOGCAT_JavadInterface
//
// MessageText:
//
// Javad Interface
//
#define EMSLOGCAT_JavadInterface         ((EMS_RESULT)0x00000076L)

//
// MessageId: EMSLOGCAT_OrbitManager
//
// MessageText:
//
// Orbit Manager Service
//
#define EMSLOGCAT_OrbitManager           ((EMS_RESULT)0x00000077L)

//
// MessageId: EMSLOGCAT_LogAggregator
//
// MessageText:
//
// Log Aggregator Service
//
#define EMSLOGCAT_LogAggregator          ((EMS_RESULT)0x00000078L)

//
// MessageId: EMSLOGCAT_OrbitalController
//
// MessageText:
//
// Orbital Controller Service
//
#define EMSLOGCAT_OrbitalController      ((EMS_RESULT)0x00000079L)

//
// MessageId: EMSLOGCAT_PSWS
//
// MessageText:
//
// Pass Scheduler Web Service
//
#define EMSLOGCAT_PSWS                   ((EMS_RESULT)0x0000007AL)

//
// MessageId: EMSLOGCAT_OrbitalAntenna
//
// MessageText:
//
// Orbital Antenna Service
//
#define EMSLOGCAT_OrbitalAntenna         ((EMS_RESULT)0x00000080L)

//
// MessageId: EMSLOGCAT_MTLWS
//
// MessageText:
//
// MTL Web Service
//
#define EMSLOGCAT_MTLWS                  ((EMS_RESULT)0x00000081L)

//
// MessageId: EMSLOGCAT_MCCIn
//
// MessageText:
//
// MCC In Service
//
#define EMSLOGCAT_MCCIn                  ((EMS_RESULT)0x00000082L)

//
// MessageId: EMSLOGCAT_MCCOut
//
// MessageText:
//
// MCC Out Service
//
#define EMSLOGCAT_MCCOut                 ((EMS_RESULT)0x00000083L)

//
// MessageId: EMSLOGCAT_TOAFOA
//
// MessageText:
//
// TOA FOA Service
//
#define EMSLOGCAT_TOAFOA                 ((EMS_RESULT)0x00000084L)

//
// MessageId: EMSLOGCAT_MEOMonitorControl
//
// MessageText:
//
// MEO Monitor Web Service
//
#define EMSLOGCAT_MEOMonitorControl      ((EMS_RESULT)0x00000085L)

//
// MessageId: EMSLOGCAT_MEOTaskScheduler
//
// MessageText:
//
// MEO Control Web Service
//
#define EMSLOGCAT_MEOTaskScheduler       ((EMS_RESULT)0x00000086L)

//
// MessageId: EMSLOGCAT_MEOTrackModeCtrl
//
// MessageText:
//
// MEO Track Mode Control Service
//
#define EMSLOGCAT_MEOTrackModeCtrl       ((EMS_RESULT)0x00000087L)

//
// MessageId: EMSLOGCAT_MCPFTPOut
//
// MessageText:
//
// MCPFTP Output Service
//
#define EMSLOGCAT_MCPFTPOut              ((EMS_RESULT)0x00000088L)

//
// MessageId: EMSLOGCAT_StatusMonitor
//
// MessageText:
//
// Status Monitor Service
//
#define EMSLOGCAT_StatusMonitor          ((EMS_RESULT)0x00000089L)

//
// MessageId: EMSLOGCAT_PwdManagerWeb
//
// MessageText:
//
// Password Manager Web
//
#define EMSLOGCAT_PwdManagerWeb          ((EMS_RESULT)0x0000008AL)

//
// MessageId: EMSLOGCAT_PipeMQBridge
//
// MessageText:
//
// Pipeline Message Queue Bridge
//
#define EMSLOGCAT_PipeMQBridge           ((EMS_RESULT)0x0000008BL)

//
// MessageId: EMSLOGCAT_TrackingScheduler
//
// MessageText:
//
// Tracking Scheduler Service
//
#define EMSLOGCAT_TrackingScheduler      ((EMS_RESULT)0x0000008CL)

#define EMSLOGCAT_MAX2		EMSLOGCAT_TrackingScheduler
#define EMSLOGCAT_VALID(cat)	((cat>= EMSLOGCAT_MIN && cat<=EMSLOGCAT_MAX) || (cat>= EMSLOGCAT_MIN2 && cat<=EMSLOGCAT_MAX2))


// MessageId 0x50 is the start of the message type values
// These CANNOT be changed so new identifiers have to skip over them


//
// MessageId: EMSLOGMSGTYPESTR_INFO
//
// MessageText:
//
// Info
//
#define EMSLOGMSGTYPESTR_INFO            ((EMS_RESULT)0x00000050L)

#define EMSLOGMSGTYPESTR_MIN		EMSLOGMSGTYPESTR_INFO

//
// MessageId: EMSLOGMSGTYPESTR_STATUS
//
// MessageText:
//
// Status
//
#define EMSLOGMSGTYPESTR_STATUS          ((EMS_RESULT)0x00000051L)

//
// MessageId: EMSLOGMSGTYPESTR_MORESTATUS
//
// MessageText:
//
// Status
//
#define EMSLOGMSGTYPESTR_MORESTATUS      ((EMS_RESULT)0x00000052L)

//
// MessageId: EMSLOGMSGTYPESTR_STARTUP
//
// MessageText:
//
// Startup
//
#define EMSLOGMSGTYPESTR_STARTUP         ((EMS_RESULT)0x00000053L)

//
// MessageId: EMSLOGMSGTYPESTR_ALARM
//
// MessageText:
//
// Alarm
//
#define EMSLOGMSGTYPESTR_ALARM           ((EMS_RESULT)0x00000054L)

//
// MessageId: EMSLOGMSGTYPESTR_FATAL
//
// MessageText:
//
// Fatal
//
#define EMSLOGMSGTYPESTR_FATAL           ((EMS_RESULT)0x00000055L)

//
// MessageId: EMSLOGMSGTYPESTR_WARNING
//
// MessageText:
//
// Warning
//
#define EMSLOGMSGTYPESTR_WARNING         ((EMS_RESULT)0x00000056L)

//
// MessageId: EMSLOGMSGTYPESTR_UNKNOWN
//
// MessageText:
//
// Unknown
//
#define EMSLOGMSGTYPESTR_UNKNOWN         ((EMS_RESULT)0x00000057L)

//
// MessageId: EMSLOGMSGTYPESTR_TRACE
//
// MessageText:
//
// Trace
//
#define EMSLOGMSGTYPESTR_TRACE           ((EMS_RESULT)0x00000058L)

//
// MessageId: EMSLOGMSGTYPESTR_DEBUG
//
// MessageText:
//
// Debug
//
#define EMSLOGMSGTYPESTR_DEBUG           ((EMS_RESULT)0x00000059L)

#define EMSLOGMSGTYPESTR_MAX		EMSLOGMSGTYPESTR_DEBUG

#define EMSLOGMSGTYPESTR_VALID(typ)	(typ>= EMSLOGMSGTYPESTR_MIN && typ<=EMSLOGMSGTYPESTR_MAX)

//
// MessageId: EMS_LOG_EXCEPTION
//
// MessageText:
//
// Exception thrown in file %1
//
#define EMS_LOG_EXCEPTION                ((EMS_RESULT)0x8004FF00L)

//
// MessageId: EMS_LOG_HR
//
// MessageText:
//
// Status code: %1
//
#define EMS_LOG_HR                       ((EMS_RESULT)0x8004FF01L)

//
// MessageId: EMS_EXCEPTION_TRACE
//
// MessageText:
//
// Exception %1 %2 (%5) in %3 at line: %4
//
#define EMS_EXCEPTION_TRACE              ((EMS_RESULT)0x0004FF02L)

//
// MessageId: EMS_LOG_UNKNOWNMESSAGE
//
// MessageText:
//
// Message ID: %1
//
#define EMS_LOG_UNKNOWNMESSAGE           ((EMS_RESULT)0x0004FF03L)

//
// MessageId: EMSLOGMSGTYPESTR_DEBUG_1
//
// MessageText:
//
// %1
//
#define EMSLOGMSGTYPESTR_DEBUG_1         ((EMS_RESULT)0x0004FF04L)

//
// MessageId: EMSLOGMSGTYPESTR_INFO_1
//
// MessageText:
//
// %1
//
#define EMSLOGMSGTYPESTR_INFO_1          ((EMS_RESULT)0x0004FF05L)

//
// MessageId: EMSLOGMSGTYPESTR_WARNING_1
//
// MessageText:
//
// %1
//
#define EMSLOGMSGTYPESTR_WARNING_1       ((EMS_RESULT)0x8004FF06L)

//
// MessageId: EMSLOGMSGTYPESTR_ALARM_1
//
// MessageText:
//
// %1
//
#define EMSLOGMSGTYPESTR_ALARM_1         ((EMS_RESULT)0x8004FF07L)

#endif // INC_LOGGRCAT

