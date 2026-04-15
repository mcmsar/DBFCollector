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

#include "datamonitordalclient.h"
#include "rawdatarecordreader.h"
#include "sqlbuilder.h"

CEMSDataMonitorDALClient::CEMSDataMonitorDALClient()
{
}

CEMSDataMonitorDALClient::CEMSDataMonitorDALClient( const CEMSDataMonitorDALClient& x ) : CEMSDataAccessHelperBase( x )
{
}

CEMSDataMonitorDALClient::~CEMSDataMonitorDALClient()
{
}

EMSTIME 
CEMSDataMonitorDALClient::GetTimestamp( const wchar_t* cwszTimestampField, const wchar_t* cwszTable,
									   const wchar_t* cwszAdditionalCriteria)
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	CEMSRawDataRecordReader* pRec = 0;

	try
	{
		std::wstring owszSQL = _GetLatestTimestampSQL( cwszTimestampField, cwszTable, cwszAdditionalCriteria );

		CEMSPointerList<CEMSRawDataRecordReader> olstData = _GetDataA( 1, owszSQL.c_str() );

		olstData.MoveFirst();

		// Only expecting one back, maximum.
		if( olstData.Count() > 0 )
		{
			pRec = olstData.GetNext();

			if( pRec )
			{
				timeRet = pRec->GetFieldAsTime( cwszTimestampField );

				pRec->Release();
				pRec = 0;
			}
		}
	}
	catch( ... )
	{
		if( pRec )
		{
			pRec->Release();
			pRec = 0;
		}

		throw;
	}

	return timeRet;
}

std::wstring
CEMSDataMonitorDALClient::_GetLatestTimestampSQL( const wchar_t* cwszField, const wchar_t* cwszTable,
												 const wchar_t* cwszAdditionalCriteria)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 1;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszField;

	oSQLBuilder.AddSelectFirstColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( cwszTable );

	if( cwszAdditionalCriteria && (wcslen(cwszAdditionalCriteria) > 0) )
	{
		oSQLBuilder.AddWhere( cwszAdditionalCriteria );
	}

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszField;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}