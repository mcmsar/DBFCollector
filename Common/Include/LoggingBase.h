
#ifndef __LOGGING_BASE_H__
#define __LOGGING_BASE_H__

#include <wchar.h>
#include "emsexcpt.h"
#include "emsloggr.h"
#include "LogMsgParam.h"
#include "LogHelper.h"

class CEMSLoggingBase
{
	public:
		CEMSLoggingBase( const unsigned short cusCategory, const unsigned long ulLutID=0 );
		virtual ~CEMSLoggingBase();

		void SetCategory( const unsigned short cusCat ) { m_usMsgCategory = cusCat; }
		void SetLutID( const ULONG culLutID ) { m_ulThisLutID = culLutID; }

		// Log a message with appropriate status
		void LogInfoMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
			{	_InitLogger(); CEMSLogHelper::LogInfoMsg( cdwMsg, param ); }
		void LogAlarmMsg( const DWORD cdwMsg, EMS_RESULT hrParam );
		void LogAlarmMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
			{	_InitLogger(); CEMSLogHelper::LogAlarmMsg( cdwMsg, param ); }
		void LogWarningMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
			{	_InitLogger(); CEMSLogHelper::LogWarningMsg( cdwMsg, param ); }
		void LogTraceMsg( const DWORD cdwMsg, CEMSLogMsgParam& param )
			{	_InitLogger(); CEMSLogHelper::LogTraceMsg( cdwMsg, param ); }

		// The following are convenience versions for messages with a single parameter
		void LogInfoMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL )
			{	_InitLogger(); CEMSLogHelper::LogInfoMsg( cdwMsg, wszSingleParam ); }
		void LogAlarmMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL )
			{	_InitLogger(); CEMSLogHelper::LogAlarmMsg( cdwMsg, wszSingleParam ); }
		void LogWarningMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL )
			{	_InitLogger(); CEMSLogHelper::LogWarningMsg( cdwMsg, wszSingleParam ); }
		void LogTraceMsg( const DWORD cdwMsg, LPCWSTR wszSingleParam = NULL )
			{	_InitLogger(); CEMSLogHelper::LogTraceMsg( cdwMsg, wszSingleParam ); }

		void LogInfoMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
		void LogAlarmMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
		void LogWarningMsg( const DWORD cdwMsg, LPCSTR szSingleParam );
		void LogTraceMsg( const DWORD cdwMsg, LPCSTR szSingleParam );

		// Log the exception as an alarm + log a trace indicating where it occurred
		// Will not log the exception if this has already happened
		// The trace will happen regardless
		void LogException( CEMSException& ex, const bool cbAsAlarm = true )
			{	_InitLogger(); CEMSLogHelper::LogException( ex, cbAsAlarm ); }

		//! @fn void Reset()
		//! Used to release the underlying pointer to the logger object.
			void Reset();

	private:	// methods
		void					_InitLogger();

	private:	// data
		unsigned long			m_ulThisLutID;
		unsigned short			m_usMsgCategory;
		bool					m_bInitialized;
};

#endif	// __LOGGING_BASE_H__