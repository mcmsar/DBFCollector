/*SDOC*************************************************************

	$Header$

	Module: DebugWin.h

	Copyright 2001 EMS Technologies, Inc.

	Description: Header file for the CDebugWin class

*************************************************************EDOC*/

/*SDOC*************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	99/05/18		rvw	start

*************************************************************EDOC*/

/*
**
**	 Includes
**
*/
#ifndef INC_DEBUGWIN
#define INC_DEBUGWIN

#include <Windows.h>

#define DEBUGWINCLASSNAME	TEXT("EMS$Debug$Window")
#define DEBUGWINTITLE		TEXT("DebugWin")
#define DEBUGMEMFILENAME	TEXT("EMS$Debug$MemFile")
#define DEBUGMEMSEMAPHORE	TEXT("EMS$Debug$Semaphore")
#define DEBUGMEMSIZE		1024

/*SDOC*************************************************************

	Comments: CDebugWin

*************************************************************EDOC*/
class CDebugWin 
{
public:
	// Constructors/destructors.
	CDebugWin() 
		{ 
			m_hwndDebugWinApp = 0; 

			m_hmemFile = OpenFileMapping(FILE_MAP_WRITE, TRUE, DEBUGMEMFILENAME);

			if (m_hmemFile)
				m_lpmemShared = MapViewOfFile(m_hmemFile, FILE_MAP_WRITE, 0, 0, DEBUGMEMSIZE);

			if (m_lpmemShared)
				m_hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, DEBUGMEMSEMAPHORE);

			FindApp();
		}

	~CDebugWin()
	{ 
		if (m_lpmemShared)
		{
			UnmapViewOfFile(m_lpmemShared);
			m_lpmemShared = 0;
		}

		if (m_hmemFile)
		{
			CloseHandle(m_hmemFile);
			m_hmemFile = 0;
		}

		if (m_hSemaphore)
		{
			CloseHandle(m_hSemaphore);
			m_hSemaphore = 0;
		}
	}

	void OutputMsg(LPVOID lpMsg)
	{
		if (lpMsg && m_lpmemShared && FindApp())
		{
			INT nLength = sizeof(TCHAR) * (lstrlen((LPCTSTR)lpMsg) + 1);

			Lock();

			memcpy(m_lpmemShared, lpMsg, nLength);

			SendMessage(m_hwndDebugWinApp, WM_USER, 0, (LPARAM)lpMsg);

			Unlock();
		}
	}

private: // methods
	BOOL Lock(void)
	{
		return (WaitForSingleObject(m_hSemaphore, INFINITE) == WAIT_OBJECT_0);
	}

	void Unlock(void)
	{
		ReleaseSemaphore(m_hSemaphore, 1, NULL);
	}

	BOOL FindApp(void)
	{
		if (!m_hwndDebugWinApp || !IsWindow(m_hwndDebugWinApp))
			m_hwndDebugWinApp = FindWindow(DEBUGWINCLASSNAME, DEBUGWINTITLE);

		return (m_hwndDebugWinApp != 0);
	}

private:	// data
	HWND m_hwndDebugWinApp;
	HANDLE m_hmemFile;
	LPVOID m_lpmemShared;
	HANDLE m_hSemaphore;
};

typedef CDebugWin *LPCDebugWin;

#endif //INC_DEBUGWIN



