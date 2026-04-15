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

/********************************************************************
*	Module:			Calib406Msg.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Calib406 Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_CALIB406MSG
#define INC_CALIB406MSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_CALIB406_BASE_CODE
//
// MessageText:
//
// EMS Calibrate406 Error
//
#define EMS_CALIB406_BASE_CODE           ((EMS_RESULT)0x8004A400L)

//
// MessageId: EMS_CALIB406_SERVICE_START
//
// MessageText:
//
// EMS Calibrate406 Service Started
//
#define EMS_CALIB406_SERVICE_START       ((EMS_RESULT)0x0004A401L)

//
// MessageId: EMS_CALIB406_SERVICE_FAILED
//
// MessageText:
//
// EMS Calibrate406 Service did not start due to error %1
//
#define EMS_CALIB406_SERVICE_FAILED      ((EMS_RESULT)0x8004A402L)

//
// MessageId: EMS_CALIB406_SERVICE_STOP
//
// MessageText:
//
// EMS Calibrate406 Service Stopped
//
#define EMS_CALIB406_SERVICE_STOP        ((EMS_RESULT)0x0004A403L)

//
// MessageId: EMS_CALIB406_ERROR
//
// MessageText:
//
// EMS Calibrate406 reports error %1.
//
#define EMS_CALIB406_ERROR               ((EMS_RESULT)0x8004A404L)

//
// MessageId: EMS_CALIB406_PRIORITY_CLASS
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetPriorityClass
//
#define EMS_CALIB406_PRIORITY_CLASS      ((EMS_RESULT)0x8004A405L)

//
// MessageId: EMS_CALIB406_THREAD_PRIORITY
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetThreadPriority
//
#define EMS_CALIB406_THREAD_PRIORITY     ((EMS_RESULT)0x8004A406L)

//
// MessageId: EMS_CALIB406_IDEAL_PROCESSOR
//
// MessageText:
//
// EMS Calibrate406 reports error %1 when calling SetThreadIdealProcessor
//
#define EMS_CALIB406_IDEAL_PROCESSOR     ((EMS_RESULT)0x8004A407L)

//
// MessageId: EMS_CALIB406_START_PASS
//
// MessageText:
//
// EMS Calibrate406 reports initialized pass for satellite %1
//
#define EMS_CALIB406_START_PASS          ((EMS_RESULT)0x0004A408L)

//
// MessageId: EMS_CALIB406_CALIBRATE_PASS
//
// MessageText:
//
// EMS Calibrate406 starting to calibrate pass for satellite %1
//
#define EMS_CALIB406_CALIBRATE_PASS      ((EMS_RESULT)0x0004A409L)

//
// MessageId: EMS_CALIB406_CALIBRATE_PASS_DONE
//
// MessageText:
//
// EMS Calibrate406 finished calibrating pass for satellite %1
//
#define EMS_CALIB406_CALIBRATE_PASS_DONE ((EMS_RESULT)0x0004A40AL)

//
// MessageId: EMS_CALIB406_TRACER
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( %1 )
//
#define EMS_CALIB406_TRACER              ((EMS_RESULT)0x0004A40BL)

//
// MessageId: EMS_CALIB406_HISTORY_RECS
//
// MessageText:
//
// EMS Calibrate406 read %1 history records.
//
#define EMS_CALIB406_HISTORY_RECS        ((EMS_RESULT)0x0004A40CL)

//
// MessageId: EMS_CALIB406_BUFFER_ADD
//
// MessageText:
//
// EMS Calibrate406 reports an error adding record %1 to the buffer.
//
#define EMS_CALIB406_BUFFER_ADD          ((EMS_RESULT)0x8004A40DL)

//
// MessageId: EMS_CALIB406_NEW_SARR_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 : New SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
//
#define EMS_CALIB406_NEW_SARR_OFFSETS    ((EMS_RESULT)0x0004A40EL)

//
// MessageId: EMS_CALIB406_CALC_SARR_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 : Insufficient Points for SARR Offsets ( SatID = %1, Freq=%2, Time=%3, Msgs=%4 ).
//
#define EMS_CALIB406_CALC_SARR_OFFSETS   ((EMS_RESULT)0x0004A40FL)

//
// MessageId: EMS_CALIB406_SARP_OFFSETS
//
// MessageText:
//
// EMS Calibrate406 has calculated new SARP Offsets ( SatID = %1, Freq=%2, Time=%3 ).
//
#define EMS_CALIB406_SARP_OFFSETS        ((EMS_RESULT)0x0004A410L)

//
// MessageId: EMS_CALIB406_ORBIT_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSOrbit.
//
#define EMS_CALIB406_ORBIT_ERROR         ((EMS_RESULT)0x8004A411L)

//
// MessageId: EMS_CALIB406_SAT_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSSatInfo.
//
#define EMS_CALIB406_SAT_INFO_ERROR      ((EMS_RESULT)0x8004A412L)

//
// MessageId: EMS_CALIB406_LUT_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSLutInfo.
//
#define EMS_CALIB406_LUT_INFO_ERROR      ((EMS_RESULT)0x8004A413L)

//
// MessageId: EMS_CALIB406_SITE_INFO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSLeo600SiteInfo
//
#define EMS_CALIB406_SITE_INFO_ERROR     ((EMS_RESULT)0x8004A414L)

//
// MessageId: EMS_CALIB406_REF_BEACON_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error %1 while trying to access IEMSRefBeacon.
//
#define EMS_CALIB406_REF_BEACON_ERROR    ((EMS_RESULT)0x8004A415L)

//
// MessageId: EMS_CALIB406_HISTORY_OUT
//
// MessageText:
//
// EMS Calibrate406 wrote %1 history records.
//
#define EMS_CALIB406_HISTORY_OUT         ((EMS_RESULT)0x0004A416L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIG
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=%2 )
//
#define EMS_CALIB406_TRACE_CONFIG        ((EMS_RESULT)0x0004A417L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIGYES
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=yes )
//
#define EMS_CALIB406_TRACE_CONFIGYES     ((EMS_RESULT)0x0004A418L)

//
// MessageId: EMS_CALIB406_TRACE_CONFIGNO
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( cfg: %1=no )
//
#define EMS_CALIB406_TRACE_CONFIGNO      ((EMS_RESULT)0x0004A419L)

//
// MessageId: EMS_CALIB406_TRACE_SORTEXCEPTION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( EX: Left=%1 ,Right=%2, Split=%3, Max=%4, Depth=%5 )
//
#define EMS_CALIB406_TRACE_SORTEXCEPTION ((EMS_RESULT)0x0004A41AL)

//
// MessageId: EMS_CALIB406_TRACE_SELNSORTEXCEPTION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( EX (SelectionSort): Left=%1 ,Right=%2 )
//
#define EMS_CALIB406_TRACE_SELNSORTEXCEPTION ((EMS_RESULT)0x0004A41BL)

//
// MessageId: EMS_CALIB406_TRACE_PARTITION
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Partition: Left=%1, Right=%2, Max=%3, *** )
//
#define EMS_CALIB406_TRACE_PARTITION     ((EMS_RESULT)0x0004A41CL)

//
// MessageId: EMS_CALIB406_TRACE_PARTITIONLTZERO
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Partition: Left=%d, Right=%d, Max=%d, Split < ZERO )
//
#define EMS_CALIB406_TRACE_PARTITIONLTZERO ((EMS_RESULT)0x0004A41DL)

//
// MessageId: EMS_CALIB406_TRACE_FORWARDINGCOUNT
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( Forwarding %1 records for Beacon %2 )
//
#define EMS_CALIB406_TRACE_FORWARDINGCOUNT ((EMS_RESULT)0x0004A41EL)

//
// MessageId: EMS_CALIB406_TRACE_SARRSARPADDED
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( SarrSarpRecords Added=%1 )
//
#define EMS_CALIB406_TRACE_SARRSARPADDED ((EMS_RESULT)0x0004A41FL)

//
// MessageId: EMS_CALIB406_TRACE_BEFORELOCK
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( before lock )
//
#define EMS_CALIB406_TRACE_BEFORELOCK    ((EMS_RESULT)0x0004A420L)

//
// MessageId: EMS_CALIB406_TRACE_AFTERLOCK
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( after lock )
//
#define EMS_CALIB406_TRACE_AFTERLOCK     ((EMS_RESULT)0x0004A421L)

//
// MessageId: EMS_CALIB406_TRACE_HISTORYREAD
//
// MessageText:
//
// EMS Calibrate406 Service Tracer ( SarrSarpHistory records read = %1 )
//
#define EMS_CALIB406_TRACE_HISTORYREAD   ((EMS_RESULT)0x0004A422L)

//
// MessageId: EMS_CALIB406_ROLLOVER_PERIOD_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving rollover period from configuration.  The configuration manager returned error %1.
//
#define EMS_CALIB406_ROLLOVER_PERIOD_GET_ERROR ((EMS_RESULT)0x0004A423L)

//
// MessageId: EMS_CALIB406_ROLLOVER_PERIOD_ZERO_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving rollover period.  The value is 0.
//
#define EMS_CALIB406_ROLLOVER_PERIOD_ZERO_ERROR ((EMS_RESULT)0x0004A424L)

//
// MessageId: EMS_CALIB406_SAT_CAPS_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving satellite capabilities for satellite %1 from configuration  The configuration manager returned error %2.
//
#define EMS_CALIB406_SAT_CAPS_GET_ERROR  ((EMS_RESULT)0x0004A425L)

//
// MessageId: EMS_CALIB406_SAT_PROCESSINFO_GET_ERROR
//
// MessageText:
//
// EMS Calibrate406 reported error retrieving satellite processing information for satellite %1 from configuration  The configuration manager returned error %2.
//
#define EMS_CALIB406_SAT_PROCESSINFO_GET_ERROR ((EMS_RESULT)0x0004A426L)

//
// MessageId: EMS_CALIB406_TCAL_BEACON_COUNT
//
// MessageText:
//
// Calibration will use %1 TCAL beacons to check SARR time accuracy.
//
#define EMS_CALIB406_TCAL_BEACON_COUNT   ((EMS_RESULT)0x0004A427L)

//
// MessageId: EMS_CALIB406_SARR_TIME_ERROR
//
// MessageText:
//
// Calibration suggests that LutID(%1) AntennaID(%2) has a %3 second SARR time error.
//
#define EMS_CALIB406_SARR_TIME_ERROR     ((EMS_RESULT)0x8004A428L)

//
// MessageId: EMS_CALIB406_SARR_TIME_OKAY
//
// MessageText:
//
// Calibration confirms that LutID(%1) AntennaID(%2) has a valid SARR time.
//
#define EMS_CALIB406_SARR_TIME_OKAY      ((EMS_RESULT)0x0004A429L)

//
// MessageId: EMS_CALIB406_ORBIT_VECTOR
//
// MessageText:
//
// EMS Calibrate406 cannot calculate an orbit vector for Satellite %1.
//
#define EMS_CALIB406_ORBIT_VECTOR        ((EMS_RESULT)0x8004A42AL)

//
// MessageId: EMS_CALIB406_BUFFER_ADD_EX
//
// MessageText:
//
// EMS Calibrate406 reports an error(0x%1) adding record(%2) SatID(%3) BeaconID(%4).
//
#define EMS_CALIB406_BUFFER_ADD_EX       ((EMS_RESULT)0x8004A42BL)

//
// MessageId: EMS_CALIB406_DATA_SOURCE_PROBLEM
//
// MessageText:
//
// EMS Calibrate406 reports bad data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)).
//
#define EMS_CALIB406_DATA_SOURCE_PROBLEM ((EMS_RESULT)0x8004A42CL)

//
// MessageId: EMS_CALIB406_DATA_SOURCE_PROBLEM_CLEARED
//
// MessageText:
//
// EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), alarm count(%4), frequency error(%5)) is back to normal.
//
#define EMS_CALIB406_DATA_SOURCE_PROBLEM_CLEARED ((EMS_RESULT)0x0004A42DL)

//
// MessageId: EMS_CALIB406_TIME_SOURCE_PROBLEM
//
// MessageText:
//
// EMS Calibrate406 reports data source (SatID(%1), LutID(%2), AntID(%3), BeaconID(%4), MessageTime (%5)) error.
//
#define EMS_CALIB406_TIME_SOURCE_PROBLEM ((EMS_RESULT)0x8004A42EL)

//
// MessageId: EMS_CALIB406_STOP_COMBINE_SARR_SARP
//
// MessageText:
//
// EMS Calibrate406 reports a frequency shift exceeding the allowable tolerance of %1Hz for satellite %2.  Combined SARR/SARP location processing will be disabled for the current pass.
//
#define EMS_CALIB406_STOP_COMBINE_SARR_SARP ((EMS_RESULT)0x8004A42FL)

//
// MessageId: EMS_CALIB406_LOW_NUMBER_SARP_RECORDS
//
// MessageText:
//
// EMS Calibrate406 produced low number of SARP records (%1) for satellite %2 passId %3.
//
#define EMS_CALIB406_LOW_NUMBER_SARP_RECORDS ((EMS_RESULT)0x8004A430L)

//
// MessageId: EMS_CALIB406_DATA_FILE_NOT_FOUND
//
// MessageText:
//
// EMS Calibrate406 cannot find the LSCalibData.xml file as specified in the registry (%1).
//
#define EMS_CALIB406_DATA_FILE_NOT_FOUND ((EMS_RESULT)0x8004A431L)


#endif // INC_CALIB406MSG
/********************************************************************
*	Module:			CollMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Collector Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_COLLMSGS
#define INC_COLLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_COLL_BASE_CODE
//
// MessageText:
//
// EMS Collector Error
//
#define EMS_COLL_BASE_CODE               ((EMS_RESULT)0x8004A300L)

//
// MessageId: EMS_COLL_SERVICE_START
//
// MessageText:
//
// EMS Collector Service Started
//
#define EMS_COLL_SERVICE_START           ((EMS_RESULT)0x0004A301L)

//
// MessageId: EMS_COLL_SERVICE_FAILED
//
// MessageText:
//
// EMS Collector Service did not start due to error (%1)
//
#define EMS_COLL_SERVICE_FAILED          ((EMS_RESULT)0x8004A302L)

//
// MessageId: EMS_COLL_SERVICE_STOP
//
// MessageText:
//
// EMS Collector Service Stopped
//
#define EMS_COLL_SERVICE_STOP            ((EMS_RESULT)0x0004A303L)

//
// MessageId: EMS_COLL_PASS_START
//
// MessageText:
//
// EMS Collector Service Starting Pass for Sat %1.
//
#define EMS_COLL_PASS_START              ((EMS_RESULT)0x0004A304L)

//
// MessageId: EMS_COLL_PASS_STOP
//
// MessageText:
//
// EMS Collector Service Stopped Pass for Sat %1.
//
#define EMS_COLL_PASS_STOP               ((EMS_RESULT)0x0004A305L)

//
// MessageId: EMS_COLL_ERROR
//
// MessageText:
//
// EMS Collector reports error (%1).
//
#define EMS_COLL_ERROR                   ((EMS_RESULT)0x8004A306L)

//
// MessageId: EMS_COLL_AD_OVERFLOW
//
// MessageText:
//
// EMS Collector reports A/D Board overflow
//
#define EMS_COLL_AD_OVERFLOW             ((EMS_RESULT)0x8004A307L)

//
// MessageId: EMS_COLL_RECV_COMMAND
//
// MessageText:
//
// EMS Collector recv'd cmd( %1 ).
//
#define EMS_COLL_RECV_COMMAND            ((EMS_RESULT)0x0004A308L)

//
// MessageId: EMS_COLL_WARN_MISSING_BUFFER
//
// MessageText:
//
// EMS Collector hasn't received a buffer in %1 seconds, resetting.
//
#define EMS_COLL_WARN_MISSING_BUFFER     ((EMS_RESULT)0x8004A309L)

//
// MessageId: EMS_COLL_ALARM_MISSING_BUFFER
//
// MessageText:
//
// EMS Collector hasn't received a buffer in %1 seconds, stopping.
//
#define EMS_COLL_ALARM_MISSING_BUFFER    ((EMS_RESULT)0xC004A309L)

//
// MessageId: EMS_COLL_WARN_ADBOARD_INIT_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to initialize AD Board, resetting. (%1)
//
#define EMS_COLL_WARN_ADBOARD_INIT_FAILED ((EMS_RESULT)0x8004A30AL)

//
// MessageId: EMS_COLL_ALARM_ADBOARD_INIT_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to initialize AD Board, stopping. (%1) 
//
#define EMS_COLL_ALARM_ADBOARD_INIT_FAILED ((EMS_RESULT)0xC004A30AL)

//
// MessageId: EMS_COLL_WARN_ADBOARD_START_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to start AD Board, resetting. (%1)
//
#define EMS_COLL_WARN_ADBOARD_START_FAILED ((EMS_RESULT)0x8004A30BL)

//
// MessageId: EMS_COLL_ALARM_ADBOARD_START_FAILED
//
// MessageText:
//
// EMS Collector reports error trying to start AD Board, stopping. (%1) 
//
#define EMS_COLL_ALARM_ADBOARD_START_FAILED ((EMS_RESULT)0xC004A30BL)

//
// MessageId: EMS_COLL_ALARM_MEMMARKER
//
// MessageText:
//
// EMS Collector reports memory marker %1 signal.
//
#define EMS_COLL_ALARM_MEMMARKER         ((EMS_RESULT)0x8004A30CL)

//
// MessageId: EMS_COLL_START_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a start command was received.
//
#define EMS_COLL_START_RECEIVED          ((EMS_RESULT)0x4004A30DL)

//
// MessageId: EMS_COLL_STOP_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a stop command was received.
//
#define EMS_COLL_STOP_RECEIVED           ((EMS_RESULT)0x4004A30EL)

//
// MessageId: EMS_COLL_SAT_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a set satellite command was received.  SatID = %1, Flags = %2, Bandwidth = %3.
//
#define EMS_COLL_SAT_RECEIVED            ((EMS_RESULT)0x4004A30FL)

//
// MessageId: EMS_COLL_INPUTID_RECEIVED
//
// MessageText:
//
// EMS Collector reports that a set input identifier command was received.  InputID = %1.
//
#define EMS_COLL_INPUTID_RECEIVED        ((EMS_RESULT)0x4004A310L)

//
// MessageId: EMS_COLL_START_UNINIT_FAILED
//
// MessageText:
//
// EMS Collector reports attempt to start collection on an uninitialized A/D Board (%1) Channel (%2).
//
#define EMS_COLL_START_UNINIT_FAILED     ((EMS_RESULT)0xC004A311L)

//
// MessageId: EMS_COLL_STATUS_UPDATE_FAILED
//
// MessageText:
//
// EMS Collector reports error attempting to update status. (%1)
//
#define EMS_COLL_STATUS_UPDATE_FAILED    ((EMS_RESULT)0x4004A312L)

//
// MessageId: EMS_COLL_NO_AD_CHANNELS
//
// MessageText:
//
// EMS Collector reports that A/D Board has no available channels.
//
#define EMS_COLL_NO_AD_CHANNELS          ((EMS_RESULT)0xC004A313L)

//
// MessageId: EMS_CS_WARN_MISSING_BUFFER
//
// MessageText:
//
// EMS CollectorStub hasn't received a buffer in %1 seconds, resetting.
//
#define EMS_CS_WARN_MISSING_BUFFER       ((EMS_RESULT)0x8004A314L)

//
// MessageId: EMS_CS_ALARM_MISSING_BUFFER
//
// MessageText:
//
// EMS CollectorStub hasn't received a buffer in %1 seconds, stopping.
//
#define EMS_CS_ALARM_MISSING_BUFFER      ((EMS_RESULT)0xC004A314L)

//
// MessageId: EMS_CS_FP_COMMS_FAILED
//
// MessageText:
//
// EMS CollectorStub failed to communicate with FP (%1)
//
#define EMS_CS_FP_COMMS_FAILED           ((EMS_RESULT)0xC004A315L)

//
// MessageId: EMS_CS_FP_COMMS_RESTORED
//
// MessageText:
//
// EMS CollectorStub communications restored to FP.
//
#define EMS_CS_FP_COMMS_RESTORED         ((EMS_RESULT)0x4004A316L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_OFF_ALARM
//
// MessageText:
//
// EMS Collector reports that the one pulse per second signal has not been detected for %1 seconds.
//
#define EMS_COLL_1PPS_SIGNAL_OFF_ALARM   ((EMS_RESULT)0xC004A317L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_OFF
//
// MessageText:
//
// EMS Collector reports that the one pulse per second signal was not detected in the last collected data buffer.
//
#define EMS_COLL_1PPS_SIGNAL_OFF         ((EMS_RESULT)0x4004A318L)

//
// MessageId: EMS_COLL_1PPS_SIGNAL_ON
//
// MessageText:
//
// EMS Collector reports that after an outage, the one pulse per second signal is now being detected.
//
#define EMS_COLL_1PPS_SIGNAL_ON          ((EMS_RESULT)0x4004A319L)

//
// MessageId: EMS_COLL_ERROR_SENDING_DATA
//
// MessageText:
//
// EMS Collector reports an error sending data.  Error code = %1.  Disconnecting.
//
#define EMS_COLL_ERROR_SENDING_DATA      ((EMS_RESULT)0x8004A31AL)

//
// MessageId: EMS_COLL_TRANSMITTING
//
// MessageText:
//
// EMS Collector reports transmitting Wave with time = %1 (%2).
//
#define EMS_COLL_TRANSMITTING            ((EMS_RESULT)0x4004A31BL)

//
// MessageId: EMS_COLL_ERROR_SENDING_WAVE_RECORD
//
// MessageText:
//
// EMS Collector reports an error sending wave record.
//
#define EMS_COLL_ERROR_SENDING_WAVE_RECORD ((EMS_RESULT)0x8004A31CL)

//
// MessageId: EMS_COLL_COMMON_INFO_MEG
//
// MessageText:
//
// EMS Collector reports %1.
//
#define EMS_COLL_COMMON_INFO_MEG         ((EMS_RESULT)0x4004A31DL)

//
// MessageId: EMS_COLL_DATA_DEST_OFFLINE
//
// MessageText:
//
// EMS Collector reports connection failed.  Data destination is offline.  Error code = %1.
//
#define EMS_COLL_DATA_DEST_OFFLINE       ((EMS_RESULT)0x8004A31EL)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: %3.
//
#define EMS_COLL_DC_DEBUG_MSG            ((EMS_RESULT)0x4004A31FL)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_MARKER_INDEX
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Last  marker index = %3, This marker index = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_MARKER_INDEX ((EMS_RESULT)0x4004A320L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_MARKER_BIT_INDEX
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Marker bit index calculated as %3.
//
#define EMS_COLL_DC_DEBUG_MSG_MARKER_BIT_INDEX ((EMS_RESULT)0x4004A321L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_BUF_TIME
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Original Data Buffer Time = %3 (%4).
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_BUF_TIME ((EMS_RESULT)0x4004A322L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_NAROSEC_OFFSET
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Nanosecond offset %3.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_NAROSEC_OFFSET ((EMS_RESULT)0x4004A323L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_SEC_DIFF
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between time of last buffer and this buffer is %3 seconds.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_SEC_DIFF ((EMS_RESULT)0x4004A324L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_1
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers exceeds 1.1 seconds. Last time = %3, this time = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_1 ((EMS_RESULT)0x4004A325L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_2
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Difference between consecutive buffers less than 1.0 second. Last time = %3, this time = %4.
//
#define EMS_COLL_DC_DEBUG_MSG_DATA_CONSECUTIVE_DIFF_2 ((EMS_RESULT)0x4004A326L)

//
// MessageId: EMS_COLL_DC_DEBUG_MSG_ADJUSTED_TIME
//
// MessageText:
//
// EMS Collector reports File: %1 Line: %2 with debug message: Adjusted Time = %3 (%4).
//
#define EMS_COLL_DC_DEBUG_MSG_ADJUSTED_TIME ((EMS_RESULT)0x4004A327L)


#endif // INC_COLLMSGS
/********************************************************************
*	Module:			WBandMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Wideband Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_WBANDMSG
#define INC_WBANDMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_WIDEBAND_BASE_CODE
//
// MessageText:
//
// EMS Wideband Error
//
#define EMS_WIDEBAND_BASE_CODE           ((EMS_RESULT)0x4004A200L)

//
// MessageId: EMS_WBAND_SERVICE_START
//
// MessageText:
//
// EMS Wideband Service Started
//
#define EMS_WBAND_SERVICE_START          ((EMS_RESULT)0x0004A201L)

//
// MessageId: EMS_WBAND_SERVICE_FAILED
//
// MessageText:
//
// EMS Wideband Service did not start due to error %1
//
#define EMS_WBAND_SERVICE_FAILED         ((EMS_RESULT)0x0004A202L)

//
// MessageId: EMS_WBAND_SERVICE_STOP
//
// MessageText:
//
// EMS Wideband Service Stopped
//
#define EMS_WBAND_SERVICE_STOP           ((EMS_RESULT)0x0004A203L)

//
// MessageId: EMS_WBAND_ERROR
//
// MessageText:
//
// EMS Wideband reports error %1.
//
#define EMS_WBAND_ERROR                  ((EMS_RESULT)0x8004A204L)

//
// MessageId: EMS_WBAND_PRIORITY_CLASS
//
// MessageText:
//
// EMS Wideband reports error %1 when calling SetPriorityClass
//
#define EMS_WBAND_PRIORITY_CLASS         ((EMS_RESULT)0x8004A205L)

//
// MessageId: EMS_WBAND_THREAD_PRIORITY
//
// MessageText:
//
// EMS Wideband reports error %1 when calling SetThreadPriority
//
#define EMS_WBAND_THREAD_PRIORITY        ((EMS_RESULT)0x8004A206L)

//
// MessageId: EMS_WBAND_IDEAL_PROCESSOR
//
// MessageText:
//
// EMS Wideband reports error %1 when calling SetThreadIdealProcessor
//
#define EMS_WBAND_IDEAL_PROCESSOR        ((EMS_RESULT)0x8004A207L)

//
// MessageId: EMS_WBAND_NO_DATA
//
// MessageText:
//
// EMS Wideband reports no data in last %1 seconds during a pass
//
#define EMS_WBAND_NO_DATA                ((EMS_RESULT)0x8004A208L)

//
// MessageId: EMS_WBAND_START_PASS
//
// MessageText:
//
// EMS Wideband starting pass ( SatID=%1, LutID=%2, Flags=%3 ).
//
#define EMS_WBAND_START_PASS             ((EMS_RESULT)0x0004A209L)

//
// MessageId: EMS_WBAND_STOP_PASS
//
// MessageText:
//
// EMS Wideband stopping pass. 
//
#define EMS_WBAND_STOP_PASS              ((EMS_RESULT)0x0004A20AL)

//
// MessageId: EMS_WBAND_RECV_COMMAND
//
// MessageText:
//
// EMS Wideband recv'd cmd( %1 ).
//
#define EMS_WBAND_RECV_COMMAND           ((EMS_RESULT)0x0004A20BL)

//
// MessageId: EMS_WBAND_TRACER
//
// MessageText:
//
// EMS Wideband ( %1 ).
//
#define EMS_WBAND_TRACER                 ((EMS_RESULT)0x0004A20CL)

//
// MessageId: EMS_WBAND_TRACER_TWIN0TO1
//
// MessageText:
//
// EMS Wideband (*** Wideband twin signal 0 -> 1)
//
#define EMS_WBAND_TRACER_TWIN0TO1        ((EMS_RESULT)0x0004A20DL)

//
// MessageId: EMS_WBAND_TRACER_TWIN1TO0
//
// MessageText:
//
// EMS Wideband (*** Wideband twin signal 1 -> 0)
//
#define EMS_WBAND_TRACER_TWIN1TO0        ((EMS_RESULT)0x0004A20EL)

//
// MessageId: EMS_WBAND_TRACER_REPEATINGINDEX
//
// MessageText:
//
// EMS Wideband (*** Wideband repeating index (%1))
//
#define EMS_WBAND_TRACER_REPEATINGINDEX  ((EMS_RESULT)0x0004A20FL)

//
// MessageId: EMS_WBAND_TRACER_OVERFLOW
//
// MessageText:
//
// EMS Wideband (*** Wideband reports overflow (%1))
//
#define EMS_WBAND_TRACER_OVERFLOW        ((EMS_RESULT)0x0004A210L)

//
// MessageId: EMS_WBAND_TRACER_HIGHESTCOUNT
//
// MessageText:
//
// EMS Wideband (*** Wideband highest count (%1))
//
#define EMS_WBAND_TRACER_HIGHESTCOUNT    ((EMS_RESULT)0x0004A211L)

//
// MessageId: EMS_WBAND_TRACER_OTHERBUFFER
//
// MessageText:
//
// EMS Wideband (*** Wideband reporting other buffer signaled (%1))
//
#define EMS_WBAND_TRACER_OTHERBUFFER     ((EMS_RESULT)0x0004A212L)

//
// MessageId: EMS_WBAND_TRACER_OLDERTHANAOS
//
// MessageText:
//
// EMS Wideband (*** Wideband data %1 minutes older than AOS )
//
#define EMS_WBAND_TRACER_OLDERTHANAOS    ((EMS_RESULT)0x0004A213L)

//
// MessageId: EMS_WBAND_TRACER_DUPLICATETIME
//
// MessageText:
//
// EMS Wideband (** Wideband detected duplicate time in buffer)
//
#define EMS_WBAND_TRACER_DUPLICATETIME   ((EMS_RESULT)0x0004A214L)

//
// MessageId: EMS_WBAND_TRACER_PREVTIME
//
// MessageText:
//
// EMS Wideband (** Wideband detected previous time in buffer)
//
#define EMS_WBAND_TRACER_PREVTIME        ((EMS_RESULT)0x0004A215L)

//
// MessageId: EMS_WBAND_TRACER_SECTOINITIALIZE
//
// MessageText:
//
// EMS Wideband (*** Wideband took %1 seconds to initialize)
//
#define EMS_WBAND_TRACER_SECTOINITIALIZE ((EMS_RESULT)0x0004A216L)

//
// MessageId: EMS_WBAND_TRACER_CONFIGYES
//
// MessageText:
//
// EMS Wideband (EMS Wideband (cfg: %1=yes))
//
#define EMS_WBAND_TRACER_CONFIGYES       ((EMS_RESULT)0x0004A217L)

//
// MessageId: EMS_WBAND_TRACER_CONFIGNO
//
// MessageText:
//
// EMS Wideband (EMS Wideband (cfg: %1=no))
//
#define EMS_WBAND_TRACER_CONFIGNO        ((EMS_RESULT)0x0004A218L)

//
// MessageId: EMS_WBAND_TRACER_CONFIG
//
// MessageText:
//
// EMS Wideband (cfg: %1=%2)
//
#define EMS_WBAND_TRACER_CONFIG          ((EMS_RESULT)0x0004A219L)

//
// MessageId: EMS_WBAND_INVALIDSTOPCMD
//
// MessageText:
//
// EMS Wideband is not collecting so a request to Stop was ignored.
//
#define EMS_WBAND_INVALIDSTOPCMD         ((EMS_RESULT)0x8004A21AL)

//
// MessageId: EMS_WBAND_INVALIDSTARTCMD
//
// MessageText:
//
// EMS Wideband is already collecting so a request to Start was ignored.
//
#define EMS_WBAND_INVALIDSTARTCMD        ((EMS_RESULT)0x8004A21BL)

//
// MessageId: EMS_WBAND_CMDERROR
//
// MessageText:
//
// EMS Wideband detected an error while processing a %1 command <%2>
//
#define EMS_WBAND_CMDERROR               ((EMS_RESULT)0x8004A21CL)


#endif // INC_WBANDMSG
/********************************************************************
*	Module:			JrnlMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS DB Journal Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_JRNLMSGS
#define INC_JRNLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DBJOURNAL_BASE_CODE
//
// MessageText:
//
// EMS DB Journal Error
//
#define EMS_DBJOURNAL_BASE_CODE          ((EMS_RESULT)0x8004A100L)

//
// MessageId: EMS_JRNL_SERVICE_START
//
// MessageText:
//
// EMS DB Journal Service Started
//
#define EMS_JRNL_SERVICE_START           ((EMS_RESULT)0x0004A101L)

//
// MessageId: EMS_JRNL_SERVICE_STOP
//
// MessageText:
//
// EMS DB Journal Service Stopped
//
#define EMS_JRNL_SERVICE_STOP            ((EMS_RESULT)0x0004A102L)

//
// MessageId: EMS_JRNL_ERROR
//
// MessageText:
//
// EMS DB Journal reports error %1.
//
#define EMS_JRNL_ERROR                   ((EMS_RESULT)0x8004A103L)

//
// MessageId: EMS_JRNL_DB_ERROR
//
// MessageText:
//
// EMS DB Journal reports error %1 while accessing database record %2.
//
#define EMS_JRNL_DB_ERROR                ((EMS_RESULT)0x8004A104L)

//
// MessageId: EMS_JRNL_TRACER
//
// MessageText:
//
// EMS DB Journal Service Tracer ( %1 )
//
#define EMS_JRNL_TRACER                  ((EMS_RESULT)0x0004A105L)

//
// MessageId: EMS_JRNL_TLEDUPKEY
//
// MessageText:
//
// EMS DB Journal Service reports duplicate primary key writing satellite %1 data to ORBIT_DATA table.
//
#define EMS_JRNL_TLEDUPKEY               ((EMS_RESULT)0x0004A106L)

//
// MessageId: EMS_JRNL_START_DBCLEAN
//
// MessageText:
//
// EMS DB Journal Starting Database Clean.
//
#define EMS_JRNL_START_DBCLEAN           ((EMS_RESULT)0x0004A107L)

//
// MessageId: EMS_JRNL_STOP_DBCLEAN
//
// MessageText:
//
// EMS DB Journal Finished Database Clean.
//
#define EMS_JRNL_STOP_DBCLEAN            ((EMS_RESULT)0x0004A108L)

//
// MessageId: EMS_JRNL_TRACER_AUDIORIFFDATA
//
// MessageText:
//
// EMS DB Journal Service Tracer ( BeaconID=%1, time=%2, Sat ID=%3, Lut ID=%4 )
//
#define EMS_JRNL_TRACER_AUDIORIFFDATA    ((EMS_RESULT)0x0004A109L)

//
// MessageId: EMS_JRNL_TRACER_LOCATEDATA
//
// MessageText:
//
// EMS DB Journal Service Tracer ( time=%1, type=%2, ID=%3 )
//
#define EMS_JRNL_TRACER_LOCATEDATA       ((EMS_RESULT)0x0004A10AL)

//
// MessageId: EMS_JRNL_TRACER_CALIBCBC
//
// MessageText:
//
// EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
//
#define EMS_JRNL_TRACER_CALIBCBC         ((EMS_RESULT)0x0004A10BL)

//
// MessageId: EMS_JRNL_TRACER_RESIDUALDATA
//
// MessageText:
//
// EMS DB Journal Service Tracer ( time=%1, sat=%2, lut=%3, type=%4 )
//
#define EMS_JRNL_TRACER_RESIDUALDATA     ((EMS_RESULT)0x0004A10CL)

//
// MessageId: EMS_JRNL_TRACER_DBCLEAN
//
// MessageText:
//
// EMS DB Journal Service Tracer ( DBClean returns %1 )
//
#define EMS_JRNL_TRACER_DBCLEAN          ((EMS_RESULT)0x0004A10DL)

//
// MessageId: EMS_JRNL_INIT_EXCEPTION
//
// MessageText:
//
// EMS DB Journal initialization failed with an unhandled exception.
//
#define EMS_JRNL_INIT_EXCEPTION          ((EMS_RESULT)0x8004A10EL)

//
// MessageId: EMS_JRNL_DB_ERROR_DUPKEY
//
// MessageText:
//
// EMS DB Journal reports a duplicate primary key error (%1).
//
#define EMS_JRNL_DB_ERROR_DUPKEY         ((EMS_RESULT)0x8004A10FL)


#endif // INC_JRNLMSGS
/********************************************************************
*	Module:			pipemsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Pipeline Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*						All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_PIPEMSGS
#define INC_PIPEMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_PIPE_BASE_CODE
//
// MessageText:
//
// EMS Pipeline Error
//
#define EMS_PIPE_BASE_CODE               ((EMS_RESULT)0x80048800L)

//
// MessageId: EMS_PIPE_LIMIT_EXCEEDED
//
// MessageText:
//
// EMS Pipeline Limit Exceeded
//
#define EMS_PIPE_LIMIT_EXCEEDED          ((EMS_RESULT)0x80048803L)

//
// MessageId: EMS_PIPE_OVERFLOW
//
// MessageText:
//
// EMS Pipeline Channel %1 has overflowed
//
#define EMS_PIPE_OVERFLOW                ((EMS_RESULT)0x80048804L)

//
// MessageId: EMS_PIPE_DATA_LOST
//
// MessageText:
//
// EMS Pipeline Channel data has been lost
//
#define EMS_PIPE_DATA_LOST               ((EMS_RESULT)0x80048805L)

//
// MessageId: EMS_PIPE_DATA_TRUNCATED
//
// MessageText:
//
// EMS Pipeline Channel data has been truncated
//
#define EMS_PIPE_DATA_TRUNCATED          ((EMS_RESULT)0x80048806L)

//
// MessageId: EMS_PIPE_UNKNOWN_SINK
//
// MessageText:
//
// EMS Pipeline Channel unknown sink
//
#define EMS_PIPE_UNKNOWN_SINK            ((EMS_RESULT)0x80048807L)

//
// MessageId: EMS_PIPE_UNKNOWN_SOURCE
//
// MessageText:
//
// EMS Pipeline Channel unknown source
//
#define EMS_PIPE_UNKNOWN_SOURCE          ((EMS_RESULT)0x80048808L)

//
// MessageId: EMS_PIPE_NO_SINKS
//
// MessageText:
//
// EMS Pipeline Channel %1 has no active sinks
//
#define EMS_PIPE_NO_SINKS                ((EMS_RESULT)0x80048809L)

//
// MessageId: EMS_PIPE_ALREADY_REGISTERED
//
// MessageText:
//
// EMS Pipeline sink / source is already registered
//
#define EMS_PIPE_ALREADY_REGISTERED      ((EMS_RESULT)0x8004880AL)

//
// MessageId: EMS_PIPE_ALREADY_SET
//
// MessageText:
//
// EMS Pipeline is already registered set
//
#define EMS_PIPE_ALREADY_SET             ((EMS_RESULT)0x8004880BL)

//
// MessageId: EMS_PIPE_TOO_BIG
//
// MessageText:
//
// EMS Pipeline is too big
//
#define EMS_PIPE_TOO_BIG                 ((EMS_RESULT)0x8004880CL)

//
// MessageId: EMS_PIPE_SERVICE_START
//
// MessageText:
//
// EMS Pipeline Service Started
//
#define EMS_PIPE_SERVICE_START           ((EMS_RESULT)0x0004880DL)

//
// MessageId: EMS_PIPE_SERVICE_FAILED
//
// MessageText:
//
// EMS Pipeline Service did not start due to error %1
//
#define EMS_PIPE_SERVICE_FAILED          ((EMS_RESULT)0x8004880EL)

//
// MessageId: EMS_PIPE_SERVICE_STOP
//
// MessageText:
//
// EMS Pipeline Service Stopped
//
#define EMS_PIPE_SERVICE_STOP            ((EMS_RESULT)0x0004880FL)

//
// MessageId: EMS_PIPE_LOG_CHANNEL_WRITE
//
// MessageText:
//
// EMS Pipeline Logging Channel Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
//
#define EMS_PIPE_LOG_CHANNEL_WRITE       ((EMS_RESULT)0x00048810L)

//
// MessageId: EMS_PIPE_START_LOGGING
//
// MessageText:
//
// EMS Pipeline Logging Enabled
//
#define EMS_PIPE_START_LOGGING           ((EMS_RESULT)0x00048811L)

//
// MessageId: EMS_PIPE_STOP_LOGGING
//
// MessageText:
//
// EMS Pipeline Logging Disabled
//
#define EMS_PIPE_STOP_LOGGING            ((EMS_RESULT)0x00048812L)

//
// MessageId: EMS_PIPE_LOG_REGISTER_SINK
//
// MessageText:
//
// EMS Pipeline Logging Register Sink ( Type=%1, Count=%2, Result = %3  )
//
#define EMS_PIPE_LOG_REGISTER_SINK       ((EMS_RESULT)0x00048813L)

//
// MessageId: EMS_PIPE_LOG_REGISTER_SOURCE
//
// MessageText:
//
// EMS Pipeline Logging Register Source ( Type=%1, Count=%2, Result = %3 )
//
#define EMS_PIPE_LOG_REGISTER_SOURCE     ((EMS_RESULT)0x00048814L)

//
// MessageId: EMS_PIPE_LOG_UNREGISTER_SINK
//
// MessageText:
//
// EMS Pipeline Logging Unregister Sink ( Type=%1, Count=%2, Result = %3  )
//
#define EMS_PIPE_LOG_UNREGISTER_SINK     ((EMS_RESULT)0x00048815L)

//
// MessageId: EMS_PIPE_LOG_UNREGISTER_SOURCE
//
// MessageText:
//
// EMS Pipeline Logging Unregister Source ( Type=%1, Count=%2, Result = %3 )
//
#define EMS_PIPE_LOG_UNREGISTER_SOURCE   ((EMS_RESULT)0x00048816L)

//
// MessageId: EMS_PIPE_LOG_WRITE_COMMAND
//
// MessageText:
//
// EMS Pipeline Logging Command Write ( Type=%1, Sinks=%2, Bytes=%3, Result=%4 )
//
#define EMS_PIPE_LOG_WRITE_COMMAND       ((EMS_RESULT)0x00048817L)

//
// MessageId: EMS_PIPE_LOG_CHANNEL_SUMMARY
//
// MessageText:
//
// EMS Pipeline Logging Channel Summary ( Type=%1, Sinks=%2, Srcs=%3, Max=%4, Min=%5 )
//
#define EMS_PIPE_LOG_CHANNEL_SUMMARY     ((EMS_RESULT)0x00048818L)

//
// MessageId: EMS_PIPE_ERROR
//
// MessageText:
//
// EMS Pipeline Error ( %1 )
//
#define EMS_PIPE_ERROR                   ((EMS_RESULT)0x80048819L)

//
// MessageId: EMS_PIPE_NO_STREAM
//
// MessageText:
//
// EMS Pipeline reports invalid stream pointer.
//
#define EMS_PIPE_NO_STREAM               ((EMS_RESULT)0x8004881AL)

//
// MessageId: EMS_PIPE_OVERFLOW_RETRY
//
// MessageText:
//
// EMS Pipeline Channel %1 has overflowed , retry %2
//
#define EMS_PIPE_OVERFLOW_RETRY          ((EMS_RESULT)0x8004881BL)

//
// MessageId: EMS_PIPE_RECV_COMMAND
//
// MessageText:
//
// Command Received( %1 )
//
#define EMS_PIPE_RECV_COMMAND            ((EMS_RESULT)0x0004881CL)

//
// MessageId: EMS_STREAM_OVERFLOW
//
// MessageText:
//
// EMS Pipeline stream has overflowed
//
#define EMS_STREAM_OVERFLOW              ((EMS_RESULT)0x8004881DL)

//
// MessageId: EMS_PIPE_CHANNEL_LOCK_FAILED
//
// MessageText:
//
// DataChannel %1::_Lock Failed
//
#define EMS_PIPE_CHANNEL_LOCK_FAILED     ((EMS_RESULT)0x8004881EL)

//
// MessageId: EMS_PIPE_PIPELINE_LOCK_FAILED
//
// MessageText:
//
// DataPipeline::_Lock Failed
//
#define EMS_PIPE_PIPELINE_LOCK_FAILED    ((EMS_RESULT)0x8004881FL)

//
// MessageId: EMS_PIPE_TRACE_WRITE_OVERFLOW
//
// MessageText:
//
// PacketStream::Write Overflow {Type=%1, Retries=%2}
//
#define EMS_PIPE_TRACE_WRITE_OVERFLOW    ((EMS_RESULT)0x00048820L)

//
// MessageId: EMS_PIPE_PKTSTREAM_LOCKFAILED
//
// MessageText:
//
// EMS Pipeline Error ( PacketStream::_Lock Failed )
//
#define EMS_PIPE_PKTSTREAM_LOCKFAILED    ((EMS_RESULT)0x80048821L)

//
// MessageId: EMS_PIPE_TRACER
//
// MessageText:
//
// EMS Pipeline : %1
//
#define EMS_PIPE_TRACER                  ((EMS_RESULT)0x00048822L)

//
// MessageId: EMS_PIPE_CHANNEL_OVERFLOW
//
// MessageText:
//
// EMS Pipeline : Overflow on channel %1 for process %2
//
#define EMS_PIPE_CHANNEL_OVERFLOW        ((EMS_RESULT)0x80048823L)

//
// MessageId: EMS_PIPE_SINK_REGISTERED_FOR_PROCESS
//
// MessageText:
//
// Sink registered on channel %1 for process %2
//
#define EMS_PIPE_SINK_REGISTERED_FOR_PROCESS ((EMS_RESULT)0x00048824L)

//
// MessageId: EMS_PIPE_SINK_REGISTERED_UNK_PROCESS
//
// MessageText:
//
// Sink registered on channel %1 for unidentified process
//
#define EMS_PIPE_SINK_REGISTERED_UNK_PROCESS ((EMS_RESULT)0x00048825L)


#endif // INC_PIPEMSGS
#ifndef INC_DACMSGS
#define INC_DACMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DAC_BASE_CODE
//
// MessageText:
//
// EMS Data Acquisition Error
//
#define EMS_DAC_BASE_CODE                ((EMS_RESULT)0x0004BB00L)

//
// MessageId: EMS_DAC_SERVICE_START
//
// MessageText:
//
// EMS Data Acquisition Service Started
//
#define EMS_DAC_SERVICE_START            ((EMS_RESULT)0x0004BB01L)

//
// MessageId: EMS_DAC_LUTTYPE_REJECTED
//
// MessageText:
//
// EMS Data Acquisition not accepting data type: %1
//
#define EMS_DAC_LUTTYPE_REJECTED         ((EMS_RESULT)0x8004BB02L)

//
// MessageId: EMS_DAC_RECV_COMMAND
//
// MessageText:
//
// EMS Data Acquisition received command ( %1 ).
//
#define EMS_DAC_RECV_COMMAND             ((EMS_RESULT)0x0004BB03L)

//
// MessageId: EMS_DAC_SERVICE_STOP
//
// MessageText:
//
// EMS Data Acquisition Service Stopped.
//
#define EMS_DAC_SERVICE_STOP             ((EMS_RESULT)0x0004BB04L)

//
// MessageId: EMS_DAC_EXCEPTION
//
// MessageText:
//
// EMS Data Acquisition Exception thrown: %1
//
#define EMS_DAC_EXCEPTION                ((EMS_RESULT)0x8004BB05L)

//
// MessageId: EMS_DAC_BAD_RETR_INTERVAL
//
// MessageText:
//
// EMS Data Acquisition - Time interval specified for data retrieval is too large.
//
#define EMS_DAC_BAD_RETR_INTERVAL        ((EMS_RESULT)0x8004BB06L)

//
// MessageId: EMS_DAC_BAD_ARRAYINDEX
//
// MessageText:
//
// EMS Data Acquisition - Array index out of bounds.
//
#define EMS_DAC_BAD_ARRAYINDEX           ((EMS_RESULT)0x8004BB07L)

//
// MessageId: EMS_DAC_SENDDATAREQ_ERR
//
// MessageText:
//
// EMS Data Acquisition - Error sending data request: DataType: %1
//
#define EMS_DAC_SENDDATAREQ_ERR          ((EMS_RESULT)0x8004BB08L)

//
// MessageId: EMS_DAC_LUTTYPE_REJECTED_DETAILS
//
// MessageText:
//
// EMS Data Acquisition not accepting data type: %1 from LUT: %2. %3
//
#define EMS_DAC_LUTTYPE_REJECTED_DETAILS ((EMS_RESULT)0x8004BB09L)

//
// MessageId: EMS_DAC_LUTTYPE_LOG_REJECTED_DETAILS
//
// MessageText:
//
// EMS Data Acquisition not accepting data type: %1 from LUT: %2. %3 %4 %5 %6
//
#define EMS_DAC_LUTTYPE_LOG_REJECTED_DETAILS ((EMS_RESULT)0x8004BB0AL)

//
// MessageId: EMS_DAC_DATAWRITEFAILED
//
// MessageText:
//
// EMS Data Acquisition data write failed. Channel Type: %1.
//
#define EMS_DAC_DATAWRITEFAILED          ((EMS_RESULT)0x8004BB0BL)


#endif // INC_DACMSGS
/********************************************************************
*	Module:			MTLMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for MTL
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 Oct 8		jb	start 

********************************************************************/
#ifndef INC_MTLMSGS
#define INC_MTLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_MTL_BASE_CODE
//
// MessageText:
//
// EMS MTL Error
//
#define EMS_MTL_BASE_CODE                ((EMS_RESULT)0x8004B600L)

//
// MessageId: EMS_MTL_EXCEPTION
//
// MessageText:
//
// EMS MTL exception has occurred:  %1
//
#define EMS_MTL_EXCEPTION                ((EMS_RESULT)0x8004B601L)

//
// MessageId: EMS_MTL_SIT_NOT_ALLOWED
//
// MessageText:
//
// EMS MTL Error:  SIT message sequence %1 of type %2 from %3 to %4 not permitted.
//
#define EMS_MTL_SIT_NOT_ALLOWED          ((EMS_RESULT)0x8004B602L)

//
// MessageId: EMS_MTL_BIN_NOT_ALLOWED
//
// MessageText:
//
// EMS MTL Error:  Binary message file %1 of type %2 from %3 to %4 not permitted.
//
#define EMS_MTL_BIN_NOT_ALLOWED          ((EMS_RESULT)0x8004B603L)

//
// MessageId: EMS_MTL_SOAP_CLIENT_EXCEPTION
//
// MessageText:
//
// EMS MTL Error:  SOAP Client error code %1, Reason: %2, Detail: %3.
//
#define EMS_MTL_SOAP_CLIENT_EXCEPTION    ((EMS_RESULT)0x8004B604L)

//
// MessageId: EMS_MTL_CONFIG_TWO_KEYS
//
// MessageText:
//
// EMS MTL Error:  Could not retrieve configuration value for Group %1:%2, Key %3 or %4.
//
#define EMS_MTL_CONFIG_TWO_KEYS          ((EMS_RESULT)0x8004B605L)

//
// MessageId: EMS_MTL_NO_ROUTE_FOUND
//
// MessageText:
//
// EMS MTL Error:  Configuration data for a route between %1 and %2 could not be found.
//
#define EMS_MTL_NO_ROUTE_FOUND           ((EMS_RESULT)0x8004B606L)

//
// MessageId: EMS_MTL_CFG_UNKNOWN_MSG_TYPE
//
// MessageText:
//
// EMS MTL Error:  An unknown message type was read from configuration:  %1.
//
#define EMS_MTL_CFG_UNKNOWN_MSG_TYPE     ((EMS_RESULT)0x8004B607L)

//
// MessageId: EMS_MTL_CFG_OUT_DIR
//
// MessageText:
//
// EMS MTL Error:  The Send directory could not be obtained from the configuration.
//
#define EMS_MTL_CFG_OUT_DIR              ((EMS_RESULT)0x8004B608L)

//
// MessageId: EMS_MTL_CFG_SHORT_NAME
//
// MessageText:
//
// EMS MTL Error:  The Cospas-Sarsat short name associated with identifier %1 could not be found in the configuration.
//
#define EMS_MTL_CFG_SHORT_NAME           ((EMS_RESULT)0x8004B609L)

//
// MessageId: EMS_MTL_INVALID_MAX_SARR_SATELLITES
//
// MessageText:
//
// EMS MTL Error:  The configured value for maximum satellites in a single SARR calibration message must be at least 1.  The value is %1.
//
#define EMS_MTL_INVALID_MAX_SARR_SATELLITES ((EMS_RESULT)0x8004B60AL)

//
// MessageId: EMS_MTL_SOAP_CLIENT_FAULT
//
// MessageText:
//
// EMS MTL Error:  A SOAP client fault has occurred.
//
#define EMS_MTL_SOAP_CLIENT_FAULT        ((EMS_RESULT)0x8004B60BL)

//
// MessageId: EMS_MTL_SOAP_SERVER_FAULT
//
// MessageText:
//
// EMS MTL Error:  A SOAP server fault has occurred.
//
#define EMS_MTL_SOAP_SERVER_FAULT        ((EMS_RESULT)0x8004B60CL)

//
// MessageId: EMS_MTL_SOAP_TAG_MISMATCH
//
// MessageText:
//
// EMS MTL Error:  A SOAP message XML element didn't correspond to anything expected.
//
#define EMS_MTL_SOAP_TAG_MISMATCH        ((EMS_RESULT)0x8004B60DL)

//
// MessageId: EMS_MTL_SOAP_TYPE_MISMATCH
//
// MessageText:
//
// EMS MTL Error:  A SOAP message XML schema type mismatch was encountered.
//
#define EMS_MTL_SOAP_TYPE_MISMATCH       ((EMS_RESULT)0x8004B60EL)

//
// MessageId: EMS_MTL_SOAP_SYNTAX_ERROR
//
// MessageText:
//
// EMS MTL Error:  A SOAP message XML syntax error occurred on the input.
//
#define EMS_MTL_SOAP_SYNTAX_ERROR        ((EMS_RESULT)0x8004B60FL)

//
// MessageId: EMS_MTL_SOAP_NO_TAG
//
// MessageText:
//
// EMS MTL Error:  A SOAP message beginning of an element expected, but not found.
//
#define EMS_MTL_SOAP_NO_TAG              ((EMS_RESULT)0x8004B610L)

//
// MessageId: EMS_MTL_SOAP_IOB
//
// MessageText:
//
// EMS MTL Error:  A SOAP processor array index is out of bounds.
//
#define EMS_MTL_SOAP_IOB                 ((EMS_RESULT)0x8004B611L)

//
// MessageId: EMS_MTL_SOAP_MUSTUNDERSTAND
//
// MessageText:
//
// EMS MTL Error:  A SOAP element configured as "must understand" needs to be ignored.
//
#define EMS_MTL_SOAP_MUSTUNDERSTAND      ((EMS_RESULT)0x8004B612L)

//
// MessageId: EMS_MTL_SOAP_NAMESPACE
//
// MessageText:
//
// EMS MTL Error:  A SOAP namespace name mismatch has occurred.
//
#define EMS_MTL_SOAP_NAMESPACE           ((EMS_RESULT)0x8004B613L)

//
// MessageId: EMS_MTL_SOAP_OBJ_MISMATCH
//
// MessageText:
//
// EMS MTL Error:  The SOAP processor has encountered a mismatch in the size and/or shape of an object.
//
#define EMS_MTL_SOAP_OBJ_MISMATCH        ((EMS_RESULT)0x8004B614L)

//
// MessageId: EMS_MTL_SOAP_ERROR
//
// MessageText:
//
// EMS MTL Trace:  A SOAP error was returned to the client.  Error code = %1.
//
#define EMS_MTL_SOAP_ERROR               ((EMS_RESULT)0x8004B615L)

//
// MessageId: EMS_MTL_SOAP_CLIENT_ERROR
//
// MessageText:
//
// EMS MTL Trace:  A SOAP error was encountered on the client:  %1.
//
#define EMS_MTL_SOAP_CLIENT_ERROR        ((EMS_RESULT)0x8004B616L)

//
// MessageId: EMS_MTL_SOAP_UNKNOWN_ERROR
//
// MessageText:
//
// EMS MTL Trace:  An unknown error was returned to the SOAP client.
//
#define EMS_MTL_SOAP_UNKNOWN_ERROR       ((EMS_RESULT)0x8004B617L)

//
// MessageId: EMS_MTL_SIT_OUTPUTFILE
//
// MessageText:
//
// EMS MTL Trace:  Writing outgoing SIT message to %1.
//
#define EMS_MTL_SIT_OUTPUTFILE           ((EMS_RESULT)0x0004B618L)

//
// MessageId: EMS_MTL_SIT_OUTDIR
//
// MessageText:
//
// EMS MTL Trace:  Writing outgoing SIT message to directory %1.
//
#define EMS_MTL_SIT_OUTDIR               ((EMS_RESULT)0x0004B619L)

//
// MessageId: EMS_MTL_SIT_SRC_NAME
//
// MessageText:
//
// EMS MTL Trace:  Outgoing SIT message source name is %1.
//
#define EMS_MTL_SIT_SRC_NAME             ((EMS_RESULT)0x0004B61AL)

//
// MessageId: EMS_MTL_SIT_DEST_NAME
//
// MessageText:
//
// EMS MTL Trace:  Outgoing SIT message destination name is %1.
//
#define EMS_MTL_SIT_DEST_NAME            ((EMS_RESULT)0x0004B61BL)

//
// MessageId: EMS_MTL_CONFIG_RTE_OUT_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  Unable to retrieve outgoing configuration information for routing from %1 to %2.
//
#define EMS_MTL_CONFIG_RTE_OUT_NOT_FOUND ((EMS_RESULT)0x8004B61CL)

//
// MessageId: EMS_MTL_ALERT_UNKNOWN_TYPE
//
// MessageText:
//
// EMS MTL Error:  Unable to create alert SIT message type %1.
//
#define EMS_MTL_ALERT_UNKNOWN_TYPE       ((EMS_RESULT)0x8004B61DL)

//
// MessageId: EMS_MTL_ALERT_SIT_NOT_CONFIGURED
//
// MessageText:
//
// EMS MTL Error:  Requested SIT message type %1 is not configured for destination %2.
//
#define EMS_MTL_ALERT_SIT_NOT_CONFIGURED ((EMS_RESULT)0x8004B61EL)

//
// MessageId: EMS_MTL_ALERT_NO_DESTINATIONS_CONFIGURED
//
// MessageText:
//
// EMS MTL Trace:  No Alert destinations are configured.
//
#define EMS_MTL_ALERT_NO_DESTINATIONS_CONFIGURED ((EMS_RESULT)0x0004B61FL)

//
// MessageId: EMS_MTL_CONFIG_ROUTE_NAME_SYNTAX
//
// MessageText:
//
// EMS MTL Error:  An invalid route name syntax was encountered:  %1.
//
#define EMS_MTL_CONFIG_ROUTE_NAME_SYNTAX ((EMS_RESULT)0x8004B620L)

//
// MessageId: EMS_MTL_CONFIG_NULL
//
// MessageText:
//
// EMS MTL Error:  Unable to access the MTL configuration object.
//
#define EMS_MTL_CONFIG_NULL              ((EMS_RESULT)0x8004B621L)

//
// MessageId: EMS_MTL_SOAP_SERVER_INIT
//
// MessageText:
//
// EMS MTL Trace:  Socket connection successful.  %1.
//
#define EMS_MTL_SOAP_SERVER_INIT         ((EMS_RESULT)0x0004B622L)

//
// MessageId: EMS_MTL_SOAP_CONNECT_RECVD
//
// MessageText:
//
// EMS MTL Trace:  Accepted connection from IP: %1.
//
#define EMS_MTL_SOAP_CONNECT_RECVD       ((EMS_RESULT)0x0004B623L)

//
// MessageId: EMS_MTL_SOAP_REQUEST_SERVED
//
// MessageText:
//
// EMS MTL Trace:  SOAP Request served on handler thread %1.
//
#define EMS_MTL_SOAP_REQUEST_SERVED      ((EMS_RESULT)0x0004B624L)

//
// MessageId: EMS_MTL_SOAP_PORT_BIND_ERROR
//
// MessageText:
//
// EMS MTL Error:  SOAP Server could not bind to incoming message port %1.
//
#define EMS_MTL_SOAP_PORT_BIND_ERROR     ((EMS_RESULT)0x8004B625L)

//
// MessageId: EMS_MTL_SERVICE_STARTED
//
// MessageText:
//
// EMS Message Translation Layer (MTL) Service started
//
#define EMS_MTL_SERVICE_STARTED          ((EMS_RESULT)0x0004B626L)

//
// MessageId: EMS_MTL_SERVICE_START_FAILED
//
// MessageText:
//
// EMS Message Translation Layer (MTL) Service failed to start with error %1.
//
#define EMS_MTL_SERVICE_START_FAILED     ((EMS_RESULT)0x8004B627L)

//
// MessageId: EMS_MTL_SERVICE_STOP
//
// MessageText:
//
// EMS Message Translation Layer (MTL) Service stopped
//
#define EMS_MTL_SERVICE_STOP             ((EMS_RESULT)0x0004B628L)

//
// MessageId: EMS_SOAP_SERVICE_STARTED
//
// MessageText:
//
// EMS SOAP Service started
//
#define EMS_SOAP_SERVICE_STARTED         ((EMS_RESULT)0x0004B629L)

//
// MessageId: EMS_SOAP_SERVICE_START_FAILED
//
// MessageText:
//
// EMS SOAP Service failed to start with error %1.
//
#define EMS_SOAP_SERVICE_START_FAILED    ((EMS_RESULT)0x8004B62AL)

//
// MessageId: EMS_SOAP_SERVICE_STOP
//
// MessageText:
//
// EMS SOAP Service stopped
//
#define EMS_SOAP_SERVICE_STOP            ((EMS_RESULT)0x0004B62BL)

//
// MessageId: EMS_MTL_SOAP_FATAL_ERROR
//
// MessageText:
//
// EMS MTL Error:  Internal SOAP error.
//
#define EMS_MTL_SOAP_FATAL_ERROR         ((EMS_RESULT)0x8004B62CL)

//
// MessageId: EMS_MTL_SOAP_NO_METHOD
//
// MessageText:
//
// EMS MTL Error:  SOAP skeleton error.  The skeleton cannot serve the method.
//
#define EMS_MTL_SOAP_NO_METHOD           ((EMS_RESULT)0x8004B62DL)

//
// MessageId: EMS_MTL_SOAP_GET_METHOD
//
// MessageText:
//
// EMS MTL Error:  SOAP unsupported HTTP Get error.
//
#define EMS_MTL_SOAP_GET_METHOD          ((EMS_RESULT)0x8004B62EL)

//
// MessageId: EMS_MTL_SOAP_EOM
//
// MessageText:
//
// EMS MTL Error:  SOAP out of memory error.
//
#define EMS_MTL_SOAP_EOM                 ((EMS_RESULT)0x8004B62FL)

//
// MessageId: EMS_MTL_SOAP_NULL
//
// MessageText:
//
// EMS MTL Error:  The SOAP processor encountered an unexpected NULL value.
//
#define EMS_MTL_SOAP_NULL                ((EMS_RESULT)0x8004B630L)

//
// MessageId: EMS_MTL_SOAP_MULTI_ID
//
// MessageText:
//
// EMS MTL Error:  The SOAP processor encountered multiple occurrences of the same element ID on the input.
//
#define EMS_MTL_SOAP_MULTI_ID            ((EMS_RESULT)0x8004B631L)

//
// MessageId: EMS_MTL_SOAP_MISSING_ID
//
// MessageText:
//
// EMS MTL Error:  The SOAP processor encountered a missing element ID for an HREF on the input.
//
#define EMS_MTL_SOAP_MISSING_ID          ((EMS_RESULT)0x8004B632L)

//
// MessageId: EMS_MTL_SOAP_HREF
//
// MessageText:
//
// EMS MTL Error:  The SOAP processor encountered an object reference incompatible with the object refered to.
//
#define EMS_MTL_SOAP_HREF                ((EMS_RESULT)0x8004B633L)

//
// MessageId: EMS_MTL_SOAP_TCP_ERROR
//
// MessageText:
//
// EMS MTL Error:  A TCP connection error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_TCP_ERROR           ((EMS_RESULT)0x8004B634L)

//
// MessageId: EMS_MTL_SOAP_HTTP_ERROR
//
// MessageText:
//
// EMS MTL Error:  An HTTP error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_HTTP_ERROR          ((EMS_RESULT)0x8004B635L)

//
// MessageId: EMS_MTL_SOAP_SSL_ERROR
//
// MessageText:
//
// EMS MTL Error:  An SSL error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_SSL_ERROR           ((EMS_RESULT)0x8004B636L)

//
// MessageId: EMS_MTL_SOAP_ZLIB_ERROR
//
// MessageText:
//
// EMS MTL Error:  A ZLIB error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_ZLIB_ERROR          ((EMS_RESULT)0x8004B637L)

//
// MessageId: EMS_MTL_SOAP_DIME_ERROR
//
// MessageText:
//
// EMS MTL Error:  A DIME parsing error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_DIME_ERROR          ((EMS_RESULT)0x8004B638L)

//
// MessageId: EMS_MTL_SOAP_EOD
//
// MessageText:
//
// EMS MTL Error:  An end of DIME error occurred while attempting to send a SOAP message.
//
#define EMS_MTL_SOAP_EOD                 ((EMS_RESULT)0x8004B639L)

//
// MessageId: EMS_MTL_SOAP_VERSION_MISMATCH
//
// MessageText:
//
// EMS MTL Error:  A SOAP version mismatch or no SOAP message error has occurred.
//
#define EMS_MTL_SOAP_VERSION_MISMATCH    ((EMS_RESULT)0x8004B63AL)

//
// MessageId: EMS_MTL_SOAP_DIME_MISMATCH
//
// MessageText:
//
// EMS MTL Error:  A SOAP DIME version mismatch has occurred.
//
#define EMS_MTL_SOAP_DIME_MISMATCH       ((EMS_RESULT)0x8004B63BL)

//
// MessageId: EMS_MTL_SOAP_PLUGIN_ERROR
//
// MessageText:
//
// EMS MTL Error:  Failure registering SOAP plugin.
//
#define EMS_MTL_SOAP_PLUGIN_ERROR        ((EMS_RESULT)0x8004B63CL)

//
// MessageId: EMS_MTL_SOAP_EOF
//
// MessageText:
//
// EMS MTL Error:  SOAP error occurred.  Unexpected end of file, no input, or timeout receiving data.
//
#define EMS_MTL_SOAP_EOF                 ((EMS_RESULT)0x8004B63DL)

//
// MessageId: EMS_MTL_CLIENT_RESOURCE_TO_SIT_ERROR
//
// MessageText:
//
// EMS MTL Error:  The MTL Client has no mapping from the resource identifier %1 to a SIT message type.
//
#define EMS_MTL_CLIENT_RESOURCE_TO_SIT_ERROR ((EMS_RESULT)0x8004B63EL)

//
// MessageId: EMS_MTL_SOAP_SERVER_THREADS
//
// MessageText:
//
// EMS SOAP Server is initializing %1 handler threads.
//
#define EMS_MTL_SOAP_SERVER_THREADS      ((EMS_RESULT)0x0004B63FL)

//
// MessageId: EMS_MTL_SIT_SERVER_NO_SHORT_NAME
//
// MessageText:
//
// EMS MTL Error:  Cannot find the short name for lut %1.
//
#define EMS_MTL_SIT_SERVER_NO_SHORT_NAME ((EMS_RESULT)0x8004B640L)

//
// MessageId: EMS_MTL_SOAP_NO_HANDLER_THREAD
//
// MessageText:
//
// EMS MTL Trace:  Could not obtain an available SOAP handler thread.
//
#define EMS_MTL_SOAP_NO_HANDLER_THREAD   ((EMS_RESULT)0x0004B641L)

//
// MessageId: EMS_MTL_SOAP_INIT_HANDLER_THREAD
//
// MessageText:
//
// EMS MTL Trace:  Running SOAP handler thread %1.
//
#define EMS_MTL_SOAP_INIT_HANDLER_THREAD ((EMS_RESULT)0x0004B642L)

//
// MessageId: EMS_MTL_BINARY_UNKNOWN
//
// MessageText:
//
// EMS MTL Error:  Unknown error in the binary server.
//
#define EMS_MTL_BINARY_UNKNOWN           ((EMS_RESULT)0x8004B643L)

//
// MessageId: EMS_MTL_SIT_SERVER_UNKNOWN
//
// MessageText:
//
// EMS MTL Error:  Unknown error in the SIT server.
//
#define EMS_MTL_SIT_SERVER_UNKNOWN       ((EMS_RESULT)0x8004B644L)

//
// MessageId: EMS_MTL_TRACK_INSTALL_TIME_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  Unable to find associated pass schedule record for pass summary record.  AOS time will be used for install time on summary record.
//
#define EMS_MTL_TRACK_INSTALL_TIME_NOT_FOUND ((EMS_RESULT)0x8004B645L)

//
// MessageId: EMS_MTL_SIT_SENDER
//
// MessageText:
//
// EMS MTL Info:  Transmission of SIT message file %1 was invoked by user %2.
//
#define EMS_MTL_SIT_SENDER               ((EMS_RESULT)0x8004B646L)

//
// MessageId: EMS_MTL_INVALID_MSG_TYPE
//
// MessageText:
//
// EMS MTL Error:  A request to send a message via an unrecognized type was encountered.
//
#define EMS_MTL_INVALID_MSG_TYPE         ((EMS_RESULT)0x8004B647L)

//
// MessageId: EMS_MTL_NOT_SUPPORTED_MSG_TYPE
//
// MessageText:
//
// EMS MTL Error:  An attempt was made to send a message via an unsupported message type.
//
#define EMS_MTL_NOT_SUPPORTED_MSG_TYPE   ((EMS_RESULT)0x8004B648L)

//
// MessageId: EMS_MTL_UNKNOWN_ENDPOINT
//
// MessageText:
//
// EMS MTL Error:  Unable to retrieve the SOAP endpoint from configuration for a route.
//
#define EMS_MTL_UNKNOWN_ENDPOINT         ((EMS_RESULT)0x8004B649L)

//
// MessageId: EMS_MTL_UNSUPPORTED_INPUT_TYPE
//
// MessageText:
//
// EMS MTL Error:  Data was received in an unsupported format.
//
#define EMS_MTL_UNSUPPORTED_INPUT_TYPE   ((EMS_RESULT)0x8004B64AL)

//
// MessageId: EMS_MTL_ALERT_SUPPRESSED
//
// MessageText:
//
// EMS MTL Info:  %1 alerts have been suppressed.
//
#define EMS_MTL_ALERT_SUPPRESSED         ((EMS_RESULT)0x0004B64BL)

//
// MessageId: EMS_MTL_MISSING_ALIAS
//
// MessageText:
//
// EMS MTL Error:  Route %1 is missing configuration of an alias for one or both endpoints.
//
#define EMS_MTL_MISSING_ALIAS            ((EMS_RESULT)0x8004B64CL)

//
// MessageId: EMS_MTL_RTE_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  The requested route, %1, could not be found in the configuration.
//
#define EMS_MTL_RTE_NOT_FOUND            ((EMS_RESULT)0x8004B64DL)

//
// MessageId: EMS_MTL_SIT_CLIENT_NO_WRAPPER_DEFINITION
//
// MessageText:
//
// EMS MTL Error:  A definition for the wrapper SIT message type <%1> could not be found.
//
#define EMS_MTL_SIT_CLIENT_NO_WRAPPER_DEFINITION ((EMS_RESULT)0x8004B64EL)

//
// MessageId: EMS_MTL_NO_SECURITY_TOKEN_FIELD_DEFINED
//
// MessageText:
//
// EMS MTL Error:  Could not retrieve the SIT message security token field name from configuration.  Searching for key <%1>.<%2>.  CM returned error <%3>.
//
#define EMS_MTL_NO_SECURITY_TOKEN_FIELD_DEFINED ((EMS_RESULT)0x8004B64FL)

//
// MessageId: EMS_MTL_CLIENT_ROUTE_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  MTL Client could not find route with identifier <%1> in configuration.
//
#define EMS_MTL_CLIENT_ROUTE_NOT_FOUND   ((EMS_RESULT)0x8004B650L)

//
// MessageId: EMS_MTL_CLIENT_SOURCE_END_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  While determining transmission message type, the MTL client could not find the sender's endpoint in the specified route.  Sender ID = <%1>, Specified Route = <%2>.
//
#define EMS_MTL_CLIENT_SOURCE_END_NOT_FOUND ((EMS_RESULT)0x8004B651L)

//
// MessageId: EMS_MTL_SIT_CLIENT_TRANS_TABLE_NOT_FOUND
//
// MessageText:
//
// EMS MTL Error:  The translation table <%1> specified in route <%2> could not be found in the configuration.
//
#define EMS_MTL_SIT_CLIENT_TRANS_TABLE_NOT_FOUND ((EMS_RESULT)0x8004B652L)

//
// MessageId: EMS_MTL_SIT_CLIENT_NO_INSTANCE_FOUND
//
// MessageText:
//
// EMS MTL Error:  A referenced instance of name <%1> could not be found in the SIT Message Definition.  There may be an error in the SIT Message Definition.
//
#define EMS_MTL_SIT_CLIENT_NO_INSTANCE_FOUND ((EMS_RESULT)0x8004B653L)

//
// MessageId: EMS_MTL_CONFIGURATION_NO_TRANS_TABLE
//
// MessageText:
//
// EMS MTL Error:  Could not find the translation table named <%1> in the configuration.  A route may may be configured incorrectly.
//
#define EMS_MTL_CONFIGURATION_NO_TRANS_TABLE ((EMS_RESULT)0x8004B654L)

//
// MessageId: EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE
//
// MessageText:
//
// EMS MTL Error:  Could not find the entry <%1> in the translation table named <%2> in the configuration.  A route may may be configured incorrectly or the translation table is incomplete.
//
#define EMS_MTL_CONFIGURATION_NO_TRANS_IN_TABLE ((EMS_RESULT)0x8004B655L)

//
// MessageId: EMS_MTL_SIT_CLIENT_XMIT_TIME_IDENTIFIER_NAME_RETRIEVE_ERROR
//
// MessageText:
//
// EMS MTL Error:  The SIT Client was unable to obtain the identifier of the transmit time message field.
//
#define EMS_MTL_SIT_CLIENT_XMIT_TIME_IDENTIFIER_NAME_RETRIEVE_ERROR ((EMS_RESULT)0x8004B656L)

//
// MessageId: EMS_MTL_SIT_CLIENT_XMIT_TIME_FIELD_OBJECT_RETRIEVE_ERROR
//
// MessageText:
//
// EMS MTL Error:  The SIT Client was unable to obtain the <%1> message field from the object model.
//
#define EMS_MTL_SIT_CLIENT_XMIT_TIME_FIELD_OBJECT_RETRIEVE_ERROR ((EMS_RESULT)0x8004B657L)

//
// MessageId: EMS_MTL_UDP_CONNECT_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client could not connect to the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_CONNECT_ERROR        ((EMS_RESULT)0x8004B658L)

//
// MessageId: EMS_MTL_UDP_INIT_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client could not be initialized.
//
#define EMS_MTL_UDP_INIT_ERROR           ((EMS_RESULT)0x8004B659L)

//
// MessageId: EMS_MTL_UDP_SEND_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client could not send data to the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_SEND_ERROR           ((EMS_RESULT)0x8004B65AL)

//
// MessageId: EMS_MTL_UDP_RECV_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client could not recive data from the LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_RECV_ERROR           ((EMS_RESULT)0x8004B65BL)

//
// MessageId: EMS_MTL_UDP_DISCONNECT_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client disconnect error; LUT <%1>, IP=<%2> Port=<%3>.
//
#define EMS_MTL_UDP_DISCONNECT_ERROR     ((EMS_RESULT)0x8004B65CL)

//
// MessageId: EMS_MTL_UDP_SETPARAM_ERROR
//
// MessageText:
//
// EMS MTL Error:  UDP Client could not set the parameters.
//
#define EMS_MTL_UDP_SETPARAM_ERROR       ((EMS_RESULT)0x8004B65DL)

//
// MessageId: EMS_MTL_RTE_NOT_FOUND_B
//
// MessageText:
//
// EMS MTL Error:  The requested route, between <%1> and <%2>, could not be found in the configuration.
//
#define EMS_MTL_RTE_NOT_FOUND_B          ((EMS_RESULT)0x8004B65EL)

//
// MessageId: EMS_MTL_SOAP_SERVER_INIT_STATS
//
// MessageText:
//
// EMS MTL Trace:  Socket connection successful.  Listening on port %1.  Master socket:  %2  Max backlog queue size:  %3.
//
#define EMS_MTL_SOAP_SERVER_INIT_STATS   ((EMS_RESULT)0x0004B65FL)

//
// MessageId: EMS_MTL_EXCEPTION_UNHANDLED
//
// MessageText:
//
// EMS MTL unhandled exception has occurred.
//
#define EMS_MTL_EXCEPTION_UNHANDLED      ((EMS_RESULT)0x8004B660L)

//
// MessageId: EMS_MTL_UDP_SERVER_LISTENING
//
// MessageText:
//
// EMS MTL Info:  UDP Server listening at IP <%1>, port <%2>.
//
#define EMS_MTL_UDP_SERVER_LISTENING     ((EMS_RESULT)0x0004B661L)

//
// MessageId: EMS_MTL_UDP_SERVER_LISTENING_FAILURE
//
// MessageText:
//
// EMS MTL Error:  UDP Server failed to bind socket for listening at IP <%1>, port <%2>.  Socket error code is <%3>.
//
#define EMS_MTL_UDP_SERVER_LISTENING_FAILURE ((EMS_RESULT)0x8004B662L)

//
// MessageId: EMS_MTL_UDP_SERVER_RECEIVED
//
// MessageText:
//
// EMS MTL Trace:  UDP Server received data or connection attempt from IP <%1>, port <%2>.
//
#define EMS_MTL_UDP_SERVER_RECEIVED      ((EMS_RESULT)0x0004B663L)

//
// MessageId: EMS_MTL_UDP_SERVER_NEW_CONNECTION
//
// MessageText:
//
// EMS MTL Info:  New connection established on UDP Server from IP <%1>, LUT ID <%2>.  Server will respond to client's port <%3>.  <%4> of maximum <%5> connections in use.
//
#define EMS_MTL_UDP_SERVER_NEW_CONNECTION ((EMS_RESULT)0x0004B664L)

//
// MessageId: EMS_MTL_UDP_SERVER_CONNECTION_LIMIT_REACHED
//
// MessageText:
//
// EMS MTL Info:  UDP Server received a connection attempt from IP <%1>, LUT ID <%2>, but client connection limit of <%3> has been reached.
//
#define EMS_MTL_UDP_SERVER_CONNECTION_LIMIT_REACHED ((EMS_RESULT)0x8004B665L)

//
// MessageId: EMS_MTL_UDP_SERVER_CONNECTION_CLOSED
//
// MessageText:
//
// EMS MTL Info:  UDP Server closing connection to IP <%1>, port <%2>, LUT ID <%3>.  <%4> of maximum <%5> connections in use.
//
#define EMS_MTL_UDP_SERVER_CONNECTION_CLOSED ((EMS_RESULT)0x0004B666L)

//
// MessageId: EMS_MTL_SOAP_SERVER_AUDIO_NEW_CONNECTION
//
// MessageText:
//
// EMS MTL Info:  New audio data connection established on SOAP Server from IP <%1>, LUT ID <%2>.
//
#define EMS_MTL_SOAP_SERVER_AUDIO_NEW_CONNECTION ((EMS_RESULT)0x0004B667L)

//
// MessageId: EMS_MTL_SOAP_SERVER_AUDIO_CONNECTION_CLOSED
//
// MessageText:
//
// EMS MTL Info:  SOAP Server closing connection to IP <%1>, LUT ID <%2>.
//
#define EMS_MTL_SOAP_SERVER_AUDIO_CONNECTION_CLOSED ((EMS_RESULT)0x0004B668L)

//
// MessageId: EMS_MTL_INVALID_EPHEMERIS
//
// MessageText:
//
// EMS MTL Received an invalid ephemeris in SIT218 for satellite <%1>.
//
#define EMS_MTL_INVALID_EPHEMERIS        ((EMS_RESULT)0x8004B669L)


#endif // INC_MTLMSGS
#ifndef INC_CCMSGS
#define INC_CCMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_CC_BASE_CODE
//
// MessageText:
//
// EMS Command and Control Error
//
#define EMS_CC_BASE_CODE                 ((EMS_RESULT)0x8004BA00L)

//
// MessageId: EMS_CC_SERVICE_START
//
// MessageText:
//
// EMS Command and Control Service Started
//
#define EMS_CC_SERVICE_START             ((EMS_RESULT)0x0004BA01L)

//
// MessageId: EMS_CC_SERVICE_STOP
//
// MessageText:
//
// EMS Command and Control Service Stopped
//
#define EMS_CC_SERVICE_STOP              ((EMS_RESULT)0x0004BA02L)

//
// MessageId: EMS_CC_EXCEPTION
//
// MessageText:
//
// EMS Command and Control Exception thrown: %1
//
#define EMS_CC_EXCEPTION                 ((EMS_RESULT)0x8004BA03L)

//
// MessageId: EMS_CC_CMD_SHUTDOWN
//
// MessageText:
//
// EMS Command and Control - Received Shutdown Command
//
#define EMS_CC_CMD_SHUTDOWN              ((EMS_RESULT)0x0004BA04L)

//
// MessageId: EMS_CC_CMD_LUT_STARTUP
//
// MessageText:
//
// EMS Command and Control - Received Startup notification from LUT: %1
//
#define EMS_CC_CMD_LUT_STARTUP           ((EMS_RESULT)0x0004BA05L)

//
// MessageId: EMS_CC_BADPROCESS
//
// MessageText:
//
// EMS Command and Control - Unable to Open Process: %1
//
#define EMS_CC_BADPROCESS                ((EMS_RESULT)0x8004BA06L)

//
// MessageId: EMS_CC_PROCESS_NO_START
//
// MessageText:
//
// EMS Command and Control - Unable to Start Process: %1
//
#define EMS_CC_PROCESS_NO_START          ((EMS_RESULT)0x8004BA07L)

//
// MessageId: EMS_CC_PROCESS_STOPPED
//
// MessageText:
//
// EMS Command and Control - Process %1 stopped.  Attempting to restart.
//
#define EMS_CC_PROCESS_STOPPED           ((EMS_RESULT)0x8004BA08L)

//
// MessageId: EMS_CC_PROCESS_RESTARTED
//
// MessageText:
//
// EMS Command and Control - Process %1 has been restarted.
//
#define EMS_CC_PROCESS_RESTARTED         ((EMS_RESULT)0x8004BA09L)

//
// MessageId: EMS_CC_SYSTEM_STARTED
//
// MessageText:
//
// EMS Command and Control - Reports System Started.
//
#define EMS_CC_SYSTEM_STARTED            ((EMS_RESULT)0x0004BA0AL)

//
// MessageId: EMS_CC_TRACER
//
// MessageText:
//
// EMS Command and Control - Trace %1.
//
#define EMS_CC_TRACER                    ((EMS_RESULT)0x0004BA0BL)

//
// MessageId: EMS_CC_WARMRESTART
//
// MessageText:
//
// EMS Command and Control - Warm Restart Commanded.
//
#define EMS_CC_WARMRESTART               ((EMS_RESULT)0x0004BA0CL)

//
// MessageId: EMS_CC_BAD_ORBIT_DATA
//
// MessageText:
//
// EMS Command and Control - Reports orbit vectors error for %1.
//
#define EMS_CC_BAD_ORBIT_DATA            ((EMS_RESULT)0x8004BA0DL)

//
// MessageId: EMS_CC_BAD_SATINFOEX_INTERFACE
//
// MessageText:
//
// EMS Command and Control - Unable to get IEMSSatelliteInfoEx interface %1.
//
#define EMS_CC_BAD_SATINFOEX_INTERFACE   ((EMS_RESULT)0x8004BA0EL)

//
// MessageId: EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE
//
// MessageText:
//
// EMS Command and Control - Unable to get satellite tolerance information %1.
//
#define EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE ((EMS_RESULT)0x8004BA0FL)

//
// MessageId: EMS_CC_SERVICESTARTERR
//
// MessageText:
//
// EMS Command and Control - Unable to start service %1 
//
#define EMS_CC_SERVICESTARTERR           ((EMS_RESULT)0x8004BA10L)

//
// MessageId: EMS_CC_SERVICENOTINITIALIZED
//
// MessageText:
//
// EMS Command and Control - Specified service (%1) has not been initialized 
//
#define EMS_CC_SERVICENOTINITIALIZED     ((EMS_RESULT)0x8004BA11L)

//
// MessageId: EMS_CC_SERVICEWAITTIMEOUT
//
// MessageText:
//
// EMS Command and Control - Wait timeout on service (%1)
//
#define EMS_CC_SERVICEWAITTIMEOUT        ((EMS_RESULT)0x8004BA12L)

//
// MessageId: EMS_CC_SERVICESTOPPED
//
// MessageText:
//
// EMS Command and Control - Service stopped (%1)
//
#define EMS_CC_SERVICESTOPPED            ((EMS_RESULT)0x8004BA13L)

//
// MessageId: EMS_CC_EXCEPTION_TRACE
//
// MessageText:
//
// EMS Command and Cntrol - Exception thrown: File: %1 Line: %2 hr = %3
//
#define EMS_CC_EXCEPTION_TRACE           ((EMS_RESULT)0x8004BA14L)

//
// MessageId: EMS_CC_FILEDELETE_ERR
//
// MessageText:
//
// EMS Command and Cntrol - Unable to delete file %1 with error %2
//
#define EMS_CC_FILEDELETE_ERR            ((EMS_RESULT)0x8004BA15L)

//
// MessageId: EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE_ERR
//
// MessageText:
//
// EMS Command and Control - Unable to get satellite tolerance information hr=%1.
//
#define EMS_CC_SATELLITE_TOLERANCES_UNAVAILABLE_ERR ((EMS_RESULT)0x8004BA16L)

//
// MessageId: EMS_CC_BAD_SATINFOEX_INTERFACE_ERR
//
// MessageText:
//
// EMS Command and Control - Unable to get IEMSSatelliteInfoEx interface hr=%1.
//
#define EMS_CC_BAD_SATINFOEX_INTERFACE_ERR ((EMS_RESULT)0x8004BA17L)

//
// MessageId: EMS_CC_BAD_ORBIT_DATA_DETAILS
//
// MessageText:
//
// EMS Command and Control - Reports orbit vectors error for Lut =%1, Sat=%2, PosErr=%3, VelErr=%4, MaxPosErr=%5, MaxVelErr=%6.
//
#define EMS_CC_BAD_ORBIT_DATA_DETAILS    ((EMS_RESULT)0x8004BA18L)

//
// MessageId: EMS_CC_BAD_INVALIDSITCONTROLCODE
//
// MessageText:
//
// EMS Command and Control - Invalid SIT Control Code
//
#define EMS_CC_BAD_INVALIDSITCONTROLCODE ((EMS_RESULT)0x8004BA19L)

//
// MessageId: EMS_CC_INVALIDFILESPEC
//
// MessageText:
//
// EMS Command and Control - Message: %1 to: %2 does not exist.
//
#define EMS_CC_INVALIDFILESPEC           ((EMS_RESULT)0x8004BA1AL)

//
// MessageId: EMS_CC_PASSSCHED_NOTIMPLEMENTED
//
// MessageText:
//
// Cannot install pass schedule on a LUT Service.
//
#define EMS_CC_PASSSCHED_NOTIMPLEMENTED  ((EMS_RESULT)0x8004BA1BL)

//
// MessageId: EMS_CC_PASSSCHEDBADCMD
//
// MessageText:
//
// Unrecognized Pass Schedule Command.
//
#define EMS_CC_PASSSCHEDBADCMD           ((EMS_RESULT)0x8004BA1CL)

//
// MessageId: EMS_CC_CONFIGITEM_NOTFOUND
//
// MessageText:
//
// Unable to find config item Group: %1 GroupID: %2 Key: %3.
//
#define EMS_CC_CONFIGITEM_NOTFOUND       ((EMS_RESULT)0x8004BA1DL)

//
// MessageId: EMS_CC_INVALID_SEL_CRITERIA
//
// MessageText:
//
// Selection criteria parameter invalid.
//
#define EMS_CC_INVALID_SEL_CRITERIA      ((EMS_RESULT)0x8004BA1EL)

//
// MessageId: EMS_CC_INVALID_ORBITVECTOR
//
// MessageText:
//
// Invalid Orbit Vector.
//
#define EMS_CC_INVALID_ORBITVECTOR       ((EMS_RESULT)0x8004BA1FL)

//
// MessageId: EMS_CC_SERVICE_EX_START
//
// MessageText:
//
// EMS Command and Control %1 Started
//
#define EMS_CC_SERVICE_EX_START          ((EMS_RESULT)0x0004BA20L)

//
// MessageId: EMS_CC_SERVICE_EX_STOP
//
// MessageText:
//
// EMS Command and Control %1 Stopped
//
#define EMS_CC_SERVICE_EX_STOP           ((EMS_RESULT)0x0004BA21L)

//
// MessageId: EMS_CC_SYSTEM_EX_STARTED
//
// MessageText:
//
// EMS Command and Control - Reports %1 Started.
//
#define EMS_CC_SYSTEM_EX_STARTED         ((EMS_RESULT)0x0004BA22L)

//
// MessageId: EMS_CC_SERVICE_STATUS_FAILED
//
// MessageText:
//
// EMS Command and Control - Unable to retrieve service status for %1.  Windows error code %2.
//
#define EMS_CC_SERVICE_STATUS_FAILED     ((EMS_RESULT)0x8004BA23L)

//
// MessageId: EMS_CC_SERVICE_FAILED_TO_GET_CONFG
//
// MessageText:
//
// EMS Command and Control - Unable to retrieve the list of managed services from configuration.
//
#define EMS_CC_SERVICE_FAILED_TO_GET_CONFG ((EMS_RESULT)0x8004BA24L)


#endif // INC_CCMSGS
#ifndef INC_LMMSGS
#define INC_LMMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_LM_BASE_CODE
//
// MessageText:
//
// EMS LUT Monitor Error
//
#define EMS_LM_BASE_CODE                 ((EMS_RESULT)0x8004C500L)

//
// MessageId: EMS_LM_SERVICE_START
//
// MessageText:
//
// EMS LUT Monitor Service Started
//
#define EMS_LM_SERVICE_START             ((EMS_RESULT)0x0004C501L)

//
// MessageId: EMS_LM_SERVICE_STOP
//
// MessageText:
//
// EMS LUT Monitor Service Stopped.
//
#define EMS_LM_SERVICE_STOP              ((EMS_RESULT)0x0004C502L)

//
// MessageId: EMS_LM_EXCEPTION
//
// MessageText:
//
// EMS LUT Monitor Exception thrown: %1
//
#define EMS_LM_EXCEPTION                 ((EMS_RESULT)0x8004C503L)

//
// MessageId: EMS_LM_COMM_CHECK_FAIL
//
// MessageText:
//
// EMS LUT Monitor - Comms check failed, LUT: %1
//
#define EMS_LM_COMM_CHECK_FAIL           ((EMS_RESULT)0x8004C504L)

//
// MessageId: EMS_LM_FAILED_CONFIGLUTGET
//
// MessageText:
//
// Unable to retrieve configured LUTs list.
//
#define EMS_LM_FAILED_CONFIGLUTGET       ((EMS_RESULT)0x8004C505L)

//
// MessageId: EMS_LM_NULLGROUPID
//
// MessageText:
//
// NULL Group ID returned.
//
#define EMS_LM_NULLGROUPID               ((EMS_RESULT)0x8004C506L)


#endif // INC_DACMSGS
/********************************************************************
*	Module:			GWayMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS600GatewayService Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2002-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	2002 Oct 8		rvw	start 

********************************************************************/
#ifndef INC_GWAYMSGS
#define INC_GWAYMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_GWAY_BASE_CODE
//
// MessageText:
//
// EMS Gateway Error
//
#define EMS_GWAY_BASE_CODE               ((EMS_RESULT)0x8004B500L)

//
// MessageId: EMS_GWAY_SERVICE_START
//
// MessageText:
//
// EMS Gateway Service Started
//
#define EMS_GWAY_SERVICE_START           ((EMS_RESULT)0x0004B501L)

//
// MessageId: EMS_GWAY_SERVICE_FAILED
//
// MessageText:
//
// EMS Gateway Service did not start due to error %1
//
#define EMS_GWAY_SERVICE_FAILED          ((EMS_RESULT)0x8004B502L)

//
// MessageId: EMS_GWAY_SERVICE_STOP
//
// MessageText:
//
// EMS Gateway Service Stopped
//
#define EMS_GWAY_SERVICE_STOP            ((EMS_RESULT)0x0004B503L)

//
// MessageId: EMS_GWAY_ERROR
//
// MessageText:
//
// EMS Gateway reports error %1.
//
#define EMS_GWAY_ERROR                   ((EMS_RESULT)0x8004B504L)

//
// MessageId: EMS_GWAY_LOG_EXCEPTION
//
// MessageText:
//
// EMS Gateway reports an exception
//
#define EMS_GWAY_LOG_EXCEPTION           ((EMS_RESULT)0x8004B505L)

//
// MessageId: EMS_GWAY_SIT_UNKNOWN
//
// MessageText:
//
// EMS Gateway : Unknown SitMsg %1 ignored ( File=%2 ).
//
#define EMS_GWAY_SIT_UNKNOWN             ((EMS_RESULT)0x8004B506L)

//
// MessageId: EMS_GWAY_SIT_ERR
//
// MessageText:
//
// EMS Gateway : Error while processing SitMsg %1 ( File=%2, Error=%3 ).
//
#define EMS_GWAY_SIT_ERR                 ((EMS_RESULT)0x8004B507L)

//
// MessageId: EMS_GWAY_SIT415
//
// MessageText:
//
// EMS Gateway : SitMsg415 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT415                  ((EMS_RESULT)0x0004B508L)

//
// MessageId: EMS_GWAY_SIT510
//
// MessageText:
//
// EMS Gateway : SitMsg510 processed ( Sat=%1, FreqOffset=%2 ). 
//
#define EMS_GWAY_SIT510                  ((EMS_RESULT)0x0004B509L)

//
// MessageId: EMS_GWAY_SIT_UNEXPECTED
//
// MessageText:
//
// EMS Gateway : SitMsg %1 was unexpected ( File=%2 ). 
//
#define EMS_GWAY_SIT_UNEXPECTED          ((EMS_RESULT)0x8004B50AL)

//
// MessageId: EMS_GWAY_SIT255
//
// MessageText:
//
// EMS Gateway : SitMsg255 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT255                  ((EMS_RESULT)0x0004B50BL)

//
// MessageId: EMS_GWAY_SIT215
//
// MessageText:
//
// EMS Gateway : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_GWAY_SIT215                  ((EMS_RESULT)0x0004B50CL)

//
// MessageId: EMS_GWAY_NEW_ORBIT_VECTOR
//
// MessageText:
//
// EMS Gateway installed new orbit vectors for Sat ID %1 ( , posErr, velErr ).
//
#define EMS_GWAY_NEW_ORBIT_VECTOR        ((EMS_RESULT)0x0004B50DL)

//
// MessageId: EMS_GWAY_ERR_ORBIT_VECTOR
//
// MessageText:
//
// EMS Gateway reports orbit vectors error for Sat ID %1 ( , posErr, velErr ).
//
#define EMS_GWAY_ERR_ORBIT_VECTOR        ((EMS_RESULT)0x8004B50EL)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV
//
// MessageText:
//
// EMS Gateway received SitMsg %1 from %2.
//
#define EMS_GWAY_SIT_MSG_RECV            ((EMS_RESULT)0x0004B50FL)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV_UNKNOWNFILE
//
// MessageText:
//
// EMS Gateway received SitMsg with unknown filename from %1.
//
#define EMS_GWAY_SIT_MSG_RECV_UNKNOWNFILE ((EMS_RESULT)0x0004B510L)

//
// MessageId: EMS_GWAY_SIT_MSG_RECV_BYTESTREAM
//
// MessageText:
//
// EMS Gateway received SitMsg as a byte stream from %1.
//
#define EMS_GWAY_SIT_MSG_RECV_BYTESTREAM ((EMS_RESULT)0x0004B511L)

//
// MessageId: EMS_GWAY_NO_SYSTEST_TIME
//
// MessageText:
//
// EMS Gateway reports insufficient time for system test.
//
#define EMS_GWAY_NO_SYSTEST_TIME         ((EMS_RESULT)0x0004B512L)

//
// MessageId: EMS_GWAY_PASS_IN_PROGRESS
//
// MessageText:
//
// EMS Gateway is currently processing a pass.
//
#define EMS_GWAY_PASS_IN_PROGRESS        ((EMS_RESULT)0x0004B513L)

//
// MessageId: EMS_GWAY_CONNECTION_RECVD
//
// MessageText:
//
// EMS Gateway received a connection from %1.
//
#define EMS_GWAY_CONNECTION_RECVD        ((EMS_RESULT)0x0004B514L)

//
// MessageId: EMS_GWAY_DISCONNECTION_RECVD
//
// MessageText:
//
// EMS Gateway:  Client disconnected.
//
#define EMS_GWAY_DISCONNECTION_RECVD     ((EMS_RESULT)0x0004B515L)

//
// MessageId: EMS_GWAY_SEND_COMMAND
//
// MessageText:
//
// EMS Gateway received command to send to destination %1.
//
#define EMS_GWAY_SEND_COMMAND            ((EMS_RESULT)0x0004B516L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_RECVD
//
// MessageText:
//
// EMS Gateway successfully added a client identified by (%1) to the list of incoming message subscribers.
//
#define EMS_GWAY_SUBSCRIPTION_RECVD      ((EMS_RESULT)0x0004B517L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_FAILED
//
// MessageText:
//
// EMS Gateway reports an error adding a client to its list of incoming message subscribers.
//
#define EMS_GWAY_SUBSCRIPTION_FAILED     ((EMS_RESULT)0x8004B518L)

//
// MessageId: EMS_GWAY_SUBSCRIPTION_CANCELLED
//
// MessageText:
//
// EMS Gateway reports incoming message subscription cancelled by client (%1).
//
#define EMS_GWAY_SUBSCRIPTION_CANCELLED  ((EMS_RESULT)0x0004B519L)

//
// MessageId: EMS_GWAY_CMD_SENT
//
// MessageText:
//
// EMS Gateway reports successfully sending command:  %1.
//
#define EMS_GWAY_CMD_SENT                ((EMS_RESULT)0x0004B51AL)

//
// MessageId: EMS_GWAY_CMD_SEND_FAIL
//
// MessageText:
//
// EMS Gateway reports failure sending command:  %1.
//
#define EMS_GWAY_CMD_SEND_FAIL           ((EMS_RESULT)0x8004B51BL)

//
// MessageId: EMS_GWAY_NOTIFY_TIMEOUT
//
// MessageText:
//
// EMS Gateway reports that a notification call to a subscriber timed out after %1 seconds.  The thread was terminated.
//
#define EMS_GWAY_NOTIFY_TIMEOUT          ((EMS_RESULT)0x8004B51CL)

//
// MessageId: EMS_GWAY_NO_CMD_CHANNEL
//
// MessageText:
//
// EMS Gateway reports that it cannot establish a command channel to Master.
//
#define EMS_GWAY_NO_CMD_CHANNEL          ((EMS_RESULT)0x8004B51DL)

//
// MessageId: EMS_GWAY_CMD_RECV_FAIL
//
// MessageText:
//
// EMS Gateway reports failure receiving message:  %1.
//
#define EMS_GWAY_CMD_RECV_FAIL           ((EMS_RESULT)0x8004B51EL)

//
// MessageId: EMS_GWAY_TRACE_MSG
//
// MessageText:
//
// EMS Gateway trace message:  %1.
//
#define EMS_GWAY_TRACE_MSG               ((EMS_RESULT)0x0004B51FL)

//
// MessageId: EMS_GWAY_BROADCAST_EXCEPTION
//
// MessageText:
//
// EMS Gateway reports an exception while notifying a subscriber.
//
#define EMS_GWAY_BROADCAST_EXCEPTION     ((EMS_RESULT)0x8004B520L)

//
// MessageId: EMS_GWAY_RESOURCE_DISABLED
//
// MessageText:
//
// EMS Gateway reports attempt to locally access unavailable resource %1.
//
#define EMS_GWAY_RESOURCE_DISABLED       ((EMS_RESULT)0x8004B521L)

//
// MessageId: EMS_GWAY_ACCESS_DENIED
//
// MessageText:
//
// EMS Gateway reports denial of access to resource %1 due to authorization failure.
//
#define EMS_GWAY_ACCESS_DENIED           ((EMS_RESULT)0x8004B522L)

//
// MessageId: EMS_GWAY_SERIAL_ACCESS_REQUIRED
//
// MessageText:
//
// EMS Gateway reports attempt to use command or data channel to invoke resource %1 while not in serialized mode.
//
#define EMS_GWAY_SERIAL_ACCESS_REQUIRED  ((EMS_RESULT)0x8004B523L)

//
// MessageId: EMS_GWAY_CONFIG_NOT_FOUND
//
// MessageText:
//
// EMS Gateway reports failed attempt to find configuration data for key = %1 and value = %2.
//
#define EMS_GWAY_CONFIG_NOT_FOUND        ((EMS_RESULT)0x8004B524L)

//
// MessageId: EMS_GWAY_UNKNOWN_RESPONSE
//
// MessageText:
//
// EMS Gateway reports an unknown response command received.
//
#define EMS_GWAY_UNKNOWN_RESPONSE        ((EMS_RESULT)0x8004B525L)

//
// MessageId: EMS_GWAY_PIPE_COMMAND_TIMEOUT
//
// MessageText:
//
// EMS Gateway reports a timeout waiting for a command response on the EMSPipeline.
//
#define EMS_GWAY_PIPE_COMMAND_TIMEOUT    ((EMS_RESULT)0x8004B526L)

//
// MessageId: EMS_GWAY_CONFIG_NO_RES_TRANS_TABLE
//
// MessageText:
//
// EMS Gateway reports that the resource translation table for lut %1 could not be found in the configuration.
//
#define EMS_GWAY_CONFIG_NO_RES_TRANS_TABLE ((EMS_RESULT)0x8004B527L)

//
// MessageId: EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED
//
// MessageText:
//
// EMS Gateway reports that while constructing a pipeline command string the maximum length was reached.
//
#define EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED ((EMS_RESULT)0x8004B528L)

//
// MessageId: EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS
//
// MessageText:
//
// EMS Gateway reports that the maximum number of LUTs (%1) from which data can be simultaneously manually recovered has been exceeded.
//
#define EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS ((EMS_RESULT)0x8004B529L)

//
// MessageId: EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES
//
// MessageText:
//
// EMS Gateway reports that the maximum number of Datatypes (%1) for which data can be simultaneously manually recovered has been exceeded.
//
#define EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES ((EMS_RESULT)0x8004B52AL)

//
// MessageId: EMS_GWAY_DAL_QUERY_TIMEOUT
//
// MessageText:
//
// EMS Gateway reports that a query executed on the DAL has timed out.  The query has been cancelled.
//
#define EMS_GWAY_DAL_QUERY_TIMEOUT       ((EMS_RESULT)0x8004B52BL)

//
// MessageId: EMS_GWAY_UNKNOWN_TARGET_LOCATION
//
// MessageText:
//
// EMS Gateway reports a problem determining whether a target location is local or remote.
//
#define EMS_GWAY_UNKNOWN_TARGET_LOCATION ((EMS_RESULT)0x8004B52CL)

//
// MessageId: EMS_GWAY_BAD_IMPL_POINTER
//
// MessageText:
//
// EMS Gateway reports an invalid pointer to the Gateway %1 implementation.
//
#define EMS_GWAY_BAD_IMPL_POINTER        ((EMS_RESULT)0x8004B52DL)

//
// MessageId: EMS_GWAY_CSSHORTNAME
//
// MessageText:
//
// C-S Short Name
//
#define EMS_GWAY_CSSHORTNAME             ((EMS_RESULT)0x0004B52EL)

//
// MessageId: EMS_GWAY_LOCALCALL
//
// MessageText:
//
// EMS Gateway trace message:  Local call
//
#define EMS_GWAY_LOCALCALL               ((EMS_RESULT)0x0004B52FL)

//
// MessageId: EMS_GWAY_REMOTECALL
//
// MessageText:
//
// EMS Gateway trace message:  Remote call
//
#define EMS_GWAY_REMOTECALL              ((EMS_RESULT)0x0004B530L)

//
// MessageId: EMS_GWAY_KERNELMSG
//
// MessageText:
//
// EMS Gateway trace message:  Message is from kernel
//
#define EMS_GWAY_KERNELMSG               ((EMS_RESULT)0x0004B531L)

//
// MessageId: EMS_GWAY_NONKERNELMSG
//
// MessageText:
//
// EMS Gateway trace message:  Message is not from kernel
//
#define EMS_GWAY_NONKERNELMSG            ((EMS_RESULT)0x0004B532L)

//
// MessageId: EMS_GWAY_PROCESSEDDIR
//
// MessageText:
//
// EMS Gateway trace message:  Processed dir=%1
//
#define EMS_GWAY_PROCESSEDDIR            ((EMS_RESULT)0x0004B533L)

//
// MessageId: EMS_GWAY_FILEPATH
//
// MessageText:
//
// EMS Gateway trace message:  File path =%1
//
#define EMS_GWAY_FILEPATH                ((EMS_RESULT)0x0004B534L)

//
// MessageId: EMS_GWAY_SENDINGPROCESSFILECMD
//
// MessageText:
//
// EMS Gateway trace message:  Sending command to process file to Master
//
#define EMS_GWAY_SENDINGPROCESSFILECMD   ((EMS_RESULT)0x0004B535L)

//
// MessageId: EMS_GWAY_BROADCASTING
//
// MessageText:
//
// EMS Gateway trace message:  Broadcasting message to subscribers
//
#define EMS_GWAY_BROADCASTING            ((EMS_RESULT)0x0004B536L)

//
// MessageId: EMS_GWAY_BROADCASTINGCOUNT
//
// MessageText:
//
// EMS Gateway trace message:  Broadcasting to %1 subscribers
//
#define EMS_GWAY_BROADCASTINGCOUNT       ((EMS_RESULT)0x0004B537L)

//
// MessageId: EMS_GWAY_CONVERTSITFAILED
//
// MessageText:
//
// EMS Gateway trace message:  Failed to convert SIT into a file.
//
#define EMS_GWAY_CONVERTSITFAILED        ((EMS_RESULT)0x0004B538L)

//
// MessageId: EMS_GWAY_BROADCASTOK
//
// MessageText:
//
// EMS Gateway trace message:  Broadcast thread completed succesfully.
//
#define EMS_GWAY_BROADCASTOK             ((EMS_RESULT)0x0004B539L)

//
// MessageId: EMS_GWAY_SUBSCRIBERREMOVED
//
// MessageText:
//
// EMS Gateway trace message:  Subscriber at index %1 being removed due to a failure during notification.
//
#define EMS_GWAY_SUBSCRIBERREMOVED       ((EMS_RESULT)0x0004B53AL)

//
// MessageId: EMS_GWAY_LUTIDENT
//
// MessageText:
//
// EMS Gateway trace message:  This LUT ID is %1
//
#define EMS_GWAY_LUTIDENT                ((EMS_RESULT)0x0004B53BL)

//
// MessageId: EMS_GWAY_BROADCASTTIMEOUT
//
// MessageText:
//
// EMS Gateway trace message:  Broadcast timeout = %1 seconds
//
#define EMS_GWAY_BROADCASTTIMEOUT        ((EMS_RESULT)0x0004B53CL)

//
// MessageId: EMS_GWAY_MASTERSENDON
//
// MessageText:
//
// EMS Gateway trace message:  Send to Master enabled
//
#define EMS_GWAY_MASTERSENDON            ((EMS_RESULT)0x0004B53DL)

//
// MessageId: EMS_GWAY_MASTERSENDOFF
//
// MessageText:
//
// EMS Gateway trace message:  Send to Master disabled
//
#define EMS_GWAY_MASTERSENDOFF           ((EMS_RESULT)0x0004B53EL)

//
// MessageId: EMS_GWAY_BYPASSINGMASTER
//
// MessageText:
//
// EMS Gateway trace message:  Bypassing transmission of msg file to Master
//
#define EMS_GWAY_BYPASSINGMASTER         ((EMS_RESULT)0x0004B53FL)

//
// MessageId: GWAY_LABEL_IF_UNKNOWN
//
// MessageText:
//
// Unknown
//
#define GWAY_LABEL_IF_UNKNOWN            ((EMS_RESULT)0x0004B540L)

//
// MessageId: GWAY_LABEL_IF_ALERTGEN
//
// MessageText:
//
// Alert Generator
//
#define GWAY_LABEL_IF_ALERTGEN           ((EMS_RESULT)0x0004B541L)

//
// MessageId: GWAY_LABEL_IF_CONFIG
//
// MessageText:
//
// Config Manager
//
#define GWAY_LABEL_IF_CONFIG             ((EMS_RESULT)0x0004B542L)

//
// MessageId: GWAY_LABEL_IF_DAC
//
// MessageText:
//
// Data Acquisition
//
#define GWAY_LABEL_IF_DAC                ((EMS_RESULT)0x0004B543L)

//
// MessageId: GWAY_LABEL_IF_DAL
//
// MessageText:
//
// Data Access Layer
//
#define GWAY_LABEL_IF_DAL                ((EMS_RESULT)0x0004B544L)

//
// MessageId: GWAY_LABEL_IF_LOCATION
//
// MessageText:
//
// Location Processor Controller
//
#define GWAY_LABEL_IF_LOCATION           ((EMS_RESULT)0x0004B545L)

//
// MessageId: GWAY_LABEL_IF_DATAXFER
//
// MessageText:
//
// Data Transfer
//
#define GWAY_LABEL_IF_DATAXFER           ((EMS_RESULT)0x0004B546L)

//
// MessageId: GWAY_LABEL_IF_MCC
//
// MessageText:
//
// MCC
//
#define GWAY_LABEL_IF_MCC                ((EMS_RESULT)0x0004B547L)

//
// MessageId: GWAY_LABEL_IF_ALERTMANAGER
//
// MessageText:
//
// Alert Manager
//
#define GWAY_LABEL_IF_ALERTMANAGER       ((EMS_RESULT)0x0004B548L)

//
// MessageId: GWAY_LABEL_IF_SIT
//
// MessageText:
//
// SIT
//
#define GWAY_LABEL_IF_SIT                ((EMS_RESULT)0x0004B549L)

//
// MessageId: GWAY_LABEL_IF_AUDIO
//
// MessageText:
//
// AUDIO
//
#define GWAY_LABEL_IF_AUDIO              ((EMS_RESULT)0x0004B54AL)

//
// MessageId: GWAY_LABEL_IF_HEALTHSTATUS
//
// MessageText:
//
// Health Status
//
#define GWAY_LABEL_IF_HEALTHSTATUS       ((EMS_RESULT)0x0004B54BL)

//
// MessageId: GWAY_LABEL_IF_LAST
//
// MessageText:
//
//  
//
#define GWAY_LABEL_IF_LAST               ((EMS_RESULT)0x0004B54CL)


#endif // INC_GWAYMSGS
/********************************************************************
*	Module:			DALMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for DAL Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003 Nov 10		jb		start 

********************************************************************/
#ifndef INC_DALMSGS
#define INC_DALMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DAL_BASE_CODE
//
// MessageText:
//
// EMS Data Access Layer Error
//
#define EMS_DAL_BASE_CODE                ((EMS_RESULT)0x0004B900L)

//
// MessageId: EMS_DAL_SERVICE_START
//
// MessageText:
//
// EMS Data Access Layer Service Started
//
#define EMS_DAL_SERVICE_START            ((EMS_RESULT)0x0004B901L)

//
// MessageId: EMS_DAL_SERVICE_FAILED
//
// MessageText:
//
// EMS Data Access Layer Service did not start due to error %1
//
#define EMS_DAL_SERVICE_FAILED           ((EMS_RESULT)0x8004B902L)

//
// MessageId: EMS_DAL_SERVICE_STOP
//
// MessageText:
//
// EMS Data Access Layer Service Stopped
//
#define EMS_DAL_SERVICE_STOP             ((EMS_RESULT)0x0004B903L)

//
// MessageId: EMS_DAL_ERROR
//
// MessageText:
//
// EMS Data Access Layer Error:  %1.
//
#define EMS_DAL_ERROR                    ((EMS_RESULT)0x8004B904L)

//
// MessageId: EMS_DAL_ADO_ERROR
//
// MessageText:
//
// EMS Data Access Layer Error:  An ADO exception has occurred.  %1.
//
#define EMS_DAL_ADO_ERROR                ((EMS_RESULT)0x8004B905L)

//
// MessageId: EMS_DAL_EXCEPTION
//
// MessageText:
//
// EMS Data Access Layer Error:  An exception of an unknown type has occurred. 
//
#define EMS_DAL_EXCEPTION                ((EMS_RESULT)0x8004B906L)

//
// MessageId: EMS_DAL_TYPE_UNEXPECTED
//
// MessageText:
//
// EMS Data Access Layer Error:  The value retrieved for a field had an unexpected type. 
//
#define EMS_DAL_TYPE_UNEXPECTED          ((EMS_RESULT)0x8004B907L)

//
// MessageId: EMS_DAL_UNKOWN_DATATYPE
//
// MessageText:
//
// EMS Data Access Layer Error:  An unknown data type for a database field was encountered.
//
#define EMS_DAL_UNKOWN_DATATYPE          ((EMS_RESULT)0x8004B908L)

//
// MessageId: EMS_DAL_NO_META_DATA
//
// MessageText:
//
// EMS Data Access Layer Error:  Unable to retrieve meta data for a recordset.
//
#define EMS_DAL_NO_META_DATA             ((EMS_RESULT)0x8004B909L)

//
// MessageId: EMS_DAL_UNKNOWN_RECORD_TYPE
//
// MessageText:
//
// EMS Data Access Layer Error:  An unknown record type was encountered.
//
#define EMS_DAL_UNKNOWN_RECORD_TYPE      ((EMS_RESULT)0x8004B90AL)

//
// MessageId: EMS_DAL_UNKNOWN_TABLE
//
// MessageText:
//
// EMS Data Access Layer Error:  A corresponding table name could not be found for the specified data type.
//
#define EMS_DAL_UNKNOWN_TABLE            ((EMS_RESULT)0x8004B90BL)

//
// MessageId: EMS_DAL_CONNECTION
//
// MessageText:
//
// EMS Data Access Layer Info:  Using connection string %1.
//
#define EMS_DAL_CONNECTION               ((EMS_RESULT)0x0004B90CL)

//
// MessageId: EMS_DAL_SQL
//
// MessageText:
//
// EMS Data Access Layer Info:  Using SQL string %1.
//
#define EMS_DAL_SQL                      ((EMS_RESULT)0x0004B90DL)

//
// MessageId: EMS_DAL_SQL_CONSTRUCTION
//
// MessageText:
//
// EMS Data Access Layer Error:  An error occurred while attempting to construct an SQL string.
//
#define EMS_DAL_SQL_CONSTRUCTION         ((EMS_RESULT)0x8004B90EL)

//
// MessageId: EMS_DAL_DELETE_TIMEOUT
//
// MessageText:
//
// EMS Data Access Layer Error:  A delete operation timed out.
//
#define EMS_DAL_DELETE_TIMEOUT           ((EMS_RESULT)0x8004B90FL)

//
// MessageId: EMS_DAL_UNKOWN_OBJECTSTATE
//
// MessageText:
//
// EMS Data Access Layer Error:  An unknown database object state was encountered.
//
#define EMS_DAL_UNKOWN_OBJECTSTATE       ((EMS_RESULT)0x8004B910L)

//
// MessageId: EMS_DAL_RECORDTYPE_UNEXPECTED
//
// MessageText:
//
// EMS Data Access Layer Error:  An unexpected record type was encountered..
//
#define EMS_DAL_RECORDTYPE_UNEXPECTED    ((EMS_RESULT)0x8004B911L)

//
// MessageId: EMS_DAL_QUERY_TIMEOUT
//
// MessageText:
//
// EMS Data Access Layer Error:  A query operation timed out.
//
#define EMS_DAL_QUERY_TIMEOUT            ((EMS_RESULT)0x8004B912L)

//
// MessageId: EMS_DAL_CACHE_RETRIEVAL
//
// MessageText:
//
// EMS Data Access Layer Info:  Caller has requested data from the cache.
//
#define EMS_DAL_CACHE_RETRIEVAL          ((EMS_RESULT)0x0004B913L)

//
// MessageId: EMS_DAL_META_RETRIEVAL
//
// MessageText:
//
// EMS Data Access Layer Info:  Caller has requested meta information.
//
#define EMS_DAL_META_RETRIEVAL           ((EMS_RESULT)0x0004B914L)

//
// MessageId: EMS_DAL_CACHE_LIMIT_REACHED
//
// MessageText:
//
// EMS Data Access Layer Error:  The resultset cache has reached its limit.  Results could not be cached.
//
#define EMS_DAL_CACHE_LIMIT_REACHED      ((EMS_RESULT)0x8004B915L)

//
// MessageId: EMS_DAL_SQL_KEYWORD_VIOLATION
//
// MessageText:
//
// EMS Data Access Layer Error:  An attempt was made to use an SQL statement that may violate the system database's integrity:  %1.
//
#define EMS_DAL_SQL_KEYWORD_VIOLATION    ((EMS_RESULT)0x8004B916L)

//
// MessageId: EMS_DAL_EXCEPTION_UNHANDLED
//
// MessageText:
//
// EMS Data Access Layer Error:  An unhandled exception has occurred.
//
#define EMS_DAL_EXCEPTION_UNHANDLED      ((EMS_RESULT)0x8004B917L)

//
// MessageId: EMS_DAL_QUERY_EXCEPTION
//
// MessageText:
//
// EMS Data Access Layer Error:  An exception occurred while processing a query (SQL: %1) (Error: %2) (Line: %3, %4)
//
#define EMS_DAL_QUERY_EXCEPTION          ((EMS_RESULT)0x8004B918L)


#endif // INC_DALMSGS
/********************************************************************
*	Module:			LPCMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for LocationProcessorController Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Oct02		CH		start 

********************************************************************/
#ifndef INC_LPCMSGS
#define INC_LPCMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_LPC_BASE_CODE
//
// MessageText:
//
// EMS LPC Error
//
#define EMS_LPC_BASE_CODE                ((EMS_RESULT)0x8004B800L)

//
// MessageId: EMS_LPC_SERVICE_START
//
// MessageText:
//
// EMS LPC Service Started
//
#define EMS_LPC_SERVICE_START            ((EMS_RESULT)0x0004B801L)

//
// MessageId: EMS_LPC_SERVICE_FAILED
//
// MessageText:
//
// EMS LPC Service did not start due to error.
//
#define EMS_LPC_SERVICE_FAILED           ((EMS_RESULT)0x8004B802L)

//
// MessageId: EMS_LPC_SERVICE_STOP
//
// MessageText:
//
// EMS LPC Service Stopped
//
#define EMS_LPC_SERVICE_STOP             ((EMS_RESULT)0x0004B803L)

//
// MessageId: EMS_LPC_ERROR
//
// MessageText:
//
// EMS LPC reports error %1.
//
#define EMS_LPC_ERROR                    ((EMS_RESULT)0x8004B804L)

//
// MessageId: EMS_LPC_TRACE_MSG
//
// MessageText:
//
// EMS LPC trace message:  %1.
//
#define EMS_LPC_TRACE_MSG                ((EMS_RESULT)0x0004B805L)

//
// MessageId: EMS_LPC_EXCEPTION
//
// MessageText:
//
// EMS LPC Exception thrown: %1
//
#define EMS_LPC_EXCEPTION                ((EMS_RESULT)0x8004B806L)

//
// MessageId: EMS_LPC_MAX_SESSIONS_REACHED
//
// MessageText:
//
// EMS LPC maximum number of manual sessions reached (%1). Cannot initialize a new session.
//
#define EMS_LPC_MAX_SESSIONS_REACHED     ((EMS_RESULT)0x8004B807L)

//
// MessageId: EMS_LPC_INVALID_SESSION_ID
//
// MessageText:
//
// EMS LPC invalid session id specified: %1
//
#define EMS_LPC_INVALID_SESSION_ID       ((EMS_RESULT)0x8004B808L)

//
// MessageId: EMS_LPC_MANUAL_STARTED
//
// MessageText:
//
// EMS LPC manual session initialized with parameters %1
//
#define EMS_LPC_MANUAL_STARTED           ((EMS_RESULT)0x0004B809L)

//
// MessageId: EMS_LPC_MANUAL_CANCELLED
//
// MessageText:
//
// EMS LPC manual session (%1) ended.
//
#define EMS_LPC_MANUAL_CANCELLED         ((EMS_RESULT)0x0004B80AL)

//
// MessageId: EMS_LPC_MANUAL_DATACOUNT
//
// MessageText:
//
// EMS LPC manual session retrieved %1 records.
//
#define EMS_LPC_MANUAL_DATACOUNT         ((EMS_RESULT)0x0004B80BL)

//
// MessageId: EMS_LPC_MANUAL_REMOVERECORDS
//
// MessageText:
//
// EMS LPC manual session (%1) records removed.
//
#define EMS_LPC_MANUAL_REMOVERECORDS     ((EMS_RESULT)0x0004B80CL)

//
// MessageId: EMS_LPC_MANUAL_PROCESS406
//
// MessageText:
//
// EMS LPC manual session (%1) location processing requested.
//
#define EMS_LPC_MANUAL_PROCESS406        ((EMS_RESULT)0x0004B80DL)

//
// MessageId: EMS_LPC_CONTROLFILELIST
//
// MessageText:
//
// EMS LPC request received for control file list.
//
#define EMS_LPC_CONTROLFILELIST          ((EMS_RESULT)0x0004B80EL)

//
// MessageId: EMS_LPC_CONTROLFILELIST_FAILED
//
// MessageText:
//
// EMS LPC failed to retrieve control file list.
//
#define EMS_LPC_CONTROLFILELIST_FAILED   ((EMS_RESULT)0x8004B80FL)

//
// MessageId: EMS_LPC_FAILEDTOPURGEFILE
//
// MessageText:
//
// EMS LPC failed to purge beacon data file %1
//
#define EMS_LPC_FAILEDTOPURGEFILE        ((EMS_RESULT)0x0004B810L)

//
// MessageId: EMS_LPC_MANUAL_INIT_FAILED
//
// MessageText:
//
// EMS LPC manual session initialization failed WHERE %1
//
#define EMS_LPC_MANUAL_INIT_FAILED       ((EMS_RESULT)0x8004B811L)

//
// MessageId: EMS_LPC_MANUAL_PROCESS406_FAILED
//
// MessageText:
//
// EMS LPC manual session (%1) location processing failed.
//
#define EMS_LPC_MANUAL_PROCESS406_FAILED ((EMS_RESULT)0x8004B812L)

//
// MessageId: EMS_LPC_MANUAL_REMOVERECORDS_FAILED
//
// MessageText:
//
// EMS LPC manual session (%1) remove records failed.
//
#define EMS_LPC_MANUAL_REMOVERECORDS_FAILED ((EMS_RESULT)0x8004B813L)

//
// MessageId: EMS_LPC_MANUAL_CANCEL_FAILED
//
// MessageText:
//
// EMS LPC manual session (%1) cancellation failed.
//
#define EMS_LPC_MANUAL_CANCEL_FAILED     ((EMS_RESULT)0x8004B814L)

//
// MessageId: EMS_LPC_MANUAL_TOMANYRECORDS
//
// MessageText:
//
// EMS LPC manual session initialization attempted to retrieve more than the maximum allowed number of records.
//
#define EMS_LPC_MANUAL_TOMANYRECORDS     ((EMS_RESULT)0x8004B815L)

//
// MessageId: EMS_LPC_PURGING_FILES
//
// MessageText:
//
// EMS LPC purging expired files.
//
#define EMS_LPC_PURGING_FILES            ((EMS_RESULT)0x0004B816L)

//
// MessageId: EMS_LPC_AUTO_REQUESTED_CALIB406
//
// MessageText:
//
// EMS LPC requesting location processing of %1 calib406 beacons.
//
#define EMS_LPC_AUTO_REQUESTED_CALIB406  ((EMS_RESULT)0x0004B817L)

//
// MessageId: EMS_LPC_AUTO_REQUESTED_COMB406
//
// MessageText:
//
// EMS LPC requesting location processing of %1 combine406 beacons.
//
#define EMS_LPC_AUTO_REQUESTED_COMB406   ((EMS_RESULT)0x0004B818L)

//
// MessageId: EMS_LPC_INVALID_DATA_DIRECTORY
//
// MessageText:
//
// EMS LPC failed to access data directory specified by configuration (%1).
//
#define EMS_LPC_INVALID_DATA_DIRECTORY   ((EMS_RESULT)0x8004B819L)

//
// MessageId: EMS_LPC_INITIALIZATION_FAILED
//
// MessageText:
//
// EMS LPC initialization failed.
//
#define EMS_LPC_INITIALIZATION_FAILED    ((EMS_RESULT)0x8004B81AL)

//
// MessageId: EMS_LPC_RECEIVECALIB406_FAILED
//
// MessageText:
//
// EMS LPC Failed while receiving calib406 data for processing.
//
#define EMS_LPC_RECEIVECALIB406_FAILED   ((EMS_RESULT)0x8004B81BL)

//
// MessageId: EMS_LPC_RECEIVECOMB406_FAILED
//
// MessageText:
//
// EMS LPC Failed while receiving combine406 data for processing.
//
#define EMS_LPC_RECEIVECOMB406_FAILED    ((EMS_RESULT)0x8004B81CL)

//
// MessageId: EMS_LPC_GATEWAYRESPONSE_FAILED
//
// MessageText:
//
// EMS LPC Failed to write a response to the gateway.
//
#define EMS_LPC_GATEWAYRESPONSE_FAILED   ((EMS_RESULT)0x8004B81DL)

//
// MessageId: EMS_LPC_FILEPURGED
//
// MessageText:
//
// EMS LPC Beacon data file (%1) purged.
//
#define EMS_LPC_FILEPURGED               ((EMS_RESULT)0x0004B81EL)

//
// MessageId: EMS_LPC_RECEIVECALIB406_SUMMARY
//
// MessageText:
//
// EMS LPC Successfully saved %1 of %2 calib406 records for location processing.
//
#define EMS_LPC_RECEIVECALIB406_SUMMARY  ((EMS_RESULT)0x0004B81FL)

//
// MessageId: EMS_LPC_RECEIVECOMB406_SUMMARY
//
// MessageText:
//
// EMS LPC Successfully saved %1 of %2 combine406 records for location processing.
//
#define EMS_LPC_RECEIVECOMB406_SUMMARY   ((EMS_RESULT)0x0004B820L)

//
// MessageId: EMS_LPC_NOBEACONSTOPROCESS
//
// MessageText:
//
// EMS LPC Automatic location processing detected no beacons ready for processing.
//
#define EMS_LPC_NOBEACONSTOPROCESS       ((EMS_RESULT)0x0004B821L)

//
// MessageId: EMS_LPC_AUTOMATIC_PROCESSING_FAILED
//
// MessageText:
//
// EMS LPC Automatic location processing failed.
//
#define EMS_LPC_AUTOMATIC_PROCESSING_FAILED ((EMS_RESULT)0x8004B822L)

//
// MessageId: EMS_LPC_PURGE_FAILED
//
// MessageText:
//
// EMS LPC Periodic file purge failed.
//
#define EMS_LPC_PURGE_FAILED             ((EMS_RESULT)0x8004B823L)

//
// MessageId: EMS_LPC_SOLVE_CMD
//
// MessageText:
//
// EMS LPC Sending solve command to location processor: %1
//
#define EMS_LPC_SOLVE_CMD                ((EMS_RESULT)0x0004B824L)

//
// MessageId: EMS_LPC_LP_TIMEOUT
//
// MessageText:
//
// EMS LPC timed out while waiting for location results.  Location processor may be busy.  Please resubmit request.
//
#define EMS_LPC_LP_TIMEOUT               ((EMS_RESULT)0x8004B825L)

//
// MessageId: EMS_LPC_LP_BUSY
//
// MessageText:
//
// EMS LPC cannot process location requests.  Location Processor is busy.  Please resubmit request.
//
#define EMS_LPC_LP_BUSY                  ((EMS_RESULT)0x8004B826L)


#endif // INC_LPCMSGS
/********************************************************************
*	Module:			configmanagermsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for config manager
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2003-2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Oct03		FJP	start 

********************************************************************/
#ifndef INC_CONFIGMANAGERMSGS
#define INC_CONFIGMANAGERMSGS

#include "emserror.h"

//
// MessageId: EMS_CM_BASE_CODE
//
// MessageText:
//
// EMS CM Error
//
#define EMS_CM_BASE_CODE                 ((EMS_RESULT)0x8004B700L)

//
// MessageId: EMS_CM_SERVICE_START
//
// MessageText:
//
// EMS CM Service Started
//
#define EMS_CM_SERVICE_START             ((EMS_RESULT)0x0004B701L)

//
// MessageId: EMS_CM_SERVICE_STOP
//
// MessageText:
//
// EMS CM Service Stopped
//
#define EMS_CM_SERVICE_STOP              ((EMS_RESULT)0x0004B702L)

//
// MessageId: EMS_CM_SERVICE_FAILED
//
// MessageText:
//
// EMS CM Service did not start due to error %1
//
#define EMS_CM_SERVICE_FAILED            ((EMS_RESULT)0x8004B703L)

//
// MessageId: EMS_CM_ERROR
//
// MessageText:
//
// EMS CM Error:  %1
//
#define EMS_CM_ERROR                     ((EMS_RESULT)0x8004B704L)

//
// MessageId: EMS_CM_EXCEPTION
//
// MessageText:
//
// EMS CM exception has occurred:  %1
//
#define EMS_CM_EXCEPTION                 ((EMS_RESULT)0x8004B705L)

//
// MessageId: EMS_CM_TRACE_MSG
//
// MessageText:
//
// EMS CM trace message:  %1
//
#define EMS_CM_TRACE_MSG                 ((EMS_RESULT)0x0004B706L)

//
// MessageId: EMS_CM_INVALID_SYS_CFG_FILE
//
// MessageText:
//
// EMS CM Error:  Error reading CM system configuration file.
//
#define EMS_CM_INVALID_SYS_CFG_FILE      ((EMS_RESULT)0x8004B707L)

//
// MessageId: EMS_CM_INVALID_SCHEMA_FILE
//
// MessageText:
//
// EMS CM Error:  Error reading schema file (%1).
//
#define EMS_CM_INVALID_SCHEMA_FILE       ((EMS_RESULT)0x8004B708L)

//
// MessageId: EMS_CM_INVALID_DATA_FILE
//
// MessageText:
//
// EMS CM could not read data file (%1).
//
#define EMS_CM_INVALID_DATA_FILE         ((EMS_RESULT)0x0004B709L)

//
// MessageId: EMS_CM_INVALID_GROUP_TYPE
//
// MessageText:
//
// EMS CM Error:  Invalid group type (%1).
//
#define EMS_CM_INVALID_GROUP_TYPE        ((EMS_RESULT)0x8004B70AL)

//
// MessageId: EMS_CM_INVALID_GROUP_ID
//
// MessageText:
//
// EMS CM Error:  Invalid group ID (%1).
//
#define EMS_CM_INVALID_GROUP_ID          ((EMS_RESULT)0x8004B70BL)

//
// MessageId: EMS_CM_INVALID_KEY_NAME
//
// MessageText:
//
// EMS CM Error:  Invalid key name (%1).
//
#define EMS_CM_INVALID_KEY_NAME          ((EMS_RESULT)0x8004B70CL)

//
// MessageId: EMS_CM_INVALID_DATA
//
// MessageText:
//
// EMS CM Error:  Invalid configuration data (key = %1).
//
#define EMS_CM_INVALID_DATA              ((EMS_RESULT)0x8004B70DL)

//
// MessageId: EMS_CM_INVALID_LEVEL
//
// MessageText:
//
// EMS CM Error:  Invalid level (%1).
//
#define EMS_CM_INVALID_LEVEL             ((EMS_RESULT)0x8004B70EL)

//
// MessageId: EMS_CM_NO_DATA
//
// MessageText:
//
// EMS CM Error:  Unable to retrieve configuration data (key = %1).
//
#define EMS_CM_NO_DATA                   ((EMS_RESULT)0x8004B70FL)

//
// MessageId: EMS_CM_PIPELINE_INIT_ERR
//
// MessageText:
//
// EMS CM Error: Failed to instantiate pipeline (%1).
//
#define EMS_CM_PIPELINE_INIT_ERR         ((EMS_RESULT)0x8004B710L)

//
// MessageId: EMS_CM_CMDSINK_INIT_ERR
//
// MessageText:
//
// EMS CM Error: Failed to instantiate command sink.
//
#define EMS_CM_CMDSINK_INIT_ERR          ((EMS_RESULT)0x8004B711L)

//
// MessageId: EMS_CM_CMDSINK_REG_ERR
//
// MessageText:
//
// EMS CM Error: Failed to register command sink (%1).
//
#define EMS_CM_CMDSINK_REG_ERR           ((EMS_RESULT)0x8004B712L)

//
// MessageId: EMS_CM_INIT_UNK_ERR
//
// MessageText:
//
// EMS CM Error: Service failed to start. Unhandled exception.
//
#define EMS_CM_INIT_UNK_ERR              ((EMS_RESULT)0x8004B713L)

//
// MessageId: EMS_CM_INVALID_VALUE_ASSIGNMENT
//
// MessageText:
//
// Attempt to assign an invalid value to [%1] %2 (level=%3) data value: %4
//
#define EMS_CM_INVALID_VALUE_ASSIGNMENT  ((EMS_RESULT)0x8004B714L)

//
// MessageId: EMS_CM_NONEXISTANT_DATA_FILE
//
// MessageText:
//
// EMS CM data file does not exist (%1).
//
#define EMS_CM_NONEXISTANT_DATA_FILE     ((EMS_RESULT)0x8004B715L)

//
// MessageId: EMS_CM_JOURNALIZE_FAILED
//
// MessageText:
//
// Could not journalize entry [%1:%2] %3 (error: %4)
//
#define EMS_CM_JOURNALIZE_FAILED         ((EMS_RESULT)0x0004B716L)

//
// MessageId: EMS_CM_NOT_INITIALIZED
//
// MessageText:
//
// EMS CM Error: Could not process request. Configuration manager has not been initialized.
//
#define EMS_CM_NOT_INITIALIZED           ((EMS_RESULT)0x0004B717L)

//
// MessageId: EMS_CM_GETCONFIGGROUP_ERR
//
// MessageText:
//
// EMS CM: Could not access specified configuration data group.
//
#define EMS_CM_GETCONFIGGROUP_ERR        ((EMS_RESULT)0x8004B718L)

//
// MessageId: EMS_CM_SETDATA_ERR
//
// MessageText:
//
// EMS CM: Configuration data items not saved.
//
#define EMS_CM_SETDATA_ERR               ((EMS_RESULT)0x8004B719L)

//
// MessageId: EMS_CM_INVALIDSYSTEMCFGFILE
//
// MessageText:
//
// EMS CM: Invalid system configuration file.
//
#define EMS_CM_INVALIDSYSTEMCFGFILE      ((EMS_RESULT)0x8004B71AL)

//
// MessageId: EMS_CM_CMSYSCONFIGINITFAILED
//
// MessageText:
//
// EMS CM: Could not load the system configuration file.
//
#define EMS_CM_CMSYSCONFIGINITFAILED     ((EMS_RESULT)0x8004B71BL)

//
// MessageId: EMS_CM_INVALID_SYS_CFG_FILE_DETAILS
//
// MessageText:
//
// EMS CM Error:  Error reading CM system configuration file (%1) (%2).
//
#define EMS_CM_INVALID_SYS_CFG_FILE_DETAILS ((EMS_RESULT)0x8004B71CL)

//
// MessageId: EMS_CM_INVALID_DATA_ENCOUNTERED
//
// MessageText:
//
// EMS CM Error:  Invalid data encountered during processing.
//
#define EMS_CM_INVALID_DATA_ENCOUNTERED  ((EMS_RESULT)0x8004B71DL)

//
// MessageId: EMS_CM_INVALID_INI_KEY
//
// MessageText:
//
// EMS CM Error:  Invalid key name "%1" found in "%2".
//
#define EMS_CM_INVALID_INI_KEY           ((EMS_RESULT)0x8004B71EL)

//
// MessageId: EMS_CM_INI_ERROR
//
// MessageText:
//
// EMS CM Error:  An error occured while loading "%1".
//
#define EMS_CM_INI_ERROR                 ((EMS_RESULT)0x8004B71FL)

//
// MessageId: EMS_CM_JOURNALIZE_EXCEPTION
//
// MessageText:
//
// EMS CM Error:  Exception while attempting to journalize initial configuration.
//
#define EMS_CM_JOURNALIZE_EXCEPTION      ((EMS_RESULT)0x8004B720L)


#endif // INC_CONFIGMANAGERMSGS
/********************************************************************
*	Module:			SGenMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Sit Generator Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_SGENMSGS
#define INC_SGENMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SITGEN_BASE_CODE
//
// MessageText:
//
// EMS SitGen Error
//
#define EMS_SITGEN_BASE_CODE             ((EMS_RESULT)0x8004B200L)

//
// MessageId: EMS_SITGEN_SERVICE_START
//
// MessageText:
//
// EMS SitGen Service Started
//
#define EMS_SITGEN_SERVICE_START         ((EMS_RESULT)0x0004B201L)

//
// MessageId: EMS_SITGEN_SERVICE_FAILED
//
// MessageText:
//
// EMS SitGen Service did not start due to error %1
//
#define EMS_SITGEN_SERVICE_FAILED        ((EMS_RESULT)0x0004B202L)

//
// MessageId: EMS_SITGEN_SERVICE_STOP
//
// MessageText:
//
// EMS SitGen Service Stopped
//
#define EMS_SITGEN_SERVICE_STOP          ((EMS_RESULT)0x0004B203L)

//
// MessageId: EMS_SITGEN_ERROR
//
// MessageText:
//
// EMS SitGen reports error %1.
//
#define EMS_SITGEN_ERROR                 ((EMS_RESULT)0x8004B204L)

//
// MessageId: EMS_SITGEN_PIPELINE_CONNECT_ERROR
//
// MessageText:
//
// EMS SitGen reports error %1 while trying to connect to the pipeline.
//
#define EMS_SITGEN_PIPELINE_CONNECT_ERROR ((EMS_RESULT)0x8004B205L)

//
// MessageId: EMS_SITGEN_NO_SITEINFO
//
// MessageText:
//
// EMS SitGen reports error trying to access the site info.
//
#define EMS_SITGEN_NO_SITEINFO           ((EMS_RESULT)0x8004B206L)

//
// MessageId: EMS_SITGEN_NO_LOGGER
//
// MessageText:
//
// EMS SitGen reports error trying to connect to the logger.
//
#define EMS_SITGEN_NO_LOGGER             ((EMS_RESULT)0x8004B207L)

//
// MessageId: EMS_SITGEN_INVALID_SEND_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing send directory( %1 ).
//
#define EMS_SITGEN_INVALID_SEND_DIR      ((EMS_RESULT)0x8004B208L)

//
// MessageId: EMS_SITGEN_FILE_CREATE_ERR
//
// MessageText:
//
// EMS SitGen reports error trying to create file (%1).
//
#define EMS_SITGEN_FILE_CREATE_ERR       ((EMS_RESULT)0x8004B209L)

//
// MessageId: EMS_SITGEN_INVALID_SENT_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing sent directory( %1 ).
//
#define EMS_SITGEN_INVALID_SENT_DIR      ((EMS_RESULT)0x8004B20AL)

//
// MessageId: EMS_SITGEN_INVALID_UNDELIVERED_DIR
//
// MessageText:
//
// EMS SitGen reports error accessing undelivered directory( %1 ).
//
#define EMS_SITGEN_INVALID_UNDELIVERED_DIR ((EMS_RESULT)0x8004B20BL)

//
// MessageId: EMS_SITGEN_UNKNOWN_DEST
//
// MessageText:
//
// EMS SitGen reports error trying to identify dest ID %1.
//
#define EMS_SITGEN_UNKNOWN_DEST          ((EMS_RESULT)0x8004B20CL)

//
// MessageId: EMS_SITGEN_RESEND_BUSY
//
// MessageText:
//
// EMS SitGen rejected retransmit request from dest ID %1.
//
#define EMS_SITGEN_RESEND_BUSY           ((EMS_RESULT)0x8004B20DL)

//
// MessageId: EMS_SITGEN_RESEND_REQ
//
// MessageText:
//
// EMS SitGen received request from dest ID %1 msgs to be resent.
//
#define EMS_SITGEN_RESEND_REQ            ((EMS_RESULT)0x0004B20EL)

//
// MessageId: EMS_SITGEN_RESEND_RESULT
//
// MessageText:
//
// EMS SitGen resent dest ID %1 messages.
//
#define EMS_SITGEN_RESEND_RESULT         ((EMS_RESULT)0x0004B20FL)

//
// MessageId: EMS_SITGEN_NO_ORBIT
//
// MessageText:
//
// EMS SitGen cannot create orbit interface (%1).
//
#define EMS_SITGEN_NO_ORBIT              ((EMS_RESULT)0x0004B210L)

//
// MessageId: EMS_SITGEN_SELECTION_EMPTY
//
// MessageText:
//
// EMS SitGen reports no data to reply to the request.
//
#define EMS_SITGEN_SELECTION_EMPTY       ((EMS_RESULT)0x8004B211L)

//
// MessageId: EMS_SITGEN_SELECTION_LIMIT
//
// MessageText:
//
// EMS SitGen reports too much data to reply to the request.
//
#define EMS_SITGEN_SELECTION_LIMIT       ((EMS_RESULT)0x8004B212L)

//
// MessageId: EMS_SITGEN_UNKNOWN_REQUEST
//
// MessageText:
//
// EMS SitGen reports unknown SendData ( %1 ) request.
//
#define EMS_SITGEN_UNKNOWN_REQUEST       ((EMS_RESULT)0x8004B213L)

//
// MessageId: EMS_SITGEN_NO_DEST_SIT
//
// MessageText:
//
// EMS SitGen reports SIT format not defined by destination.
//
#define EMS_SITGEN_NO_DEST_SIT           ((EMS_RESULT)0x8004B214L)

//
// MessageId: EMS_SITGEN_TRACER
//
// MessageText:
//
// EMS SitGen tracer ( %1 ).
//
#define EMS_SITGEN_TRACER                ((EMS_RESULT)0x0004B215L)

//
// MessageId: EMS_SITGEN_SUPPRESSED
//
// MessageText:
//
// EMS SitGen suppressed %1 alerts.
//
#define EMS_SITGEN_SUPPRESSED            ((EMS_RESULT)0x0004B216L)

//
// MessageId: EMS_SITGEN_ALERT_FILTER
//
// MessageText:
//
// EMS SitGen reports finding an Alert Filter module.
//
#define EMS_SITGEN_ALERT_FILTER          ((EMS_RESULT)0x0004B217L)

//
// MessageId: EMS_SITGEN_NO_ALERT_FILTER
//
// MessageText:
//
// EMS SitGen reports no Alert Filter module found.
//
#define EMS_SITGEN_NO_ALERT_FILTER       ((EMS_RESULT)0x0004B218L)

//
// MessageId: EMS_SITGEN_RESEND_REQ_NODATA
//
// MessageText:
//
// EMS SitGen reports failed resend request.  The requested messages %1 cannot be found.
//
#define EMS_SITGEN_RESEND_REQ_NODATA     ((EMS_RESULT)0x8004B219L)

//
// MessageId: EMS_SITGEN_RESEND_REQ_FAILED
//
// MessageText:
//
// EMS SitGen reports failed resend request.  The request for messages %1 could not be processed.
//
#define EMS_SITGEN_RESEND_REQ_FAILED     ((EMS_RESULT)0x8004B21AL)

//
// MessageId: EMS_SITGEN_MSG_SIZE_UNKNOWN
//
// MessageText:
//
// EMS SitGen reports failure retrieving configured value for maximum SIT message size.
//
#define EMS_SITGEN_MSG_SIZE_UNKNOWN      ((EMS_RESULT)0x8004B21BL)

//
// MessageId: EMS_SITGEN_NO_CM
//
// MessageText:
//
// EMS SitGen reports failure initializing the Configuration Manager.  Error code = %1.
//
#define EMS_SITGEN_NO_CM                 ((EMS_RESULT)0x8004B21CL)

//
// MessageId: EMS_SITGEN_NO_SECURITY_TOKEN
//
// MessageText:
//
// EMS SitGen reports failure retrieving a security token.  Error code = %1.
//
#define EMS_SITGEN_NO_SECURITY_TOKEN     ((EMS_RESULT)0x8004B21DL)

//
// MessageId: EMS_SITGEN_TRACE_ENTER
//
// MessageText:
//
// EMS SitGen tracer ( ** Enter: Sit (%1) )
//
#define EMS_SITGEN_TRACE_ENTER           ((EMS_RESULT)0x0004B21EL)

//
// MessageId: EMS_SITGEN_TRACE_EXIT
//
// MessageText:
//
// EMS SitGen tracer ( ** Exit: Sit (%1) )
//
#define EMS_SITGEN_TRACE_EXIT            ((EMS_RESULT)0x0004B21FL)

//
// MessageId: EMS_SITGEN_TRACE_SELN
//
// MessageText:
//
// EMS SitGen tracer ( Selection (%1) - (%2) )
//
#define EMS_SITGEN_TRACE_SELN            ((EMS_RESULT)0x0004B220L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIG
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=%2 )
//
#define EMS_SITGEN_TRACE_CONFIG          ((EMS_RESULT)0x0004B221L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIGYES
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=yes )
//
#define EMS_SITGEN_TRACE_CONFIGYES       ((EMS_RESULT)0x0004B222L)

//
// MessageId: EMS_SITGEN_TRACE_CONFIGNO
//
// MessageText:
//
// EMS SitGen tracer ( cfg: %1=no )
//
#define EMS_SITGEN_TRACE_CONFIGNO        ((EMS_RESULT)0x0004B223L)

//
// MessageId: EMS_SITGEN_TRACE_SATEPOCH
//
// MessageText:
//
// EMS SitGen tracer ( Sat=%1, Epoch=%2 )
//
#define EMS_SITGEN_TRACE_SATEPOCH        ((EMS_RESULT)0x0004B224L)

//
// MessageId: EMS_SITGEN_TRACE_DEST
//
// MessageText:
//
// EMS SitGen tracer ( Dest %1 - %2 dwFlags(%3) )
//
#define EMS_SITGEN_TRACE_DEST            ((EMS_RESULT)0x0004B225L)

//
// MessageId: EMS_SITGEN_TRACE_CHARMAPINUSE
//
// MessageText:
//
// EMS SitGen: Dest %1 has character mapping specified (%2)
//
#define EMS_SITGEN_TRACE_CHARMAPINUSE    ((EMS_RESULT)0x0004B226L)

//
// MessageId: EMS_SITGEN_LINE_LIMIT_EXCEEDED
//
// MessageText:
//
// EMS SitGen: Maximum allowed line length for a sit message has been exceeded.
//
#define EMS_SITGEN_LINE_LIMIT_EXCEEDED   ((EMS_RESULT)0x8004B227L)

//
// MessageId: EMS_SITGEN_BEACON_SUPPRESSED_FOR_DEST
//
// MessageText:
//
// EMS SitGen: Alert suppressed (Beacon: %1, Dest: %2).
//
#define EMS_SITGEN_BEACON_SUPPRESSED_FOR_DEST ((EMS_RESULT)0x0004B228L)

//
// MessageId: EMS_SITGEN_MF_RANGE_EXCEEDED
//
// MessageText:
//
// EMS SitGen: %1 %2 value was adjusted before being output (%3 changed to %4).
//
#define EMS_SITGEN_MF_RANGE_EXCEEDED     ((EMS_RESULT)0x0004B229L)

//
// MessageId: EMS_SITGEN_SENDDATA_FAILED
//
// MessageText:
//
// EMS SitGen reports error trying to process "SendData" command (SIT Number=%1, dest ID=%2, Error - %3).
//
#define EMS_SITGEN_SENDDATA_FAILED       ((EMS_RESULT)0x8004B22AL)

//
// MessageId: EMS_SIT_ALREADY_INITIALIZED
//
// MessageText:
//
// Programming error: SIT message has already been initialized.
//
#define EMS_SIT_ALREADY_INITIALIZED      ((EMS_RESULT)0x8004B22BL)


#endif // INC_SGENMSGS
/********************************************************************
*	Module:			AntMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Antenna Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_ANTMSGS
#define INC_ANTMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ANT_BASE_CODE
//
// MessageText:
//
// EMS Antenna Error
//
#define EMS_ANT_BASE_CODE                ((EMS_RESULT)0x8004A600L)

//
// MessageId: EMS_ANT_SERVICE_START
//
// MessageText:
//
// EMS Antenna Service Started
//
#define EMS_ANT_SERVICE_START            ((EMS_RESULT)0x0004A601L)

//
// MessageId: EMS_ANT_SERVICE_FAILED
//
// MessageText:
//
// EMS Antenna Service did not start due to error %1
//
#define EMS_ANT_SERVICE_FAILED           ((EMS_RESULT)0x8004A602L)

//
// MessageId: EMS_ANT_SERVICE_STOP
//
// MessageText:
//
// EMS Antenna Service Stopped
//
#define EMS_ANT_SERVICE_STOP             ((EMS_RESULT)0x0004A603L)

//
// MessageId: EMS_ANT_ERROR
//
// MessageText:
//
// EMS Antenna reports error %1.
//
#define EMS_ANT_ERROR                    ((EMS_RESULT)0x8004A604L)

//
// MessageId: EMS_ANT_START_PASS
//
// MessageText:
//
// EMS Antenna starting to track pass 
//
#define EMS_ANT_START_PASS               ((EMS_RESULT)0x0004A605L)

//
// MessageId: EMS_ANT_STOP_PASS
//
// MessageText:
//
// EMS Antenna stopped tracking pass. 
//
#define EMS_ANT_STOP_PASS                ((EMS_RESULT)0x0004A606L)

//
// MessageId: EMS_ANT_RECV_COMMAND
//
// MessageText:
//
// EMS Antenna received command ( %1 ).
//
#define EMS_ANT_RECV_COMMAND             ((EMS_RESULT)0x0004A607L)

//
// MessageId: EMS_ANT_INITIAL_HOME
//
// MessageText:
//
// EMS Antenna successfully initialized.
//
#define EMS_ANT_INITIAL_HOME             ((EMS_RESULT)0x0004A608L)

//
// MessageId: EMS_ANT_FAILED_HOME
//
// MessageText:
//
// EMS Antenna timed out during initialization.
//
#define EMS_ANT_FAILED_HOME              ((EMS_RESULT)0x8004A609L)

//
// MessageId: EMS_ANT_STATUS
//
// MessageText:
//
// EMS Antenna Homing Successful. Offset: ( %1 ).
//
#define EMS_ANT_STATUS                   ((EMS_RESULT)0x0004A60AL)

//
// MessageId: EMS_ANT_SKIP_HOME
//
// MessageText:
//
// EMS Antenna skipped homing sequence.
//
#define EMS_ANT_SKIP_HOME                ((EMS_RESULT)0x0004A60BL)

//
// MessageId: EMS_ANT_DEVICE_PERMISSION
//
// MessageText:
//
// EMS Antenna reports error accessing antenna device. (see DCOMCnfg - may have insufficient permission ).
//
#define EMS_ANT_DEVICE_PERMISSION        ((EMS_RESULT)0x8004A60CL)

//
// MessageId: EMS_ANT_HOMING_FAULT_RETRY
//
// MessageText:
//
// EMS Antenna reports homing fault ( Retrying attempt %1 ).
//
#define EMS_ANT_HOMING_FAULT_RETRY       ((EMS_RESULT)0x8004A60DL)

//
// MessageId: EMS_ANT_HOMING_FAULT
//
// MessageText:
//
// EMS Antenna reports homing fault ( Homing Terminated ).
//
#define EMS_ANT_HOMING_FAULT             ((EMS_RESULT)0x8004A60EL)

//
// MessageId: EMS_ANT_HOMING_TIMEOUT_RETRY
//
// MessageText:
//
// EMS Antenna reports homing timeout ( Retrying attempt %1 ).
//
#define EMS_ANT_HOMING_TIMEOUT_RETRY     ((EMS_RESULT)0x8004A60FL)

//
// MessageId: EMS_ANT_HOMING_TIMEOUT
//
// MessageText:
//
// EMS Antenna reports homing timeout ( Homing Terminated ).
//
#define EMS_ANT_HOMING_TIMEOUT           ((EMS_RESULT)0x8004A610L)

//
// MessageId: EMS_ANT_PASS_RETRY
//
// MessageText:
//
// EMS Antenna reports pass failure ( Retrying attempt %1 ).
//
#define EMS_ANT_PASS_RETRY               ((EMS_RESULT)0x8004A611L)

//
// MessageId: EMS_ANT_PASS_ERROR
//
// MessageText:
//
// EMS Antenna reports pass failure ( Tracking terminated ).
//
#define EMS_ANT_PASS_ERROR               ((EMS_RESULT)0x8004A612L)

//
// MessageId: EMS_ANT_RESET_WAIT_TIMEOUT
//
// MessageText:
//
// EMS Antenna reports timeout waiting for Antenna subsystem to shutdown.
//
#define EMS_ANT_RESET_WAIT_TIMEOUT       ((EMS_RESULT)0x8004A613L)

//
// MessageId: EMS_ANT_RESET_WAIT_ABANDONED
//
// MessageText:
//
// EMS Antenna reports wait abandoned for Antenna subsystem to shutdown.
//
#define EMS_ANT_RESET_WAIT_ABANDONED     ((EMS_RESULT)0x8004A614L)

//
// MessageId: EMS_ANT_DEVICE_INIT_FAILED
//
// MessageText:
//
// EMS Antenna reports an error during ACU initialization (hr = %1). This may indicate a power outage to the ACU or an ACU hardware fault.  Hardware faults can often be cleared by recycling the ACU power.
//
#define EMS_ANT_DEVICE_INIT_FAILED       ((EMS_RESULT)0x8004A615L)

//
// MessageId: EMS_ANT_INIT_HOME
//
// MessageText:
//
// EMS Antenna reports initial homing was successful.
//
#define EMS_ANT_INIT_HOME                ((EMS_RESULT)0x0004A616L)

//
// MessageId: EMS_ANT_HARDWARE_ERROR
//
// MessageText:
//
// EMS Antenna reports a hardware problem. This may indicate a power outage to the ACU or an ACU hardware fault. Hardware faults can often be cleared by recycling the ACU power.
//
#define EMS_ANT_HARDWARE_ERROR           ((EMS_RESULT)0x8004A617L)

//
// MessageId: EMS_ANT_HARDWARE_ERROR_CLEARED
//
// MessageText:
//
// EMS Antenna reports the ACU hardware error condition has been cleared.
//
#define EMS_ANT_HARDWARE_ERROR_CLEARED   ((EMS_RESULT)0x0004A618L)

//
// MessageId: EMS_ANT_INIT_ERROR_SKIP_PASS
//
// MessageText:
//
// EMS Antenna reports it is skipping a pass (satellite %1) due to problem in ACU initialization.
//
#define EMS_ANT_INIT_ERROR_SKIP_PASS     ((EMS_RESULT)0x8004A619L)


// *** EMSCAT_ANT = 0x87 ***

//
// MessageId: EMSCAT_ANT_BASE_CODE
//
// MessageText:
//
// Antenna error messages.
//
#define EMSCAT_ANT_BASE_CODE             ((EMS_RESULT)0x80048700L)

//
// MessageId: ANT_INV_CTR_REQUEST
//
// MessageText:
//
// EMS Antenna reports invalid control request received.
//
#define ANT_INV_CTR_REQUEST              ((EMS_RESULT)0x80048701L)

//
// MessageId: ANT_INV_DEST_NAME
//
// MessageText:
//
// EMS Antenna: given logical destination is invalid.
//
#define ANT_INV_DEST_NAME                ((EMS_RESULT)0x80048702L)

//
// MessageId: ANT_INV_BEAMWIDTH
//
// MessageText:
//
// EMS Antenna: Specified azimuth and elevation are not within the beamwidth.
//
#define ANT_INV_BEAMWIDTH                ((EMS_RESULT)0x80048703L)

//
// MessageId: ANT_NOT_REACHED_AOS
//
// MessageText:
//
// EMS Antenna: Could not move to AOS.
//
#define ANT_NOT_REACHED_AOS              ((EMS_RESULT)0x80048704L)

//
// MessageId: ANT_CW_LIMIT_HIT
//
// MessageText:
//
// EMS Antenna: At Clockwise limit zone.
//
#define ANT_CW_LIMIT_HIT                 ((EMS_RESULT)0x80048705L)

//
// MessageId: ANT_CCW_LIMIT_HIT
//
// MessageText:
//
// EMS Antenna: At Counter Clockwise limit zone
//
#define ANT_CCW_LIMIT_HIT                ((EMS_RESULT)0x80048706L)

//
// MessageId: ANT_HIGH_LIMIT_HIT
//
// MessageText:
//
// EMS Antenna: At High elevation limit zone
//
#define ANT_HIGH_LIMIT_HIT               ((EMS_RESULT)0x80048707L)

//
// MessageId: ANT_LOW_LIMIT_HIT
//
// MessageText:
//
// EMS Antenna: At Low elevation limit zone
//
#define ANT_LOW_LIMIT_HIT                ((EMS_RESULT)0x80048708L)

//
// MessageId: ANT_INV_REGISTRY
//
// MessageText:
//
// EMS Antenna: Can't open registry
//
#define ANT_INV_REGISTRY                 ((EMS_RESULT)0x80048709L)

//
// MessageId: ANT_ILLEGAL_LINE_NUMBER
//
// MessageText:
//
// EMS Antenna: Illegal line number.
//
#define ANT_ILLEGAL_LINE_NUMBER          ((EMS_RESULT)0x8004870AL)

//
// MessageId: ANT_NON_REQUEST_TO_CANCEL
//
// MessageText:
//
// EMS Antenna: Invalid cancel request.
//
#define ANT_NON_REQUEST_TO_CANCEL        ((EMS_RESULT)0x8004870BL)

//
// MessageId: ANT_INV_AZIMUTH_COMM
//
// MessageText:
//
// EMS Antenna: Failed to set azimuth.
//
#define ANT_INV_AZIMUTH_COMM             ((EMS_RESULT)0x8004870CL)

//
// MessageId: ANT_INV_ELEVATION_COMM
//
// MessageText:
//
// EMS Antenna: Failed to set elevation.
//
#define ANT_INV_ELEVATION_COMM           ((EMS_RESULT)0x8004870DL)

//
// MessageId: ANT_CANT_STOP_ANTENNA
//
// MessageText:
//
// EMS Antenna: Cannot stop antenna.
//
#define ANT_CANT_STOP_ANTENNA            ((EMS_RESULT)0x8004870EL)

//
// MessageId: ANT_HOME_FAULT
//
// MessageText:
//
// EMS Antenna: Error processing home command.
//
#define ANT_HOME_FAULT                   ((EMS_RESULT)0x8004870FL)

//
// MessageId: EMS_TOO_LATE_FOR_TRACK
//
// MessageText:
//
// EMS Antenna: Too late for track.
//
#define EMS_TOO_LATE_FOR_TRACK           ((EMS_RESULT)0x80048710L)

//
// MessageId: EMS_ANT_WORKERBUFFERLOCKERR
//
// MessageText:
//
// EMS Antenna: Error locking buffer in transfer track data in WorkerThread
//
#define EMS_ANT_WORKERBUFFERLOCKERR      ((EMS_RESULT)0x80048711L)

//
// MessageId: EMS_ANT_MEMORYRAWTRACK
//
// MessageText:
//
// EMS Antenna: Error Allocating memory for l_AdjRawTrack in WorkerThread
//
#define EMS_ANT_MEMORYRAWTRACK           ((EMS_RESULT)0x80048712L)

//
// MessageId: EMS_ANT_TOOMANYSMOOTHINGITER
//
// MessageText:
//
// EMS Antenna: Too many smoothing iterations in WorkerThread. Smoothing aborted.
//
#define EMS_ANT_TOOMANYSMOOTHINGITER     ((EMS_RESULT)0x80048713L)

//
// MessageId: EMS_ANT_TIMESINCEAXISPOSNTOOLONG
//
// MessageText:
//
// EMS Antenna: Track execution aborted. Time since last axis position report is too long.
//
#define EMS_ANT_TIMESINCEAXISPOSNTOOLONG ((EMS_RESULT)0x80048714L)

//
// MessageId: EMS_ANT_TRACKSPEEDMEMORYERR
//
// MessageText:
//
// EMS Antenna: Could not allocate memory for proposed track speeds.
//
#define EMS_ANT_TRACKSPEEDMEMORYERR      ((EMS_RESULT)0x80048715L)

//
// MessageId: EMS_ANT_TRACKMEMORYERR
//
// MessageText:
//
// EMS Antenna: Could not allocate memory for proposed track.
//
#define EMS_ANT_TRACKMEMORYERR           ((EMS_RESULT)0x80048716L)

//
// MessageId: EMS_ANT_AZIMUTHRECONCILEERR
//
// MessageText:
//
// EMS Antenna: Cannot reconcile azimuth values to track within the antenna parameters.
//
#define EMS_ANT_AZIMUTHRECONCILEERR      ((EMS_RESULT)0x80048717L)

//
// MessageId: EMS_ANT_RAWTRACKMEMORYERR
//
// MessageText:
//
// EMS Antenna: Cannot Allocate Memory for l_AdjRawRawTrack
//
#define EMS_ANT_RAWTRACKMEMORYERR        ((EMS_RESULT)0x80048718L)

//
// MessageId: EMS_ANT_MEMORYERR
//
// MessageText:
//
// EMS Antenna: Cannot Allocate Memory
//
#define EMS_ANT_MEMORYERR                ((EMS_RESULT)0x80048719L)

//
// MessageId: EMS_ANT_COORDMEMORYERR
//
// MessageText:
//
// EMS Antenna: Cannot Allocate Memory for coordinates
//
#define EMS_ANT_COORDMEMORYERR           ((EMS_RESULT)0x8004871AL)

//
// MessageId: EMS_ANT_HARDWAREERR
//
// MessageText:
//
// EMS Antenna: Hardware error.
//
#define EMS_ANT_HARDWAREERR              ((EMS_RESULT)0x8004871BL)

//
// MessageId: EMS_ANT_OUTOFBEAMERR
//
// MessageText:
//
// EMS Antenna: Out of beam error.
//
#define EMS_ANT_OUTOFBEAMERR             ((EMS_RESULT)0x8004871CL)

//
// MessageId: EMS_ANT_UNKNOWNERR
//
// MessageText:
//
// EMS Antenna: Unknown error.
//
#define EMS_ANT_UNKNOWNERR               ((EMS_RESULT)0x8004871DL)

//
// MessageId: EMS_ANT_AGC_SWITCH_FAIL
//
// MessageText:
//
// EMS Antenna: Failed to initialize AGC switch (hr=%1).
//
#define EMS_ANT_AGC_SWITCH_FAIL          ((EMS_RESULT)0x8004871EL)

//
// MessageId: EMS_ANT_POLR_SWITCH_FAIL
//
// MessageText:
//
// EMS Antenna: Failed to initialize polarization switch (hr=%1).
//
#define EMS_ANT_POLR_SWITCH_FAIL         ((EMS_RESULT)0x8004871FL)

//
// MessageId: EMS_ANT_FREQ1_SWITCH_FAIL
//
// MessageText:
//
// EMS Antenna: Failed to initialize the first frequency switch (hr=%1).
//
#define EMS_ANT_FREQ1_SWITCH_FAIL        ((EMS_RESULT)0x80048720L)

//
// MessageId: EMS_ANT_FREQ2_SWITCH_FAIL
//
// MessageText:
//
// EMS Antenna: Failed to initialize the second frequency switch (hr=%1).
//
#define EMS_ANT_FREQ2_SWITCH_FAIL        ((EMS_RESULT)0x80048721L)

//
// MessageId: EMS_ANT_HW_ERR_REINIT
//
// MessageText:
//
// EMS Antenna: Detected a hardware problem and trying to reinitialize the ACU. (This could be a power outages, ACU hardware error or network problem).
//
#define EMS_ANT_HW_ERR_REINIT            ((EMS_RESULT)0x80048722L)


#endif // INC_ANTMSGS
/********************************************************************
*	Module:			AudioMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Audio Service Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_AUDIOMSG
#define INC_AUDIOMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_AUDIO_BASE_CODE
//
// MessageText:
//
// EMS Audio Error
//
#define EMS_AUDIO_BASE_CODE              ((EMS_RESULT)0x8004BE00L)

//
// MessageId: EMS_AUDIO_SERVICE_START
//
// MessageText:
//
// EMS Audio Service Started
//
#define EMS_AUDIO_SERVICE_START          ((EMS_RESULT)0x0004BE01L)

//
// MessageId: EMS_AUDIO_SERVICE_FAILED
//
// MessageText:
//
// EMS Audio Service did not start due to error %1
//
#define EMS_AUDIO_SERVICE_FAILED         ((EMS_RESULT)0x0004BE02L)

//
// MessageId: EMS_AUDIO_SERVICE_STOP
//
// MessageText:
//
// EMS Audio Service Stopped
//
#define EMS_AUDIO_SERVICE_STOP           ((EMS_RESULT)0x0004BE03L)

//
// MessageId: EMS_AUDIO_ERROR
//
// MessageText:
//
// EMS Audio reports error %1.
//
#define EMS_AUDIO_ERROR                  ((EMS_RESULT)0x8004BE04L)

//
// MessageId: EMS_AUDIO_LOG_EXCEPTION
//
// MessageText:
//
// EMS Audio reports an exception
//
#define EMS_AUDIO_LOG_EXCEPTION          ((EMS_RESULT)0x8004BE05L)

//
// MessageId: EMS_AUDIO_LOG_INFO
//
// MessageText:
//
// EMS Audio reports info
//
#define EMS_AUDIO_LOG_INFO               ((EMS_RESULT)0x0004BE06L)

//
// MessageId: EMS_AUDIO_DIRECTORY_ERROR
//
// MessageText:
//
// EMS Audio reports error while trying to create directory ( %1 ).
//
#define EMS_AUDIO_DIRECTORY_ERROR        ((EMS_RESULT)0x8004BE07L)

//
// MessageId: EMS_AUDIO_TRACER
//
// MessageText:
//
// EMS Audio tracer ( %1 ).
//
#define EMS_AUDIO_TRACER                 ((EMS_RESULT)0x0004BE08L)

//
// MessageId: EMS_AUDIO_FILE_READ_FAIL
//
// MessageText:
//
// EMS Audio reports error %1 while attempting to open file %2.
//
#define EMS_AUDIO_FILE_READ_FAIL         ((EMS_RESULT)0x0004BE09L)

//
// MessageId: EMS_AUDIOMANAGER_MAXSESSIONS
//
// MessageText:
//
// EMS Audio Manager error : Max sessions reached.
//
#define EMS_AUDIOMANAGER_MAXSESSIONS     ((EMS_RESULT)0x8004BE0AL)

//
// MessageId: EMS_AUDIOMANAGER_CLIENTNOTCONNECTED
//
// MessageText:
//
// EMS Audio Manager error : Client is not connected.
//
#define EMS_AUDIOMANAGER_CLIENTNOTCONNECTED ((EMS_RESULT)0x8004BE0BL)

//
// MessageId: EMS_AUDIOMANAGER_NODATA
//
// MessageText:
//
// EMS Audio Manager : No data found.
//
#define EMS_AUDIOMANAGER_NODATA          ((EMS_RESULT)0x0004BE0CL)

//
// MessageId: EMS_AUDIOMANAGER_PROCESSFILE
//
// MessageText:
//
// EMS Audio Manager is processing the file ( %1 ).
//
#define EMS_AUDIOMANAGER_PROCESSFILE     ((EMS_RESULT)0x0004BE0DL)

//
// MessageId: EMS_AUDIOMANAGER_REQ_COMPLETED
//
// MessageText:
//
// EMS Audio Manager : Audio Request processing completed.
//
#define EMS_AUDIOMANAGER_REQ_COMPLETED   ((EMS_RESULT)0x0004BE0EL)

//
// MessageId: EMS_AUDIO_TRACER_RECORDSGEN
//
// MessageText:
//
// EMS Audio tracer ( Request ID: %1, records generated: %2)
//
#define EMS_AUDIO_TRACER_RECORDSGEN      ((EMS_RESULT)0x0004BE0FL)

//
// MessageId: EMS_AUDIO_TRACER_AUDIOREQ
//
// MessageText:
//
// EMS Audio tracer ( AudioReq %1 )
//
#define EMS_AUDIO_TRACER_AUDIOREQ        ((EMS_RESULT)0x0004BE10L)

//
// MessageId: EMS_AUDIO_TRACER_REQDETAILS
//
// MessageText:
//
// EMS Audio tracer ( SatID %1, Time %2, Duration %3, CenterFreq %4, Bandwidth %5 )
//
#define EMS_AUDIO_TRACER_REQDETAILS      ((EMS_RESULT)0x0004BE11L)

//
// MessageId: EMS_AUDIO_TRACER_MAKEWAVEFILE
//
// MessageText:
//
// EMS Audio tracer ( _MakeWaveFile:     result = %1 )
//
#define EMS_AUDIO_TRACER_MAKEWAVEFILE    ((EMS_RESULT)0x0004BE12L)

//
// MessageId: EMS_AUDIO_TRACER_CONFIG
//
// MessageText:
//
// EMS Audio tracer ( cfg: %1=%2 )
//
#define EMS_AUDIO_TRACER_CONFIG          ((EMS_RESULT)0x0004BE13L)

//
// MessageId: EMS_AUDIO_TRACER_CHANSCOEFFS
//
// MessageText:
//
// EMS Audio tracer ( Chans %1, coeffs %2 )
//
#define EMS_AUDIO_TRACER_CHANSCOEFFS     ((EMS_RESULT)0x0004BE14L)

//
// MessageId: EMS_AUDIOMANAGER_INITFAILED
//
// MessageText:
//
// EMS Audio Manager initialization failed (%1)
//
#define EMS_AUDIOMANAGER_INITFAILED      ((EMS_RESULT)0x8004BE15L)


#endif // INC_AUDIOMSG
/********************************************************************
*	Module:			CalibCBCMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS CalibCBC Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_CALIBCBCMSG
#define INC_CALIBCBCMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_CALIBCBC_BASE_CODE
//
// MessageText:
//
// EMS CalibrateCBC Error
//
#define EMS_CALIBCBC_BASE_CODE           ((EMS_RESULT)0x8004A800L)

//
// MessageId: EMS_CALIBCBC_SERVICE_START
//
// MessageText:
//
// EMS CalibrateCBC Service Started
//
#define EMS_CALIBCBC_SERVICE_START       ((EMS_RESULT)0x0004A801L)

//
// MessageId: EMS_CALIBCBC_SERVICE_FAILED
//
// MessageText:
//
// EMS CalibrateCBC Service did not start due to error %1
//
#define EMS_CALIBCBC_SERVICE_FAILED      ((EMS_RESULT)0x8004A802L)

//
// MessageId: EMS_CALIBCBC_SERVICE_STOP
//
// MessageText:
//
// EMS CalibrateCBC Service Stopped
//
#define EMS_CALIBCBC_SERVICE_STOP        ((EMS_RESULT)0x0004A803L)

//
// MessageId: EMS_CALIBCBC_ERROR
//
// MessageText:
//
// EMS CalibrateCBC reports error %1.
//
#define EMS_CALIBCBC_ERROR               ((EMS_RESULT)0x8004A804L)

//
// MessageId: EMS_CALIBCBC_START_PASS
//
// MessageText:
//
// EMS CalibrateCBC initialized for satellite %1
//
#define EMS_CALIBCBC_START_PASS          ((EMS_RESULT)0x0004A805L)

//
// MessageId: EMS_CALIBCBC_CALIBRATE_PASS
//
// MessageText:
//
// EMS CalibrateCBC completed calibration for satellite=%1, band=%2, result=%3
//
#define EMS_CALIBCBC_CALIBRATE_PASS      ((EMS_RESULT)0x0004A806L)

//
// MessageId: EMS_CALIBCBC_ADDREC_ERROR
//
// MessageText:
//
// EMS CalibrateCBC reports error %1 adding record %2.
//
#define EMS_CALIBCBC_ADDREC_ERROR        ((EMS_RESULT)0x8004A807L)

//
// MessageId: EMS_CALIBCBC_TRACER
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( %1 )
//
#define EMS_CALIBCBC_TRACER              ((EMS_RESULT)0x0004A808L)

//
// MessageId: EMS_CALIBCBC_RECV_COMMAND
//
// MessageText:
//
// EMS CalibrateCBC Command Received( %1 )
//
#define EMS_CALIBCBC_RECV_COMMAND        ((EMS_RESULT)0x0004A809L)

//
// MessageId: EMS_CALIBCBC_START_CALIBRATE
//
// MessageText:
//
// EMS CalibrateCBC Starting to calibrate %1 records.
//
#define EMS_CALIBCBC_START_CALIBRATE     ((EMS_RESULT)0x0004A80AL)

//
// MessageId: EMS_CALIBCBC_SUBSYSTEM_ERR
//
// MessageText:
//
// EMS CalibrateCBC reports error %1 while trying to access %2
//
#define EMS_CALIBCBC_SUBSYSTEM_ERR       ((EMS_RESULT)0x8004A80BL)

//
// MessageId: EMS_CALIBCBC_TRACE_AUDIOSENT
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 sent )
//
#define EMS_CALIBCBC_TRACE_AUDIOSENT     ((EMS_RESULT)0x0004A80CL)

//
// MessageId: EMS_CALIBCBC_TRACE_AUDIONOTSENT
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Audio Request for beacon ID %1 not sent )
//
#define EMS_CALIBCBC_TRACE_AUDIONOTSENT  ((EMS_RESULT)0x0004A80DL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS1
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Config Parms-%1: minAmplitude %2, fTimeBinSize %3 sec, fFreqBinSize %4 Hz, fFreqWindow %5 Hz )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS1 ((EMS_RESULT)0x0004A80EL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS2
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS2 ((EMS_RESULT)0x0004A80FL)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS3
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Config Parms: minAmplitude %1, fTimeBinSize    %2 sec, fFreqBinSize    %3 Hz, fFreqWindow %4 Hz )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS3 ((EMS_RESULT)0x0004A810L)

//
// MessageId: EMS_CALIBCBC_TRACE_CONFIGPARAMS4
//
// MessageText:
//
// EMS CalibrateCBC Service Tracer ( Config Parms: nTemplates   %1, fTemplateLength %2 sec, dCorrlThreshold %3 )
//
#define EMS_CALIBCBC_TRACE_CONFIGPARAMS4 ((EMS_RESULT)0x0004A811L)

//
// MessageId: EMS_CALIBCBC_SUBSYSTEM_ERR_CALIBRATE
//
// MessageText:
//
// EMS CalibrateCBC reports error %1 (trap %2) while trying to access the calibrate subsystem. 
//
#define EMS_CALIBCBC_SUBSYSTEM_ERR_CALIBRATE ((EMS_RESULT)0x8004A812L)

//
// MessageId: EMS_CALIBCBC_CALIBRATE_TIMEOUT
//
// MessageText:
//
// EMS CalibrateCBC time limit exceeded for satellite=%1, band=%2
//
#define EMS_CALIBCBC_CALIBRATE_TIMEOUT   ((EMS_RESULT)0x8004A813L)


#endif // INC_CALIBCBCMSG
/********************************************************************
*	Module:			C406Msgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Combine 406 Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_C406MSGS
#define INC_C406MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_COMB406_BASE_CODE
//
// MessageText:
//
// EMS Combine406 Error
//
#define EMS_COMB406_BASE_CODE            ((EMS_RESULT)0x8004BD00L)

//
// MessageId: EMS_COMB406_SERVICE_START
//
// MessageText:
//
// EMS Combine406 Service Started
//
#define EMS_COMB406_SERVICE_START        ((EMS_RESULT)0x0004BD01L)

//
// MessageId: EMS_COMB406_SERVICE_FAILED
//
// MessageText:
//
// EMS Combine406 Service did not start due to error %1
//
#define EMS_COMB406_SERVICE_FAILED       ((EMS_RESULT)0x0004BD02L)

//
// MessageId: EMS_COMB406_SERVICE_STOP
//
// MessageText:
//
// EMS Combine406 Service Stopped
//
#define EMS_COMB406_SERVICE_STOP         ((EMS_RESULT)0x0004BD03L)

//
// MessageId: EMS_COMB406_PROCESSING_START
//
// MessageText:
//
// EMS Combine406 Processing %1 records.
//
#define EMS_COMB406_PROCESSING_START     ((EMS_RESULT)0x0004BD04L)

//
// MessageId: EMS_COMB406_PROCESSING_STOP
//
// MessageText:
//
// EMS Combine406 completed proccessing.
//
#define EMS_COMB406_PROCESSING_STOP      ((EMS_RESULT)0x0004BD05L)

//
// MessageId: EMS_COMB406_ERROR
//
// MessageText:
//
// EMS Combine406 reports error %1.
//
#define EMS_COMB406_ERROR                ((EMS_RESULT)0x8004BD06L)

//
// MessageId: EMS_COMB406_FORCED_UNLOCK
//
// MessageText:
//
// EMS Combine406 forced an UNLOCK
//
#define EMS_COMB406_FORCED_UNLOCK        ((EMS_RESULT)0x8004BD07L)

//
// MessageId: EMS_COMB406_RECV_COMMAND
//
// MessageText:
//
// EMS Combine406 received command ( %1 ).
//
#define EMS_COMB406_RECV_COMMAND         ((EMS_RESULT)0x0004BD08L)

//
// MessageId: EMS_COMB406_TRACER
//
// MessageText:
//
// EMS Combine406 tracer ( %1 ).
//
#define EMS_COMB406_TRACER               ((EMS_RESULT)0x0004BD09L)

//
// MessageId: EMS_COMB406_SUMMARY
//
// MessageText:
//
// EMS Combine406 Summary ( %1 ).
//
#define EMS_COMB406_SUMMARY              ((EMS_RESULT)0x0004BD0AL)

//
// MessageId: EMS_COMB406_GEOSARR_BUFFER_OVERFLOW
//
// MessageText:
//
// EMS Combine406 GEOSarr buffer overflow has occurred.
//
#define EMS_COMB406_GEOSARR_BUFFER_OVERFLOW ((EMS_RESULT)0x8004BD0BL)

//
// MessageId: EMS_COMB406_GEOSARR_DATA_ADD_ERROR
//
// MessageText:
//
// EMS Combine406: Failed to add GEOSarr data to buffer (%1:%2)
//
#define EMS_COMB406_GEOSARR_DATA_ADD_ERROR ((EMS_RESULT)0x8004BD0CL)

//
// MessageId: EMS_COMB406_TRACER_CALIB406READ
//
// MessageText:
//
// EMS Combine406 tracer ( %1 Calib406 Records read ).
//
#define EMS_COMB406_TRACER_CALIB406READ  ((EMS_RESULT)0x0004BD0DL)

//
// MessageId: EMS_COMB406_CONFIGREAD_ERROR
//
// MessageText:
//
// Error reading %1 configuration, using %2.
//
#define EMS_COMB406_CONFIGREAD_ERROR     ((EMS_RESULT)0x8004BD0EL)


#endif // INC_C406MSGS
/********************************************************************
*	Module:			CommMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Comms Service Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2007 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_COMMMSGS
#define INC_COMMMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_COMM_BASE_CODE
//
// MessageText:
//
// EMS Comms Error
//
#define EMS_COMM_BASE_CODE               ((EMS_RESULT)0x8004B300L)

//
// MessageId: EMS_COMM_SERVICE_START
//
// MessageText:
//
// EMS Comms Service Started
//
#define EMS_COMM_SERVICE_START           ((EMS_RESULT)0x0004B301L)

//
// MessageId: EMS_COMM_SERVICE_FAILED
//
// MessageText:
//
// EMS Comms Service did not start due to error %1
//
#define EMS_COMM_SERVICE_FAILED          ((EMS_RESULT)0x0004B302L)

//
// MessageId: EMS_COMM_SERVICE_STOP
//
// MessageText:
//
// EMS Comms Service Stopped
//
#define EMS_COMM_SERVICE_STOP            ((EMS_RESULT)0x0004B303L)

//
// MessageId: EMS_COMM_ERROR
//
// MessageText:
//
// EMS Comms reports error %1.
//
#define EMS_COMM_ERROR                   ((EMS_RESULT)0x8004B304L)

//
// MessageId: EMS_COMM_FTP_LOGON_FAILED
//
// MessageText:
//
// EMS Comms unable to log on remote server ( %1 )
//
#define EMS_COMM_FTP_LOGON_FAILED        ((EMS_RESULT)0x8004B305L)

//
// MessageId: EMS_COMM_FTP_STORE_FAILED
//
// MessageText:
//
// EMS Comms unable to FTP copy file ( %1 ).
//
#define EMS_COMM_FTP_STORE_FAILED        ((EMS_RESULT)0x8004B306L)

//
// MessageId: EMS_COMM_FTP_RENAME_FAILED
//
// MessageText:
//
// EMS Comms unable to FTP rename file ( %1 ).
//
#define EMS_COMM_FTP_RENAME_FAILED       ((EMS_RESULT)0x8004B307L)

//
// MessageId: EMS_COMM_NO_MATCHING_DEST
//
// MessageText:
//
// EMS Comms unable to find matching destination for %1.  
//
#define EMS_COMM_NO_MATCHING_DEST        ((EMS_RESULT)0x8004B308L)

//
// MessageId: EMS_COMM_SEND_RETRY_LIMIT
//
// MessageText:
//
// EMS Comms exceeded retries attempting to send file %1.
//
#define EMS_COMM_SEND_RETRY_LIMIT        ((EMS_RESULT)0x8004B309L)

//
// MessageId: EMS_COMM_RECV_BAD_SEQ
//
// MessageText:
//
// EMS Comms received message %1 out of sequence.
//
#define EMS_COMM_RECV_BAD_SEQ            ((EMS_RESULT)0x8004B30AL)

//
// MessageId: EMS_COMM_BAD_SEND_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Send' directory.
//
#define EMS_COMM_BAD_SEND_DIR            ((EMS_RESULT)0x8004B30BL)

//
// MessageId: EMS_COMM_BAD_SENT_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Sent' directory.
//
#define EMS_COMM_BAD_SENT_DIR            ((EMS_RESULT)0x8004B30CL)

//
// MessageId: EMS_COMM_BAD_RECV_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Received' directory.
//
#define EMS_COMM_BAD_RECV_DIR            ((EMS_RESULT)0x8004B30DL)

//
// MessageId: EMS_COMM_BAD_PROCESSED_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Processed' directory.
//
#define EMS_COMM_BAD_PROCESSED_DIR       ((EMS_RESULT)0x8004B30EL)

//
// MessageId: EMS_COMM_BAD_UNDELIVERED_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Undelivered' directory.
//
#define EMS_COMM_BAD_UNDELIVERED_DIR     ((EMS_RESULT)0x8004B30FL)

//
// MessageId: EMS_COMM_BAD_DATA_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Data' directory.
//
#define EMS_COMM_BAD_DATA_DIR            ((EMS_RESULT)0x8004B310L)

//
// MessageId: EMS_COMM_TRACER
//
// MessageText:
//
// EMS Comms tracer (%1).
//
#define EMS_COMM_TRACER                  ((EMS_RESULT)0x0004B311L)

//
// MessageId: EMS_COMM_MOVE_FILE_ERROR
//
// MessageText:
//
// EMS Comms reports an error copying file (%1).
//
#define EMS_COMM_MOVE_FILE_ERROR         ((EMS_RESULT)0x8004B312L)

//
// MessageId: EMS_COMM_MSG_RECV
//
// MessageText:
//
// EMS Comms reports message (%1) received.
//
#define EMS_COMM_MSG_RECV                ((EMS_RESULT)0x0004B313L)

//
// MessageId: EMS_COMM_MSG_SENT
//
// MessageText:
//
// EMS Comms reports message (%1) sent.
//
#define EMS_COMM_MSG_SENT                ((EMS_RESULT)0x0004B314L)

//
// MessageId: EMS_COMM_SERVICE_START_PURGE
//
// MessageText:
//
// EMS Comms starting to purge message files.
//
#define EMS_COMM_SERVICE_START_PURGE     ((EMS_RESULT)0x0004B315L)

//
// MessageId: EMS_COMM_PURGE_MSG
//
// MessageText:
//
// EMS Comms, %1 purged.
//
#define EMS_COMM_PURGE_MSG               ((EMS_RESULT)0x0004B316L)

//
// MessageId: EMS_COMM_UNABLE_PURGE_MSG
//
// MessageText:
//
// EMS Comms unable to purge file in (%1).
//
#define EMS_COMM_UNABLE_PURGE_MSG        ((EMS_RESULT)0x8004B317L)

//
// MessageId: EMS_COMM_ROUTE_OFFLINE
//
// MessageText:
//
// EMS Comms reports one of the routes is currently offline (%1).
//
#define EMS_COMM_ROUTE_OFFLINE           ((EMS_RESULT)0x8004B318L)

//
// MessageId: EMS_COMM_BAD_LOCAL_DIR
//
// MessageText:
//
// EMS Comms was unable to access destination directory for at least one of the outgoing Routes.
//
#define EMS_COMM_BAD_LOCAL_DIR           ((EMS_RESULT)0x8004B319L)

//
// MessageId: EMS_COMM_ROUTE_ONLINE
//
// MessageText:
//
// EMS Comms reports route %1 is back online.
//
#define EMS_COMM_ROUTE_ONLINE            ((EMS_RESULT)0x8004B31AL)

//
// MessageId: EMS_COMM_BAD_TRANSFER_DIR
//
// MessageText:
//
// EMS Comms was unable to access the configured transfer directory.
//
#define EMS_COMM_BAD_TRANSFER_DIR        ((EMS_RESULT)0x8004B31BL)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED
//
// MessageText:
//
// An error occurred while processing the file ( %1 ).
//
#define EMS_COMM_MSG_UNDELIVERED         ((EMS_RESULT)0x8004B31CL)

//
// MessageId: EMS_COMM_TRACER_CONFIG
//
// MessageText:
//
// EMS Comms tracer (cfg: %1=%2).
//
#define EMS_COMM_TRACER_CONFIG           ((EMS_RESULT)0x0004B31DL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_YES
//
// MessageText:
//
// EMS Comms tracer (cfg: %1=yes).
//
#define EMS_COMM_TRACER_CONFIG_YES       ((EMS_RESULT)0x0004B31EL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_NO
//
// MessageText:
//
// EMS Comms tracer (cfg: %1=no).
//
#define EMS_COMM_TRACER_CONFIG_NO        ((EMS_RESULT)0x0004B31FL)

//
// MessageId: EMS_COMM_TRACER_CONFIG_ROUTE
//
// MessageText:
//
// EMS Comms tracer (cfg: Route #%1: Timeout=%2).
//
#define EMS_COMM_TRACER_CONFIG_ROUTE     ((EMS_RESULT)0x0004B320L)

//
// MessageId: EMS_COMM_TRACER_SHARINGVIOLATION_PROC
//
// MessageText:
//
// EMS Comms tracer (Sharing Violation while moving %1 to processing).
//
#define EMS_COMM_TRACER_SHARINGVIOLATION_PROC ((EMS_RESULT)0x0004B321L)

//
// MessageId: EMS_COMM_TRACER_SHARINGVIOLATION_UNDEL
//
// MessageText:
//
// EMS Comms tracer (Sharing Violation while moving %1 to Undelivered).
//
#define EMS_COMM_TRACER_SHARINGVIOLATION_UNDEL ((EMS_RESULT)0x0004B322L)

//
// MessageId: EMS_COMM_TRACER_MOVEFILE
//
// MessageText:
//
// EMS Comms tracer (MoveFile(%1) hr=%2).
//
#define EMS_COMM_TRACER_MOVEFILE         ((EMS_RESULT)0x0004B323L)

//
// MessageId: EMS_COMM_PURGE_MSGDIR
//
// MessageText:
//
// EMS Comms, %1 messages in <%2> purged.
//
#define EMS_COMM_PURGE_MSGDIR            ((EMS_RESULT)0x0004B324L)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED_WITHERR
//
// MessageText:
//
// An error occurred while processing the file ( File name = %1, Err = %2 ).
//
#define EMS_COMM_MSG_UNDELIVERED_WITHERR ((EMS_RESULT)0x8004B325L)

//
// MessageId: EMS_COMM_ROUTE_OFFLINE_WITHERR
//
// MessageText:
//
// EMS Comms reports one of the routes is currently offline (Route = %1, Err = %2).
//
#define EMS_COMM_ROUTE_OFFLINE_WITHERR   ((EMS_RESULT)0x8004B326L)

//
// MessageId: EMS_COMM_MOVE_RETRY_FAILURE
//
// MessageText:
//
// EMS Comms reports a failure moving the file <%1> to <%2>.  The operating system reports error <%3>.
//
#define EMS_COMM_MOVE_RETRY_FAILURE      ((EMS_RESULT)0x8004B327L)

//
// MessageId: EMS_COMM_IP_STATUS
//
// MessageText:
//
// PR,IP,%1
//
#define EMS_COMM_IP_STATUS               ((EMS_RESULT)0x0004B328L)

//
// MessageId: EMS_COMM_PATHWAY_PRIMARY_ACTIVE
//
// MessageText:
//
// EMS Comms reports that the primary pathway for route %1 is now active.
//
#define EMS_COMM_PATHWAY_PRIMARY_ACTIVE  ((EMS_RESULT)0x0004B329L)

//
// MessageId: EMS_COMM_PATHWAY_ALTERNATE_ACTIVE
//
// MessageText:
//
// EMS Comms reports that the alternate pathway for route %1 is now active.
//
#define EMS_COMM_PATHWAY_ALTERNATE_ACTIVE ((EMS_RESULT)0x0004B32AL)

//
// MessageId: EMS_COMM_IP_STATUS_TOO_MANY
//
// MessageText:
//
// EMS Comms reports that the number of active IP addresses exceeds the size of the notification message.  Maximum number of IPs is %1.  The output message may be missing IP addresses.
//
#define EMS_COMM_IP_STATUS_TOO_MANY      ((EMS_RESULT)0x8004B32BL)

//
// MessageId: EMS_COMM_NO_CONNECTION_MANAGER
//
// MessageText:
//
// EMS Comms reports that the Network Connection Manager subsystem is not installed.  As a result, Comms will not be able to report the active local IP addresses.
//
#define EMS_COMM_NO_CONNECTION_MANAGER   ((EMS_RESULT)0x0004B32CL)

//
// MessageId: EMS_COMM_ZIP_FILE_FAILED
//
// MessageText:
//
// EMS Comms reports a failure while zipping file "%1".  Error= %2.
//
#define EMS_COMM_ZIP_FILE_FAILED         ((EMS_RESULT)0x0004B32DL)

//
// MessageId: EMS_COMM_UNZIP_FILE_FAILED
//
// MessageText:
//
// EMS Comms reports a failure while unzipping file "%1".  Error= %2.
//
#define EMS_COMM_UNZIP_FILE_FAILED       ((EMS_RESULT)0x0004B32EL)

//
// MessageId: EMS_COMM_MSG_UNDELIVERED_NO_MATCHING_SOURCE
//
// MessageText:
//
// EMS Comms failed to process file (%1). Unable to find matching configuration for message originator (%2).
//
#define EMS_COMM_MSG_UNDELIVERED_NO_MATCHING_SOURCE ((EMS_RESULT)0x8004B32FL)

//
// MessageId: EMS_COMM_BAD_OFFLINE_DIR
//
// MessageText:
//
// EMS Comms was unable to access 'Offline' directory.
//
#define EMS_COMM_BAD_OFFLINE_DIR         ((EMS_RESULT)0x8004B330L)


#endif // INC_COMMMSGS
/********************************************************************
*	Module:			MastMsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Master Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_MASTMSGS
#define INC_MASTMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_MAST_BASE_CODE
//
// MessageText:
//
// EMS Master Error
//
#define EMS_MAST_BASE_CODE               ((EMS_RESULT)0x8004AB00L)

//
// MessageId: EMS_MAST_SERVICE_START
//
// MessageText:
//
// EMS Master Service Started
//
#define EMS_MAST_SERVICE_START           ((EMS_RESULT)0x0004AB01L)

//
// MessageId: EMS_MAST_SERVICE_FAILED
//
// MessageText:
//
// EMS Master Service did not start due to error %1
//
#define EMS_MAST_SERVICE_FAILED          ((EMS_RESULT)0x8004AB02L)

//
// MessageId: EMS_MAST_SERVICE_STOP
//
// MessageText:
//
// EMS Master Service Stopped
//
#define EMS_MAST_SERVICE_STOP            ((EMS_RESULT)0x0004AB03L)

//
// MessageId: EMS_MAST_PASS_START
//
// MessageText:
//
// EMS Master Service Starting Pass ( Sat=%1, Lut=%2, Flags=%3 )
//
#define EMS_MAST_PASS_START              ((EMS_RESULT)0x0004AB04L)

//
// MessageId: EMS_MAST_PASS_STOP
//
// MessageText:
//
// EMS Master Service Stopped Pass for Sat %1
//
#define EMS_MAST_PASS_STOP               ((EMS_RESULT)0x0004AB05L)

//
// MessageId: EMS_MAST_ERROR
//
// MessageText:
//
// EMS Master reports error %1.
//
#define EMS_MAST_ERROR                   ((EMS_RESULT)0x8004AB06L)

//
// MessageId: EMS_MAST_RECV_COMMAND
//
// MessageText:
//
// EMS Master received command ( %1 ).
//
#define EMS_MAST_RECV_COMMAND            ((EMS_RESULT)0x0004AB07L)

//
// MessageId: EMS_MAST_GPSCLOCK_DIFF
//
// MessageText:
//
// EMS Master : System clock differs from the GPS clock by %1 seconds.
//
#define EMS_MAST_GPSCLOCK_DIFF           ((EMS_RESULT)0x8004AB08L)

//
// MessageId: EMS_MAST_SITEINFO_ERR
//
// MessageText:
//
// EMS Master : Reports error %1 while trying to retrieve site information.
//
#define EMS_MAST_SITEINFO_ERR            ((EMS_RESULT)0x8004AB09L)

//
// MessageId: EMS_MAST_MSG_IGNORED
//
// MessageText:
//
// EMS Master : Ignoring message in file %1 - Unsupported.
//
#define EMS_MAST_MSG_IGNORED             ((EMS_RESULT)0x8004AB0AL)

//
// MessageId: EMS_MAST_SEND_TRACK_SCHED
//
// MessageText:
//
// EMS Master sending track schedule to database.
//
#define EMS_MAST_SEND_TRACK_SCHED        ((EMS_RESULT)0x0004AB0BL)

//
// MessageId: EMS_MAST_ERR_TRACK_SCHED
//
// MessageText:
//
// EMS Master reports error %1 sending track schedule.
//
#define EMS_MAST_ERR_TRACK_SCHED         ((EMS_RESULT)0x8004AB0CL)

//
// MessageId: EMS_MAST_SCHEDINFO_ERR
//
// MessageText:
//
// EMS Master : Reports error %1 while trying to retrieve schedule information.
//
#define EMS_MAST_SCHEDINFO_ERR           ((EMS_RESULT)0x8004AB0DL)

//
// MessageId: EMS_MAST_PASS_END
//
// MessageText:
//
// EMS Master reports end of pass
//
#define EMS_MAST_PASS_END                ((EMS_RESULT)0x0004AB0EL)

//
// MessageId: EMS_MASTER_TRACER
//
// MessageText:
//
// EMS Master tracer (%1).
//
#define EMS_MASTER_TRACER                ((EMS_RESULT)0x0004AB0FL)

//
// MessageId: EMS_MAST_GPSCLOCK_CHANGE
//
// MessageText:
//
// EMS Master : System clock adjusted by %1 seconds by the GPS clock.
//
#define EMS_MAST_GPSCLOCK_CHANGE         ((EMS_RESULT)0x0004AB10L)

//
// MessageId: EMS_MAST_SIT_UNKNOWN
//
// MessageText:
//
// EMS Master : Unknown SitMsg (%1) ignored.
//
#define EMS_MAST_SIT_UNKNOWN             ((EMS_RESULT)0x8004AB11L)

//
// MessageId: EMS_MAST_SIT_ERR
//
// MessageText:
//
// EMS Master : Error while processing SitMsg ( %1 ).
//
#define EMS_MAST_SIT_ERR                 ((EMS_RESULT)0x8004AB12L)

//
// MessageId: EMS_MAST_SIT415
//
// MessageText:
//
// EMS Master : SitMsg415 processed ( %1 ). 
//
#define EMS_MAST_SIT415                  ((EMS_RESULT)0x0004AB13L)

//
// MessageId: EMS_MAST_SIT510
//
// MessageText:
//
// EMS Master : SitMsg510 processed ( %1 ). 
//
#define EMS_MAST_SIT510                  ((EMS_RESULT)0x0004AB14L)

//
// MessageId: EMS_MAST_SIT_UNEXPECTED
//
// MessageText:
//
// EMS Master : SitMsg %1 was unexpected ( File=%2 ). 
//
#define EMS_MAST_SIT_UNEXPECTED          ((EMS_RESULT)0x8004AB15L)

//
// MessageId: EMS_MAST_SIT255
//
// MessageText:
//
// EMS Master : SitMsg255 processed ( %1 ). 
//
#define EMS_MAST_SIT255                  ((EMS_RESULT)0x0004AB16L)

//
// MessageId: EMS_MAST_SIT215
//
// MessageText:
//
// EMS Master : SitMsg215 processed ( Sat=%1, Freq=%2, Time=%3 ). 
//
#define EMS_MAST_SIT215                  ((EMS_RESULT)0x0004AB17L)

//
// MessageId: EMS_MAST_CREATE_INSTANCE_ERR
//
// MessageText:
//
// EMS Master : Unable to create instance of %1 during startup.
//
#define EMS_MAST_CREATE_INSTANCE_ERR     ((EMS_RESULT)0x8004AB18L)

//
// MessageId: EMS_MAST_SYSTEM_STARTUP
//
// MessageText:
//
// EMS Master : Reports System Startup
//
#define EMS_MAST_SYSTEM_STARTUP          ((EMS_RESULT)0x0004AB19L)

//
// MessageId: EMS_MAST_STATUS_AOS
//
// MessageText:
//
// %1
//
#define EMS_MAST_STATUS_AOS              ((EMS_RESULT)0x0004AB1AL)

//
// MessageId: EMS_MAST_STATUS_LOS
//
// MessageText:
//
// %1,EMS Master Status
//
#define EMS_MAST_STATUS_LOS              ((EMS_RESULT)0x0004AB1BL)

//
// MessageId: EMS_MAST_NO_SYSTEST_TIME
//
// MessageText:
//
// EMS Master reports insufficient time for system test.
//
#define EMS_MAST_NO_SYSTEST_TIME         ((EMS_RESULT)0x0004AB1CL)

//
// MessageId: EMS_MAST_NEW_ORBIT_VECTOR
//
// MessageText:
//
// EMS Master installed new orbit vectors for %1.
//
#define EMS_MAST_NEW_ORBIT_VECTOR        ((EMS_RESULT)0x0004AB1DL)

//
// MessageId: EMS_MAST_ERR_ORBIT_VECTOR
//
// MessageText:
//
// EMS Master reports orbit vectors error for %1.
//
#define EMS_MAST_ERR_ORBIT_VECTOR        ((EMS_RESULT)0x8004AB1EL)

//
// MessageId: EMS_MAST_SIT_MSG_RECV
//
// MessageText:
//
// EMS Master received SitMsg %1.
//
#define EMS_MAST_SIT_MSG_RECV            ((EMS_RESULT)0x0004AB1FL)

//
// MessageId: EMS_MAST_PASS_IN_PROGRESS
//
// MessageText:
//
// EMS Master is currently processing a pass.
//
#define EMS_MAST_PASS_IN_PROGRESS        ((EMS_RESULT)0x0004AB20L)

//
// MessageId: EMS_MAST_RESTARTING
//
// MessageText:
//
// EMS Master was instructed to perform a WARM restart. 
//
#define EMS_MAST_RESTARTING              ((EMS_RESULT)0x0004AB21L)

//
// MessageId: EMS_MAST_REBOOT
//
// MessageText:
//
// EMS Master was instructed to perform a COLD restart. 
//
#define EMS_MAST_REBOOT                  ((EMS_RESULT)0x0004AB22L)

//
// MessageId: EMS_MAST_ERR_INVALID_ORBIT
//
// MessageText:
//
// EMS Master reports invalid orbit vectors for %1.
//
#define EMS_MAST_ERR_INVALID_ORBIT       ((EMS_RESULT)0x8004AB23L)

//
// MessageId: EMS_MAST_SIT255_ERR
//
// MessageText:
//
// EMS Master reports invalid orbit vectors when processing SitMsg255 ( %1 ).
//
#define EMS_MAST_SIT255_ERR              ((EMS_RESULT)0x8004AB24L)

//
// MessageId: EMS_MAST_SET_CONFIG
//
// MessageText:
//
// EMS Master reports config change (%1).
//
#define EMS_MAST_SET_CONFIG              ((EMS_RESULT)0x0004AB25L)

//
// MessageId: EMS_MAST_SIT750A_ERR
//
// MessageText:
//
// EMS Master reports syntax error processing SIT 750A ( %1 ).
//
#define EMS_MAST_SIT750A_ERR             ((EMS_RESULT)0x8004AB26L)

//
// MessageId: EMS_MAST_AUDIO_NOT_AVAIL
//
// MessageText:
//
// EMS Master unable to retrieve requested audio data ( %1 ).
//
#define EMS_MAST_AUDIO_NOT_AVAIL         ((EMS_RESULT)0x8004AB27L)

//
// MessageId: EMS_MAST_SIT750A_INVALID_OPTION
//
// MessageText:
//
// EMS Master reports invalid option in SIT 750A ( %1 ).
//
#define EMS_MAST_SIT750A_INVALID_OPTION  ((EMS_RESULT)0x8004AB28L)

//
// MessageId: EMS_MAST_GENERATED_PASS_SCHED
//
// MessageText:
//
// EMS Master generated a new pass schedule.
//
#define EMS_MAST_GENERATED_PASS_SCHED    ((EMS_RESULT)0x0004AB29L)

//
// MessageId: EMS_MAST_GENERATED_PASS_SCHED_ERR
//
// MessageText:
//
// EMS Master reports error ( %1 ) while generating a new pass schedule.
//
#define EMS_MAST_GENERATED_PASS_SCHED_ERR ((EMS_RESULT)0x8004AB2AL)

//
// MessageId: EMS_MAST_INSTALLED_PASS_SCHED
//
// MessageText:
//
// EMS Master installed a new pass schedule.
//
#define EMS_MAST_INSTALLED_PASS_SCHED    ((EMS_RESULT)0x0004AB2BL)

//
// MessageId: EMS_MAST_DISK_PASS_SCHED
//
// MessageText:
//
// EMS Master installed last saved pass schedule.
//
#define EMS_MAST_DISK_PASS_SCHED         ((EMS_RESULT)0x0004AB2CL)

//
// MessageId: EMS_MAST_SITMSG_PASS_SCHED
//
// MessageText:
//
// EMS Master received a new pass schedule.
//
#define EMS_MAST_SITMSG_PASS_SCHED       ((EMS_RESULT)0x0004AB2DL)

//
// MessageId: EMS_MAST_VALIDATE_PASS_SCHED
//
// MessageText:
//
// EMS Master received a pass schedule to validate.
//
#define EMS_MAST_VALIDATE_PASS_SCHED     ((EMS_RESULT)0x0004AB2EL)

//
// MessageId: EMS_MAST_SCHED_VALIDATED
//
// MessageText:
//
// EMS Master validated received pass schedule (VALI).
//
#define EMS_MAST_SCHED_VALIDATED         ((EMS_RESULT)0x0004AB2FL)

//
// MessageId: EMS_MAST_SCHED_INVALID
//
// MessageText:
//
// EMS Master reports no valid entries in received pass schedule (VALI).
//
#define EMS_MAST_SCHED_INVALID           ((EMS_RESULT)0x0004AB30L)

//
// MessageId: EMS_MAST_SCHED_INFO
//
// MessageText:
//
// EMS Master received a pass schedule for information only.
//
#define EMS_MAST_SCHED_INFO              ((EMS_RESULT)0x0004AB31L)

//
// MessageId: EMS_MAST_SCHED_BAD_OPTION
//
// MessageText:
//
// EMS Master received a pass schedule with an unrecognised install option.
//
#define EMS_MAST_SCHED_BAD_OPTION        ((EMS_RESULT)0x0004AB32L)

//
// MessageId: EMS_MAST_BAD_ORBIT_OPTION
//
// MessageText:
//
// EMS Master encountered invalid MF605 while processing orbit vector.
//
#define EMS_MAST_BAD_ORBIT_OPTION        ((EMS_RESULT)0x0004AB33L)

//
// MessageId: EMS_MAST_SYSTEST_MISSING_SERVICE
//
// MessageText:
//
// EMS Master timed out waiting for the Antenna or SysTest Service.
//
#define EMS_MAST_SYSTEST_MISSING_SERVICE ((EMS_RESULT)0x8004AB34L)

//
// MessageId: EMS_MAST_PENDING_SCHEDULE
//
// MessageText:
//
// EMS Master reports pending schedule, waiting for end of pass.
//
#define EMS_MAST_PENDING_SCHEDULE        ((EMS_RESULT)0x0004AB35L)

//
// MessageId: EMS_ORBIT_NUMBER_NOT_MATCH
//
// MessageText:
//
// EMS Master reports one or more passes in the supplied schedule had different orbit number.
//
#define EMS_ORBIT_NUMBER_NOT_MATCH       ((EMS_RESULT)0x0004AB36L)

//
// MessageId: EMS_MAST_FORCED_ENDOFPASS
//
// MessageText:
//
// EMS Master reports handling forced end of pass.
//
#define EMS_MAST_FORCED_ENDOFPASS        ((EMS_RESULT)0x8004AB37L)

//
// MessageId: EMS_MAST_INITIAL_PROCESS_TIMEOUT
//
// MessageText:
//
// EMS Master timed out waiting for the core services to start.
//
#define EMS_MAST_INITIAL_PROCESS_TIMEOUT ((EMS_RESULT)0x8004AB38L)

//
// MessageId: EMS_MAST_SYSTEST_TIME_CONFLICT
//
// MessageText:
//
// EMS Master skipping system test due to insufficient time or pass conflict.
//
#define EMS_MAST_SYSTEST_TIME_CONFLICT   ((EMS_RESULT)0x0004AB39L)

//
// MessageId: EMS_MAST_COMMAND_NOT_SUPPORTED
//
// MessageText:
//
// EMS Master reports receiving a command that is not handled.
//
#define EMS_MAST_COMMAND_NOT_SUPPORTED   ((EMS_RESULT)0x8004AB3AL)

//
// MessageId: EMS_MAST_PASS_SCHED_CANT_INSTALL
//
// MessageText:
//
// EMS Master reports an error installing the pass schedule.  A pass in progress.
//
#define EMS_MAST_PASS_SCHED_CANT_INSTALL ((EMS_RESULT)0x8004AB3BL)

//
// MessageId: EMS_MAST_CREATE_INSTANCE_ERR_HR
//
// MessageText:
//
// EMS Master : Unable to create instance of %1 during startup (Error=%2).
//
#define EMS_MAST_CREATE_INSTANCE_ERR_HR  ((EMS_RESULT)0x8004AB3CL)

//
// MessageId: EMS_MASTER_TRACE_PASSSCHEDSETTINGS
//
// MessageText:
//
// EMS Master tracer ( PassSchedSettings: PrePass=%1, Tol=%2, Flags=%3 )
//
#define EMS_MASTER_TRACE_PASSSCHEDSETTINGS ((EMS_RESULT)0x0004AB3DL)

//
// MessageId: EMS_MAST_SITEINFO_ERR_HR
//
// MessageText:
//
// EMS Master : Reports error %2 while trying to retrieve site information %1.
//
#define EMS_MAST_SITEINFO_ERR_HR         ((EMS_RESULT)0x8004AB3EL)

//
// MessageId: EMS_MAST_ERR_INVALID_SATORBIT
//
// MessageText:
//
// EMS Master reports invalid orbit vectors for sat=%1.
//
#define EMS_MAST_ERR_INVALID_SATORBIT    ((EMS_RESULT)0x8004AB3FL)

//
// MessageId: EMS_MASTER_TRACE_NOACK
//
// MessageText:
//
// EMS Master tracer ( No ACK: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NOACK           ((EMS_RESULT)0x0004AB40L)

//
// MessageId: EMS_MASTER_TRACE_NORESPONSE
//
// MessageText:
//
// EMS Master tracer ( No Response: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NORESPONSE      ((EMS_RESULT)0x0004AB41L)

//
// MessageId: EMS_MASTER_TRACE_NOLOG
//
// MessageText:
//
// EMS Master tracer ( No Log: Msg(%1) hr(%2) )
//
#define EMS_MASTER_TRACE_NOLOG           ((EMS_RESULT)0x0004AB42L)

//
// MessageId: EMS_MAST_SIT255_MSG
//
// MessageText:
//
// EMS Master : SitMsg255 processed ( Message=%1 ). 
//
#define EMS_MAST_SIT255_MSG              ((EMS_RESULT)0x0004AB43L)

//
// MessageId: EMS_MAST_SIT255_ERR_MSG
//
// MessageText:
//
// EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1 ).  
//
#define EMS_MAST_SIT255_ERR_MSG          ((EMS_RESULT)0x8004AB44L)

//
// MessageId: EMS_MAST_SIT415_DETAILS
//
// MessageText:
//
// EMS Master : SitMsg415 processed ( Sat=%1  Freq=%2 Time=%3 ). 
//
#define EMS_MAST_SIT415_DETAILS          ((EMS_RESULT)0x0004AB45L)

//
// MessageId: EMS_MAST_SIT510_DETAILS
//
// MessageText:
//
// EMS Master : SitMsg510 processed ( Sat=%1 FreqOffset=%2 ). 
//
#define EMS_MAST_SIT510_DETAILS          ((EMS_RESULT)0x0004AB46L)

//
// MessageId: EMS_MAST_TIME_ZONE
//
// MessageText:
//
// EMS Master reports system clock not set to UTC, daylight savings OFF (%1).
//
#define EMS_MAST_TIME_ZONE               ((EMS_RESULT)0x8004AB47L)

//
// MessageId: EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
// EMS Master installed new orbit vectors for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_NEW_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x0004AB48L)

//
// MessageId: EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
// EMS Master reports orbit vectors error for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_ERR_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x8004AB49L)

//
// MessageId: EMS_MAST_ERR_INVALID_ORBIT_SAT
//
// MessageText:
//
// EMS Master reports invalid orbit vectors for Sat=%1.
//
#define EMS_MAST_ERR_INVALID_ORBIT_SAT   ((EMS_RESULT)0x8004AB4AL)

//
// MessageId: EMS_MAST_PASS_SCHED_FILE_EMPTY
//
// MessageText:
//
// EMS Master reports finding the Pass Schedule file, but it contains no passes.
//
#define EMS_MAST_PASS_SCHED_FILE_EMPTY   ((EMS_RESULT)0x0004AB4BL)

//
// MessageId: EMS_MAST_STOPPING_DB
//
// MessageText:
//
// EMS Master is stopping the database.
//
#define EMS_MAST_STOPPING_DB             ((EMS_RESULT)0x0004AB4CL)

//
// MessageId: EMS_MAST_FAILED_TO_START_DB
//
// MessageText:
//
// EMS Master : Failed to start the database (%1).
//
#define EMS_MAST_FAILED_TO_START_DB      ((EMS_RESULT)0x8004AB4DL)

//
// MessageId: EMS_MAST_FAILED_TO_STOP_DB
//
// MessageText:
//
// EMS Master : Failed to stop the database (%1).
//
#define EMS_MAST_FAILED_TO_STOP_DB       ((EMS_RESULT)0x8004AB4EL)

//
// MessageId: EMS_MAST_SCHED_REJECTED
//
// MessageText:
//
// EMS Master: Supplied pass schedule was rejected as invalid.
//
#define EMS_MAST_SCHED_REJECTED          ((EMS_RESULT)0x8004AB4FL)

//
// MessageId: EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT
//
// MessageText:
//
// EMS Master: The orbit data for satellite %1 may be corrupted. Pass schedule validation found %2 passes for this satellite that do not match the LUT predicted times.
//
#define EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT ((EMS_RESULT)0x8004AB50L)

//
// MessageId: EMS_MAST_PASS_OUTSIDE_TOLERANCE
//
// MessageText:
//
// EMS Master reports one or more passes in the supplied schedule were suppressed. Given AOS/LOS times did not match LUT predictions.
//
#define EMS_MAST_PASS_OUTSIDE_TOLERANCE  ((EMS_RESULT)0x8004AB51L)

//
// MessageId: EMS_MAST_PASS_TOO_OLD
//
// MessageText:
//
// EMS Master reports one or more passes in the supplied schedule were suppressed. AOS/LOS times were too old.
//
#define EMS_MAST_PASS_TOO_OLD            ((EMS_RESULT)0x8004AB52L)

//
// MessageId: EMS_MAST_PASS_ERROR_DURING_VALIDATION
//
// MessageText:
//
// EMS Master reports pass suppressed because of error detected during validation (%1).
//
#define EMS_MAST_PASS_ERROR_DURING_VALIDATION ((EMS_RESULT)0x8004AB53L)

//
// MessageId: EMS_MAST_PASS_SCHED_NO_VALID_PASSES
//
// MessageText:
//
// EMS Master: Pass schedule rejected. There were no unsupressed passes to be processed by this LUT.
//
#define EMS_MAST_PASS_SCHED_NO_VALID_PASSES ((EMS_RESULT)0x8004AB54L)

//
// MessageId: EMS_MAST_SARP_CALIBRATIONTIME_INVALID
//
// MessageText:
//
// EMS Master: Invalid sarp calibration data.  Difference between new and old calibration times exceeds configured maximum.
//
#define EMS_MAST_SARP_CALIBRATIONTIME_INVALID ((EMS_RESULT)0x8004AB55L)

//
// MessageId: EMS_MAST_SARP_REFFREQUENCY_INVALID
//
// MessageText:
//
// EMS Master: Invalid sarp calibration data.  Difference between new and old reference frequencies exceed configured maximum.
//
#define EMS_MAST_SARP_REFFREQUENCY_INVALID ((EMS_RESULT)0x8004AB56L)

//
// MessageId: EMS_MAST_SARP_REFFREQUENCY_CALIBRATIONTIME_INVALID
//
// MessageText:
//
// EMS Master: Invalid sarp calibration data.  Differences between old and new values for calibration time and reference frequency both exceed configured maximums.
//
#define EMS_MAST_SARP_REFFREQUENCY_CALIBRATIONTIME_INVALID ((EMS_RESULT)0x8004AB57L)

//
// MessageId: EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
// EMS Master installed post manoeuvre orbit vectors for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_MAST_POST_MANOEUVRE_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x0004AB58L)

//
// MessageId: EMS_MAST_OUTDATED_VECTORS
//
// MessageText:
//
// EMS Master reports that installed orbit vectors for Sat %1 were installed %2 days ago and may now be out of date.
//
#define EMS_MAST_OUTDATED_VECTORS        ((EMS_RESULT)0x8004AB59L)

//
// MessageId: EMS_MAST_OUTDATED_TCAL
//
// MessageText:
//
// EMS Master reports that TCAL data for Sat %1 was installed %2 days ago and may now be out of date.
//
#define EMS_MAST_OUTDATED_TCAL           ((EMS_RESULT)0x8004AB5AL)

//
// MessageId: EMS_MAST_ORBIT_PROBLEM
//
// MessageText:
//
// EMS Master reports Orbit Error %1 for Sat %2.
//
#define EMS_MAST_ORBIT_PROBLEM           ((EMS_RESULT)0x8004AB5BL)

//
// MessageId: EMS_MAST_SIT_SARPCALIB_DETAILS
//
// MessageText:
//
// EMS Master : Sarp Calibration (SitMsg%1) received ( Sat=%2  Freq=%3 Time=%4 ). 
//
#define EMS_MAST_SIT_SARPCALIB_DETAILS   ((EMS_RESULT)0x0004AB5CL)

//
// MessageId: EMS_MAST_GPSCLOCK_ERROR
//
// MessageText:
//
// EMS Master : Failed to communicate with GPS clock (%1).
//
#define EMS_MAST_GPSCLOCK_ERROR          ((EMS_RESULT)0x8004AB5DL)

//
// MessageId: EMS_MAST_SIT255_ERR_MSG2
//
// MessageText:
//
// EMS Master reports invalid orbit vectors when processing SitMsg255 ( Message=%1, Error=%2 ).
//
#define EMS_MAST_SIT255_ERR_MSG2         ((EMS_RESULT)0x8004AB5EL)

//
// MessageId: EMS_MAST_ERR_SAT_NO_ORBIT_DATA
//
// MessageText:
//
// EMS Master reports no orbit data available for satellite <%1>.
//
#define EMS_MAST_ERR_SAT_NO_ORBIT_DATA   ((EMS_RESULT)0x8004AB5FL)

//
// MessageId: EMS_MAST_RESTARTING_FP
//
// MessageText:
//
// EMS Master sending a restart command to the FP.
//
#define EMS_MAST_RESTARTING_FP           ((EMS_RESULT)0x0004AB60L)

//
// MessageId: EMS_MAST_REBOOTING_FP
//
// MessageText:
//
// EMS Master sending a reboot command to the FP.
//
#define EMS_MAST_REBOOTING_FP            ((EMS_RESULT)0x0004AB61L)

//
// MessageId: EMS_MAST_EXCEPTION_SENDING_FP_RESTART
//
// MessageText:
//
// EMS Master: Exception while sending a restart command to the FP.
//
#define EMS_MAST_EXCEPTION_SENDING_FP_RESTART ((EMS_RESULT)0x8004AB62L)

//
// MessageId: EMS_MAST_EXCEPTION_SENDING_FP_REBOOT
//
// MessageText:
//
// EMS Master: Exception while sending a reboot command to the FP.
//
#define EMS_MAST_EXCEPTION_SENDING_FP_REBOOT ((EMS_RESULT)0x8004AB63L)


#endif // INC_MASTMSGS
/********************************************************************
*	Module:			STestMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS System Test Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_STESTMSG
#define INC_STESTMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SYSTEST_BASE_CODE
//
// MessageText:
//
// EMS System Test Error
//
#define EMS_SYSTEST_BASE_CODE            ((EMS_RESULT)0x8004AE00L)

//
// MessageId: EMS_SYSTEST_SERVICE_START
//
// MessageText:
//
// EMS System Test Service Started
//
#define EMS_SYSTEST_SERVICE_START        ((EMS_RESULT)0x0004AE01L)

//
// MessageId: EMS_SYSTEST_SERVICE_FAILED
//
// MessageText:
//
// EMS System Test Service did not start due to error %1
//
#define EMS_SYSTEST_SERVICE_FAILED       ((EMS_RESULT)0x0004AE02L)

//
// MessageId: EMS_SYSTEST_SERVICE_STOP
//
// MessageText:
//
// EMS System Test Service Stopped
//
#define EMS_SYSTEST_SERVICE_STOP         ((EMS_RESULT)0x0004AE03L)

//
// MessageId: EMS_SYSTEST_ERROR
//
// MessageText:
//
// EMS System Test reports error %1.
//
#define EMS_SYSTEST_ERROR                ((EMS_RESULT)0x8004AE04L)

//
// MessageId: EMS_SYSTEST_TIMEOUT
//
// MessageText:
//
// EMS System Test timed out during operation.
//
#define EMS_SYSTEST_TIMEOUT              ((EMS_RESULT)0x8004AE05L)

//
// MessageId: EMS_SYSTEST_START
//
// MessageText:
//
// EMS System Test Initiated.
//
#define EMS_SYSTEST_START                ((EMS_RESULT)0x0004AE06L)

//
// MessageId: EMS_SYSTEST_FAIL_ANTENNA
//
// MessageText:
//
// EMS System Test Indicates Possible Antenna Problem %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_FAIL_ANTENNA         ((EMS_RESULT)0x8004AE07L)

//
// MessageId: EMS_SYSTEST_FAIL_POWER
//
// MessageText:
//
// EMS System Test Indicates Possible Signal Reception Problem %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_FAIL_POWER           ((EMS_RESULT)0x8004AE08L)

//
// MessageId: EMS_SYSTEST_STATUS
//
// MessageText:
//
// %1,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS               ((EMS_RESULT)0x0004AE09L)

//
// MessageId: EMS_SYSTEST_PASSED
//
// MessageText:
//
// EMS System Test Passed  %1 ( ADCrms @ az:el ).
//
#define EMS_SYSTEST_PASSED               ((EMS_RESULT)0x0004AE0AL)

//
// MessageId: EMS_SYSTEST_NO_AGC_SWITCH_INFO
//
// MessageText:
//
// EMS System Test reports AGC switch not available yet.
//
#define EMS_SYSTEST_NO_AGC_SWITCH_INFO   ((EMS_RESULT)0x0004AE0BL)

//
// MessageId: EMS_SYSTEST_NO_AGC_SWITCH_ALARM
//
// MessageText:
//
// EMS System Test reports AGC switch not available.
//
#define EMS_SYSTEST_NO_AGC_SWITCH_ALARM  ((EMS_RESULT)0x8004AE0BL)

//
// MessageId: EMS_SYSTEST_NO_ANTENNA
//
// MessageText:
//
// EMS System Test unable to communicate with the Antenna Service.
//
#define EMS_SYSTEST_NO_ANTENNA           ((EMS_RESULT)0x8004AE0CL)

//
// MessageId: EMS_SYSTEST_STATUS_OKAY
//
// MessageText:
//
// %1,OKAY,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS_OKAY          ((EMS_RESULT)0x0004AE0DL)

//
// MessageId: EMS_SYSTEST_STATUS_FAILED
//
// MessageText:
//
// %1,FAILED,EMS System Test Status 
//
#define EMS_SYSTEST_STATUS_FAILED        ((EMS_RESULT)0x0004AE0EL)

//
// MessageId: EMS_SYSTEST_NOT_INIT
//
// MessageText:
//
// EMS System Test has not initialized.
//
#define EMS_SYSTEST_NOT_INIT             ((EMS_RESULT)0x8004AE0FL)

//
// MessageId: EMS_SYSTEST_ALREADY_IN_TEST
//
// MessageText:
//
// EMS System Test cannot process the request to start a system test as a test is currently underway.
//
#define EMS_SYSTEST_ALREADY_IN_TEST      ((EMS_RESULT)0x8004AE10L)

//
// MessageId: EMS_SYSTEST_NO_TX_SWITCH_ALARM
//
// MessageText:
//
// EMS System Test reports Transmitter switch not available.
//
#define EMS_SYSTEST_NO_TX_SWITCH_ALARM   ((EMS_RESULT)0x8004AE11L)

//
// MessageId: EMS_SYSTEST_TX_SWITCH_ON_FP
//
// MessageText:
//
// EMS System Test expecting Transmitter to be switched on the FP.
//
#define EMS_SYSTEST_TX_SWITCH_ON_FP      ((EMS_RESULT)0x0004AE12L)


#endif // INC_STESTMSG
/********************************************************************
*	Module:			DBSMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for LeoLut600DBS Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	03/01/24		jb		start

********************************************************************/
#ifndef INC_DBSMSGS
#define INC_DBSMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

// EMSLEO600DBS_E_DUPLICATE_KEY to retain original numeric value:
//		MAKE_HRESULT( SEVERITY_ERROR, FACILITY_ITF, 0x7400 ) 
// Define first, before the base code, so that new 
// messages can use the +1 syntax
//
// MessageId: EMSLEO600DBS_E_DUPLICATE_KEY
//
// MessageText:
//
// EMS LeoLut600 Database: Insert failed due to duplicate primary key.
//
#define EMSLEO600DBS_E_DUPLICATE_KEY     ((EMS_RESULT)0x80047400L)

//
// MessageId: EMS_DBS_BASE_CODE
//
// MessageText:
//
// EMS LeoLut600 Database
//
#define EMS_DBS_BASE_CODE                ((EMS_RESULT)0x8004BF00L)

//
// MessageId: EMS_DBS_ERROR
//
// MessageText:
//
// Error %1 occurred while accessing %2.
//
#define EMS_DBS_ERROR                    ((EMS_RESULT)0x8004BF01L)

//
// MessageId: EMS_DBS_ADO_EXCEPTION
//
// MessageText:
//
// An ADO exception occurred while accessing %1:  error code = %2, description = %3, source = %4.
//
#define EMS_DBS_ADO_EXCEPTION            ((EMS_RESULT)0x8004BF02L)

//
// MessageId: EMS_DBS_SQL
//
// MessageText:
//
// The following SQL statement failed during execution:  %1.
//
#define EMS_DBS_SQL                      ((EMS_RESULT)0x8004BF03L)

//
// MessageId: EMS_DBS_SERVICE_DELETE_ERR
//
// MessageText:
//
// EMS LeoLut600 Database: Service could not be deleted.
//
#define EMS_DBS_SERVICE_DELETE_ERR       ((EMS_RESULT)0x8004BF04L)

//
// MessageId: EMS_DBS_HANDLERNOTINSTALLED
//
// MessageText:
//
// EMS LeoLut600 Database: Handler not installed
//
#define EMS_DBS_HANDLERNOTINSTALLED      ((EMS_RESULT)0x8004BF05L)

//
// MessageId: EMS_DBS_SERVICESTOPPED
//
// MessageText:
//
// EMS LeoLut600 Database: Service stopped
//
#define EMS_DBS_SERVICESTOPPED           ((EMS_RESULT)0x0004BF06L)

//
// MessageId: EMS_DBS_SERVICESTARTED
//
// MessageText:
//
// EMS LeoLut600 Database: Service started
//
#define EMS_DBS_SERVICESTARTED           ((EMS_RESULT)0x0004BF07L)

//
// MessageId: EMS_DBS_BADSERVICEREQUEST
//
// MessageText:
//
// EMS LeoLut600 Database: Bad service request received.
//
#define EMS_DBS_BADSERVICEREQUEST        ((EMS_RESULT)0x8004BF08L)

//
// MessageId: EMS_DBS_SMOPEN_ERR
//
// MessageText:
//
// Couldn't open service manager
//
#define EMS_DBS_SMOPEN_ERR               ((EMS_RESULT)0x8004BF09L)

//
// MessageId: EMS_DBS_CREATESERVICE_ERR
//
// MessageText:
//
// Couldn't create service
//
#define EMS_DBS_CREATESERVICE_ERR        ((EMS_RESULT)0x8004BF0AL)

//
// MessageId: EMS_DBS_OPENSERVICE_ERR
//
// MessageText:
//
// Couldn't open service
//
#define EMS_DBS_OPENSERVICE_ERR          ((EMS_RESULT)0x8004BF0BL)

//
// MessageId: EMS_DBS_E_NOTABLE
//
// MessageText:
//
// EMS LeoLut600 Database: Invalid column or table name specified. Please confirm that your database has been upgraded to the latest version.
//
#define EMS_DBS_E_NOTABLE                ((EMS_RESULT)0x8004BF0CL)


#endif // INC_DBSMSGS
/********************************************************************
*	Module:			ODetMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Orbit Determination Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_ODETMSGS
#define INC_ODETMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ODET_BASE_CODE
//
// MessageText:
//
// EMS OrbitDet Error
//
#define EMS_ODET_BASE_CODE               ((EMS_RESULT)0x8004A700L)

//
// MessageId: EMS_ODET_SERVICE_START
//
// MessageText:
//
// EMS OrbitDet Service Started
//
#define EMS_ODET_SERVICE_START           ((EMS_RESULT)0x0004A701L)

//
// MessageId: EMS_ODET_SERVICE_FAILED
//
// MessageText:
//
// EMS OrbitDet Service did not start due to error %1
//
#define EMS_ODET_SERVICE_FAILED          ((EMS_RESULT)0x0004A702L)

//
// MessageId: EMS_ODET_SERVICE_STOP
//
// MessageText:
//
// EMS OrbitDet Service Stopped
//
#define EMS_ODET_SERVICE_STOP            ((EMS_RESULT)0x0004A703L)

//
// MessageId: EMS_ODET_PROCESSING_START
//
// MessageText:
//
// EMS OrbitDet Processing %1 records.
//
#define EMS_ODET_PROCESSING_START        ((EMS_RESULT)0x0004A704L)

//
// MessageId: EMS_ODET_PROCESSING_STOP
//
// MessageText:
//
// EMS OrbitDet completed proccessing.
//
#define EMS_ODET_PROCESSING_STOP         ((EMS_RESULT)0x0004A705L)

//
// MessageId: EMS_ODET_ERROR
//
// MessageText:
//
// EMS OrbitDet reports error %1.
//
#define EMS_ODET_ERROR                   ((EMS_RESULT)0x8004A706L)

//
// MessageId: EMS_ODET_FORCED_UNLOCK
//
// MessageText:
//
// EMS OrbitDet forced an UNLOCK
//
#define EMS_ODET_FORCED_UNLOCK           ((EMS_RESULT)0x8004A707L)

//
// MessageId: EMS_ODET_RECV_COMMAND
//
// MessageText:
//
// EMS OrbitDet received command ( %1 ).
//
#define EMS_ODET_RECV_COMMAND            ((EMS_RESULT)0x0004A708L)

//
// MessageId: EMS_ODET_TRACER
//
// MessageText:
//
// EMS OrbitDet tracer ( %1 ).
//
#define EMS_ODET_TRACER                  ((EMS_RESULT)0x0004A709L)

//
// MessageId: EMS_ODET_SUMMARY
//
// MessageText:
//
// EMS OrbitDet Summary ( %1 ).
//
#define EMS_ODET_SUMMARY                 ((EMS_RESULT)0x0004A70AL)

//
// MessageId: EMS_ODET_BOUNDS_ALARM
//
// MessageText:
//
// EMS OrbitDet reports out of bounds condition { Sat, Pos, Pts, StDev = %1 }
//
#define EMS_ODET_BOUNDS_ALARM            ((EMS_RESULT)0x0004A70BL)

//
// MessageId: EMS_ODET_TLE_UPDATE
//
// MessageText:
//
// EMS OrbitDet has updated TLE vector.
//
#define EMS_ODET_TLE_UPDATE              ((EMS_RESULT)0x0004A70CL)

//
// MessageId: EMS_ODET_TLE_REJECTED
//
// MessageText:
//
// EMS OrbitDet has insufficient data to update TLE vector.
//
#define EMS_ODET_TLE_REJECTED            ((EMS_RESULT)0x0004A70DL)

//
// MessageId: EMS_ODET_TRACER_TRACKRECSREAD
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records read)
//
#define EMS_ODET_TRACER_TRACKRECSREAD    ((EMS_RESULT)0x0004A70EL)

//
// MessageId: EMS_ODET_TRACER_CALIB406RECSREAD
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records read)
//
#define EMS_ODET_TRACER_CALIB406RECSREAD ((EMS_RESULT)0x0004A70FL)

//
// MessageId: EMS_ODET_TRACER_CALIB406RECSACC
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Calib406 Records accepted)
//
#define EMS_ODET_TRACER_CALIB406RECSACC  ((EMS_RESULT)0x0004A710L)

//
// MessageId: EMS_ODET_TRACER_TRACKRECSWRITTEN
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) %3 Track Records written)
//
#define EMS_ODET_TRACER_TRACKRECSWRITTEN ((EMS_RESULT)0x0004A711L)

//
// MessageId: EMS_ODET_TRACER_ENDOFPASS
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) EndOfPass)
//
#define EMS_ODET_TRACER_ENDOFPASS        ((EMS_RESULT)0x0004A712L)

//
// MessageId: EMS_ODET_TRACER_LOCKED
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Locked)
//
#define EMS_ODET_TRACER_LOCKED           ((EMS_RESULT)0x0004A713L)

//
// MessageId: EMS_ODET_TRACER_UNLOCKED
//
// MessageText:
//
// EMS OrbitDet tracer ((SatID=%1,Pass=%2) _Unlocked)
//
#define EMS_ODET_TRACER_UNLOCKED         ((EMS_RESULT)0x0004A714L)

//
// MessageId: EMS_ODET_TRACER_UNEXPECTEDSTATE
//
// MessageText:
//
// EMS OrbitDet tracer (_DoEndOfPass : Unexpected State(%1))
//
#define EMS_ODET_TRACER_UNEXPECTEDSTATE  ((EMS_RESULT)0x0004A715L)

//
// MessageId: EMS_ODET_TRACER_MISMATCHEDSAT
//
// MessageText:
//
// EMS OrbitDet tracer (_DoEndOfPass : Sat %1 != Sat %2)
//
#define EMS_ODET_TRACER_MISMATCHEDSAT    ((EMS_RESULT)0x0004A716L)

//
// MessageId: EMS_ODET_TRACER_CONFIGTHRESHOLDS
//
// MessageText:
//
// EMS OrbitDet tracer (OrbitDet config: SatId  %1, PosThr %2 km, VelThr %3 m/sec, DurMax %4 days, ItrMin %5, ItrMax %6)
//
#define EMS_ODET_TRACER_CONFIGTHRESHOLDS ((EMS_RESULT)0x0004A717L)

//
// MessageId: EMS_ODET_TRACER_CONFIGRESIDUALSTRUE
//
// MessageText:
//
// EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk TRUE, MinPts %3)
//
#define EMS_ODET_TRACER_CONFIGRESIDUALSTRUE ((EMS_RESULT)0x0004A718L)

//
// MessageId: EMS_ODET_TRACER_CONFIGRESIDUALSFALSE
//
// MessageText:
//
// EMS OrbitDet tracer (OrbitDet config:   ResMin %1 Hz, ResMax %2 Hz, DwnLnk FALSE, MinPts %3)
//
#define EMS_ODET_TRACER_CONFIGRESIDUALSFALSE ((EMS_RESULT)0x0004A719L)

//
// MessageId: EMS_ODET_PROCESSING_STARTSATPASS
//
// MessageText:
//
// EMS OrbitDet Processing Start (SatID=%1,Pass=%2).
//
#define EMS_ODET_PROCESSING_STARTSATPASS ((EMS_RESULT)0x0004A71AL)

//
// MessageId: EMS_ODET_SUMMARYDETAILS
//
// MessageText:
//
// EMS OrbitDet Summary ( SatID=%1,Pass=%2, pos=%3, vel=%4, std=%5, num=%6 )
//
#define EMS_ODET_SUMMARYDETAILS          ((EMS_RESULT)0x0004A71BL)

//
// MessageId: EMS_ODET_BOUNDS_ALARMDETAILS
//
// MessageText:
//
// EMS OrbitDet reports out of bounds condition { Sat, Pos, Vel, Pts, StDev = %1, %2, %3, %4, %5 }
//
#define EMS_ODET_BOUNDS_ALARMDETAILS     ((EMS_RESULT)0x8004A71CL)

//
// MessageId: EMS_ODET_POST_MANOEUVRE
//
// MessageText:
//
// EMS OrbitDet will exclude all data from Sat ID %1 prior to %2.
//
#define EMS_ODET_POST_MANOEUVRE          ((EMS_RESULT)0x0004A71DL)


#endif // INC_ODETMSGS
/********************************************************************
*	Module:			Alarmsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Leo Alarm Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_ALARMSGS
#define INC_ALARMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif


//	****** NOTE ******* Warning and Alarms of the same type MUST
//	****** NOTE ******* share the same error number.

//
// MessageId: EMS_ALARM_BASE_CODE
//
// MessageText:
//
// EMS Master Error
//
#define EMS_ALARM_BASE_CODE              ((EMS_RESULT)0x0004CC00L)

//
// MessageId: EMS_ALARM_ANTENNA_NOT_MOVING
//
// MessageText:
//
// Alarm: Antenna has not moved in the last %1 seconds.
//
#define EMS_ALARM_ANTENNA_NOT_MOVING     ((EMS_RESULT)0xC004CC01L)

//
// MessageId: EMS_WARN_ANTENNA_NOT_MOVING
//
// MessageText:
//
// Warning: Antenna has not moved in the last %1 seconds.
//
#define EMS_WARN_ANTENNA_NOT_MOVING      ((EMS_RESULT)0x8004CC01L)

//
// MessageId: EMS_ALARM_ANTENNA_BEAM_ANGLE
//
// MessageText:
//
// Alarm: Antenna direction is outside of tolerance (%1 deg ).
//
#define EMS_ALARM_ANTENNA_BEAM_ANGLE     ((EMS_RESULT)0xC004CC02L)

//
// MessageId: EMS_WARN_ANTENNA_BEAM_ANGLE
//
// MessageText:
//
// Warning: Antenna direction is outside of tolerance (%1 deg ).
//
#define EMS_WARN_ANTENNA_BEAM_ANGLE      ((EMS_RESULT)0x8004CC02L)

//
// MessageId: EMS_ALARM_COMM_RETRY_LIMIT
//
// MessageText:
//
// Alarm: Communications Retry Count %1 has exceeded limit.
//
#define EMS_ALARM_COMM_RETRY_LIMIT       ((EMS_RESULT)0xC004CC03L)

//
// MessageId: EMS_WARN_COMM_RETRY_LIMIT
//
// MessageText:
//
// Warning: Communications Retry Count %1 has exceeded limit.
//
#define EMS_WARN_COMM_RETRY_LIMIT        ((EMS_RESULT)0x8004CC03L)

//
// MessageId: EMS_ALARM_COMM_CONTACT_LIMIT
//
// MessageText:
//
// Alarm: No comms messages have been received in %1 minutes.
//
#define EMS_ALARM_COMM_CONTACT_LIMIT     ((EMS_RESULT)0xC004CC04L)

//
// MessageId: EMS_WARN_COMM_CONTACT_LIMIT
//
// MessageText:
//
// Warning: No comms messages have been received in %1 minutes.
//
#define EMS_WARN_COMM_CONTACT_LIMIT      ((EMS_RESULT)0x8004CC04L)

//
// MessageId: EMS_ALARM_NO_CBC_121
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_121             ((EMS_RESULT)0xC004CC05L)

//
// MessageId: EMS_WARN_NO_CBC_121
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of CBC 121Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_121              ((EMS_RESULT)0x8004CC05L)

//
// MessageId: EMS_ALARM_NO_CBC_243
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_243             ((EMS_RESULT)0xC004CC06L)

//
// MessageId: EMS_WARN_NO_CBC_243
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of CBC 243Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_243              ((EMS_RESULT)0x8004CC06L)

//
// MessageId: EMS_ALARM_NO_CBC_406
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
//
#define EMS_ALARM_NO_CBC_406             ((EMS_RESULT)0xC004CC07L)

//
// MessageId: EMS_WARN_NO_CBC_406
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of CBC 406Mhz Signals Detected
//
#define EMS_WARN_NO_CBC_406              ((EMS_RESULT)0x8004CC07L)

//
// MessageId: EMS_ALARM_NO_SARR_406
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
//
#define EMS_ALARM_NO_SARR_406            ((EMS_RESULT)0xC004CC08L)

//
// MessageId: EMS_WARN_NO_SARR_406
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of 406Mhz SARR Signals Detected
//
#define EMS_WARN_NO_SARR_406             ((EMS_RESULT)0x8004CC08L)

//
// MessageId: EMS_ALARM_NO_SARP_406
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
//
#define EMS_ALARM_NO_SARP_406            ((EMS_RESULT)0xC004CC09L)

//
// MessageId: EMS_WARN_NO_SARP_406
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of 406Mhz SARP Signals Detected
//
#define EMS_WARN_NO_SARP_406             ((EMS_RESULT)0x8004CC09L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS
//
// MessageText:
//
// Alarm: Expecting more than (%1) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS     ((EMS_RESULT)0xC004CC0AL)

//
// MessageId: EMS_WARN_PASS_TOO_FEW_SOLNS
//
// MessageText:
//
// Warning: Expecting more than (%1) solutions.
//
#define EMS_WARN_PASS_TOO_FEW_SOLNS      ((EMS_RESULT)0x8004CC0AL)

//
// MessageId: EMS_ALARM_INSIDE_TEMP_RANGE
//
// MessageText:
//
// Alarm: Inside Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_INSIDE_TEMP_RANGE      ((EMS_RESULT)0xC004CC0BL)

//
// MessageId: EMS_WARN_INSIDE_TEMP_RANGE
//
// MessageText:
//
// Warning: Inside Temperature of %1 exceeds limits. 
//
#define EMS_WARN_INSIDE_TEMP_RANGE       ((EMS_RESULT)0x8004CC0BL)

//
// MessageId: EMS_ALARM_OUTSIDE_TEMP_RANGE
//
// MessageText:
//
// Alarm: Outside Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_OUTSIDE_TEMP_RANGE     ((EMS_RESULT)0xC004CC0CL)

//
// MessageId: EMS_WARN_OUTSIDE_TEMP_RANGE
//
// MessageText:
//
// Warning: Outside Temperature of %1 exceeds limits. 
//
#define EMS_WARN_OUTSIDE_TEMP_RANGE      ((EMS_RESULT)0x8004CC0CL)

//
// MessageId: EMS_ALARM_EQUIP_TEMP_RANGE
//
// MessageText:
//
// Alarm: Rack Temperature of %1 exceeds limits. 
//
#define EMS_ALARM_EQUIP_TEMP_RANGE       ((EMS_RESULT)0xC004CC0DL)

//
// MessageId: EMS_WARN_EQUIP_TEMP_RANGE
//
// MessageText:
//
// Warning: Rack Temperature of %1 exceeds limits. 
//
#define EMS_WARN_EQUIP_TEMP_RANGE        ((EMS_RESULT)0x8004CC0DL)

//
// MessageId: EMS_ALARM_COLLECTOR_MODINDEX
//
// MessageText:
//
// Alarm: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_ALARM_COLLECTOR_MODINDEX     ((EMS_RESULT)0xC004CC0EL)

//
// MessageId: EMS_WARN_COLLECTOR_MODINDEX
//
// MessageText:
//
// Warning: Collector reporting high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_WARN_COLLECTOR_MODINDEX      ((EMS_RESULT)0x8004CC0EL)

//
// MessageId: EMS_ALARM_COLLECTOR_ADC_LEVEL
//
// MessageText:
//
// Alarm: Collector reporting low ADC level of %1
//
#define EMS_ALARM_COLLECTOR_ADC_LEVEL    ((EMS_RESULT)0xC004CC0FL)

//
// MessageId: EMS_WARN_COLLECTOR_ADC_LEVEL
//
// MessageText:
//
// Warning: Collector reporting low ADC level of %1
//
#define EMS_WARN_COLLECTOR_ADC_LEVEL     ((EMS_RESULT)0x8004CC0FL)

//
// MessageId: EMS_ALARM_ON_UPS_POWER
//
// MessageText:
//
// Alarm: The AC power has been lost. There are %1 minutes of UPS Power left.
//
#define EMS_ALARM_ON_UPS_POWER           ((EMS_RESULT)0xC004CC10L)

//
// MessageId: EMS_ALARM_UPS_FAILURE
//
// MessageText:
//
// Alarm: The UPS device appears to have failed. This error can often be cleared by recycling the power to the UPS.
//
#define EMS_ALARM_UPS_FAILURE            ((EMS_RESULT)0xC004CC11L)

//
// MessageId: EMS_INFO_POWER_STATE
//
// MessageText:
//
// DV,AC Power,OK
//
#define EMS_INFO_POWER_STATE             ((EMS_RESULT)0x4004CC12L)

//
// MessageId: EMS_WARN_POWER_STATE
//
// MessageText:
//
// DV,AC Power,WARN
//
#define EMS_WARN_POWER_STATE             ((EMS_RESULT)0x8004CC12L)

//
// MessageId: EMS_ALARM_POWER_STATE
//
// MessageText:
//
// DV,AC Power,FAIL
//
#define EMS_ALARM_POWER_STATE            ((EMS_RESULT)0xC004CC12L)

//
// MessageId: EMS_INFO_ANTENNA_STATE
//
// MessageText:
//
// DV,Antenna,OK
//
#define EMS_INFO_ANTENNA_STATE           ((EMS_RESULT)0x4004CC13L)

//
// MessageId: EMS_WARN_ANTENNA_STATE
//
// MessageText:
//
// DV,Antenna,WARN
//
#define EMS_WARN_ANTENNA_STATE           ((EMS_RESULT)0x8004CC13L)

//
// MessageId: EMS_ALARM_ANTENNA_STATE
//
// MessageText:
//
// DV,Antenna,FAIL
//
#define EMS_ALARM_ANTENNA_STATE          ((EMS_RESULT)0xC004CC13L)

//
// MessageId: EMS_INFO_COMMS_STATE
//
// MessageText:
//
// DV,Comms,OK
//
#define EMS_INFO_COMMS_STATE             ((EMS_RESULT)0x4004CC14L)

//
// MessageId: EMS_WARN_COMMS_STATE
//
// MessageText:
//
// DV,Comms,WARN
//
#define EMS_WARN_COMMS_STATE             ((EMS_RESULT)0x8004CC14L)

//
// MessageId: EMS_ALARM_COMMS_STATE
//
// MessageText:
//
// DV,Comms,FAIL
//
#define EMS_ALARM_COMMS_STATE            ((EMS_RESULT)0xC004CC14L)

//
// MessageId: EMS_INFO_COLLECTOR_STATE
//
// MessageText:
//
// PR,Collector,OK
//
#define EMS_INFO_COLLECTOR_STATE         ((EMS_RESULT)0x4004CC15L)

//
// MessageId: EMS_WARN_COLLECTOR_STATE
//
// MessageText:
//
// PR,Collector,WARN
//
#define EMS_WARN_COLLECTOR_STATE         ((EMS_RESULT)0x8004CC15L)

//
// MessageId: EMS_ALARM_COLLECTOR_STATE
//
// MessageText:
//
// PR,Collector,FAIL
//
#define EMS_ALARM_COLLECTOR_STATE        ((EMS_RESULT)0xC004CC15L)

//
// MessageId: EMS_INFO_WIDEBAND_STATE
//
// MessageText:
//
// PR,Wideband,OK
//
#define EMS_INFO_WIDEBAND_STATE          ((EMS_RESULT)0x4004CC16L)

//
// MessageId: EMS_WARN_WIDEBAND_STATE
//
// MessageText:
//
// PR,Wideband,WARN
//
#define EMS_WARN_WIDEBAND_STATE          ((EMS_RESULT)0x8004CC16L)

//
// MessageId: EMS_ALARM_WIDEBAND_STATE
//
// MessageText:
//
// PR,Wideband,FAIL
//
#define EMS_ALARM_WIDEBAND_STATE         ((EMS_RESULT)0xC004CC16L)

//
// MessageId: EMS_INFO_ENVIRONMENT_STATE
//
// MessageText:
//
// NV,Environment,OK
//
#define EMS_INFO_ENVIRONMENT_STATE       ((EMS_RESULT)0x4004CC17L)

//
// MessageId: EMS_WARN_ENVIRONMENT_STATE
//
// MessageText:
//
// NV,Environment,WARN
//
#define EMS_WARN_ENVIRONMENT_STATE       ((EMS_RESULT)0x8004CC17L)

//
// MessageId: EMS_ALARM_ENVIRONMENT_STATE
//
// MessageText:
//
// NV,Environment,FAIL
//
#define EMS_ALARM_ENVIRONMENT_STATE      ((EMS_RESULT)0xC004CC17L)

//
// MessageId: EMS_INFO_PASS_STATE
//
// MessageText:
//
// PR,Pass,OK
//
#define EMS_INFO_PASS_STATE              ((EMS_RESULT)0x4004CC18L)

//
// MessageId: EMS_WARN_PASS_STATE
//
// MessageText:
//
// PR,Pass,WARN
//
#define EMS_WARN_PASS_STATE              ((EMS_RESULT)0x8004CC18L)

//
// MessageId: EMS_ALARM_PASS_STATE
//
// MessageText:
//
// PR,Pass,FAIL
//
#define EMS_ALARM_PASS_STATE             ((EMS_RESULT)0xC004CC18L)

//
// MessageId: EMS_ALARM_TRACER
//
// MessageText:
//
// StatusAlarm (%1).
//
#define EMS_ALARM_TRACER                 ((EMS_RESULT)0x4004CC19L)

//
// MessageId: EMS_ALARM_ALARMRETCODE
//
// MessageText:
//
// GeoLeoAlarmInfo retcode=%1
//
#define EMS_ALARM_ALARMRETCODE           ((EMS_RESULT)0x4004CC1AL)

//
// MessageId: EMS_ALARM_STATUSCOLLECTOR
//
// MessageText:
//
// *Status: Collector elapsed = %1, freq=%2
//
#define EMS_ALARM_STATUSCOLLECTOR        ((EMS_RESULT)0x4004CC1BL)

//
// MessageId: EMS_ALARM_SECABOVE5
//
// MessageText:
//
// Seconds Above 5 = %1
//
#define EMS_ALARM_SECABOVE5              ((EMS_RESULT)0x4004CC1CL)

//
// MessageId: EMS_ALARM_TIMEDELTA
//
// MessageText:
//
// Time Delta = %1
//
#define EMS_ALARM_TIMEDELTA              ((EMS_RESULT)0x4004CC1DL)

//
// MessageId: EMS_ALARM_ABOVE5DELTA
//
// MessageText:
//
// Above 5 TDelta = %1
//
#define EMS_ALARM_ABOVE5DELTA            ((EMS_RESULT)0x4004CC1EL)

//
// MessageId: EMS_ALARM_PDSFRAMERATE
//
// MessageText:
//
// PDSFrameRate =%1
//
#define EMS_ALARM_PDSFRAMERATE           ((EMS_RESULT)0x4004CC1FL)

//
// MessageId: EMS_ALARM_STARTPASS
//
// MessageText:
//
// StartPass Sat=%1
//
#define EMS_ALARM_STARTPASS              ((EMS_RESULT)0x4004CC20L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC121
//
// MessageText:
//
// Alarm: Expecting more than (%1 CBC 121Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC121 ((EMS_RESULT)0xC004CC21L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC121
//
// MessageText:
//
// Warning: Expecting more than (%1 CBC 121Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC121 ((EMS_RESULT)0x8004CC21L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC243
//
// MessageText:
//
// Alarm: Expecting more than (%1 CBC 243Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC243 ((EMS_RESULT)0xC004CC22L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC243
//
// MessageText:
//
// Warning: Expecting more than (%1 CBC 243Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC243 ((EMS_RESULT)0x8004CC22L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC406
//
// MessageText:
//
// Alarm: Expecting more than (%1 CBC 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_CBC406 ((EMS_RESULT)0xC004CC23L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC406
//
// MessageText:
//
// Warning: Expecting more than (%1 CBC 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_CBC406 ((EMS_RESULT)0x8004CC23L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_SARP406
//
// MessageText:
//
// Alarm: Expecting more than (%1 SARP 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_SARP406 ((EMS_RESULT)0xC004CC24L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_SARP406
//
// MessageText:
//
// Warning: Expecting more than (%1 SARP 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_SARP406 ((EMS_RESULT)0x8004CC24L)

//
// MessageId: EMS_ALARM_PASS_TOO_FEW_SOLNS_SARR406
//
// MessageText:
//
// Alarm: Expecting more than (%1 SARR 406Mhz) solutions.
//
#define EMS_ALARM_PASS_TOO_FEW_SOLNS_SARR406 ((EMS_RESULT)0xC004CC25L)

//
// MessageId: EMS_WARNING_PASS_TOO_FEW_SOLNS_SARR406
//
// MessageText:
//
// Warning: Expecting more than (%1 SARR 406Mhz) solutions.
//
#define EMS_WARNING_PASS_TOO_FEW_SOLNS_SARR406 ((EMS_RESULT)0x8004CC25L)

//
// MessageId: EMS_STATUS_MUTEX_INIT_ERROR
//
// MessageText:
//
// Master Status: Failed to obtain handle onto shared mutex.
//
#define EMS_STATUS_MUTEX_INIT_ERROR      ((EMS_RESULT)0x8004CC26L)

//
// MessageId: EMS_ALARM_TOO_FEW_GEO_DETECTIONS
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
//
#define EMS_ALARM_TOO_FEW_GEO_DETECTIONS ((EMS_RESULT)0xC004CC27L)

//
// MessageId: EMS_WARNING_TOO_FEW_GEO_DETECTIONS
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of GEOSAR Raw Beacon Messages Detected
//
#define EMS_WARNING_TOO_FEW_GEO_DETECTIONS ((EMS_RESULT)0x8004CC27L)

//
// MessageId: EMS_ALARM_TOO_FEW_GEO_INTEGRATIONS
//
// MessageText:
//
// Alarm: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
//
#define EMS_ALARM_TOO_FEW_GEO_INTEGRATIONS ((EMS_RESULT)0xC004CC28L)

//
// MessageId: EMS_WARNING_TOO_FEW_GEO_INTEGRATIONS
//
// MessageText:
//
// Warning: Fewer than the expected number (%1) of GEOSAR Valid Beacon Messages Processed
//
#define EMS_WARNING_TOO_FEW_GEO_INTEGRATIONS ((EMS_RESULT)0x8004CC28L)

//
// MessageId: EMS_INFO_COLLECTOR_MODINDEX
//
// MessageText:
//
// Info: Collector detected high mod index of %1 for satellite %2, pass %3 (elevation=%4, azimuth=%5)
//
#define EMS_INFO_COLLECTOR_MODINDEX      ((EMS_RESULT)0x4004CC29L)

//
// MessageId: EMS_ALARM_ANTENNA_FAULT
//
// MessageText:
//
// Alarm: Antenna has reported a fault.
//
#define EMS_ALARM_ANTENNA_FAULT          ((EMS_RESULT)0xC004CC2AL)

//
// MessageId: EMS_ALARM_COMM_RETRY_LIMIT_RTE
//
// MessageText:
//
// Alarm: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
//
#define EMS_ALARM_COMM_RETRY_LIMIT_RTE   ((EMS_RESULT)0xC004CC2BL)

//
// MessageId: EMS_WARN_COMM_RETRY_LIMIT_RTE
//
// MessageText:
//
// Warning: Communications Retry Count %1 has exceeded limit for route %2 and message %3.
//
#define EMS_WARN_COMM_RETRY_LIMIT_RTE    ((EMS_RESULT)0x8004CC2BL)


#endif // INC_ALARMSGS
/********************************************************************
*	Module:			TCalMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS TCAL Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_TCALMSGS
#define INC_TCALMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_TCAL_BASE_CODE
//
// MessageText:
//
// EMS TCAL Error
//
#define EMS_TCAL_BASE_CODE               ((EMS_RESULT)0x8004AC00L)

//
// MessageId: EMS_TCAL_SERVICE_START
//
// MessageText:
//
// EMS TCAL Service Started
//
#define EMS_TCAL_SERVICE_START           ((EMS_RESULT)0x0004AC01L)

//
// MessageId: EMS_TCAL_SERVICE_FAILED
//
// MessageText:
//
// EMS TCAL Service did not start due to error %1
//
#define EMS_TCAL_SERVICE_FAILED          ((EMS_RESULT)0x0004AC02L)

//
// MessageId: EMS_TCAL_SERVICE_STOP
//
// MessageText:
//
// EMS TCAL Service Stopped
//
#define EMS_TCAL_SERVICE_STOP            ((EMS_RESULT)0x0004AC03L)

//
// MessageId: EMS_TCAL_PROCESSING_START
//
// MessageText:
//
// EMS TCAL Processing %1 records.
//
#define EMS_TCAL_PROCESSING_START        ((EMS_RESULT)0x0004AC04L)

//
// MessageId: EMS_TCAL_PROCESSING_STOP
//
// MessageText:
//
// EMS TCAL completed proccessing.
//
#define EMS_TCAL_PROCESSING_STOP         ((EMS_RESULT)0x0004AC05L)

//
// MessageId: EMS_TCAL_ERROR
//
// MessageText:
//
// EMS TCAL reports error %1.
//
#define EMS_TCAL_ERROR                   ((EMS_RESULT)0x8004AC06L)

//
// MessageId: EMS_TCAL_FORCED_UNLOCK
//
// MessageText:
//
// EMS TCAL forced an UNLOCK
//
#define EMS_TCAL_FORCED_UNLOCK           ((EMS_RESULT)0x8004AC07L)

//
// MessageId: EMS_TCAL_RECV_COMMAND
//
// MessageText:
//
// EMS TCAL received command ( %1 ).
//
#define EMS_TCAL_RECV_COMMAND            ((EMS_RESULT)0x0004AC08L)

//
// MessageId: EMS_TCAL_TRACER
//
// MessageText:
//
// EMS TCAL tracer ( %1 ).
//
#define EMS_TCAL_TRACER                  ((EMS_RESULT)0x0004AC09L)

//
// MessageId: EMS_TCAL_SUMMARY
//
// MessageText:
//
// EMS TCAL Summary ( %1 ).
//
#define EMS_TCAL_SUMMARY                 ((EMS_RESULT)0x0004AC0AL)

//
// MessageId: EMS_TCAL_BOUNDS_ALARM
//
// MessageText:
//
// EMS TCAL reports out of bounds condition ( %1 ).
//
#define EMS_TCAL_BOUNDS_ALARM            ((EMS_RESULT)0x0004AC0BL)

//
// MessageId: EMS_TCAL_UPDATE
//
// MessageText:
//
// EMS TCAL has been updated ( %1 ).
//
#define EMS_TCAL_UPDATE                  ((EMS_RESULT)0x0004AC0CL)

//
// MessageId: EMS_TCAL_REJECTED
//
// MessageText:
//
// EMS TCAL has insufficient data to update ( %1 ).
//
#define EMS_TCAL_REJECTED                ((EMS_RESULT)0x0004AC0DL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTREAD
//
// MessageText:
//
// EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records read )
//
#define EMS_TCAL_SUMMARY_COUNTREAD       ((EMS_RESULT)0x0004AC0EL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTWRITTEN
//
// MessageText:
//
// EMS TCAL Summary ( Sat %1, %2/%3 TCalSarp Records written )
//
#define EMS_TCAL_SUMMARY_COUNTWRITTEN    ((EMS_RESULT)0x0004AC0FL)

//
// MessageId: EMS_TCAL_SUMMARY_COUNTUSED
//
// MessageText:
//
// EMS TCAL Summary ( Sat %1, %2 TCalSarp records being used )
//
#define EMS_TCAL_SUMMARY_COUNTUSED       ((EMS_RESULT)0x0004AC10L)

//
// MessageId: EMS_TCAL_TRACE_CONFIG
//
// MessageText:
//
// EMS TCAL tracer ( TCal config: SatId  %1, minUpdatePeriod %2, maxTimeSpan %3, minMeas %4, maxTSarpThresh %5, maxSarpFCThresh %6 )
//
#define EMS_TCAL_TRACE_CONFIG            ((EMS_RESULT)0x0004AC11L)

//
// MessageId: EMS_TCAL_BOUNDS_ALARMERR
//
// MessageText:
//
// EMS TCAL reports out of bounds condition ( Sat %1, rollErr %2 (%3) secs, fcErr %4 (%5) Hz, sdRes %6 secs )
//
#define EMS_TCAL_BOUNDS_ALARMERR         ((EMS_RESULT)0x8004AC12L)

//
// MessageId: EMS_TCAL_BOUNDS_ALARMTSPAN
//
// MessageText:
//
// EMS TCAL reports out of bounds condition ( Sat %1, tSpan %2 (%3) days, nMeas %4 (%5) )
//
#define EMS_TCAL_BOUNDS_ALARMTSPAN       ((EMS_RESULT)0x8004AC13L)

//
// MessageId: EMS_TCAL_UPDATE_PART1
//
// MessageText:
//
// EMS TCAL has been updated ( Sat %1, orb %2, span %3 days, pts %4, mean/sdev/max %5 msec )
//
#define EMS_TCAL_UPDATE_PART1            ((EMS_RESULT)0x0004AC14L)

//
// MessageId: EMS_TCAL_UPDATE_PART2
//
// MessageText:
//
// EMS TCAL has been updated ( cycles %1 msec, TSarpOffset %2 msec, corr %3, SarpFC %4 Hz )
//
#define EMS_TCAL_UPDATE_PART2            ((EMS_RESULT)0x0004AC15L)

//
// MessageId: EMS_TCAL_REJECTED_DAYSSINCE
//
// MessageText:
//
// EMS TCAL has insufficient data to update ( Sat %1, TCAL not performed, only %2 (%3) days since TSarp last updated )
//
#define EMS_TCAL_REJECTED_DAYSSINCE      ((EMS_RESULT)0x8004AC16L)


#endif // INC_TCALMSGS
/********************************************************************
*	Module:			EMSSecMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Security Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Dec01		RI		start 
		2005Jan05		CH		Ticket 6652: significant changes to 
								support use of actual error code as
								the message identifier for logging
********************************************************************/
#ifndef INC_EMSSECMSGS
#define INC_EMSSECMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SECURITY_BASE_CODE
//
// MessageText:
//
// EMS SECURITY Error
//
#define EMS_SECURITY_BASE_CODE           ((EMS_RESULT)0x8004BC00L)

//
// MessageId: EMS_SECURITY_ACCESS_DENIED
//
// MessageText:
//
// EMS Security Access Denied
//
#define EMS_SECURITY_ACCESS_DENIED       ((EMS_RESULT)0x8004BC01L)

//
// MessageId: EMS_SEC_RESOURCE_UNDEFINED
//
// MessageText:
//
// EMS Security Resource undefined
//
#define EMS_SEC_RESOURCE_UNDEFINED       ((EMS_RESULT)0x8004BC02L)

//
// MessageId: EMS_SEC_KEY_CLOSE_ERROR
//
// MessageText:
//
// EMS Security Cryptography Key closing error
//
#define EMS_SEC_KEY_CLOSE_ERROR          ((EMS_RESULT)0x8004BC03L)

//
// MessageId: EMS_SEC_KEY_FWRITE_ERR
//
// MessageText:
//
// EMS Security Writing Cryptography Key to file error
//
#define EMS_SEC_KEY_FWRITE_ERR           ((EMS_RESULT)0x8004BC04L)

//
// MessageId: EMS_SEC_KEY_FREAD_ERR
//
// MessageText:
//
// EMS Security Reading Cryptography Key file error
//
#define EMS_SEC_KEY_FREAD_ERR            ((EMS_RESULT)0x8004BC05L)

//
// MessageId: EMS_SEC_PUBLICKEY_LOAD_ERR
//
// MessageText:
//
// EMS Security Loading Public Key error
//
#define EMS_SEC_PUBLICKEY_LOAD_ERR       ((EMS_RESULT)0x8004BC06L)

//
// MessageId: EMS_SEC_PUBLICKEY_GEN_ERR
//
// MessageText:
//
// EMS Security Generating Public Key error
//
#define EMS_SEC_PUBLICKEY_GEN_ERR        ((EMS_RESULT)0x8004BC07L)

//
// MessageId: EMS_SEC_TOKEN_DECRYPT_ERR
//
// MessageText:
//
// EMS Security Decrypting token error
//
#define EMS_SEC_TOKEN_DECRYPT_ERR        ((EMS_RESULT)0x8004BC08L)

//
// MessageId: EMS_SEC_TOKEN_ENCRYPT_ERR
//
// MessageText:
//
// EMS Security Encrypting token error
//
#define EMS_SEC_TOKEN_ENCRYPT_ERR        ((EMS_RESULT)0x8004BC09L)

//
// MessageId: EMS_SEC_WRITE_KEYID_ERR
//
// MessageText:
//
// EMS Security Writing Key ID error
//
#define EMS_SEC_WRITE_KEYID_ERR          ((EMS_RESULT)0x8004BC0AL)

//
// MessageId: EMS_SEC_READ_KEYID_ERR
//
// MessageText:
//
// EMS Security Reading Key ID error
//
#define EMS_SEC_READ_KEYID_ERR           ((EMS_RESULT)0x8004BC0BL)

//
// MessageId: EMS_SEC_TOKEN_CREATETXT_ERR
//
// MessageText:
//
// EMS Security Creating text token error
//
#define EMS_SEC_TOKEN_CREATETXT_ERR      ((EMS_RESULT)0x8004BC0CL)

//
// MessageId: EMS_SEC_TOKEN_PARSE_ERR
//
// MessageText:
//
// EMS Security Parsing text token error
//
#define EMS_SEC_TOKEN_PARSE_ERR          ((EMS_RESULT)0x8004BC0DL)

//
// MessageId: EMS_SEC_TOKEN_ENCODEDTOBIN_ERR
//
// MessageText:
//
// EMS Security Error Creating binary token from encoded one
//
#define EMS_SEC_TOKEN_ENCODEDTOBIN_ERR   ((EMS_RESULT)0x8004BC0EL)

//
// MessageId: EMS_SEC_TOKEN_EXPIRED
//
// MessageText:
//
// EMS Security Error Security token expired
//
#define EMS_SEC_TOKEN_EXPIRED            ((EMS_RESULT)0x8004BC0FL)

//
// MessageId: EMS_SEC_PRIVATEKEY_LOAD_ERR
//
// MessageText:
//
// EMS Security Loading Private Key error
//
#define EMS_SEC_PRIVATEKEY_LOAD_ERR      ((EMS_RESULT)0x8004BC10L)

//
// MessageId: EMS_SEC_PRIVATEKEY_GEN_ERR
//
// MessageText:
//
// EMS Security Generating Private Key error
//
#define EMS_SEC_PRIVATEKEY_GEN_ERR       ((EMS_RESULT)0x8004BC11L)

//
// MessageId: EMS_SEC_PRIVATEKEY_FWRITE_ERR
//
// MessageText:
//
// EMS Security Writing Private Key to file error
//
#define EMS_SEC_PRIVATEKEY_FWRITE_ERR    ((EMS_RESULT)0x8004BC12L)

//
// MessageId: EMS_SEC_PRIVATEKEY_FREAD_ERR
//
// MessageText:
//
// EMS Security Reading Private Key file error
//
#define EMS_SEC_PRIVATEKEY_FREAD_ERR     ((EMS_RESULT)0x8004BC13L)

//
// MessageId: EMS_SEC_IDENTIFY_USER_ERR
//
// MessageText:
//
// EMS Security Error identifying user
//
#define EMS_SEC_IDENTIFY_USER_ERR        ((EMS_RESULT)0x8004BC14L)

//
// MessageId: EMS_SEC_EXTRACTING_USERNAME_ERR
//
// MessageText:
//
// EMS Security Error extracting user name
//
#define EMS_SEC_EXTRACTING_USERNAME_ERR  ((EMS_RESULT)0x8004BC15L)

//
// MessageId: EMS_SEC_EXTRACTING_USERGROUPS_ERR
//
// MessageText:
//
// EMS Security Error extracting user groups
//
#define EMS_SEC_EXTRACTING_USERGROUPS_ERR ((EMS_RESULT)0x8004BC16L)

//
// MessageId: EMS_SEC_NOROLEID_ERROR
//
// MessageText:
//
// EMS Security Error cannot find the role id
//
#define EMS_SEC_NOROLEID_ERROR           ((EMS_RESULT)0x8004BC17L)

//
// MessageId: EMS_SEC_GETTING_KEYINFO_ERR
//
// MessageText:
//
// EMS Security Error cannot find the security key information
//
#define EMS_SEC_GETTING_KEYINFO_ERR      ((EMS_RESULT)0x8004BC18L)

//
// MessageId: EMS_SEC_AUTHORIZATION_DISABLED
//
// MessageText:
//
// EMS Security, Authorization is disabled, the call succeeded
//
#define EMS_SEC_AUTHORIZATION_DISABLED   ((EMS_RESULT)0x0004BC19L)

//
// MessageId: EMS_SEC_CANNOT_INITIALIZE_EXCEPTION
//
// MessageText:
//
// EMS Security initialization failed with an unhandled exception
//
#define EMS_SEC_CANNOT_INITIALIZE_EXCEPTION ((EMS_RESULT)0x8004BC1AL)

//
// MessageId: EMS_SEC_CANNOT_AUTHENTICATE_EXCEPTION
//
// MessageText:
//
// EMS Security authentication failed with an unhandled exception
//
#define EMS_SEC_CANNOT_AUTHENTICATE_EXCEPTION ((EMS_RESULT)0x8004BC1BL)

//
// MessageId: EMS_SEC_INITIALIZED
//
// MessageText:
//
// Security component initialized
//
#define EMS_SEC_INITIALIZED              ((EMS_RESULT)0x0004BC1CL)

//
// MessageId: EMS_SEC_AUTH_REQUEST_RECVD
//
// MessageText:
//
// Authorization request received
//
#define EMS_SEC_AUTH_REQUEST_RECVD       ((EMS_RESULT)0x0004BC1DL)

//
// MessageId: EMS_SEC_INTERNAL_OBJ_INVALID
//
// MessageText:
//
// The Internal objects are not valid
//
#define EMS_SEC_INTERNAL_OBJ_INVALID     ((EMS_RESULT)0x8004BC1EL)

//
// MessageId: EMS_SEC_PUBLIC_KEY_INIT
//
// MessageText:
//
// Initialization of the Public key succeeded
//
#define EMS_SEC_PUBLIC_KEY_INIT          ((EMS_RESULT)0x0004BC1FL)

//
// MessageId: EMS_SEC_PRIVATE_KEY_INIT
//
// MessageText:
//
// Initialization of the Private key succeeded
//
#define EMS_SEC_PRIVATE_KEY_INIT         ((EMS_RESULT)0x0004BC20L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_LOADED
//
// MessageText:
//
// The Public Key loaded successfully
//
#define EMS_SEC_PUBLIC_KEY_LOADED        ((EMS_RESULT)0x0004BC21L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_LOADED
//
// MessageText:
//
// The Private Key loaded successfully
//
#define EMS_SEC_PRIVATE_KEY_LOADED       ((EMS_RESULT)0x0004BC22L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_LOAD_ERR
//
// MessageText:
//
// Cannot load Private Key
//
#define EMS_SEC_PRIVATE_KEY_LOAD_ERR     ((EMS_RESULT)0x8004BC23L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_LOAD_ERR
//
// MessageText:
//
// Cannot load Public Key
//
#define EMS_SEC_PUBLIC_KEY_LOAD_ERR      ((EMS_RESULT)0x8004BC24L)

//
// MessageId: EMS_SEC_PRIVATE_KEY_INIT_ERR
//
// MessageText:
//
// Cannot Initialize Private Key
//
#define EMS_SEC_PRIVATE_KEY_INIT_ERR     ((EMS_RESULT)0x8004BC25L)

//
// MessageId: EMS_SEC_PUBLIC_KEY_INIT_ERR
//
// MessageText:
//
// Cannot Initialize Public Key
//
#define EMS_SEC_PUBLIC_KEY_INIT_ERR      ((EMS_RESULT)0x8004BC26L)

//
// MessageId: EMS_SEC_TOKEN_SIZE_OK
//
// MessageText:
//
// The security token size is OK
//
#define EMS_SEC_TOKEN_SIZE_OK            ((EMS_RESULT)0x0004BC27L)

//
// MessageId: EMS_SEC_TOKEN_SET_OK
//
// MessageText:
//
// Setting the encoded token is successful
//
#define EMS_SEC_TOKEN_SET_OK             ((EMS_RESULT)0x0004BC28L)

//
// MessageId: EMS_SEC_TOKEN_DECODE_OK
//
// MessageText:
//
// The Security Token has been decoded successfully
//
#define EMS_SEC_TOKEN_DECODE_OK          ((EMS_RESULT)0x0004BC29L)

//
// MessageId: EMS_SEC_TOKEN_DECRYPT_OK
//
// MessageText:
//
// The Security Token has been decrypted successfully
//
#define EMS_SEC_TOKEN_DECRYPT_OK         ((EMS_RESULT)0x0004BC2AL)

//
// MessageId: EMS_SEC_TOKEN_PARSE_OK
//
// MessageText:
//
// The Security Token has been parsed successfully
//
#define EMS_SEC_TOKEN_PARSE_OK           ((EMS_RESULT)0x0004BC2BL)

//
// MessageId: EMS_SEC_TOKEN_DECODE_ERR
//
// MessageText:
//
// Cannot decode the Security token
//
#define EMS_SEC_TOKEN_DECODE_ERR         ((EMS_RESULT)0x8004BC2CL)

//
// MessageId: EMS_SEC_TOKEN_SET_ERR
//
// MessageText:
//
// Cannot set the encoded token.
//
#define EMS_SEC_TOKEN_SET_ERR            ((EMS_RESULT)0x8004BC2DL)

//
// MessageId: EMS_SEC_TOKEN_SIZE_ERR
//
// MessageText:
//
// The token size is not OK
//
#define EMS_SEC_TOKEN_SIZE_ERR           ((EMS_RESULT)0x8004BC2EL)

//
// MessageId: EMS_SEC_USER_IDENTIFY_RETRY
//
// MessageText:
//
// Retrying to identify the user
//
#define EMS_SEC_USER_IDENTIFY_RETRY      ((EMS_RESULT)0x0004BC2FL)

//
// MessageId: EMS_SEC_AUTHORIZATION_OK
//
// MessageText:
//
// The request has been authorized for the user: %1, role ID: %2  for resource ID: %3
//
#define EMS_SEC_AUTHORIZATION_OK         ((EMS_RESULT)0x0004BC30L)

//
// MessageId: EMS_SEC_TOKEN_CHECK_FAILED_AT
//
// MessageText:
//
// EMS Security Access Denied: The token for the user: %1 has expired Year %2 Month %3 Day %4 Hour %5 Minute %6 Second %7
//
#define EMS_SEC_TOKEN_CHECK_FAILED_AT    ((EMS_RESULT)0x8004BC31L)

//
// MessageId: EMS_SEC_ROLE_NOT_AUTHORIZED
//
// MessageText:
//
// EMS Security Access Denied: The user %1 Role ID %2 is not authorized to use the resource ID %3
//
#define EMS_SEC_ROLE_NOT_AUTHORIZED      ((EMS_RESULT)0x8004BC32L)

//
// MessageId: EMS_SEC_AUTHORIZATION_FAILED
//
// MessageText:
//
// EMS Security Access Denied: Error %4 while checking privileges: User Name %1, Role ID %2, resource requested %3
//
#define EMS_SEC_AUTHORIZATION_FAILED     ((EMS_RESULT)0x8004BC33L)

//
// MessageId: EMS_SEC_NOT_INITIALIZED
//
// MessageText:
//
// Request failed. Security subsystem has not been initialized.
//
#define EMS_SEC_NOT_INITIALIZED          ((EMS_RESULT)0x8004BC34L)

//
// MessageId: EMS_SEC_INIT_ERROR
//
// MessageText:
//
// EMS Security initialization failed.
//
#define EMS_SEC_INIT_ERROR               ((EMS_RESULT)0x8004BC35L)


#endif // INC_EMSSECMSGS
/********************************************************************
*	Module:			EMSSecMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Data Transfer Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Dec04		CH		start 

********************************************************************/
#ifndef INC_EMSDTSGS
#define INC_EMSDTMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DTX_BASE_CODE
//
// MessageText:
//
// EMS Data Transfer Error
//
#define EMS_DTX_BASE_CODE                ((EMS_RESULT)0x8004AF00L)

//
// MessageId: EMS_DTX_GENERAL_ERROR
//
// MessageText:
//
// EMS Data Transfer Access Denied %1
//
#define EMS_DTX_GENERAL_ERROR            ((EMS_RESULT)0x8004AF01L)

//
// MessageId: EMS_DTX_TRACE
//
// MessageText:
//
// EMS Data Transfer reports trace %1
//
#define EMS_DTX_TRACE                    ((EMS_RESULT)0x0004AF02L)

//
// MessageId: EMS_DTX_INFO
//
// MessageText:
//
// EMS Data Transfer Info %1
//
#define EMS_DTX_INFO                     ((EMS_RESULT)0x0004AF03L)

//
// MessageId: EMS_DTX_DEBUG
//
// MessageText:
//
// EMS Data Transfer debug message %1
//
#define EMS_DTX_DEBUG                    ((EMS_RESULT)0x0004AF04L)

//
// MessageId: EMS_DTX_NO_TYPES
//
// MessageText:
//
// EMS Data Transfer the supported types list is empty %1
//
#define EMS_DTX_NO_TYPES                 ((EMS_RESULT)0x8004AF05L)

//
// MessageId: EMS_DTX_INIT_ERROR
//
// MessageText:
//
// EMS Data Transfer Initialization error %1
//
#define EMS_DTX_INIT_ERROR               ((EMS_RESULT)0x8004AF06L)

//
// MessageId: EMS_DTX_ADD_DEST_ERROR
//
// MessageText:
//
// EMS Data Transfer Error Cannot add the destination information %1
//
#define EMS_DTX_ADD_DEST_ERROR           ((EMS_RESULT)0x8004AF07L)

//
// MessageId: EMS_DTX_SECURITY_ERROR
//
// MessageText:
//
// EMS Data Transfer Error Cannot retrieve the security token %1
//
#define EMS_DTX_SECURITY_ERROR           ((EMS_RESULT)0x8004AF08L)

//
// MessageId: EMS_DTX_DAL_ERROR
//
// MessageText:
//
// EMS Data Transfer Error retrieving data from the DAL %1
//
#define EMS_DTX_DAL_ERROR                ((EMS_RESULT)0x8004AF09L)

//
// MessageId: EMS_DTX_DATATOOBIG_ERROR
//
// MessageText:
//
// EMS Data Transfer Error data requested is too big %1
//
#define EMS_DTX_DATATOOBIG_ERROR         ((EMS_RESULT)0x8004AF0AL)

//
// MessageId: EMS_DTX_CREATEFILE_ERR
//
// MessageText:
//
// EMS Data Transfer Error creating the file %1
//
#define EMS_DTX_CREATEFILE_ERR           ((EMS_RESULT)0x8004AF0BL)

//
// MessageId: EMS_DTX_WRITEHEADER_ERR
//
// MessageText:
//
// EMS Data Transfer Error writing the file header %1
//
#define EMS_DTX_WRITEHEADER_ERR          ((EMS_RESULT)0x8004AF0CL)

//
// MessageId: EMS_DTX_ADDRECORD_ERR
//
// MessageText:
//
// EMS Data Transfer Error adding the record to the file %1
//
#define EMS_DTX_ADDRECORD_ERR            ((EMS_RESULT)0x8004AF0DL)

//
// MessageId: EMS_DTX_COPYFILE_ERR
//
// MessageText:
//
// EMS Data Transfer Error copying the file %1
//
#define EMS_DTX_COPYFILE_ERR             ((EMS_RESULT)0x8004AF0EL)

//
// MessageId: EMS_DTX_NOSTATICFILE_ERR
//
// MessageText:
//
// EMS Data Transfer Error: no file available in the static file list for the automatic data transfer %1
//
#define EMS_DTX_NOSTATICFILE_ERR         ((EMS_RESULT)0x8004AF0FL)

//
// MessageId: EMS_DTX_REGSINK_ERR
//
// MessageText:
//
// EMS Data Transfer Error registering pipeline sink%1
//
#define EMS_DTX_REGSINK_ERR              ((EMS_RESULT)0x8004AF10L)

//
// MessageId: EMS_DTX_DATATYPEMISSING_ERR
//
// MessageText:
//
// EMS Data Transfer Error cannot find data type information %1
//
#define EMS_DTX_DATATYPEMISSING_ERR      ((EMS_RESULT)0x8004AF11L)

//
// MessageId: EMS_DTX_NORECORDS_ERR
//
// MessageText:
//
// EMS Data Transfer Error: no records found %1
//
#define EMS_DTX_NORECORDS_ERR            ((EMS_RESULT)0x8004AF12L)

//
// MessageId: EMS_DTX_INIT_ERR
//
// MessageText:
//
// EMS Data Transfer: Cannot initialize the Data Transfer Subsystem
//
#define EMS_DTX_INIT_ERR                 ((EMS_RESULT)0x8004AF13L)

//
// MessageId: EMS_DTX_INIT
//
// MessageText:
//
// EMS Data Transfer: Data Transfer Subsystem initialized
//
#define EMS_DTX_INIT                     ((EMS_RESULT)0x0004AF14L)

//
// MessageId: EMS_DTX_UPLOADRECEIVED
//
// MessageText:
//
// EMS Data Transfer: Received Upload request - Destination:%1, Record Type: %2
//
#define EMS_DTX_UPLOADRECEIVED           ((EMS_RESULT)0x0004AF15L)

//
// MessageId: EMS_DTX_RETRIEVINGDATA_OK
//
// MessageText:
//
// EMS Data Transfer: Retrieving Data from DAL is OK - Destination:%1, Record Type: %2
//
#define EMS_DTX_RETRIEVINGDATA_OK        ((EMS_RESULT)0x0004AF16L)

//
// MessageId: EMS_DTX_WRITINGDATA_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot write the data retrieved from DAL - Destination:%1, Record Type: %2
//
#define EMS_DTX_WRITINGDATA_NOTOK        ((EMS_RESULT)0x8004AF17L)

//
// MessageId: EMS_DTX_WRITINGDATA_OK
//
// MessageText:
//
// EMS Data Transfer: Writing Data retrieved from DAL is OK - Destination:%1, Record Type: %2
//
#define EMS_DTX_WRITINGDATA_OK           ((EMS_RESULT)0x0004AF18L)

//
// MessageId: EMS_DTX_RETREIVINGDATA_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot retrieve Data from DAL - Destination:%1, Record Type: %2, Error: %3
//
#define EMS_DTX_RETREIVINGDATA_NOTOK     ((EMS_RESULT)0x8004AF19L)

//
// MessageId: EMS_DTX_AUTOWRITINGDATA_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot write the automatically generated data - Data Type: %1, Error: %2
//
#define EMS_DTX_AUTOWRITINGDATA_NOTOK    ((EMS_RESULT)0x8004AF1AL)

//
// MessageId: EMS_DTX_PIPELINEINIT_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot initialize Pipeline
//
#define EMS_DTX_PIPELINEINIT_NOTOK       ((EMS_RESULT)0x8004AF1BL)

//
// MessageId: EMS_DTX_REGISTERSINK_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot register pipeline sink
//
#define EMS_DTX_REGISTERSINK_NOTOK       ((EMS_RESULT)0x8004AF1CL)

//
// MessageId: EMS_DTX_READFROMSINK_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot read from pipeline's sink - Data Type: %1
//
#define EMS_DTX_READFROMSINK_NOTOK       ((EMS_RESULT)0x8004AF1DL)

//
// MessageId: EMS_DTX_CREATINGNEWFILE_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot create new file - Data Type: %1
//
#define EMS_DTX_CREATINGNEWFILE_NOTOK    ((EMS_RESULT)0x8004AF1EL)

//
// MessageId: EMS_DTX_CLOSEALLFILES_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot close all files
//
#define EMS_DTX_CLOSEALLFILES_NOTOK      ((EMS_RESULT)0x8004AF1FL)

//
// MessageId: EMS_DTX_INSERTTOCLOSEDLIST_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot insert file to the closed list - File Name: %1, Data Type: %2
//
#define EMS_DTX_INSERTTOCLOSEDLIST_NOTOK ((EMS_RESULT)0x8004AF20L)

//
// MessageId: EMS_DTX_SENDINGFILE_NOTOK
//
// MessageText:
//
// EMS Data Transfer: Cannot send the file - File Name: %1, Data Type: %2
//
#define EMS_DTX_SENDINGFILE_NOTOK        ((EMS_RESULT)0x8004AF21L)

//
// MessageId: EMS_DTX_AUTOWRITINGDATA_NOTOK_TIMESTAMP
//
// MessageText:
//
// EMS Data Transfer: Cannot write generated data to file - Type: %1, Timestamp: %3, Error: %2
//
#define EMS_DTX_AUTOWRITINGDATA_NOTOK_TIMESTAMP ((EMS_RESULT)0x8004AF22L)

//
// MessageId: EMS_DTX_STATICFILENOTINITIALIZED
//
// MessageText:
//
// EMS Data Transfer: Attempting to access data transfer file for data type %1 but support for this data type was not initialized.
//
#define EMS_DTX_STATICFILENOTINITIALIZED ((EMS_RESULT)0x8004AF23L)

//
// MessageId: EMS_DTX_NO_LOCAL_PATH
//
// MessageText:
//
// EMS Data Transfer: At initialization, no local path was specified.  
//
#define EMS_DTX_NO_LOCAL_PATH            ((EMS_RESULT)0x8004AF24L)

//
// MessageId: EMS_DTX_NO_DATA_TYPE
//
// MessageText:
//
// EMS Data Transfer: At initialization, no data type was specified.  
//
#define EMS_DTX_NO_DATA_TYPE             ((EMS_RESULT)0x8004AF25L)

//
// MessageId: EMS_DTX_NEW_NO_LOCAL_PATH
//
// MessageText:
//
// EMS Data Transfer: Failed to create a new temporary file because no local path was specified.
//
#define EMS_DTX_NEW_NO_LOCAL_PATH        ((EMS_RESULT)0x8004AF26L)

//
// MessageId: EMS_DTX_SEND_NO_PERIOD
//
// MessageText:
//
// EMS Data Transfer: Failed while processing a send request.  No send period was specified.
//
#define EMS_DTX_SEND_NO_PERIOD           ((EMS_RESULT)0x8004AF27L)

//
// MessageId: EMS_DTX_SEND_NO_SEND_PATH
//
// MessageText:
//
// EMS Data Transfer: Failed while processing a send request.  No send folder was specified.
//
#define EMS_DTX_SEND_NO_SEND_PATH        ((EMS_RESULT)0x8004AF28L)

//
// MessageId: EMS_DTX_CURRENT_FILE_EMPTY
//
// MessageText:
//
// EMS Data Transfer: Failed while processing a send request.  The current working file name is unspecified.
//
#define EMS_DTX_CURRENT_FILE_EMPTY       ((EMS_RESULT)0x8004AF29L)

//
// MessageId: EMS_DTX_INIT_CONFIG_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error %1 occurred while reading configuration data.
//
#define EMS_DTX_INIT_CONFIG_FAILURE      ((EMS_RESULT)0x8004AF2AL)

//
// MessageId: EMS_DTX_INIT_CONFIG_MAXSIZE_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error %1 retrieving maximum file size for data type %2.
//
#define EMS_DTX_INIT_CONFIG_MAXSIZE_FAILURE ((EMS_RESULT)0x8004AF2BL)

//
// MessageId: EMS_DTX_INIT_CONFIG_SENDFREQ_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error %1 retrieving sending frequency for data type %2.
//
#define EMS_DTX_INIT_CONFIG_SENDFREQ_FAILURE ((EMS_RESULT)0x8004AF2CL)

//
// MessageId: EMS_DTX_INIT_CONFIG_LOCALPATH_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving local path.
//
#define EMS_DTX_INIT_CONFIG_LOCALPATH_FAILURE ((EMS_RESULT)0x8004AF2DL)

//
// MessageId: EMS_DTX_INIT_CONFIG_SENDPATH_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving send path.
//
#define EMS_DTX_INIT_CONFIG_SENDPATH_FAILURE ((EMS_RESULT)0x8004AF2EL)

//
// MessageId: EMS_DTX_INIT_CONFIG_DESTS_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving destinations with error code %1.
//
#define EMS_DTX_INIT_CONFIG_DESTS_FAILURE ((EMS_RESULT)0x8004AF2FL)

//
// MessageId: EMS_DTX_INIT_CONFIG_EMSSTRING_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving copyright string.
//
#define EMS_DTX_INIT_CONFIG_EMSSTRING_FAILURE ((EMS_RESULT)0x8004AF30L)

//
// MessageId: EMS_DTX_INIT_CONFIG_COMMSSEND_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving Comms send folder.
//
#define EMS_DTX_INIT_CONFIG_COMMSSEND_FAILURE ((EMS_RESULT)0x8004AF31L)

//
// MessageId: EMS_DTX_INIT_CONFIG_SECTOKEN_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error retrieving security token for route %1.  Error code = %2.
//
#define EMS_DTX_INIT_CONFIG_SECTOKEN_FAILURE ((EMS_RESULT)0x8004AF32L)

//
// MessageId: EMS_DTX_INIT_SITEINFO_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Error creating instance of site info object.  Error code = %1.
//
#define EMS_DTX_INIT_SITEINFO_FAILURE    ((EMS_RESULT)0x8004AF33L)

//
// MessageId: EMS_DTX_INIT_SENDMSGFOLDER_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  Failed to retrieve the Comms send folder from configuration.  CM return code = %1.
//
#define EMS_DTX_INIT_SENDMSGFOLDER_FAILURE ((EMS_RESULT)0x8004AF34L)

//
// MessageId: EMS_DTX_SEND_NOLOCAL_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during data send operation.  The Data Transfer local path could be retrieved from configuration.
//
#define EMS_DTX_SEND_NOLOCAL_FAILURE     ((EMS_RESULT)0x8004AF35L)

//
// MessageId: EMS_DTX_ROUTE_NOGTWY_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during data send operation.  The Gateway object could not be created.  Error code is %1.
//
#define EMS_DTX_ROUTE_NOGTWY_FAILURE     ((EMS_RESULT)0x8004AF36L)

//
// MessageId: EMS_DTX_ROUTE_SENDDATA_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during data send operation.  An error occurred sending data via the Gateway object.  Error code is %1.
//
#define EMS_DTX_ROUTE_SENDDATA_FAILURE   ((EMS_RESULT)0x8004AF37L)

//
// MessageId: EMS_DTX_STARTED
//
// MessageText:
//
// EMS Data Transfer service has started.
//
#define EMS_DTX_STARTED                  ((EMS_RESULT)0x0004AF38L)

//
// MessageId: EMS_DTX_START_FAILED
//
// MessageText:
//
// EMS Data Transfer service failed to start.
//
#define EMS_DTX_START_FAILED             ((EMS_RESULT)0x8004AF39L)

//
// MessageId: EMS_DTX_STOPPED
//
// MessageText:
//
// EMS Data Transfer service has stoppped.
//
#define EMS_DTX_STOPPED                  ((EMS_RESULT)0x0004AF3AL)

//
// MessageId: EMS_DTX_NO_SITEINFO
//
// MessageText:
//
// EMS Data Transfer:  The site info object could not be created.
//
#define EMS_DTX_NO_SITEINFO              ((EMS_RESULT)0x8004AF3BL)

//
// MessageId: EMS_DTX_INIT_SRC_LUTID_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed during initialization.  The local LUT ID could not be obtained from configuration.
//
#define EMS_DTX_INIT_SRC_LUTID_FAILURE   ((EMS_RESULT)0x8004AF3CL)

//
// MessageId: EMS_DTX_INIT_DATATYPE_CONFIGURED
//
// MessageText:
//
// EMS Data Transfer: Data type (%1) is configured for collection.
//
#define EMS_DTX_INIT_DATATYPE_CONFIGURED ((EMS_RESULT)0x0004AF3DL)

//
// MessageId: EMS_DTX_INIT_DATATYPE_RT_CONFIGURED
//
// MessageText:
//
// EMS Data Transfer: Data type (%1) is configured for transmission on at least one route.
//
#define EMS_DTX_INIT_DATATYPE_RT_CONFIGURED ((EMS_RESULT)0x0004AF3EL)

//
// MessageId: EMS_DTX_INIT_NOTYPES_CONFIGURED
//
// MessageText:
//
// EMS Data Transfer: No data types are configured for collection.
//
#define EMS_DTX_INIT_NOTYPES_CONFIGURED  ((EMS_RESULT)0x0004AF3FL)

//
// MessageId: EMS_DTX_INIT_CM_READ_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed to read [%1].%2 from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_READ_FAILURE     ((EMS_RESULT)0x8004AF40L)

//
// MessageId: EMS_DTX_INIT_CM_READ_RTE_FAILURE
//
// MessageText:
//
// EMS Data Transfer: Failed to read [RTE:%1].%2 from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_READ_RTE_FAILURE ((EMS_RESULT)0x8004AF41L)

//
// MessageId: EMS_DTX_INIT_CM_NO_ROUTES
//
// MessageText:
//
// EMS Data Transfer: Failed to read set of routes from configuration.  CM returned error code %3.
//
#define EMS_DTX_INIT_CM_NO_ROUTES        ((EMS_RESULT)0x8004AF42L)

//
// MessageId: EMS_DTX_SECINIT_FAILED
//
// MessageText:
//
// EMS Data Transfer: Failed to initialize security.  Error code %1.
//
#define EMS_DTX_SECINIT_FAILED           ((EMS_RESULT)0x8004AF43L)


#endif // INC_EMSDTMSGS
/********************************************************************
*	Module:			LocnMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Location Processor 
*				Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_LOCNMSGS
#define INC_LOCNMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_LOCN_BASE_CODE
//
// MessageText:
//
// EMS Location 
//
#define EMS_LOCN_BASE_CODE               ((EMS_RESULT)0x8004A500L)

//
// MessageId: EMS_LOCN_SERVICE_START
//
// MessageText:
//
// EMS Location Service Started
//
#define EMS_LOCN_SERVICE_START           ((EMS_RESULT)0x0004A501L)

//
// MessageId: EMS_LOCN_SERVICE_STOP
//
// MessageText:
//
// EMS Location Service Stopped
//
#define EMS_LOCN_SERVICE_STOP            ((EMS_RESULT)0x0004A502L)

//
// MessageId: EMS_LOCN_SERVICE_FAILED
//
// MessageText:
//
// EMS Location Service did not start due to error %1
//
#define EMS_LOCN_SERVICE_FAILED          ((EMS_RESULT)0x8004A503L)

//
// MessageId: EMS_LOCN_PROCESSING_START
//
// MessageText:
//
// EMS Location Service starting to process %1 records
//
#define EMS_LOCN_PROCESSING_START        ((EMS_RESULT)0x0004A504L)

//
// MessageId: EMS_LOCN_PROCESSING_STOP
//
// MessageText:
//
// EMS Location Service finished processing. %1 location records output.
//
#define EMS_LOCN_PROCESSING_STOP         ((EMS_RESULT)0x0004A505L)

//
// MessageId: EMS_LOCN_TRACER
//
// MessageText:
//
// EMS Location Service Tracer ( %1 )
//
#define EMS_LOCN_TRACER                  ((EMS_RESULT)0x0004A506L)

//
// MessageId: EMS_LOCN_RECV_COMMAND
//
// MessageText:
//
// EMS Location received command( %1 ).
//
#define EMS_LOCN_RECV_COMMAND            ((EMS_RESULT)0x0004A507L)

//
// MessageId: EMS_LOCN_PROC_ERROR
//
// MessageText:
//
// EMS Location returns error %1 from _DetermineLocations.
//
#define EMS_LOCN_PROC_ERROR              ((EMS_RESULT)0x8004A508L)

//
// MessageId: EMS_LOCN_DETERMINE_LOCATION_ERROR
//
// MessageText:
//
// EMS Location reports result %1 from _DetermineLocation.
//
#define EMS_LOCN_DETERMINE_LOCATION_ERROR ((EMS_RESULT)0x8004A509L)

//
// MessageId: EMS_LOCN_BAD_DATA_DIR
//
// MessageText:
//
// EMS Location reports error %1 trying to access data directory.
//
#define EMS_LOCN_BAD_DATA_DIR            ((EMS_RESULT)0x8004A50AL)

//
// MessageId: EMS_LOCN_BAD_BCH
//
// MessageText:
//
// EMS Location reports BCH failure for Beacon %1.
//
#define EMS_LOCN_BAD_BCH                 ((EMS_RESULT)0x8004A50BL)

//
// MessageId: EMS_TLE_SERV_RETRIEVE_FAIL_RETRYING
//
// MessageText:
//
// EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Retrying.
//
#define EMS_TLE_SERV_RETRIEVE_FAIL_RETRYING ((EMS_RESULT)0x0004A50CL)

//
// MessageId: EMS_TLE_SERV_RETRIEVE_FAIL_NORETRY
//
// MessageText:
//
// EMS TLE Server reports error retrieving TLE data from DAL on attempt %1.  Maximum number of retries has been reached.
//
#define EMS_TLE_SERV_RETRIEVE_FAIL_NORETRY ((EMS_RESULT)0x8004A50DL)

//
// MessageId: EMS_LOCN_INSUFF_POINTS
//
// MessageText:
//
// EMS Location reports insufficient points for processing.
//
#define EMS_LOCN_INSUFF_POINTS           ((EMS_RESULT)0x8004A50EL)

//
// MessageId: EMS_LOCN_TRACER_DOIDLE
//
// MessageText:
//
// EMS Location Service Tracer ( Catch in DoIdle )
//
#define EMS_LOCN_TRACER_DOIDLE           ((EMS_RESULT)0x0004A50FL)

//
// MessageId: EMS_LOCN_TRACER_TCACONSTRAINED
//
// MessageText:
//
// EMS Location Service Tracer ( ** TCA was constrained to %1 seconds )
//
#define EMS_LOCN_TRACER_TCACONSTRAINED   ((EMS_RESULT)0x0004A510L)

//
// MessageId: EMS_LOCN_TRACER_EMPTYFILE
//
// MessageText:
//
// EMS Location Service Tracer ( File %1 has no data )
//
#define EMS_LOCN_TRACER_EMPTYFILE        ((EMS_RESULT)0x0004A511L)

//
// MessageId: EMS_LOCN_TRACER_FILECOUNT
//
// MessageText:
//
// EMS Location Service Tracer ( %1 recs in File %2 )
//
#define EMS_LOCN_TRACER_FILECOUNT        ((EMS_RESULT)0x0004A512L)

//
// MessageId: EMS_LOCN_TRACER_EXECTIME
//
// MessageText:
//
// EMS Location Service Tracer ( Execution time = %1 secs, dbHist %2 - %3 )
//
#define EMS_LOCN_TRACER_EXECTIME         ((EMS_RESULT)0x0004A513L)

//
// MessageId: EMS_LOCN_LEOCALIBREG_ERROR
//
// MessageText:
//
// Unable to register LEO_CALIBRATE_406_DATA sink
//
#define EMS_LOCN_LEOCALIBREG_ERROR       ((EMS_RESULT)0x8004A514L)

//
// MessageId: EMS_LOCN_LEOCOMBREG_ERROR
//
// MessageText:
//
// Unable to register LEO_COMBINE_406_DATA sink
//
#define EMS_LOCN_LEOCOMBREG_ERROR        ((EMS_RESULT)0x8004A515L)

//
// MessageId: EMS_LOCN_TRACER_CBCCONFIGSAT
//
// MessageText:
//
// EMS Location Service Tracer ( LocateCBC config: SatId  %1, DetMin %2, AmpMin %3, AmpMax %4, ItrMax %5, Thresh %6, CorMax %7, Drift %8, MaxNoise %9, MinPtsVisible %10 )
//
#define EMS_LOCN_TRACER_CBCCONFIGSAT     ((EMS_RESULT)0x0004A516L)

//
// MessageId: EMS_LOCN_TRACER_CBCCONFIGEE
//
// MessageText:
//
// EMS Location Service Tracer ( LocateCBC config: EEFact %1, EEAdj  %2, SwpThr %3, SwpPts %4 )
//
#define EMS_LOCN_TRACER_CBCCONFIGEE      ((EMS_RESULT)0x0004A517L)

//
// MessageId: EMS_LOCN_TRACER_406CONFIGSAT
//
// MessageText:
//
// EMS Location Service Tracer ( Locate406 config:  SatId  %1, ItrMax %2, Thresh %3, CorMax %4, Drift  %5, Altit  %6, MaxNoise %7, MinPtsVisible %8 )
//
#define EMS_LOCN_TRACER_406CONFIGSAT     ((EMS_RESULT)0x0004A518L)

//
// MessageId: EMS_LOCN_TRACER_406CONFIGEE
//
// MessageText:
//
// EMS Location Service Tracer ( Locate406 config:  EEFact %1, EEAdj  %2 )
//
#define EMS_LOCN_TRACER_406CONFIGEE      ((EMS_RESULT)0x0004A519L)

//
// MessageId: EMS_LOCN_PROCESSING_START_COUNT
//
// MessageText:
//
// EMS Location Service starting to process %1 (%2 CBC, %3 406, %4 Combine) records
//
#define EMS_LOCN_PROCESSING_START_COUNT  ((EMS_RESULT)0x0004A51AL)

//
// MessageId: EMS_LOCN_ACCURACY_CHECK_FAILURE
//
// MessageText:
//
// EMS Location Service reports that the calculated position for reference beacon %1 is %2 km different from expected (lat:%3 lon: %4).
//
#define EMS_LOCN_ACCURACY_CHECK_FAILURE  ((EMS_RESULT)0x8004A51BL)

//
// MessageId: EMS_TLE_SERV_NUM_CACHED
//
// MessageText:
//
// EMS TLE Server reports %1 orbit vectors currently stored in the cache.
//
#define EMS_TLE_SERV_NUM_CACHED          ((EMS_RESULT)0x0004A51CL)

//
// MessageId: EMS_TLE_SERV_CACHE_LIMIT_REACHED
//
// MessageText:
//
// EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached.  Oldest record in the cache will be overwritten.  
//
#define EMS_TLE_SERV_CACHE_LIMIT_REACHED ((EMS_RESULT)0x8004A51DL)

//
// MessageId: EMS_TLE_SERV_CACHE_INPUT_STOPPED
//
// MessageText:
//
// EMS TLE Server reports that the cache capacity (%1 orbit vectors) has been reached while loading from the database.  No more database records shall be added.
//
#define EMS_TLE_SERV_CACHE_INPUT_STOPPED ((EMS_RESULT)0x0004A51EL)

//
// MessageId: EMS_LOCN_UNINITIALIZED
//
// MessageText:
//
// EMS Location Service cannot process a request because it has not been initialized.
//
#define EMS_LOCN_UNINITIALIZED           ((EMS_RESULT)0x8004A51FL)

//
// MessageId: EMS_LOCN_NUMBER_INVALID_RECORDS
//
// MessageText:
//
// EMS Location Service reports %1 invalid input records.
//
#define EMS_LOCN_NUMBER_INVALID_RECORDS  ((EMS_RESULT)0x0004A520L)

//
// MessageId: EMS_LOCN_CMD_UNRECOGNIZED
//
// MessageText:
//
// EMS Location Service reports that an unrecognized command (%1) was received.  The command will be ignored.
//
#define EMS_LOCN_CMD_UNRECOGNIZED        ((EMS_RESULT)0x8004A521L)

//
// MessageId: EMS_LOCN_CMD_RESETDB
//
// MessageText:
//
// EMS Location Service reports that a command was received to clear the TOA/FOA measurement cache.
//
#define EMS_LOCN_CMD_RESETDB             ((EMS_RESULT)0x0004A522L)

//
// MessageId: EMS_LOCN_CMD_BURST_STORE_TIME
//
// MessageText:
//
// EMS Location Service reports that a command was received to set the TOA/FOA measurement store time to %1 minutes.
//
#define EMS_LOCN_CMD_BURST_STORE_TIME    ((EMS_RESULT)0x0004A523L)

//
// MessageId: EMS_LOCN_CMD_EXCEPTION
//
// MessageText:
//
// EMS Location Service reports that an exception report was received from the command message handler:  %1.
//
#define EMS_LOCN_CMD_EXCEPTION           ((EMS_RESULT)0x0004A524L)

//
// MessageId: EMS_LOCN_CMD_NOT_CONNECTED
//
// MessageText:
//
// EMS Location Service reports that it could not connect to the Message Queue for receipt of command messages.  Processing will continue, but commands will not be received.
//
#define EMS_LOCN_CMD_NOT_CONNECTED       ((EMS_RESULT)0x0004A525L)


#endif // INC_LOCNMSGS
#ifndef INC_AGMSGS
#define INC_AGMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_AG_BASE_CODE
//
// MessageText:
//
// EMS Alert Generation Error
//
#define EMS_AG_BASE_CODE                 ((EMS_RESULT)0x0004C400L)

//
// MessageId: EMS_AG_SERVICE_START
//
// MessageText:
//
// EMS Alert Generation Service Started
//
#define EMS_AG_SERVICE_START             ((EMS_RESULT)0x0004C401L)

//
// MessageId: EMS_AG_SERVICE_STOP
//
// MessageText:
//
// EMS Alert Generation Service Stopped
//
#define EMS_AG_SERVICE_STOP              ((EMS_RESULT)0x0004C402L)

//
// MessageId: EMS_AG_EXCEPTION
//
// MessageText:
//
// EMS Alert Generation Exception thrown: %1
//
#define EMS_AG_EXCEPTION                 ((EMS_RESULT)0x8004C403L)

//
// MessageId: EMS_AG_GATEWAY_INITERR
//
// MessageText:
//
// EMS Alert Generation: Error initializing the Gateway connection (%1)
//
#define EMS_AG_GATEWAY_INITERR           ((EMS_RESULT)0x8004C404L)

//
// MessageId: EMS_AG_SERVICE_START_ERR
//
// MessageText:
//
// Failed to start Alert Generator service (%1).
//
#define EMS_AG_SERVICE_START_ERR         ((EMS_RESULT)0x8004C405L)

//
// MessageId: EMS_AG_SERVICE_FAILED
//
// MessageText:
//
// Alert Generator failed due to unhandled exception (File: %1 Line: %2 hr = %3).
//
#define EMS_AG_SERVICE_FAILED            ((EMS_RESULT)0x8004C406L)


#endif // INC_AGMSGS
#ifndef INC_DMMSGS
#define INC_DMMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DM_BASE_CODE
//
// MessageText:
//
// EMS Data Manager Error
//
#define EMS_DM_BASE_CODE                 ((EMS_RESULT)0x8004C300L)

//
// MessageId: EMS_DM_SERVICE_START
//
// MessageText:
//
// EMS Data Manager Service Started
//
#define EMS_DM_SERVICE_START             ((EMS_RESULT)0x0004C301L)

//
// MessageId: EMS_DM_SERVICE_STOP
//
// MessageText:
//
// EMS Data Manager Service Stopped
//
#define EMS_DM_SERVICE_STOP              ((EMS_RESULT)0x0004C302L)

//
// MessageId: EMS_DM_EXCEPTION
//
// MessageText:
//
// EMS Data Manager - Exception thrown: %1
//
#define EMS_DM_EXCEPTION                 ((EMS_RESULT)0x8004C303L)

//
// MessageId: EMS_DM_FREESPACE_10
//
// MessageText:
//
// EMS Data Manager - Free space available is within 10%% of configured minimum.
//
#define EMS_DM_FREESPACE_10              ((EMS_RESULT)0x8004C304L)

//
// MessageId: EMS_DM_FREESPACE_5
//
// MessageText:
//
// EMS Data Manager - Free space available is within 5%% of configured minimum.
//
#define EMS_DM_FREESPACE_5               ((EMS_RESULT)0x8004C305L)

//
// MessageId: EMS_DM_FREESPACE_1
//
// MessageText:
//
// EMS Data Manager - Free space available is within 1%% of configured minimum.
//
#define EMS_DM_FREESPACE_1               ((EMS_RESULT)0x8004C306L)

//
// MessageId: EMS_DM_FREESPACE_0
//
// MessageText:
//
// EMS Data Manager - Free space available is below configured minimum.
//
#define EMS_DM_FREESPACE_0               ((EMS_RESULT)0x8004C307L)

//
// MessageId: EMS_DM_ARCHIVING
//
// MessageText:
//
// EMS Data Manager - Archiving Data Sources.
//
#define EMS_DM_ARCHIVING                 ((EMS_RESULT)0x0004C308L)

//
// MessageId: EMS_DM_ARCHIVE_SOURCE
//
// MessageText:
//
// EMS Data Manager - Archiving Data Source: %1.
//
#define EMS_DM_ARCHIVE_SOURCE            ((EMS_RESULT)0x0004C309L)

//
// MessageId: EMS_DM_ARCHIVE_SOURCE_FINISH
//
// MessageText:
//
// EMS Data Manager - Finished Archiving Data Source: %1.
//
#define EMS_DM_ARCHIVE_SOURCE_FINISH     ((EMS_RESULT)0x0004C30AL)

//
// MessageId: EMS_DM_FILEOPEN_SYSERROR
//
// MessageText:
//
// EMS Data Manager - Failed to open file %1 with system error %2.
//
#define EMS_DM_FILEOPEN_SYSERROR         ((EMS_RESULT)0x0004C30BL)

//
// MessageId: EMS_DM_RECTYPE_UNKNOWN
//
// MessageText:
//
// Unknown Database Table
//
#define EMS_DM_RECTYPE_UNKNOWN           ((EMS_RESULT)0x0004C30CL)

//
// MessageId: EMS_DM_RECTYPE_ANTENNA
//
// MessageText:
//
// Antenna Data
//
#define EMS_DM_RECTYPE_ANTENNA           ((EMS_RESULT)0x0004C30DL)

//
// MessageId: EMS_DM_RECTYPE_CALIB406
//
// MessageText:
//
// Calib 406 Data
//
#define EMS_DM_RECTYPE_CALIB406          ((EMS_RESULT)0x0004C30EL)

//
// MessageId: EMS_DM_RECTYPE_CALIBCBC
//
// MessageText:
//
// Calib CBC Data
//
#define EMS_DM_RECTYPE_CALIBCBC          ((EMS_RESULT)0x0004C30FL)

//
// MessageId: EMS_DM_RECTYPE_CALIBCBC_STATS
//
// MessageText:
//
// Calib CBC Stats
//
#define EMS_DM_RECTYPE_CALIBCBC_STATS    ((EMS_RESULT)0x0004C310L)

//
// MessageId: EMS_DM_RECTYPE_CBC
//
// MessageText:
//
// CBC Data
//
#define EMS_DM_RECTYPE_CBC               ((EMS_RESULT)0x0004C311L)

//
// MessageId: EMS_DM_RECTYPE_COLLECTOR
//
// MessageText:
//
// Collector Stats
//
#define EMS_DM_RECTYPE_COLLECTOR         ((EMS_RESULT)0x0004C312L)

//
// MessageId: EMS_DM_RECTYPE_COMB406
//
// MessageText:
//
// Combine 406 Data
//
#define EMS_DM_RECTYPE_COMB406           ((EMS_RESULT)0x0004C313L)

//
// MessageId: EMS_DM_RECTYPE_COMB406_STATS
//
// MessageText:
//
// Combine 406 Stats
//
#define EMS_DM_RECTYPE_COMB406_STATS     ((EMS_RESULT)0x0004C314L)

//
// MessageId: EMS_DM_RECTYPE_COMMS_STATS
//
// MessageText:
//
// Comms Stats
//
#define EMS_DM_RECTYPE_COMMS_STATS       ((EMS_RESULT)0x0004C315L)

//
// MessageId: EMS_DM_RECTYPE_CONFIG
//
// MessageText:
//
// Config Data
//
#define EMS_DM_RECTYPE_CONFIG            ((EMS_RESULT)0x0004C316L)

//
// MessageId: EMS_DM_RECTYPE_GEO_CALIB406_STATS
//
// MessageText:
//
// GEO Calib 406 Stats
//
#define EMS_DM_RECTYPE_GEO_CALIB406_STATS ((EMS_RESULT)0x0004C317L)

//
// MessageId: EMS_DM_RECTYPE_GEO_STATS
//
// MessageText:
//
// GEO Stats
//
#define EMS_DM_RECTYPE_GEO_STATS         ((EMS_RESULT)0x0004C318L)

//
// MessageId: EMS_DM_RECTYPE_LEO_CALIB406_STATS
//
// MessageText:
//
// LEO Calib 406 Stats
//
#define EMS_DM_RECTYPE_LEO_CALIB406_STATS ((EMS_RESULT)0x0004C319L)

//
// MessageId: EMS_DM_RECTYPE_LOCATE
//
// MessageText:
//
// Locate Data
//
#define EMS_DM_RECTYPE_LOCATE            ((EMS_RESULT)0x0004C31AL)

//
// MessageId: EMS_DM_RECTYPE_LOCATE_STATS
//
// MessageText:
//
// Locate Stats
//
#define EMS_DM_RECTYPE_LOCATE_STATS      ((EMS_RESULT)0x0004C31BL)

//
// MessageId: EMS_DM_RECTYPE_LOG
//
// MessageText:
//
// Log Data
//
#define EMS_DM_RECTYPE_LOG               ((EMS_RESULT)0x0004C31CL)

//
// MessageId: EMS_DM_RECTYPE_ORBIT
//
// MessageText:
//
// Orbit Data
//
#define EMS_DM_RECTYPE_ORBIT             ((EMS_RESULT)0x0004C31DL)

//
// MessageId: EMS_DM_RECTYPE_ORBIT_STATS
//
// MessageText:
//
// Orbit Stats
//
#define EMS_DM_RECTYPE_ORBIT_STATS       ((EMS_RESULT)0x0004C31EL)

//
// MessageId: EMS_DM_RECTYPE_PASS_STATS
//
// MessageText:
//
// Pass Stats
//
#define EMS_DM_RECTYPE_PASS_STATS        ((EMS_RESULT)0x0004C31FL)

//
// MessageId: EMS_DM_RECTYPE_RESIDUAL
//
// MessageText:
//
// Residual Data
//
#define EMS_DM_RECTYPE_RESIDUAL          ((EMS_RESULT)0x0004C320L)

//
// MessageId: EMS_DM_RECTYPE_SARP_CALIB
//
// MessageText:
//
// SARP Calib Data
//
#define EMS_DM_RECTYPE_SARP_CALIB        ((EMS_RESULT)0x0004C321L)

//
// MessageId: EMS_DM_RECTYPE_SARP_CALIB_STATS
//
// MessageText:
//
// SARP Calib Stats
//
#define EMS_DM_RECTYPE_SARP_CALIB_STATS  ((EMS_RESULT)0x0004C322L)

//
// MessageId: EMS_DM_RECTYPE_SARP
//
// MessageText:
//
// SARP Data
//
#define EMS_DM_RECTYPE_SARP              ((EMS_RESULT)0x0004C323L)

//
// MessageId: EMS_DM_RECTYPE_SARR_CALIB
//
// MessageText:
//
// SARR Calib Data
//
#define EMS_DM_RECTYPE_SARR_CALIB        ((EMS_RESULT)0x0004C324L)

//
// MessageId: EMS_DM_RECTYPE_SARR_CALIB_STATS
//
// MessageText:
//
// SARR Calib Stats
//
#define EMS_DM_RECTYPE_SARR_CALIB_STATS  ((EMS_RESULT)0x0004C325L)

//
// MessageId: EMS_DM_RECTYPE_SARR
//
// MessageText:
//
// SARR Data
//
#define EMS_DM_RECTYPE_SARR              ((EMS_RESULT)0x0004C326L)

//
// MessageId: EMS_DM_RECTYPE_SAT_TRACK
//
// MessageText:
//
// Pass Schedule Data
//
#define EMS_DM_RECTYPE_SAT_TRACK         ((EMS_RESULT)0x0004C327L)

//
// MessageId: EMS_DM_RECTYPE_SENSOR
//
// MessageText:
//
// Sensor Data
//
#define EMS_DM_RECTYPE_SENSOR            ((EMS_RESULT)0x0004C328L)

//
// MessageId: EMS_DM_RECTYPE_SPECTRUM
//
// MessageText:
//
// Spectrum Data
//
#define EMS_DM_RECTYPE_SPECTRUM          ((EMS_RESULT)0x0004C329L)

//
// MessageId: EMS_DM_RECTYPE_STAT_SUMMARY
//
// MessageText:
//
// Pass Summary Data
//
#define EMS_DM_RECTYPE_STAT_SUMMARY      ((EMS_RESULT)0x0004C32AL)

//
// MessageId: EMS_DM_RECTYPE_WIDEBAND_STATS
//
// MessageText:
//
// Wideband Stats
//
#define EMS_DM_RECTYPE_WIDEBAND_STATS    ((EMS_RESULT)0x0004C32BL)

//
// MessageId: EMS_DM_RECTYPE_AUDIO
//
// MessageText:
//
// Audio Data
//
#define EMS_DM_RECTYPE_AUDIO             ((EMS_RESULT)0x0004C32CL)

//
// MessageId: EMS_DM_RECTYPE_MANOEUVRE
//
// MessageText:
//
// Manoeuvre Data
//
#define EMS_DM_RECTYPE_MANOEUVRE         ((EMS_RESULT)0x0004C32DL)

//
// MessageId: EMS_DM_EXCEPTION_TRACE
//
// MessageText:
//
// EMS Data Manager - Exception thrown: File: %1 Line: %2 hr = %3
//
#define EMS_DM_EXCEPTION_TRACE           ((EMS_RESULT)0x8004C32EL)

//
// MessageId: EMS_DM_DISKSPACECHECKERR
//
// MessageText:
//
// Unable to check available disk space. Error code=%1.
//
#define EMS_DM_DISKSPACECHECKERR         ((EMS_RESULT)0x8004C32FL)

//
// MessageId: EMS_DM_RECTYPE_ABL_DATA
//
// MessageText:
//
// ABL Data
//
#define EMS_DM_RECTYPE_ABL_DATA          ((EMS_RESULT)0x0004C330L)

//
// MessageId: EMS_DM_RECTYPE_HEALTH_DETECTIONS
//
// MessageText:
//
// Health Detections
//
#define EMS_DM_RECTYPE_HEALTH_DETECTIONS ((EMS_RESULT)0x0004C331L)

//
// MessageId: EMS_DM_RECTYPE_HEALTH_STATUS
//
// MessageText:
//
// Health Status
//
#define EMS_DM_RECTYPE_HEALTH_STATUS     ((EMS_RESULT)0x0004C332L)


#endif // INC_DMMSGS
#ifndef INC_PKSRCRETRY_MSGS
#define INC_PKSRCRETRY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_PKSRC_BASE_CODE
//
// MessageText:
//
// EMS Retry Packet Source Error.
//
#define EMS_PKSRC_BASE_CODE              ((EMS_RESULT)0x00045A00L)

//
// MessageId: EMS_PKSRC_RETRY
//
// MessageText:
//
// EMS Retry Packet Source - Retrying Write to Pipeline %1.
//
#define EMS_PKSRC_RETRY                  ((EMS_RESULT)0x00045A01L)


#endif // INC_PKSRCRETRY_MSGS
/********************************************************************
*	Module:			EMSStatusCalibMonitorMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Calibration Monitor Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Dec01		CH		start 

********************************************************************/
#ifndef INC_EMSSECMSGS
#define INC_EMSSECMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_CALIBMONITOR_BASE_CODE
//
// MessageText:
//
// EMS Calibration Monitor Error
//
#define EMS_CALIBMONITOR_BASE_CODE       ((EMS_RESULT)0x0004B400L)

//
// MessageId: EMS_MONITOR_PIPE_INIT_ERR
//
// MessageText:
//
// Pipeline Monitor object not initialized
//
#define EMS_MONITOR_PIPE_INIT_ERR        ((EMS_RESULT)0x8004B401L)

//
// MessageId: EMS_MONITOR_CONFIG_INIT_ERR
//
// MessageText:
//
// Monitor Configuration not initialized
//
#define EMS_MONITOR_CONFIG_INIT_ERR      ((EMS_RESULT)0x8004B402L)

//
// MessageId: EMS_MONITOR_GATEWAY_INIT_ERR
//
// MessageText:
//
// Monitor Gateway not initialized
//
#define EMS_MONITOR_GATEWAY_INIT_ERR     ((EMS_RESULT)0x8004B403L)

//
// MessageId: EMS_MONITOR_SEC_INIT_ERR
//
// MessageText:
//
// Monitor Security not initialized
//
#define EMS_MONITOR_SEC_INIT_ERR         ((EMS_RESULT)0x8004B404L)

//
// MessageId: EMS_CALIBMONITOR_INIT_ERR
//
// MessageText:
//
// EMS Calibration Monitor initialization error ( %1 )
//
#define EMS_CALIBMONITOR_INIT_ERR        ((EMS_RESULT)0x8004B405L)

//
// MessageId: EMS_CALIBMONITOR_INIT_OK
//
// MessageText:
//
// EMS Calibration Monitor service started %1
//
#define EMS_CALIBMONITOR_INIT_OK         ((EMS_RESULT)0x0004B406L)

//
// MessageId: EMS_CALIBMONITOR_PROCESSTLE_ERR
//
// MessageText:
//
// EMS Calibration Monitor: an error has occurred while processing TLEs ( %1 )
//
#define EMS_CALIBMONITOR_PROCESSTLE_ERR  ((EMS_RESULT)0x0004B407L)

//
// MessageId: EMS_CALIBMONITOR_SENDOVECTORS_ERR
//
// MessageText:
//
// EMS Calibration Monitor: an error occurred while sending orbit vectors ( %1 )
//
#define EMS_CALIBMONITOR_SENDOVECTORS_ERR ((EMS_RESULT)0x0004B408L)

//
// MessageId: EMS_CALIBMONITOR_SENDTLES_ERR
//
// MessageText:
//
// EMS Calibration Monitor: an error occurred while sending TLEs ( %1 )
//
#define EMS_CALIBMONITOR_SENDTLES_ERR    ((EMS_RESULT)0x0004B409L)

//
// MessageId: EMS_CALIBMONITOR_SENDSARR_ERR
//
// MessageText:
//
// EMS Calibration Monitor: an error occurred while sending SARR data ( %1 )
//
#define EMS_CALIBMONITOR_SENDSARR_ERR    ((EMS_RESULT)0x0004B40AL)

//
// MessageId: EMS_CALIBMONITOR_SENDSARP_ERR
//
// MessageText:
//
// EMS Calibration Monitor: an error occurred while sending SARP data ( %1 )
//
#define EMS_CALIBMONITOR_SENDSARP_ERR    ((EMS_RESULT)0x0004B40BL)

//
// MessageId: EMS_STATUSMONITOR_INIT_ERR
//
// MessageText:
//
// EMS Status Monitor initialization error ( %1 )
//
#define EMS_STATUSMONITOR_INIT_ERR       ((EMS_RESULT)0x8004B40CL)

//
// MessageId: EMS_STATUSMONITOR_INIT_OK
//
// MessageText:
//
// EMS Status Monitor service started %1
//
#define EMS_STATUSMONITOR_INIT_OK        ((EMS_RESULT)0x0004B40DL)

//
// MessageId: EMS_STATUSMONITOR_SENDSTATUS_ERR
//
// MessageText:
//
// EMS Status Monitor: an error occurred while sending Statuses ( %1 )
//
#define EMS_STATUSMONITOR_SENDSTATUS_ERR ((EMS_RESULT)0x0004B40EL)

//
// MessageId: EMS_STATUSMONITOR_SENDSTARTUP_ERR
//
// MessageText:
//
// EMS Status Monitor: an error occurred while sending Startup data ( %1 )
//
#define EMS_STATUSMONITOR_SENDSTARTUP_ERR ((EMS_RESULT)0x0004B40FL)

//
// MessageId: EMS_STATUSMONITOR_SENDWARNING_ERR
//
// MessageText:
//
// EMS Status Monitor: an error occurred while sending warning ( %1 )
//
#define EMS_STATUSMONITOR_SENDWARNING_ERR ((EMS_RESULT)0x0004B410L)

//
// MessageId: EMS_STATUSMONITOR_SENDALARM_ERR
//
// MessageText:
//
// EMS Status Monitor: an error occurred while sending Alarm ( %1 )
//
#define EMS_STATUSMONITOR_SENDALARM_ERR  ((EMS_RESULT)0x0004B411L)


#endif // INC_EMSSECMSGS
/********************************************************************
*	Module:			ActvMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Geo Active Beacon Service
*				Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_ACTVMSGS
#define INC_ACTVMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ACTVBCN_BASE_CODE
//
// MessageText:
//
// EMS ActiveBeacon 
//
#define EMS_ACTVBCN_BASE_CODE            ((EMS_RESULT)0x0004AA00L)

//
// MessageId: EMS_ACTVBCN_SERVICE_START
//
// MessageText:
//
// EMS ActiveBeacon Service Started
//
#define EMS_ACTVBCN_SERVICE_START        ((EMS_RESULT)0x0004AA01L)

//
// MessageId: EMS_ACTVBCN_SERVICE_STOP
//
// MessageText:
//
// EMS ActiveBeacon Service Stopped
//
#define EMS_ACTVBCN_SERVICE_STOP         ((EMS_RESULT)0x0004AA02L)

//
// MessageId: EMS_ACTVBCN_SERVICE_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service did not start due to error %1
//
#define EMS_ACTVBCN_SERVICE_FAILED       ((EMS_RESULT)0x8004AA03L)

//
// MessageId: EMS_ACTVBCN_PROCESSING_START
//
// MessageText:
//
// EMS ActiveBeacon Service starting to process %1 records
//
#define EMS_ACTVBCN_PROCESSING_START     ((EMS_RESULT)0x0004AA04L)

//
// MessageId: EMS_ACTVBCN_PROCESSING_STOP
//
// MessageText:
//
// EMS ActiveBeacon Service finished processing. %1 location records output.
//
#define EMS_ACTVBCN_PROCESSING_STOP      ((EMS_RESULT)0x0004AA05L)

//
// MessageId: EMS_ACTVBCN_TRACER
//
// MessageText:
//
// EMS ActiveBeacon Service Tracer ( %1 )
//
#define EMS_ACTVBCN_TRACER               ((EMS_RESULT)0x0004AA06L)

//
// MessageId: EMS_ACTVBCN_RECV_COMMAND
//
// MessageText:
//
// EMS ActiveBeacon received command( %1 ).
//
#define EMS_ACTVBCN_RECV_COMMAND         ((EMS_RESULT)0x0004AA07L)

//
// MessageId: EMS_ACTVBCN_PROC_ERROR
//
// MessageText:
//
// EMS ActiveBeacon returns error %1 from _DetermineLocations.
//
#define EMS_ACTVBCN_PROC_ERROR           ((EMS_RESULT)0x8004AA08L)

//
// MessageId: EMS_ACTVBCN_DETERMINE_LOCATION_ERROR
//
// MessageText:
//
// EMS ActiveBeacon reports result %1 from _DetermineLocation.
//
#define EMS_ACTVBCN_DETERMINE_LOCATION_ERROR ((EMS_RESULT)0x8004AA09L)

//
// MessageId: EMS_ACTVBCN_BAD_DATA_DIR
//
// MessageText:
//
// EMS ActiveBeacon reports error %1 trying to access data directory.
//
#define EMS_ACTVBCN_BAD_DATA_DIR         ((EMS_RESULT)0x8004AA0AL)

//
// MessageId: EMS_ACTVBCN_BAD_BCH
//
// MessageText:
//
// EMS ActiveBeacon reports BCH failure for Beacon %1.
//
#define EMS_ACTVBCN_BAD_BCH              ((EMS_RESULT)0x8004AA0BL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIG
//
// MessageText:
//
// EMS ActiveBeacon Service Tracer ( cfg: %1=%2 )
//
#define EMS_ACTVBCN_TRACE_CONFIG         ((EMS_RESULT)0x0004AA0CL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIGYES
//
// MessageText:
//
// EMS ActiveBeacon Service Tracer ( cfg: %1=yes )
//
#define EMS_ACTVBCN_TRACE_CONFIGYES      ((EMS_RESULT)0x0004AA0DL)

//
// MessageId: EMS_ACTVBCN_TRACE_CONFIGNO
//
// MessageText:
//
// EMS ActiveBeacon Service Tracer ( cfg: %1=no )
//
#define EMS_ACTVBCN_TRACE_CONFIGNO       ((EMS_RESULT)0x0004AA0EL)

//
// MessageId: EMS_ACTVBCN_IGNORED_INVERTEDFS
//
// MessageText:
//
// EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (inverted frame sync)
//
#define EMS_ACTVBCN_IGNORED_INVERTEDFS   ((EMS_RESULT)0x0004AA0FL)

//
// MessageId: EMS_ACTVBCN_IGNORED_INVALIDFS
//
// MessageText:
//
// EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not included in set for processing (invalid frame sync)
//
#define EMS_ACTVBCN_IGNORED_INVALIDFS    ((EMS_RESULT)0x0004AA10L)

//
// MessageId: EMS_ACTVBCN_IGNORED_SERVICENOTPROCESSING
//
// MessageText:
//
// EMS ActiveBeacon Service:  Calib406 record for beacon (%1) not processed.  The Active Beacon Service is in the %2 state and can not accept new data.
//
#define EMS_ACTVBCN_IGNORED_SERVICENOTPROCESSING ((EMS_RESULT)0x0004AA11L)

//
// MessageId: EMS_ACTVBCN_INIT_MAXBEACONS
//
// MessageText:
//
// EMS ActiveBeacon Service: Initialized with MaxBeacons=%1
//
#define EMS_ACTVBCN_INIT_MAXBEACONS      ((EMS_RESULT)0x0004AA12L)

//
// MessageId: EMS_ACTVBCN_INIT_AGEOUT
//
// MessageText:
//
// EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4)
//
#define EMS_ACTVBCN_INIT_AGEOUT          ((EMS_RESULT)0x0004AA13L)

//
// MessageId: EMS_ACTVBCN_BEACON_AGEOUT
//
// MessageText:
//
// EMS ActiveBeacon Service: Data aged out for Beacon (%1). Age=%2 minutes, #Records=%3
//
#define EMS_ACTVBCN_BEACON_AGEOUT        ((EMS_RESULT)0x0004AA14L)

//
// MessageId: EMS_ACTVBCN_BEACON_REPLACED_NOALERT
//
// MessageText:
//
// EMS ActiveBeacon Service: Beacon %1 (@%2) was replaced prior to Alert. #Active Beacons=%3
//
#define EMS_ACTVBCN_BEACON_REPLACED_NOALERT ((EMS_RESULT)0x8004AA15L)

//
// MessageId: EMS_ACTVBCN_BEACON_REPLACED
//
// MessageText:
//
// EMS ActiveBeacon Service:  Beacon %1 (@%2) was replaced by Beacon %4. #Active Beacons=%3
//
#define EMS_ACTVBCN_BEACON_REPLACED      ((EMS_RESULT)0x0004AA16L)

//
// MessageId: EMS_ACTVBCN_BEACON_ADD_FAILED_BIN
//
// MessageText:
//
// EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1 (@%2). #Active Beacons=%3, Error=%4
//
#define EMS_ACTVBCN_BEACON_ADD_FAILED_BIN ((EMS_RESULT)0x8004AA17L)

//
// MessageId: EMS_ACTVBCN_BEACON_ADD_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service: Unable to add calib406 record for Beacon %1. #Active Beacons=%2
//
#define EMS_ACTVBCN_BEACON_ADD_FAILED    ((EMS_RESULT)0x8004AA18L)

//
// MessageId: EMS_ACTVBCN_BLIST_AGEOUT
//
// MessageText:
//
// EMS ActiveBeacon Service: Beacon List age out of Beacon %1. Type=%2, Age=%3 minutes, #Active Beacons=%4
//
#define EMS_ACTVBCN_BLIST_AGEOUT         ((EMS_RESULT)0x0004AA19L)

//
// MessageId: EMS_ACTVBCN_ABL_INIT_FAIL
//
// MessageText:
//
// EMS ActiveBeacon Service: Failed to initialize ABL Object (hr = %1)
//
#define EMS_ACTVBCN_ABL_INIT_FAIL        ((EMS_RESULT)0x8004AA1AL)

//
// MessageId: EMS_ACTVBCN_LOAD_CONFIG_FAIL
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during loading the ABS configurations (hr = %1)
//
#define EMS_ACTVBCN_LOAD_CONFIG_FAIL     ((EMS_RESULT)0x8004AA1BL)

//
// MessageId: EMS_ACTVBCN_FAILED_TO_WRITE_TO_PIPELINE
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during writing a location record to the pipeline (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_FAILED_TO_WRITE_TO_PIPELINE ((EMS_RESULT)0x8004AA1CL)

//
// MessageId: EMS_ACTVBCN_FAILED_TO_SENDNOW_LOCATE
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during sending a location record via gateway (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_FAILED_TO_SENDNOW_LOCATE ((EMS_RESULT)0x8004AA1DL)

//
// MessageId: EMS_ACTVBCN_ABL_GETLOCATIONS_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during getting location records from the ABL (hr = %1)
//
#define EMS_ACTVBCN_ABL_GETLOCATIONS_FAILED ((EMS_RESULT)0x8004AA1EL)

//
// MessageId: EMS_ACTVBCN_ABL_GETBCNLOCATION_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during getting a beacons location record from the ABL (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_ABL_GETBCNLOCATION_FAILED ((EMS_RESULT)0x8004AA1FL)

//
// MessageId: EMS_ACTVBCN_ABL_PUTBCNDATA_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service: An error occurred during adding a beacons location record to the ABL (beacon id = %1, hr = %2)
//
#define EMS_ACTVBCN_ABL_PUTBCNDATA_FAILED ((EMS_RESULT)0x8004AA20L)

//
// MessageId: EMS_ACTVBCN_STOPPED_IGNORING_INPUT_RECS
//
// MessageText:
//
// EMS ActiveBeacon Service: Calib406 record for beacon (%1) has not been processed. The Active Beacon Service is in the "Idle" state and cannot accept new data.
//
#define EMS_ACTVBCN_STOPPED_IGNORING_INPUT_RECS ((EMS_RESULT)0x8004AA21L)

//
// MessageId: EMS_ACTVBCN_NO_SUPPORT_FOR_CONFIG_ITEM
//
// MessageText:
//
// EMS ActiveBeacon Service: Wrong ABS configuration item - "%1" is configured to '%2'. This value is not supported in this release. The supported value will be used.
//
#define EMS_ACTVBCN_NO_SUPPORT_FOR_CONFIG_ITEM ((EMS_RESULT)0x8004AA22L)

//
// MessageId: EMS_ACTVBCN_FAILED_TOGET_CONFIG_ITEM
//
// MessageText:
//
// EMS ActiveBeacon Service: Failed to get configuration item - %1 (of '%2' group, hr = %3). Check the configuration files.
//
#define EMS_ACTVBCN_FAILED_TOGET_CONFIG_ITEM ((EMS_RESULT)0x8004AA23L)

//
// MessageId: EMS_ACTVBCN_CONFIG_ITEM_VALUE
//
// MessageText:
//
// EMS ActiveBeacon Service: The ABS configuration item - "%1" is configured to '%2'.
//
#define EMS_ACTVBCN_CONFIG_ITEM_VALUE    ((EMS_RESULT)0x0004AA24L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_WARN
//
// MessageText:
//
// EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_WARN          ((EMS_RESULT)0x8004AA25L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_ALARM
//
// MessageText:
//
// EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is above the expected maximum value (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_ALARM         ((EMS_RESULT)0x8004AA26L)

//
// MessageId: EMS_ACTVBCN_ABL_LA_OK
//
// MessageText:
//
// EMS ActiveBeacon Service: The location error of reference beacon (id=%1) is back to normal (actual=%2, expected <=%3).
//
#define EMS_ACTVBCN_ABL_LA_OK            ((EMS_RESULT)0x0004AA27L)

//
// MessageId: EMS_ACTVBCN_ABL_MAX_CAP
//
// MessageText:
//
// EMS ActiveBeacon Service: Reached the maximum configured number of raw input records. (Max=%1); this might limit the list of active beacons data.
//
#define EMS_ACTVBCN_ABL_MAX_CAP          ((EMS_RESULT)0x8004AA28L)

//
// MessageId: EMS_ACTVBCN_INIT_AGEOUT_UPDFREQ
//
// MessageText:
//
// EMS ActiveBeacon Service: Initialized with Ageout (minutes)=%1 and Update Frequency (minutes) = Min(%2), Max(%3), Valid(%4), QMS(%5)
//
#define EMS_ACTVBCN_INIT_AGEOUT_UPDFREQ  ((EMS_RESULT)0x0004AA29L)

//
// MessageId: EMS_ACTVBCN_OUTPUT_DETECTION_FAILED
//
// MessageText:
//
// EMS ActiveBeacon Service: Failed outputting beacon detection to MTL.  Error code = %1.
//
#define EMS_ACTVBCN_OUTPUT_DETECTION_FAILED ((EMS_RESULT)0x8004AA2AL)

//
// MessageId: EMS_ACTVBCN_NO_MTL_CLIENT
//
// MessageText:
//
// EMS ActiveBeacon Service: Failed outputting beacon detection to MTL.  No reference available to MTL Client.
//
#define EMS_ACTVBCN_NO_MTL_CLIENT        ((EMS_RESULT)0x8004AA2BL)


#endif // INC_ACTVMSGS
/********************************************************************
*	Module:			GeoCalibMsg.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Calib406 Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_GEOCALIBMSG
#define INC_GEOCALIBMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_GEOCALIB_BASE_CODE
//
// MessageText:
//
// EMS GeoCalib406 Error
//
#define EMS_GEOCALIB_BASE_CODE           ((EMS_RESULT)0x8004A900L)

//
// MessageId: EMS_GEOCALIB_SERVICE_START
//
// MessageText:
//
// EMS GeoCalib406 Service Started
//
#define EMS_GEOCALIB_SERVICE_START       ((EMS_RESULT)0x0004A901L)

//
// MessageId: EMS_GEOCALIB_SERVICE_FAILED
//
// MessageText:
//
// EMS GeoCalib406 Service did not start due to error %1
//
#define EMS_GEOCALIB_SERVICE_FAILED      ((EMS_RESULT)0x8004A902L)

//
// MessageId: EMS_GEOCALIB_SERVICE_STOP
//
// MessageText:
//
// EMS GeoCalib406 Service Stopped
//
#define EMS_GEOCALIB_SERVICE_STOP        ((EMS_RESULT)0x0004A903L)

//
// MessageId: EMS_GEOCALIB_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reports error %1.
//
#define EMS_GEOCALIB_ERROR               ((EMS_RESULT)0x8004A904L)

//
// MessageId: EMS_GEOCALIB_END_PASS
//
// MessageText:
//
// EMS GeoCalib406 reports end of pass for satellite %1
//
#define EMS_GEOCALIB_END_PASS            ((EMS_RESULT)0x0004A905L)

//
// MessageId: EMS_GEOCALIB_START_PASS
//
// MessageText:
//
// EMS GeoCalib406 reports initialized pass for satellite %1
//
#define EMS_GEOCALIB_START_PASS          ((EMS_RESULT)0x0004A906L)

//
// MessageId: EMS_GEOCALIB_TRACER
//
// MessageText:
//
// EMS GeoCalib406 Tracer ( %1 )
//
#define EMS_GEOCALIB_TRACER              ((EMS_RESULT)0x0004A907L)

//
// MessageId: EMS_GEOCALIB_HISTORY_RECS
//
// MessageText:
//
// EMS GeoCalib406 read %1 history records.
//
#define EMS_GEOCALIB_HISTORY_RECS        ((EMS_RESULT)0x0004A908L)

//
// MessageId: EMS_GEOCALIB_BUFFER_ADD
//
// MessageText:
//
// EMS GeoCalib406 reports an error adding record %1 to the buffer.
//
#define EMS_GEOCALIB_BUFFER_ADD          ((EMS_RESULT)0x8004A909L)

//
// MessageId: EMS_GEOCALIB_SARR_OFFSETS
//
// MessageText:
//
// EMS GeoCalib406 has calculated new SARR Offsets ( SatID = %1, Freq=%2 ).
//
#define EMS_GEOCALIB_SARR_OFFSETS        ((EMS_RESULT)0x0004A90AL)

//
// MessageId: EMS_GEOCALIB_ORBIT_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reported error %1 while trying to access IEMSOrbit.
//
#define EMS_GEOCALIB_ORBIT_ERROR         ((EMS_RESULT)0x8004A90BL)

//
// MessageId: EMS_GEOCALIB_SAT_INFO_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reported error %1 while trying to access IEMSSatInfo.
//
#define EMS_GEOCALIB_SAT_INFO_ERROR      ((EMS_RESULT)0x8004A90CL)

//
// MessageId: EMS_GEOCALIB_LUT_INFO_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reported error %1 while trying to access IEMSLutInfo.
//
#define EMS_GEOCALIB_LUT_INFO_ERROR      ((EMS_RESULT)0x8004A90DL)

//
// MessageId: EMS_GEOCALIB_SITE_INFO_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reported error %1 while trying to access IEMSLeo600SiteInfo
//
#define EMS_GEOCALIB_SITE_INFO_ERROR     ((EMS_RESULT)0x8004A90EL)

//
// MessageId: EMS_GEOCALIB_REF_BEACON_ERROR
//
// MessageText:
//
// EMS GeoCalib406 reported error %1 while trying to access IEMSRefBeacon.
//
#define EMS_GEOCALIB_REF_BEACON_ERROR    ((EMS_RESULT)0x8004A90FL)

//
// MessageId: EMS_GEOCALIB_TRACE_CONFIG
//
// MessageText:
//
// EMS GeoCalib406 Tracer ( cfg: %1=%2 )
//
#define EMS_GEOCALIB_TRACE_CONFIG        ((EMS_RESULT)0x0004A910L)

//
// MessageId: EMS_GEOCALIB_TRACE_CONFIGYES
//
// MessageText:
//
// EMS GeoCalib406 Tracer ( cfg: %1=yes )
//
#define EMS_GEOCALIB_TRACE_CONFIGYES     ((EMS_RESULT)0x0004A911L)

//
// MessageId: EMS_GEOCALIB_TRACE_CONFIGNO
//
// MessageText:
//
// EMS GeoCalib406 Tracer ( cfg: %1=no )
//
#define EMS_GEOCALIB_TRACE_CONFIGNO      ((EMS_RESULT)0x0004A912L)


#endif // INC_GEOCALIBMSG
/********************************************************************
*	Module:			SITMessageCore.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS SIT Message Core Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_SITMESSAGECOREMSG
#define INC_SITMESSAGECOREMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SITMSGCORE_BASE_CODE
//
// MessageText:
//
// EMS SIT Message Core Error
//
#define EMS_SITMSGCORE_BASE_CODE         ((EMS_RESULT)0x0004C600L)

//
// MessageId: EMS_SITMSGCORE_NOATTRIBUTE
//
// MessageText:
//
// EMS SIT Message Core reports that the attribute named <%1> could not be found in a SIT or MF definition.
//
#define EMS_SITMSGCORE_NOATTRIBUTE       ((EMS_RESULT)0x8004C601L)

//
// MessageId: EMS_SITMSGCORE_LINE_NOMFID
//
// MessageText:
//
// EMS SIT Message Core reports that an MF defined as part of a SIT Message Line has no <%1> attribute defined.
//
#define EMS_SITMSGCORE_LINE_NOMFID       ((EMS_RESULT)0x8004C602L)

//
// MessageId: EMS_SITMSGCORE_MFDEF_NOTFOUND
//
// MessageText:
//
// EMS SIT Message Core reports that a definition for MF <%1> could not be found.
//
#define EMS_SITMSGCORE_MFDEF_NOTFOUND    ((EMS_RESULT)0x8004C603L)

//
// MessageId: EMS_SITMSGCORE_NO_CONFIG_MANAGER
//
// MessageText:
//
// EMS SIT Message Core reports error <%1> attempting to connect to the CM subsystem.
//
#define EMS_SITMSGCORE_NO_CONFIG_MANAGER ((EMS_RESULT)0x8004C604L)

//
// MessageId: EMS_SITMSGCORE_NO_MFDEFS_URL
//
// MessageText:
//
// EMS SIT Message Core reports error <%1> attempting to retrieve the MF Definitions URL from the CM subsystem.
//
#define EMS_SITMSGCORE_NO_MFDEFS_URL     ((EMS_RESULT)0x8004C605L)

//
// MessageId: EMS_SITMSGCORE_NO_SITDEFS_URL_STRING
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to retrieve the SIT Definitions URL from the CM subsystem.
//
#define EMS_SITMSGCORE_NO_SITDEFS_URL_STRING ((EMS_RESULT)0x8004C606L)

//
// MessageId: EMS_SITMSGCORE_NO_LOAD_SITDEFS
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to load and parse the SIT Definitions from URL <%1>.
//
#define EMS_SITMSGCORE_NO_LOAD_SITDEFS   ((EMS_RESULT)0x8004C607L)

//
// MessageId: EMS_SITMSGCORE_NO_SITS_NODE
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to obtain the SITs tree from the SIT Definitions.
//
#define EMS_SITMSGCORE_NO_SITS_NODE      ((EMS_RESULT)0x8004C608L)

//
// MessageId: EMS_SITMSGCORE_NO_SITIDS
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to retrieve any SIT Identifiers from the SIT Definitions.
//
#define EMS_SITMSGCORE_NO_SITIDS         ((EMS_RESULT)0x8004C609L)

//
// MessageId: EMS_SITMSGCORE_NO_SIT_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to find the specification for SIT Type <%1> in the SIT Definitions.
//
#define EMS_SITMSGCORE_NO_SIT_DEFINED    ((EMS_RESULT)0x8004C60AL)

//
// MessageId: EMS_SITMSGCORE_NO_MFS_NODE
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to obtain the MFs tree from the Message Field Definitions.
//
#define EMS_SITMSGCORE_NO_MFS_NODE       ((EMS_RESULT)0x8004C60BL)

//
// MessageId: EMS_SITMSGCORE_NO_MFDEFS_URL_STRING
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to retrieve the Message Field Definitions URL from the CM subsystem.
//
#define EMS_SITMSGCORE_NO_MFDEFS_URL_STRING ((EMS_RESULT)0x8004C60CL)

//
// MessageId: EMS_SITMSGCORE_NO_LOAD_MFDEFS
//
// MessageText:
//
// EMS SIT Message Core reports that it was unable to load and parse the Message Field Definitions from URL <%1>.
//
#define EMS_SITMSGCORE_NO_LOAD_MFDEFS    ((EMS_RESULT)0x8004C60DL)

//
// MessageId: EMS_SITMSGCORE_NO_SUB_FLD_DEFINITION
//
// MessageText:
//
// EMS SIT Message Core reports that a SIT Message sub-field does not have an associated definition.
//
#define EMS_SITMSGCORE_NO_SUB_FLD_DEFINITION ((EMS_RESULT)0x8004C60EL)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_LENGTH
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field max length is <%1>, but actual length is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_LENGTH ((EMS_RESULT)0x8004C60FL)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MIN
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field minimum allowable is <%1>, but actual value is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MIN ((EMS_RESULT)0x8004C610L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MAX
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field maximum allowable is <%1>, but actual value is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_INT_MAX ((EMS_RESULT)0x8004C611L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MIN
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field minimum allowable is <%1>, but actual value is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MIN ((EMS_RESULT)0x8004C612L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MAX
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field maximum allowable is <%1>, but actual value is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_DECIMAL_MAX ((EMS_RESULT)0x8004C613L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_MULTILINE
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field illegally contains multiple lines.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_MULTILINE ((EMS_RESULT)0x8004C614L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SUBMF_INVALID_VALUE
//
// MessageText:
//
// EMS SIT Message Core reports a SIT Message validation error:  sub-field value <%1> does not match an entry in valid list.
//
#define EMS_SITMSGCORE_VALIDATION_SUBMF_INVALID_VALUE ((EMS_RESULT)0x8004C615L)

//
// MessageId: EMS_SITMSGCORE_SERIALIZATION_MF_NO_SEPS
//
// MessageText:
//
// EMS SIT Message Core reports that it could not retrieve the default Message Field Separator character/string.
//
#define EMS_SITMSGCORE_SERIALIZATION_MF_NO_SEPS ((EMS_RESULT)0x8004C616L)

//
// MessageId: EMS_SITMSGCORE_SERIALIZATION_MF_NO_SUBMFS
//
// MessageText:
//
// EMS SIT Message Core reports that, while serializing, it encountered a Message Field that does not have any sub-fields.
//
#define EMS_SITMSGCORE_SERIALIZATION_MF_NO_SUBMFS ((EMS_RESULT)0x8004C617L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message Field object was not initialized with a definition prior to deserializing.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_NO_DEFN ((EMS_RESULT)0x8004C618L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SUBFIELDS_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports that a Message Field object was encountered during deserialization for which no sub-fields are defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SUBFIELDS_DEFINED ((EMS_RESULT)0x8004C619L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SEPS_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports that it could not retrieve any Message Field separators while attempting to deserialize an MF.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_NO_SEPS_DEFINED ((EMS_RESULT)0x8004C61AL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_PARSE_NOSEP
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing Message Field <%1> because no MF separator was found.  MF contents:  <%2>.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_PARSE_NOSEP ((EMS_RESULT)0x8004C61BL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_LENGTH_DEFINED_ZERO
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing Message Field <%1> because sub-field <%2> has a defined length of 0 or less and no terminating sequence defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_LENGTH_DEFINED_ZERO ((EMS_RESULT)0x8004C61CL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TERM_SEQUENCE
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing Message Field <%1> because sub-field <%2> does not contain the expected terminating sequence of <%3>.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TERM_SEQUENCE ((EMS_RESULT)0x8004C61DL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TYPE
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing Message Field <%1> because a sub-field type <%2> is unsupported.
//
#define EMS_SITMSGCORE_DESERIALIZATION_MF_NO_TYPE ((EMS_RESULT)0x8004C61EL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_EOLS
//
// MessageText:
//
// EMS SIT Message Core reports that it could not retrieve any Message line terminators while attempting to deserialize a Line.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_EOLS ((EMS_RESULT)0x8004C61FL)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_LENGTH
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a Message line.  The line length is zero.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_LENGTH ((EMS_RESULT)0x8004C620L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFS_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports that a Line object was encountered during deserialization for which no Message Fields are defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFS_DEFINED ((EMS_RESULT)0x8004C621L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message Line object was not initialized with a definition prior to deserializing.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_DEFN ((EMS_RESULT)0x8004C622L)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_LINE_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message Line object was not initialized with a definition prior to validation.
//
#define EMS_SITMSGCORE_VALIDATION_LINE_NO_DEFN ((EMS_RESULT)0x8004C623L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFSEPS_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a Message Line.  No Message Field separators are defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_NO_MFSEPS_DEFN ((EMS_RESULT)0x8004C624L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_LINE_MF_START_NOT_FOUND
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a Message Line.  The start of a Message Field could not be found.
//
#define EMS_SITMSGCORE_DESERIALIZATION_LINE_MF_START_NOT_FOUND ((EMS_RESULT)0x8004C625L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINES_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports that a SIT object was encountered during deserialization for which no Lines are defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINES_DEFINED ((EMS_RESULT)0x8004C626L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_SUBFIELD_TERMINATORS
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a SIT message.  The termination string for a multi-line MF could not be found in line <%1>.
//
#define EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_SUBFIELD_TERMINATORS ((EMS_RESULT)0x8004C627L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINETERMS_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a SIT Message.  No message line terminators are defined.
//
#define EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_LINETERMS_DEFN ((EMS_RESULT)0x8004C628L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_EOL_FOUND
//
// MessageText:
//
// EMS SIT Message Core reports an error parsing a SIT Message.  The end of line <%1> could not be found.
//
#define EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_EOL_FOUND ((EMS_RESULT)0x8004C629L)

//
// MessageId: EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message object was not initialized with a definition prior to deserializing.
//
#define EMS_SITMSGCORE_DESERIALIZATION_SIT_NO_DEFN ((EMS_RESULT)0x8004C62AL)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SIT_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message object was not initialized with a definition prior to validation.
//
#define EMS_SITMSGCORE_VALIDATION_SIT_NO_DEFN ((EMS_RESULT)0x8004C62BL)

//
// MessageId: EMS_SITMSGCORE_TYPE_CHECK_NO_TYPE_POSITIONS
//
// MessageText:
//
// EMS SIT Message Core reports that a SIT cannot be deserialized because its type cannot be determined.  Its type cannot be determined because no SIT type positions are configured.
//
#define EMS_SITMSGCORE_TYPE_CHECK_NO_TYPE_POSITIONS ((EMS_RESULT)0x8004C62CL)

//
// MessageId: EMS_SITMSGCORE_TYPE_NOT_DETERMINED
//
// MessageText:
//
// EMS SIT Message Core reports that a SIT cannot be deserialized because its type cannot be determined.  It may not contain a SIT type specifier or it may not be at the expected offset into the message.
//
#define EMS_SITMSGCORE_TYPE_NOT_DETERMINED ((EMS_RESULT)0x8004C62DL)

//
// MessageId: EMS_SITMSGCORE_MF_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that it could not find a definition for Message Field <%1>.
//
#define EMS_SITMSGCORE_MF_NO_DEFN        ((EMS_RESULT)0x8004C62EL)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_LINE_MAX_LEN_EXCEEDED
//
// MessageText:
//
// EMS SIT Message Core reports that a Message Line fails validation because it exceeds the maximum allowable length.  Length is <%1> and maximum is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_LINE_MAX_LEN_EXCEEDED ((EMS_RESULT)0x8004C62FL)

//
// MessageId: EMS_SITMSGCORE_VALIDATION_SIT_MAX_CHARACTERS_EXCEEDED
//
// MessageText:
//
// EMS SIT Message Core reports that a SIT Message fails validation because it exceeds the maximum allowable number of characters.  Number of characters is <%1> and maximum is <%2>.
//
#define EMS_SITMSGCORE_VALIDATION_SIT_MAX_CHARACTERS_EXCEEDED ((EMS_RESULT)0x8004C630L)

//
// MessageId: EMS_SITMSGCORE_INITIALIZE_SIT_NO_DEFN
//
// MessageText:
//
// EMS SIT Message Core reports that a Message object was not set with a definition prior to initializing.
//
#define EMS_SITMSGCORE_INITIALIZE_SIT_NO_DEFN ((EMS_RESULT)0x8004C631L)

//
// MessageId: EMS_SITMSGCORE_SIT_ADDCHILD_NO_EMBEDDED_DEFINED
//
// MessageText:
//
// EMS SIT Message Core reports an attempt to encapsulate a SIT message within another SIT that is not defined as a container.
//
#define EMS_SITMSGCORE_SIT_ADDCHILD_NO_EMBEDDED_DEFINED ((EMS_RESULT)0x8004C632L)

//
// MessageId: EMS_SITMSGFILESCAN_NO_LOG_FILE_SPECD
//
// MessageText:
//
// EMS SIT Message File Scanner reports that a request to write a processed file log to disk cannot be performed because a destination file path and name has not been specified.
//
#define EMS_SITMSGFILESCAN_NO_LOG_FILE_SPECD ((EMS_RESULT)0x8004C633L)

//
// MessageId: EMS_SITMSGFILESCAN_INVALID_LOG_ENTRY_FORMAT
//
// MessageText:
//
// EMS SIT Message File Scanner reports that an entry of an invalid format was found in a log file.  Line contents:  <%1>.
//
#define EMS_SITMSGFILESCAN_INVALID_LOG_ENTRY_FORMAT ((EMS_RESULT)0x8004C634L)

//
// MessageId: EMS_SITMSGFILESCAN_NO_TRANS_DIR_SPECIFIED
//
// MessageText:
//
// EMS SIT Message File Scanner reports that no transfer directory has been specified.
//
#define EMS_SITMSGFILESCAN_NO_TRANS_DIR_SPECIFIED ((EMS_RESULT)0x8004C635L)

//
// MessageId: EMS_SITMSGFILESCAN_NO_LOG_DIR_SPECIFIED
//
// MessageText:
//
// EMS SIT Message File Scanner reports that no directory for outputting receive log files has been specified.
//
#define EMS_SITMSGFILESCAN_NO_LOG_DIR_SPECIFIED ((EMS_RESULT)0x8004C636L)

//
// MessageId: EMS_SITMSGFILESCAN_LOG_FILE_NAME_CREATION
//
// MessageText:
//
// EMS SIT Message File Scanner reports that a log file name could not be constructed.
//
#define EMS_SITMSGFILESCAN_LOG_FILE_NAME_CREATION ((EMS_RESULT)0x8004C637L)

//
// MessageId: EMS_SITMSGCORE_SET_SUBMF_UNHANDLEDTYPE
//
// MessageText:
//
// EMS SIT Message Core reports that an attempt was made to set a sub-field's value using an unexpected data type.
//
#define EMS_SITMSGCORE_SET_SUBMF_UNHANDLEDTYPE ((EMS_RESULT)0x8004C638L)

//
// MessageId: EMS_SITMSGCORE_SET_SUBMF_NOFORMAT
//
// MessageText:
//
// EMS SIT Message Core reports that an attempt was made to set a sub-field's value using it's native type, but no format string could be found in the sub-field's definition.
//
#define EMS_SITMSGCORE_SET_SUBMF_NOFORMAT ((EMS_RESULT)0x8004C639L)

//
// MessageId: EMS_SITEDITOR_NO_VALIDATION_ERRORS
//
// MessageText:
//
// EMS SIT Editor reports no validation errors found.
//
#define EMS_SITEDITOR_NO_VALIDATION_ERRORS ((EMS_RESULT)0x0004C63AL)

//
// MessageId: EMS_SITMSGCORE_NO_ROUTES
//
// MessageText:
//
// EMS SIT Message Core reports that it could not retrieve a list of routes from the configuration manager due to error <%1>.
//
#define EMS_SITMSGCORE_NO_ROUTES         ((EMS_RESULT)0x8004C63BL)

//
// MessageId: EMS_SITMSGCORE_CONFIGURATION_READ_ERROR
//
// MessageText:
//
// EMS SIT Message Core reports configuration manager error <%1> while attempting to read [%2:%3].%4.
//
#define EMS_SITMSGCORE_CONFIGURATION_READ_ERROR ((EMS_RESULT)0x8004C63CL)

//
// MessageId: EMS_SITMSGCORE_CONFIGURATION_WRITE_ERROR
//
// MessageText:
//
// EMS SIT Message Core reports configuration manager error <%1> while attempting to set [%2:%3].%4 to value <%5>.
//
#define EMS_SITMSGCORE_CONFIGURATION_WRITE_ERROR ((EMS_RESULT)0x8004C63DL)

//
// MessageId: EMS_SITEDITOR_SENDING_INFO
//
// MessageText:
//
// EMS SIT Editor sending SIT Message on <%1> routes.
//
#define EMS_SITEDITOR_SENDING_INFO       ((EMS_RESULT)0x4004C63EL)

//
// MessageId: EMS_SITEDITOR_SENDING_TO_ROUTE_INFO
//
// MessageText:
//
// EMS SIT Editor sending SIT Message via route <%1>.
//
#define EMS_SITEDITOR_SENDING_TO_ROUTE_INFO ((EMS_RESULT)0x4004C63FL)

//
// MessageId: EMS_SITEDITOR_MSG_QUEUED_SUCCESS
//
// MessageText:
//
// EMS SIT Editor successfully queued message for transmission.
//
#define EMS_SITEDITOR_MSG_QUEUED_SUCCESS ((EMS_RESULT)0x0004C640L)

//
// MessageId: EMS_SITEDITOR_UNKNOWN_TRANSMISSION_ERROR
//
// MessageText:
//
// EMS SIT Editor reports that an unknown error has occurred when attempting to queue a message for transmission.  The error code is <%1>.
//
#define EMS_SITEDITOR_UNKNOWN_TRANSMISSION_ERROR ((EMS_RESULT)0x8004C641L)

//
// MessageId: EMS_SITEDITOR_UNKNOWN_ERROR
//
// MessageText:
//
// EMS SIT Editor reports that an error has occurred.  The error code is <%1>.
//
#define EMS_SITEDITOR_UNKNOWN_ERROR      ((EMS_RESULT)0x8004C642L)

//
// MessageId: EMS_SITEDITOR_LINE_INSERTION_ERROR
//
// MessageText:
//
// EMS SIT Editor reports an error attempting to insert a new line into a SIT message.
//
#define EMS_SITEDITOR_LINE_INSERTION_ERROR ((EMS_RESULT)0x8004C643L)

//
// MessageId: EMS_SITEDITOR_NO_SIT_DEFINED
//
// MessageText:
//
// EMS SIT Editor reports that it was unable to find the specification for SIT Type <%1> in the SIT Definitions.
//
#define EMS_SITEDITOR_NO_SIT_DEFINED     ((EMS_RESULT)0x8004C644L)

//
// MessageId: EMS_SITEDITOR_NO_EOLS_DEFINED
//
// MessageText:
//
// EMS SIT Editor reports that no End-Of-Line sequences are defined in the configuration.
//
#define EMS_SITEDITOR_NO_EOLS_DEFINED    ((EMS_RESULT)0x8004C645L)

//
// MessageId: EMS_SITEDITOR_NO_DEFAULT_SRC_SELECTED
//
// MessageText:
//
// EMS SIT Editor reports that no source has been selected for default.
//
#define EMS_SITEDITOR_NO_DEFAULT_SRC_SELECTED ((EMS_RESULT)0x8004C646L)

//
// MessageId: EMS_SITEDITOR_SIT_NOT_SUPPORTED
//
// MessageText:
//
// EMS SIT Editor reports that SIT <%1> is not supported.
//
#define EMS_SITEDITOR_SIT_NOT_SUPPORTED  ((EMS_RESULT)0x8004C647L)

//
// MessageId: EMS_SITEDITOR_TITLE
//
// MessageText:
//
// EMS SIT Editor
//
#define EMS_SITEDITOR_TITLE              ((EMS_RESULT)0x4004C648L)

//
// MessageId: EMS_SITEDITOR_SAVE_AS_PROMPT
//
// MessageText:
//
// Save currently open message to file before proceeding?
//
#define EMS_SITEDITOR_SAVE_AS_PROMPT     ((EMS_RESULT)0x4004C649L)

//
// MessageId: EMS_SITEDITOR_VALIDATION_ERRORS_PROMPT
//
// MessageText:
//
// Validation errors have been found.  Do you wish to continue anyway?
//
#define EMS_SITEDITOR_VALIDATION_ERRORS_PROMPT ((EMS_RESULT)0x4004C64AL)

//
// MessageId: EMS_SITMSGCORE_INVALID_MF_LENGTH
//
// MessageText:
//
// EMS SIT Message Core reports an error extracting a sub-field from MF <%1> with value <%2>.  The MF length is <%3>, but attempting to extract sub-field from offset <%4> with length <%5>.
//
#define EMS_SITMSGCORE_INVALID_MF_LENGTH ((EMS_RESULT)0x4004C64BL)

//
// MessageId: EMS_SITEDITOR_NO_TRANSFER_DIRECTORY
//
// MessageText:
//
// EMS SIT Editor reports that no transfer directory has been specified.  A value is required.
//
#define EMS_SITEDITOR_NO_TRANSFER_DIRECTORY ((EMS_RESULT)0x8004C64CL)

//
// MessageId: EMS_SITEDITOR_CANNOT_ACCESS_DIRECTORY
//
// MessageText:
//
// EMS SIT Editor reports that it cannot access the directory <%1>.
//
#define EMS_SITEDITOR_CANNOT_ACCESS_DIRECTORY ((EMS_RESULT)0x8004C64DL)

//
// MessageId: EMS_SITEDITOR_CHECKING_COMMS_STATUS
//
// MessageText:
//
// EMS SIT Editor checking EMS Communications subsystem status.
//
#define EMS_SITEDITOR_CHECKING_COMMS_STATUS ((EMS_RESULT)0x4004C64EL)

//
// MessageId: EMS_SITEDITOR_COMMS_SERVICE_RUNNING
//
// MessageText:
//
// EMS SIT Editor reports that the EMS Communications subsystem is running.
//
#define EMS_SITEDITOR_COMMS_SERVICE_RUNNING ((EMS_RESULT)0x4004C64FL)

//
// MessageId: EMS_SITEDITOR_COMMS_SERVICE_NOT_RUNNING
//
// MessageText:
//
// EMS SIT Editor reports that the EMS Communications subsystem could not be started.
//
#define EMS_SITEDITOR_COMMS_SERVICE_NOT_RUNNING ((EMS_RESULT)0x8004C650L)

//
// MessageId: EMS_SITEDITOR_INITIALIZING_SCANNER_INFO
//
// MessageText:
//
// EMS SIT Editor is initializing the directory scanner...
//
#define EMS_SITEDITOR_INITIALIZING_SCANNER_INFO ((EMS_RESULT)0x4004C651L)


#endif
/********************************************************************
*	Module:			GeneralMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for General Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_GENERALMSG
#define INC_GENERALMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_GENERAL_BASE_CODE
//
// MessageText:
//
// General messages.
//
#define EMS_GENERAL_BASE_CODE            ((EMS_RESULT)0x4004C900L)

//
// MessageId: EMS_GENERAL_FAILURE
//
// MessageText:
//
// A failure has occurred.  The error code is %1.
//
#define EMS_GENERAL_FAILURE              ((EMS_RESULT)0x8004C901L)

//
// MessageId: EMS_GENERAL_UNKNOWN
//
// MessageText:
//
// A failure has occurred.  No error code could be retrieved.
//
#define EMS_GENERAL_UNKNOWN              ((EMS_RESULT)0x8004C902L)

//
// MessageId: EMS_GENERAL_CANNOT_OPEN_SCM
//
// MessageText:
//
// A failure has occurred:  Cannot open the service control manager.
//
#define EMS_GENERAL_CANNOT_OPEN_SCM      ((EMS_RESULT)0x8004C903L)

//
// MessageId: EMS_GENERAL_CANNOT_OPEN_SERVICE
//
// MessageText:
//
// A failure has occurred:  Cannot open (%1) service from the control manager.
//
#define EMS_GENERAL_CANNOT_OPEN_SERVICE  ((EMS_RESULT)0x8004C904L)

//
// MessageId: EMS_GENERAL_NO_CALLER_ID
//
// MessageText:
//
// A failure has occurred:  Cannot connect to Gateway because the caller's identifier has not been specified.
//
#define EMS_GENERAL_NO_CALLER_ID         ((EMS_RESULT)0x8004C905L)

//
// MessageId: EMS_GENERAL_GATEWAY_CALL_FAILURE
//
// MessageText:
//
// A failure has occurred:  A Gateway call has returned error code (%1) with description (%2).
//
#define EMS_GENERAL_GATEWAY_CALL_FAILURE ((EMS_RESULT)0x8004C906L)

//
// MessageId: EMS_GENERAL_INVALID_LOCALE
//
// MessageText:
//
// Could not initialize language resources. Invalid locale.
//
#define EMS_GENERAL_INVALID_LOCALE       ((EMS_RESULT)0x8004C907L)

//
// MessageId: EMS_GENERAL_NO_DB_CONNECTION
//
// MessageText:
//
// There is no database connection available to process this request.
//
#define EMS_GENERAL_NO_DB_CONNECTION     ((EMS_RESULT)0x8004C908L)

//
// MessageId: EMS_GENERAL_XML_FILE_LOAD_FAIL
//
// MessageText:
//
// An error occurred attempting to load the XML file, (%1):  error code = (%2), reason = (%3), source = (%4).
//
#define EMS_GENERAL_XML_FILE_LOAD_FAIL   ((EMS_RESULT)0x8004C909L)

//
// MessageId: EMS_GENERAL_XML_LOAD_FAIL
//
// MessageText:
//
// An error occurred attempting to load XML from a string:  error code = (%1), reason = (%2), source = (%3).
//
#define EMS_GENERAL_XML_LOAD_FAIL        ((EMS_RESULT)0x8004C90AL)

//
// MessageId: EMS_TREE_STATUS_UPDATE_FAILED
//
// MessageText:
//
// Failed to update the LUT status displayed in the tree view.
//
#define EMS_TREE_STATUS_UPDATE_FAILED    ((EMS_RESULT)0x8004C90BL)

//
// MessageId: EMS_TREE_STATUS_INIT_FAILED
//
// MessageText:
//
// Failed to initialize the tree view LUT status display.
//
#define EMS_TREE_STATUS_INIT_FAILED      ((EMS_RESULT)0x8004C90CL)

//
// MessageId: EMS_LUTMONITOR_LAUNCH_FAILED
//
// MessageText:
//
// Failed to launch LUT Monitor due to error: "%1"
//
#define EMS_LUTMONITOR_LAUNCH_FAILED     ((EMS_RESULT)0x8004C90DL)

//
// MessageId: EMS_CONFIGURATION_ITEM_NOT_FOUND
//
// MessageText:
//
// Failed to find a configuration item: "%1".
//
#define EMS_CONFIGURATION_ITEM_NOT_FOUND ((EMS_RESULT)0x8004C90EL)

//
// MessageId: EMS_NSP_ERROR
//
// MessageText:
//
// An error has occurred in the NSP library.  Status = (%1), Function = (%2), Context = (%3), File = (%4), Line = (%5)
//
#define EMS_NSP_ERROR                    ((EMS_RESULT)0x8004C90FL)

//
// MessageId: EMS_SOAP_CALL_ERROR
//
// MessageText:
//
// A SOAP call failed.  Fault code = %1.  Fault string = %2.  Detail = %3
//
#define EMS_SOAP_CALL_ERROR              ((EMS_RESULT)0x8004C910L)

//
// MessageId: EMS_SOAP_FRAMEWORK_ERROR
//
// MessageText:
//
// A SOAP call failed.  The SOAP framework encountered an error with code = %1.
//
#define EMS_SOAP_FRAMEWORK_ERROR         ((EMS_RESULT)0x8004C911L)

//
// MessageId: EMS_INVALID_FILTERHEXVALUE
//
// MessageText:
//
// Failed to build query.  Invalid hex filter value specified.
//
#define EMS_INVALID_FILTERHEXVALUE       ((EMS_RESULT)0x8004C912L)


#endif
/********************************************************************
*	Module:			SolutionDisplayMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Solution Display Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_SOLNDISPMSG
#define INC_SOLNDISPMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SOLN_DISP_BASE_CODE
//
// MessageText:
//
// EMS Solution Display error.
//
#define EMS_SOLN_DISP_BASE_CODE          ((EMS_RESULT)0x8004C800L)

//
// MessageId: EMS_SOLN_DISP_ADD_CHILD_FAILURE
//
// MessageText:
//
// An error occurred adding a <%1> child node to <%2>.
//
#define EMS_SOLN_DISP_ADD_CHILD_FAILURE  ((EMS_RESULT)0x8004C801L)

//
// MessageId: EMS_SOLN_DISP_VIEWS_LOAD_FAILURE
//
// MessageText:
//
// An error occurred loading views from file <%1>.
//
#define EMS_SOLN_DISP_VIEWS_LOAD_FAILURE ((EMS_RESULT)0x8004C802L)

//
// MessageId: EMS_SOLN_DISP_GET_SOURCE_NODE_FAILURE
//
// MessageText:
//
// An error occurred attempting to retrieve a source node.
//
#define EMS_SOLN_DISP_GET_SOURCE_NODE_FAILURE ((EMS_RESULT)0x8004C803L)

//
// MessageId: EMS_SOLN_DISP_CLONE_NODE_FAILURE
//
// MessageText:
//
// An error occurred attempting to clone a source node.
//
#define EMS_SOLN_DISP_CLONE_NODE_FAILURE ((EMS_RESULT)0x8004C804L)

//
// MessageId: EMS_SOLN_DISP_CHILD_ADD_FAILURE
//
// MessageText:
//
// An error occurred while attempting to add the child element <%1>.
//
#define EMS_SOLN_DISP_CHILD_ADD_FAILURE  ((EMS_RESULT)0x8004C805L)

//
// MessageId: EMS_SOLN_DISP_ELEMENT_NOT_FOUND_IN_LAYER
//
// MessageText:
//
// An error occurred because the element <%1> could not be found in a layer configuration.
//
#define EMS_SOLN_DISP_ELEMENT_NOT_FOUND_IN_LAYER ((EMS_RESULT)0x8004C806L)

//
// MessageId: EMS_SOLN_DISP_FAILED_TO_CREATE_CHILD_NODE
//
// MessageText:
//
// An error occurred while attempting to add the child node <%1> to <%2>.
//
#define EMS_SOLN_DISP_FAILED_TO_CREATE_CHILD_NODE ((EMS_RESULT)0x8004C807L)

//
// MessageId: EMS_SOLN_DISP_NO_ROOT_NODE
//
// MessageText:
//
// An error occurred while attempting to retrieve a root node.
//
#define EMS_SOLN_DISP_NO_ROOT_NODE       ((EMS_RESULT)0x8004C808L)

//
// MessageId: EMS_SOLN_DISP_INVALID_BEACON_TYPE
//
// MessageText:
//
// An error has occurred.  An attempt was made to create a configuration profile for an unsupported beacon type, <%1>.
//
#define EMS_SOLN_DISP_INVALID_BEACON_TYPE ((EMS_RESULT)0x8004C809L)

//
// MessageId: EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE
//
// MessageText:
//
// An error has occurred.  An unrecognized beacon type was specified, <%1>.
//
#define EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE ((EMS_RESULT)0x8004C80AL)

//
// MessageId: EMS_SOLN_DISP_NO_BEACON_TYPE
//
// MessageText:
//
// An error has occurred.  No beacon type was specified in a request to display solutions.
//
#define EMS_SOLN_DISP_NO_BEACON_TYPE     ((EMS_RESULT)0x8004C80BL)

//
// MessageId: EMS_SOLN_DISP_UNKNOWN_ERROR
//
// MessageText:
//
// EMS Solution Display reports that an error has occurred.  The error code is <%1>.
//
#define EMS_SOLN_DISP_UNKNOWN_ERROR      ((EMS_RESULT)0x8004C80CL)

//
// MessageId: EMS_SOLN_DISP_TITLE
//
// MessageText:
//
// EMS Solution Display
//
#define EMS_SOLN_DISP_TITLE              ((EMS_RESULT)0x4004C80DL)

//
// MessageId: EMS_SOLN_DISP_BEACON_TYPE_CONFIG_NOT_FOUND
//
// MessageText:
//
// An error has occurred.  Unable to retrieve configuration for beacon type <%1> from the view configuration.
//
#define EMS_SOLN_DISP_BEACON_TYPE_CONFIG_NOT_FOUND ((EMS_RESULT)0x8004C80EL)

//
// MessageId: EMS_SOLN_DISP_RGB_VALUE_OUT_OF_RANGE
//
// MessageText:
//
// An error has occurred.  An out of range RGB value of <%1> was specified.  Values must be in the range <%2> to <%3>.
//
#define EMS_SOLN_DISP_RGB_VALUE_OUT_OF_RANGE ((EMS_RESULT)0x8004C80FL)

//
// MessageId: EMS_SOLN_DISP_LUT_CONFIG_NOT_FOUND
//
// MessageText:
//
// An error has occurred.  Unable to retrieve configuration for LUT <%1> from the view configuration.
//
#define EMS_SOLN_DISP_LUT_CONFIG_NOT_FOUND ((EMS_RESULT)0x8004C810L)

//
// MessageId: EMS_SOLN_DISP_SAT_CONFIG_NOT_FOUND
//
// MessageText:
//
// An error has occurred.  Unable to retrieve configuration for Satellite <%1> from the view configuration.
//
#define EMS_SOLN_DISP_SAT_CONFIG_NOT_FOUND ((EMS_RESULT)0x8004C811L)

//
// MessageId: EMS_SOLN_DISP_NO_CURRENT_VIEW
//
// MessageText:
//
// An error has occurred.  No View Configuration has been selected.
//
#define EMS_SOLN_DISP_NO_CURRENT_VIEW    ((EMS_RESULT)0x8004C812L)

//
// MessageId: EMS_SOLN_DISP_NO_SESSION
//
// MessageText:
//
// An error has occurred.  The Solution Display does not have a session identifier.
//
#define EMS_SOLN_DISP_NO_SESSION         ((EMS_RESULT)0x8004C813L)

//
// MessageId: EMS_SOLN_DISP_PROVIDER_EXCEPTION
//
// MessageText:
//
// An error has occurred.  An exception was thrown by the map provider.  The error code is <%1> and description is <%2>.
//
#define EMS_SOLN_DISP_PROVIDER_EXCEPTION ((EMS_RESULT)0x8004C814L)

//
// MessageId: EMS_SOLN_DISP_NO_BEACON_DETAILS
//
// MessageText:
//
// Detailed information for the selected beacon could not be found.
//
#define EMS_SOLN_DISP_NO_BEACON_DETAILS  ((EMS_RESULT)0x8004C815L)

//
// MessageId: EMS_SOLN_DISP_MUTUAL_CONFIG_NOT_FOUND
//
// MessageText:
//
// An error has occurred.  Unable to retrieve Mutual Visibility configuration for LUT <%1> from the view configuration.
//
#define EMS_SOLN_DISP_MUTUAL_CONFIG_NOT_FOUND ((EMS_RESULT)0x8004C816L)


#endif
/********************************************************************
*	Module:			EMSErrorMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Errors & Messages
*
*					Defined here so that the numbering remains unchanged
*					Note that this file actually contains multiple "categories".
*					Specifically:
*						EMSCAT_GENERAL
*						EMSCAT_MATH
*						EMSCAT_COMM
*						EMSCAT_IRDA
*						EMSCAT_TFTP
*						EMSCAT_COMP
*						EMSCAT_RPC
*
*					The file also ensures that there are error codes and messages
*					for the following standard Microsoft errors
*						EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
*						EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
*						EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111
*
*					The following errors were also moved here ...
*						Satellite errors ... EMSATFINFO.idl
*						SIT errors ... emssit.h
*						COMM errors ... AntError.h
*						ALTIT errors ... emsaltit.idl
*						BEACON errors ... emsbeacn.idl
*						REFRACTION errors ... emsfract.idl
*						SITEINFO errors ... emssiteif.idl
*						LUT errors ... emslinfo.idl
*						ORBIT errors ... emsorbit.idl
*						PASS errors ... emspass.idl
*						STATUS errors ... emsstatus.idl
*						TLE Server errors ... emsTLEServer.idl
*						Logger errors ... emsloggr.idl
*						GPS errors ... gpsclock.h
*						LOCATE errors ... LocateError.h
*
*					Note that these have been defined here (rather than in
*					a set of new mc files to minimize the number of files
*					that need to be changed.
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/



#ifndef INC_EMSERRORMSG
#define INC_EMSERRORMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

// *** EMSCAT_GENERAL = 0x80 ***

//
// MessageId: EMSCAT_GENERAL_BASE_CODE
//
// MessageText:
//
// General messages.
//
#define EMSCAT_GENERAL_BASE_CODE         ((EMS_RESULT)0x80048000L)

//
// MessageId: EMS_NO_MEMORY
//
// MessageText:
//
// An out of memory error has been detected.
//
#define EMS_NO_MEMORY                    ((EMS_RESULT)0x80048001L)

//
// MessageId: EMS_FILE_NOT_FOUND
//
// MessageText:
//
// The specified file cannot be found.
//
#define EMS_FILE_NOT_FOUND               ((EMS_RESULT)0x80048002L)

//
// MessageId: EMS_UNKNOWN_ERROR
//
// MessageText:
//
// An unexpected error has been detected.
//
#define EMS_UNKNOWN_ERROR                ((EMS_RESULT)0x80048003L)

//
// MessageId: EMS_INVALID_HANDLE
//
// MessageText:
//
// An invalid handle has been detected.
//
#define EMS_INVALID_HANDLE               ((EMS_RESULT)0x80048004L)

//
// MessageId: EMS_HANDLE_EOF
//
// MessageText:
//
// Unexpectedly reached end of file.
//
#define EMS_HANDLE_EOF                   ((EMS_RESULT)0x80048005L)

//
// MessageId: EMS_FILE_EXISTS
//
// MessageText:
//
// Specified file already exists.
//
#define EMS_FILE_EXISTS                  ((EMS_RESULT)0x80048006L)

//
// MessageId: EMS_EOF
//
// MessageText:
//
// Unexpectedly reached end of file.
//
#define EMS_EOF                          ((EMS_RESULT)0x80048007L)

//
// MessageId: EMS_NO_FILE
//
// MessageText:
//
// File could not be opened.
//
#define EMS_NO_FILE                      ((EMS_RESULT)0x80048008L)

//
// MessageId: EMS_UNSUPPORTED
//
// MessageText:
//
// Unsupported request has been made.
//
#define EMS_UNSUPPORTED                  ((EMS_RESULT)0x80048009L)

//
// MessageId: EMS_IO_ERROR
//
// MessageText:
//
// I/O error detected.
//
#define EMS_IO_ERROR                     ((EMS_RESULT)0x8004800AL)

//
// MessageId: EMS_NOT_IMPLEMENTED
//
// MessageText:
//
// Requested functionality has not been implemented.
//
#define EMS_NOT_IMPLEMENTED              ((EMS_RESULT)0x8004800BL)

//
// MessageId: EMS_ALREADY_INSTALLED
//
// MessageText:
//
// Requested functionality has already been installed.
//
#define EMS_ALREADY_INSTALLED            ((EMS_RESULT)0x8004800CL)

//
// MessageId: EMS_CANNOT_UNINSTALL
//
// MessageText:
//
// Cannot uninstall.
//
#define EMS_CANNOT_UNINSTALL             ((EMS_RESULT)0x8004800DL)

//
// MessageId: EMS_PATH_NOT_FOUND
//
// MessageText:
//
// Specified path not found.
//
#define EMS_PATH_NOT_FOUND               ((EMS_RESULT)0x8004800EL)

//
// MessageId: EMS_ACCESS_DENIED
//
// MessageText:
//
// Access denied.
//
#define EMS_ACCESS_DENIED                ((EMS_RESULT)0x8004800FL)

//
// MessageId: EMS_BAD_PARAM
//
// MessageText:
//
// Invalid parameter received.
//
#define EMS_BAD_PARAM                    ((EMS_RESULT)0x80048010L)

//
// MessageId: EMS_DISK_FULL
//
// MessageText:
//
// Disk is full.
//
#define EMS_DISK_FULL                    ((EMS_RESULT)0x80048011L)

//
// MessageId: EMS_NO_DEVICE
//
// MessageText:
//
// No device.
//
#define EMS_NO_DEVICE                    ((EMS_RESULT)0x80048012L)

//
// MessageId: EMS_ALREADY_OPEN
//
// MessageText:
//
// Specified resource is already open.
//
#define EMS_ALREADY_OPEN                 ((EMS_RESULT)0x80048013L)

//
// MessageId: EMS_INVALID_CMD
//
// MessageText:
//
// Invalid command received.
//
#define EMS_INVALID_CMD                  ((EMS_RESULT)0x80048014L)

//
// MessageId: EMS_UNAVAIL
//
// MessageText:
//
// Specified resource is unavailable.
//
#define EMS_UNAVAIL                      ((EMS_RESULT)0x80048015L)

//
// MessageId: EMS_INVALID_TIME
//
// MessageText:
//
// Invalid time specified.
//
#define EMS_INVALID_TIME                 ((EMS_RESULT)0x80048016L)

//
// MessageId: EMS_ALREADY_INITIALIZED
//
// MessageText:
//
// Request to initialize device or service that has already been initialized.
//
#define EMS_ALREADY_INITIALIZED          ((EMS_RESULT)0x80048017L)

//
// MessageId: EMS_NOT_INITIALIZED
//
// MessageText:
//
// Request to access device or service that has not been initialized.
//
#define EMS_NOT_INITIALIZED              ((EMS_RESULT)0x80048018L)

//
// MessageId: EMS_NOT_DESIRED_LANGUAGE
//
// MessageText:
//
// Failed to load specified language.
//
#define EMS_NOT_DESIRED_LANGUAGE         ((EMS_RESULT)0x80048019L)

//
// MessageId: EMS_INVALID_FILESPEC
//
// MessageText:
//
// Invalid file specification.
//
#define EMS_INVALID_FILESPEC             ((EMS_RESULT)0x8004801AL)

//
// MessageId: EMS_OVERFLOW
//
// MessageText:
//
// Overflow detected.
//
#define EMS_OVERFLOW                     ((EMS_RESULT)0x8004801BL)

//
// MessageId: EMS_EMPTY
//
// MessageText:
//
// Empty dataset.
//
#define EMS_EMPTY                        ((EMS_RESULT)0x8004801CL)

//
// MessageId: EMS_INVALID_PTR
//
// MessageText:
//
// Invalid pointer detected.
//
#define EMS_INVALID_PTR                  ((EMS_RESULT)0x8004801DL)

//
// MessageId: EMS_GPS_NOT_TRACK
//
// MessageText:
//
// GPS is not tracking.
//
#define EMS_GPS_NOT_TRACK                ((EMS_RESULT)0x8004801EL)

//
// MessageId: EMS_TRUNCATED
//
// MessageText:
//
// Truncated data detected.
//
#define EMS_TRUNCATED                    ((EMS_RESULT)0x8004801FL)

//
// MessageId: EMS_INVALID_STREAM
//
// MessageText:
//
// Invalid stream detected.
//
#define EMS_INVALID_STREAM               ((EMS_RESULT)0x80048020L)

//
// MessageId: EMS_LINE_LIMIT_EXCEEDED
//
// MessageText:
//
// Line limit exceeded.
//
#define EMS_LINE_LIMIT_EXCEEDED          ((EMS_RESULT)0x80048021L)

//
// MessageId: EMS_EXCEPTION
//
// MessageText:
//
// Unhandled exception detected.
//
#define EMS_EXCEPTION                    ((EMS_RESULT)0x80048022L)

//
// MessageId: EMS_EXCEPTION_CONTEXT
//
// MessageText:
//
// Unhandled exception detected (%1 : %2).
//
#define EMS_EXCEPTION_CONTEXT            ((EMS_RESULT)0x80048023L)

//
// MessageId: EMS_MISSING_B_SIDE
//
// MessageText:
//
// Missing B side.
//
#define EMS_MISSING_B_SIDE               ((EMS_RESULT)0x80048024L)

//
// MessageId: EMS_EOL
//
// MessageText:
//
// End of line reached.
//
#define EMS_EOL                          ((EMS_RESULT)0x80048025L)

//
// MessageId: EMS_SYNTAX_ERROR
//
// MessageText:
//
// Syntax error detected.
//
#define EMS_SYNTAX_ERROR                 ((EMS_RESULT)0x80048026L)

//
// MessageId: EMS_ERROR_ORBIT_NUMBER_NOT_MATCH
//
// MessageText:
//
// One or more passes have different orbit numbers.
//
#define EMS_ERROR_ORBIT_NUMBER_NOT_MATCH ((EMS_RESULT)0x80048027L)

//
// MessageId: EMS_UNKNOWN_SERVER_TYPE
//
// MessageText:
//
// Unknown server type specified.
//
#define EMS_UNKNOWN_SERVER_TYPE          ((EMS_RESULT)0x80048028L)

//
// MessageId: EMS_INVALID_URL
//
// MessageText:
//
// Invalid URL specified.
//
#define EMS_INVALID_URL                  ((EMS_RESULT)0x80048029L)

//
// MessageId: EMS_INVALID_STREAM_POS
//
// MessageText:
//
// Invalid stream position specified.
//
#define EMS_INVALID_STREAM_POS           ((EMS_RESULT)0x8004802AL)

//
// MessageId: EMS_UNKNOWN_PARAM_TYPE
//
// MessageText:
//
// Unknown parameter type specified.
//
#define EMS_UNKNOWN_PARAM_TYPE           ((EMS_RESULT)0x8004802BL)

//
// MessageId: EMS_DATA_INVALID
//
// MessageText:
//
// Invalid data detected.
//
#define EMS_DATA_INVALID                 ((EMS_RESULT)0x8004802CL)

//
// MessageId: EMS_UNKNOWN_URL_TYPE
//
// MessageText:
//
// Unknown URL type specified.
//
#define EMS_UNKNOWN_URL_TYPE             ((EMS_RESULT)0x8004802DL)

//
// MessageId: EMS_UNSUPPORTED_URL_TYPE
//
// MessageText:
//
// Unsupported URL type specified.
//
#define EMS_UNSUPPORTED_URL_TYPE         ((EMS_RESULT)0x8004802EL)

//
// MessageId: EMS_WAIT_TIMEOUT
//
// MessageText:
//
// A system wait has timed out.
//
#define EMS_WAIT_TIMEOUT                 ((EMS_RESULT)0x8004802FL)

//
// MessageId: EMS_WAIT_ABANDONDED
//
// MessageText:
//
// A system wait has been abandoned.
//
#define EMS_WAIT_ABANDONDED              ((EMS_RESULT)0x80048030L)

//
// MessageId: EMS_ARRAY_OUT_OF_BOUNDS
//
// MessageText:
//
// Array out of bounds.
//
#define EMS_ARRAY_OUT_OF_BOUNDS          ((EMS_RESULT)0x80048031L)

//
// MessageId: EMS_OBJECT_CREATE_FAILED
//
// MessageText:
//
// Failed to create object %1 with error %2.
//
#define EMS_OBJECT_CREATE_FAILED         ((EMS_RESULT)0x80048032L)

//
// MessageId: EMS_QUERY_INTERFACE_ERROR
//
// MessageText:
//
// Failed to retrieve interface %1 with error %2.
//
#define EMS_QUERY_INTERFACE_ERROR        ((EMS_RESULT)0x80048033L)

//
// MessageId: EMS_NO_MATCHING_RECORD
//
// MessageText:
//
// No matching record found.
//
#define EMS_NO_MATCHING_RECORD           ((EMS_RESULT)0x80048034L)

//
// MessageId: EMS_DIRECTORY_NOT_EMPTY
//
// MessageText:
//
// Failed to delete a directory because it is not empty.
//
#define EMS_DIRECTORY_NOT_EMPTY          ((EMS_RESULT)0x80048035L)

//
// MessageId: EMS_BAD_REGISTRY_ENTRY
//
// MessageText:
//
// Failed to find an expected entry in the registry %1
//
#define EMS_BAD_REGISTRY_ENTRY           ((EMS_RESULT)0x80048036L)


// *** EMSCAT_MATH = 0x81 ***

//
// MessageId: EMSCAT_MATH_BASE_CODE
//
// MessageText:
//
// Math error messages.
//
#define EMSCAT_MATH_BASE_CODE            ((EMS_RESULT)0x80048100L)

//
// MessageId: EMS_CBCOPY_ZERO_LENGTH
//
// MessageText:
//
// Zero length cbcopy requested.
//
#define EMS_CBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048101L)

//
// MessageId: EMS_SBCOPY_ZERO_LENGTH
//
// MessageText:
//
// Zero length sbcopy requested.
//
#define EMS_SBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048102L)

//
// MessageId: EMS_WBCOPY_ZERO_LENGTH
//
// MessageText:
//
// Zero length wbcopy requested.
//
#define EMS_WBCOPY_ZERO_LENGTH           ((EMS_RESULT)0x80048103L)


// *** EMSCAT_COMM = 0x82 ***

//
// MessageId: EMSCAT_COMM_BASE_CODE
//
// MessageText:
//
// Communication error messages.
//
#define EMSCAT_COMM_BASE_CODE            ((EMS_RESULT)0x80048200L)

//
// MessageId: EMS_TIMEOUT
//
// MessageText:
//
// A timeout was detected.
//
#define EMS_TIMEOUT                      ((EMS_RESULT)0x80048201L)

//
// MessageId: EMS_NOT_OPEN
//
// MessageText:
//
// Could not open specified device or link.
//
#define EMS_NOT_OPEN                     ((EMS_RESULT)0x80048202L)

//
// MessageId: EMS_TRANSMIT_ERR
//
// MessageText:
//
// Transmit error detected.
//
#define EMS_TRANSMIT_ERR                 ((EMS_RESULT)0x80048203L)

//
// MessageId: EMS_CHECKSUM_ERR
//
// MessageText:
//
// Checksum error detected.
//
#define EMS_CHECKSUM_ERR                 ((EMS_RESULT)0x80048204L)

//
// MessageId: EMS_SEQNUMBER_ERR
//
// MessageText:
//
// Sequence number error detected.
//
#define EMS_SEQNUMBER_ERR                ((EMS_RESULT)0x80048205L)

//
// MessageId: EMS_OP_CANCELLED
//
// MessageText:
//
// Operation cancelled.
//
#define EMS_OP_CANCELLED                 ((EMS_RESULT)0x80048206L)

//
// MessageId: EMS_ERROR_LIMIT
//
// MessageText:
//
// Error limit reached.
//
#define EMS_ERROR_LIMIT                  ((EMS_RESULT)0x80048207L)

//
// MessageId: EMS_DUPLICATE_SEQ
//
// MessageText:
//
// Communications duplicate sequence number detected.
//
#define EMS_DUPLICATE_SEQ                ((EMS_RESULT)0x80048208L)

//
// MessageId: EMS_PACKET_ERR
//
// MessageText:
//
// Packet error detected.
//
#define EMS_PACKET_ERR                   ((EMS_RESULT)0x80048209L)

//
// MessageId: EMS_UNKNOWN_DATA
//
// MessageText:
//
// Request to process unknown data.
//
#define EMS_UNKNOWN_DATA                 ((EMS_RESULT)0x8004820AL)

//
// MessageId: EMS_RECV_ERR
//
// MessageText:
//
// Data receive error.
//
#define EMS_RECV_ERR                     ((EMS_RESULT)0x8004820BL)

//
// MessageId: EMS_OVERRUN_ERR
//
// MessageText:
//
// Overrun error detected.
//
#define EMS_OVERRUN_ERR                  ((EMS_RESULT)0x8004820CL)

//
// MessageId: EMS_PARITY_ERR
//
// MessageText:
//
// Parity error detected.
//
#define EMS_PARITY_ERR                   ((EMS_RESULT)0x8004820DL)

//
// MessageId: EMS_FRAMING_ERR
//
// MessageText:
//
// Framing error detected.
//
#define EMS_FRAMING_ERR                  ((EMS_RESULT)0x8004820EL)

//
// MessageId: EMS_BREAKDETECT_ERR
//
// MessageText:
//
// Break detected.
//
#define EMS_BREAKDETECT_ERR              ((EMS_RESULT)0x8004820FL)

//
// MessageId: EMS_NO_PACKET_SERVICE
//
// MessageText:
//
// No packet service available.
//
#define EMS_NO_PACKET_SERVICE            ((EMS_RESULT)0x80048210L)

//
// MessageId: EMS_OP_ABORTED
//
// MessageText:
//
// Operation aborted.
//
#define EMS_OP_ABORTED                   ((EMS_RESULT)0x80048211L)

//
// MessageId: EMS_NO_COM_PORT
//
// MessageText:
//
// No COM port available.
//
#define EMS_NO_COM_PORT                  ((EMS_RESULT)0x80048212L)

//
// MessageId: EMS_AZ_RX_FLUSH_ERROR
//
// MessageText:
//
// AZ/RX flush error.
//
#define EMS_AZ_RX_FLUSH_ERROR            ((EMS_RESULT)0x80048213L)

//
// MessageId: EMS_AZ_TX_FLUSH_ERROR
//
// MessageText:
//
// AZ/TX flush error.
//
#define EMS_AZ_TX_FLUSH_ERROR            ((EMS_RESULT)0x80048214L)

//
// MessageId: EMS_EL_RX_FLUSH_ERROR
//
// MessageText:
//
// EL/RX flush error.
//
#define EMS_EL_RX_FLUSH_ERROR            ((EMS_RESULT)0x80048215L)

//
// MessageId: EMS_EL_TX_FLUSH_ERROR
//
// MessageText:
//
// EL/TX flush error.
//
#define EMS_EL_TX_FLUSH_ERROR            ((EMS_RESULT)0x80048216L)

//
// MessageId: EMS_CANT_OPEN_AZELFILE
//
// MessageText:
//
// Cannot open AZ/EL file.
//
#define EMS_CANT_OPEN_AZELFILE           ((EMS_RESULT)0x80048217L)

//
// MessageId: EMS_SOCKET_CREATE_ERROR
//
// MessageText:
//
// Failed to create a socket.  Winsock error is %1.
//
#define EMS_SOCKET_CREATE_ERROR          ((EMS_RESULT)0x80048218L)

//
// MessageId: EMS_SOCKET_STARTUP_ERROR
//
// MessageText:
//
// Failed to start sockets subsystem.  Winsock error is %1.
//
#define EMS_SOCKET_STARTUP_ERROR         ((EMS_RESULT)0x80048219L)

//
// MessageId: EMS_SOCKET_ACCEPT_DEBUG
//
// MessageText:
//
// Socket connection accepted.
//
#define EMS_SOCKET_ACCEPT_DEBUG          ((EMS_RESULT)0x4004821AL)

//
// MessageId: EMS_SOCKET_ACCEPT_ERROR
//
// MessageText:
//
// Failed to accept a socket connection.  Winsock error is %1.
//
#define EMS_SOCKET_ACCEPT_ERROR          ((EMS_RESULT)0x8004821BL)

//
// MessageId: EMS_SOCKET_BIND_DEBUG
//
// MessageText:
//
// Bound socket to IP=%1, port=%2.
//
#define EMS_SOCKET_BIND_DEBUG            ((EMS_RESULT)0x4004821CL)

//
// MessageId: EMS_SOCKET_BIND_ERROR
//
// MessageText:
//
// Failed to bind socket to IP=%1, port=%2.  Winsock error is %3.
//
#define EMS_SOCKET_BIND_ERROR            ((EMS_RESULT)0x8004821DL)

//
// MessageId: EMS_SOCKET_CLOSE_ERROR
//
// MessageText:
//
// Error closing socket.  Winsock error is %1.
//
#define EMS_SOCKET_CLOSE_ERROR           ((EMS_RESULT)0x8004821EL)

//
// MessageId: EMS_SOCKET_CONNECT_DEBUG
//
// MessageText:
//
// Connected to socket at IP=%1, port=%2.
//
#define EMS_SOCKET_CONNECT_DEBUG         ((EMS_RESULT)0x4004821FL)

//
// MessageId: EMS_SOCKET_CONNECT_ERROR
//
// MessageText:
//
// Failed to connect socket to IP=%1, port=%2.  Winsock error is %3.
//
#define EMS_SOCKET_CONNECT_ERROR         ((EMS_RESULT)0x80048220L)

//
// MessageId: EMS_SOCKET_LISTEN_DEBUG
//
// MessageText:
//
// Listening for connections on socket.
//
#define EMS_SOCKET_LISTEN_DEBUG          ((EMS_RESULT)0x40048221L)

//
// MessageId: EMS_SOCKET_LISTEN_ERROR
//
// MessageText:
//
// Error listening for socket connection.  Winsock error is %1.
//
#define EMS_SOCKET_LISTEN_ERROR          ((EMS_RESULT)0x80048222L)

//
// MessageId: EMS_SOCKET_RECV_DEBUG
//
// MessageText:
//
// Received %1 bytes on socket.
//
#define EMS_SOCKET_RECV_DEBUG            ((EMS_RESULT)0x40048223L)

//
// MessageId: EMS_SOCKET_RECV_ERROR
//
// MessageText:
//
// Error receiving on socket.  Winsock error is %1.
//
#define EMS_SOCKET_RECV_ERROR            ((EMS_RESULT)0x80048224L)

//
// MessageId: EMS_SOCKET_SENDREQ_DEBUG
//
// MessageText:
//
// Requesting send of %1 bytes with WS2 flags = %2.
//
#define EMS_SOCKET_SENDREQ_DEBUG         ((EMS_RESULT)0x40048225L)

//
// MessageId: EMS_SOCKET_SEND_ERROR
//
// MessageText:
//
// Error sending on socket.  Winsock error is %1.
//
#define EMS_SOCKET_SEND_ERROR            ((EMS_RESULT)0x80048226L)

//
// MessageId: EMS_SOCKET_SEND_DEBUG
//
// MessageText:
//
// Sent %1 bytes on socket.
//
#define EMS_SOCKET_SEND_DEBUG            ((EMS_RESULT)0x40048227L)

//
// MessageId: EMS_SOCKET_SHUTDOWN_ERROR
//
// MessageText:
//
// Error shutting down socket.  Winsock error is %1.
//
#define EMS_SOCKET_SHUTDOWN_ERROR        ((EMS_RESULT)0x80048228L)

//
// MessageId: EMS_SOCKET_SHUTDOWN_DEBUG
//
// MessageText:
//
// Socket was shutdown.
//
#define EMS_SOCKET_SHUTDOWN_DEBUG        ((EMS_RESULT)0x40048229L)

//
// MessageId: EMS_SOCKET_SELECT_ERROR
//
// MessageText:
//
// Error selecting socket status.  Winsock error is %1.
//
#define EMS_SOCKET_SELECT_ERROR          ((EMS_RESULT)0x8004822AL)

//
// MessageId: EMS_SOCKET_SELECT_READ_DEBUG
//
// MessageText:
//
// Socket read status is %1.
//
#define EMS_SOCKET_SELECT_READ_DEBUG     ((EMS_RESULT)0x4004822BL)

//
// MessageId: EMS_SOCKET_SELECT_WRITE_DEBUG
//
// MessageText:
//
// Socket write status is %1.
//
#define EMS_SOCKET_SELECT_WRITE_DEBUG    ((EMS_RESULT)0x4004822CL)

//
// MessageId: EMS_SOCKET_FAMILY_ERROR
//
// MessageText:
//
// Unrecognized socket address family encountered.
//
#define EMS_SOCKET_FAMILY_ERROR          ((EMS_RESULT)0x8004822DL)

//
// MessageId: EMS_SNMP_CREATEFAILED
//
// MessageText:
//
// Failed to initialize SNMP communications.
//
#define EMS_SNMP_CREATEFAILED            ((EMS_RESULT)0x8004822EL)


// *** EMSCAT_IRDA = 0x83 ***

//
// MessageId: EMSCAT_IRDA_BASE_CODE
//
// MessageText:
//
// IrDA error messages.
//
#define EMSCAT_IRDA_BASE_CODE            ((EMS_RESULT)0x80048300L)

//
// MessageId: EMS_IRDA_NOT_FOUND
//
// MessageText:
//
// IrDA: not found.
//
#define EMS_IRDA_NOT_FOUND               ((EMS_RESULT)0x80048301L)

//
// MessageId: EMS_IRDA_NOT_ACTIVE
//
// MessageText:
//
// IrDA: not active.
//
#define EMS_IRDA_NOT_ACTIVE              ((EMS_RESULT)0x80048302L)

//
// MessageId: EMS_IRDA_NO_CONNECTION
//
// MessageText:
//
// IrDA: no connection.
//
#define EMS_IRDA_NO_CONNECTION           ((EMS_RESULT)0x80048303L)

//
// MessageId: EMS_IRDA_IN_USE
//
// MessageText:
//
// IrDA: in use.
//
#define EMS_IRDA_IN_USE                  ((EMS_RESULT)0x80048304L)


// *** EMSCAT_TFTP = 0x84 ***

//
// MessageId: EMSCAT_TFTP_BASE_CODE
//
// MessageText:
//
// TFTP error messages.
//
#define EMSCAT_TFTP_BASE_CODE            ((EMS_RESULT)0x80048400L)

//
// MessageId: EMS_TFTP_ERROR
//
// MessageText:
//
// TFTP error.
//
#define EMS_TFTP_ERROR                   ((EMS_RESULT)0x80048401L)

//
// MessageId: EMS_TFTP_INVALID_OP
//
// MessageText:
//
// TFTP error: invalid operation.
//
#define EMS_TFTP_INVALID_OP              ((EMS_RESULT)0x80048402L)

//
// MessageId: EMS_TFTP_UNKNOWN_ID
//
// MessageText:
//
// TFTP error: unknown id.
//
#define EMS_TFTP_UNKNOWN_ID              ((EMS_RESULT)0x80048403L)


// *** EMSCAT_COMP = 0x85 ***

//
// MessageId: EMSCAT_COMP_BASE_CODE
//
// MessageText:
//
// Computer error messages.
//
#define EMSCAT_COMP_BASE_CODE            ((EMS_RESULT)0x80048500L)

//
// MessageId: EMS_NO_COMPUTERS
//
// MessageText:
//
// No computers can be detected.
//
#define EMS_NO_COMPUTERS                 ((EMS_RESULT)0x80048501L)

#define EMS_NO_TERMINALS		EMS_NO_COMPUTERS

//
// MessageId: EMS_GUID_NOT_FOUND
//
// MessageText:
//
// Specified GUID not found.
//
#define EMS_GUID_NOT_FOUND               ((EMS_RESULT)0x80048502L)

//
// MessageId: EMS_INVALID_DRIVE
//
// MessageText:
//
// Invalid drive specified.
//
#define EMS_INVALID_DRIVE                ((EMS_RESULT)0x80048503L)

//
// MessageId: EMS_MULTIPLEX_ERR
//
// MessageText:
//
// Multiplex error detected.
//
#define EMS_MULTIPLEX_ERR                ((EMS_RESULT)0x80048504L)

//
// MessageId: EMS_SERVICE_BUSY_ERR
//
// MessageText:
//
// Requested service is busy.
//
#define EMS_SERVICE_BUSY_ERR             ((EMS_RESULT)0x80048505L)

//
// MessageId: EMS_UNKNOWN_COMPUTER_TYPE
//
// MessageText:
//
// Unknown computer type specified.
//
#define EMS_UNKNOWN_COMPUTER_TYPE        ((EMS_RESULT)0x80048506L)

#define EMS_UNKNOWN_TERMTYPE	EMS_UNKNOWN_COMPUTER_TYPE


// *** EMSCAT_RPC = 0x86 ***

//
// MessageId: EMSCAT_RPC_BASE_CODE
//
// MessageText:
//
// RPC error messages.
//
#define EMSCAT_RPC_BASE_CODE             ((EMS_RESULT)0x80048600L)

//
// MessageId: EMS_RPC_UNKNOWN_PROTOCOL
//
// MessageText:
//
// RPC error: Unknown protocol specified.
//
#define EMS_RPC_UNKNOWN_PROTOCOL         ((EMS_RESULT)0x80048601L)

//
// MessageId: EMS_RPC_LIMIT_EXCEEDED
//
// MessageText:
//
// RPC error: Limit exceeded.
//
#define EMS_RPC_LIMIT_EXCEEDED           ((EMS_RESULT)0x80048602L)

//
// MessageId: EMS_RPC_NO_CLIENT
//
// MessageText:
//
// RPC error: No client.
//
#define EMS_RPC_NO_CLIENT                ((EMS_RESULT)0x80048603L)

//
// MessageId: EMS_RPC_ERROR
//
// MessageText:
//
// RPC error detected.
//
#define EMS_RPC_ERROR                    ((EMS_RESULT)0x80048604L)

//
// MessageId: EMS_RPC_NOT_CONNECTED
//
// MessageText:
//
// RPC error: Not connected.
//
#define EMS_RPC_NOT_CONNECTED            ((EMS_RESULT)0x80048605L)

//
// MessageId: EMS_RPC_UNKNOWN_HANDLER
//
// MessageText:
//
// RPC error: Unknown handler.
//
#define EMS_RPC_UNKNOWN_HANDLER          ((EMS_RESULT)0x80048606L)

//
// MessageId: EMS_RPC_UNKNOWN_METHOD
//
// MessageText:
//
// RPC error: Unknown method.
//
#define EMS_RPC_UNKNOWN_METHOD           ((EMS_RESULT)0x80048607L)


// *** EMSCAT_ORBIT = 0x89 ***

//
// MessageId: EMSCAT_ORBIT_BASE_CODE
//
// MessageText:
//
// Orbit errors.
//
#define EMSCAT_ORBIT_BASE_CODE           ((EMS_RESULT)0x80048900L)

//
// MessageId: EMS_NO_ORBIT_OBJ
//
// MessageText:
//
// No orbit object.
//
#define EMS_NO_ORBIT_OBJ                 ((EMS_RESULT)0x80048901L)

//
// MessageId: EMS_ORBIT_NO_SATELLITE
//
// MessageText:
//
// Specified satellite not found
//
#define EMS_ORBIT_NO_SATELLITE           ((EMS_RESULT)0x80048902L)

//
// MessageId: EMS_ORBIT_NO_DATA
//
// MessageText:
//
// No orbit data information has been initialized
//
#define EMS_ORBIT_NO_DATA                ((EMS_RESULT)0x80048903L)

//
// MessageId: EMS_ORBIT_BAD_DATA
//
// MessageText:
//
// Orbital elements have been corrupted
//
#define EMS_ORBIT_BAD_DATA               ((EMS_RESULT)0x80048904L)

//
// MessageId: EMS_ORBIT_BAD_TLEXNO
//
// MessageText:
//
// Orbit Constructor - Bad TLE.xno value: Must be > 0
//
#define EMS_ORBIT_BAD_TLEXNO             ((EMS_RESULT)0x80048905L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR1
//
// MessageText:
//
// Unexpected error at location 1 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR1     ((EMS_RESULT)0x80048906L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR2
//
// MessageText:
//
// Unexpected error at location 2 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR2     ((EMS_RESULT)0x80048907L)

//
// MessageId: EMS_ORBIT_UNEXPECTEDDEEPERR3
//
// MessageText:
//
// Unexpected error at location 3 in Deep.cpp
//
#define EMS_ORBIT_UNEXPECTEDDEEPERR3     ((EMS_RESULT)0x80048908L)

//
// MessageId: EMS_ORBIT_USEDEEPSPACE
//
// MessageText:
//
// Orbit Constructor determined - SHOULD USE DEEP SPACE EPHEMERIS
//
#define EMS_ORBIT_USEDEEPSPACE           ((EMS_RESULT)0x80048909L)

//
// MessageId: EMS_ORBIT_USENEAREARTH
//
// MessageText:
//
// Orbit Constructor determined - SHOULD USE NEAR EARTH EPHEMERIS
//
#define EMS_ORBIT_USENEAREARTH           ((EMS_RESULT)0x8004890AL)

//
// MessageId: EMS_ORBIT_INVALID_FILESPEC
//
// MessageText:
//
// EMS Orbit: Could not locate the file SARSAT.TXT
//
#define EMS_ORBIT_INVALID_FILESPEC       ((EMS_RESULT)0x8004890BL)

//
// MessageId: EMS_ORBIT_NO_MEMORY
//
// MessageText:
//
// EMS Orbit:  Out of memory error has been detected
//
#define EMS_ORBIT_NO_MEMORY              ((EMS_RESULT)0x8004890CL)


// *** EMSCAT_PASS = 0x8A ***

//
// MessageId: EMSCAT_PASS_BASE_CODE
//
// MessageText:
//
// Pass Schedule Errors
//
#define EMSCAT_PASS_BASE_CODE            ((EMS_RESULT)0x80048A00L)

//
// MessageId: EMS_PASS_NO_DATA
//
// MessageText:
//
// Pass scheduler: no data.
//
#define EMS_PASS_NO_DATA                 ((EMS_RESULT)0x80048A01L)

//
// MessageId: EMS_PASS_DATA_OVERFLOW
//
// MessageText:
//
// Pass scheduler: data overflow.
//
#define EMS_PASS_DATA_OVERFLOW           ((EMS_RESULT)0x80048A02L)


// *** EMSCAT_SAT = 0x8B ***

//
// MessageId: EMSCAT_SAT_BASE_CODE
//
// MessageText:
//
// Satellite error messages.
//
#define EMSCAT_SAT_BASE_CODE             ((EMS_RESULT)0x80048B00L)

//
// MessageId: EMS_NO_SATINFO_OBJ
//
// MessageText:
//
// Satellite error: no information object available.
//
#define EMS_NO_SATINFO_OBJ               ((EMS_RESULT)0x80048B01L)

//
// MessageId: EMS_SAT_NOT_FOUND
//
// MessageText:
//
// Satellite error: satellite not found.
//
#define EMS_SAT_NOT_FOUND                ((EMS_RESULT)0x80048B02L)

//
// MessageId: EMS_SAT_NO_DATA
//
// MessageText:
//
// Satellite error: no data.
//
#define EMS_SAT_NO_DATA                  ((EMS_RESULT)0x80048B03L)

//
// MessageId: EMS_SAT_INVALID
//
// MessageText:
//
// Satellite error: invalid satellite.
//
#define EMS_SAT_INVALID                  ((EMS_RESULT)0x80048B04L)


// *** EMSCAT_LUT = 0x8D ***

//
// MessageId: EMSCAT_LUT_BASE_CODE
//
// MessageText:
//
// LUT Info Errors
//
#define EMSCAT_LUT_BASE_CODE             ((EMS_RESULT)0x80048D00L)

//
// MessageId: EMS_NO_LUTINFO_OBJ
//
// MessageText:
//
// No LUT information object.
//
#define EMS_NO_LUTINFO_OBJ               ((EMS_RESULT)0x80048D01L)

//
// MessageId: EMS_LUT_NOT_FOUND
//
// MessageText:
//
// LUT not found.
//
#define EMS_LUT_NOT_FOUND                ((EMS_RESULT)0x80048D02L)

//
// MessageId: EMS_LUT_NO_DATA
//
// MessageText:
//
// LUT no data.
//
#define EMS_LUT_NO_DATA                  ((EMS_RESULT)0x80048D03L)


// *** EMSCAT_STATUS = 0x8F ***

//
// MessageId: EMSCAT_STATUS_BASE_CODE
//
// MessageText:
//
// Status Errors
//
#define EMSCAT_STATUS_BASE_CODE          ((EMS_RESULT)0x80048F00L)

//
// MessageId: EMS_NO_STATUS_OBJ
//
// MessageText:
//
// No status object.
//
#define EMS_NO_STATUS_OBJ                ((EMS_RESULT)0x80048F01L)

//
// MessageId: EMS_STATUS_NOT_INIT
//
// MessageText:
//
// Status not initialized.
//
#define EMS_STATUS_NOT_INIT              ((EMS_RESULT)0x80048F02L)


// *** EMSCAT_LOCATE = 0x90 ***

//
// MessageId: EMSCAT_LOCATE_BASE_CODE
//
// MessageText:
//
// Locate Errors
//
#define EMSCAT_LOCATE_BASE_CODE          ((EMS_RESULT)0x80049000L)

//
// MessageId: EMS_LOCATE_MEMORYALLOC_ERROR
//
// MessageText:
//
// Memory allocation error
//
#define EMS_LOCATE_MEMORYALLOC_ERROR     ((EMS_RESULT)0x80049001L)

//
// MessageId: EMS_LOCATE_FILE_ERROR
//
// MessageText:
//
// Problem opening file
//
#define EMS_LOCATE_FILE_ERROR            ((EMS_RESULT)0x80049002L)

//
// MessageId: EMS_LOCATE_READ_ERROR
//
// MessageText:
//
// Problem reading file
//
#define EMS_LOCATE_READ_ERROR            ((EMS_RESULT)0x80049003L)

//
// MessageId: EMS_LOCATE_NO_DATA
//
// MessageText:
//
// No locate data information has been initialized
//
#define EMS_LOCATE_NO_DATA               ((EMS_RESULT)0x80049004L)

//
// MessageId: EMS_LOCATE_IE_NON_CONVERGE
//
// MessageText:
//
// IE fails to converge
//
#define EMS_LOCATE_IE_NON_CONVERGE       ((EMS_RESULT)0x80049005L)

//
// MessageId: EMS_LOCATE_CN_NON_CONVERGE
//
// MessageText:
//
// Converge fails to converge
//
#define EMS_LOCATE_CN_NON_CONVERGE       ((EMS_RESULT)0x80049006L)

//
// MessageId: EMS_LOCATE_TCA_OUTOFBOUNDS
//
// MessageText:
//
// TCA out of bounds
//
#define EMS_LOCATE_TCA_OUTOFBOUNDS       ((EMS_RESULT)0x80049007L)

//
// MessageId: EMS_LOCATE_SOLVE_ERROR
//
// MessageText:
//
// Solve error
//
#define EMS_LOCATE_SOLVE_ERROR           ((EMS_RESULT)0x80049008L)

//
// MessageId: EMS_LOCATE_NO_POINTS
//
// MessageText:
//
// No points
//
#define EMS_LOCATE_NO_POINTS             ((EMS_RESULT)0x80049009L)

//
// MessageId: EMS_LOCATE_WLS_NON_CONVERGE
//
// MessageText:
//
// WLS fails to converge
//
#define EMS_LOCATE_WLS_NON_CONVERGE      ((EMS_RESULT)0x8004900AL)

//
// MessageId: EMS_LOCATE_WRITING_ERROR
//
// MessageText:
//
// Problem writing file
//
#define EMS_LOCATE_WRITING_ERROR         ((EMS_RESULT)0x8004900BL)


// *** EMSCAT_ADBOARD = 0x98 ***

//
// MessageId: EMSCAT_ADBOARD_BASE_CODE
//
// MessageText:
//
// A/D error messages.
//
#define EMSCAT_ADBOARD_BASE_CODE         ((EMS_RESULT)0x80049800L)

//
// MessageId: EMS_ADERR_IRQ_INUSE
//
// MessageText:
//
// A/D error: IRQ in use.
//
#define EMS_ADERR_IRQ_INUSE              ((EMS_RESULT)0x80049801L)

//
// MessageId: EMS_ADERR_FN_POINTER
//
// MessageText:
//
// A/D error: invalid function pointer.
//
#define EMS_ADERR_FN_POINTER             ((EMS_RESULT)0x80049802L)

//
// MessageId: EMS_ADERR_NO_INIT
//
// MessageText:
//
// A/D error: not intialized.
//
#define EMS_ADERR_NO_INIT                ((EMS_RESULT)0x80049803L)

//
// MessageId: EMS_ADERR_NO_DLL
//
// MessageText:
//
// A/D error: missing DLL.
//
#define EMS_ADERR_NO_DLL                 ((EMS_RESULT)0x80049804L)

//
// MessageId: EMS_ADERR_ALREADY_INIT
//
// MessageText:
//
// A/D error: already intialized.
//
#define EMS_ADERR_ALREADY_INIT           ((EMS_RESULT)0x80049805L)

//
// MessageId: EMS_ADERR_NO_BOARD
//
// MessageText:
//
// A/D error: no board.
//
#define EMS_ADERR_NO_BOARD               ((EMS_RESULT)0x80049806L)

//
// MessageId: EMS_USBDT_ECODE_ERROR
//
// MessageText:
//
// A/D board error (%1)
//
#define EMS_USBDT_ECODE_ERROR            ((EMS_RESULT)0x80049807L)


// *** EMSCAT_BEACON = 0x99 ***

//
// MessageId: EMSCAT_BEACON_BASE_CODE
//
// MessageText:
//
// Ref. Beacon Info Errors
//
#define EMSCAT_BEACON_BASE_CODE          ((EMS_RESULT)0x80049900L)

//
// MessageId: EMS_NO_BEACONINFO_OBJ
//
// MessageText:
//
// Missing beacon information object.
//
#define EMS_NO_BEACONINFO_OBJ            ((EMS_RESULT)0x80049901L)

//
// MessageId: EMS_BEACON_NOT_FOUND
//
// MessageText:
//
// Beacon not found.
//
#define EMS_BEACON_NOT_FOUND             ((EMS_RESULT)0x80049902L)

//
// MessageId: EMS_BEACON_NO_DATA
//
// MessageText:
//
// No beacon data.
//
#define EMS_BEACON_NO_DATA               ((EMS_RESULT)0x80049903L)


// *** EMSCAT_GPS = 0xB0 ***

//
// MessageId: EMSCAT_GPS_BASE_CODE
//
// MessageText:
//
// GPS errors
//
#define EMSCAT_GPS_BASE_CODE             ((EMS_RESULT)0x8004B000L)

//
// MessageId: EMS_ERR_GPS_NOT_LOCKED
//
// MessageText:
//
// GPS not locked.
//
#define EMS_ERR_GPS_NOT_LOCKED           ((EMS_RESULT)0x8004B001L)

//
// MessageId: EMS_ERR_GPS_ANTENNA
//
// MessageText:
//
// GPS antenna error.
//
#define EMS_ERR_GPS_ANTENNA              ((EMS_RESULT)0x8004B002L)

//
// MessageId: EMS_ERR_GPS_SYSTEM
//
// MessageText:
//
// GPS system error.
//
#define EMS_ERR_GPS_SYSTEM               ((EMS_RESULT)0x8004B003L)

//
// MessageId: EMS_ERR_GPS_INCORRECT_SAT
//
// MessageText:
//
// GPS Satellite ID does not match.
//
#define EMS_ERR_GPS_INCORRECT_SAT        ((EMS_RESULT)0x8004B004L)

//
// MessageId: EMS_ERR_GPS_INVALID_EPHEMERIS
//
// MessageText:
//
// GPS Satellite Ephemeris is invalid
//
#define EMS_ERR_GPS_INVALID_EPHEMERIS    ((EMS_RESULT)0x8004B005L)


// *** EMSCAT_ALTIT = 0xCO ***

//
// MessageId: EMSCAT_ALTIT_BASE_CODE
//
// MessageText:
//
// Altitude errors
//
#define EMSCAT_ALTIT_BASE_CODE           ((EMS_RESULT)0x8004C000L)

//
// MessageId: EMS_NO_ALTIT_OBJ
//
// MessageText:
//
// No altitude object.
//
#define EMS_NO_ALTIT_OBJ                 ((EMS_RESULT)0x8004C001L)

//
// MessageId: EMS_ALTIT_NO_DATA
//
// MessageText:
//
// No altitude data.
//
#define EMS_ALTIT_NO_DATA                ((EMS_RESULT)0x8004C002L)


// *** EMSCAT_FRACT = 0xC1 ***

//
// MessageId: EMSCAT_FRACT_BASE_CODE
//
// MessageText:
//
// Refraction Errors
//
#define EMSCAT_FRACT_BASE_CODE           ((EMS_RESULT)0x8004C100L)

//
// MessageId: EMS_NO_FRACT_OBJ
//
// MessageText:
//
// No refraction object.
//
#define EMS_NO_FRACT_OBJ                 ((EMS_RESULT)0x8004C101L)

//
// MessageId: EMS_FRACT_NO_DATA
//
// MessageText:
//
// No refraction data.
//
#define EMS_FRACT_NO_DATA                ((EMS_RESULT)0x8004C102L)


// *** EMSCAT_TLEServer = 0xC2 ***

//
// MessageId: EMSCAT_TLESERVER_BASE_CODE
//
// MessageText:
//
// TLE Server Errors
//
#define EMSCAT_TLESERVER_BASE_CODE       ((EMS_RESULT)0x8004C200L)

//
// MessageId: EMS_NO_TLEServer_OBJ
//
// MessageText:
//
// No TLE Server object.
//
#define EMS_NO_TLEServer_OBJ             ((EMS_RESULT)0x8004C201L)

//
// MessageId: EMS_TLEServer_NO_DATA1
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA1           ((EMS_RESULT)0x8004C202L)

//
// MessageId: EMS_TLEServer_NO_DATA2
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA2           ((EMS_RESULT)0x8004C203L)

//
// MessageId: EMS_TLEServer_NO_DATA3
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA3           ((EMS_RESULT)0x8004C204L)

//
// MessageId: EMS_TLEServer_NO_DATA4
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA4           ((EMS_RESULT)0x8004C205L)

//
// MessageId: EMS_TLEServer_NO_DATA5
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA5           ((EMS_RESULT)0x8004C206L)

//
// MessageId: EMS_TLEServer_NO_DATA6
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA6           ((EMS_RESULT)0x8004C207L)

//
// MessageId: EMS_TLEServer_NO_DATA7
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA7           ((EMS_RESULT)0x8004C208L)

//
// MessageId: EMS_TLEServer_NO_DATA8
//
// MessageText:
//
// TLE Server: No data
//
#define EMS_TLEServer_NO_DATA8           ((EMS_RESULT)0x8004C209L)


// *** EMSCAT_SIT = 0xEE ***

//
// MessageId: EMSCAT_SIT_BASE_CODE
//
// MessageText:
//
// SIT error messages.
//
#define EMSCAT_SIT_BASE_CODE             ((EMS_RESULT)0x8004EE00L)

//
// MessageId: EMS_SIT_UNKNOWN_CODE
//
// MessageText:
//
// SIT error: unknown code.
//
#define EMS_SIT_UNKNOWN_CODE             ((EMS_RESULT)0x8004EE01L)


#define EMS_UNKNOWN_SIT_CODE EMS_SIT_UNKNOWN_CODE

//
// MessageId: EMS_SIT_SYNTAX_ERROR
//
// MessageText:
//
// SIT error: syntax error.
//
#define EMS_SIT_SYNTAX_ERROR             ((EMS_RESULT)0x8004EE02L)

//
// MessageId: EMS_SIT_SYNTAX_EOL
//
// MessageText:
//
// SIT error: unexpected end of line.
//
#define EMS_SIT_SYNTAX_EOL               ((EMS_RESULT)0x8004EE03L)

//
// MessageId: EMS_SIT_UNKNOWN_TYPE
//
// MessageText:
//
// SIT error: unknown type.
//
#define EMS_SIT_UNKNOWN_TYPE             ((EMS_RESULT)0x8004EE04L)


#define EMS_UNKNOWN_SIT_TYPE EMS_SIT_UNKNOWN_TYPE

//
// MessageId: EMS_SIT_FIELD_COUNT_ERROR
//
// MessageText:
//
// SIT error: field count error.
//
#define EMS_SIT_FIELD_COUNT_ERROR        ((EMS_RESULT)0x8004EE05L)

//
// MessageId: EMS_SIT_ALERT_LIMIT
//
// MessageText:
//
// SIT error: alert limit reached.
//
#define EMS_SIT_ALERT_LIMIT              ((EMS_RESULT)0x8004EE06L)

//
// MessageId: EMS_SIT_MISSING_MSGHDR
//
// MessageText:
//
// SIT error: missing message header.
//
#define EMS_SIT_MISSING_MSGHDR           ((EMS_RESULT)0x8004EE07L)

//
// MessageId: EMS_SIT_LINE_EXCEEDED
//
// MessageText:
//
// SIT error: maximum line length exceeded.
//
#define EMS_SIT_LINE_EXCEEDED            ((EMS_RESULT)0x8004EE08L)

//
// MessageId: EMS_SIT_MSGSIZE_EXCEEDED
//
// MessageText:
//
// SIT error: maximum message length exceeded.
//
#define EMS_SIT_MSGSIZE_EXCEEDED         ((EMS_RESULT)0x8004EE09L)


// *** EMSCAT_LOGGER = 0xFC ***

//
// MessageId: EMSCAT_LOGGER_BASE_CODE
//
// MessageText:
//
// Logger Errors
//
#define EMSCAT_LOGGER_BASE_CODE          ((EMS_RESULT)0x8004FC00L)

//
// MessageId: EMS_NO_LOGGER_OBJ
//
// MessageText:
//
// No logger object
//
#define EMS_NO_LOGGER_OBJ                ((EMS_RESULT)0x8004FC01L)


// *** EMSCAT_SITEINFO = 0xFD ***

//
// MessageId: EMSCAT_SITEINFO_BASE_CODE
//
// MessageText:
//
// Site Info Errors
//
#define EMSCAT_SITEINFO_BASE_CODE        ((EMS_RESULT)0x8004FD00L)

//
// MessageId: EMS_NO_SITEINFO_OBJ
//
// MessageText:
//
// No site information object
//
#define EMS_NO_SITEINFO_OBJ              ((EMS_RESULT)0x8004FD01L)

//
// MessageId: EMS_NO_SITEINFO_DATA
//
// MessageText:
//
// No site information data
//
#define EMS_NO_SITEINFO_DATA             ((EMS_RESULT)0x8004FD02L)


// *** Standard Microsoft Errors (common identifier values) ***
//			EMS_NOINTERFACE = E_NOINTERFACE = 0x80004002
//			EMS_NOAGGREGATION = CLASS_E_NOAGGREGATION = 0x80040110
//			EMS_CLASSNOTAVAILABLE = CLASS_E_CLASSNOTAVAILABLE = 0x80040111

//
// MessageId: EMS_NOINTERFACE
//
// MessageText:
//
// No such interface supported.
//
#define EMS_NOINTERFACE                  ((EMS_RESULT)0x80004002L)

//
// MessageId: EMS_NOAGGREGATION
//
// MessageText:
//
// Class does not support aggregation (or class object is remote).
//
#define EMS_NOAGGREGATION                ((EMS_RESULT)0x80040110L)

//
// MessageId: EMS_CLASSNOTAVAILABLE
//
// MessageText:
//
// ClassFactory cannot supply requested class.
//
#define EMS_CLASSNOTAVAILABLE            ((EMS_RESULT)0x80040111L)


#endif
/********************************************************************
*	Module:			CalibrateErrorMsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Calibrate Errors
*
*					These errors were previously defined in a 
*					stand-alone CalibrateError.h file
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_CALIBRATEERROR
#define INC_CALIBRATEERROR

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

// *** EMSCAT_CALIBRATE ***

//
// MessageId: EMSCAT_CALIBRATE_BASE_CODE
//
// MessageText:
//
// Calibrate error messages.
//
#define EMSCAT_CALIBRATE_BASE_CODE       ((EMS_RESULT)0x80049100L)

//
// MessageId: EMS_CALIBRATE_MEMORYALLOC_ERROR
//
// MessageText:
//
// An out of memory error has been detected.
//
#define EMS_CALIBRATE_MEMORYALLOC_ERROR  ((EMS_RESULT)0x80049101L)

//
// MessageId: EMS_CALIBRATE_FILE_ERROR
//
// MessageText:
//
// Problem opening file.
//
#define EMS_CALIBRATE_FILE_ERROR         ((EMS_RESULT)0x80049102L)

//
// MessageId: EMS_CALIBRATE_READ_ERROR
//
// MessageText:
//
// Problem reading file.
//
#define EMS_CALIBRATE_READ_ERROR         ((EMS_RESULT)0x80049103L)

//
// MessageId: EMS_CALIBRATE_NO_DATA
//
// MessageText:
//
// No locate data information has been initialized.
//
#define EMS_CALIBRATE_NO_DATA            ((EMS_RESULT)0x80049104L)

//
// MessageId: EMS_CALIBRATE_IE_NON_CONVERGE
//
// MessageText:
//
// IE fails to converge.
//
#define EMS_CALIBRATE_IE_NON_CONVERGE    ((EMS_RESULT)0x80049105L)

//
// MessageId: EMS_CALIBRATE_CN_NON_CONVERGE
//
// MessageText:
//
// Converge fails to converge.
//
#define EMS_CALIBRATE_CN_NON_CONVERGE    ((EMS_RESULT)0x80049106L)

//
// MessageId: EMS_CALIBRATE_TCA_OUTOFBOUNDS
//
// MessageText:
//
// TCA out of bounds.
//
#define EMS_CALIBRATE_TCA_OUTOFBOUNDS    ((EMS_RESULT)0x80049107L)

//
// MessageId: EMS_CALIBRATE_SOLVE_ERROR
//
// MessageText:
//
// Solve error.
//
#define EMS_CALIBRATE_SOLVE_ERROR        ((EMS_RESULT)0x80049108L)

//
// MessageId: EMS_CALIBRATE_NO_POINTS
//
// MessageText:
//
// No points.
//
#define EMS_CALIBRATE_NO_POINTS          ((EMS_RESULT)0x80049109L)

//
// MessageId: EMS_CALIBRATE_WLS_NON_CONVERGE
//
// MessageText:
//
// WLS fails to converge.
//
#define EMS_CALIBRATE_WLS_NON_CONVERGE   ((EMS_RESULT)0x8004910AL)

//
// MessageId: EMS_CALIBRATE_WRITING_ERROR
//
// MessageText:
//
// Problem writing file.
//
#define EMS_CALIBRATE_WRITING_ERROR      ((EMS_RESULT)0x8004910BL)

//
// MessageId: EMS_CALIBRATE_INDEX_ERROR
//
// MessageText:
//
// Calibration index error.
//
#define EMS_CALIBRATE_INDEX_ERROR        ((EMS_RESULT)0x8004910CL)

//
// MessageId: EMS_CALIBRATE_INPUT_DATA_ERROR
//
// MessageText:
//
// Calibration input data error.
//
#define EMS_CALIBRATE_INPUT_DATA_ERROR   ((EMS_RESULT)0x8004910DL)

//
// MessageId: EMS_CALIBRATE_BEACON_ID_ERROR
//
// MessageText:
//
// Beacon id error.
//
#define EMS_CALIBRATE_BEACON_ID_ERROR    ((EMS_RESULT)0x8004910EL)


#endif
/********************************************************************
*	Module:			AudioMonitorMsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Audio Monitor Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_AUDIOMONITORMSG
#define INC_AUDIOMONITORMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_AUDIOMONITOR_BASE_CODE
//
// MessageText:
//
// EMS Audio Monitor Error
//
#define EMS_AUDIOMONITOR_BASE_CODE       ((EMS_RESULT)0x8004C700L)

//
// MessageId: EMS_AUDIOMONITOR_UNKNOWN_ERROR
//
// MessageText:
//
// EMS Audio Monitor reports that an error has occurred.  The error code is <%1>.
//
#define EMS_AUDIOMONITOR_UNKNOWN_ERROR   ((EMS_RESULT)0x8004C701L)

//
// MessageId: EMS_AUDIOMONITOR_TITLE
//
// MessageText:
//
// EMS Audio Monitor
//
#define EMS_AUDIOMONITOR_TITLE           ((EMS_RESULT)0x4004C702L)

//
// MessageId: EMS_AUDIOMONITOR_TOOLBAR_ERROR
//
// MessageText:
//
// EMS Audio Monitor failed to create toolbar.
//
#define EMS_AUDIOMONITOR_TOOLBAR_ERROR   ((EMS_RESULT)0x8004C703L)

//
// MessageId: EMS_AUDIOMONITOR_CONFIG_ERROR
//
// MessageText:
//
// EMS Audio Monitor Configuration error. The error code is <%1>.
//
#define EMS_AUDIOMONITOR_CONFIG_ERROR    ((EMS_RESULT)0x8004C704L)

//
// MessageId: EMS_AUDIOMONITOR_AUDSTREAM_ERROR
//
// MessageText:
//
// EMS Audio Monitor Creating Audio Stream error. The error code is <%1>.
//
#define EMS_AUDIOMONITOR_AUDSTREAM_ERROR ((EMS_RESULT)0x8004C705L)

//
// MessageId: EMS_AM_AUDIOPLAYER_ERROR
//
// MessageText:
//
// EMS Audio Monitor Can't create NCTAudioPlayer2 control. The error code is <%1>.
//
#define EMS_AM_AUDIOPLAYER_ERROR         ((EMS_RESULT)0x8004C706L)

//
// MessageId: EMS_AM_AUDIOVISUALISATION_ERROR
//
// MessageText:
//
// EMS Audio Monitor Can't create NCTAudioVisualisation control. The error code is <%1>.
//
#define EMS_AM_AUDIOVISUALISATION_ERROR  ((EMS_RESULT)0x8004C707L)

//
// MessageId: EMS_AM_AUDIOFILE_ERROR
//
// MessageText:
//
// EMS Audio Monitor Can't create NCTAudioFile control. The error code is <%1>.
//
#define EMS_AM_AUDIOFILE_ERROR           ((EMS_RESULT)0x8004C708L)

//
// MessageId: EMS_AM_BANDWIDTHOUT_ERROR
//
// MessageText:
//
// EMS Audio Monitor error The bandwith range is 1 to 4 KHz.
//
#define EMS_AM_BANDWIDTHOUT_ERROR        ((EMS_RESULT)0x8004C709L)

//
// MessageId: EMS_AM_FREQUENCYOUT_ERROR
//
// MessageText:
//
// EMS Audio Monitor error The center frequency is out of range.
//
#define EMS_AM_FREQUENCYOUT_ERROR        ((EMS_RESULT)0x8004C70AL)

//
// MessageId: EMS_AUDIOMONITOR_NODATA
//
// MessageText:
//
// No data found
//
#define EMS_AUDIOMONITOR_NODATA          ((EMS_RESULT)0x8004C70BL)


#endif
/********************************************************************
*	Module:			MapServerMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Map Server Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_MAPSERVERMSG
#define INC_MAPSERVERMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_MAP_SERVER_BASE_CODE
//
// MessageText:
//
// EMS Map Server error.
//
#define EMS_MAP_SERVER_BASE_CODE         ((EMS_RESULT)0x8004CA00L)

//
// MessageId: EMS_MAP_SERVER_SESSION_NOT_FOUND
//
// MessageText:
//
// EMS Map Server:  Session with identifier <%1> could not be retrieved from the Session Manager.
//
#define EMS_MAP_SERVER_SESSION_NOT_FOUND ((EMS_RESULT)0x8004CA01L)

//
// MessageId: EMS_MAP_SERVER_MAPX_NO_PARENT_WINDOW
//
// MessageText:
//
// EMS Map Server:  Could not create a MapX object because no parent window was specified.
//
#define EMS_MAP_SERVER_MAPX_NO_PARENT_WINDOW ((EMS_RESULT)0x8004CA02L)

//
// MessageId: EMS_MAP_SERVER_MAPX_EXCEPTION
//
// MessageText:
//
// EMS Map Server:  An exception was thrown by the MapX component.  The error code is <%1> and description is <%2>.
//
#define EMS_MAP_SERVER_MAPX_EXCEPTION    ((EMS_RESULT)0x8004CA03L)

//
// MessageId: EMS_MAP_SERVER_MAPX_UNSUPPORTED_CONTAINED_TYPE
//
// MessageText:
//
// EMS Map Server:  A request was made to return a map object as an unsupported type.
//
#define EMS_MAP_SERVER_MAPX_UNSUPPORTED_CONTAINED_TYPE ((EMS_RESULT)0x8004CA04L)

//
// MessageId: EMS_MAP_SERVER_MAPX_UNSUPPORTED_FEATURE_TYPE
//
// MessageText:
//
// EMS Map Server:  An attempt to use an unsupported feature type has occurred.
//
#define EMS_MAP_SERVER_MAPX_UNSUPPORTED_FEATURE_TYPE ((EMS_RESULT)0x8004CA05L)

//
// MessageId: EMS_MAP_SERVER_NO_MAPX_LICENSE
//
// MessageText:
//
// EMS Map Server:  Could not retrieve the license key for the MapX component.
//
#define EMS_MAP_SERVER_NO_MAPX_LICENSE   ((EMS_RESULT)0x8004CA06L)

//
// MessageId: EMS_MAP_SERVER_MAPX_CREATE_FAILED
//
// MessageText:
//
// EMS Map Server:  Failed to create an instance of the MapX component.
//
#define EMS_MAP_SERVER_MAPX_CREATE_FAILED ((EMS_RESULT)0x8004CA07L)

//
// MessageId: EMS_MAP_SERVER_INVALID_PARTS
//
// MessageText:
//
// EMS Map Server:  A part within a feature does not have enough points for the feature type.  It has %1 point(s), but requires a minimum of %2 point(s).
//
#define EMS_MAP_SERVER_INVALID_PARTS     ((EMS_RESULT)0x8004CA08L)


#endif
/********************************************************************
*	Module:			SolutionDisplayMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Solution Display Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_SOLNDISPMSG
#define INC_SOLNDISPMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_VIEW_MANAGER_BASE_CODE
//
// MessageText:
//
// EMS View Manager.
//
#define EMS_VIEW_MANAGER_BASE_CODE       ((EMS_RESULT)0x8004CB00L)

//
// MessageId: EMS_VIEWMGR_VIEWS_FORMAT_INVALID
//
// MessageText:
//
// EMS View Manager reports that the Views configuration is invalid.
//
#define EMS_VIEWMGR_VIEWS_FORMAT_INVALID ((EMS_RESULT)0x8004CB01L)

//
// MessageId: EMS_VIEWMGR_VIEWS_LOAD_FAILURE
//
// MessageText:
//
// An error occurred loading views from file <%1>.
//
#define EMS_VIEWMGR_VIEWS_LOAD_FAILURE   ((EMS_RESULT)0x8004CB02L)

//
// MessageId: EMS_VIEWMGR_VIEWS_LOAD_NO_CHILD_FAILURE
//
// MessageText:
//
// An error occurred attempting to retrieve the first child node of a loaded Views configuration.
//
#define EMS_VIEWMGR_VIEWS_LOAD_NO_CHILD_FAILURE ((EMS_RESULT)0x8004CB03L)

//
// MessageId: EMS_VIEWMGR_VIEW_LOAD_FAILURE
//
// MessageText:
//
// An error occurred attempting to load an XML view string into the DOM.
//
#define EMS_VIEWMGR_VIEW_LOAD_FAILURE    ((EMS_RESULT)0x8004CB04L)

//
// MessageId: EMS_VIEWMGR_VIEW_NOT_FOUND
//
// MessageText:
//
// An error occurred attempting to retrieve the view named <%1>.  It could not be found in the list of available views.
//
#define EMS_VIEWMGR_VIEW_NOT_FOUND       ((EMS_RESULT)0x8004CB05L)

//
// MessageId: EMS_VIEWMGR_VIEW_ALREADY_EXISTS
//
// MessageText:
//
// An error occurred attempting to create a new view named <%1>.  A view of this name already exists.
//
#define EMS_VIEWMGR_VIEW_ALREADY_EXISTS  ((EMS_RESULT)0x8004CB06L)


#endif
/********************************************************************
*	Module:			SocketMsg.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Socket Service Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003 Apr 1		RVW	

********************************************************************/
#ifndef INC_SOCKETMSG
#define INC_SOCKETMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SOCKET_BASE_CODE
//
// MessageText:
//
// EMSSocketService Error
//
#define EMS_SOCKET_BASE_CODE             ((EMS_RESULT)0x8004E000L)

//
// MessageId: EMS_SOCKET_SERVICE_START
//
// MessageText:
//
// EMSSocketService Started
//
#define EMS_SOCKET_SERVICE_START         ((EMS_RESULT)0x0004E001L)

//
// MessageId: EMS_SOCKET_SERVICE_FAILED
//
// MessageText:
//
// EMSSocketService did not start due to error %1
//
#define EMS_SOCKET_SERVICE_FAILED        ((EMS_RESULT)0x0004E002L)

//
// MessageId: EMS_SOCKET_SERVICE_STOP
//
// MessageText:
//
// EMSSocketService Stopped
//
#define EMS_SOCKET_SERVICE_STOP          ((EMS_RESULT)0x0004E003L)

//
// MessageId: EMS_SOCKET_ERROR
//
// MessageText:
//
// EMSSocketService reports error %1.
//
#define EMS_SOCKET_ERROR                 ((EMS_RESULT)0xC004E004L)

//
// MessageId: EMS_SOCKET_LOG_EXCEPTION
//
// MessageText:
//
// EMSSocketService reports an exception
//
#define EMS_SOCKET_LOG_EXCEPTION         ((EMS_RESULT)0xC004E005L)

//
// MessageId: EMS_SOCKET_TRACER
//
// MessageText:
//
// EMSSocketService tracer ( %1 ).
//
#define EMS_SOCKET_TRACER                ((EMS_RESULT)0x0004E006L)

//
// MessageId: EMS_SOCKET_NAK
//
// MessageText:
//
// EMSSocketService reports a NAK.
//
#define EMS_SOCKET_NAK                   ((EMS_RESULT)0x8004E007L)

//
// MessageId: EMS_SOCKET_NONE_READY
//
// MessageText:
//
// EMSSocketService reports no sockets ready.
//
#define EMS_SOCKET_NONE_READY            ((EMS_RESULT)0x8004E008L)

//
// MessageId: EMS_SOCKET_NOT_INITIALIZED
//
// MessageText:
//
// EMSSocketService reports sockets not initialized.
//
#define EMS_SOCKET_NOT_INITIALIZED       ((EMS_RESULT)0xC004E009L)

//
// MessageId: EMS_SOCKET_UNKNOWN_ERROR
//
// MessageText:
//
// EMSSocketService reports socket error (%1).
//
#define EMS_SOCKET_UNKNOWN_ERROR         ((EMS_RESULT)0xC004E00AL)

//
// MessageId: EMS_SOCKET_NO_CONNECTION
//
// MessageText:
//
// EMSSocketService reports socket connection unavailable.
//
#define EMS_SOCKET_NO_CONNECTION         ((EMS_RESULT)0xC004E00BL)

//
// MessageId: EMS_SOCKET_CONFIG
//
// MessageText:
//
// EMSSocketService { cfg: %1 }
//
#define EMS_SOCKET_CONFIG                ((EMS_RESULT)0x0004E00CL)

//
// MessageId: EMS_SOCKET_MSG_SENT
//
// MessageText:
//
// EMSSocketService sent msg ( %1 ).
//
#define EMS_SOCKET_MSG_SENT              ((EMS_RESULT)0x0004E00DL)

//
// MessageId: EMS_SOCKET_MSG_ERR
//
// MessageText:
//
// EMSSocketService reports error sending msg ( %1 ).
//
#define EMS_SOCKET_MSG_ERR               ((EMS_RESULT)0x0004E00EL)

//
// MessageId: EMS_SOCKET_MULTISIT_ERR
//
// MessageText:
//
// EMSSocketService recv'd an unexpected MultiSIT message ( %1 ).
//
#define EMS_SOCKET_MULTISIT_ERR          ((EMS_RESULT)0xC004E00FL)

//
// MessageId: EMS_SOCKET_BADSIT_ERR
//
// MessageText:
//
// EMSSocketService recv'd an unknown SIT message ( %1 ).
//
#define EMS_SOCKET_BADSIT_ERR            ((EMS_RESULT)0xC004E010L)

//
// MessageId: EMS_SOCKET_SIT_SUPPRESS
//
// MessageText:
//
// EMSSocketService suppressed SIT message ( %1 ).
//
#define EMS_SOCKET_SIT_SUPPRESS          ((EMS_RESULT)0x0004E011L)

//
// MessageId: EMS_SOCKET_EVENT_CREATE_ERR
//
// MessageText:
//
// EMSSocketService failed to initialize event handles.
//
#define EMS_SOCKET_EVENT_CREATE_ERR      ((EMS_RESULT)0x8004E012L)

//
// MessageId: EMS_SOCKET_WAIT_ERR
//
// MessageText:
//
// EMSSocketService processing loop wait failed with error ( %1 ).
//
#define EMS_SOCKET_WAIT_ERR              ((EMS_RESULT)0x8004E013L)


#endif // INC_SOCKETMSG
/********************************************************************
*	Module:			SolutionDisplayServerMessages.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Solution Display Server Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_SOLNDISPSERVERMSG
#define INC_SOLNDISPSERVERMSG

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SOLN_DISP_SERV_BASE_CODE
//
// MessageText:
//
// EMS Solution Display Server error.
//
#define EMS_SOLN_DISP_SERV_BASE_CODE     ((EMS_RESULT)0x8004CD00L)

//
// MessageId: EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the satellite layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_SAT ((EMS_RESULT)0x8004CD01L)

//
// MessageId: EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the satellite layer.
//
#define EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_SAT ((EMS_RESULT)0x8004CD02L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_TRACK_COL_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the colour for the satellite track while generating the satellite layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_TRACK_COL_FAIL_SAT ((EMS_RESULT)0x8004CD03L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the satellite layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_SAT ((EMS_RESULT)0x8004CD04L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the configuration for satellite <%1> in order to extract data filters for the satellite layer.  
//
#define EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_SAT ((EMS_RESULT)0x8004CD05L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the Solution Display configuration interface while generating the satellite layer.  A NULL pointer was returned.  
//
#define EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_SAT ((EMS_RESULT)0x8004CD06L)

//
// MessageId: EMS_SOLN_DISP_SERVER_INIT_SAT_TRACK_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred initializing the satellite track calculation object while generating the satellite layer.  The returned error code is <%1>.
//
#define EMS_SOLN_DISP_SERVER_INIT_SAT_TRACK_FAIL_SAT ((EMS_RESULT)0x8004CD07L)

//
// MessageId: EMS_SOLN_DISP_SERVER_CALCULATE_SAT_TRACK_FAIL_SAT
//
// MessageText:
//
// Solution Display Server:  An error occurred running the satellite track calculation object to generate the satellite layer.  The returned error code is <%1>.
//
#define EMS_SOLN_DISP_SERVER_CALCULATE_SAT_TRACK_FAIL_SAT ((EMS_RESULT)0x8004CD08L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the configuration for beacon type <%1> in order to generate data for the beacon layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_BEA ((EMS_RESULT)0x8004CD09L)

//
// MessageId: EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the beacon layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_BEA ((EMS_RESULT)0x8004CD0AL)

//
// MessageId: EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the beacon layer.
//
#define EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_BEA ((EMS_RESULT)0x8004CD0BL)

//
// MessageId: EMS_SOLN_DISP_SERVER_POINT_ADD_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to add a point to a points collection object while generating the beacon layer.
//
#define EMS_SOLN_DISP_SERVER_POINT_ADD_FAIL_BEA ((EMS_RESULT)0x8004CD0CL)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the beacon layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_BEA ((EMS_RESULT)0x8004CD0DL)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_BITMAP_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the symbol bitmap configuration for beacon type <%1> while generating the beacon layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_BITMAP_FAIL_BEA ((EMS_RESULT)0x8004CD0EL)

//
// MessageId: EMS_SOLN_DISP_NO_BEACON_TYPE_BEA
//
// MessageText:
//
// An error has occurred.  No beacon type was specified in a request to display solutions.
//
#define EMS_SOLN_DISP_NO_BEACON_TYPE_BEA ((EMS_RESULT)0x8004CD0FL)

//
// MessageId: EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE_BEA
//
// MessageText:
//
// An error has occurred.  An unrecognized beacon type was specified, <%1>.
//
#define EMS_SOLN_DISP_UNRECOGNIZED_BEACON_TYPE_BEA ((EMS_RESULT)0x8004CD10L)

//
// MessageId: EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve a parts object from a feature while generating the mutual visibility layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_NO_PARTS_FROM_FEATURE_MVIS ((EMS_RESULT)0x8004CD11L)

//
// MessageId: EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to add a points collection to a parts object while generating the mutual visibility layer.
//
#define EMS_SOLN_DISP_SERVER_POINTS_ADD_FAIL_MVIS ((EMS_RESULT)0x8004CD12L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the style from a feature object while generating the mutual visibility layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_STYLE_FAIL_MVIS ((EMS_RESULT)0x8004CD13L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the configuration for LUT <%1> while generating the mutual visibility layer.  
//
#define EMS_SOLN_DISP_SERVER_GET_SATELLITE_CONFIG_FAIL_MVIS ((EMS_RESULT)0x8004CD14L)

//
// MessageId: EMS_SOLN_DISP_SERVER_INIT_CALC_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred initializing the mutual visibility calculation object while generating the mutual visibility layer.  The returned error code is <%1>.
//
#define EMS_SOLN_DISP_SERVER_INIT_CALC_FAIL_MVIS ((EMS_RESULT)0x8004CD15L)

//
// MessageId: EMS_SOLN_DISP_SERVER_CALCULATE_MVIS_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred running the mutual visibility calculation object to generate the mutual visibilty layer.  The returned error code is <%1>.
//
#define EMS_SOLN_DISP_SERVER_CALCULATE_MVIS_FAIL_MVIS ((EMS_RESULT)0x8004CD16L)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_CONFIG_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the configuration for LUT <%1> in order to extract data filters for the mutual visibility layer.  
//
#define EMS_SOLN_DISP_SERVER_GET_CONFIG_FAIL_MVIS ((EMS_RESULT)0x8004CD17L)

//
// MessageId: EMS_SOLN_DISP_STATIC_MODE_NO_TIME_CRITERIA
//
// MessageText:
//
// Solution Display Server:  Static update mode was chosen but no filter criteria were specified.
//
#define EMS_SOLN_DISP_STATIC_MODE_NO_TIME_CRITERIA ((EMS_RESULT)0x8004CD18L)

//
// MessageId: EMS_SOLN_DISP_UNRECOGNIZED_TIME_CRITERIA_TYPE
//
// MessageText:
//
// Solution Display Server:  An error has occurred.  An unrecognized time criteria type was specified, <%1>.
//
#define EMS_SOLN_DISP_UNRECOGNIZED_TIME_CRITERIA_TYPE ((EMS_RESULT)0x8004CD19L)

//
// MessageId: EMS_SOLN_DISP_UNRECOGNIZED_UPDATE_MODE
//
// MessageText:
//
// Solution Display Server:  An error has occurred.  An unrecognized update mode was specified, <%1>.
//
#define EMS_SOLN_DISP_UNRECOGNIZED_UPDATE_MODE ((EMS_RESULT)0x8004CD1AL)

//
// MessageId: EMS_SOLN_DISP_SAT_TRACK_NOT_FOUND
//
// MessageText:
//
// Solution Display Server:  An error has occurred.  A satellite track record could not be found for satellite <%1> with pass identifier <%2>.
//
#define EMS_SOLN_DISP_SAT_TRACK_NOT_FOUND ((EMS_RESULT)0x8004CD1BL)

//
// MessageId: EMS_SOLN_DISP_TLE_SELECT_NO_SATID
//
// MessageText:
//
// Solution Display Server:  An error has occurred.  Dynamic data calculator attempting to retrieve a TLE, but no satellite identifier was provided.
//
#define EMS_SOLN_DISP_TLE_SELECT_NO_SATID ((EMS_RESULT)0x8004CD1CL)

//
// MessageId: EMS_SOLN_DISP_BAD_BEACON_CRITERIA
//
// MessageText:
//
// Solution Display Server:  The dataset selection critiera specified for beacon type <%1> do not include any timestamp or other filter conditions.  A query cannot be run without criteria.
//
#define EMS_SOLN_DISP_BAD_BEACON_CRITERIA ((EMS_RESULT)0x8004CD1DL)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_REGION_COL_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the colour for the mutual visibility region while generating the mutual visibility layer.  A NULL pointer was returned.
//
#define EMS_SOLN_DISP_SERVER_GET_REGION_COL_FAIL_MVIS ((EMS_RESULT)0x8004CD1EL)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_MVIS
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the Solution Display configuration interface while generating the mutual visibility layer.  A NULL pointer was returned.  
//
#define EMS_SOLN_DISP_SERVER_GET_CONFIG_PTR_FAIL_MVIS ((EMS_RESULT)0x8004CD1FL)

//
// MessageId: EMS_SOLN_DISP_SERVER_GET_SOLN_PROC_TIME_FAIL_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve the solution processing time for satellite <%1>, pass <%2>, LUT <%3>.
//
#define EMS_SOLN_DISP_SERVER_GET_SOLN_PROC_TIME_FAIL_BEA ((EMS_RESULT)0x8004CD20L)

//
// MessageId: EMS_SOLN_DISP_SERVER_INSUFFICIENT_CRITERIA_BEA
//
// MessageText:
//
// Solution Display Server:  An error occurred attempting to retrieve data for the beacon layer in static mode.  Insufficient criteria were specified.  At minimum, either a time range or a pass specified by satellite ID and pass ID must be included in the criteria.
//
#define EMS_SOLN_DISP_SERVER_INSUFFICIENT_CRITERIA_BEA ((EMS_RESULT)0x8004CD21L)

//
// MessageId: EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_MVIS
//
// MessageText:
//
// Solution Display Server:  While generating the mutual visibility layer, unable to find pass summary data for LUT <%1>.
//
#define EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_MVIS ((EMS_RESULT)0x8004CD22L)

//
// MessageId: EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_LUT
//
// MessageText:
//
// Solution Display Server:  While generating the LUT visibility layer, unable to find pass summary data for LUT <%1>.
//
#define EMS_SOLN_DISP_SERVER_NO_LAST_PASS_DATA_LUT ((EMS_RESULT)0x8004CD23L)


#endif
/********************************************************************
*	Module:			AlertFilterMsgs.mc
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Alert Filter Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	2005/11/15		rvw	start

********************************************************************/
#ifndef INC_ALERTFILTERMSGS
#define INC_ALERTFILTERMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ALERTFILTER_BASE_CODE
//
// MessageText:
//
// EMS Alert Filter Base Code
//
#define EMS_ALERTFILTER_BASE_CODE        ((EMS_RESULT)0x8004CF00L)

//
// MessageId: EMS_ALERTFILTER_UNKNOWN_REASON
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) for an unknown reason.
//
#define EMS_ALERTFILTER_UNKNOWN_REASON   ((EMS_RESULT)0x8004CF01L)

//
// MessageId: EMS_ALERTFILTER_INVALID_COUNTRY_CODE
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid country code.
//
#define EMS_ALERTFILTER_INVALID_COUNTRY_CODE ((EMS_RESULT)0x8004CF02L)

//
// MessageId: EMS_ALERTFILTER_SINGLE_PDF1_ERROR_LIMIT
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) with a single message and uncorrectable PDF1 errors
//
#define EMS_ALERTFILTER_SINGLE_PDF1_ERROR_LIMIT ((EMS_RESULT)0x8004CF03L)

//
// MessageId: EMS_ALERTFILTER_UNLOCATED_CBC121
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated CBC 121.
//
#define EMS_ALERTFILTER_UNLOCATED_CBC121 ((EMS_RESULT)0x8004CF04L)

//
// MessageId: EMS_ALERTFILTER_UNLOCATED_CBC243
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated CBC 243.
//
#define EMS_ALERTFILTER_UNLOCATED_CBC243 ((EMS_RESULT)0x8004CF05L)

//
// MessageId: EMS_ALERTFILTER_UNLOCATED_CBC406
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated interferer.
//
#define EMS_ALERTFILTER_UNLOCATED_CBC406 ((EMS_RESULT)0x8004CF06L)

//
// MessageId: EMS_ALERTFILTER_LOCATED_CBC121
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located CBC 121.
//
#define EMS_ALERTFILTER_LOCATED_CBC121   ((EMS_RESULT)0x8004CF07L)

//
// MessageId: EMS_ALERTFILTER_LOCATED_CBC243
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located CBC 243.
//
#define EMS_ALERTFILTER_LOCATED_CBC243   ((EMS_RESULT)0x8004CF08L)

//
// MessageId: EMS_ALERTFILTER_LOCATED_CBC406
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located interferer.
//
#define EMS_ALERTFILTER_LOCATED_CBC406   ((EMS_RESULT)0x8004CF09L)

//
// MessageId: EMS_ALERTFILTER_ORBITOGRAPHY_BEACON
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Orbitography beacon.
//
#define EMS_ALERTFILTER_ORBITOGRAPHY_BEACON ((EMS_RESULT)0x8004CF0AL)

//
// MessageId: EMS_ALERTFILTER_REFERENCE_BEACON
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Reference Beacon.
//
#define EMS_ALERTFILTER_REFERENCE_BEACON ((EMS_RESULT)0x8004CF0BL)

//
// MessageId: EMS_ALERTFILTER_TEST_BEACON
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to Test encoding.
//
#define EMS_ALERTFILTER_TEST_BEACON      ((EMS_RESULT)0x8004CF0CL)

//
// MessageId: EMS_ALERTFILTER_INVERTEDFS_BEACON
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to inverted frame sync.
//
#define EMS_ALERTFILTER_INVERTEDFS_BEACON ((EMS_RESULT)0x8004CF0DL)

//
// MessageId: EMS_ALERTFILTER_LEOGEO_OUTOFSPEC
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to out of spec LEO/GEO
//
#define EMS_ALERTFILTER_LEOGEO_OUTOFSPEC ((EMS_RESULT)0x8004CF0EL)

//
// MessageId: EMS_ALERTFILTER_LEOGEO_UNLOCATED
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated LEO/GEO
//
#define EMS_ALERTFILTER_LEOGEO_UNLOCATED ((EMS_RESULT)0x8004CF0FL)

//
// MessageId: EMS_ALERTFILTER_LEOGEO_LOCATED
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located LEO/GEO
//
#define EMS_ALERTFILTER_LEOGEO_LOCATED   ((EMS_RESULT)0x8004CF10L)

//
// MessageId: EMS_ALERTFILTER_UNLOCATED_SARP
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated SARP.
//
#define EMS_ALERTFILTER_UNLOCATED_SARP   ((EMS_RESULT)0x8004CF11L)

//
// MessageId: EMS_ALERTFILTER_LOCATED_SARP
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located SARP.
//
#define EMS_ALERTFILTER_LOCATED_SARP     ((EMS_RESULT)0x8004CF12L)

//
// MessageId: EMS_ALERTFILTER_UNLOCATED_SARR
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to unlocated SARR.
//
#define EMS_ALERTFILTER_UNLOCATED_SARR   ((EMS_RESULT)0x8004CF13L)

//
// MessageId: EMS_ALERTFILTER_LOCATED_SARR
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to located SARR.
//
#define EMS_ALERTFILTER_LOCATED_SARR     ((EMS_RESULT)0x8004CF14L)

//
// MessageId: EMS_ALERTFILTER_INVALID_ENCODING
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid encoding.
//
#define EMS_ALERTFILTER_INVALID_ENCODING ((EMS_RESULT)0x8004CF15L)

//
// MessageId: EMS_ALERTFILTER_STANDARD_BEACON
//
// MessageText:
//
// EMS Alert Filter suppressed Beacon: %1, Dest: %2 (as configured).
//
#define EMS_ALERTFILTER_STANDARD_BEACON  ((EMS_RESULT)0x8004CF16L)

//
// MessageId: EMS_ALERTFILTER_TOO_MANY_BIT_ERRORS
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) because of too many bit errors.
//
#define EMS_ALERTFILTER_TOO_MANY_BIT_ERRORS ((EMS_RESULT)0x8004CF17L)

//
// MessageId: EMS_ALERTFILTER_SUPPRESSNORMAL
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) as normal
//
#define EMS_ALERTFILTER_SUPPRESSNORMAL   ((EMS_RESULT)0x8004CF18L)

//
// MessageId: EMS_ALERTFILTER_COUNTRYCODE
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to country code.
//
#define EMS_ALERTFILTER_COUNTRYCODE      ((EMS_RESULT)0x8004CF19L)

//
// MessageId: EMS_ALERTFILTER_RESERVED
//
// MessageText:
//
// EMS Alert Filter suppressed as configured (Beacon: %1, Dest: %2).
//
#define EMS_ALERTFILTER_RESERVED         ((EMS_RESULT)0x8004CF1AL)

//
// MessageId: EMS_ALERTFILTER_INVALID_FIXED_BITS
//
// MessageText:
//
// EMS Alert Filter suppressed (Beacon: %1, Dest: %2) due to invalid location fixed bits.
//
#define EMS_ALERTFILTER_INVALID_FIXED_BITS ((EMS_RESULT)0x8004CF1BL)

#endif // INC_ALERTFILTERMSGS
/********************************************************************
*	Module:			LocnAnalMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS Location Analysis Processor 
*				Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	2005/11/21		rvw	start

********************************************************************/
#ifndef INC_LOCNANALMSGS
#define INC_LOCNANALMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_LOCN_ANAL_BASE_CODE
//
// MessageText:
//
// EMS Locn Analysis
//
#define EMS_LOCN_ANAL_BASE_CODE          ((EMS_RESULT)0x8004EF00L)

//
// MessageId: EMS_LOCN_ANAL_SERVICE_START
//
// MessageText:
//
// EMS Locn Analysis Service Started
//
#define EMS_LOCN_ANAL_SERVICE_START      ((EMS_RESULT)0x0004EF01L)

//
// MessageId: EMS_LOCN_ANAL_SERVICE_STOP
//
// MessageText:
//
// EMS Locn Analysis Service Stopped
//
#define EMS_LOCN_ANAL_SERVICE_STOP       ((EMS_RESULT)0x0004EF02L)

//
// MessageId: EMS_LOCN_ANAL_SERVICE_FAILED
//
// MessageText:
//
// EMS Locn Analysis Service did not start due to error %1
//
#define EMS_LOCN_ANAL_SERVICE_FAILED     ((EMS_RESULT)0xC004EF03L)

//
// MessageId: EMS_LOCN_ANAL_ACCURACY_CHECK_FAILURE
//
// MessageText:
//
// EMS Locn Analysis Service reports reference beacon %1 location (lat:%3 lon: %4) is %2 km different from expected.
//
#define EMS_LOCN_ANAL_ACCURACY_CHECK_FAILURE ((EMS_RESULT)0x8004EF04L)

//
// MessageId: EMS_LOCN_ANAL_NOM_UPDATE
//
// MessageText:
//
// EMS Locn Analysis Service updated Sat %1 nominal %2 (%3).
//
#define EMS_LOCN_ANAL_NOM_UPDATE         ((EMS_RESULT)0x0004EF05L)

//
// MessageId: EMS_LOCN_ANAL_MARG_UPDATE
//
// MessageText:
//
// EMS Locn Analysis Service updated Sat %1 marginal %2 (%3).
//
#define EMS_LOCN_ANAL_MARG_UPDATE        ((EMS_RESULT)0x0004EF06L)

//
// MessageId: EMS_LOCN_ANAL_NEW_SARR_OFFSETS
//
// MessageText:
//
// EMS Locn Analysis Service updated SARR Offsets ( SatID=%1, Freq=%2, Drift=%3, Time=%4 ).
//
#define EMS_LOCN_ANAL_NEW_SARR_OFFSETS   ((EMS_RESULT)0x0004EF07L)


#endif // INC_LOCNANALMSGS
/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_WSMSGS
#define INC_WSMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_WS_BASE_CODE
//
// MessageText:
//
// EMS Web Service host error.
//
#define EMS_WS_BASE_CODE                 ((EMS_RESULT)0x0004E100L)

//
// MessageId: EMS_WS_HOST_STARTED
//
// MessageText:
//
// EMS Web Service (%1) has started.
//
#define EMS_WS_HOST_STARTED              ((EMS_RESULT)0x0004E101L)

//
// MessageId: EMS_WS_HOST_START_FAILED
//
// MessageText:
//
// EMS Web Service (%1) failed to start with error code %2.
//
#define EMS_WS_HOST_START_FAILED         ((EMS_RESULT)0x8004E102L)

//
// MessageId: EMS_WS_HOST_STOPPED
//
// MessageText:
//
// EMS Web Service (%1) has stopped.
//
#define EMS_WS_HOST_STOPPED              ((EMS_RESULT)0x0004E103L)

//
// MessageId: EMS_WS_HOST_BIND_FAILURE
//
// MessageText:
//
// EMS Web Service host failed to bind.  Host=%1, Port=%2.
//
#define EMS_WS_HOST_BIND_FAILURE         ((EMS_RESULT)0x8004E104L)

//
// MessageId: EMS_WS_HOST_NO_WS_CONFIG
//
// MessageText:
//
// EMS Web Service host failed to find a web service plugin configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
//
#define EMS_WS_HOST_NO_WS_CONFIG         ((EMS_RESULT)0x8004E105L)

//
// MessageId: EMS_WS_PLUGIN_USER_NOT_FOUND
//
// MessageText:
//
// EMS Web Service (%1) could not find user (%2) in the access control list.
//
#define EMS_WS_PLUGIN_USER_NOT_FOUND     ((EMS_RESULT)0x8004E106L)

//
// MessageId: EMS_WS_PLUGIN_NO_USER
//
// MessageText:
//
// EMS Web Service (%1) did not find a username in a received SOAP message.  Authentication is enabled and usernames are required.
//
#define EMS_WS_PLUGIN_NO_USER            ((EMS_RESULT)0x8004E107L)

//
// MessageId: EMS_WS_PLUGIN_PWD_VERIF_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed to verify user (%2) with the supplied password.  The username or password is incorrect.
//
#define EMS_WS_PLUGIN_PWD_VERIF_FAILURE  ((EMS_RESULT)0x8004E108L)

//
// MessageId: EMS_WS_PLUGIN_NO_USERS_FILE
//
// MessageText:
//
// EMS Web Service (%1) could not load user account information while authenticating.  A user accounts file was not configured.
//
#define EMS_WS_PLUGIN_NO_USERS_FILE      ((EMS_RESULT)0x8004E109L)

//
// MessageId: EMS_WS_PLUGIN_NO_USERNAME
//
// MessageText:
//
// EMS Web Service (%1) encountered a missing username while loading the user accounts.
//
#define EMS_WS_PLUGIN_NO_USERNAME        ((EMS_RESULT)0x8004E10AL)

//
// MessageId: EMS_WS_HOST_CRYPTO_INIT_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to setup the cryptography thread for SSL support.
//
#define EMS_WS_HOST_CRYPTO_INIT_FAILURE  ((EMS_RESULT)0x8004E10BL)

//
// MessageId: EMS_WS_HOST_SSL_NO_KEY_FILE
//
// MessageText:
//
// EMS Web Service (%1) does not have a configured SSL key file.
//
#define EMS_WS_HOST_SSL_NO_KEY_FILE      ((EMS_RESULT)0x8004E10CL)

//
// MessageId: EMS_WS_HOST_SSL_NO_KEY_PWD
//
// MessageText:
//
// EMS Web Service (%1) does not have a configured SSL key file password.
//
#define EMS_WS_HOST_SSL_NO_KEY_PWD       ((EMS_RESULT)0x8004E10DL)

//
// MessageId: EMS_WS_HOST_SSL_CTX_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to set the SSL server context.
//
#define EMS_WS_HOST_SSL_CTX_FAILURE      ((EMS_RESULT)0x8004E10EL)

//
// MessageId: EMS_WS_HOST_ATTACH_OPEN_FAILURE
//
// MessageText:
//
// EMS Web Service (%1) failed attempting to open the file %2 for attachment to a respone message.
//
#define EMS_WS_HOST_ATTACH_OPEN_FAILURE  ((EMS_RESULT)0x8004E10FL)


#endif // INC_WSMSGS
/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_FP_WS_MSGS
#define INC_FP_WS_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_FP_WS_BASE_CODE
//
// MessageText:
//
// EMS FP Web Service error.
//
#define EMS_FP_WS_BASE_CODE              ((EMS_RESULT)0x8004E200L)

//
// MessageId: EMS_FP_WS_NO_CONFIGURATION
//
// MessageText:
//
// EMS FP Web Service had not been initialized with configuration.
//
#define EMS_FP_WS_NO_CONFIGURATION       ((EMS_RESULT)0x8004E201L)

//
// MessageId: EMS_FP_WS_NO_CLASSID
//
// MessageText:
//
// EMS FP Web Service could not find a plugin class ID in the supplied configuration.  The plugin cannot be loaded.
//
#define EMS_FP_WS_NO_CLASSID             ((EMS_RESULT)0x8004E202L)


#endif // INC_WSMSGS
/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_AC_ORBITAL_PROXY_MSGS
#define INC_AC_ORBITAL_PROXY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_AC_ORBITAL_PROXY_BASE_CODE
//
// MessageText:
//
// EMS Orbital Antenna Controller Proxy error.
//
#define EMS_AC_ORBITAL_PROXY_BASE_CODE   ((EMS_RESULT)0x8004E300L)

//
// MessageId: EMS_AC_ORBITAL_PROXY_AC_CALL_FAILURE
//
// MessageText:
//
// EMS Orbital Antenna Controller Proxy reports an error calling the antenna controller.  The error code is %1 and error message is "%2".
//
#define EMS_AC_ORBITAL_PROXY_AC_CALL_FAILURE ((EMS_RESULT)0x8004E301L)

//
// MessageId: EMS_AC_ORBITAL_PROXY_NO_URL
//
// MessageText:
//
// EMS Orbital Antenna Controller Proxy reports that an endpoint URL was not specified.
//
#define EMS_AC_ORBITAL_PROXY_NO_URL      ((EMS_RESULT)0x8004E302L)

//
// MessageId: EMS_AC_ORBITAL_POXY_CREATE_INSTANCE_ERR_HR
//
// MessageText:
//
// EMS Orbital Antenna Controller Proxy: Unable to create instance of %1 during initialization (Error=%2).
//
#define EMS_AC_ORBITAL_POXY_CREATE_INSTANCE_ERR_HR ((EMS_RESULT)0x8004E303L)

//
// MessageId: EMS_AC_ORBITAL_POXY_UPDATE_ANTENNA_INFO_FAILED
//
// MessageText:
//
// EMS Orbital Antenna Controller Proxy: Unable to update antenna status info (Error=%1).
//
#define EMS_AC_ORBITAL_POXY_UPDATE_ANTENNA_INFO_FAILED ((EMS_RESULT)0x8004E304L)


#endif // INC_AC_ORBITAL_PROXY_MSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_DC_PROXY_MSGS
#define INC_DC_PROXY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_DC_PROXY_BASE_CODE
//
// MessageText:
//
// EMS Data Collector Proxy error.
//
#define EMS_DC_PROXY_BASE_CODE           ((EMS_RESULT)0x8004E400L)

//
// MessageId: EMS_DC_PROXY_CALL_FAILURE
//
// MessageText:
//
// EMS Data Collector Proxy reports an error calling the data collector.  The error code is %1 and error message is "%2".
//
#define EMS_DC_PROXY_CALL_FAILURE        ((EMS_RESULT)0x8004E401L)

//
// MessageId: EMS_DC_PROXY_NO_URL
//
// MessageText:
//
// EMS Data Collector Proxy reports that an endpoint URL was not specified.
//
#define EMS_DC_PROXY_NO_URL              ((EMS_RESULT)0x8004E402L)


#endif // INC_DC_PROXY_MSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_FP_PROXY_MSGS
#define INC_FP_PROXY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_FP_PROXY_BASE_CODE
//
// MessageText:
//
// EMS Front End Processor (FP) Proxy error.
//
#define EMS_FP_PROXY_BASE_CODE           ((EMS_RESULT)0x8004E500L)

//
// MessageId: EMS_FP_PROXY_AC_CALL_FAILURE
//
// MessageText:
//
// EMS FP Proxy reports an error calling the Front End Processor.  The error code is %1 and error message is "%2".
//
#define EMS_FP_PROXY_AC_CALL_FAILURE     ((EMS_RESULT)0x8004E501L)

//
// MessageId: EMS_FP_PROXY_NO_URL
//
// MessageText:
//
// EMS FP Proxy reports that an endpoint URL was not specified.
//
#define EMS_FP_PROXY_NO_URL              ((EMS_RESULT)0x8004E502L)


#endif // INC_FP_PROXY_MSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_FP_MSGS
#define INC_FP_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_FP_BASE_CODE
//
// MessageText:
//
// EMS FP error.
//
#define EMS_FP_BASE_CODE                 ((EMS_RESULT)0x8004E600L)

//
// MessageId: EMS_FP_NO_SCHEDULE_FOLDER
//
// MessageText:
//
// A directory from which to load FP schedules was not configured.
//
#define EMS_FP_NO_SCHEDULE_FOLDER        ((EMS_RESULT)0x8004E601L)

//
// MessageId: EMS_FP_SET_SCHED_INVALID_PAIR_ID
//
// MessageText:
//
// An attempt was made to input a pass schedule with a pair identifier not configured on the FP.  The pair identifier used was %1.
//
#define EMS_FP_SET_SCHED_INVALID_PAIR_ID ((EMS_RESULT)0x8004E602L)

//
// MessageId: EMS_FP_NO_DS_PROXY_CLASSID
//
// MessageText:
//
// The proxy class for a datastream proxy could not be loaded because no class identifier was found in the configuration for pair identifier %1.
//
#define EMS_FP_NO_DS_PROXY_CLASSID       ((EMS_RESULT)0x8004E603L)

//
// MessageId: EMS_FP_NO_ANTENNA_PROXY_CLASSID
//
// MessageText:
//
// The proxy class for a antenna controller proxy could not be loaded because no class identifier was found in the configuration for antenna identifier %1.
//
#define EMS_FP_NO_ANTENNA_PROXY_CLASSID  ((EMS_RESULT)0x8004E604L)

//
// MessageId: EMS_FP_RESTART_COMMAND_RECEIVED
//
// MessageText:
//
// A restart command was received.
//
#define EMS_FP_RESTART_COMMAND_RECEIVED  ((EMS_RESULT)0x0004E605L)

//
// MessageId: EMS_FP_REBOOT_COMMAND_RECEIVED
//
// MessageText:
//
// A reboot command was received.
//
#define EMS_FP_REBOOT_COMMAND_RECEIVED   ((EMS_RESULT)0x0004E606L)

//
// MessageId: EMS_FP_REBOOT_FORCE_COMMAND_RECEIVED
//
// MessageText:
//
// A forced reboot command was received.
//
#define EMS_FP_REBOOT_FORCE_COMMAND_RECEIVED ((EMS_RESULT)0x0004E607L)

//
// MessageId: EMS_FP_START_COMMAND_RECEIVED
//
// MessageText:
//
// A start command was received.
//
#define EMS_FP_START_COMMAND_RECEIVED    ((EMS_RESULT)0x0004E608L)

//
// MessageId: EMS_FP_STOP_COMMAND_RECEIVED
//
// MessageText:
//
// A stop command was received.
//
#define EMS_FP_STOP_COMMAND_RECEIVED     ((EMS_RESULT)0x0004E609L)

//
// MessageId: EMS_FP_SETSCHEDULE_COMMAND_RECEIVED
//
// MessageText:
//
// A new pass schedule was received for antenna/datastream pair %1.
//
#define EMS_FP_SETSCHEDULE_COMMAND_RECEIVED ((EMS_RESULT)0x0004E60AL)

//
// MessageId: EMS_FP_GETSCHEDULE_COMMAND_RECEIVED
//
// MessageText:
//
// A pass schedule retrieval command was received.
//
#define EMS_FP_GETSCHEDULE_COMMAND_RECEIVED ((EMS_RESULT)0x0004E60BL)

//
// MessageId: EMS_FP_GETLIST_COMMAND_RECEIVED
//
// MessageText:
//
// An antenna/datatstream pair listing retrieval command was received.
//
#define EMS_FP_GETLIST_COMMAND_RECEIVED  ((EMS_RESULT)0x0004E60CL)

//
// MessageId: EMS_FP_SETORBITS_COMMAND_RECEIVED
//
// MessageText:
//
// A set of orbit vectors was received.
//
#define EMS_FP_SETORBITS_COMMAND_RECEIVED ((EMS_RESULT)0x0004E60DL)

//
// MessageId: EMS_FP_GETORBITS_COMMAND_RECEIVED
//
// MessageText:
//
// A request for the current set of orbit vectors was received.
//
#define EMS_FP_GETORBITS_COMMAND_RECEIVED ((EMS_RESULT)0x0004E60EL)

//
// MessageId: EMS_FP_SETPROPERTY_COMMAND_RECEIVED
//
// MessageText:
//
// A new configuration setting for %1 was received.  The new value is %2.
//
#define EMS_FP_SETPROPERTY_COMMAND_RECEIVED ((EMS_RESULT)0x0004E60FL)

//
// MessageId: EMS_FP_GETPROPERTY_COMMAND_RECEIVED
//
// MessageText:
//
// A configuration setting request for %1 was received.
//
#define EMS_FP_GETPROPERTY_COMMAND_RECEIVED ((EMS_RESULT)0x0004E610L)

//
// MessageId: EMS_FP_SETCONFIG_COMMAND_RECEIVED
//
// MessageText:
//
// New configuration settings were received.
//
#define EMS_FP_SETCONFIG_COMMAND_RECEIVED ((EMS_RESULT)0x0004E611L)

//
// MessageId: EMS_FP_GETCONFIG_COMMAND_RECEIVED
//
// MessageText:
//
// A request for the current configuration settings were received.
//
#define EMS_FP_GETCONFIG_COMMAND_RECEIVED ((EMS_RESULT)0x0004E612L)

//
// MessageId: EMS_FP_ANT_SET_ORBITS_FAILED
//
// MessageText:
//
// An error (%1) occurred while attempting to send orbit vectors to antenna %2.
//
#define EMS_FP_ANT_SET_ORBITS_FAILED     ((EMS_RESULT)0x8004E613L)

//
// MessageId: EMS_FP_SCHEDULE_FOLDER_LOAD
//
// MessageText:
//
// Loading pass schedules from files found in directory %1.
//
#define EMS_FP_SCHEDULE_FOLDER_LOAD      ((EMS_RESULT)0x0004E614L)

//
// MessageId: EMS_FP_SCHEDULE_FILE_LOAD
//
// MessageText:
//
// Loading pass schedule from file %1.
//
#define EMS_FP_SCHEDULE_FILE_LOAD        ((EMS_RESULT)0x0004E615L)

//
// MessageId: EMS_FP_SCHEDULE_FOLDER_SAVE
//
// MessageText:
//
// Saving pass schedules to files in directory %1.
//
#define EMS_FP_SCHEDULE_FOLDER_SAVE      ((EMS_RESULT)0x0004E616L)

//
// MessageId: EMS_FP_SCHEDULE_FILE_SAVE
//
// MessageText:
//
// Saving pass schedule for antenna/datastream pair %1 to file %2.
//
#define EMS_FP_SCHEDULE_FILE_SAVE        ((EMS_RESULT)0x0004E617L)

//
// MessageId: EMS_FP_NO_LONGER_SCHEDULED
//
// MessageText:
//
// The active pass for satellite %1 is no longer in the schedule.
//
#define EMS_FP_NO_LONGER_SCHEDULED       ((EMS_RESULT)0x0004E618L)

//
// MessageId: EMS_FP_NO_LONGER_IN_PASS
//
// MessageText:
//
// The active pass for satellite %1 is over.
//
#define EMS_FP_NO_LONGER_IN_PASS         ((EMS_RESULT)0x0004E619L)

//
// MessageId: EMS_FP_STOP_COLLECTION
//
// MessageText:
//
// The command to stop data collection on A/D Board ID %1, channel %2 has been issued successfully.
//
#define EMS_FP_STOP_COLLECTION           ((EMS_RESULT)0x0004E61AL)

//
// MessageId: EMS_FP_STOP_TRACKING
//
// MessageText:
//
// The command to stop tracking with antenna %1 has been issued successfully.
//
#define EMS_FP_STOP_TRACKING             ((EMS_RESULT)0x0004E61BL)

//
// MessageId: EMS_FP_EXCEPTION_MAIN_THREAD
//
// MessageText:
//
// An unrecognized exception has occurred in the Front End processor controller's main processing thread.
//
#define EMS_FP_EXCEPTION_MAIN_THREAD     ((EMS_RESULT)0x8004E61CL)

//
// MessageId: EMS_FP_START_MAIN_THREAD
//
// MessageText:
//
// The Front End processor controller main processing thread has started.
//
#define EMS_FP_START_MAIN_THREAD         ((EMS_RESULT)0x0004E61DL)

//
// MessageId: EMS_FP_STOP_MAIN_THREAD
//
// MessageText:
//
// The Front End processor controller main processing thread has ended.
//
#define EMS_FP_STOP_MAIN_THREAD          ((EMS_RESULT)0x0004E61EL)

//
// MessageId: EMS_FP_CONTROLLER_SCHEDULE
//
// MessageText:
//
// The Front End processor controller has received a pass schedule.
//
#define EMS_FP_CONTROLLER_SCHEDULE       ((EMS_RESULT)0x0004E61FL)

//
// MessageId: EMS_FP_SCHEDULE_CHANGE
//
// MessageText:
//
// The currently active pass for pair ID %1 differs from current pass in schedule.  The active pass will be stopped.
//
#define EMS_FP_SCHEDULE_CHANGE           ((EMS_RESULT)0x0004E620L)

//
// MessageId: EMS_FP_SCHEDULE_NEW
//
// MessageText:
//
// A current pass has been found in the schedule for pair ID %1.  The pass will be started.
//
#define EMS_FP_SCHEDULE_NEW              ((EMS_RESULT)0x0004E621L)

//
// MessageId: EMS_FP_START_COLLECTION
//
// MessageText:
//
// The command to start data collection for satellite %1 on A/D Board ID %2, channel %3 has been issued successfully.
//
#define EMS_FP_START_COLLECTION          ((EMS_RESULT)0x0004E622L)

//
// MessageId: EMS_FP_START_TRACKING
//
// MessageText:
//
// The command to start tracking satellite %1 with antenna %2 has been issued successfully.
//
#define EMS_FP_START_TRACKING            ((EMS_RESULT)0x0004E623L)

//
// MessageId: EMS_FP_TRACK_RECORD_AUDIT
//
// MessageText:
//
// A pass schedule entry for pair %1 (antenna=%2,datastream=%3) has SatID = %4, Start=%5, End=%6.
//
#define EMS_FP_TRACK_RECORD_AUDIT        ((EMS_RESULT)0x0004E624L)

//
// MessageId: EMS_FP_IDLE_COMMAND_RECEIVED
//
// MessageText:
//
// An idle command was received.
//
#define EMS_FP_IDLE_COMMAND_RECEIVED     ((EMS_RESULT)0x0004E625L)

//
// MessageId: EMS_FP_STOW_CMD_SENT
//
// MessageText:
//
// Successfully sent STOW command to Antenna ID %1.
//
#define EMS_FP_STOW_CMD_SENT             ((EMS_RESULT)0x0004E626L)

//
// MessageId: EMS_FP_STOW_CMD_FAILED
//
// MessageText:
//
// Failure sending STOW command to Antenna ID %1.  Return code from antenna controller is %2.
//
#define EMS_FP_STOW_CMD_FAILED           ((EMS_RESULT)0x8004E627L)


#endif // INC_FP_MSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_ORBIT_DIST_MSGS
#define INC_ORBIT_DIST_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ORBIT_DIST_BASE_CODE
//
// MessageText:
//
// EMS Orbit Distributor error.
//
#define EMS_ORBIT_DIST_BASE_CODE         ((EMS_RESULT)0x8004E700L)

//
// MessageId: EMS_ORBIT_DIST_STARTED
//
// MessageText:
//
// EMS Orbit Distributor has started.
//
#define EMS_ORBIT_DIST_STARTED           ((EMS_RESULT)0x0004E701L)

//
// MessageId: EMS_ORBIT_DIST_START_FAILED
//
// MessageText:
//
// EMS Orbit Distributor failed to start with error code %1.
//
#define EMS_ORBIT_DIST_START_FAILED      ((EMS_RESULT)0x8004E702L)

//
// MessageId: EMS_ORBIT_DIST_STOPPED
//
// MessageText:
//
// EMS Orbit Distributor has stopped.
//
#define EMS_ORBIT_DIST_STOPPED           ((EMS_RESULT)0x0004E703L)

//
// MessageId: EMS_ORBIT_DIST_NO_CONFIG
//
// MessageText:
//
// EMS Orbit Distributor failed to to get configuration from ConfigWS for %1 Component.
//
#define EMS_ORBIT_DIST_NO_CONFIG         ((EMS_RESULT)0x8004E704L)

//
// MessageId: EMS_ORBIT_DIST_NO_SITE_INFO
//
// MessageText:
//
// EMS Orbit Distributor failed to create an instance of the site configuration object.
//
#define EMS_ORBIT_DIST_NO_SITE_INFO      ((EMS_RESULT)0x8004E705L)

//
// MessageId: EMS_ORBIT_DEST_NUM_SATS
//
// MessageText:
//
// EMS Orbit Distributor retrieved a list of %1 satellites from configuration.
//
#define EMS_ORBIT_DEST_NUM_SATS          ((EMS_RESULT)0x0004E706L)

//
// MessageId: EMS_ORBIT_DIST_NO_ORBIT
//
// MessageText:
//
// EMS Orbit Distributor failed to create an instance of the orbit object.
//
#define EMS_ORBIT_DIST_NO_ORBIT          ((EMS_RESULT)0x8004E707L)

//
// MessageId: EMS_ORBIT_DIST_ORBIT_RET_FAIL
//
// MessageText:
//
// EMS Orbit Distributor failed to retrieve orbit data for satellite %1.  Orbit object returned error code %2.
//
#define EMS_ORBIT_DIST_ORBIT_RET_FAIL    ((EMS_RESULT)0x8004E708L)

//
// MessageId: EMS_ORBIT_DIST_NO_SAT_MAPPING
//
// MessageText:
//
// EMS Orbit Distributor did not find the satellite ID to NORAD name mappings in the configuration file.
//
#define EMS_ORBIT_DIST_NO_SAT_MAPPING    ((EMS_RESULT)0x8004E709L)

//
// MessageId: EMS_ORBIT_DIST_OUT_FOLDER_AUDIT
//
// MessageText:
//
// EMS Orbit Distributor found an output folder in the configuration.  Path = %1, Data File = %2, Index File = %3.
//
#define EMS_ORBIT_DIST_OUT_FOLDER_AUDIT  ((EMS_RESULT)0x0004E70AL)

//
// MessageId: EMS_ORBIT_DIST_OUT_FOLDER_NO_FILE
//
// MessageText:
//
// EMS Orbit Distributor could not open a data file for writing.  The data file name was not found.
//
#define EMS_ORBIT_DIST_OUT_FOLDER_NO_FILE ((EMS_RESULT)0x8004E70BL)

//
// MessageId: EMS_ORBIT_DIST_OUT_FOLDER_NO_INDEX_FILE
//
// MessageText:
//
// EMS Orbit Distributor could not open a index file for writing.  The index file name was not found.
//
#define EMS_ORBIT_DIST_OUT_FOLDER_NO_INDEX_FILE ((EMS_RESULT)0x8004E70CL)

//
// MessageId: EMS_ORBIT_DIST_FILE_OPEN_FAIL
//
// MessageText:
//
// EMS Orbit Distributor could not open file %1 for writing.  OS error is %2.
//
#define EMS_ORBIT_DIST_FILE_OPEN_FAIL    ((EMS_RESULT)0x8004E70DL)

//
// MessageId: EMS_ORBIT_DIST_TLE_CONV_FAIL
//
// MessageText:
//
// EMS Orbit Distributor encountered error %1 while attempting to convert from EMSTLEDATA2 TO EMSTLERECORD formats.
//
#define EMS_ORBIT_DIST_TLE_CONV_FAIL     ((EMS_RESULT)0x8004E70EL)

//
// MessageId: EMS_ORBIT_DIST_TLE_SEND_FAIL
//
// MessageText:
//
// EMS Orbit Distributor encountered error %1 while attempting to send orbit data to a Front End Processor.
//
#define EMS_ORBIT_DIST_TLE_SEND_FAIL     ((EMS_RESULT)0x8004E70FL)

//
// MessageId: EMS_ORBIT_DIST_FP_PROXY_CREATE_FAIL
//
// MessageText:
//
// EMS Orbit Distributor encountered error %1 while attempting to create an instance of a Front End Processor proxy class.
//
#define EMS_ORBIT_DIST_FP_PROXY_CREATE_FAIL ((EMS_RESULT)0x8004E710L)

//
// MessageId: EMS_ORBIT_DIST_FILES_WRITTEN
//
// MessageText:
//
// EMS Orbit Distributor output orbit data to %1 and index %2.
//
#define EMS_ORBIT_DIST_FILES_WRITTEN     ((EMS_RESULT)0x0004E711L)

//
// MessageId: EMS_ORBIT_DIST_FP_OUTPUT
//
// MessageText:
//
// EMS Orbit Distributor output orbit data to FP with URL %1.
//
#define EMS_ORBIT_DIST_FP_OUTPUT         ((EMS_RESULT)0x0004E712L)


#endif // INC_ORBIT_DIST_MSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_PASS_SCHEDULER_MSGS
#define INC_PASS_SCHEDULER_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_PS_BASE_CODE
//
// MessageText:
//
// EMS Pass Scheduler error.
//
#define EMS_PS_BASE_CODE                 ((EMS_RESULT)0x0004E800L)

//
// MessageId: EMS_PS_STARTED
//
// MessageText:
//
// EMS Pass Scheduler has started.
//
#define EMS_PS_STARTED                   ((EMS_RESULT)0x0004E801L)

//
// MessageId: EMS_PS_START_FAILED
//
// MessageText:
//
// EMS Pass Scheduler failed to start with error code %1.
//
#define EMS_PS_START_FAILED              ((EMS_RESULT)0x8004E802L)

//
// MessageId: EMS_PS_STOPPED
//
// MessageText:
//
// EMS Pass Scheduler has stopped.
//
#define EMS_PS_STOPPED                   ((EMS_RESULT)0x0004E803L)

//
// MessageId: EMS_PS_NO_CONFIG
//
// MessageText:
//
// EMS Pass Scheduler failed to find a configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
//
#define EMS_PS_NO_CONFIG                 ((EMS_RESULT)0x8004E804L)

//
// MessageId: EMS_PS_RECS_RECEIVED
//
// MessageText:
//
// EMS Pass Scheduler has received satellite track records.
//
#define EMS_PS_RECS_RECEIVED             ((EMS_RESULT)0x0004E805L)

//
// MessageId: EMS_PS_RECS_SENT
//
// MessageText:
//
// EMS Pass Scheduler has sent %1 satellite track records to FP with URL %2.
//
#define EMS_PS_RECS_SENT                 ((EMS_RESULT)0x0004E806L)

//
// MessageId: EMS_PS_GET_FAILURE
//
// MessageText:
//
// EMS Pass Scheduler encountered error (%1) while attempting to retrieve the current schedule from FP (%2).
//
#define EMS_PS_GET_FAILURE               ((EMS_RESULT)0x8004E807L)

//
// MessageId: EMS_PS_NO_FP_CONFIG
//
// MessageText:
//
// EMS Pass Scheduler did not find a reference to an FP configuration file in the pass scheduler configuration.  As a result, the Pass Scheduler will not manage any FPs.
//
#define EMS_PS_NO_FP_CONFIG              ((EMS_RESULT)0x0004E808L)

//
// MessageId: EMS_FP_GETLIST_FAIL
//
// MessageText:
//
// EMS Pass Scheduler encountered error (%1) on call to FP (URL=%2) for its list of managed antennas.
//
#define EMS_FP_GETLIST_FAIL              ((EMS_RESULT)0x8004E809L)

//
// MessageId: EMS_FP_SETSCHEDULE_FAIL
//
// MessageText:
//
// EMS Pass Scheduler encountered error (%1) on call to FP (URL=%2) to set a schedule for antenna (%3).
//
#define EMS_FP_SETSCHEDULE_FAIL          ((EMS_RESULT)0x8004E80AL)

//
// MessageId: EMS_FP_SETSCHEDULE_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler successfully sent a pass schedule to FP (URL=%1) with (%2) passes for antenna (%3).
//
#define EMS_FP_SETSCHEDULE_SUCCEED       ((EMS_RESULT)0x0004E80BL)

//
// MessageId: EMS_FP_GETSCHEDULE_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler successfully received (%1) pass schedule records from FP (URL=%2) managing (%3) antennas.
//
#define EMS_FP_GETSCHEDULE_SUCCEED       ((EMS_RESULT)0x0004E80CL)

//
// MessageId: EMS_PS_SCHEDINIT_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler has initialized a scheduler with lutid = %1, autogenerate=%2, startup=%3, trackandscan=%4, duration=%5 hours, checkperiod=%6 minutes, pre-pass=%7 seconds, post-pass=%8 seconds.
//
#define EMS_PS_SCHEDINIT_SUCCEED         ((EMS_RESULT)0x0004E80DL)

//
// MessageId: EMS_PS_SCHEDINIT2_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler has initialized a scheduler with max_leo_duration=%1 minutes, max_geo_duration=%2 minutes, max_meo_duration=%3 minutes for satellites=(%4).
//
#define EMS_PS_SCHEDINIT2_SUCCEED        ((EMS_RESULT)0x0004E80EL)

//
// MessageId: EMS_PS_EXTERNAL_INSTALL_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler has installed a schedule that was received from an external source.
//
#define EMS_PS_EXTERNAL_INSTALL_SUCCEED  ((EMS_RESULT)0x0004E80FL)

//
// MessageId: EMS_PS_UPDATE_FROM_FPS_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler has initialized its managed schedule from FP(s) under its control.
//
#define EMS_PS_UPDATE_FROM_FPS_SUCCEED   ((EMS_RESULT)0x0004E810L)

//
// MessageId: EMS_PS_GENERATE_INSTALL_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler has generated a new schedule and installed it on the FP(s) under its control.
//
#define EMS_PS_GENERATE_INSTALL_SUCCEED  ((EMS_RESULT)0x0004E811L)

//
// MessageId: EMS_PS_INIT_OUTPUT_SUCCEED
//
// MessageText:
//
// EMS Pass Scheduler will output schedule listings to file:  (%1).
//
#define EMS_PS_INIT_OUTPUT_SUCCEED       ((EMS_RESULT)0x0004E812L)

//
// MessageId: EMS_PS_MAX_RECS_FAILURE
//
// MessageText:
//
// EMS Pass Scheduler has reached the maximum capacity (%1 satellite pass records) while generating a schedule.
//
#define EMS_PS_MAX_RECS_FAILURE          ((EMS_RESULT)0x8004E813L)

//
// MessageId: EMS_FP_MAX_RECS_WARN
//
// MessageText:
//
// EMS Pass Scheduler has retrieved an FP's pass schedule where the number of entries matches the maximum (%1) that the scheduler can handle.  The FP may actually have a schedule with more records than the scheduler can manage.
//
#define EMS_FP_MAX_RECS_WARN             ((EMS_RESULT)0x8004E814L)

//
// MessageId: EMS_PS_AUTOMATIC_COMMAND_EXECUTED
//
// MessageText:
//
// EMS Pass Scheduler has processed a command to enter into automatic scheduling mode.
//
#define EMS_PS_AUTOMATIC_COMMAND_EXECUTED ((EMS_RESULT)0x0004E815L)

//
// MessageId: EMS_PS_MANUAL_COMMAND_EXECUTED
//
// MessageText:
//
// EMS Pass Scheduler has processed a command to enter into manual scheduling mode.
//
#define EMS_PS_MANUAL_COMMAND_EXECUTED   ((EMS_RESULT)0x0004E816L)

//
// MessageId: EMS_PS_COMMAND_FAILED
//
// MessageText:
//
// EMS Pass Scheduler failed to process a command.
//
#define EMS_PS_COMMAND_FAILED            ((EMS_RESULT)0x8004E817L)

//
// MessageId: EMS_PS_COMMAND_FAILED2
//
// MessageText:
//
// EMS Pass Scheduler failed to process a command with error code %1.
//
#define EMS_PS_COMMAND_FAILED2           ((EMS_RESULT)0x8004E818L)

//
// MessageId: EMS_PS_AUTOMATIC_COMMAND_RECEIVED
//
// MessageText:
//
// EMS Pass Scheduler has received a command to enter into automatic scheduling mode.
//
#define EMS_PS_AUTOMATIC_COMMAND_RECEIVED ((EMS_RESULT)0x0004E819L)

//
// MessageId: EMS_PS_MANUAL_COMMAND_RECEIVED
//
// MessageText:
//
// EMS Pass Scheduler has received a command to enter into manual scheduling mode.
//
#define EMS_PS_MANUAL_COMMAND_RECEIVED   ((EMS_RESULT)0x0004E81AL)

//
// MessageId: EMS_PS_SETDURATION_COMMAND_RECEIVED
//
// MessageText:
//
// EMS Pass Scheduler has received a command to set the pass schedule duration to %1 days.
//
#define EMS_PS_SETDURATION_COMMAND_RECEIVED ((EMS_RESULT)0x0004E81BL)

//
// MessageId: EMS_PS_SETMINELEVATION_COMMAND_RECEIVED
//
// MessageText:
//
// EMS Pass Scheduler has received a command to set the minimum elevation angle for scheduled passes to %1 degrees.
//
#define EMS_PS_SETMINELEVATION_COMMAND_RECEIVED ((EMS_RESULT)0x0004E81CL)


#endif 
/********************************************************************
*	Module:			SATIDMsgs.mc 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for Satellite Identification's Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_SATIDMSGS
#define INC_SATIDMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_SATID_BASE_CODE
//
// MessageText:
//
// EMS Database Resource error.
//
#define EMS_SATID_BASE_CODE              ((EMS_RESULT)0x0004DE00L)

//
// MessageId: EMS_SATID_UNHANDLED_EXCEPTION_AT
//
// MessageText:
//
// EMS Satelite Identification captured an unknown exception on <%1>.
//
#define EMS_SATID_UNHANDLED_EXCEPTION_AT ((EMS_RESULT)0x8004DE01L)

//
// MessageId: EMS_SATID_SET_TEST_CONFIG
//
// MessageText:
//
// EMS Satelite Identification:  The test control file has been set to: "%1".  
//
#define EMS_SATID_SET_TEST_CONFIG        ((EMS_RESULT)0x4004DE02L)

//
// MessageId: EMS_SATID_NULL_INPUT
//
// MessageText:
//
// EMS Satelite Identification:  No input.
//
#define EMS_SATID_NULL_INPUT             ((EMS_RESULT)0x8004DE03L)

//
// MessageId: EMS_SATID_NULL_OUTPUT
//
// MessageText:
//
// EMS Satelite Identification:  No output. 
//
#define EMS_SATID_NULL_OUTPUT            ((EMS_RESULT)0x8004DE04L)

//
// MessageId: EMS_SATID_NULL_CONTROL_PARAM
//
// MessageText:
//
// EMS Satelite Identification:  No test control.
//
#define EMS_SATID_NULL_CONTROL_PARAM     ((EMS_RESULT)0x8004DE05L)

//
// MessageId: EMS_SATID_ERROR_LOADING_CONTROL_PARAM
//
// MessageText:
//
// EMS Satelite Identification:  An error occured during loading control parameters. 
//
#define EMS_SATID_ERROR_LOADING_CONTROL_PARAM ((EMS_RESULT)0x8004DE06L)

//
// MessageId: EMS_SATID_LOADED_XML_CONTROL_DATA
//
// MessageText:
//
// EMS Satelite Identification:  Control Data has been loaded from "%1". 
//
#define EMS_SATID_LOADED_XML_CONTROL_DATA ((EMS_RESULT)0x8004DE07L)

//
// MessageId: EMS_SATID_CONTROL_LOADED_INTO_XML_STRING
//
// MessageText:
//
// EMS Beacon Simulator: The control object has been loaded into XML = "%1".
//
#define EMS_SATID_CONTROL_LOADED_INTO_XML_STRING ((EMS_RESULT)0x8004DE08L)

//
// MessageId: EMS_SATID_ERROR_RUN_FAILURE
//
// MessageText:
//
// EMS Satelite Identification:   An error occured while the test is running. 
//
#define EMS_SATID_ERROR_RUN_FAILURE      ((EMS_RESULT)0x8004DE09L)

//
// MessageId: EMS_SATID_UNHANDLED_RUN_EXCEPTION
//
// MessageText:
//
// EMS Satelite Identification:  An error occured while the test is running. 
//
#define EMS_SATID_UNHANDLED_RUN_EXCEPTION ((EMS_RESULT)0x8004DE0AL)

//
// MessageId: EMS_SATID_COINIT_FAILED
//
// MessageText:
//
// EMS Satelite Identification: Coinitialize failed, hr = <%1>.
//
#define EMS_SATID_COINIT_FAILED          ((EMS_RESULT)0x8004DE0BL)

//
// MessageId: EMS_SATID_ENGINE_STARTED
//
// MessageText:
//
// EMS Satelite Identification: The Engine has started.
//
#define EMS_SATID_ENGINE_STARTED         ((EMS_RESULT)0x8004DE0CL)

//
// MessageId: EMS_SATID_ENGINE_PAUSED
//
// MessageText:
//
// EMS Satelite Identification: The engine has been paused. 
//
#define EMS_SATID_ENGINE_PAUSED          ((EMS_RESULT)0x4004DE0DL)

//
// MessageId: EMS_SATID_ENGINE_RESUMED
//
// MessageText:
//
// EMS Satelite Identification: The engine has been resumed. 
//
#define EMS_SATID_ENGINE_RESUMED         ((EMS_RESULT)0x4004DE0EL)

//
// MessageId: EMS_SATID_ENGINE_STOPPED
//
// MessageText:
//
// EMS Satelite Identification: The engine has been stopped. 
//
#define EMS_SATID_ENGINE_STOPPED         ((EMS_RESULT)0x4004DE0FL)

//
// MessageId: EMS_SATID_ERROR_DATAIN_SET_URL_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to SetURL, URL String <%1>, hr = <%2>. 
//
#define EMS_SATID_ERROR_DATAIN_SET_URL_FAILED ((EMS_RESULT)0x4004DE10L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_CREATE_DI_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to create instance of DataIO, hr = <%1>.
//
#define EMS_SATID_ERROR_DATAIN_CREATE_DI_FAILED ((EMS_RESULT)0x4004DE11L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_SET_MODE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to set open mode to read, hr = <%1>.
//
#define EMS_SATID_ERROR_DATAIN_SET_MODE_FAILED ((EMS_RESULT)0x8004DE12L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_SET_TRANS_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to set translation parameter, translation string is <%1>, hr <%2>.
//
#define EMS_SATID_ERROR_DATAIN_SET_TRANS_FAILED ((EMS_RESULT)0x4004DE13L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_SET_EVENT_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to set event name, event name is <%1>, hr <%2>.
//
#define EMS_SATID_ERROR_DATAIN_SET_EVENT_FAILED ((EMS_RESULT)0x4004DE14L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_IS_ACTIVE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn isActive() failed, hr <%1>
//
#define EMS_SATID_ERROR_DATAIN_IS_ACTIVE_FAILED ((EMS_RESULT)0x4004DE15L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_ACTIVATE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to activate DataIO, hr <%1>.
//
#define EMS_SATID_ERROR_DATAIN_ACTIVATE_FAILED ((EMS_RESULT)0x4004DE16L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_GET_STREAM_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to get data input stream, hr <%1>.
//
#define EMS_SATID_ERROR_DATAIN_GET_STREAM_FAILED ((EMS_RESULT)0x4004DE17L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_CREATE_EVENT_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataIn failed to create input event, hr <%1>.
//
#define EMS_SATID_ERROR_DATAIN_CREATE_EVENT_FAILED ((EMS_RESULT)0x4004DE18L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_GET_DATA
//
// MessageText:
//
// EMS Satelite Identification: DataIn error while retrieving data, hr <%1>.
//
#define EMS_SATID_ERROR_DATAIN_GET_DATA  ((EMS_RESULT)0x4004DE19L)

//
// MessageId: EMS_SATID_ERROR_DATAIN_NO_INPUT_STREAM
//
// MessageText:
//
// EMS Satelite Identification: DataIn no input stream.
//
#define EMS_SATID_ERROR_DATAIN_NO_INPUT_STREAM ((EMS_RESULT)0x4004DE1AL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_SET_URL_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to Set URL, URL string <1%>, hr <%2>
//
#define EMS_SATID_ERROR_DATAOUT_SET_URL_FAILED ((EMS_RESULT)0x4004DE1BL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_CREATE_DATAO_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to create instance of DataIO, hr = <%1>.
//
#define EMS_SATID_ERROR_DATAOUT_CREATE_DATAO_FAILED ((EMS_RESULT)0x8004DE1CL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_SET_MODE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to set open mode to write, hr = <%1>.
//
#define EMS_SATID_ERROR_DATAOUT_SET_MODE_FAILED ((EMS_RESULT)0x4004DE1DL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_SET_TRANS_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to set translation parameter, translation string is <%1>, hr <%2>
//
#define EMS_SATID_ERROR_DATAOUT_SET_TRANS_FAILED ((EMS_RESULT)0x4004DE1EL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_GET_STREAM_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to get data output stream, hr <%1>
//
#define EMS_SATID_ERROR_DATAOUT_GET_STREAM_FAILED ((EMS_RESULT)0x4004DE1FL)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_PATTERN_WRITE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to get data Pattern Data output stream, hr <%1>
//
#define EMS_SATID_ERROR_DATAOUT_PATTERN_WRITE_FAILED ((EMS_RESULT)0x4004DE20L)

//
// MessageId: EMS_SATID_ERROR_DATAOUT_PROB_WRITE_FAILED
//
// MessageText:
//
// EMS Satelite Identification: DataOut failed to get data Prob Data output stream, hr <%1>
//
#define EMS_SATID_ERROR_DATAOUT_PROB_WRITE_FAILED ((EMS_RESULT)0x4004DE21L)

//
// MessageId: EMS_SATID_ENGINE_OUTPUT_PATTERN_DATA
//
// MessageText:
//
// EMS Satelite Identification: The engine outputs Pattern Data to output stream. 
//
#define EMS_SATID_ENGINE_OUTPUT_PATTERN_DATA ((EMS_RESULT)0x4004DE22L)

//
// MessageId: EMS_SATID_GET_FROM_ORBIT_INTERFACE_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Visible Sat. List Configurator failed to get satellite's orbital vectors , hr <%1> 
//
#define EMS_SATID_GET_FROM_ORBIT_INTERFACE_ERROR ((EMS_RESULT)0x4004DE23L)

//
// MessageId: EMS_SATID_ORBIT_INTERFACE_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Unable to CoCreateInstance IEMSOrbit , hr <%1> 
//
#define EMS_SATID_ORBIT_INTERFACE_ERROR  ((EMS_RESULT)0x4004DE24L)

//
// MessageId: EMS_SATID_LUT_INFO_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Unable to CoCreateInstance instance LUTInfo , hr <%1> 
//
#define EMS_SATID_LUT_INFO_ERROR         ((EMS_RESULT)0x4004DE25L)

//
// MessageId: EMS_SATID_CALCULATE_RANGE_RATE
//
// MessageText:
//
// EMS Satelite Identification: Error in CEMSRangeRate::Calculate(), hr <%1> 
//
#define EMS_SATID_CALCULATE_RANGE_RATE   ((EMS_RESULT)0x4004DE26L)

//
// MessageId: EMS_SATID_DISPLAY_LUT_COORD
//
// MessageText:
//
// EMS Satelite Identification: Debug: Displays LUT Coordinates, hr <%1> 
//
#define EMS_SATID_DISPLAY_LUT_COORD      ((EMS_RESULT)0x4004DE27L)

//
// MessageId: EMS_SATID_FROM_LUT_INFO_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Error in lpLutInfo->GetSiteLocation, hr <%1> 
//
#define EMS_SATID_FROM_LUT_INFO_ERROR    ((EMS_RESULT)0x4004DE28L)

//
// MessageId: EMS_SATID_CALCULATED_DOPPLER_SHIFT_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Calculated Doppler Shift Out of Frequency Range 
//
#define EMS_SATID_CALCULATED_DOPPLER_SHIFT_ERROR ((EMS_RESULT)0x4004DE29L)

//
// MessageId: EMS_SATID_DOPPLER_FREQ_RANGE_IS_ZERO
//
// MessageText:
//
// EMS Satelite Identification: Error in the control parameter:Doppler Frequency Range is 0
//
#define EMS_SATID_DOPPLER_FREQ_RANGE_IS_ZERO ((EMS_RESULT)0x4004DE2AL)

//
// MessageId: EMS_SATID_SIGNAL_PROBABILITIES
//
// MessageText:
//
// EMS Satelite Identification: Debug: displays first, second and joint probability
//
#define EMS_SATID_SIGNAL_PROBABILITIES   ((EMS_RESULT)0x4004DE2BL)

//
// MessageId: EMS_SATID_CORRELATED_AND_CALCULATED_DOPPLER_SHIFT
//
// MessageText:
//
// EMS Satelite Identification: Debug: displays correlated and calculated Doppler shift
//
#define EMS_SATID_CORRELATED_AND_CALCULATED_DOPPLER_SHIFT ((EMS_RESULT)0x4004DE2CL)

//
// MessageId: EMS_SATID_ERROR_IN_READING_SAT_PATTERN_NO
//
// MessageText:
//
// EMS Satelite Identification: Error ir reading pattern from the Pattern File <%1>, hr <%2>
//
#define EMS_SATID_ERROR_IN_READING_SAT_PATTERN_NO ((EMS_RESULT)0x4004DE2DL)

//
// MessageId: EMS_SATID_DATAIN_INIT_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Error to initialize DataIn Object,  hr <%1>
//
#define EMS_SATID_DATAIN_INIT_ERROR      ((EMS_RESULT)0x4004DE2EL)

//
// MessageId: EMS_SATID_DATAOUT_INIT_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Error to initialize DataOut Object, hr <%1>
//
#define EMS_SATID_DATAOUT_INIT_ERROR     ((EMS_RESULT)0x4004DE2FL)

//
// MessageId: EMS_SATID_CONTROL_OBJ_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Control Obj does not exist, hr <%1>
//
#define EMS_SATID_CONTROL_OBJ_ERROR      ((EMS_RESULT)0x4004DE30L)

//
// MessageId: EMS_SATID_ERROR_IN_READING_ALL_SAT_PATTERNS
//
// MessageText:
//
// EMS Satelite Identification: Error ir reading ALL patterns from the Pattern Files, hr <%1>
//
#define EMS_SATID_ERROR_IN_READING_ALL_SAT_PATTERNS ((EMS_RESULT)0x4004DE31L)

//
// MessageId: EMS_SATID_ERROR_ADD_NEW_SIGNAL
//
// MessageText:
//
// EMS Satelite Identification: The Sat Signal Calibator Obj does not exist, hr <%1>
//
#define EMS_SATID_ERROR_ADD_NEW_SIGNAL   ((EMS_RESULT)0x4004DE32L)

//
// MessageId: EMS_SATID_ERROR_VALIDATE_SIGNAL
//
// MessageText:
//
// EMS Satelite Identification: The Sat Validator Obj does not exist, hr <%1>
//
#define EMS_SATID_ERROR_VALIDATE_SIGNAL  ((EMS_RESULT)0x4004DE33L)

//
// MessageId: EMS_SATID_PATTERN_ERROR
//
// MessageText:
//
// EMS Satelite Identification: There is NO PATTERN generated, hr <%1>
//
#define EMS_SATID_PATTERN_ERROR          ((EMS_RESULT)0x4004DE34L)

//
// MessageId: EMS_SATID_ERROR_IN_VALIDATION_SETUP
//
// MessageText:
//
// EMS Satelite Identification: Error is setup: no patterns and Control setup error
//
#define EMS_SATID_ERROR_IN_VALIDATION_SETUP ((EMS_RESULT)0x4004DE35L)

//
// MessageId: EMS_SATID_LOAD_PARTTERNS_ERROR
//
// MessageText:
//
// EMS Satelite Identification: It has be loadded less patterns than the visible satellites
//
#define EMS_SATID_LOAD_PARTTERNS_ERROR   ((EMS_RESULT)0x4004DE36L)

//
// MessageId: EMS_SATID_OUTPUT_PATTERN_ERROR
//
// MessageText:
//
// EMS Satelite Identification: Error in Output Pattern to the File, hr <%1>
//
#define EMS_SATID_OUTPUT_PATTERN_ERROR   ((EMS_RESULT)0x4004DE37L)

//
// MessageId: EMS_SATID_BESTMATCHPROB_AND_DOPPSHIFTPROB
//
// MessageText:
//
// EMS Satelite Identification: Debug: probabilities: bestmatch nad doppshift, prob1 <%1>, prob2 <%2>
//
#define EMS_SATID_BESTMATCHPROB_AND_DOPPSHIFTPROB ((EMS_RESULT)0x4004DE38L)

//
// MessageId: EMS_SATID_ANGLE_AND_COS_ANGLE
//
// MessageText:
//
// EMS Satelite Identification: Debug: angle and Cos(angle), angle <%1>, cos(angle) <%2>
//
#define EMS_SATID_ANGLE_AND_COS_ANGLE    ((EMS_RESULT)0x4004DE39L)


#endif
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_BR_WS_MSGS
#define INC_BR_WS_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_BR_WS_BASE_CODE
//
// MessageText:
//
// EMS Beacon Registry Web Service error.
//
#define EMS_BR_WS_BASE_CODE              ((EMS_RESULT)0x4004E900L)

//
// MessageId: EMS_BR_WS_NO_CONFIGURATION
//
// MessageText:
//
// EMS Beacon Registry Web Service has not been initialized with configuration.
//
#define EMS_BR_WS_NO_CONFIGURATION       ((EMS_RESULT)0x8004E901L)

//
// MessageId: EMS_BR_WS_NO_CLASSID
//
// MessageText:
//
// EMS Beacon Registry Web Service could not find a plugin class ID in the supplied configuration.  The plugin cannot be loaded.
//
#define EMS_BR_WS_NO_CLASSID             ((EMS_RESULT)0x8004E902L)

//
// MessageId: EMS_BR_WS_EXCEPTION
//
// MessageText:
//
// EMS Beacon Registry Web Service reporting an internal exception - %1.
//
#define EMS_BR_WS_EXCEPTION              ((EMS_RESULT)0x8004E903L)


#endif // INC_WSMSGS
/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_BRENGINE_MSGS
#define INC_BRENGINE_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_BRENGINE_BASE_CODE
//
// MessageText:
//
// EMS Beacon Registry Engine error.
//
#define EMS_BRENGINE_BASE_CODE           ((EMS_RESULT)0x8004EA00L)

//
// MessageId: EMS_BR_ENGINE_DBINSERT
//
// MessageText:
//
// EMS Beacon Registry:  Successfully inserted new record for beacon %1.
//
#define EMS_BR_ENGINE_DBINSERT           ((EMS_RESULT)0x0004EA01L)

//
// MessageId: EMS_BR_ENGINE_DBINSERT_ERRORS
//
// MessageText:
//
// EMS Beacon Registry: Errors encountered while performing inserts. Check server log for details.
//
#define EMS_BR_ENGINE_DBINSERT_ERRORS    ((EMS_RESULT)0x8004EA02L)

//
// MessageId: EMS_BR_ENGINE_DBINSERT_FAIL
//
// MessageText:
//
// EMS Beacon Registry:  Successfully deleted record for beacon %1.
//
#define EMS_BR_ENGINE_DBINSERT_FAIL      ((EMS_RESULT)0x0004EA03L)

//
// MessageId: EMS_BR_ENGINE_DBUPDATE
//
// MessageText:
//
// EMS Beacon Registry:  Successfully updated record for beacon %1.
//
#define EMS_BR_ENGINE_DBUPDATE           ((EMS_RESULT)0x0004EA04L)

//
// MessageId: EMS_BR_ENGINE_DBDELETE
//
// MessageText:
//
// EMS Beacon Registry:  Successfully deleted record for beacon %1.
//
#define EMS_BR_ENGINE_DBDELETE           ((EMS_RESULT)0x0004EA05L)


#endif // INC_WSMSGS
/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_BD_MSGS
#define INC_BD_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_BD_BASE_CODE
//
// MessageText:
//
// EMS Beacon Registry Web Service error.
//
#define EMS_BD_BASE_CODE                 ((EMS_RESULT)0x0004EC00L)

//
// MessageId: EMS_BDC_MISSING_REGISTRY
//
// MessageText:
//
// EMS Beacon Decoder Client: Connection information for web service was not found in the registry.
//
#define EMS_BDC_MISSING_REGISTRY         ((EMS_RESULT)0x8004EC01L)

//
// MessageId: EMS_BDC_GETIDERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to retrieve beacon ID from web service. (%1)
//
#define EMS_BDC_GETIDERROR               ((EMS_RESULT)0x8004EC02L)

//
// MessageId: EMS_BDC_GETLOCERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to retrieve encoded location from web service. (%1)
//
#define EMS_BDC_GETLOCERROR              ((EMS_RESULT)0x8004EC03L)

//
// MessageId: EMS_BDC_GETTYPEERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to retrieve beacon type from web service. (%1)
//
#define EMS_BDC_GETTYPEERROR             ((EMS_RESULT)0x8004EC04L)

//
// MessageId: EMS_BDC_SETCONNERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to set the web service connection config. (%1)
//
#define EMS_BDC_SETCONNERROR             ((EMS_RESULT)0x8004EC05L)

//
// MessageId: EMS_BDC_SETURLERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to set the web service connection URL.  (%1)
//
#define EMS_BDC_SETURLERROR              ((EMS_RESULT)0x8004EC06L)

//
// MessageId: EMS_BDC_SETUSERERROR
//
// MessageText:
//
// EMS Beacon Decoder Client: failed to set the web service connection user. (%1)
//
#define EMS_BDC_SETUSERERROR             ((EMS_RESULT)0x8004EC07L)

//
// MessageId: EMS_BDC_SETPWDERROR
//
// MessageText:
//
// BeaconDecoder failed to set the web service connection password. (%1)
//
#define EMS_BDC_SETPWDERROR              ((EMS_RESULT)0x8004EC08L)


#endif // INC_WSMSGS
/********************************************************************
*	Module:			ABLMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for ABL Messages
*
*	Usage: 
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2002-2007 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	2002 Oct 8		rvw	start 

********************************************************************/
#ifndef INC_ABLMSGS
#define INC_ABLMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_ABL_BASE_CODE
//
// MessageText:
//
// EMS Active Beacon List Object Error
//
#define EMS_ABL_BASE_CODE                ((EMS_RESULT)0x8004ED00L)

//
// MessageId: EMS_ABL_UNKNOWN_EXCEPT
//
// MessageText:
//
// EMS Active Beacon List Object reports an unknown exception
//
#define EMS_ABL_UNKNOWN_EXCEPT           ((EMS_RESULT)0x8004ED01L)

//
// MessageId: EMS_ABL_UNHANDLED_EXCEPTION_AT
//
// MessageText:
//
// EMS Active Beacon List Object reports an unknown exception on %1.
//
#define EMS_ABL_UNHANDLED_EXCEPTION_AT   ((EMS_RESULT)0x8004ED02L)

//
// MessageId: EMS_ABL_NO_CONFIG_FILE
//
// MessageText:
//
// EMS Active Beacon List Object: no configuration file.
//
#define EMS_ABL_NO_CONFIG_FILE           ((EMS_RESULT)0x8004ED03L)

//
// MessageId: EMS_ABL_MEM_OVERFLOW
//
// MessageText:
//
// EMS Active Beacon List Object reports a memory overflow.
//
#define EMS_ABL_MEM_OVERFLOW             ((EMS_RESULT)0x8004ED04L)

//
// MessageId: EMS_ABL_NO_LOCATION_UPDATE
//
// MessageText:
//
// EMS Active Beacon List Object reports no location updates at this time.
//
#define EMS_ABL_NO_LOCATION_UPDATE       ((EMS_RESULT)0x8004ED05L)

//
// MessageId: EMS_ABL_MAX_CAP
//
// MessageText:
//
// EMS Active Beacon List Object reached the maximum configured number of raw input records.
//
#define EMS_ABL_MAX_CAP                  ((EMS_RESULT)0x8004ED06L)


#endif
/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_BEACONSNMP_MSGS
#define INC_BEACONSNMP_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_BEACONSNMP_BASE_CODE
//
// MessageText:
//
// EMS Beacon SNMP Agent error.
//
#define EMS_BEACONSNMP_BASE_CODE         ((EMS_RESULT)0x8004E350L)

//
// MessageId: EMS_BEACONSNMP_PORTUNINITIALIZED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Cannot communicate with the beacon.  The port has not been initialized.
//
#define EMS_BEACONSNMP_PORTUNINITIALIZED ((EMS_RESULT)0x8004E351L)

//
// MessageId: EMS_BEACONSNMP_BADRESPONSE
//
// MessageText:
//
// EMS Beacon SNMP Agent: Cannot interpret the response read from the beacon port.
//
#define EMS_BEACONSNMP_BADRESPONSE       ((EMS_RESULT)0x8004E352L)

//
// MessageId: EMS_BEACONSNMP_ONREQ
//
// MessageText:
//
// EMS Beacon SNMP Agent: Received request to turn beacon on.
//
#define EMS_BEACONSNMP_ONREQ             ((EMS_RESULT)0x0004E353L)

//
// MessageId: EMS_BEACONSNMP_OFFREQ
//
// MessageText:
//
// EMS Beacon SNMP Agent: Received request to turn beacon off.
//
#define EMS_BEACONSNMP_OFFREQ            ((EMS_RESULT)0x0004E354L)

//
// MessageId: EMS_BEACONSNMP_ONFAILED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Request to turn on the beacon failed.
//
#define EMS_BEACONSNMP_ONFAILED          ((EMS_RESULT)0x8004E355L)

//
// MessageId: EMS_BEACONSNMP_OFFFAILED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Request to turn off the beacon failed.
//
#define EMS_BEACONSNMP_OFFFAILED         ((EMS_RESULT)0x8004E356L)

//
// MessageId: EMS_BEACONSNMP_UNHANDLEDREFRESHEXCEPTION
//
// MessageText:
//
// EMS Beacon SNMP Agent: Unhandled exception while refreshing beacon information
//
#define EMS_BEACONSNMP_UNHANDLEDREFRESHEXCEPTION ((EMS_RESULT)0x8004E357L)

//
// MessageId: EMS_BEACONSNMP_CURRENTSETTINGS
//
// MessageText:
//
// EMS Beacon SNMP Agent: Beacon = %1, Message = <%2>
//
#define EMS_BEACONSNMP_CURRENTSETTINGS   ((EMS_RESULT)0x0004E358L)

//
// MessageId: EMS_BEACONSNMP_SUPPORTUNAVAILABLE
//
// MessageText:
//
// EMS Beacon SNMP Agent: SNMP Agent support not available.
//
#define EMS_BEACONSNMP_SUPPORTUNAVAILABLE ((EMS_RESULT)0x8004E359L)

//
// MessageId: EMS_BEACONSNMP_SERVICESTARTED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Started
//
#define EMS_BEACONSNMP_SERVICESTARTED    ((EMS_RESULT)0x0004E35AL)

//
// MessageId: EMS_BEACONSNMP_SERVICESTOPPED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Stopped
//
#define EMS_BEACONSNMP_SERVICESTOPPED    ((EMS_RESULT)0x0004E35BL)

//
// MessageId: EMS_BEACONSNMP_UNHANDLEDINITEXCEPTION
//
// MessageText:
//
// EMS Beacon SNMP Agent: Unhandled exception while initializing
//
#define EMS_BEACONSNMP_UNHANDLEDINITEXCEPTION ((EMS_RESULT)0x8004E35CL)

//
// MessageId: EMS_BEACONSNMP_MIBCOMPILEERROR
//
// MessageText:
//
// EMS Beacon SNMP Agent: Failed to compile MIB files.
//
#define EMS_BEACONSNMP_MIBCOMPILEERROR   ((EMS_RESULT)0x8004E35DL)

//
// MessageId: EMS_BEACONSNMP_PORTOPENFAILED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Failed to open port %1. Confirm there is no conflict.
//
#define EMS_BEACONSNMP_PORTOPENFAILED    ((EMS_RESULT)0x8004E35EL)

//
// MessageId: EMS_BEACONSNMP_BEACONINITFAILED
//
// MessageText:
//
// EMS Beacon SNMP Agent: Failed to initialize reference to beacon component.
//
#define EMS_BEACONSNMP_BEACONINITFAILED  ((EMS_RESULT)0x8004E35FL)


#endif // INC_BEACONSNMP_MSGS
/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_OCC_PROXY_MSGS
#define INC_OCC_PROXY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_OCC_PROXY_BASE_CODE
//
// MessageText:
//
// OCC Proxy error.
//
#define EMS_OCC_PROXY_BASE_CODE          ((EMS_RESULT)0x8004F000L)

//
// MessageId: EMS_OCC_PROXY_NO_URL
//
// MessageText:
//
// EMS OCC Proxy reports that an endpoint URL was not specified.
//
#define EMS_OCC_PROXY_NO_URL             ((EMS_RESULT)0x8004F001L)


#endif // INC_OCC_PROXY_MSGS
/********************************************************************
*	Module:			HealthMonitorMsgs.mc
*	Description: 	Message File for the Health Monitoring Service
*
*********************************************************************
*	Copyright (c) 2009 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_HMMSGS
#define INC_HMMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_HM_BASE_CODE
//
// MessageText:
//
// EMS Health Monitor Service Error
//
#define EMS_HM_BASE_CODE                 ((EMS_RESULT)0x8004EF50L)

//
// MessageId: EMS_HM_SERVICE_START
//
// MessageText:
//
// EMS Health Monitor Service Started
//
#define EMS_HM_SERVICE_START             ((EMS_RESULT)0x0004EF51L)

//
// MessageId: EMS_HM_SERVICE_FAILED
//
// MessageText:
//
// EMS Health Monitor Service did not start due to error %1
//
#define EMS_HM_SERVICE_FAILED            ((EMS_RESULT)0x8004EF52L)

//
// MessageId: EMS_HM_SERVICE_STOP
//
// MessageText:
//
// EMS Health Monitor Service Stopped
//
#define EMS_HM_SERVICE_STOP              ((EMS_RESULT)0x0004EF53L)

//
// MessageId: EMS_HM_ERROR
//
// MessageText:
//
// EMS Health Monitor Service reports error %1.
//
#define EMS_HM_ERROR                     ((EMS_RESULT)0x8004EF54L)

//
// MessageId: EMS_HM_TRACER
//
// MessageText:
//
// EMS Health Monitor Service Trace (%1).
//
#define EMS_HM_TRACER                    ((EMS_RESULT)0x0004EF55L)

//
// MessageId: EMS_HM_NOT_INITIALIZED
//
// MessageText:
//
// EMS Health Monitor Service has not been initialized so cannot process the request.
//
#define EMS_HM_NOT_INITIALIZED           ((EMS_RESULT)0x8004EF56L)

//
// MessageId: EMS_HM_UNEXPECTED_EXCEPTION
//
// MessageText:
//
// EMS Health Monitor Service detected an unexpected exception.
//
#define EMS_HM_UNEXPECTED_EXCEPTION      ((EMS_RESULT)0x8004EF57L)

//
// MessageId: EMS_HM_RECEIVECALIB406_ERROR
//
// MessageText:
//
// EMS Health Monitor Service detected error while receiving calib406 data (%1).
//
#define EMS_HM_RECEIVECALIB406_ERROR     ((EMS_RESULT)0x8004EF58L)

//
// MessageId: EMS_HM_RECEIVELOGDATA_ERROR
//
// MessageText:
//
// EMS Health Monitor Service detected error while receiving log data (%1).
//
#define EMS_HM_RECEIVELOGDATA_ERROR      ((EMS_RESULT)0x8004EF59L)

//
// MessageId: EMS_HM_PROCESSCALIB406_ERROR
//
// MessageText:
//
// EMS Health Monitor Service detected error while processing calib406 data (%1).
//
#define EMS_HM_PROCESSCALIB406_ERROR     ((EMS_RESULT)0x8004EF5AL)

//
// MessageId: EMS_HM_PROCESSLOGDATA_ERROR
//
// MessageText:
//
// EMS Health Monitor Service detected error while processing log data (%1).
//
#define EMS_HM_PROCESSLOGDATA_ERROR      ((EMS_RESULT)0x8004EF5BL)

//
// MessageId: EMS_HM_STATUSREPORT_ERROR
//
// MessageText:
//
// EMS Health Monitor Service detected error while generating a status report (%1).
//
#define EMS_HM_STATUSREPORT_ERROR        ((EMS_RESULT)0x8004EF5CL)


#endif // INC_HMMSGS
/********************************************************************
*	Module:			ActvMsgs.mc
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Message File for EMS URL Retriever/Receiver 
*				Services Errors & Messages
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2009 by EMS Technologies, Inc.,
*					All rights reserved
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

	0.0	01/05/21		rvw	start

********************************************************************/
#ifndef INC_URLRMSGS
#define INC_URLRMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_URLR_BASE_CODE
//
// MessageText:
//
// EMS ActiveBeacon 
//
#define EMS_URLR_BASE_CODE               ((EMS_RESULT)0x8004F100L)

//
// MessageId: EMS_URLR_SERVICE_START
//
// MessageText:
//
// EMS URL Retriever Service Started
//
#define EMS_URLR_SERVICE_START           ((EMS_RESULT)0x0004F101L)

//
// MessageId: EMS_URLR_SERVICE_STOP
//
// MessageText:
//
// EMS URL Retriever Service Stoped
//
#define EMS_URLR_SERVICE_STOP            ((EMS_RESULT)0x0004F102L)

//
// MessageId: EMS_URLR_SERVICE_FAILED
//
// MessageText:
//
// EMS URL Retriever Service did not start due to error %1
//
#define EMS_URLR_SERVICE_FAILED          ((EMS_RESULT)0x8004F103L)

//
// MessageId: EMS_URLR_LOAD_CONFIG_ERROR
//
// MessageText:
//
// EMS URL Retriever Service failed to load the configuration file (%1)
//
#define EMS_URLR_LOAD_CONFIG_ERROR       ((EMS_RESULT)0x8004F104L)

//
// MessageId: EMS_URLR_NO_CONFIG
//
// MessageText:
//
// EMS URL Retriever Service's configuration file is not specified, make sure to configure the service with the proper configuration file.
//
#define EMS_URLR_NO_CONFIG               ((EMS_RESULT)0x8004F105L)

//
// MessageId: EMS_URLR_NO_URLS
//
// MessageText:
//
// EMS URL Retriever Service's configuration file (%1) does not specify any URL configurations, it must have at least one
//
#define EMS_URLR_NO_URLS                 ((EMS_RESULT)0x8004F106L)

//
// MessageId: EMS_FAILED_TO_CONNECT
//
// MessageText:
//
// EMS URL Retriever Service's failed to perform the 'URL Source To Destination' update (URL id=%1), check the network connections to the source and the destination.
//
#define EMS_FAILED_TO_CONNECT            ((EMS_RESULT)0x8004F107L)

//
// MessageId: EMS_BACK_ONLINE
//
// MessageText:
//
// EMS URL Retriever Service's is able to perform successful 'URL Source To Destination' update (URL id=%1).
//
#define EMS_BACK_ONLINE                  ((EMS_RESULT)0x8004F108L)


#endif // INC_URLRMSGS
/********************************************************************
*	Module:			BeaconAdvisoryMsgs.mc
*	Description: 	Message File for the Health Monitoring Service
*
*********************************************************************
*	Copyright (c) 2009 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_BARMSGS
#define INC_BARMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_BAR_BASE_CODE
//
// MessageText:
//
// EMS Beacon Advisory Service Error
//
#define EMS_BAR_BASE_CODE                ((EMS_RESULT)0x8004EF70L)

//
// MessageId: EMS_BAR_SERVICE_START
//
// MessageText:
//
// EMS Beacon Advisory Service Started
//
#define EMS_BAR_SERVICE_START            ((EMS_RESULT)0x0004EF71L)

//
// MessageId: EMS_BAR_SERVICE_FAILED
//
// MessageText:
//
// EMS Beacon Advisory Service did not start due to error %1
//
#define EMS_BAR_SERVICE_FAILED           ((EMS_RESULT)0x8004EF72L)

//
// MessageId: EMS_BAR_SERVICE_STOP
//
// MessageText:
//
// EMS Beacon Advisory Service Stopped
//
#define EMS_BAR_SERVICE_STOP             ((EMS_RESULT)0x0004EF73L)

//
// MessageId: EMS_BAR_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service reports error %1.
//
#define EMS_BAR_ERROR                    ((EMS_RESULT)0x8004EF74L)

//
// MessageId: EMS_BAR_TRACER
//
// MessageText:
//
// EMS Beacon Advisory Service Trace (%1).
//
#define EMS_BAR_TRACER                   ((EMS_RESULT)0x0004EF75L)

//
// MessageId: EMS_BAR_NOT_INITIALIZED
//
// MessageText:
//
// EMS Beacon Advisory Service has not been initialized so cannot process the request.
//
#define EMS_BAR_NOT_INITIALIZED          ((EMS_RESULT)0x8004EF76L)

//
// MessageId: EMS_BAR_UNEXPECTED_EXCEPTION
//
// MessageText:
//
// EMS Beacon Advisory Service detected an unexpected exception.
//
#define EMS_BAR_UNEXPECTED_EXCEPTION     ((EMS_RESULT)0x8004EF77L)

//
// MessageId: EMS_BAR_RECEIVECALIB406_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service detected error while receiving calib406 data (%1).
//
#define EMS_BAR_RECEIVECALIB406_ERROR    ((EMS_RESULT)0x8004EF78L)

//
// MessageId: EMS_BAR_PROCESSCALIB406_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service detected error while processing calib406 data (%1).
//
#define EMS_BAR_PROCESSCALIB406_ERROR    ((EMS_RESULT)0x8004EF79L)

//
// MessageId: EMS_BAR_CONFIG_OVERRIDE
//
// MessageText:
//
// EMS Beacon Advisory Service: Configuration value for "%1=%3" is out of range.  A value of %2 will be used instead.
//
#define EMS_BAR_CONFIG_OVERRIDE          ((EMS_RESULT)0x0004EF7AL)

//
// MessageId: EMS_BAR_REPORT_FAILED
//
// MessageText:
//
// EMS Beacon Advisory Service detected error while generating an advisory report (%1)
//
#define EMS_BAR_REPORT_FAILED            ((EMS_RESULT)0x8004EF7BL)

//
// MessageId: EMS_BAR_RESTORE_UNSUPPORTED_VERSION
//
// MessageText:
//
// EMS Beacon Advisory Service: Failed to restore data from file.  File has an unsupported version.
//
#define EMS_BAR_RESTORE_UNSUPPORTED_VERSION ((EMS_RESULT)0x8004EF7CL)

//
// MessageId: EMS_BAR_RESTORE_READ_FAILED
//
// MessageText:
//
// Failed to read the expected number of bytes.
//
#define EMS_BAR_RESTORE_READ_FAILED      ((EMS_RESULT)0x8004EF7DL)

//
// MessageId: EMS_BAR_SAVE_WRITE_FAILED
//
// MessageText:
//
// Failed to write the required number of bytes.
//
#define EMS_BAR_SAVE_WRITE_FAILED        ((EMS_RESULT)0x8004EF7EL)

//
// MessageId: EMS_BAR_LOADFILE_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service: Error detected while attempting to restore data from file (%1)
//
#define EMS_BAR_LOADFILE_ERROR           ((EMS_RESULT)0x8004EF7FL)

//
// MessageId: EMS_BAR_SAVEFILE_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service: Error detected while attempting to save data to file (%1)
//
#define EMS_BAR_SAVEFILE_ERROR           ((EMS_RESULT)0x8004EF80L)

//
// MessageId: EMS_BAR_BAD_DATA_DIR
//
// MessageText:
//
// EMS Beacon Advisory Service: Configuration specified an invalid data directory.  The software will not be able to save across restarts.
//
#define EMS_BAR_BAD_DATA_DIR             ((EMS_RESULT)0x8004EF81L)

//
// MessageId: EMS_BAR_RECEIVELOCATE_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service detected error while receiving locate data (%1).
//
#define EMS_BAR_RECEIVELOCATE_ERROR      ((EMS_RESULT)0x8004EF82L)

//
// MessageId: EMS_BAR_PROCESSLOCATE_ERROR
//
// MessageText:
//
// EMS Beacon Advisory Service detected error while processing locate data (%1).
//
#define EMS_BAR_PROCESSLOCATE_ERROR      ((EMS_RESULT)0x8004EF83L)


#endif // INC_BARMSGS
#ifndef INC_OMMSGS
#define INC_OMMSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_OM_BASE_CODE
//
// MessageText:
//
// EMS Orbit Manager Error
//
#define EMS_OM_BASE_CODE                 ((EMS_RESULT)0x8004F200L)

//
// MessageId: EMS_OM_SERVICE_START
//
// MessageText:
//
// EMS Orbit Manager Service Started
//
#define EMS_OM_SERVICE_START             ((EMS_RESULT)0x0004F201L)

//
// MessageId: EMS_OM_SERVICE_STOP
//
// MessageText:
//
// EMS Orbit Manager Service Stopped
//
#define EMS_OM_SERVICE_STOP              ((EMS_RESULT)0x0004F202L)

//
// MessageId: EMS_OM_EXCEPTION
//
// MessageText:
//
// EMS Orbit Manager Exception thrown: %1
//
#define EMS_OM_EXCEPTION                 ((EMS_RESULT)0x8004F203L)

//
// MessageId: EMS_OM_TRACER
//
// MessageText:
//
// EMS Orbit Manager - Trace %1.
//
#define EMS_OM_TRACER                    ((EMS_RESULT)0x0004F204L)

//
// MessageId: EMS_OM_EXCEPTION_TRACE
//
// MessageText:
//
// EMS Orbit Manager - Exception thrown: File: %1 Line: %2 hr = %3
//
#define EMS_OM_EXCEPTION_TRACE           ((EMS_RESULT)0x8004F205L)

//
// MessageId: EMS_OM_CONFIGITEM_NOTFOUND
//
// MessageText:
//
// EMS Orbit Manager - Unable to find config item Group: %1 GroupID: %2 Key: %3.
//
#define EMS_OM_CONFIGITEM_NOTFOUND       ((EMS_RESULT)0x8004F206L)

//
// MessageId: EMS_OM_GETTING_GLO_EPHEM
//
// MessageText:
//
// EMS Orbit Manager is retrieving ephemeris for Glonass satellites.
//
#define EMS_OM_GETTING_GLO_EPHEM         ((EMS_RESULT)0x0004F207L)

//
// MessageId: EMS_OM_GOT_GLO_EPHEM
//
// MessageText:
//
// EMS Orbit Manager retrieved ephemeris for (%1) Glonass satellites.
//
#define EMS_OM_GOT_GLO_EPHEM             ((EMS_RESULT)0x0004F208L)

//
// MessageId: EMS_OM_GETTING_GAL_EPHEM
//
// MessageText:
//
// EMS Orbit Manager is retrieving ephemeris for Galileo satellites.
//
#define EMS_OM_GETTING_GAL_EPHEM         ((EMS_RESULT)0x0004F209L)

//
// MessageId: EMS_OM_GOT_GAL_EPHEM
//
// MessageText:
//
// EMS Orbit Manager retrieved ephemeris for (%1) Galileo satellites.
//
#define EMS_OM_GOT_GAL_EPHEM             ((EMS_RESULT)0x0004F20AL)

//
// MessageId: EMS_OM_GETTING_GPS_EPHEM
//
// MessageText:
//
// EMS Orbit Manager is retrieving ephemeris for GPS satellites.
//
#define EMS_OM_GETTING_GPS_EPHEM         ((EMS_RESULT)0x0004F20BL)

//
// MessageId: EMS_OM_GOT_GPS_EPHEM
//
// MessageText:
//
// EMS Orbit Manager retrieved ephemeris for (%1) GPS satellites.
//
#define EMS_OM_GOT_GPS_EPHEM             ((EMS_RESULT)0x0004F20CL)

//
// MessageId: EMS_OM_ORBIT_NOT_CURRENT
//
// MessageText:
//
// EMS Orbit Manager - Orbit vector for satellite %1 is older than 2 days.
//
#define EMS_OM_ORBIT_NOT_CURRENT         ((EMS_RESULT)0x8004F20DL)

//
// MessageId: EMS_OM_ORBIT_NOT_AVAILABLE
//
// MessageText:
//
// EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) is not available.
//
#define EMS_OM_ORBIT_NOT_AVAILABLE       ((EMS_RESULT)0x8004F20EL)

//
// MessageId: EMS_OM_ORBIT_NOT_UPDATED
//
// MessageText:
//
// EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) could not be updated.
//
#define EMS_OM_ORBIT_NOT_UPDATED         ((EMS_RESULT)0x8004F20FL)

//
// MessageId: EMS_OM_ORBIT_LOADED
//
// MessageText:
//
// EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) has been loaded by the system, Epoch time = %3.
//
#define EMS_OM_ORBIT_LOADED              ((EMS_RESULT)0x0004F210L)

//
// MessageId: EMS_OM_JAVAD_CONNECT_FAILED
//
// MessageText:
//
// EMS Orbit Manager - Connection to Javad GNSS failed.
//
#define EMS_OM_JAVAD_CONNECT_FAILED      ((EMS_RESULT)0xC004F211L)

//
// MessageId: EMS_OM_GNSS_INITIALIZATION_FAILED
//
// MessageText:
//
// EMS Orbit Manager - Initialization of the GNSS failed.
//
#define EMS_OM_GNSS_INITIALIZATION_FAILED ((EMS_RESULT)0xC004F212L)

//
// MessageId: EMS_OM_ORBIT_NOT_LOADED
//
// MessageText:
//
// EMS Orbit Manager - Orbit vector for sat %1 (Norad %2) was not loaded by the system.
//
#define EMS_OM_ORBIT_NOT_LOADED          ((EMS_RESULT)0x8004F213L)

//
// MessageId: EMS_OM_INIT_JAVAD_EPHEM
//
// MessageText:
//
// EMS Orbit Manager is sending a request to Javad GNSS to output all ephemeris.
//
#define EMS_OM_INIT_JAVAD_EPHEM          ((EMS_RESULT)0x0004F214L)

//
// MessageId: EMS_OM_DUPL_ORBIT_VECTOR_POSVELERR
//
// MessageText:
//
// Duplicate orbit vector received for Sat=%1, PosErr=%2, VelErr=%3.
//
#define EMS_OM_DUPL_ORBIT_VECTOR_POSVELERR ((EMS_RESULT)0x0004F215L)

//
// MessageId: EMS_OM_EPHEMERIS_SERIALIZATION_FAILURE
//
// MessageText:
//
// EMS Orbit Manager was unable to serialize the ephemeris. Error:  %1.
//
#define EMS_OM_EPHEMERIS_SERIALIZATION_FAILURE ((EMS_RESULT)0x8004F216L)

//
// MessageId: EMS_OM_ORBITEXT_SERIALIZATION_FAILURE
//
// MessageText:
//
// EMS Orbit Manager was unable to serialize the orbit text. Error:  %1.
//
#define EMS_OM_ORBITEXT_SERIALIZATION_FAILURE ((EMS_RESULT)0x8004F217L)

//
// MessageId: EMS_OM_NEW_EPHEMERIS_UPDATE
//
// MessageText:
//
// EMS Orbit Manager received new ephemeris data.
//
#define EMS_OM_NEW_EPHEMERIS_UPDATE      ((EMS_RESULT)0x0004F218L)

//
// MessageId: EMS_OM_NEW_TLE_UPDATE
//
// MessageText:
//
// EMS Orbit Manager received new TLE data.
//
#define EMS_OM_NEW_TLE_UPDATE            ((EMS_RESULT)0x0004F219L)

//
// MessageId: EMS_OM_EPHEMERIS_UPDATE_FAILURE
//
// MessageText:
//
// EMS Orbit Manager failed to process the received ephemeris data. Error:  %1.
//
#define EMS_OM_EPHEMERIS_UPDATE_FAILURE  ((EMS_RESULT)0x8004F21AL)

//
// MessageId: EMS_OM_TLE_UPDATE_FAILURE
//
// MessageText:
//
// EMS Orbit Manager failed to process the received TLE data. Error:  %1.
//
#define EMS_OM_TLE_UPDATE_FAILURE        ((EMS_RESULT)0x8004F21BL)

//
// MessageId: EMS_MAST_ERR_ORBIT_SOURCE_PRIORITY
//
// MessageText:
//
// EMS Master reports orbit priority value for Sat=%1 with Source=%2 is %3 with value %4
//
#define EMS_MAST_ERR_ORBIT_SOURCE_PRIORITY ((EMS_RESULT)0x8004F21CL)


#endif // INC_OMMSGS
/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_LOG_AGGREGATOR_MSGS
#define INC_LOG_AGGREGATOR_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_LA_BASE_CODE
//
// MessageText:
//
// EMS Pass Scheduler error.
//
#define EMS_LA_BASE_CODE                 ((EMS_RESULT)0x8004F300L)

//
// MessageId: EMS_LA_STARTED
//
// MessageText:
//
// EMS Log Aggregator has started.
//
#define EMS_LA_STARTED                   ((EMS_RESULT)0x0004F301L)

//
// MessageId: EMS_LA_START_FAILED
//
// MessageText:
//
// EMS Log Aggregator failed to start with error code %1.
//
#define EMS_LA_START_FAILED              ((EMS_RESULT)0x8004F302L)

//
// MessageId: EMS_LA_STOPPED
//
// MessageText:
//
// EMS Log Aggregator has stopped.
//
#define EMS_LA_STOPPED                   ((EMS_RESULT)0x0004F303L)

//
// MessageId: EMS_LA_NO_CONFIG
//
// MessageText:
//
// EMS Log Aggregator failed to find a configuration file specified in the registry at HKLM/Software/EMS Technologies/Components/%1/config.
//
#define EMS_LA_NO_CONFIG                 ((EMS_RESULT)0x8004F304L)

//
// MessageId: EMS_LA_NO_TEMP_FOLDER
//
// MessageText:
//
// EMS Log Aggregator failed to find a value for the temporary folder (%1) in the configuration file (%2).
//
#define EMS_LA_NO_TEMP_FOLDER            ((EMS_RESULT)0x8004F305L)

//
// MessageId: EMS_LA_MAIN_LOOP_EXCEPTION
//
// MessageText:
//
// EMS Log Aggregator caught an unknown exception in the main processing loop.
//
#define EMS_LA_MAIN_LOOP_EXCEPTION       ((EMS_RESULT)0x8004F306L)

//
// MessageId: EMS_LA_NO_OUTPUT_FOLDER_CONFIG
//
// MessageText:
//
// EMS Log Aggregator failed to find a configured log output folder.
//
#define EMS_LA_NO_OUTPUT_FOLDER_CONFIG   ((EMS_RESULT)0x8004F307L)

//
// MessageId: EMS_LA_LOG_CONSUMER_NOT_CONNECTED
//
// MessageText:
//
// EMS Log Aggregator Service reports that it could not connect to the Message Queue for receipt of log messages. Processing will continue, but logs will not be received.
//
#define EMS_LA_LOG_CONSUMER_NOT_CONNECTED ((EMS_RESULT)0x0004F308L)

//
// MessageId: EMS_LA_PRODUCER_CREATED
//
// MessageText:
//
// EMS Log Aggregator Service registered an MQ producer with broker %1 on topic %2 with persistent delivery %3.
//
#define EMS_LA_PRODUCER_CREATED          ((EMS_RESULT)0x0004F309L)

//
// MessageId: EMS_LA_PRODUCER_INIT_FAILURE
//
// MessageText:
//
// EMS Log Aggregator Service failed to initialize a message queue producer.
//
#define EMS_LA_PRODUCER_INIT_FAILURE     ((EMS_RESULT)0x8004F30AL)

//
// MessageId: EMS_LA_INVALID_LOG_RECORD_SIZE
//
// MessageText:
//
// EMS Log Aggregator Service unable to convert binary log to XML. Input log record does not match expected size.
//
#define EMS_LA_INVALID_LOG_RECORD_SIZE   ((EMS_RESULT)0x8004F30BL)

//
// MessageId: EMS_LA_NO_MQ_PRODUCER
//
// MessageText:
//
// EMS Log Aggregator Service failure. Unable to transfer pipeline data to MQ. MQ Producer is not initialized.
//
#define EMS_LA_NO_MQ_PRODUCER            ((EMS_RESULT)0x8004F30CL)

//
// MessageId: EMS_LA_PRODUCER_SEND_FAILURE
//
// MessageText:
//
// EMS Log Aggregator Service failed to send message on Message Queue. Details:  %1.
//
#define EMS_LA_PRODUCER_SEND_FAILURE     ((EMS_RESULT)0x8004F30DL)

//
// MessageId: EMS_LA_LOG_EXCEPTION
//
// MessageText:
//
// EMS Aggregator Service reports that an exception report was received from the log message handler.
//
#define EMS_LA_LOG_EXCEPTION             ((EMS_RESULT)0x0004F30EL)


#endif // INC_LOG_AGGREGATOR_MSGS
/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************
 Revision Record
	$Log:
	$
********************************************************************/
#ifndef INC_MOA_CONTROLLER_PROXY_MSGS
#define INC_MOA_CONTROLLER_PROXY_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_MOA_CONTROLLER_PROXY_BASE_CODE
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy error.
//
#define EMS_MOA_CONTROLLER_PROXY_BASE_CODE ((EMS_RESULT)0x0004F400L)

//
// MessageId: EMS_MOAPOXY_CREATE_INSTANCE_ERR_HR
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy: Unable to create instance of %1 during initialization (Error=%2).
//
#define EMS_MOAPOXY_CREATE_INSTANCE_ERR_HR ((EMS_RESULT)0x8004F401L)

//
// MessageId: EMS_MOA_CONTROLLER_PROXY_AC_CALL_FAILURE
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports an error calling the antenna controller.  The error code is %1 and error message is "%2".
//
#define EMS_MOA_CONTROLLER_PROXY_AC_CALL_FAILURE ((EMS_RESULT)0x8004F402L)

//
// MessageId: EMS_MOA_CONTROLLER_PROXY_NO_URL
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports that an endpoint URL was not specified.
//
#define EMS_MOA_CONTROLLER_PROXY_NO_URL  ((EMS_RESULT)0x8004F403L)

//
// MessageId: EMS_MOA_CONTROLLER_PROXY_NO_LOCATION
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports an error getting the site location (hr=%1).
//
#define EMS_MOA_CONTROLLER_PROXY_NO_LOCATION ((EMS_RESULT)0x8004F404L)

//
// MessageId: EMS_MOA_CONTROLLER_POXY_UPDATE_ANTENNA_INFO_FAILED
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports an error getting the site location (hr=%1).
//
#define EMS_MOA_CONTROLLER_POXY_UPDATE_ANTENNA_INFO_FAILED ((EMS_RESULT)0x8004F405L)

//
// MessageId: EMS_MOA_CONTROLLER_POXY_UPDATE_ORBIT_FAILED
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports an error updating orbit data for satellite %1 (hr=%2).
//
#define EMS_MOA_CONTROLLER_POXY_UPDATE_ORBIT_FAILED ((EMS_RESULT)0x8004F406L)

//
// MessageId: EMS_MOA_CONTROLLER_POXY_TRACKING_FAILED
//
// MessageText:
//
// EMS MEO Optimized Antenna Controller Proxy reports the antenna has failed to track satellite %1 within %2 seconds.
//
#define EMS_MOA_CONTROLLER_POXY_TRACKING_FAILED ((EMS_RESULT)0x8004F407L)


#endif // INC_MOA_CONTROLLER_PROXY_MSGS
/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/
#ifndef INC_PMQ_MSGS
#define INC_PMQ_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: PMQ_BRIDGE_BASE_CODE
//
// MessageText:
//
// Pipeline-MQ Bridge
//
#define PMQ_BRIDGE_BASE_CODE             ((EMS_RESULT)0x8004F450L)

//
// MessageId: PMQ_SERVICE_START
//
// MessageText:
//
// Pipeline-MQ Bridge Service Started
//
#define PMQ_SERVICE_START                ((EMS_RESULT)0x0004F451L)

//
// MessageId: PMQ_SERVICE_STOP
//
// MessageText:
//
// Pipeline-MQ Bridge Service Stopped
//
#define PMQ_SERVICE_STOP                 ((EMS_RESULT)0x0004F452L)

//
// MessageId: PMQ_SERVICE_FAILED
//
// MessageText:
//
// Pipeline-MQ Bridge Service did not start due to error (%1)
//
#define PMQ_SERVICE_FAILED               ((EMS_RESULT)0x8004F453L)

//
// MessageId: PMQ_LOOP_EXCEPTION
//
// MessageText:
//
// Pipeline-MQ Bridge Service exception trapped in main processing loop.  No details available.
//
#define PMQ_LOOP_EXCEPTION               ((EMS_RESULT)0x8004F454L)

//
// MessageId: PMQ_PTOMQ_SINK_CONNECTED
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue adapter registered a pipeline sink on channel %1 of record size %2 bytes.
//
#define PMQ_PTOMQ_SINK_CONNECTED         ((EMS_RESULT)0x0004F455L)

//
// MessageId: PMQ_PTOMQ_THREAD_EXIT
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue failure with code %1.  Processing thread is exiting.
//
#define PMQ_PTOMQ_THREAD_EXIT            ((EMS_RESULT)0x8004F456L)

//
// MessageId: PMQ_PTOMQ_PRODUCER_CREATED
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue adapter registered an MQ producer with broker %1 on topic %2 with persistent delivery %3.
//
#define PMQ_PTOMQ_PRODUCER_CREATED       ((EMS_RESULT)0x0004F457L)

//
// MessageId: PMQ_PTOMQ_PRODUCER_SEND_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue adapter failed to send message on Message Queue.  Details:  %1.
//
#define PMQ_PTOMQ_PRODUCER_SEND_FAILURE  ((EMS_RESULT)0x8004F458L)

//
// MessageId: PMQ_PTOMQ_THREAD_CONTNUE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue failure in main processing thread with code %1.  Reconnecting pipeline and message queue.  Processing thread will continue.
//
#define PMQ_PTOMQ_THREAD_CONTNUE         ((EMS_RESULT)0x8004F459L)

//
// MessageId: PMQ_PTOMQ_EXCEPTION_THREAD_CONTNUE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue exception in main processing thread.  Processing thread will continue.
//
#define PMQ_PTOMQ_EXCEPTION_THREAD_CONTNUE ((EMS_RESULT)0x8004F45AL)

//
// MessageId: PMQ_PTOMQ_REC_SIZE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue failure.  The pipeline data record buffer size is incorrectly configured.  A value of 0 or less has been configured.
//
#define PMQ_PTOMQ_REC_SIZE               ((EMS_RESULT)0x8004F45BL)

//
// MessageId: PMQ_PTOMQ_NO_PRODUCER
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue failure.  Unable to transfer pipeline data to MQ.  An MQ Producer is not initialized.
//
#define PMQ_PTOMQ_NO_PRODUCER            ((EMS_RESULT)0x8004F45CL)

//
// MessageId: PMQ_NUM_MAPPINGS
//
// MessageText:
//
// Pipeline-MQ Bridge loaded %1 mappings.
//
#define PMQ_NUM_MAPPINGS                 ((EMS_RESULT)0x0004F45DL)

//
// MessageId: PMQ_UNSUPPORTED_DIRECTION
//
// MessageText:
//
// Pipeline-MQ Bridge does not support the direction specified in the mapping for %1.  Mapping will be ignored.
//
#define PMQ_UNSUPPORTED_DIRECTION        ((EMS_RESULT)0x8004F45EL)

//
// MessageId: PMQ_MAPPING_PARSE_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to parse the mapping configuration.  This is most likely due to a format error in the configuration.  Error:  %1.
//
#define PMQ_MAPPING_PARSE_FAILURE        ((EMS_RESULT)0x8004F45FL)

//
// MessageId: PMQ_MAPPING_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to parse the mapping configuration.  This may be due to a format error in the configuration or an error in the schema definition.  Error:  %1.
//
#define PMQ_MAPPING_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F460L)

//
// MessageId: PMQ_MAPPING_GENERAL_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to parse the mapping configuration.  Error details:  %1.
//
#define PMQ_MAPPING_GENERAL_FAILURE      ((EMS_RESULT)0x8004F461L)

//
// MessageId: PMQ_PTOMQ_START_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to start a Pipeline to Message Queue adapter.
//
#define PMQ_PTOMQ_START_FAILURE          ((EMS_RESULT)0x8004F462L)

//
// MessageId: PMQ_PTOMQ_STARTED
//
// MessageText:
//
// Pipeline-MQ Bridge has started %1 Pipeline to Message Queue adapters.
//
#define PMQ_PTOMQ_STARTED                ((EMS_RESULT)0x8004F463L)

//
// MessageId: PMQ_PTOMQ_STOP_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to stop a Pipeline to Message Queue adapter.
//
#define PMQ_PTOMQ_STOP_FAILURE           ((EMS_RESULT)0x8004F464L)

//
// MessageId: PMQ_PTOMQ_STOPPED
//
// MessageText:
//
// Pipeline-MQ Bridge has stopped %1 Pipeline to Message Queue adapters.
//
#define PMQ_PTOMQ_STOPPED                ((EMS_RESULT)0x8004F465L)

//
// MessageId: PMQ_PTOMQ_PRODUCER_INIT_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipeline to Message Queue adapter failed to initialize a message queue producer.
//
#define PMQ_PTOMQ_PRODUCER_INIT_FAILURE  ((EMS_RESULT)0x8004F466L)

//
// MessageId: PMQ_MQTOP_SRC_CONNECTED
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter registered a pipeline source on channel %1 of record size %2 bytes.
//
#define PMQ_MQTOP_SRC_CONNECTED          ((EMS_RESULT)0x0004F467L)

//
// MessageId: PMQ_MQTOP_CONSUMER_CREATED
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter registered an MQ consumer with broker %1 on topic %2.
//
#define PMQ_MQTOP_CONSUMER_CREATED       ((EMS_RESULT)0x0004F468L)

//
// MessageId: PMQ_MQTOP_PENDING_MSGS_WARNING
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter has %1 buffered messages awaiting transfer to Pipeline.
//
#define PMQ_MQTOP_PENDING_MSGS_WARNING   ((EMS_RESULT)0x8004F469L)

//
// MessageId: PMQ_MQTOP_PENDING_MSGS_ALARM
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter has %1 buffered messages awaiting transfer to Pipeline.  The oldest message has been removed to prevent further resource consumption.
//
#define PMQ_MQTOP_PENDING_MSGS_ALARM     ((EMS_RESULT)0x8004F46AL)

//
// MessageId: PMQ_MQTOP_MQ_EXCEPTION
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter has received an exception notification from the message queue broker:  %1.
//
#define PMQ_MQTOP_MQ_EXCEPTION           ((EMS_RESULT)0x8004F46BL)

//
// MessageId: PMQ_MQTOP_TYPE_NOT_SUPPORTED
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter has been configured to process %1 type source messages.  This message type is not currently supported.
//
#define PMQ_MQTOP_TYPE_NOT_SUPPORTED     ((EMS_RESULT)0x8004F46CL)

//
// MessageId: PMQ_MQTOP_TYPE_NOT_EXPECTED
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe adapter has received a message from the Message Queue of an unexpected type.  It will be ignored.
//
#define PMQ_MQTOP_TYPE_NOT_EXPECTED      ((EMS_RESULT)0x8004F46DL)

//
// MessageId: PMQ_MQTOP_NO_PSOURCE
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe failure.  Unable to transfer MQ data to pipeline.  A pipeline source is not initialized.
//
#define PMQ_MQTOP_NO_PSOURCE             ((EMS_RESULT)0x8004F46EL)

//
// MessageId: PMQ_MQTOP_START_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to start a Message Queue to Pipeline adapter.
//
#define PMQ_MQTOP_START_FAILURE          ((EMS_RESULT)0x8004F46FL)

//
// MessageId: PMQ_MQTOP_STARTED
//
// MessageText:
//
// Pipeline-MQ Bridge has started %1 Message Queue to Pipeline adapters.
//
#define PMQ_MQTOP_STARTED                ((EMS_RESULT)0x8004F470L)

//
// MessageId: PMQ_MQTOP_STOP_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge was unable to stop a Message Queue to Pipeline adapter.
//
#define PMQ_MQTOP_STOP_FAILURE           ((EMS_RESULT)0x8004F471L)

//
// MessageId: PMQ_MQTOP_STOPPED
//
// MessageText:
//
// Pipeline-MQ Bridge has stopped %1 Message Queue to Pipeline adapters.
//
#define PMQ_MQTOP_STOPPED                ((EMS_RESULT)0x0004F472L)

//
// MessageId: PMQ_MQTOP_RECSIZE_MISMATCH
//
// MessageText:
//
// Pipeline-MQ Bridge notes a difference between the configured record size (%1) and the size of records received from the Message Queue (%2).  Data will still be written to Pipeline.
//
#define PMQ_MQTOP_RECSIZE_MISMATCH       ((EMS_RESULT)0x8004F473L)

//
// MessageId: PMQ_MQTOP_RECSIZE_MISMATCH_TOO_BIG
//
// MessageText:
//
// Pipeline-MQ Bridge notes that the configured record size (%1) is smaller than the size of records received from the Message Queue (%2).  Data will not be written to Pipeline.
//
#define PMQ_MQTOP_RECSIZE_MISMATCH_TOO_BIG ((EMS_RESULT)0x8004F474L)

//
// MessageId: PMQ_MQTOP_CONSUMER_EXCEPTION
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe exception has been captured by the Message Queue consumer.
//
#define PMQ_MQTOP_CONSUMER_EXCEPTION     ((EMS_RESULT)0x8004F475L)

//
// MessageId: PMQ_MQTOP_CONSUMER_INIT_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge Pipeline to Message Queue adapter failed to initialize a message queue consumer.
//
#define PMQ_MQTOP_CONSUMER_INIT_FAILURE  ((EMS_RESULT)0x8004F476L)

//
// MessageId: PMQ_MQTOPIPE_THREAD_CONTNUE
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe failure in main processing thread with code %1.  Reconnecting pipeline and message queue.  Processing thread will continue.
//
#define PMQ_MQTOPIPE_THREAD_CONTNUE      ((EMS_RESULT)0x8004F477L)

//
// MessageId: PMQ_UNHANDLED_TYPE_CONVERSION
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper unable to perform conversion.  Specified conversion is not handled:  %1.  PipeMQBridge configuration has an error.
//
#define PMQ_UNHANDLED_TYPE_CONVERSION    ((EMS_RESULT)0x8004F478L)

//
// MessageId: PMQ_CONVERSION_TYPE_MISMATCH
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper unable to perform conversion.  Input data record size does not match expected for conversion %1.
//
#define PMQ_CONVERSION_TYPE_MISMATCH     ((EMS_RESULT)0x8004F479L)

//
// MessageId: PMQ_CONVERSION_CALIB_XML
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed to convert legacy calib type to XML version.  %1 code returned during conversion.
//
#define PMQ_CONVERSION_CALIB_XML         ((EMS_RESULT)0x8004F47AL)

//
// MessageId: PMQ_PIPETOMQ_DEST_TYPE_CONVERT_UNHANDLED
//
// MessageText:
//
// Pipeline-MQ Bridge Pipe to Message Queue does not support conversion to the destination type configured for mapping %1.  Error in configuration.
//
#define PMQ_PIPETOMQ_DEST_TYPE_CONVERT_UNHANDLED ((EMS_RESULT)0x8004F47BL)

//
// MessageId: PMQ_CONVERSION_FROM_STRING_STREAM
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed to create a stream from an input string with error code %1.
//
#define PMQ_CONVERSION_FROM_STRING_STREAM ((EMS_RESULT)0x8004F47CL)

//
// MessageId: PMQ_CONVERSION_FROM_STRING_SIZE
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed to create a stream from an input string.  The expected number of bytes written did not match expected value.
//
#define PMQ_CONVERSION_FROM_STRING_SIZE  ((EMS_RESULT)0x8004F47DL)

//
// MessageId: PMQ_CONVERSION_FROM_STRING_PARSE
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed while parsing an input string for conversion with error code %1.
//
#define PMQ_CONVERSION_FROM_STRING_PARSE ((EMS_RESULT)0x8004F47EL)

//
// MessageId: PMQ_CONVERSION_FROM_STRING_NULL
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed while parsing an input string for conversion.  Parsing results are NULL.
//
#define PMQ_CONVERSION_FROM_STRING_NULL  ((EMS_RESULT)0x8004F47FL)

//
// MessageId: PMQ_CONVERSION_SIT722A_READ_FAILURE
//
// MessageText:
//
// Pipeline-MQ Bridge Type Mapper failed while reading data from a TOA/FOA string message parser class with code %1.
//
#define PMQ_CONVERSION_SIT722A_READ_FAILURE ((EMS_RESULT)0x8004F480L)

//
// MessageId: PMQ_MQTOP_NO_TEXT_CONVERSION
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe is configured to receive text type messages, but no conversion/map to type is specified in the mapping configuration for mapping %1.
//
#define PMQ_MQTOP_NO_TEXT_CONVERSION     ((EMS_RESULT)0x8004F481L)

//
// MessageId: PMQ_MQTOP_PIPELINE_WRITE_ERROR
//
// MessageText:
//
// Pipeline-MQ Bridge Message Queue to Pipe reports an error with code %1 writing data to the pipeline for mapping %2.
//
#define PMQ_MQTOP_PIPELINE_WRITE_ERROR   ((EMS_RESULT)0x8004F482L)

//
// MessageId: PMQ_MQTOP_INTRECSIZE_MISMATCH
//
// MessageText:
//
// Pipeline-MQ Bridge found difference between the expected record size (%1) and the size of records in the internal container (%2). Data will not be written to MQ.
//
#define PMQ_MQTOP_INTRECSIZE_MISMATCH    ((EMS_RESULT)0x8004F483L)


#endif // INC_PMQ_MSGS
/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/
#ifndef INC_CONFIGCLIENT_MSGS
#define INC_CONFIGCLIENT_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: CONFCLI_BASE_CODE
//
// MessageText:
//
// Configuration Client
//
#define CONFCLI_BASE_CODE                ((EMS_RESULT)0x8004F500L)

//
// MessageId: CONFGCLI_HTTPGET_FAIL
//
// MessageText:
//
// Configuration Client exception performing HTTP GET.  HTTP Status code = %1.  HTTP Reason = %2.
//
#define CONFGCLI_HTTPGET_FAIL            ((EMS_RESULT)0x8004F501L)

//
// MessageId: CONFGCLI_HTTPGET_FAIL_NO_RESPONSE
//
// MessageText:
//
// Configuration Client exception performing HTTP GET.  HTTP Server is not responding, URL is http://%1:%2/%3.
//
#define CONFGCLI_HTTPGET_FAIL_NO_RESPONSE ((EMS_RESULT)0x8004F502L)

//
// MessageId: SATCLIENT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for Satellite encountered a configuration parsing exception.  Details:  %1.
//
#define SATCLIENT_PARSE_FAILURE          ((EMS_RESULT)0x8004F503L)

//
// MessageId: SATCLIENT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for Satellite encountered a schema exception while parsing configuration.  Details:  %1.
//
#define SATCLIENT_PARSE_SCHEMA_FAILURE   ((EMS_RESULT)0x8004F504L)

//
// MessageId: SATCLIENT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for Satellite encountered an exception while parsing configuration.  Details:  %1.
//
#define SATCLIENT_GENERAL_FAILURE        ((EMS_RESULT)0x8004F505L)

//
// MessageId: PIPEMQCLIENT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for Pipe to MQ Bridging encountered a configuration parsing exception.  Details:  %1.
//
#define PIPEMQCLIENT_PARSE_FAILURE       ((EMS_RESULT)0x8004F506L)

//
// MessageId: PIPEMQCLIENT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for Pipe to MQ Bridging encountered a schema exception while parsing configuration.  Details:  %1.
//
#define PIPEMQCLIENT_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F507L)

//
// MessageId: PIPEMQCLIENT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for Pipe to MQ Bridging encountered an exception while parsing configuration.  Details:  %1.
//
#define PIPEMQCLIENT_GENERAL_FAILURE     ((EMS_RESULT)0x8004F508L)

//
// MessageId: BEACLIENT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for Beacon encountered a configuration parsing exception.  Details:  %1.
//
#define BEACLIENT_PARSE_FAILURE          ((EMS_RESULT)0x8004F509L)

//
// MessageId: BEACLIENT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for Beacon encountered a schema exception while parsing configuration.  Details:  %1.
//
#define BEACLIENT_PARSE_SCHEMA_FAILURE   ((EMS_RESULT)0x8004F50AL)

//
// MessageId: BEACLIENT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for Beacon encountered an exception while parsing configuration.  Details:  %1.
//
#define BEACLIENT_GENERAL_FAILURE        ((EMS_RESULT)0x8004F50BL)

//
// MessageId: CCODECLIENT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for CountryCode encountered a configuration parsing exception.  Details:  %1.
//
#define CCODECLIENT_PARSE_FAILURE        ((EMS_RESULT)0x8004F50CL)

//
// MessageId: CCODECLIENT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for CountryCode encountered a schema exception while parsing configuration.  Details:  %1.
//
#define CCODECLIENT_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F50DL)

//
// MessageId: CCODECLIENT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for CountryCode encountered an exception while parsing configuration.  Details:  %1.
//
#define CCODECLIENT_GENERAL_FAILURE      ((EMS_RESULT)0x8004F50EL)

//
// MessageId: MEOSYSTEMCLIENT_LUT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LUTConfig encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LUT_PARSE_FAILURE ((EMS_RESULT)0x8004F50FL)

//
// MessageId: MEOSYSTEMCLIENT_LUT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LUTConfig encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LUT_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F510L)

//
// MessageId: MEOSYSTEMCLIENT_LUT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LUTConfig encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LUT_GENERAL_FAILURE ((EMS_RESULT)0x8004F511L)

//
// MessageId: MEOSYSTEMCLIENT_MEOLUT_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem MEOLUTConfig encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_MEOLUT_PARSE_FAILURE ((EMS_RESULT)0x8004F512L)

//
// MessageId: MEOSYSTEMCLIENT_MEOLUT_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem MEOLUTConfig encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_MEOLUT_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F513L)

//
// MessageId: MEOSYSTEMCLIENT_MEOLUT_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem MEOLUTConfig encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_MEOLUT_GENERAL_FAILURE ((EMS_RESULT)0x8004F514L)

//
// MessageId: MEOSYSTEMCLIENT_CLOCK_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem ClockConfig encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_CLOCK_PARSE_FAILURE ((EMS_RESULT)0x8004F515L)

//
// MessageId: MEOSYSTEMCLIENT_CLOCK_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem ClockConfig encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_CLOCK_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F516L)

//
// MessageId: MEOSYSTEMCLIENT_CLOCK_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem ClockConfig encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_CLOCK_GENERAL_FAILURE ((EMS_RESULT)0x8004F517L)

//
// MessageId: MEOSYSTEMCLIENT_FP_CONFIG_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem FPConfig encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_FP_CONFIG_PARSE_FAILURE ((EMS_RESULT)0x8004F518L)

//
// MessageId: MEOSYSTEMCLIENT_FP_CONFIG_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem FPConfig encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_FP_CONFIG_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F519L)

//
// MessageId: MEOSYSTEMCLIENT_FP_CONFIG_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem FPConfig encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_FP_CONFIG_GENERAL_FAILURE ((EMS_RESULT)0x8004F51AL)

//
// MessageId: MEOSYSTEMCLIENT_SP_CONFIG_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SPConfig encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_CONFIG_PARSE_FAILURE ((EMS_RESULT)0x8004F51BL)

//
// MessageId: MEOSYSTEMCLIENT_SP_CONFIG_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SPConfig encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_CONFIG_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F51CL)

//
// MessageId: MEOSYSTEMCLIENT_SP_CONFIG_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SPConfig encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_CONFIG_GENERAL_FAILURE ((EMS_RESULT)0x8004F51DL)

//
// MessageId: MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SP Params Config encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_FAILURE ((EMS_RESULT)0x8004F51EL)

//
// MessageId: MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SP Params Config encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F51FL)

//
// MessageId: MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem SP Params Config encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SP_PARAMS_CONFIG_GENERAL_FAILURE ((EMS_RESULT)0x8004F520L)

//
// MessageId: MEOSYSTEMCLIENT_DM_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem DataManager Config encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_DM_PARSE_FAILURE ((EMS_RESULT)0x8004F521L)

//
// MessageId: MEOSYSTEMCLIENT_DM_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem DataManager Config encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_DM_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F522L)

//
// MessageId: MEOSYSTEMCLIENT_DM_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem DataManager Config encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_DM_GENERAL_FAILURE ((EMS_RESULT)0x8004F523L)

//
// MessageId: MEOSYSTEMCLIENT_SERVICES_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem WinServices Config encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SERVICES_PARSE_FAILURE ((EMS_RESULT)0x8004F524L)

//
// MessageId: MEOSYSTEMCLIENT_SERVICES_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem WinServices Config encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SERVICES_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F525L)

//
// MessageId: MEOSYSTEMCLIENT_SERVICES_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem WinServices Config encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_SERVICES_GENERAL_FAILURE ((EMS_RESULT)0x8004F526L)

//
// MessageId: MEOSYSTEMCLIENT_LP_CONFIG_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LPConfig Config encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_CONFIG_PARSE_FAILURE ((EMS_RESULT)0x8004F527L)

//
// MessageId: MEOSYSTEMCLIENT_LP_CONFIG_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LPConfig Config encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_CONFIG_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F528L)

//
// MessageId: MEOSYSTEMCLIENT_LP_CONFIG_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LPConfig Config encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_CONFIG_GENERAL_FAILURE ((EMS_RESULT)0x8004F529L)

//
// MessageId: MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LP Params Config encountered a configuration parsing exception.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_FAILURE ((EMS_RESULT)0x8004F52AL)

//
// MessageId: MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LP Params Config encountered a schema exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F52BL)

//
// MessageId: MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_GENERAL_FAILURE
//
// MessageText:
//
// Configuration Client for MeoSystem LP Params Config encountered an exception while parsing configuration.  Details:  %1.
//
#define MEOSYSTEMCLIENT_LP_PARAMS_CONFIG_GENERAL_FAILURE ((EMS_RESULT)0x8004F52CL)


#endif // INC_CONFIGCLIENT_MSGS
/*******************************************************************************
*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/
#ifndef INC_INTERNAL_MODEL_MSGS
#define INC_INTERNAL_MODEL_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: INTMODEL_BASE_CODE
//
// MessageText:
//
// Internal Model
//
#define INTMODEL_BASE_CODE               ((EMS_RESULT)0x8004F550L)

//
// MessageId: MEOINTERNALMODEL_PARSING_FAILURE
//
// MessageText:
//
// MeoLut Internal Model encountered %1 exception.  Details:  %2.
//
#define MEOINTERNALMODEL_PARSING_FAILURE ((EMS_RESULT)0x8004F551L)

//
// MessageId: MEOINTERNALMODEL_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// MeoLut Internal Model encountered a schema exception while parsing %1.  Details:  %2.
//
#define MEOINTERNALMODEL_PARSE_SCHEMA_FAILURE ((EMS_RESULT)0x8004F552L)

//
// MessageId: MEOINTERNALMODEL_GENERAL_FAILURE
//
// MessageText:
//
// MeoLut Internal Model encountered a general exception while parsing %1.  Details:  %2.
//
#define MEOINTERNALMODEL_GENERAL_FAILURE ((EMS_RESULT)0x8004F553L)


#endif // INC_INTERNAL_MODEL_MSGS
/***************************************************************************
*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
****************************************************************************/
#ifndef INC_TRACKING_SCHEDULER_MSGS
#define INC_TRACKING_SCHEDULER_MSGS

#ifndef INC_EMSERROR
#include "emserror.h"
#endif

//
// MessageId: EMS_TS_BASE_CODE
//
// MessageText:
//
// EMS Tracking Scheduler error.
//
#define EMS_TS_BASE_CODE                 ((EMS_RESULT)0x8004F600L)

//
// MessageId: EMS_TS_STARTED
//
// MessageText:
//
// EMS Tracking Scheduler has started.
//
#define EMS_TS_STARTED                   ((EMS_RESULT)0x0004F601L)

//
// MessageId: EMS_TS_START_FAILED
//
// MessageText:
//
// EMS Tracking Scheduler failed to start with error code %1.
//
#define EMS_TS_START_FAILED              ((EMS_RESULT)0x8004F602L)

//
// MessageId: EMS_TS_STOPPED
//
// MessageText:
//
// EMS Tracking Scheduler has stopped.
//
#define EMS_TS_STOPPED                   ((EMS_RESULT)0x0004F603L)

//
// MessageId: EMS_TS_CONFIG_FAILED
//
// MessageText:
//
// EMS Tracking Scheduler failed to get a configuration from configWS.
//
#define EMS_TS_CONFIG_FAILED             ((EMS_RESULT)0x8004F604L)

//
// MessageId: EMS_TS_NO_CONFIG
//
// MessageText:
//
// EMS Tracking Scheduler retrieved an empty configuration change notification from configWS.
//
#define EMS_TS_NO_CONFIG                 ((EMS_RESULT)0x8004F605L)

//
// MessageId: EMS_TS_RECS_RECEIVED
//
// MessageText:
//
// EMS Tracking Scheduler has received satellite track records.
//
#define EMS_TS_RECS_RECEIVED             ((EMS_RESULT)0x0004F606L)

//
// MessageId: EMS_TS_RECS_SENT
//
// MessageText:
//
// EMS Tracking Scheduler has sent %1 satellite track records to FP with URL %2.
//
#define EMS_TS_RECS_SENT                 ((EMS_RESULT)0x0004F607L)

//
// MessageId: EMS_TS_GET_FAILURE
//
// MessageText:
//
// EMS Tracking Scheduler encountered error (%1) while attempting to retrieve the current schedule from FP (%2).
//
#define EMS_TS_GET_FAILURE               ((EMS_RESULT)0x8004F608L)

//
// MessageId: EMS_TS_NO_FP_CONFIG
//
// MessageText:
//
// EMS Tracking Scheduler did not find a reference to an FP configuration file in the Tracking scheduler configuration.  As a result, the Tracking Scheduler will not manage any FPs.
//
#define EMS_TS_NO_FP_CONFIG              ((EMS_RESULT)0x0004F609L)

//
// MessageId: EMS_FP_GETLIST_FAIL
//
// MessageText:
//
// EMS Tracking Scheduler encountered error (%1) on call to FP (URL=%2) for its list of managed antennas.
//
#define EMS_FP_GETLIST_FAIL              ((EMS_RESULT)0x8004F60AL)

//
// MessageId: EMS_FP_SETSCHEDULE_FAIL
//
// MessageText:
//
// EMS Tracking Scheduler encountered error (%1) on call to FP (URL=%2) to set a schedule for antenna (%3).
//
#define EMS_FP_SETSCHEDULE_FAIL          ((EMS_RESULT)0x8004F60BL)

//
// MessageId: EMS_FP_SETSCHEDULE_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler successfully sent a Tracking schedule to FP (URL=%1) with (%2) passes for antenna (%3).
//
#define EMS_FP_SETSCHEDULE_SUCCEED       ((EMS_RESULT)0x0004F60CL)

//
// MessageId: EMS_FP_GETSCHEDULE_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler successfully received (%1) pass schedule records from FP (URL=%2) managing (%3) antennas.
//
#define EMS_FP_GETSCHEDULE_SUCCEED       ((EMS_RESULT)0x0004F60DL)

//
// MessageId: EMS_TS_SCHEDINIT_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has initialized a scheduler with lutid = %1, runningmode=%2, startup=%3, trackandscan=%4, duration=%5 hours, checkperiod=%6 minutes, pre-pass=%7 seconds, post-pass=%8 seconds.
//
#define EMS_TS_SCHEDINIT_SUCCEED         ((EMS_RESULT)0x0004F60EL)

//
// MessageId: EMS_TS_SCHEDINIT2_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has initialized a scheduler with max_leo_duration=%1 minutes, max_geo_duration=%2 minutes, max_meo_duration=%3 minutes for satellites=(%4).
//
#define EMS_TS_SCHEDINIT2_SUCCEED        ((EMS_RESULT)0x0004F60FL)

//
// MessageId: EMS_TS_EXTERNAL_INSTALL_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has installed a schedule that was received from an external source.
//
#define EMS_TS_EXTERNAL_INSTALL_SUCCEED  ((EMS_RESULT)0x0004F610L)

//
// MessageId: EMS_TS_UPDATE_FROM_FPS_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has initialized its managed schedule from FP(s) under its control.
//
#define EMS_TS_UPDATE_FROM_FPS_SUCCEED   ((EMS_RESULT)0x0004F611L)

//
// MessageId: EMS_TS_GENERATE_INSTALL_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has generated a new schedule and installed it on the FP(s) under its control.
//
#define EMS_TS_GENERATE_INSTALL_SUCCEED  ((EMS_RESULT)0x0004F612L)

//
// MessageId: EMS_TS_INIT_OUTPUT_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler will output schedule listings to file:  (%1).
//
#define EMS_TS_INIT_OUTPUT_SUCCEED       ((EMS_RESULT)0x0004F613L)

//
// MessageId: EMS_TS_MAX_RECS_FAILURE
//
// MessageText:
//
// EMS Tracking Scheduler has reached the maximum capacity (%1 satellite pass records) while generating a schedule.
//
#define EMS_TS_MAX_RECS_FAILURE          ((EMS_RESULT)0x8004F614L)

//
// MessageId: EMS_FP_MAX_RECS_WARN
//
// MessageText:
//
// EMS Tracking Scheduler has retrieved an FP's pass schedule where the number of entries matches the maximum (%1) that the scheduler can handle.  The FP may actually have a schedule with more records than the scheduler can manage.
//
#define EMS_FP_MAX_RECS_WARN             ((EMS_RESULT)0x8004F615L)

//
// MessageId: EMS_TS_LOCAL_COMMAND_EXECUTED
//
// MessageText:
//
// EMS Tracking Scheduler has processed a command to enter into local scheduling mode.
//
#define EMS_TS_LOCAL_COMMAND_EXECUTED    ((EMS_RESULT)0x0004F616L)

//
// MessageId: EMS_TS_NOMINAL_COMMAND_EXECUTED
//
// MessageText:
//
// EMS Tracking Scheduler has processed a command to enter into nominal scheduling mode.
//
#define EMS_TS_NOMINAL_COMMAND_EXECUTED  ((EMS_RESULT)0x0004F617L)

//
// MessageId: EMS_TS_BACKUP_COMMAND_EXECUTED
//
// MessageText:
//
// EMS Tracking Scheduler has processed a command to enter into backup scheduling mode.
//
#define EMS_TS_BACKUP_COMMAND_EXECUTED   ((EMS_RESULT)0x0004F618L)

//
// MessageId: EMS_TS_COMMAND_FAILED
//
// MessageText:
//
// EMS Tracking Scheduler failed to process a command.
//
#define EMS_TS_COMMAND_FAILED            ((EMS_RESULT)0x8004F619L)

//
// MessageId: EMS_TS_COMMAND_FAILED2
//
// MessageText:
//
// EMS Tracking Scheduler failed to process a command with error code %1.
//
#define EMS_TS_COMMAND_FAILED2           ((EMS_RESULT)0x8004F61AL)

//
// MessageId: EMS_TS_LOCAL_MODE_RECEIVED
//
// MessageText:
//
// EMS Tracking Scheduler has received a configuration to run in local mode.
//
#define EMS_TS_LOCAL_MODE_RECEIVED       ((EMS_RESULT)0x0004F61BL)

//
// MessageId: EMS_TS_NOMINAL_MODE_RECEIVED
//
// MessageText:
//
// EMS Tracking Scheduler has received a configuration to run in nominal mode.
//
#define EMS_TS_NOMINAL_MODE_RECEIVED     ((EMS_RESULT)0x0004F61CL)

//
// MessageId: EMS_TS_BACKUP_MODE_RECEIVED
//
// MessageText:
//
// EMS Tracking Scheduler has received a configuration to run in backup mode.
//
#define EMS_TS_BACKUP_MODE_RECEIVED      ((EMS_RESULT)0x0004F61DL)

//
// MessageId: EMS_TS_UNSOPPORTED_CONF_CHANGE_RECEIVED
//
// MessageText:
//
// EMS Tracking Scheduler received an unsupported mode: %1.
//
#define EMS_TS_UNSOPPORTED_CONF_CHANGE_RECEIVED ((EMS_RESULT)0x8004F61EL)

//
// MessageId: EMS_TS_RECEIVED_EMPTY_CONF_CHANGE
//
// MessageText:
//
// EMS Tracking Scheduler received an empty configuration change notification.
//
#define EMS_TS_RECEIVED_EMPTY_CONF_CHANGE ((EMS_RESULT)0x8004F61FL)

//
// MessageId: EMS_TS_PARSING_FAILURE
//
// MessageText:
//
// EMS Tracking Scheduler failed to parse configuration change notification: %1.
//
#define EMS_TS_PARSING_FAILURE           ((EMS_RESULT)0x8004F620L)

//
// MessageId: EMS_TS_PROCESSING_NEW_MODE
//
// MessageText:
//
// EMS Tracking Scheduler is processing the received mode: %1 (1=Nominal 2=Backup 3=Local).
//
#define EMS_TS_PROCESSING_NEW_MODE       ((EMS_RESULT)0x0004F621L)

//
// MessageId: EMS_TS_LOG_EXCEPTION
//
// MessageText:
//
// EMS Tracking Scheduler reports that an exception report was received from: %1.
//
#define EMS_TS_LOG_EXCEPTION             ((EMS_RESULT)0x0004F622L)

//
// MessageId: EMS_TS_PARSE_FAILURE
//
// MessageText:
//
// Tracking Scheduler was unable to parse %1. This is most likely due to a format error in %2. Error:  %3.
//
#define EMS_TS_PARSE_FAILURE             ((EMS_RESULT)0x8004F623L)

//
// MessageId: EMS_TS_PARSE_SCHEMA_FAILURE
//
// MessageText:
//
// Tracking Scheduler was unable to parse %1. This may be due to a format error in %2 or an error in the schema definition. Error:  %3.
//
#define EMS_TS_PARSE_SCHEMA_FAILURE      ((EMS_RESULT)0x8004F624L)

//
// MessageId: EMS_TS_GENERAL_FAILURE
//
// MessageText:
//
// Tracking Scheduler was unable to parse %1. Error details:  %2.
//
#define EMS_TS_GENERAL_FAILURE           ((EMS_RESULT)0x8004F625L)

//
// MessageId: EMS_TS_SENT_TP_TOAMQ
//
// MessageText:
//
// EMS Tracking Scheduler sent Tracking Plan to ActiveMQ topic: %1.
//
#define EMS_TS_SENT_TP_TOAMQ             ((EMS_RESULT)0x0004F626L)

//
// MessageId: EMS_TS_CONSUMER_NOT_CONNECTED
//
// MessageText:
//
// Tracking Scheduler Service reports that it could not connect to the Message Queue for receipt of %1 messages. Processing will continue, but messages will not be received.
//
#define EMS_TS_CONSUMER_NOT_CONNECTED    ((EMS_RESULT)0x0004F627L)

//
// MessageId: EMS_TS_RECEIVED_INACTIVE_TP
//
// MessageText:
//
// Tracking Scheduler - %1 Tracking Plan that has Active field set to %2.
//
#define EMS_TS_RECEIVED_INACTIVE_TP      ((EMS_RESULT)0x0004F628L)

//
// MessageId: EMS_TS_INSTALL_LOCAL_SUCCEED
//
// MessageText:
//
// EMS Tracking Scheduler has loaded local schedule and installed it on the FP(s) under its control.
//
#define EMS_TS_INSTALL_LOCAL_SUCCEED     ((EMS_RESULT)0x0004F629L)


#endif 
