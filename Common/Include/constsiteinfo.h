#ifndef __CONSTSITEINFO_H__
#define __CONSTSITEINFO_H__

#include <wchar.h>

static const wchar_t    c_pwcsSiteGroupType[]                              = L"PRO";
static const wchar_t    c_pwcsSiteKeyLutID[]                               = L"LutID";
static const wchar_t    c_pwcsSiteKeyServiceNameFmt[]                      = L"Service.Name";
static const wchar_t    c_pwcsSiteKeyServiceRestartFmt[]                   = L"Service.Restart";

static const wchar_t    c_pwcsSiteKeyClockDifference[]                     = L"Clock.Difference";
static const wchar_t    c_pwcsSiteKeyClockCheckPeriod[]                    = L"Clock.Checkperiod";


// Data
static const wchar_t    c_pwcsSiteKeyDataDirectory[]                       = L"Data.Directory";
static const wchar_t    c_pwcsSiteKeyDataDirectorySend[]                   = L"Data.Directory.Send";
static const wchar_t    c_pwcsSiteKeyDataDirectorySent[]                   = L"Data.Directory.Sent";
static const wchar_t    c_pwcsSiteKeyDataDirectoryReceive[]                = L"Data.Directory.Receive";
static const wchar_t    c_pwcsSiteKeyDataDirectoryProcessed[]              = L"Data.Directory.Processed";
static const wchar_t    c_pwcsSiteKeyDataDirectoryUndelivered[]            = L"Data.Directory.Undelivered";
static const wchar_t    c_pwcsSiteKeyDataDirectoryOffline[]                = L"Data.Directory.Offline";
static const wchar_t    c_pwcsSiteKeyDataDirectoryTransfer[]               = L"Data.Directory.Transfer";
static const wchar_t    c_pwcsSiteKeyDataDirectoryData[]                   = L"Data.Directory.Data";

static const wchar_t    c_pwcsSiteKeyDataArchiveTime[]                     = L"Data.Archive.Time";

static const wchar_t    c_pwcsSiteKeyDataArchiveRawCBC[]                   = L"Data.Archive.RawCBC";
static const wchar_t    c_pwcsSiteKeyDataArchiveRaw406[]                   = L"Data.Archive.Raw406";
static const wchar_t    c_pwcsSiteKeyDataArchiveSpectrum[]                 = L"Data.Archive.Spectrum";
static const wchar_t    c_pwcsSiteKeyDataArchiveCalibCBC[]                 = L"Data.Archive.CalibCBC";
static const wchar_t    c_pwcsSiteKeyDataArchiveCalib406[]                 = L"Data.Archive.Calib406";
static const wchar_t    c_pwcsSiteKeyDataArchiveStats[]                    = L"Data.Archive.Stats";
static const wchar_t    c_pwcsSiteKeyDataArchiveAlarm[]                    = L"Data.Archive.Alarm";
static const wchar_t    c_pwcsSiteKeyDataArchiveTLE[]                      = L"Data.Archive.TLE";
static const wchar_t    c_pwcsSiteKeyDataArchiveLocation[]                 = L"Data.Archive.Location";
static const wchar_t    c_pwcsSiteKeyDataArchivePass[]                     = L"Data.Archive.Pass";
static const wchar_t    c_pwcsSiteKeyDataArchivePassSched[]                = L"Data.Archive.PassSched";
static const wchar_t    c_pwcsSiteKeyDataArchiveComms[]                    = L"Data.Archive.Comms";
static const wchar_t    c_pwcsSiteKeyDataArchiveLog[]                      = L"Data.Archive.Log";
static const wchar_t    c_pwcsSiteKeyDataArchiveSensor[]                   = L"Data.Archive.Sensor";
static const wchar_t    c_pwcsSiteKeyDataArchiveEnvironment[]              = L"Data.Archive.Environment";
static const wchar_t    c_pwcsSiteKeyDataArchiveCombined406[]              = L"Data.Archive.Combined406";
static const wchar_t    c_pwcsSiteKeyDataArchiveResidual[]                 = L"Data.Archive.Residual";
static const wchar_t    c_pwcsSiteKeyDataArchiveConfig[]                   = L"Data.Archive.Config";
static const wchar_t    c_pwcsSiteKeyDataArchiveSarpCalib[]                = L"Data.Archive.SarpCalib";
static const wchar_t    c_pwcsSiteKeyDataArchiveSarrCalib[]                = L"Data.Archive.SarrCalib";
static const wchar_t    c_pwcsSiteKeyDataArchiveGeoStats[]                 = L"Data.Archive.GeoStats";

static const wchar_t    c_pwcsSiteKeyDataArchiveSend[]                     = L"Data.Archive.Send";
static const wchar_t    c_pwcsSiteKeyDataArchiveSent[]                     = L"Data.Archive.Sent";
static const wchar_t    c_pwcsSiteKeyDataArchiveReceive[]                  = L"Data.Archive.Receive";
static const wchar_t    c_pwcsSiteKeyDataArchiveProcessed[]                = L"Data.Archive.Processed";
static const wchar_t    c_pwcsSiteKeyDataArchiveUndelivered[]              = L"Data.Archive.Undelivered";
static const wchar_t    c_pwcsSiteKeyDataArchiveTransfer[]                 = L"Data.Archive.Transfer";
static const wchar_t    c_pwcsSiteKeyDataArchiveData[]                     = L"Data.Archive.Data";

static const wchar_t    c_pwcsSiteKeySystemTestTestHorn[]                  = L"SystemTest.TestHorn";
static const wchar_t    c_pwcsSiteKeySystemTestSweepRange[]                = L"SystemTest.SweepRange";
static const wchar_t    c_pwcsSiteKeySystemTestStartUp[]                   = L"SystemTest.StartUp";
static const wchar_t    c_pwcsSiteKeySystemTestAvoidConflict[]             = L"SystemTest.Exclusive";
static const wchar_t    c_pwcsSiteKeySystemTestPrepass[]                   = L"SystemTest.Prepass";
static const wchar_t    c_pwcsSiteKeySystemTestThreshold[]                 = L"SystemTest.Threshold";
static const wchar_t    c_pwcsSiteKeySystemTestWaveFile[]                  = L"SystemTest.WaveFile";
static const wchar_t    c_pwcsSiteKeySystemTestMinDuration[]               = L"SystemTest.MinDuration";
static const wchar_t    c_pwcsSiteKeySystemTestMaxModIndex[]               	= L"SystemTest.MaxModIndex";

static const wchar_t    c_pwcsSiteKeyPassScheduleDuration[]                = L"PassSchedule.Duration";
static const wchar_t    c_pwcsSiteKeyPassScheduleUpdatePeriod[]            = L"PassSchedule.UpdatePeriod";
static const wchar_t    c_pwcsSiteKeyPassScheduleTimeDiff[]                = L"PassSchedule.TimeDiff";
static const wchar_t    c_pwcsSiteKeyPassSchedulePrePassTimeRange[]        = L"PassSchedule.PrePassTime.Range";
static const wchar_t    c_pwcsSiteKeyPassSchedulePriority[]                = L"PassSchedule.Priority";
static const wchar_t    c_pwcsSiteKeyPassScheduleAllowTruncated[]          = L"PassSchedule.AllowTruncated";

static const wchar_t    c_pwcsSiteKeyMonitorEnvironment[]                  = L"Monitor.Environment";

static const wchar_t    c_pwcsSiteKeyMonitorMinReportAlarm[]               = L"Monitor.Alarm.Report.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxReportAlarm[]               = L"Monitor.Alarm.Report.Max";
static const wchar_t    c_pwcsSiteKeyMonitorFreqReportAlarm[]              = L"Monitor.Alarm.FreqReport";
static const wchar_t    c_pwcsSiteKeyMonitorMinElevationAlarm[]            = L"Monitor.Alarm.Elevation.Min";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaMinAngleAlarm[]         = L"Monitor.Alarm.AntennaMinAngle";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaDelayAlarm[]            = L"Monitor.Alarm.AntennaDelay";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaBeamAngleAlarm[]        = L"Monitor.Alarm.AntennaBeamAngle";
static const wchar_t    c_pwcsSiteKeyMonitorCommsRetriesAlarm[]            = L"Monitor.Alarm.CommsRetries";
static const wchar_t    c_pwcsSiteKeyMonitorCommsContactFreqAlarm[]        = L"Monitor.Alarm.CommsContactFreq";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121CountsAlarm[]         = L"Monitor.Alarm.CBC121Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243CountsAlarm[]         = L"Monitor.Alarm.CBC243Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406CountsAlarm[]         = L"Monitor.Alarm.CBC406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406CountsAlarm[]        = L"Monitor.Alarm.SARR406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406CountsAlarm[]        = L"Monitor.Alarm.SARP406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121TimeAlarm[]           = L"Monitor.Alarm.CBC121Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243TimeAlarm[]           = L"Monitor.Alarm.CBC243Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406TimeAlarm[]           = L"Monitor.Alarm.CBC406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406TimeAlarm[]          = L"Monitor.Alarm.SARR406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406TimeAlarm[]          = L"Monitor.Alarm.SARP406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121SolutionsAlarm[]      = L"Monitor.Alarm.CBC121Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243SolutionsAlarm[]      = L"Monitor.Alarm.CBC243Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406SolutionsAlarm[]      = L"Monitor.Alarm.CBC406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406SolutionsAlarm[]     = L"Monitor.Alarm.SARR406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406SolutionsAlarm[]     = L"Monitor.Alarm.SARP406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorWidebandSyncLossesAlarm[]      = L"Monitor.Alarm.WidebandSyncLosses";
static const wchar_t    c_pwcsSiteKeyMonitorCollectorModIndexAlarm[]       = L"Monitor.Alarm.CollectorModIndex";
static const wchar_t    c_pwcsSiteKeyMonitorCollectorADCRMAlarm[]          = L"Monitor.Alarm.CollectorADCRM";
static const wchar_t    c_pwcsSiteKeyMonitorMinOutsideTempAlarm[]          = L"Monitor.Alarm.OutsideTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxOutsideTempAlarm[]          = L"Monitor.Alarm.OutsideTemp.Max";
static const wchar_t    c_pwcsSiteKeyMonitorMinInsideTempAlarm[]           = L"Monitor.Alarm.InsideTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxInsideTempAlarm[]           = L"Monitor.Alarm.InsideTemp.Max";
static const wchar_t    c_pwcsSiteKeyMonitorMinEquipTempAlarm[]            = L"Monitor.Alarm.EquipTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxEquipTempAlarm[]            = L"Monitor.Alarm.EquipTemp.Max";

static const wchar_t    c_pwcsSiteKeyMonitorMinReportWarning[]             = L"Monitor.Warning.Report.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxReportWarning[]             = L"Monitor.Warning.Report.Max";
static const wchar_t    c_pwcsSiteKeyMonitorFreqReportWarning[]            = L"Monitor.Warning.FreqReport";
static const wchar_t    c_pwcsSiteKeyMonitorMinElevationWarning[]          = L"Monitor.Warning.Elevation.Min";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaMinAngleWarning[]       = L"Monitor.Warning.AntennaMinAngle";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaDelayWarning[]          = L"Monitor.Warning.AntennaDelay";
static const wchar_t    c_pwcsSiteKeyMonitorAntennaBeamAngleWarning[]      = L"Monitor.Warning.AntennaBeamAngle";
static const wchar_t    c_pwcsSiteKeyMonitorCommsRetriesWarning[]          = L"Monitor.Warning.CommsRetries";
static const wchar_t    c_pwcsSiteKeyMonitorCommsContactFreqWarning[]      = L"Monitor.Warning.CommsContactFreq";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121CountsWarning[]       = L"Monitor.Warning.CBC121Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243CountsWarning[]       = L"Monitor.Warning.CBC243Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406CountsWarning[]       = L"Monitor.Warning.CBC406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406CountsWarning[]      = L"Monitor.Warning.SARR406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406CountsWarning[]      = L"Monitor.Warning.SARP406Counts.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121TimeWarning[]         = L"Monitor.Warning.CBC121Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243TimeWarning[]         = L"Monitor.Warning.CBC243Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406TimeWarning[]         = L"Monitor.Warning.CBC406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406TimeWarning[]        = L"Monitor.Warning.SARR406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406TimeWarning[]        = L"Monitor.Warning.SARP406Time.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC121SolutionsWarning[]    = L"Monitor.Warning.CBC121Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC243SolutionsWarning[]    = L"Monitor.Warning.CBC243Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinCBC406SolutionsWarning[]    = L"Monitor.Warning.CBC406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARR406SolutionsWarning[]   = L"Monitor.Warning.SARR406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMinSARP406SolutionsWarning[]   = L"Monitor.Warning.SARP406Solutions.Min";
static const wchar_t    c_pwcsSiteKeyMonitorWidebandSyncLossesWarning[]    = L"Monitor.Warning.WidebandSyncLosses";
static const wchar_t    c_pwcsSiteKeyMonitorCollectorModIndexWarning[]     = L"Monitor.Warning.CollectorModIndex";
static const wchar_t    c_pwcsSiteKeyMonitorCollectorADCRMWarning[]        = L"Monitor.Warning.CollectorADCRM";
static const wchar_t    c_pwcsSiteKeyMonitorMinOutsideTempWarning[]        = L"Monitor.Warning.OutsideTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxOutsideTempWarning[]        = L"Monitor.Warning.OutsideTemp.Max";
static const wchar_t    c_pwcsSiteKeyMonitorMinInsideTempWarning[]         = L"Monitor.Warning.InsideTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxInsideTempWarning[]         = L"Monitor.Warning.InsideTemp.Max";
static const wchar_t    c_pwcsSiteKeyMonitorMinEquipTempWarning[]          = L"Monitor.Warning.EquipTemp.Min";
static const wchar_t    c_pwcsSiteKeyMonitorMaxEquipTempWarning[]          = L"Monitor.Warning.EquipTemp.Max";

static const wchar_t    c_pwcsSiteKeySitMaxSize[]                          = L"Sit.MaxSize";

static const wchar_t    c_pwcsSiteKeyMCCSuppressAlarm[]                    = L"MCCSuppress.Alarm";
static const wchar_t    c_pwcsSiteKeyMCCSuppressWarning[]                  = L"MCCSuppress.Warning";

static const wchar_t    c_pwcsSiteKeyOfflineDirMaxFilesCnt[]               = L"OfflineDirectory.MaxFilesCount";
static const wchar_t    c_pwcsSiteKeyCollectorMinPPSLostAlarm[]            = L"Collector.Alarm.MinPPSLostCount";

static const wchar_t    c_pwcsSiteKeyFixedBitsValidation[]                 = L"FixedBitsValidation";

/*
static const wchar_t    c_pwcsSiteKey[]               = L"";
*/

#endif // __CONSTSITEINFO_H__

