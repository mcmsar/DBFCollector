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

#ifndef __WEBSERVICE_H__
#define __WEBSERVICE_H__

#include "aobjbase.h"
#include <string>
#include "soaplistenerthreadex.h"
#include "objectmap.h"

//! Provides fundamentals on which to base a Web Service (WS).  
class CEMSWebService : public CApiObjBase
{
	public:
		CEMSWebService();
		CEMSWebService( const CEMSWebService& x );
		virtual ~CEMSWebService();

		//! Input an XML configuration string.  This can be a complete or partial set of 
		//! configuration values.  The format is:
		//!		<ws		clsid='class id of implementing plugin'>
		//!			<host/>
		//!			<port/>
		//!			<backlog/>
		//!			<authenticate/>
		//!			<handlers/>
		//!			<users_file/>
		//!			<usessl/>
		//!			<ssl_keyfile/>	--- Optional.  Required when usessl == yes
		//!			<ssl_password/>	--- Optional.  Required when usessl == yes
		//!			<ssl_cafile/>	--- Optional.  Required when usessl == yes
		//!			<mtom enable='true/false'>	---- Optional
		//!				<tempfolder/>			---- Optional
		//!			</mtom>						---- Optional
		//!			<extras/>
		//!		</ws>
		//!
		//!	The extras element contains configuration specific to the plugin implementing the
		//! web service.
		void SetConfig( const wchar_t* cwszConfigString );

		//! Specify the host either via a fully qualified host name or an IP address.
		//! E.g., machine.cs.fsu.edu or 192.54.131.81.
		void SetHost( const char* cszHost ) { m_oszHost = cszHost; }
		
		std::string GetHost() const { return m_oszHost; }

		void SetPort( const int ciPortNo ) { m_iPortNo = ciPortNo; }
		
		int GetPort() const { return m_iPortNo; }

		void SetBacklog( const int ciValue ) { m_iBacklog = ciValue; }

		int GetBacklog() const { return m_iBacklog; }

		//! Enable/Disable authentication.  Pass a value of true to turn on and false to turn off.
		void EnableAuthenticate( const bool cbValue ) { m_bAuthenticate = cbValue; }

		//! Determine whether authentication is enabled.
		bool IsEnabledAuthenticate() const { return m_bAuthenticate; }

		void SetNumHandlers( const int ciNum ) { m_iNumHandlers = ciNum; }

		int GetNumHandlers() const { return m_iNumHandlers; }

		//! Start the web service.
		void Start();

		//! Stop the web service.
		void Stop();

		//! Determine whether the web service is running.
		bool IsRunning();

		//! Authenticate the caller.
		bool Authenticate( struct soap* pSoap ) { return _VerifyUser( pSoap ); }

		//! Retrieve the name of the web service.
		virtual std::wstring GetWSName() = 0;

		void SetUseSSL( const bool cbValue ) { m_bUseSSL = cbValue; }

		bool GetUseSSL() const { return m_bUseSSL; }

		void SetSSLKeyFile( const char* cszValue ) { m_oszSSLKeyfile = cszValue; }

		std::string GetSSLKeyFile() const { return m_oszSSLKeyfile; }

		void SetSSLKeyPwd( const char* cszValue ) { m_oszSSLKeyPwd = cszValue; }

		std::string GetSSLKeyPwd() const { return m_oszSSLKeyPwd; }

		void SetSSLCAFile( const char* cszValue ) { m_oszSSLCAFile = cszValue; }

		std::string GetSSLCAFile() const { return m_oszSSLCAFile; }

	protected:
		//! Derived classes can override this to provide specialized authentication.
		virtual bool _VerifyUser( struct soap* pSoap );

		//! Derived classes can override this method to implement pre-startup code.
		virtual void _PreStart() {}

		//! Derived classes can override this method to implement post-shutdown code.
		virtual void _PostStop() {}

		//! Derived classes should override this if HTTP Get requests are handled.
		virtual void* _GetHTTPGetHandler() { return NULL; }

#ifdef _xop__Include
		void _LoadAttachment(struct soap* pSoapRuntime, const char* cszFile, 
								const char* cszOptions, _xop__Include* pxopData);
#endif

	private:
		//! Plugins should override this method to receive the configuration file, if needed.
		virtual void _SetPluginConfig( const wchar_t* cwszConfig ) {}

		std::string _GetPassword( const char* cszUser );

		void _LoadUserMap();

	private:
		// Default Values
		static const char*	ms_cszDefaultHost;
		static const int	ms_ciDefaultPort;
		static const int	ms_ciDefaultBacklog;
		static const bool	ms_bDefaultAuthenticate;
		static const int	ms_ciDefaultNumHandlers;
		static const bool	ms_bDefaultUseSSL;

		// Configuration Keys
		static const wchar_t* ms_cwszHost;
		static const wchar_t* ms_cwszPort;
		static const wchar_t* ms_cwszBackLog;
		static const wchar_t* ms_cwszAuthenticate;
		static const wchar_t* ms_cwszHandlers;
		static const wchar_t* ms_cwszUsersFile;
		static const wchar_t* ms_cwszExtras;
		static const wchar_t* ms_cwszUseSSL;
		static const wchar_t* ms_cwszSSLKeyFile;
		static const wchar_t* ms_cwszSSLPassword;
		static const wchar_t* ms_cwszSSLCAFile;
		static const wchar_t* ms_cwszMTOMEnabled;
		static const wchar_t* ms_cwszMTOMTempFolder;

		// User Account file keys
		static const wchar_t* ms_cwszUsers;
		static const wchar_t* ms_cwszUser;
		static const wchar_t* ms_cwszUsername;
		static const wchar_t* ms_cwszPassword;

	private:
		int				m_iPortNo;
		std::string		m_oszHost;
		int				m_iBacklog;
		bool			m_bAuthenticate;
		int				m_iNumHandlers;
		std::wstring	m_owszUserFile;
		std::wstring	m_owszXMLUserConfig;

		CEMSSOAPListenerThreadEx	m_oListenerThread;
		struct soap m_soapRuntime;

		CEMSObjectMap< std::string, std::string >	m_omapUsers;

		bool			m_bUseSSL;
		std::string		m_oszSSLKeyfile;
		std::string		m_oszSSLKeyPwd;
		std::string		m_oszSSLCAFile;

		bool		m_bCryptoThreadsetup;

		bool		m_bMTOMEnabled;
		std::string	m_oszMTOMTempFolder;
};

#ifdef WITH_OPENSSL
//! For SSL support.
int CRYPTO_thread_setup();
void CRYPTO_thread_cleanup();
#endif

#endif