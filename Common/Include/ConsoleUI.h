
#ifndef __CONSOLE_USER_INTERFACE_H__
#define __CONSOLE_USER_INTERFACE_H__

#include <wchar.h>
#include <string>
#include "emstime.h"

class CEMSConsoleUI
{
	public:
		CEMSConsoleUI();
		CEMSConsoleUI( const CEMSConsoleUI& x );
		~CEMSConsoleUI();

		unsigned long	GetULong( const unsigned long culCharacters, const wchar_t* cwszPrompt);
		void			OutputMsg( const wchar_t* cwszMsg, ... );
		int				GetInt( const wchar_t* cwszPrompt );
		std::wstring	GetString( const wchar_t* cwszPrompt );
		EMSTIME			GetTime( const wchar_t* cwszPrompt ); 
};

#endif