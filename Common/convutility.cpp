/********************************************************************
*	Module:			convutility.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of CEMSConversionUtil. Routines
*					for converting between different data types.
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	02/10/20		jbass 	start

********************************************************************/
#include "errno.h"
#include "convutility.h"
#include "emserror.h"
#include "aobjbase.h"
#include "emsexcpt.h"
#ifdef __VMS
#include <stdio>
#include <stdlib>
#endif
#include <sstream>
#include <iomanip>
#include "emstime.h"

string CEMSConversionUtil::ms_szClassName = "CEMSConversionUtil";
const wchar_t* CEMSConversionUtil::ms_cwszDateTimeSep = L":";
const wchar_t* CEMSConversionUtil::ms_cwszDateTimeSep2 = L".";
const char* CEMSConversionUtil::ms_cszDateTimeSep2 = ".";
const wchar_t* CEMSConversionUtil::ms_cwszSlashSep = L"/";

void
CEMSConversionUtil::ConvertToByteArray( const double* cadValue, const long clElements, unsigned char*& abyOut, long& lOutSize )
{
	abyOut = 0;
	lOutSize = 0;

	if( clElements > 0 && cadValue )
	{
		abyOut = new unsigned char[clElements*sizeof(double)];

		if( abyOut )
		{
			memset( abyOut, 0, clElements*sizeof(double) );
			
			// Just do a straight memory copy of the double array.
			memcpy( abyOut, cadValue, clElements*sizeof(double) );

			lOutSize = clElements*sizeof(double);

		}
		else
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}
}

void
CEMSConversionUtil::ConvertToByteArray( const float* cafValue, const long clElements, unsigned char*& abyOut, long& lOutSize )
{
	abyOut = 0;
	lOutSize = 0;

	if( clElements > 0 && cafValue )
	{
		abyOut = new unsigned char[clElements*sizeof(float)];

		if( abyOut )
		{
			memset( abyOut, 0, clElements*sizeof(float) );
			
			// Just do a straight memory copy of the float array.
			memcpy( abyOut, cafValue, clElements*sizeof(float) );

			lOutSize = clElements*sizeof(float);

		}
		else
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}
}

void
CEMSConversionUtil::ConvertToByteArray( const unsigned short* casValue, const long clElements, unsigned char*& abyOut, long& lOutSize )
{
	abyOut = 0;
	lOutSize = 0;

	if( clElements > 0 && casValue )
	{
		abyOut = new unsigned char[clElements*sizeof(unsigned short)];

		if( abyOut )
		{
			memset( abyOut, 0, clElements*sizeof(unsigned short) );

			// Just do a straight memory copy of the short array.
			memcpy( abyOut, casValue, clElements*sizeof(unsigned short) );

			lOutSize = clElements*sizeof(unsigned short);
		}
		else
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}
}

void
CEMSConversionUtil::ConvertToByteArray( const unsigned long* caulValue, const long clElements, unsigned char*& abyOut, long& lOutSize )
{
	abyOut = 0;
	lOutSize = 0;

	if( clElements > 0 && caulValue )
	{
		abyOut = new unsigned char[clElements*sizeof(unsigned long)];

		if( abyOut )
		{
			memset( abyOut, 0, clElements*sizeof(unsigned long) );

			// Just do a straight memory copy of the short array.
			memcpy( abyOut, caulValue, clElements*sizeof(unsigned long) );

			lOutSize = clElements*sizeof(unsigned long);
		}
		else
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}
}

void 
CEMSConversionUtil::ConvertToByteArray( const int* caiValue, const long clElements, unsigned char*& abyOut, long& lOutSize )
{
	abyOut = 0;
	lOutSize = 0;

	if( clElements > 0 && caiValue )
	{
		abyOut = new unsigned char[clElements*sizeof(int)];

		if( abyOut )
		{
			memset( abyOut, 0, clElements*sizeof(int) );

			// Just do a straight memory copy of the short array.
			memcpy( abyOut, caiValue, clElements*sizeof(int) );

			lOutSize = clElements*sizeof(int);
		}
		else
		{
			THROW_NOMEMORY_EXCEPTION();
		}
	}
}

void
CEMSConversionUtil::ConvertToByteArray( wchar_t* szString, const long clMax, unsigned char* abyString )
{
	if( szString && abyString )
	{
		long lStringSize = wcstombs( 0, szString, 0 );

		if ( 0 < lStringSize )
		{
			// First convert the string to multibyte.
			char* szMBString = new char[lStringSize + 1];
			if( szMBString )
			{
				memset( szMBString, 0, (lStringSize + 1 ) );

				wcstombs( szMBString, szString, lStringSize );

				// Now just write it back as a byte array.  Do a direct memcpy.
				memset( abyString, 0, clMax );

				memcpy( abyString, szMBString, clMax < lStringSize ? clMax : lStringSize);

				delete[] szMBString;
				szMBString = 0;
			}
		}
	}
}

void
CEMSConversionUtil::ConvertToByteArray( wchar_t* szString, const long clSize, unsigned char* pabyString[] )
{
	if( clSize > 0 && szString && pabyString )
	{
		memset( pabyString, 0, clSize );

		// First convert the string to multibyte.
		long lStringSize = wcstombs( 0, szString, 0 );

		if ( 0 < lStringSize )
		{
			char* szMBString = new char[lStringSize + 1];
			if( szMBString )
			{
				memset( szMBString, 0, (lStringSize + 1 ) );

				wcstombs( szMBString, szString, lStringSize );

				long lStrLen = strlen( szMBString );

				long lSize = lStrLen < clSize ? lStrLen : clSize;
				// Now just write it back as a byte array.  Do a direct memcpy.
				memcpy( *pabyString, szMBString, lSize );

				delete[] szMBString;
				szMBString = 0;
			}
		}
	}
}

void 
CEMSConversionUtil::ConvertToByteArray( char* szString, const long clSize, unsigned char* pabyString[] )
{
	if( clSize > 0 && pabyString && szString )
	{
		long lStrLen = strlen( szString );
		
		// Do a direct memcpy.
		memset( *pabyString, 0, clSize );

		long lSize = lStrLen < clSize ? lStrLen : clSize;

		memcpy( *pabyString, szString, lSize );
	}
}

void
CEMSConversionUtil::ConvertToByteArray( wchar_t* szString, unsigned long& lSize, unsigned char*& abyString )
{
	lSize = 0;
	abyString = 0;

	if( szString )
	{
		// First convert the string to multibyte.
		//long lStringSize = wcstombs( 0, szString, 0 );

		//char* szMBString = new char[lStringSize + 1];
		//if( szMBString )
		//{
		//	memset( szMBString, 0, (lStringSize + 1 ) );

		//	wcstombs( szMBString, szString, lStringSize );

			lSize = sizeof(wchar_t)*wcslen( szString );
			if ( lSize > 0 )
			{
				abyString = new unsigned char[lSize];
				memset( abyString, 0, lSize );

				// Now just write it back as a byte array.  Do a direct memcpy.
				memcpy( abyString, szString, lSize );
			}
//			delete[] szMBString;
//			szMBString = 0;
//		}
	}
}

void 
CEMSConversionUtil::ConvertToByteArray( char* szString, unsigned long& lSize, unsigned char*& abyString )
{
	lSize = 0;
	abyString = 0;

	if( szString )
	{
		lSize = sizeof(char)*strlen( szString );
		if ( lSize > 0 )
		{
			abyString = new unsigned char[lSize];
			if ( abyString )
			{
				memset( abyString, 0, lSize );

				// Now just write it back as a byte array.  Do a direct memcpy.
				memcpy( abyString, szString, lSize );
			}
		}
	}
}

wstring
CEMSConversionUtil::ConvertToString( __int64 i64Value )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 65.
	wchar_t wszString[66];
	memset( wszString, 0, 66*sizeof(wchar_t) );

#ifdef WIN32
	_i64tow( i64Value, wszString, 10 );
#elif defined(__VMS)
	swprintf( wszString, 66, L"%Ld", &i64Value );
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

string
CEMSConversionUtil::ConvertToStringA( __int64 i64Value )
{
	string szRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 65.
	char szString[66];
	memset( szString, 0, 66*sizeof(char) );
	
#ifdef WIN32
	_i64toa( i64Value, szString, 10 );
#elif defined(__VMS)
	sprintf( szString, "%Ld", i64Value );
#else
#error Platform not supported.
#endif

	szRet = szString;

	return szRet;
}


wstring 
CEMSConversionUtil::ConvertToString( unsigned __int64 ui64Value )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _ui64tow() is 65.
	wchar_t wszString[66];
	memset( wszString, 0, 66*sizeof(wchar_t) );

#ifdef WIN32
	_ui64tow( ui64Value, wszString, 10 );
#elif defined(__VMS)
	swprintf( wszString, 66, L"%Lu", &ui64Value );
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

wstring 
CEMSConversionUtil::ConvertToString( char cValue )
{
	wchar_t wszValue[2];
	memset( wszValue, 0, 2*sizeof(wchar_t) );

#ifdef WIN32
	swprintf( wszValue, L"%d", cValue );
#elif defined(__VMS)
	swprintf( wszValue, 2, L"%d", &cValue );
#else
#error Platform not supported.
#endif

	wstring wszRet;
	wszRet += wszValue;
	
	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToHexString( __int64 i64Value )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	wchar_t wszString[34];
	memset( wszString, 0, 34*sizeof(wchar_t) );

#ifdef WIN32
	_i64tow( i64Value, wszString, 16 );
	_wcsupr( wszString );
#elif defined(__VMS)
	swprintf( wszString, 34, L"%Lx", &i64Value );

	for( int i = 0; i < 33; i++ )
	{
		towupper( wszString[i] );
	}
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( unsigned char byValue )
{
	wchar_t wszValue[2];
	memset( wszValue, 0, 2*sizeof(wchar_t) );

#ifdef WIN32
	swprintf( wszValue, L"%hC", byValue );
#elif defined(__VMS)
	swprintf( wszValue, 2, L"%hC", &byValue );
#else
#error Platform not supported.
#endif

	wstring wszRet;
	wszRet.append( wszValue );
	
	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( unsigned short usValue )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	wchar_t wszString[34];

	memset( wszString, 0, 34*sizeof(wchar_t) );

#ifdef WIN32
	_itow( usValue, wszString, 10 );
#elif defined(__VMS)
	swprintf( wszString, 34, L"%hu", &usValue );
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

wstring 
CEMSConversionUtil::ConvertToString( short sValue )
{
	wstring wszRet;

	//Allocate the buffer.
	wchar_t wszString[34];

	memset( wszString, 0, 34*sizeof(wchar_t) );

#ifdef WIN32
	_itow( sValue, wszString, 10 );
#elif defined(__VMS)
	swprintf( wszString, 34, L"%hd", &sValue );
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( unsigned long ulValue, const int ciBase )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	wchar_t wszString[34];

	memset( wszString, 0, 34*sizeof(wchar_t) );

#ifdef WIN32
	_ultow( ulValue, wszString, ciBase );
#elif defined(__VMS)
	if( 10 == ciBase )
		swprintf( wszString, 34, L"%lu", &ulValue );
	else if( 16 == ciBase )
		swprintf( wszString, 34, L"%lx", &ulValue );
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
	}
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

string 
CEMSConversionUtil::ConvertToStringA( unsigned long ulValue )
{
	string szRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	char szString[34];

	memset( szString, 0, 34*sizeof(char) );

#ifdef WIN32
	_ultoa( ulValue, szString, 10 );
#elif defined(__VMS)
	sprintf( szString, "%lu", ulValue );
#else
#error Platform not supported.
#endif

	szRet = szString;

	return szRet;
}

wstring
CEMSConversionUtil::ConvertToString( const long clValue )
{
	wstring wszRet;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	wchar_t wszString[34];

	memset( wszString, 0, 34*sizeof(wchar_t) );

#ifdef WIN32
	_ltow( clValue, wszString, 10 );
#elif defined(__VMS)
	swprintf( wszString, 34, L"%ld", &clValue );
#else
#error Platform not supported.
#endif

	wszRet = wszString;

	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( long lArraySize, unsigned char* abyValue )
{
	wstring wszRet;

	if( lArraySize > 0 )
	{
		wchar_t* wszNewString = 0;

		try
		{
			// Allocate the string first.
			wszNewString = new wchar_t[ lArraySize + 1 ];

			if( !wszNewString )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszNewString, 0, (lArraySize + 1)*sizeof(wchar_t) );

			for( long l = 0; l < lArraySize; l++ )
			{
				wchar_t wszValue[2];
				memset( wszValue, 0, 2*sizeof(wchar_t) );
#ifdef WIN32
				swprintf( wszValue, L"%hC", abyValue[l] );
#elif defined(__VMS)
				swprintf( wszValue, 2, L"%hC", abyValue[l] );
#else
#error Platform not supported.
#endif

				wszNewString[l] = wszValue[0];
			}

			wszRet = wszNewString;

			delete[] wszNewString;
			wszNewString = 0;
		}
		catch( ... )
		{
			if( wszNewString )
			{
				delete[] wszNewString;
				wszNewString = 0;
			}

			throw;
		}
	}

	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( double dValue )
{
	wchar_t wszBuffer[256];
	memset( wszBuffer, 0, 256*sizeof(wchar_t) );

#ifdef WIN32
	_snwprintf( wszBuffer, 255, L"%f", dValue );
#elif defined(__VMS)
	swprintf( wszBuffer, 256, L"%lf", &dValue );
#else
#error Platform not supported.
#endif

	return wstring( wszBuffer );
}

string 
CEMSConversionUtil::ConvertToStringA( double dValue )
{
	char szBuffer[256];
	memset( szBuffer, 0, 256*sizeof(char) );

#ifdef WIN32
	_snprintf( szBuffer, 255, "%f", dValue );
#elif defined(__VMS)
	snprintf( szBuffer, 255, "%lf", &dValue );
#else
#error Platform not supported.
#endif

	return string( szBuffer );
}

wstring
CEMSConversionUtil::ConvertToString( float fValue )
{
	wchar_t wszBuffer[256];
	memset( &wszBuffer, 0, 256*sizeof(wchar_t) );

#ifdef WIN32
	swprintf( wszBuffer, L"%f", fValue );
#elif defined(__VMS)
	swprintf( wszBuffer, 256, L"%f", &fValue );
#else
#error Platform not supported.
#endif

	return wstring( wszBuffer );
}

wstring 
CEMSConversionUtil::ConvertToString( const long clElements, const double* cadValue )
{
	// We want to return a string that is just a representation of the raw bytes of the array.
	wstring wszRet;

	// First convert it to a byte array.
	unsigned char* abyValue = 0;
	long lSize = 0;
	ConvertToByteArray( cadValue, clElements, abyValue, lSize );

	if( abyValue && lSize > 0 )
	{
		wszRet = ConvertToString( lSize, abyValue );
		
		delete[] abyValue;
		abyValue = 0;
	}

	return wszRet;
}

wstring 
CEMSConversionUtil::ConvertToString( const long clElements, const float* cafValue )
{
	// We want to return a string that is just a representation of the raw bytes of the array.
	wstring wszRet;

	// First convert it to a byte array.
	unsigned char* abyValue = 0;
	long lSize = 0;
	ConvertToByteArray( cafValue, clElements, abyValue, lSize );

	if( abyValue && lSize > 0 )
	{
		wszRet = ConvertToString( lSize, abyValue );
		
		delete[] abyValue;
		abyValue = 0;
	}

	return wszRet;
}

wstring
CEMSConversionUtil::ConvertToString( const long clElements, const unsigned short* casValue )
{
	// We want to return a string that is just a representation of the raw bytes of the array.
	wstring wszRet;

	// First convert it to a byte array.
	unsigned char* abyValue = 0;
	long lSize = 0;
	ConvertToByteArray( casValue, clElements, abyValue, lSize );

	if( abyValue && lSize > 0 )
	{
		wszRet = ConvertToString( lSize, abyValue );
		
		delete[] abyValue;
		abyValue = 0;
	}

	return wszRet;
}


string
CEMSConversionUtil::ConvertToString( const wchar_t* cwszString )
{
	char*	szTemp = NULL;
	string	szRet;
	szRet = "";
	try
	{
		if ( cwszString && (wcslen( cwszString ) > 0) )
		{
			size_t cSize = wcstombs( 0, cwszString, 0);
			if ( 0 < (int)cSize )
			{
				szTemp = new char[ cSize + 1 ];
				if ( szTemp )
				{
					memset( szTemp, 0, sizeof(char)*(cSize+1) );

					size_t cWritten = wcstombs( szTemp, cwszString, cSize);

					if ( 0 < (int)cWritten )
					{
						szRet = szTemp;
					}
				}
			}
		}
	}
	catch( ... )
	{
		// do nothing
	}
	if ( szTemp )
	{
		delete[] szTemp;
		szTemp = 0;
	}
	return szRet;
}

wstring 
CEMSConversionUtil::ConvertToString( const char* cszString )
{
	wchar_t* wszTemp = 0;
	wstring	wszRet;
	wszRet = L"";

	try
	{
		if ( cszString && strlen(cszString) > 0 )
		{
			size_t cSize = mbstowcs( 0, cszString, 0 );
			if ( 0 < (int)cSize )
			{
				wszTemp = new wchar_t[ cSize + 1 ];
				if ( wszTemp )
				{
					memset( wszTemp, 0, sizeof(wchar_t)*(cSize + 1) );

					size_t cWritten = mbstowcs( wszTemp, cszString, cSize );
					if ( 0 < (int)cWritten )
					{
						wszRet = wszTemp;
					}
				}
			}
		}
	}
	catch( ... )
	{
		// do nothing
	}
	if ( wszTemp )
	{
		delete[] wszTemp;
		wszTemp = 0;
	}
	return wszRet;
}

string 
CEMSConversionUtil::ConvertToStringA( const long clArraySize, const unsigned char* cabyValue)
{
	string szRet;

	for( long l = 0; l < clArraySize; l++ )
	{
		string szString = ConvertToStringA( cabyValue[l] );

		if( !szString.empty() )
		{
			szRet += szString;

		}
		else
			break;
	}

	return szRet;
}

string 
CEMSConversionUtil::ConvertToStringA( const unsigned char cbyValue )
{
	char szValue[2];
	memset( szValue, 0, 2*sizeof(char) );

	_snprintf( szValue, 1, "%hC", cbyValue );

	string szRet;
	szRet += szValue;
	
	return szRet;
}

wstring 
CEMSConversionUtil::HexULongToStringW( const unsigned long culValue )
{
	wstring wszRet;

	wchar_t wszValue[ 33 ];
	memset( wszValue, 0, 33*sizeof(wchar_t) );

#ifdef WIN32
	_ultow( culValue, wszValue, 16 );
#elif defined(__VMS)
	swprintf( wszValue, 33, L"%lx", &culValue );
#else
#error Platform not supported.
#endif

	wszRet = wszValue;

	return wszRet;

}

string 
CEMSConversionUtil::HexULongToStringA( const unsigned long culValue )
{
	string szRet;

	char szValue[ 33 ];
	memset( szValue, 0, 33*sizeof(char) );

#ifdef WIN32
	_ultoa( culValue, szValue, 16 );
#elif defined(__VMS)
	sprintf( szValue, "%lx", culValue );
#else
#error Platform not supported.
#endif

	szRet = szValue;

	return szRet;
}

EMS_RESULT
CEMSConversionUtil::ErrnoToEMSResult( int iErrno )
{
	EMS_RESULT	hr;

#ifdef WIN32

	switch (iErrno)
	{
		case 0:
			hr = EMS_OK;
			break;
		case ENOENT:	// No such file or directory
			hr = EMS_PATH_NOT_FOUND;
			break;
		case EACCES:	// Permission denied
			hr = EMS_ACCESS_DENIED;
			break;
		case ENOMEM:	// Not enough memory
			hr = EMS_NO_MEMORY;
			break;
		case EINVAL:	// Invalid argument
		case E2BIG:		// Argument list too long
			hr = EMS_BAD_PARAM;			
			break;
		case EBADF:		// Bad file number
		case EEXIST:	// File exists
		case EMFILE:	// Too many open files
		case ENOSPC:	// No space left on device
			hr = EMS_IO_ERROR;
			break;
		// For now will report the rest as unknown
		case EAGAIN:	// No more processes or not enough memory or maximum nesting level reached
		case ECHILD:	// No spawned processes
		case EDEADLOCK:	// Resource deadlock would occur
		case EDOM:		// Math argument
		case ENOEXEC:	// Exec format error
		case ERANGE:	// Result too large
		case EXDEV:		// Cross-device link
		default:
			hr = EMS_UNKNOWN_ERROR;
			break;
	}
#elif defined(__VMS)
	hr = iErrno;
#else
#error Platform not supported.
#endif

	return hr;
}

ULONG 
CEMSConversionUtil::ConvertToULong( const wchar_t* cwszValue, const int ciBase )
{
	ULONG ulRet = 0;

	if( cwszValue && ciBase > 0 )
	{
		ulRet = wcstoul( cwszValue, 0, ciBase );
	}

	return ulRet;
}

ULONG 
CEMSConversionUtil::ConvertToULong( const char* cszValue, const int ciBase )
{
	ULONG ulRet = 0;

	if( cszValue && ciBase > 0 )
	{
		ulRet = strtoul( cszValue, 0, ciBase );
	}

	return ulRet;
}

long
CEMSConversionUtil::ConvertToLong( const wchar_t* cwszValue, const int ciBase )
{
	long lRet = 0;

	if( cwszValue && ciBase > 0 )
	{
		lRet = wcstol( cwszValue, 0, ciBase );
	}

	return lRet;
}

long 
CEMSConversionUtil::ConvertToLong( const char* cszValue, const int ciBase )
{
	long lRet = 0;

	if( cszValue && ciBase > 0 )
	{
		lRet = strtol( cszValue, 0, ciBase );
	}

	return lRet;
}

double 
CEMSConversionUtil::ConvertToDouble( const wchar_t* cwszValue )
{
	double dRet = 0.0;

	if( cwszValue )
	{
		dRet = wcstod( cwszValue, 0);
	}

	return dRet;
}

double
CEMSConversionUtil::ConvertToDouble( const char* cszValue )
{
	double dRet = 0.0;

	if( cszValue )
	{
		dRet = strtod( cszValue, 0);
	}

	return dRet;
}

float 
CEMSConversionUtil::ConvertToFloat( const wchar_t* cwszValue )
{
	float fRet = 0.0;

	if( cwszValue )
	{
		fRet = wcstod( cwszValue, 0 );
	}

	return fRet;
}
	
float 
CEMSConversionUtil::ConvertToFloat( const char* cszValue )
{
	float fRet = 0.0;

	if( cszValue )
	{
		fRet = strtod( cszValue, 0 );
	}

	return fRet;
}


EMSTIME 
CEMSConversionUtil::ConvertToTime( const wchar_t* cwszValue )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	if( cwszValue )
	{
#ifdef WIN32
		timeRet.intTime = _wtoi64( cwszValue );
#elif defined(__VMS)
		timeRet.intTime = atoll( ConvertToString(cwszValue).c_str() );
#else
#error Platform not supported.
#endif
	}

	return timeRet;
}

EMSTIME 
CEMSConversionUtil::ConvertToTime( const char* cszValue )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	if( cszValue )
	{
#ifdef WIN32
		timeRet.intTime = _atoi64( cszValue );
#elif defined(__VMS)
		timeRet.intTime = atoll( cszValue );
#else
#error Platform not supported.
#endif
	}

	return timeRet;
}

INT64 
CEMSConversionUtil::ConvertHexStringToInt64( const wchar_t* cwszValue )
{
	INT64 i64Ret = 0;

	if( cwszValue )
	{
		swscanf( cwszValue, L"%I64x", &i64Ret );
	}

	return i64Ret;
}

INT64 
CEMSConversionUtil::ConvertHexStringToInt64( const char* cszValue)
{
	INT64 i64Ret = 0;

	if( cszValue )
	{
		sscanf( cszValue, "%I64x", &i64Ret );
	}

	return i64Ret;
}

unsigned __int64 
CEMSConversionUtil::ConvertHexStringToUInt64( const wchar_t* cwszValue )
{
	unsigned __int64 ui64Ret = 0;

	if( cwszValue )
	{
		swscanf( cwszValue, L"%I64x", &ui64Ret );
	}

	return ui64Ret;
}

unsigned __int64 
CEMSConversionUtil::ConvertHexStringToUInt64( const char* cszValue)
{
	unsigned __int64 ui64Ret = 0;

	if( cszValue )
	{
		sscanf( cszValue, "%I64x", &ui64Ret );
	}

	return ui64Ret;
}

unsigned __int64 
CEMSConversionUtil::ConvertStringToUInt64( const wchar_t* cwszValue )
{
	unsigned __int64 ui64Ret = 0;

	if( cwszValue )
	{
		swscanf( cwszValue, L"%I64d", &ui64Ret );
	}

	return ui64Ret;
}

long 
CEMSConversionUtil::ConvertHexStringToLong( const wchar_t* cwszValue )
{
	long lRet = 0;

	if( cwszValue )
	{
		swscanf( cwszValue, L"%x", &lRet );
	}

	return lRet;
}

short 
CEMSConversionUtil::ConvertToShort( const wchar_t* cwszValue, const int ciBase )
{
	short sRet = 0;

	if( cwszValue && ciBase > 0 )
	{
		// There will be truncation if the value is larger than a short.
		// Assumed that caller believes that the value is truly a short.
		sRet = (short) ConvertToLong( cwszValue, ciBase );
	}

	return sRet;
}

long 
CEMSConversionUtil::ConvertToOleColor( const long clRed, const long clGreen, const long clBlue )
{
	return ( clRed + (clGreen * 256) + (clBlue * 65536) );
}

wstring 
CEMSConversionUtil::ConvertToDateTimeStringW( const EMSTIME ctimeValue )
{
	std::wstringstream wstrmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nMonth << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nDay << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nHour << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nMinute << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nSecond;

	return wstrmRet.str();

}

wstring 
CEMSConversionUtil::ConvertToDateTimeString2W( const EMSTIME ctimeValue )
{
	std::wstringstream wstrmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << ms_cwszSlashSep << std::setw( 3 ) << std::setfill( L'0' ) <<
				tmFields.nJulianDay << L" " << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nHour << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nMinute << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nSecond;

	return wstrmRet.str();

}

wstring 
CEMSConversionUtil::ConvertToHexStringW( const ULONG culArraySize, unsigned char* abyValue )
{
	std::wstringstream wstrmRet;

	if( culArraySize && abyValue )
	{
		wchar_t wszValue[32];

		for( ULONG l = 0; l < culArraySize; l++ )
		{
			memset( wszValue, 0, 32*sizeof(wchar_t) );
#ifdef WIN32
			swprintf( wszValue, L"%02x", abyValue[l] );		
#elif defined(__VMS)
			swprintf( wszValue, 32, L"%02x", abyValue[l] );		
#else
#error Platform not supported.
#endif
			wstrmRet << wszValue;

		}
	}

	return wstrmRet.str();
}

string 
CEMSConversionUtil::ConvertToHexStringA( const ULONG culArraySize, unsigned char* abyValue )
{
	std::stringstream strmRet;

	if( culArraySize && abyValue )
	{
		char szValue[32];

		for( ULONG l = 0; l < culArraySize; l++ )
		{
			memset( szValue, 0, 32*sizeof(char) );
			sprintf( szValue, "%x", abyValue[l] );		

			strmRet << szValue;

		}
	}

	return strmRet.str();
}

string 
CEMSConversionUtil::ConvertToHexStringA( const EMS_RESULT chrValue )
{
	string oszRet;

	char szValue[ 32 ];
	memset( szValue, 0, 32*sizeof(char) );

#ifdef WIN32
	_snprintf( szValue, 31, "%x", chrValue );
#elif defined(__VMS)
	snprintf( szValue, 31, "%lx", chrValue );
#else
#error Platform not supported.
#endif

	oszRet = szValue;

	return oszRet;
}

wstring 
CEMSConversionUtil::ConvertToHexStringW( const EMS_RESULT chrValue )
{
	wstring owszRet;

	wchar_t wszValue[ 32 ];
	memset( wszValue, 0, 32*sizeof(wchar_t) );

#ifdef WIN32
	_snwprintf( wszValue, 31, L"%x", chrValue );
#elif defined(__VMS)
	swprintf( wszValue, 32, L"%lx", chrValue );
#else
#error Platform not supported.
#endif

	owszRet = wszValue;

	return owszRet;
}

wstring 
CEMSConversionUtil::ConvertToDateStringW( const EMSTIME ctimeValue )
{
	std::wstringstream wstrmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	if( tmFields.nYear >= 2000 )
	{
		tmFields.nYear -= 2000;
	}
	else if( tmFields.nYear < 2000 )
	{
		tmFields.nYear -= 1900;
	}

	wstrmRet << std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nMonth << ms_cwszSlashSep <<
				std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nDay << ms_cwszSlashSep <<
				std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nYear;

	return wstrmRet.str();
}

wstring 
CEMSConversionUtil::ConvertToTimeStringW( const EMSTIME ctimeValue )
{
	std::wstringstream wstrmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nHour << ms_cwszDateTimeSep <<
				std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nMinute << ms_cwszDateTimeSep <<
				std::setw( 2 ) << std::setfill( L'0' ) << tmFields.nSecond;

	return wstrmRet.str();
}

wstring 
CEMSConversionUtil::ConvertToDateTimeHiResStringW( const EMSTIME ctimeValue )
{
	std::wstringstream wstrmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nMonth << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nDay << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nHour << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nMinute << ms_cwszDateTimeSep << std::setw( 2 ) << std::setfill( L'0' ) <<
				tmFields.nSecond << ms_cwszDateTimeSep2 << std::setw( 4 ) << std::setfill( L'0' ) <<
				tmFields.lNanosecond/100000;

	return wstrmRet.str();
}

string 
CEMSConversionUtil::ConvertToDateTimeHiResString2A( const EMSTIME ctimeValue )
{
	std::stringstream strmRet;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	strmRet << tmFields.nYear << ms_cszDateTimeSep2 << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMonth << ms_cszDateTimeSep2 << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nDay << ms_cszDateTimeSep2 << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nHour << ms_cszDateTimeSep2 << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMinute << ms_cszDateTimeSep2 << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nSecond << ms_cszDateTimeSep2 << std::setw( 4 ) << std::setfill( '0' ) <<
				tmFields.lNanosecond/100000;

	return strmRet.str();
}

unsigned short 
CEMSConversionUtil::ConvertToUShort( const wchar_t* cwszValue, const int ciBase )
{
	unsigned short usRet = 0;

	if( cwszValue && ciBase > 0 )
	{
		// There will be truncation if the value is larger than a short.
		// Assumed that caller believes that the value is truly a short.
		usRet = (unsigned short) ConvertToULong( cwszValue, ciBase );
	}

	return usRet;
}

string 
CEMSConversionUtil::ConvertToHexStringA( const __int64 ci64Value )
{
	string szRet;

	//Allocate the buffer.
	//Max return size from _i64toa() is 33.
	char szString[34];
	memset( szString, 0, 34*sizeof(char) );

#ifdef WIN32
	_i64toa( ci64Value, szString, 16 );
	_strupr( szString );
#elif defined(__VMS)
	snprintf( szString, 33, "%llx", &ci64Value );
	for( int i = 0; i < 34; i++ )
	{
		toupper( szString[i] );
	}
#else
#error Platform not supported.
#endif

	szRet = szString;

	return szRet;
}

wstring 
CEMSConversionUtil::Trim( const wchar_t* cwszStr )
{
	std::wstring wszRetStr;
	
	if( cwszStr )
	{
		int iLen = wcslen(cwszStr);
		int iStart=0;
		int iEnd=iLen-1;

		if( (1 == iLen) && ( (cwszStr[0] == L' ') || (cwszStr[0] == L'\n') ) )
		{
			return L"";
		}

		while( (iStart < iLen) && 
			   ( (cwszStr[iStart] == L' ' ) ||
			     (cwszStr[iStart] == L'\t' ) ||
			     (cwszStr[iStart] == L'\n' ) ||
				 (cwszStr[iEnd] == L'\r' ) ) )
		{
			iStart++;
		}
	
		while( iEnd > iStart && 
			   ( (cwszStr[iEnd] == L' ' ) ||
			     (cwszStr[iEnd] == L'\n') ||
			     (cwszStr[iEnd] == L'\t') ||
				 (cwszStr[iEnd] == L'\r' ) ) )
		{
			iEnd--;
		}

		int i=iStart;
		while ( i<=iEnd )
		{
			wszRetStr += cwszStr[i];
			i++;
		}
	}
	
	return wszRetStr;
}

unsigned short 
CEMSConversionUtil::ConvertHexStringToUShort( const wchar_t* cwszValue )
{
	unsigned short usRet = 0;

	if( cwszValue )
	{
		swscanf( cwszValue, L"%x", &usRet );
	}

	return usRet;
}

unsigned short 
CEMSConversionUtil::ConvertHexStringToUShort( const char* cszValue )
{
	unsigned short usRet = 0;

	if( cszValue )
	{
		sscanf( cszValue, "%x", &usRet );
	}

	return usRet;
}

BYTE 
CEMSConversionUtil::ConvertToByte( const wchar_t* cwszValue )
{
	BYTE byRet = '0';

	std::string oszValue = ConvertToString( cwszValue );

	if( oszValue.length() > 0 )
		byRet = oszValue.at(0);

	return byRet;
}

BYTE 
CEMSConversionUtil::ConvertToByte( const char* cszValue )
{
	BYTE byRet = '0';

	if( cszValue && (strlen(cszValue) > 0) )
		byRet = cszValue[0];

	return byRet;
}

// The following should not be required on VMS
#ifndef __VMS

#include "objbase.h" // StringFromCLSID and CLSIDFromString

string
CEMSConversionUtil::ConvertCLSIDToString( const GUID cguid )
{
	EMS_RESULT	hr = EMS_OK;
	LPOLESTR	lpwStr = 0;

	char	szGUID[GUID_STRING_SIZE];
	memset( szGUID, 0, GUID_STRING_SIZE*sizeof(char) );

	try
	{
		hr = StringFromCLSID( cguid, &lpwStr );
		if ( S_OK == hr )
		{
			int iLen = wcslen( lpwStr );
			if ( iLen != (GUID_STRING_SIZE-1) )
			{
				hr = E_INVALIDARG;
			}
			else
			{
				// Convert back from UNICODE to ANSI
				// Given that this is a GUID string there is no need to worry about actual conversion
				// ... we are simply changing the size of the characters
				for ( int i=0; i < iLen; i++ )
				{
					szGUID[i] = lpwStr[i];
				}
			}
		}
	}
	catch(...)
	{
		hr = EMS_EXCEPTION;
	}
	if ( lpwStr )
	{
		CoTaskMemFree( (LPVOID)lpwStr );
	}
	return szGUID;
}

GUID
CEMSConversionUtil::ConvertStringtoCLSID( LPCTSTR cpszString )
{
	GUID		guid;
	memset( &guid, 0, sizeof(GUID) );

	int	iLen = strlen( cpszString );
	// GUID string is enclosed by braces
    if( cpszString
		&& (cpszString[0] == '{') 
		&& strlen( cpszString ) == (GUID_STRING_SIZE-1)
		&& (cpszString[GUID_STRING_SIZE-2] == '}') )
	{
		wchar_t		wszGUID[GUID_STRING_SIZE];
		memset( wszGUID, 0, GUID_STRING_SIZE*sizeof(wchar_t) );

		// Convert to Unicode while you are copying to your temporary buffer.
		// Do not worry about non-ANSI characters; this is a GUID string.
		for ( int i=0; i < GUID_STRING_SIZE; i++ )
		{
			wszGUID[i] = cpszString[i];
		}
		// Borrow the functionality of CLSIDFromString to get the 16-byte
		// GUID from the GUID string.
		if ( FAILED( CLSIDFromString(wszGUID, &guid) ) )
		{
			memset( &guid, 0, sizeof(GUID) );
		}
	}
    return guid;
}
#endif

void 
CEMSConversionUtil::ConvertHexStringToByteArray( const wchar_t* cwszString, const long clElements, unsigned char* abyBuffer )
{
	if( cwszString && abyBuffer )
	{
		long lLen = wcslen( cwszString );

		long k = 0;
		for( long l = 0; (k < clElements) && (l < lLen); l = l + 2, k++ )
		{
			wchar_t wszTemp[3];
			memset( wszTemp, 0, sizeof(wszTemp) );

			wcsncpy( wszTemp, &cwszString[l], 2 );

			swscanf( wszTemp, L"%2hX", &(abyBuffer[k]) );
		}
	}
}
