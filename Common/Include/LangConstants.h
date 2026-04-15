/********************************************************************
*	Module:			LangConstants.h
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

#ifndef _EMSLANGCONSTANTS_HDR
#define _EMSLANGCONSTANTS_HDR

#include <wchar.h>

typedef enum _tagEMSAppEnum
{
	EMSAPP_INVALID			= -1,
	EMSAPP_Min				= 0,
	EMSAPP_ACTIVEBEACONLIST	= 0,
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
	EMSAPP_LPI				= 17,
	EMSAPP_Max				= 17
} EMSAPP;
#define ISVALID_EMSAPP( a )  (a >= EMSAPP_Min && a <= EMSAPP_Max)

typedef enum _tagEMSAppTypeEnum
{
	EMSAPPTYPE_INVALID		= -1,
	EMSAPPTYPE_Min			= 0,
	EMSAPPTYPE_OI			= 0,
	EMSAPPTYPE_SERVICE		= 1,
	EMSAPPTYPE_Max			= 1
} EMSAPPTYPE;
#define ISVALID_EMSAPPTYPE( a )  (a >= EMSAPPTYPE_Min && a <= EMSAPPTYPE_Max)

typedef struct _tagEMSAppRes
{
	EMSAPP			eTheApp;
	EMSAPPTYPE		eAppType;	  // Used to determine which registry key to look at
	const wchar_t*	wszGUIResDLL; // generated via Visual Studio resource editor
	const wchar_t*	wszStringDLL; // generated from an MC file
} EMSAppResStruct;

// WARNING: This array is indexed by the EMSAPP enum
extern const EMSAppResStruct g_aAppResources[];

typedef enum _tagEMSLangEnum
{
	EMSLANG_INVALID			= -1,
	EMSLANG_Min				= 0,
	EMSLANG_DEFAULT			= 0,
	EMSLANG_USENGLISH		= 0,
	EMSLANG_TURKISH			= 1,
	EMSLANG_SPANISHMODERN	= 2,
	EMSLANG_NONE			= 3,
	EMSLANG_Max				= 3,
} EMSLANG;
#define ISVALID_EMSLANG( a )  (a >= EMSLANG_Min && a <= EMSLANG_Max)

typedef struct _tagEMSLangConst
{
	EMSLANG			eTheLanguage;
	unsigned long	ulLangID;
	const wchar_t*	wszAbbrev;
	const wchar_t*	wszLocale;
} EMSLangConstStruct;

// WARNING: This array is indexed by the EMSLANG enum
extern const EMSLangConstStruct g_aLangConstants[];

#endif // _EMSLANGCONSTANTS_HDR

