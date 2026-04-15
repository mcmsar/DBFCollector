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

#include "dataaccesshelper.h"
#include "emsdbfieldnames.h"
#include "sqlbuilder.h"
#include "lutdbschemainfo.h"
#include "convutility.h"
#include "objectset.h"
#include "rawdatarecordreader.h"
#include "recordmetadata.h"
#include "rawdatarecord.h"
#include "emsexcpt.h"
#include "emstime.h"
#include "emsclock.h"
#include "mastmsgs.h"
#include "PIPEMSGS.h"
#include "MTLMsgs.h"
#include "STestMsg.h"
#include "loggrcat.h"

const ULONG g_ulIgnoreLutID = 0L;

CEMSDataAccessHelper::CEMSDataAccessHelper()
{
}

CEMSDataAccessHelper::CEMSDataAccessHelper( const CEMSDataAccessHelper& x ) : CEMSDataAccessHelperBase( x )
{
}

CEMSDataAccessHelper::~CEMSDataAccessHelper()
{
}

CEMSObjectList<EMSSATELLITEPASS> 
CEMSDataAccessHelper::GetSatelliteTracks( const ULONG culLutID, const EMSTIME ctimeStart, 
										const EMSTIME ctimeEnd )
{
	CEMSObjectList<EMSSATELLITEPASS> olstRet;

	try
	{
		std::wstring wszSQL = _BuildSatTrackSQL( culLutID, ctimeStart, ctimeEnd );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 0;

		if( (0 != ctimeEnd.intTime) && (0 == ctimeStart.intTime) )
		{
			// Only end time given then we're looking for a single record.
			ulMaxRecords = 1;
		}
		else if( (0 != ctimeEnd.intTime) && (0 != ctimeStart.intTime) )
		{
			// Range given.  Get them all.
			ulMaxRecords = 0;
		}
		else if( (0 == ctimeEnd.intTime) && (0 == ctimeStart.intTime) )
		{
			// No time specified or only start time specified.  Not allowed.
			throw CEMSException( EMS_BAD_PARAM );
		}

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		olstRet = _AssembleSatelliteTracks( olstRecords );
	}
	catch( ... )
	{
		throw;
	}

	return olstRet;
}

CEMSObjectList<EMSSATELLITEPASS> 
CEMSDataAccessHelper::GetSatelliteTracksBySatellite( const ULONG culSatID, const EMSTIME ctimeStart, 
																const EMSTIME ctimeEnd )
{
	CEMSObjectList<EMSSATELLITEPASS> olstRet;

	try
	{
		std::wstring wszSQL = _BuildSatTrackSQLForSatellite( g_ulIgnoreLutID, culSatID, ctimeStart, ctimeEnd );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 0;

		if( (0 != ctimeEnd.intTime) && (0 == ctimeStart.intTime) )
		{
			// Only end time given then we're looking for a single record.
			ulMaxRecords = 1;
		}
		else if( (0 != ctimeEnd.intTime) && (0 != ctimeStart.intTime) )
		{
			// Range given.  Get them all.
			ulMaxRecords = 0;
		}
		else if( (0 == ctimeEnd.intTime) && (0 == ctimeStart.intTime) )
		{
			// No time specified or only start time specified.  Not allowed.
			throw CEMSException( EMS_BAD_PARAM );
		}

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		olstRet = _AssembleSatelliteTracks( olstRecords );
	}
	catch( ... )
	{
		throw;
	}

	return olstRet;
}

EMSSATELLITEPASS 
CEMSDataAccessHelper::GetSatelliteTracksBySatellitePass( const ULONG culSatID, const ULONG culPassID )
{
	return GetSatelliteTracksBySatellitePass( g_ulIgnoreLutID, culSatID, culPassID );
}

EMSSATELLITEPASS 
CEMSDataAccessHelper::GetSatelliteTracksBySatellitePass( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSSATELLITEPASS passRet;
	memset( &passRet, 0, sizeof(EMSSATELLITEPASS) );

	try
	{
		if( 0 == culSatID && 
			0 == culPassID )
		{
			throw CEMSException( EMS_BAD_PARAM );
		}
		
		std::wstring wszSQL = _BuildSatTrackSQLForSatellitePass( culLutID, culSatID, culPassID );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		CEMSObjectList<EMSSATELLITEPASS> olstRet = _AssembleSatelliteTracks( olstRecords );

		if( olstRet.Count() > 0 )
		{
			olstRet.MoveFirst();

			passRet = olstRet.GetNext();
		}
	}
	catch( ... )
	{
		throw;
	}

	return passRet;
}

EMSTLEDATA 
CEMSDataAccessHelper::GetTLE( const ULONG culSatID, const EMSTIME ctimeEffective )
{
	EMSTLEDATA strRet;

	memset( &strRet, 0, sizeof(EMSTLEDATA) );

	try
	{
		std::wstring wszSQL = _BuildTLESQL( g_ulIgnoreLutID, culSatID, ctimeEffective );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		strRet = _AssembleTLE( olstRecords );

	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

void
CEMSDataAccessHelper::GetLastTrackedSatellitePass( const ULONG culLutID, ULONG& ulSatID, ULONG& ulPassID)
{
	ulSatID = 0;
	ulPassID = 0;

	try
	{
		std::wstring wszSQL = _BuildLastPassSummarySQL( culLutID );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLastTrackedPass( olstRecords, ulSatID, ulPassID );

	}
	catch( ... )
	{
		throw;
	}
}

void
CEMSDataAccessHelper::GetTimeSolnProcessing( 
						const ULONG culLutID,
						const ULONG	culSatID, 
						const ULONG	culPassID,
						EMSTIME&	timeSolnProcessing )
{

	if ( 0 == culSatID || 0 == culPassID )
	{
		// Missing parameters. Not allowed.
		throw CEMSException( EMS_BAD_PARAM );
	}

	try
	{
		LPCWSTR		cawszColumns[] = {cwszPassStatusSolnProcessingTime};
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildPassSummarySQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleTimeSolnProcessing( olstRecords, timeSolnProcessing );
	}
	catch( ... )
	{
		throw;
	}
}

void
CEMSDataAccessHelper::GetLastTimeSolnProcessing( 
						const ULONG culLutID,
						EMSTIME&	timeSolnProcessing )
{

	try
	{
		LPCWSTR		cawszColumns[] = {cwszPassStatusSolnProcessingTime};
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildLastPassSummarySQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleTimeSolnProcessing( olstRecords, timeSolnProcessing );
	}
	catch( ... )
	{
		throw;
	}
}

CEMSObjectList<EMSLOCATE> 
CEMSDataAccessHelper::GetLocations( const UINT64 cui64BeaconID, const INT64 ci64Timestamp, 
								   const WORD cwType )
{
	CEMSObjectList<EMSLOCATE> olstRet;

	//	Tickets 25170: Zero can actually be a valid identifier!
	if ( /*0 == cui64BeaconID || */ 0 == ci64Timestamp )
	{
		// Missing parameters. Not allowed.
		throw CEMSException( EMS_BAD_PARAM );
	}

	try
	{
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


		std::wstring wszSQL = _BuildGetLocationsSQL( (LPCWSTR*) cawszColumns, csColumns, cui64BeaconID, ci64Timestamp, cwType, g_ulIgnoreLutID );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( 0, wszSQL.c_str() );

		olstRet = _AssembleLocationRecords( olstRecords );
	}
	catch( ... )
	{
		throw;
	}

	return olstRet;
}

EMSSATELLITEPASS 
CEMSDataAccessHelper::GetNextScheduledPass( const ULONG culLutID )
{
	EMSSATELLITEPASS strRet;
	memset( &strRet, 0, sizeof(EMSSATELLITEPASS) );
	CEMSRawDataRecordReader* pSchedRec = NULL;

	try
	{
		// This is actually a two stage request.  First, the timestamp of the current set of pass 
		// schedule records must be found.  Then the next scheduled pass must be chosen from that
		// set.
		CSQLBuilder oSQL;
		oSQL.AddSelectFirstOnly();
		oSQL.AddColumns( 1, &cwszTimestamp );

		oSQL.AddFrom();
		oSQL.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );
		if( 0 != culLutID )
		{
			oSQL.AddWhere();
			oSQL+= cwszLutID;
			oSQL.AddEQ();
			oSQL+= CEMSConversionUtil::ConvertToString( culLutID ).c_str();
		}

	    // Excludes passses generated from SIT661A
		// Only relevant for the LUT Server
		oSQL.AddAnd();		
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_SUCCESS ).c_str();
		oSQL.CloseParenth();
		oSQL.AddAnd();
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_ERROR ).c_str();
		oSQL.CloseParenth();
		oSQL.AddAnd();
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_ABORT ).c_str();
		oSQL.CloseParenth();

		oSQL.AddOrderBy();
		oSQL += cwszTimestamp;
		oSQL.AddDescending();

		CEMSPointerList<CEMSRawDataRecordReader> olstSched = _GetData( 1, ((std::wstring) oSQL).c_str() );

		olstSched.MoveFirst();

		if( pSchedRec = olstSched.GetNext() )
		{
			EMSTIME timeSched = pSchedRec->GetFieldAsTime(0L);

			pSchedRec->Release();
			pSchedRec = NULL;
		

			LPCWSTR		cawszColumns[] = { cwszSatID, cwszPassID,
											cwszSatTrackStartTime, cwszSatTrackEndTime,
											cwszSatTrackPassAzimuthAOS, cwszSatTrackPassAzimuthLOS,
											cwszSatTrackPassMaxElevation
											};
			const short	csColumns = 7;

			std::wstring wszSQL = _BuildNextSchedPassSQL( 
										cawszColumns,
										csColumns,
										culLutID,
										timeSched );
			if( wszSQL.empty() )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			ULONG ulMaxRecords = 1;

			CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

			_AssembleNextSchedPass( olstRecords, strRet );
		}
	}
	catch( ... )
	{
		if( pSchedRec )
		{
			pSchedRec->Release();
			pSchedRec = NULL;
		}

		throw;
	}

	return strRet;
}

EMSSENSORINFO 
CEMSDataAccessHelper::GetLatestSensor( const ULONG culLutID )
{
	EMSSENSORINFO strRet;
	memset( &strRet, 0, sizeof(EMSSENSORINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszSensorACUTemp, cwszSensorRackTemp, 
										cwszSensorRadomeTemp, cwszSensorServoTemp };
		const short	csColumns = 4;

		std::wstring wszSQL = _BuildLastSensorSQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLastSensor( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

CEMSObjectList<EMSLOGDATA> 
CEMSDataAccessHelper::GetLogData( const ULONG culLutID, const EMSTIME ctimeNewerThan, 
								 const ULONG culCount)
{
	CEMSObjectList<EMSLOGDATA> olstRet;

	try
	{
		const short csColumns = 4;
		const LPCWSTR cawszColumns[ csColumns ] = { cwszTimestamp, cwszLogProcessID, cwszLogMsgType,
													cwszLogMsg };


		std::wstring wszSQL = _BuildLogDataSQL( (LPCWSTR*) cawszColumns, csColumns, culLutID, ctimeNewerThan );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( culCount, wszSQL.c_str() );

		 _AssembleLogData( olstRecords, olstRet);
	}
	catch( ... )
	{
		throw;
	}


	return olstRet;
}

EMSSATELLITEPASS 
CEMSDataAccessHelper::GetCurrentScheduledPass( const ULONG culLutID, const ULONG culIdleDelaySec )
{
	EMSSATELLITEPASS strRet;
	memset( &strRet, 0, sizeof(EMSSATELLITEPASS) );
	CEMSRawDataRecordReader* pSchedRec = NULL;

	try
	{
		// This is actually a two stage request.  First, the timestamp of the current set of pass 
		// schedule records must be found.  Then the next scheduled pass must be chosen from that
		// set.
		CSQLBuilder oSQL;
		oSQL.AddSelectFirstOnly();
		oSQL.AddColumns( 1, &cwszTimestamp );
		oSQL.AddFrom();
		oSQL.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );
		if( 0 != culLutID )
		{
			oSQL.AddWhere();
			oSQL+= cwszLutID;
			oSQL.AddEQ();
			oSQL+= CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		}

	    // Excludes passses generated from SIT661A 
		// (relevant for LUT Server only)
		oSQL.AddAnd();			
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_SUCCESS ).c_str();
		oSQL.CloseParenth();
		oSQL.AddAnd();
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_ERROR ).c_str();
		oSQL.CloseParenth();
		oSQL.AddAnd();
		oSQL.OpenParenth();
		oSQL += cwszSatTrackPassFlags;
		oSQL.AddBitAnd();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_RESULT_MASK ).c_str();
		oSQL.AddNE();
		oSQL += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_ABORT ).c_str();
		oSQL.CloseParenth();

		oSQL.AddOrderBy();
		oSQL += cwszTimestamp;
		oSQL.AddDescending();

		CEMSPointerList<CEMSRawDataRecordReader> olstSched = _GetData( 1, ((std::wstring) oSQL).c_str() );

		olstSched.MoveFirst();

		if( pSchedRec = olstSched.GetNext() )
		{
			EMSTIME timeSched = pSchedRec->GetFieldAsTime(0L);

			pSchedRec->Release();
			pSchedRec = NULL;

			LPCWSTR		cawszColumns[] = { cwszSatID, cwszPassID,
											cwszSatTrackPassTimeAOS,
											cwszSatTrackPassTimeLOS,
											cwszSatTrackPassAzimuthAOS, cwszSatTrackPassAzimuthLOS,
											cwszSatTrackPassMaxElevation
											};
			const short	csColumns = 7;

			std::wstring wszSQL = _BuildCurrentSchedPassSQL( 
										cawszColumns,
										csColumns,
										culLutID,
										timeSched,
										culIdleDelaySec );
			if( wszSQL.empty() )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			ULONG ulMaxRecords = 1;

			CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

			_AssembleNextSchedPass( olstRecords, strRet );
		}
	}
	catch( ... )
	{
		if( pSchedRec )
		{
			pSchedRec->Release();
			pSchedRec = NULL;
		}

		throw;
	}

	return strRet;
}

EMSANTENNAINFO 
CEMSDataAccessHelper::GetCurrentAntennaData( const ULONG culLutID )
{
	EMSANTENNAINFO strRet;
	memset( &strRet, 0, sizeof(EMSANTENNAINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszAntennaElevationA, cwszAntennaAzimuthA, cwszAntennaStatus };
		const short	csColumns = 3;

		std::wstring wszSQL = _BuildCurrentAntennaSQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentAntennaData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSCOLLECTORINFO 
CEMSDataAccessHelper::GetCurrentCollectorData( const ULONG culLutID )
{
	EMSCOLLECTORINFO strRet;
	memset( &strRet, 0, sizeof(EMSCOLLECTORINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszSatID, cwszCollectorCarrierTime, cwszCollectorModIndexMean, 
										cwszCollectorCarrierFrequency, cwszCollectorStatus};
		const short	csColumns = 5;

		std::wstring wszSQL = _BuildCurrentCollectorSQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentCollectorData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSTIME 
CEMSDataAccessHelper::GetLastClockSynchTime( const ULONG culLutID )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	try
	{
		LPCWSTR		cawszColumns[] = { cwszTimestamp };
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildLastTimeSynchSQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLastTimeSynchData( olstRecords, timeRet );
	}
	catch( ... )
	{
		throw;
	}

	return timeRet;

}

EMSWIDEBANDINFO 
CEMSDataAccessHelper::GetCurrentWBData( const ULONG culLutID )
{
	EMSWIDEBANDINFO strRet;
	memset( &strRet, 0, sizeof(EMSWIDEBANDINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszWidebandCBC121Counts, cwszWidebandCBC243Counts, 
										cwszWidebandCBC406Counts, cwszWidebandSarpTotalFrames,
										cwszWidebandSarpTotalMessages, cwszWidebandSarrTotalMessages };
		const short	csColumns = 6;

		std::wstring wszSQL = _BuildCurrentWBSQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentWBData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSSARRDATA 
CEMSDataAccessHelper::GetCurrentSarrData( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSSARRDATA strRet;
	memset( &strRet, 0, sizeof(EMSSARRDATA) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszTimestamp, cwszSARRBeaconID, cwszSARRBeaconMsg };
		const short	csColumns = 3;

		std::wstring wszSQL = _BuildCurrentSarrSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentSarrData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSSARRDATA 
CEMSDataAccessHelper::GetCurrentGeoSarrData( const ULONG culLutID, const ULONG culSatID, const double cdElapsedMinutes )
{
	EMSSARRDATA strRet;
	memset( &strRet, 0, sizeof(EMSSARRDATA) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszTimestamp, cwszSARRBeaconID, cwszSARRBeaconMsg };
		const short	csColumns = 3;

		std::wstring wszSQL = _BuildCurrentGeoSarrSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									cdElapsedMinutes );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentSarrData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSPASSSUMMARYINFO2 
CEMSDataAccessHelper::GetLatestPassSummary( const ULONG culLutID )
{
	EMSPASSSUMMARYINFO2 strRet;
	memset( &strRet, 0, sizeof(EMSPASSSUMMARYINFO2) );

	try
	{
		LPCWSTR		cawszColumns[] = {	cwszLutID, cwszSatID, cwszPassID,
										cwszPassStatusSecsDuration, cwszPassStatusSecsCollecting, cwszPassStatusSolnProcessingTime,
										cwszPassStatusAlarms, cwszPassStatusWarnings, cwszPassStatus121Transmitters,
										cwszPassStatus243Transmitters, cwszPassStatus406Interferers, cwszPassStatus406LocatedBeacons,
										cwszPassStatus406UnlocatedBeacons, cwszPassStatusPDSRecoverRate, cwszPassStatusFramesMissed,
										cwszPassStatusTotalPDSCount, cwszPassStatusSarrMessages, cwszPassStatusOrbitEpoch,
										cwszPassStatusOrbitPositionOffset, cwszPassStatusOrbitVelocityOffset, cwszPassStatusCalibrationTime,
										cwszPassStatusRolloverTime, cwszPassStatusUSOFreq, cwszPassStatusSarrFreqOffset,
										cwszPassStatusUnlocatedAlerts };
		const short	csColumns = 25;

		std::wstring wszSQL = _BuildLatestPassSummarySQL( 
									cawszColumns,
									csColumns,
									culLutID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLatestPassSummaryData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSCOLLECTORINFO 
CEMSDataAccessHelper::GetCollectorData( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSCOLLECTORINFO strRet;
	memset( &strRet, 0, sizeof(EMSCOLLECTORINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszSatID, cwszCollectorCarrierTime, cwszCollectorModIndexMean, 
										cwszCollectorCarrierFrequency, cwszCollectorStatus};
		const short	csColumns = 5;

		std::wstring wszSQL = _BuildCollectorForPassSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCurrentCollectorData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSLOCATIONINFO 
CEMSDataAccessHelper::GetLocationStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSLOCATIONINFO strRet;
	memset( &strRet, 0, sizeof(EMSLOCATIONINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszLocateStatus };
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildLocationStatusForPassSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLocationStatusData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

CEMSObjectList<EMSLOCATE> 
CEMSDataAccessHelper::GetLocations( const EMSTIME ctimeStart, const EMSTIME ctimeEnd, const ULONG culLutID )
{
	CEMSObjectList<EMSLOCATE> olstRet;

	try
	{
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


		std::wstring wszSQL = _BuildGetLocationsSQL( (LPCWSTR*) cawszColumns, csColumns, ctimeStart, ctimeEnd, culLutID );

		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( 0, wszSQL.c_str() );

		olstRet = _AssembleLocationRecords( olstRecords );
	}
	catch( ... )
	{
		throw;
	}

	return olstRet;
}

EMSORBITDETERMINEINFO 
CEMSDataAccessHelper::GetOrbitStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSORBITDETERMINEINFO strRet;
	memset( &strRet, 0, sizeof(EMSORBITDETERMINEINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszOrbitStatus };
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildOrbitStatusForPassSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleOrbitStatusData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSTCALINFO 
CEMSDataAccessHelper::GetTCALStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSTCALINFO strRet;
	memset( &strRet, 0, sizeof(EMSTCALINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszSARPCalibStatus };
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildTCALStatusForPassSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleTCALStatusData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

EMSSARRCALIBINFO 
CEMSDataAccessHelper::GetSARRStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	EMSSARRCALIBINFO strRet;
	memset( &strRet, 0, sizeof(EMSSARRCALIBINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszSARRCalibStatus };
		const short	csColumns = 1;

		std::wstring wszSQL = _BuildSARRStatusForPassSQL( 
									cawszColumns,
									csColumns,
									culLutID,
									culSatID,
									culPassID );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleSARRStatusData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

ULONG 
CEMSDataAccessHelper::GetNumLogMessages( const EMSTIME ctimeStart, const EMSTIME ctimeEnd, 
							const ULONG culLutID, const EMS_RESULT chrMsg, 
							const int ciLogLevel )
{
	ULONG ulRet = 0;

	try
	{
		std::wstring wszSQL = _BuildLogMsgCountSQL( 
									ctimeStart,
									ctimeEnd,
									culLutID,
									chrMsg,
									ciLogLevel );
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLogMsgCountData( olstRecords, ulRet );
	}
	catch( ... )
	{
		throw;
	}

	return ulRet;
}

EMSCOMMSINFO 
CEMSDataAccessHelper::GetCurrentCommsData( const ULONG culLutID )
{
	EMSCOMMSINFO strRet;
	memset( &strRet, 0, sizeof(EMSCOMMSINFO) );

	try
	{
		LPCWSTR		cawszColumns[] = { cwszCommsStatus, cwszCommsStatusMsgID, cwszCommsStatusRouteID,
										cwszCommsStatusTimeTx, cwszCommsStatusRetryCount, 
										cwszCommsStatusLossCount, cwszCommsStatusLossDuration };
		const short	csColumns = 7;

		std::wstring wszSQL = _BuildCurrentCommsStatusSQL( 
									cawszColumns,
									csColumns,
									culLutID );
									
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleCommsStatusData( olstRecords, strRet );
	}
	catch( ... )
	{
		throw;
	}

	return strRet;
}

void
CEMSDataAccessHelper::GetCurrentLutDisplayState( 
	const ULONG culLutID,
	const ULONG culIdleDelaySec,
	LUTDISPLAYSTATE& eCurrentState,
	EMSTIME& timeStateChange )
{
	try
	{
		std::wstring wszSQL = _BuildCurrentLutDisplayStateSQL( culLutID );
									
		if( wszSQL.empty() )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ULONG ulMaxRecords = 1;

		CEMSPointerList<CEMSRawDataRecordReader> olstRecords = _GetData( ulMaxRecords, wszSQL.c_str() );

		_AssembleLutDisplayStateData( olstRecords, culIdleDelaySec, eCurrentState, timeStateChange );
	}
	catch( CEMSException& e )
	{
		if ( EMS_MTL_SOAP_TCP_ERROR == e.GetErrCode() )
		{
			// Don't actually know when this started...
			timeStateChange = CEMSSystemClock::GetTime();
			eCurrentState = LUTDISPLAYSTATE_OFFLINE;
		}
		else
		{
			throw;
		}
	}
	catch( HRESULT hr )
	{
		if ( EMS_MTL_SOAP_TCP_ERROR == hr )
		{
			// Don't actually know when this started...
			timeStateChange = CEMSSystemClock::GetTime();
			eCurrentState = LUTDISPLAYSTATE_OFFLINE;
		}
		else
		{
			throw;
		}
	}
	catch( ... )
	{
		throw;
	}
	return;
}

std::wstring 
CEMSDataAccessHelper::_BuildSatTrackSQL( const ULONG culLutID, const EMSTIME ctimeStart, 
										const EMSTIME ctimeEnd )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 4;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszSatID;
	cawszColumns[1] = cwszPassID;
	cawszColumns[2] = cwszSatTrackPassTimeAOS;
	cawszColumns[3] = cwszSatTrackPassTimeLOS;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeEnd.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatTrackPassTimeLOS;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeStart.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatTrackPassTimeLOS;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();

		bConditionAdded = true;
	}

	if( bConditionAdded )
		oSQLBuilder.AddAnd();

	oSQLBuilder.OpenParenth();
	oSQLBuilder += cwszSatTrackPassFlags;
	oSQLBuilder.AddBitAnd();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_STATUS_MASK ).c_str();
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();
	oSQLBuilder.CloseParenth();

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszSatTrackPassTimeLOS;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildSatTrackSQLForSatellite(const ULONG culLutID,
													const ULONG culSatID, 
													const EMSTIME ctimeStart, 
													const EMSTIME ctimeEnd )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 4;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszSatID;
	cawszColumns[1] = cwszPassID;
	cawszColumns[2] = cwszSatTrackPassTimeAOS;
	cawszColumns[3] = cwszSatTrackPassTimeLOS;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culSatID )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeEnd.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatTrackPassTimeLOS;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeStart.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatTrackPassTimeLOS;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();

		bConditionAdded = true;
	}

	oSQLBuilder.OpenParenth();
	oSQLBuilder += cwszSatTrackPassFlags;
	oSQLBuilder.AddBitAnd();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_STATUS_MASK ).c_str();
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();
	oSQLBuilder.CloseParenth();

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszSatTrackPassTimeLOS;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildSatTrackSQLForSatellitePass( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 4;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszSatID;
	cawszColumns[1] = cwszPassID;
	cawszColumns[2] = cwszSatTrackPassTimeAOS;
	cawszColumns[3] = cwszSatTrackPassTimeLOS;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culSatID )
	{
		if( !bConditionAdded )
				oSQLBuilder.AddWhere();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildTLESQL( const ULONG culLutID, const ULONG culSatID, const EMSTIME ctimeEffective )
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

	if( 0 != culLutID )
	{
		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culSatID )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeEffective.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszOrbitTimeEffective;
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

std::wstring 
CEMSDataAccessHelper::_BuildLastPassSummarySQL( const ULONG culLutID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	const short csColumns = 2;
	const wchar_t* cawszColumns[ csColumns ];

	cawszColumns[0] = cwszSatID;
	cawszColumns[1] = cwszPassID;


	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_PASS_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildLastPassSummarySQL( LPCWSTR* cawszColumns, const short csColumns, const ULONG culLutID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_PASS_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}


std::wstring 
CEMSDataAccessHelper::_BuildPassSummarySQL( 
									LPCWSTR*	cawszColumns,
									const short	csColumns,
									const ULONG	culLutID,
									const ULONG culSatID,
									const ULONG	culPassID )
{
	std::wstring wszRet;
	if ( csColumns <=0 || !cawszColumns || culSatID == 0 || culPassID == 0 )
	{
		// Missing parameters. Not allowed.
		throw CEMSException( EMS_BAD_PARAM );
	}

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_PASS_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	oSQLBuilder += cwszSatID;
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

	oSQLBuilder.AddAnd();

	oSQLBuilder += cwszPassID;
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

	if( 0 != culLutID )
	{
		oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();
	}

	wszRet = oSQLBuilder;

	return wszRet;
}


CEMSObjectList<EMSSATELLITEPASS> 
CEMSDataAccessHelper::_AssembleSatelliteTracks( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords )
{
	CEMSObjectList<EMSSATELLITEPASS> olstRet;

	CEMSRawDataRecordReader* pRec = 0;

	try
	{
		CEMSObjectSet<std::wstring> osetUniqueRecords;

		olstRecords.MoveFirst();

		pRec = olstRecords.GetNext();

		while( pRec )
		{

			// Records are ordered in descending order of creation.
			// There may be duplicate entries generated at different times.
			// Filter out duplicates by keeping only the most recent.

			EMSSATELLITEPASS strPassInfo;
			memset( &strPassInfo, 0, sizeof(EMSSATELLITEPASS) );

			strPassInfo.ulSatelliteID = pRec->GetFieldAsULong( 0L );
			strPassInfo.ulOrbitNumber = pRec->GetFieldAsULong( 1 );
			strPassInfo.timeAOS = pRec->GetFieldAsTime( 2 );
			strPassInfo.timeLOS = pRec->GetFieldAsTime( 3 );
	
			wchar_t wszRecordKey[ 32 ];
			memset( wszRecordKey, 0, 32*sizeof(wchar_t) );
			swprintf( wszRecordKey, L"%d_%d", strPassInfo.ulSatelliteID, strPassInfo.ulOrbitNumber );

			if( osetUniqueRecords.Add( std::wstring( wszRecordKey ) ) )
			{
				olstRet.Add( strPassInfo );
			}

			pRec->Release();
			pRec = 0;

			pRec = olstRecords.GetNext();
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

	return olstRet;
}

EMSTLEDATA 
CEMSDataAccessHelper::_AssembleTLE( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords )
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
			strRet.timeEpoch = pDataReader->GetFieldAsTime( 0L );
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

void 
CEMSDataAccessHelper::_AssembleLastTrackedPass( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
											   ULONG& ulSatID, ULONG& ulPassID )
{
	ulSatID = 0;
	ulPassID = 0;

	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		pDataReader = olstRecords.GetNext();

		// Expecting maximum of 1 record.
		if( pDataReader )
		{
			ulSatID = pDataReader->GetFieldAsULong( 0L );
			ulPassID = pDataReader->GetFieldAsULong( 1 );

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

		throw;
	}

}

void 
CEMSDataAccessHelper::_AssembleTimeSolnProcessing( 
						CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSTIME& timeSolnProcessing )
{

	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		pDataReader = olstRecords.GetNext();

		// Expecting maximum of 1 record.
		if( pDataReader )
		{
			timeSolnProcessing = pDataReader->GetFieldAsTime( 0L );

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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildGetLocationsSQL( LPCWSTR* cawszColumns, const short csColumns,
											const UINT64 cuiBeaconID, const INT64 ci64Timestamp, 
											const WORD cwType, const ULONG culLutID )
{
	std::wstring wszRet;
	if ( csColumns <=0 || !cawszColumns || 0 == cuiBeaconID  || 0 == ci64Timestamp )
	{
		// Missing parameters. Not allowed.
		throw CEMSException( EMS_BAD_PARAM );
	}

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOCATE, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	oSQLBuilder += cwszLocateBeaconID;
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( cuiBeaconID ).c_str();

	oSQLBuilder.AddAnd();

	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( ci64Timestamp ).c_str();

	if( 0 != culLutID )
	{
		oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();
	}

	if( 0 != cwType )
	{
		oSQLBuilder.AddAnd();

		oSQLBuilder += cwszType;
		oSQLBuilder.AddBitAnd();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( cwType ).c_str();
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( cwType ).c_str();

	}

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildGetLocationsSQL( LPCWSTR* cawszColumns, const short csColumns,
											const EMSTIME ctimeStart, const EMSTIME ctimeEnd,
											const ULONG culLutID )
{
	std::wstring wszRet;
	if ( csColumns <=0 || !cawszColumns )
	{
		// Missing parameters. Not allowed.
		throw CEMSException( EMS_BAD_PARAM );
	}

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );
	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOCATE, EMSDBVERSION_LEO_20 ).c_str() );

	oSQLBuilder.AddWhere();

	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddGE();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();

	oSQLBuilder.AddAnd();

	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddLE();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();

	if( 0 != culLutID )
	{
		oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

	}

	wszRet = oSQLBuilder;

	return wszRet;
}

CEMSObjectList<EMSLOCATE> 
CEMSDataAccessHelper::_AssembleLocationRecords( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords )
{
	CEMSObjectList<EMSLOCATE> olstRet;

	CEMSRawDataRecordReader* pRec = 0;

	try
	{
		olstRecords.MoveFirst();

		pRec = olstRecords.GetNext();

		while( pRec )
		{
			EMSLOCATE locateRec;
			memset( &locateRec, 0, sizeof(EMSLOCATE) );

			locateRec.time = pRec->GetFieldAsTime( 0L );
			locateRec.ulLutID = pRec->GetFieldAsULong( 1 );
			locateRec.wType = pRec->GetFieldAsUShort( 2 );
			pRec->GetFieldAsFixedBinaryArray( 3, sizeof( locateRec.cSatIDs ), 
												(unsigned char*) locateRec.cSatIDs );
			locateRec.ulSatPassID = pRec->GetFieldAsULong( 4 );
			pRec->GetFieldAsFixedBinaryArray( 5, sizeof( locateRec.cLutIDs ),
												(unsigned char*) locateRec.cLutIDs );
			locateRec.i64BeaconID = pRec->GetFieldAsUI64( 6 );
			locateRec.wlsSolution.wNumMsgs = pRec->GetFieldAsUShort( 7 );
			locateRec.wlsSolution.wNumMsgsUsed = pRec->GetFieldAsUShort( 8 );
			locateRec.wlsSolution.wNumIterations = pRec->GetFieldAsUShort( 9 );
			locateRec.timeTCA = pRec->GetFieldAsTime( 10 );
			locateRec.wWindowFactor = pRec->GetFieldAsUShort( 11 );
			locateRec.wlsSolution.dFrequency = pRec->GetFieldAsDouble( 12 );
			locateRec.fConfidence = pRec->GetFieldAsFloat( 13 );
			locateRec.fProbability = pRec->GetFieldAsFloat( 14 );
			locateRec.fPower = pRec->GetFieldAsFloat( 15 );
			locateRec.wlsSolution.fRadiusErrEllipse = pRec->GetFieldAsFloat( 16 );
			locateRec.wlsSolution.fFreqBiasError = pRec->GetFieldAsFloat( 17 );
			locateRec.wlsSolution.fFreqDrift = pRec->GetFieldAsFloat( 18 );
			locateRec.fCrossTrackAngle = pRec->GetFieldAsFloat( 19 );
			locateRec.wlsSolution.fMajorError = pRec->GetFieldAsFloat( 20 );
			locateRec.wlsSolution.fMinorError = pRec->GetFieldAsFloat( 21 );
			locateRec.wlsSolution.fHeading = pRec->GetFieldAsFloat( 22 );
			locateRec.wlsSolution.fRMS = pRec->GetFieldAsFloat( 23 );
			locateRec.wlsSolution.fTrend = pRec->GetFieldAsFloat( 24 );
			pRec->GetFieldAsFixedBinaryArray( 25, 
											sizeof( locateRec.wlsSolution.fCoVarianceMatrix ),
											(unsigned char*) locateRec.wlsSolution.fCoVarianceMatrix );
			locateRec.wlsSolution.location.degLatitude = pRec->GetFieldAsDouble( 26 );
			locateRec.wlsSolution.location.degLongitude = pRec->GetFieldAsDouble( 27 );
			locateRec.wlsSolution.location.fAltitude = pRec->GetFieldAsFloat( 28 );
			locateRec.wlsSolution.wNumBurstsUsed = pRec->GetFieldAsUShort( 29 );
			locateRec.timeFirstData = pRec->GetFieldAsTime( 30 );
			locateRec.timeLastData = pRec->GetFieldAsTime( 31 );

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
					locateRec.info.recCBC.fSweep = pRec->GetFieldAsFloat( 32 );
					locateRec.info.recCBC.fSweepError = pRec->GetFieldAsFloat( 33 );
					locateRec.info.recCBC.wSidebands = pRec->GetFieldAsUShort( 34 );
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
					pRec->GetFieldAsFixedBinaryArray( 35, 
											sizeof( locateRec.info.rec406.cBeaconMsg ),
											(unsigned char*) locateRec.info.rec406.cBeaconMsg );
					locateRec.info.rec406.wBitErrorField1 = pRec->GetFieldAsUShort( 36 );
					locateRec.info.rec406.wBitErrorField2 = pRec->GetFieldAsUShort( 37 );
					break;
			}


			pRec->Release();
			pRec = 0;

			pRec = olstRecords.GetNext();

			olstRet.Add( locateRec );
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
	
	return olstRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildNextSchedPassSQL( LPCWSTR* cawszColumns, const short csColumns,
												const ULONG culLutID, const EMSTIME ctimeSched )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Only scheduled passes.
	if( bConditionAdded )
		oSQLBuilder.AddAnd();
	else
		oSQLBuilder.AddWhere();
	
	oSQLBuilder.OpenParenth();

	oSQLBuilder += cwszSatTrackPassFlags;
	oSQLBuilder.AddBitAnd();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();

	oSQLBuilder.CloseParenth();

	bConditionAdded = true;

	// Must be in the future.
	if( bConditionAdded )
		oSQLBuilder.AddAnd();
	else
		oSQLBuilder.AddWhere();

	oSQLBuilder += cwszSatTrackStartTime;
	oSQLBuilder.AddGT();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( CEMSSystemClock::GetTime().intTime ).c_str();

	if( 0 != ctimeSched.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();
		else
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeSched.intTime ).c_str();
	}

	// Order it so that we get the most recently generated and next scheduled pass first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszSatTrackStartTime;
	oSQLBuilder.AddAscending();
	oSQLBuilder.AddComma();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleNextSchedPass( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
										EMSSATELLITEPASS& rstrPass )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		pDataReader = olstRecords.GetNext();

		// Expecting maximum of 1 record.
		if( pDataReader )
		{
			rstrPass.ulSatelliteID = pDataReader->GetFieldAsULong( 0L );
			rstrPass.ulOrbitNumber = pDataReader->GetFieldAsULong( 1 );
			rstrPass.timeAOS = pDataReader->GetFieldAsTime( 2 );
			rstrPass.timeLOS = pDataReader->GetFieldAsTime( 3 );
			rstrPass.degAzimuthAOS = pDataReader->GetFieldAsDouble( 4 );
			rstrPass.degAzimuthLOS = pDataReader->GetFieldAsDouble( 5 );
			rstrPass.degMaxElevation = pDataReader->GetFieldAsDouble( 6 );

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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildLastSensorSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SENSOR, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recent record first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLastSensor( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSSENSORINFO& rstrSensor )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		pDataReader = olstRecords.GetNext();

		// Expecting maximum of 1 record.
		if( pDataReader )
		{
			rstrSensor.dTempA = pDataReader->GetFieldAsFloat( 0L );
			rstrSensor.dTempB = pDataReader->GetFieldAsFloat( 1 );
			rstrSensor.dTempC = pDataReader->GetFieldAsFloat( 2 );
			rstrSensor.dTempD = pDataReader->GetFieldAsFloat( 3 );

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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildLogDataSQL( LPCWSTR* cawszColumns, 
										const short csColumns,
										const ULONG culLutID,
										const EMSTIME ctimeNewerThan )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOG, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeNewerThan.intTime )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGT();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeNewerThan.intTime ).c_str();

	}

	// Order it so that we get the most recent record first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLogData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						CEMSObjectList<EMSLOGDATA>& olstLogRecs )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		while( pDataReader = olstRecords.GetNext() )
		{
			EMSLOGDATA strLogData;
			memset( &strLogData, 0, sizeof( EMSLOGDATA) );
			
			strLogData.time = pDataReader->GetFieldAsTime( 0L );
			strLogData.ulProcessID = pDataReader->GetFieldAsULong( 1 );
			strLogData.cMsgType = pDataReader->GetFieldAsByte( 2 );
			pDataReader->GetFieldAsFixedBinaryArray( 3, sizeof(strLogData.cMsg), strLogData.cMsg );

			
			olstLogRecs.Add( strLogData );

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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentSchedPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const EMSTIME ctimeSched,
											const ULONG culIdleDelaySec )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SAT_TRACK, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Only scheduled passes.
	if( bConditionAdded )
		oSQLBuilder.AddAnd();
	else
		oSQLBuilder.AddWhere();
	
	oSQLBuilder.OpenParenth();

	oSQLBuilder += cwszSatTrackPassFlags;
	oSQLBuilder.AddBitAnd();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (long) EMS_PASSFLAG_PROCESS ).c_str();

	oSQLBuilder.CloseParenth();

	bConditionAdded = true;

	// Must be current.
	if( bConditionAdded )
		oSQLBuilder.AddAnd();
	else
		oSQLBuilder.AddWhere();

	EMSTIME timeCurrent = CEMSSystemClock::GetTime();

	oSQLBuilder.OpenParenth();
	oSQLBuilder += cwszSatTrackPassTimeAOS;
	oSQLBuilder.AddLE();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( timeCurrent.intTime ).c_str();
	oSQLBuilder.AddAnd();
	oSQLBuilder += cwszSatTrackPassTimeLOS;
	oSQLBuilder.AddGE();

	CEMSTime	oTimeOffsetByIdle;
	oTimeOffsetByIdle.SetTime( timeCurrent );
	double		dIdleDelaySec = culIdleDelaySec;
	oTimeOffsetByIdle.AddSeconds( dIdleDelaySec );

	// overloaded cast operator retrieves numeric value for time
	oSQLBuilder += CEMSConversionUtil::ConvertToString( oTimeOffsetByIdle.GetTimeNano() ).c_str();

	oSQLBuilder.CloseParenth();

	if( 0 != ctimeSched.intTime )
	{
		if( bConditionAdded )
			oSQLBuilder.AddAnd();
		else
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeSched.intTime ).c_str();
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 
	
	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentAntennaSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_ANTENNA, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleCurrentAntennaData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSANTENNAINFO& roAntennaRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roAntennaRec.azelActual.degElevation = pDataReader->GetFieldAsFloat( 0L );
			roAntennaRec.azelActual.degAzimuth = pDataReader->GetFieldAsFloat( 1 );
			roAntennaRec.uAntennaStatus = pDataReader->GetFieldAsUShort( 2 );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentCollectorSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_COLLECTOR, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleCurrentCollectorData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSCOLLECTORINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.ulSatID = pDataReader->GetFieldAsULong( 0L );
			roRec.carrierTime = pDataReader->GetFieldAsTime( 1 );
			roRec.fCarrierModIndexMean = pDataReader->GetFieldAsFloat( 2 );
			roRec.fCarrierFrequency = pDataReader->GetFieldAsFloat( 3 );
			roRec.uCollectorStatus = pDataReader->GetFieldAsUShort( 4 );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildLastTimeSynchSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOG, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Looking for a particular message ID (EMS_MAST_GPSCLOCK_CHANGE).
	if( bConditionAdded )
		oSQLBuilder.AddAnd();
	else
		oSQLBuilder.AddWhere();

	oSQLBuilder += cwszLogMsgNumber;
	oSQLBuilder.AddEQ();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( (EMS_RESULT) EMS_MAST_GPSCLOCK_CHANGE ).c_str();
	bConditionAdded = true;

	// 10000.0 seconds (approx 3h) is the maximum configurable period between clock comparisons.
	// Limit check to the preceeding week to control length of time this query takes 
	CEMSTime	oTime;
	oTime.SetTime( CEMSSystemClock::GetTime() );
	oTime.AddDays ( -7 );

	INT64		i64Time = oTime.GetTimeNano();

	oSQLBuilder.AddAnd();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddGT();
	oSQLBuilder += CEMSConversionUtil::ConvertToString( i64Time ).c_str();

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLastTimeSynchData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSTIME& roTime )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roTime = pDataReader->GetFieldAsTime( 0L );
		
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentWBSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_WIDEBAND_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleCurrentWBData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSWIDEBANDINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wCBC121Counts = pDataReader->GetFieldAsUShort( 0L );
			roRec.wCBC243Counts = pDataReader->GetFieldAsUShort( 1 );
			roRec.wCBC406Counts = pDataReader->GetFieldAsUShort( 2 );
			roRec.wSarpTotalFrames = pDataReader->GetFieldAsUShort( 3 );
			roRec.wSarpTotalMessages = pDataReader->GetFieldAsUShort( 4 );
			roRec.wSarrTotalMessages = pDataReader->GetFieldAsUShort( 5 );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentSarrSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SARR, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentGeoSarrSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const double cdElapsedMinutes )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SARR, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	if( 0 != cdElapsedMinutes )
	{
		CEMSTime	oTime;
		oTime.SetTime( CEMSSystemClock::GetTime() );
		oTime.AddMinutes ( -1 * cdElapsedMinutes );

		INT64		i64Time = oTime.GetTimeNano();

		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGT();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( i64Time ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleCurrentSarrData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSSARRDATA& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.hdr.id.time = pDataReader->GetFieldAsTime( 0L );
			roRec.i64BeaconID = pDataReader->GetFieldAsUI64( 1 );
			pDataReader->GetFieldAsFixedBinaryArray( 2, sizeof(roRec.cBeaconMsg), roRec.cBeaconMsg );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildLatestPassSummarySQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID)
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_PASS_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLatestPassSummaryData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSPASSSUMMARYINFO2& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.thisTrack.ulLutID = pDataReader->GetFieldAsULong( 0L );
			roRec.thisTrack.PassInfo.ulSatelliteID = pDataReader->GetFieldAsULong( 1 );
			roRec.thisTrack.PassInfo.ulOrbitNumber = pDataReader->GetFieldAsULong( 2 );
			roRec.wSecsDuration = pDataReader->GetFieldAsUShort( 3 );
			roRec.wSecsCollecting = pDataReader->GetFieldAsUShort( 4 );
			roRec.timeSolnProcessing = pDataReader->GetFieldAsTime( 5 );
			roRec.wAlarms = pDataReader->GetFieldAsUShort( 6 );
			roRec.wWarnings = pDataReader->GetFieldAsUShort( 7 );
			roRec.w121Transmitters = pDataReader->GetFieldAsUShort( 8 );
			roRec.w243Transmitters = pDataReader->GetFieldAsUShort( 9 );
			roRec.w406Interferers = pDataReader->GetFieldAsUShort( 10 );
			roRec.w406LocatedBeacons = pDataReader->GetFieldAsUShort( 11 );
			roRec.w406UnlocatedBeacons = pDataReader->GetFieldAsUShort( 12 );
			roRec.nPDSRecoveryRate = pDataReader->GetFieldAsInt( 13 );
			roRec.wFramesMissed = pDataReader->GetFieldAsUShort( 14 );
			roRec.nTotalPDSCount = pDataReader->GetFieldAsInt( 15 );
			roRec.wSarrMessages = pDataReader->GetFieldAsUShort( 16 );
			roRec.timeOrbitEpoch = pDataReader->GetFieldAsTime( 17 );
			roRec.fOrbitPositionOffset = pDataReader->GetFieldAsFloat( 18 );
			roRec.fOrbitVelocityOffset = pDataReader->GetFieldAsFloat( 19 );
			roRec.timeCalibration = pDataReader->GetFieldAsTime( 20 );
			roRec.timeRollover = pDataReader->GetFieldAsTime( 21 );
			roRec.fUSOFreq = pDataReader->GetFieldAsFloat( 22 );
			roRec.fSARR406FreqOff = pDataReader->GetFieldAsFloat( 23 );
			roRec.wUnlocatedAlerts = pDataReader->GetFieldAsUShort( 24 );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCollectorForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_COLLECTOR, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

std::wstring 
CEMSDataAccessHelper::_BuildLocationStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOCATE_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLocationStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSLOCATIONINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wStatus = pDataReader->GetFieldAsUShort( 0L );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildOrbitStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_ORBIT_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleOrbitStatusData( 
						CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSORBITDETERMINEINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wStatus = pDataReader->GetFieldAsUShort( 0L );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildTCALStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SARP_CALIB_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleTCALStatusData( 
						CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSTCALINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wStatus = pDataReader->GetFieldAsUShort( 0L );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildSARRStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_SARR_CALIB_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != culSatID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszSatID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culSatID ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != culPassID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszPassID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culPassID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleSARRStatusData( 
							CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
							EMSSARRCALIBINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wStatus = pDataReader->GetFieldAsUShort( 0L );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildLogMsgCountSQL( const EMSTIME ctimeStart,
											const EMSTIME ctimeEnd,
											const ULONG culLutID,
											const EMS_RESULT chrMsg, 
											const int ciLogLevel )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectCount();

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOG, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != ctimeStart.intTime )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddGE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();

		bConditionAdded = true;
	}

	if( 0 != ctimeEnd.intTime )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszTimestamp;
		oSQLBuilder.AddLE();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();

		bConditionAdded = true;
	}

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Add Sat condition
	if( 0 != chrMsg )
	{
		// This field is stored in the database as a DWORD.

		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLogMsgNumber;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( (const DWORD) chrMsg ).c_str();

		bConditionAdded = true;
	}

	// Add Pass condition
	if( 0 != ciLogLevel )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();
		else
			oSQLBuilder.AddAnd();

		oSQLBuilder += cwszLogMsgType;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( (const long) ciLogLevel ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
//	oSQLBuilder.AddOrderBy();
//	oSQLBuilder += cwszTimestamp;
//	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleLogMsgCountData( 
						CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						ULONG& rulCount )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			rulCount = pDataReader->GetFieldAsULong( 0L );
			
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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentCommsStatusSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID )
{
	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_COMMS_STATS, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void 
CEMSDataAccessHelper::_AssembleCommsStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
										EMSCOMMSINFO& roRec )
{
	CEMSRawDataRecordReader* pDataReader = 0;

	try
	{
		olstRecords.MoveFirst();

		if( pDataReader = olstRecords.GetNext() )
		{
			roRec.wCommsStatus = pDataReader->GetFieldAsUShort( 0L );
			roRec.ulMsgID = pDataReader->GetFieldAsULong( 1 );
			roRec.ulRouteID = pDataReader->GetFieldAsULong( 2 );
			roRec.timeTx = pDataReader->GetFieldAsTime( 3 );
			roRec.ulRetryCount = pDataReader->GetFieldAsULong( 4 );
			roRec.ulLossCount = pDataReader->GetFieldAsULong( 5 );
			roRec.ulLossDuration = pDataReader->GetFieldAsULong( 6 );

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

		throw;
	}
}

std::wstring 
CEMSDataAccessHelper::_BuildCurrentLutDisplayStateSQL( const ULONG culLutID )
{
	LPCWSTR		cawszColumns[] = { cwszTimestamp, cwszLogMsgNumber };
	const short	csColumns = 2;

	std::wstring wszRet;

	CSQLBuilder oSQLBuilder;

	oSQLBuilder.AddSelectFirstOnly();
	oSQLBuilder.AddColumns( csColumns, cawszColumns );

	oSQLBuilder.AddFrom();
	oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_LOG, EMSDBVERSION_LEO_20 ).c_str() );

	bool bConditionAdded = false;

	if( 0 != culLutID )
	{
		if( !bConditionAdded )
			oSQLBuilder.AddWhere();

		oSQLBuilder += cwszLutID;
		oSQLBuilder.AddEQ();
		oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

		bConditionAdded = true;
	}

	const wchar_t* cwszDisplayStateWhereClauseFMT = 
			L"((ulProcessID = %d AND dwMsgNumber = %d) "
			L"OR (ulProcessID = %d AND dwMsgNumber = %d) "
			L"OR (ulProcessID = %d AND dwMsgNumber = %d) "
			L"OR (ulProcessID = %d AND dwMsgNumber = %d) "
			L"OR (ulProcessID = %d AND dwMsgNumber = %d) "
			L"OR (ulProcessID = %d AND dwMsgNumber = %d) )";

	wchar_t	wszDisplayStateWhereClause[512];
	swprintf( wszDisplayStateWhereClause, cwszDisplayStateWhereClauseFMT,
			EMSLOGCAT_Master, EMS_MAST_SERVICE_START,
			EMSLOGCAT_Master, EMS_MAST_PASS_END,
			EMSLOGCAT_Master, EMS_MAST_STATUS_AOS,
			EMSLOGCAT_SysTest, EMS_SYSTEST_START,
			EMSLOGCAT_SysTest, EMS_SYSTEST_STATUS_FAILED,
			EMSLOGCAT_SysTest, EMS_SYSTEST_STATUS_OKAY );

	if( bConditionAdded )
	{
		oSQLBuilder.AddAnd();
	}
	else
	{
		oSQLBuilder.AddWhere();
	}
	oSQLBuilder += wszDisplayStateWhereClause;

	// Order it so that we get the most recently generated first.
	oSQLBuilder.AddOrderBy();
	oSQLBuilder += cwszTimestamp;
	oSQLBuilder.AddDescending(); 

	wszRet = oSQLBuilder;

	return wszRet;
}

void
CEMSDataAccessHelper::_AssembleLutDisplayStateData( 
		CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
		const ULONG culIdleDelaySec,
		LUTDISPLAYSTATE& eCurrentState, EMSTIME& timeStateChange )
{
	CEMSRawDataRecordReader* pDataReader = NULL;

	olstRecords.MoveFirst();

	try
	{
		if( pDataReader = olstRecords.GetNext() )
		{
			timeStateChange = pDataReader->GetFieldAsTime( 0L );
			DWORD	dwMsgID = pDataReader->GetFieldAsULong( 1 );

			pDataReader->Release();
			pDataReader = NULL;

			eCurrentState = _DetermineLutDisplayState( timeStateChange, culIdleDelaySec, dwMsgID );
		}
	}
	catch( ... )
	{
		if( pDataReader )
		{
			pDataReader->Release();
			pDataReader = NULL;
		}
		throw;
	}
	if( pDataReader )
	{
		pDataReader->Release();
		pDataReader = NULL;
	}
}

LUTDISPLAYSTATE
CEMSDataAccessHelper::_DetermineLutDisplayState( EMSTIME& timeStateChange, 
												 const ULONG culIdleDelaySec, 
												 const DWORD dwMsgID )
{

	LUTDISPLAYSTATE	eDisplayStateRet = LUTDISPLAYSTATE_UNKNOWN;
	bool bCheckForIdle = false;

	switch( dwMsgID )
	{
	case EMS_SYSTEST_START:
		// System Test Started
		eDisplayStateRet = LUTDISPLAYSTATE_SYSTEM_TEST;
		break;
	case EMS_SYSTEST_STATUS_FAILED:
	case EMS_SYSTEST_STATUS_OKAY:
		// System Test Ended ... either still in system test or now idle
		eDisplayStateRet = LUTDISPLAYSTATE_SYSTEM_TEST;
		bCheckForIdle = true;
		break;
	case EMS_MAST_STATUS_AOS:
		// Start of pass
		eDisplayStateRet = LUTDISPLAYSTATE_PASS;
		break;
	case EMS_MAST_PASS_END:
		// Pass Ended ... either in PostPass or now idle
		eDisplayStateRet = LUTDISPLAYSTATE_POSTPASS;
		bCheckForIdle = true;
		break;
	case EMS_MAST_SERVICE_START:
		// Last thing that happened was the system starting
		eDisplayStateRet = LUTDISPLAYSTATE_IDLE;
		break;
	}
	if ( bCheckForIdle )
	{
		CEMSTime		oTimeNow ( CEMSSystemClock::GetTime() );
		CEMSTime		oTimeIdleStart( timeStateChange );
		double			dIdleDelaySec = culIdleDelaySec;
		oTimeIdleStart.AddSeconds( dIdleDelaySec );

		if ( oTimeNow.GetTimeNano() >= oTimeIdleStart.GetTimeNano() )
		{
			timeStateChange = oTimeIdleStart;
			eDisplayStateRet = LUTDISPLAYSTATE_IDLE;
		}
	}

	return eDisplayStateRet;
}
