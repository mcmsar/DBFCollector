
#include <wchar.h>
#include "emsmstrm.h"
#include "urlhandler.h"

#include "emsfstrm.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "fileutility.h"

const wchar_t* cwszSrcDestSeparator = L"_";

CEMSURLHandler::CEMSURLHandler() : m_wszURL(0), m_eURLType(URL_UNKNOWN), m_wszSpec(0), m_pStrm(0)
{
}

CEMSURLHandler::CEMSURLHandler( const CEMSURLHandler& urlHandler )
{
	CEMSURLHandler();

	SetURL( urlHandler.m_wszURL );

	_SetSpec( urlHandler.m_wszSpec  );
	
	m_eURLType = urlHandler.m_eURLType;

	m_pStrm = urlHandler.m_pStrm;
	if( m_pStrm )
		m_pStrm->AddRef();
}

CEMSURLHandler::~CEMSURLHandler()
{
	_Reset();
}

CEMSURLHandler&
CEMSURLHandler::operator=( const CEMSURLHandler& rhs )
{
	_Reset();

	SetURL( rhs.m_wszURL );

	m_eURLType = rhs.m_eURLType;

	return *this;
}

void
CEMSURLHandler::_SetSpec( const wchar_t* cwszSpec )
{
	if( cwszSpec )
	{
		m_wszSpec = new wchar_t[ wcslen(cwszSpec) + 1 ];
		
		if( !m_wszSpec )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_wszSpec, 0, sizeof(wchar_t)*(wcslen(cwszSpec) + 1 ) );

		wcscpy( m_wszSpec, cwszSpec );
	}
}

void
CEMSURLHandler::_Reset()
{
	if( m_wszURL )
	{
		delete[] m_wszURL;
		m_wszURL = 0;
	}

	if( m_wszSpec )
	{
		delete[] m_wszSpec;
		m_wszSpec = 0;
	}

	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = 0;
	}
	

	m_eURLType = URL_UNKNOWN;
}

void
CEMSURLHandler::SetURL( const unsigned long culBytes, const unsigned char* cabyURL )
{
	
	if( culBytes > 0 )
	{
		_Reset();

		std::wstring wszURL = CEMSConversionUtil::ConvertToString( culBytes, (unsigned char*) cabyURL );

		long lStrLen = wszURL.length();

		if( lStrLen > 0 )
		{
			m_wszURL = new wchar_t[ lStrLen + 1 ];

			if( !m_wszURL )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( m_wszURL, 0, (lStrLen+1)*sizeof(wchar_t) );

			wcscpy( m_wszURL, wszURL.c_str() );
		}
	}
}

void
CEMSURLHandler::SetURL( const wchar_t* cwszURL )
{
	if( cwszURL )
	{
		if( m_wszURL )
		{
			delete[] m_wszURL;
			m_wszURL = 0;
		}

		m_wszURL = new wchar_t[ wcslen(cwszURL) + 1 ];

		if( ! m_wszURL )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_wszURL, 0, sizeof(wchar_t)*(wcslen(cwszURL)  + 1 ) );

		wcscpy( m_wszURL, cwszURL );
	}

}

wchar_t* 
CEMSURLHandler::GetURL()
{
	wchar_t* wszRet = 0;

	if( m_wszURL )
	{
		long lLen = 0;
		if( (lLen = wcslen(m_wszURL)) > 0 )
		{
			wszRet = new wchar_t[lLen+1];
			
			if( !wszRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszRet, 0, (lLen+1)*sizeof(wchar_t) );

			wcscpy( wszRet, m_wszURL );
		}
	}

	return wszRet;
}

const wchar_t* 
CEMSURLHandler::GetSpec()
{
	wchar_t* wszRet = 0;

	if( !m_wszSpec )
	{
		_ParseURL( m_wszSpec );
	}

	wszRet = m_wszSpec;

	return wszRet;

}

IEMSSeqStream* 
CEMSURLHandler::OpenStream( bool bWriteable, bool bAllowEdit )
{
	IEMSSeqStream* pStrm = 0;

	try
	{
		if( m_pStrm )
		{
			m_pStrm->Release();
			m_pStrm = 0;
		}

		bool bParseOk =_ParseURL( m_wszSpec );

		if( bParseOk )
		{
			switch( m_eURLType )
			{
				case URL_FILE:
					{
						m_pStrm = _OpenFileStream( m_wszSpec, bWriteable, bAllowEdit );
					}
					break;
				case URL_FTP:
					{
						m_pStrm = _OpenFTPStream( m_wszSpec, bWriteable );
					}
				case URL_HTTP:
					{
						m_pStrm = _OpenHTTPStream( m_wszSpec, bWriteable );
					}
				case URL_UNKNOWN:
				default:
					THROW_RUNTIME_EXCEPTION( EMS_UNKNOWN_URL_TYPE );
					break;

			}

			if( m_pStrm )
			{
				pStrm = m_pStrm;
				pStrm->AddRef();
			}
		}
		else
		{
			THROW_RUNTIME_EXCEPTION( EMS_INVALID_URL );
		}
	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return pStrm;
}

void 
CEMSURLHandler::CloseStream()
{
	switch( m_eURLType )
	{
		case URL_FILE:
			{
				_CloseFileStream( );
			}
			break;
		case URL_FTP:
			{
				_CloseFTPStream( );
			}
			break;
		case URL_HTTP:
			{
				_CloseHTTPStream( );
			}
			break;
		case URL_CLOSED:
			break;
		case URL_UNKNOWN:
			break;
		default:
			THROW_RUNTIME_EXCEPTION( EMS_UNKNOWN_URL_TYPE );
			break;

	}

	m_eURLType = URL_CLOSED;
}

std::wstring 
CEMSURLHandler::GetSource()
{
	// parse the source portion out of the URL
	
	std::wstring wszRet;
	
	wchar_t* wszTemp = 0;

	try
	{
		const wchar_t* cwszSpec = GetSpec();

		if( cwszSpec )
		{
			// Get the file name from the full path.
			CEMSFileUtility fileUtil;
			std::wstring wszFileName = fileUtil.GetFileName( cwszSpec );

			long lLen = wszFileName.length();

			wszTemp = new wchar_t[ lLen + 1 ];

			if( !wszTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszTemp, 0, (lLen + 1)*sizeof(wchar_t) );

			wcscpy( wszTemp, wszFileName.c_str() );

			wchar_t* wszTok = wcstok( wszTemp, cwszSrcDestSeparator );

			if( wszTok )
			{
				wszRet = wszTok;
			}

			delete[] wszTemp;
			wszTemp = 0;

		}

	}
	catch( ... )
	{
		if( wszTemp )
		{
			delete[] wszTemp;
			wszTemp = 0;
		}

		throw;
	}

	return wszRet;

}

std::wstring 
CEMSURLHandler::GetDestination()
{
	// parse the destination portion out of the URL
	
	std::wstring wszRet;

	
	wchar_t* wszTemp = 0;

	try
	{
		const wchar_t* cwszSpec = GetSpec();

		if( cwszSpec )
		{
			// Get the file name from the full path.
			CEMSFileUtility fileUtil;
			std::wstring wszFileName = fileUtil.GetFileName( cwszSpec );

			long lLen = wszFileName.length();

			wszTemp = new wchar_t[ lLen + 1 ];

			if( !wszTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszTemp, 0, (lLen + 1)*sizeof(wchar_t) );

			wcscpy( wszTemp, wszFileName.c_str() );

			wchar_t* wszTok = wcstok( wszTemp, cwszSrcDestSeparator );

			if( wszTok )
			{
				wszTok = wcstok( 0, cwszSrcDestSeparator );

				if( wszTok )
					wszRet = wszTok;
			}

			delete[] wszTemp;
			wszTemp = 0;

		}

	}
	catch( ... )
	{
		if( wszTemp )
		{
			delete[] wszTemp;
			wszTemp = 0;
		}

		throw;
	}

	return wszRet;
}

void 
CEMSURLHandler::_CloseFileStream()
{
	if( m_pStrm )
	{
		CEMSFileStream* pFileStream = reinterpret_cast<CEMSFileStream*>( m_pStrm ); 

		if( pFileStream )
		{
			pFileStream->CloseFile();
		}
	}

	_Reset();
}

void 
CEMSURLHandler::_CloseFTPStream()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED_URL_TYPE );
}

void 
CEMSURLHandler::_CloseHTTPStream()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED_URL_TYPE );
}

IEMSSeqStream*
CEMSURLHandler::_OpenFileStream( const wchar_t* cwszAddress, bool bWriteable, bool cbAllowEdit )
{
	IEMSSeqStream* pStrm = 0;

	if( cwszAddress )
	{
		CEMSFileStream* pFileStream = 0;

		try
		{
			pFileStream = new CEMSFileStream;

			if( !pFileStream )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			BOOL	BWriteable = bWriteable ? TRUE : FALSE;
			BOOL	BAllowEdit = cbAllowEdit ? TRUE : FALSE;
			BOOL	BAppend = FALSE;

#if defined(UNICODE) || defined(_UNICODE)
			EMS_RESULT hr = pFileStream->OpenFile( cwszAddress, BWriteable, BAppend, BAllowEdit );
#else
			EMS_RESULT hr = pFileStream->OpenFile( CEMSConversionUtil::ConvertToString( cwszAddress ).c_str(), BWriteable, BAppend, BAllowEdit );
#endif

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pFileStream->QueryInterface( IID_IEMSSeqStream, (void**) &pStrm );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pFileStream->Release();
			pFileStream = 0;
		}
		catch( ... )
		{
			if( pFileStream )
			{
				pFileStream->Release();
				pFileStream = 0;
			}

			if( pStrm )
			{
				pStrm->Release();
				pStrm = 0;
			}

			throw;
		}
	}

	return pStrm;
}

IEMSSeqStream*
CEMSURLHandler::_OpenFTPStream( const wchar_t* cwszAddress, bool bWriteable )
{
	IEMSSeqStream* pStrm = 0;

	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED_URL_TYPE );

	return pStrm;
}

IEMSSeqStream*
CEMSURLHandler::_OpenHTTPStream( const wchar_t* cwszAddress, bool bWriteable )
{
	IEMSSeqStream* pStrm = 0;

	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED_URL_TYPE );

	return pStrm;
}

bool 
CEMSURLHandler::_ParseURL( wchar_t*& wszSpec )
{
	wszSpec = 0;
	bool bRet = false;

	wchar_t* wszLocation = 0;

	if( m_wszURL )
	{
		try
		{
			const wchar_t* cwszURLSep = L"://";

			wchar_t* wszURLSep = wcsstr( m_wszURL, cwszURLSep );

			if( wszURLSep )
			{
				long lURLTypeLen = wszURLSep - m_wszURL ;

				if( lURLTypeLen < 1 )
				{
					THROW_RUNTIME_EXCEPTION( EMS_INVALID_URL );
				}

				wszLocation = new wchar_t[ lURLTypeLen + 1];
				if( !wszLocation )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( wszLocation, 0, sizeof(wchar_t)*(lURLTypeLen + 1 ) );
				wcsncpy( wszLocation, m_wszURL, lURLTypeLen );

				_EncodeURLType( wszLocation );

				delete[] wszLocation;
				wszLocation = 0;

				wchar_t* wszAddr = wszURLSep + 3;

				long lLen = wcslen( wszAddr );

				if( lLen > 0 )
				{
					if( wszSpec )
					{
						delete [] wszSpec;
						wszSpec = NULL;
					}

					wszSpec = new wchar_t[ lLen + 1 ];

					if( !wszSpec )
					{
						THROW_NOMEMORY_EXCEPTION();
					}

					memset( wszSpec, 0, sizeof(wchar_t)*(lLen + 1) );

					wcscpy( wszSpec, wszAddr );
				}
				else
				{
					THROW_RUNTIME_EXCEPTION( EMS_INVALID_URL );
				}

				bRet = true;
				
			}
			else
			{
				// No URL type specifed.  Therefore, assume default is "file"
				wchar_t* wszDefaultURLType = L"file";
				wszLocation = new wchar_t[ wcslen(wszDefaultURLType) + 1 ];

				if( !wszLocation )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( wszLocation, 0, sizeof(wchar_t)*(wcslen(wszDefaultURLType) + 1) );
				wcscpy( wszLocation, wszDefaultURLType );

				_EncodeURLType( wszLocation );

				delete[] wszLocation;
				wszLocation = 0;

				wszSpec = new wchar_t[ wcslen(m_wszURL) + 1 ];
				memset( wszSpec, 0, sizeof(wchar_t)*(wcslen(m_wszURL) + 1 ) );
				wcscpy( wszSpec, m_wszURL );

				bRet = true;
			}
		}
		catch( ... )
		{
			if( wszLocation )
			{
				delete[] wszLocation;
				wszLocation = 0;
			}

			if( wszSpec )
			{
				delete[] wszSpec;
				wszSpec = 0;
			}

			throw;
		}
	}
		
	return bRet;
}

void 
CEMSURLHandler::_EncodeURLType( const wchar_t* cwszURLType )
{
	if( cwszURLType )
	{
		if( 0 == wcsicmp( cwszURLType, L"FILE" ) )
		{
			m_eURLType = URL_FILE;
		}
		else if( 0 == wcsicmp( cwszURLType, L"HTTP" ) )
		{
			m_eURLType = URL_HTTP;
		}
		else if( 0 == wcsicmp( cwszURLType, L"FTP" ) )
		{
			m_eURLType = URL_FTP;
		}
		else
		{
			m_eURLType = URL_UNKNOWN;

		}
	}
}