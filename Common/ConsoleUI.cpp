
#include "consoleui.h"
#include "emsexcpt.h"
#include "commandlinehelper.h"
#include "convutility.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>

CEMSConsoleUI::CEMSConsoleUI()
{
}

CEMSConsoleUI::CEMSConsoleUI( const CEMSConsoleUI& x )
{
}

CEMSConsoleUI::~CEMSConsoleUI()
{
}

unsigned long
CEMSConsoleUI::GetULong(  const unsigned long culCharacters, const wchar_t* cwszPrompt )
{
	unsigned long ulRet = 0;

	wprintf( cwszPrompt );

	unsigned long ulCharacters = culCharacters;

	// Max characters for a ULONG limited to 10.
	if( 0 == ulCharacters || ulCharacters > 10 )
	{
		ulCharacters = 10;
	}

	wchar_t* wszLutID = new wchar_t[ ulCharacters + 1 ];

	if( !wszLutID )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memset( wszLutID, 0, (ulCharacters+1)*sizeof(wchar_t) );

	_getws( wszLutID );

	if( wcslen( wszLutID ) )
	{
		ulRet = _wtol( wszLutID );
	}

	delete[] wszLutID;
	wszLutID = 0;

	return ulRet;
}

void 
CEMSConsoleUI::OutputMsg( const wchar_t* cwszMsg, ... )
{
	va_list params;
	va_start( params, cwszMsg );

	if( cwszMsg )
	{
		vwprintf( cwszMsg, params );
	}
}

int 
CEMSConsoleUI::GetInt( const wchar_t* cwszPrompt )
{
	int iRet = 0;

	OutputMsg( cwszPrompt );

	wchar_t wszInt[10];
	memset( wszInt, 0, 10*sizeof(wchar_t) );

	_getws( wszInt );

	if( wcslen( wszInt ) )
	{
		iRet = _wtoi( wszInt );
	}

	return iRet;
}

std::wstring 
CEMSConsoleUI::GetString( const wchar_t* cwszPrompt )
{
	std::wstring wszRet;

	OutputMsg( cwszPrompt );

	wchar_t wszString[ 512 ];
	memset( wszString, 0, 512*sizeof(wchar_t) );

	_getws( wszString );

	wszRet = wszString;

	return wszRet;
}

EMSTIME
CEMSConsoleUI::GetTime( const wchar_t* cwszPrompt )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	OutputMsg( cwszPrompt );

	wchar_t wszString[ 512 ];
	memset( wszString, 0, 512*sizeof(wchar_t) );

	_getws( wszString );

	if( wcslen(wszString) > 0 || wcscmp( L"0", wszString ) != 0 )
	{
		CEMSTime oTime;
		CEMSCommandLineHelper oCmdLineHlpr;

		oCmdLineHlpr.ParseDateTime( (char*) CEMSConversionUtil::ConvertToString( wszString).c_str(), &oTime );

		timeRet = oTime;
	}

	return timeRet;
	
}