/*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc., All rights reserved
*
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __EMSCSVFILE_H__
#define __EMSCSVFILE_H__

#include <vector>
using std::vector;

#include <string>
using std::wstring;
using std::string;

#include "FormattedFileStream.h"
#include "CSVReader.h"
#include "EMSResource.h" //EMSRESOURCEOPENMODE

class CEMSRecordMetaData;

class CEMSCSVFile 
{
public:
	CEMSCSVFile();
	CEMSCSVFile( const CEMSCSVFile& x );
	virtual ~CEMSCSVFile();

	//! @fn void Open( const wchar_t* cwszFilename, 
	//!				   const wchar_t cwcSeparator = L',',
	//!				   const EMSRESOURCEOPENMODE eMode = RES_OPEN_MODE_READ );
	//! Specify the fully qualified filename + the separator character.
	void			Open(	const wchar_t* cwszFilename,
							const wchar_t cwcSeparator = L',',
							const EMSRESOURCEOPENMODE eMode = RES_OPEN_MODE_READ );
	//! @fn void Close()
	//! Close the file.
	void			Close();

	//! @fn void ReadHeader( const int  ciHeaderLines = 1,
	//!						 const bool cbReadColumnNames = true,
	//!						 const int  ciColumnNamesOnLine = 0 );
	//! Read the header.
	//! Optionally load the column names into memory so that
	//! values can be accessed by name.  
	//! Note that assumes column names are comma separated values.
	//! This function must be called if the file has a header
	//! whether or not you intend to use the column names.
	void			ReadHeader(	const int  ciHeaderLines = 1,
								const bool cbReadColumnNames = true,
								const int  ciColumnNamesOnLine = 0 );

	//! @fn int ReadLine();
	//!	Read the next line into memory so that the values can be accessed
	//! Returns the number of values found on the line.
	int				ReadLine();

	//! @fn std::wstring	GetValue( const wchar_t* cwszColumn );
	//! @fn std::wstring	GetValue( const int ciColumnIndex );
	//! @fn std::string		GetValueA( const wchar_t* cszColumn );
	//! @fn std::string		GetValueA( const int ciColumnIndex );
	//!	Return the value for the specified column.
	//! Columns can be identified by name (if column names were read from the header )
	//! or by index.
	wstring	GetValue( const wchar_t* cwszColumn );
	wstring	GetValue( const int ciColumnIndex );
	string	GetValueA( const wchar_t* cwszColumn );
	string	GetValueA( const int ciColumnIndex );

	//! @fn IEMSSeqStream*	GetSeqStream();
	//! Return a pointer to the file stream
	IEMSSeqStream*	GetSeqStream();

	//! @fn CEMSRecordMetaData* GetMetaData();
	//! Return a pointer to the current set of metadata
	//! Caller must release the returned pointer
	//! May return NULL
	CEMSRecordMetaData* GetMetaData();

private:
	void			_reset();
	int				_readCSVLine();
	void			_skipLine();

	CEMSCSVReader			m_oReader;
	CEMSFormattedFileStream	m_oFileStream;

	wchar_t					m_wcSeparator;
};

#endif // __EMSCSVFILE_H__
