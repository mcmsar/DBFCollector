
#ifndef __SQL_VALIDATOR_H__
#define __SQL_VALIDATOR_H__

#include <list>
#include <string>

class CEMSSQLValidator
{
	public:
		CEMSSQLValidator();
		CEMSSQLValidator( const CEMSSQLValidator& x );
		~CEMSSQLValidator();

		bool HasBannedKeyword( const wchar_t* cwszSQLString );
		void AddBannedKeyword( const wchar_t* cwszKeyword );

	private:
		std::wstring _GetLowerCase( const wchar_t* cwszString );

	private:
		std::list<std::wstring>	m_lstBannedKeywords;


};

#endif