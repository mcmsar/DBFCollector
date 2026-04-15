/********************************************************************
*
*		Copyright (c) 2003-2005 by EMS Technologies, Inc.,
*							All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include <assert.h>
#include "emstypes.h"	// must precede tchar.h in order to compile on VMS.
#include <tchar.h>
#include "logmsgparam.h"

#include "convutility.h"

CEMSLogMsgParam::CEMSLogMsgParam( short sCapacity ) : m_lLength(0)
{
	memset( m_szString, 0, clMaxMsgSize*sizeof(TCHAR) );
	
	m_sCount		= 0;
	m_sCapacity		= 0;
	m_awszParams	= NULL;

	if ( sCapacity > 0 ) SetCapacity( sCapacity );
}

CEMSLogMsgParam::CEMSLogMsgParam( const CEMSLogMsgParam& msgParam )
{
	memset( m_szString, 0, clMaxMsgSize*sizeof(TCHAR) );
	memcpy( m_szString, msgParam.m_szString, clMaxMsgSize*sizeof(TCHAR) );
	m_lLength = msgParam.m_lLength;

	_CopyParams( msgParam );
}

CEMSLogMsgParam::~CEMSLogMsgParam()
{
	_ReleaseArray();
}

CEMSLogMsgParam&
CEMSLogMsgParam::operator+=( const TCHAR* szString )
{
	Add( szString );

	return *this;
}

CEMSLogMsgParam&
CEMSLogMsgParam::operator+=( const unsigned long ulValue )
{
	Add( ulValue );

	return *this;
}


void
CEMSLogMsgParam::Add( const TCHAR* cszString )
{
	_Add( cszString );
#if defined(UNICODE) || defined(_UNICODE)
	_AddToArray( cszString );
#else
	_AddToArray( CEMSConversionUtil::ConvertToString( cszString ).c_str() );
#endif
}

void
CEMSLogMsgParam::Add( const unsigned long ulValue )
{
	wstring wstr = CEMSConversionUtil::ConvertToString( ulValue ).c_str();
	AddString( wstr.c_str() );
}

void
CEMSLogMsgParam::AddDouble( const double dValue )
{
	wstring wstr = CEMSConversionUtil::ConvertToString( dValue ).c_str();
	AddString( wstr.c_str() );
}

void
CEMSLogMsgParam::AddX( const unsigned long ulValue )
{
	wstring	wstr = L"0x" + CEMSConversionUtil::HexULongToStringW( ulValue );
	AddString( wstr.c_str() );
}

void
CEMSLogMsgParam::Add64( const __int64 i64Value )
{
	wstring	wstr = CEMSConversionUtil::ConvertToString( i64Value );
	AddString( wstr.c_str() );
}

void
CEMSLogMsgParam::AddBeaconID( const __int64 i64BeaconID )
{
	wchar_t	wszDisplay[64];
	memset( wszDisplay, 0, 64*sizeof(wchar_t) );

	wchar_t	wszID[64];
	memset( wszID, 0, 64*sizeof(wchar_t) );

#ifdef WIN32
	swprintf( wszID, L"%I64X", i64BeaconID );
#elif defined(__VMS)
	swprintf( wszID, 64, L"%llx", i64BeaconID );
	for( int i = 0; i < 64; i++ )
	{
		towupper( wszID[i] );
	}
#else
#error Platform not supported.
#endif

	int	iLen = wcslen( wszID );

	int j = 0, i=0, c=0;

	// strip off leading 0x0
	while ( wszID[i] == L'0' || wszID[i] == L'x' && i<iLen ) i++;
	while ( i<iLen )
	{
		// Display as sets of 5 characters
		// separated by blanks
		wszDisplay[j++] = wszID[i++];
		c++;
		if ( c%5 == 0 && i<iLen)
		{
			wszDisplay[j++] = L' ';
		}
	}

	AddString( wszDisplay );
}

void
CEMSLogMsgParam::AddTimestamp( const EMSTIME ctimestamp )
{
	wstring	wszTimestamp = CEMSConversionUtil::ConvertToDateTimeHiResStringW( ctimestamp );
	AddString( wszTimestamp.c_str() );
}

void 
CEMSLogMsgParam::AddString( const wchar_t* cwszParam )
{
	if( cwszParam )
	{
		LPCTSTR	tsz = NULL;
#if defined(UNICODE) || defined(_UNICODE)
		tsz = cwszParam;
#else
		std::string szParam = CEMSConversionUtil::ConvertToString( cwszParam ).c_str();
		tsz = szParam.c_str();
#endif
		_Add( tsz );
		_AddToArray( cwszParam );
	}
}

CEMSLogMsgParam& 
CEMSLogMsgParam::operator=( const CEMSLogMsgParam& oRHS )
{
	Clear();

	memset( m_szString, 0, clMaxMsgSize*sizeof(TCHAR) );
	memcpy( m_szString, oRHS.m_szString, clMaxMsgSize*sizeof(TCHAR) );
	m_lLength = oRHS.m_lLength;
	m_sCapacity = oRHS.m_sCapacity;

	_CopyParams( oRHS );

	return *this;
}

void 
CEMSLogMsgParam::Clear()
{
	memset( m_szString, 0, clMaxMsgSize*sizeof(TCHAR) );
	_ReleaseArray();
	m_sCapacity		= 0;
}

bool
CEMSLogMsgParam::_IsSpace( long lLen )
{
	return lLen <= (clMaxMsgSize - m_lLength ) ? true : false;
}

void
CEMSLogMsgParam::SetCapacity( short sCapacity )
{
	assert( m_awszParams == NULL );

	m_awszParams = new wchar_t*[sCapacity];

	if ( m_awszParams )
	{
		memset( m_awszParams, 0, sCapacity*sizeof(wchar_t*) );
		m_sCapacity = sCapacity;
	}
}

void
CEMSLogMsgParam::_Add( const TCHAR* cszString )
{
	if( cszString )
	{
		long lLen = _tcslen( cszString );

		if( _IsSpace( lLen ) )
		{
			_tcscpy( &m_szString[m_lLength], cszString );
			m_lLength += _tcslen(cszString) + 1;
		}
	}
}

void
CEMSLogMsgParam::_AddToArray( const wchar_t* wsz )
{
	assert( wsz );

	if ( m_sCapacity == m_sCount )
	{
		wchar_t** awszTmp = m_awszParams;

		short	sTmp = m_sCapacity;
		m_awszParams = NULL;
		SetCapacity( m_sCapacity + 5 );
		if ( awszTmp )
		{
			memcpy( m_awszParams, awszTmp, sTmp*sizeof(wchar_t*) );
			delete[] awszTmp;
		}
	}
	
	int iLen = wcslen(wsz) + 1;
	m_awszParams[m_sCount] = new wchar_t[iLen];
	wcscpy( m_awszParams[m_sCount], wsz );
	m_sCount++;
}

void
CEMSLogMsgParam::_ReleaseArray()
{
	for ( int i=0; i<m_sCount; i++ )
	{
		delete[] m_awszParams[i];
		m_awszParams[i] = NULL;
	}
	delete[] m_awszParams;
	m_awszParams = NULL;
	m_sCount = 0;
}

void
CEMSLogMsgParam::_CopyParams( const CEMSLogMsgParam& msgParam )
{
	SetCapacity( msgParam.m_sCapacity );
	for ( int i=0; i<msgParam.m_sCount; i++ )
	{
		_AddToArray( msgParam.m_awszParams[i] );
	}
}


