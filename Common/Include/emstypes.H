/********************************************************************
*	Module:			EMSTypes.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Definitions for platform independent data types
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	   Copyright (c) 2000 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	00/11/13		rvw	start

********************************************************************/
#ifndef INC_EMSTYPES
#define INC_EMSTYPES

typedef int BOOL;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif // !FALSE

#ifdef __WIN32__				// defined by Borland Builder
	#ifndef WIN32
		#define WIN32         
	#endif
#endif

#if defined (WIN32) && !defined (_WIN32)
#define _WIN32
#endif

#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif (_MSC_VER >= 1000) || defined(_STDCALL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#define CDECL
#else
#define CALLBACK   __far pascal
//#define CALLBACK   far pascal
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
#define PASCAL      pascal
#define CDECL			_cdecl
#endif

#ifndef FAR

#ifdef _WIN16
#define FAR             _far
#elif defined( WIN32 )
#define FAR
#elif defined( __VMS )
#define FAR
#else
#define FAR 				_far
#endif /* _WIN16 */

#endif

#ifdef WIN32
#define __RPC_FAR
#define DLLIMPORT	__declspec(dllimport)
#define DLLEXPORT	__declspec(dllexport)
#elif defined( __VMS )
#define __RPC_FAR
#define DLLIMPORT        FAR
#define DLLEXPORT        FAR
#else
#define DLLIMPORT	 FAR
#define DLLEXPORT	 FAR
#ifndef WINVER
#define __RPC_FAR 	_far 
#else
#define __RPC_FAR 	
#endif
#endif

#ifdef WIN32                                                        /*W32*/
	#define far 
	#define __far
#endif

#ifndef FARSTRUCT
	#ifdef __cplusplus
		#define FARSTRUCT   FAR
	#else
		#define FARSTRUCT   
	#endif  // __cplusplus
#endif  // FARSTRUCT


//#ifndef __BORLANDC__

	#ifndef _WORD_DEFINED
	#define _WORD_DEFINED

		typedef unsigned short WORD;
		typedef WORD __RPC_FAR *LPWORD;

	#endif // !_WORD_DEFINED

	typedef char CHAR;
	typedef CHAR __RPC_FAR *LPCHAR;

	typedef CHAR __RPC_FAR *LPSTR;
	typedef /* [string] */ const CHAR __RPC_FAR *LPCSTR;

	#ifndef _WCHAR_DEFINED 
		#define _WCHAR_DEFINED
// Only required for pre-.NET versions
		#if _MSC_VER < 1300

			#ifdef __BORLANDC__
				typedef wchar_t WCHAR;
			#else
				typedef WORD WCHAR;
				typedef WCHAR __RPC_FAR *LPWSTR;
				typedef const WCHAR __RPC_FAR *LPCWSTR;
				typedef WCHAR __RPC_FAR *LPWCHAR;
			#endif

		#else
			#if _NATIVE_WCHAR_T_DEFINED
				typedef wchar_t WCHAR;		
			#else
				typedef WORD WCHAR;				
			#endif
			typedef WCHAR __RPC_FAR *LPWSTR;
			typedef const WCHAR __RPC_FAR *LPCWSTR;
			typedef WCHAR __RPC_FAR *LPWCHAR;
		#endif

	#endif // _WCHAR_DEFINED

	#ifndef _INT_DEFINED
	#define _INT_DEFINED

		typedef int INT;

	#endif // !_INT_DEFINED

	#ifndef _UINT_DEFINED
	#define _UINT_DEFINED
	
		typedef unsigned int UINT;
		typedef UINT __RPC_FAR *LPUINT;

	#endif // !_UINT_DEFINED

	#ifndef _LONG_DEFINED
	#define _LONG_DEFINED

		typedef long LONG;

	#endif // !_LONG_DEFINED

	#ifndef _BYTE_DEFINED
	#define _BYTE_DEFINED

		typedef unsigned char BYTE;
		typedef BYTE __RPC_FAR *LPBYTE;

	#endif // !_BYTE_DEFINED

	#ifndef _WORD_DEFINED
	#define _WORD_DEFINED

		typedef unsigned short WORD;
		typedef WORD __RPC_FAR *LPWORD;

	#endif // !_WORD_DEFINED

	#ifndef _ULONG_DEFINED
	#define _ULONG_DEFINED

		typedef unsigned long ULONG;

	#endif // !_ULONG_DEFINED

	#ifndef _DWORD_DEFINED
	#define _DWORD_DEFINED

		typedef unsigned long DWORD;
		typedef DWORD __RPC_FAR *LPDWORD;

	#endif // !_DWORD_DEFINED

	#ifndef _SIZE_T_DEFINED
		#ifndef __BORLANDC__
			#define _SIZE_T_DEFINED
//			typedef unsigned int size_t;
		#endif
	#endif 

	#ifndef _INT64_DEFINED
	#define _INT64_DEFINED
		typedef __int64 INT64, __RPC_FAR *LPINT64;
	#endif

	#ifndef _UINT64_DEFINED
	#define _UINT64_DEFINED
		typedef unsigned __int64 UINT64, __RPC_FAR *LPUINT64;
	#endif

//#endif  // __BORLANDC__

#ifndef _WINDEF_

	typedef void __RPC_FAR *LPVOID;
	typedef void __RPC_FAR *HANDLE;
	typedef HANDLE __RPC_FAR *LPHANDLE;

#endif

#ifndef WIN32
typedef struct FARSTRUCT _LARGE_INTEGER {
    DWORD LowPart;
    LONG  HighPart;
} LARGE_INTEGER, *PLARGE_INTEGER, FAR *LPLARGE_INTEGER;
#endif


#ifndef WIN32
typedef struct FARSTRUCT _ULARGE_INTEGER {
    DWORD LowPart;
    DWORD HighPart;
} ULARGE_INTEGER, *PULARGE_INTEGER, FAR *LPULARGE_INTEGER;
#endif


//
// Neutral ANSI/UNICODE types and macros
//
#ifdef  UNICODE                     

#ifndef _TCHAR_DEFINED
typedef WCHAR TCHAR, *PTCHAR;
typedef WCHAR TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPWSTR LPTCH, PTCH;
typedef LPWSTR PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;
typedef LPWSTR LP;
#define __TEXT(quote) L##quote      

#else   /* UNICODE */               

#ifndef _TCHAR_DEFINED
typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE , *PTBYTE ;
#define _TCHAR_DEFINED
#endif /* !_TCHAR_DEFINED */

typedef LPSTR LPTCH, PTCH;
typedef LPSTR PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;
#define __TEXT(quote) quote         

#endif /* UNICODE */                

#define TEXT(quote) __TEXT(quote)   

#ifndef GUID_DEFINED
#define GUID_DEFINED

typedef struct _GUID {          // size is 16
    DWORD Data1;
    WORD   Data2;
    WORD   Data3;
    BYTE  Data4[8];
} GUID, __RPC_FAR *LPGUID;

#endif // !GUID_DEFINED

#ifdef WIN32
#define _fmemset memset
#define _fmemcpy memcpy
#define _fmemcmp memcmp
#define _fstrcpy strcpy
#define _fstrlen strlen
#define _fstrrchr strrchr
#define _fstrtok strtok
#define _fstrncpy strncpy
//#define _fstrnicmp strnicmp
#endif // WIN32

#ifdef __VMS
#ifdef __cplusplus
// This is so that compiles on VMS can use the Windows tchar.h (which uses __inline).
#define __inline inline
#endif
#endif

#ifndef NULL
#define NULL 0
#endif

//
// now include the EMS specific extensions
//
#ifndef INC_EMSTYPEX
#include "emstypex.h"
#endif // INC_EMSTYPEX

#endif // INC_EMSTYPES
