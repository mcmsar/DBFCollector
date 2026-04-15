#ifndef __URL_HANDLER_H__
#define __URL_HANDLER_H__

#include <string>

// forward declarations
interface IEMSSeqStream;

typedef enum tagURLType
{
	URL_UNKNOWN = 0,
	URL_FILE = 1,
	URL_FTP = 2,
	URL_HTTP = 3,
	URL_CLOSED = 4,
	URL_LAST = URL_CLOSED
} EMSURLTYPE;

class CEMSURLHandler
{
	public:
		CEMSURLHandler();
		CEMSURLHandler( const CEMSURLHandler& urlHandler );
		virtual ~CEMSURLHandler();

		void SetURL( const unsigned long ulBytes, const unsigned char* cabyURL );
		void SetURL( const wchar_t* cwszURL );
		wchar_t* GetURL();
		const wchar_t* GetSpec();
		IEMSSeqStream* OpenStream( bool bWriteable = false, bool bAllowEdit = false );
		EMSURLTYPE GetURLType() { return m_eURLType; }

		CEMSURLHandler& operator=( const CEMSURLHandler& rhs );

		void CloseStream();

		std::wstring GetSource();
		std::wstring GetDestination();

	private:
		void _SetSpec( const wchar_t* cwszSpec );
		void _Reset();
		bool _ParseURL( wchar_t*& wszSpec );
		IEMSSeqStream* _OpenFileStream( const wchar_t* cwszAddress, bool bWriteable = false, bool bAllowEdit = false );
		IEMSSeqStream* _OpenFTPStream( const wchar_t* cwszAddress, bool bWriteable = false );
		IEMSSeqStream* _OpenHTTPStream( const wchar_t* cwszAddress, bool bWriteable = false );
		void _EncodeURLType( const wchar_t* cwszURLType );
		void _CloseFileStream();
		void _CloseFTPStream();
		void _CloseHTTPStream();


	private:
		wchar_t* m_wszURL;
		wchar_t* m_wszSpec;
		EMSURLTYPE m_eURLType;
		IEMSSeqStream*	m_pStrm;

};

#endif // __URL_HANDLER_H__
