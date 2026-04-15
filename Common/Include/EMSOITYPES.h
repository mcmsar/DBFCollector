///////////////////////////////////////////////////////////////////////////////
//  EMSOITYPES.h
//
//  PATH: C:\Dev\include
//
//  CREATED: 1/29/2003 2:16:57 PM by Christiaan Burchell
//
//  PURPOSE:  Common Types for the Operator Interface
//
//  COPYRIGHT NOTICE: Copyright (c) 2003-2005 by EMS Technologies, Inc., All rights reserved
//
//  LAST CHANGED: $Date$
//
//  REVISION HISTORY:
//  $Log$

// 

#ifndef __EMSOITYPES_H__
#define __EMSOITYPES_H__
#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#endif
#include "EMSTIME.H"
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <comdef.h>
#include "emslinfo.h"
#pragma warning(push)
#pragma warning( disable : 4786)
#pragma warning( disable : 4663)
#pragma warning( disable : 4100)
#pragma warning( disable : 4018)
#include <string>
#pragma warning(pop)


typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
        std::allocator<TCHAR> > tstring;

#ifdef _DEBUG
    #define ARG_UNUSED(value) value;
#else
    #define ARG_UNUSED(value)
#endif

#define EMSTRACE EMSTRACE0
#define EMSTRACE_BUFFER_SIZE 1024

#define EMS_FORCEDEBUGOUTPUT	1
#ifdef EMS_FORCEDEBUGOUTPUT
	#define EMSTRACE0(szParam1) OutputDebugString(szParam1)
    #define EMSTRACE1(szParam1,szParam2) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2);OutputDebugString(szTemp);}
	#define EMSTRACE2(szParam1,szParam2,szParam3) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2,szParam3);OutputDebugString(szTemp);}
	#define EMSTRACE3(szParam1,szParam2,szParam3,szParam4) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2,szParam3,szParam4);OutputDebugString(szTemp);}
#else
#ifdef _DEBUG
	#define EMSTRACE0(szParam1) OutputDebugString(szParam1)
	#define EMSTRACE1(szParam1,szParam2) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2);OutputDebugString(szTemp);}
	#define EMSTRACE2(szParam1,szParam2,szParam3) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2,szParam3);OutputDebugString(szTemp);}
	#define EMSTRACE3(szParam1,szParam2,szParam3,szParam4) {TCHAR szTemp[EMSTRACE_BUFFER_SIZE]; ::_sntprintf(szTemp,EMSTRACE_BUFFER_SIZE,szParam1,szParam2,szParam3,szParam4);OutputDebugString(szTemp);}
#else
    #define EMSTRACE0(szParam1)
	#define EMSTRACE1(szParam1,szParam2)
	#define EMSTRACE2(szParam1,szParam2,szParam3)
	#define EMSTRACE3(szParam1,szParam2,szParam3,szParam4)
#endif
#endif

#define EMS_DATE_FORMAT_DATE _T("yyyy/XXX")
#define EMS_DATE_FORMAT_TIME _T("HH:mm:ss")



enum EMSPlotTool_e
{
    EMS_PLOTTOOL_NONE=0,
    EMS_PLOTTOOL_ZOOMIN=1,
    EMS_PLOTTOOL_ZOOMOUT=2,
    EMS_PLOTTOOL_SELAUDIO=3
};

enum EMSPlotterType_e
{
    EMS_PLOTTERTYPE_NONE = 0,
    EMS_PLOTTERTYPE_SPECTROGRAM = 1,
    EMS_PLOTTERTYPE_SPECTRUM = 2,
    EMS_PLOTTERTYPE_DOTPLOT = 3,
    EMS_PLOTTERTYPE_BEACON_406 = 4,
    EMS_PLOTTERTYPE_BEACON_CBC121 =5,
    EMS_PLOTTERTYPE_BEACON_CBC243 =6
};

#define ISPLOTTERBITMAPTYPE(type) ((type) == EMS_PLOTTERTYPE_DOTPLOT || (type) == EMS_PLOTTERTYPE_SPECTROGRAM || (type) == EMS_PLOTTERTYPE_BEACON_406 || (type) == EMS_PLOTTERTYPE_BEACON_CBC121 || (type) == EMS_PLOTTERTYPE_BEACON_CBC243)

#define TOOL_AUDIO EMS_PLOTTOOL_SELAUDIO
#define TOOL_ZOOMIN EMS_PLOTTOOL_ZOOMIN
#define TOOL_ZOOMOUT EMS_PLOTTOOL_ZOOMOUT


inline double _ttod(const TCHAR* str)
{
    TCHAR* endstr;
    return _tcstod(str,&endstr);
}


#define WATOI

//enum EMSLUTType_e
//{
//    EMS_GEOLUT = 0,
//    EMS_LEOLUT = 1
//#define EMS_MAX_LUT_TYPE 2
//};

struct EMSLUT
{
    TCHAR m_Name[64];
    DWORD m_Id;
//    EMSLUTType_e m_Type;
    EMSLUTTYPECODE m_Type;
    TCHAR m_Description[256];
};


enum EMSState_e
{
    EMSState_Ok = 0,
    EMSState_Warn = 1,
    EMSState_Error = 2,
    EMSState_Off = 3,
    EMSState_None = 4,
    EMSState_MAX  = 5
};

struct EMSLUTSTAT
{
    EMSTIME m_LastUpdate;
    EMSState_e m_Status;
    EMSState_e m_Summary;
    EMSState_e m_AlarmState;
    EMSState_e m_PowerState;
    EMSState_e m_CollectorState;
    EMSState_e m_WidebandState;
    EMSState_e m_CalibrateState;
    EMSState_e m_LocateState;
    EMSState_e m_CommsState;
    EMSState_e m_HardwareState;
    EMSState_e m_AntennaState;
    EMSState_e m_PassState;
    EMSState_e m_EnvironmentState;
};

struct EMSPASSDATA
{
    DWORD m_LutID;
    DWORD m_SatID;
    DWORD m_PassID;
    CEMSTime m_TimeAOS;
    CEMSTime m_TimeLOS;
};

//const TCHAR* EMSOIType_GetTypeStr(EMSLUTType_e type);
const TCHAR* EMSOIType_GetTypeStr( EMSLUTTYPECODE type );

const TCHAR* EMSOIType_GetStateStr(EMSState_e type);

const DWORD EMSOIType_GetStateColour(EMSState_e type);

#define PrintComError(e) _PrintComError(__FILE__,__LINE__,e)
void _PrintComError(const char* file,const int line,_com_error &e);

//#define EMS_OI_DATABASE_TEST

////////////////////////////////////////////////
//
// NAME: CreateConnectionString
//
// DESCRIPTION: Gets a DSN from a Lut ID
//
// CREATED:     1/27/2003 2:19:51 PM
//
// PARAMETERS: 
//             DWORD LutID : the Lut ID
//             char* buffer : buffer to output the DSN
//             DWORD MaxSize : the max size of the buffer
//
// RETURN: char* 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
TCHAR* CreateConnectionString(DWORD LutID,TCHAR* buffer,DWORD MaxSize, BOOL bDatabase);

#endif //__EMSOITYPES_H__
