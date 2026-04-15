#ifndef __CONSTLUTINFO_H__
#define __CONSTLUTINFO_H__

#include <wchar.h>

static const wchar_t    c_pwcsLUTGroupType[]             = L"LUT";
static const wchar_t    c_pwcsLUTKeyName[]               = L"Name";
static const wchar_t    c_pwcsLUTKeyDescription[]        = L"Description";
static const wchar_t    c_pwcsLUTKeyType[]               = L"Type";
static const wchar_t    c_pwcsLUTKeyVersion[]            = L"Version";
static const wchar_t    c_pwcsLUTKeyLatitude[]           = L"Latitude";
static const wchar_t    c_pwcsLUTKeyLongitude[]          = L"Longitude";
static const wchar_t    c_pwcsLUTKeyAltitude[]           = L"Altitude";
static const wchar_t    c_pwcsLUTKeyHorizonElevationN[]  = L"Horizon.Elevation.";
static const wchar_t    c_pwcsLUTKeyPassSchedPriority[]  = L"PassSchedule.Priority";

static const wchar_t    c_pwcsLUTKeyAntennaCount[]  = L"Antenna.Count";
static const wchar_t    c_pwcsLUTKeyAntennaType[]  = L"Antenna.Type";
static const wchar_t    c_pwcsLUTKeyAntennaMinAz[]  = L"Antenna.MinAz";
static const wchar_t    c_pwcsLUTKeyAntennaMaxAz[]  = L"Antenna.MaxAz";
static const wchar_t    c_pwcsLUTKeyAntennaMinEl[]  = L"Antenna.MinEl";
static const wchar_t    c_pwcsLUTKeyAntennaMaxEl[]  = L"Antenna.MaxEl";
static const wchar_t    c_pwcsLUTKeyAntennaMaxDuration[]  = L"Antenna.MaxDuration";
static const wchar_t    c_pwcsLUTKeyAntennaID[]  = L"Antenna.ID";
static const wchar_t    c_pwcsLUTKeyAntennaSatIDs[]  = L"Antenna.SatIDs";

static const wchar_t    c_pwcsLUTTypeLeo600[]         = L"LeoLUT600";
static const wchar_t    c_pwcsLUTTypeGeo600[]         = L"GeoLUT600";
static const wchar_t    c_pwcsLUTTypeMeo600[]         = L"MeoLUT600";
static const wchar_t    c_pwcsLUTTypeATLut500[]       = L"ATLUT500";
static const wchar_t    c_pwcsLUTTypeOpInt600[]       = L"OpInt600";
static const wchar_t    c_pwcsLUTTypeLutServer600[]   = L"LUTSERVER";

static const wchar_t    c_pwcsLUTAntennaTypeLeo600[]         = L"LeoLUT600";
static const wchar_t    c_pwcsLUTAntennaTypeGeo600[]         = L"GeoLUT600";
static const wchar_t    c_pwcsLUTAntennaTypeMeo600[]         = L"MeoLUT600";

static const wchar_t c_pwcsLUTKeySARRCalibrationTimeFmt[]      = L"SARR.CalibrationTime.";
static const wchar_t c_pwcsLUTKeySARRFreqOffsetFmt[]           = L"SARR.FreqOffset.";
static const wchar_t c_pwcsLUTKeySARRTimeOffsetFmt[]           = L"SARR.TimeOffset.";


#endif // __CONSTLUTINFO_H__

