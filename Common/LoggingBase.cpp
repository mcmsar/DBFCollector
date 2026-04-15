
#include "loggingbase.h"

#include <tchar.h>
#include <stdio.h>
#include "convutility.h"

#include <string>
using std::string;
using std::wstring;

CEMSLoggingBase::CEMSLoggingBase( const unsigned short cusCategory, const unsigned long ulLutID ) 
						: m_usMsgCategory( cusCategory ),
						  m_ulThisLutID(ulLutID),
						  m_bInitialized(false)
{
}

CEMSLoggingBase::~CEMSLoggingBase()
{
	Reset();
}

void
CEMSLoggingBase::Reset()
{
	if ( m_bInitialized )
	{
		CEMSLogHelper::Reset();
	}
	m_bInitialized = false;
}
void
CEMSLoggingBase::_InitLogger()
{
	if ( !m_bInitialized )
	{
		CEMSLogHelper::Init( m_ulThisLutID, m_usMsgCategory );
		m_bInitialized = true;
	}
	return;
}
void 
CEMSLoggingBase::LogAlarmMsg( const DWORD cdwMsg, EMS_RESULT hrParam )
{
	wchar_t	wszString[32];
	swprintf( wszString, L"0x%x", hrParam );
	LogAlarmMsg( cdwMsg, wszString ); 
}

void 
CEMSLoggingBase::LogInfoMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{	
	wstring	wstr = CEMSConversionUtil::ConvertToString( szSingleParam );
	LogInfoMsg( cdwMsg, wstr.c_str() );
}

void 
CEMSLoggingBase::LogAlarmMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{	
	wstring	wstr = CEMSConversionUtil::ConvertToString( szSingleParam );
	LogAlarmMsg( cdwMsg, wstr.c_str() );
}
void 
CEMSLoggingBase::LogWarningMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{	
	wstring	wstr = CEMSConversionUtil::ConvertToString( szSingleParam );
	LogWarningMsg( cdwMsg, wstr.c_str() );
}
void 
CEMSLoggingBase::LogTraceMsg( const DWORD cdwMsg, LPCSTR szSingleParam )
{	
 	wstring	wstr = CEMSConversionUtil::ConvertToString( szSingleParam );
	LogTraceMsg( cdwMsg, wstr.c_str() );
}
