#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol size.

#include "sqlvalidator.h"
#include "emsexcpt.h"

CEMSSQLValidator::CEMSSQLValidator()
{
}

CEMSSQLValidator::CEMSSQLValidator( const CEMSSQLValidator& x )
{
	m_lstBannedKeywords = x.m_lstBannedKeywords;
}

CEMSSQLValidator::~CEMSSQLValidator()
{
}

bool 
CEMSSQLValidator::HasBannedKeyword( const wchar_t* cwszSQLString )
{
	bool bRet = false;
	
	std::wstring wszSearchString = _GetLowerCase( cwszSQLString ); 

	if( wszSearchString.length() > 0 )
	{
		std::list<std::wstring>::iterator it = m_lstBannedKeywords.begin();

		while( !bRet && m_lstBannedKeywords.end() != it )
		{
			if( std::wstring::npos != wszSearchString.find( *it ) )
			{
				bRet = true;
			}

			it++;
		}
	}

	return bRet;

}

void 
CEMSSQLValidator::AddBannedKeyword( const wchar_t* cwszKeyword )
{
	std::wstring wszKeyword = _GetLowerCase( cwszKeyword );

	if( wszKeyword.length() > 0 )
	{
		m_lstBannedKeywords.push_back( wszKeyword );
	}
}

std::wstring 
CEMSSQLValidator::_GetLowerCase( const wchar_t* cwszString )
{
	std::wstring wszRet;

	if( !cwszString )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	wchar_t* wszTemp = 0;

	try
	{
		long lLen = 0;

		if( ( lLen = wcslen( cwszString) ) > 0 )
		{
			wszTemp = new wchar_t[ lLen + 1 ];

			if( !wszTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszTemp, 0, (lLen+1)*sizeof(wchar_t) );

			wcscpy( wszTemp, cwszString );
			
			wszRet = _wcslwr( wszTemp );

			delete[] wszTemp;
			wszTemp = 0;
		}
	}
	catch( ... )
	{
		if( wszTemp )
		{
			delete[] wszTemp;
			wszTemp = 0;
		}

		throw;
	}

	return wszRet;
}