#ifndef INC_EMSMON
#define INC_EMSMON

#include <emscom.h>

// {10C19BA8-3E74-4533-B7AA-5BB2A3C0CAC6}
DEFINE_GUID(IID_IEMSMonitorQuery, 0x10c19ba8, 0x3e74, 0x4533, 0xb7, 0xaa, 0x5b, 0xb2, 0xa3, 0xc0, 0xca, 0xc6);

// {FA4BB080-6B9F-4bbe-851D-2FD0F2433022}
DEFINE_GUID(IID_IEMSMonitor, 0xfa4bb080, 0x6b9f, 0x4bbe, 0x85, 0x1d, 0x2f, 0xd0, 0xf2, 0x43, 0x30, 0x22);

// {94CFC44E-04E1-47ac-931B-577E811C574C}
DEFINE_GUID(CLSID_EMSMonitor, 0x94cfc44e, 0x4e1, 0x47ac, 0x93, 0x1b, 0x57, 0x7e, 0x81, 0x1c, 0x57, 0x4c);

typedef struct IEMSMonitorQuery FAR *LPEMSMONITORQUERY;
typedef struct IEMSMonitor FAR *LPEMSMONITOR;

#undef INTERFACE
#define INTERFACE IEMSMonitorQuery

DECLARE_INTERFACE_(IEMSMonitorQuery, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;

	STDMETHOD(Init) 					(THIS ) PURE;
	STDMETHOD(Reset) 					(THIS ) PURE;
	STDMETHOD(GetInsideTemp) 		(THIS_ LPWORD lpwTemperature) PURE;
	STDMETHOD(GetOutsideTemp)		(THIS_ LPWORD lpwTemperature) PURE;
	STDMETHOD(GetWindSpeed)			(THIS_ LPWORD lpwSpeed) PURE;
	STDMETHOD(GetWindDirection) 	(THIS_ LPWORD lpwDirection) PURE;
	STDMETHOD(GetRainfall) 			(THIS_ LPWORD lpwRainfall) PURE;
	STDMETHOD(GetWindChill) 		(THIS_ LPWORD lpwTemperature) PURE;
	STDMETHOD(GetHumidity)			(THIS_ LPWORD lpwHumidity) PURE;
	STDMETHOD(GetRain)				(THIS_ LPWORD lpwRain) PURE;
	STDMETHOD(GetDoorStatus)		(THIS_ UINT uiDoorId, LPWORD lpwDoorStatus) PURE;
	STDMETHOD(GetSmokeStatus)		(THIS_ LPWORD lpwSmokeStatus) PURE;
	STDMETHOD(GetVibrationStatus)	(THIS_ LPWORD lpwVibration) PURE;
	STDMETHOD(IsRadarParked)		(THIS_ LPUINT lpuiIsRadarParked) PURE;
	STDMETHOD(RadarNeedsParking)	(THIS_ LPUINT lpuiRadarNeedsParking) PURE;
};


#undef INTERFACE
#define INTERFACE IEMSMonitor

DECLARE_INTERFACE_(IEMSMonitor, IUnknown)
{
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *) PURE;
	STDMETHOD_(ULONG, AddRef)		(THIS) PURE;
	STDMETHOD_(ULONG, Release)		(THIS) PURE;

	STDMETHOD(DoorLock)				(THIS_ UINT uiDoorId) PURE;
	STDMETHOD(DoorUnlock)			(THIS_ UINT uiDoorId) PURE;
	STDMETHOD(DoorAccessLock)		(THIS_ UINT uiDoorId) PURE;
	STDMETHOD(DoorTimeUnlock)		(THIS_ UINT uiDoorId, THIS_ UINT uiTimeUnlock) PURE;
	STDMETHOD(ParkRadar)			(THIS) PURE;
	STDMETHOD(UnparkRadar)			(THIS) PURE;
};

#endif
