/********************************************************************
*	Module:			lutconst.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Constants
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

  0.0 03/02/04	      fjp   start

********************************************************************/
#ifndef __LUTCONST_H__
#define __LUTCONST_H__

const TCHAR c_szSiteCfgHeading[]                = TEXT("LutProcessControl");
const TCHAR c_szSectionHeading[]                = TEXT("LUT:");

const TCHAR c_szLUTID[]                         = TEXT("LutID");
const TCHAR c_szGUISelect[]                     = TEXT("Gui.Select");
const TCHAR c_szDescription[]                   = TEXT("Description");
const TCHAR c_szLatitude[]                      = TEXT("Latitude");
const TCHAR c_szLongitude[]                     = TEXT("Longitude");
const TCHAR c_szAltitude[]                      = TEXT("Altitude");

const TCHAR c_szLutType[]								= TEXT("Type");
const TCHAR c_szLutVersion[]							= TEXT("Version");

const TCHAR c_szLutTypeLeo600[]						= TEXT("LeoLUT600");
const TCHAR c_szLutTypeGeo600[]						= TEXT("GeoLUT600");
const TCHAR c_szLutTypeLeo500[]						= TEXT("ATLUT500");
const TCHAR c_szLutTypeOpInt600[]					= TEXT("OpInt600");
const TCHAR c_szLutTypeLutServer600[]			= TEXT("LUTSrv600");

const TCHAR c_szHorizonElevationFmt[]           = TEXT("Horizon.Elevation.%03i");

const TCHAR c_szServiceNames[]                  = TEXT("Service.Names");
const TCHAR c_szServiceNamesFmt[]               = TEXT("Service.Names.%i");
const TCHAR c_szServiceNameFmt[]                = TEXT("Service.%s.Name");
const TCHAR c_szServiceRestartFmt[]             = TEXT("Service.%s.Restart");

const TCHAR c_szClockDifference[]               = TEXT("Clock.Difference");
const TCHAR c_szClockCheckPeriod[]              = TEXT("Clock.Checkperiod");

const TCHAR c_szDataSend[]                      = TEXT("Send");
const TCHAR c_szDataSent[]                      = TEXT("Sent");
const TCHAR c_szDataData[]                      = TEXT("Data");
const TCHAR c_szDataReceive[]                   = TEXT("Receive");
const TCHAR c_szDataProcessed[]                 = TEXT("Processed");
const TCHAR c_szDataUndelivered[]               = TEXT("Undelivered");
const TCHAR c_szDataTransfer[]					= TEXT("Transfer");

const TCHAR c_szDataDirectory[]                 = TEXT("Data.Directory");
const TCHAR c_szDataDirectoryFmt[]              = TEXT("Data.Directory.%s");
const TCHAR c_szDataArchiveTime[]               = TEXT("Data.Archive.Time");
const TCHAR c_szDataArchiveFmt[]                = TEXT("Data.Archive.%s");

const TCHAR c_szTranslationTableNames[]         = TEXT("Translation.Tablenames");
const TCHAR c_szTranslationSit115[]             = TEXT("115");
const TCHAR c_szTranslationSit115a[]            = TEXT("115A");
const TCHAR c_szTranslationSit115b[]            = TEXT("115B");
const TCHAR c_szTranslationSit115c[]            = TEXT("115C");
const TCHAR c_szTranslationSit121[]             = TEXT("121");
const TCHAR c_szTranslationSit121a[]            = TEXT("121A");
const TCHAR c_szTranslationSit121b[]            = TEXT("121B");
const TCHAR c_szTranslationSit122[]             = TEXT("122");
const TCHAR c_szTranslationSit122a[]            = TEXT("122A");
const TCHAR c_szTranslationSit122b[]            = TEXT("122B");
const TCHAR c_szTranslationSit122c[]            = TEXT("122C");
const TCHAR c_szTranslationSit122e[]            = TEXT("122E");
const TCHAR c_szTranslationSit125[]             = TEXT("125");
const TCHAR c_szTranslationSit125a[]            = TEXT("125A");
const TCHAR c_szTranslationSit125b[]            = TEXT("125B");
const TCHAR c_szTranslationSit215[]             = TEXT("215");
const TCHAR c_szTranslationSit215a[]            = TEXT("215A");
const TCHAR c_szTranslationSit255a[]            = TEXT("255A");
const TCHAR c_szTranslationSit260a[]            = TEXT("260A");
const TCHAR c_szTranslationSit270a[]            = TEXT("270A");
const TCHAR c_szTranslationSit415[]             = TEXT("415");
const TCHAR c_szTranslationSit415a[]            = TEXT("415A");
const TCHAR c_szTranslationSit415b[]            = TEXT("415B");
const TCHAR c_szTranslationSit510[]             = TEXT("510");
const TCHAR c_szTranslationSit510a[]            = TEXT("510A");
const TCHAR c_szTranslationSit605a[]            = TEXT("60AA");
const TCHAR c_szTranslationSit605b[]            = TEXT("605B");
const TCHAR c_szTranslationSit605c[]            = TEXT("605C");
const TCHAR c_szTranslationSit605d[]            = TEXT("605D");
const TCHAR c_szTranslationSit661a[]            = TEXT("661A");
const TCHAR c_szTranslationSit661b[]            = TEXT("661B");
const TCHAR c_szTranslationSit662a[]            = TEXT("662A");
const TCHAR c_szTranslationSit750a[]            = TEXT("750A");
const TCHAR c_szTranslationSit751a[]            = TEXT("751A");
const TCHAR c_szTranslationSit760a[]            = TEXT("760A");
const TCHAR c_szTranslationSit770a[]            = TEXT("770A");
const TCHAR c_szTranslationSit915[]             = TEXT("915");
const TCHAR c_szTranslationSit925[]             = TEXT("925");
const TCHAR c_szTranslationSit950a[]            = TEXT("950A");
const TCHAR c_szTranslationSit951a[]            = TEXT("951A");
const TCHAR c_szTranslationAuto[]               = TEXT("Auto");
const TCHAR c_szTranslationRequest[]            = TEXT("Request");
const TCHAR c_szTranslationFmt[]                = TEXT("%s.Translation.%x");
const TCHAR c_szTranslationSitsFmt[]			= TEXT("%s.Translation.%s");
const TCHAR c_szTranslationElementsFmt[]		= TEXT("%s.%s");

const TCHAR c_szTranslationTimeSID[]            = TEXT("SID");
const TCHAR c_szTranslationTimeExtended[]       = TEXT("Extended");
const TCHAR c_szTranslationTimeFmt[]            = TEXT("%s.Translation.Time");


const TCHAR c_szRouteCount[]                    = TEXT("Route.Count");
const TCHAR c_szRouteNames[]                    = TEXT("Route.Names");
const TCHAR c_szRouteDescriptionFmt[]           = TEXT("%s.Route.Description");
const TCHAR c_szRouteSourceFmt[]                = TEXT("%s.Route.Source");
const TCHAR c_szRouteHiResMF3Fmt[]              = TEXT("%s.Route.ExtMF3");
const TCHAR c_szRouteCalcNextVisFmt[]              = TEXT("%s.Route.CalcNextVis");
const TCHAR c_szRouteDirectoryFmt[]             = TEXT("%s.Directory");
const TCHAR c_szRouteDirectoryPendingFmt[]      = TEXT("%s.Directory.Pending");
const TCHAR c_szRouteDirectoryTransmittedFmt[]  = TEXT("%s.Directory.Transmitted");
const TCHAR c_szRouteDirectoryUndeliveredFmt[]  = TEXT("%s.Directory.Undelivered");
const TCHAR c_szRouteDirectoryReceivedFmt[]     = TEXT("%s.Directory.Received");
const TCHAR c_szRouteDirectoryProcessedFmt[]    = TEXT("%s.Directory.Processed");
const TCHAR c_szRouteDestinationFmt[]           = TEXT("%s.Route.Destination");
const TCHAR c_szRouteMsgNumberFmt[]             = TEXT("%s.Route.MsgNumber");
const TCHAR c_szRouteTranslateFmt[]             = TEXT("%s.Route.Translate");
const TCHAR c_szRouteRetriesFmt[]               = TEXT("%s.Route.Retries");
const TCHAR c_szRouteTimeoutFmt[]               = TEXT("%s.Route.Timeout");
const TCHAR c_szRouteSuppressRefBeaconsFmt[] = TEXT("%s.MCCSuppress.RefBeacons");
const TCHAR c_szRouteSuppressOrbBeaconsFmt[] = TEXT("%s.MCCSuppress.OrbBeacons");
const TCHAR c_szRouteSuppressTestBeaconsFmt[] = TEXT("%s.MCCSuppress.TestBeacons");
const TCHAR c_szRouteSuppressInvertedFrameSyncFmt[] = TEXT("%s.MCCSuppress.InvertedFrameSync");
const TCHAR c_szRouteSuppressInvalidBeaconFmt[] = TEXT("%s.MCCSuppress.InvalidBeacon");
const TCHAR c_szRouteSuppressInvalidUnlocated1Fmt[] = TEXT("%s.MCCSuppress.InvalidUnlocated1");
const TCHAR c_szRouteSuppressInvalidUnlocated2Fmt[] = TEXT("%s.MCCSuppress.InvalidUnlocated2");

const TCHAR c_szRouteFormatSit[]                = TEXT("SIT");
const TCHAR c_szRouteFormatMultisit[]           = TEXT("MultiSIT");
const TCHAR c_szRouteFormatFmt[]                = TEXT("%s.Route.Format");

const TCHAR c_szRouteSitsFmt[]                  = TEXT("%s.Route.SITs");
const TCHAR c_szRouteAutoSitsFmt[]				= TEXT("%s.Route.AutoSITs");

const TCHAR c_szRouteTypeDirect[]               = TEXT("Direct");
const TCHAR c_szRouteTypeFtp[]                  = TEXT("FTP");
const TCHAR c_szRouteTypeTcpip[]                = TEXT("TCP\\IP");
const TCHAR c_szRouteTypeSOAP[]                 = TEXT("SOAP");
const TCHAR c_szRouteTypeFmt[]                  = TEXT("%s.Route.Type");

const TCHAR c_szRouteHostFmt[]                  = TEXT("%s.Route.Host");
const TCHAR c_szRoutePortFmt[]                  = TEXT("%s.Route.Port");
const TCHAR c_szRouteLoginFmt[]                 = TEXT("%s.Route.Login");
const TCHAR c_szRoutePasswordFmt[]              = TEXT("%s.Route.Password");
const TCHAR c_szRouteRemoteDirectoryFmt[]       = TEXT("%s.Route.Directory");

const TCHAR c_szSystemTestTestHorn[]            = TEXT("SystemTest.TestHorn");
const TCHAR c_szSystemTestSweepRange[]          = TEXT("SystemTest.SweepRange");
const TCHAR c_szSystemTestStartUp[]             = TEXT("SystemTest.StartUp");
const TCHAR c_szSystemTestAvoidConflict[]       = TEXT("SystemTest.Exclusive");
const TCHAR c_szSystemTestPrepass[]             = TEXT("SystemTest.Prepass");
const TCHAR c_szSystemTestThreshold[]           = TEXT("SystemTest.Threshold");
const TCHAR c_szSystemTestWaveFile[]            = TEXT("SystemTest.WaveFile");

const TCHAR c_szPassScheduleDuration[]          = TEXT("PassSchedule.Duration");
const TCHAR c_szPassScheduleUpdatePeriod[]      = TEXT("PassSchedule.UpdatePeriod");
const TCHAR c_szPassScheduleTimeDiff[]          = TEXT("PassSchedule.TimeDiff");
const TCHAR c_szPassSchedulePrePassTimeRange[]  = TEXT("PassSchedule.PrePassTime.Range");
const TCHAR c_szPassSchedulePriority[]          = TEXT("PassSchedule.Priority");
const TCHAR c_szPassScheduleAllowTruncated[]    = TEXT("PassSchedule.AllowTruncated");

const TCHAR c_szMonitorPointACUTemp[]           = TEXT("ACUTemp");
const TCHAR c_szMonitorPointAUXTemp[]           = TEXT("AUXTemp");
const TCHAR c_szMonitorPointServoTemp[]         = TEXT("ServoTemp");
const TCHAR c_szMonitorPointLNCTemp[]           = TEXT("LNCTemp");
const TCHAR c_szMonitorPointRadomeTemp[]        = TEXT("RadomeTemp");
const TCHAR c_szMonitorPointRackTemp[]          = TEXT("RackTemp");
const TCHAR c_szMonitorPointRackAmbientTemp[]   = TEXT("RackAmbientTemp");
const TCHAR c_szMonitorPointRadomeHumidity[]    = TEXT("RadomeHumidity");
const TCHAR c_szMonitorPointACUHumidity[]       = TEXT("ACUHumidity");
const TCHAR c_szMonitorPointAGCVoltage[]        = TEXT("AGCVoltage");
const TCHAR c_szMonitorPointWindspeed[]         = TEXT("Windspeed");

// * NEW
const TCHAR c_szMonitorSignalCheckElevation[]	  	= TEXT("SignalCheckElevation");
const TCHAR c_szMonitorPointAntennaCheckElevation[]	= TEXT("AntennaCheckElevation");
const TCHAR c_szMonitorPointAntennaDelay[]		= TEXT("AntennaCheckDelay");
const TCHAR c_szMonitorPointAntennaBeamAngle[] = TEXT("AntennaBeamAngle");
const TCHAR c_szMonitorPointOutsideTemp[]  		= TEXT("OutsideTemp");
const TCHAR c_szMonitorPointMinCBC121Counts[ ] = TEXT("MinCBC121Counts");
const TCHAR c_szMonitorPointMinCBC243Counts[ ] = TEXT("MinCBC243Counts");
const TCHAR c_szMonitorPointMinCBC406Counts[ ] = TEXT("MinCBC406Counts");
const TCHAR c_szMonitorPointMinSARR406Counts[ ] = TEXT("MinSARR406Counts");
const TCHAR c_szMonitorPointMinSARP406Counts[ ] = TEXT("MinSARP406Counts");
const TCHAR c_szMonitorPointMinCBC121Time[ ] = TEXT("MinCBC121Time");
const TCHAR c_szMonitorPointMinCBC243Time[ ] = TEXT("MinCBC243Time");
const TCHAR c_szMonitorPointMinCBC406Time[ ] = TEXT("MinCBC406Time");
const TCHAR c_szMonitorPointMinSARR406Time[ ] = TEXT("MinSARR406Time");
const TCHAR c_szMonitorPointMinSARP406Time[ ] = TEXT("MinSARP406Time");
const TCHAR c_szMonitorPointMinCBC121Solns[ ] = TEXT("MinCBC121Solns");
const TCHAR c_szMonitorPointMinCBC243Solns[ ] = TEXT("MinCBC243Solns");
const TCHAR c_szMonitorPointMinCBC406Solns[ ] = TEXT("MinCBC406Solns");
const TCHAR c_szMonitorPointMinSARR406Solns[ ] = TEXT("MinSARR406Solns");
const TCHAR c_szMonitorPointMinSARP406Solns[ ] = TEXT("MinSARP406Solns");
const TCHAR c_szMonitorPointCommsContactFreq[ ] = TEXT("CommsContactFreq");
const TCHAR c_szMonitorPointCommsMaxRetries[ ] = TEXT("CommsMaxRetries");
const TCHAR c_szMonitorPointWidebandSyncLosses[ ] = TEXT("WidebandSyncLosses");
const TCHAR c_szMonitorPointMinCollectorCounts[ ] = TEXT("MinCollectorCounts");

// * NEW

const TCHAR c_szMonitorAlarmFmt[]               = TEXT("Monitor.%s.Alarm");
const TCHAR c_szMonitorWarningFmt[]             = TEXT("Monitor.%s.Warning");
const TCHAR c_szMonitorEnvironment[]            = TEXT("Monitor.Environment");
const TCHAR c_szMonitorServices[]               = TEXT("Monitor.Services");
const TCHAR c_szMonitorMinElevation[]				= TEXT("MinElevation");
const TCHAR c_szMonitorModIndex[]					= TEXT("ModIndex");

const TCHAR c_szMCCSuppressAlarm[]              = TEXT("MCCSuppress.Alarm");

const TCHAR c_szSitMaxSize[]					= TEXT("Sit.MaxSize");

const TCHAR c_szSiteName[]							= TEXT("Name");

const TCHAR c_szDefaultFrequency[]				= TEXT("60");	// ie: every minute
const DWORD c_dwDefaultRouteInfoFlags			= 0;
const DWORD c_dwDefaultDestInfoFlags			= 0;
const DWORD c_dwDefaultSourceInfoFlags			= 0;
const WORD c_wDefaultSwitchID					= 1;
const DWORD c_dwDefaultSysTestDuration			= 150;
const WORD c_wDefaultAGCSwitchID				= 24;
const DWORD c_dwDefaultAGCFlags					= 0; 
const DWORD c_dwDefaultReplicationFlags			= 0;
const DOUBLE c_dDefaultReplicationFrequency		= 0.0;
const TCHAR c_szDefaultFilterList[]				= TEXT("");
const double c_dDefaultStorageDays				= 0.0;
const float c_fDefaultElevation					= -90.0;
const DWORD    c_dwLutInfoRoutePort          = 21;
const TCHAR c_szDefaultSitMaxSize[]				= TEXT("25000");

const ULONG c_ulMaxSatellites					= 999;

#endif // ifdef __LUTCONST_H__
