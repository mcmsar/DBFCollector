/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "splerrorhandler.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "generalmsgs.h"
#include "LogHelper.h"

#ifdef EMS_USE_INTEL_SPL

static NSPStatus __stdcall
OnError( NSPStatus status, const char* cszFunction, const char* cszContext,
								const char* cszFile, int iLine )
{
	// Currently, the only kind of handling is either throw an exception or do nothing.
	switch( status )
	{
		case NSP_StsBackTrace:
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( CEMSSPLErrorHandler::GetInstance()->GetStatusText( status ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszFunction ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszContext ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszFile ).c_str() );
				oParam.Add( iLine );
				CEMSException oExcpt( EMS_NSP_ERROR, oParam );

#ifdef APACHE_LOGGER
				CEMSLogClient oLogClient(L"SPL");
				oLogClient.LogException( oExcpt );
#endif
			}
			break;
		case NSP_StsOk:
			break;
		default:
			if( CEMSSPLErrorHandler::GetInstance()->GetThrowException() )
			{
				CEMSLogMsgParam oParam;

				oParam.AddString( CEMSSPLErrorHandler::GetInstance()->GetStatusText( status ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszFunction ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszContext ).c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszFile ).c_str() );
				oParam.Add( iLine );

				throw CEMSException( EMS_NSP_ERROR, oParam );
			}
			break;
	}

	nspSetErrStatus( status );

	return status;
}

#endif

CEMSSPLErrorHandler* CEMSSPLErrorHandler::ms_pHandler = NULL;
CEMSCriticalSection	CEMSSPLErrorHandler::m_ocsInstance;

CEMSSPLErrorHandler::CEMSSPLErrorHandler() : m_bThrowException( true )
{
}

CEMSSPLErrorHandler::~CEMSSPLErrorHandler()
{
	Deactivate();
}

CEMSSPLErrorHandler* 
CEMSSPLErrorHandler::GetInstance()
{
	CEMSSPLErrorHandler* pRet = NULL;

	try
	{
		m_ocsInstance.Enter();

		if( !ms_pHandler )
		{
			ms_pHandler = new CEMSSPLErrorHandler;

			if( !ms_pHandler )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}

		if( !ms_pHandler )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pRet = ms_pHandler;

		m_ocsInstance.Leave();
	}
	catch( ...  )
	{
		m_ocsInstance.Leave();
	}

	return pRet;
}

void 
CEMSSPLErrorHandler::Activate()
{
	try
	{
#ifdef EMS_USE_INTEL_SPL
		nspSetErrMode( NSP_ErrModeParent );
		nspRedirectError( OnError );
#endif
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSSPLErrorHandler::Deactivate()
{
	try
	{
#ifdef EMS_USE_INTEL_SPL
		nspRedirectError( NULL );
#endif
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSSPLErrorHandler::Shutdown()
{
	CEMSSPLErrorHandler::GetInstance()->Deactivate();

	try
	{
		m_ocsInstance.Enter();

		if( ms_pHandler )
		{
			delete ms_pHandler;
			ms_pHandler = NULL;
		}

		m_ocsInstance.Leave();
	}
	catch( ... )
	{
		m_ocsInstance.Leave();
	}
}

std::wstring 
CEMSSPLErrorHandler::GetStatusText( const EMSSIGPROCSTATUS cstatValue )
{
	std::wstring owszRet;

#ifdef EMS_USE_INTEL_SPL
	switch( cstatValue )
	{
		case NSP_StsOk:
			owszRet = L"Ok";
			break;
		case NSP_StsBackTrace:
			owszRet = L"Back trace";
			break;
		case NSP_StsError:
			owszRet = L"Unknown/Unspecified";
			break;
		case NSP_StsInternal:
			owszRet = L"Internal error (bad state)";
			break;
		case NSP_StsNoMem:
			owszRet = L"Out of memory";
			break;
		case NSP_StsBadArg:
			owszRet = L"Bad function argument/parameter";
			break;
		case NSP_StsBadFunc:
			owszRet = L"Unsupported function";
			break;
		case NSP_StsNoConv:
			owszRet = L"Iteration didn't converge";
			break;
		case NSP_StsAutoTrace:
			owszRet = L"Tracer";
			break;
	}
#elif EMS_USE_INTEL_PP
	switch( cstatValue )
	{
		case 0: // dummy case.
		default:
			owszRet = L"unknown";
	}

#else
	#pragma message("*** must specify one of EMS_USE_INTEL_SPL or EMS_USE_INTEL_PP ****")
#endif

	return owszRet;
}