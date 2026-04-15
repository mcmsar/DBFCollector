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
#pragma warning(disable:4786)

#include "CSVFile.h"
#include "RecordMetaData.h"
#include "emsexcpt.h"
#include "assert.h"

CEMSCSVFile::CEMSCSVFile() : m_wcSeparator(L',')
{
}

CEMSCSVFile::CEMSCSVFile( const CEMSCSVFile& x ) : 
	m_wcSeparator(x.m_wcSeparator), 
	m_oFileStream( x.m_oFileStream ),
	m_oReader( x.m_oReader )
{
}

CEMSCSVFile::~CEMSCSVFile()
{
	_reset();
}

void
CEMSCSVFile::_reset()
{
	m_oFileStream.Close();
	m_oReader.Clear();
}

void
CEMSCSVFile::Close()
{
	_reset();
}

void
CEMSCSVFile::Open(	const wchar_t* cwszFilename,
					const wchar_t cwcSeparator,
					const EMSRESOURCEOPENMODE eMode )
{
	assert( cwszFilename && wcslen(cwszFilename) > 5 ); // at least x.xxx
 	assert( cwcSeparator != 0 );

	// Just in case
	_reset();

	EMSFORMATTEDSTREAMOPENMODE	eUseMode = (eMode == RES_OPEN_MODE_WRITE) ? FMT_STREAM_OMODE_WRITE : FMT_STREAM_OMODE_READ;

	// Setup the file access
	m_oFileStream.SetFilePath( cwszFilename );
	m_oFileStream.SetMode( eUseMode );

	m_wcSeparator = cwcSeparator;
}

void
CEMSCSVFile::ReadHeader(	const int  ciHeaderLines,
							const bool cbReadColumnNames,
							const int  ciColumnNamesOnLine )
{
	for ( int i=0; i< ciHeaderLines; i++ )
	{
		if ( !cbReadColumnNames || i != ciColumnNamesOnLine )
		{
			_skipLine();
		}
		else
		{
			// Column names will be comma-separated values too
			int iValueCount = _readCSVLine();

			// Tell the reader to build meta-data using the current values
			// It will retain it for use with subsequent lines
			m_oReader.BuildMetaData();
		}
	}
}

CEMSRecordMetaData*
CEMSCSVFile::GetMetaData()
{
	return m_oReader.GetMetaData();
}

void
CEMSCSVFile::_skipLine()
{
	// simply toss the next line away
	m_oFileStream.ReadLine();
}

int
CEMSCSVFile::ReadLine()
{
	// load comma separated values from the next line
	return _readCSVLine();
}

wstring
CEMSCSVFile::GetValue( const int ciColumnIndex )
{
	return m_oReader.GetFieldAsStringW( ciColumnIndex );
}

string
CEMSCSVFile::GetValueA( const int ciColumnIndex )
{
	return m_oReader.GetFieldAsStringA( ciColumnIndex );
}

wstring
CEMSCSVFile::GetValue( const wchar_t* cwszColumn )
{
	return m_oReader.GetFieldAsStringW( cwszColumn );
}

string
CEMSCSVFile::GetValueA( const wchar_t* cwszColumn )
{
	return m_oReader.GetFieldAsStringA( cwszColumn );
}


IEMSSeqStream*	
CEMSCSVFile::GetSeqStream()
{
	IEMSSeqStream*	pRet = NULL;
	EMS_RESULT		hr = m_oFileStream.QueryInterface( IID_IEMSSeqStream, (void**)&pRet );
	if ( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION(hr);
	}
	return pRet;
}

int
CEMSCSVFile::_readCSVLine()
{
	std::wstring	wstrLine = m_oFileStream.ReadLine();
	if ( !wstrLine.empty() )
	{
		return m_oReader.Init( wstrLine, m_wcSeparator );
	}
	return 0;
}
