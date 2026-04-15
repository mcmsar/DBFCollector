#include "EMSDEVREG.h"
#include "EMSRGKEY.h"
#include "comcat.h"

const int IIDLEN = 50;

CEMSDeviceRegistry::CEMSDeviceRegistry( const CLSID *lpClsID )
{
	m_lpszCLSID = NULL;
	m_lpIID = NULL;
	m_iNumIID = 0;

	if( lpClsID )
		SetClassID( lpClsID );
	else
		memset( &m_clsID, 0, sizeof( m_clsID ) );
}

CEMSDeviceRegistry::~CEMSDeviceRegistry()
{
	if( m_lpIID )
	{
		delete [] m_lpIID;
		m_lpIID = NULL;
	}
	if( m_lpszCLSID )
	{
		delete [] m_lpszCLSID;
		m_lpszCLSID = NULL;
	}
}

BOOL CEMSDeviceRegistry::SetClassID( const CLSID *lpClsID )
{
	if ( lpClsID )
	{
		WCHAR wszCLSID[ 256 ];
		TCHAR szCLSID[ 256 ];

		m_clsID = *lpClsID;

		if ( m_lpszCLSID )
		{
			delete m_lpszCLSID;
			m_lpszCLSID = 0;
		}

		StringFromGUID2( *lpClsID, wszCLSID, sizeof(wszCLSID) / sizeof(wszCLSID[0]) );

		_WideCharToLocal( szCLSID, wszCLSID, sizeof(szCLSID) / sizeof(szCLSID[0]) );

		m_lpszCLSID = new TCHAR[ lstrlen( szCLSID ) + 1 ];

		if ( m_lpszCLSID )
			lstrcpy( m_lpszCLSID, szCLSID );
	}

	return ( m_lpszCLSID != 0 );
}

EMS_RESULT CEMSDeviceRegistry::RegisterInterface( const IID *lpIID, LPCTSTR lpszDesc )
{
	CATEGORYINFO rgcc[1];
	EMS_RESULT hr;
	ICatRegister *lpCR;
	IID *l_lpIID = new IID[ m_iNumIID + 1 ];
	WCHAR wszDesc[200];

	_LocalToWideChar( wszDesc, lpszDesc, sizeof(wszDesc)/sizeof(wszDesc[0]) );
	::CoInitialize(NULL);

	hr = ::CoCreateInstance( CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_ALL, IID_ICatRegister, (LPVOID*) &lpCR );
	if( SUCCEEDED(hr) )
	{
		rgcc[0].catid = *lpIID;
		rgcc[0].lcid = 0x409;
		wcscpy( rgcc[0].szDescription, wszDesc );
		hr = lpCR->RegisterCategories( 1, rgcc );

		lpCR->Release();
	}

	::CoUninitialize();

	if( SUCCEEDED(hr) )
	{
		if( l_lpIID )
		{
			if( m_lpIID )
			{
				memcpy( l_lpIID, m_lpIID, sizeof(IID) * ( m_iNumIID ) );
				delete [] m_lpIID;
				m_lpIID = l_lpIID;
			}
			else
				m_lpIID = l_lpIID;

			memcpy( &m_lpIID[ m_iNumIID++ ], lpIID, sizeof(IID) );
		}
		else
			hr = EMS_NO_MEMORY;
	}

	return hr;
}

EMS_RESULT CEMSDeviceRegistry::RegisterDevice()
{
	EMS_RESULT hr = EMS_OK;
	ICatRegister *lpCR;

	hr = CoCreateInstance( CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_ALL, IID_ICatRegister, (LPVOID*) &lpCR );
	if( SUCCEEDED(hr) )
	{
		hr = lpCR->RegisterClassImplCategories( m_clsID, m_iNumIID, m_lpIID );
	}

	return hr;
}

EMS_RESULT CEMSDeviceRegistry::UnregisterDevice()
{
	EMS_RESULT hr = EMS_OK;

	return hr;
}

int CEMSDeviceRegistry::_LocalToWideChar( LPWSTR pWide, LPCTSTR pLocal, DWORD dwChars )
{
	int nLength = 0;

	if( pWide )
	{
		*pWide = 0;

#ifdef UNICODE
		lstrcpyn();
#else
		MultiByteToWideChar(CP_ACP, 0, pLocal, -1, pWide, dwChars);
#endif

		nLength = wcslen(pWide);
	}

	return nLength;
}

int CEMSDeviceRegistry::_WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
	int nLength = 0;

	if ( pLocal )
	{
		*pLocal = 0;

#ifdef UNICODE
		lstrcpyn( pLocal, pWide, dwChars );
#else
		WideCharToMultiByte( CP_ACP, 0, pWide, -1, pLocal, dwChars, NULL, NULL);
#endif

		nLength = lstrlen( pLocal );
	}
	return nLength;
}