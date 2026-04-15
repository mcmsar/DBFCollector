//! @file LPCConfigConstants.h
//! Constants used to access LPC configuration data
/********************************************************************
*	Module:			LPCConfigConstants.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
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

	0.0	2003Oct29		CH		First draft

********************************************************************/

#ifndef __LPC_CONFIG_CONSTANTS_H__
#define __LPC_CONFIG_CONSTANTS_H__

// Group Name(s)
static const wchar_t* cwszLPCGroupType  = L"PRO";
static const wchar_t* cwszLPCGroupID  = c_pwcsNoGroupID;

// Key(s)

//		General
static const wchar_t* cwszLPCDataDirectory = L"LPC.DataDirectory";
static const wchar_t* cwszLPCControlFileDirectory = L"LPC.ControlFileDirectory";
static const wchar_t* cwszLPCLastSessionID = L"LPC.LastSessionID";
static const wchar_t* cwszLPCMaxSessionID = L"LPC.MaxSessionID";
static const wchar_t* cwszLPCMaxRecordCount = L"LPC.MaxRecordCount";
//		Automatic processing
static const wchar_t* cwszLPCAutoDataExpiryMinutes = L"LPC.AutoProcessing.DataExpiryMinutes";
static const wchar_t* cwszLPCAutoProcessingFrequency = L"LPC.AutoProcessing.ProcessingFrequency";
static const wchar_t* cwszLPCCalib406DefaultControlFile = L"LPC.AutoProcessing.Calib406.DefaultControlFile";
static const wchar_t* cwszLPCCombine406DefaultControlFile = L"LPC.AutoProcessing.Combine406.DefaultControlFile";
//		Manual processing
static const wchar_t* cwszLPCManualDataExpiryMinutes = L"LPC.ManualProcessing.DataExpiryMinutes";
static const wchar_t* cwszLPCManualMaxActiveSessions = L"LPC.ManualProcessing.MaxActiveSessions";
static const wchar_t* cwszLPCManualDefaultControlFile = L"LPC.ManualProcessing.DefaultControlFile";

#endif	// __LPC_CONFIG_CONSTANTS_H__