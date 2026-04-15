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
#pragma warning(disable:4786)

#include "rawdatarecordreader.h"
#include "recordmetadata.h"
#include "emserrormsgs.h"
#include "convutility.h"
#include "rawdatarecord.h"
#include "emsexcpt.h"
#include "emstime.h"

CEMSRawDataRecordReader::CEMSRawDataRecordReader() : m_pRec(0), m_pMeta(0)
{
}

CEMSRawDataRecordReader::CEMSRawDataRecordReader( const CEMSRawDataRecordReader& x ) : m_pRec(0), m_pMeta(0),
																				m_mapFormatInstructions( x.m_mapFormatInstructions )
{
	SetData( x.m_pRec, x.m_pMeta );
}

CEMSRawDataRecordReader::CEMSRawDataRecordReader( CEMSRawDataRecord* pRec, CEMSRecordMetaData* pMeta ) :
														 m_pRec(0), m_pMeta(0)
{
	SetData( pRec, pMeta );
}

CEMSRawDataRecordReader::~CEMSRawDataRecordReader()
{
	_Clear();
}

void 
CEMSRawDataRecordReader::SetData( CEMSRawDataRecord* pRec, CEMSRecordMetaData* pMeta )
{
	_Clear();

	try
	{
		if( pRec && pMeta )
		{
			m_pRec = pRec;
			m_pRec->AddRef();

			m_pMeta = pMeta;
			m_pMeta->AddRef();
		}
	}
	catch( ... )
	{
		_Clear();

		throw;
	}
}

CEMSRawDataRecord* 
CEMSRawDataRecordReader::GetRawData()
{
	CEMSRawDataRecord* pRet = m_pRec;

	if( pRet )
		pRet->AddRef();

	return pRet;
}

CEMSRecordMetaData* 
CEMSRawDataRecordReader::GetMetaData()
{
	CEMSRecordMetaData* pRet = m_pMeta;

	if( pRet )
		pRet->AddRef();

	return pRet;
}


std::wstring 
CEMSRawDataRecordReader::GetFieldAsStringW( const long clIndex )
{
	std::wstring wszRet;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		wszRet = _GetAsStringW( pData, cpstrDesc, pFmtInst );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return wszRet;
}

std::string 
CEMSRawDataRecordReader::GetFieldAsStringA( const long clIndex )
{
	return CEMSConversionUtil::ConvertToString( GetFieldAsStringW( clIndex ).c_str() );
}

std::wstring 
CEMSRawDataRecordReader::GetFieldAsStringW( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsStringW( lIndex );
}

std::string 
CEMSRawDataRecordReader::GetFieldAsStringA( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsStringA( lIndex );
}

ULONG
CEMSRawDataRecordReader::GetFieldAsULong( const long clIndex )
{
	ULONG ulRet = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		ulRet = _GetULong( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return ulRet;
}

ULONG 
CEMSRawDataRecordReader::GetFieldAsULong( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsULong( lIndex );
}

EMSTIME 
CEMSRawDataRecordReader::GetFieldAsTime( const long clIndex )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		timeRet.intTime = _GetI64( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return timeRet;
}

EMSTIME 
CEMSRawDataRecordReader::GetFieldAsTime( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsTime( lIndex );
}

double 
CEMSRawDataRecordReader::GetFieldAsDouble( const long clIndex )
{
	double dRet = 0.0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		dRet = _GetDouble( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return dRet;
}

double 
CEMSRawDataRecordReader::GetFieldAsDouble( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsDouble( lIndex );
}

int 
CEMSRawDataRecordReader::GetFieldAsInt( const long clIndex )
{
	int iRet = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		iRet = _GetInt( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return iRet;
}

int 
CEMSRawDataRecordReader::GetFieldAsInt( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsInt( lIndex );
}

void 
CEMSRawDataRecordReader::GetFieldAsDoubleArray( const long clIndex, double*& adValue, ULONG& ulElements )
{
	CEMSFieldFormatInstruction* pFmtInst = 0;

	ULONG ulBytes = 0;
	unsigned char* abyData = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		_GetBinary( pData, cpstrDesc->lSize, ulBytes, abyData );

		if( ulBytes > 0 && abyData )
		{
			ulElements = ulBytes / sizeof(double);

			if( ulElements > 0 )
			{
				adValue = new double[ ulElements ];

				if( !adValue )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( adValue, 0, ulElements*sizeof(double) );

				for( long l = 0; l < ulElements; l++ )
				{
					memcpy( &(adValue[l]), abyData + l*sizeof(double), sizeof(double) );
				}
			}
			
			delete[] abyData;
			abyData = 0;
		}

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		if( adValue )
		{
			delete[] adValue;
			adValue = 0;
		}

		throw;
	}
}

void 
CEMSRawDataRecordReader::GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValue, 
											   ULONG& ulElements )
{
	long lIndex = _GetIndex( cwszColumn );

	GetFieldAsDoubleArray( lIndex, adValue, ulElements );
}

void 
CEMSRawDataRecordReader::GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue )
{
	CEMSFieldFormatInstruction* pFmtInst = 0;

	ULONG ulBytes = 0;
	unsigned char* abyData = 0;

	try
	{
		const EMSFIELDDESCRIPTOR* cpstrDesc = 0;
		const unsigned char* pData = _GetRetrievalParameters( clIndex, cpstrDesc, pFmtInst );

		_GetBinary( pData, cpstrDesc->lSize, ulBytes, abyData );

		if( ulBytes > 0 && abyData )
		{
			ULONG ulElements = ulBytes / sizeof(float);

			if( ulElements > 0 )
			{
				if( ulElements > culElements )
				{
					throw CEMSException( EMS_OVERFLOW );
				}

				for( long l = 0; l < ulElements; l++ )
				{
					memcpy( &(afValue[l]), abyData + l*sizeof(float), sizeof(float) );
				}
			}
			
			delete[] abyData;
			abyData = 0;
		}

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		if( abyData )


		{
			delete[] abyData;
			abyData = 0;
		}

		throw;
	}
}

void 
CEMSRawDataRecordReader::GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, 
												   float* afValue )
{
	long lIndex = _GetIndex( cwszColumn );

	GetFieldAsFixedFloatArray( lIndex, culElements, afValue );
}


USHORT 
CEMSRawDataRecordReader::GetFieldAsUShort( const long clIndex )
{
	USHORT usRet = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		usRet = _GetUShort( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return usRet;
}

USHORT 
CEMSRawDataRecordReader::GetFieldAsUShort( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsUShort( lIndex );
}

void 
CEMSRawDataRecordReader::GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, 
													unsigned char* abyValue )
{
	if( 0 == culMaxArraySize || 0 == abyValue )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	CEMSFieldFormatInstruction* pFmtInst = 0;

	unsigned char* abyData = 0;
	ULONG ulBytes = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		_GetLongBinary( pData, cpstrDesc->lSize, ulBytes, abyData );

		if( ulBytes > 0 &&
			abyData )
		{
			if( ulBytes > culMaxArraySize )
			{
				throw CEMSException( EMS_BAD_PARAM );
			}

			memcpy( abyValue, abyData, ulBytes );

			delete[] abyData;
			abyData = 0;
		}
		
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		throw;
	}

}

void 
CEMSRawDataRecordReader::GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, 
													const ULONG culMaxArraySize, 
													unsigned char* abyValue )
{
	long lIndex = _GetIndex( cwszColumn );

	GetFieldAsFixedBinaryArray( lIndex, culMaxArraySize, abyValue );
}

UINT64 
CEMSRawDataRecordReader::GetFieldAsUI64( const long clIndex )
{
	UINT64 ui64Ret = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		ui64Ret = _GetUI64( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return ui64Ret;
}

UINT64 
CEMSRawDataRecordReader::GetFieldAsUI64( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsUI64( lIndex );
}

INT64 
CEMSRawDataRecordReader::GetFieldAsI64( const long clIndex )
{
	INT64 i64Ret = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		const EMSFIELDDESCRIPTOR* cpstrDesc = 0;
		const unsigned char* pData = _GetRetrievalParameters( clIndex, cpstrDesc, pFmtInst );


















		i64Ret = _GetI64( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return i64Ret;
}

INT64 
CEMSRawDataRecordReader::GetFieldAsI64( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsI64( lIndex );
}

float 
CEMSRawDataRecordReader::GetFieldAsFloat( const long clIndex )
{
	float fRet = 0.0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		fRet = _GetFloat( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return fRet;
}

float 
CEMSRawDataRecordReader::GetFieldAsFloat( const wchar_t* cwszColumn )
{
	long lIndex = _GetIndex( cwszColumn );

	return GetFieldAsFloat( lIndex );
}

BYTE 
CEMSRawDataRecordReader::GetFieldAsByte( const long clIndex )
{
	BYTE byRet = 0;

	CEMSFieldFormatInstruction* pFmtInst = 0;

	try
	{
		if( !m_pRec || !m_pMeta )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		long lOffset = _GetOffset( clIndex );

		const unsigned char* pData = m_pRec->GetPointerToBuffer();

		if( !pData )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pData += lOffset;

		const EMSFIELDDESCRIPTOR* cpstrDesc = _GetDescriptor( clIndex );

		pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

		byRet = _GetUChar( pData, cpstrDesc->lSize );

		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}
	}
	catch( ... )
	{
		if( pFmtInst )
		{
			pFmtInst->Release();
			pFmtInst = 0;
		}

		throw;
	}

	return byRet;
}

WORD
CEMSRawDataRecordReader::GetFieldAsWord( const wchar_t* cwszColumn )
{
	return GetFieldAsUShort( cwszColumn );
}


WORD
CEMSRawDataRecordReader::GetFieldAsWord( const long clIndex )
{
	return GetFieldAsUShort( clIndex );
}

void 
CEMSRawDataRecordReader::AddFormatInstruction( const long clIndex, 
											  CEMSFieldFormatInstruction* pFmtInst )
{
	m_mapFormatInstructions.Add( clIndex, pFmtInst );
}

void 
CEMSRawDataRecordReader::AddFormatInstruction( const wchar_t* cwszColumn, 
											  CEMSFieldFormatInstruction* pFmtInst )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSRawDataRecordReader::_Clear()
{
	if( m_pRec )
	{
		m_pRec->Release();
		m_pRec = 0;
	}

	if( m_pMeta )
	{
		m_pMeta->Release();
		m_pMeta = 0;
	}
}

long 
CEMSRawDataRecordReader::_GetOffset( const long clIndex )
{
	long lRet = 0;

	if( !m_pMeta )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	for( long l = 0; l < clIndex; l++ )
	{
		lRet += m_pMeta->GetSize( l );
	}

	return lRet;
}

const EMSFIELDDESCRIPTOR* 
CEMSRawDataRecordReader::_GetDescriptor( const long clIndex )
{
	if( !m_pMeta )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	return  m_pMeta->GetDescriptorPtr( clIndex );

}

short 
CEMSRawDataRecordReader::_GetShort( const unsigned char* cpData, const long clSize )
{
	short sRet = 0;

	if( clSize > sizeof(short) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &sRet, cpData, clSize );

	return sRet;
}

unsigned short 
CEMSRawDataRecordReader::_GetUShort( const unsigned char* cpData, const long clSize )
{
	unsigned short usRet = 0;

	if( clSize > sizeof(unsigned short) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &usRet, cpData, clSize );

	return usRet;
}

long 
CEMSRawDataRecordReader::_GetLong( const unsigned char* cpData, const long clSize )
{
	long lRet = 0;

	if( clSize > sizeof(long) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &lRet, cpData, clSize );

	return lRet;
}

int 
CEMSRawDataRecordReader::_GetInt( const unsigned char* cpData, const long clSize )
{
	int iRet = 0;

	if( clSize > sizeof(int) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &iRet, cpData, clSize );

	return iRet;
}

ULONG 
CEMSRawDataRecordReader::_GetULong( const unsigned char* cpData, const long clSize )
{
	ULONG ulRet = 0;

	if( clSize > sizeof(ULONG) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &ulRet, cpData, clSize );

	return ulRet;
}

INT64 
CEMSRawDataRecordReader::_GetI64( const unsigned char* cpData, const long clSize )
{
	INT64 i64Ret = 0;

	if( clSize > sizeof(INT64) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &i64Ret, cpData, clSize );

	return i64Ret;
}

UINT64 
CEMSRawDataRecordReader::_GetUI64( const unsigned char* cpData, const long clSize )
{
	UINT64 u64Ret = 0;

	if( clSize > sizeof(UINT64) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &u64Ret, cpData, clSize );

	return u64Ret;
}

std::wstring 
CEMSRawDataRecordReader::_GetWString( const unsigned char* cpData, const long clSize )
{
	std::wstring wszRet = 0;

	if( clSize < 1 )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	wchar_t* wszValue = new wchar_t[ clSize / sizeof(wchar_t) + 1 ];

	if( !wszValue )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memset( wszValue, 0, ( clSize / sizeof(wchar_t) + 1)*sizeof(wchar_t) );
	
	memcpy( wszValue, cpData, clSize );

	wszRet = wszValue;

	delete[] wszValue;
	wszValue = 0;

	return wszRet;
}

std::string 
CEMSRawDataRecordReader::_GetString( const unsigned char* cpData, const long clSize )
{
	std::string szRet = 0;

	if( clSize < 1 )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	char* szValue = new char[ clSize / sizeof(char) + 1 ];

	if( !szValue )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memset( szValue, 0, ( clSize / sizeof(char) + 1)*sizeof(char) );
	
	memcpy( szValue, cpData, clSize );

	szRet = szValue;

	delete[] szValue;
	szValue = 0;

	return szRet;
}

void
CEMSRawDataRecordReader::_GetBinary( const unsigned char* cpData, const long clSize, 
										ULONG& ulSize, unsigned char*& abyVal )
{
	ulSize = 0;
	abyVal = 0;

	if( clSize < 1 )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	abyVal = new unsigned char[ clSize ];

	if( !abyVal )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memcpy( abyVal, cpData, clSize );

	ulSize = clSize;
}

void
CEMSRawDataRecordReader::_GetLongBinary( const unsigned char* cpData, const long clSize, 
										ULONG& ulSize, unsigned char*& abyVal )
{
	_GetBinary( cpData, clSize, ulSize, abyVal );
}

float 
CEMSRawDataRecordReader::_GetFloat( const unsigned char* cpData, const long clSize )
{
	float fRet = 0;

	if( clSize > sizeof(float) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &fRet, cpData, clSize );

	return fRet;
}

double 
CEMSRawDataRecordReader::_GetDouble( const unsigned char* cpData, const long clSize )
{
	double dRet = 0;

	if( clSize > sizeof(double) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &dRet, cpData, clSize );

	return dRet;
}

char 
CEMSRawDataRecordReader::_GetChar( const unsigned char* cpData, const long clSize )
{
	char cRet = 0;

	if( clSize > sizeof(char) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &cRet, cpData, clSize );

	return cRet;
}

unsigned char 
CEMSRawDataRecordReader::_GetUChar( const unsigned char* cpData, const long clSize )
{
	unsigned char ucRet = 0;

	if( clSize > sizeof(unsigned char) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &ucRet, cpData, clSize );

	return ucRet;
}

bool 
CEMSRawDataRecordReader::_GetBool( const unsigned char* cpData, const long clSize )
{
	bool bRet = false;

	if( clSize > sizeof(bool) )
	{
		throw CEMSException( EMS_BAD_PARAM );
	}

	memcpy( &bRet, cpData, clSize );

	return bRet;
}

std::wstring
CEMSRawDataRecordReader::_GetAsStringW( const unsigned char* pData, const EMSFIELDDESCRIPTOR* cpstrDesc,
									   CEMSFieldFormatInstruction* pFmtInst )
{
	std::wstring wszRet;

	if( pData && cpstrDesc )
	{
		switch( cpstrDesc->eType )
		{
			case DBFLDTYPE_SHORT:
				{
					short sVal = _GetShort( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( sVal );
				}
				break;
			case DBFLDTYPE_USHORT:
				{
					unsigned short usVal = _GetUShort( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( usVal );
				}
				break;
			case DBFLDTYPE_LONG:
				{
					long lVal = _GetLong( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( lVal );
				}
				break;
			case DBFLDTYPE_ULONG:
				{
					ULONG ulVal = _GetULong( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( ulVal );
				}
				break;
			case DBFLDTYPE_BIGINT:
				{
					INT64 i64Val = _GetI64( pData, cpstrDesc->lSize );

					// This type supports special formatting instructions.
					if( pFmtInst )
					{
						if( FORMAT_DATETIME == pFmtInst->GetFormatType() )
						{
							// Assume, for now, Julian format okay.
							wchar_t wszFormattedDateTime[ 64 ];
							memset( wszFormattedDateTime, 0, 64*sizeof( wchar_t ) );

							EMSTIME timeTemp;
							timeTemp.intTime = i64Val;
							CEMSTime oTime( timeTemp );

							EMSTIMEFIELDS tmFields;
							oTime.GetTime( &tmFields );

							swprintf( wszFormattedDateTime, L"%04d/%03d %02d:%02d:%02d", tmFields.nYear,
																						 tmFields.nJulianDay,
																						 tmFields.nHour,
																						 tmFields.nMinute,
																						 tmFields.nSecond );

							wszRet = wszFormattedDateTime;
						}
					}
					else
					{
						wszRet = CEMSConversionUtil::ConvertToString( i64Val );
					}
				}
				break;
			case DBFLDTYPE_UBIGINT:
				{
					UINT64 ui64Val = _GetUI64( pData, cpstrDesc->lSize );

					if( pFmtInst )
					{
						if( FORMAT_DATETIME == pFmtInst->GetFormatType() )
						{
							// Assume, for now, Julian format okay.
							wchar_t wszFormattedDateTime[ 64 ];
							memset( wszFormattedDateTime, 0, 64*sizeof( wchar_t ) );

							EMSTIME timeTemp;
							timeTemp.intTime = ui64Val;
							CEMSTime oTime( timeTemp );

							EMSTIMEFIELDS tmFields;
							oTime.GetTime( &tmFields );

							swprintf( wszFormattedDateTime, L"%04d/%03d %02d:%02d:%02d", tmFields.nYear,
																						 tmFields.nJulianDay,
																						 tmFields.nHour,
																						 tmFields.nMinute,
																						 tmFields.nSecond );

							wszRet = wszFormattedDateTime;
						}
					}
					else
					{
						wszRet = CEMSConversionUtil::ConvertToString( ui64Val );
					}
				}
				break;
			case DBFLDTYPE_WSTRING:
				wszRet = _GetWString( pData, cpstrDesc->lSize );
				break;
			case DBFLDTYPE_STRING:
				{
					std::string szVal = _GetString( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( szVal.c_str() );
				}
				break;
			case DBFLDTYPE_BINARY:
				{
					ULONG ulSize = 0;
					unsigned char* abyVal;
					_GetBinary( pData, cpstrDesc->lSize, ulSize, abyVal );
					wszRet = CEMSConversionUtil::ConvertToString( ulSize, abyVal );

					if( abyVal )
					{
						delete[] abyVal;
						abyVal = 0;
					}
				}
				break;
			case DBFLDTYPE_LONG_BINARY:
				{
					ULONG ulSize = 0;
					unsigned char* abyVal;
					_GetLongBinary( pData, cpstrDesc->lSize, ulSize, abyVal );
					wszRet = CEMSConversionUtil::ConvertToString( ulSize, abyVal );

					if( abyVal )
					{
						delete[] abyVal;
						abyVal = 0;
					}
				}
				break;
			case DBFLDTYPE_FLOAT:
				{
					float fVal = _GetFloat( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( fVal );
				}
				break;
			case DBFLDTYPE_DOUBLE:
				{
					double dVal = _GetDouble( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( dVal );
				}
				break;
			case DBFLDTYPE_TINYINT:
				{
					char cVal = _GetChar( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( cVal );
				}
				break;
			case DBFLDTYPE_UTINYINT:
				{
					unsigned char ucVal = _GetUChar( pData, cpstrDesc->lSize );
					wszRet = CEMSConversionUtil::ConvertToString( ucVal );
				}
				break;
			case DBFLDTYPE_BOOLEAN:
				{
					bool bVal = _GetBool( pData, cpstrDesc->lSize );
					wszRet = bVal ? L"1" : L"0";
				}
				break;
			default:
				break;
				// Error here?
		}
	}
	
	return wszRet;

}

long 
CEMSRawDataRecordReader::_GetIndex( const wchar_t* cwszColumn )
{
	long lIndex = -1;

	if( cwszColumn )
	{
		if( m_pMeta )
		{
			lIndex = m_pMeta->GetIndex( cwszColumn );
		}
	}

	return lIndex;
}

const unsigned char*
CEMSRawDataRecordReader::_GetRetrievalParameters( const long clIndex, 
												 const EMSFIELDDESCRIPTOR*& cpstrDesc,
												 CEMSFieldFormatInstruction*& pFmtInst )
{
	const unsigned char* pData = m_pRec->GetPointerToBuffer();

	if( !pData )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	long lOffset = _GetOffset( clIndex );

	pData += lOffset;

	cpstrDesc = _GetDescriptor( clIndex );

	pFmtInst = m_mapFormatInstructions.Get( (long) clIndex);

	return pData;

}