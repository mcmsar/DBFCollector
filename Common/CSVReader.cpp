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
#pragma warning(disable:4786)

#include "CSVReader.h"
#include "RecordMetaData.h"
#include "convutility.h"
#include "emsexcpt.h"
#include "assert.h"

CEMSCSVReader::CEMSCSVReader() : m_pMetaData(NULL)
{
}
CEMSCSVReader::CEMSCSVReader( std::wstring& wstrLine, 
							  const wchar_t cwcSeparator, 
							  CEMSRecordMetaData* pMeta )
{
	m_pMetaData = pMeta;
	if ( m_pMetaData ) m_pMetaData->AddRef();

	_parseCSVLine( wstrLine, cwcSeparator );
}

CEMSCSVReader::CEMSCSVReader( const CEMSCSVReader& x ) 
: m_pMetaData(NULL), m_vectCurrRow( x.m_vectCurrRow )
{
	m_pMetaData = x.m_pMetaData;
	if ( m_pMetaData ) m_pMetaData->AddRef();
}

CEMSCSVReader::~CEMSCSVReader()
{
	Clear();
	if ( m_pMetaData )
	{
		m_pMetaData->Release();
		m_pMetaData = NULL;
	}
}

void
CEMSCSVReader::Clear()
{
	m_vectCurrRow.clear();
}

int
CEMSCSVReader::Init( std::wstring& wstrLine,
					 const wchar_t cwcSeparator, 
					 CEMSRecordMetaData* pMeta )
{
	Clear();

	if ( pMeta ) SetMetaData( pMeta ); // else leave current metadata in place

	_parseCSVLine( wstrLine, cwcSeparator );

	return( m_vectCurrRow.size() );
}

void
CEMSCSVReader::SetMetaData( CEMSRecordMetaData* pMeta )
{
	if ( m_pMetaData ) 
	{
		m_pMetaData->Release();
	}
	if ( pMeta )
	{
		pMeta->AddRef();
	}
	m_pMetaData = pMeta;
}

void
CEMSCSVReader::BuildMetaData()
{
	ULONG				ulCount = m_vectCurrRow.size();

	EMSFIELDDESCRIPTOR*	aDesc = new EMSFIELDDESCRIPTOR[ulCount];
	if ( !aDesc ) THROW_NOMEMORY_EXCEPTION();
	
	try
	{
		std::wstring	wstr;
		for( int i=0;i < ulCount; i++ )
		{
			wstr = _stripBlanks( m_vectCurrRow[i] );
			wcsncpy( aDesc[i].wszName, wstr.c_str(), MAX_FIELD_NAME );
		}
		if ( m_pMetaData ) 
		{
			m_pMetaData->Release();
			m_pMetaData = NULL;
		}
		m_pMetaData = new CEMSRecordMetaData( ulCount, aDesc );
		if ( !m_pMetaData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
		delete[] aDesc;
		aDesc = NULL;
	}
	catch(...)
	{
		if ( aDesc ) delete[] aDesc;
		if ( m_pMetaData )
		{
			m_pMetaData->Release();
			m_pMetaData = NULL;
		}
		throw;
	}
	return;
}

CEMSRecordMetaData* 
CEMSCSVReader::GetMetaData()
{
	if ( m_pMetaData ) m_pMetaData->AddRef();
	return m_pMetaData;
}


// Very simplistic function at this time...
// Does not check for escaped quote characters and probably should
void
CEMSCSVReader::_parseCSVLine( std::wstring& wstrLine, const wchar_t cwcSeparator )
{
	std::wstring	wszValue;

	std::wstring::size_type iOffset = 0;
	std::wstring::size_type iSepPos = std::wstring::npos;

	m_vectCurrRow.clear();
	do 
	{
		iSepPos = wstrLine.find( cwcSeparator, iOffset );
		if ( std::wstring::npos == iSepPos )
		{
			wszValue = wstrLine.substr( iOffset );
		}
		else
		{
			wszValue = wstrLine.substr( iOffset, (iSepPos - iOffset) );
			iOffset = iSepPos + 1;
		}

		// add to array 
		m_vectCurrRow.push_back( wszValue );

	} while ( std::wstring::npos != iSepPos );

	return;
}


std::wstring 
CEMSCSVReader::GetFieldAsStringW( const long clIndex )
{
	return( _getValue( clIndex ) );
}

std::string 
CEMSCSVReader::GetFieldAsStringA( const long clIndex )
{
	return( _getValueA( clIndex ) );
}

std::wstring
CEMSCSVReader::GetFieldAsStringW( const wchar_t* cwszColumn )
{
	return( _getValue( cwszColumn ) );
}

std::string
CEMSCSVReader::GetFieldAsStringA( const wchar_t* cwszColumn )
{
	return( _getValueA( cwszColumn ) );
}

ULONG 
CEMSCSVReader::GetFieldAsULong( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertToULong( wstrValue.c_str() );
}


ULONG 
CEMSCSVReader::GetFieldAsULong( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertToULong( wstrValue.c_str() );
}

EMSTIME 
CEMSCSVReader::GetFieldAsTime( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertToTime( wstrValue.c_str() );
}

EMSTIME 
CEMSCSVReader::GetFieldAsTime( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertToTime( wstrValue.c_str() );
}

double 
CEMSCSVReader::GetFieldAsDouble( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertToDouble( wstrValue.c_str() );
}

double 
CEMSCSVReader::GetFieldAsDouble( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertToDouble( wstrValue.c_str() );
}

int 
CEMSCSVReader::GetFieldAsInt( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return _wtoi( wstrValue.c_str() );
}

int 
CEMSCSVReader::GetFieldAsInt( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return _wtoi( wstrValue.c_str() );
}

void 
CEMSCSVReader::GetFieldAsDoubleArray( const long clIndex, double*& adValue, ULONG& ulElements )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void
CEMSCSVReader::GetFieldAsDoubleArray( const wchar_t* cwszColumn, double*& adValue, ULONG& ulElements )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSCSVReader::GetFieldAsFixedFloatArray( const long clIndex, const ULONG culElements, float* afValue )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSCSVReader::GetFieldAsFixedFloatArray( const wchar_t* cwszColumn, const ULONG culElements, float* afValue )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

USHORT 
CEMSCSVReader::GetFieldAsUShort( const long clIndex )
{
	return (USHORT )GetFieldAsULong( clIndex );
}

USHORT 
CEMSCSVReader::GetFieldAsUShort( const wchar_t* cwszColumn )
{
	return (USHORT )GetFieldAsULong( cwszColumn );
}

void 
CEMSCSVReader::GetFieldAsFixedBinaryArray( const long clIndex, const ULONG culMaxArraySize, unsigned char* abyValue )
{
	memset( abyValue, 0, culMaxArraySize );

	wstring wstrValue = _getValue( clIndex );

	double	dOffset = 0;
	BYTE	byValue = 0;
	wchar_t	wcValue[3];
	wcValue[0] = wcValue[1] = wcValue[2] = 0;

	const wchar_t*	wszValue = wstrValue.c_str();
	int				iLen = wcslen( wszValue );
	int				iCount = wstrValue.length()/2;

	if ( iCount > culMaxArraySize ) THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );

	for ( int i = 0, j=0; i<iCount; i++ )
	{
		unsigned long ulValue = 0;

		wcValue[0] = wstrValue[j++];
		wcValue[1] = wstrValue[j++];
		swscanf( wcValue, L"%x", &(ulValue) );
		abyValue[i] = (BYTE )ulValue;
	}
}

void 
CEMSCSVReader::GetFieldAsFixedBinaryArray( const wchar_t* cwszColumn, const ULONG culMaxArraySize, unsigned char* abyValue )
{
	long lIndex = m_pMetaData->GetIndex( cwszColumn );
	if ( lIndex == -1 )
	{
		assert( false );
		THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
	}

	GetFieldAsFixedBinaryArray( lIndex, culMaxArraySize, abyValue );
}

UINT64 
CEMSCSVReader::GetFieldAsUI64( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertHexStringToUInt64( wstrValue.c_str() );
}

UINT64 
CEMSCSVReader::GetFieldAsUI64( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertHexStringToUInt64( wstrValue.c_str() );
}

INT64 
CEMSCSVReader::GetFieldAsI64( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertHexStringToInt64( wstrValue.c_str() );
}

INT64 
CEMSCSVReader::GetFieldAsI64( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertHexStringToInt64( wstrValue.c_str() );
}

float 
CEMSCSVReader::GetFieldAsFloat( const long clIndex )
{
	wstring wstrValue = _getValue( clIndex );
	return CEMSConversionUtil::ConvertToFloat( wstrValue.c_str() );
}

float 
CEMSCSVReader::GetFieldAsFloat( const wchar_t* cwszColumn )
{
	wstring wstrValue = _getValue( cwszColumn );
	return CEMSConversionUtil::ConvertToFloat( wstrValue.c_str() );
}

WORD 
CEMSCSVReader::GetFieldAsWord( const long clIndex )
{
	WORD	wVal = GetFieldAsUShort( clIndex );
	return wVal;
}

WORD 
CEMSCSVReader::GetFieldAsWord( const wchar_t* cwszColumn )
{
	WORD	wVal = GetFieldAsUShort( cwszColumn );
	return wVal;
}
	
wstring
CEMSCSVReader::_getValue( const int ciColumnIndex )
{
	assert( ciColumnIndex >= 0 && ciColumnIndex < m_vectCurrRow.size() );
	assert( m_vectCurrRow.size() > 0 );
	return m_vectCurrRow[ciColumnIndex];
}
string
CEMSCSVReader::_getValueA( const int ciColumnIndex )
{
	return CEMSConversionUtil::ConvertToString( _getValue( ciColumnIndex ).c_str() );
}

wstring
CEMSCSVReader::_getValue( const wchar_t* cwszColumn )
{
	assert( m_pMetaData );
	assert( cwszColumn && wcslen(cwszColumn) > 0 );
	assert( m_vectCurrRow.size() > 0 );

	int iIndex = m_pMetaData->GetIndex( cwszColumn );

	if ( iIndex == -1 ) 
	{
		assert( false );
		THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
	}

	return  m_vectCurrRow[iIndex];
}

string
CEMSCSVReader::_getValueA( const wchar_t* cwszColumn )
{
	return CEMSConversionUtil::ConvertToString( _getValue( cwszColumn ).c_str() );
}

wstring
CEMSCSVReader::_stripBlanks( const wstring& cwstrValue )
{
	int		iChars = cwstrValue.length();
	wstring	wstrRet;

	// Identify leading whitespace
	int iStart = 0;
	while ( iStart < iChars && iswspace( cwstrValue[iStart]) ) iStart++;

	// Identify trailing whitespace, CR, LF
	int iEnd = iChars-1;
	while ( iEnd >= 0 
		&& (iswspace( cwstrValue[iEnd] )  
			|| 10 == cwstrValue[iEnd] 
			|| 13 == cwstrValue[iEnd] ) )
		iEnd--;

	int iCount = iEnd - iStart + 1;
	if ( iCount > 0 )
	{
		wstrRet = cwstrValue.substr( iStart, iCount );
	}
	return wstrRet;
}
