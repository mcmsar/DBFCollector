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

#include "dartftpwrapper.h"
#include "emsexcpt.h"
#include "fileutility.h"
#include <comutil.h>
#include <sstream>
#include "uniquefilenameprovider.h"

const wchar_t* CEMSDartFTPWrapper::ms_cwszDartFtpLicenseKey = L"1530-1-593-254436:30800004:EMS Technologies";
const long CEMSDartFTPWrapper::ms_clDefaultTimeout = 60;

#define EMSDARTFTPCALL( funccall ) { EMS_RESULT hrLocal = EMS_OK; if( EMS_OK != ( hrLocal = funccall) ) { THROW_RUNTIME_EXCEPTION(hrLocal); } }

CEMSDartFTPWrapper::CEMSDartFTPWrapper() : m_ulPort( 21 ), m_ulTimeout( ms_clDefaultTimeout ), m_pFTP(NULL)
{
}

CEMSDartFTPWrapper::CEMSDartFTPWrapper( const wchar_t* cwszHost, const ULONG culPort, 
										const wchar_t* cwszUser, const wchar_t* cwszPwd,
										const wchar_t* cwszDir ) : 
													m_owszHost( cwszHost ), 
													m_ulPort( ( 0 == culPort ) ? 21 : culPort ),
													m_owszUser( cwszUser ),
													m_owszPwd( cwszPwd ),
													m_owszDir( cwszDir ? cwszDir : L"" ),
													m_ulTimeout( ms_clDefaultTimeout ),
													m_pFTP( NULL )
{
}


CEMSDartFTPWrapper::CEMSDartFTPWrapper( const CEMSDartFTPWrapper& x ) : 
													m_owszHost( x.m_owszHost ), 
													m_ulPort( x.m_ulPort ),
													m_owszUser( x.m_owszUser ),
													m_owszPwd( x.m_owszPwd ),
													m_owszDir( x.m_owszDir ),
													m_ulTimeout( x.m_ulTimeout ),
													m_pFTP( x.m_pFTP )
{
	if( m_pFTP )
		m_pFTP->AddRef();
}

CEMSDartFTPWrapper::~CEMSDartFTPWrapper()
{
	Close();
}

void 
CEMSDartFTPWrapper::Init( const wchar_t* cwszHost, const ULONG culPort, 
					const wchar_t* cwszUser, const wchar_t* cwszPwd, const wchar_t* cwszDir )
{
	m_owszHost = cwszHost;
	m_ulPort = ( 0 == culPort ) ? 21 : culPort;
	m_owszUser = cwszUser;
	m_owszPwd = cwszPwd;
	m_owszDir = cwszDir;
}

void
CEMSDartFTPWrapper::Close()
{
	if( m_pFTP )
	{
		m_pFTP->Logout();
		m_pFTP->Release();
		m_pFTP = NULL;
	}
}

void 
CEMSDartFTPWrapper::Send( const wchar_t* cwszLocalFile, const wchar_t* cwszSubDir )
{
	IFtp* pFtpClient = NULL;

	try
	{
		pFtpClient = _GetFTPClient();

		if( !pFtpClient )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		std::wstringstream owstrmDest;

		if( !m_owszDir.empty() )
			owstrmDest << m_owszDir.c_str() << L"\\";
		
		if( cwszSubDir )
			owstrmDest << cwszSubDir << L"\\";

		EMS_RESULT hr = EMS_OK;

		if( owstrmDest.str().length() > 0 )
		{
			// Create the folder hierarchy.
			wchar_t wszTemp[256];
			wcscpy( wszTemp, owstrmDest.str().c_str() );

			wchar_t* wszTok = wcstok( wszTemp, L"\\/");
			std::wstring owszCurrent;

			while( wszTok )
			{
				if( owszCurrent.length() > 0 )
					owszCurrent.append( L"\\" );

				owszCurrent.append( wszTok );

				hr = pFtpClient->MakeDirectory( _bstr_t( owszCurrent.c_str() ) );

				if( EMS_OK != hr &&
					0x800a2b5d != hr )	// This appears to be the Dart error code for dir already exists.
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}
				else
					hr = EMS_OK;

				wszTok = wcstok( NULL, L"\\/");
			}
			
		}

		owstrmDest << CEMSFileUtility::GetFileName( cwszLocalFile ).c_str() << CEMSFileUtility::GetExtension( cwszLocalFile ).c_str();

		hr = pFtpClient->Store( _bstr_t( owstrmDest.str().c_str() ), _variant_t( _bstr_t( cwszLocalFile ) ), 0  );

		if( EMS_OK != hr )
		{
			// Filename may already exists on server.  Add a unique time tag and try again.
			std::wstringstream owstrmRetry;

			if( cwszSubDir )
				owstrmRetry << cwszSubDir << L"\\";

			owstrmRetry << CEMSFileUtility::GetFileName( cwszLocalFile ).c_str() << L"_" << 
						CEMSUniqueFileNameProvider::GetUniqueFileName( L"", L"" ).c_str() << 
						CEMSFileUtility::GetExtension( cwszLocalFile ).c_str();

			EMSDARTFTPCALL( pFtpClient->Store( _bstr_t( owstrmRetry.str().c_str() ), _variant_t( _bstr_t( cwszLocalFile ) ), 0  ) );

		}

		pFtpClient->Release();
		pFtpClient = NULL;
	}
	catch( ... )
	{
		if( pFtpClient )
		{
			pFtpClient->Logout();
			pFtpClient->Release();
			pFtpClient = NULL;
		}

		throw;
	}

}

IFtp*
CEMSDartFTPWrapper::_GetFTPClient()
{
	IFtp* pRet = NULL;
	IClassFactory2*	pClassFact = NULL;

	try
	{
		if( !m_pFTP )
		{

			EMS_RESULT hr = CoGetClassObject( CLSID_Ftp, CLSCTX_ALL, NULL, IID_IClassFactory2,
										(void **)&pClassFact);

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			if( !pClassFact )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			hr = pClassFact->CreateInstanceLic( NULL, 
												 NULL, 
												 IID_IFtp,
												 _bstr_t( ms_cwszDartFtpLicenseKey ),
												 (void **) &m_pFTP);

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			EMSDARTFTPCALL( m_pFTP->put_TimeOut( 1000*(0 == m_ulTimeout ? ms_clDefaultTimeout : m_ulTimeout ) ) );
			EMSDARTFTPCALL( m_pFTP->Login( _bstr_t(m_owszHost.c_str()), _bstr_t(m_owszUser.c_str()), 
										_bstr_t(m_owszPwd.c_str()), _bstr_t(L""), 
										0 == m_ulPort ? 21 : m_ulPort ) );
			EMSDARTFTPCALL( m_pFTP->put_Type( ftpAscii ) );


			pClassFact->Release();
			pClassFact = NULL;
		}

		pRet = m_pFTP;
		pRet->AddRef();
		
	}
	catch( ... )
	{
		if( pClassFact )
		{
			pClassFact->Release();
			pClassFact = NULL;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( m_pFTP )
		{
			m_pFTP->Release();
			m_pFTP = NULL;
		}

		throw;
	}

	return pRet;
}