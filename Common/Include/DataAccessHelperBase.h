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
#ifndef __DATA_ACCESS_HELPER_BASE_H__
#define __DATA_ACCESS_HELPER_BASE_H__

#include "aobjbase.h"
#include "dal.h"
#include "gatewayhelper.h"
#include "objectlist.h"
#include "pointerlist.h"
#include "dalclient.h"

class CEMSRawDataRecordReader;
class CEMSRawDataRecord;

//! @class CEMSDataAccessHelperBase
//! Base class that can be used to access the DAL either locally or remotely.
//! Custom data accessors can be derived from this class.
class CEMSDataAccessHelperBase : public CApiObjBase
{
	public:
		CEMSDataAccessHelperBase();
		CEMSDataAccessHelperBase( const CEMSDataAccessHelperBase& x );
		virtual ~CEMSDataAccessHelperBase();

		//! @fn void Init( const ULONG culCallerID, const ULONG culCalleeID, const ULONG culChunkSize )
		//! Set the caller and callee (data source), and the retrieval chunk size.
		void Init( const ULONG culCallerID, const ULONG culCalleeID, const ULONG culChunkSize );

		//! @fn void SetDBConnection( const wchar_t* cwszCon )
		//! Set the database connection string.
		void SetDBConnection( const wchar_t* cwszCon );

		//! @fn void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
		//! Retrieve meta data describing the records held in the resource.
		void GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields );

	protected:
		CEMSPointerList<CEMSRawDataRecordReader> _GetData( const ULONG culMaxRecords, const wchar_t* cwszSQL, const bool cbPartial = false );

		//! Preserved during a merge operation.  This method allows direct DAL access (i.e., bypasses Gateway).
		CEMSPointerList<CEMSRawDataRecordReader> _GetDataA( const ULONG culMaxRecords, const wchar_t* cwszSQL );

		CEMSPointerList<CEMSRawDataRecordReader> _GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL );

		CEMSPointerList<CEMSRawDataRecord> _GetDataRaw( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL );

		CEMSPointerList<CEMSRawDataRecordReader> _ProcessData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFields,
													const ULONG culDataSize, const unsigned char* cabyData,
													const ULONG culRecordSize );

		CEMSPointerList<CEMSRawDataRecord> _ProcessDataRaw( const ULONG culDataSize, const unsigned char* cabyData,
													const ULONG culRecordSize );

		void _SaveMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFields );

	private:
		ULONG m_ulCallerID;
		ULONG m_ulCalleeID;
		ULONG m_ulChunkSize;
		std::wstring m_owszDBCon;
		
		ULONG m_ulFields;
		EMSFIELDDESCRIPTOR* m_aFields;


		CEMSGatewayHelper m_oGtwyHelper;
		CEMSDALClient m_oDALClient;
};

#endif