#ifndef __COMMAND_FORMATS_H__
#define __COMMAND_FORMATS_H__

#include <dal.h>
#include "configmanagertypes.h"

static const unsigned long culWaitTimeout = 5000;	// Event wait timeout (milliseconds)

const long MAX_LUTS_FOR_MANUAL_RECOVERY = 8;
const long MAX_DATATYPES_FOR_MANUAL_RECOVER = 8;
const TCHAR LUT_SEPARATOR[] = TEXT(":");
const TCHAR DATATYPE_SEPARATOR[] = TEXT(":");
static const TCHAR* cszRecoverDataCmdFmt = TEXT("Rec luts=%s, data=%s, start=%I64u, end=%I64u");
static const TCHAR* cszSendDataCmdFmt = TEXT("SendData src=%s");

typedef struct tagDACSendData
{
	unsigned long ulSourceID;
	EMSVARIANTRECORD recData;
} EMSSENDDATA;

static const TCHAR* cszUploadDataCmdFmt = TEXT("Upload target=%d, type=%d, max=%d, where=%s");

// For the control filenames returned by the Location Processor Controller
typedef TCHAR EMSCONTROLFILENAME[ 64 ];

// Location Processor Commands
static const TCHAR* cszLPSolve406CmdFmt = TEXT("Solve406 ControlFile=%s, DataFiles=%s, SignalName=%s");
static const TCHAR* cszLPDoneProcessingEvent = TEXT("LPDoneSolve406");
static const TCHAR* cszLPDoneProcessingEventManual = TEXT("LPDoneSolve406Manual");

// Gateway related command information
//
static const TCHAR* cszGtwyCmdLPCInitDataEnd = TEXT("LPCInitDataEnd status=%d, session=%d");
static const TCHAR* cszGtwyCmdLPCProcess406DataEnd = TEXT("LPCProcess406DataEnd status=%d");
static const TCHAR* cszGtwyCmdLPCGetFilenamesDataEnd = TEXT("LPCGetFilenamesDataEnd status=%d");
static const TCHAR* cszGtwyCmdGenericDataEnd = TEXT("DataEnd status=%d");
static const TCHAR* cszGtwyCmdDALGetEnd = TEXT("DALGetEnd status=%d, cache=%d, total=%d, size=%d, overflow=%d");

// Configuration Manager Communications

const unsigned long MAX_CONFIG_STRING_VALUE_LENGTH = 128;

// This is the same as the CM type EMSVARITYPE, but with a fixed length
// string to allow passing it over the EMSPipeline.
typedef struct _tagEMSFIXEDVARITYPE
{
	EMSVARITYPE_DATATYPE dataType;
	union 
    {
		boolean bVal;
		wchar_t wszVal[ MAX_CONFIG_STRING_VALUE_LENGTH + 1 ];
		EMSTIME tmVal;
		INT64 i64Val;
		int iVal;
		struct 
        {
			int iMaxVal;
			int iMinVal;
        } 	iRange;
		unsigned int uiVal;
		struct 
        {
			unsigned int uiMaxVal;
			unsigned int uiMinVal;
        } 	uiRange;
		double dVal;
		struct 
        {
			double dMaxVal;
			double dMinVal;
        } 	dRange;
		float fVal;
		struct 
        {
			float fMaxVal;
			float fMinVal;
        } 	fRange;
    /* [default] */  /* Empty union arm */ 
    } 	;
} EMSFIXEDVARITYPE;

static const TCHAR* cszCMGetCmdFmt = TEXT("Get user=%s, role=%d, grptype=%s, grpid=%s, key=%s");
static const TCHAR* cszCMSetStringCmdFmt = TEXT("SetString user=%s, role=%d, grptype=%s, grpid=%s, key=%s, value=%s");
static const TCHAR* cszCMLogContentsCmdFmt = TEXT("LogContents");

static const TCHAR* cszProcessInputPassSchedule = TEXT("ProcessInputPassSched");

#endif // __COMMAND_FORMATS_H__
