#ifndef __SQLBUILDER_H__
#define __SQLBUILDER_H__

#include <string>
#include "sqlstringconstants.h"

class CSQLBuilder
{
	public:
		CSQLBuilder();
		CSQLBuilder( const CSQLBuilder& x );
		CSQLBuilder( const wchar_t* cwszStmt );
		~CSQLBuilder();
		
		void AddWhere( const wchar_t* cwszWhere );
		void AddWhere();
		void AddSelectAll();
		void AddSelectFirstOnly();
		void AddSelectAllFirstOnly();
		void AddSelectColumns( const short csColumns, const wchar_t** cawszColumns );
		void AddSelectDistinctColumns( const short csColumns, const wchar_t** cawszColumns );
		void AddSelectFirstColumns( const short csColumns, const wchar_t** cawszColumns );
		void AddSelectCount();
		void AddColumns( const short csColumns, const wchar_t** cawszColumns );
		void AddFrom();
		void AddSpace();
		long Length() { return m_wszSQLStatement.length(); }
		void AddTable( const wchar_t* cwszTable );
		void AddDeleteFrom();
		void AddLT() { m_wszSQLStatement.append( cwszLT ); }
		void AddLE() { m_wszSQLStatement.append( cwszLE ); }
		void AddGT() { m_wszSQLStatement.append( cwszGT ); }
		void AddGE() { m_wszSQLStatement.append( cwszGE ); }
		void AddAnd() { m_wszSQLStatement.append( cwszAND ); }
		void AddOr() { m_wszSQLStatement.append( cwszOR ); }
		void AddEQ() { m_wszSQLStatement.append( cwszEQ ); }
		void AddNE() { m_wszSQLStatement.append( cwszNE ); }
		void AddBitAnd() { m_wszSQLStatement.append( cwszBITAND ); }
		void AddBitOr() { m_wszSQLStatement.append( cwszBITOR ); }
		void AddNot() { m_wszSQLStatement.append( cwszNot ); }
		CSQLBuilder& operator+=( const wchar_t* cwszValue );
		operator std::wstring(){ return m_wszSQLStatement; }
		void OpenParenth();
		void CloseParenth();
		void AddOrderBy() { m_wszSQLStatement.append( cwszORDERBY ); }
		void AddAscending() { m_wszSQLStatement.append( cwszASCENDING ); }
		void AddDescending() { m_wszSQLStatement.append( cwszDESCENDING ); }
		void AddComma() { m_wszSQLStatement.append( cwszCOMMA ); }

		bool HasWhere();

		void AddLimit( const int ciRows );


/*		
		void AddSelectAllFields();
		void AddField( OLECHAR* oszFieldName );
		HRESULT AddFields( OLECHAR** aoszFields );
		
		void AddAnd();
		void AddIn();
		HRESULT AddIn( const OLECHAR* oszFieldName, const OLECHAR* oszValues, BOOL bNoAnd = FALSE );
		HRESULT AddCondition( const OLECHAR* oszFieldName, const OLECHAR* oszFieldValue, int eOp, BOOL bNoAnd = FALSE, BOOL bIsString = FALSE );
		void AddComma();
		
		HRESULT AddComparisonOp( int eOp );
		
		CSQLBuilder& operator+=( OLECHAR* oszValue) { m_bszSQLStatement.Append( oszValue ); return *this; }
		CSQLBuilder& operator=( BSTR bszValue ) { m_bszSQLStatement = bszValue; return *this; }
		operator BSTR() { return m_bszSQLStatement.Copy(); }
		
		BSTR GetStringPtr() { return m_bszSQLStatement.m_str; }

		BOOL AreConditions() { return m_bHasCondition; }

		//
		// Conversion Helpers
		//
		static HRESULT ConvertToString( INT64 i64Value, BSTR& bszValue );
		static HRESULT ConvertToString( BYTE byValue, BSTR& bszValue );
		static HRESULT ConvertToString( WORD wValue, BSTR& bszValue );
		static HRESULT ConvertToString( long lValue, BSTR& bszValue );
		static HRESULT ConvertToString( BYTE* abyValue, long lArraySize, BSTR& bszValue );

		//
		// For Debugging
		// 
		HRESULT DumpToFile( char* szFileName );



	private:	// methods
		HRESULT OperatorToString( int eOp, BSTR& bszOp );
*/
	private:	// data
//		bool			m_bHasCondition;
//		bool			m_bHasField;
		std::wstring	m_wszSQLStatement;
};

#endif //__SQLBUILDER_H__