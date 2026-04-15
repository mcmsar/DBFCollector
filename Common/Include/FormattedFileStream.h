/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __FORMATTED_FILE_STREAM_H__
#define __FORMATTED_FILE_STREAM_H__

#include "aobjbase.h"
#include "emspipe.h"
#include <string>

typedef enum tagOpenModes
{
	FMT_STREAM_OMODE_UNKNOWN = 0,
	FMT_STREAM_OMODE_READ = 1,
	FMT_STREAM_OMODE_WRITE = 2,
	FMT_STREAM_OMODE_APPEND = 3,	// Moves EOF marker. Default.
	FMT_STREAM_OMODE_READWRITE = 4,	// File must exist.
	FMT_STREAM_OMODE_READWRITE_CREATE = 5,
	FMT_STREAM_OMODE_READ_BINARY = 6,
	FMT_STREAM_OMODE_WRITE_BINARY = 7,
	FMT_STREAM_OMODE_LAST
} EMSFORMATTEDSTREAMOPENMODE;

//! @class CEMSFormattedFileStream
//! Represents a text file stream.
class CEMSFormattedFileStream : public IEMSTextSeqStream, public CApiObjBase
{
	public:
		CEMSFormattedFileStream();
		CEMSFormattedFileStream( const CEMSFormattedFileStream& x );
		virtual ~CEMSFormattedFileStream();

		//! @fn void SetFilePath( const wchar_t* cwszFileSpec )
		//! Specify the fully qualified filename associated with this stream.
		void SetFilePath( const wchar_t* cwszFileSpec ) { m_wszFileSpec = cwszFileSpec; }

		//! @fn void SetMode( const EMSFORMATTEDSTREAMOPENMODE ceMode )
		//! Specify the mode with which to opent the file.
		void SetMode( const EMSFORMATTEDSTREAMOPENMODE ceMode ) { m_eMode = ceMode; }

		//! @fn int Write( const wchar_t* cwszFormat, ... )
		//! Write formatted data to the stream.
		int Write( const wchar_t* cwszFormat, ... );

		//! Write formatted (text) data to the stream.  The byte array is assumed to hold "char" type characters.
		int WriteA( const BYTE* cabyData, const ULONG culBytes );

		//! @fn int WriteBinary( const wchar_t* cwszData )
		//! Write the string as literal data.
		int WriteBinary( const wchar_t* cwszData );

		//! Write the byte array as literal data.
		int WriteBinary( const BYTE* cabyData, const ULONG culBytes );

		//! @fn int AddLine( const wchar_t* cwszFormat, ... )
		//! Write formatted data to the stream.  Automatically append a CRLF.
		int AddLine( const wchar_t* cwszFormat, ... );

		//! @fn std::wstring ReadAll()
		//! Read the entire file contents into a string.
		std::wstring ReadAll();

		//! Read the entire file contents into a string.
		std::string ReadAllA();

		//! @fn std::wstring ReadLine()
		//! Read a single line from the stream.  Assume that CR, CRLF or LF act as line delimiters.
		std::wstring ReadLine();

		//! Read a single line from the stream.  Assume that CR, CRLF or LF act as line delimiters.
		//! Strips of last character if its a newline chracter.
		std::wstring ReadLine2();

		//! @fn void Close()
		//! Close the stream.
		void Close();

/*********************************************************************
*	IEMSSeqStream Methods
*********************************************************************/
		//! @fn HRESULT STDMETHODCALLTYPE Read( BYTE* pv, ULONG cb, ULONG* pcbRead );
		//! Read a single line (wide characters) from the stream (see above).
		//! Will return at most the first cb bytes.
		//! Assumes that the caller has allocated the return buffer.
        virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
		//! @fn HRESULT STDMETHODCALLTYPE Write( BYTE* pv, ULONG cb, ULONG* pcbWritten );
		//! Write a single line (wide characters) to the stream.
		//! *** NOT IMPLEMENTED ***
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbWritten);

/*********************************************************************
*	IEMSTextSeqStream Methods
*********************************************************************/

		//! @fn HRESULT STDMETHODCALLTYPE ReadLine( wchar_t** ppwszLine );
		//! Read a single line (wide characters) from the stream.
		//! Caller must deallocate returned string using CoTaskMemFree()
        virtual HRESULT STDMETHODCALLTYPE ReadLine( 
            /* [string][out] */ wchar_t **ppwszLine);
        
		//! @fn HRESULT STDMETHODCALLTYPE Write( wchar_t* pwszLine );
		//! Write a single line (wide characters) to the stream.
		//! *** NOT IMPLEMENTED ***
        virtual HRESULT STDMETHODCALLTYPE WriteLine( 
            /* [string][in] */ wchar_t *pwszLine);

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);


	private:
		void _Init();

	private:
		std::wstring m_wszFileSpec;
		FILE*	m_fpStream;
		EMSFORMATTEDSTREAMOPENMODE m_eMode;

};

#endif