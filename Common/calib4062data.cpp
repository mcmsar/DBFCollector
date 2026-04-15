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

	$Log$
********************************************************************/
#pragma warning(disable:4786)

#include "calib4062data.h"
#include "emsdbfieldnames.h"
#include "sqlbuilder.h"
#include "LutDBSchemaInfo.h"
#include "convutility.h"
#include "rawdatarecordreader.h"
#include "recordmetadata.h"
#include "rawdatarecord.h"


CEMSCalib4062Data::CEMSCalib4062Data()
{
}

CEMSCalib4062Data::CEMSCalib4062Data( const CEMSCalib4062Data& x )
{
}

CEMSCalib4062Data::~CEMSCalib4062Data()
{
}

CEMSObjectList<INT64> 
CEMSCalib4062Data::GetUniqueBeacons( const EMSTIME ctimeOldest )
{
	CEMSObjectList<INT64> olstRet;

	CEMSRawDataRecordReader* pReader = NULL;

	try
	{
		CSQLBuilder oSQLBuilder;
		oSQLBuilder.AddSelectDistinctColumns( 1, &cwszCalib406BeaconID );
		oSQLBuilder.AddFrom();
		oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_CALIB406_2, EMSDBVERSION_LEO_20 ).c_str() );
		oSQLBuilder.AddWhere();
		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGT();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeOldest.intTime ).c_str();

		CEMSPointerList<CEMSRawDataRecordReader> olstRawData;
		std::wstring owszSQL = oSQLBuilder;
		olstRawData = _GetData( 0L, owszSQL.c_str() );
		
		olstRawData.MoveFirst();

		while( pReader = olstRawData.GetNext() )
		{
			INT64 i64BeaconID = pReader->GetFieldAsI64( 0L );

			olstRet.Add( i64BeaconID );

			pReader->Release();
			pReader = NULL;
		}
	}
	catch( ... )
	{
		if( pReader )
		{
			pReader->Release();
			pReader = NULL;
		}

		throw;
	}

	return olstRet;
}

CEMSObjectList<EMSCALIB406DATA2> 
CEMSCalib4062Data::GetBeacons( const INT64 ci64BeaconID, const EMSTIME ctimeOldest )
{
	CEMSObjectList<EMSCALIB406DATA2> olstRet;

	CEMSRawDataRecordReader* pReader = NULL;

	try
	{
		CSQLBuilder oSQLBuilder;

		const short csColumns = 21;
		const LPCWSTR cawszColumns[ csColumns ] = { 
									cwszTimestamp, cwszLutID, cwszSatID, cwszType, 
									cwszCalib4062AntennaID, cwszPassID, cwszCalib406Status, cwszCalib406BeaconID,
									cwszCalib406TimeMsg, cwszCalib406TimeOffset, cwszCalib406Frequency, cwszCalib4062FreqOffset,
									cwszCalib4062CarrierPower, cwszCalib406BitErrorField1, cwszCalib406BitErrorField2, cwszCalib406BitErrorFrameSynch,
									cwszCalib406DuplicateMsgCount, cwszCalib406Msg, cwszCalib4062BitRate, cwszCalib4062DataFlags,
									cwszCalib4062ResolutionFlags
								 };

		oSQLBuilder.AddSelectColumns( csColumns, (const wchar_t**) cawszColumns );
		oSQLBuilder.AddFrom();
		oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_CALIB406_2, EMSDBVERSION_LEO_20 ).c_str() );
		oSQLBuilder.AddWhere();
		oSQLBuilder += cwszCalib406BeaconID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ci64BeaconID ).c_str();
		oSQLBuilder.AddAnd();
		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGT();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeOldest.intTime ).c_str();
		oSQLBuilder.AddOrderBy();
		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddDescending();

		CEMSPointerList<CEMSRawDataRecordReader> olstRawData;
		std::wstring owszSQL = oSQLBuilder;
		olstRawData = _GetData( 0L, owszSQL.c_str() );
		
		olstRawData.MoveFirst();

		while( pReader = olstRawData.GetNext() )
		{
			EMSCALIB406DATA2 beaconRec;
			memset( &beaconRec, 0, sizeof(EMSCALIB406DATA2) );

			beaconRec.hdr.id.time = pReader->GetFieldAsTime( 0L );
			beaconRec.hdr.id.ulLutID = pReader->GetFieldAsULong( 1 );
			beaconRec.hdr.id.ulSatID = pReader->GetFieldAsULong( 2 );
			beaconRec.hdr.wType = pReader->GetFieldAsUShort( 3 );
			beaconRec.wAntennaID = pReader->GetFieldAsUShort( 4 );
			beaconRec.ulPassID = pReader->GetFieldAsULong( 5 );
			beaconRec.wStatus = pReader->GetFieldAsUShort( 6 );
			beaconRec.i64BeaconID = pReader->GetFieldAsI64( 7 );
			beaconRec.timeMsg = pReader->GetFieldAsTime( 8 );
			beaconRec.i64TimeOffset = pReader->GetFieldAsI64( 9 );
			beaconRec.dFrequency = pReader->GetFieldAsDouble( 10 );
			beaconRec.dFreqOffset = pReader->GetFieldAsDouble( 11 );
			beaconRec.dCarrierPower = pReader->GetFieldAsDouble( 12 );
			beaconRec.wBitErrorField1 = pReader->GetFieldAsUShort( 13 );
			beaconRec.wBitErrorField2 = pReader->GetFieldAsUShort( 14 );
			beaconRec.wBitErrorFrameSynch = pReader->GetFieldAsUShort( 15 );
			beaconRec.wDuplicateMsgCount = pReader->GetFieldAsUShort( 16 );
			pReader->GetFieldAsFixedBinaryArray( 17, sizeof( beaconRec.cBeaconMsg ),
												(unsigned char*) beaconRec.cBeaconMsg );
			beaconRec.dBitRate = pReader->GetFieldAsDouble( 18 );
			beaconRec.dwDataFlags = pReader->GetFieldAsULong( 19 );
			beaconRec.dwResolutionFlags = pReader->GetFieldAsULong( 20 );

			olstRet.Add( beaconRec );

			pReader->Release();
			pReader = NULL;
		}
	}
	catch( ... )
	{
		if( pReader )
		{
			pReader->Release();
			pReader = NULL;
		}

		throw;
	}

	return olstRet;
}