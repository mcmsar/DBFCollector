/********************************************************************
*	Module:			LangConstants.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Constants used to identify which language resources
*					to load for any given application.
*					Used by CEMSLangResources
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

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
	0.0	14Jan2005		CH		Started

********************************************************************/

#include "LangConstants.h"

// WARNING: This array is indexed by the EMSAPP enum
/*		EMSAPP_ACTIVEBEACONLIST	= 0,
	EMSAPP_BEACONPLOTTER	= 1,
	EMSAPP_DATABASE			= 2,
	EMSAPP_DOTPLOT			= 3,
	EMSAPP_GRAPHER			= 4,
	EMSAPP_LUTPICKER		= 5,
	EMSAPP_OIGUI			= 6,
	EMSAPP_PASSSCHED		= 7,
	EMSAPP_SITEDITOR		= 8,
	EMSAPP_SPECTROGRAM		= 9,
	EMSAPP_SPECTRUM			= 10,
	EMSAPP_MSGTABLE			= 11,
	EMSAPP_SOLUTIONDISPLAY	= 12,
	EMSAPP_AUDIOMON			= 13,
	EMSAPP_LUTMONITOR		= 14,
	EMSAPP_STORMMANAGER		= 15,
	EMSAPP_NETCONNMANAGER	= 16,
	EMSAPP_LPI				= 17

*/
const EMSAppResStruct g_aAppResources[] =
{
	{ EMSAPP_ACTIVEBEACONLIST,	EMSAPPTYPE_OI,		L"EMSActiveBeaconListRes",	L"EMS600MsgTable" },
	{ EMSAPP_BEACONPLOTTER,		EMSAPPTYPE_OI,		L"EMSBeaconPlotterRes",		L"EMS600MsgTable" },
	{ EMSAPP_DATABASE,			EMSAPPTYPE_OI,		L"EMSDatabaseRes",			L"EMS600MsgTable" },
	{ EMSAPP_DOTPLOT,			EMSAPPTYPE_OI,		L"EMSDotPlotRes",			L"EMS600MsgTable" },
	{ EMSAPP_GRAPHER,			EMSAPPTYPE_OI,		L"EMSGrapherRes",			L"EMS600MsgTable" },
	{ EMSAPP_LUTPICKER,			EMSAPPTYPE_OI,		L"EMSLutPickerRes",			L"EMS600MsgTable" },
	{ EMSAPP_OIGUI,				EMSAPPTYPE_OI,		L"EMSOIGUIRes",				L"EMS600MsgTable" },
	{ EMSAPP_PASSSCHED,			EMSAPPTYPE_OI,		L"EMSPassSchedRes",			L"EMS600MsgTable" },
	{ EMSAPP_SITEDITOR,			EMSAPPTYPE_OI,		L"EMSSitEditorRes",			L"EMS600MsgTable" },
	{ EMSAPP_SPECTROGRAM,		EMSAPPTYPE_OI,		L"EMSSpectrogramRes",		L"EMS600MsgTable" },
	{ EMSAPP_SPECTRUM,			EMSAPPTYPE_OI,		L"EMSSpectrumRes",			L"EMS600MsgTable" },
	{ EMSAPP_MSGTABLE,			EMSAPPTYPE_SERVICE,	NULL,						L"EMS600MsgTable"},
	{ EMSAPP_SOLUTIONDISPLAY,	EMSAPPTYPE_OI,		L"EMS600SolutionDisplayRes",L"EMS600MsgTable" },
	{ EMSAPP_AUDIOMON,			EMSAPPTYPE_OI,		L"EMSOIGUIRes",				L"EMS600MsgTable" },
	{ EMSAPP_LUTMONITOR,		EMSAPPTYPE_OI,		L"EMSLUTMonitorViewRes",	L"EMS600MsgTable" },
	{ EMSAPP_STORMMANAGER,		EMSAPPTYPE_SERVICE,	NULL,						L"EMSStormMsgs" },
	{ EMSAPP_NETCONNMANAGER,	EMSAPPTYPE_SERVICE,	NULL,						L"EMSNetConnMgrMsgs" },
	{ EMSAPP_LPI,				EMSAPPTYPE_SERVICE,	L"EMSLPIRes",				L"EMS600MsgTable" },
};

// WARNING: This array is indexed by the EMSLANG enum
const EMSLangConstStruct g_aLangConstants[] =
{
	{ EMSLANG_USENGLISH,	1033, L"ENU", L"english-us" },
	{ EMSLANG_TURKISH,		1055, L"TRK", L"turkish" },
	{ EMSLANG_SPANISHMODERN,3082, L"ESN", L"spanish-modern" },
	{ EMSLANG_NONE,			0,    L"",	  NULL } // use defaults
};

