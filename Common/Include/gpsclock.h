/********************************************************************
*	Module:			gpsclock.h
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
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*	All rights reserved
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

	0.0	01/03/22		rvw	start
	0.1	02/02/22		rvw	added IEMSGpsClock2 interface

********************************************************************/

#ifndef INC_GPSCLOCK
#define INC_GPSCLOCK

#include "emscom.h"

#ifdef __cplusplus
struct FAR IEMSGpsClock;
#endif

#ifdef __cplusplus
struct FAR IEMSGpsClock2;
#endif

#ifdef __cplusplus
struct FAR IEMSGpsClock3;
#endif

typedef struct IEMSGpsClock	FAR *LPEMSGPSCLOCK;
typedef struct IEMSGpsClock2	FAR *LPEMSGPSCLOCK2;
typedef struct IEMSGpsClock3	FAR *LPEMSGPSCLOCK3;
typedef struct IEMSGpsClock4	FAR *LPEMSGPSCLOCK4;

// {F6409481-1EE1-11d5-9448-005004583B6B}
DEFINE_GUID( CLSID_EMSGpsClock, 0xf6409481, 0x1ee1, 0x11d5, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

// {F6409482-1EE1-11d5-9448-005004583B6B}
DEFINE_GUID( IID_IEMSGpsClock, 0xf6409482, 0x1ee1, 0x11d5, 0x94, 0x48, 0x0, 0x50, 0x4, 0x58, 0x3b, 0x6b);

// {DF5D38E1-2867-11d6-8DD5-009027912866}
DEFINE_GUID( IID_IEMSGpsClock2, 0xdf5d38e1, 0x2867, 0x11d6, 0x8d, 0xd5, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {64F38D3C-5C26-48ec-AEF7-C38B4A9CF491}
DEFINE_GUID( IID_IEMSGpsClock3, 0x64f38d3c, 0x5c26, 0x48ec, 0xae, 0xf7, 0xc3, 0x8b, 0x4a, 0x9c, 0xf4, 0x91);

// {E4504310-A692-487e-87A6-DD6F6255BF15}
DEFINE_GUID( IID_IEMSGpsClock4, 0xe4504310, 0xa692, 0x487e, 0x87, 0xa6, 0xdd, 0x6f, 0x62, 0x55, 0xbf, 0x15);

#define GPS_CLOCK_DEVICE_0			(0L)
#define GPS_CLOCK_DEVICE_1			(1L)
#define GPS_CLOCK_DEVICE_2			(2L)
#define GPS_CLOCK_DEVICE_3			(3L)

#define GPS_CLOCK_MODE_1PPS			(0x1)
#define GPS_CLOCK_MODE_GPS			(0x2)
#define GPS_CLOCK_MODE_TIMECODE		(0x4)

#define EMS_GPSFLAG_ANTENNA_SHORTED	( 0x01 )
#define EMS_GPSFLAG_ANTENNA_OPEN		( 0x02 )
#define EMS_GPSFLAG_LOCKED				( 0x04 )
#define EMS_GPSFLAG_POSITION_VALID		( 0x08 )
#define EMS_GPSFLAG_TIME_VALID			( 0x10 )

#undef INTERFACE
#define INTERFACE IEMSGpsClock

DECLARE_INTERFACE_(IEMSGpsClock, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;
	STDMETHOD(Open)					(THIS_ DWORD dwDevice) PURE;
	STDMETHOD(Close)					(THIS) PURE;
	STDMETHOD(ReadTime) 				(THIS_ LPEMSTIME lpEmsTime ) PURE;
	STDMETHOD(SetTime) 				(THIS_ EMSTIME emsTime ) PURE;
	STDMETHOD(GetMode) 				(THIS_ LPDWORD lpdwMode ) PURE;
	STDMETHOD(SetMode) 				(THIS_ DWORD dwMode ) PURE;
	STDMETHOD(SyncSystemClock)		( THIS ) PURE;
};

#if !defined(__cplusplus) || defined(CINTERFACE)
#define IEMSGpsClock_QueryInterface(p,a,b)	(p)->lpVtbl->QueryInterface(p,a,b)
#define IEMSGpsClock_AddRef(p)					(p)->lpVtbl->AddRef(p)
#define IEMSGpsClock_Release(p)				(p)->lpVtbl->Release(p)
#else
#define IEMSGpsClock_QueryInterface(p,a,b)	(p)->QueryInterface(a,b)
#define IEMSGpsClock_AddRef(p)					(p)->AddRef()
#define IEMSGpsClock_Release(p)				(p)->Release()
#endif // !defined(__cplusplus) || (defined(CINTERFACE)

#undef INTERFACE
#define INTERFACE IEMSGpsClock2

DECLARE_INTERFACE_( IEMSGpsClock2, IEMSGpsClock )
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;
	STDMETHOD(Open)					(THIS_ DWORD dwDevice) PURE;
	STDMETHOD(Close)					(THIS) PURE;
	STDMETHOD(ReadTime) 				(THIS_ LPEMSTIME lpEmsTime ) PURE;
	STDMETHOD(SetTime) 				(THIS_ EMSTIME emsTime ) PURE;
	STDMETHOD(GetMode) 				(THIS_ LPDWORD lpdwMode ) PURE;
	STDMETHOD(SetMode) 				(THIS_ DWORD dwMode ) PURE;
	STDMETHOD(SyncSystemClock)		( THIS ) PURE;
	STDMETHOD(GetPosition)			( THIS_ EMSLOCATION *lpLocation ) PURE;
	STDMETHOD(GetHardwareStatus)	( THIS_ DWORD *lpdwStatus ) PURE;
	STDMETHOD(GetSatelliteInfo)	( THIS_ DWORD *lpdwSatID, double *lpdSatStrength, WORD wMax, WORD *lpwCount ) PURE;
	STDMETHOD(GetVersionInfoA)		( THIS_ WORD *lpwVersion, char *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
	STDMETHOD(GetVersionInfoW)		( THIS_ WORD *lpwVersion, WCHAR *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
};

#undef INTERFACE
#define INTERFACE IEMSGpsClock3

DECLARE_INTERFACE_( IEMSGpsClock3, IEMSGpsClock2 )
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;
	// IEMSGpsClock methods
	STDMETHOD(Open)					(THIS_ DWORD dwDevice) PURE;
	STDMETHOD(Close)					(THIS) PURE;
	STDMETHOD(ReadTime) 				(THIS_ LPEMSTIME lpEmsTime ) PURE;
	STDMETHOD(SetTime) 				(THIS_ EMSTIME emsTime ) PURE;
	STDMETHOD(GetMode) 				(THIS_ LPDWORD lpdwMode ) PURE;
	STDMETHOD(SetMode) 				(THIS_ DWORD dwMode ) PURE;
	STDMETHOD(SyncSystemClock)		( THIS ) PURE;
	// IEMSGpsClock2 methods
	STDMETHOD(GetPosition)			( THIS_ EMSLOCATION *lpLocation ) PURE;
	STDMETHOD(GetHardwareStatus)	( THIS_ DWORD *lpdwStatus ) PURE;
	STDMETHOD(GetSatelliteInfo)	( THIS_ DWORD *lpdwSatID, double *lpdSatStrength, WORD wMax, WORD *lpwCount ) PURE;
	STDMETHOD(GetVersionInfoA)		( THIS_ WORD *lpwVersion, char *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
	STDMETHOD(GetVersionInfoW)		( THIS_ WORD *lpwVersion, WCHAR *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
	// IEMSGpsClock3 methods
	STDMETHOD(GetTimingPulseOffset) ( THIS_ DWORD *lpdwPulseOffset ) PURE;
};

#undef INTERFACE
#define INTERFACE IEMSGpsClock4

DECLARE_INTERFACE_( IEMSGpsClock4, IEMSGpsClock3 )
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;
	// IEMSGpsClock methods
	STDMETHOD(Open)					(THIS_ DWORD dwDevice) PURE;
	STDMETHOD(Close)					(THIS) PURE;
	STDMETHOD(ReadTime) 				(THIS_ LPEMSTIME lpEmsTime ) PURE;
	STDMETHOD(SetTime) 				(THIS_ EMSTIME emsTime ) PURE;
	STDMETHOD(GetMode) 				(THIS_ LPDWORD lpdwMode ) PURE;
	STDMETHOD(SetMode) 				(THIS_ DWORD dwMode ) PURE;
	STDMETHOD(SyncSystemClock)		( THIS ) PURE;
	// IEMSGpsClock2 methods
	STDMETHOD(GetPosition)			( THIS_ EMSLOCATION *lpLocation ) PURE;
	STDMETHOD(GetHardwareStatus)	( THIS_ DWORD *lpdwStatus ) PURE;
	STDMETHOD(GetSatelliteInfo)	( THIS_ DWORD *lpdwSatID, double *lpdSatStrength, WORD wMax, WORD *lpwCount ) PURE;
	STDMETHOD(GetVersionInfoA)		( THIS_ WORD *lpwVersion, char *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
	STDMETHOD(GetVersionInfoW)		( THIS_ WORD *lpwVersion, WCHAR *lpszModel, WORD wMax, WORD *lpwLength ) PURE;
	// IEMSGpsClock3 methods
	STDMETHOD(GetTimingPulseOffset) ( THIS_ DWORD *lpdwPulseOffset ) PURE;
	// IEMSGpsClock4 methods
	STDMETHOD(GetLastUpdateTime) ( THIS_ LPEMSTIME lpTime ) PURE;
	STDMETHOD(GetElapsedSinceLastUpdate) ( THIS_ double *lpdSeconds ) PURE;
};

#endif // INC_GPSCLOCK

