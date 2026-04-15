/********************************************************************
*	Module:			LeoDefns.h
*	Process ID: 
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Defines for LeoLut600 Processes
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
#ifndef INC_LEODEFNS
#define INC_LEODEFNS

#include "emstypes.h"
#include "emstypex.h"

#define LEO_MASTER_COMMANDS		(5)
#define LEO_COLLECTOR_COMMANDS	(10)
#define LEO_WIDEBAND_COMMANDS	(12)
#define LEO_CALIBRATE_COMMANDS	(14)
#define LEO_CALIBRATE_CBC_COMMANDS	(15)
#define LEO_LOCATE_COMMANDS		(16)
#define LEO_LOCN_ANALYSIS_COMMANDS		(17)
#define LEO_ANTENNA_COMMANDS		(18)
#define LEO_DBJOURNAL_COMMANDS 	(20)	  
#define LEO_ORBIT_DETERMINATION_COMMANDS  (22)	  
#define LEO_COMMS_COMMANDS		(23)
#define LEO_SITGEN_COMMANDS		(24)
#define LEO_SYSTEST_COMMANDS		(25)
#define LEO_TCAL_COMMANDS			(26)
#define LEO_COMBINE_406_COMMANDS (27)



#define LUT_AUDIO_COMMANDS		(30)
#define LUT_DATA_MANAGER_COMMANDS		(31)
#define LUT_GATEWAY_COMMANDS		(40)

#define LUT_DAC_COMMANDS			(50)
#define LUT_DAL_COMMANDS			(51)
#define LUT_ALERTGEN_COMMANDS		(52)
#define LUT_DATATRANSFER_COMMANDS	(53)
#define LUT_LPC_COMMANDS			(54)
#define LUT_CM_COMMANDS				(55)

#define GEO_CALIBRATE_COMMANDS	(60)
#define GEO_ACTIVE_BEACON_COMMANDS	(61)

//CLOP Commands
#define CLOP_DATAREADER_COMMANDS		(105)
#define CLOP_MASTER_COMMANDS			(110)


#define LEO_LOG_DATA				(3)
#define LEO_MAINT_LOG_DATA 		(4)
#define LEO_ANTENNA_DATA			(14)
#define LEO_SOLUTION_DATA			(15)
#define LEO_SAT_TRACK_PASS_DATA (16)
#define LUT_SAT_TRACK_PASS_DATA (17)

// output by wideband process
#define LEO_CBC_DATA				(20)
#define LEO_SARR_DATA				(21)
#define LEO_SARP_DATA				(22)
#define LEO_AUDIO_DATA				(23)
#define LEO_SPECTRUM_DATA		  	(24)
#define LEO_TRACK_DATA		  		(25)
#define LEO_TLE_DATA				(26)
#define LEO_SARP_CALIB_DATA 		(27)
#define LEO_TCAL_DATA				(LEO_SARP_CALIB_DATA)

// output by the Calibrate406 process
#define LEO_CALIBRATE_406_DATA 	(28)
#define LEO_SARR_CALIB_DATA		(29)

// output by CBC calibration process
#define LEO_CBC_OUTPUT_DATA		(30)

// used by Combine 406 process
#define LEO_GEOSARR_DATA			( 32 )
#define LEO_COMBINE_406_DATA		( 33 )

#define LEO_CALIBRATE_406EX_DATA 	(34)
#define LEO_CALIBRATE_406_2_DATA 	(35)
#define MEO_CALIBRATE_406EX_DATA 	(36)

// output by location processor ( both 406 & CBC )
#define LEO_LOCATE_DATA			(40)
#define LEO_RESIDUAL_DATA		(41)
#define LEO_LOCATEEX_DATA       (42)

#define LEO_406_INPUT_DATA		(51)
#define LEO_406_OUTPUT_DATA		(52)

#define LEO_STATUS_DATA			(60)
#define LEO_ALARM_DATA 			(61)

#define LUT_CONFIG_DATA			(70)
#define LUT_AUDIO_REQ			(71)
#define LUT_AUDIO_REPLY			(72)
#define LUT_AUDIO_DATA_RIFF		(73)

#define LUT_HEALTH_STATUS		(74)
#define LUT_HEALTH_DETECTIONS	(75)

#define LUT_BEACON_ADVISORY_DATA	(76)

#define LUT_SIT_DATA				(80)	// channel for union of SIT data

#define GEO_ACTIVE_BEACON_DATA	( 250 )	// Header for Geo Active Beacon Data
#define GEO_BEACON_MANAGER_DATA	( 251 )	// Header for Geo Active Beacon Manager

// Return data for DAL::GetData
#define LUT_DAL_DATA			(90)

// Return data for LPC
#define LUT_LPC_INIT_DATA		(91)	// InitManualProcessing
#define LUT_LPC_PROCESS406_DATA	(92)	// Proces406

static const long cs_lSizeFileNameString = 128;	// The size in bytes of filename strings returned on the 
												// LUT_LPC_CTRL_FILENAMES channel.
#define LUT_LPC_CTRL_FILENAMES	(93)	// GetControlFilenames

// Input for DAC::SendData2
#define LUT_DAC_DATA			(94)

// Commands (in data format) for the Command & Control subsystem
#define LUT_CC_DATA				(95)

// Response to Get config request from Gateway
#define LUT_CONFIG_GET			(96)

// Response to GetData DAL request from Gateway -- raw data
#define LUT_DAL_GET_DATA		(97)
// Response to GetData DAL request from Gateway -- meta data
#define LUT_DAL_GET_META		(98)

#define LUT_DAL_GET_DATA_MAX	(1024)	// Maximum block size of data written back to Gtwy from DAL.

// Data channel for supplying CC subystem
// with Alert Genration requests.
#define LUT_CC_ALERT_DATA		(99)

// Used by Gateway to send queries to the DAL.
// Can't use Command Channel because the Command processor uses
// "," and "=" as delimiters.  These characters could be part of the
// query string.
#define LUT_DAL_GET_DATA_REQUEST (100)

#define LUT_IPSTATUS_DATA	(101)

#define LUT_SARREXT_DATA	(110)

// ABL (for active beacons list)
#define LUT_ABL_DATA	(130)

// Orbit (in EMSTLERECORD format) for the Orbit Manager Service
#define MEO_OMGR_TLE_DATA	(140)

#define	MEO_SGB_DATA_PIPE	(141)
#define	MEO_SGB_DATA_MQ		(142)


#endif	// INC_LEODEFNS


