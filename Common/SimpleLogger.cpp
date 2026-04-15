
/********************************************************************
*	Module:			SimpleLogger.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	SimpleLogger
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include "simplelogger.h"
#include "convutility.h"
#include <sstream>
#include <iomanip>
#include <windows.h>
using namespace std;

const CEMSSystemClock c_sysClock;

int CLogger::nFilenameIndex = 0;//
//int  CLogger::m_nLevel = CLogger::All;
int  CLogger::m_nLevel = CLogger::None;

namespace
{
	const string LOG_DIRECTORY_NAME = "d:\\JournalLogs\\";
	const size_t LOGFILE_SIZE_LIMT	= 10000000;	//10 MB
	const string LOG_FILE_NAME	= "Journal_Log";
}


CLogger::CLogger()
{
	m_sFileName = LOG_FILE_NAME;
	++nFilenameIndex ;
	nFileWrittenBytes = 0;
}

BOOL EmptyDirectory( string strFile )
{
	WIN32_FIND_DATA	find;
	HANDLE				hFile;
	string strFileNames = strFile + string("\\*.*");
	if((hFile = FindFirstFile(strFileNames.c_str() , &find)) != INVALID_HANDLE_VALUE)
	{				
		do
		{
			string szFileName = strFile +  find.cFileName ;
			::DeleteFile( szFileName.c_str() );					
		} while( ::FindNextFile(hFile, &find));
		FindClose(hFile);		
	}
	return TRUE;
}

BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void CLogger::SetLevel(int nLevel)
{
    m_nLevel = nLevel;
}

void CLogger::Init ( std::string strEventName )
{
	try
	{
		SetLevel( m_nLevel );
		if( m_nLevel == None )
			return;
		m_strEventName = strEventName;

		if( DirectoryExists( LOG_DIRECTORY_NAME.c_str()) )
		{
			//EmptyDirectory(  LOG_DIRECTORY_NAME );
		}
		else
		{
			BOOL bRet = CreateDirectoryA( LOG_DIRECTORY_NAME.c_str(), NULL );			
			if( !bRet )
				m_nLevel = None;
		}

		m_Logfile.open( (LOG_DIRECTORY_NAME + GetFileName() ).c_str(), ios::out  );
	}
	catch(...)
	{
		m_nLevel = None;
	}
}

string CLogger::GetFileName ( )
{
	std::ostringstream os;
	//os << m_sFileName << "_" << nFilenameIndex << ".txt";
	if( m_strEventName.empty() )
		os << m_sFileName << "_" << GetCurrentDateTimeStringEx() << nFilenameIndex << ".txt";
	else
		os << m_sFileName << "_" << GetCurrentDateTimeStringEx() << "_" << m_strEventName << ".txt";

	return os.str();
}

void CLogger::Log( const string& sMessage )
{
	if( m_nLevel == None )
		return;
	string logString = "  " +  GetCurrentDateTimeString() + ":\t" + sMessage ;
    m_Logfile << logString <<endl;
	nFileWrittenBytes += logString.size();
	if( HasFilesizeLimitExceeded() )
	{
		CloseAndCreateNewLogger();
		nFileWrittenBytes = 0;
	}
}


void CLogger::LogWithTimeElapsed( string formatString,  double number )
{
	if( m_nLevel == None )
		return;
	string szLogType = "Info: ";
	double dTime = GetTimeStampDiffInSecs(  );
	if( dTime > 5 && dTime < 10 )
	{
		szLogType = "Warning : ";
	}
	else if (dTime > 10 )
	{
		szLogType = "Alarm!! ";
	}
	std::ostringstream logString;

	logString << "  " <<  GetCurrentDateTimeString() << ":\t" << szLogType << formatString <<  number << " Time Taken in seconds : "<< dTime;
	m_Logfile << logString.str() << endl;
	nFileWrittenBytes += logString.str().size();
	if( HasFilesizeLimitExceeded() )
	{
		CloseAndCreateNewLogger();
		nFileWrittenBytes = 0;
	}
}

BOOL CLogger::HasFilesizeLimitExceeded () 
{
	if( nFileWrittenBytes > LOGFILE_SIZE_LIMT )
		return TRUE;
	return FALSE;
}

BOOL CLogger::CloseAndCreateNewLogger ()
{

	m_Logfile.close();
	//++nFilenameIndex;
	m_Logfile.open( (LOG_DIRECTORY_NAME + GetFileName() ).c_str(), ios::out  );

	 return TRUE;
}



std::string CLogger::GetCurrentDateTimeStringEx ()
{
	std::stringstream wstrmRet;
	CEMSTime timeNow;
	timeNow.SetTime( c_sysClock.GetTime( ) );

	CEMSTime oTime( timeNow );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << "_" << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMonth << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nDay << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nHour << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMinute << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nSecond;

	return wstrmRet.str();
	
}

std::string CLogger::GetCurrentDateTimeString ()
{
	std::stringstream wstrmRet;
	CEMSTime timeNow;
	timeNow.SetTime( c_sysClock.GetTime( ) );

	CEMSTime oTime( timeNow );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << "-" << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMonth << "-"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nDay << "  "  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nHour << ":"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMinute << ":"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nSecond;

	return wstrmRet.str();
	
}

void CLogger::StartTimer ()
{
	if( m_nLevel == None )
		return;
	timeStart =  CEMSSystemClock::GetTime();
}

double CLogger::GetTimeStampDiffInSecs(  )
{
	if( m_nLevel == None )
		return -1;
	CEMSTime timeEnd = CEMSSystemClock::GetTime();
	return timeStart.SecondsDifferent( timeEnd );
}