/********************************************************************
*	Module:			emsfftfile.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSFFTFile
*					Class to manage/create reading and writing FFT files ( for Audio )
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

// TODO
// TODO
// TODO
// TODO
// TODO

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2005/3/5		rrr&rvw	start

********************************************************************/
#include "emsfftfile.h"

CEMSFFTFile::CEMSFFTFile( )
{
	memset( &m_hdr, 0, sizeof( m_hdr ) );

	m_hFile = INVALID_HANDLE_VALUE;

	m_bHeaderRead = false;

	m_nHdrSize = 0;

	m_lCurrentRecord = -1;
}

CEMSFFTFile::~CEMSFFTFile( )
{
	if ( IsOpen( ) )
		Close( );
}

EMS_RESULT CEMSFFTFile::Open( LPCTSTR lpcszFilespec, bool bShared )
{
	EMS_RESULT hr = EMS_OK;

	if ( !IsOpen( ) )
	{
		if ( lpcszFilespec && *lpcszFilespec )
		{
			DWORD dwShareFlags = ( bShared ) ? FILE_SHARE_READ | FILE_SHARE_WRITE : 0;

			m_hFile = CreateFile( lpcszFilespec, GENERIC_READ, dwShareFlags,
						0,	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0 );

			if ( INVALID_HANDLE_VALUE == m_hFile )
				hr = HRESULT_FROM_WIN32( GetLastError( ) );
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_ALREADY_OPEN;

	return hr;
}

EMS_RESULT CEMSFFTFile::Create( LPCTSTR lpcszFilespec, bool bShared )
{
	EMS_RESULT hr = EMS_OK;

	if ( !IsOpen( ) )
	{
		if ( lpcszFilespec && *lpcszFilespec )
		{
			DWORD dwShareFlags = ( bShared ) ? FILE_SHARE_READ | FILE_SHARE_WRITE : 0;

			m_hFile = CreateFile( lpcszFilespec, GENERIC_WRITE, dwShareFlags,
						0,	CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
	
			if ( INVALID_HANDLE_VALUE == m_hFile )
				hr = HRESULT_FROM_WIN32( GetLastError( ) );
		}
		else
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_ALREADY_OPEN;

	return hr;
}

EMS_RESULT CEMSFFTFile::Close( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( IsOpen( ) )
	{
		CloseHandle( m_hFile );

		m_bHeaderRead = false;

		m_hFile = INVALID_HANDLE_VALUE;

		memset( &m_hdr, 0, sizeof( m_hdr ) );

		m_nHdrSize = 0;

		m_lCurrentRecord = -1;
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

EMS_RESULT CEMSFFTFile::ReadHeader( EMSFFTHEADER2 *lpHeader )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpHeader )
	{
		if ( IsOpen( ) ) 
		{
			if ( !m_bHeaderRead )
			{
				hr = _ReadHeader( &m_hdr, false );
			}

			if ( EMS_OK == hr )
			{
				*lpHeader = m_hdr;

				m_lCurrentRecord = 0;

				m_timeCurrentRecord.SetTime( m_hdr.id.time );
			}
		}
		else
			hr = EMS_NOT_OPEN;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSFFTFile::_ConvertFFTHeader( EMSFFTHEADER2 *lpHdr2, EMSFFTHEADER *lpHdr1 )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpHdr1 && lpHdr2 )
	{
		lpHdr2->sig = lpHdr1->sig;
		lpHdr2->sig.version.wNumber = 0x200;
		lpHdr2->id = lpHdr1->id;
		lpHdr2->ulPassNumber = lpHdr1->ulPassNumber;
		lpHdr2->ulDataRecordSize = lpHdr1->ulDataRecordSize;
		lpHdr2->i64DurationFFT = lpHdr1->i64DurationFFT;
		lpHdr2->fFFTOverlapFactor = 0.125;
		lpHdr2->fFreqBinSize = lpHdr1->fFreqBinSize;
		lpHdr2->wNumFFTBins = (WORD)( ( lpHdr1->ulDataRecordSize - sizeof( EMSFFTDATA ))
							  				/ ( sizeof( EMSCOMPLEX ) * lpHdr1->wNumFFTs ) );
		lpHdr2->wNumFFTs = lpHdr1->wNumFFTs;
		lpHdr2->wNumBands = lpHdr1->wNumBands;

		for ( int i = 0; i < lpHdr1->wNumBands; i++ )
		{
			lpHdr2->band[i].wStartFreqBin = lpHdr1->band[i].wStartFreqBin;
			lpHdr2->band[i].wStopFreqBin = lpHdr1->band[i].wStopFreqBin;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSFFTFile::_ReadHeader( EMSFFTHEADER2 *lpHeader, bool bRestorePosn )
{
	EMS_RESULT hr = EMS_OK;

	if ( IsOpen( ) ) 
	{
		DWORD dwOrigOffset = ( bRestorePosn ) ? SetFilePointer( m_hFile, 0, 0, FILE_CURRENT ) : 0;
		DWORD dwOffset = SetFilePointer( m_hFile, 0, 0, FILE_BEGIN );

		if ( 0 == dwOffset )
		{
			BOOL bOK;
			DWORD dwBytesRead = 0;
			EMSFILESIGNATURE fileSign;
			EMSFFTHEADER hdr1;

			bOK = ReadFile( m_hFile, (LPVOID)&fileSign, sizeof( fileSign ), 
									&dwBytesRead, 0);

			switch ( fileSign.version.wNumber )
			{
				case 0x100:
					dwOffset = SetFilePointer( m_hFile, 0, 0, FILE_BEGIN );

					bOK=ReadFile( m_hFile, (LPVOID)&hdr1, sizeof( hdr1 ), &dwBytesRead, 0 );

					if( sizeof( hdr1 ) == dwBytesRead )
					{

						m_nHdrSize = sizeof( EMSFFTHEADER );

						hr = _ConvertFFTHeader( lpHeader, &hdr1 );
					}
					else
						hr = EMS_EMPTY;

					break;

				case 0x200:
					dwOffset = SetFilePointer( m_hFile, 0, 0, FILE_BEGIN );

					bOK=ReadFile( m_hFile, (LPVOID)lpHeader, sizeof( EMSFFTHEADER2 ), 
							&dwBytesRead, 0 );

					if( sizeof( EMSFFTHEADER2 ) == dwBytesRead )
					{
						m_nHdrSize = sizeof( EMSFFTHEADER2 );
					}
					else
						hr = EMS_EMPTY;

					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if( EMS_OK == hr )
			{
				if ( bOK )
					m_bHeaderRead = true;
				else
					hr = EMS_IO_ERROR;
			}
			else
			{
				// Restore position on error.
				SetFilePointer( m_hFile, dwOrigOffset, 0, FILE_BEGIN );
			}

			if ( bRestorePosn )
				SetFilePointer( m_hFile, dwOrigOffset, 0, FILE_BEGIN );
		}
		else
			hr = EMS_IO_ERROR;
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

EMS_RESULT CEMSFFTFile::WriteHeader( EMSFFTHEADER2 *lpHeader )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpHeader )
	{
		if ( IsOpen( ) ) 
		{
			DWORD dwOffset = SetFilePointer( m_hFile, 0, 0, FILE_BEGIN );

			if ( 0 == dwOffset )
			{
				DWORD dwBytesWritten = 0;
				BOOL bOK = WriteFile( m_hFile, (LPVOID)lpHeader, 
									 sizeof( EMSFFTHEADER2 ), &dwBytesWritten, 0 );

				if ( !bOK )
					hr = EMS_IO_ERROR;
			}
			else
				hr = EMS_IO_ERROR;
		}
		else
			hr = EMS_NOT_OPEN;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSFFTFile::_SeekFromEOF( LONG lRecord )
{
	EMS_RESULT hr = EMS_OK;
	LONG lMaxRecord = GetRecordCount( );
	LONG lDesiredRecord = lMaxRecord + lRecord;

	if ( lDesiredRecord < lMaxRecord )
		hr = _SeekFromBOF( lDesiredRecord );
	else
		hr = EMS_EOF;

	return hr;
}

EMS_RESULT CEMSFFTFile::_SeekFromCurrentPosn( LONG lRecord )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;
	return hr;
}

EMS_RESULT CEMSFFTFile::_SeekFromBOF( LONG lRecord )
{
	EMS_RESULT hr = EMS_OK;

	if ( lRecord >= 0 )
	{
		if ( lRecord != m_lCurrentRecord )
		{
			DWORD dwDesiredOffset = m_nHdrSize + ( lRecord * m_hdr.ulDataRecordSize );
			DWORD dwOffset = SetFilePointer( m_hFile, dwDesiredOffset, 0, FILE_BEGIN );

			if ( dwOffset == dwDesiredOffset )
				m_lCurrentRecord = lRecord;
			else
				hr = EMS_EOF;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSFFTFile::Seek( LONG lRecord, EMSFFTFILESEEKMETHOD seekMethod )
{
	EMS_RESULT hr = EMS_OK;

	if ( IsOpen( ) )
	{
		if ( !m_bHeaderRead )
			hr = _ReadHeader( &m_hdr );

		if ( EMS_OK == hr )
		{
			switch ( seekMethod )
			{
				case EMSFFTFILE_BEGIN:
					hr = _SeekFromBOF( lRecord );
					break;

				case EMSFFTFILE_CURR:
					hr = _SeekFromCurrentPosn( lRecord );
					break;

				case EMSFFTFILE_END:
					hr = _SeekFromEOF( lRecord );
					break;

				default:
					hr = EMS_BAD_PARAM;
					break;
			}
		}
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}



EMS_RESULT CEMSFFTFile::Seek( EMSTIME timeRecord )
{
	EMS_RESULT hr = EMS_OK;

	if ( IsOpen( ) )
	{
		if ( !m_bHeaderRead )
			hr = _ReadHeader( &m_hdr );

		if ( EMS_OK == hr )
		{
		}
	}
	else
		hr = EMS_NOT_OPEN;

	return hr;
}

EMS_RESULT CEMSFFTFile::WriteRecord( EMSFFTDATA *lpData, EMSCOMPLEX *lpBuffer, LONG lCount )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}

EMS_RESULT CEMSFFTFile::ReadRecord( EMSFFTDATA *lpData, EMSCOMPLEX *lpBuffer, LONG lMaxCount, LONG *lplCount )
{
	EMS_RESULT hr = EMS_OK;
	LONG lCount = 0;

	if ( IsOpen( ) )
	{
		if ( m_bHeaderRead )
		{
			DWORD dwBytesRead = 0;
			ULONG ulSize = m_hdr.ulDataRecordSize - sizeof( EMSFFTDATA );
			BOOL bOK = ReadFile( m_hFile, lpData, sizeof( EMSFFTDATA ), &dwBytesRead, 0 );

			if ( !bOK || ( sizeof( EMSFFTDATA ) != dwBytesRead ) )
				hr = EMS_EOF;

			 if ( EMS_OK == hr )
			 {
				 bOK = ReadFile( m_hFile, lpBuffer, ulSize, &dwBytesRead, 0 );

 				if ( !bOK || ( ulSize != dwBytesRead ) )
					hr = EMS_EOF;

				 if ( EMS_OK == hr )
				 {
					INT64 i64FFTTimeInterval = (INT64)((double)m_hdr.i64DurationFFT * ( 1.0 - m_hdr.fFFTOverlapFactor )); 

					m_lCurrentRecord++;

					m_timeCurrentRecord.SetTime( lpData->timeStamp );

					m_timeCurrentRecord.AddNanoseconds( (LONG)i64FFTTimeInterval );

					lCount = dwBytesRead / sizeof( EMSCOMPLEX );
				 }
				else
				 	hr = HRESULT_FROM_WIN32( GetLastError( ) );
			 }
		}
	}
	else
		hr = EMS_NOT_OPEN;

	if ( lplCount )
		*lplCount = lCount;

	return hr;
}

LONG CEMSFFTFile::GetRecordCount( void )
{
	EMS_RESULT hr = EMS_OK;
	LONG lCount = 0;

	if ( IsOpen( ) )
	{
		DWORD dwOrigOffset = SetFilePointer( m_hFile, 0, 0, FILE_CURRENT );
		DWORD dwFileSize = SetFilePointer( m_hFile, 0, 0, FILE_END );
		DWORD dwRecordBytes = dwFileSize - m_nHdrSize;

		if( m_hdr.ulDataRecordSize > 0 )
			lCount = ( dwRecordBytes / m_hdr.ulDataRecordSize );

		SetFilePointer( m_hFile, dwOrigOffset, 0, FILE_BEGIN );
	}
	else
		hr = EMS_NOT_OPEN;

	return lCount;
}
