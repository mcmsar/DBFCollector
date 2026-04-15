#ifndef __EMS_DB_FIELD_NAMES_H__
#define __EMS_DB_FIELD_NAMES_H__

#include <wchar.h>
#include "dal.h"

// Common fields.
static const wchar_t* cwszTimestamp = L"timestamp";
static const wchar_t* cwszLutID = L"ulLutID";
static const wchar_t* cwszSatID = L"ulSatID";
static const wchar_t* cwszPassID = L"ulPassID";
static const wchar_t* cwszType = L"wType";

// Antenna_Stats
static const wchar_t* cwszAntennaElevationD = L"fElevationTx";
static const wchar_t* cwszAntennaAzimuthD = L"fAzimuthTx";
static const wchar_t* cwszAntennaElevationA = L"fElevationRx";
static const wchar_t* cwszAntennaAzimuthA = L"fAzimuthRx";
static const wchar_t* cwszAntennaStatus = L"uAntennaStatus";

// Calib406
static const wchar_t* cwszCalib406BeaconID = L"i64BeaconID";
static const wchar_t* cwszCalib406TimeMsg = L"i64TimeMsg";
static const wchar_t* cwszCalib406TimeOffset = L"i64TimeOffset";
static const wchar_t* cwszCalib406Status = L"wStatus";
static const wchar_t* cwszCalib406DuplicateMsgCount = L"wDuplicateMsgCount";
static const wchar_t* cwszCalib406Frequency = L"dFrequency";
static const wchar_t* cwszCalib406FreqOffset = L"fFreqOffset";
static const wchar_t* cwszCalib406CarrierPower = L"fCarrierPower";
static const wchar_t* cwszCalib406BitErrorField1 = L"wBitErrorField1";
static const wchar_t* cwszCalib406BitErrorField2 = L"wBitErrorField2";
static const wchar_t* cwszCalib406BitErrorFrameSynch = L"wBitErrorFrameSynch";
static const wchar_t* cwszCalib406Msg = L"cMsg";

// CalibCBC
static const wchar_t* cwszCalibCBCCalibID = L"i64CalibID";
static const wchar_t* cwszCalibCBCSequenceNumber = L"ulSeqNumber";
static const wchar_t* cwszCalibCBCFrequency = L"dFrequency";
static const wchar_t* cwszCalibCBCFreqOffset = L"fFreqOffset";
static const wchar_t* cwszCalibCBCFreqAccuracy = L"fFreqAccuracy";
static const wchar_t* cwszCalibCBCPower = L"fPower";
static const wchar_t* cwszCalibCBCSweepPeriod = L"fSweepPeriod";
static const wchar_t* cwszCalibCBCSweepSpan = L"fSweepSpan";
static const wchar_t* cwszCalibCBCSweepCorrelation = L"fSweepCorrelation";
static const wchar_t* cwszCalibCBCTCALIE = L"i64TcaIE";
static const wchar_t* cwszCalibCBCBiasIE = L"fBiasIE";
static const wchar_t* cwszCalibCBCCtaIE = L"fCtaIE";

// CalibCBC Status
static const wchar_t* cwszCalibCBCStatStatus = L"wStatus";
static const wchar_t* cwszCalibCBCStatNumBeacons = L"ulNumBeacons";
static const wchar_t* cwszCalibCBCStatInputRecords = L"ulInputRecords";
static const wchar_t* cwszCalibCBCStatUncalibratedRecords = L"ulCalibratedRecords";

// CBC (raw)
static const wchar_t* cwszCBCFreqOffset = L"fFreqOffset";
static const wchar_t* cwszCBCFreqQFactor = L"fFreqQFactor";
static const wchar_t* cwszCBCEntryCount = L"wEntryCount";
static const wchar_t* cwszCBCFrequency = L"wFrequency";
static const wchar_t* cwszCBCSweepPeriod = L"wSweepPeriod";
static const wchar_t* cwszCBCSweepCorrelation = L"wSweepCorrelation";
static const wchar_t* cwszCBCSweepSpan = L"wSweepSpan";
static const wchar_t* cwszCBCThreshold = L"fThreshold";
static const wchar_t* cwszCBCAmplitude = L"cAmplitude";

// Collector Status
static const wchar_t* cwszCollectorStatus = L"uCollectorStatus";
static const wchar_t* cwszCollectorCarrierTime = L"u64CarrierTime";
static const wchar_t* cwszCollectorCarrierLossCount = L"uCarrierLossCount";
static const wchar_t* cwszCollectorCarrierLossDuration = L"uCarrierLossDuration";
static const wchar_t* cwszCollectorCarrierFrequency = L"fCarrierFrequency";
static const wchar_t* cwszCollectorModIndex = L"fModIndexMax";
static const wchar_t* cwszCollectorModIndexMean = L"fModIndexMean";
static const wchar_t* cwszCollectorModIndexRMS = L"fModIndexRMS";
static const wchar_t* cwszCollectorADCMean = L"fADCMean";
static const wchar_t* cwszCollectorADCRMS = L"fADCRMS";
static const wchar_t* cwszCollectorMarkerBitRate = L"ulMarkerBitRate";

// Combine406
static const wchar_t* cwszCombine406BeaconID = L"i64BeaconID";
static const wchar_t* cwszCombine406Time1 = L"timestamp1";
static const wchar_t* cwszCombine406LutID1 = L"ulLutID1";
static const wchar_t* cwszCombine406SatID1 = L"ulSatID1";
static const wchar_t* cwszCombine406PassID1 = L"ulPassID1";
static const wchar_t* cwszCombine406Type1 = L"wType1";
static const wchar_t* cwszCombine406Time2 = L"timestamp2";
static const wchar_t* cwszCombine406LutID2 = L"ulLutID2";
static const wchar_t* cwszCombine406SatID2 = L"ulSatID2";
static const wchar_t* cwszCombine406PassID2 = L"ulPassID2";
static const wchar_t* cwszCombine406Type2 = L"wType2";

// Combine406 Status
static const wchar_t* cwszCombine406Status = L"wStatus";
static const wchar_t* cwszCombine406StatusGeoSarrHistRecsCurrent = L"ulGeoSarrHistoryRecordsCurrent";
static const wchar_t* cwszCombine406StatusGeoSarrHistRecsInput = L"ulGeoSarrHistoryRecordsInput";
static const wchar_t* cwszCombine406StatusGeoSarrHistRecsOutput = L"ulGeoSarrHistoryRecordsOutput";
static const wchar_t* cwszCombine406StatusLeoCalib406RecsInput = L"ulLeoCalib406RecordsInput";
static const wchar_t* cwszCombine406StatusCombinedRecsOutput = L"ulCombinedRecordsOutput";
static const wchar_t* cwszCombine406StatusNumBeacons = L"ulNumBeacons";

// Comms Status
static const wchar_t* cwszCommsStatus = L"wCommsStatus";
static const wchar_t* cwszCommsStatusMsgID = L"ulMsgID";
static const wchar_t* cwszCommsStatusRouteID = L"ulRouteID";
static const wchar_t* cwszCommsStatusTimeTx = L"u64TimeTx";
static const wchar_t* cwszCommsStatusRetryCount = L"ulRetryCount";
static const wchar_t* cwszCommsStatusLossCount = L"ulLossCount";
static const wchar_t* cwszCommsStatusLossDuration = L"ulLossDuration";

// Configuration
static const wchar_t* cwszConfigSourceID = L"ulSourceID";
static const wchar_t* cwszConfigFileLevel = L"wFileLevel";
static const wchar_t* cwszConfigGroup = L"szGroup";
static const wchar_t* cwszConfigGroupID = L"szGroupID";
static const wchar_t* cwszConfigField = L"szField";
static const wchar_t* cwszConfigValues = L"szValues";
static const wchar_t* cwszConfigSourceName = L"szSourceName";

// GEO Calib406 Status
static const wchar_t* cwszGeoCalib406StatusNumGroups = L"ulNumGroups";
static const wchar_t* cwszGeoCalib406StatusNumDetections = L"ulNumDetections";
static const wchar_t* cwszGeoCalib406StatusNumRawMsgs = L"ulNumRawMsgs";
static const wchar_t* cwszGeoCalib406StatusNumIntMsgs = L"ulNumIntMsgs";
static const wchar_t* cwszGeoCalib406StatusNumBeaconID = L"ulNumBeaconID";
static const wchar_t* cwszGeoCalib406StatusTimeLastDetect = L"timeLastDetection";
static const wchar_t* cwszGeoCalib406StatusTimeLastRefDetect = L"timeLastRefDetection";

// GEO Status
static const wchar_t* cwszGeoStatusTimeStart = L"timeStart";
static const wchar_t* cwszGeoStatusTimeEnd = L"timeEnd";
static const wchar_t* cwszGeoStatusDuration = L"dDuration";
static const wchar_t* cwszGeoStatusDurLoss = L"dDurLoss";
static const wchar_t* cwszGeoStatusNumGroups = L"ulNumGroups";
static const wchar_t* cwszGeoStatusNumGroupsMax = L"ulNumGroupsMax";
static const wchar_t* cwszGeoStatusNumGroupsMin = L"ulNumGroupsMin";
static const wchar_t* cwszGeoStatusNumDetections = L"ulNumDetections";
static const wchar_t* cwszGeoStatusNumRawMsgs = L"ulNumRawMsgs";
static const wchar_t* cwszGeoStatusNumIntMsgs = L"ulNumIntMsgs";
static const wchar_t* cwszGeoStatusNumBeaconID = L"ulNumBeaconID";
static const wchar_t* cwszGeoStatusTimeLastDetection = L"timeLastDetection";
static const wchar_t* cwszGeoStatusTimeLastRefDetection = L"timeLastRefDetection";
static const wchar_t* cwszGeoStatusNumAlarms = L"ulNumAlarms";
static const wchar_t* cwszGeoStatusNumWarnings = L"ulNumWarnings";

// LEO Calib406 Status
static const wchar_t* cwszLeoCalib406Status = L"wStatus";
static const wchar_t* cwszLeoCalib406StatusNumBeacons = L"ulNumBeacons";
static const wchar_t* cwszLeoCalib406StatusNumRefBeaconRecords = L"ulNumRefBeaconRecords";
static const wchar_t* cwszLeoCalib406StatusInputRecords = L"ulInputRecords";
static const wchar_t* cwszLeoCalib406StatusCalibratedRecords = L"ulCalibratedRecords";
static const wchar_t* cwszLeoCalib406StatusHistoryRecords = L"ulHistoryRecords";

// Locate
static const wchar_t* cwszLocateSatIDs = L"cSatIDs";
static const wchar_t* cwszLocateLutIDs = L"cLutIDs";
static const wchar_t* cwszLocateBeaconID = L"u64BeaconID";
static const wchar_t* cwszLocateNumMsgs = L"wNumMsgs";
static const wchar_t* cwszLocateNumMsgsUsed = L"wNumMsgsUsed";
static const wchar_t* cwszLocateNumIterations = L"wNumIterations";
static const wchar_t* cwszLocateTimeTCA = L"u64TimeTCA";
static const wchar_t* cwszLocateWindowsFactor = L"wWindowFactor";
static const wchar_t* cwszLocateFrequency = L"dFrequency";
static const wchar_t* cwszLocateConfidence = L"fConfidence";
static const wchar_t* cwszLocateProbability = L"fProbability";
static const wchar_t* cwszLocatePower = L"fPower";
static const wchar_t* cwszLocateRadiusErrEllipse = L"fRadiusErrEllipse";
static const wchar_t* cwszLocateFreqBiasError = L"fFreqBiasError";
static const wchar_t* cwszLocateFreqDrift = L"fFreqDrift";
static const wchar_t* cwszLocateCrossTrackAngle = L"fCrossTrackAngle";
static const wchar_t* cwszLocateMajorError = L"fMajorError";
static const wchar_t* cwszLocateMinorError = L"fMinorError";
static const wchar_t* cwszLocateHeading = L"fHeading";
static const wchar_t* cwszLocateNoise = L"fNoise";
static const wchar_t* cwszLocateTrend = L"fTrend";
static const wchar_t* cwszLocateCoVarianceMatrix = L"fCoVarianceMatrix";
static const wchar_t* cwszLocateDegLatitude = L"dDegLatitude";
static const wchar_t* cwszLocateDegLongitude = L"dDegLongitude";
static const wchar_t* cwszLocateAltitude = L"fAltitude";
static const wchar_t* cwszLocateSweepError = L"fSweepError";
static const wchar_t* cwszLocateSidebands = L"wSideBands";
static const wchar_t* cwszLocateBeaconMsg = L"cBeaconMsg";
static const wchar_t* cwszLocateBitErrorFS = L"wBitErrorFS";
static const wchar_t* cwszLocateBitErrorField1 = L"wBitErrorField1";
static const wchar_t* cwszLocateBitErrorField2 = L"wBitErrorField2";
static const wchar_t* cwszLocateSweep = L"fSweep";
static const wchar_t* cwszLocateNumBurstsUsed = L"wNumBurstsUsed";
static const wchar_t* cwszLocateDataStartTime = L"u64DataStartTime";
static const wchar_t* cwszLocateDataEndTime = L"u64DataEndTime";

// Locate Status
static const wchar_t* cwszLocateStatus = L"wStatus";
static const wchar_t* cwszLocateStatusNumBeacons = L"ulNumBeacons";
static const wchar_t* cwszLocateStatusInputRecords = L"ulInputRecords";
static const wchar_t* cwszLocateStatusTotalCBC121Solutions = L"wTotalCBC121Solutions";
static const wchar_t* cwszLocateStatusTotalCBC243Solutions = L"wTotalCBC243Solutions";
static const wchar_t* cwszLocateStatusTotalCBC406Solutions = L"wTotalCBC406Solutions";
static const wchar_t* cwszLocateStatusTotal406Solutions = L"wTotal406Solutions";
static const wchar_t* cwszLocateStatusTotal406USolutions = L"wTotal406ULSolutions";
static const wchar_t* cwszLocateStatusTotal406FdoaSolutions = L"wTotal406FdoaSolutions";
static const wchar_t* cwszLocateStatusTotal406SingleBursts = L"wTotal406SingleBursts";
static const wchar_t* cwszLocateStatusResidualRecords = L"ulResidualRecords";

// Log
static const wchar_t* cwszLogProcessID = L"ulProcessID";
static const wchar_t* cwszLogMsgNumber = L"dwMsgNumber";
static const wchar_t* cwszLogTaskID = L"cTaskID";
static const wchar_t* cwszLogMsgType = L"cMsgType";
static const wchar_t* cwszLogMsg = L"cMsg";

// Orbit
static const wchar_t* cwszOrbitTimeEffective = L"i64TimeEffective";
static const wchar_t* cwszOrbitTimeEpoch = L"i64TimeEpoch";
static const wchar_t* cwszOrbitXndt2o = L"fXndt2o";
static const wchar_t* cwszOrbitXndd6o = L"fXndd6o";
static const wchar_t* cwszOrbitBStar = L"fBStar";
static const wchar_t* cwszOrbitInclination = L"fInclination";
static const wchar_t* cwszOrbitRightAscNode = L"fRightAscNode";
static const wchar_t* cwszOrbitEccentricity = L"fEccentricity";
static const wchar_t* cwszOrbitArgPerigee = L"fArgPerigee";
static const wchar_t* cwszOrbitMeanAnomaly = L"fMeanAnomaly";
static const wchar_t* cwszOrbitMeanMotion = L"fMeanMotion";
static const wchar_t* cwszOrbitVelocityDifference = L"fVelocityDifference";
static const wchar_t* cwszOrbitRadiusDifference = L"fRadiusDifference";
static const wchar_t* cwszOrbitCoVarMatrix = L"dCoVarMatrix";

// Orbit Status
static const wchar_t* cwszOrbitStatus = L"wStatus";
static const wchar_t* cwszOrbitStatusDownLink = L"wNumDownlink";
static const wchar_t* cwszOrbitStatusDownLinkUsed = L"wNumDownlinkUsed";
static const wchar_t* cwszOrbitStatusNum406 = L"wNum406";
static const wchar_t* cwszOrbitStatusNum406Used = L"wNum406Used";
static const wchar_t* cwszOrbitStatusMeanResidualInput = L"fMeanResidualInput";
static const wchar_t* cwszOrbitStatusMeanResidualOutput = L"fMeanResidualOutput";
static const wchar_t* cwszOrbitStatusStdDevResidualInput = L"fStdDevResidualInput";
static const wchar_t* cwszOrbitStatusStdDevResidualOutput = L"fStdDevResidualOutput";
static const wchar_t* cwszOrbitStatusPositionDifference = L"fPositionDifference";
static const wchar_t* cwszOrbitStatusVelocityDifference = L"fVelocityDifference";

// Pass Status (Pass Summary)
static const wchar_t* cwszPassStatusSecsDuration = L"wSecsDuration";
static const wchar_t* cwszPassStatusSecsCollecting = L"wSecsCollecting";
static const wchar_t* cwszPassStatusPercentageCollecting = L"wPercentageCollecting";
static const wchar_t* cwszPassStatusPDSRecoverRate = L"nPDSRecoveryRate";
static const wchar_t* cwszPassStatusFramesMissed = L"wFramesMissed";
static const wchar_t* cwszPassStatusTotalPDSCount = L"nTotalPDSCount";
static const wchar_t* cwszPassStatusDistinctPDSCount = L"nDistinctPDSCount";
static const wchar_t* cwszPassStatusSarrMessages = L"wSarrMessages";
static const wchar_t* cwszPassStatusOrbitEpoch = L"timeOrbitEpoch";
static const wchar_t* cwszPassStatusOrbitPositionX = L"fOrbitPositionX";
static const wchar_t* cwszPassStatusOrbitPositionY = L"fOrbitPositionY";
static const wchar_t* cwszPassStatusOrbitPositionZ = L"fOrbitPositionZ";
static const wchar_t* cwszPassStatusOrbitVelocityX = L"fOrbitVelocityX";
static const wchar_t* cwszPassStatusOrbitVelocityY = L"fOrbitVelocityY";
static const wchar_t* cwszPassStatusOrbitVelocityZ = L"fOrbitVelocityZ";
static const wchar_t* cwszPassStatusOrbitUpdateStatus = L"wOrbitUpdateStatus";
static const wchar_t* cwszPassStatusOrbitPositionOffset = L"fOrbitPositionOffset";
static const wchar_t* cwszPassStatusOrbitVelocityOffset = L"fOrbitVelocityOffset";
static const wchar_t* cwszPassStatusCalibrationTime = L"timeCalibration";
static const wchar_t* cwszPassStatusRolloverTime = L"timeRollover";
static const wchar_t* cwszPassStatusUSOFreq = L"fUSOFreq";
static const wchar_t* cwszPassStatusSarrFreqOffset = L"fSARRFreqOffset";
static const wchar_t* cwszPassStatusSolnProcessingTime = L"timeSolnProcessing";
static const wchar_t* cwszPassStatus121Transmitters = L"w121Transmitters";
static const wchar_t* cwszPassStatus243Transmitters = L"w243Transmitters";
static const wchar_t* cwszPassStatus406Interferers = L"w406Interferers";
static const wchar_t* cwszPassStatus406LocatedBeacons = L"w406LocatedBeacons";
static const wchar_t* cwszPassStatus406UnlocatedBeacons = L"w406UnlocatedBeacons";
static const wchar_t* cwszPassStatusUnlocatedAlerts = L"wUnlocatedAlerts";
static const wchar_t* cwszPassStatusWarnings = L"wWarnings";
static const wchar_t* cwszPassStatusAlarms = L"wAlarms";
static const wchar_t* cwszPassStatusSatTrackDataTimestamp = L"sat_track_data_timestamp";
static const wchar_t* cwszPassStatusNextSatID= L"ulNextSatID";
static const wchar_t* cwszPassStatusNextPassID= L"ulNextPassID";
static const wchar_t* cwszPassStatusTimeActualAOS = L"timeActualAOS";
static const wchar_t* cwszPassStatusTimeActualLOS = L"timeActualLOS";
static const wchar_t* cwszPassStatusTimeLastClockSync = L"timeLastClockSync";
static const wchar_t* cwszPassStatusTimeMsgSARPCalibNewest = L"timeMsgSARPCalibNewest";
static const wchar_t* cwszPassStatusTimeMsgSARPCalibOldest = L"timeMsgSARPCalibOldest";
static const wchar_t* cwszPassStatusMedianLocnErrorSampleCount = L"wMedianLocnErrorSampleCount";
static const wchar_t* cwszPassStatusMedianLocnError = L"dMedianLocnError";
static const wchar_t* cwszPassStatusOrbitNumberAtEpoch = L"ulOrbitNumberAtEpoch";
static const wchar_t* cwszPassStatusGeneralStatus = L"wGeneralStatus";
static const wchar_t* cwszPassStatusUnusedDbl1 = L"dUnused1";
static const wchar_t* cwszPassStatusUnusedDbl2 = L"dUnused2";
static const wchar_t* cwszPassStatusUnusedDbl3 = L"dUnused3";
static const wchar_t* cwszPassStatusUnusedDbl4 = L"dUnused4";
static const wchar_t* cwszPassStatusUnusedInt1 = L"iUnused1";
static const wchar_t* cwszPassStatusUnusedInt2 = L"iUnused2";
static const wchar_t* cwszPassStatusTimeUnused1 = L"timeUnused1";
static const wchar_t* cwszPassStatusTimeUnused2 = L"timeUnused2";
static const wchar_t* cwszPassStatusUSOFreqDbl = L"dUSOFreq";
static const wchar_t* cwszPassStatusSarrFreqOffsetDbl = L"dSARRFreqOffset";

// Residual
static const wchar_t* cwszResidualReferenceID = L"ulReferenceID";
static const wchar_t* cwszResidualBeaconID = L"i64BeaconID";
static const wchar_t* cwszResidualMsgTime = L"timeMsg";
static const wchar_t* cwszResidualMeasurement = L"dMeasurement";
static const wchar_t* cwszResidual = L"fResidual";
static const wchar_t* cwszResidualPower = L"fPower";
static const wchar_t* cwszResidualProcessFlag = L"wProcessFlag";

// SARP Calibration
static const wchar_t* cwszSARPCalibSource = L"wSource";
static const wchar_t* cwszSARPCalibEffectiveTime = L"i64TimeEffective";
static const wchar_t* cwszSARPCalibTCALNumber = L"ulTCALNumber";
static const wchar_t* cwszSARPCalibRolloverTime = L"timeRollover";
static const wchar_t* cwszSARPCalibUSOFrequency = L"dUSOFrequency";

static const wchar_t* cwszSARPCalibUSOFrequency_124 = L"fUSOFrequency";

// SARP Calibration Status
static const wchar_t* cwszSARPCalibStatus = L"wStatus";
static const wchar_t* cwszSARPCalibStatusTCALNumber = L"ulTCALNumber";
static const wchar_t* cwszSARPCalibStatusRolloverTime = L"timeRollover";
static const wchar_t* cwszSARPCalibStatusUSOFrequency = L"dUSOFrequency";
static const wchar_t* cwszSARPCalibStatusNumMsg = L"ulNumMsg";
static const wchar_t* cwszSARPCalibStatusNumMsgUsed = L"ulNumMsgUsed";
static const wchar_t* cwszSARPCalibStatusResidualMean = L"fResidualMean";
static const wchar_t* cwszSARPCalibStatusResidualStdDev = L"fResidualStdDev";
static const wchar_t* cwszSARPCalibStatusResidualMax = L"fResidualMax";
static const wchar_t* cwszSARPCalibStatusRolloverError = L"fRolloverError";
static const wchar_t* cwszSARPCalibStatusFreqCorrectionError = L"fFreqCorrectionError";
static const wchar_t* cwszSARPCalibStatusCorrelationCoef = L"fCorrelationCoef";
static const wchar_t* cwszSARPCalibStatusRolloverPropogationError = L"fRolloverPropogationError";

static const wchar_t* cwszSARPCalibStatusUSOFrequency_124 = L"fUSOFrequency";

// SARP
static const wchar_t* cwszSARPBeaconID = L"u64BeaconID";
static const wchar_t* cwszSARPMsgTime = L"u64TimeMsg";
static const wchar_t* cwszSARPTimeOffset = L"u64TimeOffset";
static const wchar_t* cwszSARPStatus = L"wStatus";
static const wchar_t* cwszSARPFrequency = L"dFrequency";
static const wchar_t* cwszSARPFrequencyOffset = L"fFrequencyOffset";
static const wchar_t* cwszSARPAvgPower = L"fAvgPower";
static const wchar_t* cwszSARPCarrierPower = L"fCarrierPower";
static const wchar_t* cwszSARPBitErrorField1 = L"wBitErrorField1";
static const wchar_t* cwszSARPBitErrorField2 = L"wBitErrorField2";
static const wchar_t* cwszSARPBitRate = L"fBitRate";
static const wchar_t* cwszSARPMsgType = L"wMsgType";
static const wchar_t* cwszSARPBeaconMsg = L"cBeaconMsg";
static const wchar_t* cwszSARPMsg = L"cMsg";

// SARR Calibration
static const wchar_t* cwszSARRCalibSource = L"wSource";
static const wchar_t* cwszSARRCalibEffectiveTime = L"i64TimeEffective";
static const wchar_t* cwszSARRCalibSarrNumber = L"ulSarrNumber";
static const wchar_t* cwszSARRCalibFreqOffset = L"fFreqOffset";
static const wchar_t* cwszSARRCalibFreqDrift = L"fFreqDrift";
static const wchar_t* cwszSARRCalibOffsetTime = L"i64TimeOffset";

// SARR Calibration Status
static const wchar_t* cwszSARRCalibStatus = L"wStatus";
static const wchar_t* cwszSARRCalibStatusSarrNumber = L"ulSARRNumber";
static const wchar_t* cwszSARRCalibStatusFreqOffset = L"fFreqOffset";
static const wchar_t* cwszSARRCalibStatusFreqDrift = L"fFreqDrift";
static const wchar_t* cwszSARRCalibStatusOffsetTime = L"i64TimeOffset";
static const wchar_t* cwszSARRCalibStatusNumMsg = L"ulNumMsg";
static const wchar_t* cwszSARRCalibStatusNumMsgUsed = L"ulNumMsgUsed";
static const wchar_t* cwszSARRCalibStatusFreqResidualMean = L"fFreqResidualMean";
static const wchar_t* cwszSARRCalibStatusFreqResidualStdDev = L"fFreqResidualStdDev";
static const wchar_t* cwszSARRCalibStatusFreqResidualMax = L"fFreqResidualMax";
static const wchar_t* cwszSARRCalibStatusTimeResidualMean = L"fTimeResidualMean";
static const wchar_t* cwszSARRCalibStatusTimeResidualStdDev= L"fTimeResidualStdDev";
static const wchar_t* cwszSARRCalibStatusTimeResidualMax= L"fTimeResidualMax";

// SARR
static const wchar_t* cwszSARRBeaconID = L"u64BeaconID";
static const wchar_t* cwszSARRTimeOffset = L"i64TimeOffset";
static const wchar_t* cwszSARRMsgTime = L"i64TimeMsg";
static const wchar_t* cwszSARRFrequency = L"dFrequency";
static const wchar_t* cwszSARRFrequencyBandwidth = L"fFrequencyBandwidth";
static const wchar_t* cwszSARRFrequencyOffset = L"fFrequencyOffset";
static const wchar_t* cwszSARRCarrierToNoiseRatio = L"fCarrierToNoiseRatio";
static const wchar_t* cwszSARRSignalToNoiseRatio = L"fSignalToNoiseRatio";
static const wchar_t* cwszSARRBitErrorField1 = L"wBitErrorField1";
static const wchar_t* cwszSARRBitErrorField2 = L"wBitErrorField2";
static const wchar_t* cwszSARRBitErrorFrameSynch = L"wBitErrorFrameSynch";
static const wchar_t* cwszSARRBitRate = L"fBitRate";
static const wchar_t* cwszSARRModIndex = L"fModIndex";
static const wchar_t* cwszSARRShortMessIndex = L"fShortMessIndex";
static const wchar_t* cwszSARRFrameSynchMessIndex = L"fFrameSynchMessIndex";
static const wchar_t* cwszSARRFrameSynchBitOffset = L"fFrameSynchBitOffset";
static const wchar_t* cwszSARRRawBitPower = L"fRawBitPower";
static const wchar_t* cwszSARRBeaconMsg = L"cBeaconMsg";

static const wchar_t* cwszSARRFrequency_124 = L"fFrequency";

// Satellite Track (Pass Schedule)
static const wchar_t* cwszSatTrackPassFlags = L"ulPassFlags";
static const wchar_t* cwszSatTrackPassTimeAOS = L"u64PassTimeAOS";
static const wchar_t* cwszSatTrackPassTimeLOS = L"u64PassTimeLOS";
static const wchar_t* cwszSatTrackPassTimePeak = L"u64PassTimePeak";
static const wchar_t* cwszSatTrackPassMaxElevation = L"dPassMaxElevation";
static const wchar_t* cwszSatTrackPassMinElevation = L"dPassMinElevation";
static const wchar_t* cwszSatTrackPassAzimuthAOS = L"dPassAzimuthAOS";
static const wchar_t* cwszSatTrackPassAzimuthLOS = L"dPassAzimuthLOS";
static const wchar_t* cwszSatTrackStartTime = L"u64StartTime";
static const wchar_t* cwszSatTrackEndTime = L"u64EndTime";
static const wchar_t* cwszSatTrackWeight = L"dWeight";

// Sensor (status )
static const wchar_t* cwszSensorDoorStatus = L"wDoorStatus";
static const wchar_t* cwszSensorACUTemp = L"fACUTemp";
static const wchar_t* cwszSensorAUXTemp = L"fAUXTemp";
static const wchar_t* cwszSensorServoTemp = L"fServoTemp";
static const wchar_t* cwszSensorLNCTemp = L"fLNCTemp";
static const wchar_t* cwszSensorRadomeTemp = L"fRadomeTemp";
static const wchar_t* cwszSensorRackTemp = L"fRackTemp";
static const wchar_t* cwszSensorRackAmbientTemp = L"fRackAmbientTemp";
static const wchar_t* cwszSensorRadomeHumidity = L"fRadomeHumidity";
static const wchar_t* cwszSensorACUHumidity = L"fACUHumidity";
static const wchar_t* cwszSensorAGCVoltage = L"fAGCVoltage";
static const wchar_t* cwszSensorWindSpeed = L"wWindSpeed";
static const wchar_t* cwszSensorWindDirection = L"wWindDirection";
static const wchar_t* cwszSensorPowerAlarm = L"wPowerAlarm";
static const wchar_t* cwszSensorSpare = L"wSpare";

// Spectrum
static const wchar_t* cwszSpectrumMaxPower = L"fMaxPower";
static const wchar_t* cwszSpectrumFreqOffset = L"fFreqOffset";
static const wchar_t* cwszSpectrumFreqQFactor = L"fFreqQFactor";
static const wchar_t* cwszSpectrumAGCRMS = L"fAGCRMS";
static const wchar_t* cwszSpectrumAGCMean = L"fAGCMean";
static const wchar_t* cwszSpectrumCarrierFrequency = L"fCarrierFrequency";
static const wchar_t* cwszSpectrumModIndexMean = L"fModIndexMean";
static const wchar_t* cwszSpectrumModIndexMax = L"fModIndexMax";
static const wchar_t* cwszSpectrumModIndexRMS = L"fModIndexRMS";
static const wchar_t* cwszSpectrumMarkerBitRate = L"ulMarkerBitRate";
static const wchar_t* cwszSpectrumModIndexBlock = L"wModIndexBlock";
static const wchar_t* cwszSpectrumAmplitude = L"cAmplitude";

// Status (Summary)
static const wchar_t* cwszStatusSum = L"dwStatus";
static const wchar_t* cwszStatusSummary = L"cSummary";
static const wchar_t* cwszStatusSumAlarmState = L"cAlarmState";
static const wchar_t* cwszStatusSumPowerState = L"cPowerState";
static const wchar_t* cwszStatusSumCollectorState = L"cCollectorState";
static const wchar_t* cwszStatusSumWidebandState = L"cWidebandState";
static const wchar_t* cwszStatusSumCalibrateState = L"cCalibrateState";
static const wchar_t* cwszStatusSumLocateState = L"cLocateState";
static const wchar_t* cwszStatusSumCommsState = L"cCommsState";
static const wchar_t* cwszStatusSumHardwareState = L"cHardwareState";
static const wchar_t* cwszStatusSumAntennaState = L"cAntennaState";
static const wchar_t* cwszStatusSumPassState = L"cPassState";
static const wchar_t* cwszStatusSumEnvironmentState = L"cEnvironmentState";

// Wideband (Stats)
static const wchar_t* cwszWidebandStatus = L"wWidebandStatus";
static const wchar_t* cwszWidebandSarpTotalFrames = L"wSarpTotalFrames";
static const wchar_t* cwszWidebandSarpTotalMessages = L"wSarpTotalMessages";
static const wchar_t* cwszWidebandSarpTotalSyncLosses = L"wSarpTotalSyncLosses";
static const wchar_t* cwszWidebandSarpTotalNoSyncs = L"wSarpTotalNoSyncs";
static const wchar_t* cwszWidebandSarpCurrentSyncLosses = L"wSarpCurrentSyncLosses";
static const wchar_t* cwszWidebandSarpCurrentNoSyncs = L"wSarpCurrentNoSyncs";
static const wchar_t* cwszWidebandSarrTotalMessages = L"wSarrTotalMessages";
static const wchar_t* cwszWidebandCBC121Counts = L"wCBC121Counts";
static const wchar_t* cwszWidebandCBC243Counts = L"wCBC243Counts";
static const wchar_t* cwszWidebandCBC406Counts = L"wCBC406Counts";

// Audio
static const wchar_t* cwszAudioID = L"i64ID";
static const wchar_t* cwszAudioCenterFreq = L"fCenterFreq";
static const wchar_t* cwszAudioBandwidth = L"fBandWidth";
static const wchar_t* cwszAudioBitsPerSample = L"wBitsPerSample";
static const wchar_t* cwszAudioSamplesPerSec = L"ulSamplesPerSec";
static const wchar_t* cwszAudioSamples = L"lChannels";
static const wchar_t* cwszAudioDataBlobSequence = L"ulDataBlobSequence";
static const wchar_t* cwszAudioDataBlobSize = L"ulDataBlobSize";
static const wchar_t* cwszAudioDataBlob = L"cDataBlob";

// Calib406 Version 2
static const wchar_t* cwszCalib4062AntennaID = L"wAntennaID";
static const wchar_t* cwszCalib4062FreqOffset = L"dFreqOffset";
static const wchar_t* cwszCalib4062CarrierPower = L"dCarrierPower";
static const wchar_t* cwszCalib4062BitRate = L"dBitRate";
static const wchar_t* cwszCalib4062DataFlags = L"dwDataFlags";
static const wchar_t* cwszCalib4062ResolutionFlags = L"dwResolutionFlags";
static const wchar_t* cwszCalib4062Reserve0 = L"dwReserve0";
static const wchar_t* cwszCalib4062Reserve1 = L"dReserve1";
static const wchar_t* cwszCalib4062Reserve2 = L"dReserve2";
static const wchar_t* cwszCalib4062Reserve3 = L"dReserve3";


// Calib406 Extended
static const wchar_t* cwszCalib406ExProcessFlags = L"dwProcessFlags";
static const wchar_t* cwszCalib406ExSatVecCoordSystem = L"iSatVecCoordSystem";
static const wchar_t* cwszCalib406ExSatVecTime = L"timeSatVec";
static const wchar_t* cwszCalib406ExSatVecRadiusX = L"dSatVecRadiusX";
static const wchar_t* cwszCalib406ExSatVecRadiusY = L"dSatVecRadiusY";
static const wchar_t* cwszCalib406ExSatVecRadiusZ = L"dSatVecRadiusZ";
static const wchar_t* cwszCalib406ExSatVecVelocityX = L"dSatVecVelocityX";
static const wchar_t* cwszCalib406ExSatVecVelocityY = L"dSatVecVelocityY";
static const wchar_t* cwszCalib406ExSatVecVelocityZ = L"dSatVecVelocityZ";
static const wchar_t* cwszCalib406ExBeaconVecX = L"dBeaconVecX";
static const wchar_t* cwszCalib406ExBeaconVecY = L"dBeaconVecY";
static const wchar_t* cwszCalib406ExBeaconVecZ = L"dBeaconVecZ";
static const wchar_t* cwszCalib406ExTransmitTime = L"timeTransmit";
static const wchar_t* cwszCalib406ExTxFrequency = L"dTxFrequency";
static const wchar_t* cwszCalib406ExTimeResidual = L"dTimeResidual";
static const wchar_t* cwszCalib406ExFreqResidual = L"dFreqResidual";
static const wchar_t* cwszCalib406ExBurstNumber = L"wBurstNumber";

// LUT Status
static const wchar_t* cwszTimeLastSysTestEnd = L"timeLastSysTestEnd";
static const wchar_t* cwszTimeLastLutStart = L"timeLastLutStart";
static const wchar_t* cwszLutState = L"eLutState";
static const wchar_t* cwszLastSatID = L"ulLastSatID";
static const wchar_t* cwszLastPassID = L"ulLastPassID";
static const wchar_t* cwszLastSysTestStatus = L"eLastSysTestStatus";
static const wchar_t* cwszReservedULONG1 = L"ulReserved1";
static const wchar_t* cwszReservedULONG2 = L"ulReserved2";
static const wchar_t* cwszReservedTime1 = L"timeReserved1";
static const wchar_t* cwszReservedTime2 = L"timeReserved2";
static const wchar_t* cwszReservedDouble = L"dReserved";

// Health Status
static const wchar_t* cwszHealthStatusWarningCount = L"wWarningCount";
static const wchar_t* cwszHealthStatusAlarmCount = L"wAlarmCount";
static const wchar_t* cwszHealthStatusDetectRecordCount = L"wDetectRecordCount";
static const wchar_t* cwszHealthStatusReservedWord1 = L"wReserved1";
static const wchar_t* cwszHealthStatusReservedWord2 = L"wReserved2";
static const wchar_t* cwszHealthStatusReservedULONG1 = L"ulReserved1";
static const wchar_t* cwszHealthStatusReservedULONG2 = L"ulReserved2";
static const wchar_t* cwszHealthStatusReservedDouble1 = L"dReserved1";
static const wchar_t* cwszHealthStatusReservedDouble2 = L"dReserved2";
static const wchar_t* cwszHealthStatusReservedTime1 = L"timeReserved1";
static const wchar_t* cwszHealthStatusReservedTime2 = L"timeReserved2";

// Health Detections
static const wchar_t* cwszHealthDetectionsFPID = L"ulFPID";
static const wchar_t* cwszHealthDetectionsSatID = L"ulSatID";
static const wchar_t* cwszHealthDetectionsDetectionCount = L"wDetectionCount";
static const wchar_t* cwszHealthDetectionsReservedWord1 = L"wReserved1";
static const wchar_t* cwszHealthDetectionsReservedULONG1 = L"ulReserved1";

typedef enum eVersions
{
	EMSDBVERSION_UNKNOWN = 0,
	EMSDBVERSION_LEO_124 = 1,
	EMSDBVERSION_LEO_152 = 2,
	EMSDBVERSION_LEO_20 = 3,
	EMSDBVERSION_LEO_26 = 4,
	// Let's use more generic naming
	EMSDBVERSION_6 = 6,
	EMSDBVERSION_FIRST = EMSDBVERSION_UNKNOWN,
	EMSDBVERSION_LAST = EMSDBVERSION_6
} EMSDBVERSION;

// Data Type to Table Name mapping
typedef struct tagEMSDataTypeTableMap
{
	EMSRECORDTYPE eRecType;
	wchar_t* wszTableName;
	EMSDBVERSION version;
} EMSDATATYPETOTABLEMAPPING;

typedef struct tagEMSVersionDescription
{
	EMSDBVERSION version;
	wchar_t* wszDesc;
} EMSVERSIONDESCRIPTION;

static const EMSVERSIONDESCRIPTION s_caVersionDescriptions[] = 
{
	{ EMSDBVERSION_LEO_124, L"1.2.4" },
	{ EMSDBVERSION_LEO_152, L"1.5.2" },
	{ EMSDBVERSION_LEO_20, L"2.0" },
	{ EMSDBVERSION_LEO_26, L"2.6" },
	{ EMSDBVERSION_6, L"6" },
	{ EMSDBVERSION_UNKNOWN, L"" }
};


static const EMSDATATYPETOTABLEMAPPING s_caDataTypeTableMapping[] =	
{	{ EMSRT_ANTENNA, L"ANTENNA_DATA", EMSDBVERSION_LEO_20 },
	{ EMSRT_CALIB406, L"CALIB406_DATA", EMSDBVERSION_LEO_20 },
	{ EMSRT_CALIBCBC, L"CALIBCBC_DATA", EMSDBVERSION_LEO_20 },
	{ EMSRT_CALIBCBC_STATS, L"CALIBCBC_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_CBC, L"CBC_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_COLLECTOR, L"COLLECTOR_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_COMB406, L"COMBINE406_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_COMB406_STATS, L"COMBINE406_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_COMMS_STATS, L"COMMS_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_CONFIG, L"CONFIG_DATA_TXT", EMSDBVERSION_LEO_26},
	{ EMSRT_GEO_CALIB406_STATS, L"GEO_CALIB406_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_GEO_STATS, L"GEO_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_LEO_CALIB406_STATS, L"LEO_CALIB406_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_LOCATE, L"LOCATE_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_LOCATE_STATS, L"LOCATE_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_LOG, L"LOG_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_ORBIT, L"ORBIT_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_ORBIT_STATS, L"ORBIT_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_PASS_STATS, L"PASS_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_RESIDUAL, L"RESIDUAL_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SARP_CALIB, L"SARP_CALIB_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SARP_CALIB_STATS, L"SARP_CALIB_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_SARP, L"SARP_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SARR_CALIB, L"SARR_CALIB_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SARR_CALIB_STATS, L"SARR_CALIB_STATS", EMSDBVERSION_LEO_20},
	{ EMSRT_SARR, L"SARR_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SAT_TRACK, L"SAT_TRACK_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SENSOR, L"SENSOR_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_SPECTRUM, L"SPECTRUM_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_STAT_SUMMARY, L"STATUS_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_WIDEBAND_STATS, L"WIDEBAND_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_AUDIO, L"AUDIO_RIFF_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_CALIB406_EXT, L"CALIB406EX_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_CALIB406_2, L"CALIB406_2_DATA", EMSDBVERSION_LEO_20},
	{ EMSRT_ABL_DATA, L"ABL_DATA", EMSDBVERSION_LEO_20},

	{ EMSRT_ANTENNA, L"ANTENNA_DATA", EMSDBVERSION_LEO_124 },
	{ EMSRT_CALIB406, L"CALIB406_DATA", EMSDBVERSION_LEO_124 },
	{ EMSRT_CALIBCBC, L"CALIBCBC_DATA", EMSDBVERSION_LEO_124 },
	{ EMSRT_CALIBCBC_STATS, L"CALIBCBC_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_CBC, L"CBC_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_COLLECTOR, L"COLLECTOR_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_COMB406, L"COMBINE406_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_COMB406_STATS, L"COMBINE406_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_COMMS_STATS, L"COMMS_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_CONFIG, L"CONFIG_DATA_TXT", EMSDBVERSION_LEO_26},
	{ EMSRT_GEO_CALIB406_STATS, L"GEO_CALIB406_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_GEO_STATS, L"GEO_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_LEO_CALIB406_STATS, L"LEO_CALIB406_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_LOCATE_STATS, L"LOCATE_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_LOG, L"LOG_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_ORBIT, L"ORBIT_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_ORBIT_STATS, L"ORBIT_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_PASS_STATS, L"PASS_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_RESIDUAL, L"RESIDUAL_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SARP, L"SARP_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SARR_CALIB, L"SARR_CALIB_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SARR_CALIB_STATS, L"SARR_CALIB_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_SAT_TRACK, L"SAT_TRACK_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SENSOR, L"SENSOR_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SPECTRUM, L"SPECTRUM_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_STAT_SUMMARY, L"STATUS_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_WIDEBAND_STATS, L"WIDEBAND_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SARP_CALIB_124, L"SARP_CALIB_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_SARP_CALIB_STATS_124, L"SARP_CALIB_STATS", EMSDBVERSION_LEO_124},
	{ EMSRT_SARR_124, L"SARR_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_LOCATE_124, L"LOCATE_DATA", EMSDBVERSION_LEO_124},
	{ EMSRT_LUT_STATUS, L"LUT_STATE", EMSDBVERSION_LEO_26},
	// The following were introduced for version 6 of the LUT600 databse
	{ EMSRT_HEALTH_STATUS, L"HEALTH_STATUS", EMSDBVERSION_6},
	{ EMSRT_HEALTH_DETECTIONS, L"HEALTH_DETECTIONS", EMSDBVERSION_6},
	{ EMSRT_BEACON_ADVISORY, L"EMS_BEACON_ADVISORY", EMSDBVERSION_6},
	// the new status table that is used by the LP.
	{ EMSRT_LP_STATUS, L"STATUS", EMSDBVERSION_6},
	// Don't include the MANOEUVRE data type since there is no table yet
	{ EMSRT_UNKNOWN, L""},
};


#endif


