//! @file LogHelper.h
//! Header file for the CEMSLogHelper class.
/********************************************************************
*	Module:			LogHelper.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2004-2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Oct31		CH		Start
		2003Nov03		CH		Added LutID parameters

********************************************************************/
#ifndef __INC_LOGHELPER
#define __INC_LOGHELPER

#include <objbase.h>       // defines "interface"
#include "AObjBase.h"
#include "emserror.h"		// EMS_RESULT
#include "emsloggr.h"

interface IEMS600LoggerEx;
class CEMSCriticalSection;
class CEMSException;
class CEMSLogMsgParam;

#define LH_MAX_PROCESSNAMELEN 64

class CEMSLogHelper : public CApiObjBase
{
public:
	CEMSLogHelper(): CApiObjBase(TEXT("EMSLogHelper")), m_pLogger(NULL) {}
	virtual ~CEMSLogHelper();

	// The calls to Init() and Reset() are very similar to AddRef()/Release()
	// They must be matched to avoid premature destruction or memory leaks.
	static void Init( const unsigned long culLutID, const WORD cwProcessID );
	static void Reset();

	// Log a message with appropriate status
	static void LogInfoMsg( const DWORD cdwMsg, CEMSLogMsgParam& param );
	static void LogAlarmMsg( const DWORD cdwMsg, CEMSLogMsgParam& param );
	static void LogWarningMsg( const DWORD cdwMsg, CEMSLogMsgParam& param );
	static void LogTraceMsg( const DWORD cdwMsg, CEMSLogMsgParam& param );
	static void LogDebugMsg( const DWORD cdwMsg, CEMSLogMsgParam& param );
	static void LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, CEMSLogMsgParam& param );

	// The following are convenience versions for messages with a single parameter
	static void LogInfoMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );
	static void LogAlarmMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );
	static void LogWarningMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );
	static void LogTraceMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );
	static void LogDebugMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );
	static void LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL );


	// The following are convenience versions for messages with a single parameter
	static void LogInfoMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
	static void LogAlarmMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
	static void LogWarningMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
	static void LogTraceMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
	static void LogDebugMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
	static void LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCSTR szSingleParam );

	static void LogAlarmMsg( const DWORD cdwMsg, const EMS_RESULT cerrResult );

	// Log the exception as an alarm + log a trace indicating where it occurred
	// Will not log the exception if this has already happened
	// The trace will happen regardless
	static void LogException( CEMSException &ex, bool bAsAlarm=true );

private:   
	void _Init( const unsigned long culLutID, const WORD cwProcessID );
	unsigned long	_GetLutID( const unsigned long culLutID );

	void _LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, CEMSLogMsgParam& param );
	void _LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCWSTR wszSingleParam );


	IEMS600LoggerEx*			m_pLogger;

	static CEMSLogHelper*		ms_pLogger;
	static CEMSCriticalSection	ms_csLoggerCreation;

#ifdef _DEBUG
static void _LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, CEMSLogMsgParam& param );
static void _LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, LPCWSTR wszSingleParam );
#else
static void _LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, CEMSLogMsgParam& param ) {}
static void _LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, LPCWSTR wszSingleParam ) {}
#endif

};


// Standard implementation of logging methods
inline void 
CEMSLogHelper::LogInfoMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	LogMsg( EMSLogMsgInfo, cdwMsg, param );
}
inline void 
CEMSLogHelper::LogAlarmMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	LogMsg( EMSLogMsgAlarm, cdwMsg, param );
}
inline void 
CEMSLogHelper::LogWarningMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	LogMsg( EMSLogMsgWarn, cdwMsg, param );
}
inline void 
CEMSLogHelper::LogTraceMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	LogMsg( EMSLogMsgTrace, cdwMsg, param );
}
inline void 
CEMSLogHelper::LogDebugMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	LogMsg( EMSLogMsgDebug, cdwMsg, param );
}

//wchar_t
inline void 
CEMSLogHelper::LogInfoMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	LogMsg( EMSLogMsgInfo, cdwMsg, wszSingleParam );
}
inline void 
CEMSLogHelper::LogAlarmMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	LogMsg( EMSLogMsgAlarm, cdwMsg, wszSingleParam );
}
inline void 
CEMSLogHelper::LogWarningMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	LogMsg( EMSLogMsgWarn, cdwMsg, wszSingleParam );
}
inline void 
CEMSLogHelper::LogTraceMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	LogMsg( EMSLogMsgTrace, cdwMsg, wszSingleParam );
}
inline void 
CEMSLogHelper::LogDebugMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	LogMsg( EMSLogMsgDebug, cdwMsg, wszSingleParam );
}
//char*
inline void
CEMSLogHelper::LogInfoMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{
	LogMsg( EMSLogMsgInfo, cdwMsg, szSingleParam );
}
inline void 
CEMSLogHelper::LogAlarmMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{
	LogMsg( EMSLogMsgAlarm, cdwMsg, szSingleParam );
}
inline void 
CEMSLogHelper::LogWarningMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{
	LogMsg( EMSLogMsgWarn, cdwMsg, szSingleParam );
}
inline void 
CEMSLogHelper::LogTraceMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{
	LogMsg( EMSLogMsgTrace, cdwMsg, szSingleParam );
}
inline void 
CEMSLogHelper::LogDebugMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{
	LogMsg( EMSLogMsgDebug, cdwMsg, szSingleParam );
}

#endif // __INC_LOGHELPER
