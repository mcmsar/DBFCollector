/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
*	Portions of this code are derived from the gSoap 2.7 samples 
*   under the (mtom sample).
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2005, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#pragma warning(disable:4786)

#include "webservice.h"
#include "configurationaccessor.h"
#include "convutility.h"
#include "emsexcpt.h"
#include "wsmsgs.h"
#ifndef NO_OPEN_SSL
#include "plugin/wsseapi.h"
#endif
#include "soapmimehandler.h"

#include <sys/stat.h>
#include "ccbootstrap.h"


// Default Values:
const char*	CEMSWebService::ms_cszDefaultHost = "localhost";
const int	CEMSWebService::ms_ciDefaultPort = 8071;
const int	CEMSWebService::ms_ciDefaultBacklog = 100;
const bool	CEMSWebService::ms_bDefaultAuthenticate = false;
const int	CEMSWebService::ms_ciDefaultNumHandlers = 1;
const bool	CEMSWebService::ms_bDefaultUseSSL = false;

// Configuration Keys
#ifdef USE_APACHE_XERCES
const wchar_t* CEMSWebService::ms_cwszHost = L"ws/host";
const wchar_t* CEMSWebService::ms_cwszPort = L"ws/port_id";
const wchar_t* CEMSWebService::ms_cwszBackLog = L"ws/backlog";
const wchar_t* CEMSWebService::ms_cwszAuthenticate = L"ws/authenticate";
const wchar_t* CEMSWebService::ms_cwszHandlers = L"ws/handlers";
const wchar_t* CEMSWebService::ms_cwszUsersFile = L"ws/users_file";
const wchar_t* CEMSWebService::ms_cwszExtras = L"ws/extras";
const wchar_t* CEMSWebService::ms_cwszUseSSL = L"ws/usessl";
const wchar_t* CEMSWebService::ms_cwszSSLKeyFile = L"ws/ssl_keyfile";
const wchar_t* CEMSWebService::ms_cwszSSLPassword = L"ws/ssl_password";
const wchar_t* CEMSWebService::ms_cwszSSLCAFile = L"ws/ssl_cafile";
const wchar_t* CEMSWebService::ms_cwszMTOMEnabled = L"ws/mtom/@enabled";
const wchar_t* CEMSWebService::ms_cwszMTOMTempFolder = L"ws/mtom/tempfolder";
#else
const wchar_t* CEMSWebService::ms_cwszHost = L"host";
const wchar_t* CEMSWebService::ms_cwszPort = L"port_id";
const wchar_t* CEMSWebService::ms_cwszBackLog = L"backlog";
const wchar_t* CEMSWebService::ms_cwszAuthenticate = L"authenticate";
const wchar_t* CEMSWebService::ms_cwszHandlers = L"handlers";
const wchar_t* CEMSWebService::ms_cwszUsersFile = L"users_file";
const wchar_t* CEMSWebService::ms_cwszExtras = L"extras";
const wchar_t* CEMSWebService::ms_cwszUseSSL = L"usessl";
const wchar_t* CEMSWebService::ms_cwszSSLKeyFile = L"ssl_keyfile";
const wchar_t* CEMSWebService::ms_cwszSSLPassword = L"ssl_password";
const wchar_t* CEMSWebService::ms_cwszSSLCAFile = L"ssl_cafile";
const wchar_t* CEMSWebService::ms_cwszMTOMEnabled = L"mtom/@enabled";
const wchar_t* CEMSWebService::ms_cwszMTOMTempFolder = L"mtom/tempfolder";
#endif

// User account file keys
#ifdef USE_APACHE_XERCES
const wchar_t* CEMSWebService::ms_cwszUsers = L"users";
const wchar_t* CEMSWebService::ms_cwszUser = L"users/user";
const wchar_t* CEMSWebService::ms_cwszUsername = L"user/username";
const wchar_t* CEMSWebService::ms_cwszPassword = L"user/password";
#else
const wchar_t* CEMSWebService::ms_cwszUsers = L"users";
const wchar_t* CEMSWebService::ms_cwszUser = L"user";
const wchar_t* CEMSWebService::ms_cwszUsername = L"username";
const wchar_t* CEMSWebService::ms_cwszPassword = L"password";
#endif

CEMSWebService::CEMSWebService() :	m_iPortNo( ms_ciDefaultPort ),
									m_oszHost( ms_cszDefaultHost ),
									m_iBacklog( ms_ciDefaultBacklog ),
									m_bAuthenticate( ms_bDefaultAuthenticate ),
									m_iNumHandlers( ms_ciDefaultNumHandlers ),
									m_bUseSSL( ms_bDefaultUseSSL ),
									m_bCryptoThreadsetup( false ),
									m_bMTOMEnabled( true )
{
//	soap_init( &m_soapRuntime );
}

CEMSWebService::CEMSWebService( const CEMSWebService& x ) :
									m_iPortNo( x.m_iPortNo ),
									m_oszHost( x.m_oszHost ),
									m_iBacklog( x.m_iBacklog ),
									m_bAuthenticate( x.m_bAuthenticate ),
									m_iNumHandlers( x.m_iNumHandlers ),
									m_owszUserFile( x.m_owszUserFile ),
									m_owszXMLUserConfig( x.m_owszXMLUserConfig ),
									m_bUseSSL( x.m_bUseSSL ),
									m_oszSSLKeyfile( x.m_oszSSLKeyfile ),
									m_oszSSLKeyPwd( x.m_oszSSLKeyPwd ),
									m_oszSSLCAFile( x.m_oszSSLCAFile ),
									m_bCryptoThreadsetup( false ),
									m_bMTOMEnabled( x.m_bMTOMEnabled ),
									m_oszMTOMTempFolder( x.m_oszMTOMTempFolder )
{
//	soap_init( &m_soapRuntime );
}

CEMSWebService::~CEMSWebService()
{
	Stop();
}

void 
CEMSWebService::SetConfig( const wchar_t* cwszConfigString )
{
	// Read in the configuration values.
	CEMSConfigurationAccessor oConfig;
	oConfig.SetSource( cwszConfigString );

	std::wstring owszValue = oConfig.GetElementValue( ms_cwszHost );

	if( !owszValue.empty() )
	{
		SetHost( CEMSConversionUtil::ConvertToString( owszValue.c_str() ).c_str() );
	}

	int iPort = oConfig.GetElementValueInt( ms_cwszPort );

	if( 0 != iPort )
	{
		SetPort( iPort );
	}

	int iBackLog = oConfig.GetElementValueInt( ms_cwszBackLog );

	if( 0 != iBackLog )
	{
		SetBacklog( iBackLog );
	}

	owszValue = oConfig.GetElementValue( ms_cwszAuthenticate );

	if( !owszValue.empty() )
	{
		EnableAuthenticate( oConfig.GetElementValueBoolean( ms_cwszAuthenticate ) );
	}

	int iNumHandlers = oConfig.GetElementValueInt( ms_cwszHandlers );

	if( 0 != iNumHandlers )
	{
		SetNumHandlers( iNumHandlers );
	}

	if( CCBootstrap::IsMEOSystem() )
	{
		m_owszXMLUserConfig = oConfig.GetAccessor( ms_cwszUsers ).Serialize();
	}
	else
	{
		m_owszUserFile = oConfig.GetElementValue( ms_cwszUsersFile );
	}

	std::wstring owszPluginConfig = oConfig.GetAccessor( ms_cwszExtras ).Serialize();
	
	if( !owszPluginConfig.empty() )
		_SetPluginConfig( owszPluginConfig.c_str() );

	m_bUseSSL = oConfig.GetElementValueBoolean( ms_cwszUseSSL );

	m_oszSSLKeyfile = CEMSConversionUtil::ConvertToString( oConfig.GetElementValue( ms_cwszSSLKeyFile ).c_str() );
	m_oszSSLKeyPwd = CEMSConversionUtil::ConvertToString( oConfig.GetElementValue( ms_cwszSSLPassword ).c_str() );
	m_oszSSLCAFile = CEMSConversionUtil::ConvertToString( oConfig.GetElementValue( ms_cwszSSLCAFile ).c_str() );

	if( (m_bMTOMEnabled = oConfig.GetElementValueBoolean( ms_cwszMTOMEnabled )) )
		m_oszMTOMTempFolder = CEMSConversionUtil::ConvertToString( oConfig.GetElementValue( ms_cwszMTOMTempFolder ).c_str() );

}

void 
CEMSWebService::Start()
{
	try
	{
		if( !m_oListenerThread.IsRunning() )
		{
			_PreStart();

#ifndef NO_OPEN_SSL
			if( m_bUseSSL && !m_bCryptoThreadsetup )
			{
				soap_ssl_init(); /* init OpenSSL (just once) */
				if( CRYPTO_thread_setup() )
				{
					CEMSLogMsgParam oParam;
					oParam.AddString( CEMSConversionUtil::ConvertToString( GetHost().c_str() ).c_str() );
					throw CEMSException( EMS_WS_HOST_CRYPTO_INIT_FAILURE, oParam );
				} 
				else
				{
					m_bCryptoThreadsetup = true;
				}
			}
#endif

#ifdef _xop__Include
			if( m_bMTOMEnabled )
			{
				// Enable MTOM.
				soap_init1(&m_soapRuntime, SOAP_ENC_MTOM);

				// Set the temporary storage folder if there is one specified.
				CEMSSoapMimeHandler::SetWriteFolder( m_oszMTOMTempFolder.c_str() );

				// Set the MIME callbacks.
				m_soapRuntime.fmimereadopen = CEMSSoapMimeHandler::ReadOpen;
				m_soapRuntime.fmimereadclose = CEMSSoapMimeHandler::ReadClose;
				m_soapRuntime.fmimeread = CEMSSoapMimeHandler::Read;
				m_soapRuntime.fmimewriteopen = CEMSSoapMimeHandler::ServerWriteOpen;
				m_soapRuntime.fmimewriteclose = CEMSSoapMimeHandler::ServerWriteClose;
				m_soapRuntime.fmimewrite = CEMSSoapMimeHandler::ServerWrite;
			}
			else
#endif
				soap_init( &m_soapRuntime );

#ifndef NO_OPEN_SSL
			if( m_bUseSSL )
			{
				if( m_oszSSLKeyfile.empty() )
				{
					CEMSLogMsgParam oParam;
					oParam.AddString( CEMSConversionUtil::ConvertToString( GetHost().c_str() ).c_str() );
					throw CEMSException( EMS_WS_HOST_SSL_NO_KEY_FILE, oParam );
				}

				if( m_oszSSLKeyPwd.empty() )
				{
					CEMSLogMsgParam oParam;
					oParam.AddString( CEMSConversionUtil::ConvertToString( GetHost().c_str() ).c_str() );
					throw CEMSException( EMS_WS_HOST_SSL_NO_KEY_PWD, oParam );
				}

				if (soap_ssl_server_context(&m_soapRuntime,
									SOAP_SSL_DEFAULT,
									m_oszSSLKeyfile.c_str(), /* keyfile: required when server must authenticate to clients (see SSL docs on how to obtain this file) */
									m_oszSSLKeyPwd.c_str(), /* password to read the key file */
									m_oszSSLCAFile.empty() ? NULL : m_oszSSLCAFile.c_str(), /* optional cacert file to store trusted certificates */
									NULL, /* optional capath to directory with trusted certificates */
									NULL, /* DH file, if NULL use RSA */
									NULL, /* if randfile!=NULL: use a file with random data to seed randomness */
									NULL /* optional server identification to enable SSL session cache (must be a unique name) */    ))
				{
					soap_print_fault(&m_soapRuntime, stderr);
					
					CEMSLogMsgParam oParam;
					oParam.AddString( CEMSConversionUtil::ConvertToString( GetHost().c_str() ).c_str() );
					throw CEMSException( EMS_WS_HOST_SSL_CTX_FAILURE, oParam );
				} 
			}
#endif

			int m=soap_bind( &m_soapRuntime, GetHost().c_str(), GetPort(), GetBacklog() );

			if( m < 0 )
			{
				soap_print_fault( &m_soapRuntime, stderr );

				CEMSLogMsgParam oParam;
				oParam.AddString( CEMSConversionUtil::ConvertToString( GetHost().c_str() ).c_str() );
				oParam.Add( GetPort() );

				throw CEMSException( EMS_WS_HOST_BIND_FAILURE, oParam );
			}
			else
			{
				m_oListenerThread.Init( &m_soapRuntime );
				m_oListenerThread.SetNumHandlerThreads( GetNumHandlers() );
				m_oListenerThread.RegisterGetHandler( _GetHTTPGetHandler() );
				m_oListenerThread.SetUseSSL( m_bUseSSL );
				m_oListenerThread.Start();
			}
		}
	}
	catch( ... )
	{
		if( m_bCryptoThreadsetup )
		{
#ifndef NO_OPEN_SSL
			CRYPTO_thread_cleanup();
#endif
			m_bCryptoThreadsetup = false;
		}

		throw;
	}
}

void 
CEMSWebService::Stop()
{
	if( m_oListenerThread.IsRunning() )
		m_oListenerThread.Shutdown();

	soap_done( &m_soapRuntime );

	if( m_bCryptoThreadsetup )
	{
#ifndef NO_OPEN_SSL
		CRYPTO_thread_cleanup();
#endif
		m_bCryptoThreadsetup = false;
	}

	_PostStop();
}

bool 
CEMSWebService::IsRunning()
{
	return m_oListenerThread.IsRunning();
}

bool 
CEMSWebService::_VerifyUser( struct soap* pSoap )
{
	bool bRet = true;

#ifndef NO_OPEN_SSL
	if( IsEnabledAuthenticate() )
	{
		const char* cszUserName = soap_wsse_get_Username( pSoap );
		std::string oszPassword;

		if ( !cszUserName )
		{
			CEMSLogMsgParam oParam;
			oParam.AddString( GetWSName().c_str() );

			throw CEMSException( EMS_WS_PLUGIN_NO_USER, oParam );
		}
		else
		{
			oszPassword = _GetPassword( cszUserName ); // lookup password of username
		
			if( SOAP_OK == soap_wsse_verify_Password(pSoap, oszPassword.c_str()))
			{
				bRet = true;
			}
			else
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( GetWSName().c_str() );
				oParam.AddString( CEMSConversionUtil::ConvertToString( cszUserName ).c_str() );

				throw CEMSException( EMS_WS_PLUGIN_PWD_VERIF_FAILURE, oParam );
			}

		}
	}
#endif
	return bRet;
}

std::string
CEMSWebService::_GetPassword( const char* cszUser )
{
	std::string oszPwd;

	if( 0 == m_omapUsers.Count() )
	{
		// Load the map from file.
		_LoadUserMap();
	}

	std::string oszUser( cszUser );

	if( m_omapUsers.IsInMap( oszUser ) )
	{
		oszPwd = m_omapUsers.Get( oszUser );
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( GetWSName().c_str() );
		oParam.AddString( CEMSConversionUtil::ConvertToString( cszUser ).c_str() );
		throw CEMSException( EMS_WS_PLUGIN_USER_NOT_FOUND, oParam );
	}

	return oszPwd;
}


void
CEMSWebService::_LoadUserMap()
{
	if( 0 == m_omapUsers.Count() )
	{
		CEMSConfigurationAccessor oUserAccounts;
		if( CCBootstrap::IsMEOSystem() )
		{
			if( !m_owszXMLUserConfig.empty() )
				oUserAccounts.SetSource( m_owszXMLUserConfig.c_str() );
			else
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( GetWSName().c_str() );
				throw CEMSException( EMS_WS_PLUGIN_NO_USERS_FILE, oParam );
			}
		}
		else
		{
			if( m_owszUserFile.empty() )
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( GetWSName().c_str() );
				throw CEMSException( EMS_WS_PLUGIN_NO_USERS_FILE, oParam );
			}

			oUserAccounts.SetSourceFile( m_owszUserFile.c_str() );
		}

		CEMSObjectList<CEMSConfigurationAccessor> olstUsers = oUserAccounts.GetAccessorList( ms_cwszUser );

		olstUsers.MoveFirst();

		for( ULONG l = 0; l < olstUsers.Count(); l++ )
		{
			CEMSConfigurationAccessor oUser = olstUsers.GetNext();

			std::wstring owszUser = oUser.GetElementValue( ms_cwszUsername );

			if( owszUser.empty() )
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( GetWSName().c_str() );
				throw CEMSException( EMS_WS_PLUGIN_NO_USERNAME, oParam );
			}

			// For now, storing as clear text passwords.  This assumes that the user file is secure.
			// For a more secure solution, passwords should be stored as digests.  See the gSOAP
			// documentation.
			std::wstring owszPwd = oUser.GetElementValue( ms_cwszPassword );

			// Passwords can be blank.
			if( owszPwd.empty() )
			{
				owszPwd = L"";
			}

			m_omapUsers.Add(	CEMSConversionUtil::ConvertToString( owszUser.c_str() ),
								CEMSConversionUtil::ConvertToString( owszPwd.c_str() ) );
			
		}
				
	}
}

// From gSoap 2.7 samples sslserver.c
#ifdef WITH_OPENSSL

#if defined(WIN32)
# define MUTEX_TYPE		HANDLE
# define MUTEX_SETUP(x)		(x) = CreateMutex(NULL, FALSE, NULL)
# define MUTEX_CLEANUP(x)	CloseHandle(x)
# define MUTEX_LOCK(x)		WaitForSingleObject((x), INFINITE)
# define MUTEX_UNLOCK(x)	ReleaseMutex(x)
# define THREAD_ID		GetCurrentThreadId()
#elif defined(_POSIX_THREADS)
# define MUTEX_TYPE		pthread_mutex_t
# define MUTEX_SETUP(x)		pthread_mutex_init(&(x), NULL)
# define MUTEX_CLEANUP(x)	pthread_mutex_destroy(&(x))
# define MUTEX_LOCK(x)		pthread_mutex_lock(&(x))
# define MUTEX_UNLOCK(x)	pthread_mutex_unlock(&(x))
# define THREAD_ID		pthread_self()
#else
# error "You must define mutex operations appropriate for your platform"
# error	"See OpenSSL /threads/th-lock.c on how to implement mutex on your platform"
#endif

struct CRYPTO_dynlock_value
{ MUTEX_TYPE mutex;
};

static MUTEX_TYPE *mutex_buf;

static struct CRYPTO_dynlock_value *dyn_create_function(const char *file, int line)
{ struct CRYPTO_dynlock_value *value;
  value = (struct CRYPTO_dynlock_value*)malloc(sizeof(struct CRYPTO_dynlock_value));
  if (value)
    MUTEX_SETUP(value->mutex);
  return value;
}

static void dyn_lock_function(int mode, struct CRYPTO_dynlock_value *l, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(l->mutex);
  else
    MUTEX_UNLOCK(l->mutex);
}

static void dyn_destroy_function(struct CRYPTO_dynlock_value *l, const char *file, int line)
{ MUTEX_CLEANUP(l->mutex);
  free(l);
}

void locking_function(int mode, int n, const char *file, int line)
{ if (mode & CRYPTO_LOCK)
    MUTEX_LOCK(mutex_buf[n]);
  else
    MUTEX_UNLOCK(mutex_buf[n]);
}

unsigned long id_function()
{ return (unsigned long)THREAD_ID;
}

int CRYPTO_thread_setup()
{ int i;
  mutex_buf = (MUTEX_TYPE*)malloc(CRYPTO_num_locks() * sizeof(MUTEX_TYPE));
  if (!mutex_buf)
    return SOAP_EOM;
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_SETUP(mutex_buf[i]);
  CRYPTO_set_id_callback(id_function);
  CRYPTO_set_locking_callback(locking_function);
  CRYPTO_set_dynlock_create_callback(dyn_create_function);
  CRYPTO_set_dynlock_lock_callback(dyn_lock_function);
  CRYPTO_set_dynlock_destroy_callback(dyn_destroy_function);
  return SOAP_OK;
}

void CRYPTO_thread_cleanup()
{ int i;
  if (!mutex_buf)
    return;
  CRYPTO_set_id_callback(NULL);
  CRYPTO_set_locking_callback(NULL);
  CRYPTO_set_dynlock_create_callback(NULL);
  CRYPTO_set_dynlock_lock_callback(NULL);
  CRYPTO_set_dynlock_destroy_callback(NULL);
  for (i = 0; i < CRYPTO_num_locks(); i++)
    MUTEX_CLEANUP(mutex_buf[i]);
  free(mutex_buf);
  mutex_buf = NULL;
}


#endif