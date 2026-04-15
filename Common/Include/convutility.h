/********************************************************************
*	Module:			convutility.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Declaration of CEMSConversionUtil. Routines
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
#ifndef __CONVUTLITY_H__
#define __CONVUTLITY_H__

#include <string>
using std::string;
using std::wstring;

#include "emserror.h"

#define GUID_STRING_SIZE 39

class CEMSConversionUtil
{
public:
	CEMSConversionUtil() {}
	~CEMSConversionUtil() {}

public:
	static void ConvertToByteArray( const double* cadValue, const long clElements,  unsigned char*& abyOut, long& lOutSize );
	static void ConvertToByteArray( const float* cafValue, const long clElements,  unsigned char*& abyOut, long& lOutSize );
	static void ConvertToByteArray( const unsigned short* casValue, const long clElements, unsigned char*& abyOut, long& lOutSize );
	static void ConvertToByteArray( const unsigned long* caulValue, const long clElements, unsigned char*& abyOut, long& lOutSize );
	static void ConvertToByteArray( const int* caiValue, const long clElements, unsigned char*& abyOut, long& lOutSize );
	static void ConvertToByteArray( wchar_t* szString, const long clMax, unsigned char* abyString );
	static void ConvertToByteArray( wchar_t* szString, const long clSize, unsigned char* pabyString[] );
	static void ConvertToByteArray( wchar_t* szString, unsigned long& lSize, unsigned char*& abyString );
	static void ConvertToByteArray( char* szString, unsigned long& lSize, unsigned char*& abyString );
	static void ConvertToByteArray( char* szString, const long clSize, unsigned char* pabyString[] );

	static wstring ConvertToString( __int64 i64Value );
	static string ConvertToStringA( __int64 i64Value );
	static wstring ConvertToHexString( __int64 i64Value );
	static wstring ConvertToString( unsigned char byValue );
	static wstring ConvertToString( unsigned short usValue );
	static wstring ConvertToString( unsigned long ulValue, const int ciBase = 10 );
	static string ConvertToStringA( unsigned long ulValue );
	static wstring ConvertToString( const long clValue );
	static wstring ConvertToString( long lArraySize, unsigned char* abyValue);
	static wstring ConvertToString( double dValue );
	static string ConvertToStringA( double dValue );
#ifdef UNICODE
	static wstring ConvertToStringT( double dValue ) { return ConvertToString( dValue ); }
#else
	static string ConvertToStringT( double dValue ) { return ConvertToStringA( dValue ); }
#endif
	static wstring ConvertToString( float fValue );
	static wstring ConvertToString( const long clElements, const double* cadValue);
	static wstring ConvertToString( const long clElements, const float* cafValue );
	static wstring ConvertToString( const long clElements, const unsigned short* casValue );
	static wstring ConvertToString( short sValue );
	static wstring ConvertToString( unsigned __int64 ui64Value );
	static wstring ConvertToString( char cValue );

	static string ConvertToString( const wchar_t* cwszString );
	static wstring ConvertToString( const char* cszString );
	
	static string ConvertToStringA( const long clArraySize, const unsigned char* cabyValue);

	static string ConvertToStringA( const unsigned char cbyValue );

	static wstring HexULongToStringW( const unsigned long culValue );
	static string HexULongToStringA( const unsigned long culValue );

	static EMS_RESULT ErrnoToEMSResult( int iErrno );

	static ULONG ConvertToULong( const wchar_t* cwszValue, const int ciBase = 10 );
	static ULONG ConvertToULong( const char* cszValue, const int ciBase = 10 );
	static long ConvertToLong( const wchar_t* cwszValue, const int ciBase = 10 );
	static long ConvertToLong( const char* cszValue, const int ciBase = 10 );
	static double ConvertToDouble( const wchar_t* cwszValue );
	static double ConvertToDouble( const char* cszValue );
	static float ConvertToFloat( const wchar_t* cwszValue );
	static float ConvertToFloat( const char* cszValue );
	static EMSTIME ConvertToTime( const wchar_t* cwszValue );
	static EMSTIME ConvertToTime( const char* cszValue );
	static INT64 ConvertHexStringToInt64( const wchar_t* cwszValue);
	static INT64 ConvertHexStringToInt64( const char* cszValue);
	static unsigned __int64 ConvertHexStringToUInt64( const wchar_t* cwszValue);
	static unsigned __int64 ConvertHexStringToUInt64( const char* cszValue);
	static unsigned __int64 ConvertStringToUInt64( const wchar_t* cwszValue);
	static long ConvertHexStringToLong( const wchar_t* cwszValue );
	static short ConvertToShort( const wchar_t* cwszValue, const int ciBase = 10 );
	static long ConvertToOleColor( const long clRed, const long clGreen, const long clBlue );

	//! Converts an EMSTIME to a string with format YYYY:MM:DD:HH:MM:SS
	static wstring ConvertToDateTimeStringW( const EMSTIME ctimeValue );

	//! Converts an EMSTIME to a string with format YYYY/DDD HH:MM:SS
	static wstring ConvertToDateTimeString2W( const EMSTIME ctimeValue );

	//! Converts an EMSTIME to a string with format MM/DD/YY
	static wstring ConvertToDateStringW( const EMSTIME ctimeValue );

	//! Converts an EMSTIME to a string with format HH:MM:SS.
	static wstring ConvertToTimeStringW( const EMSTIME ctimeValue );

	//! Converts an EMSTIME to a string with format YYYY:MM:DD:HH:MM:SS.
	static wstring ConvertToDateTimeHiResStringW( const EMSTIME ctimeValue );

	//! Converts an EMSTIME to a string with format YYYY.MM.DD.HH.MM.SS
	static string ConvertToDateTimeHiResString2A( const EMSTIME ctimeValue );

	static wstring ConvertToHexStringW( const ULONG culArraySize, unsigned char* abyValue );
	static string ConvertToHexStringA( const ULONG culArraySize, unsigned char* abyValue );

#ifdef UNICODE
	static wstring ConvertToHexStringT( const ULONG culArraySize, unsigned char* abyValue ) { return ConvertToHexStringW( culArraySize, abyValue); }
#else
	static string ConvertToHexStringT( const ULONG culArraySize, unsigned char* abyValue ) { return ConvertToHexStringA( culArraySize, abyValue); }
#endif

	static unsigned short ConvertToUShort( const wchar_t* cwszValue, const int ciBase = 10 );

	static wstring ConvertToHexStringW( const __int64 ci64Value ) { return ConvertToHexString( ci64Value ); }

	static string ConvertToHexStringA( const __int64 ci64Value );

#ifdef UNICODE
	static wstring ConvertToHexStringT( const __int64 ci64Value ) { return ConvertToHexStringW( ci64Value ); }
	static wstring ConvertToStringT( const ULONG culValue ) { return ConvertToString( culValue ); }
#else
	static string ConvertToHexStringT( const __int64 ci64Value ) { return ConvertToHexStringA( ci64Value ); }
	static string ConvertToStringT( const ULONG culValue ) { return ConvertToStringA( culValue ); }
#endif


	// Trim a string (left and right) from spaces, tabs (\t), line feed (\n) and carriage return (\r).
	static wstring Trim( const wchar_t* cwszStr );

	static string ConvertToHexStringA( const EMS_RESULT chrValue );
	static wstring ConvertToHexStringW( const EMS_RESULT chrValue );

#ifdef UNICODE
	static wstring ConvertToHexStringT( const EMS_RESULT chrValue ) { return ConvertToHexStringW( chrValue ); }
#else
	static string ConvertToHexStringT( const EMS_RESULT chrValue ) { return ConvertToHexStringA( chrValue ); }
#endif

	static unsigned short ConvertHexStringToUShort( const wchar_t* cwszValue );
	static unsigned short ConvertHexStringToUShort( const char* cszValue );

	static BYTE ConvertToByte( const wchar_t* cwszValue );
	static BYTE ConvertToByte( const char* cszValue );

// The following are not required on VMS
#ifndef __VMS
	static string	ConvertCLSIDToString( const GUID cguid );
	static GUID		ConvertStringtoCLSID( LPCTSTR cpszString );
#endif

	static void ConvertHexStringToByteArray( const wchar_t* cwszString, const long clElements, unsigned char* abyBuffer );

private:
	static string ms_szClassName;
	static const wchar_t* ms_cwszDateTimeSep;
	static const wchar_t* ms_cwszDateTimeSep2;
	static const char* ms_cszDateTimeSep2;
	static const wchar_t* ms_cwszSlashSep;
};

#endif