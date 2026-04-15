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


#ifndef __DIRECTORY_MONITOR_H__
#define __DIRECTORY_MONITOR_H__

#include "emsthread.h"
#include <string>
#include "objectqueue.h"
#include "directoryinfo.h"
#include "emserror.h"

const ULONG EMS_FILE_NOTIFY_CHANGE_FILE_NAME =  0x00000001;
const ULONG EMS_FILE_NOTIFY_CHANGE_DIR_NAME =   0x00000002;
const ULONG EMS_FILE_NOTIFY_CHANGE_ATTRIBUTES = 0x00000004;
const ULONG EMS_FILE_NOTIFY_CHANGE_SIZE =       0x00000008;  
const ULONG EMS_FILE_NOTIFY_CHANGE_LAST_WRITE = 0x00000010;  
const ULONG EMS_FILE_NOTIFY_CHANGE_LAST_ACCESS =0x00000020;  
const ULONG EMS_FILE_NOTIFY_CHANGE_CREATION =   0x00000040;
const ULONG EMS_FILE_NOTIFY_CHANGE_SECURITY =   0x00000100; 

//! @class CEMSDirectoryMonitor
//! Used to monitor a chosen directory for new files.  Whenever a new file
//! is detected, the full path is added to a queue.  The queue can be
//! queried by a consumer/client.  
//! This class is platform dependent (Windows NT 4.0 and greater).
class CEMSDirectoryMonitor : public CEMSThread
{
	public:
		CEMSDirectoryMonitor();
		CEMSDirectoryMonitor( const CEMSDirectoryMonitor& x );
		virtual ~CEMSDirectoryMonitor();

		void Populate();
		void Populate( const ULONG culMaxFiles );
		void PopulateAndStart();
		void StartMonitor();
		void StopMonitor();
		void SetDirectory( const wchar_t* cwszDirectory );
		void SetFileExtension( const wchar_t* cwszFileExtension );
		void SetFileExtension2( const wchar_t* cwszFileExtension2 );
		void SetNotifyFilter( const ULONG culNotifyFilter ) { m_ulNotifyFilter = culNotifyFilter; }
		std::wstring Pop();
		EMS_RESULT GetStatus() { return m_hr; }
		ULONG GetCount();
		EMSTIME GetLastFileReceivedTime();

	protected:
		void run();

		void _SetupCompletionPort();
		void _Monitor();
		void _OnHandleFile( CEMSDirectoryInfo* pDirInfo, PFILE_NOTIFY_INFORMATION pFNI );
		ULONG _GetNotifyFilter();
		void _EnablePrivileges();
		bool _EnablePrivilege(LPCTSTR pszPrivName, bool fEnable = true);
		void _Add( const std::wstring& cowszFileName );
		void _ReleaseResources();
		void _UpdateLastFileTime();

	private:
		CEMSDirectoryInfo m_oDirInfo;
		HANDLE m_hIOCompletionPort;
		CEMSObjectQueue<std::wstring>	m_queueFileNames;
		std::wstring m_wszDirectory;
		std::wstring m_wszExtension;
		std::wstring m_wszExtension2;
		std::wstring m_wszLastFileName;
		ULONG m_ulNotifyFilter;
		CEMSCriticalSection m_cs;
		EMS_RESULT m_hr;
		EMSTIME m_timeLastFile;

};

#endif