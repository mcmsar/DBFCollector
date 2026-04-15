
#include "commandlinelogger.h"
#include <stdarg.h>
#include <time.h>

CEMSCommandLineLogger::CEMSCommandLineLogger() : m_fpLog(0)
{
}

CEMSCommandLineLogger::CEMSCommandLineLogger( const CEMSCommandLineLogger& x) : m_fpLog(0)
{
}

CEMSCommandLineLogger::~CEMSCommandLineLogger()
{
	_CloseLogFile();
}

void 
CEMSCommandLineLogger::Log( const char* cszMessage, ... )
{
	va_list params;
	va_start( params, cszMessage );

	if( cszMessage )
	{
		vprintf( cszMessage, params );

		_GetLoggerFile();

		if( m_fpLog )
		{
			vfprintf( m_fpLog, cszMessage, params );
			fflush( m_fpLog );
		}
		else
		{
			printf("\nCouldn't open logger file.");
		}

	}
}

void 
CEMSCommandLineLogger::Log( const wchar_t* cwszMessage, ... )
{
	va_list params;
	va_start( params, cwszMessage );

	if( cwszMessage )
	{
		vwprintf( cwszMessage, params );

		_GetLoggerFile();

		if( m_fpLog )
		{
			vfwprintf( m_fpLog, cwszMessage, params );
			fflush( m_fpLog );
		}
		else
		{
			printf("\nCouldn't open logger file.");
		}

	}
}

void
CEMSCommandLineLogger::_GetLoggerFile()
{
	if( !m_fpLog )
	{
		if( !m_wszFileName.empty() )
		{
			m_fpLog = _wfopen( m_wszFileName.c_str(), L"a+" );
		}
		else
		{
			m_fpLog = fopen( m_szFileName.c_str(), "a+" );
		}
		

		if( m_fpLog )
		{
			time_t tNow;
			time( &tNow );

			fprintf( m_fpLog, "\nFile opened at %d", tNow );
		}
	}
}

void
CEMSCommandLineLogger::_CloseLogFile()
{
	if( m_fpLog )
	{
		fclose( m_fpLog );
		m_fpLog = 0;
	}
}