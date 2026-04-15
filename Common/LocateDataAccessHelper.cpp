#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol size.

#include "assert.h"
#include "sqlbuilder.h"
#include "emsdbfieldnames.h"
#include "convutility.h"
#include "emsrecordset.h"
#include "emsexcpt.h"
#include "../../dal/locateformatter.h"
#include "LocateDataAccessHelper.h"

CEMSLocateDataAccessHelper::CEMSLocateDataAccessHelper()
{
}

CEMSLocateDataAccessHelper::CEMSLocateDataAccessHelper( const CEMSLocateDataAccessHelper& x )
{
}
CEMSLocateDataAccessHelper::~CEMSLocateDataAccessHelper()
{
}

// To build a where clause to find location records of one or more types
// E.g.		(	( wType & EMSLOCTYPE_REAL_BASE_MASK ) = EMSLOCTYPE_406_SARR
//			 OR	( wType & EMSLOCTYPE_REAL_BASE_MASK ) = EMSLOCTYPE_406_SARP )
std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_IncludeTypes( const std::vector<EMSLOCATETYPE>& crvectType )
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	for ( int i=0; i < crvectType.size(); i++ )
	{
		if ( i>0 ) oSQLWhere.AddOr();

		oSQLWhere += GetWhereClause_IncludeType( crvectType[i] ).c_str();
	}

	oSQLWhere.CloseParenth();
	return oSQLWhere;
}

std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_IncludeType( const EMSLOCATETYPE ceType )
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();
	oSQLWhere += cwszType;
	oSQLWhere.AddBitAnd();
	oSQLWhere += CEMSConversionUtil::ConvertToString( (long)EMSLOCTYPE_REAL_BASE_MASK ).c_str();
	oSQLWhere.CloseParenth();
	oSQLWhere.AddEQ();
	oSQLWhere += CEMSConversionUtil::ConvertToString( (long)ceType ).c_str();

	return oSQLWhere;
}

// To build a where clause to exclude location records of one or more sub-types
// E.g.		(	( wType & EMSLOCTYPE_DETECT_ONLY ) <> EMSLOCTYPE_DETECT_ONLY
//			 AND	( wType & EMSLOCTYPE_B_SIDE ) <> EMSLOCTYPE_B_SIDE )
std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_ExcludeSubTypes( const std::vector<EMSLOCATETYPE>& crvectType )
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	for ( int i=0; i < crvectType.size(); i++ )
	{
		if ( i>0 ) oSQLWhere.AddAnd();

		oSQLWhere.OpenParenth();
		oSQLWhere += cwszType;
		oSQLWhere.AddBitAnd();
		oSQLWhere += CEMSConversionUtil::ConvertToString( (long)crvectType[i] ).c_str();
		oSQLWhere.CloseParenth();
		oSQLWhere.AddNE();
		oSQLWhere += CEMSConversionUtil::ConvertToString( (long)crvectType[i] ).c_str();
	}

	oSQLWhere.CloseParenth();
	return oSQLWhere;
}


// To build a where clause to find location records that were created within a
// specified time frame.
std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_Time(
			const EMSTIME				ctimeStart, 
			const EMSTIME				ctimeEnd )
{
	if ( !ctimeStart.intTime && !ctimeEnd.intTime ) 
	{
		// nothing to do
		return L"";
	}

	bool			bHasCondition = false;
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	if ( ctimeStart.intTime )
	{
		oSQLWhere += L"\"";
		oSQLWhere += cwszTimestamp;
		oSQLWhere += L"\"";
		oSQLWhere.AddGE();
		oSQLWhere += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();
		bHasCondition = true;
	}

	if ( ctimeEnd.intTime )
	{
		if ( bHasCondition ) oSQLWhere.AddAnd();
	
		oSQLWhere += L"\"";
		oSQLWhere += cwszTimestamp;
		oSQLWhere += L"\"";
		oSQLWhere.AddLE();
		oSQLWhere += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();
		bHasCondition = true;
	}
	oSQLWhere.CloseParenth();
	return oSQLWhere;
}

// To build a where clause to find location records for one or more given beacons
std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_Beacons( const std::vector<INT64>& crvectBeaconID )
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();
	for ( int i=0; i<crvectBeaconID.size(); i++ )
	{
		if ( i>0 ) oSQLWhere.AddOr();
		oSQLWhere += cwszLocateBeaconID;
		oSQLWhere.AddEQ();
		oSQLWhere += CEMSConversionUtil::ConvertToString( crvectBeaconID[i] ).c_str();
	}
	oSQLWhere.CloseParenth();
	return oSQLWhere;
}

std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_Beacons( const INT64 ci64BeaconID )
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	oSQLWhere += cwszLocateBeaconID;
	oSQLWhere.AddEQ();
	oSQLWhere += CEMSConversionUtil::ConvertToString( ci64BeaconID ).c_str();

	oSQLWhere.CloseParenth();
	return oSQLWhere;
}


std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_Nominal()
{

	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	// 4 or more data points
	//  " AND wNumMsgs >= 4 "
	oSQLWhere += cwszLocateNumBurstsUsed; //cwszLocateNumMsgs;
	oSQLWhere.AddGE();
	oSQLWhere += L" 4 ";

	// data points bracketing the TCA of the satellite to the beacon
	//	" AND u64DataStartTime =< u64TimeTCA AND u64DataEndTime >= u64TimeTCA "
	oSQLWhere.AddAnd();
	oSQLWhere += cwszLocateDataStartTime;
	oSQLWhere.AddLE();
	oSQLWhere += cwszLocateTimeTCA;
	oSQLWhere.AddAnd();
	oSQLWhere += cwszLocateDataEndTime;
	oSQLWhere.AddGE();
	oSQLWhere += cwszLocateTimeTCA;

	// having an absolute value of cross-track angle (|CTA|) between 1 degree and 20 degrees
	//  " AND 1 <= ABS(fCrossTrackAngle) AND 20 >= ABS(fCrossTrackAngle) "
	oSQLWhere.AddAnd();
	oSQLWhere += L" 1 ";
	oSQLWhere.AddLE();
	oSQLWhere += L" ABS(";
	oSQLWhere += cwszLocateCrossTrackAngle;
	oSQLWhere += L") ";
	oSQLWhere.AddAnd();
	oSQLWhere += L" 20 ";
	oSQLWhere.AddGE();
	oSQLWhere += L" ABS(";
	oSQLWhere += cwszLocateCrossTrackAngle;
	oSQLWhere += L") ";

	oSQLWhere.CloseParenth();
	return oSQLWhere;
}

std::wstring 
CEMSLocateDataAccessHelper::GetWhereClause_Marginal()
{
	CSQLBuilder		oSQLWhere;

	oSQLWhere.OpenParenth();

	// NOT (4 or more data points)
	//  " wNumMsgs < 4 "
	oSQLWhere += cwszLocateNumBurstsUsed; //cwszLocateNumMsgs;
	oSQLWhere.AddLT();
	oSQLWhere += L" 4 ";

	// OR NOT (data points bracketing the TCA of the satellite to the beacon)
	//  " OR u64DataStartTime > u64TimeTCA OR u64DataEndTime < u64TimeTCA "
	oSQLWhere.AddOr();
	oSQLWhere += cwszLocateDataStartTime;
	oSQLWhere.AddGT();
	oSQLWhere += cwszLocateTimeTCA;
	oSQLWhere.AddOr();
	oSQLWhere += cwszLocateDataEndTime;
	oSQLWhere.AddLT();
	oSQLWhere += cwszLocateTimeTCA;

	// OR NOT (having an absolute value of cross-track angle (|CTA|) between 1 degree and 20 degrees)
	//  " OR 1 > ABS(fCrossTrackAngle) OR 20 < ABS(fCrossTrackAngle) "
	oSQLWhere.AddOr();
	oSQLWhere += L" 1 ";
	oSQLWhere.AddGT();
	oSQLWhere += L" ABS(";
	oSQLWhere += cwszLocateCrossTrackAngle;
	oSQLWhere += L") ";
	oSQLWhere.AddOr();
	oSQLWhere += L" 20 ";
	oSQLWhere.AddLT();
	oSQLWhere += L" ABS(";
	oSQLWhere += cwszLocateCrossTrackAngle;
	oSQLWhere += L") ";

	oSQLWhere.CloseParenth();

	return oSQLWhere;
}

ULONG CEMSLocateDataAccessHelper::GetCount(
			const wchar_t*				cwszDSN,
			const wchar_t*				cwszSQLWhere )
{
	ULONG				ulCount = 0L;

	EMS_RESULT			hr = EMS_OK;
	CEMSRecordset		oRS;

	// Query for the locations
	wchar_t wszDSN[ 256 ];
	swprintf( wszDSN, L"DSN=%s", cwszDSN );

	CSQLBuilder		oSQL;

	oSQL.AddSelectCount();
	oSQL.AddFrom();
	oSQL.AddTable( L"LOCATE_DATA" );
	if ( cwszSQLWhere && wcslen( cwszSQLWhere ) )
	{
		oSQL.AddWhere();
		oSQL+= cwszSQLWhere;
	}

	std::wstring wstrSQL = oSQL;

#ifdef _DEBUG
	{
		char	szTemp[1024];
		sprintf( szTemp, "GetCount() SQL: %S\n", wstrSQL.c_str() );
		OutputDebugString(szTemp);
	}
#endif

	oRS.Open( wszDSN, wstrSQL.c_str() );

	// Should return a single value in a single record
	if ( !oRS.IsEOF() && !oRS.IsBOF() )
	{
		oRS.MoveFirst();
		const long clIndex = 0;
		ulCount = oRS.GetULongValue( clIndex );
	}
	return ulCount;
}

bool CEMSLocateDataAccessHelper::GetLocations(
			const wchar_t*				cwszDSN,
			const wchar_t*				cwszSQLWhere, 
			std::vector<EMSLOCATE>&		rvectLocations,
			const ULONG					culMaxLocations )
{
	EMS_RESULT			hr = EMS_OK;
	CEMSRecordset		oRS;
	EMSVARIANTRECORD*	aRecs = NULL;
	bool				bMore = false;

	try
	{
		// Query for the locations
		wchar_t wszDSN[ 256 ];
		swprintf( wszDSN, L"DSN=%s", cwszDSN );

		CSQLBuilder		oSQL;

		oSQL.AddSelectAll();
		oSQL.AddTable( L"LOCATE_DATA" );
		if ( cwszSQLWhere && wcslen( cwszSQLWhere ) )
		{
			oSQL.AddWhere();
			oSQL+= cwszSQLWhere;
		}

		std::wstring wstrSQL = oSQL;

#ifdef _DEBUG
		{
			char	szTemp[1024];
			sprintf( szTemp, "_GetLocations() SQL: %S\n", wstrSQL.c_str() );
			OutputDebugString(szTemp);
		}
#endif

		oRS.Open( wszDSN, wstrSQL.c_str() );

		ULONG ulRecs = 0;
		CEMSLocateFormatter oFormatter;
		bMore = oFormatter.Format( culMaxLocations, &oRS, &ulRecs, &aRecs );

		for( int i = 0; i < ulRecs; i++ )
		{
			rvectLocations.push_back( aRecs[i].data.locate );
		}

		CoTaskMemFree( aRecs );
		aRecs = NULL;
	}
	catch( ... )
	{
		if ( aRecs )
		{
			CoTaskMemFree( aRecs );
			aRecs = NULL;
		}
		throw;
	}
	return bMore;
}
