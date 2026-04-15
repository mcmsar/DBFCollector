
#ifndef __PROCESS_CONFIG_CONSTANTS_H__
#define __PROCESS_CONFIG_CONSTANTS_H__

// Group Name(s)
static const wchar_t* cwszProcessGroup  = L"PRO";

// Key(s)
static const wchar_t* cwszDataDirectorySend = L"Data.Directory.Send";
static const wchar_t* cwszDataDirectoryUndelivered = L"Data.Directory.Undelivered";
static const wchar_t* cwszDataDirectoryBinary = L"Data.Directory.Binary";
static const wchar_t* cwszSerializedMode = L"SerializedMode";
static const wchar_t* cwszCommandTimeout = L"CommandTimeout";
static const wchar_t* cwszSitPassThrough = L"PassThroughGateway";
static const wchar_t* cwszLutID = L"LutID";
static const wchar_t* cwszSOAPServerBacklogSize = L"SOAPServer.MaxQueueSize";
static const wchar_t* cwszSOAPServerPort = L"SOAPServer.Port";
static const wchar_t* cwszSOAPServerHandlerThreads = L"SOAPServer.HandlerThreads";
static const wchar_t* cwszDataDirectoryProcessing = L"Data.Directory.Processing";
static const wchar_t* cwszDataDirectoryProcessedBinary = L"Data.Directory.ProcessedBinary";
static const wchar_t* cwszCombine406MaxGEOSarrRecords = L"Combine406.MaxGEOSarrRecords";

#endif // __PROCESS_CONFIG_CONSTANTS_H__