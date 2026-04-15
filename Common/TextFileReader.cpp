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

#include "textfilereader.h"
#include "emsexcpt.h"
#include "convutility.h"

#include <stdio.h>
#include <crtdbg.h>

#ifdef WIN32
#include <windows.h>
#endif

const ULONG culReadBufferSize = 512;

CEMSTextFileReader::CEMSTextFileReader()
{
}

CEMSTextFileReader::CEMSTextFileReader( const CEMSTextFileReader& x )
{
}

CEMSTextFileReader::~CEMSTextFileReader()
{
}

std::wstring 
CEMSTextFileReader::ReadAll( const wchar_t* cwszFileSpec )
{
	_ASSERTE( cwszFileSpec );

	if( !cwszFileSpec )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	std::wstring wszRet;

	FILE* fp = _wfopen( cwszFileSpec, L"rb" );

	if( fp )
	{
		const long clBufSize = 256;
		char szBuf[ clBufSize + 1 ];

		memset( szBuf, 0, (clBufSize+1)*sizeof(char) );

		while( 0 != fread( szBuf, 1, clBufSize, fp ) )
		{
			wszRet.append( CEMSConversionUtil::ConvertToString( szBuf ).c_str() );
			memset( szBuf, 0, (clBufSize+1)*sizeof(char) );
		}

		fclose( fp );
	}

	return wszRet;

}

std::wstring 
CEMSTextFileReader::ReadAllShared( const wchar_t* cwszFileSpec )
{
	std::wstring wszRet;
#ifdef WIN32
	HANDLE hFile = 0;

	try
	{
		hFile = CreateFileW( cwszFileSpec, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0 );

		if( INVALID_HANDLE_VALUE != hFile )
		{
			char szBuffer[culReadBufferSize];

			DWORD dwToRead = culReadBufferSize*sizeof(char);
			DWORD dwNumberRead = 0;

			do
			{
				memset( szBuffer, 0, sizeof(char)*culReadBufferSize );

				BOOL bRet = ReadFile( hFile, (LPVOID) szBuffer, dwToRead, &dwNumberRead, 0 );

				if( !bRet )
				{
					DWORD dwErr = GetLastError();
					THROW_RUNTIME_EXCEPTION( CEMSConversionUtil::ErrnoToEMSResult( dwErr ) );
				}

				if( bRet && (dwNumberRead > 0)  )
				{
					wszRet.append( CEMSConversionUtil::ConvertToString( szBuffer ).c_str() );
				}

			} while( dwNumberRead > 0 );

			CloseHandle( hFile );
		}

	}
	catch( ... )
	{
		if( hFile )
		{
			CloseHandle( hFile );
		}

		throw;
	}
#else
	THROW_RUNTIME_EXCEPTION( EMS_NOTIMPLEMENTED );
#endif

	return wszRet;
}