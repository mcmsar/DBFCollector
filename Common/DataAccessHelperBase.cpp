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

	$Log$
********************************************************************/
#pragma warning(disable:4786)

#include "dataaccesshelperbase.h"
#include "rawdatarecordreader.h"
#include "recordmetadata.h"
#include "rawdatarecord.h"
#include "emsexcpt.h"
#include "emstime.h"


CEMSDataAccessHelperBase::CEMSDataAccessHelperBase() : m_ulCallerID(0), m_ulCalleeID(0), m_ulChunkSize(0),
														m_ulFields(0), m_aFields(0)
{
}

CEMSDataAccessHelperBase::CEMSDataAccessHelperBase( const CEMSDataAccessHelperBase& x ) : m_ulCallerID( x.m_ulCallerID ),
																			m_ulCalleeID( x.m_ulCalleeID ),
																			m_ulChunkSize( x.m_ulChunkSize ),
																			m_owszDBCon( x.m_owszDBCon ),
																			m_ulFields(0),
																			m_aFields(0)
{
	_SaveMetaData( x.m_ulFields, x.m_aFields );
}

CEMSDataAccessHelperBase::~CEMSDataAccessHelperBase()
{
	if( m_aFields )
	{
		delete[] m_aFields;
		m_aFields = 0;
	}
}

void 
CEMSDataAccessHelperBase::Init( const ULONG culCallerID, const ULONG culCalleeID, const ULONG culChunkSize )
{
	m_ulCallerID = culCallerID;
	m_ulCalleeID = culCalleeID;
	m_ulChunkSize = culChunkSize;
}

void 
CEMSDataAccessHelperBase::SetDBConnection( const wchar_t* cwszCon )
{
	if( cwszCon )
	{
		m_owszDBCon = cwszCon;
	}
}

void 
CEMSDataAccessHelperBase::GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
{
	ulFields = 0;
	aFields = 0;

	if( m_aFields && m_ulFields )

	{
#ifdef _USING_COM_
		aFields = static_cast<EMSFIELDDESCRIPTOR*>(CoTaskMemAlloc( m_ulFields*sizeof(EMSFIELDDESCRIPTOR) ) );
#else
		aFields = new EMSFIELDDESCRIPTOR[ m_ulFields ];
#endif

		if( !aFields )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( aFields, 0, (m_ulFields)*sizeof(EMSFIELDDESCRIPTOR) );

		memcpy( aFields, m_aFields, (m_ulFields)*sizeof(EMSFIELDDESCRIPTOR) );

		ulFields = m_ulFields;
	}


}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDataAccessHelperBase::_GetData( const ULONG culMaxRecords, const wchar_t* cwszSQL, const bool cbPartial )
{
	CEMSPointerList<CEMSRawDataRecordReader> olstRecords;
	olstRecords.SetMaxSize( culMaxRecords );

	if( (0 == m_ulCallerID) || 
		(0 == m_ulCalleeID) )		// Chunk size can be zero to specify all in one shot.
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	EMSDALCACHEID cacheID = ( 1 == culMaxRecords ) ? DONTCACHE : INITIALDALCACHEID;
	bool bCacheOverflowed = false;
	ULONG ulTotalRecords = 0;
	ULONG ulRecordSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFields = 0;
	ULONG ulDataSize = 0;
	unsigned char* abyData = 0;

	try
	{
		m_oGtwyHelper.SetCallerID( m_ulCallerID );

		bool bFirstCall = true;

		do
		{
			ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

			if( (m_ulChunkSize > culMaxRecords) ||
				( 0 == m_ulChunkSize ) )
			{
				ulNumRecordsToRetrieve = culMaxRecords;
			}

			OutputDebugStringW( cwszSQL );

			// Could be calling GetData multiple times.  Only the first call requests the
			// field descriptions (meta data).  So, don't overwrite the variables holding this data as they
			// are needed to decode the raw data on each call.
			ULONG ulFieldsTemp = 0;
			EMSFIELDDESCRIPTOR* aFieldsTemp = 0;

			m_oGtwyHelper.GetData( m_ulCalleeID, &cacheID, ulNumRecordsToRetrieve, bFirstCall, 0, cwszSQL, 
									&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
									&ulFieldsTemp, &aFieldsTemp, &ulDataSize, &abyData );

			if( 0 != ulFieldsTemp )
				ulFields = ulFieldsTemp;

			if( aFieldsTemp )
			{
				_SaveMetaData( ulFieldsTemp, aFieldsTemp );

				if( aFields )
				{
					// Just in case.
					CoTaskMemFree( aFields );
					aFields = 0;
				}

				aFields = aFieldsTemp;
			}

			olstRecords += _ProcessData( ulFields, aFields, ulDataSize, abyData, ulRecordSize );

			bFirstCall = false;

			// Data has been copied into output list of records
			// Need to free memory returned by the GetData() call
			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		} while( ( NULLDALCACHEID != cacheID ) && 
				 ( olstRecords.Count() < culMaxRecords) &&
				 ( ulDataSize > 0 ) &&
				 !cbPartial );

		if( aFields )
		{
			CoTaskMemFree( aFields );
			aFields = 0;
		}

	
	}
	catch( ... )
	{
		if( aFields )
		{
			CoTaskMemFree( aFields );
			aFields = 0;
		}

		if( abyData )
		{
			CoTaskMemFree( abyData );
			abyData = 0;
		}

		throw;
	}

	return olstRecords;
}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDataAccessHelperBase::_GetDataA( const ULONG culMaxRecords, const wchar_t* cwszSQL )
{
	CEMSPointerList<CEMSRawDataRecordReader> olstRecords;

	EMSDALCACHEID cacheID = ( 1 == culMaxRecords ) ? DONTCACHE : INITIALDALCACHEID;
	bool bCacheOverflowed = false;
	ULONG ulTotalRecords = 0;
	ULONG ulRecordSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFields = 0;
	ULONG ulDataSize = 0;
	unsigned char* abyData = 0;

	try
	{
		if( 0 == m_ulCallerID ||
			0 == m_ulCalleeID )
		{
			// Call the DAL directly.  That is, don't get at it via the Gateway.

			bool bFirstCall = true;

			do

			{
				ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

				if( (m_ulChunkSize > culMaxRecords) ||
					( 0 == m_ulChunkSize ) )
				{
					ulNumRecordsToRetrieve = culMaxRecords;
				}

				OutputDebugStringW( cwszSQL );

				m_oDALClient.GetData( &cacheID, ulNumRecordsToRetrieve, bFirstCall, m_owszDBCon.c_str(), cwszSQL, 
										&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
										&ulFields, &aFields, &ulDataSize, &abyData );

				_SaveMetaData( ulFields, aFields );

				olstRecords += _ProcessData( ulFields, aFields, ulDataSize, abyData, ulRecordSize );

				if( aFields )
				{
					CoTaskMemFree( aFields );
					aFields = 0;
				}

				if( abyData )
				{
					CoTaskMemFree( abyData );
					abyData = 0;
				}

				bFirstCall = false;

			} while( ( NULLDALCACHEID != cacheID ) && 
					 ( olstRecords.Count() < culMaxRecords) &&
					 ( ulDataSize > 0 ) );
		}
		else
		{
			m_oGtwyHelper.SetCallerID( m_ulCallerID );

			bool bFirstCall = true;

			do
			{
				ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

				if( (m_ulChunkSize > culMaxRecords) ||
					( 0 == m_ulChunkSize ) )
				{
					ulNumRecordsToRetrieve = culMaxRecords;
				}

				OutputDebugStringW( cwszSQL );

				m_oGtwyHelper.GetData( m_ulCalleeID, &cacheID, ulNumRecordsToRetrieve, bFirstCall, 
										m_owszDBCon.c_str(), cwszSQL, 
										&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
										&ulFields, &aFields, &ulDataSize, &abyData );

				_SaveMetaData( ulFields, aFields );

				olstRecords += _ProcessData( ulFields, aFields, ulDataSize, abyData, ulRecordSize );

				if( aFields )
				{
					CoTaskMemFree( aFields );
					aFields = 0;
				}

				if( abyData )
				{
					CoTaskMemFree( abyData );
					abyData = 0;
				}

				bFirstCall = false;

			} while( ( NULLDALCACHEID != cacheID ) && 
					 ( olstRecords.Count() < culMaxRecords) &&
					 ( ulDataSize > 0 ) );
		}
	
	}
	catch( ... )
	{
		if( aFields )
		{
			CoTaskMemFree( aFields );
			aFields = 0;
		}

		if( abyData )
		{
			CoTaskMemFree( abyData );
			abyData = 0;
		}

		throw;
	}

	return olstRecords;
}


CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDataAccessHelperBase::_GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
{
	CEMSPointerList<CEMSRawDataRecordReader> olstRecords;

	bool bCacheOverflowed = false;
	ULONG ulTotalRecords = 0;
	ULONG ulRecordSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFields = 0;
	ULONG ulDataSize = 0;
	unsigned char* abyData = 0;

	const wchar_t* wszSQL = (NULLDALCACHEID != *pCacheID) && (DONTCACHE != *pCacheID) ? 0 : cwszSQL;

	try
	{
		if( 0 == m_ulCallerID ||
			0 == m_ulCalleeID )
		{



			ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

			if( (m_ulChunkSize > culMaxRecords) ||
				( 0 == m_ulChunkSize ) )
			{
				ulNumRecordsToRetrieve = culMaxRecords;
			}

			m_oDALClient.GetData( pCacheID, ulNumRecordsToRetrieve, true, m_owszDBCon.c_str(), wszSQL, 
									&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
									&ulFields, &aFields, &ulDataSize, &abyData );

			_SaveMetaData( ulFields, aFields );





			olstRecords += _ProcessData( ulFields, aFields, ulDataSize, abyData, ulRecordSize );



			if( aFields )
			{
				CoTaskMemFree( aFields );
				aFields = 0;
			}

			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		}
		else
		{
			m_oGtwyHelper.SetCallerID( m_ulCallerID );

			ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

			if( (m_ulChunkSize > culMaxRecords) ||
				( 0 == m_ulChunkSize ) )
			{
				ulNumRecordsToRetrieve = culMaxRecords;
			}

			OutputDebugStringW( cwszSQL );

			m_oGtwyHelper.GetData( m_ulCalleeID, pCacheID, ulNumRecordsToRetrieve, true, 
									m_owszDBCon.c_str(), wszSQL, 
									&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
									&ulFields, &aFields, &ulDataSize, &abyData );

			_SaveMetaData( ulFields, aFields );

			olstRecords += _ProcessData( ulFields, aFields, ulDataSize, abyData, ulRecordSize );

			if( aFields )
			{
				CoTaskMemFree( aFields );
				aFields = 0;
			}



			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		}
	
	}
	catch( ... )
	{
		if( aFields )
		{
			CoTaskMemFree( aFields );
			aFields = 0;
		}

		if( abyData )
		{
			CoTaskMemFree( abyData );
			abyData = 0;
		}

		throw;
	}

	return olstRecords;
}

CEMSPointerList<CEMSRawDataRecord> 
CEMSDataAccessHelperBase::_GetDataRaw( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const wchar_t* cwszSQL )
{
	CEMSPointerList<CEMSRawDataRecord>  olstRecords;

	bool bCacheOverflowed = false;
	ULONG ulTotalRecords = 0;
	ULONG ulRecordSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFields = 0;
	ULONG ulDataSize = 0;
	unsigned char* abyData = 0;

	const wchar_t* wszSQL = (NULLDALCACHEID != *pCacheID) && (DONTCACHE != *pCacheID) ? 0 : cwszSQL;

	try
	{
		if( 0 == m_ulCallerID ||
			0 == m_ulCalleeID )
		{

			ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

			if( (m_ulChunkSize > culMaxRecords) ||
				( 0 == m_ulChunkSize ) )
			{
				ulNumRecordsToRetrieve = culMaxRecords;
			}

			m_oDALClient.GetData( pCacheID, ulNumRecordsToRetrieve, false, m_owszDBCon.c_str(), wszSQL, 
									&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
									&ulFields, &aFields, &ulDataSize, &abyData );

			_SaveMetaData( ulFields, aFields );

			olstRecords += _ProcessDataRaw( ulDataSize, abyData, ulRecordSize );

			if( aFields )
			{
				CoTaskMemFree( aFields );
				aFields = 0;
			}

			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		}
		else
		{
			m_oGtwyHelper.SetCallerID( m_ulCallerID );

			ULONG ulNumRecordsToRetrieve = m_ulChunkSize;

			if( (m_ulChunkSize > culMaxRecords) ||
				( 0 == m_ulChunkSize ) )
			{
				ulNumRecordsToRetrieve = culMaxRecords;
			}

			OutputDebugStringW( cwszSQL );

			m_oGtwyHelper.GetData( m_ulCalleeID, pCacheID, ulNumRecordsToRetrieve, false, 
									m_owszDBCon.c_str(), wszSQL, 
									&bCacheOverflowed, &ulTotalRecords, &ulRecordSize,
									&ulFields, &aFields, &ulDataSize, &abyData );

			_SaveMetaData( ulFields, aFields );

			olstRecords += _ProcessDataRaw( ulDataSize, abyData, ulRecordSize );

			if( aFields )
			{
				CoTaskMemFree( aFields );
				aFields = 0;
			}

			if( abyData )
			{
				CoTaskMemFree( abyData );
				abyData = 0;
			}

		}
	
	}
	catch( ... )
	{
		if( aFields )
		{
			CoTaskMemFree( aFields );
			aFields = 0;
		}

		if( abyData )
		{
			CoTaskMemFree( abyData );
			abyData = 0;
		}

		throw;
	}

	return olstRecords;
}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDataAccessHelperBase::_ProcessData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFields,
									const ULONG culDataSize, const unsigned char* cabyData,
									const ULONG culRecordSize )
{
	CEMSPointerList<CEMSRawDataRecordReader> olstRecords;

	CEMSRecordMetaData* pMeta = 0;
	CEMSRawDataRecord* pRawData = 0;
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		pMeta = new CEMSRecordMetaData( culFields, caFields );

		if( !pMeta )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( culFields && caFields && culDataSize && cabyData && culRecordSize )
		{
			ULONG ulRecords = culDataSize / culRecordSize;

			for( ULONG l = 0; l < ulRecords; l++ )
			{
				pRawData = new CEMSRawDataRecord( culRecordSize, cabyData + l*culRecordSize ) ;

				if( !pRawData )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pDataReader = new CEMSRawDataRecordReader( pRawData, pMeta );

				if( !pDataReader )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				olstRecords.Add( pDataReader );

				pRawData->Release();
				pRawData = 0;

				pDataReader->Release();
				pDataReader = 0;
				
			}
		}

		pMeta->Release();
		pMeta = 0;
	}
	catch( ... )
	{
		if( pMeta )
		{
			pMeta->Release();
			pMeta = 0;
		}

		if( pRawData )
		{
			pRawData->Release();
			pRawData = 0;
		}

		if( pDataReader )
		{
			pDataReader->Release();
			pDataReader = 0;
		}

		throw;
	}

	return olstRecords;
}

CEMSPointerList<CEMSRawDataRecord> 
CEMSDataAccessHelperBase::_ProcessDataRaw( const ULONG culDataSize, const unsigned char* cabyData,
									const ULONG culRecordSize )
{
	CEMSPointerList<CEMSRawDataRecord>  olstRecords;

	CEMSRawDataRecord* pRawData = 0;

	try
	{
		if( culDataSize && cabyData && culRecordSize )
		{
			ULONG ulRecords = culDataSize / culRecordSize;

			for( ULONG l = 0; l < ulRecords; l++ )
			{
				pRawData = new CEMSRawDataRecord( culRecordSize, cabyData + l*culRecordSize ) ;

				if( !pRawData )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				olstRecords.Add( pRawData );

				pRawData->Release();
				pRawData = 0;

			}
		}

	}
	catch( ... )
	{
		if( pRawData )
		{
			pRawData->Release();
			pRawData = 0;
		}

		throw;
	}

	return olstRecords;
}

void
CEMSDataAccessHelperBase::_SaveMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFields )
{
	if( culFields && caFields )
	{
		if( m_aFields )
		{
			delete[] m_aFields;
			m_aFields = 0;
		}

		m_ulFields = 0;

		m_aFields = new EMSFIELDDESCRIPTOR[ culFields ];

		if( !m_aFields )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_aFields, 0, (culFields)*sizeof(EMSFIELDDESCRIPTOR) );

		memcpy( m_aFields, caFields, (culFields)*sizeof(EMSFIELDDESCRIPTOR) );

		m_ulFields = culFields;

	}
}
