/****************************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
****************************************************************************/

/****************************************************************************

  Revision Record

	$Log:
	$
****************************************************************************/
#pragma warning(disable:4786)

#include "directoryutility.h"
#include "fileutility.h"
#include "directorymonitor.h"
#include "emsexcpt.h"

CEMSDirectoryUtility::CEMSDirectoryUtility()
{
}

CEMSDirectoryUtility::CEMSDirectoryUtility( const CEMSDirectoryUtility& x )
{
}

CEMSDirectoryUtility::~CEMSDirectoryUtility()
{
}

bool 
CEMSDirectoryUtility::Copy( const wchar_t* cwszSrc, const wchar_t* cwszDest )
{
	bool bRet = false;

	if( cwszSrc && cwszDest )
	{
		// Does the src exist?
		struct _stat strDirInfo;
		if( 0 == _wstat( cwszSrc, &strDirInfo ) )
		{
			// Does the dest exist?
			if( 0 != _wstat( cwszDest, &strDirInfo ) )
			{
				CreateDirPath( cwszDest );
			}

			CEMSDirectoryMonitor oDirMon;
			oDirMon.SetDirectory( cwszSrc );
			oDirMon.Populate();

			std::wstring owszFile;

			while( !( owszFile = oDirMon.Pop()).empty() )
			{
				CEMSFileUtility::CopyFileToDirectory( owszFile.c_str(), cwszDest );
			}

			bRet = true;
		}
	}

	return bRet;
}

void 
CEMSDirectoryUtility::CreateDirPath( const wchar_t* cwszDirPath )
{
	if( cwszDirPath )
	{
		std::wstring owszPath( cwszDirPath );

		// Make sure there is a drive letter and root directory.
		std::wstring::size_type iPos = owszPath.find( L":\\" );

		if( std::wstring::npos == iPos )
		{
			THROW_INVALID_ARG_EXCEPTION( );
		}

		bool bContinue = true;

		std::wstring::size_type iStartPos = owszPath.find( L"\\");

		while( bContinue )
		{
			// directory name is delimited by another \ or the end of the string.
			std::wstring::size_type iNextPos = owszPath.find( L"\\", iStartPos + 1 );

			if( std::wstring::npos == iNextPos )
			{
				iNextPos = owszPath.length();
				bContinue = false;
			}
			else
				iStartPos = iNextPos;

			std::wstring owszBranch = owszPath.substr( 0, iNextPos );

			BOOL bRet = CreateDirectoryW( owszBranch.c_str(), NULL );

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
}

bool 
CEMSDirectoryUtility::Delete( const wchar_t* cwszDir )
{
	bool bRet = false;

	if( cwszDir )
	{
		// Does the src exist?
		struct _stat strDirInfo;
		if( 0 == _wstat( cwszDir, &strDirInfo ) )
		{
			CEMSDirectoryMonitor oDirMon;
			oDirMon.SetDirectory( cwszDir );
			oDirMon.Populate();

			std::wstring owszFile;

			while( !( owszFile = oDirMon.Pop()).empty() )
			{
				CEMSFileUtility::Delete( owszFile.c_str() );
			}

			if( 0 !=  _wrmdir( cwszDir ) )
			{
				switch( errno )
				{
					case ENOTEMPTY:
						THROW_RUNTIME_EXCEPTION( EMS_DIRECTORY_NOT_EMPTY );
						break;
					case ENOENT:
						THROW_RUNTIME_EXCEPTION( EMS_PATH_NOT_FOUND );
						break;
					default:
						THROW_RUNTIME_EXCEPTION( EMS_UNKNOWN_ERROR );

				}
			}
			else
				bRet = true;

		}
		else
			bRet = true;	// good as deleted.
	}

	return bRet;
}