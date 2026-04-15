/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __LOG_CLIENT_H__
#define __LOG_CLIENT_H__

#pragma warning(disable:4251)

#include "emsloggr.h"
#include "logstring.h"

namespace log4cxx{
class Logger;
}

class CEMSLogMsgParam;
class CEMSException;

// Used internally by the log client
typedef std::basic_string<TCHAR> EMSLOGTString;

//! Client used by logging framework consumers.  Use this class as a base class
//! for other classes that need to have class level logging.  
//! The logger name will be EMSLOG_<Derived Class Name>.  
//! Alternatively, this class can be instantiated and given any logger name.
class __declspec(dllexport) CEMSLogClient
{
	public:
		CEMSLogClient();
		CEMSLogClient( const wchar_t* cwszParent );
		CEMSLogClient( const char* cszParent );
		CEMSLogClient( const CEMSLogClient& x );
		~CEMSLogClient();

		//! Initialize the logging subsystem by pointing it at a configuratin file.
		void InitializeLogging( const EMSLOGString& coszConfigFile );

		//! Specify the message table to use by providing an application identifier.
		void InitializeMessageTable( const int ciAppID );

		//! Initialize process-wide settings used for logging.
		void InitializeProcess( const wchar_t* cwszName, const ULONG culProcessID, const ULONG culLutID );

		//! Initialize with default settings.  The log4cxx BasicConfigurator is used
		//! and the EMSAPP_MSGTABLE message table is initialized.
		void InitializeDefault();

		//! Looks for a log4j.properties file to initialize with in the registry.
		//! Optionally specifying an alternate name for the registry value 
		//! that holds the ini filename
		void InitializeFromRegistry( const wchar_t* cwszRegValueName = NULL );

		//! Set the LUT ID to include in LOG records.
		void SetLutID( const ULONG culLutID );

		//! Set the process ID to include in LOG records.
		void SetProcessID( const ULONG culProcessID );

		//! Safely close and remove all appenders in all loggers including the root logger.
		void Shutdown();

		//! Can be used to set the name of the logger to use.
		//! If not called, the default is ms_szPrefix with instantiated class's name
		//! appended (where this class is the base class).
		void SetLogger( const EMSLOGString& coszLogger );

		//! Can be used to set the name of the parent class.
		//! If not called, the default is ms_szPrefix with instantiated class's name
		//! appended (where this class is the base class) or if there is an intermediate
		//! derived class, it's name will be used.
		void SetParent( const EMSLOGString& coszParent );

		void LogInfoMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogFatalMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogAlarmMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogWarningMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogTraceMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogDebugMsg( const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );
		void LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, CEMSLogMsgParam& oParam, const char* szFile=0, int iLine=-1 );
					//const log4cxx::spi::LocationInfo& locationInfo );

		void LogMsg( const EMSLOGMSGTYPE ceType, const char* szFile, int iLine, const wchar_t* wszFmtString, ... );

		void LogAlarmMsg( const DWORD cdwMsg, const EMS_RESULT cerrResult, const char* szFile=0, int iLine = -1 );
				//const log4cxx::spi::LocationInfo& locationInfo );

		//! Log the exception as an alarm + log a trace indicating where it occurred
		//! Will not log the exception if this has already happened
		//! The trace will happen regardless
		void LogException( CEMSException &ex, const char* szFile=0, int iLine=-1,
						const bool cbAsAlarm=true );

		void Log( const EMSLOGMSGTYPE ceType, const wchar_t* szMessage, const char* szFile=0, int iLine=-1 );

		//! Push context information.  Should have a matching PopContext call.
		static void PushContext( const wchar_t* cwszContext );
		
		//! Pop context information.  Call this when exiting a particular context.  This
		//! call should match a PushContext call.
		static void PopContext();

		//! Remove all nested diagnostic context information for the thread.
		static void RemoveContext();

		//! Set key/value context pair for the thread.
		static void PutMappedContext( const wchar_t* cwszKey, const wchar_t* cwszValue );

		//! Delete all key/value context pairs for the thread;
		static void ClearMappedContext();

		//! Determine whether the logger is enabled for the given level.
		bool IsEnabledFor( const EMSLOGMSGTYPE ceMsgType );

		//! Determine whether the debug level is enabled for the logger.
		bool IsDebugEnabled();

		//! Overloaded assignement operator.
		CEMSLogClient& operator=( const CEMSLogClient& coRHS );

	private:
		void _GetLogger();

		void _LogWithParams( const DWORD cdwMsg, CEMSLogMsgParam& oParam, 
							const EMSLOGMSGTYPE ceMsgType, 
							const char* szFile=0, int iLine = -1 );
							//const log4cxx::spi::LocationInfo& locationInfo );

		EMSLOGTString _GetKey( const DWORD cdwMsg );

		void _ExtractParams( CEMSLogMsgParam& oParam, 
							 EMSLOGTString*& aoszParams, 
							 long& lNumParams );

		int _GetLevel( const EMSLOGMSGTYPE ceMsgType );

		bool _ReplaceErrorCodes( std::wstring& wstrParam );

	private:
		EMSLOGString m_oszLoggerName;
		log4cxx::Logger* m_pLogger;

	private:
		static const wchar_t* ms_cwszHierarchySep;
};

/** @addtogroup EMSLoggingMacros Logging macros
@{
*/

/** 
Logs a message string to a specified logger with a specified level.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
*/
#define EMSLOG( logger, level, string ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	logger->Log( level, string , __FILE__, __LINE__ ); }}}

/** 
Logs a debug message string to a specified logger.

@param logger the logger to be used.
@param string the message string to log.
*/
#define EMSLOG_DEBUG( logger, string ) {\
	if( logger ) {\
	if( logger->IsDebugEnabled() ) {\
	logger->Log( EMSLogMsgDebug, string , __FILE__, __LINE__ ); }}}



/** 
Logs a message identified by a message id/key to a specified logger with a specified level.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
*/
#define EMSLOG0( logger, level, key ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ){\
	CEMSLogMsgParam oParam; \
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }}}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having a single parameter.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param stringparam a wchar_t* substitution parameter.
*/
#define EMSLOG1( logger, level, key, stringparam ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	CEMSLogMsgParam oParam; \
	oParam.Add( stringparam );\
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }}}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having two parameters.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param stringparam1 a wchar_t* substitution parameter.
@param stringparam2 a wchar_t* substitution parameter.
*/
#define EMSLOG2( logger, level, key, stringparam1, stringparam2 ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	CEMSLogMsgParam oParam; \
	oParam.AddString( stringparam1 );\
	oParam.AddString( stringparam2 );\
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }}}


/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having three parameters.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param stringparam1 a wchar_t* substitution parameter.
@param stringparam2 a wchar_t* substitution parameter.
@param stringparam3 a wchar_t* substitution parameter.
*/

#define EMSLOG3( logger, level, key, wstringparam1, wstringparam2, wstringparam3 ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	CEMSLogMsgParam oParam; \
	oParam.AddString( wstringparam1 );\
	oParam.AddString( wstringparam2 );\
	oParam.AddString( wstringparam3 );\
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }}}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having four parameters.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param stringparam1 a wchar_t* substitution parameter.
@param stringparam2 a wchar_t* substitution parameter.
@param stringparam3 a wchar_t* substitution parameter.
@param stringparam4 a wchar_t* substitution parameter.
*/
#define EMSLOG4( logger, level, key, wstringparam1, wstringparam2, wstringparam3, wstringparam4 ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	CEMSLogMsgParam oParam; \
	oParam.AddString( wstringparam1 );\
	oParam.AddString( wstringparam2 );\
	oParam.AddString( wstringparam3 );\
	oParam.AddString( wstringparam4 );\
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }}}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having a parameter object.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param params a CEMSLogMsgParam object holding a series of parameters.
*/
#define EMSLOGEX( logger, level, key, params	 ) {\
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	logger->LogMsg( level, key, params, __FILE__, __LINE__ ); }}}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having a parameter object.  Also included is a context key/value pair.  The context lifetime is 
only for the duration of this call after which it is cleared.

@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param params a CEMSLogMsgParam object holding a series of parameters.
@param ctxkey a wchar_t* context key.
@param ctxvalue a wchar_t* context value.
*/
#define EMSLOGEXCTX1( logger, level, key, params, ctxkey, ctxvalue	 ) {\
	CEMSLogClient::PutMappedContext( ctxkey, ctxvalue ); \
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	logger->LogMsg( level, key, params, __FILE__, __LINE__ ); }\
	CEMSLogClient::PutMappedContext( ctxkey, L"" ); }}

/** 
Logs a message identified by a message id/key to a specified logger with a specified level and
having a single parameter.  Also included is a context key/pair.  The context lifetime is only
for the duration of this call after which it is cleared.
@param logger the logger to be used.
@param level the EMSLOGMSGTYPE level to log.
@param key the message string to log.
@param stringparam a wchar_t* substitution parameter.
@param ctxkey a wchar_t* context key.
@param ctxvalue a wchar_t* context value.
*/
#define EMSLOG1CTX1( logger, level, key, stringparam, ctxkey, ctxvalue ) {\
	CEMSLogClient::PutMappedContext( ctxkey, ctxvalue ); \
	if( logger ) {\
	if( logger->IsEnabledFor( level ) ) {\
	CEMSLogMsgParam oParam; \
	oParam.Add( stringparam );\
	logger->LogMsg( level, key, oParam, __FILE__, __LINE__ ); }\
	CEMSLogClient::PutMappedContext( ctxkey, L"" ); }}

/*@}*/

#endif