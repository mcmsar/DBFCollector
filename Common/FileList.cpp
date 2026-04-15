/********************************************************************
*	Module:			FileList.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
	0.0	2003Oct31		CH		Start

********************************************************************/
#pragma warning(disable:4786)	// Disable warning messages for stl debug symbol size.

#include <windows.h>
#include <stdio.h>
#include <assert.h>

#include "emserror.h"		// EMS_RESULT
#include "emsexcpt.h"
#include "FileList.h"

CEMSFileList::CEMSFileList()
{
}

CEMSFileList::~CEMSFileList()
{
}

void
CEMSFileList::GetFilenames( const char* szPath, FILENAMEVECTOR& vectorFilenames )
{
	int				i = 0;
	unsigned long	ulCount = 0;

	try
	{
		string*			pszFilename = NULL;
		BOOL			bFinished = FALSE;

		HANDLE			hFind;
		WIN32_FIND_DATAA FindFileData;

		hFind = FindFirstFileA( szPath, &FindFileData );
		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			// ignore directory specififiers
			if ( 0 != strcmp( FindFileData.cFileName, "." ) && 
				 0 != strcmp( FindFileData.cFileName, ".." ) )
			{
				// Files found
				pszFilename = new string( FindFileData.cFileName );
				vectorFilenames.push_back( pszFilename );
				pszFilename = NULL;
			}
			while( !bFinished ) 
			{
				if ( !FindNextFileA( hFind, &FindFileData ) )
				{
					if ( GetLastError() == ERROR_NO_MORE_FILES )
					{
						bFinished = TRUE;
					}
					else
					{
						THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
					}
				}
				else if ( 0 != strcmp( FindFileData.cFileName, "." ) && 
						  0 != strcmp( FindFileData.cFileName, ".." ) )
				{
					pszFilename = new string( FindFileData.cFileName );
					vectorFilenames.push_back( pszFilename );
					pszFilename = NULL;
				}
			}
			FindClose(hFind);
		}
	}
	catch( ... )
	{
		// cleanup
		ReleaseFilenames( vectorFilenames );
		throw;
	}
}

void
CEMSFileList::ReleaseFilenames( FILENAMEVECTOR& vectorFilenames )
{
	// cleanup
	for ( int i=0; i<vectorFilenames.size(); i++ )
	{
		delete vectorFilenames[i];
	}
	vectorFilenames.clear();
}

void
CEMSFileList::GetFilenamesW( const wchar_t* wszPath, FILENAMEVECTORW& vectorFilenames )
{
	int				i = 0;
	unsigned long	ulCount = 0;

	try
	{
		wstring*             pszFilename = NULL;
		BOOL                bFinished = FALSE;
		HANDLE              hFind;
		WIN32_FIND_DATAW    FindFileData;

		hFind = FindFirstFileW( wszPath, &FindFileData );
		if ( hFind != INVALID_HANDLE_VALUE ) 
		{
			// ignore directory specififiers
			if ( 0 != wcscmp( FindFileData.cFileName, L"." ) && 
				 0 != wcscmp( FindFileData.cFileName, L".." ) )
			{
				// Files found
				pszFilename = new wstring( FindFileData.cFileName );
				vectorFilenames.push_back( pszFilename );
				pszFilename = NULL;
			}
			while( !bFinished ) 
			{
				if ( !FindNextFileW( hFind, &FindFileData ) )
				{
					if ( GetLastError() == ERROR_NO_MORE_FILES )
					{
						bFinished = TRUE;
					}
					else
					{
						THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
					}
				}
				else if ( 0 != wcscmp( FindFileData.cFileName, L"." ) && 
						  0 != wcscmp( FindFileData.cFileName, L".." ) )
				{
					pszFilename = new wstring( FindFileData.cFileName );
					vectorFilenames.push_back( pszFilename );
					pszFilename = NULL;
				}
			}
			FindClose(hFind);
		}
	}
	catch( ... )
	{
		// cleanup
		ReleaseFilenamesW( vectorFilenames );
		throw;
	}
}


UINT CEMSFileList::CountExtensionFiles(wstring strFile, wstring wildcard)
{
		WIN32_FIND_DATAW	find;
		HANDLE				hFile;
		UINT	nCount = 0;
		try
		{
			if((hFile = FindFirstFileW(strFile.c_str(),&find)) != INVALID_HANDLE_VALUE)
			{				
			   do
			   {
					wstring  fileName = find.cFileName;
					wstring fileExtension =  fileName.substr(fileName.find_last_of(L".") + 1);
					wstring ext = wildcard.substr(wildcard.find_last_of(L".") + 1);
					if (!fileExtension.empty())
					{
						if( fileExtension == ext)
							nCount++;	
					}						  
			   } while( ::FindNextFileW(hFile, &find));
			   FindClose(hFile);		
			}
			else
			{
				//File not found
			}
		}
		catch( ... )
		{
			// cleanup
			FindClose(hFile);			
			throw;
		}
		return nCount;
}

void
CEMSFileList::ReleaseFilenamesW( FILENAMEVECTORW& vectorFilenames )
{
	// cleanup
	for ( int i=0; i<vectorFilenames.size(); i++ )
	{
		delete vectorFilenames[i];
	}
	vectorFilenames.clear();
}