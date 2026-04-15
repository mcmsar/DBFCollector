/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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
#pragma warning(disable:4786)

#include "brrecords.h"
#include "brrecord.h"
#include "emsexcpt.h"

const wchar_t* CEMSBRRecords::ms_cwszRoot = L"dataroot";
const wchar_t* CEMSBRRecords::ms_cwszRootElement = L"<dataroot/>";

CEMSBRRecords::CEMSBRRecords() : CApiObjBase( TEXT("CEMSBRRecords") )
{
}

CEMSBRRecords::CEMSBRRecords( const wchar_t* cwszRecord ) : CApiObjBase( TEXT("CEMSBRRecords") )
{
	Set( cwszRecord );
}

CEMSBRRecords::CEMSBRRecords( const CEMSBRRecords& x ) : CApiObjBase( x ), m_oConfig( x.m_oConfig )
{
}

CEMSBRRecords::~CEMSBRRecords()
{
}

void 
CEMSBRRecords::Set( const wchar_t* cwszRecord )
{
	if( cwszRecord )
		m_oConfig.SetSource( cwszRecord );
}

std::wstring 
CEMSBRRecords::Get()
{
	return m_oConfig.Serialize();
}

ULONG 
CEMSBRRecords::GetCount()
{
	CEMSObjectList<CEMSConfigurationAccessor> olstBeacons = m_oConfig.GetAccessorList( CEMSBRRecord::ms_cwszRegistrationDB406 );

	return olstBeacons.Count();
}

void 
CEMSBRRecords::Add( const CEMSBRRecord& croBR )
{
	if( !m_oConfig.IsInitialized() )
		m_oConfig.SetSource( CEMSBRRecords::ms_cwszRootElement );

	m_oConfig.Insert( NULL, croBR.Get().c_str() );
}

CEMSPointerList<CEMSBRRecord> 
CEMSBRRecords::GetRecords()
{
	CEMSPointerList<CEMSBRRecord> olstRet;

	CEMSBRRecord* pRecord = NULL;

	try
	{
		CEMSObjectList<CEMSConfigurationAccessor> olstBeacons = m_oConfig.GetAccessorList( CEMSBRRecord::ms_cwszRegistrationDB406 );

		olstBeacons.MoveFirst();

		ULONG ulCount = olstBeacons.Count();

		for( ULONG l = 0; l < ulCount; l++ )
		{
			CEMSConfigurationAccessor oBeacon = olstBeacons.GetNext();
			
			pRecord = new CEMSBRRecord( oBeacon.Serialize().c_str() );

			if( !pRecord )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			olstRet.Add( pRecord );

			pRecord->Release();
			pRecord = NULL;

		}
	}
	catch( ... )
	{
		if( pRecord )
		{
			pRecord->Release();
			pRecord = NULL;
		}

		throw;
	}

	return olstRet;
}