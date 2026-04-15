
#include "emstypes.h"

#include "TextRetriever.h"

#include "loggrcat.h"	// EMSLOGCAT_ values
#include "emsloggr.h"	// EMSLOGMSGTYPE enum
#include "convutility.h"

#include "assert.h"
#include "LangResources.h"
#include "netconnmgr.h"

CEMSTextRetriever::CEMSTextRetriever()
{
}

CEMSTextRetriever::CEMSTextRetriever( const CEMSTextRetriever& x )
{
}

CEMSTextRetriever::~CEMSTextRetriever()
{
}

// returns "Unknown" if no match found
wstring
CEMSTextRetriever::GetSourceText( BYTE cSrcID )
{
	BYTE	cID = EMSLOGCAT_Unknown;

	if ( EMSLOGCAT_VALID( cSrcID ) ) cID = cSrcID;

	return CEMSLangResources::GetString( cID );
}

// returns zero if no match found
BYTE 
CEMSTextRetriever::GetSourceID( LPCSTR szSource )
{
	wstring	wstr = CEMSConversionUtil::ConvertToString( szSource );
	return GetSourceID( wstr.c_str() );
}
BYTE 
CEMSTextRetriever::GetSourceID( LPCWSTR szSource )
{
	BYTE	cRet = 0;
	wstring	wstrSupplied = TrimToUpper( szSource );
	wstring	wstrComp;

	for ( DWORD dwMsgID=EMSLOGCAT_MIN; dwMsgID<=EMSLOGCAT_MAX && cRet==0; dwMsgID++ )
	{
		wstrComp = TrimToUpper( CEMSLangResources::GetString( dwMsgID ).c_str() );
		if ( wstrComp.compare( 0, wstrComp.length(), wstrSupplied ) == 0 )
		{
			cRet = dwMsgID;
		}
	}

	return cRet;
}

// Returns "Unknown" if no match found
wstring
CEMSTextRetriever::GetMsgTypeText( BYTE cMsgType )
{
	DWORD	dwMsgID = 0;
	switch ( cMsgType )
	{
		case EMSLogMsgInfo:			dwMsgID = EMSLOGMSGTYPESTR_INFO;		break;
		case EMSLogMsgStatus:		dwMsgID = EMSLOGMSGTYPESTR_STATUS;		break;
		case EMSLogMsgMoreStatus:	dwMsgID = EMSLOGMSGTYPESTR_MORESTATUS;	break;
		case EMSLogMsgStartup:		dwMsgID = EMSLOGMSGTYPESTR_STARTUP;		break;
		case EMSLogMsgAlarm:		dwMsgID = EMSLOGMSGTYPESTR_ALARM;		break;
		case EMSLogMsgFatal:		dwMsgID = EMSLOGMSGTYPESTR_FATAL;		break;
		case EMSLogMsgWarn:			dwMsgID = EMSLOGMSGTYPESTR_WARNING;		break;
		case EMSLogMsgTrace:		dwMsgID = EMSLOGMSGTYPESTR_TRACE;		break;
		case EMSLogMsgDebug:		dwMsgID = EMSLOGMSGTYPESTR_DEBUG;		break;
		default:					dwMsgID = EMSLOGMSGTYPESTR_UNKNOWN;		break;	
	}
	return CEMSLangResources::GetString( dwMsgID );
}

// Returns 0 if no match found
BYTE 
CEMSTextRetriever::GetMsgTypeID( LPCSTR szMsgType )
{
	wstring	wstr = CEMSConversionUtil::ConvertToString( szMsgType );
	return GetMsgTypeID( wstr.c_str() );
}

BYTE 
CEMSTextRetriever::GetMsgTypeID( LPCWSTR szMsgType )
{
	BYTE	cRet = 0;
	bool    bFound = false;

	DWORD	dwMatchingStrID = 0;
	wstring	wstrComp;
	wstring	wstrSupplied = TrimToUpper( szMsgType );

	for (	DWORD dwMsgID=EMSLOGMSGTYPESTR_MIN; 
			dwMsgID <= EMSLOGMSGTYPESTR_MAX && !bFound; 
			dwMsgID++ )
	{
		wstrComp = TrimToUpper( CEMSLangResources::GetString( dwMsgID ).c_str() );

		if ( wstrComp.compare( 0, wstrComp.length(), wstrSupplied ) == 0 )
		{
			dwMatchingStrID = dwMsgID;
			bFound = true;
		}
	}
	// Map the matching string identifier onto the message type
	switch ( dwMatchingStrID )
	{
		case EMSLOGMSGTYPESTR_INFO:			cRet = EMSLogMsgInfo;		break;
		case EMSLOGMSGTYPESTR_STATUS:		cRet = EMSLogMsgStatus;		break;
		case EMSLOGMSGTYPESTR_MORESTATUS:	cRet = EMSLogMsgMoreStatus; break;
		case EMSLOGMSGTYPESTR_STARTUP:		cRet = EMSLogMsgStartup;	break;
		case EMSLOGMSGTYPESTR_ALARM:		cRet = EMSLogMsgAlarm;		break;
		case EMSLOGMSGTYPESTR_FATAL:		cRet = EMSLogMsgFatal;		break;
		case EMSLOGMSGTYPESTR_WARNING:		cRet = EMSLogMsgWarn;		break;
		case EMSLOGMSGTYPESTR_TRACE:		cRet = EMSLogMsgTrace;		break;
		case EMSLOGMSGTYPESTR_DEBUG:		cRet = EMSLogMsgDebug;		break;
	}
	return cRet;
}

wstring
CEMSTextRetriever::TrimToUpper( LPCWSTR szMsgType )
{
	int	iLen = wcslen( szMsgType );
	int iStart=0;
	int iEnd=iLen-1;

	assert( iLen < 128 );
	wchar_t	wsz[128];

	// skip over leading whitespace
	while( iStart<iLen && iswspace(szMsgType[iStart]) )
	{
		iStart++;
	}
	// skip over trailing whitespace
	while( iEnd>iStart && iswspace(szMsgType[iEnd]) )
	{
		iEnd--;
	}

	// Copy the middle as upper case
	int i=iStart;
	int j=0;
	while ( i<=iEnd )
	{
		wsz[j] = towupper( szMsgType[i] );
		i++;j++;
	}
	// null-terminate
	wsz[j] = 0;

	return wsz;
}

TCHAR 
CEMSTextRetriever::GetIPConnType( const int ciType )
{
	TCHAR tcRet = TEXT(' ');

	switch( ciType )
	{
		case CONN_TYPE_ETHERNET:
			tcRet = TEXT('E');
			break;
		case CONN_TYPE_DIALUP:
			tcRet = TEXT('M');
			break;
		case CONN_TYPE_DIALUP_STORM:
			tcRet = TEXT('S');
			break;
		case CONN_TYPE_PDT:
			tcRet = TEXT('P');
			break;
	}

	return tcRet;
}

TCHAR 
CEMSTextRetriever::GetIPState( const bool cbActive )
{
	TCHAR tcRet = TEXT(' ');

	if( cbActive )
		tcRet = TEXT('A');
	else
		tcRet = TEXT('I');

	return tcRet;
}