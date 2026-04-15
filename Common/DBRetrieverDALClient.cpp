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

#include "dbretrieverdalclient.h"
#include "rawdatarecord.h"
#include "rawdatarecordreader.h"

CEMSDBRetrieverDALClient::CEMSDBRetrieverDALClient()
{
}

CEMSDBRetrieverDALClient::CEMSDBRetrieverDALClient( const CEMSDBRetrieverDALClient& x )
{
}

CEMSDBRetrieverDALClient::~CEMSDBRetrieverDALClient()
{
}

CEMSPointerList<CEMSRawDataRecord> 
CEMSDBRetrieverDALClient::GetDataRaw( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
{
	return _GetDataRaw( pCacheID, culMaxRecords, cwszSQL );
}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDBRetrieverDALClient::GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
{
	return _GetData( pCacheID, culMaxRecords, cwszSQL );
}
