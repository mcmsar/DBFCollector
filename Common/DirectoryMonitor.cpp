/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/
#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length

#include "directorymonitor.h"
#include "emsexcpt.h"
#include <crtdbg.h>
#include "convutility.h"
#include "directoryinfo.h"
#include "filelist.h"
#include "fileutility.h"
#include "emsclock.h"
#include <sys/types.h> 
#include <sys/stat.h>

#include <windows.h>

const ULONG culShutdownTimeout = 5000; // 5 seconds.
const ULONG culCheckInterval = 1000;	// 1 second
const ULONG culMaxFilesHandledPerCheck  = 20;

CEMSDirectoryMonitor::CEMSDirectoryMonitor() : m_hIOCompletionPort(NULL), 
											m_ulNotifyFilter(EMS_FILE_NOTIFY_CHANGE_LAST_WRITE | EMS_FILE_NOTIFY_CHANGE_FILE_NAME),
											m_hr( EMS_OK )
{
	m_timeLastFile.intTime = 0;
}

CEMSDirectoryMonitor::CEMSDirectoryMonitor( const CEMSDirectoryMonitor& x ) : m_ulNotifyFilter( x.m_ulNotifyFilter ), 
																		m_hr( x.m_hr ),
																		m_timeLastFile(x.m_timeLastFile)
{
}

CEMSDirectoryMonitor::~CEMSDirectoryMonitor()
{
	StopMonitor();
}

void 
CEMSDirectoryMonitor::StartMonitor()
{
	try
	{
		m_cs.Enter();
		StopMonitor();
		start();
		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void 
CEMSDirectoryMonitor::Populate()
{
	try
	{
		m_cs.Enter();

		StopMonitor();

		FILENAMEVECTORW vecFileNames;

		std::wstring owszFiles = m_wszDirectory;
//		owszFiles.append( L"\\*" );
		owszFiles.append( L"\\*.*" );

		////if( !m_wszExtension.empty() )
		////{
		////	owszFiles.append( m_wszExtension.c_str() );		
		////}
		////if( !m_wszExtension2.empty() )
		////{
		////	owszFiles.append( m_wszExtension2.c_str() );		
		////}

		CEMSFileList oFileList;
		oFileList.GetFilenamesW( owszFiles.c_str(), vecFileNames );

		for( int i = 0; i < vecFileNames.size(); i++ )
		{
			std::wstring owszNewFile = m_wszDirectory;

			if( L'\\' != owszNewFile.at( owszNewFile.length() - 1 ) )
				owszNewFile.append( L"\\" );

			owszNewFile.append( *(vecFileNames[i]) );

			// Skip sub-directories.  Skip if _wstat fails.
			struct _stat fileStats;
			if( 0 == _wstat( owszNewFile.c_str(), &fileStats ) )
			{
				if( (fileStats.st_mode & _S_IFREG) == _S_IFREG )
					_Add( owszNewFile );
			}
		}

		oFileList.ReleaseFilenamesW( vecFileNames );

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void 
CEMSDirectoryMonitor::Populate( const ULONG culMaxFiles )
{
	{
	try
	{
		m_cs.Enter();

		StopMonitor();

		FILENAMEVECTORW vecFileNames;

		std::wstring owszFiles = m_wszDirectory;
//		owszFiles.append( L"\\*" );
		owszFiles.append( L"\\*.*" );

		////if( !m_wszExtension.empty() )
		////{
		////	owszFiles.append( m_wszExtension.c_str() );		
		////}
		////if( !m_wszExtension2.empty() )
		////{
		////	owszFiles.append( m_wszExtension2.c_str() );		
		////}

		CEMSFileList oFileList;
		oFileList.GetFilenamesW( owszFiles.c_str(), vecFileNames );

		for( int i = 0; i < vecFileNames.size() && i < culMaxFiles; i++ )
		{
			std::wstring owszNewFile = m_wszDirectory;

			if( L'\\' != owszNewFile.at( owszNewFile.length() - 1 ) )
				owszNewFile.append( L"\\" );

			owszNewFile.append( *(vecFileNames[i]) );

			// Skip sub-directories.  Skip if _wstat fails.
			struct _stat fileStats;
			if( 0 == _wstat( owszNewFile.c_str(), &fileStats ) )
			{
				if( (fileStats.st_mode & _S_IFREG) == _S_IFREG )
					_Add( owszNewFile );
			}
		}

		oFileList.ReleaseFilenamesW( vecFileNames );

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}
}

void 
CEMSDirectoryMonitor::PopulateAndStart()
{
	try
	{
		m_cs.Enter();

		StopMonitor();

		FILENAMEVECTORW vecFileNames;

		std::wstring owszFiles = m_wszDirectory;
//		owszFiles.append( L"\\*" );
		owszFiles.append( L"\\*.*" );

		////if( !m_wszExtension.empty() )
		////{
		////	owszFiles.append( m_wszExtension.c_str() );		
		////}
		////if( !m_wszExtension2.empty() )
		////{
		////	owszFiles.append( m_wszExtension2.c_str() );		
		////}

		CEMSFileList oFileList;
		oFileList.GetFilenamesW( owszFiles.c_str(), vecFileNames );

		for( int i = 0; i < vecFileNames.size(); i++ )
		{
			std::wstring owszNewFile = m_wszDirectory;
			owszNewFile.append( L"\\" );
			owszNewFile.append( *(vecFileNames[i]) );
			
			// Skip sub-directories.  Skip if _wstat fails.
			struct _stat fileStats;
			if( 0 == _wstat( owszNewFile.c_str(), &fileStats ) )
			{
				if( (fileStats.st_mode & _S_IFREG) == _S_IFREG )
					_Add( owszNewFile );
			}

		}

		oFileList.ReleaseFilenamesW( vecFileNames );

		start();

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void
CEMSDirectoryMonitor::StopMonitor()
{
	try
	{
		m_cs.Enter();

		SignalStop();

		bool bShutdownOkay = wait( culShutdownTimeout );

		if( !bShutdownOkay )
			stop();		// Force the thread to stop.

		_ReleaseResources();

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void 
CEMSDirectoryMonitor::SetDirectory( const wchar_t* cwszDirectory )
{
	try
	{
		m_cs.Enter();

		if( cwszDirectory )
		{
			m_wszDirectory = cwszDirectory;
		}

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void 
CEMSDirectoryMonitor::SetFileExtension( const wchar_t* cwszFileExtension )
{
	try
	{
		m_cs.Enter();

		if( cwszFileExtension )
		{
			m_wszExtension = cwszFileExtension;
		}

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

void 
CEMSDirectoryMonitor::SetFileExtension2( const wchar_t* cwszFileExtension2 )
{
	try
	{
		m_cs.Enter();

		if( cwszFileExtension2 )
		{
			m_wszExtension2 = cwszFileExtension2;
		}

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}
}

std::wstring 
CEMSDirectoryMonitor::Pop()
{
	std::wstring owszRet;

	try
	{
		m_cs.Enter();

		owszRet = m_queueFileNames.Pop();

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}

	return owszRet;
}

ULONG
CEMSDirectoryMonitor::GetCount()
{
	ULONG ulRet = 0;

	try
	{
		m_cs.Enter();

		ulRet = m_queueFileNames.Count();

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}

	return ulRet;
}

EMSTIME 
CEMSDirectoryMonitor::GetLastFileReceivedTime()
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	try
	{
		m_cs.Enter();

		timeRet = m_timeLastFile;

		m_cs.Leave();
	}
	catch( ... )
	{
		m_cs.Leave();
		throw;
	}

	return timeRet;
}

void
CEMSDirectoryMonitor::run()
{
	try
	{
		m_hr = EMS_OK;

		_SetupCompletionPort();
		_Monitor();
	}
	catch( CEMSException& e )
	{
		m_hr = e.GetErrCode();
	}
	catch( ... )
	{
		m_hr = EMS_UNKNOWN_ERROR;
	}
}

void
CEMSDirectoryMonitor::_SetupCompletionPort()
{
	_ASSERTE( !m_wszDirectory.empty() );

	if( m_wszDirectory.empty() )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	HANDLE hDir = INVALID_HANDLE_VALUE;

	try
	{
		_EnablePrivileges();

		// Hook up a listener on the directory.
		hDir = CreateFileW( m_wszDirectory.c_str(), FILE_LIST_DIRECTORY, 
							FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE,
							NULL, OPEN_EXISTING, 
							FILE_FLAG_BACKUP_SEMANTICS| 
							FILE_FLAG_OVERLAPPED,	
							NULL );

		if( INVALID_HANDLE_VALUE == hDir )
		{
			THROW_RUNTIME_EXCEPTION( EMS_PATH_NOT_FOUND );
		}

		m_oDirInfo.SetHandle( hDir );

		hDir = INVALID_HANDLE_VALUE;	// ownership handed to m_oDirInfo.

		m_oDirInfo.SetDirName( m_wszDirectory.c_str() );

		m_hIOCompletionPort = CreateIoCompletionPort( m_oDirInfo.GetHandle(), m_hIOCompletionPort, 
													(DWORD) &m_oDirInfo, 0 );

		if( NULL == m_hIOCompletionPort )
		{
			THROW_RUNTIME_EXCEPTION( EMS_INVALID_HANDLE );
		}
	}
	catch( ... )
	{
		throw;
	}

}

void
CEMSDirectoryMonitor::_Monitor()
{
	try
	{
		// Start watching the directory.	
		if( !ReadDirectoryChangesW( m_oDirInfo.GetHandle(), m_oDirInfo.GetBuffer(), m_oDirInfo.GetMaxBuffer(), 
								FALSE, _GetNotifyFilter(), m_oDirInfo.GetBufferLengthPointer(),
								m_oDirInfo.GetOverLappedPointer(), NULL ) )
		{
			THROW_RUNTIME_EXCEPTION( CEMSConversionUtil::ErrnoToEMSResult( GetLastError() ) );
		}

		do
		{
			CEMSDirectoryInfo* pDirInfo = 0;
			DWORD dwNumBytes = 0;
			LPOVERLAPPED pOverLapped = 0;
			PFILE_NOTIFY_INFORMATION pFNI = 0;
			DWORD cbOffset = 0;

			// Retrieve the directory info for this directory through the completion key.
			GetQueuedCompletionStatus( m_hIOCompletionPort, &dwNumBytes, (PULONG_PTR) &pDirInfo, 
										&pOverLapped, culCheckInterval );

			if( pDirInfo && dwNumBytes )
			{
				pFNI = (PFILE_NOTIFY_INFORMATION) pDirInfo->GetBuffer();

				do
				{
					cbOffset = pFNI->NextEntryOffset;

					if( FILE_ACTION_MODIFIED == pFNI->Action || 
						FILE_ACTION_RENAMED_NEW_NAME == pFNI->Action ||
						FILE_ACTION_ADDED == pFNI->Action )
					{
						_OnHandleFile( pDirInfo, pFNI );
					}

					pFNI = (PFILE_NOTIFY_INFORMATION) ((LPBYTE) pFNI + cbOffset );

				} while( cbOffset );

				// Reissue the watch command.
				if( !ReadDirectoryChangesW( pDirInfo->GetHandle(), pDirInfo->GetBuffer(), pDirInfo->GetMaxBuffer(), 
								FALSE, _GetNotifyFilter(), pDirInfo->GetBufferLengthPointer(),
								pDirInfo->GetOverLappedPointer(), NULL ) )
				{
					THROW_RUNTIME_EXCEPTION( CEMSConversionUtil::ErrnoToEMSResult( GetLastError() ) );
				}
			}

		} while( !WaitForStop(culCheckInterval) );
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSDirectoryMonitor::_OnHandleFile( CEMSDirectoryInfo* pDirInfo, PFILE_NOTIFY_INFORMATION pFNI )
{
	if( pDirInfo && pFNI )
	{
		wchar_t* wszFilename = 0;

		try
		{
			std::wstring wszFullPath;
			wszFullPath += pDirInfo->GetDirName();
			wszFullPath += L"\\";

			// According Platform SDK Documentation, 
			// PFILE_NOTIFY_INFORMATION::FileName is unicode string (not NULL-terminated).
			// PFILE_NOTIFY_INFORMATION::FileNameLength is the string length in bytes.

			if( pFNI->FileNameLength > 0 )
			{
				wszFilename = new wchar_t[ pFNI->FileNameLength/sizeof(wchar_t) + 1];

				if( !wszFilename )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( wszFilename, 0, sizeof(wchar_t)*(pFNI->FileNameLength/sizeof(wchar_t) + 1) );

				wcsncpy( wszFilename, pFNI->FileName, pFNI->FileNameLength/sizeof(wchar_t) );
			}
			else
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

		
			wszFullPath += wszFilename;

			OutputDebugStringW( L"\n");
			OutputDebugStringW( wszFullPath.c_str() );

			// Don't write the same file more than once consecutively to the queue.
			// A copy into the directory can produce multiple file write notifications for the same
			// file.
			if( wszFullPath != m_wszLastFileName )	
				_Add( wszFullPath );

			m_wszLastFileName = wszFullPath;

			delete[] wszFilename;
			wszFilename = 0;

		}
		catch( ... )
		{
			if( wszFilename )
			{
				delete[] wszFilename;
				wszFilename = 0;
			}

			throw;
		}
	}
}

ULONG 
CEMSDirectoryMonitor::_GetNotifyFilter()
{
	ULONG ulRet = 0;

#ifdef WIN32
	if( EMS_FILE_NOTIFY_CHANGE_FILE_NAME == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_FILE_NAME) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_FILE_NAME;
	}

	if( EMS_FILE_NOTIFY_CHANGE_DIR_NAME == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_DIR_NAME) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_DIR_NAME;
	}

	if( EMS_FILE_NOTIFY_CHANGE_ATTRIBUTES == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_ATTRIBUTES) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_ATTRIBUTES;
	}

	if( EMS_FILE_NOTIFY_CHANGE_SIZE == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_SIZE) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_SIZE;
	}

	if( EMS_FILE_NOTIFY_CHANGE_LAST_WRITE == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_LAST_WRITE) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_LAST_WRITE;
	}

	if( EMS_FILE_NOTIFY_CHANGE_LAST_ACCESS == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_LAST_ACCESS) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_LAST_ACCESS;
	}

	if( EMS_FILE_NOTIFY_CHANGE_CREATION == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_CREATION) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_CREATION;
	}

	if( EMS_FILE_NOTIFY_CHANGE_SECURITY == (m_ulNotifyFilter & EMS_FILE_NOTIFY_CHANGE_SECURITY) ) 
	{
		ulRet |= FILE_NOTIFY_CHANGE_SECURITY;
	}

#endif
	return ulRet;
}

void 
CEMSDirectoryMonitor::_EnablePrivileges()
{
	LPCTSTR arPrivelegeNames[]	=	{
										SE_BACKUP_NAME, //	these two are required for the FILE_FLAG_BACKUP_SEMANTICS flag used in the call to 
										SE_RESTORE_NAME,//  CreateFile() to open the directory handle for ReadDirectoryChangesW

										SE_CHANGE_NOTIFY_NAME //just to make sure...it's on by default for all users.
										//<others here as needed>
									};
	for(int i = 0; i < sizeof(arPrivelegeNames) / sizeof(arPrivelegeNames[0]); ++i)
	{
		if( !_EnablePrivilege(arPrivelegeNames[i], true) )
		{
//			TRACE(_T("Unable to enable privilege: %s	--	GetLastError(): %d\n"), arPrivelegeNames[i], GetLastError());
//			TRACE(_T("CDirectoryChangeWatcher notifications may not work as intended due to insufficient access rights/process privileges.\n"));
//			TRACE(_T("File: %s Line: %d\n"), _T(__FILE__), __LINE__);
		}
	}
}

bool CEMSDirectoryMonitor::_EnablePrivilege(LPCTSTR pszPrivName, bool bEnable)
//
//	I think this code is from a Jeffrey Richter book...
//
//	Enables user priviledges to be set for this process.
//	
//	Process needs to have access to certain priviledges in order
//	to use the ReadDirectoryChangesW() API.  See documentation.
{    
	bool fOk = false;    
	// Assume function fails    
	HANDLE hToken;    
	// Try to open this process's access token    
	if (OpenProcessToken(GetCurrentProcess(), 		
					TOKEN_ADJUST_PRIVILEGES, &hToken)) 	
	{        
		// privilege        
		TOKEN_PRIVILEGES tp = { 1 };        

		if( LookupPrivilegeValue(NULL, pszPrivName,  &tp.Privileges[0].Luid) )
		{
			tp.Privileges[0].Attributes = bEnable ?  SE_PRIVILEGE_ENABLED : 0;

			AdjustTokenPrivileges(hToken, FALSE, &tp, 			      
									sizeof(tp), NULL, NULL);

			fOk = (GetLastError() == ERROR_SUCCESS);		
		}
		CloseHandle(hToken);	
	}	
	return(fOk);
}

void 
CEMSDirectoryMonitor::_Add( const std::wstring& cowszFileName )
{
	// Filter by file extension?
	bool bUseIt = false;
	if( !m_wszExtension.empty() )
	{
		if( CEMSFileUtility::GetExtension( cowszFileName.c_str() ) == m_wszExtension )
		{
			bUseIt = true;
		}
	}
	if( !m_wszExtension2.empty() )
	{
		if( CEMSFileUtility::GetExtension( cowszFileName.c_str() ) == m_wszExtension2 )
		{
			bUseIt = true;
		}
	}

	if( bUseIt )
	{
		m_queueFileNames.Push( cowszFileName );
		_UpdateLastFileTime();
	}
}


void 
CEMSDirectoryMonitor::_ReleaseResources()
{
	if( INVALID_HANDLE_VALUE != m_hIOCompletionPort )
	{
		CloseHandle( m_hIOCompletionPort );
		m_hIOCompletionPort = NULL;
	}

	m_oDirInfo.Clear();
	m_queueFileNames.Clear();
}

void
CEMSDirectoryMonitor::_UpdateLastFileTime()
{
	m_timeLastFile = CEMSSystemClock::GetTime();
}