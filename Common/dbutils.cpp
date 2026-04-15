//***************************************************************************
// Database utility functions
//***************************************************************************
//#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <comutil.h>
#include "dbutils.hpp"


// ************************************************************************
// Rules for "multiget" record requests by specifying two EMSSIGDATAID structures:
// 
// Two EMSSIGDATAID structures are provided, a start range and an end range.
// Three members in each EMSSIGDATAID: Timestamp, SatID, and LutID.
// 
// 1. If matching members in structures are both zero, the member is not to be
//    used as part of the criteria.
// 
//    ex. ( Note that field names have been simplified for these examples)
// 
//    ( minID.timestamp == 0 AND maxID.timestamp == 0 ) --> timestamp is not to be considered in the record query
// 
// 
// 2. If matching members are equal and non-zero then records containing a 
//    specific value in the corresponding column are to be queried.
// 
//    ex.
// 
//    ( minID.satID == 35 AND maxID.satID == 35 ) --> query only to return records where satID is 35
// 
// 3. If matching members are not equal then a range of values is to be queried.
// 
//    ex.
//    
//    ( minID.lutID == 2 AND maxID.lutID == 7 ) --> query to return records where lutID is 2, 3, 4, 5, 6, 7
// 
//    full ex.
// 
//    ( minID.timestamp == 182,261,798 AND maxID.timestamp == 182,500,000 )
//    ( minID.satID == 25 AND maxID.satID == 25 )
//    ( minID.lutID == 0 AND maxID.lutID == 0 )
// 
//    --> query for records where time is between 182,261,798 and 182,500,000
//        AND satID == 25
//        (any lutID)
//    --> resulting SQL statement: 
//          "select timestamp, ulsatid, ullutid from <TABLENAME> where 
//             timestamp between 182,261,798 and 182,500,000
//             and
//             ulsatid = 25"
// 
// ************************************************************************

bool
createSQLStatement(  char*          tableName,
                     EMSSIGDATAID   minID, 
                     EMSSIGDATAID   maxID,
                     char*          sqlBuf,
                     size_t         sqlBufSize )
{
   if ( sqlBuf )
   {
      bool useTimestamp = false;
      bool useSatID     = false;
      bool useLutID     = false;

      #define BUFFERSTRINGSIZE   128
      char timestampBuf[BUFFERSTRINGSIZE];
      char satIDBuf[BUFFERSTRINGSIZE];
      char lutIDBuf[BUFFERSTRINGSIZE];

      // timestamp
      if ( maxID.time.intTime == minID.time.intTime )
      {
         if ( 0 != maxID.time.intTime )         // only 1 timestamp value
         {
            useTimestamp = true;
            char* timestampFormatStr = "timestamp = %I64i";
            _sntprintf( timestampBuf, BUFFERSTRINGSIZE, 
               timestampFormatStr,
               maxID.time.intTime );
         }
      }
      else                                      // range of timestamp values
      {
         useTimestamp = true;
         char* timestampFormatStr = "timestamp between %I64i and %I64i";
         _sntprintf( timestampBuf, BUFFERSTRINGSIZE, 
            timestampFormatStr,
            minID.time.intTime,
            maxID.time.intTime );
      }
      // sat id
      if ( maxID.ulSatID == minID.ulSatID )
      {
         if ( 0 != maxID.ulSatID )              // only 1 sat ID value
         {
            useSatID = true;
            char* satIDFormatStr = "ulsatid = %lu";
            _sntprintf( satIDBuf, BUFFERSTRINGSIZE, 
               satIDFormatStr,
               maxID.ulSatID );
         }
      }
      else                                      // range of timestamp values
      {
         useSatID = true;
         char* satIDFormatStr = "ulsatid between %lu and %lu";
         _sntprintf( satIDBuf, BUFFERSTRINGSIZE, 
            satIDFormatStr,
            minID.ulSatID,
            maxID.ulSatID );
      }
      // lut id
      if ( maxID.ulLutID == minID.ulLutID )
      {
         if ( 0 != maxID.ulLutID )              // only 1 lut ID value
         {
            useLutID = true;
            char* lutIDFormatStr = "ullutid = %lu";
            _sntprintf( lutIDBuf, BUFFERSTRINGSIZE, 
               lutIDFormatStr,
               maxID.ulLutID );
         }
      }
      else                                      // range of timestamp values
      {
         useLutID = true;
         char* lutIDFormatStr = "ullutid between %lu and %lu";
         _sntprintf( lutIDBuf, BUFFERSTRINGSIZE, 
            lutIDFormatStr,
            minID.ulLutID,
            maxID.ulLutID );
      }
//    The following if statement does not allow for a "get all" request
//      if ( useTimestamp || useSatID || useLutID )  // there must be some criteria for sql statement
      {
         char* sqlFormatStr = 
            "select %s "         // columns: timestamp, sat id, lut id
            "from %s "           // table: spectrum
            "%s"                 // "where"
            "%s"                 // timestamp
            "%s"                 // "and"
            "%s"                 // sat id
            "%s"                 // "and"
            "%s";                // lut id
         
         _sntprintf( sqlBuf, sqlBufSize, 
            sqlFormatStr, 
            "timestamp, ulsatid, ullutid",
            tableName,
            (useTimestamp||useSatID||useLutID) ? " where " : "",
            useTimestamp ? timestampBuf : "",
            (useSatID && useTimestamp) ? " and " : "",
            useSatID ? satIDBuf : "",
            (useLutID && (useSatID || useTimestamp)) ? " and " : "",
            useLutID ? lutIDBuf : ""
            );
         return true;
      }
   }
   return false;
}

bool
createWhereClause( EMSSELECTCRITERIA* pCriteria, wchar_t* aFieldNames[3], BSTR& szWhere )
{
	if( pCriteria )
	{
		_bstr_t szTempWhere;

		bool bCriteriaAdded = false;

		// Is there a Satellite ID criteria?
		if( 0 != pCriteria->ulSatID1 && aFieldNames[0] )
		{
			if( !szTempWhere.length() )
				szTempWhere += L" Where ";

			bCriteriaAdded = true;

			// A field name must have been specified.
			wchar_t* szSatIDFieldName = aFieldNames[0];

			if( szSatIDFieldName )
			{
				// Is it a range of satellites?
				if( 0 != pCriteria->ulSatID2 )
				{
					szTempWhere += L"(";
					
					szTempWhere += szSatIDFieldName;
					szTempWhere += L" >= ";

					wchar_t* szSatID = NULL;
					convertToString( pCriteria->ulSatID1, szSatID );
					szTempWhere += szSatID;
					delete[] szSatID;

					szTempWhere += L" AND ";
					szTempWhere += szSatIDFieldName;
					szTempWhere += L" <= ";
					convertToString( pCriteria->ulSatID2, szSatID );
					szTempWhere += szSatID;
					delete[] szSatID;

					szTempWhere += L")";
		
				}
				else
				{
					szTempWhere += szSatIDFieldName;
					szTempWhere += L" = ";
					wchar_t* szSatID = NULL;
					convertToString( pCriteria->ulSatID1, szSatID );
					szTempWhere +=  szSatID;
					delete[] szSatID;
					
				}

			}
			else
			{
				return false;
			}
		}

		// Is there an Orbit Number criteria?
		if( 0 != pCriteria->ulOrbitNumber1 && aFieldNames[1] )
		{
			if( !szTempWhere.length() )
				szTempWhere += L" Where ";

			// A field name must have been specified.
			wchar_t* szOrbitNumberFieldName = aFieldNames[1];

			if( szOrbitNumberFieldName )
			{
				if( bCriteriaAdded )
				{
					szTempWhere += L" AND ";
				}

				bCriteriaAdded = true;

				// Is it a range of orbit numbers?
				if( 0 != pCriteria->ulOrbitNumber2 )
				{
					szTempWhere += L"(";
					
					szTempWhere += szOrbitNumberFieldName;
					szTempWhere += L" >= ";
					wchar_t* szOrbit = NULL;
					convertToString( pCriteria->ulOrbitNumber1, szOrbit );
					szTempWhere += szOrbit;
					delete[] szOrbit;
					
					szTempWhere += L" AND ";
					szTempWhere += szOrbitNumberFieldName;
					szTempWhere += L" <= ";
					
					convertToString( pCriteria->ulOrbitNumber2, szOrbit );
					szTempWhere += szOrbit;
					
					szTempWhere += L")";
		
				}
				else
				{
					szTempWhere += szOrbitNumberFieldName;
					szTempWhere += L" = ";
					
					wchar_t* szOrbit = NULL;
					convertToString( pCriteria->ulOrbitNumber1, szOrbit );
					szTempWhere += szOrbit;
					delete[] szOrbit;
				}
			}
			else
			{
				return false;
			}
		}

		// Is there a timestamp criteria?
		if( 0 != pCriteria->timeStart.intTime && aFieldNames[2] )
		{
			if( !szTempWhere.length() )
				szTempWhere += L" Where ";

			// A field name must have been specified.
			wchar_t* szTimestampFieldName = aFieldNames[2];

			if( szTimestampFieldName )
			{
				if( bCriteriaAdded )
				{
					szTempWhere += L" AND ";
				}

				bCriteriaAdded = true;

				// Is it a range of orbit numbers?
				if( 0 != pCriteria->timeEnd.intTime )
				{
					szTempWhere += L"(";
					
					szTempWhere += szTimestampFieldName;
					szTempWhere += L" >= ";
					wchar_t* szTime = NULL;
					convertToString(pCriteria->timeStart.intTime, szTime );
					szTempWhere += szTime;
					delete[] szTime;

					szTempWhere += L" AND ";
					szTempWhere += szTimestampFieldName;
					szTempWhere += L" <= ";
					convertToString( pCriteria->timeEnd.intTime, szTime );
					szTempWhere += szTime;
					delete[] szTime;

					szTempWhere += L")";
		
				}
				else
				{
					szTempWhere += szTimestampFieldName;
					szTempWhere += L" = ";
					wchar_t* szTime = NULL;
					convertToString( pCriteria->timeStart.intTime, szTime );
					szTempWhere += szTime;
					delete[] szTime;
				}
			}
			else
			{
				return false;
			}
		}
		else if( 0 != pCriteria->timeEnd.intTime && aFieldNames[2] )
		{
			if( !szTempWhere.length() )
				szTempWhere += L" Where ";

			// A field name must have been specified.
			wchar_t* szTimestampFieldName = aFieldNames[2];

			if( szTimestampFieldName )
			{
				if( bCriteriaAdded )
				{
					szTempWhere += L" AND ";
				}

				szTempWhere += szTimestampFieldName;
				szTempWhere += L" > ";
				wchar_t* szTime = NULL;
				convertToString( pCriteria->timeEnd.intTime, szTime );
				szTempWhere += szTime;
				delete[] szTime;

				bCriteriaAdded = true;


			}
		}

		szWhere = SysAllocString( szTempWhere );
	}

	return true;
}

bool
createOrderByClause( EMSSELECTCRITERIA* pCriteria, wchar_t* szColumnName, BSTR& szOrderBy )
{
	bool bRet = false;

	if( pCriteria )
	{
		if( pCriteria->bOrderByTimestamp )
		{
			if( szColumnName )
			{
				_bstr_t szTempOrderBy = L" ORDER BY ";

				szTempOrderBy += szColumnName;

				if( pCriteria->bOrderDescending )
				{
					szTempOrderBy += L" DESC";
				}
				else
				{
					szTempOrderBy += L" ASC";
				}

				szOrderBy = SysAllocString( szTempOrderBy );

				bRet = true;
			}
		}
	}

	return bRet;
}

bool
convertToString( unsigned long ulVal, char*& szString )
{
	szString = new char[34];
	memset( szString, 0, 34*sizeof(char) );

	_ultoa( ulVal, szString, 10 );

	return true;
}

bool
convertToString( unsigned long ulVal, wchar_t*& szString )
{
	szString = new wchar_t[34];
	memset( szString, 0, 34*sizeof(wchar_t) );

	_ultow( ulVal, szString, 10 );

	return true;
}

bool
convertToString( __int64 i64Val, char*& szString )
{
	szString = new char[34];
	memset( szString, 0, 34*sizeof(char) );

	_i64toa( i64Val, szString, 10 );

	return true;
}

bool
convertToString( __int64 i64Val, wchar_t*& szString )
{
	szString = new wchar_t[34];
	memset( szString, 0, 34*sizeof(wchar_t) );

	_i64tow( i64Val, szString, 10 );

	return true;
}

bool
convertToByteArray( wchar_t* szString, const long clMax, unsigned char* abyString )
{
	bool bRet = false;

	if( szString && abyString )
	{
		long lStringSize = wcstombs( 0, szString, 0 );

		// First convert the string to multibyte.
		char* szMBString = new char[lStringSize + 1];
		if( szMBString )
		{
			memset( szMBString, 0, (lStringSize + 1 ) );

			wcstombs( szMBString, szString, lStringSize );

			// Now just write it back as a byte array.  Do a direct memcpy.
			memset( abyString, 0, clMax );

			memcpy( abyString, szMBString, clMax );

			delete[] szMBString;
			szMBString = 0;
		}
	}
	
	return bRet;
}