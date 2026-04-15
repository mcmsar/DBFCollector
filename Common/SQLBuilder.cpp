#include "sqlbuilder.h"

#include <sstream>
//#include <iomanip>

CSQLBuilder::CSQLBuilder() //: m_bHasCondition(FALSE), m_bHasField(FALSE)
{
}

CSQLBuilder::CSQLBuilder( const CSQLBuilder& x )
{
	m_wszSQLStatement = x.m_wszSQLStatement;
}

CSQLBuilder::CSQLBuilder( const wchar_t* cwszStmt ) : m_wszSQLStatement( cwszStmt )
{
}

CSQLBuilder::~CSQLBuilder()
{
}

void
CSQLBuilder::AddWhere( const wchar_t* cwszWhere )
{
	m_wszSQLStatement.append( cwszWHERE );

	m_wszSQLStatement.append( cwszWhere );

	return;
}

void
CSQLBuilder::AddWhere()
{
	m_wszSQLStatement.append( cwszWHERE );
}

void 
CSQLBuilder::AddSelectColumns( const short csColumns, const wchar_t** cawszColumns )
{
	m_wszSQLStatement.append( cwszSELECT );

	for( short s = 0; s < csColumns; s++ )
	{
		if( s > 0 )
			AddComma();

		m_wszSQLStatement.append( cawszColumns[s] );
	}
}

void 
CSQLBuilder::AddSelectDistinctColumns( const short csColumns, const wchar_t** cawszColumns )
{
	m_wszSQLStatement.append( cwszSELECTDISTINCT );

	for( short s = 0; s < csColumns; s++ )
	{
		if( s > 0 )
			AddComma();

		m_wszSQLStatement.append( cawszColumns[s] );
	}
}

void 
CSQLBuilder::AddSelectFirstColumns( const short csColumns, const wchar_t** cawszColumns )
{
	m_wszSQLStatement.append( cwszSELECTFIRSTONLY );

	for( short s = 0; s < csColumns; s++ )
	{
		if( s > 0 )
			AddComma();

		m_wszSQLStatement.append( cawszColumns[s] );
	}
}

void 
CSQLBuilder::AddColumns( const short csColumns, const wchar_t** cawszColumns )
{
	for( short s = 0; s < csColumns; s++ )
	{
		if( s > 0 )
			AddComma();

		m_wszSQLStatement.append( cawszColumns[s] );
	}
}

//void
//CSQLBuilder::AddSelect()
//{
//	m_wszSQLStatement.Append( koszSELECT );
//
//	return;
//}

void
CSQLBuilder::AddSelectAll()
{
	m_wszSQLStatement.append( cwszSELECTALLFIELDS );

	return;
}

void 
CSQLBuilder::AddSelectAllFirstOnly()
{
	m_wszSQLStatement.append( cwszSELECTALLFIELDSFIRSTONLY );

	return;
}

void 
CSQLBuilder::AddSelectFirstOnly()
{
	m_wszSQLStatement.append( cwszSELECTFIRSTONLY );

	return;
}

void 
CSQLBuilder::AddSelectCount()
{
	m_wszSQLStatement.append( cwszSELECTCOUNT );
}

void
CSQLBuilder::AddFrom()
{
	//From is usually in the middle of the string.
	//So automatically put a space in front of it.
	m_wszSQLStatement.append( cwszFROM );

	return;
}

void
CSQLBuilder::AddSpace()
{
	m_wszSQLStatement.append( cwszSPACE );

	return;
}

void 
CSQLBuilder::AddTable( const wchar_t* cwszTable )
{
	m_wszSQLStatement.append( cwszTable );
}

void
CSQLBuilder::AddDeleteFrom()
{
	m_wszSQLStatement.append( cwszDELETE_FROM );
}

CSQLBuilder& 
CSQLBuilder::operator+=( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		m_wszSQLStatement.append( cwszValue );
	}

	return *this;
}

void
CSQLBuilder::OpenParenth()
{
	m_wszSQLStatement.append( cwszOpenParenth );

	return;
}

void
CSQLBuilder::CloseParenth()
{
	m_wszSQLStatement.append( cwszCloseParenth );

	return;
}

bool 
CSQLBuilder::HasWhere()
{
	bool bRet = false;

	// Convert to upper case.
	//std::wstringstream wszUpperSQL;
	std::wstring wszUpperSQL;

	if( !m_wszSQLStatement.empty() )
	{
		long lLen = m_wszSQLStatement.length();

		wchar_t* wszTemp = new wchar_t[ lLen + 1 ];

		if( wszTemp )
		{

			memset( wszTemp, 0, (lLen+1)*sizeof(wchar_t) );
			wcscpy( wszTemp, m_wszSQLStatement.c_str() );
			_wcsupr( wszTemp );

			wszUpperSQL = wszTemp;

			delete[] wszTemp;
			wszTemp = 0;
		}

		// This would be more efficient than creating a copy of the string, converting it to uppercase
		// and then assigning it to a std::wstring, but it doesn't seem to properly do the
		// conversion to uppercase.
//		wszUpperSQL << std::setiosflags(std::ios::uppercase) << m_wszSQLStatement;
	}

	std::wstring::size_type iPos = wszUpperSQL.find( cwszWHERE );

	if( m_wszSQLStatement.npos != iPos )
		bRet = true;

	return bRet;
}

void 
CSQLBuilder::AddLimit( const int ciRows )
{
	m_wszSQLStatement.append( cwszLIMIT );

	wchar_t wszRows[16];
	swprintf( wszRows, L"%d", ciRows );

	m_wszSQLStatement.append( wszRows );
}


/*
void
CSQLBuilder::AddField( OLECHAR* oszFieldName )
{
	if( m_bHasField )
	{
		AddComma();
	}

	m_bHasField = TRUE;

	

	m_bszSQLStatement.Append( oszFieldName );

	return;
}

HRESULT
CSQLBuilder::AddFields( OLECHAR** aoszFields )
{
	//*****Note*****
	// The input array must be terminated with a NULL OLECHAR*
	//**************
	HRESULT hr = S_OK;

	if( !aoszFields )
	{
		hr = E_POINTER;
	}

	long lIndex = 0L;
	while( aoszFields[lIndex] )
	{
		AddField( aoszFields[lIndex] );
		lIndex++;
	}

	return hr;
}

void
CSQLBuilder::OpenParenth()
{
	m_bszSQLStatement.Append( koszOpenParenth );

	return;
}

void
CSQLBuilder::CloseParenth()
{
	m_bszSQLStatement.Append( koszCloseParenth );

	return;
}

void 
CSQLBuilder::AddAnd()
{
	m_bszSQLStatement.Append( koszAND );

	return;
}

void
CSQLBuilder::AddIn()
{
	m_bszSQLStatement.Append( koszIN );
	m_bHasCondition = TRUE;

	return;
}

HRESULT
CSQLBuilder::AddIn( const OLECHAR* oszFieldName, const OLECHAR* oszValues, BOOL bNoAnd )
{
	HRESULT hr = S_OK;

	if( !oszFieldName || !oszValues )
	{
		hr = E_POINTER;
	}

	if( SUCCEEDED(hr) )
	{
		// Do superficial format check on the values string
		if( oszValues[0] )
		{
			if( oszValues[0] != L'(' )
			{
				hr = E_INVALIDARG;
			}
		}
		else
		{
			hr = E_INVALIDARG;
		}
	}

	if( SUCCEEDED(hr) )
	{
		if( m_bHasCondition && !bNoAnd )
		{
			m_bszSQLStatement.Append( koszAND );
		}

		m_bHasCondition = TRUE;

		m_bszSQLStatement.Append( oszFieldName );

		AddSpace();

		AddIn();

		// It's assumed that the values are specified as:  "( 3232, 4, 5, etc. )"

		m_bszSQLStatement.Append( oszValues );

	}

	return hr;
}

void
CSQLBuilder::AddComma()
{
	m_bszSQLStatement.Append( koszCOMMA );

	return;
}

HRESULT
CSQLBuilder::AddCondition( const OLECHAR* oszFieldName, 
						   const OLECHAR* oszFieldValue, 
						   int eOp, 
						   BOOL bNoAnd,
						   BOOL bIsString )
{
	HRESULT hr = S_OK;

	if( oszFieldName && oszFieldValue )
	{
		if( m_bHasCondition && !bNoAnd )
		{
			m_bszSQLStatement.Append( koszAND );
		}
		
		m_bHasCondition = TRUE;

		m_bszSQLStatement.Append( oszFieldName );

		CComBSTR bszOperator;
		hr = OperatorToString( eOp, (BSTR&) bszOperator );

		if( SUCCEEDED(hr) )
		{
			AddSpace();
			m_bszSQLStatement.Append( bszOperator );
			

			if( bIsString )
			{
				m_bszSQLStatement.Append( koszSINGLEQUOTE );
			}

			m_bszSQLStatement.Append( oszFieldValue );

			if( bIsString )
			{
				m_bszSQLStatement.Append( koszSINGLEQUOTE );
			}

			//Add a space in case more conditions are added.
			AddSpace();
		}

	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}


HRESULT
CSQLBuilder::AddComparisonOp( int eOp )
{
	CComBSTR bszOp;
	HRESULT hr = OperatorToString( eOp, (BSTR&) bszOp );

	if( SUCCEEDED(hr) )
	{
		m_bszSQLStatement.AppendBSTR( bszOp );
	}

	return hr;
}

HRESULT
CSQLBuilder::OperatorToString( int iOp, BSTR& bszOp )
{
	HRESULT hr = S_OK;

	CComBSTR bszTempOp;

	COMPARISON_OP eOp = (COMPARISON_OP) iOp;

	switch( eOp )
	{
		case OP_EQ:
			bszTempOp = koszEQ;
			break;
		case OP_LT:
			bszTempOp = koszLT;
			break;
		case OP_LE:
			bszTempOp = koszLE;
			break;
		case OP_GT:
			bszTempOp = koszGT;
			break;
		case OP_GE:
			bszTempOp = koszGE;
			break;
		default:
			hr = E_INVALIDARG;
			break;
	}

	if( SUCCEEDED(hr) )
	{
		bszOp = bszTempOp.Detach();
	}

	return hr;
}

HRESULT
CSQLBuilder::ConvertToString( INT64 i64Value, BSTR& bszValue )
{
	HRESULT hr = S_OK;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	bszValue = SysAllocStringLen( NULL, 33 );

	if( bszValue )
	{
		memset( bszValue, 0, 33*sizeof(OLECHAR) );
		_i64tow( i64Value, bszValue, 10 );
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}

	return hr;
}

HRESULT
CSQLBuilder::ConvertToString( BYTE byValue, BSTR& bszValue )
{
	HRESULT hr = S_OK;

	CComVariant vValue;

	vValue.vt = VT_UI1;
	vValue.bVal = byValue;

	hr = vValue.ChangeType( VT_BSTR );

	if( SUCCEEDED(hr) )
	{
		bszValue = SysAllocString( vValue.bstrVal );
	}

	return hr;
}

HRESULT
CSQLBuilder::ConvertToString( WORD wValue, BSTR& bszValue )
{
	HRESULT hr = S_OK;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	bszValue = SysAllocStringLen( NULL, 33 );

	if( bszValue )
	{
		memset( bszValue, 0, 33*sizeof(OLECHAR) );
		_itow( wValue, bszValue, 10 );
	}
	else
	{
		hr = E_OUTOFMEMORY;
	
	}

	return hr;
}

HRESULT
CSQLBuilder::ConvertToString( long lValue, BSTR& bszValue )
{
	HRESULT hr = S_OK;

	//Allocate the buffer.
	//Max return size from _i64tow() is 33.
	bszValue = SysAllocStringLen( NULL, 33 );

	if( bszValue )
	{
		memset( bszValue, 0, 33*sizeof(OLECHAR) );
		_ltow( lValue, bszValue, 10 );
	}
	else
	{
		hr = E_OUTOFMEMORY;
	
	}

	return hr;
}

HRESULT
CSQLBuilder::ConvertToString( BYTE* abyValue, long lArraySize, BSTR& bszValue )
{
	HRESULT hr = S_OK;

	CComBSTR bszRetValue;
	for( long l = 0; l < lArraySize && SUCCEEDED(hr); l++ )
	{
		CComBSTR bszTemp;
		hr = ConvertToString( abyValue[l], (BSTR&) bszTemp );

		if( SUCCEEDED(hr) )
		{
			bszRetValue.Append( bszTemp );
		}
	}

	if( SUCCEEDED(hr) )
	{
		bszValue = bszRetValue.Detach(); 
	}


	return hr;
}

HRESULT
CSQLBuilder::DumpToFile( char* szFileName )
{
	HRESULT hr = S_OK;

	if( szFileName )
	{
		FILE* fp = fopen( szFileName, "w+" );

		if( fp )
		{
			if( m_bszSQLStatement.Length() > 0 )
			{
				fwprintf( fp, L"\n%s", GetStringPtr() );
			}
			else
			{
				fprintf( fp, "\nEmpty" );
			}

			fflush( fp );
			fclose( fp );
		}
		else
		{
			hr = E_FAIL;
		}
	}

	return hr;
}
*/