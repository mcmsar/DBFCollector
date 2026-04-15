#ifndef __CONSTSATINFO_H__
#define __CONSTSATINFO_H__

#include <wchar.h>

static const wchar_t    c_pwcsSATComponentName[]            = L"SATInfo";
static const wchar_t    c_pwcsSATComponentDesc[]            = L"EMS SAT Info";

static const wchar_t    c_pwcsSATGroupType[]                = L"SAT";

static const wchar_t    c_pwcsSATKeyNoradID[]               = L"NoradID";
static const wchar_t    c_pwcsSATKeyDescription[]           = L"Description";
static const wchar_t    c_pwcsSATKeyPhaseMod[]              = L"PhaseMod";
static const wchar_t    c_pwcsSATKeyPassSchedPriority[]     = L"PassSchedule.Priority";

static const wchar_t    c_pwcsSATKeyBasebandFreqBandwidth[] = L"Baseband.Frequency.Bandwidth";
static const wchar_t    c_pwcsSATKeyBasebandFreqCentre[]    = L"Baseband.Frequency.Centre";
static const wchar_t    c_pwcsSATKey121FreqBandwidth[]      = L"121.Frequency.Bandwidth";
static const wchar_t    c_pwcsSATKey121FreqCentre[]         = L"121.Frequency.Centre";
static const wchar_t    c_pwcsSATKey243FreqBandwidth[]      = L"243.Frequency.Bandwidth";
static const wchar_t    c_pwcsSATKey243FreqCentre[]         = L"243.Frequency.Centre";
static const wchar_t    c_pwcsSATKey406FreqBandwidth[]      = L"406.Frequency.Bandwidth";
static const wchar_t    c_pwcsSATKey406FreqCentre[]         = L"406.Frequency.Centre";
static const wchar_t    c_pwcsSATKeyPDSFreqBandwidth[]      = L"PDS.Frequency.Bandwidth";
static const wchar_t    c_pwcsSATKeyPDSFreqCentre[]         = L"PDS.Frequency.Centre";

static const wchar_t    c_pwcsSATKey406HistoryDataStartTime[]    = L"406.HistoryData.StartTime";

static const wchar_t    c_pwcsSATKeyMI406QMSOutputRate[]	= L"MI406.QMS.OutputRate";

// ===================================================================================
// Test
static const wchar_t    c_pwcsSATKeyTestSarpSarrLocations[] = L"Test.SarpSarr.Locations";
static const wchar_t    c_pwcsSATKeyTestSuppressInvertedFrameSynch[] = L"Test.InvertedFrameSynch.Suppress";
static const wchar_t    c_pwcsSATKeyTestGeoRestrictIntegrationCount[] = L"Test.GeoIntegrationCount.Restrict";
static const wchar_t    c_pwcsSATKeyTestPostManoeuvreUseEffectiveTime[] = L"Test.PostManoeuvre.UseEffectiveTime";
static const wchar_t    c_pwcsSATKeyTestIgnoreConfirmationRules[] = L"Test.IgnoreConfirmationRules";
static const wchar_t    c_pwcsSATKeyTestSuppressCombinationMessage[] = L"Test.CombinationMessage.Suppress";

// ===================================================================================
// Spectrum
static const wchar_t c_pwcsSATKeySpectrumCollect[]                = L"Spectrum.Collect";
static const wchar_t c_pwcsSATKeySpectrumProcess[]                = L"Spectrum.Process";
static const wchar_t c_pwcsSATKeySpectrumProcessMultiPass[]       = L"Spectrum.Process.MultiPass";
static const wchar_t c_pwcsSATKeySpectrumProcessMultiSat[]        = L"Spectrum.Process.MultiSat";
static const wchar_t c_pwcsSATKeySpectrumTransmitCalibrated[]     = L"Spectrum.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeySpectrumTransmitSolution[]       = L"Spectrum.Transmit.Solution";
static const wchar_t c_pwcsSATKeySpectrumMCCSuppressLocated[]     = L"Spectrum.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeySpectrumMCCSuppressUnLocated[]   = L"Spectrum.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeySpectrumMCCSuppressUnLocated1[]  = L"Spectrum.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeySpectrumMCCSuppressUnLocated2[]  = L"Spectrum.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeySpectrumMCCFilterCriteria[]      = L"Spectrum.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeySpectrumFrequencyRange[]         = L"Spectrum.Frequency.Range";
static const wchar_t c_pwcsSATKeySpectrumNoisePassBand[]          = L"Spectrum.Noise.PassBand";
static const wchar_t c_pwcsSATKeySpectrumNoiseStopBand[]          = L"Spectrum.Noise.StopBand";
static const wchar_t c_pwcsSATKeySpectrumNoiseThreshold[]         = L"Spectrum.Noise.Threshold";
static const wchar_t c_pwcsSATKeySpectrumSignalPassBand[]         = L"Spectrum.Signal.PassBand";
static const wchar_t c_pwcsSATKeySpectrumSignalStopBand[]         = L"Spectrum.Signal.StopBand";
static const wchar_t c_pwcsSATKeySpectrumSignalThreshold[]        = L"Spectrum.Signal.Threshold";
static const wchar_t c_pwcsSATKeySpectrumCombineThreshold[]       = L"Spectrum.Combine.Threshold";
static const wchar_t c_pwcsSATKeySpectrumTimeThreshold[]          = L"Spectrum.Time.Threshold";

// ===================================================================================
// Audio
static const wchar_t c_pwcsSATKeyAudioCollect[]               = L"Audio.Collect";
static const wchar_t c_pwcsSATKeyAudioProcess[]               = L"Audio.Process";
static const wchar_t c_pwcsSATKeyAudioProcessMultiPass[]      = L"Audio.Process.MultiPass";
static const wchar_t c_pwcsSATKeyAudioProcessMultiSat[]       = L"Audio.Process.MultiSat";
static const wchar_t c_pwcsSATKeyAudioTransmitCalibrated[]    = L"Audio.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyAudioTransmitSolution[]      = L"Audio.Transmit.Solution";
static const wchar_t c_pwcsSATKeyAudioMCCSuppressLocated[]    = L"Audio.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyAudioMCCSuppressUnLocated[]  = L"Audio.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyAudioMCCSuppressUnLocated1[] = L"Audio.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyAudioMCCSuppressUnLocated2[] = L"Audio.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyAudioMCCFilterCriteria[]     = L"Audio.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyAudioFrequencyRange[]        = L"Audio.Frequency.Range";
static const wchar_t c_pwcsSATKeyAudioNoisePassBand[]         = L"Audio.Noise.PassBand";
static const wchar_t c_pwcsSATKeyAudioNoiseStopBand[]         = L"Audio.Noise.StopBand";
static const wchar_t c_pwcsSATKeyAudioNoiseThreshold[]        = L"Audio.Noise.Threshold";
static const wchar_t c_pwcsSATKeyAudioSignalPassBand[]        = L"Audio.Signal.PassBand";
static const wchar_t c_pwcsSATKeyAudioSignalStopBand[]        = L"Audio.Signal.StopBand";
static const wchar_t c_pwcsSATKeyAudioSignalThreshold[]       = L"Audio.Signal.Threshold";
static const wchar_t c_pwcsSATKeyAudioCombineThreshold[]      = L"Audio.Combine.Threshold";
static const wchar_t c_pwcsSATKeyAudioTimeThreshold[]         = L"Audio.Time.Threshold";

static const wchar_t c_pwcsSATKeyAudioFreqBands[]              = L"Audio.FreqBands";
static const wchar_t c_pwcsSATKeyAudioFileDuration[]           = L"Audio.File.Duration";
static const wchar_t c_pwcsSATKeyAudioFileSize[]               = L"Audio.File.Size";
static const wchar_t c_pwcsSATKeyAudioArchiveDuration[]        = L"Audio.Archive.Duration";
static const wchar_t c_pwcsSATKeyAudioArchiveSize[]            = L"Audio.Archive.Size";

// ===================================================================================
// SARR
static const wchar_t c_pwcsSATKeySARRCollect[]                 = L"SARR.Collect";
static const wchar_t c_pwcsSATKeySARRProcess[]                 = L"SARR.Process";
static const wchar_t c_pwcsSATKeySARRProcessMultiPass[]        = L"SARR.Process.MultiPass";
static const wchar_t c_pwcsSATKeySARRProcessMultiSat[]         = L"SARR.Process.MultiSat";
static const wchar_t c_pwcsSATKeySARRTransmitCalibrated[]      = L"SARR.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeySARRTransmitSolution[]        = L"SARR.Transmit.Solution";
static const wchar_t c_pwcsSATKeySARRMCCSuppressLocated[]      = L"SARR.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeySARRMCCSuppressUnLocated[]    = L"SARR.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeySARRMCCSuppressUnLocated1[]   = L"SARR.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeySARRMCCSuppressUnLocated2[]   = L"SARR.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeySARRMCCFilterCriteria[]       = L"SARR.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeySARRFrequencyRange[]          = L"SARR.Frequency.Range";
static const wchar_t c_pwcsSATKeySARRNoisePassBand[]           = L"SARR.Noise.PassBand";
static const wchar_t c_pwcsSATKeySARRNoiseStopBand[]           = L"SARR.Noise.StopBand";
static const wchar_t c_pwcsSATKeySARRNoiseThreshold[]          = L"SARR.Noise.Threshold";
static const wchar_t c_pwcsSATKeySARRSignalPassBand[]          = L"SARR.Signal.PassBand";
static const wchar_t c_pwcsSATKeySARRSignalStopBand[]          = L"SARR.Signal.StopBand";
static const wchar_t c_pwcsSATKeySARRSignalThreshold[]         = L"SARR.Signal.Threshold";
static const wchar_t c_pwcsSATKeySARRCombineThreshold[]        = L"SARR.Combine.Threshold";
static const wchar_t c_pwcsSATKeySARRTimeThreshold[]           = L"SARR.Time.Threshold";

static const wchar_t c_pwcsSATKeySARRVersionMaximum[]          = L"SARR.Version.Maximum";
static const wchar_t c_pwcsSATKeySARRCalibrationTimeFmt[]      = L"SARR.CalibrationTime.";
static const wchar_t c_pwcsSATKeySARRFreqOffsetFmt[]           = L"SARR.FreqOffset.";
static const wchar_t c_pwcsSATKeySARRTimeOffsetFmt[]           = L"SARR.TimeOffset.";
static const wchar_t c_pwcsSATKeySARREffectiveFmt[]            = L"SARR.Effective.";

static const wchar_t c_pwcsSATKeySARRDetectsMaximum[]          = L"SARR.Detects.Maximum";
static const wchar_t c_pwcsSATKeySARRFSerrorsMaximum[]         = L"SARR.FSErrors.Maximum";
static const wchar_t c_pwcsSATKeySARRDetectRange[]             = L"SARR.Detect.Range";
static const wchar_t c_pwcsSATKeySARRDecayThreshold[]          = L"SARR.Decay.Threshold";
static const wchar_t c_pwcsSATKeySARRCNRMinimum[]              = L"SARR.CNR.Minimum";
static const wchar_t c_pwcsSATKeySARRPowerConversion[]         = L"SARR.PowerConversion";
static const wchar_t c_pwcsSATKeySARRFreqBandAdj[]             = L"SARR.FreqBandAdjust";

// ===================================================================================
// SARP
static const wchar_t c_pwcsSATKeySARPCollect[]                 = L"SARP.Collect";
static const wchar_t c_pwcsSATKeySARPProcess[]                 = L"SARP.Process";
static const wchar_t c_pwcsSATKeySARPProcessMultiPass[]        = L"SARP.Process.MultiPass";
static const wchar_t c_pwcsSATKeySARPProcessMultiSat[]         = L"SARP.Process.MultiSat";
static const wchar_t c_pwcsSATKeySARPTransmitCalibrated[]      = L"SARP.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeySARPTransmitSolution[]        = L"SARP.Transmit.Solution";
static const wchar_t c_pwcsSATKeySARPMCCSuppressLocated[]      = L"SARP.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeySARPMCCSuppressUnLocated[]    = L"SARP.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeySARPMCCSuppressUnLocated1[]   = L"SARP.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeySARPMCCSuppressUnLocated2[]   = L"SARP.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeySARPMCCFilterCriteria[]       = L"SARP.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeySARPFrequencyRange[]          = L"SARP.Frequency.Range";
static const wchar_t c_pwcsSATKeySARPNoisePassBand[]           = L"SARP.Noise.PassBand";
static const wchar_t c_pwcsSATKeySARPNoiseStopBand[]           = L"SARP.Noise.StopBand";
static const wchar_t c_pwcsSATKeySARPNoiseThreshold[]          = L"SARP.Noise.Threshold";
static const wchar_t c_pwcsSATKeySARPSignalPassBand[]          = L"SARP.Signal.PassBand";
static const wchar_t c_pwcsSATKeySARPSignalStopBand[]          = L"SARP.Signal.StopBand";
static const wchar_t c_pwcsSATKeySARPSignalThreshold[]         = L"SARP.Signal.Threshold";
static const wchar_t c_pwcsSATKeySARPCombineThreshold[]        = L"SARP.Combine.Threshold";
static const wchar_t c_pwcsSATKeySARPTimeThreshold[]           = L"SARP.Time.Threshold";

static const wchar_t c_pwcsSATKeySARPVersionMaximum[]          = L"SARP.Version.Maximum";
static const wchar_t c_pwcsSATKeySARPCalibrationTimeFmt[]      = L"SARP.CalibrationTime.";
static const wchar_t c_pwcsSATKeySARPRolloverTimeFmt[]         = L"SARP.RolloverTime.";
static const wchar_t c_pwcsSATKeySARPUSOFrequencyFmt[]         = L"SARP.USOFrequency.";
static const wchar_t c_pwcsSATKeySARPFreqOffsetFmt[]           = L"SARP.FreqOffset.";
static const wchar_t c_pwcsSATKeySARPEffectiveFmt[]            = L"SARP.Effective.";

static const wchar_t c_pwcsSATKeySARPType[]                    = L"SARP.Type";
static const wchar_t c_pwcsSATKeySARPTimeField[]               = L"SARP.TimeField";
static const wchar_t c_pwcsSATKeySARPBitRate[]                 = L"SARP.BitRate";

static const wchar_t c_pwcsSARPCalibTimeThreshold[]			   = L"SARP.CalibrationTime.Threshold";
static const wchar_t c_pwcsSARPUSOFreqThreshold[]			   = L"SARP.USOFrequency.Threshold";

// ===================================================================================
// CBC121
static const wchar_t c_pwcsSATKeyCBC121Collect[]               = L"CBC121.Collect";
static const wchar_t c_pwcsSATKeyCBC121Process[]               = L"CBC121.Process";
static const wchar_t c_pwcsSATKeyCBC121ProcessMultiPass[]      = L"CBC121.Process.MultiPass";
static const wchar_t c_pwcsSATKeyCBC121ProcessMultiSat[]       = L"CBC121.Process.MultiSat";
static const wchar_t c_pwcsSATKeyCBC121TransmitCalibrated[]    = L"CBC121.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyCBC121TransmitSolution[]      = L"CBC121.Transmit.Solution";
static const wchar_t c_pwcsSATKeyCBC121MCCSuppressLocated[]    = L"CBC121.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyCBC121MCCSuppressUnLocated[]  = L"CBC121.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyCBC121MCCSuppressUnLocated1[] = L"CBC121.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyCBC121MCCSuppressUnLocated2[] = L"CBC121.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyCBC121MCCFilterCriteria[]     = L"CBC121.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyCBC121FrequencyRange[]        = L"CBC121.Frequency.Range";
static const wchar_t c_pwcsSATKeyCBC121NoisePassBand[]         = L"CBC121.Noise.PassBand";
static const wchar_t c_pwcsSATKeyCBC121NoiseStopBand[]         = L"CBC121.Noise.StopBand";
static const wchar_t c_pwcsSATKeyCBC121NoiseThreshold[]        = L"CBC121.Noise.Threshold";
static const wchar_t c_pwcsSATKeyCBC121SignalPassBand[]        = L"CBC121.Signal.PassBand";
static const wchar_t c_pwcsSATKeyCBC121SignalStopBand[]        = L"CBC121.Signal.StopBand";
static const wchar_t c_pwcsSATKeyCBC121SignalThreshold[]       = L"CBC121.Signal.Threshold";
static const wchar_t c_pwcsSATKeyCBC121CombineThreshold[]      = L"CBC121.Combine.Threshold";
static const wchar_t c_pwcsSATKeyCBC121TimeThreshold[]         = L"CBC121.Time.Threshold";

// ===================================================================================
// CBC243
static const wchar_t c_pwcsSATKeyCBC243Collect[]               = L"CBC243.Collect";
static const wchar_t c_pwcsSATKeyCBC243Process[]               = L"CBC243.Process";
static const wchar_t c_pwcsSATKeyCBC243ProcessMultiPass[]      = L"CBC243.Process.MultiPass";
static const wchar_t c_pwcsSATKeyCBC243ProcessMultiSat[]       = L"CBC243.Process.MultiSat";
static const wchar_t c_pwcsSATKeyCBC243TransmitCalibrated[]    = L"CBC243.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyCBC243TransmitSolution[]      = L"CBC243.Transmit.Solution";
static const wchar_t c_pwcsSATKeyCBC243MCCSuppressLocated[]    = L"CBC243.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyCBC243MCCSuppressUnLocated[]  = L"CBC243.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyCBC243MCCSuppressUnLocated1[] = L"CBC243.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyCBC243MCCSuppressUnLocated2[] = L"CBC243.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyCBC243MCCFilterCriteria[]     = L"CBC243.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyCBC243FrequencyRange[]        = L"CBC243.Frequency.Range";
static const wchar_t c_pwcsSATKeyCBC243NoisePassBand[]         = L"CBC243.Noise.PassBand";
static const wchar_t c_pwcsSATKeyCBC243NoiseStopBand[]         = L"CBC243.Noise.StopBand";
static const wchar_t c_pwcsSATKeyCBC243NoiseThreshold[]        = L"CBC243.Noise.Threshold";
static const wchar_t c_pwcsSATKeyCBC243SignalPassBand[]        = L"CBC243.Signal.PassBand";
static const wchar_t c_pwcsSATKeyCBC243SignalStopBand[]        = L"CBC243.Signal.StopBand";
static const wchar_t c_pwcsSATKeyCBC243SignalThreshold[]       = L"CBC243.Signal.Threshold";
static const wchar_t c_pwcsSATKeyCBC243CombineThreshold[]      = L"CBC243.Combine.Threshold";
static const wchar_t c_pwcsSATKeyCBC243TimeThreshold[]         = L"CBC243.Time.Threshold";

// ===================================================================================
// CBC406
static const wchar_t c_pwcsSATKeyCBC406Collect[]               = L"CBC406.Collect";
static const wchar_t c_pwcsSATKeyCBC406Process[]               = L"CBC406.Process";
static const wchar_t c_pwcsSATKeyCBC406ProcessMultiPass[]      = L"CBC406.Process.MultiPass";
static const wchar_t c_pwcsSATKeyCBC406ProcessMultiSat[]       = L"CBC406.Process.MultiSat";
static const wchar_t c_pwcsSATKeyCBC406TransmitCalibrated[]    = L"CBC406.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyCBC406TransmitSolution[]      = L"CBC406.Transmit.Solution";
static const wchar_t c_pwcsSATKeyCBC406MCCSuppressLocated[]    = L"CBC406.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyCBC406MCCSuppressUnLocated[]  = L"CBC406.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyCBC406MCCSuppressUnLocated1[] = L"CBC406.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyCBC406MCCSuppressUnLocated2[] = L"CBC406.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyCBC406MCCFilterCriteria[]     = L"CBC406.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyCBC406FrequencyRange[]        = L"CBC406.Frequency.Range";
static const wchar_t c_pwcsSATKeyCBC406NoisePassBand[]         = L"CBC406.Noise.PassBand";
static const wchar_t c_pwcsSATKeyCBC406NoiseStopBand[]         = L"CBC406.Noise.StopBand";
static const wchar_t c_pwcsSATKeyCBC406NoiseThreshold[]        = L"CBC406.Noise.Threshold";
static const wchar_t c_pwcsSATKeyCBC406SignalPassBand[]        = L"CBC406.Signal.PassBand";
static const wchar_t c_pwcsSATKeyCBC406SignalStopBand[]        = L"CBC406.Signal.StopBand";
static const wchar_t c_pwcsSATKeyCBC406SignalThreshold[]       = L"CBC406.Signal.Threshold";
static const wchar_t c_pwcsSATKeyCBC406CombineThreshold[]      = L"CBC406.Combine.Threshold";
static const wchar_t c_pwcsSATKeyCBC406TimeThreshold[]         = L"CBC406.Time.Threshold";

// ===================================================================================
// MI406
static const wchar_t c_pwcsSATKeyMI406Collect[]               = L"MI406.Collect";
static const wchar_t c_pwcsSATKeyMI406Process[]               = L"MI406.Process";
static const wchar_t c_pwcsSATKeyMI406ProcessMultiPass[]      = L"MI406.Process.MultiPass";
static const wchar_t c_pwcsSATKeyMI406ProcessMultiSat[]       = L"MI406.Process.MultiSat";
static const wchar_t c_pwcsSATKeyMI406TransmitCalibrated[]    = L"MI406.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyMI406TransmitSolution[]      = L"MI406.Transmit.Solution";
static const wchar_t c_pwcsSATKeyMI406MCCSuppressLocated[]    = L"MI406.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyMI406MCCSuppressUnLocated[]  = L"MI406.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyMI406MCCSuppressUnLocated1[] = L"MI406.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyMI406MCCSuppressUnLocated2[] = L"MI406.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyMI406MCCFilterCriteria[]     = L"MI406.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyMI406FrequencyRange[]        = L"MI406.Frequency.Range";
static const wchar_t c_pwcsSATKeyMI406NoisePassBand[]         = L"MI406.Noise.PassBand";
static const wchar_t c_pwcsSATKeyMI406NoiseStopBand[]         = L"MI406.Noise.StopBand";
static const wchar_t c_pwcsSATKeyMI406NoiseThreshold[]        = L"MI406.Noise.Threshold";
static const wchar_t c_pwcsSATKeyMI406SignalPassBand[]        = L"MI406.Signal.PassBand";
static const wchar_t c_pwcsSATKeyMI406SignalStopBand[]        = L"MI406.Signal.StopBand";
static const wchar_t c_pwcsSATKeyMI406SignalThreshold[]       = L"MI406.Signal.Threshold";
static const wchar_t c_pwcsSATKeyMI406CombineThreshold[]      = L"MI406.Combine.Threshold";
static const wchar_t c_pwcsSATKeyMI406TimeThreshold[]         = L"MI406.Time.Threshold";

static const wchar_t c_pwcsSATKeyMI406Restart[]                = L"MI406.Restart";
static const wchar_t c_pwcsSATKeyMI406WindowFreq[]             = L"MI406.WindowFreq";
static const wchar_t c_pwcsSATKeyMI406WindowTime[]             = L"MI406.WindowTime";
static const wchar_t c_pwcsSATKeyMI406WindowBit[]              = L"MI406.WindowBit";
static const wchar_t c_pwcsSATKeyMI406OutOfSpecWindowBit[]     = L"MI406.WindowBit.OutOfSpec";

static const wchar_t c_pwcsSATKeyMI406IntegrateMaxFSErr[]      = L"MI406.Integrate.MaxFSErr";
static const wchar_t c_pwcsSATKeyMI406IntegrateMaxPDF1[]        = L"MI406.Integrate.MaxPDF1Err";
static const wchar_t c_pwcsSATKeyMI406IntegrateMaxPDF2[]        = L"MI406.Integrate.MaxPDF2Err";

static const wchar_t c_pwcsSATKeyMI406ConfirmMaxFSErr[]        = L"MI406.Confirm.MaxFSErr";
static const wchar_t c_pwcsSATKeyMI406ConfirmMaxPDF1[]          = L"MI406.Confirm.MaxPDF1Err";
static const wchar_t c_pwcsSATKeyMI406ConfirmMaxPDF2[]          = L"MI406.Confirm.MaxPDF2Err";

static const wchar_t c_pwcsSATKeyMI406ValidMaxFSErr[]          = L"MI406.Valid.MaxFSErr";
static const wchar_t c_pwcsSATKeyMI406ValidMaxPDF1[]            = L"MI406.Valid.MaxPDF1Err";
static const wchar_t c_pwcsSATKeyMI406ValidMaxPDF2[]            = L"MI406.Valid.MaxPDF2Err";

static const wchar_t c_pwcsSATKeyMI406CNR1Threshold[]          = L"MI406.CNR1.Threshold";
static const wchar_t c_pwcsSATKeyMI406CNR2Threshold[]          = L"MI406.CNR2.Threshold";
static const wchar_t c_pwcsSATKeyMI406MsgTimeout[]  		   = L"MI406.Msg.Timeout";

static const wchar_t c_pwcsSATKeyMI406IntegrateAgeout[]        = L"MI406.Integrate.Ageout";
static const wchar_t c_pwcsSATKeyMI406BeaconAgeout[]           = L"MI406.Beacon.Ageout";

static const wchar_t c_pwcsSATKeyMI406MsgMinInterval[]         = L"MI406.Msg.MinInterval";
static const wchar_t c_pwcsSATKeyMI406MsgMaxInterval[]         = L"MI406.Msg.MaxInterval";
static const wchar_t c_pwcsSATKeyMI406MsgValidInterval[]       = L"MI406.Msg.ValidInterval";

// obsolete?:
static const wchar_t c_pwcsSATKeyMI406MsgForceUpdate[]			= L"MI406.Msg.ForceUpdate";
static const wchar_t c_pwcsSATKeyMI406SarrOffsetThreshold[] 	= L"MI406.SarrOffset.Threshold";
static const wchar_t c_pwcsSATKeyMI406SummaryInterval[] 	      = L"MI406.Summary.Interval";

// ===================================================================================
// LEOGEO
static const wchar_t c_pwcsSATKeyLEOGEOCollect[]               = L"LEOGEO.Collect";
static const wchar_t c_pwcsSATKeyLEOGEOProcess[]               = L"LEOGEO.Process";
static const wchar_t c_pwcsSATKeyLEOGEOProcessMultiPass[]      = L"LEOGEO.Process.MultiPass";
static const wchar_t c_pwcsSATKeyLEOGEOProcessMultiSat[]       = L"LEOGEO.Process.MultiSat";
static const wchar_t c_pwcsSATKeyLEOGEOTransmitCalibrated[]    = L"LEOGEO.Transmit.Calibrated";
static const wchar_t c_pwcsSATKeyLEOGEOTransmitSolution[]      = L"LEOGEO.Transmit.Solution";
static const wchar_t c_pwcsSATKeyLEOGEOMCCSuppressLocated[]    = L"LEOGEO.MCCSuppress.Located";
static const wchar_t c_pwcsSATKeyLEOGEOMCCSuppressUnLocated[]  = L"LEOGEO.MCCSuppress.UnLocated";
static const wchar_t c_pwcsSATKeyLEOGEOMCCSuppressUnLocated1[] = L"LEOGEO.MCCSuppress.UnLocated1";
static const wchar_t c_pwcsSATKeyLEOGEOMCCSuppressUnLocated2[] = L"LEOGEO.MCCSuppress.UnLocated2";
static const wchar_t c_pwcsSATKeyLEOGEOMCCFilterCriteria[]     = L"LEOGEO.MCCFilter.Criteria";
static const wchar_t c_pwcsSATKeyLEOGEOFrequencyRange[]        = L"LEOGEO.Frequency.Range";
static const wchar_t c_pwcsSATKeyLEOGEONoisePassBand[]         = L"LEOGEO.Noise.PassBand";
static const wchar_t c_pwcsSATKeyLEOGEONoiseStopBand[]         = L"LEOGEO.Noise.StopBand";
static const wchar_t c_pwcsSATKeyLEOGEONoiseThreshold[]        = L"LEOGEO.Noise.Threshold";
static const wchar_t c_pwcsSATKeyLEOGEOSignalPassBand[]        = L"LEOGEO.Signal.PassBand";
static const wchar_t c_pwcsSATKeyLEOGEOSignalStopBand[]        = L"LEOGEO.Signal.StopBand";
static const wchar_t c_pwcsSATKeyLEOGEOSignalThreshold[]       = L"LEOGEO.Signal.Threshold";
static const wchar_t c_pwcsSATKeyLEOGEOCombineThreshold[]      = L"LEOGEO.Combine.Threshold";
static const wchar_t c_pwcsSATKeyLEOGEOTimeThreshold[]         = L"LEOGEO.Time.Threshold";

// ===================================================================================
// TCAL
static const wchar_t c_pwcsSATKeyTCALMaxAge[] 			       = L"TCAL.MaxAge";
static const wchar_t c_pwcsSATKeyTCALUpdatePeriod[]         = L"TCAL.UpdatePeriod";
static const wchar_t c_pwcsSATKeyTCALDuration[]				   = L"TCAL.Duration";
static const wchar_t c_pwcsSATKeyTCALMinPts[]               = L"TCAL.MinPts";
static const wchar_t c_pwcsSATKeyTCALTimeThreshold[]        = L"TCAL.Time.Threshold";
static const wchar_t c_pwcsSATKeyTCALFrequencyThreshold[]   = L"TCAL.Frequency.Threshold";
static const wchar_t c_pwcsSATKeyTCALFreqAverageCount[]	   = L"TCAL.FreqAverage.Count";
static const wchar_t c_pwcsSATKeyTCALTimeOffset[]	   		= L"TCAL.Time.Offset";

// ===================================================================================
// OrbitDet
static const wchar_t c_pwcsSATKeyOrbitDetPositionThreshold[]      = L"OrbitDet.Position.Threshold";
static const wchar_t c_pwcsSATKeyOrbitDetVelocityThreshold[]      = L"OrbitDet.Velocity.Threshold";
static const wchar_t c_pwcsSATKeyOrbitDetDurationMaximum[]        = L"OrbitDet.Duration.Maximum";
static const wchar_t c_pwcsSATKeyOrbitDetIterationRange[]         = L"OrbitDet.Iteration.Range";
static const wchar_t c_pwcsSATKeyOrbitDetResidualRange[]          = L"OrbitDet.Residual.Range";
static const wchar_t c_pwcsSATKeyOrbitDetDownlink[]               = L"OrbitDet.Downlink";
static const wchar_t c_pwcsSATKeyOrbitDetBeaconMinPts[]           = L"OrbitDet.Beacon.MinPts";

// ===================================================================================
// Orbit

static const wchar_t c_pwcsSATKeyOrbitDownlinkMinPts[]         = L"Orbit.Downlink.MinPts";
static const wchar_t c_pwcsSATKeyOrbitVersionMaximum[]         = L"Orbit.Version.Maximum";
static const wchar_t c_pwcsSATKeyOrbitInstallationFmt[]        = L"Orbit.Installation.";
static const wchar_t c_pwcsSATKeyOrbitEpochFmt[]               = L"Orbit.Epoch.";
static const wchar_t c_pwcsSATKeyOrbitPlaneFmt[]               = L"Orbit.Plane.";
static const wchar_t c_pwcsSATKeyOrbitShapeFmt[]               = L"Orbit.Shape.";
static const wchar_t c_pwcsSATKeyOrbitLocationFmt[]            = L"Orbit.Location.";
static const wchar_t c_pwcsSATKeyOrbitEffectiveFmt[]           = L"Orbit.Effective.";

static const wchar_t c_pwcsSATKeyOrbitVectorMaxAge[]           = L"Orbit.Vector.MaxAge";

// ===================================================================================
// Manoeuvre

static const wchar_t c_pwcsSATKeyManoeuvrePlanned[]            = L"Manoeuvre.Planned";

static const wchar_t c_pwcsSATKeyManoeuvreVersionMaximum[]     = L"Manoeuvre.Version.Maximum";
static const wchar_t c_pwcsSATKeyManoeuvreDataFmt[]            = L"Manoeuvre.Data.";

static const wchar_t c_pwcsSATKeyManoeuvreTypeInPlane[]        = L"in";
static const wchar_t c_pwcsSATKeyManoeuvreTypeOutOfPlane[]     = L"out";
static const wchar_t c_pwcsSATKeyManoeuvreTypeUnknown[]        = L"unknown";

// ===================================================================================
// Calib406
static const wchar_t c_pwcsSATKeyCalib406RTDelay[]          = L"Calib406.RT.Delay";
static const wchar_t c_pwcsSATKeyCalib406Tlast[]            = L"Calib406.Tlast";
static const wchar_t c_pwcsSATKeyCalib406SarrSarpCombine[]	= L"Calib406.SarrSarp.Combine";
static const wchar_t c_pwcsSATKeyCalib406SarrSarpFreqDiff[]	= L"Calib406.SarrSarp.FreqDiff";
static const wchar_t c_pwcsSATKeyCalib406SarrSarpTimeDiff[]	= L"Calib406.SarrSarp.TimeDiff";
static const wchar_t c_pwcsSATKeyCalib406SarrSarpAgeout[]	= L"Calib406.SarrSarp.Ageout";
static const wchar_t c_pwcsSATKeyCalib406SarrSarpMinCount[] = L"Calib406.SarrSarp.MinCount";

// ===================================================================================
// Locate406
static const wchar_t c_pwcsSATKeyLocate406IterationsMaximum[]    = L"Locate406.Iterations.Maximum";
static const wchar_t c_pwcsSATKeyLocate406Threshold[]            = L"Locate406.Threshold";
static const wchar_t c_pwcsSATKeyLocate406CorrelationMaximum[]   = L"Locate406.Correlation.Maximum";
static const wchar_t c_pwcsSATKeyLocate406Drift[]                = L"Locate406.Drift";
static const wchar_t c_pwcsSATKeyLocate406Altitude[]             = L"Locate406.Altitude";
static const wchar_t c_pwcsSATKeyLocate406EEFactors[]            = L"Locate406.EE.Factor";
static const wchar_t c_pwcsSATKeyLocate406EEAdjustments[]        = L"Locate406.EE.Adjustment";

static const wchar_t c_pwcsSATKeyLocate406EENomFactors[]            = L"Locate406.EE.NomFactor";
static const wchar_t c_pwcsSATKeyLocate406EENomAdjustments[]        = L"Locate406.EE.NomAdjustment";

static const wchar_t c_pwcsSATKeyLocate406MaxNoise[]				= L"Locate406.MaxNoise";
static const wchar_t c_pwcsSATKeyLocate406MinPtsVisible[]			= L"Locate406.MinPtsVisible";

// ===================================================================================
// CalibCBC
static const wchar_t c_pwcsSATKeyCalibCBCAmpMin[]				= L"CalibCBC.Amplitude.Minimum";
static const wchar_t c_pwcsSATKeyCalibCBCTimeRes[]				= L"CalibCBC.Time.Resolution";
static const wchar_t c_pwcsSATKeyCalibCBCFreqRes[]				= L"CalibCBC.Frequency.Resolution";
static const wchar_t c_pwcsSATKeyCalibCBCFreqBand[]			= L"CalibCBC.Frequency.Bandwidth";
static const wchar_t c_pwcsSATKeyCalibCBCCorrThres[]			= L"CalibCBC.Correlation.Threshold";
static const wchar_t c_pwcsSATKeyCalibCBCTempNum[]				= L"CalibCBC.Template.Number";
static const wchar_t c_pwcsSATKeyCalibCBCTempDuration[]		= L"CalibCBC.Template.Duration";

static const wchar_t c_pwcsSATKeyCalibCBCAudioDuration[]		= L"CalibCBC.Audio.Duration";
static const wchar_t c_pwcsSATKeyCalibCBCAudioBandwidth[]		= L"CalibCBC.Audio.Bandwidth";

// ===================================================================================
// LocateCBC
static const wchar_t c_pwcsSATKeyLocateCBCDetectMinimum[]        = L"LocateCBC.Detect.Minimum";
static const wchar_t c_pwcsSATKeyLocateCBCAmplitudeRange[]       = L"LocateCBC.Amplitude.Range";
static const wchar_t c_pwcsSATKeyLocateCBCIterationsMaximum[]    = L"LocateCBC.Iterations.Maximum";
static const wchar_t c_pwcsSATKeyLocateCBCThreshold[]            = L"LocateCBC.Threshold";
static const wchar_t c_pwcsSATKeyLocateCBCCorrelationMaximum[]   = L"LocateCBC.Correlation.Maximum";
static const wchar_t c_pwcsSATKeyLocateCBCDrift[]                = L"LocateCBC.Drift";
static const wchar_t c_pwcsSATKeyLocateCBCEEFactors[]            = L"LocateCBC.EE.Factor";
static const wchar_t c_pwcsSATKeyLocateCBCEEAdjustments[]        = L"LocateCBC.EE.Adjustment";
static const wchar_t c_pwcsSATKeyLocateCBCSweepThreshold[]       = L"LocateCBC.Sweep.Threshold";
static const wchar_t c_pwcsSATKeyLocateCBCSweepMinPoints[]       = L"LocateCBC.Sweep.MinPoints";

static const wchar_t c_pwcsSATKeyLocateCBCEENomFactors[]            = L"LocateCBC.EE.NomFactor";
static const wchar_t c_pwcsSATKeyLocateCBCEENomAdjustments[]        = L"LocateCBC.EE.NomAdjustment";

static const wchar_t c_pwcsSATKeyLocateCBCMaxNoise[]				= L"LocateCBC.MaxNoise";
static const wchar_t c_pwcsSATKeyLocateCBCMinPtsVisible[]			= L"LocateCBC.MinPtsVisible";

// LocateFDOA
static const wchar_t c_pwcsSATKeyLocateFDOAEEFactors[]            = L"LocateFDOA.EE.Factor";
static const wchar_t c_pwcsSATKeyLocateFDOAEEAdjustments[]        = L"LocateFDOA.EE.Adjustment";
static const wchar_t c_pwcsSATKeyLocateFDOAEENomFactors[]            = L"LocateFDOA.EE.NomFactor";
static const wchar_t c_pwcsSATKeyLocateFDOAEENomAdjustments[]        = L"LocateFDOA.EE.NomAdjustment";

// LocateTDOA
static const wchar_t c_pwcsSATKeyLocateTDOAEEFactors[]            = L"LocateTDOA.EE.Factor";
static const wchar_t c_pwcsSATKeyLocateTDOAEEAdjustments[]        = L"LocateTDOA.EE.Adjustment";
static const wchar_t c_pwcsSATKeyLocateTDOAEENomFactors[]            = L"LocateTDOA.EE.NomFactor";
static const wchar_t c_pwcsSATKeyLocateTDOAEENomAdjustments[]        = L"LocateTDOA.EE.NomAdjustment";
// ===================================================================================

#endif // __CONSTSATINFO_H__


