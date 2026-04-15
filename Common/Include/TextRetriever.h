#ifndef __TEXT_RETRIEVER_H__
#define __TEXT_RETRIEVER_H__

#include <string>
using std::string;
using std::wstring;


class CEMSTextRetriever
{
	public:
		CEMSTextRetriever();
		CEMSTextRetriever( const CEMSTextRetriever& x );
		~CEMSTextRetriever();

		static wstring GetSourceText( BYTE cSrcID );
		static BYTE GetSourceID( LPCSTR szSource );
		static BYTE GetSourceID( LPCWSTR szSource );

		static wstring GetMsgTypeText( BYTE cMsgType );
		static BYTE GetMsgTypeID( LPCSTR szMsgType );
		static BYTE GetMsgTypeID( LPCWSTR szMsgType );

		// convenience function
		// that will trim leading/trailing whitespace
		// and convert the string to upper case
		static wstring	TrimToUpper( LPCWSTR szMsgType );

		static TCHAR GetIPConnType( const int ciType );
		static TCHAR GetIPState( const bool cbActive );

};

#endif // __TEXT_RETRIEVER_H__