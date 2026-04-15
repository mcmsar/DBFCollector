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

#ifndef __DART_FTP_WRAPPER_H__
#define __DART_FTP_WRAPPER_H__

#include <string>
#include "emstypes.h"

#include <initguid.h>
#include "dartftp.h"

class CEMSDartFTPWrapper
{
	public:
		CEMSDartFTPWrapper();
		CEMSDartFTPWrapper( const wchar_t* cwszHost, const ULONG culPort, 
							const wchar_t* cwszUser, const wchar_t* cwszPwd,
							const wchar_t* cwszDir );
		CEMSDartFTPWrapper( const CEMSDartFTPWrapper& x );
		~CEMSDartFTPWrapper();

		void Init( const wchar_t* cwszHost, const ULONG culPort, 
					const wchar_t* cwszUser, const wchar_t* cwszPwd, const wchar_t* cwszDir );

		void Send( const wchar_t* cwszLocalFile, const wchar_t* cwszSubDir = NULL );

		void Close();

	private:
		IFtp* _GetFTPClient();

	private:
		static const wchar_t* ms_cwszDartFtpLicenseKey;
		static const long ms_clDefaultTimeout;

	private:
		std::wstring m_owszHost;
		ULONG m_ulPort;
		std::wstring m_owszUser;
		std::wstring m_owszPwd;
		std::wstring m_owszDir;
		ULONG m_ulTimeout;

		IFtp*	m_pFTP;
};

#endif