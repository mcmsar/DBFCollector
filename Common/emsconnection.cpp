/****************************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
****************************************************************************/

/****************************************************************************

  Revision Record

	$Log:
	$
****************************************************************************/
#pragma warning(disable:4786)
#include "emsconnection.h"
#include "emsexcpt.h"
#include "dalmsgs.h"
#include "convutility.h"
#include "emsadohelper.h"

CEMSConnection::CEMSConnection()
{
}

CEMSConnection::CEMSConnection( const wchar_t* cwszCon )
{
	Open( cwszCon );
}

CEMSConnection::CEMSConnection( const CEMSConnection& x ) : m_spConn( x.m_spConn )
{
}

CEMSConnection::~CEMSConnection()
{
	if( NULL != m_spConn )
	{
		try
		{
			m_spConn->Close();
		}
		catch( _com_error& e )
		{
			_HandleException( e, m_spConn );
		}
		catch( ... )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
		}
	}
}

void 
CEMSConnection::Open( const wchar_t* cwszConString )
{
	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spConn->Open( _bstr_t( cwszConString ), _bstr_t(L""), 
					_bstr_t(L""), adConnectUnspecified );

	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSConnection::Close()
{
	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spConn->Close();

	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSConnection::BeginTrans()
{
	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spConn->BeginTrans();
	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSConnection::CommitTrans()
{
	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spConn->CommitTrans();
	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSConnection::RollbackTrans()
{
	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spConn->RollbackTrans();
	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

std::wstring 
CEMSConnection::GetProvider()
{
	std::wstring owszRet;

	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		owszRet = spConn->Provider;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return owszRet;
}

ULONG 
CEMSConnection::Execute( const wchar_t* cwszCmd )
{
	ULONG ulRet = 0;

	_ConnectionPtr spConn = _GetConPtr();

	if( 0 == spConn )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue;

		spConn->Execute( _bstr_t( cwszCmd ), &vValue, (adCmdText & adExecuteNoRecords) );

		vValue.ChangeType( VT_UI4 );
		ulRet = vValue.ulVal;

	}
	catch( _com_error& e )
	{
		_HandleException( e, spConn );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return ulRet;
}

IDispatch* 
CEMSConnection::Get()
{
	IDispatch* pRet = NULL;

	m_spConn.QueryInterface( IID_IDispatch, (void**) &pRet );
	
	return pRet;
}

_ConnectionPtr	
CEMSConnection::_GetConPtr()
{
	_ConnectionPtr spConn = 0;

	if( m_spConn == 0 )
	{
		EMS_RESULT hr = m_spConn.CreateInstance( __uuidof(Connection) );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}

	spConn = m_spConn;

	return spConn;
}

void			
CEMSConnection::_HandleException( const _com_error& croExcpt, const _ConnectionPtr& crspConn )
{
	std::wstring wszErrMsg;
	wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( croExcpt.Error() ) );
	
	if( croExcpt.Description().length() > 0 )
	{
		wszErrMsg.append( L" - " );
		wszErrMsg.append( croExcpt.Description() );
	}

	if( 0 != crspConn )
	{
		ErrorsPtr spErrors = crspConn->GetErrors();

		long lErrors = spErrors->GetCount();

		
		for( long l = 0; l < lErrors; l++ )
		{
			if( 0 == l )
			{
				wszErrMsg.append(L"  (Error trace:  ");
			}
			else
			{
				wszErrMsg.append(L", ");
			}

			ErrorPtr spError = spErrors->GetItem( l );

			wszErrMsg.append( spError->GetDescription() );
		}

		if( 0 != lErrors )
			wszErrMsg.append( L")" );
	}

	
	CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
	logParam += wszErrMsg.c_str();
#else
	logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif

	CEMSException oExcept( EMS_DAL_ADO_ERROR, logParam );

	if( _IsWarning( croExcpt.Error() ) )
	{
		oExcept.SetLogAsWarning();
	}
	else if( _FilterAlarm( croExcpt.Error() ) )
	{
		// Don't log as an alarm, but do log an info message.
		oExcept.SetAlarmLogged();		
	}

	throw oExcept;

}

bool			
CEMSConnection::_FilterAlarm( const HRESULT chrErrorCode )
{
	bool bRet = false;

	CEMSADOHelper adoHelper;

	bRet = adoHelper.FilterAlarm( chrErrorCode );

	return bRet;
}

bool			
CEMSConnection::_IsWarning( const HRESULT chrErrorCode )
{
	bool bRet = false;

	CEMSADOHelper adoHelper;

	bRet = adoHelper.IsWarning( chrErrorCode );

	return bRet;
}
