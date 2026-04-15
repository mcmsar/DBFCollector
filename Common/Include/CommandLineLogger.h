
#ifndef __COMMAND_LINE_LOGGER_H__
#define __COMMAND_LINE_LOGGER_H__

#include <stdio.h>
#include <string>

class CEMSCommandLineLogger
{
	public:
		CEMSCommandLineLogger();
		CEMSCommandLineLogger( const CEMSCommandLineLogger& x );
		~CEMSCommandLineLogger();

		void SetFileName( const char* cszFileName ) { m_szFileName = cszFileName; }
		void SetFileName( const wchar_t* cwszFileName ) { m_wszFileName = cwszFileName; }

		void Log( const char* cszMessage, ... );
		void Log( const wchar_t* cwszMessage, ... );

	private:
		void _CloseLogFile();
		void _GetLoggerFile();

	private:
		FILE*		m_fpLog;
		std::string m_szFileName;
		std::wstring m_wszFileName;
};

#endif