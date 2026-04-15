/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol size.

#include "emsdbcommand.h"

#include "emsexcpt.h"
#include "dalmsgs.h"
#include "convutility.h"

CEMSDBCommand::CEMSDBCommand()
{
}

CEMSDBCommand::CEMSDBCommand( const CEMSDBCommand& x )
{
	// Don't copy pointer.
}

CEMSDBCommand::~CEMSDBCommand()
{
}

void
CEMSDBCommand::Execute( const bool cbAsync )
{
	_CommandPtr spCmd = _GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		long lOptions = adCmdText | adExecuteNoRecords;

		if( cbAsync )
			lOptions = lOptions | adAsyncExecute;

		spCmd->Execute( 0, 0, lOptions );
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}


}

void 
CEMSDBCommand::SetConnection( const wchar_t* cwszCon )
{
	if( !cwszCon )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	_CommandPtr spCmd = _GetCommandPtr();

	BSTR bszCon = 0;

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		bszCon = SysAllocString( cwszCon );
		
		if( !bszCon )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		VARIANT vCon;
		VariantInit( &vCon );
		vCon.vt = VT_BSTR;
		vCon.bstrVal = bszCon;

		EMS_RESULT hr = spCmd->put_ActiveConnection( vCon );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( bszCon )
		{
			SysFreeString( bszCon );
			bszCon = 0;
		}
	}
	catch( CEMSException& e )
	{
		if( bszCon )
		{
			SysFreeString( bszCon );
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( bszCon )
		{
			SysFreeString( bszCon );
		}

		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		if( bszCon )
		{
			SysFreeString( bszCon );
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void
CEMSDBCommand::SetCommandString( const wchar_t* cwszCmdString )
{
	if( cwszCmdString )
	{
		_CommandPtr spCmd = _GetCommandPtr();

		if( 0 == spCmd )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		try
		{
			spCmd->CommandText = cwszCmdString;
		}
		catch( CEMSException& e )
		{
			throw e;
		}
		catch( _com_error& e )
		{
			std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

		}
		catch( ... )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
		}
	}
}

EMSDBOBJECTSTATE
CEMSDBCommand::GetState()
{
	EMSDBOBJECTSTATE eRet = DBOBJ_STATE_UNKNOWN;

	_CommandPtr spCmd = _GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		ObjectStateEnum eAdoState = (ObjectStateEnum) spCmd->State;

		eRet = m_adoHelper.GetEMSObjectState( eAdoState );

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return eRet;
}

void
CEMSDBCommand::Cancel()
{
	_CommandPtr spCmd = _GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spCmd->Cancel();

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::BindParameter( const wchar_t* cwszName, const EMSDBFLDTYPE ceDataType, 
					const EMSDBCMDDIRECTIONTYPE ceParamType )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	BSTR bszName = 0;

	try
	{
		DataTypeEnum eDataType = m_adoHelper.GetADODataType( ceDataType );

		ParameterDirectionEnum eDirType = m_adoHelper.GetADODirectionType( ceParamType );

		bszName = SysAllocString( cwszName );

		if( !bszName )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		_ParameterPtr spParam = spCmd->CreateParameter( bszName, eDataType, eDirType, -1 );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spCmd->Parameters->Append( spParam );

		if( bszName )
		{
			SysFreeString( bszName );
			bszName = 0;
		}

	}
	catch( CEMSException& e )
	{
		if( bszName )
		{
			SysFreeString( bszName );
			bszName = 0;
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( bszName )
		{
			SysFreeString( bszName );
			bszName = 0;
		}

		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		if( bszName )
		{
			SysFreeString( bszName );
			bszName = 0;
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const short csValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = csValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
	
}


void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const unsigned short cusValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_variant_t vValue;
		vValue.vt = VT_UI2;
		vValue.uiVal = cusValue;

		spParam->Value = vValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const long clValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = clValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const unsigned long culValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_variant_t vValue;
		vValue.vt = VT_UI4;
		vValue.ulVal = culValue;

		spParam->Value = vValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const __int64 ci64Value )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_variant_t vValue;
		vValue.vt = VT_I8;
		vValue.llVal = ci64Value;

		spParam->Value = vValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const unsigned __int64 cui64Value )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_variant_t vValue;
		vValue.vt = VT_UI8;
		vValue.ullVal = cui64Value;

		spParam->Value = vValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const wchar_t* cwszValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	BSTR bszValue = 0;

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		bszValue = SysAllocString( cwszValue );

		if( !bszValue )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
		
		spParam->Value = bszValue;

		if( bszValue )
		{
			SysFreeString( bszValue );
			bszValue = 0;
		}
	}
	catch( CEMSException& e )
	{
		if( bszValue )
		{
			SysFreeString( bszValue );
			bszValue = 0;
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( bszValue )
		{
			SysFreeString( bszValue );
			bszValue = 0;
		}

		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		if( bszValue )
		{
			SysFreeString( bszValue );
			bszValue = 0;
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const char* cszValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = cszValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const unsigned long culBytes, 
						const unsigned char* cabyValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_variant_t vValue;
		m_adoHelper.ConvertToSafeArray( culBytes, cabyValue, vValue );

		spParam->Value = vValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const float cfValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = cfValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const double cdValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = cdValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSDBCommand::SetParameterValue( const wchar_t* cwszName, const unsigned char cbyValue )
{
	_CommandPtr spCmd =	_GetCommandPtr();

	if( 0 == spCmd )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_ParameterPtr spParam = spCmd->Parameters->GetItem( cwszName );

		if( 0 == spParam )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		spParam->Value = cbyValue;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}


_CommandPtr
CEMSDBCommand::_GetCommandPtr()
{
	_CommandPtr spCmd = 0;

	if( 0 == m_spCmd )
	{
		EMS_RESULT hr = m_spCmd.CreateInstance( __uuidof(Command) );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}

	spCmd = m_spCmd;

	return m_spCmd;

}
