/********************************************************************
*
*		Copyright (c) 2004 by EMS Technologies, Inc.,
*							All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __VARIANT_RECORD_WRAPPER_H__
#define __VARIANT_RECORD_WRAPPER_H__

#include "dal.h"

#include <string>
using std::wstring;

//! @class CEMSVariantRecord
//! Wrapper around the EMSVARIANTRECORD data structure.
class CEMSVariantRecord
{
	public:
		CEMSVariantRecord();
		CEMSVariantRecord( const EMSVARIANTRECORD& cRecord );
		CEMSVariantRecord( const CEMSVariantRecord& x );
		~CEMSVariantRecord();

		//! @fn EMSTIME GetRecordTimestamp()
		//! Get the timestamp of the underlying record.
		EMSTIME GetRecordTimestamp();

		//! @fn void GetRecordData( unsigned long ulBufSize, unsigned char*& abyBuf )
		//! Extract the underlying data record.  That is, return the appropriate union member.
		void GetRecordData( unsigned long& ulBufSize, unsigned char*& abyBuf );

		//! @fn EMSRECORDTYPE GetType()
		//! Get the type of the underlying record
		EMSRECORDTYPE GetType() { return m_record.eType; }

		//! @fn wstring GetTypeString()
		//! Get the type of the underlying record as a string
		wstring		GetTypeString() { return GetRecordTypeString( m_record.eType ); }

		unsigned long GetRecordSize();

		//! Under Windows, the return data is allocated using CoTaskMemAlloc and caller must free
		//! using CoTaskMemFree.  Otherwise, the return data is allocated using new and must be deleted.
		static void Convert( const ULONG culRecs, const EMSVARIANTRECORD* caRecs, 
								ULONG* pulRecs, EMSVARIANTRECORD2** paRecs );

		//! Under Windows, the return data is allocated using CoTaskMemAlloc and caller must free
		//! using CoTaskMemFree.  Otherwise, the return data is allocated using new and must be deleted.
		static void Convert( const ULONG culRecs, const EMSVARIANTRECORD2* caRecs, 
								ULONG& rulRecs, EMSVARIANTRECORD*& raRecs );

		static wstring GetRecordTypeString( const EMSRECORDTYPE ceType );

	private:
		void _AllocBuffer( const unsigned long culSizeToAllocate, unsigned long& ulAllocated, unsigned char*& abyBuffer );

	private:
		EMSVARIANTRECORD	m_record;
};

class CEMSVariantRecord2
{
	public:
		CEMSVariantRecord2();
		CEMSVariantRecord2( const EMSVARIANTRECORD2& cRecord2 );
		CEMSVariantRecord2( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize );
		CEMSVariantRecord2( const CEMSVariantRecord2& x );
		~CEMSVariantRecord2();

		//! @fn EMSTIME GetRecordTimestamp()
		//! Get the timestamp of the underlying record.
		EMSTIME GetRecordTimestamp();

		//! @fn EMSRECORDTYPE GetType()
		//! Get the type of the underlying record
		EMSRECORDTYPE GetType() { return m_record2.eType; }

		//! @fn wstring GetTypeString()
		//! Get the type of the underlying record as a string
		wstring		GetTypeString() { return CEMSVariantRecord::GetRecordTypeString( m_record2.eType ); }

		// other functions can be added as necessary

		//! Convert a byte array into a EMSVARIANTRECORD2
		void SetData( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize );

		EMSVARIANTRECORD2 Get() { return m_record2; }

		static unsigned long GetRecordSize( const EMSRECORDTYPE ceType );

		static bool IsStatusRecordType( const EMSRECORDTYPE ceType );
		static EMSRECORDTYPE GetVariantRecordType( const EMSLEOSTATUSTYPE ceStatusType );
		static EMSLEOSTATUSTYPE GetStatusRecordType( const EMSRECORDTYPE ceType );

	private:
		EMSVARIANTRECORD	_getOlderRecord();

	private:
		EMSVARIANTRECORD2	m_record2;

};

class CEMSVariantRecord3
{
	public:
		CEMSVariantRecord3();
		CEMSVariantRecord3( const EMSVARIANTRECORD3& cRecord3 );
		CEMSVariantRecord3( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize );
		CEMSVariantRecord3( const CEMSVariantRecord3& x );
		~CEMSVariantRecord3();

		//! @fn EMSTIME GetRecordTimestamp()
		//! Get the timestamp of the underlying record.
		EMSTIME GetRecordTimestamp();

		//! @fn EMSRECORDTYPE GetType()
		//! Get the type of the underlying record
		EMSRECORDTYPE GetType() { return m_record3.eType; }

		//! @fn wstring GetTypeString()
		//! Get the type of the underlying record as a string
		wstring		GetTypeString() { return CEMSVariantRecord::GetRecordTypeString( m_record3.eType ); }

		// other functions can be added as necessary

		void GetVarRecord2( EMSVARIANTRECORD2& Record2 );
		void SetData( const EMSVARIANTRECORD2& cRecord2 );

		//! Convert a byte array into a EMSVARIANTRECORD3
		void SetData( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize );

		EMSVARIANTRECORD3 Get() { return m_record3; }

		static unsigned long GetRecordSize( const EMSRECORDTYPE ceType );

		static bool IsStatusRecordType( const EMSRECORDTYPE ceType );
		static EMSRECORDTYPE GetVariantRecordType( const EMSLEOSTATUSTYPE ceStatusType );
		static EMSLEOSTATUSTYPE GetStatusRecordType( const EMSRECORDTYPE ceType );

	private:
		EMSVARIANTRECORD2	_getOlderRecord();

	private:
		EMSVARIANTRECORD3	m_record3;

};

#endif
