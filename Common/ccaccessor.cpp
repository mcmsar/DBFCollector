/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/

#include "ccaccessor.h"
#include "textfilereader.h"
#include "convutility.h"
#include "emsexcpt.h"

CEMSCCAccessor::CEMSCCAccessor()
{
}

CEMSCCAccessor::CEMSCCAccessor( const CEMSCCAccessor& x ) : m_oszFilePath(x.m_oszFilePath), 
															m_oszPwd(x.m_oszPwd),
															m_osetCCs(x.m_osetCCs)
{
}

CEMSCCAccessor::~CEMSCCAccessor()
{
}

void 
CEMSCCAccessor::Init( const char* cszFile, const char* cszPwd )
{
	if( cszFile )
	{
		m_oszFilePath = cszFile;
	}

	if( cszPwd )
	{
		m_oszPwd = cszPwd;
	}

}

CEMSObjectSet<ULONG> 
CEMSCCAccessor::GetCountryCodes()
{
	CEMSObjectSet<ULONG> osetRet;

	if( m_osetCCs.Count() < 1 )
	{
		_ReadCountryCodes();
	}

	osetRet = m_osetCCs;

	return osetRet;
}

void 
CEMSCCAccessor::SetCountryCodes( const ULONG culNum, const ULONG* caulCodes )
{
	if( caulCodes )
	{
		m_osetCCs.Clear();

		for( ULONG l = 0; l < culNum; l++ )
		{
			m_osetCCs.Add( caulCodes[l] );
		}
	}
}

bool 
CEMSCCAccessor::IsInSet( const ULONG culCode )
{
	bool bRet = false;

	if( m_osetCCs.Count() < 1 )
	{
		_ReadCountryCodes();
	}

	bRet = m_osetCCs.IsInSet( culCode );

	return bRet;
}

void 
CEMSCCAccessor::_ReadCountryCodes()
{
	// For now, no encryption handling.
	if( !m_oszFilePath.empty() )
	{
		m_osetCCs.Clear();

		wchar_t* wszTemp = NULL;

		try
		{
			m_ocsFileAccess.Enter();

			CEMSTextFileReader oTextFileReader;
			std::wstring owszData = oTextFileReader.ReadAll( CEMSConversionUtil::ConvertToString( m_oszFilePath.c_str() ).c_str() );

			if( !owszData.empty())
			{
				wszTemp = wcsdup( owszData.c_str() );

				if( !wszTemp )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				wchar_t* wszTok = wcstok( wszTemp, L"\r\n" );

				while( wszTok )
				{
					ULONG ulCode = CEMSConversionUtil::ConvertToULong( wszTok );

					m_osetCCs.Add( ulCode );

					wszTok = wcstok( NULL, L"\r\n" );
				}

				delete[] wszTemp;
				wszTemp = NULL;
			}

			m_ocsFileAccess.Leave();
		}
		catch( ... )
		{
			if( wszTemp )
			{
				delete[] wszTemp;
				wszTemp = NULL;
			}

			m_ocsFileAccess.Leave();
			throw;
		}

	}
}