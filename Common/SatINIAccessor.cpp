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

#include "satiniaccessor.h"
#include <windows.h>

const wchar_t* CEMSSatINIAccessor::ms_cwszAppName = L"SAT";
const int CEMSSatINIAccessor::ms_ciDefaultStringLen = 8192;

CEMSSatINIAccessor::CEMSSatINIAccessor()
{
}

CEMSSatINIAccessor::CEMSSatINIAccessor( const CEMSSatINIAccessor& x )
{
}

CEMSSatINIAccessor::~CEMSSatINIAccessor()
{
}

void 
CEMSSatINIAccessor::Load( const wchar_t* cwszSrcFile )
{

	// This should really go through all the satellites and load them up -- no time now though.


	if( cwszSrcFile )
	{
		m_owszFileName = cwszSrcFile;
	}
}

void 
CEMSSatINIAccessor::Save( const wchar_t* cwszDestFile )
{
	std::wstring owszOutput = m_owszFileName;

	if( cwszDestFile )
	{
		owszOutput = cwszDestFile;
	}

	m_omapSats.MoveFirst();

	for( ULONG l = 0; l < m_omapSats.Count(); l++ )
	{
		CEMSINISectionAccessor oSat = m_omapSats.GetNext();

		wchar_t wszSection[ 8 ];
		swprintf( wszSection, L"%s:%+03.3s", ms_cwszAppName, oSat.GetSectionID().c_str() );

		BYTE* abyBuf = 0;
		ULONG ulSize = 0;
		oSat.Serialize( abyBuf, ulSize );

		WritePrivateProfileSectionW( wszSection, (const wchar_t*) abyBuf, owszOutput.c_str() );

	}

}

bool 
CEMSSatINIAccessor::GetByNoradID( const ULONG culNoradID, CEMSINISectionAccessor& roData )
{
	return false;
}

bool 
CEMSSatINIAccessor::GetBySatID( const ULONG culSatID, CEMSINISectionAccessor& roData  )
{
	bool bRet = false;

	if( !m_owszFileName.empty() )
	{
		//m_omapSats.Clear();

		BYTE abyBuf[ ms_ciDefaultStringLen*sizeof(wchar_t) ];
		memset( abyBuf, 0, ms_ciDefaultStringLen*sizeof(wchar_t) );

		wchar_t wszSection[ 8 ];
		swprintf( wszSection, L"%s:%03.3d", ms_cwszAppName, culSatID );

		DWORD dwRet = GetPrivateProfileSectionW( wszSection, (wchar_t*) abyBuf, ms_ciDefaultStringLen, m_owszFileName.c_str() );

		if( dwRet > 0 )
			bRet = true;

		roData.Deserialize( abyBuf, dwRet*sizeof(wchar_t) );
		
	}

	return bRet;
	
}

void 
CEMSSatINIAccessor::Add( CEMSINISectionAccessor& roData )
{
	// Should first remove if it's already in the map.
	m_omapSats.Add( roData.GetSectionID(), roData );
}