/********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "glosatidlookup.h"
#include "convutility.h"

const wchar_t* CEMSGloSatIDLookup::cwszLookupByChannelSlot = L"sat[@slot=\"%d\" and @channel=\"%d\"]/@satid";
const wchar_t* CEMSGloSatIDLookup::cwszLookupByNoradNum = L"sat[@noradid=\"%d\"]/@satid";


CEMSGloSatIDLookup::CEMSGloSatIDLookup()
{
}

CEMSGloSatIDLookup::CEMSGloSatIDLookup( const CEMSGloSatIDLookup& x ) : m_oTable( x.m_oTable )
{
}

CEMSGloSatIDLookup::~CEMSGloSatIDLookup()
{
}

void 
CEMSGloSatIDLookup::Init( const wchar_t* cwszLookupFile )
{
	m_oTable.SetSourceFile( cwszLookupFile );
}

ULONG 
CEMSGloSatIDLookup::GetSatID( const long clChannel, const long clSlot )
{
	ULONG ulSatID = 0;

	wchar_t wszQuery[64];
	swprintf( wszQuery, cwszLookupByChannelSlot, clSlot, clChannel );

	ulSatID = _DoLookup( wszQuery );


	return ulSatID;
}

ULONG 
CEMSGloSatIDLookup::GetSatID( const ULONG culNoradNumber )
{
	ULONG ulSatID = 0;

	wchar_t wszQuery[64];
	swprintf( wszQuery, cwszLookupByNoradNum, culNoradNumber );

	ulSatID = _DoLookup( wszQuery );

	return ulSatID;
}

ULONG
CEMSGloSatIDLookup::_DoLookup( const wchar_t* cwszQuery )
{
	ULONG ulRet = 0;

	std::wstring owszSatID = m_oTable.GetAttributeValue( cwszQuery );

	if( owszSatID.length() > 0 )
	{
		ulRet = CEMSConversionUtil::ConvertToULong(owszSatID.c_str() );
	}

	return ulRet;

}