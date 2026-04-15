#ifndef __SIT_RES_TRANS_TABLE_CONSTANTS_H__
#define __SIT_RES_TRANS_TABLE_CONSTANTS_H__

// Group Name(s)
static const wchar_t* cwszRTTGroup  = L"RTT";

// Key(s)
static const wchar_t* cwszSIT115 = L"SIT.115";
static const wchar_t* cwszSIT115A = L"SIT.115A";
static const wchar_t* cwszSIT115B = L"SIT.115B";
static const wchar_t* cwszSIT115C = L"SIT.115C";
static const wchar_t* cwszSIT121 = L"SIT.121";
static const wchar_t* cwszSIT121A = L"SIT.121A";
static const wchar_t* cwszSIT121B = L"SIT.121B";
static const wchar_t* cwszSIT122 = L"SIT.122";
static const wchar_t* cwszSIT122A = L"SIT.122A";
static const wchar_t* cwszSIT122B = L"SIT.122B";
static const wchar_t* cwszSIT122C = L"SIT.122C";
static const wchar_t* cwszSIT122E = L"SIT.122E";
static const wchar_t* cwszSIT125 = L"SIT.125";
static const wchar_t* cwszSIT125A = L"SIT.125A";
static const wchar_t* cwszSIT125B = L"SIT.125B";
static const wchar_t* cwszSIT215 = L"SIT.215";
static const wchar_t* cwszSIT215A = L"SIT.215A";
static const wchar_t* cwszSIT215B = L"SIT.215B";
static const wchar_t* cwszSIT255A = L"SIT.255A";
static const wchar_t* cwszSIT260A = L"SIT.260A";
static const wchar_t* cwszSIT270A = L"SIT.270A";
static const wchar_t* cwszSIT415 = L"SIT.415";
static const wchar_t* cwszSIT415A = L"SIT.415A";
static const wchar_t* cwszSIT417 = L"SIT.417";
static const wchar_t* cwszSIT417A = L"SIT.417A";
static const wchar_t* cwszSIT417B = L"SIT.417B";
static const wchar_t* cwszSIT510 = L"SIT.510";
static const wchar_t* cwszSIT510A = L"SIT.510A";
static const wchar_t* cwszSIT605A = L"SIT.605A";
static const wchar_t* cwszSIT605B = L"SIT.605B";
static const wchar_t* cwszSIT605C = L"SIT.605C";
static const wchar_t* cwszSIT605D = L"SIT.605D";
static const wchar_t* cwszSIT661A = L"SIT.661A";
static const wchar_t* cwszSIT661B = L"SIT.661B";
static const wchar_t* cwszSIT662A = L"SIT.662A";
static const wchar_t* cwszSIT750A = L"SIT.750A";
static const wchar_t* cwszSIT751A = L"SIT.751A";
static const wchar_t* cwszSIT760A = L"SIT.760A";
static const wchar_t* cwszSIT770A = L"SIT.770A";
static const wchar_t* cwszSIT915 = L"SIT.915";
static const wchar_t* cwszSIT925 = L"SIT.925";
static const wchar_t* cwszSIT950A = L"SIT.950A";
static const wchar_t* cwszSIT951A = L"SIT.951A";

// Value(s)
typedef struct tagResourceNameMapping
{
	wchar_t* wszName;
	EMSRESOURCEIDENTIFIER resID;
} EMSRESNAMEMAPPING;

static EMSRESNAMEMAPPING caResourceMap[] = {	{ L"SendLocation", EMSRES_SEND_LOCATION },
										{ L"SendAlarm", EMSRES_SEND_ALARM },
										{ L"SendWarning", EMSRES_SEND_WARNING },
										{ L"SendStatus", EMSRES_SEND_STATUS },
										{ L"SendOrbitVector", EMSRES_SEND_ORBV },
										{ L"SendTLE", EMSRES_SEND_TLE },
										{ L"SendPassSchedule", EMSRES_SEND_PASS_SCHED },
										{ L"SendMetopSchedule", EMSRES_SEND_METOP_SCHED },
										{ L"SendSARPCalib", EMSRES_SEND_SARP_CALIB },
										{ L"SendSARRCalib", EMSRES_SEND_SARR_CALIB },
										{ L"SendStartup", EMSRES_SEND_STARTUP },
										{ L"SendLEOPassSummary", EMSRES_SEND_LEO_PASS_SUMMARY },
										{ L"SendGEOPassSummary", EMSRES_SEND_GEO_PASS_SUMMARY },
										{ L"SendCommandAcknowledgement", EMSRES_SEND_CMD_ACK },
										{ L"SendCommsCheck", EMSRES_SEND_COMMS_CHECK },
										{ L"SendCommand", EMSRES_SEND_CMD },
										{ L"RetransmitMsgs", EMSRES_RETRANSMIT_MSGS },
										{ L"SendMsgs", EMSRES_SEND_MSGS },
										{ L"GetData", EMSRES_GET_DATA },
										{ L"InitManualProcessing", EMSRES_INIT_MAN_PROC },
										{ L"RemoveData", EMSRES_REMOVE_DATA },
										{ L"UploadData", EMSRES_UPLOAD_DATA },
										{ L"Process406", EMSRES_PROCESS_406 },
										{ L"CancelSession", EMSRES_CANCEL_SESSION },
										{ L"GenerateAlerts", EMSRES_GEN_ALERTS },
										{ L"SendData", EMSRES_SEND_DATA },
										{ L"RecoverData", EMSRES_RECOVER_DATA },
										{ 0, EMSRES_LAST }
									};


#endif // __SIT_TRANS_TABLE_CONSTANTS_H__
