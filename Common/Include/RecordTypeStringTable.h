
#ifndef __RECORDTYPE_STRING_TABLE_H__
#define __RECORDTYPE_STRING_TABLE_H__

#include "dal.h"

const long EMS_RECORDTYPE_STRING_LEN = 24;

typedef struct tagEMSRecordTypeString
{
	EMSRECORDTYPE eRT;
	wchar_t wszString[ EMS_RECORDTYPE_STRING_LEN + 1 ];
} EMSRECORDTYPESTRING;

static const EMSRECORDTYPESTRING caRTToStringTable[] = {	{EMSRT_UNKNOWN, L"Unknown"},
															{EMSRT_ANTENNA, L"Antenna"},
															{EMSRT_CALIB406, L"Calib406"},
															{EMSRT_CALIBCBC, L"CalibCBC"},
															{EMSRT_CALIBCBC_STATS, L"CalibCBC Stats"},
															{EMSRT_CBC, L"CBC"},
															{EMSRT_COLLECTOR, L"Collector"},
															{EMSRT_COMB406, L"Combine406"},
															{EMSRT_COMB406_STATS, L"Combine406 Stats"},
															{EMSRT_COMMS_STATS, L"Comms Stats"},
															{EMSRT_CONFIG, L"Config"},
															{EMSRT_GEO_CALIB406_STATS, L"GEO Calib406 Stats"},
															{EMSRT_GEO_STATS, L"GEO Stats"},
															{EMSRT_LEO_CALIB406_STATS, L"LEO Calib406 Stats"},
															{EMSRT_LOCATE, L"Locate"},
															{EMSRT_LOCATE_STATS, L"Locate Stats"},
															{EMSRT_LOG, L"Log"},
															{EMSRT_ORBIT, L"Orbit"},
															{EMSRT_ORBIT_STATS, L"Orbit Stats"},
															{EMSRT_PASS_STATS, L"Pass Stats"},
															{EMSRT_RESIDUAL, L"Residual"},
															{EMSRT_SARP_CALIB, L"SARP Calib"},
															{EMSRT_SARP_CALIB_STATS, L"SARP Calib Stats"},
															{EMSRT_SARP, L"SARP"},
															{EMSRT_SARR_CALIB, L"SARR Calib"},
															{EMSRT_SARR_CALIB_STATS, L"SARR Calib Stats"},
															{EMSRT_SARR, L"SARR"},
															{EMSRT_SAT_TRACK, L"Sat Track"},
															{EMSRT_SENSOR, L"Sensor"},
															{EMSRT_SPECTRUM, L"Spectrum"},
															{EMSRT_STAT_SUMMARY, L"Status Summary"},
															{EMSRT_WIDEBAND_STATS, L"Wideband Stats"},
															{EMSRT_AUDIO, L"Audio"},
															{EMSRT_MANOEUVRE, L"Manoeuvre"},
															{EMSRT_CALIB406_2, L"Calibrate 406 v2"},
															{EMSRT_LUT_STATUS, L"Lut Status"},
															{EMSRT_LAST, L""}
														};		
#endif