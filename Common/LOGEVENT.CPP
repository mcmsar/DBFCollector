/********************************************************************
*	Module:			LogEvent.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*********************************************************************
* Copyright (c) 2001-2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/30		rvw		start
		2005/01/05		ch		Ticket 6652: 
								- Added Report() and wide string usage

********************************************************************/
#include <windows.h>
#include <stdio.h>
#include "logevent.h"

const wchar_t c_wszLeoLoggerName[] = L"EMSLeoLut600";

CEMSLogEvent::CEMSLogEvent( LPCWSTR wszLoggerName ) 
{
	LPCWSTR	wsz = wszLoggerName ? wszLoggerName : c_wszLeoLoggerName;
	wcsncpy( m_wszLoggerName, wsz, MAX_LOGGERNAME_LEN-1 );
	m_wszLoggerName[MAX_LOGGERNAME_LEN-1] = 0; // ensure there is a null terminator
}

CEMSLogEvent::~CEMSLogEvent() 
{
}

// *** The following method is deprecated ***
// Use the wide string version (below) instead
// Note that this function is unchanged except for its use of GetEventType()
EMS_RESULT CEMSLogEvent::ReportEvent( EMSLOGMSGTYPE msgType, DWORD dwEvent, 
		WORD wCategory, WORD wNumStrings, LPCSTR *lpszStrings )
{
	EMS_RESULT hr = EMS_OK;
	WORD	wEventType = 0;
	PSID lpSID = 0;
	HANDLE hEventLog = RegisterEventSourceW( 0, m_wszLoggerName );

	if ( hEventLog != INVALID_HANDLE_VALUE )
	{
		wEventType = GetEventType( msgType );

		if ( ::ReportEvent( hEventLog, wEventType, wCategory, dwEvent, lpSID,
				wNumStrings, 0, lpszStrings, 0 ) )
		{
			hr = EMS_OK;
		}

		DeregisterEventSource( hEventLog );
	}

	return hr;
}
// *** END OF DEPRECATED FUNCTION ***

EMS_RESULT 
CEMSLogEvent::ReportEventW(EMSLOGMSGTYPE	msgType, 
						   DWORD			dwEvent, 
						   WORD				wCategory, 
						   WORD				wNumParams, 
						   LPCWSTR*			awszParams )
{
	EMS_RESULT	hr = EMS_OK;
	WORD		wEventType = 0;
	PSID		lpSID = 0;
	HANDLE		hEventLog = RegisterEventSourceW( 0, m_wszLoggerName );

	if ( hEventLog != INVALID_HANDLE_VALUE )
	{
		wEventType = GetEventType( msgType );

		if ( !::ReportEventW( hEventLog, wEventType, wCategory, dwEvent, lpSID,
				wNumParams, 0, awszParams, 0 ) )
		{
			// Failed to update the event log.
			// Most likely this is because the supplied event identifier is an HRESULT
			// that does not have an associated message.
			//
			// Try again with a generic message .. 
			wchar_t	wszBuffer[1024];
			swprintf( wszBuffer, L"[0x%x]: ", dwEvent );
			LPCWSTR	awszEventParams[] = { wszBuffer };

			// ... include any supplied parameters
			wchar_t	wszTemp[256];
			memset( wszTemp, 0, 256*sizeof(wchar_t) );
			int iLeft = 1024 - wcslen(wszBuffer) - 1;
			for ( int i = 0; i < wNumParams && iLeft > 0; i++ )
			{	
				wszTemp[0] = '(';
				wcsncat( wszTemp, awszParams[i], 256-3 ); // null terminator + braces
				wcscat( wszTemp, L")" );

				wcsncat( wszBuffer, wszTemp, iLeft );
				iLeft -= wcslen( wszTemp );
			}


			if ( ::ReportEventW( hEventLog, wEventType, wCategory, EMS_LOG_HR, lpSID,
				1, 0, awszEventParams, 0 ))
			{
				hr = EMS_OK;
			}
		}

		DeregisterEventSource( hEventLog );
	}

	return hr;
}

WORD
CEMSLogEvent::GetEventType( EMSLOGMSGTYPE msgType )
{
	WORD	wEventType;
	
	switch ( msgType )
	{
		case EMSLogMsgAlarm:
		case EMSLogMsgFatal:
			wEventType = EVENTLOG_ERROR_TYPE;
			break;

		case EMSLogMsgWarn:
			wEventType = EVENTLOG_WARNING_TYPE;
			break;

		default:
		case EMSLogMsgInfo:
			wEventType = EVENTLOG_INFORMATION_TYPE;
			break;
	}
	return wEventType;
}

