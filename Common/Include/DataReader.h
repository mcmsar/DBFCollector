/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include "aobjbase.h"
#include "dal.h"
#include <string>

//! @class CEMSDataReader
//! Pure virtual base class -- for reading raw data from various sources
class CEMSDataReader : public CApiObjBase
{
	public:
		CEMSDataReader() {}
		virtual ~CEMSDataReader() {}

		//! @fn std::wstring GetAsStringW( const long clIndex )
		//! Retrieve the field at the specified index in string format.
		virtual std::wstring GetFieldAsStringW( const long clIndex ) = 0;

		//! @fn std::string GetFieldAsStringA( const long clIndex )
		//! Retrieve the field at the specified index in string format.
		virtual std::string GetFieldAsStringA( const long clIndex ) = 0;

		//! @fn std::wstring GetFieldAsStringW( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name in string format.
		virtual std::wstring GetFieldAsStringW( const wchar_t* cwszColumn ) = 0;

		//! @fn std::string GetFieldAsStringA( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name in string format.
		virtual std::string GetFieldAsStringA( const wchar_t* cwszColumn ) = 0;

		//! @fn ULONG GetFieldAsULong( const long clIndex )
		//! Retrieve the field at the specified index as  ULONG.
		virtual ULONG GetFieldAsULong( const long clIndex ) = 0;

		//! @fn ULONG GetFieldAsULong( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name.
		virtual ULONG GetFieldAsULong( const wchar_t* cwszColumn ) = 0;

		//! @fn EMSTIME GetFieldAsTime( const long clIndex )
		//! Retrieve the field with the specified index as an EMSTIME.
		virtual EMSTIME GetFieldAsTime( const long clIndex ) = 0;

		//! @fn EMSTIME GetFieldAsTime( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name.
		virtual EMSTIME GetFieldAsTime( const wchar_t* cwszColumn ) = 0;

		//! @fn double GetFieldAsDouble( const long clIndex )
		//! Retrieve the field with the specified index as a double.
		virtual double GetFieldAsDouble( const long clIndex ) = 0;

		//! @fn double GetFieldAsDouble( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name.
		virtual double GetFieldAsDouble( const wchar_t* cwszColumn ) = 0;

		//! @fn double GetFieldAsInt( const long clIndex )
		//! Retrieve the field with the specified index as an int.
		virtual int GetFieldAsInt( const long clIndex ) = 0;

		//! @fn int GetFieldAsInt( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name.
		virtual int GetFieldAsInt( const wchar_t* cwszColumn ) = 0;

		//! @fn void GetFieldAsDoubleArray( const long clIndex, double*& adValues, ULONG& ulElements )
		//! Retrieve the field with the specified index as an array of doubles.
		//! The caller must delete the returned array.
		virtual void GetFieldAsDoubleArray( const long clIndex, double*& adValue, ULONG& ulElements ) = 0; 

		//! @fn void GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValues )
		//! Retrieve the field with the specified name as an array of doubles.
		//! The caller must delete the returned array.
		virtual void GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValue, ULONG& ulElements ) = 0; 

		//! @fn void GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue );
		//! Retrieve the field with the specified index as an array of floats.
		//! The caller must allocate the array.
		virtual void GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue ) = 0;

		//! @fn void GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, float* afValue )
		//! Retrieve the field with the specified name as an array of doubles.
		//! The caller must allocate the array.
		virtual void GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, float* afValue ) = 0;

		//!@fn USHORT GetFieldAsUShort( const long clIndex )
		//! Retrieve the field at the specified index as an unsigned short.
		virtual USHORT GetFieldAsUShort( const long clIndex ) = 0;

		//!@fn USHORT GetFieldAsUShort( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name as an unsigned short.
		virtual USHORT GetFieldAsUShort( const wchar_t* cwszColumn ) = 0;

		//! @fn void GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, unsigned char* abyValue )
		//! Retrieve the field at the specified index as a byte array.
		//! The caller allocates the buffer (i.e., the binary array) and specifies its size.
		//! An exception will be thrown if the actual data is larger than the buffer.
		virtual void GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, unsigned char* abyValue ) = 0;

		//! @fn void GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, const ULONG culMaxArraySize, unsigned char* abyValue )
		//! Retrieve the field with the specified name as a byte array.
		//! The caller allocates the buffer (i.e., the binary array) and specifies its size.
		//! An exception will be thrown if the actual data is larger than the buffer.
		virtual void GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, const ULONG culMaxArraySize, unsigned char* abyValue ) = 0;

		//! @fn UINT64 GetFieldAsUI64( const long clIndex )
		//! Retrieve the field at the specified index as an unsigned 64 bit integer.
		virtual UINT64 GetFieldAsUI64( const long clIndex ) = 0;

		//! @fn UINT64 GetFieldAsUI64( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name as an unsigned 64 bit integer.
		virtual UINT64 GetFieldAsUI64( const wchar_t* cwszColumn ) = 0;

		//! @fn UINT64 GetFieldAsI64( const long clIndex )
		//! Retrieve the field at the specified index as a 64 bit integer.
		virtual INT64 GetFieldAsI64( const long clIndex ) = 0;

		//! @fn UINT64 GetFieldAsI64( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name as a 64 bit integer.
		virtual INT64 GetFieldAsI64( const wchar_t* cwszColumn ) = 0;

		//! @fn float GetFieldAsFloat( const long clIndex )
		//! Retrieve the field at the specified index as a float.
		virtual float GetFieldAsFloat( const long clIndex ) = 0;

		//! @fn float GetFieldAsFloat( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified index as a float.
		virtual float GetFieldAsFloat( const wchar_t* cwszColumn ) = 0;

		//! @fn WORD GetFieldAsWord( const long clIndex )
		//! Retrieve the field at the specified index as a WORD.
		virtual WORD GetFieldAsWord( const long clIndex ) = 0;

		//! @fn WORD GetFieldAsWord( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified index as a WORD.
		virtual WORD GetFieldAsWord( const wchar_t* cwszColumn ) = 0;
};

#endif
