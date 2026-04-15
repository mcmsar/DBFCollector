/********************************************************************
*	Module:			EMSFStrm.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
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

	0.0	2001/07/30 		rvw		start
		2003/10/22		jb		Added support of the IEMSRandomStream interface.
		2003/11/07		ch		Allow Move(index) if index matches the end of file
								Support open of an existing file for edit (previously 
								choices were read-existing OR write-new)
********************************************************************/
#include <stdio.h>

#include "emsfstrm.h"
#include "emserror.h"
#include "convutility.h"

CEMSFileStream::CEMSFileStream( ) : CApiObjBase("CEMSFileStream")
{
	m_lpFile = 0;
}

CEMSFileStream::~CEMSFileStream() 
{
	if ( m_lpFile )
	{
		fclose( (FILE*)m_lpFile );
		m_lpFile = 0;
	}
}

EMS_RESULT CEMSFileStream::OpenFile(	LPCTSTR	lpcszFile, 
										BOOL	bWriteable, 
										BOOL	bAppend,
										BOOL	bAllowEdit )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_lpFile )
	{
		if ( lpcszFile && *lpcszFile )
		{
			const char *lpszMode = 0;
			const char *lpszRetry = 0;

			// Open Binary file
			if ( !bWriteable )
			{
				// read-only
				lpszMode = "rb";
			}
			else if ( bWriteable )
			{
				if ( bAppend )
				{
					// read entire file but write allowed only to the end of the file
					lpszMode = "a+b";
				}
				else if ( bAllowEdit )
				{
					// open for read/write
					lpszMode = "r+b";
					// open empty file for read/write 
					// (don't want to fail if file doesn't exist yet)
					lpszRetry = "w+b";
				}
				else
				{
					// open empty file for read/write 
					// (will erase existing file)
					lpszMode = "w+b";
				}
			}

			m_lpFile = (LPVOID)fopen( lpcszFile, lpszMode );
			if ( !m_lpFile && lpszRetry )
			{
				m_lpFile = (LPVOID)fopen( lpcszFile, lpszRetry );
			}
			if ( !m_lpFile )
			{
				hr = _GetErrorCode();
				// Sometimes there is no error code
				// so make sure that a null file handle 
				// *IS* reported as an error
				if ( EMS_OK == hr )
				{
					hr = EMS_IO_ERROR;
				}
			}
		}
		else
			hr = EMS_INVALID_FILESPEC;
	}
	else
		hr = EMS_ALREADY_OPEN;

	return hr;
}

EMS_RESULT CEMSFileStream::CloseFile( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpFile )
	{
		fclose( (FILE*)m_lpFile );
		m_lpFile = 0;
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

STDMETHODIMP_(ULONG) CEMSFileStream::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSFileStream::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSFileStream::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT result = EMS_NOINTERFACE;
	LPUNKNOWN lpUnknown = 0;

	if (lppObj)
		*lppObj = lpUnknown;

	if (IsEqualIID(riid, IID_IEMSSeqStream))
	{
		lpUnknown = (LPUNKNOWN)(LPEMSSEQSTREAM)this;
	}
	else if (IsEqualIID(riid, IID_IUnknown))
	{
		lpUnknown = (LPUNKNOWN)this;
	}
	else if(IsEqualIID(riid, IID_IEMSRandomStream))
	{
		lpUnknown = (LPUNKNOWN)(LPEMSRANDOMSTREAM)this;
	}

	if (lpUnknown)
	{
		if (lppObj)
		{
			*lppObj = lpUnknown;

			lpUnknown->AddRef();
		}

		result = EMS_OK;
	}

	return result;
}

STDMETHODIMP CEMSFileStream::Read( BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbRead )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesRead = 0;

	if ( m_lpFile )
	{
		ulBytesRead = (ULONG)fread( pv, 1, cb, (FILE*)m_lpFile );

		if ( ulBytesRead == 0 )
			hr = EMS_EOF;
	}
	else
		hr = EMS_NOT_OPEN;

	if ( pcbRead )
		*pcbRead = ulBytesRead;

	return hr;
}
        
STDMETHODIMP CEMSFileStream::Write( const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesWritten = 0;

	if ( m_lpFile )
	{
		ulBytesWritten = (ULONG)fwrite( pv, 1, cb, (FILE*)m_lpFile );

		if ( ulBytesWritten != cb )
			hr = _GetErrorCode();
	}
	else
		hr = EMS_NOT_OPEN;

	if ( pcbWritten )
		*pcbWritten = ulBytesWritten;

	return hr;
}

STDMETHODIMP CEMSFileStream::MoveFirst( void)
{
	EMS_RESULT hr = EMS_OK;

	if( m_lpFile )
	{
		int iRet = fseek( (FILE*) m_lpFile, 0, SEEK_SET );

		if( 0 != iRet )
		{
			hr = EMS_IO_ERROR;
		}
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

STDMETHODIMP CEMSFileStream::MoveLast( void)
{
	EMS_RESULT hr = EMS_OK;

	if( m_lpFile )
	{
		int iRet = fseek( (FILE*) m_lpFile, 0, SEEK_END);

		if( 0 != iRet )
		{
			hr = EMS_IO_ERROR;
		}
	}
	else
	{
		hr = EMS_NOT_OPEN;
	}

	return hr;
}

STDMETHODIMP CEMSFileStream::Move( /* [in] */ const long clIndex )
{
	EMS_RESULT hr = EMS_OK;

	if( m_lpFile )
	{
		// First find out where the end is.
		int iRet = fseek( (FILE*) m_lpFile, 0, SEEK_END);

		if( 0 != iRet )
		{
			hr = EMS_IO_ERROR;
		}

		if( SUCCEEDED(hr) )
		{
			long lCurrent = ftell( (FILE*) m_lpFile );

			if( clIndex < lCurrent )
			{
				int iRet = fseek( (FILE*) m_lpFile, clIndex, SEEK_SET);

				if( 0 != iRet )
				{
					hr = EMS_IO_ERROR;
				}
			}
			else if ( clIndex != lCurrent )
			{
				hr = EMS_IO_ERROR;
			}
		}
	}
	else
	{
		hr = EMS_NOT_OPEN;
	}

	return hr;
}

EMS_RESULT CEMSFileStream::OpenFileW( const wchar_t* cwszFile, BOOL	bWriteable, 
									 BOOL bAppend, BOOL bAllowEdit )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_lpFile )
	{
		if ( cwszFile && *cwszFile )
		{
			const wchar_t *lpszMode = 0;
			const wchar_t *lpszRetry = 0;

			// Open Binary file
			if ( !bWriteable )
			{
				// read-only
				lpszMode = L"rb";
			}
			else if ( bWriteable )
			{
				if ( bAppend )
				{
					// read entire file but write allowed only to the end of the file
					lpszMode = L"a+b";
				}
				else if ( bAllowEdit )
				{
					// open for read/write
					lpszMode = L"r+b";
					// open empty file for read/write 
					// (don't want to fail if file doesn't exist yet)
					lpszRetry = L"w+b";
				}
				else
				{
					// open empty file for read/write 
					// (will erase existing file)
					lpszMode = L"w+b";
				}
			}

			m_lpFile = (LPVOID)_wfopen( cwszFile, lpszMode );
			if ( !m_lpFile && lpszRetry )
			{
				m_lpFile = (LPVOID)_wfopen( cwszFile, lpszRetry );
			}
			if ( !m_lpFile )
			{
				hr = _GetErrorCode();
				// Sometimes there is no error code
				// so make sure that a null file handle 
				// *IS* reported as an error
				if ( EMS_OK == hr )
				{
					hr = EMS_IO_ERROR;
				}
			}
		}
		else
			hr = EMS_INVALID_FILESPEC;
	}
	else
		hr = EMS_ALREADY_OPEN;

	return hr;
}

EMS_RESULT CEMSFileStream::Flush()
{
	if( m_lpFile )
	{
		fflush( (FILE*) m_lpFile );
	}

	return EMS_OK;
}

EMS_RESULT CEMSFileStream::_GetErrorCode()
{
	return CEMSConversionUtil::ErrnoToEMSResult( errno );
}
