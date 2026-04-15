/********************************************************************
*	Module:				EMSEnvir.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface Definitions for Environment Monitor Objects			  	
*						
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	   Copyright (c) 2000 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	00/11/13		rvw	start

********************************************************************/
#ifndef INC_EMSENVIR
#define INC_EMSENVIR

#include "emscom.h"

#ifdef __cplusplus
struct FAR IEMSEnvironMonitor;
struct FAR IEMSWeatherMonitorDevice;
#endif

typedef struct IEMSEnvironMonitor FAR *LPEMSENVIRONMONITOR;
typedef struct IEMSWeatherMonitorDevice FAR *LPEMSWEATHERMONITORDEVICE;

// {FF9BCC61-BC90-11d4-9448-005004583B6B}
DEFINE_GUID(CLSID_EMSEnvironMonitor, 0xff9bcc61, 0xbc90, 0x11d4, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

// {FF9BCC62-BC90-11d4-9448-005004583B6B}
DEFINE_GUID(IID_IEMSEnvironMonitor, 0xff9bcc62, 0xbc90, 0x11d4, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

// {2D017641-BA44-11d4-9448-005004583B6B}
DEFINE_GUID(CLSID_EMSOmegaWeatherMonitorDevice, 0x2d017641, 0xba44, 0x11d4, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

// {2D017642-BA44-11d4-9448-005004583B6B}
DEFINE_GUID(IID_IEMSWeatherMonitorDevice, 0x2d017642, 0xba44, 0x11d4, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

#undef INTERFACE
#define INTERFACE IEMSWeatherMonitorDevice

DECLARE_INTERFACE_(IEMSWeatherMonitorDevice, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;

	STDMETHOD(Init)				 	(THIS_ DWORD dwOptions ) PURE;
	STDMETHOD(Reset)				 	(THIS ) PURE;
	STDMETHOD(GetDeviceInfo)		(THIS_ LPSTR lpszInfo, WORD wMaxLen, LPWORD lpwLen ) PURE;

	STDMETHOD(GetInsideTemp) 		(THIS_ LPWORD lpwTemperature) PURE;
	STDMETHOD(GetOutsideTemp)		(THIS_ LPWORD lpwTemperature) PURE;
	STDMETHOD(GetWindSpeed)			(THIS_ LPWORD lpwSpeed) PURE;
	STDMETHOD(GetWindDirection) 	(THIS_ LPWORD lpwDirection) PURE;
	STDMETHOD(GetRainfall) 			(THIS_ LPWORD lpwRainfall) PURE;
	STDMETHOD(GetWindChill) 		(THIS_ LPWORD lpwTemperature) PURE;
};

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IEMSWeatherMonitorDevice_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IEMSWeatherMonitorDevice_AddRef(p)					(p)->lpVtbl->AddRef(p)
#define IEMSWeatherMonitorDevice_Release(p)				(p)->lpVtbl->Release(p)
#else
#define IEMSWeatherMonitorDevice_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IEMSWeatherMonitorDevice_AddRef(p)					(p)->AddRef()
#define IEMSWeatherMonitorDevice_Release(p)				(p)->Release()
#endif // !defined(__cplusplus) || (defined(CINTERFACE)


#undef INTERFACE
#define INTERFACE IEMSEnvironMonitor

DECLARE_INTERFACE_(IEMSEnvironMonitor, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;

	STDMETHOD(Init)				 	(THIS_ DWORD dwOptions ) PURE;
	STDMETHOD(Reset)				 	(THIS ) PURE;
};

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IEMSEnvironMonitor_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IEMSEnvironMonitor_AddRef(p)					(p)->lpVtbl->AddRef(p)
#define IEMSEnvironMonitor_Release(p)				(p)->lpVtbl->Release(p)
#else
#define IEMSEnvironMonitor_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IEMSEnvironMonitor_AddRef(p)					(p)->AddRef()
#define IEMSEnvironMonitor_Release(p)				(p)->Release()
#endif // !defined(__cplusplus) || (defined(CINTERFACE)


#endif // INC_EMSENVIR
