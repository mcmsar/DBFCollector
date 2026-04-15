//***************************************************************************
// Database utility functions
//***************************************************************************
#ifndef _DBUTILS_HPP_
#define _DBUTILS_HPP_

#include <sigdata.h>
#include "leolut600dbs.h"
//#include <stdio.h>

//***************************************************************************
//** Function declarations **************************************************

bool
createSQLStatement(  char*          tableName,
                     EMSSIGDATAID   minID, 
                     EMSSIGDATAID   maxID,
                     char*          sqlBuf,
                     size_t         sqlBufSize );

bool
createWhereClause( EMSSELECTCRITERIA* pCriteria, wchar_t* aFieldNames[3], BSTR& szWhere );

bool
createOrderByClause( EMSSELECTCRITERIA* pCriteria, wchar_t* szColumnName, BSTR& szOrderBy );

bool
convertToString( unsigned long ulVal, char*& szString );

bool
convertToString( unsigned long ulVal, wchar_t*& szString );

bool
convertToString( __int64 i64Val, char*& szString );

bool
convertToString( __int64 i64Val, wchar_t*& szString );

bool
convertToByteArray( wchar_t* szString, const long clMax,  unsigned char* abyString );

//***************************************************************************
#endif
