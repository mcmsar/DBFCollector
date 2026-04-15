/********************************************************************
*	Module:			LogHelper.cpp
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
* Copyright (c) 2003-2005 by EMS Technologies, Inc.,
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

	0.0	2003Oct31		CH		Start

********************************************************************/
#pragma warning(disable:4786)	// Disable warning messages for stl debug symbol size.

#include <windows.h>
#include <assert.h>

#include <string>
using std::string;

#include "emsexcpt.h" 			// CEMSException
#include "criticalsection.h"	// CEMSCriticalSection
#include "convutility.h"
#include "processconfigconstants.h"
#include "ccbootstrap.h"

#define INITGUID
#include <initguid.h>
#include "emsloggr.h"			// IEMSLeo600LoggerEx
#include "iconfigmanager.h"		// IID_IEMSConfigurationManager
#include "ConfigManagerProxyClsid.h"

#include "LogHelper.h"

CEMSLogHelper*		CEMSLogHelper::ms_pLogger = NULL;
CEMSCriticalSection	CEMSLogHelper::ms_csLoggerCreation;

CEMSLogHelper::~CEMSLogHelper()
{
	if ( m_pLogger )
	{
		m_pLogger->Release();
		m_pLogger = NULL;
	}
}

void
CEMSLogHelper::Reset()
{
	if ( ms_pLogger )
	{
		ms_csLoggerCreation.Enter();
		try
		{
			if ( ms_pLogger )
			{
				ULONG	ulCount = ms_pLogger->Release();
				if ( ulCount == 0 )
				{
					ms_pLogger = NULL;
				}
			}
			ms_csLoggerCreation.Leave();
		}
		catch( ... )
		{
			ms_csLoggerCreation.Leave();
			throw;
		}
	}
	return;
}

void 
CEMSLogHelper::Init( const unsigned long culLutID, const WORD cwProcessID )
{
	bool	bAddRef = true;
	if ( !ms_pLogger )
	{
		CEMSLogHelper* pLogger = NULL;

		ms_csLoggerCreation.Enter();

		try
		{
			if( !ms_pLogger )
			{
				pLogger = new CEMSLogHelper;

				if( !pLogger )
				{
					THROW_NOMEMORY_EXCEPTION();
				}
				pLogger->_Init( culLutID, cwProcessID );
				ms_pLogger = pLogger;
				bAddRef = false;
	
			}
		}
		catch( ... )
		{
			delete pLogger;
			ms_csLoggerCreation.Leave();
			throw;
		}

		ms_csLoggerCreation.Leave();
	}
	// Didn't create ... so call AddRef()
	if ( bAddRef )
	{
		ms_pLogger->AddRef();
	}

	return;
}

// This function may ONLY be called from within the critical section
void
CEMSLogHelper::_Init( const unsigned long culLutID, const WORD cwProcessID ) 
{
	assert( !m_pLogger );

	// Ask the configuration manager for the lut id (unless being called from within the config manager!)
	unsigned long	ulLutID = ( EMSLOGCAT_CM != cwProcessID ) ? _GetLutID( culLutID ) : culLutID;

	EMS_RESULT		hr = EMS_OK;
	hr = CoCreateInstance(	CLSID_EMSLeo600Logger, 0, CLSCTX_ALL, IID_IEMS600LoggerEx,
							(LPVOID*)&m_pLogger );

	if ( SUCCEEDED(hr) && m_pLogger )
	{
		try
		{
			hr = m_pLogger->Init( ulLutID, cwProcessID );
		}
		catch( ... )
		{
			if ( m_pLogger )
			{
				m_pLogger->Release();
				m_pLogger = NULL;
			}
			throw;
		}
	}
	
	if( FAILED(hr) )
	{
		if ( m_pLogger )
		{
			m_pLogger->Release(); 
			m_pLogger = NULL;
		}
		THROW_RUNTIME_EXCEPTION( hr );
	}
	return;
}

unsigned long
CEMSLogHelper::_GetLutID( const unsigned long culLutID )
{
	unsigned long ulLutID = culLutID;
	if( 0 == ulLutID )
	{
		IEMSConfigurationManager* pCM = 0;

		EMS_RESULT hr = EMS_OK;

		if( CCBootstrap::IsMEOSystem() )
		{
			hr = CoCreateInstance( CLSID_EMSConfigProxy, 0, CLSCTX_ALL, 
											IID_IEMSConfigurationManager, (void**) &pCM);
		}
		else
		{
			hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL, 
											IID_IEMSConfigurationManager, (void**) &pCM);
		}

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		try
		{
			EMSVARITYPE varThisLutID;

			EMS_RESULT hr = pCM->Get( cwszProcessGroup, c_pwcsNoGroupID, cwszLutID, &varThisLutID );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			ulLutID = varThisLutID.uiVal;

			pCM->Release();
			pCM = 0;

		}
		catch( ... )
		{
			if( pCM )
			{
				pCM->Release();
				pCM = 0;
			}

			throw;
		}
	}

	return ulLutID;
}


void					
CEMSLogHelper::LogException( CEMSException& ex, const bool cbAsAlarm )
{
	if( !ex.LogDisabled() )
	{
		if( !ex.HasBeenAlarmed() && cbAsAlarm )	// If an alarm has been logged, don't log any further 
		{										// alarm messages related to the exception.
			if( ex.IsWarning() )
			{
				LogWarningMsg( ex.GetErrCode(), ex.GetParam() );
			}
			else
			{
				LogAlarmMsg( ex.GetErrCode(), ex.GetParam() );
			}

			// Set the flag indicating that the exception has resulted in an alarm being logged.
			ex.SetAlarmLogged();	
		}
		else
		{
			LogInfoMsg( ex.GetErrCode(), ex.GetParam() );
		}

		// Now log a trace statement indicating where this happened.
		CEMSLogMsgParam param(5);
		param.AddX( ex.GetErrCode() );
		param.AddX( ex.GetSubErrCode() );
		param.Add( ex.GetFileName() );
		param.Add( ex.GetLineNumber() );
		param.Add( ex.GetComment() ); 
		LogInfoMsg( EMS_EXCEPTION_TRACE, param );
	}
}


void 
CEMSLogHelper::_LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	if ( m_pLogger )
	{
		m_pLogger->Report( ceType, cdwMsg, param.GetCount(), param.GetParams() );
	}
}

void 
CEMSLogHelper::_LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCWSTR cwszSingleParam )
{
	if ( m_pLogger )
	{
		if ( cwszSingleParam )
		{
			m_pLogger->Report( ceType, cdwMsg, 1, &cwszSingleParam );
		}
		else
		{
			m_pLogger->Report( ceType, cdwMsg, 0, NULL );
		}
	}
}

void 
CEMSLogHelper::LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, CEMSLogMsgParam& param )
{
	if ( ms_pLogger ) ms_pLogger->_LogMsg( ceType, cdwMsg, param );
	_LogDebugTrace( ceType, cdwMsg, param );
}
void 
CEMSLogHelper::LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	if ( ms_pLogger ) ms_pLogger->_LogMsg( ceType, cdwMsg, wszSingleParam );
	_LogDebugTrace( ceType, cdwMsg, wszSingleParam );
}
#ifdef _DEBUG
void 
CEMSLogHelper::_LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, CEMSLogMsgParam& param )
{
	// only log a trace if not going to the logger
	if ( ms_pLogger ) return;

	wchar_t			wszBuff[1024];
	const wchar_t**	awszParam = param.GetParams();

	const wchar_t*	wszType = NULL;
	switch( ceType )
	{
	case EMSLogMsgAlarm:	wszType = L"Alarm"; break;
	case EMSLogMsgWarn:		wszType = L"Warn"; break;
	case EMSLogMsgTrace:	wszType = L"Trace"; break;
	case EMSLogMsgInfo:		wszType = L"Info"; break;
	case EMSLogMsgDebug:	wszType = L"Debug"; break;
	case EMSLogMsgStatus:	wszType = L"Status"; break;
	case EMSLogMsgFatal:	wszType = L"Fatal"; break;
	case EMSLogMsgStartup:	wszType = L"Startup"; break;
	default:				wszType = L"Unknown";
	}

	// leave enough room for carriage return & null terminator
	const int		iMaxChars = 1022;
	
	memset( wszBuff, 0, 1024*sizeof(wchar_t) );
	swprintf( wszBuff, L"Log %s: 0x%x with params ", wszType, cdwMsg );

	int iLen = wcslen( wszBuff );
	int iLeft = iMaxChars - iLen;

	for ( int i=0;i<param.GetCount() && iLeft>2; i++ )
	{
		wszBuff[iLen++]  = '(';		iLeft--;
		wszBuff[iLen++]  = 0;		iLeft--;
		wcsncat( wszBuff, awszParam[i], iLeft );
		iLen = wcslen( wszBuff );
		iLeft = iMaxChars - iLen;
		if ( iLeft > 0 )
		{
			wszBuff[iLen++]  = ')';	iLeft--;
		}
	}
	// End with carriage return
	int iPos = wcslen( wszBuff );
	wszBuff[iPos++] = '\n';
	wszBuff[iPos] = 0;

	OutputDebugStringW( wszBuff );
}

void
CEMSLogHelper::_LogDebugTrace( const EMSLOGMSGTYPE ceType, DWORD cdwMsg, LPCWSTR wszSingleParam )
{
	// only log a trace if not going to the logger
	if ( ms_pLogger ) return;

	const wchar_t*	wszType = NULL;
	switch( ceType )
	{
	case EMSLogMsgAlarm:	wszType = L"Alarm"; break;
	case EMSLogMsgWarn:		wszType = L"Warn"; break;
	case EMSLogMsgTrace:	wszType = L"Trace"; break;
	case EMSLogMsgInfo:		wszType = L"Info"; break;
	case EMSLogMsgDebug:	wszType = L"Debug"; break;
	case EMSLogMsgStatus:	wszType = L"Status"; break;
	case EMSLogMsgFatal:	wszType = L"Fatal"; break;
	case EMSLogMsgStartup:	wszType = L"Startup"; break;
	default:				wszType = L"Unknown";
	}

	wchar_t			wszBuff[1024];
	memset( wszBuff, 0, 1024*sizeof(wchar_t) );
	// leave enough room for carriage return & null terminator
	const int		iMaxChars = 1022;

	if ( wszSingleParam )
	{
		swprintf( wszBuff, L"Log %s: 0x%x with param ", wszType, cdwMsg );
		wcsncat( wszBuff, wszSingleParam, iMaxChars-wcslen(wszBuff) );
	}
	else
	{
		swprintf( wszBuff, L"Log %s: 0x%x", wszType, cdwMsg );
	}
	// End with carriage return
	int iPos = wcslen( wszBuff );
	wszBuff[iPos++] = '\n';
	wszBuff[iPos] = 0;

	OutputDebugStringW( wszBuff );
}
#endif

void 
CEMSLogHelper::LogMsg( const EMSLOGMSGTYPE ceType, const DWORD cdwMsg, LPCSTR szSingleParam )
{
	if ( !ms_pLogger ) return;

	wstring	wstr;
	if ( szSingleParam )
	{
		wstr = CEMSConversionUtil::ConvertToString( szSingleParam );
	}
	ms_pLogger->_LogMsg( ceType, cdwMsg, wstr.c_str() );
	_LogDebugTrace( ceType, cdwMsg, wstr.c_str() );
}

void 
CEMSLogHelper::LogAlarmMsg( const DWORD cdwMsg, const EMS_RESULT cerrResult )
{
	CEMSLogMsgParam	param(1);
	param.AddX( cerrResult );
	LogAlarmMsg( cdwMsg, param );
}

