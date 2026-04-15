/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#ifndef __RAW_DATA_RECORD_READER_H__
#define __RAW_DATA_RECORD_READER_H__

#include "DataReader.h"
#include "pointermap.h"
#include "fieldformatinstruction.h"

class CEMSRawDataRecord;
class CEMSRecordMetaData;

//! @class CEMSRawDataRecordReader
//! This class is used to read the values of fields
//! in a CEMSRawDataRecord.
class CEMSRawDataRecordReader :public CEMSDataReader

{
	public:
		CEMSRawDataRecordReader();
		CEMSRawDataRecordReader( const CEMSRawDataRecordReader& x );
		CEMSRawDataRecordReader( CEMSRawDataRecord* pRec, CEMSRecordMetaData* pMeta );
		virtual ~CEMSRawDataRecordReader();

		//! @fn void SetData( CEMSRawDataRecord* pRec,  CEMSRecordMetaData* pMeta )
		//! Store the raw data and data description.
		void SetData( CEMSRawDataRecord* pRec, CEMSRecordMetaData* pMeta );

		//! @fn CEMSRawDataRecord* GetRawData()
		//! Get a pointer to the raw data record.  The caller must Release the pointer.
		CEMSRawDataRecord* GetRawData();

		//! @fn CEMSRecordMetaData* GetMetaData()
		//! Get a pointer to the meta data for the record.  The caller must Release the pointer.
		CEMSRecordMetaData* GetMetaData();

		//! @fn std::wstring GetAsStringW( const long clIndex )
		//! Retrieve the field at the specified index in string format.
		std::wstring GetFieldAsStringW( const long clIndex );

		//! @fn std::string GetFieldAsStringA( const long clIndex )
		//! Retrieve the field at the specified index in string format.
		std::string GetFieldAsStringA( const long clIndex );

#ifdef UNICODE
		std::wstring GetFieldAsString( const long clIndex ) { return GetFieldAsStringW( clIndex ); }
#else
		std::string GetFieldAsString( const long clIndex ) { return GetFieldAsStringA( clIndex ); }
#endif

		//! @fn std::wstring GetFieldAsStringW( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name in string format.
		std::wstring GetFieldAsStringW( const wchar_t* cwszColumn );

		//! @fn std::string GetFieldAsStringA( const wchar_t* cwszColumn )
		//! Retrieve the field with the specified name in string format.
		std::string GetFieldAsStringA( const wchar_t* cwszColumn );

#ifdef UNICODE
		std::wstring GetFieldAsString( const wchar_t* cwszColumn) { return GetFieldAsStringW( cwszColumn ); }
#else
		std::string GetFieldAsString( const wchar_t* cwszColumn ) { return GetFieldAsStringA( cwszColumn ); }
#endif


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

		//! @fn void GetFieldAsDoubleArray( const long clIndex, double*& adValues )
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

		//! Retrieve the field at the specified index as a BYTE.
		BYTE GetFieldAsByte( const long clIndex );

		//! @fn void AddFormatInstruction( const long clIndex,  CEMSFieldFormatInstruction* pFmtInst )
		//! Set a format instruction for the field at index specified.
		void AddFormatInstruction( const long clIndex, CEMSFieldFormatInstruction* pFmtInst );

		//! @fn void AddFormatInstruction( const wchar_t* cwszColumn, CEMSFieldFormatInstruction* pFmtInst )
		//! Set a format instruction for the field specified.
		void AddFormatInstruction( const wchar_t* cwszColumn, CEMSFieldFormatInstruction* pFmtInst );

	private:
		void _Clear();
		std::wstring _GetAsStringW( const unsigned char* pData, const EMSFIELDDESCRIPTOR* cpstrDesc, 
										CEMSFieldFormatInstruction* pFmtInst  );
		long _GetOffset( const long clIndex );
		const EMSFIELDDESCRIPTOR* _GetDescriptor( const long clIndex );

		short _GetShort( const unsigned char* cpData, const long clSize );
		unsigned short _GetUShort( const unsigned char* cpData, const long clSize );
		long _GetLong( const unsigned char* cpData, const long clSize );
		int _GetInt( const unsigned char* cpData, const long clSize );
		ULONG _GetULong( const unsigned char* cpData, const long clSize );
		INT64 _GetI64( const unsigned char* cpData, const long clSize );
		UINT64 _GetUI64( const unsigned char* cpData, const long clSize );
		std::wstring _GetWString( const unsigned char* cpData, const long clSize );
		std::string _GetString( const unsigned char* cpData, const long clSize );
		void _GetBinary( const unsigned char* cpData, const long clSize, ULONG& ulSize, unsigned char*& abyVal );
		void _GetLongBinary( const unsigned char* cpData, const long clSize, ULONG& ulSize, unsigned char*& abyVal );
		float _GetFloat( const unsigned char* cpData, const long clSize );
		double _GetDouble( const unsigned char* cpData, const long clSize );
		char _GetChar( const unsigned char* cpData, const long clSize );
		unsigned char _GetUChar( const unsigned char* cpData, const long clSize );
		bool _GetBool( const unsigned char* cpData, const long clSize );

		const unsigned char* _GetRetrievalParameters( const long clIndex, 
										 const EMSFIELDDESCRIPTOR*& cpstrDesc,
										 CEMSFieldFormatInstruction*& pFmtInst );

		long _GetIndex( const wchar_t* cwszColumn );


	private:
		CEMSRawDataRecord* m_pRec;
		CEMSRecordMetaData* m_pMeta;

		CEMSPointerMap<long,CEMSFieldFormatInstruction> m_mapFormatInstructions;
};

#endif