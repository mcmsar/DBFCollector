/********************************************************************
*	Module:			SatCons.h
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

  0.0 01/05/10	    rvw 	start

********************************************************************/
#ifndef INC_SATCONS
#define INC_SATCONS

const TCHAR c_szSectionHeading[]                = TEXT("SAT:");

const TCHAR c_szNoradID[]                       = TEXT("NoradID");
const TCHAR c_szDescription[]                   = TEXT("Description");
const TCHAR c_szPhaseMod[]                      = TEXT("PhaseMod");
const	TCHAR	c_szPassSchedPriority[]	            = TEXT("PassSchedule.Priority");

const TCHAR c_szChannelBaseband[]               = TEXT("Baseband");
const TCHAR c_szChannel121[]                    = TEXT("121");
const TCHAR c_szChannel243[]                    = TEXT("243");
const TCHAR c_szChannel406[]                    = TEXT("406");
const TCHAR c_szChannelPDS[]                    = TEXT("PDS");
const TCHAR c_szChannelFrequencyCentreFmt[]     = TEXT("%s.Frequency.Centre");
const TCHAR c_szChannelFrequencyBandwidthFmt[]  = TEXT("%s.Frequency.Bandwidth");

const TCHAR c_szDataSpectrum[]                  = TEXT("Spectrum");
const TCHAR c_szDataAudio[]                     = TEXT("Audio");
const TCHAR c_szDataSARR[]                      = TEXT("SARR");
const TCHAR c_szDataSARP[]                      = TEXT("SARP");
const TCHAR c_szDataCBC121[]                    = TEXT("CBC121");
const TCHAR c_szDataCBC243[]                    = TEXT("CBC243");
const TCHAR c_szDataCBC406[]                    = TEXT("CBC406");
const TCHAR c_szDataMI406[]                     = TEXT("MI406");
const TCHAR c_szDataLEOGEO[]                    = TEXT("LEOGEO");

const TCHAR c_szTestConfigTestSarpSarr[ ]		= TEXT("Test.SarpSarr.Locations");

const TCHAR c_szDataCollectFmt[]                = TEXT("%s.Collect");
const TCHAR c_szDataProcessFmt[]                = TEXT("%s.Process");
const TCHAR c_szDataProcessMultiPassFmt[]       = TEXT("%s.Process.MultiPass");
const TCHAR c_szDataProcessMultiSatFmt[]        = TEXT("%s.Process.MultiSat");

const TCHAR c_szDataTransmitCalibratedFmt[]     = TEXT("%s.Transmit.Calibrated");
const TCHAR c_szDataTransmitSolutionFmt[]       = TEXT("%s.Transmit.Solution");

const TCHAR c_szDataMCCSuppressLocatedFmt[]      = TEXT("%s.MCCSuppress.Located");
const TCHAR c_szDataMCCSuppressUnLocatedFmt[]    = TEXT("%s.MCCSuppress.UnLocated");
const TCHAR c_szDataMCCSuppressUnLocated1Fmt[]   = TEXT("%s.MCCSuppress.UnLocated1");
const TCHAR c_szDataMCCSuppressUnLocated2Fmt[]   = TEXT("%s.MCCSuppress.UnLocated2");

const TCHAR c_szDataMCCFilterCriteriaFmt[]      = TEXT("%s.MCCFilter.Criteria");

const TCHAR c_szDataFrequencyRangeFmt[]         = TEXT("%s.Frequency.Range");

const TCHAR c_szDataNoisePassBandFmt[]          = TEXT("%s.Noise.PassBand");
const TCHAR c_szDataNoiseStopBandFmt[]          = TEXT("%s.Noise.StopBand");
const TCHAR c_szDataNoiseThresholdFmt[]         = TEXT("%s.Noise.Threshold");

const TCHAR c_szDataSignalPassBandFmt[]         = TEXT("%s.Signal.PassBand");
const TCHAR c_szDataSignalStopBandFmt[]         = TEXT("%s.Signal.StopBand");
const TCHAR c_szDataSignalThresholdFmt[]        = TEXT("%s.Signal.Threshold");

const TCHAR c_szDataCombineThresholdFmt[]       = TEXT("%s.Combine.Threshold");
const TCHAR c_szDataTimeThresholdFmt[]          = TEXT("%s.Time.Threshold");

//const TCHAR c_szCalibCBCCTARange[]            = TEXT("CalibCBC.CTA.Range");
//const TCHAR c_szCalibCBCCTAIncrement[]        = TEXT("CalibCBC.CTA.Increment");
//const TCHAR c_szCalibCBCAmplitudeMinimum[]    = TEXT("CalibCBC.Amplitude.Minimum");
const TCHAR c_szCalibCBCAmpMin[]				= TEXT("CalibCBC.Amplitude.Minimum");
const TCHAR c_szCalibCBCTimeRes[]				= TEXT("CalibCBC.Time.Resolution");
const TCHAR c_szCalibCBCFreqRes[]				= TEXT("CalibCBC.Frequency.Resolution");
const TCHAR c_szCalibCBCFreqBand[]				= TEXT("CalibCBC.Frequency.Bandwidth");
const TCHAR c_szCalibCBCCorrThres[]				= TEXT("CalibCBC.Correlation.Threshold");
const TCHAR c_szCalibCBCTempNum[]				= TEXT("CalibCBC.Template.Number");
const TCHAR c_szCalibCBCTempDuration[]			= TEXT("CalibCBC.Template.Duration");

const TCHAR c_szLocateCBCDetectMinimum[]        = TEXT("LocateCBC.Detect.Minimum");
const TCHAR c_szLocateCBCAmplitudeRange[]       = TEXT("LocateCBC.Amplitude.Range");
const TCHAR c_szLocateCBCIterationsMaximum[]    = TEXT("LocateCBC.Iterations.Maximum");
const TCHAR c_szLocateCBCThreshold[]            = TEXT("LocateCBC.Threshold");
const TCHAR c_szLocateCBCCorrelationMaximum[]   = TEXT("LocateCBC.Correlation.Maximum");
const TCHAR c_szLocateCBCDrift[]                = TEXT("LocateCBC.Drift");
const TCHAR c_szLocateCBCEEFactors[]            = TEXT("LocateCBC.EE.Factor");
const TCHAR c_szLocateCBCEEAdjustments[]        = TEXT("LocateCBC.EE.Adjustment");
const TCHAR c_szLocateCBCSweepThreshold[]       = TEXT("LocateCBC.Sweep.Threshold");
const TCHAR c_szLocateCBCSweepMinPoints[]       = TEXT("LocateCBC.Sweep.MinPoints");

const TCHAR c_szCalib406RTDelay[]               = TEXT("Calib406.RT.Delay");
const TCHAR c_szCalib406Tlast[]                 = TEXT("Calib406.Tlast");

const TCHAR c_szCalib406SarrSarpCombine[]		= TEXT("Calib406.SarrSarp.Combine");
const TCHAR c_szCalib406SarrSarpFreqDiff[]		= TEXT("Calib406.SarrSarp.FreqDiff");
const TCHAR c_szCalib406SarrSarpTimeDiff[]		= TEXT("Calib406.SarrSarp.TimeDiff");
const TCHAR c_szCalib406SarrSarpAgeout[]		= TEXT("Calib406.SarrSarp.Ageout");
const TCHAR c_szCalib406SarrSarpMinCount[] 		= TEXT("Calib406.SarrSarp.MinCount");

const TCHAR c_szLocate406IterationsMaximum[]    = TEXT("Locate406.Iterations.Maximum");
const TCHAR c_szLocate406Threshold[]            = TEXT("Locate406.Threshold");
const TCHAR c_szLocate406CorrelationMaximum[]   = TEXT("Locate406.Correlation.Maximum");
const TCHAR c_szLocate406Drift[]                = TEXT("Locate406.Drift");
const TCHAR c_szLocate406Altitude[]             = TEXT("Locate406.Altitude");
const TCHAR c_szLocate406EEFactors[]            = TEXT("Locate406.EE.Factor");
const TCHAR c_szLocate406EEAdjustments[]        = TEXT("Locate406.EE.Adjustment");

const TCHAR c_szSARPType[]                      = TEXT("SARP.Type");
const TCHAR c_szSARPTimeField[]                 = TEXT("SARP.TimeField");
const TCHAR c_szSARPBitRate[]                   = TEXT("SARP.BitRate");
const TCHAR c_szSARPCalibrationTimeFmt[]        = TEXT("SARP.CalibrationTime.%i");
const TCHAR c_szSARPRolloverTimeFmt[]           = TEXT("SARP.RolloverTime.%i");
const TCHAR c_szSARPUSOFrequencyFmt[]           = TEXT("SARP.USOFrequency.%i");
const TCHAR c_szSARPEffectiveFmt[]              = TEXT("SARP.Effective.%i");
const TCHAR c_szSARPVersionMaximum[]            = TEXT("SARP.Version.Maximum");

const TCHAR c_szTCALUpdatePeriod[]				= TEXT("TCAL.UpdatePeriod");
const TCHAR c_szTCALDuration[]					= TEXT("TCAL.Duration");
const TCHAR c_szTCALMinPts[]                    = TEXT("TCAL.MinPts");
const TCHAR c_szTCALTimeThreshold[]             = TEXT("TCAL.Time.Threshold");
const TCHAR c_szTCALFrequencyThreshold[]        = TEXT("TCAL.Frequency.Threshold");

const TCHAR c_szSARRCalibrationTimeFmt[]        = TEXT("SARR.CalibrationTime.%i");
const TCHAR c_szSARRFreqOffsetFmt[]             = TEXT("SARR.FreqOffset.%i");
const TCHAR c_szSARRTimeOffsetFmt[]             = TEXT("SARR.TimeOffset.%i");
const TCHAR c_szSARREffectiveFmt[]              = TEXT("SARR.Effective.%i");
const TCHAR c_szSARRVersionMaximum[]            = TEXT("SARR.Version.Maximum");
const TCHAR c_szSARRDetectsMaximum[]            = TEXT("SARR.Detects.Maximum");
const TCHAR c_szSARRFSerrorsMaximum[]           = TEXT("SARR.FSerrors.Maximum");
const TCHAR c_szSARRDetectRange[]               = TEXT("SARR.Detect.Range");
const TCHAR c_szSARRDecayThreshold[]            = TEXT("SARR.Decay.Threshold");
const TCHAR c_szSARRCNRMinimum[]                = TEXT("SARR.CNR.Minimum");
const TCHAR c_szSARRPowerConversion[]           = TEXT("SARR.PowerConversion");
const TCHAR c_szSARRFreqBandAdj[]           	= TEXT("SARR.FreqBandAdjust");

const TCHAR c_szAudioFreqBands[]                = TEXT("Audio.FreqBands");
const TCHAR c_szAudioFileDuration[]             = TEXT("Audio.File.Duration");
const TCHAR c_szAudioFileSize[]                 = TEXT("Audio.File.Size");
const TCHAR c_szAudioArchiveDuration[]          = TEXT("Audio.Archive.Duration");
const TCHAR c_szAudioArchiveSize[]              = TEXT("Audio.Archive.Size");

const TCHAR c_szMI406Restart[]                  = TEXT("MI406.Restart");
const TCHAR c_szMI406WindowFreq[]               = TEXT("MI406.WindowFreq");
const TCHAR c_szMI406WindowTime[]               = TEXT("MI406.WindowTime");
const TCHAR c_szMI406WindowBit[]                = TEXT("MI406.WindowBit");
const TCHAR c_szMI406MaxFSerr[]                 = TEXT("MI406.MaxFSerr");
const TCHAR c_szMI406MaxPF1[]                   = TEXT("MI406.MaxPF1");
const TCHAR c_szMI406MaxPF2[]                   = TEXT("MI406.MaxPF2");
const TCHAR c_szMI406Ageout[]                   = TEXT("MI406.Ageout");
const TCHAR c_szMI406CNR1Threshold[]            = TEXT("MI406.CNR1.Threshold");
const TCHAR c_szMI406CNR2Threshold[]            = TEXT("MI406.CNR2.Threshold");
const TCHAR c_szMI406OutOfSpecWindowBit[]       = TEXT("MI406.WindowBit.OutOfSpec");
const TCHAR c_szMI406MsgTimeout[]  			    = TEXT("MI406.Msg.Timeout");
const TCHAR c_szMI406MsgForceUpdate[]			= TEXT("MI406.Msg.ForceUpdate");
const TCHAR c_szMI406SarrOffsetThreshold[] 	    = TEXT("MI406.SarrOffset.Threshold");
const TCHAR c_szMI406SummaryInterval[] 	     	= TEXT("MI406.Summary.Interval");

const TCHAR c_szMI406MaxConfirmFSerr[]          = TEXT("MI406.Confirm.MaxFSErr");
const TCHAR c_szMI406MaxConfirmPDF1[]           = TEXT("MI406.Confirm.MaxPDF1Err");
const TCHAR c_szMI406MaxConfirmPDF2[]           = TEXT("MI406.Confirm.MaxPDF2Err");

const TCHAR c_szMI406MaxIntegrateFSerr[]          = TEXT("MI406.Integrate.MaxFSErr");
const TCHAR c_szMI406MaxIntegratePDF1[]           = TEXT("MI406.Integrate.MaxPDF1Err");
const TCHAR c_szMI406MaxIntegratePDF2[]           = TEXT("MI406.Integrate.MaxPDF2Err");

const TCHAR c_szMI406MaxValidFSerr[]          = TEXT("MI406.Valid.MaxFSErr");
const TCHAR c_szMI406MaxValidPDF1[]           = TEXT("MI406.Valid.MaxPDF1Err");
const TCHAR c_szMI406MaxValidPDF2[]           = TEXT("MI406.Valid.MaxPDF2Err");

const TCHAR c_szMI406MinUpdateInterval[]	  = TEXT("MI406.Msg.MinInterval");
const TCHAR c_szMI406MaxUpdateInterval[]		  = TEXT("MI406.Msg.MaxInterval");
const TCHAR c_szMI406ValidUpdateInterval[]		  = TEXT("MI406.Msg.ValidInterval");

const TCHAR c_szMI406BeaconAgeout[]           = TEXT("MI406.Beacon.Ageout");
const TCHAR c_szMI406IntegrateAgeout[]         = TEXT("MI406.Integrate.Ageout");

const TCHAR c_szOrbitPositionThreshold[]        = TEXT("OrbitDet.Position.Threshold");
const TCHAR c_szOrbitVelocityThreshold[]        = TEXT("OrbitDet.Velocity.Threshold");
const TCHAR c_szOrbitDurationMaximum[]          = TEXT("OrbitDet.Duration.Maximum");
const TCHAR c_szOrbitIterationRange[]           = TEXT("OrbitDet.Iteration.Range");
const TCHAR c_szOrbitResidualRange[]            = TEXT("OrbitDet.Residual.Range");
const TCHAR c_szOrbitDownlink[]                 = TEXT("OrbitDet.Downlink");
const TCHAR c_szOrbitBeaconMinPts[]             = TEXT("OrbitDet.Beacon.MinPts");

const TCHAR c_szOrbitInstallationFmt[]          = TEXT("Orbit.Installation.%i");
const TCHAR c_szOrbitEpochFmt[]                 = TEXT("Orbit.Epoch.%i");
const TCHAR c_szOrbitPlaneFmt[]                 = TEXT("Orbit.Plane.%i");
const TCHAR c_szOrbitShapeFmt[]                 = TEXT("Orbit.Shape.%i");
const TCHAR c_szOrbitLocationFmt[]              = TEXT("Orbit.Location.%i");
const TCHAR c_szOrbitEffectiveFmt[]             = TEXT("Orbit.Effective.%i");
const TCHAR c_szOrbitDownlinkMinPts[]           = TEXT("Orbit.Downlink.MinPts");
const TCHAR c_szOrbitVersionMaximum[]           = TEXT("Orbit.Version.Maximum");

const TCHAR c_szManoeuvreDataFmt[]              = TEXT("Manoeuvre.Data.%i");
const TCHAR c_szManoeuvreVersionMaximum[]       = TEXT("Manoeuvre.Version.Maximum");


// Default values.
const BYTE   c_byDefCalibCBCAmpMin				= 0;
const double c_dDefCalibCBCTimeRes				= 3.0;
const double c_dDefCalibCBCFreqRes				= 100.0;
const double c_dDefCalibCBCFreqBand				= 400.0;
const double c_dDefCalibCBCCorrThres			= 20184002.0;
const long   c_lDefCalibCBCTempNum				= 64;
const double c_dDefCalibCBCTempDuration			= 600.0;

const double c_dDefTCALUpdatePeriod				= 0.5;
const double c_dDefTCALDuration					= 10.0;
const long   c_lDefTCALMinPts				    = 200;
const double c_dDefTCALTimeThresh				= 0.100;
const double c_dDefTCALFrequencyThreshold		= 0.100;

const double c_dDefOrbitPositionThreshold       = 25.0; 
const double c_dDefOrbitVelocityThreshold       = 25.0; 
const double c_dDefOrbitDurationMaximum         = 3.0; 
const int    c_ulDefOrbitIterationRangeMin      = 25;
const int    c_ulDefOrbitIterationRangeMax      = 100;
const double c_dDefOrbitResidualRangeMin        = 0.001; 
const double c_dDefOrbitResidualRangeMax        = 50.0; 
const BOOL   c_bDefOrbitDownlink                = TRUE;
const ULONG  c_ulDefOrbitBeaconMinPts           = 500;

const ULONG  c_ulDefLocateCBCDetectMinimum      = 40;  // ???
const BYTE   c_byDefLocateCBCAmplitudeRangeMin  = 0;
const BYTE   c_byDefLocateCBCAmplitudeRangeMax  = 7;
const ULONG  c_ulDefLocateCBCIterationsMaximum  = 50;
const double c_dDefLocateCBCThreshold           = 2.0;
const double c_dDefLocateCBCCorrelationMaximum  = 0.99;
const BOOL   c_bDefLocateCBCDrift               = TRUE;
const int    c_iDefLocateCBCNumberEEs           = 3;
const double c_dDefLocateCBCEEFactors[c_iDefLocateCBCNumberEEs]     = {5.50, 5.50, 5.50};
const double c_dDefLocateCBCEEAdjustments[c_iDefLocateCBCNumberEEs] = {0.75, 0.75, 0.75};
const double c_dDefLocateCBCSweepThreshold      = 60.0;
const ULONG  c_ulDefLocateCBCSweepMinPoints     = 60;

const ULONG  c_ulDefLocate406IterationsMaximum  = 50;
const double c_dDefLocate406Threshold           = 2.0;
const double c_dDefLocate406CorrelationMaximum  = 0.99;
const BOOL   c_bDefLocate406Drift               = TRUE;
const BOOL   c_bDefLocate406Altitude            = TRUE;
const int    c_iDefLocate406NumberEEs           = 3;
const double c_dDefLocate406EEFactors[c_iDefLocate406NumberEEs]     = {1.65, 1.65, 1.65}; // SARP, SARR, SARP/SARR
const double c_dDefLocate406EEAdjustments[c_iDefLocate406NumberEEs] = {0.75, 1.30, 0.75};

#endif // INC_SATCONS
