
#ifndef __ROUTE_CONFIG_CONSTANTS_H__
#define __ROUTE_CONFIG_CONSTANTS_H__

#include <windows.h>  // for TEXT() macro

// Group Name(s)
static const wchar_t* cwszRouteGroup  = L"RTE";

static const wchar_t* cwszRouteEnabled = L"Enabled";

// Key(s)
static const wchar_t* cwszEnd1Identifier = L"End1.Identifier";
static const wchar_t* cwszEnd2Identifier = L"End2.Identifier";
static const wchar_t* cwszEnd1Alias = L"End1.Alias";
static const wchar_t* cwszEnd2Alias = L"End2.Alias";
static const wchar_t* cwszEnd1OutMsgNumber = L"End1.Out.MsgNumber";
static const wchar_t* cwszEnd2OutMsgNumber = L"End2.Out.MsgNumber";
static const wchar_t* cwszEnd1InMsgNumber = L"End1.In.MsgNumber";
static const wchar_t* cwszEnd2InMsgNumber = L"End2.In.MsgNumber";
static const wchar_t* cwszEnd1OutBinMsgNumber = L"End1.Out.BinMsgNumber";
static const wchar_t* cwszEnd2OutBinMsgNumber = L"End2.Out.BinMsgNumber";
static const wchar_t* cwszEnd1InBinMsgNumber = L"End1.In.BinMsgNumber";
static const wchar_t* cwszEnd2InBinMsgNumber = L"End2.In.BinMsgNumber";

static const wchar_t* cwszEnd1OutMF3Format					       = L"End1.Out.MF3";
static const wchar_t* cwszEnd2OutMF3Format					       = L"End2.Out.MF3";

static const wchar_t* cwszHiResMF3Format					     		 = L"hhmmss";
static const wchar_t* cwszNormalMF3Format					       = L"hhmm";

static const wchar_t* cwszEnd1OutCalcNextVis 				       = L"End1.Out.CalcNextVis";
static const wchar_t* cwszEnd2OutCalcNextVis 				       = L"End2.Out.CalcNextVis";
static const wchar_t* cwszEnd1OutMCCSuppressEnabled         = L"End1.Out.MCCSuppress.Enabled";
static const wchar_t* cwszEnd1OutMCCSuppressRefBeacons         = L"End1.Out.MCCSuppress.RefBeacons";
static const wchar_t* cwszEnd1OutMCCSuppressOrbBeacons         = L"End1.Out.MCCSuppress.OrbBeacons";
static const wchar_t* cwszEnd1OutMCCSuppressTestBeacons        = L"End1.Out.MCCSuppress.TestBeacons";
static const wchar_t* cwszEnd1OutMCCSuppress406Beacons         = L"End1.Out.MCCSuppress.406Beacons";
static const wchar_t* cwszEnd1OutMCCSuppressInvalidFixedBits   = L"End1.Out.MCCSuppress.InvalidFixedBits";
static const wchar_t* cwszEnd1OutMCCSuppressInvertedFrameSync  = L"End1.Out.MCCSuppress.InvertedFrameSync";
static const wchar_t* cwszEnd1OutSuppressInvalidUnlocated1     = L"End1.Out.Suppress.InvalidUnlocated1";
static const wchar_t* cwszEnd1OutSuppressInvalidUnlocated2     = L"End1.Out.Suppress.InvalidUnlocated2";
static const wchar_t* cwszEnd1OutSuppressInvalidBeacons     = L"End1.Out.MCCSuppress.InvalidBeacons";
static const wchar_t* cwszEnd2OutMCCSuppressEnabled         = L"End2.Out.MCCSuppress.Enabled";
static const wchar_t* cwszEnd2OutMCCSuppressRefBeacons         = L"End2.Out.MCCSuppress.RefBeacons";
static const wchar_t* cwszEnd2OutMCCSuppressOrbBeacons         = L"End2.Out.MCCSuppress.OrbBeacons";
static const wchar_t* cwszEnd2OutMCCSuppressTestBeacons        = L"End2.Out.MCCSuppress.TestBeacons";
static const wchar_t* cwszEnd2OutMCCSuppress406Beacons         = L"End2.Out.MCCSuppress.406Beacons";
static const wchar_t* cwszEnd2OutMCCSuppressInvalidFixedBits   = L"End2.Out.MCCSuppress.InvalidFixedBits";
static const wchar_t* cwszEnd2OutMCCSuppressInvertedFrameSync  = L"End2.Out.MCCSuppress.InvertedFrameSync";
static const wchar_t* cwszEnd2OutSuppressInvalidUnlocated1     = L"End2.Out.Suppress.InvalidUnlocated1";
static const wchar_t* cwszEnd2OutSuppressInvalidUnlocated2     = L"End2.Out.Suppress.InvalidUnlocated2";
static const wchar_t* cwszEnd2OutSuppressInvalidBeacons     = L"End2.Out.MCCSuppress.InvalidBeacons";

static const wchar_t* cwszEnd1OutAllowReserved				= L"End1.Out.Allow.Reserved";
static const wchar_t* cwszEnd2OutAllowReserved				= L"End2.Out.Allow.Reserved";
static const wchar_t* cwszEnd1OutSuppressNormal				= L"End1.Out.Suppress.Normal";
static const wchar_t* cwszEnd2OutSuppressNormal				= L"End2.Out.Suppress.Normal";
static const wchar_t* cwszEnd1OutCC							= L"End1.Out.CC";
static const wchar_t* cwszEnd2OutCC							= L"End2.Out.CC";

static const wchar_t* cwszEnd1OutRetries     = L"End1.Out.Retries";
static const wchar_t* cwszEnd2OutRetries     = L"End2.Out.Retries";
static const wchar_t* cwszEnd1 = L"End1.";
static const wchar_t* cwszEnd2 = L"End2.";
static const wchar_t* cwszIdentifier = L"Identifier";
static const wchar_t* cwszAlias = L"Alias";
static const wchar_t* cwszInSITSSID = L"In.SITS.SID";
static const wchar_t* cwszInSITSInternal = L"In.SITS.Internal";
static const wchar_t* cwszInFormat = L"In.Format";
static const wchar_t* cwszInTranslationTable = L"In.Translation.TableName";
static const wchar_t* cwszInBinaryDataAntennaEnabled = L"In.BinaryData.Antenna.Enabled";
static const wchar_t* cwszInBinaryDataCalib406Enabled = L"In.BinaryData.Calib406.Enabled";
static const wchar_t* cwszInBinaryDataCalibCBCEnabled = L"In.BinaryData.CalibCBC.Enabled";
static const wchar_t* cwszInBinaryDataCalibCBCStatsEnabled = L"In.BinaryData.CalibCBCStats.Enabled";
static const wchar_t* cwszInBinaryDataCBCEnabled = L"In.BinaryData.CBC.Enabled";
static const wchar_t* cwszInBinaryDataCollectorEnabled = L"In.BinaryData.Collector.Enabled";
static const wchar_t* cwszInBinaryDataCombine406Enabled = L"In.BinaryData.Combine406.Enabled";
static const wchar_t* cwszInBinaryDataCombine406StatsEnabled = L"In.BinaryData.Combine406Stats.Enabled";
static const wchar_t* cwszInBinaryDataCommsStatsEnabled = L"In.BinaryData.CommsStats.Enabled";
static const wchar_t* cwszInBinaryDataConfigEnabled = L"In.BinaryData.Config.Enabled";
static const wchar_t* cwszInBinaryDataGEOCalib406StatsEnabled = L"In.BinaryData.GEOCalib406Stats.Enabled";
static const wchar_t* cwszInBinaryDataGEOStatsEnabled = L"In.BinaryData.GEOStats.Enabled";
static const wchar_t* cwszInBinaryDataLEOCalib406StatsEnabled = L"In.BinaryData.LEOCalib406Stats.Enabled";
static const wchar_t* cwszInBinaryDataLocateEnabled = L"In.BinaryData.Locate.Enabled";
static const wchar_t* cwszInBinaryDataLocateStatsEnabled = L"In.BinaryData.LocateStats.Enabled";
static const wchar_t* cwszInBinaryDataLogEnabled = L"In.BinaryData.Log.Enabled";
static const wchar_t* cwszInBinaryDataOrbitEnabled = L"In.BinaryData.Orbit.Enabled";
static const wchar_t* cwszInBinaryDataOrbitStatsEnabled = L"In.BinaryData.OrbitStats.Enabled";
static const wchar_t* cwszInBinaryDataPassStatsEnabled = L"In.BinaryData.PassStats.Enabled";
static const wchar_t* cwszInBinaryDataResidualEnabled = L"In.BinaryData.Residual.Enabled";
static const wchar_t* cwszInBinaryDataSARPCalibEnabled = L"In.BinaryData.SARPCalib.Enabled";
static const wchar_t* cwszInBinaryDataSARPCalibStatsEnabled = L"In.BinaryData.SARPCalibStats.Enabled";
static const wchar_t* cwszInBinaryDataSARPEnabled = L"In.BinaryData.SARP.Enabled";
static const wchar_t* cwszInBinaryDataSARRCalibEnabled = L"In.BinaryData.SARRCalib.Enabled";
static const wchar_t* cwszInBinaryDataSARRCalibStatsEnabled = L"In.BinaryData.SARRCalibStats.Enabled";
static const wchar_t* cwszInBinaryDataSARREnabled = L"In.BinaryData.SARR.Enabled";
static const wchar_t* cwszInBinaryDataSatTrackEnabled = L"In.BinaryData.SatTrack.Enabled";
static const wchar_t* cwszInBinaryDataSatSensorEnabled = L"In.BinaryData.SatSensor.Enabled";
static const wchar_t* cwszInBinaryDataSpectrumEnabled = L"In.BinaryData.Spectrum.Enabled";
static const wchar_t* cwszInBinaryDataStatusEnabled = L"In.BinaryData.Status.Enabled";
static const wchar_t* cwszInBinaryDataWidebandEnabled = L"In.BinaryData.Wideband.Enabled";
static const wchar_t* cwszInBinaryDataAudioEnabled = L"In.BinaryData.Audio.Enabled";
static const wchar_t* cwszInBinaryDataManoeuvreEnabled = L"In.BinaryData.Manoeuvre.Enabled";
static const wchar_t* cwszInBinaryDataSARRExtEnabled = L"In.BinaryData.SARRExt.Enabled";
static const wchar_t* cwszInBinaryDataCalib4062Enabled = L"In.BinaryData.Calib4062.Enabled";
static const wchar_t* cwszOutTranslationTable = L"Out.Translation.TableName";
static const wchar_t* cwszOutSITsSID = L"Out.SITs.SID";
static const wchar_t* cwszOutSITsInternal = L"Out.SITs.Internal";
static const wchar_t* cwszOutAutoSITsInternal   = L"Out.AutoSITs.Internal";
static const wchar_t* cwszOutAutoSITsSID        = L"Out.AutoSITs.SID";
static const wchar_t* cwszOutResourceSendLocationMsgType = L"Out.Resource.SendLocation.MsgType";
static const wchar_t* cwszOutResourceSendAlarmMsgType = L"Out.Resource.SendAlarm.MsgType";
static const wchar_t* cwszOutResourceSendWarningMsgType = L"Out.Resource.SendWarning.MsgType";
static const wchar_t* cwszOutResourceSendStatusMsgType = L"Out.Resource.SendStatus.MsgType";
static const wchar_t* cwszOutResourceSendOrbitVectorMsgType = L"Out.Resource.SendOrbitVector.MsgType";
static const wchar_t* cwszOutResourceSendTLEMsgType = L"Out.Resource.SendTLE.MsgType";
static const wchar_t* cwszOutResourceSendPassScheduleMsgType = L"Out.Resource.SendPassSchedule.MsgType";
static const wchar_t* cwszOutResourceSendMetopScheduleMsgType = L"Out.Resource.SendMetopSchedule.MsgType";
static const wchar_t* cwszOutResourceSendSARPCalibMsgType = L"Out.Resource.SendSARPCalib.MsgType";
static const wchar_t* cwszOutResourceSendSARRCalibMsgType = L"Out.Resource.SendSARRCalib.MsgType";
static const wchar_t* cwszOutResourceSendStartupMsgType = L"Out.Resource.SendStartup.MsgType";
static const wchar_t* cwszOutResourceSendLEOPassSummaryMsgType = L"Out.Resource.SendLEOPassSummary.MsgType";
static const wchar_t* cwszOutResourceSendGEOPassSummaryMsgType = L"Out.Resource.SendGEOPassSummary.MsgType";
static const wchar_t* cwszOutResourceSendCommandAcknowledgementMsgType = L"Out.Resource.SendCommandAcknowledgement.MsgType";
static const wchar_t* cwszOutResourceSendCommsCheckMsgType = L"Out.Resource.SendCommsCheck.MsgType";
static const wchar_t* cwszOutResourceSendCommandMsgType = L"Out.Resource.SendCommand.MsgType";
static const wchar_t* cwszOutResourceRetransmitMsgsMsgType = L"Out.Resource.RetransmitMsgs.MsgType";
static const wchar_t* cwszOutResourceSendMsgsMsgType = L"Out.Resource.SendMsgs.MsgType";
static const wchar_t* cwszOutResourceGetDataMsgType = L"Out.Resource.GetData.MsgType";
static const wchar_t* cwszOutResourceInitManProcMsgType = L"Out.Resource.InitManProc.MsgType";
static const wchar_t* cwszOutResourceRemoveDataMsgType = L"Out.Resource.RemoveData.MsgType";
static const wchar_t* cwszOutResourceUploadDataMsgType = L"Out.Resource.UploadData.MsgType";
static const wchar_t* cwszOutResourceProcess406MsgType = L"Out.Resource.Process406.MsgType";
static const wchar_t* cwszOutResourceCancelSessionMsgType = L"Out.Resource.CancelSession.MsgType";
static const wchar_t* cwszOutResourceGenerateAlertsMsgsType = L"Out.Resource.GenerateAlerts.MsgType";
static const wchar_t* cwszOutResourceSendDataMsgType = L"Out.Resource.SendData.MsgType";
static const wchar_t* cwszOutResourceRecoverDataMsgType = L"Out.Resource.RecoverData.MsgType";
static const wchar_t* cwszOutResourceGetControlFilenamesMsgType = L"Out.Resource.GetControlFilenames.MsgType";
static const wchar_t* cwszOutResourceSendDataReportMsgType = L"Out.Resource.SendDataReport.MsgType";
static const wchar_t* cwszOutResourceConfigGetMsgType = L"Out.Resource.ConfigGet.MsgType";
static const wchar_t* cwszOutResourceConfigSetStringMsgType = L"Out.Resource.ConfigSetString.MsgType";
static const wchar_t* cwszOutResourceAlertSendSolutionsMsgType = L"Out.Resource.AlertSendSolutions.MsgType";
static const wchar_t* cwszOutResourceAlertTransmitMsgType = L"Out.Resource.AlertTransmit.MsgType";
static const wchar_t* cwszOutResourceTransmitMsgType = L"Out.Resource.SITTransmit.MsgType";
static const wchar_t* cwszOutResourceAudioRequestMsgType = L"Out.Resource.AudioMakeFreeRequest.MsgType";
static const wchar_t* cwszOutResourceAudioReqGetDataMsgType = L"Out.Resource.AudioGetFreeRequestData.MsgType";
static const wchar_t* cwszOutResourceAudioReqCancelMsgType = L"Out.Resource.AudioCancelFreeRequest.MsgType";
static const wchar_t* cwszOutResourceAudioRealConnectMsgType = L"Out.Resource.AudioConnectRealTime.MsgType";
static const wchar_t* cwszOutResourceAudioRealGetMsgType = L"Out.Resource.AudioGetDataRealTime.MsgType";
static const wchar_t* cwszOutResourceAudioRealSetParamMsgType = L"Out.Resource.AudioSetParametersRealTime.MsgType";
static const wchar_t* cwszOutResourceAudioRealDisconnectMsgType = L"Out.Resource.AudioDisconnectRealTime.MsgType";

static const wchar_t* cwszOutFormat = L"Out.Format";
static const wchar_t* cwszOutMaxSatellites = L"Out.MaxSatellites";
static const wchar_t* cwszOutBinaryDataAntennaEnabled = L"Out.BinaryData.Antenna.Enabled";
static const wchar_t* cwszOutBinaryDataCalib406Enabled = L"Out.BinaryData.Calib406.Enabled";
static const wchar_t* cwszOutBinaryDataCalibCBCEnabled = L"Out.BinaryData.CalibCBC.Enabled";
static const wchar_t* cwszOutBinaryDataCalibCBCStatsEnabled = L"Out.BinaryData.CalibCBCStats.Enabled";
static const wchar_t* cwszOutBinaryDataCBCEnabled = L"Out.BinaryData.CBC.Enabled";
static const wchar_t* cwszOutBinaryDataCollectorEnabled = L"Out.BinaryData.Collector.Enabled";
static const wchar_t* cwszOutBinaryDataCombine406Enabled = L"Out.BinaryData.Combine406.Enabled";
static const wchar_t* cwszOutBinaryDataCombine406StatsEnabled = L"Out.BinaryData.Combine406Stats.Enabled";
static const wchar_t* cwszOutBinaryDataCommsStatsEnabled = L"Out.BinaryData.CommsStats.Enabled";
static const wchar_t* cwszOutBinaryDataConfigEnabled = L"Out.BinaryData.Config.Enabled";
static const wchar_t* cwszOutBinaryDataGEOCalib406StatsEnabled = L"Out.BinaryData.GEOCalib406Stats.Enabled";
static const wchar_t* cwszOutBinaryDataGEOStatsEnabled = L"Out.BinaryData.GEOStats.Enabled";
static const wchar_t* cwszOutBinaryDataLEOCalib406StatsEnabled = L"Out.BinaryData.LEOCalib406Stats.Enabled";
static const wchar_t* cwszOutBinaryDataLocateEnabled = L"Out.BinaryData.Locate.Enabled";
static const wchar_t* cwszOutBinaryDataLocateStatsEnabled = L"Out.BinaryData.LocateStats.Enabled";
static const wchar_t* cwszOutBinaryDataLogEnabled = L"Out.BinaryData.Log.Enabled";
static const wchar_t* cwszOutBinaryDataOrbitEnabled = L"Out.BinaryData.Orbit.Enabled";
static const wchar_t* cwszOutBinaryDataOrbitStatsEnabled = L"Out.BinaryData.OrbitStats.Enabled";
static const wchar_t* cwszOutBinaryDataPassStatsEnabled = L"Out.BinaryData.PassStats.Enabled";
static const wchar_t* cwszOutBinaryDataResidualEnabled = L"Out.BinaryData.Residual.Enabled";
static const wchar_t* cwszOutBinaryDataSARPCalibEnabled = L"Out.BinaryData.SARPCalib.Enabled";
static const wchar_t* cwszOutBinaryDataSARPCalibStatsEnabled = L"Out.BinaryData.SARPCalibStats.Enabled";
static const wchar_t* cwszOutBinaryDataSARPEnabled = L"Out.BinaryData.SARP.Enabled";
static const wchar_t* cwszOutBinaryDataSARRCalibEnabled = L"Out.BinaryData.SARRCalib.Enabled";
static const wchar_t* cwszOutBinaryDataSARRCalibStatsEnabled = L"Out.BinaryData.SARRCalibStats.Enabled";
static const wchar_t* cwszOutBinaryDataSARREnabled = L"Out.BinaryData.SARR.Enabled";
static const wchar_t* cwszOutBinaryDataSatTrackEnabled = L"Out.BinaryData.SatTrack.Enabled";
static const wchar_t* cwszOutBinaryDataSatSensorEnabled = L"Out.BinaryData.SatSensor.Enabled";
static const wchar_t* cwszOutBinaryDataSpectrumEnabled = L"Out.BinaryData.Spectrum.Enabled";
static const wchar_t* cwszOutBinaryDataStatusEnabled = L"Out.BinaryData.Status.Enabled";
static const wchar_t* cwszOutBinaryDataWidebandEnabled = L"Out.BinaryData.Wideband.Enabled<";
static const wchar_t* cwszOutBinaryDataAudioEnabled = L"Out.BinaryData.Audio.Enabled";
static const wchar_t* cwszOutBinaryDataManoeuvreEnabled = L"Out.BinaryData.Manoeuvre.Enabled";
static const wchar_t* cwszOutCommsType = L"Out.Comms.Type"; // for legacy (ie. pre-lut server) callers of IEMSSiteInfo methods
static const wchar_t* cwszEnd1OutCommsTimeout = L"End1.Out.Comms.Timeout";
static const wchar_t* cwszEnd2OutCommsTimeout = L"End2.Out.Comms.Timeout";
static const wchar_t* cwszOutCommsDirectDirectory = L"Out.Comms.Direct.Directory";
static const wchar_t* cwszOutCommsFTPHost = L"Out.Comms.FTP.Host";
static const wchar_t* cwszOutCommsFTPPort = L"Out.Comms.FTP.Port";
static const wchar_t* cwszOutCommsFTPLogin = L"Out.Comms.FTP.Login";
static const wchar_t* cwszOutCommsFTPPassword = L"Out.Comms.FTP.Password";
static const wchar_t* cwszOutCommsFTPDirectory = L"Out.Comms.FTP.Directory";
static const wchar_t* cwszOutCommsSOAPEndpoint = L"Out.Comms.SOAP.Endpoint";
static const wchar_t* cwszOutCommsTimeout = L"Out.Comms.Timeout";
static const wchar_t* cwszOutCommsCompress = L"Out.Comms.Compress";

static const wchar_t* cwszOutCommsAltType = L"Out.CommsAlternate.Type"; // for legacy (ie. pre-lut server) callers of IEMSSiteInfo methods
static const wchar_t* cwszEnd1OutCommsAltTimeout = L"End1.Out.CommsAlternate.Timeout";
static const wchar_t* cwszEnd2OutCommsAltTimeout = L"End2.Out.CommsAlternate.Timeout";
static const wchar_t* cwszOutCommsAltDirectDirectory = L"Out.CommsAlternate.Direct.Directory";
static const wchar_t* cwszOutCommsAltFTPHost = L"Out.CommsAlternate.FTP.Host";
static const wchar_t* cwszOutCommsAltFTPPort = L"Out.CommsAlternate.FTP.Port";
static const wchar_t* cwszOutCommsAltFTPLogin = L"Out.CommsAlternate.FTP.Login";
static const wchar_t* cwszOutCommsAltFTPPassword = L"Out.CommsAlternate.FTP.Password";
static const wchar_t* cwszOutCommsAltFTPDirectory = L"Out.CommsAlternate.FTP.Directory";
static const wchar_t* cwszOutCommsAltSOAPEndpoint = L"Out.CommsAlternate.SOAP.Endpoint";
static const wchar_t* cwszOutCommsAltTimeout = L"Out.CommsAlternate.Timeout";
static const wchar_t* cwszOutCommsAltCompress = L"Out.CommsAlternate.Compress";


static const wchar_t* cwszOutCommsAltConnectionAlt = L"Out.CommsAlternate.AlternateConnections";
static const wchar_t* cwszOutCommsConnectionAlt = L"Out.Comms.AlternateConnections";

static const wchar_t* cwszOutAlternateDuration = L"Out.AlternateDuration";

static const wchar_t* cwszOutUseSecurityToken = L"Out.UseSecurityToken";
static const wchar_t* cwszOutMultiSitMaxAlertsPerMessage = L"Out.MultiSit.MaxAlertsPerMessage";

static const wchar_t* cwszOutReportSourceChannel = L"Out.ReportSourceChannel";
static const wchar_t* cwszOutAlertChannels = L"Out.AlertChannels";

static const wchar_t* cwszOutUndeliverableAge = L"Out.UndeliverableAge";

// Value(s)
static const wchar_t* cwszSit = L"sit";
static const wchar_t* cwszMultiSit = L"multisit";
static const wchar_t* cwszSOAP = L"SOAP";
static const wchar_t* cwszBinary = L"BINARY";
static const wchar_t* cwszSIT = L"SIT";
static const wchar_t* cwszUDP = L"UDP";

static const wchar_t* cwszCommsTypeFTP    = L"FTP";
static const wchar_t* cwszCommsTypeDirect = L"Direct";
static const wchar_t* cwszCommsTypeTCPIP  = L"TCP/IP";

// ================================================================
// Message sequence number and message filenames:

// Binary files:
static const long    clBinMsgNumWidth           = 7;
static const TCHAR   c_szDestBinFileFmt[]       = TEXT("%s_%s_%07d.bin");
static const wchar_t cwszDestBinFileFmt[]       = L"%s_%s_%07d.bin";
static const long    clMaxBinMsgSequenceNumber  = 9999999;
static const long    clMinBinMsgSequenceNumber  = 1;

// Text (SIT) files:
static const long    clTxtMsgNumWidth           = 5;
static const TCHAR   c_szDestTxtFileFmt[]       = TEXT("%s_%s_%05d.txt");
static const wchar_t cwszDestTxtFileFmt[]       = L"%s_%s_%05d.txt";
static const wchar_t cwszTmpTxtFileFmt[]        = L"%s_%s_%05d.tmp";
static const long    clMaxMsgSequenceNumber     = 99999;
static const long    clMinMsgSequenceNumber     = 1;

// XML files:
static const wchar_t cwszDestXmlFileFmt[]			= L"%s_%s_%05d.xml";

// CSV files:
static const wchar_t cwszDestCsvFileFmt[]			= L"%s_%s_%05d.csv";;

// Character Mapping files
// The first parameter is the SIT DataDirectory (i.e. the path)
// The second parameters is the short name for the destination
static const TCHAR	c_szCharMapTxtFileFmt[]		= TEXT("%s\\CharMappings\\EMSCharMap_%s.txt");
// ================================================================

#endif	// __ROUTE_CONFIG_CONSTANTS_H__

