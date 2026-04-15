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

#ifndef __DB_RETRIEVER_DAL_CLIENT_H__
#define __DB_RETRIEVER_DAL_CLIENT_H__

#include "dataaccesshelperbase.h"
#include "pointerlist.h"

class CEMSRawDataRecord;
class CEMSRawDataRecordReader;

//! @class CEMSDBRetrieverDALClient
//! Client-side DAL accessor makes queries via base class.  
//! It breaks resultset buffer into records, but does not format the records.
class CEMSDBRetrieverDALClient : public CEMSDataAccessHelperBase
{
	public:
		CEMSDBRetrieverDALClient();
		CEMSDBRetrieverDALClient( const CEMSDBRetrieverDALClient& x );
		~CEMSDBRetrieverDALClient();

		//! @fn CEMSPointerList<CEMSRawDataRecord> GetDataRaw( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
		//! Execute the given query and return data as unformatted records.
		CEMSPointerList<CEMSRawDataRecord> GetDataRaw( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, 
													const wchar_t* cwszSQL );

		//! @fn CEMSPointerList<CEMSRawDataRecordReader> GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
		//! Execute the given query and return data as unformatted records.
		CEMSPointerList<CEMSRawDataRecordReader> GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, 
													const wchar_t* cwszSQL );

};

#endif