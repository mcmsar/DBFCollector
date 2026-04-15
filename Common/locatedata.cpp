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

#include "locatedata.h"
#include "emsdbfieldnames.h"
#include "sqlbuilder.h"
#include "LutDBSchemaInfo.h"
#include "convutility.h"
#include "rawdatarecordreader.h"
#include "recordmetadata.h"
#include "rawdatarecord.h"


CEMSLocateData::CEMSLocateData()
{
}

CEMSLocateData::CEMSLocateData( const CEMSLocateData& x )
{
}

CEMSLocateData::~CEMSLocateData()
{
}

CEMSObjectList<INT64> 
CEMSLocateData::GetUniqueBeacons( const EMSTIME ctimeOldest )
{
	CEMSObjectList<INT64> olstRet;

	CEMSRawDataRecordReader* pReader = NULL;

	try
	{
		CSQLBuilder oSQLBuilder;
		oSQLBuilder.AddSelectDistinctColumns( 1, &cwszLocateBeaconID );
		oSQLBuilder.AddFrom();
		oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOCATE, EMSDBVERSION_LEO_20 ).c_str() );
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

CEMSObjectList<EMSLOCATE> 
CEMSLocateData::GetLocations( const INT64 ci64BeaconID, const EMSTIME ctimeOldest )
{
	CEMSObjectList<EMSLOCATE> olstRet;

	CEMSRawDataRecordReader* pReader = NULL;

	try
	{
		CSQLBuilder oSQLBuilder;

		const short csColumns = 38;
		const LPCWSTR cawszColumns[ csColumns ] = { cwszTimestamp, cwszLutID, cwszType, 
								cwszLocateSatIDs, cwszPassID, 
								cwszLocateLutIDs, cwszLocateBeaconID, cwszLocateNumMsgs, 
								cwszLocateNumMsgsUsed, cwszLocateNumIterations, cwszLocateTimeTCA,
								cwszLocateWindowsFactor, cwszLocateFrequency, cwszLocateConfidence,
								cwszLocateProbability, cwszLocatePower, cwszLocateRadiusErrEllipse,
								cwszLocateFreqBiasError, cwszLocateFreqDrift, cwszLocateCrossTrackAngle,
								cwszLocateMajorError, cwszLocateMinorError, cwszLocateHeading,
								cwszLocateNoise, cwszLocateTrend, cwszLocateCoVarianceMatrix,
								cwszLocateDegLatitude, cwszLocateDegLongitude, cwszLocateAltitude,
								cwszLocateNumBurstsUsed, cwszLocateDataStartTime, cwszLocateDataEndTime,
								cwszLocateSweep, cwszLocateSweepError, cwszLocateSidebands, 
								cwszLocateBeaconMsg, cwszLocateBitErrorField1, cwszLocateBitErrorField2
								 };

		oSQLBuilder.AddSelectColumns( csColumns, (const wchar_t**) cawszColumns );
		oSQLBuilder.AddFrom();
		oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOCATE, EMSDBVERSION_LEO_20 ).c_str() );
		oSQLBuilder.AddWhere();
		oSQLBuilder += cwszLocateBeaconID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ci64BeaconID ).c_str();
		oSQLBuilder.AddAnd();
		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGT();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeOldest.intTime ).c_str();
		oSQLBuilder.AddOrderBy();
		oSQLBuilder.AddDescending();
		oSQLBuilder += cwszTimestamp;

		CEMSPointerList<CEMSRawDataRecordReader> olstRawData;
		std::wstring owszSQL = oSQLBuilder;
		olstRawData = _GetData( 0L, owszSQL.c_str() );
		
		olstRawData.MoveFirst();

		while( pReader = olstRawData.GetNext() )
		{
			EMSLOCATE locateRec;
			memset( &locateRec, 0, sizeof(EMSLOCATE) );

			locateRec.time = pReader->GetFieldAsTime( 0L );
			locateRec.ulLutID = pReader->GetFieldAsULong( 1 );
			locateRec.wType = pReader->GetFieldAsUShort( 2 );
			pReader->GetFieldAsFixedBinaryArray( 3, sizeof( locateRec.cSatIDs ), 
												(unsigned char*) locateRec.cSatIDs );
			locateRec.ulSatPassID = pReader->GetFieldAsULong( 4 );
			pReader->GetFieldAsFixedBinaryArray( 5, sizeof( locateRec.cLutIDs ),
												(unsigned char*) locateRec.cLutIDs );
			locateRec.i64BeaconID = pReader->GetFieldAsUI64( 6 );
			locateRec.wlsSolution.wNumMsgs = pReader->GetFieldAsUShort( 7 );
			locateRec.wlsSolution.wNumMsgsUsed = pReader->GetFieldAsUShort( 8 );
			locateRec.wlsSolution.wNumIterations = pReader->GetFieldAsUShort( 9 );
			locateRec.timeTCA = pReader->GetFieldAsTime( 10 );
			locateRec.wWindowFactor = pReader->GetFieldAsUShort( 11 );
			locateRec.wlsSolution.dFrequency = pReader->GetFieldAsDouble( 12 );
			locateRec.fConfidence = pReader->GetFieldAsFloat( 13 );
			locateRec.fProbability = pReader->GetFieldAsFloat( 14 );
			locateRec.fPower = pReader->GetFieldAsFloat( 15 );
			locateRec.wlsSolution.fRadiusErrEllipse = pReader->GetFieldAsFloat( 16 );
			locateRec.wlsSolution.fFreqBiasError = pReader->GetFieldAsFloat( 17 );
			locateRec.wlsSolution.fFreqDrift = pReader->GetFieldAsFloat( 18 );
			locateRec.fCrossTrackAngle = pReader->GetFieldAsFloat( 19 );
			locateRec.wlsSolution.fMajorError = pReader->GetFieldAsFloat( 20 );
			locateRec.wlsSolution.fMinorError = pReader->GetFieldAsFloat( 21 );
			locateRec.wlsSolution.fHeading = pReader->GetFieldAsFloat( 22 );
			locateRec.wlsSolution.fRMS = pReader->GetFieldAsFloat( 23 );
			locateRec.wlsSolution.fTrend = pReader->GetFieldAsFloat( 24 );
			pReader->GetFieldAsFixedBinaryArray( 25, 
											sizeof( locateRec.wlsSolution.fCoVarianceMatrix ),
											(unsigned char*) locateRec.wlsSolution.fCoVarianceMatrix );
			locateRec.wlsSolution.location.degLatitude = pReader->GetFieldAsDouble( 26 );
			locateRec.wlsSolution.location.degLongitude = pReader->GetFieldAsDouble( 27 );
			locateRec.wlsSolution.location.fAltitude = pReader->GetFieldAsFloat( 28 );
			locateRec.wlsSolution.wNumBurstsUsed = pReader->GetFieldAsUShort( 29 );
			locateRec.timeFirstData = pReader->GetFieldAsTime( 30 );
			locateRec.timeLastData = pReader->GetFieldAsTime( 31 );

			switch( locateRec.wType & EMSLOCTYPE_REAL_BASE_MASK )
			{
				case EMSLOCTYPE_CBC:
				case EMSLOCTYPE_CBC_121:
				case EMSLOCTYPE_CBC_243:
				case EMSLOCTYPE_CBC_121_243:
				case EMSLOCTYPE_CBC_B:
				case EMSLOCTYPE_CBC_121_B:
				case EMSLOCTYPE_CBC_243_B:
				case EMSLOCTYPE_CBC_121_243_B:
				case EMSLOCTYPE_CBC_121_DETECT:
				case EMSLOCTYPE_CBC_243_DETECT:
				case EMSLOCTYPE_CBC_121_243_DETECT:
				case EMSLOCTYPE_CBC_406_DETECT:
					locateRec.info.recCBC.fSweep = pReader->GetFieldAsFloat( 32 );
					locateRec.info.recCBC.fSweepError = pReader->GetFieldAsFloat( 33 );
					locateRec.info.recCBC.wSidebands = pReader->GetFieldAsUShort( 34 );
					break;
				case EMSLOCTYPE_GEO_SARR:
				case EMSLOCTYPE_GEO_SARR_UNCONFIRMED:
				case EMSLOCTYPE_406:
				case EMSLOCTYPE_406_SARP:
				case EMSLOCTYPE_406_SARR:
				case EMSLOCTYPE_406_SARP_SARR:
				case EMSLOCTYPE_406_B:
				case EMSLOCTYPE_406_SARP_B:
				case EMSLOCTYPE_406_SARR_B:
				case EMSLOCTYPE_406_SARP_SARR_B:
				case EMSLOCTYPE_406_SARP_DETECT:
				case EMSLOCTYPE_406_SARR_DETECT:
				case EMSLOCTYPE_406_SARP_SARR_DETECT:
				case EMSLOCTYPE_406_FDOA_SARR:
				case EMSLOCTYPE_406_FDOA_SARP:
				case EMSLOCTYPE_406_FDOA_SARP_SARR:
				case EMSLOCTYPE_406_FDOA_SARR_B:
				case EMSLOCTYPE_406_FDOA_SARP_B:
				case EMSLOCTYPE_406_FDOA_SARP_SARR_B:
				case EMSLOCTYPE_406_FDOA_SARR_DETECT:
				case EMSLOCTYPE_406_FDOA_SARP_DETECT:
				case EMSLOCTYPE_406_FDOA_SARP_SARR_DETECT:
				case EMSLOCTYPE_406_FDOA:
				case EMSLOCTYPE_406_TDOA:
				case EMSLOCTYPE_406_FDOA_TDOA:
					pReader->GetFieldAsFixedBinaryArray( 35, 
											sizeof( locateRec.info.rec406.cBeaconMsg ),
											(unsigned char*) locateRec.info.rec406.cBeaconMsg );
					locateRec.info.rec406.wBitErrorField1 = pReader->GetFieldAsUShort( 36 );
					locateRec.info.rec406.wBitErrorField2 = pReader->GetFieldAsUShort( 37 );
					break;
			}

			olstRet.Add( locateRec );

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