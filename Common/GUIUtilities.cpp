/*********************************************************************
*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#include "guiutilities.h"
#include <crtdbg.h>
#include "messages.h"
#include "convutility.h"

const wchar_t* cwszMessageTerminator = L"\r\n";

CEMSGUIUtilities::CEMSGUIUtilities( const EMS_RESULT cMsgIDDefault, const EMS_RESULT cMsgIDDialogTitle ) : 
																	m_MsgIDDefault(cMsgIDDefault),
																	m_MsgIDDialogTitle( cMsgIDDialogTitle )
{
}

CEMSGUIUtilities::CEMSGUIUtilities( const CEMSGUIUtilities& x ) : m_MsgIDDefault( x.m_MsgIDDefault ),
																m_MsgIDDialogTitle( x.m_MsgIDDialogTitle )
{
}

CEMSGUIUtilities::~CEMSGUIUtilities()
{
}

void
CEMSGUIUtilities::HandleException( CEMSException& e )
{
	HandleError( e.GetErrCode(), &(e.GetParam()) );
}

void
CEMSGUIUtilities::HandleException( )
{
	std::wstring wszMsg ;

	// See if there's a system error code.
	DWORD dwLastError = GetLastError();
	if( ERROR_SUCCESS != dwLastError )
	{
		wszMsg = m_oMsgTable.GetMessage( dwLastError );
	}

	if( wszMsg.empty() )
	{
		wszMsg = m_oMsgTable.GetMessage( EMS_GENERAL_UNKNOWN );
	}

	_DisplayErrorMessage( wszMsg.c_str() );
}

void
CEMSGUIUtilities::HandleError( HRESULT hr, CEMSLogMsgParam* pParam )
{
	std::wstring wszMsg;
	if ( pParam )
		wszMsg = m_oMsgTable.GetMessage( hr, *pParam );
	else
		wszMsg = m_oMsgTable.GetMessage( hr );

	if( wszMsg.empty() )
	{
		CEMSLogMsgParam oLogParam;

		oLogParam.AddString( CEMSConversionUtil::ConvertToString( hr, 16 ).c_str() );

		wszMsg = m_oMsgTable.GetMessage( m_MsgIDDefault, oLogParam );
	}

	_ASSERTE( !wszMsg.empty() );

	if( wszMsg.empty() )
	{
		wszMsg = L"Unknown error occurred.";
	}

	_DisplayErrorMessage( wszMsg.c_str() );
	
}

std::wstring 
CEMSGUIUtilities::GetMessageText( const EMS_RESULT cMsgID )
{
	return m_oMsgTable.GetMessage( cMsgID );
}

std::wstring 
CEMSGUIUtilities::GetDialogBoxTitle()
{
	std::wstring wszTitle = m_oMsgTable.GetMessage( m_MsgIDDialogTitle );

	if( !wszTitle.empty() )
	{
		// Message Table always appends a CRLF.  Remove it for the title bar.
		std::wstring wszSubStr = wszTitle.substr( 0, wszTitle.find( cwszMessageTerminator ) );

		if( !wszSubStr.empty() )
		{
			wszTitle = wszSubStr;
		}
	}

	return wszTitle;
}

std::wstring 
CEMSGUIUtilities::GetDisplayMessageText( const EMS_RESULT cMsgID )
{
	std::wstring wszTitle = m_oMsgTable.GetMessage( cMsgID );

	if( !wszTitle.empty() )
	{
		// Message Table always appends a CRLF.  Remove it for the title bar.
		std::wstring wszSubStr = wszTitle.substr( 0, wszTitle.find( cwszMessageTerminator ) );

		if( !wszSubStr.empty() )
		{
			wszTitle = wszSubStr;
		}
	}

	return wszTitle;
}

void
CEMSGUIUtilities::_DisplayErrorMessage( const wchar_t* cwszErrorMsg )
{
	if( cwszErrorMsg )
	{
		MessageBoxW( 0, cwszErrorMsg, GetDialogBoxTitle().c_str(), MB_OK | MB_ICONERROR );
	}
}