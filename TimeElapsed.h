#pragma once
#include <string>
#include <sstream>
#include "EMSTIME.H"
#include "EMSCLOCK.H"
#include "convutility.h"
#define LOG_FILE		0

class CTimeElapsed
{
public:
	CTimeElapsed( ) 
	{
	};
	CTimeElapsed::~CTimeElapsed()
	{
		
	}
	static void fileOpen()
	{
#if LOG_FILE == 1
		m_pTimingFile = fopen ("c:\\dbf_timing_log.txt","a+");
#endif
	}

	static void fileClose()
	{
#if LOG_FILE == 1

		fclose( m_pTimingFile );
#endif
	}
	void FuncTimerStart( std::string descr )
	{
		m_description = descr;
		_TimeStart();
	}
	void FuncTimerClose ()
	{
		_TimeFinish();
	}
	void PrintFinalTimes ()
	{
#if LOG_FILE == 1

		if( m_pTimingFile )
		{
			m_oStrm << std::endl;
			fprintf( m_pTimingFile, m_oStrm.str().c_str() );
			//fprintf( m_pTimingFile, "\n" );
		}
#endif
	}
	static void printMessage( std::string msg )
	{
#if LOG_FILE == 1


		if( m_pTimingFile )
			fprintf( m_pTimingFile,"Timestamp: %s,  %s \n" ,
				CEMSConversionUtil::ConvertToDateTimeHiResString2A( CEMSSystemClock::GetTime() ).c_str(), msg.c_str());
#endif
	}
private:
	void _TimeStart() 
	{
		m_timeStart =  CEMSSystemClock::GetTime();
	
	}
	void _TimeFinish() 
	{
		CEMSTime timeEnd =  CEMSSystemClock::GetTime();

#if LOG_FILE == 1

	    EMSTIME timeNow = CEMSSystemClock::GetTime();

		m_oStrm << " Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( timeNow )
				<< " Func: " << m_description
				<< " Time elapsed: " << m_timeStart.SecondsDifferent( timeEnd)
				<< " Thread id: " << GetCurrentThreadId() << std::endl ;
#endif		
		printf( "\nTimestamp: %s, Time elapsed for %s is : %f seconds , threadid: %i \n" ,
			CEMSConversionUtil::ConvertToDateTimeHiResString2A( timeEnd ).c_str(),m_description.c_str(),
			m_timeStart.SecondsDifferent( timeEnd),  GetCurrentThreadId() );

	}
private:
	CEMSTime m_timeStart;
	std::string m_description;
#if LOG_FILE == 1

	std::stringstream m_oStrm;
	static FILE	*m_pTimingFile;
#endif
};