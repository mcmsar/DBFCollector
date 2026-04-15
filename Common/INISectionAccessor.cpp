/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
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

#include "inisectionaccessor.h"
#include "emsexcpt.h"
#include "arrayhelper.h"

CEMSINISectionAccessor::CEMSINISectionAccessor()
{
}

CEMSINISectionAccessor::CEMSINISectionAccessor( const CEMSINISectionAccessor& x ) :
									m_owszSection(x.m_owszSection),
									m_owszSectionID(x.m_owszSectionID),
									m_omapKeyValues( x.m_omapKeyValues )
{
}

CEMSINISectionAccessor::~CEMSINISectionAccessor()
{
}

void 
CEMSINISectionAccessor::SetSection( const wchar_t* cwszSection, const wchar_t* cwszSectionID )
{
	if( cwszSection )
		m_owszSection = cwszSection;

	if( cwszSectionID )
		m_owszSectionID = cwszSectionID;
}

void
CEMSINISectionAccessor::Serialize( BYTE*& rabyBuf, ULONG& rulBufSize )
{
	m_omapKeyValues.MoveFirst();

	rulBufSize = 0;

	for( ULONG l = 0; l < m_omapKeyValues.Count(); l++ )
	{
		std::wstring owszKey;
		std::wstring owszValue;

		m_omapKeyValues.GetNext( owszKey, owszValue );

		CEMSArrayHelper::Concatenate( rabyBuf, rulBufSize, 
						(const BYTE*) owszKey.c_str(), (owszKey.length())*sizeof(wchar_t) );

		CEMSArrayHelper::Concatenate( rabyBuf, rulBufSize, 
						(const BYTE*) L"=", 1*sizeof(wchar_t) );

		if( !owszValue.empty() )
		{
			CEMSArrayHelper::Concatenate( rabyBuf, rulBufSize, 
							(const BYTE*) owszValue.c_str(), (owszValue.length())*sizeof(wchar_t) );


		}

		// Want to include the NULL terminator at the end of each line.
		CEMSArrayHelper::Concatenate( rabyBuf, rulBufSize, 
							(const BYTE*)  L"\0", 1*sizeof(wchar_t) );
		

	}

	// Null Terminate the array.
	CEMSArrayHelper::Concatenate( rabyBuf, rulBufSize, 
							(const BYTE*)  L"\0", 1*sizeof(wchar_t) );
		
}

void 
CEMSINISectionAccessor::Deserialize(const BYTE* cabyData, const ULONG culSize )
{
	if( cabyData )
	{
		int iBytesRead = 0;

		while( iBytesRead < culSize )
		{
			wchar_t wszTemp[ 1024];
			memset( wszTemp, 0, 1024*sizeof(wchar_t));

			wcsncpy( wszTemp, (const wchar_t*) (cabyData+iBytesRead), 1023 );

			iBytesRead += wcslen(wszTemp)*sizeof(wchar_t) + 1*sizeof(wchar_t);

			wchar_t* wszTok = wcstok( wszTemp, L"=" );

			if( !wszTok )
			{
				THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
			}

			std::wstring owszKey = wszTok;

			wszTok = wcstok( NULL, L"=" );

			if( wszTok )
			{
				std::wstring owszValue = wszTok;

				m_omapKeyValues.Add( owszKey, owszValue );
			}

		}
	}
}

void 
CEMSINISectionAccessor::AddKey( const wchar_t* cwszKey, const wchar_t* cwszKeyValue )
{
	// First, remove if it already exists.
	m_omapKeyValues.Remove( std::wstring( cwszKey ) );

	m_omapKeyValues.Add( std::wstring( cwszKey ), std::wstring( cwszKeyValue ) );
}