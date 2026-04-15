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

#include "fileutility.h"

#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include "emsexcpt.h"
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

const wchar_t cwszTrailingBackslash[] = L"\\";

const ULONG CEMSFileUtility::ms_culMaxRenameAttempts = 1000;

CEMSFileUtility::CEMSFileUtility()
{
}

CEMSFileUtility::CEMSFileUtility( const CEMSFileUtility& x )
{
}

CEMSFileUtility::~CEMSFileUtility()
{
}

std::wstring 
CEMSFileUtility::MoveFileToDirectory( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory, const bool cbHandleIfExists )
{
	std::wstring owszRet;

	if( cwszFilePath && cwszDirectory )
	{
		wchar_t wszDrive[ _MAX_DRIVE ];
		wchar_t wszDir[ _MAX_DIR ];
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];

		_wsplitpath( cwszFilePath, wszDrive, wszDir, wszFilename, wszExt );

		// Sometimes destination directories are not specified with a trailing backslash
		// _wsplitpath will truncate the directory element at the last backslash.  So, add if missing.
		std::wstring wszTempDir( cwszDirectory ); 

		if( L'\\' != cwszDirectory[ wcslen(cwszDirectory) - 1 ] )
		{
			wszTempDir.append( cwszTrailingBackslash );
		}

		// In case the directory input is a full path, including drive letter.
		wchar_t wszDestDir[ _MAX_DIR ];
		_wsplitpath( wszTempDir.c_str(), 0, wszDestDir, 0, 0 );

		wchar_t wszNewFilePath[ _MAX_PATH ];
		_wmakepath( wszNewFilePath, wszDrive, wszDestDir, wszFilename, wszExt );

		if( wcslen( wszNewFilePath ) > 0 )
		{
#ifdef WIN32
			int iAttempts = 0;

			owszRet = wszNewFilePath;
			BOOL bResult = TRUE;

			while( !( bResult = MoveFileW( cwszFilePath, owszRet.c_str() ) ) &&
					iAttempts < ms_culMaxRenameAttempts )
			{
				iAttempts++;

				DWORD dwErr = GetLastError();

				if( ( ERROR_FILE_EXISTS == dwErr ||
					ERROR_ALREADY_EXISTS == dwErr ) &&
					cbHandleIfExists )
				{
					std::wstringstream owstrmNew;
					owstrmNew << GetPath( wszNewFilePath ).c_str() <<
								L"\\" <<
								GetFileName( wszNewFilePath ).c_str() <<
								L"_" <<
								iAttempts <<
								GetExtension( wszNewFilePath );

					owszRet = owstrmNew.str();
				}
				else
				{
					HRESULT hr = HRESULT_FROM_WIN32( dwErr );

					THROW_RUNTIME_EXCEPTION( hr );
				}
			}

			if( !bResult )
			{
				HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

				THROW_RUNTIME_EXCEPTION( hr );
			}
#endif
		}

		
	}

	return owszRet;
}

std::wstring 
CEMSFileUtility::CopyFileToDirectory( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory, 
										const bool cbOverWrite )
{
	std::wstring wszRet;

	if( cwszFilePath && cwszDirectory )
	{
		wchar_t wszDrive[ _MAX_DRIVE ];
		wchar_t wszDir[ _MAX_DIR ];
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];

		_wsplitpath( cwszFilePath, wszDrive, wszDir, wszFilename, wszExt );

		// Sometimes destination directories are not specified with a trailing backslash
		// _wsplitpath will truncate the directory element at the last backslash.  So, add if missing.
		std::wstring wszTempDir( cwszDirectory ); 

		if( L'\\' != cwszDirectory[ wcslen(cwszDirectory) - 1 ] )
		{
			wszTempDir.append( cwszTrailingBackslash );
		}

		// In case the directory input is a full path, including drive letter.
		wchar_t wszDestDir[ _MAX_DIR ];
		_wsplitpath( wszTempDir.c_str(), wszDrive, wszDestDir, 0, 0 );

		wchar_t wszNewFilePath[ _MAX_PATH ];
		_wmakepath( wszNewFilePath, wszDrive, wszDestDir, wszFilename, wszExt );

		if( wcslen( wszNewFilePath ) > 0 )
		{
#ifdef WIN32
			if( !CopyFileW( cwszFilePath, wszNewFilePath, true == cbOverWrite ? TRUE : FALSE  ) )
			{
				HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

				THROW_RUNTIME_EXCEPTION( hr );
			}
			else
			{
				wszRet = wszNewFilePath;
			}
#endif
		}
	}

	return wszRet;
}

std::wstring 
CEMSFileUtility::CopyFileToDirectoryEx( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory)
{
	std::wstring owszRet;

	if( cwszFilePath && cwszDirectory )
	{
		wchar_t wszDrive[ _MAX_DRIVE ];
		wchar_t wszDir[ _MAX_DIR ];
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];

		_wsplitpath( cwszFilePath, wszDrive, wszDir, wszFilename, wszExt );

		// Sometimes destination directories are not specified with a trailing backslash
		// _wsplitpath will truncate the directory element at the last backslash.  So, add if missing.
		std::wstring wszTempDir( cwszDirectory ); 

		if( L'\\' != cwszDirectory[ wcslen(cwszDirectory) - 1 ] )
		{
			wszTempDir.append( cwszTrailingBackslash );
		}

		// In case the directory input is a full path, including drive letter.
		wchar_t wszDestDir[ _MAX_DIR ];
		_wsplitpath( wszTempDir.c_str(), wszDrive, wszDestDir, 0, 0 );

		wchar_t wszNewFilePath[ _MAX_PATH ];
		_wmakepath( wszNewFilePath, wszDrive, wszDestDir, wszFilename, wszExt );

		if( wcslen( wszNewFilePath ) > 0 )
		{
#ifdef WIN32
			int iAttempts = 0;

			owszRet = wszNewFilePath;
			BOOL bResult = TRUE;

			while( !( bResult = CopyFileW( cwszFilePath, wszNewFilePath, FALSE ) ) &&
					iAttempts < ms_culMaxRenameAttempts )
			{
				iAttempts++;

				DWORD dwErr = GetLastError();

				if( ( ERROR_FILE_EXISTS == dwErr ||
					ERROR_ALREADY_EXISTS == dwErr )  )
				{
					std::wstringstream owstrmNew;
					owstrmNew << GetPath( wszNewFilePath ).c_str() <<
								L"\\" <<
								GetFileName( wszNewFilePath ).c_str() <<
								L"_" <<
								iAttempts <<
								GetExtension( wszNewFilePath );

					owszRet = owstrmNew.str();
				}
				else
				{
					HRESULT hr = HRESULT_FROM_WIN32( dwErr );

					THROW_RUNTIME_EXCEPTION( hr );
				}
			}

			if( !bResult )
			{
				HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

				THROW_RUNTIME_EXCEPTION( hr );
			}
#endif
		}
	}

	return owszRet;
}

std::wstring
CEMSFileUtility::RenameFile( const wchar_t* cwszSource, const wchar_t* cwszDest, const bool cbHandleIfExists  )
{
	std::wstring owszRet;

	if( cwszSource && cwszDest )
	{
#ifdef WIN32
		int iAttempts = 0;

		owszRet = cwszDest;
		BOOL bResult = TRUE;

		while( !( bResult = MoveFileW( cwszSource, owszRet.c_str() ) ) &&
				iAttempts < ms_culMaxRenameAttempts )
		{
			iAttempts++;

			DWORD dwErr = GetLastError();

			if( ( ERROR_FILE_EXISTS == dwErr ||
				ERROR_ALREADY_EXISTS == dwErr ) &&
				cbHandleIfExists )
			{
				std::wstringstream owstrmNew;
				owstrmNew << GetPath( cwszDest ).c_str() <<
							L"\\" <<
							GetFileName( cwszDest ).c_str() <<
							L"_" <<
							iAttempts <<
							GetExtension( cwszDest );

				owszRet = owstrmNew.str();
			}
			else
			{
				HRESULT hr = HRESULT_FROM_WIN32( dwErr );

				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

		if( !bResult )
		{
			HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

			THROW_RUNTIME_EXCEPTION( hr );
		}
#endif
	}

	return owszRet;
}

std::wstring 
CEMSFileUtility::GetFileName( const wchar_t* cwszFileSpec )
{
	std::wstring wszRet;

	if( cwszFileSpec )
	{
		wchar_t wszFilename[ _MAX_FNAME ];
		_wsplitpath( cwszFileSpec, 0, 0, wszFilename, 0 );

		wszRet = wszFilename;
	}

	return wszRet;
}

std::wstring 
CEMSFileUtility::GetFullFileName( const wchar_t* cwszFileSpec )
{
	std::wstring wszRet;

	if( cwszFileSpec )
	{
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];
		_wsplitpath( cwszFileSpec, 0, 0, wszFilename, wszExt );

		wszRet = wszFilename;
		wszRet.append( wszExt );
	}

	return wszRet;
}

bool 
CEMSFileUtility::DoesFileExist( const wchar_t* cwszFileSpec )
{
	bool bRet = false;

	if( cwszFileSpec )
	{
		struct _stat bufStat;

		int iResult = _wstat( cwszFileSpec, &bufStat );

		if( 0 == iResult )
			bRet = true;

	}

	return bRet;
}

bool
CEMSFileUtility::Delete( const wchar_t* cwszFileSpec )
{
	bool bRet = false;

	if( cwszFileSpec )
	{
		int iRet = _wunlink( cwszFileSpec );

		if( 0 == iRet )
			bRet = true;
	}

	return bRet;
}

std::wstring 
CEMSFileUtility::ModifyExtension( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt )
{
	std::wstring wszRet;

	if( cwszFileSpec && cwszNewExt )
	{
		wchar_t wszDrive[ _MAX_DRIVE ];
		wchar_t wszDir[ _MAX_DIR ];
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];

		_wsplitpath( cwszFileSpec, wszDrive, wszDir, wszFilename, wszExt );

		wchar_t wszNewFilePath[ _MAX_PATH ];
		_wmakepath( wszNewFilePath, wszDrive, wszDir, wszFilename, cwszNewExt );

		wszRet = wszNewFilePath;
	}

	return wszRet;
}

EMSTIME 
CEMSFileUtility::GetCreationTime( const wchar_t* cwszFileSpec )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	if( cwszFileSpec )
	{
	
		struct _stat bufStat;

		int iResult = _wstat( cwszFileSpec, &bufStat );

		if( 0 == iResult )
		{
			CEMSTime oTimeCreation;
			
			oTimeCreation.SetTime( bufStat.st_ctime );

			timeRet = oTimeCreation;
		}

	}
/*		HANDLE hFile = 0;

#ifdef WIN32
		try
		{
			hFile = CreateFileW( cwszFileSpec, GENERIC_READ, FILE_SHARE_READ, 0, 
										OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );
			
			if( hFile )
			{
				FILETIME ftLastModified;
				memset( &ftLastModified, 0, sizeof(FILETIME) );

				ULARGE_INTEGER uliValue;
				memset( &uliValue, 0, sizeof(ULARGE_INTEGER) );

				if( GetFileTime( hFile, 0, 0, &ftLastModified ) )
				{
					// According to Platform SDK, FILETIME is two DWORDS and can be copied into
					// a ULARGE_INTEGER (from which the QuadPart member can be taken as it's an __int64.
					if( sizeof(FILETIME) <= sizeof(ULARGE_INTEGER) )
					{
						memcpy( &uliValue, &ftLastModified, sizeof(FILETIME) );

						timeRet.intTime = uliValue.QuadPart;
					}
					else
					{
						THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
					}
				}

				CloseHandle( hFile );
				hFile = 0;
			}
		}
		catch( ... )
		{
			if( hFile )
			{
				CloseHandle( hFile );
				hFile = 0;
			}

			throw;
		}
#endif
	}
*/
	return timeRet;
}

std::wstring
CEMSFileUtility::GetDirectoryName( const wchar_t* cwszDirPath )
{
	// Want just the directory name, not its full qualified name.

	std::wstring wszRet;

	if( cwszDirPath )
	{
		try
		{
			// Assuming no trailing "\"
			wchar_t wszDir[ _MAX_DIR ];
			wchar_t wszFilename[ _MAX_FNAME ];

			_wsplitpath( cwszDirPath, 0, wszDir, wszFilename, 0 );

			wszRet = wszFilename;

		}
		catch( ... )
		{
			throw;
		}
	}

	return wszRet;
}

std::wstring 
CEMSFileUtility::GetPath( const wchar_t* cwszFilePath )
{
	std::wstring wszRet;

	if( cwszFilePath )
	{
		try
		{
			wchar_t wszDrive[ _MAX_DRIVE ];
			wchar_t wszDir[ _MAX_DIR ];

			_wsplitpath( cwszFilePath, wszDrive, wszDir, 0, 0 );

			wchar_t wszNewFilePath[ _MAX_PATH ];
			_wmakepath( wszNewFilePath, wszDrive, wszDir, 0, 0 );

			wszRet = wszNewFilePath;

		}
		catch( ... )
		{
			throw;
		}
	}

	return wszRet;
}

std::wstring
CEMSFileUtility::ChangeExtension( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt )
{
	std::wstring owszNewFileName = ModifyExtension( cwszFileSpec, cwszNewExt );

	RenameFile( cwszFileSpec, owszNewFileName.c_str() );

	return owszNewFileName;
}

std::wstring 
CEMSFileUtility::ChangeExtensionEx( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt )
{
	std::wstring owszNewFileName = ModifyExtension( cwszFileSpec, cwszNewExt );

	owszNewFileName = RenameFile( cwszFileSpec, owszNewFileName.c_str(), true );

	return owszNewFileName;
}

std::wstring 
CEMSFileUtility::GetExtension( const wchar_t* cwszFileSpec )
{
	std::wstring wszRet;

	if( cwszFileSpec )
	{
		wchar_t wszExt[ _MAX_EXT ];
		_wsplitpath( cwszFileSpec, 0, 0, 0, wszExt );
		wszRet = wszExt;
	}

	return wszRet;
}

std::wstring
CEMSFileUtility::Copy( const wchar_t* cwszSource, const wchar_t* cwszDest, 
						  const bool cbRenameIfNecessary )
{
	std::wstring owszRet;

	if( cwszSource && cwszDest )
	{
#ifdef WIN32
		int iAttempts = 0;

		owszRet = cwszDest;
		BOOL bResult = TRUE;

		while( !( bResult = CopyFileW( cwszSource, owszRet.c_str(), TRUE )  ) &&
				iAttempts < ms_culMaxRenameAttempts )
		{
			iAttempts++;

			DWORD dwErr = GetLastError();

			if( ( ERROR_FILE_EXISTS == dwErr ||
				ERROR_ALREADY_EXISTS == dwErr ) &&
				cbRenameIfNecessary )
			{
				std::wstringstream owstrmNew;
				owstrmNew << GetPath( cwszDest ).c_str() <<
							L"\\" <<
							GetFileName( cwszDest ).c_str() <<
							L"_" <<
							iAttempts <<
							GetExtension( cwszDest );

				owszRet = owstrmNew.str();
			}
			else
			{
				HRESULT hr = HRESULT_FROM_WIN32( dwErr );

				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

		if( !bResult )
		{
			HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

			THROW_RUNTIME_EXCEPTION( hr );
		}
#endif
	}

	return owszRet;
}

void 
CEMSFileUtility::CreateDir( const wchar_t* cwszDirPath )
{
	if( cwszDirPath )
	{
		BOOL bRet = CreateDirectoryW( cwszDirPath, NULL );

		if( !bRet )
		{
			DWORD dwErr = GetLastError();

			if( ERROR_FILE_EXISTS != dwErr &&
				ERROR_ALREADY_EXISTS != dwErr )
			{
				EMS_RESULT hr = HRESULT_FROM_WIN32( dwErr );

				THROW_RUNTIME_EXCEPTION( hr );
			}
		}
	}
}

void 
CEMSFileUtility::CreateDirEx( const wchar_t* cwszDirPath )
{
	if( cwszDirPath )
	{
		wchar_t wszPath[ _MAX_PATH ];
		wcscpy( wszPath, cwszDirPath );

		wchar_t* wszTok = wcstok( wszPath, L"\\/" );

		std::wstring owszCurrent;

		while( wszTok )
		{
			if( owszCurrent.length() > 0 )
				owszCurrent.append( L"\\");

			owszCurrent.append( wszTok );

			
			BOOL bRet = CreateDirectoryW( owszCurrent.c_str(), NULL );

			if( !bRet )
			{
				DWORD dwErr = GetLastError();

				if( ERROR_FILE_EXISTS != dwErr &&
					ERROR_ALREADY_EXISTS != dwErr )
				{
					EMS_RESULT hr = HRESULT_FROM_WIN32( dwErr );

					THROW_RUNTIME_EXCEPTION( hr );
				}
			}

			wszTok = wcstok( NULL, L"\\/" );
		}
	}
}

std::wstring 
CEMSFileUtility::ChangeFileName( const wchar_t* cwszFilePath, const wchar_t* cwszNewName, 
								const bool cbHandleIfExists )
{
	std::wstring owszRet;

	if( cwszFilePath && cwszNewName )
	{
		wchar_t wszDrive[ _MAX_DRIVE ];
		wchar_t wszDir[ _MAX_DIR ];
		wchar_t wszFilename[ _MAX_FNAME ];
		wchar_t wszExt[ _MAX_EXT ];

		_wsplitpath( cwszFilePath, wszDrive, wszDir, wszFilename, wszExt );

		wchar_t wszNewFilePath[ _MAX_PATH ];
		_wmakepath( wszNewFilePath, wszDrive, wszDir, cwszNewName, wszExt );

		if( wcslen( wszNewFilePath ) > 0 )
		{
#ifdef WIN32
			int iAttempts = 0;

			owszRet = wszNewFilePath;
			BOOL bResult = TRUE;

			while( !( bResult = MoveFileW( cwszFilePath, owszRet.c_str() ) ) &&
					iAttempts < ms_culMaxRenameAttempts )
			{
				iAttempts++;

				DWORD dwErr = GetLastError();

				if( ( ERROR_FILE_EXISTS == dwErr ||
					ERROR_ALREADY_EXISTS == dwErr ) &&
					cbHandleIfExists )
				{
					std::wstringstream owstrmNew;
					owstrmNew << GetPath( wszNewFilePath ).c_str() <<
								L"\\" <<
								GetFileName( wszNewFilePath ).c_str() <<
								L"_" <<
								iAttempts <<
								GetExtension( wszNewFilePath );

					owszRet = owstrmNew.str();
				}
				else
				{
					HRESULT hr = HRESULT_FROM_WIN32( dwErr );

					THROW_RUNTIME_EXCEPTION( hr );
				}
			}

			if( !bResult )
			{
				HRESULT hr = HRESULT_FROM_WIN32( GetLastError() );

				THROW_RUNTIME_EXCEPTION( hr );
			}
#endif
		}

		
	}

	return owszRet;
}