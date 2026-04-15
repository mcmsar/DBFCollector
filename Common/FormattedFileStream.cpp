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

#define INITGUID
#include <initguid.h>

#include "formattedfilestream.h"
#include "convutility.h"
#include "emsexcpt.h"
#include <stdarg.h>
#include <crtdbg.h>

const wchar_t* cwszCRLF = L"\n";

CEMSFormattedFileStream::CEMSFormattedFileStream() : m_fpStream(0), m_eMode( FMT_STREAM_OMODE_APPEND )
{
}

CEMSFormattedFileStream::CEMSFormattedFileStream( const CEMSFormattedFileStream& x ) : m_wszFileSpec( x.m_wszFileSpec ),
																					m_fpStream(0), m_eMode( x.m_eMode )
{
}

CEMSFormattedFileStream::~CEMSFormattedFileStream()
{
	Close();
}

int 
CEMSFormattedFileStream::Write( const wchar_t* cwszFormat, ... )
{
	int iRet = 0;

	va_list params;
	va_start( params, cwszFormat );

	if( cwszFormat )
	{
		vwprintf( cwszFormat, params );

		_Init();

		_ASSERTE( m_fpStream );

		if( !m_fpStream )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		iRet = vfwprintf( m_fpStream, cwszFormat, params );
		fflush( m_fpStream );
	}

	return iRet;
}

int 
CEMSFormattedFileStream::WriteA( const BYTE* cabyData, const ULONG culBytes )
{
	int iRet = 0;

	char* szData = 0;

	try
	{
		_Init();

		_ASSERTE( m_fpStream );

		if( !m_fpStream )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		szData = new char[ culBytes + 1 ];

		if( !szData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( szData, 0, (culBytes+1)*sizeof(char) );
		memcpy( szData, cabyData, culBytes*sizeof(char) );

		iRet = fprintf( m_fpStream, "%s", szData );

		delete[] szData;
		szData = 0;
	}
	catch( ... )
	{
		if( szData )
		{
			delete[] szData;
			szData = 0;
		}

		throw;
	}

	return iRet;
}

int 
CEMSFormattedFileStream::WriteBinary( const wchar_t* cwszData )
{
	int iRet = 0;

	if( cwszData && wcslen(cwszData) > 0 )
	{
		_Init();

		_ASSERTE( m_fpStream );

		if( !m_fpStream )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		// First things first.  The stream must be converted to multibyte.
		std::string szData = CEMSConversionUtil::ConvertToString( cwszData );

		char* szTemp = 0;

		long lLen = szData.length();

		szTemp = new char[ lLen + 1 ];

		memset( szTemp, 0, sizeof(char)*(lLen+1) );
		strcpy( szTemp, szData.c_str() );

		unsigned long ulSize = 0;
		unsigned char* abyString = 0;

		CEMSConversionUtil::ConvertToByteArray( szTemp, ulSize, (unsigned char*&) abyString );

		delete[] szTemp;
		szTemp = 0;

		if( abyString && ulSize > 0 )
		{
			iRet = fwrite( abyString, sizeof(unsigned char), ulSize, m_fpStream );

			delete[] abyString;
			abyString = 0;
		}

		fflush( m_fpStream );
	}

	return iRet;
}

int 
CEMSFormattedFileStream::WriteBinary( const BYTE* cabyData, const ULONG culBytes )
{
	int iRet = 0;

	if( cabyData && culBytes > 0 )
	{
		_Init();

		_ASSERTE( m_fpStream );

		if( !m_fpStream )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		iRet = fwrite( cabyData, sizeof(unsigned char), culBytes, m_fpStream );

		fflush( m_fpStream );
	}

	return iRet;
}

int 
CEMSFormattedFileStream::AddLine( const wchar_t* cwszFormat, ... )
{
	int iRet = 0;

	va_list params;
	va_start( params, cwszFormat );

	if( cwszFormat )
	{
		vwprintf( cwszFormat, params );

		_Init();

		_ASSERTE( m_fpStream );

		if( !m_fpStream )
		{
			THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
		}

		iRet = vfwprintf( m_fpStream, cwszFormat, params );
		iRet += fwprintf( m_fpStream, cwszCRLF );
		fflush( m_fpStream );
	}

	return iRet;
}

std::wstring 
CEMSFormattedFileStream::ReadAll()
{
	std::wstring wszRet;

	_Init();

	_ASSERTE( m_fpStream );

	if( !m_fpStream )
	{
		THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
	}

	const long clBufSize = 256;
	char szBuf[ clBufSize + 1 ];

	memset( szBuf, 0, (clBufSize+1)*sizeof(char) );

	while( 0 != fread( szBuf, 1, clBufSize, m_fpStream ) )
	{
		wszRet.append( CEMSConversionUtil::ConvertToString( szBuf ).c_str() );
		memset( szBuf, 0, (clBufSize+1)*sizeof(char) );
	}

	return wszRet;
}

std::string 
CEMSFormattedFileStream::ReadAllA()
{
	std::string szRet;

	_Init();

	_ASSERTE( m_fpStream );

	if( !m_fpStream )
	{
		THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
	}

	const long clBufSize = 256;
	char szBuf[ clBufSize + 1 ];

	memset( szBuf, 0, (clBufSize+1)*sizeof(char) );

	while( 0 != fread( szBuf, 1, clBufSize, m_fpStream ) )
	{
		szRet.append( szBuf );
		memset( szBuf, 0, (clBufSize+1)*sizeof(char) );
	}

	return szRet;
}

std::wstring 
CEMSFormattedFileStream::ReadLine()
{
	std::wstring wszRet;

	_Init();

	if( m_fpStream )
	{
		const long clBufSize = 4095;
		wchar_t wszBuf[ clBufSize + 1 ];
		memset( wszBuf, 0, (clBufSize+1)*sizeof(wchar_t) );

		if( fgetws( wszBuf, clBufSize, m_fpStream ) )
		{
			wszRet = wszBuf;
		}
	}

	return wszRet;
}

std::wstring 
CEMSFormattedFileStream::ReadLine2()
{
	std::wstring wszRet;

	_Init();

	if( m_fpStream )
	{
		const long clBufSize = 4095;
		wchar_t wszBuf[ clBufSize + 1 ];
		memset( wszBuf, 0, (clBufSize+1)*sizeof(wchar_t) );

		if( fgetws( wszBuf, clBufSize, m_fpStream ) )
		{
			if( wszBuf[ wcslen(wszBuf) -1 ] == L'\n' )
				wszBuf[ wcslen(wszBuf) -1 ] = L'\0';
			wszRet = wszBuf;
		}
	}

	return wszRet;
}


void
CEMSFormattedFileStream::Close()
{
	if( m_fpStream )
	{
		fclose( m_fpStream );
		m_fpStream = 0;
	}
}

void 
CEMSFormattedFileStream::_Init()
{
	if( !m_fpStream )
	{
		_ASSERTE( !m_wszFileSpec.empty() );

		if( m_wszFileSpec.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		std::wstring wszMode;

		switch( m_eMode )
		{
			case FMT_STREAM_OMODE_READ:
				wszMode = L"r";
				break;
			case FMT_STREAM_OMODE_WRITE:
				wszMode = L"w";
				break;
			case FMT_STREAM_OMODE_APPEND:
				wszMode = L"a+";
				break;
			case FMT_STREAM_OMODE_READWRITE:
				wszMode = L"r+";
				break;
			case FMT_STREAM_OMODE_READWRITE_CREATE:
				wszMode = L"w+";
				break;
			case FMT_STREAM_OMODE_READ_BINARY:
				wszMode = L"rb";
				break;
			case FMT_STREAM_OMODE_WRITE_BINARY:
				wszMode = L"wb";
				break;
			default:
				wszMode = L"a+";
				break;
		}

		m_fpStream = _wfopen( m_wszFileSpec.c_str(), wszMode.c_str() );

	}
}

/*********************************************************************
*	IEMSSeqStream Methods
*********************************************************************/
HRESULT
CEMSFormattedFileStream::Read( 
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead)
{
	HRESULT	hr = EMS_OK;

	*pv = 0;
	*pcbRead = 0;

	wchar_t*	wszOutBuffer = (wchar_t*)pv;

	try
	{
		int		iMaxChars = cb/sizeof(wchar_t);

		std::wstring wstrLine = ReadLine();

		wcsncpy( wszOutBuffer, wstrLine.c_str(), iMaxChars );
		*pcbRead = wcslen( wszOutBuffer ) * sizeof(wchar_t);
	}
	catch(...)
	{
		hr = EMS_EXCEPTION;
	}
	return hr;
}
        
HRESULT 
CEMSFormattedFileStream::Write( 
            /* [size_is][in] */ const BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbWritten)
{

	HRESULT	hr = EMS_OK;

	_Init();

	_ASSERTE( m_fpStream );

	if ( m_fpStream )
	{
		if( cb > 0 )
		{
			*pcbWritten = fwrite ( pv, sizeof(BYTE), cb, m_fpStream );
			fflush( m_fpStream );
		}
	}
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
	}	
	return hr;
}

/*********************************************************************
*	IEMSTextSeqStream Methods
*********************************************************************/

HRESULT 
CEMSFormattedFileStream::ReadLine( 
            /* [string][out] */ wchar_t **pwszLine)
{
	HRESULT	hr = EMS_OK;
	*pwszLine = NULL;
	try
	{
		std::wstring wstrLine = ReadLine();
		*pwszLine = (wchar_t*)CoTaskMemAlloc( (wstrLine.length()+1) * sizeof(wchar_t) );
		if ( !*pwszLine )
		{
			hr = EMS_NO_MEMORY;
		}
		else
		{
			wcscpy( *pwszLine, wstrLine.c_str() );
		}
	}
	catch(...)
	{
		hr = EMS_EXCEPTION;
		if ( *pwszLine )
		{
			CoTaskMemFree( *pwszLine );
			*pwszLine = NULL;
		}
	}
	return hr;
}
        
HRESULT 
CEMSFormattedFileStream::WriteLine( 
            /* [string][in] */ wchar_t *pwszLine)
{
	return EMS_NOT_IMPLEMENTED;
}

STDMETHODIMP_(ULONG) CEMSFormattedFileStream::AddRef()
{
	return IncrRefCount();
}

STDMETHODIMP_(ULONG) CEMSFormattedFileStream::Release()
{
	if (DecrRefCount() == 0)
	{
		delete this;
		return 0;
	}
	return GetRefCount();
}
	
STDMETHODIMP CEMSFormattedFileStream::QueryInterface(REFIID riid, LPVOID *lppObj)
{
	EMS_RESULT result = EMS_NOINTERFACE;
	LPUNKNOWN lpUnknown = 0;

	if (lppObj)
		*lppObj = lpUnknown;

	if (IsEqualIID(riid, IID_IEMSSeqStream))
	{
		lpUnknown = (LPUNKNOWN)(LPEMSSEQSTREAM)this;
	}
	else if (IsEqualIID(riid, IID_IEMSTextSeqStream))
	{
		lpUnknown = (LPUNKNOWN)(LPEMSTEXTSEQSTREAM)this;
	}
	else if (IsEqualIID(riid, IID_IUnknown))
	{
		lpUnknown = (LPUNKNOWN)this;
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
