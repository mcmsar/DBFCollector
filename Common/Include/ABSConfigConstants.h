
#ifndef __ABS_CONFIG_CONSTANTS_H__
#define __ABS_CONFIG_CONSTANTS_H__

#include <windows.h>  // for TEXT() macro

// Group Name(s)
static const wchar_t* cwszABSGroup  = L"ABS";

// Key(s)
static const wchar_t* cwszBeaconAgeout = L"ABS.Beacon.Ageout";
static const wchar_t* cwszSubstituteAgeout = L"ABS.Substitute.Ageout";
static const wchar_t* cwszIgnoreConfirmationRules = L"ABS.IgnoreConfirmationRules";
static const wchar_t* cwszMsgForceUpdate = L"ABS.Msg.ForceUpdate";
static const wchar_t* cwszMsgMaxInterval = L"ABS.Msg.MaxInterval";
static const wchar_t* cwszMsgMinInterval = L"ABS.Msg.MinInterval";
static const wchar_t* cwszProcessLocate = L"ABS.ProcessLocate";
static const wchar_t* cwszMsgProcessCalib406 = L"ABS.ProcessCalib406";
static const wchar_t* cwszMaximumCapacity = L"ABS.MaximumCapacity";
static const wchar_t* cwszSITTransmitRate = L"ABS.SIT.TransmitRate";

static const wchar_t* cwszMaxTimeStdDev = L"ABS.Locate.MaxTimeStdDev";
static const wchar_t* cwszMaxFreqStdDev = L"ABS.Locate.MaxFreqStdDev";
static const wchar_t* cwszLcnMaxHDOP = L"ABS.Locate.MaxHDOP";
static const wchar_t* cwszLcnProximityThreshold = L"ABS.Locate.ProximityThreshold";
static const wchar_t* cwszSubstituteReplaceMaxFSErr = L"ABS.Msg.MaxFSErr";
static const wchar_t* cwszSubstituteReplaceMaxPDF1Err = L"ABS.Msg.MaxPDF1Err";
static const wchar_t* cwszSubstituteReplaceMaxPDF2Err = L"ABS.Msg.MaxPDF2Err";
static const wchar_t* cwszRefBcnLAWarning = L"ABS.RefBcn.LAWarning";
static const wchar_t* cwszRefBcnLAAlarm = L"ABS.RefBcn.LAAlarm";
static const wchar_t* cwszUpdatePeriod = L"ABS.UpdatePeriod";
static const wchar_t* cwszPrimeOnStart = L"ABS.PrimeOnStart";
static const wchar_t* cwszMaxClusterRadius = L"ABS.Locate.MaxClusterRadius";
static const wchar_t* cwszMinTotalSats = L"ABS.Locate.MinTotalSats";
static const wchar_t* cwszMinGEOSats = L"ABS.Locate.MinGEOSats";
static const wchar_t* cwszMinLEOSats = L"ABS.Locate.MinLEOSats";
static const wchar_t* cwszMinMEOSats = L"ABS.Locate.MinMEOSats";

#endif	// __ABS_CONFIG_CONSTANTS_H__

