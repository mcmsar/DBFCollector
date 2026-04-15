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

	$Log:
	$
********************************************************************/
#pragma warning(disable:4786)

#include "dburl.h"
#include "databaseresourcemsgs.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "dburlactiveparam.h"

const wchar_t* CEMSDBURL::ms_cwszMaxRecordsParam = L"maxrecords";
const wchar_t* CEMSDBURL::ms_cwszMaxBufferParam = L"maxbuffer";
const wchar_t* CEMSDBURL::ms_cwszSQLParam = L"sql";
const wchar_t* CEMSDBURL::ms_cwszDefaultConnection = L"DefaultDB";
const wchar_t* CEMSDBURL::ms_cwszActiveParam = L"active";

CEMSDBURL::CEMSDBURL()
{
}

CEMSDBURL::CEMSDBURL( const CEMSDBURL& x ) : CEMSURL( x )
{
}

CEMSDBURL::CEMSDBURL( const wchar_t* cwszURL ) : CEMSURL( cwszURL )
{
}

CEMSDBURL::~CEMSDBURL()
{
}

void 
CEMSDBURL::SetSQL( const wchar_t* cwszSQL )
{
	CEMSURLQuery oQuery = GetQuery();

	CEMSURLQueryParam oParam = oQuery.GetParam( ms_cwszSQLParam );

	oParam.Set( ms_cwszSQLParam, cwszSQL );

	// Replaces it if necessary.
	oQuery.AddParam( oParam );

	SetQuery( oQuery );
}

std::wstring 
CEMSDBURL::GetSQL()
{
	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszSQL = oQuery.GetParam( ms_cwszSQLParam ).GetValue();

	if( wszSQL.empty() )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( ms_cwszSQLParam );
		oParam.AddString( oQuery.Get().c_str() );

		throw CEMSException( EMS_DBRES_NO_QUERY_PARAM, oParam );
	}

	return wszSQL;
}

void 
CEMSDBURL::SetConnection( const wchar_t* cwszCon )
{
	std::wstring owszCon;

	if( cwszCon && (wcslen( cwszCon ) > 0) )
	{
		owszCon = cwszCon;
	}
	else
	{
		owszCon = ms_cwszDefaultConnection;
	}

	SetPath( owszCon.c_str() );
}

std::wstring 
CEMSDBURL::GetConnection()
{
	std::wstring wszRet;

	// The connection is contained in the Path of the URL.
	std::wstring wszPath = GetPath();

	if( ms_cwszDefaultConnection != wszPath )
	{
		wszRet = wszPath;
	}

	return wszRet;
}

void 
CEMSDBURL::SetChunkSize( const ULONG culChunkSize )
{
	CEMSURLQuery oQuery = GetQuery();

	CEMSURLQueryParam oParam = oQuery.GetParam( ms_cwszMaxRecordsParam );

	oParam.Set( ms_cwszMaxRecordsParam, CEMSConversionUtil::ConvertToString( culChunkSize ).c_str() );

	// Replaces it if necessary.
	oQuery.AddParam( oParam );

	SetQuery( oQuery );
}

ULONG 
CEMSDBURL::GetChunkSize()
{
	// Optional.  If not specified in the URL, use 0 which means all data at once.
	// i.e., no streaming.

	ULONG ulRet = 0;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszMaxRecords = oQuery.GetParam( ms_cwszMaxRecordsParam ).GetValue();

	if( !wszMaxRecords.empty() )
	{
		ulRet = CEMSConversionUtil::ConvertToULong( wszMaxRecords.c_str() );
	}

	return ulRet;
}

void 
CEMSDBURL::SetMaxBufferSize( const ULONG culMaxSize )
{
	CEMSURLQuery oQuery = GetQuery();

	CEMSURLQueryParam oParam = oQuery.GetParam( ms_cwszMaxBufferParam );

	oParam.Set( ms_cwszMaxBufferParam, CEMSConversionUtil::ConvertToString( culMaxSize ).c_str() );

	// Replaces it if necessary.
	oQuery.AddParam( oParam );

	SetQuery( oQuery );
}

ULONG 
CEMSDBURL::GetMaxBufferSize()
{
	// Optional.  If not specified in the URL, use 0.

	ULONG ulRet = 0;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszMaxRecords = oQuery.GetParam( ms_cwszMaxBufferParam ).GetValue();

	if( !wszMaxRecords.empty() )
	{
		ulRet = CEMSConversionUtil::ConvertToULong( wszMaxRecords.c_str() );
	}

	return ulRet;
}

std::wstring 
CEMSDBURL::GetActiveTable()
{
	std::wstring wszRet;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszActive = oQuery.GetParam( ms_cwszActiveParam ).Get();

	// Optional
	if( !wszActive.empty() )
	{
		CEMSDBURLActiveParam oActiveParam;
		oActiveParam.Set( wszActive.c_str() );

		wszRet = oActiveParam.GetTable();
	}

	return wszRet;
}

std::wstring 
CEMSDBURL::GetActiveColumn()
{
	std::wstring wszRet;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszActive = oQuery.GetParam( ms_cwszActiveParam ).Get();

	// Optional
	if( !wszActive.empty() )
	{
		CEMSDBURLActiveParam oActiveParam;
		oActiveParam.Set( wszActive.c_str() );

		wszRet = oActiveParam.GetColumn();
	}

	return wszRet;
}

std::wstring 
CEMSDBURL::GetActiveCriteria()
{
	std::wstring wszRet;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszActive = oQuery.GetParam( ms_cwszActiveParam ).Get();

	// Optional
	if( !wszActive.empty() )
	{
		CEMSDBURLActiveParam oActiveParam;
		oActiveParam.Set( wszActive.c_str() );

		wszRet = oActiveParam.GetCriteria();
	}

	return wszRet;
}

ULONG 
CEMSDBURL::GetActiveTestPeriod()
{
	ULONG ulRet = 0;

	CEMSURLQuery oQuery = GetQuery();

	std::wstring wszActive = oQuery.GetParam( ms_cwszActiveParam ).Get();

	// Optional
	if( !wszActive.empty() )
	{
		CEMSDBURLActiveParam oActiveParam;
		oActiveParam.Set( wszActive.c_str() );

		ulRet = oActiveParam.GetPeriod();
	}

	return ulRet;
}