/*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc., All rights reserved
*
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

#ifndef __EMSCSVREADER_H__
#define __EMSCSVREADER_H__

#include <vector>
using std::vector;

#include <string>
using std::wstring;
using std::string;

#include <map>
using std::map;

#include "DataReader.h"
#include "FormattedFileStream.h"

class  CEMSRecordMetaData;

class CEMSCSVReader : public CEMSDataReader
{
public:
	CEMSCSVReader();
	CEMSCSVReader(	std::wstring& wstrLine, 
					const wchar_t cwcSeparator = L',',
					CEMSRecordMetaData* pMeta = NULL );
	CEMSCSVReader( const CEMSCSVReader& x );
	virtual ~CEMSCSVReader();

	//! @fn int Init(	std::wstring& wstrLine, 
	//!					const wchar_t cwcSeparator,
	//!					CEMSRecordMetaData* pMeta = NULL );
	//! Load a new set of values into memory.
	//! Saves the supplied meta data for future use
	//! Returns the number of values found on the given line.
	int		Init(	std::wstring& wstrLine, 
					const wchar_t cwcSeparator, 
					CEMSRecordMetaData* pMeta = NULL );

	//! @fn void Clear()
	//! Clear the internal buffers
	void	Clear();

	//! @fn int BuildMetaData( )
	//! Build a set of meta data using the current set of values
	//! as column names. 
	//! Will define all values as being of type=wstring
	void BuildMetaData();

	//! @fn void SetMetaData( CEMSRecordMetaData* pMeta );
	//! Save the supplied meta data for use
	void	SetMetaData( CEMSRecordMetaData* pMeta );

	//! @fn CEMSRecordMetaData* GetMetaData();
	//! Return a copy of this reader's meta data
	//! Caller must release the pointer
	CEMSRecordMetaData* GetMetaData();

	//! @fn std::wstring GetAsStringW( const long clIndex )
	//! Retrieve the field at the specified index in string format.
	std::wstring GetFieldAsStringW( const long clIndex );

	//! @fn std::string GetFieldAsStringA( const long clIndex )
	//! Retrieve the field at the specified index in string format.
	std::string GetFieldAsStringA( const long clIndex );

	//! @fn std::wstring GetFieldAsStringW( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name in string format.
	std::wstring GetFieldAsStringW( const wchar_t* cwszColumn );

	//! @fn std::string GetFieldAsStringA( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name in string format.
	std::string GetFieldAsStringA( const wchar_t* cwszColumn );

	//! @fn ULONG GetFieldAsULong( const long clIndex )
	//! Retrieve the field at the specified index as  ULONG.
	ULONG GetFieldAsULong( const long clIndex );

	//! @fn ULONG GetFieldAsULong( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name.
	ULONG GetFieldAsULong( const wchar_t* cwszColumn );

	//! @fn EMSTIME GetFieldAsTime( const long clIndex )
	//! Retrieve the field with the specified index as an EMSTIME.
	EMSTIME GetFieldAsTime( const long clIndex );

	//! @fn EMSTIME GetFieldAsTime( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name.
	EMSTIME GetFieldAsTime( const wchar_t* cwszColumn );

	//! @fn double GetFieldAsDouble( const long clIndex )
	//! Retrieve the field with the specified index as a double.
	double GetFieldAsDouble( const long clIndex );

	//! @fn double GetFieldAsDouble( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name.
	double GetFieldAsDouble( const wchar_t* cwszColumn );

	//! @fn double GetFieldAsInt( const long clIndex )
	//! Retrieve the field with the specified index as an int.
	int GetFieldAsInt( const long clIndex );

	//! @fn int GetFieldAsInt( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name.
	int GetFieldAsInt( const wchar_t* cwszColumn );

	//! @fn void GetFieldAsDoubleArray( const long clIndex, double*& adValues, ULONG& ulElements )
	//! Retrieve the field with the specified index as an array of doubles.
	//! The caller must delete the returned array.
	void GetFieldAsDoubleArray( const long clIndex, double*& adValue, ULONG& ulElements ); 

	//! @fn void GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValues )
	//! Retrieve the field with the specified name as an array of doubles.
	//! The caller must delete the returned array.
	void GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValue, ULONG& ulElements ); 

	//! @fn void GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue );
	//! Retrieve the field with the specified index as an array of floats.
	//! The caller must allocate the array.
	void GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue );

	//! @fn void GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, float* afValue )
	//! Retrieve the field with the specified name as an array of doubles.
	//! The caller must allocate the array.
	void GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, float* afValue );

	//!@fn USHORT GetFieldAsUShort( const long clIndex )
	//! Retrieve the field at the specified index as an unsigned short.
	USHORT GetFieldAsUShort( const long clIndex );

	//!@fn USHORT GetFieldAsUShort( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name as an unsigned short.
	USHORT GetFieldAsUShort( const wchar_t* cwszColumn );

	//! @fn void GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, unsigned char* abyValue )
	//! Retrieve the field at the specified index as a byte array.
	//! The caller allocates the buffer (i.e., the binary array) and specifies its size.
	//! An exception will be thrown if the actual data is larger than the buffer.
	void GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, unsigned char* abyValue );

	//! @fn void GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, const ULONG culMaxArraySize, unsigned char* abyValue )
	//! Retrieve the field with the specified name as a byte array.
	//! The caller allocates the buffer (i.e., the binary array) and specifies its size.
	//! An exception will be thrown if the actual data is larger than the buffer.
	void GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, const ULONG culMaxArraySize, unsigned char* abyValue );

	//! @fn UINT64 GetFieldAsUI64( const long clIndex )
	//! Retrieve the field at the specified index as an unsigned 64 bit integer.
	UINT64 GetFieldAsUI64( const long clIndex );

	//! @fn UINT64 GetFieldAsUI64( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name as an unsigned 64 bit integer.
	UINT64 GetFieldAsUI64( const wchar_t* cwszColumn );

	//! @fn UINT64 GetFieldAsI64( const long clIndex )
	//! Retrieve the field at the specified index as a 64 bit integer.
	INT64 GetFieldAsI64( const long clIndex );

	//! @fn UINT64 GetFieldAsI64( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified name as a 64 bit integer.
	INT64 GetFieldAsI64( const wchar_t* cwszColumn );

	//! @fn float GetFieldAsFloat( const long clIndex )
	//! Retrieve the field at the specified index as a float.
	float GetFieldAsFloat( const long clIndex );

	//! @fn float GetFieldAsFloat( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified index as a float.
	float GetFieldAsFloat( const wchar_t* cwszColumn );

	//! @fn WORD GetFieldAsWord( const long clIndex )
	//! Retrieve the field at the specified index as a WORD.
	WORD GetFieldAsWord( const long clIndex );

	//! @fn WORD GetFieldAsWord( const wchar_t* cwszColumn )
	//! Retrieve the field with the specified index as a WORD.
	WORD GetFieldAsWord( const wchar_t* cwszColumn );

private:
	void					_parseCSVLine(	std::wstring& wstrLine, 
											const wchar_t cwcSeparator );

	wstring					_stripBlanks( const wstring& cwstrValue );

	wstring					_getValue( const int ciColumnIndex );
	string					_getValueA( const int ciColumnIndex );
	wstring					_getValue( const wchar_t* cwszColumn );
	string					_getValueA( const wchar_t* cwszColumn );

	std::vector<wstring>	m_vectCurrRow;
	CEMSRecordMetaData*		m_pMetaData;
};

#endif // __EMSCSVREADER_H__
