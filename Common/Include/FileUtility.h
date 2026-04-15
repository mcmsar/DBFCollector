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

#ifndef __FILE_UTILITY_H__
#define __FILE_UTILITY_H__

#include <wchar.h>
#include <string>
#include "emstime.h"

class CEMSFileUtility
{
	public:
		CEMSFileUtility();
		CEMSFileUtility( const CEMSFileUtility& x );
		~CEMSFileUtility();
		
		static std::wstring MoveFileToDirectory( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory, const bool cbHandleIfExists = false );
		static std::wstring CopyFileToDirectory( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory, const bool cbOverWrite = true );
		static std::wstring CopyFileToDirectoryEx( const wchar_t* cwszFilePath, const wchar_t* cwszDirectory);
		static std::wstring RenameFile( const wchar_t* cwszSource, const wchar_t* cwszDest, const bool cbHandleIfExists = false		 );
		static std::wstring GetFileName( const wchar_t* cwszFileSpec );
		static std::wstring GetFullFileName( const wchar_t* cwszFileSpec );
		static bool DoesFileExist( const wchar_t* cwszFileSpec );
		static bool Delete( const wchar_t* cwszFileSpec );
		static std::wstring ModifyExtension( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt );
		static EMSTIME GetCreationTime( const wchar_t* cwszFileSpec );
		static std::wstring GetDirectoryName( const wchar_t* cwszDirPath );

		//! Given a file path, return just the drive and path.
		static std::wstring GetPath( const wchar_t* cwszFilePath );

		static std::wstring ChangeExtension( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt );

		static std::wstring ChangeExtensionEx( const wchar_t* cwszFileSpec, const wchar_t* cwszNewExt );

		static std::wstring GetExtension( const wchar_t* cwszFileSpec );

		static std::wstring Copy( const wchar_t* cwszSrc, const wchar_t* cwszDest, const bool cbRenameIfNecessary = false ); 

		//! Creates the last directory in the given path.  It does not create the intermediate directories.
		static void CreateDir( const wchar_t* cwszDirPath );

		//! Creates an entire directory path.
		static void CreateDirEx( const wchar_t* cwszDirPath );

		//! Changes the "filename" portion of the input fully qualified file name.
		//! E.g., Original=c:\folder1\folder2\afile.txt can be changed to
		//! c:\folder1\folder2\newfilename.txt.
		static std::wstring ChangeFileName( const wchar_t* cwszOrigPath, const wchar_t* cwszNewName, const bool cbHandleIfExists=false );

	public:
		static const ULONG ms_culMaxRenameAttempts;
};

#endif // __FILE_UTILITY_H__