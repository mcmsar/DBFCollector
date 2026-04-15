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

#include "dalorbit.h"
#include "sqlbuilder.h"
#include "emsdbfieldnames.h"
#include "lutdbschemainfo.h"
#include "convutility.h"
#include "recordmetadata.h"
#include "emsexcpt.h"
#include "rawdatarecord.h"

CEMSDALOrbit::CEMSDALOrbit()
{
}

CEMSDALOrbit::CEMSDALOrbit( const CEMSDALOrbit& x ) : m_oDALClient( x.m_oDALClient )
{
}

CEMSDALOrbit::~CEMSDALOrbit()
{
}

bool 
CEMSDALOrbit::GetTLE( const ULONG culSatID, const EMSTIME ctimeTLEEffective, EMSTLEDATA& rtleData )
{
	bool bRet = false;

	std::wstring owszSQL = _BuildTLESQL( culSatID, ctimeTLEEffective );

	EMSDALCACHEID cacheID = DONTCACHE;
	bool bOverflow = false;
	ULONG ulRecs = 0;
	ULONG ulRecSize = 0;
	ULONG ulFields = 0;
	EMSFIELDDESCRIPTOR* aFields = 0;
	ULONG ulDataSize = 0;
	BYTE* abyData = 0;

	try
	{

		m_oDALClient.GetData( &cacheID, 1, true, NULL, owszSQL.c_str(), &bOverflow, &ulRecs,
								&ulRecSize, &ulFields, &aFields, &ulDataSize, &abyData );

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _ProcessData( ulFields, aFields, 
																	ulDataSize, abyData, ulRecSize );

		if( olstRecords.Count() > 0 )
		{
			rtleData = _AssembleTLE( olstRecords );
			bRet = true;
		}

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

	return bRet;
}


std::wstring 
CEMSDALOrbit::_BuildTLESQL( const ULONG culSatID, const EMSTIME ctimeEffective )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 12;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszOrbitTimeEpoch;
	cawszColumns[1] = cwszOrbitXndt2o;
	cawszColumns[2] = cwszOrbitXndd6o;
	cawszColumns[3] = cwszOrbitBStar;
	cawszColumns[4] = cwszPassID;
	cawszColumns[5] = cwszOrbitCoVarMatrix;
	cawszColumns[6] = cwszOrbitInclination;
	cawszColumns[7] = cwszOrbitRightAscNode;
	cawszColumns[8] = cwszOrbitEccentricity;
	cawszColumns[9] = cwszOrbitArgPerigee;
	cawszColumns[10] = cwszOrbitMeanAnomaly;
	cawszColumns[11] = cwszOrbitMeanMotion;


	oSQLBuilder.AddSelectFirstOnly();
//	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_ORBIT, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	bool bConditionAdded = false;

	if( 0 != culSatID )
	{
		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeEffective.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEffective.intTime ).c_str();

		bConditionAdded = true;
	}

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

EMSTLEDATA 
CEMSDALOrbit::_AssembleTLE( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords )
{
	EMSTLEDATA strRet;
	memset( &strRet, 0, sizeof(EMSTLEDATA) );

	CEMSRawDataRecordReader* pDataReader = 0;

	double* adCoVar = 0;

	try
	{
		olstRecords.MoveFirst();

		pDataReader = olstRecords.GetNext();

		// Expecting maximum of 1 record.
		if( pDataReader )
		{
			strRet.timeEpoch = pDataReader->GetFieldAsTime( 0 );
			strRet.fXndt2o = pDataReader->GetFieldAsDouble( 1 );
			strRet.fXndd6o = pDataReader->GetFieldAsDouble( 2 );
			strRet.fBStar = pDataReader->GetFieldAsDouble( 3 );
			strRet.nOrbitNumber = pDataReader->GetFieldAsInt( 4 );
		
			ULONG ulElements = 0;
			pDataReader->GetFieldAsDoubleArray( 5, adCoVar, ulElements );

			if( adCoVar )
			{
				for( ULONG l = 0; l < (ulElements < (sizeof(strRet.fCoVarMatrix)/sizeof(double)) ? ulElements : (sizeof(strRet.fCoVarMatrix)/sizeof(double))); l++ )
				{
					strRet.fCoVarMatrix[l] = adCoVar[l];
				}

				delete[] adCoVar;
				adCoVar = 0;
			}

			strRet.elem.var.fInclination = pDataReader->GetFieldAsDouble( 6 );
			strRet.elem.var.fRightAscNode = pDataReader->GetFieldAsDouble( 7 );
			strRet.elem.var.fEccentricity = pDataReader->GetFieldAsDouble( 8 );
			strRet.elem.var.fArgPerigee = pDataReader->GetFieldAsDouble( 9 );
			strRet.elem.var.fMeanAnomaly = pDataReader->GetFieldAsDouble( 10 );
			strRet.elem.var.fMeanMotion = pDataReader->GetFieldAsDouble( 11 );

			pDataReader->Release();
			pDataReader = 0;
		}

	}
	catch( ... )
	{
		if( pDataReader )
		{
			pDataReader->Release();
			pDataReader = 0;
		}

		if( adCoVar )
		{
			delete[] adCoVar;
			adCoVar = 0;
		}

		throw;
	}

	return strRet;
}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDALOrbit::_ProcessData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caFields,
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