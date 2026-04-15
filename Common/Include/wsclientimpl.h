/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __WSCLIENT_H__
#define __WSCLIENT_H__

#include "aobjbase.h"
#include <string>

struct soap;

//! Base class for web service clients.
class CEMSWSClient : public CApiObjBase
{
	public:
		CEMSWSClient();
		CEMSWSClient( const CEMSWSClient& x );
		virtual ~CEMSWSClient();

		//! Set the target Web Service URL.
		void SetURL( const wchar_t* cwszURL );

		//! Set a user name to use when sending messages to the target Web Service.
		void SetUsername( const wchar_t* cwszUser );

		//! Set a password to use when sending messages to the target Web Service.
		void SetPassword( const wchar_t* cwszPwd );

		//! Enable or disable MTOM support.
		void EnableMTOM( const bool cbOn = true ) { m_bMTOMEnabled = cbOn; }

	protected:
		void _ThrowSOAPException( const int ciRetCode, struct soap* pSoap );
		std::string _GetUser() const { return m_oszUser; }
		std::string _GetPwd() const { return m_oszPwd; }
		std::string _GetURL() const { return m_oszURL; }

		//! Initialize the soap runtime for the client.  Returns the endpoint URL as a string.
		//! The allocated memory is released when the soap runtime is released.
		char* _Init( struct soap* pSoapRuntime );


	private:
		std::string m_oszURL;
		std::string m_oszUser;
		std::string m_oszPwd;
		bool m_bMTOMEnabled;
};

#endif