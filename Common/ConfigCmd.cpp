
#include "configcmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "emsauthorization.h"
#include "ecmdproc.h"
#include "convutility.h"
#include "emspipe.h"
#include "cmdsrc.h"
#include "leodefns.h"

CEMSConfigCmd::CEMSConfigCmd() : m_wszGroupType(0), m_wszGroupID(0), m_wszKeyName(0), m_wszStringValue(0),
								m_eType( CONFIGCMD_UNKNOWN )
{
	memset( &m_authInfo, 0, sizeof( EMSAUTHORIZATIONINFO ) );
}

CEMSConfigCmd::CEMSConfigCmd( const CEMSConfigCmd& x ) : m_wszGroupType(0), m_wszGroupID(0), m_wszKeyName(0), 
														m_wszStringValue(0), m_eType( CONFIGCMD_UNKNOWN )
{
	SetGroupType( x.m_wszGroupType );
	SetGroupID( x.m_wszGroupID );
	SetKeyName( x.m_wszKeyName );
	SetStringValue( x.m_wszStringValue );
	m_eType = x.m_eType;
	SetAuthorization( x.m_authInfo );
}

CEMSConfigCmd::~CEMSConfigCmd()
{
	if( m_wszGroupType )
	{
		delete[] m_wszGroupType;
		m_wszGroupType = 0;
	}

	if( m_wszGroupID )
	{
		delete[] m_wszGroupID;
		m_wszGroupID = 0;
	}

	if( m_wszKeyName )
	{
		delete[] m_wszKeyName;
		m_wszKeyName = 0;
	}

	if( m_wszStringValue )
	{
		delete[] m_wszStringValue;
		m_wszStringValue = 0;
	}
}

void 
CEMSConfigCmd::SetGroupType( const wchar_t* cwszVal )
{
	_SetString( m_wszGroupType, cwszVal );
}

wchar_t* 
CEMSConfigCmd::GetGroupType() const
{
	wchar_t* wszRet = 0;
	
	_SetString( wszRet, m_wszGroupType );

	return wszRet;
}

void 
CEMSConfigCmd::SetGroupID( const wchar_t* cwszVal )
{
	_SetString( m_wszGroupID, cwszVal );
}

wchar_t* 
CEMSConfigCmd::GetGroupID() const
{
	wchar_t* wszRet = 0;
	
	_SetString( wszRet, m_wszGroupID );

	return wszRet;
}

void 
CEMSConfigCmd::SetKeyName( const wchar_t* cwszVal )
{
	_SetString( m_wszKeyName, cwszVal );
}

wchar_t* 
CEMSConfigCmd::GetKeyName() const
{
	wchar_t* wszRet = 0;
	
	_SetString( wszRet, m_wszKeyName );

	return wszRet;
}

void 
CEMSConfigCmd::SetStringValue( const wchar_t* cwszVal )
{
	_SetString( m_wszStringValue, cwszVal );
}

wchar_t* 
CEMSConfigCmd::GetStringValue() const
{
	wchar_t* wszRet = 0;
	
	_SetString( wszRet, m_wszStringValue );

	return wszRet;
}

void 
CEMSConfigCmd::SetAuthorization( const EMSAUTHORIZATIONINFO& cauthInfo )
{
	memcpy( &m_authInfo, &cauthInfo, sizeof(EMSAUTHORIZATIONINFO) );
}

EMSAUTHORIZATIONINFO 
CEMSConfigCmd::GetAuthorization() const
{
	EMSAUTHORIZATIONINFO authInfo;

	memcpy( &authInfo, &m_authInfo, sizeof(EMSAUTHORIZATIONINFO) );

	return authInfo;
}

TCHAR* 
CEMSConfigCmd::Serialize( const EMSCONFIGCOMMAND ceCmdType )
{
	long lChars = EMS_PIPE_MAX_COMMAND_LENGTH / sizeof(TCHAR);
	TCHAR* szCmd = 0;

	m_eType = ceCmdType;

	try
	{
		szCmd = new TCHAR[lChars+1];
		
		if( !szCmd )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( szCmd, 0, (lChars+1)*sizeof(TCHAR) );

		switch( ceCmdType )
		{
			case CONFIGCMD_GET:
				{
					if( !m_wszGroupType || !m_wszGroupID || !m_wszKeyName )
					{
						THROW_NULL_POINTER_EXCEPTION();
					}

#if defined(UNICODE) || defined(_UNICODE)
					_sntprintf( szCmd, lChars, cszCMGetCmdFmt, 
										CEMSConversionUtil::ConvertToString( m_authInfo.szUserName ).c_str(), 
										m_authInfo.ulRoleID, m_wszGroupType, m_wszGroupID, m_wszKeyName );
#else
					_sntprintf( szCmd, lChars, cszCMGetCmdFmt, m_authInfo.szUserName, m_authInfo.ulRoleID, 
											CEMSConversionUtil::ConvertToString( m_wszGroupType ).c_str(), 
											CEMSConversionUtil::ConvertToString( m_wszGroupID ).c_str(), 
											CEMSConversionUtil::ConvertToString( m_wszKeyName ).c_str() );
#endif
				}
				break;
			case CONFIGCMD_SET_STRING:
				{
					if( !m_wszGroupType || !m_wszGroupID || !m_wszKeyName || !m_wszStringValue )
					{
						THROW_NULL_POINTER_EXCEPTION();
					}

#if defined(UNICODE) || defined(_UNICODE)
					_sntprintf( szCmd, lChars, cszCMSetStringCmdFmt, 
										CEMSConversionUtil::ConvertToString( m_authInfo.szUserName ).c_str(), 
										m_authInfo.ulRoleID, m_wszGroupType, m_wszGroupID, m_wszKeyName,
										m_wszStringValue );
#else
					_sntprintf( szCmd, lChars, cszCMSetStringCmdFmt, m_authInfo.szUserName, m_authInfo.ulRoleID, 
											CEMSConversionUtil::ConvertToString( m_wszGroupType ).c_str(), 
											CEMSConversionUtil::ConvertToString( m_wszGroupID ).c_str(), 
											CEMSConversionUtil::ConvertToString( m_wszKeyName ).c_str(),
											CEMSConversionUtil::ConvertToString( m_wszStringValue ).c_str() );
#endif
				}
				break;
			case CONFIGCMD_LOG_CONTENTS:
				_tcscpy( szCmd, cszCMLogContentsCmdFmt );
				break;
			default:
				THROW_RUNTIME_EXCEPTION( EMS_INVALID_CMD ); 
		}
	}
	catch( ... )
	{
		if( szCmd )
		{
			delete[] szCmd;
			szCmd = 0;
		}

		throw;
	}

	return szCmd;
}

void 
CEMSConfigCmd::Deserialize( CEMSCommandProcessor* pCmdProcessor )
{
	if( !pCmdProcessor )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	// Parse it
	pCmdProcessor->ParseCommand();
	pCmdProcessor->GetCmdLine();

	if( pCmdProcessor->IsCommand( TEXT("Get") ) )
	{
		m_eType = CONFIGCMD_GET;

		TCHAR szUser[EMS_MAX_USER_NAME+1];
		memset( szUser, 0, (EMS_MAX_USER_NAME+1)*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("user"), szUser, 
					sizeof( szUser ) / sizeof( szUser[ 0 ] ) );
		
		long lRoleID = pCmdProcessor->LongParam( TEXT("role") );

		EMSAUTHORIZATIONINFO authInfo;
		memset( &authInfo, 0, sizeof(EMSAUTHORIZATIONINFO) );

		authInfo.ulRoleID = lRoleID;

#if defined(UNICODE) || defined(_UNICODE)
		strncpy( (char*) authInfo.szUserName, CEMSConversionUtil::ConvertToString( szUser ).c_str(), EMS_MAX_USER_NAME - 1 );
#else
		strncpy( (char*) authInfo.szUserName, szUser, EMS_MAX_USER_NAME -1 );
#endif
		SetAuthorization( authInfo );

		TCHAR szGroupType[8];
		memset( szGroupType, 0, 8*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("grptype"), szGroupType, 
					sizeof( szGroupType ) / sizeof( szGroupType[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetGroupType( szGroupType );
#else
		SetGroupType( CEMSConversionUtil::ConvertToString( szGroupType ).c_str() );
#endif

		TCHAR szGroupID[128];
		memset( szGroupID, 0, 128*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("grpid"), szGroupID, 
					sizeof( szGroupID ) / sizeof( szGroupID[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetGroupID( szGroupID );
#else
		SetGroupID( CEMSConversionUtil::ConvertToString( szGroupID ).c_str() );
#endif

		TCHAR szKey[256];
		memset( szKey, 0, 256*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("key"), szKey, 
					sizeof( szKey ) / sizeof( szKey[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetKeyName( szKey );
#else
		SetKeyName( CEMSConversionUtil::ConvertToString( szKey ).c_str() );
#endif
	}
	else if( pCmdProcessor->IsCommand( TEXT("SetString") ) )
	{
		m_eType = CONFIGCMD_SET_STRING;

		TCHAR szUser[EMS_MAX_USER_NAME+1];
		memset( szUser, 0, (EMS_MAX_USER_NAME+1)*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("user"), szUser, 
					sizeof( szUser ) / sizeof( szUser[ 0 ] ) );
		
		long lRoleID = pCmdProcessor->LongParam( TEXT("role") );

		EMSAUTHORIZATIONINFO authInfo;
		memset( &authInfo, 0, sizeof(EMSAUTHORIZATIONINFO) );

		authInfo.ulRoleID = lRoleID;

#if defined(UNICODE) || defined(_UNICODE)
		strncpy( (char*) authInfo.szUserName, CEMSConversionUtil::ConvertToString( szUser ).c_str(), EMS_MAX_USER_NAME - 1 );
#else
		strncpy( (char*) authInfo.szUserName, szUser, EMS_MAX_USER_NAME -1 );
#endif
		SetAuthorization( authInfo );

		TCHAR szGroupType[8];
		memset( szGroupType, 0, 8*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("grptype"), szGroupType, 
					sizeof( szGroupType ) / sizeof( szGroupType[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetGroupType( szGroupType );
#else
		SetGroupType( CEMSConversionUtil::ConvertToString( szGroupType ).c_str() );
#endif

		TCHAR szGroupID[128];
		memset( szGroupID, 0, 128*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("grpid"), szGroupID, 
					sizeof( szGroupID ) / sizeof( szGroupID[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetGroupID( szGroupID );
#else
		SetGroupID( CEMSConversionUtil::ConvertToString( szGroupID ).c_str() );
#endif

		TCHAR szKey[256];
		memset( szKey, 0, 256*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("key"), szKey, 
					sizeof( szKey ) / sizeof( szKey[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetKeyName( szKey );
#else
		SetKeyName( CEMSConversionUtil::ConvertToString( szKey ).c_str() );
#endif

		TCHAR szValue[256];
		memset( szValue, 0, 256*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("value"), szValue, 
					sizeof( szValue ) / sizeof( szValue[ 0 ] ) );

#if defined(UNICODE) || defined(UNICODE)
		SetStringValue( szValue );
#else
		SetStringValue( CEMSConversionUtil::ConvertToString( szValue ).c_str() );
#endif

	}
	else if( pCmdProcessor->IsCommand( TEXT("LogContents") ) )
	{
		m_eType = CONFIGCMD_LOG_CONTENTS;
	}
}

void
CEMSConfigCmd::SendCommand( const EMSCONFIGCOMMAND ceCmdType )
{
	CEMSCommandSource* pCmdSrc = 0;
	LPEMSCOMMANDCHANNEL2 pCmdChannel = 0;
	TCHAR* szCmd = 0;

	try
	{
		EMS_RESULT hr = CoCreateInstance( CLSID_EMSDataPipeline, 0, CLSCTX_LOCAL_SERVER, 
					IID_IEMSCommandChannel2, (LPVOID*)&pCmdChannel );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		pCmdSrc = new CEMSCommandSource( 0, EMS_PIPE_MAX_COMMAND_LENGTH );
		
		if ( pCmdSrc )
			hr = pCmdChannel->RegisterSource( pCmdSrc );
		else
			THROW_NOMEMORY_EXCEPTION();

		szCmd = Serialize( ceCmdType );
		
		if( szCmd )
		{
			ULONG ulBytesSent = 0, ulLength = 0, ulFlags=0;
			BYTE cCmd[ EMS_PIPE_MAX_COMMAND_LENGTH + 1 ];

			ulLength = _tcslen( szCmd ) + 1;

			for ( int i = 0; i < (int)ulLength; i++)
				cCmd[i] = (BYTE)szCmd[i];

			hr = pCmdSrc->Write( LUT_CM_COMMANDS, cCmd, ulLength, &ulBytesSent );

			if( FAILED(hr) )
			{
//				THROW_RUNTIME_EXCEPTION( hr );
			}

			delete[] szCmd;
			szCmd = 0;
		}

		pCmdChannel->UnRegisterSource( pCmdSrc );
		pCmdChannel->Release();
		pCmdChannel = 0;

		pCmdSrc->Release();
		pCmdSrc = 0;


	}
	catch( ... )
	{
		if( pCmdChannel )
		{
			if( pCmdSrc )
				pCmdChannel->UnRegisterSource( pCmdSrc );
			
			pCmdChannel->Release();
			pCmdChannel = 0;
		}

		if( pCmdSrc )
		{
			pCmdSrc->Release();
			pCmdSrc = 0;
		}

		if( szCmd )
		{
			delete[] szCmd;
			szCmd = 0;
		}

		throw;
	}
}

void
CEMSConfigCmd::_SetString( wchar_t*& wszLHS, const wchar_t* cwszRHS ) const
{
	if( wszLHS )
	{
		delete[] wszLHS;
		wszLHS = 0;
	}

	if( cwszRHS )
	{

		long lLen = wcslen( cwszRHS );

		wszLHS = new wchar_t[ lLen + 1 ];

		if( !wszLHS )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( wszLHS, 0, (lLen+1)*sizeof(wchar_t) );

		wcscpy( wszLHS, cwszRHS );
	}
}